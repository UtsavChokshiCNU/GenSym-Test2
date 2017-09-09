;; -*- Mode:Common-Lisp; Package:AB; Base:10; Syntax:COMMON-LISP -*-
(in-package "AB")

;;;; Module KFEP2  --  Kanji Front End Processor

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Ong, Peng Tsin and Mark H. David



#+font-files
(declare-forward-reference read-asian-font-file function)	; FONT-FILES
(declare-forward-reference current-kb-serial-number variable) ; KB-SAVE2







(defparameter allowable-non-alpha-characters-in-kfep-conversions '(#.%\- #.%\'))






;; Calls to the facilities herein in modules EDIT and RUN must therefore be
;; appropriately conditionalized!



;;; Here are a few sample Kanji words in Romaji:
;;;
;;; amerika (in Katakana) == America
;;; atarashi == new
;;; nihon  == Japan
;;; nihongo == Japanese language
;;; toukyou == Tokyo
;;; sake == sake








;;; The original KFEP C files are
;;;
;;;    kkabunpo kkasetbl kkaretry kkaro2ka
;;;    kkakojin kkasystm kkamiscs
;;;    kkabatch kkabatch_g2 kkaprimitive
;;;
;;;
;;; They were originally loaded, in the above order, with
;;; 
;;;      (load-gensym-c-object-file
;;;	   (make-system-c-file-object-namestring
;;;	      c-module-name current-system-being-loaded)
;;;	   '("-lc"))












;;;; Interfaces to KFEP (originally C) Functions

;; From kkaprimitive.c




;;; `Kka_P_batkanakan' causes a translation of the Hiragana JIS codes in
;;; inbuf to be translated, and the output to be put in outbuf.
;;; It returns 3 values.  The first value is the number of JIS characters used
;;; in the translation.  The second is the number of bytes used to hold the
;;; translation in outbuf.  The third is the number of candidates left, not
;;; counting the one that is being returned.  If the first value is less than
;;; or equal to zero, the other returned values should be ignored.

;;; The argument sw is:
;;;    1 if the first candidate of this translation is desired.
;;;    0 if the next candidate of this translation is desired.

;; If inbuf has a fill pointer, there might be translation problems on several
;; platforms. [OBSOLETE! (MHD 1/3/91)]

(defun kka_P_batkanakan (sw inbuf inlen outbuf)
  (let* ((inbuf-to-use inbuf)
	 (reclaim? nil))
    (when (array-has-fill-pointer-p inbuf)	; Is this necessary now that
      (setq reclaim? t)				;   we no longer interface to C?!
      (setq inbuf-to-use			;   (MHD 1/3/91)
	    (copy-managed-lisp-string inbuf 0 inlen)))
    (multiple-value-bind (number-of-jis-characters-used
			  bytes-in-output number-of-candidates-left)
	(kfep-kka-p-batkanakan sw inbuf-to-use inlen outbuf)
      (if reclaim? (reclaim-lisp-string inbuf-to-use))
      (values
	number-of-jis-characters-used
	bytes-in-output number-of-candidates-left))))

;; The value of this function is essentially battable[0].yomilen, which is supposed
;; to be the number of JIS characters used in the translation.  -1 is returned if
;; no translation is possible.  The translation is stored in the string outbuf.






;;; `Kka_P_updatekojin' tells the KFEP to "learn" the fact that from the last
;;; list of translations, the nth-candidate was picked (n is 0 based).  This
;;; function returns -1 if an error occurs.

(defmacro kka_P_updatekojin (candidate-index)
  `(kfep-kka-p-update-kojin ,candidate-index))












;;; The function `kka_batkanakan_g2' is like kka_batkanakan, except that
;;; it returns the length of the outbuf.  This function appears in
;;; kkabatch_g2.c



;;; The function `kka_batkanakan' is a Lisp analogue to the C function of the
;;; same name.  Instead of requiring a pointer to the variable containing the
;;; length of the output string, the length of the number of bytes used in the
;;; output string (or a negative number in case of an error) is returned.
;;;
;;; The output-string is filled with the translated JIS string in the following
;;; format:
;;;   <ascii-code-01><translated-jis-string><ascii-code-01><rest-of-translated-jis-string>
;;; The pair of <ascii-code-01>'s surround the part of the JIS Kanji string which
;;; kka_batkanakan considers a suitable translation.






;;; kkabunpo.c

;; See the function kfep-chkbunpo!

;; When value-to-return equals:
;;   0 -> chkbunpo is called, and its return value is returned,
;;   1 -> the value of bunpo from the last call is returned.
;;   other -> the value of pat from the last call is returned.

;; ... more stuff here ... 






;;; kkasetbl.c







;;; kkaretry.c







;;; kkaro2ka.c

;;; The constant `ascii-and-kana-suffix-pairs' is a roman-to-kana code table.
;;; At present, it is just used to initialize the jis map in initialize-ascii-
;;; kana-converters-if-neccessary.  It is used for translating ascii to kana
;;; and vice versa.
;;;
;;; NOTE: the entries are case sensitive in this form, but not when user types
;;; them in.  The keys (car's) of each entry should be all uppercase,
;;; representing roman keyboard entries, which won't be case senstive.  The
;;; values (cdr's) of each entry are mixed case, representing binary character
;;; code values (relative to JIS X 0208).
;;;
;;; The standard set of mappings can only be said to exist for a strict subset
;;; of these mappings.  Therefore, some of these are not standard, or only
;;; semistandard.  In all cases these represent CTC's best judgement as to
;;; friendly or reasonable behavior, which Gensym believes to be excellent
;;; advice to utilize.

(def-kfep-constant ascii-and-kana-suffix-pairs
  '(("A" . "\"") ("BA" . "P") ("DA" . "@") ("FA" . "U!") ("GA" . ",")
    ("HA" . "O") ("JA" . "8c") ("KA" . "+") ("LA" . "i") ("MA" . "^")
    ("NA" . "J") ("PA" . "Q") ("QA" . "/!") ("RA" . "i") ("SA" . "5")
    ("TA" . "?") ("VA" . "~t!") ("WA" . "o") ("XA" . "!") ("YA" . "d")
    ("ZA" . "6")
    ("MY" . ascii)
    ("BBA" . "CP") ("DDA" . "C@") ("FFA" . "CU!")
    ("GGA" . "C,") ("CHA" . "Ac") ("DHA" . "Gc") ("HHA" . "CO")
    ("SHA" . "7c") ("THA" . "Fc") ("JJA" . "C8c") ("KKA" . "C+")
    ("XKA" . "~u") ("LLA" . "Ci") ("MMA" . "s^") ("NNA" . "sJ")
    ("PPA" . "CQ") ("QQA" . "C/!") ("RRA" . "Ci") ("SSA" . "C5")
    ("TSA" . "D!") ("TTA" . "C?") ("VVA" . "C~t!") ("GWA" . "0n")
    ("KWA" . "/n") ("WWA" . "Co") ("XWA" . "n") ("BYA" . "Sc")
    ("CYA" . "Ac") ("DYA" . "Bc") ("FYA" . "Uc") ("GYA" . ".c")
    ("HYA" . "Rc") ("JYA" . "8c") ("KYA" . "-c") ("LYA" . "jc")
    ("MYA" . "_c") ("NYA" . "Kc") ("PYA" . "Tc") ("QYA" . "/c")
    ("RYA" . "jc") ("SYA" . "7c") ("TYA" . "Ac") ("XYA" . "c")
    ("YYA" . "Cd") ("ZYA" . "8c") ("ZZA" . "C6") ("CCHA" . "CAc")
    ("TCHA" . "CAc") ("DDHA" . "CGc") ("SSHA" . "C7c") ("TTHA" . "CFc")
    ("TTSA" . "CD!") ("GGWA" . "C0n") ("KKWA" . "C/n") ("BBYA" . "CSc")
    ("CCYA" . "CAc") ("DDYA" . "CBc") ("FFYA" . "CUc") ("GGYA" . "C.c")
    ("HHYA" . "CRc") ("JJYA" . "C8c") ("KKYA" . "C-c") ("LLYA" . "Cjc")
    ("MMYA" . "s_c") ("NNYA" . "sKc") ("PPYA" . "CTc") ("QQYA" . "C/c")
    ("RRYA" . "Cjc") ("SSYA" . "C7c") ("TTYA" . "CAc") ("ZZYA" . "C8c")
    ("E" . "(") ("BE" . "Y") ("DE" . "G") ("FE" . "U'") ("GE" . "2")
    ("HE" . "X") ("JE" . "8'") ("KE" . "1") ("LE" . "l") ("ME" . "a")
    ("NE" . "M") ("PE" . "Z") ("QE" . "/'") ("RE" . "l") ("SE" . ";")
    ("TE" . "F") ("VE" . "~t'") ("WE" . "q") ("XE" . "'") ("YE" . "(")
    ("ZE" . "<") ("BBE" . "CY") ("DDE" . "CG") ("FFE" . "CU'")
    ("GGE" . "C2") ("CHE" . "A'") ("DHE" . "G'") ("HHE" . "CX")
    ("SHE" . "7'") ("THE" . "F'") ("JJE" . "C8'") ("KKE" . "C1")
    ("XKE" . "~v") ("LLE" . "Cl") ("MME" . "sa") ("NNE" . "sM")
    ("PPE" . "CZ") ("QQE" . "C/'") ("RRE" . "Cl") ("SSE" . "C;")
    ("TSE" . "D'") ("TTE" . "CF") ("VVE" . "C~t'") ("GWE" . "0'")
    ("KWE" . "/'") ("WWE" . "Cq") ("BYE" . "S'") ("CYE" . "A'")
    ("DYE" . "B'") ("FYE" . "U'") ("GYE" . ".'") ("HYE" . "R'")
    ("JYE" . "8'") ("KYE" . "-'") ("LYE" . "j'") ("MYE" . "_'")
    ("NYE" . "K'") ("PYE" . "T'") ("QYE" . "/'") ("RYE" . "j'")
    ("SYE" . "7'") ("TYE" . "A'") ("XYE" . "'") ("YYE" . "C(")
    ("ZYE" . "8'") ("ZZE" . "C<") ("CCHE" . "CA'") ("TCHE" . "CA'")
    ("DDHE" . "CG'") ("SSHE" . "C7'") ("TTHE" . "CF'") ("TTSE" . "CD'")
    ("GGWE" . "C0'") ("KKWE" . "C/'") ("BBYE" . "CS'") ("CCYE" . "CA'")
    ("DDYE" . "CB'") ("FFYE" . "CU'") ("GGYE" . "C.'") ("HHYE" . "CR'")
    ("JJYE" . "C8'") ("KKYE" . "C-'") ("LLYE" . "Cj'") ("MMYE" . "s_'")
    ("NNYE" . "sK'") ("PPYE" . "CT'") ("QQYE" . "C/'") ("RRYE" . "Cj'")
    ("SSYE" . "C7'") ("TTYE" . "CA'") ("ZZYE" . "C8'") ("I" . "$")
    ("BI" . "S") ("DI" . "B") ("FI" . "U#") ("GI" . ".") ("HI" . "R")
    ("JI" . "8") ("KI" . "-") ("LI" . "j") ("MI" . "_") ("NI" . "K")
    ("PI" . "T") ("QI" . "/#") ("RI" . "j") ("SI" . "7") ("TI" . "A")
    ("VI" . "~t#") ("WI" . "p") ("XI" . "#") ("YI" . "$") ("ZI" . "8")
    ("BBI" . "CS") ("DDI" . "CB") ("FFI" . "CU#") ("GGI" . "C.")
    ("CHI" . "A") ("DHI" . "G#") ("HHI" . "CR") ("SHI" . "7")
    ("THI" . "F#") ("JJI" . "C8") ("KKI" . "C-") ("LLI" . "Cj")
    ("MMI" . "s_") ("NNI" . "sK") ("PPI" . "CT") ("QQI" . "C/#")
    ("RRI" . "Cj") ("SSI" . "C7") ("TSI" . "D#") ("TTI" . "CA")
    ("VVI" . "C~t#") ("GWI" . "0#") ("KWI" . "/#") ("WWI" . "Cp")
    ("BYI" . "S#") ("CYI" . "A#") ("DYI" . "B#") ("FYI" . "U#")
    ("GYI" . ".#") ("HYI" . "R#") ("JYI" . "8#") ("KYI" . "-#")
    ("LYI" . "j#") ("MYI" . "_#") ("NYI" . "K#") ("PYI" . "T#")
    ("QYI" . "/#") ("RYI" . "j#") ("SYI" . "7#") ("TYI" . "A#")
    ("XYI" . "#") ("YYI" . "C$") ("ZYI" . "8#") ("ZZI" . "C8")
    ("CCHI" . "CA") ("TCHI" . "CA") ("DDHI" . "CG#") ("SSHI" . "C7")
    ("TTHI" . "CF#") ("TTSI" . "CD#") ("GGWI" . "C0#") ("KKWI" . "C/#")
    ("BBYI" . "CS#") ("CCYI" . "CA#") ("DDYI" . "CB#") ("FFYI" . "CU#")
    ("GGYI" . "C.#") ("HHYI" . "CR#") ("JJYI" . "C8#") ("KKYI" . "C-#")
    ("LLYI" . "Cj#") ("MMYI" . "s_#") ("NNYI" . "sK#") ("PPYI" . "CT#")
    ("QQYI" . "C/#") ("RRYI" . "Cj#") ("SSYI" . "C7#") ("TTYI" . "CA#")
    ("ZZYI" . "C8#") ("O" . "*") ("BO" . "\\") ("DO" . "I") ("FO" . "U)")
    ("GO" . "4") ("HO" . "[") ("JO" . "8g") ("KO" . "3") ("LO" . "m")
    ("MO" . "b") ("NO" . "N") ("PO" . "]") ("QO" . "/)") ("RO" . "m")
    ("SO" . "=") ("TO" . "H") ("VO" . "~t)") ("WO" . "r") ("XO" . ")")
    ("YO" . "h") ("ZO" . ">") ("BBO" . "C\\") ("DDO" . "CI")
    ("FFO" . "CU)") ("GGO" . "C4") ("CHO" . "Ag") ("DHO" . "Gg")
    ("HHO" . "C[") ("SHO" . "7g") ("THO" . "Fg") ("JJO" . "C8g")
    ("KKO" . "C3") ("LLO" . "Cm") ("MMO" . "sb") ("NNO" . "sN")
    ("PPO" . "C]") ("QQO" . "C/)") ("RRO" . "Cm") ("SSO" . "C=")
    ("TSO" . "D)") ("TTO" . "CH") ("VVO" . "C~t)") ("GWO" . "0)")
    ("KWO" . "/)") ("WWO" . "Cr") ("BYO" . "Sg") ("CYO" . "Ag")
    ("DYO" . "Bg") ("FYO" . "Ug") ("GYO" . ".g") ("HYO" . "Rg")
    ("JYO" . "8g") ("KYO" . "-g") ("LYO" . "jg") ("MYO" . "_g")
    ("NYO" . "Kg") ("PYO" . "Tg") ("QYO" . "/g") ("RYO" . "jg")
    ("SYO" . "7g") ("TYO" . "Ag") ("XYO" . "g")

    ;; Changed per CTC Request (MHD 11/25/96): ("YYO" . "CH") => ("YYO" . "Ch")
    ("YYO" . "Ch")
    
    ("ZYO" . "8g") ("ZZO" . "C>") ("CCHO" . "CAg") ("TCHO" . "CAg")
    ("DDHO" . "CGg") ("SSHO" . "C7)") ("TTHO" . "CFg") ("TTSO" . "CD)")
    ("GGWO" . "C0)") ("KKWO" . "C/)") ("BBYO" . "CSg") ("CCYO" . "CAg")
    ("DDYO" . "CBg") ("FFYO" . "CUg") ("GGYO" . "C.g") ("HHYO" . "CRg")
    ("JJYO" . "C8g") ("KKYO" . "C-g") ("LLYO" . "Cjg") ("MMYO" . "s_g")
    ("NNYO" . "sKg") ("PPYO" . "CTg") ("QQYO" . "C/g") ("RRYO" . "Cjg")
    ("SSYO" . "C7g") ("TTYO" . "CAg") ("ZZYO" . "C8g") ("U" . "&")
    ("BU" . "V") ("DU" . "E") ("FU" . "U") ("GU" . "0") ("HU" . "U")
    ("JU" . "8e") ("KU" . "/") ("LU" . "k") ("MU" . "`") ("NU" . "L")
    ("PU" . "W") ("QU" . "/%") ("RU" . "k") ("SU" . "9") ("TU" . "D")
    ("VU" . "~t%") ("WU" . "&") ("XU" . "%") ("YU" . "f") ("ZU" . ":")
    ("BBU" . "CV") ("DDU" . "CE")
    
    ;; Changed per CTC Request (MHD 11/25/96): ("FFU" . "CU%") => ("FFU" . "CU")  
    ("FFU" . "CU")
    
    ("GGU" . "C0")
    ("CHU" . "Ae") ("DHU" . "Ge") ("HHU" . "CU") ("SHU" . "7e")
    ("THU" . "Fe") ("JJU" . "C8e") ("KKU" . "C/") ("LLU" . "Ck")
    ("MMU" . "s`") ("NNU" . "sL") ("PPU" . "CW") ("QQU" . "C/%")
    ("RRU" . "Ck") ("SSU" . "C9") ("TSU" . "D") ("TTU" . "CD")
    ("XTU" . "C") ("VVU" . "C~t%") ("GWU" . "0") ("KWU" . "/")
    ("WWU" . "C&") ("XWU" . "%") ("BYU" . "Se") ("CYU" . "Ae")
    ("DYU" . "Be") ("FYU" . "Ue") ("GYU" . ".e") ("HYU" . "Re")
    ("JYU" . "8e") ("KYU" . "-e") ("LYU" . "je") ("MYU" . "_e")
    ("NYU" . "Ke") ("PYU" . "Te") ("QYU" . "/e") ("RYU" . "je")
    ("SYU" . "7e") ("TYU" . "Ae") ("XYU" . "e") ("YYU" . "Cf")
    ("ZYU" . "8e") ("ZZU" . "C:") ("CCHU" . "CAe") ("TCHU" . "CAe")
    ("DDHU" . "CGe") ("SSHU" . "C7e") ("TTHU" . "CFe") ("TTSU" . "CD")
    ("XTSU" . "C") ("GGWU" . "C0") ("KKWU" . "C/") ("BBYU" . "CSe")
    ("CCYU" . "CAe") ("DDYU" . "CBe") ("FFYU" . "CUe") ("GGYU" . "C.e")
    ("HHYU" . "CRe") ("JJYU" . "C8e") ("KKYU" . "C-e") ("LLYU" . "Cje")
    ("MMYU" . "s_e") ("NNYU" . "sKe") ("PPYU" . "CTe") ("QQYU" . "C/e")
    ("RRYU" . "Cje") ("SSYU" . "C7e") ("TTYU" . "CAe") ("ZZYU" . "C8e")
;   ("M" . "s")
    ("N" . "s")
;   ("M'" . "s")

    ("N'A" . "s\"")				; added
    ("N'I" . "s$")				; added
    ("N'U" . "s&")				; added
    ("N'E" . "s(")				; added
    ("N'O" . "s*")				; added

;   ("M`" . "s")
;   ("N`" . "s")

;   ("WN" . "s")
;   ("XM" . "~s")
;   ("XN" . "~s")
;   ("XWN" . "~s")
;   ("XM'" . "~s")
;   ("XM`" . "~s")
;   ("XN'" . "~s")
;   ("XN`" . "~s")

    ;; (2)	When we type "ci" or "ce" in Kanji or HIragana mode, the editor 
    ;; indicates two characters "c" and 2423 in JIS codes (for "ci"), or "c" and 
    ;; 2428 in JIS codes (for "ce").
    ;; Then, if we type any third character, the first two characters are replaced by 
    ;; 2441 and 2423 in JIS codes (for "ci") or 2441 and 2427 in JIS codes (for "ce").
    ;; 
    ;; In Katakana mode, the same phenomenon occurs (of course, the character codes 
    ;; are different than those in the Kanji/Hiragana modes).
    ;; 
    ;; As a matter of fact, in Japan, there aren't clear agreements for these inputs 
    ;; and each maker follows different standards.
    ;; 
    ;; Anyway, it is desirable that the inputs, "c*" are converted uniquely as follows:
    ;; 
    ;;         input characters    ->    converted character
    ;; 
    ;;                 "ca"        ->        242B (in JIS codes)
    ;;                 "ci"        ->        2437 (in JIS codes)
    ;;                 "cu"        ->        242F (in JIS codes)
    ;;                 "ce"        ->        243B (in JIS codes)
    ;;                 "co"        ->        2433 (in JIS codes)
    ;; 
    ;;                 (These are Microsoft's standards.)
    ;; 
    ;; 
    ;; Thank you for your help.
    ;; 
    ;; Regards,
    ;; Masaru Hidano
    ;; G2 Group / CTC (Japan)
    ;; 
    ;; -- Voila:  (MHD 11/19/96)
    ("CA" . #.(string (code-char #x2b)))
    ("CI" . #.(string (code-char #x37)))
    ("CU" . #.(string (code-char #x2f)))
    ("CE" . #.(string (code-char #x3b)))
    ("CO" . #.(string (code-char #x33)))
    ))

;; Some bad entries found:

;; ("VA" . "~t!")
;; "VA" => (94 84 1) BAD
;; Should be
;; "VA" => (84 1)
;;
;; ("VI" . "~t#")
;; "VI" => (94 84 3) BAD
;; Should be
;; "VA" => (84 3)
;;
;; ("VU" . "~t%")
;; "VU" => (94 84 5) BAD
;; Should be
;; "VU" => (84)  ; corrected to just one character in second email
;;
;; ("VE" . "~t'")
;; "VE" => (94 84 7) BAD
;; Should be
;; "VE" => (84 7)
;;
;; ("VO" . "~t)")
;; "VO" => (94 84 9) BAD
;; Should be
;; "VO" => (84 9)
;;
;; In other words, an illegal ~ slipped in at various points, or the tilde was
;; meant to be interpreted by our software, and we're not doing that.  So I'm
;; removing that tilde. Corrections came from CTC/Itochu, via email from
;; Hirobumi.Fukuoka@sanai.ctc.citoh.co.jp on Mon, 22 Jul 96 13:22:04 JST
;;
;; -- (MHD 11/7/96)
;;
;; UPDATE: My hunch is that every use of tilda is wrong, and that the solution
;; might be to remove it.  So I'm doing this for the following remaining cases:
;; (MHD 11/7/96)
;;
;; "XKA" =>            (94 85) BAD
;; "VVA" =>            (35 94 84 1) BAD
;; "XKE" =>            (94 86) BAD
;; "VVE" =>            (35 94 84 7) BAD
;; "VVI" =>            (35 94 84 3) BAD
;; "VVO" =>            (35 94 84 9) BAD
;; "VVU" =>            (35 94 84 5) BAD

;; Latest spec from Mr. Fukuoka:   (MHD 11/18/96)
;; In Katakana mode:
;; 
;;     "VA" = 2574, 2521        (mapping to 2 character)
;;     "VI" = 2574, 2523        (mapping to 2 character)
;;     "VU" = 2574              (mapping to 1 character)
;;     "VE" = 2574, 2527        (mapping to 2 character)
;;     "VO" = 2574, 2529        (mapping to 2 character)
;;     "XKA" = 2575             (mapping to 1 character)
;;     "VVA" = 2543, 2574, 2521 (mapping to 3 characters)
;;     "XKE" = 2576             (mapping to 1 character)
;;     "VVE" = 2543, 2574, 2527 (mapping to 3 characters)
;;     "VVI" = 2543, 2574, 2523 (mapping to 3 characters)
;;     "VVO" = 2543, 2574, 2529 (mapping to 3 characters)
;;     "VVU" = 2543, 2574       (mapping to 2 characters)
;; 
;; In Kanji and Hiragana mode:
;; 
;;     "VA" = 2574, 2421        (mapping to 2 character)
;;     "VI" = 2574, 2423        (mapping to 2 character)
;;     "VU" = 2574              (mapping to 1 character)        
;;     "VE" = 2574, 2427        (mapping to 2 character)
;;     "VO" = 2574, 2429        (mapping to 2 character)
;;     "XKA" = 2575             (mapping to 1 character) 
;;     "VVA" = 2443, 2574, 2421 (mapping to 3 characters)
;;     "XKE" = 2576             (mapping to 1 character)
;;     "VVE" = 2443, 2574, 2427 (mapping to 3 characters)
;;     "VVI" = 2443, 2574, 2423 (mapping to 3 characters)
;;     "VVO" = 2443, 2574, 2429 (mapping to 3 characters)
;;     "VVU" = 2443, 2574       (mapping to 2 characters)
;;
;; UPDATE: EUREKA!  The ~ means to always use Katakana (high byte = #x25).  So,
;; the ~'s were all right! I'm putting them back.  We just need to interpret
;; them correctly.  In addition, according to Mr. Fukuoka, it appears that the %
;; character following a ~<char> sequence, is to be ignored.  Doing the
;; interpretation in this way accounts for "vu" and "vvu" mapping as 1 and 2
;; characters, respectively, and introduces no other changes in our set.  (Note
;; that this interpretation applies only after ~<char>, not context free.)
;; However, since that is a less clear change, I'm getting clarification from
;; Mr. Fukuoka on this.  (MHD 11/19/96)
;;
;; UPDATE from Mr. Fukuoka:
;; From: "Hiro Fukuoka(=?iso-2022-jp?B?GyRCSiEyLEduSjgbKEo=?=)" 
;; 	<hirobumi.fukuoka@sanai.ctc.citoh.co.jp>
;; Reply-To: hirobumi.fukuoka@sanai.ctc.citoh.co.jp
;; Organization: CTC-G2
;; To: Mark H David <mhd@mailhost>
;; Cc: g2help@ctc.citoh.co.jp
;; Subject: Re: Romanized Input Bugs
;; X-UIDL: 848661102.000
;; 
;; Dear David,
;; 
;; We have reviewed the character mapping in your FAX.
;; 
;; The following two cases need to be corrected:
;; 
;;         Katakana     Hiragana
;;   FFU = 2543,2555    2443,2455   (remove the 3rd character)
;;   YYO = 2543,2568    2443,2468   (replace the 2nd character)
;; 
;; The rest are OK.
;; 
;; Regards,
;; 
;; Hiro Fukuoka
;; CTC, Tokyo, Japan
;;
;; -- I have made the changes per this request.
;;   ("FFU" . "CU%") => ("FFU" . "CU")
;;   ("YYO" . "CH") => ("YYO" . "Ch")



#+development
(defun print-romaji-to-kana-mappings
    (list-of-romajis-or-t-for-all &optional in-jis-euc?)
  (loop with list-of-romajis
	  = (if (eq list-of-romajis-or-t-for-all 't)
		(sort
		  (loop for (key . value) in ascii-and-kana-suffix-pairs
			when (stringp value)
			  collect key)
		  #'string<)
		list-of-romajis-or-t-for-all)
	initially
	  (format t "~%~0TRomaji~12TKatakana~35THiragana~%")
	  (format t "~%~0T------~12T--------~35T--------~%")
	for romaji in list-of-romajis
	as (romaji-string . kana-string)
	   = (assoc romaji ascii-and-kana-suffix-pairs
		    :test #'string-equal)
	do (format t "~%~4t~a ~12t= " romaji-string)
	   (loop for kana-high-byte in '(#x25 #x24)
		 do
	     (when (= kana-high-byte #x24) ; hiragana column
	       (format t "~35T"))
	     (loop with n-chars = (length kana-string)
		   with n-chars-in-mapping-counted = 0
		   with after-switch-once-to-katakana-p = nil
		   with switch-once-to-katakana-p = nil
		   with first-time? = t
		   for i from 0 below n-chars
		   as char = (char kana-string i)
		   do (cond
			((and after-switch-once-to-katakana-p
			      (char= char #\%)))
			((char= char #\~)
			 (setq after-switch-once-to-katakana-p nil)
			 (setq switch-once-to-katakana-p t))
			(t
			 (setq after-switch-once-to-katakana-p nil)
			 (unless (or first-time? in-jis-euc?)
			   (format t ", "))
			 (setq first-time? nil)
			 (incf n-chars-in-mapping-counted)
			 (cond
			   (in-jis-euc?
			    (format t "~c~c"
				    (code-char
				      (+ 128 
					 (if switch-once-to-katakana-p
					     #x25
					     kana-high-byte)))
				    (code-char
				      (+ 128 (char-code char)))))
			   (t
			    (format t "~2,'0x~2,'0x"
				    (if switch-once-to-katakana-p
					#x25
					kana-high-byte)
				    (char-code char))))
			 (when switch-once-to-katakana-p
			   (setq after-switch-once-to-katakana-p t))
			 (setq switch-once-to-katakana-p nil)))))))

#+development
(defun generate-various-reports-on-romaji-for-ctc ()
  (with-open-file (*standard-output* "/home/mhd/dev/jallhex.txt" :direction :output)
    (print-romaji-to-kana-mappings t nil))
  (with-open-file (*standard-output* "/home/mhd/dev/jalleuc.txt" :direction :output)
    (print-romaji-to-kana-mappings t t))
  (with-open-file (*standard-output* "/home/mhd/dev/jfewhex.txt" :direction :output)
    (print-romaji-to-kana-mappings t nil))
  (with-open-file (*standard-output* "/home/mhd/dev/jfeweuc.txt" :direction :output)
    (print-romaji-to-kana-mappings
      (append '("va" "vi" "vu" "ve" "vo" "xka" "vva" "xke" "vve" "vvi" "vvo" "vvu")
	      '("ca" "ci" "cu" "ce" "co"))
      t))
  (with-open-file (*standard-output* "/home/mhd/dev/certain-romaji-euc-for-ctc.text"
				     :direction :output)
    (print-romaji-to-kana-mappings
      (append '("va" "vi" "vu" "ve" "vo" "xka" "vva" "xke" "vve" "vvi" "vvo" "vvu")
	      '("ca" "ci" "cu" "ce" "co"))
      t)))

;; Try '("va" "vi" "vu" "ve" "vo" "xka" "vva" "xke" "vve" "vvi" "vvo" "vvu")
;; Make sure we get Mr. Fukuoka's recommended results; see what they
;; are, above. (MHD 11/19/96)
;;
;; Try the "c*" ones also, per Masaru Hidano's comments, with the
;; following: '("ca" "ci" "cu" "ce" "co")



    





(def-system-variable ascii-to-kana-map KFEP2 nil)
(def-system-variable maximum-length-of-ascii-string KFEP3 0)

(def-system-variable kana-to-ascii-map KFEP2 nil)
(def-system-variable maximum-length-of-kana-string KFEP2 0)

;; The above 4 variables were changed from defvar to def-system-variable. (MHD 11/27/90)

(def-hash-table jis-map
		:size 307 ; use a prime number
		:key-comparitor string=)

(defun-substitution-macro kfep-get-jis-map (key jis-map-hash-table)
  (get-jis-map key jis-map-hash-table))



;;; `Initialize-ascii-kana-converters-if-neccessary' initializes the hash
;;; tables and the parameters for the routines for translating ascii to 
;;; kana.  ascii-to-kana-map holds the mapping for the Lisp implementations
;;; of roman_kana and roman_kata (the roman-to-kana converters). The hash
;;; table kana-to-ascii-map is intended for future work in reimplementing
;;; the kana-to-ascii converter, convert-to-ascii-roman-if-possible.

(defun initialize-ascii-kana-converters-if-neccessary ()
  (when (or (null ascii-to-kana-map)
	    (null kana-to-ascii-map)
	    #+development initialize-kfep-regardless?)
    (let* ((new-ascii-to-kana-map (make-jis-map))
	   (new-kana-to-ascii-map (make-jis-map)))
      (loop for ascii-kana-pair in ascii-and-kana-suffix-pairs
	    as ascii-string = (car ascii-kana-pair)
	    as kana-string-or-translation-marker = (cdr ascii-kana-pair)
	    do
	(when (>f (length ascii-string) maximum-length-of-ascii-string)
	      (setq maximum-length-of-ascii-string
		    (length ascii-string)))
	(when (gensym-string-p kana-string-or-translation-marker)
	  (when (>f (length kana-string-or-translation-marker)
		    maximum-length-of-kana-string)
	    (setq maximum-length-of-kana-string
		  (length kana-string-or-translation-marker)))
	  (setf (get-jis-map kana-string-or-translation-marker
			     new-kana-to-ascii-map)
		ascii-string))
	(setf (get-jis-map ascii-string new-ascii-to-kana-map)
	      kana-string-or-translation-marker))
      (setq ascii-to-kana-map new-ascii-to-kana-map)
      (setq kana-to-ascii-map new-kana-to-ascii-map))))




;;; `Map-longest-possible-substring-using-jis-map' maps the longest possible
;;; substring of the given string to the target string given by the jis-map
;;; hash table.  If there is a mapping, the first value returned is the mapped
;;; string and the second is the length of the substring.  If there is no
;;; mapping, nil is returned.
;;;
;;; Any returned strings from this function should NOT be reclaimed.
;;;
;;; All alphabetic characters in the input string must be in upper case.

;; The second value returned, if non-nil, also corresponds to the index of
;; the next byte to be considered in the input string.

(defun map-longest-possible-substring-using-jis-map
       (string jis-map start-index end-index
	maximum-length-of-substring-to-consider)
  #+development
  (gensym-assert (<=f 0 start-index))
  #+development
  (gensym-assert (<=f end-index (length string)))
  (let* ((mapped-string-to-return? nil)
	 (length-of-substring-to-return? nil))
    (loop with substring
	  with mapped-string?
	  with maximum-index-in-string = (minf (length string) end-index)
	  for length-of-substring
	      from (+f maximum-length-of-substring-to-consider start-index)
	      downto 1
	  as end-index-for-substring = (+f start-index length-of-substring)
	  do
      (when (<=f end-index-for-substring maximum-index-in-string)
	(progn
	  (setq substring (lisp-string-substring
			    string start-index end-index-for-substring))
	  (setq mapped-string? (kfep-get-jis-map substring jis-map))
	  (reclaim-lisp-string substring))
	(when mapped-string?
	  (setq mapped-string-to-return? mapped-string?
		length-of-substring-to-return? length-of-substring)
	  (return nil)))
	  finally
	    (return nil))
    (values mapped-string-to-return? length-of-substring-to-return?)))








;/** Ascii to JIS code table with special case **/
(def-kfep-constant ascii-to-jis-code-map    
    '#(
       ""    ""    ""    ""    ""    ""    ""    ""
       ""    ""    ""    ""    ""    ""    ""    ""
       ""    ""    ""    ""    ""    ""    ""    ""
       ""    ""    ""    ""    ""    ""    ""    ""
       "!!"  "!*"  "!m"  "!t"  "!p"  "!s"  "!u"  "!l"	;/*   ! " # $ % & ' ***/
       "!J"  "!K"  "\"(" "!&"  "!$"  "!<"  "!#"  "!?"	;/* ( ) * + - . / ***/
       "#0"  "#1"  "#2"  "#3"  "#4"  "#5"  "#6"  "#7"	;/* 0 1 2 3 4 5 6 7 ***/
       "#8"  "#9"  "!'"  "!\"" "!c"  "\"/" "!d"  "!)"	;/* 8 9 : ; < = > ? ***/
       "!}"  "#A"  "#B"  "#C"  "#D"  "#E"  "#F"  "#G"	;/* @ A B C D E F G ***/
       "#H"  "#I"  "#J"  "#K"  "#L"  "#M"  "#N"  "#O"	;/* H I J K L M N O ***/
       "#P"  "#Q"  "#R"  "#S"  "#T"  "#U"  "#V"  "#W"	;/* P Q R S T U V W ***/
       "#X"  "#Y"  "#Z"  "!V"  "!@"  "!W"  "!0"  "!2"	;/* X Y Z [ \ ] ^ _ ***/
       "!F"  "#a"  "#b"  "#c"  "#d"  "#e"  "#f"  "#g"	;/* ` a b c d e f g ***/
       "#h"  "#i"  "#j"  "#k"  "#l"  "#m"  "#n"  "#o"	;/* h i j k l m n o ***/
       "#p"  "#q"  "#r"  "#s"  "#t"  "#u"  "#v"  "#w"	;/* p q r s t u v w ***/
       "#x"  "#y"  "#z"  "!P"  "!C"  "!Q"  "!A"  ""	;/* x y z { | } ~   ***/
       ))

(defun-substitution-macro map-ascii-character-to-jis-code (ascii-character)
  (svref ascii-to-jis-code-map
	(convert-simple-character-to-ascii ascii-character)))




;;; `Convert-ascii-to-kana-in-lisp-string' converts the ascii string
;;; to either hiragana or katakana JIS codes.  It returns the number of
;;; bytes written to the kana-buffer.  -1 is returned if the output
;;; kana buffer is not big enough for the converted jis string.

#+development
(defun tak (ascii kana &optional (hiragana? t))
  (convert-ascii-to-kana-in-lisp-string
    ascii (length ascii) kana (length kana) hiragana?))

(defun convert-ascii-to-kana-in-lisp-string
       (case-insensitive-ascii-buffer
	number-of-bytes-in-ascii-buffer
	kana-buffer size-of-kana-buffer-in-bytes
	convert-to-hiragana-p)
  (let* ((ascii-buffer
	   (copy-lisp-string-with-change-to-upper-case
	     case-insensitive-ascii-buffer))
	 (ascii-buffer-index 0)
	 (kana-buffer-index 0)
	 (kana-high-byte-character
	   (if convert-to-hiragana-p
	       (code-char #x24)
	       (code-char #x25))))
    (loop while (and (<f ascii-buffer-index number-of-bytes-in-ascii-buffer)
		     (<f kana-buffer-index size-of-kana-buffer-in-bytes))
	  do
      (multiple-value-bind (translation? ascii-buffer-index-increment?)
	  (map-longest-possible-substring-using-jis-map
	    ascii-buffer ascii-to-kana-map
	    ascii-buffer-index
	    number-of-bytes-in-ascii-buffer
	    maximum-length-of-ascii-string)
	;(format t "~& ~s[~a] -> ~s ... " ascii-buffer ascii-buffer-index translation?)
	(cond
	  ((gensym-string-p translation?)
	   ;(format t "is a string")
	   (loop with switch-once-to-katakana-p = nil
		 with after-switch-once-to-katakana-p = nil
		 for index from 0 below (length translation?)
		 as character = (char translation? index)
		 do
	     (cond
	       ((and after-switch-once-to-katakana-p
		     (char= character #\%)))
	       ((char= character #\~)	; see "UPDATE: EUREKA!" note
					;   above (MHD 11/19/96)
		(setq after-switch-once-to-katakana-p nil)
		(setq switch-once-to-katakana-p t))
	       (t
		(setq after-switch-once-to-katakana-p nil)
		(setf (char kana-buffer kana-buffer-index)
		      (if switch-once-to-katakana-p
			  #.(code-char #x25) ; katakana high byte
			  kana-high-byte-character))
		(when switch-once-to-katakana-p
		  (setq after-switch-once-to-katakana-p t))
		(setq switch-once-to-katakana-p nil)
		(incff kana-buffer-index)
		(if (<f kana-buffer-index size-of-kana-buffer-in-bytes)
		    (setf (char kana-buffer kana-buffer-index)
			  (char translation? index)))
		(incff kana-buffer-index))))
	   (incff ascii-buffer-index ascii-buffer-index-increment?)
	   ;(format t " ... New index is ~s[~a]" ascii-buffer ascii-buffer-index)
	   )
	  ((equal translation? 'ascii)
	   ;(format t "is ascii")
	   (loop for index from ascii-buffer-index
			   below (+f ascii-buffer-index
				     ascii-buffer-index-increment?)
		 do
	     (setf (char kana-buffer kana-buffer-index)
		   #.(code-char #x23))
	     (incff kana-buffer-index)
	     (if (<f kana-buffer-index size-of-kana-buffer-in-bytes)
		 (setf (char kana-buffer kana-buffer-index)
		       (char case-insensitive-ascii-buffer index)))
	     (incff kana-buffer-index))
	   (incff ascii-buffer-index ascii-buffer-index-increment?))
	  (t
	    ;(format t "is raw")
	   (setq translation?
		 (map-ascii-character-to-jis-code
		   (char case-insensitive-ascii-buffer
			 ascii-buffer-index)))
	   (incff ascii-buffer-index)
	   (setf (char kana-buffer kana-buffer-index)
		 (char translation? 0))
	   (incff kana-buffer-index)
	   (if (<f kana-buffer-index size-of-kana-buffer-in-bytes)
	       (setf (char kana-buffer kana-buffer-index)
		     (char translation? 1)))
	   (incff kana-buffer-index)))))
    (reclaim-lisp-string ascii-buffer)
    (loop with string-is-simple? = nil
	  for jis-index from 0 below (halff kana-buffer-index)
	  as jis-code = (jis-gchar kana-buffer jis-index string-is-simple?)
	  do (when (or (=f jis-code #x234E)	; N
		       (=f jis-code #x236E))	; n
	       (let* ((byte-index (twicef jis-index)))
		 (setf (char kana-buffer byte-index)
		       kana-high-byte-character)
		 (setf (char kana-buffer (+f byte-index 1))
		       #.(code-char #x0073)))))
;    (format t "~&~s, ~s" kana-buffer kana-buffer-index)
    (if (and (<f ascii-buffer-index number-of-bytes-in-ascii-buffer)
	     (>=f kana-buffer-index size-of-kana-buffer-in-bytes))
	-1
	kana-buffer-index)))







;;; `Copy-jis-string-stripping-high-byte' returns a lisp string which
;;; contains only all the odd index bytes (0 based) from the input
;;; JIS string.

;; The following is not being use, but might prove useful later.  -pto 09sep90

;(defun-substitution-macro copy-jis-string-stripping-high-byte
;			  (jis-string number-of-jis-bytes)
;  (loop with number-of-output-bytes = (halff number-of-jis-bytes)
;	with stripped-kana-buffer = (obtain-lisp-string number-of-output-bytes)
;	for index from 0 below number-of-output-bytes
;	as character = (char jis-string (+f (twicef index) 1))
;	do
;    (setf (char stripped-kana-buffer index) character)
;	finally
;	  (return stripped-kana-buffer)))


;;; `Convert-stripped-kana-to-ascii-in-lisp-string' converts a kana string
;;; with the high byte of all its characters stripped.  It returns the number
;;; of ASCII characters in the output buffer.

;; The following is not being use, but might prove useful later.  -pto 09sep90

;(defun convert-stripped-kana-to-ascii-in-lisp-string
;       (stripped-kana-buffer
;	number-of-bytes-in-stripped-kana-buffer
;	ascii-buffer size-of-ascii-buffer-in-bytes)
;  (let* ((stripped-kana-buffer-index 0)
;	 (ascii-buffer-index 0))
;    (loop while (and (<f stripped-kana-buffer-index
;			 number-of-bytes-in-stripped-kana-buffer)
;		     (<f ascii-buffer-index size-of-ascii-buffer-in-bytes))
;	  do
;      (multiple-value-bind (translation? stripped-kana-buffer-index-increment?)
;	  (map-longest-possible-substring-using-jis-map
;	    stripped-kana-buffer kana-to-ascii-map
;	    stripped-kana-buffer-index
;	    number-of-bytes-in-stripped-kana-buffer
;	    maximum-length-of-kana-string)
;	(cond
;	  ((gensym-string-p translation?)
;	   ;(format t "is a string")
;	   (loop for index from 0 below (length translation?)
;		 do
;	     (setf (char ascii-buffer ascii-buffer-index)
;		   (char translation? index))
;	     (incff ascii-buffer-index))
;	   (incff stripped-kana-buffer-index
;		  stripped-kana-buffer-index-increment?))
;	  (t
;	    ;(format t "is raw")
;	   (incff stripped-kana-buffer-index)))))
;    ascii-buffer-index))

;(defun convert-kana-to-ascii-in-lisp-string
;       (jis-buffer
;	number-of-bytes-in-jis-buffer
;	ascii-buffer size-of-ascii-buffer-in-bytes)
;  (let* ((stripped-kana-buffer
;	   (copy-jis-string-stripping-high-byte
;	     jis-buffer number-of-bytes-in-jis-buffer))
;	 (number-of-bytes-in-stripped-kana-buffer
;	   (halff number-of-bytes-in-jis-buffer)))
;    (prog1
;      (convert-stripped-kana-to-ascii-in-lisp-string
;	stripped-kana-buffer
;	number-of-bytes-in-stripped-kana-buffer
;	ascii-buffer size-of-ascii-buffer-in-bytes)
;      (reclaim-lisp-string stripped-kana-buffer))))



;(defmacro symbolization_g2 (ascii leng symbol nch_value last-value-p)
;  `(progn ,ascii ,leng ,symbol ,nch_value ,last-value-p -1))

;; Dummy function!

;; See c function symbolization_g2.

;; When laster-value-p equals:
;;   0 -> symbolization() is called.
;;   otherwise -> the last value of nch is returned





(def-system-variable last-roman_kana_g2-length KFEP2 0)

(defun roman_kana_g2 (roman-ascii-buffer length-of-ascii-buffer
		      kana-buffer number-of-bytes-in-kana-buffer
		      last-value-p)
  (if (=f last-value-p 0)
      (let* ((result
	       (convert-ascii-to-kana-in-lisp-string
		 roman-ascii-buffer length-of-ascii-buffer
		 kana-buffer number-of-bytes-in-kana-buffer t)))
	(if (<f result 0)
	    result
	    (setq last-roman_kana_g2-length result)))
      last-roman_kana_g2-length))

;; When last-value-p equals:
;;   0 -> roman_kana() is called.
;;   otherwise -> the last value of nch is returned




(def-system-variable last-roman_kata_g2-length KFEP2 0)

(defun roman_kata_g2 (roman-ascii-buffer length-of-ascii-buffer
		      kata-buffer number-of-bytes-in-kata-buffer
		      last-value-p)
  (if (=f last-value-p 0)
      (let* ((result
	       (convert-ascii-to-kana-in-lisp-string
		 roman-ascii-buffer length-of-ascii-buffer
		 kata-buffer number-of-bytes-in-kata-buffer nil)))
	(if (<f result 0)
	    result
	    (setq last-roman_kata_g2-length result)))
      last-roman_kata_g2-length))

;; When laster-value-p equals:
;;   0 -> roman_kana() is called.
;;   otherwise -> the last value of nch is returned










;;; kkakojin.c

(defmacro kka_koinit ()
  `(kfep-kka-koinit))





(defmacro kka_kodone ()
  `(kfep-kka-kodone))






;; ... more stuff here ... 






;; From kkasystm.c

(defmacro kka_mainit (sw index-filename hyoki-filename kojin-filename)  
  `(kfep-kka-mainit ,sw ,index-filename ,hyoki-filename ,kojin-filename))





;; ... more stuff here ... 



(defmacro kka_madone ()
  `(kfep-kka-madone))



;; ... more stuff here ... 






;;; kkamiscs.c


;; ... more stuff here ...













;;;; Initialization and Conversion Routines



;;; The following functions are interface to KFEP C routines.  They are called from
;;; modules EDIT and RUN.



;;; For all the functions below, the string argument (1) may include ascii roman,
;;; Kanji roman, hiragana, and katakana characters, and (2) must not be empty






;;; `Initialize-for-asian-languages' should be called once when a G2 process is
;;; launched, after loading the OK file.  G2 streams must be ready to work when
;;; this function is called.

(def-system-variable kfep-converters-have-been-initialized? KFEP2 nil)




;;; `Initialize-for-asian-languages' ... 

(defun initialize-for-asian-languages ()

  ;; Japanese
  (when t ; (japanese-authorized-p)
    ;; Japanese font loading:
    ;; (initialize-japanese-fonts)     ; no longer (MHD 1/19/95)
    (setq hfep-capability? t)
    ;; Japanese KFEP Dictionary Initializations:
    ;; (initialize-kana-to-kanji-converters)  ; no longer done here -- done
    ;;                                        ;   if/when needed for editing
    (setq kfep-capability? t))		      ; <-- this repaces above
					      ;   (MHD 1/20/95)

  ;; Korean
  (when t ; (korean-authorized-p)  ; outline font (hangul.ttf) has to authorized
				   ;   but HFEP and bitmap fonts are standard.
    ;; Korean font loading: note: we've brought back preloading in the Korean
    ;; font case because we have one monolithic font that's too huge to be
    ;; loaded in a reasonable amount of time on the fly. (MHD 3/19/98)
    (when (korean-authorized-p)
      (load-korean-outline-font))

    ;; (Obsolete) Korean font loading:
    ;; (initialize-korean-fonts)

    ;; Korean HFEP enabling:
    (setq hfep-capability? t))

  ;; Chinese  (MHD 4/9/99)
  (when (chinese-authorized-p)
    ;; Chinese font loading: note: we've brought back preloading in the Chinese
    ;; font case because we have one monolithic font that's too huge to be
    ;; loaded in a reasonable amount of time on the fly. (MHD 4/9/99)
    (when (chinese-authorized-p)
      (load-chinese-outline-font))))


(defun-allowing-unwind load-korean-outline-font ()
  (do-long-operation-with-notification
      ((tformat-text-string "Initializing Korean outline font ...") nil)
    (load-hangul-font)))

;; This is only to be called from service-workstations. 

;; This was previously named initialize-kfep-converters. (MHD 10/3/94)

(defun-allowing-unwind load-chinese-outline-font ()
  (do-long-operation-with-notification
      ((tformat-text-string "Initializing Chinese outline font ...") nil)
    (load-chinese-font)))

;; New! (MHD 4/9/99)


;;; --- OBSOLETE ---
;;; `Initialize-japanese-fonts' ...
;;; 
;;; `Initialize-korean-fonts' ...
;;;
;;; `Initialize-asian-fonts'

#+font-files
(defun initialize-japanese-fonts ()
  (initialize-asian-fonts "Kanji" '(kanji16 kanji24)))

#+font-files
(defun initialize-korean-fonts ()
  (initialize-asian-fonts "Hangul" '(hangul16 hangul24)))

#+font-files
(defun-allowing-unwind initialize-asian-fonts (script-name font-names)
  (do-long-operation-with-notification
      ((tformat-text-string "Initializing ~a Fonts ... " script-name)
       t)
    (loop for font-name in font-names
	  do (force-process-drawing)	; throw in some refreshes before/after
	     (read-asian-font-file font-name t)
	     (force-process-drawing))))



;;; `Initialize-kana-to-kanji-converters' performs initializations needed for
;;; using the KFEP (Kana-to-kanji Front-End Processor) from the editor.  It must
;;; only be called when (japanese-authorized-p) is true.

(defun-allowing-unwind initialize-kana-to-kanji-converters ()
  (when (not kfep-converters-have-been-initialized?)
    (initialize-ascii-kana-converters-if-neccessary)	; move this guy?!
    (protected-let*
	((kfep-index-filename-in-file-system (get-kfep-index-filename))
	 (kfep-main-filename-in-file-system (get-kfep-main-filename))
	 (kfep-kojin-filename-in-file-system (get-kfep-kojin-filename))
	 (kfep-index-filename-for-user
	   (import-text-string
	     kfep-index-filename-in-file-system
	     'KFEP-FILENAME)
	   (reclaim-text-string kfep-index-filename-for-user))
	 (kfep-main-filename-for-user
	   (import-text-string
	     kfep-main-filename-in-file-system
	     'KFEP-FILENAME)
	   (reclaim-text-string kfep-main-filename-for-user))
	 (kfep-kojin-filename-for-user
	   (import-text-string
	     kfep-kojin-filename-in-file-system
	     'KFEP-FILENAME)
	   (reclaim-text-string kfep-kojin-filename-for-user)))
      (do-long-operation-with-notification
	  ((tformat-text-string
	     "Initializing KFEP dictionaries from ~s, ~s, and ~s."
	     kfep-index-filename-for-user
	     kfep-main-filename-for-user
	     kfep-kojin-filename-for-user))
	(force-process-drawing)
	(cond
	  ((and (g2-stream-probe-file-for-read kfep-index-filename-in-file-system)
		(not (g2-stream-directory-p kfep-index-filename-in-file-system))
		(g2-stream-probe-file-for-read kfep-main-filename-in-file-system)
		(not (g2-stream-directory-p kfep-main-filename-in-file-system))
		(g2-stream-probe-file-for-read kfep-kojin-filename-in-file-system)
		(not (g2-stream-directory-p kfep-kojin-filename-in-file-system))
		(kka_mainit
		  0
		  kfep-index-filename-in-file-system 
		  kfep-main-filename-in-file-system
		  kfep-kojin-filename-in-file-system)
		(progn
		  (force-process-drawing)
		  (kka_koinit)))  ; initialize personal dictionary
	   (force-process-drawing)
	   (setq kfep-converters-have-been-initialized? t)
	   (setq kfep-capability? t)
	   (notify-user
	     "The KFEP dictionaries have been initialized from ~s, ~s, and ~s."
	     kfep-index-filename-for-user
	     kfep-main-filename-for-user
	     kfep-kojin-filename-for-user))
	  (t (notify-user				; improve wording?!
	       "Some of the KFEP dictionary files ~s, ~s, or ~s could not be accessed."
	       kfep-index-filename-for-user
	       kfep-main-filename-for-user
	       kfep-kojin-filename-for-user)))
	(force-process-drawing)))))




;;; `Get-kfep-filename-of-type' is a macro that gets a filename string (an ascii
;;; string) for the specified "type", where type can be one of following
;;; symbols: MAIN, INDEX, KOJIN.  Type is unevaluated.
;;; 
;;; This consults keyword arguments and environment variables as appropriate.
;;; 
;;; As a side effect, this sets the global corresponding to the specified type
;;; to its result.  This also returns that value.
;;;
;;; There is no need to reclaim the results of this at this time, since this
;;; should only be called one time per process at present.

(defmacro get-kfep-filename-of-type (type)
  `(let ((filename-variable
	   ',(intern-text-string
	       (tformat-text-string
		 "SPECIFIED-KFEP-~A-FILENAME?"
		 type))))
     (set filename-variable
	  (or (symbol-value filename-variable)
	      (get-command-line-keyword-argument
		,(tformat-text-string "kfep~(~a~)" type))
	      (make-absolute-pathname-if-possible
		(symbol-value
		  ',(intern-text-string
		      (tformat-text-string
			"KFEP-~a-FILENAME"
			type))))))))

(defun get-kfep-index-filename ()
  (get-kfep-filename-of-type index))

(defun get-kfep-main-filename ()
  (get-kfep-filename-of-type main))

(defun get-kfep-kojin-filename ()
  (get-kfep-filename-of-type kojin))
  



;; To do: 

;; 1 - don't reload Kanji Fonts if they are already loaded, since they're
;; global, and some other process might even be using them.
;; -- UPDATE: Done now for free by read-asian-font-file. (MHD 11/16/92)

;; 2 - only create the lispm virtual random access file once, or at least only
;; while there are users -- keep reference counts?

;; 3 - recover if the user gives the wrong location for the kfep files somehow,
;; perhaps by putting a UI on selecting them if they're missing upon boot

;; 4 - recover if the connection to the random access file is lost for some
;; reason, perhaps a disk being turned off or an nfs link going down due to a
;; network shutdown.

;; (MHD 11/7/91)


;; NOTES:
;;
;; 1. kka_updatekojin is used to update personal information after translation
;; (i.e. after kka_batkanakan_g2 has been called until the choice is taken.
;;
;; 2. kka_kodone is called to record information into the personal dictionary
;; and close the dictionary.  (Opposite of kka_koinit.)
;;
;; 3. kka_madone is called to release the memory of the system dictionary.


;; The above was updated for 3.0 today to load the Kanji16 font from inside
;; the process.  It used to be loaded at system image building time for Japanese
;; images, but now there is just one image.  Note that the Kanji16 Font might
;; not need to be loaded if this is a G2 without a local window, which could
;; save a good bit of space.  (MHD 4/11/91) ---
;; --- I added the loading of Kanji24 today. -mhd



; ;;; `Convert-to-roman-if-possible' returns either a new text string representing 
; ;;; the roman equivalent of string, or nil if there is no such equivalent.
;
; (defun convert-to-roman-if-possible (string)
;   ;; For test purposes, this converts by changing to lower case.
;  (copy-text-string-with-case-conversion string nil)
; ;  (convert-to-ascii-roman-if-possible string nil)
;   )
;
; ;; Consider having this return nil when the result would be identical to string.







;;;; CONVERTER (Gensym-Text-to-JIS)



;;; `Convert-to-jis-string-if-possible' returns either a new jis string 
;;; containing the jis equivalent of string together with a second value that
;;; specifies the actual number of bytes of the jis string used (precisely the
;;; number of gensym characters in string), or else nil if there is no such
;;; equivalent.  There is no such equivalent if string contains characters
;;; other than kanji characters and simple roman alphabetic characters.

;; Used in EDIT.LISP and KFEP.LISP
(defun convert-to-jis-string-if-possible (string)
  (loop with string-length = (text-string-length string)
	with string-index fixnum = 0
	with jis-string
	  = (obtain-jis-string (twicef string-length))	; in the worst case
	with jis-string-is-simple? = nil
	with jis-string-index fixnum = 0
	with wide-character
	with jis-code?
	when (>=f string-index string-length)
	  return
	    (values jis-string (twicef jis-string-index))
	do (setq wide-character
		 (read-character-from-text-string string string-index))
           (setq jis-code? (map-unicode-to-JIS-X-0208 (wide-character-code wide-character)))
	   (cond
	     (jis-code?
	      (setf (jis-gchar jis-string jis-string-index jis-string-is-simple?)
		    jis-code?))
	     ((alpha-char-pw wide-character)	; if true, here, assumed character is ASCII range
	      (setf (jis-gchar jis-string jis-string-index jis-string-is-simple?)
		    (+f (-f #x2341		; JIS "A"
			    #.(wide-character-code #.%\A))	; ASCII "A"
			(wide-character-code wide-character))))
	     ((digit-char-pw wide-character)	; ditto. (ASCII)
	      (setf (jis-gchar jis-string jis-string-index jis-string-is-simple?)
		    (+f (-f #x2330		; JIS "0"
			    #.(wide-character-code #.%\0))	; ASCII "0"
			(wide-character-code wide-character))))
	     ((char<w #.(coerce-to-wide-character 31) ; 0-31 no translation
		      wide-character
		      #.(coerce-to-wide-character 127))	; 127 no translation
	      (setf (jis-gchar jis-string jis-string-index jis-string-is-simple?)
		    (jis-char
		      (svref ascii-to-jis-code-map
			     (wide-character-code wide-character))
		      0)))
	     (t (loop-finish)))
	   (incff jis-string-index)
	finally
	  (reclaim-jis-string jis-string)
	  (return nil)))

;; Consider including the following clauses in the cond above:
;; 
;;           ((eql character #\,)
;;            (setf (jis-gchar jis-string jis-string-index jis-string-is-simple?)
;;                  #x2124))
;;           ((eql character #\.)
;;            (setf (jis-gchar jis-string jis-string-index jis-string-is-simple?)
;;                  #x2125))
;;           ((eql character #\-)
;;            (setf (jis-gchar jis-string jis-string-index jis-string-is-simple?)
;;                  #x213C))
;;           ((eql character #\")
;;            (setf (jis-gchar jis-string jis-string-index jis-string-is-simple?)
;;                  #x216D))
;;           ((eql character #\')
;;            (setf (jis-gchar jis-string jis-string-index jis-string-is-simple?)
;;                  #x216C))
;;
;; (MHD 1/3/91)







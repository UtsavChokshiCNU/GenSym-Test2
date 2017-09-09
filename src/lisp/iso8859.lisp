;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module ISO8859

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark David



;;;; ISO 8859 String Conversion





(defmacro create-8859-map (&rest mappings)
  (let ((map (make-wide-string
	       8859-part-size
	       :initial-element unicode-replacement-character)))
    (loop for (8859-code unicode) on mappings by #'cddr
	  do (setf (charw map (logandf 8859-code 8859-code-mask))
		   (code-wide-character unicode)))
    `(optimize-constant ',map)))

(defparameter 8859-2-unicode-map
  (create-8859-map
    #xA0	#x00A0	;	NO-BREAK SPACE
    #xA1	#x0104	;	LATIN CAPITAL LETTER A WITH OGONEK
    #xA2	#x02D8	;	BREVE
    #xA3	#x0141	;	LATIN CAPITAL LETTER L WITH STROKE
    #xA4	#x00A4	;	CURRENCY SIGN
    #xA5	#x013D	;	LATIN CAPITAL LETTER L WITH CARON
    #xA6	#x015A	;	LATIN CAPITAL LETTER S WITH ACUTE
    #xA7	#x00A7	;	SECTION SIGN
    #xA8	#x00A8	;	DIAERESIS
    #xA9	#x0160	;	LATIN CAPITAL LETTER S WITH CARON
    #xAA	#x015E	;	LATIN CAPITAL LETTER S WITH CEDILLA
    #xAB	#x0164	;	LATIN CAPITAL LETTER T WITH CARON
    #xAC	#x0179	;	LATIN CAPITAL LETTER Z WITH ACUTE
    #xAD	#x00AD	;	SOFT HYPHEN
    #xAE	#x017D	;	LATIN CAPITAL LETTER Z WITH CARON
    #xAF	#x017B	;	LATIN CAPITAL LETTER Z WITH DOT ABOVE
    #xB0	#x00B0	;	DEGREE SIGN
    #xB1	#x0105	;	LATIN SMALL LETTER A WITH OGONEK
    #xB2	#x02DB	;	OGONEK
    #xB3	#x0142	;	LATIN SMALL LETTER L WITH STROKE
    #xB4	#x00B4	;	ACUTE ACCENT
    #xB5	#x013E	;	LATIN SMALL LETTER L WITH CARON
    #xB6	#x015B	;	LATIN SMALL LETTER S WITH ACUTE
    #xB7	#x02C7	;	CARON
    #xB8	#x00B8	;	CEDILLA
    #xB9	#x0161	;	LATIN SMALL LETTER S WITH CARON
    #xBA	#x015F	;	LATIN SMALL LETTER S WITH CEDILLA
    #xBB	#x0165	;	LATIN SMALL LETTER T WITH CARON
    #xBC	#x017A	;	LATIN SMALL LETTER Z WITH ACUTE
    #xBD	#x02DD	;	DOUBLE ACUTE ACCENT
    #xBE	#x017E	;	LATIN SMALL LETTER Z WITH CARON
    #xBF	#x017C	;	LATIN SMALL LETTER Z WITH DOT ABOVE
    #xC0	#x0154	;	LATIN CAPITAL LETTER R WITH ACUTE
    #xC1	#x00C1	;	LATIN CAPITAL LETTER A WITH ACUTE
    #xC2	#x00C2	;	LATIN CAPITAL LETTER A WITH CIRCUMFLEX
    #xC3	#x0102	;	LATIN CAPITAL LETTER A WITH BREVE
    #xC4	#x00C4	;	LATIN CAPITAL LETTER A WITH DIAERESIS
    #xC5	#x0139	;	LATIN CAPITAL LETTER L WITH ACUTE
    #xC6	#x0106	;	LATIN CAPITAL LETTER C WITH ACUTE
    #xC7	#x00C7	;	LATIN CAPITAL LETTER C WITH CEDILLA
    #xC8	#x010C	;	LATIN CAPITAL LETTER C WITH CARON
    #xC9	#x00C9	;	LATIN CAPITAL LETTER E WITH ACUTE
    #xCA	#x0118	;	LATIN CAPITAL LETTER E WITH OGONEK
    #xCB	#x00CB	;	LATIN CAPITAL LETTER E WITH DIAERESIS
    #xCC	#x011A	;	LATIN CAPITAL LETTER E WITH CARON
    #xCD	#x00CD	;	LATIN CAPITAL LETTER I WITH ACUTE
    #xCE	#x00CE	;	LATIN CAPITAL LETTER I WITH CIRCUMFLEX
    #xCF	#x010E	;	LATIN CAPITAL LETTER D WITH CARON
    #xD0	#x0110	;	LATIN CAPITAL LETTER D WITH STROKE
    #xD1	#x0143	;	LATIN CAPITAL LETTER N WITH ACUTE
    #xD2	#x0147	;	LATIN CAPITAL LETTER N WITH CARON
    #xD3	#x00D3	;	LATIN CAPITAL LETTER O WITH ACUTE
    #xD4	#x00D4	;	LATIN CAPITAL LETTER O WITH CIRCUMFLEX
    #xD5	#x0150	;	LATIN CAPITAL LETTER O WITH DOUBLE ACUTE
    #xD6	#x00D6	;	LATIN CAPITAL LETTER O WITH DIAERESIS
    #xD7	#x00D7	;	MULTIPLICATION SIGN
    #xD8	#x0158	;	LATIN CAPITAL LETTER R WITH CARON
    #xD9	#x016E	;	LATIN CAPITAL LETTER U WITH RING ABOVE
    #xDA	#x00DA	;	LATIN CAPITAL LETTER U WITH ACUTE
    #xDB	#x0170	;	LATIN CAPITAL LETTER U WITH DOUBLE ACUTE
    #xDC	#x00DC	;	LATIN CAPITAL LETTER U WITH DIAERESIS
    #xDD	#x00DD	;	LATIN CAPITAL LETTER Y WITH ACUTE
    #xDE	#x0162	;	LATIN CAPITAL LETTER T WITH CEDILLA
    #xDF	#x00DF	;	LATIN SMALL LETTER SHARP S
    #xE0	#x0155	;	LATIN SMALL LETTER R WITH ACUTE
    #xE1	#x00E1	;	LATIN SMALL LETTER A WITH ACUTE
    #xE2	#x00E2	;	LATIN SMALL LETTER A WITH CIRCUMFLEX
    #xE3	#x0103	;	LATIN SMALL LETTER A WITH BREVE
    #xE4	#x00E4	;	LATIN SMALL LETTER A WITH DIAERESIS
    #xE5	#x013A	;	LATIN SMALL LETTER L WITH ACUTE
    #xE6	#x0107	;	LATIN SMALL LETTER C WITH ACUTE
    #xE7	#x00E7	;	LATIN SMALL LETTER C WITH CEDILLA
    #xE8	#x010D	;	LATIN SMALL LETTER C WITH CARON
    #xE9	#x00E9	;	LATIN SMALL LETTER E WITH ACUTE
    #xEA	#x0119	;	LATIN SMALL LETTER E WITH OGONEK
    #xEB	#x00EB	;	LATIN SMALL LETTER E WITH DIAERESIS
    #xEC	#x011B	;	LATIN SMALL LETTER E WITH CARON
    #xED	#x00ED	;	LATIN SMALL LETTER I WITH ACUTE
    #xEE	#x00EE	;	LATIN SMALL LETTER I WITH CIRCUMFLEX
    #xEF	#x010F	;	LATIN SMALL LETTER D WITH CARON
    #xF0	#x0111	;	LATIN SMALL LETTER D WITH STROKE
    #xF1	#x0144	;	LATIN SMALL LETTER N WITH ACUTE
    #xF2	#x0148	;	LATIN SMALL LETTER N WITH CARON
    #xF3	#x00F3	;	LATIN SMALL LETTER O WITH ACUTE
    #xF4	#x00F4	;	LATIN SMALL LETTER O WITH CIRCUMFLEX
    #xF5	#x0151	;	LATIN SMALL LETTER O WITH DOUBLE ACUTE
    #xF6	#x00F6	;	LATIN SMALL LETTER O WITH DIAERESIS
    #xF7	#x00F7	;	DIVISION SIGN
    #xF8	#x0159	;	LATIN SMALL LETTER R WITH CARON
    #xF9	#x016F	;	LATIN SMALL LETTER U WITH RING ABOVE
    #xFA	#x00FA	;	LATIN SMALL LETTER U WITH ACUTE
    #xFB	#x0171	;	LATIN SMALL LETTER U WITH DOUBLE ACUTE
    #xFC	#x00FC	;	LATIN SMALL LETTER U WITH DIAERESIS
    #xFD	#x00FD	;	LATIN SMALL LETTER Y WITH ACUTE
    #xFE	#x0163	;	LATIN SMALL LETTER T WITH CEDILLA
    #xFF	#x02D9	;	DOT ABOVE
    ))

(defparameter 8859-3-unicode-map
  (create-8859-map
    #xA0	#x00A0	;	NO-BREAK SPACE
    #xA1	#x0126	;	LATIN CAPITAL LETTER H WITH STROKE
    #xA2	#x02D8	;	BREVE
    #xA3	#x00A3	;	POUND SIGN
    #xA4	#x00A4	;	CURRENCY SIGN
    #xA6	#x0124	;	LATIN CAPITAL LETTER H WITH CIRCUMFLEX
    #xA7	#x00A7	;	SECTION SIGN
    #xA8	#x00A8	;	DIAERESIS
    #xA9	#x0130	;	LATIN CAPITAL LETTER I WITH DOT ABOVE
    #xAA	#x015E	;	LATIN CAPITAL LETTER S WITH CEDILLA
    #xAB	#x011E	;	LATIN CAPITAL LETTER G WITH BREVE
    #xAC	#x0134	;	LATIN CAPITAL LETTER J WITH CIRCUMFLEX
    #xAD	#x00AD	;	SOFT HYPHEN
    #xAF	#x017B	;	LATIN CAPITAL LETTER Z WITH DOT ABOVE
    #xB0	#x00B0	;	DEGREE SIGN
    #xB1	#x0127	;	LATIN SMALL LETTER H WITH STROKE
    #xB2	#x00B2	;	SUPERSCRIPT TWO
    #xB3	#x00B3	;	SUPERSCRIPT THREE
    #xB4	#x00B4	;	ACUTE ACCENT
    #xB5	#x00B5	;	MICRO SIGN
    #xB6	#x0125	;	LATIN SMALL LETTER H WITH CIRCUMFLEX
    #xB7	#x00B7	;	MIDDLE DOT
    #xB8	#x00B8	;	CEDILLA
    #xB9	#x0131	;	LATIN SMALL LETTER DOTLESS I
    #xBA	#x015F	;	LATIN SMALL LETTER S WITH CEDILLA
    #xBB	#x011F	;	LATIN SMALL LETTER G WITH BREVE
    #xBC	#x0135	;	LATIN SMALL LETTER J WITH CIRCUMFLEX
    #xBD	#x00BD	;	VULGAR FRACTION ONE HALF
    #xBF	#x017C	;	LATIN SMALL LETTER Z WITH DOT ABOVE
    #xC0	#x00C0	;	LATIN CAPITAL LETTER A WITH GRAVE
    #xC1	#x00C1	;	LATIN CAPITAL LETTER A WITH ACUTE
    #xC2	#x00C2	;	LATIN CAPITAL LETTER A WITH CIRCUMFLEX
    #xC4	#x00C4	;	LATIN CAPITAL LETTER A WITH DIAERESIS
    #xC5	#x010A	;	LATIN CAPITAL LETTER C WITH DOT ABOVE
    #xC6	#x0108	;	LATIN CAPITAL LETTER C WITH CIRCUMFLEX
    #xC7	#x00C7	;	LATIN CAPITAL LETTER C WITH CEDILLA
    #xC8	#x00C8	;	LATIN CAPITAL LETTER E WITH GRAVE
    #xC9	#x00C9	;	LATIN CAPITAL LETTER E WITH ACUTE
    #xCA	#x00CA	;	LATIN CAPITAL LETTER E WITH CIRCUMFLEX
    #xCB	#x00CB	;	LATIN CAPITAL LETTER E WITH DIAERESIS
    #xCC	#x00CC	;	LATIN CAPITAL LETTER I WITH GRAVE
    #xCD	#x00CD	;	LATIN CAPITAL LETTER I WITH ACUTE
    #xCE	#x00CE	;	LATIN CAPITAL LETTER I WITH CIRCUMFLEX
    #xCF	#x00CF	;	LATIN CAPITAL LETTER I WITH DIAERESIS
    #xD1	#x00D1	;	LATIN CAPITAL LETTER N WITH TILDE
    #xD2	#x00D2	;	LATIN CAPITAL LETTER O WITH GRAVE
    #xD3	#x00D3	;	LATIN CAPITAL LETTER O WITH ACUTE
    #xD4	#x00D4	;	LATIN CAPITAL LETTER O WITH CIRCUMFLEX
    #xD5	#x0120	;	LATIN CAPITAL LETTER G WITH DOT ABOVE
    #xD6	#x00D6	;	LATIN CAPITAL LETTER O WITH DIAERESIS
    #xD7	#x00D7	;	MULTIPLICATION SIGN
    #xD8	#x011C	;	LATIN CAPITAL LETTER G WITH CIRCUMFLEX
    #xD9	#x00D9	;	LATIN CAPITAL LETTER U WITH GRAVE
    #xDA	#x00DA	;	LATIN CAPITAL LETTER U WITH ACUTE
    #xDB	#x00DB	;	LATIN CAPITAL LETTER U WITH CIRCUMFLEX
    #xDC	#x00DC	;	LATIN CAPITAL LETTER U WITH DIAERESIS
    #xDD	#x016C	;	LATIN CAPITAL LETTER U WITH BREVE
    #xDE	#x015C	;	LATIN CAPITAL LETTER S WITH CIRCUMFLEX
    #xDF	#x00DF	;	LATIN SMALL LETTER SHARP S
    #xE0	#x00E0	;	LATIN SMALL LETTER A WITH GRAVE
    #xE1	#x00E1	;	LATIN SMALL LETTER A WITH ACUTE
    #xE2	#x00E2	;	LATIN SMALL LETTER A WITH CIRCUMFLEX
    #xE4	#x00E4	;	LATIN SMALL LETTER A WITH DIAERESIS
    #xE5	#x010B	;	LATIN SMALL LETTER C WITH DOT ABOVE
    #xE6	#x0109	;	LATIN SMALL LETTER C WITH CIRCUMFLEX
    #xE7	#x00E7	;	LATIN SMALL LETTER C WITH CEDILLA
    #xE8	#x00E8	;	LATIN SMALL LETTER E WITH GRAVE
    #xE9	#x00E9	;	LATIN SMALL LETTER E WITH ACUTE
    #xEA	#x00EA	;	LATIN SMALL LETTER E WITH CIRCUMFLEX
    #xEB	#x00EB	;	LATIN SMALL LETTER E WITH DIAERESIS
    #xEC	#x00EC	;	LATIN SMALL LETTER I WITH GRAVE
    #xED	#x00ED	;	LATIN SMALL LETTER I WITH ACUTE
    #xEE	#x00EE	;	LATIN SMALL LETTER I WITH CIRCUMFLEX
    #xEF	#x00EF	;	LATIN SMALL LETTER I WITH DIAERESIS
    #xF1	#x00F1	;	LATIN SMALL LETTER N WITH TILDE
    #xF2	#x00F2	;	LATIN SMALL LETTER O WITH GRAVE
    #xF3	#x00F3	;	LATIN SMALL LETTER O WITH ACUTE
    #xF4	#x00F4	;	LATIN SMALL LETTER O WITH CIRCUMFLEX
    #xF5	#x0121	;	LATIN SMALL LETTER G WITH DOT ABOVE
    #xF6	#x00F6	;	LATIN SMALL LETTER O WITH DIAERESIS
    #xF7	#x00F7	;	DIVISION SIGN
    #xF8	#x011D	;	LATIN SMALL LETTER G WITH CIRCUMFLEX
    #xF9	#x00F9	;	LATIN SMALL LETTER U WITH GRAVE
    #xFA	#x00FA	;	LATIN SMALL LETTER U WITH ACUTE
    #xFB	#x00FB	;	LATIN SMALL LETTER U WITH CIRCUMFLEX
    #xFC	#x00FC	;	LATIN SMALL LETTER U WITH DIAERESIS
    #xFD	#x016D	;	LATIN SMALL LETTER U WITH BREVE
    #xFE	#x015D	;	LATIN SMALL LETTER S WITH CIRCUMFLEX
    #xFF	#x02D9	;	DOT ABOVE
    ))

(defparameter 8859-4-unicode-map
  (create-8859-map
    #xA0	#x00A0	;	NO-BREAK SPACE
    #xA1	#x0104	;	LATIN CAPITAL LETTER A WITH OGONEK
    #xA2	#x0138	;	LATIN SMALL LETTER KRA
    #xA3	#x0156	;	LATIN CAPITAL LETTER R WITH CEDILLA
    #xA4	#x00A4	;	CURRENCY SIGN
    #xA5	#x0128	;	LATIN CAPITAL LETTER I WITH TILDE
    #xA6	#x013B	;	LATIN CAPITAL LETTER L WITH CEDILLA
    #xA7	#x00A7	;	SECTION SIGN
    #xA8	#x00A8	;	DIAERESIS
    #xA9	#x0160	;	LATIN CAPITAL LETTER S WITH CARON
    #xAA	#x0112	;	LATIN CAPITAL LETTER E WITH MACRON
    #xAB	#x0122	;	LATIN CAPITAL LETTER G WITH CEDILLA
    #xAC	#x0166	;	LATIN CAPITAL LETTER T WITH STROKE
    #xAD	#x00AD	;	SOFT HYPHEN
    #xAE	#x017D	;	LATIN CAPITAL LETTER Z WITH CARON
    #xAF	#x00AF	;	MACRON
    #xB0	#x00B0	;	DEGREE SIGN
    #xB1	#x0105	;	LATIN SMALL LETTER A WITH OGONEK
    #xB2	#x02DB	;	OGONEK
    #xB3	#x0157	;	LATIN SMALL LETTER R WITH CEDILLA
    #xB4	#x00B4	;	ACUTE ACCENT
    #xB5	#x0129	;	LATIN SMALL LETTER I WITH TILDE
    #xB6	#x013C	;	LATIN SMALL LETTER L WITH CEDILLA
    #xB7	#x02C7	;	CARON
    #xB8	#x00B8	;	CEDILLA
    #xB9	#x0161	;	LATIN SMALL LETTER S WITH CARON
    #xBA	#x0113	;	LATIN SMALL LETTER E WITH MACRON
    #xBB	#x0123	;	LATIN SMALL LETTER G WITH CEDILLA
    #xBC	#x0167	;	LATIN SMALL LETTER T WITH STROKE
    #xBD	#x014A	;	LATIN CAPITAL LETTER ENG
    #xBE	#x017E	;	LATIN SMALL LETTER Z WITH CARON
    #xBF	#x014B	;	LATIN SMALL LETTER ENG
    #xC0	#x0100	;	LATIN CAPITAL LETTER A WITH MACRON
    #xC1	#x00C1	;	LATIN CAPITAL LETTER A WITH ACUTE
    #xC2	#x00C2	;	LATIN CAPITAL LETTER A WITH CIRCUMFLEX
    #xC3	#x00C3	;	LATIN CAPITAL LETTER A WITH TILDE
    #xC4	#x00C4	;	LATIN CAPITAL LETTER A WITH DIAERESIS
    #xC5	#x00C5	;	LATIN CAPITAL LETTER A WITH RING ABOVE
    #xC6	#x00C6	;	LATIN CAPITAL LIGATURE AE
    #xC7	#x012E	;	LATIN CAPITAL LETTER I WITH OGONEK
    #xC8	#x010C	;	LATIN CAPITAL LETTER C WITH CARON
    #xC9	#x00C9	;	LATIN CAPITAL LETTER E WITH ACUTE
    #xCA	#x0118	;	LATIN CAPITAL LETTER E WITH OGONEK
    #xCB	#x00CB	;	LATIN CAPITAL LETTER E WITH DIAERESIS
    #xCC	#x0116	;	LATIN CAPITAL LETTER E WITH DOT ABOVE
    #xCD	#x00CD	;	LATIN CAPITAL LETTER I WITH ACUTE
    #xCE	#x00CE	;	LATIN CAPITAL LETTER I WITH CIRCUMFLEX
    #xCF	#x012A	;	LATIN CAPITAL LETTER I WITH MACRON
    #xD0	#x0110	;	LATIN CAPITAL LETTER D WITH STROKE
    #xD1	#x0145	;	LATIN CAPITAL LETTER N WITH CEDILLA
    #xD2	#x014C	;	LATIN CAPITAL LETTER O WITH MACRON
    #xD3	#x0136	;	LATIN CAPITAL LETTER K WITH CEDILLA
    #xD4	#x00D4	;	LATIN CAPITAL LETTER O WITH CIRCUMFLEX
    #xD5	#x00D5	;	LATIN CAPITAL LETTER O WITH TILDE
    #xD6	#x00D6	;	LATIN CAPITAL LETTER O WITH DIAERESIS
    #xD7	#x00D7	;	MULTIPLICATION SIGN
    #xD8	#x00D8	;	LATIN CAPITAL LETTER O WITH STROKE
    #xD9	#x0172	;	LATIN CAPITAL LETTER U WITH OGONEK
    #xDA	#x00DA	;	LATIN CAPITAL LETTER U WITH ACUTE
    #xDB	#x00DB	;	LATIN CAPITAL LETTER U WITH CIRCUMFLEX
    #xDC	#x00DC	;	LATIN CAPITAL LETTER U WITH DIAERESIS
    #xDD	#x0168	;	LATIN CAPITAL LETTER U WITH TILDE
    #xDE	#x016A	;	LATIN CAPITAL LETTER U WITH MACRON
    #xDF	#x00DF	;	LATIN SMALL LETTER SHARP S
    #xE0	#x0101	;	LATIN SMALL LETTER A WITH MACRON
    #xE1	#x00E1	;	LATIN SMALL LETTER A WITH ACUTE
    #xE2	#x00E2	;	LATIN SMALL LETTER A WITH CIRCUMFLEX
    #xE3	#x00E3	;	LATIN SMALL LETTER A WITH TILDE
    #xE4	#x00E4	;	LATIN SMALL LETTER A WITH DIAERESIS
    #xE5	#x00E5	;	LATIN SMALL LETTER A WITH RING ABOVE
    #xE6	#x00E6	;	LATIN SMALL LIGATURE AE
    #xE7	#x012F	;	LATIN SMALL LETTER I WITH OGONEK
    #xE8	#x010D	;	LATIN SMALL LETTER C WITH CARON
    #xE9	#x00E9	;	LATIN SMALL LETTER E WITH ACUTE
    #xEA	#x0119	;	LATIN SMALL LETTER E WITH OGONEK
    #xEB	#x00EB	;	LATIN SMALL LETTER E WITH DIAERESIS
    #xEC	#x0117	;	LATIN SMALL LETTER E WITH DOT ABOVE
    #xED	#x00ED	;	LATIN SMALL LETTER I WITH ACUTE
    #xEE	#x00EE	;	LATIN SMALL LETTER I WITH CIRCUMFLEX
    #xEF	#x012B	;	LATIN SMALL LETTER I WITH MACRON
    #xF0	#x0111	;	LATIN SMALL LETTER D WITH STROKE
    #xF1	#x0146	;	LATIN SMALL LETTER N WITH CEDILLA
    #xF2	#x014D	;	LATIN SMALL LETTER O WITH MACRON
    #xF3	#x0137	;	LATIN SMALL LETTER K WITH CEDILLA
    #xF4	#x00F4	;	LATIN SMALL LETTER O WITH CIRCUMFLEX
    #xF5	#x00F5	;	LATIN SMALL LETTER O WITH TILDE
    #xF6	#x00F6	;	LATIN SMALL LETTER O WITH DIAERESIS
    #xF7	#x00F7	;	DIVISION SIGN
    #xF8	#x00F8	;	LATIN SMALL LETTER O WITH STROKE
    #xF9	#x0173	;	LATIN SMALL LETTER U WITH OGONEK
    #xFA	#x00FA	;	LATIN SMALL LETTER U WITH ACUTE
    #xFB	#x00FB	;	LATIN SMALL LETTER U WITH CIRCUMFLEX
    #xFC	#x00FC	;	LATIN SMALL LETTER U WITH DIAERESIS
    #xFD	#x0169	;	LATIN SMALL LETTER U WITH TILDE
    #xFE	#x016B	;	LATIN SMALL LETTER U WITH MACRON
    #xFF	#x02D9	;	DOT ABOVE
    ))

(defparameter 8859-6-unicode-map	; Arabic
  (create-8859-map
    #xA0    #x00A0  ;	NO-BREAK SPACE
    #xA4    #x00A4  ;	CURRENCY SIGN
    #xAC    #x060C  ;	ARABIC COMMA
    #xAD    #x00AD  ;	SOFT HYPHEN
    #xBB    #x061B  ;	ARABIC SEMICOLON
    #xBF    #x061F  ;	ARABIC QUESTION MARK
    #xC1    #x0621  ;	ARABIC LETTER HAMZA
    #xC2    #x0622  ;	ARABIC LETTER ALEF WITH MADDA ABOVE
    #xC3    #x0623  ;	ARABIC LETTER ALEF WITH HAMZA ABOVE
    #xC4    #x0624  ;	ARABIC LETTER WAW WITH HAMZA ABOVE
    #xC5    #x0625  ;	ARABIC LETTER ALEF WITH HAMZA BELOW
    #xC6    #x0626  ;	ARABIC LETTER YEH WITH HAMZA ABOVE
    #xC7    #x0627  ;	ARABIC LETTER ALEF
    #xC8    #x0628  ;	ARABIC LETTER BEH
    #xC9    #x0629  ;	ARABIC LETTER TEH MARBUTA
    #xCA    #x062A  ;	ARABIC LETTER TEH
    #xCB    #x062B  ;	ARABIC LETTER THEH
    #xCC    #x062C  ;	ARABIC LETTER JEEM
    #xCD    #x062D  ;	ARABIC LETTER HAH
    #xCE    #x062E  ;	ARABIC LETTER KHAH
    #xCF    #x062F  ;	ARABIC LETTER DAL
    #xD0    #x0630  ;	ARABIC LETTER THAL
    #xD1    #x0631  ;	ARABIC LETTER REH
    #xD2    #x0632  ;	ARABIC LETTER ZAIN
    #xD3    #x0633  ;	ARABIC LETTER SEEN
    #xD4    #x0634  ;	ARABIC LETTER SHEEN
    #xD5    #x0635  ;	ARABIC LETTER SAD
    #xD6    #x0636  ;	ARABIC LETTER DAD
    #xD7    #x0637  ;	ARABIC LETTER TAH
    #xD8    #x0638  ;	ARABIC LETTER ZAH
    #xD9    #x0639  ;	ARABIC LETTER AIN
    #xDA    #x063A  ;	ARABIC LETTER GHAIN
    #xE0    #x0640  ;	ARABIC TATWEEL
    #xE1    #x0641  ;	ARABIC LETTER FEH
    #xE2    #x0642  ;	ARABIC LETTER QAF
    #xE3    #x0643  ;	ARABIC LETTER KAF
    #xE4    #x0644  ;	ARABIC LETTER LAM
    #xE5    #x0645  ;	ARABIC LETTER MEEM
    #xE6    #x0646  ;	ARABIC LETTER NOON
    #xE7    #x0647  ;	ARABIC LETTER HEH
    #xE8    #x0648  ;	ARABIC LETTER WAW
    #xE9    #x0649  ;	ARABIC LETTER ALEF MAKSURA
    #xEA    #x064A  ;	ARABIC LETTER YEH
    #xEB    #x064B  ;	ARABIC FATHATAN
    #xEC    #x064C  ;	ARABIC DAMMATAN
    #xED    #x064D  ;	ARABIC KASRATAN
    #xEE    #x064E  ;	ARABIC FATHA
    #xEF    #x064F  ;	ARABIC DAMMA
    #xF0    #x0650  ;	ARABIC KASRA
    #xF1    #x0651  ;	ARABIC SHADDA
    #xF2    #x0652  ;	ARABIC SUKUN
    ))

;; Consider just translating mostly arithmetically for Arabic!

;; Note: according to the current 8859-6/Unicode mapping table, the ascii digits
;; are to be mapped to arabic-indic digits.  But we're blowing that off.  I
;; doubt it's even correct, since 8859 only defines 96-character sets, and
;; leaves ASCII as is.  I've requested clarification from the Unicore mailing
;; list.  (MHD 7/10/96)
;;
;; And the answer is ...
;;
;; Date: Wed, 10 Jul 1996 13:40:29 -0700
;; From: kenw@sybase.com (Kenneth Whistler)
;; To: mhd@mailhost
;; Subject: Re: 8859-6 (Arabic) digit mappings
;; Cc: unicore@unicode.org, kenw@sybase.com, loribr@microsoft.com
;; 
;; 
;; Mark,
;; 
;; There was a back-and-forth on the 8859-6 mappings awhile
;; ago, the upshot of which is that 8859-6 0x30..0x39 MUST
;; be mapped to U+0030..U+0039, regardless of the Arabic
;; glyphs shown at those locations in the code charts for
;; 8859-6.
;; 
;; The table 8859-6.TXT on the ftp server reflects
;; the mapping published in Unicode 1.0, which is now known
;; to be in error.
;; 
;; --Ken Whistler
;; Technical Director, Unicode, Inc.




(defparameter 8859-7-unicode-map	; Greek
  (create-8859-map
    #xA0    #x00A0  ;	NO-BREAK SPACE
    #xA1    #x02BD  ;	MODIFIER LETTER REVERSED COMMA
    #xA2    #x02BC  ;	MODIFIER LETTER APOSTROPHE
    #xA3    #x00A3  ;	POUND SIGN
    #xA6    #x00A6  ;	BROKEN BAR
    #xA7    #x00A7  ;	SECTION SIGN
    #xA8    #x00A8  ;	DIAERESIS
    #xA9    #x00A9  ;	COPYRIGHT SIGN
    #xAB    #x00AB  ;	LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
    #xAC    #x00AC  ;	NOT SIGN
    #xAD    #x00AD  ;	SOFT HYPHEN
    #xAF    #x2015  ;	HORIZONTAL BAR
    #xB0    #x00B0  ;	DEGREE SIGN
    #xB1    #x00B1  ;	PLUS-MINUS SIGN
    #xB2    #x00B2  ;	SUPERSCRIPT TWO
    #xB3    #x00B3  ;	SUPERSCRIPT THREE
    #xB4    #x0384  ;	GREEK TONOS
    #xB5    #x0385  ;	GREEK DIALYTIKA TONOS
    #xB6    #x0386  ;	GREEK CAPITAL LETTER ALPHA WITH TONOS
    #xB7    #x00B7  ;	MIDDLE DOT
    #xB8    #x0388  ;	GREEK CAPITAL LETTER EPSILON WITH TONOS
    #xB9    #x0389  ;	GREEK CAPITAL LETTER ETA WITH TONOS
    #xBA    #x038A  ;	GREEK CAPITAL LETTER IOTA WITH TONOS
    #xBB    #x00BB  ;	RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
    #xBC    #x038C  ;	GREEK CAPITAL LETTER OMICRON WITH TONOS
    #xBD    #x00BD  ;	VULGAR FRACTION ONE HALF
    #xBE    #x038E  ;	GREEK CAPITAL LETTER UPSILON WITH TONOS
    #xBF    #x038F  ;	GREEK CAPITAL LETTER OMEGA WITH TONOS
    #xC0    #x0390  ;	GREEK SMALL LETTER IOTA WITH DIALYTIKA AND TONOS
    #xC1    #x0391  ;	GREEK CAPITAL LETTER ALPHA
    #xC2    #x0392  ;	GREEK CAPITAL LETTER BETA
    #xC3    #x0393  ;	GREEK CAPITAL LETTER GAMMA
    #xC4    #x0394  ;	GREEK CAPITAL LETTER DELTA
    #xC5    #x0395  ;	GREEK CAPITAL LETTER EPSILON
    #xC6    #x0396  ;	GREEK CAPITAL LETTER ZETA
    #xC7    #x0397  ;	GREEK CAPITAL LETTER ETA
    #xC8    #x0398  ;	GREEK CAPITAL LETTER THETA
    #xC9    #x0399  ;	GREEK CAPITAL LETTER IOTA
    #xCA    #x039A  ;	GREEK CAPITAL LETTER KAPPA
    #xCB    #x039B  ;	GREEK CAPITAL LETTER LAMDA
    #xCC    #x039C  ;	GREEK CAPITAL LETTER MU
    #xCD    #x039D  ;	GREEK CAPITAL LETTER NU
    #xCE    #x039E  ;	GREEK CAPITAL LETTER XI
    #xCF    #x039F  ;	GREEK CAPITAL LETTER OMICRON
    #xD0    #x03A0  ;	GREEK CAPITAL LETTER PI
    #xD1    #x03A1  ;	GREEK CAPITAL LETTER RHO
    #xD3    #x03A3  ;	GREEK CAPITAL LETTER SIGMA
    #xD4    #x03A4  ;	GREEK CAPITAL LETTER TAU
    #xD5    #x03A5  ;	GREEK CAPITAL LETTER UPSILON
    #xD6    #x03A6  ;	GREEK CAPITAL LETTER PHI
    #xD7    #x03A7  ;	GREEK CAPITAL LETTER CHI
    #xD8    #x03A8  ;	GREEK CAPITAL LETTER PSI
    #xD9    #x03A9  ;	GREEK CAPITAL LETTER OMEGA
    #xDA    #x03AA  ;	GREEK CAPITAL LETTER IOTA WITH DIALYTIKA
    #xDB    #x03AB  ;	GREEK CAPITAL LETTER UPSILON WITH DIALYTIKA
    #xDC    #x03AC  ;	GREEK SMALL LETTER ALPHA WITH TONOS
    #xDD    #x03AD  ;	GREEK SMALL LETTER EPSILON WITH TONOS
    #xDE    #x03AE  ;	GREEK SMALL LETTER ETA WITH TONOS
    #xDF    #x03AF  ;	GREEK SMALL LETTER IOTA WITH TONOS
    #xE0    #x03B0  ;	GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND TONOS
    #xE1    #x03B1  ;	GREEK SMALL LETTER ALPHA
    #xE2    #x03B2  ;	GREEK SMALL LETTER BETA
    #xE3    #x03B3  ;	GREEK SMALL LETTER GAMMA
    #xE4    #x03B4  ;	GREEK SMALL LETTER DELTA
    #xE5    #x03B5  ;	GREEK SMALL LETTER EPSILON
    #xE6    #x03B6  ;	GREEK SMALL LETTER ZETA
    #xE7    #x03B7  ;	GREEK SMALL LETTER ETA
    #xE8    #x03B8  ;	GREEK SMALL LETTER THETA
    #xE9    #x03B9  ;	GREEK SMALL LETTER IOTA
    #xEA    #x03BA  ;	GREEK SMALL LETTER KAPPA
    #xEB    #x03BB  ;	GREEK SMALL LETTER LAMDA
    #xEC    #x03BC  ;	GREEK SMALL LETTER MU
    #xED    #x03BD  ;	GREEK SMALL LETTER NU
    #xEE    #x03BE  ;	GREEK SMALL LETTER XI
    #xEF    #x03BF  ;	GREEK SMALL LETTER OMICRON
    #xF0    #x03C0  ;	GREEK SMALL LETTER PI
    #xF1    #x03C1  ;	GREEK SMALL LETTER RHO
    #xF2    #x03C2  ;	GREEK SMALL LETTER FINAL SIGMA
    #xF3    #x03C3  ;	GREEK SMALL LETTER SIGMA
    #xF4    #x03C4  ;	GREEK SMALL LETTER TAU
    #xF5    #x03C5  ;	GREEK SMALL LETTER UPSILON
    #xF6    #x03C6  ;	GREEK SMALL LETTER PHI
    #xF7    #x03C7  ;	GREEK SMALL LETTER CHI
    #xF8    #x03C8  ;	GREEK SMALL LETTER PSI
    #xF9    #x03C9  ;	GREEK SMALL LETTER OMEGA
    #xFA    #x03CA  ;	GREEK SMALL LETTER IOTA WITH DIALYTIKA
    #xFB    #x03CB  ;	GREEK SMALL LETTER UPSILON WITH DIALYTIKA
    #xFC    #x03CC  ;	GREEK SMALL LETTER OMICRON WITH TONOS
    #xFD    #x03CD  ;	GREEK SMALL LETTER UPSILON WITH TONOS
    #xFE    #x03CE  ;	GREEK SMALL LETTER OMEGA WITH TONOS
    ))

(defparameter 8859-8-unicode-map	; Hebrew
  (create-8859-map
    #xA0    #x00A0  ;	NO-BREAK SPACE
    #xA2    #x00A2  ;	CENT SIGN
    #xA3    #x00A3  ;	POUND SIGN
    #xA4    #x00A4  ;	CURRENCY SIGN
    #xA5    #x00A5  ;	YEN SIGN
    #xA6    #x00A6  ;	BROKEN BAR
    #xA7    #x00A7  ;	SECTION SIGN
    #xA8    #x00A8  ;	DIAERESIS
    #xA9    #x00A9  ;	COPYRIGHT SIGN
    #xAA    #x00D7  ;	MULTIPLICATION SIGN
    #xAB    #x00AB  ;	LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
    #xAC    #x00AC  ;	NOT SIGN
    #xAD    #x00AD  ;	SOFT HYPHEN
    #xAE    #x00AE  ;	REGISTERED SIGN
    #xAF    #x203E  ;	OVERLINE
    #xB0    #x00B0  ;	DEGREE SIGN
    #xB1    #x00B1  ;	PLUS-MINUS SIGN
    #xB2    #x00B2  ;	SUPERSCRIPT TWO
    #xB3    #x00B3  ;	SUPERSCRIPT THREE
    #xB4    #x00B4  ;	ACUTE ACCENT
    #xB5    #x00B5  ;	MICRO SIGN
    #xB6    #x00B6  ;	PILCROW SIGN
    #xB7    #x00B7  ;	MIDDLE DOT
    #xB8    #x00B8  ;	CEDILLA
    #xB9    #x00B9  ;	SUPERSCRIPT ONE
    #xBA    #x00F7  ;	DIVISION SIGN
    #xBB    #x00BB  ;	RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
    #xBC    #x00BC  ;	VULGAR FRACTION ONE QUARTER
    #xBD    #x00BD  ;	VULGAR FRACTION ONE HALF
    #xBE    #x00BE  ;	VULGAR FRACTION THREE QUARTERS
    #xDF    #x2017  ;	DOUBLE LOW LINE
    #xE0    #x05D0  ;	HEBREW LETTER ALEF
    #xE1    #x05D1  ;	HEBREW LETTER BET
    #xE2    #x05D2  ;	HEBREW LETTER GIMEL
    #xE3    #x05D3  ;	HEBREW LETTER DALET
    #xE4    #x05D4  ;	HEBREW LETTER HE
    #xE5    #x05D5  ;	HEBREW LETTER VAV
    #xE6    #x05D6  ;	HEBREW LETTER ZAYIN
    #xE7    #x05D7  ;	HEBREW LETTER HET
    #xE8    #x05D8  ;	HEBREW LETTER TET
    #xE9    #x05D9  ;	HEBREW LETTER YOD
    #xEA    #x05DA  ;	HEBREW LETTER FINAL KAF
    #xEB    #x05DB  ;	HEBREW LETTER KAF
    #xEC    #x05DC  ;	HEBREW LETTER LAMED
    #xED    #x05DD  ;	HEBREW LETTER FINAL MEM
    #xEE    #x05DE  ;	HEBREW LETTER MEM
    #xEF    #x05DF  ;	HEBREW LETTER FINAL NUN
    #xF0    #x05E0  ;	HEBREW LETTER NUN
    #xF1    #x05E1  ;	HEBREW LETTER SAMEKH
    #xF2    #x05E2  ;	HEBREW LETTER AYIN
    #xF3    #x05E3  ;	HEBREW LETTER FINAL PE
    #xF4    #x05E4  ;	HEBREW LETTER PE
    #xF5    #x05E5  ;	HEBREW LETTER FINAL TSADI
    #xF6    #x05E6  ;	HEBREW LETTER TSADI
    #xF7    #x05E7  ;	HEBREW LETTER QOF
    #xF8    #x05E8  ;	HEBREW LETTER RESH
    #xF9    #x05E9  ;	HEBREW LETTER SHIN
    #xFA    #x05EA  ;	HEBREW LETTER TAV
    ))

; (test-8859-mapping)


(eval-when (:compile-toplevel :load-toplevel :execute)
(defun make-reverse-8859-unicode-map (8859-graphic-character-set-name)
  (let ((graphic-character-set
	  (graphic-character-set 8859-graphic-character-set-name))
	(reverse-map (make-8859-reverse-unicode-map)))
    
    (loop for i from 0 below 8859-part-size
	  do (setf (get-8859-reverse-unicode-map 
		     (map-code-to-unicode graphic-character-set i)
		     reverse-map)
		   i))
    reverse-map))
)
  


;;;; Maps and Methods for ISO-8859 Graphic Character Sets

;; This sets up graphic character sets for ISO-8859 parts 1-10.  Parts 2, 3, 4,
;; 6, 7, 8, and 10 just have a lookup table; these are used by the default
;; map-code-to-unicode method for structures of type iso-8859-abstract; see
;; TRANSCODE.LISP for default method.  The other parts have an override method,
;; provided, mainly to save space the space taken by the lookup table. (Does it
;; save much?!)

(def-structure-method map-code-to-unicode (iso-8859-1 code)
  (declare (ignore iso-8859-1))
  (char+w #u0080 code))

(def-structure-method map-unicode-to-code-if-any
    (iso-8859-1 unicode-wide-character)
  (declare (ignore iso-8859-1))
  (if (char<=w #u00A0 unicode-wide-character #u00FF)
      (logandf (wide-character-code unicode-wide-character) 8859-code-mask)))

(setf (8859-unicode-map (graphic-character-set 'iso-8859-2))
      8859-2-unicode-map)

(setf (8859-reverse-unicode-map (graphic-character-set 'iso-8859-2))
      (make-reverse-8859-unicode-map 'iso-8859-2))
		       
	      

(setf (8859-unicode-map (graphic-character-set 'iso-8859-3))
      8859-3-unicode-map)

(setf (8859-reverse-unicode-map (graphic-character-set 'iso-8859-3))
      (make-reverse-8859-unicode-map 'iso-8859-3))

(setf (8859-unicode-map (graphic-character-set 'iso-8859-4))
      8859-4-unicode-map)

(setf (8859-reverse-unicode-map (graphic-character-set 'iso-8859-4))
      (make-reverse-8859-unicode-map 'iso-8859-4))

(def-structure-method map-code-to-unicode (iso-8859-5 code)
  (declare (ignore iso-8859-5))
  (let ((character (char+w #u0080 code)))
    (declare (type wide-character character))
    (wide-character-case
      character
      (#u00A0	#u00A0)			;        NO-BREAK SPACE
      (#u00AD	#u00AD)			;        SOFT HYPHEN
      (#u00F0	#u2116)			;        NUMERO SIGN
      (#u00FD	#u00A7)			;        SECTION SIGN
      (t
	;; The rest are arithmetic mappings between CYRILLIC CAPITAL LETTER IO
	;; (0xA1, 0x0401) and CYRILLIC SMALL LETTER DZHE.(0xFF, 0x045F)
	(char+w #u0400 (-f code #x20))))))

(def-structure-method map-unicode-to-code-if-any
    (iso-8859-5 unicode-wide-character)
  (declare (ignore iso-8859-5))
  (wide-character-case
    unicode-wide-character
    (#u00A0 #.(- #xA0 #x80))		;        NO-BREAK SPACE
    (#u00AD #.(- #xAD #x80))		;        SOFT HYPHEN
    (#u2116 #.(- #xF0 #x80))		;        NUMERO SIGN
    (#u00A7 #.(- #xFD #x80))		;        SECTION SIGN
    (t
      (let* ((cyrillic-block-offset #x400)
	     (code (wide-character-code unicode-wide-character))
	     (offset-code (-f code cyrillic-block-offset)))
	(declare (type fixnum cyrillic-block-offset code offset-code))
	(if (<=f 0 offset-code 95)
	    (+f #x20 offset-code))))))


(setf (8859-unicode-map (graphic-character-set 'iso-8859-6))
      8859-6-unicode-map)

(setf (8859-reverse-unicode-map (graphic-character-set 'iso-8859-6))
      (make-reverse-8859-unicode-map 'iso-8859-6))

(setf (8859-unicode-map (graphic-character-set 'iso-8859-7))
      8859-7-unicode-map)

(setf (8859-reverse-unicode-map (graphic-character-set 'iso-8859-7))
      (make-reverse-8859-unicode-map 'iso-8859-7))

(setf (8859-unicode-map (graphic-character-set 'iso-8859-8))
      8859-8-unicode-map)

(setf (8859-reverse-unicode-map (graphic-character-set 'iso-8859-8))
      (make-reverse-8859-unicode-map 'iso-8859-8))

(def-structure-method map-code-to-unicode (iso-8859-9 code)
  (declare (ignore iso-8859-9))
  ;; 8859-9 (aka Latin 5) differs slightly from 8859-1 (aka Latin 1), as
  ;; indicated here:
  (let ((character (char+w #u0080 code)))
    (declare (type wide-character character))
    (wide-character-case
      character
      (#u00D0	#u011E)	;	LATIN CAPITAL LETTER G WITH BREVE
      (#u00DD	#u0130)	;	LATIN CAPITAL LETTER I WITH DOT ABOVE
      (#u00DE	#u015E)	;	LATIN CAPITAL LETTER S WITH CEDILLA
      (#u00F0	#u011F)	;	LATIN SMALL LETTER G WITH BREVE
      (#u00FD	#u0131)	;	LATIN SMALL LETTER DOTLESS I
      (#u00FE	#u015F)	;	LATIN SMALL LETTER S WITH CEDILLA
      (#u00FF	#u00FF)	;	LATIN SMALL LETTER Y WITH DIAERESIS ;
      (t character))))

(setf (8859-reverse-unicode-map (graphic-character-set 'iso-8859-9))
      (make-reverse-8859-unicode-map 'iso-8859-9)) ; do algorithmically?!

(setf (8859-unicode-map (graphic-character-set 'iso-8859-10))
      8859-4-unicode-map)		; 4 intentional; see below!

(setf (8859-reverse-unicode-map (graphic-character-set 'iso-8859-10))
      (make-reverse-8859-unicode-map 'iso-8859-10))

;; Don't have mapping data yet on Part 10 -- according to our information, this
;; is closest to latin4 (8859-4), so we'll use that.  This standard is brand
;; new, and maybe not even finalized.  Unicode has yet to post a mapping table.
;; The following is from the web document "ISO 8859 Alphabet Soup"
;; (http://www.cs.tu-berlin.de/~czyborra/charsets).
;;
;;    Latin 6 adds the last Inuit (Greenlandic) and Sami (Lappish) letters that
;;    were missing in Latin 4 to cover the entire Nordic area. RFC 1345 listed a
;;    preliminary and different `latin6'. Skolt Sami still needs a few more
;;    accents than these.


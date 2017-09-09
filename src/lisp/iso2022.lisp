;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module ISO2022: ISO 2022 Code Extension Handling

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark David




;;;; ISO 2022


;;; [The following was produced and sent via email courtesy of Carl W. Hoffman,
;;; Basis Technology, via email to MHD 7/13/95.]
;;;
;;; 		 ISO 2022 CHARACTER SET REGISTRATIONS
;;; 
;;; 
;;; 7-BIT CHARACTER SETS
;;; --------------------
;;; 
;;; Unless otherwise noted, each of the following character sets has
;;; 94 characters.  I believe that many of them have been made
;;; obsolete by ISO8859.
;;; 
;;;  ESC ( @ ....... ISO 646-1973
;;;                  Like ASCII except 0x24 = "currency sign" rather than
;;;                  "dollar sign".
;;; 
;;;  ESC ( A ....... Britain BS4730
;;;                  Like ASCII except 0x23 = "pound" rather than "sharpsign".
;;; 
;;;  ESC ( B ....... U.S. ASCII (ANSI X3.4-1968)
;;; 
;;;  ESC ( C ....... Finland/Sweden
;;; 
;;;  ESC ( D ....... Finland/Sweden (14 characters)
;;; 
;;;  ESC ( E ....... Denmark/Norway
;;; 
;;;  ESC ( F ....... Denmark/Norway
;;; 
;;;  ESC ( G ....... ISO 646 modified for Sweden (SEN 85-02-00 Annex B)
;;; 
;;;  ESC ( H ....... ISO 646 modified for Sweden (SEN 85-02-00 Annex C)
;;; 
;;;  ESC ( I ....... Japan Katakana (JISX 0201, formerly JISC 6220-1969)
;;; 
;;;  ESC ( J ....... Japan Roman (JISX 0201, formerly JISC 6220-1969)
;;;                  Like ASCII except 0x5C = "yen" rather than "backslash".
;;; 
;;;  ESC ( K ....... Germany (DIN 66-003)
;;; 
;;;  ESC ( R ....... France
;;; 
;;; 
;;; 8-BIT CHARACTER SETS
;;; --------------------
;;; 
;;; In the following character sets, ESC ( B defines the G0 graphic
;;; character set (low half) to be ASCII and the second triple
;;; defines the G1 character set (high half) which varies between
;;; sets.
;;; 
;;;  ESC ( B ESC - A ....... ISO 8859-1 Latin-1
;;; 
;;;  ESC ( B ESC - B ....... ISO 8859-2 Latin-2
;;; 
;;;  ESC ( B ESC - C ....... ISO 8859-3 Latin-3
;;; 
;;;  ESC ( B ESC - D ....... ISO 8859-4 Latin-4
;;; 
;;;  ESC ( B ESC - L ....... ISO 8859-5 Latin/Cyrillic
;;; 
;;;  ESC ( B ESC - G ....... ISO 8859-6 Latin/Arabic
;;; 
;;;  ESC ( B ESC - F ....... ISO 8859-7 Latin/Greek
;;; 
;;;  ESC ( B ESC - H ....... ISO 8859-8 Latin/Hebrew
;;; 
;;;  ESC ( B ESC - M ....... ISO 8859-9 Latin-5
;;; 
;;;  ESC ( B ESC - Z ....... TCVN 5712:1993 (VSCII-2)
;;;                          Vietnamese Standard Code for Information Interchange
;;;                          96 characters / registration #180
;;; 
;;; 
;;; DOUBLE-BYTE CHARACTER SETS
;;; --------------------------
;;; 
;;;  ESC $ @ or ESC $ ( @ ....... JISX 0208-1976 (formerly JISC 6226-1978)
;;;                               6802 characters / registration #42
;;;                               Japan Industrial Standard
;;; 
;;;  ESC $ A or ESC $ ( A ....... GB 2312-80 ("Guo Biao")
;;;                               7445 characters / registration #58
;;;                               China Association for Standardization (PRC)
;;; 
;;;  ESC $ B or ESC $ ( B ....... JISX 0208-1983 (formerly JISC 6226-1983)
;;;                               6877 characters / registration #87
;;;                               Japan Industrial Standard
;;; 
;;;             ESC $ ( C ....... KSC 5601-1987
;;;                               8224 characters / registration #149
;;;                               Korea Bureau of Standards
;;; 
;;;             ESC $ ( D ....... JISX 0212-1990
;;;                               6067 characters / registration #159
;;;                               Japan Industrial Standard
;;; 
;;;             ESC $ ( E ....... GB 2312 and GB 8565.2 ("Guo Biao")
;;;                               8443 characters / registration #165
;;;                               China Association for Standardization (PRC)
;;; 
;;;       ESC & @ ESC $ B ....... JISX 0208-1990
;;;                               6879 characters / registration #168
;;;                               Japan Industrial Standard
;;; 
;;;             ESC $ ( G ....... CSIC Set 1 (CNS 11643-1986)
;;;                               6085 characters / registration #171
;;;                               Chinese Standard Interchange Code
;;;                               Chinese National Standard (Taiwan)
;;; 
;;;             ESC $ ( H ....... CSIC Set 2 (CNS 11643-1986)
;;;                               7650 characters / registration #172
;;; 
;;;             ESC $ ( I ....... CSIC Set 3 (CNS 11643-1992)
;;;                               6148 characters / registration #183
;;; 
;;;             ESC $ ( J ....... CSIC Set 4 (CNS 11643-1992)
;;;                               7298 characters / registration #184
;;; 
;;;             ESC $ ( K ....... CSIC Set 5 (CNS 11643-1992)
;;;                               8603 characters / registration #185
;;; 
;;;             ESC $ ( L ....... CSIC Set 6 (CNS 11643-1992)
;;;                               6388 characters / registration #186
;;; 
;;;             ESC $ ( M ....... CSIC Set 7 (CNS 11643-1992)
;;;                               6539 characters / registration #187
;;; 
;;; 
;;; ISO/IEC 10646 ESCAPE SEQUENCES
;;; ------------------------------
;;; 
;;;  ESC % / @ ....... UCS two-octet  (UCS-2) level 1
;;; 
;;;  ESC % / A ....... UCS four-octet (UCS-4) level 1
;;; 
;;;  ESC % / C ....... UCS two-octet  (UCS-2) level 2
;;; 
;;;  ESC % / D ....... UCS four-octet (UCS-4) level 2
;;; 
;;;  ESC % / E ....... UCS two-octet  (UCS-2) level 3
;;; 
;;;  ESC % / F ....... UCS four-octet (UCS-4) level 3
;;; 
;;;  ESC % B   ....... UCS Transformation Format (UTF-1)


(eval-when (:compile-toplevel :load-toplevel :execute)

;;; `All-supported-2022-escape-sequences' ... The list is sorted in order of
;;; sequence length, with longer entries appearing earlier.  Thus, matching
;;; entries from beginning to end is assured to return longer matches ahead
;;; shorter ones.

(defvar all-supported-2022-escape-sequences nil)

(defun-simple length-of-wide-string-greater-p (wide-string-1 wide-string-2)
  (>f (wide-string-length wide-string-1) (wide-string-length wide-string-2)))

;; Move to Unicode!


;;; `Def-supported-2022-escape-sequence' ... Charset should be the name of a
;;; character set as defined by def-graphic-character-set.  Invocation-side should
;;; be one of the symbols LEFT or RIGHT.

(defmacro def-supported-2022-escape-sequence
    (escape-sequence charset invocation-side)
  (ecase invocation-side ((left right)))
  ;; See note.
  `(progn
     (pushnew (list (stringw ',escape-sequence) ',charset ',invocation-side)
	      all-supported-2022-escape-sequences
	      :test #'equalw)
     ;; could insert smartly, instead of doing this batch sort, if speed mattered here
     (setq all-supported-2022-escape-sequences
	   (sort-list
	     all-supported-2022-escape-sequences
	     #'length-of-wide-string-greater-p
	     #'car))))

;; Note: unfortunately, charsets are currently defined in a later.  Otherwise,
;; it would be wise to check that only defined character sets are used!

  

;; ISO-646 (= US-ASCII)

(def-supported-2022-escape-sequence "(B" iso-646 left)

;; Note: the following three are "like ASCII", but differ in minor ways. They
;; are here so that they can be recognized and imported reasonably well.  We
;; don't currently emit them.

;; Britain BS4730 (0x23 = "pound" rather than "sharpsign")

(def-supported-2022-escape-sequence "(A" iso-646 left)


;; ISO 646-1973 [punt on this for now, use usascii!]

(def-supported-2022-escape-sequence "(@" iso-646 left)



;; Japan Roman (JISX 0201, formerly JISC 6220-1969) Like ASCII except 0x5C =
;; "yen" rather than "backslash".  [punt on this for now, use iso-646!]

(def-supported-2022-escape-sequence "(J" iso-646 left)


;;; 8-bit, single-byte character sets

;; 8859, Parts 1 through 9 in G1

(def-supported-2022-escape-sequence "-A" iso-8859-1 right)
(def-supported-2022-escape-sequence "-B" iso-8859-2 right)
(def-supported-2022-escape-sequence "-C" iso-8859-3 right)
(def-supported-2022-escape-sequence "-D" iso-8859-4 right)
(def-supported-2022-escape-sequence "-L" iso-8859-5 right)
(def-supported-2022-escape-sequence "-G" iso-8859-6 right)
(def-supported-2022-escape-sequence "-F" iso-8859-7 right)
(def-supported-2022-escape-sequence "-H" iso-8859-8 right)
(def-supported-2022-escape-sequence "-M" iso-8859-9 right)



;;; 7-bit, double-byte character sets


;; GB 2312-1980:

;; ESC $ A   ; GB 2312-80 ("Guo Biao")  or ...
(def-supported-2022-escape-sequence "$A" gb-2312 left)

;; ESC $ ( A ; GB 2312-80 ("Guo Biao")  (treat same as one above)
(def-supported-2022-escape-sequence "$(A" gb-2312 left)


;; JISX 0208-1983:

;; $(B is the most canonical.  At least, this is what we emit (c.f.,
;; invoke-graphic-character-set-if-necessary in TRANSCODE).

(def-supported-2022-escape-sequence "$(B" jis-x-0208 left)

;; The rest are largely compatible variations, which should all end up being interpreted
;; as the same thing.

(def-supported-2022-escape-sequence "$B" jis-x-0208 left)


;; JISX 0208-1990
;; no need to distinguish from 1983 version at this time

;; ESC & @ ESC $ B   ; JIS X 0208-1990
(def-supported-2022-escape-sequence
    #.(string-append
	"&@"
	(make-string 1 :initial-element (code-char #x1B))
	"$B")
  jis-x-0208
  left)

;; ESC $ @   ; JIS C 6226-1978 (earlier version, treat the same)
(def-supported-2022-escape-sequence "$@" jis-x-0208 left)

;; ESC $ B   ; JIS X 0208-1983 (earlier version, treat the same)
(def-supported-2022-escape-sequence "$B" jis-x-0208 left)


;; KS C5601-1987:

;; ESC $ ( C ; KSC 5601-1987
(def-supported-2022-escape-sequence "$(C" ks-c-5601 left)






;;; 8-bit, double-byte character sets



;; GB 2312-1980

(def-supported-2022-escape-sequence "$)A" gb-2312 right)

;; JISX 0208-1983

(def-supported-2022-escape-sequence "$)B" jis-x-0208 right)

;; KSC 5601-1987

(def-supported-2022-escape-sequence "$)C" ks-c-5601 right)

)




;;; `Match-2022-escape-ahead' is called with escape-string as a wide string and
;;; string as either a gensym string or a wide string.  In both cases, the
;;; result is true iff esc_string matches the sequence of character beginning at
;;; the position specified by the value of index.  When true, it increments
;;; index to be one past the last character read. Otherwise, it returns false
;;; (nil), and does not do anything to index.

(defmacro match-2022-escape-ahead (escape-string string index)
  (avoiding-variable-capture
      (escape-string string
		     &aux
		     wide-string-p
		     escape-end-index string-end-index
		     i j c1 c2)
    `(let* ((,wide-string-p (wide-string-p ,string))
	    (,escape-end-index
	       (wide-string-length ,escape-string))
	    (,string-end-index 
	       (if ,wide-string-p
		   (wide-string-length ,string)
		   (gensym-string-length ,string)))
	    (,i 0)
	    (,j ,index)
	    (,c1 #u0000)
	    (,c2 #u0000))
       (declare (type fixnum ,index ,escape-end-index ,string-end-index ,i ,j)
		(type wide-character ,c1 ,c2))
       (loop do (unless (<f ,i ,escape-end-index)
		  (loop-finish))
		(setq ,c1 (read-character-from-wide-string ,escape-string ,i))
		(unless (<f ,j ,string-end-index)
		  (return nil))
		(setq ,c2
		      (if ,wide-string-p
			  (read-character-from-wide-string ,string ,j)
			  (character-to-wide-character
			    (read-simple-character-from-gensym-string
			      ,string ,j nil))))
		(when (char/=w ,c1 ,c2)
		  (return nil))
	     finally
	       (setf ,index ,j)
	       (return t)))))



      
    
  










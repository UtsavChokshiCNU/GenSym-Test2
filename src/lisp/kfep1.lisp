;; -*- Mode:Common-Lisp; Package:AB; Base:10; Syntax:COMMON-LISP -*-
(in-package "AB")

;;;; Module KFEP1  --  Kanji Front End Processor

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved. 

;;; In a letter to Lowell Hawkinson dated 10 May 1991, and received 20
;;; May 1991, C.Itoh Techno-science Co., Ltd., (CTC), "would like to
;;; make sure sure that the Japanese language technology which is ported
;;; to Japanese G2, including but not limited to Romaji-to-Kana and
;;; Kana-to-Kanji conversion software, is the property of CTC and that
;;; its copyright belongs to CTC." CTC further "represent[s] that such
;;; technology does not infringe upon the rights of any third party."
;;; Gensym Corporation expects to evaluate these claims.  (MHD 5/20/91)

;;; In a phone conversation I had today with Ong, Peng Tsin, Mr.  Ong
;;; said that he wrote the Romaji-to-Kana conversion software, and that
;;; the Romaji-to-Kana conversion software should not be considered part
;;; of CTC technology that was ported to Japanese G2.  Thus, the
;;; Romaji-to- Kana conversion software that is used in Japanese G2
;;; should be considered the property of Gensym.  This software is
;;; contained in the Subsection "CONVERTERS (Kana-to-ASCII and
;;; ASCII-to-Kana)", currently located in module KFEP3, which contains
;;; convert-to-hiragana-if-possible and convert-to-katakana-if-possible,
;;; which are the interface to the EDIT module.  (MHD 12/6/91)




;;; Ong, Peng Tsin and Mark H. David




(pushnew 'kfep (optional-modules 'ab))


#+development
(declare-forward-reference check-memory function)





;;;; Start of Old KFEP1





;;;; Managed Lisp Strings

;; Move to a UTILITIES module?



;;; A `managed lisp string' is just like a text string (see module UTILITIES1),
;;; except that there are no restrictions as to what characters it can contain.



;;; `Obtain-lisp-string' ...

(defmacro obtain-lisp-string (length)
  `(obtain-simple-gensym-string ,length))

;; This is NOT documented to return a simple text string.  We are free to
;; change this to return any kind of text string.  C.f. copy-managed-lisp-
;; string.  (MHD 1/3/91)



;;; `Simple-lisp-string-p' ...

(defmacro simple-lisp-string-p (lisp-string)
  `(simple-gensym-string-p ,lisp-string))




;;; The defun-substitution-macro `copy-managed-lisp-string' returns a copy of 
;;; source-string in a new simple string.  Only the specified number of
;;; characters will be copied, and if the specified number of characters is
;;; larger than the length of string, it's an error.

(defun copy-managed-lisp-string
       (string start-index number-of-characters)
  (gensym-string-substring
    string start-index (+f start-index number-of-characters)))

;; Took out inline code above and replaced it with call to gensym-string-substring,
;; whose inline code was almost identical.  The above function has a trivially
;; different calling style than gensym-string-substring.  Its real (main) purpose for
;; being called instead calling gensym-string-substring directly is to implement the
;; data abstraction of "managed lisp strings".  (MHD 12/30/91)

;; Changed to a function today from a macro, actually a defun-substitution-macro.
;; I do not see a need to expand this code inline in any of its callers.
;; (MHD 12/26/91)

;; A few callers in this module depend on this to return a simple string, as
;; opposed to a string with a fill pointer.

;; Consider generalizing and including with standard string copying utility
;; functions in module UTILITIES1.





;;; `Copy-text-string-as-managed-lisp-string' ... It's the caller's responsibility
;;; to only call this when text-string contains all 8-bit characters.  If not, it's
;;; an error, but an error is signalled only on development.

(defun copy-text-string-as-managed-lisp-string
    (text-string start-index number-of-characters)
  (let* ((length (-f number-of-characters start-index))
	 (string (obtain-lisp-string length))
	 (simple-p (simple-gensym-string-p string)))
    (loop for i from start-index
	  repeat length
	  as char = (code-char (wide-character-code (charw text-string i)))
	  do #+development
	     (unless char
	       (error "arg cannot be coerced to a lisp string"))
	     (if simple-p
		 (setf (schar string i) char)
		 (setf (char string i) char)))
    string))



;;; `Copy-lisp-string-to-target' ...

(defun copy-lisp-string-to-target
  (source-string target-string source-start-index target-start-index number-of-characters)
  (loop with source-string-is-simple? = (simple-gensym-string-p source-string)
	with target-string-is-simple? = (simple-gensym-string-p target-string)
	repeat number-of-characters
	for i from source-start-index
	as j from target-start-index
	as source-char = (gchar source-string i source-string-is-simple?)
	do (if target-string-is-simple?		; need setf method for gchar!
	       (setf (schar target-string j) source-char)
	       (setf (char target-string j) source-char)))
  number-of-characters)





;;; `lisp-string-substring' ...

(defmacro lisp-string-substring (string start? end?)
  `(gensym-string-substring ,string ,start? ,end?))


;;; `Reclaim-lisp-string' ...

(defmacro reclaim-lisp-string (lisp-string)
  `(reclaim-gensym-string ,lisp-string))


;;; `Copy-lisp-string' ...

(defmacro copy-lisp-string (lisp-string)
  `(copy-gensym-string ,lisp-string))


;;; `Copy-lisp-string-with-change-to-upper-case' ...

(defun copy-lisp-string-with-change-to-upper-case (string)
  (loop with string-is-simple? = (simple-gensym-string-p string)
	with string-length = (glength string string-is-simple?)
	with new-string = (obtain-simple-gensym-string string-length)
	for i from 0 below string-length
	do (setf (schar new-string i)
		 (char-upcase (gchar string i string-is-simple?)))
	finally
	  (return new-string)))






;;;; JIS Strings 



;;; A `jis string' is a managed lisp string containing kanji codes, each of which
;;; is represented by two successive lisp string characters.  The length of a
;;; jis string is half its lisp string length.  A position index in a jis
;;; string is half the character index of its first lisp string character.



;;; `Convert-n-bytes-to-jis-string' ...

(defun convert-n-bytes-to-jis-string (string number-of-bytes-to-convert)
  (loop with string-is-simple? = (simple-gensym-string-p string)
	with new-string = (obtain-simple-gensym-string number-of-bytes-to-convert)
	for i from 0 below number-of-bytes-to-convert
	do (setf (schar new-string i)
		 (gchar string i string-is-simple?))
	finally
	  (return new-string)))



;;; `Jis-string-substring' is similar to lisp-string-substring, except that
;;; it works for jis strings using jis indexes.

(def-substitution-macro jis-string-substring (string start? end?)
  (lisp-string-substring
    string (if start? (twicef start?)) (if end? (twicef end?))))




;;; `Obtain-jis-string' makes a new jis string of length jis-string-length.

(defmacro obtain-jis-string (jis-string-length)
  `(obtain-lisp-string (twicef ,jis-string-length)))




;;; `Reclaim-jis-string' reclaims jis-string.

(defmacro reclaim-jis-string (jis-string)
  `(reclaim-lisp-string ,jis-string))




;;; `copy-jis-string' ...

(defmacro copy-jis-string (jis-string)
  `(copy-lisp-string ,jis-string))




;;; The macro `jis-string-length' returns the length of jis-string.

(defmacro jis-string-length (jis-string)
  `(halff (length ,jis-string)))





;;; `Jis-char' is used to access the kanji code at the position in jis-string
;;; specified by index.  Jis-char may be used with setf.  Jis-char is used in
;;; the same way as char except for the fact that it returns (or takes as an
;;; argument in the setf case) a fixnum integer JIS character code, which is
;;; to be compared using =f.

;;; Jis-gchar is to gchar as jis-char is to char; it is called with an extra
;;; argument, string-is-simple?, analogous to the arg of the same name in gchar.
;;; Unlike gchar at present, jis-gchar MAY be used with setf.

(def-substitution-macro jis-char (jis-string index)
  (let* ((base-index (twicef index)))
    (+f (ashf (char-int (char jis-string base-index)) 8)
	(char-int (char jis-string (+f base-index 1))))))

(def-substitution-macro jis-gchar (jis-string index string-is-simple?)
  (if string-is-simple?
      (let* ((base-index (twicef index)))
	(+f (ashf (char-int (schar jis-string base-index)) 8)
	    (char-int (schar jis-string (+f base-index 1)))))
      (jis-char jis-string index)))

(defsetf jis-char (jis-string index) (kanji-code)
  `(let* ((base-index (twicef ,index)))
     (setf (char ,jis-string base-index) (code-char (ashf ,kanji-code -8)))
     (setf (char ,jis-string (+f base-index 1))
	   (code-char (logandf ,kanji-code #.(- (ash 1 8) 1))))
     ,kanji-code))

(defsetf jis-gchar (jis-string index string-is-simple?) (kanji-code)
  `(if ,string-is-simple?
       (let* ((base-index (twicef ,index)))
	 (setf (schar ,jis-string base-index) (code-char (ashf ,kanji-code -8)))
	 (setf (schar ,jis-string (+f base-index 1))
	       (code-char (logandf ,kanji-code #.(- (ash 1 8) 1))))
	 ,kanji-code)
       (setf (jis-char ,jis-string ,index) ,kanji-code)))

;; Consider a setf method implementing setf method for jis-gchar.


;; Below is a function that is only in 2.1 which needs to be fixed there.
;; We don't bother with the optimization that requires this function anymore
;; -- but this code should replace its old code in 2.1!  Also, this never
;; returned the kanji code, which is not valid, but is not a problem in its
;; actual use.  (MHD 1/3/91)

;(defun setf-jis-char-from-jis-char-acessor
;       (jis-string index source-jis-string source-index)
;  (let* ((base-index (twicef index)))
;    (setf (char jis-string base-index)
;	  (char source-jis-string source-index))
;    (setf (char jis-string (+f base-index 1))
;	  (char source-jis-string (+f source-index 1)))))

;; If there were frequent occurences of the form
;;
;;    (setf (jis-char x y) (jis-char a b))
;;
;; that were in very time-critical spots, we could have a function like the one
;; above (commented out) that just moved the characters without having to
;; pack and then unpack a kanji code.  But there is no need for such a function
;; at present.  (MHD 1/3/91)




;;;; Miscellaneous String and Character functions







;;; `8th-bits-on' copies string into a new string with each character in the new
;;; string having its eight bit set.  The new string is of length length?, if that
;;; is specified, or of the same length as string, otherwise.  If length? is
;;; specified and is less than string's length, the string will be terminated with
;;; ascii "NUL" [(ascii-code-char 0)].

;;; Note: this function is intended for read-time or macro-expansion-time use only;
;;; it is not available at run-time.

(eval-when (:compile-toplevel :load-toplevel :execute)

(defun-for-macro 8th-bits-on (string &optional length?)	; for read-time only
  (loop with new-string
	  = (make-string
	      (or length? (length string))
	      :initial-element #.(ascii-code-char 0))
	for i from 0 below (length string)
	do (setf (char new-string i)
		 (ascii-code-char (logior 128 (ascii-char-code (char string i)))))
	finally
	  (return new-string)))

)


(defun-substitution-macro convert-simple-alpha-character-to-jis-code
                          (simple-character)
  (+f (convert-simple-character-to-ascii simple-character)
      #.(- #x2341 (convert-simple-character-to-ascii #\A))))



(defun-substitution-macro read-16-bit-big-endian-number-from-string
  			  (string start-index)
  (logiorf (ashf (ascii-char-code (char string start-index)) 8)
	   (ascii-char-code (char string (+f start-index 1)))))


(defmacro-for-constant most-positive-msb-of-fixnum (ash most-positive-fixnum -24))


(def-substitution-macro read-32-bit-big-endian-number-from-string-1
			(string start-index)
  (+ (+f (ashf (ascii-char-code (char string (+f start-index 1))) 16)
	 (ashf (ascii-char-code (char string (+f start-index 2))) 8)
	 (ascii-char-code (char string (+f start-index 3))))	; fixnum
     (ash (ascii-char-code (char string start-index)) 24)))	; bignum 

;; The above macro is just a common subexpression of the following two functions.
;; It is to be called in an appropriate bignum context.  It should remain a macro.


(defun read-32-bit-big-endian-number-from-string (string start-index)
  (with-permanent-bignum-creation
    (read-32-bit-big-endian-number-from-string-1 string start-index)))

(defun read-32-bit-big-endian-number-from-string-with-fixnum-limit
       (string start-index fixnum-limit)
  (with-temporary-bignum-creation
    (min 
      (read-32-bit-big-endian-number-from-string-1 string start-index)
      fixnum-limit)))


;;; `Strncmp' is the equivalent of the C function.
;;; (See Harbison & Steele, pp. 298)

(defun strncmp-function (string-1 string-2 n start-1 start-2)
  ;; limit-1 and limit-2 replaced length-1 and length-1 from G2 2.1.
  ;; If G2 2.1 is to be fixed, this function will supercede the one
  ;; in G2 2.1.
  (let* ((string-1-is-simple? (simple-gensym-string-p string-1))
	 (string-2-is-simple? (simple-gensym-string-p string-2))
	 (limit-1 (-f (glength string-1 string-1-is-simple?) start-1))
	 (limit-2 (-f (glength string-2 string-2-is-simple?) start-2))
	 char-1
	 char-2)
    (when (null n)
      (setq n (maxf limit-1 limit-2)))
    (loop for index from 0 below n
	  do
      (cond
	((>=f index limit-1)
	 (if (>=f index limit-2)
	     (return 0)
	     (return (-f (ascii-char-code (gchar string-2 (+f index start-2) string-2-is-simple?))))))
	((>=f index limit-2)		; index < limit-1
	 (return (ascii-char-code (gchar string-1 (+f index start-1) string-1-is-simple?))))
	(t
	 (setq char-1 (ascii-char-code (gchar string-1 (+f index start-1) string-1-is-simple?)))
	 (setq char-2 (ascii-char-code (gchar string-2 (+f index start-2) string-2-is-simple?)))
	 (cond
	   ((=f char-1 0)
	    (if (=f char-2 0)
		(return 0)
		(return (-f char-2))))
	   ((=f char-2 0)		; char-1 is not 0
	    (return char-1))
	   (t
	    (if (/=f char-1 char-2)
		(return (-f char-1 char-2)))))))
        finally
	  (return 0))))

(defmacro strncmp (string-1 string-2 n)
  `(strncmp-function ,string-1 ,string-2 ,n 0 0))

(defmacro strcmp (string-1 string-2)
  `(strncmp-function ,string-1 ,string-2 nil 0 0))







;;; Strcat ... is similar to the C function of the same name.

(defmacro strcat (string-1 string-2)
  `(strcat-1 ,string-1 ,string-2 0 0))


;;; Strcat-1 is like strcat, except that it treats offset-1 and offset-2
;;; as the beginning of string-1 and string-2, respectively, instead of 0.

(defun strcat-1 (string-1 string-2 offset-1 offset-2) ; like the C strcat
  (loop with string-1-is-simple? = (simple-gensym-string-p string-1)
	with string-2-is-simple? = (simple-gensym-string-p string-2)
	with length-of-string-1 = (glength string-1 string-1-is-simple?)
	with start-index = offset-1
	while (not (eql				; char= ??
		     (gchar string-1 start-index string-1-is-simple?)
		     #.(ascii-code-char 0)))
	do (incff start-index)
	finally
	  (loop for i from offset-2
		as j from start-index
		as character = (gchar string-2 i string-2-is-simple?)
		when (>= j length-of-string-1)
		  do (error "Index ~d is past the end of string ~s!" j string-1)
		do (if string-1-is-simple?	; need setf method for gchar!
		       (setf (schar string-1 j) character)
		       (setf (char string-1 j) character))
		until (eql character #.(ascii-code-char 0))))	; char= ??
  string-1)

;; Note: the error checking above should not be necessary, but costs little
;; enough; without it, this could "scribble" in memory, causing very hard-
;; to-find bugs, as it recently in fact did, costing a man-week of development
;; time. (MHD 1/3/91)




;;;; Numeric Operations for KFEP's bunbit datastructure


;;; The operations defined are /=k, logiork, and logandk, which are analogs of
;;; /=, logior, and logand, respectively.

;;; If kfep-number-of-bits-in-bunbits is greater than the number of bits
;;; in a fixnum, then generic artithmetic must be used.  In practice, this
;;; is only true on the TI Explorer.  For this reason, this arithmetic can
;;; cons on an Explorer!

(defmacro /=k (&rest args)
  `(,(if (> 27 (integer-length most-positive-fixnum))
	 '/=
	 '/=f)
    ,@args))

(defmacro logiork (&rest args)
  `(,(if (> 27 (integer-length most-positive-fixnum))
	 'logior
	 'logiorf)
    ,@args))

(defmacro logandk (&rest args)
  `(,(if (> 27 (integer-length most-positive-fixnum))
	 'logand
	 'logandf)
    ,@args))

;; Note that 27 is used above in place of kfep-number-of-bits-in-bunbits due
;; to a forward reference problem.







;;;; Additional G2 Streams Functions




;;; `G2-stream-read-32-bit-big-endian-number' ...  This can return nil if there
;;; is an end-of-file.  If number-limit?  is an integer, then the biggest number
;;; that this function will return is the min of the number read and
;;; number-limit?.  If require-fixnum? is true, and this function always returns
;;; a fixnum number no larger than most-positive-bignum.  Otherwise, this can
;;; return a permanent bignum.

(defun g2-stream-read-32-bit-big-endian-number (stream require-fixnum?)
  (let (char-1 char-2 char-3 char-4
	byte-1 byte-2 byte-3 byte-4)
    (when (and (setq char-1 (g2-stream-read-char stream))
	       (setq char-2 (g2-stream-read-char stream))
	       (setq char-3 (g2-stream-read-char stream))
	       (setq char-4 (g2-stream-read-char stream)))
      (setq byte-1 (ascii-char-code char-1)		; low byte, high word
	    byte-2 (ascii-char-code char-2)		; high byte, high word
	    byte-3 (ascii-char-code char-3)		; high byte, low word
	    byte-4 (ascii-char-code char-4))		; low byte, low word
      (if require-fixnum?
	  (with-temporary-bignum-creation
	    ;; The following had been coded as (min <arg1> <arg2>), but Chestnut
	    ;; had a bug that it got a bus error when MIN was called with a
	    ;; fixnum and a bignum.  JRA is reporting this.  The following
	    ;; recoding using logand is just as good, if not better, and works
	    ;; around that bug.  (MHD 12/3/91)
	    (logand
	      (+ (+f byte-4
		     (ashf byte-3 8)
		     (ashf byte-2 16))
		 (ash byte-1 24))
	      most-positive-fixnum))		; "most-positive-gensym-fixnum"?!
	  (with-permanent-bignum-creation
	    (+ (+f byte-4
		   (ashf byte-3 8)
		   (ashf byte-2 16))
	       (ash byte-1 24)))))))

;; In practice there are only two callers at present, and they both call this with
;; require-fixnum? = t.  Thus, there is can be no question of bignum leakage.
;; (MHD 12/3/91)





;;;; Start of Old KFEP2


;;;; KFEP Globals

;;; KFEP Constants
#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro-for-constant kfep-midxln 20)
(defmacro-for-constant kfep-bunsetumax 15)
(defmacro-for-constant kfep-bunmax 80)
(defmacro-for-constant kfep-master-header-size 13)
(defmacro-for-constant kfep-kojin-header-size 20)
(defmacro-for-constant kfep-pagesize 370)
(defmacro-for-constant kfep-tablesize 256)
(defmacro-for-constant kfep-m-table-size 370)
(defmacro-for-constant kfep-mastersize	9672) ;	/*sizeof (m_table) + 52 */
(defmacro-for-constant kfep-sel-hira 0)
(defmacro-for-constant kfep-sel-kana 1)
(defmacro-for-constant kfep-sel-kanji 2)
(defmacro-for-constant kfep-sel-none 3)
(defmacro-for-constant kfep-header (* kfep-master-header-size 4)) ; 4 is sizeof(int)
(defmacro-for-constant kfep-k-header (* kfep-kojin-header-size 4)) ; 4 is sizeof(int)
)








;; From kkausers.h
#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro-for-constant kfep-no-error 0)
(defmacro-for-constant kfep-yes-error -1)
(defmacro-for-constant kfep-eka-toolong 1)

(defmacro-for-constant kfep-kka-sinki		0)
(defmacro-for-constant kfep-kka-tugikouho	1)
(defmacro-for-constant kfep-kka-maekouho	2)
(defmacro-for-constant kfep-kka-hiragana	3)
(defmacro-for-constant kfep-kka-katakana	4)
(defmacro-for-constant kfep-kka-idou		5)
(defmacro-for-constant kfep-kka-bundec		6)
(defmacro-for-constant kfep-kka-buninc		7)
(defmacro-for-constant kfep-kka-allhira		8)
(defmacro-for-constant kfep-kka-allkana		9)
(defmacro-for-constant kfep-kka-allhan		10)

(defmacro-for-constant kfep-kka-nomal	0)
(defmacro-for-constant kfep-kka-nn	1)
(defmacro-for-constant kfep-kka-mini	2)
(defmacro-for-constant kfep-kka-kuto	3)
(defmacro-for-constant kfep-kka-misc	4)
)




;; From kkausers.h
#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro-for-constant kfep-bun-misc	1)
(defmacro-for-constant kfep-bun-meisu	2)
(defmacro-for-constant kfep-bun-meisi	3)
(defmacro-for-constant kfep-bun-godan	4)
(defmacro-for-constant kfep-bun-keiyo	5)
(defmacro-for-constant kfep-bun-keido	6)
(defmacro-for-constant kfep-bun-simo1	7)
(defmacro-for-constant kfep-bun-kami1	8)
(defmacro-for-constant kfep-bun-huku	9)
(defmacro-for-constant kfep-bun-settou	10)
(defmacro-for-constant kfep-bun-setubi	11)
(defmacro-for-constant kfep-bun-jyosi	12)
(defmacro-for-constant kfep-bun-jyodo	13)
(defmacro-for-constant kfep-bun-sahen	14)
(defmacro-for-constant kfep-bun-kahen	15)
(defmacro-for-constant kfep-bun-rentai	16)
(defmacro-for-constant kfep-bun-tanka	17)
(defmacro-for-constant kfep-bun-setu	18)
(defmacro-for-constant kfep-bun-kando	19)
(defmacro-for-constant kfep-bun-daimei	20)
(defmacro-for-constant kfep-bun-zougo	21)
(defmacro-for-constant kfep-bun-zokeido	22)
(defmacro-for-constant kfep-bun-suusi	23)


(defmacro-for-constant kfep-jyosi	0)
(defmacro-for-constant kfep-jyodou	1)
(defmacro-for-constant kfep-keiyo	2)
(defmacro-for-constant kfep-keido	3)

(defmacro-for-constant kfep-mizen	0)
(defmacro-for-constant kfep-renyou	1)
(defmacro-for-constant kfep-syuusi	2)
(defmacro-for-constant kfep-rentai	3)
(defmacro-for-constant kfep-katei	4)
(defmacro-for-constant kfep-meirei	5)
(defmacro-for-constant kfep-gokan	6)
(defmacro-for-constant kfep-undef	7)
)


#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)

(defmacro-for-constant kfep-gobisetu1-size 110)
(defmacro-for-constant kfep-gobisetu2-size 111)

)





;;; KFEP Defvars
(def-system-variable kfep-master-header KFEP1
  (:funcall make-array #.kfep-master-header-size))  ; array of int
(def-system-variable kfep-master-header-in-characters KFEP1
  (:funcall make-string #.kfep-header))
(def-system-variable kfep-kojin-header  KFEP1
  (:funcall make-array #.kfep-kojin-header-size))   ; array of integers
(def-system-variable kfep-tablemax KFEP1 0)
(def-system-variable kfep-m-table KFEP1 nil)		; array of kfep-master structures
(def-system-variable kfep-index-file-stream KFEP1)
(def-system-variable kfep-main-file-stream KFEP1)
(def-system-variable kfep-kojin-file-stream KFEP1)
(def-system-variable kfep-kojin-usedbits KFEP1)
(def-system-variable kfep-kojin-bunpobits KFEP1)
(def-system-variable kfep-kojin-index KFEP1)
(def-system-variable kfep-kojin-hyolen KFEP1)


;; u_char	batchyomi[BUNMAX];
;; struct batch battable[BUNSETUMAX];
;; int		batchyomilen;
;; int		kka_usetblnum;
(def-system-variable kfep-batchyomi KFEP1)	       ; string of length #.kfep-bunmax
(def-system-variable kfep-battable KFEP1 nil)	       ; array of kfep-batch structures
(def-system-variable kfep-batchyomilen KFEP1 0)	       ; integer
(def-system-variable kfep-kka-usetblnum KFEP1 0)       ; integer






;; acessors for bunindex "struct" -- implemented as a simple vector here.

(defmacro kfep-bunindex-length (kfep-bunindex)			; char
  `(svref ,kfep-bunindex 0))

(defmacro kfep-bunindex-start (kfep-bunindex)			; short
  `(svref ,kfep-bunindex 1))

(defmacro kfep-bunindex-end (kfep-bunindex)			; short
  `(svref ,kfep-bunindex 2))



;;; The macro `def-kfep-constant' is used to define constants used in the KFEP
;;; modules that are lists or arrays.  This may be read essentially like
;;; defconstant.  It's semantics are almost equivalent.  The only difference is
;;; that the result of evaluating the initial-value form will not be eq to the
;;; value of the constant; rather, a different, equal form will be created (at
;;; "load" time).

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro def-kfep-constant (name initial-value) ; doc string not needed
  `(defconstant ,name (optimize-constant ,initial-value)))
)
  

(progn

  ;; Franz ACL compile complained constants were being redefined when this progn
  ;; was (eval-when (:compile-toplevel :load-toplevel :execute) ...).  It looks like it needn't be,
  ;; which is why I've changed it to a progn. -mhd, 6/17/00
  
(def-kfep-constant kfep-ta-index
    '#(#(8   0    0)
       #(6   1    4)
       #(4   5   22)
       #(2  23   37)))

(def-kfep-constant kfep-sa-index
	     '#(#(8   0    3)
		#(6   4    8)
		#(4   9   13)
		#(2  14   14)))

(def-kfep-constant kfep-jd-index
	     '#(#(10    0    31)
		#( 8   32    78)
		#( 6   79   131)
		#( 4  132   155)
		#( 2  156   160)))

(def-kfep-constant kfep-jy-index
	     '#(#(8   0   0)
		#(6   1   5)
		#(4   6  21)
		#(2  22  34)))

(def-kfep-constant kfep-kk-index
	     '#(#(10   0   0)
		#( 8   1  13)
		#( 6  14  42)
		#( 4  43  66)
		#( 2  67  71)))
)

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro-for-constant kfep-taigenlen 4)	; <=> (length kfep-ta-index)
(defmacro-for-constant kfep-sahenlen 4)		; <=> (length kfep-sa-index)
(defmacro-for-constant kfep-jyodolen 5)		; <=> (length kfep-jd-index)
(defmacro-for-constant kfep-jyosilen 4)		; <=> (length kfep-jy-index)
(defmacro-for-constant kfep-keiyolen 5)		; <=> (length kfep-kk-index)
)








;;; KFEP C-Like Macros

(defmacro kfep-cur (n)
  `(svref kfep-battable ,n))

(defmacro kfep-p-maxval ()
  `(svref kfep-master-header 11))

(defmacro kfep-p-useval ()
  `(svref kfep-master-header 12))


(defmacro kfep-k-lock ()
  `(svref kfep-kojin-header 0))

(defmacro kfep-k-useyomi ()
  `(svref kfep-kojin-header 1))

(defmacro kfep-k-usebits ()
  `(svref kfep-kojin-header 2))

(defmacro kfep-k-hindex ()
  `(svref kfep-kojin-header 3))

(defmacro kfep-k-hyokisiz ()
  `(svref kfep-kojin-header 4))




;;; From kkajisho.h

(defun-substitution-macro kfep-hikakun-1 (a b n start-a start-b)
  (let* ((strncmp (strncmp-function a b n start-a start-b)))
    (if (=f strncmp 0)
      #.(ascii-char-code #\=)
      (if (>f strncmp 0)
	  #.(ascii-char-code #\>)
	  #.(ascii-char-code #\<)))))

(defun-substitution-macro kfep-hikaku-1 (a b start-a start-b)
  (let* ((strcmp (strncmp-function a b nil start-a start-b)))
    (if (=f strcmp 0)
      #.(ascii-char-code #\=)
      (if (>f strcmp 0)
	  #.(ascii-char-code #\>)
	  #.(ascii-char-code #\<)))))

(defmacro kfep-hikakun (a b n &optional (start-a 0) (start-b 0))
  `(kfep-hikakun-1 ,a ,b ,n ,start-a ,start-b))

(defmacro kfep-hikaku (a b &optional (start-a 0) (start-b 0))
  `(kfep-hikaku-1 ,a ,b ,start-a ,start-b))


;;; BUNBITS macros

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro-for-constant kfep-number-of-bits-in-bunbits 27)
)

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro kfep-all-bunbits () #.(- (ash 1 kfep-number-of-bits-in-bunbits) 1))
					; BIGNUM on TI's
)

(defmacro def-kfep-bunbit-accessor (name bit-position)
  (let* ((macro-name (intern (format nil "KFEP-BUNBIT-~a" name)))
	 (set-macro-name (intern (format nil "KFEP-BUNBIT-SET-~a" name)))
	 (clear-macro-name (intern (format nil "KFEP-BUNBIT-CLEAR-~a" name)))
	 (mask (ash 1 bit-position))
	 (inverse-mask (logxor mask (kfep-all-bunbits))))
    `(progn
       (def-substitution-macro ,macro-name (bunbit)
	 (/=k 0 (logandk ,mask bunbit)))
       (def-substitution-macro ,set-macro-name (bunbit)
	 (logiork ,mask bunbit))
       (def-substitution-macro ,clear-macro-name (bunbit)
	 (logandk ,inverse-mask bunbit)))))

(def-kfep-bunbit-accessor godan 00)
(def-kfep-bunbit-accessor shiti 01)
(def-kfep-bunbit-accessor siiti 02)
(def-kfep-bunbit-accessor sahen 03)
(def-kfep-bunbit-accessor kahen 04)
(def-kfep-bunbit-accessor dosmi 05)
(def-kfep-bunbit-accessor dosyo 06)
(def-kfep-bunbit-accessor dossy 07)
(def-kfep-bunbit-accessor dosta 08)
(def-kfep-bunbit-accessor doska 09)
(def-kfep-bunbit-accessor dosme 10)
(def-kfep-bunbit-accessor kyomi 11)
(def-kfep-bunbit-accessor kyoyo 12)
(def-kfep-bunbit-accessor kyosy 13)
(def-kfep-bunbit-accessor kyota 14)
(def-kfep-bunbit-accessor kyoka 15)
(def-kfep-bunbit-accessor kyome 16)
(def-kfep-bunbit-accessor kdomi 17)
(def-kfep-bunbit-accessor kdoyo 18)
(def-kfep-bunbit-accessor kdosy 19)
(def-kfep-bunbit-accessor kdota 20)
(def-kfep-bunbit-accessor kdoka 21)
(def-kfep-bunbit-accessor kdome 22)
(def-kfep-bunbit-accessor kyogo 23)
(def-kfep-bunbit-accessor kdogo 24)
(def-kfep-bunbit-accessor taign 25)
(def-kfep-bunbit-accessor meisa 26)
;(def-kfep-bunbit-accessor dum27 27)
;(def-kfep-bunbit-accessor dum28 28)
;(def-kfep-bunbit-accessor dum29 29)
;(def-kfep-bunbit-accessor dum30 30)
;(def-kfep-bunbit-accessor dum31 31)


;;; KFEP Structures

;;; The structure `kfep-master' is from ...

(def-structure (kfep-master)
  ;; Define reclaimer
  kfep-master-midashi			; string of length #.kfep-midxln
  kfep-master-offset			; string of length 4
  kfep-master-nbyte			; string of length 2
  )




;struct JJDKKD{
;	unsigned char	key[16];
;	int		hinsi;
;	int		katuyo;
;	bunbits	bunbun;
;};


;; acessors for jjdkkd-key "struct" -- implemented as a simple vector here.

(defmacro kfep-jjdkkd-key (kfep-jjdkkd)		; string of 16 characters
  `(svref ,kfep-jjdkkd 0))

(defmacro kfep-jjdkkd-hinsi (kfep-jjdkkd)	; int
  `(svref ,kfep-jjdkkd 1))

(defmacro kfep-jjdkkd-katuyo (kfep-jjdkkd)	; int
  `(svref ,kfep-jjdkkd 2))

(defmacro kfep-jjdkkd-bunbun (kfep-jjdkkd)	; bits
  `(svref ,kfep-jjdkkd 3))




;struct batch {
;	short			yomistpos;
;	short			yomilen;
;	unsigned char		*hyoki;
;	short			hyolen;
;	short			hukalen;
;	short			total;
;	short			entry;
;	short			current;
;	unsigned short		nofyomi;
;	char			select;
;	int			setuzoku;
;	struct JJDKKD		buntable;
;} ;
(def-structure (kfep-batch)
  ;; Define reclaimer
  kfep-batch-yomistpos
  kfep-batch-yomilen
  kfep-batch-hyoki
  kfep-batch-hyolen
  kfep-batch-hukalen
  kfep-batch-total
  kfep-batch-entry
  kfep-batch-current
  kfep-batch-nofyomi
  kfep-batch-select
  kfep-batch-setuzoku
  kfep-batch-buntable-key ; string of 16 characters
  kfep-batch-buntable-hinsi ; integer
  kfep-batch-buntable-katuyo ; integer
  kfep-batch-buntable-bunbun ; fixnum (on machines with 27 bits or more) - bunbits
  )



;; From kkabundef.h

;; acessors for gobitype "struct" -- implemented as a simple vector here.

(defmacro kfep-gobitype-gobi (kfep-gobitype)	; string (maximum 8 characters)
  `(svref ,kfep-gobitype 0))

(defmacro kfep-gobitype-katuyo (kfep-gobitype)	; int
  `(svref ,kfep-gobitype 1))

(defmacro kfep-gobitype-bogi (kfep-gobitype)	; int
  `(svref ,kfep-gobitype 2))








(def-kfep-constant kfep-gobisetu1
	     '#(#(#.(8th-bits-on "$+" 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$1" 8)	#.kfep-bun-GODAN #.kfep-MEIREI)
		#(#.(8th-bits-on "$3" 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$," 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$4" 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$5" 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$=" 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$?" 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$H" 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$J" 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$N" 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$P" 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$\\" 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$^" 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$b" 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$i" 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$m" 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$o" 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$*" 8)	#.kfep-bun-GODAN #.kfep-MIZEN)
		#(#.(8th-bits-on "$$" 8)	#.kfep-bun-KAMI1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$-" 8)	#.kfep-bun-KAMI1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$." 8)	#.kfep-bun-KAMI1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$8" 8)	#.kfep-bun-KAMI1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$A" 8)	#.kfep-bun-KAMI1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$K" 8)	#.kfep-bun-KAMI1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$R" 8)	#.kfep-bun-KAMI1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$S" 8)	#.kfep-bun-KAMI1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$_" 8)	#.kfep-bun-KAMI1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$j" 8)	#.kfep-bun-KAMI1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$(" 8)	#.kfep-bun-SIMO1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$1" 8)	#.kfep-bun-SIMO1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$2" 8)	#.kfep-bun-SIMO1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$;" 8)	#.kfep-bun-SIMO1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$<" 8)	#.kfep-bun-SIMO1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$F" 8)	#.kfep-bun-SIMO1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$G" 8)	#.kfep-bun-SIMO1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$M" 8)	#.kfep-bun-SIMO1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$X" 8)	#.kfep-bun-SIMO1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$Y" 8)	#.kfep-bun-SIMO1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$a" 8)	#.kfep-bun-SIMO1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$l" 8)	#.kfep-bun-SIMO1 #.kfep-MIZEN)
		#(#.(8th-bits-on "$C" 8)	#.kfep-bun-GODAN #.kfep-RENYOU)
		#(#.(8th-bits-on "$-" 8)	#.kfep-bun-GODAN #.kfep-RENYOU)
		#(#.(8th-bits-on "$$" 8)	#.kfep-bun-GODAN #.kfep-RENYOU)
		#(#.(8th-bits-on "$." 8)	#.kfep-bun-GODAN #.kfep-RENYOU)
		#(#.(8th-bits-on "$7" 8)	#.kfep-bun-GODAN #.kfep-RENYOU)
		#(#.(8th-bits-on "$A" 8)	#.kfep-bun-GODAN #.kfep-RENYOU)
		#(#.(8th-bits-on "$C" 8)	#.kfep-bun-GODAN #.kfep-RENYOU)
		#(#.(8th-bits-on "$K" 8)	#.kfep-bun-GODAN #.kfep-RENYOU)
		#(#.(8th-bits-on "$s" 8)	#.kfep-bun-GODAN #.kfep-RENYOU)
		#(#.(8th-bits-on "$S" 8)	#.kfep-bun-GODAN #.kfep-RENYOU)
		#(#.(8th-bits-on "$j" 8)	#.kfep-bun-GODAN #.kfep-RENYOU)
		#(#.(8th-bits-on "$$" 8)	#.kfep-bun-KAMI1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$-" 8)	#.kfep-bun-KAMI1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$." 8)	#.kfep-bun-KAMI1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$8" 8)	#.kfep-bun-KAMI1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$A" 8)	#.kfep-bun-KAMI1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$K" 8)	#.kfep-bun-KAMI1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$R" 8)	#.kfep-bun-KAMI1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$S" 8)	#.kfep-bun-KAMI1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$_" 8)	#.kfep-bun-KAMI1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$j" 8)	#.kfep-bun-KAMI1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$(" 8)	#.kfep-bun-SIMO1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$1" 8)	#.kfep-bun-SIMO1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$2" 8)	#.kfep-bun-SIMO1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$;" 8)	#.kfep-bun-SIMO1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$<" 8)	#.kfep-bun-SIMO1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$F" 8)	#.kfep-bun-SIMO1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$G" 8)	#.kfep-bun-SIMO1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$M" 8)	#.kfep-bun-SIMO1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$X" 8)	#.kfep-bun-SIMO1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$Y" 8)	#.kfep-bun-SIMO1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$a" 8)	#.kfep-bun-SIMO1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$l" 8)	#.kfep-bun-SIMO1 #.kfep-RENYOU)
		#(#.(8th-bits-on "$/" 8)	#.kfep-bun-GODAN #.kfep-SYUUSI)
		#(#.(8th-bits-on "$0" 8)	#.kfep-bun-GODAN #.kfep-SYUUSI)
		#(#.(8th-bits-on "$9" 8)	#.kfep-bun-GODAN #.kfep-SYUUSI)
		#(#.(8th-bits-on "$D" 8)	#.kfep-bun-GODAN #.kfep-SYUUSI)
		#(#.(8th-bits-on "$L" 8)	#.kfep-bun-GODAN #.kfep-SYUUSI)
		#(#.(8th-bits-on "$V" 8)	#.kfep-bun-GODAN #.kfep-SYUUSI)
		#(#.(8th-bits-on "$`" 8)	#.kfep-bun-GODAN #.kfep-SYUUSI)
		#(#.(8th-bits-on "$k" 8)	#.kfep-bun-GODAN #.kfep-SYUUSI)
		#(#.(8th-bits-on "$&" 8)	#.kfep-bun-GODAN #.kfep-SYUUSI)
		#(#.(8th-bits-on "$/" 8)	#.kfep-bun-GODAN #.kfep-RENTAI)
		#(#.(8th-bits-on "$0" 8)	#.kfep-bun-GODAN #.kfep-RENTAI)
		#(#.(8th-bits-on "$9" 8)	#.kfep-bun-GODAN #.kfep-RENTAI)
		#(#.(8th-bits-on "$D" 8)	#.kfep-bun-GODAN #.kfep-RENTAI)
		#(#.(8th-bits-on "$L" 8)	#.kfep-bun-GODAN #.kfep-RENTAI)
		#(#.(8th-bits-on "$V" 8)	#.kfep-bun-GODAN #.kfep-RENTAI)
		#(#.(8th-bits-on "$`" 8)	#.kfep-bun-GODAN #.kfep-RENTAI)
		#(#.(8th-bits-on "$k" 8)	#.kfep-bun-GODAN #.kfep-RENTAI)
		#(#.(8th-bits-on "$&" 8)	#.kfep-bun-GODAN #.kfep-RENTAI)
		#(#.(8th-bits-on "$1" 8)	#.kfep-bun-GODAN #.kfep-KATEI)
		#(#.(8th-bits-on "$2" 8)	#.kfep-bun-GODAN #.kfep-KATEI)
		#(#.(8th-bits-on "$;" 8)	#.kfep-bun-GODAN #.kfep-KATEI)
		#(#.(8th-bits-on "$F" 8)	#.kfep-bun-GODAN #.kfep-KATEI)
		#(#.(8th-bits-on "$M" 8)	#.kfep-bun-GODAN #.kfep-KATEI)
		#(#.(8th-bits-on "$Y" 8)	#.kfep-bun-GODAN #.kfep-KATEI)
		#(#.(8th-bits-on "$a" 8)	#.kfep-bun-GODAN #.kfep-KATEI)
		#(#.(8th-bits-on "$l" 8)	#.kfep-bun-GODAN #.kfep-KATEI)
		#(#.(8th-bits-on "$(" 8)	#.kfep-bun-GODAN #.kfep-KATEI)
		#(#.(8th-bits-on "$2" 8)	#.kfep-bun-GODAN #.kfep-MEIREI)
		#(#.(8th-bits-on "$;" 8)	#.kfep-bun-GODAN #.kfep-MEIREI)
		#(#.(8th-bits-on "$F" 8)	#.kfep-bun-GODAN #.kfep-MEIREI)
		#(#.(8th-bits-on "$M" 8)	#.kfep-bun-GODAN #.kfep-MEIREI)
		#(#.(8th-bits-on "$Y" 8)	#.kfep-bun-GODAN #.kfep-MEIREI)
		#(#.(8th-bits-on "$a" 8)	#.kfep-bun-GODAN #.kfep-MEIREI)
		#(#.(8th-bits-on "$l" 8)	#.kfep-bun-GODAN #.kfep-MEIREI)
		#(#.(8th-bits-on "$(" 8)	#.kfep-bun-GODAN #.kfep-MEIREI)
		nil))				; "nul terminated" ?


(def-kfep-constant kfep-gobisetu2
	     '#(#(#.(8th-bits-on "$$$k" 8)	#.kfep-bun-KAMI1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$-$k" 8)	#.kfep-bun-KAMI1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$.$k" 8)	#.kfep-bun-KAMI1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$8$k" 8)	#.kfep-bun-KAMI1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$A$k" 8)	#.kfep-bun-KAMI1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$K$k" 8)	#.kfep-bun-KAMI1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$R$k" 8)	#.kfep-bun-KAMI1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$S$k" 8)	#.kfep-bun-KAMI1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$_$k" 8)	#.kfep-bun-KAMI1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$j$k" 8)	#.kfep-bun-KAMI1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$($k" 8)	#.kfep-bun-SIMO1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$1$k" 8)	#.kfep-bun-SIMO1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$2$k" 8)	#.kfep-bun-SIMO1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$;$k" 8)	#.kfep-bun-SIMO1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$<$k" 8)	#.kfep-bun-SIMO1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$F$k" 8)	#.kfep-bun-SIMO1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$G$k" 8)	#.kfep-bun-SIMO1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$M$k" 8)	#.kfep-bun-SIMO1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$X$k" 8)	#.kfep-bun-SIMO1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$Y$k" 8)	#.kfep-bun-SIMO1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$a$k" 8)	#.kfep-bun-SIMO1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$l$k" 8)	#.kfep-bun-SIMO1 #.kfep-SYUUSI)
		#(#.(8th-bits-on "$$$k" 8)	#.kfep-bun-KAMI1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$-$k" 8)	#.kfep-bun-KAMI1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$.$k" 8)	#.kfep-bun-KAMI1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$8$k" 8)	#.kfep-bun-KAMI1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$A$k" 8)	#.kfep-bun-KAMI1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$K$k" 8)	#.kfep-bun-KAMI1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$R$k" 8)	#.kfep-bun-KAMI1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$S$k" 8)	#.kfep-bun-KAMI1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$_$k" 8)	#.kfep-bun-KAMI1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$j$k" 8)	#.kfep-bun-KAMI1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$($k" 8)	#.kfep-bun-SIMO1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$1$k" 8)	#.kfep-bun-SIMO1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$2$k" 8)	#.kfep-bun-SIMO1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$;$k" 8)	#.kfep-bun-SIMO1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$<$k" 8)	#.kfep-bun-SIMO1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$F$k" 8)	#.kfep-bun-SIMO1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$G$k" 8)	#.kfep-bun-SIMO1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$M$k" 8)	#.kfep-bun-SIMO1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$X$k" 8)	#.kfep-bun-SIMO1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$Y$k" 8)	#.kfep-bun-SIMO1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$a$k" 8)	#.kfep-bun-SIMO1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$l$k" 8)	#.kfep-bun-SIMO1 #.kfep-RENTAI)
		#(#.(8th-bits-on "$$$l" 8)	#.kfep-bun-KAMI1 #.kfep-KATEI)
		#(#.(8th-bits-on "$-$l" 8)	#.kfep-bun-KAMI1 #.kfep-KATEI)
		#(#.(8th-bits-on "$.$l" 8)	#.kfep-bun-KAMI1 #.kfep-KATEI)
		#(#.(8th-bits-on "$8$l" 8)	#.kfep-bun-KAMI1 #.kfep-KATEI)
		#(#.(8th-bits-on "$A$l" 8)	#.kfep-bun-KAMI1 #.kfep-KATEI)
		#(#.(8th-bits-on "$K$l" 8)	#.kfep-bun-KAMI1 #.kfep-KATEI)
		#(#.(8th-bits-on "$R$l" 8)	#.kfep-bun-KAMI1 #.kfep-KATEI)
		#(#.(8th-bits-on "$S$l" 8)	#.kfep-bun-KAMI1 #.kfep-KATEI)
		#(#.(8th-bits-on "$_$l" 8)	#.kfep-bun-KAMI1 #.kfep-KATEI)
		#(#.(8th-bits-on "$j$l" 8)	#.kfep-bun-KAMI1 #.kfep-KATEI)
		#(#.(8th-bits-on "$($l" 8)	#.kfep-bun-SIMO1 #.kfep-KATEI)
		#(#.(8th-bits-on "$1$l" 8)	#.kfep-bun-SIMO1 #.kfep-KATEI)
		#(#.(8th-bits-on "$2$l" 8)	#.kfep-bun-SIMO1 #.kfep-KATEI)
		#(#.(8th-bits-on "$;$l" 8)	#.kfep-bun-SIMO1 #.kfep-KATEI)
		#(#.(8th-bits-on "$<$l" 8)	#.kfep-bun-SIMO1 #.kfep-KATEI)
		#(#.(8th-bits-on "$F$l" 8)	#.kfep-bun-SIMO1 #.kfep-KATEI)
		#(#.(8th-bits-on "$G$l" 8)	#.kfep-bun-SIMO1 #.kfep-KATEI)
		#(#.(8th-bits-on "$M$l" 8)	#.kfep-bun-SIMO1 #.kfep-KATEI)
		#(#.(8th-bits-on "$X$l" 8)	#.kfep-bun-SIMO1 #.kfep-KATEI)
		#(#.(8th-bits-on "$Y$l" 8)	#.kfep-bun-SIMO1 #.kfep-KATEI)
		#(#.(8th-bits-on "$a$l" 8)	#.kfep-bun-SIMO1 #.kfep-KATEI)
		#(#.(8th-bits-on "$l$l" 8)	#.kfep-bun-SIMO1 #.kfep-KATEI)
		#(#.(8th-bits-on "$$$m" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$-$m" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$.$m" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$8$m" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$A$m" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$K$m" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$R$m" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$S$m" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$_$m" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$j$m" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$$$h" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$-$h" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$.$h" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$8$h" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$A$h" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$K$h" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$R$h" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$S$h" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$_$h" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$j$h" 8)	#.kfep-bun-KAMI1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$($m" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$1$m" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$2$m" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$;$m" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$<$m" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$F$m" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$G$m" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$M$m" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$X$m" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$Y$m" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$($h" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$1$h" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$2$h" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$;$h" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$<$h" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$F$h" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$G$h" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$M$h" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$X$h" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$Y$h" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$a$m" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$l$m" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$a$h" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		#(#.(8th-bits-on "$l$h" 8)	#.kfep-bun-SIMO1 #.kfep-MEIREI)
		nil))				; "nul terminated" ?



(def-kfep-constant kfep-jyodou-array
	     '#(#(#.(8th-bits-on "$5$;$k$3$H" 16)	1 3 #b00000000000000000000000000111110)
		#(#.(8th-bits-on "$5$;$k$H$-" 16)	1 3 #b00000000000000000000000000111110)
		#(#.(8th-bits-on "$5$;$k$N$G" 16)	1 3 #b00000000000000000000000000111110)
		#(#.(8th-bits-on "$5$;$k$N$K" 16)	1 3 #b00000000000000000000000000111110)
		#(#.(8th-bits-on "$=$&$@$C$?" 16)	1 1 #b00000000100010000010000011011111)
		#(#.(8th-bits-on "$=$&$@$m$&" 16)	1 0 #b00000000100010000010000011011111)
		#(#.(8th-bits-on "$=$&$G$\"$k" 16)	1 1 #b00000000100010000010000011011111)
		#(#.(8th-bits-on "$=$&$J$3$H" 16)	1 3 #b00000000100010000010000011011111)
		#(#.(8th-bits-on "$=$&$J$H$-" 16)	1 3 #b00000000100010000010000011011111)
		#(#.(8th-bits-on "$=$&$J$N$G" 16)	1 3 #b00000000100010000010000011011111)
		#(#.(8th-bits-on "$=$&$J$N$K" 16)	1 3 #b00000000100010000010000011011111)
		#(#.(8th-bits-on "$=$&$J$i$P" 16)	1 4 #b00000000100010000010000011011111)
		#(#.(8th-bits-on "$=$&$K$J$k" 16)	1 1 #b00000000100010000010000011011111)
		#(#.(8th-bits-on "$h$&$@$C$?" 16)	1 1 #b00000000000100000100000100011111)
		#(#.(8th-bits-on "$h$&$@$m$&" 16)	1 0 #b00000000000100000100000100011111)
		#(#.(8th-bits-on "$h$&$G$\"$k" 16)	1 1 #b00000000000100000100000100011111)
		#(#.(8th-bits-on "$h$&$J$3$H" 16)	1 3 #b00000000000100000100000100011111)
		#(#.(8th-bits-on "$h$&$J$H$-" 16)	1 3 #b00000000000100000100000100011111)
		#(#.(8th-bits-on "$h$&$J$N$G" 16)	1 3 #b00000000000100000100000100011111)
		#(#.(8th-bits-on "$h$&$J$N$K" 16)	1 3 #b00000000000100000100000100011111)
		#(#.(8th-bits-on "$h$&$J$i$P" 16)	1 4 #b00000000000100000100000100011111)
		#(#.(8th-bits-on "$h$&$K$J$k" 16)	1 1 #b00000000000100000100000100011111)
		#(#.(8th-bits-on "$i$7$$$3$H" 16)	1 3 #b00000011000000000010000010011111)
		#(#.(8th-bits-on "$i$7$$$H$-" 16)	1 3 #b00000011000000000010000010011111)
		#(#.(8th-bits-on "$i$7$$$N$G" 16)	1 3 #b00000011000000000010000010011111)
		#(#.(8th-bits-on "$i$7$$$N$K" 16)	1 3 #b00000011000000000010000010011111)
		#(#.(8th-bits-on "$i$7$+$C$?" 16)	1 1 #b00000011000000000010000010011111)
		#(#.(8th-bits-on "$i$7$1$l$P" 16)	1 4 #b00000011000000000010000010011111)
		#(#.(8th-bits-on "$i$l$k$3$H" 16)	1 3 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$i$l$k$H$-" 16)	1 3 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$i$l$k$N$G" 16)	1 3 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$i$l$k$N$K" 16)	1 3 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$5$;$J$$" 16)	1 0 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$5$;$^$9" 16)	1 1 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$5$;$k;~" 16)	1 0 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$5$;$l$P" 16)	1 4 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$;$k$3$H" 16)	1 3 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$;$k$H$-" 16)	1 3 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$;$k$N$G" 16)	1 3 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$;$k$N$K" 16)	1 3 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$=$&$J$i" 16)	1 3 #b00000000100000000000000001011111)
		#(#.(8th-bits-on "$=$&$J;~" 16)	1 3 #b00000000100000000000000001011111)
		#(#.(8th-bits-on "$?$$$3$H" 16)	1 3 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$?$$$H$-" 16)	1 3 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$?$$$N$G" 16)	1 3 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$?$$$N$K" 16)	1 3 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$?$+$C$?" 16)	1 1 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$?$+$m$&" 16)	1 0 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$?$/$J$$" 16)	1 0 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$?$1$l$P" 16)	1 4 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$G$9$3$H" 16)	1 3 #b00000001000000000010000010011111)
		#(#.(8th-bits-on "$G$9$H$-" 16)	1 3 #b00000001000000000010000010011111)
		#(#.(8th-bits-on "$G$9$N$G" 16)	1 3 #b00000001000000000010000010011111)
		#(#.(8th-bits-on "$G$9$N$K" 16)	1 3 #b00000001000000000010000010011111)
		#(#.(8th-bits-on "$J$$$3$H" 16)	1 3 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$J$$$H$-" 16)	1 3 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$J$$$N$G" 16)	1 3 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$J$$$N$K" 16)	1 3 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$J$+$C$?" 16)	1 1 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$J$+$m$&" 16)	1 0 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$J$/$J$k" 16)	1 1 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$J$1$l$P" 16)	1 4 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$^$7$g$&" 16)	1 0 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$^$9$3$H" 16)	1 3 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$^$9$H$-" 16)	1 3 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$^$9$N$G" 16)	1 3 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$^$9$N$K" 16)	1 3 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$^$9$l$P" 16)	1 4 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$h$&$J$i" 16)	1 4 #b00000000000100000100000100011111)
		#(#.(8th-bits-on "$h$&$J;~" 16)	1 3 #b00000000000100000100000100011111)
		#(#.(8th-bits-on "$i$7$$;~" 16)	1 3 #b00000010000000000010000010011111)
		#(#.(8th-bits-on "$i$l$J$$" 16)	1 0 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$i$l$^$9" 16)	1 1 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$i$l$k;~" 16)	1 3 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$i$l$l$P" 16)	1 4 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$l$k$3$H" 16)	1 3 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$l$k$H$-" 16)	1 3 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$l$k$N$G" 16)	1 3 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$l$k$N$K" 16)	1 3 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$&$3$H" 16)	1 3 #b00000000000000000000000000100001)
		#(#.(8th-bits-on "$&$H$-" 16)	1 3 #b00000000000000000000000000100001)
		#(#.(8th-bits-on "$&$N$G" 16)	1 3 #b00000000000000000000000000100001)
		#(#.(8th-bits-on "$&$N$K" 16)	1 3 #b00000000000000000000000000100001)
		#(#.(8th-bits-on "$5$;$?" 16)	1 1 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$5$;$h" 16)	1 5 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$5$;$k" 16)	1 2 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$5$;$m" 16)	1 5 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$;$J$$" 16)	1 0 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$;$^$9" 16)	1 1 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$;$k;~" 16)	1 0 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$;$l$P" 16)	1 4 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$=$&$@" 16)	1 2 #b00000000000100000100000101011111)
		#(#.(8th-bits-on "$=$&$J" 16)	1 3 #b00000000000100000100000101011111)
		#(#.(8th-bits-on "$?$$;~" 16)	1 3 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$?$3$H" 16)	1 3 #b00000000000001000001000001011111)
		#(#.(8th-bits-on "$?$H$-" 16)	1 3 #b00000000000001000001000001011111)
		#(#.(8th-bits-on "$?$N$G" 16)	1 3 #b00000000000001000001000001011111)
		#(#.(8th-bits-on "$?$N$K" 16)	1 3 #b00000000000001000001000001011111)
		#(#.(8th-bits-on "$?$i$P" 16)	1 4 #b00000000000001000001000001011111)
		#(#.(8th-bits-on "$?$m$&" 16)	1 0 #b00000000000001000001000001011111)
		#(#.(8th-bits-on "$@$C$?" 16)	1 1 #b00000000000001000000000000000000)
		#(#.(8th-bits-on "$@$m$&" 16)	1 0 #b00000000000000100000000000000000)
		#(#.(8th-bits-on "$G$\"$k" 16)	1 1 #b00000000000001000000000000000000)
		#(#.(8th-bits-on "$G$7$?" 16)	1 1 #b00000000000001000000000000000000)
		#(#.(8th-bits-on "$G$9;~" 16)	1 3 #b00000000000001000000000000000000)
		#(#.(8th-bits-on "$J$$;~" 16)	1 3 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$J$3$H" 16)	1 3 #b00000000000100000000000000000000)
		#(#.(8th-bits-on "$J$H$-" 16)	1 3 #b00000000000100000000000000000000)
		#(#.(8th-bits-on "$J$N$G" 16)	1 3 #b00000000000100000000000000000000)
		#(#.(8th-bits-on "$J$N$K" 16)	1 3 #b00000000000100000000000000000000)
		#(#.(8th-bits-on "$J$i$P" 16)	1 4 #b00000000001000000000000000000000)
		#(#.(8th-bits-on "$L$3$H" 16)	1 3 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$L$H$-" 16)	1 3 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$L$N$G" 16)	1 3 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$L$N$K" 16)	1 3 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$^$7$?" 16)	1 1 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$^$9;~" 16)	1 3 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$h$&$@" 16)	1 2 #b00000000000100000100000100011111)
		#(#.(8th-bits-on "$h$&$J" 16)	1 1 #b00000000000100000100000100011111)
		#(#.(8th-bits-on "$i$7$$" 16)	1 2 #b00000001000000000010000010011111)
		#(#.(8th-bits-on "$i$l$?" 16)	1 1 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$i$l$h" 16)	1 5 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$i$l$k" 16)	1 2 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$i$l$m" 16)	1 5 #b00000000000000000000000000110110)
		#(#.(8th-bits-on "$l$J$$" 16)	1 0 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$l$^$9" 16)	1 1 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$l$k;~" 16)	1 3 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$l$l$P" 16)	1 4 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$s$3$H" 16)	1 0 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$s$H$-" 16)	1 3 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$s$N$G" 16)	1 3 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$s$N$K" 16)	1 3 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$&;~" 16)	1 3 #b00000000000000100000100000100001)
		#(#.(8th-bits-on "$;$?" 16)	1 1 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$;$h" 16)	1 5 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$;$k" 16)	1 2 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$;$m" 16)	1 5 #b00000000000000000000000000101001)
		#(#.(8th-bits-on "$?$$" 16)	1 2 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$?$i" 16)	1 4 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$?;~" 16)	1 3 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$G$9" 16)	1 2 #b00000001000000000010000010011111)
		#(#.(8th-bits-on "$J$$" 16)	1 2 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$J$i" 16)	1 4 #b00000000001000000000000000000000)
		#(#.(8th-bits-on "$J;~" 16)	1 3 #b00000000001000000000000000000000)
		#(#.(8th-bits-on "$L;~" 16)	1 3 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$M$P" 16)	1 4 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$^$$" 16)	1 2 #b00000000000000000000000010111111)
		#(#.(8th-bits-on "$^$7" 16)	1 5 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$^$9" 16)	1 1 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$^$;" 16)	1 5 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$h$&" 16)	1 2 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$l$?" 16)	1 1 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$l$h" 16)	1 5 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$l$k" 16)	1 2 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$l$m" 16)	1 5 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$s;~" 16)	1 3 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$&" 16)	1 2 #b00000000000000100000100000100001)
		#(#.(8th-bits-on "$?" 16)	1 2 #b00000000000000000000000001011111)
		#(#.(8th-bits-on "$@" 16)	1 2 #b00000000000000000010000010011111)
		#(#.(8th-bits-on "$L" 16)	1 2 #b00000000000000000000000000111111)
		#(#.(8th-bits-on "$s" 16)	1 2 #b00000000000000000000000000000000)))

(def-kfep-constant kfep-jyosi-array
	     '#(#(#.(8th-bits-on "$@$C$F$b" 16)	0 7 #b00000000000001000001000001000000)
		#(#.(8th-bits-on "$/$i$$" 16)	0 7 #b00000000000100000100000100000000)
		#(#.(8th-bits-on "$0$i$$" 16)	0 7 #b00000000000100000100000100000000)
		#(#.(8th-bits-on "$@$C$F" 16)	0 7 #b00000000000001000001000001000000)
		#(#.(8th-bits-on "$J$,$i" 16)	0 7 #b00000000000000000010000000000000)
		#(#.(8th-bits-on "$P$+$j" 16)	0 7 #b00000000000100000100000100000000)
		#(#.(8th-bits-on "$+$i" 16)	0 7 #b00000000000010000010000010000000)
		#(#.(8th-bits-on "$-$j" 16)	0 7 #b00000000000100000100000100000000)
		#(#.(8th-bits-on "$.$j" 16)	0 7 #b00000000000100000100000100000000)
		#(#.(8th-bits-on "$3$=" 16)	0 7 #b00000000000100000100000100000000)
		#(#.(8th-bits-on "$5$(" 16)	0 7 #b00000000000100000100000100000000)
		#(#.(8th-bits-on "$7$+" 16)	0 7 #b00000000000001000001000000000000)
		#(#.(8th-bits-on "$@$1" 16)	0 7 #b00000000000100000100000100000000)
		#(#.(8th-bits-on "$@$N" 16)	0 7 #b00000000000010000010000010000000)
		#(#.(8th-bits-on "$G$b" 16)	0 7 #b00000000000001000001000001000000)
		#(#.(8th-bits-on "$J$I" 16)	0 7 #b00000000000010000010000010000000)
		#(#.(8th-bits-on "$M$(" 16)	0 7 #b00000000000010000010000010000000)
		#(#.(8th-bits-on "$[$+" 16)	0 7 #b00000000000001000001000000000000)
		#(#.(8th-bits-on "$[$I" 16)	0 7 #b00000000000100000100000100000000)
		#(#.(8th-bits-on "$^$G" 16)	0 7 #b00000110000100000100000100000000)
		#(#.(8th-bits-on "$d$i" 16)	0 7 #b00000110000010000010000010000000)
		#(#.(8th-bits-on "$h$j" 16)	0 7 #b00000110000100000100000100000000)
		#(#.(8th-bits-on "$+" 16)	0 7 #b00000000000010000010000010000000)
		#(#.(8th-bits-on "$," 16)	0 7 #b00000110000010000010000010000000)
		#(#.(8th-bits-on "$5" 16)	0 7 #b00000110000010000010000010000000)
		#(#.(8th-bits-on "$G" 16)	0 7 #b00000110000001000001000001000000)
		#(#.(8th-bits-on "$H" 16)	0 7 #b00000110000001000001000001000000)
		#(#.(8th-bits-on "$K" 16)	0 7 #b00000110000100000100000100000000)
		#(#.(8th-bits-on "$M" 16)	0 7 #b00000000000010000010000010000000)
		#(#.(8th-bits-on "$N" 16)	0 7 #b00000110000100000100000100000000)
		#(#.(8th-bits-on "$O" 16)	0 7 #b00000110000001000001000001000000)
		#(#.(8th-bits-on "$P" 16)	0 7 #b00000000001000001000001000000000)
		#(#.(8th-bits-on "$b" 16)	0 7 #b00000110000001000001000001000000)
		#(#.(8th-bits-on "$h" 16)	0 7 #b00000000000010000010000010000000)
		#(#.(8th-bits-on "$r" 16)	0 7 #b00000110000100000100000100000000)))

(def-kfep-constant kfep-keiyo-array
	     '#(#(#.(8th-bits-on "$@$1$l$G$b" 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$$$/$i$$" 16)	2 3 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$$$1$l$I" 16)	2 2 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$$$=$&$@" 16)	2 2 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$$$G$7$g" 16)	2 2 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$$$i$7$$" 16)	2 2 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$+$C$?$j" 16)	2 1 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$@$1$l$I" 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$=$&$@" 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$C$?$j" 16)	3 1 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$C$F$b" 16)	3 1 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$J$/$i$$" 16)	3 3 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$J$P$+$j" 16)	3 3 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$J$h$&$@" 16)	3 3 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$$$+$i" 16)	2 2 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$$$@$1" 16)	2 3 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$$$@$m" 16)	2 2 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$$$J$i" 16)	2 2 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$$$N$G" 16)	2 3 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$$$N$K" 16)	2 3 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$+$C$?" 16)	2 1 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$+$m$&" 16)	2 0 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$/$\"$k" 16)	2 1 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$/$5$(" 16)	2 1 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$/$F$b" 16)	2 1 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$/$J$$" 16)	2 1 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$1$l$P" 16)	2 4 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$=$&$@" 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$+$i" 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$3$H" 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$C$?" 16)	3 1 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$C$F" 16)	3 1 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$J$\"" 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$b$N" 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$m$&" 16)	3 0 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$G$5$(" 16)	3 1 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$J$@$1" 16)	3 3 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$J$N$G" 16)	3 3 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$J$N$K" 16)	3 3 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$J$[$I" 16)	3 3 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$J$^$G" 16)	3 3 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$J$i$P" 16)	3 4 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$i$7$$" 16)	3 6 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$$$+" 16)	2 2 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$$$," 16)	2 2 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$$$7" 16)	2 2 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$$$H" 16)	2 2 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$$$J" 16)	2 2 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$$$M" 16)	2 2 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$$$N" 16)	2 3 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$$$h" 16)	2 2 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$/$F" 16)	2 1 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$@$," 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$5" 16)	3 6 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$7" 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$<" 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$>" 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$H" 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$J" 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$M" 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$h" 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$@$o" 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$G$9" 16)	3 6 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$G$O" 16)	3 1 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$G$b" 16)	3 1 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$J$N" 16)	3 3 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$J$i" 16)	3 4 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$$" 16)	2 2 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$/" 16)	2 2 #b00000000000000011111100000000000)
		#(#.(8th-bits-on "$G" 16)	3 1 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$J" 16)	3 2 #b00000000000000000000000000000000)
		#(#.(8th-bits-on "$K" 16)	3 1 #b00000000000000000000000000000000)))

(def-kfep-constant kfep-taigen-array
	     '#(#(#.(8th-bits-on "$@$C$F$b" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$@$C$F" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$i$7$$" 16)	1 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$P$+$j" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$/$i$$" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$,$i" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$3$=" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$5$(" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$G$9" 16)	1 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$G$b" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$7$+" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$[$+" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$^$G" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$@$1" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$[$I" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$:$D" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$-$j" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$J$I" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$d$i" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$M$(" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$@$N" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$+$i" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$h$j" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$," 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$N" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$r" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$K" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$X" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$@" 16)	1 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$H" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$G" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$d" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$O" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$+" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$h" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$M" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$b" 16)	0 7 #b00000110000000000000000000000000)
		#(#.(8th-bits-on "$5" 16)	0 7 #b00000110000000000000000000000000)))

(def-kfep-constant kfep-sahen-array
	     '#(#(#.(8th-bits-on "$5$;$J$$" 8)	0 7 #b00000100000000000000000000001000)
		#(#.(8th-bits-on "$5$;$h$&" 8)	0 7 #b00000100000000000000000000001000)
		#(#.(8th-bits-on "$9$k$H$-" 8)	0 7 #b00000100000000000000000000001000)
		#(#.(8th-bits-on "$7$^$7$?" 8)	0 7 #b00000100000000000000000000001000)
		#(#.(8th-bits-on "$7$^$9" 8)	0 7 #b00000100000000000000000000001000)
		#(#.(8th-bits-on "$7$h$&" 8)	1 7 #b00000100000000000000000000001000)
		#(#.(8th-bits-on "$9$l$P" 8)	1 7 #b00000100000000000000000000001000)
		#(#.(8th-bits-on "$7$J$$" 8)	0 7 #b00000100000000000000000000001000)
		#(#.(8th-bits-on "$7$F$?" 8)	0 7 #b00000100000000000000000000001000)
		#(#.(8th-bits-on "$7$F" 8)	0 7 #b00000100000000000000000000001000)
		#(#.(8th-bits-on "$7$?" 8)	0 7 #b00000100000000000000000000001000)
		#(#.(8th-bits-on "$9$k" 8)	0 7 #b00000100000000000000000000001000)
		#(#.(8th-bits-on "$7$m" 8)	0 7 #b00000100000000000000000000001000)
		#(#.(8th-bits-on "$;$h" 8)	0 7 #b00000100000000000000000000001000)
		#(#.(8th-bits-on "$7" 8)	0 7 #b00000100000000000000000000001000)
		#(#.(8th-bits-on "" 8)	0 0 #b00000000000000000000000000000000)))



;;;; KFEP Functions




;;;; KFEP Initialization



#+development
(defparameter initialize-kfep-regardless? nil)


;;; Turn-japanese .... One defect: if not called within a G2 process,
;;; current-language of language-parameters remains english.  

#+development
(defun turn-japanese (&optional off?)
  (declare (ignore off?))
  ;; Recompute-true-size-for-characters? is now removed.  Needs work.
  ;; See ma:>mhd>ab>hfep-todo.text. (MHD 10/19/92)
  (cerror "Continue"
	  "This function is out-of-order.  See MHD.")
;  (cond
;    (off?
;     (setq initialize-kfep-regardless? nil)
;     (setq recompute-true-size-for-characters? nil)
;     (setq kfep-capability? nil))
;    (t     
;     (setq initialize-kfep-regardless? t)
;     (setq recompute-true-size-for-characters? t)
;     (setq kfep-capability? t)
;     (when (boundp 'current-system-name)	; if in a running process
;       (setq need-to-try-to-initialize-kfep-converters? t)
;       (setq default-language 'japanese))))
  )







;;;; KKABUNPO.C



;;; `Kfep-ismini' from kkabunpo.c ...

;#define   ismini(c)	( ((c) == 0x21 || (c) == 0x23 || (c) == 0x25 || \
;			   (c) == 0x27 || (c) == 0x29 || (c) == 0x43 || \
;			   (c) == 0x63 || (c) == 0x65 || (c) == 0x67 || \
;			   (c) == 0x6e ) ? 1 : 0 )

(defun-substitution-macro kfep-ismini (ch)
  (or (=f ch #x21) (=f ch #x23) (=f ch #x25) (=f ch #x27) (=f ch #x29)
      (=f ch #x43) (=f ch #x63) (=f ch #x65) (=f ch #x67) (=f ch #x6e)))



;;; `Kfep-g-generic-function' is a generic function to replace:
;;; g_keiyou(), g_jyodou(), g_taigen(), g_sahen(), and g_jyosi() from
;;; the file kkabunpo.c.

(defun kfep-g-generic-function (string start-index len bun
				       index-array main-array main-array-length)
  ;; Returns:
  ;;   1. Result (0 or -1)
  ;;   2. Bun bits
  (let* ((index 0)
	 (st -1)
	 (ed -1)
	 (result -1))
    (loop while (<f index main-array-length)
	  as index-entry = (svref index-array index)
	  do
      (when (=f (kfep-bunindex-length index-entry) len)
	(setq st (kfep-bunindex-start index-entry))
	(setq ed (kfep-bunindex-end index-entry)))
      (incff index))
    (when (/=f st -1)
      (setq index st)
      (loop while (<=f index ed)
	    as entry = (svref main-array index)
	    do
	(when (=f (kfep-kkastrncmp string (kfep-jjdkkd-key entry) len
				   start-index 0)
		  0)
	  (setq bun (kfep-jjdkkd-bunbun entry))
	  (setq result 0)
	  (return))
	(incff index)))
    (values result bun)))




;;; `Kfep-g-keiyou' from kkabunpo.c ...

(defmacro kfep-g-keiyou (string start-index len bun)
  `(kfep-g-generic-function ,string ,start-index ,len ,bun
			    kfep-kk-index kfep-keiyo-array (kfep-keiyolen)))


;;; `Kfep-g-jyodou' from kkabunpo.c ...

(defmacro kfep-g-jyodou (string start-index len bun)
  `(kfep-g-generic-function ,string ,start-index ,len ,bun
			    kfep-jd-index kfep-jyodou-array (kfep-jyodolen)))


;;; `Kfep-g-taigen' from kkabunpo.c ...

(defmacro kfep-g-taigen (string start-index len bun)
  `(kfep-g-generic-function ,string ,start-index ,len ,bun
			    kfep-ta-index kfep-taigen-array (kfep-taigenlen)))


;;; `Kfep-g-sahen' from kkabunpo.c ...

(defmacro kfep-g-sahen (string start-index len bun)
  `(kfep-g-generic-function ,string ,start-index ,len ,bun
			    kfep-sa-index kfep-sahen-array (kfep-sahenlen)))


;;; `Kfep-g-jyosi' from kkabunpo.c ...

(defmacro kfep-g-jyosi (string start-index len bun)
  `(kfep-g-generic-function ,string ,start-index ,len ,bun
			    kfep-JY-index kfep-jyosi-array (kfep-jyosilen)))




;;; `Kfep-chkcattr' from kkabunpo.c ...

(defun kfep-chkcattr (ch start-index)
  (declare (type fixnum start-index))
  (let* ((char-0 (ascii-char-code (char ch (+f 0 start-index))))
	 (char-1 (ascii-char-code (char ch (+f 1 start-index)))))
    (cond
      ((and (=f char-0 #x24) (=f char-1 #x73))
       (kfep-kka-nn))
      ((and (=f char-0 #x24) (kfep-ismini char-1))
       (kfep-kka-mini))
      ((and (=f char-0 #x21) (or (=f char-1 #x22) (=f char-1 #x23)))
       (kfep-kka-kuto))
      ((and (>=f char-0 #x21) (<=f char-0 #x23)
	    (>=f char-1 #x21) (<=f char-1 #x7e))
       (kfep-kka-misc))
      (t (kfep-kka-nomal)))))




;;; `Kfep-g-dousi' from kkabunpo.c ...

(defun kfep-g-dousi (string start-index len bun)
  ;; Returns:
  ;;   1. Result
  ;;   2. Modified bun bits.
  (cond
    ((>f len 4)
     (values -1 bun))
    (t
     (loop with gobisetu
	     = (if (=f len 4) kfep-gobisetu2 kfep-gobisetu1)
	   with gobisetu-length
	     = (if (=f len 4) (kfep-gobisetu2-size) (kfep-gobisetu1-size))
	   for index from 0 below gobisetu-length
	   as gobitype? = (svref gobisetu index)
	   when (and gobitype?
		     (=f (kfep-kkastrncmp
			   string (kfep-gobitype-gobi gobitype?) len
			   start-index 0)
			 0))
	     do (case (kfep-gobitype-katuyo gobitype?)
		  (#.kfep-bun-godan
		   (setq bun (kfep-bunbit-set-godan bun)))
		  (#.kfep-bun-simo1
		   (setq bun (kfep-bunbit-set-shiti bun)))
		  (#.kfep-bun-kami1
		   (setq bun (kfep-bunbit-set-siiti bun)))
		  (#.kfep-bun-sahen
		   (setq bun (kfep-bunbit-set-sahen bun)))
		  (#.kfep-bun-kahen
		   (setq bun (kfep-bunbit-set-kahen bun)))))
     (values 1 bun))))

;; Simplified considerably from original translation of C code. (See 2.1 version.)
;; The original C code and its translation had some useless code that I could
;; not see a need for -- i.e. the if part of the statements "if (i <= 111) return 1;"
;; and "if(i <= 110) return 1;" (always true), and the "return -1;" at the end
;; (never reached) were unnecessary; perhaps the Japanese comments might explain
;; these anomolies.  The C code is in kkabunpo.c.  (MHD 1/2/91)




;;; `Kfep-chkbunpo' from kkabunpo.c ...
;;; This function is called by kfep-kka-hensaisyo to perform
;;; some specific mappings.
;; I don't understand all it does.  -pto 14nov90
;;; Returns values:
;;;   1. result
;;;   2. Bunbits for bunpo
;;;   3. Value for pat

;;chkbunpo(hyoki, hlen, s, len, bunpo, pat)
;;	u_char  *hyoki;
;;	short   hlen;
;;	char	*s;
;;	int	len;
;;	bunbits *bunpo;
;;	int	*pat;

(defun kfep-chkbunpo (hyoki hlen substring len)
  (declare (type fixnum hlen len))
  (let* (result?
	 (bunpo 0)
	 (pat 0)
	 (n len)
	 (total 0)
	 (sav len)
	 (ok 0)
	 (t-var 0)
	 (i 0)
	 (d 0)
	 (sbun 0)
	 (wbun 0)
	 (hyoki-string-is-simple? (simple-gensym-string-p hyoki)))
    (declare (type fixnum bunpo pat))
    (setq bunpo (kfep-all-bunbits))
    (setq sbun (kfep-all-bunbits))
    (cond
      ((=f len 0)
       (setq result? 0))
      (t
       (tagbody
	Retry
	(block break
	  (loop while (>f n 0)
		do
		(setq t-var 0)
		(setq i (kfep-chkcattr substring total))
		(when (=f ok 0)
		  (multiple-value-setq (d wbun)
		    (kfep-g-dousi substring total n wbun))
		  (when (>f d 0)
		    (setq sbun (kfep-bunbit-set-dosmi sbun))
		    (setq sbun (kfep-bunbit-set-dosyo sbun))
		    (setq sbun (kfep-bunbit-set-dossy sbun))
		    (setq sbun (kfep-bunbit-set-dosta sbun))
		    (setq sbun (kfep-bunbit-set-doska sbun))
		    (setq sbun (kfep-bunbit-set-dosme sbun))
		    (setq t-var 1)
		    (setq ok 0)
		    (setq pat 3)
		    (when (kfep-bunbit-godan wbun)
		      (when (kfep-kka-evalbun
			      hyoki hlen (kfep-bun-godan)
			      hyoki-string-is-simple?)
			(setq sbun (kfep-bunbit-set-godan sbun))
			(incff ok)))
		    (when (kfep-bunbit-shiti wbun)
		      (when (kfep-kka-evalbun
			      hyoki hlen (kfep-bun-simo1)
			      hyoki-string-is-simple?)
			(setq sbun (kfep-bunbit-set-shiti sbun))
			(incff ok)))
		    (when (kfep-bunbit-siiti wbun)
		      (when (kfep-kka-evalbun
			      hyoki hlen (kfep-bun-kami1)
			      hyoki-string-is-simple?)
			(setq sbun (kfep-bunbit-set-siiti sbun))
			(incff ok)))
		    (when (kfep-bunbit-sahen wbun)
		      (when (kfep-kka-evalbun
			      hyoki hlen (kfep-bun-sahen)
			      hyoki-string-is-simple?)
			(setq sbun (kfep-bunbit-set-sahen sbun))
			(incff ok)))
		    (when (kfep-bunbit-kahen wbun)
		      (when (kfep-kka-evalbun
			      hyoki hlen (kfep-bun-kahen)
			      hyoki-string-is-simple?)
			(setq sbun (kfep-bunbit-set-kahen sbun))
			(incff ok)))
		    (if (/=f ok 0)
			(progn
			  (setq result? n) ; return is called here in the C code
			  (return-from break))
			(progn
			  (setq sbun (kfep-bunbit-clear-dosmi sbun))
			  (setq sbun (kfep-bunbit-clear-dosyo sbun))
			  (setq sbun (kfep-bunbit-clear-dossy sbun))
			  (setq sbun (kfep-bunbit-clear-dosta sbun))
			  (setq sbun (kfep-bunbit-clear-doska sbun))
			  (setq sbun (kfep-bunbit-clear-dosme sbun))
			  (setq pat 0)
			  (setq ok 0)))))
		(tagbody
		 sasasa

		 (when (=f ok 0)
		   (let* ((g-sahen 0))
		     (multiple-value-setq (g-sahen wbun)
		       (kfep-g-sahen substring total n wbun))
		     (when (=f g-sahen 0)
		       (when (or (kfep-kka-evalbun
				   hyoki hlen (kfep-bun-meisu)
				   hyoki-string-is-simple?)
				 (kfep-kka-evalbun
				   hyoki hlen (kfep-bun-sahen)
				   hyoki-string-is-simple?))
			 (setq t-var 1)
			 (incff ok)
			 (setq pat 2)
			 (setq sbun wbun)
			 (setq bunpo sbun)
			 (setq result? n) ; return is called here in the C code
			 (return-from break)))))

		 (when (=f ok 0)
		   (let* ((g-taigen 0))
		     (multiple-value-setq (g-taigen wbun)
		       (kfep-g-taigen substring total n wbun))
		     (when (=f g-taigen 0)
		       (when
			   (or
			     (kfep-kka-evalbun
			       hyoki hlen (kfep-bun-meisu)
			       hyoki-string-is-simple?)
			     (kfep-kka-evalbun
			       hyoki hlen (kfep-bun-zougo)
			       hyoki-string-is-simple?)
			     (kfep-kka-evalbun
			       hyoki hlen (kfep-bun-huku)
			       hyoki-string-is-simple?)
			     (kfep-kka-evalbun
			       hyoki hlen (kfep-bun-meisu)
			       hyoki-string-is-simple?)
			     (kfep-kka-evalbun
			       hyoki hlen (kfep-bun-daimei)
			       hyoki-string-is-simple?)
			     (kfep-kka-evalbun
			       hyoki hlen (kfep-bun-misc)
			       hyoki-string-is-simple?))
			 (when (or (=f i (kfep-kka-nomal))
				   (=f i (kfep-kka-kuto)))
			   (setq t-var 1)
			   (incff ok)
			   (setq pat 1)
			   (setq sbun wbun)
			   (setq bunpo sbun)
			   (setq result? n) ; return is called here in the C code
			   (return-from break))))))

		 (when (=f ok 0)
		   (when (or (=f (kfep-kkastrncmp substring "$H" n total 0) 0)
			     (=f (kfep-kkastrncmp substring "$?$k" n total 0) 0))
		     (when (kfep-kka-evalbun
			     hyoki hlen (kfep-bun-keido)
			     hyoki-string-is-simple?)
		       (setq t-var 1)
		       (incff ok)
		       (setq pat 1)
		       (setq sbun (kfep-bunbit-set-kdogo sbun))
		       (setq bunpo sbun)
		       (setq result? n) ; return is called here in the C code
		       (return-from break))))

		 (when (=f ok 0)
		   (let* ((g-keiyou 0))
		     (multiple-value-setq (g-keiyou wbun)
		       (kfep-g-keiyou substring total n wbun))
		     (when (=f g-keiyou 0)
		       (when (kfep-kka-evalbun
			       hyoki hlen (kfep-bun-keiyo)
			       hyoki-string-is-simple?)
			 (setq t-var 1)
			 (incff ok)
			 (setq pat 2)
			 (setq sbun wbun)
			 (setq bunpo sbun)
			 (setq result? n) ; return is called here in the C code
			 (return-from break)))))

		 JYO
		 (let* ((g-jyodou 0))
		   (multiple-value-setq (g-jyodou wbun)
		     (kfep-g-jyodou substring total n wbun))
		   (when (=f g-jyodou 0)
		     (when (and
			     (not (kfep-kka-evalbun
				    hyoki hlen (kfep-bun-meisi)
				    hyoki-string-is-simple?))
			     (not (kfep-kka-evalbun
				    hyoki hlen (kfep-bun-misc)
				    hyoki-string-is-simple?)))
		       (when (=f ok 0)
			 (setq t-var 0)
			 (incff ok)
			 (setq pat 2)
			 (setq sbun wbun)))
		     (return-from break)))

		 (let* ((g-jyosi 0))
		   (multiple-value-setq (g-jyosi wbun)
		     (kfep-g-jyosi substring total n wbun))
		   (when (=f g-jyosi 0)
		     (when (and
			    (not (kfep-kka-evalbun
				   hyoki hlen (kfep-bun-meisi)
				   hyoki-string-is-simple?))
			    (not (kfep-kka-evalbun
				   hyoki hlen (kfep-bun-misc)
				   hyoki-string-is-simple?)))
		       (if (=f ok 0)
			   (progn
			     (setq t-var 0)
			     (incff ok)
			     (setq pat 2))
			   (progn
			     (setq t-var 1)
			     (incff ok)
			     (setq pat 1)
			     (setq sbun wbun)
			     (setq bunpo sbun)
			     (setq result? n) ; return is called here in the C code
			     (return-from break))))
		     (return-from break)))

		 (when (and (=f t-var 1) (=f pat 1)) 
		   (setq bunpo sbun)
		   (setq result? n)	; return is called here in the C code
		   (return-from break)))
		(decff n 2)))
	(when (not result?)
	  (if (<=f n 0)
	      (if (/=f ok 0)
		  (progn
		    (setq bunpo sbun)
		    (setq result? 0))	; return is called here in the C code
		  (progn
		    (if (or (kfep-kka-evalbun
			      hyoki hlen (kfep-bun-meisi)
			      hyoki-string-is-simple?)
			    (kfep-kka-evalbun
			      hyoki hlen (kfep-bun-misc)
			      hyoki-string-is-simple?))
			(setq bunpo (kfep-all-bunbits)))
		    (setq result? 0)	; return is called here in the C code
		    ))
	      (progn
		(incff total n)
		(setq n (-f sav total))
		(go Retry)))))))
    (values result? bunpo pat)))



;;; `Kfep-kka-evalbun' from kkabunpo.c ... returns t or nil.  Note that the
;;; original C version returned 0 and -1 for t and nil, respectively.  The
;;; string-is-simple? argument was added for the lisp version for efficiency.

(defun kfep-kka-evalbun (string stringlen hinsi string-is-simple?)
  (loop with index = 0
	with golen = 0
	with count = 0
	with bun = 0
	while (<f index stringlen)
	do (setq golen (ascii-char-code (gchar string index string-is-simple?)))
	   (incff index (+f golen 1))
	   (setq bun (ascii-char-code (gchar string index string-is-simple?)))
	   (if (=f bun hinsi) (return t))
	   (incff index)
	   (incff count)))

;; Note that evalbun is only used in kfep-chkbunpo at present. (MHD 1/3/91)






;;;; KKA_MAINIT


;;; `kka-mkkojin' initializes a new KOJIN.DIC file.

(defun-substitution-macro kka-mkkojin (kojin-file-stream)
  kojin-file-stream
  )

;;; `kfep-read-master-header' reads the integers that comprises the header
;;; of the main dictionary file.

(defun-substitution-macro kfep-read-master-header (stream)
  (let* ((string kfep-master-header-in-characters)
	 (number-of-characters-read 0)
	 (string-index 0))
    (declare (type fixnum number-of-characters-read string-index))
    (loop for  array-index from 0 below (kfep-master-header-size)
	  do
      (progn
	(setq number-of-characters-read
	      (g2-stream-read-into-string stream string 4 string-index)) ; 4 is sizeof(int)
	(setf (svref kfep-master-header array-index) ; one time consing of bignums, if any
	      (read-32-bit-big-endian-number-from-string-with-fixnum-limit
	       string string-index most-positive-fixnum))
	(incff string-index number-of-characters-read)))))


(defun-substitution-macro kfep-read-kfep-master (stream kfep-master)
  ;; Returns nil if error, non-nil if ok.
  (let* (new-string
	  number-of-characters-read)
    (setq new-string (obtain-lisp-string (kfep-midxln)))
    (setq number-of-characters-read
	  (g2-stream-read-into-string stream new-string (kfep-midxln) 0))
    (cond
      ((=f number-of-characters-read (kfep-midxln))
       (setf (kfep-master-midashi kfep-master) new-string)
       (setq new-string (obtain-lisp-string 4))
       (setq number-of-characters-read
	     (g2-stream-read-into-string stream new-string 4 0))
       (cond
	 ((=f number-of-characters-read 4)
	  (setf (kfep-master-offset kfep-master) new-string)
	  (setq new-string (obtain-lisp-string 2))
	  (setq number-of-characters-read
		(g2-stream-read-into-string stream new-string 2 0))
	  (cond
	    ((=f number-of-characters-read 2)
	     (setf (kfep-master-nbyte kfep-master) new-string)
	     t)
	    (t (reclaim-lisp-string new-string)
	       nil)))
	 (t
	   (reclaim-lisp-string new-string)
	   nil)))
      (t
	(reclaim-lisp-string new-string)
	nil))))
	

(defun-substitution-macro kfep-read-m-table (stream)
  (loop for index from 0 below (kfep-m-table-size)
	do
    (kfep-read-kfep-master stream (svref kfep-m-table index))))



;;; `kfep-kka-mainit' is a replacement for the C function kka_mainit in CTC's
;;; KFEP.  It returns nil if it fails to initialize and t if it is successful.

(defun kfep-kka-mainit
    (switch index-filename hyoki-filename kojin-filename)
  (declare (ignore switch))
  (g2-stream-with-non-character-mode
    (progn ;; Initialize Globals
      
      ;; Initialize kfep-m-table
      (when (or (null kfep-m-table)
		#+development initialize-kfep-regardless?)
	(setq kfep-m-table
	      (with-permanent-array-creation (make-array (kfep-m-table-size))))
	(loop for index from 0 below (kfep-m-table-size)
	      do
	  (setf (svref kfep-m-table index) (make-kfep-master))))
      
      ;; Initialize kfep-battable
      (when (or (null kfep-battable)
		#+development initialize-kfep-regardless?)
	(setq kfep-battable
	      (with-permanent-array-creation (make-array (kfep-bunsetumax))))
	(loop for index from 0 below (kfep-bunsetumax)
	      as new-kfep-batch = (make-kfep-batch)
	      do
	  (setf (kfep-batch-hyoki new-kfep-batch) (obtain-lisp-string 4))
	  (setf (svref kfep-battable index) new-kfep-batch)))
      
      ;; Initialize kfep-batchyomi
      (setq kfep-batchyomi (obtain-lisp-string (kfep-bunmax)))
      (cond
	((or (null (setq kfep-index-file-stream
			 (g2-stream-open-for-random-access-binary-input index-filename)))
	     (null (setq kfep-main-file-stream
			 (g2-stream-open-for-random-access-binary-input hyoki-filename)))
	     (null (setq kfep-kojin-file-stream
			 (g2-stream-open-for-random-access-binary-input kojin-filename))))
	 (notify-user-of-error-opening-kfep-dictionary-file
	   (if (null kfep-index-file-stream)
	       index-filename
	       (if (null kfep-main-file-stream)
		   hyoki-filename
		   kojin-filename)))
	 nil)
	(t
	 (reset-fep-file-stream kfep-index-file-stream)
	 (reset-fep-file-stream kfep-main-file-stream)
	 (kfep-read-master-header kfep-index-file-stream)
	 (setq kfep-tablemax (kfep-p-useval))
	 (kfep-read-m-table kfep-index-file-stream)
	 (reset-fep-file-stream kfep-kojin-file-stream)
	 (kka-mkkojin kfep-kojin-file-stream)
	 (reset-fep-file-stream kfep-kojin-file-stream)
	 t)))))



;;; `Reset-fep-file-stream' takes a stream used for KFEP and sets the file
;;; position to 0.

(defun reset-fep-file-stream (stream)
  (g2-stream-set-file-position stream 0 (g2-stream-seek-from-beginning)))



;;; `Notify-user-of-error-opening-kfep-dictionary-file' is called to notify the
;;; user if there is after an error has occured openning the designated file.
;;; It is assumed that (g2-stream-get-error-flag) has just been set according to
;;; the type of failure.  This notifies the user (i.e., via the logbook).

(defun notify-user-of-error-opening-kfep-dictionary-file (ascii-filename)
  (let ((file-name-text-string
	 (import-text-string ascii-filename 'kfep-filename))
	(error-text-string		; assumed to be a legal text string
	 (most-recent-file-operation-status-as-text)))
    (notify-user
      "Error (#~d) opening ~s for input: ~s"
      (or (g2-stream-get-error-flag)
	  -100000)			; should never fall through to here!
      file-name-text-string
      error-text-string)
    (reclaim-text-string file-name-text-string)
    (reclaim-text-string error-text-string)))





(def-system-variable specified-kfep-index-filename? KFEP1 nil)
(def-system-variable specified-kfep-main-filename? KFEP1 nil)
(def-system-variable specified-kfep-kojin-filename? KFEP1 nil)


;;; The parameters `kfep-index-filename', `kfep-main-filename', and
;;; `kfep-kojin-filename' should be set to strings which give the pathname
;;; of the respective files required by the KFEP.

;;; The `kanji16-font-filename', similarly, gives the location of the Kanji
;;; font (Kanji16) used in the Japanese version of G2.

;;
;; WORK TO DO HERE FOR PTO:
;;
;; Make this user-definable:
;;

;;; The default names were changed from KFEP-INDEX.DIC, KFEP-MAIN.DIC, and
;;; KFEP-KOJIN.DIC to index.dic, main.dic, and kojin.dic, respectively, for 4.0.
;;; Note that the names are required to be lowercase (I forget why, but Platform
;;; Engineering wants it that way), and they must be 8 long in their name and 3
;;; long in their type (maximum) to survive MS-DOS. (MHD 4/5/94)

;;; ... except that we never updated our CVS lisp module, and so they are still
;;; checked in with their old names.  The next time we spin off, we should get
;;; this right, but for now, it's easier to just change what we look for than
;;; to change what is there.  - jv 2/1/99

 ; change to all-lowercase for 4.0   (MHD 11/8/93)
(defparameter kfep-index-filename
  #+development "KFEP-INDEX.DIC"
  #-development "index.dic")
(defparameter kfep-main-filename
  #+development "KFEP-MAIN.DIC"
  #-development "main.dic")
(defparameter kfep-kojin-filename
  #+development "KFEP-KOJIN.DIC"
  #-development "kojin.dic")



#+development
(defun default-kka-mainit ()
  (kfep-kka-mainit
    0
    (or specified-kfep-index-filename? kfep-index-filename)
    (or specified-kfep-main-filename? kfep-main-filename)
    (or specified-kfep-kojin-filename? kfep-kojin-filename)))






;;;; kkamiscs.c


;;; `Kfep-kkastrncmp' from kkamiscs.c ...

;; This function was fixed in 3.0 but not in 2.1.  Should another compile
;; of 2.1 be required, we should put this function in.  -pto 27nov90

;; Note: this WAS fixed in all versions, but the note should be removed! (MHD 1/2/91)

(defun kfep-kkastrncmp (string-1 string-2 n string-1-start string-2-start)
  ;; string-1-start and string-2-start should default to 0.
  (if (or (>f n (-f (length string-1) string-1-start))
	  (>f n (-f (length string-2) string-2-start)))
      0
      (loop for index from 0 below n
	    as index-1 = (+f index string-1-start)
	    as index-2 = (+f index string-2-start)
	    do
	(if (/=f (ascii-char-code (char string-1 index-1))
		 (logandf (ascii-char-code (char string-2 index-2)) #x7f))
	    (return 1))
	    finally
	      (return 0))))






;;;; KKA_KOINIT


(defun kfep-read-kojin-usedbits (stream)
  (loop for index from 0 below (kfep-k-usebits)
	do (setf (char kfep-kojin-usedbits index)
		 (g2-stream-read-char stream))))

(defun kfep-read-kojin-bunpobits (stream)
  (loop for index from 0 below (kfep-k-usebits)
	do (setf (char kfep-kojin-bunpobits index)
		 (g2-stream-read-char stream))))



(defun kfep-read-kojin-header (stream)
  (loop for index from 0 below (kfep-kojin-header-size)
	do (setf (svref kfep-kojin-header index)
		 (g2-stream-read-32-bit-big-endian-number stream t))))

;; I am not sure that using T in the above two functions, meaning to restrict
;; the result to a fixnum, does not lead to bugs or strange or erroneous
;; results.  But it has always been done that way in the released software for
;; reasons I am not sure of.  PTO coded it that way when he did the translation
;; from C to Lisp.  Also, note that the result could vary between different
;; platforms where the size of fixnum varies, e.g., between Suns, Explorers, and
;; Symbolics.  I am pretty sure that the results really would be bignums on
;; all platforms, and that we do cut them down to fixnum size.  I further think
;; that this is bogus but we don't get burned by it because it has to do with
;; managing KOJIN dictionary, which means the "user learning" dictionary, which
;; don't bother with anyway right now.  (MHD 12/3/91)




;;; `Kfep-kka-koinit' reads in the KOJIN.DIC file.

(defun kfep-kka-koinit ()
  (g2-stream-with-non-character-mode
    #+development
    (when (null kfep-kojin-file-stream)
      (setq kfep-kojin-file-stream
	    (g2-stream-open-for-input
	      (or specified-kfep-kojin-filename? kfep-kojin-filename))))
    
    (kfep-read-kojin-header kfep-kojin-file-stream)

    (when (<f (kfep-k-usebits) maximum-gensym-string-length)
      (setq kfep-kojin-usedbits (obtain-lisp-string (kfep-k-usebits)))
      (setq kfep-kojin-bunpobits (obtain-lisp-string (kfep-k-usebits)))
      (setq kfep-kojin-index (make-kojin-index))
      
      (kfep-read-kojin-usedbits kfep-kojin-file-stream)
      (kfep-read-kojin-bunpobits kfep-kojin-file-stream)
      (kfep-read-kojin-index kfep-kojin-file-stream)
      
      (setq kfep-kojin-hyolen (kfep-k-hyokisiz))
      t)))


#+development
(defun reset-kka-koinit ()
  (g2-stream-with-non-character-mode
    (if kfep-kojin-file-stream
	(g2-stream-close kfep-kojin-file-stream))
    (setq kfep-kojin-file-stream nil)))








;;;;  JIS Hiragana to JIS Kanji




;;; Kfep-find-1 is just a subfunction (macro) of kfep-find-used and kfep-find-bunpo.
;;; Num is a fixnum, and bits-string is either kfep-kojin-usedbits or kfep-kojin-
;;; bunpobits.

(def-substitution-macro kfep-find-1 (num bits-string)
  (let* ((page (+f (floorf num 4) 1))
	 (pos (modf num 4))
	 (mask (ashf #xFF (-f (ashf pos 1))))	;/* (pos << 1) =======> pos * 2 */
	 (shift (ashf (-f 3 pos) 1)))
    ;; `bit2':
    (ashf (logandf (ascii-char-code (char bits-string (-f page 1))) mask)
	  (-f shift))))




;;; `Kfep-find-used' from kkakojin.c ...

(defun kfep-find-used (num)
  (kfep-find-1 num kfep-kojin-usedbits))



;;; `Kfep-find-bunpo' from kkakojin.c ...

(defun kfep-find-bunpo (num)
  (let ((bit2 (kfep-find-1 num kfep-kojin-bunpobits)))
    (if (=f bit2 0) 1 bit2)))



;;; `Kfep-kka-gtnum' ...

(defun kfep-kka-gtnum (string string-start-index len)
  (let* ((result? nil)
	 (c 0)
	 (i 0)
	 (ok 0)
	 (buf (obtain-lisp-string 20)))	; The 17 in kka_gtnum in C is a bug.
    (copy-lisp-string-to-target string buf string-start-index 0 len)
    (copy-lisp-string-to-target "                        " buf
				0 len (-f (kfep-midxln) len))

    (loop while (<f i kfep-tablemax)
	  do
      (setq c (kfep-hikakun buf (kfep-master-midashi (svref kfep-m-table i))
			    (kfep-midxln)))
      (when (or (=f c #.(ascii-char-code #\<))
		(=f c #.(ascii-char-code #\=)))
	(setq ok 1)
	(return))
      (incff i))
    (if (/=f ok 0)
	(if (=f c #.(ascii-char-code #\=))
	    (setq result? i)
	    (setq result? (-f i 1)))
	(progn
	  (setq c (kfep-hikakun buf kfep-master-header-in-characters (kfep-midxln) 0 #.(* 4 4)))
	  (if (/=f c #.(ascii-char-code #\>))
	      (setq result? (-f kfep-tablemax 1))
	      (setq result? -1))))

    (reclaim-lisp-string buf)
    (if result? result? 0))) 





;;; Caching Facility for kfep-kka-ghyoki


(def-system-variable kfep-ghyoki-idxbuf KFEP1 nil)     ; static u_char *idxbuf;
(def-system-variable kfep-ghyoki-hptr KFEP1 nil)       ; static u_char *hptr;
(def-system-variable kfep-ghyoki-savtblnum KFEP1 -1)   ; static int savtblnum = -1;



(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro-for-constant kfep-ghyoki-idxbuf-cache-size-limit 25)
)
(def-system-variable kfep-ghyoki-idxbuf-cache-alist KFEP1 nil)



(defun-substitution-macro kfep-add-item-to-cache (new-index new-item)
  (setq kfep-ghyoki-idxbuf-cache-alist
	(gensym-cons
	  (gensym-cons new-index new-item)
	  kfep-ghyoki-idxbuf-cache-alist)))




;;; `Kfep-find-item-in-cache' tries to find a table entry in the cache
;;; given its index.  If it succeeds, it will move the cached item
;;; to the front of the LRU cache.  If it fails, it will return nil.
;;; If it fails, and there are (kfep-ghyoki-idxbuf-cache-size-limit)
;;; items in the cache, it will reclaim the last one.  It is a 
;;; defun-substitution-macro because it is only called by
;;; kfep-obtain-ghyoki-idxbuf.

(defun-substitution-macro kfep-find-item-in-cache (new-index)
  (loop as tail? = nil then rest-of-alist
	for rest-of-alist on kfep-ghyoki-idxbuf-cache-alist
	as index-item = (car rest-of-alist)
	as index = (car index-item)
	as count from 1
	when (=f new-index index)
	  do (when tail?
	       (setf (cdr tail?) (cdr rest-of-alist))
	       (setf (cdr rest-of-alist)
		     kfep-ghyoki-idxbuf-cache-alist)
	       (setq kfep-ghyoki-idxbuf-cache-alist
		     rest-of-alist))
	     (return (cdr index-item))
	when (>=f count (kfep-ghyoki-idxbuf-cache-size-limit))
	  ;; Limiting size of cache here
	  do (progn
	       (setf (cdr tail?) nil)
	       (loop for entry in rest-of-alist
		     do (reclaim-lisp-string (cdr entry))
			(reclaim-gensym-cons entry))
	       (reclaim-gensym-list rest-of-alist))
	     (return nil)))









;;; `Kfep-obtain-ghyoki-idxbuf' tries to get the desired table entry
;;; from the cache.  It it fails, it will read the table entry from
;;; the KFEP Index file.

(defun-substitution-macro kfep-obtain-ghyoki-idxbuf (tblnum nbyte offset)
  (cond
    ((=f tblnum kfep-ghyoki-savtblnum)
     nil)
    (t
     (let ((cached-item? (kfep-find-item-in-cache tblnum)))
       (cond
	 (cached-item?
	  (setq kfep-ghyoki-idxbuf cached-item?)
	  (setq kfep-ghyoki-savtblnum tblnum))
	 (t
	  (setq kfep-ghyoki-idxbuf (obtain-lisp-string nbyte))
	  (g2-stream-with-16-byte-file
	    (g2-stream-set-file-position kfep-index-file-stream
					 (+f offset (kfep-mastersize))
					 (g2-stream-seek-from-beginning))
	    (g2-stream-read-into-string kfep-index-file-stream
					kfep-ghyoki-idxbuf
					nbyte 0)
	    ;; PRETEND THERE'S NO ERROR IN THE READ.
	    (setq kfep-ghyoki-savtblnum tblnum))
	  (kfep-add-item-to-cache tblnum kfep-ghyoki-idxbuf))))))
  kfep-ghyoki-idxbuf)







;;; `Kfep-kka-ghyoki' ...

;; u_char	*kka_ghyoki(yomi, len, rhlen, entry, number)
;;   u_char *yomi;
;;   int     len;
;;   short  *rhlen;
;;   short  *entry;
;;   int    *number;




(defun kfep-kka-ghyoki (yomi yomi-start-index len) ; Does not eat yomi.
  ;; Returns 4 values:
  ;; 1st value:  result of kka_ghyoki (string or nil) - do not reclaim!
  ;; 2nd value:  value of rhlen
  ;; 3rd value:  value of entry
  ;; 4th value:  value of number
  (declare (type fixnum yomi-start-index len))
  (let* ((hoffset 0)
	 (tblnum 0)
	 (i 0)
	 (j 0)
	 (k 0)
	 (golen 0)
	 (locgonum 0)
	 (hlen 0)
	 (doonlen 0)
	 idxptr
	 (nbyte 0)
	 (offset 0)
	 (result? nil)
	 (result-set? nil)
	 (rhlen 0)
	 (entry 0)
	 (number 0))
    (cond
      ((>f len (kfep-midxln))
       (setq result? nil)
       (setq result-set? t))
      (t
       (setq tblnum (kfep-kka-gtnum yomi yomi-start-index len))
       (cond
	 ((<f tblnum 0)
	  (setq result? nil)
	  (setq result-set? t))
	 (t
	  (setq nbyte (read-16-bit-big-endian-number-from-string
		       (kfep-master-nbyte (svref kfep-m-table tblnum)) 0))
	  (setq offset (read-32-bit-big-endian-number-from-string ; should not be bignums
			(kfep-master-offset (svref kfep-m-table tblnum)) 0))


;; Old code (as per C code):
;	  (if kfep-ghyoki-idxbuf	; realloc() if necessary
;	      (when (<f (length kfep-ghyoki-idxbuf) nbyte)
;		;; From the C program, it is clear that we do not need to
;		;; copy the contents of the old idxbuf into the new one IF
;		;; they are of different sizes.
;		;; If there're problems, suspect this code first.
;		(reclaim-lisp-string kfep-ghyoki-idxbuf)
;		(setq kfep-ghyoki-idxbuf (obtain-lisp-string nbyte)))
;	      (progn
;		(setq kfep-ghyoki-idxbuf (obtain-lisp-string nbyte))))
;	  (when (/=f tblnum kfep-ghyoki-savtblnum)
;	    (g2-stream-with-16-byte-file
;	     (g2-stream-set-file-position kfep-index-file-stream
;					  (+f offset (kfep-mastersize))
;					  (g2-stream-seek-from-beginning))
;	     (g2-stream-read-into-string kfep-index-file-stream
;					 kfep-ghyoki-idxbuf
;					 nbyte 0)
;	     ;; PRETEND THERE'S NO ERROR IN THE READ.
;	     (setq kfep-ghyoki-savtblnum tblnum)))

;; New code:
	  (kfep-obtain-ghyoki-idxbuf tblnum nbyte offset)



	  (setq idxptr 0)
	  (setq i 0)
	  (setq locgonum 0)
	  (loop while (<f i nbyte)
		do
	    (block continue
	      (setq hlen (ascii-char-code (char kfep-ghyoki-idxbuf idxptr)))
	      (incff idxptr)
	      (when (or (/=f (-f hlen 5) len)
			(/=f (strncmp-function yomi kfep-ghyoki-idxbuf len
					       yomi-start-index idxptr)
			     0))
		(incff locgonum)
		(loop while (>f hlen 1)
		      do
		      (incff idxptr)
		      (incff i)
		      (decff hlen))
		(return-from continue))
	      (setq number (+f (*f (kfep-tablesize) tblnum) locgonum))
	      (setq i 0)
	      (loop while (<f i (-f hlen 5))
		    do
		    (incff idxptr)
		    (incff i))
	      (setq hoffset (read-32-bit-big-endian-number-from-string  ; should not be bignums
			     kfep-ghyoki-idxbuf idxptr))
	      (incff idxptr 4)		;4 == 32 bits
	      (g2-stream-with-16-byte-file
	       (g2-stream-set-file-position kfep-main-file-stream
					    hoffset
					    (g2-stream-seek-from-beginning))
	       (let* ((temporary-buffer (obtain-lisp-string 2)))
		 (g2-stream-read-into-string kfep-main-file-stream
					     temporary-buffer
					     2 0)
		 (setq doonlen (read-16-bit-big-endian-number-from-string
				temporary-buffer 0))
		 (reclaim-lisp-string temporary-buffer)))
	      (when kfep-ghyoki-hptr
		(reclaim-lisp-string kfep-ghyoki-hptr))
	      (setq kfep-ghyoki-hptr (obtain-lisp-string doonlen))
	      ;; PRETEND THERE'S NO ERROR IN THE ALLOCATION OF A STRING
	      (g2-stream-with-16-byte-file
	       (g2-stream-read-into-string kfep-main-file-stream
					   kfep-ghyoki-hptr
					   doonlen 0))
	      (setq rhlen doonlen)
	      (setq j 0)
	      (setq k 0)
	      (loop while (<f j doonlen)
		    do
		(progn
		  (setq golen (ascii-char-code (char kfep-ghyoki-hptr j)))
		  (incff j (+f golen 1))
		  )
		(incff j)
		(incff k))
	      (setq entry k)
	      (setq result? kfep-ghyoki-hptr)
	      (setq result-set? t)
	      (return))
	    ;; Outside the "CONTINUE" block
	    (incff i))
	  (when (not result-set?)
	    (setq number -1)
	    (setq result? nil)
	    (setq result-set? t))))))
    (values result? rhlen entry number)))



;;; `Kfep-kka-gtango' ...

;; kka_gtango(array, arraylen, pos, obuf, olen, bun)
;;	u_char	*array;
;;	short	 arraylen;
;;      short    pos;
;;      u_char  *obuf;
;;      short   *olen;
;;      u_char  *bun;

(defun kfep-kka-gtango (array-string arraylen pos obuf-string)
  (declare (type fixnum arraylen pos))
  ;; Returns 3 values:
  ;; 1st value:  returns -1 if failed, 0 if successful.
  ;; 2nd value:  returns number of bytes in the output buffer.
  ;; 3rd value:  the new value for bun-string - this string must be reclaimed.
  (let* ((olen 0)
	 (count 0)
	 (golen 0))
    (declare (type fixnum olen count golen))
    (loop with array-string-is-simple? = (simple-gensym-string-p array-string)
	  for index from 0 below arraylen
	  do
      (setq golen
	    (ascii-char-code (gchar array-string index array-string-is-simple?)))
      (if (=f pos count)
	  (progn
	    (copy-lisp-string-to-target
	      array-string obuf-string (+f index 1) 0 golen)
	    (setq olen golen)
	    (return))
	  (progn
	    (incff index (+f golen 1))))
      (incff count))
    (if (>f pos count)
	(values -1 olen)
	(values  0 olen))))




;;; `Kfep-kka-ishouki' from kkakojin.c ...

;;kka_ishouki(yomi, chkcnt, len, anslen)
;;	char	*yomi;
;;	int	 chkcnt;
;;	int	 len;
;;	int	*anslen;

(defun kfep-kka-ishouki (yomi yomi-start-index chkcnt len)
  ;; Returns:
  ;; 1. -1, 0, or 1
  ;; 2. Length of the answer(?)
  (declare (type fixnum chkcnt len))
  (let* (result?
	 (anslen 0)
	 (length-index len)
	 (index 0)
	 (go 0)
	 (ok 0)
; not used
;	 (hl 0)
;	 (ent 0)
	 ghyoki-result
	 )
    (declare (type fixnum anslen))
    (loop while (<f index chkcnt)
	  do
      (multiple-value-setq-some
	(ghyoki-result nil nil go)		; hl & ent, ignored, are values 2 & 3
	(kfep-kka-ghyoki yomi (+f yomi-start-index index) length-index))
      (when ghyoki-result
	(incff ok)
	(return))
      (when (<f length-index 0)
	(incff index)
	(setq length-index len))
      (decff length-index 2))
    (setq anslen length-index)
    (cond
      ((=f ok 0)
       (setq result? -1))
      ((=f (kfep-find-used go) (kfep-sel-none))
       (setq result? 1))
      (t
       (setq result? 0)))
    (values result? anslen)))
	


;;; `Map-to-kojin-entry' is the accessor function for entries in the `kojin index'
;;; data structure.  It takes kfep-kojin-index and indexno as arguments and maps
;;; to the appropriate index.
;;;
;;; `Make-kojin-index' creates the kojin index data structure, based on global
;;; parameters giving its length.
;;;
;;; `Kfep-read-kojin-index' reads data from stream into the kojin index data
;;; structure.
;;;
;;; Here is how this data structure is implemented in terms of basic layout of
;;; the data, and the recent change history around its implementation.  However,
;;; note that the use of these data abstraction primitives makes the details of
;;; how this data structure is implemented irrelevant to the callers.  Note also
;;; that the abstraction primitives did not previously exist prior to the most
;;; recent change; instead, explicity code was used to access it directly, based
;;; on its previous implementation.
;;;
;;; The old code that essentially implements the old abstraction is still below,
;;; effectively commented out with the reader macro preceeding it: #+obsolete.
;;; It would actually still work to use it; it would just be inefficient in
;;; terms of space (due to a bug) and time.
;;;
;;; Previously, the kojin index data structure was implemented as an array of 32
;;; bit numbers.  Currently, it is implemented as an array of byte vectors, each
;;; no longer than some maximum size based on implementation limits, and enough
;;; of them long enough to hold all of the bytes stored in the kojin dictionary
;;; (kojin.dic).
;;; 
;;; NOTE: Apparently there's been a bug all along that we create a general array
;;; (kfep-k-hindex) (= 225280) elements long (nearly a megabyte of memory) but
;;; it's to hold only 1/4 as many 32-bit integers.  The code below then used to
;;; just fill the 1/4 elements with 32-bit numbers.
;;; 
;;; Presumably, this confusion when we transformed when we transformed a byte
;;; array holding that many 8-bit-byte elements.
;;;
;;; Anyway, now we're switching back to storing a byte-array again.  Thankfully,
;;; it can use just 1/4 of a megabyte of memory.  It will be much faster to
;;; load, and the docoding into "32-bit-big-endian-numbers" will just happen at
;;; run time, and be more than fast enough.  (MHD 1/20/95)

#+obsolete
(progn

(defun-simple map-to-kojin-entry (kfep-kojin-index indexno)
  (svref kfep-kojin-index indexno))


(defun-simple make-kojin-index ()
  (with-dynamic-creation
      (make-array (kfep-k-hindex))))	; NOTE!


(defun kfep-read-kojin-index (stream)
  (loop for index from 0 below (halff (halff (kfep-k-hindex))) ; number of 32 bit integers
	do (setf (svref kfep-kojin-index index)
		 (g2-stream-read-32-bit-big-endian-number stream t))))

)

#-obsolete
(progn

;;; `Map-to-kojin-entry' ... Note that this can only produce fixnums.  If a
;;; result would result in a bignum, enough of its high-order bits are truncated
;;; to make it fit in a fixnum.  This assumes fixnums are at least 24 bits in
;;; length.

(defconstant maximum-kojin-entry-subvector-length
    (-f maximum-byte-vector-length 1))	; -1 recommended in order to "paper
					;   over bug" -- advice from FONTS
					;   (MHD 1/20/95)

(defconstant most-positive-fixnum-ash-minus-24
  (ashf most-positive-fixnum -24))

(defun-simple map-to-kojin-entry (kfep-kojin-index indexno)
  (multiple-value-bind (subvector-index byte-index)
      (floorf indexno maximum-kojin-entry-subvector-length)
    (let ((byte-vector (svref kfep-kojin-index subvector-index)))
      ;; restrict to a fixnum:
      (+f (byte-vector-aref byte-vector (+f byte-index 3))
	  (ashf (byte-vector-aref byte-vector (+f byte-index 2)) 8)
	  (ashf (byte-vector-aref byte-vector (+f byte-index 1)) 16)
	  (ashf (logandf (byte-vector-aref byte-vector (+f byte-index 0))
			 most-positive-fixnum-ash-minus-24)
		24)))))			; assumed minimum fixnum length

;; The code to restricto to the result to a fixnum had been coded as (min <arg1>
;; <arg2>), but Chestnut had a bug that it got a bus error when MIN was called
;; with a fixnum and a bignum.  JRA is reporting this.  The recoding using
;; logand is just as good, and works around that bug.  (MHD 12/3/91)
;;
;; -- Enhanced not to need to enter temporary-bignum context or to do generic
;; arithmetic.  (MHD 1/20/95)


(defun-simple make-kojin-index ()
  (let* ((total-byte-count (kfep-k-hindex))
	 (vector-length
	   (ceiling total-byte-count
		    maximum-kojin-entry-subvector-length))
	 (vector (with-permanent-array-creation (make-array vector-length))))
    (loop for i from 0 below vector-length
	  do (setf (svref vector i)
		   (allocate-byte-vector
		     (if (=f i (-f vector-length 1))
			 (modf		; last one shorter
			   total-byte-count
			   maximum-kojin-entry-subvector-length)
			 maximum-kojin-entry-subvector-length))))
    vector))


(defun-void read-kojin-stream-into-byte-vector
    (stream byte-vector number-of-characters start-index)
  (g2-stream-read-into-byte-vector
    stream byte-vector number-of-characters start-index))


(defun kfep-read-kojin-index (stream)
  (let* ((total-byte-count (kfep-k-hindex))
	 (vector-length
	   (ceiling total-byte-count
		    maximum-kojin-entry-subvector-length))
	 (vector kfep-kojin-index))
    (loop for i from 0 below vector-length
	  as byte-vector = (svref vector i)
	  as number-of-characters
	    = (if (=f i (-f vector-length 1))
		  (modf
		    total-byte-count	; last one shorter
		    maximum-kojin-entry-subvector-length)
		  maximum-kojin-entry-subvector-length)
	  do (read-kojin-stream-into-byte-vector
	       stream byte-vector number-of-characters 0))))

)





;;; `Kfep-kka-kofind' from kkakojin.c ...

(defun kfep-kka-kofind (indexno byteno)
  ;; Returns: nil or string (string needs reclaiming)
  (let* ((result? nil)
	 (kojin-entry (map-to-kojin-entry kfep-kojin-index indexno)))
    (if (=f kojin-entry most-positive-fixnum)
	(setq result? nil)
	(let* ((hptr (obtain-lisp-string byteno)))
	  (g2-stream-with-16-byte-file
	   (g2-stream-set-file-position kfep-kojin-file-stream
					(+f kojin-entry (kfep-k-header)
					    (twicef (kfep-k-usebits))
					    (kfep-k-hindex))
					(g2-stream-seek-from-beginning)))
	  (g2-stream-read-into-string kfep-kojin-file-stream
				      hptr
				      byteno 0)
	  (setq result? hptr)))
    result?))





;;; `Kfep-kka-hensaisyo' ...
;;; This is the main function for preparing a list of possible translation
;;; for the input Hiragana string.  The list is stored in static memory
;;; and the contents are accessed by kfep-kka-gtango.

(def-system-variable kfep-hensaisyo-getpos KFEP1 0)
(def-system-variable kfep-hensaisyo-tno KFEP1 0)
(def-system-variable kfep-hensaisyo-gonum KFEP1 0)
;(def-system-variable kfep-hensaisyo-initf KFEP1 nil)
(def-system-variable kfep-hensaisyo-saventry KFEP1 0)

(defun kfep-kka-hensaisyo (sp inbuf inlen)
  (let* ((result? nil)
	 (ii 0)
	 (hyolen 0)
	 (hukalen 0)
	 (entry 0)
	 ;;(miscflg 0)
	 (loclen 0)
	 (scanpos 0)
	 (ava 0)
	 ;;(reset 0)
	 (dum 0)
;	 (pat 0) ; not used
	 battable-entry
	 hyoki
	 kohyoki
	 (bunpo 0))
    (declare (type fixnum
		   hyolen hukalen entry
		   ;;miscflg
		   loclen scanpos ava
		   ;;reset
		   dum
;		   pat ; not used
		   ))
    (cond
      ((<=f inlen 0)
       ;; Return -1
       (setq result? -1))
      ((>f inlen (kfep-bunmax))		; Return (kfep-eka-toolong)
       (setq result? (kfep-eka-toolong)))
      (t
       (block nil
	 (setq kfep-batchyomilen inlen)
	 (copy-lisp-string-to-target
	   inbuf kfep-batchyomi 0 0 inlen)
	 
	 ;; Null-terminate kfep-batchyomi. [BUG FIX! (MHD 1/2/91)]
	 #+development				; fencepost problem?! (see "toolong"
						;   test above; notice that C version
						;   either includes the null character
						;   in the bcopy (our copy-lisp-string-to-
						;   target) or assumes the null character
						;   is lying there after the copy or might
						;   just have a bug in this area.  See also
						;   maximum-number-of-hiragana-bytes-to-
						;   translate, the use of which might, in
						;   fact, be masking any potential problems
						;   here! (MHD 1/2/90)
	 (test-assertion (<f inlen #.kfep-bunmax))
	 (setf (char kfep-batchyomi inlen) #.(code-char 0))
	 
	 
	 (setq kfep-hensaisyo-gonum 0)
	 (setq kfep-hensaisyo-getpos 0)
	 (setq kfep-hensaisyo-saventry 0)
	 (setq scanpos 0)
	 (setq kfep-hensaisyo-tno 0)
	 (loop for index from 0 below (kfep-bunsetumax)
	       do
	   (setq battable-entry (svref kfep-battable index))
	   (setf (kfep-batch-yomilen battable-entry) 0)
	   (setf (kfep-batch-hyolen battable-entry) 0)
	   (setf (kfep-batch-yomistpos battable-entry) 0)
	   (setf (kfep-batch-hukalen battable-entry) 0)
	   (setf (kfep-batch-entry battable-entry) 0)
	   (setf (kfep-batch-current battable-entry) 0)
	   (setf (char (kfep-batch-hyoki battable-entry) 0) #.(ascii-code-char 0))
	   (setf (kfep-batch-select battable-entry) (kfep-sel-none))
	   (setf (kfep-batch-buntable-bunbun battable-entry) (kfep-all-bunbits)))
	 ;(setq miscflg 0)
	 (setq hyolen 0)
	 (setq hukalen 0)
	 (setq entry 0)
	 
	 ;; Start of big for-loop
	 (setq ava 0)
	 (setq loclen kfep-batchyomilen)
	 (block break
	   (loop while (<=f scanpos kfep-batchyomilen)
		 do
	     (block continue
	       (when (>= kfep-hensaisyo-tno (kfep-bunsetumax))
		 (setq result? -1)
		 (return -1))
	       (multiple-value-setq (hyoki hyolen entry kfep-hensaisyo-gonum)
		 (kfep-kka-ghyoki kfep-batchyomi scanpos loclen))
	       (if (null hyoki)
		   ;; Then
		   (progn
		     (decff loclen 2)
		     (if (>=f loclen 0) (return-from continue))
		     (when (<f loclen 0)
		       (incff scanpos 2)
		       (incff ava 2)
		       (setq loclen (-f kfep-batchyomilen scanpos))))
		   ;; Else  /* START OF BIG ELSE */
		   (progn
		     (when (=f (kfep-find-used kfep-hensaisyo-gonum)
			       (kfep-sel-none))
		       (decff loclen -2)
		       (return-from continue))
		     (when (>f ava 0)
		       (if (>f kfep-hensaisyo-tno 0)
			   (incff (kfep-batch-hukalen
				   (svref kfep-battable
					 (-f kfep-hensaisyo-tno 1)))
				  ava)
			   (let* ((cur-0 (kfep-cur 0)))
			     (if (>f (kfep-batch-hyolen cur-0) 0)
				 (incff (kfep-batch-hukalen cur-0) ava)
				 (setf  (kfep-batch-hukalen cur-0) ava))
			     (setq hyolen 0)
			     (setq ava 0)
			     (incff kfep-hensaisyo-tno)
			     (return-from continue)))
		       (setq ava 0))
		     (if (and (=f kfep-hensaisyo-tno 0)
			      (=f hyolen 0))
			 (progn		; Do nothing.
			   )
			 (let* ((battable-tno
				 (svref kfep-battable kfep-hensaisyo-tno))
				(old-hyoki (kfep-batch-hyoki battable-tno)))
			   (reclaim-lisp-string old-hyoki)
			   (setf (kfep-batch-hyoki battable-tno)
				 (copy-managed-lisp-string hyoki 0 hyolen))
			   (setf (kfep-batch-hyolen battable-tno) hyolen)
			   (setf (kfep-batch-yomilen battable-tno) loclen)))
		     (let* ((battable-tno
			     (svref kfep-battable kfep-hensaisyo-tno)))
		       (if (=f kfep-hensaisyo-tno 0)
			   (setf (kfep-batch-yomistpos battable-tno) 0)
			   (setf (kfep-batch-yomistpos battable-tno)
				 scanpos))
		       (setf (kfep-batch-nofyomi battable-tno)
			     kfep-hensaisyo-gonum)
		       (setf (kfep-batch-select battable-tno)
			     (kfep-find-used kfep-hensaisyo-gonum))
		       (setf (kfep-batch-setuzoku battable-tno)
			     (kfep-find-bunpo kfep-hensaisyo-gonum))
		       (setf (kfep-batch-entry battable-tno) entry)
		       (setf (kfep-batch-current battable-tno) 0))
		     (incff scanpos loclen)
		     (setq loclen (-f kfep-batchyomilen scanpos))
		     (if (>=f scanpos kfep-batchyomilen)
			 (return-from break))
		     (setq hukalen loclen)
		     (let* ((battable-tno
			     (svref kfep-battable kfep-hensaisyo-tno))
			    (batchyomi-substring
			     (copy-managed-lisp-string
			      kfep-batchyomi scanpos
			      (-f (kfep-bunmax) scanpos))))
		       (multiple-value-setq (dum bunpo
;					     pat ; not used
					     )
			 (kfep-chkbunpo (kfep-batch-hyoki battable-tno)
					(kfep-batch-hyolen battable-tno)
					batchyomi-substring
					hukalen))
		       (reclaim-lisp-string batchyomi-substring)
		       (setq hukalen dum)
		       (setf (kfep-batch-buntable-bunbun battable-tno) bunpo))
		     (tagbody
		      (if (not (and (>f hukalen 0) (/=f sp scanpos)))
			  (go SKIP))
		      (if (=f (kfep-batch-setuzoku
				(kfep-cur kfep-hensaisyo-tno))
			      0)
			  (go SKIP))
		      (let* (
			     ;;ishouki-result
			     ho)
;			(let* ((batchyomi-scanpos
;				(copy-managed-lisp-string
;				 kfep-batchyomi scanpos
;				 (-f (kfep-bunmax) scanpos))))
;			  (multiple-value-setq (ishouki-result ii)
;			    (kfep-kka-ishouki kfep-batchyomi scanpos hukalen
;					      (-f kfep-batchyomilen scanpos)))
;			  (reclaim-lisp-string batchyomi-scanpos))
;			(if (=f ishouki-result 0)
;			    (if (or (=f pat 1) (=f pat 3))
;				(go SKIP)))
			(setq ho (kfep-chkcattr kfep-batchyomi
						(+f scanpos hukalen)))
			(if (or (=f ho (kfep-kka-nn)) (=f ho (kfep-kka-mini)))
			    (go SKIP))
			(setf (kfep-batch-hukalen
			       (svref kfep-battable kfep-hensaisyo-tno))
			      hukalen)
			(incff scanpos hukalen)
			(setq loclen (-f kfep-batchyomilen scanpos))
			(if (>=f scanpos kfep-batchyomilen)
			    (return-from break)))
		      (go FINISH)
		      SKIP
		      (setf (kfep-batch-hukalen (svref kfep-battable
						      kfep-hensaisyo-tno)) 0)
		      FINISH)
		     (let* ((battable-tno
			     (svref kfep-battable kfep-hensaisyo-tno)))
		       (setq kohyoki
			     (kfep-kka-kofind
			      (kfep-batch-nofyomi battable-tno)
			      (kfep-batch-hyolen battable-tno)))
		       (when kohyoki
			 (copy-lisp-string-to-target
			  kohyoki
			  (kfep-batch-hyoki battable-tno)
			  0 0
			  (kfep-batch-hyolen battable-tno))

			 ;; This step was left out in the C version:
			 (reclaim-lisp-string kohyoki)))
		     (incff kfep-hensaisyo-tno)))
	       )))
	 ;; End of big for-loop
	 

	 (when (null result?)
	   (when (>f ava 0)
	     (if (<=f kfep-hensaisyo-tno 0)
		 (progn
		   (setq battable-entry (svref kfep-battable 0))
		   (setf (kfep-batch-yomilen battable-entry) 0)
		   (setf (kfep-batch-yomistpos battable-entry) 0)
		   (incff (kfep-batch-hukalen battable-entry) ava))
		 (progn
		   (setq battable-entry (svref kfep-battable
					      (-f kfep-hensaisyo-tno 1)))
		   (incff (kfep-batch-hukalen battable-entry) ava)
		   (decff kfep-hensaisyo-tno))))
	   
	   (setq battable-entry (svref kfep-battable kfep-hensaisyo-tno))
	   (setq ava
		 (+f (kfep-batch-yomistpos battable-entry)
		     (kfep-batch-yomilen battable-entry)
		     (kfep-batch-hukalen battable-entry)))
	   (if (<f ava kfep-batchyomilen)
	       (incff (kfep-batch-hukalen battable-entry)
		      (-f kfep-batchyomilen ava)))
	   
	   (if (and (and (>f kfep-hensaisyo-tno 0)
			 (=f (kfep-batch-yomilen battable-entry) 0))
		    (=f (kfep-batch-hukalen battable-entry) 0))
	       (decff kfep-hensaisyo-tno))
	   
	   (when (>f scanpos kfep-batchyomilen)
	     (setq battable-entry (kfep-cur kfep-hensaisyo-tno))
	     (if (>f (kfep-batch-hukalen battable-entry) 0)
		 (progn
		   (setq ii (kfep-batch-hukalen battable-entry))
		   (setf (kfep-batch-hukalen battable-entry)
			 (maxf (-f ii (-f scanpos kfep-batchyomilen)) 0)))
		 (progn
		   (setq ii (kfep-batch-yomilen battable-entry))
		   (setf (kfep-batch-yomilen battable-entry)
			 (maxf (-f ii (-f scanpos kfep-batchyomilen)) 0)))))
	   
	   (setq battable-entry (svref kfep-battable kfep-hensaisyo-tno))
	   (when (and (/=f (kfep-batch-select battable-entry) (kfep-sel-none))
		      (>f (kfep-batch-hyolen battable-entry) 0))
	     (let* ((battable-tno
		      (svref kfep-battable kfep-hensaisyo-tno)))
	       (setq kohyoki
		     (kfep-kka-kofind
		       (kfep-batch-nofyomi battable-tno)
		       (kfep-batch-hyolen battable-tno)))
	       (when kohyoki
		 (copy-lisp-string-to-target
		   kohyoki
		   (kfep-batch-hyoki battable-tno)
		   0 0
		   (kfep-batch-hyolen battable-tno))
		 
		 ;; This step was left out in the C version:
		 (reclaim-lisp-string kohyoki)
		 
		 )))
	   (setq kfep-kka-usetblnum (+f kfep-hensaisyo-tno 1))
	   (cond
	     ((or (/=f kfep-batchyomilen inlen)
		  (not (string= kfep-batchyomi inbuf
				:end1 kfep-batchyomilen :end2 kfep-batchyomilen)))
	      (setq kfep-kka-usetblnum 0)
	      (setq kfep-hensaisyo-gonum 0)
	      (setq kfep-hensaisyo-getpos 0)
	      (setq kfep-hensaisyo-saventry 0)
	      (setq scanpos 0)
	      (setq kfep-hensaisyo-tno 0)
	      ;; Return -1:
	      (setq result? -1))
	     (t
	      (loop for index from 0 to kfep-hensaisyo-tno
		    do
		(setq battable-entry (svref kfep-battable index))
		(setf (kfep-batch-total battable-entry)
		      (+f (kfep-batch-yomilen battable-entry)
			  (kfep-batch-hukalen battable-entry))))
	      ;; Return 0:
	      (setq result? 0))))))
      ;; END OF else not EKA_TOOLONG
      )
    (if result? result? 0)))








#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)

;; Possible values of sw (switch):

(defmacro-for-constant kkaprimitive-first-candidate 1)
(defmacro-for-constant kkaprimitive-next-candidate 0)

)



;;; `kfep-kka-p-batkanakan' ... is the main function for translating from
;;; Hiragana to Kanji.  If switch is kkaprimitive-next-candidate, the function
;;; assumes that a Hiragana string is being given to it for translation.
;;; If switch is #.kkaprimitive-first-candidate, the function returns the
;;; next choice available (if any) for the last translation.

;;; This function returns the following 3 values:
;;; 
;;;   (1) -1 or yomilen (a fixnum integer)
;;;   (2) number of bytes placed in the output buffer
;;;   (3) number of candidates left
;;;
;;; However, values (2) and (3) should be ignored if value (1) <= 0.


(def-system-variable kfep-kka-p-batkanakan-position KFEP1 0)

;; BEEP!! HOW CAN THIS WORK UNDER TELEWINDOWS?!!!  This must be made editor-
;; instance specific!! (MHD 1/3/91) -- answer: this is never used to hold
;; state except between calls within a tight loop that exhaustively collects
;; all choices.  See get-list-of-choices-of-kanji-translation. (MHD 1/3/91)

(defun kfep-kka-p-batkanakan (switch inbuf inlen outbuf)
  (g2-stream-with-non-character-mode
    (let ((first-battable-entry (svref kfep-battable 0)))
      (cond
	((not (and (case switch
		     (#.kkaprimitive-next-candidate
		      (incff kfep-kka-p-batkanakan-position)
		      (not (>f kfep-kka-p-batkanakan-position	; if > # entries less 1
			       (kfep-batch-entry first-battable-entry))))
		     (#.kkaprimitive-first-candidate
		      (if (<f (kfep-kka-hensaisyo 0 inbuf inlen) 0)
			  nil
			  (setq kfep-kka-p-batkanakan-position 0))))
		   (not (=f kfep-kka-usetblnum 0))))
	 (values -1 0 0))
	(t	 
	 (let* (fill-index			; "n" in C version
		increment-index			; "i" in C version
		outlen				; var parameter in C version
		number-of-candidates)		; var parameter, "cand" C version
	   (multiple-value-setq-some (nil fill-index)
	     (kfep-kka-gtango			; 1st value, gtango-result, ignored
	       (kfep-batch-hyoki first-battable-entry)
	       (kfep-batch-hyolen first-battable-entry)
	       kfep-kka-p-batkanakan-position
	       outbuf))
	   (setq increment-index
		 (-f kfep-batchyomilen
		     (kfep-batch-yomilen first-battable-entry)))
	   (when (>f increment-index 0)
	     (setf (char outbuf fill-index) #.(ascii-code-char 0))
	     (strcat-1
	       outbuf kfep-batchyomi 0
	       (kfep-batch-yomilen first-battable-entry))
	     (incff fill-index increment-index))
	   (setq outlen fill-index)
	   (setf (kfep-batch-select first-battable-entry)
		 (kfep-sel-kanji))
	   (setf (kfep-batch-current first-battable-entry)
		 kfep-kka-p-batkanakan-position)
	   (setq number-of-candidates
		 (-f (-f (kfep-batch-entry first-battable-entry)
			 kfep-kka-p-batkanakan-position)
		     1))
	   (values
	     (kfep-batch-yomilen first-battable-entry)
	     outlen
	     number-of-candidates)))))))

;; At present, inbuf is only used if switch is #.kkaprimitive-first-candidate.
;; Perhaps it will be needed, however, to make the next-candidate case
;; work for multiple G2 edit windows.  (MHD 1/3/91)

;; Note that the extra C function variables ("outlen" and "cand") are used
;; as VAR parameters.  The are therefore not needed as parameters.  They are
;; incorporated into the result as the second value, outlen, and the third
;; value, number-of-candidates.





;;; `Kfep-kka-p-update-kojin' from kkaprimitive.c ...

(defun kfep-kka-p-update-kojin (candidate-index)
  ;;
  ;; MORE WORK HERE
  ;;
  candidate-index
  )





;;; `Kfep-kka-kodone' from kkakojin.c ...

(defun kfep-kka-kodone ()
  ;;
  ;; MORE WORK HERE
  ;;
  )


(defun kfep-kka-madone ()
  ;;
  ;; MORE WORK HERE
  ;;
  )








;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-

(in-package "AB")
     
;;;; Module KEYDEFS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author: Fred White


(declare-forward-reference classify-character-for-text-line-drawing-function function)

#+development
(clear-all-key-code-information)


;;; Illegal Key.

(def-keysym "Illegal-Key" illegal-key-index)


;;; In general, the names of characters, and their codes, come from X library
;;; file keysymdef.h, which has specifically been found at
;;; 
;;;     /usr/local/include/X11/keysymdef.h
;;;
;;; Deprecated duplicate keysyms are not included.  E.g., |Ukranian_je|, which
;;; is marked in the .h file as "/* deprecated */" and is a duplicate for the
;;; same code as |Ukrainian_ie|, is not mentioned here.


;;; The ASCII control characters represented here are unusual in that they do
;;; not have the control-bit set, yet they still satisfy control-character-p.
;;; In fact, no combination of keypresses by the user should be able to generate
;;; a key-code which is one of these with the control bit set.

;;; AS OF 5.0 ON 3/21/96, all of the symbols specified as the key-name arg to
;;; def-keysym or def-bindable-keysym must be legal Gensym symbols, meaning that
;;; their print name must be in the character set and encoding used for
;;; user-visible symbols, i.e., UTF-G, previously just known as the Gensym
;;; character set encoding for text strings.  Thus, occurrences of @, \, and
;;; ~ have generally been changed below to ~@, ~\, and ~~, respectively.  It
;;; appears that not doing this previously may have led to some bugs that Fred
;;; White (FMW) could not overcome, and this led to certain keys not being made
;;; bindable.  These cases should now be reviewed.  The right thing would be for
;;; them to be treated no differently for the user than any other key for a
;;; normal ASCII character. (MHD 3/21/96)

(def-keysym |Control+~@|  0 char-control-@)
(def-keysym |Control+a|  1 char-control-a)
(def-keysym |Control+b|  2 char-control-b)
(def-keysym |Control+c|  3 char-control-c)
(def-keysym |Control+d|  4 char-control-d)
(def-keysym |Control+e|  5 char-control-e)
(def-keysym |Control+f|  6 char-control-f)
(def-keysym |Control+g|  7 char-control-g)
(def-keysym |Control+h|  8 char-control-h)
(def-keysym |Control+i|  9 char-control-i)
(def-keysym |Control+j|  10 char-control-j)
(def-keysym |Control+k|  11 char-control-k)
(def-keysym |Control+l|  12 char-control-l)
(def-keysym |Control+m|  13 char-control-m)
(def-keysym |Control+n|  14 char-control-n)
(def-keysym |Control+o|  15 char-control-o)
(def-keysym |Control+p|  16 char-control-p)
(def-keysym |Control+q|  17 char-control-q)
(def-keysym |Control+r|  18 char-control-r)
(def-keysym |Control+s|  19 char-control-s)
(def-keysym |Control+t|  20 char-control-t)
(def-keysym |Control+u|  21 char-control-u)
(def-keysym |Control+v|  22 char-control-v)
(def-keysym |Control+w|  23 char-control-w)
(def-keysym |Control+x|  24 char-control-x)
(def-keysym |Control+y|  25 char-control-y)
(def-keysym |Control+z|  26 char-control-z)
(def-keysym |Control+\[| 27 char-control-\[)
(def-keysym |Control+~\\| 28 char-control-backslash)
(def-keysym |Control+\]| 29 char-control-\])
(def-keysym |Control+^|  30 char-control-^)
(def-keysym |Control+_|  31 char-control-_)


;; Export only 6 function keys.
(def-bindable-keysym f1 405)
(def-bindable-keysym f2 406)
(def-bindable-keysym f3 407)
(def-bindable-keysym f4 408)
(def-bindable-keysym f5 420)
(def-bindable-keysym f6 421)

(def-bindable-keysym f7  422)
(def-bindable-keysym f8  423)
(def-bindable-keysym f9  424)
(def-bindable-keysym f10 425)
(def-bindable-keysym f11 426)
(def-bindable-keysym f12 427)

(def-keysym f13 428)
(def-keysym f14 429)
(def-keysym f15 430)
(def-keysym f16 431)
(def-keysym f17 432)
(def-keysym f18 433)
(def-keysym f19 434)
(def-keysym f20 435)
(def-keysym f21 436)
(def-keysym f22 437)
(def-keysym f23 438)
(def-keysym f24 439)
(def-keysym f25 440)
(def-keysym f26 441)
(def-keysym f27 442)
(def-keysym f28 443)
(def-keysym f29 444)
(def-keysym f30 445)
(def-keysym f31 446)
(def-keysym f32 447)
(def-keysym f33 448)
(def-keysym f34 449)
(def-keysym f35 450)


;; New keycodes (fmw 28-Jul-93).
(def-bindable-keysym backspace  278 char-backspace)
(def-bindable-keysym tab        279 char-tab)
(def-bindable-keysym linefeed   280 char-linefeed)
(def-bindable-keysym return     281 char-return)
(def-bindable-keysym escape     282 char-escape)


;; The printable ASCII characters.

(def-bindable-keysym \0  48 #\0)
(def-bindable-keysym \1  49 #\1)
(def-bindable-keysym \2  50 #\2)
(def-bindable-keysym \3  51 #\3)
(def-bindable-keysym \4  52 #\4)
(def-bindable-keysym \5  53 #\5)
(def-bindable-keysym \6  54 #\6)
(def-bindable-keysym \7  55 #\7)
(def-bindable-keysym \8  56 #\8)
(def-bindable-keysym \9  57 #\9)
(def-bindable-keysym \:  58 #\:)
(def-bindable-keysym \;  59 #\;)
(def-bindable-keysym <  60 #\<)
(def-bindable-keysym =  61 #\=)
(def-bindable-keysym >  62 #\>)
(def-bindable-keysym ?  63 #\?)
(def-keysym |~@|  64 #\@)					    ; Too hard to make bindable.
(def-bindable-keysym |A|  65 #\A)
(def-bindable-keysym |B|  66 #\B)
(def-bindable-keysym |C|  67 #\C)
(def-bindable-keysym |D|  68 #\D)
(def-bindable-keysym |E|  69 #\E)
(def-bindable-keysym |F|  70 #\F)
(def-bindable-keysym |G|  71 #\G)
(def-bindable-keysym |H|  72 #\H)
(def-bindable-keysym |I|  73 #\I)
(def-bindable-keysym |J|  74 #\J)
(def-bindable-keysym |K|  75 #\K)
(def-bindable-keysym |L|  76 #\L)
(def-bindable-keysym |M|  77 #\M)
(def-bindable-keysym |N|  78 #\N)
(def-bindable-keysym |O|  79 #\O)
(def-bindable-keysym |P|  80 #\P)
(def-bindable-keysym |Q|  81 #\Q)
(def-bindable-keysym |R|  82 #\R)
(def-bindable-keysym |S|  83 #\S)
(def-bindable-keysym |T|  84 #\T)
(def-bindable-keysym |U|  85 #\U)
(def-bindable-keysym |V|  86 #\V)
(def-bindable-keysym |W|  87 #\W)
(def-bindable-keysym |X|  88 #\X)
(def-bindable-keysym |Y|  89 #\Y)
(def-bindable-keysym |Z|  90 #\Z)
(def-bindable-keysym \[ 91 #\[)
(def-keysym |~\\| 92 #\\)		; Too hard to make bindable.-fmw -- especially with an illegal print name -mhd
(def-bindable-keysym \] 93 #\])
(def-bindable-keysym ^  94 #\^)
(def-bindable-keysym _  95 #\_)
(def-bindable-keysym \`  96 #\`)

(def-keysym |a|  97 #\a)
(def-keysym |b|  98 #\b)
(def-keysym |c|  99 #\c)
(def-keysym |d| 100 #\d)
(def-keysym |e| 101 #\e)
(def-keysym |f| 102 #\f)
(def-keysym |g| 103 #\g)
(def-keysym |h| 104 #\h)
(def-keysym |i| 105 #\i)
(def-keysym |j| 106 #\j)
(def-keysym |k| 107 #\k)
(def-keysym |l| 108 #\l)
(def-keysym |m| 109 #\m)
(def-keysym |n| 110 #\n)
(def-keysym |o| 111 #\o)
(def-keysym |p| 112 #\p)
(def-keysym |q| 113 #\q)
(def-keysym |r| 114 #\r)
(def-keysym |s| 115 #\s)
(def-keysym |t| 116 #\t)
(def-keysym |u| 117 #\u)
(def-keysym |v| 118 #\v)
(def-keysym |w| 119 #\w)
(def-keysym |x| 120 #\x)
(def-keysym |y| 121 #\y)
(def-keysym |z| 122 #\z)
(def-bindable-keysym \{ 123 #\{)
(def-bindable-keysym \| 124 #\|)
(def-bindable-keysym \} 125 #\})
(def-keysym |~~| 126 #\~)


(def-bindable-keysym space 32 #\space)
(def-bindable-keysym !  33 #\!)
(def-bindable-keysym \" 34 #\")
(def-bindable-keysym \#  35 #\#)
(def-bindable-keysym $  36 #\$)
(def-bindable-keysym %  37 #\%)
(def-bindable-keysym &  38 #\&)
(def-bindable-keysym \'  39 #\')
(def-bindable-keysym \(  40 #\()
(def-bindable-keysym \)  41 #\))
(def-bindable-keysym *  42 #\*)
(def-bindable-keysym +  43 #\+)
(def-bindable-keysym \,  44 #\,)
(def-bindable-keysym -  45 #\-)
(def-bindable-keysym \.  46 #\.)
(def-bindable-keysym /  47 #\/)


;; ISO Latin1 (other than ASCII)

(def-keysym |nobreakspace|        #xa0)
(def-keysym |exclamdown|          #xa1)
(def-keysym |cent|         	  #xa2)
(def-keysym |sterling|            #xa3)
(def-keysym |currency|            #xa4)
(def-keysym |yen|                 #xa5)
(def-keysym |brokenbar|           #xa6)
(def-keysym |section|             #xa7)
(def-keysym |diaeresis|           #xa8)
(def-keysym |copyright|           #xa9)
(def-keysym |ordfeminine|         #xaa)
(def-keysym |guillemotleft|       #xab)
(def-keysym |notsign|             #xac)
(def-keysym |hyphen|              #xad)
(def-keysym |registered|          #xae)
(def-keysym |macron|              #xaf)
(def-keysym |degree|              #xb0)
(def-keysym |plusminus|           #xb1)
(def-keysym |twosuperior|         #xb2)
(def-keysym |threesuperior|       #xb3)
(def-keysym |acute|               #xb4)
(def-keysym |mu|                  #xb5)
(def-keysym |paragraph|           #xb6)
(def-keysym |periodcentered|      #xb7)
(def-keysym |cedilla|             #xb8)
(def-keysym |onesuperior|         #xb9)
(def-keysym |masculine|           #xba)
(def-keysym |guillemotright|      #xbb)
(def-keysym |onequarter|          #xbc)
(def-keysym |onehalf|             #xbd)
(def-keysym |threequarters|       #xbe)
(def-keysym |questiondown|        #xbf)
(def-keysym |Agrave|              #xc0)
(def-keysym |Aacute|              #xc1)
(def-keysym |Acircumflex|         #xc2)
(def-keysym |Atilde|              #xc3)
(def-keysym |Adiaeresis|          #xc4)
(def-keysym |Aring|               #xc5)
(def-keysym |AE|                  #xc6)
(def-keysym |Ccedilla|            #xc7)
(def-keysym |Egrave|              #xc8)
(def-keysym |Eacute|              #xc9)
(def-keysym |Ecircumflex|         #xca)
(def-keysym |Ediaeresis|          #xcb)
(def-keysym |Igrave|              #xcc)
(def-keysym |Iacute|              #xcd)
(def-keysym |Icircumflex|         #xce)
(def-keysym |Idiaeresis|          #xcf)
(def-keysym |ETH|                 #xd0)
(def-keysym |Ntilde|              #xd1)
(def-keysym |Ograve|              #xd2)
(def-keysym |Oacute|              #xd3)
(def-keysym |Ocircumflex|         #xd4)
(def-keysym |Otilde|              #xd5)
(def-keysym |Odiaeresis|          #xd6)
(def-keysym |multiply|            #xd7)
(def-keysym |Ooblique|            #xd8)
(def-keysym |Ugrave|              #xd9)
(def-keysym |Uacute|              #xda)
(def-keysym |Ucircumflex|         #xdb)
(def-keysym |Udiaeresis|          #xdc)
(def-keysym |Yacute|              #xdd)
(def-keysym |THORN|               #xde)
(def-keysym |ssharp|              #xdf)
(def-keysym |agrave|              #xe0)
(def-keysym |aacute|              #xe1)
(def-keysym |acircumflex|         #xe2)
(def-keysym |atilde|              #xe3)
(def-keysym |adiaeresis|          #xe4)
(def-keysym |aring|               #xe5)
(def-keysym |ae|                  #xe6)
(def-keysym |ccedilla|            #xe7)
(def-keysym |egrave|              #xe8)
(def-keysym |eacute|              #xe9)
(def-keysym |ecircumflex|         #xea)
(def-keysym |ediaeresis|          #xeb)
(def-keysym |igrave|              #xec)
(def-keysym |iacute|              #xed)
(def-keysym |icircumflex|         #xee)
(def-keysym |idiaeresis|          #xef)
(def-keysym |eth|                 #xf0)
(def-keysym |ntilde|              #xf1)
(def-keysym |ograve|              #xf2)
(def-keysym |oacute|              #xf3)
(def-keysym |ocircumflex|         #xf4)
(def-keysym |otilde|              #xf5)
(def-keysym |odiaeresis|          #xf6)
(def-keysym |division|            #xf7)
(def-keysym |oslash|              #xf8)
(def-keysym |ugrave|              #xf9)
(def-keysym |uacute|              #xfa)
(def-keysym |ucircumflex|         #xfb)
(def-keysym |udiaeresis|          #xfc)
(def-keysym |yacute|              #xfd)
(def-keysym |thorn|               #xfe)
(def-keysym |ydiaeresis|          #xff)


(def-keysym |Serbian_dje|		#x6a1)
(def-keysym |Macedonia_gje|		#x6a2)
(def-keysym |Cyrillic_io|		#x6a3)
(def-keysym |Ukrainian_ie|		#x6a4)
(def-keysym |Macedonia_dse|		#x6a5)
(def-keysym |Ukrainian_i|		#x6a6)
(def-keysym |Ukrainian_yi|		#x6a7)
(def-keysym |Cyrillic_je|		#x6a8)
(def-keysym |Cyrillic_lje|		#x6a9)
(def-keysym |Cyrillic_nje|		#x6aa)
(def-keysym |Serbian_tshe|		#x6ab)
(def-keysym |Macedonia_kje|		#x6ac)
(def-keysym |Byelorussian_shortu|	#x6ae)
(def-keysym |Cyrillic_dzhe|		#x6af)
(def-keysym |numerosign|		#x6b0)
(def-keysym |Serbian_DJE|		#x6b1)
(def-keysym |Macedonia_GJE|		#x6b2)
(def-keysym |Cyrillic_IO|		#x6b3)
(def-keysym |Ukrainian_IE|		#x6b4)
(def-keysym |Macedonia_DSE|		#x6b5)
(def-keysym |Ukrainian_I|		#x6b6)
(def-keysym |Ukrainian_YI|		#x6b7)
(def-keysym |Cyrillic_JE|		#x6b8)
(def-keysym |Cyrillic_LJE|		#x6b9)
(def-keysym |Cyrillic_NJE|		#x6ba)
(def-keysym |Serbian_TSHE|		#x6bb)
(def-keysym |Macedonia_KJE|		#x6bc)
(def-keysym |Byelorussian_SHORTU|	#x6be)
(def-keysym |Cyrillic_DZHE|		#x6bf)
(def-keysym |Cyrillic_yu|		#x6c0)
(def-keysym |Cyrillic_a|		#x6c1)
(def-keysym |Cyrillic_be|		#x6c2)
(def-keysym |Cyrillic_tse|		#x6c3)
(def-keysym |Cyrillic_de|		#x6c4)
(def-keysym |Cyrillic_ie|		#x6c5)
(def-keysym |Cyrillic_ef|		#x6c6)
(def-keysym |Cyrillic_ghe|		#x6c7)
(def-keysym |Cyrillic_ha|		#x6c8)
(def-keysym |Cyrillic_i|		#x6c9)
(def-keysym |Cyrillic_shorti|		#x6ca)
(def-keysym |Cyrillic_ka|		#x6cb)
(def-keysym |Cyrillic_el|		#x6cc)
(def-keysym |Cyrillic_em|		#x6cd)
(def-keysym |Cyrillic_en|		#x6ce)
(def-keysym |Cyrillic_o|		#x6cf)
(def-keysym |Cyrillic_pe|		#x6d0)
(def-keysym |Cyrillic_ya|		#x6d1)
(def-keysym |Cyrillic_er|		#x6d2)
(def-keysym |Cyrillic_es|		#x6d3)
(def-keysym |Cyrillic_te|		#x6d4)
(def-keysym |Cyrillic_u|		#x6d5)
(def-keysym |Cyrillic_zhe|		#x6d6)
(def-keysym |Cyrillic_ve|		#x6d7)
(def-keysym |Cyrillic_softsign|		#x6d8)
(def-keysym |Cyrillic_yeru|		#x6d9)
(def-keysym |Cyrillic_ze|		#x6da)
(def-keysym |Cyrillic_sha|		#x6db)
(def-keysym |Cyrillic_e|		#x6dc)
(def-keysym |Cyrillic_shcha|		#x6dd)
(def-keysym |Cyrillic_che|		#x6de)
(def-keysym |Cyrillic_hardsign|		#x6df)
(def-keysym |Cyrillic_YU|		#x6e0)
(def-keysym |Cyrillic_A|		#x6e1)
(def-keysym |Cyrillic_BE|		#x6e2)
(def-keysym |Cyrillic_TSE|		#x6e3)
(def-keysym |Cyrillic_DE|		#x6e4)
(def-keysym |Cyrillic_IE|		#x6e5)
(def-keysym |Cyrillic_EF|		#x6e6)
(def-keysym |Cyrillic_GHE|		#x6e7)
(def-keysym |Cyrillic_HA|		#x6e8)
(def-keysym |Cyrillic_I|		#x6e9)
(def-keysym |Cyrillic_SHORTI|		#x6ea)
(def-keysym |Cyrillic_KA|		#x6eb)
(def-keysym |Cyrillic_EL|		#x6ec)
(def-keysym |Cyrillic_EM|		#x6ed)
(def-keysym |Cyrillic_EN|		#x6ee)
(def-keysym |Cyrillic_O|		#x6ef)
(def-keysym |Cyrillic_PE|		#x6f0)
(def-keysym |Cyrillic_YA|		#x6f1)
(def-keysym |Cyrillic_ER|		#x6f2)
(def-keysym |Cyrillic_ES|		#x6f3)
(def-keysym |Cyrillic_TE|		#x6f4)
(def-keysym |Cyrillic_U|		#x6f5)
(def-keysym |Cyrillic_ZHE|		#x6f6)
(def-keysym |Cyrillic_VE|		#x6f7)
(def-keysym |Cyrillic_SOFTSIGN|		#x6f8)
(def-keysym |Cyrillic_YERU|		#x6f9)
(def-keysym |Cyrillic_ZE|		#x6fa)
(def-keysym |Cyrillic_SHA|		#x6fb)
(def-keysym |Cyrillic_E|		#x6fc)
(def-keysym |Cyrillic_SHCHA|		#x6fd)
(def-keysym |Cyrillic_CHE|		#x6fe)
(def-keysym |Cyrillic_HARDSIGN|		#x6ff)




;;; The macro `simple-character-key-code-p' is equivalent to simple-character-p,
;;; but it takes a key code as its argument, instead of a character.

(defmacro simple-character-key-code-p (key-code)
  `(<=f 32 ,key-code 126))

;; This used to go to 127, which is delete, which was wrong.


;;; The macro `simple-gensym-character-key-code-p' is equivalent to
;;; simple-gensym-character-p, but it takes a key code as its argument, instead
;;; of a character.

(defmacro simple-gensym-character-key-code-p (key-code)
  `(let ((key-code ,key-code))
     (and (simple-character-key-code-p key-code)
	  ,@(loop for escape-character in (escape-characters)
		  collect `(not (=f key-code
				    ,(ascii-char-code escape-character)))))))



;;; The macro `convert-key-code-to-simple-character' takes a key code that
;;; represents a simple character, and converts it to a Common Lisp character.
;;; If the key code does not represent a simple character (i.e. it is not a
;;; simple character key code), this macro might cause an error.

(defmacro convert-key-code-to-simple-character (simple-character-key-code)
  `(code-char ,simple-character-key-code))




;;; The two macros `convert-key-code-to-simple-character-following-\~' and
;;; `special-character-key-code-p' know about ISO Latin1 character codes and our
;;; keycodes for them, or the non-ascii part at least, are the same.  No one
;;; else should need to know this.

(defmacro convert-key-code-to-simple-character-following-\~ (key-code)
  `(map-iso-latin1-code-to-simple-character-following-\~-if-any ,key-code))

(defmacro special-character-key-code-p (key-code)
  `(let ((key-code ,key-code))
     (if (<=f 32 key-code 255)
	 (convert-key-code-to-simple-character-following-\~ key-code))))





;;; `Convert-key-code-to-gensym-cyrillic-character-code' and
;;; `cyrillic-gensym-key-code-p' ...

(defmacro cyrillic-gensym-key-code-p (key-code)
  `(<=f #x6a1 ,key-code #x6ff))

(defun-simple convert-key-code-to-gensym-cyrillic-character-code (key-code)
  (let ((key-name?
	  (if (cyrillic-gensym-key-code-p key-code)
	      (svref key-index-to-key-symbol-array key-code))))
    (when key-name?
      (cyrillic-gensym-character-code-for-key-name key-name?))))



;;; `Gensym-character-key-code-p' is true if key-code can be mapped into
;;; a gensym character, nil otherwise.
;;;
;;; `Convert-key-code-to-gensym-character' returns either nil or two values,
;;; character-or-character-code and escape-character?.

(defmacro gensym-character-key-code-p (key-code)
  `(convert-key-code-to-gensym-character ,key-code))


(defun convert-key-code-to-gensym-character (key-code)
  (cond
    ((unicode-bit-on-p key-code)
     (map-unicode-to-gensym-character-code (key-unicode key-code)))
    ((simple-gensym-character-key-code-p key-code)
     (values
       (convert-key-code-to-simple-character key-code)
       nil))
    ((special-character-key-code-p key-code)
     (values
       (convert-key-code-to-simple-character-following-\~ key-code)
       #\~))
    ((cyrillic-gensym-key-code-p key-code)
     (values
       (convert-key-code-to-gensym-cyrillic-character-code key-code)
       #\\))
    ;; add other language/script blocks here
    ))



;;; `Convert-key-code-to-unicode' returns either nil or the Unicode wide
;;; character corresponding to key-code.  Note that key-code is generally gotten
;;; from the workstation-event-code slot of a workstation event; see
;;; WORKSTATIONS for further information.  Note that gensym-character-key-code-p
;;; can be used to determine if this would return a non-nil value.

(defun convert-key-code-to-unicode (key-code)
  (if (unicode-bit-on-p key-code)	; new case. (MHD 5/17/99)
      (key-unicode key-code)
      (multiple-value-bind (character-or-character-code? escape-character?)
	  (convert-key-code-to-gensym-character key-code)
	(when character-or-character-code?
	  (map-gensym-character-code-to-unicode
	    (gensym-character-pair-to-code
	      character-or-character-code? escape-character?))))))

;; This is intended to replace the convert-key-code-to-gensym-character as
;; exported functions.


(defun-substitution-macro upper-case-letter-key-code-p (key-code)
  (<=f 65 (key-index key-code) 90))

(defun-substitution-macro lower-case-letter-key-code-p (key-code)
  (<=f 97 (key-index key-code) 122))

(defun-substitution-macro letter-key-code-p (key-code)
  (or (upper-case-letter-key-code-p key-code)
      (lower-case-letter-key-code-p key-code)))

(defun-substitution-macro invert-case-of-letter-key-code (letter-key-code)
  (logxorf letter-key-code #x20))

(defun-substitution-macro upcase-letter-key-code (letter-key-code)
  (if (lower-case-letter-key-code-p letter-key-code)
      (logxorf letter-key-code #x20)
      letter-key-code))

(defun-substitution-macro key-code-for-space ()
  32)

(defun-substitution-macro unicode-space-p (key-code)
  (=f key-code #.(logiorf unicode-bit 32)))


;;; The function `canonical-key-modifier-bits' computes the set of modifier
;;; bits which we expose to the user, currently only in the
;;; user-mouse-tracking context.

(defun-substitution-macro canonical-key-modifier-bits (key-code)
  (logiorf (if (shift-bit-on-p key-code) 1 0)
	   (if (control-bit-on-p key-code) 2 0)
	   (if (alternate-bit-on-p key-code) 4 0)))




;;; The function `conventional-ascii-control-character-key-code-p' is true
;;; for key code which when combined with the control key yeild some
;;; conventional ASCII contol character: control+a, control+_, etc.

(defun-substitution-macro conventional-ascii-control-character-key-code-p (key-code)
  (or (lower-case-letter-key-code-p key-code)
      (=f key-code 64)			; @
      (<=f 91 key-code 95)))		; [\]^_

;; Gross predicate needed by special cases in `key-code-function'




(defun-substitution-macro printable-ascii-key-code-p (key-code)
  (<=f 32 key-code 126))


(defun-substitution-macro iso-latin-key-code-p (key-code)
  (<=f #xa0 key-code #xff))


;;; The function `printable-character-key-code-p' is true for a printable
;;; character, without modifiers.

(defun-simple printable-character-key-code-p (key-code)
  (if (unicode-bit-on-p key-code)
      (memq
	(classify-character-for-text-line-drawing-function
	  (code-wide-character (key-unicode key-code)))
	'(mark non-spacing-mark ordinary-space))
      (gensym-character-key-code-p key-code)))

;; Changed to a defun-simple, since there's no reason this needs to be a macro
;; for performance, and it just got bigger. (MHD 5/17/99)

;; The Unicode case here is new. It handles a superset of the non-unicode
;; cases. Callers were reviewed (2 of them), and it was verified that they could
;; all handle this being revised to handle Unicode. (MHD 5/17/99)

;; The newer way of implementing this means that ISO Latin1 characters that we
;; don't now handle won't be considered printable-character-key-code-p.  I think
;; that's OK.  When they do get handled, they'll be
;; printable-character-key-code-p. -- UPDATE: the way to go with this is
;; probably to use the newer Unicode character keys.  The old system is
;; entrenched, but redundant. (MHD 5/17/99)



;;; The function `shift-bit-is-implicit-in-key-code-p' is the same as
;;; printable-character-key-code-p, except that it excludes SPACE.

(defun-substitution-macro shift-bit-is-implicit-in-key-code-p (key-code)  
  (and (printable-character-key-code-p key-code)
       (not (=f (if (unicode-bit-on-p key-code)
		    (key-unicode key-code)
		    key-code)
		32))))		; printable character except space


;;; The function `rebindable-key-code-p' is true for any key codes which are
;;; potentially rebindable in item configurations.

(defun-substitution-macro rebindable-key-code-p (key-code)
  (and (not (illegal-key-code-p key-code))
       #+ignore (not (printable-character-key-code-p key-code))))

;; Note that this has been changed to be currently implemented as a macro,
;; mostly to avoid forward referencing problems. (MHD 3/23/95)



;; On conventional machines, the Rubout key is actually labelled Delete or DEL.
;; Do we ever distinguish DELETE, DEL and RUBOUT?  X doesn't.

(def-bindable-keysym delete 127 char-rubout)
(def-keysym del       128)
(def-keysym rubout    135)




;;; Key Codes for Mouse and Window Events

(def-keysym non-event       768)

(def-keysym mouse-up        769)
(def-keysym mouse-down      770)
(def-keysym mouse-motion    771)

(def-keysym mouse-left-down   772)
(def-keysym mouse-left-up     773)
(def-keysym mouse-middle-down 774)
(def-keysym mouse-middle-up   775)
(def-keysym mouse-right-down  776)
(def-keysym mouse-right-up    777)

;; X allows for 5 buttons.  Should we?

;; New mouse-events, which are only generated internally by G2.
(def-keysym mouse-drag 778)
(def-keysym mouse-select 779)

;; Mouse wheel events, which actually behave more like keystrokes, so we define
;; them as such.  The name here is what a user will see in restrictions.
;; Until we define a nicer grammer, like "rolling mouse wheel forward", instead
;; of "typing mouse-wheel-forward".
(def-bindable-keysym mouse-wheel-forward 780)
(def-bindable-keysym mouse-wheel-backward 781)

;; Mouse-hover is also treated like a keystroke.
(def-bindable-keysym mouse-hover 782)

(defmacro key-code-is-mouse-wheel-p (key-code)
  `(member (key-index ,key-code) '(780 781)))

(defmacro key-code-is-mouse-up-p (key-code)
  `(member (key-index ,key-code) '(769 773 775 777)))

(defmacro key-code-is-mouse-left-up-p (key-code)
  ;; 769 (generic mouse-up) for compatibility. (MHD 1/13/02)
  `(member (key-index ,key-code) '(769 773)))

(defmacro key-code-is-mouse-middle-up-p (key-code)
  `(member (key-index ,key-code) '(775)))

(defmacro key-code-is-mouse-right-up-p (key-code)
  `(member (key-index ,key-code) '(777)))

(defmacro key-code-is-mouse-down-p (key-code)
  `(member (key-index ,key-code) '(770 772 774 776)))

(defmacro key-code-is-mouse-left-down-p (key-code)
  ;; 770 (generic mouse-down) for compatibility. (MHD 3/18/98)
  `(member (key-index ,key-code) '(770 772)))

(defmacro key-code-is-mouse-middle-down-p (key-code)
  `(member (key-index ,key-code) '(774)))

(defmacro key-code-is-mouse-right-down-p (key-code)
  `(member (key-index ,key-code) '(776)))

(defmacro key-code-is-mouse-motion-p (key-code)
  `(=f (key-index ,key-code) 771))

(defmacro key-code-is-mouse-hover-p (key-code)
  `(=f (key-index ,key-code) 782))

(defmacro key-code-is-mouse-generic-p (key-code)
  `(member (key-index ,key-code) '(769 770 779))) ; mouse-up, mouse-down, mouse-select


(defmacro mouse-down-event-p (key-code)
  `(key-code-is-mouse-down-p ,key-code))

(defmacro mouse-up-event-p (key-code)
  `(key-code-is-mouse-up-p ,key-code))

(defmacro mouse-motion-event-p (key-code)
  `(key-code-is-mouse-motion-p ,key-code))

(defmacro mouse-select-event-p (key-code)
  `(=f (key-index ,key-code) 779))

(defmacro mouse-hover-event-p (key-code)
  `(key-code-is-mouse-hover-p ,key-code))



;; Assuming it is the code of a mouse-up or mouse-down event.
(defmacro convert-mouse-key-code-to-mouse-up (mouse-key-code)
  `(logiorf ,mouse-key-code 1))

#+development
(defun mouse-key-code-button-name (mouse-key-code)
  (case (convert-mouse-key-code-to-mouse-up mouse-key-code)
    (773 "left")
    (775 "middle")
    (777 "right")
    (769 "any")))

(defun mouse-key-code-button-name-symbol (mouse-key-code)
  (case (convert-mouse-key-code-to-mouse-up mouse-key-code)
    (773 'left)
    (775 'middle)
    (777 'right)
    (769 'any)))



;;;; Pseudo Keysyms


;;; A `pseudo-keysym' is a keysym which does not represent a keyboard or mouse
;;; event, but rather some higher-level synthetic event, such as a window was
;;; moved or the contents of the clipboard was requested. Most of these were
;;; added in 7.0 and 8.0.

(def-concept pseudo-keysym)

(defun pseudo-key-code-p (key-code)
  (not (null (memq (convert-key-code-to-key-symbol key-code) pseudo-keysyms))))

;; Note: the dated comments apply to when these keysyms were originally added
;; with def-keysym. def-keysym was changed to def-pseudo-keysym by -fmw,
;; 12/2/03.

(def-pseudo-keysym window-refresh 784)	   ; Not the same as REFRESH. Used in 8.0
(def-pseudo-keysym window-reshape 785)

(def-pseudo-keysym paste-request 786)	   ; new in 5.0 (MHD 3/21/97)
(def-pseudo-keysym paste-availability-request 787) ; new in 5.0r1 (LGibson 7/31/97)

(def-pseudo-keysym window-activated 788)   ; New in 8.0: WM_ACTIVATE and FocusIn events.
(def-pseudo-keysym window-closed 789)	   ; New in 8.0: After WM_CLOSE has happened.
(def-pseudo-keysym enter-window 790)	   ; Added for OLE (jh, 1/29/96)
(def-pseudo-keysym leave-window 791)	   ; Ditto
(def-pseudo-keysym window-moved 792)	   ; New in 8.0: New position of client area
(def-pseudo-keysym window-sized 793)	   ; New in 8.0: New size of client area
(def-pseudo-keysym window-scrolled 794)	   ; New in 8.0

(def-keysym double-escape  800)





;;; The special-purpose keysyms simple-dialog-ok, simple-dialog-cancel, and
;;; simple-dialog-additional are for use in simple dialogs (see simple-dialog,
;;; the concept).

(def-pseudo-keysym simple-dialog-ok 801)
(def-pseudo-keysym simple-dialog-cancel 802)
(def-pseudo-keysym simple-dialog-additional 803)

;; New in G2 7.0 (MHD 1/31/02)

;; Gap at 804; possibly for future use with simple dialogs. (MHD 3/13/02)


;;; The keysym `menu-choice' is a message from a native menu.  The x value is
;;; the ID of the item chosen, or 0 if menu was dismissed without choosing. See
;;; mdi_child_on_wm_command in ext/c/msmain.c

(def-pseudo-keysym menu-choice 804)


;;; The special-purpose keysyms file-open and file-save-as are for use in a
;;; file-open and file-save-as dialogs, respectively.

;; No existing TW release will send this codes, so they can be reused.
(def-pseudo-keysym file-open 805)	   ; Unused
(def-pseudo-keysym file-save-as 806)	   ; Unused

;; New in G2 7.0 (MHD 3/13/02)


;;; The `hscroll' and `vscroll' keysyms are messages from a scrollbar control or
;;; widget.  The message's x value is the scrollbar code (SB_LINEUP,
;;; SB_PAGEDOWN, SB_THUMBTRACK, etc), and the y value is the current thumb
;;; position. Obsolete: 7.0 multiwindow mode only.

(def-pseudo-keysym hscroll 810)
(def-pseudo-keysym vscroll 811)



;;;; Synthetic mouse key codes


;;; `mouse-select' and `mouse-drag' are synthetic events we create for a mouse
;;; down/up with or without intermediate motion (see mouse-drag-detector).  We
;;; now need to know which button went down and up, hence some new keycodes.

(def-keysym mouse-left-select 812)
(def-keysym mouse-middle-select 813)
(def-keysym mouse-right-select 814)

(defmacro key-code-is-mouse-select-p (key-code)
  (let ((key-index (gensym)))
  `(let ((,key-index (key-index ,key-code)))
     (or (=f ,key-index 779)
	 (=f ,key-index 812)
	 (=f ,key-index 813)
	 (=f ,key-index 814)))))


(def-keysym mouse-left-drag 815)
(def-keysym mouse-middle-drag 816)
(def-keysym mouse-right-drag 817)

(defmacro key-code-is-mouse-drag-p (key-code)
  (let ((key-index (gensym)))
    `(let ((,key-index (key-index ,key-code)))
       (or (=f ,key-index 778)
	   (=f ,key-index 815)
	   (=f ,key-index 816)
	   (=f ,key-index 817)))))


;;; The macro `mouse-key-code-p' is true for any mouse event:
;;; up/down/drag/select, with any combination of modifier
;;; keys.

(defmacro mouse-key-code-p (code)
  `(or (<=f 769 (key-index ,code) 779)
       (key-code-is-mouse-select-p ,code)
       (key-code-is-mouse-drag-p ,code)))


    
;;; Various keysyms used to dispatch incoming events from native controls on
;;; TW. These events generally have even-plist's with more information.

(def-pseudo-keysym menu-bar 818)	   ; Eg, request to gray/ungray

(def-pseudo-keysym file-dialog 819)	   ; Choice from native file open/save dialog.

(def-pseudo-keysym status-bar 820)	   ; Someday: click on status bar

(def-pseudo-keysym pre-nms-menu-choice 821) ; Used by built-in popup menus.

(def-pseudo-keysym print-window 822)	   ; Print Telewindow (routed locally on TW)

(def-pseudo-keysym about-box 823)	   ; TW About box (routed locally on TW)

(def-pseudo-keysym print-dialog 824)	   ; Choice from native print dialog.

(def-pseudo-keysym nms-menu-posted 825)	   ; Dynamic NMS menu was posted (WM_INITPOPUPMENU)

(def-pseudo-keysym basic-dialog 826)	   ; Choice from various uncomplicated native dialogs.

(def-pseudo-keysym nms-control 827)	   ; Message from an NMS control

(def-pseudo-keysym dialog-update 828)	   ; The user has modified an active dynamic dialog

(def-pseudo-keysym dialog-dismissed 829)   ; The user has dismissed an active dynamic dialog

(def-pseudo-keysym list-directory 830)	   ; Request for directory listing on server.

(def-pseudo-keysym dialog-miscellaneous-communication 831)
			; Other information TW needs to send to G2 regarding dialogs

(def-pseudo-keysym nms-menu-item-selected 832) ; NMS menu item selected (WM_MENUSELECT)

(def-pseudo-keysym tree-view 833)	   ; Message from a native tree view

(def-pseudo-keysym html-view 834)	   ; Message from a native HTML view

(def-pseudo-keysym debugger-dialog 835)	   ; Message from a native debugger dialog

(def-pseudo-keysym editor 836)		   ; Message from a native editor

(def-pseudo-keysym nms-menu-unposted 837)  ; NMS menu was unposted (WM_UNINITPOPUPMENU)

(def-pseudo-keysym shortcut-bar 838)	   ; Message from shortcut bar

(def-pseudo-keysym chart-view 839)	   ; Message from a native chart view

(def-pseudo-keysym logbook-view 840)	   ; Message from a native logbook/message board

(def-pseudo-keysym login-dialog 841)	   ; Message from a modal native login/password dialog

(def-pseudo-keysym prop-grid 842)	   ; Message from a property grid control

(def-pseudo-keysym dialog-user-gesture 843)
                      ; A user gesture on a dialog control

(def-pseudo-keysym grid-view 844)	   ; Message from a native grid view

(def-pseudo-keysym tabular-view 845)	   ; Message from a tabular view

(def-pseudo-keysym list-sys-drives 846)    ; Request from custom file dialog for system drives listing

;;;; Key Symbols for X keyboards



(def-bindable-keysym break 385)
;; Enter is Return on TI's
(def-bindable-keysym enter 660)
						

;; Some keypad keys
;; These are not bindable, as of 10/19/94.  Many keyboards don't distinguish
;; keypad digits from real digits, for example.
(def-keysym kp-space 453)
(def-keysym kp-tab 454)
(def-keysym kp-enter 455)
(def-keysym kp-f1 456)
(def-keysym kp-f2 457)
(def-keysym kp-f3 458)
(def-keysym kp-f4 459)
(def-keysym kp-equal 460)
(def-keysym kp-multiply 461)
(def-keysym kp-add 462)
(def-keysym kp-separator 463)
(def-keysym kp-subtract 464)
(def-keysym kp-decimal 465)
(def-keysym kp-divide 466)
(def-keysym kp-0 470)
(def-keysym kp-1 471)
(def-keysym kp-2 472)
(def-keysym kp-3 473)
(def-keysym kp-4 474)
(def-keysym kp-5 475)
(def-keysym kp-6 476)
(def-keysym kp-7 477)
(def-keysym kp-8 478)
(def-keysym kp-9 479)


;; Some random X keysyms.
(def-bindable-keysym help 390)
(def-bindable-keysym insert 480)
(def-bindable-keysym redo 481)
(def-bindable-keysym menu 482)
(def-bindable-keysym find 483)
(def-bindable-keysym home 484)
(def-bindable-keysym begin 485)
(def-bindable-keysym end  404)
(def-bindable-keysym pause 486)
(def-bindable-keysym select 487)
(def-bindable-keysym print 488)
(def-bindable-keysym execute 489)			    ;?
(def-bindable-keysym abort 401)				    ; CANCEL X keysym.
(def-bindable-keysym clear-screen 396)			    ; The X keysym CLEAR


(def-keysym forward-delete 384)				    ; Unused.
(def-keysym page-up 387)				    ; PRIOR X keysym
(def-keysym page-down 389)				    ; NEXT X keysym.

;; The key codes of the arrow keys are based on VMS's
;; interrupts (see vms-key-event-handler in PRIMIVITES).
(def-bindable-keysym up-arrow 274)
(def-bindable-keysym down-arrow 275)
(def-bindable-keysym left-arrow 276)
(def-bindable-keysym right-arrow 277)



;; Vax Keyboard UIS key code
(def-bindable-keysym previous-screen 315)
(def-bindable-keysym next-screen 316)
  


;; Lisp Machines (all obsolete)
;; Maybe key-code should warn that these are obsolete?
(def-keysym network      414)
(def-keysym clear-input  386)
(def-keysym resume       402)

;; Symbolics
(def-keysym function     644)
(def-keysym refresh      395)
(def-keysym square       661)
(def-keysym circle       662)
(def-keysym triangle     663)
(def-keysym suspend      641)
(def-keysym page         652)
(def-keysym complete     416)
(def-keysym line         394)
(def-keysym scroll       666)


;; TI
(def-keysym system       413)
(def-keysym status       403)
(def-keysym term         388)
(def-keysym undo         415)
(def-keysym left         409)
(def-keysym middle       410)
(def-keysym right  	 411)



;;;; More key-code predicates



;;; The function `key-code-available-p' returns NIL if the given key-code
;;; is unreachable on the platform for which we were compiled.

#+development
(defun key-code-available-p (key-code)
  (declare (ignore key-code))
  t)

;; This function needs to depend on the particular X connection!




(def-substitution-macro special-control-key-p (key-code)
  (<=f 0 (key-index key-code) 31))

;; This used to include RETURN, BACKSPACE, etc, in the list. (fmw 16-Aug-93)



(def-substitution-macro control-key-p (key-code)
  (or (special-control-key-p key-code)
      (control-bit-on-p key-code)))


;;;; Menu event codes

;; We need a different event for a menu choose on any menu item.
;; Since keycodes are fixnums, we have lots of room.

;; A keycode with the 25th bit set is a menu-choose, with a 10-bit
;; menu number and a 10-bit item number packed in.

;; Magic event code for menu-choose on a native menu.
;; Kind of like mouse-select in that it does not correspond to a key,
;; but to a higher level event.  Probably will need more of these,
;; or something better, for native widgets.

(def-substitution-macro key-code-is-native-menu-choice-p (key-code)
  (/=f (logandf menu-bit key-code) 0))

(def-substitution-macro key-code-menu-number (key-code)
  (logandf (ashf key-code -10) 1023))

(def-substitution-macro key-code-item-number (key-code)
  (logandf key-code 1023))


;; TODO: flush this stuff in favor of the newly working event plists.

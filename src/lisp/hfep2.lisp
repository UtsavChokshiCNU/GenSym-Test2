;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module HFEP2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David and Gretchen H. Wang




;;; The HFEP module supplies the Hangul Front-End Processing capability
;;; for the G2 editor.  This module is essentially a transformation of the
;;; public-domain hangul front-end processing facility dk.el -- "Direct Korean
;;; Input Utility for Nemacs.  (Nemacs is Niponese Emacs.)




;;;; Miscellaneous Transformation Conventions


;;; (1) Underscores (_) are tranformed to the more usual (for Lisp) hyphen (-).
;;; (2) Upper vs. Lowercase is generally not preserved.  Exceptions: Nchar & Cchar.
;;; (3) C characters represented explicity as integers are represented as
;;;     characters here.  Where possible, this is stylized using code-char, e.g.,
;;;     #.(code-char 0) <=> NULL <=> (in C) 0.
;;; (4) Throughout, "character" here means a Common Lisp character, as opposed to
;;;     its dual meaning of (ASCII) character and integer in the original C
;;;     version.
;;; (5) We do throughout assume that character codes for all characters are ASCII.
;;;     (This is not ultimately portable, but works in practice and is a traditional
;;;     shortcut employed in other modules of G2.)

;;; New for 5.0:  (MHD 5/21/96)
;;;
;;; char=   =>   char=w
;;; char<=  =>   char<=w
;;; char/=  =>   char/=w
;;; case    =>   wide-character-case
;;; char-code   =>   wide-character-code
;;; code-char   =>   code-wide-character





;;;; Map to Keyboard and KOR Alphabet



;;; Here we are transforming the macros (#defines) in hctbl.h.  They
;;; look like
;;;
;;;    #define G 'r'
;;;    #define GG 'R'
;;;    #define G_S 'S'
;;;    .
;;;    .
;;;    .
;;;
;;; For this purpose, we define the macro define-keyboard-to-kor-mappings.
;;; A single call to this appears at top-level.  It defines a series of
;;; defconstants whose names are like the original C macro names, but have
;;; "HFEP-" prepended, as well as underscores turned into hyphens.  They
;;; look like
;;;
;;;    (defconstant hfep-g #.%\r)
;;;    (defconstant hfep-gg #.%\R)
;;;    (defconstant hfep-g-s #.%\S)
;;;    .
;;;    .
;;;    .

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro define-keyboard-to-kor-mappings ()
  `(progn
     . ,(loop for (symbol . character)
		  in '((G . #.%\r)
		       (GG . #.%\R)
		       (G-S . #.%\S)
		       (N . #.%\s)
		       (N-J . #.%\J)
		       (N-H . #.%\H)
		       (D . #.%\e)
		       (DD . #.%\E)
		       (R . #.%\f)
		       (R-G . #.%\G)
		       (R-M . #.%\M)
		       (R-S . #.%\N)
		       (R-B . #.%\A)
		       (R-T . #.%\B)
		       (R-P . #.%\V)
		       (R-H . #.%\F)
		       (M . #.%\a)
		       (B . #.%\q)
		       (BB . #.%\Q)
		       (B-S . #.%\C)
		       (S . #.%\t)
		       (SS . #.%\T)
		       (OO . #.%\d)
		       (J . #.%\w)
		       (JJ . #.%\W)
		       (C . #.%\c)
		       (K . #.%\z)
		       (T . #.%\x)
		       (P . #.%\v)
		       (H . #.%\g)
		       (A . #.%\k)
		       (O-A . #.%\K)
		       (AI . #.%\o)
		       (YA . #.%\i)
		       (YAI . #.%\O)
		       (EO . #.%\j)
		       (U-EO . #.%\J)
		       (E . #.%\p)
		       (YEO . #.%\u)
		       (YE . #.%\P)
		       (O . #.%\h)
		       (O-AI . #.%\H)
		       (YO . #.%\y)
		       (U . #.%\n)
		       (U-E . #.%\N)
		       (YU . #.%\b)
		       (EU . #.%\m)
		       (EU-I . #.%\M)
		       (I . #.%\l)
		       (O-I . #.%\L)
		       (U-I . #.%\B))
	      collect
		`(defconstant
		   ,(intern (format nil "HFEP-~a" symbol))
		   ,character))))

(define-keyboard-to-kor-mappings)
)








;;;; Special Character Definitions


;;; Here are some definitions for ASCII control characters.

(defconstant hfep-null #.%Null)		; a bit abstracted out of conservatism




(defconstant hfep-esc #.(code-wide-character 27))
(defconstant hfep-spc #.%space)
(defconstant hfep-eoln #.%newline)







;;;; State Table for Automata


;;; This is a 14x17 array called STATE.  We'll call it HFEP-STATE.


(defvar hfep-state
	(make-array
	  '(14 17)
	  :initial-contents
	  (optimize-constant
	    '((1  1  1  1  1  1  1  1  1  0  0  0  0  0  0  0  0)  
	      (1  1  1  1  1  1  1  1  1  2  3  4  5  6  7  8  0)  
	      (9 10 11 12 12 12 12 12 12  0  0  0  8  0  8  0  0) 
	      (9 10 11 12 12 12 12 12 12  0  0  0  0  8  8  0  0)
	      (9 10 11 12 12 12 12 12 12  0  0  0  0  0  8  0  0)
	      (9 10 11 12 12 12 12 12 12  8  0  0  0  0  0  0  0)
	      (9 10 11 12 12 12 12 12 12  0  8  0  0  0  0  0  0)
	      (9 10 11 12 12 12 12 12 12  8  8  8  0  0  0  0  0)
	      (9 10 11 12 12 12  1 12 12  0  0  0  0  0  0  0  0)
	      (1  1  1 13  1  1  1  1  1  2  3  4  5  6  7  8  0) 
	      (1  1  1  1 13 13  1  1  1  2  3  4  5  6  7  8  0) 
	      (13 1  1 13  1 13  1 13  1  2  3  4  5  6  7  8  0) 
	      (1  1  1  1  1  1  1  1  1  2  3  4  5  6  7  8  0)
	      (1  1  1  1  1  1  1  1  1  2  3  4  5  6  7  8  0)))))





;;;; Action Table for Automata


;;; Another 14x17 array.  We transform this the same way as we did above.

(defvar hfep-action
	(make-array
	  '(14 17)
	  :initial-contents
	  (optimize-constant
	    '((0  0  0  0  0  0  0  0  0  1  1  1  1  1  1  1 -2)
	      (12 12 12 12 12 12 12 12 12 2  2  2  2  2  2  2 -1)
	      (4  4  4  5  5  5  5  5  5 11 11 11  3 11  3 11 -1)
	      (4  4  4  5  5  5  5  5  5 11 11 11 11  3  3 11 -1)
	      (4  4  4  5  5  5  5  5  5 11 11 11 11 11  3 11 -1)
	      (4  4  4  5  5  5  5  5  5  3 11 11 11 11 11 11 -1)
	      (4  4  4  5  5  5  5  5  5 11  3 11 11 11 11 11 -1)
	      (4  4  4  5  5  5  5  5  5  3  3  3 11 11 11 11 -1)
	      (4  4  4  5  5  5 13  5  5 11 11 11 11 11 11 11 -1)
	      (7  7  7  6  7  7  7  7  7  9  9  9  9  9  9  9 -1) 
	      (7  7  7  7  6  6  7  7  7  9  9  9  9  9  9  9 -1) 
	      (6  7  7  6  7  6  7  6  7  9  9  9  9  9  9  9 -1) 
	      (7  7  7  7  7  7  7  7  7  9  9  9  9  9  9  9 -1) 
	      (8  8  8  8  8  8  8  8  8 10 10 10 10 10 10 10 -1)))))







;;;; Map for ENG-alphabet to KOR-alphabet


;;; Hfep-cho-ksc2c, hfep-jung-ksc2c, and hfep-jong-ksc2c ... are all simple arrays.

(defvar hfep-cho-ksc2c
  (optimize-constant
    #(#xa400 #xa400 #xa400 #xa400 #xb800  #xa400 #xa400 #xa400 #xa400 #xa400 
      #xa400 #xa400 #xa400 #xa400 #xa400  #xa400 #xc800 #xac00 #xa400 #xd000 
      #xa400 #xa400 #xdc00 #xa400 #xa400  #xa400 #xa400 #xa400 #xa400 #xa400 
      #xa400 #xa400 #xc000 #xa400 #xe000  #xd400 #xb400 #xbc00 #xf000 #xa400 
      #xa400 #xa400 #xa400 #xa400 #xa400  #xa400 #xa400 #xa400 #xc400 #xa800 
      #xb000 #xcc00 #xa400 #xec00 #xd800  #xe800 #xa400 #xe400)))


(defvar hfep-jung-ksc2c
  (optimize-constant
    #(#x0020 #x02e0 #x0020 #x0020 #x0020  #x0020 #x0020 #x01e0 #x0020 #x02a0 
      #x01c0 #x0220 #x0360 #x02c0 #x00c0  #x0160 #x0020 #x0020 #x0020 #x0020 
      #x0020 #x0020 #x0020 #x0020 #x0020  #x0020 #x0020 #x0020 #x0020 #x0020 
      #x0020 #x0020 #x0020 #x0320 #x0020  #x0020 #x0020 #x0020 #x0020 #x01a0 
      #x00a0 #x00e0 #x0040 #x03a0 #x0340  #x0260 #x0060 #x0120 #x0020 #x0020 
      #x0020 #x0020 #x0140 #x0020 #x0020  #x0020 #x0240 #x0020)))


(defvar hfep-jong-ksc2c
  (optimize-constant
    #(#x000c #x000e #x0013 #x0001 #x0001  #x0010 #x000a #x0007 #x0001 #x0006 
      #x0001 #x0001 #x000b #x000d #x0001  #x0001 #x0001 #x0003 #x0004 #x0015 
      #x0001 #x000f #x0001 #x0001 #x0001  #x0001 #x0001 #x0001 #x0001 #x0001 
      #x0001 #x0001 #x0011 #x0001 #x0018  #x0016 #x0008 #x0009 #x001c #x0001 
      #x0001 #x0001 #x0001 #x0001 #x0001  #x0001 #x0001 #x0001 #x0012 #x0002 
      #x0005 #x0014 #x0001 #x001b #x0017  #x001a #x0001 #x0019)))






;;;; Hangul Automata State Transformation 
; *
; *  Input:   [stat    Cchr    Nchr   char    \n]
; *  Output:  [stat    Cchr    Nchr   \n]
; *
; *  This automata gets an 4 byte input from emacs and
; *  returns 4 byte to emacs as a result.
; *
; *  stat -  current status of Hangul automata in this buffer.
; *  cchr -  9 byte
; *  nchr -  9 byte
; *  char -  current input char. 1 byte.
; *  \n   -  dummy newline.
; *
; *  A status of current automata is represented as an byte value.
; *
; *  MSB  7
; *       6
; *       5
; *       4
; *       3
; *       2
; *       1
; *  LSB  0
; *
; */

;#include <stdio.h>
;#include <ctype.h>
;#include "hctbl.h"		/*  All Tables used for  */


(def-structure hfep-hanc-type			; hanc-node
  hfep-flag
  
  hfep-cho
  hfep-jung
  hfep-jong1
  hfep-jong2

  hfep-ksc2c
  hfep-ksc2s)


;;; Make-hfep-hanc-type-function ... just calls make-hfep-hanc-type.  Used for
;;; forward referencing.

(defun make-hfep-hanc-type-function ()
  (make-hfep-hanc-type))

(defun reclaim-hfep-hanc-type-function (hfep-hanc-type)
  (reclaim-hfep-hanc-type hfep-hanc-type))

;; These need to be functions to be callable as the structure slot
;; initializer and reclaimer, respectively.  From module PARSE.


(defun reset-hfep-hanc-type-instance (hanc-type)
  (setf (hfep-flag hanc-type) hfep-none)	; integer
  
  (setf (hfep-cho hanc-type) hfep-null)		; characters
  (setf (hfep-jung hanc-type) hfep-null)
  (setf (hfep-jong1 hanc-type) hfep-null)
  (setf (hfep-jong2 hanc-type) hfep-null)

  (setf (hfep-ksc2c hanc-type) hfep-null-code)		; integers
  (setf (hfep-ksc2s hanc-type) hfep-null-code))



(defvar current-hfep-Cchar)			; instances of kfep-hanc-type
(defvar current-hfep-Nchar)			;   instantiated by the editor

(defvar current-hfep-c-state)			; bound (initially to 0) by the
(defvar current-hfep-c-act)			;   editor in an HFEP context.


;;; Shift-hfep-Cchar-to-Nchar-and-reset-Cchar shifts the contents of current-hfep-Cchar
;;; to current-hfep-Nchar.  Then it resets current-hfep-Cchar to the default value.

;;; When tranforming the original (C) shift function, we decided to make it use the
;;; global variables, as opposed to accepting them as arguments.  

(defun shift-hfep-Cchar-to-Nchar-and-reset-Cchar ()

  (setf (hfep-flag current-hfep-Cchar) (hfep-flag current-hfep-Nchar))

  (setf (hfep-cho current-hfep-Cchar) (hfep-cho current-hfep-Nchar))
  (setf (hfep-jung current-hfep-Cchar) (hfep-jung current-hfep-Nchar))
  (setf (hfep-jong1 current-hfep-Cchar) (hfep-jong1 current-hfep-Nchar))
  (setf (hfep-jong2 current-hfep-Cchar) (hfep-jong2 current-hfep-Nchar))

  (setf (hfep-ksc2c current-hfep-Cchar) (hfep-ksc2c current-hfep-Nchar))
  (setf (hfep-ksc2s current-hfep-Cchar) (hfep-ksc2s current-hfep-Nchar))

  (reset-hfep-hanc-type-instance current-hfep-Nchar))



;;; Initialize-hfep ...

(defun-for-macro initialize-hfep ()
  ;; Moved here from the top of main() in the c version.
  (reset-hfep-hanc-type-instance current-hfep-Cchar)
  (reset-hfep-hanc-type-instance current-hfep-Nchar))






;;; Run-hfep-automaton ...  to be run in an hfep context, in which the special
;;; variables current-hfep-Nchar, current-hfep-Cchar, current-hfep-c-act, and
;;; current-hfep-c-state are appropriately bound.

;;; This doesn't loop for ever as the C version did, but only runs once
;;; on the given string.

;;; The argument input-string is the only input, taking the place of both
;;; the impied input stream, stdin, and the buffer variable, "buf".

;;; This does not check for a null input string, as did the C version;
;;; input-string must not be null.

;;; In order to best simulate the outputting side effects of the original
;;; C version, this function wraps a twith-output-to-text-string around its
;;; body and outputs using tformat, etc.

;;; Note that the two calls 
;;; 
;;;    (reset-hfep-hanc-type-instance current-hfep-Cchar)
;;;    (reset-hfep-hanc-type-instance current-hfep-Nchar)
;;;
;;; were not moved here from main().  Instead they are in a new function,
;;; initialize-hfep   They must be called by whatever code binds special
;;; variables and initializes things -- currently, the development function
;;; reset-hfep-global-state.

(defun run-hfep-automaton (input-string)

  (twith-output-to-text-string
  
    (wide-character-case (charw input-string 0)
      (#.%\R					; /* reset */
       (setq current-hfep-c-state 0)
       (setq current-hfep-c-act 0)
       (reset-hfep-hanc-type-instance current-hfep-Cchar)
       (reset-hfep-hanc-type-instance current-hfep-Nchar))
      (#.%\F					; /* flush and reset */
       (tformat
	 "CF~c~c"				; CF -> current-hfep-Cchar/flush (ghw 10/15/92)
         ;; ghw 10/15/92
         ;; It's plausible that the first character returned -- either #.%\C or #.%\N, denotes
         ;; the structure, either current-hfep-Cchar or current-hfep-Nchar, from which the ~c~c
         ;; values are derived.  The second character returned -- either #.%\G, #.%\D, #.%\N, #.%\E or
	 ;; #.%\W -- probably denotes the flag slot of the structure, respectively hfep-go-on,
	 ;; hfep-done, hfep-none, hfep-error, or hfep-wrong; or when the first input-line char is
	 ;; #.%\F, the second output char will be #.%\F for flush.  In the case above, then, CF would
	 ;; denote current-hfep-Cchar/flush.
	 (code-wide-character
	   (ashf (hfep-ksc2s current-hfep-Cchar) -8))
	 ;; Note that the mask to select only the rightmost 8 bits was missing
	 ;; in the original C version, probably, we think, due to programmer error.
	 ;; (And note that the same comment applies to the uses of logandf below.)
	 (code-wide-character
	   (logandf #xff (hfep-ksc2s current-hfep-Cchar))))
       (tformat
	 "NF~c~c"				; NF -> current-hfep-Nchar/flush (ghw 10/15/92)
	 (code-wide-character (ashf (hfep-ksc2s current-hfep-Nchar) -8))
	 (code-wide-character (logandf #xff (hfep-ksc2s current-hfep-Nchar))))
						; added code-char to above line (ghw 10/15/92)
       (setq current-hfep-c-state 0)
       (setq current-hfep-c-act 0)
       
       (reset-hfep-hanc-type-instance current-hfep-Cchar)
       (reset-hfep-hanc-type-instance current-hfep-Nchar))
      (t
       (hfep-into-hanc (charw input-string 1))
       (case (hfep-flag current-hfep-Cchar)
	 ((#.hfep-none #.hfep-go-on)		; worry later about read-time issue!
						;   (may have to move constants to
						;   module loaded earlier)
	  (tformat
	    "CG~c~c"				; CG -> current-hfep-Cchar/hfep-go-on (ghw 10/15/92)
	    (code-wide-character (ashf (hfep-ksc2s current-hfep-Cchar) -8))
	    (code-wide-character (logandf #xff (hfep-ksc2s current-hfep-Cchar)))))
						; added code-char to above line (ghw 10/15/92)
	 (#.hfep-done				; same read-time issue as above
	  (tformat			; the only difference is the CD in this
	    "CD~c~c"				;   string vs. the CG in the above string!
						; CD -> current-hfep-Cchar/done (ghw 10/15/92)
	    (code-wide-character (ashf (hfep-ksc2s current-hfep-Cchar) -8))
	    (code-wide-character (logandf #xff (hfep-ksc2s current-hfep-Cchar))))
						; added code-char to above line (ghw 10/15/92)
	  (case (hfep-flag current-hfep-Nchar)
	    ((#.hfep-go-on #.hfep-wrong)
	     (tformat
	       "NW~c~c"				; NW -> current-hfep-Nchar/hfep-wrong (ghw 10/15/92)
	       (code-wide-character (ashf (hfep-ksc2s current-hfep-Nchar) -8))
	       (code-wide-character (logandf #xff (hfep-ksc2s current-hfep-Nchar))))
						; added code-char to above line (ghw 10/15/92)
	     (shift-hfep-Cchar-to-Nchar-and-reset-Cchar))
	    (#.hfep-none
	     (tformat
	       "NN~c~c"				; NN -> current-hfep-Nchar/hfep-none (ghw 10/15/92)
	       (code-wide-character (ashf (hfep-ksc2s current-hfep-Nchar) -8))
	       (code-wide-character (logandf #xff (hfep-ksc2s current-hfep-Nchar))))
						; added code-char to above line (ghw 10/15/92)
	     (shift-hfep-Cchar-to-Nchar-and-reset-Cchar))
	    (#.hfep-error
	     (tformat
	       "NE~c~c"				; NE -> current-hfep-Nchar/hfep-error (ghw 10/15/92)
	       (code-wide-character (ashf (hfep-ksc2s current-hfep-Nchar) -8))
	       (code-wide-character (logandf #xff (hfep-ksc2s current-hfep-Nchar))))
						; added code-char to above line (ghw 10/15/92)
	     (shift-hfep-Cchar-to-Nchar-and-reset-Cchar)
	     (setf (hfep-flag current-hfep-Cchar) hfep-done))))
	 (#.hfep-wrong
	  (tformat
	    "CW~c~c"				; CW -> current-hfep-Cchar/hfep-wrong (ghw 10/15/92)
	    (code-wide-character (ashf (hfep-ksc2s current-hfep-Cchar) -8))
	    (code-wide-character (logandf #xff (hfep-ksc2s current-hfep-Cchar))))
						; added code-char to above line (ghw 10/15/92)
	  (shift-hfep-Cchar-to-Nchar-and-reset-Cchar))
	 (#.hfep-error
	  (tformat
	    "CW~c~c"				; CW -- possible error!!!; does not follow the pattern;
						;   should be CE for current-hfep-Cchar/hfep-error?
						;   (ghw 10/15/92)
	    (code-wide-character (ashf (hfep-ksc2s current-hfep-Cchar) -8))
	    (code-wide-character (logandf #xff (hfep-ksc2s current-hfep-Cchar))))
						; added code-char to above line (ghw 10/15/92)
	  (when (eql (hfep-flag current-hfep-Nchar) hfep-go-on)
	    (tformat
	      "NG~c~c"				; NG -> current-hfep-Nchar/hfep-go-on (ghw 10/15/92)
	      (code-wide-character (ashf (hfep-ksc2s current-hfep-Nchar) -8))
	      (code-wide-character (logandf #xff (hfep-ksc2s current-hfep-Nchar))))
						; added code-char to above line (ghw 10/15/92)
	    (shift-hfep-Cchar-to-Nchar-and-reset-Cchar))))))))




;;; Hfep-into-hanc ... Here, C is a (Common Lisp) character.  This returns no
;;; useful value, but only does useful side effects.
;;;
;;; /****	Auotmata and Actions on each state, each type		*/

(defun hfep-into-hanc (c)
  (let (temp)
    (setq current-hfep-c-act
	  (aref hfep-action current-hfep-c-state (setq temp (hfep-CHgroup c))))
    (setq current-hfep-c-state
	  (aref hfep-state current-hfep-c-state temp)))
  (case current-hfep-c-act
    (-2						; /*NON-Hangul or seperator at State0*/
     (reset-hfep-hanc-type-instance current-hfep-Cchar)
     (setf (hfep-flag current-hfep-Cchar) hfep-wrong)
     (setf (hfep-cho current-hfep-Cchar) c)
     (reset-hfep-hanc-type-instance current-hfep-Nchar))
    (-1						; /*NOT-Hangul or seperator*/
     (setf (hfep-flag current-hfep-Cchar) hfep-done)
     (reset-hfep-hanc-type-instance current-hfep-Nchar)
     (setf (hfep-flag current-hfep-Nchar) hfep-wrong)
     (setf (hfep-cho current-hfep-Nchar) c))
    (0						; /*New Cho-sung*/
     (reset-hfep-hanc-type-instance current-hfep-Cchar)
     (reset-hfep-hanc-type-instance current-hfep-Nchar)
     (setf (hfep-flag current-hfep-Cchar) hfep-go-on)
     (setf (hfep-cho current-hfep-Cchar) c))
    (1						; /*New Jung-sung without Cho-sung*/
     (setf (hfep-flag current-hfep-Cchar) hfep-error)
     (setf (hfep-cho current-hfep-Cchar) hfep-null)
     (setf (hfep-jung current-hfep-Cchar) c))
    (2						; /*Cho-sung + New Jung-sung*/
     (setf (hfep-flag current-hfep-Cchar) hfep-go-on)
     (setf (hfep-jung current-hfep-Cchar) c))
    (3						; /*Cho-Jung-sung + Another Jung-sung*/
     (setf (hfep-flag current-hfep-Cchar) hfep-go-on)
     (setf (hfep-jung current-hfep-Cchar)
	   (hfep-mixVowel (hfep-jung current-hfep-Cchar) c)))
    (4						; /*Cho-Jung-sung + Jong-sung + (Optional)*/
     (setf (hfep-flag current-hfep-Cchar) hfep-go-on)
     (setf (hfep-jong1 current-hfep-Cchar) c))
    (5						; /*Cho-Jung-sung + Jong-sung*/
     (setf (hfep-flag current-hfep-Cchar) hfep-go-on)
     (setf (hfep-jong1 current-hfep-Cchar) c))
    (6						; /*Cho-Jung-Jong1-sung + Another Jong-sung*/
     (setf (hfep-flag current-hfep-Cchar) hfep-go-on)
     (setf (hfep-jong2 current-hfep-Cchar) c))
    (7						; /*Cho-Jung-Jong1-sung + Cho-sung*/
     (setf (hfep-flag current-hfep-Cchar) hfep-done)
     (setf (hfep-flag current-hfep-Nchar) hfep-go-on)
     (setf (hfep-cho current-hfep-Nchar) c))
    (8						; /*Cho-Jung-Jong1-Jong2-sung + Cho-sung*/
     ;; This (8) is the same case as 7 in the C version as well; worry
     ;; that this might have been a mistake in the original?  The comments are
     ;; quite different!
     (setf (hfep-flag current-hfep-Cchar) hfep-done)
     (setf (hfep-flag current-hfep-Nchar) hfep-go-on)
     (setf (hfep-cho current-hfep-Nchar) c))
    (9						; /*Cho-Jung-Jong1-sung + Jung-sung*/
     (setf (hfep-flag current-hfep-Cchar) hfep-done)
     (setf (hfep-flag current-hfep-Nchar) hfep-go-on)
     (setf (hfep-cho current-hfep-Nchar) (hfep-jong1 current-hfep-Cchar))
     (setf (hfep-jong1 current-hfep-Cchar) hfep-null)
     (setf (hfep-jung current-hfep-Nchar) c))
    (10						; /*Cho-Jung-Jong1-Jong2-sung + Jung-sung*/
     (setf (hfep-flag current-hfep-Cchar) hfep-done)
     (setf (hfep-flag current-hfep-Nchar) hfep-go-on)
     (setf (hfep-cho current-hfep-Nchar) (hfep-jong2 current-hfep-Cchar))
     (setf (hfep-jong2 current-hfep-Cchar) hfep-null)
     (setf (hfep-jung current-hfep-Nchar) c))
    (11						; /*Cho-Jung-sung + Errored Jung-sung*/
     (setf (hfep-flag current-hfep-Cchar) hfep-done)
     (setf (hfep-flag current-hfep-Nchar) hfep-error)
     (setf (hfep-jung current-hfep-Nchar) c))
    (12						; /*Cho-sung + Errored Cho-sung*/
     (setf (hfep-flag current-hfep-Cchar) hfep-error)
     (setf (hfep-flag current-hfep-Nchar) hfep-go-on)
     (setf (hfep-cho current-hfep-Nchar) c))
    (13						; /*Cho-Jung-sung + Cho-sung-Only*/
     (setf (hfep-flag current-hfep-Cchar) hfep-done)
     (setf (hfep-flag current-hfep-Nchar) hfep-go-on)
     (setf (hfep-cho current-hfep-Nchar) c)))	; added previously omitted line (ghw 10/15/92)
  (setf (hfep-ksc2c current-hfep-Cchar)
	(hfep-intoKsc2c
	  (hfep-cho current-hfep-Cchar) (hfep-jung current-hfep-Cchar)
	  (hfep-jong1 current-hfep-Cchar) (hfep-jong2 current-hfep-Cchar)))
  (setf (hfep-ksc2s current-hfep-Cchar)
	(hfep-intoKsc2s (hfep-ksc2c current-hfep-Cchar)))
  (cond
    ((not (eql (hfep-flag current-hfep-Nchar) hfep-none))
     (setf (hfep-ksc2c current-hfep-Nchar)
	   (hfep-intoKsc2c
	     (hfep-cho current-hfep-Nchar) (hfep-jung current-hfep-Nchar)
	     (hfep-jong1 current-hfep-Nchar) (hfep-jong2 current-hfep-Nchar)))
     (setf (hfep-ksc2s current-hfep-Nchar)
	   (hfep-intoKsc2s (hfep-ksc2c current-hfep-Nchar))))
    (t
     (setf (hfep-ksc2c current-hfep-Nchar) hfep-null-code)
     (setf (hfep-ksc2s current-hfep-Nchar) hfep-null-code))))




;;; HFEP-intoKsc2c ... C1, c2, c3, and c4 are all characters.  This returns
;;; a character code, a 16-bit integer.
;;;
;;; /****	Function which make KSC2C code from Hangule-Character	*/

(defun hfep-intoKsc2c (c1 c2 c3 c4)
  (let ((i1 #xa400) (i2 #x0200) (i3 #x0001)
	i4)
    
    (when (and (char>=w c1 #.%\A) (char<=w c1 #.%\z))	; i.e., alphabetic -- use alpha-char-p?
      (setq i1 (svref hfep-cho-ksc2c (-f (wide-character-code c1) #.(wide-character-code #.%\A)))))
    
    (cond
      ((and (char/=w c1 hfep-null) (=f i1 #xa400))	; i.e., alphabetic -- use alpha-char-p?
       (wide-character-code c1))
      (t
       (cond
	 ((char/=w c2 hfep-null)
	  (setq i2 (svref hfep-jung-ksc2c (-f (wide-character-code c2) #.(wide-character-code #.%\A)))))
	 (t
	  (setq i2 #x0200)))
       (cond
	 ((char/=w c3 hfep-null)
	  (setq i3
		(svref hfep-jong-ksc2c
		       (-f (wide-character-code (hfep-mixConso c3 c4))
			   #.(wide-character-code #.%\A)))))
	 (t
	  (setq i3 #x0001)))
       (setq i4 (logxor i1 i2 i3))
       i4))))


;; These two accessor macros are needed because the hfep-ksc2cs original
;; C-language two-dimensional array has been flattened to a simple vector.
;; See HFEP1.

(def-substitution-macro ksc2c-code-index-in-simple-vector 
			(index-if-two-dimensional-array)
  (*f index-if-two-dimensional-array 2))


(def-substitution-macro ksc2s-code-index-in-simple-vector 
			(index-if-two-dimensional-array)
  (1+f (*f index-if-two-dimensional-array 2)))


;;; HFEP-intoKsc2s ... Key is a character code, i.e., a 16-bit integer.
;;; This returns a character code.
;;;
;;; /****	Function which make KSC2S code from Hangule-Character	*/
;;; /*	Binary Search algorithm used (Assume ksc2c-ksc2s sorted)*/

(defun hfep-intoKsc2s (key)
  (let ((l 0) (u (-f hfep-ks-size 1))
	m tmp)
    (loop while (<=f l u)
	  do (setq m (halff (+f l u)))
;	     (setq tmp (aref hfep-ksc2cs m 0))
	     (setq tmp (aref hfep-ksc2cs 
			     (ksc2c-code-index-in-simple-vector m)))
	     (cond
	       ((>f key tmp)
		(setq l (+f m 1)))
	       ((=f key tmp)
;		(return (aref hfep-ksc2cs m 1)))
		(return (aref hfep-ksc2cs 
			      (ksc2s-code-index-in-simple-vector m))))
	       ((<f key tmp)
		(setq u (-f m 1))))
	  finally
	    (return key))))


;;; HFEP-CHgroup takes a character, c, and returns a character code.
;;; 
;;; /****	Hangule Alphabet Grouping for Automata doing well.	*/

(defun hfep-CHgroup (c)
  (wide-character-case c
    ((#.hfep-g #.hfep-b) 0)
    (#.hfep-n 1)
    (#.hfep-r 2)
    (#.hfep-s 3)
    (#.hfep-j 4)
    (#.hfep-h 5)
    ((#.hfep-dd #.hfep-bb #.hfep-jj) 6)
    ((#.hfep-m #.hfep-t #.hfep-p) 7)
    ((#.hfep-gg #.hfep-d #.hfep-ss #.hfep-oo #.hfep-c #.hfep-k) 8)
    (#.hfep-o 9)
    (#.hfep-u 10)
    (#.hfep-eu 11)
    ((#.hfep-a #.hfep-ai) 12)
    ((#.hfep-eo #.hfep-e) 13)
    (#.hfep-i 14)
    ((#.hfep-ya #.hfep-yeo #.hfep-yu #.hfep-yai #.hfep-ye #.hfep-yo) 15)
    ((#.hfep-o-a #.hfep-u-eo #.hfep-o-ai #.hfep-u-e #.hfep-eu-i #.hfep-o-i #.hfep-u-i)
     ;; This returns the same value, 15, as the one above, instead of 16, as would
     ;; be expected judging by the pattern.  Is this a mistake in the original?!
     ;; At least a 16 can be returned by the T clause at the end, so maybe this
     ;; is correct.  Perhaps this was broken into 2 cases to shorten the line?
     15)
    (t 16)))



;;; HFEP-mixVowel takes two characters, c1 and c2, and returns a character.
;;; 
;;; /****	Mixed Vowel combine routine				*/

(defun hfep-mixVowel (c1 c2)
  (let ((c c1))
    (when (and (char/=w c1 hfep-o)
	       (char/=w c1 hfep-u)
	       (char/=w c1 hfep-eu))
      (setq c c1)				; redundant - in the original - shrug
      (setq c1 c2)
      (setq c2 c))
    
    (wide-character-case c1
      (#.hfep-o
       (when (char=w c2 hfep-a) (setq c hfep-o-a))
       (when (char=w c2 hfep-ai) (setq c hfep-o-ai))
       (when (char=w c2 hfep-i) (setq c hfep-o-i)))
      (#.hfep-u
       (when (char=w c2 hfep-eo) (setq c hfep-u-eo))
       (when (char=w c2 hfep-e) (setq c hfep-u-e))
       (when (char=w c2 hfep-i) (setq c hfep-u-i)))
      (#.hfep-eu
       (when (char=w c2 hfep-i) (setq c hfep-eu-i))))
    c))


;;; HFEP-mixConso takes two characters, and returns a character code.
;;;
;;; /****	Mixed Consonant combine routine				*/

(defun hfep-mixconso (c1 c2)
  (let ((c c1))
    (wide-character-case c1
      (#.hfep-g
       (when (char=w c2 hfep-s) (setq c hfep-g-s)))
      (#.hfep-n
       (when (char=w c2 hfep-j) (setq c hfep-n-j))
       (when (char=w c2 hfep-h) (setq c hfep-n-h)))
      (#.hfep-r
       (when (char=w c2 hfep-g) (setq c hfep-r-g))
       (when (char=w c2 hfep-m) (setq c hfep-r-m))
       (when (char=w c2 hfep-b) (setq c hfep-r-b))
       (when (char=w c2 hfep-s) (setq c hfep-r-s))
       (when (char=w c2 hfep-t) (setq c hfep-r-t))
       (when (char=w c2 hfep-p) (setq c hfep-r-p))
       (when (char=w c2 hfep-h) (setq c hfep-r-h)))
      (#.hfep-b
       (when (char=w c2 hfep-s) (setq c hfep-b-s))))
    c))




;;;; HFEP Testing Facilities


#+development
(progn
  
  
(defvar hfep-test-state? nil)
	

(defun set-up-hfep-test ()
  (setq hfep-test-state?
	(list (make-hfep-hanc-type)
	      (make-hfep-hanc-type)
	      0
	      0)))




;;; Reset-hfep-global-state ...

(defun-for-macro reset-hfep-global-state ()
  (setq current-hfep-Cchar (first hfep-test-state?))
  (setq current-hfep-Nchar (second hfep-test-state?))
  (setq current-hfep-c-state (third hfep-test-state?))
  (setq current-hfep-c-act (fourth hfep-test-state?))

  (initialize-hfep))


(defmacro with-test-hfep-context (&body body)
  `(progn
     (if (null hfep-test-state?)
	 (set-up-hfep-test))
     (let (current-hfep-Cchar
	   current-hfep-Nchar
	   current-hfep-c-state
	   current-hfep-c-act)
       (reset-hfep-global-state)
       (prog1
	 (progn . ,body)
	 (setf (third hfep-test-state?) current-hfep-c-state)
	 (setf (fourth hfep-test-state?) current-hfep-c-act)))))


(defun test-hfep-reset ()
  (with-test-hfep-context
    (run-hfep-automaton "R")))

(defun test-hfep-flush ()
  (with-test-hfep-context
    (run-hfep-automaton "F")))


(defun test-hfep-rkrk ()
  (with-test-hfep-context
    (run-hfep-automaton "R")
    (run-hfep-automaton "Ir")
    (run-hfep-automaton "Ik")
    (run-hfep-automaton "Ir")
    (run-hfep-automaton "Ik")))

(defun test-hfep-rkrr ()
  (with-test-hfep-context
    (run-hfep-automaton "R")
    (run-hfep-automaton "Ir")
    (run-hfep-automaton "Ik")
    (run-hfep-automaton "Ir")
    (run-hfep-automaton "Ir")))


;;; The following five tests were added by ghw on 10/16/92.  See ghw's notes for the Hangul fonts
;;;   expected in the editor from these keystrokes.


;;; Test 1: enter "Hangul"

(defun test-hfep-gms-rmf ()
  (with-test-hfep-context
    (run-hfep-automaton "R")			; reset

    (run-hfep-automaton "Ig")			; enter g m s for "han" (consonant-vowel-consonant)
    (run-hfep-automaton "Im")
    (run-hfep-automaton "Is")

    (run-hfep-automaton "Ir")			; enter r m f for "gul" (consonant-vowel-consonant)
    (run-hfep-automaton "Im")
    (run-hfep-automaton "If")))


;;; Test 2: enter "Seoul"

(defun test-hfep-tj-dmf ()
  (with-test-hfep-context
    (run-hfep-automaton "R")			; reset

    (run-hfep-automaton "It")			; enter t j for "seo" (consonant-vowel)
    (run-hfep-automaton "Ij")

    (run-hfep-automaton "Id")			; enter d m f for "ul" (zero-consonant-vowel-consonant)
    (run-hfep-automaton "Im")
    (run-hfep-automaton "If")))


;;; Test 3: enter "kap" (it means "price")

(defun test-hfep-rkq ()
  (with-test-hfep-context
    (run-hfep-automaton "R")			; reset

    (run-hfep-automaton "Ir")			; enter r k q for "kap" (consonant-vowel-consonant)
    (run-hfep-automaton "Ik")
    (run-hfep-automaton "Iq")))


;;; Test 4: enter "am" (it means "the")

(defun test-hfep-dka ()
  (with-test-hfep-context
    (run-hfep-automaton "R")			; reset

    (run-hfep-automaton "Id")			; enter d k a for "am" (zero-consonant-vowel-consonant)
    (run-hfep-automaton "Ik")
    (run-hfep-automaton "Ia")))


;;; Test 5: enter "am" omitting the zero-consonant (this should be an error)

(defun test-hfep-ka ()
  (with-test-hfep-context
    (run-hfep-automaton "R")			; reset

    (run-hfep-automaton "Ik")			; enter k a for "am" erroneously omitting the zero consonant
    (run-hfep-automaton "Ia")))


) ; end #+development (progn ...)











;;;; Issues for Korean Productization


;;; This is a list of various odds and ends of issues having to do with
;;; getting the Korean product ready, or improved.
;;; 
;;; (1) Sometimes the automaton does not seem to work.  E.g. the sequence
;;; kakkak seems to produce the wrong thing.
;;; --UPDATE: this is actually not true -- this works "perfect", per
;;; Hee-Won Seo.
;;;
;;; (2) Get rid of JIS Font's Chinese characters -- replace with KS Font's!
;;; (e.g., KB in Load KB translation)
;;; --UPDATE: done in the version in progress (MHD 7/21/93)
;;;
;;; (3) Get Documentation to work on Korean Language Facilities (KLF) document.
;;; 	- Telewindows compatibility issues
;;; 	- input examples
;;; 	- Font samples
;;; 	- Language Translation
;;; --UPDATE: lots of work is now in progress by Kanti (MHD 7/21/93)
;;;
;;; (4) Get Marketing to work in Korean Language collateral -- supply them
;;; with KLF document.
;;;
;;; (5) Add korean.kl to the set of standard KBs.  See Jim/Ben/Mark about how
;;; to do this.
;;;
;;; (6) Eventually, remove the parenthesized (English) menu choices from the
;;; language translations.  Continue them for the time being -- they seem nice.
;;;
;;; (7) Support some way to have English (and maybe other languages) in addition
;;; to the translation in some automatic way, esp. to make up for the above item
;;; (6).  (in editor, in menu translations, and, eventually, in other places
;;; that get translated.
;;;
;;; (8) Support row/column input -- maybe with menus automatically generated?
;;; scrollable?
;;;
;;; (9) Support row/column (kuten) OR hex-code input for Chinese characters?
;;;
;;; (10) Load just Hangul characters and Chinese characters only on Demand?
;;; (inlude English characters with Korean?  Maybe just load first half of
;;; font that includes Hangul, and the second half (with Chinese characters)
;;; only later?



;;;; Language Parameters/Internationalization Facilities


;;; (1) Support some way to have English (and maybe other languages) in addition
;;; to the translation in some automatic way, esp. to make up for the above item
;;; (6).  (in editor, in menu translations, and, eventually, in other places
;;; that get translated.
;;; 
;;; (a) Add a slot to language-parameters
;;;
;;; 		show-parenthesized-english-along-with-translations? (yes/no)
;;;
;;; (b) Add a slot to language-parameters
;;;
;;; 		language-groupings-for-translation
;;;
;;; with grammar allowing things like
;;;
;;; 		English, Korean
;;;
;;; 		French, German, Italian
;;;
;;; 		when country = Switzerland, group French, German, and Italian
;;;
;;; [... needs work]
;;;
;;; (2) Consider converting language translations to tabular-function-like tables.
;;;
;;; (3) Need way to localize names, classes, attribute tables, ....
;;; 


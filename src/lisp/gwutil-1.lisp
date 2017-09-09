;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GWUTIL-1

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Ben Hyde


;;;; Introduction

;;; This module contains a huge misc. of stuff.


;;;; Misc C functions we import.


(defmacro def-gsiannex-c-function (function-name
				    (foreign-function-type foreign-function-name)
				    parameters
				    &body body)
  (let ((args (loop for spec in parameters collect (cadr spec))))
    `(progn
       (declare-gsi-api-symbol ,function-name)
       (if-chestnut-gsi
	 (def-gensym-c-function ,function-name
	     (,foreign-function-type ,foreign-function-name)
	   ,parameters)
	 (if-chestnut
	   ,(flet ((convert-type (type)
		     (case type
		       (:fixnum-int :fixnum-long)
		       (t type))))
	      (with-package-specific-symbols (tx |::| def-foreign-callable)
		`(def-foreign-callable (,function-name (:name ,foreign-function-name)
						       (:return-type ,(convert-type foreign-function-type)))
		     ,(loop for (type arg) in parameters collect `(,arg ,(convert-type type)))
		   ,@body)))
	   (defun ,function-name ,args
	     ,@body))))))

(def-gsiannex-c-function gsi-watch-fd (:void "gsi_watch_fd")
    ((:fixnum-int file-descriptor))
  (declare (type fixnum file-descriptor))
  file-descriptor) ;;what to put as body?

(def-gsiannex-c-function gsi-unwatch-fd (:void "gsi_unwatch_fd")
    ((:fixnum-int file-descriptor))
  (declare (type fixnum file-descriptor))
  file-descriptor)

(def-gsiannex-c-function gsi-watch-fd-for-writing (:void "gsi_watch_fd_for_writing")
    ((:fixnum-int file-descriptor))
  (declare (type fixnum file-descriptor))
  file-descriptor)

(def-gsiannex-c-function gsi-unwatch-fd-for-writing (:void "gsi_unwatch_fd_for_writing")
    ((:fixnum-int file-descriptor))
  (declare (type fixnum file-descriptor))
  file-descriptor)


;;; `def-direct-c-function' - GSI, under the guise of def-gensym-c-function,
;;; takes great pains in passing strings between C and Lisp.  A "Gensym C
;;; function" gets a wrapper placed around it which does stuff to the string.
;;; WebLink is not so cautious.  It just wants to pass the string directly.
;;; In the past, it just used lcl:def-foreign-function directly. I'm adding
;;; this macro to make the functions which don't use wrappers look more like
;;; the ones that do.  (Too much alike?  Is it confusing?  I hope not.)
;;; In so doing, I have made the C name a required parameter, and added it for
;;; all of the functions.  In the past, we relied on Lucid's default name
;;; translation (just substituting underscore for hyphen).  -jv, 10/7/03

;; Ben's undated comment regarding :string foreign functions: "Note you must
;; take great care to avoid passing this a fill-pointer string."

(defmacro def-direct-c-function (function-name
				  (foreign-function-type foreign-function-name)
				  parameters)
  `(progn
     (if-chestnut
       ,(flet ((convert-type (type)
                 (case type
                   (:fixnum32 :signed-32bit)
                   (t type))))
          (with-package-specific-symbols (tx |::| def-foreign-function)
            `(def-foreign-function (,function-name
                                    (:name ,foreign-function-name)
                                    (:return-type ,(convert-type foreign-function-type)))
               ,@(loop for (type arg) in parameters
                       collect `(,arg ,(convert-type type))))))         
       (def-gensym-c-function ,function-name
           (,foreign-function-type ,foreign-function-name)
         ,parameters))))

(def-gensym-c-function gw-fetch-errno
    (:fixnum32 "gw_fetch_errno")
  ())

(def-gensym-c-function gw-flush-console-streams
    (:fixnum32 "gw_flush_console_streams")
  ())

(def-gensym-c-function gw-tcpip-connection-check
    (:fixnum32 "gw_tcpip_connection_check")
  ((:fixnum32 socket)))

(def-gensym-c-function gw-socket-data-available-p
    (:fixnum32 "gw_socket_data_available_p")
  ((:fixnum32 socket)))

(def-direct-c-function gw-socket-write
    (:fixnum32 "gw_socket_write")
  ((:fixnum32 socket-number)
   (:string buffer)
   (:fixnum32 start)
   (:fixnum32 end)))

(def-gensym-c-function gw-socket-poll-status
    (:fixnum32 "gw_socket_poll_status")
  ((:fixnum32 socket-number)))

(def-direct-c-function gw-socket-read
    (:fixnum32 "gw_socket_read")
  ((:fixnum32 socket-number)
   (:string buffer)
   (:fixnum32 max)))

;;; `Tcp-accept' interfaces to the C foreign function accept.

;;;Note that we should not be using the tcpip direct interfaces, but rather
;;;should be using functions from networks.c (g2ext_network_*).  Unfortunately,
;;;at present the generic network interfaces do not supply the things that
;;;weblink needs (in particular the way it handles accept), and so more work
;;;needs to be done in order to do this right.  --yduJ, 3/23/05

(def-gensym-c-function g2ext-tcpip-accept-internals
    (:fixnum32 "g2ext_tcpip_accept_internals")
  ((:fixnum32 listener-socket)))

(def-gensym-c-function g2ext-tcpip-listen
    (:fixnum32 "g2pvt_tcpip_listen")
  ((:fixnum32 port)))

(def-gensym-c-function g2ext-tcpip-set-nodelay
    (:fixnum32 "g2pvt_tcpip_set_nodelay")
  ((:fixnum32 listener-socket)))

(def-direct-c-function g2ext-tcpip-connect
    (:fixnum32 "g2pvt_tcpip_connect")
  ((:string host)
   (:fixnum32 port)))

(def-gensym-c-function g2ext-tcpip-close
    (:fixnum32 "g2pvt_tcpip_close")
  ((:fixnum32 socket)))

#-development
(def-direct-c-function lgsi-rpc-declare-remote-1
    (:void "lgsi_rpc_declare_remote_1")
  ((:string function-name)
   (:fixnum32 number_of_args)
   (:fixnum32 number_of_return_values)))

(def-gensym-c-function g2ext-print-network-connections
    (:void "g2ext_print_network_connections")
  ())


;;;; A Pad for Foreign Bytes


(defparameter max-of-foreign-string-pad 10000)

;;; `Current-foreign-string-pad' is temporary storage used
;;; to move strings to and from Lisp and C.

(defparameter current-foreign-string-pad
  (make-string max-of-foreign-string-pad))

(defun coerce-into-foreign-string-pad (string)
;  #+development
;  (format t "~A" string)
  (let ((pad current-foreign-string-pad))
    (loop with length = (length string)
	  finally (setf (char pad length) null-character-for-c-strings)
	  for i from 0 below length
	  do (setf (char pad i) (char string i)))
    pad))

(defun coerce-into-foreign-string-pad-with-crlf (string)
;  #+development
;  (format t "~A~%" string)
  (let ((pad current-foreign-string-pad))
    (loop with length = (length string)
	  finally
	    (setf (char pad length) #\return)
	    (setf (char pad (+ 1 length)) #\linefeed)
	    (setf (char pad (+ 2 length)) null-character-for-c-strings)
	  for i from 0 below length
	  do (setf (char pad i) (char string i)))
    pad))

(defun make-text-string-from-foreign-string-pad (length)
  (let* ((pad current-foreign-string-pad)
	 (text-string (obtain-simple-gensym-string length)))
    (loop for i from 0 below length
	  doing (setf (char text-string i) (char pad i)))
    text-string))

(defun make-text-string-from-c-string-in-foreign-string-pad ()
  (loop
    with null-char = (code-char 0)
    with pad = current-foreign-string-pad
    for i from 0 below (length pad)
    when (eq null-char (char pad i))
      do
	(let ((result (obtain-simple-gensym-string i)))
	  (loop for j from 0 below i
		do (setf (char result j) (char pad j)))
	  (return result))))

(defun make-text-safe-for-c (string)
  (if (simple-string-p string)
      string
      (coerce-into-foreign-string-pad string)))




;;;; Gensym Strings to Internet Strings

;;; This section is a first stab at providing abstractions
;;; for moving between the text representations that occur
;;; inside and outside of the bridge and G2.  We enumerate
;;; a set of text representations and then define some
;;; routines that can coerce betwen them.

;; This should all work on and around buffers, not via the
;; twrite protcol.


;;; `Mnemonics-for-kinds-of-text-encoding' enumerates the set of all known text
;;; encodings, and the mnemonic used in routine names for each of them in the
;;; form of a plist.  The mnemonics are only used in macro generated names.

;;; `Internet-ascii' is the format common to internet mail and netnews.  Lines
;;; are terminated with CRLF.  Most importantly it is the format used to
;;; represent HTML.  When converting from it we are quite forgiving about line
;;; terminators.  The characters tend to be limited to the safe portions of
;;; ascii.

;;; `Gensym-procedure-text' are the byte streams stored in procedure locals of
;;; type `text'.  This is easily confused with the lists used in the editor and
;;; slots like text-box-translation-and-text.

(defparameter-for-macro mnemonics-for-kinds-of-text-encoding
  '(internet-ascii  i-ascii
    gensym-procedure-text gensym-pt))


;;; `Def-twrite-text-coercion' is used to define the coercion from
;;; a string of type A to a string of type B.  These routines should
;;; stream their result to the twrite stream.

(defmacro def-twrite-text-coercion ((format-of-input-string format-of-output-string)
				    (text-variable)
				    &body body)
  (let ((input-encoding-mnemonic
	  (getf mnemonics-for-kinds-of-text-encoding format-of-input-string))
	(output-encoding-mnemonic
	  (getf mnemonics-for-kinds-of-text-encoding format-of-output-string)))
    (unless input-encoding-mnemonic
      (warn "Unknown text encoding ~S" format-of-input-string))
    (unless output-encoding-mnemonic
      (warn "Unknown text encoding ~S" format-of-output-string))
    `(defun ,(build-ab-symbol "TWRITE-TEXT"
			     input-encoding-mnemonic
			     "TO"
			     output-encoding-mnemonic)
	 (,text-variable)
       ,@body)))


;;; `TWrite-coerced-string' takes a lisp string and writes its contents into
;;; the current twrite stream.  Converting its contents from the text encoding
;;; given, into the text encoding desired.  This routine is a macro, the
;;; to and from encoding are not quoted.

(defmacro twrite-coerced-string (input-string
				  format-of-input-string
				  format-of-output-string)
  (let ((input-encoding-mnemonic
	  (getf mnemonics-for-kinds-of-text-encoding format-of-input-string))
	(output-encoding-mnemonic
	  (getf mnemonics-for-kinds-of-text-encoding format-of-output-string)))
    (unless input-encoding-mnemonic
      (warn "Unknown text encoding ~S" format-of-input-string))
    (unless output-encoding-mnemonic
      (warn "Unknown text encoding ~S" format-of-output-string))
    `(,(build-ab-symbol "TWRITE-TEXT"
			input-encoding-mnemonic
			"TO"
			output-encoding-mnemonic)
       ,input-string)))


;;; `Tilde-escape-to-iso-latin-1-map' is a lisp string initialied by the macro
;;; `fillout-tilde-escape-to-iso-latin-1-map'.  It is used to map from the ~
;;; escaped characters into iso latin 1.  Note not all tilde escape characters
;;; have an iso laten representations, trademark for example.  Such characters
;;; map to space.  This is build using the info in special-character-alist and
;;; postscript-character-encodings.

#+development
(defun fillout-tilde-escape-to-iso-latin-1-map ()
  (let ((result (make-string 256)))
    (loop for i from 0 below 256 doing (setf (schar result i) #\space))
    (loop
      for (character-following-\~-in-gensym-character
	    roman-font-special-character-code
	    character-following-\~-in-lower-case-equivalent?
	    equivalent-unaccented-character?
	    character-or-characters-following-\~-for-input
	    adobe-name
	    bcis-character-code?
	    ISO-Latin1-name-if-different?) in special-character-alist
      as (adobe-text? adobe-encoding? iso-latin-1?)
	 = (find adobe-name postscript-character-encodings
		 :test #'string= :key #'first)
      do
      (setf
	(schar result (char-code character-following-\~-in-gensym-character))
	(if iso-latin-1?
	    (code-char iso-latin-1?)
	    #\space)))
    result))

(defparameter tilde-escape-to-iso-latin-1-map
  (coerce
   (list
    #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space
    #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space
    #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space
    #\Space #\Space #\Space #\Space #\Space #\Space #.(code-char #xA1) #\Space
    #.(code-char #xA3) #.(code-char #xA5)
    #.(code-char #xA2) #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space
    #\Space #\Space #.(code-char #xEB) #.(code-char #xCB) #.(code-char #xEF)
    #.(code-char #xCF) #.(code-char #xE3) #.(code-char #xC3) #.(code-char #xF5)
    #.(code-char #xD5) #.(code-char #xFB) #.(code-char #xDB) #\Space
    #.(code-char #xAE) #.(code-char #xAB) #\Space #.(code-char #xBB)
    #.(code-char #xBF) #\@ #.(code-char #xC4) #.(code-char #xC1) #.(code-char #xC7)
    #.(code-char #xC2) #.(code-char #xC9) #.(code-char #xCA) #.(code-char #xC8)
    #.(code-char #xCC) #.(code-char #xCD) #.(code-char #xCE) #\Space #\Space
    #.(code-char #xC0) #.(code-char #xD1) #.(code-char #xD6) #.(code-char #xD3)
    #.(code-char #xD4) #.(code-char #xC5) #\Space #.(code-char #xD8)
    #.(code-char #xDC) #.(code-char #xDA) #\Space #.(code-char #xC6)
    #.(code-char #xD2) #.(code-char #xD9) #\Space
    #\\ #\Space #\Space #\Space #\Space #.(code-char #xE4) #.(code-char #xE1)
    #.(code-char #xE7) #.(code-char #xE2) #.(code-char #xE9) #.(code-char #xEA)
    #.(code-char #xE8) #.(code-char #xEC) #.(code-char #xED) #.(code-char #xEE)
    #\Space #\Space #.(code-char #xE0) #.(code-char #xF1) #.(code-char #xF6)
    #.(code-char #xF3) #.(code-char #xF4) #.(code-char #xE5) #.(code-char #xDF)
    #.(code-char #xF8) #.(code-char #xFC) #.(code-char #xFA) #\Space
    #.(code-char #xE6) #.(code-char #xF2) #.(code-char #xF9) #\Space
    #.(code-char #xA9) #\Space #\~ #\Space #\Space #\Space #\Space #\Space #\Space #\Space
    #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space 
    #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space 
    #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space 
    #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space 
    #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space 
    #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space 
    #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space
    #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space
    #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space
    #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space
    #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space
    #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space
    #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space #\Space
    #\Space #\Space #\Space #\Space #\Space)
   'string))

;; That string is computed by the development only funtion above.  It would
;; need to be recomputed if we ever change the tilde escapes, that seems
;; unlikely.

	 


;;; Coerce Gensym procedure text into internet 8bit ascii (aka ISO Latin 1)
;;; with line breaks implemented using CRLF.

(def-twrite-text-coercion (gensym-procedure-text internet-ascii) (text-string)
  (macrolet ((emit-char-in-error () `(twrite-char #\space)))
    (loop with escape-character?
	  with string-is-simple? = (simple-gensym-string-p text-string)
	  with length-of-string fixnum = (glength text-string string-is-simple?)
	  with i fixnum = 0
	  while (<f i length-of-string)
	  as character-or-character-code
	     = (read-gensym-character-from-gensym-string
		 text-string i string-is-simple? escape-character?)
	  do (cond

	       ;; A small subset of ISO Latin 1 passes thru with no bother.
	       ((null escape-character?)
		(twrite-char character-or-character-code))

	       ;; The ISO Latin 1 characters.
	       ((char= escape-character? #\~)
		(twrite-char
		  (schar tilde-escape-to-iso-latin-1-map
			 (char-code character-or-character-code))))

	       ;; The formating codes.
	       ((char= escape-character? #\@)
		(character-case character-or-character-code
		  (#\L
		     (twrite-char #\Return)
		     (twrite-char #\Linefeed))
		  (#\P ;; Note A
		     )
		  (t (emit-char-in-error))))

	       ;; The Asian characters.
	       ((char= escape-character? #\\)
		;; This character cannot be translated into ascii -- for now,
		;; Ignore the kanji character
		;; Note B.
		(emit-char-in-error))))))

;; Note A: @P "might" be used to prefix a run of spaces that the formating
;; shouldn't eliminate if it is line wrapping.

;; Note B: Some ISO Latin 1 characters are encoded in the kanji space.



;;; `Handling-of-iso-latin-1-character' is an array of fixnum
;;; - 0, 1, 2, 3 - ranging over the encoding value used in ISO Latin 1
;;; 0. indicates a character that we encode without an escape.
;;; 1. denotes characters with a tilde escape prefix
;;; 2. indicates a linefeed
;;; 3. indicates a return
;;; 2 and 3 are input to the mechinism that generates @L.

;;; Meanwhile `gensym-character-of-iso-latin-1-character'
;;; is the character that should appear in the gensym in the
;;; gensym string, possibly with a prefix escape character.

(def-concept handling-of-iso-latin-1-character )
(def-concept gensym-character-of-iso-latin-1-character (make-string 256))

;;; `fill-out-handling-of-iso-latin-1-encoding' is a macro used
;;; to fill out those two vectors.

#+development
(defun fill-out-handling-of-iso-latin-1-encoding ()
  (let ((handling (make-array 256))
	(characters (make-string 256)))
    (macrolet ((f (x1 x2)
		 `(progn
		    ;; (format t "~%~3D ~2D ~S" i ,x1 ,x2)
		    (setf (svref handling i) ,x1)
		    (setf (schar characters i) ,x2))))
      (loop for i from 0 below 256
	    as c = (code-char i)
	    as (adobe-name-as-string?)
	       = (find i postscript-character-encodings :key #'third)
	    as (tilde-escaped-character?)
	       = (find adobe-name-as-string? special-character-alist
		       :key #'sixth :test #'string=)
	    doing

	(cond
	  ((eq c #\linefeed)
	   (f 2 #\space))
	  ((eq c #\return)
	   (f 3 #\space))
	  (tilde-escaped-character?
	   ;; Except characters in the tilde escape set
	   (f 1 tilde-escaped-character?))
	  ((or (<=f i 31)   ;; control chars
	       (<=f 127 i)) ;; Eight bit chars.
	   (f 0 #\space))
	  (t ;; Default
	   (f 0 c)))))
    (format t "~&(defvar handling-of-iso-latin-1-character")
    (format t "~&  '#(")
    (loop for i from 0 by 8 below (length handling) doing
      (format t "~&     ~D ~D ~D ~D  ~D ~D ~D ~D"
	      (svref handling i)
	      (svref handling (+ i 1))
	      (svref handling (+ i 2))
	      (svref handling (+ i 3))
	      (svref handling (+ i 4))
	      (svref handling (+ i 5))
	      (svref handling (+ i 6))
	      (svref handling (+ i 7))))
    (format t "))")
        (format t "~&(defvar gensym-character-of-iso-latin-1-character")
    (format t "~&  #.(coerce")
    (format t "~&    '(")
    (loop for i from 0 by 4 below (length characters) doing
      (format t "~&      #\\~:C #\\~:C #\\~:C #\\~:C"
	      (svref characters i)
	      (svref characters (+ i 1))
	      (svref characters (+ i 2))
	      (svref characters (+ i 3))))
    (format t ") 'string))")))


;; These following two forms are printed out by the funtion above.

(defvar handling-of-iso-latin-1-character
  '#(
     0 0 0 0  0 0 0 0
      0 0 2 0  0 3 0 0
      0 0 0 0  0 0 0 0
      0 0 0 0  0 0 0 0
      0 0 0 0  0 0 0 0
      0 0 0 0  0 0 0 0
      0 0 0 0  0 0 0 0
      0 0 0 0  0 0 0 0
      1 0 0 0  0 0 0 0
      0 0 0 0  0 0 0 0
      0 0 0 0  0 0 0 0
      0 0 0 0  1 0 0 0
      0 0 0 0  0 0 0 0
      0 0 0 0  0 0 0 0
      0 0 0 0  0 0 0 0
      0 0 0 0  0 0 1 0
      0 0 0 0  0 0 0 0
      0 0 0 0  0 0 0 0
      0 0 0 0  0 0 0 0
      0 0 0 0  0 0 0 0
      0 1 1 1  0 1 0 0
      0 1 0 1  0 0 1 0
      0 0 0 0  0 0 0 0
      0 0 0 1  0 0 0 1
      1 1 1 1  1 1 1 1
      1 1 1 1  1 1 1 1
      0 1 1 1  1 1 1 0
      1 1 1 1  1 0 0 1
      1 1 1 1  1 1 1 1
      1 1 1 1  1 1 1 1
      0 1 1 1  1 1 1 0
      1 1 1 1  1 0 0 0))

(defvar gensym-character-of-iso-latin-1-character
  #.(coerce
    '(
      #\Space #\Space #\Space #\Space
      #\Space #\Space #\Space #\Space
      #\Space #\Space #\Space #\Space
      #\Space #\Space #\Space #\Space
      #\Space #\Space #\Space #\Space
      #\Space #\Space #\Space #\Space
      #\Space #\Space #\Space #\Space
      #\Space #\Space #\Space #\Space
      #\Space #\! #\" #\#
      #\$ #\% #\& #\'
      #\( #\) #\* #\+
      #\, #\- #\. #\/
      #\0 #\1 #\2 #\3
      #\4 #\5 #\6 #\7
      #\8 #\9 #\: #\;
      #\< #\= #\> #\?
      #\@ #\A #\B #\C
      #\D #\E #\F #\G
      #\H #\I #\J #\K
      #\L #\M #\N #\O
      #\P #\Q #\R #\S
      #\T #\U #\V #\W
      #\X #\Y #\Z #\[
      #\\ #\] #\^ #\_
      #\` #\a #\b #\c
      #\d #\e #\f #\g
      #\h #\i #\j #\k
      #\l #\m #\n #\o
      #\p #\q #\r #\s
      #\t #\u #\v #\w
      #\x #\y #\z #\{
      #\| #\} #\~ #\Space
      #\Space #\Space #\Space #\Space
      #\Space #\Space #\Space #\Space
      #\Space #\Space #\Space #\Space
      #\Space #\Space #\Space #\Space
      #\Space #\Space #\Space #\Space
      #\Space #\Space #\Space #\Space
      #\Space #\Space #\Space #\Space
      #\Space #\Space #\Space #\Space
      #\Space #\! #\% #\#
      #\Space #\$ #\Space #\Space
      #\Space #\| #\Space #\<
      #\Space #\Space #\; #\Space
      #\Space #\Space #\Space #\Space
      #\Space #\Space #\Space #\Space
      #\Space #\Space #\Space #\>
      #\Space #\Space #\Space #\?
      #\M #\B #\D #\5
      #\A #\R #\X #\C
      #\G #\E #\F #\1
      #\H #\I #\J #\3
      #\Space #\N #\Y #\P
      #\Q #\7 #\O #\Space
      #\T #\Z #\V #\9
      #\U #\Space #\Space #\s
      #\m #\b #\d #\4
      #\a #\r #\x #\c
      #\g #\e #\f #\0
      #\h #\i #\j #\2
      #\Space #\n #\y #\p
      #\q #\6 #\o #\Space
      #\t #\z #\v #\8
      #\u #\Space #\Space #\Space) 'string))

;;; Convert internet 8bit or 7bit character streams into
;;; gensym procedure text.  This has a little AI in it to
;;; try to get LF, CRLF, and CR, to all map into @L.  This
;;; does not ever generate the evil @P.

(def-twrite-text-coercion (internet-ascii gensym-procedure-text) (ascii-string)
  (loop with string-is-simple? = (simple-gensym-string-p ascii-string)
	with length-of-string fixnum = (glength ascii-string string-is-simple?)
	with i fixnum = 0
	with char
	with char-code
	with just-saw-return? = nil ;; Note B.
	until (=f i length-of-string)
	do
    (setf char (read-simple-character-from-gensym-string
		 ascii-string i string-is-simple?))
    (setf char-code (char-code char))
    (fixnum-case (svref handling-of-iso-latin-1-character char-code)
      (0
	(twrite-char
	  (schar gensym-character-of-iso-latin-1-character char-code)))
      (1
	(twrite-char #\~)
	(twrite-char
	  (schar gensym-character-of-iso-latin-1-character char-code)))
      (2 ;; Note A
	(unless just-saw-return?
	  (twrite-char #\@)
	  (twrite-char #\L)))
      (3
	(twrite-char #\@)
	(twrite-char #\L))
      (4 ;; Encode as kanji code....  Not used yet.
	;; Should be used for the ISO latin holes
	))
    (setf just-saw-return? (eq #\return char))))

;; Note A: We attempt to handle the three line terminator styles
;; in one mechinism here, Mac like CR, Unix like LF, and Internet
;; standard style CRLF.






  


;;;; Time Utilities


(defun alarm-p (alarm-time-mf)
  (prog1
      (<f (managed-float-value alarm-time-mf)
	  (gensym-get-unix-time))))







;;;; Memory monitoring

;;; This section implements a scheme to check for memory leaks.
;;; It keeps a history of the total pool memory that is currently
;;; out.  Three operations are provided on the history:
;;;   - clear it.
;;;   - add to it.
;;;   - report its slope, and standard deviation.
;;; Generally you use this in four steps.
;;;   1. Clear the history.
;;;   2. Add to it at a point in the program were
;;;      you believe memory usage is quiet.
;;;   3. Do an operation N times.
;;;   4. Get a Report

;;; The report will show you the least squares first
;;; order function that fits the memory trend.  You
;;; want its slope to be zero.  If not then the
;;; slope should tell you how much memory per operation
;;; you are using up.


#+development
(defparameter maximum-total-pool-outstanding-object-count-history-count
  1000)

#+development
(defparameter total-pool-outstanding-object-count-history
  (make-array maximum-total-pool-outstanding-object-count-history-count))

#+development
(defvar total-pool-outstanding-object-count-history-next-sample
  0)

#+development
(defvar total-pool-outstanding-object-count-history-last-sample 0)

#+development
(defun-void clear-total-pool-outstanding-object-count-history ()
  (setf total-pool-outstanding-object-count-history-next-sample 0))

#+development
(defun add-sample-to-total-pool-outstanding-object-count-history ()
  (when (=f (+f 1 total-pool-outstanding-object-count-history-next-sample)
	    maximum-total-pool-outstanding-object-count-history-count)
    (loop for i
	  from 0 below (-f maximum-total-pool-outstanding-object-count-history-count
			   1) do
      (setf (svref total-pool-outstanding-object-count-history i)
	    (svref total-pool-outstanding-object-count-history
		   (+f i 1))))
    (decff total-pool-outstanding-object-count-history-next-sample))
  (setf (svref
	  total-pool-outstanding-object-count-history
	  total-pool-outstanding-object-count-history-next-sample)
	(total-pool-outstanding-object-count))
  (incff total-pool-outstanding-object-count-history-next-sample))

#+development
(defun report-total-pool-outstanding-object-count-history (count-of-operations)
  (declare (ignore count-of-operations))
  ;; This doesn't fit a first order line to the data (my primary desire).
  (when (<f total-pool-outstanding-object-count-history-last-sample 0)
    (format t "~&No samples in history")
    (return-from report-total-pool-outstanding-object-count-history nil))
  (macrolet
      ((adv (p)
	 `(progn
	    (incff ,p)
	    (when
		(=f ,p
		    maximum-total-pool-outstanding-object-count-history-count)
	      (setf ,p 0))
	    ,p)))
    (loop
      with first-sample
	= (svref total-pool-outstanding-object-count-history 0)
      with sum fixnum = 0
      with sum-of-squares fixnum  = 0
      with min fixnum = first-sample
      with max fixnum = first-sample
      for count-of-samples from 0
			   below total-pool-outstanding-object-count-history-next-sample
      as sample = (svref total-pool-outstanding-object-count-history
			 count-of-samples)
      do
      (incf sum sample)
      (incf sum-of-squares (*f sample sample))
      (setf min (minf min sample))
      (setf max (maxf min sample))
      finally
	(format t "~%Recent history of total pool objects in use, see total-pool-outstanding-object.")
;	(format t "~&N:~D S:~D S2:~D" count-of-samples sum sum-of-squares)
	(format t "~&~D samples ranging from ~D to ~D average ~D, std dev ~D"
		count-of-samples min max
		(roundf sum count-of-samples)
		(round
		  (let* ((float-number-of-values
			   (coerce-to-gensym-float count-of-samples))
			 (average
			   (/e (coerce-to-gensym-float sum)
			       float-number-of-values)))
		    (sqrte
			(abse
			  (-e (/e (coerce-to-gensym-float 
				    sum-of-squares)
				  float-number-of-values)
			      (*e average average))))))))))






;;;; Console Logging

;;; This section provides standard interface for generating log
;;; messages on the bridges background stream.  These are of the form.
;;;   <timestamp> <context> <kind>: <message>
;;; so other tools can run with them.  For example:
;;;   951114131936 0 Log: Configure-bridge
;;; That time stamp was generated at 1:19:36pm Nov. 14, 1995, note that
;;; it is set up to assure that time stamps sort nicely, while also being
;;; slightly readable.

;;; The principle use of <kind> is to make it trivial to grep out error
;;; messages.

(defmacro bridge-log (&rest args)
  `(notify-user-at-console ,@args))

(defmacro bridge-error (&rest args)
  `(notify-user-at-console ,@args))


;;;; Ignored Variables

;;; Due to the way certain macros expand in GSI5, it is inconvenient to attempt
;;; to use (declare (ignore ...)).  However, we don't want to get warnings about
;;; variables bound but not reference, either.  A simple solution is simply to
;;; "reference" the variable by including it in the code.  Instead of:
;;;    (defun sqrt-first (a b)
;;;       (declare (ignore b))
;;;       (sqrt a))
;;; we can say:
;;;    (defun sqrt-first (a b)
;;;       b
;;;       (sqrt a))
;;; Am I supposed to care that the second form evaluates b?  I don't see why I
;;; should.  A smart compiler should optimize out the reference to b in any
;;; case, and from testing, it appears that Lucid/Chestnut do just fine.
;;; But there are two problems with the above: one is that it is not a standard
;;; idiom and therefore somewhat opaque.  What's that b doing there?  The second
;;; problem is that I don't want to lose track of the changes I'm making,
;;; especially since these changes indicate a problem where other macros are
;;; expanding differently than we expect.  So, introduce this no-op macro,
;;; `fake-declare-ignore', to do nothing but "reference" its argument.  We can
;;; easily go back and find all the fake-declare-ignore's later if we want to.

(defmacro fake-declare-ignore (reference-me)
  reference-me)

;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module POSTSCRIPT

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author(s): Ben Hyde






;;;; Introduction To The Module POSTSCRIPT



;;; This module implements the postscript translator.  The translator enables postscript
;;; to be written using a lisp like notation.

;;; The postscript forms defined using this module appear in the next module, ps-header.
;;; They are accumulated into a single group, in the order defined to create the header
;;; used when printing to a postscript printer.

;;; Understanding the translator requires understanding two encodings.  The sources for
;;; the header are S Expressions, these are converted to postscript's postfix form via the
;;; simplest transformation I could live with.  The second encoding takes the resulting
;;; strings and compresses them.  When the postscript is emitted into the printing
;;; stream this second encoding is reversed.

;;; Converting S Expressions to postscript tokens is called translation, the symbols with
;;; `translate' in thier name implement this translation.

;;; The compiler is available only in development and macro images.  The distribution
;;; image contains only the array of encoded strings, the emit-postscript-prolog routine,
;;; and the string decoding mechinism.








;;;; Intermodule references.



;;; This module exports five macros used to define the
;;; postscript header.  These are: start-postscript-header,
;;; end-postscript-header,  defun-for-postscript,
;;; defvar-for-postscript, and top-level-progn-for-postscript.

;;; The module exports one routine, emit-postscript-prolog,
;;; that inserts the defined postscript header into the
;;; printing stream.  The printing stream is defined in the
;;; module PRINTING, and we have forward references to various
;;; aspects of the printing stream (i.e. the tools that manage
;;; line length).



(declare-forward-reference printing-stream variable)

(declare-forward-reference emit-postscript-reserve-space function)

(declare-forward-reference emit-postscript-line-length variable)

(declare-forward-reference emit-printing-color-map function)      ;; PRINTING

(declare-forward-reference pformat function)		    ; PRINTING

;;; Otherwise this module depends only on the usual stuff in the
;;; Gensym substrate: gensym-streams, defun-for-macro, etc.



;;; The defparameter `postscript-transparent-color-value' is the value we emit
;;; to represent transperency in the postscript file.  It turns out that the G2
;;; value is too large for postscript to make reliable EQ comparisons against it.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter postscript-transparent-color-value -1))

  

;;; General postscript knowledge.
;;; known-built-in-postscript-operators is used by postscript-compute-operator-compression-table
;;; to avoid compressing built-in operators.

(defparameter-for-macro known-built-in-postscript-operators
  '(abs
     add
     aload
     arc
     arcn
     array
     atan
     begin
     clip
     closepath
     copy
     currentmatrix
     currentpoint ;;  () (x y)
     cvs ;; (any string) (substring)
     cvlit ;; (any) (any)
     cvx
     def
     definefont
;     deflocal					; This isn't builtin.
     dict
     div
     end
     eq
     exch
     exec
     exit
     fill
     findfont
     flush
     get
     getinterval
     grestore
     grestoreall ;; () ()
     gsave
     ge
     gt
     initgraphics ;; () ()
     image
     imagemask
     initmatrix
     known ;; (dict key) (bool)
     length
     lineto
     load
     le
     lt
     matrix
     maxlength
     moveto
     mul
     ne ;; (any1 any2) (bool)
     neg
     newpath
     not ;; (or ((bool) (bool)) ((int) (int)))
     or ;; (or ((bool bool) (bool)) ((int int) (int)))
     pop
     print
     put
     putinterval
     rcheck  ;; (any) (bool)
     repeat  ;; (int proc) ()
     rmoveto ;; (dx dy) () 
     rlineto
     rotate
     scale
     scalefont
     setcachedevice
     setdash
     setlinecap
     setlinejoin
     setfont
     setgray
     setlinewidth
     setmatrix
     setrgbcolor
     show
     showpage
     sqrt
     store ;; (key value) () 
     string ;; (int) (string)
     stroke
     sub
     transform
     translate
     type ;; (any) (type-name)
     vmstatus ;; () (int-level int-used int-maximum)
     xcheck ;; (any) (bool)
     widthshow ;; (int int char text) ()
     ))

(defun-for-macro postscript-builtin-operator-p (name)
  (loop for op in known-built-in-postscript-operators
	when (string-equal (string op) (string name))
	 do (return name)))




;;;; Storing And Decoding Postscript Text




;;; `Postscript-header-array' is an array of constant encoded strings which
;;; make up the postscript header.  The first NIL entry in the array
;;; marks the end of the header.  The size of this array is hand tuned.

(defparameter postscript-header-array (make-array 100))




;;; Start of changes by fmw.

;;; Postscript operators which are compressed in both the header and the body
;;; of the file.  These operators may ONLY be ones which we define ourself
;;; in the header.  Builtin postscript operators which we merely call will
;;; NOT work.  Also, be careful to not include operators which are printed
;;; literally in printing.lisp, that is, operators which are part of the
;;; format string in a call to pformat.

;;; The compressed operators are strings like, "$a" ... "$z", "$aa" ... "$zz".

(defparameter-for-macro postscript-tokens-to-compress
    '(.notdef					; Legal CL symbol name?
      _atan-2-x1
      _atan-2-x2
      _atan-2-y1
      _atan-2-y2
      _bottom
      _clockwise-rotation
      _last-pt?
      _left
      _right
      _workspace-bottom
      _workspace-left
      _workspace-right
      _workspace-top
      _x-center
      _x-scale
      _y-center
      _y-scale
      add-downward-sloping-line-to-current-window
      add-from-graph-rendering-to-current-window
      add-from-icon-rendering-to-current-window
      add-from-line-of-text-to-current-window
      add-solid-rectangle-to-current-window
      add-upward-sloping-line-to-current-window
      add-wide-polyline-to-current-window
      add-polygon-to-current-window
      add-ellipse-to-current-window
      atan-2
      baseline-in-window
      begin-making-graph-rendering
      begin-making-icon-rendering
      begin-window-update
      clipped-bottom-edge
      clipped-left-edge
      clipped-right-edge
      clipped-top-edge
      color-difference
      color-map
      color-value
      color-values-for-rasters?
      corresponding-icp-object-index
      ctm-backup
      ctm-original
      define-blob-font
      define-helvetica-font
      define-paper
      define-unknown-font
      deflocal
      fetch-from-color-list
      fine-stroke
      font-map
      g2-print-job-title-page
      global-bottom-margin
      global-layout
      global-left-margin
      global-paper-orientation
      global-paper-size
      global-right-margin
      global-top-margin
      graph-rendering
      grid-background-color-value
      height-of-rendered-icon
      height-of-rendering-structure
      icon-rendering
      image-height
      image-width
      initialize-scratchpad-raster
      kanji-add-from-line-of-text-to-current-window
      kanji-paint-from-line-of-text-to-current-scratchpad-raster
      left-edge-in-graph-rendering
      left-edge-in-icon-rendering
      left-edge-of-line-of-text-in-window
      left-end-x
      left-end-y
      line-width
      list-of-color-differences
      message-group-id
      number-of-rendering-structure-elements
      nword-spacing
      paint-arc-or-circle-in-current-scratchpad-raster
      paint-filled-triangle-in-current-scratchpad-raster
      paint-from-line-of-text-to-current-scratchpad-raster
      orient-and-paint-line-of-text-to-current-scratchpad-raster
      paint-image-in-current-scratchpad-raster
      paint-last-point?
      paint-line-in-current-scratch-pad-raster
      paint-line-in-current-scratchpad-raster
      paint-point-in-current-scratchpad-raster
      paint-solid-rectangle-in-current-scratchpad-raster
      paint-solid-rectangle-in-current-window
      paint-wide-line-in-current-scratchpad-raster
      paper-bottom-margin
      paper-height
      paper-left-margin
      paper-right-margin
      paper-top-margin
      paper-width
      prepare-for-painting-graph
      real-bottom-margin
      real-left-margin
      real-right-margin
      real-top-margin
      reflection-and-rotation-of-rendering
      region-extrema-for-stored-raster
      right-end-x
      right-end-y
;;      scalefont
      set-appropriate-color
      set-icon-scale-and-rotation
      set-up-ctm
      set-up-palette
      stroke-ctm-backup
      subtract-instead?
      text-line
      top-edge-in-graph-rendering
      top-edge-in-icon-rendering
;;      translate
      update-graph-data-extrema
      update-graph-dateline
      update-ring-raster-for-graph-given-color-values
      width-of-rendered-icon
      width-of-rendering-structure
      word-spacing
      x-scale
      x-scale-of-rendering
      y-scale
      y-scale-of-rendering
      ))


;;; postscript-compute-operator-compression-table returns
;;; an alist of (operator-symbol . compressed-name)
;;; The compressed names chosen from the strings $a, ..., $z, $aa, ..., $zz.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro postscript-compute-operator-compression-table ()
  `',(loop with letters = "abcdefghijklmnopqrstuvwxyz"
	   for symbol in postscript-tokens-to-compress
	   for i from 0
	   for abbr = (cond ((<= 0 i 25)
			     (format nil "~($~a~)" (aref letters i)))
			    (t
			     (format nil "~($~a~a~)"
				     (aref letters (truncate i 26))
				     (aref letters (mod i 26)))))
	   do (when (postscript-builtin-operator-p symbol)
		(warn "~a is a builtin postscript operator, you can't compress its name."
		      symbol))
	   collect (cons symbol abbr)))
)

;; I prefixed the compressed names with "$" to avoid conflicts
;; with the postscript operators EQ, LT, GE, etc.


(defparameter-for-macro postscript-operator-compression-table (postscript-compute-operator-compression-table))


;;; Return the encoding PS operator name as a string like $a ... $aa ...
;;; If none, return NIL.

(defun-for-macro postscript-compress-operator-name (symbol)
  (cdr (assq symbol postscript-operator-compression-table)))


#+development
(defun postscript-decompress-operator-name (abbr)
  (loop for (name . ab) in postscript-operator-compression-table
	when (string= ab abbr)
	 do (return name)))



;;; Common tokens that appear in the header are encoded as single upper
;;; case characters.  When emitting the header the full token plus
;;; delimiters is emitted when ever an upper case character is
;;; encountered.  `Postscript-token-encodings' is a simple vector of
;;; strings which defines this encoding.  This vector is available at
;;; compile time to enable the encoding to be done, and at run time
;;; to enable the decoding.

;;; Any PS token is allowed here, including builtin operators.

(defparameter-for-macro postscript-tokens-to-compress-in-header
              '(                                ; instances size
		deflocal			;  216 2160 A
		def				;   58  290 B
		set-appropriate-color		;   10  220 C
		color-value			;   14  182 D
		_y-center			;   14  154 E
		_x-center			;   14  154 F
		clipped-left-edge		;    8  152 G
		clipped-top-edge		;    8  144 H
		lineto				;   17  136 I
		clipped-bottom-edge		;    6  126 J
		clipped-right-edge		;    6  120 K
		mul				;   23  115 L
		left-edge-of-line-of-text-in-window	;    3  111 M
		graph-rendering			;    6  102 N
		_bottom				;   11   99 O
		_left				;   14   98 P
		moveto				;   12   96 Q
		subtract-instead?		;    5   95 R
		translate			;    8   88 S
		_right				;   11   88 T
		add-from-graph-rendering-to-current-window	;    2   88 U
		scalefont			;    8   88 V
;		_top				;   14   84 W
;		_y1				;   16   80 X
		_x1				;   16   80 Y
;; Some entries have been changed to reduce the length of the longest strings in
;; the ps-header file, so they can make it past some bogus C compiler.
                .notdef                       ; -- hand selected to reduce maximum sized proc
		paint-line-in-current-scratchpad-raster
		))


;;; Create the array which will maps the first-stage compressed tokens ($a, etc)
;;; into single capital letters.  This array must be available at compile-time to
;;; compress the header and at run-time to decompress it.

(defmacro postscript-compute-header-token-encodings ()
  (let ((names postscript-tokens-to-compress-in-header))
    (when (> (length names) 26)
      (error "There are too many elements in POSTSCRIPT-TOKENS-TO-COMPRESS-IN-HEADER."))
    (let ((array (make-array (length names))))
      (loop for name in names
	    for i from 0
	    for compressed = (postscript-compress-operator-name name)
	    ;; For some reason, a call to (format nil "~(~a~)" name) bombs in sparc/Chestnut.
	    ;; It seems the ~( format directive was not available at run-time.
	    ;; string-downcase is better anyways. -fmw  9Jun93.
	    do (setf (aref array i) (or compressed (string-downcase (string name)))))
      `',array)))


;;; The array of upper-case-letter-number --> postscript token.
;;; Used at run-time to quickly lookup letters in the compressed postscript header.

(defparameter postscript-header-token-encodings (postscript-compute-header-token-encodings))

(defun postscript-decompress-header-token (letter)
  (svref postscript-header-token-encodings
	 (- (char-code letter) #.(char-code #\A))))


;;; Used only at compile-time. Namely, while compiling ps-header.lisp.

(defun-for-macro postscript-compress-header-token (text)
  (loop for i from 0 below (length postscript-header-token-encodings)
	when (string= text (svref postscript-header-token-encodings i))
	do (return (string (code-char (+ (char-code #\A) i))))))



;;; `Postscript-decode-text-into-gensym-stream' implements the actual decoding, it takes
;;; a gensym stream and a single constant encoded text string.  It emits the decoded text
;;; to that stream using the routines exported from the module PRINTING.

;;; A second routine nearly identical routine `Postscript-decode-text-into-real-stream'
;;; will emit to a Lisp stream rather than a gensym-stream.  It is available only in
;;; development.

;;; A macro `postscript-decode-text-into-stream-1' implements both these routines.

(defmacro postscript-decode-text-into-stream-1 
	  (encoded-text stream my-write-char my-write-string my-reserve-space my-consume-space)
  `(progn
     (loop with delimeter-must-follow = nil
	   with emitting-vanilla-token = nil
	   for i from 0 below (length ,encoded-text)
	   as c = (char ,encoded-text i)
	   do
       (cond
	 ((upper-case-p c)
	  (let ((decoded-text (postscript-decompress-header-token c)))
	    (when (and delimeter-must-follow
		       (not (,my-reserve-space 
			     (+f 1 (length decoded-text))
			     ,stream)))
	      (,my-consume-space 1 ,stream)
	      (,my-write-char #\space ,stream))
	    (,my-consume-space (length decoded-text) ,stream)
	    (,my-write-string decoded-text ,stream)
	    (setf emitting-vanilla-token nil)
	    (setf delimeter-must-follow t)))
	 ((eql c #\/)
	  (,my-reserve-space 12 ,stream)
	  (,my-consume-space 1 ,stream)
	  (,my-write-char c ,stream)
	  (setf emitting-vanilla-token t)
	  (setf delimeter-must-follow nil))
	 ((memq c '(#\{ #\} #\/))
	  (,my-reserve-space 1 ,stream)
	  (,my-consume-space 1 ,stream)
	  (,my-write-char c ,stream)
	  (setf emitting-vanilla-token nil)
	  (setf delimeter-must-follow nil))
	 ((eql c #\newline) ;; suppress the newlines they appear only for the C compiler.
	  (,my-consume-space 1 ,stream)
	  (,my-write-char #\space ,stream))
	 ((memq c '(#\space #\tab))
	  (unless (,my-reserve-space 1 ,stream)
	    (,my-consume-space 1 ,stream)
	    (,my-write-char c ,stream))
	  (setf emitting-vanilla-token nil)
	  (setf delimeter-must-follow nil))
	 (t
	  (when (eql #\@ c)
	    (incf i)
	    (setq c (char ,encoded-text i)))
	  (when (and (not emitting-vanilla-token)
		     delimeter-must-follow
		     (not (,my-reserve-space 1 ,stream)))
	    (,my-consume-space 1 ,stream)
	    (,my-write-char #\space ,stream))
	  (,my-consume-space 1 ,stream)
	  (,my-write-char c ,stream)
	  (setf emitting-vanilla-token t)
	  (setf delimeter-must-follow t))))))



(defun postscript-decode-text-into-gensym-stream (text gensym-stream)
  (macrolet ((emit-postscript-consume-space (length stream)
	       (declare (ignore stream))
	       `(incf emit-postscript-line-length ,length)))
    (postscript-decode-text-into-stream-1
      text gensym-stream
      g2-stream-write-char g2-stream-write-string emit-postscript-reserve-space emit-postscript-consume-space)))


#+development
(defun postscript-decode-text-into-real-stream (text real-lisp-stream)
  (declare (special postscript-translate-line-length)) ; defined a few forms down from here.
  (macrolet ((translate-consume-space (length space) `(incf postscript-translate-line-length ,length)))
    (postscript-decode-text-into-stream-1 
      text real-lisp-stream
      write-char write-string postscript-translate-reserve-space translate-consume-space)))



;;; `Emit-postscript-prolog' inserts the prolog into the printing stream.

(defun emit-postscript-prolog (paper-size eps?)
  (macrolet ((ps-newline ()
	       '(g2-stream-terpri printing-stream))
	     (ps-print-line (text)			    ; Text is ASCII here.
	       `(progn
		  (ps-newline)
		  (g2-stream-write-string ,text printing-stream))))
    (loop initially 
	    (ps-print-line "%%BeginProlog")
	    (ps-print-line "%%BeginResource: procset ab-header-3-0")
	    (ps-print-line "/ab-dict 495 dict def ab-dict begin")
	    (setf emit-postscript-line-length 0)
	  finally
	    (emit-printing-color-map)
	    (ps-print-line "end")
	    (ps-print-line "%%EndResource: procset ab-header-3-0")
	    (ps-print-line "%%EndProlog")
	    (unless eps?		; This belongs in the setup section, but it works here.
	      (emit-paper-tray paper-size))
	    (ps-newline)
	  
	  for i from 0 below (length postscript-header-array)
	  as encoded-text = (aref postscript-header-array i)
	  until (not encoded-text) 
	  do
      (postscript-decode-text-into-gensym-stream encoded-text printing-stream))

    (pformat "~%%%BeginSetup")
    (pformat "~%%%IncludeResource: font Helvetica")
    (pformat "~%ab-dict begin~%")
    (pformat "~%setup-blob-font~%")))



;;; The function `emit-paper-tray' emits postscript to select the
;;; paper tray.  This is what really tells the printer what size
;;; paper it is printing upon.  Since the functions `a4tray' and `a4',
;;; eg, are not always available, we wrap their invocations in the
;;; `stopped' operator.

(defun emit-paper-tray (paper-size)
  (pformat "~%~%statusdict begin~%")
  (pformat "~({~atray} stopped {{~a} stopped pop} if~)~%"
	   paper-size paper-size)
  (pformat "end~%"))



;;;; Encoding Postscript Text



;;; We we translate postscript S Expressions into our encoded strings we 
;;; maintain some dynamic state to guide the process.  These are:

;;;   - postscript-translate-stream, a real lisp stream.
;;;   - postscript-translate-line-length, to avoid long lines.
;;;   - postscript-translate-previous-token, so quoting works.
;;;   - postscript-translate-previous-token-was-self-delimiting, to avoid
;;;       excess whitespace.

;;; They are all unbound at toplevel.  They are all "for macro."
;;; They are used both by the encoding and by the debugging decoder.
;;; They work on real lisp streams, not gensym streams.

(defvar-for-macro postscript-translate-stream)
(defvar-for-macro postscript-translate-line-length)
(defvar-for-macro postscript-translate-previous-token-was-self-delimiting)
(defvar-for-macro postscript-translate-previous-token)




;;; `Postscript-translate-reserve-space' will insert a new line into the
;;; output stream if the line length would exceed 60.  If it inserts a
;;; new line it returns a non NIL value, otherwise it returns NIL.

(defun-for-macro postscript-translate-reserve-space (length stream)
  (when (and (< 60 (+ postscript-translate-line-length
		      length))
	     (not (eq '/ postscript-translate-previous-token)))
    (setf postscript-translate-line-length 0)
    (terpri stream)
    (setf postscript-translate-previous-token-was-self-delimiting t)
    t))


;;; `Postscript-encode-to-quote-uppercase' returns a string
;;; where all uppercase characters are prefixed with an #\@ character.

(defun-for-macro postscript-encode-to-quote-uppercase (text)
  (concatenate 
    'string
    (loop for i from 0 below (length text)
	  as c = (char text i)
	  nconc
	    (if (upper-case-p c)
		(list #\@ c)
		(list c)))))



;;; `postscript-translate-encode-token' takes token along with a flag
;;; indicating if this token is self delimiting in postscript.
;;; It returns two values.  The first is the conversion of that
;;; token into text to be inserted into the encoded text stream.
;;; the second value is the self delimiting flag.  That flag
;;; is changed if the token is encoded since encoded tokens are
;;; all self delimiting.

;;; Compression happens in two stages: first, convert the token
;;; to a two-letter abbreviation, if any.  Then convert that to
;;; the single-letter, self-delimiting encoding.

(defun-for-macro postscript-translate-encode-token (token self-delimiting-p)
;; Note A
;;  (when (symbolp token)
;;    (incf (getf postscript-token-counts token 0)))
  (let* ((text (or (postscript-compress-operator-name token)
		   (if (symbolp token)
		       (format nil "~(~A~)" token)
		       (format nil "~A" token))))
	 (letter (postscript-compress-header-token text)))
;    (when letter
;      (format t "~s ~s ~s~%" token text letter))
    (cond (letter
	   (values letter t))
	  (t
	   (values 
	    (postscript-encode-to-quote-uppercase text)
	    self-delimiting-p)))))


;; Note A: The commented out code that follows allows you to analyze the
;; the list accumulated in postscript-token-counts if you comment out
;; the two lines in postscript-translate-encode-token.  That enables you
;; to select a good set of tokens to encode.

;(defvar postscript-token-counts '())
;(defun sort-postscript-token-counts ()
;  (loop with n = 0
;	with a = (char-code #\a)
;	with c2 = (char-code #\w)
;	with c1 = (1- (char-code #\a))
;	with z = (char-code #\z)
;	for (token . count) in
;	    (sort
;	      (loop for (token count) 
;			on postscript-token-counts by #'cddr
;			collect (cons token count))
;	      #'>
;	      :key #'(lambda (element)
;		       (if (memq (car element) '( { } / [ ] ))
;			   0
;			   (* (+ 2 (length (symbol-name (car element))))
;			      (cdr element)))))
;	as text = (symbol-name token)
;	as i from 1 upto 1000 
;	when (and (< 28 i)
;		  (< 4 (length text))
;		  (find #\- text)) 
;	  do
;	    (format t "~&  (\"~C~C\" ~(~S~))"
;		    ;(incf n)
;		    (code-char c2) (code-char (incf c1))
;		    text)
;	    (when (<= z c1)
;	      (incf c2)
;	      (setf c1 (1- a)))))




;;; `Postscript-translate-token' inserts one token into the translation
;;; stream.  It will insert whitespace before the token if necessary to
;;; delimit it.
;;;  The token may be a symbol, a number, a character, or a string.

(defun-for-macro postscript-translate-token (token self-delimiting-p)
  (multiple-value-bind (token-text self-delimiting-p)
    (postscript-translate-encode-token token self-delimiting-p)
    (postscript-translate-reserve-space 
     (+ 1 (length token-text))
     postscript-translate-stream)
    (unless (or postscript-translate-previous-token-was-self-delimiting
                self-delimiting-p)
      (incf postscript-translate-line-length 1)
      (write-char #\space postscript-translate-stream))
    (incf postscript-translate-line-length (length token-text))
    (write-string token-text postscript-translate-stream)
    (setf postscript-translate-previous-token-was-self-delimiting self-delimiting-p)
    (setf postscript-translate-previous-token token)))







;;;; Assigning Header Slot Indexes and Associating Those Indexes With Names




;;; This section implements two macros; start-postscript-header and
;;; end-postscript-header, which should be used to bracket the top
;;; level forms which make up the header.  They setup the state
;;; used to associate the names of each top level form with the
;;; index number that form is assigned in header array.

;;; When developing the header it is very useful to be able to 
;;; recompile individual forms.  This is enabled by keeping a
;;; mapping, in development, from names to slots in the
;;; postscript array.  The slots are handed out in order as
;;; the forms are encountered.  If you recompile the entire
;;; buffer a new array is allocated and new slot assignments
;;; are made.


;;; `Last-postscript-header-index', a defvar for macro, is used to hand out slot
;;; indexs as postscript defining forms are encountered.  It is reset when ever
;;; start-postscript-header is expanded.

(defvar-for-macro last-postscript-header-index)




;;;'Postscript-header-index-key' is a global holding the key used to map names
;;;to slot indexes, that key is a gensym.  It is changed when ever
;;;start-postscript-header is expanded and that assures that a new set of index
;;;numbers are handed out.  It is a defvar for macro defined only in
;;;development.

#+development 
(defvar-for-macro postscript-header-index-key)



;;; The macro `postscript-header-index' maps from the name given to the
;;; postscript header slot index using the current key.  This is defined only in
;;; development

#+development
(defmacro postscript-header-index (name)
  `(get ,name postscript-header-index-key))



(defmacro start-postscript-header ()
  ;; Side effect the compile time environment
  #+development
  (setf postscript-header-index-key
	(make-symbol "POSTSCRIPT-DEFINITION-INDEX"))
  #+development
  (loop for i from 0 below (length postscript-header-array)
	do (setf (aref postscript-header-array i) nil))
  (setf last-postscript-header-index -1)
  nil)


(defmacro end-postscript-header ()
  ;; Nothing to do.
  nil)



;;; `Get-or-make-postscript-header-index' takes a name 
;;; and returns an index in the postscript header at which the
;;; postscript definition with that name should appear.  This
;;; is defined for the macro pass.

;;; The name and index are associated with each other when in development
;;; to enable the recompiling of individual forms in the buffer.

(defun-for-macro get-or-make-postscript-header-index (name)
  #-development 
  (declare (ignore name))
  #+development
  (or (postscript-header-index name)
      (setf (postscript-header-index name)
	    (incf last-postscript-header-index)))
  #-development
  (incf last-postscript-header-index))







;;;; Translating Postscript S Expressions




;;; The translation of postscript S Expressions into postscript token
;;; steams is extremely simple minded.  The meat of this translation
;;; is done by `postscript-translate-form-1.'

;;; Atoms are passed thru unchanged.  By default lists, i.e.  function
;;; calls, are converted into postfix notation as so:
;;;       (f 1 2) --> 1 2 f
;;;       (mul (add 2 3) (neg 4)) -->  2 3 add 4 neg mul
;;; A few "special forms" are provided, their translations are
;;; illustrated by example:
;;;      (quote a)           --> /A
;;;      (ps-token foo)      --> foo
;;;      (ps-quote "FooBar") --> FooBar
;;;      (ps-proc ...)       --> { ... }
;;;      (progn ... )        --> ...
;;;      (quote (ps-quote "FooBar"))
;;;                          --> /FooBar

;;; Some "special forms" are defined by "macros".
;;;      (if (lt 1 x) true)  --> 1 x lt { true } if
;;;      (if (lt 1 x) true false) 
;;;                          --> 1 x lt { true } { true } ifelse
;;;      (setq a 1)          --> /A 1 def
;;;      (let ((x 1) (y 2)) ...) -> 1 /x deflocal 2 /y deflocal ...
;;;      (let* ((x 1) (y 2)) ...) -> 1 /x deflocal 2 /y deflocal ...
;;;      (multiple-value-bind (x y) (currentpoint) (moveto x y))
;;;                          --> current-point /y deflocal /x deflocal x y moveto

;;; Note that all bindings are global and that there is no distinction between
;;; let and let*.

;;; Some standard postscript looping forms are provided by "macros."
;;;   (loop . <body>)
;;;   (repeat <count> . <body>)
;;;   (for (<var> <initial> <increment> <limit>) . <loop-body>)
;;;   (forall (<var> <composite-object>) . <loop-body>)

;;; Some mimics of a few common lisp classics are provided
;;;   (when <pred> . <body>)    --> (if <pred> (progn . <body))
;;;   (cond)                    --> illegal
;;;   (cond (t ...) ...)        --> illegal
;;;   (cond (true ...))         --> (progn ...)
;;;   (cond (<pred> <rhs>))     --> (if <pred> <rhs>)
;;;   (cond (<pred> <rhs>) ...) --> (if <pred> <rhs> (cond ...))

;;; These top level Lisp forms are used to write your postscript header.
;;;     defun-for-postscript
;;;     defmacro-for-postscript
;;;     top-level-progn-for-postscript

;;; This provides a VERY SLIGHT syntatic sugar over the postscript
;;; interpreter.  But the runtime model is still that of postscript.
;;; In particular it is critical to remember that the stack must
;;; be handled right.  For example (progn (add 1 2) (add 3 4) (add))
;;; will leave one object on the stack.

;;; These translations will complain if you call a function unknown
;;; to the translator.



;;; `Defmacro-for-postscript' provides a very primitive form of macros.
;;; These are used mostly to define the various looping and control forms.

;;; The property `postscript-macro' is used to hold the name of a function
;;; of the form postscript-macro-function-for-<foo>.  These functions take one argument
;;; the form they should rewrite, and they return that rewrite.

#-no-macro
(eval-when (:compile-toplevel :load-toplevel :execute)
(def-global-property-name postscript-macro-function)
)


;;; `Defmacro-for-postscript' has exactly the syntax of defmacro.  Except that
;;; the argument lambda list is limited only using the (&whole <form>). 

(defmacro defmacro-for-postscript (name args &body body)
  (unless (and (consp args)
	       (= 2 (length args))
	       (eql '&whole (car args)))
    (warn "In ~S: the lambda list of a defmacro-for-postscript was misformed: ~S" name args))
  (let ((macro-function (intern (format nil "POSTSCRIPT-MACRO-FUNCTION-FOR-~S" name)))
	(whole-var (second args)))
    (if (eval-feature :no-macros)
	'(progn)
	`(eval-when (:compile-toplevel :load-toplevel :execute)	       ; Behave like a CL macro at compile-time.
	   (defun ,macro-function (,whole-var)
	     ,@body)
	   (setf (postscript-macro-function ',name) ',macro-function)))))





;;; `Current-top-level-postscript-form', a defvar for macro, is used
;;; to provide the name of the current thing being translated when
;;; translating a postscript form.

(defvar-for-macro current-top-level-postscript-form)



;;; `Postscript-translate-form' takes a name and a postscript 
;;; S Expression.  It translates that S Expression into an encoded string.

;;; It is the callers responsibily to macro expand into a form that assigns
;;; that form to a slot in the header array.

(defun-for-macro postscript-translate-form (name-for-form form)
  (with-output-to-string (postscript-translate-stream)
    (let ((current-top-level-postscript-form name-for-form)
	  (postscript-translate-previous-token-was-self-delimiting nil)
	  (postscript-translate-previous-token nil)
	  (postscript-translate-line-length 0))
      (postscript-translate-form-1 form))))



;;; `Postscript-translate-form-1' is the recursive routine used to emit
;;; individual forms.  It is here that the special forms are handed.  No syntax
;;; checking is done.

;;; One slightly notable thing.  Progn forms nested in the branchs of an if are
;;; given special handling.

(defun-for-macro postscript-translate-form-1 (form)
  (typecase form
    (symbol
     (postscript-translate-token form nil))
    (number
     (postscript-translate-token form nil))
    (string
     (let ((length (+ 2 (length form))))
       (postscript-translate-reserve-space length postscript-translate-stream)
       (format postscript-translate-stream "(~A)" 
	       (postscript-encode-to-quote-uppercase form))
       (incf postscript-translate-line-length length)))
    (list
     (case (first form)
       (ps-proc
	(postscript-translate-token '\{ t)
	(postscript-translate-form-1 `(progn ,@(rest form)))
	(postscript-translate-token '\} t))
       (progn
	(loop for stm in (rest form) do (postscript-translate-form-1 stm)))
       (ps-token
	(let ((token (second form)))
	  (unless (or (symbolp token)
		      (stringp token))
	    (warn "In ~S: ps-token which requires a symbol or string encountered: ~S"
		  current-top-level-postscript-form token))
	  (postscript-translate-token token nil)))
       (quote
	(let ((token (second form)))
	  (cond
	    ;; `(ps-token "Foo") -> (ps-quote "Foo") 
	    ((and (consp token)
		  (eql 'ps-token (car token)))
	     (postscript-translate-form-1 `(ps-quote ,(second token))))
	    (t
	     (unless (not (consp token)) 
	       (warn "In ~S: malformed quote postscript form: ~S" current-top-level-postscript-form token))
	     (postscript-translate-token '/ t)
	     (postscript-translate-token (second form) nil)))))
       (ps-quote
	(postscript-translate-token '/ t)
        (postscript-translate-token (second form) nil))
       (postscript-array
	(postscript-translate-token '\[ t)
	(postscript-translate-form-1 `(progn ,@(rest form)))
	(postscript-translate-token '\] t))
       (postscript-hex-string
	(format postscript-translate-stream "<~A>" 
		(postscript-encode-to-quote-uppercase (second form))))
       (ps-verbatim
	(loop for token in (rest form) 
	      do
	  (cond
	    ((and (consp token)
		  (eq 'ps-quote (first token)))
	     (postscript-translate-token '/ t)
	     (postscript-translate-token (second token) nil))
	    ((and (consp token)
		  (eq 'ps-token (first token)))
	     (postscript-translate-token (second token) nil))
	    ((stringp token)
	     (postscript-translate-form-1 token))
	    ((or (symbolp token)
		 (integerp token))
	     (postscript-translate-token token
					 (if (memq token '( { } ))
					     t nil)))
	    (t
	     (warn "In ~S: unknown token in ps-verbatim: ~S" current-top-level-postscript-form token)))))
       (otherwise
	(let ((handler (postscript-macro-function (first form))))
	  (cond
	    (handler
	     (postscript-translate-form-1 (funcall handler form)))
	    (T
	     ;; Vanilla call site, convert to postfix.
	     #+development
	     (postscript-semantic-check-call form)
	     (postscript-translate-form-1 `(progn ,@(rest form)))
	     (postscript-translate-token (first form) nil)))))))))







;;;; Macros for Postscript Special and Usual Forms.

(defmacro-for-postscript setq (&whole form)
  (let ((target (second form))
	(source (third form)))
    `(def ',target ,source)))

(defmacro-for-postscript if (&whole form)
  (unless (<= 3 (length form) 4)
    (warn "In ~S: malformed postscript if statement: ~S" current-top-level-postscript-form form))
  (let ((has-else-clause? (cdddr form)))
    `(progn
       ,(second form)
       (ps-proc ,(third form))
       ,@(when has-else-clause? `((ps-proc ,(fourth form))))
       (ps-token ,(if has-else-clause? 'ifelse 'if)))))

(defmacro-for-postscript cond (&whole form)
  (gensym-dstruct-bind ((nil (lhs . rhs) . other-clauses?) form)
    (when (eql t lhs)
      (warn "In ~S: T is inappropriate in postscript code." current-top-level-postscript-form))
    (if (eql 'true lhs)
	`(progn ,@rhs)
	`(if ,lhs
	     (progn ,@rhs)
	     ,@(when other-clauses?
		 `((cond ,@other-clauses?)))))))

(defmacro-for-postscript when (&whole form)
  (let ((condition (second form))
	(body (cddr form)))
    `(if ,condition (progn ,@body))))


;;; Binding Forms

(defmacro-for-postscript let* (&whole form)
  (let ((binding-forms (second form))
	(body (cddr form)))
    `(progn
       ,@(loop for (var initial-value) in binding-forms
	       collect `(setq ,var ,initial-value))
       ,@body)))

(defmacro-for-postscript let (&whole form)
  (let ((binding-forms (second form))
	(body (cddr form)))
    `(progn
       ,@(loop for (var initial-value) in binding-forms
	       collect `(setq ,var ,initial-value))
       ,@body)))

(defmacro-for-postscript multiple-value-bind (&whole form)
  (let ((variables-to-bind (second form))
	(form-returning-multiple-values (third form))
	(body-forms (cdddr form)))
    `(progn
       ,form-returning-multiple-values
       ,@(loop for var in (nreverse (copy-list variables-to-bind))
	       collect `(deflocal ',var))
       ,@body-forms)))



;;; Looping constructs

(defmacro-for-postscript loop (&whole form)
  `(progn
     (ps-proc ,@(rest form))
     (ps-token loop)))

(defmacro-for-postscript repeat (&whole form)
  (let ((count-form (second form))
	(body (cddr form)))
    `(progn
       ,count-form
       (ps-proc ,@body)
       (ps-token repeat))))

(defmacro-for-postscript for (&whole form)
  ;; ((variable initial increment limit) &body body)
  (let ((args (second form))
	(body (cddr form)))
    `(progn
       ,@(rest args)
       (ps-proc
	 (deflocal ',(first args))
	 ,@body)
       (ps-token for))))

(defmacro-for-postscript forall (&whole form)
  (let* ((loop-control (second form))
	 (composite-object (car (last loop-control)))
	 (iteration-vars (subseq loop-control 0 (1- (length loop-control)))) 
	 (body (cddr form)))
    `(progn
       ,composite-object
       (ps-proc
	 ,@(loop for local-var in (nreverse iteration-vars)
		 collect `(deflocal ',local-var))
	 ,@body)
       (ps-token forall))))


(defmacro-for-postscript adjust-coordinates-by-one-half (&whole form)
  (let ((x1 (second form))
	(y1 (third form))
	(x2 (fourth form))
	(y2 (fifth form)))
    `(cond
      ((eq ,x1 ,x2)
       (setq ,x1 (add ,x1 0.5))
       (setq ,x2 (add ,x2 0.5)))
      ((eq ,y1 ,y2)
       (setq ,y1 (add ,y1 0.5))
       (setq ,y2 (add ,y2 0.5))))))

;; This ps macro belongs in ps-header.lisp, but I'm having some problem using it
;; in the same file in which it is defined.


(defmacro-for-postscript unless-transparent (&whole form)
  (let ((body (cdr form)))
    `(if (eq color-value #.postscript-transparent-color-value)
	 (progn)
	 (progn ,@body))))



;;; `Postscript-semantic-check-call' checks that the functions you are calling in
;;; your postscript code are actually known, either as builtin postscript operators
;;; or in from previous defun-for-postscript forms.

#+development
(defun-for-macro postscript-semantic-check-call (form)
  (let ((name (car form)))
    (unless (or (postscript-header-index name)
		(postscript-builtin-operator-p name))
      (warn "In ~S: unknown postscript operator: ~S"
	    current-top-level-postscript-form
	    name))))







;;;; Interface For Defining Header



;;; `Defun-for-postscript' records the translated encoded definition
;;; of a postscript function in the header array.  It's syntax is
;;; just like defun, except the lambda list must be no more
;;; complex than a list of symbols.

(defmacro defun-for-postscript (name args &body body)
  (let ((header-index 
	  (get-or-make-postscript-header-index name))
	(encoded-text
	  (postscript-translate-form name 
	    `(def ',name 
		  (ps-proc
		    ,@(loop for arg in (nreverse args) 
			    collect `(deflocal ',arg))
		    ,@body)))))
    `(progn
       (setf (svref postscript-header-array ,header-index)
	   ,encoded-text)
       ',name)))




;;; `Defvar-for-postscript' records a definition for a postscript
;;; variable in the header array.  It's syntax is just like defvar
;;; but the initial value is required and no documention is
;;; allowed.

(defmacro defvar-for-postscript (name initial-value)
  (let ((header-index 
	  (get-or-make-postscript-header-index name))
	(encoded-text
	  (postscript-translate-form
	    name
	    `(def ',name ,initial-value))))
    `(progn
       (setf (svref postscript-header-array ,header-index)
	     ,encoded-text)
       ',name)))

(defmacro top-level-progn-for-postscript (name &body forms)
  (let ((header-index 
	  (get-or-make-postscript-header-index name))
	(encoded-text
	  (postscript-translate-form
	    name
	    `(progn ,@forms))))
    `(progn
       (setf (svref postscript-header-array ,header-index)
	     ,encoded-text)
       ',name)))




;;;; Interface For Debugging



;;;; Uncompress Postscript files for debugging.

#+development
(defun uncompress-postscript (input-filename &optional (output-filename? t))
  (with-open-file (input-stream input-filename)
    (cond
      ((stringp output-filename?)
       (with-open-file (output-stream output-filename? :direction :output)
	 (uncompress-postscript-1 input-stream output-stream)))
      ((eql t output-filename?)
       (uncompress-postscript-1 input-stream *standard-output*))
      ((eql nil output-filename?)
       (with-open-file (output-stream (concatenate'string input-filename "u"))
	 (uncompress-postscript-1 input-stream output-stream))))))

#+development
(defun uncompress-postscript-1 (input-stream output-stream)
  (macrolet ((uprinc (x) `(write-char ,x output-stream))
	     (uformat (&rest args) `(format output-stream ,@args))
	     (new-line ()
	       `(if (zerop depth)
		 (uformat "~%")
		 (uformat "~%~VT" depth))))
    (loop with encoded-operator-pad1 = (concatenate'string "$A")
	  with encoded-operator-pad2 = (concatenate'string "$AB")
	  with inside-array? = nil
	  with inside-string? = ()	; A stack.
	  with depth = 0
	  for c? = (read-char input-stream nil nil)
	  while c?
	  do
	  (cond (inside-string?
		 (uprinc c?)
		 (when (char-equal c? #\))
		   (pop inside-string?)))
		(t
		 (case c?
		   (#\%
		    (uprinc c?)
		    (unless (or inside-string? inside-array?) ; get past comment line
		      (let ((rest-of-line? (read-line input-stream nil nil)))
			(when rest-of-line?
			  (write-string rest-of-line? output-stream)
			  (new-line)))))
		   (#\$
		    (let* ((c1 (read-char input-stream nil nil))
			   (c2 (read-char input-stream nil nil))
			   (pad nil))
		      (setf (char encoded-operator-pad1 1) c1)
		      (cond ((alphanumericp c2)
			     (setf (char encoded-operator-pad2 1) c1
				   (char encoded-operator-pad2 2) c2
				   pad encoded-operator-pad2))
			    (t
			     (unread-char c2 input-stream)
			     (setq pad encoded-operator-pad1)))
		      (uformat "~(~A~) " (or (postscript-decompress-operator-name pad) pad))))
		   (#\/
		    (unless inside-array? (new-line) (when (zerop depth) (new-line)))
		    (uformat "/"))
		   (#\{
		    (new-line)
		    (uformat "{ ")
		    (incf depth 2))
		   (#\}
		    (decf depth 2)
		    (new-line)
		    (uformat "}"))
		   ((#\[ #\<)
		    (setf inside-array? t)
		    (uprinc c?))
		   ((#\] #\>)
		    (setf inside-array? nil)
		    (uprinc c?))
		(#\(
		 (push c? inside-string?)
		 (uprinc c?))
		(t
		 (uprinc c?))))))))

;; To do this right, we should fully tokenize the postscript file.
;; Maybe someone on the net already has a ps pretty-printer.


;;; `ppx' -- print postscript hex -- prints a postscript hex array, assuming it's 16 wide --
;;; we'll generalize later.

#+development
(defun ppx (string)
  (loop for i from 0 by 4 below (length string)
	do (terpri)
	   (loop for j from i
		 repeat 4
		 do (format t "~4,'0b" (parse-integer string :start j :end (+ j 1) :radix 16)))))



;;; `Show-postscript-header' displays the entire postscript header, along with some computed info.

#+development
(defun show-postscript-header ()
  (loop with total-encoded-size = 0
	with total-decoded-size = 0
        for i from 0 upto last-postscript-header-index
        as encoded-text = (aref postscript-header-array i)
	as decoded-text = (with-output-to-string (s)
			    (let ((postscript-translate-line-length 0)
				  (postscript-translate-previous-token-was-self-delimiting t)
				  (postscript-translate-previous-token nil))
			      (postscript-decode-text-into-real-stream encoded-text s)))
	as encoded-size = (length encoded-text)
	as decoded-size = (length decoded-text)
	do
    (incf total-encoded-size encoded-size)
    (incf total-decoded-size decoded-size)
    (format t "~2&~4D ~2D%~&~S~&~S" i 
	    (round (* 100 (/ encoded-size decoded-size))) encoded-text decoded-text)
	finally
	  (format t "~& Total Encoded/Decoded: ~4D/~4D, i.e. ~2D%" 
		  total-encoded-size total-decoded-size
		  (round (* 100 (/ total-encoded-size total-decoded-size))))))



;;; `Show-postscript-definition' displays the postscript associated with the given symbol,
;;; in both compressed and expanded forms.

#+development
(defun show-postscript-definition (id-or-name)
  (let ((id (if (numberp id-or-name) 
		id-or-name
		(postscript-header-index id-or-name))))
    (cond
      ((not (fixnump id))
       (warn "Unknown id-or-name: ~S" id-or-name))
      (T
       (format t "~&~4D/~S:~%~%~S~&" id id-or-name (aref postscript-header-array id))
       (let* ((postscript-translate-line-length 0)
	      (postscript-translate-previous-token-was-self-delimiting t)
	      (postscript-translate-previous-token nil)
	      (text (with-output-to-string (stream)
		      (postscript-decode-text-into-real-stream 
		       (aref postscript-header-array id)
		       stream))))
	 (#-ansi-cl lisp:with-input-from-string
	  #+ansi-cl common-lisp:with-input-from-string (stream text)
	   (uncompress-postscript-1 stream *standard-output*))
	 (values))))))


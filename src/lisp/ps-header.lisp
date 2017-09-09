;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module PS-HEADER

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author(s): Ben Hyde






;;;; Introduction To The Module PS HEADER


;;; This module implements the postscript header.  This header is
;;; inserted at the front of every postscript printing job.  The
;;; PRINTING module calls `emit-postscript-prolog' which is exported from
;;; the POSTSCRIPT module.







;;;; Inter-Module References



;;; PS-HEADER depends upon the macros defined in the module POSTSCRIPT.
;;; There are no forward references.  There are no uses of other modules.

;;; PS-HEADER must be a seperate module so that the compile time macros,
;;; variables and functions provided by the module POSTSCRIPT have
;;; been loaded.







;;;; The Postscript Header



;;; The entire header is bracketed by calls upon start-postscript-header and
;;; end-postscript-header.  These macros provide the translator with an oportunity to
;;; reset it's tables, etc.

(start-postscript-header)





;;;; Low Level Postscript Utilities



(defun-for-postscript deflocal ()
  (exch)
  (def))
;; DEFLOCAL is used by the translator, so define it first.

(defun-for-postscript inch (inches)
  (mul inches 72))

(defun-for-postscript max (_a _b)
  (if (gt _a _b) _a _b))

(defun-for-postscript min (_a _b)
  (if (gt _a _b) _b _a))

(defun-for-postscript clip-to-rectangle (_left _top _right _bottom)
  (newpath)
  (moveto _left _top)
  (lineto _right _top)
  (lineto _right _bottom)
  (lineto _left _bottom)
  (closepath)
  (clip)
  (newpath))

;;; Here we adjust the width of the space character (ascii 32) to be the same as G2's
;;; nword-spacing. Recall that nword-spacing is a fixnum scaled by scaling-factor-for-text-widths.

(defun-for-postscript show-with-wordspacing (text-line)
  (widthshow (sub (div nword-spacing #.scaling-factor-for-text-widths)
                  width-of-space-character)
             0 32 text-line))

;; The Postscript operator WIDTHSHOW draws a text string with the width of the
;; given character INCREASED by dx,dy.  Since we are given the actual spacing
;; desired by G2, in nword-spacing, we must first substract off the spacing which
;; the font already has.


(defvar-for-postscript ctm-original
                       (currentmatrix (matrix)))

(defvar-for-postscript ctm-backup
                       (matrix))

(defun-for-postscript savectm ()
  (currentmatrix ctm-backup)
  (pop))

(defun-for-postscript restorectm ()
  (setmatrix ctm-backup))

(defvar-for-postscript stroke-ctm-backup (matrix))

(defun-for-postscript fine-stroke ()
  (currentmatrix stroke-ctm-backup) (pop)
  (setmatrix ctm-original)
  (stroke)
  (setmatrix stroke-ctm-backup))






;;;; Define the Postscript Blop font



;;; The Blob font is implemented in postscript as a bitmap font
;;; using the Postscript Cookbook's example bitmap font as a starting point.
;;; The Kanji fonts are defined by copying this one.

; (defvar-for-postscript blob-font (dict 9))


;;; `Bitmap-buildchar' is differs from the buildchar routine given in
;;; the cookbook.  The bounding box passed to setcachedevice is
;;; computed rather than stored with the character.  It is computed
;;; from the resolution which is stored in the imagemaskmatrix and
;;; the information about the bitmap's size and offset stored with
;;; each character.

;;; One last difference is that the character width is recorded in
;;; units of bits, rather than in font units, and is converted in
;;; the prior to the call to the setcachedevice.

(defun-for-postscript bitmap-buildchar (fontdict char)
  (let* ((charname (get (get fontdict (ps-quote "Encoding")) char))
         (charinfo (get (get fontdict (ps-quote "CharData")) charname))
         (wx (get charinfo 0))
         ; (charbbox (getinterval charinfo 1 4))
         (imm (get fontdict 'imagemaskmatrix))
         (resolution (get imm 0))
         (bits-wide (get charinfo 1)) ; (get charinfo 5)
         (bits-high (get charinfo 2)) ; (get charinfo 6)
         (x-imm-offset (get charinfo 3)) ; (get charinfo 7)
         (y-imm-offset (get charinfo 4)) ; (get charinfo 8)
         )

    ;; Inform the font cache of the shape of this character.
    (setcachedevice
      ;; w(x,y)  -- the vector from the origin of this char to the next.
      (div wx resolution)
      0
      ;; ll(x,y) -- the lower left corner of the bounding box.
      (neg (div x-imm-offset resolution))
      (neg (div y-imm-offset resolution))
      ;; ur(x,y) -- the upper right corner of the bounding box.
      (div (add x-imm-offset bits-wide) resolution)
      (div bits-high resolution))

    ;; Offset the bitmap by to the origin of the char.
    (put imm 4 x-imm-offset)
    (put imm 5 y-imm-offset)

    ;; Stamp it out.
    (imagemask
      bits-wide
      bits-high
      true
      imm
      ; (cvx (getinterval charinfo 9 1))
      (cvx (getinterval charinfo 5 1))
      )))


;;; The top level postscript progn `setup-blob-font' creates and
;;; defines a bitmap font called the blob-font.  It consists of
;;; no more than the .nodef character.  It's purpose is to render
;;; the cute little blobs that appear in the editor when typing
;;; the password, and to provide something to copy when creating
;;; kanji fonts.

;;; The font is rendered into a unit square.  It is encoded via
;;; the standard encoding vector.  It is a type 3 font, i.e. a
;;; bitmap font.

;;; The bitmap is designed to so that 16 bits are
;;; available from baseline to baseline.  The transform matrix
;;; passed to imagemask is [16 0 0 -16 0 0] i.e. each bit is
;;; rendered into a 1/16 unit square.  The -16 means that the
;;; scanning will proceed from top to bottom.   Since scanning
;;; goes top to bottom the transform matrix is tranlated, for
;;; each character, to so that it starts at the top of that
;;; character.

;;; The .nodef character is 13 bits wide, or 13/16 in the unit square.
;;; a one bit space is on the right side and a 12 bit square is
;;; is done in black.

;;; The CharData for the font contains these entries for each character.
;;;   1. character-width, in the unit square>
;;;   2. bounding box of inked in area, in the unit square.
;;;   3. bitmask width in hieght, in bits.
;;;   4. the offset of those bits so that the first bit will appear
;;;      in the top left corner of the character, in bits.
;;;   5. a hex string consisting of the bits.
;;; That is a total of 10 values per character.

;;; The fourth value, the offset for the bit map, has .5 subtracted
;;; from each value to avoid device rounding problems (see the cookbook
;;; program 21).

(defun-for-postscript setup-blob-font ()
  (setq blob-font (dict 11)) ; Global
  (begin blob-font)
  (setq (ps-token "FontType") 3)
  (setq (ps-token "FontMatrix")
        (postscript-array 1 0 0 1 0 0))
  (setq (ps-token "Encoding")
        (copy (ps-token "StandardEncoding")
              (array (length (ps-token "StandardEncoding")))))
  (ps-verbatim 0 1 255 { (ps-token "Encoding") exch /.notdef put } for)
  (setq (ps-token "BuildChar") (load 'bitmap-buildchar))
  (setq imagemaskmatrix
        (postscript-array 16 0 0 -16 0 0))
;;  (setq (ps-token "UniqueID") 24)
  (setq (ps-token "FontBBox") (postscript-array -2 -2 20 20))
  (setq (ps-token "CharData") (dict 25))
  ;; Fill out the CharData, for .notdef only.
  (begin (ps-token "CharData"))
  (setq (ps-token .notdef)
        (postscript-array
          ;;.6 .04 0 .52 .56 12 14 -1.5 13.5
          ;;1.     2.                 3.            4.
          ;;.8125    0 0 0.75 0.74      12 12         0 12
          ;;15    0 0 0.75 0.74      12 12         0 12
          15                         12 12         0 12
          ;; 5.
          (postscript-hex-string
              "ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff"
              ;; "7fff bfff dfff efff f7ff fbff fdff feff ff7f ffbf ffdf ffef"
              )))
  (end)
  (end)
  (pop (definefont 'blob-font blob-font)))

;; The UniqueID must be changed if you modify the font.  The font cache
;; in the printer is not cleared between print jobs.
;; Once this works, however, ought to not include UniqueID, since there
;; is no guarentee it is unique.




;;;; Kanji Font Handling



;;; If a print job has kanji characters utilized in it then the job specific
;;; header for that print job will define some number of kanji microfonts.
;;; each kanji microfont defines 250 characters that actaully were used in
;;; the print job.  Microfonts, when defined always, only one point.

;;; Sets of microfonts are gathered together into actual Kanji fonts.
;;; These given the same name as the font-name in g2, e.g., KANJI16.  They
;;; are represented by an array, with one entry for each microfont.  These
;;; are not postscript fonts, to avoid confusion these are known as kanji
;;; font vectors.

;;; `Corresponding-kanji-font' is a postscript variable used to map from G2 font
;;; names, i.e.  HM14, to the corresponding postscript kanji font vector names,
;;; i.e.  KANJI-A.  Each of the built in fonts, HM14, etc.  has an associated
;;; Kanji font.  This association is made in the dictionary
;;; corresponding-kanji-font.  This is filled in from the global property on font
;;; names corresponding-kanji-font-name-and-magnification.  When the use of a
;;; font is noticed during pass 1 of printing.

;;; Review of data types:
;;;    kanji font         -- a G2 font, a set of thousands of characters
;;;    kanji microfont    -- a set of 250 characters that are actually used in this
;;;                          print job, defined with scale equals 1 point.
;;;    kanji font vector  -- an array of kanji microfonts, scale equals 1 point.
;;;    corresponding kanji font vector
;;;                       -- created from a kanji font vector, scale as needed.
;;; all these are given names.  For example
;;;   kanji16         a kanji font name (appears only in the LISP world).
;;;   k14             a kanji microfont name
;;;   kanji16-vector  a kanji font vector name
;;;   kanji-a         a corresponding kanji font vector name
;;; The postscript names have values in the kanji-dictionary.

;;; In the main postscript dictionary two names root this mechinism.
;;;   kanji-dictionary   -- all the kanji microfonts, font vectors, etc.
;;;   current-kanji-font-vector
;;;                      -- contains when printing a text line containing kanji
;;;                      -- the corresponding kanji font vector

;;; The generated code that defines the postscript dictionary looks like this:

;;; kanji-dictionary begin
;;; /kanji16 begin-kanji-font
;;;   /k0 0 begin-kanji-microfont
;;;  /c1 0.8125 0 0 0.75 0.74 12 12 0 12<ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff> def-kanji-character
;;;  /c2 0.8125 0 0 0.75 0.74 12 12 0 12<ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff> def-kanji-character
;;;  /c3 0.8125 0 0 0.75 0.74 12 12 0 12<ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff> def-kanji-character
;;;  /c4 0.8125 0 0 0.75 0.74 12 12 0 12 <ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff> def-kanji-character
;;;   /k0 0 end-kanji-microfont
;;; /kanji16 end-kanji-font
;;; end

(defun-for-postscript begin-kanji-font (kanji-font-vector-name)
  (setq current-kanji-font-vector (array 100))
  (def kanji-font-vector-name current-kanji-font-vector))

(defun-for-postscript end-kanji-font (kanji-font-vector-name)
  )

(defun-for-postscript begin-kanji-microfont (kanji-microfont-name microfont-number)
  (setq current-microfont (dict 25))
  (def kanji-microfont-name current-microfont)
  (begin current-microfont)
  (setq (ps-token "FontType") 3)
  (setq (ps-token "FontMatrix") (postscript-array 1 0 0 1 0 0))
  (setq (ps-token "Encoding") microfont-encoding-vector)
  (setq (ps-token "BuildChar") (load 'bitmap-buildchar))
  (setq imagemaskmatrix        (postscript-array 16 0 0 -16 0 0))

  ;; This was causing the output to get messed up when there were more
  ;; than one Kanji font (i.e., Kanji16 with Kanji24).  The spec says this
  ;; is unnecessary, so why put it in?  The problem is that microfont-number
  ;; is not unique -- e.g., if you have both kanji24 & kanji16, you get
  ;; microfont-number = 0 for each font.  The font renderer evidently runs
  ;; them together.  Commented out.  (MHD 6/5/93)
  ; (setq (ps-token "UniqueID") (add 300 microfont-number))

  (setq (ps-token "FontBBox") (postscript-array -2 -2 20 20))
  (setq (ps-token "CharData") (dict 256)))

(defun-for-postscript end-kanji-microfont (kanji-microfont-name microfont-number)
  (ps-verbatim kanji-microfont-name microfont-number)
  (end) ; leave the font dict
  (deflocal 'microfont-number)
  (deflocal 'kanji-microfont-name)
  (put current-kanji-font-vector
       microfont-number
       (definefont
         kanji-microfont-name
         current-microfont)))

(defun-for-postscript def-kanji-character
                      (character-name
                        width
                        bit-width bit-height
                        bits-x-offset bits-y-offset
                        bits)
  (begin (ps-token "CharData"))
  (ps-verbatim
    character-name
    (ps-token "[")
    width
    bit-width
    bit-height
    bits-x-offset
    bits-y-offset
    bits
    (ps-token "]")
    def)
  (end)) ; leave the CharData dictionary.

(defun-for-postscript def-unknown-kanji-character (character-name)
  (def character-name
       (postscript-array
         15 12 12 0 12
         (postscript-hex-string
           "ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff"
           ))))

;; I (MHD) found this to be not working; at least, postscript errors were
;; occuring around its presence in postscript print job files.  It also seemed
;; to be the wrong thing to not use the regular def-kanji-character along with
;; the font-in-question's missing character description.  It would be good not
;; to repeat the definition, i.e., somehow refer back to it, but that wasn't
;; being done anyway; thus, this only saved a few tokens, and it's meant to
;; handle a degenerate case anyway, and so doesn't seem worth bothering to fix
;; up.  (It no longer has a caller; its former caller is
;; postscript-emit-kanji-character-description, q.v., in PRINTING.)  (MHD
;; 7/21/93)


(defun-for-postscript def-kanji-correspondence
                      (font kanji-font-vector-name size magnification)

  (let ((scale-factor (mul 16 (div magnification 256)))
        ;; Was:
        ;;   (scale-factor (mul size (div magnification 256)))
        ;; Multiply by 16 (not the point size), since, as it
        ;; says above, "each bit is rendered into a 1/16 unit square".
        ;; (MHD 6/5/93)
        (kanji-font-vector (get kanji-dictionary kanji-font-vector-name))
        (new-font-vector (array (length kanji-font-vector))))
    (for (i 0 1 (sub (length kanji-font-vector) 1))
         (let ((microfont (get kanji-font-vector i)))
           (if (eq null microfont) (exit))
           (put new-font-vector i (scalefont microfont scale-factor))))
    (put corresponding-kanji-font font new-font-vector)))


;;; Loop over the characters the text line, finding and showing escaped Kanji
;;; characters, while also showing intermediate roman characters.

(defun-for-postscript kanji-show (kanji-text-line)
  (loop
    (cond
      ((ps-verbatim kanji-text-line (ps-token "(\\033)") search)
       (show-with-wordspacing)
       (pop)
       (deflocal 'kanji-text-line)
       (let ((microfont-number (get kanji-text-line 0))
             (kanji-bit (getinterval kanji-text-line 1 1)))
         (setq kanji-text-line
               (getinterval kanji-text-line 2 (sub (length kanji-text-line) 2)))
         (setfont (get current-corresponding-kanji-font-vector microfont-number))
         (show kanji-bit)  ; shows a 1-long string in the Kanji microfont
                           ; -- I changed this to use show from show-with-wordspacing
                           ; since it was substituting the "width of a space" for
                           ; the character occupying the Space char position in the
                           ; microfont -- a subtle bug. (MHD 6/7/93)
         (setfont current-primary-font)))
      (true
       (show-with-wordspacing)
       (exit)))))
;; Careful with name conflicts: text-line is used by show-with-wordspacing.



(defun-for-postscript set-corresponding-kanji-font (font-name)
  (setq current-corresponding-kanji-font-vector
        (get corresponding-kanji-font font-name)))


;;; Select a text font.  Precompute and cache the width of a space character.

(defun-for-postscript set-appropriate-font ()
  (setq current-primary-font (exec (cvx (get font-map 0))))
  (setfont current-primary-font)
  (setq width-of-space-character (ps-verbatim " " stringwidth pop)))







;;;;  NOP Definitions For Operators Currently Not Supported.




;;; This section contains operators for all the messages that G2 can emit.
;;; These all just consume their operands, and then do nothing.  This provides
;;; a to do list, and a way to make it more likely that printing succeeds
;;; while we are developing handlers for each of these.








;;; begin-window-update           -- is never generated
;;; set-up-palette                -- is never generated
;;; initialize-scratchpad-raster  -- is never generated

;;; paint-solid-rectangle-in-current-scratchpad-raster   -- is implemented below.
;;; paint-line-in-current-scratchpad-raster              -- is implemented below.
;;; paint-arc-or-circle-in-current-scratchpad-raster     -- is implemented below.
;;; paint-filled-triangle-in-current-scratchpad-raster   -- is implemented below
;;; paint-point-in-current-scratchpad-raster             -- is implemented below
;;; paint-wide-line-in-current-scratchpad-raster         -- is implemented below
;;; paint-solid-rectangle-in-current-window              -- is implemented below
;;; paint-from-line-of-text-to-current-scratchpad-raster -- is implemented below

;;; add-solid-rectangle-to-current-window        -- is implemented below.
;;; add-from-icon-rendering-to-current-window    -- is implemented below.
;;; add-upward-sloping-line-to-current-window    -- is implemented below.
;;; add-downward-sloping-line-to-current-window  -- is implemented below.
;;; add-from-line-of-text-to-current-window      -- is implemented below.
;;; add-from-graph-rendering-to-current-window   -- is implemented below



;;; begin-making-icon-rendering -- is a nop

(defun-for-postscript begin-making-icon-rendering
                  (number-of-rendering-structure-elements        ;  unsigned-integer
                    height-of-rendered-icon        ; unsigned-integer
                    width-of-rendered-icon        ; unsigned-integer
                    height-of-rendering-structure        ; unsigned-integer
                    width-of-rendering-structure        ; unsigned-integer
                    reflection-and-rotation-of-rendering        ; symbol
                    y-scale-of-rendering        ; unsigned-integer
                    x-scale-of-rendering        ; unsigned-integer
                    corresponding-icp-object-index        ; corresponding-icp-object-index
                    )
  )



;;; update-ring-raster-for-graph-given-color-values is a nop

(defun-for-postscript update-ring-raster-for-graph-given-color-values
                      (number-of-rasters-needed        ;  unsigned-integer
                        graph-rendering                ; graph-rendering
                        )
  ;; This is a NOP.  Since we don't need to allocate a ring raster
  )







;;;; Gensym Font Names And their Specifications



;;; `Design-gensym-postscript-encoding-vector' creates the encoding vector used
;;; in printing to map from character codes to adobe character names.  This
;;; encoding vector is based on the what adobe calls the ISO encoding vector, but
;;; it differs since G2 uses characters that are not in the ISO encoding vector.

;;; Adobe character names are placed into this encoding vector due to one of four
;;; senarios.  First all the "accent" characters are included.  For example "ring,"
;;; "umlaut," and "dotlessi".  This is critical since characters with accents will
;;; not print if the characters they are made from are not included in the encoding
;;; vector.  Second all the usual characters are are placed in the encoding vector,
;;; i.e. every thing from space thru tilde including the alphabet, numbers, etc.
;;; The third and four cases are characters that G2 encodes internally with a
;;; tilde escape.  For example "aring".  Some of these have ISO encodings and
;;; these are placed at their usual ISO encoding position.  Some do not have
;;; ISO encodings and these are placed unused slots in the encoding vector.

;; OBSOLETE!  We now just encode the whole vector.  It happens to be 1:1 with Latin1 and
;; ASCII, but has stuff below ASCII and between ASCII and Latin1. (MHD 9/10/96)
;; ;;; The tilde excaped characters that do not have an encoding are placed into the
;; ;;; encoding vector starting at #o221.  Care is taken to assure that #o220 is
;; ;;; given the definition ".notdef"

(defun-for-macro design-gensym-postscript-encoding-vector ()
  (let ((result (make-array-with-nils (1+ #o377))))
    ;; This does it as of around 9/10/96, new AB Latin fonts and encodings:  (MHD 9/10/96)
    (loop for i from 0 below 256
          as def = (or (map-ab-latin-font-code-to-adobe-name i) ".notdef")
          do (setf (svref result i) def))
    result
;    (loop with accent-characters
;            = '("ring"
;                "tilde"
;                "grave"
;                "circumflex"
;                "cedilla"
;                "dotlessi"
;                "dieresis"
;                "slash"
;                "acute"
;                "caron"
;                "umlaut")
;          with table-of-gensym-tilde-escape-characters
;            = (loop with table = (make-hash-table :test #'equal)
;                    for  (nil                        ; character-following-\~-in-gensym-character
;                           nil                        ; roman-font-special-character-code
;                           nil                        ; character-following-\~-in-lower-case-equivalent?
;                           nil                        ; equivalent-unaccented-character?
;                           nil                        ; character-or-characters-following-\~-for-input
;                           adobe-name) in special-character-alist
;                    ;; Changed to reflect the fact that adobe-name is now a
;                    ;; symbol, rather than a string. (MHD 2/10/94)
;                    do (setf (gethash (symbol-name adobe-name) table) t)
;                    finally (return table))
;          with characters-without-iso-encodings = ()
;          for (adobe-character-name nil iso-encoding)
;              in postscript-character-encodings
;          when (and iso-encoding
;                    (or (<= #o40 iso-encoding #o176)
;                        (member adobe-character-name accent-characters :test #'string=)))
;            do (setf (svref result iso-encoding) adobe-character-name)
;          when (gethash adobe-character-name table-of-gensym-tilde-escape-characters)
;            do (cond
;                 (iso-encoding
;                  (setf (svref result iso-encoding) adobe-character-name))
;                 (t
;                  (push adobe-character-name characters-without-iso-encodings)))
;          finally
;            (loop with what-to-put-in-empty-slot = ".notdef"
;                  for i from #o220 to #o377
;                  when (not (svref result i))
;                    do
;                    (setf (svref result i) what-to-put-in-empty-slot)
;                    (setf what-to-put-in-empty-slot (or (pop characters-without-iso-encodings)
;                                                        ".notdef")))
;            (when characters-without-iso-encodings
;              (warn "Unable to create the Gensym postscript font encoding vector."))
;            (return result))
    ))

;;; `Gensym-postscript-font-encoding-vector' holds, at compile time, the result
;;; of design-gensym-postscript-encoding-vector's efforts.  This data structure
;;; is then used to build chunks of two runtime data.  One of these is part of
;;; the postscript header, the other is used to convert tilde escaped characters
;;; into character codes relative to the encoding vector.  The second of these
;;; is done in the module printing, see the parameter
;;; postscript-encoding-for-tilde-escape-characters.

(defvar-for-macro gensym-postscript-font-encoding-vector
  (design-gensym-postscript-encoding-vector))

;;; `Define-g2-encoding' creates the component of the postscript header containing
;;; our encoding vector in the range #o0 thru #o337.

(defmacro define-g2-encoding ()
  `(defvar-for-postscript
     g2-encoding
     (postscript-array
       ,@(loop for i from #o0                ; previously #o220
                     to #o377
               as adobe-character-name = (svref gensym-postscript-font-encoding-vector i)
               collect `(ps-quote ,adobe-character-name)))))

(define-g2-encoding)


;;; Here is where we will also redefine the Metrics entry for our char widths.
;;; Note that some postscript implmentations already have a /Metrics dictionary
;;; and some don't.  So, create or copy as required. -fmw 28May93

(defun-for-postscript reencode-font (new-font-name base-font-name metrics)
  (let* ((base-font-dictionary (findfont base-font-name))
         (new-font-dictionary (dict (add 1 (maxlength base-font-dictionary))))
         (new-encoding (array 256))        ; Encoding vectors are always of length 256.
         (new-metrics (dict 256)))
    (ps-verbatim
     ;; This code is almost raw postscript, so do not let the lispm format it.
     ;; Some things are hard to translate into the pseudo-lisp postscript.
     ;; In this case the obvious translation just doesn't work on my postscript
     ;; implementation, so I have fallen back on nearly the exact text given in the
     ;; cookbook. (Red Book, page 98)
     base-font-dictionary
       {1 index (ps-quote "FID") eq
        2 index (ps-quote "UniqueID") eq
        or
         {pop pop}
         {new-font-dictionary 3 1 roll put }
         ifelse
         } forall)

    (put new-font-dictionary (ps-quote "FontName") new-font-name)

;; Do not provide a UniqueID because we don't have one.
;;    (put new-font-dictionary (ps-quote "UniqueID") unique-id)

    ;; Fill in new encodings, [previously only from character #o220 onwards.]
    (pop (copy (get base-font-dictionary (ps-quote "Encoding")) new-encoding))
    (putinterval new-encoding #o0 ; previously #o220
                 g2-encoding)
    (put new-font-dictionary (ps-quote "Encoding") new-encoding)

    ;; Fill in new character widths.
    ;; Should we skip .notdef, or just lob garbage there?
    (put new-font-dictionary (ps-quote "Metrics") new-metrics)
    (for (i 0 1 255)
         (put new-metrics
              (get new-encoding i)
              (get metrics i)))

    (pop (definefont new-font-name new-font-dictionary))))


;(top-level-progn-for-postscript set-up-g2-fonts (reencode-font 'g2-helvetica (ps-quote "Helvetica")))


(defun-for-postscript define-g2-font (name size metrics base-font)
  (reencode-font name base-font metrics)
  (def name (scalefont (findfont name) size)))

;;; Define a G2 font derived from Helvetica.
(defun-for-postscript define-helvetica-font (name size metrics)
  (define-g2-font name size metrics (ps-quote "Helvetica")))

(defun-for-postscript define-blob-font (name size)
  (def name (scalefont (findfont 'blob-font) size)))

(defun-for-postscript define-unknown-font (name size)
  (def name (scalefont (findfont (ps-quote "Courier-BoldOblique")) size)))







;;;; Color Handling




;;; When G2 Prints it establishs a color map where in the color
;;; values are synchronized with this printing header.

;;; Color differences are converted to absolute color values
;;; on the G2 side of the wire.  If that conversion is wrong
;;; then the print out is wrong.  Getting that conversion
;;; right is hard.

(defvar-for-postscript bw-color-map
    (postscript-array
      (postscript-array 255 255 255) ; White
      (postscript-array 0 0 0)))   ; Black


;;; The defun-for-postscript `set-appropriate-color' sets the current drawing
;;; color from number in the variable "color-value", which should be an index
;;; into the current-color-map.  If the color index is out of range, we set it
;;; to 50% gray.

(defun-for-postscript set-appropriate-color ()
  (cond ((lt color-value 0)                                    ; Was transparent
         (setgray 0.5))
        ((ge color-value (length current-color-map))
         (setgray 0.5))
        (true
         (multiple-value-bind (_r _g _b array)
             (aload (get current-color-map color-value))
           (setrgbcolor _r _g _b)))))

;; The only place where this might be called with color-value equal to the
;; transparent color value (-1), is from add-from-icon-rendering.  Since
;; transparent layers are not drawn at all, it doesn't really matter what
;; color we choose here.


(defun-for-postscript set-up-color-map ()
  (setq current-color-map
        (cond ((eq 'black-and-white global-color-conversion)
               bw-color-map)
              ((eq 'grays global-color-conversion)
               gray-color-map)
              (true
               full-color-map)))
  (forall (_x1 current-color-map)
          (put _x1 0 (div (get _x1 0) 255))
          (put _x1 1 (div (get _x1 1) 255))
          (put _x1 2 (div (get _x1 2) 255))))





;;;; Painting Into Rasters, and Raster Handling




;;; The defun-for-postscript `fetch-from-color-list' grabs the color for the
;;; INDEX-th region of an icon, from the global postscript variable
;;; list-of-color-differences, which at this point is a postscript array.
;;; Referenced by `postscript-emit-color-value'.

(defun-for-postscript fetch-from-color-list (index)
  (cond ((lt index 0)
         color-value)
        ((ge index (length list-of-color-differences))
         color-value)
        (true
         (get list-of-color-differences index))))

;; This code has been bullet-proofed against disagreements between what
;; printing thinks is a polychrome icon (and hence gets a non-empty list of
;; color diffs) and what drawing thinks is a polychrome icon.  The code which
;; makes these decisions (mostly in postscript-emit-line-drawing and
;; paint-one-bitmap-for-icon-on-scratchpad-raster) is too horrendous for me to
;; tease out the real cause of this bug.



(defun-for-postscript paint-line-in-current-scratchpad-raster
    (_x1 _y1 _x2 _y2 color-value _last-pt?)
  (unless-transparent
    (set-appropriate-color)

    ;; This fixes one aspect of the off-by-one bug in printing.
    (adjust-coordinates-by-one-half _x1 _y1 _x2 _y2)

    (moveto _x1 _y1)
    (lineto _x2 _y2)
    (stroke)))

;; Postscript STROKE draws lines centered on the given coordinates, with +-1/2
;; linewidth of ink to each side.  G2, however, assumes all of the ink lies
;; below and to the left of the line.  We can compensate here, at least for
;; horizontal and vertical lines by adding 0.5 to the y and x coordinates,
;; respectively.  See also paint-wide-line-in-current-scratchpad-raster, below.



(defun-for-postscript paint-solid-rectangle-in-current-scratchpad-raster
    (_left _top _right _bottom color-value)
  (unless-transparent
    (set-appropriate-color)
    (newpath)
    (moveto _left _top)
    (lineto _right _top)
    (lineto _right _bottom)
    (lineto _left _bottom)
    (lineto _left _top)
    (fill)))

;; Postscript FILL agrees with G2 drawing.



(defun-for-postscript paint-from-line-of-text-to-current-scratchpad-raster
    (clipped-left-edge                ; coordinate
      clipped-top-edge                ; coordinate
      clipped-right-edge                ; coordinate
      clipped-bottom-edge                ; coordinate
      text-line                        ; text-line
      nword-spacing                ; word-spacing
      font-map                        ; font-map
      color-value                        ; color-value
      x-scale                        ; x-scale
      y-scale                        ; y-scale
      left-edge-of-line-of-text-in-window        ; coordinate
      baseline-in-window)                ; coordinate
  (unless-transparent
    (set-appropriate-color)
    (gsave)
    (translate clipped-left-edge baseline-in-window)
    (moveto 0 0)
    (scale 1.0 -1.0)
    (set-appropriate-font)
    (show-with-wordspacing text-line)
    (grestore)))


(defun-for-postscript kanji-paint-from-line-of-text-to-current-scratchpad-raster
    (clipped-left-edge                ; coordinate
      clipped-top-edge                ; coordinate
      clipped-right-edge                ; coordinate
      clipped-bottom-edge                ; coordinate
      text-line                        ; text-line
      nword-spacing                ; word-spacing
      font-map                        ; font-map
      color-value                        ; color-value
      x-scale                        ; x-scale
      y-scale                        ; y-scale
      left-edge-of-line-of-text-in-window        ; coordinate
      baseline-in-window)                ; coordinate
  (unless-transparent
    (set-appropriate-color)
    (gsave)
    (translate clipped-left-edge baseline-in-window)
    (moveto 0 0)
    (scale 1.0 -1.0)
    (set-appropriate-font)
    (set-corresponding-kanji-font (get font-map 0))
    (kanji-show text-line)
    (grestore)))



;;; `paint-filled-triangle-in-current-scratchpad-raster' ...
;;; <pt-1> <pt-2> <pt-3> <color-value>
;;;    paint-filled-triangle-in-current-scratchpad-raster -

(defun-for-postscript paint-filled-triangle-in-current-scratchpad-raster
    (_x1 _y1 _x2 _y2 _x3 _y3 color-value)
  (unless-transparent
    (set-appropriate-color)
    (newpath)
    (moveto _x1 _y1)
    (lineto _x2 _y2)
    (lineto _x3 _y3)
    (fill)))


;;; `paint-filled-polygon-in-current-scratchpad-raster' ...
;;;
;;;    paint-filled-polygon-in-current-scratchpad-raster -


(defun-for-postscript paint-filled-polygon-in-current-scratchpad-raster
    (unsigned-polygon-point-list color-value)
  ;; The reason this empty implementation is OK is that it is never called --
  ;; the drawing code detects a printing window and decomposes the polygon into
  ;; triangles first. Of course, we will "fix soon" -fmw, 2/7/02

   ;;pbk to fix soon
   ;;(unless-transparent
   ;; (set-appropriate-color)
   ;; (newpath)
   ;; (moveto (car unsigned-polygon-point-list)
   ;;            (cadr unsigned-polygon-point-list))
   ;;   (loop for (x y) on (cddr unsigned-polygon-point-list) by 'cddr
   ;;          do
   ;;     (lineto x y))
   ;;  (fill))
  )



(defun-for-postscript paint-point-in-current-scratchpad-raster
    (_x1 _y1 color-value)
  (unless-transparent
    (set-appropriate-color)
    (newpath)
    (moveto _x1 _y1)
    (rlineto  0 1)
    (rlineto  1 0)
    (rlineto 0 -1)
    (fill)))



(defun-for-postscript paint-wide-line-in-current-scratchpad-raster
    (_x1                        ; coordinate
      _y1                        ; coordinate
      _x2                        ; coordinate
      _y2                        ; coordinate
      color-value                ;  color-value
      paint-last-point?                                            ;  boolean
      line-width)                ;  unsigned-integer
  (unless-transparent
    (set-appropriate-color)
    (newpath)

    ;; This fixes one aspect of the off-by-one bug in printing.
    (adjust-coordinates-by-one-half _x1 _y1 _x2 _y2)

    (moveto _x1 _y1)
    (lineto _x2 _y2)
    (setlinewidth line-width)
    (stroke)
  (setlinewidth 1)))



;;; `atan-2' takes two points.  Assuming that the first point is
;;; the origin it returns the angle from that origin to the second
;;; point.  It does this in the TV coordinate system that G2 uses.

(defun-for-postscript atan-2 (_atan-2-x1 _atan-2-y1 _atan-2-x2 _atan-2-y2)
  (atan (sub _atan-2-y2 _atan-2-y1)
        (sub _atan-2-x2 _atan-2-x1)))



;;; paint-arc-or-circle-in-current-scratchpad-raster

;;; pt1 pt2 pt3 scale color circle? filled?
;;;     paint-arc-or-circle-in-current-scratchpad-raster -

(defun-for-postscript paint-arc-or-circle-in-current-scratchpad-raster
    (_x1 _y1 _x2 _y2 _x3 _y3 _x-scale _y-scale color-value _circle? _filled?)
  (unless-transparent
    (set-appropriate-color)
    (setq _filled? (eq 1 _filled?))
    (setq _circle? (eq 1 _circle?))

    (setq _a1 (sub _x2 _x1))
    (setq _b1 (sub _y2 _y1))
    (setq _a2 (sub _x3 _x2))
    (setq _b2 (sub _y3 _y2))

    (setq _c1
          (div (sub (add (mul _x2 _x2)
                         (mul _y2 _y2))
                    (add (mul _x1 _x1)
                         (mul _y1 _y1)))
               2.0))
    (setq _c2
          (div (sub (add (mul _x3 _x3)
                         (mul _y3 _y3))
                    (add (mul _x2 _x2)
                         (mul _y2 _y2)))
               2.0))
    (setq _determinant
          (sub (mul _a1 _b2)
               (mul _a2 _b1)))
    (newpath)
    (moveto _x1 _y1)
    (cond
      ((eq 0 _determinant)
       (paint-line-in-current-scratchpad-raster
         _x1 _y1 _x3 _y3 color-value 1))
      (true
       (setq _x-center (div (sub (mul _c1 _b2)
                                 (mul _c2 _b1))
                            _determinant))
       (setq _y-center (div (sub (mul _a1 _c2)
                                 (mul _a2 _c1))
                            _determinant))
       (setq _d1 (sub _x1 _x-center))
       (setq _d2 (sub _y1 _y-center))
       (setq _radius (sqrt
                       (add (mul _d1 _d1)
                            (mul _d2 _d2))))
       (setq _angle1 (atan-2 _x-center _y-center _x1 _y1))
       (setq _angle2
             (if _circle?
                 (add 360 _angle1)
                 (atan-2 _x-center _y-center _x3 _y3)))
       (if (lt _determinant 0)
           (arcn _x-center _y-center _radius
                 (if _circle? _angle2 _angle1)
                 (if _circle? _angle1 _angle2))
           (arc  _x-center _y-center _radius _angle1 _angle2))
       (if _circle? (closepath))
       (if _filled? (fill) (stroke))))))



;;; set-icon-scale-and-rotation  ...

(defun-for-postscript set-icon-scale-and-rotation
                      (_width _height _x-scale _y-scale _reflection _clockwise-rotation)
  (let ((_dx (div _width 2))
        (_dy (div _height 2)))
    (scale (div _x-scale 4096)
           (div _y-scale 4096))
    (transform _dx _dy (rotate _clockwise-rotation (matrix)))
    (translate (abs (exch)) (abs (exch)))
    (if (eq 1 _reflection) (scale -1 1))
    (rotate _clockwise-rotation)
    (translate (neg _dx) (neg _dy))))

;; The (abs (exch)), besides manipulating the two outputs that transform left on the stack,
;; here is because G2 sends the top left corner of the icon in  window coordinates, not the
;; origin from which the icon description strokes out it's illustration.


;;;; Painting Into The Window


;;; paint-solid-rectangle-in-current-window

;;; <rectangle> <color-value> paint-solid-rectangle-in-current-window -

(defun-for-postscript paint-solid-rectangle-in-current-window
    (_left _top _right _bottom color-value)
  (unless-transparent
    (set-appropriate-color)
    (newpath)
    (moveto _left _top)
    (lineto _right _top)
    (lineto _right _bottom)
    (lineto _left _bottom)
    (lineto _left _top)
  (fill)))




;;; The defun-for-postscript `paint-image-in-current-window' runs the IMAGE
;;; operator, assuming all of its arguments are on the stack:
;;; width height bits/sample matrix proc.  It draws the image at x,y,
;;; clipping to the given rectangle.  The image data must follow this call.

(defun-for-postscript paint-image-in-current-window
    (_x                                                            ; coordinate
      _y
      clipped-left-edge
      clipped-top-edge
      clipped-right-edge
      clipped-bottom-edge
      x-scale                                                    ; WS scaling, as fixnums * 4096.
      y-scale)
  (gsave)
  (savectm)
  (clip-to-rectangle clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge)
  (scale (div x-scale 4096) (div y-scale 4096))
  (translate _x _y)
  (image)
  ;; Image data goes here!
  (restorectm)
  (grestore))

;; See set-icon-scale-and-rotation, above.



;;; The defun-for-postscript `paint-image-in-current-scratchpad-raster' always
;;; paints the image in whatever the current color is.

(defun-for-postscript paint-image-in-current-scratchpad-raster
    (x-in-icon y-in-icon
               icon-width icon-height
               _image-width _image-height                    ; Don't clobber the globals
               x-scale y-scale
               color-value                                    ; Don't use color-value. It's always zero here.
               image-data)
  (unless-transparent
    (gsave)
    (set-appropriate-color)
    (clip-to-rectangle 0 0 icon-width icon-height)
    (translate x-in-icon y-in-icon)
    (scale (mul _image-width (div x-scale 4096)) (mul _image-height (div y-scale 4096)))

    (ps-verbatim
      _image-width
      _image-height
      true
      (ps-token "[") _image-width 0 0 _image-height 0 0 (ps-token "]")
      image-data
      imagemask)
    (grestore)))






;;;; Adding Operators.




(defun-for-postscript add-from-icon-rendering-to-current-window
    (clipped-left-edge                   ; coordinate
      clipped-top-edge                   ; coordinate
      clipped-right-edge           ; coordinate
      clipped-bottom-edge           ; coordinate
      color-value                   ; Usually a color-difference, here is a value.
                                   ; See our printing-handler.
      icon-rendering
      left-edge-in-icon-rendering  ; coordinate
      top-edge-in-icon-rendering   ; coordinate
      list-of-color-differences)   ; A list of color values, one per icon layer.
  (gsave)
  ;; Note A.
  (set-appropriate-color)
  (savectm)
  (clip-to-rectangle clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge)
  (translate (sub clipped-left-edge left-edge-in-icon-rendering)
             (sub clipped-top-edge top-edge-in-icon-rendering))
  (exec (cvx icon-rendering))
  (restorectm)
  (grestore))

;; Note A: color-value might be transparent here (-1).  We can't skip the
;; rendering entirely, however, since transparency must be checked per-layer.
;; However, if color-value is transparent, then it doesn't matter what color we
;; set here, so I could skip the call to set-appropriate-color entirely, which
;; is what all the other callers do (using unless-transparent).  For safety, I
;; bullet-proofed set-appropriate-color instead. -fmw, 11/8/94


(defun-for-postscript add-from-graph-rendering-to-current-window
                      ( clipped-left-edge
                        clipped-top-edge
                        clipped-right-edge
                        clipped-bottom-edge
                        grid-background-color-value
                        graph-rendering
                        left-edge-in-graph-rendering
                        top-edge-in-graph-rendering
                        color-value
                        color-values-for-rasters?)
  (gsave)
  (clip-to-rectangle
    clipped-left-edge
    clipped-top-edge
    clipped-right-edge
    clipped-bottom-edge)
  (translate (sub clipped-left-edge left-edge-in-graph-rendering)
             (sub clipped-top-edge  top-edge-in-graph-rendering))
  (exec (cvx graph-rendering))
  (grestore))


(defvar-for-postscript graph-erase-dateline 0)

(defun-for-postscript update-graph-dateline
         (dateline            ; i.e. a coordinate
          graph-erase-dateline      ; i.e. a coordinate
          ;; graph-rendering     ; i.e. a graph-rendering
            )
  (translate (neg graph-erase-dateline) 0))

(defun-for-postscript cleanup-after-graph-rendering ()
  (translate graph-erase-dateline 0))



(defun-for-postscript add-solid-rectangle-to-current-window
    (_left _top _right _bottom color-value)
  (unless-transparent
    (set-appropriate-color)
    (newpath)
    (moveto _left  _top)
    (lineto _right _top)
    (lineto _right _bottom)
    (lineto _left _bottom)
    (lineto _left _top)
    (fill)))

;; subtract-instead is not provided as an argument since is will always be 0 when printing.



(defun-for-postscript add-from-line-of-text-to-current-window
    ( _left
       _top
       _right
       _bottom
       text-line
       nword-spacing
       font-map
       color-value
       x-scale
       y-scale
       left-edge-of-line-of-text-in-window
       baseline-in-window)
  (unless-transparent
    (set-appropriate-color)
    (gsave)
    (translate left-edge-of-line-of-text-in-window baseline-in-window)
    (moveto 0 0)
    (scale x-scale y-scale)
    (set-appropriate-font)
    (show-with-wordspacing text-line)
  (grestore)))



(defun-for-postscript kanji-add-from-line-of-text-to-current-window
    ( _left
       _top
       _right
       _bottom
       text-line
       nword-spacing
       font-map
       color-value
       x-scale
       y-scale
       left-edge-of-line-of-text-in-window
       baseline-in-window)
  (unless-transparent
    (set-appropriate-color)
    (gsave)
    (translate left-edge-of-line-of-text-in-window baseline-in-window)
    (moveto 0 0)
    (scale x-scale y-scale)
    (set-appropriate-font)
    (set-corresponding-kanji-font  (get font-map 0))
  (kanji-show text-line)
  (grestore)))




(defun-for-postscript add-upward-sloping-line-to-current-window
    (color-value left-end-x right-end-y right-end-x left-end-y)
  (unless-transparent
    (set-appropriate-color)
    (moveto left-end-x left-end-y)
    (lineto right-end-x right-end-y)
    (stroke)))




(defun-for-postscript add-downward-sloping-line-to-current-window
    (color-value right-end-x right-end-y left-end-x left-end-y)
  (unless-transparent
    (set-appropriate-color)
    (moveto left-end-x left-end-y)
    (lineto right-end-x right-end-y)
    (stroke)))



(defun-for-postscript add-wide-polyline-to-current-window
    (color-value line-width line-cap line-join dashes vertices)
  (unless-transparent
    (gsave)
    (for (i 0 2 (sub (length vertices) 1))
         ;; Need to do this somehow:
         ;;  (adjust-coordinates-by-one-half _x1 _y1 _x2 _y2)
         (if (eq i 0)
             (moveto (get vertices i) (get vertices (add i 1)))
             (lineto (get vertices i) (get vertices (add i 1)))))
    (set-appropriate-color)
    (setlinewidth line-width)
    (setlinecap line-cap)
    (setlinejoin line-join)
    (setdash dashes 0)
    (stroke)
    (grestore)))

(defun-for-postscript add-polygon-to-current-window
    (color-value line-width fill-color fill-pattern vertices)
  (unless-transparent
    (gsave)
    (for (i 0 2 (sub (length vertices) 1))
         ;; Need to do this somehow:
         ;;  (adjust-coordinates-by-one-half _x1 _y1 _x2 _y2)
         (if (eq i 0)
             (moveto (get vertices i) (get vertices (add i 1)))
             (lineto (get vertices i) (get vertices (add i 1)))))
    (set-appropriate-color)
    (setlinewidth line-width)
    ;; FIXME FIXME: fill-color fill-pattern
    (stroke)
    (grestore)))

;; FIXME FIXME
(defun-for-postscript add-ellipse-to-current-window
    (color-value line-width fill-color fill-pattern x1 y1 x2 y2)
  (unless-transparent
    (gsave)
    (set-appropriate-color)
    (setlinewidth line-width)
    (stroke)
    (grestore)))


;;;; Knowledge Of The Page Layout


;;; A Large number of globals are used to guide the overall
;;; page layout.
;;; I ought to be able to get this info from the print driver
;;; while spooling, but not yet.


;;; The user requests, for all the pages in his job,
;;; some things which we store into globals
;;;    global-paper-size  (member letter legal a0..a5 b0...b5)
;;;    global-paper-orientation (member portrait landscape)
;;;    global-left-margin    postscript-units
;;;    global-top-margin     postscript-units
;;;    global-right-margin   postscript-units
;;;    global-bottom-margin  postscript-units

;;; In addition the user tells us how to scale workspace
;;; units into printer units.
;;;    workspace-units-per-postscript-unit

;;; Once we know what kind of paper we have we can
;;; know how big it is.
;;;    paper-height   postscript-units
;;;    paper-width    postscript-units

;;; Of course the printer usually can't get ink on all
;;; of that area so we eat some "hardware defined" margins
;;;    paper-right-margin   postscript-units
;;;    paper-top-margin     postscript-units
;;;    paper-left-margin    postscript-units
;;;    paper-bottom-margin  postscript-units


;;; We compute some actual margins by taking the
;;; maximum of the user's request and what
;;; the hardware lets us print on.
;;;   real-right-margin   postscript-units
;;;   real-top-margin     postscript-units
;;;   real-left-margin    postscript-units
;;;   real-bottom-margin  postscript-units

;;; That allows us to know the size of the area into which
;;; we will be spraying ink.
;;;    image-width    postscript-units
;;;    image-height   postscript-units

;;; Note: the above variables reflect the available space AFTER the page
;;; has been oriented for landscape vs portrait printing.  That is,
;;; if the orientation is landscape, then paper-bottom-margin is
;;; the space in the margin which was originally on the left side
;;; of the page.

(defun-for-postscript define-paper-1 (paper-width
                                     paper-height
                                     paper-left-margin
                                     paper-top-margin
                                     paper-right-margin
                                     paper-bottom-margin)
  )


;; This function appears to be doing nothing, but it's not:
;; it SETQ's (in postscript) the global variables named by its arguments.



;;; The function `define-paper' defines the virtual paper dimensions,
;;; accounting for the paper orientation.

(defun-for-postscript define-paper (global-paper-size
                                    global-paper-orientation
                                    paper-width-1
                                    paper-height-1
                                    paper-left-margin-1
                                    paper-top-margin-1
                                    paper-right-margin-1
                                    paper-bottom-margin-1)

  (if (eq 'portrait global-paper-orientation)
      (define-paper-1
        paper-width-1
        paper-height-1
        paper-left-margin-1
        paper-top-margin-1
        paper-right-margin-1
        paper-bottom-margin-1)
      (define-paper-1
        paper-height-1
        paper-width-1
        paper-top-margin-1
        paper-right-margin-1
        paper-bottom-margin-1
        paper-left-margin-1)))

;; i.e. Rotate the page shape if we aren't in Portrait.



;;; global-layout sets up the color conversions and the CTM for page orientation.

(defun-for-postscript global-layout (postscript-units-per-workspace-unit
                                     global-left-margin        ; As supplied by use in printer setup.
                                     global-top-margin
                                     global-right-margin
                                     global-bottom-margin
                                     global-color-conversion)

  ;; Setup the color map
  (set-up-color-map)

  ;; Compute margins that work on this paper
  (setq real-right-margin
        (max global-right-margin paper-right-margin))
  (setq real-top-margin
        (max global-top-margin paper-top-margin))
  (setq real-left-margin
        (max global-left-margin paper-left-margin))
  (setq real-bottom-margin
        (max global-bottom-margin paper-bottom-margin))
  ;; Compute the image area info for set-up-ctm
  (setq image-height (sub paper-height
                          (add real-top-margin
                               real-bottom-margin)))
  (setq image-width (sub paper-width
                         (add real-right-margin
                              real-left-margin))))



;;; `set-up-page' accounts for page rotation in landscape mode.
;;; The CTM is setup for postscripts on a virtual page.

(defun-for-postscript set-up-page ()
  ;; Rotate page if we are in landscape mode.
  (when (eq 'landscape global-paper-orientation)
    ;; The virtual paper-width.  In landscape, this was the physical paper height.
    (translate 0 paper-width)
    (rotate -90)))



;;; `set-up-ctm' sets the transform matrix for this page.  It sets it so that
;;; the given rectangle, in window? coordinates, will fill the postscript page.

(defun-for-postscript set-up-ctm (_tile-left _tile-top _tile-width _tile-height)
  (translate real-left-margin real-bottom-margin)
  (translate 0.0 image-height)
  (scale postscript-units-per-workspace-unit (neg postscript-units-per-workspace-unit))
  (clip-to-rectangle 0 0 _tile-width _tile-height))

;; The Page orientation has already been accounted for here.


;;; `draw-multipage-legend' draws a little ROWS by COLUMNS array of boxes
;;; in the margins, and fills the box numbered PAGE.

(defun-for-postscript draw-multipage-legend (rows columns page)
  (let* ((extra-space 5)
         (yspace (div (sub (sub real-bottom-margin paper-bottom-margin) extra-space) rows))
         (yscale (min yspace (div 72 4)))
         (xscale (mul yscale (div paper-width paper-height)))
         (i 1))
    ;; Legend vanishes if a pagelet is less than 0.01 inch tall
    (when (gt yscale (inch 0.01))
      (gsave)
      (translate (add paper-left-margin (div extra-space 2))
                 (add paper-bottom-margin (div extra-space 2)))
      (scale xscale yscale)
      (setlinewidth 0)
      (for (y (sub rows 1) -1 0)
           (for (x 0 1 (sub columns 1))
                (newpath)
                (moveto x y)
                (rlineto 1 0)
                (rlineto 0 1)
                (rlineto -1 0)
                (closepath)
                (when (eq i page)
                  (gsave) (setgray 0.75) (fill) (grestore))
                (stroke)
                (setq i (add 1 i))))
      (grestore))))

;; Since the imageable area for a given printer may vary,
;; don't draw the marker right up against the paper margins.




;;;; Some debug routines



#+development
(defun-for-postscript draw-box (left bottom width height)
  (gsave)
  (clip-to-rectangle -1000 -1000 2000 2000)
  (setlinewidth 0)
  (newpath)
  (moveto left bottom)
  (rlineto width 0)
  (rlineto 0 height)
  (rlineto (neg width) 0)
  (closepath)
  (stroke)
  (grestore))


;;; The function `outline-margins' outlines the drawing area while in the scope
;;; of set-up-ctm.

#+development
(defun-for-postscript outline-margins ()
  (setrgbcolor 1 0 0)
  (draw-box _tile-left _tile-top _tile-width _tile-height))



#+development
(defun-for-postscript outline-page-margins ()
  (setrgbcolor 0 1 0)
  (draw-box paper-left-margin paper-bottom-margin
            (sub (sub paper-width paper-left-margin) paper-right-margin)
            (sub (sub paper-height paper-top-margin) paper-bottom-margin)))

;; This must be called outside the scope of set-up-ctm.








;;;; Postscript Error Handling



;; Men at Work: This code is enabled only when :ab-ps-error-handler is stuffed
;; into *features* by hand. - ben 11/27/91


;; `eh-error-names' is bound to an array of all the known error names, we rebind the
;; definitions of these in the errdict.

#+ab-ps-error-handler
(defvar-for-postscript eh-error-names
  (postscript-array
    ;; configurationerror dictfull dictstackoverflow dictstackunderflow execstackunderflow
    ;; invalidaccess invalidcontext invalidexit
    'undefined
    ))

;;; This code is derived from an error handler provided by Adobe on the
;;; developer tools disk.  That disk is distributed to all Adobe Developers.

;;; A postscript error handler is installed by replacing the binding for
;;; handleerror in the errordict, which we do with ab-dict's handle-error-for-ab
;;; (see that routine for a discussion of our response to an error).
;;; The rebinding is done by eh-initialize

#+ab-ps-error-handler
(defun-for-postscript eh-initialize ()
  (setq eh-cp 0)
  (setq eh-lmargin 72)
  (setq eh-rmargin 72)
  (setq eh-courier (scalefont (findfont (ps-quote "Courier")) 10))
  (setq eh-old-handle-error (get errordict 'handleerror))
  (setq eh-string-pad (string 100))
  (setq eh-original-error-handlers (dict (add 10 (length eh-error-names))))
  (forall (error-name eh-error-names)
          (put eh-original-error-handlers error-name
               (get errordict error-name))
          (put errordict error-name
               (get ab-dict error-name)))
  ;; (store 'handleerror errordict (get ab-dict 'handle-error-for-ab))
  )



;;; Much of the code in this section exists to print postscript objects.
;;; Two things make this code odd.  First to print an object of type
;;; foo we call the routine foo in the ab-dict.  Secondly there
;;; is an ugly number of printing routines each with a slight variation
;;; on how it prints.  These are enumerated below.
;;;   eh-nl                  -- moves the printing cursor to the left margin, and down one line.
;;;   eh-print <obj>      -- prints black on white the <obj> converted to a string
;;;   eh-cvs-print <obj>      -- converts <obj> to string and prints it followed by space
;;;   eh-tprint <obj>        -- eh-nl if necessary and the err-print
;;;   eh printer for type    -- these call eh-cvs-print and or eh-tprint
;;;   eh-type-print          -- dispatch to printer for type
;;;   eh-== <obj>            -- eh-nl, eh-cp<-0, and eh-type-print

#+ab-ps-error-handler
(defun-for-postscript eh-nl ()
  (setq eh-cp 0)
  (multiple-value-bind (x y) (currentpoint)
    (moveto eh-lmargin y)
    (rmoveto 0 -10)))

#+ab-ps-error-handler
(defun-for-postscript eh-print (object)
  (if (ne 'stringtype (type object))
      (setq object (cvs eh-string-pad object)))
  (let ((tx (mul 6 (length object)))
        (ty 10))
    (multiple-value-bind (tox toy) (currentpoint)
      (setgray 1)
      (newpath)
      (moveto tox (sub toy 2))
      (rlineto 0 ty)
      (rlineto tx 0)
      (rlineto 0 (neg ty))
      (closepath)
      (fill)
      (moveto tox toy)
      (setgray 0)
      (show object))))

#+ab-ps-error-handler
(defun-for-postscript eh-tprint (_string)
  (if (gt (add eh-cp (length _string)) eh-rmargin)
      (eh-nl))
  (setq eh-cp (add eh-cp (length _string)))
  (eh-print object))

#+ab-ps-error-handler
(defun-for-postscript eh-cvs-print (object)
  (eh-tprint (cvs eh-string-pad object))
  (eh-tprint " "))

#+ab-ps-error-handler
(defun-for-postscript unknowntype (type)
  (eh-tprint "?unknowntype?")
  (eh-cvs-print (cvlit type)))

#+ab-ps-error-handler
(defun-for-postscript eh-type-print (object)
  (let ((object-type (type object)))
    (if (known currentdict object-type)
        (exec object-type object)
        (unknowntype object-type))))

#+ab-ps-error-handler
(defun-for-postscript eh-== (object)
  (eh-type-print object)
  (eh-nl))







;;; These are the printers for each type of object.  They are bound
;;; to each of the documented data types.

#+ab-ps-error-handler
(defun-for-postscript integertype  (object) (eh-cvs-print object))
#+ab-ps-error-handler
(defun-for-postscript realtype     (object) (eh-cvs-print object))
#+ab-ps-error-handler
(defun-for-postscript booleantype  (object) (eh-cvs-print object))
#+ab-ps-error-handler
(defun-for-postscript operatortype (object) (eh-tprint "//") (eh-cvs-print object))
#+ab-ps-error-handler
(defun-for-postscript marktype     (object) (eh-tprint "-mark- "))
#+ab-ps-error-handler
(defun-for-postscript dicttype     (object) (eh-tprint "-dictionary- "))
#+ab-ps-error-handler
(defun-for-postscript nulltype     (object) (eh-tprint "-null- "))
#+ab-ps-error-handler
(defun-for-postscript filetype     (object) (eh-tprint "-filestream- "))
#+ab-ps-error-handler
(defun-for-postscript savetype     (object) (eh-tprint "-savelevel- "))
#+ab-ps-error-handler
(defun-for-postscript fonttype     (object) (eh-tprint "-fontid- "))
#+ab-ps-error-handler
(defun-for-postscript nametype     (object)
  (if (not (xcheck object))
      (eh-tprint "/"))
  (eh-cvs-print object))

#+ab-ps-error-handler
(defun-for-postscript stringtype (object)
  (cond
    ((rcheck object)
     (eh-tprint "(")
     (eh-tprint object)
     (eh-tprint ")"))
    (true
     (eh-tprint "-string- "))))

#+ab-ps-error-handler
(defun-for-postscript eh-array-type-1 (object array-type-string)
  (if (rcheck object)
      (cond
        ((xcheck object)
         (eh-tprint "{")
         (forall (x object) (eh-type-print x))
         (eh-tprint "}"))
        (true
         (eh-tprint "[")
         (forall (x object) (eh-type-print x))
         (eh-tprint "]")))
      (eh-tprint array-type-string)))

#+ab-ps-error-handler
(defun-for-postscript arraytype (object)
  (eh-array-type-1 object "-array- "))

#+ab-ps-error-handler
(defun-for-postscript packedarraytype (object)
    (eh-array-type-1 object "-packedarray- "))


;;; `eh-report-error' is called by the routines we install on common errors in the
;;; error dictionary.

#+ab-ps-error-handler
(defun-for-postscript eh-report-error (error-name command-name operand-stack exec-stack)
  (initgraphics)
  (setfont eh-courier)
  (moveto eh-lmargin 720)
  (eh-print "An unexpected error occured while printing a Gensym G2 print job.")
  (eh-nl)
  (eh-print "Error: ")
  (eh-print error-name)
  (eh-print ", Offending Command: ")
  (eh-print command-name)
  (eh-nl)
  (eh-nl)
  (eh-print "Operand Stack:")
  (eh-nl)
  (eh-nl)
  (repeat (length (aload operand-stack))
          (eh-==))
  (showpage))

#+ab-ps-error-handler
(defun-for-postscript undefined (command)
  (print "Oh My Undefined!\n")
  (flush)
  (eh-report-error /undefined command (postscript-array 1 2 3) (postscript-array 3 4 5))
  (exec (get eh-original-error-handlers /undefined)))





;;; `Handle-error-for-ab' does the actual error handling.  It is
;;; installed as the binding for handleerror in the errordict.
;;; It generates a page of paper to report the error to the user,
;;; so we stand some chance of fixing the user's problem over the
;;; phone.

;;; There are two situations were we don't attempt to handle the error.  First we
;;; won't handle the error if we are already handling an error (we stuff a flag into
;;; the error dictionary to enable this).  Secondly we supress the error if it looks
;;; like a "spurious error report caused by a minor communications bug in the
;;; Appletalk implementation."

#+ab-ps-error-handler
(defun-for-postscript handle-error-for-ab ()
  (begin systemdict)
  (begin $error)
  (begin ab-dict)
  (if newerror
      (progn
        (store 'newerror 'false)
        (if (or (ne "ioerror" (get $error /errorname))
                (ne "exec" (get $error 'command)))
            ;; The above condition is to prevent spurious error reports caused by a minor
            ;; communication bug in the AppleTalk implementation.
            (progn
              (multiple-value-bind (level used maximum) (vmstatus)
                (if (ne 0 level) (grestoreall)))
              (initgraphics)
              (setfont eh-courier)
              (moveto eh-lmargin 720)
              (eh-print "ERROR: ")
              (eh-print errorname)
              (eh-nl)
              (eh-print "OFFENDING COMMAND: ")
              (eh-print (load /command))
              (if (known $error 'ostack)
                  (progn
                    (eh-nl)
                    (eh-nl)
                    (eh-print "STACK:")
                    (eh-nl)
                    (eh-nl)
                    (repeat (length (aload (get $error 'ostack)))
                            (eh-==))))
              (exec (get systemdict 'showpage))
              (store /newerror true)
              (load 'eh-old-handle-error)
              (end)
              (end)
              (end)
              (exec))
            (progn
              (end)
              (end)
              (end))))
      (progn
        (end)
        (end)
        (end))))

;; In the developer tools version of this the code takes extreme care to make
;; sure that this routine, prior to being made readonly and binding, has the
;; actual systemdict and error-handler slammed into it.  That presumably
;; protects it against having the evil code that errored changing the
;; defintions out from under it.







;;;; End of Postscript Header File.

(end-postscript-header)




;;;; Printing Parameter Needed to be loaded prior to PRINTING


;;; The encoding in postscript-paper-sizes is (name width height)

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter postscript-paper-sizes
  '((letter (8.5 inch) (11.0 inch))
    (legal  (8.5 inch) (14.0 inch))
    (ledger (11.0 inch) (17.0 inch))

    (a0 (841 mm) (1189 mm))                ; Inches: 33.11 by 46.81
    (a1 (594 mm) (841 mm))                ; Inches: 23.39 by 33.11
    (a2 (420 mm) (594 mm))                ; Inches: 16.54 by 23.39
    (a3 (297 mm) (420 mm))                ; Inches: 11.69 by 16.54
    (a4 (210 mm) (297 mm))                ; Inches: 8.26 by 11.69
    (a5 (148 mm) (210 mm))                ; Inches: 5.38 by 8.27

    (b0 (1000 mm) (1414 mm))
    (b1 (707 mm) (1000 mm))
    (b2 (500 mm) (707 mm))
    (b3 (353 mm) (500 mm))
    (b4 (250 mm) (353 mm))
    (b5 (176 mm) (250 mm))                ; 182 by 257?
    ;; C sizes? (the envelope, please)
    )))
;; Note that the grammar should track the choices here.


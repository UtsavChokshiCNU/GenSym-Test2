;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module FONTS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark David, Stephen DeVoy, and Lowell Hawkinson







;;;; Forward References in FONTS

;; Both of the following are only used in development, at present.  (MHD 10/20/92)

#+development
(declare-forward-reference c32r function)	; KB-SAVE3

(declare-forward-references			; TELEWINDOWS
  (telewindows-authorized-for-japanese-p function)
  (telewindows-authorized-for-korean-p function)
  (telewindows-authorized-for-chinese-p function))

(declare-forward-reference		; TELESTUBS
  command-line-arguments variable)

(declare-forward-references		; font-files
  (get-asian-font-file-name function)
  #+font-files
  (read-asian-font-file function))



;; Prepare contents for later translation to C for use in remote graphics processor!

;; Consider move this module to an earlier place in the load sequence, with scaling
;; still earlier, so that forward references from PANES are not required.





;;; Convert-list-to-simple-vector ...

(defun convert-list-to-simple-vector (list)
  (make-array (length list) :initial-contents list))

;; Generalizable utility.  Used at present only in in FONTS. Move elsewhere?
;; (MHD 5/3/89)









;;;; Ab Fonts



;;; An `ab font' completely describes a particular font, as used by the Gensym
;;; window system, including its size information and individual character
;;; descriptions.  An ab font is stored as the ab-font property of an `ab font
;;; name', a symbol.  Ab fonts are typically identified by their names, in
;;; formats and in "font maps" (see below).

;;; The ab-font-size slot holds the point-size of the ab font.  The
;;; ab-font-x-reso....

;;; It is a requirement for all AB fonts that digits all have the same set
;;; widths.  Code may assume this to be a fact about all fonts.
;;; Get-set-width-for-character may be used to determine the set width for a
;;; character in a given font.

;;; Ab-font-maximum-width and ab-font-maximum-height are the maximum width and
;;; height of the bounding boxes (see below) of all characters in the font...
;;; [??]

;;; It is a universal characteristic of fonts in general, and of Gensym's fonts
;;; in particular, that all digits (0, 1, 2, 3, 4, 5, 6, 7, 8, 9) are the same
;;; width.  This may be relied on for purposes of aligning numbers in columns.
;;; (However, note that the characters (-.,+$e), which often also want to be
;;; aligned with numbers in columns, generally don't share this property.)
;;;
;;; The function `font-digit-text-width' of a font or font name returns the
;;; width of the digits in that font as a text width.

;;; The ab-font-character-description-table slot contains, for a non-Kanji font,
;;; a non-kanji font vector of character descriptions or nils, or, for a Kanji
;;; font, a kanji font cache vector of gensym-cons plist buckets having Kanji
;;; codes as indicators and character descriptions as values.  The character
;;; description corresponding to character code 0 is a "blob" of width
;;; missing-character-set-width, to be used for characters missing from the
;;; font.

;;; The ab-font-cache-of-scaled-fonts slot contains either a gensym list of a
;;; single null element or a gensym list of "scaled fonts" (see below) for
;;; particular x and y scales.  In the latter case, the cdr consists of distinct
;;; scaled fonts ordered by decreasing x scale, and the car repeats one of them,
;;; usually the last one of the elements of the cdr that was accessed.

;;; AB fonts are global to the lisp environment, rather than specific to a
;;; particular process or KB.

;;; Here are the identifying slots of the ab-font structure.  This could be
;;; elaborated per the FIT, or Font Information Table, as documented in the
;;; Bitstream 4-in-1 Manual.  The first group affect the structures themselves,
;;; while the second group are descriptive, and the rest of the slots are
;;; parameters.
;;;
;;; ab-font-type
;;;    KANJI (very large number of characters) or ROMAN
;;; ab-font-format (raw character glyph storage format)
;;;    BITMAP (used for "kanji" bitmaps), RECTANGLE (used for Latin bitmaps),
;;;    SPEEDO, TRUETYPE, TYPE1, PCLEO (all four of these are outline formats)
;;; fixed-width-of-font?
;;;    nil or non-nil
;;;
;;; ab-font-name
;;;    HM14, HM18, HM24, HB72, KANJI16
;;; ab-font-style
;;;    NORMAL, ITALIC, SMALL-CAPS
;;; ab-font-weight
;;;    LIGHT, MEDIUM, BOLD, EXTRA-BOLD

(def-global-property-name ab-font)		; maps from font name to ab font

(def-structure (ab-font
		 (:reclaimer nil)
		 (:constructor
		   make-ab-font-structure
		   (ab-font-name
		     ab-font-type
		     ab-font-size
		     ab-font-baseline
		     ab-font-maximum-width
		     ab-font-maximum-height)))

  ;; new:
  ab-font-format				; see above
  ab-font-style
  ab-font-weight

  missing-character-set-width	 ; width at normalized scale, initialized by make-ab-font

  ab-font-baseline

  ab-font-size					; eliminate?
  ab-font-maximum-width				; eliminate?
  ab-font-maximum-height			; eliminate?

  ab-font-name
  
  (ab-font-character-description-table		; contains character descriptions, or
    (case ab-font-type				;   sometimes just character rectangle
      (kanji (make-kanji-font-cache-vector))	;   arrays; see below
      (t (make-non-kanji-font-vector))))
  (ab-font-cache-of-scaled-fonts		; a gensym list of scaled fonts -- see above
    (gensym-list nil))
  ab-font-type
  (number-of-characters-in-ab-font 0)		; for curiosity, not counting "blob" (code 0)



  ;; MHD's developing here!  Not finished!  (MHD 9/13/91)

  (fixed-width-of-font? nil)			; nil, or a width at normalized scale iff
						;   this is a fixed width font.  When non-nil,
						;   this must be used to determine the width
						;   of each character instead of the character
						;   description.  If both this slot and the
						;   next are non-nil, then only character
						;   rectangles are kept for each character
						;   in the ab-font-character-description-table.
						; NOTE: fixed-width-of-font?, if non-nil, is
						;   guaranteed to be the same as missing-
						;   character-set-width.
  (fixed-text-width-of-font? nil)		; same as above, but as a "text width"
  (fixed-bounding-box-of-font? nil)		; nil, or a a list of four elements:
						;     bounding-box-x-offset, bounding-box-y-offset
						;     bounding-box-width, bounding-box-height
						;   that gives the bounding box for each character
						;   in the font.  When non-nil, this must be used
						;   to determine the bounding box for each character
						;   instead of the character description. If both
						;   this slot and the above are non-nil, then only
						;   character rectangles are kept for each character
						;   in the ab-font-character-description-table.

  

  ;; SIZE
  ab-font-point-size
  ab-font-x-resolution
  ab-font-y-resolution

  ;; FONTBOUNDINGBOX
  ab-font-width-in-x
  ab-font-width-in-y
  ab-font-x-offset
  ab-font-y-offset)


;; Revising all of this to keep only bitmaps instead of character descriptions for
;; the font Kanji16, which has fixed set widths and fixed bounding boxes, would
;; save almost 200,000 bytes, I figure -- a bit of work, but probably worth doing
;; some time soon, especially if many other similar fonts are to be added!  
;; (MHD 4/29/91)
;; --- This was done for 3.0. (MHD '92)

;; Consider renaming the ab-font-character-description-table slot.  ("Table" is poor.)

;; Consider renaming the ab-font-size slot.

#+development
(def-development-printer print-ab-font (thing &optional (stream *standard-output*))
  (when (ab-font-p thing)
    (printing-random-object (thing stream)
      (format stream "AB-FONT ~a" (ab-font-name thing)))
    thing))

(defconser fonts)

(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant number-of-character-orientations 8)
)

;;; A `non-kanji font vector' is used in ab fonts to hold character
;;; descriptions.  A `scaled-font non-kanji font vector' is used in scaled fonts
;;; to hold character images.

(def-vector-pool non-kanji-font-vector #.(+ (largest-non-kanji-font-character-code) 1)
  :element-type t :initial-element nil)

;; Use aref-non-kanji-font-vector instead of svref for vectors of this type!

(def-vector-pool scaled-font-non-kanji-font-vector
    #.(+ (* number-of-character-orientations (largest-non-kanji-font-character-code)) 1)
    :element-type t :initial-element nil)



;;; A `kanji font cache vector' is used in ab fonts to hold
;;; gensym-cons plists of character descriptions.  A `scaled-font kanji font cache vector' is used in
;;; scaled fonts to hold gensym-cons plists of character
;;; gensym-cons plists of images. There is a sub-vector for
;;; each character orientation. To get a bucket, each
;;; sub-vector is hashed by its length.

(eval-when (:compile-toplevel :load-toplevel :execute)			; used in reader macro below
  (defconstant kanji-font-cache-sub-vector-length 
    137					; shorter is better because we're
					;   recycling buckets, want fewer
					; 307  ; old, 1988 - 1998
    ))

(eval-when (:compile-toplevel :load-toplevel :execute)			; used in reader macro below
  (defmacro kanji-font-cache-vector-length ()
    #.(* number-of-character-orientations kanji-font-cache-sub-vector-length))
)

(def-vector-pool kanji-font-cache-vector #.kanji-font-cache-sub-vector-length
  :element-type t :initial-element nil)

(def-vector-pool scaled-font-kanji-font-cache-vector #.(kanji-font-cache-vector-length)
  :element-type t :initial-element nil)

;; Use aref-kanji-font-cache-vector instead of svref for vectors of this type!

;; Consider not having a vector pool just for this, but instead using a vector pool whose
;; vectors are at least #.(kanji-font-cache-vector-length) in length.  In fact, consider
;; using the non-kanji-font-vector pool.









;;;; Corresponding Kanji Fonts and Kanji Character Parameters



;;; `Corresponding-kanji-font-name-and-magnification' is a global property of a font
;;; name, the value of which is of the form
;;;
;;;    (kanji-font-name . magnification?).

(def-global-property-name corresponding-kanji-font-name-and-magnification)



;;; `Get-corresponding-kanji-font-name-and-magnification' returns the kanji font name and
;;; magnification corresponding to font-name, if any, or else (kanji16 . nil) by default.

(defmacro get-corresponding-kanji-font-name-and-magnification (font-name)
  `(or (corresponding-kanji-font-name-and-magnification ,font-name)
       '(kanji16 . nil)))



;;; Non-default corresponding kanji font names and magnifications.

(setf (corresponding-kanji-font-name-and-magnification 'HM24)
      '(KANJI24 . nil))

(setf (corresponding-kanji-font-name-and-magnification 'HM18)
      '(KANJI16 . nil))


(setf (corresponding-kanji-font-name-and-magnification 'HM14)
      '(KANJI16 . #.(convert-to-magnification-at-compile-time .85)))	; .8?

(setf (corresponding-kanji-font-name-and-magnification 'HB72)
      '(KANJI16 . #.(convert-to-magnification-at-compile-time 4)))	; 3.5?



;;; `Kanji-character-margin' is the number of pixels of margin to add to each kanji
;;; character on both the left and right side.

(def-global-property-name kanji-character-margin)

(setf (kanji-character-margin 'KANJI16) 1)	; 2?

(setf (kanji-character-margin 'KANJI24) 2)	; 1?



;;; `Kanji-character-depression' is the number of pixels each kanji character is to
;;; be depressed below the baseline.

(def-global-property-name kanji-character-depression)

(setf (kanji-character-depression 'KANJI16) 2)	; ok?

(setf (kanji-character-depression 'KANJI24) 3)	; ok?





;;;; Corresponding Cyrillic Fonts and Cyrillic Character Parameters



;;; `Corresponding-cyrillic-font-name-and-magnification' is a global property of
;;; a font name, the value of which is of the form
;;;
;;;    (cyrillic-font-name . magnification?).

(def-global-property-name corresponding-cyrillic-font-name-and-magnification)



;;; `Get-corresponding-cyrillic-font-name-and-magnification' returns the cyrillic font name and
;;; magnification corresponding to font-name, if any, or else (slavic16 . nil) by default.

(defmacro get-corresponding-cyrillic-font-name-and-magnification (font-name)
  `(or (corresponding-cyrillic-font-name-and-magnification ,font-name)
       '(slavic16 . nil)))



;;; Non-default corresponding cyrillic font names and magnifications.

(setf (corresponding-cyrillic-font-name-and-magnification 'HM24)
      '(SLAVIC24 . nil))

(setf (corresponding-cyrillic-font-name-and-magnification 'HM18)
      '(SLAVIC18 . nil))


(setf (corresponding-cyrillic-font-name-and-magnification 'HM14)
      '(SLAVIC14 . nil))

(setf (corresponding-cyrillic-font-name-and-magnification 'HB72)
      '(SLAVIC72 . nil))

;; Generalize this later! -- by mapping from character code into a table of "code
;; pages"... (MHD/PGA 4/3/95)

;; Adapt printing facilities to know about this!! (MHD 4/3/95)



;;;; Corresponding Hebrew Fonts and Hebrew Character Parameters



;;; `Corresponding-hebrew-font-name-and-magnification' is a global property of
;;; a font name, the value of which is of the form
;;;
;;;    (hebrew-font-name . magnification?).

(def-global-property-name corresponding-hebrew-font-name-and-magnification)



;;; `Get-corresponding-hebrew-font-name-and-magnification' returns the hebrew font name and
;;; magnification corresponding to font-name, if any, or else (hebrew16 . nil) by default.

(defmacro get-corresponding-hebrew-font-name-and-magnification (font-name)
  `(or (corresponding-hebrew-font-name-and-magnification ,font-name)
       '(hebrew16 . nil)))



;;; Non-default corresponding hebrew font names and magnifications.

(setf (corresponding-hebrew-font-name-and-magnification 'HM24)
      '(HEBREW24 . nil))

(setf (corresponding-hebrew-font-name-and-magnification 'HM18)
      '(HEBREW18 . nil))


(setf (corresponding-hebrew-font-name-and-magnification 'HM14)
      '(HEBREW14 . nil))

(setf (corresponding-hebrew-font-name-and-magnification 'HB72)
      '(HEBREW72 . nil))





;;;; Corresponding Thai Fonts and Thai Character Parameters



;;; `Corresponding-thai-font-name-and-magnification' is a global property of
;;; a font name, the value of which is of the form
;;;
;;;    (thai-font-name . magnification?).

(def-global-property-name corresponding-thai-font-name-and-magnification)



;;; `Get-corresponding-thai-font-name-and-magnification' returns the thai font name and
;;; magnification corresponding to font-name, if any, or else (thai16 . nil) by default.

(defmacro get-corresponding-thai-font-name-and-magnification (font-name)
  `(or (corresponding-thai-font-name-and-magnification ,font-name)
       '(thai16 . nil)))



;;; Non-default corresponding thai font names and magnifications.

(setf (corresponding-thai-font-name-and-magnification 'HM24)
      '(THAI24 . nil))

(setf (corresponding-thai-font-name-and-magnification 'HM18)
      '(THAI18 . nil))


(setf (corresponding-thai-font-name-and-magnification 'HM14)
      '(THAI14 . nil))

(setf (corresponding-thai-font-name-and-magnification 'HB72)
      '(THAI72 . nil))









;;;; Unicode Combining Classes



;;; A `combining class' is a symbol (formed in some common-sense way)
;;; corresponding to one of the following classes (from Unicode's document
;;; ftp://ftp.unicode.org/Public/UNIDATA/README.TXT).  Classes also have a code,
;;; which is not used in FONTS, but is used for the Unicode character database
;;; and for documentation.
;;; 
;;; CANONICAL COMBINING CLASSES
;;; 
;;;   0: Spacing, enclosing, reordrant, and surrounding
;;;   1: Overlays and interior
;;;   6: Tibetan subjoined Letters
;;;   7: Nuktas
;;;   8: Hiragana/Katakana voiced marks
;;;   9: Viramas
;;;  10: Start of fixed position classes
;;; 199: End of fixed position classes
;;; 200: Below left attached
;;; 202: Below attached
;;; 204: Below right attached
;;; 208: Left attached (reordrant around single base character)
;;; 210: Right attached
;;; 212: Above left attached
;;; 214: Above attached
;;; 216: Above right attached
;;; 218: Below left
;;; 220: Below
;;; 222: Below right
;;; 224: Left (reordrant around single base character)
;;; 226: Right
;;; 228: Above left
;;; 230: Above
;;; 232: Above right
;;; 234: Double above

;;; The variable `supported-combining-classes' is a list of the symbols
;;; corresponding to supported combining classes.

(defvar supported-combining-classes '(above))

;;; Extremely limited support for `Unicode combining classes' is supplied. The
;;; only class supported in fact is ABOVE, meaning that a combining
;;; (non-spacing) mark is positioned centered and above its base character's
;;; glyph.  (This one class is most useful for European accents, the majority of
;;; which fall into this class.)

;;; The `combining class ABOVE' means that the character will be rendered with
;;; its bounding-box-x-offset relative to the center of the base character, and
;;; with its bounding-box-y-offset relative to the ascender (top) of the base
;;; character.  Note that such a character will have code 230 in the Unicode
;;; character database as the fourth field (field 3).  For example, notice 230
;;; in the entry for combining double-acute:
;;;
;;;   030B;COMBINING DOUBLE ACUTE ACCENT;Mn;230;L;;;;;N;NON-SPACING DOUBLE ACUTE;;;;





;;;; Character Descriptions



;;; A `character description' describes a character in an ab font.  The description is
;;; not scale-specific, as is the case with a "character image"; see below.  The
;;; design of character descriptions is based somewhat on PostScript's character
;;; coordinate system, as described in the PostScript reference manual.  The
;;; following borrows from that text.

;;; The `character coordinate system' for a character is a two-dimensional Euclidean
;;; coordinate system in which the units are pixels and x and y increase to the right
;;; and up, respectively, as they do in standard geometry.  (This differs from G2's
;;; and most computer graphics' coordinate systems, where x increases to the right,
;;; but y increases downward.  In fact, even character rectangles, used in G2 to
;;; describe character images, use a coordinate system where the origin is the top
;;; left corner and x and y increase to the right and down, respectively.)  The units
;;; of the character coordinate system are treated as normalized-scale workspace units.

;;; The `bounding box' of a character is the smallest rectangle that will just enclose
;;; the entire character.

;;; The `character left edge' of a character is a vertical line through the character
;;; that is to be treated as its left edge for purposes of normal (non-kerned)
;;; abutment with a character to its left.  It is typically close to, but may be to the
;;; left or right of, the left edge of the bounding box.  The `character right edge'
;;; of a character is similar.

;;; The `character origin', the origin of its character coordinate system, is located
;;; on the `character baseline' at the character left edge.

;;; The `character set width' of a character is the distance from the character
;;; origin to the point on the baseline at the character right edge.

;;; The `bounding box x offset' of a character is the x displacement from the left edge
;;; the character to the left edge of its bounding box; it may be positive or negative.
;;; The `bounding box y offset' of a character is the y displacement from the baseline
;;; of the character to the bottom of its bounding box; it may be positive or negative.
;;; Together, these offsets may be regarded as a vector, in the character coordinate
;;; system, from the origin of the character to the bottom left corner of its bounding
;;; box.

;;; The character-rectangle-array slot of a character description contains either
;;; nil or an array of character rectangles (see below).

(def-structure (minimal-character-description
		 #-development		; (:type vector) in non-development just 
		 (:type vector)		;   to save a bit of space (MHD 4/17/91)
		 (:constructor
		   make-minimal-character-description
		   (character-set-width character-rectangle-array)))
  character-set-width				; width at normalized scale

  (character-scaleable-text-width? nil)	; nil or a scaleable width, as a text width
  character-rectangle-array		; add "?"!
					; nil or a rectangle array (nil possible
					;   as of 4.0, used for Cyrillic, which
					;   is just an outline font for which we only
					;   store the metrics, i.e. the rest of the
					;   slots herein, and not the bitmap data
					; if nil, this should be a minimal character
					;   description; if non-nil, this should be
					;   a full-fledged character description
  )

(def-structure (character-description
		 #-development		; (:type vector) in non-development just 
		 (:type vector)		;   to save a bit of space (MHD 4/17/91)
		 ;; apparently, :include and (:type vector) don't go together, an
		 ;; issue I'm deferring by hand-including the slots from
		 ;; minimal-character-description below! (MHD 10/18/99)
		 ; (:include minimal-character-description)
		 (:constructor
		   make-character-description
		   (character-set-width character-rectangle-array
		    bounding-box-x-offset bounding-box-y-offset
		    bounding-box-width bounding-box-height)))
  character-set-width-dummy
  (character-scaleable-text-width?-dummy nil)
  character-rectangle-array-dummy

  bounding-box-x-offset bounding-box-y-offset bounding-box-width bounding-box-height)

;; The slots above are dummies to hack an include of
;; minimal-character-description that won't complain about double definition.
;; Since they are in the same positions in the structures the accessors for one
;; will work on the other.  (MHD 10/21/99)

;; Reclaimers are available, and actually may be used, e.g., when adding bitmap
;; data for character with only a minimal character description (e.g., for
;; Cyrillic fonts used when printing).  But note that there is currently no way
;; to reclaim a character rectangle array.  At present there is no practical
;; need for this functionality. (MHD 10/20/99)

;; Consider also including a character-set-width-as-text-width slot, to make text-width-
;; for-character a bit more efficient.



;;; Get-non-kanji-character-description-if-any returns a character description for the
;;; character in non-kanji-font specified by character-code, if any, or else nil.  This
;;; expands into fast in-line code.

(def-substitution-macro get-non-kanji-character-description-if-any
			(character-code ab-font-character-description-table)
  (if (<=f character-code #.(largest-non-kanji-font-character-code))
      (svref ab-font-character-description-table character-code)))

;; Consider later omitting the character-code test.



;;; `Get-kanji-character-description-if-any' returns a character description for
;;; the character in ab-font-character-description-table (from a kanji font)
;;; specified by kanji-code, if any, or else nil.  This expands into fast
;;; in-line code.

;;; Note that this may return nil for potentially legal character codes, e.g.,
;;; when the character descriptions for Japanese or Korean or Chinese have not
;;; yet been loaded because they are not authorized.

(defmacro get-kanji-character-description-if-any
	  (kanji-code ab-font-character-description-table)
  `(let ((kanji-code ,kanji-code)
	 (ab-font-character-description-table ,ab-font-character-description-table))
     (loop as l on (svref ab-font-character-description-table
			  (modf-positive
			    kanji-code
			    #.kanji-font-cache-sub-vector-length))
		by 'cddr
	   when (=f (car l) kanji-code)
	     return (cadr l))))

;; An equivalent definition is
;;
;; (def-substitution-macro get-kanji-character-description-if-any (kanji-code kanji-font)
;;   (getf (svref ab-font-character-description-table
;;	          (modf kanji-code #.kanji-font-cache-sub-vector-length))
;;	   kanji-code))


;;; `Set-kanji-character-description' creates an entry at the designated code
;;; space for character-description-or-rectangle-array-or-bitmap?, if any, in
;;; the character description table.  Unless there is already some entry at this
;;; code point, this causes dynamic consing.  That is OK, since the memory in
;;; this table is considered permanent, never to be reclaimed for the life of
;;; the G2 process.
;;;
;;; (If we desired to be able to reclaim this memory, work would be needed to
;;; reclaim the conses, as well as the structures.)
;;;
;;; Character-description-or-rectangle-array-or-bitmap? may be nil, in which
;;; case this effectively just cuts off the pointer to the character description
;;; or rectangle array or bitmap.  This feature is intended only for offline
;;; (development) use.  Therefore, no attempt is made to reclaim the storage.

(defun set-kanji-character-description
    (kanji-code ab-font-character-description-table
		character-description-or-rectangle-array-or-bitmap?)
  (with-permanent-allocation		; for now, never removed once allocated 
    (setf (getf (svref ab-font-character-description-table
		       (modf-positive
			 kanji-code
			 #.kanji-font-cache-sub-vector-length))
		kanji-code)
	  character-description-or-rectangle-array-or-bitmap?)))


;;; `Set-non-kanji-character-description' makes and returns a character
;;; description at run time.  If bitmap? is nil, this creates a
;;; minimal character description, and the last four arguments are ignored, and
;;; should just be supplied as arbitrary integers.

;;; `Change-non-kanji-character-description' is almost the same, except that it
;;; reclaims or reuses the character description that's present for the supplied
;;; font code, if any.  [At present, this is should not normally be used to
;;; "downgrade" a character description at run time to not have bitmap data,
;;; since there is currently no general support for reclaiming this kind of
;;; bitmap data.

(defun-simple set-non-kanji-character-description
    (font-code ab-font-character-description-table
	       set-width bitmap? x-offset y-offset width height
	       scaleable-text-width?)
  (let ((cd
	  (if bitmap?
	      (make-character-description set-width bitmap? x-offset y-offset width height)
	      (make-minimal-character-description
		set-width bitmap?))))
    (when scaleable-text-width?
      (setf (character-scaleable-text-width? cd)
	    scaleable-text-width?))
    (setf (svref ab-font-character-description-table font-code) cd)
    cd))


(defun change-non-kanji-character-description
    (font-code ab-font-character-description-table
	       set-width bitmap-data? x-offset y-offset width height
	       &optional scaleable-text-width?)
  (let (old-cd)
    (cond
      ((setq old-cd (svref ab-font-character-description-table font-code))
       (cond
	 ((character-rectangle-array old-cd)
	  #+development	   ; warn, note: case not encountered in practice
	  (cerror "continue, leak anyway"
		  "Needs work: can't reclaim character rectangle arrays!")
	  (cond
	    ((null bitmap-data?)
	     (reclaim-character-description old-cd)
	     (set-non-kanji-character-description
	       font-code ab-font-character-description-table
	       set-width bitmap-data?
	       x-offset y-offset width height scaleable-text-width?))
	    (t
	     (setf (character-rectangle-array old-cd) bitmap-data?)
	     (setf (character-set-width old-cd) set-width)
	     (setf (character-scaleable-text-width? old-cd) scaleable-text-width?)
	     (setf (bounding-box-x-offset old-cd) x-offset)
	     (setf (bounding-box-y-offset old-cd) y-offset)
	     (setf (bounding-box-width old-cd) width)
	     (setf (bounding-box-height old-cd) height)
	     old-cd)))
	 ((null bitmap-data?)
	  (setf (character-set-width old-cd) set-width)
	  (setf (character-scaleable-text-width? old-cd) scaleable-text-width?)
	  old-cd)
	 (t
	  (reclaim-minimal-character-description old-cd)
	  (set-non-kanji-character-description
	    font-code ab-font-character-description-table
	    set-width bitmap-data?
	    x-offset y-offset width height scaleable-text-width?))))
      (t
       (set-non-kanji-character-description
	 font-code ab-font-character-description-table
	 set-width bitmap-data?
	 x-offset y-offset width height scaleable-text-width?)))))

;; Note: this does not support scaleable set width, other than setting them to
;; nil when recycling.  Support could be added if desired; they're not used now.




;;; `Get-character-description-if-any' ...

(defun-substitution-macro get-character-description-if-any (font-code ab-font)
  (let ((table (ab-font-character-description-table ab-font)))
    (case (ab-font-type ab-font)
      (kanji
       (get-kanji-character-description-if-any font-code table))
      (t
       (get-non-kanji-character-description-if-any font-code table)))))








;;;; Character Set Widths



;;; `use-scaleable-set-widths?' ...

(def-system-variable use-scaleable-set-widths? fonts nil)

;; When this changes, all texts must be reformatted, and all character images
;; must get new scaled set widths.  Abstract an operation to do this!



;;; Text-width-for-character ...

(def-substitution-macro text-width-for-character (character-description? ab-font)
  (or (fixed-text-width-of-font? ab-font)
      (if character-description?
	  (or (if use-scaleable-set-widths?
		  (character-scaleable-text-width? character-description?))
	      (convert-to-text-width
	       (character-set-width character-description?)))
	  (convert-to-text-width
	   (missing-character-set-width ab-font)))))


;; A defmacro definition would have to evaluate ab-font in all cases. -- obsolete
;; comment with new (or (fixed-width-... ab-font) ...) wrapper. (MHD 9/23/91)







;;; Get-set-width-for-character ... character-or-character-code must be an integer
;;; if ab-font is a kanji font; otherwise, it can either be a simple character or
;;; any non-kanji character code.  This returns set width as a text width.  Use
;;; the function text-width-to-x to convert to a workspace width.  

;;; Note that you can map from a non-kanji ab-font to a corresponding kanji ab-
;;; font by using get-corresponding-kanji-font-name-and-magnification, q.v.

(defun get-set-width-for-character (character-or-character-code ab-font)
  (text-width-for-character
    (get-character-description-if-any
      (if (characterp character-or-character-code)
	  (convert-simple-character-to-ascii character-or-character-code)
	  character-or-character-code)
      ab-font)
    ab-font))

;; For use in CHARTS1 only at present.  (MHD/WGD 4/22/92)

;; Examples:
;; 
;; (get-set-width-for-character #\1 (ab-font 'hm14))
;; (text-width-to-x (get-set-width-for-character #\1 (ab-font 'hm14)))
;; (text-width-to-x (get-set-width-for-character #\0 (ab-font 'hm14)))
;; (text-width-to-x (get-set-width-for-character #\0 (ab-font 'hm18)))
;; (text-width-to-x (get-set-width-for-character #\0 (ab-font 'hm24)))
;; (text-width-to-x (get-set-width-for-character #\. (ab-font 'hm14)))
;; (text-width-to-x (get-set-width-for-character #\- (ab-font 'hm14)))
;; (text-width-to-x (get-set-width-for-character #\. (ab-font 'hm18)))
;; (text-width-to-x (get-set-width-for-character #\- (ab-font 'hm24)))
;; (text-width-to-x (get-set-width-for-character #\2 (ab-font 'hb72)))
;; (text-width-to-x (get-set-width-for-character #\- (ab-font 'hb72)))




;;; The function `font-digit-text-width' of font, a font structure or font name,
;;; returns the width of the digits in that font as a text width.  Font must be
;;; a roman font and have a character description for the "2" character present.
;;; Font must also have its character descriptions loaded into memory.  This may
;;; be used at load time as well as a run time.
;;;
;;; Note that the '2' happens to be the only digit present by default in all of
;;; our fonts; i.e., the other digits are missing in one font: HB72.

(defun-simple font-digit-text-width (font)
  (get-set-width-for-character
    #\2
    (if (symbolp font) (ab-font font) font)))


;;; Font-digit-line-height-as-text-width of font, a font structure or font name,
;;; returns, as a text width, the height required to hold a line all of the
;;; digits.

(defun-simple font-digit-line-height-as-text-width (font)
  (let* ((ab-font (if (symbolp font) (ab-font font) font))
	 (character-description-table
	   (ab-font-character-description-table ab-font)))
    (convert-to-text-width
      (loop for character in
	       '#.(loop for char in '(#\0 #\1 #\2 #\3 #\4 #\5 #\6 #\7 #\8 #\9)
			collect (convert-simple-character-to-ascii char))
	    as character-description?
	      = (get-non-kanji-character-description-if-any
		  character character-description-table)
	    when character-description?
	      maximize (bounding-box-height character-description?)))))

;; Consider caching this in the ab font structure if speed is an issue.

;; Note that at present, our standard fonts all have integer bounding box
;; heights.

;; At present, all digits in all fonts used by Gensym software rest precisely on
;; the baseline.  That is a characteristic that may or may not be present in a
;; given font.  Most modern fonts have this characteristic.  Older fonts, or
;; fonts wanting to look old for stylistic reasons, often have some digits (like
;; the 3) that descend below the baseline.

;; Note that X Windows's XLFD has a property called FIGURE_WIDTH that
;; corresponds to the digit width.  That's about the same property except that
;; it applies to the dollar sign ($) as well the arabic numerals 0 through 9.
;; The property is allowed to be undefined, i.e., for fonts that don't have
;; these characters, or for which these are not all the same width.


  




;;;; Character Rectangles



;;; A `character rectangle' is one of a set of rectangles, the union of which describes
;;; the image of a particular character at normalized scale.  A character rectangle is
;;; specified by its four edges in a coordinate system where the origin is the left-top
;;; (upper left-hand) corner of the bounding box for the character and where x and y
;;; increase to the right and down, respectively, as they do in our workspace and raster
;;; coordinate systems.  (Thus all edges are non-negative.)  A character rectangle is
;;; represented either as a gensym list of the form
;;;
;;;    (left-edge top-edge right-edge bottom-edge)
;;;
;;; or, provided the absolute value of every edge is less than 64, as the fixnum
;;;
;;;    2^18 * left-edge + 2^12 * top-edge + 2^6 * right-edge + bottom-edge.

;;; Character rectangles are originally computed by compute-character-rectangles-per-
;;; current-scratchpad-raster.



;;; `Make-character-rectangle' returns a new character rectangle with the specified
;;; edges.

(def-substitution-macro make-character-rectangle
    (left-edge top-edge right-edge bottom-edge)
  (if (and (<f left-edge 64)
	   (<f top-edge 64)
	   (<f right-edge 64)
	   (<f bottom-edge 64))
      (+f (* #.(ashf 1 18) left-edge)
	  (* #.(ashf 1 12) top-edge)
	  (* #.(ashf 1 6) right-edge)
	  bottom-edge)
      (permanent-list left-edge top-edge right-edge bottom-edge)))

;; Consider just defining this as a function.



;;; `Left-edge-of-character-rectangle', `top-edge-of-character-rectangle',
;;; `right-edge-of-character-rectangle', and `bottom-edge-of-character-rectangle' return
;;; the appropriate edge of character-rectangle.

(def-substitution-macro left-edge-of-character-rectangle (character-rectangle)
  (if (consp character-rectangle)
      (first character-rectangle)
      (logandf (ashf character-rectangle -18) 63)))

(def-substitution-macro top-edge-of-character-rectangle (character-rectangle)
  (if (consp character-rectangle)
      (second character-rectangle)
      (logandf (ashf character-rectangle -12) 63)))

(def-substitution-macro right-edge-of-character-rectangle (character-rectangle)
  (if (consp character-rectangle)
      (third character-rectangle)
      (logandf (ashf character-rectangle -6) 63)))

(def-substitution-macro bottom-edge-of-character-rectangle (character-rectangle)
  (if (consp character-rectangle)
      (fourth character-rectangle)
      (logandf character-rectangle 63)))

;; When all four of these are used together, the result of the consp test could be saved
;; in a variable for a slight speed improvement.





;;;; Character Bitmaps



;;; A `character bitmap' ...

#+development
(def-development-printer print-bitmap
    (object &optional (stream *standard-output*))
  (when (and (typep object 'simple-array)
	     (eq 'bit (array-element-type object))
	     (eql 2 (array-rank object)))
    (printing-random-object (object stream)
      (format stream "BITMAP ~Dx~D"
	      (array-dimension object 0)
	      (array-dimension object 1)))
    object))

;;; Allocate-character-bitmap ... all elements are initialized to 0.

(defmacro allocate-character-bitmap (width height)
  `(with-permanent-array-creation
     #-lucid
     (setf (first character-bitmap-scratch-list) ,width)
     #-lucid
     (setf (second character-bitmap-scratch-list) ,height)
     (make-array
       #-lucid character-bitmap-scratch-list
       #+lucid (with-permanent-allocation (list ,width ,height))
       :initial-element 0 :element-type 'bit)))

(defvar character-bitmap-scratch-list (list nil nil))

;; JRA thinks these should probably be implemented as byte vectors.  If that
;; is done, character-bitmap-width and character-bitmap-height would be a pain
;; to support (accurately); consider not supporting those operations.  (Also,
;; some implementations of "bitblt" (e.g., Lispm's) require bitmaps with widths
;; rounded up to a multiple of 32.)

;; jh, 3/11/93.  The macro allocate-character-bitmap used to give the form
;; `(,,width ,,height) as first argument to make-array.  This does not work in
;; Chestnut, although it should.  The reason it should work is that the
;; backquote character in the translation environment (Lucid) is a read macro
;; that expands into lucid-runtime-support:bq-list.  This is a macro that is
;; available to the Chestnut translator, just as allocate-character-bitmap was.
;; So the translator should continue expanding it, probably to a call to
;; lisp:list.  Anyway, I have substituted the more prosaic (list ,height ,width)
;; to do the work the Chestnut macroexpansion should have done.

;; Garbage!  I see garbage!  Calling list on the dimensions causes two conses
;; worth of garbage for each character bitmap allocated.  I've changed it to
;; modify an always existing two element list.  I do wish that we could avoid
;; using two dimensional arrays, though I can certainly see why we would want to
;; use bit vectors.  As it is all references into this thing are done with
;; generic setf calls which we would like to get inlined.  -jra 8/6/93
;;
;; When Jim's approach is used, it puts Lucid into a bad state such that it gets
;; indexing errors, such as, e.g., (aref array 10 10) doesn't work on a 16x16
;; array.  I have therefore switched it back to using list, with the appropriate
;; with-permanent-allocation wrapper, in Lucid only.  I guess this is a
;; workaround for a Lucid bug.  (MHD 12/15/94)




(defmacro character-bitmap-value (character-bitmap x y)
  `(aref ,character-bitmap ,x ,y))


(defmacro character-bitmap-width (character-bitmap)
  `(array-dimension ,character-bitmap 0))

(defmacro character-bitmap-height (character-bitmap)
  `(array-dimension ,character-bitmap 1))


(defun-void fill-rectangle-in-character-bitmap (character-bitmap value x0 y0 x1 y1)
  (loop for y from y0 below y1
	do (loop for x from x0 below x1
		 do (setf (character-bitmap-value character-bitmap x y) value))))


; #+development ; leave in for now.  REVIEW!! (MHD 12/6/91)
(defun print-character-bitmap (character-bitmap &optional width? height? include-labels-p)
  (loop with width = (or width? (character-bitmap-width character-bitmap))
	with height = (or height? (character-bitmap-height character-bitmap))
	for y from 0 below height
	when (and (=f y 0)  include-labels-p)
	  do (loop initially (princ " ") ; offset 1 space
		   for i from 0 below height
		   do (princ (mod i 10)))
	do (terpri)
	   (when include-labels-p
	     (princ (mod y 10)))
	   (loop for x from 0 below width
		 do (princ
		      (case (character-bitmap-value character-bitmap x y)
			(0 ".")
			(t "@"))))))



;;; Not-a-character-rectangle-array-but-a-bitmap-p may be used to distinguish
;;; a character rectangle array from a character bitmap.  At present, character
;;; bitmap take over the character-rectangle-array slot of character
;;; descriptions, so this needs to be used in a couple of places in FONTS to
;;; tell them apart.

;;; This should only be used to tell a character rectangle array from a
;;; character bitmap.

(defmacro not-a-character-rectangle-array-but-a-bitmap-p
	  (character-bitmap-or-rectangle-array)
  `(not (vectorp ,character-bitmap-or-rectangle-array)))



;;; A temporary bitmap may allocated and reclaimed using
;;; allocate-temporary-character-bitmap reclaim-temporary-character-bitmap.
;;; This returns a bitmap that's as big as, or bigger, than width and height.
;;; 
;;; This facility is not fast or space efficient; it is currently designed to
;;; handle giving only a few bitmaps, with very short duration, and with few
;;; sizes.  It meets the demands of its current users adequately.

(def-system-variable reclaimed-temporary-character-bitmaps fonts nil)

(defun-simple allocate-temporary-character-bitmap (width height)
  (loop as remaining-bitmaps-tail? = nil then remaining-bitmaps
	for remaining-bitmaps on reclaimed-temporary-character-bitmaps
	for character-bitmap = (car remaining-bitmaps)
	when (and (>=f (character-bitmap-width character-bitmap)
		       width)
		  (>=f (character-bitmap-height character-bitmap)
		       height))
	  do (cond
	       (remaining-bitmaps-tail?
		(setf (cdr remaining-bitmaps-tail?)
		      (cdr remaining-bitmaps)))
	       (t
		(setf reclaimed-temporary-character-bitmaps
		      (cdr remaining-bitmaps))))
	     (setf (car remaining-bitmaps) nil)
	     (setf (cdr remaining-bitmaps) nil)
	     (reclaim-gensym-cons remaining-bitmaps)
	     (return character-bitmap)
	finally
	  (return (allocate-character-bitmap width height))))

(defun-void reclaim-temporary-character-bitmap (character-bitmap)
  (setq reclaimed-temporary-character-bitmaps
	(gensym-cons character-bitmap reclaimed-temporary-character-bitmaps)))





;;;; (Crude) Character Bitmap Editor (Development)

#+development
(progn

(defun flip-cb (cb x y)
  (let ((val (character-bitmap-value cb x y)))
    (setf (character-bitmap-value cb x y) (if (= val 1) 0 1))))

(defun set-cb (cb x y)
    (setf (character-bitmap-value cb x y) 1))

(defun clear-cb (cb x y)
    (setf (character-bitmap-value cb x y) 0))

(defun edit-cb (cb)
  (print-character-bitmap cb nil nil t)
  (loop as act = (progn (format t "~%Act: ") (read))
	when (member act '(-  n))
	  return nil
	while act
	do (cond
	     ((and (consp act) (consp (car act)))
	      (loop for subact in act
		    do (interpret-cb-act subact cb)))
	     (t (interpret-cb-act act cb)))
	   (print-character-bitmap cb nil nil t)
	finally (return t)))

(defun interpret-cb-act (act cb)
  (when (eq
	  'usage
	  (cond
	    ((or (eq act 'n) (eq act '-)))
	    ((atom act) 'usage)
	    ((integerp (car act))
	     (set-cb cb (car act) (cadr act)))
	    ((eq (car act) '+)
	     (set-cb cb (second act) (third act)))     
	    ((eq (car act) '=)
	     (format t "~%~a => ~d~%" act (character-bitmap-value cb (second act) (third act))))
	    ((eq (car act) '-)
	     (clear-cb cb (second act) (third act)))
	    ((eq (car act) '*)
	     (flip-cb cb (second act) (third act)))
	    (t 'usage)))
    (format t "~%Usage: type
  - or n -- skip this, go to next, without saving
  () -- to finish editing, and save
  (* x y) -- to flip bit at (x, y)
  (+ x y) -- to set bit at (x, y)
  (x y)   -- ditto.
  (- x y) -- to clear bit at (x, y)
  (= x y) -- to print bit at (x, y)~%")))


;;; `Edit-hungarian-umlauts' ... was used to hand-edit in Hungariam umlauts.

(defun edit-hungarian-umlauts ()
  (let ((hungarian-umlaut-cb-set
	  (loop for font in '(hm14 hm18 hm24)
		nconc
		(loop for i from 20 to 23
		      collect
		      (list font i
			    (convert-character-rectangle-array-to-character-bitmap
			      (get-character-description-if-any
				i (ab-font font))))))))
    (edit-cb-set hungarian-umlaut-cb-set)))

(defun edit-cb-set (cb-set)
  (loop for (font-name font-code cb) in cb-set
	do (format t "~%~%Edit font ~a, code ~d, bitmap ~a~%"
		   font-name font-code cb)
	   (when (edit-cb cb)
	     (save-cb font-name font-code cb))))

(defun save-cb (font-name font-code cb)
  (let ((file-name (format nil "hung-~(~a-~a~)-bitmap.txt" font-name font-code))
	(*print-length* nil))		; no ...'s at the ends of lists, please
    (format t "~%Saving to ~s ..." file-name)
    (with-open-file (o file-name :direction :output)
      (format o "~%~a ~a ~a" font-name font-code cb)
      (format o "~%~%Bitmap:~%")
      (let ((*standard-output* o))
	(print-character-bitmap cb nil nil t))
      (format o "~%~%Character rectangles list: ~a"
	      (vl
		(convert-character-bitmap-to-rectangle-array cb))))
    (format t "DONE.~%~%")))

)




;;;; AB Binary Font Array Files


;;; A font bitmap sequence for a font F, consisting of a known number of
;;; characters N, of a known maximum width W, of a known maximum height H, with
;;; a known ordered set of character code indexes {i}, is as follows.
;;;
;;; Let n = the number of characters in the font.
;;; Let w = the maximum width of any character bitmap in the font.
;;; Let h = the maximum height of any character bitmap in the font.
;;;
;;; Then n * w * h is the number of bits to be represented in the font file.
;;;
;;; The font file shall represent this using
;;;
;;;    (* n (truncate (+ (* w h) 7) 8))
;;;    
;;; bytes.
;;;
;;; The bytes are layed out in fixed positions, with the bytes corresponding
;;; to the first character in the font appearing first, the second character
;;; second, etc.  What characters are present is not encoded in the format;
;;; the application using this must know how to interpret the data.
;;;
;;; The format lends itself very well to relatively small bitmaps.  It also well-
;;; suited to fixed-size fonts.
;;;
;;; It does not contain any semantic information about the font.  To make use of
;;; this, the font bitmap sequence must be embedded in a larger file containing
;;; that information, or be called by a program that stores that information
;;; separately.



;;; A `bitmap array' is a data-abstracted array for storing the contents of a
;;; font bitmap sequence in memory.
;;;
;;; 

(def-structure (bitmap-array
		 (:constructor make-bitmap-array-internal))
  bitmap-array-width
  bitmap-array-height
  bitmap-array-length
  bitmap-array-byte-vector-max-length	; bytes per byte vector
					;   that can fit 1 or more entire
					;   bitmaps
  (bitmap-array-vector-of-byte-vectors	; vector of byte vectors,
    nil					;   containing up to the
					;   above number of bytes and
					;   representing a series of whole
					;   bitmaps
    :reclaimer reclaim-vector-of-byte-vectors)
  bitmap-array-byte-vector-length	; total length in bytes
  bitmap-array-bytes-per-bitmap
  bitmap-array-character-code-to-direct-index-map?)


(defun reclaim-vector-of-byte-vectors (vector-of-byte-vectors)
  (declare (ignore vector-of-byte-vectors))
  #+development
  (error "This is not implemented!"))

;; We currently never reclaim these.  I don't know how to do that other than
;; building (possibly quantized) pools of simple vectors, so just defer this
;; until we need it.  Reclaiming the internal byte vectors would also be
;; necessary, but that's easy.  (MHD 12/23/94)



;;; `Make-bitmap-array' ...

(defmacro compute-bitmap-array-bytes-per-bitmap (width height)
  `(ceilingf (*f ,width ,height) 8))

(defmacro compute-bitmap-length-for-bitmap-array-byte-vector
    (number width height)  
  `(*f ,number (compute-bitmap-array-bytes-per-bitmap ,width ,height)))


;;; `Make-bitmap-array' creates a bitmap array. Map-spec? may be either KANJI,
;;; ROMAN, or any valid actual map.  The map maps from a character code to a
;;; direct index in the bitmap array.  A map may be one of the following:
;;;
;;;    nil  -  character-code => direct index  [no translation needed]
;;;    integer - an offset; (+ character-code offset) => direct index
;;;    symbol - a function; (funcall function character-code) => direct index
;;; 

(defun make-bitmap-array (number-of-bitmaps width height &optional map-spec?)
  (let ((bitmap-array (make-bitmap-array-internal)))
    (setf (bitmap-array-width bitmap-array) width)
    (setf (bitmap-array-height bitmap-array) height)
    (setf (bitmap-array-length bitmap-array) number-of-bitmaps)
    (setf (bitmap-array-byte-vector-length bitmap-array)
	  (compute-bitmap-length-for-bitmap-array-byte-vector
	    number-of-bitmaps width height))
    (setf (bitmap-array-bytes-per-bitmap bitmap-array)
	  (compute-bitmap-array-bytes-per-bitmap width height))
    ;; each byte vector stores integral number of entire bitmaps,
    ;; less than the maximum length constant
    (let ((hard-max (-f maximum-byte-vector-length 1)))
					; -1 -- wallpaper over bug; avoid the
      					;   outer reaches
      (setf (bitmap-array-byte-vector-max-length bitmap-array)	  
	    (-f hard-max	    
		(modf hard-max
		      (bitmap-array-bytes-per-bitmap bitmap-array)))))
    #+development			; that integer can't be zero
    (assert (>f (bitmap-array-byte-vector-max-length bitmap-array) 0))
    
    (setf (bitmap-array-vector-of-byte-vectors bitmap-array)
	  (let* ((total-length
		   (bitmap-array-byte-vector-length bitmap-array))
		 (full-length
		   (bitmap-array-byte-vector-max-length bitmap-array))
		 (number-of-byte-vectors 
		   (ceilingf-positive total-length full-length))
		 (number-of-full-length-byte-vectors
		   (floorf-positive total-length full-length))
		 (length-of-partial-byte-vector
		   (modf-positive total-length full-length))
		 (bitmap-array-vector-of-byte-vectors
		   (allocate-managed-simple-vector number-of-byte-vectors)))
	    (loop for i from 0
			below number-of-full-length-byte-vectors
		  do (setf (svref bitmap-array-vector-of-byte-vectors i)
			   (allocate-byte-vector full-length)))
	    (unless (=f length-of-partial-byte-vector 0)
	      (setf (svref bitmap-array-vector-of-byte-vectors
			   number-of-full-length-byte-vectors)
		    (allocate-byte-vector length-of-partial-byte-vector)))
	    bitmap-array-vector-of-byte-vectors))
    
    (setf (bitmap-array-character-code-to-direct-index-map? bitmap-array)
	  (case map-spec?
	    (kanji
	     'map-from-asian-character-code-to-direct-index)
	    (roman
	     -32)
	    (t map-spec?)))
    bitmap-array))




(defmacro bitmap-array-byte-reference (bitmap-array-byte-vector index)
  `(byte-vector-aref ,bitmap-array-byte-vector ,index))

(defun-substitution-macro bitmap-array-bit-byte-index
    (max-width max-height index column-index row-index)
  (let ((byte-index-for-character
	  (*f index (compute-bitmap-array-bytes-per-bitmap max-width max-height))))
    (multiple-value-bind (byte-index-within-character bit-index)
	(truncatef
	  (+f (*f row-index max-width) column-index)
	  8)
      (values
	(+f byte-index-for-character byte-index-within-character)
	bit-index))))


(defun-substitution-macro get-byte-vector-for-byte-index
    (bitmap-array byte-index)
  (svref (bitmap-array-vector-of-byte-vectors bitmap-array)
	 (floorf-positive
	   byte-index
	   (bitmap-array-byte-vector-max-length bitmap-array))))


;(defun-substitution-macro bitmap-array-reference (bitmap-array index)
;  (bitmap-array-byte-reference
;    (get-byte-vector-for-byte-index bitmap-array index)
;    (bitmap-array-bit-byte-index
;      (bitmap-array-width bitmap-array)
;      (bitmap-array-height bitmap-array)
;      index 0 0)))


(defun-substitution-macro bitmap-array-value
    (bitmap-array index column-index row-index)
  (multiple-value-bind (byte-index bit-index)
      (bitmap-array-bit-byte-index
	(bitmap-array-width bitmap-array)
	(bitmap-array-height bitmap-array)
	index column-index row-index)
    (declare (type fixnum byte-index bit-index))
    (if (logbitpf bit-index
		  (bitmap-array-byte-reference
		    (get-byte-vector-for-byte-index bitmap-array byte-index)
		    (modf-positive
		      byte-index
		      (bitmap-array-byte-vector-max-length bitmap-array))))
	1
	0)))

(defun-substitution-macro
    set-bitmap-array-value
    (bitmap-array index column-index row-index value)
  (multiple-value-bind (byte-index bit-index)
      (bitmap-array-bit-byte-index
	(bitmap-array-width bitmap-array)
	(bitmap-array-height bitmap-array)
	index column-index row-index)
    (declare (type fixnum byte-index bit-index))
    (let* ((mask
	     (svref '#(#2r00000001 #2r00000010 #2r00000100 #2r00001000
		       #2r00010000 #2r00100000 #2r01000000 #2r10000000)
		    bit-index))
	   (byte-vector
	     (get-byte-vector-for-byte-index bitmap-array byte-index))
	   (byte-index-in-byte-vector	     
	     (modf-positive
	       byte-index
	       (bitmap-array-byte-vector-max-length bitmap-array)))
	   (byte
	     (bitmap-array-byte-reference
	       byte-vector
	       byte-index-in-byte-vector)))
      (declare (type fixnum mask))
      (setf (bitmap-array-byte-reference byte-vector byte-index-in-byte-vector)
	    (if (=f value 0)
		(logandc2f byte mask)
		(logiorf byte mask))))
    value))

(defsetf bitmap-array-value set-bitmap-array-value)
	   



;;; The simple function `copy-from-bitmap-array-to-character-bitmap' copies the
;;; 1's in the relevant section of bitmap-array to character-bitmap.  Note that
;;; this depends on having a clear character bitmap (all zeros) in order to end
;;; up with an accurate copy.
;;;
;;; Here are several key assumptions about bitmap arrays:
;;;
;;;   (1) It is assumed that all bytes for a single bitmap within a bitmap array
;;;   lie within a single byte vector.
;;;
;;;   (2) It is assumed that a bitmap always is aligned to begin with an entire
;;;   byte -- they can't start in the middle of a byte.
;;;
;;;   (3) It is not assumed that (width X height) is always an even multiple of
;;;   of 8; i.e., you can run out of bits in the middle of the last byte.
;;;
;;; This also assumes that a proper size character bitmap, width, and height args
;;; are passed in.

(defun-simple copy-from-bitmap-array-to-character-bitmap
    (bitmap-array index character-bitmap width? height?)
  (declare (type fixnum index))
  (let* ((width (or width? (bitmap-array-width bitmap-array)))
	 (height (or  height? (bitmap-array-height bitmap-array)))
	 (number-of-bytes (ceilingf (*f width height) 8))
	 (byte-index
	   (bitmap-array-bit-byte-index
	     (bitmap-array-width bitmap-array)
	     (bitmap-array-height bitmap-array)
	     index 0 0)))
      (declare (type fixnum width height number-of-bytes byte-index))
      (let* ((byte-vector
	       (get-byte-vector-for-byte-index bitmap-array byte-index))
	     (start-index
	       (modf-positive
		 byte-index
		 (bitmap-array-byte-vector-max-length bitmap-array))))
	(loop with x fixnum = 0
	      with y fixnum = 0
	      for i from start-index
	      repeat number-of-bytes
	      as byte fixnum = (byte-vector-aref byte-vector i)
	      do (cond
		   ((not (=f byte 0))
		    (loop for bit-index from 0 below 8
			  do (setf (character-bitmap-value character-bitmap x y)
				   (if (logbitpf bit-index byte) 1 0))
			     (unless (<f (incff x) width)
			       (setq x 0)
			       (unless (<f (incff y) height)
				 (return)))))
		   ;; optimize for 0 byte case:
		   (t (multiple-value-bind (y-increment new-x)
			  (floorf (+f x 8) width)
			(declare (type fixnum y-increment new-x))
			(setq x new-x)
			(incff y y-increment))))))))

;; Consider making character-bitmap, width?, and height? not be parameters --
;; these can all be derived from bitmap-array.  Perhaps have a separate function
;; that works without these args.
;;
;; DONE: "This could be optimized (factor of 8, say?) if it's a bottleneck!"
;; 
;; Old, unoptimized, naive approach:
;;      (loop for y from 0 below height
;;            do (loop for x from 0 below width
;;                     do (setf (character-bitmap-value character-bitmap x y)
;;                              (bitmap-array-value bitmap-array index x y))))
;;
;; Result (in Lucid) for copying a 16x16 array 1000 times:
;;
;;   before: 8.42 seconds
;;   after:  1.23 seconds
;;
;; (MHD 1/22/95)
  
		
    
    
    
;;; `Convert-character-code-to-direct-index' ... It is assumed that bitmap-array
;;; has been configured with a proper map, in the slot bitmap-array-character-
;;; code-to-direct-index-map?.  The map may be one of the following:
;;;
;;;    nil  -  character-code => direct index  [no translation needed]
;;;    integer - an offset; (+ character-code offset) => direct index
;;;    symbol - a function; (funcall function character-code) => direct index
;;;
;;; [THIS IS OBSOLETE! (MHD 4/9/99)]

#+obsolete
(defun convert-character-code-to-direct-index
    (character-code bitmap-array)
  (let ((map? (bitmap-array-character-code-to-direct-index-map? bitmap-array)))
    (cond
      ((null map?)
       character-code)
      ((fixnump map?)
       (incff character-code map?))
      ((symbolp map?)
       (funcall map? character-code)))))




(defmacro with-open-bitmap-array-file
    ((stream-variable pathname) &body body)
  `(g2-stream-with-open-stream
     (,stream-variable ,pathname :element-type (unsigned-byte 8))
     . ,body))


(defun-substitution-macro read-byte-from-bitmap-array-stream (stream)
  (g2-stream-read-ascii-byte stream))


(defun-void read-bitmap-array-stream-into-byte-vector
    (stream byte-vector number-of-characters start-index)
  (g2-stream-read-into-byte-vector
    stream byte-vector number-of-characters start-index))


(defun-allowing-unwind test-read-bitmap-array-from-stream
    (p &optional (n-chars 100))		; p = a pathname
  (let ((width 16)
	(height 16)
	(number-of-chars n-chars))
    (with-open-bitmap-array-file (s p)
      (read-bitmap-array-from-stream
	s number-of-chars width height))))



;;; The function `Read-font-bitmap-sequence' reads from stream using read-byte.
;;; Stream should be a Common Lisp.

(defun-allowing-unwind read-bitmap-array-from-stream
    (stream number-of-bitmaps width height)
  (let* ((bitmap-array (make-bitmap-array number-of-bitmaps width height)))
    (let* ((total-length
	     (bitmap-array-byte-vector-length bitmap-array))
	   (full-length
	     (bitmap-array-byte-vector-max-length bitmap-array))
	   (number-of-full-length-byte-vectors
	     (floorf total-length full-length))
	   (length-of-partial-byte-vector
	     (modf total-length full-length))
	   (bitmap-array-vector-of-byte-vectors
	     (bitmap-array-vector-of-byte-vectors bitmap-array)))
      (loop for i from 0
		  below number-of-full-length-byte-vectors
	    do (read-bitmap-array-stream-into-byte-vector
		 stream
		 (svref bitmap-array-vector-of-byte-vectors i)
		 full-length
		 0))
      (unless (=f length-of-partial-byte-vector 0)
	(read-bitmap-array-stream-into-byte-vector
	  stream
	  (svref bitmap-array-vector-of-byte-vectors
		 number-of-full-length-byte-vectors)
	  length-of-partial-byte-vector
	  0)))  
    bitmap-array))




#+development
(progn






;;; The function `write-font-bitmap-data-to-file' writes just the bitmap font
;;; data in font as a binary font array file.

(defun write-font-bitmap-data-to-file (ab-font-or-font-name stream)
  (loop
    with ab-font
    = (if (symbolp ab-font-or-font-name)
	  (ab-font ab-font-or-font-name)
	  ab-font-or-font-name)
    with character-description-table
    = (ab-font-character-description-table ab-font)
    with number-of-characters = 0
    with character-codes-and-descriptions
    = (case (ab-font-type ab-font)
	(kanji
	 (sort
	   (loop for i from 0 below #.(kanji-font-cache-vector-length)
		 nconc (loop for l on (svref character-description-table i)
				   by 'cddr
			     as kanji-code = (car l)
			     unless (or (=f kanji-code 0)	; skip blob (0) code
					(null (jis-to-contiguous kanji-code))
					) ; SOMETHING FOR KOREAN (KSC) NEEDED! (MHD 1/5/94)
			                  ; Not supporting Chinese here, either. (MHD 4/9/99)
			       
			       collect (cons kanji-code (cadr l))))
	   #'(lambda (u v) (<f (car u) (car v)))))
	(t (loop for character-code
		 from 1 to #.(largest-non-kanji-font-character-code)
		 as character-description?
		 = (svref character-description-table character-code)
		 when character-description?
		   collect (cons character-code character-description?))))
    with fixed-bounding-box = (fixed-bounding-box-of-font? ab-font)
    as (character-code . character-description)
       in character-codes-and-descriptions
    initially 
      (unless fixed-bounding-box
	(error "fonts without fixed bounding box size unimplemented"))
    do (write-character-bitmap-as-binary-data
	 character-code character-description stream
	 (third fixed-bounding-box)
	 (fourth fixed-bounding-box))
       (incff number-of-characters)
    finally
      (return (values
		number-of-characters
		(third fixed-bounding-box)
		(fourth fixed-bounding-box)))))


(defun write-character-bitmap-as-binary-data
    (character-code character-description stream
		    bounding-box-width bounding-box-height)
  (when nil ;debugging?
    (print character-code))
  (loop with character-bitmap
	  = (if (not-a-character-rectangle-array-but-a-bitmap-p
		  character-description)
		character-description
		(convert-character-rectangle-array-to-character-bitmap
		  character-description)) ; BECOMES GARBAGE! FIX!!
	with max-length = 8		; 1 byte = 8 bits
	with integer-length = 0
	with bits = 0
	initially
	  (when (and nil ; t
		     (= character-code #x3121))
	    (list-character-bitmap-as-binary-data
	      character-bitmap
	      bounding-box-width bounding-box-height))
	for y from 0 below bounding-box-height
	do (loop for x from 0 below bounding-box-width
		 when (=f (character-bitmap-value character-bitmap x y) 1)
		   do (setq bits (+f bits (ashf 1 integer-length)))
		 do (incff integer-length)
		 when (=f integer-length max-length)
		   do (g2-stream-write-ascii-byte bits stream)
		      (setq bits 0)
		      (setq integer-length 0))
	finally
	  (unless (=f integer-length 0)
	    (g2-stream-write-ascii-byte bits stream)
	    bits)))


(defun write-asian-font-to-file
    (language ab-font stream &key start end)
  (loop with size = (ab-font-size ab-font)
	with empty-bitmap = (allocate-character-bitmap size size) ; assume square
	with character-description-table
	  = (ab-font-character-description-table ab-font)
	for i from (or start 0)
	      below (or end
			(case language
			  (japanese jis-last-contiguous-code)
			  (korean ksc-last-contiguous-code)
			  ;; not supporting legacy Chinese
			  ;;  charsets here (MHD 4/9/99)
			  (t 0))) ; make compiler happy
	as character-code
	  = (case language
	      (japanese (contiguous-to-gensym-jis-code i))
	      (korean (contiguous-to-gensym-ksc-code i))
	      ;; not supporting legacy Chinese
	      ;;  charsets here (MHD 4/9/99)
	      (t 0)) ; make compiler happy
	as character-description?
	  = (get-kanji-character-description-if-any
	      character-code
	      character-description-table)
	as bitmap = (or (if character-description?
			    (if (not-a-character-rectangle-array-but-a-bitmap-p
				  character-description?)
				character-description?
				(convert-character-rectangle-array-to-character-bitmap
				  character-description?)))
			empty-bitmap)
	count character-description? into actual-glyph-count
	do  (write-bitmap-as-binary-data bitmap stream size size)
	finally
	  (return actual-glyph-count)))

(defun write-bitmap-as-binary-data (bitmap stream width height)
  (loop with max-length = 8		; 1 byte = 8 bits
	with integer-length = 0
	with bits = 0
	for y from 0 below height
	do (loop for x from 0 below width
		 when (=f (character-bitmap-value bitmap x y) 1)
		   do (setq bits (+f bits (ashf 1 integer-length)))
		 do (incff integer-length)
		 when (=f integer-length max-length)
		   do (g2-stream-write-ascii-byte bits stream)
		      (setq bits 0)
		      (setq integer-length 0))
	finally
	  (unless (=f integer-length 0)
	    (g2-stream-write-ascii-byte bits stream)
	    bits)))

(defun list-character-bitmap-as-binary-data (character-bitmap width height)
  (loop with result = nil
	with max-length = 8		; 1 byte = 8 bits
	with integer-length = 0
	with bits = 0
	for y from 0 below height
	do (loop for x from 0 below width
		 when (=f (character-bitmap-value character-bitmap x y) 1)
		   do (setq bits (+f bits (ashf 1 integer-length)))
		 do (incff integer-length)
		 when (=f integer-length max-length)
		   do (push bits result)
		      (setq bits 0)
		      (setq integer-length 0))
	finally
	  (unless (=f integer-length 0)
	    (push bits result)
	    bits)
	  (setq result (nreverse result))
	  (loop for (a b) on result by 'cddr
		do (format t "~% ~2,16r ~2,16r" a b))
	  (print-character-bitmap character-bitmap width height)
	  (read-line)
	  (return result)))

;; Note: JIS "Kanji" characters only start getting interesting (being really
;; Kanji) at #x3121.




(defun-allowing-unwind test-write-k16-old ()
  (g2-stream-with-open-stream
    (output-stream "/home/mhd/tmp/k16-old.gb" :direction :output)
    (write-font-bitmap-data-to-file 'kanji16 output-stream)))

(defun-allowing-unwind test-write-k16 ()
  ; 1st: (read-asian-font-file 'kanji16)
  (g2-stream-with-open-stream
    (output-stream "/home/mhd/tmp/k16.gb" :direction :output)
    (write-asian-font-to-file
      'japanese
      (ab-font 'kanji16)
      output-stream)))
	     

(defun-allowing-unwind test-read-k16-into-bitmap-array ()
  (with-open-bitmap-array-file (s "/home/mhd/tmp/k16.gb")
    (read-bitmap-array-from-stream s 6875 16 16)))

(defun print-bitmap-array (bitmap-array &optional (increment 1))
  (loop with width = (bitmap-array-width bitmap-array)
	with height = (bitmap-array-height bitmap-array)
	with character-bitmap = (allocate-character-bitmap width height)
	for i from 0 below (bitmap-array-length bitmap-array)
	by increment
	do (copy-from-bitmap-array-to-character-bitmap
	     bitmap-array i character-bitmap width height)
	   (print-character-bitmap character-bitmap width height)
	   (when (=f (modf i 25) 0)
	     (format t "~%More? (y or n) [y] ")
	     (when (search "n" (read-line))
	       (return)))))

(defun print-bitmap-array-jis-character (bitmap-array jis-character-code)
  (when (jis-to-contiguous jis-character-code)
    (let ((character-bitmap
	    (allocate-character-bitmap
	      (bitmap-array-width bitmap-array)
	      (bitmap-array-height bitmap-array))))
      (copy-from-bitmap-array-to-character-bitmap
	bitmap-array
	(jis-to-contiguous jis-character-code)
	character-bitmap
	(bitmap-array-width bitmap-array)
	(bitmap-array-height bitmap-array))
      (print-character-bitmap
	character-bitmap
	(bitmap-array-width bitmap-array)
	(bitmap-array-height bitmap-array)))))



(defun print-font-character-bitmap
    (character-code &optional ab-font-or-font-name)
  (let* ((ab-font
	   (if (symbolp ab-font-or-font-name)
	       (ab-font (or ab-font-or-font-name 'kanji16)) ; hack
	       ab-font-or-font-name))
	 (character-description
	   (get-character-description-if-any character-code ab-font)))
    (print-character-bitmap
      (if (not-a-character-rectangle-array-but-a-bitmap-p
	    character-description)
	  character-description
	  (convert-character-rectangle-array-to-character-bitmap
	    character-description)))))

;; ex. (print-font-character-bitmap (char-code #\A) 'hm14)
;;   - prints an A in font HM15
;; ex. (print-font-character-bitmap (+ #x2330))
;;   - prints a 0 (zero) in KANJI16
;; ex. (print-font-character-bitmap #x3121)
;;   - prints what seems to be a Kanji letter in KANJI16
;; 
;; Note that a Kanji font must be loaded for this to work; they're
;; not loaded at load time, only at run time.


(defun print-font-bitmaps-to-file (b)
  (with-open-file (*standard-output* "/tmp/fc.text" :direction :output)
    (loop for i from #x2121 to 65000
      when (jis-to-contiguous i)
	do (format t "~%~%#x~x [~d]" i (hex-to-kuten i))
	   (print-font-character-bitmap i 'kanji16)
	   (format t "~%---")
	   (print-bitmap-array-jis-character b i))))

)



;;; `Load-bitmap-font-data-if-necessary' tries to load the appropriate
;;; bitmap font data for ab-font, or possibly a subset of it sufficient
;;; to allow the rendering of character-code.
;;;
;;; At present, this is only known to work (or to be needed) for Asian
;;; fonts, i.e., KANJI16 and KANJI24.
;;;
;;; Note that character-code is a gensym character code.  Gensym-jis codes are
;;; identical to standard JIS codes, but gensym-ksc codes are offset in the
;;; lower 8 bits from standard KSC codes.  See CHARACTERS for these definitions.

(def-suite-for-loading-file-at-launch-time kanji_* tw
  :base-name-of-file-to-load   "kanji_0"
  :type-of-file-to-load        "gb"
  :command-line-keyword        "kanji_fontfile"
  :environment-variable-name   "KANJI_FONTFILE"
  :base-name-of-disabling-file "NOG2KANJIFONTFILE"
  :type-of-disabling-file      "CMD"
  :module telestubs)


(def-suite-for-loading-file-at-launch-time kanji_* g2
  :base-name-of-file-to-load   "kanji_0"
  :type-of-file-to-load        "gb"
  :command-line-keyword        "kanji_fontfile"
  :environment-variable-name   "KANJI_FONTFILE"
  :base-name-of-disabling-file "NOG2KANJIFONTFILE"
  :type-of-disabling-file      "CMD"
  :module telestubs)

(def-suite-for-loading-file-at-launch-time hangul_* tw
  :base-name-of-file-to-load   "hangul_0"
  :type-of-file-to-load        "gb"
  :command-line-keyword        "hangul_fontfile"
  :environment-variable-name   "HANGUL_FONTFILE"
  :base-name-of-disabling-file "NOG2HANGULFONTFILE"
  :type-of-disabling-file      "CMD"
  :module telestubs)


(def-suite-for-loading-file-at-launch-time hangul_* g2
  :base-name-of-file-to-load   "hangul_0"
  :type-of-file-to-load        "gb"
  :command-line-keyword        "hangul_fontfile"
  :environment-variable-name   "HANGUL_FONTFILE"
  :base-name-of-disabling-file "NOG2HANGULFONTFILE"
  :type-of-disabling-file      "CMD"
  :module telestubs)

;; I believe the above is obsolete and/or not related to the new Chinese
;; truetype font offering. (MHD 4/9/99)




;;; `Asian-bitmap-subfont-data-info' ...
;;;
;;; Names of font files have the form
;;;
;;;    c|j|k<size>_<section>
;;;
;;; e.g., j16_0, k24_2, etc.
;;;
;;; Note that hyphens are not legal in the (minimum) standard for CD file names.
;;; Therefore, we use underscores instead, even avoid these whenever reasonable.
;;; Here, we just use them to separate the two numbers in the name, size and
;;; section number; further efforts to get rid of them are obviously possible,
;;; but "beyond the call of duty".

(defparameter asian-bitmap-subfont-data-info
  `((japanese 16 ,jis-symbols-1-start ,jis-level-1-kanji-start kanji j16_0 kanji16 kanji16
	      #+development "Japanese Font Size 16 Symbols")
    (japanese 16 ,jis-level-1-kanji-start ,jis-level-2-kanji-start kanji j16_1 kanji16 kanji16
	      #+development "Japanese Font Size 16 JIS Level 1")
    (japanese 16 ,jis-level-2-kanji-start ,jis-undefined-start kanji j16_2 kanji16 kanji16
	      #+development "Japanese Font Size 16 JIS Level 2")

    (japanese 24 ,jis-symbols-1-start ,jis-level-1-kanji-start kanji j24_0 kanji24 kanji24
	      #+development "Japanese Font Size 24 Symbols")
    (japanese 24 ,jis-level-1-kanji-start ,jis-level-2-kanji-start kanji j24_1 kanji24 kanji24
	      #+development "Japanese Font Size 24 JIS Level 1")
    (japanese 24 ,jis-level-2-kanji-start ,jis-undefined-start kanji j24_2 kanji24 kanji24
	      #+development "Japanese Font Size 24 JIS Level 2")

    (korean 16 ,ksc-symbols-1-start ,ksc-hangul-start hangul k16_0 kanji16 hangul16
	    #+development "Korean Font Size 16 Symbols")
    (korean 16 ,ksc-hangul-start ,ksc-hanja-start hangul k16_1 kanji16 hangul16
	    #+development "Korean Font Size 16 Hangul")
    (korean 16 ,ksc-hanja-start ,ksc-undefined-start hangul k16_2 kanji16 hangul16
	    #+development "Korean Font Size 16 Hanja")

    (korean 24 ,ksc-symbols-1-start ,ksc-hangul-start hangul k24_0 kanji24 hangul24
	    #+development "Korean Font Size 24 Symbols")
    (korean 24 ,ksc-hangul-start ,ksc-hanja-start hangul k24_1 kanji24 hangul24
	    #+development "Korean Font Size 24 Hangul")
    (korean 24 ,ksc-hanja-start ,ksc-undefined-start hangul k24_2 kanji24 hangul24
	    #+development "Korean Font Size 24 Hanja")

    ;; not using Chinese fonts with legacy encodings
    ))

;; The final field is for descriptive purposes only.  


;;; `Get-asian-subfont-information-for-character' returns either nil or
;;; the following 8 values:
;;;
;;;     (1) subfont-name as a symbol;
;;;     (2) the index in subfont's bitmap array for this character;
;;;     (3) the font size;
;;;     (4) the number of characters in subfont;
;;;     (5) the alphabet for this language (e.g., KANJI); 
;;;     (6) the ab-font-name for the ab-font this data gets stored in memory;
;;;     (7) the language for this character (e.g., JAPANESE); and
;;;     (8) the contiguous code for this character in this language
;;;
;;; For a legal Gensym Asian character code, this always returns non-nil;
;;; otherwise, this returns nil.  Note that new legal Asian characters will be
;;; defined from time to time in the future.
;;;     
;;; Examples:
;;; 
;;;   (get-asian-subfont-information-for-character (ab-font 'kanji16) #x2121)
;;;   
;;;    => J16_0 0 16 524 JAPANESE KANJI 0
;;;
;;;    
;;;   (get-asian-subfont-information-for-character (ab-font 'kanji16) #x217f)
;;;   
;;;    => K16_0 0 16 524 KOREAN HANGUL 0
;;;
;;; Note that at present, it may be assumed that all Asian fonts are fixed-width
;;; type fonts. In addition, they may be assumed to have square rectangles,
;;; i.e., they all have square fixed-size bounding boxes of dimensions "size"
;;; wide by "size" tall, e.g., 16x16 for size = 16.

(defun get-asian-subfont-information-for-character (ab-font character-code)
  (let ((size-for-this-font (ab-font-size ab-font))
	(language-for-this-code?
	  (map-character-code-to-asian-language character-code)))
    (when language-for-this-code?
      (loop with contiguous-code-for-this-code
	      = (map-gensym-character-code-to-contiguous-code
		  character-code language-for-this-code?)
	    for (language size start end alphabet subfont-name ab-font-name)
	      in asian-bitmap-subfont-data-info
	    when (and (eq language-for-this-code? language)
		      (eq size-for-this-font size)
		      (<=f start contiguous-code-for-this-code)
		      (<f contiguous-code-for-this-code end))
	      return (values
		       subfont-name
		       (-f contiguous-code-for-this-code start)
		       size
		       (-f end start)
		       alphabet
		       ab-font-name
		       language
		       contiguous-code-for-this-code)))))


(defun-allowing-unwind read-asian-bitmap-font-data-from-file
    (subfont-name alphabet size number)
  (let ((gensym-pathname?
	  (get-asian-bitmap-font-file-pathname
	    subfont-name alphabet size number)))
    (when gensym-pathname?
      (read-bitmap-array-from-file gensym-pathname? number size))))

(defun-allowing-unwind read-bitmap-array-from-file
    (gensym-pathname number size)
  (with-open-bitmap-array-file (stream gensym-pathname)
    (read-bitmap-array-from-stream stream number size size)))

(def-global-property-name lowercase-symbol-name)

(defun get-lowercase-symbol-name (symbol)
  (or (lowercase-symbol-name symbol)
      (setf (lowercase-symbol-name symbol)
	    (copy-text-string-with-case-conversion
	      (symbol-name-text-string symbol)
	      ':none))))

(defun get-asian-bitmap-font-file-pathname (subfont-name alphabet size number)
  (declare (ignore size number))
  (let* ((gensym-pathname
	   (gensym-make-pathname
	     :name (get-lowercase-symbol-name subfont-name)
	     :defaults (get-asian-font-file-name alphabet)))
	 (probed-gensym-pathname?
	   (gensym-probe-file gensym-pathname)))
    (when (and probed-gensym-pathname?
	       ;; check to see it's the right size! (use size, number)
	       )
      (prog1 probed-gensym-pathname?
	(reclaim-gensym-pathname gensym-pathname)))))


;;; `Load-bitmap-font-data-if-necessary' ... takes an ab-font, a unicode, and as
;;; cjk-language? either NIL, JAPANESE, CHINESE, or KOREAN.  If the bitmap data
;;; for a font, or portion thereof, needs to be loaded for unicode, this does
;;; the job.  CJK-language? is used to disambiguate among CJK characters, which
;;; might come from two or more CJK fonts.  Each character's character
;;; description is stored according to its unicode code point.  [Prior to the
;;; revision pending 4/9/99 the character description was stored in the font
;;; according to its old Gensym Han character code. (MHD 4/9/99)]

(def-global-property-name bitmap-font-data-handle)

(defmacro load-bitmap-font-data-if-necessary (ab-font unicode cjk-language?)
  (avoiding-variable-capture (ab-font unicode cjk-language?)
    `(when (and ,cjk-language?
		(eq (ab-font-type ab-font) 'kanji)
		(null (get-kanji-character-description-if-any
			,unicode
			(ab-font-character-description-table ,ab-font))))
       ;; first do an inline check to see if this is even an asian code, and, if
       ;; so, whether its "character description" (bitmap) is even missing; if
       ;; so, start all over after a function call
       (load-bitmap-font-data-if-necessary-1 ,ab-font ,unicode ,cjk-language?))))

(defun-simple load-bitmap-font-data-if-necessary-1
    (ab-font unicode cjk-language)
 (let (gensym-han-character-code)
  (when (setq gensym-han-character-code
	      (case cjk-language
		(korean
		 (or (map-unicode-to-gensym-ks-c-5601 unicode)
		     (map-unicode-to-gensym-jis-x-0208 unicode)))
		((japanese chinese)
		 ;; No Gensym han character code, and no bitmap, for Chinese at
		 ;; present, so just handle as for Japanese. (MHD 4/9/99)
		 (or (map-unicode-to-gensym-jis-x-0208 unicode)
		     (map-unicode-to-gensym-ks-c-5601 unicode)))))
   (multiple-value-bind
      (subfont-name index size number alphabet)
      (get-asian-subfont-information-for-character ab-font gensym-han-character-code)
    (when subfont-name
      (let ((bitmap-array?
	      (let ((handle? (bitmap-font-data-handle subfont-name)))
		(case handle?
		  ((:loading-failed)
		   nil)
		  ((nil)
		   (or (setf (bitmap-font-data-handle subfont-name)
			     (read-asian-bitmap-font-data-from-file
			       subfont-name alphabet size number))
		       (progn 
			 (setf (bitmap-font-data-handle subfont-name)
			       :loading-failed)
			 nil)))		  
		  (t handle?)))))
	(when bitmap-array?
	  (let ((character-bitmap
		  (allocate-character-bitmap size size)))
	    (copy-from-bitmap-array-to-character-bitmap
	      bitmap-array? index character-bitmap size size)
	    (set-kanji-character-description
	      unicode
	      (ab-font-character-description-table ab-font)
	      character-bitmap)))))))))

;; This ends up putting a copy of the bitmap data for character-code into a
;; character bitmap.  This is an unnecessary waste of storage.  It should be
;; possible to use the bitmap array directly to generate characters.  Doing
;; things this way causes the least disturbance to the rest of the software,
;; making it look just as it did when we used the GF files.  The cost to us if
;; all the Kanji codes are used is a more than doubling of the space
;; requirements.  For use of half the Kanji, space used remains reasonable
;; (i.e., better than under 3.0).  If possible, eliminate keeping this extra
;; copy before the final release! (MHD 1/13/95)




;;; Asian-font-file-loaded-p applies to Asian Gensym Font ("GF") font files,
;;; which are no longer used in the products G2 or Telewindows except for the
;;; purpose of creating the newer, but less informative, format Gensym Bitmap
;;; ("GB") font files.

(def-global-property-name asian-font-file-loaded-p)



;;; `Write-gensym-asian-bf-files' is the function used in development (by mhd)
;;; to generate the Gensym Bitmap (gb) Asian font files.  It currently generates
;;; these files in the directory /bt/mhd/lisp/fonts/.

#+font-files
(defun-allowing-unwind write-gensym-asian-bf-files ()
  (loop for (language size start end alphabet
		      subfont-name ab-font-name asian-font-name)
	    in asian-bitmap-subfont-data-info
	unless (asian-font-file-loaded-p asian-font-name)
	  do (read-asian-font-file asian-font-name)
	     (setf (asian-font-file-loaded-p asian-font-name) t)
	do (g2-stream-with-open-stream
	     (output-stream
	       (tformat-text-string "/bt/mhd/lisp/fonts/~(~a~).gb" subfont-name)
	       :direction :output)
	     (write-asian-font-to-file
	       language (ab-font ab-font-name) output-stream
	       :start start :end end))))









;;;; Gensym Bitmaps



;;; A `gensym bitmap' holds an array of bits.  You create one using
;;; make-gensym-bitmap, which produces a gensym bitmap with width columns, and
;;; height rows.  You access the bits with gensym-bitmap-bit-value, which gives
;;; the value at the intersection of row-index and column-index.  This accessor
;;; is setf'able, so you set a bit using, e.g.,
;;;
;;;   (setf (gensym-bitmap-bit-value x) 1)
;;;
;;; To view a whole bitmap on a terminal for debugging, use print-gensym-bitmap.
;;;
;;; To convert a gensym-bitmap to a character-rectangle array, use
;;; convert-gensym-bitmap-to-character-rectangle-array.  This allocates a
;;; vector of type character-rectangle-array, which has its own reclaiming
;;; interface.

(defun make-gensym-bitmap (width height)
  (make-bitmap-array 1 width height))

(defun reclaim-gensym-bitmap (gensym-bitmap)
  (reclaim-bitmap-array gensym-bitmap))

(defmacro gensym-bitmap-value (gensym-bitmap column-index row-index)
  `(bitmap-array-value ,gensym-bitmap 0 ,column-index ,row-index))

(defmacro gensym-bitmap-width (gensym-bitmap)
  `(bitmap-array-width ,gensym-bitmap))

(defmacro gensym-bitmap-height (gensym-bitmap)
  `(bitmap-array-height ,gensym-bitmap))

(defun copy-from-gensym-bitmap-to-character-bitmap
    (gensym-bitmap character-bitmap &optional width? height?)
  (copy-from-bitmap-array-to-character-bitmap
    gensym-bitmap 0 character-bitmap width? height?))

(defun convert-gensym-bitmap-to-rectangle-array (gensym-bitmap width? height?)
  (let* ((width (or width? (gensym-bitmap-width gensym-bitmap)))
	 (height (or height? (gensym-bitmap-height gensym-bitmap)))
	 (temporary-character-bitmap
	  (allocate-temporary-character-bitmap width height)))
    (copy-from-gensym-bitmap-to-character-bitmap
      gensym-bitmap temporary-character-bitmap width height)
    (prog1
	(convert-character-bitmap-to-rectangle-array
	  temporary-character-bitmap width height t)
      (reclaim-temporary-character-bitmap temporary-character-bitmap))))

(defun convert-gensym-bitmap-to-managed-rectangle-array (gensym-bitmap width? height?)
  (let* ((width (or width? (gensym-bitmap-width gensym-bitmap)))
	 (height (or height? (gensym-bitmap-height gensym-bitmap)))
	 (temporary-character-bitmap
	  (allocate-temporary-character-bitmap width height)))
    (copy-from-gensym-bitmap-to-character-bitmap
      gensym-bitmap temporary-character-bitmap width height)
    (prog1
	(convert-character-bitmap-to-managed-rectangle-array
	  temporary-character-bitmap width height t)
      (reclaim-temporary-character-bitmap temporary-character-bitmap))))

#+development
(defun print-gensym-bitmap (gensym-bitmap &optional width? height?)
  (let ((character-bitmap
	  (allocate-temporary-character-bitmap
	    (or width? (gensym-bitmap-width gensym-bitmap))
	    (or height? (gensym-bitmap-height gensym-bitmap)))))
    (copy-from-gensym-bitmap-to-character-bitmap
      gensym-bitmap character-bitmap
      (or width? (gensym-bitmap-width gensym-bitmap))
      (or height? (gensym-bitmap-height gensym-bitmap)))
    (print-character-bitmap
      character-bitmap
      (or width? (gensym-bitmap-width gensym-bitmap))
      (or height? (gensym-bitmap-height gensym-bitmap)))
    (reclaim-temporary-character-bitmap character-bitmap)
    nil))





;;;; Converting Character Rectangle Arrays to Character Bitmaps



;;; `Convert-character-rectangle-array-to-character-bitmap' ... returns a
;;; character bitmap.  If temporary? is true, this allocates the bitmap from a
;;; pool, i.e., using allocate-temporary-character-bitmap, and so it should
;;; presumably eventually be reclaimed using reclaim-temporary-character-bitmap.

(defun convert-character-rectangle-array-to-character-bitmap
       (character-description &optional temporary?)
  (loop with rectangle-array
	  = (character-rectangle-array character-description)
	with width = (bounding-box-width character-description)
	with height = (bounding-box-height character-description)
	with character-bitmap
	  = (if temporary?
		(allocate-temporary-character-bitmap width height)
		(allocate-character-bitmap width height))
	as y from 0 below height
	initially (fill-rectangle-in-character-bitmap
		    character-bitmap 0 0 0 width height)
	do (loop for i from 0 below (length rectangle-array)
		 as rectangle = (svref rectangle-array i)
		 when (and (<=f (top-edge-of-character-rectangle rectangle) y)
			   (<f y (bottom-edge-of-character-rectangle rectangle)))
		 do (loop for x
			      from (left-edge-of-character-rectangle rectangle)
			      below (right-edge-of-character-rectangle rectangle)
			  do (setf (character-bitmap-value character-bitmap x y)
				   1)))
	finally
	  (return character-bitmap)))





;;; `convert-character-bitmap-to-rectangle-array' converts
;;; character-bitmap, delimited by width? and height? if specified, into a
;;; character-rectangle array.  If ok-to-leave-blank? is true, this function
;;; leaves all bits cleared (0) in character-bitmap (in the area described by
;;; width? and height?, if specified); that saves a bit of time and so should be
;;; done if the character-bitmap will not needed again after calling this
;;; function.
;;;
;;; Ok-to-leave-blank? is documented for
;;; convert-character-bitmap-to-rectangle-list.

(defun convert-character-bitmap-to-rectangle-array
       (character-bitmap
	&optional width? height? ok-to-leave-blank?
	character-rectangle-array-to-fill?)
  (multiple-value-bind
      (character-rectangles number-of-character-rectangles)
      (convert-character-bitmap-to-rectangle-list
	character-bitmap
	width? height? ok-to-leave-blank?)
    (values
      (prog1
	  (if character-rectangle-array-to-fill?
	      ;; use replace?
	      (loop for character-rectangle in character-rectangles
		    as i from 0
		    do (setf (svref character-rectangle-array-to-fill? i)
			     character-rectangle)
		    finally (return character-rectangle-array-to-fill?))
	      (let ((vector
		      (if (=f number-of-character-rectangles 0)
			  '#()		; a (bug?) workaround
			  (allocate-managed-simple-vector
			    number-of-character-rectangles))))
		(loop for i from 0
		      for rectangle in character-rectangles
		      do (setf (svref vector i) rectangle))
		vector))
	(reclaim-gensym-list character-rectangles))
      number-of-character-rectangles)))


;;; `Convert-character-bitmap-to-managed-rectangle-array' converts
;;; character-bitmap into a managed array of character rectangles.  Other than
;;; the type of the first value -- a managed array instead of a simple vector,
;;; it is the same as convert-character-bitmap-to-rectangle-array.

(defun convert-character-bitmap-to-managed-rectangle-array
       (character-bitmap &optional width? height? ok-to-leave-blank?)
  (multiple-value-bind
      (character-rectangles number-of-character-rectangles)
      (convert-character-bitmap-to-rectangle-list
	character-bitmap
	width? height? ok-to-leave-blank?)
    (values
      (prog1
	  (loop with managed-array
		  = (allocate-managed-array number-of-character-rectangles)
		for character-rectangle in character-rectangles
		as i from 0
		do (setf (managed-svref managed-array i)
			 character-rectangle)
		finally (return managed-array))
	(reclaim-gensym-list character-rectangles))
      number-of-character-rectangles)))

;; Ask JRA to write a function copy-from-list-to-managed-array, and/or have
;; allocate-managed-array take an initial-contents argument! The replace the
;; loop above.  (MHD 12/17/93)



;;; `Convert-character-bitmap-to-rectangle-list' ... returns a list of freshly
;;; allocated gensym conses containing the character rectanges in
;;; character-bitmap.
;;;
;;; In the course of doing its work, it erases all of the bits in
;;; character-bitmap.  If ok-to-leave-blank? is true, those bits are not
;;; restored.

(defun convert-character-bitmap-to-rectangle-list
       (character-bitmap &optional width? height? ok-to-leave-blank?)
  (loop with minimum-left-edge? = nil
	with minimum-top-edge? = nil
	with maximum-right-edge fixnum = 0
	with maximum-bottom-edge fixnum = 0
	with bounding-box-width fixnum
	  = (or width? (character-bitmap-width character-bitmap))
	with bounding-box-height fixnum
	  = (or height? (character-bitmap-height character-bitmap))
	with x fixnum = 0
	with y fixnum = 0
	with number-of-character-rectangles fixnum = 0
	with character-rectangles = nil
	until (=f y bounding-box-height)
	do (loop for x0 fixnum from x below bounding-box-width
		 when (not (=f (character-bitmap-value character-bitmap x0 y) 0))	; not cleared?
		   do (setq minimum-left-edge?
			    (minf x0 (or minimum-left-edge? (1-f bounding-box-width))))
		      (setq minimum-top-edge?
			    (minf y (or minimum-top-edge? (1-f bounding-box-height))))
		      (loop for x1 fixnum = (1+f x0) then (1+f x1)
			    until (or (=f x1 bounding-box-width)
				      (=f (character-bitmap-value character-bitmap x1 y) 0))
			    finally
			      (setq x x1)
			      (loop for y1 = (1+f y) then (1+f y1) 
				    until
				      (or (=f y1 bounding-box-height)
					  (not (loop for x-check fixnum from x0 below x1
						     when (=f (character-bitmap-value
								character-bitmap
								x-check y1)
							      0)
						       return nil
						     finally (return t))))
				    finally
				      (setq maximum-right-edge
					    (maxf x1 maximum-right-edge))
				      (setq maximum-bottom-edge
					    (maxf y1 maximum-bottom-edge))
				      ;; clear rectangle (x0, y, x1, y1):
				      (fill-rectangle-in-character-bitmap
					character-bitmap 0 x0 y x1 y1)
				      (gensym-push
					(make-character-rectangle x0 y x1 y1)
					character-rectangles)
				      (incff number-of-character-rectangles)))
		      (return nil)
		 finally
		   (setq x 0)
		   (setq y (1+f y)))
	finally
	  (return
	    (values
	      (prog1
		  character-rectangles
		(unless ok-to-leave-blank?
		  (loop for character-rectangle in character-rectangles
			do (fill-rectangle-in-character-bitmap
			     character-bitmap
			     1
			     (left-edge-of-character-rectangle character-rectangle)
			     (top-edge-of-character-rectangle character-rectangle)
			     (right-edge-of-character-rectangle character-rectangle)
			     (bottom-edge-of-character-rectangle character-rectangle)))))
	      number-of-character-rectangles))))

;; The code above is based on compute-character-rectangles-per-current-
;; scratchpad-raster; that function and its callers could be converted to
;; use this instead.








;;;; Scaled Fonts



;;; A `scaled font' is a completely different structure from an ab font.  A scaled font
;;; belongs to a particular ab font and is used to cache all those images of characters
;;; in the ab font at a particular x and y scale.

;;; The scaled-font-character-image-cache slot contains, for a non-Kanji font, a non-kanji
;;; font vector of character images or nils, or, for a Kanji font, a kanji font cache
;;; vector of gensym-cons plist buckets having Kanji codes as indicators and character
;;; images as values.

;;; Scaled fonts are always created and decached within a non-icp (i.e, a system window)
;;; invocation of add-from-line-of-text-to-current-window, except that decaching may
;;; also occur while reclaiming the system window.  In any case, current-window may
;;; be assumed to be bound to the system window while creating or decaching scaled fonts.

(def-structure (scaled-font
		 (:constructor
		   make-scaled-font-internal
		   (scaled-font-x-scale
		    scaled-font-y-scale
		    scaled-font-character-image-cache
		    ab-font-for-scaled-font
		    gensym-window-for-scaled-font))
		 (:reclaimer reclaim-scaled-font-1)
		 (:include lru-element))
  scaled-font-x-scale
  scaled-font-y-scale
  (scaled-font-character-image-cache
    nil						; create structure here?
    :reclaimer reclaim-scaled-font-character-image-cache)
  ab-font-for-scaled-font
  gensym-window-for-scaled-font		; always the system window

  ;; new -- currently just used at full scale -- for native text drawing (i.e.,
  ;; via X); this either nil or a native-font structure
  (corresponding-native-font?
    nil :reclaimer reclaim-native-font-function)

  ;; These eight slots form bidirectional links between a roman font and its
  ;; corresponding complex-script font. Each roman font maps to at most one
  ;; complex font; however, multiple roman fonts can map to the same complex
  ;; font. For example, HM14 at 100% scale and HM18 at 85% scale both map to a
  ;; Kanji font at 85% scale. So the parent links must be lists. -fmw, 3/12/07
  (parents-of-cyrillic-scaled-font? nil)
  (parents-of-hebrew-scaled-font? nil)
  (parents-of-thai-scaled-font? nil)
  (parents-of-kanji-scaled-font? nil)

  (corresponding-cyrillic-scaled-font? nil)
  (corresponding-hebrew-scaled-font? nil)
  (corresponding-thai-scaled-font? nil)
  (corresponding-kanji-scaled-font? nil))

(defmacro snap-bidirectional-font-links (scaled-font parents-slot corresponding-font-slot)
  `(progn
     ;; Remove as child of all of our parents.
     (loop for parent in (,parents-slot ,scaled-font) doing
       #+development (assert-for-development (scaled-font-p parent))
       (setf (,corresponding-font-slot parent) nil))

     ;; Remove as parent of our child.
     (when (,corresponding-font-slot ,scaled-font)
       (setf (,parents-slot (,corresponding-font-slot ,scaled-font))
	     (delete-gensym-element ,scaled-font
				    (,parents-slot (,corresponding-font-slot ,scaled-font)))))
     (reclaim-gensym-list (,parents-slot ,scaled-font))
     (setf (,parents-slot ,scaled-font) nil)))

(defun reclaim-scaled-font (scaled-font)
  (snap-bidirectional-font-links scaled-font
				 parents-of-cyrillic-scaled-font? corresponding-cyrillic-scaled-font?)
  (snap-bidirectional-font-links scaled-font
				 parents-of-hebrew-scaled-font? corresponding-hebrew-scaled-font?)
  (snap-bidirectional-font-links scaled-font
				 parents-of-thai-scaled-font? corresponding-thai-scaled-font?)
  (snap-bidirectional-font-links scaled-font
				 parents-of-kanji-scaled-font? corresponding-kanji-scaled-font?)
  (reclaim-scaled-font-1 scaled-font))

#+development
(def-development-printer print-scaled-font (thing &optional (stream *standard-output*))
  (when (scaled-font-p thing)
    (printing-random-object (thing stream)
      (format stream "SCALED-FONT ~a ~d%~@[ Locked~]"
	      (and (ab-font-for-scaled-font thing)
		   (ab-font-name (ab-font-for-scaled-font thing)))
	      (round (scaled-font-x-scale thing) 40.96)
	      (and (null (lru-element-previous-element thing))
		   (null (lru-element-next-element thing)))))
    thing))

(define-decacheable-structure scaled-font 
    (make-scaled-font-internal
      scaled-font-x-scale
      scaled-font-y-scale
      scaled-font-character-image-cache
      ab-font-for-scaled-font
      gensym-window-for-scaled-font)
    compute-cost-of-decaching-scaled-font
    nil
    compute-size-of-scaled-font
    nil
    gensym-window-for-scaled-font
  (delete-scaled-font scaled-font))


;;; `Reclaim-all-scaled-fonts' ... used only in very rare circumstances, in
;;; under semi-panic conditions, to "GC" the scaled fonts in an effort to
;;; get enough rasters to continue operating.

(defun reclaim-all-scaled-fonts (&optional (verbally? t))
  (let ((count 0))
    (declare (type fixnum count))
    (do-lru-queue (element scaled-font-lru-queue)
      (incff count))
    (loop for scaled-font?
	      = (least-recently-used-lru-element scaled-font-lru-queue)
	  as counter from 1
	  while scaled-font?
	  do (decache-scaled-font scaled-font?)
	  when (>f counter count)	; should "never" happen
	    do (when verbally?
		 (notify-user-at-console
		   "~%Trouble deleting and reclaiming ~d scaled fonts!~%"
		   count))
	       (return nil)
	  finally
	    (when verbally?
	      (notify-user-at-console
		"~%Finished deleting ~d scaled fonts.~%" count))
	    (return t))
    ;; Now find any characters in scaled fonts "locked" out of the LRU queue:
    (let ((more-characters-reclaimed
	    (delete-character-images-in-scaled-fonts)))
      (when (and (>f more-characters-reclaimed 0)
		 verbally?)
	(notify-user-at-console
	  "~%Additional ~d character images deleted from locked scaled fonts.~%"
	  more-characters-reclaimed)))))
	  
	


;; Revise this to do reclamation!


(def-structure (large-scaled-font-bucket
		 (:constructor
		   make-large-scaled-font-bucket-internal
		   (parent-scaled-font-for-large-scaled-font-bucket
		     large-scaled-font-bucket-oriented-bucket-index))
		 (:include lru-element))
  (large-scaled-font-bucket-contents
    nil :reclaimer reclaim-large-scaled-font-bucket-contents)
  parent-scaled-font-for-large-scaled-font-bucket
  large-scaled-font-bucket-oriented-bucket-index
  #+development
  (time-of-creation-string
    (twith-output-to-text-string
      (multiple-value-bind (seconds minutes hours day month year)
	  (get-decoded-real-time)
	(declare (ignore day month year))
	(print-decoded-time-of-day
	  seconds minutes hours)))
    :reclaimer reclaim-text-string))

(define-decacheable-structure large-scaled-font-bucket
    (make-large-scaled-font-bucket-internal
      parent-scaled-font-for-large-scaled-font-bucket
      large-scaled-font-bucket-oriented-bucket-index)
    compute-cost-of-decaching-large-scaled-font-bucket
    nil
    compute-size-of-large-scaled-font-bucket
    nil
    nil					; See Note
  (delete-large-scaled-font-bucket large-scaled-font-bucket))

;; Note: conceivably, the implementation of G2/TW could change
;; to make window-specific structures necessary, but that's not
;; a requirement at present.  We always know which window we're
;; in and there can be only one window.



(defun-void delete-large-scaled-font-bucket (large-scaled-font-bucket)
  (let* ((scaled-font
	   (parent-scaled-font-for-large-scaled-font-bucket
	     large-scaled-font-bucket))
	 (index
	   (large-scaled-font-bucket-oriented-bucket-index
	     large-scaled-font-bucket)))
    (note-increase-in-size-of-scaled-font ; noting decrease here
      (-f (compute-size-of-large-scaled-font-bucket
	    large-scaled-font-bucket)))
    (setf (svref (scaled-font-character-image-cache scaled-font) index) nil))
  (reclaim-large-scaled-font-bucket large-scaled-font-bucket))

(defmacro do-large-scaled-font-bucket-character-images
    (((character-image-var font-code-var) large-scaled-font-bucket)
     &body body)
  (avoiding-variable-capture (&aux plist)
    `(loop with ,plist
	     = (large-scaled-font-bucket-contents ,large-scaled-font-bucket)
	   for (,font-code-var ,character-image-var) on ,plist by #'cddr
	   do (progn . ,body))))



(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter large-scaled-font-bucket-decaching-cost-constant
  1)					; 1 is nice and low; consider this cheap
)

(defun-simple compute-cost-of-decaching-large-scaled-font-bucket (large-scaled-font-bucket)
  large-scaled-font-bucket
  (*f #.large-scaled-font-bucket-decaching-cost-constant
      2000))				; see icon-rendering
	



;;; `Do-scaled-font-character-images' ... Note that body is expanded twice, and
;;; so should be kept reasonably small.  Note that body is evaluated once for
;;; each character-image in the cache, which may be zero, one, or two or more
;;; times.

(defmacro do-scaled-font-character-images
    (((character-image-variable cache-vector-index-variable bucket-variable?)
      scaled-font font-cache-vector &optional form-for-each-bucket-after-use?)
     &body body)
  (avoiding-variable-capture (scaled-font font-cache-vector &aux index bucket)
    (let ((bucket?-var (or bucket-variable? bucket)))
      `(case (ab-font-type (ab-font-for-scaled-font ,scaled-font))
	 (kanji
	  (loop as ,index from 0
			  below #.(kanji-font-cache-vector-length)
		as ,bucket?-var = (svref ,font-cache-vector ,index)
		when ,bucket?-var
		  do (do-large-scaled-font-bucket-character-images
			 ((,character-image-variable ,cache-vector-index-variable) ,bucket?-var)
		       . ,body)
		  ,@(when form-for-each-bucket-after-use?
		      `(,form-for-each-bucket-after-use?))))
	 (t (loop with ,character-image-variable
		  as ,cache-vector-index-variable from 0 below (length ,font-cache-vector)
		  do (when (setq ,character-image-variable
				 (svref ,font-cache-vector ,cache-vector-index-variable))
		       . ,body)))))))



(defparameter scaled-font-decaching-cost-constant 5)
;; Make machine specific!  
;; (use compute-cost-of-decaching-in-seconds-per-rectangle)



(defun-simple compute-cost-of-decaching-scaled-font (scaled-font)
  (*f scaled-font-decaching-cost-constant
      (let* ((ab-font (ab-font-for-scaled-font scaled-font))
	     (accumulated-cost 0))
	(declare (type fixnum accumulated-cost))
	(do-scaled-font-character-images
	    ((character-image font-code nil)
	     scaled-font
	     (scaled-font-character-image-cache scaled-font))
	  (incff accumulated-cost
		 (number-of-rectangles-for-character-image
		   character-image font-code ab-font)))
	accumulated-cost)))

;; The cost is proportional to the sum, over all character images in the scaled
;; font, of the length of its character rectangle array (from its character
;; description in the ab font).




;;; Compute-cost-of-decaching-in-seconds-per-rectangle is useful for
;;; computing scaled-font-decaching-cost-constant for various machines.  This
;;; constant is in units of seconds per character rectangle.
;;; Compute-cost-of-decaching-scaled-font multiplies this constant by the number
;;; of rectangles to determine cost to decache in seconds.  Because the cost
;;; constant is per character rectangle, it should not matter much which font is
;;; used, as long as the character has a "typical" number of rectangles.

;;; On the Micro-Explorer, the cost is
;;;   0.335 milliseconds per rectangle.

#+development
(defun compute-cost-of-decaching-in-seconds-per-rectangle 
       (scaled-font ab-font number-of-images)
  (let* ((current-window system-window)
	 (character-code (convert-simple-character-to-ascii #\a))
	 (number-of-rectangles-for-character-image
	   (number-of-rectangles-for-character-image 
	     nil character-code ab-font))
	 (total-number-of-rectangles
	   (* number-of-images number-of-rectangles-for-character-image))
	 begin-time end-time elapsed-time)
    (setq begin-time (get-fixnum-time))
    (loop for i from 1 to number-of-images
	  do (make-character-image-if-appropriate 
	       character-code 0 scaled-font ab-font))
    (setq end-time (get-fixnum-time))
    (setq elapsed-time (/ (fixnum-time-difference end-time begin-time)
			  fixnum-time-units-per-second-as-a-float))
    (format t "~%~%total number of rectangles = ~d~%" total-number-of-rectangles)
    (format t "seconds elapsed = ~s~%" elapsed-time)
    (format t "decaching cost in seconds per rectangle = ~s~%"
	    (/ elapsed-time
	       (coerce-to-gensym-float total-number-of-rectangles)))))
	       
;; The character "a" is used here as a good representative for the entire font.




(eval-when (:compile-toplevel :load-toplevel :execute)			; used in reader macro below
  (defmacro non-kanji-scaled-font-base-size ()
    #.(+ (* 13 4)			; 13 words for the scaled font structure (* 4 bytes/word)
	 (* (+ (largest-non-kanji-font-character-code)
	       1)			; number of character entries 	    
	    4)				; (* 4 bytes/word)
	 (* 1				; array header overhead
	    4)
	 )))




(eval-when (:compile-toplevel :load-toplevel :execute)			; used in reader macro below
  (defmacro kanji-scaled-font-base-size ()
    #.(+ (* 13 4)			; 13 words for the scaled font structure (* 4 bytes/word)
	 (*
	   #.(kanji-font-cache-vector-length) ; number of bucket entries
	   4)				; (* 4 bytes/word)
	 (* 1				; array header overhead
	    4)
	 )))



(defconstant large-scaled-font-bucket-base-size
  #.(* 4				; number of slot + 1 for structure overhead
       4))				; bytes per word

(defun-simple compute-size-of-scaled-font (scaled-font)
  (+f 
    (case (ab-font-type (ab-font-for-scaled-font scaled-font))
      (kanji #.(kanji-scaled-font-base-size))
      (t #.(non-kanji-scaled-font-base-size)))
    (let ((accumulated-size 0)
	  (accumulated-per-bucket-size 0)) ; only really needed in kanji case
      (declare (type fixnum accumulated-size))
      (do-scaled-font-character-images
	  ((character-image font-code nil)
	   scaled-font
	   (scaled-font-character-image-cache scaled-font)
	   (progn
	     (incff accumulated-size
		    (+f large-scaled-font-bucket-base-size
			(*f accumulated-per-bucket-size 4)))
	     (setq accumulated-per-bucket-size 0)))
	(incff accumulated-size
	       (compute-size-for-character-image character-image))
	(incff accumulated-per-bucket-size))
      accumulated-size)))



(defun-simple compute-true-size-of-scaled-font (scaled-font)
  (+f 
    (case (ab-font-type (ab-font-for-scaled-font scaled-font))
      (kanji #.(kanji-scaled-font-base-size))
      (t #.(non-kanji-scaled-font-base-size)))
    (let ((accumulated-true-size 0))
      (declare (type fixnum accumulated-true-size))
      (do-scaled-font-character-images
	  ((character-image font-code nil)
	   scaled-font
	   (scaled-font-character-image-cache scaled-font))
	(incff accumulated-true-size
	       (compute-true-size-for-character-image character-image)))
      accumulated-true-size)))

;; Make this be compute-size-of-scaled-font!





(defun-void delete-scaled-font (scaled-font)
  (let* ((ab-font (ab-font-for-scaled-font scaled-font))
	 (ab-font-cache-of-scaled-fonts
	   (ab-font-cache-of-scaled-fonts ab-font))
	 (image-cache
	   (scaled-font-character-image-cache scaled-font)))
    (case (ab-font-type ab-font)
      (kanji
       (loop as index from 0
		      below #.(kanji-font-cache-vector-length)
	     as bucket? = (svref image-cache index)
	     when bucket?
	       do (note-increase-in-size-of-large-scaled-font-bucket
		    (-f (compute-size-of-large-scaled-font-bucket
			  bucket?))))))	; noting decrease here
    (as-atomic-operation
      (setf (cdr ab-font-cache-of-scaled-fonts)
	    (delete-gensym-element
	      scaled-font (cdr ab-font-cache-of-scaled-fonts)))
      (if (eq (car ab-font-cache-of-scaled-fonts) scaled-font)
	  (setf (car ab-font-cache-of-scaled-fonts)
		(cadr ab-font-cache-of-scaled-fonts)))))
  (reclaim-scaled-font scaled-font))

;; Note that this can result in the ab-font-for-scaled-font slot being a list
;; of nil, which is ok.

;; Consider making delete-scaled-font resumeable, or only reclaiming a portion of it.
;; Some fonts (Kanji) could possibly take a long time to decache in certain cases!




;;; `Get-or-make-scaled-font' first looks for a font that has already been stored in ab-font
;;; with the correct x-scale and y-scale.  (See the definition above of ab-font.)  New
;;; scaled fonts are cached by destructively splicing them into this gensym list.

;;; `Get-or-make-scaled-font-with-lock' is does the same, but in addition, it
;;; `locks' the resulting scaled font against decaching (i.e., reclamation) by
;;; removing it from the LRU queue for scaled fonts.  A corresponding call to
;;; `unlock-scaled-font' must be made when the scaled font is safe to be
;;; decached.  `Lock-scaled-font' may be used on a scaled font to lock it.
;;; Note: it is harmless to call lock-scaled-font on an already-locked scaled
;;; font, and, similarly, it is harmless to call unlock-scaled-font on an
;;; already-unlocked scaled font.  The macro `with-locked-scaled-font' executes
;;; body with scaled-font locked (in an unwind-protect form), then unlocks
;;; scaled-font, and then returns the result of having executed body (returning
;;; any number of values).  The macro `with-locked-scaled-font-simple' is almost
;;; the same, but can only return one value, and does not unwind-protect the
;;; unlock form.

;;; Note that the use of dont-decache? provides a weak alternative to the use of
;;; locked scaled fonts.  By saying dont-decache, the caller effectively says
;;; that ALL scaled fonts are locked from decaching while this scaled font is
;;; being gotten.  If the caller(s) arrange, instead, to lock the one scaled
;;; font that typically should not be decached (i.e., the roman scaled font
;;; being used to lay out a line of text), then they can dispense with the
;;; dont-decache=t calling signature when getting associated scaled fonts, i.e.,
;;; for "kanji" fonts.  [We are switching to this calling discipline for G2
;;; 5.1. (MHD 8/19/98)]

(def-substitution-macro get-or-make-scaled-font (x-scale y-scale ab-font dont-decache?)
  (let ((scaled-font? (car (ab-font-cache-of-scaled-fonts ab-font))))
    (if (and scaled-font?
	     (=w (scaled-font-x-scale scaled-font?) x-scale)
	     (=w (scaled-font-y-scale scaled-font?) y-scale)
	     (eq (gensym-window-for-scaled-font scaled-font?) current-window))
	scaled-font?
	(get-or-make-scaled-font-1 x-scale y-scale ab-font dont-decache?))))

(def-substitution-macro get-or-make-scaled-font-with-lock (x-scale y-scale ab-font dont-decache?)
  (let ((scaled-font (get-or-make-scaled-font x-scale y-scale ab-font dont-decache?)))
    (lock-scaled-font scaled-font)
    scaled-font))

(def-substitution-macro lock-scaled-font (scaled-font)
  (as-atomic-operation
    (when (and (lru-element-previous-element scaled-font)
	       (lru-element-next-element scaled-font))
      (splice-out-lru-element scaled-font)
      (setf (lru-element-previous-element scaled-font) nil)
      (setf (lru-element-next-element scaled-font) nil))))

(def-substitution-macro unlock-scaled-font (scaled-font)
  (as-atomic-operation
    (unless (and (lru-element-previous-element scaled-font)
		 (lru-element-next-element scaled-font))
      (install-lru-element-in-queue scaled-font scaled-font-lru-queue))))

(defmacro with-locked-scaled-font ((scaled-font) &body body)
  (avoiding-variable-capture (scaled-font)
    `(as-atomic-operation
       (unwind-protect
	    (progn
	      (lock-scaled-font ,scaled-font)
	      . ,body)
	 (unlock-scaled-font ,scaled-font)))))

(defmacro with-locked-scaled-font-simple ((scaled-font) &body body)
  (avoiding-variable-capture (scaled-font)
    `(as-atomic-operation
       (prog1
	    (progn
	      (lock-scaled-font ,scaled-font)
	      . ,body)
	 (unlock-scaled-font ,scaled-font)))))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant native-font-set-width-equivalence-table-size 256)
)

(defmacro def-vector-pool-for-native-font-set-width-equivalence-table ()
  `(def-vector-pool native-font-set-width-equivalence-table
       ,native-font-set-width-equivalence-table-size
     :element-type t :initial-element nil))

(def-vector-pool-for-native-font-set-width-equivalence-table)


(def-structure (native-font (:constructor make-native-font))
  native-font-c-pointer
  (native-font-set-width-equivalence-table
    (make-native-font-set-width-equivalence-table)
    :reclaimer reclaim-native-font-set-width-equivalence-table))

;; Fix reclamation to work at the C/X font level, or not to happen.  Right
;; now, as scaled fonts are reclaimed, the loaded fonts on the C side become
;; garbage, I think!! (MHD)


(defun reclaim-non-kanji-font-vector-function (non-kanji-font-vector-slot-value)
  (when non-kanji-font-vector-slot-value
    (reclaim-non-kanji-font-vector non-kanji-font-vector-slot-value)))

(defun reclaim-native-font-function (native-font-slot-value)
  (when native-font-slot-value
    (reclaim-native-font native-font-slot-value)))

;; These handle nil as a slot-value, so they're a little special.


;;; The feature "Native-x-Fonts" is attempting to use native X fonts on X Window
;;; System implementations of G2.  This is a relatively new feature.  It was
;;; until 5/8/97 on in MHD's sandbox only, and off for all others.  It is now
;;; enabled by default for all platforms.

;;; If fonts are available under X Windows (e.g.,
;;; -Adobe-Helvetica-Medium-R-Normal--14-140-75-75-P-77-ISO8859-1), they will be
;;; used where their character spacing can be seen to match.  If they are not
;;; available, or don't match, then the traditional renderer will be used, and
;;; this may be more or less unnoticably slower, depending on the X implementation
;;; and the configuration of networks and nodes currently in use.
;;;
;;; This feature may be disabled through a new command line argument,
;;; no-native-fonts, which turns off the feature entirely.  One use for this is
;;; on a system which has bad or incorrectly interpreted font data; this has
;;; been seen, for example, on some X emulators.  Note that the name of this
;;; argument leaves out mention of the X Window System; this is done
;;; intentionally in order to leave open the possibility that we would implment
;;; this for other platforms, i.e., Windows, even though this is not done today.

;;; The system variable `enable-native-fonts?' enables the native fonts
;;; facility.  It is on unless the command line flag argument "no-native-fonts"
;;; is specified.
;;;
;;; Note that numerous other conditions determine whether they will be used.
;;; See (meta-.) no-native-fonts for details.
;;;
;;; `Native-fonts' is defined in development only.  It toggles native-fonts on
;;; or off if no argument is provided. When the optional arg is provided, it
;;; turns them on if the arg is true, and off otherwise.

(def-system-variable enable-native-fonts? fonts
  (:funcall check-if-native-fonts-enabled))

(defun check-if-native-fonts-enabled ()
  (and (getf command-line-arguments 'native-fonts)
       (not (getf command-line-arguments 'no-native-fonts))))

#+development
(defun native-fonts (&optional on-or-off?)
  (setq enable-native-fonts? 
	(case on-or-off?
	  (on t)
	  (off nil)
	  (t (not enable-native-fonts?))))
  (decache-font-bitmaps)
  (format t "~%Native Fonts ~a" (if enable-native-fonts? 'on 'off))
  enable-native-fonts?)


(defun initialize-native-font-set-width-equivalence-table (native-font)
  (loop with table = (native-font-set-width-equivalence-table native-font)
	for c from 33 to 255 ; kludge!
	do (setf (svref table c)
		 (not (member (code-char c)
			      '(#\space ; usually different, but could  
					;   maybe be rigged someday
				#\- ; this is much wider, I've noticed
				#\"
				;; this is not strictly a width
				;; problem, so it would not be
				;; detected by as an exception by
				;; automatic means: this is the
				;; same width, but it's wierd: it
				;; looks like a left-curly double
				;; quote, rather than an ascii
				;; straightdouble vertical double
				;; quote consider allowing back?
				;; (it would be cute as an earmark
				;; in development, at least...)
				)))
		 ;; Kludge: this ain't working! c-x11-get-character-set-width
		 ;; returns only 5 or 0 all the time.
;			      (=f (c-x11-get-character-set-width
;				    c font-or-error-flag)
;				  (text-width-to-x ; must check for 0 fraction bits!
;				    (get-set-width-for-character
;				      (code-char c)
;				      (ab-font-for-scaled-font new-scaled-font))))
		 )))




(defun-simple make-native-font-if-appropriate
    (new-scaled-font x-scale y-scale ab-font-type ab-font)
  ;; Hook up to X windows font, if easy (only if this feature
  ;; is enabled, if full scale, roman font, X Windows, etc.)  
  (when (and enable-native-fonts?
	     (eq type-of-current-window 'x11-window)
	     (=f x-scale (normalized-scale))
	     (=f y-scale (normalized-scale))
	     (not (eq ab-font-type 'kanji)))
    (let* ((x-font-spec?
	     (map-to-x-font (ab-font-name ab-font))))
      (when x-font-spec?
	(let ((font-or-error-flag
		(c-x11-allocate-x-font
		  (native-window? (gensym-window-for-scaled-font new-scaled-font))
		  x-font-spec?)))
	  (cond
	    ((<f font-or-error-flag 0)
	     nil)
	    (t
	     (let ((native-font (make-native-font)))
	       (setf (native-font-c-pointer native-font) font-or-error-flag)
	       (initialize-native-font-set-width-equivalence-table native-font)
	       (setf (corresponding-native-font? new-scaled-font)
		     native-font)))))))))


(defun-simple get-or-make-scaled-font-1 (x-scale y-scale ab-font dont-decache?)
  (setf (car (ab-font-cache-of-scaled-fonts ab-font))
	(loop for scaled-font in (cdr (ab-font-cache-of-scaled-fonts ab-font))
	      until (<w (scaled-font-x-scale scaled-font) x-scale)
	      when (and (=w (scaled-font-x-scale scaled-font) x-scale)
			(=w (scaled-font-y-scale scaled-font) y-scale)
			(eq (gensym-window-for-scaled-font scaled-font) current-window))
		return scaled-font
	      finally
		(return
		  (let* ((ab-font-type (ab-font-type ab-font))
			 (new-scaled-font
			   (case ab-font-type
			     (kanji
			      (make-decacheable-scaled-font
				x-scale y-scale
				(make-scaled-font-kanji-font-cache-vector)
				ab-font
				current-window
				#.(kanji-scaled-font-base-size)
				dont-decache?))
			     (t
			      (make-decacheable-scaled-font
				x-scale y-scale
				(make-scaled-font-non-kanji-font-vector)
				ab-font
				current-window
				#.(non-kanji-scaled-font-base-size)
				dont-decache?)))))

		    (setf (corresponding-native-font? new-scaled-font)
			  (make-native-font-if-appropriate
			    new-scaled-font x-scale y-scale ab-font-type ab-font))
		    (loop as l-trailer = (ab-font-cache-of-scaled-fonts ab-font) then l
			  as l = (cdr l-trailer)
			  when (or (null l)
				   (<w (scaled-font-x-scale (car l)) x-scale))
			    return
			    (as-atomic-operation
			      (car (setf (cdr l-trailer)
					 (gensym-cons
					   new-scaled-font
					   (cdr l-trailer)))))))))))

;; Note that make-decacheable-scaled-font can call delete-scaled-font which
;; can change the ab-font-cache-of-scaled-fonts slot of ab-font.  Therefore,
;; make-decacheable-scaled-font must be called outside of code which
;; inserts the new scaled font into this list.



;;;; Character Images



;;; A `character image' is like a character description but is scale-specific.  It
;;; contains a raster and text width for the character.

;;; Keeping a text width in a character image eliminates the need to scale each character
;;; individually.  (The set widths in ab fonts are for normalized-scale characters.)


(def-structure (character-image
		 (:constructor
		   make-character-image
		   (character-raster
		    character-image-set-width-as-text-width
		    character-image-text-x-offset
		    character-image-y-offset
		    character-image-width
		    character-image-height
		    character-image-orientation-code)))
  (character-raster
    nil						; create structure here?
    :reclaimer reclaim-character-raster)
  character-image-set-width-as-text-width

  character-image-text-x-offset
  character-image-y-offset
  character-image-width
  character-image-height
  character-image-orientation-code
  ;; above 4 slots replace these 4:  (MHD 9/13/93)
;  character-image-bounding-box-left-edge
;  character-image-bounding-box-top-edge
;  character-image-bounding-box-right-edge
;  character-image-bounding-box-bottom-edge
  )

;; Consider combining the 4 edge slots into 2.

;; Consider adding character-code and character-image-link slots so that the scaled-font-
;; character-image-cache slot of a Kanji scaled font need can hold linked character
;; images rather than a plist, to save a bit of space.


(defun get-reflection-and-rotation-from-orientation-code (orientation-code)
  (case orientation-code
    (0 'normal)
    (1 'clockwise-90)
    (2 'clockwise-180)
    (3 'clockwise-270)
    (4 'reflected)
    (5 'reflected-clockwise-90)
    (6 'reflected-clockwise-180)
    (7 'reflected-clockwise-270)
    (t 'normal)))

(defun-simple get-orientation-code (orientation)
  (case orientation
    (normal 0)
    (clockwise-90 1)
    (clockwise-180 2)
    (clockwise-270 3)
    (reflected  4)
    (reflected-clockwise-90 5)
    (reflected-clockwise-180 6)
    (reflected-clockwise-270 7)
    (t 0)))

(defun oriented-x-value (x y orientation-code)
  (case orientation-code
    ((0 2 4 6) x)
    ((1 3 5 7) y)))

(defun oriented-y-value (x y orientation-code)
  (case orientation-code
    ((0 2 4 6) y)
    ((1 3 5 7) x)))


(defun-simple number-of-rectangles-for-character-image
    (character-image character-code ab-font)
  (declare (ignore character-image))
  (let ((character-description?
	  (get-character-description-if-any character-code ab-font)))
    (if character-description?
	(if (or (not-a-character-rectangle-array-but-a-bitmap-p
		  character-description?)
		(not-a-character-rectangle-array-but-a-bitmap-p
		  (character-rectangle-array character-description?)))
	    25					; Kludge (average for Kanji)
	    (length (character-rectangle-array character-description?)))
	0)))

;; Review the efficiency issues here!!! (MHD 10/14/91)


(defconstant kanji-character-entry-base-size
  #.(* 4				; words used for a plist entry
       8))				; bytes per word

(defconstant character-image-base-size
  #.(* 8				; structure overhead plus 7 slots
       4))				; bytes per word

(defun-simple compute-size-for-character-image (character-image)
  (+f character-image-base-size
      (ceilingf
	(maxr 1
	      (*r (character-image-width character-image)
		  (character-image-height character-image)))
	8)))



(defun-simple compute-true-size-for-character-image (character-image)
  (maxr 1
	(roundr 
	  (*r (character-image-width character-image)
	      (character-image-height character-image))
	  32)))

;; Make this be compute-size-for-character-image!
;; Also include size of character image structure!



(defun-void reclaim-character-raster (character-raster)
  (let ((width (character-image-width structure-being-reclaimed))
	(height  (character-image-height structure-being-reclaimed))
	(orientation-code (character-image-orientation-code structure-being-reclaimed)))
    (reclaim-stored-raster
      character-raster current-window
      (maxr 1 (oriented-x-value width height orientation-code))
      (maxr 1 (oriented-y-value width height orientation-code))
      1 nil)))

;; Currently, the coordinates for computing the bounding box in a character image
;; are computed separately from the width and height of the character raster (see
;; make-character-image-if-appropriate, make-character-raster).  These
;; computations should be combined as they are redundant!  Also, there are some +r
;; and -r operators in make-character-image-if-appropriate that should actually be
;; +w and -w.  - agh 4/4/90



;;; Get-or-make-non-kanji-character-image-if-any returns a character image for the
;;; character in ab-font specified by character-code (and for the scale of scaled-font,
;;; which must belong to ab-font), if there is such a character in ab-font;
;;; otherwise, it returns nil.  Character images are cached by storing them in the
;;; character-code element of the non-kanji font vector kept as the
;;; scaled-font-character-image-cache slot of scaled-font.  This expands into fast
;;; in-line code if the character image already exists.

(def-substitution-macro get-or-make-non-kanji-character-image-if-any   ;pbk
			(character-code scaled-font ab-font orientation-code)
  (let ((oriented-character-code (+f character-code
				     (*f #.(largest-non-kanji-font-character-code)
					 orientation-code))))
    (or (svref (scaled-font-character-image-cache scaled-font) oriented-character-code)
	(setf (svref (scaled-font-character-image-cache scaled-font)
		     oriented-character-code)
	      (make-character-image-if-appropriate
		character-code orientation-code scaled-font ab-font))
;	(progn (format t "Weird ass non kanji case (could be the blob!)~%") nil)
	(svref (scaled-font-character-image-cache scaled-font) 0)
	(setf (svref (scaled-font-character-image-cache scaled-font) 0)
	      (make-character-image-if-appropriate 0 0 scaled-font ab-font)))))

;; This needs decaching logic!
;; added orientation (pbk) 12/8/95


(defun-simple map-halfwidth-to-fullwidth (unicode)
 (cond 
   ((<=f #x21 unicode #x7e)
    (cond 
          ((=f unicode #x22)
          #x201d) 
          ((=f unicode #x5c)
          #xffe5)
          ((=f unicode #x60)
          #x2018)
          ((=f unicode #x27)
          #x2019)
          (t
            (+f #xff01 (-f unicode #x21)))))
   ((<=f #xff61 unicode #xffdc) 
    (cond
    		 ;;;#xff61-ff64 is Halfwidth CJK punctuation
    		 ;;;#xff65-ff9f is Halfwidth Katakana variants
         ((=f unicode #xff61)
         #x3002)
         ((=f unicode #xff62)
         #x300c)
         ((=f unicode #xff63)
         #x300d)
         ((=f unicode #xff64)
         #x3001)
         ((=f unicode #xff65)
         #x30fb)
         ((=f unicode #xff66)
         #x30f2)
         ((<=f #xff67 unicode #xff6b)
          (+f #x30a1 (*f 2 (-f unicode #xff67))))
         ((<=f #xff6c unicode #xff6e)
          (+f #x30e3 (*f 2 (-f unicode #xff6c))))
         ((=f unicode #xff6f)
         #x30c3)
         ((=f unicode #xff70)
         #x30fc)
         ((<=f #xff71 unicode #xff75)
          (+f #x30a2 (*f 2 (-f unicode #xff71))))
         ((<=f #xff76 unicode #xff81)
          (+f #x30ab (*f 2 (-f unicode #xff76))))
         ((<=f #xff82 unicode #xff84)
          (+f #x30c4 (*f 2 (-f unicode #xff82))))  
         ((<=f #xff85 unicode #xff89)
          (+f #x30ca (-f unicode #xff85)))   
         ((<=f #xff8a unicode #xff8e)
          (+f #x30cf (*f 3 (-f unicode #xff8a))))  
         ((<=f #xff8f unicode #xff93)
          (+f #x30de (-f unicode #xff8f))) 
         ((<=f #xff94 unicode #xff96)
          (+f #x30e4 (*f 2 (-f unicode #xff94)))) 
         ((<=f #xff97 unicode #xff9b)
          (+f #x30e9 (-f unicode #xff97))) 
         ((=f unicode #xff9c)
         #x30ef)    
         ((=f unicode #xff9d)
         #x30f3)
         ((=f unicode #xff9e)
         #x309b) 
         ((=f unicode #xff9f)
         #x309c)
         ;;;#ffa0-ffdc is halfwidth Hangul variants
         ((=f unicode #xffa0)
         #x3164)
         ((<=f #xffa1 unicode #xffbe)
          (+f #x3131 (-f unicode #xffa1)))
         ;;;#xffbf,#xffc0,#ffc1 reserved;
         ((<=f #xffbf unicode #xffc1)
         unicode)
         ((<=f #xffc2 unicode #xffcf)
          (+f #x314f (-f unicode #xffc2)))
         ((<=f #xffd0 unicode #xffd1)
         unicode)
         ((<=f #xffd2 unicode #xffd7)
          (+f #x315b (-f unicode #xffd2)))
         ((<=f #xffd8 unicode #xffd9)
         unicode)
         (t
          (+f #x3161 (-f unicode #xffda)))))
   (t unicode))) 

;;; Get-or-make-kanji-character-image-if-any returns a character image for the
;;; character in kanji-font specified by kanji-code (and for the scale of scaled-font,
;;; which must belong to kanji-font), if there is such a character in kanji-font;
;;; otherwise, it returns nil.  Character images are cached by storing them in the
;;; appropriate plist bucket of the kanji font cache vector kept as the
;;; scaled-font-character-image-cache slot of scaled-font.  This expands into fast
;;; in-line code if the character image already exists.

(defmacro get-or-make-kanji-character-image-if-any-macro
	  (kanji-code oriented-scaled-font kanji-font orientation-code)
  `(let* ((kanji-code ,kanji-code)
	 (oriented-scaled-font ,oriented-scaled-font)
	 (kanji-font ,kanji-font)
	 (orientation-code ,orientation-code)
	 (unicode? (map-halfwidth-to-fullwidth kanji-code)))

	 (declare (type fixnum unicode?))

     #+development
     (unless (kanji-scaled-font-p oriented-scaled-font)
       (cerror "Continue" "Corrupting ~s" oriented-scaled-font))

     (loop with scaled-font-character-image-cache
	     = (scaled-font-character-image-cache oriented-scaled-font)
	   with bucket-index
	     ;;= (modf kanji-code #.kanji-font-cache-sub-vector-length)
	     = (modf unicode? #.kanji-font-cache-sub-vector-length)
	   with oriented-bucket-index 
	     = (+f bucket-index
		   (*f #.kanji-font-cache-sub-vector-length orientation-code))
	   with bucket
	     = (or (svref scaled-font-character-image-cache oriented-bucket-index)
		   (setf (svref scaled-font-character-image-cache oriented-bucket-index)
			 (make-decacheable-large-scaled-font-bucket
			   oriented-scaled-font
			   oriented-bucket-index
			   large-scaled-font-bucket-base-size
			   nil)))
	   with bucket-plist
	     = (large-scaled-font-bucket-contents bucket)
	   as l on bucket-plist by 'cddr
	   when (=f (car l) unicode?)
	     return (cadr l)
	   finally
	     (return
	       (let ((character-image?	; see Note 1
		       (make-character-image-if-appropriate
			 unicode?
			 orientation-code
			 oriented-scaled-font kanji-font)))
		 (let ((delta kanji-character-entry-base-size))
		   (note-increase-in-size-of-large-scaled-font-bucket delta)
		   (note-increase-in-size-of-scaled-font delta))
		 (cond
		   (character-image?
		    ;; Note: changed this code to put the newer character images
		    ;; first. It's faster, and since they're LRU, it will likely
		    ;; be faster to access the next time.  (MHD 8/13/98)
		    (setf (large-scaled-font-bucket-contents bucket)
			  (fonts-cons
			    unicode?
			    (fonts-cons
			      character-image?
			      (large-scaled-font-bucket-contents bucket)))) ; See Note 3
		    character-image?)
		   (t			; see Note 2
		    (get-or-make-substitute-kanji-character-image
		      oriented-scaled-font
		      kanji-font
		      scaled-font-character-image-cache))))))))

;; Note 1: We used to check if japanese was (ever) authorized, but that was
;; really only necessary in the days when we shipped images with Kanji fonts
;; preloaded.  Now that don't preload "Kanji" fonts (including Korean/Hangul
;; fonts), but only load them upon authorization, that really is unnecesary.
;; The check had remained through the release of 3.0, rev. 0, really due to an
;; oversight.  (MHD 10/19/92) --- Update: what was really going on was that we
;; were using a sticky variable that never could be reset to tell if we were
;; authorized.  Thus, even if you were authorized and then became deauthorized,
;; you would remain able to use the font.  I'm not going to go back and fix this
;; here, but there should be logic elsewhere that notices this and FLUSHES the
;; font when DEauthorization happens.  (MHD 11/9/92)

;; Note 2: If there is no character image, get or make a blob -- either the
;; character does not exist, which more or less is an internal error, OR the
;; font has not been loaded, which currently only can happen for a Kanji font,
;; including a Korean/Hangul "kanji" font.

;; Note 3: do NOT use bucket-plist here; 99.999% of the time it's OK, but
;; it could be recycled via the call to make-character-image-if-appropriate if
;; it caused all buckets' contents to be reclaimed because we couldn't obtain a
;; new raster. (MHD 8/20/98)


(defun-simple get-or-make-substitute-kanji-character-image
    (oriented-scaled-font kanji-font scaled-font-character-image-cache)
  (loop with bucket
	  = (or (svref scaled-font-character-image-cache 0)		
		(setf (svref scaled-font-character-image-cache 0)
		      (make-decacheable-large-scaled-font-bucket
			oriented-scaled-font
			0 ; large-scaled-font-bucket-oriented-bucket-index
			large-scaled-font-bucket-base-size
			nil)))
	with bucket-plist = (large-scaled-font-bucket-contents bucket)
	as l on bucket-plist by 'cddr
	when (=f (car l) 0)
	  return (cadr l)
	finally
	  (return
	    (let ((character-image?
		    (make-character-image-if-appropriate
		      0 0 oriented-scaled-font kanji-font)))
	      (cond
		(character-image?
		 (setf (large-scaled-font-bucket-contents bucket)
		       (fonts-cons
			 0
			 (fonts-cons
			   character-image? ; See Note 3 above			   
			   (large-scaled-font-bucket-contents bucket))))
		 character-image?))))))


(defun-simple get-or-make-kanji-character-image-if-any
    (kanji-code oriented-scaled-font kanji-font orientation-code)
  (get-or-make-kanji-character-image-if-any-macro
    kanji-code oriented-scaled-font kanji-font orientation-code))







;;; `Get-or-make-character-image-if-any' ...

(defun-substitution-macro get-or-make-character-image-if-any
    (font-code orientation-code oriented-scaled-font ab-font)
  (case (ab-font-type ab-font)
    (kanji
     (get-or-make-kanji-character-image-if-any
       font-code oriented-scaled-font ab-font orientation-code))
    (t
     (get-or-make-non-kanji-character-image-if-any
       font-code oriented-scaled-font ab-font orientation-code))))


;; Added orientation (pbk) 12/7/95
;; oriented-scaled-font has oriented x-scale and y-scale but is still
;; upright with no reflection.  The actual reflection and rotation occurs
;; when the character is put into the raster, but we needed to "stretch"
;; the character in the correct direction according to the oriented x and
;; y scales. 


;;;; Parameters for Rasterization Preferences



;;; `Prefer-bitmap-to-scaled-outline-font-at-full-scale?' tells the character
;;; rasterizer to prefer the (presumably hand-tuned) bitmap to one generated
;;; from the outline description for the character. The default value for this
;;; is T.

(defvar prefer-bitmap-to-scaled-outline-font-at-full-scale? t)

;; I'm not satisfied enough with the quality of our Bitstream Outline fonts
;; to subject our users to them at full scale, where their expectations are
;; high.  For now, I shall keep them as before.  They do look a bit better
;; when using the built-in (or scaleable) set widths, so consider using them
;; then.  Also, see how then look if/when we use custom squeezing, and/or
;; alorithmic set-width adjustment, as LH and I have discusse.  (MHD 6/7/93)

(defvar prefer-bitmap-to-scaled-outline-font? nil)

;; Use this to force bitmaps to be made -- useful for comparing old
;; appearance to new.  It's conceivable that a user might want to
;; see how things looked "before" outline fonts, but I can't imagine
;; a good way put an interface on this parameter that doesn't drag
;; down the product -- OH, I've got it: they could use an old (3.0)
;; version of Telewindows, which will display using bitmap scaling.

(defvar always-impose-device-set-widths? nil)

;; This does an OK job.  Try it for a while.  Next thing to do:
;; factors on individual characters.  One could also try sliding
;; character's bounding box over a little within their set widths.
;; (This helps to ensure evenness of (vertical) stem widths vs.
;; scaling characters.)  (MHD 5/18/93)

(defvar only-impose-device-set-widths-to-squeeze? nil)

;; This will override the one above, and make device width imposition
;; only happen when the device width is narrower than the scaleable
;; width -- i.e., just in order to squeeze down, not to widen.
;; Using the above resulted sometimes in uneven stem widths.  This
;; seems to do the best job with our Helvetica font, all in all.
;; (MHD 6/21/93)
;; -- This still looks crummy at some scales.  E.g., using large
;; font (HM18) at scale 3867 (an infrequently occuring scale), you
;; get very uneven weights.  Try looking at the log-file-parameters
;; system table at this scale. (MHD 6/30/93)

(defvar prefer-bitmap-to-scaled-outline-if-matched-at-any-scale? t)

;; Use this to match, say, HM7 to HM14 at half-scale, and prefer that to
;; an outline-font-rendered bitmap.  Uses the function below to do the
;; matching.  Right now, it's not clear this helps that much -- probably
;; would if we used the designed-in device widths, but that could only
;; be done if we had a new font, say EXTRA-SMALL; you can't go and
;; make up new set widths down at this level.

;;; `Scale-at-or-below-which-to-prefer-jis-bitmaps?' may be either nil or a
;;; scale at which or below which bitmap scaling will be preferred to outline
;;; font scaling.  When this is nil, no preference is expressed.  However, note
;;; that bitmaps could still be used based on either the lack of availability of
;;; the outline font or based on some other parameter, i.e., prefer-bitmap-to-
;;; scaled-outline-font?.  This applies only to Japanese ("JIS") characters.

;;; `Scale-at-or-below-which-to-prefer-ksc-bitmaps?' works the same way, but
;;; applies to Korean ("KSC") characters. Currently, this is nil by default: we
;;; have no really good bitmaps for this case at present.

;;; Note that, at the layer below the AB font, the Japanese (JIS) character are
;;; implemented with a completely different font than the Korean (KSC)
;;; characters.

;;; Note that Chinese support is being added at this time, but that bitmap
;;; support is not being added or planned at this time.  (MHD 5/9/99)

(defparameter scale-at-or-below-which-to-prefer-jis-bitmaps? (normalized-scale))
(defparameter scale-at-or-below-which-to-prefer-ksc-bitmaps? nil)

;; Changed from (normalized-scale) to nil in the Korean case -- we now greatly
;; prefer, and are delivering and using for Korean-authorized products, the
;; outline font -- a good looking "Sans-serif-like" font, to our bitmap Korean
;; fonts, which were reportedly of low quality, and of a poor style for running
;; text. (MHD 3/19/98 For 5.0 Rev. 3)


;; Use this to cause the tuned bitmaps to be preferred at or below a certain
;; scale.  Right now, the Bitstream Jis outline font we use is not sufficiently
;; "hinted" to be usable at or below normalized scale.  At normalized scale, the
;; "tuned" (bitmap) font look much better.  This because it has much simpler
;; strokes.  The little nubs ("serifs") on most of the lines have been removed.
;; This makes it look simpler and cleaner.  It also makes it easier to scale.
;; The scaled bitstream rasters don't lose the nubs, and at small scales these
;; nubs end up grossly distorting the characters.  In principle, the Bitstream
;; Speedo font/Speedo rasterizer combination could (and should!) do these sorts
;; of simplifications, but they do not.  Since I don't feel we can afford to
;; degrade the type quality for our users, I see not choice but to continue to
;; provide the old bitmap fonts at the scales previously provided, and only to
;; use the new fonts for scales larger than normalized.



;;; Find-bitmap-font-match ... if the first value is nil, there is
;;; no match; otherwise, this return three (3) useful values:
;;;
;;;   (1) the matching ab-font structure;
;;;   (2) the x scale at which it is a match; and
;;;   (3) the y scale at which it is a match
;;;
;;; At present, this encapsulates a bunch font-specific customizations.
;;;
;;; Character-code is a font-code, which means it's a unicode in the case of a
;;; Kanji font, and a font-specific font code in case of a Latin or Cyrillic
;;; font.

(defun find-bitmap-font-match (font-name x-scale y-scale character-code)
  (case font-name
    ((hm14 hm18 hm24)
     (if (and (=f (twicef x-scale) (normalized-scale))
	      (=f (twicef y-scale) (normalized-scale)))
	 (values
	   (ab-font (case font-name (hm14 'hm7) (hm18 'hm9) (hm24 'hm12)))
	   (normalized-scale) (normalized-scale))))
    ((kanji16 kanji24)
     (cond
       ((and scale-at-or-below-which-to-prefer-jis-bitmaps?
	     (jis-unicode-p character-code))
	(if (and scale-at-or-below-which-to-prefer-jis-bitmaps?
		 (or (<=f x-scale scale-at-or-below-which-to-prefer-jis-bitmaps?)
		     (<=f y-scale scale-at-or-below-which-to-prefer-jis-bitmaps?)))
	    (values (ab-font font-name) x-scale y-scale)))
       ((and scale-at-or-below-which-to-prefer-ksc-bitmaps?
	     (ks-unicode-p character-code))
	(if (and scale-at-or-below-which-to-prefer-ksc-bitmaps?
		 (or (<=f x-scale scale-at-or-below-which-to-prefer-ksc-bitmaps?)
		     (<=f y-scale scale-at-or-below-which-to-prefer-ksc-bitmaps?)))
	    (values (ab-font font-name) x-scale y-scale)))))))

;; Generalize this (if it's to be used)!  Make more efficient?!  (macro?)
;; (MHD 6/21/93)


;;; `Get-cjk-language-of-unicode' returns either CHINESE, JAPANESE, KOREAN,
;;; corresponding to the language most associated with the unicode character, or
;;; NIL if it's not a CJK character at all.  Han-unification-mode-to-use, and
;;; other heuristics, are used to make choices if a character is traditionally
;;; used in more than one language.
;;;
;;; if han-unification-mode-to-use is Japanese or Korean, and a character is in
;;; a range considered ambiguous (e.g., especially, Han characters, AKA "CJK
;;; unified ideographs"), and a character is not defined in the primary Japanese
;;; or Korean character sets (JIX-X-0208 and KSC5601, respectively), then the
;;; result will be CHINESE.  This is done primarily in consideration of the fact
;;; that the Chinese repertoire of Han characters is the largest.
;;;
;;; Some additional heuristics are used, including to some extent the history of
;;; the G2 product's language support features: i.e., Japanese first, Korean
;;; second, Chinese third.

(def-substitution-macro get-cjk-language-of-unicode-in-current-window
    (unicode)
  (cond
    ((<f unicode 256) 
     ;; trivial, quick check for possible Asianity
     nil)
    (t
     (get-cjk-language-of-unicode
       unicode 
       (get-font-han-unification-mode-for-window current-window)))))


(defun-simple get-cjk-language-of-unicode (unicode han-unification-mode-to-use)
  (cond
    ((or (<=f #xac00 unicode #xd7a3)	; hangul
	 (<=f #x3130 unicode #x318f)	; hangul compatibility jamo
	 )
     'korean)
    ((<=f #x4e00 unicode #x9fff)	; cjk unified ideographs (20,991 chars)
     (get-cjk-language-of-unicode-a unicode han-unification-mode-to-use)) ; see notes 1, 2
    ((or (<=f #x3000 unicode #x303f)	; cjk symbols and punctuation (including space)
         (<=f #x3200 unicode #x32ff)	; enclosed cjk letters and months
	 (<=f #x3300 unicode #x33ff)	; cjk compatibility
	 )				; See note 3
     (get-cjk-language-of-unicode-b unicode han-unification-mode-to-use))
    ((or (<=f #x3040 unicode #x309f)	; hiragana
	 (<=f #x30a0 unicode #x30ff)	; katakana
	 (<=f #x3190 unicode #x319f)	; kanbun
	 )
     'japanese)
    ((or (<=f #x3100 unicode #x312f)	; bopomofo
	 )
     'chinese)
    ((get-cjk-language-of-unicode-b unicode han-unification-mode-to-use))
    (t nil)))



;;; `Get-cjk-language-of-unicode-a' is called with a unicode for a CJK Ideograph
;;; ("Han") character.  It always returns a language, one of JAPANESE, CHINESE,
;;; or KOREAN.
;;;
;;; If the mode is Chinese, we just return that mode.  For Han unification mode
;;; of Japanese or Korean, we will return that mode as the result language if
;;; the character can be mapped to the respective national character set.
;;; Otherwise, for Korean, or null han-unification-mode-to-use, we prefer to
;;; return Japanese as long as it's a standard Japanese character (i.e., in
;;; JIS-X-0208).  This should remain the policy at least until we have a bitmap
;;; font, and/or have some assurance we won't be making any unwelcome changes to
;;; users' experience.  Probably the best fall-through would be to CHINESE, but
;;; (a) we don't have bitmap fonts for Chinese; (b) printing never worked with
;;; outline fonts; (c) it's different.  If the character doesn't map at all to
;;; Japanese, then we fall through to returning Chinese.

(defun-simple get-cjk-language-of-unicode-a (unicode han-unification-mode-to-use)
  (case han-unification-mode-to-use
    (korean			; see Note 1
     (if (map-unicode-to-gensym-ks-c-5601 unicode)
	 'korean
	 (if (map-unicode-to-gensym-jis-x-0208 unicode)
	     'japanese
	     'chinese)))
    (japanese			; see Note 2
     (if (map-unicode-to-gensym-jis-x-0208 unicode)
	 'japanese
	 (if (map-unicode-to-gensym-ks-c-5601 unicode)
	     'korean
	     'chinese)))
    (chinese
     'chinese)
    (t (if (map-unicode-to-gensym-jis-x-0208 unicode)
	   'japanese
	   'chinese))))



;;; `Get-cjk-language-of-unicode-b' is called with a unicode for a non-han
;;; character determined to be traditionally related to Asian character sets,
;;; e.g., enclosed CJK symbols, et al.  It may return a language or nil.
;;; Currently this favors Japanese if that cann 

(defun-simple get-cjk-language-of-unicode-b (unicode han-unification-mode-to-use)
  (declare (ignore han-unification-mode-to-use))
  (or (if (map-unicode-to-gensym-jis-x-0208 unicode) 'japanese)
      (if (map-unicode-to-gensym-ks-c-5601 unicode) 'korean)))

;; Notes below refer to differences between the shipping G2/TW and the version
;; for the revision pending as of 4/9/99.
;;
;; Note 1: If the CJK language is Korean, users will notice a change: (a) Han
;; characters used in KSC5601 were previously always rendered with the Japanese
;; font, but now they will be rendered in the Korean font; (b) Han characters
;; not in KSC5601 but in JISX0208 were previously rendered with the Japanese
;; font, but now they'll be rendered in the Chinese font; (c) Han characters not
;; in either the Japanese or Korean standard previously could not be rendered at
;; all, but now they can be rendered using the Chinese font.
;;
;; Note 2: If the CJK language is Japanese (which will be the case pretty much
;; by default), users will notice a change: Han characters not in either the
;; Japanese or Korean standard previously could not be rendered at all, but now
;; they can be rendered using the Chinese font.  As long as the CJK language is
;; Japanese, Han characters will be rendered using the Japanese font.  But if
;; the CJK language is Korean or Chinese, they will be rendered using either
;; Korean or Chinese fonts as appropriate, whereas previously they would have
;; always been rendered using the Japanese font.
;;
;; The Korean outline font has several non-Hangul, non-Han characters missing,
;; and for the ones it does have, there are quality problems at low scales:
;; e.g., the whole left vertical bar of the capital 'B' gets "dropped" at about
;; 10% below full scale.  In addition, the Japanese font has been up until now
;; been preferred even in cases where the Korean font should have had the
;; necessary glyph.  The Chinese font has few if any characters besides Han
;; characters.  For these reasons, and in light of our general desire to make
;; few changes, and our absolute horror at the thought of a regression, we will
;; continue to prefer the Japanese interpretation before the Korean one even if
;; the CJK language is Korean.  (Also, note that the code that previously did
;; this preferencing used the global han-interpretation-mode, which makes it
;; seem as though it would have caused a preferencing for the Korean
;; interpretation in some cases.  However, nothing in practice ever would cause
;; that global to be changed to any value, i.e., KOREAN, such that it would have
;; caused such a preferencing.
    

(defun-substitution-macro full-scale-bitmap-if-asian-ok-p (cjk-language?)
  (case cjk-language?
    (japanese
     (and scale-at-or-below-which-to-prefer-jis-bitmaps?
	  (>=f
	    scale-at-or-below-which-to-prefer-jis-bitmaps?
	    (normalized-scale))))
    (korean
     (and scale-at-or-below-which-to-prefer-ksc-bitmaps?
	  (>=f
	    scale-at-or-below-which-to-prefer-ksc-bitmaps?
	    (normalized-scale))))
    (chinese			; currently no bitmaps for Chinese
     nil)
    (t t)))


#+development
(progn
  (defparameter notify-on-font-raster-use? nil)
(defun report-font-raster-use (&optional really-just-turn-off?)
  (setq notify-on-font-raster-use? (if really-just-turn-off? nil t)))
(defparameter seconds-between-reports-of-total-rasters-in-use? 5)
(def-system-variable last-report-of-total-rasters-in-use? fonts nil)
(defparameter report-font-associated-pools-only-p t)
(defparameter font-associated-pools
  '(scaled-font-non-kanji-font-vector-2049-vectors
    scaled-font-kanji-font-cache-vector-1096-vectors
    graphics-conses gensym-conses byte-vector-conses))
(defun consider-reporting-total-rasters-in-use ()
  (when (and notify-on-font-raster-use?
	     seconds-between-reports-of-total-rasters-in-use?)
    (when (or (null last-report-of-total-rasters-in-use?)
	      (>=f (convert-fixnum-time-difference-to-seconds
		     (fixnum-time-difference
		       (get-fixnum-time)
		       last-report-of-total-rasters-in-use?))
		   seconds-between-reports-of-total-rasters-in-use?))
      (unless report-font-associated-pools-only-p
	(notify-user-at-console
	  "~%Stored rasters allocated total: ~d~%large-scaled-font bucket count: ~d~%scaled font count: ~d"
	  number-of-stored-rasters-allocated
	  (outstanding-large-scaled-font-bucket-count)
	  (outstanding-scaled-font-count))
	(notify-user-at-console "~%large-scaled-font-bucket-memory-limit-info:")
	(d large-scaled-font-bucket-memory-limit-info)
	(notify-user-at-console "~%scaled-font-memory-limit-info:")
	(d scaled-font-memory-limit-info))
      (terpri)
      (memory font-associated-pools)
      (setq last-report-of-total-rasters-in-use? (get-fixnum-time)))))
)

;;; Make-character-image-if-appropriate makes a character image for the character in
;;; ab-font specified by character-code (and for the scale of scaled-font), if there
;;; is a character description for that character in ab-font.  Otherwise, it returns nil.

;;; If kanji-font-case? is true, [as of the revision pending 4/9/99 (MHD
;;; 4/9/99)], character-code is a unicode, and the "Kanji font" will be used,
;;; although the character may or may not be an Asian character: it may just be
;;; a random Unicode character other than the ones supported in the Gensym Latin
;;; and Cyrillic character sets; otherwise, character-code is a Gensym character
;;; code (i.e., for a Gensym Latin or Cyrillic character).

(defun-simple get-font-han-unification-mode-for-window (gensym-window)
  (or
    ;; The new G2/Telewindows command line argument cjk-language is the most
    ;; directly supported way to preference one of the three languages:
    (cjk-typeface-preference-for-this-workstation?
      (workstation-this-is-on gensym-window))
    ;; I believe this only gets set from the G2/Telewindows command line, and
    ;; does not get updated based on changes to G2-window's language or the
    ;; language-parameters system table.  Consider adding an ICP message to
    ;; keep it up-to-date.
    (case (specific-language-for-this-workstation?
	    (workstation-this-is-on gensym-window))
      (japanese 'japanese)
      (chinese 'chinese)
      (korean 'korean))
    ;; Decide from G2 authorization: in most cases, there is only one of these
    ;; three languages authorized, in most cases it's for the language of the
    ;; user, and should therefore be a good default choice.
    (cond				; in order their support was added to G2
      ((or (japanese-authorized-p)
	   (if (eq current-system-name 'telewindows)
	       (telewindows-authorized-for-japanese-p gensym-window)))
       'japanese)
      ((or (korean-authorized-p) 
	   (if (eq current-system-name 'telewindows)
	       (telewindows-authorized-for-korean-p gensym-window)))
       'korean)
      ((or (chinese-authorized-p) 
	   (if (eq current-system-name 'telewindows)
	       (telewindows-authorized-for-chinese-p gensym-window)))
       'chinese))
    'japanese))			; Ultimate grandfathering: Japanese was 1st



;;; `Make-character-image-if-appropriate' .... Character-code is a font-code,
;;; which means it's a unicode in the case of a Kanji font, and a font-specific
;;; font code in case of a Latin or Cyrillic font.  This is called for making
;;; window-specific rasters for on-screen rendering.


(defun-simple make-character-image-if-appropriate
    (character-code orientation-code oriented-scaled-font ab-font)  
  (let* ((fixed-bounding-box-of-font?
	   (fixed-bounding-box-of-font? ab-font))
	 (character-description-or-rectangle-array?
	   ;; char. desc., rect. array, or bitmap; nil for unloaded "Kanji" char
	   (get-character-description-if-any character-code ab-font))
	 (rectangle-array-case?
	   (and fixed-bounding-box-of-font?
		(fixed-width-of-font? ab-font)))
	 (cjk-language?
	   (if (eq (ab-font-type ab-font) 'kanji) ; needed?
	       (get-cjk-language-of-unicode-in-current-window character-code))))
    (if (or character-description-or-rectangle-array?
	    fixed-bounding-box-of-font?)
	(let* ((oriented-x-scale (scaled-font-x-scale oriented-scaled-font))
	       (oriented-y-scale (scaled-font-y-scale oriented-scaled-font))
	       (text-width-for-character
		(text-width-for-character
		  character-description-or-rectangle-array? ab-font))
	       (character-image-set-width-as-text-width
		(delta-x-in-window text-width-for-character oriented-x-scale))
	       character-image-text-x-offset
	       character-image-y-offset
	       character-image-width
	       character-image-height
	       bitmap-data?
	       (revised-font-match? nil)  ; set in next/used in next binding
	       revised-font-match-x-scale revised-font-match-y-scale
	       (character-raster-from-revised-font? nil)
	       (dont-try-to-use-outline-font-p
		 (or (and (=f orientation-code 0) ; assume only upright bitmaps
			  (or prefer-bitmap-to-scaled-outline-font?
			      (and
				prefer-bitmap-to-scaled-outline-font-at-full-scale?
				(=f oriented-x-scale (normalized-scale))
				(=f oriented-y-scale (normalized-scale))
				;; Handle Asian exceptions, if any:
				(full-scale-bitmap-if-asian-ok-p cjk-language?))
			      (and prefer-bitmap-to-scaled-outline-if-matched-at-any-scale?
				   (multiple-value-setq
				       (revised-font-match?
					 revised-font-match-x-scale
					 revised-font-match-y-scale)
				     (find-bitmap-font-match
				       (ab-font-name ab-font)
				       oriented-x-scale oriented-y-scale
				       character-code))))
			  (or
			    character-description-or-rectangle-array?
			    (progn
			      (load-bitmap-font-data-if-necessary
				ab-font character-code cjk-language?)
			      (setq character-description-or-rectangle-array?
				    (get-character-description-if-any
				      character-code ab-font))))
			  (setq bitmap-data?
				(if rectangle-array-case?
				    character-description-or-rectangle-array?
				    (character-rectangle-array ; note: could also be a bitmap!
				      character-description-or-rectangle-array?))))
		     (and		; Thai bug fix! See note! (MHD 9/2/04)
		       (=f character-code #x5F)	; (font-code, not character-code!)
		       (memq (ab-font-name ab-font) '(thai14 thai18 thai24))
		       (<f oriented-x-scale 13000))))
	       (character-raster?
		 (or
		   (unless dont-try-to-use-outline-font-p
		       
		     ;; Irregular formatting follows here:   (!!!)
			    (let ((character-scaleable-text-width?
			     (unless rectangle-array-case?
			       (character-scaleable-text-width?
				 character-description-or-rectangle-array?))))
		       (multiple-value-bind
			   (character-raster? text-x-offset y-offset width height)
			   (make-raster-for-character-using-outline-font-if-possible
			   character-code orientation-code ab-font
			   (or (if (or always-impose-device-set-widths?
				       only-impose-device-set-widths-to-squeeze?)
				   ;; the idea is that, assuming we have the
				   ;; same scaleable width as the fontrip,
				   ;; we can do squeezing (or thickening) by
				   ;; adjusting the scale.  This may not always
				   ;; look pretty.
				   (if (and character-scaleable-text-width?
					    (not
					      (if only-impose-device-set-widths-to-squeeze?
						  (<=f character-scaleable-text-width?
						       text-width-for-character)
						  (=f character-scaleable-text-width?
						      text-width-for-character))))
				       (scale-scale
					 oriented-x-scale
					 text-width-for-character
					 character-scaleable-text-width?)))
			       oriented-x-scale)
			   oriented-y-scale cjk-language? nil)
			 (when character-raster?
			   (setq character-image-text-x-offset
			       ;; a better -- the best I now feel -- way to deal
			       ;; with imposed set widths -- just adjust the
			       ;; x offset by half the difference in the widths.
			       ;; This is now enabled when the other two
			       ;; squeezing parameters are nil. (MHD 9/14/93)
				 (if (and
				     character-scaleable-text-width?
				     (not (or always-impose-device-set-widths?
					      only-impose-device-set-widths-to-squeeze?))
					; true for now:  -- define this parameter: (!) (MHD 9/14/93)
					; only-adjust-x-offset-to-compensate-for-different-set-widths?
				     (not (=f character-scaleable-text-width?
					      text-width-for-character)))
				   (let ((adjustment
					   (halff (-f character-scaleable-text-width?
						      text-width-for-character))))
				     (-f text-x-offset adjustment))
				   text-x-offset))
			 (setq character-image-y-offset ; flip coordinate system
			       (-r (+r height y-offset)))
			 (setq character-image-width width)
			 (setq character-image-height height)
			 character-raster?))))
		 (if revised-font-match?
		     nil			 
		     (progn
		       (when (or bitmap-data?
				 ;; We now "lazily set" this variable, which might
				 ;; involve loading font data.  It might have been
				 ;; tried to be set earlier, but it's trivial to
				 ;; retry here, so we do.  (MHD 4/9/99)
				 (progn
				   (load-bitmap-font-data-if-necessary
				     ab-font character-code cjk-language?)
				   (setq character-description-or-rectangle-array?
					 (get-character-description-if-any
					   character-code ab-font))
				   (setq bitmap-data?
					 (if rectangle-array-case?
					     character-description-or-rectangle-array?
					     (character-rectangle-array ; note: could also be a bitmap!
					       character-description-or-rectangle-array?)))))
			 (let* ((bounding-box-x-offset
				  (if fixed-bounding-box-of-font?
				      (first fixed-bounding-box-of-font?)
				      (bounding-box-x-offset character-description-or-rectangle-array?)))
				(bounding-box-y-offset
				  (if fixed-bounding-box-of-font?
				      (second fixed-bounding-box-of-font?)
				      (bounding-box-y-offset character-description-or-rectangle-array?)))
				(bounding-box-width
				  (if fixed-bounding-box-of-font?
				      (third fixed-bounding-box-of-font?)
				      (bounding-box-width character-description-or-rectangle-array?)))
				(bounding-box-height
				  (if fixed-bounding-box-of-font?
				      (fourth fixed-bounding-box-of-font?)
				      (bounding-box-height character-description-or-rectangle-array?))))
			   (setq character-image-text-x-offset 
				 (delta-x-in-window
				   (convert-to-text-width bounding-box-x-offset)
				   oriented-x-scale))
			   (setq character-image-y-offset
				 (delta-y-in-window
				   (-r (+r bounding-box-y-offset bounding-box-height))
				   oriented-y-scale))
			   (multiple-value-setq-some
			       (nil character-image-width character-image-height)
			       (make-character-raster
				 oriented-scaled-font
				 orientation-code
				 bitmap-data?
				 bounding-box-x-offset bounding-box-y-offset
				 bounding-box-width bounding-box-height
				 nil))))))))
	       (new-character-image?
		 (if revised-font-match?
		     (let* ((prefer-bitmap-to-scaled-outline-if-matched-at-any-scale?
			      nil)
			    (prefer-bitmap-to-scaled-outline-font? t)
			    (revised-scaled-font
			      (get-or-make-scaled-font
				revised-font-match-x-scale
				revised-font-match-y-scale
				revised-font-match?
				nil)))	; allow decache, assuming parent s.f. is locked
		       (let ((revised-character-image?
			       ;; Locking approach same as for
			       ;; get-or-make-kanji-character-image, q.v., for
			       ;; note. (MHD 8/19/98)
			       (with-locked-scaled-font-simple (revised-scaled-font)
				 (make-character-image-if-appropriate
				   character-code orientation-code
				   revised-scaled-font revised-font-match?))))
			 ;; impose the set width:
			 (when revised-character-image?
			   (setf (character-image-set-width-as-text-width
				   revised-character-image?)
				 character-image-set-width-as-text-width)
			   revised-character-image?)))
		     (when character-raster?
		       (make-character-image
			 character-raster?
			 character-image-set-width-as-text-width ; set width
			 character-image-text-x-offset
			 character-image-y-offset 
			 character-image-width
			 character-image-height
			 orientation-code )))))
	  (when new-character-image?
	    (unless character-raster-from-revised-font?
	      (let ((delta 
		      (compute-size-for-character-image new-character-image?)))
		#+development
		(consider-reporting-total-rasters-in-use)
		(when (eq (ab-font-type ab-font) 'kanji)
		  (note-increase-in-size-of-large-scaled-font-bucket delta))
		(note-increase-in-size-of-scaled-font delta)))
	    new-character-image?)))))

;; Consider arranging scaling table lookup so that bounding-box-x-offset and bounding-box-
;; y-offset could be scaled by using them.  Note that they cannot now be simple because
;; they might be negative numbers.  Also consider whether scaling table lookup is worth
;; while; it might be just as fast or faster to do the arithmetic, at least in some
;; implementations.

;; Keep more finally useful values in character descriptions.

;; Note: regarding the "Thai bug fix" -- this is for bug HQ-4716813 "bad drawing
;; for (Thai) character 0e3f (3647)". Here's what we're doing: we have to use
;; only the hand-edited bitmap for the above case because Monotype Arial Font's
;; Thai Baht character (U+0E3F) has "issues" with our version of the Bitstream
;; Truetype rasterizer. This is a kludge to work around the unresolved bug in
;; Bitstream's rasterizer.  (Other rasterizers, including Windows, have been
;; tried and shown to work with this character in this exact font.)  The
;; replacement bitmap was rasterized from Monotype's BrowaliaUPC (BROWAU.TTF)
;; font, from a Windows 2000 system, with some hand editing of some
;; offsets. However, the original set width is used, so if we some day use the
;; real font, no reformatting will be needed.  Also, the real font is used at at
;; certain high-enough x scales, which were determined experimentally to work.
;; It was similarly determined that only the x-scale is a factor.  The resulting
;; replacement bitmaps are in the Thai font files (thai14, thai18, and
;; thai24.lisp) at each file's respective entry for font code 95. Note that
;; speed of checking for this case is basically not an issue, since this routine
;; is only called to create a bitmap, which then gets cached. (MHD 9/1/04)




(defun-void reclaim-scaled-font-character-image-cache
    (scaled-font-character-image-cache)
  (do-scaled-font-character-images
      ((character-image font-code bucket?)
       
       structure-being-reclaimed
       scaled-font-character-image-cache
       ;; ugly but efficient:   (to prevent double reclamation)
       (when bucket?		; "large font" (kanji font) case
	 (reclaim-fonts-list
	   (large-scaled-font-bucket-contents bucket?))
	 (setf (large-scaled-font-bucket-contents bucket?) nil)
	 (reclaim-large-scaled-font-bucket bucket?)))
    (reclaim-character-image character-image))
  (case (ab-font-type (ab-font-for-scaled-font structure-being-reclaimed))
    (kanji
     (reclaim-scaled-font-kanji-font-cache-vector
       scaled-font-character-image-cache))
    (t
     (reclaim-scaled-font-non-kanji-font-vector
       scaled-font-character-image-cache))))


(defun-void reclaim-large-scaled-font-bucket-contents (plist)
  (do-large-scaled-font-bucket-character-images
      ((character-image font-code) structure-being-reclaimed)
    (reclaim-character-image character-image))
  ;; just for cleanliness, remove pointer to this list:
  (setf (large-scaled-font-bucket-contents structure-being-reclaimed) nil)
  (reclaim-fonts-list plist))

(defun-simple compute-size-of-large-scaled-font-bucket (large-scaled-font-bucket)
  (+f large-scaled-font-bucket-base-size
      (let ((sum 0))
	(declare (type fixnum sum))
	(do-large-scaled-font-bucket-character-images
	    ((image code) large-scaled-font-bucket)
	  (incff sum
		 (+ (compute-size-for-character-image image)
		    kanji-character-entry-base-size)))
	sum)))
  




;;; `All-ab-font-names' ...

(defvar all-ab-font-names
  '(hm14 hm18 hm24 hb72 kanji16 kanji24 slavic14 slavic18 slavic24))


;;; `Do-scaled-fonts-in-font' knows how to iterate over the scaled fonts in an
;;; AB font.  It executes body for each scaled font with scaled-font-var bound
;;; to on each iteration to one of the scaled fonts in ab-font.  Note: it is
;;; an error to delete entries from this list during the iteration.

(defmacro do-scaled-fonts-in-font ((scaled-font-var ab-font) &body body)
  (avoiding-variable-capture (ab-font)
    `(loop for ,scaled-font-var in (cdr (ab-font-cache-of-scaled-fonts ,ab-font))
	   do (progn . ,body))))

;;; `Delete-character-images-in-scaled-fonts' ...

(defun delete-character-images-in-scaled-fonts ()
  (loop with count-of-character-images-so-far fixnum = 0
	for ab-font-name in all-ab-font-names
	as ab-font = (ab-font ab-font-name)
	unless (null ab-font)		; possible?
	  do (do-scaled-fonts-in-font (scaled-font ab-font)
	       (incff count-of-character-images-so-far
		      (delete-character-images-in-one-scaled-font
			scaled-font ab-font)))
	finally (return count-of-character-images-so-far)))


;;; `delete-character-images-in-one-scaled-font' is doing
;;; exactly what reclaim-scaled-font-character-image-cache
;;; is doing, except this has to count the number of
;;; characters as it goes, and the scaled-font will not
;;; actually be reclaimed.

(defun delete-character-images-in-one-scaled-font (scaled-font ab-font)
  (let ((count-of-character-images-so-far 0))

    (do-scaled-font-character-images
	((character-image index bucket-if-kanji?)
	 scaled-font
	 (scaled-font-character-image-cache scaled-font)
	 (progn
	   (reclaim-fonts-list
	     (large-scaled-font-bucket-contents bucket-if-kanji?))
	   (setf (large-scaled-font-bucket-contents bucket-if-kanji?) nil)
	   ;(reclaim-large-scaled-font-bucket bucket-if-kanji?) ; See note 2
	   ))
      (incff count-of-character-images-so-far)
      (reclaim-character-image character-image)
      (unless (eq (ab-font-type ab-font) 'kanji) ; See note 1
	(setf (svref (scaled-font-character-image-cache scaled-font) index) nil)))
    count-of-character-images-so-far))

;; Note 1: Unlike
;; reclaim-scaled-font-character-image-cache, here the
;; scaled-font is not being reclaimed, so we need to set
;; each non-kanji entry to nil. lgibson 10/15/98

;; Note 2: For kanji fonts, each entry is a bucket, which
;; we could reclaim, but we are going to leave
;; around. lgibson 10/15/98







;;;; Character Rasters




;;; A `character raster' is a 1-bit-per-pixel stored raster.




;;; The system variable `scratch-character-rectangle-array' is a simple
;;; array of sufficient size to handle any number of character rectangles
;;; possible in any AB font, which is currently 200.

;;; This is only to be used by make-character-rectangle

(def-system-variable
  scratch-character-rectangle-array fonts (:funcall make-array 200))

;; This works for Kanji16 at least -- where the max is probably 52 -- not
;; sure about HB72, however! (MHD 4/26/91)

;; Move elsewhere?






;;; Make-character-raster creates and returns a raster that is (at least) of sufficient
;;; width and height such that the character described by character-description in scaled-
;;; font will fit.  (Note that the actual widths and heights of rasters is subject to
;;; certain system dependent constraints and so may not be an accurate reflection of the
;;; minimum sufficient widths and heights.)  Scaled-font should be created via a suitable
;;; call to get-or-make-scaled-font, which will return a suitable scaled-font, which will
;;; have x- and y-scaling-tables which are used to implement scaling as table lookups.
;;; Once the raster is created, it should be stored in the table in the scaled-font-image-
;;; table slot of the scaled-font as the element indexed by the character-code of
;;; this particular character.  Character-description can be obtained by referencing the
;;; element index by the character-code in the table in the ab-font-character-description-
;;; table slot of an ab-font.  For an example of how arguments are obtained given a character-
;;; code, an ab-font, and x- and y-scales, see the definitiion of get-or-make-character-
;;; raster.
;;;
;;; Make-character-raster is obliged to never create a raster with less than a one pixel
;;; by one pixel area and never to scale any of the character rectangles of a
;;; character-description into rectangles of area less than one pixel by one pixel.
;;;
;;; The second and third values returned are the width and height, respectively, of the
;;; resulting raster.

(defun make-character-raster
       (oriented-scaled-font
        orientation-code
	character-rectangle-array-or-bitmap-or-bitmap-array
	bounding-box-x-offset bounding-box-y-offset
	bounding-box-width bounding-box-height
	index-for-bitmap-array-case?)
  (let* ((oriented-x-scale (scaled-font-x-scale oriented-scaled-font))
	 (oriented-y-scale (scaled-font-y-scale oriented-scaled-font))
	 (left-column 
	   (delta-x-in-window bounding-box-x-offset oriented-x-scale))
	 (top-row				; relative to baseline
	   (delta-y-in-window
	     (+w (-w bounding-box-y-offset) (-w bounding-box-height))
	     oriented-y-scale))
	 (right-column 
	   (delta-x-in-window (+w bounding-box-x-offset bounding-box-width)
			      oriented-x-scale))
	 (bottom-row				; relative to baseline
	   (delta-y-in-window (-w bounding-box-y-offset) oriented-y-scale))
	 (normalized-width  (maxr 1 (-r right-column left-column)))
	 (normalized-height (maxr 1 (-r bottom-row top-row)))
	 (oriented-width  (case orientation-code
			    ((0 2 4 6) normalized-width)
			    ((1 3 5 7) normalized-height)))
	 (oriented-height (case orientation-code
			    ((0 2 4 6) normalized-height)
			    ((1 3 5 7) normalized-width)))
	 character-rectangle-array		; set below
	 number-of-character-rectangles
	 clipped-left-edge clipped-top-edge
	 clipped-right-edge clipped-bottom-edge)
    ;; All bits in character raster should be cleared. (We assume that make-scratchpad-
    ;; raster creates rasters whose bits are all cleared.)
    
    ;; UGLY:   (MHD 4/26/91, 9/23/91)
    (cond
      (index-for-bitmap-array-case?
      ; (format t "index-for-bitmap-array-case?~%")
       (multiple-value-setq
	 (character-rectangle-array number-of-character-rectangles)
	 (let ((temporary-character-bitmap
		(allocate-temporary-character-bitmap
		  (bitmap-array-width
		    character-rectangle-array-or-bitmap-or-bitmap-array)
		  (bitmap-array-height
		    character-rectangle-array-or-bitmap-or-bitmap-array))))
	   (copy-from-bitmap-array-to-character-bitmap
	     character-rectangle-array-or-bitmap-or-bitmap-array	     
	     index-for-bitmap-array-case?
	     temporary-character-bitmap nil nil)
	   (convert-character-bitmap-to-rectangle-array
	     temporary-character-bitmap
	     bounding-box-width bounding-box-height nil
	     scratch-character-rectangle-array))))
      ((not-a-character-rectangle-array-but-a-bitmap-p
	 character-rectangle-array-or-bitmap-or-bitmap-array)
      ; (format t "not-a-character-rectangle-array-but-a-bitmap-p~%")
       (multiple-value-setq
	 (character-rectangle-array number-of-character-rectangles)
	 (convert-character-bitmap-to-rectangle-array
	   character-rectangle-array-or-bitmap-or-bitmap-array
	   bounding-box-width bounding-box-height nil
	   scratch-character-rectangle-array)))
      (t
      ; (format t "default bitmap case ~%")
       (setq character-rectangle-array
	     character-rectangle-array-or-bitmap-or-bitmap-array)
       (setq number-of-character-rectangles
	     (length character-rectangle-array-or-bitmap-or-bitmap-array))))    
    (values
      (on-scratchpad-raster-for-font-character-image
	(current-window
	  oriented-width
	  oriented-height)
	('reclaim-all-scaled-fonts)	
	(loop for i from 0 below number-of-character-rectangles
	      as character-rectangle
		 = (svref character-rectangle-array i)
	      as left-edge
		 = (delta-x-in-window
		     (+r (left-edge-of-character-rectangle character-rectangle)
			 bounding-box-x-offset)
		     oriented-x-scale)
	      as top-edge
		 = (delta-y-in-window
		     (-r (top-edge-of-character-rectangle character-rectangle)
			 bounding-box-y-offset bounding-box-height)
		     oriented-y-scale)
	      as right-edge
		 = (delta-x-in-window
		     (+r (right-edge-of-character-rectangle character-rectangle)
			 bounding-box-x-offset)
		     oriented-x-scale)
	      as bottom-edge
		 = (delta-y-in-window
		     (-r (bottom-edge-of-character-rectangle character-rectangle)
			 bounding-box-y-offset bounding-box-height)
		     oriented-y-scale)
	      do (when (=r left-edge right-edge)
		   (if (=r left-edge left-column)
		       (incfr right-edge)
		       (if (=r right-edge right-column)
			   (decfr left-edge)
			   (incfr right-edge))))
		 (when (=r top-edge bottom-edge)
		   (if (=r top-edge top-row)
		       (incfr bottom-edge)
		       (if (=r bottom-edge bottom-row)
			   (decfr top-edge)
			   (incfr bottom-edge))))
	      do
	  ;; Make sure each rectangle is at least one pixel wide by one pixel high
	  ;; and fits in the character raster (similarly coerced above to be at
	  ;; least one pixel wide by one pixel high).  At very small scales all
	  ;; rectangles will be described by the edges (0,0,1,1) in a one by
	  ;; one character raster.
						;first trivialize args for subst. macro
	  (setq clipped-left-edge   (-r left-edge left-column)
		clipped-top-edge    (-r top-edge top-row)
		clipped-right-edge  (-r right-edge left-column)
		clipped-bottom-edge (-r bottom-edge top-row))
	  (orient-points-for-icon
	      (get-reflection-and-rotation-from-orientation-code orientation-code)
	      normalized-width normalized-height
	    clipped-left-edge clipped-top-edge clipped-right-edge clipped-bottom-edge)
	  
	  (paint-solid-rectangle-in-current-scratchpad-raster
	    (minr clipped-left-edge clipped-right-edge)
	    (minr clipped-top-edge clipped-bottom-edge)
	    (maxr clipped-left-edge clipped-right-edge)
	    (maxr clipped-top-edge clipped-bottom-edge)
	    1)))
      normalized-width normalized-height)))







;;;; Font Maps



;;; A `font map' is a list of font names.  A font map should specify `ordinary faces'
;;; (light faces, usually); names for other faces (bold, italic, bold italic, etc.) are
;;; derived from the names for ordinary faces.  The first element of a font map should
;;; specify the `principal font', and the remaining elements should specify `secondary
;;; fonts'.

;; Implement a facility for defining the mapping from the name of an ordinary face to
;; the names of other faces!



(def-system-variable plist-of-corresponding-icp-object-maps-for-font-maps fonts nil)

(def-icp-object-type font-map
		     (standard-icp-object-index-space
		       ;;ajs (4/12/96) Prevent corruption in
		       ;; plist-of-corresponding-icp-object-maps-for-font-maps
		       ;;(get-gensym-plist-element
		       (get-icp-plist-element
			plist-of-corresponding-icp-object-maps-for-font-maps
			(if (null (cdr font-map)) (car font-map) font-map)))
  (loop for font-name in font-map
	as first-element? = t then nil
	do (send-icp-add-to-list-of-symbols
	     corresponding-icp-object-index font-name first-element?)))

;; Consider moving entries in plist-of-corresponding-icp-object-maps-for-font-maps up to
;; the front when they are accessed, as an optimization.  Alternatively, consider
;; implementing the corresponding-icp-object-map access form for font maps in some more
;; efficient way, if there come to be lots of distinct font maps.

;; NOTE: Font maps are created with gensym conses but they are never reclaimed. Fix!!!






;;;; AB-Latin-1 Font Codes


;;; `Unicode-to-adobe-encoding-map' maps Adobe's PDFDocEncoding codes to Unicode
;;; character codes and Adobe and Unicode names.
;;;
;;; Note that the ASCII characters (range 32-127) and the ISO Latin 1 characters
;;; (range 160-255) correspond identically to PDFDocEncoding with the exception
;;; of no-break space and soft hyphen.  The additional Adobe characters fit in
;;; to the 7-bit and 8-bit control range.
;;;
;;; Two unencoded characters are handled as follows: (1) #xA0 (no-break space)
;;; is mapped to #x20 (space); and (2) #xAD, soft-hyphen, is mapped to #x2D,
;;; hyphen.  Thus, this is strictly speaking a many-to-one mapping, in that
;;; unicodes #x20 and #xAD also map to #x20 and #xAD, respectively.
;;;
;;; The source for this information is the _Portable Document Format Reference
;;; Manual_, (c) 1993, Adobe Systems, Inc., published by Addison-Wesley, and the
;;; UnicodeData-2.0.12.txt database of Unicode characters, available from the
;;; Unicode FTP site, ftp.unicode.org.

;;; I have tried to include most of the Unicode and to make all the names
;;; correspond to Unicode 2.0 naming, but I haven't completely finished the job.
;;; A program should probably be written to complete the job.  Note that there
;;; no known users of these names currently.  Note that this currently is a
;;; defparameter-for-macro, meaning that it is unavailable and occupies no
;;; storage in productions versions of G2.

(defparameter-for-macro unicode-to-adobe-encoding-map
  '((#x2D8  24  "SPACING BREVE" "breve")
    (#x2C7  25  "CARON" "caron")	; called MODIFIER LETTER HACEK in Unicode 1.0
    (#x2C6  26  "MODIFIER LETTER CIRCUMFLEX ACCENT" "circumflex") ; called MODIFIER LETTER CIRCUMFLEX in Unicode 1.0
    (#x2D9  27  "SPACING DOT ABOVE" "dotaccent")
    (#x2DD  28  "SPACING DOUBLE ACUTE" "hungarumlaut")
    (#x2DB  29  "SPACING OGONEK" "ogonek")
    (#x2DA  30  "SPACING RING ABOVE" "ring")
    (#x2DC  31  "SPACING TILDE" "tilde")
    (#x20   32  "SPACE" "space")
    (#x21  #x21  "EXCLAMATION MARK" "exclam")
    (#x22  #x22  "QUOTATION MARK" "quotedbl")
    (#x23  #x23  "NUMBER SIGN" "numbersign")
    (#x24  #x24  "DOLLAR SIGN" "dollar")
    (#x25  #x25  "PERCENT SIGN" "percent")
    (#x26  #x26  "AMPERSAND" "ampersand")
    (#x27  #x27 "APOSTROPHE" "quotesingle") ; called APOSTROPHE-QUOTE in Unicode 1.0
    (#x28  #x28  "LEFT PARENTHESIS" "parenleft") ; called OPENING PARENTHESIS in Unicode 1.0
    (#x29  #x29  "RIGHT PARENTHESIS" "parenright") ; called CLOSING PARENTHESIS in Unicode 1.0
    (#x2A  #x2A  "ASTERISK" "asterisk")
    (#x2B  #x2B  "PLUS SIGN" "plus")
    (#x2C  #x2C  "COMMA" "comma")
    (#x2D  #x2D  "HYPHEN-MINUS" "hyphen")
    (#x2E  #x2E  "PERIOD" "period")
    (#x2F  #x2F  "SLASH" "slash")
    (#x30  #x30  "DIGIT ZERO" "zero")
    (#x31  #x31  "DIGIT ONE" "one")
    (#x32  #x32  "DIGIT TWO" "two")
    (#x33  #x33  "DIGIT THREE" "three")
    (#x34  #x34  "DIGIT FOUR" "four")
    (#x35  #x35  "DIGIT FIVE" "five")
    (#x36  #x36  "DIGIT SIX" "six")
    (#x37  #x37  "DIGIT SEVEN" "seven")
    (#x38  #x38  "DIGIT EIGHT" "eight")
    (#x39  #x39  "DIGIT NINE" "nine")
    (#x3A  #x3A  "COLON" "colon")
    (#x3B  #x3B  "SEMICOLON" "semicolon")
    (#x3C  #x3C  "LESS-THAN SIGN" "less")
    (#x3D  #x3D  "EQUALS SIGN" "equal")
    (#x3E  #x3E  "GREATER-THAN SIGN" "greater")
    (#x3F  #x3F  "QUESTION MARK" "question")
    (#x40  #x40  "COMMERCIAL AT" "at")
    (#x41  #x41  "LATIN CAPITAL LETTER A" "A")
    (#x42  #x42  "LATIN CAPITAL LETTER B" "B")
    (#x43  #x43  "LATIN CAPITAL LETTER C" "C")
    (#x44  #x44  "LATIN CAPITAL LETTER D" "D")
    (#x45  #x45  "LATIN CAPITAL LETTER E" "E")
    (#x46  #x46  "LATIN CAPITAL LETTER F" "F")
    (#x47  #x47  "LATIN CAPITAL LETTER G" "G")
    (#x48  #x48  "LATIN CAPITAL LETTER H" "H")
    (#x49  #x49  "LATIN CAPITAL LETTER I" "I")
    (#x4A  #x4A  "LATIN CAPITAL LETTER J" "J")
    (#x4B  #x4B  "LATIN CAPITAL LETTER K" "K")
    (#x4C  #x4C  "LATIN CAPITAL LETTER L" "L")
    (#x4D  #x4D  "LATIN CAPITAL LETTER M" "M")
    (#x4E  #x4E  "LATIN CAPITAL LETTER N" "N")
    (#x4F  #x4F  "LATIN CAPITAL LETTER O" "O")
    (#x50  #x50  "LATIN CAPITAL LETTER P" "P")
    (#x51  #x51  "LATIN CAPITAL LETTER Q" "Q")
    (#x52  #x52  "LATIN CAPITAL LETTER R" "R")
    (#x53  #x53  "LATIN CAPITAL LETTER S" "S")
    (#x54  #x54  "LATIN CAPITAL LETTER T" "T")
    (#x55  #x55  "LATIN CAPITAL LETTER U" "U")
    (#x56  #x56  "LATIN CAPITAL LETTER V" "V")
    (#x57  #x57  "LATIN CAPITAL LETTER W" "W")
    (#x58  #x58  "LATIN CAPITAL LETTER X" "X")
    (#x59  #x59  "LATIN CAPITAL LETTER Y" "Y")
    (#x5A  #x5A  "LATIN CAPITAL LETTER Z" "Z")
    (#x5B  #x5B  "LEFT SQUARE BRACKET" "bracketleft") ; called OPENING SQUARE BRACKET in Unicode 1.0
    (#x5C  #x5C  "BACKSLASH" "backslash")
    (#x5D  #x5D  "RIGHT SQUARE BRACKET" "bracketright")	; called CLOSING SQUARE BRACKET in Unicode 1.0
    (#x5E  #x5E  "CIRCUMFLEX ACCENT" "asciicircum") ; called SPACING CIRCUMFLEX in Unicode 1.0
    (#x5F  #x5F  "LOW LINE" "underscore") ; called SPACING UNDERSCORE in Unicode 1.0
    (#x60  #x60  "GRAVE ACCENT" "grave") ; called SPACING GRAVE in Unicode 1.0
    (#x61  #x61  "LATIN SMALL LETTER A" "a")
    (#x62  #x62  "LATIN SMALL LETTER B" "b")
    (#x63  #x63  "LATIN SMALL LETTER C" "c")
    (#x64  #x64  "LATIN SMALL LETTER D" "d")
    (#x65  #x65  "LATIN SMALL LETTER E" "e")
    (#x66  #x66  "LATIN SMALL LETTER F" "f")
    (#x67  #x67  "LATIN SMALL LETTER G" "g")
    (#x68  #x68  "LATIN SMALL LETTER H" "h")
    (#x69  #x69  "LATIN SMALL LETTER I" "i")
    (#x6A  #x6A  "LATIN SMALL LETTER J" "j")
    (#x6B  #x6B  "LATIN SMALL LETTER K" "k")
    (#x6C  #x6C  "LATIN SMALL LETTER L" "l")
    (#x6D  #x6D  "LATIN SMALL LETTER M" "m")
    (#x6E  #x6E  "LATIN SMALL LETTER N" "n")
    (#x6F  #x6F  "LATIN SMALL LETTER O" "o")
    (#x70  #x70  "LATIN SMALL LETTER P" "p")
    (#x71  #x71  "LATIN SMALL LETTER Q" "q")
    (#x72  #x72  "LATIN SMALL LETTER R" "r")
    (#x73  #x73  "LATIN SMALL LETTER S" "s")
    (#x74  #x74  "LATIN SMALL LETTER T" "t")
    (#x75  #x75  "LATIN SMALL LETTER U" "u")
    (#x76  #x76  "LATIN SMALL LETTER V" "v")
    (#x77  #x77  "LATIN SMALL LETTER W" "w")
    (#x78  #x78  "LATIN SMALL LETTER X" "x")
    (#x79  #x79  "LATIN SMALL LETTER Y" "y")
    (#x7A  #x7A  "LATIN SMALL LETTER Z" "z")
    (#x7B  #x7B  "LEFT CURLY BRACKET" "braceleft") ; called OPENING CURLY BRACKET in Unicode 1.0
    (#x7C  #x7C  "VERTICAL BAR" "bar")
    (#x7D  #x7D  "RIGHT CURLY BRACKET" "braceright") ; called CLOSING CURLY BRACKET in Unicode 1.0
    (#x7E  #x7E  "TILDE" "asciitilde")
    ;; hole at #x7F (decimal 127)
    (#x2022  128  "BULLET" "bullet")
    (#x2020  129  "DAGGER" "dagger")
    (#x2021  130  "DOUBLE DAGGER" "daggerdbl")
    (#x2026  131  "HORIZONTAL ELLIPSIS" "ellipsis")
    (#x2014  132  "EM DASH" "emdash")
    (#x2013  133  "EN DASH" "endash")
    (#x192   134  "LATIN SMALL LETTER SCRIPT F" "florin")
    (#x2044  135  "FRACTION SLASH" "fraction")
    (#x2039  136  "LEFT POINTING SINGLE GUILLEMET" "guilsinglleft")
    (#x203A  137  "RIGHT POINTING SINGLE GUILLEMET" "guilsinglright")
    (#x2212  138  "MINUS SIGN" "minus")
    (#x2030  139  "PER MILLE SIGN" "perthousand")
    (#x201E  140  "LOW DOUBLE COMMA QUOTATION MARK" "quotedblbase")
    (#x201C  141  "DOUBLE TURNED COMMA QUOTATION MARK" "quotedblleft")
    (#x201D  142  "DOUBLE COMMA QUOTATION MARK" "quotedblright")
    (#x2018  143  "SINGLE TURNED COMMA QUOTATION MARK" "quoteleft")
    (#x2019  144  "SINGLE COMMA QUOTATION MARK" "quoteright")
    (#x201A  145  "LOW SINGLE COMMA QUOTATION MARK" "quotesinglbase")
    (#x2122  146  "TRADE MARK SIGN" "trademark") ; called TRADEMARK in Unicode 1.0
    (#xFB01  147  "LATIN SMALL LIGATURE FI" "fi")
    (#xFB02  148  "LATIN SMALL LIGATURE FL" "fl")
    (#x141   149  "LATIN CAPITAL LETTER L WITH STROKE" "Lslash") ; called LATIN CAPITAL LETTER L SLASH in Unicode 1.0
    (#x152   150  "LATIN CAPITAL LETTER O E" "OE")
    (#x160   151  "LATIN CAPITAL LETTER S WITH CARON" "Scaron")
    (#x178   152  "LATIN CAPITAL LETTER Y WITH DIAERESIS" "Ydieresis")
    (#x17D   153  "LATIN CAPITAL LETTER Z WITH CARON" "Zcaron")
    (#x131   154  "LATIN SMALL LETTER DOTLESS I" "dotlessi")
    (#x142   155  "LATIN SMALL LETTER L WITH STROKE" "lslash") ; called LATIN SMALL LETTER L SLASH in Unicode 1.0
    (#x153   156  "LATIN SMALL LETTER O E" "oe")
    (#x161   157  "LATIN SMALL LETTER S WITH CARON" "scaron") ; called LATIN SMALL LETTER S HACEK in Unicode 1.0
    (#x17E   158  "LATIN SMALL LETTER Z WITH CARON" "zcaron") ; called LATIN SMALL LETTER Z HACEK in Unicode 1.0
    (#xA0    #x20 "NO-BREAK SPACE" "(no name)") ; #x20 replaces #x9E  ; same as space, but diff. semantics
    (#xA1    #xA1  "INVERTED EXCLAMATION MARK" "exclamdown")
    (#xA2    #xA2  "CENT SIGN" "cent")
    (#xA3    #xA3  "POUND SIGN" "sterling")
    (#xA4    #xA4  "CURRENCY SIGN" "currency")
    (#xA5    #xA5  "YEN SIGN" "yen")
    (#xA6    #xA6  "BROKEN BAR" "brokenbar")
    (#xA7    #xA7  "SECTION SIGN" "section")
    (#xA8    #xA8  "SPACING DIAERESIS" "dieresis")
    (#xA9    #xA9  "" "copyright")	; Get Unicode name!
    (#xAA    #xAA  "FEMININE ORDINAL INDICATOR" "ordfeminine")
    (#xAB    #xAB  "LEFT POINTING GUILLEMET" "guillemotleft")
    (#xAC    #xAC  "NOT SIGN" "logicalnot")
    (#xAD    #x2D  "SOFT HYPHEN" "(no name)") ; #x2D replaces #x97  ; same as hyphen, but diff. semantics
    (#xAE    #xAE  "" "registered") ; Get Unicode name!
    (#xAF    #xAF  "SPACING MACRON" "macron")
    (#xB0    #xB0  "DEGREE SIGN" "degree")
    (#xB1    #xB1  "PLUS-MINUS SIGN" "plusminus")
    (#xB2    #xB2  "SUPERSCRIPT TWO" "twosuperior")
    (#xB3    #xB3  "SUPERSCRIPT THREE" "threesuperior")
    (#xB4    #xB4  "SPACING ACUTE" "acute")
    (#xB5    #xB5  "MICRO SIGN" "mu")
    (#xB6    #xB6  "PARAGRAPH SIGN" "paragraph")
    (#xB7    #xB7  "MIDDLE DOT" "periodcentered") ; use "middot" for BCID
    (#xB8    #xB8  "SPACING CEDILLA" "cedilla")
    (#xB9    #xB9  "SUPERSCRIPT ONE" "onesuperior")
    (#xBA    #xBA  "MASCULINE ORDINAL INDICATOR" "ordmasculine")
    (#xBB    #xBB  "RIGHT POINTING GUILLEMET" "guillemotright")
    (#xBC    #xBC  "VULGAR FRACTION ONE QUARTER" "onequarter")
    (#xBD    #xBD  "VULGAR FRACTION ONE HALF" "onehalf")
    (#xBE    #xBE  "VULGAR FRACTION THREE QUARTERS" "threequarters")
    (#xBF    #xBF  "INVERTED QUESTION MARK" "questiondown")
    (#xC0    #xC0  "" "Agrave")		; Get Unicode name!
    (#xC1    #xC1   "" "Aacute")
    (#xC2    #xC2   "" "Acircumflex")
    (#xC3    #xC3   "" "Atilde")
    (#xC4    #xC4   "" "Adieresis")
    (#xC5    #xC5   "" "Aring")
    (#xC6    #xC6   "LATIN CAPITAL LETTER A E" "AE")
    (#xC7    #xC7   "" "Ccedilla")
    (#xC8    #xC8   "" "Egrave")
    (#xC9    #xC9   "" "Eacute")
    (#xCA    #xCA   "" "Ecircumflex")
    (#xCB    #xCB   "" "Edieresis")
    (#xCC    #xCC   "" "Igrave")
    (#xCD    #xCD   "" "Iacute")
    (#xCE    #xCE   "" "Icircumflex")
    (#xCF    #xCF   "" "Idieresis")
    (#xD0    #xD0   "LATIN CAPITAL LETTER ETH (Icelandic)" "Eth")
    (#xD1    #xD1   "" "Ntilde")
    (#xD2    #xD2   "" "Ograve")
    (#xD3    #xD3   "" "Oacute")
    (#xD4    #xD4   "" "Ocircumflex")
    (#xD5    #xD5   "" "Otilde")
    (#xD6    #xD6   "" "Odieresis")
    (#xD7    #xD7   "MULTIPLICATION SIGN" "multiply")
    (#xD8    #xD8   "LATIN CAPITAL LETTER O SLASH" "Oslash")
    (#xD9    #xD9   "" "Ugrave")
    (#xDA    #xDA   "" "Uacute")
    (#xDB    #xDB   "" "Ucircumflex")
    (#xDC    #xDC   "" "Udieresis")
    (#xDD    #xDD   "LATIN CAPITAL LETTER Y WITH ACUTE" "Yacute")
    (#xDE    #xDE   "LATIN CAPITAL LETTER THORN (Icelandic)" "Thorn")
    (#xDF    #xDF   "LATIN SMALL LETTER SHARP S" "germandbls")
    (#xE0    #xE0   "" "agrave")
    (#xE1    #xE1   "" "aacute")
    (#xE2    #xE2   "" "acircumflex")
    (#xE3    #xE3   "" "atilde")
    (#xE4    #xE4   "" "adieresis")
    (#xE5    #xE5   "" "aring")
    (#xE6    #xE6   "LATIN SMALL LETTER A E" "ae")
    (#xE7    #xE7   "" "ccedilla")
    (#xE8    #xE8   "" "egrave")
    (#xE9    #xE9   "" "eacute")
    (#xEA    #xEA   "" "ecircumflex")
    (#xEB    #xEB   "" "edieresis")
    (#xEC    #xEC   "" "igrave")
    (#xED    #xED   "" "iacute")
    (#xEE    #xEE   "" "icircumflex")
    (#xEF    #xEF   "" "idieresis")
    (#xF0    #xF0   "LATIN SMALL LETTER ETH (Icelandic)" "eth")
    (#xF1    #xF1   "" "ntilde")
    (#xF2    #xF2   "" "ograve")
    (#xF3    #xF3   "" "oacute")
    (#xF4    #xF4   "" "ocircumflex")
    (#xF5    #xF5   "" "otilde")
    (#xF6    #xF6   "" "odieresis")
    (#xF7    #xF7   "DIVISION SIGN" "divide")
    (#xF8    #xF8   "LATIN SMALL LETTER O SLASH" "oslash")
    (#xF9    #xF9   "" "ugrave")
    (#xFA    #xFA   "" "uacute")
    (#xFB    #xFB   "" "ucircumflex")
    (#xFC    #xFC   "" "udieresis")
    (#xFD    #xFD   "LATIN SMALL LETTER Y WITH ACUTE" "yacute")
    (#xFE    #xFE   "LATIN SMALL LETTER THORN (Icelandic)" "thorn")
    (#xFF    #xFF   "LATIN SMALL LETTER Y WITH DIAERESIS" "ydieresis")))




;;; The function `map-ab-latin-font-code-to-adobe-name' maps an
;;; AB-Latin font code to its corresponding Adobe name.  It is a
;;; defun-for-macro, and is used both for font Generation, an
;;; occasional developmeng-only task, as well as for defining
;;; a table needed by the Postscript printing facility.

(defun-for-macro map-ab-latin-font-code-to-adobe-name (font-code)
  (fourth
    (find font-code unicode-to-adobe-encoding-map
	  :key #'second :test #'=)))





;;; `Map-unicode-to-ab-latin-font-code-or-zero-macro' is called with a Unicode
;;; character code (a 16-bit unsigned integer), and returns the corresponding
;;; AB-Latin font code, if any.  Zero is returned for any Unicode that has no
;;; corresponding AB-Latin-1 font code.
;;;
;;; Note that this is based on the mappings in unicode-to-adobe-encoding-map,
;;; q.v., above.

;;; GENSYMCID-1042: Unability to display some polish characters
;;; The 14 new polish characters are now defined in HM14, HM18 and HM24 (05~18)

(defparameter-for-macro gensym-non-adobe-standard-encoded-latin-codes
  '(
    (#x0104 05)			; LATIN CAPITAL LETTER A WITH OGONEK
    (#x0105 06)			; LATIN SMALL LETTER A WITH OGONEK
    (#x0106 07)			; LATIN CAPITAL LETTER C WITH ACUTE
    (#x0107 08)			; LATIN SMALL LETTER C WITH ACUTE
    (#x0118 09)			; LATIN CAPITAL LETTER E WITH OGONEK
    (#x0119 10)			; LATIN SMALL LETTER E WITH OGONEK
    (#x0143 11)			; LATIN CAPITAL LETTER N WITH ACUTE
    (#x0144 12)			; LATIN SMALL LETTER N WITH ACUTE
    (#x015A 13)			; LATIN CAPITAL LETTER S WITH ACUTE
    (#x015B 14)			; LATIN SMALL LETTER S WITH ACUTE
    (#x0179 15)			; LATIN CAPITAL LETTER Z WITH ACUTE
    (#x017A 16)			; LATIN SMALL LETTER Z WITH ACUTE
    (#x017B 17)			; LATIN CAPITAL LETTER Z WITH DOT ABOVE
    (#x017C 18)			; LATIN SMALL LETTER Z WITH DOT ABOVE

    (#x030B 19)			; COMBINING DOUBLE ACUTE ACCENT
    (#x0170 20)			; LATIN CAPITAL LETTER U WITH DOUBLE ACUTE
    (#x0171 21)			; LATIN SMALL LETTER U WITH DOUBLE ACUTE
    (#x0150 22)			; LATIN CAPITAL LETTER O WITH DOUBLE ACUTE
    (#x0151 23)			; LATIN SMALL LETTER O WITH DOUBLE ACUTE
    ))

(defmacro gensym-non-adobe-standard-encoded-latin-code-p (unicode)
  `(assoc ,unicode ',gensym-non-adobe-standard-encoded-latin-codes))

(defmacro map-unicode-to-ab-latin-font-code-or-zero-macro (unicode)
  (avoiding-variable-capture (unicode)
    `(cond
       ((<=f #x20 ,unicode #x7f)	; see note 1
	,unicode)
       ((=f ,unicode #xA0)
	#x20)
       ((=f ,unicode #xAD)
	#x2D)
       ((<=f #xA0 ,unicode #xFF)
	,unicode)
       (t
	(fixnum-case ,unicode
	  ,@gensym-non-adobe-standard-encoded-latin-codes
	  ,@(sort			; see note 2
	      (loop for entry in unicode-to-adobe-encoding-map
		    when (not (<f (first entry) 256))
		      collect `(,(first entry) ,(second entry)))
	      #'< :key #'car)
	  (t 0))))))

(defun-simple map-unicode-to-ab-latin-font-code-or-zero (unicode)
  (map-unicode-to-ab-latin-font-code-or-zero-macro unicode))
  

;; Note 1: we pass ASCII/ISO Latin 1 characters through as their own font code,
;; with a couple of exceptions. This short cut is based on documentation of
;; unicode-to-adobe-encoding-map, q.v., and the Unicode's structural
;; relationship to ASCII/ISO Latin 1:

;; Note 2: sorting brings no known benefits, but cannot hurt and at least makes
;; the generated code look easier; perhaps, it helps the optimizer more easily
;; produce a "computed goto", but that is uncertain. (MHD)



;; Code generated by generate-AB-Latin-font-code-to-BCID-map: (B = Bitstream)

(defparameter ab-latin-font-code-to-bcid-map
  (optimize-constant
       '#.(make-array 256
          :element-type '(unsigned-byte 16)
          :initial-contents '(
     #x0 #x0 #x0 #x0 #x0

      ;; Hand-edits for A, a, E, e ogonek; C, c, N, n, S, s, Z, z acute;
      ;; and Z, z dot_above.  -- Chun Tian (binghe), 5/22/2013

      ;; 05~18: #x0 #x0 #x0 #x0 #x0 #x0 #x0 #x0 #x0 #x0 #x0 #x0 #x0 #x0
      227 233 622 621 228 234 321 320 665 664 610 609 614 613

      ;; Hand-edits for U, u, O, and o double-acutes:  [BCID's corresponding
      ;; to Unicode values in fontrip module cmtglob.c] (MHD 8/1/98)
			      
			      #xEF	; 19: #x0  (same as 28: #xEF "hungarumlaut")

			      681 680 657 656
					; 20, 21, 22, 23: #x0 #x0 #x0 #x0

			      #xB3 #xAD #xA7 #xED #xEF #xF6 #xB5 #xAB 
     #x20 #x21 #x22 #x23 #x24 #x25 #x26 #x27 #x28 #x29 #x2A #x2B #x2C #x2D #x2E #x2F 
     #x30 #x31 #x32 #x33 #x34 #x35 #x36 #x37 #x38 #x39 #x3A #x3B #x3C #x3D #x3E #x3F 
     #x40 #x41 #x42 #x43 #x44 #x45 #x46 #x47 #x48 #x49 #x4A #x4B #x4C #x4D #x4E #x4F 
     #x50 #x51 #x52 #x53 #x54 #x55 #x56 #x57 #x58 #x59 #x5A #x5B #x5C #x5D #x5E #x5F 
     #xA5 #x61 #x62 #x63 #x64 #x65 #x66 #x67 #x68 #x69 #x6A #x6B #x6C #x6D #x6E #x6F 
     #x70 #x71 #x72 #x73 #x74 #x75 #x76 #x77 #x78 #x79 #x7A #x7B #x7C #x7D #x1288 #x0 
     #x23F #x8E #x8F #x1A7 #x1A2 #x91 #x85 #x87 #x9D #x9E #x1C1 #x86 #x8D #x8A #x8B #x89 
     #x27 #x8C #x236 #x81 #x82 #xE2 #x96 #x29B #x15D #x264 #x9C #xE6 #x9A #x29A #x263 #x0 
     #x0 #xA2 #x84 #x83 #x1B4 #x1AB #x1B3 #x90 #xA9 #x234 #x192 #x9F #x1E6 #x0 #x235 #xB1 
     #x23C #x1C4 #xC3 #xC4 #xA3 #x216 ; #x1859 ; #x1FD
			      #x1BA
			      136 ; #x16BB is periodcentered, but middot works with BCID
			      #xAF #xC2 #x191 #xA0 #xBA #xBC #xBE #xA1 
     #x18D #x18F #x18B #x187 #x189 #x93 #x94 #xB7 #x183 #x185 #x181 #x17F #x177 #x179 #x175 #x173 
     #xE1 #x143 #x149 #x147 #x14B #x14F #x14D #x1C2 #x95 #x153 #x151 #x155 #x157 #x15F #x1A8 #x9B 
     #x18E #x190 #x18C #x188 #x18A #x97 #x98 #xB8 #x184 #x186 #x182 #x180 #x178 #x17A #x176 #x174 
     #x1AA #x142 #x148 #x146 #x14A #x14E #x14C #x1C3 #x99 #x152 #x150 #x154 #x156 #x15E #x1A9 #x15C ))))


(defmacro map-ab-latin-font-code-to-bcid (ab-latin-font-code)
  `(the (unsigned-byte 16)
	(aref (the (simple-array (unsigned-byte 16) (*))
		   ab-latin-font-code-to-bcid-map)
	      (the (unsigned-byte 8) ,ab-latin-font-code))))





;;;; Text Lines


;;; A `text line' is an element of a text containing the characters of the text.
;;; Historically, in G2 text lines have been implemented as text strings (i.e.,
;;; Common Lisp strings).  Along with that, the character encoding was Gensym's
;;; own multibyte encoding method, which uses all 7-bit ASCII characters, and
;;; reserving 3 of these characters for use as single-shift escapes into
;;; extended code ranges.  Finally, add to that that the character set repertoire
;;; and their numeric encoding (where it existed) was Gensym's own, though it
;;; was based to a large extend on various national standards.

;;; In 5.0 we are transitioning in one fell swoop to a new data type, the wide
;;; string, a new encoding, pure 16-bit bytes, and a new character set, the
;;; Unicode/ISO 10646 character set.

;;; The operations defined here for text-line are being defined mostly to ease
;;; the transition from text lines as text-strings to text lines as wide
;;; strings.  During this transitional phase, text lines are implemented as a
;;; union type of text-string and wide-string.



;;; `Reclaim-text-line' reclaims text-line.

(defmacro reclaim-text-line (text-line)
  `(reclaim-text-string ,text-line))




;;; `Text-line-p' is true if text-element, an element of a text, is a text
;;; string representing a line of text), as opposed to other text elements.

(defmacro text-line-p (text-element)
  `(text-string-p-macro ,text-element))

(defmacro text-line-length (text-line)
  `(text-string-length ,text-line))

(defmacro copy-text-line (text-line)
  `(copy-text-string ,text-line))


;;; `Find-next-character-in-text-line' returns the character at position
;;; character-index in string, as two values:
;;;    (1) a wide character for a wide string or a character or character code;
;;;    (2) the character index past the next character.

;;; There is assumed to be a next character in string; character-index must not
;;; be at the end of string.

;;; `Find-previous-character-in-text-line' returns the character just before
;;; position character-index in string, as two values:
;;;    (1) a wide character for a wide string or a character or character code;
;;;    (3) the character index for the previous character.

;;; There is assumed to be a previous character in string; character-index must
;;; not be at the beginning of string.

;;; These are text-line versions/replacements for the operation
;;; find-next/previous-character-in-string, q.v., on text strings.

(def-substitution-macro find-next-character-in-text-line (index text-line)
  (values (charw text-line index) (+f index 1)))

(def-substitution-macro find-previous-character-in-text-line (index text-line)
  (values (charw text-line (-f index 1)) (-f index 1)))




;;;; Text Line Graphic Element Primitives



(def-icp-value-type-equivalence text-line text-string)	; move to where text-line defined!

(def-icp-value-type-equivalence word-spacing unsigned-integer)

(def-icp-value-type-equivalence x-scale unsigned-integer)	; move to where scale
(def-icp-value-type-equivalence y-scale unsigned-integer)	;   is defined!




(defparameter hm14-native-font-name
  #.(stringw "-Adobe-Helvetica-Medium-R-Normal--14-140-75-75-P-77-ISO8859-1"))
(defparameter hm18-native-font-name
  #.(stringw "-Adobe-Helvetica-Medium-R-Normal--18-180-75-75-P-98-ISO8859-1"))
(defparameter hm24-native-font-name
  #.(stringw "-Adobe-Helvetica-Medium-R-Normal--24-240-75-75-P-130-ISO8859-1"))

;; These have a hyphen that's way too wide.  Try using the en dash?!


(defun map-to-x-font (ab-font-name &optional word-spacing) ; eliminate word-spacing?
  word-spacing				; important issue -- can't punt!
  (case ab-font-name
    (hm14 hm14-native-font-name)
    (hm18 hm18-native-font-name)
    (hm24 hm24-native-font-name)))











;;; `Gensym-noncharacter-code' is the character-code part of a \ complex
;;; character, and is used, by convention, as the missing character for failure
;;; to map from a Unicode to a `Gensym Classic Character', i.e., an element of
;;; the Gensym character set repertoire as of G2 4.0, which is a subset of
;;; Unicode and is all that's planned to be supported in our non-native graphics
;;; at this time.  This wide character should never be in a wide string; it is
;;; just used for internal processing in order to yield the glyph for a missing
;;; character.

(defconstant gensym-noncharacter-code 256)


;;; `Unicode-wide-character-to-gensym-pair-for-fonts' returns two values, the
;;; pair character-or-character-code and escape-character? that matches
;;; unicode-wide-character, provided it corresponds to a Gensym Classic
;;; Character, or a pair that matches gensym-noncharacter-code, which is
;;; intended to produce a "blob" indicating a missing character.

(defmacro unicode-wide-character-to-gensym-pair-for-fonts (unicode-wide-character)
  `(gensym-character-code-to-pair
     (or
       (map-unicode-to-gensym-character-code
	 (wide-character-code ,unicode-wide-character))
       gensym-noncharacter-code)))

;; Just used for PRINTING, for now. That module could use some modernization! (MHD 8/26/96)





(def-substitution-macro classify-character-for-text-line-drawing (character)
  (cond
    ((non-graphic-character-p-macro character)
     'non-graphic)
    ((or (char=w character #.%space)
	 (char=w character #.%no-break-space))
     'ordinary-space)
    ((char=w character #.%zero-width-space)
     'zero-width-space)
    ((non-spacing-mark-p-macro character)
     'non-spacing-mark)
    (t 'mark)))

(defun-simple classify-character-for-text-line-drawing-function (character)
  (classify-character-for-text-line-drawing character))
  

(defmacro get-non-spacing-mark-combining-class (character)
  `(let ((character ,character))
     (cond
       ((or (char<=w #u0300 character #u030F) ; Latin
	    ;; add more!
	    (char=w #u05b9 character)	; Hebrew (See note below!)
	    (char=w #u05bf character)
	    (char=w #u05c1 character)
	    (char=w #u05c2 character)
	    (char=w #u05c4 character))
	'above-rtl)
       ((or (char<=w #u05b0 character #u05b8) ; Hebrew
	    (char=w #u05bb character)
	    (char=w #u05bd character))
	'below-rtl)
       ((char=w #u05bc character)	; Hebrew dagesh
	'center-rtl)

       ((char=w #u0e31 character)	; Thai
	'above)
       ((char<=w #u0e34 character #u0e37) ; Thai
	'above)
       ((char<=w #u0e38 character #u0e3a) ; Thai
	;; These lower diacritics need special handling -- custom glyph
	;; substitution -- when used in combination with 0e0d or 0e10, which
	;; have a built-in lower diacritic. In particular, for our Monotype
	;; Arial Thai font, the glyph variants for 0e0d & 0e10 can be found at
	;; PUA locations f700 & f70f, respectively. (MHD 12/15/03)
	'below)
       ((char=w #u0e47 character) ; Thai
	'above)
       ((char=w #u0e48 character) ; Thai
	'above)
       ((char<=w #u0e49 character  #u0e4a) ; Thai
	'above)
       ((char<=w #u0e4b character #u0e4d) ; Thai
	'above)
       ((char=w #u0e4e character) ; Thai
	'above))))

;; Note: technically, most of the Hebrew diacritics (nikudes) are in "fixed
;; position classes", meaning they have to have special positioning.  However,
;; for our purposes, a rough recategorization in terms of major classes we
;; handle and what works with our font (Monotype/Windows Arial Hebrew) should
;; more than suffice. (MHD 10/15/99)

;; Note: today added Thai diacritics. Also, changed combining classes for Hebrew
;; diacritics to have names ending with "-RTL", and fixed callers
;; accordingly. (MHD 12/21/03)      

;; Incomplete, but a placeholder for adding further support for non-spacing
;; marks! (MHD 8/2/98)



;;; `Map-to-non-kanji-font-character-code-if-any' ...

#+OBSOLETE
(defun-substitution-macro map-to-non-kanji-font-character-code-if-any
    (character escape-character?)
  (let* ((gensym-code
	   (gensym-character-pair-to-code character escape-character?))
	 (unicode
	   (map-gensym-character-code-to-unicode gensym-code))
	 (ab-latin-code
	   (map-unicode-to-ab-latin-font-code-or-zero-macro unicode)))
    ab-latin-code))
    
; OBS:
;  (if (or (null escape-character?)
;	  (and (char= escape-character? #\@)
;	       (not (char= character #\L)) ; optimization
;	       (not (alpha-char-p character))))
;      (convert-simple-character-to-ascii character)
;      (if (eql escape-character? #\~)
;	  (map-to-roman-font-special-character-code-if-any character))))


;;; `Non-latin-font-character-p' is here as part of the font support in
;;; PRINTING.  It merely says whether unicode-wide-character corresponds to a
;;; character stored in a "kanji" font, which happens to be determined to be
;;; true if the character was previously encoded with the \ escape character
;;; in the original Gensym character encoding. 

#+OBSOLETE
(defun-substitution-macro non-latin-font-character-p (unicode-wide-character)
  (multiple-value-bind (character-or-character-code? escape-character?)
      (let ((gensym-character-code?
	     (map-unicode-to-gensym-character-code
	       (wide-character-code unicode-wide-character))))
	(if gensym-character-code?
	    (gensym-character-code-to-pair gensym-character-code?)))
    (declare (ignore character-or-character-code?))
    (and escape-character?
	 (char= escape-character? #\\))))

;; Only used in PRINTING for now. (MHD 8/26/96)



;;; `Map-to-cyrillic-font-code-if-any' maps from a gensym Cyrillic character
;;; code to its corresponding font code.

#+OBSOLETE
(defmacro map-to-cyrillic-font-code-if-any (gensym-cyrillic-character-code)
  `(let ((where (+f (-f ,gensym-cyrillic-character-code
			gensym-cyrillic-character-block-start)
		    32)))
     (if (<=f 32 where #.(+ 32 128))
	 where)))

;; At present, the first 32 places are always wasted, although the first (0th)
;; element contains the missing ("blob") character.

(defmacro map-cyrillic-font-code-to-unicode-index (gensym-cyrillic-font-code)
  `(-f ,gensym-cyrillic-font-code 32))

(defmacro map-hebrew-font-code-to-unicode (font-code)
  `(let ((font-code ,font-code))
     ,(ez-generate-binary-search-code
	'font-code
	`((,(+ #x20 (- unicode-hebrew-character-block-end
		       unicode-hebrew-character-block-start))
	    (if (>=f font-code #x20)
		(+f (-f font-code #x20)
		    unicode-hebrew-character-block-start)))
	  (,(- #x20 1)
	    (if (=f font-code ,(- #x20 1))
		,(unicode-euro-sign)))
	  (,(- #x20 2)
	    (if (=f font-code ,(- #x20 2))
		,(unicode-new-sheqel-sign)))
	  (,(- #x20 3)
	    (if (=f font-code ,(- #x20 3))
		,(unicode-french-franc-sign)))
	  (,(- #x20 4) (if (=f font-code ,(- #x20 4)) #x011e)) ; G+breve
	  (,(- #x20 5) (if (=f font-code ,(- #x20 5)) #x011f)) ; g+breve
	  (,(- #x20 6) (if (=f font-code ,(- #x20 6)) #x0130)) ; I+dot
	  (,(- #x20 7) (if (=f font-code ,(- #x20 7)) #x015c)) ; S+circumflex
	  (,(- #x20 8) (if (=f font-code ,(- #x20 8)) #x015d)) ; s+circumflex	  
	  (,(- #x20 9) (if (=f font-code ,(- #x20 9)) #x015e)) ; S+cedilla
	  (,(- #x20 10) (if (=f font-code ,(- #x20 10)) #x015f)) ; s+cedilla
	  (,(- #x20 11) (if (=f font-code ,(- #x20 11)) #x01e6)) ; G+caron
	  (,(- #x20 12) (if (=f font-code ,(- #x20 12)) #x01e7)) ; g+caron
	  (,(+ #x20
	       (- unicode-hebrew-character-block-end
		  unicode-hebrew-character-block-start)
	       1
	       (- unicode-hebrew-precomposed-character-block-end
		  unicode-hebrew-precomposed-character-block-start))
	    (if (>=f font-code
		     ,(+ #x20
			 (- unicode-hebrew-character-block-end
			    unicode-hebrew-character-block-start)
			 1))
		(+f (-f font-code
			,(+ #x20
			    (- unicode-hebrew-character-block-end
			       unicode-hebrew-character-block-start)
			    1))
		    unicode-hebrew-precomposed-character-block-start))))
	nil)))

(defmacro map-thai-font-code-to-unicode (font-code)
  `(let ((font-code ,font-code))
     ,(ez-generate-binary-search-code
	'font-code
	`((,(+ #x20 (- unicode-thai-character-block-end
		       unicode-thai-character-block-start))
	    (if (>=f font-code #x20)
		(+f (-f font-code #x20)
		    unicode-thai-character-block-start)))
	  (,(+ #x20
	       (- unicode-thai-character-block-end
		  unicode-thai-character-block-start)
	       1
	       (- unicode-thai-glyph-variants-end
		  unicode-thai-glyph-variants-start))
	    (if (>=f font-code
		     ,(+ #x20
			 (- unicode-thai-character-block-end
			    unicode-thai-character-block-start)
			 1))
		(+f (-f font-code
			,(+ #x20
			    (- unicode-thai-character-block-end
			       unicode-thai-character-block-start)
			    1))
		    unicode-thai-glyph-variants-start))))
	nil)))


;;; `Map-gensym-character-to-font' is a macro that conveys several bits of
;;; information through the side-affecting of its -var args.
;;;
;;; This determines the font to use, either a substitute or the argument
;;; ab-font. When a substitute font is required, substitute-font?-var is set to
;;; it.  Otherwise, it gets set to nil.
;;;
;;; Font-code?-var is set to the font code used to index the glyph for
;;; character-or-character-code/escape-character?  in resulting font.  In rare
;;; cases, this might set to nil.  In those cases, none of the other values or
;;; side effects should be trusted.
;;;
;;; Magnification?-var is either nil or a magnification to be applied to
;;; the scale the substitute font characters.
;;;
;;; This function return value is the type of the font to be used, i.e., either
;;; KANJI or ROMAN, which must also be the value of the ab-font-type slot of
;;; either the substitute-font, if any, or ab-font.

#+OBSOLETE ; (MHD 8/16/96)
(defmacro map-gensym-character-to-font
    (character-or-character-code
      escape-character? ab-font
      font-code?-var substitute-font?-var magnification?-var)
  (avoiding-variable-capture
      (character-or-character-code
	escape-character? ab-font
	&aux cyrillic-font-name-and-magnification
	     kanji-font-name-and-magnification)
    `(if (and ,escape-character?
	      (char= ,escape-character? #\\))
	 (cond
	   ((legal-gensym-cyrillic-character-p ,character-or-character-code)
	    (let* ((,cyrillic-font-name-and-magnification
		      (get-corresponding-cyrillic-font-name-and-magnification
			(ab-font-name ,ab-font))))
	      (setf ,substitute-font?-var
		    (ab-font (car ,cyrillic-font-name-and-magnification)))
	      (setf ,magnification?-var
		    (cdr ,cyrillic-font-name-and-magnification))
	      (setf ,font-code?-var
		    (map-to-cyrillic-font-code-if-any
		      ,character-or-character-code))
	      'roman))			; meaning "small character set"
	   (t
	    (let* ((,kanji-font-name-and-magnification
		      (get-corresponding-kanji-font-name-and-magnification
			(ab-font-name ,ab-font))))
	      (setf ,substitute-font?-var
		    (ab-font (car ,kanji-font-name-and-magnification)))
	      (setf ,magnification?-var
		    (cdr ,kanji-font-name-and-magnification))
	      (setf ,font-code?-var ,character-or-character-code)
	      'kanji)))			; meaning "large character set"
	 (progn	   
	   (setf ,substitute-font?-var nil)
	   (setf ,magnification?-var nil)
	   (setf ,font-code?-var 
		 (map-to-non-kanji-font-character-code-if-any
		   ,character-or-character-code ,escape-character?))
	   'roman))))



;;; `Get-scaled-gensym-character-set-width-as-text-width' ...
;;;
;;; `Get-gensym-character-set-width-as-text-width' computes a set width for a
;;; character both for purposes of rendering and for (re)formatting.  Note that
;;; this computation must be exactly in synch for both rendering and formatting
;;; or graphical errors could result....
;;;
;;; This does not yet handle fixed-width spaces and certain other @ complex
;;; characters.  The @ complex characters at present all return the width 0.
;;; This is technically incorrect for the spacing versions of these characters
;;; (@V, et al).  They're not fully implemented at present, e.g., by the
;;; formatter or allowed by the UI, so this will need revisiting when and if
;;; they some day are implemented and promulgated.
;;;
;;; It is an error for this to be called other than with an argument ab font has
;;; a corresponding kanji font, if necessary, and such that both ab-font and its
;;; corresponding kanji font have been set up properly handle missing
;;; characters.  This always returns a text width; if the designated character
;;; does not exist in the font, then the appropriate missing-character-set-width
;;; is returned.

;; Consider either dropping or, alternatively, making further use of,
;; ab-font-type-if-known?.  For now, I don't want to use it because it's a bit
;; ugly, and the efficiency gain seems negligable.

#+OBSOLETE ; (MHD 8/16/96)
(defun-substitution-macro get-gensym-character-image
    (character-or-character-code orientation-code
      escape-character? scaled-font ab-font)
  (let* (font-code? substitute-font? magnification?)
    (map-gensym-character-to-font
      character-or-character-code escape-character? ab-font
      font-code? substitute-font? magnification?)
    (when font-code?
      (let* ((ab-font (or substitute-font? ab-font))
	     (scaled-font
	       (if substitute-font?
		   (let ((oriented-x-scale (scaled-font-x-scale scaled-font))
			 (oriented-y-scale (scaled-font-y-scale scaled-font)))
		     (get-or-make-scaled-font
		       (if magnification?
			   (magnify oriented-x-scale magnification?)
			   oriented-x-scale)
		       (if magnification?
			   (magnify oriented-y-scale magnification?)
			   oriented-y-scale)
		       substitute-font?
		       nil))
		   scaled-font)))
	(prog1 (progn
		 (when substitute-font?
		   (lock-scaled-font scaled-font))
		 (get-or-make-character-image-if-any
		   font-code? orientation-code scaled-font ab-font))
	  (when substitute-font?
	    (unlock-scaled-font scaled-font)))))))

;; added orientation (pbk) 12/7/95

(defun-simple get-or-make-cyrillic-character-image
    (cyrillic-font-code orientation-code scaled-font ab-font)
  (declare (type fixnum cyrillic-font-code))
  (let* ((cyrillic-font
	   (ab-font			; ignore mag., known to be nil
	     (car
	       (get-corresponding-cyrillic-font-name-and-magnification
		 (ab-font-name ab-font)))))
	 (cyrillic-scaled-font
	   (or (corresponding-cyrillic-scaled-font? scaled-font)
	       (let ((sf
		       (setf (corresponding-cyrillic-scaled-font? scaled-font)
			     (get-or-make-scaled-font
			       (scaled-font-x-scale scaled-font)
			       (scaled-font-y-scale scaled-font)
			       cyrillic-font nil)))) ; scaled font locked 
		 (gensym-pushnew scaled-font (parents-of-cyrillic-scaled-font? sf))
		 sf))))
    (get-or-make-non-kanji-character-image-if-any
      cyrillic-font-code
      cyrillic-scaled-font cyrillic-font orientation-code)))

(defun-simple get-or-make-hebrew-character-image
    (hebrew-font-code orientation-code scaled-font ab-font)
  (declare (type fixnum hebrew-font-code))
  (let* ((hebrew-font
	   (ab-font			; ignore mag., known to be nil
	     (car
	       (get-corresponding-hebrew-font-name-and-magnification
		 (ab-font-name ab-font)))))
	 (hebrew-scaled-font
	   (or (corresponding-hebrew-scaled-font? scaled-font)
	       (let ((sf
		       (setf (corresponding-hebrew-scaled-font? scaled-font)
			     (get-or-make-scaled-font
			       (scaled-font-x-scale scaled-font)
			       (scaled-font-y-scale scaled-font)
			       hebrew-font nil)))) ; scaled font locked 
		 (gensym-pushnew scaled-font (parents-of-hebrew-scaled-font? sf))
		 sf))))
    (get-or-make-non-kanji-character-image-if-any
      hebrew-font-code
      hebrew-scaled-font hebrew-font orientation-code)))

(defun-simple get-or-make-thai-character-image
    (thai-font-code orientation-code scaled-font ab-font)
  (declare (type fixnum thai-font-code))
  (let* ((thai-font
	   (ab-font			; ignore mag., known to be nil
	     (car
	       (get-corresponding-thai-font-name-and-magnification
		 (ab-font-name ab-font)))))
	 (thai-scaled-font
	   (or (corresponding-thai-scaled-font? scaled-font)
	       (let ((sf
		       (setf (corresponding-thai-scaled-font? scaled-font)
			     (get-or-make-scaled-font
			       (scaled-font-x-scale scaled-font)
			       (scaled-font-y-scale scaled-font)
			       thai-font nil)))) ; scaled font locked 
		 (gensym-pushnew scaled-font (parents-of-thai-scaled-font? sf))
		 sf))))
    (get-or-make-non-kanji-character-image-if-any
      thai-font-code
      thai-scaled-font thai-font orientation-code)))      

(defun-simple get-or-make-kanji-character-image
    (unicode orientation-code scaled-font ab-font)
  (declare (type fixnum unicode)
	   (type fixnum orientation-code))
  (let* ((kanji-font-and-magnification
	   (get-corresponding-kanji-font-name-and-magnification
	     (ab-font-name ab-font)))
	 (kanji-font
	   (ab-font (car kanji-font-and-magnification)))
	 (magnification?
	   (cdr kanji-font-and-magnification))
	 (kanji-scaled-font
	   (or (corresponding-kanji-scaled-font? scaled-font)
	       (let ((sf
		       (setf (corresponding-kanji-scaled-font? scaled-font)
			     (if magnification?
				 (get-or-make-scaled-font
				   (magnify
				     (scaled-font-x-scale scaled-font)
				     magnification?)
				   (magnify
				     (scaled-font-y-scale scaled-font)
				     magnification?)
				   kanji-font
				   nil) ; scaled font locked
				 (get-or-make-scaled-font
				   (scaled-font-x-scale scaled-font)
				   (scaled-font-y-scale scaled-font)
				   kanji-font
				   nil))))) ; scaled font locked
		 (gensym-pushnew scaled-font (parents-of-kanji-scaled-font? sf))
		 sf))))
    (get-or-make-kanji-character-image-if-any-macro
      unicode
      kanji-scaled-font
      kanji-font
      orientation-code)))

#+development
(defun check-fonts ()
  (loop for fn in '(hm18 hm14 thai24 hebrew24 hebrew18 hebrew14 thai18
		    thai14 hm24 slavic24 hb72 kanji24 kanji16 blob18 slavic14 slavic18)
	as ab-font = (ab-font fn)
	always (check-ab-font ab-font)))

#+development
(defun check-ab-font (ab-font)
  (loop for scaled-font in (cdr (ab-font-cache-of-scaled-fonts ab-font))
	as kanji? = (corresponding-kanji-scaled-font? scaled-font)
	as ok-1 = (check-scaled-font ab-font scaled-font)
	as ok-2 = (or (null kanji?)
		    (kanji-scaled-font-p kanji?))
	unless ok-1
	  do (warn "Corresponding Kanji font for ~s isn't Kanji!: ~s" scaled-font kanji?)
	always (and ok-1 ok-2)))

#+development
(defun check-scaled-font (ab-font scaled-font)
  (let* ((parents (parents-of-kanji-scaled-font? scaled-font))
	 (backlink-ok?
	   (eq (ab-font-for-scaled-font scaled-font) ab-font))
	 (parents-ok?
	   (loop for parent in parents
		 always (and (kanji-scaled-font-p scaled-font)
			     (scaled-font-p parent)
			     (not (kanji-scaled-font-p parent))
			     (eq (corresponding-kanji-scaled-font? parent) scaled-font))))
	 (chars-ok?
	   (check-scaled-font-chars scaled-font)))
    (unless parents-ok?
      (warn "Problem with parents: ~s" parents))
    (and backlink-ok?
	 parents-ok?
	 chars-ok?)))

#+development
(defun check-scaled-font-chars (scaled-font)
  (loop with cache = (scaled-font-character-image-cache scaled-font)
	with type = (ab-font-type (ab-font-for-scaled-font scaled-font))
	for i below (length cache)
	as char? = (aref cache i)
	as ok = (or (null char?)
		    (case type
		      (kanji (large-scaled-font-bucket-p char?))
		      (t (character-image-p char?))))
	unless ok
	  do (warn "Problem with ~d ~s in ~s" i char? scaled-font)
	always ok))

#+development
(defun kanji-font-p (ab-font)
  (and (ab-font-p ab-font)
       (eq (ab-font-type ab-font) 'kanji)))

#+development
(defun kanji-scaled-font-p (scaled-font)
  (kanji-font-p (ab-font-for-scaled-font scaled-font)))



(defmacro map-unicode-to-ab-cyrillic-font-code-if-any-macro (unicode)
  (avoiding-variable-capture (unicode)
    `(if (<=f 0 (-f ,unicode unicode-cyrillic-character-block-start) 96)
	 (+f #x20 (-f ,unicode unicode-cyrillic-character-block-start)))))

(defun map-unicode-to-ab-cyrillic-font-code-if-any (unicode)
  (declare (type fixnum unicode))
  (map-unicode-to-ab-cyrillic-font-code-if-any-macro unicode))





(defmacro map-unicode-to-ab-hebrew-font-code-if-any-macro (unicode)
  `(let ((unicode ,unicode))
     ,(ez-generate-binary-search-code
	'unicode
	`((,unicode-hebrew-character-block-end
	     (if (>=f unicode ,unicode-hebrew-character-block-start)
		 (+f #x20 (-f unicode ,unicode-hebrew-character-block-start))))
	  (,(unicode-euro-sign)
	    (if (=f unicode ,(unicode-euro-sign))
		(-f #x20 1)))
	  (,(unicode-new-sheqel-sign)
	    (if (=f unicode ,(unicode-new-sheqel-sign))
		(-f #x20 2)))
	  (,(unicode-french-franc-sign)
	    (if (=f unicode ,(unicode-french-franc-sign))
		(-f #x20 3)))
	  (#x011e (if (=f unicode #x011e) (-f #x20 4))) ; G+breve
	  (#x011f (if (=f unicode #x011f) (-f #x20 5))) ; g+breve
	  (#x0130 (if (=f unicode #x0130) (-f #x20 6))) ; I+dot

	  (#x015c (if (=f unicode #x015c) (-f #x20 7))) ; S+circumflex
	  (#x015d (if (=f unicode #x015d) (-f #x20 8))) ; s+circumflex	  
	  (#x015e (if (=f unicode #x015e) (-f #x20 9))) ; S+cedilla
	  (#x015f (if (=f unicode #x015f) (-f #x20 10))) ; s+cedilla
	  (#x01e6 (if (=f unicode #x01e6) (-f #x20 11))) ; G+caron
	  (#x01e7 (if (=f unicode #x01e7) (-f #x20 12))) ; g+caron

	  (,unicode-hebrew-precomposed-character-block-end
	     (if (>=f unicode ,unicode-hebrew-precomposed-character-block-start)
		 (+f #x20
		     (+f (-f ,unicode-hebrew-character-block-end
			     ,unicode-hebrew-character-block-start)
			 1)
		     (-f ,unicode ,unicode-hebrew-precomposed-character-block-start)))))
	nil)))

;; Based on code for hebrew-unicode-p.  Too much of these definitions, and that
;; of map-hebrew-font-code-to-unicode, is common, and should be abstracted out!
;; (MHD 10/13/99)

(defun map-unicode-to-ab-hebrew-font-code-if-any (unicode)
  (declare (type fixnum unicode))
  (map-unicode-to-ab-hebrew-font-code-if-any-macro unicode))





(defmacro map-unicode-to-ab-thai-font-code-if-any-macro (unicode)
  `(let ((unicode ,unicode))
     ,(ez-generate-binary-search-code
	'unicode
	`((,unicode-thai-character-block-end
	     (if (>=f unicode ,unicode-thai-character-block-start)
		 (+f #x20 (-f unicode ,unicode-thai-character-block-start))))
	  
	  (,unicode-thai-glyph-variants-end
	     (if (>=f unicode ,unicode-thai-glyph-variants-start)
		 (+f #x20
		     (+f (-f ,unicode-thai-character-block-end
			     ,unicode-thai-character-block-start)
			 1)
		     (-f ,unicode ,unicode-thai-glyph-variants-start)))))
	nil)))

(defun map-unicode-to-ab-thai-font-code-if-any (unicode)
  (declare (type fixnum unicode))
  (map-unicode-to-ab-thai-font-code-if-any-macro unicode))

;; based on thai-unicode-p.



#+obsolete				; (MHD 4/9/99)
(defmacro map-unicode-to-ab-kanji-font-code-if-any-macro (unicode)
  `(map-unicode-to-gensym-han-character-code ,unicode))

(defun-substitution-macro get-unicode-character-image
    (unicode-wide-character orientation-code scaled-font ab-font)
  (let* ((unicode (wide-character-code unicode-wide-character))
	 font-code)
    (declare (type fixnum unicode))
    (cond
      ((/=f (setq font-code
		  (map-unicode-to-ab-latin-font-code-or-zero-macro unicode))
	    0)
       (get-or-make-non-kanji-character-image-if-any
	 font-code scaled-font ab-font orientation-code))
      ((setq font-code
	     (map-unicode-to-ab-cyrillic-font-code-if-any unicode))
       (get-or-make-cyrillic-character-image
	 font-code orientation-code scaled-font ab-font))
      ((setq font-code
	     (map-unicode-to-ab-hebrew-font-code-if-any unicode))
       (get-or-make-hebrew-character-image
	 font-code orientation-code scaled-font ab-font))
      ((setq font-code
	     (map-unicode-to-ab-thai-font-code-if-any unicode))
       (get-or-make-thai-character-image
	 font-code orientation-code scaled-font ab-font))
      ((get-or-make-kanji-character-image
	 unicode orientation-code scaled-font ab-font))
      (t
       ;; none available; use substitute:
       (get-or-make-non-kanji-character-image-if-any
	 0 scaled-font ab-font orientation-code)))))

(defun-simple get-unicode-set-width-as-text-width
    (unicode-wide-character ab-font)
  (case (classify-character-for-text-line-drawing unicode-wide-character)
    (mark
     (let* ((unicode (wide-character-code unicode-wide-character))
	    font-code
	    (final-font ab-font)
	    (magnification? nil))
       (declare (type fixnum unicode))
       (let ((width
	       (text-width-for-character
		 (cond
		   ((/=f (setq font-code
			       (map-unicode-to-ab-latin-font-code-or-zero-macro unicode))
			 0)
		    (svref (ab-font-character-description-table ab-font)
			   font-code))
		   ((setq font-code
			  (map-unicode-to-ab-cyrillic-font-code-if-any unicode))
		    (setq final-font

			  (or
			    (ab-font
			      (car 
				(get-corresponding-cyrillic-font-name-and-magnification
				  (ab-font-name ab-font))))
			    ;; random fall-through, but it's more like the 4.0
			    ;; behavior, and fixes the abort in print-frame with
			    ;; Russian text! (MHD 5/7/97)
			    ab-font))
		    (svref (ab-font-character-description-table final-font)
			   font-code))
		   ((setq font-code
			  (map-unicode-to-ab-hebrew-font-code-if-any unicode))
		    (setq final-font
			  (or
			    (ab-font
			      (car 
				(get-corresponding-hebrew-font-name-and-magnification
				  (ab-font-name ab-font))))
			    ab-font))
		    (svref (ab-font-character-description-table final-font)
			   font-code))
		   ((setq font-code
			  (map-unicode-to-ab-thai-font-code-if-any unicode))
		    (setq final-font
			  (or
			    (ab-font
			      (car 
				(get-corresponding-thai-font-name-and-magnification
				  (ab-font-name ab-font))))
			    ab-font))
		    (svref (ab-font-character-description-table final-font)
			   font-code))
		   ((setq font-code	; "Kanji font" now stores character 
			  unicode)	;   descriptions by unicode (MHD 4/9/99)
		    (let ((kanji-font-name-and-magnification
			    (get-corresponding-kanji-font-name-and-magnification
			      (ab-font-name ab-font))))
		      (setq final-font 
			    (ab-font (car kanji-font-name-and-magnification)))
		      (setq magnification? (cdr kanji-font-name-and-magnification))
		      (if (fixed-text-width-of-font? final-font)
			  nil		; currently always the case in practice (MHD 4/9/99)
			  (get-kanji-character-description-if-any
			    font-code
			    (ab-font-character-description-table final-font)))))
		   ;; Next case obsolete: now buck stops at the "Kanji" font 
		   ;; case, above. (MHD 4/9/99)
;		   (t
;		    ;; none available; use substitute:
;		    (svref (ab-font-character-description-table ab-font)
;			   0))
		   )
		 final-font)))
	 (declare (type fixnum width))
	 (when magnification?
	   (setq width (magnify width magnification?)))
	 width)))
    (t 0)))

;; The call explicit checking for fixed with is necessary because we don't
;; create character descriptions for some of the Kanji font characters at all
;; now until they're "needed".  I don't want to say they're "needed" in this
;; case, since that involves possibly needless expense to load them.  I'd like
;; to fix this by putting this detailed knowledge into text-width-for-character,
;; change it to take a font code instead of a character description, and fix its
;; few callers.  Needs review: a quick plan, which I'm deferring. (MHD 4/22/95)

;; OK for @L, etc.; handle fixed spaces (@V, etc.)! (MHD 6/14/95)
  

(defun-substitution-macro get-scaled-unicode-set-width-as-text-width
    (unicode-wide-character scaled-font ab-font)
  (delta-x-in-window
    (get-unicode-set-width-as-text-width unicode-wide-character ab-font)
    (scaled-font-x-scale scaled-font)))

;; You could magnify either the text width or the scale.  Magnifying the text
;; width rather than the scale would result in slightly more round off error
;; (when reducing) because text widths have lower resolutions than scales (12
;; vs. 8 bits).  But this shouldn't be noticeable, and does not seem worth the
;; extra complication of doing it differently when formatting.  Note, however,
;; that in 3.0 we magnified the scale while rendering, and the width while
;; formatting (because the scale never changed).  Now, as of 4.0, we always just
;; magnify the width, and apply scaling on top of that when rendering.  This
;; seems reasonable and sane. (MHD 3/10/95)

;; The above convention for noncharacter substitution may be repeated elsewhere
;; in this file without further commentary.

;; Wide-string replacement for the following, but implemented in terms of the
;; following for the transition. (MHD 11/17/95)



(defun render-character-image
    (subtract-instead?
      character-image?
      text-x-a text-x-b
      normalized-width normalized-height
      text-orientation icon-orientation
      x-scale y-scale
      clipped-left-edge clipped-top-edge
      clipped-right-edge clipped-bottom-edge
      color-difference baseline-in-window
      paint-to-current-scratchpad-raster-instead?)

  #-text-element-reflection-rotation
  (declare (ignore text-orientation))
  (let* ((left-edge-of-character-raster-in-window
	   (incremented-text-x-as-x
	     text-x-a text-x-b
	     (character-image-text-x-offset character-image?)))
	 (top-edge-of-character-raster-in-window
	   (+r baseline-in-window
	       (character-image-y-offset character-image?)))
	 (right-edge-of-character-raster-in-window
	   (+r left-edge-of-character-raster-in-window
	       (character-image-width character-image?)))
	 (bottom-edge-of-character-raster-in-window
	   (+r top-edge-of-character-raster-in-window
	       (character-image-height character-image?))))

  
    #+text-element-reflection-rotation
    (when (and  normalized-width normalized-height
		(not (eq text-orientation 'normal)))
      (orient-points-for-icon 
	  text-orientation
	  (-r clipped-right-edge clipped-left-edge)
	  (-r clipped-bottom-edge clipped-top-edge)
	left-edge-of-character-raster-in-window
	top-edge-of-character-raster-in-window
	right-edge-of-character-raster-in-window
	bottom-edge-of-character-raster-in-window)
      (psetf left-edge-of-character-raster-in-window
	     (minr left-edge-of-character-raster-in-window
		   right-edge-of-character-raster-in-window)
	     right-edge-of-character-raster-in-window
	     (maxr  left-edge-of-character-raster-in-window
		    right-edge-of-character-raster-in-window)
	     top-edge-of-character-raster-in-window
	     (minr top-edge-of-character-raster-in-window
		   bottom-edge-of-character-raster-in-window)
	     bottom-edge-of-character-raster-in-window
	     (maxr top-edge-of-character-raster-in-window
		   bottom-edge-of-character-raster-in-window)))
     
    (when (and  normalized-width normalized-height
	       (not (eq icon-orientation 'normal)))
      (orient-points-for-icon 
	  icon-orientation
	  (delta-x-in-window normalized-width x-scale)
	  (delta-y-in-window normalized-height y-scale)
	left-edge-of-character-raster-in-window
	top-edge-of-character-raster-in-window
	right-edge-of-character-raster-in-window
	bottom-edge-of-character-raster-in-window)
      (psetf left-edge-of-character-raster-in-window
	     (minr left-edge-of-character-raster-in-window
		   right-edge-of-character-raster-in-window)
	     right-edge-of-character-raster-in-window
	     (maxr  left-edge-of-character-raster-in-window
		    right-edge-of-character-raster-in-window)
	     top-edge-of-character-raster-in-window
	     (minr top-edge-of-character-raster-in-window
		   bottom-edge-of-character-raster-in-window)
	     bottom-edge-of-character-raster-in-window
	     (maxr top-edge-of-character-raster-in-window
		   bottom-edge-of-character-raster-in-window)))
      
    (let* ((left-edge-within-clipped-area
	     (maxr clipped-left-edge
		   left-edge-of-character-raster-in-window))
	   (top-edge-within-clipped-area 
	     (maxr clipped-top-edge
		   top-edge-of-character-raster-in-window))
	   (right-edge-within-clipped-area
	     (minr clipped-right-edge
		   right-edge-of-character-raster-in-window))
	   (bottom-edge-within-clipped-area
	     (minr clipped-bottom-edge
		   bottom-edge-of-character-raster-in-window)))
      
      (when (and (>r right-edge-within-clipped-area
		     left-edge-within-clipped-area)
		 (>r bottom-edge-within-clipped-area
		     top-edge-within-clipped-area))
	(let ((character-raster (character-raster character-image?))
	      (left-edge-in-stored-raster
		(-r left-edge-within-clipped-area
		    left-edge-of-character-raster-in-window))
	      (top-edge-in-stored-raster
		(-r top-edge-within-clipped-area
		    top-edge-of-character-raster-in-window)))
	  (if paint-to-current-scratchpad-raster-instead?
	      (cond
		(current-scratchpad-raster-tiled-p
		 ;; (format t "color difference=~s~%" color-difference) pbk
		 (on-current-scratchpad-raster-tiles
		     ((left-edge-within-clipped-area right-edge-within-clipped-area)
		      (top-edge-within-clipped-area bottom-edge-within-clipped-area)
		      left-edge-within-clipped-area  top-edge-within-clipped-area 
		      right-edge-within-clipped-area bottom-edge-within-clipped-area
		      current-scratchpad-raster)
		   (case current-scratchpad-raster-type
		     (x11-pixmap
		      (c-x11-copy-bitmap-to-bitmap
			character-raster tile-to-paint
			left-edge-in-stored-raster top-edge-in-stored-raster
			left-edge-within-clipped-area top-edge-within-clipped-area
			(-r right-edge-within-clipped-area left-edge-within-clipped-area)
			(-r bottom-edge-within-clipped-area top-edge-within-clipped-area)
			color-difference))))) 
		;; need to copy to a temporary raster, perform rotation-and-reflection
		;; and then copy into the actual tiled-raster
		(t
		 (paint-from-stored-raster-to-current-scratchpad-raster
		   left-edge-within-clipped-area top-edge-within-clipped-area
		   right-edge-within-clipped-area bottom-edge-within-clipped-area
		   character-raster
		   left-edge-in-stored-raster top-edge-in-stored-raster
		   color-difference)))	; color-value (1 or 0) in this case!
	      (add-from-stored-raster-to-current-window	; a macro
		subtract-instead?
		left-edge-within-clipped-area top-edge-within-clipped-area
		right-edge-within-clipped-area bottom-edge-within-clipped-area
		color-difference character-raster
		left-edge-in-stored-raster top-edge-in-stored-raster))))))
  nil)




(defun-substitution-macro unicode-same-native-set-width-p
    (native-font unicode-wide-character)
  ;; For now, we know that this table holds truth values for the ISO Latin-1
  ;; Codes that are in Unicode in the range 0..255, so we give that answer based
  ;; on that truth value if the code is in that range; otherwise, the answer is
  ;; simply no.
  (let ((code (wide-character-code unicode-wide-character)))
    (declare (type fixnum code))
    (if (<f code native-font-set-width-equivalence-table-size)
	(svref (native-font-set-width-equivalence-table native-font)
	       code))))


;;; `With-x-drawable-string' is used within render-string-using-native-font to
;;; bind a temporary string whose contents are derived from the segment of
;;; text-string starting at start, including all characters before end.  This is
;;; designed to produce a simple gensym string, such as can be passed down
;;; through the C foreign function interface without any need for copying.  It
;;; handles all copying and reclamation issues.  Note that this assumes that all
;;; characters between start and end are 8-bit, ISO-Latin-1 characters, already
;;; known to be able to be rendered by the X Window System using the specified
;;; native font.  Note that string-variable will be bound to a gensym string,
;;; and so cannot have wide-string operations (e.g., charw, lengthw) applied to
;;; it.

(defmacro with-x-drawable-string ((string-variable text-string start end)
				  &body body)
  (avoiding-variable-capture (text-string start end &aux i j)
    `(let ((,string-variable
	      (obtain-simple-gensym-string
		(-f end start))))
       (loop for ,i from ,start below ,end ; See note
	     as ,j from 0
	     do (setf (schar ,string-variable ,j)
		      (wide-character-to-character
			(charw ,text-string ,i))))
       (prog1 (progn . ,body)
	 (reclaim-gensym-string ,string-variable)))))

;; Note: ideally, the copying operation should be made faster, ideally using a C
;; or assembly routine. However, no such operation currently exists for the
;; wide-string to gensym-string case. (MHD 5/5/97)



;;; `Render-string-using-native-font' ... 

(defun-void render-string-using-native-font
    (start end
      native-font
      clipped-left-edge clipped-top-edge
      clipped-right-edge clipped-bottom-edge
      text-line color-difference
      start-text-x-a start-text-x-b
      end-text-x-a end-text-x-b
      baseline-in-window)
  (with-x-drawable-string (x-string text-line start end) ; reformat some day
  (let* ((start-left-edge (text-x-to-x start-text-x-a start-text-x-b))
	 (end-right-edge (text-x-to-x end-text-x-a end-text-x-b)))
    (cond
      ((or (<r (-r start-left-edge 4) clipped-left-edge)
	   (>r (+r end-right-edge 4) clipped-right-edge)
	   (<r (-r baseline-in-window 30)
	       clipped-top-edge)
	   (>r (+r baseline-in-window 10)
	       clipped-bottom-edge))
       ;; check for need for clipping with a kludge that adds enough slop around
       ;; known positions in the line to be ok for HM14, 18, 24; needs work!
       (c-x11-draw-string-in-font-with-clipping
	 current-native-window?
	 start-left-edge baseline-in-window
	 clipped-left-edge clipped-top-edge
	 clipped-right-edge clipped-bottom-edge
	 (infer-color-value-from-color-difference-and-transfer-mode color-difference)
	 (current-transfer-mode-for-x11-windows)
	 (native-font-c-pointer native-font)
	 x-string (-f end start)))
      (t
       (c-x11-draw-string-in-font
	 current-native-window?
	 start-left-edge baseline-in-window
	 (infer-color-value-from-color-difference-and-transfer-mode color-difference)
	 (current-transfer-mode-for-x11-windows)
	 (native-font-c-pointer native-font)
	 x-string (-f end start)))))))



;;; Add-from-line-of-text-to-current-window ....  Font-map is a sequence which
;;; consists of at least one element (the first element is called the zeroeth
;;; element) and all of whose elements are ab-font names.... Word-spacing is a
;;; text-width at normalized scale....  Note that x-scale and y-scale may not be
;;; the current x and y scale, due to magnification.

;;; Paint-from-line-of-text-to-current-scratchpad-raster ... is similar, except
;;; that (1) there is no erase-instead? argument, (2) there is a color-value
;;; argument instead of a color-difference, and (3) the
;;; left-edge-of-line-of-text-in-window and baseline-in-window arguments refer
;;; to the coordinate system of the raster.

;;; Add-from-line-of-text-to-current-window-1 is a substitution-macro
;;; subfunction of the above two functions.  In the case where
;;; paint-to-current-scratchpad- raster-instead? is true, this ignores
;;; subtract-instead?, treats color-difference as a color value, and paints
;;; text-line into current-scratchpad-raster. In the other case
;;; (paint-to-current-scratchpad-raster-instead? is false), these argument names
;;; make sense, and this adds text-line to the current window accordingly.


(defun add-from-line-of-text-to-current-window-1
  (subtract-instead?
    clipped-left-edge clipped-top-edge
    clipped-right-edge clipped-bottom-edge
    normalized-width normalized-height 
    text-line
    text-orientation icon-orientation
    word-spacing font-map color-difference
    normalized-x-scale normalized-y-scale
    left-edge-of-line-of-text-in-window
    baseline-in-window paint-to-current-scratchpad-raster-instead?)
   
  (loop with combined-orientation
	  = #+text-element-reflection-rotation
	    (multiply-reflection-and-rotation text-orientation icon-orientation)
	    #-text-element-reflection-rotation
	    icon-orientation
	with ab-font = (ab-font (car font-map))	; fix this!
	with orientation-code = (get-orientation-code combined-orientation)
	with oriented-x-scale =
	(oriented-x-value normalized-x-scale normalized-y-scale orientation-code)
	with oriented-y-scale =
	(oriented-y-value normalized-x-scale normalized-y-scale orientation-code)
	with scaled-font
	  = (get-or-make-scaled-font-with-lock	; Note 7
	      oriented-x-scale oriented-y-scale ab-font nil)
	with native-font? = (unless (or paint-to-current-scratchpad-raster-instead?
					(not enable-native-fonts?)
					(not (=f orientation-code 0))
					;; for some reason, native fonts only
					;; work in paint mode, so prohibit
					;; native fonts in XOR drawing case:
					(xor-mode-p))
			      (corresponding-native-font? scaled-font))
	with word-spacing-at-current-scale
	fixnum = (delta-x-in-window word-spacing oriented-x-scale)
	with normalized-clipped-right-edge = clipped-right-edge
	with normalized-clipped-left-edge = clipped-left-edge
	with line-length fixnum = (text-line-length text-line)
	with previous-i fixnum = 0
	with i fixnum = 0
	with text-x-a fixnum = 0
	with text-x-b fixnum = 0
	with set-width-at-current-scale fixnum = 0
	with start-for-native-string? = nil
	with native-string-text-x-a fixnum = 0
	with native-string-text-x-b fixnum = 0
	with render-this-character? = nil
	with last-mark-wide-character? = nil
	with previous-nsm-y-offset? = nil ; for trivial diacritic "stacking"
	with unicode-wide-character
	with character-classification	; markup, ordinary-space, or mark
	initially
	  (set-text-x text-x-a text-x-b left-edge-of-line-of-text-in-window)
	  (when (and normalized-width normalized-height
		     (not (eq icon-orientation 'normal)))
	    (orient-points-for-icon
		icon-orientation
		(delta-x-in-window normalized-width oriented-x-scale)
		(delta-y-in-window normalized-height oriented-y-scale)
	      clipped-left-edge
	      clipped-top-edge
	      clipped-right-edge
	      clipped-bottom-edge)
	    (psetf clipped-left-edge
		   (minw clipped-left-edge clipped-right-edge)
		   clipped-top-edge
		   (minw clipped-top-edge clipped-bottom-edge) 
		   clipped-right-edge
		   (maxw clipped-left-edge clipped-right-edge)
		   clipped-bottom-edge
		   (maxw clipped-top-edge clipped-bottom-edge)))
	
	do (let ((finish-loop?
		   (or (>=f i line-length)
		       (>=r (text-x-to-x text-x-a text-x-b)
			    normalized-clipped-right-edge))))
	     (when start-for-native-string?
	       (let ((run-ended-on-previous-char?
		       (or render-this-character? ; just ended a run of characters
			   (eq character-classification 'non-graphic)
			   (eq character-classification 'ordinary-space)
			   (eq character-classification 'zero-width-space))))
		 (when (or finish-loop? run-ended-on-previous-char?)
		   (render-string-using-native-font
		     start-for-native-string?
		     (if run-ended-on-previous-char?
			 previous-i
			 i)
		     native-font? 		 
		     clipped-left-edge clipped-top-edge
		     clipped-right-edge clipped-bottom-edge
		     text-line color-difference
		     native-string-text-x-a native-string-text-x-b
		     text-x-a text-x-b
		     baseline-in-window)
		   (setq start-for-native-string? nil))))
	     (when finish-loop?
	       (loop-finish)))
	   (setq previous-i i)
	   (setq unicode-wide-character
		 (read-character-from-wide-string text-line i))
	   (setq character-classification
		 (classify-character-for-text-line-drawing
		   unicode-wide-character))
    ;; Note: if you carefully check, you'll notice that the only case where
    ;; text-x-a/b is not incremented is for the case of a nonspacing mark.  The
    ;; increment happens before the rendering.  Thus, we don't space before a
    ;; non-spacing mark, causing the desired overstrike effect.  Also note that
    ;; the set-width-at-current-scale variable is not altered in the nonspacing
    ;; mark case, thus leaving it with its last, possibly spacing, value.
	   (case character-classification
	     (non-spacing-mark
	      (multiple-value-bind
		  (text-x-a text-x-b new-baseline-in-window character-image?
			    base-character-image-y-offset)
		  (offset-position-for-rendering-non-spacing-mark
		    unicode-wide-character
		    last-mark-wide-character?
		    text-x-a text-x-b
		    baseline-in-window
		    set-width-at-current-scale
		    orientation-code scaled-font ab-font
		    normalized-x-scale normalized-y-scale
		    previous-nsm-y-offset?)
		(when character-image?
		  (render-character-image
		    subtract-instead? character-image?
		    text-x-a text-x-b
		    normalized-width normalized-height
		    text-orientation
		    icon-orientation
		    oriented-x-scale oriented-y-scale 
		    clipped-left-edge clipped-top-edge
		    clipped-right-edge clipped-bottom-edge
		    color-difference new-baseline-in-window
		    paint-to-current-scratchpad-raster-instead?)
		  (setq previous-nsm-y-offset?
			(+r base-character-image-y-offset
			    (-r (character-image-y-offset character-image?))
			    (-r baseline-in-window new-baseline-in-window))))))
	     (t
	      (setq previous-nsm-y-offset? nil)
	      (case character-classification
		((non-graphic zero-width-space) ; @L, etc., most need other handling!!
		 (incf-text-x text-x-a text-x-b set-width-at-current-scale)
		 (setq set-width-at-current-scale 0)
		 (setq render-this-character? nil))
		(ordinary-space
		 (incf-text-x text-x-a text-x-b set-width-at-current-scale)
		 (setq set-width-at-current-scale
		       word-spacing-at-current-scale)
		 (setq render-this-character? nil))
		(mark
		 (setq last-mark-wide-character? unicode-wide-character)
		 (incf-text-x text-x-a text-x-b set-width-at-current-scale)
		 
		 ;; A special hack for certain Thai combinations: (MHD 12/17/03)
		 (when (or (char=w unicode-wide-character #u0E0D)
			   (char=w unicode-wide-character #u0E10))
		   (let ((peek? (if (<f i line-length) (charw text-line i))))
		     (when (and peek?
				(eq (classify-character-for-text-line-drawing peek?)
				    'non-spacing-mark)
				(eq (get-non-spacing-mark-combining-class peek?)
				    'below))
		       ;; For Thai, using font Arial Thai for Gensym, substitute code
		       ;; corresponding to PUA code with a special glyph that has a
		       ;; diacritic-like part of its underneath removed -- similar in
		       ;; concept to using the dotless-i glyph with accents.
		       (setq last-mark-wide-character?
			     (setq unicode-wide-character
				   (if (char=w unicode-wide-character #u0E0D)
				       #uF70F
				       #uF700))))))
		 
		 (setq set-width-at-current-scale
		       (get-scaled-unicode-set-width-as-text-width
			 unicode-wide-character
			 scaled-font ab-font))
		 (setq render-this-character?
		       (cond
			 ((not (<r (incremented-text-x-as-x
				     text-x-a text-x-b
				     set-width-at-current-scale)
				   normalized-clipped-left-edge))
			  (cond
			    ((and native-font?
				  (unicode-same-native-set-width-p
				    native-font? unicode-wide-character))
			     (unless start-for-native-string?
			       (setq start-for-native-string? previous-i)
			       (setq native-string-text-x-a text-x-a)
			       (setq native-string-text-x-b text-x-b))
			     nil)
			    (t t)))
			 (t nil)))
		 (when render-this-character?
		   (let* ((character-image?
			    (get-unicode-character-image
			      unicode-wide-character
			      orientation-code
			      scaled-font ab-font)))
		     (when character-image?
		       (render-character-image
			 subtract-instead? character-image?
			 text-x-a text-x-b
			 normalized-width normalized-height
			 text-orientation
			 icon-orientation
			 oriented-x-scale oriented-y-scale 
			 clipped-left-edge clipped-top-edge
			 clipped-right-edge clipped-bottom-edge
			 color-difference baseline-in-window
			 paint-to-current-scratchpad-raster-instead?))))))))
	finally
	  (unlock-scaled-font scaled-font)))

;; Changes 2/22/95
;;
;; - Take out the commented out code for doing native xwindows call and
;;   put it, in comments still, into a real macro that could be used
;;   as a sandbox for experimentation with native drawing,
;;   maybe-add-from-line-of-text-natively
;;
;;   - remove left, top, right, and bottom-edge-of-update-area variables; these
;;   had been special variables a long time ago, and had a function; now that
;;   their function has ended, they should be removed
;;
;;   - remove x-in-window-for-next-character -- it was not used
;;
;;   - abstracted out character getting code as get-gensym-character-image,
;;   which cannot really return nil with our current fonts, and should be
;;   defined to never return nil; for now the code assumes that it gets
;;   a blob character back for missing characters, but doesn't crash if
;;   nil is returned
;;
;;   - code to render missing characters as blobs flushed, no longer necessary
;;
;;   - made this bunch of variables be locally bound around their use:
;;   
;;	  left-edge-of-character-raster-in-window
;;	  top-edge-of-character-raster-in-window
;;	  right-edge-of-character-raster-in-window
;;	  bottom-edge-of-character-raster-in-window
;;	  left-edge-within-clipped-area
;;	  top-edge-within-clipped-area
;;	  right-edge-within-clipped-area
;;	  bottom-edge-within-clipped-area
;;	  left-edge-in-stored-raster
;;	  top-edge-in-stored-raster
;;
;;   - after this, it was easy to pull out this code as a subfunction (macro),
;;   render-character-image, which renders the character (paints or adds)
;;
;;   - added a function to get the scaled character text width and then
;;   made the final character rendering in its raster happen only
;;   if it's really to be drawn; i.e., clipping on the the left edge
;;   is now done as well as on the right.
;;
;;   - factored out common code to increment text-x-a/b
;;
;;   - cleaned up early exit for clipping on right slightly
;;
;; (MHD 2/22/95)

;; Note 7: The reason the font is locked is so
;; that this call won't decache the scaled font to which scaled-font is bound.
;; If this were not done, the scaled font to which scaled-font is bound could be
;; reclaimed and come back as a kanji font.  The kanji font would then be used for
;; non-kanji characters causing serious problems.

;; Consider just using clipped-left-edge et al instead of computing and using left-edge-
;; of-update-area et al, to save on the bitblting at the expense of some arithmetic.

;; Fix to save some clipping and transformation effort on each iteration!






;;; The function offset-position-for-rendering-non-spacing-mark returns nil if
;;; there is no previous wide character, or it has no glyph, or if there's no
;;; glyph for the given character (unicode-wide-character). Otherwise, this
;;; returns 5 values:
;;;
;;;   text-x-a
;;;   text-x-b
;;;   baseline-in-window
;;;   character-image
;;;   base-character-image-y-offset

(defun offset-position-for-rendering-non-spacing-mark
    (unicode-wide-character base-character?
			    text-x-a text-x-b baseline-in-window
			    set-width-for-prev-char-at-current-scale
			    orientation-code scaled-font ab-font
			    normalized-x-scale normalized-y-scale
			    &optional previous-nsm-y-offset?)
  (declare (type fixnum text-x-a text-x-b baseline-in-window orientation-code)
	   (ignore normalized-x-scale))
  (block body
    (let* ((combining-class
	     (get-non-spacing-mark-combining-class unicode-wide-character))
	   (base-character-image
	     (or (if base-character?
		     (get-unicode-character-image
		       base-character?
		       orientation-code scaled-font ab-font))
		 (return-from body nil)))
	   ;; no need to nil check base-character? beyond this point
	   (base-character-image-y-offset
	     (character-image-y-offset base-character-image))
	   (ci (or (get-unicode-character-image
		     unicode-wide-character orientation-code scaled-font ab-font)
		   (return-from body nil)))
	   (y-offset (character-image-y-offset ci))
	   (height (character-image-height ci)))      
      (declare (type fixnum base-character-image-y-offset y-offset height))
      (incf-text-x
	text-x-a text-x-b
	(case combining-class
	  ((above-rtl below-rtl center-rtl)
	   ;; advance half the previous character's width
	   (halff set-width-for-prev-char-at-current-scale))
	  (t
	   set-width-for-prev-char-at-current-scale)))
      (case combining-class
	((above-rtl below-rtl center-rtl)
	 (let ((text-x-c 0) (text-x-d 0)
	       (set-width-as-text-width
		 (character-image-set-width-as-text-width ci)))
	   (declare (type fixnum text-x-c text-x-d set-width-as-text-width))
	   (set-text-x-from-text-width
	     text-x-c text-x-d
	     (or (if (char=w unicode-wide-character #u05bc)
		     ;; hand edit for dagesh+...
		     (wide-character-case
		       base-character?
		       (#u05d5
			  (+r (halff set-width-for-prev-char-at-current-scale)
			      (halff set-width-as-text-width))))) ; vav
		 (halff set-width-as-text-width)))
	   (subtract-from-text-x text-x-a text-x-b text-x-c text-x-d))))
      (incfr baseline-in-window
	     (case combining-class
	       ((above above-rtl)
		(-w base-character-image-y-offset
		    (or previous-nsm-y-offset? 0)))
	       ((center center-rtl)
		(halfr (+w base-character-image-y-offset
			   (or previous-nsm-y-offset? 0))))
	       (t 0)))
      (case combining-class
	((above center above-rtl center-rtl)
	 (incfr baseline-in-window (-r y-offset))
	 (incfr baseline-in-window (-r height))
	 (when (or (eq combining-class 'above)
		   (eq combining-class 'above-rtl)
		   ;; hand edit for dagesh+...
		   (and (char=w unicode-wide-character #u05bc)
			(char=w base-character? #u05e4))) ; peh
	   (incfr baseline-in-window
		  (-r (delta-y-in-window 1 normalized-y-scale))))))
      (values text-x-a text-x-b baseline-in-window ci
	      base-character-image-y-offset))))



(def-icp-message-functions add-from-line-of-text-to-current-window
			   (subtract-instead?
			     (coordinate clipped-left-edge) (coordinate clipped-top-edge)
			     (coordinate clipped-right-edge) (coordinate clipped-bottom-edge)
			     text-line word-spacing font-map color-difference x-scale y-scale
			     (coordinate left-edge-of-line-of-text-in-window)
			     (coordinate baseline-in-window))
  (case type-of-current-window
    (t
     (add-from-line-of-text-to-current-window-1
       subtract-instead?
       clipped-left-edge clipped-top-edge
       clipped-right-edge clipped-bottom-edge nil nil
       text-line
       'normal 'normal ; text-element-rotation and icon-rotation
       word-spacing font-map color-difference x-scale y-scale
       left-edge-of-line-of-text-in-window
       baseline-in-window nil))))

;; need to make constant normal-orientation = 0

(def-icp-message-functions paint-from-line-of-text-to-current-scratchpad-raster
    
			   ((coordinate clipped-left-edge) (coordinate clipped-top-edge)
			    (coordinate clipped-right-edge) (coordinate clipped-bottom-edge)
			    text-line word-spacing font-map color-value
			    x-scale y-scale
			    (coordinate left-edge-of-line-of-text-in-window)
			    (coordinate baseline-in-window))
  (case type-of-current-window
    (t
     (iterate-over-monochrome-raster-list-if-appropriate (color-value)
       (add-from-line-of-text-to-current-window-1
	 nil
	 clipped-left-edge clipped-top-edge
	 clipped-right-edge clipped-bottom-edge
	 nil nil  ; width height only needed for oriented text
	 text-line
	 'normal 'normal ; text-element-rotation and icon-rotation
	 word-spacing font-map color-value x-scale y-scale
	 left-edge-of-line-of-text-in-window
	 baseline-in-window t)))))

;; This ICP message function was added today, initially for use with charts, and
;; eventually for use in graphs and icon renderings.

;; This should be fixed to support rotation and reflection, if possible before
;; it's too late to change the ICP message argument list!!  At least the
;; arguments should be put in even if they will not be implemented right away.
;; (MHD 9/29/90)


(def-icp-message-functions orient-and-paint-line-of-text-to-current-scratchpad-raster
    
			   ((coordinate clipped-left-edge) (coordinate clipped-top-edge)
			    (coordinate clipped-right-edge) (coordinate clipped-bottom-edge)
			    (unsigned-integer normalized-width) (unsigned-integer normalized-height)
			    text-line
			    (symbol text-orientation) (symbol icon-orientation)
			    word-spacing font-map color-value
			    (x-scale normalized-x-scale) (y-scale normalized-y-scale)
			    (coordinate left-edge-of-line-of-text-in-window)
			    (coordinate baseline-in-window))
  
  (case type-of-current-window
    (t
     (let* ((subtract-instead? nil)
	    (paint-to-current-scratchpad-raster-instead? t))
       (iterate-over-monochrome-raster-list-if-appropriate (color-value)
	 (add-from-line-of-text-to-current-window-1
	   subtract-instead?
	   clipped-left-edge clipped-top-edge
	   clipped-right-edge clipped-bottom-edge
	   normalized-width normalized-height
	   text-line
	   text-orientation icon-orientation
	   word-spacing font-map color-value
	   normalized-x-scale normalized-y-scale
	   left-edge-of-line-of-text-in-window
	   baseline-in-window
	   paint-to-current-scratchpad-raster-instead?))))))



;;;; Getting the Bitmap of a Font Character



;;; `Get-character-bitmap-of-font-character' ... Note that ab-font here is the
;;; exact font for the character, not the base roman font.  This returns the
;;; following values:
;;;
;;; 
;;;      character-bitmap
;;;      temporary-p               ; if true, caller must reclaim using
;;;                                ;   reclaim-temporary-character-bitmap
;;;      bounding-box-x-offset bounding-box-y-offset
;;;      bounding-box-width bounding-box-height
;;;      width-for-character       ; the character set width in pixels
;;;      text-width-for-character  ; the character set width as a
;;;                                ;   text width
;;;
;;; Note that this is to be called for Kanji or Cyrillic fonts associated with
;;; a base Roman font, not with a Roman font, and generally not for a glyph
;;; for a Latin character.  Notice that the argument is a Unicode, not a font
;;; code.  [This is new as of the pending G2 release.]
;;;
;;; This is called from module PRINTING for making offscreen "character bitmaps"
;;; to be used to make glyph definition code to be included in postscript files.

(defun get-character-bitmap-of-font-character (unicode ab-font)
  (let* ((cjk-language?
	   (get-cjk-language-of-unicode
	     unicode
	     (get-font-han-unification-mode-for-window system-window)))
	 (bitmap-preferred?
	   (or prefer-bitmap-to-scaled-outline-font?
	       (and
		 prefer-bitmap-to-scaled-outline-font-at-full-scale?
		 ;; here, we know we're at full scale (normalized-scale)
		 ;; Handle Asian exceptions, if any:
		 (full-scale-bitmap-if-asian-ok-p cjk-language?))))
	 (latin-font-code?
	   (map-unicode-to-ab-latin-font-code-or-zero unicode))
	 (font-code
	   (cond
	     ((and latin-font-code? (not (=f latin-font-code? 0)))
	      latin-font-code?)
	     ((cyrillic-unicode-p unicode)
	      (map-unicode-to-ab-cyrillic-font-code-if-any unicode))
	     ((hebrew-unicode-p unicode)
	      (map-unicode-to-ab-hebrew-font-code-if-any unicode))
	     ((thai-unicode-p unicode)
	      (map-unicode-to-ab-thai-font-code-if-any unicode))
	     (t unicode)))
	 (character-description?
	   (get-character-description-if-any font-code ab-font))
	(fixed-width-of-font?
	  (fixed-width-of-font? ab-font))
	(fixed-bounding-box-of-font?
	  (fixed-bounding-box-of-font? ab-font)))
    (when (and (null character-description?) bitmap-preferred?)
      (load-bitmap-font-data-if-necessary ab-font unicode cjk-language?)
      (setq character-description?
	    (get-character-description-if-any font-code ab-font)))
    (when (or (null character-description?)
	      (if (not (and fixed-width-of-font? fixed-bounding-box-of-font?))
		  (null (character-rectangle-array character-description?))))
      (setq character-description?
	    (load-bitmap-data-of-font-character
	      ab-font unicode font-code character-description?
	      cjk-language? bitmap-preferred?)))
    (let* ((character-description
	     (or (if (and character-description?
			  (or (and fixed-width-of-font?
				   fixed-bounding-box-of-font?)
			      (character-rectangle-array character-description?)))
		     character-description?)
		 ;; substitution glyph (blob):
		 (get-character-description-if-any 0 ab-font)))
	   (text-width-for-character
	     (text-width-for-character character-description ab-font))
	   (character-bitmap
	     (if (and fixed-width-of-font? fixed-bounding-box-of-font?)
		 character-description
		 (convert-character-rectangle-array-to-character-bitmap
		   character-description
		   t))))		; note: temporary in this case
      (values
	character-bitmap
	(not (and fixed-width-of-font? fixed-bounding-box-of-font?))
	(if fixed-bounding-box-of-font?
	    (first fixed-bounding-box-of-font?)
	    (bounding-box-x-offset character-description))
	(if fixed-bounding-box-of-font?
	    (second fixed-bounding-box-of-font?)
	    (bounding-box-y-offset character-description))
	(if fixed-bounding-box-of-font?
	    (third fixed-bounding-box-of-font?)
	    (bounding-box-width character-description))
	(if fixed-bounding-box-of-font?
	    (fourth fixed-bounding-box-of-font?)
	    (bounding-box-height character-description))
	(text-width-to-x text-width-for-character) ; some precision gets lost!
	text-width-for-character))))


(defun load-bitmap-data-of-font-character
    (ab-font unicode font-code character-description? cjk-language? bitmap-preferred?)
  (multiple-value-bind
      (success?
	text-width-x-offset y-offset
	width height set-width)
      (make-raster-for-character-using-outline-font-if-possible
	font-code 0 ab-font
	(normalized-scale) (normalized-scale) cjk-language? t)
    (cond
      (success?
       (let* ((x-offset (text-width-to-x text-width-x-offset))
	      (character-bitmap
		(if character-description?
		    (allocate-temporary-character-bitmap width height)
		    (allocate-character-bitmap
		      (or (fixed-width-of-font? ab-font) width)
		      (or (fixed-width-of-font? ab-font) height)))))
	 (when character-description?
	   ;; for temporary bitmaps, have to clear them first:
	   (fill-rectangle-in-character-bitmap
	     character-bitmap 0 0 0 width height))
	 (copy-from-fontrip-bitmap-to-character-bitmap
	   character-bitmap
	   0 width (if (fixed-width-of-font? ab-font) (maxr 0 x-offset) 0)
	   0 height (if (fixed-width-of-font? ab-font) (maxr 0 y-offset) 0))
	 (cond
	   (character-description?
	    (setq character-description?
		  (change-non-kanji-character-description
		    font-code
		    (ab-font-character-description-table ab-font)
		    (text-width-to-x set-width)
		    (convert-character-bitmap-to-rectangle-array
		      character-bitmap width height t)
		    x-offset y-offset width height set-width))
	    (reclaim-temporary-character-bitmap character-bitmap))
	   (t
	    (set-kanji-character-description
	      unicode
	      (ab-font-character-description-table ab-font)
	      character-bitmap)
	    (setq character-description?
		  character-bitmap)))))
      ((not bitmap-preferred?)
       ;; so this hasn't been tried yet; try it now:
       (load-bitmap-font-data-if-necessary ab-font unicode cjk-language?)
       (setq character-description?
	     (get-character-description-if-any font-code ab-font)))))
  character-description?)

(defun-void copy-from-fontrip-bitmap-to-character-bitmap
    (character-bitmap
      source-x0 width destination-x0
      source-y0 height destination-y0)
  (declare (type fixnum
		 source-x0 width destination-x0
		 source-y0 height destination-y0))
  ;; copy from temporary bitmap in "C" memory to the character bitmap:
  (loop for x from source-x0
	as destination-x from destination-x0
	repeat width
	do (loop for y from source-y0
		 as destination-y from destination-y0
		 repeat height
		 when (=f 1 (c-fontrip-bitmap-value x y))
		   do (setf (character-bitmap-value
			      character-bitmap destination-x destination-y)
			    1))))





;;;; Macro for Reading Gensym Characters from Strings with Lost Spaces


;;; `Read-gensym-character-from-text-string-with-lost-spaces' is just like
;;; read-gensym-character-from-text-string (q.v., in CHARACTERS) except that it
;;; is extended to handle the lost-spaces data structure, and to allow indexing
;;; into it.  Lost-spaces is simple the data structure that can be the cdr of a
;;; lost-spaces element in a text, i.e., an integer or a string containing
;;; Gensym characters containing all (presumably nonordinary) spaces.
;;; 
;;; Lost-spaces are the spaces that are implicitly at the end of the text line,
;;; but have been removed from it explicitly.  The concept of lost-spaces is
;;; fully explained in the module BOXES.  To express the default number (0) of
;;; lost spaces, pass in 0 here.

(defmacro read-unicode-character-from-wide-string-with-lost-spaces
    (wide-string index-variable line-length lost-spaces)
  (avoiding-variable-capture
      (wide-string line-length lost-spaces &aux i offset)
    `(cond
       ((<f ,index-variable ,line-length)
	(prog1 (charw ,wide-string ,index-variable)
	  (incff ,index-variable)))
       ((fixnump ,lost-spaces)
	(incff ,index-variable)
	#.%space)
       (t
	(let* ((,i (-f ,index-variable ,line-length))
	       (,offset (-f ,i)))
	  (prog1 (charw ,lost-spaces ,i)
	    (incff ,i)
	    (incff ,index-variable (+f ,i ,offset))))))))





;;;; Computing the Width of a Text Line




(defmacro word-spacing-based-tab-width (word-spacing)
  ;; Alt 1: 5 spaces -- the trusty, old typewriter convention
;  `(*w ,word-spacing 5)
  ;; Alt 2: 8 spaces -- the convention used by Emacs and Netscape 1.0:
;  `(*w ,word-spacing 8)
  
  ;; Note that the above alternatives are more appropriate for
  ;; fixed-width fonts, which we don't currently have, hence ...
  
  ;; Alt 3: 1/2 inch  (ala MSWord; text width of 9600, i.e., 37 workspace units)
  `(progn
     ,word-spacing  ; ignored
     #.(let ((points-per-inch 72)     ; PostScript uses 72; HP PCL uses 72.307
	     (resolution-in-dpi 75))
	 (round (* (convert-to-text-width (round points-per-inch 2))
		   (convert-to-text-width resolution-in-dpi))
		(convert-to-text-width points-per-inch))))
  )
     
  



;;; `Compute-width-of-text-line' returns the unmagnified workspace (normalized-scale)
;;; width of text-line, or the portion of it specified by start? and end?.  The
;;; result is normally represented in workspace (or normalized-scale) units, but
;;; when return-text-width? is non-nil, the result is represented as a text width.
;;; Text-line can be any string that consists entirely of Gensym characters.
;;; Start? and end?, when non-nil, are Common Lisp string positions.  Word-spacing
;;; may be arbitrary if there are no spaces in string.  Return-text-width? should be
;;; non-nil only when it is known that the result can be represented as a text width.

;;; This intentionally does not include indentation or take scale or magnification
;;; into account, and it does not yet handle fixed-width spaces and certain other
;;; @ complex characters.  Lost spaces for text-line are included only as specified
;;; by the lost-spaces argument.

(defun compute-width-of-text-line
    (text-line start? end? font-map word-spacing
	       &optional return-text-width? (lost-spaces 0)
	                 tab-width?)	; as a text width
  (loop with ab-font = (ab-font (car font-map))
	with line-length fixnum = (text-line-length text-line)
	with end fixnum
		 = (or end?
		       (if (and (fixnump lost-spaces)		; small optimization
				(=f lost-spaces 0))
			   line-length
			   (+f line-length
			       (if (fixnump lost-spaces)
				   lost-spaces
				   (text-line-length lost-spaces)))))
	with i fixnum = (or start? 0)
	with text-x-a fixnum = 0	; arbitrary initializations
	with text-x-b fixnum = 0
	with character
	initially
	  (set-text-x text-x-a text-x-b 0)
	while (<f i end)
	do (setq character
		 (read-unicode-character-from-wide-string-with-lost-spaces
		   text-line i line-length lost-spaces))
	   (cond
	     ((char=w character #.%tab)
	      (let* ((a text-x-a)
		     (b text-x-b)
		     (position
		       (text-x-to-text-width a b))
		     (tab-width		       
		       (or tab-width?
			   (word-spacing-based-tab-width
			     word-spacing)))
		     (next-tab-position
		       (+f (-f position (modf position tab-width)) tab-width)))
		;; Word-spacing should be default-word-spacing!  This works
		;; only as long as we don't have justified text or other fancy
		;; formatting! (MHD)
		(set-text-x-from-text-width
		  text-x-a text-x-b next-tab-position)))
	     (t
	      (incf-text-x
		text-x-a text-x-b
		(if (char=w character #.%space) ; wrong for Unicode if NSM follows!
		    word-spacing		 
		    (get-unicode-set-width-as-text-width character ab-font)))))
	finally
	  (return
	    (if return-text-width?
		(text-x-to-text-width text-x-a text-x-b)
		(text-x-to-x text-x-a text-x-b)))))

;; Consider renaming this "compute-width-of-string".





;;; `Adjust-to-previous-base-character' tries to find the line index for the
;;; previous base character (for purposes of determining the left edge of a
;;; composed character) of a run of characters that may include non-spacing
;;; marks (e.g., accents) up to the character just before starting-line-index.
;;; This may not always get the index of a true base character.  This just
;;; returns the first character that is not classified as non-spacing-mark,
;;; which may be (and usually is) the character at just before
;;; starting-line-index.

(defun adjust-to-previous-base-character (text-line starting-line-index)
  (loop for i fixnum from (1-f starting-line-index) downto 0
	as character = (charw text-line i)
	while (non-spacing-mark-p-macro character)
	finally (return i)))

;; Note: ideally, it would be good to not have to go back at least one
;; character.  This is done in case we're adding a character that's a
;; non-spacing mark that's not yet in text-line, but that will come after a
;; possible run of characters in text-line.  The downside is just that we might
;; not find the smallest area to erase, i.e., we erase one character further
;; back than necessary. But that's generally a minute amount of extra drawing,
;; and almost never noticeable.  (MHD 6/16/04)



;;; `Compute-minimum-left-edge-of-character-in-line-of-text' returns no greater
;;; than the left-most pixel on which the character at start-character-index
;;; begins.
;;;
;;; This works by computing the gross width of text-line from the first to last
;;; character before the starting character, and then adding the font-wide
;;; bounding box X offset (probably always negative) to leave enough room for a
;;; character like the lowercase "j", which juts out to the left.
;;;
;;; With italics, jutting out is likely to become much more prevalent among many
;;; other characters.
;;;
;;; For now this appears to work for the minimum text cases, most Roman text and
;;; j's in the three basic sizes.  We still worry about (a) whether Gensym has
;;; these accurate in its fonts (experimentation seems to indicate it does); (b)
;;; whether they cover outline fonts (no evidence to the contrary with the "j"
;;; at several scales); (c) whether they cover the corresponding fonts
;;; adequately in practice (i.e., Japanese, Korean, Cyrillic).

(defun compute-minimum-left-edge-of-character-in-line-of-text
    (text-line starting-line-index font-map word-spacing)
  (let ((starting-line-index-adjusted-to-base-character
	  (adjust-to-previous-base-character text-line starting-line-index)))
    (+w (compute-width-of-text-line
	  text-line 0
	  starting-line-index-adjusted-to-base-character
	  font-map word-spacing)
	(or (ab-font-x-offset (ab-font (first font-map)))
	    0))))			; shouldn't be necessary, but some
					;   fonts are missing this info!

;; Consider (for the next rev.) iterating over all the fonts in font-map, and
;; then over all of their corresponding fonts (Cyrillic, Kanji, etc.),
;; determining the most negative X offset.





;;;; Making Ab Fonts



;;; Def-ab-font ... is to be used only below and in ab font modules generated by
;;; save-ab-font.

(defvar current-ab-font? nil)			; used by add-character-description

(defmacro def-ab-font
	  (font-name font-type
	   font-size font-baseline font-maximum-width font-maximum-height

	   ;; new args: (MHD 5/26/93)
	   &optional
	   point-size x-resolution y-resolution
	   width-in-x width-in-y x-offset y-offset)
  `(define-ab-font
     ',font-name ',font-type
     ,font-size ,font-baseline
     ,font-maximum-width ,font-maximum-height

     nil nil  ; fixed width/fixed bounding box (support here?)
     nil  ; get existing if available? (no; feature used by Kanji font files)
     ,point-size ,x-resolution ,y-resolution
     ,width-in-x ,width-in-y ,x-offset ,y-offset))


;;; Define-ab-font is a functional variation of def-ab-font.  It evaluates all of
;;; its arguments.

(defun define-ab-font
       (font-name font-type
	font-size font-baseline font-maximum-width font-maximum-height
	&optional fixed-width-of-font? fixed-bounding-box-of-font?
	          get-existing-font-if-available?

		  ;; new args: (MHD 5/26/93) 
		  point-size x-resolution y-resolution
		  width-in-x width-in-y x-offset y-offset)
  (setq current-ab-font?
	(or (if get-existing-font-if-available?
		(ab-font font-name))
	    (setf (ab-font font-name)
		  (new-make-ab-font
		    font-name font-type
		    font-size font-baseline
		    font-maximum-width font-maximum-height
		    fixed-width-of-font? fixed-bounding-box-of-font?

		    point-size x-resolution y-resolution
		    width-in-x width-in-y x-offset y-offset)))))

;; Consider adding what's necessary to allow "meta-." to work on the font name.  Consider
;; defining the font-name to be the font, using defvar.




;;; Add-character-description ... is to be used only below and in ab font modules generated
;;; by save-ab-font.

(defmacro add-character-description
    (character-code character-set-width?
		    bounding-box-x-offset? bounding-box-y-offset?
		    bounding-box-width? bounding-box-height?
		    character-rectangle-array-or-bitmap
		    &optional scaleable-text-width?
		              combining-class?)
  `(add-character-description-1
     ,character-code ,character-set-width?
     ,bounding-box-x-offset? ,bounding-box-y-offset?
     ,bounding-box-width? ,bounding-box-height?
     ,(if (constantp character-rectangle-array-or-bitmap)
	  `(optimize-constant ,character-rectangle-array-or-bitmap)
	  character-rectangle-array-or-bitmap)
     ,scaleable-text-width?
     ,combining-class?))




;;; Set-current-ab-font sets up any special variables needed for calling
;;; add-character-description as part of reading in a font from disk.

(defun set-current-ab-font (font-or-font-name)
  (setq current-ab-font?
	(if (symbolp font-or-font-name)
	    (ab-font font-or-font-name)
	    font-or-font-name)))

;; Added today.  Used now by read-ab-font-file.  (MHD 11/10/92)


;;; Make-ab-font creates a font and fills in its missing-character information.

(defun make-ab-font
       (ab-font-name ab-font-type ab-font-size ab-font-baseline
	ab-font-maximum-width ab-font-maximum-height
	&optional fixed-width-of-font? fixed-bounding-box-of-font?)
  (case ab-font-type				; FIXUP! changes args
    (kanji
     (cond
       ((=f ab-font-baseline 16)
	(incff ab-font-size (*f 2 (kanji-character-margin 'kanji16)))
	(incff ab-font-baseline (kanji-character-depression 'kanji16)))
       ((=f ab-font-baseline 24)
	(incff ab-font-size (*f 2 (kanji-character-margin 'kanji24)))
	(incff ab-font-baseline (kanji-character-depression 'kanji24))))))
  (let ((current-ab-font?
	  (make-ab-font-structure
	    ab-font-name ab-font-type ab-font-size ab-font-baseline
	    ab-font-maximum-width ab-font-maximum-height))
	(missing-character-set-width
	  (or fixed-width-of-font?
	      (case ab-font-type
		(kanji ab-font-size)	        ; heuristic, the font size
		(t ab-font-baseline)))))	; heuristic, the baseline offset from the top
    (setf (missing-character-set-width current-ab-font?) missing-character-set-width)

    ;; This no longer has special logic below to figure out a special
    ;; size for the Kanji font.  I took that out, since Kanji fonts
    ;; are fixed-width/fixed-bounding-box now.  Note also that
    ;; the size changed for 3.1, so the old information would cause
    ;; a wrong-sized bitmap to go in, which caused bombouts showing
    ;; kanji blobs for a while in 3.1 inhouse.  (MHD 7/15/93)
    (cond
      ((and fixed-width-of-font? fixed-bounding-box-of-font?)
       (add-character-description
	0 nil nil nil nil nil
	(let ((character-bitmap
	       (allocate-character-bitmap
		(third fixed-bounding-box-of-font?)
		(fourth fixed-bounding-box-of-font?))))	; fixed-width/fixed-bbox
	  (fill-rectangle-in-character-bitmap
	   character-bitmap 1 0 0
	   (third fixed-bounding-box-of-font?)
	   (fourth fixed-bounding-box-of-font?))
	  character-bitmap)))
      (t
       (let* ((blob-margin 1)		; solid square "blob" for a missing character
	      (blob-depression 0)
	      (blob-size
	       (-f missing-character-set-width (*f 2 blob-margin))))
	 (add-character-description
	  0
	  missing-character-set-width
	  blob-margin
	  (-f blob-depression)
	  blob-size
	  blob-size
	  (make-array
	   1 :initial-element (make-character-rectangle 0 0 blob-size blob-size))))))
    (setf (fixed-width-of-font? current-ab-font?)
	  fixed-width-of-font?)
    (if fixed-width-of-font?
	(setf (fixed-text-width-of-font? current-ab-font?)
	      (convert-to-text-width fixed-width-of-font?)))
    (setf (fixed-bounding-box-of-font? current-ab-font?)
	  fixed-bounding-box-of-font?)
    current-ab-font?))


(defun new-make-ab-font
       (ab-font-name ab-font-type 

	;; soon to be obsoleted by args below:
	ab-font-size ab-font-baseline
	ab-font-maximum-width ab-font-maximum-height

	&optional

	;; ok args:
	fixed-width-of-font? fixed-bounding-box-of-font?

	;; soon to be required, and replace obsolete args above:
	point-size x-resolution y-resolution
	width-in-x width-in-y x-offset y-offset)
  (let ((ab-font
	 (make-ab-font
	  ab-font-name ab-font-type 
	  ab-font-size ab-font-baseline
	  ab-font-maximum-width ab-font-maximum-height
	  fixed-width-of-font? fixed-bounding-box-of-font?)))
    (setf (ab-font-point-size ab-font) point-size)
    (setf (ab-font-x-resolution ab-font) x-resolution)
    (setf (ab-font-y-resolution ab-font) y-resolution)
    (setf (ab-font-width-in-x ab-font) width-in-x)
    (setf (ab-font-width-in-y ab-font) width-in-y)
    (setf (ab-font-x-offset ab-font) x-offset)	
    (setf (ab-font-y-offset ab-font) y-offset)
    ;; add in/rethink arglist of the constructor! (MHD 5/25/93)
    ab-font))

;; Consider trying to reclaim the conses generated herein.




(defun add-character-description-1
      (character-code character-set-width?
		      bounding-box-x-offset? bounding-box-y-offset?
		      bounding-box-width? bounding-box-height?
		      character-rectangle-array-or-bitmap?
		      scaleable-text-width?
		      &optional combining-class?) ; new arg (MHD 8/2/98)
    (when (and combining-class?
	       (not (member combining-class? supported-combining-classes)))
      (warn "~A is not a supported combining class (on of ~A).  It will be ignored."
	    combining-class? supported-combining-classes)
      (setq combining-class? nil))
    (let* ((ab-font-character-description-table
	     (ab-font-character-description-table current-ab-font?))
	   (character-description-or-rectangle-array-or-bitmap
	     (if (and (null character-set-width?)
		      (null bounding-box-x-offset?))
		 character-rectangle-array-or-bitmap?
		 (let ((character-description
			 (if (null character-rectangle-array-or-bitmap?)
			     (make-minimal-character-description character-set-width? nil)
			     (make-character-description
			       character-set-width?
			       character-rectangle-array-or-bitmap?
			       bounding-box-x-offset? bounding-box-y-offset?
			       bounding-box-width? bounding-box-height?))))
		   (setf (character-scaleable-text-width? character-description)
			 scaleable-text-width?)  ;  make new arg! (MHD 5/25/93)
		   character-description))))
      (case (ab-font-type current-ab-font?)
	(kanji
	 (set-kanji-character-description
	   character-code
	   ab-font-character-description-table
	   character-description-or-rectangle-array-or-bitmap))
	(t (unless (or (svref ab-font-character-description-table character-code)
		       (=f character-code 0))
	     (incff (number-of-characters-in-ab-font current-ab-font?)))
	   (setf (svref ab-font-character-description-table character-code)
		 character-description-or-rectangle-array-or-bitmap)))))


;; Old code follows that used to be used to either enter a new character description
;; structure -- this was before we had "fixed width" fonts -- or modify an existing
;; one.  That situation is only encountered in development, and so should now be
;; ignored, since it was unnecessarily complex and would have complicated the
;; introduction of fixed width fonts.  Note, however, that the arglist had been
;; 
;;   (character-code character-set-width
;;	bounding-box-x-offset bounding-box-y-offset
;;	bounding-box-width bounding-box-height
;;	character-rectangle-array)
;;
;; (MHD 9/23/91)
;; 
;; ;;     (let ((existing-character-description?
;; ;;             (get-kanji-character-description-if-any
;; ;;               character-code ab-font-character-description-table)))
;; ;;       (cond
;; ;;         (existing-character-description?
;; ;;          (setf (character-set-width existing-character-description?)
;; ;;                character-set-width)
;; ;;          (setf (bounding-box-x-offset existing-character-description?)
;; ;;                bounding-box-x-offset)
;; ;;          (setf (bounding-box-y-offset existing-character-description?)
;; ;;                bounding-box-y-offset)
;; ;;          (setf (bounding-box-width existing-character-description?) bounding-box-width)
;; ;;          (setf (bounding-box-height existing-character-description?) bounding-box-height)
;; ;;          (setf (character-rectangle-array existing-character-description?)
;; ;;                character-rectangle-array)
;; ;;          existing-character-description?)
;; ;;         (t (let ((character-description-table
;; ;;                    (ab-font-character-description-table current-ab-font?))
;; ;;                  (bucket-index
;; ;;                    (modf character-code #.(kanji-font-cache-vector-length)))
;; ;;                  result)
;; ;;              (setf (svref character-description-table bucket-index)
;; ;;                    (gensym-cons
;; ;;                      character-code
;; ;;                      (gensym-cons
;; ;;                        (setq result
;; ;;                              (make-character-description
;; ;;                                character-set-width bounding-box-x-offset bounding-box-y-offset
;; ;;                                bounding-box-width bounding-box-height
;; ;;                                character-rectangle-array))
;; ;;                        (svref character-description-table bucket-index))))
;; ;;              (unless (=f character-code 0)
;; ;;                (incff (number-of-characters-in-ab-font current-ab-font?)))
;; ;;              result))))

;; Old code follows that used to be at the beginning of the above function to fix up
;; some version of the Lisp-format Kanji ab font file.  It has not been needed for
;; some time, since the file used for version 2.1 even already had incorporated
;; these magic fixups.  (MHD 9/23/91)
;; 
;; ;;   (case (ab-font-type current-ab-font?)         ; FIX UP!
;; ;;     (kanji
;; ;;      (cond
;; ;;        ((=f character-set-width 16)
;; ;;         (incff character-set-width (*f 2 (kanji-character-margin 'kanji16)))
;; ;;         (incff bounding-box-x-offset (kanji-character-margin 'kanji16))
;; ;;         (incff bounding-box-y-offset (-f (kanji-character-depression 'kanji16))))
;; ;;        ((=f character-set-width 24)
;; ;;         (incff character-set-width (*f 2 (kanji-character-margin 'kanji24)))
;; ;;         (incff bounding-box-x-offset (kanji-character-margin 'kanji24))
;; ;;         (incff bounding-box-y-offset (-f (kanji-character-depression 'kanji24)))))))


;; Consider optimizing this.

;; Consider reclaiming the image-description-rectangles conses.

;; Consider having this do some error checking, particularly of character-code being
;; in range.



;;; `Create-fixed14-font' ... is an 8-pixel-wide fixed-width roman pseudo-font used only
;;; by print-frame for printing tables.

(defun create-fixed14-font ()
  (let ((ab-font
	  (make-ab-font
	    'fixed14 'roman
	    (ab-font-size (ab-font 'hm14))
	    (ab-font-baseline (ab-font 'hm14))
	    (ab-font-maximum-width (ab-font 'hm14))
	    (ab-font-maximum-height (ab-font 'hm14)))))
    (loop with character-description-table
	    = (ab-font-character-description-table ab-font)
	  as i from 0 below (length character-description-table)
	  do (setf (svref character-description-table i)
		   (make-character-description	; use same one for all characters?
		     8 0 0 0 0 nil)))    
    (setf (ab-font 'fixed14) ab-font)))

;; This works only if all characters printed are simple.  Fix it to work in all cases!

;; FIX THIS TO FILL IN ONLY THOSE CHARACTERS THAT ARE IN HM14!




;;; `Create-blob18-font' ... is a 14-pixel-wide fixed-width roman pseudo-font used
;;; by the login facility for editing secret passwords.  All characters are missing
;;; and therefore will appear as "blobs" on the screen.

;;; The font `blob18' is a standard G2 font, as created by create-blob18-font. It
;;; is used only, at present, for online editing of secret passwords.  No software
;;; may arrange to have references to this font saved on KBs. This leaves open the
;;; option of removing it from Gensym software without the risk of having KB
;;; compatibility problems in the future.

(def-ab-font
  BLOB18; ab-font-name
  ROMAN	; ab-font-type
  18	; ab-font-size
  14	; ab-font-baseline; the 14 becomes the missing character set width
  24	; ab-font-maximum-width
  22	; ab-font-maximum-height

  ;; New, for 3.1 (4.0).  (MHD 5/26/93)
  18	; ab-font-point-size
  75	; ab-font-x-resolution
  75	; ab-font-y-resolution

  22	; ab-font-width-in-x
  18	; ab-font-width-in-y
  -2	; ab-font-x-offset
  -4	; ab-font-y-offset
  )

;; The magic numbers are derived from font HM18.

;; Note that Telewindows needs to have this font loaded so that it can manage a
;; window on which a secret password is being typed.  (MHD 3/20/90)

;; Note that this font takes up almost no space, since it has no character
;; information.






;;; Stubs for Kanji fonts


;;; Define-stubs-for-kanji-fonts must be called to ensure that stub version of
;;; all Kanji fonts (Kanji16 and Kanji24, at present) are predefined and available
;;; at load time.

;;; These call def-ab-font with the appropriate data -- the same it would be called
;;; with if the font were loaded from disk.  All that needs to be added then are
;;; the character descriptions.  [This was not strictly true before, but it mattered
;;; less; see below.]

;;; Since 3.0 Rev. 1, i.e., with the additional Korean option, Kanji fonts are
;;; not actually replaced at the time they are loaded in; instead, the character
;;; descriptions are merely filled in.  

;;; Also, since 3.0 Rev. 1, Korean character may now occupy part of the Kanji font.

(defun define-stubs-for-kanji-fonts ()		; A function because TI does
  (if (null (ab-font 'kanji16))			;   not do the macros correctly!
						;   (MHD 9/8/89)
						; -- now mute: calls define- function,
						; but leave as is for now. (MHD 11/9/92)
      ;; NEW:   (MHD 11/9/92)
      (define-ab-font 'kanji16 'kanji
	16  ; was 18 -- bogusly (MHD 6/5/93)
	18 16 16 18 '(1 -2 16 16))
      
      ;; OLD:  
      ;; (def-ab-font kanji16 kanji 16 16 16 16)
      )

      
  (if (null (ab-font 'kanji24))

      ;; NEW:
      (define-ab-font 'kanji24 'kanji
	24  ; was 28 -- bogusly (MHD 6/5/93)
	27 24 24 26 '(1 -4 24 24))

      ;; OLD:  
      ;; (def-ab-font kanji24 kanji 24 24 24 24)
      ))

(define-stubs-for-kanji-fonts)
















;;;; Determining If an Asian (Kanji) Font is Loaded




;;; An `asian font name' is a bit different from a font name; the name
;;; of the font is always KANJI<size>, e.g., KANJI16 or KANJI24.  But
;;; the asian font name gives the real function of the font.  It may be
;;; one of KANJI16, KANJI24, HANGUL16, or HANGUL24.


;;; Asian-font-read-in-already-p returns true iff all characters in the
;;; font corresponding to asian-font-name have been loaded.

(defun asian-font-read-in-already-p (asian-font-name)
  (progn asian-font-name nil)
  #+comment				; FIX THIS to WORK!!
  (let ((ab-font?
	  (case asian-font-name
	    ((kanji16 hangul16)
	     (ab-font 'kanji16))
	    ((kanji24 hangul24)
	     (ab-font 'kanji24)))))
    (if ab-font?
	(loop with hangul-case?
		= (case asian-font-name
		    ((kanji16 kanji24) nil)
		    ((hangul16 hangul24) t))
	      with character-description-table
		= (ab-font-character-description-table ab-font?)
	      as high-byte
	         from (if hangul-case? ksc-high-byte-min jis-high-byte-min)
		 to (if hangul-case? ksc-high-byte-max jis-high-byte-max)
	      do (loop for low-byte
		         from (if hangul-case? ksc-low-byte-min jis-low-byte-min)
		         to (if hangul-case? ksc-low-byte-min jis-low-byte-min)
		       as code = (+f (ashf high-byte -8) low-byte)
		       always
			(or (get-kanji-character-description-if-any
			      code character-description-table)
			    (and (null hangul-case?)	; Kanji case

				 ;; Some chars not in our fonts
				 (or
				   ;; New Kanji - not in KANJI16 or
				   ;;   KANJI24 (See CHARACTERS)
				   (<=f #x7421 code #x7426)

				   ;; New symbols - not in KANJI24
				   ;;   (See CHARACTERS)
				   (<=f #x223a code #x2241)
				   (<=f #x224a code #x2250)
				   (<=f #x225c code #x226a)
				   (<=f #x2272 code #x2279)
				   (=f code #x227e)

				   ;; New Line-drawing characters -
				   ;;   not in KANJI24
				   (<=f #x2821 code #x2840)))))))))





;;;; Resetting Asian Fonts



;;; `Reset-asian-fonts' is a development-only function that clears all Asian
;;; bitmaps as character descriptions.  It also resets asian-font-file-loaded-p
;;; for all asian font file names.  And it resets all bitmap-font-data-handle
;;; for all asian bitmap font file names.
;;;
;;; This is intended to allow the environment to reset the environment after a
;;; call to write-gensym-asian-bf-files, or after limited use of the bf files,
;;; in order to allow testing of the bf file-usage mechanisms.
;;;
;;; This makes plenty of garbage, which is OK to do for a function used only in
;;; development.  A GC should reclaim the wasted space.

#+development
(defun reset-asian-fonts ()
  (loop for (language size start end alphabet
		      subfont-name ab-font-name asian-font-name)
	    in asian-bitmap-subfont-data-info
	do (setf (asian-font-file-loaded-p asian-font-name) nil)
	   (setf (bitmap-font-data-handle subfont-name) nil)
	   #+obsolete
	   (loop with table = (ab-font-character-description-table
				(ab-font ab-font-name))
		 for contiguous-code from start below end
		 as kanji-code
		   = (case language
		       (japanese
			(contiguous-to-gensym-jis-code contiguous-code))
		       (korean
			(contiguous-to-gensym-ksc-code contiguous-code)))
		 do (set-kanji-character-description kanji-code table nil))
	   (setf (ab-font-cache-of-scaled-fonts (ab-font ab-font-name))
		 (gensym-list nil)))
  ;; Resets all "Asian" transient data directly, and
  ;; handles Chinese. (MHD 4/9/99)
  #-obsolete
  (loop for ab-font-name in '(kanji16 kanji24)
	as ab-font = (ab-font ab-font-name)
	do (setf (ab-font-character-description-table ab-font)
		 (make-kanji-font-cache-vector))
	   (setf (ab-font-cache-of-scaled-fonts ab-font)
		 (gensym-list nil))))





;;;; A Note About the Following Sections



;;; The following sections are just for development.  





;;;; Making Ab Font Modules



#+development
(progn

;;; Save-ab-font ...  If wide-string-with-characters-to-keep? is non-nil, only
;;; those characters included therein will be saved.

;;; Save-ab-font returns three values: a list of sequences of character codes, the
;;; total number of characters, and the total number of character rectangles in all
;;; of the character descriptions.

;;; Note: If the saved ab font is a new one for G2, remember to add it to the lists of
;;; modules in BOOTSTRAP.

;;; Special Behavior for Huge Fonts
;;;
;;; When a font is "huge", meaning that it contains more than maximum-number-of-
;;; characters-per-font-file characters, the resulting file is split up into two
;;; or more files containing no more than maximum-number-of-characters-per-font-
;;; file characters.  The first file has the normal file name, and the subsequent
;;; files have 2, 3, 4, and so on, appended to their names.  Similarly, the header
;;; (a comment) of each subsequent file appends 2, 3, 4, and so on, to the font
;;; name; e.g. ";;;; <font name>-2" appears as the header in the second file.
;;;
;;; Only the first file actually begins with a def-ab-font form.  Subsequent files
;;; just set the variable current-ab-font? to (ab-font <font name>).  
;;;
;;; In practice, this should only be used for large-character-set language fonts
;;; (i.e. Kanji).  The main reason for this feature is to keep file sizes down 
;;; to a "reasonable" size in order not to stress the limits of certain
;;; implementations of Common Lisp.

(defparameter maximum-number-of-characters-per-font-file 1000)

#+development
(defvar def-ab-font-format-string	; args: as shown in comments
  "~%(def-ab-font
  ~a	; ab-font-name
  ~a	; ab-font-type
  ~a	; ab-font-size
  ~a	; ab-font-baseline
  ~a	; ab-font-maximum-width
  ~a	; ab-font-maximum-height

  ;; New, for 3.1 (4.0).  (MHD 5/26/93)
  ~a	; ab-font-point-size
  ~a	; ab-font-x-resolution
  ~a	; ab-font-y-resolution

  ~a	; ab-font-width-in-x
  ~a	; ab-font-width-in-y
  ~a	; ab-font-x-offset
  ~a	; ab-font-y-offset
  )")

#+development
(defvar font-file-header-format-string	; args: module-name, year-for-copyright
  ";; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-~
    ~%(in-package \"AB\")~
    ~%~
    ~%;;;; Module ~a~
    ~%~
    ~%;;; Copyright (c) ~d Gensym Corporation.~
    ~%;;; All Rights Reserved.~3%")



;;; ... bitmap-conditionalization-feature?, if non-nil, should be a feature
;;; name.  It will conditionalize using NIL or using the real bitmap for each
;;; character description.  E.g., if it's SLAVIC-BITMAPS, then the line with the
;;; bitmap data will look something like this:
;;;
;;;   #-slavic-bitmaps nil #+slavic-bitmaps

#+development
(defun save-ab-font
       (ab-font-or-font-name
	&optional non-standard-pathname?
	          wide-string-with-characters-to-keep?
		  bitmap-conditionalization-feature?)
  (let* ((ab-font-name
	   (if (symbolp ab-font-or-font-name)
	       ab-font-or-font-name
	       (ab-font-name ab-font-or-font-name)))
	 (ab-font
	   (if (symbolp ab-font-or-font-name)
	       (ab-font ab-font-or-font-name)
	       ab-font-or-font-name))
	 (character-description-table
	   (ab-font-character-description-table ab-font))
	 (*print-base* 10.))			; unnecessary
    (loop with last-defined-character-index? = nil
	  with character-code-sequences = nil
	  with number-of-characters = 0
	  with total-number-of-character-rectangles = 0
	  with character-codes-and-descriptions
	    = (case (ab-font-type ab-font)
		(kanji
		 (sort
		   (loop for i from 0 below #.(kanji-font-cache-vector-length)
			 nconc (loop for l on (svref character-description-table i)
					   by 'cddr
				     as kanji-code = (car l)
				     unless (=f kanji-code 0)
				       collect (cons kanji-code (cadr l))))
		   #'(lambda (u v) (<f (car u) (car v)))))
		(t (loop for character-code
			     from 1 to #.(largest-non-kanji-font-character-code)
			 as character-description?
			    = (svref character-description-table character-code)
			 when character-description?
			   collect (cons character-code character-description?))))
	  with base-pathname
	    = (or non-standard-pathname?
		  (make-system-pathname 'ab ab-font-name "LISP" :newest))
	  for file-number from 1
	  as name = (if (eq (ab-font-type ab-font) 'kanji)
			(format nil "~a-~d" ab-font-name file-number)
			(format nil "~a" ab-font-name))
	  for pathname
	      = (make-pathname :defaults base-pathname :name (string-downcase name))
	  as module-name = (intern name)
	  until
	    (with-open-file (*standard-output* pathname :direction :output)
	      (multiple-value-bind (seconds minutes hours day month year dotw dsp)
                  (get-decoded-time)
		(format t font-file-header-format-string module-name year)
		(format t "~%;; ~d ~d ~d ~d ~d ~d ~d ~a ~
                                      ~%;; ~d/~d/~d~3%"
			seconds minutes hours day month year dotw dsp
			month day year))
	      (if last-defined-character-index?
		  (print
		    `(setq current-ab-font? (ab-font ,(ab-font-name ab-font))))
		  
		  (format t def-ab-font-format-string
			  (ab-font-name ab-font)
			  (ab-font-type ab-font)
			  (ab-font-size ab-font)
			  (ab-font-baseline ab-font)
			  (ab-font-maximum-width ab-font)
			  (ab-font-maximum-height ab-font)
			  
			  (ab-font-point-size ab-font)
			  (ab-font-x-resolution ab-font)
			  (ab-font-y-resolution ab-font)
			  
			  (ab-font-width-in-x ab-font)
			  (ab-font-width-in-y ab-font)
			  (ab-font-x-offset ab-font)
			  (ab-font-y-offset ab-font)))
	      (terpri)
	      (terpri)
	      (loop with number-of-characters-in-this-font-file = 0
		    as (character-code . character-description)
		       in character-codes-and-descriptions
		    as index from 1
		    when (and (or (null last-defined-character-index?)
				  (>f index last-defined-character-index?))
			      (or (null wide-string-with-characters-to-keep?)
		     (loop for i from 0
				 below
			   (length
			     wide-string-with-characters-to-keep?)
			   as font-code
			      = (map-unicode-to-ab-latin-font-code-or-zero
				  (wide-character-code
				    (charw wide-string-with-characters-to-keep? i)))
			   thereis (and (/=f font-code 32) ; just to exclude space (32)!
					(=f font-code character-code)))))
		      do (write-character-definition
			   character-code character-description
			   (cond
			     ((eq (ab-font-type ab-font) 'kanji)
			      (format nil "~X" character-code))
                             ((memq (ab-font-name ab-font) '(slavic14 slavic18 slavic24)) ; unkludge!
                              (map-unicode-index-to-cyrillic-name                                
                                (map-cyrillic-font-code-to-unicode-index character-code)))
                             ((memq (ab-font-name ab-font) '(hebrew14 hebrew18 hebrew24)) ; improve later!
                              (format nil "Hebrew Font Code 0x~x, Unicode 0x~x"
				      character-code
				      (map-hebrew-font-code-to-unicode character-code)))
                             ((memq (ab-font-name ab-font) '(thai14 thai18 thai24)) ; improve later!
                              (format nil "Thai Font Code 0x~x, Unicode 0x~x"
				      character-code
				      (map-thai-font-code-to-unicode character-code)))
			     ((<=f 32 character-code 126)
			      (format nil "~C" (code-char character-code)))
			     (t
			      (map-ab-latin-font-code-to-adobe-name character-code)
;OBS:			      
;			      (loop for (adobe-name . roman-font-special-character-code)
;					  in adobe-name-to-roman-font-special-character-code-alist
;				      when (=f roman-font-special-character-code
;					       character-code)
;					return adobe-name)
			      ))
			   bitmap-conditionalization-feature?)
			 (if (and character-code-sequences
				  (=f character-code
				      (+f (second (first character-code-sequences)) 1)))
			     (setf (second (first character-code-sequences))
				   character-code)
			     (push (list character-code character-code)
				   character-code-sequences))
			 (incff number-of-characters)
			 (incff total-number-of-character-rectangles
				(length (character-rectangle-array character-description)))
			 (incff number-of-characters-in-this-font-file)
			 (when (>f number-of-characters-in-this-font-file
				   maximum-number-of-characters-per-font-file)
			   (setq last-defined-character-index? number-of-characters)
			   (terpri)
			   (return nil))
		    finally
		      (return t)))		; signals exhaustion
	  finally
	    (terpri)
	    (return
	      (values
		(nreverse character-code-sequences)
		number-of-characters
		total-number-of-character-rectangles)))))

;; Improve the time stamp format!

;; Consider having this include an Adobe or Bitstream copyright where appropriate.

;; Consider reclaiming the conses and strings generated herein.



(defun write-character-definition
       (character-code character-description comment-string?
		       bitmap-conditionalization-feature?)
  (terpri)
  (if comment-string?
      (format t "~%;; ~A" comment-string?))	; put after add-character-description?
  (terpri)
  (format
    t
    "(add-character-description~%  ~D ~D ~D ~D ~D ~D~%  "	; include vector length?
    character-code
    (character-set-width character-description)
    (bounding-box-x-offset character-description)
    (bounding-box-y-offset character-description)
    (bounding-box-width character-description)
    (bounding-box-height character-description))
  (when bitmap-conditionalization-feature?
    (format t "~(#-~a nil #+~a ~)"
	    bitmap-conditionalization-feature?
	    bitmap-conditionalization-feature?))
  (format t "'#(")	  
  (loop with character-rectangle-array
	  = (character-rectangle-array character-description)
	as i from 0 below (length character-rectangle-array)
	as character-rectangle = (svref character-rectangle-array i)
	do (if (>f i 0)
	       (if (=f (modf i 8) 0)		; 6 or 7?
		   (format t "~%    ")
		   (princ " ")))
	   (if (consp character-rectangle)
	       (princ character-rectangle)
	       (format t "#o~O" character-rectangle)))
  (format t ")
  ~a)"
	  ;; new for 3.1 ("4.0"). (MHD 5/27/93)
	  (character-scaleable-text-width? character-description)
	  ))














;;;; Adobe Fonts



;;; The following describes the procedure used to convert fonts received
;;; from Adobe in the form of IBM PC diskettes in Interchange Format to Lisp
;;; files in AB font format.

;;; (1) There are two diskettes: one containing the files hm7, hm8, hm10,
;;; hm12, hm14, hm18, and hm24 and the other containing the file hb72.
;;; All files have extension "bit" -- e.g. "hm7.bit".

;;; (2) The disk is inserted onto BLM's PC, equipped with a hard disk,
;;; ethernet, and FTP.

;;; (3) A FONTS directory is created and changed to:
;;;
;;;        C:> mkdir c:\fonts
;;;        C:> cd c:\fonts

;;; (4) The files are copied from each floppy into the fonts directory:
;;;
;;;        C:> copy a:\*.*

;;; (5) The files are transfered, via FTP, to a directory on MA,
;;; "ma:>mhd>fonts>":
;;;
;;;        C:> ftp ma
;;;        PASSWORD:
;;;        FTP> cd >mhd>fonts>
;;;        FTP> mput *.*
;;;        SEND ALL (A)? [...]: A
;;;         [... five minutes ...]
;;;        FTP> quit

;;; (6) The font directory is deleted from the IBM PC disk:
;;;
;;;        C:> del *.*
;;;        C:> cd c:\
;;;        C:> rmdir fonts

;;; (6.5) At this point, I noticed a flaw in the files introduced somewhere
;;; in the process of file transferring.  Every new line was followed by
;;; a NUL character and an extra new line.  To remove this in a given file,
;;; read it into Zmacs on an Explorer, then type the following Zmacs command
;;; sequence to strip these things out.  The following is a series of seven
;;; single keystrokes.  It should be executed with the cursor at the very
;;; beginning of the file:
;;;
;;;    (1) Meta-% (2) Ctrl-Q (3) <return> (4) Symbol-Shift-'
;;;    (5) <return> (6) <return> (7) !
;;;
;;; After the last keystroke, the machine runs very hard for between 10
;;; seconds and a minute.  When it is done, the cursor jumps to the end of
;;; the file.  Now free of defects, the file should be saved. 

;;; (7) We now go to a development version of G2 running on a Lisp machine.
;;; Get into a Lisp read-eval-print loop inside of a G2 window by typing BREAK.
;;; The fonts hm14, hm18, hm24, and hb72 are then loaded into memory:
;;;
;;;     (make-ab-font-from-adobe-font-file "ma:>mhd>fonts>hm14.bit")
;;;     (make-ab-font-from-adobe-font-file "ma:>mhd>fonts>hm18.bit")
;;;     (make-ab-font-from-adobe-font-file "ma:>mhd>fonts>hm24.bit")
;;;     (make-ab-font-from-adobe-font-file "ma:>mhd>fonts>hb72.bit")
;;;
;;;     (make-ab-font-from-adobe-font-file "hi:/usr/kanji/kanji.g.16.adobe" 'kanji 'kanji16)
;;;     (make-ab-font-from-adobe-font-file "lr:/disc2/kanji.adb" 'kanji 'kanji24)
;;;
;;;     (make-ab-font-from-adobe-font-file   ; Experimental Hangul Fonts (MHD 6/22/92)
;;;        "isr:/usr/local/src/X/X11R5/DIST/mit/fonts/bdf/misc/hanglm16.bdf"
;;;        'kanji 'hangul16) 		     ; note that the font type is KANJI, even
;;;        				     ;   though the font is Korean.  This is
;;;        				     ;   an historical artifact. (MHD 10/19/92)
;;;        				     
;;;     (make-ab-font-from-adobe-font-file   ; Experimental Hangul Fonts (MHD 6/22/92)
;;;        "isr:/usr/local/src/X/X11R5/DIST/mit/fonts/bdf/misc/hanglm24.bdf"
;;;        'kanji 'hangul24)

;;; (8) The fonts in memory are saved out as G2 Lisp modules in Lisp format:
;;;
;;;     (save-ab-font 'hm14 "ma:>ab>hm14.lisp")
;;;     (save-ab-font 'hm18 "ma:>ab>hm18.lisp")
;;;     (save-ab-font 'hm24 "ma:>ab>hm24.lisp")
;;;     (save-ab-font 'hb72 "ma:>ab>hb72.lisp"
;;;         (tformat-text-string "Telewindows Gensym G2~c~c"
;;;            %trade-mark-sign %registered-sign))
;;;
;;;     (write-ab-font-file 'kanji16 "ma:>ab>kanji16.gf")
;;;     (write-ab-font-file 'kanji24 "ma:>ab>kanji24.gf")
;;;     (write-ab-font-file 'hangul16 "ma:>ab>hangul16.gf")
;;;     (write-ab-font-file 'hangul24 "ma:>ab>hangul24.gf")

;;; (9) If any of these fonts are new ones for G2, we add them to the lists of
;;; modules in BOOTSTRAP.

;;; Done. (MHD 5/3/89)



;;; Make-ab-font-from-adobe-font-file ...

(defvar largest-character-code-in-ab-font-from-adobe) ; used for statistics

(defun make-ab-font-from-adobe-font-file
       (adobe-font-file-pathname
	&optional (ab-font-type 'roman) (font-name? nil)
	(maximum-number-of-characters-to-read? nil) (verbose-p nil))
  (when verbose-p
    (format t "~3&Opening file ~a ... " adobe-font-file-pathname))
  (with-open-file (input-stream adobe-font-file-pathname)
    (when verbose-p
      (format t "~&Opened ~a~&" (truename input-stream)))
    (let (input-line version font-name
	  point-size x-resolution y-resolution
	  width-in-x width-in-y
	  x-offset y-offset
	  number-of-characters
	  (largest-character-code-in-ab-font-from-adobe 0))
      (setq input-line (read-line-from-adobe-font-file input-stream))
      (test-assertion (string-equal input-line "STARTFONT"
				    :end1 (min 9 (length input-line))))
      (setq version (read-from-string input-line nil nil :start 9))
      (when verbose-p
	(format t "~&~4%Adobe Character Bitmap Distribution Format ~a" version))
      (setq input-line (read-line-from-adobe-font-file input-stream))
      (test-assertion (string-equal input-line "FONT"
				    :end1 (min 4 (length input-line))))
      (setq font-name (read-from-string input-line nil nil :start 4))
      (when verbose-p
	(format t "~&Adobe Font: ~a" font-name))
      (setq input-line (read-line-from-adobe-font-file input-stream))
      (test-assertion (string-equal input-line "SIZE"
				    :end1 (min 4 (length input-line))))
      (let ((next-read-start 4))
	(multiple-value-setq (point-size next-read-start)
	  (read-from-string input-line nil nil :start next-read-start))
;	(setq font-name (intern (format nil "~a-~d" font-name point-size))) ; (one way to do it?)
	(setq font-name
	      (or font-name?
		  (intern (format nil "~a" (string-upcase (pathname-name adobe-font-file-pathname))))))
	(multiple-value-setq (x-resolution next-read-start)
	  (read-from-string input-line nil nil :start next-read-start))
	(multiple-value-setq (y-resolution)
	  (read-from-string input-line nil nil :start next-read-start))
	(when verbose-p
	  (format t "~2%Point-Size: ~d~%  X resolution: ~d~%  Y resolution: ~d"
		  point-size x-resolution y-resolution))
	(setq input-line (read-line-from-adobe-font-file input-stream))
	(test-assertion (string-equal input-line "FONTBOUNDINGBOX"
				      :end1 (min 15 (length input-line))))
	(setq next-read-start 15)
	(multiple-value-setq (width-in-x next-read-start)
	  (read-from-string input-line nil nil :start next-read-start))
	(multiple-value-setq (width-in-y next-read-start)
	  (read-from-string input-line nil nil :start next-read-start))
	(multiple-value-setq (x-offset next-read-start)
	  (read-from-string input-line nil nil :start next-read-start))
	(multiple-value-setq (y-offset)
	  (read-from-string input-line nil nil :start next-read-start))
	(when verbose-p
	  (format t "~2%Font Bounding Box:~%  width in x: ~d~%  width in y: ~d"
		  width-in-x width-in-y)
	  (format t "~%  x displacement: ~d~%  y displacement: ~d"
		  x-offset y-offset)))
      
      (setq input-line (read-line-from-adobe-font-file input-stream))
      
      ;; in Hanglm24.bdf (MHD 6/22/92) -- this is documented as new for BDF
      ;; version 2.1. (MHD 5/19/93)
      (if (string-equal input-line "STARTPROPERTIES"
			:end1 (min 15 (length input-line)))
	  (loop do (setq input-line (read-line-from-adobe-font-file input-stream))
		until (string-equal input-line "ENDPROPERTIES"
				    :end1 (min 13 (length input-line)))
		finally
		  (setq input-line (read-line-from-adobe-font-file input-stream))))
      (test-assertion (string-equal input-line "CHARS"
				    :end1 (min 5 (length input-line))))
      (setq number-of-characters 
	    (read-from-string input-line nil nil :start 5))
      (when verbose-p
	(format t "~3%A total of ~d different characters follow.~2%"
		number-of-characters))
      (let ((ab-font
	     ;; OLD -- OBSOLETE -- DUMB: [prior to 5/19/93]
	     ;;   (make-ab-font
	     ;;     font-name ab-font-type
	     ;;     width-in-y
	     ;;     (+ width-in-y y-offset)
	     ;;     (- width-in-x x-offset)
	     ;;     (- width-in-y y-offset))
	     ;; The above corresponded to the arglist:
	     ;;   ab-font-name ab-font-type ab-font-size ab-font-baseline
	     ;;   ab-font-maximum-width ab-font-maximum-height
	     (new-make-ab-font
	      font-name ab-font-type

	      ;; "obsolete" args:
	      width-in-y
	      (+ width-in-y y-offset)
	      (- width-in-x x-offset)
	      (- width-in-y y-offset)
	      
	      ;; Old args -- these are ok:
	      ;;   fixed-width-of-font? fixed-bounding-box-of-font?
	      nil nil  ; compute these? -- get from properties (now ignored)?


	      ;; new args:

	      ;; SIZE
	      point-size x-resolution y-resolution

	      ;; FONTBOUNDINGBOX
	      width-in-x width-in-y x-offset y-offset)))
	(loop as i from 0
	      while (string-equal
		      (setq input-line
			    (read-line-from-adobe-font-file input-stream))
		      "STARTCHAR"
		      :end1 (min 9 (length input-line)))
	      do (if (and maximum-number-of-characters-to-read?
			  (=f maximum-number-of-characters-to-read? i))
		     (return nil))
		 (get-adobe-character-from-stream
		   input-stream input-line ab-font
		   point-size x-resolution verbose-p)
	      finally
		(test-assertion (string-equal input-line "ENDFONT"
					      :end1 (min 7 (length input-line)))))
	(setf (ab-font font-name) ab-font)
	(format t "~%Largest character code in ~a: ~d"
		;; should base largest-non-kanji-font-character-code on this number!
		font-name
		largest-character-code-in-ab-font-from-adobe)
	ab-font))))



(defun read-line-from-adobe-font-file (stream)
  (loop for line? = (read-line stream nil nil)
	while line?
	thereis
	  (if (and (not (string= line? ""))
		   (not (string-equal
			  line? "COMMENT"
			  :end1 (min #.(length "COMMENT") (length line?)))))
	      line?)))





(defvar location-of-adobe-standard-encoding-map
  "/bt/mhd50/lisp/StandardEncoding.txt")

;; Source URL:
;;
;;    ftp://unicode.org/pub/MappingTables/VendorMaps/Adobe/StandardEncoding.txt
;;
;; where it's status is given as "unofficial" (?)....
;;
;; Note: we don't use StandardEncoding here because it encodes a smallish subset
;; of Latin 1 characters and the available Adobe Latin font characters. Instead,
;; we use PDFDocEncoding, which unfortunately was not found online, but only in
;; a book; see unicode-to-adobe-encoding-map.


;;; `AB-Latin-font-code-to-BCID-map', generated by this form, contains mappings
;;; from AB Latin font codes to Bitstream Character IDs (BCID's).  A mapping of
;;; 0 indicates an unknown/non-existant code.


(defvar bcid-adobe-map-pathname "/bt/mhd50/lisp/bcid-adobe-map.txt")

(defun generate-AB-Latin-font-code-to-BCID-map ()
  (with-open-file (stream bcid-adobe-map-pathname)
    (loop with contents = (make-list 256 :initial-element nil)
	  for line? = (read-line stream nil nil)
	  while line?
	  when (and (> (length line?) 0)
		    (not (char= (char line? 0) #\#)))
	  do (multiple-value-bind (bcid? index)
		 (parse-integer line? :junk-allowed t)
	       (when bcid?
		 (multiple-value-bind (adobe-name?)
		     (read-from-string line? nil nil :start index)
		   (let ((ab-latin-font-code?
			   (if (and bcid?
				    adobe-name?
				    (stringp adobe-name?)
				    (not (string= adobe-name? "")))
			       (map-adobe-name-to-ab-latin-font-code-if-any
				 adobe-name?))))
		     (when (and ab-latin-font-code?
				;; The following test ensures we get the first/earliest
				;; entry in the file.  This works out better, in particular,
				;; because there's a second entry for "mu" which turns out
				;; not to be available in the font:  (MHD 9/3/96)
				(null (nth ab-latin-font-code? contents)))
		       (setf (nth ab-latin-font-code? contents)
			     bcid?))))))
	  finally
	    ;; Hand edit: Adobe's name for the Latin 1 character with code 0xB7
	    ;; is "periodcentered".  However, the "periodcentered" character is
	    ;; not available in the Bitstream Swiss 721 SWA font we're using.
	    ;; Meanwhile, "middot", BCID 136, is available in the font.  So, we
	    ;; patch here so 0xB7 maps to "middot".  Not great.... (MHD 9/3/96)
	    (setf (nth #xB7 contents) 136)

	    (format t "~%(defparameter ab-latin-font-code-to-bcid-map~
		          ~%  (optimize-constant~
                                 ~%       '#.(make-array 256~
		          ~%          :element-type '(unsigned-byte 16)~
		          ~%          :initial-contents '(")
	    (loop for i from 0 below 256
		  when (= (mod i 16) 0)
		    do (format t "~%     ")
		  do (format t "#x~x " (or (nth i contents) 0)))
	    (format t "))))~%"))))




;; Note: this is only for development, and even then, only for the times we are regenerating
;; new fonts, which is very, very rare. (MHD 8/15/96)

(defun map-adobe-name-to-ab-latin-font-code-if-any (adobe-name)
  (second 
    (find adobe-name unicode-to-adobe-encoding-map
	  :key #'fourth :test #'string=)))


;; map-ab-latin-font-code-to-adobe-name moved out of
;; this development-only forma, and made a defun-for-macro, since it's
;; used now for building a table used for postscript printing. (MHD 9/11/96)


;; Test:

(unless (and (string=
	       "A"
	       (map-ab-latin-font-code-to-adobe-name
		 (map-adobe-name-to-ab-latin-font-code-if-any "A")))
	     (string=
	       "mu"
	       (map-ab-latin-font-code-to-adobe-name
		 (map-adobe-name-to-ab-latin-font-code-if-any "mu")))
	     (string=
	       "eth"
	       (map-ab-latin-font-code-to-adobe-name
		 (map-adobe-name-to-ab-latin-font-code-if-any "eth"))))
  (error "something's wrong with map-adobe-name-to-ab-latin-font-code-if-any or its inverse!"))


(defun get-adobe-character-from-stream
       (input-stream initial-input-line ab-font point-size x-resolution verbose-p)
  (declare (special system-window		; defvar in run
		    point-size x-resolution))		; for computing scaleable-text-width only
  (let (input-line character-name character-code? 
	scaleable-width         ; for computing scaleable-text-width only
	scaleable-text-width	;a device width represented as a "text width" (derived
				;  from the scalable-width & point-size below)
	device-width
	bounding-box-width bounding-box-height bounding-box-x-offset bounding-box-y-offset
	(character-raster-lines nil))
    (setq character-name
	  (string-trim '(#\space) (subseq initial-input-line 9)))
    (setq input-line (read-line-from-adobe-font-file input-stream))
    (test-assertion (string-equal input-line "ENCODING" :end1 8))
    (setq character-code? (read-from-string input-line nil nil :start 8))
    (cond
      ((eq (ab-font-type ab-font) 'roman)
       ;; The following is needed because we use our own encoding on the Adobe
       ;; fonts, a superset of their Standard Encoding and of Latin 1 (MHD
       ;; 8/15/96); note that with the BDF files that Adobe shipped us came with
       ;; bogus encodings, i.e. even the standard characters had -1 as their
       ;; encoding!!!! -mhd, 5/19/87
       (setq character-code?
	     (map-adobe-name-to-ab-latin-font-code-if-any character-name))
       (if (eql character-code? -1)
	   (setq character-code? nil)))
      ;; The following follows our own convention for naming Kanji
      ;; characters.  The format is
      ;;   k-0x<hex-JIS-code>
      ;; where <hex-jis-code> is the JIS code (in Hexadecimal) for the
      ;; character.
      ((and (eq (ab-font-type ab-font) 'kanji)
	    (or (null character-code?)
		(eql character-code? -1))
	    (string-equal character-name "k-0x" :end1 4))	; case-insensitive
       (setq character-code?
	     (parse-integer
	       character-name :start 4 :radix 16 :junk-allowed t))))
    (when character-code?
      (setq largest-character-code-in-ab-font-from-adobe
	    (max largest-character-code-in-ab-font-from-adobe
		 character-code?)))
    (setq input-line  (read-line-from-adobe-font-file input-stream))
    (test-assertion (string-equal input-line "SWIDTH" :end1 6))
    (setq scaleable-width (read-from-string input-line nil nil :start 6)) ; for computing scaleable-text-width only
    (setq scaleable-text-width  ; not really used -- doesn't work as well as device width
	  (convert-any-number-to-text-width-at-compile-time
	    (* scaleable-width (/ point-size 1000.0) (/ x-resolution 72.0))))
    (setq input-line  (read-line-from-adobe-font-file input-stream))
    (test-assertion (string-equal input-line "DWIDTH" :end1 6))
    (setq device-width (read-from-string input-line nil nil :start 6))
    (setq input-line  (read-line-from-adobe-font-file input-stream))
    (test-assertion (string-equal input-line "BBX" :end1 3))
    (let ((next-read-start 3))
      (multiple-value-setq (bounding-box-width next-read-start)
	(read-from-string input-line nil nil :start next-read-start))
      (multiple-value-setq (bounding-box-height next-read-start)
	(read-from-string input-line nil nil :start next-read-start))
      (multiple-value-setq (bounding-box-x-offset next-read-start)
	(read-from-string input-line nil nil :start next-read-start))
      (multiple-value-setq (bounding-box-y-offset next-read-start)
	(read-from-string input-line nil nil :start next-read-start)))
    (setq input-line (read-line-from-adobe-font-file input-stream))
    (test-assertion (string-equal input-line "BITMAP" :end1 6))
    (let ((character-bitmap
	   (allocate-character-bitmap bounding-box-width bounding-box-height)))
      (with-local-color
	(loop initially
		(when verbose-p
		  (if (null character-code?)
		      (format t "~&Non-standard character: ~a" character-name)
		      (format t "Standard character: ~a" character-name)))
	      as y from 0 below bounding-box-height
	      do (setq input-line (read-line-from-adobe-font-file input-stream))
		 (push (parse-integer input-line :radix 16) character-raster-lines)
		 (when verbose-p (fresh-line))
		 (loop for position from (- (logandc2 (+ bounding-box-width 7) 7) 1) downto 0
		       as x from 0 
		       when (logbitp position (car character-raster-lines))
			 do (setf (character-bitmap-value character-bitmap x y) 1)))
	(if character-code?
	    (multiple-value-bind (hand-edited-character-rectangles
				  bounding-box-width? bounding-box-height?
				  bounding-box-x-offset? bounding-box-y-offset?)
		(get-hand-edits-for-character-if-appropriate
		  (ab-font-name ab-font) character-code?)
	      (when verbose-p
		(format t "~&Entering character code ~d" character-code?)
		(print-character-bitmap
		 character-bitmap bounding-box-width bounding-box-height)
		(terpri))
	      (let ((character-rectangles-array
		     (or (if hand-edited-character-rectangles
			     (convert-list-to-simple-vector hand-edited-character-rectangles))
			 (convert-character-bitmap-to-rectangle-array
			  character-bitmap bounding-box-width bounding-box-height))))
		(unless
		  (or (case (ab-font-name ab-font)
			(kanji16		; exclude solid-color "characters"
			 (or (if (not (=f character-code? #x2121))
				 (zerop (length character-rectangles-array)))	; keeps space (#x2121)
			     (if (null hand-edited-character-rectangles)
				 (equalp character-rectangles-array '#(#o2020)))))
			(kanji24		; exclude empty "characters"
			 (if (not (=f character-code? #x2121))
			     (zerop (length character-rectangles-array)))))	; keeps space (#x2121)
;		      (<=f #x2121 character-code? #x2132)	; exclude special characters
;		      (<=f #x213b character-code? #x216d)
;		      (<=f #x2170 character-code? #x237f)
;		      (<=f #x2620 character-code? #x265f)	; exclude Greek
;		      (<=f #x2720 character-code? #x277f)	; exclude Cyrrilic (sp?)
		      )
		  (let ((current-ab-font? ab-font))
		    (add-character-description
		      character-code? (round device-width)
		      (or bounding-box-x-offset? bounding-box-x-offset)
		      (or bounding-box-y-offset? bounding-box-y-offset)
		      (or bounding-box-width? bounding-box-width)
		      (or bounding-box-height? bounding-box-height)
		      character-rectangles-array
		      scaleable-text-width))))))))
      (setq input-line (read-line-from-adobe-font-file input-stream))
      (test-assertion (string-equal input-line "ENDCHAR" :end1 7))
      character-code?))

;; The device width of the font actually works better than scaling the scaleable width
;; ourselves.  Perhaps this is how the fonts were designed to work.  We thought that
;; the extra fraction bits they give would improve the widths, but they seem, by my
;; rough visual inspection, to make them worse. Maybe ask someone at adobe about this.
;; (MHD 6/15/87)





;; Tools for Evaluating New Adobe Fonts:

;; Temporary: for Adobe font evaluation. (MHD 3/15/89)

;; This probably will not compile correctly without many of the modules that follow
;; FONTS in the loading sequence loaded; it is mainly intended for temporary use
;; in a development environment in which it can be evaluated in the buffer.
;; (MHD 3/16/90)

;#+development
;(progn

;(def-format-class (font-demo-18 text-cell-format)
;  (text-cell-lines-justified? nil)
;  (text-cell-left-margin 10)
;  (text-cell-top-margin 10)
;  (text-cell-right-margin 10)
;  (text-cell-bottom-margin 10)
;  (text-cell-paragraph-indentation 0)
;  (text-cell-turnover-line-indentation 20)
;  (text-cell-line-height 20)
;  (text-cell-baseline-position 16)
;  (text-cell-line-spacing 3)
;  (default-word-spacing #.(convert-to-text-width 6))
;  (minimum-format-width-for-text-cell 350))

;(def-format-class (font-demo-14 font-demo-18)
;  (text-cell-left-margin 8)
;  (text-cell-top-margin 4)
;  (text-cell-right-margin 8)
;  (text-cell-bottom-margin 4)
;  (text-cell-turnover-line-indentation 8)
;  (text-cell-line-height 18)
;  (text-cell-baseline-position 14)
;  (default-word-spacing #.(convert-to-text-width 4))
;  (minimum-format-width-for-text-cell 300))

;(def-format-class (font-kanji-24 text-cell-format)
;  (text-cell-lines-justified? nil)
;  (text-cell-left-margin 10)
;  (text-cell-top-margin 10)
;  (text-cell-right-margin 10)
;  (text-cell-bottom-margin 10)
;  (text-cell-paragraph-indentation 0)
;  (text-cell-turnover-line-indentation 20)
;  (text-cell-line-height 25)
;  (text-cell-baseline-position 24)
;  (text-cell-line-spacing 1)
;  (default-word-spacing #.(convert-to-text-width 6))
;  (minimum-format-width-for-text-cell 450))

;(def-font-demo-18 18.euros)
;(def-font-demo-18 18.glyph)
;(def-font-demo-18 18.helvebla)
;(def-font-demo-18 18.helvelig)
;(def-font-demo-18 18.machi)
;(def-font-demo-18 18.memphlig)
;(def-font-demo-14 18.palatrom)
;(def-font-demo-18 18.stonesan)


;(def-font-demo-14 14.euros)
;(def-font-demo-14 14.glyph)
;(def-font-demo-14 14.helvebla)
;(def-font-demo-14 14.helvelig)
;(def-font-demo-14 14.machi)
;(def-font-demo-14 14.memphlig)
;(def-font-demo-14 14.palatrom)
;(def-font-demo-14 14.stonesan)

;(def-font-kanji-24 kanji-plain)

;(defvar all-kanji-fonts '(kanji-plain))

;(defvar all-demo-fonts
;	'(18.euros 18.glyph
;		   18.helvebla
;		   18.helvelig
;		   18.machi
;		   18.memphlig
;		   18.palatrom
;		   18.stonesan
;		   14.euros
;		   14.glyph
;		   14.helvebla
;		   14.helvelig
;		   14.machi
;		   14.memphlig
;		   14.palatrom
;		   14.stonesan))

;(defun display-fonts (&optional kanji? verbose?)
;  (loop with pane = current-workstation-detail-pane
;	with workspace
;	for font-name in (if kanji? all-kanji-fonts all-demo-fonts)
;	when (null (ab-font font-name))
;	  do (notify-user
;	       "Reading Font ~a; please wait ... " font-name)
;	     (make-ab-font-from-adobe-font-file
;	       (if kanji?
;		   "ca:/usr/pecann/kanji/kanji.adobe"
;		   (format nil "tx:mhd.fonts;~a" font-name))
;	       verbose?)
;	     (if (null (ab-font font-name))
;		 (or 
;		   (if kanji?
;		       (setf (ab-font 'kanji-plain)
;			     (ab-font 'kanji))	        ; the name is the file name 
;		       (setf (ab-font font-name)	;   (before the dot)
;			     (if (string= font-name "14"
;                                         :end1 (min 2 (length font-name)))
;				 (ab-font '|14|)
;				 (ab-font '|18|))))
;		   (cerror """where's the font?!")))
;	     ;; fix up ITC MACHINE -- only caps avail.
;	     (if (memq font-name '(18.machi 14.machi))
;		 (loop for i from (char-code #\A) to (char-code #\Z)
;		       as j from (char-code #\a) to (char-code #\z)
;		       do (setf (svref (ab-font-character-description-table
;					 (ab-font font-name))
;				       j)
;				(svref (ab-font-character-description-table
;					 (ab-font font-name))
;				       i))))	
;	     (setf (text-cell-font-map (get-or-make-format-frame font-name))
;		   (slot-value-list font-name))
;	do (setq workspace
;		 (make-workspace
;		   nil font-name
;		   (make-or-reformat-table
;		     (slot-value-list
;		       (slot-value-list
;			 (make-text-cell
;			   (copy-for-slot-value
;			     '("abcdefghijklmnopqrstuvwxyz"
;			       "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
;			       "0123456789-=`~\,./'!@#$%^&"
;			       "*()_+{}[]|<>?"))
;			   font-name))
;		       (slot-value-list
;			 (make-text-cell
;			   (copy-for-slot-value
;			     '("For all page types, the point (0, 0) in default"
;			       "user coordinate space is the lower left corner of the"
;			       "entire page, not of the imageable region; that is, the"
;			       "origin lies some distance outside the lower left corner"
;			       "of the imagable region. The coordinate system is"
;			       "arranged this way so that switching page types"
;			       "does not affect the position of graphical objects on"
;			       "the paper but just changes the sizes of the margins."))
;			   font-name)))
;		     'default-table-format nil)))
;	   (put-workspace-on-pane workspace pane)))

;;(defun test-latest-gizmo ()
;;  (display-fonts t nil))

;)  ; end of #+development (progn ...)





;;;; Bitstream Fonts



;;; Make-ab-font-from-bitstream-font-file ...

(defvar bitstream-byte-stream)

(defvar bitstream-byte-count)

(defun read-bitstream-byte ()
  (incf bitstream-byte-count)
  (read-byte bitstream-byte-stream))
  
(defun read-bitstream-halfword ()
  (+ (read-bitstream-byte) (ash (read-bitstream-byte) 8)))

(defun read-bitstream-word ()
  (+ (read-bitstream-byte) (ash (read-bitstream-byte) 8)
     (ash (read-bitstream-byte) 16) (ash (read-bitstream-byte) 24)))


(defun ascii-character (ascii-character-code)
  (if (= ascii-character-code 13)		; Carriage Return
      #.char-return
      (if (= ascii-character-code 10)		; Linefeed
	  #.char-linefeed
	  (ascii-code-char ascii-character-code))))

;; Move this to module CHARACTERS (and maybe eliminate it in favor of other
;; abstractions)!


(defun read-bitstream-ascii-string (nbytes)
  (with-output-to-string (string-stream)
    (loop repeat nbytes
	  do (write-char
	       (ascii-character (read-bitstream-byte))
	       string-stream))))

(defvar character-directory-record-length-in-bytes)



(defun make-ab-font-from-bitstream-font-file
       (bitstream-font-file-pathname &optional (ab-font-type 'roman) (verbose-p nil))
  (when verbose-p
    (format t "~3&Opening file ~a ... " bitstream-font-file-pathname))
  (with-open-file (input-stream bitstream-font-file-pathname
				#-ti :element-type #-ti '(unsigned-byte 8))
    (when verbose-p
      (format t "~&Opened ~a~&" (truename input-stream)))
    (let* ((bitstream-byte-count 0)
	   (bitstream-byte-stream input-stream)
	   (version						; 4 ascii
	    (read-bitstream-ascii-string 4))
	   (outline-font-id					; 4 ascii
	    (read-bitstream-ascii-string 4))
	   (outline-font-name					; 70 ascii
	    (read-bitstream-ascii-string 70))
	   (date						; 10 ascii
	     (read-bitstream-ascii-string 10))
	   (bitmap-font-name					; 70 ascii
	    (read-bitstream-ascii-string 70))	     
	   (outline-font-revision-number				; 16 bit integer
	     (read-bitstream-halfword))
	   
	   (offset-in-file-to-font-information-section-in-bytes	; 32 bit integer
	     (read-bitstream-word))
	   
	   (size-of-font-information-section-in-bytes		; 16 bit integer
	     (read-bitstream-halfword))
	   
	   (offset-in-file-to-kerning-pairs-section-in-bytes	; 32 bit integer
	     (read-bitstream-word))
	   
	   (kerning-pair-record-length-in-bytes			; 16 bit integer
	     (read-bitstream-halfword))
	   (number-of-kerning-pair-records			; 16 bit integer
	     (read-bitstream-halfword))
	   
	   (offset-in-file-to-character-directory-section-in-bytes	; 32 bit integer
	     (read-bitstream-word))
	   
	   (character-directory-record-length-in-bytes		; 16 bit integer
	     (read-bitstream-halfword))
	   
	   (number-of-character-directory-records		; 16 bit integer    
	     (read-bitstream-halfword))
	   
	   (offset-in-file-to-bitmaps-section-in-bytes		; 32 bit integer
	     (read-bitstream-word))
	   
	   (size-of-bitmaps-section-in-bytes			; 32 bit integer
	     (read-bitstream-word))
	   
	   (unused						; skip bytes 191 to 222
	     (loop repeat (+ (- 222 191) 1)			;    (reserved for fut.)
		   do (read-bitstream-byte)))
	   
	   (bitstream-copyright-data				; 34 ascii
	     (read-bitstream-ascii-string 34)))
      unused
      (when verbose-p
	(format t "~2&~{~&~(~a~)~45T= ~a~}"
		(list
		  'version version
		  'outline-font-id outline-font-id
		  'outline-font-name outline-font-name
		  'date date
		  'bitmap-font-name bitmap-font-name
		  'outline-font-revision-number outline-font-revision-number
		  
		  'offset-in-file-to-font-information-section-in-bytes
		  offset-in-file-to-font-information-section-in-bytes
		  
		  'size-of-font-information-section-in-bytes
		  size-of-font-information-section-in-bytes
		  
		  'offset-in-file-to-kerning-pairs-section-in-bytes
		  offset-in-file-to-kerning-pairs-section-in-bytes
		  
		  'kerning-pair-record-length-in-bytes
		  kerning-pair-record-length-in-bytes
		  
		  'number-of-kerning-pair-records
		  number-of-kerning-pair-records
		  
		  'offset-in-file-to-character-directory-section-in-bytes
		  offset-in-file-to-character-directory-section-in-bytes
		  
		  'character-directory-record-length-in-bytes
		  character-directory-record-length-in-bytes
		  
		  'number-of-character-directory-records
		  number-of-character-directory-records
		  
		  'offset-in-file-to-bitmaps-section-in-bytes
		  offset-in-file-to-bitmaps-section-in-bytes
		  
		  'size-of-bitmaps-section-in-bytes
		  size-of-bitmaps-section-in-bytes
		  'bitstream-copyright-data bitstream-copyright-data))
	
	(format t "~2&Font Information: "))
      (loop until (= bitstream-byte-count
		     offset-in-file-to-font-information-section-in-bytes)
	    do (read-bitstream-byte))

      (let* ((number-of-lines-per-em-square			; 16 bit integer
	       (read-bitstream-halfword))
	     (number-of-lines-below-the-baseline-in-em-square	; 16 bit integer
	       (read-bitstream-halfword))
	     (width-of-screen-cursor-character-in-pixels	; 16 bit integer
	       (read-bitstream-halfword))
	     (height-of-screen-cursor-character-in-pixels	; 16 bit integer
	       (read-bitstream-halfword))
	     (kerning-value-for-kerning-track-1-in-pixels	; 16 bit integer
	       (read-bitstream-halfword))
	     (kerning-value-for-kerning-track-2-in-pixels	; 16 bit integer
	       (read-bitstream-halfword))
	     (kerning-value-for-kerning-track-3-in-pixels	; 16 bit integer
	       (read-bitstream-halfword))
	     (kerning-value-for-kerning-track-4-in-pixels	; 16 bit integer
	       (read-bitstream-halfword))
	     (point-size-in-tenths-of-points			; 16 bit integer
	       (read-bitstream-halfword))
	     (vertical-resolution-in-dots-per-inch		; 16 bit integer
	       (read-bitstream-halfword))
	     (horizontal-resolution-in-dots-per-inch		; 16 bit integer
	       (read-bitstream-halfword)))

	(when verbose-p
	  (format t "~2&~{~&~(~a~)~45T= ~a~}" 
		  (list
		    'number-of-lines-per-em-square
		       number-of-lines-per-em-square		; not used yet 
		    'number-of-lines-below-the-baseline-in-em-square
		       number-of-lines-below-the-baseline-in-em-square
		    'width-of-screen-cursor-character-in-pixels
		       width-of-screen-cursor-character-in-pixels
		    'height-of-screen-cursor-character-in-pixels
		       height-of-screen-cursor-character-in-pixels
		    'kerning-value-for-kerning-track-1-in-pixels
		       kerning-value-for-kerning-track-1-in-pixels
		    'kerning-value-for-kerning-track-2-in-pixels
		       kerning-value-for-kerning-track-2-in-pixels
		    'kerning-value-for-kerning-track-3-in-pixels
		       kerning-value-for-kerning-track-3-in-pixels
		    'kerning-value-for-kerning-track-4-in-pixels
		       kerning-value-for-kerning-track-4-in-pixels
		    'point-size-in-tenths-of-points
		       point-size-in-tenths-of-points
		    'vertical-resolution-in-dots-per-inch
		       vertical-resolution-in-dots-per-inch
		    'horizontal-resolution-in-dots-per-inch
		       horizontal-resolution-in-dots-per-inch)))

	(when verbose-p
	  (format t "~2&Kerning Information: (Skipped)~&"))
	(loop until (= bitstream-byte-count
		       offset-in-file-to-kerning-pairs-section-in-bytes)
	      do (read-bitstream-byte))
	(when verbose-p
	  (format t "~2&Character Information: "))


	(let* ((font-name
		 (intern
		   (format nil "~a~d"
			   (read-from-string outline-font-name)
			   horizontal-resolution-in-dots-per-inch)))
	       (ab-font
		 (make-ab-font
		   font-name ab-font-type
		   number-of-lines-per-em-square
		   (- number-of-lines-per-em-square
		      number-of-lines-below-the-baseline-in-em-square)
		   nil nil)))			; FIX!
	  (setf (ab-font font-name) ab-font)
	  (loop with bounding-box-x-offset
		with bounding-box-y-offset
		with bounding-box-width
		with bounding-box-height
		with set-width
		with character-code
		with bitmap-offset
		with bitmap-length
		with bitmap-is-run-length-encoded?
		with run-length-var-size
		repeat number-of-character-directory-records
		do (multiple-value-setq 
		     (character-code bounding-box-x-offset bounding-box-y-offset
		       bounding-box-width bounding-box-height
		       set-width bitmap-offset bitmap-length
		       bitmap-is-run-length-encoded? run-length-var-size)
		     (read-bitstream-character
		       number-of-lines-below-the-baseline-in-em-square
		       verbose-p))
		collect `(,character-code ,bounding-box-x-offset ,bounding-box-y-offset
			  ,bounding-box-width ,bounding-box-height
			  ,set-width ,bitmap-offset ,bitmap-length
			  ,bitmap-is-run-length-encoded? ,run-length-var-size)
		  into character-information
		finally
		  (loop until (= bitstream-byte-count
				 offset-in-file-to-bitmaps-section-in-bytes)
			do (read-bitstream-byte))
		  (when verbose-p
		    (format t " OK~&")
		    (format t "~&Now getting bitmaps ... "))
		  (read-bitstream-bitmaps
		    ab-font
		    character-information
		    offset-in-file-to-bitmaps-section-in-bytes
		    verbose-p))
	  ab-font)))))



(defun read-bitstream-bitmaps (ab-font character-information
			       offset-in-file-to-bitmaps-section-in-bytes verbose-p)
  (declare (special system-window))
  (loop for (character-code bounding-box-x-offset bounding-box-y-offset
	      bounding-box-width bounding-box-height
	      set-width bitmap-offset bitmap-byte-length
	      bitmap-is-run-length-encoded? 8-bit-integers-case?)
	    in character-information
	maximize bounding-box-width into maximum-width
	maximize bounding-box-height into maximum-height
	do
           (when verbose-p
	     (format t "~2%"))
	   (loop until (= bitstream-byte-count
			  (+ offset-in-file-to-bitmaps-section-in-bytes
			     bitmap-offset))
		 if (> bitstream-byte-count
		       (+ offset-in-file-to-bitmaps-section-in-bytes
			  bitmap-offset))
		   do (error "I'm Lost.")
		 do (read-bitstream-byte))
	   (let ((character-bitmap
		  (allocate-character-bitmap
		   (+ bounding-box-width 1)
		   (+ bounding-box-height 1))))
	     (cond
	       ((not bitmap-is-run-length-encoded?)
		;; it is bitmap encoded
		(loop with y = 0
		      with x = 0
		      repeat (progn
			       ;; (test-assertion
			       ;;    (= (floor	; total number of bytes
			       ;;         (+ (* bounding-box-width bounding-box-height) 7)
			       ;;         8)
			       ;;       bitmap-byte-length))
			       bitmap-byte-length)
		      as byte = (read-bitstream-byte)
		      do (loop for index from 7 downto 0
			       until (and (= y bounding-box-height)
					  (= x bounding-box-width))			       
			       do 
			       (setf (character-bitmap-value character-bitmap x y)
				     (if (logbitp index byte) 1 0))
			       (if (= (incf x) bounding-box-width)
				   (if (= (incf y) bounding-box-height)
				       (return nil)
				       (setq x 0))))))
	       (t
		;; it is run-length encoded
		(loop for y from 0 below bounding-box-height
		      as number-of-runs
		      = (if 8-bit-integers-case?
			    (read-bitstream-byte) ; "8 bit unsigned integers"
			    (read-bitstream-halfword)) ; "16 bit signed integers"
		      do
		      (loop repeat number-of-runs
			    as starting-x
			    = (if 8-bit-integers-case?
				  (read-bitstream-byte)
				  (read-bitstream-halfword))
			    as run-length
			    = (if 8-bit-integers-case?
				  (read-bitstream-byte)
				  (read-bitstream-halfword))
			    do (loop repeat run-length
				     for x from starting-x				 
				     do (setf (character-bitmap-value character-bitmap x y) 1))))))
	     (when verbose-p
	       (print-character-bitmap
		character-bitmap bounding-box-width bounding-box-height)
	       (print-bitstream-character
		 character-code
		 bitmap-is-run-length-encoded?
		 8-bit-integers-case?
		 bitmap-byte-length bounding-box-width bounding-box-height))
	     (when (<= 0 character-code #o177)	; FIX!
	       (let ((current-ab-font? ab-font))
		 (add-character-description
		   character-code (round set-width)
		   bounding-box-x-offset bounding-box-y-offset
		   bounding-box-width bounding-box-height
		   (convert-character-bitmap-to-rectangle-array
		    character-bitmap bounding-box-width bounding-box-height)))))
	   finally
	     (setf (ab-font-maximum-width ab-font) maximum-width)
	     (setf (ab-font-maximum-height ab-font) maximum-height)))



(defun print-bitstream-character
    (character-code
      bitmap-is-run-length-encoded?
      8-bit-integers-case?
      &optional bitmap-byte-length? bounding-box-width bounding-box-height)  
  (format t "~&Character \"~c\" (Code: ~d)"
	  (if (<= 32 character-code 127)
	      (ascii-character character-code) ; maybe not ascii
	      #\-)
	  character-code)
  (when bitmap-byte-length?
    (format t " (~a w/~d bytes) (~d x ~d)"
	  (if bitmap-is-run-length-encoded?
	      (if 8-bit-integers-case?
		  "8 bit run-length encoded"
		  "16 bit run-length encoded")
	      "bitmap encoded")
	    bitmap-byte-length?
	    bounding-box-width
	    bounding-box-height)))



(defun read-bitstream-character (vertical-offset-of-baseline-from-em-square-origin verbose-p)
  (let* ((beginning-byte-count bitstream-byte-count)
	 (character-code (read-bitstream-halfword))
	 (unused (read-bitstream-halfword))
	 (horizontal-offset-of-minimum-rectangle-from-em-square-origin
	   (read-bitstream-halfword))
	 (vertical-offset-of-minimum-rectangle-from-em-square-origin
	   (read-bitstream-halfword))
	 (minimum-rectangle-width
	   (read-bitstream-halfword))
	 (minimum-rectangle-height
	   (read-bitstream-halfword))
	 ;; now convert these into our postscript-like system
	 (bounding-box-width minimum-rectangle-width)
	 (bounding-box-height minimum-rectangle-height)
	 (bounding-box-x-offset
	   horizontal-offset-of-minimum-rectangle-from-em-square-origin)
	 (bounding-box-y-offset
	   (- vertical-offset-of-minimum-rectangle-from-em-square-origin
	      vertical-offset-of-baseline-from-em-square-origin))
	 (set-width (read-bitstream-halfword))
	 (offset-for-bitmap-from-beginning-of-bitmap-section-in-bytes
	   (read-bitstream-word))
	 (number-of-bytes-in-bitmap-minimum-rectangle-for-character
	   (read-bitstream-halfword))
	 (bitflags
	   (read-bitstream-halfword))
	 (bitmap-is-run-length-encoded?
	   (not (logbitp 0 bitflags)))
	 (run-length-var-size
	   (if (logbitp 1 bitflags)
	       '16-bit-signed-integers
	       '8-bit-unsigned-integers))
	 (8-bit-integers-case?
	   (case run-length-var-size
	     (8-bit-unsigned-integers t)
	     (t nil))))
    unused
    bitmap-is-run-length-encoded? run-length-var-size    
    (when verbose-p
      (print-bitstream-character
	character-code
	bitmap-is-run-length-encoded?
	8-bit-integers-case?))
    (loop until (= bitstream-byte-count		; necessary?
		   (+ beginning-byte-count
		      character-directory-record-length-in-bytes))
	  do (read-bitstream-byte))
    (values
      character-code
      bounding-box-x-offset bounding-box-y-offset bounding-box-width bounding-box-height
      set-width
      offset-for-bitmap-from-beginning-of-bitmap-section-in-bytes
      number-of-bytes-in-bitmap-minimum-rectangle-for-character
      bitmap-is-run-length-encoded?
      8-bit-integers-case?)))





;;;; Hand Edits to Licensed Fonts



;;; Get-hand-edits-for-character-if-appropriate ...

(defun get-hand-edits-for-character-if-appropriate (font-name character-code)

  (case font-name

    (hm14

     (case character-code

       ;; The following "3" has does not have the one by two unit horizontal bar one
       ;; unit down from the top left corner of the bounding box, but instead has a
       ;; single point at the top left corner.  It also has this done to the bottom
       ;; right corner.  The purpose of all this to keep 3's from looking like
       ;; 9's, e.g. when reduced in scale by about 20%. (MHD 9/14/88)
       (#.(convert-simple-character-to-ascii #\3)
	  '(#o110512 #o5050611 #o2040505 #o5010604 #o501))

       ;; This shaves off the curly hook coming down from the upper left corner of
       ;; the 6.
       (#.(convert-simple-character-to-ascii #\6)
	  '(#o1110512 #o5050611 #o1050206 #o2040505 #o10111 #o1000501))

       ;; This shaves off the curly hook coming up from the lower left corner of the 9.
       (#.(convert-simple-character-to-ascii #\9)
	  '(#o1110512 #o1050506 #o5010611 #o10105 #o1000501))))

    (hm18

     (case character-code

       ;; The following "-" has an one pixel extra thickness (on top) and has one pixel
       ;; longer (added to the right).  (MHD 10/21/87)
       (#.(convert-simple-character-to-ascii #\-)
	  (values '(#o602) 6 2))

       ;; The following "3" has been changed as follows: changed bottom bar, removed
       ;; bottom left upcurl, removed top left downcurl, removed middle of top left
       ;; downcurl, changed top bar.
       (#.(convert-simple-character-to-ascii #\3)
	  '(#o2140515 #o1130515 #o5120615 #o7071013 #o6060714 #o3050507 #o5040610 #o6020705
	    #o7011004 #o1000702))

       ;; The following "6" has been changed as follows: changed top right downcurl.
       (#.(convert-simple-character-to-ascii #\6)
	  '(#o3130615 #o2120315 #o7071013 #o6060714 #o2060307 #o3050607 #o30113 #o2020303
	    #o6000702 #o1010214 #o2000602))

       ;; The following "9" has been changed as follows: changed bottom bar, removed
       ;; bottom left upcurl.
       (#.(convert-simple-character-to-ascii #\9)
	  '(#o1140215 #o1130515 #o5120615 #o2070510 #o2060607 #o7021012 #o5020603 #o20106
	    #o6010714 #o1010207 #o2000602))

       ;; The following "r" has the single pixel connecting the two bars of the "r"
       ;; raised up by one pixel.  This makes it look less like it has a notch and helps
       ;; distinguish it from "m" and "n".  Note that shifting the "r" one to the left
       ;; has problems.  C.f. "tr", where the "t" and "r" touch.  Consider (only if a
       ;; completely new font is spun off from this one) extending the main horizontal
       ;; bar one longer to the right.  (MHD 10/21/87)
       (#.(convert-simple-character-to-ascii #\r)
	  (values '(#o2010302 #o3000502 #o212) 6 10))))

    (hm24)

    (hb72)))

;; Use map-to-roman-font-special-character-code-if-any herein as appropriate.






;;;; Determining Legal Kanji Codes



;;; Determine-legal-jis-code-ranges ...
;;;
;;;   ((overall-min . overall-max)
;;;    . { (min . max) } )
;;;
;;; This can be used to compute the value for legal-jis-code-ranges in
;;; a development environment in which the japanese font KANJI16 is loaded.

#+development
(defun determine-legal-jis-code-ranges ()
  (loop with result = nil
	with min? = nil
	with max = 0
	with this-min? = nil
	with this-max = nil
	for character-code
	    from 1				; 0 reserved for blob
	    below #.(ash 1 16)
	do (cond
	     ((get-kanji-character-description-if-any
		character-code
		(ab-font-character-description-table (ab-font 'kanji16)))
	      (if (null min?)
		  (setq min? character-code))
	      (if (null this-min?)
		  (setq this-min? character-code))
	      (setq max character-code)
	      (setq this-max character-code))
	     (t
	      (when this-min?
		(setq result
		      (cons (cons this-min? this-max) result)))
	      (setq this-min? nil)
	      (setq this-max nil)))
	finally
	  (return
	    (cons
	      (cons min? max)
	      (nreverse result)))))




;;; Determine-legal-hangul-code-ranges has been used in development to
;;; generate the legal hangul code ranges; this result becomes the value
;;; of legal-hangul-code-ranges, in CHARACTERS, q.v.

#+development
(defun determine-legal-hangul-code-ranges ()
  ;; Tested with "ma:>mhd>ab>hangul16.gf"  -- MHD, 10/10/92
  (with-open-file (input-stream "ma:>mhd>ab>hangul16.gf")
    (loop repeat 3 do (read-line input-stream))	; kludge to read past header
    (loop as line? = (read-line input-stream nil nil)
	  while line?
	  as 32r-string = (subseq line? 0 (position #\+ line?))
	  for character-code = (c32r 32r-string)
	  collect character-code into character-codes
	  finally
	    (setq character-codes (sort character-codes #'<))
	    (return
	      ;; code adapted from determine-legal-kanji-code-ranges
	      (loop with result = nil
		    with min? = nil
		    with max = 0
		    with this-min? = nil
		    with this-max = nil
		    for character-code
			from 1			; 0 reserved for blob
			below #.(ash 1 16)
		    do (cond
			 ((loop for code in character-codes	; member?
				until (> code character-code)
				when (= code character-code)
				  do (setq character-codes
					   (delq code character-codes 1))
				     (return t))
			  (if (null min?)
			      (setq min? character-code))
			  (if (null this-min?)
			      (setq this-min? character-code))
			  (setq max character-code)
			  (setq this-max character-code))
			 (t
			  (when this-min?
			    (setq result
				  (cons (cons this-min? this-max) result)))
			  (setq this-min? nil)
			  (setq this-max nil)))
		    finally
		      (return
			(cons
			  (cons min? max)
			  (nreverse result))))))))

;; Added. (MHD 10/10/92)

;; BUGS: (MHD 11/10/92)
;; 
;;  (1) The legal hangul code ranges was missing the one code 9300 for some
;; reason -- the range fell one short of it, at 9299.
;;  (2) The code #x223A (8762), which is 0226 in Kuten, is not in Kanji24, but it
;; is in Kanji16.  It's not in JIS according to our trusty old xeroxed Kanji Character
;; Code Table from Mr. Fukuoka of CTC (received 8/15/88).  But it is in JIS according
;; to Bitstream's catalog of Kanji -- there it shows up as a left pitchfork logical
;; symbol (curly E).  Since it is defined for Kanji16, it appears to be a legal
;; character, and can actually be entered with backslash in the editor.  When displayed
;; with "large" or "small" font in G2, it shows up.  When displayed with "extra-large"
;; font, however, it appears blank -- not as a blob -- why is that?!  Now, another
;; problem is that the code ranges were generated from the Kanji16 font.  Is this
;; char part of JIS or not?  Is it part of the extensions to JIS made around '88?  Why
;; was it only extended in Kanji16 and not Kanji24?  We can't leave it in just half of
;; our fonts!
;;
;; There are a whole "row" of symbols in this area, in the Kuten range from 0226 to
;; 0289: logical notation symbols, some musical notation symbols (e.g., Kuten 0285,
;; #x2276, is a musical note), a paragraph symbol (Kuten 0289, #x2279), and various
;; other miscellaneous symbols.  See Bitstream's catalog, Ward 02, Page 1 of 1.  I
;; figure all the characters in this range are there, although I only tried the
;; example codes above.



;;; System-initialize-kanji-codes-on has been used in development to initialize
;;; an array so that it can be charted to show the ranges of on vs. off characters
;;; in the kanji character set.

#+obsolete
(defun system-initialize-kanji-codes-on (integer-array &optional count-8bit-codes-as-on?)
  (loop for i from 1 below 29566		; safe: punt on getting fencepost right
	do (mutate-g2-array-reclaiming-evaluation-values
	     integer-array
	     i
	     (if (or (legal-kanji-character-code-p i)
		     (and count-8bit-codes-as-on?
			  (or (logtest #2r0000000010000000 i)
			      (logtest #2r1000000000000000 i))))
		 1
		 0))))

;; Added. (MHD 10/10/92)  -- Obsoleted.  (MHD 2/26/97)




;;;; Font Test Functions


;; The following only works for Lisp machines, since the
;;   trick here is that lispm raster arrays have
;;   dimensions (y x) instead of the usual (x y).

#+development
(defun show-raster
       (raster &optional x-limit? y-limit?
	&key (on-character #\@) (off-character #\space)
	     (x-border-character #\-) (y-border-character #\|))
  (if (null x-limit?)
      (setq x-limit? (array-dimension raster 1)))
  (if (null y-limit?)
      (setq y-limit? (array-dimension raster 0)))
  (loop for y from 0 below y-limit?
	do
	   (fresh-line)
	   (loop for x from 0 below x-limit?
		 do (format t " ~c"
			    (if (zerop (aref raster y x))
				(or (if (or (= y 0) (= y (1- y-limit?)))
					x-border-character)
				    (if (or (= x 0) (= x (1- x-limit?)))
					y-border-character)
				    off-character)
				on-character)))))


;;; `Compare-font-wide-bounding-box-with-facts' ...

(defun compare-font-wide-bounding-box-with-facts (non-kanji-ab-font)
  (loop for i from 0 below (+ (largest-non-kanji-font-character-code) 1)
	as character-description?
	  = (svref (ab-font-character-description-table non-kanji-ab-font) i)
	when character-description?
	  minimize (bounding-box-x-offset character-description?) into bbox
	  and minimize (bounding-box-y-offset character-description?) into bboy
	  and maximize (bounding-box-width character-description?) into bbw
	  and maximize (bounding-box-height character-description?) into bbh
	finally
	  (return
	    (list
	      (list
		'fontwide
		(ab-font-x-offset non-kanji-ab-font)
		(ab-font-y-offset non-kanji-ab-font)
		(ab-font-width-in-x non-kanji-ab-font)
		(ab-font-width-in-y non-kanji-ab-font))
	      (list
		'facts
		bbox
		bboy
		bbw
		bbh)))))


;;; Test-hm-font-wide-bounding-boxes returns three values:
;;;
;;;    (1) Passable-p;
;;;    (2) Perfect-p; and
;;;    (3) a list of the form
;;;
;;;         ( { ( font-name issue? comparison) } )
;;;
;;;        where issue? is either NIL (meaning perfect), OK-IT-FITS-INSIDE, or
;;;        BAD-IT-DOES-NOT-FIT, and where comparison is the result of
;;;        calling compare-font-wide-bounding-box-with-facts on the font
;;;        named by font-name
;;;
;;; The first value says that the fonts are passable overall because all of
;;; them either have perfect-sized or oversized font-wide bounding boxes. The
;;; second value just says if they're all perfect-sized.

(defun test-hm-font-wide-bounding-boxes ()
  (loop for font-name in '(hm14 hm18 hm24)
	as ab-font = (ab-font font-name)
	as comparison = (compare-font-wide-bounding-box-with-facts ab-font)
	as ((nil fontwide-bbox fontwide-bboy fontwide-bbw fontwide-bbh)
	    (nil bbox bboy bbw bbh))
	   = comparison
	as issue? = (cond
		      ((and (= fontwide-bbox bbox)
			    (= fontwide-bboy bboy)
			    (= fontwide-bbw bbw)
			    (= fontwide-bbh bbh))
		       nil)
		      ((and (<= fontwide-bbox bbox)
			    (<= fontwide-bboy bboy)
			    (>= fontwide-bbw bbw)
			    (>= fontwide-bbh bbh))
		       'ok-it-fits-inside)
		      (t 'bad-it-does-not-fit))
	count (eq issue? 'bad-it-does-not-fit) into bad-count
	count (eq issue? 'ok-it-fits-inside) into ok-count
	collect (list font-name issue? comparison) into issues-and-comparisons
	finally
	  (let ((passable? (= bad-count 0))
		(perfect? (and (= bad-count 0) (= ok-count 0))))
	    (return
	      (values
		passable?
		perfect?
		issues-and-comparisons)))))

;;; At present (6/21/95), we're getting passable-p.  Here are the details:
;;;
;;; (test-hm-font-wide-bounding-boxes)
;;; => T
;;;    NIL
;;;    ((HM14 OK-IT-FITS-INSIDE ((FONTWIDE -1 -3 15 15) (FACTS -1 -3 13 14)))
;;;     (HM18 OK-IT-FITS-INSIDE ((FONTWIDE -2 -4 22 18) (FACTS -1 -4 17 18)))
;;;     (HM24 OK-IT-FITS-INSIDE ((FONTWIDE -3 -5 28 24) (FACTS -1 -5 22 24))))
;;;
;;; Presumably the fontwide bbox is less because its based on the original
;;; Adobe font, and that font presumably has characters we're not using that
;;; jut out more in various ways.
;;;
;;; (MHD 6/21/95)
  



) ; end of #+(and development)





;;; `Reclaim-cached-structures-for-window' reclaims all structures specific to the
;;; argument window that are cached in lru-queues.  The reclamation is done by
;;; looping through each element in such a queue and calling the decaching
;;; function for the structure if it is specific to the argument window.

;;; `Reclaim-cached-structures-for-window' exists here because it requires
;;; names-and-sizes-for-decacheable-structures to be complete, and the last
;;; define-decacheable-structure form is in fonts.  Consider moving this to
;;; windows1 and providing a facility similar to that in the frame system whereby
;;; reclaim-cached-structures-for-window is re-compiled each time
;;; define-decacheable-structure is evaluated.

(defmacro reclaim-cached-structures-for-window-macro (gensym-window)
  (unless names-and-sizes-for-decacheable-structures
    (warn "This can't be right! names-and-sizes-for-decacheable-structures~
           is NIL when expanding reclaim-cached-structures-for-window-macro.  Oh Andreas?"))
  `(progn
     ,@(loop for name-and-size-info
		 in names-and-sizes-for-decacheable-structures
	     as corresponding-window-slot-name? = (third name-and-size-info)
	     as lru-queue = (fourth name-and-size-info)
	     when corresponding-window-slot-name?
	       collect 
		 `(let ((least-recently-used-lru-element
			  (least-recently-used-lru-element ,lru-queue)))
		    (when least-recently-used-lru-element
		      (loop as lru-element 
			       = least-recently-used-lru-element
			       then next-lru-element
			    as next-lru-element
			       = (lru-element-next-element lru-element)
			    until (eq lru-element ,lru-queue)
			    when (eq ,gensym-window
				     (,corresponding-window-slot-name? 
				      lru-element))
			      do (,(fifth name-and-size-info) lru-element))))
	       ;; Consider abstracting this loop to a function.
	       ;; To do this, need to define accessor functions for
	       ;; corresponding-window-slot-name?
		 )))

(defun-simple reclaim-cached-structures-for-window (gensym-window)
  (let ((current-window gensym-window))
    (reclaim-cached-structures-for-window-macro gensym-window)))

;; Probably could be defun-void, haven't checked!

;; The decaching function calls the reclamation function for the structure 
;; which splices the structure out of the lru-queue (see remove-lru-element).
;; The pointer to next-lru-element is necessary to hang on to the next
;; element when the current one is reclaimed.

;; See also define-decacheable-structures.

;; This function should become suspendable eventually.  This will require that
;; reclaim-window-for-workstation become suspendable.  When this is done, it will
;; no longer be possible to call reclaim-window-for-workstation simply as a slot
;; reclaimer for window-for-workstation.  Rather, it will have to be scheduled as
;; a resumeable task.  One problem with doing this is that currently, the task
;; scheduler does not run when the system is not running.

;; Need to reclaim rasters in stored raster pools.  For platforms where the
;; operating system can reclaim rasters (X-windows for example), this should be
;; done.  On other platforms, the rasters should go to another window or be put in
;; some global pool.  If not, they become garbage when the window is deleted.
;; Talk to Peng.







;;; Run-some-informational-tests-for-mhd ...  A debugging function.
;;; Temporarily, this runs in the distribution version when you do the
;;; "highlight-invoked-rules" menu choice.  It should work and be unnoticable,
;;; unless something is wrong with the platform.  This is only to be run inside
;;; a G2 process.  This can create a bit of garbage.

(defvar defvar-for-informational-tests-for-mhd)

(defun run-some-informational-tests-for-mhd ()
  
;  ;; For testing whether MIN works if given mixed number types, i.e., a
;  ;; bignum and a fixnum.  [MHD & JRA concluded that it was faulty in
;  ;; Chestnut as of today.  Jim went off to work on a fix and/or contact
;  ;; Chestnut, Inc.]  (MHD 12/3/91)
;  (with-temporary-bignum-creation
;    (setq defvar-for-informational-tests-for-mhd
;	  (min
;	    (get-universal-time)		; assumed to always create a bignum
;	    most-positive-fixnum))
;    (if (> defvar-for-informational-tests-for-mhd 0)	; always true, outsmart constant-folding
;	(setq defvar-for-informational-tests-for-mhd nil)))	; don't point to temp. bignum

  ;; Found to work fine. -mhd, 12/3/91
;  ;; For testing whether "character byte-vector" and "character raster" data
;  ;; abstractions work in chestnut.  (MHD 11/7/91)
;  (loop with byte-vector = (allocate-character-byte-vector 100)
;	for i from 0 below (character-byte-vector-length byte-vector)
;	do (setf (character-byte-vector-ref byte-vector i) i)
;	unless (eql (character-byte-vector-ref byte-vector i) i)
;	  do (return-from
;	       run-some-informational-tests-for-mhd
;	       (notify-user
;		 "Bad result for (eql (character-byte-vector-ref byte-vector ~a) ~a)"
;		 i i)))
;  (loop with character-bitmap = (allocate-character-bitmap 100 100)
;	for x from 0 below (character-bitmap-width character-bitmap)
;	do (loop for y from 0 below (character-bitmap-height character-bitmap)
;		 do (setf (character-bitmap-value character-bitmap x y)
;			  (if (oddp x) 1 0)))
;	finally
;	  (loop for x from 0 below (character-bitmap-width character-bitmap)
;		do (loop for y from 0 below (character-bitmap-height character-bitmap)
;			 unless (=f (character-bitmap-value character-bitmap x y)			 
;				    (if (oddp x) 1 0))
;			   do (return-from
;				run-some-informational-tests-for-mhd
;				(notify-user
;				  "Bad result for (=f (character-bitmap-value ~
;                                   character-bitmap ~a ~a) ~
;			           (if (oddp ~a) 1 0))"
;				  x y x)))))
  )





;;;; Outline Font RIP (Font Raster Image Processor) Interface 


;;; Horizontal-lines-per-em-as-text-width, Vertical-lines-per-em-as-text-width ...
;;; may only be used at compile time.
 
;;; Lines-per-em = (point-size-x * x-resolution)/points-per-inch, where
;;; points-per-inch = 72 (per Adobe specs).  The idea is to convert all of this
;;; to text-width units (at compile time), then do all the arithmetic (scaling)
;;; with fixnums.  Text-widths are known about (and decoded into whole/fraction
;;; parts) down on the C receiving end, in fontrip.c.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun compute-lines-per-em-as-text-width (point-size resolution-in-dpi)
  (let ((points-per-inch 72))		; PostScript uses 72; HP PCL uses 72.307
    (round (* (convert-to-text-width point-size)
	      (convert-to-text-width resolution-in-dpi))
	   (convert-to-text-width points-per-inch))))
)








;;; Outline-font-info is a global symbol property on the name of an ab-font,
;;; which is a bitmap font.  Its fields are
;;; 
;;;   (1) Corresponding-outline-font
;;;   (2) file-name-of-corresponding-outline-font (string) or a function
;;;       to call to get it (symbol)
;;;   (3) Point-size-of-device-of-the-bitmap-font
;;;   (4) Original-bitmap-x-device-resolution
;;;   (5) Original-bitmap-y-device-resolution
;;;   (6) Horizontal-lines-per-em-as-text-width
;;;   (7) Vertical-lines-per-em-as-text-width
;;;   (8) Make-chars-using-imported-set-width?
;;;   (9) Built-in-Font-ID?
;;;        - a positive fixnum or NIL, corresponding to
;;;          a built-in Font ID, as defined in fontrip.c; when
;;;          non-nil, this must be defined as a built-in font
;;;          in fontrip, and then this will override file
;;;          in slot (2) above
;;;   (10) subfont-and-char-id-function? -- If non-nil, a
;;;       fonction that when given a Gensym character code,
;;;       returns the name of a subfont, and the (Bitstream)
;;;       char_id within the subfont.  (Convert-kanji-code-
;;;       to-font-file-name-and-index is now the only
;;;       example -- it's used for Kanji.)
;;;   (11) processor-type? -- nil or speedo (for upward compatibility),
;;;        truetype, or type1
;;;   (12) outline-font-file-indexing-method - used to be driven from
;;;       subfont-and-char-id-function?. Now allows specification of indexing method
;;;       for the input font.

;;; Outline-font-file-indexing-method should be one of the
;;; character-mapping-protocol values given by constants immediately below.

;; Note: previously: protoDirectIndex (0) and protoBCID (1) (MHD 6/18/97)

;; The following corresponds to the current enum statement in the Bitstream C
;; source file speedo.h, here reproduced for documentation purposes.  Note that
;; these must be kept in synch with the C sources, so if we take an update to
;; the speedo.h source file, this may need updating.  (MHD 10/1/96)
;;
;; /* 4-in-1 stuff: */
;; /* Font data protocols supported */
;; enum {
;; 	protoSymSet,
;; 	protoPSEncode,
;; 	protoBCID,
;; 	protoUnicode,
;; 	protoMSL,
;; 	protoUser,
;; 	protoPSName,
;; 	protoDirectIndex,
;; 	protoShiftJIS,
;; 	protoJIS,
;; 	protoExtUnix
;; };

(defconstant protoSymSet-character-mapping-protocol 0)
(defconstant protoPSEncode-character-mapping-protocol 1)
(defconstant protoBCID-character-mapping-protocol 2)
(defconstant protoUnicode-character-mapping-protocol 3)
(defconstant protoMSL-character-mapping-protocol 4)
(defconstant protoUser-character-mapping-protocol 5)
(defconstant protoPSName-character-mapping-protocol 6)
(defconstant protoDirectIndex-character-mapping-protocol 7)
(defconstant protoShiftJIS-character-mapping-protocol 8)
(defconstant protoJIS-character-mapping-protocol 9)
(defconstant protoExtUnix-character-mapping-protocol 10)


(def-list-structure (outline-font-info)
  (corresponding-outline-font
   file-name-of-corresponding-outline-font
   point-size-of-the-bitmap-font
   original-bitmap-x-device-resolution
   original-bitmap-y-device-resolution
   horizontal-lines-per-em-as-text-width
   vertical-lines-per-em-as-text-width
   make-chars-using-imported-set-width?
   built-in-outline-font-id?
   subfont-and-char-id-function?
   outline-font-processor-type?
   outline-font-file-indexing-method

   outline-font-restriction?
   outline-font-file-name?))

(def-global-property-name outline-font-info)
(def-global-property-name outline-font-handle)


(defmacro get-font-processor-enumerated-type (outline-font-info)
  `(case (outline-font-processor-type? ,outline-font-info)
     ((speedo nil) 3)
     (truetype 2)
     (type1 1)))

;; Refer to speedo.h for enumerated type definition.


;;; `Check-if-outline-font-restricted' returns true if the designated outline
;;; font is restricted from use.  Otherwise, it returns nil.

#+development
(defparameter enable-japanese-font-in-development-p nil)
#+development
(defparameter enable-korean-font-in-development-p nil)
#+development
(defparameter enable-chinese-font-in-development-p nil)

;; The default used to be as if these were true; now we prefer false to make
;; sure we can more easily test the authorization code properly in
;; development. Using an appropriate OK file is preferred to bypassing security,
;; even in development.  (MHD 4/7/98)



(defun-simple check-if-outline-font-restricted (outline-font-info)
  (and (outline-font-restriction? outline-font-info)
       (when (not (case (outline-font-restriction? outline-font-info)
		    (japanese
		     (or (japanese-authorized-p)
			 (if (eq current-system-name 'telewindows)
			     (telewindows-authorized-for-japanese-p system-window))
			 #+development
			 enable-japanese-font-in-development-p))
		    (korean
		     (or (korean-authorized-p)
			 (if (eq current-system-name 'telewindows)
			     (telewindows-authorized-for-korean-p system-window))
			 #+development
			 enable-korean-font-in-development-p))
		    (chinese
		     (or (chinese-authorized-p)
			 (if (eq current-system-name 'telewindows)
			     (telewindows-authorized-for-chinese-p system-window))
			 #+development
			 enable-chinese-font-in-development-p))
		    (t t)))
	 (warn-of-outline-font-failure-if-appropriate outline-font-info)
	t)))


;;; The global property `outline-font-failure-warning-sent?' is stored on the
;;; symbol that is the corresponding outline font of an outline-font-info
;;; structure (a list structure).  Its value is true of false; when false, a
;;; warning still needs to be sent to the user about a loading failure.  Used
;;; only in `warn-of-outline-font-failure-if-appropriate', below, which issues
;;; warnings of failures loading fonts.

(def-global-property-name outline-font-failure-warning-sent?)

;; Previously a "slot" on the outline-font-info list structure, but couldn't be
;; (validly) set, since those structures are typically constants, i.e., stored
;; in static (read-only) memory.  (MHD 3/18/98)


(defun warn-of-outline-font-failure-if-appropriate (outline-font-info)
  (unless (outline-font-failure-warning-sent?
	    (corresponding-outline-font outline-font-info))
    (setf (outline-font-failure-warning-sent?
	    (corresponding-outline-font outline-font-info))
	  t)
    (case (outline-font-restriction? outline-font-info)
      ((japanese korean)
       (notify-user-at-console
	 "Note: outline fonts for ~a cannot be used because~
               ~%this software has no ~a product authorization. A~
               ~%bitmap font will be substituted. You can obtain the~
               ~%~a authorization from Gensym Corporation."
	 (outline-font-restriction? outline-font-info)
	 (outline-font-restriction? outline-font-info)
	 (outline-font-restriction? outline-font-info)))
      ((chinese)
       (notify-user-at-console
	 "Note: no font is available for Chinese because this~
               ~%software has no Chinese product authorization. You can~
               ~%obtain the Chinese authorization from Gensym Corporation.")))))

;; HQ-2632368 - reformatted above messages due to addition of timestamps to notify messages -dkuznick, 9/12/01

;; To do: have a way to reconsider if the authorization comes through -- i.e.,
;; decache the ugly bitmaps, remove the outline-font-failure-warning-sent? flag,
;; and start anew!  Would be nice, but not absolutely necessary.
;;
;; Note that Chinese bitmap fonts do not exist! (MHD 4/9/99)



;;; `Def-corresponding-outline-font' creates an outline-font-info structure (a
;;; list structure) for some outline font of the specified
;;; name....
;;;
;;; A parameter whose name of the form <name>-<point-size> is defined and bound
;;; to the resulting info structure.  This can then be setf'ed as the
;;; ouline-font-info of a given ab-font name.
;;;
;;; Point-size-of-ab-font should correspond to the point size at the "standard
;;; resolution" (in dots per inch) that some AB font (i.e., a bitmap font) was
;;; designed for.  The resulting info structure can then be assigned as the
;;; outline-font-info global property of that AB font.
;;;
;;; The "standard resolution" is given by the constant
;;; standard-resolution-for-gensym-fonts-in-dpi. [Note that we've altered
;;; slightly from what it should be (i.e., 70 instead of 75) to find the right
;;; sized corresponding outline fonts we have.  In particular, formats defined
;;; for the built-in fonts no longer completely "fit" the scaled outline fonts
;;; when we tried using 75 for roman.  Note that Kanji uses 75.  This needs
;;; review.  It should also be a parameter; not all fonts are tuned for the same
;;; point size (75 dpi)!]

(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant standard-resolution-for-gensym-fonts-in-dpi 70)
)

(defmacro def-corresponding-outline-font
    (name point-size-of-ab-font
	  &optional built-in-id? processor-type? font-file-name?
	  (outline-font-file-indexing-method 1)
	  file-name-of-corresponding-font-or-function-to-get-file-name?
	  outline-font-restriction?)
  `(progn
     (defparameter ,(build-ab-symbol name point-size-of-ab-font)
       (list ',name			; corresponding-outline-font
	     ',(or file-name-of-corresponding-font-or-function-to-get-file-name?
		   'get-font-file-name)
	     ',point-size-of-ab-font	; point-size-of-the-bitmap-font
	     ',standard-resolution-for-gensym-fonts-in-dpi ; original-bitmap-x-device-resolution
	     ',standard-resolution-for-gensym-fonts-in-dpi ; original-bitmap-y-device-resolution
	     ',(compute-lines-per-em-as-text-width ; horizontal-lines-per-em-as-text-width
		 point-size-of-ab-font
		 standard-resolution-for-gensym-fonts-in-dpi)
	     ',(compute-lines-per-em-as-text-width ; vertical-lines-per-em-as-text-width
		 point-size-of-ab-font
		 standard-resolution-for-gensym-fonts-in-dpi)
	     'nil			; make-chars-using-imported-set-width?
	     ',built-in-id?		; ID if a built-in font
	     'nil			; subfont-and-char-id-function?
	     ',processor-type?		; outline-font-processor-type?
	     ',outline-font-file-indexing-method
	     ',outline-font-restriction?     ; currently, one of JAPANESE, 
	     ',font-file-name?))))	     ;   KOREAN, or CHINESE


(def-corresponding-outline-font swiss-721-swa 14 1 speedo font3004 2) ; see note: 2 = ...
(def-corresponding-outline-font swiss-721-swa 18 1 speedo font3004 2)
(def-corresponding-outline-font swiss-721-swa 24 1 speedo font3004 2)
;; note: 2 = protoBCID-character-mapping-protocol

(def-corresponding-outline-font arial 14 nil truetype)
(def-corresponding-outline-font arial 18 nil truetype)
(def-corresponding-outline-font arial 24 nil truetype)



;;;; Slavic Outline Font


;;; The slavic outline file is saved as a C program (a .h file), and
;;; included as the built-in outline font with ID = 3.  This has been
;;; accepted for use in G2 and Telewindows products as of version 4.0,
;;; Rev. 1.

(def-corresponding-outline-font slavic 14 3 truetype nil 7) ; direct indexed; see note: 7 = ...
(def-corresponding-outline-font slavic 18 3 truetype nil 7)
(def-corresponding-outline-font slavic 24 3 truetype nil 7)
(def-corresponding-outline-font slavic 72 3 truetype nil 7) ; not used

;; 7 = protoDirectIndex-character-mapping-protocol
(progn (setf (outline-font-info 'slavic14) slavic-14)
       (setf (outline-font-info 'slavic18) slavic-18)
       (setf (outline-font-info 'slavic24) slavic-24)
       (setf (outline-font-info 'slavic72) slavic-72)) ; should be Black weight!




;;;; Hebrew Outline Font


;;; The Hebrew outline file is saved as a C program (a .h file), and
;;; included as the built-in outline font with ID = 4.  This has been
;;; accepted for use in G2 and Telewindows products as of version 5.1,
;;; Rev. 4 and 6.0, in sources pending 10/13/99.

(def-corresponding-outline-font hebrew 14 4 truetype nil 3) ; Unicode indexing; see note: 3 = ...
(def-corresponding-outline-font hebrew 18 4 truetype nil 3)
(def-corresponding-outline-font hebrew 24 4 truetype nil 3)
(def-corresponding-outline-font hebrew 72 4 truetype nil 3) ; not used

;; 3 = protoUnicode-character-mapping-protocol
(progn (setf (outline-font-info 'hebrew14) hebrew-14)
       (setf (outline-font-info 'hebrew18) hebrew-18)
       (setf (outline-font-info 'hebrew24) hebrew-24)
       (setf (outline-font-info 'hebrew72) hebrew-72)) ; should be Black weight!





;;;; Thai Outline Font


;;; The Thai outline font file is expected to be found as the file named
;;; "thai.ttf" in the G2/TW fonts directory.
;;;
;;; Thai script support is being added for G2 8.0, the pending release. Thai
;;; fonts are indexed using Unicode indexing protocol (code 3).

(def-corresponding-outline-font thai 14 nil truetype nil 3)
(def-corresponding-outline-font thai 18 nil truetype nil 3)
(def-corresponding-outline-font thai 24 nil truetype nil 3)
(def-corresponding-outline-font thai 72 nil truetype nil 3) ; not used

(progn (setf (outline-font-info 'thai14) thai-14)
       (setf (outline-font-info 'thai18) thai-18)
       (setf (outline-font-info 'thai24) thai-24)
       (setf (outline-font-info 'thai72) thai-72)) ; should be Black weight!





;;;; ...

(progn
  (setf (outline-font-info 'hm14) swiss-721-swa-14)
  (setf (outline-font-info 'hm18) swiss-721-swa-18)
  (setf (outline-font-info 'hm24) swiss-721-swa-24))


;;;; ...

;(progn
;  (setf (outline-font-info 'hm14) arial-14)
;  (setf (outline-font-info 'hm18) arial-18)
;  (setf (outline-font-info 'hm24) arial-24)
;  (setf (outline-font-handle 'arial) nil)) ; to retry after any difficulty


;; It works to try out the truetype fonts, but they're not built in and there
;; are problems with mapping to certain characters, such as the ' as well as
;; most european and accented characters.  Still, the results are interesting.
;; To try it, have the truetype font be in G2 launch directory.  (Unfortunately,
;; at present, they are not looked for in the fonts subdirectory. (MHD 2/16/95)





;;;; Chinese Font


(def-concept chinesettf-14)		; for hm18/kanji16; def-concepts 
					;   to make it easier to find this spot
(def-corresponding-outline-font chinesettf 14 nil truetype nil 3
				get-asian-font-file-name chinese)

(def-concept chinesettf-18)
(def-corresponding-outline-font chinesettf 18 nil truetype nil 3
				get-asian-font-file-name chinese)

(def-concept chinesettf-24)			; for hm24/kanji24
(def-corresponding-outline-font chinesettf 24 nil truetype nil 3
				get-asian-font-file-name chinese)

;; Note: 3 = #.protoUnicode-character-mapping-protocol



;;; `Load-chinese-font' finds and reads font data for the Chinese TTF font.
;;; This is just an analog of load-hangul-font, q.v., but for Chinese.

(defun load-chinese-font ()
  (get-outline-handle-and-char-id chinesettf-14))


;;; `kanji-font-associated-chinese-outline-font-info' returns the outline font
;;; info structure associated with kanji-font for Chinese.  Kanji-font should be
;;; KANJI16 or KANJI24.

(defmacro kanji-font-associated-chinese-outline-font-info (kanji-font)
  `(case ,kanji-font
     (kanji16 chinesettf-18)
     (kanji24 chinesettf-24)))






;;;; Korean Hangul Font


(def-concept hangulttf-14)			; for hm18/kanji16; def-concepts 
					;   to make it easier to find this spot
(def-corresponding-outline-font hangulttf 14 nil truetype nil 3
				get-asian-font-file-name korean)

(def-concept hangulttf-18)
(def-corresponding-outline-font hangulttf 18 nil truetype nil 3
				get-asian-font-file-name korean)

(def-concept hangulttf-24)			; for hm24/kanji24
(def-corresponding-outline-font hangulttf 24 nil truetype nil 3
				get-asian-font-file-name korean)

;; Note: 3 = #.protoUnicode-character-mapping-protocol



;;; `Load-hangul-font' finds and reads font data for the Hangul TTF font.  This
;;; supports early "preloading" as an alternative to on-the-fly loading upon
;;; needing the first character.  The problem with doing it on-the-fly is that
;;; it takes an unreasonably long time, since there is just one, huge monolithic
;;; outline font for over 12,000 characters.
;;;
;;; Load-hangul-font keeps a memory of previous attempts, and does not try to
;;; load a font once it has had a failure (or if it's already been loaded).
;;; Thus, is may be called more than once from startup code.  Accordingly,
;;; Telewindows uses it every time it obtains checks license levels, and finds
;;; that Korean is authorized.

(defun load-hangul-font ()
  (get-outline-handle-and-char-id hangulttf-14))

;; the -14 just as well be -18 or -24


;;; `kanji-font-associated-korean-outline-font-info' returns the outline font
;;; info structure associated with kanji-font for Korean.  Kanji-font should be
;;; KANJI16 or KANJI24.

(defmacro kanji-font-associated-korean-outline-font-info (kanji-font)
  `(case ,kanji-font
     (kanji16 hangulttf-18)
     (kanji24 hangulttf-24)))





;;;; Japanese Kanji Font

(def-suite-for-loading-file-at-launch-time minm_* tw
  :base-name-of-file-to-load   "minm_00"
  :type-of-file-to-load        "spd"
  :command-line-keyword        "minm_fontfile"
  :environment-variable-name   "MINM_FONTFILE"
  :base-name-of-disabling-file "NOG2MINMFONTFILE"
  :type-of-disabling-file      "CMD"
  :module telestubs)


(def-suite-for-loading-file-at-launch-time minm_* g2
  :base-name-of-file-to-load   "minm_00"
  :type-of-file-to-load        "spd"
  :command-line-keyword        "minm_fontfile"
  :environment-variable-name   "MINM_FONTFILE"
  :base-name-of-disabling-file "NOG2MINMFONTFILE"
  :type-of-disabling-file      "CMD"
  :module telestubs)

;; To direct G2 to use this font from a particular directory, you need a command
;; line like this
;;
;;   g2 -minm_fontfile /gensym/ut/dev/g2-latest/fonts/minm_*.spd
;;
;; (for example, to use the outline fonts from the g2-latest directory).
;;
;; It should just need to have the -fonts command line option, but that isn't yet
;; working.  Fix for the release!! (MHD 6/13/94)





(setf (outline-font-info 'kanji16)
      `(minm
	 get-asian-font-file-name
	 16 75 75			; point size and lines-per-em = 16
	 ,(compute-lines-per-em-as-text-width 16 75)
	 ,(compute-lines-per-em-as-text-width 16 75)
	 nil				; impose imported set widths
	 nil				; no built-in font ID
					; subfont-and-char-id-function?
	 convert-kanji-code-to-font-file-name-and-index
	 nil				; outline-font-processor-type?
	 ,protoDirectIndex-character-mapping-protocol ; outline-font-file-indexing-method (direct indexing)
	 japanese			; outline-font-restriction?
	 ))


(setf (outline-font-info 'kanji24)
      `(minm
	 get-asian-font-file-name
	 24 75 75			; point size and lines-per-em = 24
	 ,(compute-lines-per-em-as-text-width 24 75)
	 ,(compute-lines-per-em-as-text-width 24 75)
	 nil				; impose imported set widths
	 nil				; no built-in font ID
					; subfont-and-char-id-function?
	 convert-kanji-code-to-font-file-name-and-index
	 nil				; outline-font-processor-type?
	 ,protoDirectIndex-character-mapping-protocol ; outline-font-file-indexing-method (direct indexing)
	 japanese			; outline-font-restriction?
	 ))

;; Consider having a G2_FONT "home directory" for G2 fonts?!


(defun-substitution-macro get-handle-for-outline-font-name-if-any
    (outline-font-info outline-font-name character-mapping-protocol?)
  (let ((handle? (outline-font-handle outline-font-name)))
    (cond
      ((and handle? (not (eq handle? ':loading-failed)))
       handle?)
      ((eq handle? ':loading-failed)
       nil)
      ((check-if-outline-font-restricted outline-font-info)
       nil)
      (t
       (let ((handle-and-success-if-non-negative?
	       (cond
		 ((built-in-outline-font-id? outline-font-info)
		  (c-load-built-in-outline-font
		    (built-in-outline-font-id? outline-font-info)))
		 (t
		  (load-outline-font-file
		    outline-font-name outline-font-info
		    character-mapping-protocol?)))))
	 (cond
	   ((or (null handle-and-success-if-non-negative?) ; not really possible
		(<f handle-and-success-if-non-negative? 0))
	    (setf (outline-font-handle outline-font-name) ':loading-failed)
	    nil)
	   (t
	    (setf (outline-font-handle outline-font-name)
		  handle-and-success-if-non-negative?)
	    handle-and-success-if-non-negative?)))))))

;;; `Get-or-make-corresponding-outline-font-handle' returns one or two values:
;;;
;;;    (1) nil or an index (a fixnum integer) corresponding to a font
;;;    (2) nil or the appropriate char-id
;;;
;;; Note: character-code? should normally be the specific character code that is
;;; being rendered so that this can find the appropriate subfont if this is a
;;; subfonted outline font.  But it may be nil or unspecified if the aim is just
;;; to load (especially to preload) an entire font.  However, the functionality
;;; of loading an entire font in this way currently only works for monolithic
;;; fonts (e.g., chinese.ttf, korean.ttf), and not for subfonted fonts (e.g.,
;;; minm).  At present there is no need for subfonted fonts to be preloaded,
;;; since they load swiftly on the fly, if there were, this could be fixed.

(defun get-outline-handle-and-char-id (outline-font-info &optional character-code?)
  (let* ((subfont-and-char-id-function?
	   (subfont-and-char-id-function? outline-font-info))
	 (char-id? nil)	   
	 (character-mapping-protocol?
	   (outline-font-file-indexing-method outline-font-info))
	 (corresponding-outline-font
	   (corresponding-outline-font outline-font-info))
	 (font-code?
	   (if character-code?
	       (case corresponding-outline-font
		 (minm			; Japanese
		  (map-unicode-to-gensym-jis-x-0208 character-code?))
		 (slavic		; assume "gensym cyrillic" code
		  (unless (=f character-code? 0)
		    (map-unicode-index-to-slavic-font-direct-index
		      (map-cyrillic-font-code-to-unicode-index character-code?))))
		 (hebrew		; use unicode mapping for this
		  (unless (=f character-code? 0)
		    (map-hebrew-font-code-to-unicode character-code?)))
		 (thai		; use unicode mapping for this
		  (unless (=f character-code? 0)
		    (map-thai-font-code-to-unicode character-code?)))
		 ((hangulttf chinesettf) ; expect Unicode mapping in this case
		  character-code?)
		 (t
		  (let ((c? (if (<f character-code? 256) ; range check; abstract!
				(map-ab-latin-font-code-to-bcid character-code?))))
		    (if (and c? (not (=f c? 0)))
			c?))))))
	 (outline-font-name?
	   (if (and subfont-and-char-id-function? character-code?)
	       (if font-code?		; make sure we could map
		   (multiple-value-setq-some
		       (nil char-id?)
		       (funcall subfont-and-char-id-function? font-code?)))
	       (if (or (null character-code?) ; make sure we could map
		       font-code?)
		   corresponding-outline-font)))
	 (handle?
	   (if outline-font-name?
	       (get-handle-for-outline-font-name-if-any
		 outline-font-info outline-font-name?
		 character-mapping-protocol?))))
    (when handle?
      (values
	handle?
	(or char-id? font-code?)))))

;; This has font-specific information.  With some effort it could be teased
;; out. (MHD 4/9/99)


(def-gensym-c-function c-load-outline-font
    (:fixnum-int			; returns index in font memory 
      "g2fnt_load_outline_font")		;  array; negative if failure
  ((:string file-name)
   (:fixnum-int character-mapping-protocol))) ; previously 0 (direct index)
					;   or 1 (BCID); now, per
					;   the "-mapping-protocol" variables
					;   corresponding change made
					;   simultaneously in fnt/c/fontrip.c
					;   (MHD 10/1/96)

(defun load-outline-font-file
    (outline-font-name outline-font-info character-mapping-protocol?)
  (let* ((subfont-and-char-id-function?
	   (subfont-and-char-id-function? outline-font-info))
	 (file-name?
	   (let ((name-or-function-to-get-name
		   (file-name-of-corresponding-outline-font
		     outline-font-info)))
	     (if (text-string-p name-or-function-to-get-name)
		 name-or-function-to-get-name
		 (let ((gensym-pathname-or-namestring?
			 (funcall name-or-function-to-get-name
				  (or (outline-font-file-name?
					outline-font-info)
				      (corresponding-outline-font
					outline-font-info)))))
		   (when gensym-pathname-or-namestring?
		     (prog1 (gensym-namestring gensym-pathname-or-namestring?)
		       (if (text-string-p gensym-pathname-or-namestring?)
			   (reclaim-text-string
			     gensym-pathname-or-namestring?)
			   (reclaim-gensym-pathname
			     gensym-pathname-or-namestring?)))))))))
    (when (and file-name? subfont-and-char-id-function?)
      ;; If there is a subfont-and-char-id-function?,
      ;; then the print name of the subfont must be
      ;; substituted for whatever file-name? is now.
      ;; Note that it is a convention to name the font
      ;; with an *, e.g., "minm_*" in the outline font
      ;; info, and in the name component of file-name? as
      ;; it is now, but does not buy this behavior, nor
      ;; is it required.  NOTE: It is now always assumed
      ;; that DirectIndex character mapping should be
      ;; employed when there's a subfont.  Otherwise,
      ;; BCID is used.
      (setq file-name?
	    (let ((new-gensym-pathname
		    (gensym-merge-pathnames
		      (symbol-name-text-string outline-font-name)
		      file-name?)))
	      (reclaim-text-string file-name?)
	      (prog1 (gensym-namestring new-gensym-pathname)
		(reclaim-gensym-pathname new-gensym-pathname)))))
    (when file-name?
      (prog1 (c-load-outline-font
	       file-name?
	       (or character-mapping-protocol? ; a real method, not zero-for-direct-indexing
		   (if (=f (outline-font-file-indexing-method ; here, 0 means for direct indexing
			     outline-font-info)
			   0)
		       protoDirectIndex-character-mapping-protocol
		       protoBCID-character-mapping-protocol)))
	(reclaim-text-string file-name?)))))




;;; `c-get-character-bounding-box-width-and-height' returns the width and height
;;; for the given character's raster, if possible.  This will be a positive
;;; integer if successful; otherwise, it returns 0.

;;; The value is a fixnum encoded into a height part and a width part, which
;;; should only be accessed using the following accessors.  The macro
;;; `bounding-box-width-part' accesses the width part of this function's return
;;; value.  The macro `bounding-box-height-part' accesses the height part of
;;; this function's return value.

(defmacro bounding-box-width-part (bounding-box-width-and-height)
  `(logandf ,bounding-box-width-and-height #xfff))

(defmacro bounding-box-height-part (bounding-box-width-and-height)
  `(ashf ,bounding-box-width-and-height -12))

(def-gensym-c-function c-get-character-bounding-box-width-and-height
  (:fixnum-int "g2fnt_get_bbox_width_and_height")
  ((:fixnum-int outline_font_handle)
   (:fixnum-int character-code)
   (:fixnum-int point-size-x-as-text-width)
   (:fixnum-int point-size-y-as-text-width)
   (:fixnum-int imported-set-width-or-zero-for-none)))

;; This assumes that you could never have a character whose raster width or
;; height is greater than 4095, the largest 12-bit number.  (MHD 7/12/93)










;;; Make-raster-for-character-using-outline-font-if-possible) ...

;;; This returns nil if it cannot create a raster for any reason.  Otherwise,
;;; it returns six values:
;;;
;;;   (1) a raster (or a bitmap, if make-bitmap-instead? is true);
;;;   (2) the x offset (as a text width) for the raster from the character origin;
;;;   (3) the y offset (in whole pixels) for the raster from the character origin;
;;;   (4) the width of the character's bounding box, i.e., the
;;;       width of the active part of the raster (note that
;;;       the raster may always be wider or taller than the
;;;       bounding box);
;;;   (5) the height of the character's bounding box; and
;;;   (6) the ideal set width of the character as a text width

;;; This function assumes that things have been arranged such that the
;;; width and height for the character in ab-font are within 25% plus
;;; 5 pixels of the size that the outline font will compute for them,
;;; after scaling.  This leaves ample allowance for divergences in the
;;; the scaling algorithms used by the ab-font raster scaler versus that
;;; used by the outline font raster image processor.  The only way this
;;; could fail would be if the outline font were radically different
;;; in terms of sizes of characters than ab-font, or if the font
;;; information in (outline-font-info ab-font) is not set up properly.

(defun-allowing-unwind make-raster-for-character-using-outline-font-if-possible
  (character-code orientation-code ab-font x-scale y-scale cjk-language? make-bitmap-instead?)
  (protected-let*
      ((outline-font-info-list
	 (get-outline-font-info-list ab-font cjk-language? character-code)
	 (reclaim-gensym-list outline-font-info-list)))
    (loop with raster?
	  with x-offset
	  with y-offset
	  with width
	  with height
	  with set-width
	  with outline-font-char-id
	  with outline-font-handle
	  for outline-font-info in outline-font-info-list
	  when (and (multiple-value-setq
			(outline-font-handle outline-font-char-id)
		      (get-outline-handle-and-char-id
			outline-font-info character-code))
		    outline-font-char-id
		    (multiple-value-setq
			(raster? x-offset y-offset width height set-width)
		      (internal-make-raster-for-character-using-outline-font-if-possible
			outline-font-char-id orientation-code x-scale y-scale
			outline-font-info outline-font-handle
			make-bitmap-instead?)))
	    return (values raster? x-offset y-offset width height set-width))))


(defun get-outline-font-info-list (ab-font cjk-language? character-code?)
  (let* ((font-name (ab-font-name ab-font))
	 (info? (outline-font-info font-name)))
    (if cjk-language?
	(let* ((korean-info? (kanji-font-associated-korean-outline-font-info font-name))
	       (chinese-info? (kanji-font-associated-chinese-outline-font-info font-name))
	       (japanese-info? info?)
	       (info-list
		 ;; Start off with a list ranked according to G2
		 ;; history/tradition.
		 (if (and character-code? ; here, a unicode
			  (<=f #x4e00 character-code? #x9fff)) ; Han chars
		     ;; But only do this for the Han characters -- why?  See
		     ;; "Note on Chinese Font Corrupted Roman Characters",
		     ;; below, for why we don't want the Chinese font to be used
		     ;; for non-Han characters even if it would look better than
		     ;; a Japanese bitmap font. (MHD 4/9/99)
		     (nconc 
		       (if japanese-info? (gensym-list japanese-info?))
		       (if korean-info? (gensym-list korean-info?))
		       (if chinese-info? (gensym-list chinese-info?)))
		     (gensym-list japanese-info?))))
	  ;; Now revise the ranking if necessary:
	  (case cjk-language?
	    (korean
	     (when korean-info?
	       (setf info-list
		     (delete-gensym-element korean-info? info-list))
	       (gensym-push korean-info? info-list)))
	    (chinese
	     (when chinese-info?
	       (setf info-list
		     (delete-gensym-element chinese-info? info-list))
	       (gensym-push chinese-info? info-list))))
	  info-list)
	(if info?
	    (gensym-list info?)))))

;; Consider caching static lists, e.g., as system-specific properties of the
;; language, rather than consing them up and reclaiming them per character, for
;; efficiency.  The list doesn't change in practice at run time. (MHD 4/9/99)

(defun internal-make-raster-for-character-using-outline-font-if-possible
    (outline-font-char-id orientation-code x-scale y-scale
			  outline-font-info outline-font-handle
			  make-bitmap-instead?)
  (let* ((scaled-horizontal-lines-per-em-as-text-width
	   (delta-x-in-window
	     (horizontal-lines-per-em-as-text-width outline-font-info)
	     x-scale))
	 (scaled-vertical-lines-per-em-as-text-width
	   (delta-y-in-window
	     (vertical-lines-per-em-as-text-width outline-font-info)
	     y-scale))
	 (character-bounding-box-width-and-height-or-zero
	   (c-get-character-bounding-box-width-and-height
	     outline-font-handle
	     outline-font-char-id
	     scaled-horizontal-lines-per-em-as-text-width
	     scaled-vertical-lines-per-em-as-text-width
	     0)))			; imposing set widths (unused)
    (unless (=f character-bounding-box-width-and-height-or-zero 0)
      (let* ((width-for-raster
	       (bounding-box-width-part
		 character-bounding-box-width-and-height-or-zero))
	     (height-for-raster
	       (bounding-box-height-part
		 character-bounding-box-width-and-height-or-zero)))
	(cond
	  (make-bitmap-instead?
	   (fill-outline-character-font-bitmap-using-outline-font
	     outline-font-char-id orientation-code outline-font-handle
	     scaled-horizontal-lines-per-em-as-text-width
	     scaled-vertical-lines-per-em-as-text-width
	     width-for-raster height-for-raster))
	  (t
	   (make-outline-character-raster-using-outline-font
	     outline-font-char-id orientation-code outline-font-handle
	     scaled-horizontal-lines-per-em-as-text-width
	     scaled-vertical-lines-per-em-as-text-width
	     width-for-raster height-for-raster
	     (oriented-x-value
	       width-for-raster height-for-raster orientation-code)
	     (oriented-y-value
	       width-for-raster height-for-raster orientation-code))))))))


(defun fill-outline-character-font-bitmap-using-outline-font
    (outline-font-char-id orientation-code outline-font-handle
			  scaled-horizontal-lines-per-em-as-text-width
			  scaled-vertical-lines-per-em-as-text-width
			  width-for-raster height-for-raster)
  (let* ((success-if-non-zero
	   (c-make-outline-character-raster
	     outline-font-handle
	     orientation-code
	     0
	     outline-font-char-id
	     scaled-horizontal-lines-per-em-as-text-width
	     scaled-vertical-lines-per-em-as-text-width
	     0
	     1)))
    (cond
      ((not (=f success-if-non-zero 0))
       (values
	 t
	 (c-get-text-x-offset-for-current-outline-character-raster)
	 (c-get-y-offset-for-current-outline-character-raster)
	 width-for-raster height-for-raster
	 (c-get-set-width-as-text-width-for-current-outline-character-raster)))
      (t nil))))

(defun make-outline-character-raster-using-outline-font
    (outline-font-char-id orientation-code outline-font-handle
			  scaled-horizontal-lines-per-em-as-text-width
			  scaled-vertical-lines-per-em-as-text-width
			  width-for-raster height-for-raster
			  oriented-width oriented-height)
  (let* (success-if-non-zero
	 (stored-raster
	   (on-scratchpad-raster-for-font-character-image
	     (current-window oriented-width oriented-height)
	     ('reclaim-all-scaled-fonts)
	     (setq
	       success-if-non-zero
	       (c-make-outline-character-raster
		 outline-font-handle
		 orientation-code
		 current-scratchpad-raster
		 outline-font-char-id
		 scaled-horizontal-lines-per-em-as-text-width
		 scaled-vertical-lines-per-em-as-text-width
		 0
		 0))))) 
    ;; imposing set widths unused (and non-working) functionality
    (cond
      ((not (=f success-if-non-zero 0))
       (values
	 stored-raster
	 (c-get-text-x-offset-for-current-outline-character-raster)
	 ;;  was: (c-get-x-offset-for-current-outline-character-raster)
	 (c-get-y-offset-for-current-outline-character-raster)
	 width-for-raster height-for-raster
	 (c-get-set-width-as-text-width-for-current-outline-character-raster)))
      (t
       (reclaim-stored-raster
	 stored-raster current-window width-for-raster height-for-raster
	 1				; bits-per-pixel per on-scratchpad-raster
	 nil)				; make-raster-exact-size-p
       nil))))

;; Note on Chinese Font Corrupted Roman Characters:
;;
;; Important mystery/bug: with certain characters, e.g., U+FF10, which is CJK
;; Wide Character Zero (0) in the new Chinese truetype font (Monotype Hei), the
;; raster width we're getting back is bad.  For example, with x-scale/y-scale =
;; 12672 (3.09375 * normalized scale), and the
;; scaled-horizontal-lines-per-em-as-text-width is 13860 (which is approximately
;; 54.14 lines per em), the resulting width we get back is 221.  This results in
;; a very wierd-looking, corrupted-looking bitmap.  The resulting height is 39,
;; which is what the width should be.  This has been reported to Monotype as
;; bug/mystery, but they don't know of any problem, and think it could be a
;; rasterizer issue.  It could be that, and could also be a bug in the layer we
;; have added between our software and the rasterizer (this code + the C file
;; fontrip.c). (MHD 4/9/99)

;; This would be improved by having a setup function

;; Usually, it would be possible to pack all for parts of the bounding box into
;; one 24-bit fixnum.  But it's not absolutely assured.  If you could, you could
;; go to having the x/y offset of the bounding box gotten by the call for the
;; width and height.

;; The final arg is not used, at present, unless the native widths are being used.
;; If width information were always available here, you could skip having that
;; arg.



;;; The c-callable function `open_character_bitmap_for_outline_font' ...
;;; The Lisp c-callable function `open-character-bitmap-for-outline-font' ...
;;; ... it is an error to call this with args greater than 29 bits, which means that
;;; the integer part of x_set_width, y_set_width, xorg, and yorg may not exceed
;;; (29 - 16) = 13 bits, or 8192.  Their type is long.

;(def-foreign-callable (open-character-bitmap-for-outline-font
;                        (:name "open_character_bitmap_for_outline_font")
;                        (:return-type fixnum))
;    ((x-set-width long)                 ; fix31 x_set_width
;     (y-set-width long)                 ; fix31 y_set_width
;     (x-origin long)                    ; fix31 xorg
;     (y-origin long)                    ; fix31 yorg
;     (width-for-bitmap short)           ; fix15 xsize
;     (height-of-bitmap short))          ; fix15 ysize
;  )
    




;;; The following three foreign functions support viewing outline font
;;; characters.

;;; The function `c-run-font-demo-1' is passed an outline font handle, width and
;;; height arguments, and a char-spec.  The char-spec can either be a code for a
;;; particular character or zero, to indicate that the first codes 0..255 be
;;; used.  The result is the output of "ascii art" pictures of the corresponding
;;; character glyphs. The outline font handle must correspond to an already
;;; loaded font, i.e., the value returned by c-load-outline-font.

;;; The function `c-run-built-in-font-demo' is similar, but it takes the name of
;;; a built-in font, and loads the font if needed.  It returns the font handle
;;; for font it loads, or -1 if there was a problem loading the font.

;;; The function `c-run-font-demo' is similar, but it takes a font file name as
;;; its first argument, and a character mapping protocol as its final argument.
;;; It always loads the named font file, i.e., using up one of the limited slots
;;; available to store the pointers to font memory .  It returns the font handle
;;; for font it loads, or -1 if there was a problem.

;;; Note that fonts may be loaded into memory only a limited number of times in
;;; any given Lisp session.  See corresponding c function in ext/c/fontrip.c for
;;; important additional details and limitations.

;;; Here are some examples of usage, which can be run from a Lisp listener with
;;; G2 or Telewindows loaded in development. Note: you must cd to the base of
;;; your sandbox and have the fonts module checked out in order to use the file
;;; examples as written (or modify them to reference a valid font file).
;;;
;;;   (c-run-built-in-font-demo "SWISS721-SWA" 25 25 0 0 #x40)
;;;   (c-run-font-demo "fonts/c/flat/font3004.spd" 25 25 0 0 #x40 protoUnicode-character-mapping-protocol)
;;;   (let ((m (c-load-outline-font "fonts/c/flat/font3004.spd" protoUnicode-character-mapping-protocol)))
;;;      (c-run-font-demo-1 m 25 25 0 0 #x40))
;;;
;;;   -- the above all output the same thing: a picture of the @ character
;;;
;;;   (c-run-built-in-font-demo "HEBREW" 25 25 0 0 #x05d5)
;;;   (c-run-font-demo "fonts/c/flat/hebrew.ttf" 30 30 0 0 #x05d5 protoUnicode-character-mapping-protocol)
;;;   (let ((m (c-load-outline-font "fonts/c/flat/hebrew.ttf" protoUnicode-character-mapping-protocol)))
;;;      (c-run-font-demo-1 m 25 25 0 0 #x05d5))
;;;
;;;   -- the above all output the same thing: a picture of VAV, which resembles
;;;   sans-serif cap. I
;;;
;;;   (c-run-built-in-font-demo "HEBREW" 50 50 0 0 #x20ac)
;;;   (c-run-font-demo "fonts/c/flat/hebrew.ttf" 50 50 0 0 #x20ac protoUnicode-character-mapping-protocol)
;;;   (let ((m (c-load-outline-font "fonts/c/flat/hebrew.ttf" protoUnicode-character-mapping-protocol)))
;;;      (c-run-font-demo-1 m 25 25 0 0 #x20ac))
;;;
;;;   -- the above all output the same thing: a big picture of the Euro
;;;   character, which happens to be in this font.

#+development
(def-gensym-c-function c-run-font-demo-1
    (:fixnum-int "g2fnt_run_font_demo_1")
  ((:fixnum-int outline-font-handle)
   (:fixnum-int h)
   (:fixnum-int v)
   (:fixnum-int fractional-h)
   (:fixnum-int fractional-v)
   (:fixnum-int char-spec)))

#+development
(def-gensym-c-function c-run-font-demo
    (:fixnum-int "g2fnt_run_font_demo")
  ((:string pathname)
   (:fixnum-int h)
   (:fixnum-int v)
   (:fixnum-int fractional-h)
   (:fixnum-int fractional-v)
   (:fixnum-int char-spec)
   (:fixnum-int character-mapping-protocol)))

#+development
(def-gensym-c-function c-run-built-in-font-demo
    (:fixnum-int "g2fnt_run_built_in_demo")
  ((:string font-name)
   (:fixnum-int h)
   (:fixnum-int v)
   (:fixnum-int fractional-h)
   (:fixnum-int fractional-v)
   (:fixnum-int char-spec)))




(def-gensym-c-function c-load-built-in-outline-font
    (:fixnum-int			; returns index in font memory 
      "g2fnt_load_built_in_outline_font")	;  array; negative if failure
  ((:fixnum-int built-in-font-id)))


(def-gensym-c-function c-make-outline-character-raster
  (:fixnum-int "g2fnt_make_outline_character_raster") ; returns success/failure
  ((:fixnum-int outline-font-handle)
   (:fixnum-int orientation-code)
   ;; if last arg is non-zero, abritrary (just supply 0):
   (:pointer irrelevant-pixmap-structure-pointer)
   (:fixnum-int character-code)
   (:fixnum-int scaled-horizontal-lines-per-em-as-text-width)
   (:fixnum-int scaled-vertical-lines-per-em-as-text-width)
   (:fixnum-int imported-set-width-or-zero-for-none)
   ;; one or zero, if zero writes into pixmap arg, 1 writes into temp raster:
   (:fixnum-int write-bitmap-to-temp-raster-or-zero)))


;;; `c-fontrip-bitmap-value' reads a value from the temporary raster produced in
;;; a call to `c-make-outline-character-raster' with a last argument of 1.  It
;;; returns either 1 or 0.  This is used for online bitmap production while
;;; printing, and also for offline bitmap production while creating bitmap
;;; fonts.  It should be preceeded by a call to c-make-outline-character-raster
;;; with the write-bitmap-to-temp-raster-or-zero argument = 1.

(def-gensym-c-function c-fontrip-bitmap-value 
  (:fixnum-int "g2fnt_fontrip_bitmap_value")
  ((:fixnum-int x)
   (:fixnum-int y)))

;; Made non-development to enable creation of bitmaps from outline fonts, for
;; printing, at run time. (MHD 5/7/99)


(def-gensym-c-function c-get-text-x-offset-for-current-outline-character-raster
  (:fixnum-int "g2fnt_get_textx_offset_for_cur_raster")
  ())


(def-gensym-c-function c-get-x-offset-for-current-outline-character-raster
  (:fixnum-int "g2fnt_get_x_offset_for_cur_raster")
  ;; name was changed recently in the C sources -- used to be called
  ;; get_x_offset_for_current_outline_character_raster; same for the Y
  ;; case; EXT/C directories need to be updated now.  (Name was longer
  ;; than 31 characters, which the Alpha objected to.) (MHD 6/10/93)
  ())					; OBSOLETE -- use one above!


(def-gensym-c-function c-get-y-offset-for-current-outline-character-raster
  (:fixnum-int "g2fnt_get_y_offset_for_cur_raster")
  ())


(def-gensym-c-function c-get-set-width-as-text-width-for-current-outline-character-raster
  (:fixnum-int "g2fnt_get_current_raster_text_width")
  ())

#+development
(defun get-ci (character ab-font-name &optional x-scale y-scale)
  (let* ((character-code (char-code character))
	 (ab-font (ab-font ab-font-name))
	 (scaled-font?
	  (get-or-make-scaled-font-1
	   (or x-scale (normalized-scale))
	   (or y-scale (normalized-scale))
	   ab-font nil)))
    (values
     (when scaled-font?
       (svref (scaled-font-character-image-cache scaled-font?) character-code))
     (when scaled-font?
       (scaled-font-character-image-cache scaled-font?))
     scaled-font?
     character-code)))

;; Issues
;;
;; Recycling of rasters when scaling fails is disabled!
;; Find out if scaling fails for illegitimate reasons, and fix them!
;; -> Eliminate "boolean" slop.
;;
;; How to add monospace?
;;  - Get from Bitstream "tuned" monospace.
;;
;; Consider courier?  Easier on PostScript printers!
;;
;; Downloading fonts story.
;;
;; OK to load at runtime?  Would be hard to save out
;; in G2 image, it seems.
;;
;; Japanese fonts -- bring up new software -- read J. fonts doc (Bitstream)
;;
;;
;; Check in -- get compiles going on different platforms!
;;
;; BUG IN SCALING -- straybits & dropout! Fax in to bitstream!
;;
;; Bug in widths -- the last column of bits is being left out sometimes!
;;
;; Clear up confusion:
;; Fix size, bounding-box slots in font structure.  Fix exising fonts def.
;; (HM15 has size=15, e.g., etc.)
;;
;; Fix up (names of) slots in character-image structure.
;;
;; Review increasing maximum-scane by 4X in window attributes plist!
;;
;; Consider adding EXTRA-SMALL, TINY as "fonts" in the "fonts" system
;; table.  These could be hm10 and hm7.  (We have hm7, 8, 9, 10, and 12
;; in tuned sizes licensed from adobe, in addition to hm14, 18, and 24,
;; which we already use.)
;;
;; What to do about "font-size" (term in annotations) vs. "font" (term
;; in message definitions and fonts system table)
;;
;; Fixed-width: could add a new set of fonts named fixed-width-large,
;; fixed-width-small, fixed-width-extra-large, etc.
;;
;; Ask why the max_bits clipping should be needed -- just for the application,
;; i.e., the X&O's demo?  Or is there some slop inherent in the program. For
;; now, we're leaving the max_bits check out.
;;
;; Get the rest of our characters in -- right now we only do ascii --
;; figure out the rest, e.g., copyright, trademark, specials, euros.
;;
;; Plan to hand-tune wide characters on a character-specific fudge - could
;; get the fudge factor in, semiautomate.
;;
;;
;; We have the option to use Adobe-contributed 75dpi and 100dpi screen
;; fonts and outline fonts (type1 format) for typeface Utopia.  It's
;; located currently in
;;    ~/X11R5/contrib/fonts/Utopia/UTRG____.dir/UTRG____.pfa
;; (It comes with bitmaps for point sizes 10, 12, 14, 18, and 24, nearby
;; in the directory tree.)  The 4in1 processor handles these files fine.
;;
;; We similarly may use ~/X11R5/contrib/fonts/scaled/Type1/cour.pfa, a Type1
;; courier font.  This was contributed by IBM.  It has an IBM trademark.  There
;; are no bitmap files nearby; maybe they're located elsewhere.
;;
;; Then, there's a Speedo Bitstream Courier font, located in
;;   ~/X11R5/mit/fonts/scaled/Speedo/font0419.spd
;; This has associated bitmap fonts in 75dpi for point sizes 10, 12, 14, 18,
;; and 24 in
;;   ~/X11R5/mit/fonts/bdf/75dpi/courR10.bdf
;; and so on for different sizes.
;;
;; Then there's a Speedo "Transitional 801 Bitstream Charter", located in
;;   ~/X11R5/mit/fonts/scaled/Speedo/font0648.spd
;; This has associated bitmap fonts in 75dpi for point sizes 10, 12, 14, 18,
;; and 24 in
;;   ~/X11R5/mit/fonts/bdf/75dpi/charR10.bdf
;; and so on for different sizes.
;;
;; What's pretty interesting is that Adobe Helvetica screen fonts "just
;; like ours" are located in
;;   ~/X11R5/mit/fonts/bdf/75dpi/helvR10.bdf
;; etc.  These are like ours, but there are some differences:
;; Its Bitmap Distribution Format 2.1, where ours is 2.0, and some of the
;; characters glyphs are different.  Some of the widths may be different,
;; but I've not found any by eyeballing it.  They seem to be more complete
;; in terms of relating to ISO-8859-1 (ISO Latin-1), having encodings, etc.
;;
;; Our original adobe hand-tuned bitmaps are in
;;   ~/adobe/hm10.bit
;; and so on for other sizes.
;;
;; Note that we hand tuned some of our character glyphs, but none of our
;; setwidths -- see hand-tuning information, above.
;; (get-hand-edits-for-character-if-appropriate)
;;
;; Other bitmap fonts in the directory
;;    ~/X11R5/mit/fonts/bdf/75dpi/
;; include Adobe's New Century Schoolbook, Bigelow & Holmes's Lucida,
;; Adobe's Symbol, and Adobe's Times.
;;
;; (~ means /home/mhd.)
;;
;; Should this return the set width?  As a "text width" (fixnum w/fraction
;; bits)?  Returning this would allow using outline fonts without any bitmap
;; font, or metric information at all.  I think the C interface function
;; should now be written.  
;;
;;
;; How to use these?  Should they really be kept in memory?  It takes just
;; a fraction of a second on a fast machine to read them in.  However, it
;; adds the hassle of having to worry about where the font file is.  If
;; it gets lost, you can be screwed.
;;
;;
;;
;; Character-image structures should take up less space -- they could use
;; a single fixnum to encode a bounding box, for example.  The old way
;; was best for really slow machines, where you wanted to avoid decoding
;; them.  They should also probably encode x offset, y offset, width,
;; and height, rather than left, top, right, and bottom, for consistency.
;;
;;
;; 
;; PROBLEM: Swiss721 is not really compatible with our Adobe set widths.
;; The m's and w's being too wide are a major problem.  Plus, they're
;; probably off in various other ways.  A t next to an f will will overlap
;; at times.
;;
;; Two possible solutions: (1) Bitstream has a Speedo Swiss721-SWA font, which
;; is "a completely different font" compatible with Adobe's set widths.  Karen
;; Tackett is trying to prepare this font for our evaluation.  (2) Bitstream's
;; speedo processor conveniently comes with a function sp_make_char_isw, which
;; takes a character's set width, will squeezes it to fit.  I will try making
;; use of that in the meantime.
;;
;; Hmmmm: I just noticed that the DWIDTHs don't correspond to the SWIDTHs exactly:
;; Take our HM14 for example:
;;    m DWIDTH: 14 SWIDTH: 833
;;    M DWIDTH: 16 SWIDTH: 833
;; In other words, a 2-pixel difference in device-width with zero (0) difference
;; in scaleable width.  BUT: that doesn't even make sense.  A bug? Maybe.
;; If you look at the (newer) "HM14" in the X11R5 distribution, they have
;;    m DWIDTH: 11 SWIDTH: 833
;;    M DWIDTH: 13 SWIDTH: 833
;; In either case, non-equal device widths are resulting from equal scaleable
;; widths, which is surprising in a way.  If you go and print a line of M's and
;; a line of m's on an Apple Laser writer with Adobe PostScript, it is true
;; that the lines end up exactly the same length.  So having 833 for both seems
;; right.

;; Using SWISS-721-SWA, at full scale.
;;
;; -- General Impression: looks bad
;; -- rn looks exactly the same as m.
;; -- doesn't look exactly the same as on the Mac, not as good
;; -- m/M matches up
;;
;; Regarding Break on BuildSortedSpeedoIDList in frontend.c. -- see that it actually
;; sorts things.  See that for a given BCID -- see what index you get.  When sp_get_char_org
;; is called for that index, see that the index is the same.

;; Plan of action on sizes:  (6/1/93)
;; (1) Change hm14.lisp ab-font-size to 14, from 15.  DONE. (6/1/93)
;; (2) Change kanji16, kanji24, hangul16, hangul24.
;; (3) Fix references to ab-font-size in printing.  Fix references
;;     to ab-font-size and ab-font-baseline in charts1.
;; (4) Make up real fonts for the scaled outlines, using scaleable widths.
;; (5) Substitute in names of scaled outline fonts in formats.
;; (6) Old fonts will be "not in printer" -- printer should be
;;     downloaded with the widths and bitmaps when it has a font
;;     "not in printer"; new font - Helvetica - will be assumed to
;;     be in the printer.  Must always use scaleable widths.  (Actually,
;;     that's idealistic -- we will continue to use the printer's glyphs
;;     for Helvetica, but will impose our set widths,  This is for
;;     compatibility.
;; (7) If using new scaleable widths with an old Telewindows, must
;;     write a version of add-from-line-of-text that does the tracking
;;     of individual characters.  [will be slowish.]
;; (8) Add a "character-fudge-factor" facility -- for squeezing characters
;; (9) a bit.
;;
;;
;;
;; 
;; Problem: g hangs down below the bounding box on the main menu when scaled
;; down 10% once.
;; ---UPDATE: this was fixed by fixing a bug involving doubly scaling the
;; part of the width of the baseline-to-baseline band.
;;
;; Problem: g hangs down below the bounding box in the editor using small font
;; format, at any scale.  This is probably a problem with the format.
;;
;; Todo: Add a rev. to the Telewindows protocol: "fontrip-available", or something.


;; Issue or mapping with Bitream's 4-in-1:
;; 
;; Date: Thu, 15 Aug 96 15:32:25 edt
;; From: "karen" <karen@met.bitstream.com>
;; To: mhd@mailhost (Mark H David)
;; Subject: Re: protoUnicode mapping protocol
;; 
;; Yes, this mapping works. I'll try to guess what is set up wrong at 
;; your end. 
;; 
;; If you are working with a Speedo font, you simply have to set the 
;; flag to define protoUnicode, pass in Unicode values, and we do a 
;; mapping to our BCID. The BCID is passed to the rasterizer without 
;; any effort on your part. The Unicode to BCID (and other schemes) 
;; mapping is contained in the CMTGLOB.C file. 
;; 
;; I suspect, however, your problem is with a TrueType font. For 
;; TrueType, we assume that the char code being passed in is a 
;; Unicode value. You do not have to set the protocol. 
;; 
;; The next step is to call the function tt_load_font_params() with 
;; the correct platform ID, specific ID pair.  Our default is 1,0 
;; which indicates the Apple CMAP. Your Unicode will actually be 
;; interpreted as a one-byte index into the Apple CMAP, which 
;; contains 256 chars.  I suspect this is not what you wish to 
;; achieve. 
;; 
;; If you want to select a character in the Windows CMAP, you must 
;; use the pair 3,1.  The pair would be 3,0 for a symbol or non-Latin 
;; font.  This allows us to load the CMAP, and lookup the char glyph 
;; for the Unicode value provided. 
;; 
;; If this doesn't solve the problem, I need much more detail: what 
;; font format are you using, what font, what Unicode requested, what 
;; glyph is rendered, or what error is returned. 
;; 
;; -Karen Tackett
;; karen@bitstream.com 
;; 
;; 
;; ______________________________ Reply Separator _________________________________
;; Subject: protoUnicode mapping protocol
;; Author:  mhd@gensym.com (Mark H David) at huxleypo
;; Date:    8/15/96 1:42 PM
;; 
;; 
;; Does the protoUnicode mapping protocol work?  I didn't 
;; see anything that looked like a mapping table among 
;; the sources. And when I briefly tried turning it on, 
;; it did not seem to work.  Are I could easily install 
;; to get this to work, or ..... Any advice?
;; 
;; Thanks,
;; 
;; Mark








;; We are now making new fonts with the following function:

#+development
(progn
(defun make-new-gensym-adobe-bitmap-fonts ()
  ;; also consider: hm7, hm8, hm9, hm10, hm12
  (make-ab-font-from-adobe-font-file "/home/mhd/adobe/hm14.bit")
  (make-ab-font-from-adobe-font-file "/home/mhd/adobe/hm18.bit")
  (make-ab-font-from-adobe-font-file "/home/mhd/adobe/hm24.bit")
  (make-ab-font-from-adobe-font-file "/home/mhd/adobe/hb72.bit"))


(defun make-new-gensym-adobe-bitmap-fonts-2 ()
  (make-ab-font-from-adobe-font-file "/home/mhd/X11R5/mit/fonts/bdf/75dpi/helvR14.bdf" 'roman 'hm14)
  (make-ab-font-from-adobe-font-file "/home/mhd/X11R5/mit/fonts/bdf/75dpi/helvR18.bdf" 'roman 'hm18)
  (make-ab-font-from-adobe-font-file "/home/mhd/X11R5/mit/fonts/bdf/75dpi/helvR24.bdf" 'roman 'hm24))


;; See (switch-to-scaleable-widths) and (switch-to-device-widths), in BOXES.


(defun save-new-gensym-adobe-bitmap-fonts ()
  (save-ab-font 'hm14 "/home/mhd/adobe/hm14.lisp")
  (save-ab-font 'hm18 "/home/mhd/adobe/hm18.lisp")
  (save-ab-font 'hm24 "/home/mhd/adobe/hm24.lisp")
  (save-ab-font
    'hb72 "/home/mhd/adobe/hb72.lisp"    
    (tformat-text-string
      "Telewindows Gensym G2~c~c"
      %trade-mark-sign %registered-sign)))

;;; `Load-and-save-new-gensym-adobe-bitmap-fonts' is used to generate the
;;; AB-Latin Lisp fonts hm14, hm18, hm24, and hb72, from the .bit masters.

(defun load-and-save-new-gensym-adobe-bitmap-fonts ()
  (make-new-gensym-adobe-bitmap-fonts)
  (save-new-gensym-adobe-bitmap-fonts))

(defun decache-font-bitmaps ()
  (loop for font-name in '(hm14 hm18 hm24 hb72 kanji16 kanji24 slavic14 slavic18 slavic24)
	as font? = (ab-font font-name)
	when font?
	  do (setf (ab-font-cache-of-scaled-fonts font?) (list nil)))
  (loop for subfont-name in '(j16_0 j16_1 j16_2 j24_0 j24_1 j24_2
			      k16_0 k16_1 k16_2 k24_0 k24_1 k24_2)
	do (setf (bitmap-font-data-handle subfont-name) nil)))

(defun toggle-outlines-for-full-scale ()
  (decache-font-bitmaps)
  (setq prefer-bitmap-to-scaled-outline-font-at-full-scale?
	(not prefer-bitmap-to-scaled-outline-font-at-full-scale?))
  (list 'prefer-bitmap-to-scaled-outline-font?
	prefer-bitmap-to-scaled-outline-font?
	'prefer-bitmap-to-scaled-outline-font-at-full-scale?
	prefer-bitmap-to-scaled-outline-font-at-full-scale?))

(defun toggle-outlines-for-any-scale ()
  (decache-font-bitmaps)
  (setq prefer-bitmap-to-scaled-outline-font?
	(not prefer-bitmap-to-scaled-outline-font?))
  (list 'prefer-bitmap-to-scaled-outline-font?
	prefer-bitmap-to-scaled-outline-font?
	'prefer-bitmap-to-scaled-outline-font-at-full-scale?
	prefer-bitmap-to-scaled-outline-font-at-full-scale?))



)

;;; 4 kinds of (Helvetica) fonts:
;;;
;;; 1 - Hand-tuned Widths/Bitmaps/Corresponding Printer Font (HM14)  		[traditional G2 Font, 14 pt, 75dpi]
;;; 2 - Scaleable Widths/Bitmaps/Corresponding Printer Font (HM14-SWA)		[Above with scaleable widths,
;;;                                                                              not in old TW's]
;;; 3 - Hand-tuned Widths/Outlines/Corresponding Printer Font (SWISS-721-SWG2)	[Speedo Font, Scaled to 14 pt.,
;;; 										 Set Width's from Trad. G2 Font]
;;; 4 - Scaleable Widths/Outlines/Corresponding Printer Font (SWISS-721-SWA)
;;;
;;; 



#+development
(progn
(defun make-new-cyrillic-gensym-bitmap-fonts ()
  ;; Modeled on make-new-gensym-adobe-bitmap-fonts
  (make-ab-font-from-tt-font 'slavic14 'hm14)
  (make-ab-font-from-tt-font 'slavic18 'hm18)
  (make-ab-font-from-tt-font 'slavic24 'hm24))

(defun make-new-hebrew-gensym-truetype-bitmap-fonts ()
  (make-ab-font-from-tt-font 'hebrew14 'hm14)
  (make-ab-font-from-tt-font 'hebrew18 'hm18)
  (make-ab-font-from-tt-font 'hebrew24 'hm24))

(defun make-new-thai-gensym-truetype-bitmap-fonts ()
  (make-ab-font-from-tt-font 'thai14 'hm14)
  (make-ab-font-from-tt-font 'thai18 'hm18)
  (make-ab-font-from-tt-font 'thai24 'hm24))

(defun save-new-cyrillic-gensym-bitmap-fonts ()
  (save-ab-font 'slavic14 "slavic14.lisp" nil 'slavic-bitmaps)
  (save-ab-font 'slavic18 "slavic18.lisp" nil 'slavic-bitmaps)
  (save-ab-font 'slavic24 "slavic24.lisp" nil 'slavic-bitmaps))

(defun save-new-hebrew-gensym-truetype-bitmap-fonts ()
  (save-ab-font 'hebrew14 "hebrew14.lisp" nil 'hebrew-bitmaps)
  (save-ab-font 'hebrew18 "hebrew18.lisp" nil 'hebrew-bitmaps)
  (save-ab-font 'hebrew24 "hebrew24.lisp" nil 'hebrew-bitmaps))

(defun save-new-thai-gensym-truetype-bitmap-fonts ()
  (save-ab-font 'thai14 "thai14.lisp" nil 'thai-bitmaps)
  (save-ab-font 'thai18 "thai18.lisp" nil 'thai-bitmaps)
  (save-ab-font 'thai24 "thai24.lisp" nil 'thai-bitmaps))

(defun load-and-save-new-cyrillic-gensym-bitmap-fonts ()
  (make-new-cyrillic-gensym-bitmap-fonts)
  (save-new-cyrillic-gensym-bitmap-fonts))

(defun load-and-save-new-hebrew-gensym-truetype-bitmap-fonts ()
  (make-new-hebrew-gensym-truetype-bitmap-fonts)
  (save-new-hebrew-gensym-truetype-bitmap-fonts))

(defun load-and-save-new-thai-gensym-truetype-bitmap-fonts ()
  (make-new-thai-gensym-truetype-bitmap-fonts)
  (save-new-thai-gensym-truetype-bitmap-fonts))

(defun make-ab-font-from-tt-font (font-name related-ab-font-name
					    &optional
					    (verbose-p nil)
					    (ab-font-type 'ROMAN)
					    (number-of-characters 128))
  ;; Modeled on make-ab-font-from-adobe-font-file.  The information taken from
  ;; the related-ab-font may not be appropriate.
  number-of-characters ;  Not yet used.
  (let* ((related-ab-font (ab-font related-ab-font-name))
	 (outline-font-info (outline-font-info font-name))
	 (handle (get-outline-handle-and-char-id outline-font-info)))
    (when handle
      (let (ab-font
	     (point-size (point-size-of-the-bitmap-font outline-font-info))
	     (x-resolution (original-bitmap-x-device-resolution outline-font-info))
	     (y-resolution (original-bitmap-y-device-resolution outline-font-info))
	     (width-in-x (horizontal-lines-per-em-as-text-width outline-font-info)) ; font bounding box
	     (width-in-y (vertical-lines-per-em-as-text-width outline-font-info))
	     ;; The offset values may need to be extracted from the real font.
	     (x-offset (ab-font-x-offset related-ab-font)) ; displacement
	     (y-offset (ab-font-y-offset related-ab-font)) ; displacement
	     )
	(setq ab-font
	      (new-make-ab-font
		font-name ab-font-type

		;; "obsolete" args:
		point-size
		(ab-font-baseline related-ab-font)
		(ab-font-maximum-width related-ab-font)
		(ab-font-maximum-height related-ab-font)		  
		
		;; Old args -- these are ok:
		;;   fixed-width-of-font? fixed-bounding-box-of-font?
		nil nil  ; compute these? -- get from properties (now ignored)?

		;; new args:

		;; SIZE
		point-size x-resolution y-resolution

		;; FONTBOUNDINGBOX
		width-in-x width-in-y
		x-offset y-offset))
	(cond
	  ((search "SLAVIC" (symbol-name font-name))
	   ;; not general -- for cyrillic only:
	   (loop as unicode-index from 0 below 128
		 as font-character-code = (+f unicode-index 32)
		 as char-id? = (map-unicode-index-to-slavic-font-direct-index unicode-index)
		 when char-id?
		   do 
		     ;; modeled on get-adobe-character-from-stream
		     (convert-tt-character-to-ab-character
		       font-character-code char-id?
		       handle ab-font point-size
		       x-resolution verbose-p)))
	  ((search "HEBREW" (symbol-name font-name))
	   ;; also nongeneral: for Hebrew only:
	   (loop as unicode from 0 below #xFFFF
		 when (hebrew-unicode-p unicode)
		   do (let ((font-character-code
			      (map-unicode-to-ab-hebrew-font-code-if-any unicode)))
			(cond
			 ((null font-character-code)
			  (cerror "skip character" "Character with Unicode #x~x can't be handled"
				  unicode))
			 (t
			  (convert-tt-character-to-ab-character
			   font-character-code unicode
			   handle ab-font point-size
			   x-resolution verbose-p))))))
	  ((search "THAI" (symbol-name font-name))
	   ;; also nongeneral: for Thai only:
	   (loop as unicode from 0 below #xFFFF
		 when (thai-unicode-p unicode)
		   do (let ((font-character-code
			      (map-unicode-to-ab-thai-font-code-if-any unicode)))
			(cond
			 ((null font-character-code)
			  (cerror "skip character" "Character with Unicode #x~x can't be handled"
				  unicode))
			 (t
			  (convert-tt-character-to-ab-character
			   font-character-code unicode
			   handle ab-font point-size
			   x-resolution verbose-p))))))
	  (t (break "Don't know this case!")))
	(setf (ab-font font-name) ab-font)
	ab-font))))  

(defun convert-tt-character-to-ab-character
    (character-code char-id
		    font-handle ab-font point-size
		    x-resolution
		    &optional (verbose-p t) (imported-set-width 0))
  (let* 
      (height-for-raster
	width-for-raster
	(point-size-x-as-text-width
	  (compute-lines-per-em-as-text-width point-size x-resolution))
	(point-size-y-as-text-width
	  (compute-lines-per-em-as-text-width point-size x-resolution)); y resolution?
	(character-bounding-box-width-and-height-or-zero
	  (c-get-character-bounding-box-width-and-height
	    font-handle char-id
	    point-size-x-as-text-width point-size-y-as-text-width imported-set-width)))
;    (when (zerop character-bounding-box-width-and-height-or-zero) (error "Bad bounding box value"))
    (setq width-for-raster
	  (bounding-box-width-part
	    character-bounding-box-width-and-height-or-zero))
    (setq height-for-raster
	  (bounding-box-height-part
	    character-bounding-box-width-and-height-or-zero))
    (let* ((set-width-as-text-width (c-get-set-width-as-text-width-for-current-outline-character-raster))
	   (bounding-box-x-offset (c-get-x-offset-for-current-outline-character-raster))
	   (bounding-box-y-offset (c-get-y-offset-for-current-outline-character-raster)))
      (setq current-ab-font? ab-font)
      ;;current-ab-font? must be set
      (if verbose-p (format t "\nConverting ~d" character-code))
      (unless (c-make-outline-character-raster
		font-handle
		0                       ; normal-orientation ..should declare as constant
		0			; irrelevant
		char-id
		(ab-font-width-in-x ab-font)
		(ab-font-width-in-y ab-font)
		0
		1)
	(error "failed to create character"))
      (let ((character-bitmap
	      (allocate-character-bitmap
		width-for-raster height-for-raster)))	; fixed-width/fixed-bbox
	(loop for x from 0 below width-for-raster do
	  (loop for y from 0 below height-for-raster do
	    (setf (character-bitmap-value character-bitmap x y)
		  (c-fontrip-bitmap-value x y))))
	(let ((rectangle-array
		(convert-character-bitmap-to-rectangle-array
		  character-bitmap width-for-raster height-for-raster)))
	  (add-character-description
	    character-code
	    (text-width-to-x set-width-as-text-width)
	    bounding-box-x-offset
	    bounding-box-y-offset
	    width-for-raster
	    height-for-raster
	    rectangle-array
	    set-width-as-text-width))))))

#+comment
(defun slavic-test ()
  (make-new-top-level-kb-workspace
    'kb-workspace
    nil 'slavic-test
    (make-free-text-box
      (twith-output-to-text-string
	(loop for i from 0 below 128
	      when (and (not (=f i 0)) (=f (modf i 16) 0))
		do (tformat "~%")
	      when (map-unicode-index-to-slavic-font-direct-index i)
		do (twrite-string (kstring (+ #x2000 i))))))))
)




;; Sadly, the next two sections are mired in "the future" -- i.e., they're not ready
;; for prime time yet, and are not being used. (MHD)



;;;; Def-font


#+def-font
(defmacro def-font (&body font-structure-fields-and-values)
  `(list  ; FINISH!!
    . ,font-structure-fields-and-values))
  




;;;; Font Declarations


;;; SWISS14 is a bitmap font, not loaded into the image at (Lisp) load time, that
;;; should only be used non-outline-font capable platforms, such as the Lisp
;;; machine, that wish to emulate the look of the outline font SWISS-721-SWA,
;;; q.v.
;;;
;;; SWISS18 and SWISS24 are just 18 and 24-point, 75 dpi, variations of SWISS14,
;;; which is 14-point, 75dpi.

;; Stack:
;; - way to know if loaded yet
;; - way to trigger on authorization -- for J. & K.
;; - way to substitute, e.g., HM14 for SWISS14 if not supported in
;;   the Telewindows protocol
;; - get JH to support a GENSYM_FONT environment variable/command line arg
;; - get JH to support gensym instead of g2 or tw and just have one def-suite
;; - define the def-font macro
;; - define all fonts this way
;; - 

#+def-font
(def-suite-for-loading-file-at-launch-time swiss14 g2
  :base-name-of-file-to-load   "swiss14"
  :type-of-file-to-load        "gf"
  :command-line-keyword        "swiss14-font"
  :environment-variable-name   "SWISS14-FONT"
  :base-name-of-disabling-file "NOSWISS14-FONT"
  :type-of-disabling-file      "CMD"
  :module telestubs)

#+def-font
(def-suite-for-loading-file-at-launch-time swiss14 tw
  :base-name-of-file-to-load   "swiss14"
  :type-of-file-to-load        "gf"
  :command-line-keyword        "swiss14-font"
  :environment-variable-name   "SWISS14-FONT"
  :base-name-of-disabling-file "NOSWISS14-FONT"
  :type-of-disabling-file      "CMD"
  :module telestubs)


#+def-font
(def-font (ab-font-name SWISS14)

  (ab-font-format bitmap)

  (fixed-width-of-font? nil)
  (ab-font-style roman)
  (ab-font-weight medium)

  ;; obsolete! eliminate!
  (ab-font-size 14)
  (ab-font-baseline 12)
  (ab-font-maximum-width 16)
  (ab-font-maximum-height 18)

  ;; newer replacements
  (ab-font-point-size 14)
  (ab-font-x-resolution 75)
  (ab-font-y-resolution 75)

  (ab-font-width-in-x 15)
  (ab-font-width-in-y 15)
  (ab-font-x-offset -1)
  (ab-font-y-offset -3)

  (corresponding-outline-font? SWISS-721-SWA)
  (similar-bitmap-font HM14)

  (minimum-telewindows-protocol-for-use outline-font-support)  ; (DEFINE!)(DEFINE!)

  (font-loading-pathname-or-pathname-getter get-or-use-g2-swiss14-pathname) ; (DEFINE!)
  (format-of-font-file gf) ; GF, LISP, C-SPEEDO, SPEEDO, TYPE1, TRUETYPE, PCL, [BDF?]
			   ; LISP and C-SPEEDO are linked right into the G2/TW image
			   ; LISP and GF yield bitmap fonts
			   ; C-SPEEDO yields a SPEEDO font

  (when-to-load-font first-use)  ; (DEFINE!) FIRST-USE, AUTHORIZATION, STARTUP, LOAD-TIME
  (when-font-is-needed missing-corresponding-outline-font) ; (DEFINE!)

  )

#+def-font
(def-suite-for-loading-file-at-launch-time swiss14 g2
  :base-name-of-file-to-load   "swiss14"
  :type-of-file-to-load        "gf"
  :command-line-keyword        "swiss14-font"
  :environment-variable-name   "SWISS14-FONT"
  :base-name-of-disabling-file "NOSWISS14-FONT"
  :type-of-disabling-file      "CMD"
  :module telestubs)

#+def-font
(def-suite-for-loading-file-at-launch-time swiss14 tw
  :base-name-of-file-to-load   "swiss14"
  :type-of-file-to-load        "gf"
  :command-line-keyword        "swiss14-font"
  :environment-variable-name   "SWISS14-FONT"
  :base-name-of-disabling-file "NOSWISS14-FONT"
  :type-of-disabling-file      "CMD"
  :module telestubs)


#+def-font
(def-font (ab-font-name SWISS14)

  (ab-font-format bitmap)

  (fixed-width-of-font? nil)
  (ab-font-style roman)
  (ab-font-weight medium)

  ;; obsolete! eliminate!
  (ab-font-size 14)
  (ab-font-baseline 12)
  (ab-font-maximum-width 16)
  (ab-font-maximum-height 18)

  ;; newer replacements
  (ab-font-point-size 14)
  (ab-font-x-resolution 75)
  (ab-font-y-resolution 75)

  (ab-font-width-in-x 15)
  (ab-font-width-in-y 15)
  (ab-font-x-offset -1)
  (ab-font-y-offset -3)

  (corresponding-outline-font? SWISS-721-SWA)
  (similar-bitmap-font HM14)

  (minimum-telewindows-protocol-for-use outline-font-support)  ; (DEFINE!)(DEFINE!)

  (font-loading-pathname-or-pathname-getter get-or-use-g2-swiss14-pathname) ; (DEFINE!)
  (format-of-font-file gf) ; GF, LISP, SPEEDO, TYPE1, TRUETYPE, PCL, [BDF?]

  (when-to-load-font first-use)  ; (DEFINE!) FIRST-USE, AUTHORIZATION, STARTUP, LOAD-TIME
  (when-font-is-needed missing-corresponding-outline-font) ; (DEFINE!)

  )
  





;;;; Converting Binary Font Files to C Programs


;;; Convert-binary-file-to-c-program opens a binary file and writes
;;; out a C source file contains a declaration of an array of bytes
;;; equivalent to the contents of the input file.
;;;
;;; This will be used for converting the binary data in font files
;;; into linkable object modules, which will allow fonts to be linked
;;; right into the image.

#+development
(defun convert-binary-file-to-c-program (binary-file-name c-file-name &optional array-base-name?)
  (let* ((binary-pathname (pathname binary-file-name))
	 (array-base-name
	  (or array-base-name? (pathname-name binary-pathname)))
	 (array-name
	  (format nil "~a_array" array-base-name)))
    (with-open-file (input-stream binary-file-name :element-type '(unsigned-byte 8))
      (with-open-file (output-stream c-file-name :direction :output)
	(format
	  output-stream
	  "/* C Version of Binary File ~S */~%"
	  (namestring binary-pathname))
	(format
	  output-stream
	  "static unsigned char ~a[] = {~%"
	  array-name)
	(loop for byte? = (read-byte input-stream nil nil)
	      as first-time? = t then nil
	      as count from 0
	      while byte?
	      when (not first-time?)
	        do (format output-stream ",")
		   (if (= (mod count 10) 0)
		       (format output-stream "~%")
		       (format output-stream " "))
	      do (format output-stream "0x~x" byte?)
	      count t into size
	      finally
		(format output-stream "~%};~%")
		(format output-stream "~%static unsigned long ~a_size = ~d;~%"
			array-base-name size))))))


;; The above was used as follows:
;;
;;    (convert-binary-file-to-c-program "/bt/mhd/lisp/font3004.spd" "/bt/ext/c/font3004.h")
;;
;; Then font3004.h was then included in fontrip.c.  Then font3004_array was made one of
;; the "built in" fonts (the only one, so far) known about by fontrip.c.  Then it was
;; also made into a known built-in font in this module (FONTS).
;;
;; ---
;; Used again, after revisions, with
;;
;;    (convert-binary-file-to-c-program
;;       "/home/mhd/bitstream/swa-fonts/font3008.spd"
;;       "/bt/mhd/sun4/fonts/c/flat/font3008.h")  ; Bitstream's "Courier SWA" font
;;

;; Used for generating the Hebrew font (which includes the Euro character): --
;; takes about a minute to finish in our development environment.  (MHD
;; 10/12/99)

#+development
(defun generate-hebrew-dot-h-file-from-ttf ()
  (convert-binary-file-to-c-program
    "/bt/mhd/fonts/c/flat/hebrew.ttf"
    "/bt/mhd/fnt/c/hebrew.h"))

#+development
(defun generate-thai-dot-h-file-from-ttf ()
  (convert-binary-file-to-c-program "thai.ttf" "thai.h"))

;; The following comments are several years old, and apply to bitstream "SWA"
;; fonts: (MHD 10/12/99)
;;
;; PROBLEM: this font has missing characters, and characters out of place!
;; PROBLEM: the above is caused by the fact that we're using Bitstream's SWA font
;; (Swiss 721 SWA), and Bitstream only supplies the characters in the standard
;; encoding vector.  This means it does not include such characters as accented
;; characters (A-acute, for example) or Trademark, Copyright, or Registered.  It
;; also means that they don't supply the character at 126 ("tilde spacing") -- but
;; they do supply they character they call "Math Half Approximation", which is
;; what they map to for the request to get asciitilde.
;; (This is a gross pain in the neck!!!)

;; PROBLEM: (related)  The "backquote" character (ascii 96) is really code 137
;; in Bitstream's SWA.  This is even a bigger pain in the neck, since this character
;; is not in the special characters alist, leaving us without an easy kludge
;; to fix this, as we had in the above tilde case.
;; --- SOLVED: you actually can "just" (easily) add an entry for the backquote
;; character to the map, which I have done.  The ascii codes and the special
;; character codes are disjoint, making this possible.



;; PROBLEM: the accented capital letters extend above the height of the ascenders.
;; Sometimes this causes the accent to be clipped off.  (The top of the tilde
;; in Ntilde at 4X - 10% scale is lopped off.  It shows OK at 4X scale.)
;; This is not really acceptable.  Note that the tuned bitmaps (from Adobe) have
;; squashed accented characters, so that the line height is about the same.  That
;; looks ugly, and this looks a lot better.  But they're not really compatible
;; looks.  (And then printing -- with printer Helvetica -- doesn't have the
;; squashing, and probably doesn't have the chopping off.)  Another really
;; bad case: Acircumflex looks like Aumlaut at 10% reductions.
;;
;; This could be fixed by:
;; (1) squashing ourselves; or
;; (2) fix the fontwide bounding box (if necessary) to account for these
;; characters, and change the line height where necessary in text cell formats
;; to account for the fontwide bounding box.
;;
;; (1) has the advantage that it's compatible with the bitmap font;
;; (2) has the advantage that it's compatible with hardcopy output, and what
;; the character should really look like, and the way it looks best, without
;; squeezing.


;; PROBLEM: review use of extra space for rasters -- should not be necessary
;; when fontwide information is stored properly -- finish def-font!

;; A simple earmark of the difference between Bitstream's SWISS-721 SWA and
;; Adobe's Helvetica (bitmaps) is the asterisk: Bitstream's is a 5-point star,
;; while Adobe's is a six-pointed.

;; Weight problem: even with the new squeeze-only policy, there are still
;; some problems with unevenness of stems.  At the scale you get after
;; 2 control-b (2X+10%), the "m" and the "a" are lighter than the rest of
;; the lowercase alphabetic characters.


;; PROBLEM: there's some inefficiency here around getting the bounding
;; box and making the character raster.  Several extra function calls
;; could be gotten rid of.  I'm not sure how much this impacts the
;; overall speed, though.  (MHD 7/12/93)







;;;; Interface to Kanji Outline Fonts


;;; We use the Bitstream Kanji outline font Hon Mincho Medium, which is their
;;; equivalent of the (Adobe) PostScript outline font known as Ryumin_L.  It is
;;; roughly the equivalent of a serifed roman font.  While we use a sans serif
;;; roman font in G2, we have traditionally used this style of Kanji font.  This
;;; style of font, then, is not the best match for our roman font, but does
;;; match best our previously released Kanji font ("Kanji16" and "Kanji24").

;;; The font is in Speedo format, and can be directly handled by the Speedo font
;;; raster image processor, which is part of our FONTRIP C library/module.

;;; Kanji codes (Gensym's name for all Asian font codes, including Japanese and
;;; Korean) can be converted to/from JIS codes, and the rows ("wards") and
;;; columns encoded therein.  The conversion functions are in CHARACTERS.

;;; The font as shipped by Bitstream is laid out as 42 different Speedo font
;;; files corresponding to wards in the JIS character set.  We provide here
;;; functions to convert from Gensym Kanji character codes into Bitstream Speedo
;;; Kanji font file name and character index.

;;; The macro `Set-jis-row-and-column' setf's the variables row-variable and
;;; column-variable to the row and column encoded by jis-code.

;;; The function `Get-jis-row-and-column' returns as first and second values the
;;; row and column, respectively, encoded by jis-code.

;;; Both of the two above functions return a 0-based row, and 0-based column.

(defmacro set-jis-row-and-column (jis-code row-variable column-variable)
  (avoiding-variable-capture (jis-code &aux high-byte low-byte)
    `(let ((,high-byte (ashf ,jis-code -8))
	   (,low-byte (logandf ,jis-code 255)))
      (setf ,row-variable (-f ,high-byte #x21))
      (setf ,column-variable (-f ,low-byte #x21)))))


(defun get-jis-row-and-column (jis-code)
  (let (row column)
    (set-jis-row-and-column jis-code row column)
    (values row column)))

;; See also also the related JIS - JIS Kuten section, below.  Maybe these should
;; be combined.  Or it should be flushed.

;; This was moved here from CHARACTERS just to get avoiding-variable-capture.



;;; `convert-kanji-code-to-font-file-name-and-index' ... a funcallable function
;;; used to map from a Gensym JIS character code (kanji-code) to the corresponding
;;; Bitstream Hon Mincho (minm_*) font.  Given a valid code, this returns two
;;; values: (1) a symbol whose print name is the (lowercase) name of the
;;; corresponding font file name, and (2) the char-id within that font
;;; corresponding to kanji-code.  If kanji-code is an invalid code, this returns
;;; nil.  The char-id is actually the the Shift-JIS code corresponding to the
;;; JIS code (corresponding to kanji-code).
;;;
;;; Note that the symbol returned has a lowercase print name, which is a bit
;;; unusual.
;;;
;;; Also note that this function does not cons at all. It's also very
;;; quick.
;;;
;;; Note that this function may handle kanji codes that are not strictly
;;; legal Gensym codes; it still should not be relied on other than to return
;;; codes corresponding to all legal Gensym kanji codes.
;;;
;;; See the Bitstream Speedo Kanji Processor documentation for information
;;; on Speedo Kanji fonts and their encoding.

(defvar kanji-row-to-font-file-name-mapping-vector
  (let* ((hex-digits "0123456789abcdef")
	 (initial-contents
	 (nconc

	   ;; Ward 0 -- Shift-JIS Ranges 0, 1, and 3
	   (list (format-symbol "minm_00"))
			 
;	   ;; JIS Wards 1 through 62 -- Shift-JIS Range 2
;	   (loop for lead-byte from #x81 to #x9f
;		 collect (format-symbol "minm_~(~x~)" lead-byte))

	   ;; Fixing ~( format bug - JED 8/24/93
	   ;; JIS Wards 1 through 62 -- Shift-JIS Range 2
	   (loop for lead-byte from #x81 to #x9f
		 collect (format-symbol "minm_~C~C"
					(char hex-digits (ashf lead-byte -4))
					(char hex-digits (logandf lead-byte 15)))) 

	   ;; JIS Wards 63 through 84 -- Shift-JIS Range 4
	   (loop for lead-byte from #xE0 to #xEA
		 collect (format-symbol "minm_~C~C"
					(char hex-digits (ashf lead-byte -4))
					(char hex-digits (logandf lead-byte 15))))

	   ;; Note: no files are provided for Range 5 or Range 6.
	   )))
    (make-array
      (length initial-contents)
      :initial-contents initial-contents)))

(defun convert-kanji-code-to-font-file-name-and-index (kanji-code)
  (cond
    ((=f kanji-code 0)
     nil)
    ((legal-gensym-jis-character-code-p kanji-code)
     (let ((jis-code (gensym-jis-to-jis kanji-code))
	   row column)
       (set-jis-row-and-column jis-code row column)
       (values
	 (svref kanji-row-to-font-file-name-mapping-vector
		(+f (halff row) 1))	; requires that halff has floor behavior
	 (jis-to-shift-jis jis-code))))))
	 


#+development
(decache-font-bitmaps)			; a good thing to do after loading this



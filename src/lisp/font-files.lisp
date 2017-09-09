;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module FONT-FILES: Saving/Loading Font Files

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark David


;; #+font-files is used in front of stuff that we would make non-development if
;; we had to load (.gf) font files again, as we did in G2 3.0.  This stuff
;; works fine as far as I know, but we never need to use it, so we don't need
;; to include the code in production.  (MHD 7/26/96)


#+font-files
(declare-forward-reference put-up-long-operation-notification function)
                                                ; to keep telewindows development
                                                ; compilation happy

;;;; Font Files 



;;; A `font file' has the format
;;;
;;;   F font-description-plist {character-description} E
;;;
;;; A `font description plist' is a plist with the following required
;;; properties (these make up the arguments to define-ab-font) 
;;;
;;;     font-name                  ; these are documented under def-ab-font
;;;     font-type
;;;     font-size
;;;     font-baseline
;;;     font-maximum-width
;;;     font-maximum-height
;;;
;;; and the following optional properties
;;; 
;;;     fixed-width-of-font     ; if present, a number, the fixed width for
;;;                             ;   each character in the font
;;;
;;;     fixed-bounding-box-of-font
;;;                             ; if present, a list of four elements:
;;;                             ;     bounding-box-x-offset, bounding-box-y-offset
;;;                             ;     bounding-box-width, bounding-box-height
;;;                             ;   that gives the bounding box for each character
;;;                             ;   in the font
;;;
;;; Other properties may be added in the future.  For example, a
;;; font-file-version property may have to added at a later date if this
;;; software changes but is to remain upwardly compatible font files written
;;; in an earlier version.  Also, addition information may one day be required
;;; about fonts than is now provided.
;;;
;;;   
;;; A `character description' has the format
;;; 
;;;    character-code		tagged font-file element (integer)	G2-internal codes
;;;    [character-set-width]	tagged font-file element (integer)	a text width
;;;    [bounding-box-x-offset	tagged font-file element (integer)	
;;;     bounding-box-y-offset	tagged font-file element (integer)
;;;     bounding-box-width	tagged font-file element (integer)
;;;     bounding-box-height]	tagged font-file element (integer)
;;;    n elements		each element is a small font-file	chunk of bits
;;;                               positive integer; 
;;;                               n = width * height
;;;                               with width & height are given
;;;                               by the fixed width & height, if any,
;;;                               or otherwise the bounding-box-width &
;;;                               height
;;;
;;; (making up the args, NOT listed, to add-character-description, q.v.)
;;;
;;; Character-code is a font file number.  All other numbers are "small font-
;;; file numbers" (see below).
;;; 
;;; Character-set-width is not provided when the fixed-width-of-font property
;;; is provided in the font description plist.
;;;
;;; Bounding-box-x-offset, bounding-box-y-offset, bounding-box-width, and
;;; bounding-box-height are not provided when the fixed-bounding-box-of-font
;;; property is provided in the font description plist.


;; Notes

;; At present, font files are only used for loading Kanji fonts.  The other
;; fonts in G2 are loaded as Lisp files at system load time.  Note that the
;; one Kanji font used presently, "KANJI16", takes advantage of both the
;; fixed-width-of-font and fixed-bounding-box-of-font properties.

;; You might want to save a character per character description in the font
;; files for fonts requiring 11 bits or less to represent all character codes,
;; and you could do that by having a property to say to do that in the font
;; description; I didn't do that now, because I can't use that, since we're
;; writing Kanji fonts, which need more than 11 bits (i.e., 17 bits) per
;; character code.








;;; `Convert-character-bitmap-to-character-rectangle-array' converts character-bitmap,
;;; delimited by width? and height? if specified, into a character-rectangle array.
;;; This function leaves all bits cleared (0) in character-bitmap (in the area
;;; described by width? and height?, if specified).

#+font-files
(defun convert-character-bitmap-to-run-length-encoded-character-byte-vector
       (character-bitmap &optional width? height?)
  (loop with number-of-columns
	  = (or width? (character-bitmap-width character-bitmap))
	with number-of-rows
	  = (or height? (character-bitmap-height character-bitmap))
	for y from 0 below number-of-rows
	nconc
	  (loop with encoding-for-this-row = nil
		with count-of-runs = 0
		with x-at-beginning-of-run? = nil
		for x from 0 below number-of-columns
		do (cond
		     (x-at-beginning-of-run?
		      (when (=f (character-bitmap-value character-bitmap x y) 0)
			(setq encoding-for-this-row
			      (nconc
				encoding-for-this-row
				(gensym-list
				  x-at-beginning-of-run?
				  (-f x x-at-beginning-of-run?))))
			(setq x-at-beginning-of-run? nil)))
		     ((=f (character-bitmap-value character-bitmap x y) 1)
		      (incff count-of-runs)
		      (setq x-at-beginning-of-run? x)))
		finally
		  (when x-at-beginning-of-run?
		    (setq encoding-for-this-row
			  (nconc
			    encoding-for-this-row
			    (gensym-list
			      x-at-beginning-of-run?
			      (-f number-of-columns x-at-beginning-of-run?)))))
		  (return
		    (gensym-cons
		      count-of-runs
		      encoding-for-this-row)))
	  into run-length-encoding-lists using gensym-cons
	finally
	  (return
	    (let ((character-byte-vector
		    (allocate-character-byte-vector
		      (length run-length-encoding-lists))))
	      (loop for byte in run-length-encoding-lists
		    as i from 0
		    do (setf (character-byte-vector-ref character-byte-vector i) byte))
	      (reclaim-gensym-list run-length-encoding-lists)
	      character-byte-vector))))



#+(and development font-files)
(defun print-character-byte-vector (byte-vector width height)	; run-length encoded
  (loop with i = 0
	with character-bitmap = (allocate-character-bitmap width height)
	for y from 0 below height
	do (loop with number-of-pairs = (character-byte-vector-ref byte-vector i)
		 repeat number-of-pairs
		 do (let* ((x0 (character-byte-vector-ref byte-vector (incff i)))
			   (x-run-length (character-byte-vector-ref byte-vector (incff i))))
		      (fill-rectangle-in-character-bitmap
			character-bitmap 1 x0 y (+f x0 x-run-length) (+f y 1))))
	   (incff i)
	finally
	  (print-character-bitmap character-bitmap)
	  ;; note: character-bitmap is now garbage!
	  ))






#+(and development font-files)
(defun kcd (&optional (code #x4444))
  (get-kanji-character-description-if-any
    code (ab-font-character-description-table (ab-font 'hangul16))))





#+(and development font-files)
(defun reload-k16 (&optional compile?)
  (loop for i from 1 to 7
	as binary-pathname
	   = (format nil "ok:ab.dev;kanji16-~d.xld" i)
	do (if compile?
	       (compile-file
		 (format nil "ma:>ab>kanji16-~d.lisp" i)
		 :output-file binary-pathname))
	   (load binary-pathname)))









;;;; Reading Font Files





;;; `Reading-font-file' ... opens gensym-pathname-or-namestring, sets up an
;;; environment in which to read from it, and closes it.

#+font-files
(defvar next-character-for-font-file?)

#+font-files
(defvar number-of-font-file-characters-so-far?)	; initially 0 iff displaying progress

#+font-files
(defvar read-font-file-stream)

#+font-files
(defvar name-text-string-for-font-file-being-read)

#+font-files
(defmacro reading-font-file ((gensym-pathname-or-namestring) &body body)
  (avoiding-variable-capture (gensym-pathname-or-namestring)
    `(let* ((read-font-file-stream-internal nil)
	    (truename? nil)
	    namestring-for-font-file-being-read
	    name-text-string-for-font-file-being-read)
       (handling-gensym-file-errors
	 (unwind-protect
	     (cond
	       ((null (setq read-font-file-stream-internal
			    (g2-stream-open-for-input
			      (gensym-namestring ,gensym-pathname-or-namestring))))
		(notify-user-if-possible
		  "Could not open font save file ~s for input!"
		  (gensym-namestring ,gensym-pathname-or-namestring)))
	       (t
		(let* ((read-font-file-stream read-font-file-stream-internal)
		       (number-of-font-file-characters-so-far? nil)
		       (next-character-for-font-file? nil)
		       (read-font-file-buffer-index 0)
		       (read-font-file-buffer-length 0))
		  (setq truename? (gensym-truename ,gensym-pathname-or-namestring))
		  (setq namestring-for-font-file-being-read
			(gensym-namestring truename?))
		  (setq name-text-string-for-font-file-being-read
			(import-text-string
			  namestring-for-font-file-being-read
			  'GENSYM-PATHNAME-NAMESTRING))
		  . ,body)))
	   (when truename?
	     (reclaim-gensym-pathname truename?)
	     (reclaim-text-string namestring-for-font-file-being-read)
	     (reclaim-text-string name-text-string-for-font-file-being-read))
	   (if read-font-file-stream-internal
	       (g2-stream-close read-font-file-stream-internal)))))))





;;; `Read-next-char-for-font-file' ...

#+font-files
(def-system-variable read-font-file-buffer FONT-FILES ; must be a simple Lisp string
  (:funcall make-string 2048))

#+font-files
(defvar read-font-file-buffer-index)

#+font-files
(defvar read-font-file-buffer-length)		; constant?

#+font-files
(defmacro read-next-char-for-font-file ()
  `(if (<f read-font-file-buffer-index read-font-file-buffer-length)
       (let ((new-char 
	       (schar read-font-file-buffer read-font-file-buffer-index)))
	 (when number-of-font-file-characters-so-far?
	   (incff number-of-font-file-characters-so-far?))
	 (incff read-font-file-buffer-index)
	 new-char)
       (read-next-char-for-font-file-from-refilled-buffer)))


#+font-files
(defun-simple read-next-char-for-font-file-from-refilled-buffer ()
  (let ((number-of-characters-in-buffer?
	  (g2-stream-read-into-buffer
	    read-font-file-buffer
	    (length-of-simple-string read-font-file-buffer)
	    read-font-file-stream)))
    (cond ((and number-of-characters-in-buffer?
		(pluspf number-of-characters-in-buffer?))
	   (when number-of-font-file-characters-so-far?
	     (incff number-of-font-file-characters-so-far?))
	   (setq read-font-file-buffer-length number-of-characters-in-buffer?)
	   (setq read-font-file-buffer-index 1)
	   (schar read-font-file-buffer 0))
	  (t
	   (abort-on-bad-font-file)))))



;;; `Read-char-for-font-file' ...

#+font-files
(defmacro read-char-for-font-file ()
  `(if next-character-for-font-file?
       (prog1
	 next-character-for-font-file?
	 (setq next-character-for-font-file? nil))
       (read-next-char-for-font-file)))


#+font-files
(defun read-element-for-font-file-after-newline ()
  ;; If there were a progress display to update, it should be done here.
  (read-element-for-font-file))


#+font-files
(defun abort-on-bad-font-file
       (&optional problem-character-unless-eof? case-number?)
  (let ((problem
	  (if problem-character-unless-eof?
	      (tformat-text-string
		"Bad character ~A"
		problem-character-unless-eof?)
	      "End-of-file unexpectedly"))
	(case-text-string?
	  (if case-number? (tformat-text-string "[Case ~d.]  " case-number?))))
    (notify-user-if-possible
      "~A encountered while reading.  ~A~S is not a valid Font File."
      problem (or case-text-string? "")
      name-text-string-for-font-file-being-read)
    (if problem-character-unless-eof?
	(reclaim-text-string problem))
    (if case-text-string?
	(reclaim-text-string case-text-string?))
    (abort)))





#+font-files
(defun read-character-sequence-for-font-file (number-of-characters)
  (loop with gensym-string = (obtain-simple-gensym-string number-of-characters)
	with i = 0
	with character
	while (<f i number-of-characters)
	do (case (setq character (read-char-for-font-file))
	     (#\\
	      (let ((next-character (read-next-char-for-font-file)))
		(cond
		  ((not (simple-character-p next-character))
		   (loop until (eql (read-next-char-for-font-file) #\\)))
		  (t (setf (schar gensym-string i) #\\)
		     (incff i)
		     (unless (and (=f i number-of-characters)
				  (eql next-character #\\))
		       (setq next-character-for-font-file? next-character))))))
	     (t (setf (schar gensym-string i) character)
		(incff i)))
	finally
	  (return gensym-string)))

#+font-files
(defun read-element-for-font-file ()
  (let* ((character (read-char-for-font-file))
	 (weight? (if (not (upper-case-p character))
		      (digit-char-p character 32))))
    (if weight?
	(loop as value-so-far
		 = weight?
		 then (+f (ashf value-so-far 5) weight?)
	      do (setq character (read-next-char-for-font-file))
	      while (and (not (eql character #\+))	; most common case
			 (setq weight?
			       (if (not (upper-case-p character))
				   (digit-char-p character 32))))
	      when (not (<=f value-so-far
			     most-positive-fixnum-ash-minus-5-minus-1))
		return (abort-on-bad-font-file character 1)
	      finally
		(return
		  (case character
		    (#\+ value-so-far)
		    (#\- (-f value-so-far))
		    ((#\` #\,)
		     (intern-gensym-string
		       (read-character-sequence-for-font-file value-so-far)
		       (if (eql character #\,) keyword-package-1)))
		    (#\S
		     (read-character-sequence-for-font-file value-so-far))
		    (t (abort-on-bad-font-file character 2)))))
	(case character
	  (#\Z 0)
	  (#\N nil)
	  (#\T t)
	  (#\L (loop with l = (gensym-cons-macro (read-element-for-font-file) nil)
		     with l-tail = l
		     do (case (setq character (read-char-for-font-file))
			  (#\R (return l))
			  (#\. (setf (cdr l-tail) (read-element-for-font-file))
			       (return l)))
			(setq next-character-for-font-file? character)
			(setq l-tail
			      (setf (cdr l-tail)
				    (gensym-cons-macro
				      (read-element-for-font-file) nil)))))
	  (#\space (read-element-for-font-file))	; maybe iterate?
	  (#\newline (read-element-for-font-file-after-newline))
	  (#\; (loop until (eql (read-next-char-for-font-file) #\newline))
						; limit by count?
	       ; "How can this possibly work?! ML 4/9/91" -- ml's comment for KB load
	       (read-element-for-font-file-after-newline))
	  (#\E nil)
	  (t
	   (if (member character		; linebreak char?
		       '#.(remove-duplicates
			    '(#.char-linefeed #.char-return
			      #.(code-char 12) #.(code-char 10))))

	       (read-element-for-font-file)
	       (abort-on-bad-font-file character 3)))))))







;;; While reading, fixed-width-of-font-being-read? is bound, and it is set after
;;; reading the font description at the beginning of the file to either nil or
;;; fixed width, as appropriate.  If it is non-nil, then the character set
;;; width field of the character descriptions in the file will not be found, and
;;; the value of fixed-width-of-font-being-read? should be substituted.

#+font-files
(defvar fixed-width-of-font-being-read?)



;;; While reading, fixed-bounding-box-of-font-being-read? is bound, and it is
;;; set after reading the font description at the beginning of the file to either
;;; nil or fixed bounding-box, a gensym list ..., as appropriate.  ...

#+font-files
(defvar fixed-bounding-box-of-font-being-read?)




#+font-files
(defmacro convert-char-to-font-file-small-fixnum-integer (char)
  `(-f (char-code ,char) 32))

#+font-files
(defmacro read-small-positive-fixnum-for-font-file ()
  '(convert-char-to-font-file-small-fixnum-integer
     (read-char-for-font-file)))




;;; Skip-bits-in-character-bitmap ... advances x-variable and y-variable
;;; by number-of-bits.  This is only used for skipping over past whitespace
;;; in character bitmaps, at present.  This always leaves x-variable less
;;; than width.  Notice that this can leave y-variable greater than height,
;;; since it does not know the maximum height of the character bitmap being
;;; written.

#+font-files
(defmacro skip-bits-in-character-bitmap
	  (number-of-bits width x-variable y-variable)
  (avoiding-variable-capture (number-of-bits width)
    `(progn
       (incff ,x-variable ,number-of-bits)
       (when (>=f ,x-variable ,width)
	 (loop do (setq ,x-variable (-f ,x-variable ,width))
		  (incff ,y-variable)
	       until (<f ,x-variable ,width))))))



;;; Read-character-description adds the next character description in the current
;;; font save file, unless the end of the file has been reached, in which case
;;; this just returns nil instead.

;;; If character-code-mapping-function? is supplied, it should be a function of
;;; one argument, which maps the character code found with the character
;;; description to another one to be used in instead.  This is used, for example,
;;; when reading the Hangul (Korean) font, where we must map the codes elsewhere
;;; so as not to conflict with Kanji (Japanese) codes.

#+font-files
(defvar debugging-read-character-description? nil)

#+font-files
(defun read-character-description
       (&optional character-code-mapping-function?
	font-from-which-to-clone-set-widths?)
  (let ((character-code? (read-element-for-font-file))
	(width (if fixed-bounding-box-of-font-being-read?
		   (third fixed-bounding-box-of-font-being-read?)))
	(height (if fixed-bounding-box-of-font-being-read?
		    (fourth fixed-bounding-box-of-font-being-read?)))
	set-width x-offset y-offset)
    (if character-code?
	(add-character-description
	  (if character-code-mapping-function?
	      (funcall character-code-mapping-function? character-code?)
	      character-code?)
	  (unless fixed-width-of-font-being-read?	; character-set-width
	    (setq set-width (read-element-for-font-file))
	    (or (if font-from-which-to-clone-set-widths?
		    (let ((character-description?
			    (get-non-kanji-character-description-if-any
			      character-code?
			      (ab-font-character-description-table
				font-from-which-to-clone-set-widths?))))
		      (if character-description?
			  (character-set-width character-description?))))
		(text-width-to-x		; shouldn't this slot hold a text width?!
		  set-width)))
	  (unless fixed-bounding-box-of-font-being-read?
	    (setq x-offset
		  (read-element-for-font-file)))	; x-offset
	  (unless fixed-bounding-box-of-font-being-read?
	    (setq y-offset
		  (read-element-for-font-file))) ; y-offset
	  (unless fixed-bounding-box-of-font-being-read?
	    (setq width (read-element-for-font-file)))
	  (unless fixed-bounding-box-of-font-being-read?
	    (setq height (read-element-for-font-file)))
	  (loop with character-bitmap
		  = (allocate-character-bitmap width height)
		with total-number-of-characters-needed
		  = (ceilingf
		      (*f width height)
		      max-small-font-file-fixnum-integer-length)
;		with xxx
;		  = (cerror ""
;			    "Code: ~d; Setwidth: ~d; Xoffset: ~d; Yoffset: ~d; Width: ~d; Height: ~d; Total chars: ~d"
;			    character-code?
;			    x-offset y-offset width height
;			    total-number-of-characters-needed
;			    )
		with y = 0
		with x = 0
		with bits 
		repeat total-number-of-characters-needed
		do (setq bits (read-small-positive-fixnum-for-font-file))
		   (if (=f bits 0)		; optimization -- see note below
		       (skip-bits-in-character-bitmap
			 max-small-font-file-fixnum-integer-length
			 width x y)
		       (loop for index
				 from 0
				 below max-small-font-file-fixnum-integer-length
			     when
			       ;; Test if the INDEXth bit in BITS is set by
			       ;; logand'ing it with a bitmask containing just
			       ;; the INDEXth bit set.  If it is not zero, i.e.,
			       ;; is 1, that bit is set in BITS.  To do this
			       ;; test, we have (set up at read time) an array
			       ;; A[0..N-1] of bitmasks such that A[I] = (ash 1
			       ;; i), when N is the number of bits in bits.
			       ;; E.g., for N = 6, A contains 1, 2, 4, 8, 16,
			       ;; and 32 at indexes 0, 1, 2, 3, 4, 5, and 6,
			       ;; respectively.  (MHD 4/20/92) An alternative
			       ;; test is: (LOGBITPF INDEX BITS)
			       (not (=f (logandf bits
						 (svref '#.(convert-list-to-simple-vector
							     (loop for i from 0
									 below max-small-font-file-fixnum-integer-length
								   collect (ash 1 i)))
							index))
					0))
			       do (setf (character-bitmap-value character-bitmap x y) 1)
			     do (incff x)
			     when  (=f x width)
			       do (incff y)
				  (setq x 0)))
		finally
		  (when debugging-read-character-description?
		    (format t "~%character code: ~d" character-code?)
		    (print-character-bitmap character-bitmap))
		  (return character-bitmap))))))


;; Note: on the Lisp Machines, adding the (=f bits 0) optimization only saved
;; a few percentage points.  Two runs of (read-ab-font-file "ma:>ab>kanji16.gf")
;; with the optimization took 64.7 and 64.2 seconds each, while two runs without
;; the optimization took 66.1 and 66.5 seconds each.  (MHD 4/4/92)



;;; Preview-font-file-bits can be used in development to print out on the
;;; terminal the ones and zeroes corresponding to a string of characters
;;; in a font file representing the bits of a character.

#+(and development font-files)
(defun preview-font-file-bits (string &optional (row-width 9))
  (terpri)
  (loop with zz = 0
	for i from 0 below (length string) as char = (char string i)
	as xx = (format nil "~6,,,'0a" (reverse (format nil "~2r" (- (char-code char) 32 ))))
	do (loop for i from 0 below (length xx)
		 do (write-char (char xx i))
		 when (=f (incf zz) row-width)
		   do (terpri) (setq zz 0))))



;;; Read-ab-font-file reads in a font that was written in KB-save style.  IF
;;; font-name-to-use?  is nil, the font name is derived from the font file; if it is
;;; specified, it will override whatever name is given in the font file.  This is used,
;;; for example, for Asian fonts (Kanji and Hangul), where both the font KANJI16 and
;;; HANGUL16 want to use the same font name, KANJI16.

;;; If always-redefine?  is true, this always redefines (ab-font <font being read>).
;;; Otherwise, this leaves an existing definition as is and merely fills in the character
;;; data.  Leaving an existing font, the default, is used, for example, when loading
;;; Hangul or Kanji fonts, which have to share the same font structure for different
;;; characters.

;;; Character-code-mapping-function? is passed along to read-character-description;
;;; see its documentation there.

#+font-files
(defun-allowing-unwind read-ab-font-file
		       (pathname
			 &optional font-name-to-use? always-redefine?
			 character-code-mapping-function?
			 font-from-which-to-clone-set-widths?)
  (reading-font-file (pathname)
    (cond
      ((not (eql (read-char-for-font-file) #\F))
       (notify-user-if-possible
	 "~S is not a valid font file; it does not start with F!"
	 (gensym-namestring pathname)))
      (t
       (let (fixed-width-of-font-being-read?
	     fixed-bounding-box-of-font-being-read?)
	 (let* ((font-description-plist (read-element-for-font-file)))
	   (setq fixed-width-of-font-being-read?
		 (getf font-description-plist 'fixed-width-of-font))
	   (setq fixed-bounding-box-of-font-being-read?
		 (getf font-description-plist 'fixed-bounding-box-of-font))
	   (let ((font-name
		   (or font-name-to-use?
		       (getf font-description-plist 'font-name))))
	     (if (or always-redefine?
		     (null (ab-font font-name)))
		 (define-ab-font
		   font-name
		   (getf font-description-plist 'font-type)
		   (getf font-description-plist 'font-size)
		   (getf font-description-plist 'font-baseline)
		   (getf font-description-plist 'font-maximum-width)
		   (getf font-description-plist 'font-maximum-height)
		   fixed-width-of-font-being-read?
		   fixed-bounding-box-of-font-being-read?)
		 (set-current-ab-font font-name)))
	   (loop for i from 0
		 ;; commented out today -- get back to this! (MHD 12/18/91)
;		 as debugging-read-character-description?
;		   = (temporary-progn (12 15 91)	; temporary -- for debugging! (MHD 12/4/91)
;		       (<f i 100))
		 while (read-character-description
			 character-code-mapping-function?
			 font-from-which-to-clone-set-widths?))    
	   (reclaim-gensym-list font-description-plist)))))))

;; This hardly does any error checking at all!  If an ascii file begins with
;; F, this takes the risk of assuming that it is a valid font file!  Improve!


;; It takes about 100 seconds to read the new KANJI16 font files on Explorer II+
;; Antimony from Massachusetts.
;;
;; It takes about 120 seconds to read the old KANJI16 font files on the same
;; machine.










;;; `Asian-font-reading-information' ... is an a-list.  Each entry is if the
;;; form
;;;
;;;    (asian-font-name  default-filename-variable
;;;       keyword  font-name  mapping-function?)
;;;
;;; This is used by read-asian-font-file; see below.

(defparameter asian-font-reading-information
  '((hangul16 hangul16-font-filename "hangul16-font" kanji16 ksc-to-gensym-ksc)
    (hangul24 hangul24-font-filename "hangul24-font" kanji24 ksc-to-gensym-ksc)
    ;; hangul gb bitmap data files:
    (hangul hangul_*-font-filename "hangul_fontfile" hangul nil)
    ;; Hangul TTF (TrueType Font) font file:  (Goes best with Microsoft's
    ;;   gulim, which MS provides free for end users)
    (hangulttf hangulttf-font-filename "hangulttf_fontfile" hangul nil)
    (chinesettf chinesettf-font-filename "chinesettf_fontfile" chinese nil)
    (kanji16 kanji16-font-filename "kanji16-font" kanji16 nil)
    (kanji24 kanji24-font-filename "kanji24-font" kanji24 nil)
    ;; kanji gb bitmap data files:
    (kanji kanji_*-font-filename "kanji_fontfile" kanji nil)
    (minm minm_*-font-filename "minm_fontfile" minm nil)))




;;; Read-asian-font-file reads in the font file associated with asian-font-name.
;;; At present, asian-font-name must be one of kanji16, kanji24, hangul16, or
;;; hangul24.  This takes care of merging in with the default pathname and handling
;;; keyword arguments, or environment variables, to override the defaults.  These
;;; are always of the form <asian-font-name>-font.  For example, the following
;;; overrides the default pathname for the hangul24 font when starting telewindows:
;;;
;;;     tw <host> <address> -hangul24-font /home/mhd/my-hangul-24.gf

;;; Read-asian-font-file uses the a-list asian-font-reading-information to associate
;;; asian-font-name with information needed to find the font file and read it in
;;; correctly.

;;; If put-up-long-notification? is true, which it may only be if running G2, this
;;; calls put-up-long-operation-notification to immediately put up a notification
;;; message.  This is to be used in a do-long-operation-with-notification context,
;;; q.v., in which a message has been set up announcing the loading of this font,
;;; and possibly others.

;;; Telewindows-gensym-window? may be nil, which it must always be if called from
;;; a G2 process, or a gensym window upon which to post progress notifications.

;;; Unless always-read-in-font-data? is true, this skips loading the font if it
;;; determines that the font has been read in already, using asian-font-read-in-
;;; already-p.

#+font-files
(defun read-asian-font-file (asian-font-name
			     &optional put-up-long-notification?
			     always-read-in-font-data?)
  (gensym-dstruct-bind
    ((nil nil font-name mapping-function?)
     (cdr (assq asian-font-name asian-font-reading-information)))
    (let* ((font-filename-from-file-system
	     (get-asian-font-file-name asian-font-name))
	   (font-filename-for-user
	     (import-text-string
	       font-filename-from-file-system
	       'GENSYM-PATHNAME-NAMESTRING)))
      (unless (if always-read-in-font-data?
		  nil
		  (asian-font-read-in-already-p asian-font-name))
	(when put-up-long-notification?
	  (put-up-long-operation-notification))
	(cond
	  ((g2-stream-probe-file-for-read font-filename-from-file-system)
	   (let ((listed-text-string
		   (gensym-list
		     (tformat-text-string
		       "Reading ~a font from ~s."
		       asian-font-name font-filename-for-user))))
	     ;; leave out as unnecessary, and acompilation issue, for now:
	     ;; (MHD 10/17/94)
	     (notify-user-if-possible "~a" (first listed-text-string))
	     (reclaim-text-string (first listed-text-string))
	     (reclaim-gensym-list listed-text-string))
	   (read-ab-font-file
	     font-filename-from-file-system
	     font-name nil mapping-function?))
	  (t (notify-user-if-possible
	       "The ~a font file, ~s, could not be accessed."	; improve wording?!
	       asian-font-name font-filename-for-user))))
      (reclaim-text-string font-filename-for-user))))


#+development
(defparameter fonts-override-path-name-string? nil) ; e.g., #w"/gensym/ut/fonts-50r3/"

(defun get-font-file-directory-pathname ()
  (let* ((filename-from-launch-environment?
	   (or #+development
	       (copy-if-text-string fonts-override-path-name-string?)
	       (copy-if-text-string
		 (get-command-line-keyword-argument #w"fonts"))
	       (get-gensym-environment-variable #w"FONTS")))
	 (pathname
	   (if filename-from-launch-environment?
	       (or (get-new-directory-pathname-dwim
		     filename-from-launch-environment?)
		   (make-empty-gensym-pathname))
	       (gensym-make-pathname :directory '(:relative #w"fonts")))))
    (when filename-from-launch-environment?
      (reclaim-text-string filename-from-launch-environment?))
    pathname))

(defun-simple get-asian-font-file-name (asian-font-name)
  (gensym-dstruct-bind
      ((default-filename-variable keyword)
       (cdr (assq asian-font-name asian-font-reading-information)))
    (get-font-file-name
      (or (get-command-line-keyword-argument keyword)
	  (let ((keyword-as-uppercase-string
		  (copy-text-string-with-case-conversion keyword :all)))
	    (prog1 (get-gensym-environment-variable keyword-as-uppercase-string)
	      (reclaim-text-string keyword-as-uppercase-string)))
	  (symbol-value default-filename-variable)))))



;;; The function `get-font-file-name' takes a symbol or a text string.  If it's
;;; a string, no file-type information (e.g., ".ttf") is added of any kind, and
;;; it is not reclaimed or incorporated by this function.  If it's a symbol, the
;;; print name is is downcased, and ".ttf", the file-type for truetype fonts, is
;;; appended.
;;;
;;; This returns a new text string, a namestring based on merging in the
;;; argument with font pathnmame defaults.

(defun-simple get-font-file-name (basic-font-file-name)
  (let* ((basic-namestring
	   (if (symbolp basic-font-file-name)
	       (tformat-text-string "~(~a~).ttf" basic-font-file-name)
	       (copy-text-string basic-font-file-name)))
	 (font-file-directory-pathname? (get-font-file-directory-pathname))
	 (series			; every element is a fresh text string or
	   (nconc			;   gensym pathname, to be reclaimed
	     (gensym-list basic-namestring)
	     (if font-file-directory-pathname?
		 (gensym-list font-file-directory-pathname?))
	     (if process-specific-system-pathname
		 (gensym-list
		   (copy-gensym-pathname
		     process-specific-system-pathname)))))
	 (gensym-pathname
	   (prog1 (merge-series-of-pathnames series)
	     (loop for thing in series
		   do (cond
			((gensym-pathname-p thing)
			 (reclaim-gensym-pathname thing))
			((text-string-p thing)
			 (reclaim-text-string thing))))
	     (reclaim-gensym-list series))))
    (prog1 (gensym-namestring gensym-pathname)
      (reclaim-gensym-pathname gensym-pathname))))

;; Note: the conversion from the pathname to the namestring should not be
;; necessary, but experiments prove that it is.  Get JH to fix or justify! (MHD
;; 6/21/94)
;; jh, 8/29/94.  I think this conversion problem will go away now that the call
;; to gensym-make-pathname uses a structured :directory component (i.e., a
;; list), since the lack of a :relative element in the directory list from the
;; previous (gensym-make-pathname :directory "fonts") could cause merge
;; problems.  Besides, the string "fonts" did not work at all in VMS, since the
;; VMS file system needs something like "fonts.dir" to be a valid directory as
;; file, or "[.fonts]" to be a valid relative directory, and neither would work
;; in UNIX anyway.  See copy-directory-components-from-directory-string in
;; PATHNAMES for a description of what happens when a string is given as the
;; :directory component of gensym-make-pathname.





;;;; Writing Font Files



#+(and development font-files)
(progn



(defvar write-font-file-stream)

(defvar length-of-saved-font-file-line-so-far)

(defparameter number-of-characters-beyond-which-to-start-a-new-saved-font-file-line 60)

(defparameter number-of-characters-at-which-to-break-a-font-file-character-sequence 75)


;;; `Writing-font-file' ... opens gensym-pathname-or-namestring for output, sets
;;; up an environment in which to write to it, and closes it.

(defmacro writing-font-file ((gensym-pathname-or-namestring) &body body)
  `(let* ((write-font-file-stream-internal nil))
     (handling-gensym-file-errors
       (unwind-protect
	   (cond
	     ((null (setq write-font-file-stream-internal
			  (g2-stream-open-for-output
			    (gensym-namestring ,gensym-pathname-or-namestring))))
	      (notify-user-if-possible
		"Could not open Font File ~s for output!"
		(gensym-namestring pathname)))
	     (t
	      (let* ((write-font-file-stream write-font-file-stream-internal)
		     (number-of-font-file-characters-so-far? nil)
		     (length-of-saved-font-file-line-so-far 0)
		     (next-character-for-font-file? nil))
		. ,body)))
	 (if write-font-file-stream-internal
	     (g2-stream-close write-font-file-stream-internal))))))




(defmacro start-new-font-file-line-if-appropriate ()
  `(if (>f length-of-saved-font-file-line-so-far
	   number-of-characters-beyond-which-to-start-a-new-saved-font-file-line)
       (start-new-font-file-line)))


(defmacro write-char-for-font-file (character)
  `(progn
     (incff length-of-saved-font-file-line-so-far)
     (g2-stream-write-char ,character write-font-file-stream)))

(defun start-new-font-file-line ()
  ; (incff number-of-font-file-lines-so-far) ; for file progress?
  (setq length-of-saved-font-file-line-so-far 0)
  (g2-stream-write-char #\newline write-font-file-stream))







(defun write-fixnum-for-font-file (fixnum)
  (start-new-font-file-line-if-appropriate)		; sometimes redundant
  (let* ((negative? (<f fixnum 0))
	 (non-negative-fixnum
	   (if negative? (-f fixnum) fixnum)))
    (write-fixnum-digits-for-font-file non-negative-fixnum)
    (write-char-for-font-file (if negative? '#\- '#\+))))


(defmacro write-non-negative-fixnum-for-font-file (non-negative-fixnum)
  `(write-fixnum-digits-for-font-file ,non-negative-fixnum))


(defun write-fixnum-digits-for-font-file (non-negative-fixnum)
  (let* ((digit (logandf non-negative-fixnum 31))
	 (character (digit-char digit 32)))
    (if (>f non-negative-fixnum 31)
	(write-fixnum-digits-for-font-file (ashf non-negative-fixnum -5)))
    (incff length-of-saved-font-file-line-so-far)
    (g2-stream-write-char
      (if (upper-case-p character) (char-downcase character) character)
      write-font-file-stream)))



(defun write-small-positive-fixnum-for-font-file (x)
  (if (>f (integer-length x) max-small-font-file-fixnum-integer-length)
      (error "~d is too big a number (~d bits)!" x (integer-length x))
      (progn
	(incff length-of-saved-font-file-line-so-far)
	(g2-stream-write-char
	  (code-char (+f x 32))
	  write-font-file-stream))))		; NOTE: must be ASCII
  




(defun write-character-sequence-for-font-file (prefix-character string)  
  (let ((number-of-chars (length string)))
    (if (>f (+f length-of-saved-font-file-line-so-far number-of-chars 3)  ; 3 for count-and-char??
	    number-of-characters-at-which-to-break-a-font-file-character-sequence)
	(start-new-font-file-line))
    (write-non-negative-fixnum-for-font-file number-of-chars)
    (write-char-for-font-file prefix-character)
    (loop as i from 0 below number-of-chars
	  as char = (charw string i)
	  when (>=f length-of-saved-font-file-line-so-far
		    number-of-characters-at-which-to-break-a-font-file-character-sequence)
	    do (write-char-for-font-file #\\)
	       (start-new-font-file-line)
	       (write-char-for-font-file #\\)
	  do (write-char-for-font-file char)
	  finally
	    (if (and (>f number-of-chars 0) (eql char #\\))  ; if the last char is #\\,
		(write-char-for-font-file #\\)))))



(defun write-symbol-for-font-file (symbol)
  (start-new-font-file-line-if-appropriate)
  (let* ((name (symbol-name symbol))
	 (package? (symbol-package symbol)))
    (write-character-sequence-for-font-file
      (cond
	((eq package? keyword-package-1)
	 #\,)
	((or (eq package? *package*)		; in AB package
	     (eq package? lisp-package-1)	; in LISP package
	     (find-symbol name))		; in "Global" package (?)
	 #\`)
	(t
	 (error
	   (if (null package?)
	       "Uninterned symbol ~S encountered while trying to save Font File" 
	       "Symbol ~S from a foreign package encountered while trying to save Font File")
	   symbol)))
      name)))

(defun write-element-for-font-file (x)
  (start-new-font-file-line-if-appropriate)
  (cond
    ((fixnump x)
     (if (=f x 0)
	 (write-char-for-font-file '#\Z)
	 (write-fixnum-for-font-file x)))
    ((symbolp x)
     (cond
       ((null x)
	(write-char-for-font-file '#\N))
       ((eq x 't)
	(write-char-for-font-file '#\T))
       (t (write-symbol-for-font-file x))))
    ((consp x)     
     (write-char-for-font-file '#\L)
     (loop for y = x then (cdr y)
	   until (atom y)
	   do (write-element-for-font-file (car y))
	   finally
	     (cond
	       ((not (null y))
		(write-char-for-font-file '#\.)
		(write-element-for-font-file y))
	       (t (write-char-for-font-file '#\R)))))
    ((gensym-string-p x)
     (write-character-sequence-for-font-file '#\S x))
    (t
     (error
       "Illegal object ~S encountered while trying to save FONT-FILE"
       x))))


) ; end of #+(and development font-files) progn





;;;; Iterating over Kanji Character Descriptions



#+(and development font-files)
(defmacro do-kanji-character-descriptions
	  ((character-description-var kanji-ab-font) &body body)
  `(loop with character-description-table
	   = (ab-font-character-description-table ,kanji-ab-font)
	 for i from 0 below #.(kanji-font-cache-vector-length)
	 do (loop for l on (svref character-description-table i)
			by 'cddr
		  as kanji-code = (car l)
		  unless (=f kanji-code 0)
		    do (let ((,character-description-var (cadr l)))
			 . ,body))))

#+(and development font-files)
(defun average-number-of-rectangles-in-kanji16 ()
  (let* ((number-of-characters-so-far 0)
	 (number-of-rectangles-so-far 0))
    (do-kanji-character-descriptions (cd (ab-font 'kanji16))
      (incf number-of-characters-so-far)
      (incf number-of-rectangles-so-far
	    (length (character-rectangle-array cd))))
    (round (/ (float number-of-rectangles-so-far)
	      number-of-characters-so-far))))

;; Result: 19
;; (MHD 4/19/91)




#+(and development font-files)
(defun investigate-schemes (&optional (verbose? t))
  (let* ((words-per-bitmap (ceiling (* 16 16) 32))
	 (character-bitmap (allocate-character-bitmap 16 16))
	 (total-rectangle-words 0)
	 (total-bitmap-words 0)
	 (total-vector-words 0)
	 (maximum-number-of-rectangles 0)
	 (maximum-number-of-bytes 0)
	 (minimum-number-of-rectangles 100000)
	 (minimum-number-of-bytes 100000)
	 (rectangle-winners 0)
	 (bitmap-winners 0)
	 (vector-winners 0))
    (do-kanji-character-descriptions (cd (ab-font 'kanji16))
      (setq character-bitmap
	    (convert-character-rectangle-array-to-character-bitmap cd))
      (let* ((character-byte-vector	      
	       (convert-character-bitmap-to-run-length-encoded-character-byte-vector
		 character-bitmap 16 16))
	     (words-per-rectangle-array
	       (length (character-rectangle-array cd)))
	     (words-per-byte-vector
	       (ceiling (character-byte-vector-length character-byte-vector)
			4)))
	(setq maximum-number-of-rectangles
	      (max maximum-number-of-rectangles
		   (length (character-rectangle-array cd))))
	(setq minimum-number-of-rectangles
	      (min minimum-number-of-rectangles
		   (length (character-rectangle-array cd))))
	(setq maximum-number-of-bytes
	      (max maximum-number-of-bytes
		   (length character-byte-vector)))
	(setq minimum-number-of-bytes
	      (min minimum-number-of-bytes
		   (length character-byte-vector)))
	(let ((min
		(min words-per-rectangle-array
		     words-per-byte-vector
		     words-per-bitmap)))
	  (when verbose?
	    (print-character-bitmap character-bitmap)
	    (print 
	      (list words-per-rectangle-array
		    words-per-byte-vector
		    words-per-bitmap)))
	  (incf total-rectangle-words words-per-rectangle-array)
	  (incf total-bitmap-words words-per-bitmap)
	  (incf total-vector-words words-per-byte-vector)
	  (cond
	    ((= min words-per-rectangle-array)
	     (incf rectangle-winners))
	    ((= min words-per-byte-vector)
	     (incf vector-winners))
	    (t (incf bitmap-winners))))))
    `((rectangle-winners ,rectangle-winners)
      (vector-winners ,vector-winners)
      (bitmap-winners ,bitmap-winners)
      
      (total-rectangle-words ,total-rectangle-words)
      (total-bitmap-words ,total-bitmap-words)
      (total-vector-words ,total-vector-words)
      
      (maximum-number-of-rectangles ,maximum-number-of-rectangles)
      (maximum-number-of-bytes ,maximum-number-of-bytes)
      (minimum-number-of-rectangles ,minimum-number-of-rectangles)
      (minimum-number-of-bytes ,minimum-number-of-bytes))))

;; Result:
;; 
;; ((rectangle-winners 272)
;;  (vector-winners 0)
;;  (bitmap-winners 6603)
;;  (total-rectangle-words 170562)
;;  (total-bitmap-words 55000)
;;  (total-vector-words 173910))
;;  
;; (MHD 4/24/91)






;;;; Asian (Kanji) Font File Names

;;; `Kanji16-font-filename' ...
;;; [ETC.!]

(defparameter kanji16-font-filename "kanji16.gf")
(defparameter kanji24-font-filename "kanji24.gf")
(defparameter kanji_*-font-filename "*.gb")
(defparameter minm_*-font-filename "*.spd")

(defparameter hangul16-font-filename "hangul16.gf")
(defparameter hangul24-font-filename "hangul24.gf")
(defparameter hangul_*-font-filename "*.gb")

(defparameter hangulttf-font-filename "hangul.ttf")

(defparameter chinesettf-font-filename "chinese.ttf") ; (MHD 4/9/99)














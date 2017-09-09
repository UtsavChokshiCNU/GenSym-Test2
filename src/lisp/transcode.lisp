;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module TRANSCODE: Facilities for Transcoding (Plain Text Import/Export)

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark David



(declare-forward-references
  (g2-stream-write-char function)        ; STREAMS
  (g2-stream-write-from-wide-string-buffer function)
  (g2-stream-write-from-buffer function))
(declare-forward-reference g2-stream-write-string function)
(declare-forward-reference intern-using-string-buffer function)



;;;; Replacement Characters Used for Transcoding



(defconstant ascii-replacement-character #.%\?) ; ? ; Consider also control code SUB, #u001A
(defconstant unicode-replacement-character #uFFFD) ; Unicode REPLACEMENT CHARACTER



;;; `Transcode-text-conversion-style' is the internal structure representing
;;; a "text-conversion-style" that the G2 user sees.  That is a frame with
;;; very similar slots.  See text-conversion-style, in module FILE-SYSPROC.

(eval-when (:compile-toplevel :load-toplevel :execute)

(def-structure transcode-text-conversion-style

  (transcode-conversion-style-name nil)

  (transcode-external-character-set nil)

  (transcode-unconvertible-character-spec nil) ; nil (drop unconvertable characters), or
                                        ;   a character (a replacement character)

  (transcode-unicode-line-separator-export-translation 'per-platform)
  ;; IRRELEVANT | PER-PLATFORM | CR | LF | CRLF | UNICODE-LINE-SEPARATOR | UNICODE-PARAGRAPH-SEPARATOR
  ;; IRRELEVANT -- means this doesn't come up -- e.g., if converting a line of
  ;; text, which by definition has no internal line ends; this information
  ;; may help the translator to spead up the translation in certain cases
  ;; -- ULS (Unicode Line Separator) only allowed if external
  ;; character set is Unicode, UTF-8, UTF-7, or UTF-G;
  ;; should get frame note if not matched.
  ;; -- PER-LOCAL-OS-STYLE means CRLF on Windows, LF on Unix,
  ;; and CRLF on VMS; it would be CR on MacOS if we ever
  ;; offered that.
  ;; -- this affects export only
  ;; -- for any of the 7-, 8-, or multibyte encodings,
  ;; CR => ULS, LF => ULS, CRLF => ULS, and ULS => ULS;
  ;; read-line stops at any of CR, LF, or CRLF;
  ;; -- for either of the Unicode UCS-2 encodings, read-line
  ;; stops additionally at ULS.

  (transcode-han-unification-mode nil)

  (string-type-for-export 'wide-string)) ; either GENSYM-STRING or WIDE-STRING

)








;;;; Defining Text Transcode Purposes


(def-global-property-name text-conversion-style-for-purpose)

(defmacro def-text-transcode-purpose
    (purpose
      &key
      parent-purpose
      conversion-style-name
      external-character-set
      unconvertible-character-spec
      unicode-line-separator-export-translation
      han-unification-mode
      string-type-for-export)
  `(install-text-transcode-purpose
     ',purpose
     ',parent-purpose
     ',conversion-style-name
     ',external-character-set
     ',unconvertible-character-spec
     ',unicode-line-separator-export-translation
     ',han-unification-mode
     ',string-type-for-export))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun create-transcode-text-conversion-style
       (parent-style?
        conversion-style-name external-character-set unconvertible-character-spec
        unicode-line-separator-export-translation han-unification-mode
        string-type-for-export)
  (let ((style (make-transcode-text-conversion-style)))
    (when parent-style?
       (setf (transcode-conversion-style-name style)
             (transcode-conversion-style-name parent-style?))
       (setf (transcode-external-character-set style)
             (transcode-external-character-set parent-style?))
       (setf (transcode-unconvertible-character-spec style)
             (transcode-unconvertible-character-spec parent-style?))
       (setf (transcode-unicode-line-separator-export-translation style)
             (transcode-unicode-line-separator-export-translation parent-style?))
       (setf (transcode-han-unification-mode style)
             (transcode-han-unification-mode parent-style?))
       (setf (string-type-for-export style)
             (string-type-for-export parent-style?)))
     (when conversion-style-name
       (setf (transcode-conversion-style-name style) conversion-style-name))
     (when external-character-set
       (setf (transcode-external-character-set style) external-character-set))
     (when unconvertible-character-spec
       (setf (transcode-unconvertible-character-spec style) unconvertible-character-spec))
     (when unicode-line-separator-export-translation
       (setf (transcode-unicode-line-separator-export-translation style)
             unicode-line-separator-export-translation))
     (when han-unification-mode
       (setf (transcode-han-unification-mode style) han-unification-mode))
     (when string-type-for-export
       (setf (string-type-for-export style) string-type-for-export))
     style))

(defun install-text-transcode-purpose
    (purpose
      parent-purpose
      conversion-style-name
      external-character-set
      unconvertible-character-spec
      unicode-line-separator-export-translation
      han-unification-mode
      string-type-for-export)
  (let ((style (create-transcode-text-conversion-style
                 (when parent-purpose (text-conversion-style-for-purpose parent-purpose))
                 conversion-style-name external-character-set unconvertible-character-spec
                 unicode-line-separator-export-translation han-unification-mode
                 string-type-for-export)))
    (setf (text-conversion-style-for-purpose purpose) style)
     purpose))
)







;;;; Basic Text Import Purposes for G2, GSI, and Telewindows


;;; A slew of Text Import Purposes are defined.  Purpose can be one of the
;;; following symbols:
;;;
;;;
;;;   UTF-G-STRING, NIL (default) -- imports an all-purpose utf-g-encoded wide
;;;   string or gensym string as a (Unicode-encoded) text string.
;;;
;;;   UTF-8-STRING -- imports a UTF-8-encoded wide string or gensym string as a
;;;   text string.
;;;
;;;   UTF-7-STRING -- imports a UTF-7-encoded wide string or gensym string as a
;;;   text string.
;;;
;;;   8859-1-STRING -- imports an 8859-1 (Latin 1) string
;;;   8859-2-STRING -- imports an 8859-2 (Latin 2) string
;;;   8859-3-STRING -- imports an 8859-3 (Latin 3) string
;;;   8859-4-STRING -- imports an 8859-4 (Latin 4) string
;;;   8859-5-STRING -- imports an 8859-5 (Latin/Cyrillic) string
;;;   8859-6-STRING -- imports an 8859-6 (Latin/Arabic) string
;;;   8859-7-STRING -- imports an 8859-7 (Latin/Greek) string
;;;   8859-8-STRING -- imports an 8859-8 (Latin/Hebrew) string
;;;   8859-9-STRING -- imports an 8859-9 (Latin 5) string
;;;   8859-10-STRING -- imports an 8859-10 (Latin 6) string
;;;
;;;   JIS -- imports 7-bit, ISO 2022 encoded JIS X 0208 (Japanese)
;;;   JIS-EUC -- imports 8-bit, escapeless ISO 2022 encoded JIS X 0208
;;;   Shift-JIS -- imports shift-jis encoded JIS X 0208
;;;
;;;   KSC -- imports 7-bit, ISO 2022 encoded KS C 5601 (Korean)
;;;   KSC-EUC -- imports 8-bit, escapeless ISO 2022 encoded KS C 5601
;;;
;;;   GB-2312 -- imports 7-bit, ISO 2022 encoded GB 2312-80 (Chinese Simplified)
;;;   GB-2312-EUC -- imports 8-bit, escapeless ISO 2022 encoded GB 2312-80
;;;
;;;   X-COMPOUND-TEXT -- imports X Compound Text -- this is text initially
;;;     in ISO 8859-1 (Latin1), but a subset of ISO 2022 escape sequences
;;;     can put you into any of the following character sets:
;;;        8859 (1-9); JIS-EUC; KSC-EUC
;;;     Note, however, that this uses LF only as the line end character, per
;;;     the X spec.
;;;
;;;   COMMAND-LINE-ARGUMENT -- a command line argument, gotten by the the system
;;;   for various general purposes
;;;
;;;   USER-COMMAND-LINE-ARGUMENT -- a command line argument, gotten by the user
;;;   via the get-command-line-argument-from-launch system procedure
;;;
;;;   DEFAULT-LANGUAGE-SPEC-VIA-ENVIRONMENT -- the spec given by "the
;;;   environment" (either an environment variable or equivalent concept for
;;;   Windows or VMS or a command line argument) -- note that this is a text
;;;   string, but the encoding might not be Unicode
;;;
;;;   GFI-INPUT-LINE, ATTRIBUTE-FILE-LINE -- these expect almost UTF-G encoded
;;;   lines of text, except tabs are allowed, and get converted to spaces. No
;;;   internal newline characters (i.e., CR, LF) are expected or handled.
;;;
;;;   X-CUT-BUFFER -- expect ISO Latin1 with LF's (CR's are handled for input,
;;;   too) and tabs.  Additional-arg?, if non-nil, should be the number of
;;;   spaces to expand a tab into.  If nil, tabs are accepted.  LF's are used
;;;   for export of line end characters.  [Note: later, this should determine
;;;   the charset from the locale and/or ISO 2022 escapes in the text!]
;;;
;;;   G2-STREAM-ERROR-STRING -- String returned by g2-stream-error-string, which
;;;   may come from the OS.
;;;
;;;   INIT-FILE-COMMAND-LINE -- text line in ASCII (at least traditionally --
;;;   consider making it Latin1 or even Unicode in the future) representing a
;;;   "command line" in a G2 init file.  (Here, "command line" is legal
;;;   Load/Save KB dialog grammar.)  In 4.0, spaces and tabs were stripped off
;;;   of either end, and tabs were converted to spaces, but that's no longer
;;;   strictly necessary, since tabs are fine in 5.0, or soon will be.  Thus,
;;;   the only action is to copy the input text string exactly.
;;;
;;;   KFEP-FILENAME -- a command line argument, environment variable, or default
;;;   pathname that specifies the location of one of the KFEP dictionary files.
;;;   For now this is assumed to be an ascii (8-bit) file name.  Conceivably,
;;;   this could be something quite exotic, such as an EUC-encoded JIS string.
;;;   Things will probably work out reasonably well even in this case, since
;;;   we'll leave all of the characters alone.
;;;
;;;   WIN32-MESSAGE -- a "message" (OS event) from the Win32 interface; CR/LF's
;;;   sequences and standalone Returns and Linefeeds are turned into our
;;;   canonical line break character; the additional arg, if non-nil, should
;;;   be a number that specifies the number of spaces to translate the Tab
;;;   character into.  If nil, tabs pass through untranslated.
;;;
;;;   G2-DIRECTORY-PATHNAME -- for now, this is expected to be a wide string
;;;   giving a pathname in ISO Latin1 (a superset of ASCII), with no internal
;;;   newlines or tabs (at least not any requiring translation); this is called,
;;;   e.g., from system procedure helper functions like
;;;   default-directory-lisp-side in order to import pathnames produced by the
;;;   g2-stream-get-default-directory.
;;;
;;;   GENSYM-PATHNAME-NAMESTRING -- this is the general purpose importer for the
;;;   namestring of a gensym pathname.  For now, these are assumed to be in ISO
;;;   Latin1 (a superset of ASCII), with no internal newlines or tabs.  This is
;;;   used, e.g., for making the name string of a KB pathname presentable to
;;;   users.
;;;
;;;   ICP-FILTERED-TEXT-STRING-WRITER -- ICP says, "the reader transforms G2
;;;   newlines into C newlines and removes G2 escape characters.  The writer
;;;   transforms C newlines into G2 newlines and removes C characters which have
;;;   no representation in G2, such as \t, the tab character."  This was
;;;   written for pre-Unicode G2.  Now that we have a represenation for all
;;;   of ISO Latin1, including Tab, we accept that.  Also, we handle the usual
;;;   ASCII newline conventions (CR, CRLF, and LF) now, not just LF.  [Review
;;;   this with JH et al! (MHD 6/18/96)]
;;;
;;;   FILTER-TEXT-FOR-GSI -- for both import/export this will receive a Gensym
;;;   string, which can just be passed in transcoded as ISO-8859-1 (Latin-1).



;; By default, for these purposes, we just consider the input to be in ISO Latin
;; 1 characters, since, as far as I can tell, there was never any documentation
;; stating that these were in the gensym character set in 4.0 or earlier, and I
;; don't see that things would have worked out that well if they were --
;; consider the case of a command line with a tilde, for example: g2 -ok
;; ~/myg2.ok
;;
;; However, see user-command-line-argument, below!

(def-text-transcode-purpose command-line-argument
    :external-character-set iso-8859-1
    :unicode-line-separator-export-translation irrelevant)

(def-text-transcode-purpose g2-stream-error-string
    :external-character-set iso-8859-1
    :unicode-line-separator-export-translation irrelevant)

(def-text-transcode-purpose init-file-command-line
    :external-character-set iso-8859-1
    :unicode-line-separator-export-translation irrelevant)

(def-text-transcode-purpose kfep-filename
    :external-character-set iso-8859-1
    :unicode-line-separator-export-translation irrelevant)

(def-text-transcode-purpose g2-directory-pathname
    :external-character-set iso-8859-1
    :unicode-line-separator-export-translation irrelevant)

(def-text-transcode-purpose g2-directory-pathname-w
    :external-character-set unicode
    :unicode-line-separator-export-translation irrelevant)

;; The following might have linebreak encoded as CRLF, CR, or LF.  Upon import,
;; such a linebreak is turned into Unicode Line Separator.

(def-text-transcode-purpose win32-message
    :external-character-set iso-8859-1)

(def-text-transcode-purpose icp-filtered-text-string-writer
    :external-character-set iso-8859-1)

(def-text-transcode-purpose gensym-pathname-namestring
    :external-character-set iso-8859-1)

(def-text-transcode-purpose namestring-as-gensym-string
    :external-character-set iso-8859-1
    :string-type-for-export gensym-string)

(def-text-transcode-purpose x-cut-buffer
    :external-character-set iso-8859-1
    :string-type-for-export gensym-string
    :unicode-line-separator-export-translation LF)

(def-text-transcode-purpose icp-filtered-text-string-writer
    :external-character-set iso-8859-1)

(def-text-transcode-purpose idl-file-input
    :external-character-set iso-8859-1)

(def-text-transcode-purpose ole-text-of-single-byte-chars
    :external-character-set iso-8859-1
    :string-type-for-export gensym-string)

(def-text-transcode-purpose filter-text-for-gsi
    :external-character-set iso-8859-1)

(def-text-transcode-purpose kb-file-comment
    :external-character-set iso-8859-1        ; review later; see comments in
                                        ;   kb load/save modules (MHD 11/13/96)
    :string-type-for-export gensym-string)



;; The following traditionally use UTF-G, and they allow tabs to be present.
;; They do normally have linebreak characters. Note: better error diagnosis is
;; needed to avoid a regression in diagnostic functionality from 4.0 -> 5.0!
;; (MHD 3/5/96)
;;
;; Note that no inverses of these (i.e., export) currently exist.


;;; The text conversion style for purpose `GFI-input-line' serves as a default.
;;; It is to be overridden by the text-conversion-style of the GFI input
;;; object.  (See also the next one.)

(def-text-transcode-purpose gfi-input-line
    :external-character-set utf-g)        ; tabs are needed & allowed



;;; The text conversion style for purpose `attribute-file-line' serves as a
;;; default for attribute files.  At this point we're not sure if we should make
;;; it overridable by the global text conversion style (the
;;; text-conversion-style of language-parameters) or just leave it as is.  If
;;; we left it as is, the plan might be to define a header that gives the
;;; character set, and derive the charset from the file's header.  ...

(def-text-transcode-purpose attribute-file-line
    :external-character-set utf-g)        ; tabs are needed & allowed





;;; The text conversion style for purpose `user-command-line-argument'
;;; is used when the command line is read by the system procedure
;;; get-command-line-argument-from-launch.

(def-text-transcode-purpose user-command-line-argument
    :external-character-set iso-8859-1
    :unicode-line-separator-export-translation irrelevant)

;; Note: in 4.0 this was actually utf-g, i.e., the Gensym character set.
;; However, this brought probably very little benefit to users, was not
;; consistent with G2's own handling of the interpretation of the characters on
;; the command line, and caused major hassles for users on Windows, who would
;; essentially have to use ~\ where they meant \ in a command line if they
;; wanted G2 to "get it" (and this would then not be interpreted correctly by G2
;; if they did it).  So, we're making this slightly incompatible change, and
;; we think it's for the better.  (Ideas about making this subject to
;; OS locale or to better parameterization facilities in G2 can still be
;; entertained, but should be done in synch with other command line
;; transcoding purposes.)  (MHD 12/6/96)




;; Purposes for Explicit Charsets: Sometimes You Really Just Know What You Want

(def-text-transcode-purpose utf-7-string
    :external-character-set unicode-utf-7)

(def-text-transcode-purpose utf-8-string
    :external-character-set unicode-utf-8)

(def-text-transcode-purpose 8859-1-string
    :external-character-set iso-8859-1)
(def-text-transcode-purpose 8859-2-string
    :external-character-set iso-8859-2)
(def-text-transcode-purpose 8859-3-string
    :external-character-set iso-8859-3)
(def-text-transcode-purpose 8859-4-string
    :external-character-set iso-8859-4)
(def-text-transcode-purpose 8859-5-string
    :external-character-set iso-8859-5)
(def-text-transcode-purpose 8859-6-string
    :external-character-set iso-8859-6)
(def-text-transcode-purpose 8859-7-string
    :external-character-set iso-8859-7)
(def-text-transcode-purpose 8859-8-string
    :external-character-set iso-8859-8)
(def-text-transcode-purpose 8859-9-string
    :external-character-set iso-8859-9)
(def-text-transcode-purpose 8859-10-string
    :external-character-set iso-8859-10)


(def-text-transcode-purpose jis-string
    :external-character-set jis-x-0208        ; pretty much MIME's ISO-2022-JP
    :han-unification-mode japanese)

(def-text-transcode-purpose jis-gensym-string-with-crlf
    :external-character-set jis-x-0208
    :string-type-for-export gensym-string
    :han-unification-mode japanese
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose jis-euc-string
    :external-character-set jis-x-0208-euc ; we call it elsewhere JIS-EUC; simplify!
    :han-unification-mode japanese)

(def-text-transcode-purpose jis-euc-gensym-string-with-crlf
    :external-character-set jis-x-0208-euc
    :string-type-for-export gensym-string
    :han-unification-mode japanese
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose shift-jis-string
    :external-character-set shift-jis-x-0208 ; we call it elsewhere shift-jis; simplify!
    :han-unification-mode japanese)

(def-text-transcode-purpose shift-jis-gensym-string-with-crlf
    :external-character-set shift-jis-x-0208
    :string-type-for-export gensym-string
    :han-unification-mode japanese
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose ks-string
    :external-character-set ks-c-5601
    :han-unification-mode korean)

(def-text-transcode-purpose ks-gensym-string-with-crlf
    :external-character-set ks-c-5601
    :string-type-for-export gensym-string
    :han-unification-mode korean
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose ks-euc-string
    :external-character-set ks-c-5601-euc
    :han-unification-mode korean)

(def-text-transcode-purpose ks-euc-gensym-string-with-crlf
    :external-character-set ks-c-5601-euc
    :string-type-for-export gensym-string
    :han-unification-mode korean
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose gb-2312-string
    :external-character-set gb-2312
    :han-unification-mode chinese)

(def-text-transcode-purpose gb-2312-gensym-string-with-crlf
    :external-character-set gb-2312
    :string-type-for-export gensym-string
    :han-unification-mode chinese
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose gb-2312-euc-string
    :external-character-set gb-2312-euc
    :han-unification-mode chinese)

(def-text-transcode-purpose gb-2312-euc-gensym-string-with-crlf
    :external-character-set gb-2312-euc
    :string-type-for-export gensym-string
    :han-unification-mode chinese
    :unicode-line-separator-export-translation CRLF)

;;; `X-Compound-Text-String' implements (a subset of) X Compound Text....

(def-text-transcode-purpose x-compound-text-string
    :string-type-for-export gensym-string
    :external-character-set x-compound-text
    ;; starts out in iso-8859-1, but can move between that and many
    ;; other standards.
    :han-unification-mode japanese
    ;; line end character must be LF per the X spec:
    :unicode-line-separator-export-translation LF)

;;; `X-String' implements the X String format .... This exports a gensym string
;;; in ISO 8859-1 (Latin-1) with LF's as the line end character on all platforms.

(def-text-transcode-purpose x-string
    :string-type-for-export gensym-string
    :external-character-set iso-8859-1
    ;; line end character must be LF per the X spec:
    :unicode-line-separator-export-translation LF)

;;; `CF-Text' implements the Windows simple Clipboard Format for text .... This
;;; exports a gensym string in ISO 8859-1 (Latin-1) with CRLF's as the line end
;;; character on all platforms.
;;;
;;; `CF-Unicode-Text' is similar, but (a) it exports a wide string, and (b) the
;;; character set is Unicode.  (CRLF's are still used at line endings.)

(def-text-transcode-purpose cf-text
    :string-type-for-export gensym-string
    :external-character-set iso-8859-1
    ;; line end character must be CRLF per the Windows spec:
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose cf-unicode-text
    :external-character-set unicode
    ;; line end character must be CRLF per the Windows spec:
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose utf-g-string
    :external-character-set utf-g)

(def-text-transcode-purpose utf-g-ascii-as-much-as-possible-string
    :external-character-set utf-g-ascii-as-much-as-possible)

(defvar default-text-conversion-style
  (text-conversion-style-for-purpose 'utf-g-string))

(defvar utf-g-ascii-as-much-as-possible-conversion-style
  (text-conversion-style-for-purpose
    'utf-g-ascii-as-much-as-possible-string))





;;;; Basic Text Export Purposes for G2, GSI, and Telewindows




(def-text-transcode-purpose unicode
    :external-character-set unicode)

(def-text-transcode-purpose known-iso-latin1-to-iso-latin1
    :external-character-set iso-8859-1)

(def-text-transcode-purpose known-ascii-to-ascii
    :external-character-set us-ascii)

(def-text-transcode-purpose us-ascii-gensym-string-with-crlf
    :external-character-set us-ascii
    :string-type-for-export gensym-string
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose g2-directory-pathname
    :external-character-set iso-8859-1)

(def-text-transcode-purpose gensym-pathname-namestring
    :external-character-set iso-8859-1)

(def-text-transcode-purpose pformat
    :external-character-set iso-8859-1)

(def-text-transcode-purpose instantiate-file-template-for-printing
    :external-character-set iso-8859-1)

(def-text-transcode-purpose notify-user-if-possible-via-console
    :external-character-set iso-8859-1)

(def-text-transcode-purpose kb-error
    :external-character-set iso-8859-1)

(def-text-transcode-purpose icp-filtered-text-string-reader
    :external-character-set iso-8859-1)

(def-text-transcode-purpose iso-latin1-gensym-string
    :external-character-set iso-8859-1)

(def-text-transcode-purpose idl-source-file-pathname
    :external-character-set iso-8859-1)

(def-text-transcode-purpose filter-text-for-gsi
    :external-character-set iso-8859-1)


(def-text-transcode-purpose iso-8859-1-wide-string
    :external-character-set iso-8859-1)

(def-text-transcode-purpose iso-8859-1-gensym-string
    :external-character-set iso-8859-1
    :string-type-for-export gensym-string)

(def-text-transcode-purpose iso-8859-1-gensym-string-with-crlf
    :external-character-set iso-8859-1
    :string-type-for-export gensym-string
    :unicode-line-separator-export-translation CRLF)

;;; The purpose ASCII is an easy-to-remember alias for
;;; iso-8859-1-gensym-string.  It does the thing you
;;; probably expect in most cases: turns line separators
;;; into <LF>, produces a gensym string.  Also, eight bit
;;; Latin-1 characters are just turned into their
;;; corresponding 8-bit Latin-1 characters.

(def-text-transcode-purpose ascii
    :external-character-set iso-8859-1
    :string-type-for-export gensym-string)


(def-text-transcode-purpose iso-8859-2-wide-string
    :external-character-set iso-8859-2)

(def-text-transcode-purpose iso-8859-2-gensym-string
    :external-character-set iso-8859-2
    :string-type-for-export gensym-string)

(def-text-transcode-purpose iso-8859-2-gensym-string-with-crlf
    :external-character-set iso-8859-2
    :string-type-for-export gensym-string
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose iso-8859-3-wide-string
    :external-character-set iso-8859-3)

(def-text-transcode-purpose iso-8859-3-gensym-string
    :external-character-set iso-8859-3
    :string-type-for-export gensym-string)

(def-text-transcode-purpose iso-8859-3-gensym-string-with-crlf
    :external-character-set iso-8859-3
    :string-type-for-export gensym-string
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose iso-8859-4-wide-string
    :external-character-set iso-8859-4)

(def-text-transcode-purpose iso-8859-4-gensym-string
    :external-character-set iso-8859-4
    :string-type-for-export gensym-string)

(def-text-transcode-purpose iso-8859-4-gensym-string-with-crlf
    :external-character-set iso-8859-4
    :string-type-for-export gensym-string
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose iso-8859-5-wide-string
    :external-character-set iso-8859-5)

(def-text-transcode-purpose iso-8859-5-gensym-string
    :external-character-set iso-8859-5
    :string-type-for-export gensym-string)

(def-text-transcode-purpose iso-8859-5-gensym-string-with-crlf
    :external-character-set iso-8859-5
    :string-type-for-export gensym-string
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose iso-8859-6-wide-string
    :external-character-set iso-8859-6)

(def-text-transcode-purpose iso-8859-6-gensym-string
    :external-character-set iso-8859-6
    :string-type-for-export gensym-string)

(def-text-transcode-purpose iso-8859-6-gensym-string-with-crlf
    :external-character-set iso-8859-6
    :string-type-for-export gensym-string
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose iso-8859-7-wide-string
    :external-character-set iso-8859-7)

(def-text-transcode-purpose iso-8859-7-gensym-string
    :external-character-set iso-8859-7
    :string-type-for-export gensym-string)

(def-text-transcode-purpose iso-8859-7-gensym-string-with-crlf
    :external-character-set iso-8859-7
    :string-type-for-export gensym-string
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose iso-8859-8-wide-string
    :external-character-set iso-8859-8)

(def-text-transcode-purpose iso-8859-8-gensym-string
    :external-character-set iso-8859-8
    :string-type-for-export gensym-string)

(def-text-transcode-purpose iso-8859-8-gensym-string-with-crlf
    :external-character-set iso-8859-8
    :string-type-for-export gensym-string
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose iso-8859-9-wide-string
    :external-character-set iso-8859-9)

(def-text-transcode-purpose iso-8859-9-gensym-string
    :external-character-set iso-8859-9
    :string-type-for-export gensym-string)

(def-text-transcode-purpose iso-8859-9-gensym-string-with-crlf
    :external-character-set iso-8859-9
    :string-type-for-export gensym-string
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose iso-8859-10-wide-string
    :external-character-set iso-8859-10)

(def-text-transcode-purpose iso-8859-10-gensym-string
    :external-character-set iso-8859-10
    :string-type-for-export gensym-string)

(def-text-transcode-purpose iso-8859-10-gensym-string-with-crlf
    :external-character-set iso-8859-10
    :string-type-for-export gensym-string
    :unicode-line-separator-export-translation CRLF)


(def-text-transcode-purpose utf-7-wide-string
    :external-character-set unicode-utf-7)

(def-text-transcode-purpose utf-7-gensym-string
    :external-character-set unicode-utf-7
    :string-type-for-export gensym-string)

(def-text-transcode-purpose utf-8-wide-string
    :external-character-set unicode-utf-8)

(def-text-transcode-purpose utf-8-gensym-string
    :external-character-set unicode-utf-8
    :string-type-for-export gensym-string)

(def-text-transcode-purpose utf-8-gensym-string-with-newline
    :external-character-set unicode-utf-8
    :string-type-for-export gensym-string
    :unicode-line-separator-export-translation lf)

(def-text-transcode-purpose utf-8-gensym-string-with-crlf
    :external-character-set unicode-utf-8
    :string-type-for-export gensym-string
    :unicode-line-separator-export-translation CRLF)

(def-text-transcode-purpose utf-g-wide-string
    :external-character-set utf-g)

(def-text-transcode-purpose utf-g-gensym-string
    :external-character-set utf-g
    :string-type-for-export gensym-string)





;;;; Miscellaneous Transcoding Code



;;; `Char+w' returns the wide character whose code is that of wide character
;;; plus delta.  Delta should be a smallish positive or negative fixnum, i.e.,
;;; such that the resulting code remains within the range of 16-bit unsigned
;;; integers.  `Char-w' is the same but subtracts delta.

;;; `Char-ashw' returns the wide character whose code is that of wide character
;;; arithmetically shifted to the left by delta.  Delta should be a very small
;;; positive or negative fixnum, i.e., such that the resulting code remains
;;; within the range of 16-bit unsigned integers.

(defmacro char+w (wide-character delta)
  `(code-wide-character
     (+f (wide-character-code ,wide-character) ,delta)))

(defmacro char-w (wide-character delta)
  `(code-wide-character
     (-f (wide-character-code ,wide-character) ,delta)))

(defmacro char-ashw (wide-character shift-amount)
  `(code-wide-character
     (ashf (wide-character-code ,wide-character) ,shift-amount)))

(defmacro char-iorw (wide-character-1 wide-character-2)
  `(code-wide-character
     (logiorf
       (wide-character-code ,wide-character-1)
       (wide-character-code ,wide-character-2))))

(defmacro char-andw (wide-character-1 wide-character-2)
  `(code-wide-character
     (logandf
       (wide-character-code ,wide-character-1)
       (wide-character-code ,wide-character-2))))



;;; `Wide-character-octets-to-wide-character' converts two octets represented as
;;; wide characters into a single wide character, in which lead-character
;;; occupies the most significant bits.  `Octets-to-wide-character' is similar,
;;; but goes from octets lead-octet and trail-octet.

(defun-substitution-macro octets-to-wide-character
    (lead-octet trail-octet)
  (code-wide-character
    (logiorf
      (ashf (logandf lead-octet #xFF) 8)
      (logandf trail-octet #xFF))))

(defun-substitution-macro wide-character-octets-to-wide-character
    (lead-character trail-character)
  (octets-to-wide-character
    (wide-character-code lead-character) (wide-character-code trail-character)))



;;; `Wide-character-lead-octet-character' returns the wide character whose code
;;; whose code has as its bits the leftmost 8 bits of wide-character.  E.g.,
;;; if wide-character is #uABCD, this returns #u00AB.

(defun-substitution-macro wide-character-lead-octet-character (wide-character)
  (char-ashw wide-character -8))

;;; `Wide-character-trail-octet-character' returns the wide character whose code
;;; whose code has as its bits the rightmost 8 bits of wide-character.  E.g.,
;;; if wide-character is #uABCD, this returns #u00CD.

(defun-substitution-macro wide-character-trail-octet-character (wide-character)
  (char-andw wide-character #u00FF))




;;; `Wide-characters-to-double-byte-code' converts either GL (7-bit) or GR
;;; (8-bit) lead and trail (wide) characters into their corresponding 16-bit
;;; code.  `Octets-to-double-byte-code' does the same but for octets (8-bit
;;; bytes).  `7-bit-octets-to-double-byte-code' does the same, but only converts
;;; GL (7-bit) octets.

(defun-substitution-macro 7-bit-octets-to-double-byte-code
    (lead-7-bit-octet trail-7-bit-octet)
  (+f (ashf lead-7-bit-octet 8) trail-7-bit-octet))

(defun-substitution-macro octets-to-double-byte-code (lead-octet trail-octet)
  (7-bit-octets-to-double-byte-code
    (logandf lead-octet #x7F)
    (logandf trail-octet #x7F)))

(defun-substitution-macro wide-characters-to-double-byte-code
    (lead-character trail-character)
  (octets-to-double-byte-code
    (wide-character-code lead-character)
    (wide-character-code trail-character)))


;;; `Double-byte-lead-octet' extracts the lead 7-bit code from double-byte-code,
;;; a 16-bit integer.
;;;
;;; `Double-byte-trail-octet' extracts the trail 8-bit code from
;;; double-byte-code, a 16-bit integer.

(defun-substitution-macro double-byte-lead-octet (double-byte-code)
  (logandf (ashf double-byte-code -8) #x7F))

(defun-substitution-macro double-byte-trail-octet (double-byte-code)
  (logandf double-byte-code #x7F))



;;; `Read-wide-character-from-string' -- a special-purpose macro.
;;; Wide-string-case? is evaluated at macroexpansion time to choose the
;;; appropriate expansion.

(defmacro read-wide-character-from-string
    (string i string-is-simple? wide-string-case?)
  (avoiding-variable-capture (string i string-is-simple?)
    (if wide-string-case?
        `(prog1 (read-character-from-text-string ,string ,i)
           ,string-is-simple?)                ; not used, just to suppress warning!
        `(character-to-wide-character
           (read-simple-character-from-gensym-string
             ,string ,i ,string-is-simple?)))))



;;; `Read-gensym-character-from-wide-string' is similar to
;;; read-gensym-character-from-gensym-string, but works with text strings with
;;; UTF-G encoding instead of gensym strings. It reads and returns the next
;;; gensym character, after setting index-variable to the character index past
;;; the next character, and after setting escape-character?-variable to either
;;; nil or the escape character beginning a complex character if the next
;;; character is complex.
;;;
;;; Note that since this is in UTF-G, the result is a "gensym character", i.e.,
;;; a pair of character-or-character-code and escape-character?.
;;;
;;; This macro is nonstandard in the following way: index-variable may be
;;; evaluated and set more than one time.

(defmacro read-gensym-character-from-wide-string
    (wide-string index-variable escape-character?-variable)
  (avoiding-variable-capture (wide-string &aux wide-character)
    `(let ((,wide-character
             (read-character-from-wide-string
               ,wide-string ,index-variable)))
       (declare (type wide-character ,wide-character))
       (wide-character-case
         ,wide-character
         ((#.%\@ #.%\~)
          (setf ,escape-character?-variable
                (wide-character-to-character ,wide-character))
          (wide-character-to-character
            (read-character-from-wide-string
              ,wide-string ,index-variable)))
         (#.%\\
            (setf ,escape-character?-variable
                  (wide-character-to-character ,wide-character))
            (read-kanji-code-from-wide-string
              ,wide-string ,index-variable))
         (t
           (setf ,escape-character?-variable nil)
           (ascii-code-char
             (wide-character-code
               ,wide-character)))))))

;; Consider changing "gensym" to "utf-g" here and similar cases throughout.





(defun-void twrite-spaces-for-tabs (spaces-for-tabs?)
  (loop repeat (if spaces-for-tabs?
                   (if (fixnump spaces-for-tabs?) spaces-for-tabs? 1)
                   1)
        do (twrite-char (if spaces-for-tabs? #.%space #.%tab))))





;;;; Text Sequence Structures



(def-structure (text-sequence
                 (:constructor make-text-sequence-internal ())
                 (:reclaimer reclaim-text-sequence-internal))

  text-sequence-string
  (text-sequence-string-start 0)
  text-sequence-string-end

  text-sequence-string-type                ; GENSYM-STRING | WIDE-STRING
  (text-sequence-string-is-simple-p nil) ; relevant for gensym strings only

  text-sequence-string-index
  previous-text-sequence-string-index)        ; records index just before a get, to
                                        ;   support rollback, i.e., "unget"



(def-structure (gensym-string-text-sequence
                 (:include
                   text-sequence
                   (text-sequence-string-type 'gensym-string)))
  )


(def-structure (wide-string-text-sequence
                 (:include
                   text-sequence
                   (text-sequence-string-type 'wide-string)))
  )






;;; `Initialize-text-sequence-string for text-sequence' ...

(def-generic-structure-method initialize-text-sequence-string
    (text-sequence string start? end?))

(def-structure-method initialize-text-sequence-string
    (text-sequence string start? end?)
  (declare (ignore end?))   ; must be set up by inferior class's methods
  (setf (text-sequence-string text-sequence) string)
  (setf (text-sequence-string-start text-sequence) (or start? 0))
  (setf (text-sequence-string-index text-sequence)
        (text-sequence-string-start text-sequence)))


(def-structure-method initialize-text-sequence-string
    (gensym-string-text-sequence string start? end?)
  (funcall-superior-method gensym-string-text-sequence string start? end?)
  (let ((simple-p (simple-gensym-string-p string)))
    (setf (text-sequence-string-is-simple-p gensym-string-text-sequence)
          simple-p)
    (setf (text-sequence-string-end gensym-string-text-sequence)
          (or end? (glength string simple-p)))))


(def-structure-method initialize-text-sequence-string
    (wide-string-text-sequence string start? end?)
  (funcall-superior-method wide-string-text-sequence string start? end?)
  (setf (text-sequence-string-end wide-string-text-sequence)
        (or end? (wide-string-length string)))
  nil)





;;; `Text-sequence-has-more-characters-p' is true if text-sequence has
;;; exhausted all of its characters.  Otherwise it's false.

(def-substitution-macro text-sequence-has-more-characters-p (text-sequence)
  (<f (text-sequence-string-index text-sequence)
      (text-sequence-string-end text-sequence)))



;;; `read-character-from-text-sequence for text-sequence' ...

(def-generic-structure-method read-character-from-text-sequence
    (text-sequence))

(def-structure-method read-character-from-text-sequence
    (gensym-string-text-sequence)
  (let ((text-sequence gensym-string-text-sequence))
    (setf (previous-text-sequence-string-index text-sequence)
          (text-sequence-string-index text-sequence))
    (character-to-wide-character
      (read-simple-character-from-gensym-string
        (text-sequence-string text-sequence)
        (text-sequence-string-index text-sequence)
        (text-sequence-string-is-simple-p text-sequence)))))

(def-structure-method read-character-from-text-sequence
    (wide-string-text-sequence)
  (let ((text-sequence wide-string-text-sequence))
    (setf (previous-text-sequence-string-index text-sequence)
          (text-sequence-string-index text-sequence))
    (read-character-from-wide-string
      (text-sequence-string text-sequence)
      (text-sequence-string-index text-sequence))))


;;; `Make-text-sequence' creates a text-sequence or an instance of a subtype
;;; thereof, and initializes its slots based on these argument.

(defun-simple make-text-sequence (string start? end?)
  (let ((text-sequence
          (cond
            ((gensym-string-p string)
             (make-gensym-string-text-sequence))
            (t
             (make-wide-string-text-sequence)))))
    (initialize-text-sequence-string text-sequence string start? end?)
    text-sequence))


;;; `With-text-sequence' executes body with sequence-var bound to a text
;;; sequence based on string, start?, and end?, and returns the first value of
;;; the result of that evaluation.  Note that multiple values cannot be returned
;;; from this function.  Note also that a throw or error during body will result
;;; in the text sequence being not reclaimed, i.e., leaked.

(defmacro with-text-sequence ((sequence-var string start? end?) &body body)
  `(let ((,sequence-var (make-text-sequence ,string ,start? ,end?)))
     (prog1 (progn . ,body)
       (reclaim-structure ,sequence-var))))




;;; `Reclaim-text-sequence' reclaims a text sequence or any instance
;;; of a subtype of text-sequence.

(defmacro reclaim-text-sequence (text-sequence)
  `(reclaim-structure ,text-sequence))






;; Not ready for prime time ...
;;
;; ;;;; Text Conversion Structures
;;
;;
;; ;;; A `text conversion' structure is used to transact a text
;; ;;; conversion.  It has three components:
;; ;;;
;; ;;;   (1) an input text sequence;
;; ;;;   (2) an output text sequence; and
;; ;;;   (3) a text conversion style
;; ;;;
;; ;;; The steps involved in converting text are
;; ;;;
;; ;;;   (1) create and initialize a text conversion
;; ;;;       with the above three components: the
;; ;;;       input text sequence, the output
;; ;;;       text sequence, and the text
;; ;;;       conversion style
;; ;;;
;; ;;;   (2) call the do-text-conversion method
;; ;;;
;; ;;;   (3) extract the resulting output text sequence
;; ;;;
;; ;;;   (4) examine the text-conversion-result slot
;; ;;;       of the structure: it contains information
;; ;;;       on the success or lack thereof.
;;
;; (def-structure text-conversion
;;   text-conversion-input-text-sequence
;;   text-conversion-output-text-sequence
;;   text-conversion-text-conversion-style
;;   (text-conversion-result nil))
;;
;;






;;;; Translating Line Ending Characters


;;; Line-ending characters are to be translated in G2 as follows:
;;;
;;;   CRLF => <line end>
;;;   LF => <line end>
;;;   CR => <line end>
;;;
;;; Note that in 4.0, the translation LFCR => <line end> was used in various
;;; places, that was probably at best never used, and at worst was a bug.  There
;;; is no character set/encoding standard anywhere, I (MHD) believe, that uses
;;; that convention, whereas the above convention reflects a fairly standard
;;; kind of handling.
;;;
;;; The canonical character internally for <line end> shall be Unicode Line
;;; Separator (#u2028).
;;;
;;; See transcode-control-character, below, for the implementation of this
;;; strategy.





;;;; Transcoders




;;; The `transcoder' is the basic structure around which a text
;;; data element conversion happens.  ...

(def-structure (transcoder)
  transcoder-text-sequence
  (transcoder-character #uFFFF)                ; the current character
  (transcoder-previous-character #uFFFF) ; the previous character
  transcoder-text-conversion-style
  (transcoder-enqueued-characters '()))        ; simple gensym-list; hardly used



;;; `With-transcoder' executes body with transcoder-var bound to a transcoder
;;; based on its args, and returns the first value of the result of that
;;; evaluation.  Note that multiple values cannot be returned from this
;;; function.  Note also that a throw or error during body will result in the
;;; text sequence being not reclaimed, i.e., leaked.

(defmacro with-transcoder ((transcoder-var
                             text-conversion-style
                             text-sequence)
                           &body body)
  `(let ((,transcoder-var
            (make-transcoder-per-text-conversion-style
              ,text-conversion-style
              ,text-sequence)))
     (prog1 (progn . ,body)
       (reclaim-structure ,transcoder-var))))



;;; `Get-transcoder-character' ... only to be called when characters are
;;; available and always returns a character.  `Get-transcoder-character-if-any'
;;; can be called in either case; if no characters are available, it returns
;;; nil.

(defun-simple get-transcoder-character (transcoder)
  (let* ((text-sequence (transcoder-text-sequence transcoder)))
    (setf (transcoder-previous-character transcoder)
          (transcoder-character transcoder))
    (setf (transcoder-character transcoder)
          (read-character-from-text-sequence text-sequence))))

(defun-simple get-transcoder-character-if-any (transcoder)
  (let* ((text-sequence (transcoder-text-sequence transcoder)))
    (when (text-sequence-has-more-characters-p text-sequence)
      (setf (transcoder-previous-character transcoder)
            (transcoder-character transcoder))
      (setf (transcoder-character transcoder)
            (read-character-from-text-sequence text-sequence)))))



;;; `Enqueue-pending-transcoder-character' is (conceptually (*)) a method that
;;; is used by transcode-character or export-character when it's necessary to
;;; emit more than one character based on a single input character.
;;;
;;; Not all transcoders use this.  In general, it is the responsibility of the
;;; twrite-for-export-from-transcoder and twrite-unicode-from-transcoder
;;; functions to service this queue between calls to transcode-character or
;;; export-character methods.  (It could have been made the responsibility of
;;; those methods, but that would make more complicated than seems necessary.)
;;;
;;; The `pending-transcoder-characters-p' and
;;; `dequeue-pending-transcoder-character' operations are for testing for the
;;; presence of and for dequeueing enqueued characters, respectively.

;;; (*) These operations are macros for now, not methods, which is more
;;; efficient.  They could be made real methods at any time, but it's good for
;;; them to add as little overhead as possible when they're used.

(defmacro enqueue-pending-transcoder-character (transcoder character)
  (avoiding-variable-capture (transcoder character)
    `(setf (transcoder-enqueued-characters ,transcoder)
           (nconc
             (transcoder-enqueued-characters ,transcoder)
             (gensym-cons ,character nil)))))

;; This is efficient enough for the intended light-weight usage.

(defmacro pending-transcoder-characters-p (transcoder)
  `(transcoder-enqueued-characters ,transcoder))

(defmacro dequeue-pending-transcoder-character (transcoder)
  `(gensym-pop (transcoder-enqueued-characters ,transcoder)))








;;; The generic structure method `transcode-character' on transcoder
;;; type structures is the heart of character set decoding.  This
;;; should in general be specialized for each subtype of transcoder.
;;;
;;; It should either get the next character, transcoded as appropriate, or
;;; return #uFFFF to indicate that nothing should be done with the next
;;; character.  In getting the next character, it may decide to take various
;;; additional actions, which may include getting further characters and/or
;;; changing the state of the transcoder, or doing additional side effects.
;;;
;;; It should be called when additional characters are available.
;;;
;;; It should maintain the slots transcoder-character and
;;; transcoder-previous-character as best it can.  However, in case it performs
;;; side effects such as reading additional characters, and it cannot maintain
;;; sensible values in those slots, it should fill one or both of them with the
;;; value #uFFFF.  This should be done, for example, after reading an ISO 2022
;;; escape sequence or a Gensym UTF-G escape sequence.

(def-generic-structure-method transcode-character (transcoder))


;;; The generic structure method `export-character' on transcoder type
;;; structures maps from a Unicode character to the appropriate character or
;;; characters for the transcoder.  If more than one character, the additional
;;; character are enqueued; see enqueue-pending-transcoder-character.  If
;;; the character #uFFFF (Unicode undefined character) is returned, it is
;;; interpreted to mean "skip this character"; this may help simplify the
;;; case where characters are enqueued.

(def-generic-structure-method export-character (transcoder))



;;; The `transcode-character for transcoder' method is a noop: it simply gets
;;; the next character and passes it through as is.

(def-structure-method transcode-character (transcoder)
  (get-transcoder-character transcoder))



;;; The `export-character for transcoder' method is a noop: it simply gets
;;; the next character and passes it through as is.

(def-structure-method export-character (transcoder)
  (get-transcoder-character transcoder))


(def-generic-structure-method transcode-as-text-string (transcoder))
(def-generic-structure-method twrite-unicode-from-transcoder (transcoder))
(def-generic-structure-method export-as-string (transcoder))
(def-generic-structure-method twrite-for-export-from-transcoder (transcoder))


(def-structure-method transcode-as-text-string (transcoder)
  (twith-output-to-text-string
    (twrite-unicode-from-transcoder transcoder)))

;; #uFFFF (written U+FFFF in Unicode publications) is the "non-character character".


(def-structure-method twrite-unicode-from-transcoder (transcoder)
  (let ((translated-character #uFFFF))
    (declare (type wide-character translated-character))
    (loop with text-sequence = (transcoder-text-sequence transcoder)
          while (text-sequence-has-more-characters-p text-sequence)
          do (setq translated-character (transcode-character transcoder))
             (unless (char=w translated-character #uFFFF)
                                        ; "skip-translated-char-p"?
               (twrite-char translated-character)
               (when (pending-transcoder-characters-p transcoder)
                 (loop for character
                           = (dequeue-pending-transcoder-character transcoder)
                       do (twrite-char character)
                       while (pending-transcoder-characters-p transcoder)))))))



(def-structure-method export-as-string (transcoder)
  (cond
    ((eq (string-type-for-export
           (transcoder-text-conversion-style transcoder))
         'gensym-string)
     (twith-output-to-gensym-string
       (twrite-for-export-from-transcoder transcoder)))
    (t
     (twith-output-to-wide-string
       (twrite-for-export-from-transcoder transcoder)))))


(def-structure-method twrite-for-export-from-transcoder (transcoder)
  (let ((translated-character #uFFFF))
    (declare (type wide-character translated-character))
    (loop with text-sequence = (transcoder-text-sequence transcoder)
          while (text-sequence-has-more-characters-p text-sequence)
          do (setq translated-character (export-character transcoder))
             (unless (char=w translated-character #uFFFF)
                                        ; "skip-translated-char-p"?
               (twrite-char translated-character))
             (when (pending-transcoder-characters-p transcoder)
               (loop do (twrite-char
                          (dequeue-pending-transcoder-character
                            transcoder))
                     while (pending-transcoder-characters-p
                             transcoder))))))


;;; `Transcode-control-character' is an operation on any type of transcoder for
;;; handling normal ASCII-like "control characters", i.e. characters with codes
;;; in the range 0 to 31.  This handles CR, LF, and CRLF, in the usual delicate
;;; way, returning #uFFFF for the the LF after a CR, %line-separator for the
;;; other cases of CR and LF, and otherwise passes every other character through
;;; as is.  In particular, note that handling of #u001B (the escape character)
;;; is left to the caller, if it is to be done at all.

;;; `Transcode-character-handling-line-separator' is currently the same, but is
;;; stylistically preferred in cases where the character is not known to be a
;;; control character, and may well be a graphic character.

(defun-substitution-macro transcode-control-character (character transcoder)
  (cond
    ((and (char=w character #.%linefeed)
          (char=w (transcoder-previous-character transcoder) #.%return))
     #uFFFF)
    ((or (char=w character #.%linefeed)
         (char=w character #.%return))
     #.%line-separator)
    (t character)))

(defun-substitution-macro transcode-character-handling-line-separator
    (character transcoder)
  (transcode-control-character character transcoder))


;;; `Export-control-character' is an operation on any type of transcoder for
;;; handling normal ASCII-like "control characters", i.e. characters with codes
;;; in the range 0 to 31.  This handles ULS in the usual delicate way, i.e.,
;;; turning it into CR, LF, or CRLF, per the text conversion style in the
;;; transcoder.  In addition, this handles the Unicode characters
;;; %Line-separator and %Paragraph-separator.
;;;
;;; Note: this may enqueue one additional character, i.e., the LF in CRLF, so
;;; users of this operation must always check for enqueued pending characters;
;;; see the documentation for enqueue-pending-transcoder-character.

;;; `Export-character-handling-line-separator' is currently the same, but is
;;; stylistically preferred in cases where the character is not known to be
;;; a control character, and may well be a graphic character.

(defun-substitution-macro export-control-character (character transcoder)
  (cond
    ((or (char=w character #.%line-separator)
         (char=w character #.%paragraph-separator)) ; review!
     (case (transcode-unicode-line-separator-export-translation
             (transcoder-text-conversion-style transcoder))
       (per-platform
        (case g2-operating-system
          ((dos vms win32)
           (enqueue-pending-transcoder-character transcoder #.%linefeed)
           #.%return)
          (unix #.%linefeed)
          (t #.%linefeed)))                ; unknown platform
       (CR #.%return)
       (LF #.%linefeed)
       (CRLF
        (enqueue-pending-transcoder-character transcoder #.%linefeed)
        #.%return)
       (UNICODE-LINE-SEPARATOR
        #.%line-separator)
       (UNICODE-PARAGRAPH-SEPARATOR
        #.%paragraph-separator)
       (t character)))
    (t character)))

(defun-substitution-macro export-character-handling-line-separator
    (character transcoder)
  (export-control-character character transcoder))



;;; `Transcode-unhandled-character' is an operation on any type of transcoder
;;; for handling an unhandled character in the usual way, which is somewhat
;;; parameterized by the transcoder's text conversion style's
;;; unconvertable-character-spec slot.  The two main actions are either dropping
;;; the character, as indicated by the return value of #uFFFF, or using the
;;; replacement character in the slot, as indicated by the return of any other
;;; value, which would be that character.  It would be nice to support at least
;;; two other actions: (1) signalling an error and (2) returning a nearest
;;; approximation of character, possibly as more than one character, possibly by
;;; jumping to a table of nearest approximations supplied by the user or by
;;; some other source.

(defun transcode-unhandled-character (character transcoder)
  (declare (ignore character))
  (let ((spec
          (transcode-unconvertible-character-spec
            (transcoder-text-conversion-style transcoder))))
    (cond
      ;; report the error somehow, and/or use substitution character!!!
      ;; error: illegal/unknown, non-8-bit character
      ((eq 'nil spec) #uFFFF)
      ((wide-character-p spec)
       spec)
      (t #uFFFF))))





;;;; Defining Graphic Character Sets



;;;
;;; A `graphic character set' as a concept is defined in the ISO 2022 standard,
;;; and so this description gives a bit of theoretical and practical background.
;;; This does not completely explain everything.  For further information, the
;;; ISO 2022 is a good guide.  The X Compound Text Encoding document is also an
;;; excellent resource.  It's included in X release documentation, and is also
;;; found in _X Window System_, by Robert W. Scheifler & James Gettys, Third
;;; Edition, 1992, Appendix 1, page 889.
;;;
;;; A graphic character set can have either n^m elements, where n is either 94
;;; or 96, and m is either 1, 2, 3, or 4.  The m=1 case is known as the case of
;;; a single-byte character set.  The m=2 case is known as the case of a
;;; double-byte character set.  For our purposes, we do not consider further the
;;; cases where m=3 or m=4, and we note that they are not in common use.

(def-structure graphic-character-set        ; according to ISO 2022
  (graphic-character-set-name 'iso-646)
  (graphic-character-set-synonyms '(iso-646-irv ascii us-ascii))
  (graphic-character-set-n-octets 1)
  (graphic-character-set-characters-per-octet 94)
  (graphic-character-set-registration-sequence #w"A") ; a wide string; {I} F
                                               
  (graphic-character-set-8859-part-number? nil)) ; true for 8859 parts 1-10


(def-global-property-name graphic-character-set)



;;; `Def-graphic-character-set' ...
;;;
;;; Args:
;;;
;;;    (1) name/inheritance;
;;;    (2) N Octets;
;;;    (3) number of defined octets (94 or 96);
;;;    (4) registration sequence: nil for an abstract set; otherwise, a wide
;;;        string containing the 0 or more Intermediate characters and one
;;;        final character registered as the official ISO registration
;;;        sequence for this character set;
;;;    (5) list of synonyms for name; (the rest) new slots, if
;;;        :ABSTRACT, or otherwise initialization overrides.

(defmacro def-graphic-character-set
    (name-etc n-octets characters-per-octet registration-sequence synonyms
              &rest additional-slot-descriptions)
  (let ((name (first name-etc))
        (abstract-p (memq ':abstract (cdr name-etc))))
    (when (and (not abstract-p)
               (not (wide-string-p registration-sequence)))
      (cerror "Continue, using the bad data anyway"
              "~s is not a wide string, so it's not a valid registration sequence for ~a"
              registration-sequence
              name))
    `(progn
       (def-structure
           (,name
              (:include
                ,(if (or (null (second name-etc))
                         (eq (second name-etc) :abstract))
                     'graphic-character-set
                     (second name-etc))
                (graphic-character-set-name
                  ',(first name-etc))
                (graphic-character-set-synonyms
                  ',synonyms)
                (graphic-character-set-n-octets
                  ',n-octets)
                (graphic-character-set-characters-per-octet
                  ',characters-per-octet)
                (graphic-character-set-registration-sequence
                  ',registration-sequence)
                ,@(if (not (eq (second name-etc) ':abstract))
                      additional-slot-descriptions)))
         ,@(if abstract-p additional-slot-descriptions))
       (setf (graphic-character-set ',name)
             (,(build-ab-symbol 'make name)))
       (loop for synonym in ',synonyms
             do (setf (graphic-character-set synonym)
                      (graphic-character-set ',name)))
       ',name)))



;;; The `map-code-to-unicode' generic structure method on graphic character set
;;; structures returns either a unicode character corresponding to code, with
;;; respect to the particular graphic character set, or else nil if no mapping
;;; is possible.

(def-generic-structure-method map-code-to-unicode
    (graphic-character-set code))

;; Consider renaming "to-unicode-character"!


;;; `Map-unicode-to-code-if-any' either returns the code position of
;;; unicode-wide-character in the given graphic character set, or nil to
;;; indicate that no mapping is available or known.
;;;
;;; For single-byte character sets (e.g., ASCII, ISO Latin-1, etc.), this is a
;;; number betweeen 32 and 128.  It should therefore be offset by either 0,
;;; i.e., if it is to be used as a 7-bit character (GL in the ISO 2022
;;; framework), or by #x80, i.e., if it is to be used as an 8-bit character (GR
;;; in the ISO 2022 framework).
;;;
;;; For double-byte character sets (e.g., JIS-X-0208, KS-C-5601, etc.), this
;;; encodes the first byte (the lead byte) as the most significant byte
;;; (leftmost 8 bits), and the second byte (the trail byte) as the least
;;; significant (rightmost 8 bits).  In a double-byte character set, the lead
;;; byte minus #x20 is an index into a vector of 94 or 96 rows; the trail byte
;;; minus #x20 is a column index, that is an index into that row of 94 or 96
;;; actual graphic characters.

(def-generic-structure-method map-unicode-to-code-if-any
    (graphic-character-set unicode-wide-character))





;;;; Defining Character Encodings



(def-global-property-name transcoder-creation-function)

(defmacro def-character-set-encoding
    (name (&key synonyms) &body body-that-creates-transcoder)
  (let ((function-name (build-ab-symbol 'create-transcoder-for name)))
    `(progn (defun ,function-name ()
              . ,body-that-creates-transcoder)
            (setf (transcoder-creation-function ',name)
                  ',function-name)
            (loop for synonym in ',synonyms
                  do (setf (transcoder-creation-function synonym)
                           ',function-name))
            ',name)))





;;;; Character Sets


(def-graphic-character-set (iso-646) 1 94 #w"B"
                           (iso-646-irv ascii us-ascii ansi3.4))

(def-structure-method map-code-to-unicode (iso-646 code)
  (declare (ignore iso-646))
  (code-wide-character code))

(def-structure-method map-unicode-to-code-if-any
    (iso-646 unicode-wide-character)
  (declare (ignore iso-646))
  (if (char<=w #u0020 unicode-wide-character #u007F)
      (wide-character-code unicode-wide-character)))



(def-graphic-character-set (iso-8859-abstract :abstract)
    ;; the suffix "-abstract" is there mainly to keep make-iso-8859-1 from
    ;; being defined as the (internal) name of the maker function!
    1 96 nil nil
    (8859-part-number nil)  ; to be filled in
    (8859-unicode-map nil) ; to be filled in if table lookup method is to be used
    (8859-reverse-unicode-map nil))

(def-structure-method map-code-to-unicode (iso-8859-abstract code)
  (charw (8859-unicode-map iso-8859-abstract) code))


(def-hash-table 8859-reverse-unicode-map
  ;; NOTE: we need to prevent the use of skip list here, because current module
  ;; is loaded before UTILITIES3 and G2-RANDOM is not defined at all. Also, the
  ;; unicode map is not modified at runtime, therefore the tree is thread-safe.
  ;; -- Chun Tian (binghe), May 12, 2014.
  :use-binary-tree t)

(def-structure-method map-unicode-to-code-if-any
    (iso-8859-abstract unicode-wide-character)
  (get-8859-reverse-unicode-map
    unicode-wide-character
    (8859-reverse-unicode-map iso-8859-abstract)))


(def-graphic-character-set (iso-8859-1 iso-8859-abstract)
    1 96 #w"A" (Latin-1)
    (8859-part-number 1))


(def-graphic-character-set (iso-8859-2 iso-8859-abstract)
    1 96 #w"B" (Latin-2)
    (8859-part-number 2))


(def-graphic-character-set (iso-8859-3 iso-8859-abstract)
    1 96 #w"C" (Latin-3)
    (8859-part-number 3))


(def-graphic-character-set (iso-8859-4 iso-8859-abstract)
    1 96 #w"D" (Latin-4)
    (8859-part-number 4))


(def-graphic-character-set (iso-8859-5 iso-8859-abstract)
    1 96 #w"L" (Latin-Cyrillic)
    (8859-part-number 5))


(def-graphic-character-set (iso-8859-6 iso-8859-abstract)
    1 96 #w"G" (Latin-Arabic)
    (8859-part-number 6))


(def-graphic-character-set (iso-8859-7 iso-8859-abstract)
    1 96 #w"F" (Latin-Greek)
    (8859-part-number 7))


(def-graphic-character-set (iso-8859-8 iso-8859-abstract)
    1 96 #w"H" (Latin-Hebrew)
    (8859-part-number 8))


(def-graphic-character-set (iso-8859-9 iso-8859-abstract)
    1 96 #w"M" (Latin-5)
    (8859-part-number 9))


(def-graphic-character-set (iso-8859-10 iso-8859-abstract)
    1 96 #w"D"                                ; reg. unknown; as Latin-4 for now!
    (Latin-6)
    (8859-part-number 10))

;; See ISO8859.lisp for the setup of the maps for parts 2, 3, 4, 6, 7, 8, and
;; 10, and the override methods for the other parts.



(def-graphic-character-set (asian-double-byte :abstract)
    2 94 nil nil
    ;; on nonrefined subtypes, to be filled in with a simple vector while
    ;; elements are either nil (for empty rows) or wide strings mapping
    ;; columns in this row to corresponding Unicode characters (#uFFFF should
    ;; be used to mean "unassigned")
    (asian-double-byte-code-map nil))

(def-structure-method map-code-to-unicode (asian-double-byte code)
  #+development
  (unless (asian-double-byte-code-map asian-double-byte)
    (cerror
      "Continue, in error, as in production"
      "The asian-double-byte-code-map must be present, or this method needs to be refined!"))
  (let* ((row (-f (double-byte-lead-octet code) #x20))
         (column (-f (double-byte-trail-octet code) #x20)))
    (declare (type fixnum row column))
    (let ((row-map? (svref (asian-double-byte-code-map asian-double-byte) row)))
      (if row-map? (charw row-map? column)))))



(def-graphic-character-set (jis-x-0208 asian-double-byte) 2 94 #w"B" (JIS))

;; X Compound Text specified JIS-x-0208-1983, but the handling is identical with
;; jis-x-0208 for our purposes, as well as for the overwhelming majority of
;; applications.

(def-structure-method map-code-to-unicode (jis-x-0208 code)
  (declare (ignore jis-x-0208))
  (code-wide-character (or (map-JIS-X-0208-to-unicode code) #xFFFF)))

(def-structure-method map-unicode-to-code-if-any
    (jis-x-0208 unicode-wide-character)
  (declare (ignore jis-x-0208))
  (map-unicode-to-JIS-X-0208
    (wide-character-code unicode-wide-character)))

(def-graphic-character-set (ks-c-5601 asian-double-byte) 2 94 #w"C" (KS KSC))

(def-structure-method map-code-to-unicode (ks-c-5601 code)
  (declare (ignore ks-c-5601))
  (code-wide-character (or (map-ks-c-5601-to-unicode code) #xFFFF)))

(def-structure-method map-unicode-to-code-if-any
    (ks-c-5601 unicode-wide-character)
  (declare (ignore ks-c-5601))
  (map-unicode-to-KS-C-5601
    (wide-character-code unicode-wide-character)))

(def-graphic-character-set (gb-2312 asian-double-byte) 2 94 #w"C" (GB GB2312))

(def-structure-method map-code-to-unicode (gb-2312 code)
  (declare (ignore gb-2312))
  (code-wide-character (or (map-gb-2312-to-unicode code) #xFFFF)))

(def-structure-method map-unicode-to-code-if-any
    (gb-2312 unicode-wide-character)
  (declare (ignore gb-2312))
  (map-unicode-to-GB-2312
    (wide-character-code unicode-wide-character)))











;;;; ISO 8859 Transcoder



(def-structure (iso-8859-transcoder
                 (:include transcoder)
                 (:constructor
                   make-iso-8859-transcoder
                   (iso-8859-part-number
                     iso-8859-graphic-character-set)))
  iso-8859-part-number                        ; legal values: 1-10
  iso-8859-graphic-character-set)        ; graphic char. set substructure


;;; The `transcode-character for iso-8859-transcoder' method translates ISO
;;; 8859-X into Unicode.  Note that ISO 2022 escapes are not handled.

(def-structure-method transcode-character (iso-8859-transcoder)
  (let* ((transcoder iso-8859-transcoder)
         (character (get-transcoder-character transcoder)))
    (declare (type wide-character character))
    (cond
      ((char<w character #u0020)        ; Control range
       (transcode-control-character character transcoder))
      ((char<w character #u0080)        ; ASCII range
       character)
      ((char<=w #u00A0 character #u00FF) ; ISO 8859 Range
       (or (map-code-to-unicode
             (iso-8859-graphic-character-set transcoder)
             (-f (wide-character-code character) #x80))
           (transcode-unhandled-character character transcoder)))
      (t
       (transcode-unhandled-character character transcoder)))))



(def-structure-method export-character (iso-8859-transcoder)
  (let* ((transcoder iso-8859-transcoder)
         (character (get-transcoder-character transcoder)))
    (declare (type wide-character character))
    (cond
      ((or (char<w character #u0020)        ; Control range
           (char=w character #.%line-separator)        ; line/para separator characters
           (char=w character #.%paragraph-separator))
       (export-control-character character transcoder))
      ((char<w character #u00A0)
       character)
      (t
       (let ((code?
               (map-unicode-to-code-if-any
                 (iso-8859-graphic-character-set transcoder)
                 character)))
         (or (if code? (char+w #u0080 code?))
             (transcode-unhandled-character character transcoder)))))))





;;;; ISO 2022 Transcoder



(def-structure (iso-2022-transcoder (:include transcoder))
  (iso-2022-8-bit-environment-p t)        ; true => 8-bit; nil => 7-bit

  ;; You _designate_ a character set into G0, G1, G2, and G3:
  (iso-2022-G0-designation (graphic-character-set 'iso-646))
  (iso-2022-G1-designation (graphic-character-set 'iso-8859-1))
  (iso-2022-G2-designation nil)                ; undesignated by default
  (iso-2022-G3-designation nil)                ; undesignated by default

  ;; You _invoke_ a Gn character set into GL and GR:
  (iso-2022-GL-invocation                ; invoked from G0
    (graphic-character-set 'iso-646))
  (iso-2022-GR-invocation                ; invoked from G1
    (graphic-character-set 'iso-8859-1))
  (character-set-selection-list nil))        ; MUST be filled in




(def-character-set-encoding iso-646
    (:synonyms (us-ascii iso-646-irv ascii ansi3.4))
  (let ((tc (make-iso-2022-transcoder)))
    (set-up-iso-2022-transcoder-for-us-ascii tc)
    tc))

(def-character-set-encoding iso-2022
    (:synonyms (x-compound-text))
  (let ((tc (make-iso-2022-transcoder)))
    (set-up-iso-2022-transcoder-for-x-compound-text tc)
    tc))

(def-character-set-encoding jis-x-0208
    (:synonyms (JIS))
  (let ((tc (make-iso-2022-transcoder)))
    (set-up-iso-2022-transcoder-for-jis-x-0208 tc)
    tc))

(def-character-set-encoding jis-x-0208-euc
    (:synonyms (JIS-EUC))
  (let ((tc (make-iso-2022-transcoder)))
    (set-up-iso-2022-transcoder-for-jis-x-0208-euc tc)
    tc))

(def-character-set-encoding shift-jis-x-0208
    (:synonyms (MS-kanji shift-jis))
  (let ((tc (make-shift-jis-transcoder-function)))
    tc))


(def-character-set-encoding ks-c-5601
    (:synonyms (ks ksc))
  (let ((tc (make-iso-2022-transcoder)))
    (set-up-iso-2022-transcoder-for-ks-c-5601 tc)
    tc))

(def-character-set-encoding ks-c-5601-euc
    (:synonyms (ks-euc ksc-euc))
  (let ((tc (make-iso-2022-transcoder)))
    (set-up-iso-2022-transcoder-for-ks-c-5601-euc tc)
    tc))

(def-character-set-encoding gb-2312
    (:synonyms (gb gb2312))
  (let ((tc (make-iso-2022-transcoder)))
    (set-up-iso-2022-transcoder-for-gb-2312 tc)
    tc))

(def-character-set-encoding gb-2312-euc
    (:synonyms (gb-euc gb2312-euc))
  (let ((tc (make-iso-2022-transcoder)))
    (set-up-iso-2022-transcoder-for-gb-2312-euc tc)
    tc))



;;; `read-iso-2022-escape-from-wide-string' returns one of the following
;;; symbols, at present.  The list is likely to grow.
;;;
;;;     nil -- unrecognized escape
;;;
;;; Examples:
;;;
;;;     ISO-646
;;;     ISO-8859-1
;;;     ISO-8859-5
;;;     JIS-X-0208
;;;     KS-C-5601
;;;     GB-2312
;;;
;;; The set of supported escape sequences is defined in module ISO2022.

(defmacro read-iso-2022-escape-from-wide-string-macro (string index)
  (avoiding-variable-capture (string index &aux forward-index)
    `(let (,forward-index)
       (cond
         ,@(loop for (escape-sequence charset invocation-side)
                     in all-supported-2022-escape-sequences
                 collect `((progn
                             (setq ,forward-index ,index)
                             (match-2022-escape-ahead
                               ',escape-sequence ,string ,forward-index))
                           (values ',charset ,forward-index ',invocation-side)))
         ;; evaluate STRING to avoid a bound-but-not-referenced warning
         ;; in the case where there are no supported-2022-escape-sequences
         (t ,string (values nil ,index))))))

;; NOTE: ext/c/transcode.c, and variations forked off by the Database bridges
;; group, define a similar function with a similar name:
;; read_2022_escape_from_wide_string.  If we defined a function with that name
;; (but hyphens instead of underscores), we'd create a conflict.  (MHD 2/5/96)

(defun read-iso-2022-escape-from-wide-string (string index)
  #+lispworks4
  (cerror "Return nil"
          "read-iso-2022-escape-from-wide-string is too big!!!")
  #-lispworks4
  (read-iso-2022-escape-from-wide-string-macro string index))



;; `Handle-iso-2022-escape' ... This is a hack version for now; we just want to
;; handle the straightforward Japanese, and Korean 7-bit encodings, since these
;; are the only things we need to support that require changes to the
;; transcoder's slot in the middle via escape sequences.  This requires handling
;; setting ASCII as G0, i.e., when returning from J or K.
;;
;; Later, we can implement a general ISO 2022 escape sequence parser.  Also, for
;; lack of anything better to do, this sets both the current and previous
;; character of the transcoder to #uFFFF ("nothing").

(defun-void handle-iso-2022-escape (iso-2022-transcoder)
  (let ((transcoder iso-2022-transcoder))
    (let ((text-sequence (transcoder-text-sequence transcoder)))
      (multiple-value-bind (graphic-character-set-name forward-index invocation-side)
          (read-iso-2022-escape-from-wide-string
            (text-sequence-string text-sequence)
            (text-sequence-string-index text-sequence))
        (loop repeat (-f
                       forward-index
                       (text-sequence-string-index text-sequence))
              do (get-transcoder-character transcoder))
        (let ((graphic-character-set?
                (graphic-character-set graphic-character-set-name)))
          (cond
            (graphic-character-set?
             (case invocation-side
               (left (setf (iso-2022-GL-invocation transcoder)
                           graphic-character-set?))
               (right (setf (iso-2022-GR-invocation transcoder)
                           graphic-character-set?))
               #+development
               (t (error "bad invocation side value: ~a" invocation-side))))
            #+development
            (t
             (warn "Developer Note: Unknown or unhandled character set name: ~a"
                   graphic-character-set-name))))))
    ;; Avoid having random contents there for this side-effecting operation
    (setf (transcoder-previous-character transcoder) #uFFFF)
    (setf (transcoder-character transcoder) #uFFFF)))




;;; `Invoke-graphic-character-set-if-necessary' enqueues an escape sequence
;;; appropriate for the argument set, a graphic character set structure, in the
;;; specified ISO 2022 transcoder, for the specified invocation side, which
;;; should be either LEFT (7-bit characters) or RIGHT (8-bit characters).

(defun-substitution-macro invoke-graphic-character-set-if-necessary
    (set iso-2022-transcoder invocation-side)
  (macrolet ((nq (x)
               `(enqueue-pending-transcoder-character
                  iso-2022-transcoder ,x))
             (nq-registration-sequence ()
               `(loop with i = 0
                      with string
                        = (graphic-character-set-registration-sequence set)
                      do (nq (charw string i))
                         (incff i)
                      while (<f i (wide-string-length string)))))
    (case invocation-side
      (left
       (unless (eq set (iso-2022-GL-invocation iso-2022-transcoder))
         (setf (iso-2022-GL-invocation iso-2022-transcoder) set)
         (nq #.%escape)
         (when (>f (graphic-character-set-n-octets set) 1)
           (nq #.%\$))
         (nq #.%\()
         (nq-registration-sequence)))
      (right
       (unless (eq set (iso-2022-GR-invocation iso-2022-transcoder))
         (setf (iso-2022-GR-invocation iso-2022-transcoder) set)
         (nq #.%escape)
         (cond
           ((=f (graphic-character-set-characters-per-octet set) 94)
            (when (>f (graphic-character-set-n-octets set) 1)
              (nq #.%\$))
            (nq #.%\)))
           (t
            (nq #.%\-)))
         (nq-registration-sequence))))))





;;; The iso-2022 transcoder set up for x-compound-text implements
;;; X-Compound-Text compliant processing of character for supported character
;;; sets.  At present, the supported character sets are ISO-8859 (parts 1-10),
;;; ISO-646 (US-ASCII), KS-C-5601-1987 (Korean), and JIS-X-0208-1983 (Japanese).
;;; Note that GB2312-1980 (China (PRC) Hanzi) is unfortunately not yet handled
;;; at this time.  This is a known deficiency.  -- UPDATE: GB2312-1980 will now
;;; be handled in the current release pending 4/9/99. (MHD 4/9/99)
;;;
;;; There may be ambiguity as to which character set to choose, since some
;;; characters in Unicode reside in more than one of the above character sets.
;;; This has a partially fixed and partially parameterized priority scheme for
;;; choosing, as follows:
;;;
;;;     (1) ISO-646;
;;;     (2-11) ISO-8859, Parts 1-10 in that order;
;;;     (12-14) JIS-X-0208, KS-C-5601, GB-2312, if han unification
;;;             mode is Japanese, and an appropriate other order if
;;;             it's Chinese or Korean

;;       -- UPDATE: Revised for Chinese! (MHD 4/9/99)
;;;
;;; This does not generally do mapping to the control ranges; that is,
;;; processing of line breaks and tabs should be done prior to using
;;; this.
;;;
;;; This returns as its sole value the value to be returned from the
;;; export-character method.

(def-concept x-compound-text)

;; NOTE: X Compound Text is still not handled quite right: it should only put
;; out LF for a line break; nothing else is allowed.  However, that's not right
;; for other uses of the export-character method above, e.g., for general
;; xxx-euc Asian output, say, on a PC with a CRLF requirement.  So, there should
;; be subclassing of the iso-2022 transcoder for the various purposes.  In
;; practice, however, this will work in most cases, and we and our users can
;; probably get by for the immediate future. (MHD 5/20/97)


(defparameter no-han-x-compound-text-character-set-selection-list
  `((,(graphic-character-set 'iso-646) left)
    (,(graphic-character-set 'iso-8859-1) right)
    (,(graphic-character-set 'iso-8859-2) right)
    (,(graphic-character-set 'iso-8859-3) right)
    (,(graphic-character-set 'iso-8859-4) right)
    (,(graphic-character-set 'iso-8859-5) right)
    (,(graphic-character-set 'iso-8859-6) right)
    (,(graphic-character-set 'iso-8859-7) right)
    (,(graphic-character-set 'iso-8859-8) right)
    (,(graphic-character-set 'iso-8859-9) right)
    (,(graphic-character-set 'jis-x-0208) left)
    (,(graphic-character-set 'ks-c-5601) left)
    (,(graphic-character-set 'gb-2312) left)))

(defparameter japanese-han-x-compound-text-character-set-selection-list
  `(,@no-han-x-compound-text-character-set-selection-list
    (,(graphic-character-set 'jis-x-0208) left)
    (,(graphic-character-set 'ks-c-5601) left)
    (,(graphic-character-set 'gb-2312) left)))

(defparameter korean-han-x-compound-text-character-set-selection-list
  `(,@no-han-x-compound-text-character-set-selection-list
    (,(graphic-character-set 'ks-c-5601) left)
    (,(graphic-character-set 'jis-x-0208) left)
    (,(graphic-character-set 'gb-2312) left)))

(defparameter chinese-han-x-compound-text-character-set-selection-list
  `(,@no-han-x-compound-text-character-set-selection-list
    (,(graphic-character-set 'gb-2312) left)
    (,(graphic-character-set 'jis-x-0208) left)
    (,(graphic-character-set 'ks-c-5601) left)))

(defparameter default-han-x-compound-text-character-set-selection-list
  japanese-han-x-compound-text-character-set-selection-list)

(defmacro choose-selection-list-per-han-unification-mode (mode)
  `(case ,mode
     (japanese japanese-han-x-compound-text-character-set-selection-list)
     (korean korean-han-x-compound-text-character-set-selection-list)
     (chinese chinese-han-x-compound-text-character-set-selection-list)
     (t default-han-x-compound-text-character-set-selection-list)))

(declare-forward-reference                ; a ref. later this file
  text-conversion-style-for-transcoder-being-created
  variable)

(defun-void set-up-iso-2022-transcoder-for-x-compound-text (transcoder)
  (setf (character-set-selection-list transcoder)
        (choose-selection-list-per-han-unification-mode
          (transcode-han-unification-mode
            text-conversion-style-for-transcoder-being-created))))




(defparameter us-ascii-character-set-selection-list
  `((,(graphic-character-set 'iso-646) left)))

(defun-void set-up-iso-2022-transcoder-for-us-ascii (transcoder)
  (setf (character-set-selection-list transcoder)
        us-ascii-character-set-selection-list)
  (setf (iso-2022-8-bit-environment-p transcoder) nil)
  (setf (iso-2022-G0-designation transcoder)
        (graphic-character-set 'iso-646))
  (setf (iso-2022-GL-invocation transcoder)
        (iso-2022-G0-designation transcoder)))

;;; The Asian 7-bit double-byte character sets use an iso-2022-transcoder whose
;;; primary encoding is a 7-bit Asian encoding, The characteristics of this form
;;; of the transcoder are: no use of GR permitted.  Must swap G0 (ascii,
;;; single-byte) and G1 (asian, double-byte) into GL.  Use of G3 and G4 are not
;;; handled for now; that can be done later -- they should be done using single
;;; shifts (SS1 and SS2 escapes).

;;; The Asian 8-bit double-byte character sets use an iso-2022-transcoder whose
;;; primary encoding is a 7-bit Asian encoding, The characteristics of this form
;;; of the transcoder are: Use of G3 and G4 are not handled for now; that can be
;;; done later -- they should be done using single shifts (SS1 and SS2 escapes).

(defparameter ks-c-5601-character-set-selection-list
  `((,(graphic-character-set 'iso-646) left)
    (,(graphic-character-set 'ks-c-5601) left)))

(defun-void set-up-iso-2022-transcoder-for-ks-c-5601 (transcoder)
  (setf (character-set-selection-list transcoder)
        ks-c-5601-character-set-selection-list)
  (setf (iso-2022-8-bit-environment-p transcoder) nil)
  (setf (iso-2022-G0-designation transcoder)
        (graphic-character-set 'ISO-646))
  (setf (iso-2022-G1-designation transcoder)
        (graphic-character-set 'ks-c-5601))
  (setf (iso-2022-GR-invocation transcoder)
        (iso-2022-G0-designation transcoder)))

(defparameter ks-c-5601-euc-character-set-selection-list
  `((,(graphic-character-set 'iso-646) left)
    (,(graphic-character-set 'ks-c-5601) right)))

(defun-void set-up-iso-2022-transcoder-for-ks-c-5601-euc (transcoder)
  (setf (character-set-selection-list transcoder)
        ks-c-5601-euc-character-set-selection-list)
  (setf (iso-2022-8-bit-environment-p transcoder) t)
  (setf (iso-2022-G0-designation transcoder)
        (graphic-character-set 'ISO-646))
  (setf (iso-2022-g1-designation transcoder)
        (graphic-character-set 'ks-c-5601))
  (setf (iso-2022-GL-invocation transcoder)
        (iso-2022-G0-designation transcoder))
  (setf (iso-2022-GR-invocation transcoder)
        (iso-2022-G1-designation transcoder)))


(defparameter gb-2312-character-set-selection-list
  `((,(graphic-character-set 'iso-646) left)
    (,(graphic-character-set 'gb-2312) left)))

(defun-void set-up-iso-2022-transcoder-for-gb-2312 (transcoder)
  (setf (character-set-selection-list transcoder)
        gb-2312-character-set-selection-list)
  (setf (iso-2022-8-bit-environment-p transcoder) nil)
  (setf (iso-2022-G0-designation transcoder)
        (graphic-character-set 'ISO-646))
  (setf (iso-2022-G1-designation transcoder)
        (graphic-character-set 'gb-2312))
  (setf (iso-2022-GR-invocation transcoder)
        (iso-2022-G0-designation transcoder)))

(defparameter gb-2312-euc-character-set-selection-list
  `((,(graphic-character-set 'iso-646) left)
    (,(graphic-character-set 'gb-2312) right)))

(defun-void set-up-iso-2022-transcoder-for-gb-2312-euc (transcoder)
  (setf (character-set-selection-list transcoder)
        gb-2312-euc-character-set-selection-list)
  (setf (iso-2022-8-bit-environment-p transcoder) t)
  (setf (iso-2022-G0-designation transcoder)
        (graphic-character-set 'ISO-646))
  (setf (iso-2022-g1-designation transcoder)
        (graphic-character-set 'gb-2312))
  (setf (iso-2022-GL-invocation transcoder)
        (iso-2022-G0-designation transcoder))
  (setf (iso-2022-GR-invocation transcoder)
        (iso-2022-G1-designation transcoder)))


(defparameter jis-x-0208-character-set-selection-list
  `((,(graphic-character-set 'iso-646) left)
    (,(graphic-character-set 'jis-x-0208) left)))

(defun-void set-up-iso-2022-transcoder-for-jis-x-0208 (transcoder)
  (setf (character-set-selection-list transcoder)
        jis-x-0208-character-set-selection-list)
  (setf (iso-2022-8-bit-environment-p transcoder) nil)
  (setf (iso-2022-G0-designation transcoder)
        (graphic-character-set 'ISO-646))
  (setf (iso-2022-G1-designation transcoder)
        (graphic-character-set 'jis-x-0208))
  (setf (iso-2022-GR-invocation transcoder)
        (iso-2022-G0-designation transcoder)))

(defparameter jis-x-0208-euc-character-set-selection-list
  `((,(graphic-character-set 'iso-646) left)
    (,(graphic-character-set 'jis-x-0208) right)))

(defun-void set-up-iso-2022-transcoder-for-jis-x-0208-euc (transcoder)
  (setf (character-set-selection-list transcoder)
        jis-x-0208-euc-character-set-selection-list)
  (setf (iso-2022-8-bit-environment-p transcoder) t)
  (setf (iso-2022-G0-designation transcoder)
        (graphic-character-set 'ISO-646))
  (setf (iso-2022-g1-designation transcoder)
        (graphic-character-set 'jis-x-0208))
  (setf (iso-2022-GL-invocation transcoder)
        (iso-2022-G0-designation transcoder))
  (setf (iso-2022-GR-invocation transcoder)
        (iso-2022-G1-designation transcoder)))





(defun-substitution-macro transcode-iso-2022-C0-character (character transcoder)
  (let ((result-character
          (transcode-control-character character transcoder)))
    (wide-character-case
      result-character
      (#.%escape                        ; changes transcoder's slots
         (handle-iso-2022-escape transcoder)
         #uFFFF)                        ; return this value to skip
      ;; handle SI, SO, and others here, too, esp., needed for Korean mail std.!
      (t result-character))))


(defun transcode-iso-2022-C1-character (character transcoder)
  (transcode-unhandled-character character transcoder))



;;; `Transcode-iso-2022-graphic-character' ... Zone should be either
;;; GL or GR.

(defun-simple transcode-iso-2022-graphic-character
    (character transcoder zone)
  (declare (type wide-character character))
  (let ((graphic-character-set
          (if (eq zone 'GL)
              (iso-2022-GL-invocation transcoder)
              ;; else GR
              (iso-2022-GR-invocation transcoder)))
        (text-sequence (transcoder-text-sequence transcoder)))
    (or
      (cond
        ((=f (graphic-character-set-n-octets graphic-character-set) 1)
         (map-code-to-unicode
           graphic-character-set
           (logandf (wide-character-code character) #x7F)))
        ((=f (graphic-character-set-n-octets graphic-character-set) 2)
         (when (text-sequence-has-more-characters-p text-sequence)
           (setf (transcoder-previous-character transcoder)
                 character)
           (setf (transcoder-character transcoder)
                 (read-character-from-text-sequence text-sequence))
           (let ((trail-character
                   (code-wide-character
                     (logandf
                       (wide-character-code (transcoder-character transcoder))
                       #x7F))))
             (if (char<=w #u0020 trail-character #u0080)
                 ;; note: handle both 94 (zone = GL) or 96 (zone = GR) char sets uniformly
                 (map-code-to-unicode
                   graphic-character-set
                   (wide-characters-to-double-byte-code
                     character
                     trail-character)))))))
      (transcode-unhandled-character character transcoder))))




(defun-substitution-macro export-iso-2022-graphic-character (transcoder character)
  (loop with set-selection-list = (character-set-selection-list transcoder)
        with code
        for (set side) in set-selection-list
        when (setq code (map-unicode-to-code-if-any set character))
          do (invoke-graphic-character-set-if-necessary set transcoder side)
             (macrolet
                 ((nq (octet)
                    `(enqueue-pending-transcoder-character
                       transcoder
                       (code-wide-character
                         (if (eq side 'left) ,octet (logiorf ,octet #x80))))))
               (cond
                 ((=f (graphic-character-set-n-octets set) 1)
                  (nq code))
                 (t                        ; n must be 2
                  (nq (double-byte-lead-octet code))
                  (nq (double-byte-trail-octet code)))))
             (return #uFFFF)
        finally
          (return
            (transcode-unhandled-character character transcoder))))



;;; The `transcode-character for iso-2022-transcoder' method translates
;;; a character in an ISO-2022-encoded text sequence.  It is intended
;;; to handle arbitrary general escape sequences, but it only handles
;;; a few at this time.  Its main value is that it interprets the state
;;; in the iso-2022-transcoder structure, which can handle most of the
;;; structures defined by ISO 2022. ...

(def-structure-method transcode-character (iso-2022-transcoder)
  (let* ((transcoder iso-2022-transcoder)
         (character (get-transcoder-character transcoder)))
    (declare (type wide-character character))
    (cond
      ((char<w character #u0020)        ; C0 (Control) range
       (transcode-iso-2022-C0-character
         character
         transcoder))
      ((char<w character #u0080)        ; GL range (usually ASCII)
       (transcode-iso-2022-graphic-character
         character
         transcoder 'GL))
      (t
       (or (if (iso-2022-8-bit-environment-p transcoder)
               (cond
                 ((char<w character #u00A0)        ; C1 (Control) range (2nd, unused)
                  (transcode-iso-2022-C1-character
                    character transcoder))
                 ((char<w character #u0100)        ; GR range (usually ISO 8859)
                  (transcode-iso-2022-graphic-character
                    character transcoder 'GR))))
           (transcode-unhandled-character character transcoder))))))

(def-structure-method export-character (iso-2022-transcoder)
  (let* ((transcoder iso-2022-transcoder)
         (character (get-transcoder-character transcoder)))
    (declare (type wide-character character))
    (cond
      ((or (char<w character #u0020)        ; Control range
           (char=w character #.%line-separator)        ; line/para separator characters
           (char=w character #.%paragraph-separator)
           (char=w character #u007F)
           (char<w #u007F character #u00A0))
       (when (newline-p character)        ; see note
         (invoke-graphic-character-set-if-necessary
           (graphic-character-set 'iso-646)
           transcoder
           'left))
       (export-control-character character transcoder))
      (t
       (export-iso-2022-graphic-character transcoder character)))))

;; Assume that C0/C1 are immutable, and is OK for sending controls, both low
;; (C0) and high (C1), including line breaks; It is recommended (e.g., by Ken
;; Lunde in "UJIP") to switch to ASCII before newline.  I don't think it's an
;; ISO 2022 requirement, but we now do this.  NOTE: we don't do this at EOF.
;; Should we?  (MHD 6/4/97)


;;;; Shift-JIS Transcoder



;;; The `transcode-character for shift-jis-transcoder' method translates a
;;; character in Shift-JIS- (aka MS Kanji-) encoded text sequence.
;;;
;;; Note that Shift-JIS is not really compliant with the ISO 2022 standard.

(def-structure (shift-jis-transcoder (:include transcoder))
  (shift-jis-double-byte-character-set        ; always holds the JIS-x-0208 character set
    (graphic-character-set 'jis-x-0208))
  ;; in inheriting variant structures, could add proprietary double-byte
  ;; character sets here, and revise code slightly to use it!
  )

(defun make-shift-jis-transcoder-function ()
  (make-shift-jis-transcoder))                ; exists so you can forward reference it
                                        ;   as an alternative to using the macro
                                        ;   version.


;;; `Set-octets-shift-jis-to-jis' replaces the values of lead-octet-var and
;;; trail-octet-var, which must be evaluable any number of times and setf'able,
;;; and which must evaluate to lead and trail shift-JIS octets, with their
;;; corresponding lead and trail JIS octets.  No useful value is returned.

(defmacro set-octets-shift-jis-to-jis (lead-octet-var trail-octet-var)
  (avoiding-variable-capture (&aux c1 c2 adjust-p row-offset cell-offset)
    `(let* ((,c1 ,lead-octet-var)
            (,c2 ,trail-octet-var)
            (,adjust-p (<f ,c2 159))
            (,row-offset (if (<f ,c1 160) 112 176))
            (,cell-offset
               (if ,adjust-p
                   (if (>f ,c2 127) 32 31)
                   126)))
       (setf ,lead-octet-var
             (-f (ashf (-f ,c1 ,row-offset) 1)
                 (if ,adjust-p 1 0)))
       (setf ,trail-octet-var (-f ,trail-octet-var ,cell-offset))
       nil)))

(defmacro set-octets-jis-to-shift-jis (lead-octet-var trail-octet-var)
  (avoiding-variable-capture (&aux c1 c2 row-offset cell-offset)
    `(let* ((,c1 ,lead-octet-var)
            (,c2 ,trail-octet-var)
            (,row-offset (if (<f ,c1 95) 112 176))
            (,cell-offset
               (if (oddp (the fixnum ,c1))
                   (if (>f ,c2 95) 32 31)
                   126)))
       (setf ,lead-octet-var (+f (ashf (+f ,c1 1) -1) ,row-offset))
       (setf ,trail-octet-var (+f ,trail-octet-var ,cell-offset))
       nil)))

;; Above two macros adapted from the following public domain C code, found in
;; jconv.c, written by Ken Lunde, author of Understanding Japanese Information
;; Processing (UJIP).
;;
;; void sjis2jis(int *p1, int *p2)
;; {
;;   unsigned char c1 = *p1;
;;   unsigned char c2 = *p2;
;;   int adjust = c2 < 159;
;;   int rowOffset = c1 < 160 ? 112 : 176;
;;   int cellOffset = adjust ? (c2 > 127 ? 32 : 31) : 126;

;;   *p1 = ((c1 - rowOffset) << 1) - adjust;
;;   *p2 -= cellOffset;
;; }
;;
;; void jis2sjis(int *p1, int *p2)
;; {
;;   unsigned char c1 = *p1;
;;   unsigned char c2 = *p2;
;;   int rowOffset = c1 < 95 ? 112 : 176;
;;   int cellOffset = c1 % 2 ? (c2 > 95 ? 32 : 31) : 126;
;;
;;   *p1 = ((c1 + 1) >> 1) + rowOffset;
;;   *p2 += cellOffset;
;; }


(def-structure-method transcode-character (shift-jis-transcoder)
  (let* ((transcoder shift-jis-transcoder)
         (character (get-transcoder-character transcoder)))
    (declare (type wide-character character))
    (cond
      ((char<w character #u0020)        ; C0 (Control) range
       (transcode-iso-2022-C0-character character transcoder))
      ((char<w character #u0080)        ; ASCII/JIS-Roman, but defer on
       character)                        ;   Yen/Backslash Issue, say it's ASCII!
      ((char<=w #u00A1 character #u00DF)
       ;; single byte range half-width katakana
       (char+w
         #uFF61                                ; first half-width Katakana in Unicode
         (-f (wide-character-code character) #xA1)))
      ((or (or (char<=w #u0081 character #u009F)  ; 2-byte, std char, 1st
               (char<=w #u00E0 character #u00EF)) ;   byte range
           (char<=w #u00F0 character #u00FC)) ; 2-byte, user-defined char, 1st
                                                 ;   byte range
       (block exhausted
         (let* ((lead-character character)
                (trail-character
                  (or (get-transcoder-character-if-any transcoder)
                      (return-from exhausted
                        (transcode-unhandled-character
                          character transcoder))))
                (lead-octet
                  (wide-character-code
                    (char-andw lead-character #u00FF)))
                (trail-octet
                  (wide-character-code
                    (char-andw trail-character #u00FF))))
           (set-octets-shift-jis-to-jis lead-octet trail-octet)
           (let* ((double-byte-code
                    (7-bit-octets-to-double-byte-code lead-octet trail-octet)))
             (map-code-to-unicode
               (shift-jis-double-byte-character-set transcoder)
               double-byte-code)))))
      (t
       ;; Some proprietary single byte encodings ignored; e.g., Apple has #x80 =
       ;; backslash (\), but we skip this kind of thing for now.
       (transcode-unhandled-character character transcoder)))))

(def-structure-method export-character (shift-jis-transcoder)
  (let* ((transcoder shift-jis-transcoder)
         (character (get-transcoder-character transcoder)))
    (declare (type wide-character character))
    (cond
      ((or (char<w character #u0020)        ; Control range
           (char=w character #.%line-separator)        ; line/para separator characters
           (char=w character #.%paragraph-separator)
           (char=w character #u007F)
           (char<w #u007F character #u00A0))
       ;; Assume that C0/C1 are immutable, and is OK for sending controls, both
       ;; low (C0) and high (C1), including line breaks; may be best and/or
       ;; required to "shift out" and/or switch to some other designation (e.g.,
       ;; to ASCII or G0) in certain applications before newline, but I don't
       ;; think it's an ISO 2022 requirement!
       (export-control-character character transcoder))
      ((char<w character #u0080)        ; ASCII/JIS-Roman, but defer on
       character)                        ;   Yen/Backslash Issue, say it's ASCII!
      (t
       (let ((jis-code?
               (map-unicode-to-JIS-X-0208
                 (wide-character-code character))))
         (cond
           (jis-code?
            (let* ((jis-code jis-code?)
                   (lead-octet (double-byte-lead-octet jis-code))
                   (trail-octet (double-byte-trail-octet jis-code)))
              (set-octets-jis-to-shift-jis lead-octet trail-octet)
              (enqueue-pending-transcoder-character
                transcoder
                (code-wide-character trail-octet))
              (code-wide-character lead-octet)))
           (t
            (transcode-unhandled-character character transcoder))))))))

;; Expect problems/complaints with both import/export around backslash (\) and yen sign!
;;
;; Here's mail on the subject:

;; To: Multiple Recipients of <unicode@Unicode.ORG>
;; Reply-To: Joe Ross <joe.ross@tivoli.com>
;; From: "Unicode Discussion" <unicode@Unicode.ORG>
;; Date: Thu, 8 May 1997 08:34:57 -0700 (PDT)
;; Subject: Re: JIS 0x5C <=> U+A5
;;
;; Steve Bossie wrote:
;;
;; > I'm looking for input on the mapping of JIS characters 0x5C and 0x7E to
;; > Unicode.
;; >
;; >
;; > In my case, I chose to map the JIS 0x5C to Unicode U+5C. This enables me
;; > to read old (pre-Unicode) script programs that happen to contain a "\"
;; > without worrying about the mapping. In fact, it appears to make life
;; > easiest if my mappings, I retain all code points 0-127 to map onto
;; > themselves (0-127).
;;
;; I agree completely. This is the default conversion that makes the
;; most sense, and this is also what we are doing. However, our Japanese
;; converters have a modifier which selects a different conversion if
;; the caller wants a "display" interpretation of the 0x5C and 0x7E
;; characters in code page 932.
;;
;; Joe
;;
;; Joe Ross                                          joe.ross@tivoli.com
;; Tivoli Systems Internationalization                     (512)436-8







;;;; UTF-G Transcoder


(def-structure (utf-g-transcoder
                 (:include transcoder))
  (transcoder-previous-gensym-character-code #xFFFF) ; arbitrary, non-extended
  (transcoder-current-gensym-character-code #xFFFF))



(defmacro extended-lead-half-gensym-character-code-p (gensym-character-code)
  `(=f (ashf ,gensym-character-code -8) #xF7))

(defmacro extended-trail-half-gensym-character-code-p (gensym-character-code)
  `(=f (ashf ,gensym-character-code -8) #xF8))



(defun-simple get-utf-g-transcoder-code (character transcoder)
  (declare (type wide-character character))
  (block exhausted
    ;; The local macro get-one either returns the character as
    ;; a wide character, or does a "non-local" return from the
    ;; block.
    (macrolet ((get-one ()
                 `(or (get-transcoder-character-if-any transcoder)
                      (return-from
                        exhausted
                        #xFFFF))))
      (wide-character-case
        character
        ((#.%\@ #.%\~)
         (gensym-character-pair-to-code
           (wide-character-to-character (get-one))
           (wide-character-to-character character)))
        (#.%\\
           (let* ((code (wide-character-code (get-one))))
             (declare (type fixnum code))
             (gensym-character-pair-to-code
               (if (<f code 40)
                   (let ((first-code (wide-character-code (get-one)))
                         (second-code (wide-character-code (get-one))))
                     (let ((result
                             (+f (ashf code 13)
                                 (*f 95 first-code)
                                 second-code
                                 #.(- (+ (ash 32 13) (* 95 40) 32)))))
                       (declare (type fixnum result))
                       (if (not (<=f 0 result #xFFFF))
                           (return-from exhausted #xFFFF)
                           result)))
                   (let ((first-code (wide-character-code (get-one))))
                     (+f (*f 95 code)
                         first-code
                         #.(+ (ash 33 13)
                              (- (+ (ash 32 13) (* 95 40) 32))))))
               (wide-character-to-character character))))
        (t
          (gensym-character-pair-to-code
            (wide-character-to-character character)
            nil))))))

;; Note: the basic formula for interpreting a 3-character \ complex char could
;; result in an illegal negative or 17-bit code with certain illegal byte
;; sequences.  We have to explicitly restrict the code to the range 0..#xFFFF,
;; since this \ complex char has not necessarily been written by a trusted
;; source. See "Important Note" on this topic in the "Kanji Characters (\
;; Complex Characters)" subsection of CHARACTERS. (MHD 5/25/00)


(def-structure-method transcode-character (UTF-G-transcoder)
  (let* ((transcoder UTF-G-transcoder)
         (character (get-transcoder-character transcoder)))
    (declare (type wide-character character))
    (setf (transcoder-previous-gensym-character-code transcoder)
          (transcoder-current-gensym-character-code transcoder))
    (cond
      ((char<w character #u0020)        ; C0 (Control) range
       (setf (transcoder-current-gensym-character-code transcoder)
             #xFFFF)
       (transcode-control-character character transcoder))
      ((char<w character #u0080)        ; GL range (usually ASCII)
       (setf (transcoder-current-gensym-character-code transcoder)
             (get-utf-g-transcoder-code character transcoder))
       (cond
         ((=f (transcoder-current-gensym-character-code transcoder) #xFFFF)
          (transcode-unhandled-character character transcoder))
         ((extended-lead-half-gensym-character-code-p
            (transcoder-previous-gensym-character-code transcoder))
          (cond
            ((extended-trail-half-gensym-character-code-p
               (transcoder-current-gensym-character-code transcoder))
             (let ((current-extended-utf-g-low-half-character?
                     (transcoder-previous-gensym-character-code transcoder)))
               (code-wide-character
                 (map-gensym-character-code-to-unicode
                   (transcoder-current-gensym-character-code transcoder)))))
            (t
             (transcode-unhandled-character character transcoder))))
         ((extended-lead-half-gensym-character-code-p
            (transcoder-current-gensym-character-code transcoder))
          #uFFFF)                        ; wait till the next character
         (t
          (let ((code
                  (map-gensym-character-code-to-unicode
                    (transcoder-current-gensym-character-code
                      transcoder))))
            (if (=f code #xFFFF)
                (transcode-unhandled-character character transcoder)
                (code-wide-character code))))))
      (t
        (setf (transcoder-current-gensym-character-code transcoder)
              #xFFFF)
        (transcode-unhandled-character character transcoder)))))




;;; `Export-utf-g-character-code-as-octets' enqueues in the argument transcoder
;;; the wide characters corresponding to the two or three octets used to
;;; represent a character code following a \ escape character in Gensym UTF-G
;;; character.  This is a submacro of export-utf-g-character.  This returns no
;;; useful values.

(defmacro export-utf-g-character-code-as-octets
    (character-code transcoder)
  (avoiding-variable-capture (character-code transcoder)
    `(let (octet-1? (octet-2 0) (octet-3 0))
       (declare (type fixnum octet-2 octet-3))
       (when (set-octets-from-gensym-character-code
               ,character-code octet-1? octet-2 octet-3)
         (enqueue-pending-transcoder-character
           ,transcoder (code-wide-character octet-1?)))
       (enqueue-pending-transcoder-character
         ,transcoder (code-wide-character octet-2))
       (enqueue-pending-transcoder-character
         ,transcoder (code-wide-character octet-3)))))


;;; `Export-utf-g-character' returns the one wide character, or enqueues the n
;;; wide characters, corresponding to the octets used to encode character, a
;;; Unicode character, as a UTF-Gensym G character.  The result is either the
;;; one character, a valid Unicode character, or the non-character character
;;; #uFFFF, with the queue filled with n characters.  Here, N may be between 2
;;; and 8, inclusive.

(defmacro export-utf-g-character (character transcoder)
  (avoiding-variable-capture (character transcoder)
    `(let (escape-character?
            character-or-character-code
            extended-escape-character?
            extended-character-or-character-code?)
       (set-gensym-character-pairs-from-unicode
         (wide-character-code ,character)
         escape-character?
         character-or-character-code
         extended-escape-character?
         extended-character-or-character-code?)
       (cond
         ((null escape-character?)
          ;; Then character-or-character-code is a wide character, and
          ;; extended-escape-character? and
          ;; extended-character-or-character-code? must be null.
          character-or-character-code)
         (t
          ;; escape-character? is a wide character.
          (enqueue-pending-transcoder-character ,transcoder escape-character?)
          (wide-character-case
            escape-character?
            ((#.%\@ #.%\~)
             ;; Then character-or-character-code is a character, and
             ;; extended-escape-character? and
             ;; extended-character-or-character-code? must be null.
             (enqueue-pending-transcoder-character
               ,transcoder character-or-character-code))
            (t
              ;; Escape-character? is #.%\\, character-or-character-code is a
              ;; code, and extended-escape-character? and
              ;; extended-character-or-character-code? might not be null; if
              ;; they're not, extended-escape-character? must be #.%\\, and
              ;; extended-character-or-character-code? must be a code.
              (export-utf-g-character-code-as-octets
                character-or-character-code ,transcoder)
              (when extended-escape-character?
                (enqueue-pending-transcoder-character
                  ,transcoder extended-escape-character?)
                (export-utf-g-character-code-as-octets
                  extended-character-or-character-code? ,transcoder))))
          #uFFFF)))))



(def-structure-method export-character (utf-g-transcoder)
  (let* ((transcoder utf-g-transcoder)
         (character (get-transcoder-character transcoder)))
    (declare (type wide-character character))
    (cond
      ((or (char=w character #.%linefeed)
           (char=w character #.%return)
           (char=w character #.%tab)        ; Directly encoded Part of Control range; include Formfeed?!
           ;; For now, we're skipping these for compatibility with G2 4.0 & earlier:
;           (char=w character #.%line-separator)        ; line/para separator characters
;           (char=w character #.%paragraph-separator)
           )
       (export-control-character character transcoder))
      ((or (char=w character #.%line-separator)
           (char=w character #.%paragraph-separator))
       (enqueue-pending-transcoder-character transcoder #.%\@)
       (enqueue-pending-transcoder-character
         transcoder
         (if (char=w character #.%line-separator)
             #.%\L
             #.%\P))
       #uFFFF)
      (t
       (export-utf-g-character character transcoder)))))



;;; Prior to G2 5.0, g2-write-line emitted "ascii as much as possible", meaning
;;; ASCII characters as ASCII (i.e., including @, ~, and \), and other
;;; characters in the Gensym encoding, potentially resulting in
;;; ambiguous output.  This transcoder implements that encoding behavior.

(def-structure (utf-g-ascii-as-much-as-possible-transcoder
                 (:include utf-g-transcoder))
  )

(def-structure-method export-character
    (utf-g-ascii-as-much-as-possible-transcoder)
  (let* ((transcoder utf-g-ascii-as-much-as-possible-transcoder)
         (character (get-transcoder-character transcoder)))
    (declare (type wide-character character))
    (cond
      ((or (char=w character #.%linefeed)
           (char=w character #.%return)
           (char=w character #.%tab)        ; Directly encoded Part of Control range; include Formfeed?!
           (char=w character #.%line-separator)
           (char=w character #.%paragraph-separator))
       (export-control-character character transcoder))
      ((or (char=w character #.%\@)
           (char=w character #.%\\)
           (char=w character #.%\~))
       character)
      (t
       (export-utf-g-character character transcoder)))))





;;;; Unicode UCS-2 Transcoder



;;  NOTE: in a Unicode-UCS-2 transcoder each "character" is actually regarded
;;  as an octet.

(def-structure (unicode-ucs-2-transcoder (:include transcoder))
  (next-character-determines-byte-order-if-BOM? t) ; t/nil; set nil after next char
  (unicode-ucs-2-transcoder-is-little-endian? nil)) ; t/nil; t => byte-swapped

;;; This implements the notorious Byte-Order Mark (BOM) protocol for determining
;;; byte order for Unicode.  The canonical/standard byte order is big-endian,
;;; i.e., most significant octet first.  But, if a data element (e.g., a file)
;;; starts out with the byte-order mark, or with its byte-swapped equivalent,
;;; that can be taken to override the default, and the character can just be
;;; discarded.  Byte-order mark is U+FEFF.  The character in Unicode that
;;; would be written U+FFFE is not a legal character.  Thus, U+FFFE can only
;;; be interpreted by swiping its bytes (octets), thus yielding the proper
;;; U+FEFF interpretation.  From then on, presumably, the entire rest of the
;;; the stream may be read in byte-swapped order.

(def-structure-method transcode-character (unicode-ucs-2-transcoder)
  (let* ((transcoder unicode-ucs-2-transcoder)
         (lead-character (get-transcoder-character transcoder))
         (trail-character #u0000))
    (declare (type wide-character lead-character trail-character))
    (cond
      ((not (text-sequence-has-more-characters-p
              (transcoder-text-sequence transcoder)))
       (transcode-unhandled-character lead-character transcoder)) ; odd octet-count!
      ((not (and (char<w lead-character #u0100) ; not octets!
                 (char<w trail-character #u0100)))
       (transcode-unhandled-character lead-character transcoder))
      (t
       (setq trail-character
             (get-transcoder-character transcoder))
       (or (if (next-character-determines-byte-order-if-BOM? transcoder)
               (progn
                 (setf (next-character-determines-byte-order-if-BOM?
                         transcoder)
                       nil)
                 (cond
                   ((and (char=w lead-character #u00FE)
                         (char=w trail-character #u00FF))
                    (setf (unicode-ucs-2-transcoder-is-little-endian?
                            transcoder)
                          nil)
                    #uFFFF)
                   ((and (char=w lead-character #u00FF)
                         (char=w trail-character #u00FE))
                    (setf (unicode-ucs-2-transcoder-is-little-endian?
                            transcoder)
                          t)
                    #uFFFF)
                   (t nil))))
           (transcode-character-handling-line-separator
             (if (unicode-ucs-2-transcoder-is-little-endian? transcoder)
                 (wide-character-octets-to-wide-character
                   trail-character lead-character)
                 (wide-character-octets-to-wide-character
                   lead-character trail-character))
             transcoder))))))

(def-structure-method export-character (unicode-ucs-2-transcoder)
  (let* ((transcoder unicode-ucs-2-transcoder)
         (character
           (export-character-handling-line-separator
             (get-transcoder-character transcoder)
             transcoder)))
    (declare (type wide-character character))
    (cond
      ((unicode-ucs-2-transcoder-is-little-endian? transcoder)
       (enqueue-pending-transcoder-character
         transcoder
         (wide-character-lead-octet-character character))
       (wide-character-trail-octet-character character))
      (t
       (enqueue-pending-transcoder-character
         transcoder
         (wide-character-trail-octet-character character))
       (wide-character-lead-octet-character character)))))





;;;; Unicode Transcoder



(def-structure (unicode-transcoder (:include transcoder)))

(def-structure-method transcode-character (unicode-transcoder)
  (transcode-character-handling-line-separator
    (get-transcoder-character unicode-transcoder)
    unicode-transcoder))

(def-structure-method export-character (unicode-transcoder)
  (export-character-handling-line-separator
    (get-transcoder-character unicode-transcoder)
    unicode-transcoder))





;;;; Unicode-Byte-Swapped Transcoder



(def-structure (unicode-byte-swapped-transcoder (:include transcoder)))

(def-structure-method transcode-character (unicode-byte-swapped-transcoder)
  (let* ((transcoder unicode-byte-swapped-transcoder)
         (character (get-transcoder-character transcoder)))
    (declare (type wide-character character))
    (transcode-character-handling-line-separator
      (wide-character-octets-to-wide-character
        (wide-character-trail-octet-character character)
        (wide-character-lead-octet-character character))
      transcoder)))

(def-structure-method export-character (unicode-byte-swapped-transcoder)
  (let* ((transcoder unicode-byte-swapped-transcoder)
         (character
           (export-character-handling-line-separator
             (get-transcoder-character transcoder)
             transcoder)))
    (declare (type wide-character character))
    (wide-character-octets-to-wide-character
      (wide-character-trail-octet-character character)
      (wide-character-lead-octet-character character))))





;;;; Character Set Encodings



(def-character-set-encoding iso-8859-1 (:synonyms (latin-1))
  (make-iso-8859-transcoder 1 (graphic-character-set 'iso-8859-1)))
(def-character-set-encoding iso-8859-2 (:synonyms (latin-2))
  (make-iso-8859-transcoder 2 (graphic-character-set 'iso-8859-2)))
(def-character-set-encoding iso-8859-3 (:synonyms (latin-3))
  (make-iso-8859-transcoder 4 (graphic-character-set 'iso-8859-3)))
(def-character-set-encoding iso-8859-4 (:synonyms (latin-4))
  (make-iso-8859-transcoder 4 (graphic-character-set 'iso-8859-4)))
(def-character-set-encoding iso-8859-5 (:synonyms (latin-cyrillic))
  (make-iso-8859-transcoder 5 (graphic-character-set 'iso-8859-5)))
(def-character-set-encoding iso-8859-6 (:synonyms (latin-arabic))
  (make-iso-8859-transcoder 6 (graphic-character-set 'iso-8859-6)))
(def-character-set-encoding iso-8859-7 (:synonyms (latin-greek))
  (make-iso-8859-transcoder 7 (graphic-character-set 'iso-8859-7)))
(def-character-set-encoding iso-8859-8 (:synonyms (latin-hebrew))
  (make-iso-8859-transcoder 8 (graphic-character-set 'iso-8859-8)))
(def-character-set-encoding iso-8859-9 (:synonyms (latin-5))
  (make-iso-8859-transcoder 9 (graphic-character-set 'iso-8859-9)))
(def-character-set-encoding iso-8859-10 (:synonyms (latin-6))
  (make-iso-8859-transcoder 10 (graphic-character-set 'iso-8859-10)))


(def-character-set-encoding gensym
    (:synonyms (UTF-G))
  (make-utf-g-transcoder))


(def-character-set-encoding gensym-with-ascii-as-much-as-possible
    (:synonyms (utf-g-ascii-as-much-as-possible))
  (make-utf-g-ascii-as-much-as-possible-transcoder))



;;; UNICODE-UCS-2 handles both "guess the byte order" and "normal (big-endian)
;;; byte order".  Guessing means that if the very first character is a
;;; non-unicode character which, when byte-reversed, turns out to be the BOM
;;; (byte-order-mark) character, then the stream is interpreted in byte-reversed
;;; fashion.  This character is interpreted as a "signature" and is not actually
;;; passed along.  As long as this is called either at the beginning of the line
;;; or at the beginning of text, there should be no problem with having it serve
;;; both functions.
;;;
;;; UNICODE-UCS-2-BYTE-SWAPPED is really only needed for unmarked, byte-reversed
;;; Unicode.  However, note that it will switch byte order back to normal if the
;;; first character is the BOM when byte-reversed.

(def-character-set-encoding unicode-ucs-2
    (:synonyms (iso-10646-ucs-2))
  (make-unicode-ucs-2-transcoder))

(def-character-set-encoding unicode-ucs-2-byte-swapped
    ()
  (let ((transcoder (make-unicode-ucs-2-transcoder)))
    (setf (unicode-ucs-2-transcoder-is-little-endian? transcoder) t)
    transcoder))

;; Hmmmm, this leaves no way to pass along the BOM/signature.  What if you want that?!



;;; UNICODE handles pure Unicode.  This is a noop for import.  The result of
;;; transcoding a string from this encoding is guaranteed to be 100% identical
;;; to the original string.  UNICODE-BYTE-SWAPPED is pure Unicode with the
;;; exception that all of the characters are byte-swapped.  The result double
;;; transcoding a string with this encoding (i.e., transcoding the result of
;;; transcoding once) is guaranteed to be same as the original string.

(def-character-set-encoding unicode (:synonyms (iso-10646))
  (make-unicode-transcoder))

(def-character-set-encoding unicode-byte-swapped
    (:synonyms (iso-10646-byte-swapped))
  (make-unicode-byte-swapped-transcoder))





;;;; Creation of Transcoders




;;; The function `make-transcoder-per-text-conversion-style' creates an
;;; appropriate transcoder structure based on text-conversion-style and
;;; text-sequence.  The job of importing (i.e., as a Unicode text string) the
;;; data element represented by text sequence is performed by calling the
;;; transcode-as-text-string method on the resulting transcoder structure.
;;;
;;; This binds `text-conversion-style-for-transcoder-being-created' to the
;;; argument text-conversion-style so that it can be used in the creation
;;; function.

(defvar text-conversion-style-for-transcoder-being-created)

(defun make-transcoder-per-text-conversion-style
    (text-conversion-style text-sequence)
  (let* ((funcallable-creator
           (or (transcoder-creation-function
                 (transcode-external-character-set ; may be a synonym
                   text-conversion-style))
               #+development
               (cerror "Continue, in error, as though in production."
                       "No transcoder defined for external character set ~a"
                       (transcode-external-character-set
                         text-conversion-style))))
         (text-conversion-style-for-transcoder-being-created
           text-conversion-style)
         (transcoder (funcall funcallable-creator)))
    (setf (transcoder-text-sequence transcoder) text-sequence)
    (setf (transcoder-text-conversion-style transcoder)
          text-conversion-style)
    transcoder))





;;;;





(defun-void twrite-ascii-from-wide-string (wide-string)
  (loop with length-of-string fixnum = (lengthw wide-string)
        for i from 0 below length-of-string
        as wide-character = (charw wide-string i)
        do (cond
             ((newline-p wide-character)
              (twrite-char #.%Linefeed))
             ((char<w wide-character #u0100) ; have this or a variant to to 255!!
              (twrite-char wide-character))
             (t nil))))





;;;; ISO2022




(defun-simple map-jis-x-0208-bytes-to-unicode-character (lead-byte trail-byte)
  (if (and (<=f #x21 lead-byte #x74)
           (<=f #x21 trail-byte #x7E))
      ;; abstract later!
      (code-wide-character
        (map-JIS-X-0208-to-unicode
          (+f (ashf lead-byte 8) trail-byte)))
      unicode-replacement-character))

(defun-simple map-ks-c-5601-bytes-to-unicode-character (lead-byte trail-byte)
  (if (and (<=f #x21 lead-byte #x7d)
           (<=f #x21 trail-byte #x7E))
      ;; abstract later!
      (code-wide-character
        (map-ks-c-5601-to-unicode
          (+f (ashf lead-byte 8) trail-byte)))
      unicode-replacement-character))

(defun-simple map-gb-2312-bytes-to-unicode-character (lead-byte trail-byte)
  (if (and (<=f #x21 lead-byte #x7d)
           (<=f #x21 trail-byte #x7E))
      ;; abstract later!
      (code-wide-character
        (map-gb-2312-to-unicode
          (+f (ashf lead-byte 8) trail-byte)))
      unicode-replacement-character))




(defun-simple map-shift-jis-bytes-to-unicode-character
    (lead-byte trail-byte)
  (declare (type fixnum lead-byte trail-byte))
  (setq lead-byte
        (-f lead-byte (if (<f lead-byte #xd0) #x71 #xb1)))
  (when (>f trail-byte #x7f)
    (setq trail-byte (-f trail-byte 1)))
  (setq lead-byte (ashf lead-byte -1))
  (when (>f trail-byte #x9d)
    (setq lead-byte (+f lead-byte 1))
    (setq trail-byte (-f trail-byte #x5e)))
  (setq trail-byte (-f trail-byte #x1f))
  (setq lead-byte (+f lead-byte 1))
  (code-wide-character
    (+f (ashf lead-byte 8) trail-byte)))

(defun-simple map-shift-jis-half-width-katakana-to-unicode
    (shift-jis-half-width-katakana-character)
  ;; Info from Unicode mapping table at
  ;;
  ;;   ftp://ftp.ora.com/pub/examples/nutshell/ujip/unicode/jisx0201-1976.txt
  ;;
  ;; as of this date. (MHD 7/19/96)
  (let ((code
          (wide-character-code
            shift-jis-half-width-katakana-character)))
    (code-wide-character (+f (-f code #xA0) #xFF60))))

;; The #uFF60 points to the compatibility region in Unicode for half-width
;; katakana.  We could either map half-width katakana to full-width (probably
;; the high road), or just map it to this compatibility zone.  However, this is
;; not quite one-to-one, and some tabular (nonaritmetic) lookup would be
;; necessary.  Half-width Katakana is not used all that often, and it's not
;; part of the JIS X 0208 character set we've always supported.  Unicode prefers
;; that half-width Katakana's essential functionality, i.e., narrower
;; characters, be achieved through font variations.  Note that we should also
;; support half-width katakana for EUC, in which one of the single shift escapes
;; is used for half-width Katakana.  (MHD 7/19/96)


(defmacro 8859-charset-part-number (8859-charset)
  `(case ,8859-charset
     (iso-8859-1 1)
     (iso-8859-2 2)
     (iso-8859-3 3)
     (iso-8859-4 4)
     (iso-8859-5 5)
     (iso-8859-6 6)
     (iso-8859-7 7)
     (iso-8859-8 8)
     (iso-8859-9 9)
     (iso-8859-10 10)))

;; Note that this can be used for most uses of X Compound Text.


;; NEW IMPL:

(defun-simple shift-jis-x-0208-in-text-sequence-to-unicode
    (text-sequence character)
  (cond
    ((char<w character #u0080)
     ;; translate to/from JIS-Roman?!!
     character)
    ((char<=w #u00A1 character #u00DF)
     (map-shift-jis-half-width-katakana-to-unicode character))
    ((or (char<=w #u0081 character #u009F)
         (char<=w #u00E0 character #u00EF))
     (cond
       ((not (text-sequence-has-more-characters-p text-sequence))
        unicode-replacement-character)        ; bad encoding!
       (t
        (map-shift-jis-bytes-to-unicode-character
          (wide-character-code character)
          (wide-character-code
            (read-character-from-text-sequence text-sequence))))))))


(defmacro x-EUC-in-text-sequence-to-unicode
    (text-sequence character x-double-byte-mapping-function)
  (avoiding-variable-capture (text-sequence character)
    `(cond
       ((char<w ,character #u00A0)
        ,character)
       ((char<w character #u0080)
        unicode-replacement-character)
       (t
        (cond
          ((not (text-sequence-has-more-characters-p ,text-sequence))
           unicode-replacement-character)        ; bad encoding
          (t
           (,x-double-byte-mapping-function
              (ashf (wide-character-code ,character) -1)
              (ashf (wide-character-code
                      (read-character-from-text-sequence ,text-sequence))
                    -1))))))))

(defun-simple jis-x-0208-euc-in-text-sequence-to-unicode (text-sequence character)
  (x-EUC-in-text-sequence-to-unicode
    text-sequence character
    map-jis-x-0208-bytes-to-unicode-character))

(defun-simple ks-c-5601-euc-in-text-sequence-to-unicode (text-sequence character)
  (x-EUC-in-text-sequence-to-unicode
    text-sequence character
    map-ks-c-5601-bytes-to-unicode-character))

(defun-simple gb-2312-euc-in-text-sequence-to-unicode (text-sequence character)
  (x-EUC-in-text-sequence-to-unicode
    text-sequence character
    map-gb-2312-bytes-to-unicode-character))

;; Deal with SS1 and SS2 in JIS and KSC versions of EUC!! They're little used,
;; but ultimately needed for completeness.  However, they're in the x80-x9F
;; range, which we're ignoring now, so this could really mess up the
;; interpretation of text that uses them.  (MHD 7/19/96)



(defun-simple jis-x-0208-in-text-sequence-to-unicode (text-sequence character)
  (cond
    ((not (text-sequence-has-more-characters-p text-sequence))
     unicode-replacement-character)        ; bad encoding
    (t
     (map-jis-x-0208-bytes-to-unicode-character
       (wide-character-code character)
       (wide-character-code
         (read-character-from-text-sequence text-sequence))))))


(defun-simple ks-c-5601-in-text-sequence-to-unicode (text-sequence character)
  (cond
    ((not (text-sequence-has-more-characters-p text-sequence))
     unicode-replacement-character)        ; bad encoding
    (t
     (map-ks-c-5601-bytes-to-unicode-character
       (wide-character-code character)
       (wide-character-code
         (read-character-from-text-sequence text-sequence))))))


(defun-simple gb-2312-in-text-sequence-to-unicode (text-sequence character)
  (cond
    ((not (text-sequence-has-more-characters-p text-sequence))
     unicode-replacement-character)        ; bad encoding
    (t
     (map-gb-2312-bytes-to-unicode-character
       (wide-character-code character)
       (wide-character-code
         (read-character-from-text-sequence text-sequence))))))





;;;; JIS (Japanese Industrial Standard) Encoding

;;; The encodings of JISX0208 we support are:
;;;
;;;    JIS (aka 2022-JP)
;;;
;;;    Shift JIS (aka sjis; Microsoft Kanji)
;;;
;;;    JIS EUC (aka Extended Unix Code; ujis; EUC-JP)
;;;
;;; In addition, we support both Japanese and US versions
;;; of ASCII (ISO 646).
;;;
;;; In addition, for import only, we support a "guess" mode,
;;; which uses the well-known tricks for guessing the encoding
;;; and/or handling ISO2022 escape sequences.
;;;
;;;

;;;; Importing and Exporting Text



;;; `Import-text-string' takes string, either a text string or a gensym string,
;;; and returns a new text string, performing character set translation
;;; parameterized appropriately as to character set type and leniency
;;; characteristics.
;;;
;;; This always returns a fresh text string, always encoded in Unicode.
;;;
;;; Purpose indicates a purpose for the string after importation, and implies
;;; assumptions about the character set and encoding of the input string and
;;; what, if any, conversion to perform during import.  The range of purposes
;;; is documented below in detail.
;;;
;;; Start? and end? have their usual meaning: start? is the first (physical)
;;; index at which to start the copying of the input string; nil is interpreted
;;; to mean 0.  End? is the index past the last character character to copy; nil
;;; is interpreted to mean the length of the string.
;;;
;;; Additional-arg? is usually not needed, but may be supplied in order to
;;; provide additional input to the translation, but its meaning is specified on
;;; a per-purpose basis; see below for details.

;;;
;;; [That is the spec; as of 2/27/96, we're just trying to get callers to go
;;; through this interface, and later we will do the parameterization
;;; followthrough.  For now, there are hardcoded answers, and you have to
;;; look at the code to discover them! (MHD 2/27/96)]

(defun import-text-string (string &optional purpose start? end?)
  (let ((style (or (text-conversion-style-for-purpose purpose)
                   #+development
                   (warn "No text conversion style known for purpose ~a; using default"
                         purpose)
                   default-text-conversion-style)))
    #+development
    (when *debug*
      ;; Useful for debugging -- trace may print too much of the string, i.e., garbage
      (let ((s (text-string-substring string start? end?)))
        (dformat "Import-text-string (~A): ~a"
                 purpose
                 (text-string-substring string start? end?))
        (reclaim-text-string s)))
    (import-text-string-per-text-conversion-style
      string style start? end?)))

(defun import-text-string-per-text-conversion-style
    (string text-conversion-style &optional start? end?)
  (with-text-sequence (text-sequence string start? end?)
    (with-transcoder (transcoder text-conversion-style text-sequence)
      (transcode-as-text-string transcoder))))





;;; `Export-text-string' ... This only accepts a text string, and will either
;;; emit a gensym string or a wide string (in some encoding).
;;;
;;; The known purposes are:
;;;
;;;     UTF-G-WIDE-STRING (default) -- a UTF-G encoded wide string
;;;     UTF-G-GENSYM-STRING -- a UTF-G encoded gensym string
;;;
;;;     UTF-8-WIDE-STRING -- a UTF-8 encoded text string
;;;     UTF-8-GENSYM-STRING -- a utf-8 encoded gensym string
;;;
;;;     UTF-7-WIDE-STRING -- a UTF-7 encoded text string
;;;     UTF-7-GENSYM-STRING -- a UTF-7 encoded gensym string
;;;
;;;     -- UTF-7 is written in the "optimistic" fashion, that is, directly
;;;     encoding as many characters as this format allows, including "Set O"
;;;     (optional direct characters).  The allowed control characters, including
;;;     CR and LF, are also written directly.  The + character is not written as
;;;     +-, but is rather fully encoded in UTF-7 Modified Base64.  Finally, all
;;;     base64 encoding runs are terminated with the - character, even when that
;;;     is not strictly necessary, to aid in legibility.
;;;
;;;     NOTIFY-USER-IF-POSSIBLE-VIA-CONSOLE -- for printing console
;;;     messages, especially by non-G2 applications (i.e., Telewindows and GSI);
;;;     this translates any newline characters, including our canonical line
;;;     separator (Unicode Line Separator) and our canonical paragraph separator
;;;     (Unicode Paragraph Separator), into the ASCII #\Linefeed character.
;;;     Non-8-bit characters are strictly disallowed at this time; if present,
;;;     their bits are truncated so that they appear as "garbage" 8-bit
;;;     characters in the output.
;;;
;;;     ICP-FILTERED-TEXT-STRING-READER -- implements the spec for ICP's
;;;     filtered-text-string value type reader.  At present, this turns all
;;;     newline characters into the linefeed character, eliminates non-8-bit
;;;     characters, and writes out all the rest.  Note that this has some
;;;     existing use contracts around it, but it's not that clear how to carry
;;;     them forward or what the user expectation really is.  This need review!
;;;
;;;     PFORMAT -- (same as above)
;;;
;;;     KB-ERROR -- (same as above) this is basically a call to
;;;     CL's error.  These strings end up being passed to our internal-error
;;;     handler.  However, there's no good way to get UTF-G through this way.
;;;     So, non-8-bit characters are simply truncated.
;;;
;;;     INSTANTIATE-FILE-TEMPLATE-FOR-PRINTING -- (same as above)
;;;
;;;     G2-DIRECTORY-PATHNAME, GENSYM-PATHNAME-NAMESTRING -- Assumed for now to
;;;     be in ISO Latin 1, and to be generally free of linebreaks and hence the
;;;     linebreak issue; flip side of transformation with same name in import
;;;     side, q.v.
;;;
;;;     IDL-SOURCE-FILE-PATHNAME -- Input is a text string that should be in ISO
;;;     Latin1, to be used as a an IDL source file pathname. There should be no
;;;     newline issues.  Output is an ISO Latin1 encoded gensym string. [Talk to
;;;     JH: consider making this UTF-8 and/or make sure that there is checking
;;;     to make sure the ISO Latin1 nature is understood by user, and appropriate
;;;     feedback is given for a more ambitious string! (MHD 6/4/96)]
;;;
;;;     FILTER-TEXT-FOR-GSI -- transcodes as ISO-8859-1 (Latin-1).
;;;
;;;
;;;
;;; The encoding of the argument text string can only be Unicode. However, it
;;; may be required for certain purposes that it be a particular subset of
;;; Unicode.  For example, to use KNOWN-ISO-LATIN1-TO-ISO-LATIN1, the contents
;;; should be all ISO-LATIN1, which is code-for-code identical with the block of
;;; 256 characters of Unicode in the range 0..FF.
;;;
;;; The result text string can be in any encoding, UTF-G, UTF-8, JIS/EUC,
;;; Shift-JIS, etc.

(defun export-text-string-per-text-conversion-style
    (text-string text-conversion-style &optional start? end?)
  (with-text-sequence (text-sequence text-string start? end?)
    (with-transcoder (transcoder text-conversion-style text-sequence)
      (export-as-string transcoder))))


(defun export-text-string (text-string &optional purpose start? end?)
  (let ((style (or (text-conversion-style-for-purpose purpose)
                   #+development
                   (warn "No text conversion style known for purpose ~a; using default"
                         purpose)
                   default-text-conversion-style)))
    (export-text-string-per-text-conversion-style
      text-string style start? end?)))




;;; `Unicode-known-iso-latin1-to-gensym-string copies text-string as a gensym
;;; string, assuming it contains only ISO Latin1 characters (i.e., only Unicode
;;; characters that can be represented in 8 bits).  It is intended that this be
;;; used for text strings containing only 8-bit characters.  However, note that
;;; all characters are stripped of their bits beyond the 8th, effectively
;;; rendering non-8-bit characters as garbage in the output.  This is a
;;; subfunction of export-text-string.

(defun-simple unicode-known-iso-latin1-to-gensym-string (text-string)
  (twith-output-to-gensym-string
    (loop for i from 0 below (text-string-length text-string)
          as character = (charw text-string i)
          do (twrite-char
               (code-wide-character
                 (logandf #xff (wide-character-code character)))))))





;;;; UTF-7


;;; UTF-7 is a mail safe and "ASCII-safe" encoding and interchange format for
;;; Unicode text.  Like the traditional Gensym character set encoding, all text
;;; is encoded in the ASCII character set, that is, using 7-bit characters.
;;; Unlike the Gensym encoding, control characters (codes 0-31) are legal,
;;; including Tab, Return, Linefeed, etc., and all 65,336 possible Unicode
;;; character codes can be encoded.  It also differs of course in the ways that
;;; the Gensym character set differs from the Unicode character set, as
;;; discussed extensively elsewhere.



;;; The following (beginning after this paragraph and through the examples at
;;; the end) defines UTF-7 and is taken verbatim from the document titled "UTF-7
;;; Encoding Form", by David Goldsmith, Taligent, Inc., and Mark Davis,
;;; Taligent, Inc., as found on the web at
;;; http://www.stonehand.com/unicode/standard/utf7.html#x7 on 5/28/96.
;;;
;;;
;;; US-ASCII Set D (directly encoded characters).
;;;
;;;         Set D (directly encoded characters) consists of the following
;;;         characters (derived from RFC 1521, Appendix B): the upper and lower
;;;         case letters A through Z and a through z, the 10 digits 0-9, and the
;;;         following nine special characters (note that "+" and "=" are
;;;         omitted):
;;;
;;;         Character   ASCII & Unicode Value (decimal)
;;;            '           39
;;;            (           40
;;;            )           41
;;;            ,           44
;;;            -           45
;;;            .           46
;;;            /           47
;;;            :           58
;;;            ?           63
;;;
;;; US-ASCII Set O (optional direct characters).
;;;
;;;         Set O (optional direct characters) consists of the following
;;;         characters (note that "\" and "~" are omitted):
;;;
;;;         Character   ASCII & Unicode Value (decimal)
;;;            !           33
;;;            "           34
;;;            #           35
;;;            $           36
;;;            %           37
;;;            &           38
;;;            *           42
;;;            ;           59
;;;            <           60
;;;            =           61
;;;            >           62
;;;            @           64
;;;            [           91
;;;            ]           93
;;;            ^           94
;;;            _           95
;;;            `           96
;;;            {           123
;;;            |           124
;;;            }           125
;;;
;;;         Rationale. The characters "\" and "~" are omitted because they are
;;;         often redefined in variants of ASCII.
;;;
;;; US-ASCII Set B (Modified Base 64)
;;;
;;;         Set B (Modified Base 64) is the set of characters in the Base64
;;;         alphabet defined in RFC 1521, excluding the pad character "="
;;;         (decimal value 61).
;;;
;;;         Rationale. The pad character = is excluded because UTF-7 is designed
;;;         for use within header fields as set forth in RFC 1522. Since the
;;;         only readable encoding in RFC 1522 is "Q" (based on RFC 1521's
;;;         Quoted- Printable), the "=" character is not available for use
;;;         (without a lot of escape sequences). This was very unfortunate but
;;;         unavoidable.  The "=" character could otherwise have been used as
;;;         the UTF-7 escape character as well (rather than using "+").
;;;
;;;         Note that all characters in US-ASCII have the same value in Unicode
;;;         when zero-extended to 16 bits.
;;;
;;; UTF-7 Definition
;;;
;;; A UTF-7 stream represents 16-bit Unicode characters in 7-bit US-ASCII as
;;; follows:
;;;
;;; Rule 1 (direct encoding)
;;;
;;; Unicode characters in set D above may be encoded directly as their ASCII
;;; equivalents. Unicode characters in Set O may optionally be encoded directly
;;; as their ASCII equivalents, bearing in mind that many of these characters
;;; are illegal in header fields, or may not pass correctly through some mail
;;; gateways.
;;;
;;; Rule 2 (Unicode shifted encoding)
;;;
;;; Any Unicode character sequence may be encoded using a sequence of characters
;;; in set B, when preceded by the shift character "+" (US-ASCII character value
;;; decimal 43). The "+" signals that subsequent octets are to be interpreted as
;;; elements of the Modified Base64 alphabet until a character not in that
;;; alphabet is encountered. Such characters include control characters such as
;;; carriage returns and line feeds; thus, a Unicode shifted sequence always
;;; terminates at the end of a line. As a special case, if the sequence
;;; terminates with the character "-" (US-ASCII decimal 45) then that character
;;; is absorbed; other terminating characters are not absorbed and are processed
;;; normally.
;;;
;;; Rationale. A terminating character is necessary for cases where the next
;;; character after the Modified Base64 sequence is part of character set B. It
;;; can also enhance readability by delimiting encoded sequences.
;;;
;;; Also as a special case, the sequence "+-" may be used to encode the
;;; character "+". A "+" character followed immediately by any character other
;;; than members of set B or "-" is an ill-formed sequence.
;;;
;;; Unicode is encoded using Modified Base64 by first converting Unicode 16-bit
;;; quantities to an octet stream (with the most significant octet first). Text
;;; with an odd number of octets is ill-formed.
;;;
;;; Rationale. ISO/IEC 10646-1:1993(E) specifies that when characters in the
;;; UCS-2 form are serialized as octets, that the most significant octet appear
;;; first. This is also in keeping with common network practice of choosing a
;;; canonical format for transmission.
;;;
;;; Next, the octet stream is encoded by applying the Base64 content transfer
;;; encoding algorithm as defined in RFC 1521, modified to omit the "=" pad
;;; character. Instead, when encoding, zero bits are added to pad to a Base64
;;; character boundary. When decoding, any bits at the end of the Modified
;;; Base64 sequence that do not constitute a complete 16-bit Unicode character
;;; are discarded. If such discarded bits are non-zero the sequence is
;;; ill-formed.
;;;
;;; Rationale. The pad character "=" is not used when encoding Modified Base64
;;; because of the conflict with its use as an escape character for the Q
;;; content transfer encoding in RFC 1522 header fields, as mentioned above.
;;;
;;; Rule 3
;;;
;;; The space (decimal 32), tab (decimal 9), carriage return (decimal 13), and
;;; line feed (decimal 10) characters may be directly represented by their ASCII
;;; equivalents. However, note that MIME content transfer encodings have rules
;;; concerning the use of such characters. Usage that does not conform to the
;;; restrictions of RFC 822, for example, would have to be encoded using MIME
;;; content transfer encodings other than 7bit or 8bit, such as
;;; quoted-printable, binary, or base64.
;;;
;;; Summary
;;;
;;; Given this set of rules, Unicode characters which may be encoded via rules 1
;;; or 3 take one octet per character, and other Unicode characters are encoded
;;; on average with 2 2/3 octets per character plus one octet to switch into
;;; Modified Base64 and an optional octet to switch out.
;;;
;;; Examples
;;;
;;;          The Unicode sequence "A<NOT IDENTICAL TO><ALPHA>." (hexadecimal
;;;         0041,2262,0391,002E) may be encoded as follows:
;;;
;;;       A+ImIDkQ.
;;;
;;;          The Unicode sequence "Hi Mom <WHITE SMILING FACE>!" (hexadecimal 0048,
;;;         0069, 0020, 004D, 006F, 004D, 0020, 263A, 0021) may be encoded as follows:
;;;
;;;       Hi Mom +Jjo-!
;;;
;;;         The Unicode sequence representing the Han characters for the
;;;         Japanese word "nihongo" (hexadecimal 65E5,672C,8A9E) may be encoded
;;;         as follows:
;;;
;;;       +ZeVnLIqe-
;;;
;;;

;;; The following comes from RFC1521, found on the web at
;;; http://www.cis.ohio-state.edu/htbin/rfc/rfc1521.html as of 5/28/96:
;;
;;; A 65-character subset of US-ASCII is used, enabling 6 bits to be
;;; represented per printable character. (The extra 65th character, "=",
;;; is used to signify a special processing function.)
;;;
;;;     NOTE: This subset has the important property that it is
;;;     represented identically in all versions of ISO 646, including US
;;;     ASCII, and all characters in the subset are also represented
;;;     identically in all versions of EBCDIC.  Other popular encodings,
;;;     such as the encoding used by the uuencode utility and the base85
;;;     encoding specified as part of Level 2 PostScript, do not share
;;;     these properties, and thus do not fulfill the portability
;;;     requirements a binary transport encoding for mail must meet.
;;;
;;; The encoding process represents 24-bit groups of input bits as output
;;; strings of 4 encoded characters. Proceeding from left to right, a
;;; 24-bit input group is formed by concatenating 3 8-bit input groups.
;;; These 24 bits are then treated as 4 concatenated 6-bit groups, each
;;; of which is translated into a single digit in the base64 alphabet.
;;; When encoding a bit stream via the base64 encoding, the bit stream
;;; must be presumed to be ordered with the most-significant-bit first.
;;;
;;; That is, the first bit in the stream will be the high-order bit in
;;; the first byte, and the eighth bit will be the low-order bit in the
;;; first byte, and so on.
;;;
;;; Each 6-bit group is used as an index into an array of 64 printable
;;; characters. The character referenced by the index is placed in the
;;; output string. These characters, identified in Table 1, below, are
;;; selected so as to be universally representable, and the set excludes
;;; characters with particular significance to SMTP (e.g., ".", CR, LF)
;;; and to the encapsulation boundaries defined in this document (e.g.,
;;; "-").
;;;
;;;                          Table 1: The Base64 Alphabet
;;;
;;;    Value Encoding  Value Encoding  Value Encoding  Value Encoding
;;;         0 A            17 R            34 i            51 z
;;;         1 B            18 S            35 j            52 0
;;;         2 C            19 T            36 k            53 1
;;;         3 D            20 U            37 l            54 2
;;;         4 E            21 V            38 m            55 3
;;;         5 F            22 W            39 n            56 4
;;;         6 G            23 X            40 o            57 5
;;;         7 H            24 Y            41 p            58 6
;;;         8 I            25 Z            42 q            59 7
;;;         9 J            26 a            43 r            60 8
;;;        10 K            27 b            44 s            61 9
;;;        11 L            28 c            45 t            62 +
;;;        12 M            29 d            46 u            63 /
;;;        13 N            30 e            47 v
;;;        14 O            31 f            48 w         (pad) =
;;;        15 P            32 g            49 x
;;;        16 Q            33 h            50 y
;;;
;;; The output stream (encoded bytes) must be represented in lines of no
;;; more than 76 characters each.  All line breaks or other characters
;;; not found in Table 1 must be ignored by decoding software.  In base64
;;; data, characters other than those in Table 1, line breaks, and other
;;; white space probably indicate a transmission error, about which a
;;; warning message or even a message rejection might be appropriate
;;; under some circumstances.
;;;
;;; Special processing is performed if fewer than 24 bits are available
;;; at the end of the data being encoded.  A full encoding quantum is
;;; always completed at the end of a body.  When fewer than 24 input bits
;;; are available in an input group, zero bits are added (on the right)
;;; to form an integral number of 6-bit groups.  Padding at the end of
;;; the data is performed using the '=' character.  Since all base64
;;; input is an integral number of octets, only the following cases can
;;; arise: (1) the final quantum of encoding input is an integral
;;; multiple of 24 bits; here, the final unit of encoded output will be
;;; an integral multiple of 4 characters with no "=" padding, (2) the
;;; final quantum of encoding input is exactly 8 bits; here, the final
;;; unit of encoded output will be two characters followed by two "="
;;; padding characters, or (3) the final quantum of encoding input is
;;; exactly 16 bits; here, the final unit of encoded output will be three
;;; characters followed by one "=" padding character.
;;;
;;; Because it is used only for padding at the end of the data, the
;;; occurrence of any '=' characters may be taken as evidence that the
;;; end of the data has been reached (without truncation in transit).  No
;;; such assurance is possible, however, when the number of octets
;;; transmitted was a multiple of three.
;;;
;;; Any characters outside of the base64 alphabet are to be ignored in
;;; base64-encoded data.  The same applies to any illegal sequence of
;;; characters in the base64 encoding, such as "====="
;;;
;;; Care must be taken to use the proper octets for line breaks if base64
;;; encoding is applied directly to text material that has not been
;;; converted to canonical form.  In particular, text line breaks must be
;;; converted into CRLF sequences prior to base64 encoding. The important
;;; thing to note is that this may be done directly by the encoder rather
;;; than in a prior canonicalization step in some implementations.
;;;
;;;    NOTE: There is no need to worry about quoting apparent
;;;    encapsulation boundaries within base64-encoded parts of multipart
;;;    entities because no hyphen characters are used in the base64
;;;    encoding.

;;; [Back to Gensym's text by MHD.]
;;;
;;; Full-blown MIME is highly stateful, and all kinds of heuristics may be
;;; advisable depending on how wide a range of mail systems your data has to
;;; "tunnel" through.  We interpret the inclusion by reference of MIME encoding
;;; to start and end with the handling of triplets of characters.  Therefore,
;;; the only "state" we need to keep track of is (a) the lookahead of the next
;;; two characters when we're in a base64 writing mode, and (b) whether or not
;;; we're in a base64 writing mode.  However, these notes (from the Unicode/UTF-7
;;; document) should be kept in mind:

;;;   Note that to achieve the best interoperability with systems that may not
;;;   support Unicode or MIME, when preparing text for mail transmission line
;;;   breaks should follow Internet conventions. This means that lines should be
;;;   short and terminated with the proper SMTP CRLF sequence. Unicode LINE
;;;   SEPARATOR (hexadecimal 2028) and PARAGRAPH SEPARATOR (hexadecimal 2029)
;;;   should be converted to SMTP line breaks. Ideally, this would be handled
;;;   transparently by a Unicode-aware user agent.
;;;
;;;   This preparation is not absolutely necessary, since UTF-7 and the
;;;   appropriate MIME content transfer encoding can handle text that does not
;;;   follow Internet conventions, but readability by systems without Unicode or
;;;   MIME will be impaired.  See RFC 1521 for an in-depth discussion of mail
;;;   interoperability issues.
;;;
;;;   Lines should never be broken in the middle of a UTF-7 shifted sequence,
;;;   since such sequences may not cross line breaks.  Therefore, UTF-7 encoding
;;;   should take place after line breaking. If a line containing a shifted
;;;   sequence is too long after encoding, a MIME content transfer encoding such
;;;   as Quoted Printable can be used to encode the text. Another possibility is
;;;   to perform line breaking and UTF-7 encoding at the same time, so that
;;;   lines containing shifted sequences already conform to length restrictions.
;;;
;;; However, I received via email the following clarification from the author:
;;;
;;;       Subject: Re: Clarification on UTF-7
;;;       Date: Wed, 29 May 96 12:15:45 -0700
;;;       From: David Goldsmith <david_goldsmith@taligent.com>
;;;
;;;       ... The issues with respect to usage with MIME in the UTF-7 document
;;;       are advisory on how best to prepare content for maximum
;;;       interoperability, and are a recommendation for the Unicode data
;;;       itself, *not* something enforced by UTF-7. ...  [While] RFC 1521
;;;       clearly statest that lines should be no more than 76 characters, [the]
;;;       UTF-7 spec should state that this constraint does not apply at the
;;;       transformation format level. ... UTF-7 is not inherently mail-safe...
;;;
;;; In light of the above, note that we pay no heed to line breaks or to line
;;; lengths in our implementation of UTF-7 encoding.


;;; `UTF-7-modified-base64-characters' is a wide string, 64 elements long,
;;; defining the digits of a base64 integer used for UTF-7 modified base64
;;; encoding.

(defparameter utf-7-modified-base64-characters
  (stringw "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"))


(defun-simple utf-7-base64-digit-char-p (wide-character)
  (let ((unicode (wide-character-code wide-character)))
    (utf-7-base64-digit-char-code-p unicode)))


(defun-simple utf-7-base64-digit-char-code-p (unicode)
  (cond
    ((<=f #.(ascii-char-code #\A) unicode #.(ascii-char-code #\Z))
     (-f unicode #.(ascii-char-code #\A)))
    ((<=f #.(ascii-char-code #\a) unicode #.(ascii-char-code #\z))
     (+f 26 (-f unicode #.(ascii-char-code #\a))))
    ((<=f #.(ascii-char-code #\0) unicode #.(ascii-char-code #\9))
     (+f 52 (-f unicode #.(ascii-char-code #\0))))
    ((=f unicode #.(ascii-char-code #\+))
     62)
    ((=f unicode #.(ascii-char-code #\/))
     63)
    (t nil)))

#+development                                ; test
(assert
  (loop for i from 0 below (lengthw utf-7-modified-base64-characters)
        always (=f i (utf-7-base64-digit-char-p
                       (charw utf-7-modified-base64-characters i)))))



;;; `UTF-7-base64-unicode-p' is true iff unicode is one of the UTF-7 modified
;;; base64 digits.

(defun-substitution-macro UTF-7-base64-unicode-p (unicode)
  (or (<=f #.(ascii-char-code #\A) unicode #.(ascii-char-code #\Z))
      (<=f #.(ascii-char-code #\a) unicode #.(ascii-char-code #\z))
      (<=f #.(ascii-char-code #\0) unicode #.(ascii-char-code #\9))
      (=f unicode #.(ascii-char-code #\+))
      (=f unicode #.(ascii-char-code #\/))))

;; Consider defining in terms of the above, or just eliminating in favor of the
;; above, ala Common Lisp.



;;; `UTF-7-ultraconservative-p' is by default nil.  When true, the set of characters
;;; that are optionally directly encoded are not directly encoded.  Rather, they are
;;; encoded using UTF-7 modified base64 encoding.

(defparameter utf-7-ultraconservative-p nil)



;;; `UTF-7-delimit-encoded-sequences-p' is by default true.  When true, UTF-7
;;; encoding always ends a base64-encoded sequence with a - character, whether
;;; or not it is followed by a base64 digit or by end-of-file.  When false, this
;;; is only done when the sequence is followed by a base64 digit.  This is
;;; strictly optional, and adds on average a bit more storage cost, but it
;;; results in output that's easier for humans to read and a little more robust.

(defparameter utf-7-delimit-encoded-sequences-p t)



;;; `UTF-7-direct-unicode-p' is true if unicode is to be directly encoded and
;;; false if unicode is to be encoded in UTF-7 modified base64 encoding.  This
;;; has as an implicit parameter the variable utf-7-ultraconservative-p, q.v.

(defun-substitution-macro utf-7-direct-unicode-p (unicode)
  (and (<f unicode 127)
       (if (<f unicode #.(ascii-char-code #\space))
           (or (=f unicode 9)
               (=f unicode 13)
               (=f unicode 10))
           (if utf-7-ultraconservative-p
               (or (<=f #.(ascii-char-code #\A) ; Rule 1
                        unicode
                        #.(ascii-char-code #\Z))
                   (<=f #.(ascii-char-code #\a)
                        unicode
                        #.(ascii-char-code #\z))
                   (<=f 39 unicode 41)
                   (<=f 44 unicode 47)

                   (=f unicode                ; Rule 3
                       #.(ascii-char-code #\space))
                   (=f unicode 58)
                   (=f unicode 63))
               (and (not (=f unicode #.(ascii-char-code #\=)))
                    (not (=f unicode #.(ascii-char-code #\+))))))))


(def-structure (utf-7-transcoder (:include transcoder)))

(def-character-set-encoding unicode-utf-7 (:synonyms (utf-7))
  (make-utf-7-transcoder))

(def-structure-method transcode-character (utf-7-transcoder)
  (let* ((transcoder utf-7-transcoder)
         (character (get-transcoder-character transcoder)))
    (declare (type wide-character character))
    (cond
      ((char<w character #u0020)        ; C0 (Control) range
       (transcode-control-character character transcoder))
      ((char<w character #u0080)        ; GL range (usually ASCII)
       (cond
         ((char=w character #.%\+)
          (transcode-utf-7-base64 transcoder))
         ((utf-7-direct-unicode-p (wide-character-code character))
          character)
         (t (transcode-unhandled-character character transcoder))))
      (t
       (transcode-unhandled-character character transcoder)))))

(defun transcode-utf-7-base64 (transcoder)
  (loop with buffered-sextets-in-reverse-order = '()
        as first-time? = t then nil
        with post-base64-character? = nil
        with character
        with sextet
        while (setq character
                    (get-transcoder-character-if-any transcoder))
        do (cond
             ((setq sextet (UTF-7-base64-digit-char-p character))
              (gensym-push sextet buffered-sextets-in-reverse-order))
             (first-time?
              (cond
                ((char=w character #.%\-)
                 ;; special case: +- ==> +
                 (return #.%\+))
                (t
                 ;; illegal sequence: +<non-base64-char>
                 ;; "illegal-non-base64-character-after-plus"
                 (return
                   (transcode-unhandled-character character transcoder)))))
             ((char=w character #.%\-)
              (loop-finish))
             (t
              (setq post-base64-character? character)
              (loop-finish)))
        finally
          (cond
            ((emit-buffered-utf-7-base64-sextets-as-unicodes
               transcoder
               buffered-sextets-in-reverse-order)
             ;; non-nil ==> error
             (return
               (transcode-unhandled-character
                 character transcoder))) ; somewhat random args here; improve!!
            (t
             ;; OK, now deal with the last character, if any, one past the base64 run:
             (when post-base64-character?
               (enqueue-pending-transcoder-character
                 transcoder post-base64-character?))
             (return
               (dequeue-pending-transcoder-character
                 transcoder))))))


(defun emit-buffered-unicodes-as-utf-7-base64-to-transcoder
    (buffered-unicodes-in-reverse-order transcoder)
  (loop with buffered-unicodes = (nreverse buffered-unicodes-in-reverse-order)
        for unicode in buffered-unicodes
        collect (ashf unicode -8)
          into octets using gensym-cons
        collect (logandf unicode #xff)
          into octets using gensym-cons
        finally
          (reclaim-gensym-list buffered-unicodes)
          (emit-buffered-octets-as-utf-7-base64-to-transcoder
            octets
            transcoder)))


(defun emit-buffered-octets-as-utf-7-base64-to-transcoder
    (buffered-octets transcoder)
  (loop for (octet-1 octet-2? octet-3?) on buffered-octets by #'cdddr
        do (let* ((sextet-1 (ashf octet-1 -2))
                  (sextet-2 (+f (ashf (logandf octet-1 #b11) 4)
                                (if octet-2?
                                    (ashf octet-2? -4)
                                    0)))
                  (sextet-3?
                    (if octet-2?
                        (+f (ashf (logandf octet-2? #b1111) 2)
                            (if octet-3?
                                (ashf octet-3? -6)
                                0))))
                  (sextet-4?
                    (if octet-3? (logandf octet-3? #b111111))))
             (enqueue-pending-transcoder-character
               transcoder
               (charw utf-7-modified-base64-characters sextet-1))
             (enqueue-pending-transcoder-character
               transcoder
               (charw utf-7-modified-base64-characters sextet-2))
             (when sextet-3?
               (enqueue-pending-transcoder-character
                 transcoder
                 (charw utf-7-modified-base64-characters sextet-3?)))
             (when sextet-4?
               (enqueue-pending-transcoder-character
                 transcoder
                 (charw utf-7-modified-base64-characters sextet-4?)))))
  (reclaim-gensym-list buffered-octets))



(defun emit-buffered-utf-7-base64-sextets-as-unicodes
    (transcoder buffered-sextets-in-reverse-order)
  (loop with buffered-sextets = (nreverse buffered-sextets-in-reverse-order)
        with octet-1
        as octet-2? = nil
        as octet-3? = nil
        for j from 0 by 4
        as (sextet-1 sextet-2? sextet-3? sextet-4?) on buffered-sextets by #'cddddr
        do (cond
             ((null sextet-2?)
              (reclaim-gensym-list buffered-sextets-in-reverse-order)
              (return 'illegal-utf-7-base64-character) ; Deal with error better!
;              (return
;                (values
;                  nil 'illegal-utf-7-base64-character
;                  (+f stop-reading-index j 1)))
              )
             (t
              (setq octet-1
                    (+f (ashf sextet-1 2)
                        (ashf sextet-2? -4)))
              (when sextet-3?
                (setq octet-2?
                      (+f (ashf (logandf sextet-2? #b1111) 4)
                          (ashf (or sextet-3? 0) -2)))
                (setq octet-3?
                      (+f (ashf (logandf sextet-3? #b11) 6)
                          (or sextet-4? 0))))))
        collect octet-1 into buffered-octets using gensym-cons
        when octet-2?
          collect octet-2? into buffered-octets using gensym-cons
        when octet-3?
          collect octet-3? into buffered-octets using gensym-cons
        finally
          (reclaim-gensym-list buffered-sextets)
          (return
            (emit-buffered-octets-as-unicodes
              transcoder buffered-octets))))


(defun emit-buffered-octets-as-unicodes (transcoder buffered-octets)
  (loop for (octet-1 octet-2?) on buffered-octets by #'cddr
        as j from 0 by 3
        when (and (null octet-2?) (not (=f octet-1 0)))
          do (reclaim-gensym-list buffered-octets)
          and return 'ill-formed-octet-stream-odd-number ; Deal with error better!
;          and return (values
;                       nil
;                       'ill-formed-octet-stream-odd-number
;                       (+f stop-reading-index j))
        when octet-2?
          do (enqueue-pending-transcoder-character
               transcoder
               (code-wide-character (+f (ashf octet-1 8) octet-2?)))
        finally
          (reclaim-gensym-list buffered-octets)
;          (return stop-reading-index)
          (return nil)))


;; Export

(def-structure-method export-character (utf-7-transcoder)
  (let* ((transcoder utf-7-transcoder)
         (character (get-transcoder-character transcoder)))
    (declare (type wide-character character))
    (cond
      ((utf-7-direct-unicode-p (wide-character-code character))
       character)
      (t
       (export-utf-7-base64 character transcoder)))))


(defun-simple export-utf-7-base64 (first-non-direct-character transcoder)
  (declare (type wide-character first-non-direct-character))
  (loop with reversed-buffered-unicodes        ; a gensym list
          = (gensym-list (wide-character-code first-non-direct-character))
        as character? = (get-transcoder-character-if-any transcoder)
        while character?
        until (utf-7-direct-unicode-p (wide-character-code character?))
        do (gensym-push
             (wide-character-code character?)
             reversed-buffered-unicodes)
        finally
          (emit-buffered-unicodes-as-utf-7-base64-to-transcoder
            reversed-buffered-unicodes
            transcoder)
          (enqueue-pending-transcoder-character transcoder #.%\-)
          (when character?
            (enqueue-pending-transcoder-character transcoder character?))
          (return #.%\+)))

;; Regression tests:
;;
;; Examples [from the UTF-7 Encoding Form web document]
;;
;;     The Unicode sequence "A<NOT IDENTICAL TO><ALPHA>." (hexadecimal
;;     0041,2262,0391,002E) may be encoded as follows:
;;
;;
;;       A+ImIDkQ.
;;
;;     [NB: The following is equivalent, and is what we generate:
;;
;;       A+ImIDkQ-.
;;
;;     ]
;;
;;     The Unicode sequence "Hi Mom <WHITE SMILING FACE>!" (hexadecimal 0048,
;;     0069, 0020, 004D, 006F, 004D, 0020, 263A, 0021) may be encoded as
;;     follows:
;;
;;
;;       Hi Mom +Jjo-!
;;
;;     The Unicode sequence representing the Han characters for the Japanese
;;     word "nihongo" (hexadecimal 65E5,672C,8A9E) may be encoded as follows:
;;
;;
;;       +ZeVnLIqe-

;; Should be enabled, but #w"..." reader can't work in this module!

;#+development
;(defparameter utf-7-test-data
;  '(("A+ImIDkQ-." #w"A\u2262\u0391.")
;    ("Hi Mom +Jjo-!" #w"Hi Mom \u263A!")
;    ("+ZeVnLIqe-" #w"\u65E5\u672C\u8A9E")))

;#+development
;(defun test-utf-7 (&optional verbose?)
;  (loop for (utf-7-gensym-string unicode-text-string) in utf-7-test-data
;        as purported-utf-7
;           = (twith-output-to-gensym-string
;               (twrite-utf-7-from-text-string unicode-text-string))
;        as purported-unicode
;           = (twith-output-to-text-string
;               (twrite-unicode-from-utf-7-encoded-gensym-string
;                 utf-7-gensym-string))
;        when verbose?
;          do (format t "~%Unicode ~s~% => UTF-7 ~s"
;                     unicode-text-string purported-utf-7)
;             (if (string= purported-utf-7 utf-7-gensym-string)
;                 (format t "~%Good.")
;                 (format t "~%Bad. Should be UTF-7 ~s" utf-7-gensym-string))
;             (format t "~%UTF-7 ~s~% => Unicode ~s"
;                     utf-7-gensym-string purported-unicode)
;             (if (string=w purported-unicode unicode-text-string)
;                 (format t "~%Good.")
;                 (format t "~%Bad. Should be Unicode ~s" unicode-text-string))
;        unless (string= purported-utf-7 utf-7-gensym-string)
;          do (cerror "Continue" "Regression test failed: Unicode ~s => UTF-7 ~s (not ~s)"
;                     unicode-text-string utf-7-gensym-string purported-utf-7)
;        unless (string=w purported-unicode unicode-text-string)
;          do (cerror "Continue" "Regression test failed: UTF-7 ~s => Unicode ~s (not ~s)"
;                     utf-7-gensym-string purported-unicode unicode-text-string)))

;#+development
;(test-utf-7 nil)





;;;; UTF-8


;;; UTF-8 provides a way to map any UCS-4 (4-octet, i.e., 32-bit) code to a
;;; sequence of up to UTF-*, i.e., a sequence of between 1 and 6 octets.  Note
;;; that this is more than adequate for handling any Unicode value, they being
;;; 2-octet, i.e., 16 codes, so we actually never need to use the all of the
;;; capacity this provides, at least not for Unicode.
;;;
;;; Note that, according to the features of UTF-8,
;;;
;;;    a 7-bit ("ASCII") code (range [0..127]) requires one octet
;;;
;;;    a unicode (range [0..(2^16 - 1)]) requires at most 3 octets
;;;
;;;    an arbitrary ucs-4 (range [0..(2^32 - 1)] requires at most 6 octets
;;;
;;; Note that the ucs-4 case is provided for convenience and completion of the
;;; spec, but it is for all intents and purposes never used in Gensym software,
;;; since we limit our usage to the unicode range.
;;;
;;; Note also that, unlike UTF-7 and UTF-G, the resulting octets may have their
;;; 8th bit set, and so may be unsuitable for certain mail systems, which
;;; may be ASCII-only or 8-bit unfriendly in some other way.
;;;
;;; The documentation for UTF-8 can be found on the Web at
;;;
;;;    http://www.stonehand.com/unicode/standard/wg2n1036.html
;;;
;;; Here are some features of UTF-8 from that document
;;;
;;;   [terminology: UTF - UCS Transformation Format; UCS - Universal Character
;;;   Set, 16-bit or 32-bit versions -- 16-bit version is Unicode; UCS-4 -
;;;   32-bit version of UCS;]
;;;
;;;            UCS characters from 0000 0000 to 0000 007E (ASCII repertoire) map
;;;            to UTF-8 octets 00 to 7E (ASCII values).
;;;
;;;            ASCII values do not otherwise occur in a UTF-8
;;;            transformation. This provides compatibility with historical file
;;;            systems and other systems which parse for ASCII octets.
;;;
;;;            It is easy to convert to and from UCS-4.
;;;
;;;            The first octet indicates the number of octets to follow in a
;;;            multi-octet sequence.  It is efficient to find the start of a
;;;            character starting from an arbitrary location in an octet stream.
;;;
;;;            UTF-8 is not extravagant in terms of number of octets used for
;;;            encoding.
;;;
;;;            The transformation defined for UTF-8 is applicable to characters
;;;            coded according to UCS-4, but not for characters coded according
;;;            to UTF-16.
;;;
;;;            If it is desired to transform data coded in UTF-16 into UTF-8,
;;;            this can be accomplished first by transforming from UTF-16 to
;;;            UCS-4 (see Annex 0) before applying UTF-8.
;;;
;;;            If it is desired to transform data coded in UTF-8 to UTF-16, this
;;;            can be accomplished first by transforming from UTF-8 to UCS-4
;;;            before applying UTF-16.

;;; The following table shows the format of the first octet of a coded
;;; character; the free bits available for coding the character are indicated by
;;; an x. [Note 2]
;;;
;;;      Octets          Binary     Bits Free   Max. UCS-4
;;;     1st of 1        0xxxxxxx        7       0000 007F
;;;     1st of 2        110xxxxx        5       0000 07FF
;;;     1st of 3        1110xxxx        4       0000 FFFF
;;;     1st of 4        11110xxx        3       001F FFFF
;;;     1st of 5        111110xx        2       03FF FFFF
;;;     1st of 6        1111110x        1       7FFF FFFF
;;;     2nd .. nth      10xxxxxx        6
;;;
;;; Coded representations in the range 0000 D800 to 0000 DFFF shall be excluded
;;; from this conversion process. Therefore any UTF-8 octet that starts with
;;; binary 0 is a sequence of one; any octet that starts with 10 is a trailing
;;; octet of a multi-octet sequence; any other octet is the start of a
;;; multi-octet UTF-8 sequence.


;;; Note.
;;;
;;; Fundamentally, UTF-8 distributes the UCS-4 bits among the xxxx bits in the
;;; appropriate sequence above. The algorithm can be explained in a fairly
;;; simple manner:
;;;
;;;        To convert UCS-4 to UTF-8, determine which sequence to use based on
;;;        the Maximum UCS-4 value in the above table. Take the bits in the
;;;        UCS-4 coded representation and distribute them among the xxxx bits in
;;;        that sequence, starting with the low bits in the last octet of the
;;;        sequence.
;;;
;;;        To convert UTF-8 to UCS-4, take all the xxxx bits of each octet in
;;;        the sequence and concatenate them together, with the bits in the last
;;;        octet going in the low bits of the result. Any high-order bits not
;;;        represented in the sequence are set to zero.

;;; The following table defines the transformation from UCS-4 to UTF-8:
;;;
;;; UTF-4                   UTF-8
;;;
;;; x < 80;                 x;
;;;
;;; x < 800;                C0 + x / 2^6;
;;;                         80 + x %2^6;
;;;
;;; D800 <= x < DC00;       E0 + t/2^12%2^6;
;;;                         where t = (x - D800)*2^10 +
;;;                                   (y - DC00) + 10 0000
;;;
;;; DC00 <= y < E000;       80 + t/2^6%2^6; 80 + t%2^6;
;;;                         where t is same as above
;;;
;;; x < 1 0000;             E0 + x/2^12;
;;;                         80 + x/2^6%2^6;
;;;                         80 + x%2^6;
;;;
;;; x < 20 0000;            F0 + x/2^18;
;;;                         80 + x/2^12%2^6;
;;;                         80 + x/2^6%2^6;
;;;                         80 + x%2^6;
;;;
;;; x < 400 0000;           F8 + x/2^24;
;;;                         80 + x/2^18%2^6;
;;;                         80 + x/2^12%2^6;
;;;                         80 + x/2^6%2^6;
;;;                         80 + x%2^6;
;;;
;;; x;                      FC + x/2^30;
;;;                         80 + x/2^24%2^6;
;;;                         80 + x/2^18%2^6;
;;;                         80 + x/2^12%2^6;
;;;                         80 + x/2^6%2^6;
;;;                         80 + x%2^6;
;;;
;;; The following table defines the transformation from UTF-8 to UCS-4:
;;;
;;; UTF-8                   UCS-4
;;;
;;; z < C0;                 z;
;;; z < E0; y;              (z-C0)*2^6 + (y-80);
;;; z < F0; y; x;           (z-E0)*2^12 + (y-80)*2^6 + (x-80);
;;; z < F8; y; x; w;        (z-F0)*2^18 + (y-80)*2^12 + (x-80)*2^6 + (w-80);
;;; z < FC; y; x; w; v;     (z-F8)*2^24 + (y-80)*2^18 + (x-80)*2^12 + (w-80)*2^6 + (v - 80);
;;; z; y; x; w; v; u;       (z-FC)*2^30 + (y-80)*2^24 + (x-80)*2^18 + (w-80)*2^12 + (v-80)*2^6 + (u-80);



;;; `Get-utf-8-octet-count-from-ucs-4' takes a unicode (or any other instance of
;;; a UCS-4), and returns the number of octets it would require to represent
;;; that character in UTF-8.

;; UCS-4  =>  UTF-8

(def-substitution-macro get-utf-8-octet-count-from-ucs-4 (ucs-4)
  (cond
    ((<=f ucs-4 #x0000007F)                ; 1 octet
     1)
    ((<=f ucs-4 #x000007FF)                ; 2 octet
     2)
    ((<=f ucs-4 #x0000FFFF)                ; 3 octet
     3)
    ;; unsupported: ucs-4:
;    ((<=f ucs-4 #x001FFFFF)                ; 4 octet
;     4)
;    ((<=f ucs-4 #x03FFFFFF)                ; 5 octet
;     5)
;    ((<=f ucs-4 #x7FFFFFFF)                ; 6 octet
;     6)
    ))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar ucs-4-to-utf-8-1st-octet-table
  ;; # Octets  Binary             Use Bits   Bits Free   Max. UCS-4
  '((1         #b00000000         #b01111111 7           #x0000007F)
    (2         #b11000000         #b00011111 5           #x000007FF)
    (3         #b11100000         #b00001111 4           #x0000FFFF)
    ;; unsupported: ucs-4
;    (4         #b11110000         #b00000111 3           #x001FFFFF)
;    (5         #b11111000         #b00000011 2           #x03FFFFFF)
;    (6         #b11111100         #b00000001 1           #x7FFFFFFF)
    ))
)


(defun twrite-utf-8-octets (unicode n-octets binary use-bits bits-free)
  (let ((binary-2 #b10000000) ; "2" means "2 through n"
        (use-bits-2 #b00111111)
        (bits-free-2 6))
    (loop for binary = binary then binary-2
          as bits-free = bits-free then bits-free-2
          as use-bits = use-bits then use-bits-2
          as octet-index from n-octets downto 1
          as octet
             = (logiorf
                 binary
                 (logandf
                   use-bits
                   (right-shiftf unicode (*f bits-free-2 (-f octet-index 1)))))
          do (twrite-char (code-wide-character octet)))))


;;; `Twrite-unicode-as-utf-8-macro' twrites to the current output string the
;;; UTF-8 octets that represent unicode.  `Twrite-unicode-as-utf-8' is a
;;; function version that does the same thing, but takes up considerably less
;;; code space.  Both are suitable for calling in any of the contexts
;;; twith-output-to-text-string, twith-output-to-wide-string, or
;;; twith-output-to-gensym-string.
;;;
;;; Example:
;;;
;;; The following creates a wide string that contains the UTF-8 encoding of
;;; a sequence of the two unicode characters U+05F2, U+05B7:

#+comment
(twith-output-to-wide-string
  (twrite-unicode-as-utf-8 #x5f2)
  (twrite-unicode-as-utf-8 #x5b7))

;; This creates a wide string characters whose codes are, in order:
;;
;;    #xD7 #xB2 #xD6 #xB7

(defmacro twrite-unicode-as-utf-8-macro (unicode)
  (avoiding-variable-capture (unicode)
    `(cond
       . ,(loop for (n-octets binary use-bits bits-free max-ucs-4)
                    in ucs-4-to-utf-8-1st-octet-table
                if (= n-octets 1)        ; SPECIAL CASE: inline single-byte 7-bit
                  collect                ;     (ASCII) case as an optimization
                    `((<=f ,unicode ,max-ucs-4)
                      (twrite-char (code-wide-character ,unicode)))
                else collect
                  `((<=f ,unicode ,max-ucs-4)
                    (twrite-utf-8-octets
                      ,unicode ,n-octets ,binary ,use-bits ,bits-free))))))

(defun twrite-unicode-as-utf-8 (unicode)
  (twrite-unicode-as-utf-8-macro unicode))



;; UTF-8  =>  UCS-4


(defun transform-utf-8-to-ucs-4 (z &optional y x  w v u)
  (cond
    ((<f z #xC0)                        ; use z
     z)
    ((<f z #xE0)                        ; use z, y
     (+f (*f (-f z #xC0) #.(expt 2 6)) (-f y #x80)))
    ((<f z #xF0)                        ; use z, y, x
     (+f (*f (-f z #xE0) #.(expt 2 12))
         (*f (-f y #x80) #.(expt 2 6))
         (-f x #x80)))
    ;; unsupported: ucs-4
    ((<f z #xF8)                        ; use z, y, x, w
     (+f (*f (-f z #xF0) #.(expt 2 18))
         (*f (-f y #x80) #.(expt 2 12))
         (*f (-f x #x80) #.(expt 2 6))
         (-f w #x80)))
    ((<f z #xFC)                        ; use z, y, x, w, v
     (+f (*f (-f z #xF8) #.(expt 2 24))
         (*f (-f y #x80) #.(expt 2 18))
         (*f (-f x #x80) #.(expt 2 12))
         (*f (-f w #x80) #.(expt 2 6))
         (-f v #x80)))
    (t                                  ; use z, y, x, w, v, u
     ;; TODO: use general operator #'+ instead. 
     (+f (*f (-f z #xFC) #.(expt 2 24) #.(expt 2 6)) ; old: #.(expt 2 30)
         (*f (-f y #x80) #.(expt 2 24))
         (*f (-f x #x80) #.(expt 2 18))
         (*f (-f w #x80) #.(expt 2 12))
         (*f (-f v #x80) #.(expt 2 6))
         (-f u #x80)))
    ))


;;; `Get-octet-count-from-utf-8-lead-octet' returns the number of octets that
;;; should follow Z, a UTF-8 lead octet.

(def-substitution-macro get-octet-count-from-utf-8-lead-octet (z)
  (cond
    ((<f z #xC0)                        ; use z
     1)
    ((<f z #xE0)                        ; use z, y
     2)
    ((<f z #xF0)                        ; use z, y, x
     3)
    ;; unsupported: ucs-4
    ((<f z #xF8)                        ; use z, y, x, w
     4)
    ((<f z #xFC)                        ; use z, y, x, w, v
     5)
    (t                                  ; use z, y, x, w, v, u
     6)
    ))




;;; `Twrite-utf-8-from-text-string' twrites the UTF-8 "octets" (all 8-bit
;;; characters in the range [32..255]) from text-string.  This can be called
;;; in either a twith-output-to-text-string or twith-output-to-gensym-string
;;; context.

(defun-void twrite-utf-8-from-text-string (text-string)
  (loop with length fixnum = (text-string-length text-string)
        with i fixnum = 0
        with wide-character
        for wide-string-index fixnum from 0
        while (<f i length)
        do (setq wide-character
                 (read-character-from-text-string text-string i))
           (twrite-unicode-as-utf-8-macro
             (wide-character-code wide-character))))



;;; `Unicode-to-utf-8-wide-string' takes a Unicode-encoded wide string,
;;; text-string, and returns a UTF-8-encoded wide string.

(defun unicode-to-utf-8-wide-string (text-string)
  (twith-output-to-wide-string
    (twrite-utf-8-from-text-string text-string)))

;;; `Unicode-to-utf-8-gensym-string' takes a Unicode-encoded wide string,
;;; text-string, and returns a UTF-8-encoded gensym string.

(defun unicode-to-utf-8-gensym-string (text-string)
  (twith-output-to-gensym-string
    (twrite-utf-8-from-text-string text-string)))





;;; `Get-utf-8-as-unicode-from-text-sequence' returns a unicode character
;;; produced from a utf-8 character in text-sequence.  If the input is
;;; exhausted, nil is returned.

(defun-simple get-utf-8-as-unicode-from-text-sequence (text-sequence)
  (block exhausted
     (macrolet ((g ()
                  `(if (text-sequence-has-more-characters-p text-sequence)
                       (wide-character-code
                         (read-character-from-text-sequence text-sequence))
                       (return-from exhausted nil))))
       (let* ((z (wide-character-code        ; known not exhausted for first character
                   (read-character-from-text-sequence text-sequence)))
              (y 0)
              (x 0)
              (w 0)
              (v 0)
              (u 0)
              (octet-count (or (get-octet-count-from-utf-8-lead-octet z)
                               0))) ;actually an error of some sort
         (declare (type fixnum z y x w v u octet-count))
         (and
           (>f octet-count 1)
           (setq y (g))
           (>f octet-count 2)
           (setq x (g))
           (>f octet-count 3)
           (setq w (g))
           (>f octet-count 4)
           (setq v (g))
           (>f octet-count 5)
           (setq u (g)))
         (code-wide-character
           (transform-utf-8-to-ucs-4 z y x w v u))))))





;;; UTF-8 Regression Testing

#+development
(defparameter utf-8-regression-test-data
  ;; UCS-4  (32-bit universal code)         UTF-8
  ;; ------------------------------         -----------
  '((#b00000000000000000000000000000001 #b00000001)
    (#b00000000000000000000000001111111 #b01111111)
    (#b00000000000000000000000010000000 #b11000010 #b10000000)
    (#b00000000000000000000011111111111 #b11011111 #b10111111)
    (#b00000000000000000000100000000000 #b11100000 #b10100000 #b10000000)
    (#b00000000000000001111111111111111 #b11101111 #b10111111 #b10111111)
    ;; THE following get into bignums.  Not needed for the forseeable future, if ever. (MHD 8/1/96)
;    (#b00000000000000010000000000000000 #b11110000 #b10010000 #b10000000 #b10000000)
;    (#b00000000000111111111111111111111 #b11110111 #b10111111 #b10111111 #b10111111)
;    (#b00000000001000000000000000000000 #b11111000 #b10001000 #b10000000 #b10000000 #b10000000)
;    (#b00000011111111111111111111111111 #b11111011 #b10111111 #b10111111 #b10111111 #b10111111)
;    (#b00000100000000000000000000000000 #b11111100 #b10000100 #b10000000 #b10000000 #b10000000 #b10000000)
;    (#b01111111111111111111111111111111 #b11111101 #b10111111 #b10111111 #b10111111 #b10111111 #b10111111)
    ))


#+development
(defun test-utf-8-to-ucs-4 ()
  (loop for (ucs-4 . utf-8-sequence) in utf-8-regression-test-data
        as utf-8-wide-string
           = (twith-output-to-wide-string
               (loop for octet in utf-8-sequence
                     do (twrite-char octet)))
        as sequence-active-length = (length utf-8-sequence)
        as octet-count = (get-octet-count-from-utf-8-lead-octet
                           (first utf-8-sequence))
        do (assert (= octet-count sequence-active-length))
           (assert (= ucs-4 (apply 'transform-utf-8-to-ucs-4 utf-8-sequence)))
           (with-text-sequence (text-sequence utf-8-wide-string nil nil)
             (assert (char=w (code-wide-character ucs-4)
                             (get-utf-8-as-unicode-from-text-sequence
                               text-sequence)))
             (assert (= (text-sequence-string-index text-sequence)
                        octet-count)))
           (reclaim-wide-string utf-8-wide-string)))


#+development
(defun test-ucs-4-to-utf-8 (&optional print-it-p)
  (loop for (ucs . octets) in utf-8-regression-test-data
        as s = (twith-output-to-wide-string
                 (twrite-unicode-as-utf-8 ucs))
        when print-it-p
          do (let ((*print-base* 16)
                   (*print-escape* t))
               (format t "~%~a~%~a"
                       (list ucs '-?> octets)
                       (list ucs '-->
                             (loop with s = (twith-output-to-wide-string
                                              (twrite-unicode-as-utf-8 ucs))
                                   for i from 0 below (lengthw s)
                                   collect (wide-character-code (charw s i))))))
        do (test-assertion
             (equal (loop for i from 0 below (lengthw s)
                          collect (wide-character-code (charw s i)))
                    octets))))


#+development
(test-utf-8-to-ucs-4)

#+development
(test-ucs-4-to-utf-8)






(def-structure (utf-8-transcoder (:include transcoder)))

(def-character-set-encoding unicode-utf-8 (:synonyms (utf-8))
  (make-utf-8-transcoder))


(def-structure-method transcode-character (utf-8-transcoder)
  (let* ((transcoder utf-8-transcoder)
         (character (get-transcoder-character transcoder)))
    (declare (type wide-character character))
    (cond
      ((char<w character #u0020)        ; C0 (Control) range
       (transcode-control-character character transcoder))
      ((char<w character #u0080)        ; GL range (usually ASCII)
       character)
      ;; Note that C1 controls codes (#x80..#x9f) are valid UTF-8 octets
      ((char<w character #u0100)
       (let* ((z (wide-character-code character))
              (y 0)
              (x 0)
              (octet-count (or (get-octet-count-from-utf-8-lead-octet z)
                               0))) ; actually an error of some sort
         (declare (type fixnum octet-count z y x))
         (cond
           ((>f octet-count 3)
            ;; either a bug, or attempt to use (full) UCS-4, not handled; squawk?!
            (transcode-unhandled-character character transcoder))
           (t
            (when (>f octet-count 1)
              (let ((c (get-transcoder-character-if-any transcoder)))
                (cond
                  ((null c)
                   (setq y -1))
                  (t
                   (setq y (wide-character-code c))
                   (when (>f octet-count 2)
                     (setq c (get-transcoder-character-if-any transcoder))
                     (cond
                       ((null c)
                        (setq x -1))
                       (t
                        (setq x (wide-character-code c)))))))))
            (cond
              ((or (<f y 0) (<f x 0))
               (transcode-unhandled-character character transcoder))
              (t
               (code-wide-character
                 (transform-utf-8-to-ucs-4 z y x))))))))
      (t
       (transcode-unhandled-character character transcoder)))))


;; Export

(defmacro export-utf-8-for-transcoder (character transcoder)
  `(cond
     . ,(loop for (n-octets binary use-bits bits-free max-ucs-4)
                  in ucs-4-to-utf-8-1st-octet-table
              as max-character = (code-wide-character max-ucs-4)
              if (= n-octets 1)        ; SPECIAL CASE: inline single-byte 7-bit
                collect                ;     (ASCII) case as an optimization
                `((char<=w ,character ,max-character)
                  ,character)
              else collect
                `((char<=w ,character ,max-character)
                  (encode-utf-8-octets-for-transcoder
                    ,transcoder
                    ,character ,n-octets ,binary ,use-bits ,bits-free)))))


(def-structure-method export-character (utf-8-transcoder)
  (let* ((transcoder utf-8-transcoder)
         (character
           (export-character-handling-line-separator
             (get-transcoder-character transcoder)
             transcoder)))
    (declare (type wide-character character))
    (export-utf-8-for-transcoder character transcoder)))


;;; `Encode-utf-8-octets-for-transcoder' returns the first of the
;;; series of octets used to encode characters in UTF-8, and enqueues
;;; the rest in the transcoder.

(defun-simple encode-utf-8-octets-for-transcoder
    (transcoder character n-octets binary use-bits bits-free)
  (let ((binary-2 #b10000000) ; "2" means "2 through n"
        (use-bits-2 #b00111111)
        (bits-free-2 6))
    (loop for binary = binary then binary-2
          as bits-free = bits-free then bits-free-2
          as use-bits = use-bits then use-bits-2
          as octet-index from n-octets downto 1
          as octet
             = (logiorf
                 binary
                 (logandf
                   use-bits
                   (right-shiftf
                     (wide-character-code character)
                     (*f bits-free-2 (-f octet-index 1)))))
          as octet-character = (code-wide-character octet)
          do (enqueue-pending-transcoder-character transcoder octet-character))
    #uFFFF))



;;; The development function `test-utf-8-round-trip' tests that round-trip
;;; compatibility between Unicode and UTF-8 encoding is working.  This should be
;;; run routinely to test for regressions, and especially whenever changes to
;;; UTF-8 code is made.

#+development
(defun test-utf-8-round-trip ()
  (loop with permitted-import-export-exceptions
        ;; these don't truly make the round trip, but we think that's a feature
        ;; for import/export:
          = '(#x000A #x000D #xFFFF)
        for code from 0 below (expt 2 16)
        as s1
           = (make-wide-string
               1
               :initial-element (code-wide-character code))
        as s2 = (export-text-string s1 'utf-8-wide-string)
        as s3 = (import-text-string s2 'utf-8-wide-string)
        when (= (mod (+ code 1) 1000) 0)
          do (format t "#x~x..." code)
        when (= (mod (+ code 1) 5000) 0)
          do (terpri)
        do (unless (or (string=w s1 s3)
                       (member code permitted-import-export-exceptions))
             (cerror "continue testing"
                     "Failed UTF-8 roundtrip test on code #x~x; ~s => ~s => ~s"
                     code s1 s2 s3))
               (reclaim-wide-string s1)
           (reclaim-wide-string s2)
           (reclaim-wide-string s3)))





;;;; UTF-G


;;; The following discusses the design of UTF-G, "UCS Transformation Format -
;;; Gensym encoding"

;;; Note that gensym-string encoding is still a viable candidate for external
;;; representation of 5.0 text, e.g., in KBs, etc., for a while. This lets us
;;; defer on the external encoding issue, and compatibility therewith.
;;;
;;; In principle, we could even use it indefinitely as an internal processing,
;;; subject to the resolution of the some of following issues.
;;;
;;; The main issue is that
;;; when we either (a) have a policy for a while of not accepting any characters
;;; outside the Gensym repertoire (a subset of the Unicode characters); (b)
;;; signal an error or return a strange result if some characters in wide string
;;; can't be translated; or (c) extend the (classic) Gensym set to encompas all
;;; Unicode characters by hook or by crook.  Perhaps something like @Z<code
;;; encoded as for \ escape sequences> might be OK.
;;;
;;; On the other hand, this is somewhat incompatible with our published spec for
;;; the Gensym character, and would break our and potentially customers' parsers
;;; for it.
;;;
;;;
;;; Two possible extension methods that wouldn't break it is as follows:
;;;
;;; (1)
;;;
;;; Unicode 1.1 uses a bit over 50% of the 65,000 some characters, while we use
;;; only about 25% so far.  We could allocate the remaining 75% to the 50% that
;;; Unicode 1.1 needs.  I'll have to check about 2.0 to see if even it would fit.
;;; Unicode 2.0 is emerging right now as a replacement for 1.1.  I believe they
;;; have allocated more than 10,000 new characters, particularly for Korean.
;;;
;;; (1A)
;;;
;;; Allow 8-bit characters in UTF-G instead of just 7-bit characters.  This will
;;; easily allow all of Unicode, and then some, though at the cost of a fairly
;;; significant change in format, and loss of 7-bit/mail safeness.
;;;
;;;
;;; (2)
;;;
;;; Allocate a block of \ character codes for most significant unicode octets
;;; (MSO characters), calling them MS0-0, MSO-1, ..., MSO-255.  Allocate another
;;; block of \ character codes for least significant unicode octets (LSO
;;; characters), calling them LSO-0, LSO-1, ..., LSO-255.
;;;
;;; Then regard sequences of the form MSO+LSO as forming an arbitrary Unicode
;;; character whose value is computed as
;;;
;;;    (+ (* 256 (- MSO MSO-0))
;;;       (- LSO LSO-0))
;;;
;;; For example, say we make MSO-0 #x0600 and LSO-0 #x0700.  Then, say we
;;; encounter a sequence of two \ whose values are #x613 and #x7A4.  Then,
;;; we consider this to be the Unicode character whose value is given by
;;;
;;;   (+ (* 256 (- #x613 #x600)) (- #x7A4 #x700))
;;;
;;; or #x13A4 (5028 in decimal notation).
;;;
;;; Sequences other than MSO+LSO in Gensym text strings would of course be
;;; considered anomolous, but not illegal.  (To handle their translation to
;;; Unicode in such an anomolous case, they should probably be offset to the
;;; private-use zone of unicode.)
;;;
;;; Notice that this yields 65536 (2^16) code points.
;;;
;;; This design is based upon and inspired by the Unicode community's much
;;; discussed proposal "Extended UCS-2" proposal for extending Unicode to encode
;;; an additional 1,048,576 through the allocation of 1024 most-significant and
;;; 1024 least-signification unicode characters to be interpreted in a similar
;;; fashion.
;;;
;;; Implementation note: to do this most easily, a reader for a gensym character
;;; should be written that automatically skips past the first character of the
;;; pair when encountered and returns the pair
;;;
;;;    #\\ <16-bit code>
;;;
;;; after the second pair.  However, it should handle failures to properly pair
;;; codes in a robust manner if at all possible.

;; NB: The lowest level parts of the implementation of UTF-G are now in
;; CHARACTERS2; see map-unicode-to-gensym-character-code and
;; map-gensym-character-code-to-unicode.


;;; `Gensym-string-to-wide-string' copies its input argument
;;; gensym-string, which should be an (old-style) text string encoding Gensym
;;; characters, using what's now referred to as UTF-G, into a wide string with
;;; characters translated into in the Unicode character set, and encoded as
;;; single 16-bit bytes ("wide characters").

;;; This function is highly optimized for the case of a straight UTF-G to
;;; Unicode/Wide String conversion.

;;; `utf-g-string-to-unicode-text-string' is similar but takes a few optional
;;; arguments that give it more flexibility, with just a slight performance
;;; drop over gensym-string-to-wide-string.

;;; Start-index? and end-index? may be either nil or physical indices into
;;; gensym-string.  If nil, they default to 0 and the length of the string,
;;; respectively.
;;;
;;; NOTE: Both of these functions currently cannot deal with illegal sequences
;;; of Gensym characters.  They both should be able to do that!  Certain callers
;;; require that functionality, in particular import-text-string.  It must be
;;; added, or some other measure taken for its lack! (MHD 3/2/96)
;;;
;;; NOTE: Both of these MUST! be fixed to handle extended UTF-G characters,
;;; they are likely to come up in the not-too-distant future.



;;; `Twrite-unicode-from-utf-G-encoded-string' is a macro used to implement
;;; several functions below.  It is a little inelegant, and not totally hygenic,
;;; but that is mainly to achieve sanity, efficiency, and minimize the number of
;;; sources of obscure source code, hopefully down to one.
;;;
;;; String, start?, and end? are evaluated in order, once only, at run time.
;;; Wide-string-case? is evaluated at macro expansion time.

(defmacro twrite-unicode-from-utf-G-encoded-string
    (string start? end? wide-string-case?)
  (avoiding-variable-capture (string start? end?
                                     &aux simple? end i
                                     character-or-character-code
                                     escape-character?
                                     gensym-character-code)
    (let ((get-char-form
            (if wide-string-case?
                `(setq ,character-or-character-code
                       (read-gensym-character-from-wide-string
                         ,string ,i
                         ,escape-character?))
                `(setq ,character-or-character-code
                       (read-gensym-character-from-gensym-string
                         ,string ,i ,simple?
                         ,escape-character?))))
          (get-length-form
            (if wide-string-case?
                `(wide-string-length ,string)
                `(glength ,string ,simple?))))
      `(let (,@(unless wide-string-case?
                 `((,simple? (simple-gensym-string-p ,string)))))
         (loop with ,end fixnum = (or ,end? ,get-length-form)
             with ,i fixnum = ,(if (fixnump start?)
                                   start?
                                 (if (null start?)
                                     0
                                   `(or ,start? 0)))
               with ,character-or-character-code
               with ,escape-character?
               with ,gensym-character-code fixnum = 0
               while (<f ,i ,end)
               do ,get-char-form
               (setq ,gensym-character-code
                     (gensym-character-pair-to-code
                       ,character-or-character-code
                       ,escape-character?))
               (cond
                 ((=f (ashf ,gensym-character-code -8) #xF7)
                  (let ((current-extended-utf-g-low-half-character? ; *Special*
                          ,gensym-character-code))
                    (when (<f ,i ,end)
                      ;; If not followed by any char, ...
                      ,get-char-form
                      (setq ,gensym-character-code
                            (gensym-character-pair-to-code
                              ,character-or-character-code
                              ,escape-character?))
                      (when (=f (ashf ,gensym-character-code -8) #xF8)
                        ;; ... or if followed by an inappropriate second
                        ;; char, just don't translate this character.  (Or,
                        ;; review, when we have substitution character
                        ;; protocol in place!)
                        (twrite-char
                          (code-wide-character
                            (map-gensym-character-code-to-unicode
                              ,gensym-character-code)))))))
                 ;; Handle illegal character (currently #xFFFF) some way!!
                 (t
                  (twrite-char
                    (code-wide-character
                      (map-gensym-character-code-to-unicode
                        ,gensym-character-code))))))))))

;; Note: this can emit to either a wide or gensym string; consider not doing
;; that, just to save a few cycles; or make that a macroexpansion-time
;; parameter.

;; This also has to be made to deal with illegally encoded UTF-G strings, or at
;; least there needs to be some version of this that does that.  This currently
;; could bomb out if given an illegal ~ or \ escape sequence!  (MHD 6/18/96)

;; Notice that a double transformation is taking place: (1) multibyte to
;; widebyte and (2) Gensym character code to Unicode.  You can also
;; just to one or the other.
#| ; this function currently has no callers!
(defun utf-g-string-to-unicode-text-string
    (string &optional start-index? end-index?)
  (twith-output-to-text-string
    (cond
      ((gensym-string-p string)
       (twrite-unicode-from-utf-G-encoded-string
         string start-index? end-index? nil))
      (t
       (twrite-unicode-from-utf-G-encoded-string
         string start-index? end-index? t)))))
|#





(defun-simple gensym-string-to-wide-string (gensym-string)
  (twith-output-to-text-string
    (twrite-unicode-from-utf-G-encoded-string
      gensym-string 0 nil nil)))

;; Should probably be renamed gensym-string-to-text-string!





;;; `Read-kanji-code-from-wide-string' returns a kanji code produced from a
;;; kanji character in text-string that starts at the position just before that
;;; specified by index-variable.  Index-variable is advanced past the kanji
;;; character.

(defmacro read-kanji-code-from-wide-string
    (wide-string index-variable)
  (avoiding-variable-capture (wide-string &aux code)
    `(let* ((,code
               (wide-character-code
                 (read-character-from-wide-string
                   ,wide-string ,index-variable))))
       (declare (type fixnum ,code))
       (if (<f ,code 40)
           (+f (ashf ,code 13)
               (*f 95
                   (wide-character-code
                     (read-character-from-wide-string
                       ,wide-string ,index-variable)))
               (wide-character-code
                 (read-character-from-wide-string
                   ,wide-string ,index-variable))
               #.(- (+ (ash 32 13) (* 95 40) 32)))
           (+f (*f 95 ,code)
               (wide-character-code
                 (read-character-from-wide-string
                   ,wide-string ,index-variable))
               #.(+ (ash 33 13) (- (+ (ash 32 13) (* 95 40) 32))))))))




;;; `Twrite-gensym-character-code' translates gensym-character-code to
;;; its corresponding character-or-character-code and escape-character?
;;; pair, and then emits the resulting pair, using twrite-gensym-character,
;;; to the current output string.

(defun-substitution-macro twrite-gensym-character-code (gensym-character-code)
  (multiple-value-bind (character-or-character-code escape-character?)
      (gensym-character-code-to-pair gensym-character-code)
    (twrite-gensym-character character-or-character-code escape-character?)))

;; This should probably be removed to a CHARACTERS module somewhere!




;;; `Twrite-utf-g-from-text-string' twrites the UTF-G "octets" (all ASCII
;;; characters in the range [32..126]) from text-string.  This can be called
;;; in either a twith-output-to-text-string or twith-output-to-gensym-string
;;; context.

(defun-void twrite-utf-g-from-text-string (text-string)
  (loop with length fixnum = (text-string-length text-string)
        with i fixnum = 0
        with wide-character
        with gensym-character-code fixnum = 0
        with extended-code?
        for wide-string-index fixnum from 0
        while (<f i length)
        do (setq wide-character
                 (read-character-from-text-string text-string i))
           (multiple-value-setq (gensym-character-code extended-code?)
             (map-unicode-to-gensym-character-code
               (wide-character-code wide-character)))
           (twrite-gensym-character-code gensym-character-code)
           (when extended-code?
             (twrite-gensym-character-code extended-code?))))

;; Note: this cannot fail hard in any of its mappings, given any wide string,
;; but note that the results depend on special han-unification-mode, q.v.



;;; `Unicode-to-utf-g-wide-string' takes a Unicode-encoded wide string,
;;; text-string, and returns a UTF-G-encoded wide string.

(defun-simple unicode-to-utf-g-wide-string (text-string)
  (twith-output-to-wide-string
    (twrite-utf-g-from-text-string text-string)))

;;; `Unicode-to-utf-g-gensym-string' takes a Unicode-encoded wide string,
;;; text-string, and returns a UTF-G-encoded gensym string.

(defun-simple unicode-to-utf-g-gensym-string (text-string)
  (twith-output-to-gensym-string
    (twrite-utf-g-from-text-string text-string)))



(defmacro twrite-wide-character-code-as-gensym-characters (wide-character-code)
  `(let ((wide-character-code ,wide-character-code))
     (multiple-value-bind (gensym-character-code extended-code?)
         (map-unicode-to-gensym-character-code wide-character-code)
       (twrite-gensym-character-code gensym-character-code)
       (when extended-code?
         (twrite-gensym-character-code extended-code?)))))


(defvar intern-string-buffer
  (make-array (1+f intern-string-buffer-length)
              :element-type (gensym-string-char-type)
              :fill-pointer 0))

(defun twrite-intern-string-buffer-as-gensym-characters (size)
  (loop for i from 0 below size
        do (twrite-wide-character-code-as-gensym-characters
             (char-code (char intern-string-buffer i)))))

(def-concept next-character-for-intern)
(def-concept result-of-intern)

(defmacro interning-text-character-sequence (&body body)
  (let ((index (make-symbol "INDEX"))
        (next-char? (make-symbol "NEXT-CHAR"))
        (using-string-buffer-p (make-symbol "USING-STRING-BUFFER-P")))
    `(let ((,index 0)
           (,next-char? nil)
           (,using-string-buffer-p t))
       (twith-possible-output-to-gensym-string
         (macrolet ((next-character-for-intern (char)
                      `(progn
                         (setq ,',next-char? ,char)
                         (cond ((and ,',using-string-buffer-p
                                     (<f ,',index intern-string-buffer-length)
                                     (unicode-is-simple-gensym-character-p
                                       (wide-character-code ,',next-char?)))
                                (setf (char intern-string-buffer ,',index)
                                      (code-char (wide-character-code ,',next-char?))))
                               (t
                                (when ,',using-string-buffer-p
                                  (setq ,',using-string-buffer-p nil)
                                  (start-output-to-gensym-string)
                                  (twrite-intern-string-buffer-as-gensym-characters ,',index))
                                (twrite-wide-character-code-as-gensym-characters
                                  (wide-character-code ,',next-char?))))
                         (incff ,',index)))
                    (result-of-intern (&optional package?)
                      `(if ,',using-string-buffer-p
                           (intern-using-string-buffer intern-string-buffer ,',index ,package?)
                           (intern-gensym-string (finish-output-to-gensym-string) ,package?))))
           (progn ,@body))))))

;;; `Intern-wide-string' interns a symbol whose wide-symbol-name is string=w to
;;; wide-string.
(defun intern-wide-string (wide-string &optional package?)
  (prog1 (intern-wide-string-no-reclaim wide-string package?)
    (reclaim-wide-string wide-string)))

(defun intern-wide-string-no-reclaim (wide-string &optional package?)
  (interning-text-character-sequence
    (loop for index from 0 below (wide-string-length wide-string)
          do (next-character-for-intern (charw wide-string index)))
    (result-of-intern package?)))



;;; A `simple symbol' contains only simple gensym characters (basically ASCII
;;; except not @, ~, or \.  `Intern-simple-symbol-portion-of-wide-string' may
;;; only be used for interning simple symbols, and must be supplied explicitly
;;; with wide-string, start, end, and package? arguments.  If package? is nil, it means
;;; to use the current value of *package*.
;;;
;;; `Intern-and-upcase-simple-symbol-portion-of-wide-string' is similar, but in
;;; addition upcases lowercase (a-z) characters.

(defun-simple intern-simple-symbol-portion-of-wide-string (wide-string start end package?)
  (declare (type fixnum start end))
  (intern-gensym-string
    (loop with s = (obtain-simple-gensym-string (-f end start))
          for i from start below end
          as j from 0
          do (setf (schar s j)
                   (ascii-code-char (wide-character-code (charw wide-string i))))
          finally (return s))
    package?))

(defun-simple intern-and-upcase-simple-symbol-portion-of-wide-string (wide-string start end package?)
  (declare (type fixnum start end))
  (intern-gensym-string
    (let ((char #u0000))
      (declare (type wide-character char))
      (loop with s = (obtain-simple-gensym-string (-f end start))
            with case-delta fixnum = #.(-f (char-code #\A) (char-code #\a))
            for i from start below end
            as j from 0
            do (setq char (charw wide-string i))
               (setf (schar s j)
                     (ascii-code-char
                       (wide-character-code
                         (if (char<=w #.%\a char #.%\z)
                             (char+w char case-delta)
                             char))))
            finally (return s)))
    package?))




;;; The development function `test-utf-g-round-trip' tests that round-trip
;;; compatibility between Unicode and UTF-G encoding is working.  This should be
;;; run routinely to test for regressions, and especially whenever changes to
;;; UTF-G code is made.  This tests both the optimized utf-g transcoding, and
;;; that with transcoders.

#+development
(defun test-utf-g-round-trip ()
  (loop with permitted-import-export-exceptions
        ;; these don't truly make the round trip, but we think that's a feature
        ;; for import/export:
          = '(#x000A #x000D #xFFFF)
        for code from 0 below (expt 2 16)
        as s1
           = (make-wide-string
               1
               :initial-element (code-wide-character code))
        as s2 = (twith-output-to-wide-string
                  (twrite-utf-g-from-text-string s1))
        as s2-export = (export-text-string s1 'utf-g-wide-string)
        as s3 = (twith-output-to-wide-string
                  (twrite-unicode-from-utf-G-encoded-string
                    s2 nil nil t))
        as s3-import = (import-text-string s2-export 'utf-g-wide-string)
        when (= (mod (+ code 1) 1000) 0)
          do (format t "#x~x..." code)
        when (= (mod (+ code 1) 5000) 0)
          do (terpri)
        do (unless (string=w s1 s3)
             (cerror "continue testing"
                     "Failed roundtrip test on code #x~x; ~s => ~s => ~s"
                     code s1 s2 s3))
           (unless (or (string=w s1 s3-import)
                       (member code permitted-import-export-exceptions))
             (cerror "continue testing"
                     "Failed export/import roundtrip test on code #x~x; ~s => ~s => ~s"
                     code s1 s2-export s3-import))
               (reclaim-wide-string s1)
           (reclaim-wide-string s2)
           (reclaim-wide-string s3)
           (reclaim-wide-string s2-export)
           (reclaim-wide-string s3-import)))








;;; `Gensym-string-to-wide-string-using-streams' is for development-only.  It's
;;; an experimental version of gensym-string-to-wide-string.  This is version
;;; makes fairly clean use of the stream-like interface to text developed above.
;;; But it's slower than the previous version, so it's not going to be used in
;;; production.  The previous, "production" version, mostly because the faster
;;; version is speeded up by bypassing the streams abstraction -- I (MHD) just
;;; thought the stream method would be cooler. But it's not particularly
;;; strategic.

#+development
(defun-allowing-unwind gensym-string-to-wide-string-using-streams
    (gensym-string &optional start-index? end-index?)
  (let* ((wide-start-index? nil)
         (wide-end-index? nil)
         (result-wide-string
           (twith-output-to-wide-string
             (with-input-from-gensym-string-stream (gensym-string-stream gensym-string)
               (loop for wide-string-index from 0
                     with gensym-character-code
                     when (and start-index?
                               (=f start-index?
                                   (gensym-string-stream-index
                                     gensym-string-stream)))
                       do (setq wide-start-index? wide-string-index)
                     when (and end-index?
                               (=f end-index?
                                   (gensym-string-stream-index
                                     gensym-string-stream)))
                       do (setq wide-end-index? wide-string-index)
                     while (setq gensym-character-code
                                 (read-character-code gensym-string-stream))
                     do (twrite-wide-character
                          (code-wide-character
                            (map-gensym-character-code-to-unicode
                              gensym-character-code))))))))
    (values
      result-wide-string
      wide-start-index?
      wide-end-index?)))




(defun-simple wide-string-to-gensym-string (wide-string)
  (unicode-to-utf-g-gensym-string wide-string))

;; Consider eliminating this function in favor of the one it calls, after
;; changing callers to use subfunction.  Or make it a macro.  Note: in the first
;; Beta release of 5.0, this had its own code, which had a bug: it did not
;; properly write out both gensym characters in the case of an "extended UTF-G"
;; character sequence.  This might go unnoticed, since it would only involve
;; obscure, illegal, or unassigned ranges of Unicode's 16-bit encoding
;; space. (MHD 2/27/97)






;;;; Exporting to G2 Streams


;;; The functions in this section are used to encapsulate various
;;; idiomatic code needed to handle reading from UCS-2 streams using
;;; 8-bit operations.  Ultimately, these should be replace with true
;;; UCS-2 stream reading code, supported at a lower level.  These
;;; are thus far only used for I/O with streams via System procedures,
;;; called from FILE-SYSPROC, and for output to inspect files, called
;;; from QUERIES.

;;; Note: the functions in this section are declared ELIMINATE-FOR-GSI, since
;;; they are only used for G2.  It is assumed they will not be used for
;;; Telewindows either, but that's not been tested yet.

;;; NOTE: this code is eliminated for GSI.  In particular, there can be no
;;; refererences to C foreign functions for accessing G2 streams, since they are
;;; not part of GSI.





(def-substitution-macro 2-octet-byte-swapped-p (transcode-text-conversion-style)
  (if (memq-p-macro
        (transcode-external-character-set transcode-text-conversion-style)
        '(unicode-byte-swapped unicode-ucs-2-byte-swapped))
      t
      nil))

(def-substitution-macro n-octets-per-character (transcode-text-conversion-style)
  (if (memq-p-macro
        (transcode-external-character-set transcode-text-conversion-style)
        '(unicode unicode-byte-swapped
          unicode-ucs-2 unicode-ucs-2-byte-swapped))
      2
      1))

;;; `Preimported-text-lines-p' applies to lines (i.e., without internal
;;; linebreak characters) of text that are already in Unicode and have had their
;;; byte size ordering issues dealt with, and therefore don't need further
;;; processing for importing into G2, thus allowing the process of transcoding
;;; them to be skipped.  This corresponds to the four unicode UCS-2 variants
;;;
;;;   us-ascii latin-1
;;;   unicode unicode-byte-swapped
;;;   unicode-ucs-2 unicode-ucs-2-byte-swapped
;;;
;;; as they are handled by the line reader in FILE-SYSPROC, q.v.

(def-substitution-macro preimported-text-lines-p
    (transcode-text-conversion-style)
  (memq-p-macro
    (transcode-external-character-set transcode-text-conversion-style)
    '(us-ascii latin-1
      unicode unicode-byte-swapped
      unicode-ucs-2 unicode-ucs-2-byte-swapped)))

(def-substitution-macro export-two-octets-per-per-character-p
    (transcode-text-conversion-style)
  (memq-p-macro
    (transcode-external-character-set transcode-text-conversion-style)
    '(unicode unicode-byte-swapped)))


(defun-simple get-line-end-sequence-from-style (transcode-text-conversion-style)
  (case (transcode-unicode-line-separator-export-translation
          transcode-text-conversion-style)
    (per-platform
     (case g2-operating-system
       ((dos vms win32)
        '(#.%return #.%linefeed))
       (unix '(#.%linefeed))
       (t '(#.%linefeed))))                ; unknown platform
    (CR '(#.%return))
    (LF '(#.%linefeed))
    (CRLF '(#.%return #.%linefeed))
    (UNICODE-LINE-SEPARATOR '(#.%line-separator))
    (UNICODE-PARAGRAPH-SEPARATOR '(#.%paragraph-separator))))



(defun-simple g2-stream-write-line-with-end-character-sequence
    (line line-end-character-sequence g2-stream)
  (declare (eliminate-for-gsi))
  (when (g2-stream-write-string line g2-stream)
    (loop for character in line-end-character-sequence
          always (g2-stream-write-char character g2-stream))))

;; Move this. There's nothing specific to this module about it.



;;; G2-stream-write-unicode-ucs-2-line, g2-stream-write-unicode-ucs-2-string,
;;; and g2-stream-write-ucs-2-character are a cascade of entry points for
;;; writing unicode-ucs-2 characters to a g2-stream depending on whether
;;; you need to write a single character, a string of characters, or a
;;; string of characters terminated with a linebreak (i.e. a 'line').
;;;
;;; They all take a `byte-swapped-p' argument to determine the order in which
;;; the bytes of their characters are to appear. If this is nill they are
;;; big-endian, if nil, little-endian as used by NT among others. The unicode
;;; direction-indicating characters are not used.
;;;
;;; These functions operate on wide characters exclusively. The only
;;; respect in which they are really specific to unicode-ucs-2 is
;;; the provision for swapping bytes.

(defun-simple g2-stream-write-unicode-ucs-2-line
    (line line-end-character-sequence byte-swapped-p g2-stream)
  (declare (eliminate-for-gsi))
  (g2-stream-write-unicode-ucs-2-string line byte-swapped-p g2-stream)
  (loop for character in line-end-character-sequence
        always (g2-stream-write-ucs-2-character
                 character byte-swapped-p g2-stream)))


(defun-simple g2-stream-write-unicode-ucs-2-string
    (line byte-swapped-p g2-stream)
  (declare (eliminate-for-gsi))
  (loop for i from 0 below (lengthw line)
        as character = (charw line i)
        always (g2-stream-write-ucs-2-character
                 character
                 byte-swapped-p
                 g2-stream)))


(defun-simple g2-stream-write-ucs-2-character
    (character byte-swapped-p g2-stream)
  (when (g2-stream-write-char
          (if byte-swapped-p
              (wide-character-trail-octet-character character)
              (wide-character-lead-octet-character character))
          g2-stream)
    (g2-stream-write-char
      (if byte-swapped-p
          (wide-character-lead-octet-character character)
          (wide-character-trail-octet-character character))
      g2-stream)))



(defun-simple g2-stream-write-trailing-bytes-of-wide-string
    (string g2-stream)
  (loop for i from 0 below (lengthw string)
        as character = (charw string i)
        always (g2-stream-write-char
                 (wide-character-trail-octet-character character)
                 g2-stream)))





;;; These three `export-and-emit...' functions take lines, strings, or
;;; single characters comprised of wide-characters and have them written to
;;; the stream in encoded form as dictated by their transcode-text-
;;; conversion-style arguments. All of the heavy lifting is done by
;;; export-text-string-per-text-conversion-style.

(defun-simple export-and-emit-text-line
    (string transcode-text-conversion-style g2-stream)
  (declare (eliminate-for-gsi))
  (let ((encoded-string
          (export-text-string-per-text-conversion-style
            string transcode-text-conversion-style)))
    (prog1
        (and (g2-stream-write-wide-string-using-text-conversion-style
               transcode-text-conversion-style encoded-string g2-stream)
             (g2-stream-write-line-terminator-using-text-conversion-style
               transcode-text-conversion-style g2-stream))
      (if (gensym-string-p encoded-string)
          (reclaim-gensym-string encoded-string)
          (reclaim-text-string encoded-string)))))


(defun-simple export-and-emit-text-string
    (string transcode-text-conversion-style g2-stream)
  (declare (eliminate-for-gsi))
  (let ((encoded-string
          (export-text-string-per-text-conversion-style
            string transcode-text-conversion-style)))
    (prog1
        (g2-stream-write-wide-string-using-text-conversion-style
          transcode-text-conversion-style
          encoded-string g2-stream)
      (reclaim-text-string encoded-string))))


(defun-simple export-and-emit-character
    (character transcode-text-conversion-style g2-stream)
  (declare (eliminate-for-gsi))
  (let* ((string
           (twith-output-to-text-string (twrite-char character)))
         (encoded-string
           (export-text-string-per-text-conversion-style
             string transcode-text-conversion-style)))
    (prog1
        (g2-stream-write-wide-string-using-text-conversion-style
          transcode-text-conversion-style
          encoded-string g2-stream)
      (reclaim-text-string string)
      (reclaim-text-string encoded-string))))

(defun-simple g2-stream-write-wide-string-using-text-conversion-style
    (transcode-text-conversion-style wide-string g2-stream)
  (declare (eliminate-for-gsi))
  (let ((length (wide-string-length wide-string)))
    (declare (type fixnum length))
    (cond
      ((=f (n-octets-per-character transcode-text-conversion-style) 2)
       (cond
         ((export-two-octets-per-per-character-p
            transcode-text-conversion-style)
          (g2-stream-write-from-wide-string-buffer wide-string length g2-stream))
         (t
          (g2-stream-write-from-buffer wide-string length g2-stream))))
      (t (g2-stream-write-from-buffer wide-string length g2-stream)))))





;;; `G2-stream-write-line-terminator-using-text-conversion-style' writes
;;; the approprate character or characters for terminating a line
;;; as indicated by the text-conversion-style, encapulating all of
;;; the details.

(defun-simple g2-stream-write-line-terminator-using-text-conversion-style
    (transcode-text-conversion-style g2-stream)
  (let ((line-end-character-sequence
          (get-line-end-sequence-from-style transcode-text-conversion-style)))
    (if (=f 2  ; only other option is 1
            (n-octets-per-character transcode-text-conversion-style))
        (loop for character in line-end-character-sequence
              always (g2-stream-write-ucs-2-character
                       character
                       (2-octet-byte-swapped-p transcode-text-conversion-style)
                       g2-stream))
        (loop for character in line-end-character-sequence
              always (g2-stream-write-char
                       character g2-stream)))))





;;;; Did you know ....



;;;
;;; Legal values for the charset parameter of the MIME HTML type are:  (8/6/96)
;;;
;;;     charset = "US-ASCII"
;;;             | "ISO-8859-1"  | "ISO-8859-2"        | "ISO-8859-3"
;;;             | "ISO-8859-4"  | "ISO-8859-5"        | "ISO-8859-6"
;;;             | "ISO-8859-7"  | "ISO-8859-8"        | "ISO-8859-9"
;;;             | "ISO-2022-JP" | "ISO-2022-JP-2"     | "ISO-2022-KR"
;;;             | "UNICODE-1-1" | "UNICODE-1-1-UTF-7" | "UNICODE-1-1-UTF-8"
;;;             | token





;;;; Testing



(defvar standard-8-bit-non-graphic-characters-skip-spec
  '(0 1 (7 15) 8 9))




#+development
(defun write-transcode-test-character-table
    (stream n-rows n-columns skip-spec? n-octets
            byte-swapped-p line-end-character)
  (loop with skip-spec
          = (if (eq skip-spec? 't)
                nil
                (or skip-spec?
                    standard-8-bit-non-graphic-characters-skip-spec))
        for row from 0 below n-rows
        unless (member row skip-spec)
          do (loop with columns-to-skip
                     = (cdr (find row skip-spec
                                  :key #'(lambda (x) (if (consp x) (car x)))))
                   as column from 0 below n-columns
                   as wide-character
                      = (code-wide-character (+ (* row n-columns) column))
                   do (unless (member column columns-to-skip)
                          (write-wide-character-to-lisp-stream
                            stream wide-character n-octets byte-swapped-p)))
        do (write-wide-character-to-lisp-stream
             stream line-end-character n-octets byte-swapped-p)))


#+development
(defun write-wide-character-to-lisp-stream
    (stream wide-character n-octets byte-swapped-p)
  (cond
    ((=f n-octets 2)
     (cond
       (byte-swapped-p
        (write-char
          (code-char
            (wide-character-code
              (wide-character-trail-octet-character wide-character)))
          stream)
        (write-char
          (code-char
            (wide-character-code
              (wide-character-lead-octet-character wide-character)))
          stream))
       (t
        (write-char
          (code-char
            (wide-character-code
              (wide-character-lead-octet-character wide-character)))
          stream)
        (write-char
          (code-char
            (wide-character-code
              (wide-character-trail-octet-character wide-character)))
          stream))))
    (t
     (write-char
       (code-char
         (wide-character-code
           (wide-character-trail-octet-character wide-character)))
       stream))))


#+development
(defun generate-iso-8859-test-files ()
  (loop for part-number from 1 to 10
        do (with-open-file (stream (format
                                     nil
                                     "/home/mhd/tmp/mod/8859-~d.text"
                                     part-number)
                                   :direction :output)
             (write-transcode-test-character-table
               stream 16 16 nil 1 nil #.%linefeed))))

#+development
(defun generate-unicode-test-file ()
  (with-open-file (stream "/home/mhd/tmp/mod/unicode.text"
                          :direction :output)
    (write-transcode-test-character-table
      stream 16 16 nil 2 nil #.%line-separator)))

#+development
(defun generate-unicode-byte-swapped-test-file ()
  (with-open-file (stream "/home/mhd/tmp/mod/unicode-byte-swapped.text"
                          :direction :output)
    (write-transcode-test-character-table
      stream 16 16 nil 2 t #.%line-separator)))

#+development
(defun generate-all-transcode-test-files ()
  (generate-iso-8859-test-files)
  (generate-unicode-test-file)
  (generate-unicode-byte-swapped-test-file))




;;;; Design Note: Translation Style Plists

;;; Instead of showing the han-unification-mode at the top level of
;;; every translation style object, it should be in a plist.  Other
;;; things to consider putting there:
;;;
;;;   - handling of \ vs. Yen for Shift-JIS
;;;
;;;   - use of JIS-Roman vs. ASCII for ISO-2022 output
;;;
;;;   - Use of Unicode 1.1 vs. 2.0 for Hangul
;;;
;;;   - Use of conservative vs. non-conservative mode for UTF-7
;;;
;;; etc.

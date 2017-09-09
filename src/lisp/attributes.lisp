;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module ATTRIBUTES:  Attribute Values File Input.

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark David, Chris Morel, and Ong, Peng Tsin.


;;; Mark David is doing some maintenence work here.  An old backup
;;; version was spun off as this commenced with the name
;;; "ATTRIBUTES-65-6-18-91.LISP.65".  (MHD 1/6/92)




;;;; Attributes




;;; The purpose of the ATTRIBUTES module is to allow the user to modify item
;;; attributes by loading a text file.  This is a method of initializing
;;; attribute values at run time.  Currently, this feature is available by
;;; selecting the "Load Attribute File" menu-choice of the Miscellany Menu.
;;; Any attribute value that can be edited by the user in G2 should also be
;;; modifiable by loading the appropriate input from an Attribute File.

;;; The main function of this module is load-attribute-file.  This function
;;; processes the attribute file: it reads item, attribute, and value input,
;;; validates the input, and puts the values in the appropriate frame locations.

;;; The input file has the following format: 
;;;
;;; { item: <an item><RETURN>
;;;  {attribute: <an attribute><RETURN>
;;;   value: <a single or multi-line value><RETURN>
;;;   <RETURN>}* }*  
;;; 
;;;    where: <an item> is a constant designation.
;;;           <an attribute> is the slot alias, if any, otherwise the slot name.
;;;           <a single or multi-line value> is the same form as entered through
;;;             slot editing.
;;;           <RETURN> is any linebreak character (or character sequence)



;; Possible Future Changes:
;; 1. Allow the creation of items.
;; 2. Improved file format:
;;    a. Simpler format without the item, attribute, and value labels.
;;    b. Format similar to GFI event files.
;;    c. A spreadsheet format that would make the input of a large number of
;;       values simpler.
;;
;; MHD's list:
;;
;;   Allow comment lines.  #...<return>  OR   ; ... <return>






;;;; Constants and System-Variables for Attribute File Input




;;; `Attribute Input Labels' are strings that are used to specify the location
;;;  of item, attribute, and value information in the attribute input file.


(progn

  ;; Franz ACL compile complained constants were being redefined when this progn
  ;; was (eval-when (:compile-toplevel :load-toplevel :execute) ...).  It looks like it needn't be,
  ;; which is why I've changed it to a progn. -mhd, 6/17/00

(defconstant attribute-input-item-label #w"item:")

(defconstant attribute-input-attribute-label  #w"attribute:")

(defconstant attribute-input-value-label #w"value:")



;;; `attribute-input-white-space' is a list of legal white-space in the
;;; attribute input-file, that is ignored.   Note that #.%Linefeed is
;;; not present.

(defconstant attribute-input-white-space '(#.%Space #.%Tab #.%Return))

;; Presumably Linefeed is not present because it's always stripped out
;; by virtue of calling some read-line type of function to read in data
;; line by line.

) ; closes progn & comment about change from (eval-when ...)



;;; The class `attribute-file-input' is needed mostly when parsing a frame
;;; constant designation.  (The attribute-file-item-designation is first
;;; reclaimed if necessary, before being set.) It also holds other information
;;; during attribute-file input.

(def-class (attribute-file-input block)
  ;; choose a more appropriate parent class!! (?)
  (attribute-file-item-designation
    nil lookup-slot (type constant-designation) do-not-save)
  (attribute-file
    nil lookup-slot do-not-put-in-attribute-tables do-not-save))

;; Attribute-file-input class has a parent-class of "command", since a parent is
;; needed to run without error, and if the parent is "object" this class is
;; displayed when "new object" is chosen from a workspace menu.




;;; The system-variable `attribute-file-input-frame' is used when parsing a
;;; constant designation for an item from a text-string.  The resulting
;;; designation is saved in the frame of this system-variable.  The frame also
;;; holds other attribute-file input information.

(def-system-variable attribute-file-input-frame attributes nil)






;;;; Attribute Input Warnings




(defun attribute-input-no-label-warning (attribute-input-label)
  (warning-message* 1
      "Could not locate ~s in the attribute file.  ~
     Attempting to process the remainder of the file."
    attribute-input-label))

					; Is this still
					; necessary!!??

#+unused
(defun attribute-input-no-data-after-label-warning (attribute-input-label)
  (warning-message* 1
      "While loading an Attribute File, no data found for ~s.  ~
     Attempting to process the remainder of the file."
    attribute-input-label))


(defun attribute-input-no-item-data-warning (input-line)
  (warning-message* 1
      "While loading an Attribute File, missing item on line ~s.  ~
     Attempting to process the remainder of the file."
    input-line))


(defun attribute-input-no-attribute-data-warning (input-line)
  (warning-message* 1
      "While loading an Attribute File, missing attribute on line ~s.  ~
     Attempting to process the remainder of the file."
    input-line))


(defun attribute-input-no-value-data-warning (input-line)
  (warning-message* 1
      "While loading an Attribute File, missing value on line ~s.  ~
     Attempting to process the remainder of the file."
    input-line))


(defun attribute-input-text-parsing-error (unparsable-text)
  (warning-message* 1
      "While loading an Attribute File, could not parse the text ~s.  ~
     Attempting to process the remainder of the file."
    unparsable-text))


(defun attribute-input-text-bad-char-error (gensym-string)
  (warning-message* 1
      "While loading an Attribute File, could not read the text beginning with ~
     ~s.  An invalid character follows the text.  ~
     Attempting to process the remainder of the file."
    gensym-string))


(defun attribute-input-non-existent-frame-warning ()
  (warning-message* 1
      "While loading an Attribute File, the item `~ND' ~
       does not exist.  Attempting to process the remainder of the ~
       file."
    (attribute-file-item-designation attribute-file-input-frame)))


(defun attribute-input-temporary-constant-frame-warning (temporary-constant)
  (warning-message* 1
      "While loading an Attribute File, ~NC does not specify an item.  ~
       Attempting to process the remainder of the file."
    (constant-value temporary-constant)
    (constant-type temporary-constant)))


(defun attribute-input-invalid-slot-name-warning (illegal-slot-name)
  (warning-message* 1
      "While loading an Attribute File, an invalid attribute name, ~s, has been ~
     read.  Attempting to process the remainder of the file."
    illegal-slot-name))


(defun attribute-input-invalid-slot-value-warning (slot-value-string)
  (warning-message* 1
      "While loading an Attribute File, an illegal attribute value, ~s, has ~
     been read.  Attempting to process the remainder of the file."
    slot-value-string))

;; Substitution macros were changed to defuns.  I can't conceive of a reason why
;; they should be def-substitution-macros.  If someone feels they should be,
;; please see me.
;;
;; In addition, format control string segments of the form
;;
;;    \"~a\"
;;
;; were all changed to ~s, which is more correct as well as simpler.
;;
;; Also, generally tried to get all warnings into a single call to
;; (warning-message* ...), and succeeded.  It is hoped this will be
;; much a step along the way to eventual internationalization.
;;
;; (MHD 2/21/96)


(defun attribute-input-error-recovery-ignore-warning (input-string)
  (warning-message* 1 
      "Error recovery.  Skipping input line: ~s."
    input-string))

;; This used to truncate the line displayed to 40 characters, but that's a bad
;; idea. If you're debugging, and need to know, you can have a hard time finding
;; that information.  Meanwhile, wrapping the line works perfectly fine, or at
;; as well on average as the 40-character limit. (MHD 2/21/96)


(defun attribute-input-read-error ()
  (let ((error-text (most-recent-file-operation-status-as-text)))
    (warning-message* 1
	(if attribute-file-input-frame
	    "Cannot read from the Attribute File ~s: ~a.  The file is being closed."
	    "Cannot read from an Attribute File: ~a.  The file is being closed.")
      (if attribute-file-input-frame
	  (attribute-file attribute-file-input-frame)
	  error-text)
      error-text)
    (reclaim-text-string error-text)))


(defun attribute-input-can-not-open-file-error ()
  (warning-message* 1 
      (if attribute-file-input-frame
	  "Could not open the attribute file ~s."
	  "Could not open the Attribute File.")
    (if attribute-file-input-frame
	(attribute-file attribute-file-input-frame))))


(defun attribute-input-end-of-file-warning ()
  (warning-message* 1 
      (if attribute-file-input-frame
	  "While loading the Attribute File ~s, an unexpected end-of-file occurred."
	  "While loading the Attribute File, an unexpected end-of-file occurred.")
    (if attribute-file-input-frame
	(attribute-file attribute-file-input-frame))))






;;;; Utilities for Attribute File Input



;;; The function `g2-stream-read-line-for-attribute-file' Returns either nil or
;;; a text string.  If it encounters end-of-file or some other error, it simply
;;; return nil.  At present, it assumes that stream is supposed to consist of
;;; all gensym-character-set encoded characters (in UTF-G) and tabs and
;;; newlines.  If a non-UTF-G/non-tab/non-newline character is encountered, it
;;; calls attribute-input-text-bad-char-error to report the error with the
;;; relevant substring around the error.  If all goes well, it returns the text
;;; string containing all Unicode characters.  Note that for Han character
;;; translation into Unicode, this depends on the global han-unification-mode,
;;; q.v.  Apart from attribute-input-text-bad-char-error, this is supposed to be
;;; the only function that deals directly with gensym strings, UTF-G, and
;;; possible character set encoding problems.

(defun g2-stream-read-line-for-attribute-file (stream)
  (let* ((text-string?			; wide string with gensym encoding
	   (g2-stream-read-line stream)))
    (cond
      ((null text-string?)
       nil)
      (t
       (let ((gensym-string (wide-string-to-string text-string?))) ; gensym string w/ encoding
	 (multiple-value-bind
	     (legal-gensym-string-p? illegal-gensym-string-char-index?) 
	     (legal-gensym-string-p gensym-string)
	   (cond
	     ((not legal-gensym-string-p?)
	      (let ((gensym-string-substring
		      (gensym-string-substring
			gensym-string 0
			(or illegal-gensym-string-char-index?
			    (gensym-string-length gensym-string)))))
		(attribute-input-text-bad-char-error gensym-string-substring)
		(reclaim-gensym-string gensym-string-substring))
	      nil)
	     (t
	      (prog1 (import-text-string
		       gensym-string
		       'ATTRIBUTE-FILE-LINE)
		(reclaim-text-string text-string?)
		(reclaim-gensym-string gensym-string))))))))))

;; Adapt import-text-string to be able to take a "translation structure"
;; or some such thing, and put the report about illegal characters into
;; it!  (MHD 3/5/96)
      


;;; The function `attribute-input-find-non-white-space' returns the 0-based
;;; index of the first non-white-space character between the start and end of
;;; the string, a text string.  (A start and end within the string can be
;;; optionally be specified).  If no non-white-space character is found, NIL is
;;; returned.

(defun attribute-input-find-non-white-space
       (string &optional (start 0) (end nil))
  (loop for i = start then (+f i 1)
	with end = (if end
		       (minf (text-string-length string) end)
		       (text-string-length string))
	until (or (>=f i end)
		  (not (wide-character-member
			 (charw string i)
			 attribute-input-white-space)))
	finally
	  (if (>=f i end)
	      (return nil)
	      (return i))))




;;; The function `locate-attribute-input-label' attempts to locate the specified
;;; label at the start of the input-string, ignoring white-space.  If the label
;;; is found, the 0-based input-string index past the label is returned.
;;; Otherwise, NIL is returned.  (The input-line argument is not reclaimed.)

(defun locate-attribute-input-label (input-string label-string)
  (let ((start-index (attribute-input-find-non-white-space input-string))
	(end-index (text-string-length input-string))
	(label-length (text-string-length label-string)))

    (if (<=f label-length (-f end-index start-index))
	(if (text-string-equal+
	      label-string input-string
	      :start2 start-index
	      :end2 (+f start-index label-length))
	    ;; return index past the label.
	    (+f start-index label-length))
	;; return NIL.
	nil)))




;;; The function `attribute-input-terminator-line-p' returns T if the input-line
;;; is a termination line.  Otherwise, NIL is returned.  The termination line is
;;; a line containing only white-space.  This line is used to terminate "values"
;;; that can have multiple lines.

(def-substitution-macro attribute-input-terminator-line-p (input-string)
  (not (attribute-input-find-non-white-space input-string)))




;;; The function `read-complete-attribute-input-value' accepts the first line of
;;; input for an attribute value as its argument and returns the complete
;;; attribute value (a text-string) or NIL if a read error occurs.  If the value
;;; in the first input-line is not complete (i.e., the value is not followed by
;;; a blank-line, containing only white-space), one or more input lines are read
;;; from the file.  (The input-line argument is not reclaimed here.)

(defun read-complete-attribute-input-value (input-line input-stream)
  (let* ((fatal-error? nil)
	 (value-string? 
	   (twith-output-to-text-string
	     (loop with ends-with-newline?	; writes 1st line
		     = (twrite-string-as-input-line input-line nil)
		   for new-input-line?
		       = (g2-stream-read-line-for-attribute-file input-stream)
		   until (or (null new-input-line?)
			     (attribute-input-terminator-line-p new-input-line?))
		   do (if (not ends-with-newline?) (twrite-char #.%space))
		      (setq ends-with-newline?
			    (twrite-string-as-input-line
			      new-input-line? (not ends-with-newline?)))
		      (reclaim-text-string new-input-line?)
		   finally
		     (if (and (null new-input-line?)
			      (not (g2-stream-last-error-is-eof-p)))
			 (setf fatal-error? t)
			 ;; Else, if no error, reclaim value-termination line
			 ;;   (i.e., whitespace).
			 (when new-input-line?
			   (reclaim-text-string new-input-line?)))))))
    (if fatal-error?
	(progn (attribute-input-read-error)
	       (if (text-string-p value-string?)
		   (reclaim-text-string value-string?))
	       ;; return value.
	       nil)
	;; else ok, return the complete input-value string.
	value-string?)))

;; Converted to use the new function I wrote below, twrite-string-as-input-line.
;; It now obeys the new conventions we're establishing for the user to allow
;; him to enter newlines, and also to require that his input be legal-text-
;; string-p for the most part.  (MHD 2/3/92)





;;; Twrite-string-as-input-line ...  returns ends-with-newline?.  This value, if
;;; true, indicates that the next line, if any, should not begin with a space,
;;; since the line separator (@L in UTF-G) already serves that purpose.  That is
;;; a user-documented convention.  If skip-initial-whitespace?  is true, this
;;; does not twrite the leading whitespace in input-line.  This is intended to
;;; be called after a linebreak that does not come after an explicit line
;;; separator (@L); the purpose of this is to allow users to format their text
;;; in the ascii input file with indentation without worrying about the
;;; indentation translating into space characters when formatted in G2.

;;; Input-line must be a text string.

(defun twrite-string-as-input-line
       (input-line &optional skip-initial-whitespace?)
  (loop with string-length = (text-string-length input-line)
	with past-whitespace? = nil
	with char
	as last-char? = nil then char
	as i from 0
	when (=f i string-length)
	  do (cond
	       ((and last-char?
		     (newline-p last-char?))
		(return t))
	       (t
		(return nil)))
	do (setq char (charw input-line i))
	   (when (and skip-initial-whitespace?
		      (not past-whitespace?)
		      (not (wide-character-member
			     char attribute-input-white-space)))
	     (setq past-whitespace? t))
	   (cond
	     ((and skip-initial-whitespace?
		   (not past-whitespace?)))
	     ((char=w char #.%tab)
	      (loop repeat
		      (maxf
			(number-of-spaces-to-insert-on-a-tab editor-parameters)
			1)
		    do (twrite-char #.%space)))
	     (t
	      (twrite-char char)))))






;;; The function `read-ignore-and-display-complete-attribute-input-value'
;;; accepts the first line of input for an attribute value as its argument and
;;; reads additional lines until the value is completed, a read error occurs, or
;;; an end of file occurs.  T is returned if the value is read successfully,
;;; otherwise NIL is returned.  This function is used in "error recovery" mode
;;; when a non-fatal error has occurred during processing of an attribute file.
;;; The information associated with the error is being ignored (and some of this
;;; input is displayed to the user) so that the remainder of the file can be
;;; processed.  (The input-line argument is not reclaimed here.)

(defun read-ignore-and-display-complete-attribute-input-value
       (input-line? input-stream)
  ;; This first line is being "skipped", for error recovery.
  ;; Display only this line to the user.
  (attribute-input-error-recovery-ignore-warning input-line?)
  (loop for new-input-line? = (g2-stream-read-line-for-attribute-file input-stream)
	for line-count = 0 then (+f line-count 1)
	until (or (null new-input-line?)
		  (attribute-input-terminator-line-p new-input-line?))
	do (reclaim-text-string new-input-line?)
	   ;; these lines are also being "skipped", for error recovery.
	finally
	  ;; Inform the user of additional lines skipped.
	  (when (>f line-count 0)
	    (warning-message
	      1 "Error recovery.  Skipping ~d input line~a."
	      line-count (if (=f line-count 1) "" "s")))
	  (cond ((and (null new-input-line?) 
		      (not (g2-stream-last-error-is-eof-p)))
		 ;; fatal error.
		 (attribute-input-read-error)
		 (return nil))
		(t (when new-input-line?
		     ;; Else, if no error, reclaim value-termination line
		     ;;   (i.e., whitespace).
		     (reclaim-text-string new-input-line?))
		   (return t)))))






;;;; Process Attribute File Input



;;; The function `process-attribute-input-item' accepts a text-string argument
;;; (a line of text already ready from the attribute input file) and returns an
;;; evaluated frame designation or nil.  (This frame is the item whose attribute
;;; will receive a new value.) First, the name of the frame is located beginning
;;; at the start-index or the start of the input-string, ignoring leading
;;; white-space.  Then, the frame designation is created, and evaluated.  If
;;; this all succeeds, the evaluated frame designation is returned and the item
;;; designation is saved in the attribute-file-item-designation slot of the
;;; system-variable attribute-file-input-frame.  Otherwise, NIL is returned.

(defun process-attribute-input-item (input-string starting-index?)
  (let ((current-index?  (attribute-input-find-non-white-space
			   input-string (or starting-index? 0))))
    (cond
      ((null current-index?)
       (attribute-input-no-item-data-warning input-string)
       nil)
      (t
       (when (attribute-file-item-designation attribute-file-input-frame)
	 (reclaim-slot-value
	   (attribute-file-item-designation attribute-file-input-frame))
	 (setf (attribute-file-item-designation attribute-file-input-frame)
	       nil))
       (cond
	 ;; Note that parse-text-for-slot has a side-effect of putting the
	 ;; designation in the attribute-file-item-designation of
	 ;; attribute-file-input-frame.  A return value of NIL means that the
	 ;; parse failed.
	 ((null
	    (parse-text-for-slot
	      (convert-text-string-to-text
		(text-string-substring	; becomes a text string here
		  input-string current-index? (text-string-length input-string)))
	      attribute-file-input-frame
	      (get-slot-description-of-frame
		'attribute-file-item-designation
		attribute-file-input-frame)))
	  ;; Text parsing error.
	  (let ((unparsable-text
		  ;; reclaimed below
		  (text-string-substring
		    input-string current-index?
		    (text-string-length input-string))))
	    (attribute-input-text-parsing-error unparsable-text)
	    (reclaim-text-string unparsable-text)
	    ;; Error, return value.
	    nil))
	 (t
	  ;; Parsed okay.
	  (let ((current-computation-flags current-computation-flags))
	    (setf (role-serve-inactive-objects?) t)
	    (let* ((*current-computation-frame* 
		     attribute-file-input-frame)
		   (item? (evaluate-designation
			    (attribute-file-item-designation
			      attribute-file-input-frame)
			    nil)))
	      (cond ((null item?)
		     (attribute-input-non-existent-frame-warning)
		     ;; error.
		     nil)
		    ((temporary-constant-p item?)
		     (attribute-input-temporary-constant-frame-warning
		       item?)
		     (reclaim-temporary-constant item?)
		     (setf item? nil)
		     ;; error.
		     nil)
		    (t 
		     ;; Successly evaluated to an item.
		   item?))))))))))




;;; The function `process-attribute-name-for-attribute-input-if-legal' accepts a
;;; text-string argument (a line of text already ready from the attribute input
;;; file) and returns the slot description, if any, for a legal, user-editable
;;; slot, or NIL, if the attribute is not validated.  (This attribute that will
;;; receive a new value.)  First, the attribute name is located beginning at the
;;; start-index or the start of the input-string, ignoring leading white-space.
;;; Then, the attribute is validated by testing if it is an attribute, alias for
;;; an attribute, or an unnamed slot (e.g., text) for the frame, and that it is
;;; ok for the user to modify this attribute.

(defun process-attribute-name-for-attribute-input-if-legal
    (input-string frame starting-index?)

  ;; NOTE: now input-string is a text string, and and starting-index? is
  ;; either nil or the (adjusted) starting index for that string.
  (let ((current-index?
	  (attribute-input-find-non-white-space
	    input-string (or starting-index? 0)))
	class-qualifier? attribute-name?)
    ;; If the start of the attribute name data is found, then parse it.
    (cond
      ((null current-index?)
       (attribute-input-no-attribute-data-warning input-string)
       ;; No attribute found.
       nil)
      (t
       
       (multiple-value-setq-some (attribute-name? nil class-qualifier?)
	   (read-attribute-name-from-text-string
	     input-string current-index?))
       (cond
	 ((null attribute-name?)
	  (attribute-input-text-parsing-error input-string)
	  nil)
	 (t
	  (let ((slot-description?
		  (get-slot-description-if-editable-attribute
		    frame attribute-name? class-qualifier?)))
	    (cond ((null slot-description?)
		   ;; Error, could not validate the attribute.
		   (attribute-input-invalid-slot-name-warning attribute-name?)
		   nil)
		  (t slot-description?)))))))))

;; MHD: read-symbol-from-string doesn't handle quoting characters at all
;; or characters that need quoting.  E.g.  (read-symbol-from-string
;; "JOEiBOB" 0 7) => JOEIBOB, with the i capitalized;
;; (read-symbol-from-string "JOE BOB" 0 7) => JOE (with the space and
;; BOB missing); (read-symbol-from-string "JOE@ BOB" 0 7) => JOE (with
;; the space and BOB missing).

;; It should be fixed to require a legal text string, and to expect
;; nonsimple characters.
;;
;; When this is done, you can enter, say, the following "symbol" (shown as
;; it would appear if printed without quoting character, e.g., in a name
;; box)
;;
;;   A SYMBOL WITH SPACES, COMMAS, PARENS, AND A COLON(:)
;;
;; with text in the attribute file
;;
;;    A~@ SYMBOL~@ WITH~@ SPACES~@,~@ COMMAS~@,~@ PARENS~@,~@ AND~@ A~@ COLON~@(~@:~@)
;;
;; When written parsably in G2, say in an attribute table, it would look the same
;; except that the ~@'s would just be @'s, i.e.,
;;
;;    A@ SYMBOL@ WITH@ SPACES@,@ COMMAS@,@ PARENS@,@ AND@ A@ COLON@(@:@)
;;
;; Why can this not be the format used to enter the symbol in the attribute file?
;; Because @ is the quoting character within symbols.  It must be quoted itself.
;; Also, latin characters must also be quoted.  If the following came in
;;
;;    ~U
;;
;; It would look to the user like a symbol one character long, consisting of the
;; single character U-Umlaut.  A Kanji character might have @ in it, e.g.,
;;
;;    \3"@
;;
;; [The above is not yet quite coherent!! FIX!! -- (MHD 1/6/92)]





;;; The function `process-attribute-input-value' accepts a text-string argument
;;; (the first line of input of an attribute value ready from the attribute
;;; input file) and returns T if a value was successfully read, validated, and
;;; stored, in the item's attribute.  First, the value is located beginning at
;;; the start-index or the start of the input-string, ignoring leading
;;; white-space.  Additional input lines are read as necessary (until an
;;; attribute-input terminator line or end of file is reached).  If the value is
;;; complete and valid for the item attribute, it is stored in the item's
;;; attribute, and T is returned.  If the value is not valid or if it is
;;; incomplete, an error message is displayed and NIL is returned.

(defun process-attribute-input-value
    (input-string input-stream frame slot-description starting-index?)
  (let ((current-index?
	  (attribute-input-find-non-white-space
	    input-string (or starting-index? 0))))
    (cond
      ((null current-index?)
       (attribute-input-no-value-data-warning input-string)
       ;; Error, No value found.
       nil)
      (t
       ;; If the start of the attribute slot data is found, try read the
       ;; complete value.
       (let* ((first-value-input-line
		;; Reclaimed below.
		(text-string-substring
		  input-string current-index? (text-string-length input-string)))
	      (complete-value-text-string?
		(read-complete-attribute-input-value
		  first-value-input-line input-stream)))
	 (reclaim-text-string first-value-input-line)
	 (cond
	   ((null complete-value-text-string?)
	    ;; Error in the reading of the completed value.
	    ;; Error message was already displayed.
	    nil)
	   ;; A complete value text-string.
	   (t
	    
	    (cond
	      ;; Note that parse-text-for-slot may have the side-effect of
	      ;; putting the value in the attribute.  A return value of NIL
	      ;; means that the parse failed.
	      ((null
		 (parse-text-for-slot
		   ;; Parses the complete value text-string, and if valid, puts
		   ;; it in the item attribute.
		   (convert-text-string-to-text
		     ;; Note that the string is copied here in case it is
		     ;; needed for the following error message.  (The parsing
		     ;; function reclaims its text argument.)
		     (text-string-substring
		       complete-value-text-string? 0
		       (text-string-length complete-value-text-string?)))
		   frame slot-description))
	       (attribute-input-invalid-slot-value-warning
		 complete-value-text-string?)
	       (reclaim-text-string complete-value-text-string?)
	       nil)
	      (t
	       ;; The value is OK and was placed in the attribute.
	       (reclaim-text-string complete-value-text-string?)
	       ;; SUCCESS.
	       t)))))))))






;;;; Load Attribute File - Main Function




;;; The function `load-attribute-file' is the main (top-level) function for
;;; Attribute File input.  It is called by executing the "Load Attribute File"
;;; menu-choice from the Miscellany menu.

;;; Any attribute value that can be edited by the user in G2 should also be
;;; modifiable by loading the appropriate input from an Attribute File.

;;; This function processes the attribute file by reading item, attribute, and
;;; value input, validating the input, and putting the values in the appropriate
;;; frame locations.

;;; File syntax: 
;;;
;;; { item: <an item><RETURN>
;;;  {attribute: <an attribute><RETURN>
;;;   value: <a single or multi-line value><RETURN>
;;;   <RETURN>}* }*  
;;; 
;;; where: <an item> is a constant designation.
;;;        <an attribute> is the slot alias, if any, otherwise the slot name.
;;;        <a single or multi-line value> is the same form as entered through
;;;         slot editing.

;;; If a fatal error occurs, file processing is stopped, a warning is displayed
;;; to the user, and nil is returned.  If a non-fatal error occurs, processing
;;; will continue past the error if possible.
;;;
;;; Fatal errors: 
;;;   Could not open file; 
;;;   Could not read from file;
;;;   Unexpected end-of-file.
;;;
;;; Non-fatal errors: 
;;;   Invalid (or missing) item, attribute, or value;
;;;   Incorrect (or missing) label (e.g., attribute-input-item-label);
;;;   Missing blank line after a value (except at end-of-file).

;;; Side Effects: 
;;;   The attribute values are set as indicated in the Attribute File. 
;;;   If an attribute already contains a subtable as its value, this is deleted
;;;     when the attribute receives a new value.

;;; Return Value: if the input file is successfully processed T is returned 
;;;    (this includes recovering from a non-fatal error);
;;;   otherwise NIL is returned.


(defun load-attribute-file (gensym-pathname)
  (let* ((input-file? (if (gensym-pathname-p gensym-pathname)
			  (gensym-namestring gensym-pathname)
			  nil))
	 (input-stream? (if (and input-file? (text-string-p input-file?))
			    (g2-stream-open-for-input input-file?)
			    nil)))
    (cond
      ((null input-stream?)
       (attribute-input-can-not-open-file-error)
       (reclaim-if-text-string input-file?)
       ;; return value
       (return-from load-attribute-file nil))
      (t
       (loop for input-line? = (g2-stream-read-line-for-attribute-file input-stream?)
			     then (progn
				    (when input-line?
				      (reclaim-text-string input-line?))
				    (g2-stream-read-line-for-attribute-file input-stream?))
	     with input-result? = nil
	     with index-after-label? = nil
	     with item? = nil
	     with slot-description? = nil
	     with value-processed-p? = nil
	     with fatal-error? = nil
	     with non-fatal-error? = nil
	     with eof? = nil

	     initially
	       (setf attribute-file-input-frame
		     (make-frame 'attribute-file-input))
	       (setf (attribute-file attribute-file-input-frame) 
		     input-file?)
	     do (cond
		  ((null input-line?)
		   ;; End Of File (expected or not) or Read Error.
		   (if (g2-stream-last-error-is-eof-p)
		       (if (and (not non-fatal-error?) (not value-processed-p?))
			   ;; Unexpected end of file.
			   (progn
			     (attribute-input-end-of-file-warning)
			     (setf fatal-error? t))
			   ;; Expected end of file
			   (setf eof? t))
		       ;; read error
		       (progn
			 (attribute-input-read-error)
			 (setf fatal-error? t))))

		  ;; if "white space" don't process.
		  ((null (attribute-input-find-non-white-space input-line?)))

		  (non-fatal-error?
		   ;; Attempt Error Recovery.  Process the remaining file if
		   ;; possible.  (If the next attribute-input-item-label is found,
		   ;; process the remainder of the file.)
		   (setf index-after-label? 
			 (locate-attribute-input-label
			   input-line? attribute-input-item-label))
		   (cond (index-after-label?
			  ;; ITEM-LABEL was found.  Process the item designation.
			  (setq input-result? 
				(process-attribute-input-item 
				  input-line? index-after-label?))
			  (cond ((null input-result?)
				 ;; Another non-fatal error.
				 (setf non-fatal-error? t))
				(t (setf item? input-result?)
				   ;; Clear these flags, since now must locate the
				   ;; attribute name and attribute value.
				   (setf non-fatal-error? nil)
				   (setf slot-description? nil)
				   (setf value-processed-p? nil))))
			 
			 ((locate-attribute-input-label
			    input-line? attribute-input-value-label)
			  ;; VALUE-LABEL is found on the current-line, skip
			  ;; the complete (possibly several lines) "value",
			  ;; display a warning to the user, and try error recovery
			  ;; on next iteration.
			  (if (not (read-ignore-and-display-complete-attribute-input-value
				     input-line? input-stream?))
			      (setf fatal-error? t)))
			 
			 ;; ATTRIBUTE-LABEL is on this line.  Skip this line.  Try
			 ;; every recovery again with the next line on the next
			 ;; iteration.
			 (t (attribute-input-error-recovery-ignore-warning
			      input-line?))))

		  (value-processed-p?
		   ;; Process ATTRIBUTE or ITEM LABEL.
		   ;; Value has been placed in the item's attribute.
		   ;; Next check for another attribute or item.
		   (setf index-after-label?
			 (locate-attribute-input-label
			   input-line? attribute-input-attribute-label))
		   (if index-after-label?
		       ;; ATTRIBUTE label found.
		       (progn
			 (setq input-result?
			       (process-attribute-name-for-attribute-input-if-legal
				 input-line? item? index-after-label?))
			 (cond ((null input-result?)
				(setf non-fatal-error? t))
			       (t
				;; here, input-result? is a slot description
				(setq slot-description? input-result?)
				;; reset slot name and value flag, since
				;;   these are now needed.
				(setf value-processed-p? nil))))
		       ;; Check for ITEM label.
		       (progn
			 (setf index-after-label?
			       (locate-attribute-input-label
				 input-line? attribute-input-item-label))
			 (if index-after-label?
			     ;; ITEM label found.
			     (progn
			       (setq input-result?
				     (process-attribute-input-item
				       input-line? index-after-label?))
			       (cond ((null input-result?)
				      (setf non-fatal-error? t))
				     (t (setf item? input-result?)
					;; reset slot-description and value flag, since
					;;   these are now needed.
					(setf slot-description? nil)
					(setf value-processed-p? nil))))
			     ;; Item-label not found.  
			     (progn (setf non-fatal-error? t)
				    (attribute-input-no-label-warning
				      attribute-input-item-label))))))

		  (slot-description?
		   ;; process VALUE, since the attribute is present.
		   (setf index-after-label?
			 (locate-attribute-input-label
			   input-line? attribute-input-value-label))
		   (if index-after-label?
		       ;; VALUE label found.
		       (progn
			 ;; Attempt to read the complete value and STORE THE VALUE
			 ;; IN THE ATTRIBUTE OF THE ITEM.
			 (setq input-result?
			       (process-attribute-input-value
				 input-line? input-stream?
				 item? slot-description?
				 index-after-label?))
			 
			 (if (null input-result?)
			     (setf non-fatal-error? t)
			     (setf value-processed-p? input-result?)))
		       ;; Value-label not found.  
		       (progn (setf non-fatal-error? t)
			      (attribute-input-no-label-warning
				attribute-input-value-label))))

		  (item?
		   ;; process ATTRIBUTE, since the item is present.
		   (setf index-after-label?
			 (locate-attribute-input-label
			   input-line? attribute-input-attribute-label))
		   (if index-after-label?
		       ;; VALUE label found.
		       (progn
			 (setq input-result?
			       (process-attribute-name-for-attribute-input-if-legal
				 input-line? item? index-after-label?))
			 (if (null input-result?)
			     (setf non-fatal-error? t)
			     (progn
			       (setf slot-description? ; input-result? is a slot description
				     input-result?))))
		       ;; Attribute-label not found.  
		       (progn (setf non-fatal-error? t)
			      (attribute-input-no-label-warning
				attribute-input-attribute-label))))

		  (t 
		   ;; Process ITEM, since neither item, attribute, or value are
		   ;; present. 
		   (setf index-after-label?
			 (locate-attribute-input-label
			   input-line? attribute-input-item-label))
		   (if index-after-label?
		       ;; VALUE label found.
		       (progn
			 (setq input-result?
			       (process-attribute-input-item 
				 input-line? index-after-label?))
			 (if (null input-result?)
			     (setf non-fatal-error? t)
			     (setf item? input-result?)))
		       ;; Item-label not found.  
		       (progn (setf non-fatal-error? t)
			      (attribute-input-no-label-warning
				attribute-input-item-label)))))

	     until (or fatal-error? eof?)

	     finally
	       ;; Reclaim and reset.

	       (if (text-string-p input-line?)
		   (reclaim-text-string input-line?))
	       (if input-stream?
		   (g2-stream-close input-stream?))

	       (when (attribute-file-item-designation 
		       attribute-file-input-frame)
		 ;; reclaim and reset the item constant designation.
		 (reclaim-slot-value
		   (attribute-file-item-designation 
		     attribute-file-input-frame))
		 (setf (attribute-file-item-designation 
			 attribute-file-input-frame) nil))

	     ;; reclaim the pathname namestring.
	       (reclaim-if-text-string input-file?)

	     ;; Reset the attribute-file, so that it is not reclaimed when
	     ;; the frame is deleted.
	       (setf (attribute-file attribute-file-input-frame)
		     nil)
	       (delete-frame attribute-file-input-frame)

	       (return
		 (if fatal-error?
		     nil
		     (if eof?
			 ;; finished processing (ok or continued from
			  ;; non-fatal error).
			  t
			  ;; not fatal error, did not continue.
			  nil))))))))


;; There may is a CONS LEAK, when strings (and floats) are stored in attributes!!
;; When replacing attribute values that are simple-text strings with simple-text
;; strings, new strings are being created.  The strings should be recycled.
;; This leak seems to be in the "parse-text-for-slot" code.  This also occurs
;; when editting directly, e.g., when modifying a variable!!

;; The load-attribute-file function could be made more efficient!!  In some
;; cases the attribute-input label is tested twice: e.g., after having processed
;; and put a value into an attribute, the label is tested for item-label and
;; attribute-label, which is retested when processing the item or attribute
;; input.

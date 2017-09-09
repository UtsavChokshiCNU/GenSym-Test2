;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module DOC

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark David and Lowell B. Hawkinson








;;;; Documentation Conventions



;;;; Standards

;;;  1.0 Standards Manual.  Where appropriate, the Chicago Manual of Style, 13th
;;; edition, (the "CMS") should be used to decide on all issues of style.  The
;;; guidelines presented here are all intended to be compatible with that
;;; manual.  The manual is the major publishing industry standard and is readily
;;; available at most bookstores.

;;;  2.0 Layout.  Headers should be preceeded by six blank lines and followed by
;;; four blank lines. 
;;;
;;; A block of public documentation text should be preceeded by four blank lines
;;; and followed by one blank line. 
;;;
;;; Paragraphs of text are generally delimited by blank lines.  The lines may or
;;; may not have leading semicolons and blanks, according to the writer's
;;; preference.  There is no special indentation for the first or following
;;; lines of text.  Text should usually begin one column after the final
;;; semicolon.  However, in comments that do not begin in the first column of
;;; the page, we prefer to see a hanging indent of two spaces for following
;;; lines of a paragraph.  This is because it often not possible or desirable to
;;; add blank lines between paragraphs and because these paragraphs usually
;;; refer to code to the left of the first line of the paragraph.  Also these
;;; "paragraphs" are usually cryptic notes that generally do not span more than
;;; one line, thus making them further suitable for hanging indentation.  In
;;; comments that are preceeded by only one semicolon to the right of code, it
;;; is acceptable to use no space in the first column after the semicolon.  A
;;; space here is still preferred and is, to repeat, required in all other
;;; cases. 

;;; Lines should be at most eighty (80) columns long (including the leading
;;; semicolons and spaces).

;;;  3.0 Grammar and Punctuation.
;;;
;;;  3.1 Please note especially the Manual's specification on the use of a comma
;;; to separate each item in a series of three or parts of speech, including the
;;; last one before the conjunction.
;;;
;;;    Examples. 
;;;    
;;;       The good, the bad, and the ugly. 
;;;
;;;       foo, bar, baz, and blech
;;;
;;;       tall, dark, and handsome

;;;  3.2 Please note the Manual's specification on the use of ellipses (...).
;;; The American style of always three periods, regardless of the position of
;;; the missing text, is preferred.

;;;  3.3 Disregard the Manual's information on spelling of computer terms. See
;;; section 7.0 below. I.e. A Database is not a "Data Base", and Real-time is
;;; not Real time.


;;;  4.0 Printing, Typography, and Logo.  The standard Gensym type family for
;;; all publications Helvetica (also called Swiss).  The standard Gensym colors
;;; are Grey and Aquamarine.  These have PMS (Pantone Marking System) numbers
;;; 431 (for Grey) and 320 (for Aquamarine).  In future versions of the system,
;;; some amount of software will be devoted to rendering the logo on screens and
;;; printers in the appropriate colors.  Until then, consult the Marketing
;;; department of Gensym for help in reproducing the logo and colors.

;;;  5.0 Spelling, Capitalization, and Typesetting.  The name Gensym is always
;;; spelled with the first letter only capitalized and the rest lowercase.

;;;  6.0 Legal Notifications. Confidential product information (product
;;; descriptions) should bear the following notice of confidentiality on its
;;; cover page:
;;;
;;;    The information contained herein is confidential and
;;;    proprietary to Gensym Corporation, and is to be used by the
;;;    recipient only for purposes of evaluating the product described
;;;    herein.  The information may not be disclosed or transferred,
;;;    directly or indirectly, to any third party.

;;;  7.0 Miscellaneous Stylistic Conventions
;;;
;;; Lisp  (not LISP)
;;;
;;; Common Lisp  (not CommonLISP, Common LISP, or CommonLisp; two words)
;;;
;;; CLtL - stands for Common Lisp the Language, the book by Guy L. Steele, Jr.
;;; CLtL2 - stands for Common Lisp the Language, 2nd Edition, the book by
;;; Guy L. Steele, Jr.
;;;
;;; Timestamp
;;;
;;; Filename
;;;
;;; Database
;;;
;;; Real-time (when used as an adjective; "real time" as a noun; e.g. "The
;;; real-time version performs these operations in real time.")
;;;
;;; Runtime 
;;;
;;; "Knowledge base" is two words. (Also use KB, the common abbreviation for
;;; this)
;;;
;;; Names of modules (i.e. the name component of the pathnames of source files)
;;; should always be written in all upper case: e.g. BOOTSTRAP, WINDOWS1, etc.
;;;
;;; Lisp symbols are often written in all uppercase.  This allows one to avoid
;;; ugly syntactic conventions such as using the lisp symbol quoting character
;;; "'", or making wordy reference to the fact that reference is made to a Lisp
;;; object of type symbol.  For example,
;;;
;;;     Parsing-extension-mode may be T, END, or NO-AUTOCOMPLETION.
;;;
;;; vs.
;;;
;;;     Parsing-extension-mode may be 't, 'end, or 'no-autocompletion.
;;;
;;; But this can be overdone, especially for longer symbol names that have
;;; enough hyphens (-) in them that it is obvious that reference is made to
;;; a symbol.







;;;; Writing Software Documentation



;;; In source code there are basically five types of documentation.  They are
;;; `Public', `Heading', `Private', `In-line', and `Side-line'.  To give you a
;;; quick glance, in the following example of a source file: the A text is
;;; public, the B text is heading, the C text is private, the D text is in-line,
;;; and the E text is side-line.



;;; ;; -*- bbbb: bbbb -*-
;;; 
;;; ;;;; bbbbb b bbb bbbbbbbbbbbb
;;;
;;;
;;;
;;; ;;; aaa a aaaaaa a aaaaaa aa aaa aaaa a aa a aaaa aa aaaa aaaa a aaa
;;; ;;; aaaa a a aaa aaaaa.  aaaa aaa a aa aaaa aa a a aaaaaa aaaaa aaaaa.
;;; ;;;
;;; ;;; a aaaaa aaaaa a aa aaa aa aaa.  aaaa aaaa aa aaaa aa aaaa aaaa  a aa
;;; ;;; aa aa a aaaaaa aa aa.
;;; 
;;; (defun foo (a b c)
;;;   ;; d dd ddd dddd ddddd dddddd ddddddd ddddddd
;;;   ;;   ddd dddd ddd dddd ddd dddd ddd dddd ddd.
;;;   (cond
;;;     ((foo-p a)				; ee eee eeee eee
;;; 						;   eee eee eee eeeee
;;;      (bar b)				; ee eeeee eee
;;;     (t (values b c)))))
;;; 
;;; ;; cccc cccc ccc ccc cc c ccc cc ccc cccc ccc c cc cc cc cc cc cc c c c
;;; ;; cc ccc cc cc!

;;; Public documentation is the most important documentation as that is the
;;; documentation that the public (e.g. your fellow programmers, our
;;; documentation writers, and perhaps even customers) will read.  It is not
;;; unreasonable to expect that about one third of the time you spend editing
;;; source files will be spent writing, revising, and rewriting your public
;;; documentation.  You are strongly urged not to skimp on this important task.
;;; Public documentation will automatically be extracted by the codoc ("Code
;;; Documenter") program, and since this is a very valuable and convenient
;;; service, a good deal of the conventions here are intended to make it
;;; possible for codoc to do its job, some times, rarely, we hope, at the
;;; expense of elegance or convenience to its users.
;;; 
;;; Public documentation should not require or expect its readers to read the
;;; source code or any other kinds of documentation in the file.  It is intended
;;; to be stand-alone and should not assume that the reader has the code in
;;; front of him.  On the other hand, none of this is to say that your
;;; documentation is intended for the layman!  It is first of all intended for
;;; yourself and anyone who may use any part of a program that you have written.
;;; In addition, certain things in the source, such as the name of the function
;;; and arguments, want to be in the codoc output documentation but do not
;;; naturally belong in the public documentation as it appears in the source.
;;; These facilities are described below.
;;;
;;; All of your documentation, but especially, your public documentation should
;;; adhere to several trivial rules of style, grammar, and punctuation.  Please
;;; avoid "doing your own thing"; if for no other reason, consider that doing so
;;; may be create extra work for other people in the organization, such as
;;; documentation writers as well as yours truly, the author of codoc.
;;;
;;; Public documentation appears, syntactically, as paragraphs of fully
;;; punctuated, upper and lower case, readable english text whose lines all
;;; begin in column five.  Each line has a semicolon in each of its first three
;;; columns and has a space in its fourth column.  Tabs are never used to begin
;;; paragraphs.  Paragraphs are delimited by blank lines or lines that just
;;; contain three semicolons (;;;) in the first three columns and nothing else.
;;;
;;; A hyphen (-) at the end of a line should only be used in a word where that
;;; hyphen would naturally occur, rather than merely as a punctuation mark.  For
;;; example, you can put "foo-" on the end of a line if the word (or lisp
;;; symbol, obviously) it is breaking up is "foo-bar", but not if it is
;;; "foobar".  If you absolutely must hyphenate words that don't have hyphens,
;;; please use the German language convention of using the equal sign (=) for
;;; this exact pur= pose (I think).
;;;
;;; Upon the definition (or redefinition after several megabytes have gone by)
;;; of a new term, you can `italicize', `boldface', or, let us just say,
;;; `introduce' it by enclosing it in backward- (`) and forward- (') quotation
;;; marks, as was done, for example, in this very sentence with the words
;;; italicize, boldface, and introduce.  When introducing a new term, generally
;;; use the singular form of it when putting it in quotes, e.g., "A `foo' is
;;; a kind of a bar.  Foos are used in special situations. ..."  The quote marks
;;; should not be used simply as a device to get something into the index.  
;;;
;;; Heading documentation usually just consists of single-line section titles,
;;; labels, and the like, used to mark the beginning of some public
;;; documentation.  `Headings' or `Headers', as this type of documentation is
;;; sometimes called, should not be used to introduce code or anything other
;;; than public documentation.  For example, a poor use of headers would be to
;;; have the heading "Source Code" followed by a bunch of source (lisp) code.  A
;;; good use on the other hand, would be the heading "Frames" followed by
;;; several paragraphs of public documentation all about frames.  Headings are
;;; just like section headings in books.  They should follow chapter or title
;;; capitalization rules:  capitalize the first letter of important words;
;;; do not capitalize all letters, unless they normally should appear in all
;;; capital letters, e.g. module names; etc.  The heading line should also be
;;; preceeded by about six blank lines and followed by four blank lines.
;;;
;;; Whether to put blank lines to mark spaces between paragraphs, as opposed to
;;; putting lines with just ";;;" at the beginning, is up to the individual
;;; writing the documentation.
;;;
;;; Use of long strings of printing characters to separate sections of source
;;; files, e.g. ";;;;;;;;;;;;;;;;;;;;;;;;;;", ";-------------------------", etc.,
;;; is discouraged.  Proper and consistent use of vertical whitespace should
;;; reduce or eliminate the need for such devices.

;;; Fonts should never be used in G2 documentation.  Nor should non-USASCII
;;; characters.  Only plain US ASCII text is allowed.

;;; Stick to the standard, Emacs "-*-" headers as well.  These are occasionally
;;; updated (for, e.g., copyright year), but all should follow a standard,
;;; uniform format.  They are generally cut-and-paste'ed in to ensure
;;; consistency.









;;;; Producing Documentation



;;; Document-system produces documentation for a system in text file format,
;;; complete with indexing of definitions and "interesting symbols".  The output
;;; file, whose truename is the single value returned from the function, has as
;;; its path the system-pathname of the system, as its name the name of the
;;; system, and as type the extension "doc".  This facility does not currently
;;; break lines if they are too long.  It does however insert a page break about
;;; every seventy lines and between modules.  The recommended maximum length of
;;; a line of lines of text (code as well) is about eighty characters.  (Emacs
;;; users can discover their current cursor position by using the C-X = command
;;; sequence, which prints out their position in terms of x, y, character, and
;;; line.  Most emacs's also support "autofill", but it tends to work a little
;;; different in each implementation.)

;;; An `interesting symbol' is defined as a string of six or more characters
;;; which, when capitalized, is the print-name of a symbol which is an internal
;;; symbol in the AB package and is either a function or a declared variable.
;;; Symbols may be broken at either a hyphen over a single line break and still
;;; be recognized.

;;; Definitions may be broken at a hyphen of space between words and still
;;; recognized.

;;; The index produced has two columns.  In the first column the interesting
;;; symbols or definitions appear.  A definition appears without the quote marks
;;; and is followed by the string of characters "(Def.)".  In the second column,
;;; the page numbers are listed with commas separating them.  [It is possible
;;; for the page numbers to fall off the right side of the page.  In fact, it is
;;; possible for any of the lines to fall off the right side of the page.  None
;;; of this is handled yet.  Printers and editors will have to do the best they
;;; can for now.]

;;; Headings are underlined.


(defparameter default-number-of-lines-per-page 75)
(defparameter default-number-of-pages-per-volume 150)
(defparameter default-output-file-type "text")

(defun document-system (system-name)
  
    (let ((file-output-stream? nil))
      (unwind-protect-for-development document-system
	  (loop with system = (normalize-system-name system-name)
		with date-notice
		  = (multiple-value-bind (second minute hour date month year)
			(get-decoded-real-time)
		      second minute hour
		      (format nil "Printed on ~d ~a ~d"
			      date
			      (cadr
				(assoc
				  month
				  '((1 "January") (2 "February") (3 "March")
				    (4 "April") (5 "May") (6 "June") (7 "July")
				    (8 "August") (9 "September") (10 "October")
				    (11 "November") (12 "December"))))
			      year))
		with lines-per-page = default-number-of-lines-per-page
		with pages-per-volume = default-number-of-pages-per-volume
		with quotations
		with interesting-symbols
		with headers
		with new-contents-entries
		with table-of-contents = nil
		with sorted-index-entries = nil
		with current-page-number = 1
		with current-volume-number = 1
		with files-written = nil
		for module in (all-lisp-source-file-symbols system)
		as first-time? = t then nil
		as module-pathname
		   = (make-system-pathname 'ab module 'lisp ':newest)
		initially
		  (setq file-output-stream?
			(open (make-system-pathname
				system-name
				(format nil "~(~a~)-volume-~a"
					system-name current-volume-number)
				default-output-file-type ':newest)
			      ':direction ':output))
		do
	    (when (>= current-page-number pages-per-volume)
	      (format t "~&End of Volume ~A" current-volume-number)
	      (push (truename file-output-stream?) files-written)
	      (close file-output-stream?)
	      (setq file-output-stream? nil)
	      (incf current-volume-number)
	      (setq current-page-number 1)
	      (setq first-time? t)
	      (setq file-output-stream?
		    (open (make-system-pathname
			    system-name
			    (format nil "~(~a~)-volume-~a"
				    system-name current-volume-number)
			    default-output-file-type ':newest)
			  :direction :output)))
	    (format t "~&Documenting module ~a ... " module)
	    (when (not first-time?)
	      (incf current-page-number)
	      (format file-output-stream? "~&~|~&"))
	    (multiple-value-setq
	      (quotations interesting-symbols headers new-contents-entries
			  current-page-number)
	      (document-file-1
		module-pathname file-output-stream?
		(make-boxed-lines
		  (format nil "~a: ~a" system module)
		  ""
		  "Copyright (c) 1986 - 2017 Gensym Corporation."
		  "All Rights Reserved."
		  ""
		  date-notice)
		lines-per-page
		current-page-number
		current-volume-number))
	    (setq sorted-index-entries
		  (merge 'list	;note that merge is guaranteed to be stable
			 sorted-index-entries
			 (stable-sort
			   (nconc quotations interesting-symbols headers)
			   #'string-lessp ':key #'car)
			 #'string-lessp ':key #'car))
	    (setq table-of-contents (nconc table-of-contents new-contents-entries))
	    (format t "Done.~&")
		finally
		  (format t "~%Done traversing files.~%")
		  (push (truename file-output-stream?) files-written)
		  (close file-output-stream?)
		  (setq file-output-stream? nil)
		  (with-open-file
		    (index-file (make-system-pathname
				  system-name
				  (format nil "~(~a~)-index" system-name)
				  default-output-file-type ':newest)
				:direction :output)
		    (print-index
		      index-file sorted-index-entries
		      lines-per-page current-page-number)
		    (push (truename index-file) files-written))
		  (format t "Done printing index.~&")
		  (with-open-file
		    (contents-file (make-system-pathname
				     system-name
				     (format nil "~(~a~)-contents" system-name)
				     default-output-file-type ':newest)
				   :direction :output)
		    (print-table-of-contents
		      (make-boxed-lines
			(format nil "Documentation for ~a" system-name)
			""
			""
			"Copyright (c) 1986 - 2017 Gensym Corporation."
			"All Rights Reserved."
			""
			date-notice)
		      table-of-contents
		      lines-per-page
		      contents-file)
		    (push (truename contents-file) files-written))
		  (format t "Done printing table of contents.~&")
		  (return (reverse files-written)))
	(if file-output-stream?
	    (progn
	      (format *error-output* "~&Aborted!~&")
	      (close file-output-stream? ':abort t))
	    (format t "~&Done.~&")))))

(defun document-module (module-name
			&optional (system-name 'ab)
			(output-file nil))
  (let* ((system (normalize-system-name system-name))
	 (file (if output-file
		   (pathname output-file)
		   (make-system-pathname
		     system
		     (format nil "~(~a~)-doc" module-name)
		     "text" ':newest)))
	 (module-pathname
	   (make-system-pathname system module-name 'lisp :newest))
	 (date-notice
	   (multiple-value-bind (second minute hour date month year)
	       (get-decoded-real-time)
	     second minute hour
	     (format nil "Printed on ~d ~a ~d"
		     date
		     (cadr
		       (assoc
			 month
			 '((1 "January") (2 "February") (3 "March")
			   (4 "April") (5 "May") (6 "June") (7 "July")
			   (8 "August") (9 "September") (10 "October")
			   (11 "November") (12 "December"))))
		     year)))
	 (index-entries nil)
	 (table-of-contents nil))
    (list
      (with-open-file (output file :direction :output)
	(multiple-value-bind (quotations interesting-symbols headers
			      new-contents-entries current-page-number)
	    (document-file-1
	      module-pathname output
	      (make-boxed-lines
		(format nil "~a: ~a" system module-name)
		""
		"Copyright (c) 1986 - 2017 Gensym Corporation."
		"All Rights Reserved."
		""
		date-notice)
	      default-number-of-lines-per-page 1 1)
	  (setq index-entries
		(stable-sort
		  (nconc quotations interesting-symbols headers)
		  #'string-lessp ':key #'car))
	  (format output "~&~|")
	  (print-index
	    output index-entries
	    default-number-of-lines-per-page current-page-number)
	  (setq table-of-contents new-contents-entries))
	(truename output))
      (with-open-file (output (make-system-pathname
				system
				(format nil "~(~a~)-contents" module-name)
				"text"
				:newest)
			      :direction :output)
	(print-table-of-contents
	  (make-boxed-lines
	    (format nil "Documentation for ~a" module-name)
	    ""
	    ""
	    "Copyright (c) 1986 - 2017 Gensym Corporation."
	    "All Rights Reserved."
	    ""
	    date-notice)
	  table-of-contents
	  default-number-of-lines-per-page
	  output)
	(truename output)))))


(defmacro string-head-= (string1 string2 char-count)
  `(string= ,string1 ,string2 :end1 ,char-count))

(defvar header-underliner-string (make-string 100 ':initial-element #\-))

(defun document-file-1
       (file destination header-lines lines-per-page current-page-number volume-number
	&aux (file-output-stream? nil))
  (unwind-protect-for-development document-file-1
    (with-open-file (file file)
      (loop for line? = (read-line file nil nil)
	    with line-number = 1
	    with page-number = current-page-number
	    with comment-prefix-length
	    with last-line-was-one? = t
	    with interesting-symbols = nil
	    with last-line-if-hyphenated? = nil
	    with hyphenation-start
	    with hyphenation-end
	    with last-line-if-quotation-started? = nil
	    with quotations = nil
	    with quotation
	    with quotation-start
	    with quotation-end
	    with candidate-string
	    with interesting-symbol?
	    with line-end-index
	    with line-start-index
	    with line-not-a-header?
	    with headers = nil
	    with table-of-contents-entries
	      = (list (list (format nil "~a Module"
				    (pathname-name (truename file)))
			    (cons volume-number page-number))
		      nil)
	    initially
	      (setq destination
		    (if (eq destination t)
			*standard-output*
			(if (streamp destination)
			    destination
			    (setq file-output-stream?
				  (open destination ':direction ':output)))))
	      (loop for header-line in header-lines
		    do (write-line header-line destination)
		       (incf line-number))
	    while line?
	    do
	(cond
	  ((or (setq line-not-a-header?
		     (string-head-=
		       line? ";;; "
		       (progn
			 (setq comment-prefix-length 4)
			 (min (length line?) comment-prefix-length))))
	       (string-head-=
		 line? ";;;; "
		 (progn
		   (setq comment-prefix-length 5)
		   (min (length line?) comment-prefix-length))))
	   (incf line-number)
	   ;; If this is a header line, double space before it.
	   (when (null line-not-a-header?)
	     (incf line-number 2)
	     (when (not (>= line-number lines-per-page))
	       (format destination "~2%")))
	   (when (>= line-number lines-per-page)
	     (format destination "~&~|~&")
	     (incf page-number)
	     (setq line-number 1))
	   (write-line
	     line? destination
	     ':start (setq line-start-index comment-prefix-length)
	     ':end (setq line-end-index
			 (let ((position-of-hyphen?
				 (position-if-not
				   #'(lambda (character)
				       (eql character #\space))
				   line?
				   :from-end t
				   :start line-start-index)))
			   (if position-of-hyphen?
			       (+ position-of-hyphen? 1)
			       line-start-index))))
	   (when (null line-not-a-header?)
	     (incf line-number)
	     (write-line
	       header-underliner-string destination
	       ':start 0 ':end (- line-end-index line-start-index))
	     (let ((header-name (subseq line? comment-prefix-length)))
	       (push (list header-name (cons volume-number page-number) 'header)
		     headers)
	       (push (list header-name (cons volume-number page-number))
		     table-of-contents-entries)))
	   (if last-line-if-quotation-started?
	       (let ((previous-record?
		       (assoc 
			 (setq quotation
			       (concatenate
				 'string
				 (subseq
				   last-line-if-quotation-started?
				   (+ quotation-start 1) quotation-end)
				 (if last-line-if-hyphenated? "" " ")
				 (subseq
				   line? line-start-index
				   (or (position-if
					 #'(lambda (character)
					     (eql character #\'))
					 line?
					 ':start line-start-index
					 ':end line-end-index)
						;punt if didn't fit on 2 lines
				       line-end-index))))
			 quotations :test #'string-equal)))
		 (if previous-record?
		     (setf (cdr previous-record?)
			   (nconc (cdr previous-record?)
				  (list (cons volume-number page-number))))
		     (push (list quotation (cons volume-number page-number))
			   quotations))))
	   (if last-line-if-hyphenated?
	       (progn
		 (setq candidate-string
		       (concatenate
			 'string
			 (subseq
			   last-line-if-hyphenated?
			   hyphenation-start hyphenation-end)
			 (subseq
			   line?
			   (setq line-start-index
				 (or (position-if-not
				       #'(lambda (character)
					   (eql character #\space))
				       line?
				       ':start line-start-index
				       ':end line-end-index)
				     line-start-index))
			   (setq line-start-index
				 (or (position-if-not
				       #'(lambda (character)
					   (or (alphanumericp character)
					       (member
						 character '(#\* #\? #\-)
						 ':test #'eql)))
				       line?
				       ':start line-start-index
				       ':end line-end-index)
				     line-start-index)))))
		 (if (setq interesting-symbol?
			   (symbol-if-interesting candidate-string))
		     (let ((previous-record?
			     (assoc
			       interesting-symbol? interesting-symbols
			       :test #'eq)))
		       (if previous-record?
			   (if (not (member (cons volume-number page-number)
					    (cddr previous-record?)
					    :test #'equal))
			       (setf (cddr previous-record?)
				     (nconc (cddr previous-record?)
					    (list (cons volume-number
							page-number)))))
			   (push (list interesting-symbol?
				       candidate-string
				       (cons volume-number page-number))
				 interesting-symbols))))))
	   (setq last-line-if-hyphenated?
		 (if (and (> line-end-index line-start-index)
			  (eql (char line? (- line-end-index 1)) #\-)
			  (not
			    (=
			      (setq
				hyphenation-start
				(let ((word-start-position?
					(position-if-not
					  #'(lambda (character)
					      (or (alphanumericp
						    character)
						  (eql character #\-)))
					  line?
					  ':end (- line-end-index 1)
					  ':start line-start-index
					  ':from-end t)))
				  (if word-start-position?
				      (+ word-start-position? 1)
				      line-start-index)))
			      (- line-end-index 1))))
		     (progn
		       (setq hyphenation-end line-end-index)
		       (setq line-end-index hyphenation-start)
		       line?)))
	   (loop with symbol-start? = line-start-index
		 while (and symbol-start?
			    (setq symbol-start?
				  (position-if
				    #'(lambda (character)
					(or (alphanumericp character)
					    (eql character #\*)))
				    line?
				    :start symbol-start?
				    :end line-end-index)))
		 do
	     (setq candidate-string
		   (subseq
		     line? symbol-start?
		     (setq symbol-start?
			   (position-if-not
			     #'(lambda (character)
				 (or (alphanumericp character)
				     (member
				       character '(#\* #\? #\-)
				       :test #'eql)))
			     line?
			     :start symbol-start?
			     :end line-end-index))))
	     (if (setq interesting-symbol?
		       (symbol-if-interesting candidate-string))
		 (let ((previous-record?
			 (assoc interesting-symbol?
				interesting-symbols :test #'eq)))
		   (if previous-record?
		       (if (not (member (cons volume-number page-number)
					(cddr previous-record?)
					:test #'equal))
			   (setf (cddr previous-record?)
				 (nconc (cddr previous-record?)
					(list (cons volume-number
						    page-number)))))
		       (push (list interesting-symbol? candidate-string
				   (cons volume-number page-number))
			     interesting-symbols)))))
	   (setq last-line-if-quotation-started?
		 (loop with quotation-start? = line-start-index
		       with quotation-end?
		       do
		   (if (setq quotation-start?
			     (position-if
			       #'(lambda (character) (eql character #\`))
			       line? ':start quotation-start?
			       ':end line-end-index))
		       (if (setq quotation-end?
				 (position-if
				   #'(lambda (character)
				       (eql character #\'))
				   line?
				   :start quotation-start?
				   :end line-end-index))
			   (let ((previous-record?
				   (assoc
				     (setq quotation
					   (subseq
					     line?
					     (+ quotation-start? 1)
					     (setq quotation-start?
						   quotation-end?)))
				     quotations :test #'string-equal)))
			     (if previous-record?
				 (setf (cdr previous-record?)
				       (nconc (cdr previous-record?)
					      (list (cons volume-number
							  page-number))))
				 (push (list quotation
					     (cons volume-number page-number))
				       quotations)))
			   (return
			     (setq quotation-start quotation-start?
				   quotation-end line-end-index
				   last-line-if-quotation-started?
				   line?)))
		       (return nil))))
	   (setq last-line-was-one? t))
;	  ((and nil				; not implemented yet
;		(string= line? "(def" ':end1 4))	;  check some mode/parameter here?
;	   (multiple-value-bind (definition-lines?
;				 current-line-in-stream
;				 definition-type name arglist)
;	       ;; Read definition name and arglist from string and
;	       ;; stream
;	       (extract-arglist-lines-from-stream line? file)
;	     definition-lines?			; none of this implemented yet
;	     current-line-in-stream
;	     definition-type name arglist))
	  (last-line-was-one?
	   (terpri destination)
	   (incf line-number 1)
	   (setq last-line-was-one? nil)
	   (setq last-line-if-hyphenated? nil)
	   (setq last-line-if-quotation-started? nil)))
	    finally
	      (return
		(values quotations interesting-symbols headers
			(reverse table-of-contents-entries) page-number))
	      (when file-output-stream?
		(close file-output-stream?)
		(setq file-output-stream? nil))))
    (if file-output-stream?
	(close file-output-stream? ':abort t))))


(defun make-boxed-lines (&rest lines)
  (let* ((max-length 
	   (loop for line in lines
		 maximize (length line)))
	 (top-line
	   (make-string (+ max-length 10) ':initial-element #\_))
	 (next-to-top-line
	   (make-string (+ max-length 10) ':initial-element #\space))
	 (bottom-line
	   (make-string (+ max-length 10) ':initial-element #\_)))
    (setf (subseq top-line 0 1) " ")
    (setf (subseq top-line (- (length top-line) 1) (length top-line)) " ")
    (setf (subseq next-to-top-line 0 1) "|")
    (setf (subseq next-to-top-line
		  (- (length next-to-top-line) 1) (length next-to-top-line))
	  "|")
    (setf (subseq bottom-line 0 1) "|")
    (setf (subseq bottom-line (- (length bottom-line) 1) (length bottom-line))
	  "|")
    (nconc (list top-line)
	   (list next-to-top-line)
	   (loop for line in lines
		 collect (format nil "~5a~va~5@:a" "|" max-length line "|"))
	   (list bottom-line))))

(defun print-index
       (stream sorted-index-entries lines-per-page current-page-number)
  (let ((line-number 1) (page-number current-page-number))
    (format stream "~3%Index~2%")
    (format stream "Index Entry ")
    (loop repeat (- 56 (length "Index Entry "))
	  do (write-char #\. stream))
    (format stream " Volume:Page~2%")
    (setq line-number 8)
    (incf page-number)
    (loop for index-entry in sorted-index-entries
	  do
      (when (>= (incf line-number) lines-per-page)
	(format stream "~&~|~&")
	(format stream "Index Entry ")
	(loop repeat (- 56 (length "Index Entry "))
	      do (write-char #\. stream))
	(format stream " Volume:Page~2%")
	(incf page-number)
	(setq line-number 3))
      (loop for extra-page-entry
		in
		(cond ((symbolp (first index-entry))
		       (format stream "~a "
			       (second index-entry))
		       (loop repeat
			       (max (- 60 (1+ (length (second index-entry)))) 3)
			     do (write-char #\. stream)
			     finally
			       (format stream " ~2d:~3d"
				       (car (third index-entry))
				       (cdr (third index-entry))))
		       (nthcdr 3 index-entry))
		      ((eq (third index-entry) 'header)
		       (format stream "~a (Header) " (first index-entry))
		       (loop repeat
			       (max (- 60 (+ (length (first index-entry)) 10))
				    3)
			     do (write-char #\. stream)
			     finally
			       (format stream " ~2d:~3d"
				       (car (second index-entry))
				       (cdr (second index-entry))))
		       (nthcdr 3 index-entry))
		      (t
		       (format stream "~a (Def) " (first index-entry))
		       (loop repeat
			       (max (- 60 (+ (length (first index-entry)) 7)) 3)
			     do (write-char #\. stream)
			     finally
			       (format stream " ~2d:~3d"
				       (car (second index-entry))
				       (cdr (second index-entry))))
		       (nthcdr 2 index-entry)))
	    do (format stream ", ~a: ~a"
		       (car extra-page-entry)
		       (cdr extra-page-entry)))
      (terpri stream))))

(defun print-table-of-contents
       (cover-page table-entries lines-per-page output)
  (let ((line-number 1))
    (loop for line in cover-page
	  do
      (write-line line output))
    (format output "~&~|~&")
    (let ((summary-header (make-boxed-lines "Summary of Contents")))
      (loop for line in summary-header
	    do
	(write-line line output))
      (format output "~%Module ")
      (loop repeat (- 57 (length "Module ")) do (write-char #\. output))
      (format output " Volume:Page~2%")
      (setq line-number (+ (length summary-header) 4))
      (loop for entry-cons on table-entries
	    do
	(when (null (car entry-cons))
	  (when (>= (incf line-number) lines-per-page)
	    (format output "~&~|~&Module ")
	    (loop repeat (- 57 (length "Module ")) do (write-char #\. output))
	    (format output " Volume:Page~2%")
	    (setq line-number 3))
	  (let* ((module-entry (second entry-cons))
		 (header (first module-entry))
		 (page-entry (second module-entry))
		 (volume-number (car page-entry))
		 (page-number (cdr page-entry)))
	    (write-string header output)
	    (write-char #\space output)
	    (loop repeat (maxf 3 (- 60 (length header)))
		  do (write-char #\. output))
	    (format output " ~2d:~4d~%" volume-number page-number)))))
    (format output "~&~|~&")
    (loop with table-header = (make-boxed-lines "Table of Contents")
	  for line in table-header
	  do
      (write-line line output)
	  finally
	    (format output "~%Section ")
	    (loop repeat (- 57 (length "Section ")) do (write-char #\. output))
	    (format output " Volume:Page~2%")
	    (setq line-number (+ (length table-header) 4)))
    (loop for entry in table-entries
	  do
      (when (>= (incf line-number) lines-per-page)
	(format output "~&~|~&Section ")
	(loop repeat (- 57 (length "Section ")) do (write-char #\. output))
	(format output " Volume:Page~2%")
	(setq line-number 3))
      (if entry
	  (let* ((header (first entry))
		 (page-entry (second entry))
		 (volume-number (car page-entry))
		 (page-number (cdr page-entry)))
	    (write-string header output)
	    (write-char #\space output)
	    (loop repeat (maxf 3 (- 60 (length header)))
		  do
	      (write-char #\. output))
	    (format output " ~2d:~4d~%" volume-number page-number))
	  (terpri output)))))

(defun symbol-if-interesting (string)
  (if (> (length string) 5)
      (multiple-value-bind (symbol? type-of-inheritance)
	  (find-symbol string)
	(if (and (or symbol?
		     (multiple-value-setq (symbol? type-of-inheritance)
		       (find-symbol (string-upcase string))))
		 (eq type-of-inheritance ':internal)
		 (or (boundp symbol?) (fboundp symbol?)))
	    symbol?))))




	  

;;; Docf is a simplified version of document-file intended for interactive,
;;; on-line use and as a way of quickly previewing a file's documentation.  It
;;; prints out the documentation the way document-file would with the following
;;; exceptions:
;;; 
;;;    (1) Underlines are not placed beneath headers
;;;    (2) No index is printed
;;;    (3) Destination defaults to the value of *standard-output*, rather than
;;;        a file derived from the name of the input file.
;;;    (4) Docf supports the destination nil.  Supplying the destination nil
;;;        causes docf not to print any output but rather to return its output
;;;        as a string.

(defun docf (file &optional (destination t) &aux (string-output-stream? nil))
  (with-open-stream (to
		      (if (eq destination t)
			  *standard-output*
			  (if (eq destination nil)
			      (setq string-output-stream?
				    (make-string-output-stream))
			      (if (streamp destination)
				  destination
				  (open destination ':direction ':output)))))
    (with-open-file (file file)
      (loop for line? = (read-line file nil nil)
	    with last-line-was-one? = t
	    while line?
	    if (or (string= line? ";;; " ':end1 #.(length ";;; "))
		   (string= line? ";;;; " ':end1 #.(length ";;;; ")))
	      do (write-line line? to ':start #.(length ";;; "))
		 (setq last-line-was-one? t)
	    else (when last-line-was-one?
;		   (write-line "" to)
		   (write-line "" to)
		   (setq last-line-was-one? nil)))))
  (when string-output-stream?
    (get-output-stream-string string-output-stream?)))



;;; Extract-arglist-lines-from-stream extracts the lines starting with 
;;; first-line-as-string?, if it is non-nil, and continuing with more lines
;;; read from stream?, if it is non-nil, that make up the arglist (or simi-
;;; larly interesting information) of a function definition (or similarly 
;;; interesting defining form).  If it fails to capture this information
;;; for any reason, the single value returned is nil. ...

(defun extract-arglist-lines-from-stream (first-line-as-string? stream?)
  (declare (ignore first-line-as-string? stream?))
  nil)

;; Code this if people really want it!






;;;; Overviews of Modules

;; By Ben Hyde





;;; Compute-overview ...

;;; From time to time I generate the file ma:>ab>overview.lisp.
;;;    % # It is a little as if I did this:
;;;    % grep -e '^;;; ;' -e '^(def' *.lisp > overview.lisp

;;; In anycase it provides an overview of all the modules in G2, and
;;; I find it useful when
;;;  1. deciding were to place a new facility,
;;;  2. getting a feel for how things fit together, and
;;;  3. when I don't have symbol-search loaded.

(defun compute-overview (&optional (system-name 'ab))
  (let ((system (normalize-system-name system-name)))
    
      (with-open-file (overview-stream (make-system-pathname 'ab "overview" 'lisp ':newest)
				       :direction :output)
	(loop for module in (all-lisp-source-file-symbols system)
	      as module-pathname = (make-system-pathname 'ab module 'lisp ':newest)
	      do
	  (format overview-stream "~7%;;;;; MODULE: ~A" module)
	  (with-open-file (module module-pathname :direction :input)
	    (loop for line? = (read-line module nil nil)
		  while line?
		  when (< 4 (length line?))
		    do
		      (cond
			((and (eql #\( (char line? 0))
			      (eql #\d (char line? 1))
			      (eql #\e (char line? 2))
			      (eql #\f (char line? 3)))
			 (format overview-stream "~%~A" line?)
			 (loop with count = 0
			       for i from 0 below (length line?)
			       for c = (char line? i)
			       when (eql #\( c) do (incf count)
			       when (eql #\) c) do (decf count)
			       finally 
				 (when (plusp count)
				   (format overview-stream " ... ~A" (subseq ")))))))))))))))))))" 0 count)))))
			((and (eql #\; (char line? 0))
			      (eql #\; (char line? 1))
			      (eql #\; (char line? 2))
			      (eql #\; (char line? 3)))
			 (format overview-stream "~2%~A" line?)))))))))

;; Documentation was in the change log.  I moved it in here.  (MHD 10/23/92)

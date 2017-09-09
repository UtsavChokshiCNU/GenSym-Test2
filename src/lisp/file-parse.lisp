;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module FILE-PARSE

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved

;;; John Hodgkinson

;; split from PATHNAMES, 25 Jun 1991



;;;; Parsing Namestrings


;;; def-filename-parser
;;;   <file-system> <case-mode> <temporary-variables> <special-characters> 
;;;   &rest <links>

;;; The basic idea is to tokenize the filename string into a sequence of special
;;; characters and clusters of non-special characters called words.  Words are
;;; represented as strings, while the special characters are represented as symbols
;;; indexing into a table named filename-special-character-registry.  Such symbols
;;; are termed punctuation-registry symbols.  Note that different file systems have
;;; different ideas of which characters are special.  Special-characters is an
;;; unevaluated list of punctuation-registry symbols considered special by the
;;; particular file-system.

;;; Case-mode indicates the canonical character case used by file-system.  This
;;; is either a symbol (:all-uppercase or :case-sensitive) or a list.  If a
;;; list, it is of the form (:global-variable-for-character-case <variable>),
;;; where <variable> is one of :all-uppercase or :case-sensitive, and is
;;; consulted at runtime to provide the canonical character case.

;;; Temporary-variables is an unevaluated list of variables which can be used
;;; during processing.  Any conses in these variables will NOT be reclaimed
;;; automatically; explicit forms in individual parsing nodes must do the
;;; reclaiming.  These variables are initially bound to nil.  The following
;;; variables are implcitly included in the temporary lists: host, device,
;;; directory, name, type, version.  These six variables are included for
;;; convenience in assembling the pathname components when the parse is finished.
;;; Since these values will become part of the final pathname structure, they of
;;; course should not be reclaimed until that pathname structure itself is.

;;; Each link represents a parsing node of the form
;;;   (link <from-node> <to-node> <match-pattern> &rest <body>)

;;; From-node and to-node are integer tags representing parsing nodes.  From-node
;;; must always be an integer.  To-node is typically an integer as well.  As a
;;; special-purpose hack, to-node can also be (if <form> <integer1> <integer2>) to
;;; provide a rudimentary computed go-to.  This feature prevents code duplication
;;; in some cases.

;;; There are two special tags: finish and error.  Finish cleans up temporary
;;; structures (such as conses and text-strings) used in the parse and returns a
;;; valid pathname.  Recall, however, that the contents of any temporary-variables
;;; must be reclaimed manually.  Error performs the same cleanup, but always
;;; returns nil.

;;; Match-pattern is a pattern for comparison.  If it succeeds, body is executed
;;; and control transfers to to-node.  The forms in body are executed in a lexical
;;; environment in which utility macros are in effect and in which a number of
;;; currently visible tokens are bound.  Details on the semantics of matching, on
;;; the utility macros, and on the binding mechanism are given below.

;;; If the match fails, the next to-node with the same to-node tag is tried, and so
;;; on, until control passes to a different tag.  Once control reaches a given tag,
;;; it is an error to "fall off the end".  We announce this error in development
;;; and quietly return nil elsewhere.


;;; The following describes the behavior of the match patterns and the bindings
;;; they cause.

;;; If match-pattern is <anything> the match always succeeds, binds the identifier
;;; <anything> to the current token, executes body, advances the token pointer, and
;;; jumps to the to-node.

;;; If match-pattern is <word> and the current token is not a special character, the
;;; match succeeds, binds <word> to the current token, executes body, advances the
;;; token pointer, and jumps to the to-node

;;; If match-pattern is <go> the match always succeeds, executes body, DOES NOT
;;; advance the token pointer, and jumps to to-node.

;;; If match is a punctuation-registry symbol, the match succeeds if the current
;;; token is the same symbol.  the parser executes body, advances the token
;;; pointer, and jumps to the to-node.

;;; If match-pattern is a specific string, the match succeeds if the current token is
;;; a word which is string= to match-pattern.  the parser executes body, advances the
;;; token pointer, and jumps to the to-node.

;;; Match-pattern may also be a list of match-patterns from the above.  If this is
;;; the case, the entire sequence must have enough tokens to cover the sequence and
;;; must match in order.  The parser binds any <word> or <anything> identifiers to
;;; their corresponding tokens, executes the body, advances the token-pointer by
;;; the number of tokens matches, and jumps to the to-node.  Multiple occurrences
;;; of bindable tokens may be differentiated by numerals, e.g.  <word>1 or
;;; 2<anything>.  For an example of such multiple binding see the part of the VMS
;;; parser that extracts the host.

;;; The following describes the local macros which may be called within the body
;;; of a node.  Note that some reclaim their argument and some don't.  None of
;;; these local macros reclaim text strings, even if they are elements of lists
;;; that are reclaimed.

;;; coalesce-filename-tokens (words-and-punct)
;;; type of argument: any symbol, string, or list of strings and punctuation-registry symbols
;;; reclaims conses in argument? no
;;; resulting order: same as argument
;;; comment: Converts argument into a text-string which will become a pathname
;;; component or (as with directories) a subcomponent).  Called by all other
;;; coalesce-xxx macros.

;;; coalesce-filename-sublists (sublists)
;;; type of argument: list of arguments to coalesce
;;; reclaims conses in argument? yes
;;; resulting order: reverse of argument
;;; comment: Typically used for directories.

;;; coalesce-reversed-filename-list (reversed-list)
;;; type of argument: list of strings and punctuation-registry symbols
;;; reclaims conses in argument? yes
;;; resulting order: reverse of argument
;;; comment: Typically used for name or type.

;;; coalesce-filename-items (&rest items)
;;; type of each argument: string or punctuation-registry symbol
;;; reclaims arguments? no
;;; resulting order: same as arglist
;;; comment: Currently used only in vms host/account/password syntax.

;;; coalesce-remainder-of-filename-sequence ()
;;; type of each argument: no args
;;; reclaims arguments? no args
;;; resulting order: not applicable
;;; comment: Used to get our platform-independent wildcards in versions

;;; change-filename-sequence-to (new-sequence) 
;;; Stores the old sequence of tokens and its pointer, sets the token-sequence to a
;;; copy of new-sequence, and begins parsing the copy.  Does not set up a
;;; backtracking point, just stores enough to resume the old sequence from whatever
;;; node invokes resume-previous-filename-sequence.

;;; resume-previous-filename-sequence ()
;;; Reclaims conses in sequence being parsed, restores old sequence and pointer,
;;; and continues parsing with it.

;;; error-in-filename-parse (message)
;;; In development, signals a continuable error and prints message.  Elsewhere,
;;; causes the parser to return nil for this filename.

;;; place-mark-in-filename-sequence ()
;;; Stores the current sequence pointer.

;;; revert-to-last-mark-in-filename-sequence ()
;;; Changes the sequence pointer to its value at the last time (mark-sequence) was
;;; called.

;;; current-filename-sequence-element () 
;;; For internal use unless extraordinary cases arise.  Better to use the automatic
;;; binding provided (see above description of match patterns).

;;; advance-filename-sequence-pointer ()
;;; For internal use unless extraordinary cases arise.

;;; traverse-filename-parser-link 
;;;  (to-node jump-node-p node-table-name)
;;; For internal use unless extraordinary cases arise.  If jump-node-p is non-nil,
;;; the sequence-pointer is left alone, otherwise it is incremented.
;;; Node-table-name names the global variable containing compiled functions
;;; representing each parser node.  This is to support an optimization for node
;;; traversal which avoids using funcall-symbol.




;; Possible Namestring-parsing Pitfalls

;; Note that hp unix truncates filename+type to 14 characters.  This will affect
;; truename strings on HP systems.

;; Note that the logical name environment of VMS could affect the truename of
;; files.

;; Do explorers and microexplorers tolerate spaces in filenames?  If so, we might
;; need another mode :allows-whitespace in the def-filename-parser formalism
;; alongside the character-case modes.



;;; Filename-special-character-registry contains the union of all characters
;;; considered special by any file system.  The tokenizer for each file-system uses
;;; a subset of these characters.

(eval-when (:compile-toplevel :load-toplevel :execute)

(defvar filename-special-character-registry nil)

) ;end of eval-when for filename-special-character-registry



(defmacro def-filename-character-alias (alias character)
  `(progn
     (pushnew (cons ',alias ,character)
	      filename-special-character-registry
	      :test #'equalw)
     (defvar ,alias ',alias)))
  


(eval-when (:compile-toplevel :load-toplevel :execute)

(defvar <end-of-sequence> '<end-of-sequence>)

(def-filename-character-alias <colon>               #.%\:)
(def-filename-character-alias <slash>               #.%\/)
(def-filename-character-alias <dot>                 #.%\.)
(def-filename-character-alias <tilde>               #.%\~)
(def-filename-character-alias <asterisk>            #.%\*)
(def-filename-character-alias <left-bracket>        #.%\[)
(def-filename-character-alias <right-bracket>       #.%\])
(def-filename-character-alias <semicolon>           #.%\;)
(def-filename-character-alias <double-quote>        #.%\")
(def-filename-character-alias <space>               #.%Space)
(def-filename-character-alias <hyphen>              #.%\-)
(def-filename-character-alias <left-angle-bracket>  #.%\<)
(def-filename-character-alias <right-angle-bracket> #.%\>)
(def-filename-character-alias <sharp-sign>          #.%\#)
(def-filename-character-alias <exclamation>         #.%\!)
(def-filename-character-alias <comma>               #.%\,)
(def-filename-character-alias <backslash>           #.%\\)

) ;end of eval-when for def-filename-character-alias forms


;; Tokenize-filename takes as input a filename (which must be a string) and a list
;; of symbols representing special chacters to the file system.  It transforms the
;; filename into a path-list consisting of text-strings representing clusters of
;; non-special characters we will call "words" and symbols representing special
;; characters, in the order that they occur in the original.  Each word or special
;; character consitutes a single "token" for purposes of parsing the filename in
;; the given file system.

;; Need escape characters here, for coral #\Option-D, for unix #\\.  To my
;; knowledge, VMS has none.  This is not a high priority (12/18/90) because we
;; often treat filenames as case-insensitive anyway (as in read-kb in FILES).



;; Nreversef is a modify macro that takes a single argument, a location, and
;; reverses its contents in place.  Note that nreversef does what we sometimes
;; misguidedly want nreverse to do.

(define-modify-macro nreversef () nreverse)

(defun tokenize-filename 
       (filename special-characters 
	&optional (character-case-mode :case-sensitive))
  (let* ((text-string-copy (copy-text-string filename))
	 (private-filename
	   (case character-case-mode 
	     (:case-sensitive text-string-copy)
	     (:all-uppercase (nstring-upcasew text-string-copy))
	     (:all-lowercase (nstring-downcasew text-string-copy))
	     #+development
	     (otherwise (error "unknown character-case-mode ~a"
			       character-case-mode))))
	 (tokenized-filename nil)
	 (special-character-registry
	   (loop for entry in filename-special-character-registry
		 when (wide-character-member
			(car entry)
			special-characters)
		   collect entry using path-cons)))
    (loop for index from 0 below (lengthw private-filename)
	  with char = nil
	  with accumulated-chars = nil
	  do (setq char (charw private-filename index))
	     (let ((special-character-entry
		     (wide-character-rassoc char special-character-registry)))
	       (cond (special-character-entry
		      (when accumulated-chars
			(path-push 
			  (twith-output-to-text-string
			    (loop for accumulated-char 
				      in (nreversef accumulated-chars)
				  do
			      (twrite-char accumulated-char)))
			  tokenized-filename)
			(reclaim-path-list accumulated-chars)
			(setq accumulated-chars nil))
		      (path-push (car special-character-entry)
				 tokenized-filename))
		     (t (path-push char accumulated-chars))))
	  finally
	    (when accumulated-chars
	      (path-push 
		(twith-output-to-text-string
		  (loop for accumulated-char 
			    in (nreversef accumulated-chars)
			do
		    (twrite-char accumulated-char)))
		tokenized-filename)
	      (reclaim-path-list accumulated-chars))
	    (reclaim-path-list special-character-registry)
	    (reclaim-text-string private-filename)
	    (return (nreverse
		      (path-cons '<end-of-sequence> 
				 tokenized-filename))))))

;; jh, 12/10/92.  Fixed a longstanding bug in tokenize-filename where it
;; destructively upcased its string input under certain circumstances.

(eval-when (:compile-toplevel :load-toplevel :execute)

(defvar trace-filename-parsing-p nil)

) ;end of eval-when for trace-filename-parsing-p





(def-structure (filename-parser-information
		 (:constructor make-filename-parser-information ())
		 (:reclaimer reclaim-filename-parser-information-internal))
  (tokenized-filename nil)
  (filename-sequence nil)
  (filename-sequence-length nil)
  (previous-filename-sequences-stack nil)
  (filename-parser-error-message nil)
  (filename-parser-error-function nil)
  (filename-sequence-pointer nil)
  (saved-filename-sequence-pointer nil)
  (next-filename-node nil)
  )




(eval-when (:compile-toplevel :load-toplevel :execute)

(defvar-for-macro filename-parser-info-symbol '#:parser-info)
(defvar-for-macro filename-parser-traverse-label '#:parser-traverse)
(defvar-for-macro current-filename-sequence-token '#:current-token)
(defvar-for-macro filename-parser-next-node-symbol '#:next-node)
(defvar-for-macro filename-parser-node-names nil)

)

;; The two variables above were causing problems in the Chestnut translator.
;; Through inspection of the code below and inspection of the translated C code,
;; it would appear that the two variables, filename-parser-info-symbol, and
;; filename-parser-traverse-label, are only referenced at macro expand time.  So,
;; an attempt has been made to fix this by defining them as defvar-for-macros.
;; Please review these changes, John!!!  -jra 2/1/91

;; Reviewed.  This fix will work fine.  The uninterned symbols seemed necessary
;; because the filename parsing macro lets the programmer using this facility
;; choose local variable names, and names like parser-info and parser-traverse are
;; not unlikely.  jh, 2/1/91.

;; Note there is a third variable now, current-filename-sequence-token.  The same
;; reassurance holds for it.  jh, 2/21/91.



(defun reclaim-filename-parser-information
       (parser-info)
  ;; reclaim the current filename sequence
  (reclaim-path-list (filename-sequence parser-info))

  ;; reclaim the entries in the stack describing previous sequences (note that
  ;; they contain substructure which must be reclaimed)
  (let ((previous-stack (previous-filename-sequences-stack parser-info)))
    (loop for entry in previous-stack
	  do
	  (reclaim-path-list (third entry)) ;previous sequence
	  (reclaim-path-list entry)         ;other info (pointer & length)
	  finally
	  (reclaim-path-list previous-stack)))

  ;; reclaim the original tokenized sequence (from which all filename sequences,
  ;; current and previous, were derived)
  (loop for token in (tokenized-filename parser-info)
	when (text-string-p token)
	  do (reclaim-text-string token)
	finally
	(reclaim-path-list (tokenized-filename parser-info)))

  ;; reclaim the parser information structure itself
  (reclaim-filename-parser-information-internal parser-info))



(defmacro coalesce-filename-tokens (words-and-punct)
  `(coalesce-filename-tokens-1 ,words-and-punct))

(defun coalesce-filename-tokens-1 (words-and-punct)
  (if (symbolp words-and-punct)
      (let ((entry (assoc words-and-punct
			  filename-special-character-registry)))
	(if entry
	    (twith-output-to-text-string
	      (twrite-char (cdr entry)))
	    words-and-punct))
      (twith-output-to-text-string
	(loop for section in words-and-punct
	      do
	      (cond ((or (text-string-p section)
			 (gensym-string-p section))
		     (twrite-string section))
		    ((eq '<end-of-sequence> section))
		    (t (let ((entry 
			       (assoc section 
				      filename-special-character-registry)))
			 (if entry
			     (twrite-char (cdr entry))
			     #+development
			     (cerror "skip"
				     "discrepancy in special character ~a"
				     section)))))))))



(defmacro coalesce-filename-sublists (sublists)
  `(coalesce-filename-sublists-1 ,sublists))

(defun coalesce-filename-sublists-1 (sublists)
  (when sublists
    (let ((sublists-in-order (nreverse sublists)))
      (loop for sublist-item in sublists-in-order
	    collect (coalesce-filename-tokens sublist-item)
	      using path-cons
	    when (consp sublist-item)
	      do (reclaim-path-list sublist-item)
	    finally
	    (reclaim-path-list sublists-in-order)))))



(defmacro coalesce-reversed-filename-list (reversed-list)
  `(coalesce-reversed-filename-list-1 ,reversed-list))

(defun coalesce-reversed-filename-list-1 (reversed-list)
  (let ((list-in-order (nreverse reversed-list)))
    (prog1 (coalesce-filename-tokens list-in-order)
	   (reclaim-path-list list-in-order))))



(defmacro coalesce-filename-items (&rest items)
  `(coalesce-filename-items-1 (path-list ,@items)))

(defun coalesce-filename-items-1 (item-list)
  (prog1 (coalesce-filename-tokens item-list)
	 (reclaim-path-list item-list)))

(defmacro coalesce-remainder-of-filename-sequence ()
  `(coalesce-remainder-of-filename-sequence-1 ,filename-parser-info-symbol))

(defun coalesce-remainder-of-filename-sequence-1 (parser-info)
  (coalesce-filename-tokens 
    (nthcdr 
      (filename-sequence-pointer parser-info)
      (filename-sequence parser-info))))

(defmacro change-filename-sequence-to (new-sequence &optional (increment 1))
  `(change-filename-sequence-to-1
     ,new-sequence
     ,filename-parser-info-symbol
     ,increment))

(defun-void change-filename-sequence-to-1 (new-sequence parser-info increment)
  (let ((end-of-sequence-list
	  (path-list '<end-of-sequence>)))
    (path-push (path-list (+f (filename-sequence-pointer parser-info)
			      increment)
			  (filename-sequence-length parser-info)
			  (filename-sequence parser-info))
	       (previous-filename-sequences-stack parser-info))
    (setf (filename-sequence-pointer parser-info) (-f increment))
    (setf (filename-sequence-length parser-info)
	  (1+ (length new-sequence)))
    (cond (new-sequence
	   (let ((copy-of-new-sequence
		   (copy-list-using-path-conses new-sequence)))
	     (setf (cdr (last copy-of-new-sequence))
		   end-of-sequence-list)
	     (setf (filename-sequence parser-info) 
		   copy-of-new-sequence)))
	  (t (setf (filename-sequence parser-info)
		   end-of-sequence-list)))))



(defmacro resume-previous-filename-sequence ()
  `(resume-previous-filename-sequence-1 ,filename-parser-info-symbol))

(defun resume-previous-filename-sequence-1 (parser-info)
  (let ((previous-info 
	  (path-pop 
	    (previous-filename-sequences-stack parser-info))))
    (reclaim-path-list (filename-sequence parser-info))
    (setf (filename-sequence-pointer parser-info)
	  (first previous-info))
    (setf (filename-sequence-length parser-info)
	  (second previous-info))
    (setf (filename-sequence parser-info)
	  (third previous-info))
    (reclaim-path-list previous-info)))


(defmacro current-filename-sequence-element ()
  current-filename-sequence-token)




(defmacro advance-filename-sequence-pointer ()
  `(incff (filename-sequence-pointer ,filename-parser-info-symbol)))



(defmacro traverse-filename-parser-link (to jump-node-p node-table-name)
  (flet ((expand-node-traversal (node-name)
	   (let ((node-index?
		   (position node-name filename-parser-node-names)))
	     (unless node-index?
	       (error "TRAVERSE-FILENAME-PARSER-LINK: unknown node name ~a"
		      node-name))
	     `(#+development
	       (setf (next-filename-node ,filename-parser-info-symbol)
		     ',node-name)
	       (setq ,filename-parser-next-node-symbol
		    (svref ,node-table-name ,node-index?))))))
    `(progn
       ,@(if (not jump-node-p)
	     `((advance-filename-sequence-pointer)))
       ,@(if (consp to)
	     (gensym-dstruct-bind 
	         ((nil testform then-node else-node) to)
	       (unless (eq (car to) 'if)
		 (error "unknown conditional traversal form ~a" to))
	       `((cond  (,testform 
			 ,@(expand-node-traversal then-node))
			(t ,@(expand-node-traversal else-node)))))
	     (expand-node-traversal to))
       (go ,filename-parser-traverse-label))))



(defmacro catcher-for-filename-parse-error ()
  `'catcher-for-filename-parse-error)

(defmacro error-in-filename-parse (string)
  `(error-in-filename-parse-1 ,string ,filename-parser-info-symbol))

(defun error-in-filename-parse-1 (string parser-info)
  #-development
  (declare (ignore string))
  #+development
  (setf (filename-parser-error-message parser-info) string)
  (funcall-simple-compiled-function
    (filename-parser-error-function parser-info) parser-info))






(defun-for-macro multiple-match-in-def-filename-parser
		 (next-node
		   node-table-name
		   match
		   body
		   internal-match-vars
		   setqs-for-new-internal-match-vars
		   error-node-p)
  (let* ((length-of-match (length match))
	 (external-match-bindings
	   (and (not error-node-p)
		(loop for match-var in internal-match-vars
		      for match-patt in match
		      when 
		      (and (symbolp match-patt)
			   (or (memq match-patt '(<word> <anything>))
			       (let ((match-patt-name
				       (symbol-name match-patt)))
				 (or (search "<WORD>" match-patt-name)
				     (search "<ANYTHING>" match-patt-name)))))
			collect
			`(,match-patt ,match-var)))))
    `(,@(if setqs-for-new-internal-match-vars
	    `((and ,@setqs-for-new-internal-match-vars))
	    nil)
      (when ,(elt internal-match-vars (1- length-of-match))
	(when (and ,@(loop for match-var in internal-match-vars
			   for match-patt in match
			   when (not (eq '<anything> match-patt))
			     collect
			     (cond ((or (gensym-string-p match-patt)
					(text-string-p match-patt))
				    `(string=w ',(stringw match-patt) ,match-var))
				   ((or (eq '<word> match-patt)
					(search "<WORD>" 
						(symbol-name match-patt)))
				    `(text-string-p ,match-var))
				   (t `(eq ,match-var ,match-patt)))))
	  ,@(if external-match-bindings ;error-node-p is never true
		`((let ,external-match-bindings
		    ,@body
		    (incff (filename-sequence-pointer 
			    ,filename-parser-info-symbol)
			  ,length-of-match)
		    (traverse-filename-parser-link 
		      ,next-node 
		      t 
		      ,node-table-name)))
		`(,@body
		  ,@(if error-node-p
			nil
			`((incff (filename-sequence-pointer 
				   ,filename-parser-info-symbol)
				 ,length-of-match)
			  (traverse-filename-parser-link 
			    ,next-node 
			    t 
			    ,node-table-name))))))))))




(defun-for-macro single-match-in-def-filename-parser
		 (next-node
		   node-table-name
		   match
		   body)
  (case match
    (<word>
     `((let ((<word> (current-filename-sequence-element)))
	 (when (text-string-p <word>)
	   ,@body
	   (traverse-filename-parser-link ,next-node nil ,node-table-name)))))
    (<anything>
     `((let ((<anything> (current-filename-sequence-element)))
	 (when (not (eq '<end-of-sequence> <anything>))
	   ,@body
	   (traverse-filename-parser-link ,next-node nil ,node-table-name)))))
    (<go>
     `(,@body
       (traverse-filename-parser-link ,next-node t ,node-table-name)))
    (otherwise ;punctuation-registry symbol
     `((when (eq (current-filename-sequence-element) ,match)
	 ,@body
	 (traverse-filename-parser-link ,next-node nil ,node-table-name))))))




#+development
(defun trace-filename-parsing (parser-info last-node)
  (format t "~&going from ~a to ~a: " 
	  last-node
	  (next-filename-node parser-info))
  (loop for index from 0
		  below (filename-sequence-length parser-info)
	for elt in (filename-sequence parser-info)
	do
	(when (=f (filename-sequence-pointer parser-info)
		  index)
	  (format t "*"))
	(format t "~s " elt)
	finally
	(format t "~%")))





(defun-for-macro link-body-for-def-filename-parser
		 (last-node 
		   current-defun-body 
		   temporaries 
		   parser-error-name)
     `(tagbody
	  ,@current-defun-body
	  #+development
	  (setf (filename-parser-error-message 
		  ,filename-parser-info-symbol)
		(format nil
			"fell off end in ~a" ',last-node))
	  (,parser-error-name ,filename-parser-info-symbol)
	  ,filename-parser-traverse-label
	  #+development
	  (when trace-filename-parsing-p
	    (trace-filename-parsing ,filename-parser-info-symbol ',last-node))
	  (return-from ,last-node
	    (funcall-simple-compiled-function
	      ,filename-parser-next-node-symbol
	      ,filename-parser-info-symbol
	      host device directory name type version
	      ,@temporaries))))





(defun-for-macro link-for-def-filename-parser
		 (last-node 
		   current-defun-body 
		   temporaries 
		   parser-error-name
		   internal-match-vars
		   filename-sequence-var
		   match-pointer-var
		   sequence-length-var)
  (if internal-match-vars
      `(defun-simple ,last-node 
	      (,filename-parser-info-symbol
	       host device directory name type version
	       ,@temporaries)
	 (let* ((,filename-parser-next-node-symbol nil)
		(,filename-sequence-var
		   (filename-sequence ,filename-parser-info-symbol))
		(,sequence-length-var
		   (filename-sequence-length ,filename-parser-info-symbol))
		(,match-pointer-var
		   (filename-sequence-pointer ,filename-parser-info-symbol))
		(,current-filename-sequence-token
		   (nth ,match-pointer-var
			,filename-sequence-var))
		(,(car internal-match-vars)
		    ,current-filename-sequence-token)
		,@(loop for match-var in (cdr internal-match-vars)
			collect
			`(,match-var nil)))
	   ,(link-body-for-def-filename-parser
	      last-node 
	      current-defun-body 
	      temporaries 
	      parser-error-name)))
      `(defun-simple ,last-node 
	      (,filename-parser-info-symbol
	       host device directory name type version
	       ,@temporaries)
	 ,(let ((link-body
		  (link-body-for-def-filename-parser
		    last-node 
		    current-defun-body 
		    temporaries 
		    parser-error-name)))
	    (labels ((current-filename-token-referenced-p (body)
		       (cond ((not (consp body)) nil)
			     ((equal body 
				     '(current-filename-sequence-element))
			      (throw
				'filename-token-referenced-p 
				t))
			     (t (current-filename-token-referenced-p
				  (car body))
				(current-filename-token-referenced-p
				  (cdr body))))))
	      `(let ((,filename-parser-next-node-symbol nil)
		     ,@(if (catch 'filename-token-referenced-p
			     (current-filename-token-referenced-p link-body))
			   `((,current-filename-sequence-token
			        (nth (filename-sequence-pointer 
				       ,filename-parser-info-symbol)
				     (filename-sequence 
				       ,filename-parser-info-symbol))))))
		 ,link-body))))))




(defun-for-macro links-for-def-filename-parser
		 (links
		   temporaries
		   parser-error-name
		   node-table-name)
  (loop for (nil this-node next-node match . body)
	    in links
	with last-node = nil
	with current-defun-body = nil
	with all-node-defuns = nil
	with internal-match-vars = nil
	with filename-sequence-var = '#:filename-sequence
	with match-pointer-var = '#:match-pointer
	with sequence-length-var = '#:sequence-length

	for defun-starts-p = nil
	    then (not (eql this-node last-node))
	for error-node-p = (eq parser-error-name next-node)

	do
	(when defun-starts-p
	  (push (link-for-def-filename-parser
		  last-node
		   current-defun-body 
		   temporaries 
		   parser-error-name
		   internal-match-vars
		   filename-sequence-var
		   match-pointer-var
		   sequence-length-var)
		all-node-defuns)
	  (push last-node
		filename-parser-node-names)
	  (setq internal-match-vars nil)
	  (setq current-defun-body nil))

	(when error-node-p
	  (setq body
		`(#+development
		  (setf (filename-parser-error-message 
			  ,filename-parser-info-symbol)
			,(if (cdr body)
			     `(progn ,@body)
			     (car body)))
		  (,parser-error-name ,filename-parser-info-symbol))))

	(setq 
	  current-defun-body
	  (append
	    current-defun-body
	    (cond ((consp match)
		   ;; If we need additional match variables for multiple-token
		   ;; match, add them to internal-match-vars here.  That way we
		   ;; only have to bind them once, in the defun for the entire
		   ;; node.  jh, 11/19/90.
		   (let* ((old-match-length
			    (length internal-match-vars))
			  (match-length
			    (length match))
			  (new-internal-match-vars
			    (loop for index from old-match-length
					    below match-length
				  collect
				  (read-from-string
				    (format nil "#:MATCH-~a" index))))
			  (setqs-for-new-internal-match-vars
			    (loop for index from old-match-length
					    below match-length
				  for new-var in new-internal-match-vars
				  when (/= index 0)
				    collect
				    `(<f (incff ,match-pointer-var)
					 ,sequence-length-var)
				  when (/= index 0)
				    collect
				    `(setq ,new-var
					   (nth ,match-pointer-var
						,filename-sequence-var)))))
		     
		     (setq internal-match-vars
			   (nconc internal-match-vars
				  new-internal-match-vars))
		     (multiple-match-in-def-filename-parser 
		       next-node
		       node-table-name
		       match
		       body
		       internal-match-vars
		       setqs-for-new-internal-match-vars
		       error-node-p)))
		  ((or (text-string-p match)
		       (gensym-string-p match))
		   `((when (string=w ,(stringw match)
				     (current-filename-sequence-element))
		       ,@body
		       (traverse-filename-parser-link 
			 ,next-node
			 nil
			 ,node-table-name))))
		  (t (single-match-in-def-filename-parser
		       next-node
		       node-table-name
		       match
		       body)))))
	(setq last-node this-node)

	finally
	(push (link-for-def-filename-parser
		last-node
		current-defun-body
		temporaries
		parser-error-name
		internal-match-vars
		filename-sequence-var
		match-pointer-var
		sequence-length-var)
	      all-node-defuns)
	(push last-node
	      filename-parser-node-names)
	(return 
	  (nreverse
	    all-node-defuns))))




(def-global-property-name filename-parser-of-file-system)
(def-global-property-name namestring-generator-of-file-system)

(defvar-for-development all-known-file-systems nil)

(defmacro def-filename-parser
	  (file-system character-case-mode 
	   temporaries special-characters &rest unsorted-links)
  (unless (or (memq character-case-mode '(:case-sensitive :all-uppercase))
	      (and (consp character-case-mode)
		   (eq (first character-case-mode)
		       :global-variable-for-character-case)
		   (second character-case-mode)))
    (error "DEF-FILENAME-PARSER: unknown character case mode ~a"
	   character-case-mode))
  (let ((links 
	  (stable-sort (copy-tree unsorted-links) #'< :key #'second))
	(parser-name
	  (intern (format nil "PARSE-~a-FILENAME" file-system)))
	(parser-error-name
	  (intern (format nil "ERROR-IN-~a-FILENAME-PARSER" file-system)))
	(final-node-name
	  (intern (format nil "FINAL-~a-PARSER-NODE" file-system)))
	(node-table-name
	  (intern (format nil "NODES-FOR-~a-FILENAME-PARSER" file-system))))

    (setq filename-parser-node-names 
	  (list parser-error-name final-node-name))

    (loop for link in links
	  for (nil from-node to-node) in links
	  do
	  (setf (second link)
		(intern (format nil 
				"~a-NODE-~a" parser-name from-node)))
	  (if (consp to-node)
	      (gensym-dstruct-bind 
		  ((if-tag nil then-node else-node) to-node)
		(unless (eq if-tag 'if)
		  (error "Unknown conditional traversal form ~a" to-node))
		(setf (third to-node)
		      (intern (format nil 
				      "~a-NODE-~a" parser-name then-node)))
		(setf (fourth to-node)
		      (intern (format nil 
				      "~a-NODE-~a" parser-name else-node))))
	      (case to-node
		(error (setf (third link) parser-error-name))
		(finish (setf (third link) final-node-name))
		(otherwise 
		 (setf (third link)
		       (intern (format nil 
				       "~a-NODE-~a" parser-name to-node)))))))
    `(progn

       ,@(if (eval-feature :development)
	     `((pushnew ',file-system all-known-file-systems))
	     nil)

       (eval-when (:compile-toplevel :load-toplevel :execute)
	 ,(let ((convert-p
		  (if (eq character-case-mode :all-uppercase)
		      't
		      'nil)))
	    `(setf (convert-file-strings-to-uppercase-p ',parser-name)
		   ,convert-p
		   (convert-file-strings-to-uppercase-p ',file-system)
		   ,convert-p)))

       (setf (filename-parser-of-file-system  ',file-system) ',parser-name)

       (defvar ,node-table-name nil)

       (defun-simple ,parser-error-name
	      (,filename-parser-info-symbol)
	 #+development
	 (when report-filename-parsing-errors-in-development-p
	   (cerror "give up and return nil"
		   "~&file-parsing error: ~a~%" 
		   (filename-parser-error-message 
		     ,filename-parser-info-symbol))) ;no args yet
	 (reclaim-filename-parser-information ,filename-parser-info-symbol)
	 (throw (catcher-for-filename-parse-error) nil))

       (defun-simple ,final-node-name
	      (,filename-parser-info-symbol
	       host device directory name type version
	       ,@temporaries)
	 (declare (ignore ,@temporaries))
	 (prog1
	   (if (filename-parser-error-message ,filename-parser-info-symbol)
	       nil
	       (let ((result-pathname
		       (make-gensym-pathname-structure-function
			 host device directory name type version)))
		 (setf (gensym-pathname-file-system result-pathname)
		       ',file-system)
		 (setf (gensym-pathname-filename-parser result-pathname)
		       (filename-parser-of-file-system ',file-system))
		 (setf (gensym-pathname-namestring-generator result-pathname)
		       (namestring-generator-of-file-system ',file-system))
		 result-pathname))
	   (reclaim-filename-parser-information
	     ,filename-parser-info-symbol)))

       ,@(let* ((defuns-for-links
		  (links-for-def-filename-parser
		    links
		    temporaries
		    parser-error-name
		    node-table-name))
		(start-node-name
		  (second (first defuns-for-links))))
	   `(,@defuns-for-links
	     
	     ;; actual parsing function
	     (defun-allowing-unwind ,parser-name
				    (filename)
	       (catch (catcher-for-filename-parse-error)
		 (let ((,filename-parser-info-symbol 
		        (make-filename-parser-information)))
		   (setf (tokenized-filename ,filename-parser-info-symbol)
			 (tokenize-filename 
			   filename 
			   '(,@special-characters)
			   ,(if (consp character-case-mode)
				(second character-case-mode)
				`',character-case-mode)))
		   (setf (filename-sequence ,filename-parser-info-symbol)
			 (copy-list-using-path-conses
			   (tokenized-filename ,filename-parser-info-symbol)))
		   (setf (filename-sequence-length 
			   ,filename-parser-info-symbol)
			 (length 
			   (tokenized-filename 
			     ,filename-parser-info-symbol)))
		   (setf (previous-filename-sequences-stack 
			   ,filename-parser-info-symbol) 
			 nil)
		   (setf (filename-parser-error-message
			   ,filename-parser-info-symbol) 
			 nil)
		   (setf (filename-sequence-pointer
			   ,filename-parser-info-symbol) 
			 0)
		   (setf (saved-filename-sequence-pointer
			   ,filename-parser-info-symbol) 
			 nil)
		   (setf (filename-parser-error-function
			   ,filename-parser-info-symbol)
			 (svref ,node-table-name
				,(or (position parser-error-name
					       filename-parser-node-names)
				     (error "DEF-FILENAME-PARSER: ~
                                           unknown error node ~a"
					    parser-error-name))))
		   (,start-node-name
		    ,filename-parser-info-symbol
		    ;; host device directory name type version
		    nil  nil    nil       nil  nil  nil 
		    ,@(loop for nil in temporaries collect nil)))))
	     ))

       (setq ,node-table-name
	     (make-array ,(length filename-parser-node-names)
	       :element-type 
	       t
	       :initial-contents 
	       (list ,@(loop for node-name 
				 in filename-parser-node-names
			     collect
			     `#',node-name))))

       ',parser-name
       )))

;; Streamlined def-filename-parser code to bind match variables only when needed,
;; to cache the current sequence element, to funcall compiled functions rather
;; than symbols when traversing nodes, to store the node-traversal function in a
;; local variable rather than a slot in the parser-info structure, and to call
;; common parse operations as functions.
;;
;; Binding match variables as needed involved setting local variables only at
;; those places where they will help verify the match.  For example, the two links
;;   (link 100 101 (<dot> "-1"))                    ;link 1
;;   (link 100 101 (<double-quote> <word> <colon>)) ;link 2
;; will bind the first two match variables, try link 1, and only bind the third
;; match variable if link 1 fails.
;;
;; Caching the current sequence element obviously enhances speed, as does
;; funcalling compiled functions instead of symbols and storing the node-traversal
;; function in a local variable (each avoids a layer of indirection).  Funcalling
;; common parse operations makes the generated code more compact.  jh, 2/21/91.




;; jh, 3/8/91.  Changed UNIX filename parser to parse "~" as a gensym-pathname
;; empty except for a :previous version.  This is to help the G2 user's file
;; interface, which separates pathname components more.  jh, 3/8/91.

;; jh, 10/4/91.  Changed UNIX filename parser to reject filenames of the form
;; host:name, since the notion of relative directories across machines is
;; ill-defined in UNIX.  This notion is defined in VMS, so we should do something
;; there, though we currently don't.

;; jh, 10/6/91.  Changed UNIX filename parser to accept a single space following
;; the colon delimiter for the host component.  This is a hack to allow proper
;; conversion of Lisp machine pathnames for some UNIX platforms.

;; jh, 12/10/91.  Changed UNIX filename parser to prepend :relative onto any
;; non-empty directory which isn't headed by either :absolute, :home, or :relative
;; itself.  This will allow better merging during KB load, among other things.

;; jh, 1/10/92.  Need accept-any-version-component-p to allow wildcards more
;; complicated than "*" inside version components.  This becomes an issue now that
;; we have a platform-independent regular-expression matcher.  Users need to be
;; able to match version component specified by our metacharacters, some of which
;; aren't permissible in a straight parse of the version.  This is not a problem
;; for name and type components, because the regular expression metacharacters
;; happen to be allowed there.  The rationale for making this a global switch
;; instead of simply decreeing that all parsers should accept our local
;; metacharacters is that the file-parser are designed to reflect the underlying
;; file system as much as possible.  The ultimate solution is to include a switch
;; which lets us decide whether or not all components of a namestring being parsed
;; will accept our metacharacters.  This should be done inside the tokenizer, not
;; inside each individual filename parser.

(def-system-variable accept-any-version-component-p FILE-PARSE nil)

(def-filename-parser unix :case-sensitive
  (directory-item directory-list name-type-version-list name-list type-list)
  (<dot> <tilde> <slash> <colon> <asterisk>)

  ;; unix devices are never specified
  (link 100 101
	<go>
	(setq device :unspecific))

  ;; get host name if any
  (link 101 102
	(<word> <colon> <slash>)
	(setq host (copy-text-string <word>))
	(path-push :absolute directory-list))
  (link 101 102 ;hack for Lispms (see note above)
	(<word> <colon> " " <slash>)
	(setq host (copy-text-string <word>))
	(path-push :absolute directory-list))
  (link 101 102
	<slash> 
	(path-push :absolute directory-list))
  (link 101 102
	<go>)

  ;; scan directory names
  (link 102 103
	<slash>
	(setq directory-item
	      (nreverse directory-item))
	(change-filename-sequence-to directory-item))
  ;; current directory-item is actually a name/type/version
  (link 102 105
	<end-of-sequence>
	(setq directory
	      (coalesce-filename-sublists directory-list))
	(when directory
	  (unless (memq (car directory) '(:relative :absolute :home :up))
	    (path-push :relative directory)))
	(setq name-type-version-list
	      (nreverse directory-item))
	(change-filename-sequence-to name-type-version-list))
  (link 102 102
	<anything>
	(path-push <anything> directory-item))

  ;; decode special character sequences in a directory item
  (link 103 104
	<end-of-sequence>)
  (link 103 104
	(<tilde> <end-of-sequence>)
	(path-push :home directory-list))
  (link 103 104
	(<dot> <end-of-sequence>)
	(path-push :relative directory-list))
  (link 103 104
	(<dot> <dot> <end-of-sequence>)
	(path-push :up directory-list))
  (link 103 104
	(<asterisk> <end-of-sequence>)
	(path-push :wild directory-list))
  (link 103 104
	<go>
	(path-push (copy-list-using-path-conses
		     directory-item)
		   directory-list))
  (link 104 102
	<go>
	(reclaim-path-list directory-item)
	(setq directory-item nil)
	(resume-previous-filename-sequence))


  ;; special cases for name, type, and version
  (link 105 111
	<end-of-sequence>)
  (link 105 111
	(<dot> <end-of-sequence>)
	(let ((new-directory-component (path-list :relative)))
	  (if directory
	      (setf (cdr (last directory)) new-directory-component)
	      (setq directory new-directory-component))))
  (link 105 111
	(<dot> <dot> <end-of-sequence>)
	(let ((new-directory-component (path-list :up)))
	  (if directory
	      (setf (cdr (last directory)) new-directory-component)
	      (setq directory new-directory-component))))
  (link 105 111
	(<asterisk> <end-of-sequence>)
	(setq name :wild))
  (link 105 111
	(<tilde> <end-of-sequence>)
	(setq version :previous))

  (link 105 108
	(<asterisk> <dot>)
	(setq name :wild))
  (link 105 106
	<go>)

  ;; scan name, type, and version
  (link 106 111
	(<tilde> <end-of-sequence>)
	(setq name (coalesce-reversed-filename-list name-list))
	(setq version :previous))
  (link 106 111
	<end-of-sequence>
	(setq name (coalesce-reversed-filename-list name-list)))
  (link 106 108
	<dot>
	(setq name (coalesce-reversed-filename-list name-list)))
  (link 106 106
	<anything>
	(path-push <anything> name-list))

  ;; have name, scan for type and version
  (link 108 109
	<go>)

  (link 109 111
	(<asterisk> <end-of-sequence>)
	(setq type :wild))
  (link 109 110
	<go>)

  (link 110 111
	(<tilde> <end-of-sequence>)
	(setq type (coalesce-reversed-filename-list type-list))
	(setq version :previous))
  ;; jh, 10/2/92.  The following link now handles the UNIX practice of prefacing
  ;; secret files with a dot, the same character used to delimit file types.
  (link 110 111
	<end-of-sequence>
	(if name
	    (setq type (coalesce-reversed-filename-list type-list))
	    (setq name (coalesce-reversed-filename-list
			 (nconc type-list (path-list "."))))))
  ;; jh, 10/1/92.  The following link handles multiple dots -- we assume that
  ;; the final dot delimits the file type.
  (link 110 110
	<dot>
	(setq type-list (nconc type-list 
			       (if name
				   (path-list "." name)
				   (path-list "."))))
	(setq type (coalesce-reversed-filename-list type-list))
	(setq type-list nil)
	(when name (reclaim-text-string name))
	(setq name type))
  (link 110 110
	<anything>
	(path-push <anything> type-list))

  (link 111 finish
	<go>
	(reclaim-path-list name-type-version-list)))



;; jh, 12/10/91.  Note that the VMS filename parser does not expand logical names,
;; but always parses them into the device component of a gensym-pathname.

(defvar vms-directory-filenames-can-dangle-p nil)

(defun-void reclaim-nascent-vms-directory (directory-list directory-item?)
  (loop for component in directory-list
	when (consp component)
	  do (reclaim-path-list component)
	finally
	  (reclaim-path-list directory-list)
	  (reclaim-path-list directory-item?)))	  

(def-filename-parser vms :all-uppercase
  (directory-list directory-item? final-directory-item-p name-list type-list
   dual-directory-impossible-p doing-dual-directory-p)
  (<colon> <dot> <asterisk> <left-bracket> <right-bracket> 
   <semicolon> <double-quote> <space> <hyphen>)

  ;; get host
  (link 101 102
	(<word> <colon> <colon>)
	(setq host (copy-text-string <word>)))

  (link 101 102
	(<word>0
	   <double-quote> 
             <word>1 ;account without password
           <double-quote> 
	 <colon> <colon>)
	(setq host 
	      (coalesce-filename-items <word>0
				       <double-quote>
				       <word>1
				       <double-quote>)))
  (link 101 102
	(<word>0
	   <double-quote> 
             <word>1 <space> <word>2 ;account with password
           <double-quote>
	 <colon> <colon>)
	(setq host
	      (coalesce-filename-items <word>0
				       <double-quote>
				       <word>1
				       <space>
				       <word>2
				       <double-quote>)))
  (link 101 102
	<go>)

  ;; get device or logical name
  (link 102 103
	(<word> <colon>)
	(setq device (copy-text-string <word>)))
  (link 102 103
	<go>)

  ;; directory spec special cases
  (link 103 108
	(<left-bracket> <dot> <dot> <dot> <right-bracket>)
	(setq dual-directory-impossible-p t)
	(setq directory 
	      (path-list :relative :wild-inferiors)))
  (link 103 108
	(<left-bracket> <right-bracket>)
	(setq dual-directory-impossible-p t)
	(setq directory 
	      (path-list :relative)))
  (link 103 108
        (<left-bracket> "000000" <right-bracket>)
	(setq dual-directory-impossible-p t)
	(setq directory 
	      (path-list :absolute)))
  (link 103 108
        (<left-bracket> "000000" <dot> <dot> <dot> <right-bracket>)
	(setq dual-directory-impossible-p t)
	(setq directory 
	      (path-list :absolute :wild-inferiors)))

  ;; special cases for first directory item
  (link 103 104
        (<left-bracket> "000000" <dot>)
	(path-push :absolute directory-list))
  (link 103 104
	(<left-bracket> <hyphen> <dot>)
	(path-push :relative directory-list)
	(setq dual-directory-impossible-p t)
	(path-push :up directory-list))
  (link 103 finish 
	(<left-bracket> <dot> <right-bracket>)
	(error-in-filename-parse "empty relative VMS pathname"))
  (link 103 104
	(<left-bracket> <dot>)
	(path-push :relative directory-list))
  (link 103 finish ; zero directory components
	(<left-bracket> <end-of-sequence>)
	(cond
	  (vms-directory-filenames-can-dangle-p
	   (setq directory (path-list :relative)))
	  (t (reclaim-pathname-components host device)
	     (error-in-filename-parse
	       "VMS directory not supplied after \["))))
  (link 103 104
	<left-bracket>
	(path-push :absolute directory-list))	
  (link 103 108 ;no directory spec at all
	<go>)

  ;; scan directory
  (link 104 107
	(<dot> <dot> <dot> <right-bracket>)
	(path-push :wild-inferiors directory-list))
  (link 104 finish
	(<dot> <right-bracket> <left-bracket> <hyphen>)
	(reclaim-pathname-components host device)
	(reclaim-nascent-vms-directory directory-list directory-item?)
	(error-in-filename-parse
	  "second directory spec can't have initial :up marker"))
  (link 104 105 ;"dual directory" syntax, e.g. "[user.][jh]"
        (<dot> <right-bracket> <left-bracket>)
	(cond
	  (dual-directory-impossible-p
	   (reclaim-pathname-components host device)
	   (reclaim-nascent-vms-directory directory-list directory-item?)
	   (error-in-filename-parse
	     "dual directory syntax not permited in this context"))
	  (doing-dual-directory-p
	   (reclaim-pathname-components host device)
	   (reclaim-nascent-vms-directory directory-list directory-item?)
	   (error-in-filename-parse
	     "dual directory syntax can't be cascaded"))
	  (t (setq directory-item? (nreverse directory-item?))
	     (setq doing-dual-directory-p t)
	     (change-filename-sequence-to directory-item? 3))))
  (link 104 105
        <right-bracket>
	(setq final-directory-item-p t)
	(setq directory-item? (nreverse directory-item?))
	(cond
	  ((and (null directory-item?) doing-dual-directory-p)
	   (reclaim-pathname-components host device)
	   (reclaim-nascent-vms-directory directory-list directory-item?)
	   (error-in-filename-parse
	     "second directory spec cannot be empty"))
	  (t (change-filename-sequence-to directory-item?))))
  (link 104 105
	<dot>
	(setq directory-item? (nreverse directory-item?))
	(change-filename-sequence-to directory-item?))
  (link 104 114 ;bad constituent char - second left-bracket
	<left-bracket>
	(reclaim-nascent-vms-directory directory-list directory-item?))
  (link 104 114 ;bad constituent char
	<colon>
	(reclaim-nascent-vms-directory directory-list directory-item?))
  (link 104 finish <end-of-sequence> ;at least one directory component
	(cond
	  (vms-directory-filenames-can-dangle-p
	   (when directory-item?
	     (setq directory-item? (nreverse directory-item?))
	     (path-push (copy-list-using-path-conses directory-item?)
			directory-list)
	     (reclaim-path-list directory-item?))
	   (setq directory
		 (coalesce-filename-sublists directory-list)))
	  (t (reclaim-nascent-vms-directory directory-list directory-item?)
	     (error-in-filename-parse
	       "VMS directory not terminated with \]"))))
  (link 104 104
	<anything>
	(path-push <anything> directory-item?))

  ;; directory item special cases
  (link 105 106
        (<hyphen> <end-of-sequence>)
	(unless doing-dual-directory-p
	  (setq dual-directory-impossible-p t))
	(path-push :up directory-list))
  (link 105 106
	(<asterisk> <end-of-sequence>)
	(path-push :wild directory-list))
  (link 105 106
	<go>
	(when directory-item?
	  (path-push (copy-list-using-path-conses directory-item?)
		     directory-list)))
  (link 106 (if final-directory-item-p 107 104) ;hack!
	<go>
	(reclaim-path-list directory-item?)
	(setq directory-item? nil)
	(resume-previous-filename-sequence))

  ;; finished scanning directory
  (link 107 108 
        <go>
	(setq directory
	      (coalesce-filename-sublists directory-list)))

  ;; special cases for name
  (link 108 110
	(<asterisk> <dot>)
	(setq name :wild))
  (link 108 finish
	(<asterisk> <end-of-sequence>)
	(setq name :wild))
  (link 108 109
	<go>)

  ;; scan name
  (link 109 110
	<dot>
	(setq name (coalesce-reversed-filename-list name-list)))
  (link 109 112
	<semicolon>
	(setq name (coalesce-reversed-filename-list name-list)))
  (link 109 finish
	<end-of-sequence>
	(setq name (coalesce-reversed-filename-list name-list)))
  (link 109 114 <left-bracket> ;bad constituent char
	(reclaim-path-list name-list))
  (link 109 114 <right-bracket> ;bad constituent char
	(reclaim-path-list name-list))
  (link 109 114 <colon> ;bad constituent char
	(reclaim-path-list name-list))
  (link 109 109
	<anything>
	(path-push <anything> name-list))

  ;; special cases for type
  ;; vms version delimiter characters may be either . or ;
  (link 110 112
	(<asterisk> <dot>)
	(setq type :wild))
  (link 110 112
	(<asterisk> <semicolon>)
	(setq type :wild))
  (link 110 finish
	(<asterisk> <end-of-sequence>)
	(setq type :wild))
  (link 110 111
	<go>)

  ;; vms version delimiter characters may be either . or ;
  (link 111 112
	<dot>
	(setq type (coalesce-reversed-filename-list type-list)))
  (link 111 112
	<semicolon>
	(setq type (coalesce-reversed-filename-list type-list)))
  (link 111 finish
	<end-of-sequence>
	(setq type (coalesce-reversed-filename-list type-list)))
  (link 111 114 <left-bracket> ;bad constituent char
	(reclaim-path-list type-list))
  (link 111 114 <right-bracket> ;bad constituent char
	(reclaim-path-list type-list))
  (link 111 114 <colon> ;bad constituent char
	(reclaim-path-list type-list))
  (link 111 111
	<anything>
	(path-push <anything> type-list))

  ;; special cases for version
  (link 112 finish
	(<asterisk> <end-of-sequence>)
	(setq version :wild))
  (link 112 finish
	(<hyphen> "1" <end-of-sequence>)
	(setq version :previous))
  (link 112 finish
	("0" <end-of-sequence>)
	(setq version :newest))
  (link 112 finish
	<end-of-sequence>
	(setq version :newest))
  (link 112 113
	<go>)

  ;; coerce version to integer here
  ;; special case integers like 0 and -1 have already been handled
  (link 113 finish
	(<word> <end-of-sequence>)
	(setq version 
	      (read-positive-fixnum-from-string
		<word>
		0
		(text-string-length <word>)))
	(unless version
	  (cond 
	    (accept-any-version-component-p
	     (setq version (coalesce-remainder-of-filename-sequence)))
	    (t (reclaim-pathname-components host device directory name type)
	       (error-in-filename-parse "non-numeric version")))))
  (link 113 finish
	(<hyphen> <word> <end-of-sequence>)
	(setq version
	      (read-positive-fixnum-from-string
		<word>
		0
		(text-string-length <word>)))
	(if (null version)
	    (cond 
	      (accept-any-version-component-p
	       (setq version (coalesce-remainder-of-filename-sequence)))
	      (t (reclaim-pathname-components host device directory name type)
		 (error-in-filename-parse "non-numeric version")))
	    (setq version (- version))))
  (link 113 finish
	<go>
	(cond 
	  (accept-any-version-component-p
	   (setq version (coalesce-remainder-of-filename-sequence)))
	  (t (reclaim-pathname-components host device directory name type)
	     (error-in-filename-parse "non-numeric version"))))

  ;; E.g.  a <left-bracket>, <right-bracket>, or <colon> in a base file name or
  ;; type.
  (link 114 finish
	<go>
	(reclaim-pathname-components host device directory name)
	(error-in-filename-parse "bad constituent char"))	
  )




;; jh, 12/12/91.  Added filename parser for DOS.

;; jh, 1/26/94.  Parameterized DOS filename parser to work on PC platforms
;; (where there are length limitations on filename components) as well as
;; Windows NT platforms (where there are no length limitations).

;; jh, 2/10/94.  DOS filenames also differ from Windows NT in that DOS filenames
;; are required to have an extension and Windows NT filenames are not.
;; Parameterized this as well.

;; mpc, 7/22/94.  File systems FYI:
;; File name constraints in NT are volume specific. That is, the naming constraints
;; depend on how the volume you are looking at is formatted. You could have a
;; single device partitioned and formatted multiple ways. (Yikes!) NT supports
;; three file system types: FAT, HPFS, and NTFS.  
;; 
;; 	FAT is the old DOS 8.3 uppercase file system. File names can
;; 	  contain chars A thru Z and special chars $%'-_@()`|#{}.
;; 	HPFS is the OS/2 standard of names up to 254 chars that can also
;; 	  include spaces plus special chars ,+=[];_.  File names can
;; 	  be upper, lower, or mixed case, for directory listings only
;; 	  therefore you cannot have two files whose names differ only by
;; 	  case.
;; 	NTFS is the new NT file system. A name consists of up to 255 Unicode
;; 	  characters. Like HPFS, names preserve case but are not case
;; 	  sensitive.
;; 
;; 	In addition, NTFS also supports a POSIX subsystem with POSIX.1
;; 	  compliant naming conventions, therefore README.TXT, Readme.txt,
;; 	  and readme.txt are three different files.

(defvar limit-dos-filename-component-lengths-p)
(defvar allow-extensionless-dos-filenames-p)
(defvar character-case-mode-for-generalized-dos)

(def-filename-parser generalized-dos
    (:global-variable-for-character-case
      character-case-mode-for-generalized-dos)
  (directory-item directory-list wildcard-encountered-p 
   name-and-type-list name-list type-list)
  (<dot> <backslash> <colon> <asterisk>)

  (link 100 101
	(<backslash> <backslash> <word>)
	(setq host (copy-text-string <word>))
	(setq version :unspecific))

  (link 100 101
	<go>
	(setq host :unspecific)
	(setq version :unspecific))

  ;; get device name if any
  (link 101 111
	(<word> <colon> <end-of-sequence>)
	(when limit-dos-filename-component-lengths-p
	  (unless (=f (text-string-length <word>) 1)
	    (error-in-filename-parse "device must only have one letter")))
	(setq device (copy-text-string <word>))
	(path-push :relative directory))
  (link 101 102
	(<word> <colon> <backslash>)
	(when limit-dos-filename-component-lengths-p
	  (unless (=f (text-string-length <word>) 1)
	    (error-in-filename-parse "device must only have one letter")))
	(setq device (copy-text-string <word>))
	(path-push :absolute directory-list))
  (link 101 102
	(<word> <colon>)
	(when limit-dos-filename-component-lengths-p
	  (unless (=f (text-string-length <word>) 1)
	    (error-in-filename-parse "device must only have one letter")))
	(setq device (copy-text-string <word>)))
  (link 101 102
	<backslash> 
	(path-push :absolute directory-list))
  (link 101 102
	<go>)

  ;; scan directory names
  (link 102 103
	<backslash>
	(when wildcard-encountered-p
	  (when directory-item
	    (reclaim-path-list directory-item))
	  (when directory-list
	    (reclaim-path-tree directory-list))
	  (error-in-filename-parse "no wildcards allowed in directory"))
	(setq directory-item
	      (nreverse directory-item))
	(change-filename-sequence-to directory-item))
  ;; current directory-item is actually a name/type
  (link 102 105
	<end-of-sequence>
	(setq directory
	      (coalesce-filename-sublists directory-list))
	(when directory
	  (unless (memq (car directory) '(:relative :absolute :home :up))
	    (path-push :relative directory)))
	(setq name-and-type-list
	      (nreverse directory-item))
	(change-filename-sequence-to name-and-type-list))
  (link 102 102
	<anything>
	(path-push <anything> directory-item))

  ;; decode special character sequences in a directory item
  (link 103 104
	<end-of-sequence>)
  (link 103 104
	(<dot> <end-of-sequence>)
	(path-push :relative directory-list))
  (link 103 104
	(<dot> <dot> <end-of-sequence>)
	(path-push :up directory-list))
  (link 103 104
	(<asterisk> <end-of-sequence>)
	(setq wildcard-encountered-p t))
  (link 103 104
	<go>
	(path-push (copy-list-using-path-conses
		     directory-item)
		   directory-list))
  (link 104 102
	<go>
	(reclaim-path-list directory-item)
	(setq directory-item nil)
	(resume-previous-filename-sequence))

  ;; special cases for name and type
  (link 105 111
	<end-of-sequence>)
  (link 105 111
	(<dot> <end-of-sequence>)
	(let ((new-directory-component (path-list :relative)))
	  (if directory
	      (setf (cdr (last directory)) new-directory-component)
	      (setq directory new-directory-component))))
  (link 105 111
	(<dot> <dot> <end-of-sequence>)
	(let ((new-directory-component (path-list :up)))
	  (if directory
	      (setf (cdr (last directory)) new-directory-component)
	      (setq directory new-directory-component))))

  (link 105 108
	(<asterisk> <dot>)
	(setq name :wild))
  (link 105 106
	<go>)

  ;; scan name and type
  (link 106 111
	<end-of-sequence>
	(cond
	  (allow-extensionless-dos-filenames-p
	   (setq name (coalesce-reversed-filename-list name-list)))
	  ;; jh, 11/21/94.  Consider the following if the change of
	  ;; allow-extensionless-dos-filenames-p to T in parse-dos-filename is
	  ;; too broad.
	  ;((equal name-list '(<asterisk>))
	  ; (setq name (coalesce-reversed-filename-list name-list)))
	  (t (when name-list
	       (reclaim-gensym-tree name-list))
	     (error-in-filename-parse "file type required"))))
  (link 106 108
	<dot>
	(setq name (coalesce-reversed-filename-list name-list)))
  (link 106 106
	<word>
	(path-push <word> name-list))
  (link 106 106
	<asterisk>
	(path-push <asterisk> name-list))

  (link 108 111
	(<asterisk> <end-of-sequence>)
	(setq type :wild))
  (link 108 110
	<go>)

  (link 110 111
	<end-of-sequence>
	(setq type (coalesce-reversed-filename-list type-list))
	;; Just truncate the file type instead of refusing to parse -- this is
	;; friendlier, in the sense that it is probably what DOS users expect.
	;; jh, 1/25/92.
	(when (and limit-dos-filename-component-lengths-p
		   (>f (text-string-length type) 3))
	  (setq type
		(prog1 (text-string-substring type 0 3)
		       (reclaim-text-string type)))))
  ;; jh, 12/19/96.  Snarfed from UNIX parser.  The following link handles
  ;; multiple dots -- we assume that the final dot delimits the file type.
  (link 110 110
	<dot>
	(setq type-list (nconc type-list 
			       (if name
				   (path-list "." name)
				   (path-list "."))))
	(setq type (coalesce-reversed-filename-list type-list))
	(setq type-list nil)
	(when name (reclaim-text-string name))
	(setq name type))
  (link 110 110
	<word>
	(path-push <word> type-list))
  (link 110 110
	<asterisk>
	(path-push <asterisk> type-list))

  ;; total chars must not exceed 63
  (link 111 finish
	<go>
	(reclaim-path-list name-and-type-list)
	(when limit-dos-filename-component-lengths-p
	  (let ((count-of-characters-in-filename 0))
	    (declare (type fixnum count-of-characters-in-filename))
	    (when device
	      (incff count-of-characters-in-filename 2))
	    (when (eq (car directory) :absolute)
	      (incff count-of-characters-in-filename 1))
	    (loop for directory-element in (cdr directory)
		  do
	      (case directory-element
		(:relative (incf count-of-characters-in-filename 1))
		(:up (incf count-of-characters-in-filename 2))
		(otherwise
		 (incff count-of-characters-in-filename 
			(1+f (text-string-length directory-element))))))
	    (if (text-string-p name)
		(incff count-of-characters-in-filename
		       (text-string-length name))
		(incff count-of-characters-in-filename 1))
	    (when name
	      (incff count-of-characters-in-filename 1))
	    (if (text-string-p type)
		(incff count-of-characters-in-filename
		       (text-string-length type))
		(incff count-of-characters-in-filename 1))
	    (when (>f count-of-characters-in-filename 63)
	      (when (text-string-p device)
		(reclaim-text-string device))
	      (when directory
		(loop for element in directory
		      when (text-string-p element)
			do (reclaim-text-string element)
		      finally
			(reclaim-path-list directory)))
	      (when (text-string-p name)
		(reclaim-text-string name))
	      (when (text-string-p type)
		(reclaim-text-string type))
	      (error-in-filename-parse "over 63 characters in filename"))))))

(defun-allowing-unwind parse-dos-filename (filename)
  (let* ((limit-dos-filename-component-lengths-p t)
	 (allow-extensionless-dos-filenames-p t)
	 (character-case-mode-for-generalized-dos :all-uppercase)
	 (result-pathname? (parse-generalized-dos-filename filename)))
    (when result-pathname?
      (setf (gensym-pathname-file-system result-pathname?) 'dos)
      (setf (gensym-pathname-filename-parser result-pathname?)
	    'parse-dos-filename)
      (setf (gensym-pathname-namestring-generator result-pathname?)
	    'generate-dos-namestring))
    result-pathname?))

;; jh, 11/21/94.  Changed allow-extensionless-dos-filenames-p to T in
;; parse-dos-filename because Mike C tells me that is allowed in the Windows-S
;; DOS.  Another reason is that the directory wildcarding machinery requires
;; that at least the extensionless filename "*" be parsable in DOS.  For a more
;; surgical fix, consider changing the 106 -> 111 link above per my note this
;; date.

(setf (convert-file-strings-to-uppercase-p 'dos) t)
(setf (convert-file-strings-to-uppercase-p 'parse-dos-filename) t)
(setf (filename-parser-of-file-system 'dos) 'parse-dos-filename)

(defun-allowing-unwind parse-win32-filename (filename)
  (let* ((limit-dos-filename-component-lengths-p nil)
	 (allow-extensionless-dos-filenames-p t)
	 (character-case-mode-for-generalized-dos :case-sensitive)
	 (result-pathname? (parse-generalized-dos-filename filename)))
    (when result-pathname?
      (setf (gensym-pathname-file-system result-pathname?) 'win32)
      (setf (gensym-pathname-filename-parser result-pathname?)
	    'parse-win32-filename)
      (setf (gensym-pathname-namestring-generator result-pathname?)
	    'generate-win32-namestring))
    result-pathname?))

(setf (convert-file-strings-to-uppercase-p 'win32) nil)
(setf (convert-file-strings-to-uppercase-p 'parse-win32-filename) nil)
(setf (filename-parser-of-file-system 'win32) 'parse-win32-filename)

#+development
(progn
  (setq all-known-file-systems (remove 'generalized-dos all-known-file-systems))
  (pushnew 'dos all-known-file-systems)
  (pushnew 'win32 all-known-file-systems))


;;;; Generating Namestrings

;;; The basic idea is to generate reclaimable text-strings from gensym-pathname
;;; structures.  We use the punctuation-registry symbols from the parsing machinery
;;; as a template for generating sections of the text-string, which will become a
;;; well-formed namestring in the file system.

;;; def-namestring-generator
;;;   file-system 
;;;   character-case-mode
;;;   (host-tag  host-template &rest host-plist)
;;;   (device-tag device-template &rest device-plist)
;;;   (dir-tag compound-dir-template dir-template &rest dir-plist)
;;;   (name-tag name-template &rest name-plist)
;;;   (type-tag type-template &rest type-plist)
;;;   (version-tag version-template &rest version-plist)

;;; As with def-filename-parser, character-case-mode is one of the symbols
;;; :case-sensitive or :all-uppercase, or a list of the form
;;; (:global-variable-for-character-case <variable>).

;;; each component in the def-namestring-generator form is of the general structure
;;;   (<tag> [ <compound-template> ] <component-template> 
;;;    . <special-meaning-plist>)
;;;
;;; <tag> simply names the component.  Acceptable tags are the symbols host, device,
;;; directory, name, type, and version, in that order.

;;; <compound-template> is typically a list containing zero or more literal
;;; strings, punctuation-registry symbols, or the special symbol :compound, which
;;; represents the contents of a compound component of the gensym-pathname.  Each
;;; element of the compount component is then formatted using the
;;; <component-template> below.  Currently (10/17/90) the only compound pathname
;;; component is the directory, though the VMS host component is probably complex
;;; enough to attain compound status someday.  An example of a sequence-template is
;;; the VMS form
;;;   (def-namestring-generator vms
;;;     ... 
;;;     (directory (<left-bracket> :compound <right-bracket>)  ...)
;;;     ...)
;;; which causes directories to be printed surrounded by brackets.

;;; <component-template> is a list containing zero or more literal strings,
;;; punctuation-registry symbols, or the special symbol :component, which
;;; represents the contents of a simple component of a gensym-pathname.  A simple
;;; component is one that has no inner structure and is represented as either a
;;; text-string or a symbol.  Currently (10/16/90) every pathname component except
;;; the directory is simple.  An example of a component-template is the Explorer
;;; form
;;;  (def-namestring-generator explorer
;;;    ...
;;;    (version (<sharp-sign> :component)))
;;; which causes the version to be printed preceded by a sharp-sign.

;;; <component-template> may also have a tail, which is a plist.  If so, this
;;; plist may contain the keys :last-item, :leading-items, or :special cases.
;;; :Last-item depicts the formatting instructions for the final item in a
;;; compound sequence; :leading-items depicts the formatting instructions for
;;; every other item.  These formatting instructions are a list of one or more
;;; literal strings or punctuation-registry symbols.  If either list contains a
;;; single element, the surrounding parentheses may be omitted for readability.

;;; :Special-cases is an alist which pairs a list of special patterns which may
;;; occur at the beginning of a compound sequence, such as (:relative :up).  If the
;;; generator detects such a sequence in the pathname component, it will replace it
;;; with the formatting instructions.  Again, these instructions are a list of one
;;; or more literal strings or punctuation-registry symbols, where singletons can
;;; omit their parentheses.  For example the namestring definition
;;;   (def-namestring-generator vms
;;;     ...
;;;     (directory (<left-bracket> :compound <right-bracket>)
;;;	           (:leading-items (:component <dot>)
;;;	            :last-item     (:component)
;;;	            :special-cases
;;;	            ((:relative :up) (<hyphen> <dot>))))
;;;     ...)
;;; will surround a VMS directory with square brackets, follow every component
;;; except the last with a dot, and print directory sequences beginning (:absolute
;;; :up ...) without the intervening dot.

;;; The default :special-cases behavior is to match any sequence which begins with
;;; the given pattern.  To match a sequence of limited length, use the symbol
;;; <end-of-sequence>.  For example the namestring definition
;;;   (def-namestring-generator explorer 
;;;     ...
;;;     (directory (:compound <semicolon>)
;;;	           (:leading-items (:component <dot>)
;;;	            :last-item     (:component)
;;;	            :special-cases
;;;	            ((:absolute <end-of-sequence>) <tilde>)))
;;;     ...)
;;; will follow an Explorer directory with a semicolon, follow every component
;;; except the last with a dot, and print a solitary tilde for a top-level
;;; directory.

;;; The tradeoff between formatting clarity and conciseness may get strained a bit
;;; in the :special-cases syntax.

;;; <special-meaning-plist> associates tags used in the pathname representation
;;; with formatting instructions.  Examples of such tags are :absolute (found in
;;; the directory component), :newest (found in the version), and :wild (found just
;;; about everywhere).  Formatting instructions are a list of zero or more
;;; punctuation-registry symbols or literal strings.  If this list contains only a
;;; single element, the surrounding parentheses may be omitted for readability.

;;; To allow for more complexities, a punctuation-registry token may appear
;;; surrounded by question-marks instead of the usual angle-brackets, e.g.
;;; ?colon?  instead of <colon>.  This notation causes the character to be omitted
;;; from the final namestring if the next token encountered is the symbol
;;; !delete!.  For example, the following namestring definition will cause
;;; a device name to be followed by a colon unless the first component in the
;;; directory is :relative.
;;;  (def-namestring-generator coral
;;;    ...
;;;    (device    (:component ?colon?) ...)
;;;    (directory (:compound)
;;;	          (:component <colon>
;;;	           :special-cases
;;;	           ((:relative) (!delete! <semicolon>) ...))))





;; The following write-xxx-for-namestring functions must be called only in the
;; context of a twith-output-to-text-string.


(defvar last-deletable-token-in-namestring nil)

(defun write-known-special-character-for-namestring
       (special-character-description)
  (let ((special-character-entry
	  (assoc special-character-description
		 filename-special-character-registry)))
    (if special-character-entry
	(twrite-char (cdr special-character-entry))
	#+development
	(error "unknown special character ~a in GENSYM-NAMESTRING" 
	       special-character-description))))

(defmacro flush-undeleted-token-in-namestring ()
  `(when last-deletable-token-in-namestring
     (write-known-special-character-for-namestring 
       last-deletable-token-in-namestring)
     (setq last-deletable-token-in-namestring nil)))

(defun write-special-character-for-namestring 
       (special-character-description)
  (cond ((eq special-character-description '!delete!)
	 (setq last-deletable-token-in-namestring nil))
	(t (flush-undeleted-token-in-namestring)
	   (cond ((text-string-p special-character-description)
		  (twrite-string special-character-description))
		 ((and (consp special-character-description)
		       (eq (first special-character-description) 
			   '!deletable!))
		  (setq last-deletable-token-in-namestring
			(second special-character-description)))
		 (t (write-known-special-character-for-namestring
		      special-character-description))))))
  

(defun write-special-characters-for-namestring 
       (special-character-description)
  (cond ((text-string-p special-character-description)
	 (flush-undeleted-token-in-namestring)
	 (twrite-string special-character-description))
	((and (consp special-character-description)
	      (eq (first special-character-description) '!deletable!))
	 (setq last-deletable-token-in-namestring
	       (second special-character-description)))
	((consp special-character-description)
	 (loop for special-character-subdescription
		   in special-character-description
	       do
	       (write-special-character-for-namestring 
		 special-character-subdescription)))
	(t (write-special-character-for-namestring
	     special-character-description))))



(defun write-monolithic-component-for-namestring
       (component component-template 
	special-symbol-plist convert-to-uppercase-p)
  (if (or (null component)
	  (eq :unspecific component))
      (flush-undeleted-token-in-namestring)
      (loop for template-item in component-template
	    do
	    (case template-item
	      (:component
	       (let ((special-symbol-entry 
		       (getf special-symbol-plist component)))
		 (cond (special-symbol-entry
			(write-special-characters-for-namestring
			  special-symbol-entry))
		       ((and (text-string-p component)
			     convert-to-uppercase-p)
			(let ((uppercase-component
				(nstring-upcasew
				  (copy-text-string component))))
			  (twrite uppercase-component)
			  (reclaim-text-string uppercase-component)))
		       (t (flush-undeleted-token-in-namestring)
			  (twrite component)))))
	      (otherwise
	       (write-special-character-for-namestring template-item))))))


;; Directories are currently (12/16/90) the only compound components, but this
;; could change as filename components, especially hosts and devices, grow more
;; complex.  Hence the abstraction here.

(defun write-compound-component-for-namestring
       (component component-template sequence-template
	heterogeneous-sequence-p special-symbol-plist
	prologue? convert-to-uppercase-p)
  (if (and (null component)
	   (null prologue?))
      (flush-undeleted-token-in-namestring)
      (let ((inner-component-template nil)
	    (last-component-template nil))
	(when heterogeneous-sequence-p
	  (setq inner-component-template
		(getf component-template :leading-items))
	  (setq last-component-template
		(getf component-template :last-item)))
	(loop for sequence-item in sequence-template
	      do
	      (case sequence-item
		(:compound
		 (loop initially
		       (when prologue?
			 (write-special-characters-for-namestring
			   prologue?))
		       for component-item in component
		       for component-cons on component
		       for last-component-template? =
			   (and (null (cdr component-cons))
				last-component-template)
		       do
		       (if heterogeneous-sequence-p
			   (write-monolithic-component-for-namestring
			     component-item
			     (or last-component-template?
				 inner-component-template)
			     special-symbol-plist
			     convert-to-uppercase-p)
			   (write-monolithic-component-for-namestring
			     component-item
			     component-template
			     special-symbol-plist
			     convert-to-uppercase-p))))
		(otherwise
		 (write-special-character-for-namestring 
		   sequence-item)))))))



(defun-for-macro special-cases-for-def-namestring-generator
		 (special-cases?
		   directory-template
		   directory-sequence
		   heterogeneous-directory-format-p
		   directory-plist
		   convert-p)
  (let* ((maximum-pattern-length
	   (loop for match-pattern in special-cases?
				   by 'cddr
		 maximize (or (position '<end-of-sequence> match-pattern)
			      (length match-pattern))))
	 (match-variables
	   (loop for index from 1 to maximum-pattern-length
		 collect
		 (intern
		   (format nil "MATCH-~d" index)))))
    `(let* ((directory-length
	      (length gensym-pathname-directory))
	    ,@(loop for match-variable in match-variables
		    for index from 0
		    unless (eq '<end-of-sequence> match-variable)
		      collect
		      `(,match-variable
		          (if (<f ,index directory-length)
			      (nth ,index gensym-pathname-directory)
			      nil))))
       (cond ,@(loop for (match-pattern special-template)
			 on special-cases?
			 by 'cddr
		     for pattern-length = (length match-pattern)
		     collect
		     `((and ,(if (memq '<end-of-sequence> match-pattern)
				 `(=f directory-length 
				     ,(position '<end-of-sequence> 
						match-pattern))
				 `(>=f directory-length ,pattern-length))
			    ,@(loop for match-element in match-pattern
				    for match-variable in match-variables
				    for index from 0 below pattern-length
				    until 
				    (eq '<end-of-sequence> match-element)
				    collect
				    `(eq ',match-element ,match-variable)))
		       (write-compound-component-for-namestring
			 (nthcdr ,pattern-length gensym-pathname-directory)
			 ',directory-template
			 ',directory-sequence
			 ,heterogeneous-directory-format-p
			 ',directory-plist
			 ',special-template
			 ,convert-p)))
	     (t (write-compound-component-for-namestring
		  gensym-pathname-directory
		  ',directory-template
		  ',directory-sequence
		  ,heterogeneous-directory-format-p
		  ',directory-plist
		  nil
		  ,convert-p))))))



(defun-for-macro convert-template-with-deletion-possible
		 (template)
  (loop for token in template
	collect
        (if (not (symbolp token))
	    token
	    (let* ((token-name (symbol-name token))
		   (token-end (1- (length token-name))))
	      (if (or (< token-end 1)
		      (not (eql (char token-name 0) #\?))
		      (not (eql (char token-name token-end) #\?)))
		  token
		  (list '!deletable!
			(intern 
			  (format nil "<~a>"
				  (subseq token-name 1 token-end)))))))))





(defmacro def-namestring-generator 
	  (file-system 
	   character-case-mode
	   (host-tag  host-template &rest host-plist)
	   (device-tag device-template &rest device-plist)
	   (dir-tag directory-sequence directory-template &rest directory-plist)
	   (name-tag name-template &rest name-plist)
	   (type-tag type-template &rest type-plist)
	   (version-tag version-template &rest version-plist))
  (unless (and (eq 'host host-tag)
	       (eq 'device device-tag)
	       (eq 'directory dir-tag)
	       (eq 'name name-tag)
	       (eq 'type type-tag)
	       (eq 'version version-tag))
    (error "bad syntax in DEF-NAMESTRING-GENERATOR"))
  (unless (or (memq character-case-mode '(:case-sensitive :all-uppercase))
	      (and (consp character-case-mode)
		   (eq (first character-case-mode)
		       :global-variable-for-character-case)
		   (second character-case-mode)))
    (error "DEF-NAMESTRING-GENERATOR: unknown character case mode ~a"
	   character-case-mode))
  (let ((generator-name
	  (intern (format nil "GENERATE-~a-NAMESTRING" file-system)))
	(compile-time-convert-p
	  (if (eq character-case-mode :all-uppercase)
	      't
	      'nil))
	;; jh, 8/23/94.  We don't rely on character-case-mode at runtime any
	;; more, since lowercase characters cannot get into gensym-pathnames
	;; created in file systems that only allow uppercase, and we need the
	;; ability to lowercase internally on behalf of the
	;; def-gensym-namestring functions for which prefer-lowercase-p is
	;; non-nil.
	(convert-p 'nil))

    `(progn
       (eval-when (:compile-toplevel :load-toplevel :execute)
	 (setf (convert-file-strings-to-uppercase-p ',generator-name)
	       ,compile-time-convert-p)
	 (setf (convert-file-strings-to-uppercase-p ',file-system)
	       ,compile-time-convert-p))

       (setf (namestring-generator-of-file-system ',file-system)
	     ',generator-name)

       (defun ,generator-name (pathname)
	 (with-pathname-components (pathname)
	   (twith-output-to-text-string
	     ,@(if host-template
		   `((write-monolithic-component-for-namestring
		       gensym-pathname-host
		       ',(convert-template-with-deletion-possible 
			   host-template)
		       ',(strings-to-text-strings-in-list host-plist)
		       ,convert-p)))
	     ,@(if device-template
		   `((write-monolithic-component-for-namestring
		       gensym-pathname-device
		       ',(convert-template-with-deletion-possible
			   device-template)
		       ',(strings-to-text-strings-in-list device-plist)
		       ,convert-p)))
	     ,(let ((converted-directory-template
		      (convert-template-with-deletion-possible
			directory-template))
		    (heterogeneous-directory-format-p
		      (and (getf directory-template :leading-items)
			   (getf directory-template :last-item)
			   t))
		    (special-cases?
		      (getf directory-template :special-cases)))
		(cond (special-cases?
		       (remf converted-directory-template :special-cases)
		       (special-cases-for-def-namestring-generator
			 special-cases?
			 converted-directory-template
			 directory-sequence
			 heterogeneous-directory-format-p
			 (strings-to-text-strings-in-list directory-plist)
			 convert-p))
		    (t `(write-compound-component-for-namestring
			  gensym-pathname-directory
			  ',converted-directory-template
			  ',directory-sequence
			  ,heterogeneous-directory-format-p
			  ',(strings-to-text-strings-in-list directory-plist)
			  nil
			  ,convert-p))))
	     (write-monolithic-component-for-namestring
	       gensym-pathname-name
	       ',(convert-template-with-deletion-possible
		   name-template)
	       ',(strings-to-text-strings-in-list name-plist)
	       ,convert-p)
	     ,@(if type-template
		   `((write-monolithic-component-for-namestring
		       gensym-pathname-type
		       ',(convert-template-with-deletion-possible
			   type-template)
		       ',(strings-to-text-strings-in-list type-plist)
		       ,convert-p)))
	     ,@(if version-template
		   `((write-monolithic-component-for-namestring
		       gensym-pathname-version
		       ',(convert-template-with-deletion-possible
			   version-template)
		       ',(strings-to-text-strings-in-list version-plist)
		       ,convert-p)))))))))









(def-namestring-generator unix :case-sensitive
  (host      (:component <colon>))
  (device    nil)
  (directory (:compound)
	     (:component <slash>) 
	     :absolute #w""
	     :relative <dot>
	     :up (<dot> <dot>)
	     :wild <asterisk>
	     :home <tilde>)
  (name      (:component) 
	     :wild <asterisk>)
  (type      (<dot> :component) 
	     :wild <asterisk>)
  (version   (:component) 
	     :previous <tilde>
	     :newest #w""
	     :wild #w"{~}*"))

;; jh, 10/31/91.  Changed the namestring generator for UNIX to handle :wild
;; versions.  This comes up in the system procedure for files-in-directory (see
;; FILE-IO) which doesn't care if the file system represents versions or not.
;; The UNIX system itself does not represent versions, but our namestring model
;; represents previous versions using a tilde (this seems to be a consensus
;; among other UNIX applications, like Gnu Emacs).  So we postpend a string that
;; makes gensym-directory search for files possibly ending in a tilde.  The
;; regular expression metacharacter sequence [~]* ("search for zero or more
;; occurrences of the single character tilde, which is not a metacharacter")
;; should do this, as long as convert-to-unix-regular-expression places the
;; end-of-sequence metacharacter ($) immediately following.  See man pages for
;; ed and re_comp for verification.

;; jh, 10/11/95.  Gensym regular expression syntax has long used curly braces
;; rather than square brackets.  A grep through the sources reveals nobody is
;; creating pathnames with :wild versions, so this bug has apparently gone
;; unnoticed for years.  Fixed.


(def-namestring-generator vms :all-uppercase
  (host      (:component <colon> <colon>))
  (device    (:component <colon>))
  (directory (<left-bracket> :compound <right-bracket>)
	     (:leading-items (:component <dot>)
	      :last-item     (:component)
	      :special-cases
	      (
	       (:relative :up) (<hyphen> <dot>)
	       (:absolute <end-of-sequence>) #w"000000"
	       (:absolute :wild-inferiors) (#w"000000" <dot> <dot> <dot>)
	       (:absolute) #w""
	       ))
	     :up <hyphen>
	     :wild <asterisk>
	     :wild-inferiors (<dot> <dot>)
	     :relative #w"")
  (name      (:component)
	     :wild <asterisk>)
  (type      (<dot> :component)
	     :wild <asterisk>)
  (version   (<semicolon> :component)
	     :previous #w"-1" 
	     :newest #w"0"
	     :wild <asterisk>))

;; jh per ac, 5/22/91.  Changed the VMS namestring generator not to include the
;; superfluous 000000 component of an absolute directory spec.  This was causing
;; problems when we used this spec to get the contents of a VMS directory, in that
;; the RMS call $PARSE couldn't understand it.


;; jh, 12/13/91.  Added a namestring generator for DOS.

(def-namestring-generator generalized-dos
    (:global-variable-for-character-case
      character-case-mode-for-generalized-dos)
  (host      (<backslash> <backslash> :component))
  (device    (:component <colon>))
  (directory (:compound)
	     (:component <backslash>) 
	     :absolute #w""
	     :relative <dot>
	     :up (<dot> <dot>))
  (name      (:component)
	     :wild <asterisk>)
  (type      (<dot> :component)
	     :wild <asterisk>)
  (version   nil))

(defun generate-dos-namestring (pathname)
  (let ((character-case-mode-for-generalized-dos :all-uppercase))
    (generate-generalized-dos-namestring pathname)))

(setf (convert-file-strings-to-uppercase-p 'generate-dos-namestring) t)
(setf (namestring-generator-of-file-system 'dos) 'generate-dos-namestring)

(defun generate-win32-namestring (pathname)
  (let ((character-case-mode-for-generalized-dos :case-sensitive))
    (generate-generalized-dos-namestring pathname)))

(setf (convert-file-strings-to-uppercase-p 'generate-win32-namestring) nil)
(setf (namestring-generator-of-file-system 'win32) 'generate-win32-namestring)






;;; Testing code for Pathname Parsers and Namestring Generators

#+development
(defparameter unix-filename-parser-test-data
  (copy-tree-changing-strings-to-text-strings
  '(
    ("/home/jh/.cshrc"           (nil :unspecific (:absolute "home" "jh") ".cshrc" nil nil))
    ("/home/jh/.cshrc.c"         (nil :unspecific (:absolute "home" "jh") ".cshrc" "c" nil))
    ("/home/jh/.cshrc.c.bak"     (nil :unspecific (:absolute "home" "jh") ".cshrc.c" "bak" nil))
    ("/home/jh/touch.tone.1"     (nil :unspecific (:absolute "home" "jh") "touch.tone" "1" nil))
    ("/home/jh/mci.touch.tone.1" (nil :unspecific (:absolute "home" "jh") "mci.touch.tone" "1" nil))
    ("."                         (nil :unspecific (:relative) nil nil nil))
    (".."                        (nil :unspecific (:up) nil nil nil))
    ("~/hello"                   (nil :unspecific (:home) "hello" nil nil))
    ("~/hello~"                  (nil :unspecific (:home) "hello" nil :previous))
    ("~/hello.txt~"              (nil :unspecific (:home) "hello" "txt" :previous))
    ("~/no/place/like/hi.txt~"   (nil :unspecific (:home "no" "place" "like") "hi" "txt" :previous))
    ("~/no/place/like/hi.~"      (nil :unspecific (:home "no" "place" "like") "hi" nil :previous))
    ("~"			 (nil :unspecific nil nil nil :previous))
    ("*"			 (nil :unspecific nil :wild nil nil))
    ("*stuff"			 (nil :unspecific nil "*stuff" nil nil))
    ("stuff*"			 (nil :unspecific nil "stuff*" nil nil))
    ("stuff*more"		 (nil :unspecific nil "stuff*more" nil nil))
    ("xyz.*"			 (nil :unspecific nil "xyz" :wild nil))
    ("xyz.*stuff"		 (nil :unspecific nil "xyz" "*stuff" nil))
    ("xyz.stuff*"		 (nil :unspecific nil "xyz" "stuff*" nil))
    ("xyz.stuff*more"		 (nil :unspecific nil "xyz" "stuff*more" nil))
    ("*.xyz"			 (nil :unspecific nil :wild "xyz" nil))
    ("./abc.xyz"		 (nil :unspecific (:relative) "abc" "xyz" nil))
    ("/*"			 (nil :unspecific (:absolute) :wild nil nil))
    ("/xyz.*"			 (nil :unspecific (:absolute) "xyz" :wild nil))
    ("/*.xyz"			 (nil :unspecific (:absolute) :wild "xyz" nil))
    ("/*/*/.././xyz"		 (nil :unspecific (:absolute :wild :wild :up :relative) "xyz" nil nil))
    ("wa:/*/*/.././xyz"		 ("wa" :unspecific (:absolute :wild :wild :up :relative) "xyz" nil nil))
    ;; following should return nil, since relative directories don't make any sense across machine boundaries
    ("wa:fe"			 (nil :unspecific nil "wa:fe" nil nil))
    ("/*/hello*/.././xyz.txt~"	 (nil :unspecific (:absolute :wild "hello*" :up :relative) "xyz" "txt" :previous))
    ("a/b/c"			 (nil :unspecific (:relative "a" "b") "c" nil nil))
    ("./a/b/c"			 (nil :unspecific (:relative "a" "b") "c" nil nil))
    ("../a/b/c"			 (nil :unspecific (:up "a" "b") "c" nil nil))
    )))




;; jh, 10/14/94.  Although VMS sometime parses "-" as :back, we can't do this,
;; since it involves going out to the actual file-system (see CLtL/2e pp
;; 620-22).  The general policy (alas, not documented anywhere general as yet)
;; is to keep the filename parsers in FILE-PARSE purely syntactic, and indeed
;; isolate all file-system interaction to gensym-truename, gensym-probe-file,
;; g2-stream-probe-file, gensym-directory, and gensym-subdirectories.  Also
;; pertinent are the comments near the def-merge-pathnames-rule for
;; replace-empty-components in PATHNAMES.  These comments describe the grief we
;; got into when we tried to diverge from purely syntactic filename parsing in
;; expanding VMS logical names.

#+development
(defparameter vms-filename-parser-test-data
  (copy-tree-changing-strings-to-text-strings
  '(
    ;; test "dual directory" syntax
    ("home:[us.-.users.jh.][for]"        nil) ;VMS syntax error
    ("home:[us.jh.for][-]"               nil) ;VMS expands "-" as :back here (see above note)
    ("home:[us.][jh.for.-]"              (nil "HOME" (:absolute "US" "JH" "FOR" :up) nil nil nil))
    ("home:[us.jh.][for.-]"              (nil "HOME" (:absolute "US" "JH" "FOR" :up) nil nil nil))
    ("home:[us.jh.][for]"                (nil "HOME" (:absolute "US" "JH" "FOR") nil nil nil))
    ("home:[us.jh][.for]"                nil) ;VMS syntax error
    ("home:[us.][jh.for.-]"              (nil "HOME" (:absolute "US" "JH" "FOR" :up) nil nil nil))
    ("[us.-.users.jh.][for]"             nil) ;VMS syntax error
    ("[us.jh.for][-]"                    nil) ;VMS expands "-" as :back here (see above note)
    ("[us.][jh.for.-]"                   (nil nil (:absolute "US" "JH" "FOR" :up) nil nil nil))
    ("[us.jh.][for.-]"                   (nil nil (:absolute "US" "JH" "FOR" :up) nil nil nil))
    ("[us.jh.][for]"                     (nil nil (:absolute "US" "JH" "FOR") nil nil nil))
    ("[us.jh][.for]"                     nil) ;VMS syntax error
    ("[us.][jh.for.-]"                   (nil nil (:absolute "US" "JH" "FOR" :up) nil nil nil))
    ("home:[us.-.users.jh.][for]xyz.zyx" nil) ;VMS syntax error
    ("home:[us.jh.for][-]xyz.zyx"        nil) ;VMS expands "-" as :back here (see above note)
    ("home:[us.][jh.for.-]xyz.zyx"       (nil "HOME" (:absolute "US" "JH" "FOR" :up) "XYZ" "ZYX" nil))
    ("home:[us.jh.][for.-]xyz.zyx"       (nil "HOME" (:absolute "US" "JH" "FOR" :up) "XYZ" "ZYX" nil))
    ("home:[us.jh.][for]xyz.zyx"         (nil "HOME" (:absolute "US" "JH" "FOR") "XYZ" "ZYX" nil))
    ("home:[us.jh][.for]xyz.zyx"         nil) ;VMS syntax error
    ("home:[us.][jh.for.-]xyz.zyx"       (nil "HOME" (:absolute "US" "JH" "FOR" :up) "XYZ" "ZYX" nil))
    ("home:[us.][jh.][for]"              nil) ;VMS syntax error
    ("home:[us.jh.][]"                   nil) ;VMS syntax error
    ("home:[][us.jh.]"                   nil) ;VMS syntax error
    ("[.]hello.text"                     nil) ;VMS syntax error
    ("[...][foreign]hello.text"          nil) ;VMS syntax error
    ("[000000][foreign]hello.text"       nil) ;VMS syntax error
    ("[000000...][foreign]hello.text"    nil) ;VMS syntax error

    ;; pre-existing stuff
    ("[hello.there.]"                    (nil nil (:absolute "HELLO" "THERE") nil nil nil))
    ("[hello.there.]jh"                  (nil nil (:absolute "HELLO" "THERE") "JH" nil nil))
    ("abc.xyz;o"			 nil) ;non-numeric version
    ("g230$:[customer.kbs:jh]x.kb"       nil) ;no colon in directory
    ("g230$:[customer.kbs[jh]x.kb"       nil) ;no second left-bracket in directory
    ("g230$[customer.kbs]x.kb"           nil) ;bad VMS namestring - device needs colon
    ("g230$:[customer.kbs]x.kb"          (nil "G230$" (:absolute "CUSTOMER" "KBS") "X" "KB" nil))
    (";*"                                (nil nil nil nil nil :wild))
    ("[...]hello.txt;0"                  (nil nil (:relative :wild-inferiors) "HELLO" "TXT" :newest))
    ("*"				 (nil nil nil :wild nil nil))
    ("*stuff"				 (nil nil nil "*STUFF" nil nil))
    ("stuff*"				 (nil nil nil "STUFF*" nil nil))
    ("stuff*more"			 (nil nil nil "STUFF*MORE" nil nil))
    ("xyz.*"				 (nil nil nil "XYZ" :wild nil))
    ("xyz.*stuff"			 (nil nil nil "XYZ" "*STUFF" nil))
    ("xyz.stuff*"			 (nil nil nil "XYZ" "STUFF*" nil))
    ("xyz.stuff*more"			 (nil nil nil "XYZ" "STUFF*MORE" nil))
    ("*.xyz"				 (nil nil nil :wild "XYZ" nil))
    ("*.*"				 (nil nil nil :wild :wild nil))
    ("*.*.*"				 (nil nil nil :wild :wild :wild))
    ("*.*;*"				 (nil nil nil :wild :wild :wild))
    ("[000000]*"			 (nil nil (:absolute) :wild nil nil))
    ("[000000...]*"			 (nil nil (:absolute :wild-inferiors) :wild nil nil))
    ("[...]*"			         (nil nil (:relative :wild-inferiors) :wild nil nil))
    ("[]xyz.*"				 (nil nil (:relative) "XYZ" :wild nil))
    ("[-.hello]*.xyz"			 (nil nil (:relative :up "HELLO") :wild "XYZ" nil))
    ("[goodbye.-.hello]*.xyz"		 (nil nil (:absolute "GOODBYE" :up "HELLO") :wild "XYZ" nil))
    ("[.hello]*.xyz"			 (nil nil (:relative "HELLO") :wild "XYZ" nil))
    ("[hello]*.xyz"			 (nil nil (:absolute "HELLO") :wild "XYZ" nil))
    ("abc.xyz;0"			 (nil nil nil "ABC" "XYZ" :newest))
    ("abc.xyz;"		        	 (nil nil nil "ABC" "XYZ" :newest))
    ("abc.xyz"		    	    	 (nil nil nil "ABC" "XYZ" nil))
    ("abc.xyz;-1"			 (nil nil nil "ABC" "XYZ" :previous))
    ("abc.xyz;-11"			 (nil nil nil "ABC" "XYZ" -11))
    ("abc.xyz;34"			 (nil nil nil "ABC" "XYZ" 34))
    ("acton::dua0:[x]y.z"		 ("ACTON" "DUA0" (:absolute "X") "Y" "Z" nil))
    ("g2$root:y.z"			 (nil "G2$ROOT" nil "Y" "Z" nil)) 
    ("acton\"a\"::dua0:[x]y.z"		 ("ACTON\"A\"" "DUA0" (:absolute "X") "Y" "Z" nil))
    ("acton\"a b\"::dua0:[x]y.z"	 ("ACTON\"A B\"" "DUA0" (:absolute "X") "Y" "Z" nil))
    )))



#+development
(defparameter generalized-dos-filename-parser-test-data
  (copy-tree-changing-strings-to-text-strings
  '(
    ("."                              (:unspecific nil (:relative) nil nil :unspecific))
    (".."                             (:unspecific nil (:up) nil nil :unspecific))
    ("xyz.*"			      (:unspecific nil nil "XYZ" :wild :unspecific))
    ("xyz.*x"		              (:unspecific nil nil "XYZ" "*X" :unspecific))
    ("xyz.x*"		              (:unspecific nil nil "XYZ" "X*" :unspecific))
    ("xyz.x*z"		              (:unspecific nil nil "XYZ" "X*Z" :unspecific))
    ("*.xyz"			      (:unspecific nil nil :wild "XYZ" :unspecific))
    (".\\abc.xyz"		      (:unspecific nil (:relative) "ABC" "XYZ" :unspecific))
    (".\\hello\\there\\abc.xyz"	      (:unspecific nil (:relative "HELLO" "THERE") "ABC" "XYZ" :unspecific))
    (".\\hello\\there\\abc\\"	      (:unspecific nil (:relative "HELLO" "THERE" "ABC") nil nil :unspecific))
    ("..\\hello\\there\\abc.xyz"      (:unspecific nil (:up "HELLO" "THERE") "ABC" "XYZ" :unspecific))
    ("\\hello\\there\\abc.xyz"	      (:unspecific nil (:absolute "HELLO" "THERE") "ABC" "XYZ" :unspecific))
    ("\\hello\\..\\there\\abc.xyz"    (:unspecific nil (:absolute "HELLO" :up "THERE") "ABC" "XYZ" :unspecific))
    ("\\hello\\.\\there\\abc.xyz"     (:unspecific nil (:absolute "HELLO" :relative "THERE") "ABC" "XYZ" :unspecific))
    ("\\xyz.*"			      (:unspecific nil (:absolute) "XYZ" :wild :unspecific))
    ("\\*.xyz"			      (:unspecific nil (:absolute) :wild "XYZ" :unspecific))
    ("a:.\\abc.xyz"		      (:unspecific "A" (:relative) "ABC" "XYZ" :unspecific))
    ("a:.\\hello\\there\\abc.xyz"     (:unspecific "A" (:relative "HELLO" "THERE") "ABC" "XYZ" :unspecific))
    ("a:.\\hello\\there\\abc\\"	      (:unspecific "A" (:relative "HELLO" "THERE" "ABC") nil nil :unspecific))
    ("a:..\\hello\\there\\abc.xyz"    (:unspecific "A" (:up "HELLO" "THERE") "ABC" "XYZ" :unspecific))
    ("a:\\hello\\there\\abc.xyz"      (:unspecific "A" (:absolute "HELLO" "THERE") "ABC" "XYZ" :unspecific))
    ("a:\\hello\\..\\there\\abc.xyz"  (:unspecific "A" (:absolute "HELLO" :up "THERE") "ABC" "XYZ" :unspecific))
    ("a:\\hello\\.\\there\\abc.xyz"   (:unspecific "A" (:absolute "HELLO" :relative "THERE") "ABC" "XYZ" :unspecific))
    ("a:\\xyz.*"		      (:unspecific "A" (:absolute) "XYZ" :wild :unspecific))
    ("a:\\*.xyz"		      (:unspecific "A" (:absolute) :wild "XYZ" :unspecific))
    ("a:"                             (:unspecific "A" (:relative) nil nil :unspecific))
    ("a:\\"                           (:unspecific "A" (:absolute) nil nil :unspecific))
    ("xyz.zyx"		              (:unspecific nil nil "XYZ" "ZYX" :unspecific))
    ;; no wildcards in directory
    ("\\hi\\*\\there\\john.text"      nil)
    ("abc.xyz.kb"                     (:unspecific nil nil "ABC.XYZ" "KB" :unspecific))
    )))

#+development
(defparameter dos-filename-parser-test-data
  (copy-tree-changing-strings-to-text-strings
  `(
    ,@generalized-dos-filename-parser-test-data
    ;; extensions must be no more than three chars
    ("xyz.abcd"		              (:unspecific nil nil "XYZ" "ABC" :unspecific))
    ;; 63-char limit
    ("12345678901234567890123456789012345678901234567890123456789.123"
                                      (:unspecific 
					nil 
					nil 
					"12345678901234567890123456789012345678901234567890123456789"
					"123"
					:unspecific))
    ("123456789012345678901234567890123456789012345678901234567890.234" nil)
    ;; extensionless pathnames
    ("d:\\bt\\ab\\g2\\o\\"            (:unspecific
					"D"
					(:absolute "BT" "AB" "G2" "O")
					nil
					nil
					:unspecific))
    ;; jh, 11/21/94.  Following filename used to yield nil.  In other words, the
    ;; parser used to reject extensionless filenames.  See my note this date
    ;; below parse-dos-filename for why we changed it.
    ("d:\\bt\\ab\\g2\\o"              (:unspecific
					"D"
					(:absolute "BT" "AB" "G2")
					"O"
					nil
					:unspecific))
    )))

#+development
(defparameter win32-filename-parser-test-data
  (copy-tree-changing-strings-to-text-strings
  `(
    ;; jh, 10/14/94.  The following shortcut won't work if we ever test mixed
    ;; character case in DOS, but why would we want to do that?
    ,@(loop for (input expected) in generalized-dos-filename-parser-test-data
	    collect
	    `(,input
	      ,(loop for component in expected
		     collect (cond
			       ((or (gensym-string-p component)
				    (text-string-p component))
				(string-downcasew (stringw component)))
			       ((consp component)
				(loop for subcomponent in component
				      collect
				      (if (or (gensym-string-p subcomponent)
					      (text-string-p subcomponent))
					  (string-downcasew (stringw subcomponent))
					  subcomponent)))
			       (t component)))))
    ;; no 3-char limit on extensions
    ("xyz.abcd"		              (:unspecific nil nil "xyz" "abcd" :unspecific))
    ;; no 63-char limit
    ("12345678901234567890123456789012345678901234567890123456789.123"
                                      (:unspecific 
					nil 
					nil 
					"12345678901234567890123456789012345678901234567890123456789"
					"123"
					:unspecific))
    ("123456789012345678901234567890123456789012345678901234567890.234"
                                      (:unspecific 
					nil 
					nil 
					"123456789012345678901234567890123456789012345678901234567890"
					"234"
					:unspecific))
    ;; extensionless pathnames permitted
    ("d:\\bt\\ab\\g2\\o\\"            (:unspecific
					"d"
					(:absolute "bt" "ab" "g2" "o")
					nil
					nil
					:unspecific))
    ("d:\\bt\\ab\\g2\\o"              (:unspecific
					"d"
					(:absolute "bt" "ab" "g2")
					"o"
					nil
					:unspecific))
    )))


#+development
(defparameter unix-namestring-generator-test-data
  (copy-tree-changing-strings-to-text-strings
  '(
    ("./"			(nil :unspecific (:relative) nil nil nil))
    ("~/hello.text{~}*"         (nil :unspecific (:home) "hello" "text" :wild))
    ("~/hello"                  (nil :unspecific (:home) "hello" nil nil))
    ("~/hello~"                 (nil :unspecific (:home) "hello" nil :previous))
    ("~/hello.txt~"             (nil :unspecific (:home) "hello" "txt" :previous))
    ("~/no/place/like/hi.txt~"  (nil :unspecific (:home "no" "place" "like") "hi" "txt" :previous))
    ("~/no/place/like/hi~"      (nil :unspecific (:home "no" "place" "like") "hi" nil :previous))
    ("~"			(nil :unspecific nil "~" nil nil))
    ("hello"                    (nil :unspecific nil "hello" nil nil))
    ("./*"			(nil :unspecific (:relative) :wild nil nil))
    ("./*stuff"			(nil :unspecific (:relative) "*stuff" nil nil))
    ("./stuff*"			(nil :unspecific (:relative) "stuff*" nil nil))
    ("./stuff*more"		(nil :unspecific (:relative) "stuff*more" nil nil))
    ("./xyz.*"			(nil :unspecific (:relative) "xyz" :wild nil))
    ("./xyz.*stuff"		(nil :unspecific (:relative) "xyz" "*stuff" nil))
    ("./xyz.stuff*"		(nil :unspecific (:relative) "xyz" "stuff*" nil))
    ("./xyz.stuff*more"		(nil :unspecific (:relative) "xyz" "stuff*more" nil))
    ("./*.xyz"			(nil :unspecific (:relative) :wild "xyz" nil))
    ("./*"			(nil :unspecific (:relative) :wild nil nil))
    ("*stuff"			(nil :unspecific nil "*stuff" nil nil))
    ("stuff*"			(nil :unspecific nil "stuff*" nil nil))
    ("stuff*more"		(nil :unspecific nil "stuff*more" nil nil))
    ("xyz.*"			(nil :unspecific nil "xyz" :wild nil))
    ("xyz.*stuff"		(nil :unspecific nil "xyz" "*stuff" nil))
    ("xyz.stuff*"		(nil :unspecific nil "xyz" "stuff*" nil))
    ("xyz.stuff*more"		(nil :unspecific nil "xyz" "stuff*more" nil))
    ("*.xyz"			(nil :unspecific nil :wild "xyz" nil))
    ("/*"			(nil :unspecific (:absolute) :wild nil nil))
    ("/xyz.*"			(nil :unspecific (:absolute) "xyz" :wild nil))
    ("/*.xyz"			(nil :unspecific (:absolute) :wild "xyz" nil))
    ("/*/*/.././xyz"		(nil :unspecific (:absolute :wild :wild :up :relative) "xyz" nil nil))
    ("wa:/*/*/.././xyz"		("wa" :unspecific (:absolute :wild :wild :up :relative) "xyz" nil nil))
    ("/*/hello*/.././xyz.txt~"	(nil :unspecific (:absolute :wild "hello*" :up :relative) "xyz" "txt" :previous))
    ("./~"			(nil :unspecific (:relative) "~" nil nil))
    ("./a/b/c"			(nil :unspecific (:relative "a" "b") "c" nil nil))
    ("a/b/c"			(nil :unspecific ("a" "b") "c" nil nil))
    )))





#+development
(defparameter vms-namestring-generator-test-data
  (copy-tree-changing-strings-to-text-strings
  '(
    ("[.GREETINGS...]HELLO.TXT;0"       (nil nil (:relative "GREETINGS" :wild-inferiors) "HELLO" "TXT" :newest))
    ("[GREETINGS...]HELLO.TXT;0"        (nil nil (:absolute "GREETINGS" :wild-inferiors) "HELLO" "TXT" :newest))
    ;; not all logicals should have the empty directory [] (g2$root itself shouldn't!)  
    ;; we have to decide where in the process to expand the logical name.
    ("G2$ROOT:[]Y.Z"			(nil "G2$ROOT" (:relative) "Y" "Z" nil)) 
    ("G2$ROOT:Y.Z"			(nil "G2$ROOT" nil "Y" "Z" nil)) 
    ("[...]HELLO.TXT;0"                 (nil nil (:relative :wild-INFERIORS) "HELLO" "TXT" :newest))
    ("[]*"				(nil nil (:relative) :wild nil nil))
    ("[]*STUFF"				(nil nil (:relative) "*STUFF" nil nil))
    ("[]STUFF*"				(nil nil (:relative) "STUFF*" nil nil))
    ("[]STUFF*MORE"			(nil nil (:relative) "STUFF*MORE" nil nil))
    ("[]XYZ.*"				(nil nil (:relative) "XYZ" :wild nil))
    ("[]XYZ.*STUFF"			(nil nil (:relative) "XYZ" "*STUFF" nil))
    ("[]XYZ.STUFF*"			(nil nil (:relative) "XYZ" "STUFF*" nil))
    ("[]XYZ.STUFF*MORE"			(nil nil (:relative) "XYZ" "STUFF*MORE" nil))
    ("[]*.XYZ"				(nil nil (:relative) :wild "XYZ" nil))
    ("[]*.*"				(nil nil (:relative) :wild :wild nil))
    ("[]*.*;*"				(nil nil (:relative) :wild :wild :wild))
    ("*"				(nil nil nil :wild nil nil))
    ("*STUFF"				(nil nil nil "*STUFF" nil nil))
    ("STUFF*"				(nil nil nil "STUFF*" nil nil))
    ("STUFF*MORE"			(nil nil nil "STUFF*MORE" nil nil))
    ("XYZ.*"				(nil nil nil "XYZ" :wild nil))
    ("XYZ.*STUFF"			(nil nil nil "XYZ" "*STUFF" nil))
    ("XYZ.STUFF*"			(nil nil nil "XYZ" "STUFF*" nil))
    ("XYZ.STUFF*MORE"			(nil nil nil "XYZ" "STUFF*MORE" nil))
    ("*.XYZ"				(nil nil nil :wild "XYZ" nil))
    ("*.*"				(nil nil nil :wild :wild nil))
    ("*.*;*"				(nil nil nil :wild :wild :wild))
    ("[000000]*"			(nil nil (:absolute) :wild nil nil))
    ("[000000...]*"			(nil nil (:absolute :wild-inferiors) :wild nil nil))
    ("[]XYZ.*"				(nil nil (:relative) "XYZ" :wild nil))
    ("[-.HELLO]*.XYZ"			(nil nil (:relative :UP "HELLO") :wild "XYZ" nil))
    ("[GOODBYE.-.HELLO]*.XYZ"           (nil nil (:absolute "GOODBYE" :UP "HELLO") :wild "XYZ" nil))
    ("[.HELLO]*.XYZ"			(nil nil (:relative "HELLO") :wild "XYZ" nil))
    ("[HELLO]*.XYZ"	   	        (nil nil (:absolute "HELLO") :wild "XYZ" nil))
    ("[]ABC.XYZ;0"			(nil nil (:relative) "ABC" "XYZ" :newest))
    ("[]ABC.XYZ"		    	(nil nil (:relative) "ABC" "XYZ" nil))
    ("[]ABC.XYZ;-1"			(nil nil (:relative) "ABC" "XYZ" :previous))
    ("[]ABC.XYZ;-11"			(nil nil (:relative) "ABC" "XYZ" -11))
    ("[]ABC.XYZ;34"			(nil nil (:relative) "ABC" "XYZ" 34))
    ("ACTON::DUA0:[X]Y.Z"	        ("ACTON" "DUA0" (:absolute "X") "Y" "Z" nil))
    ("ACTON\"A\"::DUA0:[X]Y.Z"	        ("ACTON\"A\"" "DUA0" (:absolute "X") "Y" "Z" nil))
    ("ACTON\"A B\"::DUA0:[X]Y.Z"	("ACTON\"A B\"" "DUA0" (:absolute "X") "Y" "Z" nil))
    )))


#+development
(defparameter dos-namestring-generator-test-data
  (copy-tree-changing-strings-to-text-strings
  '(
    (".\\"                            (:unspecific nil (:relative) nil nil :unspecific))
    ("..\\"                           (:unspecific nil (:up) nil nil :unspecific))
    ("XYZ.*"			      (:unspecific nil nil "XYZ" :wild :unspecific))
    ("XYZ.*X"		              (:unspecific nil nil "XYZ" "*X" :unspecific))
    ("XYZ.X*"		              (:unspecific nil nil "XYZ" "X*" :unspecific))
    ("XYZ.X*Z"		              (:unspecific nil nil "XYZ" "X*Z" :unspecific))
    ("*.XYZ"			      (:unspecific nil nil :wild "XYZ" :unspecific))
    (".\\ABC.XYZ"		      (:unspecific nil (:relative) "ABC" "XYZ" :unspecific))
    (".\\HELLO\\THERE\\ABC.XYZ"	      (:unspecific nil (:relative "HELLO" "THERE") "ABC" "XYZ" :unspecific))
    (".\\HELLO\\THERE\\ABC\\"	      (:unspecific nil (:relative "HELLO" "THERE" "ABC") nil nil :unspecific))
    ("..\\HELLO\\THERE\\ABC.XYZ"      (:unspecific nil (:up "HELLO" "THERE") "ABC" "XYZ" :unspecific))
    ("\\HELLO\\THERE\\ABC.XYZ"	      (:unspecific nil (:absolute "HELLO" "THERE") "ABC" "XYZ" :unspecific))
    ("\\HELLO\\..\\THERE\\ABC.XYZ"    (:unspecific nil (:absolute "HELLO" :up "THERE") "ABC" "XYZ" :unspecific))
    ("\\HELLO\\.\\THERE\\ABC.XYZ"     (:unspecific nil (:absolute "HELLO" :relative "THERE") "ABC" "XYZ" :unspecific))
    ("\\XYZ.*"			      (:unspecific nil (:absolute) "XYZ" :wild :unspecific))
    ("\\*.XYZ"			      (:unspecific nil (:absolute) :wild "XYZ" :unspecific))
    ("A:.\\ABC.XYZ"		      (:unspecific "A" (:relative) "ABC" "XYZ" :unspecific))
    ("A:.\\HELLO\\THERE\\ABC.XYZ"     (:unspecific "A" (:relative "HELLO" "THERE") "ABC" "XYZ" :unspecific))
    ("A:.\\HELLO\\THERE\\ABC\\"	      (:unspecific "A" (:relative "HELLO" "THERE" "ABC") nil nil :unspecific))
    ("A:..\\HELLO\\THERE\\ABC.XYZ"    (:unspecific "A" (:up "HELLO" "THERE") "ABC" "XYZ" :unspecific))
    ("A:\\HELLO\\THERE\\ABC.XYZ"      (:unspecific "A" (:absolute "HELLO" "THERE") "ABC" "XYZ" :unspecific))
    ("A:\\HELLO\\..\\THERE\\ABC.XYZ"  (:unspecific "A" (:absolute "HELLO" :up "THERE") "ABC" "XYZ" :unspecific))
    ("A:\\HELLO\\.\\THERE\\ABC.XYZ"   (:unspecific "A" (:absolute "HELLO" :relative "THERE") "ABC" "XYZ" :unspecific))
    ("A:\\XYZ.*"		      (:unspecific "A" (:absolute) "XYZ" :wild :unspecific))
    ("A:\\*.XYZ"		      (:unspecific "A" (:absolute) :wild "XYZ" :unspecific))
    ("A:.\\"                          (:unspecific "A" (:relative) nil nil :unspecific))
    ("A:\\"                           (:unspecific "A" (:absolute) nil nil :unspecific))
    )))



(defmacro test-namestring-facility (test-data facility-function mode)
  `(loop for ,(case mode
		(:parse `(input desired))
		(:generate `(desired input)))
	     in ,test-data
	do
	(format t "~&input ~s should return ~s (press [cr])~%"
		input
		desired)
	(read-char)
	(let ((result 
		,(case mode
		   (:parse `(let ((result (funcall ,facility-function input)))
			      (if (gensym-pathname-p result)
				  (path-list
				    (gensym-pathname-host result)
				    (gensym-pathname-device result)
				    (gensym-pathname-directory result)
				    (gensym-pathname-name result)
				    (gensym-pathname-type result)
				    (gensym-pathname-version result))
				  nil)))
		   (:generate `(funcall ,facility-function
					(apply 
					  #'make-gensym-pathname-structure-function
					  input))))))
	  (cond ((equalw result desired)
		 (format t "~&successfully returned ~s~2%" result))
		(t (format t "~&!!! failed !!! result was ~s~2%"
			   result)
		   (format t "~&type q to quit: ")
		   (if (eql (read-char) #\q)
		       (return nil)
		       (clear-input)))))))


(defmacro validate-namestring-facility (test-data facility-function mode)
  `(loop for ,(case mode
		(:parse `(input desired))
		(:generate `(desired input)))
	     in ,test-data
	 with all-correct-p = t
	do
	(let ((result 
		,(case mode
		   (:parse `(let ((result (funcall ,facility-function input)))
			      (if (gensym-pathname-p result)
				  (path-list
				    (gensym-pathname-host result)
				    (gensym-pathname-device result)
				    (gensym-pathname-directory result)
				    (gensym-pathname-name result)
				    (gensym-pathname-type result)
				    (gensym-pathname-version result))
				  nil)))
		   (:generate `(funcall ,facility-function
					(apply 
					  #'make-gensym-pathname-structure-function
					  input))))))
	  (unless (equalw result desired)
	    (setq all-correct-p nil)
	    (format t "~&!!! failure !!!~%result: ~s~%desired: ~s~2%"
		    result
		    desired)))
	 finally
	  (return all-correct-p)))



#+development
(defun test-unix-filename-parser ()
  (test-namestring-facility 
    unix-filename-parser-test-data 
    'parse-unix-filename 
    :parse))

#+development
(defun validate-unix-filename-parser ()
  (validate-namestring-facility 
    unix-filename-parser-test-data 
    'parse-unix-filename 
    :parse))

#+development
(defun test-vms-filename-parser ()
  (test-namestring-facility 
    vms-filename-parser-test-data 
    'parse-vms-filename 
    :parse))

#+development
(defun validate-vms-filename-parser ()
  (validate-namestring-facility 
    vms-filename-parser-test-data 
    'parse-vms-filename 
    :parse))

#+development
(defun test-dos-filename-parser ()
  (test-namestring-facility 
    dos-filename-parser-test-data 
    'parse-dos-filename 
    :parse))

#+development
(defun validate-dos-filename-parser ()
  (validate-namestring-facility 
    dos-filename-parser-test-data 
    'parse-dos-filename 
    :parse))

#+development
(defun test-win32-filename-parser ()
  (test-namestring-facility 
    win32-filename-parser-test-data 
    'parse-win32-filename 
    :parse))

#+development
(defun validate-win32-filename-parser ()
  (validate-namestring-facility 
    win32-filename-parser-test-data 
    'parse-win32-filename 
    :parse))



#+development
(defun test-unix-namestring-generator ()
  (test-namestring-facility 
    unix-namestring-generator-test-data 
    'generate-unix-namestring
    :generate))

#+development
(defun validate-unix-namestring-generator ()
  (validate-namestring-facility 
    unix-namestring-generator-test-data 
    'generate-unix-namestring
    :generate))

#+development
(defun test-vms-namestring-generator ()
  (test-namestring-facility 
    vms-namestring-generator-test-data 
    'generate-vms-namestring
    :generate))

#+development
(defun validate-vms-namestring-generator ()
  (validate-namestring-facility 
    vms-namestring-generator-test-data 
    'generate-vms-namestring
    :generate))

#+development
(defun test-dos-namestring-generator ()
  (test-namestring-facility 
    dos-namestring-generator-test-data 
    'generate-dos-namestring
    :generate))

#+development
(defun validate-dos-namestring-generator ()
  (validate-namestring-facility 
    dos-namestring-generator-test-data 
    'generate-dos-namestring
    :generate))



#+development
(defun validate-all-filename-parsers ()
  (format t "~&unix ...")
  (format t "~:[~&unix failed~; passed~]~2%"
	  (validate-unix-filename-parser))
  (format t "~&vms ...")
  (format t "~:[~&vms failed~; passed~]~2%"
	  (validate-vms-filename-parser))

  (format t "~&dos ...")
  (format t "~:[~&dos failed~; passed~]~2%"
	  (validate-dos-filename-parser))
  (format t "~&win32 ...")
  (format t "~:[~&win32 failed~; passed~]~2%"
	  (validate-win32-filename-parser))
  )


#+development
(defun validate-all-namestring-generators ()
  (format t "~&unix ...")
  (format t "~:[~&unix failed~; passed~]~2%"
	  (validate-unix-namestring-generator))
  (format t "~&vms ...")
  (format t "~:[~&vms failed~; passed~]~2%"
	  (validate-vms-namestring-generator))

  (format t "~&dos & win32 ...")
  (format t "~:[~&dos & win32 failed~; passed~]~2%"
	  (validate-dos-namestring-generator))
  )





;; e.g., 
;; (examine-filename-parser-memory-use
;;   #'parse-unix-filename
;;   unix-filename-parser-test-data)
;; (remember to do it twice -- the second time counts)

#+development
(defun examine-filename-parser-memory-use (parsing-function test-data)
  (loop for (input nil) in test-data
	do
	(format t "~&input: ~a" input)
	(with-memory-checking
	  (let ((pathname? 
		  (funcall parsing-function input)))
	    (when pathname?
	      (reclaim-gensym-pathname pathname?))))
	(format t "~%~%")))

#+development
(defun examine-memory-use-of-all-filename-parsers ()
  (macrolet ((examine (file-system)
	       `(progn (format t ,(format nil "~~&;;; ~a:~~%" file-system))
		       (examine-filename-parser-memory-use
			 #',(intern (format nil "PARSE-~a-FILENAME" file-system))
			 ,(intern (format nil "~a-FILENAME-PARSER-TEST-DATA" file-system))))))
    (examine unix)
    (examine vms)
    (examine dos)
    (examine win32)
    ))


;; e.g., 
;; (examine-namestring-generator-memory-use
;;   #'generate-unix-namestring
;;   unix-namestring-generator-test-data)
;; (remember to do it twice -- the second time counts)

#+development
(defun examine-namestring-generator-memory-use (generating-function test-data)
  (let ((empty-pathname
	  (make-gensym-pathname-structure-function nil nil nil nil nil nil)))
    (loop for (nil input) in test-data 
	  do 
          (format t "~&input: ~a~%" input)
	  (setf (gensym-pathname-host empty-pathname) (first input))
	  (setf (gensym-pathname-device empty-pathname) (second input))
	  (setf (gensym-pathname-directory empty-pathname) (third input))
	  (setf (gensym-pathname-name empty-pathname) (fourth input))
	  (setf (gensym-pathname-type empty-pathname) (fifth input))
	  (setf (gensym-pathname-version empty-pathname) (sixth input))
	  (with-memory-checking
	    (let ((namestring?
		    (funcall generating-function empty-pathname)))
	      (when namestring?
		(reclaim-text-string namestring?))))
	  (format t "~%~%"))))

#+development
(defun examine-memory-use-of-all-namestring-generators ()
  (macrolet ((examine (file-system)
	       `(progn (format t ,(format nil "~~&;;; ~a:~~%" file-system))
		       (examine-namestring-generator-memory-use
			 #',(intern (format nil "GENERATE-~a-NAMESTRING" file-system))
			 ,(intern (format nil "~a-NAMESTRING-GENERATOR-TEST-DATA" file-system))))))
    (examine unix)
    (examine vms)
    (examine dos)
    ))

;; End file with CR


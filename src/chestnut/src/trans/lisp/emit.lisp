;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; emit.lisp -- emit C code
;;;
;;; author :  Sandra Loosemore
;;; date   :  26 Jun 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;
;;; The emitter tries to produce legible (but not beautiful) output.
;;; I assume that anybody who is really finicky about code appearance
;;; is capable of piping it through a formatter like the Unix indent 
;;; utility.
;;;

; *** Crocks:
; *** - Doesn't keep track of whether to unwind stack very elegantly.
; *** - Temporary fix for RETURN_VALUE, etc.:  uses global temp and
; ***   can't handle precedence.

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/emit.lisp,v $"
 "$Revision: 1.15 $"
 "$Date: 2007/07/13 18:16:52 $")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Formatting utilities
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Experimental:  Unprotected mode:

(defparameter *protect-local-variables* t)


;;; Header lines to be output to the top of each file

(define-translator-parameter *header-lines*
  '("#include \"user.h\""))
;  '("#include \"kernel.h\""))

;;; Switch to permit date to be omitted from output files.
;;; This is for the benefit of users who use grep to determine
;;; which output files have changed.

(define-translator-parameter *include-dates-in-headers* t)


;;; Switch to determine whether application function and global
;;; variable definitions are generated in header files, or
;;; at the top of each referencing function definition

(define-translator-parameter *local-declarations* nil)


;;; Keep track of the indentation level for the emitted code.  This
;;; variable is rebound at strategic points by the emitter.

(defvar *indent-column* 0)


;;; Keep track of where we are column-wise in the output to help in
;;; placing line breaks.

;(defvar *current-column* 0)


;;; How far do we want to indent nested levels?

(define-translator-parameter *indent-delta* 4)


;;; Indentation for "semi-block" constructs like PUSH_SPECIAL

(define-translator-parameter *semi-indent-delta* 2)


;;; Where is the right margin?

(define-translator-parameter *margin-column* 79)


;;; T if any declarations emitted at top of function body;
;;; if so, separate by a newline from statements.
(defvar *any-declarations-p* nil)

;;;;;; Define constants for operator precedence.  The ordering is taken
;;; straight from K&R.  We don't actually generate code using many of
;;; these operators (yet).

(defconstant expression-precedence      0)  ; default
(defconstant comma-precedence           1)  ; comma operator
(defconstant assignment-precedence      2)  ; assignment operators
(defconstant conditional-precedence     3)  ; conditional operator
(defconstant logical-or-precedence      4)  ; || operator
(defconstant logical-and-precedence     5)  ; && operator
(defconstant bitwise-ior-precedence     6)  ; | operator
(defconstant bitwise-xor-precedence     7)  ; ^ operator
(defconstant bitwise-and-precedence     8)  ; binary & operator
(defconstant equality-precedence        9)  ; == and != operators
(defconstant relational-precedence     10)  ; <, >, <=, >= operators
(defconstant shift-precedence          11)  ; << and >> operators
(defconstant additive-precedence       12)  ; binary + and - operators
(defconstant multiplicative-precedence 13)  ; binary *, /, % operators.
(defconstant cast-precedence           14)  ; cast operator
(defconstant prefix-precedence         15)  ; various unary prefix operators
(defconstant postfix-precedence        16)  ; various unary postfix operators
(defconstant primary-precedence        17)  ; identifier, constant, etc.

(defstruct c-operator
  name
  precedence
  argument-count
  string
  prefix-p)

(defun get-c-operator (name)
  (let ((op (get name 'c-operator)))
    (check-type op c-operator)
    op))

(defsetf get-c-operator (name) (value)
  `(setf (get ,name 'c-operator) ,value))

(defmacro define-prefix-c-operator (name string precedence)
  `(setf (get-c-operator ',name)
	 (make-c-operator :name ',name
			  :argument-count 1
			  :string ,string
			  :precedence ,precedence
			  :prefix-p t)))

(defmacro define-binary-c-operator (name string precedence)
  `(setf (get-c-operator ',name)
	 (make-c-operator :name ',name
			  :argument-count 2
			  :string ,string
			  :precedence ,precedence
			  :prefix-p nil)))

(define-binary-c-operator c+ " + " additive-precedence)
(define-binary-c-operator c- " - " additive-precedence)
(define-binary-c-operator c* " * " multiplicative-precedence)
(define-binary-c-operator c/ " / " multiplicative-precedence)
(define-binary-c-operator crem " % " multiplicative-precedence)
(define-binary-c-operator cbitand " & " bitwise-and-precedence)
(define-binary-c-operator cbitor  " | " bitwise-ior-precedence)
(define-binary-c-operator cbitxor " ^ " bitwise-xor-precedence)
(define-binary-c-operator c== " == " equality-precedence)
(define-binary-c-operator c!= " != " equality-precedence)
(define-binary-c-operator c< " < " relational-precedence)
(define-binary-c-operator c> " > " relational-precedence)
(define-binary-c-operator c<= " <= " relational-precedence)
(define-binary-c-operator c>= " >= " relational-precedence)
(define-binary-c-operator c<< " << " shift-precedence)
(define-binary-c-operator c>> " >> " shift-precedence)
(define-binary-c-operator csubscripting "[]" postfix-precedence)

(define-prefix-c-operator cbitnot " ~" prefix-precedence)
(define-prefix-c-operator clogicalnot " !" prefix-precedence)
(define-prefix-c-operator cnegate " - " prefix-precedence)
(define-prefix-c-operator c-cast-to-float "(float)" cast-precedence)
(define-prefix-c-operator c-cast-to-double "(double)" cast-precedence)
(define-prefix-c-operator cindirection " * " prefix-precedence)

;;; Various primitives.

(defvar *output-buffer* nil)

(eval-when (compile load eval)
(defparameter *output-buffer-size* 250)
)
(defvar null-trailer "")

(defstruct output-line
  (indent 0)
  (start 0)
  (length 0)
  (next-split-scan 0)
  (prev nil))

(defvar *free-output-lines* nil)

(defstruct output-buffer
  (stream (error "you must supply the stream") :type stream)
  (buffer (make-string *output-buffer-size*) :type simple-string)
  (size *output-buffer-size*)
  (start 0)
  (length 0)
  (line (make-output-line))
  (emit-and-split-p nil)
  (trailer nil)
  (margin nil)
  (margin1 nil)
  (first-line-p t))

#|| ; Moved to toplevel.lisp
(defmacro with-output-stream (stream &body forms)
  `(with-output-stream1 stream #'(lambda () ,@forms)))
||#

(defun with-output-stream1 (stream function)
  (let ((*output-buffer* (make-output-buffer :stream stream)))
    (prog1 (funcall function)
      (emit-output-line))))

(defun current-column ()
  (let* ((output-buffer (or *output-buffer*
			    (error "not inside with-output-stream")))
	 (line (output-buffer-line output-buffer))
	 (indent (output-line-indent line))
	 (length (output-line-length line)))
    (declare (fixnum indent length))
    (the fixnum (+ indent length))))

(defun current-column--one-line ()
  (let* ((output-buffer (or *output-buffer*
			    (error "not inside with-output-stream")))
	 (line (output-buffer-line output-buffer))
	 (indent (output-line-indent line))
	 (length (output-buffer-length output-buffer)))
    (declare (fixnum indent length))
    (the fixnum (+ indent length))))

(defmacro emit-newline ()
  `(emit-output-line nil t))

(defmacro emit-newline-indent (&optional (offset 0) trailer keep-p)
  `(emit-output-line ,trailer t (+ *indent-column* ,offset) ,keep-p))

(defmacro with-fast-output (stream &body forms)
  #-lucid
  `(macrolet ((put-char (char)
		`(write-char ,char ,',stream))
	      (put-string (string &optional start end)
		`(write-string ,string ,',stream
			       :start ,(or start 0)
			       :end ,(or end `(length ,string)))))
     ,@forms)
  #+lucid
  `(let ((.stream. (lcl:underlying-stream ,stream :output)))
     (macrolet ((put-char (char)
		  `(lcl:fast-write-char ,char .stream.))
		(put-string (string &optional start end)
		  `(lcl:fast-write-string ,string .stream. 
					  :start ,(or start 0)
					  :end ,(or end `(length ,string)))))
       ,@forms)))

(defun emit-output-line (&optional trailer newline-p (new-indent 0)
				   keep-p)
  (let* ((output-buffer (or *output-buffer*
			    (error "not inside with-output-stream")))
	 (line (output-buffer-line output-buffer))
	 (stream (output-buffer-stream output-buffer))
	 (buffer (output-buffer-buffer output-buffer))
	 (indent (output-line-indent line))
	 (start (output-line-start line))
	 (length (output-line-length line))
	 (end (+ start length))
	 (buffer-size (output-buffer-size output-buffer))
	 (new-buffer-length (- (output-buffer-length output-buffer)
			       length)))
    (declare (type simple-string buffer)
	     (type (unsigned-byte 15) indent start length end
		   buffer-size new-buffer-length))
    (with-fast-output stream
      (unless keep-p (emit-and-split-finish))
      (when (plusp indent)
	(multiple-value-bind (tabs spaces)
	    (floor indent 8)
	  (declare (fixnum tabs spaces))
	  (dotimes (i tabs) (put-char #\tab))
	  (dotimes (i spaces) (put-char #\space))))
      (when (plusp length)
	(if (> end buffer-size)
	    (let ((end (- end buffer-size)))
	      (declare (type (unsigned-byte 15) end))
	      (put-string buffer start buffer-size)
	      (put-string buffer 0 end))
	    (put-string buffer start end)))
      (when trailer
	(put-string trailer))
      (when newline-p
	(put-char #\newline))
      (setf (output-line-indent line) new-indent)
      (setf (output-line-length line) 0)
      (setf (output-line-next-split-scan line) 0)
      (setf (output-line-prev line) nil)
      (unless keep-p
	(setf (output-line-start line) 0)
	(setf (output-buffer-start output-buffer) 0))
      (setf (output-buffer-length output-buffer) new-buffer-length)
      line)))

(defmacro with-emit-and-split-string (trailer &body forms)
  `(progn
     (emit-and-split-start ,trailer)
     ,@forms))

(defun emit-and-split-string (string &optional trailer)
  (with-emit-and-split-string trailer
    (dotimes (i (length string))
      (emit-char (char string i)))))

;;; Emit and split an expression.  Try to split at a comma, ?, :, or space,
;;; or if that's not possible at an open paren.  The idea is to set
;;; last-split-pos to the last line break position before the margin or
;;; the first afterward.  If there is leftover text, then recurse to
;;; take care of it.
;;; Don't line break between open parens because it looks ugly.
;;; Don't line break between a (potential) identifier and the open paren.
;;; If the identifier is a macro call, doing so would confuse the C
;;; preprocessor.  If the identifier names a function, it simply looks ugly.
;;; *** Note that indirect function calls can still get a line break inserted
;;; *** between the function reference and the open paren enclosing the args.
;;; Don't line break between ! and an open paren because it looks ugly.

;;  If the output within with-emit-and-split-string can be printed
;;before margin, then don't split at all.
;;  Otherwise, we want to split at the rightmost good split position
;;before margin1, if there is one; otherwise at the first good split position
;;appearing at or after margin1.
;;  If with-emit-and-split-string begins after the wrap margin, then
;;the first character is a good split position.  
;;  Good split positions can't appear within strings or 
;;after an escape character and the character following it.  
;;  The position after one of (#\, #\? #\: #\space) is a good split position.  
;;  If no other good split positions can be found, 
;;we are allowed to split at any open parenthesis that does not follow 
;;any of (#\! #\( #\_ alphanumeric-char), provided it is not the 
;;first character printed within the with-emit-and-split-string.

;;There are three events that might result in a call to emit-split here:
;;  reaching margin1 
;;    (when we are not doing the first line, and eass-split-column is set),
;;  reaching margin
;;    (when we are doing the first line, and eass-split-column is set), and
;;  finding a split position
;;    (when we have reached margin1 (or margin, for the first line)).

;;If we reach margin1, and are doing the first line, we can't actually do
;;the split until we reach margin; and we have to record any split positions
;;that follow the one for the first line in a separate variable.

(defun emit-and-split-fits-on-one-line-p ()
  (let* ((output-buffer (or *output-buffer*
			    (error "not inside with-output-stream")))
	 (margin (output-buffer-margin output-buffer)))
    (and (output-buffer-first-line-p output-buffer)
	 (> margin (current-column--one-line)))))

(defun emit-and-split-start (trailer)
  (let* ((output-buffer (or *output-buffer*
			    (error "not inside with-output-stream")))
	 (margin *margin-column*)
	 (line (output-buffer-line output-buffer)))
    (when (output-buffer-emit-and-split-p output-buffer)
      (error "Already within with-emit-and-split"))
    (setf (output-buffer-emit-and-split-p output-buffer) t)
    (setf (output-buffer-trailer output-buffer) trailer)
    (setf (output-buffer-margin output-buffer) margin)
    (setf (output-buffer-margin1 output-buffer) 
	  (- (if trailer
		 (- *margin-column* (length trailer))
		 *margin-column*)
	     *indent-delta*))
    (setf (output-line-next-split-scan line)
	  (output-line-length line))
    (setf (output-line-prev line) nil)
    (setf (output-buffer-first-line-p output-buffer) t)))

(defun emit-and-split-finish ()
  (let* ((output-buffer (or *output-buffer*
			    (error "not inside with-output-stream"))))
    (when (output-buffer-emit-and-split-p output-buffer)
      (setf (output-buffer-emit-and-split-p output-buffer) nil)
      (setf (output-buffer-trailer output-buffer) nil)
      (setf (output-buffer-first-line-p output-buffer) t))))

(defun update-split-column (last-column)
  (let* ((output-buffer (or *output-buffer*
			    (error "not inside with-output-stream")))
	 (buffer (output-buffer-buffer output-buffer))
	 (line (output-buffer-line output-buffer))
	 (size (output-buffer-size output-buffer))
	 (margin1 (output-buffer-margin1 output-buffer))
	 (line-start (output-line-start line))
	 (indent (output-line-indent line))
	 (split-column nil)
	 (allow-paren-split-p t)
	 (i (output-line-next-split-scan line))
	 (prev (output-line-prev line))
	 (in-string-p nil)
	 (skip-next-p nil)
	 (first-p (zerop i))
	 (pos (+ line-start i)))
    (when (>= pos size) (setq pos (- pos size)))
    (when (and first-p
	       (output-buffer-first-line-p output-buffer)
	       (> (+ i indent) (+ *indent-column* (* *indent-delta* 2))))
      (setq split-column (+ i indent))
      (setq allow-paren-split-p nil))
    (loop (let ((char (schar buffer pos))
		(column (+ i indent)))
	    (if in-string-p
		(if skip-next-p
		    (setq skip-next-p nil)
		    (if (or (eql char #\") (eql char #\'))
			(when (eql in-string-p char)
			  (setq in-string-p nil))
			(when (eql char #\\)
			  (setq skip-next-p t))))
		(progn
		  (when (or (when (member prev '(#\, #\? #\: #\space))
			      (setq allow-paren-split-p nil)
			      t)
			    (and (eql char #\()
				 allow-paren-split-p
				 prev
				 (not (member prev '(#\! #\( #\_)))
				 (not (alphanumericp prev))))
		    (setq split-column column))
		  (when (or (eql char #\") (eql char #\'))
		    (setq in-string-p char))))
	    (setq prev char)
	    (incf i)
	    (when (or (= column last-column)
		      (and split-column 
			   (>= column margin1)))
	      (return nil))
	    (incf pos) (when (>= pos size) (setq pos (- pos size)))))
    (setf (output-line-next-split-scan line) i)
    (setf (output-line-prev line) prev)
    (when split-column
      (let* ((split-length (- split-column indent))
	     (new-length (- (output-line-length line) split-length))
	     (new-start (+ line-start split-length)))
	(when (>= new-start size) (setq new-start (- new-start size)))
	(setf (output-line-length line) split-length)
	(emit-newline-indent 8 (output-buffer-trailer output-buffer) t)
	(setf (output-buffer-start output-buffer) new-start)
	(setf (output-buffer-first-line-p output-buffer) nil)
	(setf (output-line-start line) new-start
	      (output-line-length line) new-length)))))

(defmacro emit-char-body (length index-var char-form)
  `(when (plusp ,length)
     (let* ((output-buffer (or *output-buffer*
			       (error "not inside with-output-stream")))
	    (buffer (output-buffer-buffer output-buffer))
	    (line (output-buffer-line output-buffer))
	    (size (output-buffer-size output-buffer))
	    (b-start (output-buffer-start output-buffer))
	    (b-length (output-buffer-length output-buffer))
	    (new-line-length (+ ,length (output-line-length line)))
	    (new-b-length (+ ,length b-length)))
       (declare (fixnum size b-start b-length new-line-length new-b-length)
		(simple-string buffer))
       (when (> new-b-length size)
	 (let* ((new-size (+ new-b-length 10))
		(new-buffer (make-string new-size))
		(j (output-buffer-start output-buffer)))
	   (declare (fixnum new-size j)
		    (simple-string new-buffer))
	   (dotimes (i b-length)
	     (declare (fixnum i))
	     (setf (schar new-buffer i) (schar buffer j))
	     (incf j)
	     (when (>= j size) (setq j 0)))
	   (setf (output-buffer-buffer output-buffer) 
		 (setq buffer new-buffer))
	   (setf (output-buffer-size output-buffer)
		 (setq size new-size))
	   (setf (output-buffer-start output-buffer) 0)
	   (setq b-start 0)
	   (setf (output-line-start line) 0)))
       (let ((pos (+ b-start b-length)))
	 (declare (fixnum pos))
	 (when (>= pos size)
	   (setq pos (- pos size)))
	 ,(if index-var
	      `(dotimes (,index-var ,length)
		 (declare (fixnum ,index-var))
		 (setf (schar buffer pos) ,char-form)
		 (incf pos)
		 (when (= pos size) (setq pos 0)))
	      `(setf (schar buffer pos) ,char-form))
	 (setf (output-line-length line) new-line-length)
	 (setf (output-buffer-length output-buffer) new-b-length)
	 (when (output-buffer-emit-and-split-p output-buffer)
	   (let* ((column (+ (output-line-indent line) 
			     (output-line-length line) -1))
		  (limit (output-buffer-margin output-buffer)))
	     (when (>= column limit)
	       (update-split-column column))))))))
  
(defun emit-char (char)
  (emit-char-body 1 nil char))

(defun emit-string (string &optional (start 0) (end (length string)))
  (setq string (string string))
  (let ((length (- end start)))
    (emit-char-body length i (char string (+ i start)))))

(defun emit-char-sequence (string &optional (start 0) (end (length string)))
  (let ((length (- end start)))
    (emit-char-body length i (elt string (+ i start)))))

(defmacro emit-integer (integer)
  `(emit-char-sequence (integer-to-char-list ,integer)))

(defun emit-simple (object)
  (typecase object
    (string (emit-string object))
    (character (emit-char object))
    (integer (emit-integer object))
    (list 
     (if (dolist (c object t)
	   (unless (characterp c) (return nil)))
	 (emit-char-sequence object)
	 (mapc #'emit-simple object)))
    (t (error "~S is not a character, string, integer, or list of characters" object))))

(defun emit-list (list &optional delimiter)
  (when list
    (emit-simple (car list))
    (dolist (e (cdr list))
      (when delimiter (emit-simple delimiter))
      (emit-simple e))))

(defun emit-to-column (column)
  ;; Tab over to column; emit at least 2 spaces
  (let* ((current-column (current-column))
	 (length (- (max column (+ current-column 2))
		    current-column)))
    (emit-char-body length i #\Space)))

(defmacro emit-format (format &rest args)
  (let ((forms nil)
	(characters nil)
	(if-info nil)
	(i 0)
	(unsupplied-arg '(unsupplied-arg))
	(limit (length format)))
    (labels ((do-immediate ()
	       (when characters
		 (push (if (cdr characters)
			   `(emit-string ,(coerce (nreverse characters) 
						  'string))
			   `(emit-char ,(car characters)))
		       forms)
		 (setq characters nil)))
	     (format-form ()
	       `(progn ,@(prog1 (nreverse forms)
			   (setq forms nil)))))
      (loop (when (>= i limit) (return nil))
	    (let ((char (aref format i)))
	      (incf i)
	      (if (not (eql #\~ char))
		  (push char characters)
		  (let ((atsign-seen-p nil)
			(colon-seen-p nil)
			(directive-args nil)
			(c nil))
		    (do-immediate)
		    (loop (case (setq c (and (< i limit)
					     (char-upcase (aref format i))))
			    (#\: (when atsign-seen-p
				   (error ": must precede @"))
				 (setq colon-seen-p t))
			    (#\@ (setq atsign-seen-p t))
			    (#\, (push unsupplied-arg directive-args))
			    ((#\V #\v)
			     (push (pop args) directive-args)
			     (let ((next (1+ i)))
			       (when (char= #\, (aref format next))
				 (setq i next))))
			    (#\'
			     (incf i)
			     (push (and (< i limit) (aref format i))
				   directive-args)
			     (let ((next (1+ i)))
			       (when (char= #\, (aref format next))
				 (setq i next))))
			    (t (if (digit-char-p c)
				   (multiple-value-bind (arg next)
				       (parse-integer format
						      :start i
						      :junk-allowed t)
				     (push arg directive-args)
				     (setq i (if (and (< next limit)
						      (char= (aref format next)
							     #\,))
						 next
						 (1- next))))
				   (return nil))))
			  (incf i))
		    (setq directive-args (nreverse directive-args))
		    (case c
		      (#\newline
		       (when atsign-seen-p
			 (push `(emit-newline) forms))
		       (unless colon-seen-p
			 (loop (when (or (>= i limit)
					 (let ((c (aref format i)))
					   (not (or (eql c #\space)
						    (eql c #\tab)))))
				 (return nil))
			       (incf i))
			 (decf i)))
		      (#\[ (when (or (null colon-seen-p) atsign-seen-p)
			     (error "emit-format error"))
			   (push (list forms args nil) if-info)
			   (setq args (cdr args))
			   (setq forms nil))
		      (#\; (let ((info (car if-info)))
			     (push (format-form) (third info))
			     (setq args (cdr (second info)))))
		      (#\* (pop args))
		      (#\] (let ((info (pop if-info)))
			     (push (format-form) (third info))
			     (setq forms `((if ,(car (second info))
					       ,@(third info))
					   ,@(first info)))))
		      (#\% (push `(emit-newline) forms))
		      (#\A (let ((delimiter
				  (when atsign-seen-p
				    (let ((darg (or (pop directive-args)
						    unsupplied-arg)))
				      (if (eq darg unsupplied-arg)
					  (pop args)
					  darg))))
				 (arg (pop args)))
			   (push (if atsign-seen-p
				     `(emit-list ,arg 
						 ,@(when delimiter `(,delimiter)))
				     `(emit-simple ,arg))
				 forms)))
		      (#\D (push `(emit-integer ,(pop args)) forms))
		      (#\E (let ((precedence
				  (if colon-seen-p
				      (pop args)
				      (let ((darg (or (pop directive-args)
						      unsupplied-arg)))
					(if (eq darg unsupplied-arg)
					    'expression-precedence
					    darg))))
				 (delimiter
				  (when atsign-seen-p
				    (let ((darg (or (pop directive-args)
						    unsupplied-arg)))
					(if (eq darg unsupplied-arg)
					    (pop args)
					    darg))))
				 (arg (pop args)))
			     (push `(,(if atsign-seen-p 
					  'emit-expressions
					  'emit-expression)
				      ,arg
				      ,precedence
				      ,@(when delimiter `(,delimiter)))
				   forms)))				 
		      (t (error "emit-format: char ~S" (aref format i))))
		    (incf i)))))
      (do-immediate)
      (format-form))))

(defun integer-to-char-list (num)
  (unless (integerp num)
    (error "~S is not an integer" num))
  (let ((digits nil)
	(minusp (minusp num)))
    (when minusp
      (setq num (- num)))
    (if (zerop num)
	(push #\0 digits)
	(loop (multiple-value-bind (quotient divisor)
		  (floor num 10)
		(push (digit-char divisor) digits)
		(when (zerop quotient)
		  (return nil))
		(setq num quotient))))
    (when minusp
      (push #\- digits))
    digits))

;;; Emit a documentation string, doing appropriate fiddling with embedded
;;; newlines.

(defun emit-documentation (string)
  (emit-comments string))

(defun fiddle-newlines (string)
  (declare (type string string))
  (let ((results  nil)
	(next     nil)
	(start    0)
	(end      (length string)))
    (declare (fixnum start end))
    (loop
     (cond ((>= start end)
	    (return nil))
	   ((setq next (position #\newline string :start start))
	    (push (subseq string start next) results)
	    (setq start (1+ next)))
	   ((eql start 0)
	    (push string results)
	    (return nil))
	   (t
	    (push (subseq string start end) results)
	    (return nil))))
    (nreverse results)))


;;; Emit a top-level comment

(defun emit-toplevel-comments (strings)
  (emit-newline)
  (emit-comments strings))


;;; Helper function for both of the above.  Format each line of the
;;; comment nicely.  If it is a single-line comment, just wrap it with
;;; "/* ... */".  Otherwise start each line of a multiline comment
;;; with an asterisk and put the close comment delimiter on its own line.
;;; Also keep an eye out for embedded "*/" substrings in the comment.

(defun emit-comments (strings &optional (newline-p t))
  (when strings
    (unless (listp strings)
      (setq strings (fiddle-newlines strings)))
    (let ((multiline  nil)
	  (offset (if newline-p 0 (- (current-column) *indent-column*))))
      (when newline-p
	(emit-newline-indent))
      (emit-string "/* ")
      (emit-string (munge-comment (car strings)))
      (dolist (s (cdr strings))
	(setq multiline t)
	(emit-newline-indent offset)
	(emit-string " * ")
	(emit-string (munge-comment s)))
      (if multiline
	  (emit-newline-indent offset))
      (emit-string " */"))))


;;; Maximum comment length; provided for the benefit of C compilers
;;; which can't handle long comments.

(defparameter *truncate-comments* 240)


(defun munge-comment (string &optional (start 0))
  (declare (type string string) (type fixnum start))
  (when (and *truncate-comments*
	     (> (length string) *truncate-comments*))
    (setq string (subseq string 0 *truncate-comments*)))
  ;; "\244\245" is a legal C string, but the accompanying comment
  ;; isn't.  Mask off high bits.
  ;; This should also solve the Symbolics problem with fonts in comments.
  (dotimes (index (length string))
    (unless (standard-char-p (char string index))
      (setf (char string index) #\?)))
  (let ((index  (search "*/" string :start2 start)))
    (if index
	(progn
	  (setf (char string index) #\?)
	  (munge-comment string (+ start 2)))
	string)))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Interface to name mapper
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; Note that functions for declaring globally defined names live in
;;; declare.lisp.

;;; Declare variables to keep track of locally defined names.

(defvar *local-labels* nil)


;;; Get the name of a local function.
;;; All of the hair with define-c-function-name-generator is for
;;; dealing with function names that are lists.

(defvar *c-function-name-generators* (make-hash-table :test 'eq))

(defun c-function-name-generator (key)
  (or (gethash key *c-function-name-generators*)
      (error "No method for generating function names for ~S." key)))

(defmacro define-c-function-name-generator (name lambda-list &body body)
  ;(progn (print "dcne")(print name))
  (check-type name symbol)
  (let ((dname (intern (sformat "~A-~A" name 
			       'c-function-name-generator))))
    `(progn
       (defun ,dname ,lambda-list ,@body)
       (setf (gethash ',name *c-function-name-generators*)
	     #',dname))))

(defun c-function-name-generator--symbol (name prefix)
  (multiple-value-bind (string case)
      (string-canonicalize-case (string-trim-stars name))
    (values (string->legal-c-name string case prefix)
	    prefix
	    ""
	    case
	    name)))

(defvar *local-function-prefix* "")

(defun generate-local-function-name-aux (name)
  (funcall (etypecase name
	     (symbol #'c-function-name-generator--symbol)
	     (cons (c-function-name-generator (car name))))
	   name
	   *local-function-prefix*))

(define-c-function-name-generator SETF (name prefix)
  (check-type name (satisfies setf-function-name-p))
  (c-function-name-generator--symbol (second name)
				     (sformat "~ASETF_" prefix)))

(defun generate-local-function-name (record)
  (set-function-record-unique-name
    record
    (multiple-value-bind (string prefix suffix case name)
	(generate-local-function-name-aux (function-record-name record))
      ;; Note that specifying these names as local is dependent on the
      ;; proper order of processing done by emit-function-definition-aux
      ;; and emit-function-header, which ensure that the mapped names of
      ;; functions are generated outside the per-function binding of
      ;; *local-names*, so that the names of local functions are added to
      ;; the per-file binding of *local-names*.
      (string->c-name string nil
		      :case case
		      :symbol name
		      :prefix prefix
		      :suffix suffix))))

(defun generate-local-function-prefix (name)
  (multiple-value-bind (string prefix)
      (generate-local-function-name-aux name)
    (sformat "~A~A_" prefix string)))

;;; Generate the name of a local variable.

(defun generate-local-variable-name (record &optional case)
  ;; If CASE is specified, the string is assumed to be already
  ;; "canonicalized."
  (or (variable-record-unique-name record)
      (let ((name (variable-record-name record))
	    string)
	(if (null case)
	    (multiple-value-setq (string case)
	      (let ((tutil::using-translator-symbol-names-p nil))
		(string-canonicalize-case (string-trim-stars name))))
	    (setq string name))
	(setf (variable-record-unique-name record)
	      (string->c-name string nil
			      :case case
			      :symbol (and (symbolp name) name))))))

(defun generate-static-variable-name (record)
  ;; Generate a lower-case temp name based on "unique name"
  (or (variable-record-static-variable-name record)
      (multiple-value-bind (string case)
	  (string-canonicalize-case (variable-record-unique-name record))
	(setf (variable-record-static-variable-name record)
	      (string->c-name string nil :case case)))))

(defun generate-initcode-closed-variable-names (records)
  (dolist (record records)
    (when (variable-record-closed-p record)
      (generate-local-variable-name record))))

;;; Generate names for constants.

(defun generate-local-constant-name (constant)  ;; not a record
  (generate-local-variable-name (extract-constant-record constant)))

(defun assign-global-constant-name (constant)   ;; not a record
  (let ((record (extract-constant-record constant)))
    (unless (variable-record-unique-name record)
      (generate-local-variable-name record))))


;;; Find the name of a label (for a goto).
;;; Note that the code generator for tagbody maps all tagbody tags into 
;;; uninterned symbols.
;;; *** The use of uninterned symbols was an artifact of problems with
;;; *** the name mapper.  Probably just strings could be used now.
;;; This is no longer true. The initializer for labeled statements
;;; requires that the label be a symbol, so it can hang the
;;; labeled statement on the plist---ARL 11/6/91

(defun find-name-of-label (label)
  (cond ((eq label :default)
	 "default")
	((integerp label)
	 (sformat "case ~d" label))
	((characterp label)
	 (sformat "case ~a" (format-c-char label)))
	(t
	 (find-name-of-label-aux label))))

(defun find-name-of-label-aux (symbol)
  (or (cdr (assoc symbol *local-labels*))
      (multiple-value-bind (string case)
	  (string-canonicalize-case (string-trim-stars symbol))
	(setf string (string->c-name string nil
				     :case case
				     :symbol symbol))
	(push (cons symbol string) *local-labels*)
	string)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    File header and trailer
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; Emit the file header.  This is just a little blurb at the top of
;;; the file to identify it and include all the necessary files.

(defun this-year ()
  (multiple-value-bind (second minute hour date month year)
      (get-decoded-time)
    (declare (ignore second minute hour date month))
    year))

(defun date-and-time-string ()
  (multiple-value-bind (second minute hour date month year)
      (get-decoded-time)
    (format nil "~2,'0d ~a ~d  ~2,'0d:~2,'0d:~2,'0d"
	    date
	    (nth (1- month)
		 '("Jan" "Feb" "Mar" "Apr" "May" "Jun"
		   "Jul" "Aug" "Sep" "Oct" "Nov" "Dec"))
	    year
	    hour
	    minute
	    second)))



(defparameter *copyright-notice*
  (sformat
	  "Copyright (C) ~D Chestnut Software, Inc.  All Rights Reserved."
	  (this-year)))

; *** do the same thing in dump; grep for '#include'.

(defun emit-file-header (input-filename output-filename &optional (include-statement-p t) (note ""))
  (emit-string
   (format nil "/* ~a~
              ~% * Input file:  ~a~a~
           ~@[~% * Translated on ~a~]~
              ~% * ~a~
              ~% */~%~
           ~@[~%~{~A~%~}~]"
	       (file-namestring output-filename)
	       (file-namestring input-filename)
	       note
	       (and *include-dates-in-headers* (date-and-time-string))
	       *copyright-notice*
	       (and include-statement-p *header-lines*)
	       )))

(defun emit-file-trailer ()
  (emit-newline))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Emit global variable definitions
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun emit-variables (variables)
  (mapc #'emit-variable variables))

(defun emit-variable (symbol)
  (let ((redefinition-record (variable-redefinition-record symbol))
	#+translator-supports-thread
	(constant-p (variable-descriptor-constant-p
			(defined-as-variable symbol)))
	#+translator-supports-thread
	(global-p (cdr (assoc 'tx:global-variable
			      (variable-proclamations symbol)))))
    (when (redefinition-record-definition-needs-dumping redefinition-record)
      (emit-newline)
      (let ((doc (variable-descriptor-documentation
		     (defined-as-variable symbol))))
	(when doc
	  (emit-documentation doc)))
      (emit-newline)

      #-translator-supports-thread
      (emit-format "Object ~a = UNBOUND;" (c-name-of-global-variable symbol))
      #+translator-supports-thread
      (if (or constant-p global-p)
	(emit-format "Object ~a = UNBOUND;"
		     (c-name-of-global-variable symbol))
	(emit-format "DEFINE_VARIABLE_WITH_SYMBOL(~a, ~a);"
		     (c-name-of-global-variable symbol)
		     (c-name-of-quoted-symbol symbol)))

      (redefinition-record-note-definition-dumped redefinition-record))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Emit function definitions
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; Emit definitions of functions.

(defun emit-function (record)
  (let ((classification (function-record-classification record)))
    (ecase classification
      ((:global :bound-global :callable :global-dllexport :callable-dllexport) 
       (emit-function-definition-aux record classification nil))
      (:local
       (emit-function-definition-aux record nil nil))
      #+translator-supports-clos
      (:generic-function
       (emit-generic-function-definition record))
      (:init
       (emit-function-definition-aux record nil t)))))

;;; Emit a function entry for a generic function, if needed.

#+translator-supports-clos
(defun emit-generic-function-definition (record)
  (when (function-record-variadic-p record)
    ;; Only variadic generic functions need an entry defined here.
    ;; Non-variadic functions are defined as macros in a .h file.
    (let* ((name (function-record-name record))
	   (entry (c-name-of-function-entry name))
	   (object (c-name-of-function-object name))
	   (constants (function-record-constants record)))
      (let ((doc (function-record-documentation record)))
	(emit-newline)
	(when doc (emit-documentation doc)))
      (mapc #'assign-global-constant-name constants)
      (mapc #'emit-global-constant-definition constants)
      (emit-newline)
      (emit-newline)
      (with-emit-and-split-string nil
	(emit-format "DEFINE_VARIADIC_GENERIC_FUNCTION(~A,~A)"
		     entry object)))
    (clear-function-record record)))

;;; Emit nested functions bottom-up.

(defvar *function-being-emitted* nil)

(defun emit-function-definition-aux (record global-p init-p)
  ;; Generate names for all the stuff with external or per-file scope.
  (generate-function-record-per-file-names record global-p init-p)
  (with-c-name-table :top-level-function
    ;; Map all closed variables first!
    (generate-external-variable-names record)
    (emit-function-definition-internal record global-p init-p)))

;;; All external variables must be named before doing local processing of the
;;; function and its nested functions, so that name conflicts with closed
;;; variables will cause local variables to be mapped to other names.  This
;;; must be done before (and be inherited by) per-function naming, because
;;; each closed variable is given a single name whose scope is effectively
;;; "leaf toplevel form".  This has the perhaps unfortunate side effect that
;;; nested functions that don't refer to a given closed variable still have
;;; that variable's name in their mapping table.

(defun generate-external-variable-names (record &optional do-unclosed-only-p)
  (dolist (vr (function-record-external-variables record) nil)
    (unless (and do-unclosed-only-p
		 (variable-record-closed-p vr))
      (generate-local-variable-name vr)))
  (dolist (nf (function-record-nested-functions record))
    (generate-external-variable-names nf do-unclosed-only-p)))

(defun generate-function-record-per-file-names (record global-p init-p)
  (macrolet ((with-prefix (record &body body)
	       `(let ((*function-being-emitted* ,record)
		      (*local-function-prefix*
		        (if *function-being-emitted*
			    (generate-local-function-prefix
			      (function-record-name *function-being-emitted*))
			    "")))
		  ,@body)))
    (labels ((generate-function-names (record)
	       (with-prefix record
		 (generate-local-function-name record)
		 (mapc #'generate-function-names
		       (function-record-nested-functions record))))
	     (generate-constant-names (record)
	       (mapc #'assign-global-constant-name
		     (function-record-constants record))
	       (generate-external-variable-names record t)
	       (mapc #'generate-constant-names
		     (function-record-nested-functions record))))
      (with-prefix record
	(if (or global-p init-p)
	    (set-function-record-unique-name
	      record
	      (c-name-of-function-entry (function-record-name record)))
	    (generate-local-function-name record))
	(unless init-p
	  ;; These have already been assigned names by the time the file's
	  ;; initfunction gets processed.
	  (mapc #'generate-function-names
		(function-record-nested-functions record)))
	(generate-constant-names record)))))

(defvar *sets-values-count-p* t)

(defvar *saved-stack-p* nil)
(defvar *protecting-variables-p* nil)
(defvar *protected-variables* nil)

(defun need-to-unprotect ()
  *protecting-variables-p*)

(defun need-to-pop-stack ()
  *saved-stack-p*)

(defvar *unbound* (make-symbol "UNBOUND"))

(defvar *might-save-stack-p* nil)

(defun might-need-to-pop-stack ()
  (or *saved-stack-p* *might-save-stack-p*))

(defun emit-function-definition-internal (record global-p init-p)
  (unless init-p
    (dolist (f (function-record-nested-functions record))
      (emit-function-definition-internal f nil nil)))
  (dolist (constant (function-record-constants record))
    (unless (and init-p 
		 (null (variable-record-initializer 
			(extract-constant-record constant))))
      (emit-global-constant-definition constant)))
  (dolist (variable (function-record-external-variables record))
    (unless (variable-record-closed-p variable)
      (when (eq (translator-foreign-type :object)
		(variable-record-foreign-type variable))
	(setf (variable-record-initializer variable) *unbound*))
      (emit-global-variable-definition variable)))
  (let* ((*function-being-emitted* record)
	 (*sets-values-count-p*
	  (not (function-record-returns-one-value-p record)))
	 (*saved-stack-p* nil)
	 (*might-save-stack-p* nil)
	 (*protecting-variables-p* nil)
	 (*protected-variables* nil))
    (with-c-name-table :function
      ;; Generate local name assignments.
      (generate-function-record-names record global-p init-p)
      (emit-function-header record global-p init-p)
      (emit-function-body record)
      (emit-function-trailer record global-p init-p)))
  (clear-function-record record init-p))

(defun emit-global-variable-definition (record)
  (unless (variable-record-constant-declaration-emitted-p record)
    (push record *global-constants-emitted*)
    (emit-global-constant-declaration record)))

;;; external variables have already been named by this point.
(defun generate-function-record-names (record global-p init-p)
  (declare (ignore global-p))
  (mapc #'generate-local-variable-name
	(function-record-argument-variables record))
  (mapc #'generate-local-variable-name
	(function-record-local-variables record))
  (when init-p
    (mapc #'generate-local-constant-name
	  (function-record-constants record))))

;returns 3 values: main-type-string, prefix-string, postfix-string.
(defun parse-c-type (type)
  (let ((c-type (c-type type)))
    (if (eq c-type :none)
	(values "Bad_C_Type" "" "")
	(let ((*-index (position #\* c-type)))
	  (if *-index
	      (let ((split (if (char= #\space (aref c-type (1- *-index)))
			       (1- *-index)
			       (error "Can't parse this type: ~
                                       fix parse-c-type"))))
		(values (subseq c-type 0 split)
			(subseq c-type *-index)
			""))
	      (values c-type "" ""))))))


(defvar *name-marker* (make-symbol "NAME-MARKER"))

(defun emit-type-declaration (type)
  (unless type
    (setq type :object))
  (let* ((c-type-name (c-type-for-foreign-type type *name-marker*))
	 (marker-position (position *name-marker* c-type-name))
	 (main-type (car c-type-name))
	 (prefix (subseq c-type-name 2 marker-position)) ; skip #\space
	 (postfix (subseq c-type-name (1+ marker-position))))
    (emit-string main-type)
    (emit-string " ")
    (values prefix postfix)))

(defun emit-single-type-declaration (type name &key 
					  indent-p storage-class initializer)
  (let* ((foreign-type (or type :object))
	 (c-type (c-type-for-foreign-type foreign-type name))
	 (*indent-column* (if indent-p *indent-column* 0))
	 (new-p nil))
    (emit-newline-indent)
    (when storage-class (emit-string storage-class) (emit-char #\space))
    (dolist (c c-type)
      (when (eql c #\})
	(decf *indent-column* *indent-delta*))
      (when new-p
	(emit-newline-indent))
      (emit-simple c)
      (setq new-p (case c
		    (#\{ (incf *indent-column* *indent-delta*) t)
		    (#\; t)
		    (t nil))))
    (when initializer
      (emit-string " = ")
      (emit-c-constant (c-constant-type-name foreign-type)
		       initializer))
    (emit-char #\;)))

;;; Emit the function header, including the argument and local
;;; variable declarations.

(defun emit-dllexport ()
  (emit-string "DLLEXPORT "))

#+translator-supports-thread
(defun remove-quoted-specials (constants)
  (remove-if #'(lambda (x)
		 (let ((object (second x)))
		   (and (symbolp object)
			(let ((desc (defined-as-variable object)))
			  (and desc
			       (variable-descriptor-special-p desc)
			       (not (variable-descriptor-constant-p desc)))))))
	     constants))

(defun emit-function-header (record global-p init-p)
  (let ((name (function-record-name record)))
    (if (and name (symbolp name) (symbol-package name))
	(emit-toplevel-comments (format nil "~S" name))
	(emit-newline)))
  (emit-newline)
  (let* ((variadic-p       (function-record-variadic-p record))
	 (lambda-list-info (function-record-lambda-list-info record))
	 (arguments        (function-record-argument-variables record))
	 (externals        (function-record-external-variables record))
	 (locals           (function-record-local-variables record))
	 (constants        (nreverse
			    (mapcar #'extract-constant-record
				    #+translator-supports-thread
				    (remove-quoted-specials (function-record-constants record))
				    #-translator-supports-thread
				    (function-record-constants record))))
	 (*indent-column*  *indent-delta*)
	 (*any-declarations-p* nil)
	 (with-protected-variables-p (and *using-with-protected-variables-p*
					  (not init-p))))
    (unless (or global-p init-p)
      (emit-string "static "))
    (when (or (eq global-p ':global-dllexport) (eq global-p ':callable-dllexport))
      (emit-dllexport))
    (let* ((type (if init-p
		     :void
		     (or (function-record-foreign-return-type record)
			 :object)))
	   (c-type-name (c-type-for-foreign-type `(:function () ,type)
						 *name-marker*))
	   (marker-position (position *name-marker* c-type-name))
	   (main-type-string (car c-type-name))
	   (prefix (subseq c-type-name 1 marker-position))
	   (postfix (subseq c-type-name (+ marker-position 3))))
      (emit-string main-type-string)
      (emit-simple prefix)
      (emit-string (function-record-unique-name record))
      (if variadic-p
	  (emit-string 
			(if postfix
			   " varargs_arglist_1(int, n)"
			   " varargs_1(int, n)"))
	  (with-emit-and-split-string nil
	    (emit-c-argument-list
	     (mapcar #'variable-record-unique-name arguments))))
      (emit-simple postfix)
      (cond (variadic-p
	     (when postfix
	       (emit-newline-indent)
	       (emit-string "varargs_declarations_1(int, n)"))
	     (emit-newline) (emit-string "{")
	     (emit-variable-declarations record 
					 arguments with-protected-variables-p))
	    (t
	     (emit-variable-declarations record arguments)
	     (setq *any-declarations-p* nil)
	     (emit-newline) (emit-string "{"))))
    (emit-variable-declarations record externals)
    (emit-variable-declarations record locals with-protected-variables-p)
    (when init-p (emit-local-constant-declarations record constants))
    (multiple-value-bind (protect protecti)
	(if with-protected-variables-p
	    (values nil nil)
	    (collect-protect record (if init-p constants nil)))
      (let ((non-simple-variadic-p
	     (and variadic-p
		  (or (not (function-record-nonrelocating-p record))
		      (lambda-list-info-restp lambda-list-info)
		      (lambda-list-info-keyp lambda-list-info)))))
	(emit-random-decls record variadic-p non-simple-variadic-p init-p
			   protect protecti)
	(emit-local-temp-declarations (function-record-local-temps record))
	(when *any-declarations-p* (emit-newline))
	(when (function-record-documentation record)
	  (emit-documentation (function-record-documentation record)))
	(when (stringp *enter-function-callback*)
	  (emit-newline-indent)
	  (emit-string *enter-function-callback*)
	  (emit-string "(")
	  (cond (*enter-function-use-file-index-p*
		 (emit-integer *enter-function-file-index*)
		 (emit-string ",")
		 (emit-integer (- *enter-function-index*
				  (or (car *enter-function-callback-file-data*)
				      0)))
		 (incf *enter-function-index*))
		(*enter-function-use-index-p*
		 (emit-integer *enter-function-index*)
		 (incf *enter-function-index*))
		(t
		 (emit-string (function-record-unique-name record))))
	  (emit-string ");")
	  (push (list (function-record-name record)
		      (function-record-unique-name record))		      
		*enter-function-callback-data*))
	(emit-closure-initializations externals
				      (function-record-closure-state record))
	(cond (non-simple-variadic-p
	       (emit-save-stack)
	       (emit-newline-indent) (emit-string "INIT_ARGS();")
	       (dolist (a arguments)
		 (emit-newline-indent)
		 (emit-string (variable-record-unique-name a))
		 (emit-string " = REQUIRED_ARG();"))
	       (emit-newline-indent) (emit-string "SAVE_ARGS();")
	       (emit-gc-protect protect protecti))
	      (t
	       (when variadic-p 
		 (emit-newline-indent)
		 (emit-string "INIT_ARGS_nonrelocating();")
		 (dolist (a arguments)
		   (emit-newline-indent)
		   (emit-string (variable-record-unique-name a))
		   (emit-string " = REQUIRED_ARG_nonrelocating();")))
	       (when (or (function-record-uses-stack-p record)
			 protect protecti)
		 (emit-save-stack)
		 (emit-gc-protect protect protecti))))
	(when init-p
	  (emit-global-gc-protect (nreverse *global-constants-emitted*)))))))

;;; Build the string representing the C argument list.

(defun emit-c-argument-list (names)
  (if (null names)
      (emit-string "()")
      (progn
	(emit-char #\()
	(emit-string (car names))
	(dolist (name (cdr names))
	  (emit-char #\,)
	  (emit-string name))
	(emit-char #\)))))

(defun format-delimited-list (items separator &optional stream)
  (if stream
      (format-delimited-list-aux stream items separator)
      (let ((string  (make-array 100
				 :element-type 'standard-char
				 :fill-pointer 0
				 :adjustable t)))
	(with-output-to-string (stream string)
	  (format-delimited-list-aux stream items separator))
	string)))

(defun format-delimited-list-aux (stream items separator)
  (write-string (car items) stream)
  (dolist (item (cdr items))
    (write-string separator stream)
    (write-string item stream)))


;;; Emit variable declarations.
(defun emit-variable-declarations (record variable-records &optional
					  maybe-initialize-p
					  constant-declarations-p)
  ;; Generate local variable declarations
  ;; Fit as many as possible per line, separated by commas
  (let ((first-p t)
	(variable-records
	 (sort (copy-list variable-records) #'string<
	       :key #'(lambda (vr)
			(c-type (variable-record-foreign-type vr)))))
	emitted-declarations-p
	current-type current-prefix current-postfix)
    (loop (unless variable-records
	    (when emitted-declarations-p
	      (emit-char #\;))
	    (return nil))
	  (let* ((v (pop variable-records))
		 (name (variable-record-unique-name v))
		 (variable-type 
		  (if (variable-needs-setjmp-protection v record)
		      `(:volatile ,(variable-record-foreign-type v))
		      (variable-record-foreign-type v)))
		 (initialize-p (and maybe-initialize-p
				    (eq variable-type
					(translator-foreign-type :object))
				    (variable-record-needs-gc-protection v))))
	    (unless (variable-record-constant-declaration-emitted-p v)
	      (cond
		((or first-p
		     (>= (+ (current-column) (length name)
			    (if initialize-p 12 2))
			 *margin-column*)
		     (not (eq variable-type current-type)))
		 (unless first-p
		   (emit-char #\;))
		 (emit-newline-indent)
		 (setq first-p nil)
		 (setq current-type variable-type)
		 (multiple-value-setq
		     (current-prefix current-postfix)
		   (emit-type-declaration variable-type)))
		(t (emit-string ", ")))
	      (emit-simple current-prefix)
	      (emit-string name)
	      (emit-simple current-postfix)
	      (when initialize-p
		(emit-string " = UNBOUND"))
	      (when constant-declarations-p
		(setf (variable-record-constant-declaration-emitted-p v) t))
	      (setq *any-declarations-p*   t
		    emitted-declarations-p t))))))

;;; Define the protocol for emitting declarations for local temps.
;;; Each set is identified by a keyword, which is used for dispatching.

(defvar *local-temp-emitters* (make-hash-table :test #'eq))

(defmacro local-temp-emitter (keyword)
  `(gethash ,keyword *local-temp-emitters*))

(defmacro define-local-temp-emitter (keyword lambda-list &body body)
  (let ((function-name
	 (intern (sformat "~a-TEMP-EMITTER" (symbol-name keyword)))))
    `(progn
       (defun ,function-name ,lambda-list ,@body)
       (setf (local-temp-emitter ',keyword) #',function-name)
       ',keyword)))

(defun emit-local-temp-declarations (keywords)
  ;; Make sure "result" declaration present if needed.
  ;; If code contains STORE-VALUE or STORE-VALUES, this has already
  ;; been done by code walker.
  ;; The only other case to worry about comes from RETURN-VALUES.
  (when (might-need-to-pop-stack)
    (pushnew 'trun:%store-value-temp-declaration keywords))
  (mapc #'emit-local-temp-declaration keywords))

(defun emit-local-temp-declaration (keyword)
  (let ((function  (local-temp-emitter keyword)))
    (if function
	(progn
	  (funcall function keyword)
	  (setq *any-declarations-p* t))
	(error "Unknown local temporary set keyword ~s." keyword))))


;;; Emit constant declarations.
;;; The things that are collected as "constants" by the gather phase
;;; are actually target language constructs that associate a variable
;;; record with a constant.

(defun extract-constant-record (c)
  (case (target-form-type c)
    (constant (third c))
    (load-time-value (fourth c))
    (t (error "Unrecognized target language construct ~s." c))))

(defun emit-local-constant-declarations (record variable-records)
  (emit-variable-declarations record variable-records nil t))

(defun emit-single-variable-declaration (record &key 
						storage-class 
						(indent-p t))
  (emit-single-type-declaration 
   (variable-record-foreign-type record)
   (variable-record-unique-name record)
   :storage-class storage-class
   :initializer (variable-record-initializer record)
   :indent-p indent-p)
  (setf (variable-record-constant-declaration-emitted-p record) t))

(defun emit-extern-constant-declaration (c)
  (emit-single-variable-declaration c :storage-class "extern"))

(defun emit-global-constant-declaration (c)
  (emit-single-variable-declaration c :storage-class "static"))

;;; Emit stuff to gc-protect all the local variables that need it.
;;; This is controlled by the needs-gc-protection slot of the variable
;;; record, but also all closed variables need to be protected regardless
;;; of the value of this slot.

(defun collect-protect (function constants &optional wpv-statement)
  ;; Returns 2 values:  protect; protect-and-initialize.
  ;; arguments, externals, and locals have already had their protection
  ;; requirements determined in the optimize phase; for constants,
  ;; we just look at the nonrelocating-type slot in the variable record.
  ;; The needs-gc-protection slot in a variable-record is either
  ;; t or nil (for an unclosed variable) or
  ;; a list of functions in which the variable must be protected
  ;; (for a closed-over variable).
  (let ((arguments (function-record-argument-variables function))
	(externals (function-record-external-variables function))
	(locals    (function-record-local-variables function))
	(current (or wpv-statement function))
	(protect nil)
	(protect-and-initialize nil))
    (when *rtl-includes-gc-p*
      (dolist (const constants)
	(unless (variable-record-nonrelocatable-type const)
	  (push const protect)))
      (macrolet ((push-if-needs-protection (vars list)
		   (let ((var (gensym)))
		     `(dolist (,var ,vars)
			(when (variable-needs-gc-protection ,var current)
			  (push ,var ,list))))))
	(push-if-needs-protection externals protect)
	(push-if-needs-protection arguments protect)
	(if wpv-statement
	    (push-if-needs-protection locals protect)
	    (push-if-needs-protection locals protect-and-initialize)))
      (values 
       (nreverse protect)
       (nreverse protect-and-initialize)))))

(defun emit-save-stack ()
  (emit-newline-indent)
  (emit-string "SAVE_STACK();")
  (setq *saved-stack-p* t))

(defun emit-gc-protect (variables ivariables)
  (when (or variables ivariables)
    (setq variables (set-difference variables *protected-variables*))
    (setq *protected-variables* (append variables *protected-variables*))
    (setq ivariables (set-difference ivariables *protected-variables*))
    (setq *protected-variables* (append ivariables *protected-variables*))
    (unless *saved-stack-p*
      (emit-save-stack))
    (when variables
      (emit-gc-protect-aux variables nil))
    (when ivariables
      (emit-gc-protect-aux ivariables t))
    (setq *protecting-variables-p* t)))

(defun emit-gc-protect-aux (variables initialize-p)
  (when (notevery #'(lambda (v)
		      (eq :object
			  (translator-foreign-type-name
			   (variable-record-foreign-type v))))
		  variables)
    (error "Non-Object variable ~A requires protection"
	   (find-if-not #'(lambda (v)
			    (eq :object
				(translator-foreign-type-name
				 (variable-record-foreign-type v))))
			variables)))
  ;; Emit PROTECT[I] statement(s)
  (let ((length  (length variables))
	(rest    nil))
    (when (> length 10)
      (setq length 10)
      (setq rest (nthcdr 10 variables))
      (setq variables (subseq variables 0 10)))
    (emit-newline-indent)
    (with-emit-and-split-string nil
      (emit-format "PROTECT~:[~;I~]_~d(~@a);"
		   initialize-p
		   length
		   ","
		   (mapcar #'variable-record-unique-name variables)))
    (when rest
      (emit-gc-protect-aux rest initialize-p))))


;;; Emit GC-protections for global constants that need it.  This is done
;;; using a somewhat different mechanism than for local constants; there's
;;; no need declare local protect frames here, for example.

(defun emit-global-gc-protect (records)
  (when *rtl-includes-gc-p*
    (dolist (r records)
      (unless (variable-record-nonrelocatable-type r)
	(emit-newline-indent)
	(emit-string "PROTECT_GLOBAL(")
	(emit-string (variable-record-unique-name r))
	(emit-string ");")))))


;;; Emit declarations for random stuff.  Variadic functions need
;;; more stuff declared than non-variadic functions.

(defun emit-random-decls (record variadic-p non-simple-variadic-p init-p
				 gc-protect gc-protecti)  
  (when variadic-p
    (emit-newline-indent)
    (emit-string (if non-simple-variadic-p
		     "Declare_varargs;"
		     "Declare_varargs_nonrelocating;"))
    (setq *any-declarations-p* t))
  (when (or (and *rtl-includes-gc-p*
		 (if (and *using-with-protected-variables-p* (not init-p))
		     (macrolet
			 ((gc-p (list)
			    `(some #'variable-record-needs-gc-protection
				   ,list)))
		       (or (gc-p (function-record-argument-variables record))
			   (gc-p (function-record-external-variables record))
			   (gc-p (function-record-local-variables record))))
		     (or gc-protect gc-protecti)))
	    (and variadic-p non-simple-variadic-p)
	    (function-record-uses-stack-p *function-being-emitted*))
    (emit-newline-indent)
    (emit-string "Declare_stack_pointer;")
    (setq *might-save-stack-p* t)
    (setq *any-declarations-p* t))
  (let ((n 0))
    (when (> (setq n (function-record-catchframe-count record)) 0)
      (emit-newline-indent)
      (emit-format "Declare_catch(~d);" n)
      (setq *any-declarations-p* t))
    (when (> (setq n (function-record-specialframe-count record)) 0)
      (emit-newline-indent)
      (emit-format "Declare_special(~d);" n)
      (setq *any-declarations-p* t))
    (when (> (setq n (function-record-areaframe-count record)) 0)
      (emit-newline-indent)
      (emit-format "XDeclare_area(~d);" n)
      (setq *any-declarations-p* t))
    (when (> (setq n (function-record-frontierframe-count record)) 0)
      (emit-newline-indent)
      (emit-format "XDeclare_frontier(~d);" n)
      (setq *any-declarations-p* t))))

;;; Emit statements to initialize pointers to closed-over variables.
;;;*** Maybe this can go in the gather phase directly?

(defun emit-closure-initializations (externals state)
  (dolist (v externals)
    (when (variable-record-closed-p v)
      (let ((p (position v state)))
	(emit-newline-indent)
	(if (closed-binding-used-here-p v)
	    (emit-format "~a = FIND_BINDING(~d);"
			 (variable-record-unique-name v) p)
	    (emit-format "~a = BINDING_OF(FIND_BINDING(~d));"
			 (variable-record-unique-name v) p))))))


;;; A helper function.  If we are only interested in the value of the
;;; closed-over external variable and not its binding, we can extract
;;; the value once at the top of the function instead of every time
;;; it is referenced.

;;; Replacement for incorrect definitions below.
(defun closed-binding-used-here-p (record)
  (declare (ignore record))
  t)

#| These definitions are incorrect -- see bug report.  kab, 9/7/91
(defun closed-binding-used-here-p (record)
    (or (member *function-being-emitted* (variable-record-modified-p record))
	(chained-by-other-closures-p
	    record
	    (function-record-nested-functions *function-being-emitted*))
	(chained-by-other-variables-p
	    record
	    (function-record-local-variables *function-being-emitted*))))

(defun chained-by-other-closures-p (record function-records)
    (dolist (f function-records nil)
	(if (eq record (car (function-record-closure-state f)))
	    (return t))))

(defun chained-by-other-variables-p (record variable-records)
    (dolist (v variable-records nil)
	(if (eq record (car (variable-record-closure-state v)))
	    (return t))))
|#
    

;;; Emit the function body statements.

(defun emit-function-body (record)
  (let ((*indent-column*  *indent-delta*)
	(*local-labels*   nil))
    (emit-statements (function-record-statements record))))
    
;;; Emit any trailing code for the function.

(defun emit-function-trailer (record global-p init-p)
  (declare (ignore record global-p))
  (when init-p
    (let ((*indent-column*  *indent-delta*))
      ;; WARNING: The order of these is important.
      (when (or (need-to-unprotect)
		(need-to-pop-stack))
	(emit-newline-indent)
	(emit-string "RESTORE_STACK();"))))
  (emit-newline)
  (emit-string "}"))


;;; Emit definitions for global constants.  Include a comment about
;;; the value of the constant.  Note that there might be duplicate entries
;;; for constants in the list, so keep track of the ones we've already
;;; emitted declarations for.

;;; These variables are used mostly for the benefit of C compilers
;;; which don't like comments whose names are too long.
;;; They are part of the external interface to the Translator.

(define-translator-parameter *constant-print-length* 5)
(define-translator-parameter *constant-print-level* 2)
(define-translator-parameter *constant-print-case* :downcase)


(defun emit-global-constant-definition (construct)
  (let ((record  (extract-constant-record construct))
	(object  (second construct)))
    (unless (or (null record)
		(variable-record-constant-declaration-emitted-p record)
		;; Don't generate definitions for quoted symbols whose master is special variable
		#+translator-supports-thread
		(and (symbolp object)
		     (let ((desc (defined-as-variable object)))
		       (and desc
			    (variable-descriptor-special-p desc)
			    (not (variable-descriptor-constant-p desc))))))
      (push record *global-constants-emitted*)
      (let ((comment
	     (let ((*print-length*  *constant-print-length*)
		   (*print-level*   *constant-print-level*)
		   (*print-case*    *constant-print-case*)
		   (*print-array* t))
	       (prin1-to-string object))))
	(emit-newline)
	(emit-global-constant-declaration record)
	(emit-to-column 35)
	(emit-comments comment nil)))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Emit statements
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;*** Kim suggests using destructuring-bind to dissect the target language.

;;; The idea here is that only statements are emitted directly.  Expressions
;;; are handled by building up a string which is then emitted as part of
;;; its enclosing statement.  

(defmacro define-statement-emitter (name lambda-list &body body)
  (let ((fname  (intern (sformat "EMIT-~a-FUNCTION" name))))
    `(progn
       (defun ,fname ,lambda-list ,@body)
       (setf (emit-statement-function ',name) #',fname)
       ',name)))

;;; This macro is used to flatten out unnecessary compound statements.

(defmacro with-compound-statement (in-compound-p &body body)
  `(progn
     (when (not ,in-compound-p)
       (emit-string " {"))
     ,@body
     (when (not ,in-compound-p)
       (emit-newline-indent (- *indent-delta*))
       (emit-string "}"))))

(defun emit-statement (s in-compound-p)
  (let ((fn (target-form-emit-statement-function s)))
    (if fn
	(prog1
	    (funcall fn s in-compound-p)
	  (maybe-deallocate-target-form s))
	(emit-expression-statement s))))

(defun emit-statements (list)
  (let ((labelp nil))
    (dolist (s list)
      (setq labelp nil)
      (loop (unless (eq (target-form-type s) 'labeled-statement)
	      (return nil))
	    (emit-label s)
	    (setq s (caddr s))
	    (when (null-statement-p s)
	      (setq labelp t)))
      (unless labelp
	(emit-statement s t)))
    (when labelp
      (emit-char #\;))))

(defun null-statement-p (s)
  (or (null s)
      (case (target-form-type s)
	(null-statement 
	 t)
	(compound-statement
	 (every #'null-statement-p (cdr s)))
	(with-lexical-bindings 
	 (and (notany #'variable-record-closed-p (cadr s))
	      (every #'null-statement-p (cddr s))))
	(with-protected-variables
	 (multiple-value-bind (protect protecti)
	     (collect-protect *function-being-emitted* nil s)
	   (and (null protect) (null protecti)
		(every #'null-statement-p (cddr s)))))
	(t 
	 nil))))

(defun emit-label (s)
  (emit-newline-indent (floor *indent-delta* -2))
  (emit-string (find-name-of-label (cadr s)))
  (emit-char #\:))

(defun emit-expression-statement (s)
  (emit-newline-indent)
  (emit-expression s)
  (emit-char #\;))

;;; No code actually generated for this at the point of definition.  Instead,
;;; the gather uses this as a "place-holder" to determine whether the
;;; C global variable definition should be generated.

(define-statement-emitter variable-definition (s in-compound-p)
  (declare (ignore s))
  (emit-statement (make-target-form 'null-statement) in-compound-p))

(define-statement-emitter null-statement (s in-compound-p)
  (declare (ignore s))
  (unless in-compound-p
    (emit-char #\;)))


;;; Return-value and return-values are similar, but return-value has
;;; simpler treatment for cases where you have to pop the lisp stack
;;; before returning because we know that the computation of the
;;; return result is an "atomic" operation.
;;; *** These three functions ought to use common helpers.

(define-statement-emitter return-value (s in-compound-p)
  (cond ((or (need-to-pop-stack)
	     (need-to-unprotect))
	 (with-compound-statement in-compound-p
	   (emit-newline-indent)
	   (emit-string "RESTORE_STACK();")
	   (emit-maybe-values-return (cadr s))))
	(t
	 (emit-maybe-values-return (cadr s)))))

(defun emit-maybe-values-return (e)
  (emit-newline-indent)
  (if *sets-values-count-p*
      (progn
	(emit-string "return VALUES_1(")
	(emit-expression e)
	(emit-string ");"))
      (progn
	(emit-string "return ")
	(emit-expression e)
	(emit-string ";"))))

(define-statement-emitter return-values (s in-compound-p)
  (cond ((need-to-pop-stack)
	 (with-compound-statement in-compound-p
	   (emit-store-values (cadr s))
	   (emit-newline-indent)
	   (emit-string "RESTORE_STACK();")
	   (emit-newline-indent)
	   (emit-string "return result;")))
	((need-to-unprotect)
	 (with-compound-statement in-compound-p
	   (emit-newline-indent)
	   (emit-string "RESTORE_STACK();")
	   (emit-newline-indent)
	   (emit-string "return ")
	   (emit-expression (cadr s))
	   (emit-string ";")))
	(t
	 (emit-newline-indent)
	 (emit-string "return ")
	 (emit-expression (cadr s))
	 (emit-string ";"))))

(define-statement-emitter return-stored-values (s in-compound-p)
  (declare (ignore s))
  (cond ((or (need-to-pop-stack) (need-to-unprotect))
	 (with-compound-statement in-compound-p
	   ;; WARNING: The order of unprotect and restore is important.
	   (emit-newline-indent)
	   (emit-string "RESTORE_STACK();")
	   (emit-newline-indent)
	   (emit-string "return result;")))
	(t
	 (emit-newline-indent)
	 (emit-string "return result;"))))


(define-statement-emitter save-values (s in-compound-p)
  (declare (ignore in-compound-p))
  (emit-newline-indent)
  (emit-string "SAVE_VALUES(")
  (emit-expression (second s))
  (emit-string ");"))

(define-statement-emitter save-more-values (s in-compound-p)
  (declare (ignore in-compound-p))
  (emit-newline-indent)
  (emit-string "SAVE_MORE_VALUES(")
  (emit-expression (second s))
  (emit-string ");"))

(define-statement-emitter store-value (s in-compound-p)
  (declare (ignore in-compound-p))
  (emit-newline-indent)
  (emit-string "result = VALUES_1(")
  (emit-expression (cadr s))
  (emit-string ");"))

(define-statement-emitter store-values (s in-compound-p)
  (declare (ignore in-compound-p))
  (emit-store-values (cadr s)))

(defun emit-store-values (s)
  ;; Temporary crock for "result ="
  (emit-newline-indent)
  (emit-string "result = ")
  (with-emit-and-split-string nil
   (emit-expression s assignment-precedence))
  (emit-char #\;))

(define-statement-emitter with-protected-variables (s in-compound-p)
  (let ((statements (cdr s)))
    (if statements
	(multiple-value-bind (protect protecti)
	    (collect-protect *function-being-emitted* nil s)
	  (if (and (null (cdr statements))
		   (null protect) (null protecti))
	      (emit-statement (car statements) in-compound-p)
	      (with-compound-statement in-compound-p
		(let ((*saved-stack-p* *saved-stack-p*)
		      (*protecting-variables-p* *protecting-variables-p*)
		      (*protected-variables* *protected-variables*))
		  (emit-gc-protect protect protecti)
		  (emit-statements statements)))))
	(unless in-compound-p
	  (emit-newline-indent)
	  (emit-char #\;)))))

(define-statement-emitter values-assign (s in-compound-p)
  (declare (ignore in-compound-p))
  (let* ((places (cdr s))
	 (length (length places))
	 (limit *max-values-inline-assign*)
	 (so-far (1+ (mod (1- length) limit))))
  (emit-newline-indent)
  (with-emit-and-split-string nil
    (emit-format "MVS_~D(result" so-far)
    (dotimes (i so-far)
      (let ((e (pop places)))
	(emit-char #\,)
	(emit-expression e assignment-precedence)))
    (emit-string ");"))
  (loop (unless (< so-far length)
	  (return nil))
	(emit-newline-indent)
	(let* ((next (min (+ so-far limit) length))
	       (this-time (- next so-far)))
	  (with-emit-and-split-string nil
	    (emit-format "MVSR(~D" so-far)
	    (dotimes (i this-time)
	      (let ((e (pop places)))
		(emit-char #\,)
		(emit-expression e assignment-precedence)))
	    (emit-string ");"))
	  (setq so-far next)))))

(define-statement-emitter with-lexical-bindings (s in-compound-p)
  (let ((closed     (remove-if-not #'variable-record-closed-p (cadr s)))
	(statements (cddr s)))
    (if (or statements closed)
	(if (and (null closed) (null (cdr statements)))
	    (emit-statement (car statements) in-compound-p)
	    (with-compound-statement in-compound-p
	      (dolist (v closed)
		(emit-newline-indent)
		(emit-format "~a = ADD_BINDING(~a);"
			     (variable-record-unique-name v)
			     (if (variable-record-closure-state v)
				 (variable-record-unique-name
				  (car (variable-record-closure-state v)))
				 "Nil")))
	      (emit-statements statements)))
	(unless in-compound-p
	  (emit-newline-indent)
	  (emit-char #\;)))))

(define-statement-emitter with-special-binding (s in-compound-p)
  (let* ((index (cadr s))
	 (name  (caddr s))
	 (init  (cadddr s))
	 (rest  (cddddr s))
	 (cname (c-name-of-global-variable name)))
    (with-compound-statement in-compound-p
      (emit-newline-indent)
      #-translator-supports-thread
      (emit-format "PUSH_SPECIAL(~a," cname)
      #+translator-supports-thread
      (emit-format "PUSH_SPECIAL_WITH_SYMBOL(~a,~a,"
		   cname (c-name-of-quoted-symbol name))
      (emit-expression init)
      (emit-format ",~d);" index)
      (let ((*indent-column*  (+ *indent-column* *semi-indent-delta*)))
	(emit-statements rest))
      (emit-newline-indent)
      (emit-string "POP_SPECIAL();"))))

(define-statement-emitter labeled-statement (s in-compound-p)
  (emit-label s)
  (let ((statement (caddr s)))
    (emit-statement statement
		    (and in-compound-p
			 (not (eq (target-form-type statement)
				  'null-statement))))))

(define-statement-emitter goto (s in-compound-p)
  (let ((label     (find-name-of-label (cadr s)))
	(specials  (caddr s))
	(catches   (cadddr s)))
    (flet ((doit ()
	     (emit-newline-indent)
	     (emit-string "goto ")
	     (emit-string label)
	     (emit-char #\;)))
      (if (or (> specials 0) catches)
	  (with-compound-statement in-compound-p
	    (pop-the-specials specials)
	    (pop-the-catches catches)
	    (doit))
	  (doit)))))

(defun pop-the-specials (n)
  (dotimes (i n)
    (emit-newline-indent)
    (emit-string "POP_SPECIAL();")))

(defun pop-the-catches (catches)
  (dolist (catcher catches)
    (emit-newline-indent)
    (emit-format "POP_CATCH(~d);" (second (car catcher)))))

(define-statement-emitter switch (s in-compound-p)
  (declare (ignore in-compound-p))
  (emit-newline-indent)
  (emit-string "switch (")
  (emit-expression (cadr s))
  (emit-char #\))
  (let ((*indent-column*  (+ *indent-column* *indent-delta*)))
    (emit-statement (caddr s) nil)))

(define-statement-emitter compound-statement (s in-compound-p)
  (with-compound-statement in-compound-p
    (emit-statements (cdr s))))


;;; For "if", do some magic so that "else if"'s line up neatly.  Also
;;; watch out for dangling else problem in the then clauses.

(define-statement-emitter if-statement (s in-compound-p)
  (declare (ignore in-compound-p))
  (emit-if-aux "if " s))

(defun emit-if-aux (string s)
  (emit-newline-indent)
  (emit-string string)
  (emit-char #\()
  (emit-expression (cadr s))
  (emit-char #\))
  (let ((*indent-column* (+ *indent-column* *indent-delta*))
	(then-statement  (emittable-part (caddr s))))
    (if (eq (target-form-type then-statement) 'if-statement)
	(emit-statement
	 (make-target-form 'compound-statement then-statement) nil)
	(emit-statement then-statement nil)))
  (setq s (cadddr s))
  (setq s (emittable-part s))
  (cond ((null s)
	 nil)
	((eq (target-form-type s) 'if-statement)
	 (emit-if-aux "else if " s))
	(t
	 (emit-newline-indent)
	 (emit-string "else")
	 (let ((*indent-column*  (+ *indent-column* *indent-delta*)))
	   (emit-statement s nil)))))

;;; Given a target statement (or nil), return a
;;; (possibly simpler target statement
;;; that will emit the same way. Useful for target forms (like if-statement)
;;; that look at the target-form-type substatements, so they will not be
;;; misled by non-emitting pieces (such as with-lexical-bindings for
;;; non-closed-over variables)
(defun emittable-part (s)
  (when s
    (case (target-form-type s)
      (with-protected-variables
       (if (and (cadr s) (null (cddr s))
		(multiple-value-bind (protect protecti)
		    (collect-protect *function-being-emitted* nil s)
		  (and (null protect) (null protecti))))
	   (emittable-part (cadr s))
	   s))
      (with-lexical-bindings
       (if (and (notany #'variable-record-closed-p (cadr s))
		(caddr s)
		(null (cdddr s)))
	   (emittable-part (caddr s))
	   s))
      (compound-statement
       (if (and (cadr s)
		(null (cddr s)))
	   (emittable-part (cadr s))
	   s))
      (t 
       s))))


(define-statement-emitter with-catch (s in-compound-p)
  (let ((index   (second s)))
    (with-compound-statement in-compound-p
      (emit-statement
       (make-target-form 'if-statement
			 (make-target-form 'set-catch (third s) index)
			 (fourth s)
			 (fifth s))
       t)
      (emit-newline-indent)
      (emit-format "POP_CATCH(~d);" index))))

(define-statement-emitter with-unwind-protect (s in-compound-p)
  (let ((index   (second s)))
    (with-compound-statement in-compound-p
      (emit-statement
       (make-target-form 'if-statement
			 (make-target-form 'set-unwind-protect index)
			 (third s))
       t)
      (emit-newline-indent)
      (emit-format "POP_UNWIND_PROTECT(~d);" index)
      (emit-statement (fourth s) t)
      (emit-newline-indent)
      (emit-format "CONTINUE_UNWINDING(~d);" index))))

(define-statement-emitter with-progv (s in-compound-p)
  (destructuring-bind (index symbols values body) (cdr s)
    (with-compound-statement in-compound-p
      (emit-statement
       (make-target-form
	'if-statement (make-target-form 'set-progv symbols values index)
	body)
       t)
      (emit-newline-indent)
      (emit-format "POP_PROGV(~D);" index))))

(define-statement-emitter with-local-allocation (s in-compound-p)
  (destructuring-bind (catch-index area-index frontier-index body) (cdr s)
    (with-compound-statement in-compound-p
      (emit-statement
       (make-target-form 'if-statement
			 (make-target-form 'set-local-allocation
					   catch-index
					   area-index
					   frontier-index)
			 body)
       t)
      (emit-newline-indent)
      (emit-format "POP_LOCAL_ALLOCATION(~:[~D,~;~*~]~D,~D);"
		   *new-areas-and-frontiers* catch-index
		   area-index frontier-index))))

(define-statement-emitter with-area (s in-compound-p)
  (destructuring-bind (catch-index area-index area-keyword body) (cdr s)
    (with-compound-statement in-compound-p
      (emit-statement
       (make-target-form 'if-statement
			 (make-target-form 'set-area
					   catch-index
					   area-index
					   area-keyword)
			 body)
       t)
      (emit-newline-indent)
      (emit-format "POP_AREA(~:[~D,~;~*~]~D);" 
		   *new-areas-and-frontiers* catch-index
		   area-index))))

(define-statement-emitter forever-statement (s in-compound-p)
  (declare (ignore in-compound-p))
  (emit-newline-indent)
  (emit-string "for (;;)")
  (let ((*indent-column*  (+ *indent-column* *indent-delta*)))
    (emit-statement (second s) nil)))

(define-statement-emitter for-statement (s in-compound-p)
  (let ((init      (second s))
	(end-test  (third s))
	(step      (fourth s))
	(body      (fifth s))
	(result    (sixth s)))
    (if result
	(with-compound-statement in-compound-p
	  (emit-for-aux init end-test step body)
	  (emit-statement result t))
	(emit-for-aux init end-test step body))))

(defun emit-for-aux (init end-test step body)
  (emit-newline-indent)
  (emit-string "for ")
  (with-emit-and-split-string nil
    (emit-string "( ")
    (when init 
      (emit-expression init expression-precedence))
    (emit-string "; ")
    (when end-test
      (emit-expression end-test expression-precedence))
    (emit-string "; ")
    (when step
      (emit-expression step expression-precedence))
    (emit-string ")"))
  (let ((*indent-column*  (+ *indent-column* *indent-delta*)))
    (emit-statement body nil)))

(define-statement-emitter while-statement (s in-compound-p)
  (declare (ignore in-compound-p))
  (emit-newline-indent)
  (with-emit-and-split-string nil
    (emit-format "while (~e)" (cadr s)))
  (let ((*indent-column*  (+ *indent-column* *indent-delta*)))
    (emit-statement (caddr s) nil)))

(define-statement-emitter do-while-statement (s in-compound-p)
  (declare (ignore in-compound-p))
  (emit-newline-indent)
  (emit-string "do ")
  (let ((*indent-column*  (+ *indent-column* *indent-delta*)))
    (emit-statement (cadr s) nil))
  (with-emit-and-split-string nil
    (emit-format " while (~e);" (caddr s))))

(define-statement-emitter break-statement (s in-compound-p)
  (let ((specials  (cadr s))
	(catches   (caddr s)))
    (flet ((doit ()
	     (emit-newline-indent)
	     (emit-string "break;")))
      (if (or (> specials 0) catches)
	  (with-compound-statement in-compound-p
	    (pop-the-specials specials)
	    (pop-the-catches catches)
	    (doit))
	  (doit)))))

(define-statement-emitter set-symbol-value-location (s in-compound-p)
  (declare (ignore in-compound-p))
  (let ((symbol  (second s)))
    (emit-newline-indent)
    (with-emit-and-split-string nil
      (emit-format "SET_SYMBOL_VALUE_LOCATION(~a,~a);"
		   (c-name-of-quoted-symbol symbol)
		   (c-name-of-global-variable symbol)))))

(define-statement-emitter c-lines (s in-compound-p)
  (declare (ignore in-compound-p))
  (mapc #'emit-c-line (rest s)))

(defun emit-c-line (c-line-string)
  (if (stringp c-line-string)
      (let* ((start 0)
	     (length (length c-line-string)))
	(loop (when (> start length)
		(return nil))
	      (when (= start length)
		(emit-newline-indent)
		(return nil))
	      (let ((end (or (position #\newline c-line-string :start start)
			     length))
		    (cpp-p (char= #\# (char c-line-string start))))
		(if cpp-p
		    (emit-newline)
		    (emit-newline-indent))
		(with-emit-and-split-string (when cpp-p " \\")
		  (emit-string c-line-string start end))
		(setq start (1+ end)))))
      (emit-newline)))

(define-statement-emitter preprocessor-conditional (s in-compound-p)
  (declare (ignore in-compound-p))
  (let ((all-if-conditionals nil))
    (flet ((emit-if/else-line (conditional first-if-command-p)
	     (unless first-if-command-p
	       (emit-newline)
	       (emit-char #\#)
	       (emit-string "else"))
	     (let ((if-command-string nil)
		   (if-conditional    nil))
	       (cond ((stringp conditional)
		      (setf if-command-string "if"
			    if-conditional    conditional)
		      (push if-conditional all-if-conditionals))
		     ((consp conditional)
		      (setf if-command-string
			    (if (eq (first conditional) :defined)
				"ifdef"
			        "ifndef")
			    if-conditional (second conditional))
		      (push if-conditional all-if-conditionals)))
	       (when if-command-string
		 (emit-newline)
		 (emit-char #\#)
		 (emit-string if-command-string)
		 (emit-char #\space)
;		 (let ((delta (- *indent-column* (current-column))))
;		   (if (plusp delta)
;		       (dotimes (counter delta)
;			 (emit-char #\space))
;		       (emit-char #\space)))
		 (emit-string if-conditional)))))
      (do ((conditionals       (second s) (rest conditionals))
	   (statements         (third s)  (rest statements))
	   (first-if-command-p t          nil)
	   (conditional)
	   (clause-statements))
	  ((null conditionals)
	   (dolist (if-conditional all-if-conditionals)
	     (emit-newline)
	     (emit-char #\#)
	     (emit-string "endif ")
	     (emit-comments (list if-conditional) nil)))
	(setf conditional (first conditionals)
	      clause-statements (first statements))
	(emit-if/else-line conditional first-if-command-p)
	(when clause-statements
	  (emit-statements clause-statements))))))

;;; No code actually generated for this at the point of reference.  Instead,
;;; the gathering done by merge-initcode collects the function record, with
;;; merge-initcode emitting the function definition directly from the record.

(define-statement-emitter function-definition (s in-compound-p)
  (declare (ignore s))
  (emit-statement (make-target-form 'null-statement) in-compound-p))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Build expression strings
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(defmacro define-expression-emitter (name lambda-list &body body
					  &environment env)
  (let ((fname-prec (intern (sformat "EMIT-~a-FUNCTION-PRECEDENCE" name)))
	(fname-emit (intern (sformat "EMIT-~a-FUNCTION-EMIT" name))))
    (when (translator-environment-p env)
      (setq env nil))
    (unless (and (consp (car body))
		 (null (cdr body)))
      (pprint body)
      (error "bad form for define-expression-emitter"))
    (unless (eq (caar body) 'values)
      (setq body (list (macroexpand (car body) env))))
    (unless (eq (caar body) 'values)
      (pprint body)
      (error "bad form for define-expression-emitter"))
    `(progn
       (defun ,fname-prec ,lambda-list ,@lambda-list ,(third (car body)))
       (defun ,fname-emit ,lambda-list ,@lambda-list ,(second (car body)))
       (setf (emit-expression-function ',name) 
	     (cons #',fname-prec #',fname-emit))
       ',name)))

;;; Each emit-expression-function returns two values, a string and
;;; a predecence number.  If the returned precedence is less than the
;;; precedence specified as an argument, wrap the returned expression
;;; string with parentheses.
;;;
;;; The argument precedences specified when walking subexpressions 
;;; generally correspond to what the C grammar allows.  If you want to 
;;; force parentheses to show up even when they're not strictly required, 
;;; just provide a higher precedence argument.  Passing primary-precedence 
;;; will force just about everything to end up wrapped in parens!
;;;
;;; Note that the individual expression builders are responsible for
;;; handling associativity of subexpressions at the same precedence
;;; level.  This is really only an issue for things that are defined as 
;;; n-ary expressions in the target language but which are actually
;;; implemented as binary operators with either left- or right-associativity.

;;; Note that we copy an expression whenever we put parentheses around it.
;;; The easiest way around this I can see would be to make this and related
;;; functions return streams, rather than strings. Not clear whether this
;;; would cons less, though.

(defun emit-expression (e &optional (add-parens-below-this-precedence
				     expression-precedence))
  (let ((fn (target-form-emit-expression-function e)))
    (unless fn
      (error "Don't know about target language construct ~s." e))
    (unless (output-buffer-emit-and-split-p 
	     (or *output-buffer*
		 (error "not inside with-output-stream")))
      (emit-and-split-start nil))
    (let* ((precedence-fn (car fn))
	   (emit-fn (cdr fn))
	   (paren-p (< (funcall precedence-fn e)
		       add-parens-below-this-precedence)))
      (when paren-p (emit-char #\())
      (funcall emit-fn e)
      (when paren-p (emit-char #\))))
    (maybe-deallocate-target-form e)))

(defun emit-expressions (list precedence &optional delimiter)
  (when list
    (emit-expression (car list) precedence)
    (dolist (e (cdr list))
      (typecase delimiter
	(string (emit-string delimiter))
	(character (emit-char delimiter)))
      (emit-expression e precedence))))

;;; Define the actual expression generators.

(define-expression-emitter restore-values (e)
  (values (emit-string "RESTORE_VALUES()") postfix-precedence))

(define-expression-emitter values (e)
  (values
   (let ((list (cdr e)))
     (emit-format "VALUES_~D(~:@E)" 
		  (length list)
		  assignment-precedence "," (cdr e)))
   postfix-precedence))

(define-expression-emitter nth-value (e)
  (values
   (emit-format "NTH_VALUE(~:E, result)"
		assignment-precedence (cadr e))
   postfix-precedence))

(define-expression-emitter first-multiple-value (e)
  (values (emit-string "result") primary-precedence))

(define-expression-emitter setq (e)
  (values
   (emit-format "~:E = ~:E"
		prefix-precedence (second e)
		assignment-precedence (third e))
   assignment-precedence))

(define-expression-emitter operator-call (e)
  (values
   (let* ((descriptor (find-descriptor (cadr e)))
	  (operator (foreign-function-descriptor-operator descriptor))
	  (precedence (c-operator-precedence operator)))
     (ecase (c-operator-argument-count operator)
       (1
	(if (c-operator-prefix-p operator)
	    (emit-format "~A~:E"
			 (c-operator-string operator)
			 precedence (caddr e))
	    (emit-format "~:E~A"
			 (c-operator-string operator)
			 precedence (caddr e))))
       (2
	(if (eq (c-operator-name operator) 'csubscripting)
	    (emit-format "~:E[~E]"
			 precedence (caddr e) (cadddr e))
	    (emit-format "~:E~A~:E"
			 precedence (caddr e)
			 (c-operator-string operator)
			 (1+ precedence) (cadddr e))))))
   (let* ((descriptor (find-descriptor (cadr e)))
	  (operator (foreign-function-descriptor-operator descriptor)))
     (c-operator-precedence operator))))

(defun emit-call-aux1 (name countp args)
  (emit-string name)
  (emit-char #\()
  (when countp
    (emit-integer (length args))
    (when args
      (emit-char #\,)))
  (when args
    (emit-expressions args assignment-precedence #\,))
  (emit-char #\)))

(defmacro emit-call-aux (name countp args)
  `(values
     (emit-call-aux1 ,name ,countp ,args)
     postfix-precedence))

(define-expression-emitter call (e)
  (emit-call-aux
   (c-name-of-function-entry (cadr e))
   nil
   (cddr e)))

(define-expression-emitter variadic-call (e)
  (emit-call-aux
   (c-name-of-function-entry (cadr e))
   t
   (cddr e)))

(define-expression-emitter call-generic (e)
  (emit-call-aux
   (c-name-of-function-entry (cadr e))
   nil
   (cddr e)))

(define-expression-emitter variadic-call-generic (e)
  (emit-call-aux
   (c-name-of-function-entry (cadr e))
   t
   (cddr e)))

(define-expression-emitter macro-call (e)
  (emit-call-aux
   (c-name-of-function-entry (cadr e))
   nil
   (cddr e)))

(define-expression-emitter foreign-call (e)
  (emit-call-aux
   (c-name-of-function-entry (cadr e))
   nil
   (cddr e)))

(define-expression-emitter accessor-call (e)
  (emit-call-aux
   (c-name-of-function-entry (cadr e))
   nil
   (cddr e)))

(define-expression-emitter c-call (e)
  (values (emit-c-call e) postfix-precedence))

(define-expression-emitter values-c-call (e)
  (values (emit-c-call e) postfix-precedence))

(define-expression-emitter variadic-c-call (e)
  (values (emit-variadic-c-call e) postfix-precedence))

(define-expression-emitter variadic-values-c-call (e)
  (values (emit-variadic-c-call e) postfix-precedence))

(defun emit-c-call (e)
  (emit-format "~:E(~:@E)"
	       postfix-precedence (second e)
	       assignment-precedence "," (cddr e)))

(defun emit-variadic-c-call (e)
  (if (null (cddr e))
      (emit-format "~:E(0)" postfix-precedence (second e))
      (emit-format "~:E(~D,~:@E)"
		   postfix-precedence (second e)
		   (length (cddr e))
		   assignment-precedence "," (cddr e))))

(define-translator-parameter *use-function-value-cells* nil)

(defun global-function-emitter-internal (e)
  (let ((function-name (cadr e)))
    (if (or *use-function-macros* *use-function-value-cells*)
	(emit-string (c-name-of-function-object function-name))
	(cond ((or (symbolp function-name)
		   (and (environment-entry-p function-name)
			(not (consp (environment-entry-name function-name)))))
	       (emit-format "SYMBOL_FUNCTION(~a)"
			    (c-name-of-quoted-symbol function-name)))
	      ((or (setf-function-name-p function-name)
		   (and (environment-entry-p function-name)
			(consp (environment-entry-name function-name))))
	       (emit-format "SETF_FUNCTION(~a)"
			    (c-name-of-quoted-symbol
			     (cadr 
			      (if (environment-entry-p function-name)
				  (environment-entry-name function-name)
				  function-name)))))
	      (t
	       (bad-function-name-error function-name))))))

(define-expression-emitter global-function (e)
  (values
   (global-function-emitter-internal e)
   primary-precedence))

(define-expression-emitter global-foreign-function (e)
  (values
   (global-function-emitter-internal e)
   primary-precedence))

(define-expression-emitter function-object (e)
  (values
   (let ((record (cadr e)))
     (function-object-initializer
      (ecase (function-record-classification record)
	((:global :bound-global :global-dllexport) "STATIC_FUNCTION")
	((:local :ignore) "MAKE_FUNCTION")) ; :ignore shouldn't need to be here
      (function-record-unique-name record)
      (let ((state (function-record-closure-state record)))
	(if state
	    (variable-record-unique-name (car state))
	    "NIL"))
      (function-record-variadic-p record)
      (function-record-lambda-list-info record)))
   postfix-precedence))

(defun function-object-initializer (maker unique-name closure-state variadic-p
					  ll-info)
  (emit-format "~A(~A,~A,~:[FALSE~;TRUE~],~D,~D)"
	       maker
	       unique-name
	       closure-state
	       variadic-p
	       (if ll-info
		   (lambda-list-info-required ll-info)
		   0)
	       (if ll-info
		   (lambda-list-info-positional ll-info)
		   0)))

(define-expression-emitter symbolic-constant (e)
  (values
   (emit-string (c-name-of-global-variable (cadr e)))
   primary-precedence))

(define-expression-emitter conditional-operator (e)
  (values
   (emit-format "~:E ? ~:E : ~:E"
		logical-or-precedence  (second e)
		logical-or-precedence  (third e)
		conditional-precedence (fourth e))
   conditional-precedence))

(define-expression-emitter not-operator (e)
  (values
   (emit-format "!~:E" 
		cast-precedence (second e))
   prefix-precedence))

(define-expression-emitter comma-operator (e)
  (values
   (if (null (cdr e))
       (error "Can't have an empty comma-operator.")
       (emit-expressions (cdr e) comma-precedence ", "))
   comma-precedence))

(define-expression-emitter and-expression (e)
  (values
   (if (null (cdr e))
       (error "Can't have an empty and-expression.")
       (emit-expressions (cdr e) logical-and-precedence " && "))
   logical-and-precedence))

(define-expression-emitter or-expression (e)
  (values
   (if (null (cdr e))
       (error "Can't have an empty or-expression.")
       (emit-expressions (cdr e) logical-or-precedence " || "))
   logical-or-precedence))

(defparameter *c-constant-foreign-type-alist*
  '(("char"  :char)  ("unsigned char"  :char)
    ("short" :int)   ("unsigned short" :int)
    ("long"  :int)   ("unsigned long"  :int)
    ("int"   :int)   ("unsigned int"   :int)
    ("float" :float) ("double"         :float)))

(defun c-constant-type-name (foreign-type)
  (typecase foreign-type
    (cons
     (case (car foreign-type)
       ((:const :volatile) (c-constant-type-name (cadr foreign-type)))
       (:pointer `(:pointer ,(c-constant-type-name (cadr foreign-type))))
       (:array   `(:array ,(c-constant-type-name (cadr foreign-type))
			  ,(if (eq ':column-major (cadddr foreign-type))
			       (reverse (caddr foreign-type))
			       (caddr foreign-type))))
       (t nil)))
    (symbol
     (case foreign-type
       ((:boolean :object)
	foreign-type)
       ((:unsigned-8bit :signed-8bit :character)
	:char)
       ((:unsigned-16bit :signed-16bit :unsigned-32bit :signed-32bit :unsigned-64bit :signed-64bit
	 :int :fixnum)
	:int)
       ((:single-float :double-float :float :static-float)
	:float)
       ((:string :static-string)
	'(:pointer :char))
       (t
	(let* ((c-type (c-type foreign-type))
	       (len-2 (- (length c-type) 2))
	       (pointer-p (string= c-type " *" :start1 len-2))
	       (c-type1 (if pointer-p
			    (subseq c-type 0 len-2)
			    c-type))
	       (ftn1 (or (cadr (assoc c-type1 *c-constant-foreign-type-alist*
				      :test #'equal))
			 (error "Unknown c constant foreign-type ~s."
				foreign-type))))
	  (if pointer-p
	      `(:pointer ,ftn1)
	      ftn1)))))
    (t
     (c-constant-type-name (translator-foreign-type-name foreign-type)))))

;See immediate-constant-p.
(define-expression-emitter c-constant (e)
  (values
   (let ((foreign-type (cadr e))
	 (value (caddr e)))
     (cond ((eq foreign-type :c-expression)
	    (emit-format "(~a)" value))
	   (t
	    (emit-c-constant (c-constant-type-name foreign-type)
			     value))))
   primary-precedence))

(defun emit-c-constant (type-name value)
  (if (consp type-name)
      (case (car type-name)
	(:pointer
	 (case (cadr type-name)
	   (:char
	    (etypecase value
	      (null
	       (emit-string "NULL"))
	      (string
	       (emit-format "~a" (format-c-string value)))))))
	(:array
	 (if (and (stringp value)
		  (eq (cadr type-name) ':char)
		  (eql 1 (length (caddr type-name)))
		  (or (null *maximum-c-string-constant-length*)
		      (<= (length value)
			  *maximum-c-string-constant-length*)))
	     (emit-format "~a" (format-c-string value))
	     (emit-c-array (cadr type-name)
			   (length (caddr type-name))
			   (active-array-dimensions value)
			   value))))
      (case type-name
	(:object
	 (cond ((eq value *unbound*)
		(emit-string "UNBOUND"))))
	(:boolean
	 (emit-string (if value "TRUE" "FALSE")))
	(:char
	 (emit-format "~a" (format-c-char value)))
	(:int
	 (when *integer-constants-are-long-p*
           (emit-string "(SI_Long)"))
	 (emit-integer value)
	 (when *integer-constants-are-long-p*
	   (emit-char #\L)))
	(:float
	 (emit-string (let ((*read-default-float-format* (type-of value)))
			(prin1-to-string value)))))))

(defun emit-c-array (etype c-rank dims value)
  (let ((*indent-column* (+ *indent-column* 2)))
    (if (and (eql 1 c-rank) (and dims (null (cdr dims))))
	(emit-c-array-1 etype dims value)
	(emit-c-array-any etype c-rank dims value nil))))

(defun emit-c-array-1 (etype dims value)
  (emit-newline-indent)
  (emit-char #\{)
  (let ((*indent-column* (+ *indent-column* 2)))
    (dotimes (i (car dims))
      (unless (zerop i) (emit-char #\,))
      (emit-c-constant etype (aref value i))))
  (emit-newline-indent)
  (emit-char #\}))

(defun emit-c-array-any (etype c-rank dims value position)
  (when (plusp c-rank)
    (emit-newline-indent)
    (emit-char #\{))
  (let ((*indent-column* (+ *indent-column* 2)))
    (cond ((null dims)
	   (emit-c-constant etype (apply #'aref value (reverse position))))
	  (t
	   (let ((c-rank (1- c-rank))
		 (rest (cdr dims)))
	     (dotimes (i (car dims))
	       (unless (zerop i) (emit-char #\,))
	       (emit-c-array-any etype c-rank rest value 
				 (cons i position)))))))
  (when (plusp c-rank)
    (emit-newline-indent)
    (emit-char #\})))

;;; Return a string or character that is the C representation of a character.

(defvar *quoted-char-mappings*
    '((#\newline   . #\n)
      (#\linefeed  . #\n)
      (#\tab       . #\t)
      (#\backspace . #\b)
      (#\return    . #\r)
      (#\page      . #\f)
      (#\\         . #\\)
      (#\?         . #\?)
      (#\'         . #\')
      (#\"         . #\")))

(defun make-octal-char-mapping-vector ()
  (let ((vector (make-array 256)))
    (dotimes (i 256)
      (setf (aref vector i) (format nil "\\~3,'0o" i)))
    vector))

(defvar *octal-char-mapping-vector* (make-octal-char-mapping-vector))

(defun make-char-mapping-vector ()
  (let ((vector (make-array 256 :initial-element nil)))
    (dotimes (i 256)
      (let ((char (tutil::ascii-code-char i)))
	(when (standard-char-p char)
	  (setf (aref vector i) (format nil "~a" char)))))
    (dolist (char *quoted-char-mappings*)
      (setf (aref vector (tutil::char-ascii-code (car char)))
	    (format nil "\\~a" (cdr char))))
    (dotimes (i 256)
      (unless (aref vector i)
	(setf (aref vector i) (aref *octal-char-mapping-vector* i))))
    vector))

(defmacro octal-c-char-name (code)
  `(aref *octal-char-mapping-vector* ,code))

(defvar *char-mapping-vector* (make-char-mapping-vector))

(defmacro c-char-name (char)
  `(aref *char-mapping-vector* (tutil::char-ascii-code ,char)))

(defvar *octal-char-string-vector* (make-array 256 :initial-element nil))
(defvar *char-string-vector* (make-array 256 :initial-element nil))

(defun format-c-char (char)
  (etypecase char
    (character
     (let ((code (tutil::char-ascii-code char)))
       (declare (fixnum code))
       (or (aref *char-string-vector* code)
	   (setf (aref *char-string-vector* code)
		 (format nil "'~a'" (c-char-name char))))))
    (fixnum
     (let ((code char))
       (declare (fixnum code))
       (when (minusp code)
	 (setq code (logand code #xFF)))
       (or (aref *octal-char-string-vector* code)
	   (setf (aref *octal-char-string-vector* code)
		 (format nil "'~a'" (octal-c-char-name code))))))))

;;; Return a string that is the C representation of a string.
(defun format-c-string (string)
  (let ((size 2)
	(length (length string)))
    (declare (fixnum size length))
    (dotimes (i length)
      (incf size (length (c-char-name (char string i)))))
    (let ((c-string (make-string size)))
      (setf (char c-string 0) #\")
      (setf (char c-string (1- size)) #\")
      (let ((position 0))
	(declare (fixnum position))
	(dotimes (i length c-string)
	  (let ((str (c-char-name (char string i))))
	    (dotimes (j (length str))
	      (setf (char c-string (incf position)) (char str j)))))))))

(define-expression-emitter box-value (e)
  (values
   (let* ((ctype (cadr e))
	  (value (caddr e))
	  (boxer (boxer ctype)))
     (unless boxer
       (warn "~S doesn't have a boxer" ctype))
     (if (eq boxer :nonstandard)
	 (if (eq :boolean (translator-foreign-type-name ctype))
	     (emit-format "~:E ? T : Nil"
			  logical-or-precedence value)
	     (error "nonstandard boxer but non-boolean ctype"))
	 (emit-format "~a(~e)"
		      (c-name-of-function-entry boxer) value)))
   (let* ((ctype (cadr e))
	  (boxer (boxer ctype)))
     (if (and (eq boxer :nonstandard)
	      (eq :boolean (translator-foreign-type-name ctype)))
	 conditional-precedence
	 postfix-precedence))))

(define-expression-emitter unbox-value (e)
  (values
   (let* ((ctype   (cadr e))
	  (value   (caddr e))
	  (unboxer (unboxer ctype)))
     (unless unboxer
       (warn "~S doesn't have an unboxer" ctype))
     (emit-format "~a(~e)"
		  (c-name-of-function-entry unboxer) value))
   postfix-precedence))

(define-expression-emitter unbound-special-p (e)
  (values
   (emit-format "~:E == UNBOUND"
		primary-precedence (cadr e))
   equality-precedence))
  
(define-expression-emitter constant (e)
  (values (emit-string (variable-record-unique-name (third e)))
	  primary-precedence))

(define-expression-emitter constant-label (e)
  (values (emit-string (variable-record-unique-name (second e)))
	  primary-precedence))

(define-expression-emitter initial-symbol (e)
  (values (emit-string (c-name-of-quoted-symbol (cadr e)))
	  primary-precedence))

(define-expression-emitter initial-package (e)
  (values (emit-string (c-name-of-package (cadr e)))
	  primary-precedence))

(define-expression-emitter load-time-value (e)
  (values (emit-string (variable-record-unique-name (fourth e)))
	  primary-precedence))

(define-expression-emitter local-variable (e)
  (values
   (let ((record  (cadr e)))
     (if (and (variable-record-closed-p record)
	      (closed-binding-used-here-p record))
	 (emit-format "BINDING_OF(~a)"
		      (variable-record-unique-name record))
	 (emit-string (variable-record-unique-name record))))
   (let ((record  (cadr e)))
     (if (and (variable-record-closed-p record)
	      (closed-binding-used-here-p record))
	 postfix-precedence
	 primary-precedence))))

(define-expression-emitter special-variable (e)
  (values
   (emit-string (c-name-of-global-variable (cadr e)))
   primary-precedence))


;;; These are hacks used by the emitters for WITH-CATCH,
;;; WITH-UNWIND-PROTECT, WITH-PROGV, WITH-LOCAL-ALLOCATION, and WITH-AREA.

(define-expression-emitter set-catch (e)
  (values
   (emit-format "PUSH_CATCH(~:E,~d)"
		assignment-precedence (second e)
		(third e))
   postfix-precedence))

(define-expression-emitter set-unwind-protect (e)
  (values
   (emit-format "PUSH_UNWIND_PROTECT(~d)" (second e))
   postfix-precedence))

(define-expression-emitter set-progv (e)
  (values (destructuring-bind (symbols values index) (cdr e)
	    (emit-format "PUSH_PROGV(~:E,~:E,~d)"
			 assignment-precedence symbols
			 assignment-precedence values
			 index))
	  postfix-precedence))

(define-expression-emitter set-local-allocation (e)
  (values (destructuring-bind (catch-index area-index frontier-index) (cdr e)
	    (emit-format "PUSH_LOCAL_ALLOCATION(~A,~:[~D,~;~*~]~D,~D)"
			 "Local_area" 
			 *new-areas-and-frontiers* catch-index
			 area-index frontier-index))
	  postfix-precedence))

(define-expression-emitter set-area (e)
  (values (destructuring-bind (catch-index area-index area-keyword) (cdr e)
	    (emit-format "PUSH_AREA(~A,~:[~D,~;~*~]~D)"
			 (ecase area-keyword
			   (:dynamic "Dynamic_area")
			   (:static "Static_area")
			   (:local "Local_area"))
			 *new-areas-and-frontiers* catch-index
			 area-index))
	  postfix-precedence))

(define-expression-emitter cast (e)
  (values
   (emit-format "(~A)~:E"
		(c-type (second e))
		prefix-precedence (third e))
   cast-precedence))

(define-expression-emitter function-name (e)
  (values
   (emit-string (let ((fn (cadr e)))
		  (cond ((stringp fn) 
			 fn)
			((or (symbolp fn) (consp fn))
			 (c-name-of-function-entry fn))
			(t
			 (function-record-unique-name (cadr e))))))
   primary-precedence))

;;; This ties in with references to %local-temp-declaration on
;;; the database.
(define-local-temp-emitter trun:%local-temp-declaration (key)
  (declare (ignore key))
  (emit-newline-indent)
  (emit-string "Declare_local_temp;"))

(define-local-temp-emitter trun:%store-value-temp-declaration (key)
  (declare (ignore key))
  (emit-newline-indent)
  (emit-string "Object result;"))

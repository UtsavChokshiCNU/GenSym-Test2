;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module OS-SETTINGS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; John Hodgkinson

;; 26 February 1996
;;
;; Some utility functions were moved from here to UNICODE so that they could use
;; the UNICODE module's string processing functions.  Some of the documentation
;; the big picture remain documented in OS-SETTINGS.  The core primitive
;; functions of course remain here.  (MHD 2/26/96)


;; 2 February 1992
;;
;; This module was spun off from BASICS #369 and PLATFORMS #468 (and probably
;; eventually INTERFACES as well) It contains the machinery with which G2
;; receives settings from the operating system, including command-line
;; arguments, environment variables, user name, and user home directory string.
;; It was thought that this machinery is complex enough to rate its own module.
;; As well, it is time os-specific modules got more revealing names.

;; jh, 2/2/92.  Only spun off as much as was necessary to upgrade the time
;; machinery.  Did not introduce any new functionality.  As soon as the smoke
;; clears from the beta, the command-line machinery from INTERFACES and PLATFORMS
;; should be migrated here.

;; jh, 4/4/93.  Finished the consolidation of OS settings code into this file.


;;;; Forward References


(declare-forward-references
  (reclaim-gensym-string function)
  (copy-null-terminated-string-as-text-string function)
  (import-text-string function)
  (gensym-cons-function function)
  (obtain-simple-gensym-string function)
  )



;;;; Command-Line Arguments

;;; A `command-line argument' is part of the command-line which launched G2,
;;; considered as a string.  Command-line arguments are used to modify various
;;; aspects of G2's behavior. ...

;;; The external interface for processing the command-line which launched G2:

;;; get-command-line-keyword-argument (keyword-string)
;;; 
;;; Returns the command-line argument following the given keyword as a string,
;;; or nil if there is no such argument, any error occurs, or the operating
;;; system does not support a command-line facility.  This string should NOT be
;;; reclaimed by the caller, as it may be from a cache.  The keyword comaparison
;;; is case-sensitive.
;;; E.g., (get-command-line-keyword-argument "-display")

;;; get-command-line-keyword-argument-as-integer (keyword-as-string) 
;;;
;;; Returns the command-line argument following the given keyword as a fixnum,
;;; or nil if there is no such argument, any error occurs, or the operating
;;; system does not support a command-line facility.  This string should NOT be
;;; reclaimed by the caller, as it may be from a cache.  The keyword comaparison
;;; is case-insensitive.
;;; E.g., (get-command-line-keyword-argument-as-integer "-rgn1lmt")

;;; get-command-line-flag-argument (flag-as-string &optional require-hyphen?)
;;;
;;; Returns a non-nil value if the given flag is present on the command line.
;;; Returns nil if the flag is not preseht, any error occurs, or the operating
;;; system does not support a command-line facility.  If the non-nil value is a
;;; string, it should NOT be reclaimed, as it may be from a cache.  The flag
;;; comaparison is case-insensitive.
;;; E.g., (get-command-line-flag-argument "start" t) to start a KB on launch

;;; For lower-level command-line processing:

;;; get-gensym-command-line-argument (arg-number)
;;;
;;; Returns the command-line argument specified by arg-number as a string, or
;;; nil if there is no such argument, any error occurs, or the operating system
;;; does not support a command-line facility.  This string should NOT be
;;; reclaimed by the caller, as it may be from a cache.  The 0th argument is the
;;; name of the command which launched the G2 or TW image.
;;; E.g. (get-gensym-command-line-argument 1)

;;; get-gensym-command-line-argument-count ()
;;;
;;; Returns the count of all command-line arguments as a fixnum, or nil if any
;;; error occurs or the operating system does not support a command-line
;;; facility.


;;; Unlike get-gensym-environment-variable (the interface functions for
;;; environment variable defined below), all the above interface functions
;;; return strings which should NOT be reclaimed since they may be from a cache.

;; jh, 4/4/93.  Accessing the command-line in any other way than through this
;; interface is denigrated.  As of this date, they have been removed.




;;; The variable `unix-command-line-arguments' is a list of the strings
;;; corresponding to the unix command line arguments given to G2, or t when
;;; these command line arguments have not yet been retrieved.
;;;
;;; The variable `unix-command-line-arguments-as-text-strings' is a list of the
;;; text strings corresponding to the unix command line arguments given to G2,
;;; or t when these command line arguments have not yet been retrieved.  These
;;; have been imported into G2 with character set translation done in some
;;; standard way.

;; jh, 4/4/93.  As of this date, the variable unix-command-line-arguments is
;; suitable for intercepting command-line-arguments with our own.

;; ...as is unix-command-line-argument-count for intercepting the count of
;; command-line-arguments. paf! 29oct93.
;; the unix-command-line-argument-count should not be initialized to t.
;;   -ncc, 7/6/94

(defvar unix-command-line-arguments t)
(defvar unix-command-line-arguments-as-text-strings t)
(defvar unix-command-line-argument-count 0)

;;; The macro  `general-get-command-line-argument' determines  from
;;; which place command line arguments will  be obtained
;;; Because in translated g2 the single quote in commandline will be remove,
;;; we need to do this in LW, Clozure and SBCL g2.

(defmacro general-get-command-line-argument (argument-number)
  #+(and clozure (not chestnut-3))
  `(remove #\' (nth ,argument-number ccl:*command-line-argument-list*))
  #+(and sbcl (not chestnut-3))
  `(remove #\' (nth ,argument-number sb-ext:*posix-argv*))
  #+(and lispworks (not chestnut-3))
  `(remove #\' (nth ,argument-number system:*line-arguments-list*))
  #+chestnut-3
  `(foreign-get-command-line-argument ,argument-number))

;;; The function `cache-command-line-if-necessary' is called by the
;;; launch-function created by the define-system-access form for G2, TW, or
;;; other products.  Cache-command-line-if-necessary stores the command-line
;;; which launched G2/TW, as tokenized by the C argv mechanism, into the
;;; variable unix-command-line-arguments.  Whenever either of the following
;;; variables is T, this rebuilds the cache, resetting both variables to a fresh
;;; list of gensym-conses, and either unshared text strings or shared gensym
;;; strings:
;;;
;;;   unix-command-line-arguments-as-text-strings
;;;   unix-command-line-arguments
;;;
;;; In addition, the variable unix-command-line-argument-count is set
;;; appropriately.

(defun cache-command-line-if-necessary ()
  (when (or
	  ;; either var T invalidates cache:
	  (eq unix-command-line-arguments-as-text-strings t)
	  (eq unix-command-line-arguments t))
    (loop for argument-number from 0
	  as argument = (general-get-command-line-argument argument-number)
	  while argument
	  collect argument into result using gensym-cons-function
	  finally (setf unix-command-line-arguments result)
		  (setf unix-command-line-argument-count argument-number))
    (copy-unix-line-arguments-as-text-strings)))

(defun copy-unix-line-arguments-as-text-strings ()
  (setq unix-command-line-arguments-as-text-strings
	(loop for string in unix-command-line-arguments
	      collect (import-text-string string 'command-line-argument)
		using gensym-cons-function)))


;; Added cache for imported-text-string version of the arg list. Also: removed
;; the mystifying head/tail logic above, as well as free consing (using CONS) in
;; favor of a simple collect using gensym-cons-function.  I'm confident this is
;; an improvement.  (MHD 2/27/96)



(def-gensym-c-function c-argv-n-strlen 
		       (:fixnum-int "g2ext_argv_strlen")
  ((:fixnum-int arg-number)))

(def-gensym-c-function c-return-argv-n
		       (:fixnum-int "g2ext_return_argv")
  ((:string buff) (:fixnum-int arg-number)))

(defun foreign-get-command-line-argument (argument-number)
  (let ((length (c-argv-n-strlen argument-number)))
    (if (=f length c-argv-n-strlen-failure)
	nil
	(let* ((buffer (obtain-simple-gensym-string length))
	       (result-code (c-return-argv-n buffer argument-number)))
	  (cond
	    ((=f result-code gensym-environment-variable-success)
	     (prog1 (copy-null-terminated-string-as-text-string buffer)
	       (reclaim-gensym-string buffer)))
	    (t nil))))))

;; jh, 5/28/92.  Modified foreign-get-command-line-argument and
;; foreign-get-environment-variable to use
;; interface-to-foreign-environment-access, the preferred interface when we get
;; strings from the C side.  The previous code called make-string without
;; establishing a permanent consing area.  We believe this placed a pointer to
;; the beginning of the temporary area in our simple string pool, causing
;; copy-simple-text-string to return the same pointer as that returned by
;; subsequent make-strings in the non-permanent area.  This in turn broke the
;; get-command-line-arguments-from-launch system procedure, causing it to return
;; reclaimed strings after the first time it was called.


(def-gensym-c-function c-get-argc
		       (:fixnum-int "g2ext_return_argc")  ())




;;; The function `get-gensym-command-line-argument' ... returns a string (a
;;; gensym/Common Lisp string) corresponding to arg-number, if there is one, or
;;; nil.  The indexing of arguments is 1-based.  Note that the resulting string
;;; is shared, and should never be reclaimed or mutated.  The use of this
;;; function is generally discouraged in favor of
;;; copy-gensym-command-line-argument-as-text-string, q.v..
;;;
;;; The function `get-gensym-command-line-argument-as-text-string' returns a
;;; text-string corresponding to arg-number, if there is on, or nil.  Note that
;;; the resulting string is shared, and should never be reclaimed or mutated.
;;; Note that in this case the string is "imported", using import-text-string,
;;; q.v., as COMMAND-LINE-ARGUMENT.  However, note that this imporation is done
;;; at the start of the system process, not at the time this function is called.
;;; The character set translation performed on the string is parameterized in
;;; the text import facility, q.v., in UNICODE.

(defun get-gensym-command-line-argument (arg-number)
  (when (listp unix-command-line-arguments)
    (nth arg-number unix-command-line-arguments)))

(defun get-gensym-command-line-argument-as-text-string (arg-number)
  (when (listp unix-command-line-arguments-as-text-strings)
    (nth arg-number unix-command-line-arguments-as-text-strings)))













;;;; Intercepting Command-line Arguments

;;; In debugging, it is sometimes useful to simulate launching G2 with a given
;;; command line.  The interface to this facility is the development-only
;;; function replace-command-line.  It takes as argument a single string, which
;;; consists of the command line that G2 should use.  Note that G2 takes a lot
;;; of action based on the command-line when it launches, so calling
;;; replace-command-line after launch may produce unexpected behavior or
;;; unexpected lack of behavior.

#+development
(defun tokenize-command-line (command-line-as-string)
  (let ((within-single-quote-p nil)
	(within-double-quote-p nil)
	(token-chars? nil)
	(tokens nil)
	(single-escape-p nil)
	(insert-empty-token-p nil))
    (macrolet ((store-token-chars ()
		 `(cond
		    (token-chars?
		     (push (concatenate 
			     'string 
			     (nreverse token-chars?)) 
			   tokens)
		     (setq token-chars? nil)
		     (setq insert-empty-token-p nil))
		    (insert-empty-token-p
		     (push "" tokens)
		     (setq insert-empty-token-p nil)))))
      (loop for index from 0 below (length command-line-as-string)
	    for this-char = (char command-line-as-string index)
	    do
	(case this-char
	  (#\\ (if (or within-single-quote-p
		       (not within-double-quote-p))
		   (cond
		     (single-escape-p
		      (push #\\ token-chars?)
		      (setq single-escape-p nil))
		     (t (setq single-escape-p t)))
		   (push #\\ token-chars?)))
	  (#\Space
	   (cond
	     ((or within-single-quote-p 
		  within-double-quote-p
		  single-escape-p)
	      (setq single-escape-p nil)
	      (push #\Space token-chars?))
	     (t (store-token-chars))))
	  (#\"
	   (cond 
	     (within-single-quote-p
	      (push #\" token-chars?))
	     (within-double-quote-p
	      (unless token-chars?
		(setq insert-empty-token-p t))
	      (setq within-double-quote-p nil))
	     (t (setq within-double-quote-p t))))
	  (#\'
	   (cond 
	     (within-double-quote-p
	      (push #\' token-chars?))
	     (within-single-quote-p
	      (unless token-chars?
		(setq insert-empty-token-p t))
	      (setq within-single-quote-p nil))
	     (t (setq within-single-quote-p t))))
	  (otherwise
	   (setq single-escape-p nil)
	   (push this-char token-chars?)))
	    finally
	      (store-token-chars)
	      (return (nreverse tokens))))))

;; For clarity in reading the test suite input and output, double-quotes are
;; indicated by ; and the backslash escape is indicated by |.  These characters
;; are substituted before the test and restored afterwards.  These characters
;; were chosen because they both delineate a command line in UNIX.

#+development
(defparameter test-suite-for-tokenize-command-line
  '(
    ;; vanilla
    ("-display and:0.0" ("-display" "and:0.0"))
    ("-display   and:0.0" ("-display" "and:0.0"))
    ("   -display   and:0.0" ("-display" "and:0.0"))
    ("-display   and:0.0   " ("-display" "and:0.0"))

    ;; vanilla double quotes
    ("-name ;myG2;" ("-name" "myG2"))
    ("-name ;my G2;" ("-name" "my G2"))
    ("-name ;my G2;  " ("-name" "my G2"))
    ("-name   ;my G2;" ("-name" "my G2"))
    ("-name   ;my G2;  " ("-name" "my G2"))

    ;; vanilla single quotes
    ("-name 'myG2'" ("-name" "myG2"))
    ("-name 'my G2'" ("-name" "my G2"))

    ;; mixed quotes
    ("-name ;my'G2';" ("-name" "my'G2'"))
    ("-name ;my'very'ownG2;" ("-name" "my'very'ownG2"))
    ("-name ;my;very;ownG2;" ("-name" "myveryownG2"))

    ;; empty quotes
    (";;" (""))
    ("''" (""))
    (";;;;;;" (""))
    ("    ;;;;;;" (""))
    (";;;;;;   " (""))
    ("-name ;;;;;;" ("-name" ""))
    ("-name ''''''" ("-name" ""))

    ;; escape char outside of quotes
    ("-name |hi" ("-name" "hi"))
    ("-name hi|there" ("-name" "hithere"))
    ("-name hi||there" ("-name" "hi|there"))
    ("-name | " ("-name" " "))

    ;; escape char works within single quotes
    ("-name '|;'" ("-name" ";"))
    ("-name ';'" ("-name" ";"))

    ;; escape char shouldn't work within double quotes
    ("-name ;|';" ("-name" "|'"))
    ("-name ;';" ("-name" "'"))

    ;; iterated single escapes
    ("-name ||" ("-name" "|"))
    ("||" ("|"))
    ("||||" ("||"))
    ("-name hi||there" ("-name" "hi|there"))
    ("-name hi||||there" ("-name" "hi||there"))
    ))

#+development
(defun test-tokenize-command-line ()
  (loop for (raw-input raw-expected-output) 
	    in test-suite-for-tokenize-command-line
	with all-correct-p = t
	do
    (macrolet ((transform-test-data (data)
		 `(substitute #\\ #\|
		    (substitute #\" #\; ,data))))
      (let* ((input (transform-test-data raw-input))
	     (output (tokenize-command-line input))
	     (expected-output 
	       (loop for token in raw-expected-output
			 collect (transform-test-data token))))
	(unless (equal expected-output output)
	  (error "TEST-TOKENIZE-COMMAND-LINE:~%~
                  input: ~s~%output: ~s~%expected output: ~s"
		 input
		 output
		 expected-output))))
	finally
	  (return all-correct-p)))


#+development
(defun replace-command-line (command-line-as-string)
  (setq unix-command-line-arguments
	(tokenize-command-line command-line-as-string))
  (copy-unix-line-arguments-as-text-strings)
  (loop for argument-cons on unix-command-line-arguments
 	as possible-keyword = (car argument-cons)
 	when (member possible-keyword '("-init" "-ok" "-kb")
 		     :test #'string-equal)
 	  do (let ((filename? (cadr argument-cons)))
 	       (unless filename?
 		 (warn "no filename argument for ~s" possible-keyword))
 	       (unless (probe-file filename?)
 		 (warn "~s, filename arg to ~s, does not exist"
 		       filename?
 		       possible-keyword))))
  (setq unix-command-line-argument-count
	(length unix-command-line-arguments)))

#+development
(defun replace-kb-in-command-line (kb-as-string)
  (unless (probe-file kb-as-string)
    (warn "~s, filename arg to -kb, does not exist" kb-as-string))
  (cond
    ((consp unix-command-line-arguments)
     (loop for argument-cons on unix-command-line-arguments
	   do (when (string-equal (car argument-cons) "-kb")
		(setf (cadr argument-cons) kb-as-string)
		(copy-unix-line-arguments-as-text-strings)
		(return))
	   finally 
	     (setq unix-command-line-arguments
		   (append unix-command-line-arguments
			   (list "-kb" kb-as-string)))
	     (copy-unix-line-arguments-as-text-strings)))
    (t (setq unix-command-line-arguments (list "g2" "-kb" kb-as-string))
       (copy-unix-line-arguments-as-text-strings)))
  unix-command-line-arguments)

#+development
(defun coalesce-unix-command-line-arguments ()
  (apply #'concatenate
	 'string
	 (loop for token in unix-command-line-arguments
	       for token-cons on unix-command-line-arguments
	       for last-token-p = (null (cdr token-cons))
	       collect token
	       unless last-token-p collect " ")))
  

;; This doesn't belong here, does it?!  If so, it's not easy to understand.  In
;; addition, this calls the command line facility too early to use gensym-cons
;; (or gensym-cons-function)!  Removed. (MHD 2/27/96)

;#+(and development lucid)
;(replace-command-line "g2 -display :0")


;;;; Environment Variables

;;; An `environment variable' is an location, considered as a string, which can
;;; be set from the host operating system and used to modify some aspect of G2
;;; behavior.  ...

;;; ...  this is complicated by the fact that operating systems often maintain
;;; two or more sets of variables, such as "logical names" and "symbols" in VMS,
;;; and "environment variables" and "shell variables" in UNIX.


;;; The external interface to acquiring environment variables:

;;; get-gensym-environment-variable (variable-as-string)
;;;   e.g., (get-gensym-environment-variable "G2_OK")
;;; Returns the value of the given environment variable as a simple text-string,
;;; or nil if there is no such variable, any error occurred, or the operating
;;; system does not support an environment variable facility.  
;;; NOTE WELL: The search for an environment variable is case-sensitive, unlike
;;; the keyword comparisons in the command-line argument facility defined above
;;; in this file.
;;; NOTE WELL: Unlike the interface functions for command-line arguments defined
;;; above, this interface function returns a simple text-string, which the
;;; caller must reclaim.

;;; read-number-for-gensym-environment-variable (variable-as-string)
;;;   e.g., (read-number-for-gensym-environment-variable "RGN1LMT")
;;; Returns a fixnum corresponding to the value of the given environment
;;; variable, or nil if there is no such variable, any error occurred, or the
;;; operating system does not support an environment variable facility.
;;; NOTE WELL: The search for an environment variable is case-sensitive, unlike
;;; the keyword comparisons in the command-line argument facility defined above
;;; in this file.

;; jh, 4/4/93.  Accessing environmental variables in any other way than through
;; this interface is denigrated, but not unheard-of.  As of this date, they have
;; been removed.







(def-gensym-c-function c-environment-var-strlen
		       (:fixnum-int "g2ext_environment_variable_strlen")
  ((:string name)))

(def-gensym-c-function c-return-environment-var
		       (:fixnum-int "g2ext_return_environment_variable")
  ((:string name) (:string buff)))

(defun foreign-get-environment-variable (name)
  (let ((length (c-environment-var-strlen name)))
    (if (=f length c-environment-var-strlen-failure)
	nil
	(let* ((buffer (obtain-simple-gensym-string length))
	       (result-code (c-return-environment-var name buffer)))
	  (cond
	    ((=f result-code gensym-environment-variable-success)
	     (prog1 (copy-null-terminated-string-as-text-string buffer)
	       (reclaim-gensym-string buffer)))
	    (t nil))))))






;;;; Obtaining the User's Home Directory from the Operating System

;;; ...  This information may or may not be stored in the command-line or in
;;; environment variables, so acquiring it is treated as a special case.

#+unused
(def-gensym-c-function c-user-homedir
		       (:fixnum-int "get_user_homedir")
  ((:string buff)))

;;; Foreign-get-user-homedir returns a new text-string if successful, nil
;;; otherwise.

#+unused
(defun foreign-get-user-homedir ()
  (let ((result-code
	  (c-user-homedir gensym-environment-variable-buffer)))
    (interface-to-foreign-environment-access result-code)))



;;; The function `windows-platform-p' is a predicate which determines the type of the
;;; platform on which current G2 is running. 

(defun windows-platform-p ()
  (or
    (eq g2-machine-type 'intelnt) ; the one actually used now
    (eq g2-machine-type 'windows) ; for compatibility
    (eq g2-machine-type 'alphant)
    (eq g2-machine-type 'windows95)
    (eq g2-machine-type 'dos)))

;SS_ERROR: 3 commented
#+translator
(def-gensym-c-function make-malloced-array
    (:object "g2rtl_make_malloced_array")
  ((:fixnum-int length)))

#+translator
(def-gensym-c-function free-malloced-array-internal
    (:void "g2rtl_free_malloced_array_internal")
  ((:object array-length)))

#+translator
(def-gensym-c-function malloc-string
    (:object "g2rtl_make_malloced_string")
  ((:fixnum-int length)))

;; The function update_gensym_error_buffer is a Gensym addition to the Chestnut
;; runtime library, in rtl/c/rtlcore/errors.c.  We suppress translator
;; complaints by declaring it to be a foreign function.  For a similar
;; technique, possibly something we should abstract someday, see
;; adjust-memory-areas-if-appropriate in OS-MEMORY.

#+(and chestnut-3 chestnut-trans)
(def-gensym-c-function c-update_gensym_error_buffer
                       (:void "g2rtl_update_gensym_error_buffer")
  ())

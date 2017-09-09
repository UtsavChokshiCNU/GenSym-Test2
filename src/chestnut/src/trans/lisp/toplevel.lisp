;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; toplevel.lsp -- file-level handling for the translator
;;;
;;; Author :  Sandra Loosemore
;;; Date   :  13 Jun 1990
;;; 
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;; Anything that belongs to the external interface to the Translator is
;;; declared in this file with a comment to indicate that it is external.
;;;
;;; The approach that is taken is that each file is translated with 
;;; TRANSLATE-FILE within the same running Lisp image.  During the 
;;; translation process, a database is built up on a per-application 
;;; basis that contains things like the definitions of constants and 
;;; symbol tables.  After all the source files have been translated, 
;;; this database must be dumped in a form that can be compiled and 
;;; linked with the other application files.

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/toplevel.lisp,v $"
 "$Revision: 1.10 $"
 "$Date: 2007/11/16 21:57:39 $")

;;; We don't want to have to look up the current function in the
;;; environment every time we add or reference variables.  Since
;;; it is something that infrequently changes anyway (it's rebound
;;; only as the codewalker enters a function definition), store it
;;; in a special variable.

(defvar *current-function* nil)


;;; This variable is used to ensure that calls to init functions
;;; are dumped in the correct order.

(defvar *translated-file-sequence-number* 0)


;;; This variable is used to help ensure that global variable
;;; definitions are always translated to the first file in which
;;; the global is encountered.

(defvar *current-translated-file* nil)


;;; Hash table of translated files
;;; Used to keep track of init functions.

(defparameter *translated-files* (make-hash-table :test #'equal))

(defun get-output-file (key)
  (let ((translated-file (translated-file key)))
    (translated-file-output-pathname translated-file)))

(defsetf get-output-file (key) (val)
  `(let ((translated-file (translated-file ,key)))
     (setf (translated-file-output-pathname translated-file) ,val)))

(defun get-output-files ()
  (let ((pns '()))
    (maphash #'(lambda (key val) 
		 (declare (ignore key))
		 (push (translated-file-output-pathname val)
		       pns))
	     *translated-files*)
    pns))
  
(defun init-function-p ()
  ;; See if an init function is required; should return T or NIL
  (not (not (or *initcode-statements* *initcode-local-constants*))))

(defun make-pathname-key (path)
  ;; Build a pathname for use as a hash table index, such that
  ;; "equivalent" pathnames are mapped to EQUAL pathname objects
  (merge-pathnames (make-pathname :version :newest :defaults path)))

;;; Make a "cookie" used to identify uniquely each invocation
;;; of TRANSLATE-FILE.
;;; This is used to ensure that exactly one definition for each
;;; special variable is dumped.

(defvar *translated-file-cookie* 0)

(defun make-translated-file-cookie () (incf *translated-file-cookie*))

(defun translated-file (input-file &optional (initfunction-name nil))
  ;; Get the translated-file descriptor for the next translated file.
  ;; If this file has been seen before, use its descriptor, but
  ;; update its invocation cookie.
  (let* ((path-key (make-pathname-key input-file))
	 (descriptor
	     (or (gethash path-key *translated-files*)
		 (setf (gethash path-key *translated-files*)
		       (make-translated-file)))))
    (setf (translated-file-cookie descriptor)
	  (make-translated-file-cookie))
    (cond (initfunction-name
	   (check-type initfunction-name string)
	   (let ((initsym (translated-file-init-function-name descriptor))
		 (initname nil))
	     (when (or (null initsym)
		       (null (setq initname (name-of-function-entry initsym)))
		       (not (string= initname initfunction-name)))
	       (setf initsym (gensym))
	       (setf (translated-file-init-function-name descriptor) initsym)
	       (setf (c-name-of-function-entry initsym) initfunction-name))))
	  ((not (translated-file-init-function-name descriptor))
	   (setf (translated-file-init-function-name descriptor)
		 (make-init-code-name input-file))))
    descriptor))

(defvar *non-toplevel-function-name-table*
  (make-hash-table :test 'equal))

(defun note-non-toplevel-function-definition (name)
  (setf (gethash name *non-toplevel-function-name-table*) t))

(define-translator-parameter *report-undefined-functions-unit* ':file)

;;; Keep track of undefined functions referenced within the file,
;;; and report them file-wide.

(defvar *undefined-functions* '())

(defun flag-undefined-function (name)
  (when (and (eq name 'ignore)
	     (not (eq *report-undefined-functions-unit* ':immediate)))
    (undefined-functions-warn (list name)))
  (unless (member name *undefined-functions* :test #'equal)
    (when (and (eq *report-undefined-functions-unit* ':immediate)
	       (not (gethash name *non-toplevel-function-name-table*)))
      (undefined-functions-warn (list name)))
    (push name *undefined-functions*)))

(defun report-undefined-functions ()
  (when *undefined-functions*
    (setq *undefined-functions*
	  (delete-if #'(lambda (name)
			 (gethash name *non-toplevel-function-name-table*))
		     *undefined-functions*))
    (setq *undefined-functions*
	  (sort *undefined-functions*
		#'(lambda (name1 name2)
		    (string<
		     (if (consp name1) (second name1) name1)
		     (if (consp name2) (second name2) name2)))))
    (when *undefined-functions*
      (undefined-functions-warn *undefined-functions*))
    (setq *undefined-functions* nil)))

(defun undefined-functions-warn (functions)
  (warn "The following referenced function~:[ has~;s have~] ~
           no top-level definition:~
           ~{~%~S~}"
	(cdr functions)
	functions))


;;; The Translator uses a slightly modified readtable in order
;;; to handle things like backquote properly.  See readtbl.lisp.
;;; This is part of the external interface to the Translator.
;;; Users who want to hack the readtable must hack *translator-readtable*
;;; instead of *readtable*.

(defparameter *translator-readtable* (copy-readtable nil))


;;; These variables are initialized in initenv.lisp.

(defvar *initial-c-names*)


;;; This variable belongs to the emitter.  It has to be rebound on
;;; a per-file basis.

(defvar *global-constants-emitted* nil)

;;; This is used by the emitter and gatherer. It specifies whether the
;;; translation of with-area and with-frontier (and hence
;;; with-dynamic-allocation and with-temporary-allocation) involves a catch.
;;; The old version does, the new version works like a special binding
;;; instead.
  
(define-translator-parameter *new-areas-and-frontiers* t)

;;; Control whether top-level comments are emitted.  The flag for
;;; semicolon comments is exported but not the one for sharp bar comments
;;; (because it's broken).
;;; *** We need to document that you need to set this to NIL if you want
;;; *** to assign some other meaning to these characters in the readtable.

(define-translator-parameter *preserve-comments* t)
(define-translator-parameter *emit-sharp-bar-comments-p* nil)


;;; Formatting flags
;;; These are defined in emit.lisp and dump.lisp.
;;; They are part of the external interface to the Translator.

(define-forward-variable-reference *header-lines*)
(define-forward-variable-reference *include-dates-in-headers*)
(define-forward-variable-reference *copyright-notice*)


;;; These are various defaults for pathnames.
;;; These are part of the external interface to the Translator.
;;; These probably need to be tweaked for different lisps and machines.

(define-translator-parameter *translate-file-input-type* "lisp")
(define-translator-parameter *translate-file-output-type* "c")
(define-translator-parameter *translate-file-header-type* "h")
(define-translator-parameter *translate-file-init-type* "top")
(define-translator-parameter *translate-file-prepare-type* "tpr")
(define-translator-parameter *translate-file-object-type* "o")


;;; The switch *TOPLEVEL-LOCATION* determines where the init function
;;; is written:
;;;    :local    - init function goes in filename.c
;;;    :include  - init function goes in filename.top, #included in toplevel.c
;;;    :separate - init function goes in T_filename.c
;;; This is part of the external interface to the Translator.

(define-translator-parameter *toplevel-location* :local)
(define-translator-parameter *symbol-init-statements-per-file* 1000)

;;; The switch *STATIC-CONSTANTS* determines how quoted constants
;;; are generated:
;;;    T   - Build all constants as static, initialized C data structures
;;;    NIL - Build all constants using explicit initialization code
;;; This is part of the external interface to the Translator.

;(define-translator-parameter *static-constants* nil)


;;; The switch *STATIC-FUNCTIONS* determines how statically-allocated,
;;; non-closed function objects (#'foo) are generated:
;;;    T   - Build all function objects as static, initialized
;;;          C data structures
;;;    NIL - Build all function objects using explicit initialization code
;;; This is part of the external interface to the Translator.

;(define-translator-parameter *static-functions* nil)


;;; The switch *LOCAL-SYMBOLS* determines how quoted symbols are built:
;;;    T   - Build symbols in top-level forms for each file
;;;          containing a reference
;;;    NIL - Dump symbols as global variables or table entries
;;; This is part of the external interface to the Translator.

;(define-translator-parameter *local-symbols* t)



;;; The switch *FUNCTION-SYMBOLS* determines whether a quoted symbol is
;;; always generated for each user-defined function:
;;;    T   - Always generate a symbol
;;;    NIL - Generate a symbol only if globally quoted
;;; This is part of the external interface to the Translator.

(define-translator-parameter *function-symbols* t)


;;; The switch *SPECIAL-SYMBOLS* determines whether a quoted symbol is
;;; always generated for each special variable:
;;;    T   - Always generate a symbol
;;;    NIL - Generate a symbol only if globally quoted
;;; This is part of the external interface to the Translator.

(define-translator-parameter *special-symbols* t)

;;; The switch *INITIAL-SYMBOLS* is used to control whether the entire
;;; RTL is linked in, or only the parts apparently needed by the application.
;;;  T -  Link entire RTL
;;;  NIL -  Only those functions called within the application, and those
;;;  whose names occur in quoted structure in the application, are linked in.
;;;  Names of other functions will still exist as symbols in the lisp package,
;;;  but they will be funbound. In a future version, RTL symbols not referenced
;;;  by the application may not be present at runtime at all.

(define-translator-parameter *initial-symbols* t)

;;; The switch *NIL-IS-ZERO* determines whether NIL is represented
;;; in C as 0.  (If so, then TRUEP can be elided, but list accessors
;;; such as CAR evaluate their arguments multiple times and are not
;;; lvalues.)
;;;    T   - NIL is represented as a symbol.
;;;    NIL - NIL is represented as 0.
;;; This is part of the external interface to the Translator.

(define-translator-parameter *nil-is-zero* t)


;;; These switches determine whether, by default, expanders
;;; for macros, type definitions, etc. are included in the image.
;;; (These might be used by runtime calls to EVAL or TYPEP.)
;;; The flag can be overridden by the proclamation
;;; TX:INCLUDE-IN-RUNTIME or TX:OMIT-FROM-RUNTIME.
;;;    T   - Include all expanders in the image, unless proclaimed
;;;          OMIT-FROM-RUNTIME.
;;;    NIL - Omit all expanders in the image, unless proclaimed
;;;          INCLUDE-FROM-RUNTIME.
;;; This is part of the external interface to the Translator.

(define-translator-parameter *include-macro-expanders* t)

;; currently not supported:
(define-translator-parameter *include-setf-expanders* t)
(define-translator-parameter *include-type-expanders* t)


;;; The switch *SOURCE-OPTIMIZATIONS* determines whether optimizations
;;; which reduce the correspondence between the original and generated
;;; sources, such as tail-recursion elimination.

(define-translator-parameter *source-optimizations* nil)


;;; There are a few places where the semantics of ANSI common lisp diverges
;;; from CLtL common lisp, notably in the scoping of declarations.
;;; This is part of the external interface to the Translator.

(define-translator-parameter *ansi-semantics* t)


;;; Some of the potential error/warning situations we check for are 
;;; annoying to get warnings about all the time, so use this switch to
;;; turn them on and off.
;;; This is part of the external interface to the Translator.

(define-translator-parameter *verbose-warnings* nil)


;;; Should we make documentation strings available for the DOCUMENTATION
;;; function at runtime?
;;; *** This ought to be part of the external interface to the Translator,
;;; *** but the RTL doesn't implement (SETF DOCUMENTATION) yet so it
;;; *** doesn't make sense to advertise this feature.

(define-translator-parameter *record-documentation-for-runtime* nil)

;;; Some C compilers choke on fairly simple expressions containing
;;; the comma operator. If this switch is set to t, the translator
;;; will attempt to avoid use of the comma operator when possible.
;;; This is part of the external interface to the Translator.

(define-translator-parameter *avoid-comma-operator* nil)

;;; Some C compilers are unhappy with files containing large numbers of
;;; #define's. If this switch is set to T, the #define's for Ffoo in userfuns.h
;;; will be suppressed, and the Translator will generate
;;; SYMBOL_FUNCTION(Qfoo) directly instead of Ffoo when referring to a function
;;; object. A separate version of initfuns.h, small-initfuns.h, will
;;; be generated that does not contain the #define's for Ffoo for
;;; Common Lisp functions foo.
;;; This is part of the external interface to the Translator.

(define-translator-parameter *use-function-macros* t)

(define-translator-parameter *initial-compile-time-too* nil)

(define-translator-parameter *if-exists-action*
  :supersede)

(define-translator-parameter *if-does-not-exist-action*
  :create)

;From emit.lisp
(defmacro with-output-stream (stream &body forms)
  `(with-output-stream1 ,stream #'(lambda () ,@forms)))

(defmacro with-open-file* ((stream filename &rest options)
			   predicate
			   &body forms)
  `(with-open-stream* (,stream (open ,filename ,@options))
     ,predicate
     ,@forms))

(defmacro with-open-stream* ((stream form) predicate &body forms)
  (let ((abort-p (make-symbol "ABORT-P"))
	(saved-stream (make-symbol "SAVED-STREAM")))
    `(let ((,abort-p t)
	   (,saved-stream nil))
       (unwind-protect
	    (multiple-value-prog1
		(let ((,stream (setq ,saved-stream
				     (when ,predicate ,form))))
		  ,@forms)
	      (setq ,abort-p nil))
	 (when ,saved-stream
	   (close ,saved-stream :abort ,abort-p))))))

;;; TRANSLATE-FILE is part of the external interface to the Translator.
;;; If output-file is NIL, then only the top-level, compile-time 
;;; definitions from the file will be loaded and no code for non-top-level
;;; forms will be produced or emitted.

(defun translate-file (input-file
			&key (output-file nil output-file-p)
			     (init-file nil init-file-p)
			     (h-file nil h-file-p)
			     (prepare-file nil)
			     (verbose *compile-verbose*)
			     (relative-to-directory nil)
			     (print *compile-print*)
			     (record-documentation
			         *record-documentation-for-runtime*)
			     (initfunction-name nil)
			 &aux default-pathname)
  (setq default-pathname (make-pathname :defaults *default-pathname-defaults*
					:type *translate-file-input-type*))
  (setq input-file (merge-pathnames input-file default-pathname))
  (setq output-file (merge-output-file output-file output-file-p input-file))
  (unless relative-to-directory
    (setq relative-to-directory output-file))
  (setq h-file (merge-output-file h-file h-file-p input-file
				  *translate-file-header-type*))
  (setq prepare-file (merge-output-file prepare-file t input-file
					*translate-file-prepare-type*))
  (setq init-file
	(ecase *toplevel-location*
	  (:local nil)
	  (:include
	   (merge-output-file init-file init-file-p input-file
			      *translate-file-init-type* ""))
	  (:separate
	   (merge-output-file init-file init-file-p input-file
			      *translate-file-output-type* "T_"))))
  (if verbose
      (if output-file
	  (format t "~%Translating ~s to output file ~s."
		  (namestring input-file)
		  (namestring output-file))
	  (format t "~%Preparing file ~s." (namestring input-file))))
  (let ((*compile-time-only*          (not output-file))
	(*preserve-comments*          (if output-file
					  *preserve-comments*
					  nil))
	(*current-translated-file*
	 (translated-file input-file initfunction-name))
	(*verbose* verbose)
	(*initcode-local-constants*      nil)
	(*initcode-local-constants-last* nil)
	(*initcode-statements*           nil)
	(*initcode-statements-last*      nil)
	(*initcode-functions*            nil)
	(*initcode-functions-last*       nil)
	(*global-constants-emitted*      nil)
	(*record-documentation-for-runtime*  record-documentation)
	(*header-lines*
	 (when output-file
	   (append *header-lines*
		   (list (sformat "#include \"~A\""
				  (namestring* h-file
					       :relative-to-directory
					       relative-to-directory))))))
	(*compile-print*              print)
	(*compile-file-pathname*      input-file)
	(*compile-file-truename*      (truename input-file))
	(*features*                   (adjoin :translating *features*))
	(*readtable*                  *translator-readtable*)
	(*package*                    *package*)
	;;avoid annoying "defined more than once" messages
	(*load-pathname* nil)
	#+lispworks (lw:*handle-warn-on-redefinition* :quiet)
	#+lispworks (lw:*redefinition-action* :quiet)
	#+(and allegro (not allegro-v4.1)) (excl:*record-source-files* nil)
	#+(and allegro allegro-v4.1) (excl:*record-source-file-info* nil)
	#+lucid (lcl:*source-pathname* nil)
	#+lucid (lcl:*redefinition-action* nil))
    (declare (special *verbose*))
    (let ((*current-function*
	   (new-function-record
	     (translated-file-init-function-name
	       *current-translated-file*)
	     :init)))
      (reset-constant-tables t)
      (with-translator-message (unless verbose
				 (format nil "~S"
					 (enough-namestring input-file
							    default-pathname)))
	(with-c-name-table :file
	  (with-open-file (input-stream input-file :direction :input)
	    (if *compile-time-only*
		(with-open-file*
		    (*prepare-stream* prepare-file
				      :direction :output
				      :if-exists *if-exists-action*
				      :if-does-not-exist
				      *if-does-not-exist-action*)
		  prepare-file
		  (process-input-forms input-stream))
		(with-open-file (output output-file
					:direction :output
					:if-exists *if-exists-action*
					:if-does-not-exist
					*if-does-not-exist-action*)
		  (with-output-stream output
		    (emit-file-header input-file output-file)
		    (process-input-forms input-stream)
		    (setf (translated-file-init-pathname 
			   *current-translated-file*)
			  nil)
		    (when (setf (translated-file-init-function-p
				 *current-translated-file*)
				(init-function-p))
		      (ecase *toplevel-location*
			(:local
			 (do-init-function-backend-processing))
			(:include
			 (setf (translated-file-init-pathname
				*current-translated-file*)
			       init-file)
			 (with-open-file (output init-file
						 :direction :output
						 :if-exists *if-exists-action*
						 :if-does-not-exist
						 *if-does-not-exist-action*)
			   (with-output-stream output
			     (emit-file-header input-file init-file
					       nil " (top-level forms)")
			     (do-init-function-backend-processing)
			     (emit-file-trailer))))
			(:separate
			 (with-open-file (output init-file
						 :direction :output
						 :if-exists *if-exists-action*
						 :if-does-not-exist
						 *if-does-not-exist-action*)
			   (with-output-stream output
			     (emit-file-header input-file init-file
					       t " (top-level forms)")
			     (do-init-function-backend-processing)
			     (emit-file-trailer))))))
		    (emit-file-trailer)))))))
      (unless *compile-time-only*
	(dump-header-file h-file relative-to-directory))
      ;; Add to output-files
      (when output-file 
	(let ((wd *default-pathname-defaults*))
	  (setf (get-output-file (merge-pathnames input-file wd))
		(merge-pathnames output-file wd))))
      (when (eq *report-undefined-functions-unit* ':file)
	(report-undefined-functions))
      (reset-constant-tables t)
      (if (and output-file init-file)
	  (list output-file init-file)
	  output-file))))

(defun show-translation (toplevel-form &key
			 (process-p t)
			 (record-documentation
			  *record-documentation-for-runtime*)
			 (initfunction-name nil))
  (let ((*current-translated-file*
	 (make-translated-file
	  :cookie (make-translated-file-cookie)
	  :init-function-name (or initfunction-name
				  (make-symbol "INITFUNCTION"))))
	(*header-lines*
	 (list (first *header-lines*)))
	(*compile-print*            nil)
	(*compile-time-only*             nil)
	(*preserve-comments*             nil)
	(*verbose*                       t)
	(*initcode-local-constants*      nil)
	(*initcode-local-constants-last* nil)
	(*initcode-statements*           nil)
	(*initcode-statements-last*      nil)
	(*initcode-functions*            nil)
	(*initcode-functions-last*       nil)
	(*global-constants-emitted*      nil)
	(*undefined-functions*           nil)
	(*record-documentation-for-runtime*  record-documentation)
	(*features*                   (adjoin :translating *features*))
	(*readtable*                  *translator-readtable*)
	(*package*                    *package*))
    (declare (special *verbose*))
    (let ((*current-function*
	   (new-function-record
	     (translated-file-init-function-name
	       *current-translated-file*)
	     :init)))
      (reset-constant-tables t)
      (with-c-name-table :file
	(when process-p
	  (let ((*compile-time-only* t))
	    (translate-toplevel-form
	     toplevel-form *default-global-environment*
	     *initial-compile-time-too*)) )
	(let ((output (with-output-to-string (output)
			(with-output-stream output
			  (translate-toplevel-form
			   toplevel-form *default-global-environment*
			   *initial-compile-time-too*)
			  (do-init-function-backend-processing)))))
	  (with-output-stream *standard-output*
	    (emit-header-file)
	    (emit-output-line nil t))
	  (write-string output *standard-output*)
	  (values))))))

(defun merge-output-file (output-file output-file-p input-file
				      &optional type name-prefix)
  ;; Produce output file pathname
  (unless (and output-file-p (null output-file))
    (let ((file (make-pathname
		 :type (or type *translate-file-output-type*)
		 :name (if name-prefix
			   (concatenate 'string
					name-prefix (pathname-name input-file))
			   (pathname-name input-file))
		 :defaults input-file)))
      (if (and output-file (not (eq output-file 't)))
	  (merge-pathnames output-file file)
	  file))))


;;; Perform preliminary top-level code walk to determine function
;;; calling sequences, etc.
;;; This part of the external interface to the Translator.

(defun prepare-file (input-file &rest keys)
  (apply #'translate-file input-file :output-file nil :init-file nil keys))


;;; Re-initialize the Translator.  Restore all state variables to their
;;; initial values, containing only information about things that we
;;; provide as part of the Translator and no application-specific information.
;;; This is part of the external interface to the Translator.

(define-translator-parameter *warn-about-new-interface-p* nil)

(define-translator-parameter *lisp-symbol-to-foreign-string-method* nil)
(define-translator-parameter *remove-leading-underscore-from-foreign-string-p* t)
(define-translator-parameter *member-to-or-limit* 4)
(define-translator-parameter *rtl-includes-gc-p* t)
(define-translator-parameter *integer-constants-are-long-p* nil)

(defvar *global-c-lines* nil)

(defun initialize-translator ()
  (when *warn-about-new-interface-p*
    (warn "You should use the macro ~S instead of calling ~S"
	  'with-translator-environment 'initialize-translator))
  (free-translator-environment *default-global-environment*)
  (setq *default-global-environment*
	(copy-translator-environment *initial-global-environment*))
  (setq tutil::*c-names* (tutil::get-initial-c-names))
  (setq *translated-files* (make-hash-table :test #'equal))
  (setq *global-c-lines* nil)
  (clrhash *non-toplevel-function-name-table*)
  (setq *undefined-functions* nil)
  nil)

#-SBCL (declaim (special *load-pathname*))

(defmacro with-translator-environment (globalp &body forms)
  (unless (symbolp globalp)
    (warn "Check the call to ~S" 'with-translator-environment))    
  `(flet ((with-translator-environment-body ()
	    ,@forms))
     (if ,globalp
	 (with-translator-environment-body)
	 (let ((*default-global-environment*
		(copy-translator-environment *initial-global-environment*))
	       (*translated-files* (make-hash-table :test #'equal))
	       (*global-c-lines* nil)
	       (tutil::*c-names* (tutil::get-initial-c-names))
	       (*undefined-functions* nil)
	       (*non-toplevel-function-name-table*
		(make-hash-table :test #'equal)))
	   (unwind-protect
		(with-translator-environment-body)
	     (free-translator-environment *default-global-environment*))))))

(defun translate-files (files &key
			      (dump-headers t)
			      (globalp nil)
			      (write-prepare-files-p nil)
			      ((:default-pathname *default-pathname-defaults*)
			       *default-pathname-defaults*))
  (setq files (mapcar #'merge-pathnames files))
  (with-translator-environment globalp
    (flet ((simple-prepare-file (file)
	     (prepare-file file :prepare-file write-prepare-files-p))
	   (simple-translate-file (file)
	     (translate-file file)))
      (mapc #'simple-prepare-file files)
      (mapc #'simple-translate-file files))
    (when (eq *report-undefined-functions-unit* ':all)
      (report-undefined-functions))
    (when dump-headers
      (write-header-files)
      (write-main-file)
      (write-makefile-file))))

;;; Decide what to call the initialization function for the file.

(defun make-init-code-name (input-file)
  (make-symbol (sformat "~a-INIT" (pathname-name input-file))))


;;; Loop reading forms from the file and passing them to the top-level
;;; form walker.  Process comments in the file appropriately.

(defvar *count-of-toplevel-reads* 0)
(defvar *position-in-file-before-read* nil)

(defun process-input-forms (input-stream)
  (let ((*count-of-toplevel-reads* 0)
	(*position-in-file-before-read* 0)
	(eof (cons nil nil))
	(form nil))
    (loop
      (case (type-of-next-printing-char-with-checking input-stream)
	(:eof (return nil))
	(:semicolon (process-toplevel-semicolon-comments input-stream))
	(:sharp-bar (process-toplevel-sharp-bar-comments input-stream))
	(t (setq *position-in-file-before-read* (file-position input-stream))
	   (when (eq (setf form (read input-stream nil eof)) eof)
	     (return nil))
	   (incf *count-of-toplevel-reads*)
	   (translate-toplevel-form
	    form *default-global-environment*
	    *initial-compile-time-too*))))))

;;; Helper functions for the above.
;;; The approach we take for dealing with comments is to peek ahead at the
;;; input stream for comment characters appearing between forms at top-level.
;;; Since we are not using the readtable, if you want to hack the readtable
;;; to assign some other meaning to characters that are normally comment 
;;; characters, you must also turn off the variables that control the
;;; peeking for comments.  Also, there are some weirdnesses in that if you
;;; have things like #+ in the input stream, comments that appear to be 
;;; at top-level might not be seen.

(defun process-toplevel-semicolon-comments (input-stream)
  (let ((comment-strings nil)
	comment-string
	eof-p
	char-type
	relevant-whitespace-chars-skipped)
    (loop
      (move-to-start-of-comment input-stream)
      (multiple-value-setq (comment-string eof-p)
	(read-line input-stream nil ""))
      (push comment-string comment-strings)
      (when eof-p
	(return (emit-toplevel-comments (nreverse comment-strings))))
      (multiple-value-setq (char-type relevant-whitespace-chars-skipped)
	(type-of-next-printing-char-with-checking input-stream '(#\Newline)))
      (when (or (not (eq char-type :semicolon))
		relevant-whitespace-chars-skipped)
	(return (emit-toplevel-comments (nreverse comment-strings)))))))

(defun process-toplevel-sharp-bar-comments (input-stream)
  (let (char
	(comment-strings nil)
	(eof (cons nil nil))
	(sharp-bars-encountered 0)
	(bar-sharps-encountered 0))
    (block comment-strings
      (loop
        (let ((comment-string-chars nil))
	  (loop
	    (setf char (peek-char nil input-stream nil eof))
	    (cond ((eq char eof)
		   (error
		     "End of file was reached within a sharp-bar comment"))
		  ((sharp-bar-p char input-stream)
		   (incf sharp-bars-encountered)
		   (read-char input-stream)
		   (read-char input-stream))
		  ((bar-sharp-p char input-stream)
		   (incf bar-sharps-encountered)
		   (read-char input-stream)
		   (read-char input-stream)
		   (when (eq sharp-bars-encountered bar-sharps-encountered)
		     (push comment-string-chars comment-strings)
		     (return-from comment-strings)))
		  ((eql char #\Newline)
		   (read-char input-stream)
		   (push comment-string-chars comment-strings)
		   (return))
		  (t (push char comment-string-chars)
		     (read-char input-stream)))))))
    (emit-toplevel-comments
        (mapcar #'(lambda (comment-string-chars)
		      (coerce (nreverse comment-string-chars) 'string))
		(nreverse comment-strings)))))

(defun type-of-next-printing-char-with-checking
  (input-stream &optional skipped-whitespace-chars)
  (let ((eof (cons nil nil))
	(whitespace-chars-encountered nil)
	char)
    (loop
      (setf char (peek-char nil input-stream nil eof))
      (if (not (whitespace-char-p char))
	  (return
	    (values
	      (cond ((eq char eof) :eof)
		    ((and *preserve-comments*
			  (eql char #\;))
		     :semicolon)
		    ((and *emit-sharp-bar-comments-p*
			  (sharp-bar-p char input-stream))
		     :sharp-bar)
		    (t t))
	      whitespace-chars-encountered))
	  (progn
	    (read-char input-stream)
	    (when (member char skipped-whitespace-chars)
	      (pushnew char whitespace-chars-encountered)))))))

(defun move-to-start-of-comment (input-stream)
  (let (char)
    (loop
      (unless (eql (setf char (read-char input-stream nil nil)) #\;)
	(unread-char char input-stream)
	(return)))))

(defun whitespace-char-p (char)
  (member char '(#\Tab #\Space #\Page #\Return #\Newline #\Linefeed)))

(defun sharp-bar-p (char input-stream)
  (two-char-chord-p #\# #\| char input-stream))

(defun bar-sharp-p (char input-stream)
  (two-char-chord-p #\| #\# char input-stream))


;;; There's a fundamental problem here.  Since we need to peek ahead
;;; two characters, we can't use peek-char (which only allows a one-character
;;; lookahead) to do the peeking.  So this uses file-position, but the
;;; CL standard permits file-position not to "work".  This is not something
;;; that is strictly a matter of it working in some implementations and
;;; not others; it might work for some particular *streams* in a particular
;;; implementation and not for others, and we have no way to determine
;;; whether it will actually work.
;;; For now we have left this code in place but not advertised the flag
;;; that enables it.  Maybe someday we will figure out how to solve the
;;; problem.  It's probably not important enough to spend a lot of time
;;; on unless we get specific complaints from customers about it.

(defun two-char-chord-p (char1 char2 input-char input-stream)
  (if (eql input-char char1)
      (let ((current-pos (file-position input-stream)))
	(read-char input-stream)
	(if (eql (peek-char nil input-stream nil nil) char2)
	    (file-position input-stream current-pos)
	    (progn (file-position input-stream current-pos)
		   nil)))))

;;; Version in call-information.lisp does this, plus some
;;; call-information-related stuff that we don't do in SBCL.
;;; So we use this stub for SBCL, where we don't load call-infomation.
#-lucid ; old: #+sbcl
(defun set-function-record-unique-name (record name)
  (setf (function-record-unique-name record) name)
  name)

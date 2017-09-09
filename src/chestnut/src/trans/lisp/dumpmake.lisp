;;; -*- Mode: LISP; Package: TIMPL; Syntax: Common-Lisp -*-

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/dumpmake.lisp,v $"
 "$Revision: 1.3 $"
 "$Date: 2007/06/22 19:50:28 $")

(define-translator-parameter *target-pathname-syntax*
  #+MCL :mac
  #+DOS :dos
  #+UNIX :unix
  #+VMS :vms
  #+genera :unix ; lisp machines don't have make, anyway
  #-(or mcl dos unix vms genera) :unix)

(define-translator-parameter *compile-into-source-directory-p* nil)

(defvar *current-target-pathname-syntax* nil)
(defvar *include-host-p*)
(defvar *include-device-p*)
(defvar *device-terminator*)
(defvar *absolute-directory-start*)
(defvar *relative-directory-start*)
(defvar *directory-separator*)
(defvar *directory-terminator*)

(defun update-target-pathname-parameters ()
  (unless (eq *target-pathname-syntax* *current-target-pathname-syntax*)
    (multiple-value-setq
	(*include-host-p*
	 *include-device-p*
	 *device-terminator*
	 *absolute-directory-start*
	 *relative-directory-start*
	 *directory-separator*
	 *directory-terminator*)
      (ecase *target-pathname-syntax*
	(:unix   (values nil nil "" "/" "" "/" "/"))
	(:mac    (values nil nil "" "" ":" ":" ":"))
	(:genera (values t   nil "" "" ">" ">" ">"))
	(:dos    (values nil t   "" "" "\\" "\\" "\\")) ; is this right?
	;; maybe the 5th value isn't right.
	(:vms    (values nil t   "" "[" "[.." "." "]"))))
    (setq *current-target-pathname-syntax* *target-pathname-syntax*))
  *target-pathname-syntax*)
      
#+mcl
(progn

(define-translator-parameter *mac-to-unix-illegal-characters*
  '(#\space #\newline #\( #\) #\' #\&))

(defun convert-mac-file-name (name)
  (if (stringp name)
      (map 'string
	   #'(lambda (char)
	       (if (and (standard-char-p char)
			(not (member char
				     *mac-to-unix-illegal-characters*)))
		   char
		   #\_))
	   name)
      name))

)

;;; All the pathnames that appear in c files, h files and the Makefile 
;;; are converted to strings with namestring*.

(defun namestring* (pathname &key directory-only-p
			     relative-to-directory
			     symbolic-directory user-file-p name type)
  (update-target-pathname-parameters)
  (let ((dir (apply #'concatenate 'string 
		    (nconc (when (and *include-host-p* pathname)
			     (list (host-namestring pathname) ":"))
			   (when (and *include-device-p* pathname)
			     (list (pathname-device pathname) ":"))
			   (namestring*-directory-list
			    pathname relative-to-directory
			    symbolic-directory user-file-p)))))
    (values (if directory-only-p
		dir
		(let ((name (or name (pathname-name pathname)))
		      (type (or type (pathname-type pathname))))
		  #+mcl
		  (when (eq *target-pathname-syntax* :unix)
		    (setq name (convert-mac-file-name name))
		    (setq type (convert-mac-file-name type)))
		  (concatenate 'string dir name "." type)))
	    dir)))

(defun namestring*-directory-list
    (pathname relative-to-directory symbolic-directory user-file-p)
  (when (and relative-to-directory
	     (or (and *include-host-p*
		      (not (eq (pathname-host pathname)
			       (pathname-host relative-to-directory))))
		 (and *include-device-p*
		      (not (eq (pathname-device pathname)
			       (pathname-device relative-to-directory))))))
    (setq relative-to-directory nil))
  (let (#+mcl (unix-p (eq *target-pathname-syntax* :unix)))
    (if (and symbolic-directory
	     (not (and *compile-into-source-directory-p*
		       user-file-p)))
	(list (sformat "$(~A)" symbolic-directory))
	(let* ((directory (if relative-to-directory
			      (directory-diff pathname
					      relative-to-directory)
			      (or (and pathname
				       (pathname-directory pathname))
				  '(:relative))))
	       (dlist 
		(mapcan #'(lambda (dname)
			    #+mcl
			    (when unix-p
			      (setq dname (convert-mac-file-name dname)))
			    (list dname *directory-separator*))
			(cdr directory))))
	  (unless (and (eq ':relative (car directory))
		       (null (cdr directory)))
	    (cons (if (eq ':absolute (car directory))
		      *absolute-directory-start*
		      *relative-directory-start*)
		  (nconc (butlast dlist)
			 (list *directory-terminator*))))))))

(defun directory-diff (pathname defaults)
  (let ((pdir (or (pathname-directory pathname)
                  '(:relative)))
	(ddir (or (pathname-directory defaults)
                  '(:relative))))
    (if (or (atom pdir) (atom ddir)
	    (not (eq (car pdir) (car ddir))))
	pdir
	(let ((pdir-tail (cdr pdir))
	      (ddir-tail (cdr ddir)))
	  (loop (unless ddir-tail
		  (return (cons ':relative pdir-tail)))
		(unless (and pdir-tail
			     (equal (car pdir-tail)
				    (car ddir-tail)))
		  (return pdir))
		(pop pdir-tail) (pop ddir-tail))))))

(define-translator-parameter *main-pathname-default-name*
  "main"
  "Default pathname-name for C main file.")

(define-translator-parameter *main-pathname-default-type*
  *translate-file-output-type*
  "Default pathname-type for C main file.")

(define-translator-parameter *makefile-pathname-default-name*
  "Makefile"
  "Default pathname-name for the Makefile file.")

(define-translator-parameter *makefile-pathname-default-type*
  #+genera "" #-genera nil
  "Default pathname-type for the Makefile file.")

(define-translator-parameter *cc-default*			
  "cc"
  "Default call to C compiler")

(define-translator-parameter *cc-flags-default*		
  '(:debug)
  "Default flags to C compiler. -g in unix.")

(define-translator-parameter *executable-filename-default*		
  "lisptoc"
  "Default name of C executable file produced.")

(define-translator-parameter *link-files*
  '()
  "Default user files to link into application")

(define-translator-parameter *all-cc-flags*
  '(;;(cc-flags-key FLAGS-prefix cc-argument-string)
    (:debug       "G"   "-g")
    (:optimize    "O"   "-O")
    (:profile     "P"   "-p")
    #+unix
    (:gprofile    "PG"  "-pg")
    (:no-warnings "W"   "-w")))

;;;
;;; Makefile dumper
;;;

(defun write-makefile-file
    (&key (default-pathname	 (dumper-default-pn *dumper-pathnames*))
	  (pathname
	   (make-pathname :defaults default-pathname
			  :name *makefile-pathname-default-name*
			  :type *makefile-pathname-default-type*))
	  (main-pathname
	   (make-pathname :defaults default-pathname
			  :name *main-pathname-default-name*
			  :type *main-pathname-default-type*))
	  (translated-pathnames	 ())
	  (symbols-pathname	 (dumper-symbols-pn *dumper-pathnames*))
	  (symbol-names-pathname (dumper-symbol-names-pn *dumper-pathnames*))
	  (functions-pathname	 (dumper-functions-pn *dumper-pathnames*))
	  (callables-pathname	 (dumper-callables-pn *dumper-pathnames*))
	  (symbol-init-code-pathname
	   (dumper-symbol-init-code-pn *dumper-pathnames*))
	  (variables-pathname	 (dumper-variables-pn *dumper-pathnames*))
	  (init-pathname	 (dumper-init-pn *dumper-pathnames*))
	  #+translator-supports-clos
	  (slot-index-pathname	 (dumper-slot-index-pn *dumper-pathnames*))
	  (structures-pathname	 (dumper-structures-pn *dumper-pathnames*))
	  (user-header-pathname	 (dumper-user-header-pn *dumper-pathnames*))
	  (bin-directory       (make-pathname :defaults default-pathname
					      :directory '(:relative "BIN")))
	  (obin-directory      (make-pathname :defaults default-pathname
					      :directory '(:relative "OBIN")))
	  (header-directory      nil)
	  (executable-filename   *executable-filename-default*)
	  (oexecutable-filename  nil)
	  (cc			 *cc-default*)
	  (cc-flags		 *cc-flags-default*)
	  (link-files            *link-files*)
	  (include-repl		 nil)
	  (verbose 		 *compile-verbose*))
  (declare (ignore callables-pathname
		   variables-pathname
		   symbol-names-pathname))
  "Dump Makefile to file PATHNAME."
  (check-type oexecutable-filename (or null string))
  (check-type cc string)
  (check-type cc-flags (satisfies valid-cc-flags-p))
  (check-type link-files (satisfies valid-lib-paths-p))
  (unless oexecutable-filename
    (setq oexecutable-filename 
	  (concatenate 'string "o" executable-filename)))
  (if obin-directory
      (check-type obin-directory (or string pathname))
      (setq obin-directory bin-directory))
  ;; Everything form here on down is a true pathname.
  (let ((translated-pathnames (or translated-pathnames
				  (translated-output-pathnames)))
	(*default-pathname-defaults* default-pathname))
    ;; Warn if no files have been translated.
    (when (null translated-pathnames)
      (cerror "Will write Makefile with no translated files."
	      "Writing Makefile with no translated files."))
    (let ((simple-localinit-pathnames
	   (append (mapcar #'merge-pathnames
			   (list main-pathname
				 symbols-pathname
				 init-pathname))
		   (if (listp symbol-init-code-pathname)
		       (mapcar #'merge-pathnames symbol-init-code-pathname)
		       (list (merge-pathnames symbol-init-code-pathname)))))
	  (localinit-pathnames 
	   (mapcar #'merge-pathnames
		   (list functions-pathname
			 #+translator-supports-clos
			 slot-index-pathname)))
	  (localinit-header-pathnames
	   (mapcar #'merge-pathnames
		   (list user-header-pathname
			 functions-pathname
			 structures-pathname
			 #+translator-supports-clos
			 slot-index-pathname))))
      (setq pathname (merge-pathnames pathname))
      (setq main-pathname (merge-pathnames main-pathname))
      (setq bin-directory (parse-namestring bin-directory))
      (setq obin-directory (parse-namestring obin-directory))
      (when header-directory
	(setq header-directory (parse-namestring header-directory)))
      (when verbose 
	(format t "~%Writing ~A..." (enough-namestring pathname)))
      (update-target-pathname-parameters)
      (with-open-file (stream pathname
			      :direction :output 
			      :if-exists *if-exists-action*
			      :if-does-not-exist *if-does-not-exist-action*)
	(output-makefile-header stream executable-filename)
	(output-makefile-directory-macros 
	 stream bin-directory obin-directory header-directory 
	 cc-flags pathname)
	(output-makefile-cc-macros stream cc cc-flags header-directory)
	(output-makefile-target-macros 
	 stream executable-filename oexecutable-filename cc-flags)
	(output-makefile-file-macros
	 stream pathname 
	 (append simple-localinit-pathnames localinit-pathnames)
	 localinit-header-pathnames translated-pathnames
	 include-repl)
	(output-makefile-link-rule stream link-files) 
	(output-optimized-target stream)
	(output-makefile-compile-rules
	 stream pathname 
	 simple-localinit-pathnames localinit-pathnames translated-pathnames)
	(terpri stream))
      (if verbose (values) :done))))
		 
(defun output-makefile-comment (stream comment)
  (format stream "~2%# ~A~%" comment))

(defun output-makefile-header (stream executable-filename)
  (dotimes (i *margin-column*) (write-char #\# stream))
  (format stream "~%#")
  (format stream "~%#~5TMakefile for ~A" executable-filename)
  (and *include-dates-in-headers* 
       (format stream "~%#~5T~A"  (date-and-time-string)))
  (format stream "~%#~5T~A" *copyright-notice*)
  (format stream "~%#~%#")
  (dotimes (i *margin-column*) (write-char #\# stream)))

(defmacro debug-p (flags) 
  `(not (null (member :debug ,flags :test #'eq))))

(defun output-makefile-directory-macros (stream bin-directory obin-directory
						header-directory cc-flags make-pn)
  (output-makefile-comment stream "Directories")
  (format stream "~2%RUNTIMEDIR = $(RUNTIME)~A" *directory-separator*)
  (format stream "~%LIBDIR = $(RUNTIMEDIR)libdir~A"
	  *directory-terminator*)
  (format stream "~%INCLUDEDIR = $(RUNTIMEDIR)include~A"
	  *directory-terminator*)
  #-translator-supports-clos
  (progn
    (format stream "~%GLIB = $(LIBDIR)runtime.a ~
                    ~%OLIB = $(LIBDIR)oruntime.a")
    (format stream "~%LIB = ~:[$(OLIB)~;$(GLIB)~]" (debug-p cc-flags)))
  #+translator-supports-clos
  (progn
    (format stream "~%GCLOSLIB = $(LIBDIR)clos-runtime.a~
                    ~%OCLOSLIB = $(LIBDIR)oclos-runtime.a")
    (format stream "~%CLOSLIB = ~:[$(OCLOSLIB)~;$(GCLOSLIB)~]"
	    (debug-p cc-flags)))
  (when header-directory
    (format stream "~2%HEADERDIR = ~A"
	    (namestring* header-directory 
                         :directory-only-p t
                         :relative-to-directory make-pn)))
  (unless  *compile-into-source-directory-p*
    (format stream "~2%BIN = ~A"
	    (namestring* bin-directory 
                         :directory-only-p t
                         :relative-to-directory make-pn))
    (format stream "~%OBIN = ~A"
	    (namestring* obin-directory 
                         :directory-only-p t
                         :relative-to-directory make-pn)))
  #+debug-clos
  (format stream "~2%WORK = $(RUNC)~Awork" *directory-separator*))

(defun output-makefile-cc-macros (stream cc cc-flags header-directory)
  (terpri stream)
  (output-makefile-comment stream "CC Flags")
  (format stream "~%FLAGS = -I$(INCLUDEDIR) ~@[-I$(HEADERDIR)~]" 
	  (not (null header-directory)))
  #+translator-supports-clos
  (format stream " -DSI_SUPPORT_CLOS=1")
  (format stream "~:{~%~AFLAGS = ~A~}" (mapcar #'cdr *all-cc-flags*))
  (format stream "~%CFLAGS = ~{$(~AFLAGS) ~}"
	  (cons "" (mapcar #'(lambda (flag)
			       (second (assoc flag *all-cc-flags*)))
			   cc-flags)))
  (format stream "~2%CC = ~A" cc))
    
(defun output-makefile-target-macros (stream executable-filename
					     oexecutable-filename cc-flags)
  (format stream "~2%GEXE = ~A~%OEXE = ~A"
	  executable-filename oexecutable-filename)
  (format stream "~%EXE = ~:[$(OEXE)~;$(GEXE)~]" (debug-p cc-flags)))

(define-translator-parameter *maximum-files-per-rule* 100)

(defparameter *rtl-include-file-names*
  (append
   '(;; included by user.h
     "kernel" "uconfig"
     ;; included by rtl/include/kernel.h
     "config" "object" "values" "svarargs" "core" "instance"
     "inline" "specific" "lisplib" "ffi")
   #-translator-supports-clos
   '("smcompat" "ifuns" "initvars")
   #+translator-supports-clos
   '("clos" "smcompat" "c-sdefs" "c-ifuns" "initvars"
     ;; included by rtl/include/clos.h
     "wrapper" "methargs" "initclos" "slotv" "methcomb")))

(define-translator-parameter *explicitly-list-rtl-include-files-p* t)

(defun output-makefile-file-macros (stream make-pn localinit-pns
					   localinit-header-pns
					   translated-pns repl)
  (labels ((macro-file (pn symb-dir user-p macro-file-type)
	     (namestring* pn
			  :symbolic-directory symb-dir
			  :user-file-p user-p
                          :relative-to-directory make-pn
			  :type macro-file-type))
	   (output-macro (macro list &optional (depth 0))
	     (let ((ngroups (ceiling (length list) *maximum-files-per-rule*)))
	       (if (< 1 ngroups)
		   (let ((prefix (if (< 4 depth) (error "Too many files")
				     (aref '#("_" "__" "___" "____") depth)))
			 (groups nil))
		     (dotimes (i ngroups)
		       (let ((group (sformat "~A~A~D" macro prefix i))
			     (tail (nthcdr *maximum-files-per-rule* list)))
			 (output-macro group (ldiff list tail) depth)
			 (setq list tail)
			 (push (sformat "$(~A)" group) groups)))
		     (output-macro macro (nreverse groups) (1+ depth)))
		   (progn
		     (format stream "~2%~A = " macro)
		     (makefile-format stream list
				      :start (+ (length macro) 3))))))
	   (output-user-objects-macro (name symbolic-directory pathnames)
	     (flet ((file-string (pathname)
		      (macro-file pathname symbolic-directory t
				  *translate-file-object-type*)))
	       (output-macro name (mapcar #'file-string pathnames)))))
    #+debug-clos (output-user-objects-macro
		  "NEWINIT" "WORK" '("initclos" "clos-symdefs"
				     "clos-initsyms" "clos-initfuns"))
    #+debug-clos (format stream "~%NEWSTUFF = ")
    (output-user-objects-macro "BASEFILES" "BIN" translated-pns)
    (output-makefile-comment stream "REPL")
    (format stream "~%REPL = ~A" (if repl
				     (macro-file "repl" "BIN" t
						 *translate-file-object-type*)
				     ""))
    (output-user-objects-macro "LOCALINIT" "BIN" localinit-pns)
			       
    (output-macro
     "HEADERS"
     (append (flet ((include-file (name)
		      (namestring* nil
				   :symbolic-directory "INCLUDEDIR"
				   :name name
				   :type *translate-file-header-type*)))
	       (if *explicitly-list-rtl-include-files-p*
		   (mapcar #'include-file *rtl-include-file-names*)
		   (list (include-file "*"))))
	   (sort (mapcar #'(lambda (pn)
			     (namestring* pn
					  :relative-to-directory make-pn
					  :type *translate-file-header-type*))
			 localinit-header-pns)
		 #'string<)))
    (terpri stream)))

(defun output-makefile-link-rule (stream link-files)
  (output-makefile-rule :link
			stream
			"$(EXE)"
			(append
			 '(#+debug-clos
			   "$(NEWSTUFF)"
			   "$(BASEFILES)"
			   "$(LOCALINIT)"
			   "$(REPL)"
			   #-translator-supports-clos "$(LIB)"
			   #+translator-supports-clos "$(CLOSLIB)")
			 link-files)
			'("-o $(EXE) -lm")))

(defvar *local-init-file-p* nil)

(define-translator-parameter *cc-includes-from-source-directory-p* t)

(defun output-makefile-compile-rule (stream make-pn pn &optional (h-file-p t))
  (terpri stream)
  (multiple-value-bind (h-file h-file-dir)
      (when h-file-p
	(namestring* pn
		     :relative-to-directory make-pn
		     :type *translate-file-header-type*))
    (let ((c-file (namestring* pn
			       :relative-to-directory make-pn
			       :type *translate-file-output-type*)))
      (output-makefile-rule
       :compile stream
       (namestring* pn 
		    :symbolic-directory "BIN"
		    :user-file-p t
		    :relative-to-directory make-pn
		    :relative-to-directory make-pn
		    :type *translate-file-object-type*)
       (list c-file)
       (unless (or (not h-file-p) (equal h-file-dir ""))
	 (list (concatenate 'string "-I"
			    (if *cc-includes-from-source-directory-p*
				"./"
				h-file-dir))))
       (when h-file-p (list h-file))))))

(defun output-makefile-compile-rules (stream make-pn simple-localinit-pns
					     localinit-pns translated-pns)
  (flet ((output-simple-rule (pn)
	   (output-makefile-compile-rule stream make-pn pn nil))
	 (output-rule (pn)
	   (output-makefile-compile-rule stream make-pn pn t)))
    (let ((*local-init-file-p* nil))
      (output-makefile-comment stream "Base Files")
      (mapc #'output-rule translated-pns))
    (let ((*local-init-file-p* t))
      (output-makefile-comment stream "Local Init Files")
      (mapc #'output-simple-rule simple-localinit-pns)
      (mapc #'output-rule localinit-pns))))

(defun output-optimized-target (stream)
  (format stream "~%optimized :")
  (format stream "~%~A(" #\tab)
  #-translator-supports-clos
  (format stream "LIB=\"$(OLIB)\" ; \\~%~A " #\tab)
  #+translator-supports-clos
  (format stream "CLOSLIB=\"$(OCLOSLIB)\" ; \\~%~A " #\tab)
  (format stream "EXE=\"$(OEXE)\" ; \\~%~A " #\tab)
  (format stream "CFLAGS=\"$(OFLAGS) $(FLAGS)\" ; \\~%~A " #\tab)
  (format stream "BIN=\"$(OBIN)\" ; \\~%~A " #\tab)
  (format stream "export ")
  #+translator-supports-clos
  (format stream "CLOSLIB ")
  #-translator-supports-clos
  (format stream "LIB ")
  (format stream "EXE CFLAGS BIN ;\\")
  (format stream "~%~A $(MAKE) -e)~%" #\tab))
  
(defun output-makefile-rule (type stream target dependencies &optional
				  action-args other-dependencies)
  (format stream "~%~A : " target)
  (makefile-format stream 
		   (cons "$(HEADERS)" (append dependencies other-dependencies))
		   :start (+ 3 (length target)))
  (format stream "~%~A" #\tab)
  (makefile-format stream 
		   (ecase type
		     (:compile (append (list "$(COMPILE.c) -o" target)
				       dependencies action-args))
		     (:link    (append (list "$(LINK.c)")
				       dependencies action-args)))
		   :start 8)
  (terpri stream))

(defun makefile-format (stream strings &key (start 0))
  (let ((margin *margin-column*)
 	(indent-char #\Tab)
	(indent-size 8)			;??
	(current-pos start))
    (declare (fixnum margin current-pos))
    (dolist (st strings)
      (let ((len (length st)))
	(declare (fixnum len))
	(if (>= margin (+ current-pos len))
	      (format stream "~A " st)
	      (progn
		(format stream "~C~%~A~A " #\\ indent-char st)
		(setq current-pos indent-size)))
	(incf current-pos (1+ len))))))

(defun translated-output-pathnames ()
  (let* ((sysfilenames '(#+translator-supports-clos
			 "initialize-generic-functions"))
	 (pns (remove-if #'(lambda (pn) 
			     (or (null pn)
				 (not (null (member (pathname-name pn) 
						    sysfilenames 
						    :test #'string=)))))
			 (get-output-files))))
    (sort pns #'string-lessp :key #'pathname-name)))

(defun valid-cc-flags-p (flags)
  (and (listp flags)
       (every #'(lambda (flag)
		  (assoc flag *all-cc-flags*))
	      flags)))

(defun valid-lib-paths-p (libs)
  (and (listp libs)
       (every #'stringp libs)))

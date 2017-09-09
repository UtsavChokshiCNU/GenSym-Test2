;;; -*- Mode: LISP; Package: TIMPL; Syntax: Common-Lisp -*-

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/dumpmain.lisp,v $"
 "$Revision: 1.2 $"
 "$Date: 2007/11/14 22:02:54 $")

(defstruct (FUNCTION-DESCRIPTION 
	    (:print-function function-description-printer)
	    (:conc-name fd-))
  (name			""		:type	string)
  (return-value		"void"		:type	string)
  (argument-list	"()"		:type	string)
  (comment		nil		:type	(or null string))
  (package		"TCL-USER"	:type	(or null string))
  )

(defun FUNCTION-DESCRIPTION-PRINTER (struct stream depth)
  (declare (ignore depth))
  (format stream "#<Function-Description ~A>" (fd-name struct)))

(defparameter *INTERNAL-FUNCTION-DESCRIPTIONS*
  (list
    (make-function-description 
      :name		"heap_command_line"
      :return-value	"void"
      :argument-list	"(argc, argv)"
      :comment		"Process command line arguments"
      )
    (make-function-description
      :name		"init_top_level"
      :return-value	"void"
      :argument-list	"()"
      :comment		"Set up Lisp system internals"
      )
    (make-function-description
      :name		"userinit"
      :return-value	"void"
      :argument-list	"()"
      :comment		"Application specific initialization"
      )
    ))

#+internal-use
(defparameter *REPL-FUNCTION-DESCRIPTION*
  (make-function-description
    :name		"lisp_top_level"
    :return-value	"void"
    :argument-list	"()"
    :comment		"Chestnut Read Eval Print Loop"
    :package		nil
    )
  )

;;;
;;; Write Main file
;;;

(defun write-main-file
    (&key (default-pathname
	      (dumper-default-pn *dumper-pathnames*))
	  (pathname
	   (make-pathname :defaults default-pathname
			  :name *main-pathname-default-name*
			  :type *main-pathname-default-type*))
	  (user-header-pathname   (dumper-user-header-pn *dumper-pathnames*))
	  (user-toplevel	  nil)
	  (user-toplevel-package  nil)
	  (user-toplevel-comment  "Calling User Toplevel Function")
	  #+internal-use
	  (include-repl	          nil)
	  (verbose		  *compile-verbose*))
  #+internal-use
  (when (and user-toplevel include-repl)
    (error "Can specify either USER-TOPLEVEL or INCLUDE-REPL, not both."))
  (check-type pathname (or string pathname))
  (check-type default-pathname (or string pathname))
  (check-type user-header-pathname (or string pathname))
  (check-type user-toplevel (or symbol string))
  (check-type user-toplevel-package (or null string))
  (check-type user-toplevel-comment (or null string))
  (let ((package nil)
	(toplevel-desc nil))
    (when user-toplevel-package
      (if (not (null (find-package user-toplevel-package)))
	  (setq package (find-package user-toplevel-package))
	  (warn "Package ~A does not currently exists."
		user-toplevel-package)))
    (when user-toplevel
      (when (stringp user-toplevel)
	(unless package
	  (warn "Assuming USER-TOPLEVEL function ~A is interned in package TCL-USER."
		user-toplevel)
	  (setq package (find-package "TCL-USER")))
	(setq user-toplevel (intern user-toplevel package)))
      (let ((function-descriptor (defined-as-function user-toplevel)))
	(cond ((null function-descriptor)
	       (warn "USER-TOPLEVEL function ~S has not been defined."
		     user-toplevel))
	      ((not (null (function-descriptor-lambda-list function-descriptor)))
	       (warn "USER-TOPLEVEL function ~S has a non-null argument list ~S.~
		      ~%Ignoring argument list ~S."
		     user-toplevel
		     (function-descriptor-lambda-list function-descriptor)
		     (function-descriptor-lambda-list function-descriptor)))
	      (t nil)))
      (setq toplevel-desc
	    (make-function-description 
	     :name (translate-function-name user-toplevel)
	     :return-value "Object"
	     :argument-list "()"
	     :comment user-toplevel-comment)))
    #+internal-use
    (when include-repl
      (setf (fd-package *repl-function-description*) user-toplevel-package))
    (setq pathname (merge-pathnames (parse-namestring pathname) default-pathname))
    (setq user-header-pathname (parse-namestring user-header-pathname))
    (dump-main-aux pathname
		   (list user-header-pathname)
		   toplevel-desc 
		   #+internal-use include-repl 
		   verbose)))

(defun DUMP-MAIN-AUX (pn header-pns toplevel-desc #+internal-use repl verbose)
  (setq pn (make-pathname :defaults pn
			  :type *translate-file-output-type*))
  (when verbose (format t "~%Writing ~A..." (namestring pn)))
  (with-open-file (stream pn :direction :output
			     :if-exists *if-exists-action*
			     :if-does-not-exist *if-does-not-exist-action*)
    (output-file-header stream pn)
    (output-includes stream pn header-pns)
    (output-main stream toplevel-desc #+internal-use repl)
    (output-file-footer stream))
  pn)
;  (if verbose (values) :done))

(defun OUTPUT-FILE-HEADER (stream pn)
  (write-header-file-header stream pn "Main file")
  (terpri stream))

(defun OUTPUT-FILE-FOOTER (stream)
  (terpri stream))

(defun OUTPUT-INCLUDES (stream main-pn header-pns)
  (dolist (pn header-pns)
    (format stream "~%#include ~S"
	    (namestring* pn
			 :relative-to-directory main-pn
			 :type *translate-file-header-type*))))

(defun OUTPUT-MAIN (stream toplevel-desc #+internal-use repl)
  (labels
      ((OUTPUT-STATEMENT (level string &rest args)
	   (declare (fixnum level))
	   (let ((indent *indent-delta*))
	     (declare (fixnum indent))
	   (terpri stream)
	   (dotimes (i (* indent level)) (write-char #\space stream))
	   (apply #'format stream string args)))
       (OUTPUT-COMMENT (level string)
	 (output-statement level "/* ~A */" string))
       (OUTPUT-LEFT-BRACE (&optional (level 0))
	 (output-statement level "~C" #\{))
       (OUTPUT-RIGHT-BRACE (&optional (level 0))
	 (output-statement level "~C" #\}))
       (OUTPUT-FUNCTION-CALL (level desc)
	 (when (fd-comment desc)
	   (output-comment level (fd-comment desc)))
	 (output-statement level "~A~A;" (fd-name desc) (fd-argument-list desc)))
       (OUTPUT-MAIN-AND-ARGS ()
	 (output-statement 0 "main(argc, argv)")
	 (output-statement 1 "int argc;")
	 (output-statement 1 "char **argv;"))
       (OUTPUT-EXTERNS ()
;	 (dolist (desc *internal-function-descriptions*)
;	   (output-statement 1 "extern ~A();" (fd-name desc)))
;	 #+internal-use
;	 (when repl 
;	   (output-statement 1 "extern ~A();" (fd-name *repl-function-description*)))
	 (when toplevel-desc
	   (output-statement 1
			     "extern ~A ~A();" 
			     (fd-return-value toplevel-desc)
			     (fd-name toplevel-desc))))
       (OUTPUT-INTERNAL-FUNCTION-CALLS ()
	  (dolist (desc *internal-function-descriptions*)
	    (terpri stream)
	    (output-function-call 1 desc)))
       (OUTPUT-USER-TOPLEVEL-CALL ()
	  (terpri stream)
	  (output-function-call 1 toplevel-desc))
       #+internal-use
       (OUTPUT-REPL-FUNCTION-CALL ()
	  (terpri stream)
	  (output-function-call 1 *repl-function-description*))
       #+internal-use
       (OUTPUT-CURRENT-PACKAGE-STATEMENT (package)
	  (terpri stream)
	  (output-comment 1 (format nil "Setting current package to ~S" package))
	  (output-statement 1 "Package = find-package(istring_to_string(~S));" package))
       (OUTPUT-EXIT-STATEMENT ()
	  (terpri stream)
	  (output-statement 1 "lexit(FIX(0));")
	  (output-comment 1 "NOTREACHED"))
       ;; Pthreads-w32 static linking requires special treatment.
       ;; -- Chun Tian (binghe), 2010/3/12
       #+translator-supports-thread
       (output-pthread-block (left-p)
         (terpri stream)
         (output-statement 0 "#ifdef PTW32_STATIC_LIB")
         (if left-p
             (output-statement 1 "pthread_win32_process_attach_np();")
             (output-statement 1 "pthread_win32_process_detach_np();"))
         (output-statement 0 "#endif"))
       )
    (output-main-and-args)
    (output-left-brace)
    (output-externs)
    #+translator-supports-thread
    (output-pthread-block t)
    (output-internal-function-calls)
    (when toplevel-desc (output-user-toplevel-call))
    #+internal-use
    (when repl 
      (let ((package-name (fd-package *repl-function-description*)))
	(cond ((null package-name) nil)
	      ((string= package-name "TCL-USER") nil)
	      (t
	       (output-current-package-statement package-name))))
      (output-repl-function-call))
    #+translator-supports-thread
    (output-pthread-block nil)
    (output-exit-statement)
    (output-right-brace 0)))

(defun TRANSLATE-FUNCTION-NAME (symbol)
  (tutil::c-name-of-function-entry symbol))





;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; dump.lisp -- dump .c and .h files with declarations for global stuff.
;;;
;;; author :  Sandra Loosemore
;;; date   :  18 Nov 1990
;;;
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;
;;; *** to do:
;;; *** make sure all those strange initialization functions are actually
;;; ***    defined in the runtime library.
;;; *** figure out the order that the various initializations have to take
;;; ***    place in; some things might need to be treated magically.
;;; *** add the stuff for dumping definitions for DEFSTRUCTS.

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/dump.lisp,v $"
 "$Revision: 1.13 $"
 "$Date: 2009/06/27 01:43:00 $")

;;; Initialized elsewhere

(define-forward-variable-reference *initial-global-environment*)
(define-forward-variable-reference *default-global-environment*)


;;; This prefix is attached to internal initialization functions 

(defparameter *internal-function-prefix* "SI")

(defparameter *system-header-lines*
  '("#define SI_VARIADIC_KEYWORD_FUNCTIONS"
    "#include \"runtime.h\""))

(defmacro with-system-header-lines (&body body)
  `(let ((*header-lines* *system-header-lines*)) ,@body))


;;; Construct a sorted list of symbols in the database that have a
;;; particular property.
;;; The key function maps names in the database to strings (that are used
;;; to do the alphabetization).
;;; The test function is a predicate used to select which names to include.
;;; It receives two arguments -- the name and the associated value.

(defmacro with-sorted-data ((var env property key test) &body body)
  (multiple-value-bind (real-body decls) (parse-body body nil)
    (let ((env-temp      (gensym))
	  (property-temp (gensym))
	  (key-temp      (gensym))
	  (test-temp     (gensym)))
      `(let ((,env-temp ,env)
	     (,property-temp ,property)
	     (,key-temp ,key)
	     (,test-temp ,test)
	     (,var nil))
	 (declare ,@decls)
	 (translator-map-environment-names
	  #'(lambda (name value)
	      (if (funcall ,test-temp name value)
		  (push (list (funcall ,key-temp name) name value)
			,var)))
	  ,env-temp
	  ,property-temp)
	 (setq ,var (sort ,var #'string< :key #'car))
	 ,@real-body))))


;;; Iterate over the sorted list.

(defmacro do-with-sorted-data (((string name value) data) &body body)
  (let ((temp  (gensym)))
    `(dolist (,temp ,data)
       (destructuring-bind (,string ,name ,value) ,temp
	 ,@body))))


;;; Merge the three pathnames into something reasonable.

(defun merge-pathname-defaults (namepath type defaults)
  (make-pathname :defaults (merge-pathnames namepath defaults)
		 :type type))


;;; Make a .c file pathname and a .h file pathname from the basename and
;;; defaults, and apply the function to them.

(defun code-pathname (namepath &optional
		      (defaults *default-pathname-defaults*))
  (merge-pathname-defaults namepath
			   *translate-file-output-type*
			   defaults))

(defun header-pathname (namepath &optional
			(defaults *default-pathname-defaults*))
  (merge-pathname-defaults namepath
			   *translate-file-header-type*
			   defaults))

(defun apply-to-code-pathname (function namepath &optional
			       (defaults *default-pathname-defaults*))
  (funcall function (code-pathname namepath defaults)))

(defun apply-to-header-pathname (function namepath &optional
				 (defaults *default-pathname-defaults*))
  (funcall function (header-pathname namepath defaults)))

(defun apply-to-pathnames (function namepath &optional
			   (defaults *default-pathname-defaults*))
  (funcall function
	   (code-pathname namepath defaults)
	   (header-pathname namepath defaults)))

(defun make-default-pathname (name defaults)
  (make-pathname :defaults defaults
		 :name name
		 :version nil))


;;; A macro for dealing with header files.

(defmacro with-header-file ((stream-var pathname description) &body body)
  (multiple-value-bind (real-body decls) (parse-body body nil)
    (let ((pathname-var    (gensym))
	  (description-var (gensym)))
      `(let ((,pathname-var     ,pathname)
	     (,description-var  ,description))
	 (declare (special *verbose*))
	 (with-open-file (,stream-var
			  ,pathname-var :direction :output
			  :if-exists *if-exists-action*
			  :if-does-not-exist *if-does-not-exist-action*)
	   (declare ,@decls)
	   (when *verbose*
	     (format t "~%Writing ~A..." (namestring ,pathname-var)))
	   (write-header-file-header
	    ,stream-var ,pathname-var ,description-var)
	   (with-output-stream ,stream-var ,@real-body)
	   (write-header-file-trailer ,stream-var))))))



;;; Write the header file header.

(defun write-header-file-header (stream pathname description)
  (format stream 
	  "/* ~a -- ~a~
           ~@[~% * Generated on ~a~]~
           ~% * ~a~
           ~% */~%"
	  (file-namestring pathname)
	  description
	  (and *include-dates-in-headers* (date-and-time-string))
	  *copyright-notice*))


;;; Put a newline at the end of the header file.

(defun write-header-file-trailer (stream)
  (terpri stream))

(defmacro with-documentation (doc-form &body body)
  (let ((doc (gensym)))
    `(let ((,doc ,doc-form))
       (when ,doc
	 (emit-newline)
	 (emit-documentation ,doc))
       ,@body)))

;;; Dump #include statements for each file normally included.

(defun dump-default-includes ()
  (emit-newline)
  (dolist (line *header-lines*)
    (emit-string line)
    (emit-newline)))

;;; These tables are generated by some of the dumpers and then
;;; used by others.


;;; Init statements generated by symbol-table and function dumpers
;;; Each "statement" is of the form (statement . declarations)
(defvar *symbol-init-statements*)

(defun add-symbol-init-statement (statement &rest declarations)
  (push (cons statement declarations)
	*symbol-init-statements*))


;;; Name table used by function-object dumper

;;; Number of function-object tables
(defvar *function-table-count*)
;;; Current position
(defvar *function-table-position*)
;;; Hash table of name -> encoding of {table, pos}
(defvar *function-table*)



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Main entry points
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; Dump files containing declarations and initializations for things
;;; in the runtime library database.  These files can be shared across
;;; multiple applications.

(defparameter *default-symbols-pathname*
  #.(concatenate 'string #+translator-supports-clos "c-" "sdefs"))

(defparameter *default-symbols-code-pathname*
  #.(concatenate 'string #+translator-supports-clos "c-" "isyms"))

(defparameter *default-functions-pathname*
  #.(concatenate 'string #+translator-supports-clos "c-" "ifuns"))

(defparameter *default-small-functions-pathname*
  #.(concatenate 'string #+translator-supports-clos "c-" "small-initfuns"))

#+translator-supports-clos
(defparameter *default-clos-info-pathname*      "initclos")

#+translator-supports-clos
(defparameter *default-clos-init-pathname*      "closinit")

(defun dump-initial-header-files
    (&key (default-pathname
	      (make-pathname :defaults *default-pathname-defaults*
			     :name nil :type nil :version nil))
	  (symbols-pathname
	   (make-default-pathname *default-symbols-pathname*
				  default-pathname))
	  (symbols-code-pathname
	   (make-default-pathname *default-symbols-code-pathname*
				  default-pathname))
	  (functions-pathname
	   (make-default-pathname *default-functions-pathname*
				  default-pathname))
	  (small-functions-pathname
	   (make-default-pathname *default-small-functions-pathname*
				  default-pathname))
	  ((:verbose *verbose*) t)
	  (symbol-init-statements-per-file 20000)
	  #+translator-supports-clos
	  (clos-info-pathname
	   (make-default-pathname *default-clos-info-pathname*
				  default-pathname))
	  #+translator-supports-clos
	  (clos-init-pathname
	   (make-default-pathname *default-clos-init-pathname*
				  default-pathname)))
  (declare (special *verbose*))
  (let ((*symbol-init-statements* '())
	(*symbol-init-statements-per-file* symbol-init-statements-per-file))
    (apply-to-pathnames #'dump-initial-symbols
			symbols-pathname default-pathname)
    (apply-to-code-pathname #'dump-initial-symbol-init-function
			    symbols-code-pathname default-pathname))
  (apply-to-pathnames #'dump-initial-functions
		      functions-pathname default-pathname)
  (apply-to-pathnames #'dump-small-initial-functions
		      small-functions-pathname default-pathname)
  #+translator-supports-clos
  (progn
    (dump-initial-slots-header
     (header-pathname clos-info-pathname default-pathname))
    (tclosi:dump-clos-bootstrap-info clos-init-pathname))
  nil)


;;; User Header Pathnames

(defstruct (dumper-pathnames (:conc-name dumper-))
  (default-pn			*default-pathname-defaults*)
  (symbols-pn			(make-pathname :name "symtab"))
  (symbol-names-pn		(make-pathname :name "symnames"))
  (functions-pn			(make-pathname :name "userfuns"))
  (callables-pn			(make-pathname :name "callables"))
  (symbol-init-code-pn		(make-pathname :name "usersyms"))
  (variables-pn			(make-pathname :name "uservars"))
  (init-pn			(make-pathname :name "userinit"))
  (structures-pn		(make-pathname :name "userstrs"))
  (user-header-pn		(make-pathname :name "user"))
  (user-defs-header-pn		(make-pathname :name "userdefs"))
  #+translator-supports-clos
  (slot-index-pn		(make-pathname :name "slotidx"))
  (user-global-c-lines-pn       (make-pathname :name "uglobal"))
  #+translator-supports-thread
  (user-special-header-pn	(make-pathname :name "uspecial"))
  )

(defparameter *dumper-pathnames* (make-dumper-pathnames))

;;; Produce the application-wide .h files for the application.
;;; *** Need to extend this to dump the files for structures, slot indices,
;;; *** plus whatever else we think of....

(define-translator-parameter *application-name* "Lisp-to-C Translator")

;;; This part of the external interface to the Translator.
(defun write-header-files
    (&key ((:application-name *application-name*) *application-name*)
	  (default-pathname
	      (make-pathname :defaults *default-pathname-defaults*
			     :name nil :type nil :version nil))
	  (symbols-pathname
	   (make-default-pathname "symtab" default-pathname))
	  (symbol-names-pathname
	   (make-default-pathname "symnames" default-pathname))
	  (functions-pathname
	   (make-default-pathname "userfuns" default-pathname))
	  (callables-pathname
	   (make-default-pathname "callables" default-pathname))
	  (symbol-init-code-pathname
	   (make-default-pathname "usersyms" default-pathname))
	  (variables-pathname
	   (make-default-pathname "uservars" default-pathname))
	  (init-pathname
	   (make-default-pathname "userinit" default-pathname))
	  #+translator-supports-clos
	  (slot-index-pathname
	   (make-default-pathname "slotidx" default-pathname))
	  (structures-pathname
	   (make-default-pathname "userstrs" default-pathname))
	  (user-header-pathname
	   (make-default-pathname "user" default-pathname))
	  (user-defs-header-pathname
	   (make-default-pathname "userdefs" default-pathname))
	  (user-global-c-lines-pathname
	   (make-default-pathname "uglobal" default-pathname))
	  #+translator-supports-thread
	  (user-special-header-pathname
	   (make-default-pathname "uspecial" default-pathname))
	  (verbose *compile-verbose*))
  (let ((*verbose* verbose)
	(*default-pathname-defaults* default-pathname)
	(*header-lines*
	 (list (sformat "#include \"~A\""
			(namestring* user-header-pathname
				     :relative-to-directory default-pathname
				     :type *translate-file-header-type*)))))
    (declare (special *verbose*))
    (let ((*symbol-init-statements* '()))
      (mark-user-functions)
      (dump-user-symbols-c (code-pathname symbols-pathname))
      (dump-user-functions-c (header-pathname functions-pathname)
			     (code-pathname functions-pathname)
			     default-pathname)
      (dump-user-variables-c (code-pathname variables-pathname))
      (setq symbol-init-code-pathname
	    (dump-user-symbol-init-function
	     (code-pathname symbol-init-code-pathname))))
    (dump-toplevel (code-pathname init-pathname) default-pathname)
    #+translator-supports-clos
    (apply-to-pathnames #'dump-slot-index-definitions slot-index-pathname)
    (dump-user-structures (header-pathname structures-pathname))
    (dump-global-c-lines (header-pathname user-global-c-lines-pathname))
    (dump-system-header-file (header-pathname user-header-pathname)
			     structures-pathname
			     (when *global-c-lines*
			       user-global-c-lines-pathname)
			     #+translator-supports-clos
			     slot-index-pathname)
    #+translator-supports-thread
    (dump-user-special-header-file (header-pathname
                                    user-special-header-pathname)))
  (setq *dumper-pathnames*
	(make-dumper-pathnames 
	 :default-pn 		default-pathname
	 :symbols-pn 		symbols-pathname
	 :symbol-names-pn 	symbol-names-pathname
	 :functions-pn 		functions-pathname
	 :callables-pn          callables-pathname
	 :symbol-init-code-pn	symbol-init-code-pathname
	 :variables-pn 		variables-pathname
	 :init-pn		init-pathname
	 :structures-pn 	structures-pathname
	 :user-header-pn  	user-header-pathname
	 :user-defs-header-pn  	user-defs-header-pathname
	 #+translator-supports-clos
	 :slot-index-pn 
	 #+translator-supports-clos
	 slot-index-pathname
	 :user-global-c-lines-pn user-global-c-lines-pathname
	 #+translator-supports-thread
	 #+translator-supports-thread
	 :user-special-header-pn user-special-header-pathname))
  nil)

(defun dump-global-c-lines (h-file)
  (declare (special *verbose*))
  (when *global-c-lines*
    (with-header-file (output h-file "User Global C Lines Header File")
      (mapc #'emit-c-line *global-c-lines*))))

(defun dump-user-defs (h-file)
  (declare (special *verbose*))
  (with-header-file (output h-file "User Definitions Header File")
    (emit-header-file)))

(defun dump-header-file (h-file default-pathname)
  (declare (special *verbose*))
  (with-header-file
      (output h-file
	      (sformat "Header File for ~A"
		      (namestring* h-file
				   :relative-to-directory default-pathname
				   :type *translate-file-output-type*)))
    (emit-header-file)))

(defun emit-header-file ()
  (emit-user-symbols-h)
  (emit-user-functions-h)
  (emit-callables-h)
  (emit-user-variables-h))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Symbol and package setup
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Dump extern declarations for quoted symbols to initsyms.h
;;; Dump definitions and initializers to initsyms.c
;;; Note that symbols flagged :exists-at-runtime nil in the database
;;; just don't get a defined-as-symbol property assigned to them, so
;;; they just don't show up as we do the mapping over this property.

(defun dump-initial-symbols (cpath hpath)
  (with-sorted-data (symbol-data *initial-global-environment*
				 'defined-as-symbol
				 #'symbol-name
				 #'(lambda (symbol info)
				     (declare (ignore symbol))
				     (not (symbol-descriptor-magicp info))))
    (with-sorted-data (package-data *initial-global-environment*
				    'defined-as-package
				    #'runtime-package-name
				    #'trun:constantly-true)
      (let ((description "initial symbols for translator runtime"))
	(with-system-header-lines
	  (with-header-file (out hpath description)
	    (emit-symbols-aux-h symbol-data package-data))
	  (dump-symbols-aux-c symbol-data package-data cpath t
			      description))))))

;;; Likewise for static user symbols

(defun dump-user-symbols-c (cpath)
  (multiple-value-bind (symbol-data package-data)
      (get-user-symbols)
    (dump-symbols-aux-c
     symbol-data package-data cpath nil
     (sformat "~a Symbol Definitions" *application-name*))))

(defun emit-user-symbols-h ()
  (multiple-value-bind (symbol-data package-data)
      (if *current-translated-file*
	  (get-user-symbols (translated-file-cookie *current-translated-file*))
	  (get-user-symbols))
    (emit-format "~%~%/* Symbol Definitions */")
    (emit-symbols-aux-h symbol-data package-data)))

(defun get-user-symbols (&optional cookie)
  (with-sorted-data (package-data 
		     *default-global-environment*
		     'defined-as-package
		     #'runtime-package-name
		     #'(lambda (package info)
			 (declare (ignore package info))
			 t))
    (with-sorted-data
	(symbol-data
	 *default-global-environment*
	 'defined-as-symbol
	 #'symbol-name
	 #'(lambda (symbol info)
	     (declare (ignore symbol))
	     (and (not (symbol-descriptor-magicp info))
		  (symbol-descriptor-quoted-p info)
		  (or (null cookie)
		      (eql cookie (descriptor-file-cookie info))))))
      (values symbol-data package-data))))

(defun runtime-package-name (package)
  (package-descriptor-name (defined-as-package package)))

(defun emit-symbols-aux-h (symbol-data package-data)
  ;; Write the extern declarations to the .h file
  ;; Always generate declarations; RTL versions will be invisible,
  ;; so that same names can be used for static and non-static versions
  (do-with-sorted-data ((mapped-name symbol value) symbol-data)
    (declare (ignore mapped-name value))
    (emit-format "~%extern Object ~a;" 
		 (c-name-of-quoted-symbol symbol)))
  (emit-newline)
  (do-with-sorted-data ((mapped-name package descriptor) package-data)
    (declare (ignore mapped-name descriptor))
    (emit-format "~%extern Object ~a;" (c-name-of-package package))))

(defun dump-symbols-aux-c (symbol-data package-data cpath init-p description)
  ;; Write the definitions to the .c file
  (with-header-file (out cpath description)
    (dump-default-includes)
    (do-with-sorted-data ((mapped-name symbol value) symbol-data)
      (declare (ignore mapped-name value))
      (when (or init-p
		(not (defined-as-symbol symbol
			 *initial-global-environment*)))
	(emit-format "~%Object ~a;"
		     (c-name-of-quoted-symbol symbol))
	(unless (symbol-package symbol)
	  (add-symbol-init-statement
	   (sformat "~a = STATIC_SYMBOL(~a,NIL);"
		   (c-name-of-quoted-symbol symbol)
		   (format-c-string (symbol-name symbol)))))))
    (emit-newline)
    (do-with-sorted-data ((mapped-name package descriptor) package-data)
      (declare (ignore mapped-name descriptor))
      (when (or init-p
		(not (defined-as-package package
			 *initial-global-environment*)))
	(emit-format "~%Object ~a;"
		     (c-name-of-package package))))
    ;; re-sort the package list by the sequence number in the descriptor
    ;; to ensure that packages are created in the right order.
    ;; this is a violation of abstraction, sigh, but it does the right
    ;; thing....
    (setq package-data
	  (sort package-data
		#'(lambda (info1 info2)
		    (< (package-descriptor-sequence-number (third info1))
		       (package-descriptor-sequence-number (third info2))
		       ))))
    (dolist (pass '(1 2))
      (do-with-sorted-data ((mapped-name package descriptor) package-data)
	(declare (ignore mapped-name))
	(emit-newline)
	(dump-package-init-code package descriptor init-p pass)))))


;;; Dump the code to create and initialize a package.
;;; Do this in the order prescribed for DEFPACKAGE, namely:
;;; (1) create the package.
;;; (2) shadow the symbols from the shadow list.
;;; (3) shadowing-import the symbols from the shadowing-import list.
;;; (4) establish "use" links.
;;; (5) import the symbols from the import list.
;;; (6) intern the symbols from the intern list.
;;; (7) export the symbols from the export list.

(defun dumped-symbol-p (s init-p)
  (let* ((descriptor (defined-as-symbol s))
	 (magicp (symbol-descriptor-magicp descriptor)))
    (and
     (not magicp)
     (or init-p
	 (symbol-descriptor-quoted-p descriptor)))))

(defun sort-symbols (table init-p)
  ;; Sort all symbols which should be dumped from TABLE
  (let ((list  nil))
    (map-symbol-table
     #'(lambda (s) (when (dumped-symbol-p s init-p) (push s list)))
     table)
    (sort list #'string< :key #'symbol-name)))

(defun count-symbols (table init-p)
  ;; Count all symbols which should be dumped from TABLE
  (let ((count 0))
    (map-symbol-table
     #'(lambda (s)
	 (when (dumped-symbol-p s init-p)
	   (incf count)))
     table)
    count))

(defun symbol-export-status (symbol export)
  (if (symbol-entered-p symbol export) "TRUE" "FALSE"))


;;;; Non-static-constants-style initialization:  Dump code
;;;; which contains allocation calls

(defun dump-package-init-code (package descriptor init-p pass)
  ;; On pass 1, dump the symbol initialization code only.
  ;; On pass 2, dump the IMPORT and PACKAGE_USE code.
  (let ((c-name  (c-name-of-package package))
	(export  (package-descriptor-export descriptor))
	(initial-package-p
	 (defined-as-package package *initial-global-environment*)))
    (case pass
      (1
       (when (or init-p (not initial-package-p))
	 (add-symbol-init-statement
	  (sformat "~a = NEW_PACKAGE(~a);"
		   c-name 
		   (format-c-string (package-descriptor-name descriptor)))
	  (sformat "extern Object ~A;" c-name))
	 (dolist (n (sort (copy-list (package-descriptor-nicknames descriptor))
			  #'string<))
	   (add-symbol-init-statement
	    (sformat "ADD_PACKAGE_NICKNAME(~a,~a);"
		     c-name (format-c-string n)))))
       (dolist (s (sort-symbols
		   (package-descriptor-shadow descriptor)
		   init-p))
	 (add-symbol-constructor s c-name export)
	 (add-symbol-init-statement
	  (sformat "ADD_SHADOW(~a,~a);"
		   c-name
		   (c-name-of-quoted-symbol s)))
	 (add-variable-bindings s init-p))
       (dolist (s (sort-symbols
		   (package-descriptor-intern descriptor)
		   init-p))
	 (add-symbol-constructor s c-name export)
	 (add-variable-bindings s init-p)))
      (2
       (dolist (s (sort-symbols
		   (package-descriptor-shadowing-import descriptor)
		   init-p))
	 (add-symbol-init-statement
	  (sformat "ADD_SHADOW(~a,~a);"
		   c-name
		   (c-name-of-quoted-symbol s)))
	 (add-symbol-init-statement
	  (sformat "ADD_IMPORT(~a,~a,~a);"
		   c-name
		   (c-name-of-quoted-symbol s)
		   (symbol-export-status s export))))
       (when (or init-p (not initial-package-p))
	 (dolist (p (package-descriptor-use descriptor))
	   (add-symbol-init-statement
	    (sformat "ADD_PACKAGE_USE(~a,~a);"
		     c-name
		     (c-name-of-package p)))))
       (dolist (s (sort-symbols
		   (package-descriptor-import descriptor) 
		   init-p))
	 (add-symbol-init-statement
	  (sformat "ADD_IMPORT(~a,~a,~a);"
		   c-name
		   (c-name-of-quoted-symbol s)
		   (symbol-export-status s export))
          ;;; Add more package declarations for safety -- binghe, 2009/7/13
          (sformat "extern Object ~A;" c-name)))))))

(defun add-symbol-init-statement* (statement declarations)
  (push (cons statement declarations)
	*symbol-init-statements*))

(defun add-symbol-constructor (s c-name export)
  (let ((sym-decl (sformat "extern Object ~A;" (c-name-of-quoted-symbol s)))
	(pck-decl (sformat "extern Object ~A;" c-name))
	(info (defined-as-variable s *initial-global-environment*)))
    (if info
	(let ((simple-p (eq :simple-constant 
			    (variable-descriptor-constant-p info))))
	  (add-symbol-init-statement*
	   (sformat "~a = ENSURE_GLOBAL~A(~a,~a,~a,~a);"
		    (c-name-of-quoted-symbol s)
		    (if simple-p "_CONSTANT" "")
		    (c-name-of-global-variable s)
		    c-name
		    (format-c-string (symbol-name s))
		    (symbol-export-status s export))
	   (list* sym-decl
		  pck-decl
		  (unless simple-p
		    (let ((c-name-of-gv (c-name-of-global-variable s)))
		      (list #+translator-supports-thread
			    (if (member c-name-of-gv tutil::*special-variable-names*
					:test #'string=)
			      (sformat "DECLARE_VARIABLE(~A);" c-name-of-gv)
			      (sformat "extern Object ~A;" c-name-of-gv))
			    #-translator-supports-thread
			    (sformat "extern Object ~A;" c-name-of-gv)))))))
	(add-symbol-init-statement
	 (sformat "~a = NEW_SYMBOL(~a,~a,~a);"
		  (c-name-of-quoted-symbol s)
		  c-name
		  (format-c-string (symbol-name s))
		  (symbol-export-status s export))
	 sym-decl
	 pck-decl))))

;;; Object NEW_PACKAGE(char *name);
;;;     Create and return a new package with the given name.
;;;     Does not need to check whether a package with the same name already 
;;;     exists.
;;; void ADD_PACKAGE_NICKNAME(Object package, char *name);
;;;     Make the string be a new nickname for the package.  Doesn't need
;;;     to check whether a package with the same name already exists.
;;; Object NEW_SYMBOL(Object package, char *name, int externalp);
;;;     Create a symbol with the given name and install it as an internal
;;;     or external (according to externalp) symbol in the package.  
;;;     Doesn't need to check whether there is already a symbol with 
;;;     this name accessible in the package, or do any name conflict checking,
;;;     but does need to set the home package of the symbol.
;;;     Initializes the symbol-value and symbol-function to unbound and
;;;     sets the symbol-plist to nil.
;;; void ADD_SHADOW(Object package, Object symbol);
;;;     Add the symbol to the shadowing symbols list in the package.
;;;     Doesn't need to check if it is already there.  Doesn't need to
;;;     make the symbol accessible in the package.
;;; void ADD_PACKAGE_USE(Object package, Object package_to_use);
;;;     Add package_to_use to the use list of package.  Doesn't need to
;;;     check for name conflicts.
;;; void ADD_IMPORT(Object package, Object symbol, int externalp);
;;;     Make the symbol accessible in the package.  Doesn't need to check 
;;;     for name conflicts or set the home package of the symbol.



;;;  Note that this is timpl::add-variable-bindings.
;;; tutil::add-variable-bindings (defined in env.lisp) is a completely
;;; different function.
(defun add-variable-bindings (symbol init-p)
  ;; Add symbol->global bindings to init function
  (unless (or init-p			; Done explicitly by RTL
	      (defined-as-variable symbol *initial-global-environment*))
    (let ((descriptor (defined-as-variable symbol)))
      (when (and descriptor
		 (not (variable-descriptor-linked-locally-p descriptor)))
	(let ((variable-declarations
		(and *local-declarations*
		     (not (defined-as-variable symbol
			    *initial-global-environment*))
		     (list 
		       (sformat "extern Object ~A;"
			       (c-name-of-global-variable symbol))))))
	  (apply #'add-symbol-init-statement
	    (sformat "SET_SYMBOL_VALUE_LOCATION(~A, ~A);"
		    (c-name-of-quoted-symbol symbol)
		    (c-name-of-global-variable symbol))
	    variable-declarations))))))


;;;; Generate symbol-table initialization function.  This is
;;;; dumped as usersyms(); it's split into several functions
;;;; for the benefit of limited-capacity C compilers.


;;; Mapping of init-fn-number -> init-fn-name
;;; Not reinitialized; used to ensure names are unique and recycled
(defvar *symbol-init-functions* (make-hash-table :test #'eq))

(defun symbol-init-function-name (n)
  (cond
   ((zerop n)
    ;; The starting point should always be the same.
    'trun:usersyms)
   ((gethash n *symbol-init-functions*))
   (t
    (setf (gethash n *symbol-init-functions*)
	  (make-symbol "USERSYMS")))))

;;; Number of init statements per symbol-init file
;;; Note:  Since the number of declarations is actually the constraining
;;; factor, this should be used as the dividing line.
(defconstant init-statements-per-file 1000)

(defun dump-user-symbol-init-function (cpath)
  (dump-symbol-init-function-aux cpath nil))

(defun dump-initial-symbol-init-function (cpath)
  (let ((*header-lines* '("#include \"kernel.h\""
			  #-translator-supports-clos
			  "#include \"sdefs.h\"")))
    (dump-symbol-init-function-aux cpath t)))

(defun count-statement-files (list)
  (let ((count 0))
    (loop (when (null list) (return count))
	  (setq list (skip-one-statement-file list))
	  (incf count))))

(defun skip-one-statement-file (list)
  (let ((n *symbol-init-statements-per-file*)
	(count 0))
    (loop (unless list (return nil))
	  (when (= count n) (return list))
	  (let* ((entry (car list))
		 (statement (car entry))
		 (statement-length (length statement)))
	    (incf count (if (and (> statement-length 17)
				 (string= "PROTECT_GLOBAL_10" statement
					  :end2 17))
			    10
			    1))
	    (when (> count n)
	      (return list)))
	  (setq list (cdr list)))))

(defun dump-symbol-init-function-aux (cpath init-p)
  ;; Each statement is of the form (statement . declarations)
  (setq cpath (pathname cpath))
  (let ((init-statements (reverse *symbol-init-statements*))
	(cpath-list nil))
    (do ((next-tail (skip-one-statement-file init-statements)
		    (skip-one-statement-file next-tail))
	 (remaining-statements init-statements next-tail)
	 (file-count 0 (1+ file-count))
	 (number-of-files (count-statement-files *symbol-init-statements*))
	 (base-name (pathname-name (pathname cpath))))
	((and (null remaining-statements)
	      (plusp file-count))
	 (nreverse cpath-list))
      (let* ((statement-entries (ldiff remaining-statements next-tail))
	     (statements (mapcar #'car statement-entries))
	     (function-entry
	      (if init-p
		  "SI_initsyms"
		  (c-name-of-function-entry
		   (symbol-init-function-name file-count))))
	     (declarations
	      (remove-duplicates
	       (mapcan #'(lambda (statement)
			   (copy-list (cdr statement)))
		       statement-entries)
	       :from-end t
	       :test #'string=))
	     (this-path
	      (if (zerop file-count) cpath
		  (make-pathname
		   :name (sformat "~A~D" 
				  (let* ((bns (length base-name))
					 (fcs (cond ((<= file-count 10) 1)
						    ((<= file-count 100) 2)
						    (t 3)))
					 (d (- (+ bns fcs) 8)))
				    (if (<= d 0)
					base-name
					(subseq base-name 0 (- bns d))))
				  file-count)
		   :defaults cpath)))
	     (description
	      (format nil
		      "~a Symbol Initialization Code~:[~2*~; (Part ~D of ~D)~]"
		      *application-name*
		      (plusp number-of-files)
		      (1+ file-count) number-of-files)))
	(push this-path cpath-list)
	(dump-symbol-init-function-aux1 
	 this-path description
	 function-entry
	 declarations statements
	 (when next-tail
	   (if (not init-p)
	       (c-name-of-function-entry
		(symbol-init-function-name (1+ file-count)))
	       (error "Internal error:  SI_initsyms too long!"))))))))

(defun dump-symbol-init-function-aux1 
    (this-path description
     function-entry declarations statements &optional next-function-entry)
  (with-header-file (out this-path description)
    (dump-default-includes)
    (emit-format "~%void ~A()~%{" function-entry)
    (when declarations
      (emit-newline)
      (setq declarations (sort declarations #'string<))
      (let ((last-declaration nil))
	(dolist (declaration declarations)
	  (unless (equal declaration last-declaration)
	    (setq last-declaration declaration)
	    (emit-format "    ~A~%" declaration)))))
    (when next-function-entry
      (emit-newline)
      (emit-format "    extern void ~A();~%~%" next-function-entry))
    (dolist (statement statements)
      (emit-newline-indent *indent-delta*)
      (emit-and-split-string statement))
    (emit-newline)
    (if next-function-entry
	(emit-format "    ~A();~%}~%" next-function-entry)
	(emit-format "}~%"))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Function setup
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Dump small-initfuns.h. This contains only externs and not #defines
;;; for functions.

(defun dump-small-initial-functions (cpath hpath)
  (dump-initial-functions cpath hpath nil nil))

;;; Dump extern declarations and #define's for functions to initfuns.h
;;; Dump code to install functional objects to initfuns.c.
;;; Note that foreign functions don't get either an extern declaration 
;;; or a #define for the functional object.

(defun dump-initial-functions (cpath hpath &optional 
				     (dump-defines-p t)
				     (dump-c-file-p t))
  (with-sorted-data
      (data *initial-global-environment*
	    'defined-as-function
	    #'(lambda (name) (c-name-of-function-entry name))
	    #'(lambda (name desc)
		(declare (ignore name))
		(not (function-descriptor-foreign-protocol desc))))
    ;; Write the extern declarations and #defines to the .h file
    (with-header-file (out hpath "initial functions for translator runtime")
      (emit-format "~%#ifdef SI_VARIADIC_KEYWORD_FUNCTIONS")
      (emit-format "~%#define RESTORE_SI_VARIADIC_KEYWORD_FUNCTIONS")
      (emit-format "~%#endif")
      (emit-format "~%#define SI_VARIADIC_KEYWORD_FUNCTIONS")
      (emit-format "~%#include \"varkey.h\"~%")
      (emit-function-declarations nil data dump-defines-p t)
      (emit-format "~%~%~%#ifndef RESTORE_SI_VARIADIC_KEYWORD_FUNCTIONS")
      (emit-format "~%#undef SI_VARIADIC_KEYWORD_FUNCTIONS")
      (emit-format "~%#endif")
      (emit-format "~%#include \"varkey.h\"~%"))
    (when dump-c-file-p
      (let ((*header-lines* '("#include \"kernel.h\""
			      #-translator-supports-clos
			      "#include \"sdefs.h\"")))
	;; Write the .c file to create and install the function definitions
	(with-header-file (out cpath 
			       "initial functions for translator runtime")
	  (dump-default-includes)
	  (emit-format "~%void ~a_initfuns()~%{" *internal-function-prefix*)
	  (dump-linking-code data t)
	  (emit-format "~%}")
	  ;; Now dump definitions for variadic generic function entries.
	  #+translator-supports-clos
	  (progn
	    (emit-newline)
	    (dump-generic-function-definitions data)))))))

;;; Same, for user-defined functions.  We only need a .h file here
;;; because the translator generates top-level forms to install the
;;; function definitions in the file in which they are defined.

(defun emit-user-functions-h ()
  (let ((cookie (and *current-translated-file*
		     (translated-file-cookie *current-translated-file*))))
    (with-sorted-data
	(data *default-global-environment*
	      'defined-as-function
	      #'(lambda (name) (c-name-of-function-entry name))
	      #'(lambda (name desc)
		  (declare (ignore name))
		  (and (not (function-descriptor-foreign-protocol desc))
		       (not (function-descriptor-defined-in-rtl-p desc))
		       (or (null cookie)
			   (eql cookie (descriptor-file-cookie desc))))))
      ;; Write the extern declarations and #defines to the .h file
      (emit-function-declarations "function declarations" data
				  (and *use-function-macros*
				       (not *use-function-value-cells*))))))

(defun emit-user-functions-aux (description data)
  (emit-format "~%~%/* ~A */" description)
  (do-with-sorted-data ((entry-name function-name descriptor) data)
    (unless (defined-as-function function-name *initial-global-environment*)
      (dump-function-declaration entry-name function-name descriptor)
      ;; Dump macro definition for function object, if necessary
      (when (and *use-function-macros* (not *use-function-value-cells*))
	(dump-function-object-macro function-name)))))

(defun mark-user-functions ()
  (with-sorted-data
      (data *default-global-environment*
	    'defined-as-function
	    #'(lambda (name) (c-name-of-function-entry name))
	    #'(lambda (name desc)
		(and (not (function-descriptor-foreign-protocol desc))
		     (not (defined-as-function name
			      *initial-global-environment*)))))
    (do-with-sorted-data ((entry-name function-name descriptor) data)
      (declare (ignore entry-name))
      (unless (or (defined-as-function function-name
		      *initial-global-environment*)
		  (function-descriptor-linked-locally-p descriptor)
		  (function-descriptor-generic-function-p descriptor))
	(mark-quoted-symbol (get-fn-principal-name function-name))))))

(defun dump-user-functions-c (hpath cpath default-pathname)
  (with-header-file
      (out hpath (format nil "Header for function linking code for ~a"
			 *application-name*))
    (dump-user-functions-c--rtl-internal #'dump-linking-code-header)
    (dump-user-functions-c--user-internal #'dump-linking-code-header))
  (with-header-file
      (out cpath (format nil "Function linking code for ~a"
			 *application-name*))
    (let* ((hpath-include
	    (sformat "#include \"~A\""
		     (namestring* hpath
				  :relative-to-directory default-pathname
				  :type *translate-file-header-type*)))
	   (*header-lines* (append *header-lines* (list hpath-include))))
      (dump-default-includes)
      (emit-format "~%void initfuns()~%{")
      (dump-user-functions-c--rtl-internal #'dump-linking-code)
      (emit-format "~%}")
      (emit-format "~%~%void user_initfuns()~%{")
      (dump-user-functions-c--user-internal #'dump-linking-code)
      (emit-format "~%}"))))

(defun dump-user-functions-c--user-internal (function)
  (with-sorted-data
      (data *default-global-environment*
	    'defined-as-function
	    #'(lambda (name) (c-name-of-function-entry name))
	    #'(lambda (name desc)
		(declare (ignore name))
		(not (or (function-descriptor-foreign-protocol desc)
			 (function-descriptor-generic-function-p desc)
			 (function-descriptor-linked-locally-p desc)
			 (function-descriptor-defined-in-rtl-p desc)))))
    (funcall function data nil)))

(defun dump-user-functions-c--user ()
  (with-sorted-data
      (data *default-global-environment*
	    'defined-as-function
	    #'(lambda (name) (c-name-of-function-entry name))
	    #'(lambda (name desc)
		(declare (ignore name))
		(not (or (function-descriptor-foreign-protocol desc)
			 (function-descriptor-generic-function-p desc)
			 (function-descriptor-linked-locally-p desc)
			 (function-descriptor-defined-in-rtl-p desc)))))
    (do-with-sorted-data ((entry-name function-name descriptor) data)
      (declare (ignore entry-name descriptor))
      (multiple-value-bind (principal setfp)
	  (get-fn-principal-name function-name)
	(add-symbol-init-statement
	 (with-output-to-string (out)
	   (with-output-stream out
	     (emit-format "~A(~A, "
			  (if setfp
			      "SET_SETF_FUNCTION"
			      "SET_SYMBOL_FUNCTION")
			  (c-name-of-quoted-symbol principal))
	     (named-function-object-initializer
	      "STATIC_FUNCTION" function-name)
	     (emit-string ");")))
	 (sformat "extern Object ~A();"
		  (c-name-of-function-entry function-name)))))))

(defun dump-user-functions-c--rtl (hpath cpath default-pathname)
  (with-header-file
      (out hpath (format nil "Header for linking code for RTL functions for ~a"
			 *application-name*))
    (dump-user-functions-c--rtl-internal #'dump-linking-code-header))
  (with-header-file
      (out cpath (format nil "Linking code for RTL functions for ~a"
			 *application-name*))
    (let* ((hpath-include
	    (sformat "#include \"~A\""
		     (namestring* hpath
				  :relative-to-directory default-pathname
				  :type *translate-file-header-type*)))
	   (*header-lines* (append *header-lines* (list hpath-include))))
      (dump-default-includes)
      (emit-format "~%void initfuns()~%{")
      (dump-user-functions-c--rtl-internal #'dump-linking-code)
      ;; No need to dump definitions for variadic generic function entries,
      ;; since they will always be defined in minimal-initfuns() in
      ;; the Clos translator
      (emit-format "~%}"))))

(defun dump-user-functions-c--rtl-internal (function)
  (unless *initial-symbols*
    (with-sorted-data
	(data *initial-global-environment*
	      'defined-as-function
	      #'(lambda (name)
		  (c-name-of-function-entry name))
	      #'(lambda (name desc)
		  (and (not (function-descriptor-foreign-protocol desc))
		       (not (function-descriptor-rtl-requires-linking desc))
		       (symbol-descriptor-quoted-p
			(defined-as-symbol
			    (principal-name-of-function-name name))))))
      (funcall function data t))))

(defun dump-linking-code-header (data rtl-p)
  (declare (ignore rtl-p))
  (do-with-sorted-data ((entry-name function-name info) data)
    (declare (ignore entry-name))
    (unless (function-descriptor-generic-function-p info)
      (emit-format "~%extern Object ~a;" 
		   (c-name-of-quoted-symbol 
		    (cond ((symbolp function-name) function-name)
			  ((setf-function-name-p function-name)
			   (cadr function-name))
			  (t (bad-function-name-error function-name)))))))
  (emit-function-declarations nil data nil))

(defparameter *use-prototypes-flag* "USE_PROTOTYPES") ;"__STDC__"

(defun emit-function-declarations (description data &optional
					       dump-defines-p skip-aliases-p)
  
  (when data
    (when description
      (emit-format "~%~%/* ~A */" description))
    (emit-format "~%~%#ifdef ~A" *use-prototypes-flag*)
    (emit-function-declarations-aux data t skip-aliases-p)
    (emit-format "~%~%#else")
    (emit-function-declarations-aux data nil skip-aliases-p)
    (emit-format "~%~%#endif")
    (when dump-defines-p
      (emit-newline)
      (do-with-sorted-data ((entry-name function-name info) data)
	(declare (ignore entry-name info))
	(dump-function-object-macro function-name)))))

(defun emit-function-declarations-aux (data &optional ansi-p skip-aliases-p)
  (emit-newline)
  (let ((*generate-ansi-c-types* ansi-p)
	(*ansi-c-more-parameters-string*
	 *function-declaration-ansi-c-more-parameters-string*))
    (do-with-sorted-data ((entry-name function-name info) data)
      (with-documentation (function-descriptor-documentation info)
	(unless (and skip-aliases-p (function-descriptor-alias-p info))
	  (dump-function-declaration entry-name function-name info))))))

(defun dump-linking-code (data rtl-p)
  (declare (ignore rtl-p))
  (do-with-sorted-data ((entry-name function-name info) data)
    ;; No need to dump definitions for variadic generic function entries,
    ;; since they will always be defined in minimal-initfuns() in
    ;; the Clos translator
    (unless (function-descriptor-generic-function-p info)
      (emit-newline-indent *indent-delta*)
      (multiple-value-bind (principal setfp)
	  (get-fn-principal-name function-name)
	(emit-format "~A(~A,"
		     (if setfp
			 "SET_SETF_FUNCTION"
			 "SET_SYMBOL_FUNCTION")
		     (c-name-of-quoted-symbol principal))
	(emit-newline-indent (+ *indent-delta* *indent-delta*))
	(function-object-initializer
	 "STATIC_FUNCTION"
	 entry-name
	 "NIL"
	 (function-descriptor-variadic info)
	 (get-descriptor-lambda-list-info info))
	(emit-string ");")))))

;;; callables.h includes only extern declarations, not #defines for Ffoo,
;;; because callables do not have an associated function object.

(defun emit-callables-h ()
  (let ((cookie (and *current-translated-file*
		     (translated-file-cookie *current-translated-file*))))
    (with-sorted-data (data *default-global-environment*
			    'defined-as-function
			    #'(lambda (name) (c-name-of-function-entry name))
			    #'(lambda (name desc)
				(and (function-descriptor-extern-required desc)
				     (or (null cookie)
					 (eql cookie
					      (descriptor-file-cookie desc)))
				     (not (defined-as-function name
					      *initial-global-environment*)))))
      ;; Write the extern declarations and #defines to the .h file
      (emit-function-declarations "Externally callable routines" data nil))))

(defun emit-callables-aux (description data)
  (emit-format "~%~%/* ~A */" description)
  (do-with-sorted-data ((entry-name function-name info) data)
    (with-documentation (function-descriptor-documentation info)
      (dump-function-declaration entry-name function-name info))
    (emit-newline)))

;;; *** This has been tweaked to dump ANSI prototypes....

(defun dump-function-declaration-1 (entry-name descriptor)
  (emit-single-type-declaration
   (function-foreign-type descriptor)
   entry-name
   :storage-class
   (cond ((function-descriptor-dllexport-p descriptor)
	  "DLLEXPORT extern")
	 ((function-descriptor-dllimport-p descriptor)
	  "DLLIMPORT extern")
	 (t
	  "extern"))))


(defun dump-function-declaration (entry-name function-name descriptor)
  (if (and (function-descriptor-generic-function-p descriptor)
	   (not (function-descriptor-variadic descriptor)))
      ;; Positional generic functions get a macro definition in header files.
      (dump-positional-generic-function-declaration entry-name
						    function-name
						    descriptor)
      (dump-function-declaration-1 entry-name descriptor)))


(defun dump-function-object-macro (function-name)
  (cond ((symbolp function-name)
	 (emit-format "~%#define ~a SYMBOL_FUNCTION(~a)"
		      (c-name-of-function-object function-name)
		      (c-name-of-quoted-symbol function-name)))
	((setf-function-name-p function-name)
	 (emit-format "~%#define ~a SETF_FUNCTION(~a)"
		      (c-name-of-function-object function-name)
		      (c-name-of-quoted-symbol (cadr function-name))))
	(t
	 (bad-function-name-error function-name)))) 

(defun bad-function-name-error (function-name)
  (error "Internal error: bad function name ~s." function-name))


(defun named-function-object-initializer (maker function-name)
  ;; Build Ffoo initializer from function name
  (let ((descriptor (defined-as-function function-name)))
    (unless descriptor
      (error "Descriptor missing for function ~S" function-name))
    (function-object-initializer
      maker
      (c-name-of-function-entry function-name)
      "Nil"
      (function-descriptor-variadic descriptor)
      (get-descriptor-lambda-list-info descriptor))))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Special variables and constants
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; Dump an extern declaration for variables to initvars.h
;;; Dump a #define for simple constants to initvars.h also
;;; Dump the variable definition to initvars.c.
;;; Code to initialize the variables/constants is dumped in the files
;;; where the DEFVAR/DEFPARAMETER/DEFCONSTANT appears.

(defun dump-initial-variables (cpath hpath)
  (with-sorted-data (data *initial-global-environment*
			  'defined-as-variable
			  #'(lambda (name) (c-name-of-global-variable name))
			  #'(lambda (name desc)
			      (declare (ignore name))
			      (variable-descriptor-dump-definition-p desc)))
    (let ((desc "initial variables/constants for translator runtime"))
      (dump-initial-variables-aux-h hpath desc data)
      (dump-variables-aux-c cpath t desc data))))

(defun dump-initial-variables-aux-h (hpath description data)
  ;; Write the .h file
  (with-header-file (out hpath description)
    (emit-variables-aux-h data)))

(defun dump-user-variables-c (cpath)
  (with-sorted-data
      (data *default-global-environment*
	    'defined-as-variable
	    #'(lambda (name) (c-name-of-global-variable name))
	    #'(lambda (name desc)
		(and (variable-descriptor-dump-definition-p desc) 
		     (not (defined-as-variable
			      name *initial-global-environment*)))))
    (let ((desc (format nil "variables/constants specific to ~a"
			*application-name*)))
      (dump-variables-aux-c cpath nil desc data))))

(defun emit-user-variables-h ()
  (let ((cookie (and *current-translated-file*
		     (translated-file-cookie *current-translated-file*))))
    (with-sorted-data
	(data *default-global-environment*
	      'defined-as-variable
	      #'(lambda (name) (c-name-of-global-variable name))
	      #'(lambda (name desc)
		  (and (variable-descriptor-dump-definition-p desc)
		       (or (null cookie)
			   (eql cookie (descriptor-file-cookie desc)))
		       (not (defined-as-variable
				name *initial-global-environment*)))))
      (emit-format "~%~%/* ~A */" "variables/constants")
      (emit-variables-aux-h data))))

(defun emit-variables-aux-h (data)
  ;; Write the .h file
  (do-with-sorted-data ((mapped-name name info) data)
    (ecase (variable-descriptor-constant-p info)
      ((:simple-constant)
       (if (variable-descriptor-value-p info)
	   (with-documentation (variable-descriptor-documentation info)
	     (emit-format "~%#define ~a ~e"
			  mapped-name
			  (translate-constant-aux 
			   (variable-descriptor-value info))))
	   (error "Don't have a value for constant ~s." name)))
      ((:complex-constant)
       (with-documentation (variable-descriptor-documentation info)
	 (emit-format "~%extern Object ~a;" mapped-name)))
      ((nil)
       (with-documentation (variable-descriptor-documentation info)
	 #+translator-supports-thread
	 (if (variable-descriptor-special-p info)
	   (emit-format "~%DECLARE_VARIABLE_WITH_SYMBOL(~a, ~a);"
			mapped-name (c-name-of-quoted-symbol name))
	   (emit-format "~%extern Object ~a;" mapped-name))
	 #-translator-supports-thread
	 (emit-format "~%extern Object ~a;" mapped-name))))))

(defun dump-variables-aux-c (cpath init-p description data)
  (when init-p
    ;; Write the .c file
    (with-header-file (out cpath description)
      (dump-default-includes)
      (do-with-sorted-data ((mapped-name name info) data)
	(declare (ignore name))
	(ecase (variable-descriptor-constant-p info)
	  ((:simple-constant) nil)
	  ((:complex-constant)
	   (with-documentation (variable-descriptor-documentation info)
	     (emit-format "~%Object ~a = UNBOUND;" mapped-name)))
	  ((nil) ; variables
	   (with-documentation (variable-descriptor-documentation info)
	     #+translator-supports-thread
	     (if (variable-descriptor-special-p info)
	       (emit-format "DECLARE_VARIABLE(~a);" mapped-name)
	       (emit-format "~%Object ~a = UNBOUND;" mapped-name))
	     #-translator-supports-thread
	     (emit-format "~%Object ~a = UNBOUND;" mapped-name)))))))
  (when *rtl-includes-gc-p*
    ;; Write the PROTECT-GLOBAL forms to the init function
    (let ((ten-variables '())
	  (name-count 0))
      (declare (fixnum name-count) (type list ten-variables))
      (labels ((flush-variables ()
		 (when ten-variables
		   (setq ten-variables (nreverse ten-variables))
		   (add-symbol-init-statement*
		    (format nil "PROTECT_GLOBAL_~D(~{~A~^,~});"
			    name-count
			    (mapcar #'car ten-variables))
		    (mapcar #'(lambda (name+info)
				(destructuring-bind (name . info) name+info
				  #-translator-supports-thread
				  (declare (ignore info))
				  #+translator-supports-thread
				  (if (and (variable-descriptor-special-p info)
					   (not (variable-descriptor-constant-p info)))
				    (sformat "DECLARE_VARIABLE(~A);" name)
				    (sformat "extern Object ~A;" name))
				  #-translator-supports-thread
				  (sformat "extern Object ~A;" name)))
			    ten-variables)))		   
		 (setq ten-variables '() name-count 0))
	       (protect-variable (name info)
		 (when (= name-count 10)
		   (flush-variables))
		 (incf name-count)
		 (push (cons name info) ten-variables)))
	(do-with-sorted-data ((mapped-name name info) data)
	  (declare (ignore name))
	  ;; Protect only if the variable has been
	  ;; referenced (and hence defined) somewhere
	  (when (variable-descriptor-redefinition-record info)
	    (ecase (variable-descriptor-constant-p info)
	      ((:simple-constant) nil)
	      ((nil :complex-constant)
	       (protect-variable mapped-name info)))))
	(flush-variables)))))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Code to invoke top-level forms
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun dump-toplevel (cpath relative-to-directory)
  ;; Dump calls to top-level functions which are nonempty, in order
  ;; by sequence number
  (let ((translated-files '()))
    (maphash #'(lambda (key descriptor)
		 (declare (ignore key))
		 (when (translated-file-init-function-p descriptor)
		   (push descriptor translated-files)))
	     *translated-files*)
    (setq translated-files
	  (sort translated-files #'< :key #'translated-file-sequence-number))
    (with-header-file (out cpath
			   (format nil "~a Top-Level Forms"
				   *application-name*))
      (dump-default-includes)
      (emit-newline)
      (let ((names-needing-declarations '())
	    (any-includes-p nil))
	(dolist (descriptor translated-files)
	  (let ((path (translated-file-init-pathname descriptor)))
	    (if path			; this allows mix & match
		(progn
		  (emit-format "~%#include \"~A\""
			       (namestring* path
					    :relative-to-directory
					    relative-to-directory))
		  (setq any-includes-p t))
		(push (translated-file-init-function-name descriptor)
		      names-needing-declarations))))
	(if *initial-symbols*
	    (emit-format "~%INCLUDE_LISP_PACKAGE~%")
	    (emit-format "~%INCLUDE_LISP_PACKAGE_SELECTIVELY~%"))
	(emit-newline)
	(emit-format "~:[~;~%~%~]void userinit()~%{" 
		     any-includes-p)
	(when names-needing-declarations
	  (dolist (name (nreverse names-needing-declarations))
	    (emit-format "~%    extern void ~A();"
			 (c-name-of-function-entry name)))
	  (emit-newline))
	(when *enter-function-maximum-index-callback*
	  (emit-format "~%    ~A(~D);" 
		       *enter-function-maximum-index-callback*
		       *enter-function-index*))
	(dolist (descriptor translated-files)
	  (emit-format "~%    ~A();" 
		       (c-name-of-function-entry
			(translated-file-init-function-name descriptor)))))
      (emit-format "~%}~%"))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Dump initial slot information
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

#+translator-supports-clos
(progn

(defun dump-initial-slots-header (hpath)
  (with-header-file (out hpath "internal slot indexes and access macros")
    (dump-internal-slot-access-macros)
    (emit-newline)
    (dump-initial-slot-index-declarations)))

;;; Dump internal macros for accessing internal slots in metaobjects.

(defparameter *internal-slot-access-reader*
  "~%#define ~A_~A(o) \\~%~4T~2:*~A~*_SLOT_VALUE_INDEXED(o,~A,~A)~%")

(defparameter *internal-slot-access-boundp*
  "~%#define ~A_~A(o) \\~%~4T~2:*~A~*_SLOT_BOUNDP_INDEXED(o,~A,~A)~%")

(defparameter *internal-slot-access-writer*
  "~%#define ~A_~A(o,v) \\~%~4T~2:*~A~*_SET_SLOT_VALUE_INDEXED(o,~A,v,~A)~%")

(defun dump-internal-slot-access-macros ()
  (dolist (entry (sort (copy-list (tclosi:internal-slot-accessors))
		       #'string<
		       :key #'(lambda (entry)
				(or (second entry)
				    (third entry)
				    (fourth entry)))))
    (destructuring-bind (slot-name reader writer boundp) entry
      (let ((index (c-name-of-global-variable
		    (tclosi:global-slot-index slot-name)))
	    (slot-name (c-name-of-quoted-symbol slot-name)))
	(when reader
	  (let ((name reader))
	    (emit-format "~%#define ~A_~A(o) \\~%" 
			 *internal-function-prefix* name)
	    (emit-format "    ~A_SLOT_VALUE_INDEXED(o,~A,~A)~%"
			 *internal-function-prefix* slot-name index)))
	(when boundp
	  (let ((name boundp))
	    (emit-format "~%#define ~A_~A(o) \\~%" 
			 *internal-function-prefix* name)
	    (emit-format "    ~A_SLOT_BOUNDP_INDEXED(o,~A,~A)~%"
			 *internal-function-prefix* slot-name index)))
	(when writer
	  (let ((name writer))
	    (emit-format "~%#define ~A_~A(o,v) \\~%" 
			 *internal-function-prefix* name)
	    (emit-format "    ~A_SET_SLOT_VALUE_INDEXED(o,~A,v,~A)~%"
			 *internal-function-prefix* slot-name index)))))))
)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Dump slot index definitions
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

#+translator-supports-clos
(progn

;;; User slot indexes are defined as preprocessor macros.  Built in slot
;;; indexes are defined as global constants.  Defining slot indexes as macros
;;; typically results in faster slot access times (though const declarations
;;; might be able to fix this).  The built-in slot indexes use global constants
;;; in order to avoid requiring a recompilation of all kernel files that
;;; reference them each time a translation is done.  Instead, each translation
;;; generates a .c file that defines the built-in slot indexes and this file
;;; gets compiled and linked with the rest of the application.

(defun dump-initial-slot-index-declarations ()
  (let ((names (tclosi:collect-slot-index-constants
		    *initial-global-environment*)))
    (setf names
	  (sort (mapcar #'(lambda (s) (c-name-of-global-variable s)) names)
		#'string<))
    (dolist (name names)
      (emit-format "~%extern Object ~a;" name))
    (emit-format "~%~%extern Object SI_Slot_index_min, SI_Slot_index_max;")))

(defun dump-slot-index-definitions (cpath hpath)
  (macrolet ((do-slot-index-triples (bindings triples &body body)
	       (let ((triple (gensym)))
		 `(dolist (,triple ,triples)
		    (destructuring-bind ,bindings ,triple
		      ,@body))))
	     (c-name (constant)
	       `(c-name-of-global-variable ,constant)))
    (let ((desc (format nil "slot index definitions for ~A"
			*application-name*))
	  (application ())
	  (kernel ())
	  (min 0)
	  (max 0))
      #| Lucid 4.0 destructuring-bind doesn't permit &WHOLE!
      (do-slot-index-triples
	  (&whole triple name constant index)
	  (sort (tclosi:compute-global-slot-indexes) #'string>
		:key #'(lambda (triple) (c-name (second triple))))
        (if (eq
              (tclosi:global-slot-index name *initial-global-environment* nil)
	      constant)
	    (push triple kernel)
	    (push triple application))
	(cond ((< index min) (setf min index))
	      ((< max index) (setf max index))))
      |#
      ;; Use this since &whole not always permitted.
      (dolist (triple (sort (tclosi:compute-global-slot-indexes) #'string>
			    :key #'(lambda (triple) (c-name (second triple)))))
	(destructuring-bind (name constant index) triple
	  (if (eq
	       (tclosi:global-slot-index name *initial-global-environment* nil)
	       constant)
	      (push triple kernel)
	      (push triple application))
	  (cond ((< index min) (setf min index))
		((< max index) (setf max index)))))
      (flet ((define-index (c-name index)
	       (emit-format "~%#define ~A ~E"
		       c-name (translate-constant-aux index))))
	(with-header-file (s hpath desc)
	  (do-slot-index-triples (name constant index) application
	    (declare (ignore name))
	    (define-index (c-name constant) index))))
      (flet ((define-index (c-name index)
	       ;; We'd like to put const qualifiers on these, but that's not
	       ;; supported by some traditional compilers.
	       (emit-format "~%Object ~A = ~E;"
			    c-name (translate-constant-aux index))))
	(with-header-file (s cpath desc)
	  (dump-default-includes)
	  (do-slot-index-triples (name constant index) kernel
	    (declare (ignore name))
	    (define-index (c-name constant) index))
	  (emit-newline)
	  (define-index "SI_Slot_index_min" min)
	  (define-index "SI_Slot_index_max" max))))))

)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Dump generic function entries
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun dump-generic-function-declaration
    (entry-name function-name descriptor)
  ;; *** This test really ought to be using function-descriptor-variadic-p,
  ;; *** but that function is currently broken because the changes to argument
  ;; *** processing are incomplete.  For now, use alternate method of getting
  ;; *** the information, but this should be fixed later.
  (if (lambda-list-info-restp (get-descriptor-lambda-list-info descriptor))
      ;; Variadic generic functions just get a normal function declaration in
      ;; header files.
      (dump-function-declaration-1 entry-name descriptor)
      ;; Positional generic functions get a macro definition in header files.
      (dump-positional-generic-function-declaration entry-name
						    function-name
						    descriptor)))

(defparameter *generic-function-arg-starts*
  (make-array 20 :fill-pointer 0 :adjustable t :element-type 'fixnum))
(defparameter *generic-function-arg-ends*
  (make-array 20 :fill-pointer 0 :adjustable t :element-type 'fixnum))
(defparameter *generic-function-args-string*
  (make-array 100 :fill-pointer 0 :adjustable t
	      :element-type '#.(array-element-type "")))

(defun initialize-generic-function-arguments-string (max-arg-count)
  (let ((starts *generic-function-arg-starts*)
	(ends *generic-function-arg-ends*))
    (when (< (length starts) max-arg-count)
      (setf (fill-pointer starts) 0)
      (setf (fill-pointer ends) 0)
      (let ((string *generic-function-args-string*))
	(setf (fill-pointer string) 0)
	(with-output-to-string (stream string)
	  (dotimes (i max-arg-count)
	    (unless (zerop i) (write-char #\, stream))
	    (vector-push-extend (length string) starts)
	    (format stream "a~D" i)
	    (vector-push-extend (length string) ends)))))))

(defun write-generic-function-arguments-string (count)
  (when (plusp count)
    (initialize-generic-function-arguments-string count)
    (emit-string *generic-function-args-string* 
		 0 (aref *generic-function-arg-ends* (1- count)))))

;;; The maximum value of "n" for which the runtime provides a definition for
;;; "GENERIC_FUNCTION_CALL_n()".
(defparameter *maximim-simple-positional-generic-function-definition* 10)

(defun dump-positional-generic-function-declaration
    (entry-name function-name descriptor)
  (let* ((info (get-descriptor-lambda-list-info descriptor))
	 (argq (lambda-list-info-positional info)))
    (with-documentation (function-descriptor-documentation descriptor)
      (emit-format "~%#define ~A(" entry-name)
      (write-generic-function-arguments-string argq)
      (if (<= argq *maximim-simple-positional-generic-function-definition*)
	  (progn
	    (emit-format ") \\~%    GENERIC_FUNCTION_CALL_~D(~A,"
			 argq (c-name-of-function-object function-name))
	    (write-generic-function-arguments-string argq)
	    (emit-char #\)))
	  (progn
	    (emit-format ") \\~%    (GENERIC_FUNCTION_CALL_START(), \\")
	    (let ((starts *generic-function-arg-starts*)
		  (ends *generic-function-arg-ends*)
		  (string *generic-function-args-string*))
	      (dotimes (i argq)
		(emit-format "~%     GENERIC_FUNCTION_CALL_ARG(")
		(emit-string string (aref starts i) (aref ends i))
		(emit-string "), \\")))
	    (emit-format "~%     GENERIC_FUNCTION_CALL(~A,~D))"
			 (c-name-of-function-object function-name) argq))))))

(defun dump-generic-function-definitions (data)
  (do-with-sorted-data ((entry-name function-name info) data)
    (when (and (function-descriptor-generic-function-p info)
	       (function-descriptor-variadic info))
      (dump-variadic-generic-function-definition
       entry-name function-name info))))

(defun dump-variadic-generic-function-definition
    (entry-name function-name descriptor)
  (with-documentation (function-descriptor-documentation descriptor)
    (emit-format "~%DEFINE_VARIADIC_GENERIC_FUNCTION(~A,"
		 entry-name)
    (emit-format "~%                                 ~A)~%"
		 (c-name-of-function-object function-name))))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Dump structure definitions
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun dump-user-structures (hpath &aux root)
  (with-header-file (out hpath "application-specific structures")
    (with-output-stream out
      (when (setf root (defined-as-structure untyped-structure-root-name))
        (dump-untyped-structures (structure-info-root-children root)))
      (when (setf root (defined-as-structure list-structure-root-name))
	(dump-list-structures (structure-info-root-children root)))
      (when (setf root (defined-as-structure vector-structure-root-name))
	(dump-vector-structures (structure-info-root-children root)))
      (dump-foreign-structures))))

(defun dump-foreign-structures ()
  (with-sorted-data
      (data *default-global-environment*
	    'defined-as-foreign-structure
	    #'(lambda (name) (symbol-name name))
	    #'(lambda (name fsinfo)
		(declare (ignore name fsinfo))
		t))
    (do-with-sorted-data ((struct-name fsname fsinfo) data)
      (declare (ignore struct-name fsname))
      (dump-foreign-structure fsinfo))))

;;; Dump definitions for foreign structures

(defun dump-foreign-structure (node)
  (let ((*package* (foreign-structure-info-package node)))
    (dump-foreign-header node)
    (dump-foreign-structure-definition node)
    (dump-foreign-structure-foreign-accessors node)))

(defun dump-foreign-header (node)
  (emit-toplevel-comments
    (list (sformat "Foreign Structure ~A" 
		   (foreign-structure-info-name node)))))

(defun dump-foreign-structure-definition (node)
  (emit-newline)
  (emit-single-type-declaration
   `(:struct nil 
	     ,@(mapcar #'(lambda (local-slot)
			   `(,(foreign-slot-info-foreign-type local-slot)
			     ,(make-c-name-of-slot local-slot)))
		       (foreign-structure-info-local-slots node)))
   (c-name-of-structure-type (foreign-structure-info-foreign-name node))
   :storage-class "typedef"))

(defmacro dump-and-split-c-macro-string (name-form &body forms)
  `(progn
     (emit-newline)
     (emit-string "#define ")
     ,name-form
     (emit-char #\space)
     (with-emit-and-split-string " \\"
       ,@forms)))

(defun dump-foreign-structure-foreign-accessors (node &aux local-slots)
  (when (setq local-slots (foreign-structure-info-local-slots node))
    (emit-newline)
    (mapc #'(lambda (foreign-accessor slot)
	      (let* ((macro-arg-name
		      (c-name-of-c-macro-arg
		       "O"
		       (list
			(c-name-of-structure-type
			 (foreign-structure-info-foreign-name node))
			(slot-info-c-name slot))))
		     (sft (translator-foreign-type-name 
			   (foreign-slot-info-foreign-type slot)))
		     (complex-p (defined-as-foreign-structure sft)))
		(dump-and-split-c-macro-string
		 (emit-format "~A(~A)" 
			      (c-name-of-function-entry foreign-accessor)
			      macro-arg-name)
		 (if complex-p
		     (emit-format "(&(~A)->~A)" 
				  macro-arg-name
				  (slot-info-c-name slot))
		     (emit-format "((~A)->~A)"
				  macro-arg-name
				  (slot-info-c-name slot))))))
	  (foreign-structure-info-local-slot-foreign-accessors node)
	  local-slots)))

;;; Dump definitions for "untyped" structures

(defun dump-untyped-structures (nodes &aux children)
  (dolist (node nodes)
    (setf node (defined-as-structure node))
    (let ((*package* (untyped-structure-info-package node)))
      (dump-untyped-header node)
      (dump-structure-definition node)
      (dump-untyped-predicate node)
      (dump-untyped-accessors node)
      (dump-untyped-copier node)
      (setf children (append children
			     (untyped-structure-info-children node)))))
  (when children
    (dump-untyped-structures children)))

(defun dump-untyped-header (node)
  (emit-toplevel-comments
    (list (sformat "Structure ~A" (untyped-structure-info-name node)))))

(defun make-c-name-of-slot (slot)
  (with-global-c-name-table
    (setf (slot-info-c-name slot)
	  (c-name-of-local-variable (slot-info-name slot)))))

(defun make-c-name-of-included-fields ()
  (with-global-c-name-table
    (c-name-of-local-variable "INCLUDED-FIELDS")))

(defun dump-structure-definition (node)
  (emit-newline)
  (let ((supertype (untyped-structure-info-foreign-supertype node)))
    (emit-single-type-declaration
     `(:struct nil 
	       (,(c-name-of-structure-type supertype)
		 ,(make-c-name-of-included-fields))
	       ,@(mapcar #'(lambda (local-slot)
			     `(:object ,(make-c-name-of-slot local-slot)))
			 (untyped-structure-info-local-slots node)))
     (c-name-of-structure-type (untyped-structure-info-foreign-name node))
     :storage-class "typedef")))

(defun dump-untyped-predicate (node)
  (emit-newline)
  (dump-and-split-c-macro-string
   (emit-format "~A(o)"
		(c-name-of-function-entry
		 (untyped-structure-info-foreign-predicate node)))
   (emit-format "(~A(o) && ~A(o,~D,~A))"
		(c-name-of-function-entry
		 (untyped-structure-info-structure-object-predicate node))
		(untyped-structure-info-primitive-predicate node)
		(untyped-structure-info-depth node)
		(c-name-of-quoted-symbol
		 (untyped-structure-info-name node)))))

(defun dump-untyped-accessors (node)
  (dump-untyped-included-slot-accessors node)
  (dump-untyped-local-slot-accessors node))

(defun dump-untyped-included-slot-accessors (node &aux included-slots)
  (when (setf included-slots (untyped-structure-info-included-slots node))
    (emit-newline)
    (mapc #'(lambda (foreign-accessor slot)
	      (dump-and-split-c-macro-string
	       (emit-format "~A(o)"
			    (c-name-of-function-entry foreign-accessor))
	       (emit-format "~A(o)"
			    (c-name-of-function-entry
			     (slot-info-native-foreign-accessor slot)))))
	  (untyped-structure-info-included-slot-foreign-accessors node)
	  included-slots)))

(defun dump-untyped-local-slot-accessors (node &aux local-slots)
  (when (setf local-slots (untyped-structure-info-local-slots node))
    (emit-newline)
    (mapc #'(lambda (foreign-accessor slot)
	      (let ((macro-arg-name
		     (c-name-of-c-macro-arg
		      "O"
		      (list
		       (c-name-of-structure-type
			(untyped-structure-info-foreign-name node))
		       (slot-info-c-name slot)))))
		(dump-and-split-c-macro-string
		 (emit-format "~A(~A)" 
			      (c-name-of-function-entry foreign-accessor)
			      macro-arg-name)
		 (emit-format "~A(~A,~A,~A)"
			      (slot-info-primitive-accessor slot)
			      macro-arg-name
			      (c-name-of-structure-type
			       (untyped-structure-info-foreign-name node))
			      (slot-info-c-name slot)))))
	  (untyped-structure-info-local-slot-foreign-accessors node)
	  local-slots)))

(defun dump-untyped-copier (node &aux foreign-copier)
  (when (setf foreign-copier (untyped-structure-info-foreign-copier node))
    (emit-newline)
    (dump-and-split-c-macro-string
     (emit-format "~A(o)" (c-name-of-function-entry foreign-copier))
     (emit-format "~A(o)"
		  (c-name-of-function-entry
		   (untyped-structure-info-primitive-copier node))))))

;;; Dump definitions for list structures

(defun dump-list-structures (nodes &aux children)
  (dolist (node nodes)
    (setf node (defined-as-structure node))
    (let ((*package* (list-structure-info-package node)))
      (dump-list-structure-header node)
      (dump-list-structure-predicate node)
      (dump-list-structure-accessors&setters node)
      (dump-list-structure-copier node)
      (setf children (append children (list-structure-info-children node)))))
  (when children
    (dump-list-structures children)))

(defun dump-list-structure-header (node)
  (emit-toplevel-comments
    (list (sformat "List Structure ~A" (list-structure-info-name node)))))

(defun dump-list-structure-predicate (node &aux foreign-predicate)
  (when (setf foreign-predicate (list-structure-info-foreign-predicate node))
    (emit-newline)
    (dump-and-split-c-macro-string
     (emit-format "~A(o)" (c-name-of-function-entry foreign-predicate))
     (emit-format "~A(o,~D,~A)"
		  (list-structure-info-primitive-predicate node)
		  (first (list-structure-info-named-name-indices node))
		  (c-name-of-quoted-symbol
		   (first (list-structure-info-named-names node)))))))

(defun dump-list-structure-accessors&setters (node)
  (dump-list-structure-included-slot-accessors node)
  (dump-list-structure-included-slot-setters node)
  (dump-list-structure-local-slot-accessors node)
  (dump-list-structure-local-slot-setters node))

(defun dump-list-structure-included-slot-accessors (node &aux included-slots)
  (when (setf included-slots (list-structure-info-included-slots node))
    (emit-newline)
    (mapc #'(lambda (foreign-accessor slot)
	      (dump-and-split-c-macro-string
	       (emit-format "~A(o)" 
			    (c-name-of-function-entry foreign-accessor))
	       (emit-format "~A(o)"
			    (c-name-of-function-entry
			     (slot-info-native-foreign-accessor slot)))))
	  (list-structure-info-included-slot-foreign-accessors node)
	  included-slots)))

(defun dump-list-structure-included-slot-setters
    (node &aux included-slot-setters)
  (when (setf included-slot-setters
	      (list-structure-info-included-slot-foreign-setters node))
    (emit-newline)
    (mapc #'(lambda (slot)
	      (when (slot-info-native-foreign-setter slot)
		(dump-and-split-c-macro-string
		 (emit-format "~A(o,n)"
			      (c-name-of-function-entry
			       (pop included-slot-setters)))
		 (emit-format "~A(o,n)"
			      (c-name-of-function-entry
			       (slot-info-native-foreign-setter slot))))))
	  (list-structure-info-included-slots node))))

(defun dump-list-structure-local-slot-accessors (node &aux local-slots offset)
  (when (setf local-slots (list-structure-info-local-slots node))
    (emit-newline)
    (mapc #'(lambda (foreign-accessor slot)
	      (dump-and-split-c-macro-string
	       (emit-format "~A(o)"
			    (c-name-of-function-entry foreign-accessor))
	       (if (> (setf offset (slot-info-offset slot)) 9)
		   (emit-format "~A(~E,o)"
				(c-name-of-function-entry
				 (slot-info-primitive-accessor slot))
				(translate-constant-aux offset))
		   (emit-format "~A(o)"
				(c-name-of-function-entry
				 (slot-info-primitive-accessor slot))))))
	  (list-structure-info-local-slot-foreign-accessors node)
	  local-slots)))

(defun dump-list-structure-local-slot-setters (node &aux local-slot-setters
						    offset)
  (when (setf local-slot-setters
	      (list-structure-info-local-slot-foreign-setters node))
    (emit-newline)
    (mapc #'(lambda (slot)
	      (when (slot-info-native-foreign-setter slot)
		(dump-and-split-c-macro-string
		 (emit-format "~A(o,n)"
			      (c-name-of-function-entry
			       (pop local-slot-setters)))
		 (if (> (setf offset (slot-info-offset slot)) 9)
		     (emit-format "~A(~E,o,n)"
				  (c-name-of-function-entry
				   (slot-info-primitive-setter slot))
				  (translate-constant-aux offset))
		     (emit-format "~A(o,n)"
				  (c-name-of-function-entry
				   (slot-info-primitive-setter slot)))))))
	  (list-structure-info-local-slots node))))

(defun dump-list-structure-copier (node &aux foreign-copier)
  (when (setf foreign-copier (list-structure-info-foreign-copier node))
    (emit-newline)
    (dump-and-split-c-macro-string
     (emit-format "~A(o)" (c-name-of-function-entry foreign-copier))
     (emit-format "~A(o)" (c-name-of-function-entry
			   (list-structure-info-primitive-copier node))))))

;;; Dump definitions for vector structures

(defun dump-vector-structures (nodes &aux children)
  (dolist (node nodes)
    (setf node (defined-as-structure node))
    (let ((*package* (vector-structure-info-package node)))
      (dump-vector-structure-header node)
      (dump-vector-structure-predicate node)
      (dump-vector-structure-accessors&setters node)
      (dump-vector-structure-copier node)
      (setf children (append children (vector-structure-info-children node)))))
  (when children
    (dump-vector-structures children)))

(defun dump-vector-structure-header (node)
  (emit-toplevel-comments
    (list (sformat "Vector Structure ~A"
		  (vector-structure-info-name node)))))

(defun dump-vector-structure-predicate (node &aux foreign-predicate)
  (when (setf foreign-predicate (vector-structure-info-foreign-predicate node))
    (emit-newline)
    (dump-and-split-c-macro-string
     (emit-format "~A(o)"
		  (c-name-of-function-entry foreign-predicate))
     (emit-format "~A(o,~D,~A)"
		  (vector-structure-info-primitive-predicate node)
		  (first (vector-structure-info-named-name-indices node))
		  (c-name-of-quoted-symbol
		   (first (vector-structure-info-named-names node)))))))

(defun dump-vector-structure-accessors&setters (node)
  (dump-vector-structure-included-slot-accessors node)
  (dump-vector-structure-included-slot-setters node)
  (dump-vector-structure-local-slot-accessors node)
  (dump-vector-structure-local-slot-setters node))

(defun dump-vector-structure-included-slot-accessors (node &aux included-slots)
  (when (setf included-slots (vector-structure-info-included-slots node))
    (emit-newline)
    (mapc #'(lambda (foreign-accessor slot)
	      (dump-and-split-c-macro-string
	       (emit-format "~A(o)"
			    (c-name-of-function-entry foreign-accessor))
	       (emit-format "~A(o)"
			    (c-name-of-function-entry
			     (slot-info-native-foreign-accessor slot)))))
	  (vector-structure-info-included-slot-foreign-accessors node)
	  included-slots)))

(defun dump-vector-structure-included-slot-setters
    (node &aux included-slot-setters)
  (when (setf included-slot-setters
	      (vector-structure-info-included-slot-foreign-setters node))
    (emit-newline)
    (mapc #'(lambda (slot)
	      (when (slot-info-native-foreign-setter slot)
		(dump-and-split-c-macro-string
		  (emit-format "~A(o,n)"
			       (c-name-of-function-entry
				(pop included-slot-setters)))
		  (emit-format "~A(o,n)"
			       (c-name-of-function-entry
				(slot-info-native-foreign-setter slot))))))
	  (vector-structure-info-included-slots node))))

(defun dump-vector-structure-local-slot-accessors (node &aux local-slots)
  (when (setf local-slots (vector-structure-info-local-slots node))
    (emit-newline)
    (mapc #'(lambda (foreign-accessor slot)
	      (dump-and-split-c-macro-string
	       (emit-format "~A(o)"
			    (c-name-of-function-entry foreign-accessor))
	       (emit-format "~A(o,~E)"
			    (c-name-of-function-entry
			     (slot-info-primitive-accessor slot))
			    (translate-constant-aux (slot-info-offset slot)))))
	  (vector-structure-info-local-slot-foreign-accessors node)
	  local-slots)))

(defun dump-vector-structure-local-slot-setters (node &aux local-slot-setters)
  (when (setf local-slot-setters
	      (vector-structure-info-local-slot-foreign-setters node))
    (emit-newline)
    (mapc #'(lambda (slot)
	      (when (slot-info-native-foreign-setter slot)
		(dump-and-split-c-macro-string
		 (emit-format "~A(o,n)"
			      (c-name-of-function-entry
			       (pop local-slot-setters)))
		 (emit-format "~A(o,~E,n)"
			      (c-name-of-function-entry
			       (slot-info-primitive-setter slot))
			      (translate-constant-aux
			       (slot-info-offset slot))))))
	  (vector-structure-info-local-slots node))))

(defun dump-vector-structure-copier (node &aux foreign-copier)
  (when (setf foreign-copier (vector-structure-info-foreign-copier node))
    (emit-newline)
    (dump-and-split-c-macro-string
     (emit-format "~A(o)" (c-name-of-function-entry foreign-copier))
     (emit-format "~A(o)" (c-name-of-function-entry
			   (vector-structure-info-primitive-copier node))))))

(defun make-c-names-of-slots (slots)
  (with-global-c-name-table
    (dolist (slot slots)
      (setf (slot-info-c-name slot)
	    (c-name-of-local-variable (slot-info-name slot))))
    (c-name-of-local-variable "INCLUDED-FIELDS")))

(defun c-name-of-local-variable (name)
  (multiple-value-bind (string case)
      (string-canonicalize-case (string-trim-stars name))
    (string->c-name string t
		    :case case
		    :symbol (when (symbolp name) name))))

(defun c-name-of-c-macro-arg (arg c-macro-var-names)
  (with-global-c-name-table
    (dolist (name c-macro-var-names)
      (record-global-c-name name))
    (c-name-of-local-variable arg)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Dump User Header File
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defun dump-system-header-file (user-pn &rest pathnames)
  (with-header-file (ostream user-pn "User Header File")
    (terpri ostream)
    ;;(format ostream "~%#define SKIP_SI_VARIADIC_KEYWORD_FUNCTIONS~%")
    ;; output kernel.h first
    (dolist (pn #+translator-supports-thread
		(cons "kernel" (cons "uconfig" (cons "uspecial" pathnames)))
		#-translator-supports-thread
		(cons "kernel" (cons "uconfig" pathnames)))
      (when pn
	(format ostream "~%#include ~S"
		(namestring* pn
			     :type *translate-file-header-type*
			     :relative-to-directory user-pn))))))


;;; The rest of this is from patch 25, but is as far as I can tell not
;;; called anywhere. Maybe dump-initial-files is supposed to be part of the
;;; API??
(defun merge-directory (directory)
  (let ((defaults (merge-pathnames
		   (make-pathname :defaults *default-pathname-defaults*
				  :directory directory))))
    (make-pathname :defaults defaults
		   :name nil :type nil :version nil)))

(defparameter *default-code-directory*
  '(:relative "src"
    #-translator-supports-clos "core"
    #+translator-supports-clos "clos"))

(defparameter *default-header-directory*
  '(:relative "include"))

(defun dump-initial-files
    (&key (default-code-pathname 
	   (merge-directory *default-code-directory*))
	  (default-header-pathname 
	   (merge-directory *default-header-directory*))
	  (symbols-pathname *default-symbols-pathname*)
	  (symbols-code-pathname *default-symbols-code-pathname*)
	  (functions-pathname *default-functions-pathname*)
	  (small-functions-pathname *default-small-functions-pathname*)
	  ((:verbose *verbose*) t)
	  (symbol-init-statements-per-file 20000)
	  #+translator-supports-clos
	  (clos-info-pathname *default-clos-info-pathname*)
	  #+translator-supports-clos
	  (clos-init-pathname *default-clos-init-pathname*))
  (declare (special *verbose*))
  (let ((*symbol-init-statements* '())
	(*symbol-init-statements-per-file* symbol-init-statements-per-file))
    (dump-initial-symbols 
     (code-pathname symbols-pathname default-code-pathname)
     (header-pathname symbols-pathname default-header-pathname))
    (dump-initial-symbol-init-function
     (code-pathname symbols-code-pathname default-code-pathname)))
  (dump-initial-functions
   (code-pathname functions-pathname default-code-pathname)
   (header-pathname functions-pathname default-header-pathname))
  (dump-small-initial-functions
   (code-pathname small-functions-pathname default-code-pathname)
   (header-pathname small-functions-pathname default-header-pathname))
  #+translator-supports-clos
  (progn
    (dump-initial-slots-header
     (header-pathname clos-info-pathname default-header-pathname))
    (tclosi:dump-clos-bootstrap-info 
     clos-init-pathname
     :output-file (code-pathname clos-init-pathname default-code-pathname)
     :h-file (header-pathname clos-init-pathname default-header-pathname)))
  nil)

#+translator-supports-thread
(defun dump-user-special-header-file (hpath)
  (with-header-file (out hpath "application-defined special variables in form of C macro")
    (with-sorted-data
	(data *default-global-environment*
	      'defined-as-variable
	      #'(lambda (name) (c-name-of-global-variable name))
	      #'(lambda (name desc)
		  (and (variable-descriptor-global-p desc)
		       (not (defined-as-variable name
				*initial-global-environment*))
                       ;; ignore some special variables which shouldn't be defined in uspecial.h
                       (not (member (c-name-of-global-variable name)
                                    tutil::*ignored-special-variables* :test #'equal))
		       (not (variable-descriptor-constant-p desc))
		       (variable-descriptor-special-p desc))))
      (emit-newline)

      (emit-format "#if SI_SUPPORT_THREAD~%")
      (emit-newline)

      ;;; Part 1: struct SI_Special_data
      (emit-format "struct SI_Tls_data {~%")
      (emit-format "    INCLUDE_SI_SPECIAL(Object, LOCAL);~%")
      (do-with-sorted-data ((entry-name variable-name descriptor) data)
	(declare (ignore variable-name descriptor))
	(emit-format "    Object ~A_LOCAL;~%" entry-name))
      (emit-format "};~%")
      (emit-newline)

      ;;; Part 2: struct SI_Special_count
      (emit-format "struct SI_Tls_count {~%")
      (emit-format "    INCLUDE_SI_SPECIAL(short, COUNT);~%")
      (do-with-sorted-data ((entry-name variable-name descriptor) data)
	(declare (ignore variable-name descriptor))
	(emit-format "    short ~A_COUNT;~%" entry-name))
      (emit-format "};~%")
      (emit-newline)

      ;;; Part 3: All #defines
      (do-with-sorted-data ((entry-name variable-name descriptor) data)
	(declare (ignore variable-name descriptor))
	(emit-format "#define ~A SPECIAL_VALUE(~A)" entry-name entry-name)
	(emit-newline))

      (emit-newline)
      (emit-format "#endif /* SI_SUPPORT_THREAD */"))))

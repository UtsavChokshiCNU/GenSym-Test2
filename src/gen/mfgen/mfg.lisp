;;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: USER -*-
(in-package "USER")

;;;; Module MFG (makefile generator)
;;;
;;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;;  All Rights Reserved.
;;;
;;;; Author: Mark E. Staknis
;;;
;;;; Description:
;;;      This module contains utilities and data definitions needed to
;;;    generate makefiles.  It relies on rdb.lisp as an interface to the
;;;    database. The module is divided into sections and provides an
;;;    interface described below.
;;;
;;;; Dependencies: rdb.lisp
;;;
;;;; File Organization and External Interface:
;;;      The file is divided into a few major sections. The sections and
;;;    their contents are listed below.  For more detail, see the section
;;;    and function headers.
;;;    
;;;    Structure Definitions
;;;      mftenv structure: Maintains values passed during template processing
;;;        in the single instance "env".
;;;      mftdep structure: Substructure of mftenv; contains information about
;;;        dependencies of current target.
;;;      mftinstall structure: Substructure of mftenv; contains information
;;;        needed while generating the "install" target.
;;;
;;;    Printing Functions and Macros
;;;      mfg-downcase-symbol (value): Returns value as lower-case string
;;;        if it's a symbol.
;;;      mfg-print-downcased (value): Prints lower-case if a symbol and prints
;;;        ascii otherwise.
;;;      mfg-format-variable-use (name):  Prints name as $(name).
;;;      mfg-print-list-with-space-separators (list): Prints atoms downcased
;;;        and separated by single spaces.
;;;      mfg-print-list-with-comma-separators (list): Prints atoms downcased
;;;        and separated by ", ".
;;;      mfg-print-list-without-separators (list): Prints atoms downcased
;;;        and concatenated.
;;;      mfg-print-strings-with-continuation-lines
;;;        (initial-length list-of-strings): Prints strings separated by
;;;        spaces on maximum 78-character lines with continuation lines.
;;;      mfg-print-include-path-options (include-path-list):
;;;        Prints each directory prefixed with "-I" and followed by a space.
;;;
;;;    Macros for Attribute Access and Formatting
;;;      mfg-compile-category-to-directory (compile-category):
;;;        Returns opt for optimize, o for debug, and o-pg for profile.
;;;      mfg-full-filename-string (directory delimiter file-root suffix): 
;;;        Concatenates elements to form a full path name.
;;;      mfg-file-type-suffix (file-type operating-system):
;;;        Returns ".<suffix>" with <suffix> found appropriately.
;;;      mfg-directory-delimiter (operating-system): Returns delimiter
;;;        that separates directory from filename.
;;;
;;;    Functions for Formatting Dependencies as Lists of Strings
;;;      mfg-local-dependencies-to-list-of-strings 
;;;        (type delimiter operating-system local-deependency-view
;;;         list &optional suffix):
;;;        Each local dependency is given full-path representation.
;;;      mfg-nonlocal-dependencies-to-list-of-strings
;;;        (type delimiter operating-system platform-group-priority-view
;;;         nonlocal-dependency-view list-of-dependencies &optional suffix):
;;;        Each non-local dependency is given full-path representation.
;;;      mfg-variable-dependencies-to-list-of-strings (list):
;;;        Variable dependencies are represented as strings of form $(<var>).
;;;      mfg-dependencies-to-list-of-strings (env):  Formats all dependencies
;;;        as strings, distinguishing local, variable and non-local types.
;;;
;;;    Functions and Macros for Special Database Selection
;;;      mfg-database (relation-name): Returns relation from database.
;;;      mfg-select-local-directory (type):  Accesses "local-location-relation"
;;;        to find directory for the given file type.
;;;      mfg-select-nonlocal-directory
;;;        (target-group-priority-view platform-group-priority-view):
;;;        Accesses "nonlocal-location-relation" to find nonlocal directory.
;;;      mfg-select-template
;;;        (category product-group-priority-view platform-group-priority-view):
;;;        Selects highest priority template from "template-relation".
;;;      mfg-select-command (command-type platform-group-priority-view):
;;;        Selects highest priority command from "commands-relation".
;;;      mfg-select-command-options-to-string
;;;        (option-category additive-option-category
;;;         options-to-string-function env): Creates and returns an option
;;;         string or variable for the current target, platform, etc.
;;;      mfg-construct-option-list-string: internal function; the macro
;;;        mfg-select-command-options-to-string should be used as a wrapper.
;;;
;;;    Functions for Setting up and Dealing with Groups
;;;      mfg-create-target-group-priority-view (target type):
;;;        Creates the target-group-view needed for most target selection.
;;;      mfg-create-group-priority-view
;;;        (member groups-relation group-priorities-relation):
;;;        General means to create a group-priority view.
;;;      mfg-highest-priority-group
;;;        (group-attribute group-priority-view relation):
;;;        Returns name of highest-priority group in relation.
;;;      ------------------
;;;        The following group of functions is largely self-explanatory.  See
;;;        the function headers for details.
;;;      mfg-select-highest-priority-group-rows
;;;      mfg-select-highest-priority-group-value
;;;      mfg-select-all-group-rows
;;;      mfg-select-target-group-rows
;;;      mfg-select-target-group-value
;;;      mfg-select-platform-product-group-rows
;;;      mfg-select-platform-product-group-value
;;;      mfg-select-all-platform-product-group-rows
;;;      mfg-select-platform-target-group-rows
;;;      mfg-select-platform-target-group-value
;;;      mfg-select-all-platform-target-group-rows
;;;
;;;    Functions for Dealing with Makefile Variables (a.k.a. "Macros")
;;;      mfg-print-variable-definitions (variable-position-value-view):
;;;        Orders and prints variable definitions in proper format.
;;;      mfg-declared-variable-name-and-position
;;;        (variable-category type-group target-group platform-group):
;;;        If a declaration in variable-declaration-relation exists,
;;;        returns (variable-name position) for the given variable-category
;;;        and groups, otherwise returns nil.
;;;      mfg-install-variable-and-position-and-value
;;;        (variable-name position variable-value variable-value-view):
;;;        Adds a new row to the variable-value-view.
;;;
;;;    Foundational Functions
;;;      mfg-establish-dependencies (env): For current target, determines
;;;        dependencies and sets fields in mftdep substructure of env.
;;;      mfg-generate-targets (template target-list env):  Iterates through
;;;        target-list, setting up environment and running process-template
;;;        for each target.
;;;      mfg-process-template (template env): Processes the template from
;;;        left to right, printing literals and dispatching symbols with
;;;        (funcall MFGTF-<symbol> env)
;;;      mfg-lazy-select-rows-of-option-category: currently unused due to
;;;        implementation obstacles
;;;
;;;; Notes and reminders:
;;;      Nonlocal libraries are troublesome.  To avoid executables that depend
;;;    on them, all of their dependencies would have to be explicitly named.
;;;    If * dependencies are allowed, there may be hope.
;;;      ---
;;;      Variable targets are very useful, but they must be set up with care.
;;;    They are pseudo targets that simply define variables for groups of
;;;    targets.  Because they are alphabetized, and because mms requires a
;;;    definition to precede its use, it is best to limit variable targets to
;;;    a single level. In those rare cases where multiple levels are necessary,
;;;    it can be achieved by giving prior levels names that are earlier in the
;;;    alphabet.
;;;      Another problem concerns linking.  Variable dependencies are included
;;;    in link command lines.  For executable dependencies, these _must_
;;;    therefore be restricted to groups object files; i.e., for an executable
;;;    that depends on a variable target, the variable must be restricted to
;;;    object files. If libraries are included, they might appear in an
;;;    inappropriate position unless the variables were set up very
;;;    carefully.






;;;; Structure Definitions
;;;    This section defines the env structure and substructures used in
;;;    makefile generation. 

;;; structure: mftenv
;;; description: An instance of this structure maintains the global environment
;;;   of template functions (discussed below) during generation of a single
;;;   makefile.  Each slot has a specified purpose and usage.  Slots are
;;;   conventionally read-only for descendents in the template function
;;;   calling hierarchy (i.e., they are rarely used to return a value to a
;;;   caller).  They are used primarily to pass information cleanly down or
;;;   laterally (to siblings) within the calling hierarchy.
;;; slot descriptions:
;;;     to be added
;;;     variable-target-list is a pseudo target list, since no entry is
;;;   generated
;;;     object-default-replacment takes its value from the default-
;;;   replacement field of object-default-entry-relation and determines
;;;   where, if any, a format string will be used.
;;; modifications:
;;;     jv, 6/19/96: added slots for shared-object-target-list and nonlocal-
;;;   shared-object-target-list.

(defstruct mftenv
  (platform nil)
  (product nil)
  (compile-category nil)
  (target nil)
  (target-type nil)
  (operating-system nil)
  (objects-per-command nil)
  (nonstandard-objects-list nil)
  (object-default-replacement)
  (compile-entry-format-string "")
  (compile-body-format-string  "")
  (filename nil)
  (platform-group-priority-view nil)
  (product-group-priority-view nil)
  (target-group-priority-view nil)
  (variable-value-view nil)
  (local-location-view nil)
  (nonlocal-location-view nil)
  (category-view-list-cons '(()) )     ; a wrapper for a property list
  (dependency-view nil)
  (command-options-view nil)
  (dummy-target-list nil)              ; lists of targets for makefile
  (variable-target-list nil)
  (library-target-list nil)
  (dll-library-target-list nil)
  (shared-object-target-list nil)
  (nonlocal-library-target-list nil)
  (nonlocal-object-target-list nil)
  (executable-target-list nil)
  (dll-executable-target-list nil)
  (object-target-list nil)
  (resource-target-list nil)
  (target-dependencies (make-mftdep))  ; a substructure for dependency info
  (current-dir nil)
  (directory-delimiter nil)
  (compile-command nil)
  (install-slots (make-mftinstall))    ; a substructure for installation info
  (tmp-list nil))                      ; to pass a rare list




;;; structure: mftdep
;;; description: Contains lists of dependencies for the current target. The
;;;   lists are set during template processing by mfg-establish-dependencies.
;;;   Each slot maintains a list of dependencies of the indicated type.
;;; slot descriptions:
;;;   to be added
;;; modifications:
;;;     jv, 6/19/96: added slots shared-object, shared-object-unsorted,
;;;   nonlocal-shared-object, nonlocal-shared-object-unsorted.


(defstruct mftdep
  (dummy nil)
  (variable nil)
  (library nil)
  (library-unsorted nil)
  (dll-library nil)
  (dll-library-unsorted nil)
  (nonlocal-library nil)
  (nonlocal-library-unsorted nil)
  (shared-object nil)
  (shared-object-unsorted nil)
  (nonlocal-object nil)
  (nonlocal-object-unsorted nil)
  (executable nil)
  (dll-executable nil)
  (object nil)
  (object-unsorted nil)
  (resource nil)
  (resource-unsorted nil)
  (include nil)
  (nonlocal-include nil)
  (c nil)
  (opt nil)           ;opt files are strictly for vms
  (nonlocal-opt nil))




;;; structure: mftinstall
;;; description: Contains slots to pass information needed to create lines of
;;;   the install target.
;;; slot descriptions:
;;;   to be added

(defstruct mftinstall
  (destination-view nil)
  (install-rename-view nil)
  (name nil)
  (suffix nil)
  (source-dir nil)
  (destination-dir nil)
  (distribution nil)
  (parts-filetype nil)
  (partslist nil)
  (parts-subdir nil))






;;;; Printing Functions and Macros
;;;    This section contains functions and macros that print output
;;;    directly to the makefile.




;;; macro: mfg-downcase-symbol
;;; arguments:
;;;   value: an atom
;;; return value: the value, but as a lower-case string if it's a symbol
;;; description: Makes a symbol suitable for printing.
;;; scope: internal

(defun mfg-downcase-symbol (value)
  (if (symbolp value)
      (or (get value 'downcase)
	  (setf (get value 'downcase)
		(format () "~(~a~)" value)))
      value))




;;; macro: mfg-print-downcased
;;; arguments:
;;;   value: an atom
;;; return-value: nil
;;; description: prints the value to standard output converted to lower
;;;   case if it's a symbol
;;; scope: internal

(defun mfg-print-downcased (value)
  (let ((value (mfg-downcase-symbol value)))
    (if (stringp value)
	(write-string value)
	(format t "~a" value))))




;;; macro: mfg-format-variable-use
;;; arguments:
;;;   name: a variable name
;;; return value: a string of form "$(variable-name)"
;;; description: Converts a variable-name into the form needed for macro
;;;   expansion in a makefile. Note that variable names are upper-case.
;;; scope: internal

(defun mfg-format-variable-use (name)
  (if (symbolp name)
      (or (get name 'mf-variable)
	  (setf (get name 'mf-variable)
		(format () "$(~a)" name)))
      (format () "$(~a)" name)))




;;; function: mfg-print-list-with-space-separators
;;; arguments:
;;;   list: a list of atoms
;;; return value: nil
;;; description: Prints the atoms separated by spaces. Care is taken not to
;;;   precede or follow an empty string by a space.
;;; note: Printing a single space separator is achieved by maintaining a
;;;   Boolean needs-a-separator that determines whether a space should
;;;   precede the next non-empty-string to be printed.
;;; scope: internal

(defun mfg-print-list-with-space-separators (list)
  (loop
    with needs-a-separator = nil
    for tail on list
    for value = (car tail)
    do
    (if (not (rdb-equal "" value)) 
	(progn
	  (if needs-a-separator
	      (progn
		(write-char #\space)
		(setf needs-a-separator nil)))
	  (mfg-print-downcased value)
	  (setf needs-a-separator t)))))




;;; function: mfg-print-list-with-comma-separators
;;; arguments:
;;;   list: a list of atoms
;;; return value: nil
;;; description: Prints the atoms separated by ", ". Care is taken not to
;;;   precede or follow an empty string by a separator.
;;; note: Printing separator is achieved by maintaining a
;;;   Boolean needs-a-separator that determines whether a separator should
;;;   precede the next non-empty-string to be printed.
;;; scope: internal

(defun mfg-print-list-with-comma-separators (list)
  (loop
    with needs-a-separator = nil
    for tail on list
    for value = (car tail)
    do
    (if (not (rdb-equal "" value)) 
	(progn
	  (if needs-a-separator
	      (progn
		(format t ", ")
		(setf needs-a-separator nil)))
	  (mfg-print-downcased value)
	  (setf needs-a-separator t)))))



;;; function: mfg-print-strings-with-continuation-lines
;;; arguments:
;;;   initial-length: number of characters already in current line
;;;   list: a list of strings
;;; return value: number of characters in current line
;;; description: Prints strings in the list with spaces between them.
;;;   A count is maintained of the line length, and if it is
;;;   to be exceeded, the \ line continuation character and a newline are
;;;   first printed.  initial-length is passed to account for already-
;;;   printed characters, and line-length is returned to indicate where
;;;   in the line the printing stopped.
;;; notes: a space separator is printed between each string, and this is taken
;;;   into account in line-length.  No space is printed after the final string
;;;   but the line-length is incremented anyway.  It doesn't make much
;;;   difference that it's off by one.
;;; scope: internal

(defun mfg-print-strings-with-continuation-lines (initial-length
						   list-of-strings)
  (loop
    with line-length = initial-length
    for tail on list-of-strings
    for string = (car tail)
    for string-length = (length string)
    do (if (< (+ line-length string-length) 78)
	   (progn
	     (if (stringp string)
		 (write-string string)
		 (format t "~a" string))
	     (when (cdr tail) (write-char #\space))
	     (setf line-length (+ line-length string-length 1)))
	   (progn
	     (format t "\\~%  ~a" string)
	     (when (cdr tail) (write-char #\space))
	     (setf line-length (+ string-length 3))))
    finally
      (return line-length)))




;;; function: mfg-print-include-path-options
;;; arguments:
;;;   include-path-list: a list of paths of include-file directories
;;; return value: nil
;;; description: Prints each directory in the list in the default format
;;;   for most operating systems; i.e., with format
;;;          "-I<path1> -I<path2>..."
;;; scope: internal

(defun mfg-print-include-path-options (include-path-list)
  (if include-path-list
      (loop
	for path-tail on include-path-list
	do
	(format t "-I~a~a"
		(mfg-downcase-symbol (car path-tail))
		(if (cdr path-tail) " " "")))))







;;;; Macros for Attribute Access and Formatting
;;;    This section contains macros that provide quick access
;;;    to names that are relatively stable and defined by the system.
;;;    It also contains macros for quick filename formatting.




;;; macro: mfg-compile-category-to-directory
;;; arguments:
;;;   compile-category: optimize, debug, mt-debug, profile, or optimize-intc
;;; return value: the corresponding Gensym directory classification
;;; description: Determines the name that Gensym uses for the corresponding
;;;   directory.
;;; scope: internal
	 
(defmacro mfg-compile-category-to-directory (compile-category)
  `(case ,compile-category
     (optimize "opt")
     (debug "o")
     (mt-debug "o-mt")
     (profile "o-pg")
     (optimize-intc "opt-intc")))




;;; macro: mfg-full-filename-string
;;; arguments:
;;;   directory: directory in which the file resides (may be "")
;;;   delimiter: path delimiter for the operating system
;;;   file-root: an atom
;;;   suffix: the file suffix (may be "")
;;; return value: a string containing the path, filename, and suffix
;;; description:  Stores the dependency in a string with format of either
;;;       <directory><delimiter><name><suffix> or <name><suffix>
;;;   The latter is used if the directory name is empty
;;; scope: internal

(defmacro mfg-full-filename-string (directory delimiter file-root suffix)
  `(if (rdb-equal ,directory "")
       (format () "~a~a"
	       (mfg-downcase-symbol ,file-root)
	       ,suffix)
       (format () "~a~a~a~a"
	       (mfg-downcase-symbol ,directory)
	       ,delimiter
	       (mfg-downcase-symbol ,file-root)
	       ,suffix)))




;;; macro: mfg-file-type-suffix
;;; arguments:
;;;   file-type: the type of the file
;;;   operating-system: the operating system type (e.g., unix, win32)
;;; return value: the suffix for the given file type and operating system
;;; description: Determines the suffix for the given type and operating
;;;   system and returns it as a string.  If no explicit file type is present,
;;;   the type name is used preceded by a '.' and printed in lowercase.
;;; notes: This information would best be stored in a relation if efficiency
;;;   were not a concern.
;;; modifications:
;;;     jv, 6/19/96: added a case for dynamically linked shared object archives.
;;;   The Unix suffix for shared objects is ".so".
;;;     jv, 11/21/03: change the symbol corresponding to shared objects from
;;;   'so to 'dso (dynamic shared object).
;;; scope: internal

(defmacro mfg-file-type-suffix (file-type operating-system)
  `(case ,file-type
     (h       ".h")
     (dum     ""  )
     (c       ".c")
     (c++     ".cpp")
     (opt     ".opt")
     (obj
      (case ,operating-system
	(unix ".o"  )
	(t    ".obj")))
     (exe
      (case ,operating-system
	(unix ""   )
	(t    ".exe")))
     (dexe    ".exe")
     (lib
      (case ,operating-system
	(unix ".a")
	(t    ".lib")))

     ;; The following illustrates the difference between 'dlib and 'dso.  They
     ;; both refer to dynamically linked libraries.  When one builds a dll on
     ;; Windows, two meaningful files are produced.  foo.dll contains all of
     ;; the code and is loaded into the image at run time, but foo.lib is
     ;; necessary to make it work.  foo.lib contains stubs which are linked into
     ;; the image statically, which allows the dll to work.  Therefore, building
     ;; the executable depends on foo.lib, not foo.dll, and so the target in the
     ;; makefile should be foo.lib.  That's why the suffix for 'dlib is ".lib".
     ;; However, for the install target, what we actually want to ship is the
     ;; dll file; we denote the file as a 'dso in that case.  This is sort of
     ;; brain-dead, and maybe the makefile generator should just know how to
     ;; build and ship dll files, but it doesn't, and this pretty much seems
     ;; to work.  -jv, 11/24/03
     (dlib    ".lib")
     (dso
      (case ,operating-system
	(unix ".so")
	(t    ".dll")))

     (mak     "")
     (dkb     ".kb")
     (skb     ".kb")
     (tkb     ".kb")
     (ukb     ".kb")
     (dkl     ".kl")
     (skl     ".kl")
     (tkl     ".kl")
     (ukl     ".kl")
     (dtxt    ".txt")
     (stxt    ".txt")
     (ttxt    ".txt")
     (utxt    ".txt")
     (dgif    ".gif")
     (sgif    ".gif")
     (tgif    ".gif")
     (ugif    ".gif")
     (dxbm    ".xbm")
     (sxbm    ".xbm")
     (txbm    ".xbm")
     (uxbm    ".xbm")
     (t   (format () ".~(~a~)" ,file-type))))




;;; macro: mfg-directory-delimiter
;;; arguments:
;;;   operating-system: the operating system type (e.g., unix, win32)
;;; return value: the delimiter that separates a directory path from a filename
;;; description: Determines the delimiter for the given operating system.
;;; scope: internal
	 
(defmacro mfg-directory-delimiter (operating-system)
  `(case ,operating-system
     (unix    "/"  )
     (win32   "\\" )))






;;;; Functions for Formatting Dependencies as Lists of Strings
;;;    This section contains functions that provide an intermediate
;;;    step of formatting dependencies for printing.




;;; function: mfg-local-dependencies-to-list-of-strings
;;; arguments:
;;;   type: the type of the dependencies
;;;   delimiter: the directory/file separator (may be "")
;;;   operating-system: unix, win32, etc.
;;;   local-location-view: directory locations for given types
;;;   list: a list of dependencies
;;;   &suffix: if present, this suffix is used, otherwise the default for the
;;;     type and operating system is determined (optional)
;;; return value: a list of strings
;;; description: For each dependency in the list, a string is obtained for
;;;   the path and file name, and the string is added to a list that is
;;;   returned.
;;; scope: internal

(defun mfg-local-dependencies-to-list-of-strings (type
						   delimiter
						   operating-system
						   local-location-view
						   list
						   &optional suffix)
  (loop
    with directory = (mfg-select-local-directory type local-location-view)
    with file-suffix = (if suffix
			   suffix
			   (mfg-file-type-suffix type operating-system))
    for dependency in list
    collect (mfg-full-filename-string
	      directory
	      delimiter
	      dependency
	      file-suffix)))




;;; function: mfg-nonlocal-dependencies-to-list-of-strings
;;; arguments:
;;;   type: the type of the dependencies
;;;   delimiter: the directory/file separator (may be "")
;;;   operating-system: unix, win32, etc.
;;;   platform-group-priority-view: groups and priorities of current platform
;;;   nonlocal-location-view: file locations for current platform and product
;;;   list-of-dependencies: the nonlocal dependencies
;;;   &suffix: if present, this suffix is used, otherwise the default for the
;;;     type and operating system is determined (optional)
;;; return value: a list of strings
;;; description: For each dependency in the list, looks up its directory
;;;   location, obtains string representing path and file name, and adds the
;;;   string to a list of strings that is returned.
;;; scope: internal

(defun mfg-nonlocal-dependencies-to-list-of-strings
    (type
      delimiter
      operating-system
      platform-group-priority-view
      list-of-dependencies
      nonlocal-location-view
      &optional suffix )
  (loop
    with file-suffix
    = (if suffix
	  suffix
	  (mfg-file-type-suffix type operating-system))
    for dependency in list-of-dependencies
    collect (mfg-full-filename-string
	      (mfg-select-nonlocal-directory
		(mfg-create-target-group-priority-view dependency type)
		platform-group-priority-view
		nonlocal-location-view)
	      delimiter
	      dependency
	      file-suffix)))




;;; function: mfg-variable-dependencies-to-list-of-strings
;;; arguments:
;;;   list: a list of dependencies
;;; return value: a list of strings of form "$(<dependencies>)"
;;; description: For each dependency in the list, the dependency is represented
;;;   in a string as a variable reference, and the string is added to a list
;;;   that is returned.
;;; note: this function is intended solely to format pseudo dependencies
;;;   stored in (mftenv-variable-target-list env)
;;; scope: internal

(defun mfg-variable-dependencies-to-list-of-strings (list)
  (loop
    for variable in list
    collect (mfg-format-variable-use variable)))




;;; function: mfg-dependencies-to-list-of-strings
;;; arguments:
;;;   env: the environment of template functions
;;; return value: nil
;;; description: Collects all dependencies for the current target as strings of
;;;   form either <directory-><directory-delimiter><target><suffix>
;;;   or <target><suffix>. The latter is used for files in the current
;;;   directory.  Dependencies are ordered as indicated at the end of the
;;;   function.
;;; notes:  To avoid printing unnecessary spaces between possibly
;;;   empty dependencies, dependencies of a particular type are collected
;;;   into a string then printed all at once in the desired order.
;;;   The lists of dependencies are set in env by mfg-establish-dependencies.
;;; modifications:
;;;     mes 5/19/95:  Replaced nonlocal-libraries-string-list with a
;;;   conventional file name.  Previously it was a special dummy that
;;;   triggered a dummy rule that would invoke "make" for the library in the
;;;   nonlocal directory.
;;;     jv, 6/19/96: Added "shared objects" as a dependency type.  A
;;;   shared object should be handled in exactly the same way as a
;;;   library.  The only difference (as far as the makefile is concerned
;;;   is the suffix.  For this function, I have just duplicated the
;;;   code concerning libraries, substituting shared object for library.
;;; scope: internal

(defun mfg-dependencies-to-list-of-strings (env)
  (let*
      ((dependencies (mftenv-target-dependencies env))
       (operating-system (mftenv-operating-system env))
       (delimiter (mftenv-directory-delimiter env))
       (pgp-view (mftenv-platform-group-priority-view env))
       (local-location-view
	 (mftenv-local-location-view env))       
       (nonlocal-location-view
	 (mftenv-nonlocal-location-view env))
       ;; nonlocal libraries are treated as dummies to force their update
       (nonlocal-libraries-string-list
	 (mfg-nonlocal-dependencies-to-list-of-strings
	   'lib delimiter operating-system pgp-view
           (mftdep-nonlocal-library dependencies)
	   nonlocal-location-view))
       (nonlocal-objects-string-list
	 (mfg-nonlocal-dependencies-to-list-of-strings
	   'obj delimiter operating-system pgp-view
	   (mftdep-nonlocal-object dependencies)
	   nonlocal-location-view)) 
       (dummies-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'dum delimiter operating-system local-location-view 
	   (mftdep-dummy dependencies)))
       (variables-string-list
	 (mfg-variable-dependencies-to-list-of-strings
	   (mftdep-variable dependencies)))
       (objects-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'obj delimiter operating-system local-location-view
	   (mftdep-object dependencies)))
       (resources-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'res delimiter operating-system local-location-view
	   (mftdep-resource dependencies)))
       (libraries-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'lib delimiter operating-system local-location-view
	   (mftdep-library dependencies)))
       (dll-libraries-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'dlib delimiter operating-system local-location-view
	   (mftdep-dll-library dependencies)))
       (shared-objects-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'dso delimiter operating-system local-location-view
	   (mftdep-shared-object dependencies)))
       (executables-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'exe delimiter operating-system local-location-view
	   (mftdep-executable dependencies)))
       (dll-executables-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'dexe delimiter operating-system local-location-view
	   (mftdep-dll-executable dependencies)))
       (csources-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'c delimiter operating-system local-location-view
	   (mftdep-c dependencies)))
       (includes-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'h delimiter operating-system local-location-view
	   (mftdep-include dependencies)))
       (nonlocal-includes-string-list
	 (mfg-nonlocal-dependencies-to-list-of-strings
	   'h delimiter operating-system pgp-view
	   (mftdep-nonlocal-include dependencies)
	   nonlocal-location-view))
       (opts-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'opt delimiter operating-system local-location-view
	   (mftdep-opt dependencies)))
       (nonlocal-opts-string-list
	 (mfg-nonlocal-dependencies-to-list-of-strings
	   'opt delimiter operating-system pgp-view
	   (mftdep-nonlocal-opt dependencies)
	   nonlocal-location-view)))
    ;;Below is where the order of dependencies is controlled
    (append
      nonlocal-libraries-string-list
      nonlocal-objects-string-list
      dummies-string-list
      objects-string-list
      resources-string-list
      variables-string-list
      libraries-string-list
      dll-libraries-string-list
      shared-objects-string-list
      executables-string-list
      dll-executables-string-list
      csources-string-list
      includes-string-list
      nonlocal-includes-string-list
      opts-string-list
      nonlocal-opts-string-list)))


    



;;;; Functions for Special Database Selection
;;;      This section contains the function that provides general access to
;;;    the database as well as functions that provide specialized access
;;;    to directory-name relations.




;;; function: mfg-database
;;; arguments:
;;;   relation-name: the name of a relation in the database
;;; return value: a pointer to the relation
;;; description:  The database is searched for a relation of the given name
;;;   and a pointer to it is returned.  An error occurs if the relation is
;;;   not found.
;;; notes:
;;;   This is a repository for permanent relations. The repository is
;;;     established at load time.  It provides a means for data encapsulation
;;;     and avoids the need to make the relations global.
;;;   Currently, this does nothing more than encapsulate global references.
;;; scope: internal

(defun mfg-database (relation-name)
  (symbol-value relation-name))




;;; function: mfg-select-local-directory
;;; arguments: 
;;;   type: the file type
;;;   local-location-view: view derived from local-location-relation that
;;;     contains types and their locations
;;; return value: a string representing the directory in which a local
;;;   file of the given type resides
;;; description: the local-location-view is searched to find the
;;;   directory in which the given file type resides.  If no entry
;;;   if found for the given type (if rdb-select-row-value returns nil),
;;;   then the type value "default" is searched for and its value is
;;;   returned.
;;; scope: internal

(defun mfg-select-local-directory (type local-location-view)
  (let
      ((dir
         (rdb-select-row-value
           'directory
           (list
             (list type 'type))
	   local-location-view)))
    (if dir
        dir
        (rdb-select-row-value
          'directory
          '((default type))
	  local-location-view))))
       



;;; function: mfg-select-nonlocal-directory
;;; arguments:
;;;   target-group-priority-view: groups and priorities of current target
;;;   platform-group-priority-view: groups and priorities of current platform
;;;   nonlocal-location-view: file locations for current platform and product
;;; return value: a string representing the directory in which a nonlocal
;;;   file resides
;;; description: the nonlocal-location-view is searched to find the
;;;   directory in which the dependency resides.  The dependency's group
;;;   is used for the search, and the highest priority group's location is
;;;   used.
;;; notes:  The "target" may be a dependency or file to be installed.
;;;     Because a preselection is performed on nonlocal-location-relation
;;;   to select all product-group rows, product-group is irrelevant to this
;;;   selection.
;;; scope: internal

(defun mfg-select-nonlocal-directory (target-group-priority-view
                                       platform-group-priority-view
				       nonlocal-location-view)
  (mfg-select-platform-target-group-value
    'directory
    target-group-priority-view
    platform-group-priority-view
    nonlocal-location-view))




;;; function: mfg-select-template
;;; arguments:
;;;   category: the template category
;;;   product-group-priority-view: groups and priorities of current product
;;;   platform-group-priority-view: groups and priorities of current platform
;;; return value: a template
;;; global references: template-relation
;;; description: Selects the template value from the highest-priority platform
;;;   and product row of template-relation for the given category.
;;; scope: internal

(defun mfg-select-template (category
			    product-group-priority-view
			    platform-group-priority-view)
  (mfg-select-platform-product-group-value
    'template
    product-group-priority-view
    platform-group-priority-view
    (rdb-select-rows
      (list (list category 'category))
      (mfg-database 'template-relation))))



;;; function: mfg-select-command
;;; arguments:
;;;   command-type: the type of command to be found
;;;   platform-group-priority-view: groups and priorities of current platform
;;; global references:
;;;   commands-relation:   contains commands
;;; return value: the command for the specified type and platform
;;; description:  Selects and returns command for given command-type and the
;;;   highest-priority platform group.
;;; scope: internal

(defun mfg-select-command (command-type platform-group-priority-view)
  (let*
      ((command
	 (mfg-select-highest-priority-group-value
	   'command
	   'platform-group
	   platform-group-priority-view
	   (rdb-select-rows
	     (list (list command-type 'command-type))
	     (mfg-database 'commands-relation)))))
    (if (null command)
	(error "No command of type ~a for specified groups." command-type)
	command)))




;;; macro: mfg-select-command-options-to-string
;;; arguments:
;;;   option-category: any valid command option category
;;;   additive-option-category: any valid general command option category
;;;   target-group-priority-view: table of groups and priorities of current
;;;     target (required)
;;;   platform-group-priority-view: table of groups and priorities of current
;;;     platform (required)
;;; return value: an ordered list of command-options
;;; description: Options of category "option-category" and
;;;   "additive-option-category" are selected from command-options-relation
;;;   and returned in a list ordered by the "position" attribute. Options of
;;;   the "additive-option-category" category are non-overridden; i.e., they
;;;   are taken from all associated target and platform groups.
;;; scope: internal

(defmacro mfg-select-command-options-to-string (option-category
						 additive-option-category
						 options-to-string-function
						 env)
  `(mfg-construct-option-list-string
     ,option-category
     ,options-to-string-function
     (mftenv-target-group-priority-view ,env)
     (mftenv-platform-group-priority-view ,env)
     (mftenv-variable-value-view ,env)
     (mftenv-category-view-list-cons ,env)
     (mftenv-command-options-view ,env)
     :sort-attribute 'position
     :additive-option-category ,additive-option-category))




;;; function: mfg-construct-option-list-string
;;; arguments:
;;;   option-category:  a value in the option-category field of the relation
;;;     (required)
;;;   options-to-string-function: the function that will transform an option
;;;     or list of options into a printable string with appropriate
;;;     format (required)
;;;   target-group-priority-view: table of groups and priorities of current
;;;     target (required)
;;;   platform-group-priority-view: table of groups and priorities of current
;;;     platform (required)
;;;   variable-value-view: variables and their values for the current makefile
;;;   category-view-list-cons: a cons containing a list of selections on
;;;     "option-category" of relations; used to implement pseudo-lazy
;;;     evaluation (currently unused due to property list problem with
;;;     mfg-lazy-select...)
;;;   relation: relation from which options are to be taken (required)
;;;   :sort-attribute: if present, the relation is sorted by
;;;      this attribute before the option list is created (optional)
;;;   :additive-option-category: an additional, non-overridden
;;;      platform option-category to be merged with options of the primary
;;;      option-category (optional)
;;; return value: a list containing the requested options or the variable name
;;;   associated with the options
;;; description: This function extracts options of the specified option-category
;;;   from the relation for the highest-priority target and platform. It
;;;   checks first whether a variable is defined for the option-category,
;;;   target, and platform, and if so, returns the variable name.  Otherwise,
;;;   the extraction is performed.  If a variable is declared, the list is
;;;   stored with the variable name, otherwise, it is returned. Optionally,
;;;   the function sorts the options by the specified attribute.  Also option-
;;;   ally, it includes options from the specified :additive-option-category;
;;;   this option-category is non-overridden in the sense that options for all
;;;   platform and target groups (not just the highest) are included.
;;; notes:
;;;   By passing a non-existent option-category as a parameter, the additive
;;;   category alone is used.
;;; scope: internal
    
(defun mfg-construct-option-list-string (option-category
					  options-to-string-function
					  target-group-priority-view
					  platform-group-priority-view
					  variable-value-view
					  category-view-list-cons
					  relation
					  &key
					  sort-attribute
					  additive-option-category)
  (declare (ignore category-view-list-cons))
  (let*
      ((category-view
	 (rdb-select-rows
	   (list (list option-category 'option-category))
	   relation))
       (specific-options-view
	 (mfg-select-platform-target-group-rows
	   target-group-priority-view
	   platform-group-priority-view
	   category-view))
       (highest-priority-type-group
	 (rdb-attribute-value-of-first-row
	   'type-group
	   specific-options-view))
       (highest-priority-target-group
	 (rdb-attribute-value-of-first-row
	   'target-group
	   specific-options-view))
       (highest-priority-platform-group
	 (rdb-attribute-value-of-first-row
	   'platform-group
	   specific-options-view))
       (variable-name-and-position
	 (mfg-declared-variable-name-and-position
	   option-category
	   highest-priority-type-group
	   highest-priority-target-group
	   highest-priority-platform-group))
       (variable-name (first variable-name-and-position))
       (variable-position (second variable-name-and-position))
       (variable-value
	 (if variable-name
             (rdb-select-row-value
                'variable-value
	       (list (list variable-name 'variable-name))
	       variable-value-view))))
    (if (and variable-name variable-value)
	(mfg-format-variable-use variable-name)
	(let*
	    ((projection-list                      ;used to project options
	       (if sort-attribute
		   (list 'option sort-attribute)
		   '(option)))
	     (projected-specific-options-view
	       (rdb-project-relation
		 projection-list
		 specific-options-view))
	     (all-options-view
	       (if (not additive-option-category)
		   projected-specific-options-view ;use category options only
		   (let                            ;use additive options, too
		       ((additive-options-view
			  (rdb-project-relation
			    projection-list
			    (mfg-select-all-platform-target-group-rows
			     target-group-priority-view
			     platform-group-priority-view
			     (rdb-select-rows
			      (list (list
				      additive-option-category
				      'option-category))
			      relation)))))
		     (rdb-append-relation
		       projected-specific-options-view
		       additive-options-view))))
	     (all-options-string           ;get the options, possibly sorted,
	       (with-output-to-string      ;and format them into a string
		   (*standard-output*)     ;using the supplied function
		 (funcall options-to-string-function
			  (rdb-column-to-list
			    'option
			    (if (not sort-attribute)
				all-options-view        ;not sorted
				(rdb-sort-relation      ;sorted
				  (list sort-attribute 'option)
				  all-options-view)))))))
	  (if (not variable-name)
	      all-options-string
	      (mfg-format-variable-use
		(mfg-install-variable-and-position-and-value
		  variable-name
		  variable-position
		  all-options-string
		  variable-value-view)))))))






;;;; Functions for Setting Up and Dealing With Groups
;;;    This section contains means to work with groups.  Some generic
;;;    group functions are provided.  Specific functions are provided
;;;    to access data for platform and target groups.




;;; function: mfg-create-target-group-priority-view
;;; arguments:
;;;   target: the name of the group member whose groups are to be found.
;;;   type:   the target's type
;;; return value: a relation
;;; description:  Creates a 3-column view (relation) containing the target's
;;;   group, type, and priority, plus two new rows.  The first new
;;;   row consists of the target's name and the highest priority (a), because
;;;   every target defines its own highest priority group.  The second new row
;;;   consists of the group "_all" and the lowest priority (z), because
;;;   every target belongs to the group "_all".
;;; scope: external

(defun mfg-create-target-group-priority-view (target
					       type)
  (let
      ((target-view
	 (rdb-add-row-to-relation
	   (list '_all 'z type)
	   (rdb-add-row-to-relation
	     (list target 'a type)
	     (rdb-project-relation
	       '(group priority type)
	       (rdb-join-relations
		 '((group group) (type type))
		 (mfg-database 'target-group-priorities-relation)
		 (rdb-select-rows
		   (list (list
			   target
			   'group-member))
		   (mfg-database 'target-groups-relation)))))))
       (type-view
	 (rdb-rename-attributes
	   '((priority type-priority) (group type-group))
	   (rdb-add-row-to-relation
	     (list type '_all 'z)
	     (rdb-add-row-to-relation
	       (list type type 'a)
	       (rdb-project-relation   ; projection assures attribute order
		 '(group-member group priority)
		 (rdb-join-relations
		   '((group group))
		   (mfg-database 'type-group-priorities-relation)
		   (rdb-select-rows
		     (list (list
			     type
			     'group-member ))
		     (mfg-database 'type-groups-relation)))))))))
    (rdb-project-relation
      '(group priority type-group type-priority)
      (rdb-join-relations
	'((type group-member))
	target-view
	type-view))))
	



;;; function: mfg-create-group-priority-view
;;; arguments:
;;;   member: the name of the group member whose groups are to be found.
;;;   groups-relation:   groups to which the member may belong
;;;   group-priorities-relation:   the groups and their priorities
;;; return value: a relation
;;; description:  Creates a 2-column view (relation) containing the item's
;;;   groups and their priorities plus two new rows.  The first new
;;;   row consists of the item's name and the highest priority (a), because
;;;   every item defines its own highest priority group.  The second new row
;;;   consists of the group "_all" and the lowest priority (z), because
;;;   every item belongs to the group "_all".
;;; scope: external

(defun mfg-create-group-priority-view (member
					groups-relation
					group-priorities-relation)
  (rdb-add-row-to-relation
    '(_all z)
    (rdb-add-row-to-relation
      (list member 'a)
      (rdb-project-relation
	'(group priority)
	(rdb-join-relations
	  '((group group))
	  group-priorities-relation
	  (rdb-select-rows
	    (list (list
		    member
		    'group-member ))
	    groups-relation))))))




;;; function: mfg-highest-priority-group
;;; arguments:
;;;   group-attribute: the group attribute in the relation
;;;   group-priority-view: table of groups and priorities
;;;   relation: relation containing the group to be identified
;;; return value: the name of the highest-priority group in the relation
;;; description: Joins the group view with the relation to determine group
;;;   membership, finds the highest priority group, and returns it.
;;; scope: internal

(defun mfg-highest-priority-group (group-attribute group-view relation)
  (rdb-select-least-row-value
     'group
     '(priority)
     (rdb-join-relations
       (list (list 'group group-attribute))
       group-view
       relation)))




;;; function: mfg-select-highest-priority-group-rows
;;; arguments:
;;;   group-attribute: the attribute for the group to be used
;;;   group-priority-view: groups and priorities of current product
;;;   relation: relation containing the group to be identified
;;; return value: a new relation containing the rows of the highest priority
;;;   groups
;;; description: Selects the rows of the relation that have the highest
;;;   priority group for the given group.
;;; scope: internal

(defun mfg-select-highest-priority-group-rows (group-attribute
                                               group-priority-view
                                               relation)
  (let*
      ((highest-priority-group
	 (mfg-highest-priority-group
	   group-attribute
	   group-priority-view
	   relation)))
    (rdb-select-rows
      (list
	(list highest-priority-group group-attribute))
      relation)))




;;; function: mfg-select-highest-priority-group-value
;;; arguments:
;;;   attribute: an attribute of the relation
;;;   group-attribute: the attribute for the group to be used
;;;   platform-group-priority-view: groups and priorities of current platform
;;;   relation: a relation with appropriate attributes
;;; return value: an attribute's value
;;; description:  This function finds the row of "relation" with the 
;;;   highest priority group for the specified group and returns the specified
;;;   "attribute" of the row.  If more than one row of the relation satisfies
;;;   the selection criteria, the value in the first row is returned.
;;; scope: external

(defun mfg-select-highest-priority-group-value (attribute
                                                group-attribute
                                                group-priority-view
                                                relation)
  (rdb-select-row-value
    attribute
    (list
      (list
	(mfg-highest-priority-group
	  group-attribute
	  group-priority-view
	  relation)
	group-attribute))
    relation))




;;; function: mfg-select-all-group-rows
;;; arguments:
;;;   group-attribute: the attribute for the group to be used
;;;   group-priority-view: groups and priorities of current product
;;;   relation: relation containing the group attribute
;;; return value: a new relation containing the rows of all 
;;;   groups in the group-priority-view.
;;; description: Selects all rows with matching groups.
;;; scope: internal

(defun mfg-select-all-group-rows (group-attribute
				   group-priority-view
				   relation)
  (rdb-join-relations
    (list
      (list group-attribute 'group))
    relation
    group-priority-view))




;;; function: mfg-select-target-group-rows
;;; arguments:
;;;   target-group-priority-view: groups and priorities of current platform
;;;   relation: relation containing the group to be identified
;;; return value: a new relation containing the rows of the highest priority
;;;   target group
;;; description: Selects the rows of the relation that have the highest
;;;   priority target group.
;;; scope: internal

(defun mfg-select-target-group-rows
    (target-group-priority-view relation)
  (let*
      ((highest-priority-target-group
	 (mfg-highest-priority-group
	   'target-group
	   target-group-priority-view
	   relation)))
    (rdb-select-rows
      (list
	(list highest-priority-target-group 'target-group))
      relation)))




;;; function: mfg-select-target-group-value
;;; arguments:
;;;   attribute: an attribute of the relation
;;;   target-group-priority-view: groups and priorities of current target
;;;   relation: a relation with appropriate attributes
;;; return value: an attribute's value
;;; description:  This function finds the row of "relation" with   
;;;   the highest priority target group and returns the specified
;;;   "attribute" of the row.  If more than one row of the relation satisfies
;;;   the selection criteria, the value in the first row is returned.
;;; scope: external

(defun mfg-select-target-group-value
    (attribute
      target-group-priority-view
      relation)
  (rdb-select-row-value
    attribute
    (list
      (list
	(mfg-highest-priority-group
	  'target-group
	  target-group-priority-view
	  relation)
	'target-group))
    relation))




;;; function: mfg-select-platform-product-group-rows
;;; arguments:
;;;   product-group-priority-view: groups and priorities of current product
;;;   platform-group-priority-view: groups and priorities of current platform
;;;   relation: relation containing the group to be identified
;;; return value: a new relation containing the rows of the highest priority
;;;   product and platform groups
;;; description: Selects the rows of the relation with the highest priority
;;;   platform and product groups.  The platform group is primary and the
;;;   product group is secondary.
;;; scope: internal

(defun mfg-select-platform-product-group-rows
    (product-group-priority-view platform-group-priority-view relation)
  (let*
      ((platform-product-view
	 (rdb-join-relations
	   '((platform-group group))
	   (rdb-rename-attributes          ; to avoid having 2 priority attrs
	     '((priority product-priority))
	     (rdb-join-relations
	       '((product-group group))
	       relation
	       product-group-priority-view))
	   platform-group-priority-view))
       (product-group-index
	 (rdb-attribute-to-index 'product-group platform-product-view))
       (platform-group-index
	 (rdb-attribute-to-index 'platform-group platform-product-view))
       (least-row
	 (rdb-select-least-row
	   '(priority product-priority)     ; priority is for platform
	   platform-product-view))
       (highest-priority-platform-group
	 (nth platform-group-index least-row))
       (highest-priority-product-group
	 (nth product-group-index least-row)))
    (rdb-select-rows
      (list
	(list highest-priority-platform-group 'platform-group)
	(list highest-priority-product-group 'product-group))
      relation)))




;;; function: mfg-select-platform-product-group-value
;;; arguments:
;;;   attribute: an attribute of the relation
;;;   product-group-priority-view: groups and priorities of current product
;;;   platform-group-priority-view: groups and priorities of current platform
;;;   relation: a relation with appropriate attributes
;;; return value: an attribute's value
;;; description:  This function finds the row of "relation" with   
;;;   the highest priority product and platform groups and returns the specified
;;;   "attribute" of the row.  If more than one row of the relation satisfies
;;;   the selection criteria, the value in the first row is returned. To
;;;   determine the highest priority row, the platform group is primary and
;;;   the product group is secondary.
;;; scope: external

(defun mfg-select-platform-product-group-value
    (attribute
      product-group-priority-view
      platform-group-priority-view
      relation)
    (let*
      ((platform-product-view
	 (rdb-join-relations
	   '((platform-group group))
	   (rdb-rename-attributes          ; to avoid having 2 priority attrs
	     '((priority product-priority))
	     (rdb-join-relations
	       '((product-group group))
	       relation
	       product-group-priority-view))
	   platform-group-priority-view))
       (product-group-index
	 (rdb-attribute-to-index 'product-group platform-product-view))
       (platform-group-index
	 (rdb-attribute-to-index 'platform-group platform-product-view))
       (least-row
	 (rdb-select-least-row
	   '(priority product-priority)     ; priority is for platform
	   platform-product-view))
       (highest-priority-platform-group
	 (nth platform-group-index least-row))
       (highest-priority-product-group
	 (nth product-group-index least-row)))
      (rdb-select-row-value
	attribute
	(list
	  (list highest-priority-platform-group 'platform-group)
	  (list highest-priority-product-group 'product-group))
	relation)))




;;; function: mfg-select-all-platform-product-group-rows
;;; arguments:
;;;   product-group-priority-view: groups and priorities of current product
;;;   platform-group-priority-view: groups and priorities of current platform
;;;   relation: relation containing the groups to be identified
;;; return value: a new relation containing the rows of all relevant priority
;;;   product and platform groups
;;; description: Selects all rows of the relation that match any of both the
;;;   platform and product groups.
;;; scope: internal

(defun mfg-select-all-platform-product-group-rows
    (product-group-priority-view platform-group-priority-view relation)
  (rdb-join-relations
    '((platform-group group))
    (rdb-rename-attributes		; to avoid having 2 priority attrs
      '((priority product-priority))
      (rdb-join-relations
       '((product-group group))
        relation
      product-group-priority-view))
    platform-group-priority-view))




;;; function: mfg-select-platform-target-group-rows
;;; arguments:
;;;   target-group-priority-view: groups and priorities of current target
;;;   platform-group-priority-view: groups and priorities of current platform
;;;   relation: relation containing the group to be identified
;;; return value: a new relation containing the rows of the highest priority
;;;   target and platform groups
;;; description: Selects the rows of the relation with the highest priority
;;;   platform and target groups.  The platform group is primary and the
;;;   target group is secondary.
;;; scope: internal

(defun mfg-select-platform-target-group-rows
    (target-group-priority-view platform-group-priority-view relation)
  (let*
      ((platform-target-view
	 (rdb-join-relations
	   '((platform-group group))
	   (rdb-rename-attributes          ; to avoid having 2 priority attrs
	     '((priority target-priority))
	     (rdb-join-relations
	       '((target-group group) (type-group type-group))
	       relation
	       target-group-priority-view))
	   platform-group-priority-view))
       (least-row
	 (rdb-select-least-row
	   '(priority type-priority target-priority)  ;priority is for platform
	   platform-target-view))
       (highest-priority-platform-group
	 (nth
	   (rdb-attribute-to-index 'platform-group platform-target-view)
	   least-row))
       (highest-priority-type-group
	 (nth
	   (rdb-attribute-to-index 'type-group platform-target-view)
	   least-row))
       (highest-priority-target-group
	 (nth
	   (rdb-attribute-to-index 'target-group platform-target-view)
	   least-row)))
    (rdb-select-rows
      (list
	(list highest-priority-platform-group 'platform-group)
	(list highest-priority-type-group 'type-group)
	(list highest-priority-target-group 'target-group))
      relation)))




;;; function: mfg-select-platform-target-group-value
;;; arguments:
;;;   attribute: an attribute of the relation
;;;   target-group-priority-view: groups and priorities of current target
;;;   platform-group-priority-view: groups and priorities of current platform
;;;   relation: a relation with appropriate attributes
;;; return value: an attribute's value
;;; description:  This function finds the row of "relation" with   
;;;   the highest priority target and platform groups and returns the specified
;;;   "attribute" of the row.  If more than one row of the relation satisfies
;;;   the selection criteria, the value in the first row is returned. To
;;;   determine the highest priority row, the platform group is primary and
;;;   the target group is secondary.
;;; scope: external

(defun mfg-select-platform-target-group-value
    (attribute
      target-group-priority-view
      platform-group-priority-view
      relation)
    (let*
      ((platform-target-view
	 (rdb-join-relations
	   '((platform-group group))
	   (rdb-rename-attributes          ; to avoid having 2 priority attrs
	     '((priority target-priority))
	     (rdb-join-relations
	       '((target-group group) (type-group type-group))
	       relation
	       target-group-priority-view))
	   platform-group-priority-view))
       (least-row
	 (rdb-select-least-row
	   '(priority type-priority target-priority) ;priority is for platform
	   platform-target-view))
       (highest-priority-platform-group
	 (nth
	   (rdb-attribute-to-index 'platform-group platform-target-view)
	   least-row))
       (highest-priority-type-group
	 (nth
	   (rdb-attribute-to-index 'type-group platform-target-view)
	   least-row))
       (highest-priority-target-group
	 (nth
	   (rdb-attribute-to-index 'target-group platform-target-view)
	   least-row)))
      (rdb-select-row-value
	attribute
	(list
	  (list highest-priority-platform-group 'platform-group)
	  (list highest-priority-type-group 'type-group)
	  (list highest-priority-target-group 'target-group))
	relation)))




;;; function: mfg-select-all-platform-target-group-rows
;;; arguments:
;;;   target-group-priority-view: groups and priorities of current target
;;;   platform-group-priority-view: groups and priorities of current platform
;;;   relation: relation containing the groups to be identified
;;; return value: a new relation containing the rows of all relevant priority
;;;   target and platform groups
;;; description: Selects all rows of the relation that match any of both the
;;;   platform and target groups
;;; scope: internal

(defun mfg-select-all-platform-target-group-rows
    (target-group-priority-view platform-group-priority-view relation)
  (rdb-join-relations
    '((platform-group group))
    (rdb-rename-attributes		; to avoid having 2 priority attrs
      '((priority target-priority))
      (rdb-join-relations
       '((target-group group) (type-group type-group))
        relation
      target-group-priority-view))
    platform-group-priority-view))






;;;; Functions for Dealing with Makefile Variables (a.k.a. "Macros")
;;;    This section contains functions that provide access to and print
;;;    variable definitions.  Variables are added to the env in the
;;;    variable-value-view field either during initialization or
;;;    as automatically generated substitutions for options (see
;;;    mfg-construct-option-list-string).




;;; function: mfg-print-variable-definitions
;;; arguments:
;;;   variable-position-value-view: a table of variable names, positions,
;;;     and values
;;; return value: nil
;;; description: Prints the variable names and their values in the format
;;;   that a makefile uses for variable definitions.  The "position" is used
;;;   to group variables for printing.  Group 'a' is printed first, group 'b'
;;;   second, etc.  Within a group, variables are printed alphabetically.
;;; scope: internal

(defun mfg-print-variable-definitions (variable-position-value-view)
  (loop
    with position-list
    = (remove-duplicates
	(sort
	  (rdb-column-to-list
	    'position
	    variable-position-value-view)
	  #'rdb-lessp))
    for position in position-list
    do
    (loop
      with position-view
      = (rdb-sort-relation
	  '(variable-name)
	  (rdb-select-rows
	    (list (list position 'position))
	    variable-position-value-view))
      with name-index = (rdb-attribute-to-index 'variable-name position-view)
      with value-index = (rdb-attribute-to-index 'variable-value position-view)
      for row in (rdb-table position-view)
      for name = (nth name-index row)
      for value = (nth value-index row)
      do
      (format t "~a = ~a~%" name value))))




;;; function: mfg-declared-variable-name-and-position
;;; arguments:
;;;   variable-category: category to which the variable being sought belongs
;;;   type-group: the group of the type being processed
;;;   target-group: the group of the target being processed
;;;   platform-group: the group of the platform being processed
;;; return value: a pair of form (<variable-name> <position>) or nil
;;; description: Searches through variable-declaration-relation to determine
;;;   whether a declared variable exists for the given category, target, and
;;;   platform. If so, the name is returned, otherwise nil is returned.
;;; notes: If the data is consistent, only a single name (and row) will
;;;   be associated with a given category, target, and platform.  No check is
;;;   made for this, and the first row is used if multiple rows exist.
;;; scope: internal

(defun mfg-declared-variable-name-and-position (variable-category
						 type-group
						 target-group
						 platform-group)
  (first
    (rdb-table
      (rdb-project-relation
	'(variable-name position)
	(rdb-select-rows                 ;only one row should be selected
	  (list
	    (list variable-category 'variable-category)
	    (list platform-group 'platform-group)
	    (list target-group 'target-group)
	    (list type-group 'type-group))
	  (mfg-database 'variable-declaration-relation))))))




;;; function: mfg-install-variable-and-position-and-value
;;; arguments:
;;;   variable-name: the name of the variable to be assigned
;;;   position: the relative position of the variable when printed
;;;   variable-value: the value to be assigned
;;;   variable-value-view: the relation into which to put the new pair
;;; return value: variable-name
;;; description: Adds a new row to variable-value-view, which contains
;;;   variable-name, position, variable-value rows.  If the value to be added
;;;   is nil, the empty string "" is instead stored; this allows nil to be
;;;   returned by if there is no entry for the variable name.
;;; notes: It's assumed that a variable name is bound only once; no check is
;;;   made for duplication, so it's possible, but bad, for a variable to appear
;;;   multiple times.
;;; scope: internal

(defun mfg-install-variable-and-position-and-value (variable-name
						     position
						     variable-value
						     variable-value-view)
  (progn
    (rdb-add-row-to-relation
      (list
	variable-name
	position
	(if variable-value variable-value ""))
      variable-value-view)
    variable-name))




;;; function: mfg-establish-dependencies
;;; arguments:
;;;   env: the instance of mftenv containing the template-function environment
;;; return value: nil
;;; side effects: sets the slot values of env's target-dependencies, which
;;;   is a structure of type mftdep.
;;; description: This selects from dependencies-view all dependencies that
;;;   are directly dependent on the current target.  Each type of dependency
;;;   is stored in a separate list, which is sorted before being added to
;;;   the environment.
;;; notes: The logic of this function is very simple. It selects direct
;;;   dependencies, iterates through them, and stores each in a separate
;;;   list.  The lists are then sorted and "setf"ed into the
;;;   env->target-dependenies structure.  The code is long because struct
;;;   accessors don't lend themselves nicely to parameterization.
;;; modifications:
;;;     jv, 6/19/96: added shared objects parallel to libraries.
;;; scope: internal

(defun mfg-establish-dependencies (env)
  (loop
    with dependency-view
    = (mfg-select-all-platform-target-group-rows
	(mftenv-target-group-priority-view env)
	(mftenv-platform-group-priority-view env)
	(mftenv-dependency-view env))
    with dependency-index
    = (rdb-attribute-to-index 'dependency dependency-view)
    with dependency-type-index
    = (rdb-attribute-to-index 'dependency-type dependency-view)
    with local-index
    = (rdb-attribute-to-index 'local dependency-view)
    with target-dependencies = (mftenv-target-dependencies env)
    with dummies = nil
    with variables = nil
    with libraries = nil
    with dll-libraries = nil
    with shared-objects = nil
    with nonlocal-libraries = nil
    with nonlocal-objects = nil
    with executables = nil
    with dll-executables = nil
    with objects = nil
    with resources = nil
    with csources = nil
    with includes = nil
    with nonlocal-includes = nil
    with opts = nil
    with nonlocal-opts = nil
    for row in (rdb-table dependency-view)
    for dependency-type = (nth dependency-type-index row)
    for local = (nth local-index row)
    for dependency = (nth dependency-index row)
    do
    (case dependency-type
      (dum (push dependency dummies))
      (var (push dependency variables))
      (lib
       (if (eq local 'y)
	   (push dependency libraries)
	   (push dependency nonlocal-libraries)))
      (res (push dependency resources))
      (dlib (push dependency dll-libraries))
      (dso (push dependency shared-objects))
      (exe (push dependency executables))
      (dexe (push dependency dll-executables))
      (obj
	(if (eq local 'y)
	    (push dependency objects)
	    (push dependency nonlocal-objects)))
      (h
       (if (eq local 'y)
	   (push dependency includes)
	   (push dependency nonlocal-includes)))
      (c (push dependency csources))
      (opt
       (if (eq local 'y)
	   (push dependency opts)
	   (push dependency nonlocal-opts))))
    finally
      (setf (mftdep-dummy target-dependencies)
	    (sort dummies #'rdb-lessp))
      (setf (mftdep-variable target-dependencies)
	    (sort variables #'rdb-lessp))
      (setf (mftdep-library-unsorted target-dependencies)
	    (reverse libraries))          ; to reverse the push ordering
      (setf (mftdep-library target-dependencies)
	    (sort libraries #'rdb-lessp))
      (setf (mftdep-dll-library-unsorted target-dependencies)
	    (reverse dll-libraries))
      (setf (mftdep-dll-library target-dependencies)
	    (sort dll-libraries #'rdb-lessp))
      (setf (mftdep-shared-object-unsorted target-dependencies)
	    (reverse shared-objects))          ; to reverse the push ordering
      (setf (mftdep-shared-object target-dependencies)
	    (sort shared-objects #'rdb-lessp))
      (setf (mftdep-nonlocal-library-unsorted target-dependencies)
	    (reverse nonlocal-libraries)) ; to reverse the push ordering
      (setf (mftdep-nonlocal-library target-dependencies)
	    (sort nonlocal-libraries #'rdb-lessp))
      (setf (mftdep-nonlocal-object-unsorted target-dependencies)
	    (reverse nonlocal-objects)) ; to reverse the push ordering
      (setf (mftdep-nonlocal-object target-dependencies)
	    (sort nonlocal-objects #'rdb-lessp))
      (setf (mftdep-executable target-dependencies)
	    (sort executables #'rdb-lessp))
      (setf (mftdep-dll-executable target-dependencies)
	    (sort dll-executables #'rdb-lessp))
      (setf (mftdep-object-unsorted target-dependencies)
	    (reverse objects)) ; to reverse the push ordering
      (setf (mftdep-resource-unsorted target-dependencies)
	    (reverse resources)) ; to reverse the push ordering

      (setf (mftdep-object target-dependencies)
	    (sort objects #'rdb-lessp))
      (setf (mftdep-resource target-dependencies)
	    (sort resources #'rdb-lessp))
      (setf (mftdep-include target-dependencies)
	    (sort includes #'rdb-lessp))
      (setf (mftdep-nonlocal-include target-dependencies)
	    (sort nonlocal-includes #'rdb-lessp))
      (setf (mftdep-c target-dependencies)
	    (sort csources #'rdb-lessp))
      (setf (mftdep-opt target-dependencies)
	    (sort opts #'rdb-lessp))
      (setf (mftdep-nonlocal-opt target-dependencies)
	    (sort nonlocal-opts #'rdb-lessp))))




;;; function: mfg-generate-targets
;;; arguments:
;;;   template: template to be used
;;;   target-list: list of targets
;;;   env: the standard environment for makefile template functions
;;; return value: nil
;;; side effects: print a makefile entry for each target in list
;;; description: For each member of the target list this creates and prints
;;;   a makefile entry using the provided template.
;;; scope: internal

(defun mfg-generate-targets (template target-list env)
  (if target-list
      (loop
	for target in target-list
	do
	(setf (mftenv-target env) target)
	(setf (mftenv-target-group-priority-view env)
	      (mfg-create-target-group-priority-view
		(mftenv-target env)
		(mftenv-target-type env)))
	(mfg-process-template template env)
	(terpri))))




;;; function: mfg-process-template
;;; arguments:
;;;   template: the template to be processed
;;;   env: a property list that serves as a means of communication between
;;;        template components.
;;; return value: nil
;;; description: This processes the template from left to right.  The template
;;;   is a list of characters, strings, and symbols. Each has a different
;;;   meaning and treatment.
;;;     Strings and characters: printed directly by the lisp format function
;;;       and a "~a" control string.
;;;     Symbols: These cause a function to be "dispatched" by call of form
;;;           (mfgtf-<symbol> env)
;;;       where env is the property-list argument to this function. The
;;;       function returns nil. It prints to standard output as a side effect.
;;;   Dispatched functions can communicate by adding standard-property values
;;;   to the property list.  The standard properties are documented below in
;;;   the header comment for the mfg template functions (mfgtf-).
;;; scope: internal

(defun mfg-process-template (template env)
  (loop
    for member in template
    do
    (cond
      ((stringp member)
       (write-string member))
      ((characterp member)
       (format t "~a" member))
      ((symbolp member)
       (funcall            ; dispatch the symbol
	 (or (get member 'mfgtf)
	     (setf (get member 'mfgtf)
		   (intern (format nil "MFGTF-~a" member))))
	 env)) 
      (t
       (error "Unrecognized member ~a of type ~a of template ~a"
	      member (type-of member) template)))))




;;; function: mfg-lazy-select-rows-of-option-category
;;; arguments:
;;;   option-category: an atom
;;;   relation: a relation with an "option-category" attribute
;;;   category-view-list-cons: A list containing a property list that is
;;;     indexed by option-category names.  The property value is a relation
;;;     and a selection of the relation
;;; return value: a pointer to a relation with rows selected from "relation"
;;;   where the category attribute matches the category value
;;; description: Uses pseudo-lazy evaluation to create specialized views as
;;;   needed and returns a pointer to a view if it exists. The views are
;;;   specifically just those created by selecting the "option-category"
;;;   attribute of a relation. Views are stored in a property list indexed by
;;;   the catgory.  Associated with a property is a pair containing a pointer
;;;   to the relation from which the view was created and the selected view.
;;;   Whenever the category matches but the relation doesn't, the view is
;;;   regenerated.
;;; notes:
;;;   To allow setf and getf to work properly, the property list itself
;;;   cannot be passed, because new properties are prepended.  Instead, the
;;;   "wrapper" containing the list is passed so that it can be destructively
;;;   modified.
;;; scope: internal

(defun mfg-lazy-select-rows-of-option-category (option-category
						 relation
						 category-view-list-cons)
  (let
      ((view-pair         ;search for the option-category in property list
	 (getf (car category-view-list-cons) option-category)))
    (if (and
	  view-pair
	  (eq relation (first view-pair)))
	(second view-pair)          ;if view is found, return it
	(let                        ;otherwise recreate, store, and return it
	    ((category-view
	       (rdb-select-rows
		 (list (list option-category 'option-category))
		 relation)))
	  (setf (getf (car category-view-list-cons) option-category)
		(list relation category-view))
	  category-view))))

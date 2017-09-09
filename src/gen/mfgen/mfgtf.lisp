;;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: USER -*-
(in-package "USER")

;;;; Module MFGTF (makefile generator template functions)
;;;
;;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;;  All Rights Reserved.
;;;
;;;; author: Mark E. Staknis
;;;
;;;; Description:
;;;      Included below are makefile-generator template functions (mfgtf-).
;;;    Template functions are "dispatched" by symbols in makefile templates
;;;    when the templates are processed left-to-right by the function
;;;    process-template.  Template processing is initiated by
;;;    mfg-generate-standard-makefile, which selects either standard-makefile
;;;    or standard-install-makefile.
;;;      A symbol in a template is expanded to a call of form
;;;          (funcall mfgtf-<symbol> env)
;;;    The call returns nil, but as a side effect it prints the designated part
;;;    of the template. All functions take a mftenv structure, env, as the only
;;;    argument. The slots of env are essentially optional parameters.  As a
;;;    template is processed from left to right, the structure is used
;;;    to pass information between stages of the template.
;;;      (See the Notes below for more detail.)
;;;
;;;; File Organization
;;;      The file is divided into a few major sections.  Because there are
;;;    many functions, they are not listed by name.  However, the functions
;;;    within a group are often very similar and functionality may be
;;;    easily intuited by the function's name. 
;;;
;;;    I. Sections that Select and Process other Templates
;;;      IMPORTANT: The functions of Section I themselves select
;;;    and process additional templates, and they do so in a fairly
;;;    intuitive way.  They do not print output directly. The template
;;;    hierarchy is fairly shallow. (See the Notes below for naming
;;;    conventions).
;;;
;;;    Functions that Produce Single Makefile Entries or Pseudo Entries
;;;        This section selects and processes templates to produce makefile
;;;      entries for the targets clean: and install: It also processes
;;;      templates to produce an initial comment section, an all: target
;;;      to prebuild non-local libraries, and a special parameterized object
;;;      compilation format string that enhances efficiency.
;;;
;;;    Functions that Iteratively Produce Makefile Entries
;;;        This section contains functions that iterate over a list of
;;;      targets of a particular type (dummy, executable, library, object,
;;;      nonlocal library, and variable) and process the appropriate
;;;      template for each target.  All have an identical form with
;;;      the exception of that for objects, which has an efficiency
;;;      enhancement.
;;;     
;;;    Makefile Entry Bodies and Lines
;;;        These functions exist to separate makefile entries into reasonable
;;;      parts or to generate lines iteratively.  Those with name
;;;      mfgtf-<name>-line simply select and process the template <name>-line.
;;;      The functions that generate lines iteratively (install, archive-with-
;;;      multiple-commands) or that handle object compilation have additional
;;;      complexity.
;;;
;;;    II. Sections that Format and Print Output
;;;       Each of the functions in Section II accesses the environment
;;;    or the database to generate and print output to fill the corresponding
;;;    "field" of the template.  These functions never invoke other templates.
;;;
;;;    Functions that Format and Print Lists from Env
;;;        These functions process lists (of dependencies, objects,
;;;      etc.) from env and format the elements for printing.  This may
;;;      require pathname expansion, adding suffixes, and so on.
;;;
;;;    Fields from env
;;;        Many of these simply print the corresponding slot from env
;;;      in the appropriate format (current-dir, directory-delimiter,
;;;      filename, odir, product, target).  Others combine env elements,
;;;      for example to build a full pathname.  A few (log-type,
;;;      runmake-product-kludge) make simple mappings of env fields to names.
;;;
;;;    Commands
;;;        All functions in this group have name mfgtf-<command>-command
;;;      and have identical form.  Each merely selects <command> from
;;;      commands-relation and prints it.
;;;
;;;    Command Options
;;;        All functions in this group have name mfgtf-<command>-options
;;;      and have identical form. Each identically selects, formats, and
;;;      prints relevant options from command-options-relation.  (See the
;;;      section header comments for additional details.)
;;;
;;;    Install Entry Components
;;;        The functions in this section access and format fields of the
;;;      install-slots substructure of the env structure.  The install: entry
;;;      is the most complex entry in a makefile.  Its organization is
;;;      taken care of by the functions mfgtf-install and mfgtf-install-lines
;;;      and their associated templates (see Notes for further description).
;;;
;;;; Notes
;;;      Functions in this file are never called directly from other Lisp
;;;    functions.  They are always dispatched during template processing.
;;;    This rule should never be violated or the code organization will
;;;    become (extremely) difficult to follow.
;;;      ---
;;;      A distinction is made between a target and the command that produces
;;;    it.  If one keeps the following in mind, much becomes clearer.
;;;          COMMAND      TARGET
;;;          -------      -------
;;;          archive      library
;;;          compile      object
;;;      ---
;;;      The most frequently occurring entries in a typical makefile are
;;;    those for objects.  Because object entries often have a default
;;;    format that is identical for all, an optimization has been added
;;;    that in many cases cuts processing time in half.  The optimization
;;;    is to create two pseudo templates for objects.  These pseudo templates
;;;    are Lisp format strings with the target name replaced by ~a.  The
;;;    format strings are created by mfgtf-object-default-target.  The strings
;;;    are used by either mfgtf-object-targets or mfgtf-compile-body, which
;;;    determine whether the object uses default formatting.
;;;      The function mfg-deduce-nonstandard-object-list analyzes the
;;;    compilation options to generate a list of nonstandard compilation
;;;    targets, which is stored in env.
;;;      For details about the creation and processing of the pseudo template,
;;;    see the individual notes of the functions mentioned above.
;;;      ---
;;;      For the association between compilation options and the functions
;;;    that select them, see the comments below in the Command Options section.
;;;      ---
;;;      The install target is by far the most complex.  It has some intrinsic
;;;    complexity, such as the need to install in different directories.
;;;    Much of the complexity is due to tradition or convenience.  For
;;;    example, file renaming is a convenience.  The majority of the complexity
;;;    is due to the parts.list file and its idiosyncracies.  The system
;;;    as a whole could be improved by drastically rethinking and simplifying
;;;    the parts.list design.






;;;; Functions that Produce Single Makefile Entries or Pseudo Entries
;;;      With the exception of object-default-target, each function in this
;;;    section selects a template and processes it with the current product
;;;    and platform group views.  The function mfgtf-<name>-target selects
;;;    template <name>.



;;; function: mfgtf-clean-target
;;; arguments and return value: standard
;;; description: Generates the "clean" target; i.e., the target that deletes
;;;   all files produced by the makefile.
;;; scope: internal

(defun mfgtf-clean-target (env)
  (mfg-process-template
    (mfg-select-template
      'clean
      (mftenv-product-group-priority-view env)
      (mftenv-platform-group-priority-view env))
    env))




;;; function: mfgtf-comments-prologue
;;; arguments and return value: standard
;;; description: Dispatches the comments-prologue template, if any, for the
;;;   platform.  The comments-prologue template is used to provide comments
;;;   or special makefile inclusion at the beginning of the makefile.
;;; scope: internal

(defun mfgtf-comments-prologue (env)
  (mfg-process-template
    (mfg-select-template
      'comments-prologue
      (mftenv-product-group-priority-view env)
      (mftenv-platform-group-priority-view env))
    env))



 
;;; function: mfgtf-install-target
;;; arguments and return value: standard
;;; description: Dispatches the template that creates the "install" target.
;;; scope: internal
  
(defun mfgtf-install-target (env)
  (mfg-process-template
    (mfg-select-template
      'install
      (mftenv-product-group-priority-view env)
      (mftenv-platform-group-priority-view env))
    env))




;;; function: mfgtf-object-default-target
;;; arguments and return value: standard
;;; description: Generates format strings to print default object target
;;;   entries and bodies, then stores them in env for later use.
;;; notes:
;;;     In the future this is where a default object-compilation entry will
;;;   be emitted for those platforms whose "make" supports it.
;;;     This function uses a trick to produce a format string for a
;;;   makefile "object" entry.  The trick is to pass "~a" as the object
;;;   name.  Since this object does not exist and is not in any target
;;;   group, the default makefile entry is returned as a string with
;;;   "~a" whereever the object basename would be.  By then printing the
;;;   format string with the object name as each argument, a makefile entry
;;;   with default structure is generated with effectively no processing
;;;   overhead.
;;;     This function generates format strings for both the compile template
;;;   and compile-body template because one or the other may be used,
;;;   depending on the product.  The template function mfgtf-object-targets
;;;   determines which format string to use, if any.
;;; scope: internal

(defun mfgtf-object-default-target (env)
   (setf (mftenv-target env) "~a")
   (setf (mftenv-target-type env) 'obj)
   (setf (mftenv-target-group-priority-view env)
      (mfg-create-target-group-priority-view
         (mftenv-target env)
         (mftenv-target-type env)))
   (setf (mftenv-compile-entry-format-string env)
	 (with-output-to-string
	     (*standard-output*)
	   (mfg-process-template
	     (mfg-select-template
	       'compile
	       (mftenv-product-group-priority-view env)
	       (mftenv-platform-group-priority-view env))
	     env)))
   (setf (mftenv-compile-body-format-string env)
	 (with-output-to-string
	     (*standard-output*)
	   (mfg-process-template
	     (mfg-select-template
	       'compile-body
	       (mftenv-product-group-priority-view env)
	       (mftenv-platform-group-priority-view env))
	     env))))





;;; function: mfgtf-nonlocal-library-dummy-target
;;; arguments and return value: standard
;;; description: This target serves as a means to cause non-local libraries
;;;   to be updated without requiring all products that depend on them
;;;   to be remade (unless they are older than the libraries).  It produces a
;;;   special "all" target entry that appears first and forces the libraries
;;;   to be updated.
;;; scope: internal

(defun mfgtf-nonlocal-library-dummy-target (env)
  (if (mftenv-nonlocal-library-target-list env) ;skip unless there are some
      (progn
	(setf (mftenv-target-type env) 'dum)
	(mfg-generate-targets
	  (mfg-select-template
	    'nonlocal-library-dummy
            (mftenv-product-group-priority-view env)
	    (mftenv-platform-group-priority-view env))
	  '(all)
	  env))))


;;; function: mfgtf-nonlocal-object-dummy-target
;;; arguments and return value: standard
;;; description: This target serves as a means to cause non-local libraries
;;;   to be updated without requiring all products that depend on them
;;;   to be remade (unless they are older than the libraries).  It produces a
;;;   special "all" target entry that appears first and forces the libraries
;;;   to be updated.
;;; modifications:
;;;     jv, 6/19/96: created by duplicating mfgtf-nonlocal-library-dummy-target
;;;   and replacing "library" with "shared-object".
;;; scope: internal

(defun mfgtf-nonlocal-object-dummy-target (env)
  (if (mftenv-nonlocal-object-target-list env) ;skip unless there are some
      (progn
	(setf (mftenv-target-type env) 'dum)
	(mfg-generate-targets
	  (mfg-select-template
	    'nonlocal-object-dummy
            (mftenv-product-group-priority-view env)
	    (mftenv-platform-group-priority-view env))
	  '(all)
	  env))))






;;;; Functions that Iteratively Produce Makefile Entries
;;;      These functions have names mfgtf-<name>-targets.  With a few
;;;    exceptions, each sets the target type, selects the template <name>,
;;;    and then calls mfg-generate-targets with the appropriate list of
;;;    targets from env.  mfg-generate-targets simply iterates through the
;;;    target list setting up the target group and calling
;;;    mfg-process-template with the chosen template.
;;;      The functions mfgtf-enter-exit-targets and mfgtf-clean-target
;;;    do not have a list of targets.  Each causes a single template to be
;;;    processed that generates its specialized entries.
;;;      The function mfgtf-object-targets is more complex because it
;;;    has a performance enhancement.  It essentially duplicates
;;;    mfg-generate-targets, except that for the indicated products, it
;;;    assumes that an object has a standard makefile entry unless the
;;;    object appears in mftenv-nonstandard-objects-list.  Standard
;;;    objects are printed without processing by using the object-entry
;;;    format string.




;;; function: mfgtf-dummy-targets
;;; arguments and return value: standard
;;; description: Prints a makefile entry for each target in env's
;;;   dummy-target-list.
;;; notes:  A dummy target is simply one used for grouping within a makefile.
;;;   It has dependencies to be made but a dummy entry has an empty body.
;;;   The all: target is a well-known dummy target.
;;; scope: internal

(defun mfgtf-dummy-targets (env)
  (setf (mftenv-target-type env) 'dum) 
  (mfg-generate-targets
    (mfg-select-template
      'dummy
      (mftenv-product-group-priority-view env)
      (mftenv-platform-group-priority-view env))
    (mftenv-dummy-target-list env)
    env))




;;; function: mfgtf-enter-exit-targets
;;; arguments and return value: standard
;;; description: Processes the template that produces explicit entries
;;;   for _mfenter and _mfexit, which are used for initialization and cleanup.
;;; notes: See mfgtf-dependencies-with-augmented-all.
;;; scope: internal

(defun mfgtf-enter-exit-targets (env)
  (mfg-process-template
    (mfg-select-template
      'enter-exit
      (mftenv-product-group-priority-view env)
      (mftenv-platform-group-priority-view env))
    env))




;;; function: mfgtf-executable-targets
;;; arguments and return value: standard
;;; description: Prints a makefile entry for each target in env's
;;;   executable-target-list
;;; scope: internal

(defun mfgtf-executable-targets (env)
  (setf (mftenv-target-type env) 'exe)
  (mfg-generate-targets
    (mfg-select-template
      (if (eq 'optimize (mftenv-compile-category env))
	  'link-optimized ; so we can generate unstripped executables, too.
	  'link)
      (mftenv-product-group-priority-view env)
      (mftenv-platform-group-priority-view env))
    (mftenv-executable-target-list env)
    env))



;;; function: mfgtf-dll-executable-targets
;;; arguments and return value: standard
;;; description: Prints a makefile entry for each target in env's
;;;   dll-executable-target-list
;;; scope: internal

(defun mfgtf-dll-executable-targets (env)
  (setf (mftenv-target-type env) 'dexe)
  (mfg-generate-targets
    (mfg-select-template
      'dll-link
      (mftenv-product-group-priority-view env)
      (mftenv-platform-group-priority-view env))
    (mftenv-dll-executable-target-list env)
    env))




;;; function: mfgtf-library-targets
;;; arguments and return value: standard
;;; description: Prints a makefile entry for each target in env's
;;;   library-target-list
;;; scope: internal

(defun mfgtf-library-targets (env)
  (setf (mftenv-target-type env) 'lib)
  (mfg-generate-targets
    (mfg-select-template
      'archive
      (mftenv-product-group-priority-view env)
      (mftenv-platform-group-priority-view env))
    (mftenv-library-target-list env)
    env))



;;; function: mfgtf-library-targets
;;; arguments and return value: standard
;;; description: Prints a makefile entry for each target in env's
;;;   dll-library-target-list
;;; scope: internal

(defun mfgtf-dll-library-targets (env)
  (setf (mftenv-target-type env) 'dlib)
  (mfg-generate-targets
    (mfg-select-template
      'dll-archive
      (mftenv-product-group-priority-view env)
      (mftenv-platform-group-priority-view env))
    (mftenv-dll-library-target-list env)
    env))




;;; function: mfgtf-shared-object-targets
;;; arguments and return value: standard
;;; description: Prints a makefile entry for each target in env's
;;;   shared-object-target-list
;;; modifications:
;;;     jv, 6/19/96: created by duplicating mfgtf-library-targets
;;;   and replacing "library" with "shared-object".
;;; scope: internal

(defun mfgtf-shared-object-targets (env)
  (setf (mftenv-target-type env) 'dso)
  (mfg-generate-targets
    (mfg-select-template
      'shared-object
      (mftenv-product-group-priority-view env)
      (mftenv-platform-group-priority-view env))
    (mftenv-shared-object-target-list env)
    env))




;;; function: mfgtf-object-targets
;;; arguments and return value: standard
;;; description: Prints a makefile entry for each target in env's
;;;   object-target-list.  Objects with default entries are printed
;;;   very efficiently using a precomputed format string.
;;; notes: Because object-target entries are typically the most numerous
;;;   entries in a makefile, considerable processing overhead can be
;;;   avoided by precomputing an appropriate format string and using
;;;   it to print defaults.  The function mfgtf-object-default-target
;;;   precomputes the needed format string.  Non-default objects are
;;;   identified by mfg-deduce-nonstandard-object-list during env
;;;   initialization and stored in the nonstandard-objects-list slot.
;;;   If the object is not in the list, the default entry format is used,
;;;   otherwise it is processed fully.
;;;     Some products have default entries because their dependency lists have
;;;   the same form.  Other products entries can have different
;;;   dependencies, so their default body is taken care of by
;;;   mfgtf-compile-body.  Whether one default or the other is used is
;;;   determined by the object-default-entry-relation
;;; modifications:
;;; scope: internal

(defun mfgtf-object-targets (env)
  (setf (mftenv-target-type env) 'obj)
  (loop
    with template
      = (mfg-select-template
	  'compile
	  (mftenv-product-group-priority-view env)
	  (mftenv-platform-group-priority-view env))
    with format-string
      = (mftenv-compile-entry-format-string env)
    with use-format-string
      = (eq (mftenv-object-default-replacement env) 'entry)
    for target in (mftenv-object-target-list env)
    do
    (if (and
	  use-format-string
	  (not (member target (mftenv-nonstandard-objects-list env))))
	;; For standard objects, use the predefined format string, passing
	;; target as many times as it might be needed (there must be a
	;; better way).
	(let
	    ((str (mfg-downcase-symbol target)))
	  (format t format-string
		  str str str str str str str str str str str str str str str))
	;; For nonstandard object compilation, prepare for and dispatch
	;; the template.
	(progn
	  (setf (mftenv-target env) target)
	  (setf (mftenv-target-group-priority-view env)
		(mfg-create-target-group-priority-view
		  (mftenv-target env)
		  (mftenv-target-type env)))
	  (mfg-process-template template env)))
    (format t "~%")))




;;; function: mfgtf-nonlocal-library-targets
;;; arguments and return value: standard
;;; description: Prints a makefile entry for each target in env's
;;;   nonlocal-library-target-list
;;; scope: internal

(defun mfgtf-nonlocal-library-targets (env)
  (setf (mftenv-target-type env) 'lib)
  (mfg-generate-targets
    (mfg-select-template
      'nonlocal-archive
      (mftenv-product-group-priority-view env)
      (mftenv-platform-group-priority-view env))
    (mftenv-nonlocal-library-target-list env)
    env))




;;; function: mfgtf-nonlocal-object-targets
;;; arguments and return value: standard
;;; description: Prints a makefile entry for each target in env's
;;;   nonlocal-object-target-list
;;; modifications:
;;;     jv, 6/19/96: created by duplicating mfgtf-nonlocal-library-targets
;;;   and replacing "library" with "shared-object".
;;; scope: internal

(defun mfgtf-nonlocal-object-targets (env)
  (setf (mftenv-target-type env) 'obj)
  (mfg-generate-targets
    (mfg-select-template
      'nonlocal-archive
      (mftenv-product-group-priority-view env)
      (mftenv-platform-group-priority-view env))
    (mftenv-nonlocal-object-target-list env)
    env))




;;; function: mfgtf-variable-targets
;;; arguments and return value: standard
;;; description: Prints a variable definition for each variable target in
;;;   env's variable-target-list.  Variable targets are pseudo targets that
;;;   exist merely to assign lists of dependencies to variables.
;;; scope: internal

(defun mfgtf-variable-targets (env)
  (setf (mftenv-target-type env) 'var)
  (mfg-generate-targets
    (mfg-select-template
      'variable-targets
      (mftenv-product-group-priority-view env)
      (mftenv-platform-group-priority-view env))
    (mftenv-variable-target-list env)
    env))



;;; function: mfgtf-resource-targets
;;; arguments and return value: standard
;;; description: Prints a makefile entry for each target in env's
;;;   resource-target-list
;;; modifications:
;;; scope: internal

(defun mfgtf-resource-targets (env)
  (setf (mftenv-target-type env) 'res)
  (mfg-generate-targets
    (mfg-select-template
      'resource-file
      (mftenv-product-group-priority-view env)
      (mftenv-platform-group-priority-view env))
    (mftenv-resource-target-list env)
    env))


(defun mfgtf-resource-command (env)
  (mfg-print-downcased
     (mfg-select-command 'resource (mftenv-platform-group-priority-view env))))


(defun mfgtf-resource-options (env)
  (write-string
    (mfg-select-command-options-to-string
      'rsrc
      'general-rsrc
      #'mfg-print-list-with-space-separators
      env)))


(defun mfgtf-rc-source-for-target (env)
  (let* ((target (mftenv-target env))
	 (override-source
	   (cadr (assoc target (cadr (mfg-database 'source-target-relation)))))
	 (source (or override-source target)))
    (mfg-print-downcased
      (mfg-full-filename-string
	(mfg-select-local-directory
	  'rc
	  (mftenv-local-location-view env))
	(mftenv-directory-delimiter env)
	source
	(mfg-file-type-suffix
	  'rc
	  (mftenv-operating-system env))))))






;;;; Makefile Entry Bodies and Lines
;;;      The functions mfgtf-<name>-line (singular) simply select and process
;;;    the template whose name is "<name>-line".
;;;      The function mfgtf-compile-body is similar to the mfgtf-<name>-line
;;;    functions except that it uses a format line for default objects. 
;;;      The functions mfgtf-<name>-lines each behaves differently; however,
;;;    each has iterative behavior.  See the individual comments for
;;;    mfgtf-archive-with-multiple-command-lines, mfgtf-install-lines,
;;;    and mfgtf-remove-exes-lines,




;;; function: mfgtf-archive-line
;;; arguments and return value: standard
;;; description: Dispatches the template archive-line that generates the
;;;   lines to produce an archive.
;;; notes: The archive-line template has a slightly misleading name in
;;;   that the template may have multiple lines or further invoke
;;;   the template archive-with-multiple-command-lines.
;;; scope: internal

(defun mfgtf-archive-line (env)
  (mfg-process-template
    (mfg-select-template
	'archive-line
        (mftenv-product-group-priority-view env)
	(mftenv-platform-group-priority-view env))
    env))


;;; function: mfgtf-dll-archive-line
;;; arguments and return value: standard
;;; description: Dispatches the template dll-archive-line that generates the
;;;   lines to produce an DLL archive.
;;; notes: The dll-archive-line template has a slightly misleading name in
;;;   that the template may have multiple lines or further invoke
;;;   the template archive-with-multiple-command-lines.
;;; scope: internal

(defun mfgtf-dll-archive-line (env)
  (mfg-process-template
    (mfg-select-template
      'dll-archive-line
      (mftenv-product-group-priority-view env)
      (mftenv-platform-group-priority-view env))
    env))


;;; function: mfgtf-shared-object-line
;;; arguments and return value: standard
;;; description: Dispatches the template shared-object-line that generates the
;;;   lines to produce a shared-object.
;;; scope: internal

(defun mfgtf-shared-object-line (env)
  (mfg-process-template
    (mfg-select-template
	'shared-object-line
        (mftenv-product-group-priority-view env)
	(mftenv-platform-group-priority-view env))
    env))


;;; function: mfgtf-archive-with-multiple-command-lines
;;; arguments and return value: standard
;;; description: Orchestrates the creation of multiple archive lines by
;;;   processing library objects and passing a number limited by the env's
;;;   objects-per-command to library creation and append templates.
;;; notes:   This separates archiving into separate create and append
;;;   command lines to accommodate platforms whose archiving commands limit
;;;   the number of arguments.
;;; scope: internal

(defun mfgtf-archive-with-multiple-command-lines (env)
  (let*
      ((objects-per-command (mftenv-objects-per-command env))
       (dependencies (mftenv-target-dependencies env))
       (delimiter (mftenv-directory-delimiter env))
       (operating-system (mftenv-operating-system env))
       (objects-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'obj delimiter operating-system
	   (mftenv-local-location-view env)
	   (mftdep-object dependencies)))
       (variables-string-list
	 (mfg-variable-dependencies-to-list-of-strings
	   (mftdep-variable dependencies)))
       (creation-template
	 (mfg-select-template
	   'archive-create-line
           (mftenv-product-group-priority-view env)
	   (mftenv-platform-group-priority-view env)))
       (insertion-template
	 (mfg-select-template
	   'archive-insert-line
           (mftenv-product-group-priority-view env)
	   (mftenv-platform-group-priority-view env)))
       (creation-needed t))
    (loop    ; write variable dependencies one per command line
      for variable-string in variables-string-list
      do
      (setf (mftenv-tmp-list env) variable-string)
      (mfg-process-template
	(if creation-needed
	    (progn
	      (setf creation-needed nil) 
	      creation-template)
	    insertion-template)
	env))
    (loop
      for remaining-objects-string on objects-string-list by
      #'(lambda (list) (nthcdr objects-per-command list))
      do
      (setf (mftenv-tmp-list env)
	    (if (< (length remaining-objects-string) objects-per-command)
		remaining-objects-string
		(subseq remaining-objects-string 0 objects-per-command)))
      (mfg-process-template
	(if creation-needed
	    (progn
	      (setf creation-needed nil) 
	      creation-template)
	    insertion-template)
	env))
    (setf (mftenv-tmp-list env) nil)))




;;; function: mfgtf-compile-body
;;; arguments and return value: standard
;;; description: Produces the body of the compilation template.  For
;;;   objects that are created with standard options, the format string
;;;   produced during env setup is used.  For objects that have nonstandard
;;;   options, the "compile-body" template is dispatched.  See the notes
;;;   for function mfgtf-object-targets.
;;; scope: internal

(defun mfgtf-compile-body (env)
  (let*
      ((target (mftenv-target env))
       (str (mfg-downcase-symbol target)))
    (if (and
	  (eq (mftenv-object-default-replacement env) 'body)
	  (not (member target (mftenv-nonstandard-objects-list env))))
	;; For standard objects, use the predefined format string, passing
	;; target as many times as it might be needed (there must be a better
	;; way).
	(progn
	  (format t (mftenv-compile-body-format-string env)
		str str str str str str str str str str))
	;; For nonstandard object compilation, dispatch the template.
	(mfg-process-template
	  (mfg-select-template
	    'compile-body
	    (mftenv-product-group-priority-view env)
	    (mftenv-platform-group-priority-view env))
	  env))))




;;; function: mfgtf-compile-target-line
;;; arguments and return value: standard
;;; description: Chooses and dispatches the template to emit a target
;;;   dependency line.  Some products such as g2 and tw have an explicit
;;;   .h file for each .c file, while other products do not; this function
;;;   selects the template accordingly.
;;; scope: internal

(defun mfgtf-compile-target-line (env)
  (mfg-process-template
    (mfg-select-template
        'compile-target-line
        (mftenv-product-group-priority-view env)
        (mftenv-platform-group-priority-view env))
    env))



;;; function: mfgtf-sorted-install-dependency-view
;;; arguments and return value: standard?
;;; description: This code used to be inlined in mfgtf-install-lines, which
;;;   remains its only caller.  I (jv) moved it out primarily just to call
;;;   attention to it, because for the life of me I can't imagine why we
;;;   do this.  Basically, we get the depencencies of the "install" target,
;;;   and sort them ALPHABETICALLY BY "TYPE", where "type" means the symbol
;;;   used to describe the type of file the dependency is.  The other reason
;;;   to pull this out is because it's six lines stuck into one clause of a
;;;   loop which is still way too long after pulling it out.  -jv, 11/24/03
;;; scope: internal

(defun mfgtf-sorted-install-dependency-view (env)
  (rdb-sort-relation
    '(dependency-type local dependency)
    (mfg-select-all-platform-target-group-rows
      (mfg-create-target-group-priority-view 'install 'dum)
      (mftenv-platform-group-priority-view env)
      (mftenv-dependency-view env))))



;;; function: mfgtf-install-lines
;;; arguments and return value: standard
;;; description: Prints command lines to install associated products.
;;;   The "install" target is special in the dependencies view.
;;; notes:
;;;     This is much more complex than the other functions for a few reasons.
;;;   One reason is that each installed product requires one or more
;;;   specific commands.  The other is due to the overhead of creating
;;;   subdirectories, a parts.list file, etc.
;;;     The 'install' target is never a member of any general target group
;;;   nor is it ever a dependency.  It is set up below as the sole member
;;;   of a target group for consistency and flexibility.
;;;     The dependencies of "install" themselves become (pseudo) targets
;;;   so that the basic utility functions (for commands, options, etc.)
;;;   can operate for them.
;;;     In summary, this function first selects all dependencies of the
;;;   install target, then iterates through them to produce the appropriate
;;;   install lines for each (which typically add an entry to the parts.list
;;;   file, copy the file, and set its protection).  The nested loop is
;;;   needed to handle files with multiple destinations.
;;;     Many of the fields set in the mftinstall- structure are needed
;;;   solely for parts.list.  The fields for parts-filetype and distribution
;;;   are idiosyncratic and vestigal and would better be omitted.  The field
;;;   for partslist is also idiosyncratic and could be omitted if a consistent
;;;   view were adopted that a single <product>/tape directory should not
;;;   hold multiple products.  Even the parts-subdir of parts.list could
;;;   probably be improved (e.g., with some variable definition) to
;;;   eliminate the needs for the special partslist relations.
;;; scope: internal

(defun mfgtf-install-lines (env)
  (loop
    ;; Obtain the list of dependencies, the template to be used, etc.
    with install-slots = (mftenv-install-slots env)
    with install-rename-view = (mftinstall-install-rename-view install-slots)
    with operating-system = (mftenv-operating-system env)
    with pgp-view = (mftenv-platform-group-priority-view env)
    with nonlocal-location-view = (mftenv-nonlocal-location-view env)
    with dependency-view = (mfgtf-sorted-install-dependency-view env)
    with dependency-index
    = (rdb-attribute-to-index 'dependency dependency-view)
    with dependency-type-index
    = (rdb-attribute-to-index 'dependency-type dependency-view)
    with local-index
    = (rdb-attribute-to-index 'local dependency-view)
    with template
    = (mfg-select-template
	'install-lines
        (mftenv-product-group-priority-view env)
	(mftenv-platform-group-priority-view env))
    ;; Begin the iteration for each dependency, which will temporarily become
    ;; the target so that standard functions can operate on it.
    for target-row in (rdb-table dependency-view)
    for install-target = (nth dependency-index target-row)
    for install-target-type = (nth dependency-type-index target-row)
    for tgp-view
    = (mfg-create-target-group-priority-view
	install-target
	install-target-type)
    for parts-filetype
    = (rdb-select-row-value
        'partslist-type
        (list
          (list install-target-type 'type))
        (mfg-database 'partslist-filetype-relation))
    do
    ;; Set fields that are constant for all destinations for the file to be
    ;; installed (the target).
    (setf (mftenv-target env) install-target)
    (setf (mftenv-target-type env) install-target-type)
    (setf (mftinstall-suffix install-slots)
	  (mfg-file-type-suffix install-target-type operating-system))
    (setf (mftenv-target-group-priority-view env) tgp-view)
    (setf (mftinstall-source-dir install-slots)
	  (if (eq 'y (nth local-index target-row))
	      (mfg-select-local-directory
		install-target-type
		(mftenv-local-location-view env))
	      (mfg-select-nonlocal-directory
		tgp-view
		pgp-view
		nonlocal-location-view)))
    (setf (mftinstall-parts-filetype install-slots)
          (if parts-filetype parts-filetype ""))
    (loop
      ;; Obtain the list of all destinations.
      with destination-view
      = (mfg-select-platform-target-group-rows
	  tgp-view
	  pgp-view
	  (mftinstall-destination-view install-slots))
      with new-name       ; if file is to be renamed this is non-nil
      = (rdb-select-row-value
	  'new-name
	  (list
	    (list install-target 'name)
	    (list install-target-type 'type))
	  install-rename-view)
      ;; Iterate over each destination.
      for destination-row in (rdb-table destination-view)
      for destination-dir
      = (nth (rdb-attribute-to-index 'directory destination-view)
	     destination-row)
      do
      ;; Set fields for the particular destination.
      (setf (mftinstall-destination-dir install-slots) destination-dir)
      (setf (mftinstall-partslist install-slots)
	    (nth (rdb-attribute-to-index 'partslist destination-view)
		 destination-row))
      (setf (mftinstall-parts-subdir install-slots)
	    (nth (rdb-attribute-to-index 'parts-subdir destination-view)
		 destination-row))
      (setf (mftinstall-distribution install-slots)
	    (nth (rdb-attribute-to-index 'distribution destination-view)
		 destination-row))
      (setf (mftinstall-name install-slots)
	    (if new-name new-name install-target))
      ;; Process the template that emits the install lines for the target
      ;; and destination.
      (mfg-process-template
	template
	env))))




;;; function: mfgtf-link-line
;;; arguments and return value: standard
;;; description: Dispatches the template link-line that generates the
;;;    link-line
;;; scope: internal

(defun mfgtf-link-line (env)
  (mfg-process-template
    (mfg-select-template
	'link-line
        (mftenv-product-group-priority-view env)
	(mftenv-platform-group-priority-view env))
    env))



;;; function: mfgtf-link-line-optimized
;;; arguments and return value: standard
;;; description: Dispatches the template link-line that generates the
;;;    link-line
;;; scope: internal

(defun mfgtf-link-line-optimized (env)
  (mfg-process-template
    (mfg-select-template
      'link-line-optimized ; so we can generate unstripped executables, too.
      (mftenv-product-group-priority-view env)
      (mftenv-platform-group-priority-view env))
    env))



;;; function: mfgtf-dll-link-line
;;; arguments and return value: standard
;;; description: Dispatches the template link-line that generates the
;;;    dll-link-line
;;; scope: internal

(defun mfgtf-dll-link-line (env)
  (mfg-process-template
    (mfg-select-template
	'dll-link-line
        (mftenv-product-group-priority-view env)
	(mftenv-platform-group-priority-view env))
    env))




;;; function: mfgtf-log-finish-line
;;; arguments and return value: standard
;;; description: Dispatches the template that completes logging activity for
;;;   the target.
;;; scope: internal

(defun mfgtf-log-finish-line (env)
  (mfg-process-template
    (mfg-select-template
	'log-finish-line
        (mftenv-product-group-priority-view env)
	(mftenv-platform-group-priority-view env))
    env))




;;; function: mfgtf-log-start-line
;;; arguments and return value: standard
;;; description: Dispatches the template that begins logging activity for
;;;   the target.
;;; scope: internal

(defun mfgtf-log-start-line (env)
  (mfg-process-template
    (mfg-select-template
	'log-start-line
        (mftenv-product-group-priority-view env)
	(mftenv-platform-group-priority-view env))
    env))




;;; function: mfgtf-remove-exes-lines
;;; arguments and return value: standard
;;; description: Iteratively prints a line to delete each executable.
;;; note:  This is needed within the clean: target for Unix executables
;;;   because they have no suffix to characterize them.
;;; scope: internal

(defun mfgtf-remove-exes-lines (env)
  (loop
    with template
    = (mfg-select-template
	  'remove-line
          (mftenv-product-group-priority-view env)
	  (mftenv-platform-group-priority-view env))
    for filename in (mftenv-executable-target-list env)
    do
    (setf (mftenv-filename env) filename)
    (mfg-process-template template env)))




;;; function: mfgtf-remove-target-line
;;; arguments and return value: standard
;;; description: Dispatches the template remove-target-line that deletes the
;;;   target file conditionally.  Generally used before a link or compile to
;;;   guarante that no file will be left around if the command fails initially.
;;; scope: internal

(defun mfgtf-remove-target-line (env)
  (mfg-process-template
    (mfg-select-template
	'remove-target-line
        (mftenv-product-group-priority-view env)
	(mftenv-platform-group-priority-view env))
    env))






;;;; Functions that Format and Print Lists from Env
;;;      The functions below process one of more lists stored in env
;;;    and print the members in an appropriate format.




;;; function: mfgtf-dependencies
;;; arguments and return value: standard
;;; description: First finds then prints all dependencies for the current
;;;   target. "env" is used to pass the lists of dependencies from one stage
;;;   to the next.
;;; scope: internal

(defun mfgtf-dependencies (env)
  (mfg-establish-dependencies env)
  (mfg-print-list-with-space-separators
    (mfg-dependencies-to-list-of-strings env)))




;;; function: mfgtf-dependencies-with-augmented-all
;;; arguments and return value: standard
;;; description: First finds then prints all dependencies for the current
;;;   target. "env" is used to pass the lists of dependencies from one stage
;;;   to the next. If the target is "all", two additional dependencies are
;;;   added: _mfenter and _mfexit, at the beginning and end of the dependency
;;;   list, respectively.
;;; notes: Custom makefile entries for _mfenter and _mfexit must be provided
;;;   when this is used.  They allow initialization and termination commands
;;;   to be added.
;;; scope: internal

(defun mfgtf-dependencies-with-augmented-all (env)
  (mfg-establish-dependencies env)
  (if (eq (mftenv-target env) 'all)
      (format t "_mfenter "))       ; print leading _mfenter
  (mfg-print-list-with-space-separators
    (mfg-dependencies-to-list-of-strings env))
  (if (eq (mftenv-target env) 'all)
      (format t " _mfexit")))       ; print trailing _mfexit




;;; function: mfgtf-dependencies-with-continuation-lines
;;; arguments and return value: standard
;;; description: First finds then prints all dependencies for the current
;;;   target. Line breaks (" \<return>  ") are printed to limit the number of
;;;   dependencies per line. "env" is used to pass the lists of
;;;   dependencies from one stage to the next.  An initial line length
;;;   of 20 is passed to the print routine to account for "<target> :"
;;;   in the dependency line.
;;; scope: internal

(defun mfgtf-dependencies-with-continuation-lines (env)
  (mfg-establish-dependencies env)
  (mfg-print-strings-with-continuation-lines
    20
    (mfg-dependencies-to-list-of-strings env)))




;;; function: mfgtf-objects-and-libs
;;; arguments and return value: standard
;;; description:  Prints objects, variables, and libraries with proper
;;;   suffixes and separated by spaces.
;;; modifications:
;;;     jv, 6/19/96: added shared objects by duplicating code pertaining
;;;   to libraries and replacing "library" with "shared-object".
;;; scope: internal

(defun mfgtf-objects-and-libs (env)
  (let*
      ((dependencies (mftenv-target-dependencies env))
       (operating-system (mftenv-operating-system env))
       (delimiter (mftenv-directory-delimiter env))
       (pgp-view (mftenv-platform-group-priority-view env))
       (local-location-view (mftenv-local-location-view env))
       (nonlocal-location-view (mftenv-nonlocal-location-view env))
       (objects-string-list
	 (mfg-local-dependencies-to-list-of-strings
           'obj delimiter operating-system local-location-view
           (mftdep-object-unsorted dependencies)))
       (variables-string-list
	 (mfg-variable-dependencies-to-list-of-strings
	   (mftdep-variable dependencies)))
       (resources-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'res delimiter operating-system local-location-view
	   (mftdep-resource-unsorted dependencies)))
       (libraries-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'lib delimiter operating-system local-location-view
	   (mftdep-library-unsorted dependencies)))
       (dll-libraries-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'dlib delimiter operating-system local-location-view
	   (mftdep-dll-library-unsorted dependencies)))
       (shared-objects-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'dso delimiter operating-system local-location-view
	   (mftdep-shared-object-unsorted dependencies)))
       (nonlocal-libraries-string-list
	 (mfg-nonlocal-dependencies-to-list-of-strings
	   'lib delimiter operating-system pgp-view
	   (mftdep-nonlocal-library-unsorted dependencies)
	   nonlocal-location-view))
       (nonlocal-objects-string-list
	 (mfg-nonlocal-dependencies-to-list-of-strings
	   'obj delimiter operating-system pgp-view
	   (mftdep-nonlocal-object-unsorted dependencies)
	   nonlocal-location-view)))
    (mfg-print-list-with-space-separators
      (append
	objects-string-list
	resources-string-list
	variables-string-list
	libraries-string-list
	dll-libraries-string-list
	shared-objects-string-list
	nonlocal-libraries-string-list
	nonlocal-objects-string-list))))




;;; function: mfgtf-objects-and-libs-with-continuation-lines
;;; arguments and return value: standard
;;; description:  Prints objects and libraries with proper suffixes, a space
;;;   between them, and continuation lines if needed.
;;; modifications:
;;;     jv, 6/19/96: added shared objects by duplicating code pertaining
;;;   to libraries and replacing "library" with "shared-object".
;;; scope: internal

(defun mfgtf-objects-and-libs-with-continuation-lines (env)
  (let*
      ((dependencies (mftenv-target-dependencies env))
       (operating-system (mftenv-operating-system env))
       (delimiter (mftenv-directory-delimiter env))
       (pgp-view (mftenv-platform-group-priority-view env))
       (local-location-view (mftenv-local-location-view env))
       (nonlocal-location-view (mftenv-nonlocal-location-view env))
       (objects-string-list
	 (mfg-local-dependencies-to-list-of-strings
          'obj delimiter operating-system local-location-view
           (mftdep-object-unsorted dependencies)))
       (resources-string-list
	 (mfg-local-dependencies-to-list-of-strings
          'res delimiter operating-system local-location-view
           (mftdep-resource-unsorted dependencies)))
       (variables-string-list
	 (mfg-variable-dependencies-to-list-of-strings
	   (mftdep-variable dependencies)))
       (libraries-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'lib delimiter operating-system local-location-view
	   (mftdep-library-unsorted dependencies)))
       (dll-libraries-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'dlib delimiter operating-system local-location-view
	   (mftdep-dll-library-unsorted dependencies)))
       (shared-objects-string-list
	 (mfg-local-dependencies-to-list-of-strings
	   'dso delimiter operating-system local-location-view
	   (mftdep-shared-object-unsorted dependencies)))
       (nonlocal-libraries-string-list
	 (mfg-nonlocal-dependencies-to-list-of-strings
	   'lib delimiter operating-system pgp-view
	   (mftdep-nonlocal-library-unsorted dependencies)
	   nonlocal-location-view))
       (nonlocal-objects-string-list
	 (mfg-nonlocal-dependencies-to-list-of-strings
	   'obj delimiter operating-system pgp-view
	   (mftdep-nonlocal-object-unsorted dependencies)
	   nonlocal-location-view)))
    (mfg-print-strings-with-continuation-lines
      35    ; to allow link command and options
      (append
	objects-string-list
	resources-string-list
	variables-string-list
	libraries-string-list
	dll-libraries-string-list
	shared-objects-string-list
	nonlocal-libraries-string-list
	nonlocal-objects-string-list))))




;;; function: mfgtf-nonlocal-library-dummy-dependencies
;;; arguments and return value: standard
;;; description: Prints the members of nonlocal-library-target-list with
;;;   spaces between them.  This is part of a mechanism to allow nonlocal
;;;   libraries to be updated before their use.  All nonlocal libraries are
;;;   listed in "dummy" form (no suffix) as dependencies of "all".
;;; scope: internal

(defun mfgtf-nonlocal-library-dummy-dependencies (env)
  (mfg-print-list-with-space-separators
    (mftenv-nonlocal-library-target-list env)))




;;; function: mfgtf-nonlocal-object-dummy-dependencies
;;; arguments and return value: standard
;;; description: Prints the members of nonlocal-object-target-list with
;;;   spaces between them.  This is part of a mechanism to allow nonlocal
;;;   libraries to be updated before their use.  All nonlocal libraries are
;;;   listed in "dummy" form (no suffix) as dependencies of "all".
;;; modifications:
;;;     jv, 6/19/96: created mfgtf-nonlocal-shared-object-dummy-dependencies
;;;   by duplicating mfgtf-nonlocal-library-dummy-dependencies and replacing
;;;   "library" with "shared-object".
;;; scope: internal

(defun mfgtf-nonlocal-object-dummy-dependencies (env)
  (mfg-print-list-with-space-separators
    (mftenv-nonlocal-object-target-list env)))




;;; function: mfgtf-strings-with-continuation-lines
;;; arguments and return value: standard
;;;   within env, tmp-list contains a list of strings to be printed
;;; description: Prints the strings in tmp-list with standard continuation
;;;   lines.
;;; notes:  This is a special function that requires that a predecessor in
;;;   the template set tmp-list.  It should be used only in rare cases and
;;;   with extreme care because it can be very difficult to track.
;;; scope: internal

(defun mfgtf-strings-with-continuation-lines (env)
    (mfg-print-strings-with-continuation-lines
     30  ; to allow for archive command, options, and archive name
     (mftenv-tmp-list env)))








;;;; Fields from env
;;;      Many of these, which have name, mfgtf-<name>, simply print
;;;    the <name> field of env with the appropriate format (current-dir,
;;;    directory-delimiter, filename, odir, product, target).  Those for
;;;    c-source, full-target, h-file, and *nonlocal* produce full pathnames.
;;;    A few (log-type, runmake-product-kludge) make simple mappings of env
;;;    fields to names to accommodate commands with peculiar needs.




;;; function: mfgtf-c-source-for-target
;;; arguments and return value: standard
;;; description: Prints the target basename as a full path to source with the
;;;   appropriate c suffix
;;; modifications:
;;;     jv, 6/19/96: Added "override source".  Prior to this change, the makefile
;;;   generator made the reasonable assumption that the target (object) file
;;;   would share the same basename as the source file.  However, we now have a
;;;   case where we want to be able to compile a C source file one way for one
;;;   product, then compile it with different options for another product.  The
;;;   solution chosen for this problem is to use a different target name for the
;;;   "second" compilation.  This function now uses the "source-target-relation"
;;;   defined in commands-and-options.rel.
;;; scope: internal

(defun mfgtf-c-source-for-target (env)
  (let* ((target (mftenv-target env))    ; target basename
	 (override-source
	   (cadr (assoc target (cadr (mfg-database 'source-target-relation)))))
	 (source-file-type
	   (if (member target (mfg-database 'c++-files))
	       'c++
	       'c))
	 (source (or override-source target)))
    (mfg-print-downcased
      (mfg-full-filename-string
	(mfg-select-local-directory      ; directory path
	  'c
	  (mftenv-local-location-view env))
	(mftenv-directory-delimiter env)
	source
	(mfg-file-type-suffix            ; c suffix
	  source-file-type
	  (mftenv-operating-system env))))))




;;; function: mfgtf-current-dir
;;; arguments and return value: standard
;;; description: prints the value of the current-dir slot, which identifies
;;;   the directory in which the makefile is located.
;;; scope: internal

(defun mfgtf-current-dir (env)
  (mfg-print-downcased
    (mftenv-current-dir env)))




;;; function: mfgtf-dir-delim
;;; arguments and return value: standard
;;; description: For the operating system in use, prints the delimiter that
;;;   separates a directory path from a filename.
;;; scope: internal

(defun mfgtf-dir-delim (env)
  (let ((value (mftenv-directory-delimiter env)))
    (typecase value
      (character (write-char value))
      (string (write-string value))
      (t (format t "~a" value)))))




;;; function: mfgtf-filename
;;; arguments and return value: standard
;;; description: prints the value of the filename property
;;; scope: internal

(defun mfgtf-filename (env)
   (mfg-print-downcased (mftenv-filename env)))




;;; function: mfgtf-full-nonlocal-target
;;; arguments and return value: standard
;;; description: prints the directory, name, and suffix of the target
;;; scope: internal

(defun mfgtf-full-nonlocal-target (env)
  (format t "~a~a~a~a"
	  (mfg-downcase-symbol
	    (mfg-select-nonlocal-directory
	      (mftenv-target-group-priority-view env)
	      (mftenv-platform-group-priority-view env)
	      (mftenv-nonlocal-location-view env)))
	  (mftenv-directory-delimiter env)
	  (mfg-downcase-symbol (mftenv-target env))
	  (mfg-downcase-symbol
	    (mfg-file-type-suffix
	      (mftenv-target-type env)
	      (mftenv-operating-system env)))))




;;; function: mfgtf-h-file-for-target
;;; arguments and return value: standard
;;; description: Prints the target basename as a full path to source with the
;;;   appropriate h suffix
;;; scope: internal

(defun mfgtf-h-file-for-target (env)
  (mfg-print-downcased
    (mfg-full-filename-string
      (mfg-select-local-directory      ; directory path
	'h
	(mftenv-local-location-view env))
      (mftenv-directory-delimiter env)
      (mftenv-target env)              ; target basename
      (mfg-file-type-suffix            ; h suffix
	'h
	(mftenv-operating-system env)))))




;;; function: mfgtf-log-type
;;; arguments and return value: standard
;;; description: This determines and prints the command expected by cc_log
;;;   for the given target type.
;;; scope: internal

(defun mfgtf-log-type (env)
  (mfg-print-downcased
    (case (mftenv-target-type env)
      (obj  'cc)
      (exe  'link)
      (lib  'ar)
      (t    'UNKNOWN_LOG_TYPE))))




;;; function: mfgtf-nonlocal-lib-target-dir
;;; arguments and return value: standard
;;; description: prints the directory of the target, which is a nonlocal
;;;   library
;;; scope: internal

(defun mfgtf-nonlocal-lib-target-dir (env)
  (mfg-print-downcased
    (mfg-select-nonlocal-directory
      (mftenv-target-group-priority-view env)
      (mftenv-platform-group-priority-view env)
      (mftenv-nonlocal-location-view env))))




;;; function: mfgtf-nonlocal-dso-target-dir
;;; arguments and return value: standard
;;; description: prints the directory of the target, which is a nonlocal
;;;   shared-object
;;; modifications:
;;;     jv, 6/19/96: created mfgtf-nonlocal-so-target-dir by duplicating
;;;   mfgtf-nonlocal-lib-target-dir and replacing "library" with
;;;   "shared-object".
;;;     jv, 11/22/03: change function name: "so" becomes "dso"
;;; scope: internal

(defun mfgtf-nonlocal-dso-target-dir (env)
  (mfg-print-downcased
    (mfg-select-nonlocal-directory
      (mftenv-target-group-priority-view env)
      (mftenv-platform-group-priority-view env)
      (mftenv-nonlocal-location-view env))))





;;; function: mfgtf-odir
;;; arguments and return value: standard
;;; description: prints the object directory for the current compilation
;;;   category; i.e., o, opt, or o-pg
;;; scope: internal

(defun mfgtf-odir (env)
  (mfg-print-downcased
    (mfg-compile-category-to-directory
      (mftenv-compile-category env))))




;;; function: mfgtf-product
;;; arguments and return value: standard
;;; description: prints the current product
;;; scope: internal

(defun mfgtf-product (env)
   (mfg-print-downcased (mftenv-product env)))




;;; function: mfgtf-target
;;; arguments and return value: standard
;;; description: Prints the target name.
;;; scope: internal

(defun mfgtf-target (env)
  (mfg-print-downcased (mftenv-target env)))




;;; function: mfgtf-target-as-variable
;;; arguments and return value: standard
;;; description: Prints the target name as a variable (upper case by default)
;;; scope: internal

(defun mfgtf-target-as-variable (env)
  (format t "~a" (mftenv-target env)))




;;; function: mfgtf-target-with-suffix
;;; arguments and return value: standard
;;; description: Prints the target and the suffix associated with the target-type and
;;;   operating system.
;;; scope: internal

(defun mfgtf-target-with-suffix (env)
  (mfg-print-downcased (mftenv-target env))
  (mfg-print-downcased (mfg-file-type-suffix
			 (mftenv-target-type env)
			 (mftenv-operating-system env))))




;;; function: mfgtf-target-with-dll-suffix
;;; arguments and return value: standard
;;; description: Prints the target, and uses the suffix ".dll"
;;; scope: internal

(defun mfgtf-target-with-dll-suffix (env)
  (mfg-print-downcased (mftenv-target env))
  (write-string ".dll"))



;;; function: mfgtf-target-with-unstripped-suffix-if-opt
;;; arguments and return value: standard
;;; description: Prints the target, and uses the suffix ".unstripped"
;;; scope: internal

(defun mfgtf-target-with-unstripped-suffix (env)
  (mfg-print-downcased (mftenv-target env))
  (write-string ".unstripped"))






;;;; Commands
;;;      The functions in this section are extremely simple.  With the
;;;    exception of the mfgtf-compile-command, which is precomputed and
;;;    stored in env for faster access, each function mfgtf-<command>-command
;;;    simple selects <command> from the commands-relation and prints it.


;;; function: mfgtf-archive-command
;;; arguments and return value: standard
;;; description: Prints the command to store objects in a library.
;;; scope: internal

(defun mfgtf-archive-command (env)
  (mfg-print-downcased
     (mfg-select-command 'archive (mftenv-platform-group-priority-view env))))


(defun mfgtf-shared-object-command (env)
  (mfg-print-downcased
     (mfg-select-command 'shared-object (mftenv-platform-group-priority-view env))))


;;; function: mfgtf-dll-archive-command
;;; arguments and return value: standard
;;; description: Prints the command to store objects in a DLL library.
;;; scope: internal

(defun mfgtf-dll-archive-command (env)
  (mfg-print-downcased
     (mfg-select-command 'dll-archive (mftenv-platform-group-priority-view env))))




;;; function: mfgtf-archive-insert-command
;;; arguments and return value: standard
;;; description: Prints the command to insert files into a library.
;;; scope: internal

(defun mfgtf-archive-insert-command (env)
  (mfg-print-downcased
     (mfg-select-command
      'archive-insert
      (mftenv-platform-group-priority-view env))))




;;; function: mfgtf-cd-command
;;; arguments and return value: standard
;;; description: Prints the command to change the working directory
;;; scope: internal

(defun mfgtf-cd-command (env)
  (mfg-print-downcased
     (mfg-select-command 'cd (mftenv-platform-group-priority-view env))))




;;; function: mfgtf-chmod-command
;;; arguments and return value: standard
;;; description: Prints the command to change the protection of a file
;;; scope: internal

(defun mfgtf-chmod-command (env)
  (mfg-print-downcased
     (mfg-select-command 'chmod (mftenv-platform-group-priority-view env))))




;;; function: mfgtf-compile-command
;;; arguments and return value: standard
;;; description: Prints the command to compile files.
;;; notes: Because this command is printed so frequently, its value is
;;;   precomputed for each platform and stored in the environment.
;;; scope: internal

(defun mfgtf-compile-command (env)
  (mfg-print-downcased
    (mftenv-compile-command env)))




;;; function: mfgtf-install-command
;;; arguments and return value: standard
;;; description: Prints the command to install (copy) a file in its destination
;;; scope: internal

(defun mfgtf-install-command (env)
  (mfg-print-downcased
     (mfg-select-command 'install (mftenv-platform-group-priority-view env))))




;;; function: mfgtf-strip-command
;;; arguments and return value: standard
;;; description: Prints the command to strip the linker symbols from an executable file
;;; scope: internal

(defun mfgtf-strip-command (env)
  (mfg-print-downcased
     (mfg-select-command 'strip (mftenv-platform-group-priority-view env))))




;;; function: mfgtf-link-command
;;; arguments and return value: standard
;;; description: Prints the command to link objects to create an executable.
;;; scope: internal

(defun mfgtf-link-command (env)
  (mfg-print-downcased
     (mfg-select-command 'link (mftenv-platform-group-priority-view env))))



;;; function: mfgtf-dll-link-command
;;; arguments and return value: standard
;;; description: Prints the command to link objects to create an executable,
;;;              using a GSI DLL.
;;; scope: internal

(defun mfgtf-dll-link-command (env)
  (mfg-print-downcased
     (mfg-select-command 'dll-link (mftenv-platform-group-priority-view env))))




;;; function: mfgtf-log-command
;;; arguments and return value: standard
;;; description: Prints the command that logs command activity
;;; scope: internal

(defun mfgtf-log-command (env)
  (mfg-print-downcased
     (mfg-select-command 'log (mftenv-platform-group-priority-view env))))




;;; function: mfgtf-errlog-command
;;; arguments and return value: standard
;;; description: Prints the command that monitors makefile progress.
;;; scope: internal

(defun mfgtf-errlog-command (env)
  (mfg-print-downcased
     (mfg-select-command 'errlog (mftenv-platform-group-priority-view env))))




;;; function: mfgtf-make-command
;;; arguments and return value: standard
;;; description: Prints the command to invoke makefile processing.
;;; scope: internal

(defun mfgtf-make-command (env)
  (mfg-print-downcased
     (mfg-select-command 'make (mftenv-platform-group-priority-view env))))




;;; function: mfgtf-ranlib-command
;;; arguments and return value: standard
;;; description: Prints the command to change the working directory
;;; scope: internal

(defun mfgtf-ranlib-command (env)
  (mfg-print-downcased
     (mfg-select-command 'ranlib (mftenv-platform-group-priority-view env))))




;;; function: mfgtf-remove-command
;;; arguments and return value: standard
;;; description: Prints the command to change the working directory
;;; scope: internal

(defun mfgtf-remove-command (env)
  (mfg-print-downcased
     (mfg-select-command 'remove (mftenv-platform-group-priority-view env))))




;;; function: mfgtf-runmake-command
;;; arguments and return value: standard
;;; description: Prints the "runmake" command, which invokes a script that
;;    copies the makefile to the appropriate directory and invokes make there.
;;; scope: internal

(defun mfgtf-runmake-command (env)
  (mfg-print-downcased
     (mfg-select-command 'runmake (mftenv-platform-group-priority-view env))))






;;;; Command Options
;;;      All functions in this group have name mfgtf-<command>-options
;;;    and have identical form. Each identically selects, formats, and
;;;    prints relevant options from command-options-relation.  Each function
;;;    looks for two types of option, <command> and general-<command>.  The
;;;    general- option uses inclusive inheritance such that all options for all
;;;    relevant types are retained.  The non-general option uses exclusive
;;;    inheritance such that only options for the highest priority are
;;;    retained.  Both general and non-general options are combined.
;;;    See the notes in commands-and-options.rel for additional explanation.
;;;      Note that the following option-name abbrevations are used.
;;;
;;;             FUNCTION               OPTION
;;;            archive               archv
;;;            archive-insert        inarchv
;;;            archive-obj           archvobj
;;;            include-paths         ipaths
;;;            lib-paths             libpath
;;;            libs                  lib




;;; function: mfgtf-archive-options
;;; arguments and return value: standard
;;; description: Selects archive options from options-relation
;;;   and prints them separated by spaces.  Options are selected from 
;;;   options-relation from the option-category specified by archv and
;;;   general-archv.
;;; scope: internal

(defun mfgtf-archive-options (env)
  (write-string
    (mfg-select-command-options-to-string
      'archv
      'general-archv
      #'mfg-print-list-with-space-separators
      env)))




;;; function: mfgtf-archive-insert-options
;;; arguments and return value: standard
;;; description: Selects archive options from options-relation
;;;   and prints them with appropriate separation.  Options are selected from 
;;;   options-relation from the option-category specified by inarchv and
;;;   general-inarchv.
;;; scope: internal

(defun mfgtf-archive-insert-options (env)
  (write-string
    (mfg-select-command-options-to-string
      'inarchv
      'general-inarchv
      #'mfg-print-list-without-separators
      env)))




;;; function: mfgtf-archive-obj-options
;;; arguments and return value: standard
;;; description: Selects special archive objects from options-relation
;;;   and prints them separated by spaces.  Options are selected from
;;;   options-relation from the option-category specified by archvobj and
;;;   general-archvobj.
;;; notes:  This is typically used to include objects from nonlocal,
;;;   non-Gensym directories, such as special objects from compilers.
;;;   Typically there are no dependencies on these objects because
;;;   they do not have their own target entries.
;;; scope: internal

(defun mfgtf-archive-obj-options (env)
  (write-string
    (mfg-select-command-options-to-string
      'archvobj
      'general-archvobj
      #'mfg-print-list-with-space-separators
      env)))




;;; function: mfgtf-cc-odp-options
;;; arguments and return value: standard
;;; description: Selects optimize-debug-profile compilation options from
;;;   compilation-options-relation and prints them separated by spaces. Options
;;;   are selected from the cc-odp and general-cc-odp option-categories.
;;; scope: internal

(defun mfgtf-cc-odp-options (env)
  (write-string
    (mfg-select-command-options-to-string
      'cc-odp
      'general-cc-odp
      #'mfg-print-list-with-space-separators
      env)))




;;; function: mfgtf-cc-options
;;; arguments and return value: standard
;;; description: Selects compilation options from compilation-options-relation
;;;   and prints them separated by spaces.  Options are selected from 
;;;   compile-options-relation from the option-category specified by the
;;;   cc and general-cc categories.
;;; scope: internal

(defun mfgtf-cc-options (env)
  (write-string
    (mfg-select-command-options-to-string
      'cc
      'general-cc
      #'mfg-print-list-with-space-separators
      env)))




;;; function: mfgtf-chmod-options
;;; arguments and return value: standard
;;; description: Selects link options from options-relation
;;;   and prints them separated by spaces.  Options are selected from 
;;;   options-relation from the option-category specified by
;;;   link and general-link.
;;; scope: internal

(defun mfgtf-chmod-options (env) 
  (write-string
    (mfg-select-command-options-to-string
      'chmod
      'general-chmod
      #'mfg-print-list-with-space-separators
      env)))




;;; function: mfgtf-include-paths
;;; arguments and return value: standard
;;; description: Selects compilation options for "ipath" and "general-ipath".
;;;   These are the include paths for the compilation line.  They are printed
;;; in the format "-I<path1> -I<path2>..."
;;; scope: internal

(defun mfgtf-include-paths (env)
  (write-string
    (mfg-select-command-options-to-string
      'ipath
      'general-ipath
      #'mfg-print-include-path-options
      env)))




;;; function: mfgtf-install-options
;;; arguments and return value: standard
;;; description: Selects link options from options-relation
;;;   and prints them separated by spaces.  Options are selected from 
;;;   options-relation from the option-category specified by
;;;   link and general-link.
;;; notes: this is essentially useless because options are restricted
;;;   to a particular file type, but the install command is not.  This
;;;   means that in the database, options must be replicated for
;;;   every file type
;;; scope: internal

(defun mfgtf-install-options (env) 
  (write-string
    (mfg-select-command-options-to-string
      'install
      'general-install
      #'mfg-print-list-with-space-separators
      env)))




;;; function: mfgtf-lib-paths
;;; arguments and return value: standard
;;; description: Selects library paths from options-relation
;;;   and prints them appropriately.  Options are selected from 
;;;   options-relation from the option-category specified by
;;;   libpath and general-libpath.
;;; scope: internal

(defun mfgtf-lib-paths (env)
  (write-string
    (mfg-select-command-options-to-string
      'libpath
      'general-libpath
      #'mfg-print-list-with-space-separators
      env)))




;;; function: mfgtf-libs
;;; arguments and return value: standard
;;; description: Selects link libraries from options-relation
;;;   and prints them appropriately.  Options are selected from 
;;;   options-relation from the option-category specified by
;;;   lib and general-lib.
;;; scope: internal

(defun mfgtf-libs (env)
  (write-string
    (mfg-select-command-options-to-string
      'lib
      'general-lib
      #'mfg-print-list-with-space-separators
      env)))






;;; function: mfgtf-link-options
;;; arguments and return value: standard
;;; description: Selects link options from options-relation
;;;   and prints them separated by spaces.  Options are selected from 
;;;   options-relation from the option-category specified by
;;;   link and general-link.
;;; scope: internal

(defun mfgtf-link-options (env) 
  (write-string
    (mfg-select-command-options-to-string
      'link
      'general-link
      #'mfg-print-list-with-space-separators
      env)))




;;; function: mfgtf-make-options
;;; arguments and return value: standard
;;; description: Selects make options from options-relation
;;;   and prints them separated by spaces.  Options are selected from 
;;;   options-relation from the option-category specified by make and
;;;   general-make.  Make options are typically the means by which explicit
;;;   definitions are passed to the makefile.
;;; scope: internal

(defun mfgtf-make-options (env)
  (write-string
    (mfg-select-command-options-to-string
      'make
      'general-make
      #'mfg-print-list-with-space-separators
      env)))






;;;;  Install Entry Components
;;;       The functions in this section format and print the fields of the
;;;     install-slots substructure of env.  They are dispatched exclusively
;;;     from the install-lines template, and the fields of the install-slot
;;;     structure are set exclusively by the mfgtf-install-lines function,
;;;     which initiates processing of the install-lines template.




;;; function: mfgtf-install-destination-dir
;;; arguments and return value: standard
;;; description: Prints the directory path of the file to be installed.
;;; scope: internal

(defun mfgtf-install-destination-dir (env)
  (format t "~a"
	  (mftinstall-destination-dir (mftenv-install-slots env))))




;;; function: mfgtf-install-distribution
;;; arguments and return value: standard
;;; description: Prints distribution fields for parts.list and file being
;;;   installed.
;;; scope: internal

(defun mfgtf-install-distribution (env)
  (mfg-print-downcased
    (mftinstall-distribution (mftenv-install-slots env))))




;;; function: mfgtf-install-filename-and-suffix
;;; arguments and return value: standard
;;; description: Prints filename and suffix of the installed file.
;;; scope: internal

(defun mfgtf-install-filename-and-suffix (env)
  (let ((install-slots (mftenv-install-slots env)))
    (mfg-print-downcased
      (mftinstall-name install-slots))
    (write-string
      (mftinstall-suffix install-slots))))




;;; function: mfgtf-install-full-destination
;;; arguments and return value: standard
;;; description: Prints the full path and filename of the destination of the
;;;   file to be installed.
;;; scope: internal

(defun mfgtf-install-full-destination (env)
  (let
      ((install-slots (mftenv-install-slots env)))
    (format t "~a"
	    (mfg-full-filename-string
	      (mftinstall-destination-dir install-slots)
	      (mftenv-directory-delimiter env)
	      (mftinstall-name install-slots)
	      (mftinstall-suffix install-slots)))))




;;; function: mfgtf-install-full-source
;;; arguments and return value: standard
;;; description: Prints the full path and filename of the file to be installed.
;;; scope: internal

(defun mfgtf-install-full-source (env)
  (let
      ((install-slots (mftenv-install-slots env)))
    (format t "~a"
	    (mfg-full-filename-string
	      (mftinstall-source-dir install-slots)
	      (mftenv-directory-delimiter env)
	      (mftenv-target env)
	      (mftinstall-suffix install-slots)))))




;;; function: mfgtf-install-nonempty-source-dir
;;; arguments and return value: standard
;;; description: Prints the directory path of the file to be installed.  If
;;;   it is the current directory, $(MFDIR) is printed.  This is needed by
;;;   tar when copying files from the current directory.
;;; scope: internal

(defun mfgtf-install-nonempty-source-dir (env)
  (let
      ((dir
	  (mftinstall-source-dir (mftenv-install-slots env))))
    (format t "~a" 
	    (if (rdb-equal "" dir)
		"$(MFDIR)"
		dir))))




;;; function: mfgtf-install-parts-filetype
;;; arguments and return value: standard
;;; description: Prints distribution filetype for file being installed.
;;; scope: internal

(defun mfgtf-install-parts-filetype (env)
  (mfg-print-downcased
    (mftinstall-parts-filetype (mftenv-install-slots env))))




;;; function: mfgtf-install-parts-subdir
;;; arguments and return value: standard
;;; description: Prints subdirectory portion of parts.list entry.
;;; scope: internal

(defun mfgtf-install-parts-subdir (env)
  (format t "~a"
	  (mftinstall-parts-subdir (mftenv-install-slots env))))




;;; function: mfgtf-install-partslist
;;; arguments and return value: standard
;;; description: Prints directory in which the relevant parts.list is stored.
;;; scope: internal

(defun mfgtf-install-partslist (env)
  (format t "~a"
	  (mftinstall-partslist (mftenv-install-slots env))))




;;; function: mfgtf-install-source-dir
;;; arguments and return value: standard
;;; description: Prints the directory path of the file to be installed.
;;; scope: internal

(defun mfgtf-install-source-dir (env)
  (format t "~a"
	  (mftinstall-source-dir (mftenv-install-slots env))))

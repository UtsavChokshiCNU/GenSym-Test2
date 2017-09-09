;;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: USER -*-
(in-package "USER")

;;;; Module MFGMAIN (makefile generator main interface)
;;; 
;;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;;  All Rights Reserved.
;;;
;;;; Author: Mark E. Staknis
;;;
;;;; Description:
;;;      This module contains the Lisp user interface to generate makefiles
;;;    for Gensym's core products.  Directly or indirectly, it makes use
;;;    of all lisp files and relations.  All access to the modules should be
;;;    through the user-interface function mfg-generate-makefiles-for-build,
;;;    which is contained in this file.
;;;      For details of the overall module organization, see Notes below.
;;;
;;;; Dependencies: mfg.lisp, rdb.lisp
;;;
;;;; External User Interface: mfg-generate-makefiles-for-build (see below)
;;;
;;;; File Organization:
;;;
;;;    Functions to Set Initial Values of env
;;;      mfg-establish-operating-system (platform-group-priority-view):
;;;        Searches the view to find operating system and returns it.
;;;      mfg-establish-variable-value-view
;;;        (product compile-category platform-group-priority-view):
;;;        Constructs initial variable-value-view for product and compile
;;;        category.  Accesses variable-initialization-relation to do so.
;;;      mfg-establish-targets (env):  Sets target-list fields of env (dummy,
;;;        executable, library, etc.) by calling following function.
;;;      mfg-add-targets-recursively-to-env (target type env):  Traverses the
;;;        dependency view to find all targets and adds them to the appropriate
;;;        target list.
;;;      mfg-establish-command-options-view
;;;        (product-group-priority-view compile-category
;;;          platform-group-priority-view):
;;;        Preprocess command-options-relation to extract commands relevant
;;;        for platform, product, and compile category.
;;;      mfg-establish-install-destination-relation (product compile-category)
;;;        Find and return install-destination relation if one is defined.
;;;      mfg-establish-env (platform compile-category product dependency-view):
;;;        Creates and returns a new env.  This is the coordinating function
;;;        that calls all others in this section.
;;;      mfg-determine-starting-template-name (product compile-category...):
;;;        Finds the starting template for the product and compile-category
;;;
;;;    Functions for Makefile Creation 
;;;      mfg-generate-standard-makefile
;;;        (platform compile-category product dependency-view): Creates and
;;;        prints makefile to standard output.  Coordinates env creation,
;;;        initial template selection and invocation, and printing of
;;;        variable ("macro") definitions.
;;;      mfg-generate-standard-makefile-to-file
;;;        (platform compile-category product dependency-view filename):
;;;        Wrapper for mfg-generate-standard-makefile that redirects standard
;;;        output to specified file.
;;;
;;;    Utility Functions for User Interface
;;;      mfg-file-to-list (filename): Reads specified file as stream of
;;;        symbols and returns them in a list.
;;;      mfg-create-dependency-table (product dependent type filelist):
;;;        Creates dependency entries for list of files of translated product.
;;;      mfg-load-dependency-view (product): Loads file containing the
;;;        product's dependency relation 
;;;      mfg-set-up-dependency-view (product):  Creates the dependency view
;;;        for the product, possibly by augmenting it, for translated products,
;;;        with additional dependency rows.
;;;      mfg-load-and-set-up-dependency-view (product): Calls the two
;;;        preceding functions.
;;;      mfg-bind-special-symbols ():  Checks that special symbol SRCBOX
;;;        is bound and binds it to /bt/ab if not.
;;;      mfg-create-makefile-path-and-name (compile-category product platform):
;;;        Constructs appropriate pathname of form "../mfiles/<filename>".
;;;      mfg-load-database (): Loads all relation files except
;;;        of the dependency files, which are loaded per product.
;;;
;;;    User Interface
;;;      mfg-generate-makefiles-for-build (&optional argument-list): Iterates
;;;        over all products, platforms, and compile categories, producing
;;;        makefiles for all that are legal.
;;;
;;;    Utility Functions for Manual Use and Debugging
;;;      show-options
;;;        (option-category platform
;;;         &key (target 'dummytarget) target-type (compile-category 'optimize)
;;;         (product 'ext))
;;;        Determines and returns options for the target, platform, etc.
;;;      generate-single-makefile
;;;        (product platform &key filename (category 'optimize)):
;;;        Produces a makefile for the specified parameters.  Useful with
;;;        breakpoints in a Lisp environment.
;;;
;;;; Notes:
;;;      This module serves as Lisp coordinator for makefile generation.
;;;    The function mfg-generate-makefiles-for-build is the user interface
;;;    function.  It processes command-line arguments and creates individual
;;;    makefiles with repeated calls to mfg-generate-standard-makefile.
;;;    For debugging in a Lisp environment, one can use
;;;    mfg-generate-standard-makefile and the functions in the last section.
;;;      jv, 6/19/96: My suggestions for debugging in Lisp:
;;;    -- start Lucid (M-x lucid)
;;;    - (in-package 'user)
;;;    -- make sure ${SRCBOX}/gen/mfgen/sbin exists
;;;    - (defvar SRCBOX "<your-srcbox-here>")
;;;    - (cd (format nil "~a/gen/mfgen" SRCBOX))
;;;    -- M-x default-directory-lisp  (C-z !)
;;;    - (load "compile-and-load-mfg.lisp")
;;;    - (compile-and-load-mfg)
;;;
;;;    - (mfg-generate-makefiles-for-build '(<platforms> <products> <compile-types>))
;;;
;;; - or -
;;;
;;;    - (mfg-load-database)
;;;    - (mfg-load-dependency-view '<product>)
;;;    - (setq dep-view (mfg-set-up-dependency-view '<product>))
;;;    - (mfg-generate-standard-makefile
;;;           '<platform> '<optimize|debug>  '<product> dep-view)






;;;; Functions to Set Initial Values of env
;;;      The functions in this section are used to create and populate a
;;;    new instance of the structure env, which is passed as a parameter
;;;    to template functions (in mfgtf.lisp).  The env is the means of
;;;    passing data between stages. The function mfg-establish-env is
;;;    the initial function called.  With the exception of
;;;    mfg-add-targets-recursively-to-env, all other functions are called
;;;    just once and have been separated merely to improve readability.




;;; function: mfg-establish-operating-system
;;; arguments:
;;;   platform-group-priority-view: groups and priorities of current platform
;;; return value: the symbol representing the current operating system or
;;;   unix, the default, if not found
;;; description: Searches through the platform-group-priority-view for the
;;;   operating system to which the platform belongs and returns the operating
;;;   system name
;;; notes: the operating systems could be listed in a relation
;;; scope: internal

(defun mfg-establish-operating-system (platform-group-priority-view)
  (let
      ((group-list
         (rdb-column-to-list 'group platform-group-priority-view)))
    (loop
      for os in '(unix win32)
      if (member os group-list)
        return os
      finally
        (return 'unix))))




;;; function: mfg-establish-variable-value-view
;;; arguments:
;;;   platform: linux, intelnt, etc.
;;;   product: any product as defined in products-relation, e.g. g2, ext
;;;   compile-category: debug, optimize, or profile
;;;   platform-group-priority-view:groups and priorities of current platform
;;; return value: a pointer to an empty variable-value-view
;;; description: Creates a variable-value-view initialized with variables
;;;    for the current product, platform, and compilation-category. The
;;;    variables ODIR and PLATFORM are defined and added to a constructed view.
;;;    The view is constructed from variable-initialization-relation in
;;;    stages.  First, selection is made for "category" equal to
;;;    compile-category and _all.  Second, the highest priority platform
;;;    and product groups are selected.  The latter is accomplished by
;;;    selecting all relevant platform and product rows, sorting them so that
;;;    the highest priority row for each variable is first, then deleting
;;;    all but the first row for each variable.  The highest priority variables
;;;    remain.  A projection is performed to obtain the appropriate fields
;;;    for the variable-value-view, and the variables ODIR and PLATFORM
;;;    are added.
;;; scope: internal

(defun mfg-establish-variable-value-view (platform
					   compile-category
					   product-group-priority-view
					   platform-group-priority-view)
  (let*
      ((vv-view
	 (rdb-project-relation
	   '(variable-name position variable-value)
	   ;; Delete all but the highest priority value for each variable.
	   (rdb-delete-adjacent-duplicate-rows
	     '(variable-name)
	     ;; Sort the table so that variable names are grouped together
	     ;; and the highest priority platform and product is first in each
	     ;; group. (This relies on knowledge that the ...select-all... call
	     ;; renames the product priority to product-priority.)
	     (rdb-sort-relation
	       '(variable-name priority product-priority)
	       (mfg-select-all-platform-product-group-rows
		 product-group-priority-view
		 platform-group-priority-view
		 ;; select rows whose compile-category is either _all
		 ;; or the current compilation category
		 (rdb-select-rows-with-or
		   (list (list
			   (list  compile-category '_all)
				 'compile-category))
		   (mfg-database 'variable-initialization-relation))))))))
    (mfg-install-variable-and-position-and-value
      "PLATFORM"
      'c
      (mfg-downcase-symbol platform)
      vv-view)
    (mfg-install-variable-and-position-and-value
      "ODIR"
      'c
      (mfg-compile-category-to-directory compile-category)
      vv-view)
    vv-view))




;;; function: mfg-establish-targets
;;; arguments:
;;;   env: the instance of mftenv containing the template-function environment
;;; return value: nil
;;; side effects: initializes the following env slots
;;;   dummy-target-list: a list of dummy targets
;;;   library-target-list: a list of libraries to be made
;;;   nonlocal-library-target-list: a list of nonlocal libraries to be made
;;;   executable-target-list: a list of targets that require linking
;;;   object-target-list: a list of targets the require compilation
;;; description:  The purpose of this function is to create ordered lists of
;;;   all targets for the makefile. It gathers information from the
;;;   dependency-view to create lists of targets for a given makefile and
;;;   platform.  The items added to env are subsequently referenced by the
;;;   template functions.  The first target entry of every makefile is the
;;;   dummy target "all", and all dependencies in dependency-view should be
;;;   reachable from it; by default a makefile makes all executables and
;;;   libraries.
;;; modifications:
;;;     jv, 6/19/96: added shared objects to mtenv, with the appropriate
;;;   initialization (to nil) here.
;;; scope: internal

(defun mfg-establish-targets (env)
  (progn
    (setf (mftenv-dummy-target-list            env) nil)  ;initialize the lists
    (setf (mftenv-variable-target-list         env) nil)
    (setf (mftenv-executable-target-list       env) nil)
    (setf (mftenv-dll-executable-target-list   env) nil)
    (setf (mftenv-library-target-list          env) nil)
    (setf (mftenv-dll-library-target-list      env) nil)
    (setf (mftenv-shared-object-target-list    env) nil)
    (setf (mftenv-nonlocal-library-target-list env) nil)
    (setf (mftenv-nonlocal-object-target-list  env) nil)
    (setf (mftenv-object-target-list           env) nil)
    (setf (mftenv-resource-target-list         env) nil)
    (mfg-add-targets-recursively-to-env 'all              ;fill the lists
					'dum
					env)
    (setf (mftenv-dummy-target-list env)                  ;sort the lists
	  (cons
	    (car (mftenv-dummy-target-list env))
	    (sort (cdr (mftenv-dummy-target-list env)) #'rdb-lessp)))
    (setf (mftenv-resource-target-list env)
	  (sort (mftenv-resource-target-list env) #'rdb-lessp))
    (setf (mftenv-variable-target-list env)
	  (sort (mftenv-variable-target-list env) #'rdb-lessp))
    (setf (mftenv-executable-target-list env)
	  (sort (mftenv-executable-target-list env) #'rdb-lessp))
    (setf (mftenv-dll-executable-target-list env)
	  (sort (mftenv-dll-executable-target-list env) #'rdb-lessp))
    (setf (mftenv-library-target-list env)
	  (sort (mftenv-library-target-list env) #'rdb-lessp))
    (setf (mftenv-dll-library-target-list env)
	  (sort (mftenv-dll-library-target-list env) #'rdb-lessp))
    (setf (mftenv-shared-object-target-list env)
	  (sort (mftenv-shared-object-target-list env) #'rdb-lessp))
    (setf (mftenv-nonlocal-library-target-list env)
	  (sort (mftenv-nonlocal-library-target-list env) #'rdb-lessp))
    (setf (mftenv-nonlocal-object-target-list env)
	  (sort (mftenv-nonlocal-object-target-list env) #'rdb-lessp))
    (setf (mftenv-object-target-list env)
	  (sort (mftenv-object-target-list env) #'rdb-lessp))))




;;; function: mfg-add-targets-recursively-to-env
;;; arguments:
;;;   target: the name of the target to be added
;;;   type: the type of the target
;;;   env: the mftenv structure passed to template functions
;;; return value: nil
;;; side effects: nconcs entries onto env's dummy-target-list,
;;;   executable-target-list, library-target-list, object-target-list, etc.
;;; description: This adds a target to the appropriate list of env,
;;;   then recursively invokes the function for each dependency.  The function
;;;   returns immediately if the type is irrelevant or if the target is
;;;   already in the list. If the type is object, it is added to the object
;;;   list, but no further dependencies are sought.  For types that might
;;;   depend on other targets, their dependencies are sought, and for local
;;;   dependencies, this function is invoked recursively.  Non-local
;;;   dependencies are ignored, except libraries, which are added to the env's
;;;   nonlocal-library list.
;;; modifications:
;;;     jv, 6/19/96: added shared objects.  Changed the nested if statement
;;;   at the bottom of the code into a cond statement.  I believe it makes
;;;   the code easier to understand, especially at a glance.  Also, it
;;;   reduces the amount of indentation and allows for nil to be explicitly
;;;   returned in the (presumably erroneous) case in which the dependency
;;;   is not local but is also not defined in the nonlocal relations list.
;;; scope: internal

(defun mfg-add-targets-recursively-to-env (target type env)
  (if (member type '(dum var exe dexe lib dlib obj dso res)) ; ignore others
      (let*
	  ((target-list (case type
			  (dum  (mftenv-dummy-target-list env))
			  (var  (mftenv-variable-target-list env))
			  (lib  (mftenv-library-target-list env))
			  (dlib (mftenv-dll-library-target-list env))
			  (dso  (mftenv-shared-object-target-list env))
			  (exe  (mftenv-executable-target-list env))
			  (dexe (mftenv-dll-executable-target-list env))
			  (res  (mftenv-resource-target-list env))
			  (obj  (mftenv-object-target-list env)))))
	(if (not (member target target-list))           ; ignore duplicates
	    (progn
	      (setf target-list        ; add new target to appropriate list
		    (if target-list
			(nconc target-list (list target))
			(list target)))
	      (case type               ; and store list back in env
		(dum
		 (setf (mftenv-dummy-target-list env) target-list))
		(var
		 (setf (mftenv-variable-target-list env) target-list))
		(res
		 (setf (mftenv-resource-target-list env) target-list))
		(lib
		 (setf (mftenv-library-target-list env) target-list))
		(dlib
		 (setf (mftenv-dll-library-target-list env) target-list))
		(dso
		 (setf (mftenv-shared-object-target-list env) target-list))
		(exe
		 (setf (mftenv-executable-target-list env) target-list))
		(dexe
		 (setf (mftenv-dll-executable-target-list env) target-list))
		(obj
		 (setf (mftenv-object-target-list env) target-list))) 
	      (loop                   ;Process recursive dependencies.
		with dependency-view
		= (mftenv-dependency-view env)
		with dependency-index
		= (rdb-attribute-to-index 'dependency dependency-view)
		with dependency-type-index
		= (rdb-attribute-to-index 'dependency-type dependency-view)
		with local-index
		= (rdb-attribute-to-index 'local dependency-view)
		with platform-group-priority-view
		= (mftenv-platform-group-priority-view env)
		with target-group-priority-view
		= (mfg-create-target-group-priority-view
		    target
		    type)
		with target-dependency-view
		= (mfg-select-all-platform-target-group-rows
		    target-group-priority-view
		    platform-group-priority-view
		    dependency-view)
		for table-tail on (rdb-table target-dependency-view)
		for row = (car table-tail)
		for local = (nth local-index row)
		for dependency-type = (nth dependency-type-index row)
		for dependency = (nth dependency-index row)
		do
		(cond
		  ((eq local 'y)
		   (mfg-add-targets-recursively-to-env dependency
						       dependency-type
						       env))
                  ; deal with nonlocal libraries
		  ((eq dependency-type 'lib)
		   (cond
		     ((null (mftenv-nonlocal-library-target-list env))
		      (setf (mftenv-nonlocal-library-target-list env)
			    (list dependency)))
		     ((member dependency
			      (mftenv-nonlocal-library-target-list env))
		      nil)
		     (t
		      (nconc (mftenv-nonlocal-library-target-list env)
			     (list dependency)))))
		  ((eq dependency-type 'dso)
		   (cond
		     ((null (mftenv-nonlocal-object-target-list env))
		      (setf (mftenv-nonlocal-object-target-list env)
			    (list dependency)))
		     ((member dependency
			      (mftenv-nonlocal-object-target-list env))
		      nil)
		     (t
		      (nconc (mftenv-nonlocal-object-target-list env)
			     (list dependency)))))
		  (t
		   nil))
		))))))




;;; function: mfg-establish-command-options-view
;;; arguments:
;;;   product: any product as defined in products-relation, e.g. g2, ext
;;;   compile-category: optimize, debug, mt-debug, profile, or optimize-intc
;;;   platform-group-priority-view: table of groups and priorities of current
;;;     platform
;;; return value: a relation containing relevant command-options rows
;;; description: This performs a preselection on command-options-relation
;;;   to isolate rows that are relevant for the particular product,
;;;   compile-category, and platform.  First, all rows that match on both
;;;   a product-group and platform-group are selected.  From these, rows
;;;   are selected whose compile-category field is either _all or the value
;;;   of the compile-category argument.  Finally, a projection is done so that
;;;   only needed columns are retained.

(defun mfg-establish-command-options-view (product-group-priority-view
					    compile-category
					    platform-group-priority-view)
  (let*
      ((compile-abbrev
	 (case compile-category
	     (optimize 'opt)
	     (debug    'dbg)
	     (mt-debug 'dbg-mt)
	     (optimize-intc 'opt-intc)
	     (profile  'prf)
	     (t   (error "Unknown compile category ~a."
			 compile-category))))
       (command-options-relation
	 (mfg-database 'command-options-relation)))
    (rdb-project-relation
      (remove 'compile-category
	      (remove 'product-group
		      (rdb-attributes command-options-relation)))
      (rdb-select-rows-with-or
	(list (list
		(list '_all compile-abbrev)
		'compile-category))
	(mfg-select-all-platform-product-group-rows
	  product-group-priority-view
	  platform-group-priority-view
	  command-options-relation)))))




;;; function: mfg-establish-local-location-view
;;; arguments:
;;;   product-group-priority-view: for the current product
;;; return value: a relation containing relevant rows for local locations
;;; description: This performs a preselection on local-location-relation
;;;   to isolate rows that are relevant for the particular product.
;;;   All rows that match on a product-group are selected then a projection
;;;   is done so that only needed columns are retained.

(defun mfg-establish-local-location-view (product-group-priority-view)
  (let*
      ((local-location-relation
	 (mfg-database 'local-location-relation)))
    (rdb-project-relation
      (remove 'product-group
	      (rdb-attributes local-location-relation))
      (mfg-select-all-group-rows
	'product-group
	product-group-priority-view
	local-location-relation))))




;;; function: mfg-establish-nonlocal-location-view
;;; arguments:
;;;   product: any product as defined in products-relation, e.g. g2, ext
;;;   platform-group-priority-view: table of groups and priorities of current
;;;     platform
;;; return value: a relation containing relevant rows for nonlocal locations
;;; description: This performs a preselection on nonlocal-location-relation
;;;   to isolate rows that are relevant for the particular product and
;;;   platform.  First, all rows that match on both a product-group and
;;;   platform-group are selected.  Then a projection is done so that only
;;;   needed columns are retained.

(defun mfg-establish-nonlocal-location-view (product-group-priority-view
					      platform-group-priority-view)
  (let*
      ((nonlocal-location-relation
	 (mfg-database 'nonlocal-location-relation)))
    (rdb-project-relation
      (remove 'product-group
	      (rdb-attributes nonlocal-location-relation))
      (mfg-select-all-platform-product-group-rows
	product-group-priority-view
	platform-group-priority-view
	nonlocal-location-relation))))




;;; function: mfg-establish-install-destination-relation
;;; arguments:
;;;   product: any product as defined in products-relation, e.g. g2, ext
;;;   compile-category: optimize, debug, or profile
;;; return value:  the install-destination-relation if there is one, else nil
;;; description: Use template-meta-relation to determine whether a product
;;;   and compile type has an install target, and if so, extract the
;;;   install-destination relation name from it, then return the relation.
;;;   If not, return nil.

(defun mfg-establish-install-destination-relation (product
						compile-category)
    	 (if (eq            ; if the makefile has an install target
	       'y
	       (rdb-select-row-value
		 'install-target
		 (list
		   (list product 'product)
		   (list compile-category 'compile-category))
		 (mfg-database 'template-meta-relation)))
	     (let       ; then find the name of destination relation
		 ((relation-name
		    (cond    
		      ((rdb-select-row-value
			 'install-destination-relation-name
			 (list
			   (list product 'product))
			 (mfg-database 'install-destination-meta-relation)))
		      ((rdb-select-row-value
			 'install-destination-relation-name
			 (list
			   (list '_all 'product))
			 (mfg-database 'install-destination-meta-relation))))))
	       (mfg-database relation-name)) ; and return the relation
	     nil)) ; otherwise return an empty relation




;;; function: mfg-establish-install-rename-view
;;; arguments:
;;;    product-group-priority-view: for the product
;;; return value:  the install-rename-relation with relevant product rows
;;; description:  Preselects all rows of install-rename-relation for which the
;;;   product is a member of a product group.  A projection is then done so
;;;   that only needed columns are retained.

(defun mfg-establish-install-rename-view (product-group-priority-view)
  (let*
      ((install-rename-relation
	 (mfg-database 'install-rename-relation)))
    (rdb-project-relation
      (remove 'product-group
	      (rdb-attributes install-rename-relation))
      (mfg-select-all-group-rows
	'product-group
	product-group-priority-view
	install-rename-relation))))




;;; function: mfg-deduce-nonstandard-object-list
;;; arguments:
;;;   command-options-view: command options for product and compile-type
;;;   platform-group-priority-view: groups and priorities of current platform
;;; return value: a list of objects likely to have a non-default makefile entry
;;; description: This function processes command-options-view to produce a
;;;   list of targets likely to require special compilation options.
;;; notes:
;;;     The word "likely" is used because all relevant groups are included
;;;   rather than only the highest priority group for each option, which would
;;;   be very difficult to select exactly.  First, rows for all relevant
;;;   compilation categories are selected, then rows for all relevant platform
;;;   groups. From this, the target groups column is selected. This contains
;;;   both target groups and individual file names. The column is joined with
;;;   target-groups-relation to obtain all target names associated with the
;;;   target-groups. A list of targets is formed by combining names from both
;;;   the original target groups and the target names. The former is needed to
;;;   account for individual file names
;;;     There is no harm to makefiles if standard object names are
;;;   included.  Although slightly more processing time is required, the
;;;   resultant makefile entry is the same.  There is also no harm in
;;;   leaving target group names or _all in the list, since they never
;;;   match a target.
;;; scope: internal

(defun mfg-deduce-nonstandard-object-list (command-options-view
					    platform-group-priority-view)
  (let*
      ;; obtain target-groups for any possible platform options
      ((all-target-view
	 (rdb-project-relation
	   '(target-group)
	   (rdb-join-relations
	     '((group platform-group))
	     platform-group-priority-view
	     (rdb-select-rows-with-or
	       '(((cc-odp general-cc-odp cc general-cc ipath general-ipath )
		  option-category))
	       command-options-view)))))
    (rdb-column-to-list
      'target-group
      ;; remove any duplicate names
      (rdb-delete-adjacent-duplicate-rows
	'(target-group)
	(rdb-sort-relation
	  '(target-group)
	  (rdb-append-table-to-relation
	    (rdb-table   
	      (rdb-project-relation
		'(group-member)
		;; find all group members for the relevant target-groups
		(rdb-join-relations
		  '((target-group group))
		  all-target-view
		  (mfg-database 'target-groups-relation))))
	    all-target-view))))))




;;; function: mfg-establish-env
;;; arguments:
;;;   platform: the platform for which the makefile is to be made
;;;   compile-category: optimize, debug, or profile
;;;   product: any product as defined in products-relation, e.g. g2, ext
;;;   dependency-view: the view containing dependencies for the product
;;; return value: a new mftenv structure initialized for the platform
;;; description: This function sets up the environment needed by template
;;;   functions of a standard makefile..
;;; scope: internal

(defun mfg-establish-env (platform
			   compile-category
			   product
			   dependency-view)
  (let*
      ((pgp-view
	 (mfg-create-group-priority-view
	   platform
	   (mfg-database 'platform-groups-relation)
	   (mfg-database 'platform-group-priorities-relation)))
       (product-group-priority-view
	 (mfg-create-group-priority-view
	   product
	   (mfg-database 'product-groups-relation)
	   (mfg-database 'product-group-priorities-relation)))
       (operating-system
	 (mfg-establish-operating-system pgp-view))
       (command-options-view
	 (mfg-establish-command-options-view
	   product-group-priority-view compile-category pgp-view)) 
       (local-location-view
	 (mfg-establish-local-location-view
	   product-group-priority-view))       
       (nonlocal-location-view
	 (mfg-establish-nonlocal-location-view
	   product-group-priority-view pgp-view))
       (env (make-mftenv
	      :platform platform
	      :compile-category compile-category
	      :platform-group-priority-view pgp-view
	      :product product
	      :product-group-priority-view product-group-priority-view
	      :operating-system operating-system
	      :variable-value-view
	      (mfg-establish-variable-value-view
		platform
		compile-category
		product-group-priority-view
		pgp-view)
	      ;; the following needs differentiation
	      :dependency-view dependency-view
	      :command-options-view command-options-view
	      :local-location-view local-location-view
	      :nonlocal-location-view nonlocal-location-view
	      :compile-command (mfg-select-command 'compile pgp-view)
	      :objects-per-command
	      (mfg-select-highest-priority-group-value
		'limit
		'platform-group
		pgp-view
		(mfg-database 'objects-per-command-relation))
	      :nonstandard-objects-list
	      (mfg-deduce-nonstandard-object-list
		command-options-view
		pgp-view)
	      :object-default-replacement
	      (rdb-select-row-value
		'default-replacement
		(list
		  (list product 'product))
		(mfg-database 'object-default-entry-relation))
	      :directory-delimiter (mfg-directory-delimiter operating-system)
	      :current-dir "$(MFDIR)"))
       (install-destination-relation
	 (mfg-establish-install-destination-relation
	   product
	   compile-category)))
    (if install-destination-relation  ; existence indicates install target,
				      ; so set needed fields
	(progn
	  (setf (mftinstall-destination-view (mftenv-install-slots env))
		install-destination-relation)
	  (setf (mftinstall-install-rename-view (mftenv-install-slots env))
		(mfg-establish-install-rename-view
		  product-group-priority-view))))
    ;; return the env that has been set up
    env))






;;;; Functions for Makefile Creation
;;;      The functions in this section provide the means to generate
;;;    a single makefile.  The function mfg-generate-standard-makefile
;;;    does the work to set up the environment, invoke mfg-process-template
;;;    with the initial template, and format the makefile. The function
;;;    mfg-generate-standard-makefile-to-file serves simply to redirect
;;;    output to a file.  mfg-determine-starting-template-name determines
;;;    where to initiate template processing.




;;; function: mfg-determine-starting-template-name
;;; return value: the symbol that is the name of the starting template
;;; description:  Determines starting template for makefile generation.
;;; notes:  This selects the product and compile-category fields of the
;;;   relation and looks for a direct match.  If none is found, the
;;;   _all/_all value is returned.  See template-meta-relation.

(defun mfg-determine-starting-template-name (product
					      compile-category
					      template-meta-relation)
  (cond
    ((rdb-select-row-value
       'starting-template
       (list
	 (list product 'product)
	 (list compile-category 'compile-category))
       template-meta-relation))
     ((rdb-select-row-value
       'starting-template
       (list
	 (list '_all 'product)
	 (list '_all 'compile-category))
       template-meta-relation))))




;;; function: mfg-generate-standard-makefile
;;; arguments:
;;;   platform: the platform for which the makefile is to be made
;;;   compile-category: optimize, debug, or profile
;;;   product: any product as defined in products-relation, e.g. g2, ext
;;;   dependency-view: the view containing dependencies for the product
;;; return value: nil
;;; description: This function sets up the environment needed to produce a
;;;   standard makefile for the given parameters.  It then commences
;;;   processing the standard template in the environment.  The makefile body
;;;   is captured as a string while variable ("macro") definitions are added
;;;   through side effects to the variable-value-view slot of env.  The
;;;   variable definitions are then printed before the makefile body.
;;; notes: For debugging, it may be useful to replace the assignment to
;;;   makefile-body by the three commented-out lines below it.  This allows
;;;   standard output to be as it is produced.  Note that for this function
;;;   to be called directly, dependency-view is needed, which can be created
;;;   with mfg-set-up-dependency-view.
;;; scope: internal

(defun mfg-generate-standard-makefile (platform
					compile-category
					product
					dependency-view)
  (let*
      ((env
	 (mfg-establish-env platform compile-category product dependency-view))
       (template
	 (mfg-select-template
	   (mfg-determine-starting-template-name
	     product
	     compile-category
	     (mfg-database 'template-meta-relation))
	   (mftenv-product-group-priority-view env)
	   (mftenv-platform-group-priority-view env)))
       (makefile-body
	 (with-output-to-string
	     (*standard-output*) 
	   (mfg-establish-targets env)
	   (mfg-process-template template env))))
     ;; see function notes above
     ;;(makefile-body "")
     ;;(mfg-establish-targets env)
     ;;(mfg-process-template template env)
    (mfg-print-variable-definitions (mftenv-variable-value-view env))
    (write-string makefile-body)
    ))




;;; function: mfg-generate-standard-makefile-to-file
;;; arguments:
;;;   platform: the platform for which the makefile is to be made
;;;   compile-category: optimize, debug, or profile
;;;   product: any product as defined in products-relation, e.g. g2, ext
;;;   dependency-view: the view containing dependencies for the product
;;;   filename: the path and filename for the generated file
;;; return value: nil
;;; description: This is a wrapper around mfg-generate-standard-makefile
;;;   that directs the output to the specified file.
;;; scope: internal

(defun mfg-generate-standard-makefile-to-file (platform
						compile-category
						product
						dependency-view
						filename)
  (with-open-file
      (*standard-output* filename :direction :output
			 :if-does-not-exist :create
			 :if-exists :supersede)
      (mfg-generate-standard-makefile
	platform compile-category product dependency-view)))



;;; function: mfg-note-inability-to-generate-makefile-to-file
;;; arguments:
;;;   filename: the path and filename for the makefile
;;; return value: nil
;;; description: If we don't have the information to properly generate a
;;;   makefile, we append a note at the end to the existing makefile
;;;   indicating that we were unable to re-generate it.
;;; scope: internal

(defun mfg-note-inability-to-generate-makefile-to-file (filename)
  (with-open-file
      (*standard-output* filename :direction :output
			 :if-does-not-exist :create
			 :if-exists :supersede)
    (format t "~%~%# Warning: makefile generator unable to find dependencies")
    (format t " for this makefile.~%~%")))






;;;; Utility Functions for User Interface
;;;      The functions in this section are called for services directly by
;;;    mfg-generate-makefiles-for-build, which is the user interface
;;;    for makefile generation.  Many of the functions exist merely
;;;    to augment the product dependency relation with new rows. The
;;;    rows are generated from a list of names in the file
;;;    <SRCBOX>/<product>/c/<product>-files.txt, which is
;;;    produced by the Lisp-to-C translator.




;;; function: mfg-file-to-list
;;; arguments:
;;;   filename: a filename as a string
;;; return value: the tokens of the file in a list
;;; description: Reads the file as a stream of tokens, stores them in a list,
;;;   and returns the list
;;; scope: internal

(defun mfg-file-to-list (filename)
  (cond
    ((probe-file filename)
     (with-open-file (v filename)
       (loop
	 for token = (read v nil :eof)
	 until (eq token :eof)
	 collect token)))
    (t
     (warn "Could not locate file ~s." filename)
     (format t "You need to check out that module if you want to be able to~%")
     (format t "  properly generate a makefile for it.~%"))))




;;; function: mfg-create-dependency-table
;;; arguments:
;;;   product: any product as defined in products-relation, e.g. g2, ext
;;;   dependency-template-view: the dependency-template-relation
;;; return value: A table of new dependencies derived from <product>-
;;;   files.txt and the templates in dependency-template-relation.
;;;   The dependencies are formed by creating rows for each name in
;;;   the text file and each row template for the product.

(defun mfg-create-dependency-table (product dependency-template-view)
  (loop
    with filename = (format nil "~(~a/~a/c/~a-files.txt~)"
			    SRCBOX product product)
    with filelist = (mfg-file-to-list filename)
    with files-to-omit = (rdb-column-to-list
			   'file-to-omit
			   (mfg-database 'translator-dependency-omit-relation))
    with omit-if-listed-index = (rdb-attribute-to-index
				  'omit-if-listed dependency-template-view)
    with row-template-index = (rdb-attribute-to-index
				'row-template dependency-template-view) 
    for row in (rdb-table
		 (rdb-select-rows
		   (list
		     (list product 'product))
		   dependency-template-view))
    for omit-it = (eq (nth omit-if-listed-index row) 'y)
    for row-template = (nth row-template-index row)
    nconc
    (loop
      for name in filelist
      unless  (and omit-it (member name files-to-omit))
	collect (subst name 'name-from-file row-template))))




;;; function: mfg-load-dependency-view
;;; arguments:
;;;   product: any product as defined in products-relation, e.g. g2, ext
;;; return value: none
;;;   side effect: sets <product>-dependency-relation
;;; description: This determines which file in which the desired dependency
;;;   relation resides, then loads it.
;;; notes:  If the file name is given in dependency-product-relation,
;;;   it is used.  If not, the file name is assumed to be <product>-
;;;   dependencies.rel

(defun mfg-load-dependency-view (product)
  (let
      ((filename
	 (rdb-select-row-value
	   'dependency-file
	   (list
	     (list product 'product))
	   (mfg-database 'dependency-file-relation))))
    (if filename
	(load filename)
	(load
	  (format nil "~(~a-dependencies.rel~)" product)))))




;;; function: mfg-set-up-dependency-view
;;; arguments:
;;;   product: any product as defined in products-relation, e.g. g2, ext
;;; return value: a relation containing dependencies for the given product
;;; description: This determines or sets up the dependency relation for the
;;;   given product.  In the case of translated products such as g2, tw, and
;;;   gsi, some rows of the dependency relation are produced by reading data
;;;   files emitted during translation.
;;; notes: See dependency-row-template-relation.

(defun mfg-set-up-dependency-view (product)
  (let
      ((dependency-view
	 (mfg-database
	   (intern (format nil "~a-DEPENDENCY-RELATION" product))))
       (dependency-template-view
	 (mfg-database 'dependency-row-template-relation)))
    (if (rdb-select-row-value  ; if the file has a *-files.txt file
	  'product
	  (list
	    (list product 'product))
	  dependency-template-view)
	(let ((dependency-table
	       (mfg-create-dependency-table
		product
		dependency-template-view)))
	  (and dependency-table
	       (rdb-append-table-to-relation
		dependency-table
		dependency-view)))
	dependency-view)))




;;; function: mfg-load-and-set-up-dependency-view
;;; arguments:
;;;   product: any product as defined in products-relation, e.g. g2, ext
;;; return value: a relation containing dependencies for the given product
;;; description: As the name indicates, this loads the file that defines
;;;   the dependency relation, then performs addition processing of it..

(defun mfg-load-and-set-up-dependency-view (product)
  (mfg-load-dependency-view product)
  (mfg-set-up-dependency-view product))




;;; function: mfg-bind-special-symbols
;;; arguments: none
;;; return value: nil
;;; description: This function checks whether the special symbol SRCBOX is
;;;   bound, which it should be.  If not, a warning message is printed and
;;;   SRCBOX is bound to /bt/ab

(defun mfg-bind-special-symbols ()
   (if (not (boundp 'srcbox))
       (progn
	 (setq SRCBOX "/bt/ab")
	 (format t
		 "mfg: Warning: SRCBOX was not bound. Using default /bt/ab"))))




;;; function: mfg-create-makefile-path-and-name
;;; arguments:
;;;   compile-category: optimize, debug, mt-debug, profile, or optimize-intc
;;;   product: the product to be made
;;;   platform: the platform on which it is to be made
;;; return value: a string containing the full path and expected filename
;;;   for the product makefile
;;; description: This yields the standard path and filename for the
;;;   generated makefile.
;;; scope: internal

(defun mfg-create-makefile-path-and-name (compile-category product platform)
  (let*
      ((path "../mfiles/")
       (compile-suffix
	 (case compile-category
	   (optimize 'opt)
	   (debug    'o  )
	   (mt-debug 'o-mt)
	   (profile  'o-pg)
	   (optimize-intc 'opt-intc)
	   (t 'bad_category))))
	(format nil "~(~a~a-~a-~a~)" path platform product compile-suffix)))




;;; function: mfg-load-database
;;; arguments: none
;;; return value: none
;;; description:  This loads the basic relations that constitute the
;;;   makefile database.
;;; notes:  In the future, it would be nice to pass as an argument the
;;;   path in which these files are found.

(defun mfg-load-database ()
  (load "config.rel")
  (load "groups.rel")
  (load "commands-and-options.rel")
  (load "templates.rel"))





;;;; User Interface
;;;      This section contains only the single function below.  It is the
;;;    only Lisp function that should be called by a user.




;;; function: mfg-generate-makefiles-for-build
;;; arguments:
;;;   argument-list: a list of products, platforms, and/or compilation
;;;     categories for which makefiles are to be built. Compilation categories
;;;     are   optimize, debug, or profile
;;; return value: nil
;;; description: This generates makefiles for the listed products, compilation
;;;   categories, and platforms.  If no specific products, platforms, or
;;;   compilation categories are given, a default list of all available
;;;   types is used.  For example, if none of the compilation categories
;;;   optimize, debug, or profile appears, then all 3 are used by default.
;;;   Default products are determined from products-relation and default
;;;   platforms are determined from platform-makefiles-relation.
;;;   For a makefile to be created for a given platform and compilation
;;;   category, there must be a 'y' in the appropriate field of platform-
;;;   makefiles-relation.
;;; notes:  If a specified makefile is not generated for a given product,
;;;   category, and platform, it's probably because there is no 'y' in the
;;;   category field of platform-makefiles-relation.  Note, in particular,
;;;   that the mt-debug compile category is only usable, working order
;;;   for a limited number of platforms and products; at this time (8/3/01),
;;;   only for platform = sparcsol, and product = ext, rtl, gsi, and then
;;;   only for the purpose of linking with jgi c code.
;;; Similarly, the optimize-intc category is only for the intel compiler on NT.
;;; scope: external

(defun mfg-generate-makefiles-for-build (&optional argument-list)
  (mfg-load-database)
  (let*
      ;;Uncomment optimize-intc to generate files for intel compiler.
      ((available-categories '(optimize debug mt-debug profile optimize-intc))
       (available-products
	 (rdb-column-to-list
	   'product
	   (mfg-database 'products-relation)))
       (available-platforms
	 (rdb-column-to-list
	   'platform
	   (mfg-database 'platform-makefiles-relation)))
       (tmp-product-list
	 (intersection available-products argument-list))
       (product-list
	 (if tmp-product-list tmp-product-list available-products))
       (tmp-category-list
	 (intersection available-categories argument-list))
       (category-list
	 (if tmp-category-list tmp-category-list available-categories))
       (tmp-platform-list
	 (intersection available-platforms argument-list))
       (platform-list
	 (if tmp-platform-list tmp-platform-list available-platforms)))
    (mfg-bind-special-symbols)        ; set up default SRCBOX if necessary
    ;; Determine and print warnings for all illegal arguments
    (loop
      for illegal-argument in (set-difference
				argument-list
				(append
				  product-list
				  category-list
				  platform-list))
      do
      (format t "mfg: Warning: Ignoring unrecognized argument ~a~%"
	      illegal-argument))
    ;; Iterate over all products, categories, and platforms to create makefiles
    (loop
      for product in product-list
      for dependency-view = (mfg-load-and-set-up-dependency-view product)
      do
      (loop
	for compile-category in category-list
	;; Obtain the list of platforms active for the given compile-category
	for platform-category-list
	= (rdb-column-to-list
	    'platform
	    (rdb-select-rows
	      (list (list 'y compile-category))
	      (mfg-database 'platform-makefiles-relation)))
	do
	(loop
	  ;; The intersection below restricts generation of makefiles
	  ;; to compile categories that are active for the platform
	  for platform in (intersection platform-list platform-category-list)
	  for filename = (mfg-create-makefile-path-and-name
			   compile-category
			   product platform)
	  do
	  (cond
	    (dependency-view
	     (format t "mfg: generating ~a~%" filename)
	     (mfg-generate-standard-makefile-to-file
	      platform compile-category product dependency-view filename))
	    (t
	     (format t "mfg: unable to generate ~a~%" filename)
	     (mfg-note-inability-to-generate-makefile-to-file filename))))))))





;;;; Utility Functions for Manual Use and Debugging
;;;      The functions in this section are conveniences for debugging and
;;;    should be used only by those with an understanding of the internal
;;;    system structure.




;;; function: all-of
;;; arguments:
;;;   some-tree: any s-expression, but assumed to be a long, nested list
;;;   fresh-line-p: whether or not to precede the output with a fresh-line
;;;   circle-p: passed directly to #'write as :circle
;;; return value: no values
;;; description: prints the first argument in a highly readable form
;;; note: for debugging use only; note the absence of the suffix mfg-
;;; scope: external

(defun all-of (some-tree &optional (fresh-line-p t) (circle-p nil))
  (let ((*standard-output* *terminal-io*))
    (when fresh-line-p
      (fresh-line))
    (let ((*print-case* :downcase)
	  (*print-level* 30)
	  (*print-length* 1000)
	  #+lucid (lcl:*debug-print-level* 30)
	  #+lucid (lcl:*debug-print-length* 1000))
      (write some-tree :pretty t :circle circle-p))
    (fresh-line)
    (values)))


;;; function: show-options
;;; arguments:
;;;   option-category: cc, link, make, lib, libpath, ipath
;;;   platform: a valid platform
;;;   :target: a valid target; if not present, 'dummyname' is used, which
;;;      will give default options since it should never be a valid target
;;;   :target-type: a valid target type; if not present, this is deduced
;;;      from  "option-category"
;;;   :compile-category: optimize, debug, or profile; default is 'optimize'
;;;   :product: any product as defined in products-relation, e.g. g2, ext;
;;;      default is 'ext'
;;; description: Used for debugging and examining options. Lists the options
;;;   for the given option-category and platform in the order.  The options
;;;   appear separated by spaces.  The default values have been chosen to
;;;   provide results with minimal parameters.
;;; notes: no attempt is made to format the options for the given platform,
;;;   since formatting is indicated explicitly by the template.  If this
;;;   command is used frequently, a Lisp wrapper can be thrown together in the
;;;   interpreter.  This has the unfortunate behavior of returning a variable
;;;   name and not its value when a variable name would be used.
;;; scope: internal

(defun show-options (option-category
		      platform
		      &key
		      (target 'dummytarget)
		      target-type
		      (compile-category 'optimize)
		      (product 'ext))
  (mfg-load-database)
  (let*
      ((env
	 (mfg-establish-env
	   platform
	   compile-category
	   product
	   (mfg-load-and-set-up-dependency-view product))) 
       (type
	 (if target-type
	     target-type 
	     (case option-category
	       (cc 'obj)
	       (link 'exe)
	       (make 'lib)
	       (libpath 'exe)
	       (install 'exe)
	       (chmod 'exe)
	       (ipath 'obj)
	       (t (progn
		    (format t "Assuming target-type obj.")
		    'obj))))))
    (setf (mftenv-target env) target)
    (setf (mftenv-target-type env) type)
    (setf (mftenv-target-group-priority-view env)
	  (mfg-create-target-group-priority-view
	    target
	    type))
    (format t "~a"
	    (mfg-select-command-options-to-string
	      option-category
	      (intern (format nil "GENERAL-~a" option-category))
	      #'mfg-print-list-with-space-separators
	      env))))





;;; function: generate-single-makefile
;;; arguments:
;;;   product: a legal product name
;;;   platform: a legal platform name
;;;   :filename: makefile path and name to write to (optional)
;;;   :category: optimize, profile, or debug (optional)
;;; return value: nil
;;; description: For the given parameters, this generates an makefile with
;;;   the proper name in the mfiles directory. The name can be specified
;;;   explicitly
;;; note: this is purely for convenience; note the absence of the suffix mfg-
;;; scope: external

(defun generate-single-makefile (product
				  platform
				  &key
				  filename
				  (category 'optimize))
  (mfg-bind-special-symbols)
  (let
      ((filename-to-use
	 (if filename
	     filename
	     (mfg-create-makefile-path-and-name category product platform))))
    (format t "generating ~a~%" filename-to-use)
    (mfg-generate-standard-makefile-to-file
      platform
      category
      product
      (mfg-set-up-dependency-view product)
      filename-to-use)))

;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module PATHNAMES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved

;;; John Hodgkinson

;; 8 Oct 1990

;; jh, 6/25/91.  Split off the filename-parsing and generating portion of this
;; module, now called FILE-PARSE.



;;;; Reclaimable Pathname Facility

;; jh, 10/8/90.

;;; The idea is to duplicate the basic functionality of Common Lisp pathnames, but
;;; provide a means of reclaiming pathname objects.  This will prevent the leaks
;;; that occur when Common Lisp simply drops a pathname or pathname-related string
;;; (like a true-namestring).  The following analogues are currently (12/3/90)
;;; implemented:

;;; gensym function/macro             Common Lisp analogue         CltL/2e ref
;;; ---------------------             --------------------         -----------
;;; gensym-default-pathname-defaults  *default-pathname-defaults*  642
;;; reclaim-gensym-pathname              -                          -
;;; gensym-make-pathname              make-pathname                643-44
;;; copy-gensym-pathname                 -                          -
;;; gensym-pathnames-equal-p          equal                        107 (re pathnames)
;;; gensym-probe-file                 probe-file                   654
;;; gensym-probe-file-for-write          -                          -
;;; handling-gensym-file-errors          -                          -
;;; ignoring-gensym-file-errors          -                          -
;;; gensym-namestring                 namestring                   644-45
;;; gensym-enough-namestring          enough-namestring            644-5
;;; gensym-file-namestring            file-namestring              644-45
;;; gensym-directory-namestring       directory-namestring         644-45
;;; gensym-host-namestring            host-namestring              644-45
;;; gensym-pathname                   pathname                     638-39
;;; gensym-directory-as-file             -                          -
;;; gensym-file-as-directory             -                          -
;;; gensym-parse-namestring           parse-namestring             639-40
;;; gensym-truename                   truename                     639
;;; gensym-merge-pathnames            merge-pathnames              641
;;; gensym-directory                  directory                    663
;;; gensym-subdirectories                -                          -
;;; gensym-rename-file                rename-file                  653
;;; gensym-delete-file                delete-file                  653-54
;;; valid-pathname-p                     -                         (punts on p 642)
;;; valid-directory-p                    -                          -
;;; with-file-search-path                -                          -
;;; gensym-wild-pathname-p            wild-pathname-p              623
;;; gensym-maximum-file-name-length      -                          -
;;; gensym-pathname-host              pathname-host                644
;;; gensym-pathname-device            pathname-device              644
;;; gensym-pathname-directory         pathname-directory           644
;;; gensym-pathname-name              pathname-name                644
;;; gensym-pathname-type              pathname-type                644
;;; gensym-pathname-version           pathname-version             644
;;; gensym-pathname-p                 pathnamep                    643


;;; The naming template is gensym-xxx, where xxx is the name of the Common Lisp
;;; analogue function.  Where no analogue exists, the nomenclature follows
;;; internal gensym guidelines, e.g., reclaim-gensym-pathname.

;; On Lisp Machines, Common Lisp pathnames are used in the underlying mechanism of
;; the Common Lisp analogue functions.  Leaks occur with this mechanism, but will
;; be restricted to non-standard platforms, i.e., Lisp Machines.  All other
;; platforms are guaranteed 100% recyclable.  Note that, regardless of platform,
;; the Gensym Common Lisp analogues are defined and have the same argument and
;; return types, namely text-strings, g2-pathnames, or nil.  The only thing that
;; changes is their consing behavior.  jh, 12/3/90.





;; Policy: all strings used and returned are reclaimiable text-strings.  All lists
;; (used and returned) are composed of path-conses.  All pathname structures
;; returned from the analogue functions are gensym-pathnames, even when the
;; underlying mechanism uses Lisp pathnames.

(defconser path PATHNAMES)


;;;; Forward References

(declare-forward-references (:suppress-module-checks-for gsi ctest)
  (notify-user                                             function DEBUG)
  (g2-stream-directory                                     function STREAMS)
  (g2-stream-subdirectories                                function STREAMS)
  (g2-stream-get-version                                   function STREAMS)
  (g2-stream-delete-file                                   function STREAMS)
  (g2-stream-rename-file                                   function STREAMS)
  (g2-stream-p                                             function STREAMS)
  (identical-g2-streams-p                                  function STREAMS)
  (all-gensym-pathnames-containing-open-streams            variable STREAMS)
  (g2-stream-get-default-directory                         function STREAMS)
  (g2-stream-get-device                                    function STREAMS)
  (wild-regular-expression-string-p                        function STREAMS)
  (g2-stream-probe-file-for-write                          function STREAMS)
  (g2-stream-open-for-output                               function STREAMS)
  (g2-stream-maximum-file-name-length                      function STREAMS)
  (g2-stream-directory-p                                   function STREAMS)
  (gensym-probe-file                                       function STREAMS)
  (current-kb-pathname?                                    variable KB-LOAD1)
  (file-system-for-interception?                           variable STREAMS)
  (process-specific-system-pathname                        variable STREAMS)
  (most-recently-encountered-file-already-exists-error-p   function STREAMS)
)

(declare-forward-reference g2-stream-close function)



;;;; Static File System Information


;; The constants local-file-system, local-filename-parser, and
;; local-namestring-generator should be the only place where static information
;; about the file system is kept.  All other references should expand into
;; read-time #. macros involving these constants.

;; Changed the constants local-file-system, local-filename-parser, and
;; local-namestring-generator to be macros, since we are coalescing binaries on
;; the explorer and microexplorer and thus can no longer determine the local file
;; system type at compile time.  jh per mhd, 2/8/91.

;; Changed the underlying macroexpansion of local-file-system,
;; local-filename-parser, and local-namestring-generator not to use ifdef-case,
;; which complicates porting to new platforms.  Instead, we determine the local
;; file system at runtime by looking at *features*.  jh, 7/15/91.
;; jh, 2/19/92.  The preceding note has been superseded.  On
;; distribution platforms, we now look at g2-operating-system, which is
;; set up in g2main.c in the translated code.
;; jh, 8/22/94.  The preceding note is out of date.  On distribution platforms,
;; we now look at g2-operating-system, which is set up by a foreign call to
;; c-get-platform-code, which in urn contains the platform-specific code
;; necessary to provide the operating system tag.

(defun initialize-local-file-system ()
  (case g2-operating-system
    (unix        'unix)
    (vms         'vms)
    (dos         'dos)
    (win32       'win32)
    (otherwise 'unix)))

(defvar local-file-system (initialize-local-file-system))

(defmacro local-file-system ()
  `local-file-system)




(defun initialize-local-filename-parser ()
  (case g2-operating-system
    (unix        'parse-unix-filename)
    (vms         'parse-vms-filename)
    (dos         'parse-dos-filename)
    (win32       'parse-win32-filename)
    (otherwise   'parse-unix-filename)))

(defvar local-filename-parser (initialize-local-filename-parser))


(defmacro local-filename-parser ()
  `local-filename-parser)


(defun initialize-local-namestring-generator ()
  (case g2-operating-system
    (unix        'generate-unix-namestring)
    (vms         'generate-vms-namestring)
    (dos         'generate-dos-namestring)
    (win32       'generate-win32-namestring)
    (otherwise   'generate-unix-namestring)))

(defvar local-namestring-generator
  (initialize-local-namestring-generator))


(defmacro local-namestring-generator ()
  `local-namestring-generator)








;; The property convert-file-strings-to-uppercase-p is useful when gensym-pathname
;; structures created "by hand" (i.e., by gensym-make-pathname) are merged with
;; those created by parsing a file's namestring.  This will ensure that the
;; underlying g2-stream operations perform correctly.  Since the g2-stream
;; operations don't process their namestrings before presenting them to the file
;; system, merges involving a home-grown gensym-pathname could result in the wrong
;; character case being used to access a file, with resultant erratic behavior.
;; This property should always be derivable from either the symbol which names the
;; filename parser (e.g., parse-unix-filename) or the symbol naming the namestring
;; generator (e.g., generate-unix-namestring).  jh, 12/11/90.

;; Note that convert-file-strings-to-uppercase-p and
;; gensym-default-pathname-defaults both statically define the default file-system
;; through use of compiler switches.  This is a first pass at solving the pathname
;; equivalence problem above, but probably should be generalized to provide for
;; environments where we need to determine the file system dynamically.  The
;; special variable convert-file-strings-to-uppercase-p is currently bound when
;; gensym-pathnames are created by our pathname functions, providing some dynamic
;; flexibility.  If we wanted more, we would elaborate the function
;; initialize-default-gensym-pathname-defaults, perhaps by having it read from a
;; site file.

(def-global-property-name convert-file-strings-to-uppercase-p)

;; Changed the variable convert-file-strings-to-uppercase-p not to use
;; compile-time read macros.  We are merging explorer and microexplorer binaries
;; and thus can no longer determine the local file system type when we compile.
;; jh per mhd, 2/8/91.

(defun initialize-convert-file-strings-to-uppercase-p ()
  (case (local-file-system)
    (unix          nil)
    (vms           t)
    (dos           t)
    (win32         nil)
    (otherwise     nil)))

(defvar convert-file-strings-to-uppercase-p
  (initialize-convert-file-strings-to-uppercase-p))


  

;;; Gensym-pathname Structure

;;; The gensym-pathname structure contains slots for the Common Lisp pathname
;;; components.  Eventually, it may also contain a wild-p slot, which is true
;;; when the pathname structure does not refer to a single file, and a
;;; cached-truename slot, which contains a canonical namestring for this pathname,
;;; if one is ever computed.  Note that we must take care that both of these slots
;;; are not invalidated by the operating system as G2 works with the pathname.

;; Changed the gensym-pathname slots gensym-pathname-file-system,
;; gensym-pathname-filename-parser, and gensym-pathname-namestring-generator not
;; to use read macros for their initialization specs.  We are merging explorer and
;; microexplorer binaries and thus can no longer determine anything about the
;; local file system type when we compile.  jh per mhd, 2/8/91.

(def-structure (gensym-pathname
		 ;; The print method is not perfected yet.  jh, 10/20/91.
		 ;; -- Obsolete comment?! (MHD 3/13/94)
		 #+development
		 (:print-function print-gensym-pathname-structure)
		 (:constructor make-gensym-pathname-structure-macro
			       (gensym-pathname-host 
				 gensym-pathname-device 
				 gensym-pathname-directory 
				 gensym-pathname-name 
				 gensym-pathname-type 
				 gensym-pathname-version))
		 (:reclaimer reclaim-gensym-pathname-structure-macro))
  (gensym-pathname-host nil)             ;text-string, symbol, or nil
  (gensym-pathname-device nil)           ;text-string, symbol, or nil
  (gensym-pathname-directory nil)        ;list of text-strings and symbols (eg :up)
  (gensym-pathname-name nil)             ;text-string, symbol, or nil
  (gensym-pathname-type nil)             ;text-string, symbol, or nil
  (gensym-pathname-version nil)          ;fixnum, symbol (eg :newest), text-string, or nil
  (gensym-pathname-stream? nil)          ;g2-stream or nil
  (gensym-pathname-file-system           ;symbol of fs used to parse, never nil
    (local-file-system))  
  (gensym-pathname-filename-parser       ;symbol of parsing function, never nil
    (local-filename-parser)) 
  (gensym-pathname-namestring-generator  ;symbol of generator function, never nil
    (local-namestring-generator))
  )





;;; print-gensym-pathname-structure prints gensym-pathname to stream, ignoring the
;;; variable depth, in a host-operating-system-independent (i.e., ignorant)
;;; manner. ...

#+development
(defun print-gensym-pathname-structure (gensym-pathname stream depth)
  (declare (ignore depth))
  (printing-random-object (gensym-pathname stream)
    (let* ((local-filename-parser (initialize-local-filename-parser))
	   (local-namestring-generator (initialize-local-namestring-generator))
	   (local-file-system (initialize-local-file-system))
	   (gensym-namestring (gensym-namestring gensym-pathname)))
      (prog1 (format
	       stream "GP~s"		; ala CL's #P"foo"
	       gensym-namestring)
	(reclaim-text-string gensym-namestring)))))

;; I don't see the problems described here previously anymore.  (Lispm-only
;; problems should be ignored now.)  (MHD 3/13/94)




(defun make-gensym-pathname-structure-function
       (gensym-pathname-host 
	gensym-pathname-device 
	gensym-pathname-directory 
	gensym-pathname-name 
	gensym-pathname-type 
	gensym-pathname-version)
  (make-gensym-pathname-structure-macro
    gensym-pathname-host 
    gensym-pathname-device 
    gensym-pathname-directory 
    gensym-pathname-name 
    gensym-pathname-type 
    gensym-pathname-version))

(defun-simple make-empty-gensym-pathname () 
  (make-gensym-pathname-structure-macro
    nil
    nil
    nil
    nil
    nil
    nil))

#+unused
(defun gensym-pathname-p-function (thing)
  (gensym-pathname-p thing))

;;; gensym-default-pathname-defaults 


(defun initialize-default-gensym-pathname-defaults ()
  (let ((defaults
	  (make-gensym-pathname-structure-function
	    nil 
	    nil 
	    '(:relative) 
	    nil 
	    nil 
	    :newest)))
    (setf (gensym-pathname-file-system defaults)
	  (local-file-system))
    (setf (gensym-pathname-filename-parser defaults)
	  (local-filename-parser))
    (setf (gensym-pathname-namestring-generator defaults)
	  (local-namestring-generator))
    defaults))

(def-system-variable gensym-default-pathname-defaults PATHNAMES
  (:funcall initialize-default-gensym-pathname-defaults) nil t)



;;; reclaim-gensym-pathname


;; With-pathname-components binds gensym-pathname slots to their corresponding
;; accessor names.  It is similar in intent to the CLOS with-slots construct.

(defmacro with-pathname-components ((pathname) &body body)
  (unless (symbolp pathname)
    (error "WITH-PATHNAME-COMPONENTS: pathname form must be a symbol, not ~a"
	   pathname))
  `(let ,(loop for component-identifier
		   in '(gensym-pathname-host
			 gensym-pathname-device
			 gensym-pathname-directory
			 gensym-pathname-name
			 gensym-pathname-type
			 gensym-pathname-version)
	       collect
	       `(,component-identifier 
		 (,component-identifier ,pathname)))
     ,@(ignoring-variables-appropriately
	 (gensym-pathname-host
	   gensym-pathname-device
	   gensym-pathname-directory
	   gensym-pathname-name
	   gensym-pathname-type
	   gensym-pathname-version)
	 body)))


(defun reclaim-pathname-or-string (pathname-var)
  (cond
    ((null pathname-var) nil)
    ((gensym-pathname-p pathname-var)
     (reclaim-gensym-pathname pathname-var))
    ((text-string-p pathname-var)
     (reclaim-text-string pathname-var))
    #+development
    (t
     (error "Bad arg to reclaim-pathname-or-string"))))

;; Added store-current-pathname to reclaim the old pathname automatically, since
;; leaking is now under control.  jh, 12/15/90.  Added store-current-namestring,
;; too.  jh, 1/3/91.

(defmacro store-current-pathname (pathname-var new-value)
  (unless (symbolp pathname-var)
    (error "STORE-CURRENT-PATHNAME: need a symbol for pathname, not ~s"
	   pathname-var))
  (avoiding-variable-capture (new-value) ;since new-value may mention pathname-var
    `(progn
       (reclaim-pathname-or-string ,pathname-var)
       (setq ,pathname-var
	     (cond ((text-string-p ,new-value)
		    (prog1 (gensym-pathname ,new-value)
		      (reclaim-text-string ,new-value)))
		   (t ,new-value))))))

(defmacro store-current-namestring (pathname-var new-value)
  (unless (symbolp pathname-var)
    (error "STORE-CURRENT-NAMESTRING: need a symbol for namestring, not ~s"
	   pathname-var))
  (avoiding-variable-capture (new-value) ;since new-value may mention pathname-var
    `(progn 
       (cond ((text-string-p ,pathname-var)
	      (reclaim-text-string ,pathname-var))
	     ((gensym-pathname-p ,pathname-var)
	      (reclaim-gensym-pathname ,pathname-var)))
       (setq ,pathname-var ,new-value))))


;; Like with-pathname-components, with-multiple-pathname-components binds pathname
;; slots to accessor names in its scope.  The difference is that more than one set
;; of pathname components may be bound.  To distinguish them, the accessor names
;; are postfixed with the indices 1, 2, and so on.  The index origin is 1; no
;; hypens intervene between the accessor name and the index.

;; With-multiple-pathname-components will be used in gensym-pathnames-equal-p.
;; Since the code was cloned from with-pathname-components, we will keep it nearby
;; for the nonce.

;; Ignoring unused variables is harder here than in with-pathname-components, so
;; we don't do it for now.  jh, 12/18/90.

(defmacro with-multiple-pathname-components (pathname-symbols &body body)
  (unless (every #'symbolp pathname-symbols)
    (error "WITH-MULTIPLE-PATHNAME-COMPONENTS: non-symbol in specs ~a"
	   pathname-symbols))
  `(let ,(loop for designator from 1 to (length pathname-symbols)
	       for pathname-symbol in pathname-symbols
	       append
	       (loop for component-identifier
			 in '(gensym-pathname-host
			       gensym-pathname-device
			       gensym-pathname-directory
			       gensym-pathname-name
			       gensym-pathname-type
			       gensym-pathname-version)
		     collect
		     `(,(intern 
			  (format nil "~a~a"
			    component-identifier 
			    designator))
		       (,component-identifier ,pathname-symbol))))
     ,@body))



(defun reclaim-gensym-pathname (pathname)

  ;; jh per jra.  To catch double reclamation of gensym-pathnames, a
  ;; source of obscure bugs.
  #+development
  (unless (gensym-pathname-p pathname)
    (cerror "Continue without attempting to reclaim the object."
	    "RECLAIM-GENSYM-PATHNAME: ~s is not a gensym-pathname"
	    pathname)
    (return-from reclaim-gensym-pathname))

  (let ((current-custom-reclamation-stamp? "RclmGsmPthnm"))	; suspect recycling bug. (MHD 2/8/93)
    (with-pathname-components (pathname)
      (when (text-string-p gensym-pathname-host)
	(reclaim-text-string gensym-pathname-host))
      (when (text-string-p gensym-pathname-device)
	(reclaim-text-string gensym-pathname-device))
      (when (consp gensym-pathname-directory)
	(loop for directory-component in gensym-pathname-directory
	      when (text-string-p directory-component)
		do (reclaim-text-string directory-component)
	      finally (reclaim-path-list gensym-pathname-directory)))
      (when (text-string-p gensym-pathname-name)
	(reclaim-text-string gensym-pathname-name))
      (when (text-string-p gensym-pathname-type)
	(reclaim-text-string gensym-pathname-type))
      (when (text-string-p gensym-pathname-version)
	(reclaim-text-string gensym-pathname-version))	;reached in Coral Common Lisp
      (reclaim-gensym-pathname-structure-macro pathname))))

(defun-simple reclaim-if-gensym-pathname (pathname?)
  (when pathname?
    (reclaim-gensym-pathname pathname?)))


;; jh, 6/18/92.  Added following function for use in the filename parsers which
;; gather some pathname components and then have to give up.

(defun reclaim-pathname-components 
       (&optional host device directory name type version)
  (when (text-string-p host)
    (reclaim-text-string host))
  (when (text-string-p device)
    (reclaim-text-string device))
  (loop for directory-item in directory
	when (text-string-p directory-item)
	  do (reclaim-text-string directory-item)
	finally (reclaim-path-list directory))
  (when (text-string-p name)
    (reclaim-text-string name))
  (when (text-string-p type)
    (reclaim-text-string type))
  (when (text-string-p version)
    (reclaim-text-string version)))


;; jh, 1/30/92.  Added print-gensym-pathname for debugging in Chestnut.  Thus it
;; does NOT have a #+development reader switch.
;; OBSOLETE? -- see print-gensym-pathname-structure, above. (MHD 3/14/94)

(defun print-gensym-pathname (pathname?)
  (if (gensym-pathname-p pathname?)
      (with-pathname-components (pathname?)
        (format t "~&~a pathname -~%" (gensym-pathname-file-system pathname?))
        (format t "~&     host: ~s~%" gensym-pathname-host)
        (format t "~&   device: ~s~%" gensym-pathname-device)
        (format t "~&directory: ~s~%" gensym-pathname-directory)
        (format t "~&     name: ~s~%" gensym-pathname-name)
        (format t "~&     type: ~s~%" gensym-pathname-type)
        (format t "~&  version: ~s~%" gensym-pathname-version))
      (format t "~&not a gensym-pathname: ~s~%" pathname?)))


;;; The function pathname-distinguished-by-version-p does its best to determine if
;;; the file system used by that pathname keeps version information.
;;; Pathname-distinguished-by-version-p takes a single argument, a
;;; gensym-pathname, and returns two values: true and true if it could be
;;; determined that version information is kept, nil and true if it could be
;;; determined that version information is not kept, and nil and nil if it could
;;; not be determined if version information is kept.

(defconstant file-systems-which-distinguish-by-version
	     '(vms))
		
(defun pathname-distinguished-by-version-p (pathname)
  (if (gensym-pathname-p pathname)
      (if (memq (gensym-pathname-file-system pathname)
		file-systems-which-distinguish-by-version)
	  (values t t)
	  (values nil t))
      (values nil nil)))

;;; The function pathname-can-contain-device-p is analogous to
;;; pathname-distinguished-by-version-p.

(defconstant file-systems-which-store-device-names
	     '(vms coral))
		
(defun pathname-can-contain-device-p (pathname)
  (if (gensym-pathname-p pathname)
      (if (memq (gensym-pathname-file-system pathname)
		file-systems-which-store-device-names)
	  (values t t)
	  (values nil t))
      (values nil nil)))


;;; gensym-make-pathname 

;;; gensym-make-pathname 
;;;   &key
;;;   host-text-string
;;;   device-text-string
;;;   directory-path-list-of-text-strings
;;;   name-text-string
;;;   type-text-string
;;;   version-integer-or-symbol
;;;   => gensym-pathname
;;; ref: CLt:/2e p643-4

;; Note: The Common Lisp analogue gensym-make-pathname is a macro which must
;; appear at the beginning of this file because of definitional dependencies.
;; (Almost every other pathname function uses it when it coerces things into
;; pathnames.) Gensym-make-pathname is a macro so that we can use keywords without
;; paying the run-time penalty of parsing a complex lambda-list.  Keywords are
;; considered more perspicuous than by-order arguments in this case.  Doing it
;; this way also lets us skip a run-time test for defaults on platforms which
;; still must use lisp pathnames.

;; The internal function gensym-make-pathname-without-copying, however, must
;; appear after the definition of the gensym-merge-pathnames macro.

;; Further note that gensym-make-pathname copies its arguments, to preserve a
;; standard "caller reclaims" discipline.

;; Warning: the functions gensym-make-pathname-with-copied-components and
;; gensym-make-pathname-without-copying are internal and should not be used
;; outside of the PATHNAMES module.  Current names and behavior are subject to
;; change and should not be relied upon.  If you need this functionality in a
;; module previous to PATHNAMES, use gensym-make-pathname-function.  Note that
;; gensym-make-pathname-function does not use keywords, unlike
;; gensym-make-pathname.  In this case, we will have to exchange exact Common Lisp
;; compatability for the runtime win of not having to parse a keyworded
;; lambda-list.

;; CLtL/2e p 615 leaves unspecified what can be given to the :directory
;; component of make-pathname, but we try to do something reasonable when we get
;; a string.  If the string can be seen as a directory, we use that.  If it can
;; be parsed as a non-directory sort of file, we use the directory component.
;; If we can't parse the string at all (and this is the most controversial), we
;; use nil, that is, an empty directory.  It could be argued that this last case
;; should generate an error, but it could also be argued that
;; gensym-make-pathname should always return some sort of gensym-pathname,
;; however skewed.

;; Gensym-merge-pathnames is a macro which must be defined before the
;; (conceptually more primitive) gensym-make-pathname.  Gensym-merge-pathnames is
;; a macro to save on the extra tests for the presence of defaults on platforms
;; which don't use gensym-pathnames.

(defmacro gensym-merge-pathnames 
       (convertible-thing &optional default default-version)
  `(gensym-merge-pathnames-function
     ,convertible-thing
     ,default
     ,default-version))

;; jh, 10/8/91.  A setf-method for values is defined for the Lisp machines, but
;; not anywhere else.  In particular, the Lucid we use in the translator has no
;; setf-method for values.  Even so, there are problems with redefining this
;; setf-method on the Microexplorer, having to do with an undefined function in
;; the compile, even though this function appears nowhere in the full
;; macroexpansion in an Emacs buffer.  For future reference, the undefined
;; function is named (setf common-lisp-ar-1).  Better to take no risks and define
;; our own.

;; jra & jh, 10/9/91.  Note that a true setf-method for values would have to use
;; define-setf-method, since the subforms of the places inside the values form in
;; (setf (values ...) ...) must be evaluated in the correct order (CLtL/2e pp
;; 135-6).  Thus CLtL/2e p 129 is mistaken when it says that writing a setf-method
;; for values is "not a difficult task".  We will defer doing it right until after
;; the 3.0 release, though; the current setf-method will serve our purposes for
;; now.

;; jh, 10/8/91.  We also get a complaint from the Symbolics compiler that three
;; gensyms are never used.  My guess is that the expander for 
;;   (setf (ab-values subform1 subform2 ...) ...) 
;; creates them to hold the values of the subforms, not knowing that our defsetf
;; expander creates its own.  Not sure how to fix this.

;(defmacro ab-values (&rest args) `(values ,@args)) ;stifles Symbolics compiler

;(defsetf ab-values (&rest value-receiving-forms) (value-returning-form)
;  (let ((receiving-variables
;	  (loop for index from 0 below (length value-receiving-forms)
;		collect (make-symbol (format nil "RECEIVED-VALUE-~a" index)))))
;    `(multiple-value-bind ,receiving-variables
;			  ,value-returning-form
;       ,@(loop for receiving-variable in receiving-variables
;	       for receiving-form in value-receiving-forms
;	       collect `(setf ,receiving-form ,receiving-variable)))))

(defun get-default-file-system-info ()
  (values (local-filename-parser)
	  (local-namestring-generator)
	  (local-file-system)))


 
 

(defun gensym-make-pathname-without-copying
       (host device directory name type version &optional defaults)
  (let ((undefaulted-pathname
	  (make-gensym-pathname-structure-function
	    host 
	    device 
	    directory 
	    name 
	    type 
	    version)))
    (multiple-value-bind
      (filename-parser namestring-generator file-system)
      (cond ((and host (text-string-p host))
	     (get-parser-from-namestring host))
	    ((and defaults (gensym-pathname-p defaults))
	     (values (gensym-pathname-filename-parser defaults)
		     (gensym-pathname-namestring-generator defaults)
		     (gensym-pathname-file-system defaults)))
	    ((and defaults (text-string-p defaults))
	     (get-parser-from-namestring defaults))
	    (t (get-default-file-system-info)))
      (setf (gensym-pathname-filename-parser undefaulted-pathname) 
	    filename-parser)
      (setf (gensym-pathname-namestring-generator undefaulted-pathname) 
	    namestring-generator)
      (setf (gensym-pathname-file-system undefaulted-pathname)
	    file-system))
    (if defaults
	(prog1 (gensym-merge-pathnames
		 undefaulted-pathname
		 defaults)
	       (reclaim-gensym-pathname
		 undefaulted-pathname))
	undefaulted-pathname)))

(defun copy-directory-components-from-directory-string (directory-string)
  (let ((raw-directory-pathname? (gensym-pathname directory-string)))
    (cond
      ;; jh, 8/29/94.  If the :directory component given to gensym-make-pathname
      ;; was a string that did not parse into a pathname in the current file
      ;; system, return nil.  This may not be the right thing to do, but
      ;; gensym-make-pathname always undertakes to return a pathname, so without
      ;; a condition system that covers file errors, this is the best we can do
      ;; for now.
      ((null raw-directory-pathname?) nil)
      ((gensym-pathname-name raw-directory-pathname?)
       (let ((directory-pathname?
	       (gensym-file-as-directory raw-directory-pathname?)))
	 (if directory-pathname?
	     (loop for directory-component
		       in (gensym-pathname-directory directory-pathname?)
		   collecting
		   (copy-pathname-contents directory-component)
		     using path-cons
		   finally
		     (reclaim-gensym-pathname directory-pathname?)
		     (reclaim-gensym-pathname raw-directory-pathname?))
	     ;; The :directory component given to gensym-make-pathname was a
	     ;; string that did not parse into a pathname that could represent a
	     ;; directory.  So extract only the directory component of the
	     ;; pathname we did get.
	     (loop for directory-component
		       in (gensym-pathname-directory raw-directory-pathname?)
		   collect
		   (copy-pathname-contents directory-component)
		     using path-cons
		   finally
		     (reclaim-gensym-pathname raw-directory-pathname?)))))
      (t (loop for directory-component
		   in (gensym-pathname-directory raw-directory-pathname?)
	       collecting
	       (copy-pathname-contents directory-component)
		 using path-cons
	       finally
		 (reclaim-gensym-pathname raw-directory-pathname?))))))

(defun gensym-make-pathname-with-copied-components
       (host device directory name type version defaults)
  (let ((convert-file-strings-to-uppercase-p
	  (cond ((and host (text-string-p host))
		 (convert-file-strings-to-uppercase-p
		   (nth-value 2 (get-parser-from-namestring host))))
		((and defaults (gensym-pathname-p defaults))
		 (convert-file-strings-to-uppercase-p
		   (gensym-pathname-file-system defaults)))
		((and defaults (text-string-p defaults))
		 (convert-file-strings-to-uppercase-p
		   (nth-value 2 (get-parser-from-namestring defaults))))
		(t nil)))) ;don't use local file system here!
    (setq host (copy-pathname-contents host))
    (setq device (copy-pathname-contents device))
    (setq directory
	  (cond
	    ((consp directory)
	     (loop for directory-component in directory
		   collecting
		   (copy-pathname-contents directory-component)
		     using path-cons))
	    ((text-string-p directory)
	     (copy-directory-components-from-directory-string
	       directory))
	    ;; This "else" is not currently (12/12/90) reached.
	    (t (copy-pathname-contents directory))))
    (setq name (copy-pathname-contents name))
    (setq type (copy-pathname-contents type))
    (setq version (copy-pathname-contents version))
    (gensym-make-pathname-without-copying
      host
      device
      directory
      name
      type
      version
      defaults)))


(defmacro gensym-make-pathname
       (&key host device directory name type version defaults)
  `(gensym-make-pathname-with-copied-components
     ,host
     ,device
     ,directory
     ,name
     ,type
     ,version
     ,defaults))


(defun gensym-make-pathname-function
       (host device directory name type version &optional defaults)
  (gensym-make-pathname
    :host      host
    :device    device
    :directory directory
    :name      name
    :type      type
    :version   version
    :defaults  defaults))




;;; copy-gensym-pathname <old-gensym-pathname> <new-gensym-pathname>

;;; Note that copy-gensym-pathname converts to upper case if the value of
;;; convert-file-strings-to-uppercase-p is non-nil and converts symbols to lower
;;; case if convert-file-strings-to-uppercase-p is nil.  This is a heuristic
;;; designed to accomodate the user in the largest number of cases.

(defun copy-pathname-contents (old-contents)
  (cond ((null old-contents) old-contents)
        ((and (text-string-p old-contents)
	      convert-file-strings-to-uppercase-p)
	 (nstring-upcasew (copy-text-string old-contents)))
	((text-string-p old-contents)
	 (copy-text-string old-contents))
	((and (symbolp old-contents)   ;sloppy - really need something like
	      (keywordp old-contents)) ; special-pathname-tag-p (e.g. :newest)
	 old-contents)
	((symbolp old-contents)
	 (let ((mutable-string-from-symbol
		 (copy-text-string (symbol-name-text-string old-contents))))
	   (if convert-file-strings-to-uppercase-p
	       mutable-string-from-symbol
	       (nstring-downcasew mutable-string-from-symbol))))
	((gensym-string-p old-contents)
	 #+development
	 (cerror "Continue, turning it into a text string"
		 "Gensym strings (~s) are now illegal in Gensym pathnames"
		 old-contents)
	 (copy-text-string old-contents))
	(t old-contents)))

;; jh, 10/5/91.  Modified copy-pathname-contents to handle symbols.


(defun copy-directory-contents (directory-to-copy)
  (loop for directory-component in directory-to-copy
		 collect
		   (copy-pathname-contents directory-component)
				using path-cons))


(defun copy-gensym-pathname (old-pathname)
   (when (null old-pathname)
    (return-from copy-gensym-pathname nil))
     (with-pathname-components (old-pathname)
       (let* ((new-pathname 
           (make-gensym-pathname-structure-function nil nil nil nil nil nil))
         (convert-file-strings-to-uppercase-p
           (convert-file-strings-to-uppercase-p
             (gensym-pathname-file-system old-pathname))))
         (setf (gensym-pathname-host new-pathname)
          (copy-pathname-contents gensym-pathname-host))
         (setf (gensym-pathname-device new-pathname)
          (copy-pathname-contents gensym-pathname-device))
         (setf (gensym-pathname-directory new-pathname)
          (if (consp gensym-pathname-directory)
         (copy-directory-contents gensym-pathname-directory)
         ;; This "else" is not currently (12/12/90) reached.
         (copy-pathname-contents gensym-pathname-directory)))
         (setf (gensym-pathname-name new-pathname)
          (copy-pathname-contents gensym-pathname-name))
         (setf (gensym-pathname-type new-pathname)
          (copy-pathname-contents gensym-pathname-type))
         (setf (gensym-pathname-version new-pathname)
          (copy-pathname-contents gensym-pathname-version))
         (setf (gensym-pathname-file-system new-pathname)
          (gensym-pathname-file-system old-pathname))
         (setf (gensym-pathname-filename-parser new-pathname)
          (gensym-pathname-filename-parser old-pathname))
         (setf (gensym-pathname-namestring-generator new-pathname)
          (gensym-pathname-namestring-generator old-pathname))
         new-pathname)))

;;; gensym-pathnames-equal-p <gensym-pathname-1> <gensym-pathname-2>

(defun gensym-pathname-contents-equal-p (contents1 contents2)
  (cond ((and (text-string-p contents1)
	      (text-string-p contents2)
	      convert-file-strings-to-uppercase-p)
	 (string-equalw contents1 contents2))
	((and (text-string-p contents1)
	      (text-string-p contents2))
	 (string=w contents1 contents2))
	(t (eql contents1 contents2))))

(defun gensym-pathnames-equal-p (pathname1 pathname2)
  (and (gensym-pathname-p pathname1)
       (gensym-pathname-p pathname2)
       (let ((file-system1
	       (gensym-pathname-file-system pathname1))
	     (file-system2
	       (gensym-pathname-file-system pathname2)))
	 (and (eq file-system1 file-system2)
	      (let ((convert-file-strings-to-uppercase-p
		      (convert-file-strings-to-uppercase-p file-system1)))
		(with-multiple-pathname-components (pathname1 pathname2)
		  (and (gensym-pathname-contents-equal-p
			 gensym-pathname-host1
			 gensym-pathname-host2)
		       (gensym-pathname-contents-equal-p
			 gensym-pathname-device1
			 gensym-pathname-device2)
		       (if (and (consp gensym-pathname-directory1)
				(consp gensym-pathname-directory2))
			   (and (= (length gensym-pathname-directory1)
				   (length gensym-pathname-directory2))
				(loop for component1 
					  in gensym-pathname-directory1
				 for component2 
				     in gensym-pathname-directory2
				      always 
					(gensym-pathname-contents-equal-p
					  component1
					  component2)))
			   (gensym-pathname-contents-equal-p
			     gensym-pathname-directory1
			     gensym-pathname-directory2))
		       (gensym-pathname-contents-equal-p
			 gensym-pathname-name1
			 gensym-pathname-name2)
		       (gensym-pathname-contents-equal-p
			 gensym-pathname-type1
			 gensym-pathname-type2)
		       (gensym-pathname-contents-equal-p
			 gensym-pathname-version1
			 gensym-pathname-version2))))))))


;; Added gensym-pathnames-equal-enough-p, which will return true if one pathname
;; has no version information and the other has :newest.  This prevents the
;; confirmation dialogue box in save-kb which from coming up if two pathnames, one
;; derived and one a truename, are identical except that the truename has a
;; version component of :newest.  This function is modified from
;; gensym-pathnames-equal-p, which is of more general utility.  jh, 3/6/91.

(defun gensym-pathnames-equal-enough-p (pathname1 pathname2)
  (and (gensym-pathname-p pathname1)
       (gensym-pathname-p pathname2)
       (let ((file-system1
	       (gensym-pathname-file-system pathname1))
	     (file-system2
	       (gensym-pathname-file-system pathname2)))
	 (and (eq file-system1 file-system2)
	      (let ((convert-file-strings-to-uppercase-p
		      (convert-file-strings-to-uppercase-p file-system1)))
		(with-multiple-pathname-components (pathname1 pathname2)
		  (and (gensym-pathname-contents-equal-p
			 gensym-pathname-host1
			 gensym-pathname-host2)
		       (gensym-pathname-contents-equal-p
			 gensym-pathname-device1
			 gensym-pathname-device2)
		       (if (and (consp gensym-pathname-directory1)
				(consp gensym-pathname-directory2))
			   (and (= (length gensym-pathname-directory1)
				   (length gensym-pathname-directory2))
				(loop for component1 
					  in gensym-pathname-directory1
				 for component2 
				     in gensym-pathname-directory2
				      always 
					(gensym-pathname-contents-equal-p
					  component1
					  component2)))
			   (gensym-pathname-contents-equal-p
			     gensym-pathname-directory1
			     gensym-pathname-directory2))
		       (gensym-pathname-contents-equal-p
			 gensym-pathname-name1
			 gensym-pathname-name2)
		       (gensym-pathname-contents-equal-p
			 gensym-pathname-type1
			 gensym-pathname-type2)
		       (cond ((and (eq gensym-pathname-version1 :newest)
				   (null gensym-pathname-version2))
			      t)
			     ((and (null gensym-pathname-version1)
				   (eq gensym-pathname-version2 :newest))
			      t)
			     (t (gensym-pathname-contents-equal-p
				  gensym-pathname-version1
				  gensym-pathname-version2))))))))))

			      

;;; Internal conversion to and from lisp pathnames

;; Warning: the functions lisp-pathname-to-gensym-pathname,
;; gensym-pathname-to-lisp-pathname, and convert-to-lisp-pathname-if-necessary are
;; internal.  There should be no need to use them outside the PATHNAMES module.
;; The underlying mechanism actually used to implement a pathname system should be
;; invisible.  As an added inducement, note that the behavior of these functions
;; is currently (12/14/90) only supported on Lisp Machines, and will produce
;; erratic results anywhere else.

(defun-for-macro get-lisp-pathname-binding-forms (pathname-symbol)
  (if (eval-feature :ti)
      (with-package-specific-symbols (fs |::| host
				      fs |::| device
				      fs |::| directory
				      fs |::| name
				      fs |::| type
				      fs |::| version)
	`(
	  (lisp-pathname-host      (symeval-in-instance ,pathname-symbol 'host))
	  (lisp-pathname-device    (symeval-in-instance ,pathname-symbol 'device))
	  (lisp-pathname-directory (symeval-in-instance ,pathname-symbol 'directory))
	  (lisp-pathname-name      (symeval-in-instance ,pathname-symbol 'name))
	  (lisp-pathname-type      (symeval-in-instance ,pathname-symbol 'type))
	  (lisp-pathname-version   (symeval-in-instance ,pathname-symbol 'version))
	  ))
      `(
	(lisp-pathname-host      (pathname-host      ,pathname-symbol))
	(lisp-pathname-device    (pathname-device    ,pathname-symbol))
	(lisp-pathname-directory (pathname-directory ,pathname-symbol))
	(lisp-pathname-name      (pathname-name      ,pathname-symbol))
	(lisp-pathname-type      (pathname-type      ,pathname-symbol))
	(lisp-pathname-version   (pathname-version   ,pathname-symbol))
	)))

(defmacro with-lisp-pathname-components ((pathname) &body body)
  (unless (symbolp pathname)
    (error "WITH-LISP-PATHNAME-COMPONENTS: pathname form must be a symbol, ~
            not ~a"
	   pathname))
  `(let ,(get-lisp-pathname-binding-forms pathname)
     ,@(ignoring-variables-appropriately
	 (lisp-pathname-host
	   lisp-pathname-device
	   lisp-pathname-directory
	   lisp-pathname-name
	   lisp-pathname-type
	   lisp-pathname-version)
	 body)))


(defun file-system-host-as-text-string (lisp-pathname-host)
  (cond ((text-string-p lisp-pathname-host)
	 (tformat-text-string "~a" lisp-pathname-host))
	((null lisp-pathname-host)
	 nil)
	(t #+development
	   (cerror "Use NIL"
		   "LISP-PATHNAME-TO-GENSYM-PATHNAME: Unknown ~
                              Lisp pathname host component:~%~s"
		   lisp-pathname-host)
	   nil)))


;;; Underlying Macros for Pathname Analogues

;;; In the code that follows, convertible-thing is one of
;;;  a text-string
;;;  a symbol [disobeying the Common Lisp II directive]
;;;  a gensym-pathname
;;;  an open g2-stream.





;;; with-pathname-conversion 
;;;   binding-specs &body body

;;; In the scope of a with-pathname-conversion-form, a binding is established to a
;;; gensym-pathname made from that object, or to nil if creating a pathname is
;;; impossible.  For more complex uses, note that the gensym-pathname contains
;;; funcallable symbols for the parser and generator appropriate for the object.
;;; As a temporary expedient, we also bind a switch that controls case conversion
;;; when the pathname is created or copied.

;;; With-protected-pathname-conversion behaves like with-pathname-conversion,
;;; except that the converted pathnames are reclaimed on exit, as if by
;;; unwind-protect.  No gensym-pathnames should be returned from the scope of this
;;; form, as they have already been reclaimed by this point.

;;; With-pathname-conversion and with-protected-pathname-conversion have binding
;;; specs of the form
;;;   (original-form new-variable)
;;; where original-form is the thing to be converted to a gensym-pathname, and
;;; new-variable is a symbol to be bound to that gensym-pathname, or to nil if the
;;; thing cannot be converted.  Any errors during the conversion process are
;;; supressed; signal-gensym-file-error must be called explicitly if that is the
;;; desired behavior.

;;; Note that a new gensym-pathname is always created, even when the original form
;;; evaluates to a gensym-pathname.  This is to foster clarity in keeping track of
;;; file-related data structures for later reclamation.

;;; Note that, unlike with-protected-pathname-conversion, it is allowable to
;;; return gensym-pathname structures to places outside the scope of a
;;; with-pathname-conversion form.  It then becomes the responsibility of the
;;; caller to reclaim these structures.

;;; If a gensym-pathname structure is created, its
;;; gensym-pathname-namestring-generator slot contains the name of the function G2
;;; will use to create a namestring from a gensym-pathname and its
;;; gensym-pathname-filename-parser slot contains the name of the function G2 uses
;;; to parse a namestring into a gensym-pathname.  Knowing these functions may be
;;; helpful in the scope of a with-pathname-conversion form.

;;; With-pathname-conversion and with-protected-pathname-conversion also bind the
;;; special variable convert-file-strings-to-uppercase-p to t if the file system
;;; converts file namestrings to uppercase, and nil otherwise.  See the note
;;; attached to this variable for the rationale.  This causes
;;; convert-to-gensym-pathname to do case conversion where appropriate.

(defun convert-namestring-to-gensym-pathname-with-known-parser
    (namestring filename-parser namestring-generator)
  (let ((pathname?
	  (funcall-symbol filename-parser namestring)))
    (when pathname?
      (setf (gensym-pathname-filename-parser pathname?)
	    filename-parser)
      (setf (gensym-pathname-namestring-generator pathname?)
	    namestring-generator)
      pathname?)))

;;; The new LOOP path is to simplify the looping code on global variable
;;; all-gensym-pathnames-containing-open-streams, which is a list in legacy
;;; build and constant queue in SymScale.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (define-loop-path gensym-pathname
		    #-SymScale expand-list-loop-iterator
		    #+SymScale constant-queue-elements-of (of)))

;; Changed under the superstitious belief that it might help a bombout in the
;; translator that can't perform this operation when defined as a substitution
;; macro.  -jra & ac 9/5/91

(defun convert-g2-stream-to-gensym-pathname (g2-stream)
  (current-system-case
    (gsi g2-stream)
    (t
      (loop for pathname being each gensym-pathname
			    of all-gensym-pathnames-containing-open-streams
	    thereis 
	    (and (identical-g2-streams-p
		   (gensym-pathname-stream? pathname) 
		   g2-stream)
		 (copy-gensym-pathname pathname))
	    finally
	      #+development
	      (cerror "Return empty pathname"
		      "CONVERT-TO-GENSYM-PATHNAME: G2 stream ~a not found" 
		      g2-stream)
	      (return (make-empty-gensym-pathname))))))


(defun convert-to-gensym-pathname-with-known-parser
    (thing filename-parser namestring-generator)
  (cond
    ((gensym-pathname-p thing)		; def-structures are not CL types
     (copy-gensym-pathname thing))
    ((wide-string-p thing)		; ditto.
     (convert-namestring-to-gensym-pathname-with-known-parser
       thing
       filename-parser
       namestring-generator))
    (t
     (typecase thing
       (string				; eliminate this case! (MHD 4/30/96)
	(convert-namestring-to-gensym-pathname-with-known-parser
	  thing
	  filename-parser
	  namestring-generator))
       (symbol				; not CL but useful
	(convert-namestring-to-gensym-pathname-with-known-parser
	  (symbol-name-text-string thing) filename-parser namestring-generator))
       (otherwise
	(cond
	  ((g2-stream-p thing)
	   (convert-g2-stream-to-gensym-pathname thing))
	  (t #+development
	     (cerror
	       "Return empty pathname"
	       "CONVERT-TO-GENSYM-PATHNAME-OF-KNOWN-HOST:~%~
                 Encountered inappropriate thing ~a~%~
                 (neither string, text-string, symbol, g2-stream, nor gensym-pathname)"
	       thing)
	     (make-empty-gensym-pathname))))))))


(defmacro convert-namestring-to-gensym-pathname 
	  (namestring default-filename-parser default-namestring-generator)

  `(convert-to-gensym-pathname-with-known-parser
     ,namestring
     ,default-filename-parser
     ,default-namestring-generator)
  )




(defun convert-to-gensym-pathname 
    (thing default-filename-parser default-namestring-generator)
  (cond
    ((gensym-pathname-p thing)		; def-structures are not CL types
     (copy-gensym-pathname thing))
    ((text-string-p thing)		; ditto.
     (convert-namestring-to-gensym-pathname 
       thing default-filename-parser default-namestring-generator))
    (t
     (typecase thing
       (string				; eliminate this case! (MHD 4/30/96)
	(convert-namestring-to-gensym-pathname 
	  thing default-filename-parser default-namestring-generator))
       (symbol				; not CL but useful
	(convert-namestring-to-gensym-pathname 
	  (symbol-name-text-string thing)
	  default-filename-parser
	  default-namestring-generator))
       (otherwise
	(cond
	  ((g2-stream-p thing)
	   (convert-g2-stream-to-gensym-pathname thing))
	  (t #+development
	     (cerror
	       "Return empty pathname"
	       "CONVERT-TO-GENSYM-PATHNAME:~%~
                 Encountered inappropriate thing ~a~%~
                 (neither string, text-string, symbol, g2-stream, nor gensym-pathname)"
	       thing)
	     (make-empty-gensym-pathname))))))))

;; Changed with-pathname-conversion and with-protected-pathname-conversion to
;; determine the local file system at runtime rather than compile time.  We are
;; coalescing explorer and microexplorer binaries and can no longer tell anything
;; about the file system at compile time.  jh per mhd 2/8/91.

(defmacro with-pathname-conversion 
	  (binding-specs &body body)
  (unless (loop for (original-variable converted-variable) in binding-specs
		always
		(and (symbolp original-variable)
		     (symbolp converted-variable)))
    (error "WITH-PATHNAME-CONVERSION:~%~
            new variables in binding specs ~a must be exclusively symbols"
	   binding-specs))
  (avoiding-variable-capture (&aux current-local-filename-parser
				   current-local-namestring-generator)
    `(let* ((,current-local-filename-parser
	       (local-filename-parser))
	    (,current-local-namestring-generator
	       (local-namestring-generator))
	    (convert-file-strings-to-uppercase-p
	      (convert-file-strings-to-uppercase-p 
		,current-local-filename-parser))
	    ,@(loop for (original-variable converted-variable) in binding-specs
		    collect
		    `(,converted-variable
		        (convert-to-gensym-pathname 
			  ,original-variable
			  ,current-local-filename-parser
			  ,current-local-namestring-generator
			  ))))
       ,@body)))

		    
(defmacro with-protected-pathname-conversion 
	  (binding-specs &body body)
  (unless (loop for (original-variable converted-variable) in binding-specs
		always
		(and (symbolp original-variable)
		     (symbolp converted-variable)))
    (error "WITH-PROTECTED-PATHNAME-CONVERSION:~%~
            new variables in binding specs ~a must be exclusively symbols"
	   binding-specs))
  (avoiding-variable-capture (&aux current-local-filename-parser
				   current-local-namestring-generator)
    `(let* ((,current-local-filename-parser
	       (local-filename-parser))
	    (,current-local-namestring-generator
	       (local-namestring-generator))
	    (convert-file-strings-to-uppercase-p
	      (convert-file-strings-to-uppercase-p
		,current-local-filename-parser)))
       (protected-let ,(loop for (original-variable converted-variable) 
				 in binding-specs
			     collect
			     `(,converted-variable
			         (convert-to-gensym-pathname 
				   ,original-variable
				   ,current-local-filename-parser
				   ,current-local-namestring-generator)
				 (when ,converted-variable
				   (reclaim-gensym-pathname ,converted-variable))))
	 ,@body))))


	      
       

;; We need a special pathname-conversion context for merge-pathnames in which the
;; filename parser is derivable from the defaults.  This context is roughly
;; equivalent to three scoping layers: an outer layer which derives the filename
;; parser, a with-pathname-conversion layer for the pathname arg and a
;; with-protected-pathname-conversion layer for the default pathname (which gets
;; reclaimed).  jh, 1/9/91.

;;; error-absorbing constructs


;;; gensym-probe-file
;;;   convertible-thing => gensym-pathname or nil
;;; Ignores errors.
;;; ref: CLtL/2e p654
;;; notes: More comprehensive than g2-stream-probe-file, since it takes arbitrary
;;; (convertble) objects.


;;; Note: In what follows, we use the term "truename conversion" to refer to the
;;; process whereby a unique pathname structure is associated with a file.  Common
;;; Lisp (CLtL/2e) requires that two pathname functions do truename conversion:
;;; probe-file and truename.  This conversion typically involves things like
;;; determining the version number of the file, canonicizing the case of its
;;; components, coalescing meta-components (like :up) in the directory list, and
;;; resolving filename links.  This last is not available yet (12/6/90), but
;;; gensym-probe-file and gensym-truename (which calls gensym-probe-file) make an
;;; effort to do the remaining three.  In this they are aided by the filename
;;; parser, which has already converted the character case of the filename to that
;;; expected by the file system.  jh, 12/6/90.

;; jh, 11/14/91.  Rewrote coalesce-directory-components for clarity and improved
;; it to remove excess :relative markers as well as the :up markers it was already
;; removing.  Added a validation suite so we can check its behavior in the future.

(defun coalesce-directory-components (directory-list)
  (loop for directory-component in directory-list
	with result-directory-list = nil
	for retain-relative-marker-p = 
	    (eq (car directory-list) :relative) then nil
	for retain-up-marker-p = 
	    (eq (car directory-list) :up) 
	    then (and retain-up-marker-p (eq directory-component :up))
	do
    (case directory-component
      (:relative 
       (when retain-relative-marker-p
	 (path-push directory-component result-directory-list)))
      (:up
       (if retain-up-marker-p
	   (path-push directory-component result-directory-list)
	   (let ((discarded-component
		   (path-pop result-directory-list)))
	     (when (text-string-p discarded-component)
	       (reclaim-text-string discarded-component)))))
       (otherwise 
	 (path-push directory-component result-directory-list)))
    finally 
      (reclaim-path-list directory-list)
      (return (nreverse result-directory-list))))

(define-modify-macro coalesce-directory-components-in-place ()
		     coalesce-directory-components)

#+development
(defvar coalesce-directory-components-validation-suite
	'(
	  ((:up :up :up "HELLO" "THERE") 
	   (:up :up :up "HELLO" "THERE"))
	  ((:relative :relative :relative "HELLO" :relative "THERE")
	   (:relative "HELLO" "THERE"))
	  ((:up "HELLO" :up "THERE")
	   (:up "THERE"))
	  (("HELLO" "THERE")
	   ("HELLO" "THERE"))
	  (("HELLO" :up "THERE" :up "JOHN")
	   ("JOHN"))
	  ))

#+development
(defun validate-coalesce-directory-components ()
  (loop for (test expected) 
	    in coalesce-directory-components-validation-suite
	for index from 0
	do (format t "~&~a ...~%" index)
	always
	(let ((result 
		(coalesce-directory-components 
		  (loop for component in test
			collect (if (text-string-p component)
				    (copy-text-string component)
				    component)
				      using path-cons))))
	  (and (= (length result) (length expected))
	       (every #'equal result expected)))))

	
;; jh, 3/25/91.  Fixed coalesce-directory-components to remove :up sequences in
;; which :up is the second element.  Previously, it would give up, though it would
;; still reclaim conses properly.



;; jh, 3/27/92.  The function `canonicize-host-name-from-file-system'
;; canonicizes the host name on the Lispms and possibly others, eventually.
;; This is done implicitly in gensym-probe-file, but is needed for
;; gensym-directory.  Someday, we should abstract it better in case we ever
;; again deal with multiple-host file systems in the real world.

(defun-allowing-unwind canonicize-host-name-from-file-system (pathname)
  pathname)

;;; The function `supply-home-to-unix-pathname' destructively modifies its
;;; gensym-pathname argument, whose gensym-pathname-directory slot is assumed to
;;; contain a path-list whose car is :HOME.

(defun-allowing-unwind supply-home-to-unix-pathname (pathname)
  (protected-let ((home-directory-string?
		    (get-gensym-environment-variable #w"HOME")
		    (reclaim-text-string home-directory-string?)))
    (when home-directory-string?
      (let ((directory-length (lengthw home-directory-string?)))
	(when (>f directory-length 0)
	  (protected-let* ((already-terminated-p
			     (char=w
			       #.%\/
			       (charw home-directory-string?
				      (1-f directory-length))))
			   (terminated-home-directory-string
			     (if already-terminated-p
				 home-directory-string?
				 (tformat-text-string "~A/"
						      home-directory-string?))
			     (unless already-terminated-p
			       (reclaim-text-string 
				 terminated-home-directory-string)))
			   (home-directory-pathname
			     (gensym-pathname terminated-home-directory-string)
			     (reclaim-gensym-pathname
			       home-directory-pathname)))
	    (path-pop (gensym-pathname-directory pathname))
	    (setf (gensym-pathname-directory pathname)
		  (nconc (gensym-pathname-directory home-directory-pathname)
			 (gensym-pathname-directory pathname)))
	    (setf (gensym-pathname-directory home-directory-pathname)
		  nil)))))))

(defun-allowing-unwind maybe-supply-home-to-possible-unix-pathname (pathname)
  (when (and (eq (gensym-pathname-file-system pathname) 'unix)
	     (eq (first (gensym-pathname-directory pathname)) :home))
    (supply-home-to-unix-pathname pathname))
  pathname)





;; Note that these facilities are now used from Telewindows -- therefore they
;; must use notify-user-if-possible instead of notify-user, and assume very
;; little about their environment!  (MHD 4/17/91)

;; This needs to handle other error conditions, e.g. fs::file-error!! (MHD 2/27/91)




;;; Handling-gensym-file-errors

;;; handling-gensym-file-errors
;;;   &body body
;;;   => single value from last form in body, or nil if error occurred
;;; Reports any error messages to the logbook.
;;; ref: FILES
;;; notes: 
;;; Each facility does its own wrapping and is responsible for reclaimation.
;;; Consider cleaning up the g2-stream error layer.


(defvar inside-handling-gensym-file-errors-scope-p nil)
(defvar gensym-file-error-occurred-p nil)

(defmacro gensym-file-error-catch-tag ()
  `'gensym-file-error-catch-tag)

(defmacro handling-gensym-file-errors (&body body)
  (avoiding-variable-capture (&aux result-from-body)
    `(let ((inside-handling-gensym-file-errors-scope-p t)
	   (gensym-file-error-occurred-p nil))
       (let ((,result-from-body
	        (catch (gensym-file-error-catch-tag)
		  ,@body)))
	 (if gensym-file-error-occurred-p
	     (gensym-dstruct-bind
	         ((control-string . error-args)
		  ,result-from-body)
	       (let ((report-string
		       (prog1 
			 (apply
			   #'tformat-text-string
			   control-string
			   error-args)
			 (when ,result-from-body
			   (loop for error-arg in ,result-from-body
				 when (text-string-p error-arg)
				   do (reclaim-text-string error-arg)
				 finally
				 (reclaim-path-list ,result-from-body))))))
		 (notify-user-if-possible "~a" report-string)	; might be in Telewindows
		 (reclaim-text-string report-string))
	       nil)				; was not returning nil! -- fixed (MHD/jh 7/10/92)
	     ,result-from-body)))))

;; Consider returning a unique value (or values, e.g., the error string)!
;; (MHD 7/10/92)



;;; ignoring-gensym-file-errors
;;;   &body body
;;;   => single value from last form in body, or nil if error occurred
;;; ref: FILES
;;; note: 
;;; Each facility does its own wrapping and is responsible for reclaimation.

;;; The macro ignoring-gensym-file-errors traps all file-related exceptions.  If
;;; an error occurs, it returns nil; otherwise, it returns the first value that
;;; its body returns.

(defmacro ignoring-gensym-file-errors (&body body)
  (avoiding-variable-capture (&aux result-from-body)
    `(let ((inside-handling-gensym-file-errors-scope-p t)
	   (gensym-file-error-occurred-p nil))
       (let ((,result-from-body
	      (catch (gensym-file-error-catch-tag)
		,@body)))
	 (if gensym-file-error-occurred-p
	     nil
	     ,result-from-body)))))




;; The arguments-list in signal-gensym-file-error must be a list of path-conses,
;; which the handler will recycle.

(defun signal-gensym-file-error (file-error-string arguments-list)
  (cond (inside-handling-gensym-file-errors-scope-p
	 (setq gensym-file-error-occurred-p t)
	 (throw (gensym-file-error-catch-tag)
		(path-cons file-error-string arguments-list)))
	(t #+development
	   (cerror "Do a G2 Abort"
		   "SIGNAL-GENSYM-FILE-ERROR: no catcher for signal")
	   (let ((report-string
		   (apply #'tformat-text-string
			  file-error-string
			  arguments-list)))
	     (notify-user-if-possible "~a" report-string)
	     (reclaim-text-string report-string)
	     (when arguments-list
	       (loop for error-arg in arguments-list
		     when (text-string-p error-arg)
		       do (reclaim-text-string error-arg)
		     finally
		     (reclaim-path-list arguments-list)))
	     (abort)))))


;; jh per bah, 5/7/91.  Added the ability to supress development errors in
;; filename parsing.  
;; jh, 10/3/91.  Made it default to nil, since actual parser errors haven't been
;; seen in a while.

(defvar report-filename-parsing-errors-in-development-p nil)

;;; The function valid-pathname-p will return t if its argument can be converted
;;; into a pathname on the host file system, nil otherwise.  Borderline case: on
;;; file systems which accept multiple file syntax (like the lispms), namestrings
;;; which lack a host component or which contain a non-existent host component
;;; cannot be parsed.  In this case, valid-pathname-p will return nil.


(defun valid-pathname-p (convertible-thing)
  (let ((report-filename-parsing-errors-in-development-p nil))
    (cond ((equal convertible-thing nil) nil)
		 ( t (with-pathname-conversion 
        ((convertible-thing pathname?))
      (cond (pathname?
	     (reclaim-gensym-pathname pathname?)
	     t)
	    (t nil)))))))

;; Valid-directory-p checks for syntactic validity only.  This function does not
;; query the file system.  It is typically used in concert with
;; g2-stream-directory-p and g2-stream-probe-file.

(defmacro get-file-system-for-valid-directory-p (pathname)
  (if (eval-feature :development)
      `(or file-system-for-interception?
	   (gensym-pathname-file-system ,pathname))
      `(gensym-pathname-file-system ,pathname)))
    
(defun-allowing-unwind valid-directory-p (convertible-thing)
  (let ((report-filename-parsing-errors-in-development-p nil))
    (with-protected-pathname-conversion 
        ((convertible-thing pathname?))
      (when pathname? ; invalid pathname syntax means not valid directory
	(and (case (get-file-system-for-valid-directory-p pathname?)
	       (unix (gensym-pathname-name pathname?))
	       (vms (and (gensym-pathname-name pathname?)
			 (string-equalw (gensym-pathname-type pathname?) 
					#w"DIR")))
	       ((dos win32 generalized-dos) (gensym-pathname-name pathname?))
	       (otherwise nil))
	     t))))) ;don't return a reclaimed text-string

;; Gensym-wild-pathname-p ...  only checks name, type, and version, since
;; gensym-directory does not currently (1/7/92) support wild inferior directories,
;; wild host names, and the like.
  
(defun-allowing-unwind gensym-wild-pathname-p (convertible-thing)
  (with-protected-pathname-conversion ((convertible-thing pathname?))
    (if pathname?
	(macrolet ((wild-component-p (accessor)
		     (avoiding-variable-capture (&aux contents)
		       `(let ((,contents (,accessor pathname?)))
			  (if (text-string-p ,contents)
			      (wild-regular-expression-string-p ,contents)
			      (eq :wild ,contents))))))
	  (or (wild-component-p gensym-pathname-name)
	      (wild-component-p gensym-pathname-type)
	      (wild-component-p gensym-pathname-version)))
	nil)))



;;; convertible-thing => text-string functions

;;; Gensym-xxx-namestring functions

;;; All functions properly dispose of any intermediate gensym-pathname.  If
;;; convertible-thing is a g2-stream, returns name under which file was opened.
;;;   gensym-namestring:           everything
;;;   gensym-file-namestring:      file + type + version
;;;   gensym-directory-namestring: directory
;;;   gensym-host-namestring:      host
;;;   gensym-enough-namestring:    everything but the defaults
;;; ref: CLtL/2e pp644-5

(defmacro with-suppressed-pathname-components
	  (pathname supressed-components &body body)
  (if supressed-components
      (avoiding-variable-capture (pathname)
	(let ((old-names
		(loop for supressed-component in supressed-components
		      collect
			(make-symbol
			  (format nil "OLD-~a"
				  supressed-component)))))
	  `(let ,(loop for supressed-component in supressed-components
		       for old-name in old-names
		       collect
			 `(,old-name (,supressed-component ,pathname)))
	     (unwind-protect
	       (progn
		 ,@(loop for supressed-component in supressed-components
			 collect
			   `(setf (,supressed-component ,pathname) nil))
		 ,@body)
	       ,@(loop for supressed-component in supressed-components
		       for old-name in old-names
		       collect
			 `(setf (,supressed-component ,pathname) ,old-name))))))
      `(progn ,@body)))

;; jh, 10/28/91.  Added case where there are no supressed components to
;; with-suppressed-pathname-components.  In that case we don't need to set up
;; the unwind-protect.



;;; `Def-gensym-namestring-function' ... When also-define-text-string-variant?
;;; is true, this also defines a function returns the same result as the
;;; namestring function, except that it's converted to the Gensym character set.
;;; I.e., a function defined as follows:
;;;
;;;    (defun <name>-as-text-string (convertible-thing)
;;;      (let ((namestring (gensym-namestring convertible-thing)))
;;;        (prog1
;;; 	      (convert-ascii-filename-to-text-string-as-much-as-possible namestring)
;;;          (reclaim-text-string namestring))))

(defmacro def-gensym-namestring-function
    (name components-to-use &optional also-define-text-string-variant?)
  ;; Note that we don't need to use avoiding-variable-capture on any variables in
  ;; here, since they are all protected inside the defun.
  (let ((accessors-to-use
	  (loop for component in components-to-use
		collect 
		(intern 
		  (format nil "GENSYM-PATHNAME-~a" component)))))
    `(progn
     (defun-allowing-unwind ,name
	 (convertible-thing &optional (prefer-lowercase-p t))
       (with-protected-pathname-conversion
	   ((convertible-thing pathname?))
	 (if pathname?
	     (with-suppressed-pathname-components 
		 pathname?
		 ,(set-difference 
		    '(gensym-pathname-host 
		      gensym-pathname-device 
		      gensym-pathname-directory
		      gensym-pathname-name
		      gensym-pathname-type
		      gensym-pathname-version)
		    accessors-to-use)
	       (when (and (convert-file-strings-to-uppercase-p
			    (gensym-pathname-file-system pathname?))
			  prefer-lowercase-p)
		 ,@(loop for accessor in accessors-to-use
			 collect
			 (if (eq accessor 'gensym-pathname-directory)
			     `(loop for component in (,accessor pathname?)
				    do
				(when (text-string-p component)
				  (unless (wild-regular-expression-string-p
					    component)
				    (nstring-downcasew component))))
			     `(let ((component (,accessor pathname?)))
				(when (text-string-p component)
				  (unless (wild-regular-expression-string-p
					    component)
				    (nstring-downcasew component)))))))
	       (let ((internal-namestring
		       (funcall (gensym-pathname-namestring-generator pathname?)
				pathname?)))
		 internal-namestring))
	     (copy-constant-wide-string #w""))))
       ,@(when also-define-text-string-variant?
	   (let ((namestring '#:namestring))
	     `((defun ,(intern (format nil "~a-AS-TEXT-STRING" name))
		   (convertible-thing &optional (prefer-lowercase-p t))
		 (let ((,namestring
			  (,name convertible-thing prefer-lowercase-p)))
		   ,namestring))))))))	; Now generally considered ASCII
					;   No translation is needed now, since
					;   text strings are, as of 5.0, in
					;   Unicode, which is a superset of
					;   ASCII.  Later, handle other charsets
					;   besides ASCII, e.g., JIS (Japanese)
					;   (MHD 2/9/96)

;; jh, 2/9/94.  All gensym-xxx-namestring functions have an optional
;; prefer-lowercase-p argument that defaults to t.  This enables us to print
;; filenames in lowercase on those systems in which the actual namestrings are
;; stored in uppercase.  Since the majority of clients of the
;; gensym-xxx-namestring suite intend to show the resulting namestring to a
;; human, this is on the whole what we want.

;; A case where this is undesirable is when we are preparing a wildcarded
;; namestring to check a group of filenames we get from the operating system,
;; say if we are doing a directory search, to take a random example.  Here we
;; want to generate a namestring "as is" so that the proper regular expression
;; matching can ensue.  If such a string ends up being shown to the user, we can
;; explain that G2 has to convert to the file system's internal representation
;; when passing it wildcards.

;; So, I added a wild-regular-expression-string-p check before we downcase each
;; filename component as the result of the optional prefer-lowercase-p argument.
;; This retains non-wild components as lowercase for readability.  The downside
;; is that we reveal that the user's wildcard component might have been upcased,
;; as when a type component of "{kK}{bB}" is transformed to "{KK}{BB}" on those
;; file systems that store filenames internally as uppercase.  Again, we can
;; tell the user that G2 has to adhere to the way filenames are stored by the
;; host operating system, and in any event a lowercase character in the user's
;; wildcard specification would not match anything on such a file system.

;; Added the also-define-text-string-variant? option to the macro above, and
;; used it to eliminate the explicit defuns that were present here earlier
;; for the gensym-namestring and gensym-file-namestring variants, and used
;; it to define for the first time the gensym-directory-namestring variant.
;;
;; I guess we should document the following, which I have assumed: variants
;; may be freely added whenever needed. (MHD 6/7/94)

(def-gensym-namestring-function gensym-namestring 
				(host device directory name type version)
  t)

(defun-simple namestring-as-gensym-string (pathname)
  (let* ((namestring (gensym-namestring pathname))
	 (gensym-string (export-text-string namestring 'namestring-as-gensym-string)))
    (reclaim-wide-string namestring)
    gensym-string))

;; jh per mhd, 10/6/91.  Added optional argument to gensym-namestring to lowercase
;; filenames on systems where case doesn't matter.  More precisely, if
;; perfer-lowercase-p is true (the default) and the file system disregards
;; character case, then gensym-namestring will return a string consisting entirely
;; of lowercase characters.  Note that this is an extension to Common Lisp
;; behavior, or possibly a deviation, since this practice conflicts somewhat with
;; the :case keyword for gensym-pathnames (cf CLtL2e, p617 ff).  This is mainly to
;; make pathnames more readable and take up less space, but we will eventually
;; have to make a policy about how closely G2 obeys local file system conventions
;; and convey that policy to G2 users.

;; jh, 10/24/91.  Abstracted the creation of gensym-namestring functions, since it
;; is something we do every so often.  This has the added advantage of allowing us
;; to pass prefer-lowercase-p to any member of the suite.


(def-gensym-namestring-function gensym-file-namestring
				(name type version)
  t)


;; The functions gensym-device-namestring, gensym-base-namestring,
;; gensym-type-namestring, and gensym-version-namestring are provided for the G2
;; file i/o interface.  The interface is more homogeneous than that of Common
;; Lisp, and just wants to separate out the base file name, the type, and the
;; version, rather than concatenating them together as does Common Lisp.  jh,
;; 3/8/91.

(def-gensym-namestring-function gensym-host-namestring
				(host))

(def-gensym-namestring-function gensym-device-namestring
				(device))

(def-gensym-namestring-function gensym-directory-namestring
				(directory)
  t)

(def-gensym-namestring-function gensym-base-namestring
				(name))

(def-gensym-namestring-function gensym-type-namestring
				(type))

(def-gensym-namestring-function gensym-version-namestring
				(version))


(defun-allowing-unwind gensym-namestring-of-directory-as-file (pathname)
  (protected-let ((directory
		    (gensym-pathname-directory pathname))
		  (all-but-last-of-directory
		    (if (listp directory)
			(loop for len = (length directory)
			      for dn in directory
			      for i from 1
			      unless (=f i len)
				collect dn using gensym-cons)
			directory)
		    (when (consp all-but-last-of-directory)
		      (reclaim-gensym-list all-but-last-of-directory)))
		  (pathname-of-directory-as-file
		    (gensym-make-pathname
		      :host (gensym-pathname-host pathname)
		      :device (gensym-pathname-device pathname)
		      :directory all-but-last-of-directory
		      :name (when (consp directory)
			      (car (last directory))))
		    (reclaim-gensym-pathname pathname-of-directory-as-file)))
    (gensym-namestring pathname-of-directory-as-file)))
    




;;; Gensym-host-and-directory-namestring is necessary for those filesystems that
;;; need the host to parse the directory's delimiters correctly.  Curently these
;;; are only the Lisp machines.

(def-gensym-namestring-function gensym-host-and-directory-namestring
				(host directory))

(defun gensym-directory-and-wildcard-file-namestring 
       (convertible-thing &optional (prefer-lowercase-p t))
  (let ((host-and-directory-namestring
	  (gensym-host-and-directory-namestring 
	    convertible-thing
	    prefer-lowercase-p)))
    (prog1 (tformat-text-string 
	     "~a*.*"
	     host-and-directory-namestring)
	   (reclaim-text-string host-and-directory-namestring))))



;; jh, 5/28/91.  Added gensym-device-and-directory-namestring to make directory
;; access work on VMS.  Previously, we were only passing it the directory
;; component.

(def-gensym-namestring-function gensym-device-and-directory-namestring
				(device directory))

;; jh, 8/22/94.  Need the following for mhd's new editor filename-parsing
;; functionality.

(def-gensym-namestring-function gensym-directory-and-above-namestring
				(host device directory)
  t)

;; jh, 1/1/92.  Need the following for the new version wildcarding machinery.

(def-gensym-namestring-function gensym-name-and-type-namestring
				(name type))

;; jh, 8/6/93.  Added gensym-enough-namestring per a request of mhd.  Some
;; possible pitfalls: (1) although gensym-enough-namestring is the inverse of
;; gensym-merge-pathnames in the sense given on CLtL/2e p 645, it does not
;; invert each individual gensym-merge-pathname rule, and (2) if the original
;; directory is explicitly relative, as in "./lisp/hello.lisp", this will be
;; lost in the namestring.  Neither of these issues appear to be show-stoppers
;; at present.

;; jh, 8/22/94.  Issue (2) has been promoted in importance. because suppressing
;; the :relative token at the head of a directory is wrong in VMS.  It makes the
;; leading dot, which signifies a relative directory path, disappear.  On the
;; other hand, this is what we want to see in UNIX and DOS, since the initial
;; "./" or ".\" gets tedious.  So for now, we make a special case for VMS in
;; gensym-enough-namestring, since there does not appear to be any way outside
;; this function to create a directory whose first element is neither :absolute
;; nor :relative.  However, we should consider a more platform-independent
;; abstraction for what happens when the first element of a directory is neither
;; :absolute nor :relative.

(defun-allowing-unwind gensym-enough-namestring
    (convertible-thing
      &optional (default gensym-default-pathname-defaults))
  (with-protected-pathname-conversion
       ((convertible-thing pathname?)
	(default default-pathname?))
    (let ((file-system (and pathname? (gensym-pathname-file-system pathname?))))
      (if (and pathname?
	       default-pathname?
	       (eq file-system
		   (gensym-pathname-file-system default-pathname?)))
	  (macrolet ((unmerge-component
			 (component unmerge-remaining-components-p)
		       (let ((component-1 (intern (ab-lisp::format nil "~a1" component)))
			     (component-2 (intern (ab-lisp::format nil "~a2" component))))
			 `(cond ((gensym-pathname-contents-equal-p
				  ,component-1
				  ,component-2)
				 (when (text-string-p ,component-1)
				   (reclaim-text-string ,component-1))
				 (setf (,component pathname?) nil))
			        ((not ,unmerge-remaining-components-p)
				 (go provide-namestring))))))
	    (let ((convert-file-strings-to-uppercase-p
		   (convert-file-strings-to-uppercase-p file-system)))

	      ;; Canonicalize the directories before the comparison, and before
	      ;; we bind the structure slots to variables.
	      (coalesce-directory-components-in-place
		(gensym-pathname-directory pathname?))
	      (coalesce-directory-components-in-place
		(gensym-pathname-directory default-pathname?))

	      ;; The intent of the following form is to eliminate as many
	      ;; components of the pathname? gensym-pathname structure as we
	      ;; can, given the components of default-pathname?.  Excess
	      ;; components are reclaimed apropriately.
	      (with-multiple-pathname-components (pathname? default-pathname?)
		(tagbody
		   (unmerge-component gensym-pathname-host nil)

		   ;; jh, 8/6/93.  Consider applying the inverse of
		   ;; merge-pathnames-rule-1 here: If the host is missing, you
		   ;; needn't include the device in the "enough" namestring if
		   ;; it is the same as the default device for the file system.
		   ;; This doesn't work too well for the only file system where
		   ;; this currently matters (VMS), since there are several
		   ;; default devices from which to choose, so we won't do it
		   ;; just yet.
		   (unmerge-component gensym-pathname-device nil)

		   (let* ((first-directory-component1
			    (first gensym-pathname-directory1))
			  (absolute-marker-to-restore?
			    (and (eq first-directory-component1 :absolute)
				 (eq first-directory-component1
				     (first gensym-pathname-directory2))
				 first-directory-component1)))
		     (loop for component-1? = (car gensym-pathname-directory1)
			   for component-2? = (car gensym-pathname-directory2)
			   for number-of-components-dropped from 0
			   with reclaimable-components = nil
			   while (and (or component-1? component-2?)
				      (gensym-pathname-contents-equal-p
					component-1?
					component-2?))
			   do
		       (path-push (pop gensym-pathname-directory1)
				  reclaimable-components)
		       (pop gensym-pathname-directory2)
			   finally
			     (let ((remaining-directory?
				     (copy-list-using-path-conses
				       gensym-pathname-directory1)))
			       (loop for reclaimable-component
					 in reclaimable-components
				     when (text-string-p reclaimable-component)
				       do (reclaim-text-string
					    reclaimable-component)
					 finally
				       (reclaim-path-list
					 reclaimable-components))
			       (reclaim-path-list
				 (gensym-pathname-directory pathname?))
			       ;; jh, 8/6/93.  The following form suppresses
			       ;; explicit relative pathname prefixes.  See above
			       ;; note this date.
			       (loop while
				     (eq (car remaining-directory?) :relative)
				     do (path-pop remaining-directory?))
			       (setf (gensym-pathname-directory pathname?)
				     remaining-directory?)
			       (cond
				 (remaining-directory?
				  (when (and absolute-marker-to-restore?
					     (<=f number-of-components-dropped 1))
				    (path-push
				      :absolute
				      (gensym-pathname-directory pathname?)))
				  (when (and (eq (gensym-pathname-file-system
						   pathname?)
						 'vms)
					     (>=f number-of-components-dropped 1))
				    (path-push
				      :relative
				      (gensym-pathname-directory pathname?))))
				 (t (loop for count from 1
					    to (length gensym-pathname-directory2)
					  do
				      (path-push
					:up
					(gensym-pathname-directory
					  pathname?))))))))
		   (unmerge-component gensym-pathname-name t)
		   (unmerge-component gensym-pathname-type t)
		   (unmerge-component gensym-pathname-version t)

		 provide-namestring
		   (return-from gensym-enough-namestring
		     (gensym-namestring pathname?))))))
	  ""))))

;;; `Gensym-enough-namestring-as-text-string' returns the same result as
;;; gensym-enough-namestring, except that it's converted to the Gensym
;;; character set.

(defun gensym-enough-namestring-as-text-string 
    (convertible-thing
      &optional (default gensym-default-pathname-defaults))
  ;; no further translation needed now:   (MHD 2/9/96)
  (gensym-enough-namestring convertible-thing default))

#+development
(defparameter gensym-enough-namestring-validation-suite
  `(
    ;; Vanilla
    (("/home/jh/hello.text" "/home/jh/") "hello.text")
    (("/home/jh/hello.text" "/home/jh") "jh/hello.text")

    ;; Cousin directories
    (("/home/jh/lisp/hello.text" "/home/jh/lisp/clos/") "../hello.text")
    (("/home/jh/lisp/hello.text" "/home/jh/lisp/clos/mop/") "../../hello.text")

    ;; Cousin directories of relative pathnames
    (("home/jh/lisp/hello.text" "home/jh/lisp/clos/") "../hello.text")
    (("home/jh/lisp/hello.text" "home/jh/lisp/clos/mop/") "../../hello.text")

    ;; Relative vs absolute pathnames
    (("/home/jh/hello.text" "home/jh/clos/") "/home/jh/hello.text")
    (("home/jh/hello.text" "/home/jh/") "home/jh/hello.text")

    ;; Absolute pathnames with no commonality.
    (("/usr/bizarre-twist/guide-4-0/xy.kb" "/home/mhd/")
     "/usr/bizarre-twist/guide-4-0/xy.kb")

    ;; Canonicalizing directory components
    (("/home/jh/lisp/../greetings/hello.text" "/home/jh/")
     "greetings/hello.text")

    ;; Eliminating components lower than directory (e.g. type)
    (("mhd/foo/far.lisp" "mhd/foo.lisp") "foo/far")
    ))

#+development
(defun validate-gensym-enough-namestring (&optional verbose-p)
  (loop for ((arg1 arg2) expected-result)
	    in gensym-enough-namestring-validation-suite
	with succeeded-p = t
	do
    (let* ((result (gensym-enough-namestring arg1 arg2))
	   (matches-p (equal result expected-result)))
      (reclaim-text-string result)
      (when verbose-p
	(format t "~&~:[!!! incorrect: ~;OK: ~]~
                   (gensym-enough-namestring ~s ~s)~%~
                   ~0@*~:[!!!~;~]~7t=> ~3@*~s~%~
                   ~0@*~:[!!!~7tbut expected ~4@*~s~%~;~]"
		matches-p
		arg1
		arg2
		result
		expected-result))
      (unless matches-p
	(setq succeeded-p nil)))
      finally (return succeeded-p)))

#+development
(defmacro with-memory-checking (&body forms)
  `(progn 
     (setq memory-comparison-alist nil)
     (compare-memory-allocation)
     ,@forms
     (compare-memory-allocation)))

#+development
(defun examine-enough-namestring-memory-use ()
  (with-memory-checking
    (validate-gensym-enough-namestring)))
      
  



;;; gensym-directory-as-file

;;; The function `gensym-directory-as-file' is an extension to the Gensym Common
;;; Lisp pathname analogues.  Given a thing coercible to a pathname, this
;;; function extracts the host, device, and directory components, and then
;;; converts them into a new pathname that represents the directory as a file.
;;; The intent is to allow the user to probe for the existence of a directory
;;; without forcing an intimate knowledge of the specific conventions of the
;;; file system.  If gensym-directory-as-file is unable to do the conversion, it
;;; returns nil.  The conversion will fail when the argument contains a a
;;; non-empty name, type, or version component, the argument cannot be coerced
;;; into a pathname, or when the file system doesn't represent directories as
;;; files at all.  Note that gensym-directory-as-file does not do any probing
;;; itself.  Thus this function is unable to determine the directory-file of a
;;; relative pathname with no other directory subcomponents than the :relative
;;; marker.

;;; Note that gensym-directory-as-file is more or less an inverse of
;;; gensym-file-as-directory.  Note also that this function performs a syntactic
;;; check only, for example, it does NOT verify that a pathname being presented
;;; as that of a UNIX directory, is actually such a directory in the current
;;; file system.  G2-stream-directory-p must be used for that purpose.

(defun-simple gensym-pathname-version-empty-p (pathname)
  (let ((version (gensym-pathname-version pathname)))
    (or (null version)
	(eq version :unspecific))))

(defun-allowing-unwind gensym-directory-as-file (convertible-thing)
  (with-pathname-conversion 
        ((convertible-thing pathname?))
    (when pathname?
      (cond 
	((or (gensym-pathname-name pathname?)
	     (gensym-pathname-type pathname?)
	     ;; consider using (not gensym-pathname-version-empty-p)
	     (gensym-pathname-version pathname?))
	 (reclaim-gensym-pathname pathname?)
	 (setq pathname? nil))
	(t (let ((directory-subcomponents 
		   (gensym-pathname-directory pathname?)))
	     (cond 
	       ((null directory-subcomponents)
		(setf (gensym-pathname-directory pathname?) 
		      (path-list :absolute)))
	       ((equal directory-subcomponents '(:absolute)))
	       ((equal directory-subcomponents '(:relative))
		(reclaim-gensym-pathname pathname?)
		(setq pathname? nil))
	       (t (unless (memq (car directory-subcomponents) 
				'(:absolute :relative))
		    (path-push :relative directory-subcomponents))
		  (let* ((pointer-to-last-subcomponent
			   (loop for subcomponent-cons 
				     on directory-subcomponents
				 when (null (cddr subcomponent-cons))
				   do (return subcomponent-cons)))
			 (last-subcomponent
			   (cadr pointer-to-last-subcomponent)))
		    (setf (cdr pointer-to-last-subcomponent) nil)
		    (case (gensym-pathname-file-system pathname?)
		      (unix (setf (gensym-pathname-name pathname?)
				  last-subcomponent))
		      (vms (setf (gensym-pathname-name pathname?)
				 last-subcomponent)
			   (setf (gensym-pathname-type pathname?)
				 (copy-constant-wide-string #w"DIR")))
		      ((dos win32 generalized-dos)
		       (setf (gensym-pathname-name pathname?)
			     last-subcomponent))
		      (otherwise (reclaim-gensym-pathname pathname?)
				 (setq pathname? nil))))))))))
	 pathname?))

;;; The function `gensym-file-as-directory' is an extension to the Gensym Common
;;; Lisp pathname analogues.  Given a thing coercible to a pathname that
;;; represents the directory as a file, this function returns a new
;;; gensym-pathname that represents that file as the final directory component
;;; of a gensym-pathname with empty name, type, and version components.  It is
;;; up to the caller of this function to reclaim the pathname it returns.  If
;;; the argument to gensym-file-as-directory cannot be coerced to a pathname
;;; representing a directory file (for instance "XYX.NONDIR" on VMS), this
;;; function will return nil.  Gensym-file-as-directory is useful in cases where
;;; gensym-pathnames must be merged in ways beyond the capabilities of
;;; gensym-merge-pathnames.

;;; Note that gensym-file-as-directory is more or less an inverse of
;;; gensym-directory-as-file.  Note also that this function performs a syntactic
;;; check only, for example, it does NOT verify that a pathname being presented
;;; as that of a UNIX directory, is actually such a directory in the current
;;; file system.  G2-stream-directory-p must be used for that purpose.

(defun gensym-file-as-directory (convertible-thing)
  (with-pathname-conversion 
      ((convertible-thing pathname?))
    (if pathname?
	(cond ((valid-directory-p pathname?)
	       (let ((final-directory-component
		       (case (gensym-pathname-file-system pathname?)
			 ((unix win32 dos) (gensym-file-namestring pathname?))
			 (otherwise
			  (copy-text-string
			    (gensym-pathname-name pathname?))))))
		 (setf (gensym-pathname-directory pathname?)
		       (nconc (gensym-pathname-directory pathname?)
			      (path-list final-directory-component)))
		 (let ((pathname-name 
			 (gensym-pathname-name pathname?)))
		   (when (text-string-p pathname-name)
		     (reclaim-text-string pathname-name))
		   (setf (gensym-pathname-name pathname?) nil))
		 (let ((pathname-type 
			 (gensym-pathname-type pathname?)))
		   (when (text-string-p pathname-type)
		     (reclaim-text-string pathname-type))
		   (setf (gensym-pathname-type pathname?) nil))
		 (let ((pathname-version
			 (gensym-pathname-version pathname?)))
		   (when (text-string-p pathname-version)
		     (reclaim-text-string pathname-version))
		   ;; jh, 1/20/95.  Following form loses :unspecific on
		   ;; versionless file systems like NT - review someday.
		   (setf (gensym-pathname-version pathname?) nil))
		 pathname?))
	      (t (reclaim-gensym-pathname pathname?)
		 nil))
	nil)))


;; jh, 10/1/92.  Added get-new-directory-pathname-dwim to acquire a directory
;; from a user-supplied text-string representing a pathname.  The "dwim" comes
;; from the fact that G2 must figure out whether the user is supplying a
;; directory, a pathname for a file that happens also to be a directory, or a
;; pathname for a non-directory file from which the directory components are to
;; be extracted.  If unable to construct a pathname, this function can return
;; nil.

;; The following are examples of how this function should behave.
;; user supplies             user means
;; -------------             ----------
;; "/home/jh/"               "/home/jh/"
;; "/home/jh"                "/home/jh/"
;; "/home/nondir"            "/home/"
;; "[HOME.JH]"               "[HOME.JH]"
;; "[HOME]JH.DIR"            "[HOME.JH]"
;; "[HOME]NONDIR.DIR"        "[HOME]"

;;; jh, 3/3/95.  Moved get-new-directory-pathname-dwim from FILE-SYSPROC, so it
;;; can be used by other products (like Telewindows).

(defun get-new-directory-pathname-dwim (new-directory-string)
  (let ((raw-pathname? (gensym-pathname new-directory-string)))
    (when raw-pathname?
      (let ((raw-pathname-name (gensym-pathname-name raw-pathname?))
	    (raw-pathname-type (gensym-pathname-type raw-pathname?)))	    
	(cond ((and (null raw-pathname-name)
		    (null raw-pathname-type)
		    (gensym-pathname-version-empty-p raw-pathname?))
	       raw-pathname?)
	      ((g2-stream-directory-p new-directory-string)
	       (prog1 (gensym-file-as-directory raw-pathname?)
		      (reclaim-gensym-pathname raw-pathname?)))
	      (t (let ((raw-pathname-version
			 (gensym-pathname-version raw-pathname?)))
		   (when (text-string-p raw-pathname-name)
		     (reclaim-text-string raw-pathname-name))
		   (setf (gensym-pathname-name raw-pathname?) nil)
		   (when (text-string-p raw-pathname-type)
		     (reclaim-text-string raw-pathname-type))
		   (setf (gensym-pathname-type raw-pathname?) nil)
		   (when (text-string-p raw-pathname-version)
		     (reclaim-text-string raw-pathname-version))
		   (setf (gensym-pathname-version raw-pathname?) nil)
		   raw-pathname?)))))))


	    
;;; convertible-thing => gensym-pathname functions

;;; gensym-pathname
;;;   convertible-thing => gensym-pathname
;;; Doesn't do defaulting.
;;; Doesn't signal error if can't locate file.
;;; Always returns a pathname
;;; ref: CLtL/2e pp638-639

(defun gensym-pathname (convertible-thing)
  (with-pathname-conversion 
      ((convertible-thing pathname?))
    (or pathname? (make-empty-gensym-pathname))))
 
    
;;; gensym-parse-namestring
;;;   convertible-thing host-text-string default-gensym-pathname 
;;;   => gensym-pathname
;;; Defaults enough to complete the parse (cf gensym-pathname and gensym-truename).
;;; Doesn't signal error if can't locate file.
;;; ref: CLtL/2e pp639-40

(defmacro substring-case (substring-key &body clauses)
  (avoiding-variable-capture (substring-key)
    `(cond ,@(loop for (match . actions) in clauses
		   when (text-string-p match)
		     collect
		     `((text-string-search
			 ,match ,substring-key
			 0		; :start2
			 ,(lengthw match)) ; :end2
		       ,@actions)
		   when (memq match '(t otherwise))
		     collect
		     `(t ,@actions)))))



;; Get-parser-from-host taks a string naming a host as its single argument.  It
;; returns three symbols pertinent to file operations involving this host: 
;;   (1) the filename parser, which converts namestrings to gensym-pathname
;;       structures,
;;   (2) the namestring generator, which converts gensym-pathname structures to
;;       namestrings in the appropriate syntax, and
;;   (3) a a symbol naming the file system used to make these conversions.
;; Get-parser-from-host returns nil if it is unable to determine this information
;; from the host.  Typically in this case the parser and generator for the local
;; file system are used.


(defun get-parser-from-host (host)
  ;; UNIX, Coral, and VMS systems can't parse filenames on
  ;; alien hosts.
  (declare (ignore host))
 (get-default-file-system-info)


  )



(defun get-parser-from-namestring (namestring)
  ;; UNIX, Coral, and VMS systems can't parse filenames on
  ;; alien hosts.
  (declare (ignore namestring))		; "namestring" was "host" (MHD 1/9/91)
  (get-default-file-system-info))

(defun parser-in-namestring-p (namestring)
  (declare (ignore namestring))
  nil)



;; Changed gensym-parse-namestring-function not to use read macros to determine
;; the local file system.  We are coalescing explorer and microexplorer binaries
;; and can no longer tell anything about the file system at compile time.  
;; jh per mhd, 2/8/91.


(defun-allowing-unwind gensym-parse-namestring-function
       (convertible-thing host default)
  (with-protected-pathname-conversion 
      ((default default-pathname?))
    (let ((host-for-conversion
	    (or host
		(and default-pathname?
		     (gensym-pathname-host default-pathname?)))))
      (multiple-value-bind (filename-parser namestring-generator)
	  (get-parser-from-host host-for-conversion)
	(unless filename-parser
	  (setq filename-parser
		(local-filename-parser))
	  (setq namestring-generator
		(local-namestring-generator)))
	(let ((pathname?
		(convert-to-gensym-pathname 
		  convertible-thing 
		  filename-parser
		  namestring-generator)))
	  (cond (pathname?
		 (setf (gensym-pathname-filename-parser pathname?)
		       filename-parser)
		 (setf (gensym-pathname-namestring-generator pathname?)
		       namestring-generator)
		 pathname?)
		(t (make-empty-gensym-pathname))))))))



(defmacro gensym-parse-namestring
       (convertible-thing &optional host defaults)
  `(gensym-parse-namestring-function
     ,convertible-thing
     ,host
     ,defaults))



;;; gensym-truename
;;;   convertible-thing => gensym-pathname
;;; Doesn't do defaulting.
;;; Signals error if it can't locate actual file by throwing inside
;;; handling-gensym-file-errors.  For example, does this when convertible-thing is
;;; a gensym-pathname with a :wild component.
;;; ref: CLtL/2e p639




(defun-allowing-unwind gensym-truename (convertible-thing)
  (if (g2-stream-p convertible-thing)
      (let ((pathname-from-stream?
	      (gensym-probe-file convertible-thing)))
	(or pathname-from-stream?
	    (signal-gensym-file-error
	      "GENSYM-TRUENAME: Cannot get pathname from stream ~a"
	      (path-list convertible-thing))))
      (with-protected-pathname-conversion
	  ((convertible-thing pathname?))
	(if pathname?
	    (let ((probed-pathname?
		    (gensym-probe-file pathname?)))
	      (or probed-pathname?
		  (signal-gensym-file-error
		    "GENSYM-TRUENAME: Cannot access file ~a"
		    (path-list convertible-thing))))
	    (signal-gensym-file-error
	      "GENSYM-TRUENAME: Cannot obtain pathname for ~a"
	      (path-list convertible-thing))))))

;; jh, 5/17/91.  Changed gensym-truename to check in the outside file system for
;; the file, as specified in CLtL/2e p 639.  Previously all it took for success
;; was a successful parse of the namestring.

;; jh, 5/20/91.  Changed gensym-truename to provide a gensym-pathname when given
;; an open stream as argument.  This behavior is not mandatory (see CLtL/2e p639).
;; It does, however, make things a lot easier for facilities (like the screen
;; printer) which need multiple streams open to different versions of the same
;; filename.

;;; gensym-merge-pathnames
;;;   convertible-thing 
;;;     &optional default-convertible-thing version-symbol-or-integer
;;;   => gensym-pathname
;;; Does defaulting (obviously).
;;; Caller must reclaim all gensym-pathname structures passed to this function.
;;; ref: CLtL/2e p641


;;; The algorithm for pathname merging is taken from Common Lisp: The Language,
;;; second edition (p 642).  We implement them as separate rules in case our
;;; understanding of this standard changes or in case we encounter borderline cases
;;; in some file systems.  The rules are kept in the list merge-pathname-rules,
;;; which is sorted once at load time.  It is a very bad idea to use this list
;;; directly.  Instead, if you want to introduce changes to the merge-pathname
;;; rules, set the list to nil and evaluate ALL of the def-merge-pathnames-rule
;;; forms that are to be in effect.


(eval-when (:compile-toplevel :load-toplevel :execute)

(defvar merge-pathnames-rules nil)
(defvar merge-pathnames-rules-sorted-p nil)

) ; end of eval-when for merge-pathname-rules



(defun transfer-gensym-pathname-contents (old-contents new-contents)
  (cond ((consp old-contents)
	 (loop for old-component in old-contents
	       when (text-string-p old-component)
		 do
		 (reclaim-text-string old-component)
	       finally
	       (reclaim-path-list old-contents)))
	((text-string-p old-contents)
	 (reclaim-text-string old-contents)))
  (cond ((consp new-contents)
	 (loop for new-component in new-contents
	       collect
	       (if (text-string-p new-component)
		   (copy-text-string new-component)
		   new-component)
	       using path-cons))
	;; We don't have to worry about case conversion here, since
	;; this is called inside the scope of a with-pathname-conversion,
	;; which does case conversion both when it parses namestrings and
	;; when it copies already-existing pathnames.
	((text-string-p new-contents)
	 (copy-text-string new-contents))
	(t new-contents)))



(defmacro def-merge-pathnames-rule 
	  (name order 
	   &key when then otherwise finally pathname-components component-exceptions)
  (let ((rule-function-name 
	  (intern (format nil "MERGE-PATHNAMES-~a" name))))
    `(progn
       (declare-funcallable-symbol ,rule-function-name)
       (defun ,rule-function-name
	      (original-pathname pathname 
	       &optional defaults default-version)
	 ,@(ignoring-variables-appropriately (default-version original-pathname)
	     `((macrolet ((setf-pathname-contents (old-location new-contents)
			    (avoiding-variable-capture (&aux old-contents)
			      `(let ((,old-contents ,old-location))
				 (setf ,old-location
				       (transfer-gensym-pathname-contents
					 ,old-contents
					 ,new-contents))))))
		 ,@(if pathname-components
		       (loop for component in pathname-components
			     for accessor
				 = (intern 
				     (format nil 
				       "GENSYM-PATHNAME-~a" 
				       component))
			     for component-exception =
				 (getf component-exceptions component)
			     collect
			     (subst accessor
				    'gensym-pathname-component
				    `(,(if otherwise 'if 'when)
				        ,(if component-exception
					     `(and ,when 
						   (not ,component-exception))
					     when)
				      ,then
				      ,@(if otherwise (list otherwise))))
			     when finally ;finally is not a loop keyword here
			       collect
				 (subst accessor 'pathname-component finally))
		       `((,(if otherwise 'if 'when) ,when
			  ,then
			  ,@(if otherwise (list otherwise)))
			 ,@(if finally (list finally))))))))
       (pushnew (cons ,order ',rule-function-name)
		merge-pathnames-rules
		:key #'cdr
		:test #'equal))))

;; CLtL/2e: p 642: 

;; "If the given pathname explicitly specifies a host and does not supply a
;; device, then if the host component of the defaults matches the host component
;; of the given pathname, then the device is taken from the defaults; otherwise
;; the device will be the default file device for that host."

(defun get-default-file-device-from-host (pathname)
  (declare (ignore pathname))
  nil) ;just a stub for now


(def-merge-pathnames-rule device-default-rule 0
  :when
  (and (gensym-pathname-host original-pathname)
       (null (gensym-pathname-device original-pathname))
       (string=w (gensym-pathname-host original-pathname)
		 (gensym-pathname-host defaults)))
  :then
  (setf-pathname-contents (gensym-pathname-device pathname)
			  (gensym-pathname-device defaults))
  :otherwise
  (when (and (gensym-pathname-host original-pathname)
	     (null (gensym-pathname-device original-pathname)))
    (unless (eq (gensym-pathname-device original-pathname) :unspecific)
      (setf-pathname-contents 
	(gensym-pathname-device pathname)
	(get-default-file-device-from-host original-pathname)))))

;; jh, 10/17/91.  Added tests for explicit host and :unspecific to
;; device-default-rule.  See replace-empty-components for an explanation of the
;; former.  The latter is propably not the final place for this abstraction.



;; The propagate-file-system merge-pathnames rule is not from Common Lisp, but
;; helps to ensure that case conversion occurs by propagating parsers and
;; generators wherever possible.

(def-merge-pathnames-rule propagate-file-system 1
  :when (null (gensym-pathname-host original-pathname))
  :then (setf (gensym-pathname-file-system pathname)
	        (gensym-pathname-file-system defaults)
	      (gensym-pathname-filename-parser pathname)
	        (gensym-pathname-filename-parser defaults)
	      (gensym-pathname-namestring-generator pathname)
	        (gensym-pathname-namestring-generator defaults)))
 


;;It turns out that replace-unspecific-host is actually counter to the common
;;lisp specification, in that :unspecific is not supposed to be replaced by the
;;defaults.  However, :unspecific is not supposed to be used if the host
;;component has a meaning for the platform.  So, I could have made the change by
;;turning :unspecific into nil, but there are a hundred lines of test data which
;;would also have to have been changed in file-parse.lisp, and this seemed
;;cleaner, at least until I read the spec.  I'm doing it this way anyway.
;;yduJ, 10/9/05
(def-merge-pathnames-rule replace-unspecific-host 2
  :when (and (eq (gensym-pathname-host original-pathname) :unspecific)
	     (not (null (gensym-pathname-host defaults))))
  :then (setf-pathname-contents (gensym-pathname-host pathname)
				(gensym-pathname-host defaults)))



;; "Next, if the given pathname does not specify a host, device, directory, name,
;; or type, each such component is copied from the defaults."
 

(def-merge-pathnames-rule replace-empty-components 3
  :pathname-components (host device directory name type)
  :component-exceptions (device 
			  (or (gensym-pathname-host original-pathname)
			      (and (eq (gensym-pathname-file-system pathname) 'vms)
				   (gensym-pathname-directory original-pathname)))
			 directory
  			  (and (eq (gensym-pathname-file-system pathname) 'vms)
			       (gensym-pathname-device original-pathname))
			 )
  :when (null (gensym-pathname-component original-pathname))
  :then (setf-pathname-contents (gensym-pathname-component pathname)
				(gensym-pathname-component defaults)))

;; jh, 10/17/91.  Added :component-exceptions keyword to handle a
;; re-interpretation of the replace-empty-componehts rule.  It is now thought that
;; this rule applies to the gensym-pathname-device slot only if this wasn't
;; already filled by the device-default-rule.  The reasoning is as follows.
;; Consider a pathname which explicitly specifies a host and lacks a device, and
;; suppose merge-pathnames is passed an optional defaults argument with a
;; different host and in which the device is present.  The device-default-rule
;; will fail to give that device to the pathname, but the replace-empty-components
;; rule will blindly copy the device anyway, unless we make the exception above.

;; jh, 11/15/91.  Although the Common Lisp filename system addresses the issue of
;; platform-independent logical pathnames, it doesn't allow for platform-specific
;; expansion of logical filenames.  VMS, with its elaborate logical name facility,
;; therefore falls outside the Common Lisp model.  This facility does textual
;; replacements on the device and directory components of a filename at points in
;; the file-naming process that are outside the control of gensym-merge-pathnames
;; (for example, when a file is opened).  Besides, completely expanding a logical
;; name and working with the resulting pathname is counter-intuitive to VMS users.

;; After a talk with Jon Anthony, it seems the right thing to do is to abandon all
;; attempts at generating merge-pathnames rules for device and directory
;; components in VMS pathnames.  Instead, if the file system of a gensym-pathname
;; is VMS and it has a device or directory component, we will not merge the
;; default device and directory components into that pathname.  If the pathname is
;; devoid of both device and directory, we will get these from the default after
;; all.  This is implemented by modifying :component-exceptions in the
;; replace-empty-components merge-pathnames-rule.  Also had to change
;; augment-pathname-from-file-system in this file to get desired results.



;; "If the pathname doesn't specify a name, then the version, if not provided,
;; will come from the defaults, just like the other components.  However, if the
;; pathname does specify a name, then the version is not affected by the defaults.
;; ...  Finally, if this process leaves the version missing, the default version
;; is used."

(def-merge-pathnames-rule version-default-rule 4
  :when
  (and (null (gensym-pathname-version original-pathname))
       (null (gensym-pathname-name original-pathname)))
  :then
  (setf-pathname-contents (gensym-pathname-version pathname)
			  (gensym-pathname-version defaults))
  :finally
  (when (null (gensym-pathname-version pathname))
    (setf-pathname-contents 
      (gensym-pathname-version pathname)
      default-version)))


;; The merge-structured-directories merge-pathnames-rule is not from Common Lisp,
;; though structured pathnames are discussed on p 620ff of CLtL/2e.  This rule is
;; important so the user working in UNIX can load in KBs with names like
;; "../sisterdir/analogous.kb".  jh, 11/14/91.

(defun elide-directory-containing-up-with-default-directory
       (directory-containing-up default-directory)
  (let ((reversed-copy-of-default-directory?
	  (nreverse (copy-directory-contents default-directory))))
    (loop for directory-component in directory-containing-up
	  while (and (eq directory-component :up)
		     reversed-copy-of-default-directory?
		     (text-string-p (car reversed-copy-of-default-directory?)))
	  do
      (path-pop directory-containing-up)
      (reclaim-text-string (path-pop reversed-copy-of-default-directory?))
	  finally
	    (return
	      (nconc (nreverse reversed-copy-of-default-directory?)
		     directory-containing-up)))))

;; jh, 3/9/94.  Enhanced elide-directory-containing-up-with-default-directory to
;; collapse multiple occurrences of :up in the original directory with multiple
;; components of the default directory.

(def-merge-pathnames-rule merge-structured-directories 5
  :when
  (and (gensym-pathname-directory original-pathname)
       (memq (car (gensym-pathname-directory pathname)) '(:up :relative)))
  :then
  (let ((directory-so-far (gensym-pathname-directory pathname))
	(default-directory? (gensym-pathname-directory defaults)))
    (when default-directory?
      (gensym-dstruct-bind ((first-component second-component)
			   directory-so-far)
	(cond ((and (eq first-component :relative)
		    (eq second-component :up))
	       (path-pop directory-so-far)
	       (setf (gensym-pathname-directory pathname)
		     (elide-directory-containing-up-with-default-directory
		       directory-so-far
		       default-directory?)))
	      ((eq first-component :up)
	       (setf (gensym-pathname-directory pathname)
		     (elide-directory-containing-up-with-default-directory
		       directory-so-far
		       default-directory?)))	      
	      ((eq first-component :relative)
	       (path-pop directory-so-far)
	       (let ((default-directory-section-to-merge
		       (copy-directory-contents default-directory?)))
		 (setf (gensym-pathname-directory pathname)
		       (nconc default-directory-section-to-merge
			      directory-so-far)))))))))

#+development
(defparameter test-data-for-merge-structured-directories
  '(
    ((gensym-namestring (gensym-merge-pathnames "y" "z/"))             "./z/y")
    ((gensym-namestring (gensym-merge-pathnames "x/y" "z/"))           "./z/x/y")
    ((gensym-namestring (gensym-merge-pathnames "../x/y" "z/"))        "./x/y")
    ((gensym-namestring (gensym-merge-pathnames "../../x/y" "z/"))     "./../x/y")
    ((gensym-namestring (gensym-merge-pathnames "../../x/y" "z/w/"))   "./x/y")
    ((gensym-namestring (gensym-merge-pathnames "../../x/y" "z/w/p/")) "./z/x/y")
    ))

#+development
(defun validate-merge-structured-directories ()
  (let ((bad-forms nil))
    (loop for (form expected-result)
	      in test-data-for-merge-structured-directories
	  do
      (let ((result (eval form)))
	(unless (equal result expected-result)
	  (push form bad-forms))))
    (if bad-forms
	(values nil bad-forms)
	(values t nil))))

;; jh per mhd, 3/9/94.  Added a test to the merge-structured-directories
;; merge-pathnames rule to prevent re-merging a relative default directory into
;; the directory component of the merged pathname if that component was already
;; supplied by the replace-empty-components rule.  E.g., before this fix
;;   (gensym-namestring (gensym-merge-pathnames "a" "b/") => "./b/b/a"
;; while after the fix
;;   (gensym-namestring (gensym-merge-pathnames "a" "b/") => "./b/a"	 

;; The following form must follow all the def-merge-pathnames-rule forms in the
;; system:

(eval-when (:compile-toplevel :load-toplevel :execute)

(as-atomic-operation
  (setq merge-pathnames-rules 
          (sort merge-pathnames-rules #'< :key #'car)
	merge-pathnames-rules-sorted-p
          t))
)


(defun gensym-merge-pathnames-after-conversion
       (pathname 
	&optional defaults default-version)
  (let* ((convert-file-strings-to-uppercase-p nil)
	 (original-pathname
	   (copy-gensym-pathname pathname)))
    (loop for (nil . merge-pathnames-rule) in merge-pathnames-rules
	  do
	  (funcall-symbol merge-pathnames-rule 
	    original-pathname
	    pathname
	    defaults 
	    default-version))
    (reclaim-gensym-pathname original-pathname)
    pathname))

;; jh, 10/17/91.  Added another argument, original-pathname, to the merge-pathname
;; rules called by gensym-merge-pathnames-after-conversion.  This is necessary
;; because some rules refer to the contents of the original pathname and some
;; refer to contents which have been modified by preceding rules.



;;; Nota Bene: gensym-merge-pathnames follows Common Lisp specifications and always
;;; returns a new gensym-pathname structure (CLtL/2e p641).  It is the responsibility
;;; of the caller to reclaim any gensym-pathname passed to gensym-merge-pathnames.

;; Note: The actual Common Lisp analogue, gensym-merge-pathnames, is a macro which
;; must appear at the beginning of this file because of definitional dependencies.

;; Changed gensym-merge-pathnames-function to derive the filename parser from args
;; that are already gensym-pathnames.  This is only a problem on Lisp Machines
;; right now, but could change as true "open architectures" are able to read
;; several file systems.  We should be ready for this, hence the extra layer of
;; complexity.  jh, 1/9/91.

;; Changed with-pathname-conversion-for-merge so it doesn't try to determine the
;; local file system at compile time.  We are coalescing explorer and
;; microexplorer binaries and can no longer tell anything about the local file
;; system at compile time.  jh per mhd, 2/8/91.

(defmacro with-pathname-conversion-for-merge
	  (((original-pathname-var converted-pathname-var)
	    (original-default-var converted-default-var))
	   &body body)

  (let* ((binding-vars
	   (list original-pathname-var converted-pathname-var
		 original-default-var converted-default-var))
	 (non-symbolic-binding-vars
	   (remove-if #'symbolp binding-vars)))

    (when non-symbolic-binding-vars
      (error "WITH-PATHNAME-CONVERSION-FOR-MERGE:~%~
              variables in binding specs must be exclusively symbols, not:~%~
              ~{~a~%~}"
	     non-symbolic-binding-vars)))

    (avoiding-variable-capture 
      (&aux filename-parser namestring-generator
	    default-filename-parser default-namestring-generator)

      `(let (,filename-parser ,namestring-generator
	     ,default-filename-parser ,default-namestring-generator)

	 ;; get the parser and generator for the pathname to merge
	 (cond 
	   ((gensym-pathname-p ,original-pathname-var)
	    (setq ,filename-parser
		  (gensym-pathname-filename-parser 
		    ,original-pathname-var))
	    (setq ,namestring-generator
		  (gensym-pathname-namestring-generator 
		    ,original-pathname-var)))
	   ((and (text-string-p ,original-pathname-var)
		 (parser-in-namestring-p ,original-pathname-var))
	    (multiple-value-setq 
	        (,filename-parser ,namestring-generator)
	      (get-parser-from-namestring ,original-pathname-var)))
	   ((gensym-pathname-p ,original-default-var)
	    (setq ,filename-parser
		  (gensym-pathname-filename-parser 
		    ,original-default-var))
	    (setq ,namestring-generator 
		  (gensym-pathname-namestring-generator
		    ,original-default-var)))
	   ((and (text-string-p ,original-default-var)
		 (parser-in-namestring-p ,original-default-var))
	    (multiple-value-setq
	      (,filename-parser ,namestring-generator)
	      (get-parser-from-namestring ,original-default-var)))
	   (t (setq ,filename-parser (local-filename-parser))
	      (setq ,namestring-generator (local-namestring-generator))))

	 ;; get the default parser and generator
	 (cond ((gensym-pathname-p ,original-default-var)
		(setq ,default-filename-parser
		      (gensym-pathname-filename-parser 
			,original-default-var))
		(setq ,default-namestring-generator 
		      (gensym-pathname-namestring-generator
			,original-default-var)))
	       ((and (text-string-p ,original-default-var)
		     (parser-in-namestring-p ,original-default-var))
		(multiple-value-setq
		  (,default-filename-parser ,default-namestring-generator)
		  (get-parser-from-namestring ,original-default-var)))
	       (t (setq ,default-filename-parser ,filename-parser)
		  (setq ,default-namestring-generator ,namestring-generator)))

	 ;; bind the converted variables
	 (let* ((convert-file-strings-to-uppercase-p
		  (convert-file-strings-to-uppercase-p ,filename-parser))
		(,converted-pathname-var
		   (convert-to-gensym-pathname-with-known-parser
		     ,original-pathname-var
		     ,filename-parser
		     ,namestring-generator)))
	   (protected-let ((,converted-default-var
			      (convert-to-gensym-pathname-with-known-parser
				,original-default-var
				,default-filename-parser
				,default-namestring-generator)
			      (reclaim-gensym-pathname ,converted-default-var)))
	     ,@body)))))



(defun-allowing-unwind gensym-merge-pathnames-function
       (convertible-thing default default-version)
  (with-pathname-conversion-for-merge 
      ((convertible-thing pathname?)
       (default default-pathname?))
    (cond ((and pathname? default-pathname?)
	   (gensym-merge-pathnames-after-conversion 
	     pathname? ;will be modified and old contents reclaimed
	     default-pathname?
	     default-version))
	  (pathname?
	   (gensym-merge-pathnames-after-conversion
	     pathname? ;will be modified and old contents reclaimed
	     gensym-default-pathname-defaults
	     default-version))
	  (t (make-empty-gensym-pathname)))))





;;; Make-absolute-pathname-if-possible ... 

;;; For example, in development at Gensym, (make-absolute-pathname-if-possible "foo.kb")
;;; in a freshly loaded G2 should return the pathame whose namestring is
;;; "ma:>ab>foo.kb".

(defun-allowing-unwind make-absolute-pathname-if-possible (filename)
  (current-system-case
    (gsi filename nil)
    (t
      (if (gensym-pathname-p process-specific-system-pathname)
	  (protected-let*
	      ((pathname-of-filename 
		 (gensym-pathname filename)
		 (reclaim-gensym-pathname pathname-of-filename))
	       (pathname-for-namestring
		 (gensym-make-pathname 
		   :defaults process-specific-system-pathname
		   :name (gensym-pathname-name pathname-of-filename)
		   :type (gensym-pathname-type pathname-of-filename))
		 (reclaim-gensym-pathname pathname-for-namestring)))
	    (gensym-namestring pathname-for-namestring))
	  filename))))

;; Dropped in here by MHD -- replaces make-kfep-dictionary-pathname-if-possible,
;; which was in KFEP2 because I needed it for Telewindows.  JRH: please review.
;; (MHD 4/17/91)




;;; Miscellaneous File Access Facilities



;; jh, 11/10/91.  Added make-wild-name-and-type-pathname so we can get UNIX files
;; with no extension.  Not sure this is at the right level of abstraction: another
;; possibility would be to make the namestring generator do the right thing when
;; it gets a :wild name component and a nil type component.  Common Lisp punts on
;; detailed semantics of :wild in pathnames (CLtL/2e, p624), so we're on our own.

(defun make-wild-name-and-type-pathname (default-pathname)
  (case (gensym-pathname-file-system default-pathname)
    (unix (gensym-make-pathname :name :wild))
    ((win32 dos generalized-dos) (gensym-make-pathname :name :wild))
    (otherwise (gensym-make-pathname :name :wild
				     :type :wild))))

;; jh, 1/19/95.  Added case for DOS-related fileysstems to
;; make-wild-name-and-type-pathname, which will eventuate in the wildcard
;; expression "*" rather than "*.*".  On DOS-related filesystems, the "*"
;; wildcard grabs both files and directories, even though directories are not
;; "really" stored as files, and even though the "DIR" command on the NTs makes
;; the names of directories look like "XXX.DIR".  The "*.*" wildcard only grabs
;; "real" files.

;;; The fuction `make-canonical-wild-directory-pathname-if-possible' helps
;;; files-in-directory and subdirectories-in-directory behave properly when
;;; given a directory string that specifies the file used by the operating
;;; system to store directory information (e.g., "XXX.DIRECTORY" on the lispms,
;;; "XXX.DIR" on VMS, and anything with the correct format on UNIX.  It returns
;;; nil if it is unable to create such a pathname.

(defun-allowing-unwind make-canonical-wild-directory-pathname-if-possible
		       (directory-pathname directory-string)
  (cond 
    ;; Something with no name, type, or version was specified.  Supply wildcard
    ;; components.
    ((and (null (gensym-pathname-name directory-pathname))
	  (null (gensym-pathname-type directory-pathname))
	  (gensym-pathname-version-empty-p directory-pathname))
     (protected-let
         ((wild-pathname
	    (make-wild-name-and-type-pathname directory-pathname)
	    (reclaim-gensym-pathname wild-pathname)))
       (gensym-merge-pathnames directory-pathname wild-pathname)))

    ;; A file was specified, but that file is a directory.  Convert it to a
    ;; directory pathname and supply wildcard components.

    ;; jh, 2/10/94.  Not sure why the probe-file, and it is breaking the NT,
    ;; where directories are not files nohow (q.v. directory-exists-lisp-side in
    ;; FILE-SYSPROC).  Note that the VAX C implementation of fopen() (which is
    ;; what g2-stream-probe-file ends up calling) works somehow, even though
    ;; directories aren't exactly files on VMS either.
    ((and ;(g2-stream-probe-file directory-string)
	  (g2-stream-directory-p directory-string))
     (protected-let
         ((canonical-directory-pathname?
	    (gensym-file-as-directory directory-pathname)
	    (reclaim-gensym-pathname canonical-directory-pathname?)))
       (if canonical-directory-pathname?
	   (protected-let
	       ((wild-pathname
		  (make-wild-name-and-type-pathname 
		    canonical-directory-pathname?)
		  (reclaim-gensym-pathname wild-pathname)))
	     (gensym-merge-pathnames 
	       canonical-directory-pathname?
	       wild-pathname))
	   nil)))
    (t nil)))



;;; Some notes on the interface with g2-streams

;;; A list all-gensym-pathnames-containing-open-streams is maintained by the
;;; STREAMS module for use in conversion of g2-streams to gensym-pathnames.  The
;;; list is completely reclaimed when g2 shuts down (that is, whenever the list
;;; g2-stream-all-open-streams was completely reclaimed.) Individual conses in the
;;; list are reclaimed when a stream is closed.  Lisp Machines do not use this
;;; list, since we have to use their pathname and stream system anyway.

;;; The PATHNAMES module makes the assumption that g2-streams are represented as
;;; fixnums.  This should be abstracted soon.
;; jh, 4/26/96.  Finally, fixed.


;;; with-file-search-path <truename-var> <commonality-spec> <search-specs> 
;;;  &body <body>

;;; The macro `with-file-search-path' automates the common process of looking in
;;; several places for a file.  This macro executes <body> with <truename-var>
;;; bound to the first successful gensym-probe-file of a sequence of pathnames.
;;; Each pathname in this sequence is constructed by appending the pathname
;;; component specification in <commonality-spec> with successive component
;;; specifications in <search-specs>.  A pathname component specialization is a
;;; list of keyword-argument pairs suitable for gensym-make-pathname.  Note that
;;; the pathname components in <commonality-spec> are only evaluated once.

;;; The keyword :ditto may appear as the value of any pathname component in
;;; <search-specs>.  This means that the previous value is for that component is
;;; carried over into the current search.  This keyword enables
;;; with-file-search-path to perform various optimizations, such as caching
;;; directory contents to aid the case-insensitive search for file names on
;;; case-sensitive file systems like UNIX.

;;; For example, the form
;;;  (with-file-search-path module-truename? 
;;;                         (:name (get-next-module-name) :version :newest)
;;;    ((:type "KB" :defaults current-kb-pathname?)
;;;     (:type "KB" :defaults (gensym-launch-directory)
;;;     (:type "KL" :defaults :ditto)))
;;;    (if module-truename?
;;;        (prog1 (load-module module-truename?)
;;;               (reclaim-gensym-pathname module-truename?))
;;;        (notify-user "Unknown module")))
;;; will look in the current directory for KB files, and then will look in the
;;; launch directory, first for KB files, and finally for KL files.  If no file of
;;; the given :name is found, module-truename?  will be bound to nil.  Note that
;;; this form will only evaluate (get-next-module-name) once, which is probably
;;; what the user intends.  Further note that the :ditto keyword enables
;;; with-file-search-path to cache the results of any directory searches in
;;; (gensym-launch-directory), making the subsequent "KL" search more efficient.

;;; With-file-search-path takes care of reclaiming intermediate gensym-pathname
;;; structures.  If <truename-var> ends up being bound to a gensym-pathname, it is
;;; the responsibility of body to arrange to reclaim it.  Store-current-pathname
;;; (q.v.) might be useful in this regard.  It is also the responsibility of the
;;; user to reclaim any pathnames that are used as input to with-file-search-path,
;;; e.g., as an argument to the :defaults keyword in <commonality-spec> or
;;; <search-specs>.

;;; `Get-less-case-sensitive-gensym-pathname-given-directory' ...

(defun get-less-case-sensitive-gensym-pathname-given-directory 
       (gensym-pathname directory)
  (loop with name = (gensym-pathname-name gensym-pathname)	
	with type = (gensym-pathname-type gensym-pathname)
	with version = (gensym-pathname-version gensym-pathname)
	for truename in directory
	thereis
	  (and name
	       (gensym-pathname-name truename)
	       (string-equalw (gensym-pathname-name truename) name)
	       type
	       (gensym-pathname-type truename)
	       (string-equalw (gensym-pathname-type truename) type)
	       (let ((truename-version 
		       (gensym-pathname-version truename)))
		 (and (or (eql version truename-version)
			  
			  (and (memq-p-macro version '(nil :newest :unspecific))
			       (memq-p-macro truename-version '(nil :newest :unspecific)))
			  ;; -- replaces previous test: -- was inadequate for
			  ;; Windows/NT directories, wherein each pathname would
			  ;; normally have :unspecific, while gensym-pathname
			  ;; might have version = nil.  JH should review. (MHD 5/6/95)
			  
;                          (and (null version) 
;                               (eq truename-version :newest))
;                          (and (null truename-version)
;                               (eq version :newest))
			       )
		      (copy-gensym-pathname truename))))))

(defmacro with-file-search-path 
	  (truename-var pathname-commonality search-path-spec &body body)

  (avoiding-variable-capture 
      (&rest pathname-commonality ;only want this evaluated once
       &aux pathname exit-search
	    directory-namestring new-directory-namestring cached-directory
	    dittoed-host dittoed-device dittoed-directory dittoed-defaults
	    dittoed-name dittoed-type dittoed-version)

    (let ((dittoed-variables
	    (loop for pathname-spec in search-path-spec
		  with possible-dittoed-variables = nil
		  when (eq (getf pathname-spec :host) :ditto)
		    do (pushnew dittoed-host possible-dittoed-variables)
		  when (eq (getf pathname-spec :device) :ditto)
		    do (pushnew dittoed-device possible-dittoed-variables)
		  when (eq (getf pathname-spec :directory) :ditto)
		    do (pushnew dittoed-directory possible-dittoed-variables)
		  when (eq (getf pathname-spec :name) :ditto)
		    do (pushnew dittoed-name possible-dittoed-variables)
		  when (eq (getf pathname-spec :type) :ditto)
		    do (pushnew dittoed-type possible-dittoed-variables)
		  when (eq (getf pathname-spec :version) :ditto)
		    do (pushnew dittoed-version possible-dittoed-variables)
		  when (eq (getf pathname-spec :defaults) :ditto)
		    do (pushnew dittoed-defaults possible-dittoed-variables)
		  finally 
		    (return possible-dittoed-variables))))

      `(let ((,truename-var nil)
	     (,directory-namestring nil)
	     (,cached-directory 'directory-not-cached)
	     ,pathname 
	     ,new-directory-namestring
	     ,@dittoed-variables)

	 ;; return from this block when we have found a match
	 (prog ()
	   ,@(loop for pathname-spec in search-path-spec
		   for pathname-spec-cons on search-path-spec
		   for next-pathname-spec? = (cadr pathname-spec-cons)

		   for within-prog-p = nil then t

		   for host? = (getf pathname-spec :host)
		   for device? = (getf pathname-spec :device)
		   for directory? = (getf pathname-spec :directory)
		   for name? = (getf pathname-spec :name)
		   for type? = (getf pathname-spec :type)
		   for version? = (getf pathname-spec :version)
		   for defaults? = (getf pathname-spec :defaults)

		   for next-host? = (getf next-pathname-spec? :host)
		   for next-device? = (getf next-pathname-spec? :device)
		   for next-directory? = (getf next-pathname-spec? :directory)
		   for next-name? = (getf next-pathname-spec? :name)
		   for next-type? = (getf next-pathname-spec? :type)
		   for next-version? = (getf next-pathname-spec? :version)
		   for next-defaults? = (getf next-pathname-spec? :defaults)

		   for previous-host? = nil then host?
		   for previous-device? = nil then device?
		   for previous-directory? = nil then directory?
		   for previous-defaults? = nil then defaults?
		 
		   ;; searching-identical-directory-p locates situations where we
		   ;; know at compile time that we don't have to cache the
		   ;; directory contents
		   for searching-identical-directory-p = nil
		       then 
		       (and (or (eq host? :ditto)
				(and (constantp host?)
				     (equal host? previous-host?)))
			    (or (eq device? :ditto)
				(and (constantp device?)
				     (equal device? previous-device?)))
			    (or (eq directory? :ditto)
				(and (constantp directory?)
				     (equal directory? previous-directory?)))
			    (or (eq defaults? :ditto)
				(and (constantp defaults?)
				     (equal defaults? previous-defaults?))))
		   append
		   `(
		     ;; store the dittoed variables if any
		     ,@(if (eq next-host? :ditto)
			   `((setq ,dittoed-host ,host?)))
		     ,@(if (eq next-device? :ditto)
			   `((setq ,dittoed-device ,device?)))
		     ,@(if (eq next-directory? :ditto)
			   `((setq ,dittoed-directory ,directory?)))
		     ,@(if (eq next-name? :ditto)
			   `((setq ,dittoed-name ,name?)))
		     ,@(if (eq next-type? :ditto)
			   `((setq ,dittoed-type ,type?)))
		     ,@(if (eq next-version? :ditto)
			   `((setq ,dittoed-version ,version?)))
		     ,@(if (eq next-defaults? :ditto)
			   `((setq ,dittoed-defaults ,defaults?)))
		     
		     ;; form the pathname (handling :ditto appropriately)
		     (setq ,pathname 
			   (gensym-make-pathname
			     ,@pathname-commonality
			     ,@(loop for (component value) 
					 on pathname-spec by 'cddr
				     collect component
				     collect
				     (case component
				       (:host 
					(if (or (eq value :ditto)
						(eq next-host? :ditto))
					    dittoed-host
					    value))
				       (:device 
					(if (or (eq value :ditto)
						(eq next-device? :ditto))
					    dittoed-device
					    value))
				       (:directory
					(if (or (eq value :ditto)
						(eq next-directory? :ditto))
					    dittoed-directory
					    value))
				       (:name
					(if (or (eq value :ditto)
						(eq next-name? :ditto))
					    dittoed-name
					    value))
				       (:type
					(if (or (eq value :ditto)
						(eq next-type? :ditto))
					    dittoed-type
					    value))
				       (:version
					(if (or (eq value :ditto)
						(eq next-version? :ditto))
					    dittoed-version
					    value))
				       (:defaults
					(if (or (eq value :ditto)
						(eq next-defaults? :ditto))
					    dittoed-defaults
					    value))
				       (otherwise value)))))
		     
		     ;; arrange to cache the directory contents if necessary
		     ,@(cond 
			 (searching-identical-directory-p
			  nil)
			 (within-prog-p
			  `((when (eq (gensym-pathname-file-system ,pathname) 
				      'unix)
			      (setq ,new-directory-namestring 
				    (gensym-directory-and-wildcard-file-namestring
				      ,pathname))

			      ;; the cond checks at runtime that we truly do have
			      ;; to go to the trouble of caching a new directory.
			      (cond 
				((equal ,new-directory-namestring 
					,directory-namestring)
				 (reclaim-text-string 
					   ,new-directory-namestring))
				(t (when (consp ,cached-directory)
				     (reclaim-gensym-directory-results 
				       ,cached-directory))
				   ;; Directory-namestring can be nil if a
				   ;; previous pathname in the search path was
				   ;; non-UNIX.  Hence the apparently
				   ;; superfluous text-string-p test.
				   (when (text-string-p ,directory-namestring)
				     (reclaim-text-string ,directory-namestring))
				   (setq ,directory-namestring 
					 ,new-directory-namestring)
				   (setq ,cached-directory 
					 'directory-not-cached))))))
			 (t ;; entering the prog
			    `((when (eq (gensym-pathname-file-system ,pathname) 
					'unix)
				(setq ,directory-namestring
				      (gensym-directory-and-wildcard-file-namestring
					,pathname))))))
			     
		     ;; do the probing
		     (setq ,truename-var 
			   (gensym-probe-file ,pathname))
		   
		     ;; probe for a less case-sensitive name if necessary
		     (unless ,truename-var
		       (when (eq (gensym-pathname-file-system ,pathname) 'unix)
			 (when (eq ,cached-directory 'directory-not-cached)
			   (setq ,cached-directory 
				 (gensym-directory ,directory-namestring nil)))
			 (setq 
			   ,truename-var
			   (get-less-case-sensitive-gensym-pathname-given-directory
			     ,pathname
			     ,cached-directory))))

		     ;; reclaim the pathname (not the truename of course)
		     (reclaim-gensym-pathname ,pathname)

		     ;; exit the prog if we find a match
		     (when ,truename-var
		       (go ,exit-search))))

	   ,exit-search ;a prog label

	   (when ,directory-namestring
	     (reclaim-text-string ,directory-namestring))
	   (when (consp ,cached-directory)
	     (reclaim-gensym-directory-results ,cached-directory))
	   (return nil))

       ;; body is executed with truename-var setq'd apropriately
       ,@body))))

;; jh, 10/8/91.  Modified with-file-search-path to check UNIX directories for
;; case-sensitive analogues.  This makes it behave the way the search for KBs does
;; on these platforms.

;; jh, 10/18/91.  Improved with-file-search-path to cache UNIX directories only if
;; a straight probe-file did not work.  This should handle the large majority of
;; cases without having to do a gensym-directory, since strings are typically
;; typed in lower-case and symbols are down-cased as a matter of course.

;; jh, 10/30/91.  Changed gensym-host-and-directory-namestring to
;; gensym-directory-and-wildcard-file-namestring in with-file-search-path, since
;; the former doesn't give gensym-directory what it needs in UNIX.  We were
;; failing to do a wildcard search, and only matching files whose name is "".
;; This bug was not apparent in gensym-directory on the Lispm, where a namestring
;; with only a directory component will cause the wildcard search we need.

;; Testing with-file-search-path

;(defvar *p*) 
;(defvar *q*)
;(defun pretest ()
;  (setq *p* (gensym-pathname "nj:/usr/jh/foreign/xxx.kb"))
;  (setq *q* (gensym-pathname "nj:/usr/jh/yyy.kb")))

;(defun test (module-name) ;(test 'file-io)
;  (with-file-search-path
;    module-truename? 
;    (:name module-name :version :newest)
;    ((:type "kl" :defaults *p*)
;     (:type "kb" :defaults :ditto)
;     (:type "kl" :defaults *q*)
;     (:type "kb" :defaults :ditto))
;    module-truename?))




;;;; Pathname Support for KB Modularity



;;; Make-kb-pathname-from-module-name ... 

#+obsolete
(defun make-kb-pathname-from-module-name (module-name &optional default-pathname?)
  (with-file-search-path
    module-truename? 
    (:name module-name :version :newest)
    ((:type "kl" :defaults (or default-pathname? current-kb-pathname?))
     (:type "kb" :defaults :ditto)
     (:type "kl" :defaults process-specific-system-pathname)
     (:type "kb" :defaults :ditto))
    module-truename?))

;; This is made obsolete by search-for-module-truename, and friends, which are
;; now in KB-MERGE. Keep around for a while. (MHD 5/19/95)





;;; Make-module-name-from-kb-pathname ...

(defun make-module-name-from-kb-pathname (kb-pathname)
  (intern-text-string
    (nstring-upcasew
      (copy-text-string (gensym-pathname-name kb-pathname)))))



;;; `Merge-series-of-pathnames' produces a new gensym pathname by merging
;;; together the pathnames series-of-pathname.  Each element of
;;; series-of-pathname should be either nil or a gensym pathname.  Each pathname
;;; is processed in order, and any of its non-nil components are used to fill-in
;;; any null components remaining in the new pathname.  Note that a null element
;;; in series-of-pathnames is permitted primarily as a convenience, to ease
;;; construction of the list and also to ease debugging in certain cases.
;;;
;;; The conses of the argument list are neither reclaimed nor mutated by this
;;; function.  The resulting value is always a fresh gensym-pathname structure,
;;; reclamation of which is the responsibility of the caller.
;;;
;;; Note that (merge-series-of-pathnames nil) is equivalent to
;;; (gensym-make-pathname), which is equivalent to (gensym-parse-namestring "").

(defun merge-series-of-pathnames (series-of-pathnames)
  (loop for pathname?
	    = nil
	    then (pop series-of-pathnames)
	for result-so-far
	    = (gensym-make-pathname) ; all components nil
	    then (if pathname?
		     (prog1 (gensym-merge-pathnames
			      result-so-far
			      pathname?)
		       (reclaim-gensym-pathname result-so-far))
		     result-so-far)
	while series-of-pathnames
	finally (return result-so-far)))

;; This is not just used for modules.  In fact, this is called from some
;; functions used in TELEWINDOWS (for asian font file loading). By MHD.  Move
;; elsewhere?  (MHD 6/24/94)

;; Changed to allow NIL arguments, for easier tracing. -rh, 29-Sep-99






;;;; Validating gensym-pathname functions

;; be sure to test merging of both namestrings and gensym-pathnames to thoroughly
;; exercise the conversion machinery (this can be done in the harness function,
;; which after all has to be different from the standard one used to test
;; gensym-search inter alia.

#+development
(defun-allowing-unwind gensym-merge-namestrings
		       (namestring &optional default-namestring default-version)
  (protected-let ((original-pathname
		    (gensym-pathname namestring)
		    (reclaim-gensym-pathname original-pathname))
		  (default-pathname
		    (gensym-pathname default-namestring)
		    (reclaim-gensym-pathname default-pathname)))
    (gensym-merge-pathnames 
      original-pathname
      default-pathname
      default-version)))

#+development
(defun gensym-merge-pathnames-reclaiming-arguments 
       (original-pathname default-pathname)
  (prog1 (gensym-merge-pathnames original-pathname default-pathname)
	 (when (gensym-pathname-p original-pathname)
	   (reclaim-gensym-pathname original-pathname))
	 (when (gensym-pathname-p default-pathname)
	   (reclaim-gensym-pathname default-pathname))))


#+development
(defun gensym-merge-pathnames-reclaiming-first-argument
       (original-pathname default-pathname)
  (prog1 (gensym-merge-pathnames original-pathname default-pathname)
	 (when (gensym-pathname-p original-pathname)
	   (reclaim-gensym-pathname original-pathname))))

#+development
(defparameter gensym-merge-pathnames-validation-suite
  '(
    ;; device-default-rule (rule 0)
    ((gensym-merge-pathnames "bolton::[greetings]hello.there"
			     "bolton::dua0:[jh]hello.text")
     ("BOLTON" "DUA0" (:absolute "GREETINGS") "HELLO" "THERE" nil))
    ((gensym-merge-pathnames "bolton::[greetings]hello.there"
			     "ludlow::dua0:[jh]hello.text")
     ("BOLTON" nil (:absolute "GREETINGS") "HELLO" "THERE" nil))

    ;; propagate-file-system (rule 1, not CL)
    ((gensym-merge-pathnames "/usr/jh/hello.there"
			     "nj:/usr/greetings.default")
     ("nj" :unspecific (:absolute "usr" "jh") "hello" "there" nil))
    ((gensym-merge-pathnames ">usr>jh>hello.there"
			     "ma:>ab>greetings.default")
     ("MA" :unspecific (:absolute "USR" "JH") "HELLO" "THERE" nil))
    ((gensym-merge-pathnames "[usr.jh]hello.there"
			     "bolton::[ab]greetings.default")
     ("BOLTON" nil (:absolute "USR" "JH") "HELLO" "THERE" nil))

    ;; replace-empty-components (rule 2)
    ((gensym-merge-pathnames "ma:>ab>jh>"
			     "ma:>defaults>greetings.text")
     ("MA" :unspecific (:absolute "AB" "JH") "GREETINGS" "TEXT" nil))
    ((gensym-merge-pathnames "nj:/usr/jh/"
			     "ma:>defaults>greetings.text")
     ("nj" :unspecific (:absolute "usr" "jh") "GREETINGS" "TEXT" nil))
    ((gensym-merge-pathnames "bolton::[usr.jh]"
			     "bolton::[defaults]greetings.text")
     ("BOLTON" nil (:absolute "USR" "JH") "GREETINGS" "TEXT" nil))

    ;;version-default-rule (rule 3)
    ;; (a) if has no name, copy from default-pathname argument
    ((gensym-merge-pathnames "ma:>ab>jh>"
			     "ma:>defaults>greetings.text.32")
     ("MA" :unspecific (:absolute "AB" "JH") "GREETINGS" "TEXT" 32))
    ((gensym-merge-pathnames "nj:/usr/jh/"
			     "ma:>defaults>greetings.text.32")
     ("nj" :unspecific (:absolute "usr" "jh") "GREETINGS" "TEXT" 32))
    ((gensym-merge-pathnames "bolton::[usr.jh]"
			     "bolton::[defaults]greetings.text.32")
     ("BOLTON" nil (:absolute "USR" "JH") "GREETINGS" "TEXT" 32))

    ;; (b) if has a name, ignore version in default-pathname argument
    ((gensym-merge-pathnames "ma:>ab>jh>greetings.text.newest"
			     "ma:>defaults>greetings.default.32")
     ("MA" :unspecific (:absolute "AB" "JH") "GREETINGS" "TEXT" :newest))
    ((gensym-merge-pathnames "nj:/usr/jh/greetings.text~"
			     "ma:>defaults>greetings.default.newest")
     ("nj" :unspecific (:absolute "usr" "jh") "greetings" "text" :previous))
    ((gensym-merge-pathnames "bolton::[usr.jh]greetings.text.32"
			     "bolton::[defaults]greetings.text.23")
     ("BOLTON" nil (:absolute "USR" "JH") "GREETINGS" "TEXT" 32))

    ;; (c) if still no version, get it from the default-version argument
    ((gensym-merge-pathnames "ma:>ab>jh>greetings.text"
			     "ma:>defaults>greetings.default"
			     11)
     ("MA" :unspecific (:absolute "AB" "JH") "GREETINGS" "TEXT" 11))
    ((gensym-merge-pathnames "nj:/usr/jh/greetings.text"
			     "ma:>defaults>greetings.default"
			     22)
     ("nj" :unspecific (:absolute "usr" "jh") "greetings" "text" 22))
    ((gensym-merge-pathnames "bolton::[usr.jh]greetings.text"
			     "bolton::[defaults]greetings.text"
			     33)
     ("BOLTON" nil (:absolute "USR" "JH") "GREETINGS" "TEXT" 33))

    ;; device-default-rule (rule 0)
    ((gensym-merge-namestrings "bolton::[greetings]hello.there"
			       "bolton::dua0:[jh]hello.text")
     ("BOLTON" "DUA0" (:absolute "GREETINGS") "HELLO" "THERE" nil))
    ((gensym-merge-namestrings "bolton::[greetings]hello.there"
			       "ludlow::dua0:[jh]hello.text")
     ("BOLTON" nil (:absolute "GREETINGS") "HELLO" "THERE" nil))

    ;; propagate-file-system rule not applicable

    ;; replace-empty-components (rule 2)
    ((gensym-merge-namestrings "ma:>ab>jh>"
			       "ma:>defaults>greetings.text")
     ("MA" :unspecific (:absolute "AB" "JH") "GREETINGS" "TEXT" nil))
    ((gensym-merge-namestrings "nj:/usr/jh/"
			       "ma:>defaults>greetings.text")
     ("nj" :unspecific (:absolute "usr" "jh") "GREETINGS" "TEXT" nil))
    ((gensym-merge-namestrings "bolton::[usr.jh]"
			       "bolton::[defaults]greetings.text")
     ("BOLTON" nil (:absolute "USR" "JH") "GREETINGS" "TEXT" nil))
    ;; Test VMS special-casing
    ((gensym-merge-pathnames-reclaiming-arguments
       (parse-vms-filename "work.kl")
       (parse-vms-filename "jh$disk:[jh]john.kb"))
     (nil "JH$DISK" (:absolute "JH") "WORK" "KL" nil))
    ((gensym-merge-pathnames-reclaiming-arguments
       (parse-vms-filename "work.kl")
       (parse-vms-filename "jh$disk:john.kb"))
     (nil "JH$DISK" nil "WORK" "KL" nil))
    ((gensym-merge-pathnames-reclaiming-arguments
       (parse-vms-filename "jh$root:work.kl")
       (parse-vms-filename "jh$disk:[jh]john.kb"))
     (nil "JH$ROOT" nil "WORK" "KL" nil))
    ((gensym-merge-pathnames-reclaiming-arguments
       (parse-vms-filename "[usr.g2]work.kl")
       (parse-vms-filename "jh$disk:[jh]john.kb"))
     (nil nil (:absolute "USR" "G2") "WORK" "KL" nil))
    ((gensym-merge-pathnames-reclaiming-arguments
       (parse-vms-filename "[usr.g2]work.kl")
       (parse-vms-filename "jh$disk:john.kb"))
     (nil nil (:absolute "USR" "G2") "WORK" "KL" nil))
    ((gensym-merge-pathnames-reclaiming-arguments
       (parse-vms-filename "g2$root:[opt]work.kl")
       (parse-vms-filename "jh$disk:[jh]john.kb"))
     (nil "G2$ROOT" (:absolute "OPT") "WORK" "KL" nil))
    ((gensym-merge-pathnames-reclaiming-arguments
       (parse-vms-filename "g2$root:[opt]work.kl")
       (parse-vms-filename "jh$disk:john.kb"))
     (nil "G2$ROOT" (:absolute "OPT") "WORK" "KL" nil))

    ;;version-default-rule (rule 3)
    ;; (a) if has no name, copy from default-pathname argument
    ((gensym-merge-namestrings "ma:>ab>jh>"
			       "ma:>defaults>greetings.text.32")
     ("MA" :unspecific (:absolute "AB" "JH") "GREETINGS" "TEXT" 32))
    ((gensym-merge-namestrings "nj:/usr/jh/"
			       "ma:>defaults>greetings.text.32")
     ("nj" :unspecific (:absolute "usr" "jh") "GREETINGS" "TEXT" 32))
    ((gensym-merge-namestrings "bolton::[usr.jh]"
			       "bolton::[defaults]greetings.text.32")
     ("BOLTON" nil (:absolute "USR" "JH") "GREETINGS" "TEXT" 32))

    ;; (b) if has a name, ignore version in default-pathname argument
    ((gensym-merge-namestrings "ma:>ab>jh>greetings.text.newest"
			       "ma:>defaults>greetings.default.32")
     ("MA" :unspecific (:absolute "AB" "JH") "GREETINGS" "TEXT" :newest))
    ((gensym-merge-namestrings "nj:/usr/jh/greetings.text~"
			       "ma:>defaults>greetings.default.newest")
     ("nj" :unspecific (:absolute "usr" "jh") "greetings" "text" :previous))
    ((gensym-merge-namestrings "bolton::[usr.jh]greetings.text.32"
			       "bolton::[defaults]greetings.text.23")
     ("BOLTON" nil (:absolute "USR" "JH") "GREETINGS" "TEXT" 32))

    ;; (c) if still no version, get it from the default-version argument
    ((gensym-merge-namestrings "ma:>ab>jh>greetings.text"
			       "ma:>defaults>greetings.default"
			       11)
     ("MA" :unspecific (:absolute "AB" "JH") "GREETINGS" "TEXT" 11))
    ((gensym-merge-namestrings "nj:/usr/jh/greetings.text"
			       "ma:>defaults>greetings.default"
			       22)
     ("nj" :unspecific (:absolute "usr" "jh") "greetings" "text" 22))
    ((gensym-merge-namestrings "bolton::[usr.jh]greetings.text"
			       "bolton::[defaults]greetings.text"
			       33)
     ("BOLTON" nil (:absolute "USR" "JH") "GREETINGS" "TEXT" 33))

    ;; merge-structured-directories (rule 4)
    ;; Inserted parse-unix-filename because lispms can't take relative directories
    ;; across hosts.
    ((gensym-merge-pathnames-reclaiming-first-argument
       (parse-unix-filename "../gsi/skeleton.kb")
       "nj:/usr/jh/sysproc/")
     ("nj" :unspecific (:absolute "usr" "jh" "gsi") "skeleton" "kb" nil))
    ((gensym-merge-pathnames
       "bolton::[-.gsi]skeleton.kb"
       "bolton::[usr.jh.sysproc]")
     ("BOLTON" nil (:absolute "USR" "JH" "GSI") "SKELETON" "KB" nil))
    ((gensym-merge-pathnames-reclaiming-first-argument
       (parse-unix-filename "./gsi/skeleton.kb")
       "nj:/usr/jh/")
     ("nj" :unspecific (:absolute "usr" "jh" "gsi") "skeleton" "kb" nil))
    ((gensym-merge-pathnames-reclaiming-first-argument
       (parse-unix-filename "gsi/skeleton.kb")
       "nj:/usr/jh/")
     ("nj" :unspecific (:absolute "usr" "jh" "gsi") "skeleton" "kb" nil))
    ((gensym-merge-pathnames 
       "bolton::[.gsi]skeleton.kb"
       "bolton::[usr.jh]")
     ("BOLTON" nil (:absolute "USR" "JH" "GSI") "SKELETON" "KB" nil))
    ))


#+development
(defun validate-gensym-pathname-facility (validation-suite &optional verbose-p)
  (loop for (form result) in validation-suite
	for test-result 
	    = (eval form)
	for passed-p 
	    = (cond ((gensym-pathname-p test-result)
		     (and (equal (gensym-pathname-host test-result)
				 (first result))
			  (equal (gensym-pathname-device test-result)
				 (second result))
			  (equal (gensym-pathname-directory test-result)
				 (third result))
			  (equal (gensym-pathname-name test-result)
				 (fourth result))
			  (equal (gensym-pathname-type test-result)
				 (fifth result))
			  (equal (gensym-pathname-version test-result)
				 (sixth result))))
		    (t (equal test-result result)))
	with bad-forms = nil
	do
	(when verbose-p
	  (format t "~&~:[!!! incorrect: ~;  OK:~] ~s => ~%~
                    ~:[!!!~7t~;~10t~]~s~
                     ~@[~%!!! but should be~%~
                          !!!~7t~s~]~%~%"
		  passed-p 
		  form
		  passed-p
		  (cond ((gensym-pathname-p test-result)
			 (list
			   (gensym-pathname-host test-result)
			   (gensym-pathname-device test-result)
			   (gensym-pathname-directory test-result)
			   (gensym-pathname-name test-result)
			   (gensym-pathname-type test-result)
			   (gensym-pathname-version test-result)))
			(t test-result))
		  (and (not passed-p) result)))
	(unless passed-p
	  (push form bad-forms))
	(when (gensym-pathname-p test-result)
	  (reclaim-gensym-pathname test-result))
	finally (return (values (null bad-forms) bad-forms))))

#+development
(defun validate-gensym-merge-pathnames (&optional verbose-p)
  (validate-gensym-pathname-facility 
    gensym-merge-pathnames-validation-suite
    verbose-p))

#+development
(defun examine-merge-pathnames-memory-use ()
  (with-memory-checking
    (validate-gensym-merge-pathnames)))






#+development
(defvar emit-lisp-p nil)

;nil :append-to-name :append-to-directory
(defvar object-file-pathname-for-machine :append-to-name)

(defparameter g2-machine-type-string
  (gensym-string-to-wide-string (string-downcase (symbol-name g2-machine-type))))


(defun-simple make-object-file-pathname (pathname type)
  (let* ((directory (gensym-pathname-directory pathname))
	 (obj-file-dir
	   (if (and (eq object-file-pathname-for-machine :append-to-directory)
		    (consp directory))
	       (nconc (copy-list-using-path-conses directory)
		      (path-list g2-machine-type-string))
	       directory))
	 (name (gensym-pathname-name pathname))
	 (obj-file-name
	   (if (eq object-file-pathname-for-machine :append-to-name)
	       (tformat-text-string "~A-~A" name g2-machine-type-string)
	       name)))
    (prog1 (gensym-make-pathname
	     :directory obj-file-dir		   
	     :name obj-file-name
	     :type type
	     :defaults pathname)
      (when (and (eq object-file-pathname-for-machine :append-to-directory)
		 (consp directory))
	(reclaim-path-list obj-file-dir))
      (when (eq object-file-pathname-for-machine :append-to-name)
	(reclaim-text-string obj-file-name)))))


(defun-simple pathname->shared-file-pathname (pathname)
  (make-object-file-pathname
    pathname
    (cond
      #+development
      (emit-lisp-p
       '#.(gensym-string-to-wide-string
	    (bootstrap-information-lisp-binary-file-type)))
      (t
       (case local-file-system
	 (unix  #w"so")
	 (vms   #w"lib")
	 (win32 #w"dll")
	 (t     #w"dll"))))))



;;; `pathname->object-file-pathname' is obsolete because the C function
;;; to produce a shared object now merely takes a suffix instead of
;;; the full filename.

#+obsolete
(defun-simple pathname->object-file-pathname (pathname)
  (make-object-file-pathname
    pathname
    (cond
      #+development
      (emit-lisp-p
       '#.(gensym-string-to-wide-string
	    (bootstrap-information-lisp-binary-file-type)))
      (t
       (case local-file-system
	 (unix  #w"o")
	 (t     #w"obj"))))))


(defun-simple get-object-file-suffix-for-this-os ()
  (case local-file-system
    (unix  #w".o")
    (t     #w".obj")))


(defun-simple kb-name->shared-object-filename (kb-filename)
  (twith-output-to-text-string
    (loop for i from 0 below (text-string-length kb-filename)
	  as c = (charw kb-filename i)
	  until (char=w #.%\. c) do
      (twrite-wide-character-macro c))
    (twrite-string #w"-")
    (twrite-string g2-machine-type-string)
    (twrite-string #w".")
    (case local-file-system
      (unix  (twrite-string #w"so"))
      (vms   (twrite-string #w"lib"))
      (win32 (twrite-string #w"dll"))
      (t     (twrite-string #w"dll")))))




;;;; Obtaining the User Name from the Operating System

;;; ...  This information may or may not be stored in the command-line or in
;;; environment variables, so acquiring it is treated as a special case.



(def-gensym-c-function c-user-name
		       (:fixnum-int "g2ext_get_user_name")
  ((:string buff)))

;;; Foreign-get-user-name returns a new text-string if successful, nil
;;; otherwise.

(defun foreign-get-user-name ()
  (let ((result-code
	  (c-user-name gensym-environment-variable-buffer)))
    (interface-to-foreign-environment-access result-code)))

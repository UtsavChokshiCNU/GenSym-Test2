;; -*- mode: lisp; package: bundle -*-

(in-package "BUNDLE")

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; BUNDLE - Generator of data structures, data files, and scripts for bundling
;; G2 and related products.

;; Mark H. David and Judy Anderson




;; Good ideas to do for the generated tree-generation shell script (i.e., make-g2fam-tar.sh):
;; -- have the script take an "all" argument, to do all of them.
;; -- allow more than one target platform on the command line
;; -- Have a way to tar up the resulting tree (for Unix only).
;; -- Have it be smart enough to just untar the G2 directory one time, not
;;   once for each time it needs a file from it.
;; --yduJ/MHD, 9/100



;;;; Part 1: Bundle Hacks

;; Judy Anderson


(defstruct family
  name
  pretty-name
  file-syntax-version
  index
  bundles
  directory
  splash-screen
  readme-file
  guid
  previous-versions

  ;; We used to always "shun" any previous version of a bundle and force
  ;; the user to remove it. That's not too friendly, esp. for a beta release.
  ;; We don't have too much technical reason for it
  ;; anymore. `Compatible-previous-versions' has the exact same format as
  ;; previous-versions, but it is just a placeholder for GUID's of previous
  ;; released bundle that we actually don't do anything with. This is a new
  ;; feature we hope to make increasing use of.  Note that at present it is just
  ;; discarded -- not put in the .fam file or into any of the generated
  ;; InstallShield files.  However, we still encourage its use for the
  ;; forseeable future, in case we decide it needs to be used, to have a place
  ;; to record the information. (MHD 1/28/03)
  compatible-previous-versions
  
  license-text
  platforms
  non-platforms)

(defstruct bundle
  name components version directory platforms non-platforms)


;;; Component - Note: radio-button-group-index, if non-nil, is to be used to
;;; establish that this component is mutually exclusive with all other
;;; components that have the same index.  Added by MHD, 9/8/00, but it may not
;;; be used for a while; the main use will be to ensure sane selection of
;;; license key components, e.g., one and only one G2.OK file.

;;; The contents-parts element, created by def-component with the
;;; :include-in-contents keyword, is used by the contents file generator to
;;; decide which parts would be used to specify the version.  This is a notable
;;; problem with the G2 documentation component, which has multitudinous
;;; parts with widely varying version numbers, so we want to just say that it
;;; matches the G2 documentation.  Otherwise, you might have multiple versions
;;; of a component (for example in the G2 5.2r1 bundle, we shipped ProTools
;;; 6.0r1 and ProTools 5.1r9, and would like to include both of those on the cd
;;; contents.)

(defstruct component
  name parts platforms non-platforms watermark typical optional
  radio-button-group-index contents-parts)


;;; Part - Note: (new feature) filename may be an atom (usually a string, but
;;; also a symbol) or a list.  If it's a list, then all fields that can
;;; reasonably apply to all filenames apply.  Note that new-filename should
;;; never be supplied in the list case, since it would not be able to express a
;;; renaming of all the files to unique names.

(defstruct part
  name source destination version
  filename				; one file name, or a list thereof (consider renaming!)
  new-filename				; NA if filename is a list
  files-to-exclude indep
  obfuscate
  platforms non-platforms
  source-subdirectory
  source-ship-type			; :internal or :external, or nil (= :external)
  remove-from-source
  environment-variables registry-entries register shortcuts
  make-not-read-only
  preinstall-code postinstall-code uninstall-code)


(defstruct environment-variable
  name value append-or-merge)
(defstruct registry-entry
  name key-name path value)
(defstruct shortcut
  name
  folder-name subfolder-name subsubfolder-name ; 3 levels
  application-display-name
  application-directory target-name parameters icon-file icon-index run-style
  ;; missing field for "bin", per DDM!
  )

     
(defvar *family-descriptor*)



(defvar *directories-to-make* nil)
(defvar *path-separator* #+win32 "\\" #+linux "/")
(defun make-mkdir (filename)
  (setq filename (pathname filename))
  (let ((directory-list (pathname-directory filename))
	(directory-string ""))
    (pop directory-list); flush the :root
    #+win32(setq directory-string (concatenate 'string (pathname-device filename) ":"))
    (loop for element in directory-list do
      (setq directory-string (concatenate 'string directory-string *path-separator* element))
      (unless (member directory-string *directories-to-make* :test #'equalp)
	(unless nil ; (probe-file directory-string)  ; wrong time to probe (MHD)
	  (setq *directories-to-make*
		(append *directories-to-make* (list directory-string))))))
    (setq directory-string (concatenate 'string directory-string *path-separator*
					(file-namestring filename)))
    (unless (member directory-string *directories-to-make* :test #'equalp)
      (unless nil  ; (probe-file directory-string)  ; wrong time to probe (MHD)
	(setq *directories-to-make*
	      (append *directories-to-make* (list directory-string)))))))


;;; The global special variable *use-iship-instead-of-eship-p* is to be bound
;;; normally at top level to nil.  This makes :source reference generally go to
;;; eship (for externally shipping/promoted products being bundled).  It can be
;;; specially bound to T (true) around the call to independent-filename or
;;; dependent-file name to have iship (for internally shipping/promoted
;;; products) be used instead.

(defvar *use-iship-instead-of-eship-p* nil)

(defun absolute-pathname (filename)
  (and (> (length filename) 0)
       ;;this is a bit of a misnomer, because the pathname can contain a ':'
       ;;(a real absolute pathname), or it can start with a %, meaning an environment
       ;;variable (e.g. %SRCBOX%).
       #+win32
       (or (char= #\% (char filename 0))
           (and (> (length filename) 1)
                (char= #\: (char filename 1))))
       ;;this is a bit of a misnomer, because the pathname can start either with a /
       ;;(a real absolute pathname), or it can start with a $, meaning an environment
       ;;variable (e.g. $SRCBOX).
       #+(or linux unix)
       (or (char= #\/ (char filename 0))
           (char= #\$ (char filename 0)))))

(defun independent-filename (filename &key test-p)
  (unless (absolute-pathname filename)
    (if test-p
	(format nil
                #+win32"c:\\g2\\stage\\~a\\indep\\~a\\test"
                #+linux"/g2/stage/~a/indep/~a/test"
		(if *use-iship-instead-of-eship-p* "iship" "eship")
		filename)
	(format nil
                #+win32"c:\\g2\\stage\\~a\\indep\\~a\\tape\\~a.zip"
                #+linux"/g2/stage/~a/indep/~a/tape/~a.tar"
		(if *use-iship-instead-of-eship-p* "iship" "eship")
		filename
		filename))))


(defun dependent-filename (filename &key test-p alt-platform)
  (unless (absolute-pathname filename)
    (if test-p
	(format nil
                #+win32"c:\\g2\\stage\\~a\\dep\\~a\\~a\\test"
                #+linux"/g2/stage/~a/dep/~a/~a/test"
		(if *use-iship-instead-of-eship-p* "iship" "eship")
		(if alt-platform
                    (translate-platform alt-platform)
                    #+win32"%platform%" #+linux"$platform")
		filename)
	(format nil
                #+win32"c:\\g2\\stage\\~a\\dep\\~a\\~a\\tape\\~a.zip"
                #+linux"/g2/stage/~a/dep/~a/~a/tape/~a.tar"
		(if *use-iship-instead-of-eship-p* "iship" "eship")
		(if alt-platform
                    (translate-platform alt-platform)
                    #+win33"%platform%" #+linux"$platform")
		filename
		filename))))


(defun divine-tar-directory (filename source-filename platform version
				      &optional source-subdirectory)
  ;; the tar files in the tape directory have the unfortunate property that they
  ;; have the platform and product already in the directory hierarchy within the
  ;; tar file.  For example, the tar files for fonts contain files like
  ;; "indep/fonts/chinese.ttf".  So, from a filename of the sort "fonts-51r5",
  ;; we need to divine "indep/fonts/"
  (let ((version-location (search version source-filename)))
    (concatenate 'string
		 platform *path-separator*
		 (subseq source-filename 0 (and version-location (1- version-location)))
		 (if source-subdirectory *path-separator* "") (or source-subdirectory "")
		 *path-separator* filename)))

(defvar *very-temporary-directory*
  #+win32(or (environment-variable "TEMP") (environment-variable "TMP") (environment-variable "TMPDIR"))
  #+linux"/tmp")
(defun stage-tar-file (stage-destination tar-command platform part)
  (let ((output-lines nil)
	(source-filename (part-source part))
	(what-to-copy (or (part-source-subdirectory part) ".")))
    (push tar-command output-lines)
    (push (format nil "cd ~a" (divine-tar-directory "" source-filename platform
						    (part-version part)))
	  output-lines)
    (when (part-obfuscate part)
      (setq output-lines
	    (nconc
	      (loop for name
			in (if (listp (part-filename part))
			       (part-filename part)
			       (list (part-filename part)))
		    collect (format nil
				#+win32"%SRCBOX%\\bundle\\c\\%MACHINE%\\obfuscator -F ~a -k ~a"
				#+linux"$SRCBOX/bundle/c/$MACHINE/obfuscator -F ~a -k ~a"
				name (family-guid *family-descriptor*)))
	      output-lines)))
    (loop with r = (part-remove-from-source part)
	  for what in (if (listp r) r (list r))
	  do (push (format nil "rm -rf ~a~a~a" what-to-copy *path-separator* what)
		   output-lines))
    (when (part-make-not-read-only part)
      ;; This does something useful: it makes the files that have a dot in them
      ;; be writeable in this directory and its subdirectories.  This handles
      ;; all the cases we currently care about for installer bugs.  It's not
      ;; very general at all! (MHD 10/23/00)
      (push "chmod a+w ./*.* ./*/*.*" output-lines))
    (when (part-files-to-exclude part)
      (push "# get rid of certain files we didn't actually want" output-lines)
      (loop for file in (part-files-to-exclude part) do
	(push (format nil "find . -name ~a -exec rm -rf \\{\\} \\;"
		      file) output-lines)))

    ;; GENSYMCID-774 -- xu.jingtao@glority.com, 17-May-2012
    ;; use shell command 'cp' instead of 'mv' will make recursive directory copy not failed.
    ;; we got error messages moving directory to an exist destinition directory.
    (if (equalp what-to-copy ".")
	(push (format nil "cp -fr `ls -A` ~a" stage-destination) output-lines)
	(push (format nil "(cd ~a ; cp -fr `ls -A` ~a)" what-to-copy stage-destination) output-lines))
    (push "cd ../.." output-lines)
    (push (format nil "rm -rf ~a" platform) output-lines)
    output-lines))
  
    
(defparameter *script-beginning*
  "#!/bin/csh
# This script was generated to create the tar hierarchy which will be used to
# deploy in the bundle for UNIX platforms
if ($#argv < 1) then
  goto usage
endif

if ($1 == \"-v\") then
  set verbose = 1
  shift
endif

set platform = $1
if ($platform == \"\") then
  goto usage
endif

goto execute

usage:
echo \"usage: $0 [-v] platform\"
echo \"platform = intelnt, rs6000, sparcsol, linux, linux64, alphaosf, or hp9000s700\"
exit 1

execute:
")

(defvar *family-eship-platform*
  '(("nt" "intelnt" "Windows")
    ("win64" "win64" "Windows x64")
    ("aix" "rs6000" "IBM AIX")
    ("sparcsol" "sparcsol" "Sun Solaris")
    ("linux" "linux" "Linux x86")
    ("linux64" "linux64" "Linux x86_64")
    ("hpux" "hp9000s700" "PA-RISC HP-UX")
    ("alphaosf" "alphaosf" "Compaq Tru64 UNIX")
    ("hpia64" "hpia64" "Itanium HP-UX")))

(defun translate-platform (family-platform)
  (let ((result (second (assoc family-platform *family-eship-platform* :test #'equalp))))
    (unless result (warn "failed to translate ~s to eship platform name" family-platform))
    result))

(defun indep-or-special (indep)
  (if (eq indep t) "indep" (translate-platform indep)))

(defun probe-file-with-envvars (filename)
  (if (char/= #+win32 #\% #+linux #\$ (char filename 0))
      (probe-file filename)
      (let ((env-end-pos (position #+win32 #\% #+linux #\/ filename :start 1)))
	(probe-file (format nil "~a~a"
			    (environment-variable (subseq filename 1 env-end-pos))
			    (subseq filename #+win32(1+ env-end-pos) #+linux env-end-pos))))))

;;Too bad we can't get the shell to help us with this environment variable
;;expansion, but we have to extract it ourselves from the filename string.  This
;;means we can't do anything fancy by having an environment variable embedded
;;within the string, but we only can deal with it at the start.  Fortunately,
;;that's all we want at this time.
	
  

(defun create-skip-command (part)
  ;; we need to create a command which will skip the next bit of code
  ;; if $platform does not match any of the part-platforms, or, if $platforms
  ;; is in any of the non-platforms.
  ;; platforms: use if $platform == part-platform && $platform == part-platform-2
  ;; non-platforms:use if $platforms != non-platform || etc.
  ;; there's probably some way to do this without duplicating the format below, and
  ;; having the || and == as parameters, but I think it's complicated enough as it is.
  ;; there's probably some way to do it without splitting the first from the rest, but etc.
  (if (part-platforms part)
      (format nil "if ($platform == ~(~a~)~@[~{ || $platform == ~(~a~)~}~]) then"
	      (translate-platform (car (part-platforms part)))
	      (mapcar #'translate-platform (cdr (part-platforms part))))
      (format nil "if ($platform != ~(~a~)~@[~{ && $platform != ~(~a~)~}~]) then"
	      (translate-platform (car (part-non-platforms part)))
	      (mapcar #'translate-platform (cdr (part-non-platforms part))))))

;; The idea here is to return all the parts in the family. we assume it's not
;; possible to have a component that has a part that lives in a different place.
;; All parts are top level and know their own directory structure; they have it
;; hard-wired.

(defun consolidate-bundles (family-descriptor)
  (loop with collected-parts = nil
	for bundle in (family-bundles family-descriptor)
	do (loop for component in (bundle-components bundle) do
	     (loop for part in (component-parts component)
		   as prev-part = (member part collected-parts
					  :test #'(lambda (x y)
						    (equalp (part-name x) (part-name y))))
		   do
	       ;;propagate any platform specificity downwards	    
	       (if (and (component-platforms component) (not (part-platforms part)))
		   (setf (part-platforms part) (component-platforms component)))
	       (if (and (component-non-platforms component) (not (part-non-platforms part)))
		   (setf (part-non-platforms part) (component-non-platforms component)))
	       ;;Now, if we have a prev part, union up the platform
	       ;;possibilities, and don't push it.  Otherwise it's new, so push
	       (if prev-part
		   (progn
		     (setq prev-part (car prev-part))
		     (setf (part-non-platforms prev-part)
			   (intersection (part-non-platforms part) (part-non-platforms prev-part)
					 :test #'equalp))
		     (setf (part-platforms prev-part)
			   (union (part-platforms part) (part-platforms prev-part)
				  :test #'equalp)))
		   (pushnew part collected-parts))))
	finally (return (nreverse collected-parts))))

(defun consolidate-components (family-descriptor)
  (loop with collected-components = nil
	for bundle in (family-bundles family-descriptor)
	do (loop for component in (bundle-components bundle) do
	     (pushnew component collected-components :test #'equalp))
	finally (return (nreverse collected-components))))

;; foo.lisp => foo.lisp
;; /foo/bar/baz/foo.lisp => foo.lisp
(defun strip-leading-path (string)
  (let ((loc (position #+win32 #\\ #+linux #\/ string :from-end t)))
    (if loc
	(subseq string (1+ loc))
	string)))

(defun create-script (stage-directory filename)
  (let ((output-lines nil)
	(first-section nil))
    (setq *directories-to-make* nil)
    (push (format nil "cd ~a" *very-temporary-directory*) output-lines)
    (let ((base-directory (format nil "~a/$platform-~(~a~)" stage-directory 
				  (family-name *family-descriptor*))))
      (push (format nil "if (-d ~a) then~%~
                      echo \"error: directory ~a already exists -- please remove it\"~%~
                      exit 1~%endif" base-directory base-directory)
	    first-section)
      (loop for part in (consolidate-bundles *family-descriptor*) do
	(let* ((stage-destination
		 (format nil "~a~@[/~a~]" base-directory (part-destination part))) 
	       (tar-file
		 (let ((*use-iship-instead-of-eship-p*
			 (eq (part-source-ship-type part) :internal)))
		   (if (eq (part-indep part) t)
		       (independent-filename (part-source part))
		       (dependent-filename (part-source part)
					   :alt-platform (part-indep part)))))
	       (filename-platform
		 (if (part-indep part) (indep-or-special (part-indep part)) "$platform"))
	       (maybe-tag (or (part-platforms part) (part-non-platforms part))))
	  (when maybe-tag
	    (push (create-skip-command part)
		  output-lines))
	  (make-mkdir stage-destination)
	  (if tar-file
	      (setq output-lines
		    (append
		      (stage-tar-file
			stage-destination				
			(with-output-to-string (output-stream)
			  (format output-stream "tar xf ~a " tar-file)
			  ;; whether to get just one or more individual files, or the whole nine yards
			  (loop for name in (if (listp (part-filename part))
						(part-filename part)
						(list (part-filename part)))
				do (format
				     output-stream "~s "
;;;Note: the ~s above is to put double quotes around the filenames in order to
;;;handle spaces and other special characters that might appear in those
;;;filenames (under Windows usually).  Interestingly, divine-tar-directory will
;;;produce a $platform variable within those double quotes, but the shell will
;;;expand that variable properly, even though it happily quotes the other
;;;special characters such as () or '
				     (divine-tar-directory
				       name (part-source part)
				       filename-platform (part-version part)
				       (part-source-subdirectory part)))))
			filename-platform
			part)
		      output-lines))
	      (loop for name in (if (listp (part-filename part))
				    (part-filename part) ; may be nil
				    (list (part-filename part)))
		    as source-filename
		       = (format nil "~a/~a" (part-source part) name)
		    do (unless (probe-file-with-envvars source-filename)
			 (warn "file ~a missing" source-filename))
		       (push
			 (format nil "cp -p ~a ~a" source-filename stage-destination)
			 output-lines)
		       (cond ((eq (part-obfuscate part) :from-sandbox)
			      (push
				(format nil "$SRCBOX/bundle/c/$MACHINE/obfuscator -d -F ~a/~a -k known_seed"
					stage-destination (strip-leading-path source-filename))
				output-lines)
			      (push
				(format nil "$SRCBOX/bundle/c/$MACHINE/obfuscator -F ~a/~a -k ~a"
					stage-destination (strip-leading-path source-filename)
					(family-guid *family-descriptor*))
				output-lines))
			     ((eq (part-obfuscate part) t)
			      (push
				(format nil "$SRCBOX/bundle/c/$MACHINE/obfuscator -F ~a/~a -k ~a"
					stage-destination (strip-leading-path source-filename)
					(family-guid *family-descriptor*))
				output-lines)))))
	  (if maybe-tag (push "endif" output-lines)))
	(push "" output-lines))
      (push "# and a final collection of files we didn't want" output-lines)
      (push (format nil "find ~a -name contents.txt -exec rm \\{\\} \\;"
		    base-directory) output-lines))
    (with-open-file (stream filename :direction :output :if-exists :supersede)
      (write-line *script-beginning* stream)
      (loop for line in (reverse first-section) do
	(write-line line stream))
      (loop for line in *directories-to-make* do
	(format stream "if (! -d ~a) mkdir ~a~%" line line))
      (write-line "" stream)
      (loop for line in (reverse output-lines) do
	(write-line line stream)))
    ;; now make the new file be executable:
    (shell (format nil "chmod a+x ~a" filename))))

(defvar *difference-beginning*
  "#!/bin/csh
#automatically generated file to validate G2 bundle

if ($#argv < 2) then
    echo
    echo \"Usage: ~a <platform> <installation directory>\"
    exit 0
endif
set platform = $1
set installdir = $2

")

(defun make-difference-file-internal (filename)
  (let ((output-lines nil))
    (loop for part in (consolidate-bundles *family-descriptor*) do
      (let ((tar-file
	      (let ((*use-iship-instead-of-eship-p*
		      (eq (part-source-ship-type part) :internal)))
		(if (eq (part-indep part) t)
		    (independent-filename (part-source part) :test-p t)
		    (dependent-filename (part-source part)
					:test-p t
					:alt-platform (part-indep part)))))
	    (names (if (listp (part-filename part))
		       (part-filename part)
		       (list (part-filename part))))
	    (destination (if (part-destination part)
			     (format nil "~a/" (part-destination part))
			     ""))
	    (maybe-tag (or (part-platforms part) (part-non-platforms part))))	
	(unless (equalp (part-filename part) "watermark.txt")
	  (when maybe-tag
	    (push (create-skip-command part)
		  output-lines))
	  (unless tar-file
	    (setq tar-file (part-source part)))
	  (if (part-source-subdirectory part)
	      (setq tar-file (format nil "~a/~a" tar-file (part-source-subdirectory part))))
	  (if names
	      (setq output-lines
		    ;;diff -q output is "files differ" without showing all differences within file
		    ;;Requested by QA to make less clutter in log files.
		    (append (loop for name in names collect (format nil "diff -q $installdir/~a~a ~a/~a" destination
								    name tar-file name))
			    output-lines))
	      (push (format nil "diff -rq $installdir/~a ~a | grep -v 'Only in .* contents.txt'"
			    ;;we don't care about contents.txt -- we don't include it,
			    ;;but eship does.  Reduce clutter in the output thus.
			    destination tar-file)
		    output-lines))
	  (if maybe-tag (push "endif" output-lines))
	  (push "" output-lines))))
    (with-open-file (stream filename :direction :output :if-exists :supersede)
      (format stream *difference-beginning* filename)
      (loop for line in (reverse output-lines) do
	(write-line line stream)))
    ;; now make the new file be executable:
    (shell (format nil "chmod a+x ~a" filename))))

(defun platform-match (platform platforms non-platforms)
  (or (and (null platforms) (null non-platforms))
      (and platforms (member platform platforms :test #'equalp))
      (and non-platforms (not (member platform non-platforms :test #'equalp)))))

(defun make-contents-file-internal (filename platform pretty-platform)
  (let ((ship-lines nil))
    (loop for component in (consolidate-components *family-descriptor*) do
      (loop for part in (if (eq (component-contents-parts component) :none)
			    nil
			    (or (component-contents-parts component)
				(component-parts component)))
	  if (and (not (equalp (part-filename part) "watermark.txt"))
		  (not (absolute-pathname (part-source part)))
		  (platform-match platform (part-platforms part)
				  (part-non-platforms part))
		  (platform-match platform (component-platforms component)
				       (component-non-platforms component)))
	    do
	      (multiple-value-bind
		  (version-symbol version-major version-minor version-revision suffix version-letter)
		  (parse-version-symbol (intern (string-upcase (part-version part))))
		(declare (ignore version-symbol))
		(let ((build-ID (if (> (length suffix) 0) (format nil " (Build ~a)" (subseq suffix 1)) ""))
		      (iship (if (eq (part-source-ship-type part) :internal) " (iship)" "")))
		  (pushnew (format nil "~a ~a~a~a~a~a~a~a"
				   (component-name component)
                                   version-major
                                   (if (string/= "" version-minor) "." "")
                                   version-minor
				   (if (string/= "" version-revision) version-letter "")
                                   version-revision build-ID iship
				   #+ignore ; not used
				   (part-destination part))
			   ship-lines :test #'equalp)))))
    (with-open-file (stream filename :direction :output :if-exists :supersede)
      (format stream "Contents of the bundle ~a ~a on platform ~a:~%~%"
	      (family-name *family-descriptor*)
	      (bundle-version (first (family-bundles *family-descriptor*)))
	      pretty-platform)
      (loop for line in (sort ship-lines #'string-lessp) do
	(write-line line stream)))))

(defvar *indentation* 0)

;;; Format-indented ... if item is a symbol, it is printed in all lowercase.  If
;;; it is a string, it is printed literally, i.e., with the lettercase of the
;;; string, but without surrounding double quotes. Do not hack lettercase using
;;; vertical bar or backquotes, e.g., |FoF"; use strings instead.  To print a
;;; string with surrounding double quotes, use format-indented-string, below.

(defun format-indented (stream label item &optional back-tab)
  (let ((*indentation* (if back-tab (- *indentation* back-tab) *indentation*)))
    (if (> *indentation* 0)
	;;too bad that tabbing always does at least one space
	(format stream
		(if (symbolp item) "~VT~a: ~(~a~)~%" "~VT~a: ~a~%")
		*indentation* label item)
	(format stream 
		(if (symbolp item) "~a: ~(~a~)~%" "~a: ~a~%") label item))))

(defun format-indented-list (stream label items &optional back-tab)
  (let ((item-string  (format nil "~{ ~a~}" items)))
    (format-indented stream label item-string back-tab)))

(defun format-indented-string (stream label items)
  (let ((item-string (format nil "~s" items)))
    (format-indented stream label item-string)))

(defvar *component-counters* nil)
(defconstant too-many-components 68)
(defconstant too-many-bundles 16)
(defconstant too-big-family-id 256)

;;writing out the family file
(defun create-family-file (filename)
  (with-open-file (stream filename :direction :output :if-exists :supersede)
    (format stream "# Automatically Generated File -- Please Do Not Edit~%")
    (terpri stream)
    (if (>= (family-index *family-descriptor*) too-big-family-id)
	(warn "FAMILY ID ~a TOO LARGE!  Must be smaller than ~a"
	      (family-index *family-descriptor*) too-big-family-id))
    (format-indented stream "index" (family-index *family-descriptor*))
    (terpri stream)
    (format-indented stream "family file syntax version" (family-file-syntax-version *family-descriptor*))
    (terpri stream)
    (format-indented stream "family" (family-pretty-name *family-descriptor*))
    (format-indented stream "directory name" (family-directory *family-descriptor*))
    (when (family-platforms *family-descriptor*)
      (format-indented-list stream "only on" (family-platforms *family-descriptor*)))
    (when (family-non-platforms *family-descriptor*)
      (format-indented-list stream "on all but" (family-non-platforms *family-descriptor*)))
    (when (family-splash-screen *family-descriptor*)
      (format-indented stream "splash screen" (family-splash-screen *family-descriptor*)))
    (when (family-readme-file *family-descriptor*)
      (format-indented stream "readme" (family-readme-file *family-descriptor*)))
    (when (family-guid *family-descriptor*)
      (format-indented stream "guid" (family-guid *family-descriptor*)))
    (loop for p in (family-previous-versions *family-descriptor*)
	  do (format-indented stream "previous version" (previous-version p))
             (let ((*indentation* (+ *indentation* 2)))
	       (format-indented stream "previous version guid" (previous-version-guid p))))
    (when (family-license-text *family-descriptor*)
      (format-indented stream "license text" (family-license-text *family-descriptor*)))
    (loop for bundle in (family-bundles *family-descriptor*)
	  as bundle-counter from 1
	  with *indentation* = (+ *indentation* 4) do
      (if (= bundle-counter too-many-bundles)
	    (warn "BUNDLE INDEX BEYOND ~d!" (1- too-many-bundles)))
      (format-indented stream "bundle" (bundle-name bundle) 2)
      (format-indented stream "id" bundle-counter)
      (format-indented stream "version" (bundle-version bundle))
      (if (bundle-platforms bundle)
 	  (format-indented-list stream "only on" (bundle-platforms bundle)))
      (if (bundle-non-platforms bundle)
	  (format-indented-list stream "on all but" (bundle-non-platforms bundle)))
      ;;currently not using the directory name part of the bundle itself, only that of family
      ;(format-indented stream "directory name" (bundle-directory bundle))
      (loop for component in (bundle-components bundle) 
	    as component-counter from (or (pop *component-counters*) 1)
	    with *indentation* = (+ *indentation* 4) do
	(format-indented stream "component" (component-name component) 2)
	(format-indented stream "index" component-counter)
	(if (= component-counter too-many-components)
	    (warn "COMPONENT INDEX BEYOND ~d!" (1- too-many-components)))
	(if (component-platforms component)
	    (format-indented-list stream "only on" (component-platforms component)))
	(if (component-non-platforms component)
	    (format-indented-list stream "on all but" (component-non-platforms component)))
	(if (component-watermark component)
	    (format-indented stream "watermark" (component-watermark component)))
	(if (component-typical component)
	    (format-indented stream "typical" (component-typical component)))
	(if (component-optional component)
	    (format-indented stream "optional" (component-optional component)))
	(if (component-radio-button-group-index component)
	    (format-indented stream "radio button group index"
			     (component-radio-button-group-index component)))
	(loop for part in (component-parts component)
	  with *indentation* = (+ *indentation* 4) do
	  (format-indented stream "part" (part-name part) 2)
	  (if (part-source part)
	      (if (part-source-subdirectory part)
		  (format-indented-list stream "sourcedir"
					(list (part-source part) (part-source-subdirectory part)))
		  (format-indented stream "sourcedir" (part-source part))))
	  (if (part-destination part) 
	      (format-indented stream "destdir" (part-destination part)))
	  (loop for name in (if (listp (part-filename part))
				(part-filename part) ; may be nil
				(list (part-filename part)))
		do
	    (format-indented stream "filename" name))
	  (if (part-new-filename part) 
	      (format-indented stream "new filename" (part-new-filename part)))
	  (if (part-obfuscate part) 
	      (format-indented stream "obfuscate" "true")) ; false is also legal, but not needed
	  (if (part-platforms part)
	      (format-indented-list stream "only on" (part-platforms part))) 
	  (if (part-non-platforms part)
	      (format-indented-list stream "on all but" (part-non-platforms part)))
	  (loop with *indentation* = (+ *indentation* 4)
		for variable in (part-environment-variables part)
		as variable-number from 1
		as append-or-merge = (environment-variable-append-or-merge variable)
		as merge-p = (eq append-or-merge 'merge)
		as effect-string
		   = (if (null append-or-merge) "new" (if merge-p "merge" "append"))
		as env-variable = (environment-variable-name variable)
		as env-value
		   = (or (environment-variable-value variable)
			 (format nil "<TARGETDIR>\\\\~a" (part-destination part)))
		
		do	      
	    (cond
	      ((null env-variable)
	       (cerror "continue without using it"
		       "Part ~a (bundle ~a) has an undefined variable (#~d): ~a"
		       (part-name part) (bundle-name bundle)
		       variable-number variable))
	      (merge-p
	       ;; Explode the path into subpaths, so we can have nice compact
	       ;; representation but generate distinct merge directives per
	       ;; element.  (We assume the value is either an explodable
	       ;; semicolon-separated path value, or that it has no semicolons
	       ;; so that it shouldn't matter.) (MHD 10/20/00)
	       (loop with paths = (explode-windows-path-string env-value)
		     for path in paths
		     do
		 (format-indented stream "env variable" env-variable 2)
		 (format-indented stream "env value" path)
		 (format-indented stream "env effect" effect-string)))
	      (t
	       (format-indented stream "env variable" env-variable 2)
	       (format-indented stream "env value" env-value)
	       (format-indented stream "env effect" effect-string))))
	  (when (part-registry-entries part)
	    (loop for entry in (part-registry-entries part)
		  with *indentation* = (+ *indentation* 4) do
	      (format-indented stream "registry entry" (registry-entry-name entry) 2)
	      (format-indented stream "key path" (registry-entry-path entry))
	      (format-indented stream "key name" (registry-entry-key-name entry))
	      (format-indented stream "key value" (registry-entry-value entry))))
	  (when (part-register part)
	    (when (part-registry-entries part)
	      (warn "There is both a part-registry and a register entry.  But they are incompatible!")) ; per ddm
	    (format-indented stream "register" "yes"))
	  (when (part-preinstall-code part)
	    (format-indented stream "preinstall code" (part-preinstall-code part)))
	  (when (part-postinstall-code part)
	    (format-indented stream "postinstall code" (part-postinstall-code part)))
	  (when (part-uninstall-code part)
	    (format-indented stream "uninstall code" (part-uninstall-code part)))
	  (loop for shortcut in (part-shortcuts part)
		with *indentation* = (+ *indentation* 4) do
	    (format-indented stream "shortcut" "" 2)
	    (format-indented stream "folder name" (shortcut-folder-name shortcut))
	    (when (shortcut-subfolder-name shortcut)
	      (format-indented stream "subfolder name" (shortcut-subfolder-name shortcut))
	      (when (shortcut-subsubfolder-name shortcut)
		(format-indented stream "subsubfolder name" (shortcut-subsubfolder-name shortcut))))
	    (format-indented stream "application display name" (shortcut-application-display-name shortcut))
	    (format-indented stream "application directory" (shortcut-application-directory shortcut))
	    (format-indented stream "target name" (shortcut-target-name shortcut))
	    (when (shortcut-parameters shortcut)
	      (format-indented stream "parameters" (shortcut-parameters shortcut)))
	    (when  (shortcut-icon-file shortcut)
	      (format-indented stream "icon file" (shortcut-icon-file shortcut)))
	    (when  (shortcut-icon-index shortcut)
	      (format-indented stream "icon index" (shortcut-icon-index shortcut)))
	    (when  (shortcut-run-style shortcut)
	      (format-indented stream "run style" (shortcut-run-style shortcut)))))))))





;;; Explode-windows-path-string takes a string that would be used as
;;; a path or classpath under windows, i.e., of the form
;;;
;;;   "<path1>;<path2>;..."
;;;
;;; i.e., using semicolons separating pathstrings, and returns a list of
;;; subpaths strings of the form
;;;
;;;   ("<path1>" "<Path2>" ...)

(defun explode-windows-path-string (path-string)
  (loop with separator-char = #\;
	with resulting-substrings = '()
	with next-start
	with end = (length path-string)
	for start = 0 then next-start
	while (< start end)
	do (setq next-start
		 (loop for i from start 
		       when (or (not (< i end))
				(char= (char path-string i) separator-char))
			 do (setq resulting-substrings
				  (nconc resulting-substrings
					 (list (subseq path-string start i))))
			    (return (+ i 1))))
	finally (return resulting-substrings)))
		   


;;;; Obfuscation Seed String Creation



;;; The obfuscation seed string is the family's GUID.  Differences in lettercase
;;; and the presence of nonalphanumeric characters in the string are ignored.

(defconstant obfuscation-base-modulus 3989)

(defun make-obfuscation-seed-string (family)
  (loop with strings = (family-guid family)
	with result = 0
	for string in strings
	do (setq result (make-obfuscation-seed-string-1 string result))
	finally
	  (return result)))

(defun make-obfuscation-seed-string-1 (string result)
  (loop with acc = result
	for ch across string		; would not work in Gensym's loop 
	do (setq acc (mod (+ acc
			     (if (or (char<= #\a ch #\z) (char<= #\0 ch #\9))
				 (char-code ch)
				 (if (char<= #\A ch #\Z)
				     (char-code (char-downcase ch))
				     0)))
			  obfuscation-base-modulus))
	finally (return acc)))



;;;; Test Family Descriptor


#+test
(setq *family-descriptor*
      (make-family
	:name "G2"
	:bundles
	(list
	  (make-bundle
	    :version "5.1r5"
	    :name "G2 Deployment"
	    :components
	    (list
	      (make-component
		:name "javalink"
		:parts
		(list
		  (make-part
		    :name "javalink-intelnt"
		    :source "jvl-11r0"
		    :source-subdirectory "components"
		    :destination "g2/javalink"
		    :platforms '("nt")
		    :environment-variables (list (make-environment-variable
						   :name "CLASSPATH"
						   :value "%JAVA_HOME%\\\\lib\\\\tools.tar"
						   :append 'merge))
		    :registry-entries (list (make-registry-entry
					      :name "uninstall_data"
					      :path "hkey_local_machine\\software\\gensym"
					      :value "this is a test")))
		  (make-part
		    :name "javalink-UNIX"
		    :source "jvl-11r0"
		    :destination "g2/javalink"
		    :non-platforms '("nt"))))
	      (make-component
		:name "G2"
		:parts
		(list
		  (make-part
		    :name "G2"
		    :source "g2-51r5"
		    :destination "g2"
		    :files-to-exclude '("g2.ok"))
		  (make-part
		    :name "kbs"
		    :source "kbs-51r5"
		    :destination "g2/kbs"
		    :indep t)
		  (make-part
		    :name "fonts"
		    :source "fonts-51r5"
		    :destination "g2/fonts"
		    :indep t))
		:watermark "g2/g2.ok")	; NEW. (MHD 8/23/00)
	      (make-component
		:name "Client 4-Pack"
		:parts
		(list
		  (make-part
		    :name "ok"
		    :source "/home/ab/ok"
		    :destination "g2"
		    :filename "g2df0tw20v51.ok"
		    :new-filename "g2.ok")))


	      (make-component
		:name "Telewindows"
		:parts
		(list
		  (make-part
		    :name "Telewindows"
		    :source "tw-51r5"
		    :destination "g2"
		    :files-to-exclude '("tw.ok")))))))))






;;;; Part 2: Family Definitions

;; Mark H. David


;;; Here are definitions to generate the data structures to create the family
;;; file and associated scripts.




(defun bundle-set (name key value parent &optional default-default)
  (setf (get name key)
	(if (eq value :delete)
	    nil
	    (or value (if parent (get parent key)) default-default))))

;;;mhd 12/14/01
(defun probable-version-tag-p (symbol-or-string)
  (let* ((string (string symbol-or-string))
	 (length (length string)))
    (if (and (> length 0)
	     (digit-char-p (char string 0))
	     (digit-char-p (char string (- length 1))))
	t
	nil)))

;;;mhd 12/14/01
(defun dehyphenate (symbol-or-string)
  (let ((string (string symbol-or-string)))
    (loop with length = (length string)
	  for i from 0 below length
	  with start = 0
	  when (char= (char string i) #\-)
	    collect (subseq string start i) into result-so-far
	    and do (setq start (+ i 1))
	  finally
	    (return (nconc result-so-far
			   (if (>= i start)
			       (list (subseq string start i))
			       nil))))))

;;;decodes the family name and version tag (e.g. g2-61r0) and returns just the
;;;string version of the family name (e.g. "g2").  Attempts to handle hyphenated
;;;family names and hyphenated version numbers both -- looks for the first thing
;;;that is apparently a version number, so family names cannot have hyphenated
;;;components which begin with a number, e.g. no "g2-6-1r0" expecting the family
;;;name to be "g2-6".
(defun get-family-name-from-family (name)
   (loop with result
	 as first-time-p = t then nil
	 for word in (dehyphenate name)
	 while (not (probable-version-tag-p word))
	 do (setq result (if first-time-p word (concatenate 'string result "-" word)))
	 finally (return (string-downcase result))))

(defmacro def-family (name &key index file-syntax-version bundles print-name
			   directory splash-screen readme-file
			   guid previous-versions compatible-previous-versions
			   license-text platforms non-platforms
			   parent)
  (declare (ignore compatible-previous-versions))
  (let ((make-x-fam (intern (format nil "MAKE-~a-FAM" name)))
	(make-x-fam-script (intern (format nil "MAKE-~a-FAM-SCRIPT" name))))
    `(progn
       (bundle-set ',name 'family-index ',index ',parent)
       (bundle-set ',name 'family-name (get-family-name-from-family ',name) ',parent)
       (bundle-set ',name 'family-file-syntax-version ',file-syntax-version ',parent)
       (bundle-set ',name 'family-bundles ',bundles ',parent)
       (bundle-set ',name 'family-print-name ',print-name ',parent)
       (bundle-set ',name 'family-directory ',directory ',parent)
       (bundle-set ',name 'family-splash-screen ',splash-screen ',parent)
       (bundle-set ',name 'family-readme-file ',readme-file ',parent)
       (bundle-set ',name 'family-guid ',guid ',parent)
       (bundle-set ',name 'family-previous-versions ',previous-versions ',parent)
       (bundle-set ',name 'family-license-text ',license-text ',parent)
       (bundle-set ',name 'family-platforms ',platforms ',parent)
       (bundle-set ',name 'family-non-platforms ',non-platforms ',parent)
       (defun ,make-x-fam (filename)
	 (make-family-file ',name filename))
       (defun ,make-x-fam-script (scriptname stage-directory)
	 (make-script-to-make-big-tar-file ',name scriptname stage-directory))
       ',name)))

(defun family-print-name (family-name)
  (or (get family-name 'family-print-name)
      (setf (get family-name 'family-print-name)
	    (format nil "~(~a~)" family-name))))

(defmacro def-component (name &key parts platforms non-platforms
			      print-name watermark typical optional
			      radio-button-group-index parent include-in-contents)
  `(progn
     ;; the blank watermark stuff is to deal with bogosity in the NT
     ;; installer/uninstaller: every component needs a blank watermark, so that
     ;; it can get clobbered by later parts of the install, so that the real one
     ;; can get uninstalled in the final result.
     (check-component-name ',name)
     (check-component-name ',print-name)
     (bundle-set
       ',name 'component-parts
       ;; The inheritence handling of parent breaks down here with the
       ;; autoconsing of the blank-watermark. That's because parent is only
       ;; looked at when this argument (value) is non-nil. So we do the
       ;; inheriting work explicitly here.  The parent argument at the end will
       ;; just be ignored, since the value arg is non-nil.
       ',(cons 'blank-watermark (or (dwim-group parts) (if parent (get parent 'component-parts))))
       ',parent)
     (bundle-set ',name 'component-platforms ',platforms ',parent)
     (bundle-set ',name 'component-non-platforms ',non-platforms ',parent)
     (bundle-set ',name 'component-print-name ',print-name ',parent)
     (bundle-set ',name 'component-watermark ',watermark ',parent)
     (bundle-set ',name 'component-typical ',typical ',parent)
     (bundle-set ',name 'component-optional ',optional ',parent)
     (bundle-set ',name 'component-radio-button-group-index ',radio-button-group-index ',parent)
     (bundle-set ',name 'component-contents-parts ',include-in-contents ',parent)
     ',name))


(defun component-print-name (component-name)
  (or (get component-name 'component-print-name)
      (setf (get component-name 'component-print-name)
	    (format nil "~(~a~)" component-name))))



;;; Def-bundle .... Note: components and evaluated-components are mutually
;;; exclusive; one or the other should always be used.  In the evaluated case,
;;; the arg is evaluated to come up with a list of components.  In the plain
;;; components (unevaluated) case, the arg should be a list of components, which
;;; list will not be evaluated.

(defmacro def-bundle (name &key components version print-name directory
			   platforms non-platforms parent)
  `(progn
     (bundle-set ',name 'bundle-components ',(dwim-group components) ',parent)
     (check-part-version ',name ',version)
     (bundle-set ',name 'bundle-version ',version ',parent)
     (bundle-set ',name 'bundle-print-name ',print-name ',parent)
     (bundle-set ',name 'bundle-directory ',directory ',parent)
     (bundle-set ',name 'bundle-platforms ',platforms ',parent)
     (bundle-set ',name 'bundle-non-platforms ',non-platforms ',parent)
     ',name))

(defun bundle-print-name (bundle-name)
  (or (get bundle-name 'bundle-print-name)
      (setf (get bundle-name 'bundle-print-name)
	    (format nil "~(~a~)" bundle-name))))

;;;in order to avoid requiring users to use lisp quoting and lisp functions like
;;;append, we instead "do what they meant" by taking either a variable which is
;;;a list of components, or a symbol, which is an individually named component,
;;;and doing the quoting for them (really, evaluating the variable for them) and
;;;appending everything to form a list.

;;;currently this function, in concert with defvar and def-bundle in the same
;;;x-family.lisp file, doesn't work if you compile the file and load the binary,
;;;but does work if you load the x-family.lisp file.
(defun dwim-group (stuff)
  (let ((result nil))
    (loop for item in stuff
	  if (and (boundp item) (listp (symbol-value item)))
	    do (setq result (append result (symbol-value item)))
	  else do (setq result (append result (list item))))
    result))


(defun check-name-for-dots (name name-type)
  (cond ((find #\. (string name))
	 (error	; known problem on Windows (InstallGenerator)
	   "The ~(~a~) name ~s has an illegal dot (.) character."
	   name-type
	   name)
	 nil)
	(t t)))

(defun check-component-name (name)
  (check-name-for-dots name 'component))

(defun check-part-name (name)
  (check-name-for-dots name 'part))


;;; Note check-part-version may also be used to check the version of a bundle.
;;; Their namespaces are collapsed for purposes of declaring and checking
;;; versions.  Perhaps this should change, and perhaps it will.

(defparameter *warn-on-unknown-version* nil)

(defun check-part-version  (part-name version)
  (cond
    ((null version)); sometimes we think it's OK to not have a version.
    ((null (get version 'part-version-major))
     (if *warn-on-unknown-version*
	 (cerror "continue regardless" "~a is an unknown version symbol (part = ~a)"
		 (version-print-name version)
		 (part-print-name part-name))
	 (dwim-version-information version)))
    ((not (member part-name (get version 'part-version-known-parts)))
     (when *warn-on-unknown-version*
       (warn "Part ~a isn't known to have version ~a (version string: ~a)"
	     (part-print-name part-name)
	     (version-print-name version)
	     (get-version-string version))))))

;;; A version symbol is expected to be a symbol in the keyword package
;;; of the form
;;;
;;;    <major><minor><status><revision>[<letter-suffix>][-<build-suffix>]
;;;
;;; where <major> and <minor> are single-digit versions in [0..9]; <status> is a
;;; single letter status indication or release, beta, or alpha status, one of r,
;;; b, or a; <revision> is a single-digit revision number in [0..9];
;;; <letter-suffix> is a letter in [a..z]; <build-suffix> is an arbitrary suffix
;;; string.
;;;
;;; This always downcases the <status> letter and the <letter-suffix> letter.
;;; The case of the letters in suffix is left unchanged.  Therefore, if the case
;;; of suffix should not be uppercase, as it rarely is in practice, the symbol
;;; should be written using vertical bar quotes, e.g., :|50r1-pdf|.

;;; New "modern" Gensym version symbol:
;;;
;;;    <major><minor><status><revision>[<letter-suffix>][-<build-suffix>]
;;;
;;; where <major> is now 4-digit version string i.e. "2011", <minor> can be 1-digit
;;; or 2-digit version string. others remains.

(defun dwim-version-information (version-symbol)
  (multiple-value-bind
	(version-symbol version-major version-minor version-revision suffix version-letter)
	(parse-version-symbol version-symbol)
      (eval
	`(def-part-version ,version-symbol
	     :major ,version-major
	     :minor ,version-minor
	     :revision ,version-revision
	     :suffix ,suffix
	     :letter ,version-letter))))

;;; GENSYMCID-449: Gensym Linux installer: investigation and building Linux Gensym installer
;;; The function PARSE-VERSION-SYMBOL now supports new G2 version system, i.e. 2011 --binghe

(defun parse-version-symbol (version-symbol)
  (let* ((version-string (string version-symbol))
         (possible-version-letter (char version-string 2)))
    (if (alpha-char-p possible-version-letter)
        (parse-version-symbol-legacy version-symbol)
        (parse-version-symbol-modern version-symbol))))

;;; following version string are supported:
;;;   :2011, major: 2011, minor: 0, letter: "r", revision: 0, suffix: none
;;;   :2011r2, major: 2011, minor: 0, letter: "r", revision: 2, suffix: none
;;;   :2011b3-xxx, major: 2011, minor: 0, letter "b", revision: 3, suffix: "-XXX"
;;;   :20110r1, major: 2011, minor: 0, letter: "r", revision: 1, suffix: none
;;;   :201101r1, major: 2011, minor: 1, letter: "r", revision: 1, suffix: none

(defun parse-version-symbol-modern (version-symbol)
  (let* ((version-string   (string version-symbol))
         (version-major    (subseq version-string 0 4))
         (sep-pos?         (position-if-not #'digit-char-p version-string))
         (version-minor    (if (and (> (length version-string) 4)
                                    (digit-char-p (char version-string 4)))
                               (subseq version-string 4 sep-pos?)
                               ""))
         (dashpos?         (position #\- version-string))
         (letterpos?       (position-if #'alpha-char-p version-string))
         (version-letter   (if (cond ((and dashpos? letterpos?) (> dashpos? letterpos?))
                                     (dashpos? letterpos?))
                               (char-downcase (char version-string letterpos?))
                               "r"))
         (version-revision (if (cond ((and dashpos? letterpos?) (> dashpos? (1+ letterpos?)))
                                     (letterpos? (> (length version-string) letterpos?)))
                               (subseq version-string (1+ letterpos?) dashpos?)
                               ""))
         (build-suffix     (if dashpos?
                               (subseq version-string dashpos?)
                               "")))
    ;; note: return type changes:
    ;; version-major, version-minor are strings (previous: single digit char)
    (values
      version-symbol version-major version-minor
      version-revision build-suffix version-letter)))

(defun parse-version-symbol-legacy (version-symbol)
  (let* ((version-string (string version-symbol))
	 (version-major (char version-string 0))
	 (version-minor (char version-string 1))
	 (version-letter (char-downcase (char version-string 2)))
	 (dashpos? (position #\- version-string))
	 (version-revision (string-downcase (subseq version-string 3 dashpos?)))
	 (build-suffix (if dashpos?
			   (subseq version-string dashpos?)
			   "")))
    (values
      version-symbol version-major version-minor
      version-revision build-suffix version-letter)))

(defun version-print-name (version-name)
  (or (get version-name 'part-version-print-name)
      (setf (get version-name 'part-version-print-name)
	    (format nil "~(~a~)" version-name))))

(defun get-version-string (version-name)
  (or (get version-name 'version-string)
      (make-version-string version-name)))

(defun get-pretty-version-string (version-name)
  (or (get version-name 'pretty-version-string)
      (make-pretty-version-string version-name)))

(defun make-version-string (version-name &optional pretty-p)
  (let ((version-major (get version-name 'part-version-major)))
    (if (and (stringp version-major)
             (= (length version-major) 4))
        (make-version-string-modern version-name pretty-p)
      (make-version-string-legacy version-name pretty-p))))

(defun make-version-string-legacy (version-name &optional pretty-p)
  (format nil "~a~a~a~a~a"
	  (get version-name 'part-version-major)
	  (if pretty-p "." "")
	  (get version-name 'part-version-minor)
	  (let ((r (get version-name 'part-version-revision)))
	    (if r (format nil "~a~a" (or (get version-name 'part-version-letter) "r") r) ""))
	  (let ((s (get version-name 'part-version-suffix)))
	    (if s (format nil "~a" s) ""))))

(defun make-version-string-modern (version-name &optional pretty-p)
  (let* ((version-major (get version-name 'part-version-major))
         (version-minor (get version-name 'part-version-minor)))
    (format nil "~a~a~a~a~a"
            version-major
            (if (and pretty-p
                     (and (stringp version-minor) (string/= version-minor "")))
                "." "")
            version-minor
            (let ((r (get version-name 'part-version-revision)))
              (if (and r (stringp r) (string/= r ""))
                  (format nil "~a~a" (or (get version-name 'part-version-letter) "r") r)
                ""))
            (let ((s (get version-name 'part-version-suffix)))
              (if s (format nil "~a" s) "")))))

(defun make-pretty-version-string (version-name)
  (make-version-string version-name t))
     

(defmacro def-part (name &key version source source-filename destination-directory 
			 destination-filename indep print-name files-to-exclude
			 obfuscate
			 platforms non-platforms
			 source-subdirectory source-ship-type
			 remove-from-source
			 environment-variables registry-entries register shortcuts
			 make-not-read-only ; only for script, not family file
			 preinstall-code postinstall-code uninstall-code parent)
  `(progn
     (check-part-name ',name)
     (check-part-name ',print-name)
     (bundle-set ',name 'part-components ',name ',parent)
     (check-part-version ',name ',version)
     (bundle-set ',name 'part-version ',version ',parent)
     (bundle-set ',name 'part-source ',source ',parent)
     (bundle-set ',name 'part-source-filename ',source-filename ',parent)
     (bundle-set ',name 'part-destination-directory ',destination-directory ',parent)
     (bundle-set ',name 'part-destination-filename ',destination-filename ',parent)
     (bundle-set ',name 'part-indep ',indep ',parent) ; t (= platform independent) or nil (default)
     (bundle-set ',name 'part-files-to-exclude ',files-to-exclude ',parent)
     (bundle-set ',name 'part-obfuscate ',obfuscate ',parent)
     (bundle-set ',name 'part-platforms ',platforms ',parent)
     (bundle-set ',name 'part-non-platforms ',non-platforms ',parent)
     (bundle-set ',name 'part-source-subdirectory ',source-subdirectory ',parent)
     (bundle-set ',name 'part-source-ship-type ',source-ship-type ',parent)
     (bundle-set ',name 'part-remove-from-source ',remove-from-source ',parent)
     (bundle-set ',name 'part-print-name ',print-name ',parent)
     (bundle-set ',name 'part-environment-variables ',environment-variables ',parent)
     (bundle-set ',name 'part-registry-entries ',registry-entries ',parent)
     (bundle-set ',name 'part-register ',register ',parent)
     (bundle-set ',name 'part-shortcuts ',shortcuts ',parent)
     (bundle-set ',name 'part-make-not-read-only ',make-not-read-only ',parent)
     (bundle-set ',name 'part-preinstall-code ',preinstall-code ',parent)
     (bundle-set ',name 'part-postinstall-code ',postinstall-code ',parent)
     (bundle-set ',name 'part-uninstall-code ',uninstall-code ',parent)
     ',name))

(defun part-print-name (part-name)
  (or (get part-name 'part-print-name)
      (setf (get part-name 'part-print-name)
	    (format nil "~(~a~)" part-name))))

(defmacro def-part-version (name &optional &key major minor revision suffix known-parts
				 letter print-name parent)
  `(progn
     ;; require major and minor only:
     (assert (not (null ',major)))
     (assert (not (null ',minor)))
     
     (bundle-set ',name 'part-version-name ',name ',parent)
     (bundle-set ',name 'part-version-major ',major ',parent)
     (bundle-set ',name 'part-version-minor ',minor ',parent)
     (bundle-set ',name 'part-version-revision ',revision ',parent)
     (bundle-set ',name 'part-version-letter ',letter ',parent)
     (bundle-set ',name 'part-version-suffix ',suffix ',parent)
     (bundle-set ',name 'part-version-known-parts ',known-parts ',parent)
     (bundle-set ',name 'part-version-print-name ',print-name ',parent)
     ',name))


;;; Def-environment-variable ... The variable-name can be a string with a
;;; particular spelling, which will be used as is, or omitted, in which case the
;;; (usually uppercase) print name, as a string, will be used, or a symbol, in
;;; which case that symbol's lowercase spelling will be emitted (usually NOT
;;; what you want).

(defmacro def-environment-variable (name &optional &key value variable append-or-merge parent)
  `(progn
     (bundle-set ',name 'variable-name ',variable ',parent ',(symbol-name name))
     (bundle-set ',name 'variable-value ',value ',parent)
     (bundle-set ',name 'variable-append-or-merge ',append-or-merge ',parent)
     ',name))

(defmacro def-registry-entry (name &optional &key value path key-name parent)
  `(progn
     (bundle-set ',name 'entry-name ',name ',parent)
     (bundle-set ',name 'entry-key-name ',key-name ',parent)
     (bundle-set ',name 'entry-value ',value ',parent)
     (bundle-set ',name 'entry-path ',path ',parent)
     ',name))

(defvar *default-folder-name* "Gensym G2")

(defun check-shortcut-application-display-name (application-display-name)
  (loop for i from 0 below (length application-display-name)
	as char = (char application-display-name i)
	when (not (or (alphanumericp char)
		      (member char '(#\space #\- #\_ #\. #\' #\+ #\) #\())))
	  do (cerror "continue anyway, probably with lossage"
		     "The character ~c is not legal in shortcut name ~s."
		     char application-display-name)))

;; You get very little feedback about this problem.  InstallShield just dies
;; with no information at setup time if you have illegal characters here! (MHD
;; 12/10/00)

(defmacro def-shortcut (name &optional &key folder-name subfolder-name subsubfolder-name
			     application-display-name
			     application-directory target-name parameters
			     icon-file icon-index run-style parent)
  (when application-display-name
    (check-shortcut-application-display-name application-display-name))
  `(progn
     (bundle-set ',name 'shortcut-name ',name ',parent)
     ;; folder-name is not quoted below, to enable it to refer to a variable.
     ;; Strings when re-evaluated will become themselves, so this is okay -- we
     ;; are now not allowing people to name their folders with symbols but
     ;; requiring strings (which they were all doing anyway).
     (bundle-set ',name 'shortcut-folder-name ,folder-name ',parent *default-folder-name*)
     (bundle-set ',name 'shortcut-subfolder-name ',subfolder-name ',parent)
     (bundle-set ',name 'shortcut-subsubfolder-name ',subsubfolder-name ',parent)
     (bundle-set ',name 'shortcut-application-display-name ',application-display-name ',parent)
     (bundle-set ',name 'shortcut-application-directory ',application-directory ',parent)
     (bundle-set ',name 'shortcut-target-name ',target-name ',parent)
     (bundle-set ',name 'shortcut-parameters ',parameters ',parent)
     (bundle-set ',name 'shortcut-icon-file ',icon-file ',parent)
     (bundle-set ',name 'shortcut-icon-index ',icon-index ',parent)
     (bundle-set ',name 'shortcut-run-style ',run-style ',parent)
     ;; missing field for "bin", per DDM!
     ',name))


;;; A `previous version' is a data abstraction to represent information needed
;;; about previous versions.  A previous version is represented as a list of two
;;; strings, a version string and a guid string, in that order.  Thus it can be
;;; simply read in by the Lisp reader.  Accessor operations for previous version
;;; are previous-version, which gets the version string, and
;;; previous-version-guid, which gets the guid string, and there are same-named
;;; accessor functions to implement these operations.

(defun previous-version (previous-version)
  (first previous-version))

(defun previous-version-guid (previous-version)
  (second previous-version))

;; New for Bundle Installer 1.0 Rev. 2. (MHD 12/7/00)
  


;;;; Part 4: Interface to yduJ's Bundle Hacks


(defun make-family-descriptor (family-name)
  (make-family
    :name (get family-name 'family-name)
    :pretty-name (family-print-name family-name)
    :file-syntax-version (get family-name 'family-file-syntax-version)
    :index (get family-name 'family-index)
    :bundles (make-bundles-for-family family-name)
    :directory (get family-name 'family-directory)
    :splash-screen (get family-name 'family-splash-screen)
    :readme-file (get family-name 'family-readme-file)
    :guid (get family-name 'family-guid)
    :previous-versions (get family-name 'family-previous-versions)
    :license-text (get family-name 'family-license-text)
    :platforms (get family-name 'family-platforms)
    :non-platforms (get family-name 'family-non-platforms)))


(defun make-bundles-for-family (family-name)
  (loop for bundle-name in (get family-name 'family-bundles)
	collect (make-bundle
		  :name (bundle-print-name bundle-name)
		  :version (get-pretty-version-string
			     (get bundle-name 'bundle-version))
		  :components (make-components-for-bundle bundle-name)
		  :directory (get bundle-name 'bundle-directory)
		  :platforms (get bundle-name 'bundle-platforms)
		  :non-platforms (get bundle-name 'bundle-non-platforms))))

(defun make-components-for-bundle (bundle-name)
  (loop for component-name in (get bundle-name 'bundle-components)
	as platforms = (get component-name 'component-platforms)
	as non-platforms = (get component-name 'component-non-platforms)
	as watermark? = (get component-name 'component-watermark)
	as typical = (get component-name 'component-typical)
	as optional = (get component-name 'component-optional)
	as contents-parts = (get component-name 'component-contents-parts)
	as radio-button-group-index = (get component-name 'component-radio-button-group-index)
	collect (make-component
		  :name (component-print-name component-name)
		  :platforms platforms
		  :non-platforms non-platforms
		  :parts (make-parts (get component-name 'component-parts) component-name)
		  :contents-parts (if (eq contents-parts :none)
				      :none
				      (make-parts contents-parts component-name))
		  :watermark watermark?
		  :typical typical
		  :optional optional
		  :radio-button-group-index radio-button-group-index)))


(defun make-component-source-pathname (component-name part-name version-name)
  (declare (ignore component-name))	; ignored for now
  (let ((source (or (get part-name 'part-source) (part-print-name part-name))))
    ;;don't lowercase filenames which were specified as strings
    (format nil (if (symbolp source) "~(~a~)~@[-~a~]" "~a~@[-~a~]")
	    source (and version-name (get-version-string version-name)))))

(defun make-component-destination-pathname (component-name part-name version-name)
  (declare (ignore component-name version-name)) ; ignored for now
  (let ((destination (get part-name 'part-destination-directory)))
    (and destination (format nil (if (symbolp destination) "~(~a~)" "~a") destination))))

(defun make-component-subdirectory-pathname (component-name part-name version-name)
  (declare (ignore component-name version-name)) ; ignored for now
  (let ((source-subdirectory (get part-name 'part-source-subdirectory)))
    (and source-subdirectory (format nil (if (symbolp source-subdirectory) "~(~a~)" "~a")
				         source-subdirectory))))

(defun make-parts (parts component-name)
  (loop for part-name in parts
	collect (make-individual-part part-name component-name)))

(defun make-individual-part (part-name component-name)
  (let* ((version-name  (get part-name 'part-version))
	 (source  (make-component-source-pathname
		    component-name part-name version-name))
	 
	 (destination  (make-component-destination-pathname
			 component-name part-name version-name))
	 (indep  (get part-name 'part-indep))
	 (files-to-exclude  (get part-name 'part-files-to-exclude))
	 (source-filename  (get part-name 'part-source-filename))
	 (destination-filename  (get part-name 'part-destination-filename))
	 (source-subdirectory  (make-component-subdirectory-pathname
				 component-name part-name version-name))
	 (source-ship-type  (get part-name 'part-source-ship-type))
	 (remove-from-source  (get part-name 'part-remove-from-source))
	 (obfuscate  (get part-name 'part-obfuscate))
	 (platforms  (get part-name 'part-platforms))
	 (non-platforms  (get part-name 'part-non-platforms))
	 (environment-variables  (make-variables-for-part part-name))
	 (registry-entries  (make-entries-for-part part-name))
	 (register  (get part-name 'part-register))
	 (shortcuts  (make-shortcuts-for-part part-name))
	 (make-not-read-only  (get part-name 'part-make-not-read-only))
	 (preinstall-code  (get part-name 'part-preinstall-code))
	 (postinstall-code  (get part-name 'part-postinstall-code))
	 (uninstall-code  (get part-name 'part-uninstall-code)))
    (make-part
      :name (part-print-name part-name)
      :source source
      :version (get-version-string version-name)
      :destination destination
      :indep indep
      :files-to-exclude files-to-exclude
      :source-subdirectory source-subdirectory
      :source-ship-type source-ship-type
      :remove-from-source remove-from-source
      :obfuscate obfuscate
      :platforms platforms
      :non-platforms non-platforms
      :filename source-filename
      :new-filename destination-filename
      :environment-variables environment-variables
      :registry-entries registry-entries
      :register register
      :shortcuts shortcuts
      :make-not-read-only make-not-read-only
      :preinstall-code preinstall-code
      :postinstall-code postinstall-code
      :uninstall-code uninstall-code)))

(defun make-variables-for-part (part-name)
  (loop for variable in (get part-name 'part-environment-variables)
	as variable-name = (get variable 'variable-name)
	as variable-value = (get variable 'variable-value)
	as variable-append-or-merge = (get variable 'variable-append-or-merge)
	collect (make-environment-variable
		  :name variable-name
		  :value variable-value
		  :append-or-merge variable-append-or-merge)))

(defun make-entries-for-part (part-name)
  (loop for entry in (get part-name 'part-registry-entries)
	as entry-name = (get entry 'entry-name)
	as entry-key-name = (get entry 'entry-key-name)
	as entry-value = (get entry 'entry-value)
	as entry-path = (get entry 'entry-path)
	collect (make-registry-entry
		  :name entry-name
		  :key-name entry-key-name
		  :value entry-value
		  :path entry-path)))


;;; Make-shortcuts-for-part creates shortcut structures from the list of
;;; shortcut symbols on the PART-SHORTCUTS property of part-name.  This does a
;;; basic sanity check to see that the shortcut was actually defined: i.e., by
;;; checking that there is a non-nil SHORTCUT-FOLDER-NAME on the shortcut
;;; symbol.  If there is none, this will issue a warning if it has not been
;;; issued previously.  This tracks whether a warning has been issued using the
;;; property BAD-SHORTCUT-REPORTED property (t/nil) as a mark.

(defun make-shortcuts-for-part (part-name)
  (loop for shortcut in (get part-name 'part-shortcuts)
	if (null (get shortcut 'shortcut-folder-name)) ; check others, too?
	  do (unless (get shortcut 'bad-shortcut-reported)
	       (setf (get shortcut 'bad-shortcut-reported) t)
	       (format t "~%Part ~a's part-shortcut ~a is not defined or is missing required data."
		     part-name shortcut))
	else collect
	        (make-shortcut
		  :name (get shortcut 'shortcut-name)
		  :folder-name (get shortcut 'shortcut-folder-name)
		  :subfolder-name (get shortcut 'shortcut-subfolder-name)
		  :subsubfolder-name (get shortcut 'shortcut-subsubfolder-name)
		  :application-display-name (get shortcut 'shortcut-application-display-name)
		  :application-directory (get shortcut 'shortcut-application-directory)
		  :target-name (get shortcut 'shortcut-target-name)
		  :parameters (get shortcut 'shortcut-parameters)
		  :icon-file (get shortcut 'shortcut-icon-file)
		  :icon-index (get shortcut 'shortcut-icon-index)
		  :run-style (get shortcut 'shortcut-run-style))))
	


(defun make-family-file (family-name filename)
  (let ((*family-descriptor* (make-family-descriptor family-name)))
    (create-family-file filename)))

(defun make-difference-file (family-name filename)
  (let ((*family-descriptor* (make-family-descriptor family-name)))
    (make-difference-file-internal filename)))

(defun make-contents-file (family-name filename-prefix)
  (let ((*family-descriptor* (make-family-descriptor family-name)))
    (loop for (family-platform eship-platform pretty-platform) in *family-eship-platform* do
      (make-contents-file-internal (concatenate 'string filename-prefix "-" eship-platform)
				   family-platform pretty-platform))))

(defun make-script-to-make-big-tar-file (family-name filename stage-directory)
  (let ((*family-descriptor* (make-family-descriptor family-name)))
    (create-script stage-directory filename)))


  


;;;; Additional Def's Layered On Top Of All This



;;; `Def-g2-ok-components' ...


(eval-when (:compile-toplevel :load-toplevel :execute)
  (defvar prevailing-ok-version-suffix "-v5")) ; abstract further?!

;;; this is a kluge to deal with the fact that the whole rename situation
;;; doesn't really work on NT.  Here instead of in the family.lisp file because
;;; it is referred to above in def-component.

(def-part blank-watermark
    :source "$SRCBOX/bundle/ok"
    :source-filename "watermark.txt")
  
;;; ... if an element n-clients-list is an integer, it is combined with other
;;; args to form a name.  If it is a list, then the first element is a number of
;;; clients, and the second element is either an integer, which is a number of
;;; G2 processes, or a string, which is appended to the filename, and is
;;; normally a temporary OK file expiration date.
;;;
;;; Bundle-name-and-options can be either simply a symbol, giving the bundle
;;; name, or a list whose car is the bundle name and whose cdr is options, which
;;; should be a keyword-style argument list.  Currently the supported options
;;; are
;;;
;;;   :obfuscate { t | nil | :from-sandbox}
;;;            - if true, the file is obfuscated in the standard manner
;;;            - if :from-sandbox, it is obfuscated in the new standard manner

(defmacro def-g2-ok-components (bundle-name-and-options  family-name combined-print-name n-clients-list)
  (declare (ignore family-name))	; not currently used, but maybe some day
  (destructuring-bind (bundle-name &key obfuscate)
    (if (atom bundle-name-and-options)
	(list bundle-name-and-options)
	bundle-name-and-options)
    (let ((list-of-g2-ok-components nil)
	  (family-defvar-name (intern (format nil "~a-FAMILY-OK-COMPONENTS" bundle-name)))
	  (source-directory (if (eq obfuscate :from-sandbox)
				"$SRCBOX/bundle/ok"
				"$SRCBOX/promote")))
      `(progn
	 ,@(loop for n-or-n-plus in n-clients-list
		 as n = (if (listp n-or-n-plus) (first n-or-n-plus) n-or-n-plus)
		 as plus = (if (listp n-or-n-plus)
			       (if (stringp (second n-or-n-plus))
				   (second n-or-n-plus)
				   (format nil "-~a-process" (second n-or-n-plus)))
			       "")
		 as plus-pretty-prefix
		    = (if (listp n-or-n-plus)
			  (string-append (string-trim '(#\- #\space) plus) " ")
			  "")
		 as n-suffix = (format nil "-~d" n)
		 as v-suffix = prevailing-ok-version-suffix
		 as ok-name = (intern (format nil "~a~a~a-OK" bundle-name n-suffix plus))
		 as file-name = (intern (format nil "~(~a~)~a~a~a.~a"
						bundle-name n-suffix v-suffix plus
						(if (eq obfuscate :from-sandbox) "obf" "ok")))
		 do (setq list-of-g2-ok-components
			  (nconc list-of-g2-ok-components (list ok-name)))
		 collect `(def-component ,ok-name
			    ;; should end up looking like, e.g., 4-Client Deployment G2 Classic OK
			    :print-name
			    ,(format nil "~a~d-Client ~a OK"
				     plus-pretty-prefix n combined-print-name)
			    :parts (,ok-name)
			    :watermark "g2/g2.ok"
			    :radio-button-group-index 1)
		 collect `(def-part ,ok-name
			      :destination-directory "g2"
			      :destination-filename "g2.ok"
			      :indep t
			      :source ,source-directory
			      :source-filename ,file-name
			      :obfuscate ,obfuscate))
	 (defparameter ,family-defvar-name ',list-of-g2-ok-components)))))






;;; `Def-gsi-bridge-ok-parts' ... options should be a keyword-style argument list.
;;; Currently  the supported options are
;;;
;;;   :obfuscate { t | nil }  - if true, the file is obfuscated in the standard manner

(defmacro def-gsi-bridge-ok-parts (options &rest gsi-bridges)
  (when (and options (or (atom options)   ; for compatibilty -- options was recently added (MHD 5/23/01)
			 (not (keywordp (car options))))) ;more compatibility: gsi-bridges were allowed to be lists even more recently.  yduJ 6/1/04
					
    (warn "~%Fixing options arg to def-gsi-bridge-ok-parts -- ok for now.~%")
    (push options gsi-bridges)
    (setq options nil))
  (destructuring-bind (&rest keys-and-values
		       &key obfuscate
		       &allow-other-keys)
    options
    (let ((source-directory (if (eq obfuscate :from-sandbox)
				"$SRCBOX/bundle/ok"
				"$SRCBOX/promote")))
      `(progn
	 . ,(let ((result '())
		  (more-keys-and-values
		    ;;loop through stripping out the keywords this macro
		    ;;understands and retaining only those that are additional
		    (loop for (key value) on keys-and-values by #'cddr 
			  unless (memq key '(:obfuscate :version))
			    collect key and collect value)))
	      ;;A bridge can either be just the name, e.g. oracle, which gets used
	      ;;for both the part name and the filename, or it can be a list of
	      ;;part-name and bridge name, e.g. (oracle-hp oracle)
	      (loop for bridge in gsi-bridges 
		    as part-name = (if (atom bridge) bridge (car bridge))
		    as bridge-name = (if (atom bridge) bridge (second bridge)) do
		(push `(def-part ,(intern (format nil "GSI-~a-BLANK-OK" part-name))
			   :destination-directory ,(format nil "~(~s~)" bridge-name)
			   :indep t 
			   :source "$SRCBOX/bundle/ok"
			   :source-filename "gsi.ok")
		      result)
		(push `(def-part ,(intern (format nil "GSI-~a-OK" part-name))
			   :destination-directory ,(format nil "~(~s~)" bridge-name)
			   :indep t 
			   :source ,source-directory
			   :source-filename "gsi.ok"
			   ,@more-keys-and-values)
		    result))
	    (reverse result))))))




;;;; Testing: Creating the G2.fam Family File


;; To load and test everything, and generate g2.fam in the current directory,
;; start Lucid Lisp, evaluate the following after the #+test.

#+test
(load (compile-file "/bt/mhd/bundle/tools/bundle.lisp"))

#+test
(load (compile-file "/bt/mhd/bundle/tools/g2-family.lisp"))

#+test
(bundle::make-g2-fam "/bt/mhd/tools/datafiles/families/g2.fam")

#+test
(bundle::make-g2-fam-script "/bt/mhd/bundle/tools/make-g2fam-tar.sh" "/home/mhd/trees")

#+test  ; or just do this: all of the above, all at once
(progn
  (load (compile-file "/bt/mhd/bundle/tools/bundle.lisp"))
  (load (compile-file "/bt/mhd/bundle/tools/g2-family.lisp"))
  (funcall (intern "MAKE-G2-FAM" "BUNDLE") "/bt/mhd/tools/datafiles/families/g2.fam")
  (funcall (intern "MAKE-G2-FAM-SCRIPT" "BUNDLE") "/bt/mhd/bundle/tools/make-g2fam-tar.sh" "/home/mhd/trees"))

#+yduj-test
(progn
  (load (compile-file "/bt/yduj/bundle/tools/bundle.lisp"))
  (load (compile-file "/bt/yduj/bundle/tools/g2-family.lisp"))
  (funcall (intern "MAKE-G2-FAM" "BUNDLE") "/bt/yduj/tools/datafiles/families/g2.fam")
  (funcall (intern "MAKE-G2-FAM-SCRIPT" "BUNDLE") "/bt/yduj/bundle/tools/make-g2fam-tar.sh" "/home/yduj/install"))

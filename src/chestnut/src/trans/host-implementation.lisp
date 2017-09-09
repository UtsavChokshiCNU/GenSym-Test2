;;; -*- Mode: Lisp; Package: HOST-IMPLEMENTATION; Syntax: Common-Lisp -*-
;;;
;;; Copyright (c) 1992, Chestnut Software Inc.
;;;

(in-package "HOST-IMPLEMENTATION")

#-(or sbcl cmu harlequin-common-lisp mcl clozure)
(progn

(defun string-case (string &optional (default :upper))
  (declare (type string string))
  (let ((length (length string))
	(upper-p nil)
	(lower-p nil))
      (dotimes (i length (cond (upper-p :upper)
			       (lower-p :lower)
			       (t default)))
	(let ((char (aref string i)))
	  (cond ((upper-case-p char)
		 (when lower-p (return :mixed))
		 (setq upper-p t))
		((lower-case-p char)
		 (when upper-p (return :mixed))
		 (setq lower-p t)))))))

(defun host-default-case (host-or-pathname) ; returns :upper or :lower
  #-genera (declare (ignore host-or-pathname))
  #+vms :upper
  #-(or vms genera) :lower
  #+genera
  (let ((host (etypecase host-or-pathname
		(pathname (scl:send host-or-pathname :host)) 
		(net:host host-or-pathname)
		(string (fs:get-pathname-host host-or-pathname)))))
    (typecase host
      ;;(fs:vms-host :upper) ; need to get these flavor names right
      ;;(fs:unix-host :lower)
      (t :lower))))

(defun convert-pathname-component-to-case (component case pathname)
  (if (stringp component)
      (ecase case
	(#-genera :local #+genera :common
	 component)
	(#-genera :common #+genera :local
	 (case (host-default-case pathname)
	   (:upper component)
	   (:lower
	    (case (string-case component)
	      (:upper (string-downcase component))
	      (:lower (string-upcase component))
	      (:mixed component))))))
      component))

(defun pathname-device (pathname &key (case :local))
  (setq pathname (pathname pathname))
  (convert-pathname-component-to-case
   (lisp:pathname-device pathname) case pathname))

(defun pathname-host (pathname &key (case :local))
  (setq pathname (pathname pathname))
  (convert-pathname-component-to-case
   (lisp:pathname-host pathname) case pathname))

(defun pathname-directory (pathname &key (case :local))
  (setq pathname (pathname pathname))
  (let ((directory (directory-to-subdirectory-list
		     (lisp:pathname-directory pathname))))
    (if (listp directory)
	(mapcar #'(lambda (component)
		    (convert-pathname-component-to-case
		      component case pathname))
		directory)	  
	directory)))

(defun pathname-name (pathname &key (case :local))
  (setq pathname (pathname pathname))
  (convert-pathname-component-to-case
   (lisp:pathname-name pathname) case pathname))

(defun pathname-type (pathname &key (case :local))
  (setq pathname (pathname pathname))
  (convert-pathname-component-to-case
   (lisp:pathname-type pathname) case pathname))

(defun pathname-version (pathname)
  (setq pathname (pathname pathname))
  (lisp:pathname-version pathname))

(defvar *host-only-pathname-alist* nil)

(defun host-only-pathname (&optional (pathname *default-pathname-defaults*))
  (let* ((host (pathname-host pathname))
	 (a (if (and *host-only-pathname-alist*
		     (eq host (caar *host-only-pathname-alist*)))
		(car *host-only-pathname-alist*)
		(assoc host *host-only-pathname-alist* :test #'equal))))
    (unless a
      (push (setq a (cons host (lisp:make-pathname :host host
						   :device nil
						   :directory nil
						   :name nil
						   :type nil
						   :version nil)))
	    *host-only-pathname-alist*))
    (cdr a)))

(defun make-pathname (&key (case :local)
			   (defaults (host-only-pathname))
			   (host (pathname-host defaults :case case))
			   (device (pathname-device defaults :case case))
			   (directory (pathname-directory defaults :case case))
			   (name (pathname-name defaults :case case))
			   (type (pathname-type defaults :case case))
			   (version (pathname-version defaults)))
  (lisp:make-pathname
   :host (convert-pathname-component-to-case host case host)
   :device (convert-pathname-component-to-case device case host)
   :directory (subdirectory-list-to-directory
	       (mapcar #'(lambda (component)
			   (convert-pathname-component-to-case
			    component case host))
		       directory))
   :name (convert-pathname-component-to-case name case host)
   :type (convert-pathname-component-to-case type case host)
   :version version))

#+(or lucid kcl excl chestnut)
;If path contains a relative directory,
;the result's directory is merged from both path and defaults.
(defun merge-pathnames (path &optional (defaults *default-pathname-defaults*)
			     (default-version :newest))
  (setq path (pathname path)) (setq defaults (pathname defaults))
  (make-pathname :defaults (lisp:merge-pathnames path defaults default-version)
		 :directory (pathname-directory-merge path defaults)))

(defun pathname-directory-merge (pdir dpdir)
  (let ((s-pdir (pathname-directory pdir)))
    (if (eq :relative (car s-pdir))
	(let ((first-part (pathname-directory dpdir)) 
	      (last-part (cdr s-pdir))) 
	  (loop (unless (eq (car last-part) ':up) (return nil))
		(pop last-part) (setq first-part (butlast first-part)))
	  (append first-part last-part))
	s-pdir)))

(defun directory-to-subdirectory-list (pdir)
  (when (pathnamep pdir) (setq pdir (lisp:pathname-directory pdir)))
  #+(or cleanup cmu mcl clozure sbcl Chestnut) ; must fix the RTL pathname stuff
             pdir
  #+lucid    (if (null pdir)
		 '(:relative)
		 (subst :up ".." 
			(case (car pdir)
			  (:relative pdir)
			  (:current '(:relative))
			  (:root (cons :absolute (cdr pdir))))
			:test #'equal))
  #+genera   (if (and (consp pdir) (eq (car pdir) :relative))
		 pdir
		 (if (null pdir)
		     '(:relative)
		     (cons :absolute (and (listp pdir) pdir))))
  #+excl     (cond ((equal pdir '(:absolute :root))
		    '(:absolute))
		   ((null pdir)
		    '(:relative))
		   (t
		    pdir)))

(defun subdirectory-list-to-directory (s-list)
  (when (null s-list) (setq s-list '(:relative)))
  #+(or cleanup cmu16 mcl clozure sbcl Chestnut)
	     s-list
  #+lucid    (subst ".." :up 
		    (if (eq (car s-list) :relative)
			s-list
			(cons :root (cdr s-list))))
  #+genera   (if (eq (car s-list) :relative)
		 (if (cdr s-list) s-list nil)
		 (if (cdr s-list) (cdr s-list) :root))
  #+kcl      (subst ".." :up (if (eq (car s-list) :relative)
				 (cdr s-list) (cons :root (cdr s-list))))
  #+excl     (cond ((equal s-list '(:absolute))
		    '(:absolute :root))
		   ((equal s-list '(:relative))
		    nil)
		   (t
		    s-list)))
)

#+harlequin-common-lisp
(defun make-pathname (&key (case :local)
			   (defaults nil defaults-p)
			   host
			   (device nil device-p)
			   (directory nil directory-p)
			   (name nil name-p)
			   (type nil type-p)
			   (version nil version-p))
  (when defaults-p (setq defaults (pathname defaults)))
  (lisp:make-pathname
   :case case
   :host (or host (pathname-host (if defaults-p defaults
				     *default-pathname-defaults*)
				 :case case))
   :device (if device-p device
	       (and defaults-p (pathname-device defaults
						:case case)))
   :directory (if directory-p directory
		  (and defaults-p (pathname-directory defaults
						      :case case)))
   :name (if name-p name
	     (and defaults-p (pathname-name defaults :case case)))
   :type (if type-p type
	     (and defaults-p (pathname-type defaults :case case)))
   :version (if version-p version
		(and defaults-p (pathname-version defaults)))))

(defvar *translator-directory* (truename *default-pathname-defaults*))

(defun subfile (directory-name-list &key name type)
  (make-pathname :host (pathname-host *translator-directory*)
		 :device (pathname-device *translator-directory*)
		 :directory (append (pathname-directory *translator-directory*)
				    directory-name-list)
		 :name name
		 :type type))

(defun make-load-file-pathname (file &optional 
				     (directory 
				      nil directory-p)
				     (type "lisp"))
  (setq file (pathname file))
  (make-pathname :host (pathname-host file)
		 :device (pathname-device file)
		 :directory (if directory-p
				(if (pathnamep directory)
				    (pathname-directory directory)
				    directory)
				(pathname-directory file))
		 :name (format nil "~A-load" (pathname-name file))
		 :type type))

(defun load-file-module (file)
  `(:module ,(pathname-name (make-load-file-pathname file nil nil))))

(defun load-file-modules (name files &rest options)
  `(:module ,name
	    ,@options
	    ,@(mapcar #'load-file-module files)))


(defvar *loaded-patches* nil)

(defvar *patch-source-directory*
  (make-pathname :directory
		 (append (pathname-directory *translator-directory*)
			 '(:up "patches"))
		 :defaults *translator-directory*))

(defun patch-file (patch &optional (binary-p t) (table-p nil))
  (declare (special *translator-source-directory* *translator-binary-directory*
		    *translator-source-type* *translator-binary-type*))
  (make-pathname :defaults (if binary-p
			       *translator-binary-directory*
			       (or *patch-source-directory*
				   *translator-source-directory*))
		 :name (if (eq patch :wild)
			   :wild
			   (format nil "~A-~D"
				   (if table-p "patch-table" "patch")
				   patch))
		 :type (if binary-p
			   *translator-binary-type*
			   *translator-source-type*)
		 #+genera :version #+genera :newest))

(defvar *available-patches* :unknown)

(defun available-patches (&optional (binary-p t) (table-p nil))
  (let* ((key (if table-p "patch-table-" "patch-"))
	 (key-length (length key)))
    (unless table-p
      (let ((tables (available-patches binary-p t)))
	(when tables
	  (setq *available-patches* :unknown)
	  (let* ((table (car (last tables)))
		 (table-path (patch-file table binary-p t)))
	    (unless binary-p
	      (let ((table-bin (patch-file table t t)))
		(unless (and (probe-file table-bin)
			     (> (file-write-date table-bin)
				(file-write-date table-path)))
		  (compile-file table-path :output-file table-bin))))
	    (load table-path)))))
    (sort (if (eq *available-patches* :unknown)
	      (mapcan #'(lambda (path)
			  (let ((name (pathname-name path)))
			    (when (and (> (length name) key-length)
				       (string-equal name key
						     :end1 key-length))
			      (list (parse-integer name :start key-length)))))
		      (directory (patch-file :wild binary-p)))
	      *available-patches*)
	  #'<)))

(defun unloaded-patches ()
  (mapcan #'(lambda (patch)
	      (unless (member patch *loaded-patches*)
		(list patch)))
	  (available-patches)))

(defun compile-patches ()
  (dolist (patch (available-patches nil))
    (let* ((source (patch-file patch nil))
	   (binary (patch-file patch t))
	   (compile-p (or (null (probe-file binary))
			  (>= (file-write-date source)
			      (file-write-date binary))))
	   (load-p (or compile-p (not (member patch *loaded-patches*)))))
      (when compile-p
	(compile-file source :output-file binary))
      (when load-p
	(load-patch patch)))))

(defun load-patch (patch)
  (let (#+mcl (ccl:*warn-if-redefine* nil)
	#+lucid (lcl:*redefinition-action* nil)
	#+allegro (excl:*redefinition-warnings* nil))
    (load-file (patch-file patch))
    (pushnew patch *loaded-patches*)
    patch))

(defun load-patches (&optional compile-p)
  (declare (special *load-binary-files-p*))
  (if (and compile-p (not *load-binary-files-p*))
      (compile-patches)
      (mapc #'load-patch (unloaded-patches))))


(defvar *rcs-revision-table* (make-hash-table :test 'equal))

(defun note-rcs-revision (source-spec revision-spec date-spec)
  (multiple-value-bind (rcs-source source rcs-revision rcs-date)
      (note-rcs-revision1 source-spec revision-spec date-spec)
    (note-rcs-revision2 rcs-source source rcs-revision rcs-date)))

(defun note-rcs-revision1 (source-spec revision-spec date-spec)
  (let ((source (subseq source-spec 9 (- (length source-spec) 2)))
	(revision (subseq revision-spec 11 (- (length revision-spec) 2)))
	(date (subseq date-spec 7 (- (length date-spec) 2))))
    (values source
	    (unless (equal source "")
	      (let* ((source-dir1 (position #\/ source :from-end t))
		     (source-dir2 (position #\/ source :from-end t
					    :end (1- source-dir1)))
		     (end (length source)))
		(concatenate 'string
			     (subseq source 0 (1+ source-dir2))
			     (subseq source (1+ source-dir1) (- end 2)))))
	    revision
	    date)))

(defun note-rcs-revision2 (rcs-source source rcs-revision rcs-date)
  (unless (equal rcs-source "")
    (setf (gethash source *rcs-revision-table*)
	  (list ':source rcs-source rcs-revision rcs-date))
    (let* ((key-names '(:rcs-source :name))
	   (source-dir-end (1+ (or (position #\/ source :from-end t)
				   #+genera (position #\> source :from-end t)
				   #+mcl (position #\: source :from-end t))))
	   (source-name (subseq source source-dir-end
				(position #\. source :start source-dir-end))))
      (dolist (key (list rcs-source source-name))
	(let* ((key-name (pop key-names))
	       (sources (gethash key *rcs-revision-table*)))
	  (unless (member source sources :test #'equal)
	    (setf (gethash key *rcs-revision-table*)
		  (cons key-name
			(sort (cons source sources) #'string<))))))))
  source)

(defun rcs-revision (source)
  (let ((value (gethash source *rcs-revision-table*)))
    (when value
      (if (eq (car value) ':source)
	  (third value)
	  (rcs-revision (cadr value))))))

(defun rcs-loaded-revisions ()
  (let ((list nil))
    (maphash #'(lambda (key value)
		 (let ((name (pathname-name key))
		       (revision (caddr value)))
		   (when (and (eq (car value) ':source)
			      (let ((rcs-name (pathname-name (cadr value))))
				(or (string= name rcs-name)
				    (not (string= revision
						  (rcs-revision rcs-name))))))
		     (push (list name revision) list))))
	     *rcs-revision-table*)
    (sort list #'string< :key #'car)))

(defvar *show-rcs-date-p* nil)
(defvar *show-rcs-prefix* "/u/projects/trans/lisp/")

(defun string-diff (string1 string2)
  (if (and (stringp string2)
	   (string= string1 string2
		    :end1 (length string2)))
      (subseq string1 (length string2))
      string1))

(himpl:note-rcs-revision
 "$Source: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/chestnut/src/trans/host-implementation.lisp,v $"
 "$Revision: 1.3 $"
 "$Date: 2007-11-14 22:02:53 $")

(himpl:note-rcs-revision
 *host-implementation-package-source*
 *host-implementation-package-revision*
 *host-implementation-package-date*)

(defun show-rcs-revision (&optional source)
  (if source
      (progn
	(when (pathnamep source) (setq source (namestring source)))
	(unless (stringp source)
	  (error "The argument to ~S must be a string, a pathname, or NIL"
		 'show-rcs-revision))
	(let ((value (gethash source *rcs-revision-table*)))
	  (cond ((null value)
		 (format t "~&No rcs-revision recorded for ~S.~%" source))
		((not (consp value))
		 (error "error in show-rcs-revision"))
		((eq (car value) ':source)
		 (unless *show-rcs-date-p* (setq value (butlast value)))
		 (if (string= (pathname-name source)
			      (pathname-name (cadr value)))
		     (format t "~&~A:~{ ~A~}~%"
			     (string-diff source *show-rcs-prefix*)
			     (cddr value))
		     (format t "~&~A:~%   ~{ ~A~}~%"
			     (string-diff source *show-rcs-prefix*)
			     (cons (string-diff (cadr value) *show-rcs-prefix*)
				   (cddr value)))))
		(t
		 (mapc #'show-rcs-revision (cdr value))))))
      (let ((list nil))
	(maphash #'(lambda (key value)
		     (when (eq (car value) ':source)
		       (push key list)))
		 *rcs-revision-table*)
	(setq list (sort list #'string<))
	(mapc #'show-rcs-revision list)))
  (values))

(eval-when (compile load eval) ; These are defined in translator.lisp
#-(or Chestnut MCL)
(proclaim '(special *translator-release* *current-translator-release*))
#+(or Chestnut MCL)
(declaim (special *translator-release* *current-translator-release*))
)

(defun print-*current-translator-release*-form (&optional name date)
  (unless date
    (setq date
	  (let ((dtime (multiple-value-list (get-decoded-time))))
	    (format nil "~2,'0D/~2,'0D/~2,'0D"
		    (fifth dtime) (fourth dtime) (mod (sixth dtime) 100)))))
  (unless name
    (setq name (format nil "~A+  ~A" *translator-release* date)))
  (pprint `(defparameter *current-translator-release*
	     '((,name ,date) ,@(rcs-loaded-revisions))))
  (unless (member ':translator-supports-clos *features*)
    (format t "~&Be sure you had the clos version loaded.~%"))
  (format t "~&Put this form at the end of the file translator.lisp~%")
  (format t "You might want to add 1 to the \"translator\" revision.~%")
  (format t "Remember to manually add entries for:~%")
  (format t " lisp/*build.lisp, lisp/load*-trans.lisp, and host/*.lisp~%"))

(defun revision-list (revision)
  (let ((start 0)
	(values nil))
    (loop (multiple-value-bind (integer index)
	      (parse-integer revision :start start :junk-allowed t)
	    (when (zerop index)
	      (return (nreverse values)))
	    (push integer values)
	    (when (= index (length revision))
	      (return (nreverse values)))
	    (setq start (1+ index))))))

(defun revision-difference (release1 release2)
  (cond ((or (null release1) (null release2))
	 nil)
	((eql (car release1) (car release2))
	 (revision-difference (cdr release1) (cdr release2)))
	(t
	 (cons (- (car release1) (car release2))
	       (revision-difference (cdr release1) (cdr release2))))))

(defun translator-unreleased-files (&optional (include-version-p t))
  (mapcan #'(lambda (name+revision)
	      (let* ((name (car name+revision))
		     (revision (cadr name+revision))
		     (rcs-revision (rcs-revision name)))
		(when (and rcs-revision
			   (not (string= rcs-revision
					 revision)))
		  (list (if include-version-p
			    (list name
				  (revision-difference
				   (revision-list rcs-revision)
				   (revision-list revision)))
			    name)))))
	  (cdr *current-translator-release*)))

(defun translator-version (&optional show-unreleased-files-p)
  (let ((clos-p (member ':translator-supports-clos *features*)))
    (if (not show-unreleased-files-p)
	(format nil "~A  (~A)" *translator-release* 
		(if clos-p "CLOS" "non-CLOS"))
	(let* ((files (translator-unreleased-files))
	       (version1 (format nil "~A  (~A)"
				 (caar *current-translator-release*)
				 (if clos-p "CLOS" "non-CLOS")))
	       (version (if *loaded-patches*
			    (let ((first (car (last *loaded-patches*)))
				  (last (first *loaded-patches*)))
			      (if (and (cdr *loaded-patches*)
				       (dotimes (i (- last first) t)
					 (unless (member (+ i first)
							 *loaded-patches*)
					   (return nil))))
				  (format nil "~A  (patches: ~D-~D)"
					  version1 first last)
				  (format nil "~A  (patches: ~{~D~^, ~})"
					  version1 
					  (reverse *loaded-patches*))))
			    version1)))
	  (if (null files)
	      version
	      (format nil "~A~@[~%Files checked in since ~A:~{~%~{~A~}~}~]"
		      version
		      (cadar *current-translator-release*)
		      (let ((lines nil)
			    (line nil)
			    (size 0))
			(loop (when (null files)
				(when line (push (nreverse line) lines))
				(return (nreverse lines)))
			      (let* ((fstr (format nil "~{~A +~{~D~^.~}~}~@[,~]"
						   (pop files)
						   files))
				     (flen (length fstr)))
				(when (and (plusp size)
					   (>= (+ size flen 1) 80))
				  (setq size 0)
				  (push (nreverse line) lines)
				  (setq line nil))
				(when line
				  (push " " line)
				  (incf size))
				(push fstr line)
				(incf size flen))))))))))

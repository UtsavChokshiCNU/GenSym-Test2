;;; see lw64.log for the reason of this patch.

(in-package :uiop/configuration)

(with-upgradability ()
  (defun resolve-absolute-location (x &key ensure-directory wilden)
    "Given a designator X for an absolute location, resolve it to a pathname"
    (ensure-pathname
     (etypecase x
       (null nil)
       (pathname x)
       (string
        (let ((p #-mcl (parse-namestring x)
                 #+mcl (probe-posix x)))
          #+mcl (unless p (error "POSIX pathname ~S does not exist" x))
          (if ensure-directory (ensure-directory-pathname p) p)))
       (cons
        (return-from resolve-absolute-location
          (if (null (cdr x))
              (resolve-absolute-location
               (car x) :ensure-directory ensure-directory :wilden wilden)
              (merge-pathnames*
               (resolve-relative-location
                (cdr x) :ensure-directory ensure-directory :wilden wilden)
               (resolve-absolute-location
                (car x) :ensure-directory t :wilden nil)))))
       ((eql :root)
        ;; special magic! we return a relative pathname,
        ;; but what it means to the output-translations is
        ;; "relative to the root of the source pathname's host and device".
        (return-from resolve-absolute-location
          (let ((p (make-pathname :directory '(:relative))))
            (if wilden (wilden p) p))))
       ((eql :home)
	;; GENSYMCID-1839: Failures in Lisp unit tests after upgrading lisp-unit package
	;;
	;; In LispWorks, (user-homedir-pathname) returns #p"" under SYSTEM (in TeamCity) but ASDF
	;; requires absolute pathnames here. -- Chun Tian (binghe), July 18, 2016.
	#+(and lispworks mswindows) #p"/"
	#-(and lispworks mswindows) (user-homedir-pathname))
       ((eql :here) (resolve-absolute-location
                     (or *here-directory* (pathname-directory-pathname (load-pathname)))
                     :ensure-directory t :wilden nil))
       ((eql :user-cache) (resolve-absolute-location
                           *user-cache* :ensure-directory t :wilden nil)))
     :wilden (and wilden (not (pathnamep x)))
     :resolve-symlinks *resolve-symlinks*
     :want-absolute t)))

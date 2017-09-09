;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(in-package :tests)
(load "../mi/dir-list")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                                         AUXILIARY FUNCTIONS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Deletes file or directory (recursive)
(defun delete-file-or-directory (name)
  (if (directory-pathname-p name)
       #+clozure (ccl::recursive-delete-directory name)
       #-clozure
      (progn 
        (dolist (x (list-directory name))
          (delete-file-or-directory x))
        #+sbcl (sb-posix:rmdir name)
        #+lispworks (lispworks:delete-directory name))
      (delete-file name)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Create file if it does not exist
(defun touch (filename)
  (with-open-file (s filename :direction :output :if-exists :error)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Create listed files in specified directory and returns created file' pathnames
(defun create-files (names dir)
  (let ((pathnames) (absolute-pathname)(relative-pathname))
    (dolist (file (sort names #'string<))
      (setq relative-pathname (merge-pathnames file dir))
      (ensure-directories-exist relative-pathname)
      (touch relative-pathname)
      (setq absolute-pathname (make-pathname
                                :defaults (merge-pathnames relative-pathname)
                                :version nil))
      (setq pathnames (append pathnames (list absolute-pathname))))
    pathnames))

(defun compare-pathname-sets-p (file-list-1 file-list-2)
  (set-equal (mapcar #'truename file-list-1) (mapcar #'truename file-list-2)))

(defun up ()
  #-lispworks :up
  #+lispworks :back)

(defun pathname-drive (pathname)
  #-lispworks (pathname-device pathname)
  #+lispworks (pathname-host pathname))

  (defmacro assert-pathname-sets-equal (pathname-set-1 pathname-set-2)
  `(assert-equality #'compare-pathname-sets-p ,pathname-set-1 ,pathname-set-2))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                                                TESTS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Test for component-present-p function
;; (component-present-p value) returns
;;      nil if value is nil or :unspecific
;;      T otherwise
(define-test test-component-present-p
  (assert-false (component-present-p nil))
  (assert-false (component-present-p :unspecific))
  (assert-true  (component-present-p "component-name")))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Test for directory-pathname-p function
;; (directory-pathname-p path) returns T if path is specified in directory form,
;;  nil otherwise
(define-test test-directory-pathname-p
  ; pathnames in file form
  (assert-false (directory-pathname-p "c:/some/path"))
  (assert-false (directory-pathname-p "some/path"))
  (assert-false (directory-pathname-p "../some/path"))
  
  ; pathnames in directory form
  (assert-true  (directory-pathname-p "c:/some/path/"))
  (assert-true  (directory-pathname-p "some/path/"))
  (assert-true  (directory-pathname-p "../some/path/")))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Test for pathname-as-directory function
;; (pathname-as-directory pathname) returns pathname in directory form
(define-test test-pathname-as-directory
  (loop 
     for (dirname device-expected dir-expected) in 
     (list 
      ;; pathnames in file form
      '("c:/some/path"    "c" (:absolute "some" "path"))
      '("some/path"        nil (:relative "some" "path"))
      `("../some/path"    nil (:relative ,(up) "some" "path"))
      ;; pathnames in directory form
      '("c:/some/path/"  "c" (:absolute "some" "path"))
      '("some/path/"      nil (:relative "some" "path"))
      `("../some/path/"  nil (:relative ,(up) "some" "path")))
     do
     (setq
      path-as-dir (pathname-as-directory dirname) 
                                        ; transform dirname to pathname
      device (pathname-drive path-as-dir)     ; extract actual device
      dir    (pathname-directory path-as-dir) ; extract actual directory
      name   (pathname-name path-as-dir)      ; extract actual name
      type   (pathname-type path-as-dir))     ; extract actual type
        
     ;; actual device must be equal to expected
     (assert-equal device-expected device)
     ;; actual directory must be equal to expected
     (assert-equal dir-expected dir)
     ;; actual name must be nil or :unspecific
     (assert-false (and name (not (eql name :unspecific))))
     ;; actual type must be nil or :unspecific
     (assert-false (and type (not (eql type :unspecific))))
     ;; wildchars appending to dirname cause errors, only concrete directory 
     ;; name is enabled
     (assert-error 'error (pathname-as-directory 
                           (concatenate 'string dirname "*")))

     #+sbcl ; only sbcl doesn't accept both ? anywehere and * at the beginning
                                        ; of the disk
     (progn
       (assert-error 'error (pathname-as-directory 
                             (concatenate 'string "*" dirname)))
       (assert-error 'error (pathname-as-directory 
                             (concatenate 'string dirname "?")))
       (assert-error 'error (pathname-as-directory 
                             (concatenate 'string "?" dirname))))))
      
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Test for list-directory function
(define-test test-list-directory
  (let* ((tempdir "test-list-directory-temp-dir/")
         (names '("a.html" "a.lisp" "a.txt"
                  "b.html" "b.lisp" "b.txt"
                  "c.html" "c.lisp" "c.txt"
                  "d.html" "d.lisp" "d.txt"))
         ;;create files in tempdir
         (pathnames (create-files names tempdir)))

    ;; compare collected pathnames with pathnames returned 
    ;; by list-directory function
    (assert-pathname-sets-equal pathnames (list-directory tempdir))
    ;; file pathnames for list-directory is disabled
    (assert-false (list-directory (pathname "some/path/file.lisp")))
    ;; remove created directory and files
    ;; compare collected pathnames with pathnames returned
    ;; by list-directory function
    (assert-pathname-sets-equal pathnames (list-directory tempdir))
    ;; file pathnames for list-directory is disabled
    (assert-false (list-directory (pathname "some\\path\\file.lisp")))
    ;;(assert-error 'error (list-directory (pathname "some\\path\\file.lisp")))
    ;; remove created directory and files
    (delete-file-or-directory tempdir)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Test fot lisp-p function
;; (lisp-p file) returns true for lisp file
(define-test test-lisp-p
  (assert-true  (lisp-p "c:/some/path/file.lisp"))
  (assert-true  (lisp-p "some/path/file.lisp"))
  (assert-true  (lisp-p "../some/path/file.lisp"))
  (assert-false (lisp-p "c:/some/path/file.txt"))
  (assert-false (lisp-p "some/path/file.txt"))
  (assert-false (lisp-p "../some/path/file.txt"))
  (assert-false (lisp-p "c:/some/path/"))
  (assert-false (lisp-p "some/path/"))
  (assert-false (lisp-p "../some/path/"))
  (assert-false (lisp-p "c:/some/path/lisp"))
  (assert-false (lisp-p "some/path/lisp"))
  (assert-false (lisp-p "../some/path/lisp"))
  (assert-false (lisp-p "../some/path/lisp/")))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Test for list-directory function
;; (walk dirname test recursive) returns list of pathnames for files 
;; from specified directory
;; Returned list contains file' pathnames that correspont test function
(define-test test-walk
  (let ((tempdir "test-walk-temp-dir/")
        (lisp-in-tempdir-files ; lisp files placed in tempdir directly
         '("defs.lisp"
           "dir-list.lisp"
           "mi-calc.lisp"
           "mi-main.lisp"
           "walker.lisp"))
        (lisp-in-subdir-files           ; lisp files placed in subdir
         '("subdir/files.lisp"
           "subdir/for.lisp"
           "subdir/walk.lisp"
           "subdir/function.lisp"
           "subdir/testing.lisp"))
        (java-files              ; java files in different directories
         '("src/biz/gdev/mitool/reportgen/util/HTMLConstants.java"
           "src/biz/gdev/mitool/reportgen/HTMLGenerator.java"
           "src/biz/gdev/mitool/reportgen/util/HTMLGeneratorUtil.java"
           "src/biz/gdev/mitool/reportgen/IGenerator.java"
           "src/biz/gdev/mitool/reportgen/LispMI.java"
           "src/biz/gdev/mitool/reportgen/util/ResultsBean.java"
           "src/biz/gdev/mitool/reportgen/TXTGenerator.java"))
        (other-files   ; junk that is interfering to our carefree life
         '("lib/LispMI.jar"
           "lib/log4j-1.2.14.jar"
           "lib/stax-1.2.0.jar"
           "lib/stax-api-1.0.1.jar"
           "res/reportgen/mireport.css"
           "res/log4j.properties"
           "config.txt"
           "build.xml"
           "lib/junk.txt"
           "lib/junk.html"
           "src/biz/gdev/mitool/reportgen/junk.txt"
           "src/biz/gdev/mitool/reportgen/junk.html"
           "src/biz/gdev/mitool/reportgen/util/junk.txt"
           "src/biz/gdev/mitool/reportgen/util/junk.html"
           "junk.txt"
           "junk.html"
           "subdir/junk.txt"
           "subdir/junk.html"))
        
        (lisp-in-tempdir-pathnames)
        (lisp-in-subdir-pathnames)
        (java-pathnames))
  
    ;; create listed files
    (setq
     lisp-in-tempdir-pathnames  (create-files lisp-in-tempdir-files tempdir)
     lisp-in-subdir-pathnames   (create-files lisp-in-subdir-files  tempdir)
     java-pathnames  (create-files java-files tempdir))


    (create-files other-files tempdir)

    ;; by default walk function is not walking subdirs
    ;; lisp files in tempdir directly
    (assert-pathname-sets-equal lisp-in-tempdir-pathnames 
                                (walk tempdir :test #'lisp-p))

    ;; lisp foles in subdir
    (assert-pathname-sets-equal lisp-in-subdir-pathnames 
                                (walk (merge-pathnames "subdir" tempdir) 
                                      :test #'lisp-p))
    (assert-pathname-sets-equal 
     java-pathnames 
     (walk tempdir :test #'(lambda (file) 
                             (string-equal "java" (pathname-type file)))
           :recursive T))

    (delete-file-or-directory tempdir)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Test for list-for-lisp-files function
;; (list-for-lisp-files config recursive nil) returns list for lisp files 
;; in folder specified
;; in config file (walking direcrory recursively if needed)
(define-test test-list-for-lisp-files
  (let* ((config "test-list-for-lisp-files-config")
         (tempdir "test-list-for-lisp-files-temp-dir/")
         (lisp-in-tempdir-files ; lisp files placed in tempdir directly
          '("defs.lisp"
            "dir-list.lisp"
            "mi-calc.lisp"
            "mi-main.lisp"
            "walker.lisp"))
         (lisp-in-subdir-files          ; lisp files placed in subdir
          '("subdir/files.lisp"
            "subdir/for.lisp"
            "subdir/walk.lisp"
            "subdir/function.lisp"
            "subdir/testing.lisp"))
         (other-files  ; junk that is interfering to our carefree life
          '("lib/LispMI.jar"
            "lib/log4j-1.2.14.jar"
            "lib/stax-1.2.0.jar"
            "lib/stax-api-1.0.1.jar"
            "res/reportgen/mireport.css"
            "res/log4j.properties"
            "config.txt"
            "build.xml"
            "lib/junk.txt"
            "lib/junk.html"
            "junk.txt"
            "junk.html"
            "subdir/junk.txt"
            "subdir/junk.html"))
         (lisp-files (append lisp-in-tempdir-files lisp-in-subdir-files))
         (lisp-in-tempdir-pathnames)
         (lisp-in-subdir-pathnames)
         (lisp-pathnames))

    ;; write string containing path to tempdir into config file
    (with-open-file (s config :direction :output :if-exists :error)
      (write-line tempdir s))
    
    ;; create lisp files in tempdir and their subdir
    (setq
     lisp-in-tempdir-pathnames  (create-files lisp-in-tempdir-files tempdir)
     lisp-in-subdir-pathnames   (create-files lisp-in-subdir-files  tempdir))
    ;; create other files
    (create-files other-files tempdir)

    ;; test list-for-lisp-files without recursion
    (assert-pathname-sets-equal 
     lisp-in-tempdir-pathnames (list-for-lisp-files config))
    
    ;; merge pathname' lists
    (setq lisp-pathnames (merge
                          'list
                          lisp-in-tempdir-pathnames
                          lisp-in-subdir-pathnames
                          #'(lambda (p1 p2)
                              (string< (namestring p1) (namestring p2)))))
      
    ;; test list-for-lisp-files with recursion
    (assert-pathname-sets-equal lisp-pathnames (list-for-lisp-files config T))

    (delete-file-or-directory tempdir)
    (delete-file config)))

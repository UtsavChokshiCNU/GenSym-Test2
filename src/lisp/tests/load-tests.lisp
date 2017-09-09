(in-package :cl-user)

(eval-when (:compile-toplevel :load-toplevel)
  (error "Do not compile this file"))

(defun pathname-from-here (relative-pathname)
  ; pathname relative to the directory of *load-truename*
  (let* ((path-to-load-truename (make-pathname :defaults (pathname #.*load-truename*) :name nil :type nil)))
    (merge-pathnames relative-pathname path-to-load-truename)))

(format t "Begin loading ASDF.~%")
#-asdf
(load (compile-file (pathname-from-here #p"../../asdf/asdf.lisp")))
#+(and asdf3 lispworks) ; SBCL uses old ASDF not compatible with this patch.
(load (compile-file (pathname-from-here #p"../../asdf/asdf-patch.lisp")))
(format t "End loading ASDF.~%")

;; the first three packages must be added manually
(setq asdf:*central-registry*
      (mapcar 'pathname-from-here
              (list #p"../../asdf/packages/cl-fad-0.7.3/"
                    #p"../../asdf/packages/alexandria-20150505-git/"
                    #p"../../asdf/packages/bordeaux-threads-0.8.3/")))

(format t "asdf:*central-registry* = ~A~%" asdf:*central-registry*)

(format t "Begin loading CL-FAD.~%")
(asdf:load-system :cl-fad)
(format t "End loading CL-FAD.~%")

;; then use CL-FAD to bootstrap all other packages
(setq asdf:*central-registry*
      (append
       (list (pathname-from-here ""))
       (cl-fad:list-directory (pathname-from-here "../../asdf/packages/"))
       ))
(format t "asdf:*central-registry* = ~A~%" asdf:*central-registry*)

(asdf:load-system :mock-macro)

;; moved here from run-tests.lisp
(pushnew :exclude-possible-bugs *features*)

(defun prepare-g2-macros-for-mocking ()
  (dolist (name
    '("ab::frame-status-and-notes" "AB::MODULE-SYSTEM-TABLE-BELONGS-TO?"
                                   "ab::top-level-kb-module?" "ab::workspace-spacial-index?"))
    (mock-macro:prepare-macro-for-mocking (read-from-string name))))

(defun load-g2 (options)
  (let ((*default-pathname-defaults* (truename "..")))
    (pushnew :under-test *features*)
    (load (pathname-from-here "../123.lisp"))
    (funcall (intern "G2MENU")
	     (funcall (intern "CONVERT-OPTION-AND-SWITCHES-TO-LIST") options))))

(defun load-g2-development-mode (options)
  "This is used when we develop unit test suite. Hence we need not to run all the suite once, but
only load it and make it possible to run it more than once"
  (let ((*default-pathname-defaults* (truename "..")))
    (pushnew :under-test *features*)
    (load (pathname-from-here "../123.lisp"))
    (g2menu (convert-option-and-switches-to-list options))))

(defun load-everything (&optional (123-options "1pm"))
  (load-g2 123-options)
  (asdf:load-system :tests :force t))

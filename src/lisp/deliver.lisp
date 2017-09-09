;;;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-

;;; Standalone G2 Server built directly from Lisp
;;; NOTE: please do a "1rpm" build before using this script.

;;; Usage (command-line): 
;;;   * lispworks -build deliver.lisp [<123.lisp options. Default 1pm>]
;;;     E.g. lispworks -build deliver.lisp 7rpm
;;;   * wx86cl -l deliver.lisp -- 1rpm
;;;   * wx86cl64 -l deliver.lisp -- 1rpm

;;; Step 1, Load 123.lisp
;;; Step 2, Load G2 System
;;; Step 3, Deliver executions

(in-package :cl-user)

;; Stop from compile this file
(eval-when (:compile-toplevel)
  (error "DO NOT COMPILE THIS FILE (~A)!" *compile-file-pathname*))

(defun pathname-from-here (relative-pathname)
  ; pathname relative to the directory of *load-truename*
  (let* ((path-to-load-truename (make-pathname :defaults (pathname #.*load-truename*) :name nil :type nil)))
    (merge-pathnames relative-pathname path-to-load-truename)))

#+lispworks
(load-all-patches)

(defparameter *options* "7rpm")

#+lispworks
(defparameter *level* 0)

;; Step 0

#-asdf
(load (compile-file #p"../asdf/asdf.lisp"))
#+(and asdf3 lispworks) ; SBCL uses old ASDF not compatible with this patch.
(load (compile-file #p"../asdf/asdf-patch.lisp"))

;; the first three packages must be added manually
(setq asdf:*central-registry*
      (list #p"../asdf/packages/cl-fad-0.7.3/"
	    #p"../asdf/packages/alexandria-20150505-git/"
	    #p"../asdf/packages/bordeaux-threads-0.8.3/"
	    '*default-pathname-defaults*))

(asdf:load-system :cl-fad)

;; then use CL-FAD to bootstrap all other packages
(setq asdf:*central-registry*
      (nconc (cl-fad:list-directory "../asdf/packages/")
	     (list '*default-pathname-defaults*)))

(asdf:load-system :trivial-backtrace)

;; Step 1
(let ((*features* (cons :under-test *features*)))
  (load #p"../lisp/123.lisp")) ; TODO

;; Step 2
(g2menu (convert-option-and-switches-to-list *options*))

;; Step 2.5: delete advice for ab::launch-ab so that it starts G2 in current thread.
#+lispworks
(delete-advice ab::launch-ab ab::launch-ab-in-new-thread)

;; Windows XP and Windows 2003 Server can't handle 32 Mb sizes in an executable
#+(and lispworks (not lispworks-64bit))
(sys:set-maximum-segment-size 7 :function 31)

;; Step 3
(format t "Saving G2 into a standalone executable ...~%")

(defun entry-function ()
  ;; disable the default error trapping,
  (let* ((ab::do-error-trapping? nil))
    ;; and catch all errors and print the backtrace and exit.
    (handler-bind
	((error #'(lambda (condition)
		    (trivial-backtrace:print-backtrace
		      condition
		      :output "backtrace.txt"
		      :if-exists :supersede
		      :verbose t)
		    (uiop:quit 1))))
      (ab::launch-ab))))

(compile 'entry-function)

(let ((*default-pathname-defaults* (truename "."))
      (destination-dir "../../dst/g2/opt/"))
  #+lispworks
  (deliver 'entry-function
           (pathname-from-here (concatenate 'string destination-dir "g2-lw64"))
           *level*
	   :keep-eval t :multiprocessing t
	   :console :input)
  #+clozure
  (ccl:save-application
    (pathname-from-here (concatenate 'string destination-dir "g2-ccl64" #+windows-target ".exe"))
    :toplevel-function 'entry-function
    :prepend-kernel t)

  #+sbcl
  (sb-ext:save-lisp-and-die
    (pathname-from-here (concatenate 'string destination-dir "g2-sbcl64" #+win32 ".exe"))
    :executable t
    :toplevel 'entry-function
    :save-runtime-options t))

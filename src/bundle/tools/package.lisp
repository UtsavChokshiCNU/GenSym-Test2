;;;; -*- Mode: Lisp -*-

(eval-when (:compile-toplevel :load-toplevel :execute)
  (unless (find-package :bundle)
    (defpackage bundle
      (:use :common-lisp))))

(in-package :bundle)

(declaim (inline memq
                 environment-variable
                 string-append
                 shell
                 quit))

(defun memq (obj lst)
  #+lispworks
  (sys:memq obj lst)
  #-lispworks
  (member obj lst :test #'eq))

(defun environment-variable (name)
  #+lispworks
  (lw:environment-variable name)
  #+sbcl
  (sb-ext:posix-getenv name)
  #-(or lispworks sbcl)
  (error "ENVIRONMENT-VARIABLE is not supported for this platform yet."))

(defun string-append (&rest strings)
  "Appends strings. Makes sure that the result string can
contain all character types of all the string arguments."
  (declare (dynamic-extent strings))
  #-lispworks
  (apply #'concatenate 'string strings)
  #+lispworks
  (apply #'lw:string-append strings))

(defvar *verbose-out* t)
(defun shell (command)
  #+lispworks
  (system:call-system-showing-output
   command
   :shell-type "/bin/sh"
   :show-cmd nil
   :prefix ""
   :output-stream *verbose-out*)
  #+sbcl
  (sb-ext:process-exit-code
   (apply #'sb-ext:run-program
          #+win32 "sh" #-win32 "/bin/sh"
          (list  "-c" command)
          :input nil :output *verbose-out*
          #+win32 '(:search t) #-win32 nil))
  #-(or lispworks sbcl)
  (error "SHELL is not supported for this platform yet."))

(defun quit ()
  #+lispworks
  (lw:quit)
  #+sbcl
  (sb-ext:quit)
  #-(or lispworks sbcl)
  (error "QUIT is not supported for this platform yet."))

;;;; -*- Mode: Lisp; Package: CL-USER; Base: 10; Syntax: Common-Lisp -*-
;;;;
;;;; Module LICENSING-SERVER: G2 standalone licensing server

;;; Copyright (c) 2010 Versata Software, Inc.
;;; All Rights Reserved.

;;; Author: Chun Tian (binghe) <binghe.lisp@gmail.com>

(in-package :cl-user)

(defparameter *major-version* 2)
(defparameter *minor-version* 0)
(defparameter *revision* 0)

(defun show-startup-message (&optional (stream *standard-output*))
  (format stream "G2 Licensing Server ~D.~Dr~D at Port 7535.~%"
          *major-version* *minor-version* *revision*))

(defun patch-pathname (i)
  (make-pathname :name (format nil "~4,'0D" i)
                 :type sys:*binary-file-type*
                 :directory '(:relative "patch" "licensing-server")
                 :defaults *default-pathname-defaults*))

(defun list-patches ()
  (let ((patch-files nil))
    (loop for i from 1 do
       (let ((patch-file (patch-pathname i)))
         (if (probe-file patch-file)
             (push patch-file patch-files)
           (loop-finish))))
    (nreverse patch-files)))

(defun load-patches (&aux (counter 0))
  (dolist (i (list-patches))
    (handler-case (prog1 (load i :verbose nil :print nil)
                    (incf counter))
      (error (c) (format *error-output* "Error when loading a patch (~A)~%" i))))
  (format *error-output* "~A Patch(s) Loaded.~%" counter))

(defun licensing-server ()
  (load-patches)
  (show-startup-message)
  (ab::start-licensing-server))

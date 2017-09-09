;;;; -*- Mode: Lisp; Package: CL-USER; Base: 10; Syntax: Common-Lisp -*-
;;;;
;;;; DELIVER-LC: Standalone Licensing Client written in LW

;;; Copyright (c) 2010 Versata Software, Inc.
;;; All Rights Reserved.

;;; Author: Chun Tian (binghe) <binghe.lisp@gmail.com>

;;; Usage (command-line): lispworks -build deliver-lc.lisp
;;; IMPORTANT: to build all licensing client programs, run this script twice.

(in-package :cl-user)

;; Stop from compile this file
(eval-when (:compile-toplevel)
  (error "DO NOT COMPILE THIS FILE (~A)!" *compile-file-pathname*))

(load-all-patches)

(load (make-pathname :name "translations" :type "lisp"
                     :directory (append (pathname-directory *load-truename*) '("server"))
                     :defaults *load-truename*))

(defparameter *client-level* 4)

(defparameter *icon-file* #p"SRC:G2;C;G2.ICO")

(defparameter *client-file*
  #+mswindows #p"SRC:LIC;LICENSING-CLIENT-GUI.EXE"
  #-mswindows #p"SRC:LIC;LICENSING-CLIENT-GUI")

;; Step 3 (License Server & Client GUI)

(compile-file #p"SRC:LIC;LICENSING-CLIENT.LISP" :load t)

;; Step 4 (delivery)
(deliver 'licensing-client
         *client-file*
         *client-level*
         :icon-file *icon-file*
         :keep-eval nil
         :keep-fasl-dump t
         :keep-load-function :full
         :keep-lisp-reader t
         :interface :capi
         :multiprocessing t)

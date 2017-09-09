;;;; -*- Mode: Lisp; Package: CL-USER; Base: 10; Syntax: Common-Lisp -*-
;;;;
;;;; DELIVER-LS: Standalone Licensing Server/Client written in LW

;;; Copyright (c) 2010 Versata Software, Inc.
;;; All Rights Reserved.

;;; Author: Chun Tian (binghe) <binghe.lisp@gmail.com>

;;; Usage (command-line): lispworks -build deliver-ls.lisp

(in-package :cl-user)

;; Stop from compile this file
(eval-when (:compile-toplevel)
  (error "DO NOT COMPILE THIS FILE (~A)!" *compile-file-pathname*))

(load-all-patches)

(load (make-pathname :name "translations" :type "lisp"
                     :defaults *load-truename*))

;; Step 1
(let ((*features* (cons :under-test *features*)))
  (load #p"SRC:LISP;123.LISP"))

(defparameter *build-options* "1nrpm")
(defparameter *server-level* 1)

(defparameter *server-file*
  #+mswindows #p"SRC:LIC;SERVER;LICENSING-SERVER.EXE"
  #-mswindows #p"SRC:LIC;SERVER;LICENSING-SERVER")

(defparameter *icon-file* #p"SRC:G2;C;G2.ICO")

;; Step 2
(g2menu (convert-option-and-switches-to-list *build-options*))

;; Step 3 (License Server)
(compile-file #p"SRC:LIC;SERVER;LICENSING-SERVER.LISP" :load t)

;; Step 4 (delivery)
(deliver 'licensing-server
         *server-file*
         *server-level*
         :icon-file *icon-file*
         :console t
         :keep-eval t
         :keep-fasl-dump t
         :keep-load-function :full
         :keep-lisp-reader t
         :multiprocessing t)

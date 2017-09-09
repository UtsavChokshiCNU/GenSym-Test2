;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module INTEROP

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Sarge Rogatch, 



;;;; Introduction

;;; This file is part of Telewindows and G2, and contains code which is shared
;;; between them to implement DLL interoperability and integration into the
;;; modern development environments and frameworks.

;;;; Forward References
; [tam.srogatch][2010-10-23]: Left here for now, just to have an example
(declare-forward-references
  (process-view-init-plist function)
  (encode-dock-and-neighbor function))

(def-gensym-c-function c-load-dynamic-library
    (:fixnum-int "g2ext_load_dynamic_library")
  ((:wide-string file-name)
   ; next parameter like: (:wide-string message-string)
  )
)

(defun-for-system-procedure g2-load-dynamic-library
  ((file-name text))
  (declare (values item))
  (values 
	(make-evaluation-integer (
		c-load-dynamic-library file-name))
  )
)


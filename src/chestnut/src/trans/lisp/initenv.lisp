;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; initenv.lisp -- initializing the initial global environment
;;;
;;; Author :  Kim Barrett
;;; Date   :  05 Mar 1991
;;;
;;; Copyright (c) 1991, Chestnut Software Inc.
;;;
;;; Finally initialize the initial environment.

(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/initenv.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006/02/28 21:59:07 $")

;;; First declare the built-in packages.  These were actually created
;;; in the host environment with host:defclass in rpacks.lisp, but now 
;;; provide information so we can produce run-time initialization code.
;;; Note the all the exports from these packages are established later,
;;; as we process the database.


;;; TCLOS has to be installed before TCL, because some symbols from
;;; TCLOS are imported into TCL

(install-static-package "TCLOS"
    (:nicknames "TRANSLATOR-CLOS")
    (:use)    ; uses nothing
    (:runtime-name "CLOS")
    (:runtime-nicknames "TCLOS" "TRANSLATOR-CLOS")
    )

(install-static-package "TCL"
    (:nicknames "TRANSLATOR-COMMON-LISP")
    (:use)    ; uses nothing
    (:runtime-name "COMMON-LISP")
    (:runtime-nicknames "LISP" "CL" "TCL" "TRANSLATOR-COMMON-LISP")
    )

(install-static-package "TX"
    (:nicknames "TRANSLATOR-EXTENSIONS")
    (:use)    ; uses nothing
    )

(install-static-package "TRUN"
    (:nicknames "TRANSLATOR-RUNTIME")
    (:use)    ; uses nothing
    )

(install-static-package "TCLOS-RUN"
    (:nicknames "TRANSLATOR-CLOS-RUNTIME")
    (:use)    ; uses nothing
    (:runtime-name "CLOS-RUN")
    (:runtime-nicknames "TCLOS-RUN" "TRANSLATOR-CLOS-RUNTIME")
    )

(install-static-package "TCLOSX"
    (:nicknames "TRANSLATOR-CLOS-EXTENSIONS")
    (:use)    ; uses nothing
    (:runtime-name "CLOSX")
    (:runtime-nicknames "CLOS-EXTENSIONS"
			"TCLOSX"
			"TRANSLATOR-CLOS-EXTENSIONS")
    )

(install-static-package "KEYWORD"
    (:use)    ; uses nothing
    )

(install-static-package "TCL-USER"
    (:use "TCL")
    (:runtime-name "COMMON-LISP-USER")
    (:runtime-nicknames "CL-USER" "TCL-USER" "USER")
    )


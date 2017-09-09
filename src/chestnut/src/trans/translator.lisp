;;; -*- Mode: Lisp; Package: HOST-IMPLEMENTATION; Syntax: Common-Lisp -*-
;;;
;;; Copyright (c) 1992, Chestnut Software Inc.
;;;

;Controlled by the following symbols on *features*:
; :internal-use :optimize-translator :translator-supports-clos 

(in-package "HOST-IMPLEMENTATION")

(himpl:note-rcs-revision
 "$Source: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/chestnut/src/trans/translator.lisp,v $"
 "$Revision: 1.5 $"
 "$Date: 2009-08-02 00:00:00 $")

(defmacro feature (name)
  `(find-feature ',name))

(defun find-feature (name)
  (dolist (feature *features* nil)
    (when (and (symbolp feature) (string= feature name))
      (return t))))

(defparameter *translator-source-directory*
  (subfile '("lisp")))

(defparameter *translator-binary-directory*
  (let ((pathname
	 (subfile 
	  (list (concatenate
		 'string
		 (if (feature optimize-translator) "O" "")
		 (if (feature translator-supports-thread) "T" "")
		 (if (feature translator-supports-clos) "CLOS" "")
		 "BIN")))))
    (prog1 pathname
      (ensure-directories-exist pathname))))

;;; This variable holds the list of database files that contain
;;; declarations for the symbols that exist in the runtime library.

(defparameter *runtime-symbols-databases*
  (mapcar #'(lambda (name)
	      (subfile '("lisp")
		       :name name
		       :type "lisp"))
	  `("symbols"
	    "list-symbols"
	    "array-symbols"
	    ,@(when (feature translator-supports-clos)
		'("clos-runtime-symbols")))))

;; Avoid doing this at top level, so as not to confuse Lucid's compiler
(let ((optimize (if (feature optimize-translator)
		    '(optimize (speed 3) (safety 1) (space 0) #+sbcl (debug 3)
		               (compilation-speed 0))
		    '(optimize (speed 0) (safety 3) (space 0) #+sbcl (debug 3)
		               (compilation-speed #-sbcl 3 #+sbcl 0)))))
  (setq *optimize* optimize)
  (proclaim optimize))

;;; Define the module description for the translator.

(defmodule-internal :translator
    `((:source-pathname ,*translator-source-directory*)
      (:binary-pathname ,*translator-binary-directory*)
      (:module packages
	       (:package "HOST-IMPLEMENTATION")
	       (:module define-symbols)
	       (:module hpacks)
	       (:module host-packages (:requires define-symbols hpacks)
			(:source-pathname ,(subfile '("host")))
			(:module #+lcl5.0       lucid-5-syms
				 #+(and lcl4.0 (not lcl5.0))
					        lucid-4-syms
				 #+(or allegro-v4.0 allegro-v4.1)
					        allegro-4-syms
				 #+MCL-2.0      mac-2-0-syms
				 #+(or MCL-5.2 MCL-6.0)
					        mcl-5-2-syms
				 #+(or (and LispWorks6 (not LispWorks6.0)) ; 6.1+
				       LispWorks7) ; 7.x
					        lispworks-6-1-syms
				 #+(or LispWorks5 (and LispWorks6 LispWorks6.0))
					        lispworks-5-syms
				 #+(or LispWorks3.1 LispWorks4)
						lispworks-3-1-syms
				 #+Genera-8-0   genera-8-0-syms
				 #+sbcl-old     sbcl-1-0-10-syms
				 #+(and sbcl (not sbcl-old))
						sbcl-1-0-52-syms
				 #+clozure      ccl-1-4-syms
				 #-(or lcl4.0 allegro-v4.0 allegro-v4.1 SBCL
				       MCL Genera-8-0 clozure LispWorks)
				 #.(error "You must supply the ~
                                           name of the host syms file")))
	       (:module host-compatibility (:requires host-packages)
			(:source-pathname ,(subfile '("host")))
			(:module #+lcl5.0       lucid-5-defs
				 #+(and lcl4.0 (not lcl5.0))
					        lucid-4-defs
				 #+(or allegro-v4.0 allegro-v4.1)
					        allegro-4-defs
				 #+MCL2.0       mac-2-0-defs
				 #+(or MCL-5.2 MCL-6.0)
					        mcl-5-2-defs
				 #+(or (and LispWorks6 (not LispWorks6.0)) ; 6.1+
				       LispWorks7) ; 7.x
					        lispworks-6-1-defs
				 #+(or LispWorks5 (and LispWorks6 LispWorks6.0))
					        lispworks-5-defs
				 #+(or LispWorks3.1 LispWorks4)
						lispworks-3-defs
				 #+Genera-8-0   genera-8-0-defs
				 #+sbcl-old     sbcl-1-0-10-defs
				 #+(and sbcl (not sbcl-old))
						sbcl-1-0-52-defs
				 #+clozure      ccl-1-4-defs
				 #-(or lcl4.0 allegro-v4.0 allegro-v4.1 SBCL
				       MCL Genera-8-0 clozure LispWorks)
				 #.(error "You must supply the ~
                                           name of the host defs file")))
	       (:module runtime-packages (:requires host-compatibility)
			(:module rpacks))
	       (:module ipacks (:requires runtime-packages)))
      (:module utilities (:requires packages)
	       (:package "TUTIL")
	       (:module util)
	       (:module resource)
	       (:module lambda (:requires util))
	       (:module env (:requires lambda))
	       (:module type (:requires env))
	       (:module initdecl (:requires type))
	       (:module tcldefs (:requires env))
	       (:module map-name (:requires util))
	       (:module reserved (:requires map-name))
	       (:module namespaces (:requires env)))
      (:module kernel (:requires utilities)
	       (:package "TIMPL")
	       (:module record)
	       (:module target (:requires record))
	       (:module foreign-types (:requires target))
	       (:module target-form-types (:requires foreign-types))
	       (:module codewalk (:requires target-form-types))
	       (:module walk (:requires codewalk))
	       (:module toplevel (:requires codewalk))
	       #+lucid ; old: #-sbcl
	       (:module call-information (:requires toplevel))
	       (:module bq)
	       (:module readtbl (:requires toplevel bq)))
      ,@(when (feature translator-supports-clos)
	  `((:module clos-utilities (:requires kernel)
		     ;;(:module remote-environments)
		     (:module clos-util)
		     (:module find-class)
		     (:module canonic-initargs))))
      (:module walkers (:requires kernel)
	       (:package "TIMPL")
	       (:module binding)
	       (:module block)
	       (:module call (:requires binding))
	       (:module catch)
	       (:module defsetf)
	       (:module defstruct (:requires defsetf))
	       (:module define (:requires call defstruct))
	       (:module defpackage (:requires define))
	       (:module emacros)
	       (:module if (:requires call))
	       (:module iter)
	       (:module loop)
	       (:module misc)
               ,@(when (feature translator-supports-thread)
                   `((:module thread)))
	       (:module modify-macros (:requires defsetf))
	       (:module pattern)
	       (:module progn)
	       (:module setf)
	       (:module setf-methods (:requires defsetf))
	       (:module tagbody)
	       (:module transform-lambda)
	       (:module values (:requires binding)))
      (:module backend (:requires walkers)
	       (:package "TIMPL")
	       (:module optimize)
	       (:module pregather)
	       (:module gather (:requires pregather))
	       (:module constant)
	       (:module emit (:requires constant optimize)))
      (:module database (:requires backend)
	       (:package "TIMPL")
	       (:module library)
	       (:module declare)
	       (:module dump)
	       (:module dumpmake (:requires dump))
	       (:module dumpmain (:requires dump dumpmake)))
      ,@(when (feature translator-supports-clos)
	  `((:module clos-kernel (:requires utilities kernel clos-utilities)
		     (:module initfunctions)
		     (:module early-metaclasses)
		     (:module global-index (:requires database))
		     (:module clos-records (:requires early-metaclasses)
			      (:module class-record)
			      (:module slot-definition
				       (:requires walkers ; binding
						  global-index
						  class-record)))
		     (:module std-class
			      (:requires clos-records early-metaclasses)))
	    (:module clos (:requires kernel clos-kernel)
		     (:module classes
			      (:module ensure-translator-class)
			      (:module defclass
				       (:requires ensure-translator-class))
			      (:module initialize-class-records
				       (:requires defclass))
			      (:module metaobjects
				       (:requires initialize-class-records
						  defclass)))
		     (:module method-arguments)
		     (:module define-method-combination
			      (:requires method-arguments))
		     (:module methods (:requires classes method-arguments)
			      (:module make-method-body)
			      (:module slot-accesses
				       (:requires make-method-body)
				       (:module slot-access)
				       (:module slot-access-std-class 
						(:requires slot-access))
				       (:module slot-layout))
			      (:module defmethod (:requires backend database)))
		     (:module generics (:requires classes methods)
			      (:module #-mcl generic-function-definition
				       #+mcl generic-definition)
			      (:module ensure-generic-function)
			      (:module defgeneric)
			      (:module local-generic-functions)))))
      (:module initialize
	       (:requires database
			  ,@(when (feature translator-supports-clos)
			      `(clos)))
	       (:package "TIMPL")
	       ,@(when (feature translator-supports-clos)
		   `((:module initialize-generic-functions)
		     (:module build-boot)))
	       (:module license)
	       (:module type-specific)
	       (:module initenv)
	       (:module symbols (:requires initenv))
	       (:module list-symbols (:requires initenv))
	       (:module array-symbols (:requires initenv))
	       (:module more-symbols (:requires symbols
						list-symbols array-symbols))
	       ,@(when (feature translator-supports-clos)
		   `((:module clos-runtime-symbols
			      (:requires initenv))))
	       (:module final
			(:requires more-symbols license
				   ,@(when (feature translator-supports-clos)
				       `(clos-runtime-symbols
					 initialize-generic-functions)))))))


(defparameter *translator-release* "3.3")

;; Created with the help of (himpl::print-*current-translator-release*-form),
;; with some editing by hand.
(defparameter *current-translator-release*
  '(("3.3 beta 1  12/19/2015" "12/19/2015")

    ("array-symbols" "1.2")
    ("binding" "1.93")
    ("block" "1.21")
    ("bq" "1.7")
    ("build-boot" "1.13")
    ("build" "1.67")
    ("call" "1.80")
    ("canonic-initargs" "1.12")
    ("catch" "1.31")
    ("class-record" "2.41")
    ("clos-build" "1.29")
    ("clos-runtime-symbols" "1.44")
    ("clos-util" "2.13")
    ("codewalk" "1.78")
    ("constant" "1.52")
    ("declare" "1.53")
    ("defclass" "2.24")
    ("defgeneric" "1.26")
    ("define-method-combination" "1.18")
    ("define-symbols" "1.5")
    ("define" "1.84")
    ("defmethod" "1.20")
    ("defpackage" "1.40")
    ("defsetf" "1.24")
    ("defstruct" "1.23")
    ("dump" "1.118")
    ("dumpmain" "1.21")
    ("dumpmake" "1.46")
    ("early-metaclasses" "2.15")
    ("emacros" "1.10")
    ("emit" "1.137")
    ("ensure-generic-function" "2.11")
    ("ensure-translator-class" "2.23")
    ("env" "1.86")
    ("final" "1.6")
    ("find-class" "2.13")
    ("foreign-types" "1.5")
    ("gather" "1.63")
    ("generic-function-definition" "2.6")
    ("global-index" "1.12")
    ("host-implementation-package" "1.8")
    ("host-implementation" "1.18")
    ("hpacks" "1.8")
    ("if" "1.37")
    ("initdecl" "1.16")
    ("initenv" "1.22")
    ("initfunctions" "2.10")
    ("initialize-class-records" "2.21")
    ("initialize-generic-functions" "1.27")
    ("ipacks" "1.121")
    ("iter" "1.31")
    ("lambda" "1.36")
    ("library" "1.50")
    ("license" "1.17")
    ("list-symbols" "1.3")
    ("load-clos-trans" "1.22")
    ("load-trans" "1.20")
    ("local-generic-functions" "1.6")
    ("loop" "1.2")
    ("make-clos-trans" "1.5")
    ("make-method-body" "2.43")
    ("make-trans" "1.3")
    ("map-name" "1.32")
    ("metaobjects" "2.29")
    ("method-arguments" "1.19")
    ("misc" "1.32")
    ("modify-macros" "1.12")
    ("module" "1.19")
    ("namespaces" "1.6")
    ("obuild" "1.18")
    ("oclos-build" "1.17")
    ("optimize" "1.36")
    ("pattern" "1.6")
    ("pregather" "1.12")
    ("progn" "1.23")
    ("readtbl" "1.6")
    ("record" "1.54")
    ("reserved" "1.35")
    ("resource" "1.3")
    ("rpacks" "1.19")
    ("setf-methods" "1.32")
    ("setf" "1.17")
    ("slot-access-std-class" "1.25")
    ("slot-access" "1.23")
    ("slot-definition" "2.23")
    ("slot-layout" "1.18")
    ("std-class" "2.18")
    ("symbols" "1.245")
    ("tagbody" "1.23")
    ("target-form-types" "1.4")
    ("target" "1.71")
    ("tcldefs" "1.18")
    ("thread" "1.1")
    ("toplevel" "1.84")
    ("transform-lambda" "1.13")
    ("translation-script" "1.4")
    ("translator" "1.43")
    ("type-specific" "1.3")
    ("type" "1.51")
    ("util" "1.42")
    ("values" "1.42")
    ("walk" "2.36")
    ("allegro-4-defs" "1.8")
    ("allegro-4-syms" "1.2")
    ("genera-8-0-defs" "1.6")
    ("genera-8-0-syms" "1.5")
    ("lispworks-3-1-syms" "1.4")
    ("lispworks-3-defs" "1.4")
    ("lispworks-5-syms" "1.1")
    ("lispworks-5-defs" "1.1")
    ("lispworks-6-1-syms" "1.0")
    ("lispworks-6-1-defs" "1.0")
    ("sbcl-1-0-10-defs" "1.0")
    ("sbcl-1-0-10-syms" "1.0")
    ("lucid-4-defs" "1.9")
    ("lucid-4-syms" "1.15")
    ("ccl-1-4-defs" "1.2")
    ("ccl-1-4-syms" "1.2")
    ("mac-2-0-defs" "1.5")
    ("mac-2-0-syms" "1.4")
    ("mcl-5-2-defs" "1.0")
    ("mcl-5-2-syms" "1.0")))

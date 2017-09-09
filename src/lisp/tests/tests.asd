
;;;; -*- Mode: Lisp; Syntax: ANSI-Common-Lisp; Base: 10 -*-

(unless (find-package :tests-system)
  (defpackage tests-system (:use :cl :asdf)))

;;; NOTE: to pass all tests in LispWorks 6, it's required to put
;;;
;;; (set-default-character-element-type 'simple-char)
;;;
;;; into your lw:*init-file-name* (.lispworks). --binghe

(in-package :tests-system)

(defsystem tests
  :name "Unit tests for Gensym G2"
  :version "1.0"
  :serial t
  :components ((:file "defpackage")
               (:file "mocks")
               (:file "mock-from-old-lisp-unit"
                :description "mock was removed from newer lisp-unit, but some tests use it")
               (:file "utilities"
		:description "Utility functions for test suite")
               (:file "g2-test-setups"
		:description "Test setup macros for misc cases of testing")
               ;;(:file "test-bootstrap") ; meaningless tests
               (:file "test-chaining")
               (:file "test-clock")
               (:file "test-eval")
               ;;(:file "test-dir-list")
               (:file "test-frames2")
               (:file "test-frames2a")
               (:file "test-frames4")

               #+(and connections-v2 (or sbcl lispworks))
	       (:file "test-connect1")
               #+(and connections-v2 (or sbcl lispworks))
	       (:file "test-connect2")
               #+(and connections-v2 (or sbcl lispworks))
               (:file "test-connect5")
               (:file "test-definitions")

               (:file "test-g2-meters")
               (:file "test-glbasics")
               (:file "test-grammar7")
               (:file "test-graph-util")
               (:file "test-int1")
               ;;(:file "test-interop")

               (:file "test-moves")

	       #+(or sbcl lispworks)
	       (:file "test-kb-merge")

               (:file "test-kb-load2")
               ;;(:file "test-load")
               (:file "test-modf-quick")
               (:file "test-primitives")
               ;;(:file "test-schedule") ; real test is commented out
               (:file "test-stack-eval2")
               (:file "test-streams")
               (:file "test-unicode")
               (:file "test-char-code-decrypt")
               (:file "test-hash-wide-string")
               (:file "test-reclaim-tree")
               (:file "test-extract-number")
               ;;(:file "test-edit-grid")
               (:file "test-platforms")
               (:file "test-os-foreign")
               (:file "test-os-settings")
               (:file "test-utilities0")
               (:file "test-utilities1")
               (:file "test-utilities2")
               (:file "test-utilities4")
               (:file "test-alphabet")

               #+(and connections-v2 (or sbcl lispworks))
	       (:file "test-connect4")
               #+connections-v2
	       (:file "test-roles")

               (:file "test-kb-save4")

               ;;(:file "test-nkb-shared")   ; no nkb package
               ;;(:file "test-nkb-shared-2") ; no nkb package
               (:file "test-variables")
               (:file "test-queue") ; ported from SBCL's SB-CONCURRENT package
               (:file "test-queue-reverse")
               (:file "test-queue-stack")
               (:file "test-queue-all")

               (:file "test-sequences2")
               (:file "test-types")
               (:file "test-stack-acts")
               (:file "test-histories")

               #+SymScale (:file "test-lockfree-hashtable")
               #+SymScale (:file "test-lockfree-skiplist-hashtable-mt")
               #+SymScale (:file "test-lockfree-skiplist-priority-queue-mt")
               #+SymScale (:file "test-lockfree-skiplist-tree-mt")

               #+sbcl
	       (:file "test-loop")
               ) ; end of components
  :depends-on (:lisp-unit :mock-macro :cl-junit-xml.lisp-unit))

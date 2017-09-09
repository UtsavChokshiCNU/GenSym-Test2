;;; -*- Mode: Lisp; Package: HOST; Syntax: Common-Lisp -*-
;;;
;;; ipacks.lisp -- set up implementation packages for the translator
;;;
;;; author :  Sandra Loosemore
;;; date   :  05 Oct 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;
;;;

(in-package "HOST")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/ipacks.lisp,v $"
 "$Revision: 1.11 $"
 "$Date: 2007/07/12 18:29:34 $")

(eval-when (compile load eval)

;;; The TRANS package defines the external interface used to invoke
;;; the translator.  It basically includes anything that would normally
;;; be processed with the host Lisp's evaluator or compiler to control the
;;; behavior of translator, but not things that would normally appear in
;;; code processed with the translator itself.
;;; *** Someday there will be more things added here, such as the entry
;;; *** points for manipulating global translation environments, adding
;;; *** names to the collision database, etc.

(unless (find-package "TRANS")

;;; binghe, 2009/3/26, late LispWorks ships with KnowledgeWorks (KW), which
;;; have a package "TRANS" too, and it's been protected by LW. We should
;;; unlock "TRANS" and make sure Chestnut never been used at the same time
;;; with KW.
#+(or LispWorks5 LispWorks6)
(eval-when (compile load eval)
  (delete "TRANS" hcl:*packages-for-warn-on-redefinition* :test #'string=))

(defpackage "TRANS"
    (:nicknames "TRANSLATOR")
    (:use #+ALLEGRO-V4.0 "DUMMY")     ; uses nothing
    (:import-from "HOST"
     "*COMPILE-PRINT*"
     "*COMPILE-VERBOSE*")
    (:import-from "HOST-IMPLEMENTATION"
     "*INHIBIT-FINAL-TRANSLATOR-INITIALIZATION*")
    (:export
     "PREPARE-FILE"
      "WITH-LOCAL-ALLOCATION" ;added by SoftServe
     "TRANSLATE-FILE"
     "SHOW-TRANSLATION"
     "INITIALIZE-TRANSLATOR"
     "WITH-TRANSLATOR-ENVIRONMENT"
     "TRANSLATE-FILES"
     "WRITE-HEADER-FILES"
     "WRITE-MAKEFILE-FILE"
     "WRITE-MAIN-FILE"
     "DEFINE-STATIC-PACKAGE"
     "ADD-C-RESERVED-NAME"
     "TRANSLATOR-SYMBOL-NAME"
     "TRANSLATOR-MESSAGE"
     "*TRANSLATE-FILE-INPUT-TYPE*"
     "*TRANSLATE-FILE-OUTPUT-TYPE*"
     "*TRANSLATE-FILE-HEADER-TYPE*"
     "*TRANSLATE-FILE-OBJECT-TYPE*"

     "*MAKEFILE-PATHNAME-DEFAULT-NAME*"
     "*MAKEFILE-PATHNAME-DEFAULT-TYPE*"
     "*CC-DEFAULT*"
     "*CC-FLAGS-DEFAULT*"
     "*EXECUTABLE-FILENAME-DEFAULT*"
     "*LINK-FILES*"
     "*ALL-CC-FLAGS*"
     "*MAIN-PATHNAME-DEFAULT-NAME*"
     "*MAIN-PATHNAME-DEFAULT-TYPE*"
     "*MAXIMUM-FILES-PER-RULE*"
     "*EXPLICITLY-LIST-RTL-INCLUDE-FILES-P*"
     "*CC-INCLUDES-FROM-SOURCE-DIRECTORY-P*"
     "*INTEGER-CONSTANTS-ARE-LONG-P*"
     
     "*TRANSLATOR-READTABLE*"
     "*VERBOSE-WARNINGS*"
     "*REPORT-UNDEFINED-FUNCTIONS-UNIT*"
     "*RTL-INCLUDES-GC-P*"
     
     "*COMPILE-PRINT*"
     "*COMPILE-VERBOSE*"

     "*ANSI-SEMANTICS*"
     "*PROTECT-LOCAL-VARIABLES*"
     "*TOPLEVEL-LOCATION*"
     "*FUNCTION-SYMBOLS*"
     "*SPECIAL-SYMBOLS*"
     "*NIL-IS-ZERO*"
     "*INITIAL-SYMBOLS*"
     "*USE-FUNCTION-MACROS*"
     "*LOCAL-DECLARATIONS*"
     "*INCLUDE-MACRO-EXPANDERS*"
     "*INCLUDE-SETF-EXPANDERS*"
     "*INCLUDE-TYPE-EXPANDERS*"
     "*SOURCE-OPTIMIZATIONS*"
     "*TARGET-PATHNAME-SYNTAX*"
     "*COMPILE-INTO-SOURCE-DIRECTORY-P*"
     "*FUNCALLABLE-FOREIGN-FUNCTIONS-P*"
     "*INITIAL-COMPILE-TIME-TOO*"
     "*INLINE-MAP-FUNCTIONS-P*"
     "*DEFINE-MACROS-IN-HOST-ENVIRONMENT-P*"
     "*MAXIMUM-C-STRING-CONSTANT-LENGTH*"

     "*PRESERVE-COMMENTS*"
     "*HEADER-LINES*"
     "*INCLUDE-DATES-IN-HEADERS*"
     "*COPYRIGHT-NOTICE*"
     "*APPLICATION-NAME*"
     "*CONSTANT-PRINT-LENGTH*"
     "*CONSTANT-PRINT-LEVEL*"
     "*CONSTANT-PRINT-CASE*"
     "*TRUNCATE-COMMENTS*"
     "*AVOID-COMMA-OPERATOR*"
     "*ELIDE-NOT-NULL*"
     "*SYMBOL-INIT-STATEMENTS-PER-FILE*"

     #+MCL "*MAC-TO-UNIX-ILLEGAL-CHARACTERS*"
     "*IF-EXISTS-ACTION*"
     "*IF-DOES-NOT-EXIST-ACTION*"
     )
    (:export
     "*WARN-ON-DEFMETHOD-WITHOUT-DEFGENERIC*"

     ;; Generic functions for slot optimization.
     "ESTABLISH-SLOT-OPTIMIZATION-CONTEXT"
     "OPTIMIZE-SET-SLOT-VALUE"
     "OPTIMIZE-SLOT-BOUNDP"
     "OPTIMIZE-SLOT-EXISTS-P"
     "OPTIMIZE-SLOT-MAKUNBOUND"
     "OPTIMIZE-SLOT-VALUE"

     "INVALIDATE-CLASS-CACHE"

     ;; Macros for providing compile-time information about classes.
     "DEFINE-TRANSLATOR-CLASS"
     "DECLARE-CLASS"

     ;; Generic functions for defclass extension.
     "CANONICALIZE-CLASS-OPTION"
     "CANONICALIZE-SUPERCLASSES"
     "CANONICALIZE-SLOT-SPECIFICATIONS"
     "CANONICALIZE-SLOT-SPECIFICATION"
     "CANONICALIZE-SLOT-OPTION"

     ;; Functions for manipulating canonic initarg lists.
     "CGETF" "CREMF"
     )
    ))


;;; The TUTIL package defines some utilities that are used by all parts
;;; of the translator implementation.

(unless (find-package "TUTIL")
(defpackage "TUTIL"
    (:nicknames "TRANSLATOR-UTILITIES")
    (:use "HOST" "HOSTX" "TRANS")
    (:import-from "HOST"
		  "*TRANSLATOR-PACKAGES*"
		  "NOTICE-TRANSLATOR-PACKAGE")
    (:shadow "WARN" "ERROR" "CERROR" "SOME" "EVERY")
    (:export
         ;; Type name, predicate, etc.
     "TRANSLATOR-ENVIRONMENT"
     "TRANSLATOR-ENVIRONMENT-P"
     "*DEFAULT-GLOBAL-ENVIRONMENT*"
     "*INITIAL-GLOBAL-ENVIRONMENT*"
     "COPY-TRANSLATOR-ENVIRONMENT"
     "FREE-TRANSLATOR-ENVIRONMENT"
     "GLOBAL-TRANSLATOR-ENVIRONMENT-P"
     "COERCE-TO-ENVIRONMENT"
         ;; Primitive accessors for global definitions
     "TRANSLATOR-ENVIRONMENT-NAME"
     "TRANSLATOR-ENVIRONMENT-GET"
     "TRANSLATOR-ENVIRONMENT-REMPROP"
     "TRANSLATOR-MAP-ENVIRONMENT-PROPERTIES"
     "TRANSLATOR-MAP-ENVIRONMENT-NAMES"
     "ENVIRONMENT-ENTRY"
     "ENVIRONMENT-ENTRY-P"
     "NAME-AND-ENVIRONMENT-ENTRY"
     "ENVIRONMENT-ENTRY-NAME"
     "FUNCTION-OR-MULTIPLE-EXECUTION-CONTOUR-LIST-P"
     ;; High-level accessors for global definitions (incomplete)
     "DEFINE-TRANSLATOR-PROPERTY"
     "DEFINED-AS-VARIABLE"
     "DEFINED-AS-FUNCTION"
     "DEFINED-AS-MACRO"
     "DEFINED-AS-SPECIAL-FORM"
     "DEFINED-AS-TOPLEVEL-FORM"
     "DEFINED-AS-DECLARATION"
     "DEFINED-AS-CLASS"
     "DEFINED-AS-COMPILER-MACRO"
     "DEFINED-AS-DEFTYPE"
     "DEFINED-AS-GENERALIZED-VARIABLE"
     "SIMPLE-SETF-UPDATE-FUNCTION"
     "DEFINED-AS-STRUCTURE"
     "DEFINED-AS-SYMBOL"
     "DEFINED-AS-QUOTED-SYMBOL"
     "FORWARD-DEFINED-AS-SYMBOL"
     "VARIABLE-PROCLAMATIONS"

     "DESCRIPTOR"
     "DESCRIPTOR-FILE-COOKIE"
         ;; Function descriptors
     "FUNCTION-DESCRIPTOR"
     "MAKE-FUNCTION-DESCRIPTOR"
     "MAKE-FUNCTION-DESCRIPTOR-INTERNAL"
     "FUNCTION-DESCRIPTOR-LAMBDA-LIST"
     "FUNCTION-DESCRIPTOR-LAMBDA-LIST-INFO"
     "FUNCTION-DESCRIPTOR-DEFINED-IN-RTL-P"
     "FUNCTION-DESCRIPTOR-VARIADIC"
     "FUNCTION-DESCRIPTOR-NONCONSING"
     "FUNCTION-DESCRIPTOR-NONRELOCATING"
     "FUNCTION-DESCRIPTOR-STATE-USING"
     "FUNCTION-DESCRIPTOR-STATE-CHANGING"
     "FUNCTION-DESCRIPTOR-DECLARE"
     "FUNCTION-DESCRIPTOR-ARGUMENT-TYPES"
     "FUNCTION-DESCRIPTOR-RETURN-TYPE"
     "FUNCTION-DESCRIPTOR-TRANSFORMS"
     "FUNCTION-DESCRIPTOR-DOCUMENTATION"
     "FUNCTION-DESCRIPTOR-GENERIC-FUNCTION-P"
     "FUNCTION-DESCRIPTOR-LINKED-LOCALLY-P"
     "FUNCTION-DESCRIPTOR-FOREIGN-PROTOCOL"
     "FUNCTION-DESCRIPTOR-RTL-REQUIRES-LINKING"
     "FUNCTION-DESCRIPTOR-REQUIRES-RETURN-TYPE-DECLARATION"
     "FUNCTION-DESCRIPTOR-EXTERN-REQUIRED"
     "FUNCTION-DESCRIPTOR-FUNCALLABLE-P"
     "FUNCTION-DESCRIPTOR-COERCE-RATIONALS-TO-FLOATS-P"
     "FUNCTION-DESCRIPTOR-COERCE-FLOATS-TO-RATIONALS-P"
     "FUNCTION-DESCRIPTOR-SETS-VALUES-COUNT-P"
     "FUNCTION-DESCRIPTOR-ARRAY-SETF-FUNCTION-P"
     "FUNCTION-DESCRIPTOR-ALIAS-P"
     "FUNCTION-DESCRIPTOR-EXPLICIT-OPTIONALS-P"
     "FUNCTION-DESCRIPTOR-DLLEXPORT-P"
     "FUNCTION-DESCRIPTOR-DLLIMPORT-P"
     "DLLEXPORT"
     "DLLIMPORT"
     "FOREIGN-FUNCTION-DESCRIPTOR-FOREIGN-ARGUMENTS"
     "FOREIGN-FUNCTION-DESCRIPTOR-FOREIGN-RETURN-TYPE"
     "FOREIGN-FUNCTION-DESCRIPTOR-USES-LOCALS"
     "FOREIGN-FUNCTION-DESCRIPTOR-USES-CONSTANTS"
     "FOREIGN-FUNCTION-DESCRIPTOR-LVALUE"
     "FOREIGN-FUNCTION-DESCRIPTOR-OPERATOR"
     "BUILD-ARGUMENT-DESCRIPTOR"
     "ARGUMENT-DESCRIPTORS-EQUAL-P"
         ;; Variable descriptors
     "VARIABLE-DESCRIPTOR"
     "MAKE-VARIABLE-DESCRIPTOR"
     "VARIABLE-DESCRIPTOR-CONSTANT-P"
     "VARIABLE-DESCRIPTOR-GLOBAL-P"
     "VARIABLE-DESCRIPTOR-DOCUMENTATION"
     "VARIABLE-DESCRIPTOR-VALUE-P"
     "VARIABLE-DESCRIPTOR-VALUE"
     "VARIABLE-DESCRIPTOR-DUMP-DEFINITION-P"
     "VARIABLE-DESCRIPTOR-LINKED-LOCALLY-P"

     #+translator-supports-thread
     "VARIABLE-DESCRIPTOR-SPECIAL-P" ; binghe, 2009/5/26

     "VARIABLE-DESCRIPTOR-REDEFINITION-RECORD"
     "ASSIGN-C-NAMES-FOR-GLOBAL-VARIABLE"
     "VARIABLE-REDEFINITION-RECORD"
     "UPDATE-VARIABLE-DESCRIPTOR"
     "PROCESS-VARIABLE-LINKS"
         ;; Redefinition records
     "REDEFINITION-RECORD-FILE"
     "REDEFINITION-RECORD-COOKIE"
     "REDEFINITION-RECORD-DEFINITION-DUMPED"
     "COMPUTE-REDEFINITION-RECORD"
     "UPDATE-REDEFINITION-RECORD"
     "REDEFINITION-RECORD-NOTE-DEFINITION-DUMPED"
     "REDEFINITION-RECORD-DEFINITION-NEEDS-DUMPING"
         ;; Syntactic-environment-access equivalents
     "TRANSLATOR-VARIABLE-INFORMATION"
     "TRANSLATOR-FUNCTION-INFORMATION"
     "TRANSLATOR-DECLARATION-INFORMATION"
     "TRANSLATOR-SET-DECLARATION-INFORMATION"
     "TRANSLATOR-AUGMENT-ENVIRONMENT"
     "TRANSLATOR-PARSE-DECLARATIONS"
     "DEFINE-TRANSLATOR-DECLARATION"
         ;; Equivalents for high-level functions (incomplete)
     "TRANSLATOR-PROCLAIM"
     "TRANSLATOR-MACRO-FUNCTION"
     "TRANSLATOR-MACROEXPAND"
     "TRANSLATOR-MACROEXPAND-1"
     "TRANSLATOR-SYMBOL-MACROEXPAND-1"
     "TRANSLATOR-CONSTANTP"
     "TRANSLATOR-CONSTANT-VALUE"
     "TRANSLATOR-COMPILER-MACRO-FUNCTION"
     "TRANSLATOR-COMPILER-MACROEXPAND-1"
     "CALL-MACRO-FUNCTION"
     "TRANSLATOR-FIND-CLASS"
     "TRANSLATOR-ENSURE-GENERIC-FUNCTION"
         ;; Declaration accessors
     "VARIABLE-INFORMATION-VALUE"
     "FUNCTION-INFORMATION-VALUE"
     "VARIABLE-TYPE"
     "FUNCTION-NOTINLINE-P"
     "SAFETY-LEVEL"
     "SAFE-CODE-P"
         ;; Type system support (from type.lisp)
     "DEFINE-TRANSLATOR-TYPE"
     "DEFINE-TYPE-SYMBOL"
     "TRANSLATOR-TYPE-SPECIFIER-P"
     "TRANSLATOR-TYPEP"
     "OPTIMIZE-TYPEP"
     "TRANSLATOR-SUBTYPEP"
     "TRANSLATOR-UPGRADED-ARRAY-ELEMENT-TYPE"
     "TRANSLATOR-UPGRADED-COMPLEX-PART-TYPE"
     "TRANSLATOR-TYPE-OF"
     "AND-VALUE-TYPES"
     "AND-TYPES"
     "OR-VALUE-TYPES"
     "OR-TYPES"
     "SINGLE-VALUE-TYPE"
     "MAKE-UNSPECIFIC-NUMBER-OF-VALUES-TYPE"
         ;; From util.lisp
     "DEFINE-HASHED-STRUCTURE"
     "ONCE-ONLY"
     "ONCE-ONLY*"
     "DEFINE-FLAGS"
     "DEFINE-FORWARD-VARIABLE-REFERENCE"
     "PARSE-BODY"
     "PRINCIPAL-NAME-OF-FUNCTION-NAME"
     "DEFINE-PRINCIPAL-FUNCTION-NAME"
     "INVALID-FUNCTION-NAME-ERROR"
     "BODY-BLOCK-NAME"
     "LAMBDA-EXPRESSION-P"
     "SETF-FUNCTION-NAME-P"
     "VALID-FUNCTION-NAME-P"
     "REQUIRED-KEYWORD"
     "*RECORD-DOCUMENTATION-FOR-RUNTIME*"
     "RECORD-DOCUMENTATION-P"
     "DEFINE-INTERNAL-FUNCTION"
     "DEFINE-TRANSLATOR-PARAMETER"
     "*TRANSLATOR-PARAMETERS*"
     "WITH-TRANSLATOR-MESSAGE"
     "WARN" "ERROR"
     "SFORMAT"
      "RESET-READ-ONCE-SETQS"
      "MAP-OVER-ENCLOSING-FUNCTIONS"
         ;; From lambda.lisp
     "PARSE-LAMBDA-LIST"
     "LAMBDA-KEYWORD-P"
     "DESTRUCTURE"
     "DESTRUCTURE-AUX"
     "TRANSLATOR-PARSE-MACRO"
     "TRANSLATOR-PARSE-MACRO-FOR-EXPANDER"
     "TRANSLATOR-PARSE-COMPILER-MACRO"
     "TRANSLATOR-PARSE-DEFTYPE"
     "TRANSLATOR-ENCLOSE"
     "EVAL-IN-ENV"
     "*PREPARE-STREAM*"
     "WRITE-PREPARE-FORM"
     "UNIONQ"
     "UNIONF"
     "UNIONQF"
     "UNION-APPEND"
     "UNION-APPENDF"
     "UNIONQ-APPEND"
     "UNIONQ-APPENDF"
     "UNIONQ-APPEND1"
     "UNIONQ-APPEND1F"
     "NUNIONQ"
     "APPENDF"
     "APPEND1F"
     "MAXF"
     "TRANSLATOR-LAMBDA-LIST-KEYWORDS"
         ;; From defsetf.lisp
     "DEFINE-TRANSLATOR-SETF-METHOD"
     "TRANSLATOR-DEFSETF"
     "UNKNOWN-APPLY-OF-PLACE-ERROR"
     "MAKE-SETF-METHOD-TEMP-VAR"
     "MAKE-SETF-METHOD-TEMP-VARS"
         ;; From modify-macros.lisp
     "DEFINE-TRANSLATOR-MODIFY-MACRO"
         ;; From setf.lisp
     "TRANSLATOR-GET-SETF-METHOD"
     "TRANSLATOR-GET-SETF-METHOD-MULTIPLE-VALUE"
         ;; From transform-lambda.lisp
     "TRANSFORM-LAMBDA-TO-LET"
         ;; From codewalk.lisp
     "*CONTEXT*"
     "*COMPILE-TIME-ONLY*"
     "DEFTRANSLATE"
     "DEFINE-TOPLEVEL-FORM"
     "DEFINE-TRANSLATOR-MACRO"
     "DEFINE-TRANSLATOR-COMPILER-MACRO"
     "MERGE-INITCODE"
     "APPLY-MACROS"
     "REALLY-ATOM"
     "VARIABLE-OR-CONSTANT-P"
         ;; From toplevel.lisp
     "PRINT-PROGRESS-MESSAGE"
     "*CURRENT-TRANSLATED-FILE*"
     "TRANSLATED-FILE"
     "TRANSLATED-FILE-PATHNAME"
     "TRANSLATED-FILE-COOKIE"
     ;; These should be be in either TCL or TX someday.
     "NONRELOCATABLE"
     "GLOBAL-FUNCTION"
     "FUNCTION-NAME"
         ;; From map-name.lisp
     "WITH-C-NAME-TABLE"
     "WITH-GLOBAL-C-NAME-TABLE"
     "COPY-C-NAME-TABLE"
     "RECORD-GLOBAL-C-NAME"
     "C-NAME-CONFLICT-P"
     "STRING->C-NAME"
     "STRING->LEGAL-C-NAME"
     "STRING-CANONICALIZE-CASE"
     "STRING-TRIM-STARS"
         ;; From namespaces.lisp
     "DEFINE-C-NAMESPACE"
     "SYMBOL-FOR-FUNCTION-NAME"
     "C-NAME-OF-FUNCTION-OBJECT"
     "NAME-OF-FUNCTION-OBJECT"
     "C-NAME-OF-FUNCTION-ENTRY"
     "NAME-OF-FUNCTION-ENTRY"
     "C-NAME-OF-GLOBAL-VARIABLE"
     "NAME-OF-GLOBAL-VARIABLE"
     "C-NAME-OF-QUOTED-SYMBOL"
     "NAME-OF-QUOTED-SYMBOL"
     "C-NAME-OF-PACKAGE"
     "NAME-OF-PACKAGE"
     "TARGET-FORM-TYPE"
     "MAKE-TARGET-FORM"
         ;; From dump.lisp
     "*INTERNAL-FUNCTION-PREFIX*"
     "WITH-SYSTEM-HEADER-LINES"
         ;; From env.lisp
     "FUNCTION-OR-MULTIPLE-EXECUTION-ENV-P"
         ;; From defpackage.lisp
     "MARK-QUOTED-SYMBOL"
     "*TRANSLATOR-PACKAGES*"
     "NOTICE-TRANSLATOR-PACKAGE"
     "*TRANS-PACKAGE*"
     "*TUTIL-PACKAGE*"
     "*TIMPL-PACKAGE*"
     "*WALK-PACKAGE*"
     #+translator-supports-clos
     "*TCLOSI-PACKAGE*"

     "*TCL-PACKAGE*"
     "*TX-PACKAGE*"
     "*TCLOS-PACKAGE*"
     "*TRUN-PACKAGE*"
     "*TCLOS-RUN-PACKAGE*"
     "*TCLOSX-PACKAGE*"
     "*TCL-USER-PACKAGE*"

     #+translator-supports-clos
     "ENSURE-TRANSLATOR-CLASS"    ; used by defstruct expansion
     )
    ))


;;; Most of the implementation of the translator is done in the TIMPL
;;; package.  It uses TRANS and TUTIL but exports nothing of its own.

(unless (find-package "TIMPL")
(defpackage "TIMPL"
  (:nicknames "TRANSLATOR-IMPLEMENTATION")
  (:shadowing-import-from "TUTIL" "WARN" "ERROR" "CERROR" "SOME" "EVERY")
  (:use "HOST" "HOSTX" "TRANS" "TUTIL")))


; Was in clos-packages.lisp
(unless (find-package "WALK")
(defpackage "WALK"
  (:shadowing-import-from "TUTIL" "WARN" "ERROR" "CERROR" "SOME" "EVERY")
  (:use "HOST" "HOSTX" "TUTIL")
  (:nicknames "TRANSLATOR-CODE-WALKER")
  (:export "WALK-ARGUMENTS"
	   "WALK-FORM"
	   "WALK-FUNCTION"
	   "WALK-PROGN"
	   "WALK-FORM-1"
	   "WALK-ARGUMENTS-1"
	   "WALK-FUNCTION-1"
	   "WALK-PROGN-1"
	   )
  ))

#+translator-supports-clos
(unless (find-package "TCLOSI")
(defpackage "TCLOSI"
  (:nicknames "TRANSLATOR-CLOS-INTERNALS")
  (:shadowing-import-from "TUTIL" "WARN" "ERROR" "CERROR" "SOME" "EVERY")
  (:use "HOST" "HOSTX" "TUTIL" "TRANS")
  ;; Called by the dumper.
  (:export "COLLECT-SLOT-INDEX-CONSTANTS"
	   "COMPUTE-GLOBAL-SLOT-INDEXES"
	   "GLOBAL-SLOT-INDEX"
	   "INTERNAL-SLOT-ACCESSORS"
	   "DUMP-CLOS-BOOTSTRAP-INFO"
	   )
  ;; Called by the environment intialization.
  (:export "CREATE-GLOBAL-SLOT-INDEX"
	   "INITIALIZE-GENERIC-FUNCTIONS"
	   )
  ))

)

(in-package :tutil)

(defvar *tcl-package* (find-package :tcl))
(defvar *tx-package* (find-package :tx))
(defvar *tclos-package* (find-package :tclos))
(defvar *trun-package* (find-package :trun))
(defvar *tclos-run-package* (find-package :tclos-run))
(defvar *tclosx-package* (find-package :tclosx))
(defvar *tcl-user-package* (find-package :tcl-user))

(defvar *trans-package* (find-package :trans))
(defvar *tutil-package* (find-package :tutil))
(defvar *timpl-package* (find-package :timpl))
(defvar *walk-package* (find-package :walk))
#+translator-supports-clos
(defvar *tclosi-package* (find-package :tclosi))
(defvar himpl::*tcl-package* (find-package :tcl))

;; not sure where these should go; they're from patch 2 -alatto, 3/1/06
(eval-when (compile load eval)
(let ((sym (intern "*LISP-SYMBOL-TO-FOREIGN-STRING-METHOD*" 
		   #+lucid "LCL" #-lucid "HOSTX")))
  #+lucid (import sym "HOSTX")
  (export sym "HOSTX")
  (import sym "TRANS")
  (export sym "TRANS"))
(let ((sym (intern "*REMOVE-LEADING-UNDERSCORE-FROM-FOREIGN-STRING-P*"
		   "TRANS")))
  (export sym "TRANS"))
)

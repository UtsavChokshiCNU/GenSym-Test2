;;; -*- Mode: Lisp -*-
;;;
;;; sbcl-1-0-10-syms.lisp -- HOST package database for SBCL 1.0.10
;;;
;;; This is a *data* file, not a code file.  Don't try to LOAD it.
;;;

#-SBCL
#.(error "Attempting to use incorrect host database.
This file is for SBCL version 1.0.10.")

(in-package "HOST-IMPLEMENTATION")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/host/sbcl-1-0-10-syms.lisp,v $"
 "$Revision: 1.3 $"
 "$Date: 2009/04/11 00:00:00 $")

#+sbcl
(eval-when (:compile-toplevel :load-toplevel :execute)
  (require :sb-cltl2))

(himpl:define-symbols :lisp nil

("&ALLOW-OTHER-KEYS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("&AUX"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("&BODY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("&ENVIRONMENT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("&KEY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("&OPTIONAL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("&REST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("&WHOLE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("**"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("***"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*BREAK-ON-SIGNALS*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*COMPILE-FILE-PATHNAME*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*COMPILE-FILE-TRUENAME*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*COMPILE-PRINT*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*COMPILE-VERBOSE*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*DEBUG-IO*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*DEBUGGER-HOOK*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*DEFAULT-PATHNAME-DEFAULTS*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*ERROR-OUTPUT*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*FEATURES*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*GENSYM-COUNTER*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*LOAD-PATHNAME*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*LOAD-PRINT*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*LOAD-TRUENAME*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*LOAD-VERBOSE*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*MACROEXPAND-HOOK*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*MODULES*"
    (:symbol
        :package "HOST"
	:import-from "COMMON-LISP"
	)
    )

("*PACKAGE*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*PRINT-ARRAY*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*PRINT-BASE*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*PRINT-CASE*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*PRINT-CIRCLE*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*PRINT-ESCAPE*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*PRINT-GENSYM*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*PRINT-LENGTH*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*PRINT-LEVEL*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*PRINT-LINES*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*PRINT-MISER-WIDTH*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*PRINT-PPRINT-DISPATCH*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*PRINT-PRETTY*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*PRINT-RADIX*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*PRINT-READABLY*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*PRINT-RIGHT-MARGIN*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*QUERY-IO*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*RANDOM-STATE*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*READ-BASE*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*READ-DEFAULT-FLOAT-FORMAT*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*READ-EVAL*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*READ-SUPPRESS*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*READTABLE*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*STANDARD-INPUT*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*STANDARD-OUTPUT*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*TERMINAL-IO*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("*TRACE-OUTPUT*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("+"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("++"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("+++"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("-"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("/"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("//"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("///"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("/="
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("1+"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("1-"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("<"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("<="
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("="
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

(">"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

(">="
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ABORT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ABS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ACONS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ACOS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ACOSH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ADD-METHOD"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("ADJOIN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ADJUST-ARRAY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ADJUSTABLE-ARRAY-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ALLOCATE-INSTANCE"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("ALPHA-CHAR-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ALPHANUMERICP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("AND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("APPEND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("APPLY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("APROPOS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("APROPOS-LIST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("AREF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ARITHMETIC-ERROR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ARITHMETIC-ERROR-OPERANDS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ARITHMETIC-ERROR-OPERATION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ARRAY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ARRAY-DIMENSION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ARRAY-DIMENSION-LIMIT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ARRAY-DIMENSIONS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ARRAY-DISPLACEMENT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ARRAY-ELEMENT-TYPE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ARRAY-HAS-FILL-POINTER-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ARRAY-IN-BOUNDS-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ARRAY-RANK"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ARRAY-RANK-LIMIT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ARRAY-ROW-MAJOR-INDEX"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ARRAY-TOTAL-SIZE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ARRAY-TOTAL-SIZE-LIMIT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ARRAYP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ASH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ASIN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ASINH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ASSERT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ASSOC"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ASSOC-IF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ASSOC-IF-NOT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ATAN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ATANH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ATOM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

;; binghe: SB-CLTL2 has this symbol, but not actually defined
("AUGMENT-ENVIRONMENT"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL ; "SB-CLTL2"
        )
    )

("BASE-CHAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BASE-STRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BIGNUM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BIT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BIT-AND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BIT-ANDC1"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BIT-ANDC2"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BIT-EQV"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BIT-IOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BIT-NAND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BIT-NOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BIT-NOT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BIT-ORC1"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BIT-ORC2"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BIT-VECTOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BIT-VECTOR-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BIT-XOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BLOCK"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOOLE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOOLE-1"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOOLE-2"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOOLE-AND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOOLE-ANDC1"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOOLE-ANDC2"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOOLE-C1"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOOLE-C2"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOOLE-CLR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOOLE-EQV"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOOLE-IOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOOLE-NAND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOOLE-NOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOOLE-ORC1"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOOLE-ORC2"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOOLE-SET"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOOLE-XOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOTH-CASE-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BOUNDP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BREAK"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BROADCAST-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BROADCAST-STREAM-STREAMS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BUILT-IN-CLASS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("BUTLAST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BYTE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BYTE-POSITION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("BYTE-SIZE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CAAAAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CAAADR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CAAAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CAADAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CAADDR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CAADR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CAAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CADAAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CADADR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CADAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CADDAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CADDDR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CADDR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CADR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CALL-ARGUMENTS-LIMIT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CALL-METHOD"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("CALL-NEXT-METHOD"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("CAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CASE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CATCH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CCASE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CDAAAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CDAADR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CDAAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CDADAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CDADDR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CDADR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CDAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CDDAAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CDDADR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CDDAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CDDDAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CDDDDR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CDDDR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CDDR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CDR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CEILING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CELL-ERROR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CELL-ERROR-NAME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CERROR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHANGE-CLASS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("CHAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR-CODE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR-CODE-LIMIT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR-DOWNCASE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR-EQUAL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR-GREATERP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR-INT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR-LESSP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR-NAME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR-NOT-EQUAL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR-NOT-GREATERP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR-NOT-LESSP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR-UPCASE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR/="
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR<"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR<="
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR="
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR>"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHAR>="
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHARACTER"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHARACTERP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CHECK-TYPE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CIS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CLASS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

#|
("CLASS-DEFAULT-INITARGS"
    (:SYMBOL
        :PACKAGE HOST-CLOS
        :IMPORT-FROM NIL
        )
    )
|#

#|
("CLASS-DIRECT-DEFAULT-INITARGS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

#|
("CLASS-DIRECT-SUBCLASSES"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "CCL"
        )
    )

("CLASS-DIRECT-SUPERCLASSES"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "CCL"
        )
    )
|#

("CLASS-NAME"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("CLASS-OF"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

#|
("CLASS-PRECEDENCE-LIST"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "CCL"
        )
    )
|#

#|
("CLASS-PROTOTYPE"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "CCL"
        )
    )
|#

#|
("CLASS-SLOTS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

("CLEAR-INPUT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CLEAR-OUTPUT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CLOSE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CLRHASH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CODE-CHAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COERCE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COMPILATION-SPEED"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COMPILE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COMPILE-FILE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COMPILE-FILE-PATHNAME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COMPILED-FUNCTION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COMPILED-FUNCTION-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COMPILER-MACRO"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COMPILER-MACRO-FUNCTION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COMPLEMENT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COMPLEX"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COMPLEXP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COMPUTE-APPLICABLE-METHODS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

#|
("COMPUTE-EFFECTIVE-METHOD"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "CCL"
        )
    )
|#

("COMPUTE-RESTARTS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CONCATENATE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CONCATENATED-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CONCATENATED-STREAM-STREAMS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CONDITION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CONJUGATE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CONS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CONSP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CONSTANTLY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CONSTANTP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CONTINUE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CONTROL-ERROR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COPY-ALIST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COPY-LIST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COPY-PPRINT-DISPATCH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COPY-READTABLE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COPY-SEQ"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COPY-STRUCTURE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COPY-SYMBOL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COPY-TREE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COSH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COUNT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COUNT-IF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("COUNT-IF-NOT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("CTYPECASE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DEBUG"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DECF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DECLAIM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DECLARATION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DECLARATION-INFORMATION"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM "SB-CLTL2"
        )
    )

("DECLARE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DECODE-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DECODE-UNIVERSAL-TIME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DEFCLASS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("DEFCONSTANT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DEFGENERIC"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("DEFINE-COMPILER-MACRO"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DEFINE-CONDITION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )


("DEFINE-CONSTANT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM NIL
        )
    )

#|
("DEFINE-DECLARATION"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM "COMMON-LISP"
        )
    )
|#

("DEFINE-METHOD-COMBINATION"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("DEFINE-MODIFY-MACRO"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DEFINE-SETF-EXPANDER"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DEFINE-SETF-METHOD"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("DEFMACRO"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DEFMETHOD"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("DEFPACKAGE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DEFPARAMETER"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DEFSETF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DEFSTRUCT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DEFTYPE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DEFUN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DEFVAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DELETE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DELETE-DUPLICATES"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DELETE-FILE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DELETE-IF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DELETE-IF-NOT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DELETE-PACKAGE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DENOMINATOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DEPOSIT-FIELD"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DESCRIBE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DESCRIBE-OBJECT"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("DESTRUCTURING-BIND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DIGIT-CHAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DIGIT-CHAR-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DIRECTORY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DIRECTORY-NAMESTRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DISASSEMBLE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DIVISION-BY-ZERO"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DO"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DO*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DO-ALL-SYMBOLS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DO-EXTERNAL-SYMBOLS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DO-SYMBOLS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DOCUMENTATION"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("DOLIST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DOTIMES"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DOUBLE-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DOUBLE-FLOAT-EPSILON"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DOUBLE-FLOAT-NEGATIVE-EPSILON"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DPB"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DRIBBLE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("DYNAMIC-EXTENT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ECASE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ECHO-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ECHO-STREAM-INPUT-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ECHO-STREAM-OUTPUT-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ED"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("EIGHTH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ELT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ENCLOSE"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM nil
        )
    )

("ENCODE-UNIVERSAL-TIME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("END-OF-FILE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ENDP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ENOUGH-NAMESTRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ENSURE-GENERIC-FUNCTION"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("EQ"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("EQL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("EQUAL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("EQUALP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ERROR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ETYPECASE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("EVAL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("EVAL-WHEN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("EVENP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("EVERY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("EXP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("EXPORT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("EXPT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("EXTENDED-CHAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FBOUNDP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FCEILING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FDEFINITION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FFLOOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FIFTH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FILE-AUTHOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FILE-ERROR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FILE-ERROR-PATHNAME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FILE-LENGTH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FILE-NAMESTRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FILE-POSITION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FILE-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FILE-STRING-LENGTH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FILE-WRITE-DATE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FILL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FILL-POINTER"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FIND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FIND-ALL-SYMBOLS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FIND-CLASS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("FIND-IF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FIND-IF-NOT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FIND-METHOD"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("FIND-PACKAGE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FIND-RESTART"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FIND-SYMBOL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FINISH-OUTPUT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FIRST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FIXNUM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FLET"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FLOAT-DIGITS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FLOAT-PRECISION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FLOAT-RADIX"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FLOAT-SIGN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FLOATING-POINT-INEXACT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FLOATING-POINT-INVALID-OPERATION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FLOATING-POINT-OVERFLOW"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FLOATING-POINT-UNDERFLOW"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FLOATP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FLOOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FMAKUNBOUND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FORCE-OUTPUT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FORMAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FORMATTER"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

#|
("FORWARD-REFERENCED-CLASS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

("FOURTH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FRESH-LINE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FROUND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FTRUNCATE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FTYPE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FUNCALL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

#|
("FUNCALLABLE-STANDARD-CLASS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "CCL"
        )
    )
|#

("FUNCTION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FUNCTION-INFORMATION"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM "SB-CLTL2"
        )
    )

("FUNCTION-KEYWORDS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("FUNCTION-LAMBDA-EXPRESSION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("FUNCTIONP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("GCD"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

#|
("GENERIC-FLET"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM nil
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )
|#

("GENERIC-FUNCTION"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

#|
("GENERIC-FUNCTION-ARGUMENT-PRECEDENCE-ORDER"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

#|
("GENERIC-FUNCTION-DECLARATIONS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

#|
("GENERIC-FUNCTION-INITIAL-METHODS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

#|
("GENERIC-FUNCTION-LAMBDA-LIST"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

#|
("GENERIC-FUNCTION-METHOD-CLASS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "CCL"
        )
    )
|#

#|
("GENERIC-FUNCTION-METHOD-COMBINATION"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "CCL"
        )
    )
|#

#|
("GENERIC-FUNCTION-METHODS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "CCL"
        )
    )
|#

#|
("GENERIC-FUNCTION-NAME"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

#|
("GENERIC-LABELS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM nil
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )
|#

("GENSYM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("GENTEMP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("GET"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("GET-DECODED-TIME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("GET-DISPATCH-MACRO-CHARACTER"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("GET-INTERNAL-REAL-TIME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("GET-INTERNAL-RUN-TIME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("GET-MACRO-CHARACTER"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("GET-OUTPUT-STREAM-STRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("GET-PROPERTIES"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("GET-SETF-EXPANSION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("GET-SETF-METHOD"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM nil
        )
    )

("GET-SETF-METHOD-MULTIPLE-VALUE"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM nil
        )
    )

("GET-UNIVERSAL-TIME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("GETF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("GETHASH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("GO"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("GRAPHIC-CHAR-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("HANDLER-BIND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("HANDLER-CASE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("HASH-TABLE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("HASH-TABLE-COUNT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("HASH-TABLE-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("HASH-TABLE-REHASH-SIZE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("HASH-TABLE-REHASH-THRESHOLD"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("HASH-TABLE-SIZE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("HASH-TABLE-TEST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("HOST-NAMESTRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("IDENTITY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("IF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("IGNORABLE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("IGNORE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("IGNORE-ERRORS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("IMAGPART"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("IMPORT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("IN-PACKAGE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("INCF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("INITIALIZE-INSTANCE"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("INLINE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("INPUT-STREAM-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("INSPECT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("INTEGER"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("INTEGER-DECODE-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("INTEGER-LENGTH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("INTEGERP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("INTERACTIVE-STREAM-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("INTERN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("INTERNAL-TIME-UNITS-PER-SECOND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("INTERSECTION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("INVALID-METHOD-ERROR"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("INVOKE-DEBUGGER"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("INVOKE-RESTART"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("INVOKE-RESTART-INTERACTIVELY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ISQRT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("KEYWORD"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("KEYWORDP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LABELS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LAMBDA"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LAMBDA-LIST-KEYWORDS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LAMBDA-PARAMETERS-LIMIT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

;;; Don't import last, since allegro has 1-argument last, and we want
;;; two argument last (defined in allegro-4-0-defs)
("LAST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LCM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LDB"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LDB-TEST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LDIFF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LEAST-NEGATIVE-DOUBLE-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LEAST-NEGATIVE-LONG-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LEAST-NEGATIVE-NORMALIZED-DOUBLE-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LEAST-NEGATIVE-NORMALIZED-LONG-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LEAST-NEGATIVE-NORMALIZED-SHORT-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LEAST-NEGATIVE-NORMALIZED-SINGLE-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LEAST-NEGATIVE-SHORT-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LEAST-NEGATIVE-SINGLE-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LEAST-POSITIVE-DOUBLE-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LEAST-POSITIVE-LONG-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LEAST-POSITIVE-NORMALIZED-DOUBLE-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LEAST-POSITIVE-NORMALIZED-LONG-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LEAST-POSITIVE-NORMALIZED-SHORT-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LEAST-POSITIVE-NORMALIZED-SINGLE-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LEAST-POSITIVE-SHORT-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LEAST-POSITIVE-SINGLE-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LENGTH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LET"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LET*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LISP-IMPLEMENTATION-TYPE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LISP-IMPLEMENTATION-VERSION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LIST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LIST*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LIST-ALL-PACKAGES"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LIST-LENGTH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LISTEN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LISTP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOAD"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOAD-LOGICAL-PATHNAME-TRANSLATIONS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOAD-TIME-VALUE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOCALLY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOG"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOGAND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOGANDC1"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOGANDC2"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOGBITP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOGCOUNT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOGEQV"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOGICAL-PATHNAME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOGICAL-PATHNAME-TRANSLATIONS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOGIOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOGNAND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOGNOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOGNOT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOGORC1"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOGORC2"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOGTEST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOGXOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LONG-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LONG-FLOAT-EPSILON"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LONG-FLOAT-NEGATIVE-EPSILON"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LONG-SITE-NAME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOOP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOOP-FINISH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("LOWER-CASE-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MACHINE-INSTANCE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MACHINE-TYPE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MACHINE-VERSION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MACRO-FUNCTION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MACROEXPAND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MACROEXPAND-1"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MACROLET"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-ARRAY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-BROADCAST-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-CONCATENATED-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-CONDITION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-DISPATCH-MACRO-CHARACTER"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-ECHO-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-HASH-TABLE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-INSTANCE"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("MAKE-INSTANCES-OBSOLETE"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("MAKE-LIST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-LOAD-FORM"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("MAKE-LOAD-FORM-SAVING-SLOTS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("MAKE-METHOD"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("MAKE-PACKAGE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-PATHNAME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-RANDOM-STATE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-SEQUENCE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-STRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-STRING-INPUT-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-STRING-OUTPUT-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-SYMBOL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-SYNONYM-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKE-TWO-WAY-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAKUNBOUND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAP-INTO"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAPC"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAPCAN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAPCAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAPCON"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAPHASH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAPL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAPLIST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MASK-FIELD"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MAX"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MEMBER"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MEMBER-IF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MEMBER-IF-NOT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MERGE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MERGE-PATHNAMES"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("METHOD"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("METHOD-COMBINATION"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("METHOD-COMBINATION-ERROR"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

#|
("METHOD-FUNCTION"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "CCL"
        )
    )
|#

#|
("METHOD-GENERIC-FUNCTION"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "CCL"
        )
    )
|#

#|
("METHOD-LAMBDA-LIST"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

("METHOD-QUALIFIERS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

#|
("METHOD-SLOT-NAME"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "CCL"
        )
    )
|#

#|
("METHOD-SPECIALIZERS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "CCL"
        )
    )
|#

("MIN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MINUSP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MISMATCH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MOD"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MOST-NEGATIVE-DOUBLE-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MOST-NEGATIVE-FIXNUM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MOST-NEGATIVE-LONG-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MOST-NEGATIVE-SHORT-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MOST-NEGATIVE-SINGLE-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MOST-POSITIVE-DOUBLE-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MOST-POSITIVE-FIXNUM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MOST-POSITIVE-LONG-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MOST-POSITIVE-SHORT-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MOST-POSITIVE-SINGLE-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MUFFLE-WARNING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MULTIPLE-VALUE-BIND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MULTIPLE-VALUE-CALL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MULTIPLE-VALUE-LIST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MULTIPLE-VALUE-PROG1"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MULTIPLE-VALUE-SETQ"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("MULTIPLE-VALUES-LIMIT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NAME-CHAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NAMESTRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NBUTLAST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NCONC"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NEXT-METHOD-P"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("NIL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NINTERSECTION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NINTH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NO-APPLICABLE-METHOD"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("NO-NEXT-METHOD"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("NOT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NOTANY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NOTEVERY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NOTINLINE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NRECONC"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NREVERSE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NSET-DIFFERENCE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NSET-EXCLUSIVE-OR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NSTRING-CAPITALIZE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NSTRING-DOWNCASE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NSTRING-UPCASE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NSUBLIS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NSUBST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NSUBST-IF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NSUBST-IF-NOT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NSUBSTITUTE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NSUBSTITUTE-IF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NSUBSTITUTE-IF-NOT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NTH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NTH-VALUE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NTHCDR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NULL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NUMBER"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NUMBERP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NUMERATOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("NUNION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ODDP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("OPEN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("OPEN-STREAM-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("OPTIMIZE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("OR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("OTHERWISE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("OUTPUT-STREAM-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PACKAGE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PACKAGE-ERROR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PACKAGE-ERROR-PACKAGE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PACKAGE-NAME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PACKAGE-NICKNAMES"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PACKAGE-SHADOWING-SYMBOLS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PACKAGE-USE-LIST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PACKAGE-USED-BY-LIST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PACKAGEP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PAIRLIS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PARSE-ERROR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PARSE-INTEGER"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PARSE-MACRO"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM "SB-CLTL2"
        )
    )

("PARSE-NAMESTRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PATHNAME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PATHNAME-DEVICE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PATHNAME-DIRECTORY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PATHNAME-HOST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PATHNAME-MATCH-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PATHNAME-NAME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PATHNAME-TYPE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PATHNAME-VERSION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PATHNAMEP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PEEK-CHAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PHASE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PI"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PLUSP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("POP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("POSITION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("POSITION-IF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("POSITION-IF-NOT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PPRINT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PPRINT-DISPATCH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PPRINT-EXIT-IF-LIST-EXHAUSTED"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PPRINT-FILL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PPRINT-INDENT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PPRINT-LINEAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PPRINT-LOGICAL-BLOCK"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PPRINT-NEWLINE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PPRINT-POP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PPRINT-TAB"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PPRINT-TABULAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PRIN1"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PRIN1-TO-STRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PRINC"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PRINC-TO-STRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PRINT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PRINT-NOT-READABLE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PRINT-NOT-READABLE-OBJECT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PRINT-OBJECT"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

;;; Note that this, while implemented, does not heed the unimplemented
;;; *print-readably* switch. If this is important, we have a portable
;;; implementation that does heed the switch, instead of inheriting
;;; allegro behavior.
("PRINT-UNREADABLE-OBJECT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PROBE-FILE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PROCLAIM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PROG"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PROG*"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PROG1"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PROG2"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PROGN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PROGRAM-ERROR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PROGV"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )


("PROVIDE"
    (:symbol
        :package "HOST"
	:import-from "COMMON-LISP"
	)
    )

("PSETF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PSETQ"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PUSH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("PUSHNEW"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("QUOTE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RANDOM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RANDOM-STATE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RANDOM-STATE-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RASSOC"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RASSOC-IF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RASSOC-IF-NOT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RATIO"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RATIONAL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RATIONALIZE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RATIONALP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("READ"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("READ-BYTE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("READ-CHAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("READ-CHAR-NO-HANG"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("READ-DELIMITED-LIST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("READ-FROM-STRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("READ-LINE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("READ-PRESERVING-WHITESPACE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("READER-ERROR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("READTABLE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("READTABLE-CASE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("READTABLEP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("REAL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("REALP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("REALPART"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("REDUCE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("REINITIALIZE-INSTANCE"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("REM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("REMF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("REMHASH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("REMOVE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("REMOVE-DUPLICATES"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("REMOVE-IF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("REMOVE-IF-NOT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("REMOVE-METHOD"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("REMPROP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RENAME-FILE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RENAME-PACKAGE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("REPLACE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("REQUIRE"
    (:symbol
        :package "HOST"
	:import-from "COMMON-LISP"
	)
    )

("REST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RESTART"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RESTART-BIND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RESTART-CASE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RESTART-NAME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RETURN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RETURN-FROM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("REVAPPEND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("REVERSE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ROOM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ROTATEF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ROUND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ROW-MAJOR-AREF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RPLACA"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("RPLACD"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SAFETY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SATISFIES"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SBIT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SCALE-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SCHAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SEARCH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SECOND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SEQUENCE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SERIOUS-CONDITION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SET"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SET-DIFFERENCE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SET-DISPATCH-MACRO-CHARACTER"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SET-EXCLUSIVE-OR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SET-MACRO-CHARACTER"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SET-PPRINT-DISPATCH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SET-SYNTAX-FROM-CHAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SETF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST" "HOST-CLOS")
        )
    )

("SETQ"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SEVENTH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SHADOW"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SHADOWING-IMPORT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SHARED-INITIALIZE"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("SHIFTF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SHORT-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SHORT-FLOAT-EPSILON"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SHORT-FLOAT-NEGATIVE-EPSILON"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SHORT-SITE-NAME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIGNAL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIGNED-BYTE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIGNUM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIMPLE-ARRAY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIMPLE-BASE-STRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIMPLE-BIT-VECTOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIMPLE-BIT-VECTOR-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIMPLE-CONDITION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIMPLE-CONDITION-FORMAT-ARGUMENTS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIMPLE-CONDITION-FORMAT-CONTROL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIMPLE-ERROR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIMPLE-STRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIMPLE-STRING-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIMPLE-TYPE-ERROR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIMPLE-VECTOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIMPLE-VECTOR-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIMPLE-WARNING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SINGLE-FLOAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SINGLE-FLOAT-EPSILON"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SINGLE-FLOAT-NEGATIVE-EPSILON"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SINH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SIXTH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SLEEP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SLOT-BOUNDP"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

#|
("SLOT-BOUNDP-USING-CLASS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

#|
("SLOT-DEFINITION"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

#|
("SLOT-DEFINITION-ALLOCATION"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

#|
("SLOT-DEFINITION-INITARGS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

#|
("SLOT-DEFINITION-INITFORM"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

#|
("SLOT-DEFINITION-INITFUNCTION"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

#|
("SLOT-DEFINITION-NAME"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "CCL"
        )
    )
|#

#|
("SLOT-DEFINITION-READERS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

#|
("SLOT-DEFINITION-TYPE"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

#|
("SLOT-DEFINITION-WRITERS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

("SLOT-EXISTS-P"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

#|
("SLOT-EXISTS-P-USING-CLASS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

("SLOT-MAKUNBOUND"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

#|
("SLOT-MAKUNBOUND-USING-CLASS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

("SLOT-MISSING"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("SLOT-UNBOUND"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("SLOT-VALUE"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

#|
("SLOT-VALUE-USING-CLASS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

("SOFTWARE-TYPE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SOFTWARE-VERSION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SOME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SORT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SPACE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SPECIAL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

#|
("SPECIAL-FORM-P"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM "COMMON-LISP"
        )
    )
|#

("SPECIAL-OPERATOR-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SPEED"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SQRT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STABLE-SORT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STANDARD"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

#|
("STANDARD-ACCESSOR-METHOD"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "CCL"
        )
    )
|#

("STANDARD-CHAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STANDARD-CHAR-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STANDARD-CLASS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("STANDARD-GENERIC-FUNCTION"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("STANDARD-METHOD"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("STANDARD-OBJECT"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

#|
("STANDARD-READER-METHOD"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "CCL"
        )
    )
|#

#|
("STANDARD-SLOT-DEFINITION"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM NIL
        )
    )
|#

#|
("STANDARD-WRITER-METHOD"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "CCL"
        )
    )
|#

("STEP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STORAGE-CONDITION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STORE-VALUE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STREAM-ELEMENT-TYPE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STREAM-ERROR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STREAM-ERROR-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STREAM-EXTERNAL-FORMAT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STREAMP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING-CAPITALIZE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING-CHAR"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("STRING-DOWNCASE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING-EQUAL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING-GREATERP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING-LEFT-TRIM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING-LESSP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING-NOT-EQUAL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING-NOT-GREATERP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING-NOT-LESSP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING-RIGHT-TRIM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING-TRIM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING-UPCASE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING/="
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING<"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING<="
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING="
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING>"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRING>="
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRINGP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRUCTURE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("STRUCTURE-CLASS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("STRUCTURE-OBJECT"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("STYLE-WARNING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SUBLIS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SUBSEQ"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SUBSETP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SUBST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SUBST-IF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SUBST-IF-NOT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SUBSTITUTE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SUBSTITUTE-IF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SUBSTITUTE-IF-NOT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SUBTYPEP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SVREF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SXHASH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SYMBOL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SYMBOL-FUNCTION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SYMBOL-MACROLET"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("SYMBOL-NAME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SYMBOL-PACKAGE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SYMBOL-PLIST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SYMBOL-VALUE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SYMBOLP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SYNONYM-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("SYNONYM-STREAM-SYMBOL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("T"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TAGBODY"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TAILP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TAN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TANH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TENTH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TERPRI"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("THE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("THIRD"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("THROW"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TIME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TRACE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TRANSLATE-LOGICAL-PATHNAME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TRANSLATE-PATHNAME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TREE-EQUAL"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TRUENAME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TRUNCATE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TWO-WAY-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TWO-WAY-STREAM-INPUT-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TWO-WAY-STREAM-OUTPUT-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TYPE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TYPE-ERROR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TYPE-ERROR-DATUM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TYPE-ERROR-EXPECTED-TYPE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TYPE-OF"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TYPE-SPECIFIER-P"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("TYPECASE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("TYPEP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("UNBOUND-SLOT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("UNBOUND-SLOT-INSTANCE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("UNBOUND-VARIABLE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("UNDEFINED-FUNCTION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("UNEXPORT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("UNINTERN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("UNION"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("UNLESS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("UNREAD-CHAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("UNSIGNED-BYTE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("UNTRACE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("UNUSE-PACKAGE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("UNWIND-PROTECT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("UPDATE-INSTANCE-FOR-DIFFERENT-CLASS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("UPDATE-INSTANCE-FOR-REDEFINED-CLASS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("UPGRADED-ARRAY-ELEMENT-TYPE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("UPGRADED-COMPLEX-PART-TYPE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("UPPER-CASE-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("USE-PACKAGE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("USE-VALUE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("USER-HOMEDIR-PATHNAME"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("VALUES"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("VALUES-LIST"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("VARIABLE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("VARIABLE-INFORMATION"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM "SB-CLTL2"
        )
    )

("VECTOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("VECTOR-POP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("VECTOR-PUSH"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("VECTOR-PUSH-EXTEND"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("VECTORP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WARN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WARNING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WHEN"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WILD-PATHNAME-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WITH-ACCESSORS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("WITH-COMPILATION-UNIT"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WITH-CONDITION-RESTARTS"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WITH-HASH-TABLE-ITERATOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WITH-INPUT-FROM-STRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WITH-OPEN-FILE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WITH-OPEN-STREAM"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WITH-OUTPUT-TO-STRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WITH-PACKAGE-ITERATOR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WITH-SIMPLE-RESTART"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WITH-SLOTS"
    (:SYMBOL
        :PACKAGE "HOST-CLOS"
        :IMPORT-FROM "COMMON-LISP"
        :EXPORT ("HOST-CLOS" "HOST")
        )
    )

("WITH-STANDARD-IO-SYNTAX"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WRITE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WRITE-BYTE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WRITE-CHAR"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WRITE-LINE"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WRITE-STRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("WRITE-TO-STRING"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("Y-OR-N-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("YES-OR-NO-P"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

("ZEROP"
    (:SYMBOL
        :PACKAGE "HOST"
        :IMPORT-FROM "COMMON-LISP"
        )
    )

;Added by SoftServe

("WITH-ALIEN" 
 (:SYMBOL 
   :PACKAGE "HOST"
   :IMPORT-FROM "SB-ALIEN"
  )
)                                           

("LOCAL-ALIEN-INFO" 
 (:SYMBOL 
   :PACKAGE "HOST"
   :IMPORT-FROM "SB-ALIEN-INTERNALS"
  )
)                      
                                            
;end                                            
                      
                      
("ASSQ"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM "SB-INT"
        )
    )

("CD"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

#|
("DEF-FOREIGN-CALLABLE"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )
|#

#|
("DEF-FOREIGN-FUNCTION"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )
|#

("DELQ"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM "SB-INT"
        )
    )

#|
("LIST-NREVERSE"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )
|#

#|
("LIST-REVERSE"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )
|#

("MEMQ"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM "SB-INT"
        )
    )

("PWD"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("QUIT"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM "SB-EXT"
        )
    )

("SHELL"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("STRING-APPEND"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("WITH-DYNAMIC-AREA"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("WITH-STATIC-AREA"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("XOR"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("GETENV"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("CHAR*-TO-STRING"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("DEFCSTRUCT"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("DEFFOREIGN-LIST"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("STRING-TO-CHAR*"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("%POINTER"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("%SYSINT"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("+&"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("/&"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("ARRAY-LENGTH"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("CLOSE-ALL-FILES"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("COPY-ARRAY-CONTENTS"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("DOS"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("EXIT"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("FILE-INFO"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("FLATSIZE"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("IFN"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

#|
("LSH"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM "CCL"
        )
    )
|#

("MAKE-WINDOW-STREAM"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("NCONS"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("NEQ"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM "SB-INT"
        )
    )

("NEQL"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("RPLACB"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("SEND-FILE"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("SEND-WINDOW"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("STREAM-DEFAULT-HANDLER"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

("STRING-SEARCH"
    (:SYMBOL
        :PACKAGE "HOSTX"
        :IMPORT-FROM NIL
        )
    )

)

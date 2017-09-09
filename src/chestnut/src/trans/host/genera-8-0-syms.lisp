;;; -*- Syntax: Common-Lisp; Package: HIMPL; Base: 10; Mode: Lisp -*-
;;;
;;; genera-8-0-syms.lisp -- HOST package database for Symbolics Genera 8.0
;;;
;;; author :  Richard Harris (from lucid-4-0-syms.lisp)
;;; date   :  17 Nov 92
;;;
;;; Copyright (c) 1992, Chestnut Software Inc.
;;; 

#-Symbolics
#.(error "Attempting to use incorrect host database.")

(in-package "HOST-IMPLEMENTATION")

(himpl:note-rcs-revision
 "$Source: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/chestnut/src/trans/host/genera-8-0-syms.lisp,v $"
 "$Revision: 1.1 $"
 "$Date: 2006-02-28 21:58:58 $")

(himpl:define-symbols :lisp nil

;;; Symbols with the comment NON-ANSI-STANDARD-CLOS are symbols from a list
;;; agreed upon between Symbolics and Lucid as being MOP extensions exported
;;; from the CLOS package.  They are listed in a message from Moon to the 
;;; Common-Lisp-Object-System@mcc.com, dated 4-March-90.

("&ALLOW-OTHER-KEYS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("&AUX"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("&BODY"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("&ENVIRONMENT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("&KEY"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("&OPTIONAL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("&REST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("&WHOLE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("**"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("***"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*BREAK-ON-SIGNALS*"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("*COMPILE-FILE-PATHNAME*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*COMPILE-FILE-TRUENAME*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*COMPILE-PRINT*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*COMPILE-VERBOSE*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*DEBUG-IO*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*DEBUGGER-HOOK*"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("*DEFAULT-PATHNAME-DEFAULTS*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*ERROR-OUTPUT*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*FEATURES*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*GENSYM-COUNTER*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*LOAD-PATHNAME*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*LOAD-PRINT*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*LOAD-TRUENAME*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*LOAD-VERBOSE*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*MACROEXPAND-HOOK*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*MODULES*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*PACKAGE*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*PRINT-ARRAY*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*PRINT-BASE*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*PRINT-CASE*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*PRINT-CIRCLE*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*PRINT-ESCAPE*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*PRINT-GENSYM*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*PRINT-LENGTH*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*PRINT-LEVEL*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*PRINT-LINES*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*PRINT-MISER-WIDTH*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*PRINT-PPRINT-DISPATCH*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*PRINT-PRETTY*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*PRINT-RADIX*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*PRINT-READABLY*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*PRINT-RIGHT-MARGIN*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*QUERY-IO*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*RANDOM-STATE*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*READ-BASE*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*READ-DEFAULT-FLOAT-FORMAT*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*READ-EVAL*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*READ-SUPPRESS*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*READTABLE*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*STANDARD-INPUT*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*STANDARD-OUTPUT*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*TERMINAL-IO*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("*TRACE-OUTPUT*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("+"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("++"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("+++"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("-"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("/"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("//"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("///"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("/="
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("1+"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("1-"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("<"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("<="
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("="
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

(">"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

(">="
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ABORT"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("ABS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ACONS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ACOS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ACOSH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ADD-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("ADJOIN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ADJUST-ARRAY"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ADJUSTABLE-ARRAY-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ALLOCATE-INSTANCE"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS-INTERNALS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("ALPHA-CHAR-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ALPHANUMERICP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("AND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("APPEND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("APPLY"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("APROPOS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("APROPOS-LIST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("AREF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ARITHMETIC-ERROR"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("ARITHMETIC-ERROR-OPERANDS"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("ARITHMETIC-ERROR-OPERATION"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("ARRAY"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ARRAY-DIMENSION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ARRAY-DIMENSION-LIMIT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ARRAY-DIMENSIONS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ARRAY-DISPLACEMENT"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("ARRAY-ELEMENT-TYPE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ARRAY-HAS-FILL-POINTER-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ARRAY-IN-BOUNDS-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ARRAY-RANK"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ARRAY-RANK-LIMIT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ARRAY-ROW-MAJOR-INDEX"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ARRAY-TOTAL-SIZE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ARRAY-TOTAL-SIZE-LIMIT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ARRAYP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ASH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ASIN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ASINH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ASSERT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ASSOC"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ASSOC-IF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ASSOC-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ATAN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ATANH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ATOM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("AUGMENT-ENVIRONMENT"
    (:symbol
        :package "HOSTX"
	:import-from :lisp
	)
    )

("BASE-CHAR"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("BASE-STRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BIGNUM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BIT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BIT-AND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BIT-ANDC1"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BIT-ANDC2"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BIT-EQV"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BIT-IOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BIT-NAND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BIT-NOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BIT-NOT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BIT-ORC1"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BIT-ORC2"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BIT-VECTOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BIT-VECTOR-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BIT-XOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BLOCK"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOOLE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOOLE-1"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOOLE-2"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOOLE-AND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOOLE-ANDC1"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOOLE-ANDC2"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOOLE-C1"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOOLE-C2"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOOLE-CLR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOOLE-EQV"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOOLE-IOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOOLE-NAND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOOLE-NOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOOLE-ORC1"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOOLE-ORC2"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOOLE-SET"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOOLE-XOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOTH-CASE-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BOUNDP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BREAK"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BROADCAST-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BROADCAST-STREAM-STREAMS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BUILT-IN-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("BUTLAST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BYTE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BYTE-POSITION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("BYTE-SIZE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CAAAAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CAAADR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CAAAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CAADAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CAADDR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CAADR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CAAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CADAAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CADADR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CADAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CADDAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CADDDR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CADDR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CADR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CALL-ARGUMENTS-LIMIT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CALL-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("CALL-NEXT-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("CAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CASE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CATCH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CCASE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CDAAAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CDAADR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CDAAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CDADAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CDADDR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CDADR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CDAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CDDAAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CDDADR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CDDAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CDDDAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CDDDDR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CDDDR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CDDR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CDR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CEILING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CELL-ERROR"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("CELL-ERROR-NAME"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("CERROR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHANGE-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("CHAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR-CODE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR-CODE-LIMIT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR-DOWNCASE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR-EQUAL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR-GREATERP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR-INT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR-LESSP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR-NAME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR-NOT-EQUAL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR-NOT-GREATERP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR-NOT-LESSP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR-UPCASE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR/="
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR<"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR<="
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR="
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR>"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHAR>="
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHARACTER"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHARACTERP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CHECK-TYPE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CIS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("CLASS-DEFAULT-INITARGS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("CLASS-DIRECT-DEFAULT-INITARGS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("CLASS-DIRECT-SUBCLASSES"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("CLASS-DIRECT-SUPERCLASSES"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("CLASS-NAME"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("CLASS-OF"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("CLASS-PRECEDENCE-LIST"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("CLASS-PROTOTYPE"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("CLASS-SLOTS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("CLEAR-INPUT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CLEAR-OUTPUT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CLOSE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CLRHASH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CODE-CHAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COERCE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COMPILATION-SPEED"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COMPILE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COMPILE-FILE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COMPILE-FILE-PATHNAME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COMPILED-FUNCTION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COMPILED-FUNCTION-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COMPILER-MACRO"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("COMPILER-MACRO-FUNCTION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COMPLEMENT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COMPLEX"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COMPLEXP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COMPUTE-APPLICABLE-METHODS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("COMPUTE-EFFECTIVE-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("COMPUTE-RESTARTS"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("CONCATENATE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CONCATENATED-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CONCATENATED-STREAM-STREAMS"
    (:SYMBOL
        :PACKAGE "HOST"
	:IMPORT-FROM :lisp
	)
    )

("COND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CONDITION"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("CONJUGATE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CONS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CONSP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CONSTANTLY"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CONSTANTP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CONTINUE"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("CONTROL-ERROR"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("COPY-ALIST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COPY-LIST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COPY-PPRINT-DISPATCH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COPY-READTABLE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COPY-SEQ"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COPY-STRUCTURE"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("COPY-SYMBOL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COPY-TREE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COSH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COUNT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COUNT-IF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("COUNT-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("CTYPECASE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DEBUG"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DECF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DECLAIM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DECLARATION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DECLARATION-INFORMATION"
    (:symbol
        :package "HOSTX"
	:import-from :lisp
	)
    )

("DECLARE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DECODE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DECODE-UNIVERSAL-TIME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DEFCLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("DEFCONSTANT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DEFGENERIC"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("DEFINE-COMPILER-MACRO"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DEFINE-CONDITION"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("DEFINE-DECLARATION"
    (:symbol
        :package "HOSTX"
	:import-from :lisp
	)
    )

("DEFINE-METHOD-COMBINATION"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("DEFINE-MODIFY-MACRO"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DEFINE-SETF-EXPANDER"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("DEFINE-SETF-METHOD"
    (:symbol
        :package "HOSTX"
	:import-from :lisp
	)
    )

("DEFMACRO"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DEFMETHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("DEFPACKAGE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DEFPARAMETER"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DEFSETF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DEFSTRUCT"
    (:symbol
        :package "HOST"
	:import-from "COMMON-LISP" ; defstruct is broken in FUTURE-COMMON-LISP
	)
    )

("DEFTYPE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DEFUN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DEFVAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DELETE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DELETE-DUPLICATES"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DELETE-FILE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DELETE-IF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DELETE-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DELETE-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DENOMINATOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DEPOSIT-FIELD"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DESCRIBE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DESCRIBE-OBJECT"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("DESTRUCTURING-BIND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DIGIT-CHAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DIGIT-CHAR-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DIRECTORY"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DIRECTORY-NAMESTRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DISASSEMBLE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DIVISION-BY-ZERO"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("DO"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DO*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DO-ALL-SYMBOLS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DO-EXTERNAL-SYMBOLS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DO-SYMBOLS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DOCUMENTATION"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("DOLIST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DOTIMES"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DOUBLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DOUBLE-FLOAT-EPSILON"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DOUBLE-FLOAT-NEGATIVE-EPSILON"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DPB"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DRIBBLE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("DYNAMIC-EXTENT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ECASE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ECHO-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ECHO-STREAM-INPUT-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ECHO-STREAM-OUTPUT-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ED"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("EIGHTH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ELT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ENCLOSE"
    (:symbol
        :package "HOSTX"
	:import-from :lisp
	)
    )

("ENCODE-UNIVERSAL-TIME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("END-OF-FILE"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("ENDP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ENOUGH-NAMESTRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ENSURE-GENERIC-FUNCTION"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("EQ"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("EQL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("EQUAL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("EQUALP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ERROR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ETYPECASE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("EVAL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("EVAL-WHEN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("EVENP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("EVERY"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("EXP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("EXPORT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("EXPT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("EXTENDED-CHAR"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("FBOUNDP"
    (:symbol
        :package "HOST"
	:import-from "FUTURE-COMMON-LISP"
	)
    )

("FCEILING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FDEFINITION"
    (:symbol
        :package "HOST"
	:import-from "FUTURE-COMMON-LISP"
	)
    )

("FFLOOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FIFTH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FILE-AUTHOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FILE-ERROR"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("FILE-ERROR-PATHNAME"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("FILE-LENGTH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FILE-NAMESTRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FILE-POSITION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FILE-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FILE-STRING-LENGTH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FILE-WRITE-DATE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FILL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FILL-POINTER"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FIND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FIND-ALL-SYMBOLS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FIND-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("FIND-IF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FIND-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FIND-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("FIND-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FIND-RESTART"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("FIND-SYMBOL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FINISH-OUTPUT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FIRST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FIXNUM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FLET"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FLOAT-DIGITS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FLOAT-PRECISION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FLOAT-RADIX"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FLOAT-SIGN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FLOATING-POINT-INEXACT"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("FLOATING-POINT-INVALID-OPERATION"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("FLOATING-POINT-OVERFLOW"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("FLOATING-POINT-UNDERFLOW"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("FLOATP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FLOOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FMAKUNBOUND"
    (:symbol
        :package "HOST"
	:import-from "FUTURE-COMMON-LISP"
	)
    )

("FORCE-OUTPUT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FORMAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FORMATTER"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FORWARD-REFERENCED-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("FOURTH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FRESH-LINE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FROUND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FTRUNCATE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FTYPE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FUNCALL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FUNCALLABLE-STANDARD-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("FUNCTION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FUNCTION-INFORMATION"
    (:symbol
        :package "HOSTX"
	:import-from :lisp
	)
    )

("FUNCTION-KEYWORDS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("FUNCTION-LAMBDA-EXPRESSION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("FUNCTIONP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("GCD"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("GENERIC-FLET"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("GENERIC-FUNCTION"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("GENERIC-FUNCTION-ARGUMENT-PRECEDENCE-ORDER"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("GENERIC-FUNCTION-DECLARATIONS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("GENERIC-FUNCTION-INITIAL-METHODS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("GENERIC-FUNCTION-LAMBDA-LIST"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("GENERIC-FUNCTION-METHOD-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("GENERIC-FUNCTION-METHOD-COMBINATION"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("GENERIC-FUNCTION-METHODS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("GENERIC-FUNCTION-NAME"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("GENERIC-LABELS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("GENSYM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("GENTEMP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("GET"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("GET-DECODED-TIME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("GET-DISPATCH-MACRO-CHARACTER"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("GET-INTERNAL-REAL-TIME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("GET-INTERNAL-RUN-TIME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("GET-MACRO-CHARACTER"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("GET-OUTPUT-STREAM-STRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("GET-PROPERTIES"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("GET-SETF-EXPANSION"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("GET-SETF-METHOD"
    (:symbol
        :package "HOSTX"
	:import-from :lisp
	)
    )

("GET-SETF-METHOD-MULTIPLE-VALUE"
    (:symbol
        :package "HOSTX"
	:import-from :lisp
	)
    )

("GET-UNIVERSAL-TIME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("GETF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("GETHASH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("GO"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("GRAPHIC-CHAR-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("HANDLER-BIND"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("HANDLER-CASE"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("HASH-TABLE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("HASH-TABLE-COUNT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("HASH-TABLE-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("HASH-TABLE-REHASH-SIZE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("HASH-TABLE-REHASH-THRESHOLD"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("HASH-TABLE-SIZE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("HASH-TABLE-TEST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("HOST-NAMESTRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("IDENTITY"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("IF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("IGNORABLE"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("IGNORE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("IGNORE-ERRORS"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("IMAGPART"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("IMPORT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("IN-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("INCF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("INITIALIZE-INSTANCE"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("INLINE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("INPUT-STREAM-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("INSPECT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("INTEGER"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("INTEGER-DECODE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("INTEGER-LENGTH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("INTEGERP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("INTERACTIVE-STREAM-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("INTERN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("INTERNAL-TIME-UNITS-PER-SECOND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("INTERSECTION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("INVALID-METHOD-ERROR"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("INVOKE-DEBUGGER"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("INVOKE-RESTART"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("INVOKE-RESTART-INTERACTIVELY"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("ISQRT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("KEYWORD"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("KEYWORDP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LABELS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LAMBDA"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LAMBDA-LIST-KEYWORDS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LAMBDA-PARAMETERS-LIMIT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LAST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LCM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LDB"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LDB-TEST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LDIFF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LEAST-NEGATIVE-DOUBLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LEAST-NEGATIVE-LONG-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LEAST-NEGATIVE-NORMALIZED-DOUBLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LEAST-NEGATIVE-NORMALIZED-LONG-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LEAST-NEGATIVE-NORMALIZED-SHORT-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LEAST-NEGATIVE-NORMALIZED-SINGLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LEAST-NEGATIVE-SHORT-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LEAST-NEGATIVE-SINGLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LEAST-POSITIVE-DOUBLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LEAST-POSITIVE-LONG-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LEAST-POSITIVE-NORMALIZED-DOUBLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LEAST-POSITIVE-NORMALIZED-LONG-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LEAST-POSITIVE-NORMALIZED-SHORT-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LEAST-POSITIVE-NORMALIZED-SINGLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LEAST-POSITIVE-SHORT-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LEAST-POSITIVE-SINGLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LENGTH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LET"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LET*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LISP-IMPLEMENTATION-TYPE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LISP-IMPLEMENTATION-VERSION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LIST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LIST*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LIST-ALL-PACKAGES"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LIST-LENGTH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LISTEN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LISTP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOAD"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOAD-LOGICAL-PATHNAME-TRANSLATIONS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOAD-TIME-VALUE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOCALLY"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOG"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOGAND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOGANDC1"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOGANDC2"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOGBITP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOGCOUNT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOGEQV"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOGICAL-PATHNAME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOGICAL-PATHNAME-TRANSLATIONS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOGIOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOGNAND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOGNOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOGNOT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOGORC1"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOGORC2"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOGTEST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOGXOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LONG-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LONG-FLOAT-EPSILON"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LONG-FLOAT-NEGATIVE-EPSILON"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LONG-SITE-NAME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOOP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("LOOP-FINISH"
    (:symbol
        :package "HOST"
	:import-from :lisp ; maybe "SCL" instead?
	)
    )

("LOWER-CASE-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MACHINE-INSTANCE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MACHINE-TYPE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MACHINE-VERSION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MACRO-FUNCTION"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("MACROEXPAND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MACROEXPAND-1"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MACROLET"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAKE-ARRAY"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAKE-BROADCAST-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAKE-CONCATENATED-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAKE-CONDITION"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("MAKE-DISPATCH-MACRO-CHARACTER"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAKE-ECHO-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAKE-HASH-TABLE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAKE-INSTANCE"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("MAKE-INSTANCES-OBSOLETE"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("MAKE-LIST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAKE-LOAD-FORM"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("MAKE-LOAD-FORM-SAVING-SLOTS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("MAKE-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("MAKE-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAKE-PATHNAME"
    (:symbol
        :package "HOST"
	:import-from "HOST-IMPLEMENTATION"
	)
    )

("MAKE-RANDOM-STATE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAKE-SEQUENCE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAKE-STRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAKE-STRING-INPUT-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAKE-STRING-OUTPUT-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAKE-SYMBOL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAKE-SYNONYM-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAKE-TWO-WAY-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAKUNBOUND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAP-INTO"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAPC"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAPCAN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAPCAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAPCON"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAPHASH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAPL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAPLIST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MASK-FIELD"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MAX"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MEMBER"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MEMBER-IF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MEMBER-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MERGE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MERGE-PATHNAMES"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("METHOD-COMBINATION"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("METHOD-COMBINATION-ERROR"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("METHOD-FUNCTION"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("METHOD-GENERIC-FUNCTION"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("METHOD-LAMBDA-LIST"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("METHOD-QUALIFIERS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("METHOD-SLOT-NAME"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("METHOD-SPECIALIZERS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("MIN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MINUSP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MISMATCH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MOD"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MOST-NEGATIVE-DOUBLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MOST-NEGATIVE-FIXNUM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MOST-NEGATIVE-LONG-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MOST-NEGATIVE-SHORT-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MOST-NEGATIVE-SINGLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MOST-POSITIVE-DOUBLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MOST-POSITIVE-FIXNUM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MOST-POSITIVE-LONG-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MOST-POSITIVE-SHORT-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MOST-POSITIVE-SINGLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MUFFLE-WARNING"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("MULTIPLE-VALUE-BIND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MULTIPLE-VALUE-CALL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MULTIPLE-VALUE-LIST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MULTIPLE-VALUE-PROG1"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MULTIPLE-VALUE-SETQ"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("MULTIPLE-VALUES-LIMIT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NAME-CHAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NAMESTRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NBUTLAST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NCONC"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NEXT-METHOD-P"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("NIL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NINTERSECTION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NINTH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NO-APPLICABLE-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("NO-NEXT-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("NOT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NOTANY"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NOTEVERY"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NOTINLINE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NRECONC"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NREVERSE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NSET-DIFFERENCE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NSET-EXCLUSIVE-OR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NSTRING-CAPITALIZE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NSTRING-DOWNCASE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NSTRING-UPCASE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NSUBLIS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NSUBST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NSUBST-IF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NSUBST-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NSUBSTITUTE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NSUBSTITUTE-IF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NSUBSTITUTE-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NTH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NTH-VALUE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NTHCDR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NULL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NUMBER"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NUMBERP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NUMERATOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("NUNION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ODDP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("OPEN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("OPEN-STREAM-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("OPTIMIZE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("OR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("OTHERWISE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("OUTPUT-STREAM-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PACKAGE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PACKAGE-ERROR"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("PACKAGE-ERROR-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("PACKAGE-NAME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PACKAGE-NICKNAMES"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PACKAGE-SHADOWING-SYMBOLS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PACKAGE-USE-LIST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PACKAGE-USED-BY-LIST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PACKAGEP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PAIRLIS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PARSE-ERROR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PARSE-INTEGER"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PARSE-MACRO"
    (:symbol
        :package "HOSTX"
	:import-from :lisp
	)
    )

("PARSE-NAMESTRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PATHNAME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PATHNAME-DEVICE"
    (:symbol
        :package "HOST"
	:import-from "HOST-IMPLEMENTATION"
	)
    )

("PATHNAME-DIRECTORY"
    (:symbol
        :package "HOST"
	:import-from "HOST-IMPLEMENTATION"
	)
    )

("PATHNAME-HOST"
    (:symbol
        :package "HOST"
	:import-from "HOST-IMPLEMENTATION"
	)
    )

("PATHNAME-MATCH-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PATHNAME-NAME"
    (:symbol
        :package "HOST"
	:import-from "HOST-IMPLEMENTATION"
	)
    )

("PATHNAME-TYPE"
    (:symbol
        :package "HOST"
	:import-from "HOST-IMPLEMENTATION"
	)
    )

("PATHNAME-VERSION"
    (:symbol
        :package "HOST"
	:import-from "HOST-IMPLEMENTATION"
	)
    )

("PATHNAMEP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PEEK-CHAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PHASE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PI"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PLUSP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("POP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("POSITION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("POSITION-IF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("POSITION-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PPRINT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PPRINT-DISPATCH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PPRINT-EXIT-IF-LIST-EXHAUSTED"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PPRINT-FILL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PPRINT-INDENT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PPRINT-LINEAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PPRINT-LOGICAL-BLOCK"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PPRINT-NEWLINE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PPRINT-POP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PPRINT-TAB"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PPRINT-TABULAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PRIN1"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PRIN1-TO-STRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PRINC"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PRINC-TO-STRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PRINT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PRINT-NOT-READABLE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PRINT-NOT-READABLE-OBJECT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PRINT-OBJECT"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("PRINT-UNREADABLE-OBJECT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PROBE-FILE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PROCLAIM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PROG"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PROG*"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PROG1"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PROG2"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PROGN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PROGRAM-ERROR"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("PROGV"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )


("PROVIDE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PSETF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PSETQ"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PUSH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("PUSHNEW"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("QUOTE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("RANDOM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("RANDOM-STATE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("RANDOM-STATE-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("RASSOC"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("RASSOC-IF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("RASSOC-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("RATIO"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("RATIONAL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("RATIONALIZE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("RATIONALP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("READ"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )


("READ-BYTE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("READ-CHAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("READ-CHAR-NO-HANG"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("READ-DELIMITED-LIST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("READ-FROM-STRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("READ-LINE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("READ-PRESERVING-WHITESPACE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("READER-ERROR"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("READTABLE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("READTABLE-CASE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("READTABLEP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("REAL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("REALP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("REALPART"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("REDUCE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("REINITIALIZE-INSTANCE"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("REM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("REMF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("REMHASH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("REMOVE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("REMOVE-DUPLICATES"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("REMOVE-IF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("REMOVE-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("REMOVE-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("REMPROP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("RENAME-FILE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("RENAME-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("REPLACE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("REQUIRE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("REST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("RESTART"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("RESTART-BIND"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("RESTART-CASE"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("RESTART-NAME"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("RETURN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("RETURN-FROM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("REVAPPEND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("REVERSE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ROOM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ROTATEF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ROUND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ROW-MAJOR-AREF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("RPLACA"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("RPLACD"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SAFETY"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SATISFIES"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SBIT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SCALE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SCHAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SEARCH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SECOND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SEQUENCE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SERIOUS-CONDITION"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("SET"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SET-DIFFERENCE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SET-DISPATCH-MACRO-CHARACTER"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SET-EXCLUSIVE-OR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SET-MACRO-CHARACTER"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SET-PPRINT-DISPATCH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SET-SYNTAX-FROM-CHAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SETF"
    (:symbol
        :package "HOST"
	:import-from "FUTURE-COMMON-LISP"
	:export ("HOST" "HOST-CLOS")
	)
    )

("SETQ"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SEVENTH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SHADOW"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SHADOWING-IMPORT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SHARED-INITIALIZE"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("SHIFTF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SHORT-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SHORT-FLOAT-EPSILON"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SHORT-FLOAT-NEGATIVE-EPSILON"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SHORT-SITE-NAME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SIGNAL"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("SIGNED-BYTE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SIGNUM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SIMPLE-ARRAY"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SIMPLE-BASE-STRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SIMPLE-BIT-VECTOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SIMPLE-BIT-VECTOR-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SIMPLE-CONDITION"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("SIMPLE-CONDITION-FORMAT-ARGUMENTS"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("SIMPLE-CONDITION-FORMAT-CONTROL"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("SIMPLE-ERROR"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("SIMPLE-STRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SIMPLE-STRING-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SIMPLE-TYPE-ERROR"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("SIMPLE-VECTOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SIMPLE-VECTOR-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SIMPLE-WARNING"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("SIN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SINGLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SINGLE-FLOAT-EPSILON"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SINGLE-FLOAT-NEGATIVE-EPSILON"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SINH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SIXTH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SLEEP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SLOT-BOUNDP"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("SLOT-BOUNDP-USING-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION-ALLOCATION"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION-INITARGS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION-INITFORM"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION-INITFUNCTION"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION-NAME"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION-READERS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION-TYPE"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION-WRITERS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-EXISTS-P"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("SLOT-EXISTS-P-USING-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-MAKUNBOUND"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("SLOT-MAKUNBOUND-USING-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-MISSING"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("SLOT-UNBOUND"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("SLOT-VALUE"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("SLOT-VALUE-USING-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SOFTWARE-TYPE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SOFTWARE-VERSION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SOME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SORT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SPACE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SPECIAL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SPECIAL-FORM-P"
    (:symbol
        :package "HOSTX"
	:import-from :lisp
	)
    )

("SPECIAL-OPERATOR-P"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

;;; Removed pending discussion on common-lisp-object-system mailing list.
;("SPECIALIZER-DIRECT-GENERIC-FUNCTIONS"
;    (:symbol
;        :package "HOST-CLOS"
;	:import-from
;         "CLOS"
;	;; NON-ANSI-STANDARD-CLOS
;	)
;    )

;;; Removed pending discussion on common-lisp-object-system mailing list.
;("SPECIALIZER-DIRECT-METHODS"
;    (:symbol
;        :package "HOST-CLOS"
;	:import-from
;         "CLOS"
;	;; NON-ANSI-STANDARD-CLOS
;	)
;    )

("SPEED"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SQRT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STABLE-SORT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STANDARD"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("STANDARD-ACCESSOR-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("STANDARD-CHAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STANDARD-CHAR-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STANDARD-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("STANDARD-GENERIC-FUNCTION"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("STANDARD-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("STANDARD-OBJECT"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("STANDARD-READER-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("STANDARD-SLOT-DEFINITION"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("STANDARD-WRITER-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("STEP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STORAGE-CONDITION"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("STORE-VALUE"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STREAM-ELEMENT-TYPE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STREAM-ERROR"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("STREAM-ERROR-STREAM"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("STREAM-EXTERNAL-FORMAT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STREAMP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING-CAPITALIZE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING-CHAR"
    (:symbol
        :package "HOSTX"
	:import-from "LISP"
	)
    )

("STRING-DOWNCASE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING-EQUAL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING-GREATERP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING-LEFT-TRIM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING-LESSP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING-NOT-EQUAL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING-NOT-GREATERP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING-NOT-LESSP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING-RIGHT-TRIM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING-TRIM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING-UPCASE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING/="
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING<"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING<="
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING="
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING>"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRING>="
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRINGP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRUCTURE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("STRUCTURE-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("STRUCTURE-OBJECT"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("STYLE-WARNING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SUBLIS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SUBSEQ"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SUBSETP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SUBST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SUBST-IF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SUBST-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SUBSTITUTE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SUBSTITUTE-IF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SUBSTITUTE-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SUBTYPEP"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("SVREF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SXHASH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SYMBOL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SYMBOL-FUNCTION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SYMBOL-MACROLET"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("SYMBOL-NAME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SYMBOL-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SYMBOL-PLIST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SYMBOL-VALUE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SYMBOLP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SYNONYM-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("SYNONYM-STREAM-SYMBOL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("T"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TAGBODY"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TAILP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TAN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TANH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TENTH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TERPRI"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("THE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("THIRD"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("THROW"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TIME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TRACE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TRANSLATE-LOGICAL-PATHNAME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TRANSLATE-PATHNAME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TREE-EQUAL"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TRUENAME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TRUNCATE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TWO-WAY-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TWO-WAY-STREAM-INPUT-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TWO-WAY-STREAM-OUTPUT-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TYPE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TYPE-ERROR"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("TYPE-ERROR-DATUM"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("TYPE-ERROR-EXPECTED-TYPE"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("TYPE-OF"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TYPE-SPECIFIER-P"
    (:symbol
        :package "HOSTX"
	:import-from nil
	)
    )

("TYPECASE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("TYPEP"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("UNBOUND-SLOT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("UNBOUND-SLOT-INSTANCE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("UNBOUND-VARIABLE"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("UNDEFINED-FUNCTION"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("UNEXPORT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("UNINTERN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("UNION"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("UNLESS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("UNREAD-CHAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("UNSIGNED-BYTE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("UNTRACE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("UNUSE-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("UNWIND-PROTECT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("UPDATE-INSTANCE-FOR-DIFFERENT-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("UPDATE-INSTANCE-FOR-REDEFINED-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("UPGRADED-ARRAY-ELEMENT-TYPE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("UPGRADED-COMPLEX-PART-TYPE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("UPPER-CASE-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("USE-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("USE-VALUE"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("USER-HOMEDIR-PATHNAME"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("VALUES"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("VALUES-LIST"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("VARIABLE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("VARIABLE-INFORMATION"
    (:symbol
        :package "HOSTX"
	:import-from :lisp
	)
    )

("VECTOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("VECTOR-POP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("VECTOR-PUSH"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("VECTOR-PUSH-EXTEND"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("VECTORP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WARN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WARNING"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("WHEN"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WILD-PATHNAME-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WITH-ACCESSORS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("WITH-COMPILATION-UNIT"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WITH-CONDITION-RESTARTS"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WITH-HASH-TABLE-ITERATOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WITH-INPUT-FROM-STRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WITH-OPEN-FILE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WITH-OPEN-STREAM"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WITH-OUTPUT-TO-STRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WITH-PACKAGE-ITERATOR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WITH-SIMPLE-RESTART"
    (:symbol
        :package "HOST"
	:import-from "CONDITIONS"
	)
    )

("WITH-SLOTS"
    (:symbol
        :package "HOST-CLOS"
	:import-from "CLOS"
	:export ("HOST-CLOS" "HOST")
	)
    )

("WITH-STANDARD-IO-SYNTAX"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WRITE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WRITE-BYTE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WRITE-CHAR"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WRITE-LINE"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WRITE-STRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("WRITE-TO-STRING"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("Y-OR-N-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("YES-OR-NO-P"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

("ZEROP"
    (:symbol
        :package "HOST"
	:import-from :lisp
	)
    )

;;;; Vendor-specific extensions

;;; Lucid extensions

("ASSQ"
    (:symbol
	:package "HOSTX"
	:import-from "ZETALISP"
	)
    )

("CD"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("DEF-FOREIGN-CALLABLE"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("DEF-FOREIGN-FUNCTION"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("DELQ"
    (:symbol
	:package "HOSTX"
	:import-from "ZETALISP"
	)
    )

("LIST-NREVERSE"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("LIST-REVERSE"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("MEMQ"
    (:symbol
	:package "HOSTX"
	:import-from "ZETALISP"
	)
    )

("PWD"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("QUIT"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("SHELL"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("STRING-APPEND"
    (:symbol
	:package "HOSTX"
	:import-from "SCL"
	)
    )

("WITH-DYNAMIC-AREA"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("WITH-STATIC-AREA"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("XOR"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

;;; Allegro extensions

;;; Allegro extensions package

("GETENV"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

;;; Allegro FF (foreign-functions) package

("CHAR*-TO-STRING"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("DEFCSTRUCT"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("DEFFOREIGN-LIST"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("STRING-TO-CHAR*"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

;;; Gold Hill extensions

("%POINTER"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("%SYSINT"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("+&"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("/&"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("ARRAY-LENGTH"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("CLOSE-ALL-FILES"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("COPY-ARRAY-CONTENTS"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("DOS"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("EXIT"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("FILE-INFO"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("FLATSIZE"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("IFN"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("LSH"
    (:symbol
	:package "HOSTX"
	:import-from "SCL"
	)
    )

("MAKE-WINDOW-STREAM"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("NCONS"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("NEQ"
    (:symbol
	:package "HOSTX"
	:import-from "SCL"
	)
    )

("NEQL"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("RPLACB"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("SEND-FILE"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("SEND-WINDOW"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("STREAM-DEFAULT-HANDLER"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

("STRING-SEARCH"
    (:symbol
	:package "HOSTX"
	:import-from nil
	)
    )

)

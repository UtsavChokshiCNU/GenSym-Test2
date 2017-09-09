;;; -*- Mode: Lisp -*-
;;;
;;; lucid-5-syms.lisp -- HOST package database for lucid 5
;;;
;;; author :  Sandra Loosemore (from original by Kim Barrett)
;;; date   :  30 Jan 1991
;;;
;;; Copyright (c) 1991, Chestnut Software Inc.
;;; 

#-LCL5.0
#.(error "Attempting to use incorrect host database.
This file is for Lucid Common Lisp version 5.0.")

(in-package "HOST-IMPLEMENTATION")

(himpl:note-rcs-revision
 "$Source: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/chestnut/src/trans/host/lucid-5-syms.lisp,v $"
 "$Revision: 1.2 $"
 "$Date: 2007-05-21 21:57:22 $")

(himpl:define-symbols :lisp nil

;;; Symbols with the comment NON-ANSI-STANDARD-CLOS are symbols from a list
;;; agreed upon between Symbolics an Lucid as being MOP extensions exported
;;; from the CLOS package.  They are listed in a message from Moon to the 
;;; Common-Lisp-Object-System@mcc.com, dated 4-March-90.

("&ALLOW-OTHER-KEYS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("&AUX"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("&BODY"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("&ENVIRONMENT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("&KEY"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("&OPTIONAL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("&REST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("&WHOLE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("**"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("***"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*BREAK-ON-SIGNALS*"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("*COMPILE-FILE-PATHNAME*"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("*COMPILE-FILE-TRUENAME*"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("*COMPILE-PRINT*"
    (:symbol
        :package "HOST"
	:import-from "USER"
	)
    )

("*COMPILE-VERBOSE*"
    (:symbol
        :package "HOST"
	:import-from "USER"
	)
    )

("*DEBUG-IO*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*DEBUGGER-HOOK*"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("*DEFAULT-PATHNAME-DEFAULTS*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*ERROR-OUTPUT*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*FEATURES*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*GENSYM-COUNTER*"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("*LOAD-PATHNAME*"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("*LOAD-PRINT*"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("*LOAD-TRUENAME*"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("*LOAD-VERBOSE*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*MACROEXPAND-HOOK*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
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
	:import-from "LISP"
	)
    )

("*PRINT-ARRAY*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*PRINT-BASE*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*PRINT-CASE*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*PRINT-CIRCLE*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*PRINT-ESCAPE*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*PRINT-GENSYM*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*PRINT-LENGTH*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*PRINT-LEVEL*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*PRINT-LINES*"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("*PRINT-MISER-WIDTH*"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("*PRINT-PPRINT-DISPATCH*"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("*PRINT-PRETTY*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*PRINT-RADIX*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*PRINT-READABLY*"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("*PRINT-RIGHT-MARGIN*"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("*QUERY-IO*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*RANDOM-STATE*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*READ-BASE*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*READ-DEFAULT-FLOAT-FORMAT*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*READ-EVAL*"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("*READ-SUPPRESS*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*READTABLE*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*STANDARD-INPUT*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*STANDARD-OUTPUT*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*TERMINAL-IO*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("*TRACE-OUTPUT*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("+"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("++"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("+++"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("-"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("/"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("//"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("///"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("/="
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("1+"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("1-"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("<"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("<="
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("="
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

(">"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

(">="
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ABORT"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("ABS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ACONS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ACOS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ACOSH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ADD-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("ADJOIN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ADJUST-ARRAY"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ADJUSTABLE-ARRAY-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ALLOCATE-INSTANCE"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("ALPHA-CHAR-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ALPHANUMERICP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("AND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("APPEND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("APPLY"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("APROPOS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("APROPOS-LIST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("AREF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ARITHMETIC-ERROR"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("ARITHMETIC-ERROR-OPERANDS"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("ARITHMETIC-ERROR-OPERATION"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("ARRAY"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ARRAY-DIMENSION"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ARRAY-DIMENSION-LIMIT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ARRAY-DIMENSIONS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
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
	:import-from "LISP"
	)
    )

("ARRAY-HAS-FILL-POINTER-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ARRAY-IN-BOUNDS-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ARRAY-RANK"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ARRAY-RANK-LIMIT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ARRAY-ROW-MAJOR-INDEX"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ARRAY-TOTAL-SIZE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ARRAY-TOTAL-SIZE-LIMIT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ARRAYP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ASH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ASIN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ASINH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ASSERT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ASSOC"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ASSOC-IF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ASSOC-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ATAN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ATANH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ATOM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("AUGMENT-ENVIRONMENT"
    (:symbol
        :package "HOSTX"
	:import-from nil
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
	:import-from nil
	)
    )

("BIGNUM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BIT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BIT-AND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BIT-ANDC1"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BIT-ANDC2"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BIT-EQV"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BIT-IOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BIT-NAND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BIT-NOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BIT-NOT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BIT-ORC1"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BIT-ORC2"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BIT-VECTOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BIT-VECTOR-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BIT-XOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BLOCK"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOOLE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOOLE-1"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOOLE-2"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOOLE-AND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOOLE-ANDC1"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOOLE-ANDC2"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOOLE-C1"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOOLE-C2"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOOLE-CLR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOOLE-EQV"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOOLE-IOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOOLE-NAND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOOLE-NOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOOLE-ORC1"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOOLE-ORC2"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOOLE-SET"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOOLE-XOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOTH-CASE-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BOUNDP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BREAK"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BROADCAST-STREAM"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("BROADCAST-STREAM-STREAMS"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("BUILT-IN-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("BUTLAST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BYTE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BYTE-POSITION"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("BYTE-SIZE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CAAAAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CAAADR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CAAAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CAADAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CAADDR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CAADR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CAAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CADAAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CADADR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CADAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CADDAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CADDDR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CADDR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CADR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CALL-ARGUMENTS-LIMIT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CALL-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("CALL-NEXT-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("CAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CASE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CATCH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CCASE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CDAAAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CDAADR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CDAAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CDADAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CDADDR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CDADR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CDAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CDDAAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CDDADR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CDDAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CDDDAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CDDDDR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CDDDR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CDDR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CDR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CEILING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CELL-ERROR"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("CELL-ERROR-NAME"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("CERROR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHANGE-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("CHAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR-CODE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR-CODE-LIMIT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR-DOWNCASE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR-EQUAL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR-GREATERP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR-INT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR-LESSP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR-NAME"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR-NOT-EQUAL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR-NOT-GREATERP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR-NOT-LESSP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR-UPCASE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR/="
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR<"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR<="
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR="
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR>"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHAR>="
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHARACTER"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHARACTERP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CHECK-TYPE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CIS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("CLASS-DEFAULT-INITARGS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("CLASS-DIRECT-DEFAULT-INITARGS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("CLASS-DIRECT-SUBCLASSES"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("CLASS-DIRECT-SUPERCLASSES"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("CLASS-NAME"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("CLASS-OF"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("CLASS-PRECEDENCE-LIST"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("CLASS-PROTOTYPE"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("CLASS-SLOTS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("CLEAR-INPUT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CLEAR-OUTPUT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CLOSE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CLRHASH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CODE-CHAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COERCE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COMPILATION-SPEED"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COMPILE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COMPILE-FILE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COMPILE-FILE-PATHNAME"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("COMPILED-FUNCTION"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COMPILED-FUNCTION-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
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
	:import-from nil
	)
    )

("COMPLEMENT"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("COMPLEX"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COMPLEXP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COMPUTE-APPLICABLE-METHODS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("COMPUTE-EFFECTIVE-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("COMPUTE-RESTARTS"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("CONCATENATE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CONCATENATED-STREAM"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("CONCATENATED-STREAM-STREAMS"
    (:SYMBOL
        :PACKAGE "HOST"
	:IMPORT-FROM nil
	)
    )

("COND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CONDITION"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("CONJUGATE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CONS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CONSP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CONSTANTLY"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("CONSTANTP"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("CONTINUE"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("CONTROL-ERROR"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("COPY-ALIST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COPY-LIST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COPY-PPRINT-DISPATCH"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("COPY-READTABLE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COPY-SEQ"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COPY-STRUCTURE"
    (:symbol
        :package "HOST"
	:import-from "SYSTEM"
	)
    )

("COPY-SYMBOL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COPY-TREE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COSH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COUNT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COUNT-IF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("COUNT-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("CTYPECASE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DEBUG"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("DECF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DECLAIM"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("DECLARATION"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DECLARATION-INFORMATION"
    (:symbol
        :package "HOSTX"
	:import-from nil
	)
    )

("DECLARE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DECODE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DECODE-UNIVERSAL-TIME"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DEFCLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("DEFCONSTANT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DEFGENERIC"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("DEFINE-COMPILER-MACRO"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("DEFINE-CONDITION"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("DEFINE-DECLARATION"
    (:symbol
        :package "HOSTX"
	:import-from nil
	)
    )

("DEFINE-METHOD-COMBINATION"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("DEFINE-MODIFY-MACRO"
    (:symbol
        :package "HOST"
	:import-from "LISP"
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
	:import-from "LISP"
	)
    )

("DEFMACRO"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DEFMETHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("DEFPACKAGE"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("DEFPARAMETER"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DEFSETF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DEFSTRUCT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DEFTYPE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DEFUN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DEFVAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DELETE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DELETE-DUPLICATES"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DELETE-FILE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DELETE-IF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DELETE-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DELETE-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("DENOMINATOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DEPOSIT-FIELD"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DESCRIBE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DESCRIBE-OBJECT"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("DESTRUCTURING-BIND"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("DIGIT-CHAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DIGIT-CHAR-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DIRECTORY"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DIRECTORY-NAMESTRING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DISASSEMBLE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DIVISION-BY-ZERO"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("DO"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DO*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DO-ALL-SYMBOLS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DO-EXTERNAL-SYMBOLS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DO-SYMBOLS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DOCUMENTATION"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("DOLIST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DOTIMES"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DOUBLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DOUBLE-FLOAT-EPSILON"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DOUBLE-FLOAT-NEGATIVE-EPSILON"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DPB"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DRIBBLE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("DYNAMIC-EXTENT"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("ECASE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ECHO-STREAM"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("ECHO-STREAM-INPUT-STREAM"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("ECHO-STREAM-OUTPUT-STREAM"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("ED"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("EIGHTH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ELT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ENCLOSE"
    (:symbol
        :package "HOSTX"
	:import-from nil
	)
    )

("ENCODE-UNIVERSAL-TIME"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("END-OF-FILE"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("ENDP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ENOUGH-NAMESTRING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ENSURE-GENERIC-FUNCTION"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("EQ"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("EQL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("EQUAL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("EQUALP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ERROR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ETYPECASE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("EVAL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("EVAL-WHEN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("EVENP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("EVERY"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("EXP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("EXPORT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("EXPT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
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
	:import-from #+clos nil #-clos "LISP"
	)
    )

("FCEILING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FDEFINITION"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("FFLOOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FIFTH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FILE-AUTHOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FILE-ERROR"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("FILE-ERROR-PATHNAME"
    (:symbol
        :package "HOST"
	:import-from nil    ; not in LCL!?
	)
    )

("FILE-LENGTH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FILE-NAMESTRING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FILE-POSITION"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FILE-STREAM"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("FILE-STRING-LENGTH"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("FILE-WRITE-DATE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FILL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FILL-POINTER"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FIND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FIND-ALL-SYMBOLS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FIND-CLASS"
    (:symbol
        :package "HOST-CLOS"
	;; Avoid bug in LCL4.0.  This name is instead homed in HOST and
	;; defined in terms of the implementation's definition.
	:import-from nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("FIND-IF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FIND-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FIND-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("FIND-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FIND-RESTART"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("FIND-SYMBOL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FINISH-OUTPUT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FIRST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FIXNUM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FLET"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FLOAT-DIGITS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FLOAT-PRECISION"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FLOAT-RADIX"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FLOAT-SIGN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FLOATING-POINT-INEXACT"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("FLOATING-POINT-INVALID-OPERATION"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("FLOATING-POINT-OVERFLOW"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("FLOATING-POINT-UNDERFLOW"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("FLOATP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FLOOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FMAKUNBOUND"
    (:symbol
        :package "HOST"
	:import-from #+clos nil #-clos "LISP"
	)
    )

("FORCE-OUTPUT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FORMAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FORMATTER"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("FORWARD-REFERENCED-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("FOURTH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FRESH-LINE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FROUND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FTRUNCATE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FTYPE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FUNCALL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FUNCALLABLE-STANDARD-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("FUNCTION"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("FUNCTION-INFORMATION"
    (:symbol
        :package "HOSTX"
	:import-from nil
	)
    )

("FUNCTION-KEYWORDS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("FUNCTION-LAMBDA-EXPRESSION"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("FUNCTIONP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("GCD"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("GENERIC-FLET"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("GENERIC-FUNCTION"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("GENERIC-FUNCTION-ARGUMENT-PRECEDENCE-ORDER"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("GENERIC-FUNCTION-DECLARATIONS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("GENERIC-FUNCTION-INITIAL-METHODS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("GENERIC-FUNCTION-LAMBDA-LIST"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("GENERIC-FUNCTION-METHOD-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("GENERIC-FUNCTION-METHOD-COMBINATION"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("GENERIC-FUNCTION-METHODS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("GENERIC-FUNCTION-NAME"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("GENERIC-LABELS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("GENSYM"
    (:symbol
        :package "HOST"
	;; Implement this ourselves, due to different semantics between CLtL
	;; and ANSI definitions.
	:import-from nil
	)
    )

("GENTEMP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("GET"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("GET-DECODED-TIME"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("GET-DISPATCH-MACRO-CHARACTER"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("GET-INTERNAL-REAL-TIME"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("GET-INTERNAL-RUN-TIME"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("GET-MACRO-CHARACTER"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("GET-OUTPUT-STREAM-STRING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("GET-PROPERTIES"
    (:symbol
        :package "HOST"
	:import-from "LISP"
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
	:import-from "LISP"
	)
    )

("GET-SETF-METHOD-MULTIPLE-VALUE"
    (:symbol
        :package "HOSTX"
	:import-from "LISP"
	)
    )

("GET-UNIVERSAL-TIME"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("GETF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("GETHASH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("GO"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("GRAPHIC-CHAR-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("HANDLER-BIND"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("HANDLER-CASE"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("HASH-TABLE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("HASH-TABLE-COUNT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("HASH-TABLE-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("HASH-TABLE-REHASH-SIZE"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("HASH-TABLE-REHASH-THRESHOLD"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("HASH-TABLE-SIZE"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("HASH-TABLE-TEST"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("HOST-NAMESTRING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("IDENTITY"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("IF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
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
	:import-from "LISP"
	)
    )

("IGNORE-ERRORS"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("IMAGPART"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("IMPORT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("IN-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("INCF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("INITIALIZE-INSTANCE"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("INLINE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("INPUT-STREAM-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("INSPECT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("INTEGER"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("INTEGER-DECODE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("INTEGER-LENGTH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("INTEGERP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("INTERACTIVE-STREAM-P"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("INTERN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("INTERNAL-TIME-UNITS-PER-SECOND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("INTERSECTION"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("INVALID-METHOD-ERROR"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("INVOKE-DEBUGGER"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("INVOKE-RESTART"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("INVOKE-RESTART-INTERACTIVELY"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("ISQRT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("KEYWORD"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("KEYWORDP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LABELS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LAMBDA"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LAMBDA-LIST-KEYWORDS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LAMBDA-PARAMETERS-LIMIT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LAST"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("LCM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LDB"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LDB-TEST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LDIFF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LEAST-NEGATIVE-DOUBLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LEAST-NEGATIVE-LONG-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LEAST-NEGATIVE-NORMALIZED-DOUBLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("LEAST-NEGATIVE-NORMALIZED-LONG-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("LEAST-NEGATIVE-NORMALIZED-SHORT-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("LEAST-NEGATIVE-NORMALIZED-SINGLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("LEAST-NEGATIVE-SHORT-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LEAST-NEGATIVE-SINGLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LEAST-POSITIVE-DOUBLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LEAST-POSITIVE-LONG-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LEAST-POSITIVE-NORMALIZED-DOUBLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("LEAST-POSITIVE-NORMALIZED-LONG-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("LEAST-POSITIVE-NORMALIZED-SHORT-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("LEAST-POSITIVE-NORMALIZED-SINGLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("LEAST-POSITIVE-SHORT-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LEAST-POSITIVE-SINGLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LENGTH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LET"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LET*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LISP-IMPLEMENTATION-TYPE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LISP-IMPLEMENTATION-VERSION"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LIST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LIST*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LIST-ALL-PACKAGES"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LIST-LENGTH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LISTEN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LISTP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOAD"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOAD-LOGICAL-PATHNAME-TRANSLATIONS"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("LOAD-TIME-VALUE"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("LOCALLY"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOG"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOGAND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOGANDC1"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOGANDC2"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOGBITP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOGCOUNT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOGEQV"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOGICAL-PATHNAME"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("LOGICAL-PATHNAME-TRANSLATIONS"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("LOGIOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOGNAND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOGNOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOGNOT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOGORC1"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOGORC2"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOGTEST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOGXOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LONG-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LONG-FLOAT-EPSILON"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LONG-FLOAT-NEGATIVE-EPSILON"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LONG-SITE-NAME"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOOP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("LOOP-FINISH"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("LOWER-CASE-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MACHINE-INSTANCE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MACHINE-TYPE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MACHINE-VERSION"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MACRO-FUNCTION"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MACROEXPAND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MACROEXPAND-1"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MACROLET"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAKE-ARRAY"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAKE-BROADCAST-STREAM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAKE-CONCATENATED-STREAM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAKE-CONDITION"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("MAKE-DISPATCH-MACRO-CHARACTER"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAKE-ECHO-STREAM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAKE-HASH-TABLE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAKE-INSTANCE"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("MAKE-INSTANCES-OBSOLETE"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("MAKE-LIST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAKE-LOAD-FORM"
    (:symbol
        :package "HOST-CLOS"
	;; Avoid a `bug' in that this symbol is not yet present in the CLOS
	;; package because it has not yet been implemented in version 4.0.
	:import-from nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("MAKE-LOAD-FORM-SAVING-SLOTS"
    (:symbol
        :package "HOST-CLOS"
	;; Avoid a `bug' in that this symbol is not yet present in the CLOS
	;; package because it has not yet been implemented in version 4.0.
	:import-from nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("MAKE-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("MAKE-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
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
	:import-from "LISP"
	)
    )

("MAKE-SEQUENCE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAKE-STRING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAKE-STRING-INPUT-STREAM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAKE-STRING-OUTPUT-STREAM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAKE-SYMBOL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAKE-SYNONYM-STREAM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAKE-TWO-WAY-STREAM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAKUNBOUND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAP-INTO"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("MAPC"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAPCAN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAPCAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAPCON"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAPHASH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAPL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAPLIST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MASK-FIELD"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MAX"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MEMBER"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MEMBER-IF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MEMBER-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MERGE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MERGE-PATHNAMES"
    (:symbol
        :package "HOST"
	:import-from "HOST-IMPLEMENTATION"
	)
    )

("METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("METHOD-COMBINATION"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("METHOD-COMBINATION-ERROR"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("METHOD-FUNCTION"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("METHOD-GENERIC-FUNCTION"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("METHOD-LAMBDA-LIST"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("METHOD-QUALIFIERS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("METHOD-SLOT-NAME"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("METHOD-SPECIALIZERS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("MIN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MINUSP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MISMATCH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MOD"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MOST-NEGATIVE-DOUBLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MOST-NEGATIVE-FIXNUM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MOST-NEGATIVE-LONG-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MOST-NEGATIVE-SHORT-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MOST-NEGATIVE-SINGLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MOST-POSITIVE-DOUBLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MOST-POSITIVE-FIXNUM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MOST-POSITIVE-LONG-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MOST-POSITIVE-SHORT-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MOST-POSITIVE-SINGLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MUFFLE-WARNING"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("MULTIPLE-VALUE-BIND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MULTIPLE-VALUE-CALL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MULTIPLE-VALUE-LIST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MULTIPLE-VALUE-PROG1"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MULTIPLE-VALUE-SETQ"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("MULTIPLE-VALUES-LIMIT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NAME-CHAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NAMESTRING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NBUTLAST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NCONC"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NEXT-METHOD-P"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("NIL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NINTERSECTION"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NINTH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NO-APPLICABLE-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("NO-NEXT-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("NOT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NOTANY"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NOTEVERY"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NOTINLINE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NRECONC"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NREVERSE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NSET-DIFFERENCE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NSET-EXCLUSIVE-OR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NSTRING-CAPITALIZE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NSTRING-DOWNCASE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NSTRING-UPCASE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NSUBLIS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NSUBST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NSUBST-IF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NSUBST-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NSUBSTITUTE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NSUBSTITUTE-IF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NSUBSTITUTE-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NTH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NTH-VALUE"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("NTHCDR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NULL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NUMBER"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NUMBERP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NUMERATOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("NUNION"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ODDP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("OPEN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("OPEN-STREAM-P"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("OPTIMIZE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("OR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("OTHERWISE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("OUTPUT-STREAM-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PACKAGE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PACKAGE-ERROR"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("PACKAGE-ERROR-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("PACKAGE-NAME"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PACKAGE-NICKNAMES"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PACKAGE-SHADOWING-SYMBOLS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PACKAGE-USE-LIST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PACKAGE-USED-BY-LIST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PACKAGEP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PAIRLIS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PARSE-ERROR"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("PARSE-INTEGER"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PARSE-MACRO"
    (:symbol
        :package "HOSTX"
	:import-from nil
	)
    )

("PARSE-NAMESTRING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PATHNAME"
    (:symbol
        :package "HOST"
	:import-from "LISP"
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
	:import-from nil
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
	:import-from "LISP"
	)
    )

("PEEK-CHAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PHASE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PI"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PLUSP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("POP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("POSITION"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("POSITION-IF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("POSITION-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PPRINT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PPRINT-DISPATCH"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("PPRINT-EXIT-IF-LIST-EXHAUSTED"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("PPRINT-FILL"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("PPRINT-INDENT"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("PPRINT-LINEAR"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("PPRINT-LOGICAL-BLOCK"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("PPRINT-NEWLINE"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("PPRINT-POP"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("PPRINT-TAB"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("PPRINT-TABULAR"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("PRIN1"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PRIN1-TO-STRING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PRINC"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PRINC-TO-STRING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PRINT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PRINT-NOT-READABLE"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("PRINT-NOT-READABLE-OBJECT"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("PRINT-OBJECT"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("PRINT-UNREADABLE-OBJECT"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("PROBE-FILE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PROCLAIM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PROG"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PROG*"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PROG1"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PROG2"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PROGN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PROGRAM-ERROR"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("PROGV"
    (:symbol
        :package "HOST"
	:import-from "LISP"
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
	:import-from "LISP"
	)
    )

("PSETQ"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PUSH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("PUSHNEW"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("QUOTE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("RANDOM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("RANDOM-STATE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("RANDOM-STATE-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("RASSOC"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("RASSOC-IF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("RASSOC-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("RATIO"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("RATIONAL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("RATIONALIZE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("RATIONALP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("READ"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )


("READ-BYTE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("READ-CHAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("READ-CHAR-NO-HANG"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("READ-DELIMITED-LIST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("READ-FROM-STRING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("READ-LINE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("READ-PRESERVING-WHITESPACE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
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
	:import-from "LISP"
	)
    )

("READTABLE-CASE"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("READTABLEP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("REAL"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("REALP"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("REALPART"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("REDUCE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("REINITIALIZE-INSTANCE"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("REM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("REMF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("REMHASH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("REMOVE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("REMOVE-DUPLICATES"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("REMOVE-IF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("REMOVE-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("REMOVE-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("REMPROP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("RENAME-FILE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("RENAME-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("REPLACE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
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
	:import-from "LISP"
	)
    )

("RESTART"
    (:symbol
        :package "HOST"
	:import-from nil    ; not in LCL!?
	)
    )

("RESTART-BIND"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("RESTART-CASE"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("RESTART-NAME"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("RETURN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("RETURN-FROM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("REVAPPEND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("REVERSE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ROOM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ROTATEF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ROUND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ROW-MAJOR-AREF"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("RPLACA"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("RPLACD"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SAFETY"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SATISFIES"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SBIT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SCALE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SCHAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SEARCH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SECOND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SEQUENCE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SERIOUS-CONDITION"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("SET"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SET-DIFFERENCE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SET-DISPATCH-MACRO-CHARACTER"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SET-EXCLUSIVE-OR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SET-MACRO-CHARACTER"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SET-PPRINT-DISPATCH"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("SET-SYNTAX-FROM-CHAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SETF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	:export ("HOST" "HOST-CLOS")
	)
    )

("SETQ"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SEVENTH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SHADOW"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SHADOWING-IMPORT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SHARED-INITIALIZE"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("SHIFTF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SHORT-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SHORT-FLOAT-EPSILON"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SHORT-FLOAT-NEGATIVE-EPSILON"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SHORT-SITE-NAME"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SIGNAL"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("SIGNED-BYTE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SIGNUM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SIMPLE-ARRAY"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SIMPLE-BASE-STRING"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("SIMPLE-BIT-VECTOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SIMPLE-BIT-VECTOR-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SIMPLE-CONDITION"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("SIMPLE-CONDITION-FORMAT-ARGUMENTS"
    (:symbol
        :package "HOST"
	:import-from "LCL"
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
	:import-from "LCL"
	)
    )

("SIMPLE-STRING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SIMPLE-STRING-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SIMPLE-TYPE-ERROR"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("SIMPLE-VECTOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SIMPLE-VECTOR-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SIMPLE-WARNING"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("SIN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SINGLE-FLOAT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SINGLE-FLOAT-EPSILON"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SINGLE-FLOAT-NEGATIVE-EPSILON"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SINH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SIXTH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SLEEP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SLOT-BOUNDP"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("SLOT-BOUNDP-USING-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION-ALLOCATION"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION-INITARGS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION-INITFORM"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION-INITFUNCTION"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION-NAME"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION-READERS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION-TYPE"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-DEFINITION-WRITERS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-EXISTS-P"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("SLOT-EXISTS-P-USING-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-MAKUNBOUND"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("SLOT-MAKUNBOUND-USING-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SLOT-MISSING"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("SLOT-UNBOUND"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("SLOT-VALUE"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("SLOT-VALUE-USING-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("SOFTWARE-TYPE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SOFTWARE-VERSION"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SOME"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SORT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SPACE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SPECIAL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SPECIAL-FORM-P"
    (:symbol
        :package "HOSTX"
	:import-from "LISP"
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
;        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
;	;; NON-ANSI-STANDARD-CLOS
;	)
;    )

;;; Removed pending discussion on common-lisp-object-system mailing list.
;("SPECIALIZER-DIRECT-METHODS"
;    (:symbol
;        :package "HOST-CLOS"
;	:import-from
;        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
;	;; NON-ANSI-STANDARD-CLOS
;	)
;    )

("SPEED"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SQRT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STABLE-SORT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STANDARD"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("STANDARD-ACCESSOR-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("STANDARD-CHAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STANDARD-CHAR-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STANDARD-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("STANDARD-GENERIC-FUNCTION"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("STANDARD-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("STANDARD-OBJECT"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("STANDARD-READER-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("STANDARD-SLOT-DEFINITION"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("STANDARD-WRITER-METHOD"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	;; NON-ANSI-STANDARD-CLOS
	)
    )

("STEP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STORAGE-CONDITION"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("STORE-VALUE"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("STREAM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STREAM-ELEMENT-TYPE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STREAM-ERROR"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("STREAM-ERROR-STREAM"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("STREAM-EXTERNAL-FORMAT"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("STREAMP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRING-CAPITALIZE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
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
	:import-from "LISP"
	)
    )

("STRING-EQUAL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRING-GREATERP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRING-LEFT-TRIM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRING-LESSP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRING-NOT-EQUAL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRING-NOT-GREATERP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRING-NOT-LESSP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRING-RIGHT-TRIM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRING-STREAM"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("STRING-TRIM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRING-UPCASE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRING/="
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRING<"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRING<="
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRING="
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRING>"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRING>="
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRINGP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRUCTURE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("STRUCTURE-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("STRUCTURE-OBJECT"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("STYLE-WARNING"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("SUBLIS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SUBSEQ"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SUBSETP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SUBST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SUBST-IF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SUBST-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SUBSTITUTE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SUBSTITUTE-IF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SUBSTITUTE-IF-NOT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
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
	:import-from "LISP"
	)
    )

("SXHASH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SYMBOL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SYMBOL-FUNCTION"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SYMBOL-MACROLET"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("SYMBOL-NAME"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SYMBOL-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SYMBOL-PLIST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SYMBOL-VALUE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SYMBOLP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("SYNONYM-STREAM"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("SYNONYM-STREAM-SYMBOL"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("T"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("TAGBODY"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("TAILP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("TAN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("TANH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("TENTH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("TERPRI"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("THE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("THIRD"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("THROW"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("TIME"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("TRACE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("TRANSLATE-LOGICAL-PATHNAME"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("TRANSLATE-PATHNAME"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("TREE-EQUAL"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("TRUENAME"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("TRUNCATE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("TWO-WAY-STREAM"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("TWO-WAY-STREAM-INPUT-STREAM"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("TWO-WAY-STREAM-OUTPUT-STREAM"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("TYPE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("TYPE-ERROR"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("TYPE-ERROR-DATUM"
    (:symbol
        :package "HOST"
	:import-from nil    ; not in LCL!?
	)
    )

("TYPE-ERROR-EXPECTED-TYPE"
    (:symbol
        :package "HOST"
	:import-from nil    ; not in LCL!?
	)
    )

("TYPE-OF"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("TYPE-SPECIFIER-P"
    (:symbol
        :package "HOSTX"
	:import-from "LCL"
	)
    )

("TYPECASE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
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
	:import-from nil
	)
    )

("UNBOUND-SLOT-INSTANCE"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("UNBOUND-VARIABLE"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("UNDEFINED-FUNCTION"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("UNEXPORT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("UNINTERN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("UNION"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("UNLESS"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("UNREAD-CHAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("UNSIGNED-BYTE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("UNTRACE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("UNUSE-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("UNWIND-PROTECT"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("UPDATE-INSTANCE-FOR-DIFFERENT-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("UPDATE-INSTANCE-FOR-REDEFINED-CLASS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("UPGRADED-ARRAY-ELEMENT-TYPE"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("UPGRADED-COMPLEX-PART-TYPE"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("UPPER-CASE-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("USE-PACKAGE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("USE-VALUE"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("USER-HOMEDIR-PATHNAME"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("VALUES"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("VALUES-LIST"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("VARIABLE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("VARIABLE-INFORMATION"
    (:symbol
        :package "HOSTX"
	:import-from nil
	)
    )

("VECTOR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("VECTOR-POP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("VECTOR-PUSH"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("VECTOR-PUSH-EXTEND"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("VECTORP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("WARN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("WARNING"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("WHEN"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("WILD-PATHNAME-P"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("WITH-ACCESSORS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("WITH-COMPILATION-UNIT"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("WITH-CONDITION-RESTARTS"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("WITH-HASH-TABLE-ITERATOR"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("WITH-INPUT-FROM-STRING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("WITH-OPEN-FILE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("WITH-OPEN-STREAM"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("WITH-OUTPUT-TO-STRING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("WITH-PACKAGE-ITERATOR"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("WITH-SIMPLE-RESTART"
    (:symbol
        :package "HOST"
	:import-from "LCL"
	)
    )

("WITH-SLOTS"
    (:symbol
        :package "HOST-CLOS"
	:import-from
        #+translator-supports-clos "CLOS" #-translator-supports-clos nil
	:export ("HOST-CLOS" "HOST")
	)
    )

("WITH-STANDARD-IO-SYNTAX"
    (:symbol
        :package "HOST"
	:import-from nil
	)
    )

("WRITE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("WRITE-BYTE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("WRITE-CHAR"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("WRITE-LINE"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("WRITE-STRING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("WRITE-TO-STRING"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("Y-OR-N-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("YES-OR-NO-P"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

("ZEROP"
    (:symbol
        :package "HOST"
	:import-from "LISP"
	)
    )

;;;; Vendor-specific extensions

;;; Lucid extensions

("ASSQ"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("CD"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("COPY-FOREIGN-POINTER"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("DEF-FOREIGN-CALLABLE"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("DEF-FOREIGN-FUNCTION"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("DEF-FOREIGN-STRUCT"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("DEF-FOREIGN-SYNONYM-TYPE"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("DEFINED-FOREIGN-TYPE-P"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("DELQ"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("FOREIGN-AREF"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("FOREIGN-POINTER"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("FOREIGN-POINTER-ADDRESS"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("FOREIGN-POINTER-P"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("FOREIGN-POINTER-TYPE"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("FOREIGN-SIZE-OF"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("FOREIGN-STRING-VALUE"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("FOREIGN-TYPE"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID"
	)
    )

("FOREIGN-TYPE-SIZE"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("FOREIGN-TYPE-REMAINDER"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("FOREIGN-TYPE-MODULUS"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("FOREIGN-TYPE-NAME"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID"
	)
    )

("FOREIGN-TYPEP"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("FOREIGN-VALUE"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("FOREIGN-VARIABLE-ADDRESS"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("FOREIGN-VARIABLE-POINTER"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("FREE-FOREIGN-POINTER"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("LIST-NREVERSE"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("LIST-REVERSE"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("MAKE-FOREIGN-POINTER"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("MALLOC-FOREIGN-POINTER"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("MEMQ"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("PWD"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("QUIT"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("SHELL"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("STRING-APPEND"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("STATIONARY-OBJECT-P"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("TYPED-FOREIGN-AREF"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("WITH-DYNAMIC-AREA"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("WITH-STATIC-AREA"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
	)
    )

("XOR"
    (:symbol
	:package "HOSTX"
	:import-from "LUCID-COMMON-LISP"
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
	:import-from nil
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
	:import-from nil
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

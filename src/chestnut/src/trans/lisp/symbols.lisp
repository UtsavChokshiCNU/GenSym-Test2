;;; -*- Mode: Lisp; Package: HOST; Syntax: Common-Lisp -*-
;;;
;;; symbols.lisp -- database of symbols that exist in the run-time system
;;;
;;; author :  Sandra Loosemore
;;; date   :  10 Oct 1990
;;;

(in-package "HOST")

;;; Having the close parens on lines by themselves just makes it easier to
;;; edit the database (adding and removing fields, in particular).  For
;;; one thing, not having to worry about parens in random places has made
;;; it much easier for me to use emacs keyboard macros to make all the
;;; global changes in the database lately.
;;;   				-- Sandra Loosemore, 9 April 1991

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/symbols.lisp,v $"
 "$Revision: 1.16 $"
 "$Date: 2009/08/10 00:00:00 $")

(himpl:define-symbols :host t


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Symbols in the TCL package
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

("&ALLOW-OTHER-KEYS"
    (:symbol
        :package "TCL"
	)
    (:lambda-list-keyword)
    )

("&AUX"
    (:symbol
        :package "TCL"
	)
    (:lambda-list-keyword)
    )

("&BODY"
    (:symbol
        :package "TCL"
	)
    (:lambda-list-keyword)
    )

("&ENVIRONMENT"
    (:symbol
        :package "TCL"
	)
    (:lambda-list-keyword)
    )

("&KEY"
    (:symbol
        :package "TCL"
	)
    (:lambda-list-keyword)
    )

("&OPTIONAL"
    (:symbol
        :package "TCL"
	)
    (:lambda-list-keyword)
    )

("&REST"
    (:symbol
        :package "TCL"
	)
    (:lambda-list-keyword)
    )

("&WHOLE"
    (:symbol
        :package "TCL"
	)
    (:lambda-list-keyword)
    )

("*"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (&rest numbers)
	:entry-name "timesn"		;BB - was "times"
	:object-name "Ftimes"
	:argument-types (&rest number)
	:return-type number
	)
    (:random-syntax)
    (:variable
        :variable-name "Star"
        :return-type t
	)
    )

("**"
    (:symbol
        :package "TCL"
	)
    (:variable
        :variable-name "Star_star"
        :return-type t
	)
    )

("***"
    (:symbol
        :package "TCL"
	;; Name mapper doesn't deal with this one very well.  The outer pair
	;; of stars get stripped off, and the result then collides with the
	;; name for "*", so a package prefix gets inserted.
	:symbol-name "Qstar_star_star"
	)
    (:variable
        :variable-name "Star_star_star"
        :return-type t
	)
    )

("*BREAK-ON-SIGNALS*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type t
	;;:unsupported t
	)
    )

("*COMPILE-FILE-PATHNAME*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type t
	;;:unsupported t
	)
    )

("*COMPILE-FILE-TRUENAME*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type t
	;;:unsupported t
	)
    )

("*COMPILE-PRINT*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type t
	;;:unsupported t
	)
    )

("*COMPILE-VERBOSE*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type t
	;;:unsupported t
	)
    )

("*DEBUG-IO*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type stream
	;; :initial-value standard-stream
	)
    )

("*DEBUGGER-HOOK*"
    (:symbol
        :package "TCL"
	)
    (:variable
        ;;:unsupported t
        :return-type t
	)
    )

("*DEFAULT-PATHNAME-DEFAULTS*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type (or pathname string)
	;; :initial-value (pathname "")
	)
    )

("*ERROR-OUTPUT*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type stream
	;; :initial-value standard-stream
	)
    )

("*FEATURES*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type list
	;; :initial-value nil
	)
    )

("*GENSYM-COUNTER*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type integer
	;; :initial-value 0
	)
    )

("*LOAD-PATHNAME*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type t
	)
    )

("*LOAD-PRINT*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type t
	)
    )

("*LOAD-TRUENAME*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type t
	)
    )

("*LOAD-VERBOSE*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type t
	)
    )

("*MACROEXPAND-HOOK*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type t
	)
    )

;;; Returned to language 12/91
("*MODULES*"
    (:symbol
         :package "TCL"
	 )
    (:variable
         :return-type t
	 ;; Fix core/bindsyms, then remove next line
         ;;:unsupported t
	 )
    )

("*PACKAGE*"
    (:symbol
        :package "TCL"
	:symbol-name "Qpackage_variable"
	)
    (:variable
        :return-type package
	;; :initial-value user-package
	)
    )

("*PRINT-ARRAY*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type t
        ;; :initial-value t
	)
    )

("*PRINT-BASE*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type fixnum
	;; :initial-value 10
	)
    )

("*PRINT-CASE*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type symbol
	;; :initial-value :upcase
	)
    )

("*PRINT-CIRCLE*"
    (:symbol
        :package "TCL"
	)
    (:variable
	;;:unsupported t
        :return-type t
	;; :initial-value nil
	)
    )

("*PRINT-ESCAPE*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type t
	;; :initial-value t
	)
    )

("*PRINT-GENSYM*"
    (:symbol
        :package "TCL"
	)
    (:variable
	;;:unsupported t
        :return-type t
	;; :initial-value t
	)
    )

("*PRINT-LENGTH*"
    (:symbol
        :package "TCL"
	)
    (:variable
	;;:unsupported t
        :return-type (or null integer)
	;; :initial-value nil
	)
    )

("*PRINT-LEVEL*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type (or null integer)
	;; :initial-value nil
	)
    )

("*PRINT-LINES*"
    (:symbol
        :package "TCL"
	)
    (:variable
	;;:unsupported t
        :return-type t
	)
    )

("*PRINT-MISER-WIDTH*"
    (:symbol
        :package "TCL"
	)
    (:variable
	;;:unsupported t
        :return-type t
	)
    )

("*PRINT-PPRINT-DISPATCH*"
    (:symbol
        :package "TCL"
	)
    (:variable
	;;:unsupported t
        :return-type t
	)
    )

("*PRINT-PRETTY*"
    (:symbol
        :package "TCL"
	)
    (:variable
	;;:unsupported t
        :return-type t
	;; :initial-value nil
	)
    )

("*PRINT-RADIX*"
    (:symbol
        :package "TCL"
	)
    (:variable
	;;:unsupported t
        :return-type t
        ;; :initial-value nil
	)
    )

("*PRINT-READABLY*"
    (:symbol
        :package "TCL"
	)
    (:variable
	;;:unsupported t
        :return-type t
	;; :initial-value nil
	)
    )

("*PRINT-RIGHT-MARGIN*"
    (:symbol
        :package "TCL"
	)
    (:variable
	;;:unsupported t
        :return-type t
	)
    )

("*QUERY-IO*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type stream
	;; :initial-value standard-stream
	)
    )

("*RANDOM-STATE*"
    (:symbol
        :package "TCL"
	:symbol-name "Qrandom_state_variable"
	)
    (:variable
        :return-type random-state
	;; :initial-value (make-random-state t)
	)
    )

("*READ-BASE*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type fixnum
	;; :initial-value 10
	)
    )

("*READ-DEFAULT-FLOAT-FORMAT*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type symbol
	;; :initial-value 'single-float
	)
    )

("*READ-EVAL*"
    (:symbol
        :package "TCL"
	)
    (:variable
	;;:unsupported t
        :return-type t
	;; :initial-value t
	)
    )

("*READ-SUPPRESS*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type t
	;; :initial-value nil
	)
    )

("*READTABLE*"
    (:symbol
        :package "TCL"
	:symbol-name "Qreadtable_variable"
	)
    (:variable
        :return-type readtable
	;; :initial-value common-lisp-readtable
	)
    )

("*STANDARD-INPUT*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type stream
	;; :initial-value standard-stream
	)
    )

("*STANDARD-OUTPUT*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type stream
	;; :initial-value standard-stream
	)
    )

("*TERMINAL-IO*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type stream
	;; :initial-value standard-stream
	)
    )

("*TRACE-OUTPUT*"
    (:symbol
        :package "TCL"
	)
    (:variable
        :return-type stream
	;; :initial-value standard-stream
	)
    )

("+"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (&rest numbers)
	:entry-name "addn"		;BB - was "plus"
	:object-name "Fadd"		;BB - was "Fplus"
	:argument-types (&rest number)
	:return-type number
	)
    (:method-combination)
    (:variable
        :variable-name "Plus"
        :return-type t
	)
    )

("++"
    (:symbol
        :package "TCL"
	)
    (:variable
        :variable-name "Plus_plus"
        :return-type t
	)
    )

("+++"
    (:symbol
        :package "TCL"
	)
    (:variable
        :variable-name "Plus_plus_plus"
        :return-type t
	)
    )

("-"
    (:symbol
        :package "TCL"
	:symbol-name "Qminus"
	)
    (:function
        :state-changing nil
        :lambda-list (number &rest more-numbers)
	:entry-name "minusn"		;BB - was "minus"
	:object-name "Fminus"
	:argument-types (number &rest number)
	:return-type number
	)
    (:variable
        :variable-name "Us"
        :return-type t
	)
    )

("/"
    (:symbol
        :package "TCL"
	:symbol-name "Qslash"
	)
    (:function
        :state-changing nil
        :lambda-list (number &rest more-numbers)
	:entry-name "dividen"		;BB - was "divide"
	:object-name "Fdivide"
	:argument-types (number &rest number)
	:return-type number
	)
    (:variable
        :variable-name "Sl"
        :return-type t
	)
    )

("//"
    (:symbol
        :package "TCL"
	:symbol-name "Qslashslash"
	)
    (:variable
        :variable-name "Sl_sl"
        :return-type t
	)
    )

("///"
    (:symbol
        :package "TCL"
	:symbol-name "Qslashslashslash"
	)
    (:variable
        :variable-name "Sl_sl_sl"
        :return-type t
	)
    )

("/="
    (:symbol
        :package "TCL"
	:symbol-name "Qnum_ne"
	)
    (:function
        :state-changing nil
        :lambda-list (&rest numbers)
	:entry-name "num_nen"		;BB
	:object-name "Fnum_ne"
	:argument-types (&rest number)
	:return-type t
	)
    )

("1+"
    (:symbol
        :package "TCL"
	:symbol-name "Qadd1"
	)
    (:function
        :state-changing nil
        :lambda-list (a)
	:entry-name "add1"
	:object-name "Fadd1"
	:argument-types (number)
	:return-type number
	:transforms ((trun:1+% :no-longs)
		     ;(trun:1+%int64 :all-int64)
		     (trun:1+%long nil)
		     (trun:1+%single :single)
		     (trun:1+%double nil))
	)
    )

("1-"
    (:symbol
        :package "TCL"
	:symbol-name "Qsub1"
	)
    (:function
        :state-changing nil
        :lambda-list (a)
	:entry-name "sub1"
	:object-name "Fsub1"
	:argument-types (number)
	:return-type number
	:transforms ((trun:1-% :no-longs)
		     ;(trun:1+%int64 :all-int64)
		     (trun:1-%long nil)
		     (trun:1-%single :single)
		     (trun:1-%double nil))
	)
    )

("<"
    (:symbol
        :package "TCL"
	:symbol-name "Qnum_lt"
	)
    (:function
        :state-changing nil
        :lambda-list (number &rest more-numbers)
	:entry-name "num_ltn"		;BB
	:object-name "Fnum_lt"
	:argument-types (number &rest number)
	:return-type t
	)
    )

("<="
    (:symbol
        :package "TCL"
	:symbol-name "Qnum_le"
	)
    (:function
        :state-changing nil
        :lambda-list (number &rest more-numbers)
	:entry-name "num_len"		;BB
	:object-name "Fnum_le"
	:argument-types (number &rest number)
	:return-type t
	)
    )

("="
    (:symbol
        :package "TCL"
	:symbol-name "Qnum_eq"
	)
    (:function
        :state-changing nil
        :lambda-list (number &rest more-numbers)
	:entry-name "num_eqn"		;BB
	:object-name "Fnum_eq"
	:argument-types (number &rest number)
	:return-type t
	)
    )

(">"
    (:symbol
        :package "TCL"
	:symbol-name "Qnum_gt"
	)
    (:function
        :state-changing nil
        :lambda-list (number &rest more-numbers)
	:entry-name "num_gtn"		;BB
	:object-name "Fnum_gt"
	:argument-types (number &rest number)
	:return-type t
	)
    )

(">="
    (:symbol
        :package "TCL"
	:symbol-name "Qnum_ge"
	)
    (:function
        :state-changing nil
        :lambda-list (number &rest more-numbers)
	:entry-name "num_gen"		;BB
	:object-name "Fnum_ge"
	:argument-types (number &rest number)
	:return-type t
	)
    )

("ABORT"
    (:symbol
        :package "TCL"
	)
    (:function
	:unsupported t
	:lambda-list (&optional condition)
	:argument-types (&optional (or condition null))
	:return-type nil
	)
    (:restart-name)
    )

("ABS"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (a)
	:argument-types (number)
	:return-type number
	:entry-name "l_abs"
	:transforms ((trun:abs% :no-longs)
		     (trun:abs%long nil)
		     (trun:abs%rd nil))
	)
    )

("ACONS"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (key datum a-list)
	:return-type cons
	:argument-types (t t t)
	)
    )

("ACOS"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (a)
	:return-type number
        :entry-name "lacos"
	:argument-types (number)
	)
    )

("ACOSH"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (a)
	:return-type number
	:entry-name "lacosh"
	:argument-types (number)
	)
    )

("ADD-METHOD"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (generic-function method)
	:return-type generic-function
	:generic-function t
	:argument-types (generic-function method)
	)
    )

("ADJOIN"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (item list &key test test-not key)
	:return-type cons
	)
    )

("ALLOCATE-INSTANCE"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (class &rest initargs)
	:return-type t
	:generic-function t
	)
    )

("ALPHA-CHAR-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (char)
	:return-type t
	:transforms ((trun:%alpha-char-p t))
	)
    )

("ALPHANUMERICP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (char)
	:return-type t
	:transforms ((trun:%alphanumericp t))
	)
    )

("AND"
    (:symbol
        :package "TCL"
	)
    (:macro)
    (:method-combination)
    (:type-specifier-list)
    )

("APPEND"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (&rest lists)
	:return-type t
	)
    (:method-combination)
    )

("APPLY"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (function arg &rest lists)
	:return-type (values &rest t)
	)
    (:setf-place)
    )

("APROPOS"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (string &optional package)
	:return-type (values))
    )

("APROPOS-LIST"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (string &optional package)
	:return-type list)
    )

("ARITHMETIC-ERROR"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("ARITHMETIC-ERROR-OPERANDS"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("ARITHMETIC-ERROR-OPERATION"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("ASH"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (i count)
	:return-type integer
	:transforms ((trun:ash-left%long nil)
		     (trun:ash-right%long nil))
	)
    )

("ASIN"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (a)
	:return-type number
	:entry-name "lasin"
	)
    )

("ASINH"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (a)
	:return-type number
	:entry-name "lasinh"
	)
    )

("ASSERT"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("ASSOC"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (item a-list &key test test-not key)
	:return-type list
	)
    )

("ASSOC-IF"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (predicate a-list &key key)
	:return-type list
	)
    )

("ASSOC-IF-NOT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (predicate a-list &key key)
	:return-type list
	)
    )

("ATAN"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (y &optional x)
	:return-type number
	:entry-name "latan"
	:transforms ((trun:atan1%rd nil)
		     (trun:atan%rd nil))
	)
    )

("ATANH"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (a)
	:return-type number
	:entry-name "latanh"
	)
    )

("BASE-CHAR"
    (:symbol
        :package "TCL"
	)
    (:type-name)
    )

("BASE-STRING"
    (:symbol
        :package "TCL"
	)
    (:type-name)
    (:type-specifier-list)
    )

("BIGNUM"
    (:symbol
        :package "TCL"
	)
    (:type-name)
    )

("BIT"
    (:symbol
        :package "TCL"
	:exists-at-runtime t
	)
    (:function
        :state-changing nil
        :lambda-list (bit-array &rest subscripts)
	:return-type bit
	:alias-p t
	)
    (:setf-function
        :lambda-list (new-bit bit-array &rest subscripts)
	:return-type bit
	)
    (:setf-place
        :setf-function t
	)
    (:type-name)
    )

("BIT-AND"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (bit-array1 bit-array2 &optional result-bit-array)
        :return-type (array bit)
        )
    )

("BIT-ANDC1"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (bit-array1 bit-array2 &optional result-bit-array)
        :return-type (array bit)
	)
    )

("BIT-ANDC2"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (bit-array1 bit-array2 &optional result-bit-array)
	:return-type (array bit)
	)
    )

("BIT-EQV"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (bit-array1 bit-array2 &optional result-bit-array)
	:return-type (array bit)
	)
    )

("BIT-IOR"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (bit-array1 bit-array2 &optional result-bit-array)
	:return-type (array bit)
	)
    )

("BIT-NAND"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (bit-array1 bit-array2 &optional result-bit-array)
	:return-type (array bit)
	)
    )

("BIT-NOR"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (bit-array1 bit-array2 &optional result-bit-array)
	:return-type (array bit)
	)
    )

("BIT-NOT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (bit-not &optional result-bit-array)
	:return-type (array bit)
	)
    )

("BIT-ORC1"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (bit-array1 bit-array2 &optional result-bit-array)
	:return-type (array bit)
	)
    )

("BIT-ORC2"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (bit-array1 bit-array2 &optional result-bit-array)
	:return-type (array bit)
	)
    )

("BIT-VECTOR"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    (:type-specifier-list)
    )

("BIT-VECTOR-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%bit-vector-p t))
	)
    )

("BIT-XOR"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (bit-array1 bit-array2 &optional result-bit-array)
	:return-type (array bit)
	)
    )

("BLOCK"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("BOOLE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (op integer1 integer2)
	:return-type integer
	)
    )

("BOOLE-1"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value 0
	)
    )

("BOOLE-2"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value 1
	)
    )

("BOOLE-AND"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value 2
	)
    )

("BOOLE-ANDC1"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value 3
	)
    )

("BOOLE-ANDC2"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value 4
	)
    )

("BOOLE-C1"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value 5
	)
    )

("BOOLE-C2"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value 6
	)
    )

("BOOLE-CLR"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value 7
	)
    )

("BOOLE-EQV"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value 8
	)
    )

("BOOLE-IOR"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value 9
	)
    )

("BOOLE-NAND"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value 10
	)
    )

("BOOLE-NOR"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value 11
	)
    )

("BOOLE-ORC1"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value 12
	)
    )

("BOOLE-ORC2"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value 13
	)
    )

("BOOLE-SET"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value 14
	)
    )

("BOOLE-XOR"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value 15
	)
    )

("BOTH-CASE-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (char)
	:return-type t
	)
    )

("BOUNDP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (symbol)
	:return-type t
	:transforms ((trun:%boundp t))
	)
    )

("BREAK"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional format-control &rest format-arguments)
	:return-type null
	:entry-name "breakn"
	)
    )

("BROADCAST-STREAM"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("BROADCAST-STREAM-STREAMS"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("BUILT-IN-CLASS"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:class-name)
    (:type-name)
    )

("BUTLAST"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list &optional n)
	:return-type list
	)
    )

("BYTE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (size position)
	:return-type t
	:transforms ((trun:%byte t))
	)
    )

("BYTE-POSITION"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (bytespec)
	:return-type integer
	:transforms ((trun:%byte-position t))
	)
    )

("BYTE-SIZE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (bytespec)
	:return-type integer
	:transforms ((trun:%byte-size t))
	)
    )

("CALL-ARGUMENTS-LIMIT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value most-positive-fixnum
	)
    )

("CALL-METHOD"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:macro)
    )

#+translator-supports-clos
("CALL-NEXT-METHOD"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (&rest arguments)
	:return-type (values &rest t)
	;; There seems to be no way to declare these lexical functions.
	:unsupported t
        )
    )

#-translator-supports-clos
("CALL-NEXT-METHOD"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :unsupported t
        )
    )

("CASE"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("CATCH"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("CCASE"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("CEILING"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (a &optional divisor)
	:return-type (values integer number)
	:transforms ()
	)
    )

("CELL-ERROR"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("CELL-ERROR-NAME"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("CERROR"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (continue-format-string error-format-string &rest args)
        :return-type null
	:entry-name "cerrorn"
	)
    )

("CHANGE-CLASS"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (instance class)
	:return-type t
	:generic-function t
	)
    )

("CHAR-CODE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (char)
	:return-type fixnum
	:transforms ((trun:%char-code t))
        )
    )

("CHAR-CODE-LIMIT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value cc-limit
	)
    )

("CHAR-DOWNCASE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (char)
        :return-type character
	:transforms ((trun:%char-downcase t))
	)
    )

("CHAR-EQUAL"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (character &rest more-characters)
	:entry-name "char_equaln"	;BB
        :return-type t
	)
    )

("CHAR-GREATERP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (character &rest more-characters)
	:entry-name "char_greaterpn"	;BB
        :return-type t
	)
    )

("CHAR-INT"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (char)
        :return-type fixnum
	:transforms ((trun:%char-int t))
	)
    )

("CHAR-LESSP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (character &rest more-characters)
	:entry-name "char_lesspn"	;BB
        :return-type t
	)
    )

("CHAR-NAME"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (char)
        :return-type (or simple-string null)
	)
    )

("CHAR-NOT-EQUAL"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (character &rest more-characters)
	:entry-name "char_not_equaln"	;BB
        :return-type t
	)
    )

("CHAR-NOT-GREATERP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (character &rest more-characters)
	:entry-name "char_not_greaterpn" ;BB
        :return-type t
	)
    )

("CHAR-NOT-LESSP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (character &rest more-characters)
	:entry-name "char_not_lesspn"	;BB
        :return-type t
	)
    )

("CHAR-UPCASE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (char)
        :return-type character
	:transforms ((trun:%char-upcase t))
	)
    )

("CHAR/="
    (:symbol
        :package "TCL"
	:symbol-name "Qchar_ne"
	)
    (:function
        :lambda-list (character &rest more-characters)
        :entry-name "char_nen"		;BB
	:object-name "Fchar_ne"
	:return-type t
	)
    )

("CHAR<"
    (:symbol
        :package "TCL"
	:symbol-name "Qchar_lt"
	)
    (:function
        :lambda-list (character &rest more-characters)
	:entry-name "char_ltn"		;BB
	:object-name "Fchar_lt"
	:return-type t
	)
    )

("CHAR<="
    (:symbol
        :package "TCL"
	:symbol-name "Qchar_le"
	)
    (:function
        :state-changing nil
        :lambda-list (character &rest more-characters)
	:entry-name "char_len"		;BB
	:object-name "Fchar_le"
	:return-type t
	)
    )

("CHAR="
    (:symbol
        :package "TCL"
	:symbol-name "Qchar_eq"
	)
    (:function
        :state-changing nil
        :lambda-list (character &rest more-characters)
	:entry-name "char_eqn"		;BB
	:object-name "Fchar_eq"
	:return-type t
	)
    )

("CHAR>"
    (:symbol
        :package "TCL"
	:symbol-name "Qchar_gt"
	)
    (:function
        :lambda-list (character &rest more-characters)
	:entry-name "char_gtn"		;BB
	:object-name "Fchar_gt"
	:return-type t
	)
    )

("CHAR>="
    (:symbol
        :package "TCL"
	:symbol-name "Qchar_ge"
	)
    (:function
        :state-changing nil
        :lambda-list (character &rest more-characters)
	:entry-name "char_gen"		;BB
	:object-name "Fchar_ge"
	:return-type t
	)
    )

("CHARACTER"
    (:symbol
        :package "TCL"
	:exists-at-runtime t
	)
    (:class-name)
    (:function
        :state-changing nil
        :lambda-list (object)
        :return-type character
	)
    (:type-name)
    )

("CHARACTERP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%characterp t))
	)
    )

("CHECK-TYPE"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("CIS"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (radians)
        :return-type number
	)
    )

("CLASS"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:class-name)
    (:type-name)
    )

("CLASS-NAME"
    (:symbol
        :package "TCLOS"
	:import-from nil
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (class)
	:return-type t
	:generic-function t
	)
    (:setf-function
        :lambda-list (name class)
	:return-type t
	:generic-function t
	)
    (:setf-place
        :setf-function t
	)
    )

("CLASS-OF"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    #+translator-supports-clos
    (:function
        :lambda-list (object)
	:return-type class
        )
    #-translator-supports-clos
    (:function
        :unsupported t
        )
    )

("CLEAR-INPUT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional input-stream)
        :return-type null
	)
    )

("CLEAR-OUTPUT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional output-stream)
        :return-type null
	)
    )

("CLOSE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (stream &key abort)
	:entry-name "lclose"		;stdio
        :return-type t
	)
    )

("CLRHASH"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (hash-table)
        :return-type hash-table
	)
    )

("CODE-CHAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (code)
	:return-type character
	:transforms ((trun:%code-char t))
	)
    )

("COERCE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object result-type)
        :return-type t
	)
    )

("COMPILATION-SPEED"
    (:symbol
        :package "TCL"
	)
    (:optimize-quality)
    )

("COMPILE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    (:random-syntax)
    )

("COMPILE-FILE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (input-file &key output-file verbose print
				 external-format)
	:return-type (values (or pathname null) t t)
        )
    )

("COMPILE-FILE-PATHNAME"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("COMPILED-FUNCTION"
    (:symbol
        :package "TCL"
	)
    (:type-name)
    )

("COMPILED-FUNCTION-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object)
	:transforms ((trun:%compiled-function-p t))
	:return-type t
	)
    )


("COMPILER-MACRO"
    (:symbol
        :package "TCL"
	)
    (:documentation-type)
    )
    

("COMPILER-MACRO-FUNCTION"
    (:symbol
        :package "TCL"
	:import-from nil
	)
    (:function
        :unsupported t
        )
    (:setf-place)
    )

("COMPLEMENT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (function)
        :return-type compiled-function
	)
    )

("COMPLEX"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:function
        :lambda-list (realpart &optional imagpart)
        :return-type complex
	:entry-name "lcomplex"
	)
    (:type-name)
    (:type-specifier-list)
    )

("COMPLEXP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%complexp t))
	)
    )

("COMPUTE-APPLICABLE-METHODS"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (generic-function arguments)
	:return-type list ;  **Fix this. (maybe)
	:generic-function t
	)
    )

("COMPUTE-RESTARTS"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("CONCATENATE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (result-type &rest sequences)
        :return-type sequence
	)
    )

("CONCATENATED-STREAM"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("CONCATENATED-STREAM-STREAMS"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("COND"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("CONDITION"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("CONJUGATE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (a)
        :return-type number
	:unsupported t
	)
    )

("CONSTANTLY"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (value)
	:return-type function
        )
    )

("CONSTANTP"
    (:symbol
        :package "TCL"
	:import-from nil
	)
    (:function
        :state-changing nil
        :lambda-list (object &optional env)
        :return-type t
	)
    )

("CONTINUE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (&optional condition)
	:return-type null
        )
    (:restart-name)
    )

("CONTROL-ERROR"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("COPY-ALIST"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (list)
        :return-type list
	)
    )

("COPY-LIST"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
        :return-type list
	)
    )

("COPY-PPRINT-DISPATCH"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("COPY-READTABLE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional from-readtable to-readtable)
        :return-type readtable
	)
    )

("COPY-SEQ"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (sequence)
        :return-type sequence
	)
    )

("COPY-STRUCTURE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (structure)
	:return-type structure-object
        )
    )

("COPY-SYMBOL"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (sym &optional copy-props)
        :return-type symbol
	)
    )

("COPY-TREE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (list)
        :return-type list
	)
    )

("COS"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (radians)
        :return-type number
	:entry-name "lcos"
	:transforms ((trun:cos%rd nil))
	)
    )

("COSH"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (a)
        :return-type number
	:entry-name "lcosh"
	)
    )

("COUNT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (item sequence &key from-end test test-not start end key)
        :return-type fixnum
	)
    )

("COUNT-IF"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (predicate sequence &key from-end start end key)
        :return-type fixnum
	)
    )

("COUNT-IF-NOT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (predicate sequence &key from-end start end key)
        :return-type fixnum
	)
    )

("CTYPECASE"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DEBUG"
    (:symbol
        :package "TCL"
	)
    (:optimize-quality)
    )

("DECF"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DECLAIM"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DECLARATION"
    (:symbol
        :package "TCL"
	)
    (:declaration)
    (:random-syntax)
    )

("DECLARE"
    (:symbol
        :package "TCL"
	)
    (:random-syntax)
    (:special-form)
    )

("DECODE-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (float)
        :return-type (values float fixnum float)
	)
    )

("DECODE-UNIVERSAL-TIME"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (universal-time &optional time-zone)
	:return-type (values fixnum fixnum fixnum fixnum fixnum fixnum fixnum
			     t rational)
	)
    )

("DEFCLASS"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:macro)
    )

("DEFCONSTANT"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DEFGENERIC"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:macro)
    )

("DEFINE-COMPILER-MACRO"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DEFINE-CONDITION"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DEFINE-METHOD-COMBINATION"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:macro)
    )

("DEFINE-MODIFY-MACRO"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DEFINE-SETF-EXPANDER"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DEFMACRO"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DEFMETHOD"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:macro)
    )

("DEFPACKAGE"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DEFPARAMETER"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DEFSETF"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DEFSTRUCT"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DEFTYPE"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DEFUN"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DEFVAR"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DELETE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (item sequence
			   &key from-end test test-not start end count key)
	:return-type sequence
	:entry-name "ldelete"
	)
    )

("DELETE-DUPLICATES"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (sequence &key from-end test test-not start end key)
        :return-type sequence
	)
    )

("DELETE-FILE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (file)
	:return-type t
        )
    )

("DELETE-IF"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (predicate sequence &key from-end start end count key)
        :return-type sequence
	)
    )

("DELETE-IF-NOT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (predicate sequence &key from-end start end count key)
        :return-type sequence
	)
    )

("DELETE-PACKAGE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("DENOMINATOR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (rational)
        :return-type integer
	:transforms ((trun:%denominator t))
	)
    )

("DEPOSIT-FIELD"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (newbyte bytespec i)
        :return-type integer
	)
    )

("DESCRIBE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (object &optional stream)
	:return-type (values)
        )
    )

("DESCRIBE-OBJECT"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :unsupported t
	:lambda-list (object stream)
	:return-type t ; check this.  the spec allows any number of results.
	:generic-function t
	)
    )

("DESTRUCTURING-BIND"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DIGIT-CHAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (weight &optional radix font)
        :return-type (or character null)
	)
    )

("DIGIT-CHAR-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (char &optional radix)
        :return-type t
	)
    )

("DIRECTORY"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (pathname &key)
        :return-type list
	)
    )

("DIRECTORY-NAMESTRING"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (pathname)
        :return-type simple-string
	)
    )

("DISASSEMBLE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("DIVISION-BY-ZERO"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("DO"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DO*"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DO-ALL-SYMBOLS"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DO-EXTERNAL-SYMBOLS"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DO-SYMBOLS"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DOCUMENTATION"
    ;; This function has different behavior from the host definition when
    ;; the argument is a class object.
    #+translator-supports-clos
    (:symbol
        :package "TCLOS"
	:import-from nil
	:export ("TCLOS" "TCL")
	)
    #-translator-supports-clos
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :unsupported t
	:lambda-list (object &optional doc-type)
	:return-type t
	:generic-function t
	)
    (:setf-function
        :unsupported t
	:lambda-list (doc object &optional doc-type)
	:return-type t
	:generic-function t
	)
    (:setf-place
        :setf-function t
	)
    )

("DOLIST"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DOTIMES"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("DOUBLE-FLOAT"
    (:symbol
        :package "TCL"
	:exists-at-runtime t
	)
    (:type-name)
    (:type-specifier-list)
    )

("DOUBLE-FLOAT-EPSILON"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type double-float
	;; :initial-value ?
	)
    )

("DOUBLE-FLOAT-NEGATIVE-EPSILON"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type double-float
	;; :initial-value ?
	)
    )

("DPB"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (newbyte bytespec i)
        :return-type integer
	)
    )

("DRIBBLE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (&optional pathname)
	:return-type t ; check this.  the spec allows any number of results.
        )
    )

("DYNAMIC-EXTENT"
    (:symbol
        :package "TCL"
	)
    (:declaration)
    (:random-syntax)
    )

("ECASE"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("ECHO-STREAM"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("ECHO-STREAM-INPUT-STREAM"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("ECHO-STREAM-OUTPUT-STREAM"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("ED"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:return-type t ; check this.  the spec allows any number of results.
        )
    )

("ELT"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (sequence index)
        :return-type t
	)
    (:setf-place)
    )

("ENCODE-UNIVERSAL-TIME"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (second minute hour date month year &optional time-zone)
        :return-type integer
	)
    )

("END-OF-FILE"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("ENOUGH-NAMESTRING"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (pathname &optional defaults)
        :return-type simple-string
	)
    )

#+translator-supports-clos
("ENSURE-GENERIC-FUNCTION"
    (:symbol
        :package "TCLOS"
	:import-from nil
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (name &rest arguments)
	:return-type t
	)
    )

#-translator-supports-clos
("ENSURE-GENERIC-FUNCTION"
    (:symbol
        :package "TCLOS"
	:import-from nil
	:export ("TCLOS" "TCL")
	)
    (:function
        :unsupported t
	)
    )

("EQ"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (x y)
	:return-type t
	:transforms ((trun:%eq t))
	)
    )

("EQL"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (x y)
	:return-type t
	:transforms ((trun:%eql-fast-1 nil)
		     (trun:%eql-fast-2 nil)
		     (trun:%eql t))
	)
    (:random-syntax)
    (:type-specifier-list)
    )

("EQUAL"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (x y)
	:return-type t
	:transforms ((trun:%equal t))
	)
    )

("EQUALP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (x y)
	:return-type t
	:transforms ((trun:%equalp t))
	)
    )

("ERROR"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:function
        :lambda-list (format-string &rest args)
        :return-type nil
	:entry-name "errorn"
	)
    (:type-name)
    )

("ETYPECASE"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("EVAL"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t  ; **Fix this
	:lambda-list (form)
	:return-type (values &rest t)
	;;:entry-name "eval"
        )
    (:random-syntax)
    )

("EVAL-WHEN"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("EVENP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (a)
        :return-type t
	:transforms ((trun:evenp% :no-longs)
		     (trun:evenp%long nil))
	)
    )

("EVERY"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (predicate sequence &rest more-sequences)
        :return-type t
	)
    )

("EXP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (power)
        :return-type number
	:entry-name "lexp"
	:transforms ((trun:exp%rd nil))
	)
    )

("EXPORT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (symbols &optional package)
        :return-type (member t)
	)
    )

("EXPT"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (base power)
        :return-type number
	:transforms ((trun:expt2 nil)
		     (trun:expt%long nil)
		     (trun:expt%rd nil))
	)
    )

("EXTENDED-CHAR"
    (:symbol
        :package "TCL"
	)
    (:type-name)
    )

("FBOUNDP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (symbol)
        :return-type t
	)
    )

("FCEILING"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (a &optional divisor)
        :return-type (values float number)
	:transforms ()
	)
    )

("FDEFINITION"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (name)
	:return-type t
        )
    (:setf-place)
    )

("FFLOOR"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (a &optional divisor)
	:entry-name "lffloor"		;HP, SGI conflict
        :return-type (values float number)
	:transforms ()
	)
    )

("FILE-AUTHOR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (file)
        :return-type (or simple-string null)
	)
    )

("FILE-ERROR"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("FILE-ERROR-PATHNAME"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("FILE-LENGTH"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (file)
        :return-type (or integer null)
	)
    )

("FILE-NAMESTRING"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (pathname)
        :return-type simple-string
	)
    )

("FILE-POSITION"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (file-stream &optional position)
        :return-type t
	)
    )

("FILE-STREAM"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("FILE-STRING-LENGTH"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("FILE-WRITE-DATE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (file)
        :return-type (or integer null)
	)
    )

("FILL"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (sequence item &key start end)
        :return-type sequence
	)
    )

("FIND"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (item sequence &key from-end test test-not start end key)
        :return-type t
	)
    )

("FIND-ALL-SYMBOLS"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (string-or-symbol)
        :return-type list
	:unsupported t
	)
    )

("FIND-CLASS"
    (:symbol
        :package "TCLOS"
	:import-from nil
	:export ("TCLOS" "TCL")
	)
    #+translator-supports-clos
    (:function
        :lambda-list (symbol &optional errorp environment)
	:return-type t
        )
    #-translator-supports-clos
    (:function
        :unsupported t
	)
    #+translator-supports-clos
    (:setf-function
        :lambda-list (value symbol &optional errorp environment)
	:return-type t
	)
    #-translator-supports-clos
    (:setf-function
        :unsupported t
	)
    (:setf-place
        :setf-function t
	)
    )

("FIND-IF"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (predicate sequence &key from-end start end key)
        :return-type t
	)
    )

("FIND-IF-NOT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (predicate sequence &key from-end start end key)
        :return-type t
	)
    )

("FIND-METHOD"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list
	  (generic-function qualifiers specializers &optional errorp)
	:return-type t
	:generic-function t
	)
    )

("FIND-PACKAGE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (name)
        :return-type (or package null)
	)
    )

("FIND-RESTART"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("FIND-SYMBOL"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (string &optional package)
        :return-type (values symbol symbol)
	)
    )

("FINISH-OUTPUT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional output-stream)
        :return-type null
	)
    )

("FIXNUM"
    (:symbol
        :package "TCL"
	:exists-at-runtime t
	)
    (:type-name)
    )

("FLET"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("FLOAT"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:function
        :state-changing nil
        :lambda-list (a &optional other)
	:entry-name "lfloat"		;C language conflict
        :return-type float
	:transforms ((trun:%long-to-float nil)
		     (trun:%long-to-float2 :single)
		     (trun:%long-to-double nil)
		     (trun:%long-to-double2 nil))
	)
    (:type-name)
    (:type-specifier-list)
    )

("FLOAT-DIGITS"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (float)
        :return-type fixnum
	)
    )

("FLOAT-PRECISION"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (float)
        :return-type fixnum
	)
    )

("FLOAT-RADIX"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (float)
        :return-type fixnum
	)
    )

("FLOAT-SIGN"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (float1 &optional float2)
        :return-type float
	)
    )

("FLOATING-POINT-INEXACT"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("FLOATING-POINT-INVALID-OPERATION"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("FLOATING-POINT-OVERFLOW"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("FLOATING-POINT-UNDERFLOW"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("FLOATP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%floatp t))
	)
    )

("FLOOR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (a &optional divisor)
	:entry-name "lfloor"		;RTL conflict
        :return-type (values integer number)
	:transforms ((trun:floor-positive%long nil))
	)
    )

("FMAKUNBOUND"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (symbol)
        :return-type symbol
	)
    )

("FORCE-OUTPUT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional output-stream)
        :return-type null
	)
    )

("FORMAT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (destination control-string &rest arguments)
        :return-type (or string null)
	:entry-name "formatn"
	)
    )

("FORMATTER"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("FRESH-LINE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional output-stream)
        :return-type t
	)
    )

("FROUND"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (a &optional divisor)
        :return-type (values float number)
	:transforms ()
	)
    )

("FTRUNCATE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (a &optional divisor)
	:entry-name "lftruncate"	;HP conflict
        :return-type (values float number)
	:transforms ()
	)
    )

("FTYPE"
    (:symbol
        :package "TCL"
	)
    (:declaration)
    (:random-syntax)
    )

("FUNCALL"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (fn &rest arguments)
        :return-type (values &rest t)
	)
    )

("FUNCTION"
    (:symbol
        :package "TCL"
	:exists-at-runtime t
	)
    (:class-name)
    (:documentation-type)
    (:random-syntax)
    (:special-form)
    (:type-name)
    (:type-specifier-list)
    )

("FUNCTION-KEYWORDS"
    (:symbol
        :package "TCLOS"
	:import-from nil
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (method)
	:return-type (values list t)
	:generic-function t
	)
    )

("FUNCTION-LAMBDA-EXPRESSION"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (function)
	:return-type (values t t t)
        )
    )

("FUNCTIONP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object)
        :return-type t
	:transforms ((trun:%functionp t))
	)
    )

("GCD"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&rest integers)
        :return-type integer
	:entry-name "gcdn"		;BB
	)
    )

;;; Removed from language 12/91
#|("GENERIC-FLET"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:special-form)
    )
|#


;;; Macro removed from language 12/91
("GENERIC-FUNCTION"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:class-name)
    ;(:macro)
    (:type-name)
    )


;;; Removed from language 12/91
#|("GENERIC-LABELS"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:special-form)
    )
|#

("GENSYM"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (&optional x)
        :return-type symbol
	)
    )

("GENTEMP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (&optional prefix package)
        :return-type symbol
	)
    )

("GET"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
	:nonconsing t
        :lambda-list (symbol indicator &optional default)
        :return-type t
	)
    (:setf-place)
    )

("GET-DECODED-TIME"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list ()
	:return-type (values fixnum fixnum fixnum fixnum fixnum fixnum fixnum
			     t rational)
	)
    )

("GET-DISPATCH-MACRO-CHARACTER"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        :lambda-list (disp-char sub-char &optional readtable)
        :return-type (or function null)
	)
    )

("GET-INTERNAL-REAL-TIME"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list ()
        :return-type integer
	)
    )

("GET-INTERNAL-RUN-TIME"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list ()
        :return-type integer
	)
    )

("GET-MACRO-CHARACTER"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (char &optional readtable)
        :return-type (values (or function null) t)
	)
    )

("GET-OUTPUT-STREAM-STRING"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (string-output-stream)
        :return-type string
	)
    )

("GET-PROPERTIES"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (place indicator-list)
        :return-type (values t t list)
	)
    )

("GET-SETF-EXPANSION"
    (:symbol
        :package "TCL"
	:import-from nil
	)
    (:function
        :unsupported t
	:lambda-list (place &optional environment)
	:return-type (values list list list t t)
	)
    )

("GET-UNIVERSAL-TIME"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list ()
        :return-type integer
	)
    )

("GETF"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
	:nonconsing t
        :lambda-list (place indicator &optional default)
        :return-type t
	)
    (:setf-place)
    )

("GETHASH"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (key hash-table &optional default)
        :return-type (values t t)
	)
    (:setf-place)
    )

("GO"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("GRAPHIC-CHAR-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (char)
        :return-type t
	:transforms ((trun:%graphic-char-p t))
	)
    )

("HANDLER-BIND"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("HANDLER-CASE"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("HASH-TABLE"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("HASH-TABLE-COUNT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (hash-table)
	:return-type fixnum
	;; Not currently open-coded in runtime   jar 4/29/91
	;; :transforms ((trun:%hash-table-count t))
	;; WB 9/4/91:  Dmitry and Kim agree that there's no
	;; benefit to be gained from open-coding this accessor, which
	;; would also have to multiply evaluate its argument.
	)
    )

("HASH-TABLE-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%hash-table-p t))
	)
    )

("HASH-TABLE-REHASH-SIZE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("HASH-TABLE-REHASH-THRESHOLD"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("HASH-TABLE-SIZE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("HASH-TABLE-TEST"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("HOST-NAMESTRING"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (pathname)
        :return-type simple-string
	)
    )

("IDENTITY"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object)
        :return-type t
	:transforms ((trun:%identity t))
	)
    )

("IF"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("IGNORABLE"
    (:symbol
        :package "TCL"
	)
    (:declaration)
    (:random-syntax)
    )

("IGNORE"
    (:symbol
        :package "TCL"
	)
    (:declaration)
    (:random-syntax)
    )

("IGNORE-ERRORS"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("IMAGPART"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (a)
        :return-type number
	)
    )

("IMPORT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (symbols &optional package)
        :return-type (member t)
	)
    )

("IN-PACKAGE"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("INCF"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("INITIALIZE-INSTANCE"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (object &rest initargs)
	:return-type t
	:generic-function t
	)
    )

("INLINE"
    (:symbol
        :package "TCL"
	)
    (:declaration)
    (:random-syntax)
    )

("INPUT-STREAM-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (stream)
	:return-type t
	:transforms ((trun:%input-stream-p t))
	)
    )

("INSPECT"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (object)
	:return-type t ; check this.  the spec allows any number of results.
        )
    )

("INTEGER"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    (:type-specifier-list)
    )

("INTEGER-DECODE-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (float)
        :return-type (values integer fixnum fixnum)
	)
    )

("INTEGER-LENGTH"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (i)
        :return-type fixnum
	)
    )

("INTEGERP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%integerp t))
	)
    )

("INTERACTIVE-STREAM-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("INTERN"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (string &optional package)
        :return-type (values symbol symbol)
	)
    )

("INTERNAL-TIME-UNITS-PER-SECOND"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value 1000
	)
    )

("INTERSECTION"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (list1 list2 &key test test-not key)
        :return-type list
	)
    )

("INVALID-METHOD-ERROR"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    #+translator-supports-clos
    (:function
        :lambda-list (method format-control &rest arguments)
	:return-type t ; check this.  the spec allows any number of results.
	:unsupported t
	)
    #-translator-supports-clos
    (:function
        :unsupported t
	)
    )

("INVOKE-DEBUGGER"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (condition)
	:return-type nil
        )
    )

("INVOKE-RESTART"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (restart &rest arguments)
	:return-type (values &rest t)
        )
    )

("INVOKE-RESTART-INTERACTIVELY"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (restart)
	:return-type (values &rest t)
        )
    )

("ISQRT"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (i)
        :return-type integer
	)
    )

("ISYMBOL-NAME"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "isymbol_name"
	:allow-multiple-uses-of-entry-name t
        :lambda-list (symbol)
	:return-type string
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :simple-string
	)
    )

("KEYWORD"
    (:symbol
        :package "TCL"
	)
    (:type-name)
    )

("KEYWORDP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%keywordp t))
	)
    )

("LABELS"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("LAMBDA"
    (:symbol
        :package "TCL"
	)
    (:random-syntax)
    )

("LAMBDA-LIST-KEYWORDS"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type cons
	;; :initial-value '(&optional &rest &key &allow-other-keys &aux
	;;			   &whole &environment &body)
	)
    )

("LAMBDA-PARAMETERS-LIMIT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :initial-value most-positive-fixnum
	)
    )

("LCM"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&rest integers)
        :return-type integer
	:entry-name "lcmn"		;BB
	)
    )

("LDB"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (bytespec i)
        :return-type integer
	)
    (:setf-place)
    )

("LDB-TEST"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (bytespec i)
        :return-type t
	)
    )

("LEAST-NEGATIVE-DOUBLE-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type double-float
	;; :initial-value ?
	)
    )

("LEAST-NEGATIVE-LONG-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type long-float
	;; :initial-value ?
	)
    )

("LEAST-NEGATIVE-NORMALIZED-DOUBLE-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type double-float
	;; :initial-value ?
	)
    )

("LEAST-NEGATIVE-NORMALIZED-LONG-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type long-float
	;; :initial-value ?
	)
    )

("LEAST-NEGATIVE-NORMALIZED-SHORT-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type short-float
	;; :initial-value ?
	)
    )

("LEAST-NEGATIVE-NORMALIZED-SINGLE-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type single-float
	;; :initial-value ?
	)
    )

("LEAST-NEGATIVE-SHORT-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type short-float
	;; :initial-value ?
	)
    )

("LEAST-NEGATIVE-SINGLE-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type single-float
	;; :initial-value ?
	)
    )

("LEAST-POSITIVE-DOUBLE-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type double-float
	;; :initial-value ?
	)
    )

("LEAST-POSITIVE-LONG-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type long-float
	;; :initial-value ?
	)
    )

("LEAST-POSITIVE-NORMALIZED-DOUBLE-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type double-float
	;; :initial-value ?
	)
    )

("LEAST-POSITIVE-NORMALIZED-LONG-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type long-float
	;; :initial-value ?
	)
    )

("LEAST-POSITIVE-NORMALIZED-SHORT-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type short-float
	;; :initial-value ?
	)
    )

("LEAST-POSITIVE-NORMALIZED-SINGLE-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type single-float
	;; :initial-value ?
	)
    )

("LEAST-POSITIVE-SHORT-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type short-float
	;; :initial-value ?
	)
    )

("LEAST-POSITIVE-SINGLE-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type single-float
	;; :initial-value ?
	)
    )

("LENGTH"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
	:nonconsing t
        :lambda-list (sequence)
        :return-type fixnum
	:transforms ((trun:%primitive-vector-length nil))
	)
    )

("LET"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("LET*"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("LISP-IMPLEMENTATION-TYPE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list ()
	:return-type simple-string
        )
    )

("LISP-IMPLEMENTATION-VERSION"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list ()
	:return-type simple-string
        )
    )

("LIST"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:function
        :state-changing nil
        :lambda-list (&rest args)
        :return-type list
	)
    (:method-combination)
    (:type-name)
    )

("LIST*"
    (:symbol
        :package "TCL"
        :symbol-name "Qlist_star"
	)
    (:function
        :state-changing nil
        :lambda-list (arg &rest others)
	:return-type cons
	:entry-name "list_star"
	:object-name "Flist_star"
	)
    )

("LIST-ALL-PACKAGES"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list ()
        :return-type cons
	)
    )

("LIST-LENGTH"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (list)
        :return-type (or fixnum null)
	)
    )

("LISTEN"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (&optional input-stream)
        :return-type t
	:entry-name "llisten"
	)
    )

("LOAD"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    (:random-syntax)
    )

("LOAD-LOGICAL-PATHNAME-TRANSLATIONS"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("LOAD-TIME-VALUE"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("LOCALLY"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("LOG"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (a &optional base)
	:entry-name "llog"		;C RTL conflict
        :return-type number
	:transforms ((trun:log1%rd nil)
		     (trun:log%rd nil))
	)
    )

("LOGAND"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (&rest integers)
	:entry-name "logandn"		;BB
        :return-type integer
	)
    )

("LOGANDC1"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (i j)
        :return-type integer
	:transforms ((trun:logandc1%long nil))
	)
    )

("LOGANDC2"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (i j)
        :return-type integer
	:transforms ((trun:logandc2%long nil))
	)
    )

("LOGBITP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (index i)
        :return-type t
	:transforms ((trun:logbitp%long nil))
	)
    )

("LOGCOUNT"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (i)
        :return-type fixnum
	:transforms ((trun:logcount%long nil))
	)
    )

("LOGEQV"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&rest integers)
	:entry-name "logeqvn"		;BB
        :return-type integer
	)
    )

("LOGICAL-PATHNAME"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:function
        :unsupported t
        )
    (:type-name)
    )

("LOGICAL-PATHNAME-TRANSLATIONS"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    (:setf-place)
    )

("LOGIOR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (&rest integers)
	:entry-name "logiorn"		;BB
        :return-type integer
	)
    )

("LOGNAND"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (i j)
        :return-type integer
	:transforms ((trun:lognand%long nil))
	)
    )

("LOGNOR"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (i j)
        :return-type integer
	:transforms ((trun:lognor%long nil))
	)
    )

("LOGNOT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (i)
        :return-type integer
	:transforms ((trun:lognot% :no-longs)
		     (trun:lognot%long nil))
	)
    )

("LOGORC1"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (i j)
        :return-type integer
	:transforms ((trun:logorc1%long nil))
	)
    )

("LOGORC2"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (i j)
        :return-type integer
	:transforms ((trun:logorc2%long nil))
	)
    )

("LOGTEST"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (i j)
        :return-type t
	:transforms ((trun:logtest%long nil))
	)
    )

("LOGXOR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (&rest integers)
	:entry-name "logxorn"		;BB
        :return-type integer
	)
    )

("LONG-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:type-name)
    (:type-specifier-list)
    )

("LONG-FLOAT-EPSILON"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type long-float
	;; :initial-value ?
	)
    )

("LONG-FLOAT-NEGATIVE-EPSILON"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type long-float
	;; :initial-value ?
	)
    )

("LONG-SITE-NAME"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list ()
	:return-type simple-string
        )
    )

("LOOP"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("LOOP-FINISH"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("LOWER-CASE-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (character)
        :return-type t
	:transforms ((trun:%lower-case-p t))
	)
    )

("MACHINE-INSTANCE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("MACHINE-TYPE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("MACHINE-VERSION"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("MACRO-FUNCTION"
    (:symbol
        :package "TCL"
	:import-from nil
	)
    (:function
        :state-changing nil
        :lambda-list (symbol &optional env)
	:return-type (or function null)
        )
    (:setf-place)
    )

("MACROEXPAND"
    (:symbol
        :package "TCL"
	:import-from nil
	)
    (:function
        :lambda-list (form &optional env)
	:return-type (values t t)
        )
    )

("MACROEXPAND-1"
    (:symbol
        :package "TCL"
	:import-from nil
	)
    (:function
        :lambda-list (form &optional env)
	:return-type (values t t)
        )
    )

("MACROLET"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("MAKE-BROADCAST-STREAM"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (&rest streams)
        :return-type broadcast-stream
	)
    )

("MAKE-CONCATENATED-STREAM"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&rest streams)
        :return-type concatenated-stream
	)
    )

("MAKE-CONDITION"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("MAKE-DISPATCH-MACRO-CHARACTER"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        :lambda-list (char &optional non-terminating-p readtable)
        :return-type (member t)
	:unsupported t
	)
    )

("MAKE-ECHO-STREAM"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (input-stream output-stream)
        :return-type echo-stream
	)
    )

("MAKE-HASH-TABLE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (&key test size rehash-size rehash-threshold)
        :return-type hash-table
	)
    )

("MAKE-INSTANCE"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (class &rest initargs)
	:return-type t
	:generic-function t
	)
    )

("MAKE-INSTANCES-OBSOLETE"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (class)
	:return-type t
	:generic-function t
	)
    )

("MAKE-LOAD-FORM"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        :lambda-list (object)
	:return-type (values t &optional t)
	:generic-function t
	)
    )

("MAKE-LOAD-FORM-SAVING-SLOTS"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (object &key slot-names environment)
	:return-type (values t t)
	:generic-function t
        )
    )

("MAKE-METHOD"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:random-syntax)
    )

("MAKE-PACKAGE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (package-name &key nicknames use)
        :return-type package
	)
    )

;;; CLtL2 specifies a new keyword argument, CASE, for
;;; the MAKE-PATHNAME function; this is currently not supported.

("MAKE-PATHNAME"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (&key host device directory name type version defaults)
        :return-type pathname
	)
    )

("MAKE-RANDOM-STATE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional state)
        :return-type random-state
	)
    )

("MAKE-SEQUENCE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (type size &key initial-element)
        :return-type sequence
	)
    )

("MAKE-STRING-INPUT-STREAM"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (string &optional start end)
        :return-type string-stream
	)
    )

;;; CLtL2 specifies a new keyword argument, ELEMENT-TYPE, for
;;; the MAKE-STRING-OUTPUT-STREAM function; this is currently not supported

("MAKE-STRING-OUTPUT-STREAM"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list ()
        :return-type string-stream
	)
    )

("MAKE-SYMBOL"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (print-name)
        :return-type symbol
	)
    )

("MAKE-SYNONYM-STREAM"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :unsupported t
        :lambda-list (symbol)
        :return-type synonym-stream
	)
    )

("MAKE-TWO-WAY-STREAM"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (input-stream output-stream)
        :return-type two-way-stream
	)
    )

("MAKUNBOUND"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (symbol)
        :return-type symbol
	)
    )

("MAP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (result-type function sequence &rest more-sequences)
        :return-type sequence
	)
    )

("MAP-INTO"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (result-sequence function &rest sequences)
        :return-type sequence
	:unsupported t
	)
    )

("MAPC"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (function list &rest more-lists)
        :return-type list
	)
    )

("MAPCAN"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (function list &rest more-lists)
        :return-type list
	)
    )

("MAPCAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (function list &rest more-lists)
        :return-type list
	)
    )

("MAPCON"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (function list &rest more-lists)
        :return-type list
	)
    )

("MAPHASH"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (function hash-table)
        :return-type null
	)
    )

("MAPL"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (function list &rest more-lists)
        :return-type list
	)
    )

("MAPLIST"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (function list &rest more-lists)
        :return-type list
	)
    )

("MASK-FIELD"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (bytespec i)
        :return-type integer
	)
    (:setf-place)
    )

("MAX"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (number &rest more-numbers)
	:entry-name "maxn"		;BB
        :return-type number
	)
    (:method-combination)
    )

("MEMBER"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (item list &key test test-not key)
        :return-type list
	)
    (:type-specifier-list)
    )

("MEMBER-IF"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (predicate list &key key)
        :return-type list
	)
    )

("MEMBER-IF-NOT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (predicate list &key key)
        :return-type list
	)
    )

("MERGE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (result-type sequence1 sequence2 predicate &key key)
        :return-type sequence
	)
    )

("MERGE-PATHNAMES"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (pathname &optional defaults default-version)
        :return-type pathname
	)
    )

("METHOD"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:class-name)
    (:type-name)
    )

("METHOD-COMBINATION"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:class-name)
    (:type-name)
    )

("METHOD-COMBINATION-ERROR"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    #+translator-supports-clos
    (:function
        :lambda-list (format-control &rest arguments)
	:return-type t ; check this.  the spec allows any number of results.
	:unsupported t
	)
    #-translator-supports-clos
    (:function
        :unsupported t
	)
    )

("METHOD-QUALIFIERS"
    (:symbol
        :package "TCLOS"
	:import-from nil
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (method)
	:return-type list
	:generic-function t
	)
    )

("MIN"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (number &rest more-numbers)
	:entry-name "minn"		;BB
        :return-type number
	)
    (:method-combination)
    )

("MINUSP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (a)
        :return-type t
	:transforms ((trun:minusp% :no-longs)
		     (trun:minusp%long nil)
		     (trun:minusp%single :single)
		     (trun:minusp%double nil))
	)
    )

("MISMATCH"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (sequence1 sequence2
				&key from-end test test-not key
				start1 start2 end1 end2)
	:return-type (or null fixnum)
	)
    )

("MOD"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (a divisor)
        :return-type (values integer number)
	:transforms ((trun:mod-positive%long nil))
	)
    (:type-specifier-list)
    )

("MOST-NEGATIVE-DOUBLE-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type double-float
	;; :initial-value ?
	)
    )

("MOST-NEGATIVE-FIXNUM"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	;; :initial-value #.(- (expt 2 29))
	)
    )

("MOST-NEGATIVE-LONG-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type long-float
	;; :initial-value ?
	)
    )

("MOST-NEGATIVE-SHORT-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type short-float
	;; :initial-value ?
	)
    )

("MOST-NEGATIVE-SINGLE-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type single-float
	;; :initial-value ?
	)
    )

("MOST-POSITIVE-DOUBLE-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type double-float
	;; :initial-value ?
	)
    )

("MOST-POSITIVE-FIXNUM"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	;; :initial-value #.(- (expt 2 29) 1)
	)
    )

("MOST-POSITIVE-LONG-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type long-float
	;; :initial-value ?
	)
    )

("MOST-POSITIVE-SHORT-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type short-float
	;; :initial-value ?
	)
    )

("MOST-POSITIVE-SINGLE-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type single-float
	;; :initial-value ?
	)
    )

("MUFFLE-WARNING"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (&optional condition)
	:return-type nil
        )
    (:restart-name)
    )

("MULTIPLE-VALUE-BIND"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("MULTIPLE-VALUE-CALL"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("MULTIPLE-VALUE-LIST"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("MULTIPLE-VALUE-PROG1"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("MULTIPLE-VALUE-SETQ"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("MULTIPLE-VALUES-LIMIT"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type fixnum
	:simple-p t
	;; :inital-value mv-limit
	)
    )

("NAME-CHAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (name)
        :return-type (or character null)
	)
    )

("NAMESTRING"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (pathname)
        :return-type simple-string
	)
    )

("NCONC"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&rest lists)
        :return-type t
	)
    (:method-combination)
    )

#+translator-supports-clos
("NEXT-METHOD-P"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list ()
	:return-type t
	;; There isn't a way to say local-only.
        :unsupported t
	)
    )

#-translator-supports-clos
("NEXT-METHOD-P"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :unsupported t
	)
    )

("NIL"
    (:symbol
        :package "TCL"
	:magicp t
	:exists-at-runtime t
	)
    (:constant
        :return-type null
	:initial-value NIL
	:simple-p t
	)
    (:type-name)
    )

("NINTERSECTION"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (list1 list2 &key test test-not key)
        :return-type list
	)
    )

("NO-APPLICABLE-METHOD"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (generic-function &rest arguments)
	:return-type t ; check this.  the spec allows any number of results.
	:generic-function t
	)
    )

("NO-NEXT-METHOD"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (generic-function method &rest arguments)
	:return-type t ; check this.  the spec allows any number of results.
	:generic-function t
	)
    )

("NOT"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%not%boolean :boolean)
		     (trun:%not t))
	)
    (:type-specifier-list)
    )

("NOTANY"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (predicate sequence &rest more-sequences)
        :return-type t
	)
    )

("NOTEVERY"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (predicate sequence &rest more-sequences)
        :return-type t
	)
    )

("NOTINLINE"
    (:symbol
        :package "TCL"
	)
    (:declaration)
    )

("NRECONC"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (x y)
        :return-type list
	)
    )

("NREVERSE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (sequence)
        :return-type sequence
	)
    )

("NSET-DIFFERENCE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (list1 list2 &key test test-not key)
        :return-type list
	)
    )

("NSET-EXCLUSIVE-OR"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (list1 list2 &key test test-not key)
        :return-type list
	)
    )

("NSTRING-CAPITALIZE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (string &key start end)
        :return-type string
	)
    )

("NSTRING-DOWNCASE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (string &key start end)
        :return-type string
	)
    )

("NSTRING-UPCASE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (string &key start end)
        :return-type string
	)
    )

("NSUBLIS"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (alist tree &key test test-not key)
        :return-type t
	)
    )

("NSUBST"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (new old tree &key test test-not key)
        :return-type t
	)
    )

("NSUBST-IF"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (new test tree &key key)
        :return-type t
	)
    )

("NSUBST-IF-NOT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (new test tree &key key)
        :return-type t
	)
    )

("NSUBSTITUTE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (newitem olditem sequence
			      &key from-end test test-not start end count key)
	:return-type sequence
	)
    )

("NSUBSTITUTE-IF"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (newitem test sequence &key from-end start end count key)
        :return-type sequence
	)
    )

("NSUBSTITUTE-IF-NOT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (newitem test sequence &key from-end start end count key)
        :return-type sequence
	)
    )

("NTH-VALUE"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("NTHCDR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (n list)
        :return-type t
	)
    )

("NULL"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:function
        :state-changing nil
        :lambda-list (object)
        :return-type t
	)
    (:type-name)
    )

("NUMBER"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("NUMBERP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
	:lambda-list (object)
       :return-type t
       :transforms ((trun:%numberp t))
       )
    )

("NUMERATOR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (rational)
        :return-type integer
	:transforms ((trun:%numerator t))
	)
    )

("NUNION"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (list1 list2 &key test test-not key)
        :return-type list
	)
    )

("ODDP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (a)
        :return-type t
	:transforms ((trun:oddp% :no-longs)
		     (trun:oddp%long nil))
	)
    )

;;; CLtL2 specifies a new keyword argument, EXTERNAL-FORMAT, for
;;; the OPEN function; this is currently not supported

("OPEN"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (filename &key direction element-type if-exists
			       if-does-not-exist)
	:entry-name "lopen"		;stdio conflict
	:return-type t
	)
    )

("OPEN-STREAM-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("OPTIMIZE"
    (:symbol
        :package "TCL"
	)
    (:declaration)
    (:random-syntax)
    )

("OR"
    (:symbol
        :package "TCL"
	)
    (:macro)
    (:method-combination)
    (:type-specifier-list)
    )

("OTHERWISE"
    (:symbol
        :package "TCL"
	)
    (:random-syntax)
    )

("OUTPUT-STREAM-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (stream)
	:return-type t
	:transforms ((trun:%output-stream-p t))
	)
    )

("PACKAGE"
    (:symbol
        :package "TCL"
	:symbol-name "Qpackage_type"
	)
    (:class-name)
    (:type-name)
    )

("PACKAGE-ERROR"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("PACKAGE-ERROR-PACKAGE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

;;; Package accessors don't declare the macro versions as equivalents
;;; because the macros work only on package objects and the functions 
;;; also take package names as arguments.

("PACKAGE-NAME"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (package)
        :return-type string
	)
    )

("PACKAGE-NICKNAMES"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (package)
        :return-type list
	)
    )

("PACKAGE-SHADOWING-SYMBOLS"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (package)
        :return-type list
	)
    )

("PACKAGE-USE-LIST"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (package)
        :return-type list
	)
    )

("PACKAGE-USED-BY-LIST"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (package)
        :return-type list
	)
    )

("PACKAGEP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%packagep t))
	)
    )

("PAIRLIS"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (keys data &optional a-list)
        :return-type list
	)
    )

("PARSE-ERROR"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("PARSE-INTEGER"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (string &key start end radix junk-allowed)
        :return-type (values (or null integer) fixnum)
	)
    )

("PARSE-NAMESTRING"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (thing &optional host defaults
			    &key start end junk-allowed)
        :return-type (values (or null pathname) fixnum)
	)
    )

("PATHNAME"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:function
        :state-changing nil
        :lambda-list (pathname)
        :return-type pathname
	)
    (:type-name)
    )


;;; We do not yet support the :case keyword for pathnames.  When we
;;; do, the equivalence of these guys to the macros will have to be 
;;; removed.

("PATHNAME-DEVICE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (pathname)
	:return-type t
	)
    )

("PATHNAME-DIRECTORY"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (pathname)
	:return-type t
	)
    )

("PATHNAME-HOST"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (pathname)
	:return-type t
	:transforms ((trun:%pathname-host t))
	)
    )

("PATHNAME-MATCH-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("PATHNAME-NAME"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (pathname)
	:return-type t
	)
    )

("PATHNAME-TYPE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (pathname)
        :return-type t
       )
    )

("PATHNAME-VERSION"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (pathname)
	:return-type t
	)
    )

("PATHNAMEP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%pathnamep t))
	)
    )

("PEEK-CHAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (&optional peek-type input-stream eof-error-p eof-value
				recursive-p)
	:return-type t
	)
    )

("PHASE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (number)
        :return-type number
	)
    )

("PI"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type long-float
	;; :initial-value #.pi
	)
    )

("PLUSP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (a)
        :return-type t
	:transforms ((trun:plusp% :no-longs)
		     (trun:plusp%long nil)
		     (trun:plusp%single :single)
		     (trun:plusp%double nil))
	)
    )

("POP"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("POSITION"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (item sequence
			   &key from-end test test-not start end key)
	:return-type (or fixnum null)
	)
    )

("POSITION-IF"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (test sequence &key from-end start end key)
        :return-type (or fixnum null)
	)
    )

("POSITION-IF-NOT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (test sequence &key from-end start end key)
        :return-type (or fixnum null)
	)
    )

("PPRINT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object &optional output-stream)
        :return-type null
	)
    )

("PPRINT-DISPATCH"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (object &optional table)
	:return-type (values t t)
        )
    )

("PPRINT-EXIT-IF-LIST-EXHAUSTED"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("PPRINT-FILL"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("PPRINT-INDENT"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("PPRINT-LINEAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("PPRINT-LOGICAL-BLOCK"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("PPRINT-NEWLINE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("PPRINT-POP"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("PPRINT-TAB"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("PPRINT-TABULAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("PRIN1"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object &optional output-stream)
        :return-type t
	)
    )

("PRIN1-TO-STRING"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object)
        :return-type simple-string
	)
    )

("PRINC"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object &optional output-stream)
        :return-type t
	)
    )

("PRINC-TO-STRING"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object)
        :return-type simple-string
	)
    )

("PRINT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object &optional output-stream)
        :return-type t
	)
    )

("PRINT-NOT-READABLE"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("PRINT-NOT-READABLE-OBJECT"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("PRINT-OBJECT"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (object stream)
	:return-type t
	:generic-function t
	)
    )

("PRINT-UNREADABLE-OBJECT"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("PROBE-FILE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (file)
        :return-type (or null pathname)
	)
    )

("PROCLAIM"
    (:symbol
        :package "TCL"
	:import-from nil
	)
    (:function
        :unsupported t
        )
    )

("PROG"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("PROG*"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("PROG1"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("PROG2"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("PROGN"
    (:symbol
        :package "TCL"
	)
    (:method-combination)
    (:special-form)
    )

("PROGRAM-ERROR"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("PROGV"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

;;; Returned to language 12/91
("PROVIDE"
    (:symbol
        :package "TCL"
	)
    (:function
         :lambda-list (module-name)
	 :return-type t
         :unsupported t
	 )
    )

("PSETF"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("PSETQ"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("PUSH"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("PUSHNEW"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("QUOTE"
    (:symbol
        :package "TCL"
	:exists-at-runtime t
	)
    (:special-form)
    )

("RANDOM"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (a &optional state)
        :return-type number
	:entry-name "l_random"
	)
    )

("RANDOM-STATE"
    (:symbol
        :package "TCL"
	:symbol-name "Qrandom_state_type"
	)
    (:class-name)
    (:type-name)
    )

("RANDOM-STATE-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%random-state-p t))
	)
    )

("RASSOC"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (item a-list &key test test-not key)
        :return-type list
	)
    )

("RASSOC-IF"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (predicate a-list &key key)
        :return-type list
	)
    )

("RASSOC-IF-NOT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (predicate a-list &key key)
        :return-type list
	)
    )

("RATIO"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("RATIONAL"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:function
        :lambda-list (a)
        :return-type rational
	)
    (:type-name)
    (:type-specifier-list)
    )

("RATIONALIZE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (a)
        :return-type rational
	)
    )

("RATIONALP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%rationalp t))
	)
    )

("READ"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional input-stream eof-error-p eof-value recursive-p)
	:entry-name "lread"		;stdio conflict
        :return-type t
	)
    )


;;; Note that :return-type is t even for specialized read functions, because
;;; eof-value can be anything.

("READ-BYTE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (binary-input-stream &optional eof-error-p eof-value)
        :return-type t
	)
    )

("READ-CHAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional input-stream eof-error-p eof-value recursive-p)
        :return-type t
	)
    )

("READ-CHAR-NO-HANG"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional input-stream eof-error-p eof-value recursive-p)
        :return-type t
	)
    )

("READ-DELIMITED-LIST"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (char &optional input-stream recursive-p)
        :return-type list
	)
    )

("READ-FROM-STRING"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (string &optional eof-error-p eof-value
			     &key start end preserve-whitespace)
	:return-type (values t fixnum)
	)
    )

("READ-LINE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional input-stream eof-error-p eof-value recursive-p)
        :return-type (values t t)
	)
    )

("READ-PRESERVING-WHITESPACE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional input-stream eof-error-p eof-value recursive-p)
        :return-type t
	)
    )

("READER-ERROR"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("READTABLE"
    (:symbol
        :package "TCL"
	:symbol-name "Qreadtable_type"
	)
    (:class-name)
    (:type-name)
    )

("READTABLE-CASE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    (:setf-place)
    )

("READTABLEP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%readtablep t))
	)
    )

("REAL"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    (:type-specifier-list)
    )

("REALP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%realp t))
	)
    )

("REALPART"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (number)
        :return-type number
	)
    )

("REDUCE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (function sequence &key from-end start end initial-value)
        :return-type t
	)
    )

("REINITIALIZE-INSTANCE"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (object &rest initargs)
	:return-type t
	:generic-function t
	)
    )

("REM"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (a divisor)
        :return-type (values integer number)
	:transforms ((trun:mod-positive%long nil))
	)
    )

("REMF"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("REMHASH"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (key hash-table)
        :return-type t
	)
    )

("REMOVE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (item sequence
			   &key from-end test test-not start end count key)
	:return-type sequence
	:entry-name "lremove"
	)
    )

("REMOVE-DUPLICATES"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (sequence &key from-end test test-not start end key)
        :return-type sequence
	)
    )

("REMOVE-IF"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (test sequence &key from-end start end count key)
        :return-type sequence
	)
    )

("REMOVE-IF-NOT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (test sequence &key from-end start end count key)
        :return-type sequence
	)
    )

("REMOVE-METHOD"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (generic-function method)
	:return-type generic-function
	:generic-function t
	)
    )

("REMPROP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (symbol indicator)
        :return-type t
	)
    )

("RENAME-FILE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (file new-name)
        :return-type (values pathname pathname pathname)
	)
    )

("RENAME-PACKAGE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (package new-name &optional new-nicknames)
        :return-type package
	)
    )

("REPLACE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (sequence1 sequence2 &key start1 end1 start2 end2)
        :return-type sequence
	)
    )

;;; Returned to language 12/91
("REQUIRE"
    (:symbol
        :package "TCL"
	)
    (:function
         :lambda-list (module-name)
	 :return-type t
         :unsupported t
	 )
    )

("RESTART"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("RESTART-BIND"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("RESTART-CASE"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("RESTART-NAME"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("RETURN"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("RETURN-FROM"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("REVAPPEND"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (x y)
        :return-type list
	)
    )

("REVERSE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (sequence)
        :return-type sequence
	)
    )

("ROOM"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional x)
        :return-type t ; check this.  the spec allows any number of results.
	)
    )

("ROTATEF"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("ROUND"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (a &optional divisor)
        :return-type (values integer number)
	:entry-name "l_round"
	:transforms ()
	)
    )

("SAFETY"
    (:symbol
        :package "TCL"
	)
    (:optimize-quality)
    )

("SATISFIES"
    (:symbol
        :package "TCL"
	)
    (:type-specifier-list)
    )

("SBIT"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (bit-array &rest subscripts)
        :return-type bit
	:alias-p t
	)
    (:setf-function
        :lambda-list (new-bit bit-array &rest subscripts)
	:return-type bit
	)
    (:setf-place
        :setf-function t
	)
    )

("SCALE-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (x i)
        :return-type float
	)
    )

("SEARCH"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (sequence1 sequence2
				&key from-end test test-not key
				start1 start2 end1 end2)
	:return-type (or null fixnum)
	)
    )

("SEQUENCE"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("SERIOUS-CONDITION"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("SET"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (symbol value)
        :return-type t
	)
    )

("SET-DIFFERENCE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (list1 list2 &key test test-not key)
        :return-type list
	)
    )

("SET-DISPATCH-MACRO-CHARACTER"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        :lambda-list (disp-char sub-char function &optional readtable)
        :return-type (member t)
	)
    )

("SET-EXCLUSIVE-OR"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (list1 list2 &key test test-not key)
        :return-type list
	)
    )

("SET-MACRO-CHARACTER"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (char function &optional non-terminating-p readtable)
        :return-type (member t)
	)
    )

("SET-PPRINT-DISPATCH"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("SET-SYNTAX-FROM-CHAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (to-char from-char &optional to-readtable from-readtable)
        :return-type (member t)
	)
    )

("SETF"
    (:symbol
        :package "TCL"
	)
    (:documentation-type)
    (:macro)
    (:random-syntax)
    )

("SETQ"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("SHADOW"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        :lambda-list (symbols &optional package)
        :return-type (member t)
	)
    )

("SHADOWING-IMPORT"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        :lambda-list (symbols &optional package)
        :return-type (member t)
	)
    )

("SHARED-INITIALIZE"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (object slot-names &rest initargs)
	:return-type t
	:generic-function t
	)
    )

("SHIFTF"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("SHORT-FLOAT"
    (:symbol
        :package "TCL"
	)
    (:type-name)
    (:type-specifier-list)
    )

("SHORT-FLOAT-EPSILON"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type short-float
	;; :initial-value ?
	)
    )

("SHORT-FLOAT-NEGATIVE-EPSILON"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type short-float
	;; :initial-value ?
	)
    )

("SHORT-SITE-NAME"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list ()
	:return-type simple-string
        )
    )

("SIGNAL"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (datum &rest arguments)
	:return-type null
        )
    )

("SIGNED-BYTE"
    (:symbol
        :package "TCL"
	:exists-at-runtime t
	)
    (:type-name)
    (:type-specifier-list)
    )

("SIGNUM"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (a)
        :return-type number
	)
    )

("SIMPLE-ARRAY"
    (:symbol
        :package "TCL"
	)
    (:type-name)
    (:type-specifier-list)
    )

("SIMPLE-BASE-STRING"
    (:symbol
        :package "TCL"
	)
    (:type-name)
    (:type-specifier-list)
    )

("SIMPLE-BIT-VECTOR"
    (:symbol
        :package "TCL"
	)
    (:type-name)
    (:type-specifier-list)
    )

("SIMPLE-BIT-VECTOR-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%simple-bit-vector-p t))
	)
    )

("SIMPLE-CONDITION"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("SIMPLE-CONDITION-FORMAT-ARGUMENTS"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("SIMPLE-CONDITION-FORMAT-CONTROL"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("SIMPLE-ERROR"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("SIMPLE-STRING"
    (:symbol
        :package "TCL"
	)
    (:type-name)
    (:type-specifier-list)
    )

("SIMPLE-STRING-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%simple-string-p t))
	)
    )

("SIMPLE-TYPE-ERROR"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("SIMPLE-VECTOR"
    (:symbol
        :package "TCL"
	)
    (:type-name)
    (:type-specifier-list)
    )

("SIMPLE-VECTOR-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%simple-vector-p t))
	)
    )

("SIMPLE-WARNING"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("SIN"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (radians)
        :return-type number
	:entry-name "lsin"
	:transforms ((trun:sin%rd nil))
	)
    )

("SINGLE-FLOAT"
    (:symbol
        :package "TCL"
	:exists-at-runtime t
	)
    (:type-name)
    (:type-specifier-list)
    )

("SINGLE-FLOAT-EPSILON"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type single-float
	;; :initial-value ?
	)
    )

("SINGLE-FLOAT-NEGATIVE-EPSILON"
    (:symbol
        :package "TCL"
	)
    (:constant
        :return-type single-float
	;; :initial-value ?
	)
    )

("SINH"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (a)
        :return-type number
	:entry-name "lsinh"
	)
    )

("SLEEP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (seconds)
        :return-type null
	:entry-name "lsleep"		;Unix RTL conflict
	)
    )

("SLOT-BOUNDP"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    #+translator-supports-clos
    (:function
        :lambda-list (object slot)
	:return-type t
	)
    #-translator-supports-clos
    (:function
        :unsupported t
	)
    (:random-syntax)
    )

("SLOT-EXISTS-P"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    #+translator-supports-clos
    (:function
        :lambda-list (object slot)
	:return-type t
	)
    #-translator-supports-clos
    (:function
        :unsupported t
	)
    )

("SLOT-MAKUNBOUND"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    #+translator-supports-clos
    (:function
        :lambda-list (object slot)
	:return-type t
        )
    #-translator-supports-clos
    (:function
        :unsupported t
        )
    (:random-syntax)
    )

("SLOT-MISSING"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (class object slot-name operation &optional value)
	:return-type t
	:generic-function t
	)
    )

("SLOT-UNBOUND"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (class object slot-name)
	:return-type t ; check this.  the spec allows any number of results.
	:generic-function t
	)
    )

("SLOT-VALUE"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    #+translator-supports-clos
    (:function
        :lambda-list (object slot)
	:return-type t
        )
    #-translator-supports-clos
    (:function
        :unsupported t
        )
    (:random-syntax)
    #+translator-supports-clos
    (:setf-place)
    )

("SOFTWARE-TYPE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("SOFTWARE-VERSION"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("SOME"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (predicate sequence &rest more-sequences)
        :return-type t
	)
    )

("SORT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (sequence predicate &key key)
        :return-type sequence
	)
    )

("SPACE"
    (:symbol
        :package "TCL"
	)
    (:optimize-quality)
    )

("SPECIAL"
    (:symbol
        :package "TCL"
	)
    (:declaration)
    )

("SPECIAL-OPERATOR-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	)
    )

("SPEED"
    (:symbol
        :package "TCL"
	)
    (:optimize-quality)
    )

("SQRT"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (a)
        :return-type number
	:entry-name "lsqrt"
	:transforms ((trun:sqrt%rd nil))
	)
    )

("STABLE-SORT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (sequence predicate &key key)
        :return-type sequence
	)
    )

("STANDARD"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:method-combination)
    ;; No longer a type name -- Issue STANDARD-REPERTOIRE-GRATUITOUS
    )

("STANDARD-CHAR"
    (:symbol
        :package "TCL"
	)
    (:type-name)
    )

("STANDARD-CHAR-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (char)
        :return-type t
	:transforms ((trun:%standard-char-p t))
	)
    )

("STANDARD-CLASS"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:class-name)
    (:type-name)
    )

("STANDARD-GENERIC-FUNCTION"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:class-name)
    (:type-name)
    )

("STANDARD-METHOD"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:class-name)
    (:type-name)
    )

("STANDARD-OBJECT"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:class-name)
    (:type-name)
    )

("STEP"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("STORAGE-CONDITION"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("STORE-VALUE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (value &optional condition)
	:return-type null
        )
    (:restart-name)
    )

("STREAM"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("STREAM-ELEMENT-TYPE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (stream)
        :return-type t
	)
    )

("STREAM-ERROR"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("STREAM-ERROR-STREAM"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("STREAM-EXTERNAL-FORMAT"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("STREAMP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%streamp t))
	)
    )

("STRING"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:function
        :state-changing nil
        :lambda-list (string)
        :return-type string
	)
    (:type-name)
    (:type-specifier-list)
    )

("STRING-CAPITALIZE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (string &key start end)
        :return-type string
	)
    )

("STRING-DOWNCASE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (string &key start end)
        :return-type string
	)
    )

("STRING-EQUAL"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (string1 string2 &key start1 end1 start2 end2)
        :return-type (or null fixnum)
	)
    )

("STRING-GREATERP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (string1 string2 &key start1 end1 start2 end2)
        :return-type (or null fixnum)
	)
    )

("STRING-LEFT-TRIM"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (character-bag string)
        :return-type string
	)
    )

("STRING-LESSP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (string1 string2 &key start1 end1 start2 end2)
        :return-type (or null fixnum)
	)
    )

("STRING-NOT-EQUAL"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (string1 string2 &key start1 end1 start2 end2)
        :return-type (or null fixnum)
	)
    )

("STRING-NOT-GREATERP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (string1 string2 &key start1 end1 start2 end2)
        :return-type (or null fixnum)
	)
    )

("STRING-NOT-LESSP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (string1 string2 &key start1 end1 start2 end2)
        :return-type (or null fixnum)
	)
    )

("STRING-RIGHT-TRIM"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (character-bag string)
        :return-type string
	)
    )

("STRING-STREAM"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("STRING-TRIM"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (character-bag string)
        :return-type string
	)
    )

("STRING-UPCASE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (string &key start end)
        :return-type string
	)
    )

("STRING/="
    (:symbol
        :package "TCL"
	:symbol-name "Qstring_ne"
	)
    (:function
        :lambda-list (string1 string2 &key start1 end1 start2 end2)
	:return-type (or null fixnum)
	:entry-name "string_ne"
	:object-name "Fstring_ne"
	)
    )

("STRING<"
    (:symbol
        :package "TCL"
	:symbol-name "Qstring_lt"
	)
    (:function
        :state-changing nil
        :lambda-list (string1 string2 &key start1 end1 start2 end2)
	:return-type (or null fixnum)
	:entry-name "string_lt"
	:object-name "Fstring_lt"
	)
    )

("STRING<="
    (:symbol
        :package "TCL"
	:symbol-name "Qstring_le"
	)
    (:function
        :lambda-list (string1 string2 &key start1 end1 start2 end2)
	:return-type (or null fixnum)
	:entry-name "string_le"
	:object-name "Fstring_le"
	)
    )

("STRING="
    (:symbol
        :package "TCL"
        :symbol-name "Qstring_eq"
	)
    (:function
        :state-changing nil
        :lambda-list (string1 string2 &key start1 end1 start2 end2)
	:return-type (or null fixnum)
	:entry-name "string_eq"
	:object-name "Fstring_eq"
	)
    )

("STRING>"
    (:symbol
        :package "TCL"
	:symbol-name "Qstring_gt"
	)
    (:function
        :lambda-list (string1 string2 &key start1 end1 start2 end2)
	:return-type (or null fixnum)
	:entry-name "string_gt"
	:object-name "Fstring_gt"
	)
    )

("STRING>="
    (:symbol
        :package "TCL"
	:symbol-name "Qstring_ge"
	)
    (:function
        :lambda-list (string1 string2 &key start1 end1 start2 end2)
	:return-type (or null fixnum)
	:entry-name "string_ge"
	:object-name "Fstring_ge"
	)
    )

("STRINGP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%stringp t))
	)
    )

("STRLEN"
  (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "strlen"
	:allow-multiple-uses-of-entry-name t
        :lambda-list (string)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:simple-string nil))
	:foreign-return-type :fixnum-int
	)
    )

("STRCPY"
  (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "strlen"
	:allow-multiple-uses-of-entry-name t
        :lambda-list (string string)
	:return-type string
	:foreign-protocol :macro
	:foreign-arguments ((:simple-string nil) (:simple-string nil))
	:foreign-return-type :simple-string
	)
    )

("STRUCTURE"
    (:symbol
        :package "TCL"
	)
    (:documentation-type)
    )

("STRUCTURE-CLASS"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:class-name)
    (:type-name)
    )

("STRUCTURE-OBJECT"
    (:symbol
        ;; Home package for this is TRUN, for Medfly compat.  Blech.
        :package "TRUN"
	:export ("TRUN" "TCLOS" "TCL")
	)
    (:class-name)
    (:type-name)
    )

("STYLE-WARNING"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("SUBLIS"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (alist tree &key test test-not key)
        :return-type t
	)
    )

("SUBSEQ"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (sequence start &optional end)
        :return-type sequence
	)
    (:setf-place)
    )

("SUBSETP"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (list1 list2 &key test test-not key)
        :return-type t
	)
    )

("SUBST"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (new old tree &key test test-not key)
        :return-type t
	)
    )

("SUBST-IF"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (new test tree &key key)
        :return-type t
	)
    )

("SUBST-IF-NOT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (new test tree &key key)
        :return-type t
	)
    )

("SUBSTITUTE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (newitem olditem sequence
			      &key from-end test test-not start end count key)
        :return-type sequence
	)
    )

("SUBSTITUTE-IF"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (newitem test sequence &key from-end start end count key)
        :return-type sequence
	)
    )

("SUBSTITUTE-IF-NOT"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (newitem test sequence &key from-end start end count key)
        :return-type sequence
	)
    )

("SUBTYPEP"
    (:symbol
        :package "TCL"
	:import-from nil
	)
    (:function
        :lambda-list (type1 type2 &optional env)
        :return-type (values t t)
	)
    )

("SXHASH"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
        :return-type fixnum
	)
    )

("SYMBOL"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("SYMBOL-FUNCTION"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (symbol)
	:return-type compiled-function  ;*** change if new function types added
	:transforms ((trun:%symbol-function t))
	)
    (:setf-place)
    )

("SYMBOL-MACROLET"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:special-form)
    )

("SYMBOL-NAME"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (symbol)
	:return-type string
	:transforms ((trun:%symbol-name t))
	)
    )

("SYMBOL-PACKAGE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (symbol)
	:return-type (or package null)
	:transforms ((trun:%symbol-package t))
	)
    )

("SYMBOL-PLIST"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (symbol)
	:return-type list
	:transforms ((trun:%symbol-plist t))
	)
    (:setf-place)
    )

("SYMBOL-VALUE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (symbol)
	:return-type t
	:transforms ((trun:%symbol-value t))
	)
    (:setf-place)
    )

("SYMBOLP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%symbolp t))
	)
    )

("SYNONYM-STREAM"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("SYNONYM-STREAM-SYMBOL"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("T"
    (:symbol
        :package "TCL"
	:magicp t
	:exists-at-runtime t
	)
    (:class-name)
    (:constant
        :return-type symbol
	:initial-value T
	:simple-p t
	)
    (:type-name)
    )

("TAGBODY"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("TAN"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (radians)
        :return-type number
	:entry-name "ltan"
	:transforms ((trun:tan%rd nil))
	)
    )

("TANH"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (a)
        :return-type number
	:entry-name "ltanh"
	)
    )

("TERPRI"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional output-stream)
        :return-type null
	)
    )

("THE"
    (:symbol
        :package "TCL"
	)
    (:setf-place)
    (:special-form)
    )

("THROW"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("TIME"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("TRACE"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("TRANSLATE-LOGICAL-PATHNAME"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("TRANSLATE-PATHNAME"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("TREE-EQUAL"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (x y &key test test-not)
        :return-type t
	)
    )

("TRUENAME"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (pathname)
        :return-type pathname
	)
    )

("TRUNCATE"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (a &optional divisor)
	:entry-name "ltruncate"		;C RTL conflict; HP conflict
        :return-type (values integer number)
	:transforms ((trun:floor-positive%long nil))
	)
    )

("TWO-WAY-STREAM"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("TWO-WAY-STREAM-INPUT-STREAM"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("TWO-WAY-STREAM-OUTPUT-STREAM"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("TYPE"
    (:symbol
        :package "TCL"
	)
    (:declaration)
    (:documentation-type)
    (:random-syntax)
    )

("TYPE-ERROR"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("TYPE-ERROR-DATUM"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("TYPE-ERROR-EXPECTED-TYPE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("TYPE-OF"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (object)
        :return-type t
	)
    )

("TYPECASE"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("TYPEP"
    (:symbol
        :package "TCL"
	:import-from nil
	)
    (:function
        :state-changing nil
        :lambda-list (object type &optional env)
        :return-type t
	)
    )

("UNBOUND-SLOT"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("UNBOUND-SLOT-INSTANCE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("UNBOUND-VARIABLE"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("UNDEFINED-FUNCTION"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("UNEXPORT"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        :lambda-list (symbols &optional package)
        :return-type (member t)
	)
    )

("UNINTERN"
    (:symbol
        :package "TCL"
	)
	;changed by SoftServe: removed "unsupported" flag
    (:function
        :lambda-list (symbol &optional package)
        :return-type (member t nil)
	)
	;end of changes
    )

("UNION"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (list1 list2 &key test test-not key)
	:entry-name "lunion"		;C language conflict
        :return-type list
	)
    )

("UNLESS"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("UNREAD-CHAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (character &optional input-stream)
        :return-type null
	)
    )

("UNSIGNED-BYTE"
    (:symbol
        :package "TCL"
	:exists-at-runtime t
	)
    (:type-name)
    (:type-specifier-list)
    )

("UNTRACE"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("UNUSE-PACKAGE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	#|
        :lambda-list (packages-to-use &optional package)
        :return-type (member t)
        |#
	)
    )

("UNWIND-PROTECT"
    (:symbol
        :package "TCL"
	)
    (:special-form)
    )

("UPDATE-INSTANCE-FOR-DIFFERENT-CLASS"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :lambda-list (previous current &rest initargs)
	:return-type t ; check this.  the spec allows any number of results.
	:generic-function t
	)
    )

("UPDATE-INSTANCE-FOR-REDEFINED-CLASS"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:function
        :unsupported t
	:lambda-list (object added-slots removed-slots plist &rest initargs)
	:return-type t ; check this.  the spec allows any number of results.
	:generic-function t
	)
    )

("UPGRADED-ARRAY-ELEMENT-TYPE"
    (:symbol
        :package "TCL"
	:import-from nil
	)
    (:function
	:lambda-list (type &optional env)
	:return-type t
        )
    )

("UPGRADED-COMPLEX-PART-TYPE"
    (:symbol
        :package "TCL"
	:import-from nil
	)
    (:function
        :unsupported t
	:lambda-list (type &optional env)
	:return-type t
        )
    )

("UPPER-CASE-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (char)
        :return-type t
	:transforms ((trun:%upper-case-p t))
	)
    )

("USE-PACKAGE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (packages-to-unuse &optional package)
        :return-type (member t)
	)
    )

("USE-VALUE"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
	:lambda-list (value &optional condition)
	:return-type null
        )
    (:restart-name)
    )

("USER-HOMEDIR-PATHNAME"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional host)
        :return-type (or pathname null)
	)
    )

("VALUES"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&rest args)
        :return-type (values &rest t)
	)
    (:type-specifier-list)
    )

("VALUES-LIST"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (list)
        :return-type (values &rest t)
	)
    )

("VARIABLE"
    (:symbol
        :package "TCL"
	)
    (:documentation-type)
    )

("WARN"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (datum &rest args)
        :return-type null
	:entry-name "warnn"
	)
    )

("WARNING"
    (:symbol
        :package "TCL"
	)
    (:class-name)
    (:type-name)
    )

("WHEN"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("WILD-PATHNAME-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :unsupported t
        )
    )

("WITH-ACCESSORS"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:macro)
    )

("WITH-COMPILATION-UNIT"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("WITH-CONDITION-RESTARTS"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("WITH-HASH-TABLE-ITERATOR"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("WITH-INPUT-FROM-STRING"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("WITH-OPEN-FILE"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("WITH-OPEN-STREAM"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("WITH-OUTPUT-TO-STRING"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("WITH-PACKAGE-ITERATOR"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("WITH-SIMPLE-RESTART"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

("WITH-SLOTS"
    (:symbol
        :package "TCLOS"
	:export ("TCLOS" "TCL")
	)
    (:macro)
    )

("WITH-STANDARD-IO-SYNTAX"
    (:symbol
        :package "TCL"
	)
    (:macro)
    )

;;; CLtL2 specifies five new keyword arguments (READABLY, RIGHT-MARGIN,
;;; MISER-WIDTH, LINES, and PPRINT-DISPATCH) for the WRITE function;
;;; they are currently not supported

("WRITE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object &key stream escape radix base circle pretty level
			     length case gensym array)
	:entry-name "lwrite"		;stdio conflict
	:return-type t
	)
    )

("WRITE-BYTE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (i binary-output-stream)
        :return-type integer
	)
    )

("WRITE-CHAR"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (character &optional output-stream)
        :return-type character
	)
    )

("WRITE-LINE"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (string &optional output-stream &key start end)
        :return-type string
	)
    )

("WRITE-STRING"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (string &optional output-stream &key start end)
        :return-type string
	)
    )

;;; CLtL2 specifies five new keyword arguments (READABLY, RIGHT-MARGIN,
;;; MISER-WIDTH, LINES, and PPRINT-DISPATCH) for the WRITE-TO-STRING function;
;;; they are currently not supported

("WRITE-TO-STRING"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (object &key escape radix base circle pretty level length
			     case gensym array)
	:return-type simple-string
	)
    )

("Y-OR-N-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional format-string &rest arguments)
        :return-type t
	:entry-name "y_or_n_pn"
	)
    )

("YES-OR-NO-P"
    (:symbol
        :package "TCL"
	)
    (:function
        :lambda-list (&optional format-string &rest arguments)
        :return-type t
	:entry-name "yes_or_no_pn"
	)
    )

("ZEROP"
    (:symbol
        :package "TCL"
	)
    (:function
        :state-changing nil
        :lambda-list (a)
        :return-type t
	:transforms ((trun:zerop% :no-longs)
		     (trun:zerop%long nil)
		     (trun:zerop%single :single)
		     (trun:zerop%double nil))
	)
    )



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Symbols in the TCLOS package but not in the TCL package
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Symbols with the comment NON-ANSI-STANDARD-CLOS are symbols from a list
;;; agreed upon between Symbolics an Lucid as being MOP extensions exported
;;; from the CLOS package.  They are listed in a message from Moon to the 
;;; Common-Lisp-Object-System@mcc.com, dated 4-March-90.

#+translator-supports-clos
("CLASS-DEFAULT-INITARGS"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (class)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("CLASS-DIRECT-DEFAULT-INITARGS"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (class)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("CLASS-DIRECT-SLOTS"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (class)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("CLASS-DIRECT-SUBCLASSES"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (class)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("CLASS-DIRECT-SUPERCLASSES"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (class)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("CLASS-PRECEDENCE-LIST"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (class)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("CLASS-PROTOTYPE"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (class)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("CLASS-SLOTS"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (class)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("COMPUTE-EFFECTIVE-METHOD"
    (:symbol
        :package "TCLOS"
	:import-from "HOST-CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    ;; This function is called to determine the effective method metaobject
    ;; from a sorted list of method metaobjects.
    ;; [Note: This description differs from the MOP specification, which has
    ;; this function returning an effective method form.]
    (:function
        :entry-name "compute_effective_method"
        :lambda-list (generic-function method-combination methods)
	:return-type trun:effective-method
	:generic-function t
	)
    )

#+translator-supports-clos
("FORWARD-REFERENCED-CLASS"
    (:symbol
        :package "TCLOS"
	:import-from "HOST-CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    (:class-name)
    (:type-name)
    )

#+translator-supports-clos
("FUNCALLABLE-STANDARD-CLASS"
    (:symbol
        :package "TCLOS"
	:import-from "HOST-CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    (:class-name)
    (:type-name)
    )

#+translator-supports-clos
("GENERIC-FUNCTION-ARGUMENT-PRECEDENCE-ORDER"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (generic-function)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("GENERIC-FUNCTION-DECLARATIONS"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (generic-function)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("GENERIC-FUNCTION-INITIAL-METHODS"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (generic-function)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("GENERIC-FUNCTION-LAMBDA-LIST"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (generic-function)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("GENERIC-FUNCTION-METHOD-CLASS"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (generic-function)
	:return-type class
	:generic-function t
	)
    )

#+translator-supports-clos
("GENERIC-FUNCTION-METHOD-COMBINATION"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (generic-function)
	:return-type method-combination
	:generic-function t
	)
    )

#+translator-supports-clos
("GENERIC-FUNCTION-METHODS"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (generic-function)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("GENERIC-FUNCTION-NAME"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (generic-function)
	:return-type t
	:generic-function t
	)
    )

#+translator-supports-clos
("METHOD-FUNCTION"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (method)
	:return-type function
	:generic-function t
	)
    )

#+translator-supports-clos
("METHOD-GENERIC-FUNCTION"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (method)
	:return-type generic-function
	:generic-function t
	)
    )

#+translator-supports-clos
("METHOD-LAMBDA-LIST"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (method)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("METHOD-SLOT-NAME"
   (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
   (:function
        :lambda-list (method)
	:return-type symbol
	:generic-function t
	)
    )

#+translator-supports-clos
("METHOD-SPECIALIZERS"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (method)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("SLOT-BOUNDP-USING-CLASS"
    (:symbol
        :package "TCLOS"
	:import-from "HOST-CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (class object slot-name)
	:return-type t
	:generic-function t
	)
    )

#+translator-supports-clos
("SLOT-DEFINITION"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:class-name)
    (:type-name)
    )

#+translator-supports-clos
("SLOT-DEFINITION-ALLOCATION"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (slotd)
	:return-type t
	:generic-function t
	)
    )

#+translator-supports-clos
("SLOT-DEFINITION-INITARGS"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (slotd)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("SLOT-DEFINITION-INITFORM"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (slotd)
	:return-type t
	:generic-function t
	)
    )

#+translator-supports-clos
("SLOT-DEFINITION-INITFUNCTION"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (slotd)
	:return-type function
	:generic-function t
	)
    )

#+translator-supports-clos
("SLOT-DEFINITION-NAME"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (slotd)
	:return-type symbol
	:generic-function t
	)
    )

#+translator-supports-clos
("SLOT-DEFINITION-READERS"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (slotd)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("SLOT-DEFINITION-TYPE"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (slotd)
	:return-type t
	:generic-function t
	)
    )

#+translator-supports-clos
("SLOT-DEFINITION-WRITERS"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (slotd)
	:return-type list
	:generic-function t
	)
    )

#+translator-supports-clos
("SLOT-MAKUNBOUND-USING-CLASS"
    (:symbol
        :package "TCLOS"
	:import-from "HOST-CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (class object slot)
	:return-type t
	:generic-function t
	)
    )

#+translator-supports-clos
("SLOT-VALUE-USING-CLASS"
    (:symbol
        :package "TCLOS"
	:import-from "HOST-CLOS"
	;; NON-ANSI-STANDARD-CLOS
	)
    (:function
        :lambda-list (class object slot)
	:return-type t
	:generic-function t
	)
    (:setf-function
        :lambda-list (value class object slot)
	:return-type t
	:generic-function t
	)
    (:setf-place
        :setf-function t
	)
    )

;;; Removed, pending further discussion on common-lisp-object-system list.
;#+translator-supports-clos
;("SPECIALIZER-DIRECT-GENERIC-FUNCTIONS"
;    (:symbol
;        :package "TCLOS"
;        :import-from "HOST-CLOS"
;	;; NON-ANSI-STANDARD-CLOS
;	)
;    )

;;; Removed, pending further discussion on common-lisp-object-system list.
;#+translator-supports-clos
;("SPECIALIZER-DIRECT-METHODS"
;    (:symbol
;        :package "TCLOS"
;        :import-from "HOST-CLOS"
;	;; NON-ANSI-STANDARD-CLOS
;	)
;    )

#+translator-supports-clos
("STANDARD-ACCESSOR-METHOD"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:class-name)
    (:type-name)
    )

#+translator-supports-clos
("STANDARD-READER-METHOD"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:class-name)
    (:type-name)
    )

#+translator-supports-clos
("STANDARD-SLOT-DEFINITION"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:class-name)
    (:type-name)
    )

#+translator-supports-clos
("STANDARD-WRITER-METHOD"
    (:symbol
        :package "TCLOS"
	:import-from nil
	;; NON-ANSI-STANDARD-CLOS
	)
    (:class-name)
    (:type-name)
    )




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Symbols in the TX package
;;;
;;;;;;;;;;;;;;;;;;;;;;;;n;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Hack, so we can translate LOOP forms using Lucid's expander
#+(and lcl4.0 (not translating))
("LIST-ERROR"
    (:symbol
        :package "TX"
	:import-from "SYSTEM"
	:exists-at-runtime nil
	)
    (:function
        :entry-name "list_error"
        :lambda-list (thing)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments ((:object nil))
	)
    )

;; Gensym-requested Memory Management extentions

("ALLOCATE-MEMORY-TO-TARGET"
 (:symbol
         :package "TX"
	 :import-from nil
	 )
 (:function
      :lambda-list (area-name target)
      :return-type t
      )
 )

("AREA-MEMORY-LIMIT"
 (:symbol
         :package "TX"
	 :import-from nil
	 )
 (:function
      :lambda-list (area-name)
      :return-type t
      )
 )

("AREA-MEMORY-USED"
 (:symbol
         :package "TX"
	 :import-from nil
	 )
 (:function
      :lambda-list (area-name)
      :return-type t
      )
 )

("AREA-TARGET-SIZE"
 (:symbol
         :package "TX"
	 :import-from nil
	 )
 (:function
      :lambda-list (area-name)
      :return-type t
      )
 )

("AREA-MEMORY-LIMIT-AS-FLOAT"
 (:symbol
         :package "TX"
	 :import-from nil
	 )
 (:function
      :lambda-list (area-name)
      :return-type double-float
      )
 )

("AREA-MEMORY-USED-AS-FLOAT"
 (:symbol
         :package "TX"
	 :import-from nil
	 )
 (:function
      :lambda-list (area-name)
      :return-type double-float
      )
 )

("AREA-TARGET-SIZE-AS-FLOAT"
 (:symbol
         :package "TX"
	 :import-from nil
	 )
 (:function
      :lambda-list (area-name)
      :return-type double-float
      )
 )

("BIGNUM-LENGTH"
 (:symbol
         :package "TX"
	 :import-from nil
	 )
 (:function
      :lambda-list (integer)
      :return-type fixnum
      )
 )

("STORE-BIGNUM"
 (:symbol
         :package "TX"
	 :import-from nil
	 )
 (:function
      :lambda-list (value target)
      :return-type boolean
      )
 )

("COPY-OF-BIGNUM"
 (:symbol
         :package "TX"
	 :import-from nil
	 )
 (:function
      :lambda-list (value)
      :return-type integer
      )
 )

("TOTAL-MEMORY-USED"
 (:symbol
         :package "TX"
	 :import-from nil
	 )
 (:function
      :lambda-list ()
      :return-type t
      )
 )

("AUGMENT-ENVIRONMENT"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :unsupported t
        )
    )

("CONSTANT-VALUE"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :unsupported t
	)
    )

("CLOSED-VARIABLE"
    (:symbol
        :package "TX"
	:import-from nil
	)
    )

("DECLARATION-INFORMATION"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :unsupported t
        )
    )

("DEFINE-DECLARATION"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:macro)
    )

("DEFINE-SETF-METHOD"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:macro)
    )

("ENCLOSE"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :unsupported t
        )
    )

("FUNCTION-INFORMATION"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :unsupported t
        )
    )

("GET-SETF-METHOD"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :unsupported t
        )
    )

("GET-SETF-METHOD-MULTIPLE-VALUE"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :unsupported t
        )
    )

#+translator-supports-thread
("GLOBAL-VARIABLE"
    (:symbol
        :package "TX"
        :import-from nil
	)
    (:declaration)
    )

("PARSE-DECLARATIONS"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :unsupported t
	)
    )

("PARSE-MACRO"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :unsupported t
        )
    )

("SET-DECLARATION-INFORMATION"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :unsupported t
        )
    )

("SPECIAL-FORM-P"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:function
        :unsupported t
        )
    )

("STRING-CHAR"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:type-name)
    (:random-syntax)
    )

("UNREAD-VARIABLE"
    (:symbol
        :package "TX"
	:import-from nil
	)
    )

("UNWRITTEN-VARIABLE"
    (:symbol
        :package "TX"
	:import-from nil
	)
    )

("VARIABLE-INFORMATION"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :unsupported t
        )
    )

;;; Extensions

;;; Note:  %POINTER and %SYSINT do "exist at runtime"; they're
;;;        GCLISP extensions.

#|
("%POINTER"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:entry-name "gcl_pointer"
	:lambda-list (object)
	:return-type (unsigned-byte 32)
	:transforms ((trun:%%pointer t))
	)
    )

("%SYSINT"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:entry-name "gcl_sysint"
	:lambda-list (a b c d e &optional f g)   ;; ?
	:return-type t          ;; ?
	:transforms ((trun:%%sysint t))
	)
    )

("ARRAY-LENGTH"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (array)
	:return-type fixnum
	)
    )
|#

("ASSQ"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (item a-list)
	:return-type list
	)
    )

("C-LINES"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:special-form)
    )

#|
("CD"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (path)
	:return-type pathname
	)
    )

("CHAR*-TO-STRING"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (pointer)
	:return-type simple-string
	)
    )

("CLOSE-ALL-FILES"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list ()
	:return-type t   ;; ?
	)
    )

("COPY-ARRAY-CONTENTS"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (to from)  ;; ?
	:return-type array      ;; ?
	)
    )
|#

("COPY-FOREIGN-POINTER"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:function
        :lambda-list (fp)
	:return-type t
	)
    )

("CPP-CONDITIONAL"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:special-form)
    )

("DEF-FOREIGN-CALLABLE"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:macro)
    )

("DEF-FOREIGN-FUNCTION"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:macro)
    )

("DEF-FOREIGN-STRUCT"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:macro)
    )

("DEF-FOREIGN-SYNONYM-TYPE"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:macro)
    )

("DEFINED-FOREIGN-TYPE-P"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:macro)
    )

("DELQ"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (item list)
	:return-type list
	)
    )

#|
("DOS"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (&optional command)
	:return-type fixnum    ;; ?
	)
    )
|#

("EVAL-RUN"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :lambda-list (form)
        :return-type (values &rest t)
	)
    )

#|
("EXIT"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list ()
	:return-type t
	)
    )

("FILE-INFO"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (path)
	:return-type t   ;; ?
	)
    )
|#

("FOREIGN-AREF"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:function
        :lambda-list (array &rest indices)
	:return-type t
	)
    (:setf-function
        :lambda-list (new-value array &rest subscripts)
	:return-type t
	:entry-name "set_foreign_aref"
	)
    (:setf-place
        :setf-function t
	)
    )

("FOREIGN-POINTER"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:type-name)
    (:class-name)
    )

("FOREIGN-POINTER-ADDRESS"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:function
        :lambda-list (object)
	:argument-types (tx:foreign-pointer)
	:return-type (unsigned-byte #+x86-64 64 #-x86-64 32)
	:transforms ((tx:%foreign-pointer-address t))
        )
    )

("SET-FOREIGN-POINTER-ADDRESS"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :lambda-list (object address)
	:argument-types (tx:foreign-pointer (unsigned-byte #+x86-64 64 #-x86-64 32))
	:return-type (unsigned-byte #+x86-64 64 #-x86-64 32)
	:transforms ((tx:%set-foreign-pointer-address t))
        )
    )

("%FOREIGN-POINTER-ADDRESS"
    (:symbol
	:package "TX"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FOREIGN_POINTER_ADDRESS"
	:lambda-list (foreign-pointer)
	:argument-types (tx:foreign-pointer)
	:return-type (unsigned-byte #+x86-64 64 #-x86-64 32)
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type #+x86-64 :unsigned-64bit #-x86-64 :unsigned-32bit))

("%SET-FOREIGN-POINTER-ADDRESS"
    (:symbol
        :package "TX"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (foreign-pointer new-value)
	:argument-types (tx:foreign-pointer
			  (unsigned-byte #+x86-64 64 #-x86-64 32))
	:return-type (unsigned-byte #+x86-64 64 #-x86-64 32)
	:foreign-protocol :lvalue-setter
	:lvalue tx:%foreign-pointer-address
	:foreign-arguments ((:object nil)
			    (#+x86-64 :unsigned-64bit #-x86-64 :unsigned-32bit nil))
	:foreign-return-type #+x86-64 :unsigned-64bit #-x86-64 :unsigned-32bit))

("FOREIGN-POINTER-P"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:function
        :lambda-list (object)
	:return-type t
        )
    )

("FOREIGN-POINTER-TYPE"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((tx:%foreign-pointer-type t))
        )
    )

("SET-FOREIGN-POINTER-TYPE"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :lambda-list (object new-type)
	:return-type t
	:transforms ((tx:%set-foreign-pointer-type t))
        )
    )

("FOREIGN-POINTER-TYPE-P"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((tx:%foreign-pointer-p t))
        )
    )

("%FOREIGN-POINTER-TYPE"
    (:symbol
	:package "TX"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FOREIGN_POINTER_TYPE"
	:lambda-list (foreign-pointer)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SET-FOREIGN-POINTER-TYPE"
    (:symbol
        :package "TX"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (foreign-pointer new-value)
	:return-type t
	:foreign-protocol :lvalue-setter
	:lvalue tx:%foreign-pointer-type
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%FOREIGN-POINTER-P"
    (:symbol
        :package "TX"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "FOREIGN_POINTER_P"
	:lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("FOREIGN-SIZE-OF"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:function
        :lambda-list (object)
	:return-type (unsigned-byte 32)
        )
    )

("FOREIGN-STRING-VALUE"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:function
        :lambda-list (object)
	:return-type string
        )
    )

("FOREIGN-TYPE"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:type-name)
    (:class-name)
    (:function
        :lambda-list (object &optional error-p)
	:return-type t
	:entry-name "get_foreign_type"
	:transforms ((tx:%foreign-type t))
        )
    )

("PRIMITIVE-FOREIGN-TYPE"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:type-name)
    (:class-name)
    )

("ARRAY-FOREIGN-TYPE"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:type-name)
    (:class-name)
    )

("STRUCTURE-FOREIGN-TYPE"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:type-name)
    (:class-name)
    )

("POINTER-FOREIGN-TYPE"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:type-name)
    (:class-name)
    )


("%FOREIGN-TYPE"
    (:symbol
	:package "TX"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FOREIGN_TYPE"
	:lambda-list (object)
	:return-type tx:foreign-type
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("%FOREIGN-TYPE2"
    (:symbol
	:package "TX"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FOREIGN_TYPE2"
	:lambda-list (object error-p)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t)(:object nil))
	:foreign-return-type :object
	)
    )

("FOREIGN-TYPEP"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:function
        :lambda-list (foreign-pointer foreign-type)
	:return-type t
        )
    )

("FOREIGN-TYPE-NAME"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:function
        :lambda-list (foreign-type)
	:return-type t
        )
    )

("FOREIGN-TYPE-SIZE"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:function
        :lambda-list (object)
	:return-type fixnum
        )
    )

("FOREIGN-TYPE-MODULUS"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:function
        :lambda-list (object)
	:return-type fixnum
        )
    )


("FOREIGN-TYPE-REMAINDER"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:function
        :lambda-list (object)
	:return-type fixnum
        )
    )

("FOREIGN-VALUE"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:function
        :lambda-list (foreign-pointer)
	:return-type t
        )
    )

("UNDEFINE-FOREIGN-TYPE"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:function
        :lambda-list (foreign-type)
	:return-type t
        )
    )

("DEFINE-FOREIGN-SYNONYM-TYPE"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :lambda-list (new-foreign-type-name foreign-type)
	:return-type t
        )
    )

("FOREIGN-TYPE-P"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((tx:%foreign-type-p t))
        )
    )

("%FOREIGN-TYPE-P"
    (:symbol
        :package "TX"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "FOREIGN_TYPE_P"
	:lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("SET-FOREIGN-STRING-VALUE"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :lambda-list (object string)
	:return-type string
        )
    )

("SET-FOREIGN-VALUE"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :lambda-list (foreign-pointer value)
	:return-type t
        )
    )

("MAKE-STRUCT-FOREIGN-TYPE"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :lambda-list (name size modulus remainder)
	:return-type t
        )
    )

("FLATSIZE"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (object)
	:return-type fixnum
	)
    )

("FREE-FOREIGN-POINTER"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:function
        :lambda-list (foreign-pointer)
	:return-type t
        )
    )

#|
("GETENV"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
        :entry-name "lgetenv"
	:lambda-list (variable)
	:return-type (or string null)
	)
    )
|#

("IFN"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:macro)
    )

("INCLUDE-AT-RUNTIME"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:declaration)
    )

("LIST-NREVERSE"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (list)
	:return-type list
	)
    )

("LIST-REVERSE"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (list)
	:return-type list
	)
    )

("LOAD-RUN"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:function
        :lambda-list (form &key verbose print if_does_not_exist)
        :return-type t
	)
    )

#|
("LSH"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (i shift)
	:return-type integer
	)
    )
|#

("MAKE-FOREIGN-POINTER"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (&key address type)
	:return-type t
	)
    )

("MAKE-FOREIGN-POINTER-INTERNAL"
    (:symbol
	:package "TX"
	:import-from nil
	)
    (:function
	:state-changing nil
	:lambda-list (address type)
	:return-type tx:foreign-pointer
	:foreign-protocol :macro
	:foreign-arguments ((:unsigned-32bit nil)(:object nil))
	:foreign-return-type :object
	)
    )

("MALLOC-FOREIGN-POINTER"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (&key type)
	:return-type t
	)
    )

#|
("MAKE-WINDOW-STREAM"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (&key size position)
	:return-type t
	)
    )
|#

("MEMQ"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (item list)
	:return-type list
	:transforms ((trun:%member-eq t))
	)
    )

("NCONS"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (item)
	:return-type cons
	)
    )

#|
("NEQ"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (x y)
	:return-type t
	:transforms ((trun:%neq t))
	)
    )

("NEQL"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (x y)
	:return-type t
	:transforms ((trun:%neql t))
	)
    )
|#

("NONCONSING"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:declaration)
    )


("NONRELOCATING"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:declaration)
    )

("NON-STATE-CHANGING"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:declaration)
    )

("NON-STATE-USING"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:declaration)
    )

("OMIT-AT-RUNTIME"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:declaration)
    )

#|
("PWD"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (path)
	:return-type pathname
	)
    )

("QUIT"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list ()
	:return-type nil
	)
    )

("RPLACB"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (cell1 cell2)
	:return-type cons
	:transforms ((trun:%rplacb t))
	)
    )

("SEND-FILE"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (a b &optional c d)  ;; ?
	:return-type t  ;; ?
	)
    )

("SEND-WINDOW"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (a b &optional c d)  ;; ?
	:return-type t  ;; ?
	)
    )

("SHELL"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (command)
	:return-type integer       ;; fixnum?
	:entry-name "tx_shell"
	)
    )

("STREAM-DEFAULT-HANDLER"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (a b &optional c d e)  ;; ?
	:return-type t  ;; ?
	)
    )
|#

("STATIONARY-OBJECT-P"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (object)
	:return-type t
	)
    )

("STRING-APPEND"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (&rest strings)
	:return-type string
	:entry-name "string_appendn"
	)
    )

#|
("STRING-SEARCH"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (a b &optional c d)  ;; ?
	:return-type t  ;; ?
	)
    )

("STRING-TO-CHAR*"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (string)
	:return-type (unsigned-byte 32)
	:entry-name "ff_string_to_char_star"
	)
    )
|#

("TOPLEVEL-C-LINES"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:special-form)
    )

("TYPED-FOREIGN-AREF"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:function
        :lambda-list (foreign-type array &rest indices)
	:return-type t
	)
    )

("%TYPED-FOREIGN-AREF"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::csubscripting
        :lambda-list (object index)
	:foreign-protocol :operator
	:foreign-arguments (((:pointer (:array :int)) nil) (:fixnum nil))
	:foreign-return-type :int
	)
    )

("WITH-DYNAMIC-ALLOCATION"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:macro)
    )

("WITH-DYNAMIC-AREA"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:macro)
    )

("WITH-STATIC-AREA"
    (:symbol
        :package "TX"
	:import-from "HOSTX"
	)
    (:macro)
    )

("WITH-LOCAL-ALLOCATION"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:special-form)
    )


("WITH-LOCAL-AREA"
    (:symbol
        :package "TX"
	:import-from nil
	)
    (:macro)
    )

("XOR"
    (:symbol
	:package "TX"
	:import-from "HOSTX"
	)
    (:function
	:lambda-list (&rest args)
	:return-type t
	)
    )

;; Gensym-requested Multi-Threading extensions (PortableThreads compatible)
;; For SymScale Project (Versata)
;;
;; Author: Chun Tian (binghe) <binghe.lisp@gmail.com>

#+translator-supports-thread
("ALL-THREADS"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
        :state-changing nil
        :lambda-list ()
	:entry-name "all_threads"
	:object-name "Fall_threads"
	:argument-types ()
	:return-type list
	)
    )

#+translator-supports-thread
("ATOMIC-DECF"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:macro)
    )

#+translator-supports-thread
("ATOMIC-DECF&"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:macro)
    )

#+translator-supports-thread
("ATOMIC-INCF"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:macro)
    )

#+translator-supports-thread
("ATOMIC-INCF&"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:macro)
    )

#+translator-supports-thread
("ATOMIC-INCFF-SYMBOL-VALUE"
    (:symbol
	:package "TX"
	:import-from nil
	)
    (:function
	:lambda-list (symbol delta)
	:entry-name "atomic_incff_symval"
	:object-name "Fatomic_incff_symval"
	:argument-types (symbol fixnum)
	)
    )

#+translator-supports-thread
("ATOMIC-INCFF-CAR"
    (:symbol
	:package "TX"
	:import-from nil
	)
    (:function
	:lambda-list (cons delta)
	:entry-name "atomic_incff_car"
	:object-name "Fatomic_incff_car"
	:argument-types (list fixnum)
	)
    )

#+translator-supports-thread
("ATOMIC-INCFF-CDR"
    (:symbol
	:package "TX"
	:import-from nil
	)
    (:function
	:lambda-list (cons delta)
	:entry-name "atomic_incff_cdr"
	:object-name "Fatomic_incff_cdr"
	:argument-types (list fixnum)
	)
    )

#+translator-supports-thread
("ATOMIC-INCFF-SIMPLE-VECTOR-SLOT"
    (:symbol
	:package "TX"
	:import-from nil
	)
    (:function
	:lambda-list (vector index delta)
	:entry-name "atomic_incff_svslot"
	:object-name "Fatomic_incff_svslot"
	:argument-types (simple-vector fixnum fixnum)
	)
    )

#+translator-supports-thread
("ATOMIC-EXCHANGE"
    (:symbol
	:package "TX"
	:import-from nil
	)
    (:macro)
    )

#+translator-supports-thread
("ATOMIC-EXCHANGE-SYMBOL-VALUE"
    (:symbol
	:package "TX"
	:import-from nil
	)
    (:function
	:lambda-list (symbol value)
	:entry-name "atomic_exchange_symval"
	:object-name "Fatomic_exchange_symval"
	:argument-types (symbol t)
	)
    )

#+translator-supports-thread
("CONDITION-VARIABLE-BROADCAST"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
        :lambda-list (condition-variable)
        :entry-name "condition_variable_broadcast"
        :object-name "Fcondition_variable_broadcast"
        :argument-types (t)
        :return-type t
        )
    )

#+translator-supports-thread
("CONDITION-VARIABLE-SIGNAL"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
        :lambda-list (condition-variable)
        :entry-name "condition_variable_signal"
        :object-name "Fcondition_variable_signal"
        :argument-types (t)
        :return-type t
        )
    )

#+translator-supports-thread
("CONDITION-VARIABLE-WAIT"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
        :lambda-list (condition-variable)
        :entry-name "condition_variable_wait"
        :object-name "Fcondition_variable_wait"
        :argument-types (t)
        :return-type t
        )
    )

#+translator-supports-thread
("CONDITION-VARIABLE-WAIT-WITH-TIMEOUT"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
        :lambda-list (condition-variable timeout)
        :entry-name "condition_variable_wait_with_timeout"
        :object-name "Fcondition_variable_wait_with_timeout"
        :argument-types (t t)
        :return-type t
        )
    )

#+translator-supports-thread
("CURRENT-THREAD"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
        :lambda-list ()
        :entry-name "current_thread"
        :object-name "Fcurrent_thread"
        :return-type t
        )
    )

#+translator-supports-thread
("KILL-THREAD"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
        :lambda-list (thread)
        :entry-name "kill_thread"
        :object-name "Fkill_thread"
        :argument-types (t)
        :return-type t
        )
    )

#+translator-supports-thread
("MAKE-ATOMIC-REFERENCE"
    (:symbol
	:package "TX"
	:import-from nil
	)
    (:function
	:lambda-list (object mark)
	:entry-name "make_atomic_reference"
	:object-name "Fmake_atomic_reference"
	:argument-types (t boolean)
	:return-type t
	)
    )

#+translator-supports-thread
("ATOMIC-REFERENCE-OBJECT"
    (:symbol
	:package "TX"
	:import-from nil
	)
    (:function
	:entry-name "ATOMIC_REF_OBJECT"
	:lambda-list (reference)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    (:setf-function
	:lambda-list (new-object reference)
	:return-type t
	)
    (:setf-place
	:setf-function t
	)
    )

#+translator-supports-thread
("ATOMIC-REFERENCE-MARK"
    (:symbol
	:package "TX"
	:import-from nil
	)
    (:function
	:entry-name "ATOMIC_REF_MARK"
	:lambda-list (reference)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    (:setf-function
	:lambda-list (new-mark reference)
	:return-type t
	)
    (:setf-place
	:setf-function t
	)
    )

#+translator-supports-thread
("ATOMIC-REFERENCE-EQUAL"
    (:symbol
	:package "TX"
	:import-from nil
	)
    (:function
	:state-changing nil
	:nonconsing t
	:entry-name "ATOMIC_REF_EQUAL"
	:lambda-list (r1 r2)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

#+translator-supports-thread
("MAKE-CONDITION-VARIABLE"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
        :lambda-list (&key lock)
        :entry-name "make_condition_variable"
        :object-name "Fmake_condition_variable"
        :argument-types (&key t)
        :return-type t
        )
    )

#+translator-supports-thread
("MAKE-LOCK"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
        :lambda-list (&key name)
        :entry-name "make_lock"
        :object-name "Fmake_lock"
        :argument-types (&key string)
        :return-type t
        )
    )

#+translator-supports-thread
("MAKE-RECURSIVE-LOCK"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
        :lambda-list (&key name)
        :entry-name "make_recursive_lock"
        :object-name "Fmake_recursive_lock"
        :argument-types (&key string)
        :return-type t
        )
    )

#+translator-supports-thread
("RUN-IN-THREAD"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
        :lambda-list (thread function &rest args)
        :return-type t
        )
    )

#+translator-supports-thread
("SPAWN-THREAD"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
        :lambda-list (name function &rest args)
	:entry-name "spawn_thread"
	:object-name "Fspawn_thread"
	:argument-types (string t &rest t)
        :return-type t
        )
    )

#+translator-supports-thread
("SYMBOL-VALUE-IN-THREAD"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
	:state-changing nil
        :lambda-list (symbol thread)
        :return-type t
	:transforms ((trun:%symbol-value-in-thread t))
        )
    (:setf-function
        :lambda-list (new-value symbol &optional thread)
	:return-type t
        :transforms ((trun:%set-symbol-value-in-thread t))
	)
    (:setf-place
	:setf-function t
	)
    )

#+translator-supports-thread
("THREAD-ALIVE-P"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
        :lambda-list (thread)
        :return-type t
        )
    )

#+translator-supports-thread
("THREADP"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
        :lambda-list (thread)
        :return-type t
        )
    )

#+translator-supports-thread
("THREAD-HOLDS-LOCK-P"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
        :lambda-list (lock)
        :return-type boolean
        )
    )

#+translator-supports-thread
("THREAD-NAME"
    (:symbol
        :package "TX"
	:import-from "PORTABLE-THREADS"
	)
    (:function
	:entry-name "SI_THREAD_NAME"
	:lambda-list (thread)
	:return-type t
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    (:setf-function
        :lambda-list (new-name thread)
	:return-type t
	)
    (:setf-place
        :setf-function t
        )
    )

#+translator-supports-thread
("THREAD-WHOSTATE"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
        :lambda-list (thread)
        :return-type string
        )
    (:setf-function
        :lambda-list (whostate thread)
        :return-type string
        )
    (:setf-place
        :setf-function t
        )
    )

#+translator-supports-thread
("THREAD-YIELD"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:function
        :lambda-list ()
	:entry-name "thread_yield"
	:object-name "Fthread_yield"
	:argument-types ()
        :return-type t
        )
    )

#+translator-supports-thread
("WITH-LOCK-HELD"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:macro)
    )

#+translator-supports-thread
("WITH-TIMEOUT"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:special-form)
    )

#+translator-supports-thread
("WITHOUT-LOCK-HELD"
    (:symbol
        :package "TX"
        :import-from "PORTABLE-THREADS"
        )
    (:special-form)
    )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Symbols in the TRUN package
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; This list may not be complete -- there might still be some calls to
;;; helper functions that appear in macro expansions that haven't been 
;;; added to this list yet.


("%ALPHA-CHAR-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "ALPHA_CHAR_P"
        :lambda-list (char)
	:argument-types (character)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("%ALPHANUMERICP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "ALPHANUMERICP"
        :lambda-list (object)
	:argument-types (character)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("%BOUNDP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "BOUNDP"
        :lambda-list (symbol)
	:argument-types (symbol)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("%BREAK"
     (:symbol
	  :package "TRUN"
	  :import-from nil
	  :exists-at-runtime nil
	  )
     (:function
          :entry-name "lbreak"
	  :lambda-list (count string &rest format-arguments)
	  :return-type t ; The c code returns T, but should return NIL
	  :foreign-protocol :foreign-arguments-function
	  :foreign-arguments ((:int nil) (:string nil))
	  :foreign-return-type :object
	  )
     )

("%BYTE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "BYTE"
        :lambda-list (size position)
	:argument-types (fixnum fixnum) ; unsafe otherwise
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%BYTE-POSITION"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "BYTE_POSITION"
        :lambda-list (bytespec)
	:argument-types (fixnum)
	:return-type integer
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%BYTE-SIZE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "BYTE_SIZE"
        :lambda-list (bytespec)
	:argument-types (fixnum)
	:return-type integer
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%CERROR"
     (:symbol
	  :package "TRUN"
	  :import-from nil
	  :exists-at-runtime nil
	  )
     (:function
          :entry-name "cerror"
	  :lambda-list (count continue-string string &rest format-arguments)
	  :return-type null
	  :foreign-protocol :foreign-arguments-function
	  :foreign-arguments ((:int nil) (:string nil) (:string nil))
	  :foreign-return-type :object
	  )
     )

("%CHAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "CHAR"
        :lambda-list (string index)
	:return-type character
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%CHAR-CODE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "CHAR_CODE"
        :lambda-list (char)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
        )
    )

("%CHAR-DOWNCASE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "CHAR_DOWNCASE"
        :lambda-list (char)
        :return-type character
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("%CHAR-INT"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "CHAR_INT"
        :lambda-list (char)
        :return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%CHAR-UPCASE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "CHAR_UPCASE"
        :lambda-list (char)
        :return-type character
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("%CHAR*-TO-STRING"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "FF_CHAR_POINTER_TO_STRING"
	:lambda-list (pointer)
	:return-type simple-string
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("%CHARACTERP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "CHARACTERP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("%COBJECTP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "COBJECTP"
	:lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%CODE-CHAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "CODE_CHAR"
        :lambda-list (code)
	:return-type character
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%COMPILED-FUNCTION-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "COMPILED_FUNCTION_P"
        :lambda-list (object)
	:foreign-protocol :macro
	:return-type t
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%COMPLEXP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:nonconsing t
        :entry-name "COMPLEXP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%DENOMINATOR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DENOMINATOR"
        :lambda-list (rational)
        :return-type integer
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("%EQ"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t	
        :entry-name "EQ"
        :lambda-list (x y)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("%EQL-FAST-1"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "EQ"
	:allow-multiple-uses-of-entry-name t
        :lambda-list (x y)
	:return-type t
	:foreign-protocol :macro
	:argument-types ((or fixnum character array symbol cons package pathname stream) t)
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("%EQL-FAST-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "EQ"
	:allow-multiple-uses-of-entry-name t
        :lambda-list (x y)
	:return-type t
	:foreign-protocol :macro
	:argument-types (t (or fixnum character array symbol cons package pathname stream))
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("%EQL"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "EQL"
        :lambda-list (x y)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("%EQUAL"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "EQUAL"
        :lambda-list (x y)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("%EQUALP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "EQUALP"
        :lambda-list (x y)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("%ERROR"
     (:symbol
	  :package "TRUN"
	  :import-from nil
	  :exists-at-runtime nil
	  )
     (:function
          :entry-name "error"
	  :lambda-list (count string &rest format-arguments)
	  :return-type null
	  :foreign-protocol :foreign-arguments-function
	  :foreign-arguments ((:int nil) (:string nil))
	  :foreign-return-type :object
	  )
     )

("%FLOATP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "FLOATP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%FORMAT"
     (:symbol
	  :package "TRUN"
	  :import-from nil
	  :exists-at-runtime nil
	  )
     (:function
          :entry-name "format"
	  :lambda-list (count stream string &rest format-arguments)
	  :return-type null
	  :foreign-protocol :foreign-arguments-function
	  :foreign-arguments ((:int nil) (:object nil) (:string nil))
	  :foreign-return-type :object
	  )
     )

("%FUNCTIONP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "FUNCTIONP"
        :lambda-list (object)
        :return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%GRAPHIC-CHAR-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "GRAPHIC_CHAR_P"
        :lambda-list (char)
        :return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("%HASH-TABLE-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "HASH_TABLE_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%IDENTITY"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "IDENTITY"
        :lambda-list (object)
        :return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%INPUT-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "INPUT_STREAM_P"
        :lambda-list (stream)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("%INTEGERP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "INTEGERP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%KEYWORDP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "KEYWORDP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%LOWER-CASE-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "LOWER_CASE_P"
        :lambda-list (character)
        :return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("%MAKE-STRUCTURE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "MAKE_STRUCTURE"
	:lambda-list (type c-type)
	:return-type structure-object
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%NOT"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "NOT"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%NOT%BOOLEAN"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::clogicalnot
        :lambda-list (object)
	:foreign-protocol :operator
	:foreign-arguments ((:boolean nil))
	:foreign-return-type :boolean
	)
    )

("%NUMBERP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "NUMBERP"
       :lambda-list (object)
       :return-type t
       :foreign-protocol :macro
       :foreign-arguments ((:object t))
       :foreign-return-type :boolean
       )
    )

("%NUMERATOR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "NUMERATOR"
        :lambda-list (rational)
        :return-type integer
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("%OUTPUT-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "OUTPUT_STREAM_P"
        :lambda-list (stream)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("%PACKAGEP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "PACKAGEP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%PATHNAME-HOST"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "PATHNAME_HOST"
        :lambda-list (pathname)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%PATHNAMEP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "PATHNAMEP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%RANDOM-STATE-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "RANDOM_STATE_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%RATIONALP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "RATIONALP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%READTABLEP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "READTABLEP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%REALP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "REALP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%STANDARD-CHAR-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "STANDARD_CHAR_P"
        :lambda-list (char)
        :return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%STREAMP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "STREAMP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%STRING-TO-CHAR*"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "FF_STRING_TO_CHAR_POINTER"
	:lambda-list (string)
	:return-type (unsigned-byte 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("%STRINGP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "STRINGP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%SYMBOL-FUNCTION"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "SYMBOL_FUNCTION"
        :lambda-list (symbol)
	:return-type compiled-function  ;*** change if new function types added
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SYMBOL-NAME"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "SYMBOL_NAME"
        :lambda-list (symbol)
	:return-type string
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SYMBOL-PACKAGE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "SYMBOL_PACKAGE"
        :lambda-list (symbol)
	:return-type (or package null)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SYMBOL-PLIST"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "SYMBOL_PLIST"
        :lambda-list (symbol)
	:return-type list
	:foreign-protocol :accessor
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%SYMBOL-VALUE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "SYMBOL_VALUE"
        :lambda-list (symbol)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

#+translator-supports-thread
("%SYMBOL-VALUE-IN-THREAD"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "SYMBOL_VALUE_IN_THREAD"
        :lambda-list (symbol)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%SYMBOLP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "SYMBOLP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )


;;; We currently cannot generate this macro version
;;; It can't be done by a compiler-macro, because these
;;; cannot determine whether typep is being called in a predicate
;;; context.
;;; It can't be generated by a generic-to-specific transformation,
;;; because the language these are expressed in isn't powerful
;;; enough to transform typep (which has three arguments)
;;; into TYPEP (which has two arguments)
;;; We could do this if we wrote a three-argument macro TYPEP with the
;;; third argument optional, but this would be inefficient enough to
;;; defeat the purpose of having TYPEP in addition to typep.

("%TYPEP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "TYPEP"
        :lambda-list (object type)
        :return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("%UPPER-CASE-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "UPPER_CASE_P"
        :lambda-list (char)
        :return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("%WARN"
     (:symbol
	  :package "TRUN"
	  :import-from nil
	  :exists-at-runtime nil
	  )
     (:function
          :entry-name "warn"
	  :lambda-list (count string &rest format-arguments)
	  :return-type null
	  :foreign-protocol :foreign-arguments-function
	  :foreign-arguments ((:int nil) (:string nil))
	  :foreign-return-type :object
	  )
     )


("%Y-OR-N-P"
     (:symbol
	  :package "TRUN"
	  :import-from nil
	  :exists-at-runtime nil
	  )
     (:function
          :entry-name "y_or_n_p"
	  :lambda-list (count string &rest format-arguments)
	  :return-type symbol
	  :foreign-protocol :foreign-arguments-function
	  :foreign-arguments ((:int nil) (:string nil))
	  :foreign-return-type :object
	  )
     )

("%YES-OR-NO-P"
     (:symbol
	  :package "TRUN"
	  :import-from nil
	  :exists-at-runtime nil
	  )
     (:function
          :entry-name "yes_or_no_p"
	  :lambda-list (count string &rest format-arguments)
	  :return-type symbol
	  :foreign-protocol :foreign-arguments-function
	  :foreign-arguments ((:int nil) (:string nil))
	  :foreign-return-type :object
	  )
     )



;;; These are inline versions of real Lisp functions that exist in the
;;; TRUN package and have a regular Lisp definition and function object
;;; too.
;;; These are mostly type predicates (TYPEP needs to have a real Lisp
;;; function for them too).

("%BIGNUMP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "BIGNUMP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%BITP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "BITP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%BIT-0"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "bit0"
	:alias-p t
	)
    )

("%BIT-1"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (bit-array index)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "bit1"
	:alias-p t
	)
    )

("%BIT-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (bit-array index0 index1)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "bit2"
	:alias-p t
	)
    )

("%BIT-3"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (bit-array index0 index1 index2)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "bit3"
	:alias-p t
	)
    )

("%BIT-4"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (bit-array index0 index1 index2 index3)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "bit4"
	:alias-p t
	)
    )

("%BIT-5"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (bit-array index0 index1 index2 index3 index4)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "bit5"
	:alias-p t
	)
    )

("%BIT-6"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (bit-array index0 index1 index2 index3 index4 index5)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "bit6"
	:alias-p t
	)
    )

("%BIT-7"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :lambda-list (bit-array index0 index1 index2 index3 index4 index5
				index6)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "bit7"
	:alias-p t
	)
    )

("%SET-BIT-0"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array new-value)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_bit0"
	:alias-p t
	)
    )

("%SET-BIT-1"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array index new-value)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_bit1"
	:alias-p t
	)
    )

("%SET-BIT-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array index0 index1 new-value)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_bit2"
	:alias-p t
	)
    )

("%SET-BIT-3"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array index0 index1 index2 new-value)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_bit3"
	:alias-p t
	)
    )

("%SET-BIT-4"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array index0 index1 index2 index3 new-value)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_bit4"
	:alias-p t
	)
    )

("%SET-BIT-5"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array index0 index1 index2 index3 index4 new-value)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_bit5"
	:alias-p t
	)
    )

("%SET-BIT-6"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array index0 index1 index2 index3 index4 index5 
			    new-value)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_bit6"
	:alias-p t
	)
    )

("%SET-BIT-7"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (bit-array index0 index1 index2 index3 index4 index5
				index6 new-value)
	:return-type bit
	:foreign-protocol :foreign-arguments-function
	:entry-name "set_bit7"
	:alias-p t
	)
    )

("%BROADCAST-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "BROADCAST_STREAM_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

#+translator-supports-clos
("%CLASS-WRAPPER-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "CLASS_WRAPPER_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%CONCATENATED-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "CONCATENATED_STREAM_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%ECHO-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "ECHO_STREAM_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

#+translator-supports-clos
("%EFFECTIVE-METHOD-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "EFFECTIVE_METHOD_P"
	:lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%FILE-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "FILE_STREAM_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%FIXNUMP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "FIXNUMP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("%INTERACTION-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "INTERACTION_STREAM_P"
	:lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%INTERNAL-MARKER-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "INTERNAL_MARKER_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%LOGICAL-PATHNAME-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "LOGICAL_PATHNAME_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%RATIOP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "RATIOP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%SEQUENCEP"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SEQUENCEP"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%SIMPLE-ARRAY-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil

	)
    (:function
        :entry-name "SIMPLE_ARRAY_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%STANDARD-OBJECT-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STANDARD_OBJECT_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%STRING-INPUT-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STRING_INPUT_STREAM_P"
	:lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("%STRING-OUTPUT-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STRING_OUTPUT_STREAM_P"
	:lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("%STRING-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STRING_STREAM_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("%STRUCTURE-OBJECT-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STRUCTURE_OBJECT_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%SYNONYM-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SYNONYM_STREAM_P"
        :unsupported t
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%TWO-WAY-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "TWO_WAY_STREAM_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )



("%SETF-FUNCTION"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SETF_FUNCTION"
        :lambda-list (symbol)
	:return-type compiled-function  ;*** change if new function types added
	:foreign-protocol :macro               ;*** not :accessor, might cons
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )


;;; Unboxing macros

("%BYTE-16-SARRAY-TO-SHORT-POINTER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "BYTE_16_SARRAY_TO_SHORT_POINTER"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :16-bit-signed-array
	)
    )

("%BYTE-8-SARRAY-TO-CHAR-POINTER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "BYTE_8_SARRAY_TO_CHAR_POINTER"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :8-bit-signed-array
	)
    )

("%BYTE-32-SARRAY-TO-INT-POINTER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "BYTE_32_SARRAY_TO_INT_POINTER"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :32-bit-signed-array
	)
    )

("%BYTE-64-SARRAY-TO-INT64-POINTER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "BYTE_64_SARRAY_TO_INT64_POINTER"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :64-bit-signed-array
	)
    )

("%CHARACTER-TO-CHAR"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "CHARACTER_TO_CHAR"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :character
	)
    )

("%DFLOAT-SARRAY-TO-DOUBLE-POINTER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "DFLOAT_SARRAY_TO_DOUBLE_POINTER"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :double-float-array
	)
    )

;;; Like the type-specific arithmetic operators, this temporarily
;;; has a non-% name so can be called directly by applications

("UNBOX%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:lambda-list (object)
	:entry-name "DOUBLE_FLOAT_TO_DOUBLE"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :double-float
	:foreign-arguments ((:object t))
	)
    )

("%FIXNUM-TO-CHAR"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "FIXNUM_TO_CHAR"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :fixnum-char
	)
    )

("%FIXNUM-TO-INT"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "FIXNUM_TO_INT"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :fixnum-int
	)
    )

("%FIXNUM-TO-LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "FIXNUM_TO_LONG"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :fixnum-long
	)
    )

("%FIXNUM-TO-SHORT"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "FIXNUM_TO_SHORT"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :fixnum-short
	)
    )

("%IFIX"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (object)
	:entry-name "IFIX"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :fixnum
	)
    )

("%INTEGER-TO-CHAR"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "INTEGER_TO_CHAR"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :signed-8bit
	)
    )

("%INTEGER-TO-INT"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "INTEGER_TO_INT"
	:foreign-protocol :unboxing-macro
	:foreign-arguments ((:object t))
	:foreign-return-type :int))

("%INTEGER-TO-LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "INTEGER_TO_LONG"
	:foreign-protocol :unboxing-macro
	:foreign-arguments ((:object t))
	:foreign-return-type :long))

("%INTEGER-TO-INT64"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "INTEGER_TO_INT64"
	:foreign-protocol :unboxing-macro
	:foreign-arguments ((:object t))
	:foreign-return-type :signed-64bit))

("%INTEGER-TO-SHORT"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "INTEGER_TO_SHORT"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :signed-16bit
	)
    )

("%INTEGER-TO-UNSIGNED-CHAR"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "INTEGER_TO_UNSIGNED_CHAR"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :unsigned-8bit
	)
    )

("%INTEGER-TO-UNSIGNED-INT"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "INTEGER_TO_UNSIGNED_INT"
	:foreign-protocol :unboxing-macro
	:foreign-arguments ((:object t))
	:foreign-return-type :unsigned-int
	)
    )

("%INTEGER-TO-UNSIGNED-LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "INTEGER_TO_UNSIGNED_LONG"
	:foreign-protocol :unboxing-macro
	:foreign-arguments ((:object t))
	:foreign-return-type :unsigned-long
	)
    )

("%INTEGER-TO-UNSIGNED-INT64"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "INTEGER_TO_UINT64"
	:foreign-protocol :unboxing-macro
	:foreign-arguments ((:object t))
	:foreign-return-type :unsigned-64bit
	)
    )

("%INTEGER-TO-UNSIGNED-SHORT"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "INTEGER_TO_UNSIGNED_SHORT"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :unsigned-16bit
	)
    )

("%ISTRING"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "ISTRING"
	:nonconsing nil
	:foreign-protocol :unboxing-macro
	:foreign-return-type :string
	)
    )

("%SFLOAT-SARRAY-TO-FLOAT-POINTER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "SFLOAT_SARRAY_TO_FLOAT_POINTER"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :single-float-array
	)
    )

("%SHORT-FLOAT-TO-FLOAT"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "SHORT_FLOAT_TO_FLOAT"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :short-float
	:foreign-arguments ((:object t))
	)
    )

("%SIMPLE-STRING-TO-CHAR-POINTER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "SIMPLE_STRING_TO_CHAR_POINTER"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :simple-string
	)
    )

("%SINGLE-FLOAT-TO-FLOAT"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "SINGLE_FLOAT_TO_FLOAT"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :single-float
	)
    )

("%TRUEP"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "TRUEP"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :boolean
	)
    )

("%UBYTE-16-SARRAY-TO-USHORT-PTR"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "UBYTE_16_SARRAY_TO_USHORT_PTR"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :16-bit-unsigned-array
	)
    )

("%UBYTE-8-SARRAY-TO-UCHAR-PTR"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "UBYTE_8_SARRAY_TO_UCHAR_PTR"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :8-bit-unsigned-array
	)
    )

("%UBYTE-32-SARRAY-TO-UINT-PTR"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "UBYTE_32_SARRAY_TO_UINT_PTR"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :32-bit-unsigned-array
	)
    )

("%UBYTE-64-SARRAY-TO-UINT64-PTR"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "UBYTE_64_SARRAY_TO_UINT64_PTR"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :64-bit-unsigned-array
	)
    )

("%UNBOUND-MARKER"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:constant
        :variable-name "UNBOUND"
	:allow-multiple-uses-of-variable-name t
	:simple-p t
	:foreign-p t
	:dump-definition-p nil
	)
    )

("%UNBOX-CHAR"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "ICHAR_CODE"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :char
	)
    )

("%UNBOX-FLOAT"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "IDOUBLE"
	:foreign-protocol :unboxing-macro
	:foreign-return-type :float
	:foreign-arguments ((:object t))
	)
    )


;;; Boxing macros

("%CDOUBLE-TO-DOUBLE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (c-float)
	:return-type float
	:foreign-protocol :macro
	:foreign-arguments ((:float nil))
	:foreign-return-type :object
	)
    )

("%CHAR-TO-CHARACTER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "CHAR_TO_CHARACTER"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:character nil))
	)
    )

("%CHAR-TO-FIXNUM"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "CHAR_TO_FIXNUM"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:fixnum-char nil))
	)
    )

("%CHAR-TO-INTEGER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "CHAR_TO_INTEGER"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:unsigned-8bit nil))
	)
    )

("%CHR"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "CHR"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:char nil))
	)
    )

;;; Like the type-specific arithmetic operators, this temporarily
;;; has a non-% name so can be called directly by applications

("BOX%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:lambda-list (object)
	:entry-name "DOUBLE_TO_DOUBLE_FLOAT"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:double-float nil))
	)
    )

("%FLOAT-TO-SINGLE-FLOAT"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "FLOAT_TO_SINGLE_FLOAT"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:single-float nil))
	)
    )

("%FLOAT-TO-SHORT-FLOAT"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "FLOAT_TO_SHORT_FLOAT"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:short-float nil))
	)
    )

("%FIX"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (object)
	:entry-name "FIX"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:fixnum nil))
	)
    )

("%INT-TO-FIXNUM"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "INT_TO_FIXNUM"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:fixnum-int nil))
	)
    )

("%ISTRING-TO-STRING"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (c-string)
	:return-type string
	:entry-name "istring_to_string"
	:foreign-protocol :macro
	:foreign-arguments ((:string nil))
	:foreign-return-type :object
	)
    )

("%ISTRING-TO-SIMPLE-STRING"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (c-string)
	:return-type string
	:entry-name "istring_to_string_or_nil"
	:allow-multiple-uses-of-entry-name t
	:foreign-protocol :macro
	:foreign-arguments ((:simple-string nil))
	:foreign-return-type :object
	)
    )

("%LONG-TO-FIXNUM"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "LONG_TO_FIXNUM"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:fixnum-long nil))
	)
    )

("%INT-TO-INTEGER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "INT_TO_INTEGER"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:int t))
	)
    )

("%LONG-TO-INTEGER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "LONG_TO_INTEGER"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:long t))
	)
    )

("%INT64-TO-INTEGER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "INT64_TO_INTEGER"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:signed-64bit t))
	)
    )

("%LONG-TO-FLOAT"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c-cast-to-float
	:lambda-list (x)
	:foreign-protocol :operator
	:foreign-arguments ((:long nil))
	:foreign-return-type :single-float
	)
    )

("%LONG-TO-DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:operator timpl::c-cast-to-double
	:lambda-list (x)
	:nonconsing t
	:foreign-protocol :operator
	:foreign-arguments ((:long nil))
	:foreign-return-type :double-float
	)
    )

("%LONG-TO-FLOAT2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (x float)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil) (:single-float nil))
	:foreign-return-type :single-float
	)
    )

("%LONG-TO-DOUBLE2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (x float)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil) (:double-float nil))
	:foreign-return-type :double-float
	)
    )

("%SHORT-TO-FIXNUM"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "SHORT_TO_FIXNUM"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:fixnum-short nil))
	)
    )

("%SHORT-TO-INTEGER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "SHORT_TO_INTEGER"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:signed-16bit nil))
	)
    )

("%UNSIGNED-CHAR-TO-INTEGER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "UNSIGNED_CHAR_TO_INTEGER"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:unsigned-8bit nil))
	)
    )

("%UNSIGNED-INT-TO-INTEGER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "UNSIGNED_INT_TO_INTEGER"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:unsigned-int t))
	)
    )

("%UNSIGNED-LONG-TO-INTEGER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "UNSIGNED_LONG_TO_INTEGER"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:unsigned-long t))
	)
    )

("%UNSIGNED-INT64-TO-INTEGER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "UINT64_TO_INTEGER"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:unsigned-64bit t))
	)
    )

("%UNSIGNED-SHORT-TO-INTEGER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "UNSIGNED_SHORT_TO_INTEGER"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:unsigned-16bit nil))
	)
    )

("%VOID-TO-NULL"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:entry-name "VOID_TO_NULL"
	:foreign-protocol :boxing-macro
	:foreign-arguments ((:null nil))
	)
    )

("%DOUBLE-TO-FLOAT"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c-cast-to-float
	:lambda-list (x)
	:foreign-protocol :operator
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :single-float
	)
    )

("%FLOAT-TO-DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:operator timpl::c-cast-to-double
	:lambda-list (x)
	:nonconsing t
	:foreign-protocol :operator
	:foreign-arguments ((:single-float nil))
	:foreign-return-type :double-float
	)
    )


;;; Constant tagging macros

("%TAG-ARRAY"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (object)
	:return-type (simple-array t)
	:entry-name "TAG_ARRAY"
	:foreign-protocol :macro
	:foreign-return-type :object
	:foreign-arguments ((:pointer nil))
	)
    )

("%TAG-BIGNUM"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (pointer)
	:return-type bignum
	:entry-name "TAG_BIGNUM"
	:foreign-protocol :macro
	:foreign-return-type :object
	:foreign-arguments ((:pointer nil))
	)
    )

("%TAG-COMPILED-FUNCTION"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (pointer)
	:return-type compiled-function
	:entry-name "TAG_COMPILED_FUNCTION"
	:foreign-protocol :macro
	:foreign-return-type :object
	:foreign-arguments ((:pointer nil))
	)
    )

("%TAG-CONS"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (pointer)
	:return-type cons
	:entry-name "TAG_CONS"
	:foreign-protocol :macro
	:foreign-return-type :object
	:foreign-arguments ((:pointer nil))
	)
    )

("%TAG-DOUBLE-FLOAT"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (pointer)
	:return-type double-float
	:entry-name "TAG_DOUBLE_FLOAT"
	:foreign-protocol :macro
	:foreign-return-type :object
	:foreign-arguments ((:pointer nil))
	)
    )

("%TAG-RATIO"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (pointer)
	:return-type ratio
	:entry-name "TAG_RATIO"
	:foreign-protocol :macro
	:foreign-return-type :object
	:foreign-arguments ((:pointer nil))
	)
    )

("%TAG-STRING"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (pointer)
	:return-type simple-string
	:entry-name "TAG_STRING"
	:foreign-protocol :macro
	:foreign-return-type :object
	:foreign-arguments ((:pointer nil))
	)
    )

("%TAG-UNINTERNED-SYMBOL"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (pointer)
	:return-type symbol
	:entry-name "TAG_UNINTERNED_SYMBOL"
	:foreign-protocol :macro
	:foreign-return-type :object
	:foreign-arguments ((:pointer nil))
	)
    )

("%TAG-VECTOR"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:lambda-list (pointer)
	:return-type simple-vector
	:entry-name "TAG_VECTOR"
	:foreign-protocol :macro
	:foreign-return-type :object
	:foreign-arguments ((:pointer nil))
	)
    )



;;; These are inline versions of real Lisp functions that exist in the
;;; TX package and have a regular Lisp definition and function object
;;; too.

("%%POINTER"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "GCL_POINTER"
	:lambda-list (object)
	:return-type (unsigned-byte #+x86-64 64 #-x86-64 32)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%%SYSINT"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "GCL_SYSINT"
	:lambda-list (a b c d e &optional f g)   ;; ?
	:return-type t          ;; ?
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%NEQ"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "NEQ"
        :lambda-list (x y)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("%NEQL"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "NEQL"
        :lambda-list (x y)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("%RPLACB"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "RPLACB"
	:lambda-list (cell1 cell2)
	:return-type cons
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )


;;; These functions have foreign definitions only.  Calls might show up
;;; as a result of source-to-source transformations but these are never
;;; efunctuated or funcalled.


;;; void ADD_IMPORT(Object package, Object symbol, int externalp);
;;;     Make the symbol accessible in the package.  Doesn't need to check 
;;;     for name conflicts or set the home package of the symbol.


("%ADD-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "add"
	:lambda-list (x y)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:coerce-rationals-to-floats-p t
	:transforms ((trun:+% :no-longs)
		     ;(trun:+%int64 :all-int64)
		     (trun:+%long nil)
		     (trun:+%single :single)
		     (trun:+%double nil))
	)
    )

("%ADD-IMPORT"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "ADD_IMPORT"
        :lambda-list (package symbol externalp)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil) (:int nil))
	:foreign-return-type :void
	)
    )


;;; void ADD_PACKAGE_NICKNAME(Object package, char *name);
;;;     Make the string be a new nickname for the package.  Doesn't need
;;;     to check whether a package with the same name already exists.

("%ADD-PACKAGE-NICKNAME"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "ADD_PACKAGE_NICKNAME"
        :lambda-list (package name)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:string nil))
	:foreign-return-type :void
	)
    )


;;; void ADD_PACKAGE_USE(Object package, Object package_to_use);
;;;     Add package_to_use to the use list of package.  Doesn't need to
;;;     check for name conflicts.

("%ADD-PACKAGE-USE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "ADD_PACKAGE_USE"
        :lambda-list (package package-to-use)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :void
	)
    )

;;; void ADD_SHADOW(Object package, Object symbol);
;;;     Add the symbol to the shadowing symbols list in the package.
;;;     Doesn't need to check if it is already there.  Doesn't need to
;;;     make the symbol accessible in the package.

("%ADD-SHADOW"
     (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "ADD_SHADOW"
        :lambda-list (package symbol)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :void
	)
    )

("%APPEND-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "append2"
        :lambda-list (list1 list2)
	:return-type list
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%APPLY-1"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "APPLY_1"
        :lambda-list (fn list)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function  ; returns multiple values
	:foreign-arguments ((:object t) (:object nil))
	:foreign-return-type :object
	)
    )

("%APPLY-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "APPLY_2"
        :lambda-list (fn x1 list)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function  ; returns multiple values
	:foreign-arguments #.(cons '(:object t) (make-list 2 :initial-element
							     '(:object nil)))
	:foreign-return-type :object
	)
    )

("%APPLY-3"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "APPLY_3"
        :lambda-list (fn x1 x2 list)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function  ; returns multiple values
	:foreign-arguments #.(cons '(:object t) (make-list 3 :initial-element
							     '(:object nil)))
	:foreign-return-type :object
	)
    )

("%APPLY-4"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "APPLY_4"
        :lambda-list (fn x1 x2 x3 list)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function  ; returns multiple values
	:foreign-arguments #.(cons '(:object t) (make-list 4 :initial-element
							     '(:object nil)))
	:foreign-return-type :object
	)
    )

("%APPLY-5"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "APPLY_5"
        :lambda-list (fn x1 x2 x3 x4 list)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function  ; returns multiple values
	:foreign-arguments #.(cons '(:object t) (make-list 5 :initial-element
							     '(:object nil)))
	:foreign-return-type :object
	)
    )

("%ASSOC-EQ"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "assoc_eq"
	:lambda-list (item alist)
	:return-type list
	:foreign-protocol :foreign-arguments-function
	)
    )

("%ASSOC-EQL"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "assoc_eql"
	:lambda-list (item alist)
	:return-type list
	:foreign-protocol :foreign-arguments-function
	)
    )

("%ASSOC-EQUAL"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "assoc_equal"
	:lambda-list (item alist)
	:return-type list
	:foreign-protocol :foreign-arguments-function
	)
    )

;;; This macro retrieves the values stored by THROW.

("%CATCH-VALUES"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "CATCH_VALUES"
	:lambda-list ()
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function
	)
    )

("%CHAR-NE-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "CHAR_NE"		;BB (was CHAR_NE_2)
        :lambda-list (char1 char2)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("%CHAR-LT-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "CHAR_LT"		;BB
        :lambda-list (char1 char2)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("%CHAR-LE-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "CHAR_LE"		;BB
        :lambda-list (char1 char2)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("%CHAR-EQ-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "CHAR_EQ"		;BB
        :lambda-list (char1 char2)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("%CHAR-GT-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "CHAR_GT"		;BB
        :lambda-list (char1 char2)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("%CHAR-GE-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "CHAR_GE"		;BB
        :lambda-list (char1 char2)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("%CHAR-EQUAL-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "CHAR_EQUAL"	;BB
        :lambda-list (char1 char2)
        :return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("%CHAR-GREATERP-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "CHAR_GREATERP"	;BB
        :lambda-list (char1 char2)
        :return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("%CHAR-LESSP-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "CHAR_LESSP"	;BB
        :lambda-list (char1 char2)
        :return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("%CHAR-NOT-EQUAL-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "CHAR_NOT_EQUAL"	;BB
        :lambda-list (char1 char2)
        :return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("%CHAR-NOT-GREATERP-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "CHAR_NOT_GREATERP"	;BB
        :lambda-list (char1 char2)
        :return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("%CHAR-NOT-LESSP-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "CHAR_NOT_LESSP"	;BB
        :lambda-list (char1 char2)
        :return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("%DELETE-EQ"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "delete_eq"
	:lambda-list (item list)
	:return-type list
	:foreign-protocol :foreign-arguments-function
	)
    )

("%DELETE-EQL"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "delete_eql"
	:lambda-list (item list)
	:return-type list
	:foreign-protocol :foreign-arguments-function
	)
    )

("%DELETE-EQUAL"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "delete_equal"
	:lambda-list (item list)
	:return-type list
	:foreign-protocol :foreign-arguments-function
	)
    )

("%DIVIDE-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "divide"
	:lambda-list (x y)
	:return-type t
	:coerce-rationals-to-floats-p t
	:foreign-protocol :foreign-arguments-function
	:transforms ((trun:/%single :single)
		     (trun:/%double nil))
	)
    )

("EXPT2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (base power)
	:foreign-protocol :secret-special-form
	:argument-types ((member 2) (integer 0 *))
	)
    )

("EXPT%LONG"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :lambda-list (base power)
	:foreign-protocol :macro
	:entry-name "expt_long"
	:requires-return-type-declaration t
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("%FUNCALL-0"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "FUNCALL_0"
        :lambda-list (fn)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments #.(make-list 1 :initial-element '(:object nil))
	:foreign-return-type :object
	:transforms ((trun:%funcall-symbol-0 nil))
	)
    )

("%FUNCALL-1"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "FUNCALL_1"
        :lambda-list (fn arg1)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments #.(cons '(:object t) (make-list 1 :initial-element
							     '(:object nil)))
	:foreign-return-type :object
	:transforms ((trun:%funcall-symbol-1 nil))
	)
    )

("%FUNCALL-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "FUNCALL_2"
        :lambda-list (fn arg1 arg2)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments #.(cons '(:object t) (make-list 2 :initial-element
							     '(:object nil)))
	:foreign-return-type :object
	:transforms ((trun:%funcall-symbol-2 nil))
	)
    )

("%FUNCALL-3"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "FUNCALL_3"
        :lambda-list (fn arg1 arg2 arg3)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments #.(cons '(:object t) (make-list 3 :initial-element
							     '(:object nil)))
	:foreign-return-type :object
	:transforms ((trun:%funcall-symbol-3 nil))
	)
    )

("%FUNCALL-4"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "FUNCALL_4"
        :lambda-list (fn arg1 arg2 arg3 arg4)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments #.(cons '(:object t) (make-list 4 :initial-element
							     '(:object nil)))
	:foreign-return-type :object
	:transforms ((trun:%funcall-symbol-4 nil))
	)
    )

("%FUNCALL-5"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "FUNCALL_5"
        :lambda-list (fn arg1 arg2 arg3 arg4 arg5)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments #.(cons '(:object t) (make-list 5 :initial-element
							     '(:object nil)))
	:foreign-return-type :object
	:transforms ((trun:%funcall-symbol-5 nil))
	)
    )

("%FUNCALL-SYMBOL-0"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "FUNCALL_SYMBOL_0"
	:lambda-list (fn)
	:argument-types (symbol)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments #.(make-list 1 :initial-element '(:object nil))
        :foreign-return-type :object
	)
    )

("%FUNCALL-SYMBOL-1"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "FUNCALL_SYMBOL_1"
        :lambda-list (fn arg1)
	:argument-types (symbol t)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments #.(cons '(:object t) (make-list 1 :initial-element
							     '(:object nil)))
	:foreign-return-type :object
	)
    )

("%FUNCALL-SYMBOL-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "FUNCALL_SYMBOL_2"
        :lambda-list (fn arg1 arg2)
	:argument-types (symbol t t)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments #.(cons '(:object t) (make-list 2 :initial-element
							     '(:object nil)))
	:foreign-return-type :object
	)
    )

("%FUNCALL-SYMBOL-3"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "FUNCALL_SYMBOL_3"
        :lambda-list (fn arg1 arg2 arg3)
	:argument-types (symbol t t t)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments #.(cons '(:object t) (make-list 3 :initial-element
							     '(:object nil)))
	:foreign-return-type :object
	)
    )

("%FUNCALL-SYMBOL-4"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "FUNCALL_SYMBOL_4"
        :lambda-list (fn arg1 arg2 arg3 arg4)
	:argument-types (symbol t t t t)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments #.(cons '(:object t) (make-list 4 :initial-element
							     '(:object nil)))
	:foreign-return-type :object
	)
    )

("%FUNCALL-SYMBOL-5"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "FUNCALL_SYMBOL_5"
        :lambda-list (fn arg1 arg2 arg3 arg4 arg5)
	:argument-types (symbol t t t t t)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function
	:foreign-arguments #.(cons '(:object t) (make-list 5 :initial-element
							     '(:object nil)))
	:foreign-return-type :object
	)
    )

("%GCD-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "gcd"
	:lambda-list (x y)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	)
    )

("%ILENGTH"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "ilength"
	:lambda-list (sequence)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :fixnum
	)
    )

("%KEYWORD-ARG"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "KEYWORD_ARG"
        :lambda-list (svar)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("%KEYWORD-ARG-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "KEYWORD_ARG_P"
        :lambda-list (keyword)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("LOGCOUNT%LONG"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :lambda-list (i)
	:foreign-protocol :macro
	:entry-name "logcount_long"
	:foreign-arguments ((:long nil))
	:foreign-return-type :fixnum-int
	)
    )

("%LCM-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "lcm"
	:lambda-list (x y)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	)
    )

("%LOGAND-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "logand"
	:lambda-list (x y)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:transforms ((trun:logand% :no-longs)
		     (trun:logand%long nil))
	)
    )

("%LOGEQV-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "logeqv"
	:lambda-list (x y)
	:return-type integer
	:foreign-protocol :foreign-arguments-function
	:transforms ((trun:logeqv% :no-longs)
		     (trun:logeqv%long nil))
	)
    )

("%LOGIOR-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "logior"
	:lambda-list (x y)
	:return-type integer
	:foreign-protocol :foreign-arguments-function
	:transforms ((trun:logior% :no-longs)
		     (trun:logior%long nil))
	)
    )

("%LOGXOR-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "logxor"
	:lambda-list (x y)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:transforms ((trun:logxor% :no-longs)
		     (trun:logxor%long nil))
	)
    )

("%LIST-1"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "LIST_1"
        :lambda-list (arg1)
	:return-type cons
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%LIST-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "LIST_2"
        :lambda-list (arg1 arg2)
	:return-type cons
	:foreign-protocol :macro
	:foreign-arguments #.(make-list 2 :initial-element '(:object nil))
	:foreign-return-type :object
	)
    )

("%LIST-3"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "LIST_3"
        :lambda-list (arg1 arg2 arg3)
	:return-type cons
	:foreign-protocol :macro
	:foreign-arguments #.(make-list 3 :initial-element '(:object nil))
	:foreign-return-type :object
	)
    )

("%LIST-4"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "LIST_4"
        :lambda-list (arg1 arg2 arg3 arg4)
	:return-type cons
	:foreign-protocol :macro
	:foreign-arguments #.(make-list 4 :initial-element '(:object nil))
	:foreign-return-type :object
	)
    )

("%LIST-5"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
        :entry-name "LIST_5"
        :lambda-list (arg1 arg2 arg3 arg4 arg5)
	:return-type cons
	:foreign-protocol :macro
	:foreign-arguments #.(make-list 5 :initial-element '(:object nil))
	:foreign-return-type :object
	)
    )

("%LIST-STAR-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "LIST_STAR_2"
        :lambda-list (item tail)
	:return-type cons
	:foreign-protocol :macro
	:foreign-arguments #.(make-list 2 :initial-element '(:object nil))
	:foreign-return-type :object
	)
    )

("%LIST-STAR-3"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "LIST_STAR_3"
        :lambda-list (item1 item2 tail)
	:return-type cons
	:foreign-protocol :macro
	:foreign-arguments #.(make-list 3 :initial-element '(:object nil))
	:foreign-return-type :object
	)
    )


;;; lvalue variants of Common Lisp functions


("%MAX-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "lmax"
	:lambda-list (x y)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:transforms ((trun:max% :no-longs)
		     (trun:max%long nil)
		     (trun:max%d :no-doubles)
		     (trun:max%rd nil))
	)
    )

("%MEMBER-EQ"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "member_eq"
	:lambda-list (item list)
	:return-type list
	:foreign-protocol :foreign-arguments-function
	)
    )

("%MEMBER-EQL"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "member_eql"
	:lambda-list (item list)
	:return-type list
	:foreign-protocol :foreign-arguments-function
	)
    )

("%MEMBER-EQUAL"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "member_equal"
	:lambda-list (item list)
	:return-type list
	:foreign-protocol :foreign-arguments-function
	)
    )

#+translator-supports-clos
("%METHOD-COMBINATION-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "METHOD_COMBINATION_P"
        :lambda-list (object)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("%MIN-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "lmin"
	:lambda-list (x y)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:transforms ((trun:min% :no-longs)
		     (trun:min%long nil)
		     (trun:min%d :no-doubles)
		     (trun:min%rd nil))
		     
	)
    )

("%MINUS-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "minus"
	:lambda-list (x y)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:coerce-rationals-to-floats-p t
	:transforms ((trun:-% :no-longs)
		     (trun:-%long nil)
		     (trun:-%single :single)
		     (trun:-%double nil))
	)
    )

;;; Appears in code produced for MULTIPLE-VALUE-CALL in the case where
;;; there is only one values-producing form.  The values have already
;;; been stored, and the argument is the function to apply to them.

("%MV-FUNCALL"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "MV_FUNCALL"
        :lambda-list (function)
	:return-type (values &rest t)
	:foreign-protocol :foreign-arguments-function  ; returns multiple values
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

;;; This one is the primitive for MULTIPLE-VALUE-LIST.  Again, the values
;;; have already been stored.

("%MV-LIST"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Calling this a function is really a misnomer.
    ;; It is only used in the implementation of multiple-value-list, and is
    ;; really a special operator, since it is assumed that the value form will
    ;; set up the values buffer.
    (:function
        :entry-name "MV_LIST"
        :lambda-list (value)
	:return-type list
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("%MV-SETQ-REMAINING"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    ;; Helper for MULTIPLE-VALUE-SETQ and related forms.
    ;; Calling this a function is really a misnomer.
    ;; It is only used in the implementation of multiple-value-setq, and is
    ;; really a special operator, since it is assumed that the values are
    ;; already stored in the values buffer.
    ;; Takes a start index and a block of 10 l-values, and stores the 10 values
    ;; beginning with start into the 10 l-values.
    (:function
        :entry-name "MVSR"
	:lambda-list (n a b c d e f g h i j)
	:foreign-protocol :macro
	:foreign-arguments ((:int nil))
	:foreign-return-type :void
	)
    )

;;; From a source-to-source transformation on NCONC.

("%NCONC-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :nonconsing t
        :entry-name "nconc2"
        :lambda-list (list1 list2)
	:return-type list
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%NEGATE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "negate"
	:lambda-list (a)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:transforms ((trun:negate% :no-longs)
		     (trun:negate%long nil)
		     (trun:negate%single :single)
		     (trun:negate%double nil))
	)
    )

("NEGATE%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::cnegate
	:lambda-list (i j)
	:requires-return-type-declaration t ; all this for just one bad value
	:foreign-protocol :operator
	:foreign-arguments ((:long nil))
	:foreign-return-type :long
	)
    )

("NEGATE%DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::cnegate
	:lambda-list (i j)
	:foreign-protocol :operator
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("NEGATE%SINGLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::cnegate
	:lambda-list (i j)
	:foreign-protocol :operator
	:foreign-arguments ((:single-float nil))
	:foreign-return-type :single-float
	)
    )

;;; Object NEW_PACKAGE(char *name);
;;;     Create and return a new package with the given name.
;;;     Does not need to check whether a package with the same name already 
;;;     exists.

("%NEW-PACKAGE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "NEW_PACKAGE"
        :lambda-list (name)
	:return-type package
	:foreign-protocol :macro
	:foreign-arguments ((:string nil))
	:foreign-return-type :object
	)
    )


;;; Object NEW_SYMBOL(Object package, char *name, int externalp);
;;;     Create a symbol with the given name and install it as an internal
;;;     or external (according to externalp) symbol in the package.  
;;;     Doesn't need to check whether there is already a symbol with 
;;;     this name accessible in the package, or do any name conflict checking,
;;;     but does need to set the home package of the symbol.
;;;     Initializes the symbol-value and symbol-function to unbound and
;;;     sets the symbol-plist to nil.

("%NEW-SYMBOL"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "NEW_SYMBOL"
        :lambda-list (package name externalp)
	:return-type symbol
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:string nil) (:int nil))
	:foreign-return-type :object
	)
    )

("%NUM-EQ-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:return-type t
	:entry-name "NUM_EQ"
	:lambda-list (x y)
	:foreign-protocol :macro
	:foreign-return-type :boolean
	:foreign-arguments ((:object t)(:object t))
	:transforms ((trun:=% :no-longs)
		     (trun:=%long nil)
		     (trun:=%single :single)
		     (trun:=%double nil))
	)
    )

("%NUM-NE-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:return-type t
	:entry-name "NUM_NE"
	:lambda-list (x y)
	:foreign-protocol :macro
	:foreign-return-type :boolean
	:foreign-arguments ((:object t)(:object t))
	:transforms ((trun:/=% :no-longs)
		     (trun:/=%long nil)
		     (trun:/=%single :single)
		     (trun:/=%double nil))
	)
    )

("%NUM-LT-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:return-type t
	:entry-name "NUM_LT"
	:lambda-list (x y)
	:foreign-protocol :macro
	:foreign-return-type :boolean
	:foreign-arguments ((:object t)(:object t))
	:transforms ((trun:<% :no-longs)
		     (trun:<%long nil)
		     (trun:<%single :single)
		     (trun:<%double nil))
	)
    )

("%NUM-GT-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:return-type t
	:entry-name "NUM_GT"
	:lambda-list (x y)
	:foreign-protocol :macro
	:foreign-return-type :boolean
	:foreign-arguments ((:object t)(:object t))
	:transforms ((trun:>% :no-longs)
		     (trun:>%long nil)
		     (trun:>%single :single)
		     (trun:>%double nil))
	)
    )

("%NUM-LE-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:return-type t
	:entry-name "NUM_LE"
	:lambda-list (x y)
	:foreign-protocol :macro
	:foreign-return-type :boolean
	:foreign-arguments ((:object t)(:object t))
	:transforms ((trun:<=% :no-longs)
		     (trun:<=%long nil)
		     (trun:<=%single :single)
		     (trun:<=%double nil))
	)
    )

("%NUM-GE-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:return-type t
	:entry-name "NUM_GE"
	:lambda-list (x y)
	:foreign-protocol :macro
	:foreign-return-type :boolean
	:foreign-arguments ((:object t)(:object t))
	:transforms ((trun:>=% :no-longs)
		     (trun:>=%long nil)
		     (trun:>=%single :single)
		     (trun:>=%double nil))
	)
    )

("%OPTIONAL-ARG"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing t
	:nonconsing t
        :entry-name "OPTIONAL_ARG"
        :lambda-list ()
	:return-type t
	:foreign-protocol  :macro
	:foreign-arguments ()
	:foreign-return-type :object
	)
    )
     
("%OPTIONAL-ARG-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "OPTIONAL_ARG_P"
        :lambda-list ()
	:return-type t
	:foreign-protocol  :macro
	:foreign-arguments ()
	:foreign-return-type :boolean
	)
    )

("%NR-OPTIONAL-ARG"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing t
	:nonconsing t
        :entry-name "OPTIONAL_ARG_nonrelocating"
        :lambda-list ()
	:return-type t
	:foreign-protocol  :macro
	:foreign-arguments ()
	:foreign-return-type :object
	)
    )
     
("%NR-OPTIONAL-ARG-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
        :entry-name "OPTIONAL_ARG_P_nonrelocating"
        :lambda-list ()
	:return-type t
	:foreign-protocol  :macro
	:foreign-arguments ()
	:foreign-return-type :boolean
	)
    )

("%NR-END-ARGS"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing t
	:nonconsing t
        :entry-name "END_ARGS_nonrelocating"
        :lambda-list ()
	:return-type nil
	:foreign-protocol  :macro
	:foreign-arguments ()
	:foreign-return-type :void
	)
    )

("%RECIPROCAL"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "reciprocal"
	:lambda-list (a)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:transforms (;;(trun:/1%long nil)
		     ;;(trun:/1%double nil)
		     )
	)
    )

("%REST-ARG"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "REST_ARG"
        :lambda-list ()
	:return-type list
	:foreign-protocol  :macro
	:foreign-arguments ()
	:foreign-return-type :object
	)
    )
       

("%SET-BIGNUM-DIGIT"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SET_BIGNUM_DIGIT"
	:lambda-list (bignum digit-number high-digit low-digit)
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:int nil) (:int nil) (:int nil))
	:foreign-return-type :void
	)
    )


("%SET-ROW-MAJOR-AREF"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :lambda-list (array index new-value)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%SET-SETF-FUNCTION"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SET_SETF_FUNCTION"
        :lambda-list (symbol new-value)
	:return-type function
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-SUBSEQ-1"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "set_subseq1"
        :lambda-list (sequence start new-sequence)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-SUBSEQ-2"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "set_subseq2"
        :lambda-list (sequence start end new-sequence)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil) (:object nil)
			    (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-SYMBOL-FUNCTION"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SET_SYMBOL_FUNCTION"
        :lambda-list (symbol new-value)
	:return-type function
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-SYMBOL-PLIST"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SET_SYMBOL_PLIST"
        :lambda-list (symbol new-value)
	:return-type function
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
        )
    )

("%SET-SYMBOL-VALUE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SET_SYMBOL_VALUE"
        :lambda-list (symbol value)
	:return-type t
	:foreign-protocol  :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

#+translator-supports-thread
("%SET-SYMBOL-VALUE-IN-THREAD"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "SET_SYMBOL_VALUE_IN_THREAD"
        :lambda-list (symbol value thread)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%STRING-APPEND-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "string_append2"
	:lambda-list (string1 string2)
	:return-type string
	:foreign-protocol :foreign-arguments-function
	)
    )

;;; Appears in the code produced for handling THROW.
;;; Assumes that the values to be returned from the throw (beyond the
;;; first) have already been stored; the first value is passed to the macro.

("%THROW"   
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "THROW"
        :lambda-list (tag result)
	:return-type nil
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object   ; actually, never returns
	)
    )


("%TIMES-2"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "ltimes"
	:lambda-list (x y)
	:return-type t
	:foreign-protocol :foreign-arguments-function
	:coerce-rationals-to-floats-p t
	:transforms ((trun:*% :no-longs)
		     (trun:*%long nil)
		     (trun:*%single :single)
		     (trun:*%double nil))
	)
    )



;;;; Type-specific arithmetic operators
;;;; These carry no "%" prefix to make it easier for users
;;;; to reference these operators directly (they are currently
;;;; supported directly as extensions).


;;; Type-specific fixnum operators

("+%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_ADD"
	:lambda-list (i j)
	:return-type fixnum
	:requires-return-type-declaration t
	:foreign-protocol :macro
	:argument-types (fixnum fixnum)
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("+%INT64"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:operator timpl::c+
	:lambda-list (i j)
	:return-type (signed-byte 64)
	:requires-return-type-declaration t
	:nonconsing t
	:foreign-protocol :operator
	:argument-types ((signed-byte 64) (signed-byte 64))
	:foreign-arguments ((:signed-64bit nil) (:signed-64bit nil))
	:foreign-return-type :signed-64bit
	)
    )

("+%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:operator timpl::c+
	:lambda-list (i j)
	:requires-return-type-declaration t
	:nonconsing t
	:foreign-protocol :operator
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("+%DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c+
	:lambda-list (i j)
	:foreign-protocol :operator
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :double-float
	)
    )

("+%SINGLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c+
	:lambda-list (i j)
	:foreign-protocol :operator
	:foreign-arguments ((:single-float nil) (:single-float nil))
	:foreign-return-type :single-float
	)
    )

("*%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_TIMES"
	:lambda-list (i j)
	:return-type fixnum
	:requires-return-type-declaration t
	:foreign-protocol :macro
	:argument-types (fixnum fixnum)
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("*%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:lambda-list (i j)
	:operator timpl::c*
	:requires-return-type-declaration t
	:foreign-protocol :operator
	:nonconsing t
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("*%DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c*
	:lambda-list (i j)
	:foreign-protocol :operator
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :double-float
	)
    )

("*%SINGLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c*
	:lambda-list (i j)
	:foreign-protocol :operator
	:foreign-arguments ((:single-float nil) (:single-float nil))
	:foreign-return-type :single-float
	)
    )

("-%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_MINUS"
	:lambda-list (i j)
	:return-type fixnum
	:foreign-protocol :macro
	:argument-types (fixnum fixnum)
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("-%INT64"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:operator timpl::c-
	:lambda-list (i j)
	:return-type (signed-byte 64)
	:requires-return-type-declaration t
	:nonconsing t
	:foreign-protocol :operator
	:argument-types ((signed-byte 64) (signed-byte 64))
	:foreign-arguments ((:signed-64bit nil) (:signed-64bit nil))
	:foreign-return-type :signed-64bit
	)
    )

("-%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:lambda-list (i j)
	:operator timpl::c-
	:requires-return-type-declaration t
	:foreign-protocol :operator
	:nonconsing t
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("-%DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c-
	:lambda-list (i j)
	:foreign-protocol :operator
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :double-float
	)
    )

("-%SINGLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c-
	:lambda-list (i j)
	:foreign-protocol :operator
	:foreign-arguments ((:single-float nil) (:single-float nil))
	:foreign-return-type :single-float
	)
    )

;;; Note that this C macro doesn't actually exist; it's just
;;; a "place holder" for FIXNUM_TRUNCATE.  See the comments in
;;; library.lisp.

("/%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FIXNUM_DIVIDE"
	:lambda-list (i divisor)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("/%SINGLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:operator timpl::c/
	:lambda-list (i j)
	:nonconsing t
	:foreign-protocol :operator
	:foreign-arguments ((:single-float nil) (:single-float nil))
	:foreign-return-type :single-float
	)
    )

("/%DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:operator timpl::c/
	:lambda-list (i j)
	:nonconsing t
	:foreign-protocol :operator
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :double-float
	)
    )

("<%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_LT"
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :macro
	:argument-types (fixnum fixnum)
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("<%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c<
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :boolean
	)
    )

("<=%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_LE"
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :macro
	:argument-types (fixnum fixnum)
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("<=%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c<=
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:argument-types (fixnum fixnum)
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :boolean
	)
    )

("=%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_EQ"
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :macro
	:argument-types (fixnum fixnum)
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("=%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c==
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :boolean
	)
    )

(">=%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_GE"
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :macro
	:argument-types (fixnum fixnum)
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

(">=%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c>=
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :boolean
	)
    )

(">%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_GT"
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :macro
	:argument-types (fixnum fixnum)
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

(">%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c>
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :boolean
	)
    )

("/=%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_NE"
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :macro
	:argument-types (fixnum fixnum)
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("/=%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c!=
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :boolean
	)
    )

("<%DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c<
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :boolean
	)
    )

("<%SINGLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c<
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:foreign-arguments ((:single-float nil) (:single-float nil))
	:foreign-return-type :boolean
	)
    )

("<=%DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c<=
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :boolean
	)
    )

("<=%SINGLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c<=
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:foreign-arguments ((:single-float nil) (:single-float nil))
	:foreign-return-type :boolean
	)
    )

("=%DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c==
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :boolean
	)
    )

("=%SINGLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c==
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:foreign-arguments ((:single-float nil) (:single-float nil))
	:foreign-return-type :boolean
	)
    )

(">=%DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c>=
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :boolean
	)
    )

(">=%SINGLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c>=
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:foreign-arguments ((:single-float nil) (:single-float nil))
	:foreign-return-type :boolean
	)
    )

(">%DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c>
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :boolean
	)
    )

(">%SINGLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c>
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:foreign-arguments ((:single-float nil) (:single-float nil))
	:foreign-return-type :boolean
	)
    )

("/=%DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c!=
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :boolean
	)
    )

("/=%SINGLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c!=
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :operator
	:foreign-arguments ((:single-float nil) (:single-float nil))
	:foreign-return-type :boolean
	)
    )

("1-%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_SUB1"
	:lambda-list (i)
	:return-type fixnum
	:foreign-protocol :macro
	:argument-types (fixnum)
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("1+%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_ADD1"
	:lambda-list (i)
	:return-type fixnum
	:requires-return-type-declaration t
	:foreign-protocol :macro
	:argument-types (fixnum)
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("1+%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil))
	:foreign-return-type :long
	:requires-return-type-declaration t
	)
    )

("1+%INT64"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:signed-64bit nil))
	:foreign-return-type :signed-64bit
	:requires-return-type-declaration t
	)
    )

("1+%DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("1+%SINGLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:single-float nil))
	:foreign-return-type :single-float
	)
    )

("1-%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil))
	:foreign-return-type :long
	:requires-return-type-declaration t
	)
    )

("1-%DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("1-%SINGLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:single-float nil))
	:foreign-return-type :single-float
	)
    )

("ABS%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_ABS"
	:lambda-list (i)
	:return-type fixnum
	:foreign-protocol :macro
	:argument-types (fixnum)
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("ABS%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "ABS"
	:allow-multiple-uses-of-entry-name t
	:lambda-list (d)
	:foreign-protocol :macro
	:foreign-arguments ((:long t))
	:foreign-return-type :long
	)
    )

("ASH%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FIXNUM_ASH"
	:lambda-list (i shift)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("ASH-RIGHT%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:requires-return-type-declaration t
	;; :return-type fixnum
	:argument-types (fixnum ; (signed-byte #+x86-64 64 #-x86-64 32)
			 (integer * 0))
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("ASH-LEFT%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:requires-return-type-declaration t
	;; :return-type fixnum
	:argument-types (fixnum ; (signed-byte #+x86-64 64 #-x86-64 32)
			 (integer 0 *))
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("CEILING%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FIXNUM_CEILING"
	:lambda-list (i j)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("CEILING1%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "FIXNUM_CEILING1"
	:lambda-list (i)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("DECF%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:macro)
    )

("DPB%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FIXNUM_DPB"
	:lambda-list (newbyte bytespec i)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t) (:object nil))
	:foreign-return-type :object
	)
    )

("EVENP%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_EVENP"
	:lambda-list (i)
	:return-type t
	:foreign-protocol :macro
	:argument-types (fixnum)
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("EVENP%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil))
	)
    )

("FLOOR%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FIXNUM_FLOOR"
	:lambda-list (i divisor)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("FLOOR1%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "FIXNUM_FLOOR1"
	:lambda-list (i)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("FLOOR-POSITIVE%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i divisor)
	:operator timpl::c/
	:foreign-protocol :operator
	:argument-types ((integer 0 *) (integer 0 *))
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("INCF%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:macro)
    )

("ISQRT%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FIXNUM_ISQRT"
	:lambda-list (i)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("LDB%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FIXNUM_LDB"
	:lambda-list (bytespec i)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("LOGAND%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_LOGAND"
	:lambda-list (i j)
	:return-type fixnum
	:foreign-protocol :macro
	:argument-types (fixnum fixnum)
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("LOGAND%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::cbitand
	:lambda-list (i j)
	:foreign-protocol :operator
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("LOGANDC1%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("LOGANDC2%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FIXNUM_LOGANDC2"
	:lambda-list (i j)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("LOGANDC2%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("LOGBITP%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FIXNUM_LOGBITP"
	:lambda-list (index i)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("LOGBITP%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:argument-types ((signed-byte #+x86-64 64 #-x86-64 32)
			 (integer 0 #+x86-64 63 #-x86-64 31))
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil) (:long nil))
	)
    )

("LOGCOUNT%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FIXNUM_LOGCOUNT"
	:lambda-list (i)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("LOGEQV%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_LOGEQV"
	:lambda-list (i j)
	:return-type fixnum
	:foreign-protocol :macro
	:argument-types (fixnum fixnum)
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("LOGEQV%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("LOGIOR%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_LOGIOR"
	:lambda-list (i j)
	:return-type fixnum
	:foreign-protocol :macro
	:argument-types (fixnum fixnum)
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("LOGIOR%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::cbitor
	:lambda-list (i j)
	:foreign-protocol :operator
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("LOGNAND%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("LOGNOR%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("LOGNOT%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i)
	:entry-name "FIXNUM_LOGNOT"
	:return-type fixnum
	:foreign-protocol :macro
	:argument-types (fixnum)
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("LOGNOT%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::cbitnot
	:lambda-list (i)
	:foreign-protocol :operator
	:foreign-arguments ((:long nil))
	:foreign-return-type :long
	)
    )

("LOGORC1%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("LOGORC2%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("LOGTEST%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FIXNUM_LOGTEST"
	:lambda-list (i j)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :boolean
	)
    )

("LOGTEST%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil) (:long nil))
	)
    )

("LOGXOR%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_LOGXOR"
	:lambda-list (i j)
	:return-type fixnum
	:foreign-protocol :macro
	:argument-types (fixnum fixnum)
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("LOGXOR%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::cbitxor
	:lambda-list (i j)
	:foreign-protocol :operator
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("LSH%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "FIXNUM_LSH"
	:lambda-list (i shift)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("MAX%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_MAX"
	:lambda-list (i j)
	:return-type fixnum
	:foreign-protocol :macro
	:argument-types (fixnum fixnum)
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("MAX%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "MAX"
	:allow-multiple-uses-of-entry-name t
	:lambda-list (x y)
	:foreign-protocol :macro
	:foreign-arguments ((:long t) (:long t))
	:foreign-return-type :long
	)
    )

("MIN%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_MIN"
	:lambda-list (i j)
	:return-type fixnum
	:foreign-protocol :macro
	:argument-types (fixnum fixnum)
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("MIN%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "MIN"
	:allow-multiple-uses-of-entry-name t
	:lambda-list (x y)
	:foreign-protocol :macro
	:foreign-arguments ((:long t) (:long t))
	:foreign-return-type :long
	)
    )

("MINUSP%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FIXNUM_MINUSP"
	:lambda-list (i)
	:return-type t
	:foreign-protocol :macro
	:argument-types (fixnum)
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("MINUSP%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil))
	)
    )

("MINUSP%DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:double-float nil))
	)
    )

("MINUSP%SINGLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:single-float nil))
	)
    )

("MOD%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FIXNUM_MOD"
	:lambda-list (i divisor)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object t))
	:foreign-return-type :object
	)
    )

("MOD-POSITIVE%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i divisor)
	:operator timpl::crem
	:foreign-protocol :operator
	:argument-types ((integer 0 *) (integer 0 *))
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("NEGATE%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_NEGATE"
	:lambda-list (i)
	:return-type fixnum
	:foreign-protocol :macro
	:argument-types (fixnum)
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	)
    )

("ODDP%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:return-type t
	:entry-name "FIXNUM_ODDP"
	:lambda-list (i)
	:foreign-protocol :macro
	:argument-types (fixnum)
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("ODDP%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil))
	)
    )

("PLUSP%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FIXNUM_PLUSP"
	:lambda-list (i)
	:return-type t
	:foreign-protocol :macro
	:argument-types (fixnum)
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("PLUSP%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil))
	)
    )

("PLUSP%DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:double-float nil))
	)
    )

("PLUSP%SINGLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:single-float nil))
	)
    )

("REM%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FIXNUM_REM"
	:lambda-list (i divisor)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("RSH%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "FIXNUM_RSH"
	:lambda-list (i shift)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("SHIFT-LEFT%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c<<
	:lambda-list (i j)
	:requires-return-type-declaration t
	:argument-types ((unsigned-byte #+x86-64 64 #-x86-64 32)
			 (integer 0 *))
	:foreign-protocol :operator
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("SHIFT-RIGHT%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::c>>
	:lambda-list (i j)
	:requires-return-type-declaration t
	:argument-types ((unsigned-byte #+x86-64 64 #-x86-64 32)
			 (integer 0 *))
	:foreign-protocol :operator
	:foreign-arguments ((:long nil) (:long nil))
	:foreign-return-type :long
	)
    )

("TRUNCATE%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "FIXNUM_TRUNCATE"
	:lambda-list (i divisor)
	:return-type fixnum
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("ZEROP%"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "FIXNUM_ZEROP"
	:lambda-list (i)
	:return-type t
	:foreign-protocol :macro
	:argument-types (fixnum)
	:foreign-arguments ((:object nil))
	:foreign-return-type :boolean
	)
    )

("ZEROP%LONG"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:long nil))
	)
    )

("ZEROP%DOUBLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:double-float nil))
	)
    )

("ZEROP%SINGLE"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:lambda-list (i j)
	:foreign-protocol :secret-special-form
	:foreign-arguments ((:single-float nil))
	)
    )

;;; Type-specific boxed double-float operators

("+%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_ADD"
	:lambda-list (x y)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("*%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_TIMES"
	:lambda-list (x y)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("-%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_MINUS"
	:lambda-list (x y)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("/%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_DIVIDE"
	:lambda-list (x y)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("<%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_LT"
	:lambda-list (x y)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("<=%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_LE"
	:lambda-list (x y)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("=%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_EQ"
	:lambda-list (x y)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

(">%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_GT"
	:lambda-list (x y)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

(">=%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_GE"
	:lambda-list (x y)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("/=%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_NE"
	:lambda-list (x y)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :boolean
	)
    )

("1+%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_ADD1"
	:lambda-list (x)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("1-%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_SUB1"
	:lambda-list (x)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("NEGATE%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DOUBLE_FLOAT_NEGATE"
	:lambda-list (x)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("ABS%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_ABS"
	:lambda-list (x)
	:return-type double-float
	:foreign-protocol :macro
	:argument-types (double-float)
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("ATAN1%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DOUBLE_FLOAT_ATAN1"
	:lambda-list (y)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("ATAN%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_ATAN"
	:lambda-list (y x)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("CEILING1%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DOUBLE_FLOAT_CEILING1"
	:lambda-list (x)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("CEILING%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_CEILING"
	:lambda-list (x divisor)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("COS%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_COS"
	:lambda-list (radians)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("EXP%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_EXP"
	:lambda-list (power)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("EXPT%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_EXPT"
	:lambda-list (x power)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("FLOOR1%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DOUBLE_FLOAT_FLOOR1"
	:lambda-list (x)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("FLOOR%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_FLOOR"
	:lambda-list (x divisor)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("FROUND1%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DOUBLE_FLOAT_FROUND1"
	:lambda-list (x)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("FROUND%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_FROUND"
	:lambda-list (x divisor)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("LOG1%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DOUBLE_FLOAT_LOG1"
	:lambda-list (x)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("LOG%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_LOG"
	:lambda-list (x base)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("MAX%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_MAX"
	:lambda-list (x y)
	:return-type double-float
	:foreign-protocol :macro
	:argument-types (double-float double-float)
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("MIN%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_MIN"
	:lambda-list (x y)
	:return-type double-float
	:foreign-protocol :macro
	:argument-types (double-float double-float)
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("MINUSP%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_MINUSP"
	:lambda-list (x)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("PLUSP%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_PLUSP"
	:lambda-list (x)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )

("ROUND1%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DOUBLE_FLOAT_ROUND1"
	:lambda-list (x)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("ROUND%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_ROUND"
	:lambda-list (x divisor)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("SIN%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_SIN"
	:lambda-list (radians)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("SQRT%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_SQRT"
	:lambda-list (x)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("TAN%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_TAN"
	:lambda-list (radians)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("TRUNCATE1%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DOUBLE_FLOAT_TRUNCATE1"
	:lambda-list (x)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :object
	)
    )

("TRUNCATE%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_TRUNCATE"
	:lambda-list (x divisor)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t) (:object t))
	:foreign-return-type :object
	)
    )

("ZEROP%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOAT_ZEROP"
	:lambda-list (x)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :boolean
	)
    )


;;; Double-float boxing and unboxing macros
;;; Temporarily commented out because of name conflict
#|

("BOX%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DOUBLE_TO_DOUBLE_FLOAT"
	:lambda-list (d)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :object
	)
    )

("UNBOX%D"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DOUBLE_FLOAT_TO_DOUBLE"
	:lambda-list (x)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:object t))
	:foreign-return-type :double-float
	)
    )
|#


;;; Type-specific unboxed double-float operators

("+%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_ADD"
	:lambda-list (d e)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :double-float
	)
    )

("*%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_TIMES"
	:lambda-list (d e)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :double-float
	)
    )

("-%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_MINUS"
	:lambda-list (d e)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :double-float
	)
    )

("/%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_DIVIDE"
	:lambda-list (d e)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :double-float
	)
    )

("<%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_LT"
	:lambda-list (d e)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :boolean
	)
    )

("<=%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_LE"
	:lambda-list (d e)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :boolean
	)
    )

("=%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_EQ"
	:lambda-list (d e)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :boolean
	)
    )

(">%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_GT"
	:lambda-list (d e)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :boolean
	)
    )

(">=%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_GE"
	:lambda-list (d e)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :boolean
	)
    )

("/=%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_NE"
	:lambda-list (d e)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :boolean
	)
    )

("1+%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_ADD1"
	:lambda-list (d)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("1-%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_SUB1"
	:lambda-list (d)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("NEGATE%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DOUBLE_NEGATE"
	:lambda-list (d)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("ABS%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "ABS"
	:allow-multiple-uses-of-entry-name t
	:lambda-list (d)
	:foreign-protocol :macro
	:foreign-arguments ((:double-float t))
	:foreign-return-type :double-float
	)
    )

("ATAN1%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "atan" ; "DOUBLE_ATAN1"
	:lambda-list (yd)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("ATAN%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "atan2" ; "DOUBLE_ATAN"
	:lambda-list (yd xd)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :double-float
	)
    )

("CEILING1%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DOUBLE_CEILING1"
	:lambda-list (d)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("CEILING%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_CEILING"
	:lambda-list (d divisor)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :double-float
	)
    )

("COS%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "cos" ; "DOUBLE_COS"
	:lambda-list (radians)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("EXP%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "exp" ; "DOUBLE_EXP"
	:lambda-list (power)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("EXPT%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "pow" ; "DOUBLE_EXPT"
	:lambda-list (d power)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :double-float
	)
    )

("FLOOR1%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DOUBLE_FLOOR1"
	:lambda-list (d)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("FLOOR%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FLOOR"
	:lambda-list (d divisor)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :double-float
	)
    )

("FROUND1%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DOUBLE_FROUND1"
	:lambda-list (d)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("FROUND%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_FROUND"
	:lambda-list (d divisor)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :double-float
	)
    )

("LOG1%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "log" ; "DOUBLE_LOG1"
	:lambda-list (d)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("LOG%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "DOUBLE_LOG"
	:lambda-list (d base)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :double-float
	)
    )

("MAX%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "MAX"
	:allow-multiple-uses-of-entry-name t
	:lambda-list (d e)
	:foreign-protocol :macro
	:foreign-arguments ((:double-float t) (:double-float t))
	:foreign-return-type :double-float
	)
    )

("MIN%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "MIN" ; "DOUBLE_MIN"
	:allow-multiple-uses-of-entry-name t
	:lambda-list (d e)
	:foreign-protocol :macro
	:foreign-arguments ((:double-float t) (:double-float t))
	:foreign-return-type :double-float
	)
    )

("MINUSP%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_MINUSP"
	:lambda-list (d)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :boolean
	)
    )

("PLUSP%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_PLUSP"
	:lambda-list (d)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :boolean
	)
    )

("ROUND1%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DOUBLE_ROUND1"
	:lambda-list (d)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("ROUND%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_ROUND"
	:lambda-list (d divisor)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :double-float
	)
    )

("SIN%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "sin" ; "DOUBLE_SIN"
	:lambda-list (radians)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("SQRT%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "sqrt" ; "DOUBLE_SQRT"
	:lambda-list (d)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("TAN%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:entry-name "tan" ; "DOUBLE_TAN"
	:lambda-list (radians)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("TRUNCATE1%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "DOUBLE_TRUNCATE1"
	:lambda-list (d)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :double-float
	)
    )

("TRUNCATE%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_TRUNCATE"
	:lambda-list (d divisor)
	:return-type double-float
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil) (:double-float nil))
	:foreign-return-type :double-float
	)
    )

("ZEROP%RD"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:entry-name "DOUBLE_ZEROP"
	:lambda-list (d)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:double-float nil))
	:foreign-return-type :boolean
	)
    )

("%SET-PACKAGE"
   (:symbol
      :package "TRUN"
      :import-from nil
      :exists-at-runtime nil
      )
   (:function
     :entry-name "SET_PACKAGE"
     :lambda-list (name)
     :foreign-protocol :macro
     :foreign-arguments ((:string nil))
     :foreign-return-type :object
     )
   )

;;; All of the static-xxx guys are used to allocate constants from static
;;; storage during the processing of top-level forms.  See constant.lisp.

("%STATIC-BIT-ARRAY"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STATIC_BIT_ARRAY"
        :lambda-list (n &rest dimensions)
	:return-type (array bit)    ; initialized to 0
	:foreign-protocol :macro
	:foreign-arguments ((:int nil))
	:foreign-return-type :object
	)
    )

("%STATIC-CHAR-ARRAY"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STATIC_CHAR_ARRAY"
        :lambda-list (n &rest dimensions)
	:return-type (array character)  ; initialized to 0
	:foreign-protocol :macro
	:foreign-arguments ((:int nil))
	:foreign-return-type :object
	)
    )

("%STATIC-CONS"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STATIC_CONS"
        :lambda-list (car cdr)
	:return-type cons
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%STATIC-FLOAT"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STATIC_FLOAT"
        :lambda-list (c-float)
	:return-type float
	:foreign-protocol :macro
	:foreign-arguments ((:float nil))
	:foreign-return-type :object
	)
    )

("%STATIC-GENERAL-ARRAY"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STATIC_GENERAL_ARRAY"
        :lambda-list (n &rest dimensions)
	:return-type (array t)  ; initialized to nil
	:foreign-protocol :macro
	:foreign-arguments ((:int nil))
	:foreign-return-type :object
	)
    )

("%STATIC-LIST"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STATIC_LIST"
	:lambda-list (n &rest objects)
	:return-type list
	:foreign-protocol :macro
	:foreign-arguments ((:int nil))
	:foreign-return-type :object
	)
    )

("%STATIC-LIST-STAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STATIC_LIST_STAR"
	:lambda-list (n &rest objects)
	:return-type list
	:foreign-protocol :macro
	:foreign-arguments ((:int nil))
	:foreign-return-type :object
	)
    )

("%STATIC-NEGATIVE-BIGNUM"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STATIC_NEGATIVE_BIGNUM"
	:lambda-list (length)
	:return-type bignum
	:foreign-protocol :macro
	:foreign-arguments ((:int nil))
	:foreign-return-type :object
	)
    )

("%STATIC-PACKAGE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STATIC_PACKAGE"
        :lambda-list (name)
	:return-type package   ; like find-package but never returns nil
        :foreign-protocol :macro
	:foreign-arguments ((:string nil))
	:foreign-return-type :object
	)
    )

("%STATIC-POSITIVE-BIGNUM"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STATIC_POSITIVE_BIGNUM"
	:lambda-list (length)
	:return-type bignum
	:foreign-protocol :macro
	:foreign-arguments ((:int nil))
	:foreign-return-type :object
	)
    )

("%STATIC-RATIO"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STATIC_RATIO"
	:lambda-list (numerator denominator)
	:return-type ratio
	:foreign-protocol :macro
	:foreign-arguments ((:object nil) (:object nil))
	:foreign-return-type :object
	)
    )

("%STATIC-STRING"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STATIC_STRING"
        :lambda-list (c-string)
	:return-type string
	:foreign-protocol :macro
	:foreign-arguments ((:string nil))
	:foreign-return-type :object
	)
    )

("%STATIC-SYMBOL"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "STATIC_SYMBOL"
        :lambda-list (string package-or-nil)     ; kind of like intern
	:return-type string
	:foreign-protocol :macro
	:foreign-arguments ((:string nil) (:object nil))
	:foreign-return-type :object
	)
    )

;;; This is used in various places.  It should just be implemented to
;;; be equivalent to (list name) -- its purpose is just to return a
;;; unique object.

("%UNIQUE-TAG"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :entry-name "UNIQUE_TAG"
        :lambda-list (name)
	:return-type t
	:foreign-protocol :macro
	:foreign-arguments ((:object nil))
	:foreign-return-type :object
	))

;;; This represents the unsupplied-argument marker that is defined in the RTL.

("%UNSUPPLIED-MARKER"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:constant
        :variable-name "_"
	:simple-p t
	:foreign-p t
	:dump-definition-p nil
	)
    )


;;; This is used to generate local temp declarations for macros
;;; such as CAR and CONSP.
;;; It's just a place-holder for the :uses-locals slot in these
;;;   macros to refer to emit-local-temp-declaration.

("%LOCAL-TEMP-DECLARATION"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    )

;;; This is the place holder for STORE-VALUE and STORE-VALUES,
;;; which are (as a temporary hack) implemented using the local
;;; variable "result".

("%STORE-VALUE-TEMP-DECLARATION"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    )

("%PRINTF"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing t
        :entry-name "printf"
	:lambda-list (control-string &rest printf-args)
	:foreign-protocol :macro
	:foreign-arguments ((:string nil) &rest (:simple-c-type nil))
	:foreign-return-type :int
	)
    )

;;; Error handler, in lieu of a condition system.  Used by REP loop.

("*BREAK-FUNCTION*"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:variable
        :return-type (or null function)
	;; :initial-value nil
	)
    )

("*GC-INHIBIT*"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:variable
        :return-type (member t nil)
	;; :initial-value nil
	)
    )

("*GC-SILENCE*"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:variable
        :return-type (member t nil)
	;; :initial-value nil
	)
    )

;;; The remaining functions listed here all need to be real Lisp-callable
;;; functions, for various reasons.

;;; Appears in expansion of DO-SYMBOLS and friends.  See rtlpacks.lisp.

("ADVANCE-DO-SYMBOLS-ITERATOR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (state)
	:return-type (values symbol t)
	:unsupported t
	)
    )


;;; Appears in expansion of WITH-PACKAGE-ITERATOR.  See rtlpacks.lisp.

("ADVANCE-WITH-PACKAGE-ITERATOR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (state)
	:return-type (values &rest t)
	:unsupported t
	)
    )

("ALLOW-GC"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    ;; Ensure specified amount of space available before next GC.
    (:function
        :lambda-list (dynamic array)
	:return-type t
	)
    )

("BACKQUOTE"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:random-syntax)
    )

;;; Helper for print-unreadable-object

("BEGIN-PRINT-UNREADABLE-OBJECT"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object stream type identity bodyp)
	:return-type t
	)
    )


;;; Helper function for the TIME macro.  Returns the current run-time 
;;; and real-time as values.

("BEGIN-TIME"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list ()
	:return-type (values integer integer)
	)
    )



;;; Primitive predicate for (typep <object> 'bignum)

("BIGNUMP"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%bignump t))
	)
    )

;;; Primitive predicate for (typep <object> 'bit)

("BITP"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%bitp t))
	)
    )

("BROADCAST-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%broadcast-stream-p t))
	)
    )



#+translator-supports-clos
("CLASS-WRAPPER"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:type-name)
    (:class-name)
    )

#+translator-supports-clos
("CLASS-WRAPPER-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%class-wrapper-p t))
	)
    )

("COBJECT"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:type-name)
    (:class-name)
    )

("COBJECTP"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%cobjectp t))
	)
    )

("COMMA"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:random-syntax)
    )

("COMMA-ATSIGN"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:random-syntax)
    )

("COMMA-DOT"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:random-syntax)
    )

("CONCATENATED-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%concatenated-stream-p t))
	)
    )

;;; The function CONSTANT-INITFUNCTION is used by the object system to compute
;;; slot initfunctions when the initform is a constant.  The idea is to reduce
;;; the number of distinct function objects generated by only allocating one
;;; function per EQL object.  CONSTANT-INITFUNCTION is externally a lot like
;;; CONSTANTLY, but the returned function doesn't need to accept any arguments.
;;; It is not equivelent to CONSTANTLY because it might not be a good idea to
;;; have CONSTANTLY cache the function associated with each value it is called
;;; with, since this would prevent the value and function from being GC'ed
;;; (assuming weak tables or some such mechanism are not available).  For
;;; initfunctions this isn't such an issue because classes tend to be pretty
;;; long lived and unchanging, so the value and initfunction are not likely to
;;; be available for GC.
;;;
;;; A possible Lisp definition for CONSTANT-INITFUNCTION is:
;
;(defvar *constant-initfunctions*)
;
;(defun trun:constant-initfunction (value)
;  ;; Initialize table first time through.
;  (unless (boundp '*constant-initfunctions*)
;    (let ((table (make-hash-table :test 'eql)))
;      (setf (gethash nil table) #'trun:constantly-false)
;      (setf (gethash t table) #'trun:constantly-true)
;      (setf *constant-initfunctions* table)))
;  ;; Use corresponding function from the table if one exists.
;  (or (gethash value *constant-initfunctions*)
;      ;; Otherwise, cons up a closure over the value, record it in the table
;      ;; for later calls, and return the closure.
;      (setf (gethash value *constant-initfunctions*)
;	    ;; Hopefully, any compiler smart enough to optimize away this
;	    ;; binding will also be smart enough to recognize that the bound
;	    ;; value is closed over and avoid closing over the outer binding
;	    ;; by actually not optimizing away this binding.
;	    (let ((value value)) #'(lambda () ,value)))))

("CONSTANT-INITFUNCTION"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (value)
	:return-type compiled-function
	)
    )

("CONSTANTLY-FALSE"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    ;; Function which ignores any number of arguments and returns NIL.
    (:function
        :lambda-list (&rest arguments)
        :return-type null
	)
    )

("CONSTANTLY-NIL-INITFUNCTION"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    ;; Similar to the function CONSTANTLY-FALSE, but accepts no arguments.
    ;; This is used in slot initfunctions rather than CONSTANTLY-FALSE so that
    ;; all slot initfunctions have the same argument pattern.
    (:function
        :lambda-list ()
	:return-type null
	)
    )

("CONSTANTLY-T-INITFUNCTION"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    ;; Similar to the function CONSTANTLY-TRUE, but accepts no arguments.
    ;; This is used in slot initfunctions rather than CONSTANTLY-TRUE so that
    ;; all slot initfunctions have the same argument pattern.
    (:function
        :lambda-list ()
	:return-type (eql t)
	)
    )

("CONSTANTLY-TRUE"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    ;; Function which ignores any number of arguments and returns T.
    (:function
        :lambda-list (&rest arguments)
	:return-type t
	)
    )


;;; A bunch of helper functions for DEFPACKAGE.  See
;;; defpackage.lisp for what they should do.

("DEFPACKAGE-EXPORT"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (name package)
	:return-type null
	)
    )

("DEFPACKAGE-IMPORT-FROM"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (name from-package-name package)
	:return-type null
	)
    )

("DEFPACKAGE-INTERN"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (name package)
	:return-type null
	)
    )

("DEFPACKAGE-SHADOW"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (name package)
	:return-type null
	:unsupported t
	)
    )

("DEFPACKAGE-SHADOWING-IMPORT-FROM"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (name from-package-name package)
	:return-type null
	:unsupported t
	)
    )
        
("DEFPACKAGE-USE-PACKAGE"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (package-name package)
	:return-type null
	)
    )


;;; This is the new-value function used in the expansion of the read-modify-
;;; write macro REMF

("DO-REMF"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (place indicator)
	:return-type t
	)
    )


("ECHO-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%echo-stream-p t))
	)
    )

#+translator-supports-clos
("EFFECTIVE-METHOD"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:class-name)
    (:type-name)
    )

#+translator-supports-clos
("EFFECTIVE-METHOD-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    ;; Type predicate for EFFECTIVE-METHOD.
    (:function
        :entry-name "effective_method_p"
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%effective-method-p t))
	)
    )

;;; This thing is used by the handlers for DEFVAR and DEFPARAMETER.

("ESTABLISH-SPECIAL-VARIABLE"
    (:symbol
	:package "TRUN"
	:import-from nil)
    (:special-form)
    )

;;; Internal special forms for use in implementing *function-symbols*
;;; and *special-symbols*

("LINK-FUNCTION"
    (:symbol
	:package "TRUN"
	:exists-at-runtime nil
	:import-from nil)
    (:special-form)
    )


("LINK-SETF-FUNCTION"
    (:symbol
	:package "TRUN"
	:exists-at-runtime nil
	:import-from nil)
    (:special-form)
    )

("LINK-VARIABLE"
    (:symbol
	:package "TRUN"
	:exists-at-runtime nil
	:import-from nil)
    (:special-form)
    )

("UNBOUND-SPECIAL-P"
    (:symbol
	:package "TRUN"
	:exists-at-runtime nil
	:import-from nil)
    (:special-form)
    )

;;; Appears in the expansion of WITH-OUTPUT-TO-STRING when the string
;;; argument is supplied.  It must be a string with a fill pointer
;;; and this function is supposed to make it into a string-stream object.

("EXTEND-STRING-OUTPUT-STREAM"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (string)
	:return-type string-stream
	)
    )



("FILE-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%file-stream-p t))
	)
    )


;;; This is probably broken.

("FINISH-PRINT-UNREADABLE-OBJECT"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object stream identity bodyp)
	:return-type t
	)
    )



;;; Another helper function for TIME.  Takes start run and real time as
;;; arguments, computes the difference from the current times, and prints
;;; the message to *trace-output*.  Return value is discarded.

("FINISH-TIME"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (start-run-time start-real-time)
	:return-type t
	)
    )


("FIXNUMP"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%fixnump t))
	)
    )

("FORCE-GC"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    ;; Force an immediate garbage collection.
    (:function
        :lambda-list ()
	:return-type t
	)
    )

;;; Appear in macroexpansion of WITH-HASH-TABLE-ITERATOR.

("HASH-TABLE-ITERATOR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (state)
	:return-type t
	)
    )

("BEGIN-HASH-TABLE-ITERATOR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (hash-table)
	:return-type t
	)
    )

("END-HASH-TABLE-ITERATOR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (state)
	:return-type t
	)
    )

("CLEANUP-HASH-TABLE-ITERATOR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (state)
	:return-type t
	)
    )


;;; Appear in macroexpansion of DO-SYMBOLS and friends.  See rtlpacks.lisp.

("INITIALIZE-DO-ALL-SYMBOLS-ITERATOR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list ()
	:return-type t
	:unsupported t
	)
    )

("INITIALIZE-DO-EXTERNAL-SYMBOLS-ITERATOR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (package)
	:return-type t
	:unsupported t
	)
    )

("INITIALIZE-DO-SYMBOLS-ITERATOR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (package)
	:return-type t
	:unsupported t
	)
    )

("INITIALIZE-WITH-PACKAGE-ITERATOR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (package-list internal-p external-p inherited-p)
	:return-type t
	:unsupported t
	)
    )

("INTERACTION-STREAM"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:type-name)
    (:class-name)
    )

("INTERACTION-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%interaction-stream-p t))
	)
    )

("INTERNAL-MARKER"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:type-name)
    (:class-name)
    )

("INTERNAL-MARKER-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%internal-marker-p t))
        :unsupported t
	)
    )

("KEYWORD-PACKAGE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:package
	:variable-name "Pkeyword"
	:package-name "KEYWORD"
	)
    )

("LOGICAL-PATHNAME-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%logical-pathname-p t))
        :unsupported t
	)
    )

("MAKE-STRUCTURE-CLASS"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (class superclass local-slots print-function
		      constructor doc-string)
	:return-type symbol
        )
    )

#+translator-supports-clos
("METHOD-COMBINATION-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%method-combination-p t))
	)
    )

;;; A helper for ASSERT, CCASE, etc.
;;; Not implemented yet in RTL, so for now there's a translator-macro
;;; in emacros.lisp. The :macro entry should be removed, and the
;;; :function entry uncommented, when the RTL function is implemented.

("PROMPT-FOR-VALUE"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
;   (:function
;       :lambda-list (place-info)
;	:return-type t
;	:unsupported t
;	)
    (:macro)
    )



;;; More primitive predicates...

("RATIOP"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%ratiop t))
	)
    )

("SEQUENCEP"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%sequencep t))
	)
    )

;;; store functions used to update generalized variables

("SET-CHAR"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (string index new-character)
	:return-type character
        ;; :unsupported t
	:transforms ((trun:%set-char t))
	)
    )

("SET-COMPILER-MACRO-FUNCTION"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :unsupported t
        :lambda-list (name new-function)
	:return-type t
	)
    )

("SET-ELT"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (sequence index new-elt)
	:return-type t
	)
    )

("SET-FDEFINITION"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (name new-function)
	:return-type function
	)
    )

("SET-GET"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (symbol indicator new-value)
	:return-type t
	)
    )

("SET-GETF"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (place indicator new-value)
	:return-type cons
	)
    )

("SET-GETHASH"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (key hash-table new-value)
	:return-type t
	)
    )

("SET-LOGICAL-PATHNAME-TRANSLATIONS"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :unsupported t
        :lambda-list (host new-translations)
	:return-type list
	)
    )

("SET-MACRO-FUNCTION"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
	:lambda-list (name new-function)
	:return-type t
	)
    )

("SET-PACKAGE"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (name)
	:return-type package
	)
    )

("SET-READTABLE-CASE"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :unsupported t
	:lambda-list (readtable new-readtable-case)
	:return-type keyword
	)
    )

("SET-ROW-MAJOR-AREF"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
	:lambda-list (array index new-value)
	:return-type t
	:transforms ((trun:%set-row-major-aref t))
	)
    )

("SET-SETF-FUNCTION"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (symbol new-function)
	:return-type function
	:transforms ((trun:%set-setf-function t))
	)
    )

("SET-SLOT-VALUE"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    #+translator-supports-clos
    (:function
        :lambda-list (object slot-name value)
	:return-type t
	)
    #-translator-supports-clos
    (:function
        :unsupported t
	)
    )

;;; Note:  The lambda-list for this "function" isn't, strictly speaking,
;;; accurate; it's just a place-holder for %set-subseq-1 and %set-subseq-2.

("SET-SUBSEQ"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (sequence start end new-sequence)
	:return-type sequence
	:unsupported t
	)
    )

("SET-SYMBOL-FUNCTION"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (symbol new-function)
	:return-type function
	:transforms ((trun:%set-symbol-function t))
	)
    )

("SET-SYMBOL-PLIST"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (symbol list)
	:return-type list
	:transforms ((trun:%set-symbol-plist t))
	)
    )

("SETF-FUNCTION"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (symbol)
	:return-type compiled-function  ;*** change if new function types added
	:transforms ((trun:%setf-function t))
	)
    ;; This is not allowed; the same c function can't be the function entry
    ;; for both set-setf-function and (setf setf-function)
    ;(:setf-function
    ;    :lambda-list (function symbol)
    ;    :entry-name "set_setf_function"
    ;    :transforms ((trun:%set-setf-function t))
    ;    )
    (:setf-place)
    )

("SIMPLE-ARRAY-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%simple-array-p t))
	)
    )

("STANDARD-OBJECT-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%standard-object-p t))
	)
    )

("STRING-INPUT-STREAM"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:type-name)
    (:class-name)
    )

("STRING-INPUT-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%string-input-stream-p t))
	)
    )

("STRING-OUTPUT-STREAM"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:type-name)
    (:class-name)
    )

("STRING-OUTPUT-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%string-output-stream-p t))
	)
    )

("STRING-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%string-stream-p t))
	)
    )


("STRUCTURE-OBJECT-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%structure-object-p t))
	)
    )



;;; Used in the expansion of WITH-INPUT-FROM-STRING.  It returns the
;;; index of the next character in the string-input-stream to be read,
;;; or the length of the string if all characters have been read.

("STRING-STREAM-INDEX"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (string-input-stream)
	:return-type fixnum
	)
    )


("SYNONYM-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :unsupported t
	:lambda-list (object)
	:return-type t
	:transforms ((trun:%synonym-stream-p t))
	)
    )

;;; More static package names

("TCL-PACKAGE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:package
        :package-name "TCL"
	:variable-name "Pcl"
	)
    )

("TCL-USER-PACKAGE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:package
        :package-name "TCL-USER"
	:variable-name "Pcl_user"
	)
    )

("TCLOS-PACKAGE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:package
        :package-name "TCLOS"
	:variable-name "Pclos"
	)
    )

("TCLOSX-PACKAGE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:package
        :package-name "TCLOSX"
	:variable-name "Pclosx"
	)
    )

("TCLOS-RUN-PACKAGE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:package
        :package-name "TCLOS-RUN"
	:variable-name "Pclos_run"
	)
    )

("TRUN-PACKAGE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:package
        :package-name "TRUN"
	:variable-name "Ptrun"
	)
    )

("TX-PACKAGE"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:package
        :package-name "TX"
	:variable-name "Ptx"
	)
    )

("TWO-WAY-STREAM-P"
    (:symbol
        :package "TRUN"
	:import-from nil
	)
    (:function
        :lambda-list (object)
	:return-type t
	:transforms ((trun:%two-way-stream-p t))
	)
    )

("USERFUNS"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "userfuns"
	:lambda-list ()
	:foreign-protocol :macro
	:foreign-arguments ()
	:foreign-return-type :void
	)
    )

("USERINIT"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "userinit"
	:lambda-list ()
	:foreign-protocol :macro
	:foreign-arguments ()
	:foreign-return-type :void
	)
    )

("USERSYMS"
    (:symbol
	:package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
	:entry-name "usersyms"
	:lambda-list ()
	:foreign-protocol :macro
	:foreign-arguments ()
	:foreign-return-type :void
	)
    )

;;; Used by the test suites only.

("DO-TEST"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:macro)
    )

("%DO-TEST"
    (:symbol
        :package "TRUN"
        :import-from nil
	:exists-at-runtime nil
	)
     (:function
        :entry-name "do_test"
	:lambda-list (string test-result expected-result)
	:return-type null
	:foreign-protocol :macro
	:foreign-arguments ((:string nil) (:object nil) (:object nil))
	:foreign-return-type :object
	)
     )


("DO-SIDE-EFFECTS-TEST"
    (:symbol
        :package "TRUN"
        :import-from nil
	:exists-at-runtime nil
	)
     (:function
        :entry-name "do_side_effects_test"
	:lambda-list (string test-result expected-result)
	:return-type null
	:foreign-protocol :macro
	:foreign-arguments ((:string nil) (:object nil) (:object nil))
	:foreign-return-type :object
	)
     )

("SHARED-STRUCTURE-P"
     (:symbol
         :package "TRUN"
	 :import-from nil
	 :exists-at-runtime nil
	 )
     (:function
         :entry-name "shared_structure_p"
	 :lambda-list (sequence1 sequence2)
	 :return-type t
	 :foreign-protocol :foreign-arguments-function
	 )
     )

("WITH-AREA"
    (:symbol
	:package "TRUN"
	:import-from nil
	)
    (:special-form))

#+translator-supports-thread
("%LOCK"
    (:symbol
        :package "TRUN"
        :import-from nil
        :exists-at-runtime nil
        )
    (:function
        :entry-name "LOCK"
        :lambda-list (object)
        :foreign-protocol :macro
        :return-type t
        :foreign-arguments ((:object t))
        :foreign-return-type :boolean
        )
    )

#+translator-supports-thread
("%TRYLOCK"
    (:symbol
        :package "TRUN"
        :import-from nil
        :exists-at-runtime nil
        )
    (:function
        :entry-name "TRYLOCK"
        :lambda-list (object)
        :foreign-protocol :macro
        :return-type t
        :foreign-arguments ((:object t))
        :foreign-return-type :boolean
        )
    )

#+translator-supports-thread
("%UNLOCK"
    (:symbol
        :package "TRUN"
        :import-from nil
        :exists-at-runtime nil
        )
    (:function
        :entry-name "UNLOCK"
        :lambda-list (object)
        :foreign-protocol :macro
        :return-type t
        :foreign-arguments ((:object t))
        :foreign-return-type :boolean
        )
    )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;;    Symbols in the keyword package
;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; This probably isn't complete yet either.  

("ABORT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("ACCESSOR"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("ADDRESS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("ADJUSTABLE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("AFTER"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("ALIGNMENT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("ALLOCATION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("ALLOW-OTHER-KEYS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("APPEND"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("ARGUMENT-PRECEDENCE-ORDER"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("ARGUMENTS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("AROUND"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("ARRAY"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("BACK"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("BASE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("BEFORE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("CAPITALIZE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("CASE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )


("CHARACTER"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("CHESTNUT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("CIRCLE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("CLASS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("CLTL2"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("COLUMN-MAJOR"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("COMMON"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("COMMON-LISP"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("CONC-NAME"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("CONSTANT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("CONSTRUCTOR"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("COPIER"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("COUNT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("CREATE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("DATUM"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("DECLARE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("DEFAULT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("DEFAULT-INITARGS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("DEFAULTS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("DESCRIPTION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("DEVICE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("DIRECTION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("DIRECTORY"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("DISPLACED-INDEX-OFFSET"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("DISPLACED-TO"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("DOCUMENTATION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("DOUBLE-FLOAT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("DOWNCASE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("DYNAMIC"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("ELEMENT-TYPE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("END"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("END1"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("END2"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("ENVIRONMENT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("ERROR"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("ESCAPE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("EXPECTED-TYPE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("EXPORT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("EXTERNAL"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("EXTERNAL-FORMAT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("FILL-POINTER"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("FORMAT-STRING"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("FORMAT-ARGUMENTS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("FROM-END"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("FUNCTION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("GENERIC-FUNCTION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("GENERIC-FUNCTION-CLASS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("GENSYM"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("HOST"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("IDENTITY-WITH-ONE-ARGUMENT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("IEEE-FLOATING-POINT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("IF-DOES-NOT-EXIST"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("IF-EXISTS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("IMPORT-FROM"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("INCLUDE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("INDEX"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("INHERITED"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("INITARG"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("INITFORM"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("INITIAL-CONTENTS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("INITIAL-ELEMENT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("INITIAL-OFFSET"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("INITIAL-VALUE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("INPUT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("INSTALLED"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("INSTANCE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("INTERACTION-FUNCTION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("INTERACTIVE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("INTERN"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("INTERNAL"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("INVERT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("IO"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("JUNK-ALLOWED"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("KEY"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("LAMBDA-LIST"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("LENGTH"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("LEVEL"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("LEXICAL"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("LINES"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("LOCAL"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

#+translator-supports-thread
("LOCK"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("MACRO"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("MALLOC"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("METHOD"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("METHOD-CLASS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("METHOD-COMBINATION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("METACLASS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("MISER-WIDTH"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("MOST-SPECIFIC-FIRST"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("MOST-SPECIFIC-LAST"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("NAME"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("NAMED"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("NEW-VERSION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("NEWEST"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("NICKNAMES"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("OLDEST"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("OPERANDS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("OPERATION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("OPERATOR"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("ORDER"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("OUTPUT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("OVERWRITE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("PACKAGE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("PATHNAME"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("PPRINT-DISPATCH"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("PREDICATE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("PRESERVE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("PRESERVE-WHITESPACE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("PRETTY"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("PREVIOUS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("PRINT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("PRINT-FUNCTION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("PROBE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("RADIX"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("READ-EOF"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("READ-ONLY"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("READABLY"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("READER"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("REHASH-SIZE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("REHASH-THRESHOLD"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("RENAME"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("RENAME-AND-DELETE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("REPORT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("REPORT-FUNCTION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("REQUIRED"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("RIGHT-MARGIN"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("ROW-MAJOR"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("SHADOW"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("SHADOWING-IMPORT-FROM"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )


("SINGLE-FLOAT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("SIGNED-8BIT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("SIGNED-16BIT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )


("SIGNED-32BIT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("SIGNED-64BIT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("SIZE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("SPECIAL"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("SPECIAL-FORM"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("START"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("START1"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("START2"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("STATIC"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("STREAM"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("SUPERSEDE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("SYMBOL-MACRO"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("TEST"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("TEST-FUNCTION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("TEST-NOT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("TYPE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("UNSIGNED-8BIT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("UNSIGNED-16BIT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("UNSIGNED-32BIT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("UNSIGNED-64BIT"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("UNSPECIFIC"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("UP"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("UPCASE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("USE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("VARIABLE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("VERBOSE"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("VERSION"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("WILD"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("WILD-INFERIORS"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("WRITER"
    (:symbol
        :package "KEYWORD"
	:import-from nil
	)
    )

("%INDIRECTION"
    (:symbol
        :package "TRUN"
	:import-from nil
	:exists-at-runtime nil
	)
    (:function
        :state-changing nil
	:nonconsing t
	:operator timpl::cindirection
        :lambda-list (object)
	:foreign-protocol :operator
	:foreign-arguments (((:pointer :int) nil))
	:foreign-return-type :int
	)
    )
)

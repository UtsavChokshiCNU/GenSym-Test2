;;; -*- Mode: Lisp; Package: HOST; Syntax: Common-Lisp -*-
;;;
;;; rpacks.lisp -- set up packages which are used by the translator runtime
;;;
;;; author :  Sandra Loosemore
;;; date   :  05 Oct 1990
;;;
;;; Copyright (c) 1990, Chestnut Software Inc.
;;;

(in-package "HOST")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/rpacks.lisp,v $"
 "$Revision: 1.17 $"
 "$Date: 2009/08/10 00:00:00 $")

;;;
;;; Setup of the built-in packages that exist at runtime follows a
;;; four-step procedure:
;;; (1) Create all the packages.
;;; (2) Install the symbols in the packages by reading the database.
;;; (3) Save information necessary to create all the packages during
;;;     initialization of the RTL.
;;; (4) Save information necessary to install all the symbols during
;;;     initialization of the RTL.
;;;
;;; This file contains steps (1) and (2).  Steps (3) and (4) happen
;;; when initenv.lisp is loaded.
;;; 
;;; Steps (1) and (2) are separate for bootstrapping reasons:  the code
;;; to do steps (3) and (4) can't be loaded before the packages are set
;;; up in the host Lisp environment.
;;;
;;; Step (1) is separate from step (2) (and step (3) from (4)) to allow
;;; the use of the database mechanism to specify what symbols go where.
;;;
;;; 

(eval-when (compile load eval)

(defvar *translator-packages* nil)

(defun notice-translator-package (p)
  (unless (packagep p) (setq p (find-package p)))
  (pushnew p *translator-packages*))

(dolist (p '(("TCL" ("TRANSLATOR-COMMON-LISP"))
	     ("TX" ("TRANSLATOR-EXTENSIONS"))
	     ("TRUN" ("TRANSLATOR-RUNTIME"))
	     ("TCLOS" ("TRANSLATOR-CLOS"))
	     ("TCLOSX" ("TRANSLATOR-CLOS-EXTENSIONS"))
	     ("TCLOS-RUN" ("TRANSLATOR-CLOS-RUNTIME"))
	     ("TCL-USER" () "TCL")))
  (let ((name (car p))
	(nicknames (cadr p))
	(use (caddr p)))
    (unless (find-package name)
      (make-package name :nicknames nicknames
		    :use #-SBCL use #+SBCL (and use (list use))))
    (notice-translator-package name)))
)

;;; The TCL package exports all the symbols that are defined in ANSI
;;;     Common Lisp as being in the COMMON-LISP package.

(eval-when (compile load eval)

(dolist (name '("COMPILER-MACRO-FUNCTION" "CONSTANTP" "GET-SETF-EXPANSION"
		"MACRO-FUNCTION" "MACROEXPAND" "MACROEXPAND-1" "PROCLAIM"
		"SUBTYPEP" "TYPEP"
		"UPGRADED-ARRAY-ELEMENT-TYPE" "UPGRADED-COMPLEX-PART-TYPE"))
  (export (intern name "TCL") "TCL"))

(dolist (name '("CLASS-NAME" "ENSURE-GENERIC-FUNCTION" "FIND-CLASS"
		"FUNCTION-KEYWORDS" "METHOD-QUALIFIERS"))
  (export (intern name "TCLOS") "TCLOS"))

#+translator-supports-clos
(dolist (name '("DOCUMENTATION"))
  (export (intern name "TCLOS") "TCLOS"))

(defmacro import-and-export (symbols &optional (package '*package*))
  `(eval-when (compile load eval)
     (import ,symbols ,package)
     (export ,symbols ,package)))

)

(import-and-export
  '(&allow-other-keys &aux &body &environment &key &optional &rest &whole * **
    *** *break-on-signals* *compile-file-pathname* *compile-file-truename*
    *compile-print* *compile-verbose* *debug-io* *debugger-hook*
    *default-pathname-defaults* *error-output* *features* *gensym-counter*
    *load-pathname* *load-print* *load-truename* *load-verbose*
    *macroexpand-hook* *modules* *package* *print-array* *print-base*
    *print-case* *print-circle* *print-escape* *print-gensym* *print-length*
    *print-level* *print-lines* *print-miser-width* *print-pprint-dispatch*
    *print-pretty* *print-radix* *print-readably* *print-right-margin*
    *query-io* *random-state* *read-base* *read-default-float-format*
    *read-eval* *read-suppress* *readtable* *standard-input* *standard-output*
    *terminal-io* *trace-output* + ++ +++ - / // /// /= 1+ 1- < <= = > >= abort
    abs acons acos acosh add-method adjoin adjust-array adjustable-array-p
    allocate-instance alpha-char-p alphanumericp and append apply apropos
    apropos-list aref arithmetic-error arithmetic-error-operands
    arithmetic-error-operation array array-dimension array-dimension-limit
    array-dimensions array-displacement array-element-type
    array-has-fill-pointer-p array-in-bounds-p array-rank array-rank-limit
    array-row-major-index array-total-size array-total-size-limit arrayp ash
    asin asinh assert assoc assoc-if assoc-if-not atan atanh atom base-char
    base-string bignum bit bit-and bit-andc1 bit-andc2 bit-eqv bit-ior bit-nand
    bit-nor bit-not bit-orc1 bit-orc2 bit-vector bit-vector-p bit-xor block
    boole boole-1 boole-2 boole-and boole-andc1 boole-andc2 boole-c1 boole-c2
    boole-clr boole-eqv boole-ior boole-nand boole-nor boole-orc1 boole-orc2
    boole-set boole-xor both-case-p boundp break broadcast-stream
    broadcast-stream-streams built-in-class butlast byte byte-position
    byte-size caaaar caaadr caaar caadar caaddr caadr caar cadaar cadadr cadar
    caddar cadddr caddr cadr call-arguments-limit call-method call-next-method
    car case catch ccase cdaaar cdaadr cdaar cdadar cdaddr cdadr cdar cddaar
    cddadr cddar cdddar cddddr cdddr cddr cdr ceiling cell-error
    cell-error-name cerror change-class char char-code char-code-limit
    char-downcase char-equal char-greaterp char-int char-lessp char-name
    char-not-equal char-not-greaterp char-not-lessp char-upcase char/= char<
    char<= char= char> char>= character characterp check-type cis class
    tclos:class-name class-of clear-input clear-output close clrhash code-char
    coerce compilation-speed compile compile-file compile-file-pathname
    compiled-function compiled-function-p compiler-macro
    tcl:compiler-macro-function complement complex complexp
    compute-applicable-methods compute-restarts concatenate concatenated-stream
    concatenated-stream-streams cond condition conjugate cons consp constantly
    tcl:constantp continue control-error copy-alist copy-list
    copy-pprint-dispatch copy-readtable copy-seq copy-structure copy-symbol
    copy-tree cos cosh count count-if count-if-not ctypecase debug decf declaim
    declaration declare decode-float decode-universal-time defclass defconstant
    defgeneric define-compiler-macro define-condition define-method-combination
    define-modify-macro define-setf-expander defmacro defmethod defpackage
    defparameter defsetf defstruct deftype defun defvar delete
    delete-duplicates delete-file delete-if delete-if-not delete-package
    denominator deposit-field describe describe-object destructuring-bind
    digit-char digit-char-p directory directory-namestring disassemble
    division-by-zero do do* do-all-symbols do-external-symbols do-symbols
    #-translator-supports-clos documentation
    #+translator-supports-clos tclos:documentation
    dolist dotimes double-float double-float-epsilon
    double-float-negative-epsilon dpb dribble dynamic-extent ecase echo-stream
    echo-stream-input-stream echo-stream-output-stream ed eighth elt
    encode-universal-time end-of-file endp enough-namestring
    tclos:ensure-generic-function eq eql equal equalp error etypecase eval
    eval-when evenp every exp export expt extended-char fboundp fceiling
    fdefinition ffloor fifth file-author file-error file-error-pathname
    file-length file-namestring file-position file-stream file-string-length
    file-write-date fill fill-pointer find find-all-symbols tclos:find-class
    find-if find-if-not find-method find-package find-restart find-symbol
    finish-output first fixnum flet float float-digits float-precision
    float-radix float-sign floating-point-inexact
    floating-point-invalid-operation floating-point-overflow
    floating-point-underflow floatp floor fmakunbound force-output format
    formatter fourth fresh-line fround ftruncate ftype funcall function
    tclos:function-keywords function-lambda-expression functionp gcd
    generic-function gensym gentemp get get-decoded-time
    get-dispatch-macro-character get-internal-real-time get-internal-run-time
    get-macro-character get-output-stream-string get-properties
    tcl:get-setf-expansion get-universal-time getf gethash go graphic-char-p
    handler-bind handler-case hash-table hash-table-count hash-table-p
    hash-table-rehash-size hash-table-rehash-threshold hash-table-size
    hash-table-test host-namestring identity if ignorable ignore ignore-errors
    imagpart import in-package incf initialize-instance inline input-stream-p
    inspect integer integer-decode-float integer-length integerp
    interactive-stream-p intern internal-time-units-per-second intersection
    invalid-method-error invoke-debugger invoke-restart
    invoke-restart-interactively isqrt keyword keywordp labels lambda
    lambda-list-keywords lambda-parameters-limit last lcm ldb ldb-test ldiff
    least-negative-double-float least-negative-long-float
    least-negative-normalized-double-float least-negative-normalized-long-float
    least-negative-normalized-short-float
    least-negative-normalized-single-float least-negative-short-float
    least-negative-single-float least-positive-double-float
    least-positive-long-float least-positive-normalized-double-float
    least-positive-normalized-long-float least-positive-normalized-short-float
    least-positive-normalized-single-float least-positive-short-float
    least-positive-single-float length let let* lisp-implementation-type
    lisp-implementation-version list list* list-all-packages list-length listen
    listp load load-logical-pathname-translations load-time-value locally log
    logand logandc1 logandc2 logbitp logcount logeqv logical-pathname
    logical-pathname-translations logior lognand lognor lognot logorc1 logorc2
    logtest logxor long-float long-float-epsilon long-float-negative-epsilon
    long-site-name loop loop-finish lower-case-p machine-instance machine-type
    machine-version tcl:macro-function tcl:macroexpand tcl:macroexpand-1
    macrolet make-array make-broadcast-stream make-concatenated-stream
    make-condition make-dispatch-macro-character make-echo-stream
    make-hash-table make-instance make-instances-obsolete make-list
    make-load-form make-load-form-saving-slots make-method make-package
    make-pathname make-random-state make-sequence make-string
    make-string-input-stream make-string-output-stream make-symbol
    make-synonym-stream make-two-way-stream makunbound map map-into mapc mapcan
    mapcar mapcon maphash mapl maplist mask-field max member member-if
    member-if-not merge merge-pathnames method method-combination
    method-combination-error tclos:method-qualifiers min minusp mismatch mod
    most-negative-double-float most-negative-fixnum most-negative-long-float
    most-negative-short-float most-negative-single-float
    most-positive-double-float most-positive-fixnum most-positive-long-float
    most-positive-short-float most-positive-single-float muffle-warning
    multiple-value-bind multiple-value-call multiple-value-list
    multiple-value-prog1 multiple-value-setq multiple-values-limit name-char
    namestring nbutlast nconc next-method-p nil nintersection ninth
    no-applicable-method no-next-method not notany notevery notinline nreconc
    nreverse nset-difference nset-exclusive-or nstring-capitalize
    nstring-downcase nstring-upcase nsublis nsubst nsubst-if nsubst-if-not
    nsubstitute nsubstitute-if nsubstitute-if-not nth nth-value nthcdr null
    number numberp numerator nunion oddp open open-stream-p optimize or
    otherwise output-stream-p package package-error package-error-package
    package-name package-nicknames package-shadowing-symbols package-use-list
    package-used-by-list packagep pairlis parse-error parse-integer
    parse-namestring pathname pathname-device pathname-directory pathname-host
    pathname-match-p pathname-name pathname-type pathname-version pathnamep
    peek-char phase pi plusp pop position position-if position-if-not pprint
    pprint-dispatch pprint-exit-if-list-exhausted pprint-fill pprint-indent
    pprint-linear pprint-logical-block pprint-newline pprint-pop pprint-tab
    pprint-tabular prin1 prin1-to-string princ princ-to-string print
    print-not-readable print-not-readable-object print-object
    print-unreadable-object probe-file tcl:proclaim prog prog* prog1 prog2
    progn program-error progv provide psetf psetq push pushnew quote random
    random-state random-state-p rassoc rassoc-if rassoc-if-not ratio rational
    rationalize rationalp read read-byte read-char read-char-no-hang
    read-delimited-list read-from-string read-line read-preserving-whitespace
    reader-error readtable readtable-case readtablep real realp realpart reduce
    reinitialize-instance rem remf remhash remove remove-duplicates remove-if
    remove-if-not remove-method remprop rename-file rename-package replace
    require rest restart restart-bind restart-case restart-name return
    return-from revappend reverse room rotatef round row-major-aref rplaca
    rplacd safety satisfies sbit scale-float schar search second sequence
    serious-condition set set-difference set-dispatch-macro-character
    set-exclusive-or set-macro-character set-pprint-dispatch
    set-syntax-from-char setf setq seventh shadow shadowing-import
    shared-initialize shiftf short-float short-float-epsilon
    short-float-negative-epsilon short-site-name signal signed-byte signum
    simple-array simple-base-string simple-bit-vector simple-bit-vector-p
    simple-condition simple-condition-format-arguments
    simple-condition-format-control simple-error simple-string simple-string-p
    simple-type-error simple-vector simple-vector-p simple-warning sin
    single-float single-float-epsilon single-float-negative-epsilon sinh sixth
    sleep slot-boundp slot-exists-p slot-makunbound slot-missing slot-unbound
    slot-value software-type software-version some sort space special
    special-operator-p speed sqrt stable-sort standard standard-char
    standard-char-p standard-class standard-generic-function standard-method
    standard-object step storage-condition store-value stream
    stream-element-type stream-error stream-error-stream stream-external-format
    streamp string string-capitalize string-downcase string-equal
    string-greaterp string-left-trim string-lessp string-not-equal
    string-not-greaterp string-not-lessp string-right-trim string-stream
    string-trim string-upcase string/= string< string<= string= string>
    string>= stringp structure structure-class structure-object style-warning
    sublis subseq subsetp subst subst-if subst-if-not substitute substitute-if
    substitute-if-not tcl:subtypep svref sxhash symbol symbol-function
    symbol-macrolet symbol-name symbol-package symbol-plist symbol-value
    symbolp synonym-stream synonym-stream-symbol t tagbody tailp tan tanh tenth
    terpri the third throw time trace translate-logical-pathname
    translate-pathname tree-equal truename truncate two-way-stream
    two-way-stream-input-stream two-way-stream-output-stream type type-error
    type-error-datum type-error-expected-type type-of typecase tcl:typep
    unbound-slot unbound-slot-instance unbound-variable undefined-function
    unexport unintern union unless unread-char unsigned-byte untrace
    unuse-package unwind-protect update-instance-for-different-class
    update-instance-for-redefined-class tcl:upgraded-array-element-type
    tcl:upgraded-complex-part-type upper-case-p use-package use-value
    user-homedir-pathname values values-list variable vector vector-pop
    vector-push vector-push-extend vectorp warn warning when wild-pathname-p
    with-accessors with-compilation-unit with-condition-restarts
    with-hash-table-iterator with-input-from-string with-open-file
    with-open-stream with-output-to-string with-package-iterator
    with-simple-restart with-slots with-standard-io-syntax write write-byte
    write-char write-line write-string write-to-string y-or-n-p yes-or-no-p
    zerop)
  "TCL")


;;; The TX package exports symbols which we document and support as 
;;;     extensions to the language.
(eval-when (compile load eval)

#+(and lcl4.0 (not translating))
(import-and-export (intern "LIST-ERROR" "SYSTEM") "TX")
)

(dolist (name '("ALLOCATE-MEMORY-TO-TARGET" "AREA-MEMORY-LIMIT"
		"AREA-MEMORY-USED" "AREA-TARGET-SIZE" "AUGMENT-ENVIRONMENT"
		"C-LINES" "CLOSED-VARIABLE" "CONSTANT-VALUE" "CPP-CONDITIONAL"
		"DECLARATION-INFORMATION" "ENCLOSE" "EVAL-RUN"
		"FOREIGN-CALL" "FUNCTION-INFORMATION" "FUNCTION-OBJECT" "GET-SETF-METHOD"
		"GET-SETF-METHOD-MULTIPLE-VALUE" "INCLUDE-AT-RUNTIME"
		"LOAD-RUN" "NON-STATE-CHANGING" "NON-STATE-USING"
		"NONCONSING" "NONRELOCATING"
		"OMIT-AT-RUNTIME" "PARSE-DECLARATIONS" "PARSE-MACRO"
		"SET-DECLARATION-INFORMATION" "TOPLEVEL-C-LINES"
		"TOTAL-MEMORY-USED" "TYPE-FROM-ELEMENT-TYPE"
		"UNREAD-VARIABLE" "UNWRITTEN-VARIABLE"
		"READ-ONCE-VARIABLE"
		"VARIABLE-INFORMATION"
		"WITH-DYNAMIC-ALLOCATION"
		"WITH-LOCAL-ALLOCATION" "WITH-LOCAL-AREA"
		"PRINTF"
		"%FOREIGN-POINTER-ADDRESS" "%SET-FOREIGN-POINTER-ADDRESS"
		"SET-FOREIGN-POINTER-ADDRESS" "SET-FOREIGN-POINTER-TYPE"
		"%SET-FOREIGN-POINTER-TYPE"
		"SET-FOREIGN-STRING-VALUE" "SET-FOREIGN-VALUE"
		"%FOREIGN-POINTER-P" "%FOREIGN-POINTER-TYPE"
		"%FOREIGN-TYPE" "%FOREIGN-TYPE-P" "PRIMITIVE-FOREIGN-TYPE-P"
		"ARRAY-FOREIGN-TYPE-P" "STRUCTURE-FOREIGN-TYPE-P"
		"POINTER-FOREIGN-TYPE-P"
		"MAKE-STRUCT-FOREIGN-TYPE" "DEFINE-FOREIGN-SYNONYM-TYPE"
		"PRIMITIVE-FOREIGN-TYPE" "ARRAY-FOREIGN-TYPE"
		"STRUCTURE-FOREIGN-TYPE" "POINTER-FOREIGN-TYPE"
		"VARIADIC-FOREIGN-CALL" "FOREIGN-FUNCTION"
		"BINDING-ENVIRONMENT" "FUNCTION-NEEDS-OBJECT"
		"CLOSED-FUNCTION" "FUNCTION-NEEDS-ENVIRONMENT"
		"BIGNUM-LENGTH" "STORE-BIGNUM" "COPY-OF-BIGNUM"
		"RETURNS-ONE-VALUE" "PROCLAIM-SPECIAL"
		"DLLEXPORT-FUNCTION" "DLLIMPORT-FUNCTION"
		"AREA-MEMORY-LIMIT-AS-FLOAT" "AREA-MEMORY-USED-AS-FLOAT"
		"AREA-TARGET-SIZE-AS-FLOAT"))
  (export (intern name "TX") "TX"))

;; Rest symbols are defined by portable-threads and then imported in symbols.lisp
#+translator-supports-thread
(dolist (name '("GLOBAL-VARIABLE"
		"ATOMIC-EXCHANGE"
		"ATOMIC-EXCHANGE-SYMBOL-VALUE"
		"ATOMIC-INCFF-CAR"
		"ATOMIC-INCFF-CDR"
		"ATOMIC-INCFF-SYMBOL-VALUE"
		"ATOMIC-INCFF-SIMPLE-VECTOR-SLOT"))
  (export (intern name "TX") "TX"))

(dolist (name '("ASSQ" "DEFINE-DECLARATION" "DEFINE-SETF-METHOD" "DELQ"
		"FLATSIZE" "IFN"  "LIST-NREVERSE" "LIST-REVERSE" "MEMQ" "NCONS"
		"SPECIAL-FORM-P" "STRING-APPEND" "STRING-CHAR"
		"WITH-DYNAMIC-AREA" "WITH-STATIC-AREA" "XOR"))
  (import-and-export (intern name "HOSTX") "TX"))

;; not sure where these should go; they're from patch 2 -alatto, 3/1/06
(eval-when (compile load eval)
(let ((sym (intern "UNDEFINE-FOREIGN-TYPE"
		   #+lucid "LCL" #-lucid "HOSTX")))
  #+lucid (import sym "HOSTX")
  (export sym "HOSTX"))


(dolist (name '("COPY-FOREIGN-POINTER" "DEF-FOREIGN-CALLABLE"
		"DEF-FOREIGN-FUNCTION" "DEF-FOREIGN-STRUCT"
		"DEF-FOREIGN-SYNONYM-TYPE" "DEFINED-FOREIGN-TYPE-P"
		"FOREIGN-AREF" "FOREIGN-POINTER" "FOREIGN-POINTER-ADDRESS"
		"FOREIGN-POINTER-P" "FOREIGN-POINTER-TYPE"
		"FOREIGN-POINTER-TYPE-P" "FOREIGN-TYPE-P"
		"FOREIGN-STRING-VALUE" "FOREIGN-SIZE-OF"
		"FOREIGN-TYPE" "FOREIGN-TYPE-NAME"
		"FOREIGN-TYPE-SIZE" "FOREIGN-TYPE-MODULUS"
		"FOREIGN-TYPE-REMAINDER" "FOREIGN-TYPEP" "FOREIGN-VALUE"
 		"FOREIGN-VARIABLE-ADDRESS" "FOREIGN-VARIABLE-POINTER" 
 		"FREE-FOREIGN-POINTER"
		"MAKE-FOREIGN-POINTER-INTERNAL" "SET-TYPED-FOREIGN-AREF"
 		"MAKE-FOREIGN-POINTER" "MALLOC-FOREIGN-POINTER"
 		"STATIONARY-OBJECT-P" "TYPED-FOREIGN-AREF"
		;; Unsupported stuff
		#||
		"FOREIGN-VARIABLE-P" "FOREIGN-UNDEFINED-SYMBOL-NAMES" 
		 "*LISP-SYMBOL-TO-FOREIGN-STRING-METHOD*"
		"LOAD-FOREIGN-FILES" "LOAD-FOREIGN-LIBRARIES"
		"UNINTERN-FOREIGN-SYMBOL"
		"WRITABLE-OBJECT-P"
		||#))
  (import-and-export (intern name "HOSTX") "TX"))

#+translator-supports-clos
(dolist (name '("CALL-COMBINED-METHOD" "COMBINE-METHODS"
		"DEFINE-METHOD-COMBINATION-FUNCTION" "LOCAL-METHOD"))
  (import-and-export (intern name "TCLOSX") "TX"))
)

;;; The TRUN package exports other symbols needed for runtime that show
;;;     up in translated code, but that we do not necessarily document
;;;     or support.  User code should never reference these directly.

(in-package :trun)

(host::import-and-export
  '(%%pointer %%sysint %add-2 %add-import %add-package-nickname
    %add-package-use %add-shadow %adjustable-array-p %alpha-char-p
    %alphanumericp %append-2 %apply-1 %apply-2 %apply-3 %apply-4 %apply-5
    %aref-0 %aref-1 %aref-2 %aref-3 %aref-4 %aref-5 %aref-6 %aref-7
    %array-has-fill-pointer-p %array-rank %array-total-size %arrayp %assoc-eq
    %assoc-eql %assoc-equal %atom %bignump %bit-0 %bit-1 %bit-2 %bit-3 %bit-4
    %bit-5 %bit-6 %bit-7 %bit-vector-p %bitp %boundp %break %broadcast-stream-p
    %byte %byte-16-sarray-to-short-pointer %byte-8-sarray-to-char-pointer
    %byte-32-sarray-to-int-pointer %byte-64-sarray-to-int64-pointer
    %byte-position %byte-size %caaaar %caaadr %caaar %caadar %caaddr %caadr
    %caar %cadaar %cadadr %cadar %caddar %cadddr %caddr %cadr %car
    %catch-values %cdaaar %cdaadr %cdaar %cdadar %cdaddr %cdadr %cdar %cddaar
    %cddadr %cddar %cdddar %cddddr %cdddr %cddr %cdr %cerror %char
    %char*-to-string %char-code %char-downcase %char-eq-2 %char-equal-2
    %char-ge-2 %char-greaterp-2 %char-gt-2 %char-int %char-le-2 %char-lessp-2
    %char-lt-2 %char-ne-2 %char-not-equal-2 %char-not-greaterp-2
    %char-not-lessp-2 %char-to-character %char-to-fixnum %char-to-integer
    %char-upcase %character-to-char %characterp %chr %cobjectp %code-char
    %compiled-function-p %complexp %concatenated-stream-p %cons %consp
    %delete-eq %delete-eql %delete-equal %denominator %dfloat-saref-0
    %dfloat-saref-1 %dfloat-saref-2 %dfloat-saref-3 %dfloat-saref-4
    %dfloat-saref-5 %dfloat-saref-6 %dfloat-saref-7
    %dfloat-sarray-to-double-pointer %dfloat-saset-0 %dfloat-saset-1
    %dfloat-saset-2 %dfloat-saset-3 %dfloat-saset-4 %dfloat-saset-5
    %dfloat-saset-6 %dfloat-saset-7 %divide-2 %do-test %echo-stream-p %eighth
    %endp %eq %eql %equal %equalp %error %fifth %file-stream-p %fill-pointer
    %first %fix %fixnum-to-char %fixnum-to-int %fixnum-to-long %fixnum-to-short
    %fixnump %float-to-short-float %float-to-single-float %floatp %format
    %fourth %funcall-0 %funcall-1 %funcall-2 %funcall-3 %funcall-4 %funcall-5
    %funcall-symbol-0 %funcall-symbol-1 %funcall-symbol-2 %funcall-symbol-3
    %funcall-symbol-4 %funcall-symbol-5 %functionp %gcd-2 %graphic-char-p
    %hash-table-p %identity %ifix %input-stream-p %int-to-fixnum
    %integer-to-char %integer-to-long %integer-to-int %integer-to-int64
    %integer-to-short %integer-to-unsigned-int
    %integer-to-unsigned-char %integer-to-unsigned-long %integer-to-unsigned-int64
    %integer-to-unsigned-short %integerp %interaction-stream-p
    %internal-marker-p %istring %keyword-arg %keyword-arg-p %keywordp %lcm-2
    %list-1 %list-2 %list-3 %list-4 %list-5 %list-star-2 %list-star-3 %listp
    %local-temp-declaration %logand-2 %logeqv-2 %logical-pathname-p %logior-2
    %logxor-2 %lower-case-p 
    %long-to-fixnum %long-to-integer %int-to-integer %int64-to-integer
    %m-caaaar
    %m-caaadr %m-caaar %m-caadar %m-caaddr %m-caadr %m-caar %m-cadaar %m-cadadr
    %m-cadar %m-caddar %m-cadddr %m-caddr %m-cadr %m-car %m-cdaaar %m-cdaadr
    %m-cdaar %m-cdadar %m-cdaddr %m-cdadr %m-cdar %m-cddaar %m-cddadr %m-cddar
    %m-cdddar %m-cddddr %m-cdddr %m-cddr %m-cdr %m-eighth %m-fifth %m-first
    %m-fourth %m-ninth %m-nth %m-rest %m-second %m-seventh %m-sixth %m-tenth
    %m-third %make-structure %max-2 %member-eq %member-eql %member-equal %min-2
    %minus-2 %mv-funcall %mv-list %mv-setq-remaining %nconc-2 %negate %neq
    %neql %new-package %new-symbol %ninth %not %num-eq-2 %num-ge-2 %num-gt-2
    %num-le-2 %num-lt-2 %num-ne-2 %numberp %numerator %optional-arg
    %optional-arg-p %output-stream-p %packagep %pathname-host %pathnamep
    %random-state-p %rationalp %ratiop %readtablep %realp %reciprocal %rest
    %rest-arg %row-major-aref %rplaca %rplacb %rplacd %sbit-0 %sbit-1 %sbit-2
    %sbit-3 %sbit-4 %sbit-5 %sbit-6 %sbit-7 %sbitp-1 %schar %second %sequencep
    %set-aref-0 %set-aref-1 %set-aref-2 %set-aref-3 %set-aref-4 %set-aref-5
    %set-aref-6 %set-aref-7 %set-bignum-digit %set-bit-0 %set-bit-1 %set-bit-2
    %set-bit-3 %set-bit-4 %set-bit-5 %set-bit-6 %set-bit-7 %set-caaaar
    %set-caaadr %set-caaar %set-caadar %set-caaddr %set-caadr %set-caar
    %set-cadaar %set-cadadr %set-cadar %set-caddar %set-cadddr %set-caddr
    %set-cadr %set-car %set-cdaaar %set-cdaadr %set-cdaar %set-cdadar
    %set-cdaddr %set-cdadr %set-cdar %set-cddaar %set-cddadr %set-cddar
    %set-cdddar %set-cddddr %set-cdddr %set-cddr %set-cdr %set-char %set-eighth
    %set-fifth %set-fill-pointer %set-first %set-fourth %set-isvref %set-ninth
    %set-nth %set-package %set-rest %set-row-major-aref %set-sbit-0 %set-sbit-1
    %set-sbit-2 %set-sbit-3 %set-sbit-4 %set-sbit-5 %set-sbit-6 %set-sbit-7
    %set-schar %set-second %set-setf-function %set-seventh %set-sixth
    %set-subseq-1 %set-subseq-2 %set-svref %set-symbol-function
    %set-symbol-plist %set-symbol-value %set-tenth %set-third %setf-function
    %seventh %sfloat-sarray-to-float-pointer %short-float-to-float
    %short-to-fixnum %short-to-integer %simple-array-p %simple-bit-vector-p
    %simple-string-p %simple-string-to-char-pointer %simple-vector-p
    %single-float-to-float %sixth %standard-char-p %standard-object-p
    %static-bit-array %static-char-array %static-array %static-cons %static-float
    %static-general-array %static-list %static-negative-bignum %static-package
    %static-positive-bignum %static-ratio %static-string %static-symbol
    %store-value-temp-declaration %streamp %string-append-2
    %string-input-stream-p %string-output-stream-p %string-stream-p
    %string-to-char* %stringp %structure-object-p %svref %symbol-function
    %symbol-name %symbol-package %symbol-plist %symbol-value %symbolp
    %synonym-stream-p %tag-array %tag-bignum %tag-compiled-function %tag-cons
    %tag-double-float %tag-ratio %tag-string %tag-uninterned-symbol %tag-vector
    %tenth %third %throw %times-2 %truep %two-way-stream-p %typep
    %ubyte-8-sarray-to-uchar-ptr %ubyte-16-sarray-to-ushort-ptr
    %ubyte-32-sarray-to-uint-ptr %ubyte-64-sarray-to-uint64-ptr
    %ubyte-8-saref-0 %ubyte-8-saref-1 %ubyte-8-saref-2 %ubyte-8-saref-3
    %ubyte-8-saref-4 %ubyte-8-saref-5 %ubyte-8-saref-6 %ubyte-8-saref-7 
    %ubyte-8-saset-0 %ubyte-8-saset-1 %ubyte-8-saset-2 %ubyte-8-saset-3
    %ubyte-8-saset-4 %ubyte-8-saset-5 %ubyte-8-saset-6 %ubyte-8-saset-7
    %ubyte-16-saref-0 %ubyte-16-saref-1 %ubyte-16-saref-2 %ubyte-16-saref-3
    %ubyte-16-saref-4 %ubyte-16-saref-5 %ubyte-16-saref-6 %ubyte-16-saref-7
    %ubyte-16-saset-0 %ubyte-16-saset-1 %ubyte-16-saset-2 %ubyte-16-saset-3
    %ubyte-16-saset-4 %ubyte-16-saset-5 %ubyte-16-saset-6 %ubyte-16-saset-7
    %ubyte-32-saref-0 %ubyte-32-saref-1 %ubyte-32-saref-2 %ubyte-32-saref-3
    %ubyte-32-saref-4 %ubyte-32-saref-5 %ubyte-32-saref-6 %ubyte-32-saref-7
    %ubyte-32-saset-0 %ubyte-32-saset-1 %ubyte-32-saset-2 %ubyte-32-saset-3
    %ubyte-32-saset-4 %ubyte-32-saset-5 %ubyte-32-saset-6 %ubyte-32-saset-7
    %ubyte-64-saref-0 %ubyte-64-saref-1 %ubyte-64-saref-2 %ubyte-64-saref-3
    %ubyte-64-saref-4 %ubyte-64-saref-5 %ubyte-64-saref-6 %ubyte-64-saref-7
    %ubyte-64-saset-0 %ubyte-64-saset-1 %ubyte-64-saset-2 %ubyte-64-saset-3
    %ubyte-64-saset-4 %ubyte-64-saset-5 %ubyte-64-saset-6 %ubyte-64-saset-7
    %unbox-char %unbox-float %unique-tag %unsigned-char-to-integer
    %unsigned-int-to-integer %unsigned-long-to-integer %unsigned-int64-to-integer
    %unsigned-short-to-integer %unsupplied-marker
    %upper-case-p %vectorp %void-to-null %warn %y-or-n-p %yes-or-no-p *% *%d
    *%long *%rd *break-function* *gc-inhibit* *gc-silence*
    +% +%d +%long +%int64 +%uint64 +%rd -% -%d -%long -%int64 -%uint64
    -%rd /% /%d /%rd /=% /=%d /=%long /=%rd 1+% 1+%d 1+%rd 1-% 1-%d 1-%rd <%
    <%d <%long <%rd <=% <=%d <=%long <=%rd =% =%d =%long =%rd >% >%d >%long
    >%rd >=% >=%d >=%long >=%rd abs% abs%d abs%rd advance-do-symbols-iterator
    advance-with-package-iterator allow-gc ash% atan%d atan%rd atan1%d atan1%rd
    backquote begin-hash-table-iterator begin-print-unreadable-object
    begin-time bignump bitp box%d broadcast-stream-p ceiling% ceiling%d
    ceiling%rd ceiling1% ceiling1%d ceiling1%rd cleanup-hash-table-iterator
    cobject cobjectp comma comma-atsign comma-dot concatenated-stream-p
    constant-initfunction constantly-false constantly-nil-initfunction
    constantly-t-initfunction constantly-true cos%d cos%rd decf%
    defpackage-export defpackage-import-from defpackage-intern
    defpackage-shadow defpackage-shadowing-import-from defpackage-use-package
    do-remf do-side-effects-test do-test dpb% echo-stream-p
    end-hash-table-iterator establish-special-variable evenp% exp%d exp%rd
    expt%d expt%rd extend-string-output-stream file-stream-p
    finish-print-unreadable-object finish-time fixnump floor% floor%d floor%rd
    floor1% floor1%d floor1%rd force-gc fround%d fround%rd fround1%d fround1%rd
    hash-table-iterator incf% initialize-do-all-symbols-iterator
    initialize-do-external-symbols-iterator initialize-do-symbols-iterator
    initialize-with-package-iterator interaction-stream interaction-stream-p
    internal-marker internal-marker-p isqrt% keyword-package ldb% link-function
    link-setf-function link-variable log%d log%rd log1%d log1%rd logand%
    logandc2% logbitp% logcount% logeqv% logical-pathname-p logior% lognot%
    logtest% logxor% lsh% make-structure-class max% max%d max%rd min% min%d
    min%rd minusp% minusp%d minusp%rd mod% negate% negate%d negate%rd oddp%
    plusp% plusp%d plusp%rd prompt-for-value ratiop rem% round%d round%rd
    round1%d round1%rd rsh% sequencep set-caaaar set-caaadr set-caaar
    set-caadar set-caaddr set-caadr set-caar set-cadaar set-cadadr set-cadar
    set-caddar set-cadddr set-caddr set-cadr set-car set-cdaaar set-cdaadr
    set-cdaar set-cdadar set-cdaddr set-cdadr set-cdar set-cddaar set-cddadr
    set-cddar set-cdddar set-cddddr set-cdddr set-cddr set-cdr set-char
    set-compiler-macro-function set-eighth set-elt set-fdefinition set-fifth
    set-fill-pointer set-first set-fourth set-get set-getf set-gethash
    set-logical-pathname-translations set-macro-function set-ninth set-nth
    set-package set-readtable-case set-rest set-row-major-aref set-schar
    set-second set-setf-function set-seventh set-sixth set-slot-value
    set-subseq set-svref set-symbol-function set-symbol-plist set-tenth
    set-third setf-function shared-structure-p simple-array-p sin%d sin%rd
    sqrt%d sqrt%rd standard-object-p string-input-stream string-input-stream-p
    string-output-stream string-output-stream-p string-stream-index
    string-stream-p host:structure-object structure-object-p
    synonym-stream-p tan%d tan%rd tcl-package tcl-user-package tclos-package
    tclos-run-package tclosx-package trun-package truncate% truncate%d
    truncate%rd truncate1%d truncate1%rd two-way-stream-p tx-package
    unbound-special-p unbox%d userfuns userinit usersyms with-area zerop%
    zerop%d zerop%rd %primitive-vector-p %primitive-vector-length
    %istring-to-simple-string %static-list-star %unbound-marker
    %eql-fast-1 %eql-fast-2 isymbol-name strcpy strlen)
    "TRUN")

#+translator-supports-thread
(host::import-and-export
  '(%symbol-value-in-thread %set-symbol-value-in-thread
    %lock %unlock)
    "TRUN")

(host::import-and-export
  '(%cdouble-to-double %istring-to-string
    +%double -%double *%double
    1+%long 1+%int64 1+%uint64 1-%long 1-%int64 1-%uint64
    1+%double 1-%double
    
    ash-right%long ash-left%long shift-left%long shift-right%long
    zerop%long plusp%long minusp%long evenp%long oddp%long
    zerop%double plusp%double minusp%double
    logand%long logior%long logxor%long logeqv%long lognot%long
    logtest%long logbitp%long
    negate%long negate%double
    =%double /=%double <%double <=%double >%double >=%double

    logandc1%long logandc2%long lognand%long
    lognor%long logorc1%long logorc2%long

    abs%long max%long min%long

    %double-to-float %float-to-double %isvref %set-isvref
    %ichar %ischar %set-ichar %set-ischar

    %printf

    1+%single +%single 1-%single -%single zerop%single
    =%single plusp%single <%single minusp%single >%single
    expt2 %long-to-float2 %long-to-float %long-to-double2 %long-to-double
    expt%long floor-positive%long logcount%long mod-positive%long
    %not%boolean mod-positive%long floor-positive%long /%single
    /%double negate%single /=%single <=%single >=%single *%single
    %typed-foreign-aref %indirection
    %nr-optional-arg %nr-optional-arg-p %nr-end-args)
  "TRUN")

#+translator-supports-clos
(host::import-and-export
 '(%class-wrapper-p %effective-method-p %method-combination-p class-wrapper
   class-wrapper-p effective-method effective-method-p method-combination-p)
 "TRUN")

#+translator-supports-thread
(host::import-and-export
 '(%lock %trylock %unlock)
 "TRUN")

(host:in-package :host)


;;; The TCLOS package exports symbols related to CLOS, including both
;;;     those that are defined in ANSI Common Lisp as being in the 
;;;     COMMON-LISP package and those which are in the proposed defacto
;;;     list symbols in the MOP which are available for introspection.

(import-and-export
  '(add-method allocate-instance built-in-class call-method call-next-method
    change-class class tclos:class-name class-of compute-applicable-methods
    defclass defgeneric define-method-combination defmethod describe-object
    #-translator-supports-clos documentation
    #+translator-supports-clos tclos:documentation
    tclos:ensure-generic-function tclos:find-class find-method
    tclos:function-keywords generic-function initialize-instance
    invalid-method-error make-instance make-instances-obsolete make-method
    method method-combination method-combination-error tclos:method-qualifiers
    next-method-p no-applicable-method no-next-method print-object
    reinitialize-instance remove-method shared-initialize slot-boundp
    slot-exists-p slot-makunbound slot-missing slot-unbound slot-value standard
    standard-class standard-generic-function standard-method standard-object
    structure-class structure-object symbol-macrolet
    update-instance-for-different-class update-instance-for-redefined-class
    with-accessors with-slots)
  "TCLOS")

#+translator-supports-clos
(eval-when (compile load eval)
(dolist (name '("CLASS-DEFAULT-INITARGS"
		"CLASS-DIRECT-DEFAULT-INITARGS" "CLASS-DIRECT-SLOTS"
		"CLASS-DIRECT-SUBCLASSES" "CLASS-DIRECT-SUPERCLASSES"
		"CLASS-PRECEDENCE-LIST" "CLASS-PROTOTYPE"
		"CLASS-SLOTS" "ENSURE-GENERIC-FUNCTION"
		"GENERIC-FUNCTION-ARGUMENT-PRECEDENCE-ORDER"
		"GENERIC-FUNCTION-DECLARATIONS"
		"GENERIC-FUNCTION-INITIAL-METHODS"
		"GENERIC-FUNCTION-LAMBDA-LIST"
		"GENERIC-FUNCTION-METHOD-CLASS"
		"GENERIC-FUNCTION-METHOD-COMBINATION"
		"GENERIC-FUNCTION-METHODS"
		"GENERIC-FUNCTION-NAME" "METHOD-FUNCTION"
		"METHOD-GENERIC-FUNCTION" "METHOD-LAMBDA-LIST"
		"METHOD-SLOT-NAME" "METHOD-SPECIALIZERS" "SLOT-DEFINITION"
		"SLOT-DEFINITION-ALLOCATION" "SLOT-DEFINITION-INITARGS"
		"SLOT-DEFINITION-INITFORM" "SLOT-DEFINITION-INITFUNCTION"
		"SLOT-DEFINITION-NAME" "SLOT-DEFINITION-READERS"
		"SLOT-DEFINITION-TYPE" "SLOT-DEFINITION-WRITERS"
		"STANDARD-ACCESSOR-METHOD" "STANDARD-READER-METHOD"
		"STANDARD-SLOT-DEFINITION" "STANDARD-WRITER-METHOD"))
  (export (intern name "TCLOS") "TCLOS"))

(dolist (name '("COMPUTE-EFFECTIVE-METHOD"
		"FORWARD-REFERENCED-CLASS" "FUNCALLABLE-STANDARD-CLASS"
		"SLOT-BOUNDP-USING-CLASS"
		"SLOT-MAKUNBOUND-USING-CLASS" "SLOT-VALUE-USING-CLASS"))
  (import-and-export (intern name "HOST-CLOS") "TCLOS"))
)

;;; The TCLOSX package exports symbols which we document and support as
;;;     extensions to CLOS.  This is primarily for MOP-related stuff.
(host:in-package :tclosx)

#+translator-supports-clos
(host::import-and-export
 '(add-direct-subclass call-combined-method class-default-superclasses
   class-finalized-p combine-methods compute-class-default-initargs
   compute-class-precedence-list compute-effective-slot-definition
   compute-effective-slot-definition-initargs compute-method-combination
   compute-slots default-initargs define-method-combination-function
   direct-slot-definition direct-slot-definition-class
   effective-slot-definition effective-slot-definition-class
   elide-access-method-p finalize-inheritance find-effective-slot-definition
   internal-standard-class local-method local-slot-definition-p method-class
   no-primary-method optimize-slot-access optimize-slot-accesses
   remove-direct-subclass shared-slot-definition-p
   standard-direct-slot-definition standard-effective-local-slot-definition
   standard-effective-shared-slot-definition standard-effective-slot-definition
   standard-object-ref validate-superclass)
 "TCLOSX")

(host:in-package :host)

;;; The TCLOS-RUN package exports other symbols needed for runtime as part
;;;     of the CLOS implementation.

(host:in-package :tclos-run)

#+translator-supports-clos
(host::import-and-export
  '(%assign-slot-index %call-next-method %call-next-method-arguments
    %class-status-p %class-typep %copy-method-frame
    %effective-method-allow-other-keys-p %effective-method-call
    %effective-method-keyp %effective-method-keys
    %effective-method-keyword-permutation %effective-method-positional
    %effective-method-required %effective-method-restp
    %establish-generic-function %finalize-effective-method %initial-class-info
    %initial-generic-function-info %initialize-slot-index-table
    %instance-wrapper %make-call-next-method-safe %make-call-next-method-unsafe
    %make-effective-method %make-instances-obsolete-slots-to-flush
    %make-next-method-p %method-argument |%METHOD-ARGUMENT(BOXED)|
    %method-argument-list %method-combination-function
    %method-combination-key-value %method-combination-name
    %method-combination-options %method-key-p %method-key-value
    %method-optional-argument-p |%METHOD-OPTIONAL-ARGUMENT-P(BOXED)|
    %method-rest-list %next-method-p %register-class-status %set-class-status-p
    %set-slot-value %set-slot-value-indexed %set-slot-value-using-wrapper
    %slot-boundp %slot-boundp-indexed %slot-boundp-using-wrapper
    %slot-exists-p-indexed %slot-exists-p-using-wrapper %slot-makunbound
    %slot-makunbound-indexed %slot-makunbound-using-wrapper %slot-value
    %slot-value-indexed %slot-value-using-wrapper %sort-parsed-methods
    %standard-object-ref %update-effective-method
    *generic-function-for-method-combination-errors*
    *method-combination-effective-method*
    *method-combination-for-method-combination-errors* add-named-class
    add-named-generic-function add-named-method allocation
    argument-precedence-map argument-precedence-order arguments
    class-fully-defined-p class-status-bits compute-class-prototype
    compute-slot-definition-location compute-slot-definition-locations
    compute-valid-change-class-initargs compute-valid-creation-initargs
    compute-valid-reinitialization-initargs constant-initform-p
    constantly-zero-initfunction critical-methods declarations
    direct-default-initargs direct-slots direct-subclasses direct-superclasses
    display-cache-statistics doc-string effective-methods encoded-lambda-list
    ensure-class eql-specialized-methods find-instance-keyword
    find-standard-method-class find-standard-method-combination
    generic-function initargs initform initfunction initial-methods
    kernel-generic-function keyword-parameter-map lambda-list location
    make-generic-function metaobject metaobject-documentation metaobject-name
    method-class method-combination method-combination-function
    method-combination-name method-combination-options methods name object
    object-change-class-function object-creation-function
    object-initialization-function object-reinitialization-function
    permit-metaobject-reinitialization precedence-list previous prototype
    qualifiers readers record-method-combination-function
    set-class-direct-subclasses set-class-finalized-p set-class-fully-defined-p
    set-generic-function-initial-methods set-generic-function-methods
    set-method-generic-function set-standard-object-ref shared-slot-locations
    slot-definition-location slot-name slot-type slots slots-alist
    slotted-class specialized-positions specializers status-bits superclass
    update-initial-methods valid-change-class-initargs valid-creation-initargs
    valid-reinitialization-initargs value wrapper writers)
  "TCLOS-RUN")

(host:in-package :host)


;;; I assume there is already a KEYWORD package, but maybe the
;;; CL-USER package is missing, or maybe it uses different things.
;;; The translator doesn't use this at all except that it needs a package
;;; object around at translation-time to hang things off of.


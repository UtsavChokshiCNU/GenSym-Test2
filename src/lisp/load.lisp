;;;; -*- Mode: Common-Lisp; Base: 10; Syntax: COMMON-LISP -*-

(in-package #+translator-is-loaded "TCL-USER"
            #+(and (not translator-is-loaded) ansi-cl) "CL-USER"
            #+(and (not translator-is-loaded) (not ansi-cl)) "USER")

;;;; Module LOAD

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Jim Allard, Mark H. David, and John Hodgkinson.



;;;; Loading the AB System

;;; The LOAD module is very dependent on sequential evaluation, and it makes
;;; profound global changes to the Lisp environment.  It should not be
;;; evaluated or compiled incrementally, as there is a danger of spoiling the
;;; lisp environment.  The basic steps performed are:


;; jra & jh, 9/15/92.  Additions made to this file to abstract from the LISP and
;; USER packages.

;; The architecture of the packages will be in flux while we are moving from
;; Chestnut 1.7 to Chestnut 3.1 because 1.7 doesn't implement export correctly,
;; and 3.1 has a package TCL instead of LISP.  In G2 3.0 the package AB
;; used LISP, and we shadowed symbols that we did not want to inherit.  In 3.1
;; we want to have a package AB-LISP that uses LISP or TCL, depending on the
;; platform, AB-LISP exports the LISP symbols we want in AB, and AB uses
;; AB-LISP.  Since export doesn't work in 1.7 (we don't yet know if it works in
;; 3.1) we will use a hybrid architecture for the moment.  AB-LISP will use
;; LISP as is planned for 3.1, but AB will use the LISP package directly, and
;; we will continue to shadow symbols in AB that we don't want from LISP.  This
;; way we don't have to edit the references to AB-LISP that have already been
;; placed into the sources, and we can transition to the 3.1 architecture by
;; editing only the file LOAD.  -jra & jh 2/2/93

;;;    [0] Run pre-launch initialization functions.
;;;
;;;    [1] Set up the AB package system as follows:
;;;      [1.1] Create the package AB-LISP, exporting all Lisp symbols to be used
;;;            by AB so that they are visible without package qualifiers in our
;;;            sources, which are all in-package "AB".
;;;      [1.2] Create the package AB, which uses AB-LISP.
;;;      [1.3] Enter the AB package.
;;;      [1.4] Create facilities to handle symbols we want to place in the USER
;;;            package.
;;;      [1.5] Define the G2-DEFSTRUCT-STRUCTURE-NAME Package
;;;
;;;    [2] Define some parameters (e.g. version) and macros.
;;;
;;;    [3] Shadow the symbols LOOP, DEFMACRO, and DEFINE-MODIFY-MACRO in
;;;        package AB.  After the new Chestnut translator is installed, this
;;;        will no longer be necessary, as it will be handled in item [1.1].
;;;
;;;    [4] Provide any other package related fixes as will be needed by
;;;        specific implementations.
;;;
;;;    [5] Provide minimal lisp implementation fixes that are needed for the
;;;        purposes of the Load and Bootstrap modules before the Lisp Fixes
;;;        can be loaded.
;;;
;;;    [6] Set up *features*
;;;      [6.1] Gensym-info-on-known-file-types -- for Lisp Machines
;;;
;;;    [7] Make various global proclamations
;;;
;;;    [8] Define the bootstrap information, preferably automatically, but
;;;        possibly via query of the user.
;;;
;;;    [9] Declare non-standard file types
;;;
;;;    [10] Miscellany (e.g., set up garbage collection parameters)
;;;
;;;    [11] Load the bootstrap module.


;;;; [0] Run pre-launch initialization functions.

#+(and sbcl (not chestnut-trans))
(setq *compile-print* nil)                ;Don't tell about each fn compiled

;;; The macro adjust-memory-areas-for-load-time is the first form in the first
;;; module in the loading sequence.  This macro changes the default memory area
;;; sizes so that implementations can allocate memory at launch time efficiently
;;; and without "obtaining more memory" messages.  Currently (jh, 9/23/93), the
;;; only such implementation needing this is Chestnut 3.1.

;; Adjust-memory-areas-for-load-time references the macro
;; adjust-memory-areas-if-appropriate, defined in OS-MEMORY.  This macro creates
;; a defvar whise initform calls a runtime library frunction to set the default
;; size for each memory area according to the product being built (G2 or
;; Telewindows).  For further details, see OS-MEMORY.

(defmacro adjust-memory-areas-for-load-time ()
  (if (and (member :chestnut-3 *features*)
           (member :chestnut-trans *features*))
      `(,(intern "ADJUST-MEMORY-AREAS-IF-APPROPRIATE" "AB"))
      nil))

(adjust-memory-areas-for-load-time)

;;;; [1.1] Create the AB-LISP Package

;; According to the Chestnut translator 3.1 User Guide (p 18), the feature
;; :translator-is-loaded is always present in the translator.  The feature
;; :translating is temporarily pushed onto *features* only when the translator
;; is actually reading source files.

;;; The following form exports all the symbols in the LISP package used by AB
;;; from the AB-LISP package, so that they will be accessible in AB.  This means
;;; that our source files won't have to use a package-prefix on core Lisp
;;; symbols (car, +, cond, and the like) after we do the indirection through the
;;; AB-LISP package.

;; jh, 9/15/92.  Note that this indirection is necessary in the first place
;; because of a Chestnut requirement.  We have to shadow some symbols in the
;; LISP package and refer to the original, package-qualified LISP symbols
;; somewhere within the redefinition, and Chestnut no longer wants us to refer
;; to the LISP package directly in our source code.  Their rationale is that
;; each Lisp hosting their translator has a different set of external symbols in
;; its LISP package, and this confuses their translator.  Even without
;; Chestnut's fiat, however, this scenario would have occurred when we switched
;; from the LISP package (from CLtL, 1st ed) to the COMMON-LISP package (ANSI).

;; jh, 9/16/92.  TI defpackage does not obey the description in CLtL/2e.  Trying
;; to :export symbols from the :use package results in a conflict, despite the
;; assurance in CLtL/2e that "the action of :export may be affected by a :use
;; option, because an inherited or imported symbol will be used in preference to
;; creating a new one".  So we must export by hand for now.

;; Chestnut 1.7 does not process defpackage at all, so until we move to Chestnut
;; 3.1 we will have to use make-package.  Hopefully, we can use a real
;; defpackage some sunny day.  -jra 11/6/92

(defmacro export-from-ab-lisp-package ()
  (cond
    ((and (member :translator-is-loaded *features*)
          (member :translating *features*)
          (let ((current-system-symbol?
                  (find-symbol "CURRENT-SYSTEM-BEING-LOADED" "AB")))
            (and current-system-symbol?
                 (boundp current-system-symbol?)
                 (eq (symbol-value current-system-symbol?)
                     (find-symbol "GSI" "AB")))))
     `(export '(t float integer symbol list array) (find-package "AB-LISP")))
    (t `(export
          ;; jra & jh, 9/15/92.  The following list of Lisp symbols was obtained
          ;; by running the development function symbol-index, found in
          ;; ma:>jra>symbol-index.lisp.
          ;;
          ;; We had to add lisp:nil by hand because symbol-index bottoms out at
          ;; nil, instead of regarding it as yet another symbol to index.  Also
          ;; had to add lisp:import, lisp:shadow, lisp:shadowing-import,
          ;; lisp:prog*, lisp:short-site-name, lisp:machine-type, and
          ;; lisp:machine-instance, since symbol-index does not scan this file
          ;; (LOAD).  Also had to add lisp:char-code-limit because symbol-index
          ;; cannot capture lisp symbols mentioned in #.  reader syntax.
          ;;
          ;; Note that we have shadowed several Lisp symbols below in order to
          ;; insert our own definitions in BOOTSTRAP.  They are:
          ;;   catch
          ;;   define-modify-macro
          ;;   defmacro
          ;;   describe
          ;;   funcall
          ;;   gensym
          ;;   if
          ;;   let
          ;;   let*
          ;;   loop
          ;;   multiple-value-bind
          ;;   or
          ;;   unwind-protect
          ;;
          ;; jh, 1/23/93.  Shadowed the following symbols, which are not present
          ;; in the new ANSI Common Lisp.  They are redefined in BOOTSTRAP.
          ;; Each occurrence below is marked with ";Chestnut3.1".
          ;;   char-bit
          ;;   compiler-let
          ;;   define-setf-method
          ;;   get-setf-method
          ;;   set-char-bit
          ;;   special-form-p
          ;;   string-char
          ;;   string-char-p
          ;;
          ;; jh, 5/28/93.  Shadowed the symbol DOCUMENTATION because its home
          ;; package in Lucid is TCLOS, and Chestnut therefore wants to
          ;; construct a TCLOS package for it.
          ;;
          ;; jh, 6/9/93.  Giving up on shadowing *break-on-warnings*.  The new
          ;; 3.1 Chestnut translator does not implement it, but it is never
          ;; needed there, so read macros should suffice.
          ;;
          ;; jh, 1/26/94.  Shadowed the following Lisp pathname symbols that
          ;; have non-consing analogues in PATHNAMES.  It is almost always a
          ;; mistake to use these in distribution.  They are redefined in
          ;; BOOTSTRAP.
          ;;   directory
          ;;   directory-namestring
          ;;   enough-namestring
          ;;   file-namestring
          ;;   delete-file
          ;;   host-namestring
          ;;   make-pathname
          ;;   merge-pathnames
          ;;   namestring
          ;;   parse-namestring
          ;;   pathname
          ;;   pathname-device
          ;;   pathname-directory
          ;;   pathname-host
          ;;   pathname-name
          ;;   pathname-type
          ;;   pathname-version
          ;;   pathnamep
          ;;   probe-file
          ;;   rename-file
          ;;   truename
          ;;   wild-pathname-p
          ;;
          ;; jh, 4/6/95.  Shadowing format for the GSI size project.
          '(
            &allow-other-keys
            &aux
            &body
            &environment
            &key
            &optional
            &rest
            &whole
            *
            **
            ***

            ;; jh, 6/9/93.  *break-on-warnings* is not present in the new 3.1 Chestnut
            ;; translator. -- generally not in ansi-cl (including allegro). (MHD 6/10/00)
            #-(or chestnut-3 ansi-cl)
            *break-on-warnings*

            *debug-io*
            *default-pathname-defaults*
            *error-output*
            *features*
            *package*
            *print-array*
            *print-base*
            *print-case*
            *print-circle*
            *print-escape*
            *print-length*
            *print-level*
            *print-pretty*
            *print-radix*
            *read-base*
            *read-default-float-format*
            *readtable*
            *standard-input*
            *standard-output*
            *terminal-io*
            +
            ++
            +++
            -
            /
            //
            ///
            /=
            1+
            1-
            <
            <=
            =
            >
            >=
            abs
            adjoin
            alpha-char-p
            alphanumericp
            and
            append
            apply
            apropos                                        ; (MHD 11/5/92)
            aref
            array
            array-dimension
            array-element-type
            array-has-fill-pointer-p
            array-rank
            array-total-size
            array-total-size-limit
            arrayp
            ash
            asin
            assert
            assoc
            atan
            atom
            bignum
            bit
            block
            both-case-p
            boundp
            break
            butlast
            byte
            byte-position
            caaaar
            caaadr
            caaar
            caadar
            caaddr
            caadr
            caar
            cadaar
            cadadr
            cadar
            caddar
            cadddr
            caddr
            cadr
            car
            case

            ;; The symbol lisp:catch is not exported, so that we may redefine it
            ;; in the AB package.
            ;;catch

            cdaaar
            cdaadr
            cdaar
            cdadar
            cdaddr
            cdadr
            cdar
            cddaar
            cddadr
            cddar
            cdddar
            cddddr
            cdddr
            cddr
            cdr
            ceiling
            cerror
            char
            ;;char-bit ;Chestnut3.1
            char-code
            char-code-limit
            char-downcase
            char-equal
            char-greaterp
            char-int
            char-lessp
            char-not-equal
            char-upcase
            char=
            char/=
            char<
            char>
            char<=
            char>=
            character
            characterp
            clear-input
            close
            clrhash
            code-char
            coerce
            compilation-speed
            compile
            compile-file
            compiled-function
            compiled-function-p
            ;;compiler-let ;Chestnut3.1
            concatenate
            cond
            cons
            consp
            constantp
            copy-list
            copy-seq
            copy-tree
            cos
            count
            count-if ;jh, 3/5/93.
            decf
            declaration
            declare
            decode-universal-time
            defconstant

            ;; The symbol lisp:define-modify-macro is not exported, so that we
            ;; may redefine it in the AB package.
            ;;define-modify-macro

            ;;define-setf-method ;Chestnut3.1

            ;; The symbol lisp:defmacro is not exported, so that we may redefine it in
            ;; the AB package.
            ;;defmacro
            #+(or allegro lispworks) defpackage

            ;; For :chestnut-3, we redefined to make sure it has tx:global-variable
            ;; declaim.  -- binghe, 2009/5/30
            #-chestnut-3 defparameter
            defsetf
            defstruct
            deftype
            defvar
            delete

            ;; jh, 1/26/94.  Shadowing dangerous Lisp pathname functions (vide
            ;; supra).
            ;;delete-file

            denominator

            ;; The symbol lisp:describe is not exported, so that we may redefine
            ;; it in the AB package.
            ;;describe

            digit-char
            digit-char-p

            ;; jh, 1/26/94.  Shadowing dangerous Lisp pathname functions (vide
            ;; supra).
            ;;directory
            ;;directory-namestring

            disassemble
            do
            do*
            do-all-symbols
            do-symbols

            ;; jh, 6/8/93.  The Chestnut 3.1 translator wants to create a TCLOS
            ;; package for the symbol DOCUMENTATION at run time.  This we do not
            ;; need.
            ;;documentation

            dolist
            dotimes
            double-float
            dribble
            ecase
            ed
            eighth
            elt
            encode-universal-time

            ;; jh, 1/26/94.  Shadowing dangerous Lisp pathname functions (vide
            ;; supra).
            ;;enough-namestring

            endp
            eq
            eql
            equal
            equalp
            error
            eval
            eval-when
            evenp
            every
            exp
            export
            expt
            fboundp
            fceiling
            ffloor
            fifth
            file-author
            file-length

            ;; jh, 1/26/94.  Shadowing dangerous Lisp pathname functions (vide
            ;; supra).
            ;;file-namestring

            file-position
            file-write-date
            fill
            fill-pointer
            find
            find-if
            find-package
            find-symbol
            first
            fixnum
            flet
            float
            floatp
            floor

            fmakunbound ;jh, 7/22/93.  Fixes Fred's lcl:record-source-file advice.

            force-output

            ;; jh, 4/6/95.  Shadowing format for the GSI size project.
            ;;format

            fourth
            fresh-line
            fround
            ftruncate

            ;; The symbol lisp:funcall is not exported, so that we may redefine
            ;; it in the AB package.
            ;;funcall

            function
            functionp

            ;; The symbol lisp:gensym is not exported, so that we may redefine
            ;; it in the AB package.
            ;;gensym

            gentemp
            get
            get-decoded-time
            get-internal-real-time
            get-output-stream-string
            get-setf-expansion
            ;;get-setf-method ;Chestnut3.1
            get-universal-time
            getf
            gethash
            go
            hash-table
            hash-table-count

            ;; jh, 1/26/94.  Shadowing dangerous Lisp pathname functions (vide
            ;; supra).
            ;;host-namestring

            identity

            ;; The symbol lisp:if is not exported, so that we may redefine it in
            ;; the AB package.
            ;;if

            ignorable
            ignore
            import
            in-package
            incf
            inline ; binghe, 2010/7/29
            inspect
            integer
            integer-length
            integerp
            intern
            internal-time-units-per-second
            intersection
            isqrt
            keyword
            keywordp
            labels
            lambda
            lambda-list-keywords
            last
            ldb
            ldiff
            least-positive-double-float
            least-positive-single-float
            length

            ;; The symbols lisp:let and lisp:let* are not exported, so that we
            ;; may redefine them in the AB package.
            ;;let
            ;;let*

            lisp-implementation-version
            list
            list*
            list-length
            listen
            listp
            load
            load-time-value ; new added, used by as-atomic-operation (glbasics)
            locally
            log
            logand
            logandc1
            logandc2
            logbitp
            logcount
            logior
            lognot
            logtest
            logxor
            long-float

            ;; The symbol lisp:loop is not exported, so that we may redefine it
            ;; in the AB package.
            ;;loop

            lower-case-p
            machine-instance
            machine-type
            macro-function
            macroexpand
            macroexpand-1
            macrolet
            make-array
            make-broadcast-stream
            make-hash-table
            make-list
            make-package

            ;; jh, 1/26/94.  Shadowing dangerous Lisp pathname functions (vide
            ;; supra).
            ;;make-pathname

            make-string
            make-string-output-stream
            make-symbol
            make-synonym-stream
            makunbound
            map
            #-chestnut-3 map-into
            mapcar
            mapcan
            maphash
            max
            member
            merge

            ;; jh, 1/26/94.  Shadowing dangerous Lisp pathname functions (vide
            ;; supra).
            ;;merge-pathnames

            min
            minusp
            mismatch
            mod

            ;; Shadowing fixnum limits, use fixed values from 32-bit platform,
            ;; defined in bootstrap.lisp -- Chun Tian (binghe), 2012/5/26
            most-negative-double-float
            most-negative-fixnum
            most-positive-double-float
            most-positive-fixnum

            ;; The symbol lisp:multiple-value-bind is not exported, so that we
            ;; may redefine it in the AB package.
            ;;multiple-value-bind

            multiple-value-call
            multiple-value-list
            multiple-value-prog1
            multiple-value-setq
            multiple-values-limit

            ;; jh, 1/26/94.  Shadowing dangerous Lisp pathname functions (vide
            ;; supra).
            ;;namestring

            nbutlast
            nconc

            ;; jra & jh, 9/17/92.  We do not attempt to export the symbol lisp:nil on
            ;; the TIs, because it doesn't work (lisp:nil stays :inherited instead of
            ;; :external).  Instead, we import lisp:nil by hand into AB on the TIs
            ;; below, after the defpackage for AB.
            ;; jh, 6/8/93.  The same phenomenon happens in Chestnut rev 3.1.
            #-chestnut-3
            nil

            ninth
            not
            notany
            nreconc
            nreverse
            nstring-downcase
            nstring-upcase
            nsubst
            nth
            nthcdr
            null
            number
            numberp
            numerator
            oddp
            open
            optimize

            ;; The symbol lisp:or is not exported, so that we may redefine it in
            ;; the AB package.
            ;;or

            otherwise
            package
            package-name
            parse-integer

            ;; jh, 1/26/94.  Shadowing dangerous Lisp pathname functions (vide
            ;; supra).
            ;;parse-namestring
            ;;pathname
            ;;pathname-device
            ;;pathname-directory
            ;;pathname-host
            ;;pathname-name
            ;;pathname-type
            ;;pathname-version
            ;;pathnamep

            peek-char
            phase
            pi
            plusp
            pop
            position
            position-if
            position-if-not
            pprint
            prin1
            princ
            print

            ;; jh, 1/26/94.  Shadowing dangerous Lisp pathname functions (vide
            ;; supra).
            ;;probe-file

            proclaim
            prog
            prog*
            prog1
            prog2
            progn
            progv
            psetf
            psetq
            push
            pushnew
            quote
            random
            rassoc
            ratio
            read
            read-byte
            read-char
            read-char-no-hang
            read-from-string
            read-line
            rem
            remf
            remove
            remove-duplicates
            remove-if
            remove-if-not
            remprop

            ;; jh, 1/26/94.  Shadowing dangerous Lisp pathname functions (vide
            ;; supra).
            ;;rename-file

            replace
            rest
            return
            return-from
            revappend
            reverse
            room
            rotatef
            round
            rplaca
            rplacd
            safety
            satisfies
            sbit
            scale-float
            schar
            search
            second
            sequence
            set
            ;;set-char-bit ;Chestnut3.1
            set-difference
            setf
            setq
            seventh
            shadow
            shadowing-import
            shiftf
            short-float
            short-site-name
            simple-array
            simple-string
            simple-string-p
            simple-vector
            simple-vector-p
            sin
            single-float
            sixth
            sleep
            #+lispworks some
            sort
            space
            special
            ;;special-form-p ;Chestnut3.1
            #+ansi-cl special-operator-p
            speed
            sqrt
            stable-sort
            step
            stream
            streamp
            string
            string-capitalize
            ;;string-char ;Chestnut3.1
            ;;string-char-p ;Chestnut3.1
            string-downcase
            string-equal
            string-greaterp
            string-lessp
            string-not-equal
            string-not-greaterp
            string-not-lessp
            string-trim
            string-upcase
            string/=
            string<
            string<=
            string=
            stringp
            sublis
            subseq
            subsetp
            subst
            substitute
            svref
            sxhash
            symbol
            symbol-function
            ;;symbol-macrolet
            symbol-name
            symbol-package
            symbol-plist
            symbol-value
            symbolp
            t
            tagbody
            tan
            tenth
            terpri
            the
            third
            throw
            time
            trace
            tree-equal

            ;; jh, 1/26/94.  Shadowing dangerous Lisp pathname functions (vide
            ;; supra).
            ;;truename

            truncate
            type
            type-of
            typecase
            typep
            signed-byte
            union
            unintern ; added by SoftServe
            unless
            unread-char
            unsigned-byte
            untrace

            ;; The symbol lisp:unwind-protect is not exported, so that we may
            ;; redefine it in the AB package.
            ;;unwind-protect

            upper-case-p
            values
            values-list
            variable
            vector
            vectorp
            vector-push
            warn
            when

            ;; jh, 1/26/94.  Shadowing dangerous Lisp pathname functions (vide
            ;; supra).
            ;;wild-pathname-p

            with-open-file
            with-open-stream
            with-output-to-string
            with-input-from-string
            write
            write-byte
            write-char
            write-line
            write-string
            write-to-string
            zerop
               )
          (find-package "AB-LISP")))))



(eval-when (:compile-toplevel :load-toplevel :execute)
  (when (not (find-package "AB-LISP"))
    (make-package
      "AB-LISP"
      :nicknames nil
      :use
      `(#+translator-is-loaded "TCL"
        #+(and (not translator-is-loaded) (not ansi-cl)) "LISP"
        #+(and (not translator-is-loaded) ansi-cl) "COMMON-LISP"
        #+(and sbcl (not translator-is-loaded)) "SB-ALIEN"
        #+(and sbcl (not translator-is-loaded)) "SB-C-CALL")))

  (export-from-ab-lisp-package)

) ;end of eval-when that defines the AB-LISP package




;;;; [1.2] Create the AB Package

(defmacro create-ab-package ()
  `(eval-when (:compile-toplevel :load-toplevel :execute)
     (let ((ab-package-name "AB")
           (ab-package-use-list '("AB-LISP"))
           (extant-ab-package? (find-package "AB")))
       (cond
         (extant-ab-package?
          ,(if (and (member :chestnut-trans *features*)
                    (let ((current-system-symbol?
                            (find-symbol "CURRENT-SYSTEM-BEING-LOADED" "AB")))
                      (and current-system-symbol?
                           (boundp current-system-symbol?)
                           (eq (symbol-value current-system-symbol?)
                               (find-symbol "GSI" "AB")))))
               nil
               `(let ((extant-ab-package-use-list
                        (mapcar #'package-name
                                (package-use-list extant-ab-package?))))
                  (when (set-exclusive-or
                          ab-package-use-list
                          extant-ab-package-use-list
                          :test #'equal)
                    (error
                      "CREATE-AB-PACKAGE: ~
                       Bad use-list ~s for extant AB package.  ~
                       You will certainly lose."
                      extant-ab-package-use-list)))))
         (t (make-package ab-package-name
                          :nicknames nil
                          :use ab-package-use-list))))))

(create-ab-package)


#+under-test
(defun maybe-prepare-g2-macros-for-mocking ()
  (let ((symbol (find-symbol "PREPARE-G2-MACROS-FOR-MOCKING" :CL-USER)))
    (when (and symbol (fboundp symbol))
      (funcall symbol)
      (eval (read-from-string "(mock-macro:enable-macroexpand-hook-for-mocking-macros)")))))

#+under-test
(maybe-prepare-g2-macros-for-mocking)


;; jh, 9/28/93 per bhyde.  Modified the above toplevel form to complain unless
;; the AB package uses exactly the packages we expect.

;; In the form above, we are currently using LISP instead of AB-LISP.  This
;; should change as we move from Chestnut 1.7 to 3.1 (see comments above).
;; Also, we have a problem with the make-package form getting called at
;; run-time in the translated image, since the AB package gets made by special
;; code in g2main.c and twmain.c.  We will get around this problem by calling
;; an explict use-package for Chestnut 1.7, which we hope to fix in Chestnut
;; 3.1 Also note that we are currently using TICL in the AB package.  When we
;; switch back to using AB-LISP, we should remove the TICL package.  -jra & jh
;; 2/2/93

;; jh, 9/24/93.  Now we do package indirection in Lucid development as well as
;; the translator, in order to catch errors sooner.

#+(and chestnut (not translator-is-loaded))
(use-package '(#+ansi-cl "COMMON-LISP" #-ansi-cl "LISP") (find-package "AB"))

;; jh, 9/16/92 (later).  The symbol lisp:nil cannot be exported from a package
;; that uses the LISP package on the TIs.  So we import it by hand here.  Note
;; that we also had to compile-switch out the symbol nil on the list of symbols
;; we exported from the AB-LISP package above.  (Incidentally, the symbol
;; lisp:nil can only be exported from a package into which it was imported, not
;; inherited, reason unknown.  We do not make use of that fact here.)
;; jh, 6/8/93.  The same phenomenon (inability to export lisp:nil) happens in
;; Chestnut rev 3.1.

;; -jh & jra, 3/21/95 We no longer need to support the TI, so only the handling
;; for Chestnut remains.  Also, we no longer export symbols en masse in GSI, but
;; we felt queasy about not having T and NIL in AB be eq to the Lisp package
;; versions.  We "import" T by exporting it from AB-LISP in the macro
;; export-from-ab-lisp-package above, and we import NIL here.

#+chestnut-3
(eval-when (:compile-toplevel :load-toplevel :execute)
  (import (list (find-symbol "NIL" "AB-LISP"))
          (find-package "AB")))

;;;; [1.3] Enter the AB Package

;; jh, 9/10/92.  It might be argued that the preceding forms should appear in a
;; separate file (PRELOAD?) and the following form should appear first in this
;; file (LOAD).  Then again, things are complicated enough already.

(in-package "AB")

;;;; [1.4] Handle Symbols in the USER Package

;; jh, 9/10/92.  Chestnut also advises us to change all references to the USER
;; package to the TCL-USER package.  Our requirements here are different from
;; what drove us to the AB-LISP indirection above.  We don't do any symbol
;; shadowing in the USER package, and we never do an in-pacakge on it.  We do
;; create internal symbols in the USER package for development purposes.  (This
;; makes it possible to do things like kill-old-windows in the Lispm listener
;; that launched G2 without having to use cumbersome package prefixes or even
;; having to grok package constraints at all.) In order to have this convenient
;; behavior, we must affect the actual USER package, not some package that uses
;; it.

;;; Some USER symbols make it to distribution (look at the translation of LOAD,
;;; currently f366.c) although it is not clear that they need to.  For the sake
;;; of these symbols, we institute the function import-into-user-package.  This
;;; function takes as its single arg a symbol which is to be imported into
;;; whatever package serves as a user package in the current Lisp.  If the home
;;; package of the defined symbol is the AB package, an error is signaled.

;;; When ANSI Lisp comes out, we will push :standard-lisp onto *features*, or
;;; convert the :standard-lisp compiler feature in the form below to whatever
;;; ANSI advertises. (It's :ANSI-CL actually.  --binghe, 2009/10/9)

(defvar user-package-in-this-lisp
        #+translator-is-loaded (find-package "TCL-USER")
        #-translator-is-loaded (find-package #+ansi-cl "CL-USER" #-ansi-cl "USER"))

(defvar list-for-import (make-list 1))

(ab-lisp::defmacro import-into-user-package (symbol-from-ab-package)
  (ab-lisp::let ((symbol-var (make-symbol "SYMBOL-FROM-AB-PACKAGE")))
    (cond
      ((and (boundp 'current-system-being-loaded)
            (eq (symbol-value 'current-system-being-loaded) 'gsi)
            (member :chestnut-trans *features*))
       nil)
      (t `(ab-lisp::let* ((,symbol-var ,symbol-from-ab-package)
                          (package-of-symbol (symbol-package ,symbol-var)))
            (unless (eq (find-package "AB") package-of-symbol)
              (error "IMPORT-INTO-USER-PACKAGE:
                      can only import from AB package, ~
                      but symbol ~s is in the ~s package."
                     ,symbol-var
                     (package-name package-of-symbol))
              ;;These lines are unreachable.  Leaving for potential
              ;;documentation purposes
              ;(setf (first list-for-import) ,symbol-var)
              ;(import list-for-import user-package-in-this-lisp)
              ))))))


;;;; [1.5] Define the G2-DEFSTRUCT-STRUCTURE-NAME Package

(eval-when (:compile-toplevel :load-toplevel :execute)
  (ab-lisp::or (find-package "G2-DEFSTRUCT-STRUCTURE-NAME")
               (make-package "G2-DEFSTRUCT-STRUCTURE-NAME"
                 :nicknames nil
                 :use nil)))

;;;; [2] Define some parameters and macros.


;; Things that were here, defvars for latest-delta-version and creation-date,
;; have been moved to module DELTA. (MHD 4/29/94)

;;;; [3] Shadow LOOP, DEFMACRO, and DEFINE-MODIFY-MACRO

;; jh, 9/15/92.  Since we export symbols from the LISP package individually into
;; AB, explicit calls to the Lisp function shadow are no longer necessary.
;; Instead, we simply refrain from exporting the symbols from the LISP package
;; that we want to shadow in the AB package.  Retaining this section for a while,
;; as it has edifying comments.

;;; Preparation for AB's version Loop.  Note that AB's version of loop is
;;; derived from the public domain `Loop Iteration Macro', by Glenn Burke, et
;;; al.  Note that AB's loop is a compatible superset of the `simple loop' in
;;; Common Lisp the Language, by Steele, in that if the first subexpression is
;;; not a loop keyword, the form expanded to be semantically equivalent to
;;; simple loop.

;;; Note that we do not use, nor do we define the macro define-loop-macro,
;;; which has been traditionally present in loop iteration macro
;;; implementations.

#-chestnut-3
(progn
(shadow '(loop))
(shadow '(defmacro))
(shadow '(define-modify-macro))
(shadow '(multiple-value-bind))
(shadow '(defun))
(shadow '(let let*))
(shadow '(or))
(shadow '(gensym))
(shadow '(funcall))
(shadow '(catch))
(shadow '(unwind-protect))
(shadow '(if))
(shadow '(describe))
(shadow '(documentation))
(shadow '(format))
)

;;; The following symbols are shadowed because they have different definitions
;;; (or are not defined) in ANSI Common Lisp vs.  CLtL II.  Our definitions of
;;; these are found in BOOTSTRAP.  See the doc near their definitions in
;;; BOOTSTRAP.

#-chestnut-trans
(shadow '(compiler-let special-form-p string-char
          string-char-p declaim))

;;;; [4] and [5] Shadowing and Implementation-specific, Package-related Fixes

;;; SymScale modified Chestnut 3 supports a TX:GLOBAL-VARIABLE which used to declare
;;; global variable as non-TLS variable (as before) after translation.
;;; By default, we declaim all DEFPARAMETERs into this kind of variable for performance
;;; considerations.                              -- Chun Tian (binghe), 2009/10/9

;;; Following two new macros were defined for convinent define non-TLS variables.
;;;
;;; Clozure CL supports DEFSTATIC for special global variables, SBCL supports
;;; DEFGLOBAL in addition to SB-EXT:GLOBAL, but we don't know if they're mapped
;;; to DEFVAR or DEFPARAMETER.                   -- Chun Tian (binghe), 2010/6/12

#-no-macros
(ab-lisp::defmacro declare-special-global (&body symbols)
  (declare (ignorable symbols))
  #+SymScale
  `(eval-when (:compile-toplevel :load-toplevel :execute)
     #+(and chestnut-3 translator-supports-thread)
     (ab-lisp::declaim (tx:global-variable ,@symbols))
     #+(and lispworks (not chestnut-3))
     (ab-lisp::declaim (hcl:special-global ,@symbols)))
  #-SymScale
  nil)

#-no-macros
(ab-lisp::defmacro declare-special-global-mtg2 (&body symbols)
  (declare (ignorable symbols))
  #+mtg2
  `(eval-when (:compile-toplevel :load-toplevel :execute)
     #+(and chestnut-3 translator-supports-thread)
     (ab-lisp::declaim (tx:global-variable ,@symbols))
     #+(and lispworks (not chestnut-3))
     (ab-lisp::declaim (hcl:special-global ,@symbols)))
  #-mtg2
  nil)     

#-no-macros
(ab-lisp::defmacro defvar-of-special-global (name &body body)
  `(progn
     (declare-special-global ,name)
     (declare-special-global-mtg2 ,name)
     #+(and lispworks (not chestnut-3))
     (define-dspec-alias ,name cl:defvar)
     (defvar ,name ,@body)))

#-chestnut-trans
(shadow '(defparameter))

(ab-lisp::defmacro defparameter (name &body body)
  `(progn
     (declare-special-global ,name)
     (declare-special-global-mtg2 ,name)
     (ab-lisp::defparameter ,name ,@body)))

;; Shadow non-cl symbols in TI lisp global package that not common lisp, but
;; thrown in by TI & we have our own versions, too; not even zetalisp; defined
;; in FRAMES1

;; jh, 7/9/93.  Added development Lucid to the form below, since redefining
;; lcl:delq as a macro sometimes confuses the Lucid close-file function, no
;; doubt among other things.

#+(and lucid (not chestnut-trans))
(shadow
  '(assq memq delq neq nth-value
         class destructuring-bind
         ;; the following are patched (in LISP-FIXES)
         fixnump))

;;;; [6] Set Up *Features*

;;; Development Machines:

;; Every machine is defaulted to compile for development.
;; An environment either has :distribution or :development in *features*

#+(and (not distribution) (not no-macros))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (ab-lisp::if (and (not (member :non-development-macros *features*))
                    (not (member :distribution *features*))
                    (not (member :no-macros *features*)))
               (pushnew :development *features*)
               (setq *features* (delete :development *features*))))

;;; Macro Compiles:

#+no-macros
(pushnew :no-macros *features*)

;; If LOAD was compiled without macros, ensure that :no-macros is in *features*.

;;; Computers:

;; For Allegro really -dkuznick, 8/6/99
#+(and solaris2 (not chestnut-trans))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :solaris *features*))

;; For Lispworks & Clozure
#+(and (or win32 windows) (not chestnut-trans))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :mswindows *features*))

#+(and sparc (not solaris) (not chestnut-trans))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :sunos-but-not-solaris *features*))

;;; Lisp Versions:
#+(and lucid lcl4.0 (not chestnut-trans))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :lucid-4 *features*))

;;; Unix Machines:

#+(and (or solaris linux hppa rs6000 dec sunos-but-not-solaris) (not chestnut-trans))
(pushnew :unix *features*)

#+(and unix (not chestnut-trans))
(pushnew :x11-unix *features*)

;; jh, 6/14/94.  See comment in FEATURES about why we push
;; x11-unix onto *features* even when the image is destined to run on other than
;; UNIX- or X-supporting platforms.

;;; Vanilla:

;; The "vanilla" features are:
;; :vanilla                - a plain Lisp environment.
;; :vanilla-areas        - Temporary areas are non-functional if so.
;; :vanilla-numbers        - Assume no special hooks for the number management facilities.
;; :vanilla-time        - Use Lisp functions for time.
;; :vanilla-unix        - a Standard UNIX environment with X11 and TCP/IP

;; The feature :vanilla will be used when porting to new platforms.  It defines
;; Common Lisp implementations of many Lisp-based system dependant facilities,
;; mostly pertaining to memory and number management.

#+(or translator (not (or lispm lucid)))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :vanilla *features*))

;; Here we treat CL platforms other than Lucid as trivial, because in macros like
;; `float-vector-aref' there're only two branches, one is for :vanilla-numbers,
;; the other is for :lucid. -- Chun Tian (binghe), 4 marzo 2014.

#+(and vanilla (not chestnut-trans))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :vanilla-areas      *features*)
  (pushnew :vanilla-numbers    *features*)
  (pushnew :vanilla-time       *features*))

;;;; [7] Various Global Proclamations

;; jh, 2/12/93.  Here we declaim to Lucid that tx:nonrelocating is a declaration
;; from another Lisp.  We must be careful not to declaim the same thing to
;; Chestnut, so we do not make the declamation when actually translating.  Rick
;; Harris of Chetsnut, in a phone conversation today, told me he thinks it is a
;; bug that the translator does not warn when the user attempts to declaim a
;; native declaration tag like tx:nonrelocating.

#+(and chestnut-3 (not chestnut-trans))
(ab-lisp::declaim (declaration tx:nonrelocating
                               tx:non-state-changing))

;;
;; For LispWorks 6.0.1 debug has to be below 3 due to the bug in
;; (the double-float (ffloor 1d0 1d0)) when it is evaluated in 
;; the function compiled with (debug 3)
;;
#+(and lispworks (not chestnut-trans))
(progn
  
  ;; release
  #-debug-build
  (proclaim '(cl:optimize
              (cl:compilation-speed 0)
              (cl:debug 0)
              (cl:speed 3)
              (cl:safety 0)
              (hcl:fixnum-safety 3)
              (cl:space 0)
              (cl:float 1)))

  ;; debug
  #+debug-build
  (progn
    (setq *features* (delete :debug-build *features*))
    (proclaim '(cl:optimize
                (cl:compilation-speed 0)
                (cl:debug 2)
                (cl:speed 0)
                (cl:safety 3)))))
              
#+(and sbcl (not chestnut-trans))
(progn
  (sb-ext:unlock-package :common-lisp)
  (ab-lisp::declaim (sb-ext:muffle-conditions sb-ext:compiler-note)))

#+(and sbcl (not chestnut-3))
(cl:require :sb-posix)

;; Chestnut requires to set lower level of debugging (1) in order to prevent
;; memory exhaustion

#+(and sbcl (not chestnut-trans))
(proclaim '(cl::optimize
            (cl::compilation-speed 0)
            (cl::speed 0)
            (cl::debug 3)
            (cl::safety 3)))

#+(and clozure (not chestnut-trans))
(setq ccl::*suppress-compiler-warnings* t)

#+(and lispworks (not translator))
(progn
  (setq common-lisp:*load-verbose* nil)        ; These is part of Common Lisp, css 05/09/01
  (setq common-lisp:*compile-verbose* nil)
  (setq system:*stack-overflow-behaviour* :warn)) ; stack-kern needs this

;;;; [8] Define Bootstrap Information

;;; Bootstrap-information holds useful implementation-specific information that
;;; is used during the bootstrap process.  It is a list whose elements are, in
;;; order,
;;;
;;;   (a) Lisp binary file type - a string
;;;
;;;   (b) Lisp source file type - a string
;;;
;;;   (c) KB file type - a string
;;;
;;;   (d) KL file type - a string
;;;
;;;   (e) One of downcase, upcase, or nil.  Downcase tells to system to
;;;   downcase names in filenames.  Upcase tells the system to upcase names in
;;;   filenames.  Nil tells the system not to care about case in filenames.
;;;
;;;   (f) T if there is support in the host file system for version numbers for
;;;   filenames. (See also (8).)
;;;
;;;   (g) A default pathname (which is merged with "bootstrap.lisp" for finding
;;;   the bootstrap file, and from which the default system directory is
;;;   derived.
;;;
;;;   (h) T if bootstrap should operate in the mode of using the common lisp
;;;   directory function to obtain a list the latest source files and
;;;   binary files, assume that  these are truenames, and use this
;;;   information instead of probing each file.  (This  is only useful if
;;;   (f) is T; otherwise, this has no effect).  This usually results in
;;;   (i) fewer file system accesses (probes) (ii) a longer delay in processing
;;;   the first  module (iii) less delay in processing each subsequent
;;;   module (iv) operating on  each file present at the beginning of the
;;;   bootstrap, rather than the file present  at the time the module is
;;;   processed (so writing out files after the first file  has begun being
;;;   processed is guaranteed not to result in that particular file  being
;;;   procesed).
;;;
;;;   (i) explicit-lock-file-type?  -- T, NIL, or a file type.   When this
;;;   is nil, the file locking facility is disabled.  See compile-file-for-bootstrap
;;;   for further information on how this is used.

(defvar bootstrap-information)



;;; Accessors for bootstrap information

;; We should figure a way to shadow these macros so that they are not expanded
;; in distribution compiles.  Defmacro is shadowed in BOOTSTRAP now.  One
;; solution would be to move the shadowing from BOOTSTRAP to just after defmacro
;; is declared as shadowed here in LOAD.  Another solution would be to move
;; these macros to BOOTSTRAP.  -pto 20dec88

#-no-bootstrap
(ab-lisp::defmacro bootstrap-information-lisp-binary-file-type ()
  '(first bootstrap-information))
#-no-bootstrap
(ab-lisp::defmacro bootstrap-information-lisp-source-file-type ()
  '(second bootstrap-information))
#-no-bootstrap
(ab-lisp::defmacro bootstrap-information-kb-file-type ()
  '(third bootstrap-information))
#-no-bootstrap
(ab-lisp::defmacro bootstrap-information-kl-file-type ()
  '(fourth bootstrap-information))
#-no-bootstrap
(ab-lisp::defmacro bootstrap-information-case-of-file-type ()
  '(fifth bootstrap-information))
#-no-bootstrap
(ab-lisp::defmacro bootstrap-information-version-numbers-available-p ()
  '(sixth bootstrap-information))
#-no-bootstrap
(ab-lisp::defmacro bootstrap-information-default-pathname ()
  '(seventh bootstrap-information))
#-no-bootstrap
(ab-lisp::defmacro bootstrap-information-use-directory-function-p ()
  '(eighth bootstrap-information))
#-no-bootstrap
(ab-lisp::defmacro bootstrap-information-explicit-lock-file-type? ()
  '(ninth bootstrap-information))

(defvar ab-system-pathname)
(import-into-user-package 'ab-system-pathname)

(import 'common-lisp:*load-pathname*)        ; more correct - css, 05/03/01

;;; `Source-directory-name' is a function of no arguments that
;;; returns the name of the sandbox we are loading from, for example
;;; "ab".  It computes this first looking for a "buildroot.dat" file
;;; in the directory this module is being loaded from.  Second it
;;; looks in the current directory.  Finally it just gives up and
;;; returns "ab".

(defparameter file-naming-spin-id "buildroot.dat")

(defparameter file-naming-specific-source-directory "srcbox.dat")
(defparameter file-naming-specific-dest-directory "dstbox.dat")
(defparameter file-naming-tools-directory "toolsdir.dat")

(defparameter default-sandbox-location "/bt")
(defparameter default-spin-id "ab")
(defparameter default-sandbox-name
  (ab-lisp::format nil "~A/~A"
                   default-sandbox-location
                   default-spin-id))

;;; GENSYMINT-617: new pathname detection system. -- Chun Tian (binghe)

#-chestnut-trans
(ab-lisp::defun get-environment-variable-value (name)
  #+lispworks (lw:environment-variable name)
  #+sbcl (sb-ext:posix-getenv name)
  #+clozure (ccl:getenv name))

#-chestnut-trans
(ab-lisp::defun component-present-p (value)
  (and value (not (eql value :unspecific))))

#-chestnut-trans
(ab-lisp::defun %directory-pathname-p (pathspec)
  (and (not (component-present-p (ab-lisp::pathname-name pathspec)))
       (not (component-present-p (ab-lisp::pathname-type pathspec)))
       pathspec))

#-chestnut-trans
(ab-lisp::defun pathname-as-directory (pathspec)
  (ab-lisp::let ((pathname (ab-lisp::pathname pathspec)))
    (when (ab-lisp::wild-pathname-p pathname)
      (error "Can't reliably convert wild pathnames."))
    (cond ((not (%directory-pathname-p pathspec))
           (ab-lisp::make-pathname 
            :directory (append 
                        (ab-lisp::or (ab-lisp::pathname-directory pathname)
                                     (list :relative))
                        (list (ab-lisp::file-namestring pathname)))
            :name nil
            :type nil
            :defaults pathname))
          (t pathname))))

#-chestnut-trans
(ab-lisp::defun simplify-pathname (pathname)
  (ab-lisp::truename (ab-lisp::pathname (ab-lisp::namestring pathname))))

#-chestnut-trans
(ab-lisp::defun initialize-directory-name (env default)
  (ab-lisp::let ((value (get-environment-variable-value env)))
    (ab-lisp::if value
        (pathname-as-directory (ab-lisp::pathname value))
      (ab-lisp::let ((result-pathname
                      (simplify-pathname
                       (ab-lisp::make-pathname 
                        :name nil :type nil
                        :directory (append (ab-lisp::or (ab-lisp::pathname-directory
                                                         *load-pathname*)
                                                        '(:relative))
                                           default)
                        :defaults *load-pathname*))))
        (ab-lisp::format t "RESULT-PATHNAME = ~A~%" result-pathname)
        result-pathname))))

(defparameter source-directory-name
  #-chestnut-trans (initialize-directory-name "SRCBOX" '(:up))
  #+chestnut-trans nil)

(defparameter dest-directory-name
  #-chestnut-trans (initialize-directory-name "DSTBOX" '(:up :up "dst"))
  #+chestnut-trans nil)

(defparameter toolsdir-name
  #-chestnut-trans source-directory-name
  #+chestnut-trans nil)

;;;
;;; *fasl-extension* is a variable containing FASL extension (type) 
;;; for a specific Common Lisp implementation. When porting 
;;; to a new CL implementation don't forget to specify it.
;;;

(eval-when (:compile-toplevel :load-toplevel :execute)
  #+ecl 
  (defconstant +ecl-fasl-extension+
    #+ecl-bytecmp "fasc"
    #-ecl-bytecmp "fas")

  (defvar *fasl-extension*
    #+sbcl #.sb-fasl:*fasl-file-type*
    #+clozure #.(cl:pathname-type ccl:*.fasl-pathname*)
    #+allegro #.excl:*fasl-default-type*
    #+lispworks #.system:*binary-file-type*
    #+ecl +ecl-fasl-extension+))

(setq bootstrap-information
      `(,*fasl-extension* "lisp" "kb" "kl" 
                          downcase nil ,*load-pathname* nil nil))

#-no-bootstrap
(ab-lisp::defun use-dates-instead-of-versions-p ()
  (not (bootstrap-information-version-numbers-available-p)))

;;;; [10] Miscellany

#+(and sbcl (not translator))
(setq *print-array* nil)

;;; This section expands Lisp memory to amounts reasonable for a G2 compile.
;;; Note that this code is not emitted into the final translated distributions.
;;; If you need to turn this off, you can do so by setqing lucid-memory-
;;; expanded? to t before loading this file, LOAD.

;;; Also note that we do not have temporary areas for Lucid, and this is
;;; reflected by pushing features denoting this fact.  These features are used
;;; in the with-temporary-XXX-creation macros.

;OBSOLETE?

#+(and lucid (not translator))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :using-egc *features*)
  (pushnew :no-lucid-temporary-areas *features*))

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defvar lisp-memory-expanded? nil))

#+(and lucid (not translator))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (unless lisp-memory-expanded?
    (unless (member "SUPRESS-MEMORY-EXPANSION" *features* :test #'string=)
      (setq lisp-memory-expanded? t)
      (ab-lisp::let ((lcl:*gc-silence* t))
        (lcl:change-memory-management
          ;; Kill Lisp if larger than approx. 524 MB (<=> 8000 X 65536) (MHD/JRA 2/14/97)
          :growth-limit 8000
          ;; Grow 3 Meg at a time (2 hemispheres * 25 segments * 64Kbytes).
          :growth-rate 25
          ;; Add 18 Meg per hemisphere to Lucid's default allocation.
          :expand 250
          ;; Only expand if there is less than 20% free after a GC, default is 33%
          :reclamation-ratio 0.2
          ;; Grow the reserved area by 25 segments at a time, i.e. 1.2 Meg.
          :reserved-growth-rate 25
          ;; Add 52 Meg reserve to the 7 Meg already reserved.
          :expand-reserved 850)
        ;; Set the ephemeral level sizes to 1 Meg, 1.2 Meg, and 1.2 Meg to
        ;; attempt to get lots of garbage reclaimed here.  This is double the
        ;; default sizes.  -jra 1/6/92
        (lcl:egc-options :level-sizes '(16 20 20))))))

#+(and lispworks (not translator))
(eval-when (:compile-toplevel :load-toplevel :execute)

(unless lisp-memory-expanded?                ; relic - css, 05/03/01
  (unless (member "SUPRESS-MEMORY-EXPANSION" *features* :test #'string=)
    (setq lisp-memory-expanded? t)

    (setq common-lisp:*compile-print* nil
          common-lisp:*load-print* nil
          common-lisp:*compile-verbose* t
          common-lisp:*load-verbose* nil
          compiler::*source-file-recording* t
          compiler::*source-level-debugging* t
          compiler::*notice-changed-definitions* t
          compiler::*produce-xref-info* t
          compiler::*load-xref-info* t)))
)

;;;; [11] Loading the Bootstrap Module.

;;; Compile-file-for-bootstrap is just like Common Lisp's compile-file, except that
;;; if (bootstrap-information-explicit-lock-file-type?) is non-nil, it waits, up
;;; to a maximum of around ten minutes, to obtain the `lock' for compiling input-file
;;; and, if successful, owns the lock while it compiling input file.  If
;;; (bootstrap-information-explicit-lock-file-type?) is T, the file type if the lock
;;; file is defaulted to something reasonable; otherwise, it should be a string to
;;; be used as the file type.

;;; The lock is maintained by creating a `lock file', with the
;;; type extention "lock" and otherwise the same pathname as the output file,
;;; that contains a bit of information about the caller (user name, machine
;;; instance, date and time when compilation started, etc.).  Compile-file-
;;; with-lock also contains one additional keyword parameter, :if-exists,
;;; which specifies the action to take if the output file that would be created
;;; by the call to compile-file already exists.  It can be one of nil, :overwrite,
;;; :supercede, or :error.  The default is nil, meaning to skip compiling.  Note
;;; that in all cases, this waits until the lock has been obtained to determine
;;; its action.  Thus, if if-exists is nil, this is guaranteed to return after
;;; the compiled output file has been created, whether by this process right
;;; now, another process before this function was called, or another process while
;;; this function was waiting.   Note that this keyword argument is ignored if
;;; (bootstrap-information-explicit-lock-file-type?) is non-nil, although it
;;; is allowed to be passed in.

;;; Using this function to compile files in all different processes and on all
;;; workstations that may try to compile the same file (to the same output file)
;;; will prevent more than one process from compiling the same file at the same
;;; time.  Note, however, that there is no protection against someone doing
;;; compile-file explicitly on the file in question; this only works if everyone
;;; uses compile-file-for-bootstrap.



;;; The function muffle-if-nuisance-warning-condition takes
;;; a condition of type warning, and if it matches one of our pattern strings, it
;;; muffles the warning.  Otherwise, it takes no action.  Here is a summary of the
;;; warnings and why they're muffled:

;;;;ALLEGRO:
;;; "Variable ... is never used." -- this is there just to eliminate the
;;; warnings about variables that are set but never used for value.  We cannot
;;; conveniently build macros so that these warnings never arise.  Use of
;;; (declare (ignorable ...))  is required, and it's not very simple in many
;;; cases.  Moreover, there are over 300 such warnings in our current sources,
;;; virtually all from macros.  We don't miss these warnings in the SET-only
;;; case, but we very much want them back in the completely unused (not set and
;;; not used for value).  Still, we can more easily live without them entirely
;;; than live with them for the SET case.  We're asking Franz for a better
;;; workaround than this.
;;;
;;; "tag ... is never referenced" -- this is to eliminate warnings about tags
;;; in tagbodies for which there is no corresponding (GO <tag>).  Again, these
;;; are in macros by the score (especially the loop macro), and it's not easy,
;;; and not worthwhile, to change the code to not get these warnings.
;;;
;;; "cond clause ... is unreachable " -- this is to eliminate warnings about
;;; cond clauses (or OR clauses) that the compiler knows cannot be reached.
;;; Problem is that this gets in the way of writing macros generating code that
;;; handle otherwise cases.  For example, the following code
;;;   (defconstant foo 4)
;;;   (defmacro bar (baz) `(or ,baz 27))
;;;   (defun blech () (bar foo))
;;; results in this warning:
;;;   ; While compiling BLECH:
;;;   Warning: cond clause (T 27) is unreachable

;;; This works using match patterns against the strings of warning messages.  This
;;; is not extremely robust, but at least the patterns are intended to survive
;;; variations in initial capitalization, initial whitespace, trailing period,
;;; and trailing whitespace.

;;;;SBCL:
;;;muffle redefinition warnings.  Otherwise eval-when compile and load will
;;;cause a warning.

#+(and sbcl (not chestnut-trans))
(ab-lisp::defun muffle-if-nuisance-warning-condition (condition)
  (when (ab-lisp::typep condition 'sb-kernel:redefinition-warning)
    (ab-lisp::muffle-warning)))

#+(and sbcl (not chestnut-trans))
(ab-lisp::defun handle-defconstant-uneql-condition (condition)
  (ab-lisp::if (equalp (sb-ext:defconstant-uneql-old-value condition)
		       (sb-ext:defconstant-uneql-new-value condition))
    (cl:abort condition)
    (error "redefining <~S> with different value ~S and ~S"
	   (sb-ext:defconstant-uneql-name condition)
	   (sb-ext:defconstant-uneql-old-value condition)
	   (sb-ext:defconstant-uneql-new-value condition))))

#-no-macros
(ab-lisp::defmacro with-gensym-handlers-for-compile-file ((&rest options) &body body)
  (declare (ignore options))
  #+allegro
  `(user::handler-bind
    ((user::warning #'muffle-if-nuisance-warning-condition))
    . ,body)
  #+sbcl
  `(common-lisp:handler-bind
    ((common-lisp:style-warning #'muffle-if-nuisance-warning-condition)
     (sb-ext:defconstant-uneql #'handle-defconstant-uneql-condition))
    . ,body)
  #-(or allegro sbcl)
  `(progn . ,body))

(ab-lisp::defmacro with-gensym-handlers-for-load-file (&body body)
  #+sbcl
  `(common-lisp:handler-bind
    ((common-lisp:style-warning #'muffle-if-nuisance-warning-condition)
     (sb-ext:defconstant-uneql #'handle-defconstant-uneql-condition))
    . ,body)
  #-sbcl
  `(progn . ,body))

;;; Open-lock-file ... returns nil if a file whose pathname is lock-file-pathname
;;; exists.  Otherwise, it opens such a file and an output stream open to that
;;; file.

#-no-macros
(ab-lisp::defun open-lock-file (lock-file-pathname)
  (open
    lock-file-pathname
    :direction :output
    :if-does-not-exist :create
    :if-exists nil))

#-no-macros
(ab-lisp::defun compile-file-for-bootstrap (input-file &rest keyword-arguments)
  (ab-lisp::let* ((if-exists
                    (prog1 (getf keyword-arguments :if-exists)
                           (remf keyword-arguments :if-exists))))
   (with-gensym-handlers-for-compile-file ()
    (ab-lisp::if
      (bootstrap-information-explicit-lock-file-type?)
      (ab-lisp::let* ((input-file-truename
                        (ab-lisp::truename input-file))
                      (output-file? (getf keyword-arguments :output-file))
                      (pathname-type-for-output-file
                        (ab-lisp::if (ab-lisp::or
                                       (null output-file?)
                                       (null (ab-lisp::pathname-type output-file?))
                                       (not (stringp (ab-lisp::pathname-type output-file?))))
                                     (bootstrap-information-lisp-binary-file-type)
                                     (ab-lisp::pathname-type output-file?)))
                      (output-file-pathname
                        (ab-lisp::if output-file?
                                     (ab-lisp::make-pathname
                                       :defaults (ab-lisp::merge-pathnames
                                                   output-file? input-file
                                                   (ab-lisp::pathname-version
                                                     input-file-truename))
                                       :type pathname-type-for-output-file)
                                     (ab-lisp::make-pathname
                                       :defaults input-file
                                       :type pathname-type-for-output-file
                                       :version (ab-lisp::pathname-version
                                                  input-file-truename))))
                      (lock-file-pathname
                        (ab-lisp::make-pathname
                          :defaults output-file-pathname
                          :version (ab-lisp::pathname-version input-file-truename)
                          :type
                          (ab-lisp::or
                            (ab-lisp::if
                              (eq (bootstrap-information-explicit-lock-file-type?)
                                  't)
                              nil
                              (bootstrap-information-explicit-lock-file-type?))
                            (ab-lisp::format nil
                                             "~(~a~)-lock"
                                             pathname-type-for-output-file))))
                      (open-output-stream? nil)
                      (lock-file-truename? nil))
        (ab-lisp::unwind-protect
            (do* ((maximum-total-delay (* 15 60))
                  (total-delay-so-far 0)
                  (delay 5 30)
                  (first-time? t nil)
                  (lock-file-output-stream?))
                 (nil)
              (when (setq lock-file-output-stream?
                          (setq open-output-stream?
                                (open-lock-file lock-file-pathname)))
                (unless first-time?
                  (ab-lisp::format t "got it!~%"))
                (ab-lisp::let ((*standard-output* lock-file-output-stream?))
                  (ab-lisp::format
                    lock-file-output-stream?
                    "~%Locked File: ~s"
                    (ab-lisp::namestring input-file-truename))
                  (ab-lisp::format t "~%Time Locked: ")
                  (ab-lisp::multiple-value-bind
                    (second minute hour date month year
                            day-of-the-week daylight-savings-time-p
                            time-zone)
                      (decode-universal-time (get-universal-time))
                    (declare
                      (ignore day-of-the-week daylight-savings-time-p time-zone)
                      (ignorable date month year hour minute second))
                    #-chestnut-trans
                    (ab-lisp::format t
                            "~2,' d ~a ~2,'0d  ~d:~2,'0d:~2,'0d"
                            ;; e.g. "10 Dec 86  8:05:19"
                            date
                            (nth (- month 1)
                                 '("Jan" "Feb" "Mar" "Apr" "May" "Jun"
                                   "Jul" "Aug" "Sep" "Oct" "Nov" "Dec"))
                            year
                            hour minute second)
                    #+chestnut-trans
                    (ab-lisp::format t "Chestnut format failed in write-time-stamp"))
                  (ab-lisp::format t "~%Machine Type: ~s" (machine-type))
                  (ab-lisp::format t "~%Machine Instance: ~s" (machine-instance)))
                (ab-lisp::let ((truename-of-lock-file-output-stream?
                                 (ab-lisp::truename lock-file-output-stream?)))
                  (close lock-file-output-stream?)
                  (setq open-output-stream? nil)
                  (setq lock-file-truename? truename-of-lock-file-output-stream?)
                  (ab-lisp::let ((truename-of-existing-output-file?
                                   (ab-lisp::probe-file output-file-pathname)))
                    (ab-lisp::if (and truename-of-existing-output-file?
                                      (ab-lisp::or
                                        (bootstrap-information-version-numbers-available-p)
                                        (>= (file-write-date truename-of-existing-output-file?)
                                            (file-write-date input-file-truename))))
                                 (case if-exists
                                   ((nil)
                                    truename-of-existing-output-file?)
                                   (:error
                                    (error "The file ~s already exists."
                                           truename-of-existing-output-file?))
                                   (t                ; (:overwrite :supercede)
                                    (apply
                                      'compile-file
                                      input-file
                                      (cond
                                        ((eq if-exists :supercede)
                                         (setf (getf keyword-arguments :output-file)
                                               (ab-lisp::make-pathname
                                                 :defaults output-file-pathname
                                                 :version :newest))        ; portable?!
                                         keyword-arguments)
                                        (t keyword-arguments)))))
                                 (apply 'compile-file input-file keyword-arguments))))
                (return))
              (when first-time?
                (with-open-file
                  (input-stream?
                    lock-file-pathname
                    :direction :input
                    :if-does-not-exist nil)
                  (when input-stream?
                    (do* ((line?
                            (read-line input-stream? nil nil)
                            (read-line input-stream? nil nil)))
                         ((null line?))
                      (write-line line?)))))
              (cond
                ((< total-delay-so-far maximum-total-delay)
                 (ab-lisp::format t "~%File locked; retrying in ~d seconds ... " delay)
                 (force-output)
                 (do* ((seconds-delayed 0 (+ seconds-delayed 1)))
                      ((= seconds-delayed delay))
                   (when (member (read-char-no-hang)
                                 '(
                                   #.(code-char 1)        ;control-A
                                   #.(code-char 3)        ;control-C
                                   #.(code-char 27)        ;escape
                                   ))
                     (ab-lisp::format t "~%Compiling was aborted.~%")
                     (return nil))
                   (sleep 1))
                 (incf total-delay-so-far delay))
                (t (cerror
                     (ab-lisp::format nil "Skip compiling ~s"
                             (ab-lisp::namestring input-file-truename))
                     "Cannot get lock for ~s"
                     (ab-lisp::namestring input-file-truename))
                   (return))))
          (ab-lisp::if (and open-output-stream?
                            (ab-lisp::probe-file open-output-stream?))

                       ;; timeout waiting for lock or abnormal exit case:
                       (ab-lisp::delete-file open-output-stream?)

                       ;; normal unlocking case:
                       (when (and lock-file-truename?
                                  (ab-lisp::probe-file lock-file-truename?))
                         (ab-lisp::delete-file lock-file-truename?)))))
      (apply 'compile-file input-file keyword-arguments)))))

#-(or no-bootstrap translator)
(eval-when (:compile-toplevel :load-toplevel :execute)
(ab-lisp::defun load-bootstrapping-file
    (pathname-name &optional (ignore-if-no-file? nil))
  (setq pathname-name (string pathname-name))               ;ensures that it is a string
  (prog*
    ((binary-directory
       (cl:ensure-directories-exist
         (ab-lisp::make-pathname
           :directory (append (ab-lisp::pathname-directory (bootstrap-information-default-pathname))
                              (list :up :up "dst" "lisp" cl-user::*dest-macro-directory-name*))
           :defaults (bootstrap-information-default-pathname))))
     (binary-pathname
       (ab-lisp::make-pathname
         :directory (ab-lisp::pathname-directory binary-directory)
         :name (ecase (bootstrap-information-case-of-file-type)
                 (upcase (string-upcase pathname-name))
                 ((downcase nil) (string-downcase pathname-name)))
         :type (bootstrap-information-lisp-binary-file-type)
         :version :newest))
     ;; Note that we made a hacky patch
     (source-pathname
       (ab-lisp::make-pathname
         :host (ab-lisp::pathname-host (bootstrap-information-default-pathname))
         :defaults (bootstrap-information-default-pathname)
         :name (ecase (bootstrap-information-case-of-file-type)
                 (upcase (string-upcase pathname-name))
                 ((downcase nil) (string-downcase pathname-name)))
         :type (bootstrap-information-lisp-source-file-type)
         :version :newest))
     binary-truename?
     source-truename?
     (file-symbol (intern (string-upcase pathname-name))))

         (setq binary-truename?
               (ab-lisp::probe-file binary-pathname)
               source-truename?
               (ab-lisp::probe-file source-pathname))
         (cond
           ((and (null source-truename?) (null binary-truename?))
            (when (not ignore-if-no-file?)
              (ab-lisp::format
                t
                "Cannot locate ~a source (~s) or binary (~s). Aborting."
                file-symbol
                (ab-lisp::namestring source-pathname)
                (ab-lisp::namestring binary-pathname)))
            (return nil)))
         (setq ab-system-pathname source-pathname)
         (cond
           #+ignore ; always re-compile the three bootstrap files --binghe
           ((and (null source-truename?) binary-truename?)
            (ab-lisp::format t "~&Loading ~a" binary-truename?)
            (with-gensym-handlers-for-load-file
             (load binary-truename?))
            (setf (get file-symbol 'module-pathname-previously-loaded?)
                  binary-truename?)
            (when (use-dates-instead-of-versions-p)
              (setf
                (get file-symbol
                     'file-write-date-of-previously-loaded-module?)
                (file-write-date binary-truename?))))
           ((and source-truename?
                 (ab-lisp::or
                   (null binary-truename?)
                   (ab-lisp::if
                     (not
                       (bootstrap-information-version-numbers-available-p))
                     (< (setf
                          (get file-symbol
                               'file-write-date-of-previously-loaded-module?)
                          (file-write-date binary-truename?))
                        (file-write-date source-truename?))
                     (> (ab-lisp::pathname-version source-truename?)
                        (ab-lisp::pathname-version binary-truename?)))))
            #-no-macros
            (ab-lisp::let ((output-file-pathname
                             (ab-lisp::make-pathname
                               :defaults binary-pathname
                               :version (ab-lisp::pathname-version source-truename?)))
                           #+lucid
                           (lucid::*gc-silence* t))
              (ab-lisp::format t "~&Compiling: ~a" source-truename?)
              (ab-lisp::format t "~%~2Tto ~a" output-file-pathname)
              (when (not (member :development *features*))
                (cerror "Continue"
                        "~%~%WARNING:  ~
                         About to compile ~s in NON DEVELOPMENT environment.~%~
                         This is not healthy.~%~%"
                        source-truename?))
              (compile-file-for-bootstrap
                source-truename? :output-file output-file-pathname)
              (ab-lisp::format t "~&Loading ~a" binary-pathname)
	      (with-gensym-handlers-for-load-file
		(load binary-pathname))
              (when (not (bootstrap-information-version-numbers-available-p))
                (setf (get file-symbol
                           'file-write-date-of-previously-loaded-module?)
                      (file-write-date binary-pathname)))
              (setf (get file-symbol 'module-pathname-previously-loaded?)
                    (ab-lisp::truename binary-pathname))))
           (source-truename?
            (ab-lisp::format t "~&Loading ~a" binary-pathname)
	    (with-gensym-handlers-for-load-file
	      (load binary-pathname))
            (ab-lisp::if
              (not (bootstrap-information-version-numbers-available-p))
              (setf
                (get file-symbol
                     'file-write-date-of-previously-loaded-module?)
                (file-write-date binary-pathname)))
            (setf (get file-symbol 'module-pathname-previously-loaded?)
                  (ab-lisp::truename binary-pathname)))))))

#-translator
(eval-when (:load-toplevel :execute)                        ;not compile
  (when (not (member :no-bootstrap *features*))
    (load-bootstrapping-file "bootstrap")
    (load-bootstrapping-file "systems")                ; contains declare-system's
    (load-bootstrapping-file "delta" t)))

;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module FEATURES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David, Anne Chinn and Ben Hyde





;;;; Introduction

;;; This module provides a home for managing the *features* list.  It contains a
;;; facility for declaring the set of all things found in the features list.  In
;;; addition some portion of the actual munging of the features list is in this
;;; file.  Much of the munging of the features list is done in BOOTSTRAP and
;;; LOAD.

;;; Most importantly all *features* entries known to G2 are documented in this
;;; module.

;;; `*Features*' exists at runtime, but it is never, or very very rarely
;;; accessed.  Instead of using *features* at runtime see g2-machine-type and
;;; g2-operating-system. See also feature-case, and eval-feature.

;; JH cons'd up this table of what appears in the runtime *features* list.
;; These are probably all a mistake, and some are just wrong.
;;                   feature ; whence                                where
;;                   ------- ; ------                                -----
;;                     :KFEP ; non-eval-when toplevel form           KFEP1
;;                :C-STREAMS ; non-eval-when toplevel form           STREAMS
;;                    :ASCII ; eval-when all-situations              CHARACTERS
;;      :TOOLKIT-DEVELOPMENT ; non-eval-when toplevel form           FEATURES
;;             :DISTRIBUTION ; boot-all-modules-of-system            BOOTSTRAP
;; :NO-LUCID-TEMPORARY-AREAS ; featured eval-when all-situations     LOAD
;;                :USING-EGC ; boot-all-modules-of-system            BOOTSTRAP
;;                           ;   & featured eval-when all-situations LOAD
;;                 :X11-UNIX ; featured non-eval-when toplevel form  LOAD
;;                     :UNIX ; featured non-eval-when toplevel form  LOAD
;;                  :LUCID-4 ; featured eval-when all-situations     LOAD
;;                  :LUCID-3 ; featured eval-when all-situations     LOAD
;;                     :SUN4 ; featured eval-when all-situations     LOAD
;;                      :SUN ; featured eval-when all-situations     LOAD
;;                :NO-MACROS ; featured non-eval-when toplevel form  BOOTSTRAP
;;                           ;   & boot-all-modules-of-system        BOOTSTRAP
;;                 :CHESTNUT ; boot-system                           BOOTSTRAP
;; - ben, jh 7/9/93







;;;; Declarating *FEATURE* Entries




;;; All features that appear in *FEATURES* of any Lisp Implementation
;;; that AB encounters are enumerated below, for each such feature
;;; on `def-feature' form exists.  If a feature is encounted that
;;; we haven't heard of we attempt to generate a warning at load or
;;; compile time.

;;; The def-feature forms provide an chance to document the meaning
;;; of each *feature* entry.

;;; All features no longer in use should also have def-feature forms
;;; to maintain a historical record.

;; - ben 7/8/93




;;; The syntax/sematics of the forms found in def-feature predicates is
;;; slightly extented.  A special token `:feature-predicate-true' is used
;;; to indicate an always true test.

(defmacro feature-predicate (feature-keyword)
  `(get 'feature-predicate ,feature-keyword))


;;; `Def-feature' takes a keyword, i.e. the name of an occational
;;; entry in the *features* list.  It takes an optional second
;;; argument which is a #+ style predicate which must be true
;;; when ever the feature appears.  For example one might write
;;;   (def-feature :chestnut (and lucid lcl4.0 (not lcl4.1) (not chestnut-3)))

(defmacro def-feature (feature-keyword &optional (predicate :feature-predicate-true))
  (unless (keywordp feature-keyword)
    (warn "in def-feature ~S should be a keyword" feature-keyword))
  `(progn
    (setf (feature-predicate ,feature-keyword) ',predicate)
    ,feature-keyword))




;;; `Validate-*feature*' is a development only function which when called
;;; will complain if any of the entries in *features* hasn't been declared
;;; via def-feature, or if it's predicate doesn't evaluate to true.  See
;;; G2-PATCHES for an invocation of this function.

(defmacro validate-*features* ()
  (validate-*features*-1)
  nil)

(defun-for-macro validate-*features*-1 ()
  (dolist (feature *features*)
    (let* ((feature-predicate? (feature-predicate feature))
           (ok? (and feature-predicate?
                    (check-feature-p feature
                                     feature-predicate?
                                     '(:feature-should-not-be-used-in-code)))))
      (unless ok?
        (format t "~&Warning problem with *feature* entry ~S" feature)
        (if feature-predicate?
            (format t "~&   def-feature predicate failed: ~A" feature-predicate?)
            (format t "~&   feature unknown to def-feature."))))))


;;; `Check-feature-p' takes three arguments and implements our extended feature
;;; test.  The first argument is the feature who's predicate is being tested,
;;; this argument is currently unused.  The second argument is the predicate and
;;; we recursively tour this expression to compute our result.  The third
;;; argument is a list of additional features to pretend currently appear on the
;;; *features* list.

(defun-for-macro check-feature-p (feature feature-predicate pretend-features)
  (or (eql feature-predicate :feature-predicate-true)
      (typecase feature-predicate
        (cons
         (case (car feature-predicate)
           (and
            (dolist (subpredicate (rest feature-predicate) t)
              (unless (check-feature-p feature subpredicate pretend-features)
                (return nil))))
           (or
            (dolist (subpredicate (rest feature-predicate))
              (when (check-feature-p feature subpredicate pretend-features)
                (return t))))
           (not
            (not (check-feature-p feature (second feature-predicate)
                                  pretend-features)))))
        (symbol
         (if (or (member (symbol-name feature-predicate)
                         *features*
                         :key #'symbol-name
                         :test #'string=)
                 (member (symbol-name feature-predicate)
                         pretend-features
                         :key #'symbol-name
                         :test #'string=))
             t)))))

;; It would be interesting to rebind the #+ #- reader macros, and
;; to allow feature-case and friends to do some semantic checking for
;; misspellings etc.  - ben 7/8/93


;;; Turns off checks that "shouldn't" fail but do it
(def-feature :no-misterious-checks-in-dev)

;;;; Declare Misc. Undocumented Features


;;; The features declared in this section should be documented but at
;;; this time they are not.

;; Please maintain this list in alphabetical order.

(def-feature :acl-socket)
(def-feature :allegro)
(def-feature :allegro-cl-professional)
(def-feature :allegro-v5.0)
(def-feature :allegro-version>=)
(def-feature :ansi-cl)
(def-feature :ascii)
(def-feature :big-endian)
(def-feature :c-streams)
(def-feature :clos)
(def-feature :clx-little-endian)
(def-feature :clx-overlapping-arrays)
(def-feature :comment)
(def-feature :common-lisp)
(def-feature :compiler)
(def-feature :compiler-debug)
(def-feature :compose-char-bit)
(def-feature :conforming-ieee)
(def-feature :cons)
(def-feature :debugging)
(def-feature :def-font)
(def-feature :defstruct)
(def-feature :demo)
(def-feature :dlfcn)
(def-feature :draft-ansi-cl-2)
(def-feature :drag-to-draw)
(def-feature :dynload)
(def-feature :dynload-acl-library)
(def-feature :egc)
(def-feature :enable-ole)
(def-feature :excl)
(def-feature :fasload)
(def-feature :find-callers)
(def-feature :flavors)
(def-feature :franz-inc)
(def-feature :gensym-typed-arithmetic)
(def-feature :grindef)
(def-feature :gsgc)
(def-feature :ieee)
(def-feature :ieee-floating-point)
(def-feature :ignore)
(def-feature :ignore-view-pad-limits)
(def-feature :ip)
(def-feature :kfep)
(def-feature :lep)
(def-feature :libxml)
(def-feature :line)
(def-feature :lisp-streams)
(def-feature :lucid)
(def-feature :lucid-2)
(def-feature :lucid-2-0)
(def-feature :lucid-4)
(def-feature :meta-bit)
(def-feature :monitoring)
(def-feature :multiprocessing)
(def-feature :multitasking)
(def-feature :mxt)
(def-feature :newcfg)
(def-feature :newio)
(def-feature :no)
(def-feature :no-bootstrap)
(def-feature :no-lucid-temporary-areas)
(def-feature :nupec)
(def-feature :old)
(def-feature :old-evaluators)
(def-feature :old-font-files)
(def-feature :old-vms-arthur)
(def-feature :porting)
(def-feature :pqc)
(def-feature :regular-expression-object)
(def-feature :remote-updates)
(def-feature :run-while-reset)
(def-feature :scroll-bar)
(def-feature :shadow-symbol-function)
(def-feature :shadow-symbol-value)
(def-feature :simple-unix-rg)
(def-feature :sort)
(def-feature :string)
(def-feature :tcp-sockets)
(def-feature :tes)
(def-feature :testing)
(def-feature :testing-icon-editor-widgets)
(def-feature :trace)
(def-feature :unrestricted)
(def-feature :use-structs-in-compiler)
(def-feature :using-egc)
(def-feature :x3j13)
(def-feature :xlib)

;; End of list







;;;; Features Being Phased Out

;;; If you encounter a feature that is being phased out in source code
;;; you may remove the now dead code associated with it.  These features
;;; should never appear in the *features* list again.

;; It would be nice if a redefinition of the reader macros could generate
;; warnings on the use of these.


(def-feature :ccl :feature-being-phased-out)
(def-feature :clx-little-endian :feature-being-phased-out)
(def-feature :clx-overlapping-arrays :feature-being-phased-out)
(def-feature :cons :feature-being-phased-out)
(def-feature :defstruct :feature-being-phased-out)
(def-feature :demo :feature-being-phased-out)
(def-feature :genera :feature-being-phased-out)
(def-feature :fasload :feature-being-phased-out)
(def-feature :grindef :feature-being-phased-out)
(def-feature :ip :feature-being-phased-out)
(def-feature :kfep :feature-being-phased-out)
(def-feature :line :feature-being-phased-out)
(def-feature :lucid-2-for-os4 :feature-being-phased-out)
(def-feature :meta-bit :feature-being-phased-out)
(def-feature :mxt :feature-being-phased-out)
(def-feature :newio :feature-being-phased-out)
(def-feature :ps2 :feature-being-phased-out)
(def-feature :sort :feature-being-phased-out)
(def-feature :string :feature-being-phased-out)
(def-feature :trace :feature-being-phased-out)
(def-feature :vaxlisp :feature-being-phased-out)
(def-feature :xlib :feature-being-phased-out)
(def-feature :xlt :feature-being-phased-out)







;;;; Features That Should NOT Appear In Code.

;;; Features whose predicate is :feature-should-not-be-used-in-code
;;; may appear in the *features* list code should never need to
;;; dispatch on them.

(def-feature :multio :feature-should-not-be-used-in-code)
(def-feature :svr4 :feature-should-not-be-used-in-code)
(def-feature :dbcs :feature-should-not-be-used-in-code)

;; These three graduated here from from :feature-being-phased-out today.
;; (MHD 9/15/93)
(def-feature :ibcl :feature-should-not-be-used-in-code)
(def-feature :ibcl-memory-check :feature-should-not-be-used-in-code)
(def-feature :ibcl-static-compile :feature-should-not-be-used-in-code)

(def-feature :top-down :feature-being-phased-out) ; ex-parser feature --
                                        ;  make this permanent, i.e.,
                                        ;  :feature-should-not-be-used-in-code
                                        ;  soon! (MHD 12/7/94)
(def-feature :optimize-translator :feature-should-not-be-used-in-code)


(def-feature :c-to-ffi :feature-should-not-be-used-in-code)
(def-feature :jeida-nihongo :feature-should-not-be-used-in-code)




;;;; Features that Determine the Lisp Implementation



;;; One of these four configurations is currently being supported.
;;; (or lispm
;;;      (and lucid lcl4.1 (not chestnut))
;;;      (and lucid lcl4.0 (not lcl4.1) chestnut)
;;;      (and lucid lcl4.1 chestnut-3))

;;; The need to make distinctions between 4.1, and 4.0 should be extremely rare.


;;; `Chestnut' is the name used for the Lisp to C translator we utilize.
;;; There are two chestnut versions `chestnut' the original, and `chestnut-3'
;;; their third release.  These two tokens appear as features when you
;;; load their translator, and at runtime.

(def-feature :chestnut   (and lucid lcl4.0 (not lcl4.1) (not chestnut-3)))
(def-feature :chestnut-3 (and lucid lcl4.1 (not chestnut)))
(def-feature :chestnut-3-2-7 (and lucid lcl4.1 chestnut-3 (not chestnut)))

(def-feature :dllexport-function (and lucid chestnut-3))

;;; The feature `translator' is pushed onto the *features* list during
;;; the final translation pass of a compile.

(def-feature :translator (and lucid chestnut))




;;; The feature `translator-is-loaded' is available when the Chestnut Version 3
;;; translator is loaded into the Lisp environment.

(def-feature :translator-is-loaded (and lucid chestnut-3))




;;; `Lispm' is used to signal that we are within the Generic Lisp Machine
;;; dialect of Common Lisp.  But this is more commonly used for to sense
;;; the hardware archecture.

;;; `Lucid' is used to sense that we are using the Lucid dialect
;;; of Common Lisp.  Total accuracy requires that you also check if
;;; chestnut translator is masking out Lucid, but this is rarely
;;; necessary.

(def-feature :lucid (not :allegro))
(def-feature :liquid (not :allegro))
(def-feature :lcl (not :allegro))


;;; There have been many versions of lucid in the history of the project.  Some
;;; of the features signalling these versions are entirely obsolete, while
;;; others still appear in the features list, but not in code.



(def-feature :lcl5.0
    (and :lcl4.2))


(def-feature :lcl4.2
    (and :lcl4.1))
;         :feature-should-not-be-used-in-code))  ;; Rarely needed.

(def-feature :lcl4.1
    (and :lcl4.0))
;         :feature-should-not-be-used-in-code))  ;; Rarely needed.

(def-feature :lcl4.1.1
    (and :lcl4.1))


(def-feature :lcl4.0
    (and :lcl3.0))
;         :feature-should-not-be-used-in-code)) ;; Rarely needed.

(def-feature :lcl3.0
    (and :lucid-3
         :feature-should-not-be-used-in-code))

(def-feature :lucid-3
    (and :lucid
         :feature-should-not-be-used-in-code))

(def-feature :lucid-2
    (and :lucid
         :feature-being-phased-out
         :feature-should-not-be-used-in-code))

(def-feature :lucid-2-0
    (and :lucid
         ;; :feature-being-phased-out
         ;; I phased out this feature completely today. (MHD 10/27/93)
         :feature-should-not-be-used-in-code))


(def-feature :shared-libraries)



;;; The version of Franz Allegro Common Lisp (ACL) 5.0.1 for Linux/Intel has
;;; these features:
;;;
;;;   little-endian redhat5 linux86 x86 verify-car-cdr allegro-v5.0.1
;;;
;;; Since they're specific to ACL and/or other specifics of this environment,
;;; these should not normally be used in code.

(def-feature :x86 :little-endian)
(def-feature :x86 (not :lucid))

(def-feature :verify-car-cdr :allegro)
(def-feature :allegro-v5.0.1 :allegro)





;;;; Features to Declare the Major Compiling Styles

;;; There are 3 major styles we compile G2 in.
;;  1.development
;;;   Known as a development compile.
;;; 2.(and (not development) (not distribution))
;;;   This is the first pass of the build.
;;; 3.(and :no-macro)
;;;   This is the second pass of the build.

;;; In `development' a compile large number of additional checks and
;;; debugging tools are included into the code.

;;; In Pass 1 of the build we create a Lisp Process that contains
;;; all the macros support.

;;; In Pass 2 of the build we create FASL files or C files that do not contain
;;; macros, or the support routines for macros.  See defvar-for-macro,
;;; defconstant-for-macro, defmacro, etc. for examples.

(def-feature :no-macro)
(def-feature :no-macros)
(def-feature :development)
(def-feature :compiled-fun-in-development)
;;uncomment these lines to turn back on funcall-compiled-function optimization in development
;#+development
;(pushnew :compiled-fun-in-development *features*)


;;; `Distribution' is probably obsolete feature that was once used to
;;; feature in code that was only included in distribution images.

;; Is this right? - ben 7/9/93

(def-feature :distribution no-macro)



;;; `Chestnut-trans' is a feature used to signal that we are in the second pass
;;; of the build and that we are creating C code, rather than FASL files as our
;;; output.  This is a feature pushed by Gensym and not by Chestnut.  The rev 3

(def-feature :chestnut-trans
    (and (not :development)
         (or (and chestnut translator)
             (and chestnut-3 translator-is-loaded translator))))

;;; Chestnut translator also pushes the feature `:translating' during our second
;;; pass, but we do not make use of that.

(def-feature :translating
    (and chestnut-trans
         feature-should-not-be-used-in-code))


(def-feature :gsi-in-g2)

(def-feature :use-a-structure-for-frame-serial-numbers)

(def-feature :use-queue-allocation-for-consing)




;;;; Features to Declare the Minor Compiling Variations


(def-feature :incremental-trans)



;;; The *features* entry `:supress-memory-expansion' maybe pushed, by
;;; hand, on *features* prior to loading "load".  It will supress the
;;; default expansion of the Lucid process memory.  This is approprate
;;; when loading a Telewindows that has already been compiled uptodate.

(def-feature :supress-memory-expansion
    (and lucid development))




;;; `:Just-telewindows' must be pushed into *features* is you want to
;;; load Telewindows, but not G2, into a LispM or Lucid.  It enables
;;; the code in TW-PATCHES which would otherwise corrupt the
;;; cohabitating G2.

(def-feature :just-telewindows
    (and lucid development))

;; (progn (pushnew :just-telewindows *features*) (pushnew :supress-memory-expansion *features*))



;;; `:gsi-web' is used to indicate a Weblink compile/translation.  Weblink is
;;; compiled/translated as GSI, but with this feature enabled, it will include
;;; the additional files needed by Weblink, and modify some common files to work
;;; with Weblink.  See bootstrap.lisp, and the trail doc 0269-gw51r1-branch.txt.

(def-feature :gsi-web)




;;; The feature `:meter-init-memory' may be pushed by hand, prior to a full
;;; recompile, to enable various meters that meter how much memory is allocated
;;; at process launch time by various subsystems of G2 like structures and class
;;; definitions.  -jra 8/3/94

(def-feature :meter-init-memory)




;;; The feature `:do-not-check-for-aborts' is pushed by 123.lisp when it is
;;; executed via command line arguments and not as an interactive tool.  This
;;; inhibits bootstrap code from looking for Control-A and other characters on
;;; the input stream which can be used tocleanly stop a compile or load process.

(def-feature :do-not-check-for-aborts)






;;;; Features to Declare Platform


;;; In the history of the project we have compiled on many different platforms.
;;; Currently most platform specific code is handled in one of two ways.  A
;;; small portion is controled by Lisp read time feature switches, while the
;;; larger portion is controled by C or runtime switching.

(def-feature :unix)

;; Features to identify our active or historically important (Sun4) platforms.
;; Note, we do not have a symbol specifically for HP on Itanium: if we ever
;; acquire a Lisp for that platform, we can see what symbol it chooses to use.
;; We also do not have a way to distinguish between the pthreads version of
;; Linux and the older version, even though to a small extent they are separate
;; "platforms" in 8.3r1.  The old Linux will go away soon anyway.  -jv, 8/2/07
(def-feature :mswindows)  ;; aka intelnt, win32, microsoft
(def-feature :solaris)
(def-feature :linux)
(def-feature :rs6000)  ;; IBM AIX
(def-feature :hppa) ;; HP-UX but not Itanium
(def-feature :dec)  ;; Alpha OSF/Digital Unix/Tru64 Unix
(def-feature :sunos-but-not-solaris) ;; SunOS 4 (aka Solaris 1)


;; These three should not be used, except to push the preferred symbol onto the
;; features list.
(def-feature :solaris2     :feature-should-not-be-used-in-code)
(def-feature :sparc        :feature-should-not-be-used-in-code)
(def-feature :win32        :feature-should-not-be-used-in-code)

;; These are either old or redundant and should not be used at all.
(def-feature :h9000        :feature-should-not-be-used-in-code)
(def-feature :hp           :feature-should-not-be-used-in-code)
(def-feature :ibm-aix      :feature-should-not-be-used-in-code)
(def-feature :microsoft    :feature-should-not-be-used-in-code)
(def-feature :microsoft-32 :feature-should-not-be-used-in-code)
(def-feature :sun          :feature-should-not-be-used-in-code)
(def-feature :sun-os       :feature-should-not-be-used-in-code)
(def-feature :sun4         :feature-should-not-be-used-in-code)
(def-feature :sunos        :feature-should-not-be-used-in-code)

;; These refer to platforms which are completely dead (although one still might
;; hope for a resurrection of the Mac port), or to hardware attributes, which we
;; try not to bifurcate on.  ("i386" and "intel-386" referred to a specific Unix
;; platform on which we once ran.)
(def-feature :aviion       :feature-should-not-be-used-in-code)
(def-feature :concurrent   :feature-should-not-be-used-in-code)
(def-feature :data-general :feature-should-not-be-used-in-code)
(def-feature :decstation   :feature-should-not-be-used-in-code)
(def-feature :dgux         :feature-should-not-be-used-in-code)
(def-feature :hp9000s300   :feature-should-not-be-used-in-code)
(def-feature :hp9000s800   :feature-should-not-be-used-in-code)
(def-feature :i386         :feature-should-not-be-used-in-code)
(def-feature :intel-386    :feature-should-not-be-used-in-code)
(def-feature :mac          :feature-should-not-be-used-in-code)
(def-feature :mac-os       :feature-should-not-be-used-in-code)
(def-feature :masscomp     :feature-should-not-be-used-in-code)
(def-feature :mc68000      :feature-should-not-be-used-in-code)
(def-feature :mips         :feature-should-not-be-used-in-code)
(def-feature :mips-risc    :feature-should-not-be-used-in-code)
(def-feature :next         :feature-should-not-be-used-in-code)
(def-feature :pa           :feature-should-not-be-used-in-code)
(def-feature :sequent      :feature-should-not-be-used-in-code)
(def-feature :sun3         :feature-should-not-be-used-in-code)
(def-feature :ultrix       :feature-should-not-be-used-in-code)
(def-feature :vax          :feature-should-not-be-used-in-code)
(def-feature :vms          :feature-should-not-be-used-in-code)
(def-feature :vanilla-vms  :feature-should-not-be-used-in-code)


;;; The `vanilla' features are used to describe a platform which has generic
;;; aspects.  It has not truly been supported in years, but some uses of it
;;; remain in the code, and in theory we might want to resurrect this ability
;;; to run on a generic Lisp system.  -jv, 8/3/07

(def-feature :vanilla)
(def-feature :vanilla-areas)
(def-feature :vanilla-numbers)
(def-feature :vanilla-time)
(def-feature :vanilla-unix)


;;; ... however, there are a couple which we had at one time, which are
;;; completely unused now; and, unless, someone finds something useful
;;; for them, they should not be used.
(def-feature :vanilla-characters :feature-should-not-be-used-in-code)
(def-feature :vanilla-memory     :feature-should-not-be-used-in-code)





;;;; Features Used To Indicate Window System



;; jh, 6/14/94.  I hope this is the appropriate place to add to features lore.
;; The feature :x11-unix is introduced by LOAD and is always present in code
;; that will be translated into distribution images, even if the destination
;; platform does not use X windows or does not have a UNIX operating system.
;; Currently, the only such platform is Windows.  The issue is complicated by
;; the fact that Gensym has written a suite of X emulation functions for the
;; Windows platform, so pushing this token onto *features* can still be seen as
;; appropriate (but for the name "x11-unix" itself).  Despite the emulation,
;; however, some code on the Lisp side may have to be modified to refrain from
;; doing X-like things.  (See x11-display-specified-p in PLATFORMS, for
;; example).  Such modification should be done using the global variables
;; g2-machine-type or g2-operating system as appropriate.

(def-feature :x11-unix)


(def-feature :color)





;;;; Features Used by Font Facilities



;;; The feature `:Font-Files' is used in front of stuff that we would make
;;; non-development if we had to load (.gf) font files again, as we did in G2
;;; 3.0.  This stuff works fine as far as I know, but we never need to use it,
;;; except in the production or manipulation of font data during development,
;;; so we don't need to include the code in production.  (MHD 7/26/96)

(def-feature :font-files)

#+development
(pushnew :font-files *features*)





;;;; Java-export-facilities - Feature for the Java Export Feature


;;; [SEE BELOW FOR AN IMPORTANT UPDATE!]
;;; The feature `Java-export-facilities' enables or disables the Java export
;;; facility, which was developed in 1997 and 1998, and has since been
;;; abandoned.  As best we can determine, it was not reachable, at least through
;;; documented means, in G2 5.1.  It was never released, though it was partially
;;; demoed at the GUS conference in 1998. It is not likely to be resurrected.
;;; If this feature is on, the code for it will be included in G2.  Most of the
;;; code is in JAVA1, JAVA2, and JAVA3; these modules are included in G2 if this
;;; feature is on (but note: SYSTEMS is loaded ahead of FEATURES, so the feature
;;; must be pushed earlier if it's to work).  Calls to those modules are
;;; scattered in about a dozen places elsewhere, specificially in RPC-COMMON3,
;;; PARSE, FRAMES1, and EDIT1, guarded by this feature.

(def-feature :java-export-facilities)

;; Switched off as of G2 7.0p0, the main line under development. (MHD 7/11/02)

;;; IMPORTANT UPDATE (MHD 3/6/03): switched back on: switching it off broke
;;; download interfaces per bug HQ-4517594 "Javalink: downloadinterfaces fails
;;; against G2 70r0".
;;;
;;; To switch it on now, note: we (1) added this form:
;;;
;;;   (pushnew :java-export-facilities *features*)
;;;
;;; to lisp/systems.lisp, above its first use there; (2) placed java1.lisp,
;;; java2.lisp, and java3.lisp back in in their proper place in the file
;;; lisp/files-in-order.lisp; (3) recompiled everything in Lisp (for testing).





;;;; res-g2-facilities - Feature for the Java Export Feature


;;; The feature `res-g2-facilities' enables or disables the features in RES-G2,
;;; which are basically to provide G2-side Windows resource file facilities for
;;; the NTW ("New TW", using Bristol and Win32) project, which was cancelled for
;;; the TW2 (using Java) project around end of 1996.

(def-feature :res-g2-facilities)

;; Switched off as of G2 7.0p0, the main line under development. (MHD 7/25/02)





;;;; gesture-definition-facilities - Obsolete NTW Stuff


;;; The feature `gesture-definition-facilities' enables or disables the features
;;; in events-g2 for handling UI gestures in the context of the NTW ("New TW",
;;; using Bristol and Win32) project, which was cancelled for the TW2 (using
;;; Java) project around end of 1996.

(def-feature :gesture-definition-facilities)

;; Switched off for G2 7.0a2, the main line under development. (MHD 11/18/02)





;;;; Setup Misc Features




(def-feature :mhd-special-purpose)        ; See MHD

(def-feature :echo-dialog-send)  ; jv, 4/11/05





;;;; Features Used for Coding Gimicks



;;; `unused' is a feature used to comment out blocks of
;;; code that while interesting to read, write, or dream
;;; about are not actually used in the sources.  Such
;;; code should be viewed with suspicion since it is
;;; likely not in synch with the current code.

;;; Such code should be deleted, or commented if you
;;; notice that it is incompatible with the current code.

(def-feature :unused)



;;; `:obsolete' is a feature used to comment out blocks
;;; of code that have been replaced by some other design
;;; or implementation.  Such code is sometime left behind
;;; to give historians an idea of how things used to work.

;;; It is common to use this when bridging to the new code.

;;; Generally such code maybe deleted if you think it no
;;; longer serves any useful function.

(def-feature :obsolete)









;;;; Features Used by Individual Developers.


;;; The following features, `:bhyde' for example, should appear in
;;; sources only within an individual's sandbox to guard code an
;;; individual developer want's included as he works on the
;;; product.  All these are guarded with #+development so warnings
;;; will be generated if they are checked in by mistake.  Things
;;; are more memorable and predictable if these are identical to
;;; your unix login name.

#+development
(def-feature :bhyde)

#+development
(def-feature :fmw)

#+development
(def-feature :ddm)





;;; The *features* entry `:Toolkit-Development' was used during implementation
;;; to guard the code that implemented propritary mode.  This code is now
;;; finished and all uses of this have been removed from the code.

(def-feature :toolkit-development :feature-being-phased-out)




;;; The *features* entry `:ab-ps-error-handler' is used to disable a body
;;; of code that was intended to implement an postscript error handler
;;; within print jobs.

(def-feature :ab-ps-error-handler)


;;; The feature `:loop' is pushed on the features list by our
;;; Loop implemenation.  It is not used in code.

(def-feature :loop :feature-should-not-be-used-in-code)



;;; SAFER-SUBSTITUTION-MACROS


;;; The *features* entry `:SAFER-SUBSTITUTION-MACROS' enables a a more fastidous
;;; versions of {def,defun}-substitution-macro.  This feature is not currently
;;; enabled since it exposes a huge number of oportunities.  To enable push it
;;; into *features* and recompile glbasics, and the modules your interested in.

(def-feature :SAFER-SUBSTITUTION-MACROS)

;; (pushnew :SAFER-SUBSTITUTION-MACROS *features*)


;;; The *features* entry `:pre-g2-v5-licensing' was used to comment out the
;;; code that implemented the licensing of G2 prior to version 5.0.  This
;;; code was left visible for historians.

;;; Note that code under this feature should not be removed.  The
;;; old licensing was very subtle and complex and the implementation
;;; was often the ONLY way to figure out exactly what the spec might
;;; have been.

;; (pushnew :pre-g2-v5-licensing *features*)

(def-feature :pre-g2-v5-licensing)


;;; The feature `:runtime-functionality-without-a-license' is used to compile
;;; G2 images for China that have runtime functionality independent of
;;; any license.

(def-feature :runtime-functionality-without-a-license)
;(pushnew :runtime-functionality-without-a-license *features*)


(def-feature :allow-icp-trace-for-gsi)


;;;; Old Evaluator Phaseout




;;; The feature old-evaluators will begin to be used to mark those pieces of
;;; software which will be removed when the last of the old evaluator uses is
;;; gone.  -jra 8/27/91

;;; Removing the switch to see how well it goes.  -jra 10/19/91

;(pushnew :old-evaluators *features*)




(def-feature :trace-invocations)

;(pushnew :trace-invocations *features*)




;;;; Slavic-bitmaps, Hebrew-bitmaps, Thai-bitmaps

;;; Slavic-bitmaps, hebrew-bitmaps, and thai-bitmaps are features to determine
;;; if the bitmap data in the Slavic, Hebrew, and Thai font files, respectively,
;;; will be stored in these fonts.  This information is currently redundant, and
;;; uses space unnecessarily.  The bitmaps are not tuned to look in any way
;;; different than what would be derived from the associated outline font.
;;; Finally, for the Slavic and Hebrew cases the fonts are built into the G2/TW
;;; images, so there is improvement in availability, except for Thai. The only
;;; advantage then is a small amount of speed if the exact size is used.  And
;;; you could go back to just using bitmap fonts, not using the outline, if you
;;; had to.

(def-feature :slavic-bitmaps)
(def-feature :hebrew-bitmaps)
(def-feature :thai-bitmaps)





;;;; Rework *ReadTable* to Check Features


;; This section is entirely a comment.  To use it select the
;; comment body, and then compile that region.

#|
(defun eval-feature-predicate (feature-predicate)
  (let (expr-head)
    (cond
      ((symbolp feature-predicate)
       (if (member feature-predicate *features* :test #'string=)
           t nil))
      ((and (consp feature-predicate)
            (symbolp (setf expr-head (car feature-predicate)))
            (member (setf expr-head (symbol-name expr-head))
                    '("AND" "OR" "NOT") :test #'string=))
       (cond
         ((string= "AND" expr-head)
          (dolist (subpredicate (cdr feature-predicate) t)
            (unless (eval-feature-predicate subpredicate)
              (return nil))))
         ((string= "OR" expr-head)
          (dolist (subpredicate (cdr feature-predicate) nil)
            (when (eval-feature-predicate subpredicate)
              (return t))))
         ((string= "NOT" expr-head)
          ;; No check of length = 2
          (not (eval-feature-predicate (second feature-predicate))))))
      (t
       (error "Malformed Feature Test: ~S" feature-predicate)))))


(defparameter collected-feature-predicates ())

(defun sharp-plus-or-minus-reader-for-ab (stream character arg)
  (declare (ignore arg))
  (let* ((feature-predicate (let ((*read-suppress* nil))
                              (read stream t nil t)))
         (flag (eval-feature-predicate feature-predicate)))
    (unless (check-feature-use-in-code feature-predicate)
      (warn "Read time feature checking encountered unexpected predicate: ~S"
            feature-predicate))
    (pushnew
     (labels ((n (x) (cond
                      ((null x) x)
                      ((symbolp x)
                       (intern (symbol-name x) (symbol-package :keyword)))
                      (t
                       (cons (n (car x)) (n (cdr x)))))))
            (n feature-predicate))
     collected-feature-predicates
     :test #'equal)
    (let ((*read-suppress* (or *read-suppress*
                               (if (eql #\- character)
                                   flag
                                   (not flag)))))
      (cond
        (*read-suppress*
         (read stream t nil t)
         (values))
        (t
         (read stream t nil t))))))


(defun check-feature-use-in-code (feature-predicate)
  (cond
    ((symbolp feature-predicate)
     (feature-is-allowed-in-code feature-predicate))
    ((consp feature-predicate)
     (dolist (subpredicate (cdr feature-predicate) t)
       (unless (check-feature-use-in-code subpredicate)
         (return nil))))
    (t nil)))

(defun feature-is-allowed-in-code (feature-symbol)
  (let ((feature-predicate?
            (feature-predicate
                (find-symbol (symbol-name feature-symbol)
                             (symbol-package :keyword)))))
    (and feature-predicate?
         (not (feature-predicate-requires-feature
               :feature-being-phased-out
               feature-predicate?))
         (not (feature-predicate-requires-feature
               :feature-should-not-be-used-in-code
               feature-predicate?)))))


(defun feature-predicate-requires-feature (feature feature-predicate)
  (cond
    ((symbolp feature-predicate)
     (string= feature feature-predicate))
    ((consp feature-predicate)
     (case (car feature-predicate)
       (and
        (dolist (subpredicate feature-predicate nil)
          (when (feature-predicate-requires-feature feature subpredicate)
            (return t))))
       (or
        nil)
       (not
        nil)))))



(defun install-my-readtable ()
  (setf *readtable* (copy-readtable nil))
  (set-dispatch-macro-character #\# #\- 'sharp-plus-or-minus-reader-for-ab)
  (set-dispatch-macro-character #\# #\+ 'sharp-plus-or-minus-reader-for-ab))

(defun deinstall-my-readtable ()
  (setf *readtable* (copy-readtable nil)))


|#


;; The following are just to record what features are there from scratch,
;; and what features are pushed onto the list by us.  - jv, 5/12/99

#+development
(defconstant features-in-liquid50-at-startup
  '(:clos :lep :find-callers :tcp-sockets :liquid :egc :multitasking :dbcs
    :shared-libraries :jeida-nihongo :monitoring :pqc :compiler :loop
    :ieee-floating-point :multio :sun-os :sparc :sun :unix :sunos :solaris
    :solaris2 :svr4 :lucid :lcl :common-lisp :lcl3.0 :lcl4.0 :lcl4.1 :lcl4.2
    :lcl5.0))

#+development
(defconstant features-we-push-liquid-solaris-Aug-4-2007
  '(:clear-text-saving-is-initially-enabled
    :clear-text-loading-is-initially-enabled :c-streams :ascii
    :clear-text
    :gensym-typed-arithmetic :font-files :no-lucid-temporary-areas
    :using-egc :x11-unix :lucid-4 :lucid-3 :sun4 :development))

#+development
(defconstant features-in-Allegro-CL-Professional-Edition-5.0.1-Linux/X86
  '(:acl-socket :multiprocessing :flavors :little-endian :gsgc :clos :compiler
    :use-structs-in-compiler :dynload :dlfcn :unix :linux :redhat5 :linux86 :x86
    :verify-car-cdr :ieee :ieee-floating-point :conforming-ieee :common-lisp
    :ansi-cl :draft-ansi-cl-2 :x3j13 :allegro :excl :franz-inc :allegro-version>=
    :dynload-acl-library :allegro-v5.0.1 :allegro-cl-professional))

#+development
(defconstant features-in-Allegro-CL-Free-Express-Edition-8.0-Windows
  '(:allegro-cl-trial :allegro :franz-inc :allegro-v8.0 :excl
    :x86 :mswindows :microsoft :microsoft-32 :little-endian
    :allegro-version>= :allegro-version= :acl-socket :dynload-acl-library :ipv6
    :common-lisp :ansi-cl :draft-ansi-cl-2 :clos :x3j13
    :ide :profiler :compiler :multiprocessing :common-graphics :flavors :gsgc
    :hiper-socket :use-structs-in-compiler :verify-car-cdr :dynload :dlwin
    :encapsulating-efs :relative-package-names :module-versions
    :ieee :ieee-floating-point :conforming-ieee :ics
    :new-environments :os-threads :process7 :symbol-value-vector
    :ssl-support))

;; -- Added for ACL. -mhd, 6/17/00.  Added ACL 8.0 Windows Trial, jv, 7/19/07


#+development
(defconstant features-in-LispWorks-4-2-0-win32
  '(:lispworks4 :lispworks4.2 :harlequin-pc-lisp :new-pc-compiler
    :float :supports-cons-blocks
    ;; above in 4.2 only; below shared with 5.0
    :lispworks :common-ffi :clos :ansi-cl :common-lisp :harlequin-common-lisp
    :common-lispworks :win32 :little-endian :iapx386 :unicode :latin-1
    :capi-toolkit :capi :dbcs-env :ieee-floating-point :class-shake-using-gates
    :common-defsystem :dbcs :reverse :compile-reverse #+lispworks harp::pc386
    :lw-editor :byte-instructions :compiler :new-patch-system))

#+development
(defconstant features-in-LispWorks-5-0-2-win32
  '(:lispworks5 :lispworks5.0 :lispworks-32bit :lispworks-x86 :x86 :mswindows
    :fli-register-module :no-function-register :no-leading-underscore :nts
    :have-shared-library :mapped-image :shallow-binding :x11-motif-no-libraries
    #+lispworks harp::pc386-x
    ;; above in 5.0 only; below shared with 4.2
    :lispworks :common-ffi :clos :ansi-cl :common-lisp :harlequin-common-lisp
    :common-lispworks :win32 :little-endian :iapx386 :unicode :latin-1
    :capi-toolkit :capi :dbcs-env :ieee-floating-point :class-shake-using-gates
    :common-defsystem :dbcs :reverse :compile-reverse #+lispworks harp::pc386
    :lw-editor :byte-instructions :compiler :new-patch-system))

;; -- Added for Lispworks.  Re-ordered the features very subjectively, roughly
;;    in order of how useful they seem.  -jv, 7/17/07

#+development
(defconstant features-in-sbcl-at-startup
  '(:sb-after-xc-core :sb-core-compression :ansi-cl :common-lisp :sbcl :sb-doc
    :sb-test :sb-ldb :sb-package-locks :sb-unicode :sb-eval
    :sb-source-locations :ieee-floating-point :os-provides-putwc :little-endian
    :multiply-high-vops :memory-barrier-vops :inline-constants :float-eql-vops
    :complex-float-vops :cycle-counter :alien-callbacks
    :stack-allocatable-fixed-objects :stack-allocatable-lists
    :stack-allocatable-vectors :stack-allocatable-closures :raw-instance-init-vops
    :unwind-to-frame-and-call-vop :compare-and-swap-vops :linkage-table
    :c-stack-is-control-stack :stack-grows-downward-not-upward :gencgc
    :sb-dynamic-core :dfs-are-windows-handles :sb-gc-safepoint :os-provided-dlopen
    :sb-foreign-thread :sb-thread :sb-futex :win32 :x86-64))

;; The :properties-api-based-on-hash-tables allows usage of hash-tables  instead of
;; plists as default properties-api engine. You should change nil to t if you 
;; want to allow this feature. Note: RTL's hash-tables inmplementation
;; has a deep undetermined bug which breaks hash-tables consistance so hash-tables
;; can't be used on translated sources so far.

(def-feature :properties-api-based-on-hash-tables)


;; The following operations used to be at the top of loop.lisp because it was
;; among the first to be loaded.  But this file gets loaded first, and it's
;; FEATURES, which is where this belongs anyway!!!  -jv, 12/5/07

#-(and chestnut-3 chestnut-trans)
(progn
  #+no-macros
  (pushnew :no-macros *features*)
  #-no-macros
  (setq *features* (delete :no-macros *features*))

  #+development
  (pushnew :development *features*)
  #-development
  (setq *features* (delete :development *features*))

  #+distribution
  (pushnew :distribution *features*)
  #-distribution
  (setq *features* (delete :distribution *features*)))

;;; SymScale switch -- Chun Tian (binghe), 2009/8/12
(def-feature :SymScale)

(def-feature :mtg2)

;;; Some new features added since G2 2015 and late G2 2011
;;; -- Chun Tian (binghe_, 2016/06/04

(def-feature :subblocks-v2)
(def-feature :connections-v2)
(def-feature :relation-instances-v2)
(def-feature :relation-instances-v2.0)
(def-feature :relation-instances-v2.1)
(def-feature :procedure-invocations-using-binary-tree)
(def-feature :evaluation-types-using-binary-tree)


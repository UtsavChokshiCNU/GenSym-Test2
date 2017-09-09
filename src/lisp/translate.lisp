;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module TRANSLATE

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; Mark Staknis, Jim Allard, and John Hodgkinson


;;;; Extra Side-effect-free Declarations

;;; There is a bug in Chestnut in that they have not declared "*" to be a
;;; side-effect free function.  We provide the declaration ourselves here.  -jra
;;; 3/20/91

(declare-side-effect-free-function *)

#+chestnut
(declare-side-effect-free-function trun:m_car)
#+chestnut-3
(declare-side-effect-free-function trun:%m-car)

#+chestnut
(declare-side-effect-free-function trun:m_cdr)
#+chestnut-3
(declare-side-effect-free-function trun:%m-cdr)



;;;; Version-independent File Processing Functions

;; jh, 1/18/93.  For the new 3.1 Chestnut rev.

(defmacro chestnut-map-symbol-name (original-symbol new-symbol)
  (feature-case
    (:chestnut
      (with-package-specific-symbols (trans |::| map-symbol-name)
        `(map-symbol-name ,original-symbol ,new-symbol)))
    (:chestnut-3
      (with-package-specific-symbols (trans |::| translator-symbol-name)
        `(setf (translator-symbol-name ,original-symbol)
               (symbol-name ,new-symbol))))
    (t (error "CHESTNUT-MAP-SYMBOL-NAME: ~
               can't locate a feature for Chestnut"))))


(defmacro chestnut-map-keyword (original-symbol)
  (feature-case
    (:chestnut
      (with-package-specific-symbols (trans |::| map-keyword)
        `(map-keyword ,original-symbol)))
    (:chestnut-3
      nil) ;already uniquified, according to Chestnut 3.1 User Guide, p 92
    (t (error "CHESTNUT-MAP-KEYWORD: ~
               can't locate a feature for Chestnut"))))

(defmacro chestnut-clear-user-tables ()
  (feature-case
    (:chestnut
      (with-package-specific-symbols (trans |::| clear-user-tables)
        `(clear-user-tables)))
    (t (error "CHESTNUT-CLEAR-USER-TABLES: ~
               can't locate a feature for Chestnut"))))

(defmacro chestnut-dump-user-tables ()
  (feature-case
    (:chestnut
      (with-package-specific-symbols (trans |::| dump-user-tables)
        `(dump-user-tables)))
    (t (error "CHESTNUT-DUMP-USER-TABLES: ~
               can't locate a feature for Chestnut"))))

(defmacro chestnut-write-header-files (system)
  (feature-case
   (:chestnut-3
    (with-package-specific-symbols (trans |::| write-header-files)
      `(write-header-files
        :default-pathname
        (make-system-pathname ,system 'header "c"
                              :newest nil
                              'system-lisp-source-files 'binary))))
   (t (error "CHESTNUT-write-header-files: ~
              can't locate a feature for Chestnut"))))

#+(and chestnut-3 (not chestnut-trans))
(defparameter *chestnut-header-files*
  '("userfuns" "userstrs" "user" #+SymScale "uspecial"))

#+(and chestnut-3 (not chestnut-trans))
(defun chestnut-write-header-files-if-modified (system)
  (let ((file-class 'system-lisp-source-files))
    (macrolet (#+lispworks
               (do-headers (() &body body)
                 `(dolist (name *chestnut-header-files*)
                    (let* ((temp-name (intern (format nil "~a-TEMP" name)))
                           (temp-pathname
                            (make-system-pathname system temp-name "h" :newest nil file-class 'binary))
                           (destination-pathname
                            (make-system-pathname system name "h" :newest nil file-class 'binary))
                           (old-translation-exists? (probe-file destination-pathname)))
                      ,@body))))
      #+lispworks
      (do-headers ()
        (when old-translation-exists?
          (rename-file destination-pathname temp-pathname)))
      ;; call `chestnut-write-header-files' once.
      (chestnut-write-header-files system)
      #+lispworks
      (do-headers ()
        (when old-translation-exists?
          (cond ((file-diff-p destination-pathname temp-pathname)
                 ;; if there're any differences, old files are useless.
                 (delete-file temp-pathname))
                (t
                 ;; or, recover old files
                 (delete-file destination-pathname)
                 (rename-file temp-pathname destination-pathname))))))))

(defmacro chestnut-prep-file (source-pathname?)
  (feature-case
    (:chestnut
      (with-package-specific-symbols (trans |::| prep-file)
        `(prep-file ,source-pathname?)))
    (:chestnut-3
      (with-package-specific-symbols (trans |::| prepare-file)
        `(prepare-file ,source-pathname? :print nil)))
    (t (error "CHESTNUT-PREP-FILE: ~
               can't locate a feature for Chestnut"))))


;; jh, 3/22/93.  Added modules-to-translate-verbosely to help track down
;; enigmatic translator warnings.


(defvar modules-to-translate-verbosely
  `(
    ))

(defmacro chestnut-translate-file
          (source-pathname
           c-destination-pathname
           e-or-h-destination-pathname
           top-destination-pathname?)
  (feature-case
    (:chestnut
      (with-package-specific-symbols (trans |::| translate-file)
        `(translate-file
           ,source-pathname
           ,c-destination-pathname
           ,e-or-h-destination-pathname
           ,top-destination-pathname?)))
    (:chestnut-3
      ;; Lacks a ".top" file, so the corresponding arg is omitted.
      (with-package-specific-symbols (trans |::| translate-file)
        (avoiding-variable-capture (source-pathname)
          `(translate-file
            ,source-pathname
            :output-file ,c-destination-pathname
            :h-file ,e-or-h-destination-pathname
            :print (member (pathname-name ,source-pathname)
                    modules-to-translate-verbosely
                    :test #'equalp)))))
    (t (error "CHESTNUT-TRANSLATE-FILE: ~
               can't locate a feature for Chestnut"))))




;;; The macro `chestnut-write-main-file' will call Chestnut 3.2's emitter for a
;;; main file, hiding its weird argument format.

(defmacro chestnut-write-main-file (main-pathname top-level-function-symbol?)
  (feature-case
    (:chestnut-3
      (with-package-specific-symbols (trans |:| write-main-file)
        `(let ((pathname ,main-pathname)
               (top-level? ,top-level-function-symbol?))
           (if top-level?
               (write-main-file :pathname pathname :user-toplevel top-level?)
               (write-main-file :pathname pathname)))))
    (t
      (error
        "CHESTNUT-WRITE-MAIN-FILE: not available given current *features*."))))





;;;; Abstractions for Chestnut Internals

;; jh, 1/28/93.  We don't know enough about Chestnut 3.1 to do incremental
;; compiles, so the following abstraction currently only works in the old
;; version, rev 1.7.

(defvar dummy-place-for-chestnut-internals nil)

(defmacro chestnut-top-level-functions ()
  #+chestnut `trans::*top-level-functions*
  #-chestnut `dummy-place-for-chestnut-internals
  )

(defmacro chestnut-function-symbols ()
  #+chestnut `trans::*function-symbols*
  #-chestnut `dummy-place-for-chestnut-internals
  )

(defmacro chestnut-proclaimed-specials ()
  #+chestnut `trans::*proclaimed-specials*
  #-chestnut `dummy-place-for-chestnut-internals
  )

(defmacro chestnut-user-function-table ()
  #+chestnut `trans::*user-function-table*
  #-chestnut `dummy-place-for-chestnut-internals
  )

(defmacro chestnut-symbol-initialization-functions ()
  #+chestnut `trans::*symbol-initialization-functions*
  #-chestnut 0
  )

(defmacro chestnut-conflicting-symbols ()
  #+chestnut `trans::*conflicting-symbols*
  #-chestnut `dummy-place-for-chestnut-internals
  )

(defmacro chestnut-quoted-symbols ()
  #+chestnut `trans::*quoted-symbols*
  #-chestnut `dummy-place-for-chestnut-internals
  )

(defmacro chestnut-global-symbols ()
  #+chestnut `trans::*global-symbols*
  #-chestnut `dummy-place-for-chestnut-internals
  )

(defmacro chestnut-keywords ()
  #+chestnut `trans::*keywords*
  #-chestnut `dummy-place-for-chestnut-internals
  )

(defmacro chestnut-kernel-functions-called ()
  #+chestnut `trans::*kernel-functions-called*
  #-chestnut `dummy-place-for-chestnut-internals
  )

(defmacro chestnut-kernel-macros-called ()
  #+chestnut `trans::*kernel-macros-called*
  #-chestnut `dummy-place-for-chestnut-internals
  )

(defmacro chestnut-clear-existing-user-tables-without-prompting ()
  #+chestnut `trans::*clear-existing-user-tables-without-prompting*
  #-chestnut `dummy-place-for-chestnut-internals
  )

;;; The only package-qualified symbols after this point should be official
;;; Chestnut translator switches.  We cannot abstract these because they vary
;;; widely between releases



;;;; Include File Generation

;;; The following are used to generate include files for the Chestnut makefiles.
;;; Files are read into a Makefile by beginning a line with the word "include"
;;; followed by the file name.  In this case the include file will define a local
;;; variable in the Makefile which is the list of all of the modules which should
;;; be linked in with the given system.  For example, the include file for tw
;;; should follow this pattern,
;;;
;;; files = load.o \
;;;        bootstrap.o \
;;;        loop.o \
;;;     basics.o ....
;;;
;;; Two phases are necessary in order to get the final makefile for a platform.
;;; First the skeleton makefile which contains the rules for compilation and
;;; ifdefs for all of the platform specific compiler macros is run through
;;; cpp, the C preprocessor, to generate a makefile for the specific platform.
;;; This makefile then includes the include file to get the current list
;;; of modules for the system.



#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun generate-list-of-core-modules (system)
  (loop for item in (all-lisp-source-file-symbols system t)
        when (include-for-load-p item
                              'system-lisp-source-files
                              system)
        collect item))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun generate-list-of-updated-modules (system)
  (loop for item in modules-compiled
        when (include-for-load-p item
                              'system-lisp-source-files
                              system)
        collect item))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun test-top-level-module (item top-level-function)
  (let ((item-string (format nil "~(~a~).top" item)))
    (string= item-string (second top-level-function))))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun generate-list-of-top-level-modules (core-modules init-modules)
  (let ((modules (nconc (copy-list core-modules) (copy-list init-modules))))
    (loop for item in modules
          when (member item (chestnut-top-level-functions)
                       :test 'test-top-level-module)
          collect (intern (format nil "t_~a" item)))))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defparameter modules-to-add '(load
                               bootstrap
                               initsyms
                               toplevel
                               symbols))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun check-top-level-module (item module)
  (test-top-level-module module item))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun repair-utable-top-level-functions (modules)
  (loop for item in (chestnut-top-level-functions)
        when (member item modules :test 'check-top-level-module)
        collect item))


#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun repair-utable-function-symbols ()
  (loop for item in (chestnut-function-symbols)
        when (fboundp item)
        collect item))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun repair-utable-proclaimed-specials ()
  (loop for item in (chestnut-proclaimed-specials)
        when #+sbcl (sb-walker:var-globally-special-p item)
             #+lispworks (walker:variable-special-p item)
             #+lucid (sys::proclaimed-special-p item)
             #-(or sbcl lispworks lucid) (error "Unsupported implementation")
        collect item))
	
	
#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun test-car-eq (item list)
  (eq item (car list)))



#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun repair-utable-user-function-table (top-level-functions)
  (loop for item in (chestnut-user-function-table)
        when (or (fboundp (car item))
                 (member (car item)
                         top-level-functions
                         :test 'test-car-eq)
                 (equal (string<= "LEX" (car item)) 3)
                 (equal (string<= "TEXPAND" (car item)) 7)
                 (equal (string<= "INITSYMS-TOP-LEVEL" (car item)) 18))
        collect item))



#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun generate-list-of-init-modules ()
  (loop for i from 1 to (chestnut-symbol-initialization-functions)
        collect (intern (format nil "INIT~a" i))))



#+(and :chestnut (not :chestnut-trans)) ;Chestnut3.1
(defun generate-include-file-for-make (system)
  (let* ((core-modules (generate-list-of-core-modules system))
         (init-modules  (generate-list-of-init-modules))
         (top-level-modules
           (generate-list-of-top-level-modules core-modules modules-to-add))
         (list-of-modules (nconc (copy-list core-modules)
                                 (copy-list  init-modules)
                                 (copy-list top-level-modules)
                                 (copy-list modules-to-add)))
         (include-file-for-makefile
           (make-pathname :defaults
                          #+development
                          (local-chestnut-development-directory system)
                          #+distribution
                          (local-chestnut-dst-directory system)
                          :name (case system
                                  (telewindows "tw")
                                  (ab "g2")
                                  (t "inc"))
                          :type "mak")))
    (with-open-file (output-file include-file-for-makefile :direction :output)
      (dolist (module list-of-modules)
              (format output-file "~(~a~)~%" module)))))


#+(and :chestnut-3 (not :chestnut-trans)) ;Chestnut3.1
(defun chestnut-create-makefile ()
  (trans:write-makefile-file))



;;;; Symbol Printname Truncation

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(progn

(defparameter max-chestnut-symbol-length 256)

(defparameter expand-symbol-buffer
  (make-array 256 :element-type 'character :fill-pointer 0))

(defun append-string (string buffer)
  (dotimes (cnt (length string))
    (vector-push (char string cnt) buffer)))

(defvar char-mappings ; used to have only "* ?"
  (loop for (char mapping) in tutil::*non-alphanumeric-char-mappings*
        unless (char= char #\-)
          collect (cons char (string-upcase mapping))))

(defun expand-symbol (symbol)
  (let ((buffer expand-symbol-buffer)
        (sym-name (symbol-name symbol)))
    (setf (fill-pointer buffer) 0)
    (current-system-case
      (gsi
        (unless (get symbol 'gsi-api-symbol)
          (append-string "G2INT-" buffer))))
    (dotimes (pos (length sym-name))
      (let* ((char (char sym-name pos))
             (mapping (cdr (assoc char char-mappings))))
        (if mapping
            (append-string mapping buffer)
            (vector-push (char-upcase char) buffer))))
    buffer))

(defun generate-unique-symbol (expanded-symbol-buffer maximum-length)
  (let ((symbol-number 0)
        (ab-package (find-package "AB")))
    (setf (fill-pointer expanded-symbol-buffer)
          (current-system-case
            (gsi maximum-length)
            (t (- maximum-length 4))))
    (loop (multiple-value-bind (new-or-existing-symbol new?)
              (intern (current-system-case 
                        (gsi
                          (replace expanded-symbol-buffer
                                   (format nil "~3,'0d"
                                           symbol-number)
                                   :start1 2)
                           expanded-symbol-buffer)
                        (t
                          (format nil "F~3,'0d~a"
                                  symbol-number
                                  expanded-symbol-buffer)))
                      ab-package)
            (if new?
                (setq symbol-number (1+ symbol-number))
                (return new-or-existing-symbol)))))) ; end of loop

(defun load-symbol-map (map-symbols-file)
  (let ((*package* (find-package "AB")))
    (with-open-file (map-file map-symbols-file :direction :input)
      (loop as symbol = (read map-file nil nil)
            as truncated-symbol = (read map-file nil nil)
            until (or (null symbol)
                      (null truncated-symbol))
            do
        (chestnut-map-symbol-name symbol truncated-symbol)
        (setf (get symbol 'truncated-symbol) truncated-symbol)))))

(defun truncate-symbols (maximum-length system)
  (let ((mapfile-pathname (make-symbolmap-pathname system))
        (ab-package (find-package "AB")))
    (let ((*package* ab-package))
      (with-open-file (mapfile mapfile-pathname
                               :direction :output
                               :if-exists :supersede)
        (let ((alist nil))
          (do-symbols (symbol ab-package)
            (when (and (eq (symbol-package symbol) ab-package)
                       (plusp (length (symbol-name symbol))))
              (let* ((expanded-symbol-buffer (expand-symbol symbol))
                     (too-long-p (> (length expanded-symbol-buffer) maximum-length)))
                (when (current-system-case
                        (gsi t)
                        (t too-long-p))
                  (let ((truncated-symbol
                          (cond
                            ((get symbol 'gsi-api-symbol)
                             (when too-long-p
                               (format t "~&Warning: The GSI API symbol ~S is too long for VMS~%" symbol))
                             symbol)
                            ((current-system-case
                               (gsi (not too-long-p))
                               (t nil))
                             (intern expanded-symbol-buffer ab-package))
                            ((get symbol 'truncated-symbol))
                            (t
                             (setf (get symbol 'truncated-symbol)
                                   (generate-unique-symbol expanded-symbol-buffer maximum-length))))))
                    (chestnut-map-symbol-name symbol truncated-symbol)  ; line_checked
                    (when (get symbol 'truncated-symbol)
                      (push (cons symbol truncated-symbol) alist))))))) ; line_checked
          (setq alist (sort alist #'string< :key #'car))
          (loop for (symbol . truncated-symbol) in alist
                do (format mapfile " ~S ~5t~S ~%" symbol truncated-symbol)))))))

) ; progn 

;;;; Translator Switches

#+(and :chestnut (not :chestnut-trans))
(defun set-up-chestnut-defaults (system)
  (let ((gsi-functions   '(gsi-rd-text
                           gsi-stop-data
                           gsi-set-data
                           gsi-get-data
                           gsi-def-obj
                           gsi-accept-data
                           gsi-pause-ds
                           gsi-resume-ds
                           gsi-init-ds
                           gsi-shutdown-ds))
        (ab-package (find-package "AB")))
    (setq trans::*user-tables-pathname*
          (make-pathname :defaults
                         (local-source-directory system)
                         :name (case system
                                 (telewindows "tw-utables")
                                 (ab "g2-utables")
                                 (t "utables"))
                         :type "lisp"))
    (setq trans::*user-symbols-pathname*
          (make-pathname :defaults
                         #+development
                         (local-chestnut-development-directory system)
                         #+distribution
                         (local-chestnut-dst-directory system)
                         :name "symbols"
                         :type "h"))
    (setq trans::*user-macros-pathname*
          (make-pathname :defaults
                         #+development
                         (local-chestnut-development-directory system)
                         #+distribution
                         (local-chestnut-dst-directory system)
                         :name "trandefs"
                         :type "h"))
    (setq trans::*initial-symbols-pathname*
          (make-pathname :defaults
                         #+development
                         (local-chestnut-development-directory system)
                         #+distribution
                         (local-chestnut-dst-directory system)
                         :name "symbols"
                         :type "c"))
    (setq trans::*symbol-initialization-pathname*
          (make-pathname :defaults
                         #+development
                         (local-chestnut-development-directory system)
                         #+distribution
                         (local-chestnut-dst-directory system)
                         :name "initsyms"
                         :type "c"))
    (setq trans::*toplevel-pathname*
          (make-pathname :defaults
                         #+development
                         (local-chestnut-development-directory system)
                         #+distribution
                         (local-chestnut-dst-directory system)
                         :name "toplevel"
                         :type "c"))
    (setq trans::*include-toplevel* nil)
    (setq trans::*preserve-comments* nil)
    (setq trans::*constant-print-length* 0)
    (setq trans::*constant-print-level* 0)
    (setq trans::*include-function-symbols* nil)
    (setq trans::*include-global-symbols* nil)
    (setq trans::*protect-local-variables* nil)
    (setq trans::*aggressive-side-effects* t)
    (setq trans::*symbol-initialization-prefix* "init")
    (setq trans::*include-dates-in-headers* nil)
    (setq trans::*explicit-temps* t)
    (loop for item in gsi-functions do
      (chestnut-map-symbol-name
        (intern (format nil "~a" item) ab-package)
        (intern (format nil "G2-~a" item) ab-package)))
    (chestnut-map-symbol-name 'ab::abort 'ab::abort-g2)
    (chestnut-map-symbol-name 'ab::add 'ab::g2-add)
    (chestnut-map-symbol-name 'ab::result 'ab::g2-result)
    (chestnut-map-keyword :chestnut)
    (chestnut-map-keyword :return-value)
    (chestnut-map-keyword :symbol-value)))


;; Consider setting trans:*toplevel-location* to :separate

#+(and :chestnut-3 (not :chestnut-trans)) ;Chestnut3.1
(defun set-up-chestnut-defaults (system)
  (declare (ignore system)) ;see comment below about absent defaults
  (let ((gsi-functions   '(gsi-rd-text
                           gsi-stop-data
                           gsi-set-data
                           gsi-get-data
                           gsi-def-obj
                           gsi-accept-data
                           gsi-pause-ds
                           gsi-resume-ds
                           gsi-init-ds
                           gsi-shutdown-ds))
        (ab-package (find-package "AB")))

    (setq trans:*preserve-comments* nil)
    (setq trans:*include-dates-in-headers* nil)

    (setq trans:*constant-print-length* 0)
    (setq trans:*constant-print-level* 0)

    (setq trans:*function-symbols* nil)
    (setq trans:*special-symbols* nil)
    (setq trans:*initial-symbols* nil)
    (setq trans:*include-macro-expanders* nil)
    (setq trans:*avoid-comma-operator* t)
    (setq trans:*use-function-macros* nil)
    (setq trans:*maximum-c-string-constant-length* 175)
    (setq trans:*rtl-includes-gc-p* nil)

    (setq timpl::*copyright-notice*
          (format nil
                  "Copyright (c) 1986 - ~s Gensym Corporation.  All Rights Reserved."
                  year-at-compilation-time))

    (setq timpl::*compute-flow-p* t)
    (setq timpl::*do-coalescing-p* t)

    (setq timpl::*coalesce-variables-with-different-names-p* nil)
    (setq timpl::*coalesce-internal-variables-with-different-names-p* nil)
    (setq timpl::*coalesce-setf-variables-with-different-names-p* t)

    ;; jh, 4/2/96.  Both Chestnut and I want a foreign function that calls
    ;; the unadorned strcpy().
    (setq timpl::*allow-multiple-foreign-functions-per-c-name* t)

    ;; The following is a workaround for a false identification of a nonlocal
    ;; lexical jump from Rick.  This is supposed to eliminate calls to
    ;; ADD_BINDING.  -jra 12/21/93
    #-chestnut-3-2-7 (setq timpl::*enable-nonlocal-lexical-jumps-p* nil)

    ;; I believe that there is a bug in Chestnut's read-once-optimization code,
    ;; so I'm disabling it for the time being.  -jra 12/10/93
    #-chestnut-3-2-7 (setq timpl::*do-read-once-optimization* nil)
    ;; The following variable enables patch 35, which fixes a bug in the
    ;; AlphaOSF compiler.  -jra 4/14/94
    (setq trans:*integer-constants-are-long-p* t)

    (setq timpl::*enter-function-callback* "x_note_fn_call")
    (setq timpl::*enter-function-use-index-p* t)
    (setq timpl::*enter-function-use-file-index-p* t)
    (setq timpl::*enter-function-maximum-index-callback* "INIT_names")
    (setq timpl::*enter-function-callback-data* nil)
    (setq timpl::*enter-function-callback-file-data* nil)

    #+chestnut-3-2-7 (setq timpl::*generate-declarations-for-foreign-functions-p* nil)
    ;; Since we do not use EVAL.  -rh 5/3/96
    #+chestnut-3-2-7 (setq timpl::*include-declarations-at-runtime* nil)

    ;; Change default if-exists-action to make sure old files can be
    ;; overwritten directly. -- binghe, 2009/6/12
    (setq timpl::*if-exists-action* :supersede)

    (loop for item in gsi-functions do
      (chestnut-map-symbol-name
        (intern (format nil "~a" item) ab-package)
        (intern (format nil "G2-~a" item) ab-package)))
    (chestnut-map-symbol-name 'ab::abort 'ab::abort-g2)
    (chestnut-map-symbol-name 'ab::add 'ab::g2-add)
    (chestnut-map-symbol-name 'ab::result 'ab::g2-result)
    (chestnut-map-keyword :chestnut)
    (chestnut-map-keyword :chestnut-3)
    (chestnut-map-keyword :return-value)
    (chestnut-map-keyword :symbol-value)))



;;;; Incremental Translation

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun set-up-chestnut-incremental-translations (system)
  (let ((mapfile (make-symbolmap-pathname system)))
    (when (probe-file mapfile)
      (format t ";;; Loading symbol map file.")
      (load-symbol-map mapfile))))


#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun translate-module (system module)
  (prepare-or-translate-module system t nil module)
;  (prepare-or-translate-module system nil nil module)
  (prepare-or-translate-module system nil t module))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun dump-utable-header (outfile)
  (macrolet ((p (line) `(format outfile "~a~%" ,line)))
    (p ";;; Lisp-to-C Translator symbol and function tables (utables.lsp)")
    (p ";;; Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.")
    (p "(ab-lisp::in-package \"LUCID-RUNTIME-SUPPORT\")")
    (p "(ab-lisp::in-package \"TOOLS\")")
    (p "(ab-lisp::in-package \"KEYWORD\")")
    (p "(ab-lisp::in-package \"G2-DEFSTRUCT-STRUCTURE-NAME\")")
    (p "(ab-lisp::in-package \"AB\")")
    (p "(ab-lisp::in-package \"LISP\")")
    (p "(ab-lisp::in-package \"LUCID-COMMON-LISP\")")
    (p "(ab-lisp::in-package \"SYSTEM\")")
    (p "(ab-lisp::in-package \"TRANSLATOR\")")
    (p "(ab-lisp::in-package \"TRANSLATOR-RUNTIME\")")
    (p "(ab-lisp::in-package \"USER\")")
    (p "(ab-lisp::in-package \"TRANSLATOR\")"))
  (print '(init-utables) outfile))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun dump-conflicting-symbols (outfile)
  (format outfile "~a~%" "(SET-TABLE *CONFLICTING-SYMBOLS* ")
  (let ((*package* (find-package 'trans)))
    (dolist (item (chestnut-conflicting-symbols))
      (print item outfile)))
  (format outfile ")~%"))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun dump-user-function-table (outfile)
  (format outfile "~a~%" "(SET-TABLE *USER-FUNCTION-TABLE* ")
  (let ((*package* (find-package 'trans)))
    (dolist (item (repair-utable-user-function-table
                    (chestnut-top-level-functions)))
      (print item outfile)))
  (format outfile ")~%"))


#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun dump-proclaimed-specials (outfile)
  (format outfile "~a~%" "(SET-TABLE *PROCLAIMED-SPECIALS* ")
  (let ((*package* (find-package 'trans)))
    (dolist (item (repair-utable-proclaimed-specials))
      (print item outfile)))
  (format outfile ")~%"))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun dump-quoted-symbols (outfile)
  (format outfile "~a~%" "(SET-TABLE *QUOTED-SYMBOLS* ")
  (let ((*package* (find-package 'trans)))
    (dolist (item (chestnut-quoted-symbols))
      (print item outfile)))
  (format outfile ")~%"))



#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun dump-function-symbols (outfile)
  (format outfile "~a~%" "(SET-TABLE *FUNCTION-SYMBOLS* ")
  (let ((*package* (find-package 'trans)))
    (dolist (item (repair-utable-function-symbols))
      (print item outfile)))
  (format outfile ")~%"))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun map-unused-globals-to-dummy-globals ()
  (let ((dummy-number 0)
        (ab-package (find-package "AB")))
    (dolist (item (chestnut-global-symbols))
      (when (not (special-variable-p item))
        (chestnut-map-symbol-name item
                                  (intern
                                    (format nil
                                            "DUMMY-~d" dummy-number)
                                    ab-package))
        (setq dummy-number (1+ dummy-number))))))




#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun dump-global-symbols (outfile)
  (format outfile "~a~%" "(SET-TABLE *GLOBAL-SYMBOLS* ")
  (let ((*package* (find-package 'trans)))
    (dolist (item (chestnut-global-symbols))
      (print item  outfile)))
  (format outfile ")~%"))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun dump-keywords (outfile)
  (format outfile "~a~%" "(SET-TABLE *KEYWORDS* ")
    (let ((*package* (find-package 'trans)))
      (dolist (item (chestnut-keywords))
        (print item outfile)))
  (format outfile ")~%"))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun dump-top-level-functions (outfile system)
  (format outfile "~a~%" "(SET-TABLE *TOP-LEVEL-FUNCTIONS* ")
  (let ((*package* (find-package 'trans)))
    (dolist (item (repair-utable-top-level-functions
                    (nconc (copy-list '(load bootstrap))
                           (generate-list-of-core-modules system))))
      (print item outfile)))
  (format outfile ")~%"))


#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun dump-kernel-functions-called (outfile)
  (format outfile "~a~%" "(SET-TABLE *KERNEL-FUNCTIONS-CALLED* ")
  (let ((*package* (find-package 'trans)))
    (dolist (item (chestnut-kernel-functions-called))
      (print item outfile)))
  (format outfile ")~%"))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun dump-kernel-macros-called (outfile)
  (format outfile "~a~%" "(SET-TABLE *KERNEL-MACROS-CALLED* ")
  (let ((*package* (find-package 'trans)))
    (dolist (item (chestnut-kernel-macros-called))
      (print item outfile)))
  (format outfile ")~%"))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun dump-utable-end (outfile)
  (print "(end-utables)" outfile))


#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun make-utable-pathname (system)
  (make-pathname
   :defaults
   (local-source-directory system)
   :name
   (case system
     (ab "g2-utables")
     (telewindows "tw-utables")
     (gsi "gsi-utables"))
   :type "lisp"))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun make-symbolmap-pathname (system)
  (make-pathname
   :defaults
   (local-source-directory system)
   :name
   (case system
     (ab "g2-symbols")
     (telewindows "tw-symbols")
     (gsi "gsi-symbols"))
   :type "log"))

#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun prepare-user-tables (pathname system)
  (with-open-file (outfile  pathname :direction :output)
    (dump-utable-header outfile)
    (dump-conflicting-symbols outfile)
    (dump-user-function-table outfile)
    (dump-proclaimed-specials outfile)
    (dump-quoted-symbols outfile)
    (dump-function-symbols outfile)
    (dump-global-symbols outfile)
    (dump-keywords outfile)
    (dump-top-level-functions outfile system)
    (dump-kernel-functions-called outfile)
    (dump-kernel-macros-called outfile)
    (dump-utable-end outfile)))


;;;; Mnemonic Name Generator

;; Taken from code by Ben in ma:>bhyde>, 4/14/93.

;;; The function whip-up-a-mnemonic was designed to to generate short base file
;;; names given longer G2 module names.  The technique used is, I hope, easy for
;;; a developer to execute in his head when he wants to find a file and he
;;; already knows the module name.

;;; The algorithun runs in two steps, with the second step being optional.

;;; First we apply all the standard mnemonic rewrite rules.  For example
;;; "window" becomes "win" and "stack" becomes "stk".  There are a dozen of
;;; these rules.  Presumably a developer will learn these rules for the modules
;;; he often vists.

;;; The second step is applied only if the name is not already 6 characters
;;; long.  In this step we eliminate all the vowels and dashes, except the first
;;; and last ones.

;;; This works for all the current module names in G2.  Adding additional
;;; "standard mnemonics" to the list the-standard-mnemonics provides a way to
;;; work around additional problems.

;; The routine test-whip-up-a-mnemonic below will demonstrate that the names are
;; all short enough and that there are no duplicates, given the current module
;; list.

(defparameter-excluding-no-macros-gsi the-standard-mnemonics
  '(("area" "a")           ;; areas3-egc -> as3egc, areas -> as
    ("attr-export" "atrxpt")
    ("attribute" "attr")
    ("change-log" "chglog")
    ("character" "char")
    ("check" "chk")
    ("codes" "cds")
    ("ctest" "ct")
    ("command" "cmd")      ;; commands -> cmds         -fmw, 12/7/93
    ("rpc-common" "rpcmn") ;jh, 3/18/94
    ("common" "cmn")
    ("connect" "cnct")     ;; connection3a -> cnct3a
    ("dialogs" "dlogs")
    ("events" "evt")
    ("grammar" "gram")     ;; grammar8a    -> gram8a
    ("hash-tables" "hshtbl")
    ("images" "lspimg")
    ("interface" "if")     ;; interfaces   -> ifs
    ("licensing-users" "lsusr")
    ("lucid-server" "lsrvr")
    ("memory" "mem")
    ("module" "mod")
    ("native-" "natv")
    ("nupec" "np")         ;; g2ds-nupec  -> g2dsnp
    ("patch" "pat")
    ("platform" "ptfm")
    ("portable" "p")       ;; portable-threads -> pthreads
    ("postscript" "ps")
    ("priority-queues" "priqus")
    ("sysproc" "sp")
    ("proc" "pc")          ;; proc-debug -> pcdbg
    ("resources" "rsrcs")
    ("socket" "sock")
    ("service" "svc")      ;; web-services -> wbsvcs
    ("settings" "set")
    ("smbx" "sm")          ;; smbx-tcp -> smtcp
    ("stack" "stk")
    ("stubs" "sb")
    ("systems" "systm")
    ("transcode" "trnscd")
    ("translate" "tran")
    ("traversal" "trv")
    ("version" "vrn")
    ("view" "vw")
    ("win32" "w32")
    ("windows" "win")
    ("workstation" "wrkstn")
    ))

(defun-for-macro apply-standard-mnemonics-1 (char-list)
  (declare (eliminate-for-no-macros-gsi))
  (loop for (from  to) in the-standard-mnemonics
        as match? = (search from char-list)
        when match?
          do
          (return (concatenate 'list
                    (subseq char-list 0 match?)
                    to
                    (subseq char-list (min (length char-list)
                                           (+ match? (length from))))))
          finally
            (return char-list)))

(defun-for-macro apply-standard-mnemonics (symbol)
  (declare (eliminate-for-no-macros-gsi))
  (concatenate'string
    (loop for old = (string-downcase (symbol-name symbol))
                  then new
          for new = (apply-standard-mnemonics-1 old)
          when (equal new old)
            do
              (return new))))

#+(or development (and chestnut-3 (not chestnut-trans)))
(defun whip-up-a-mnemonic (symbol)
  (declare (eliminate-for-no-macros-gsi))
  (let* ((mnemonic (apply-standard-mnemonics symbol))
         (len (length mnemonic)))
    ;; Apply second rule only if necessary.
    (when (< 6 len)
      (setf mnemonic
            (concatenate'string
              (subseq mnemonic 0 1)
              (remove-if
                #'(lambda (c) (find c "aeiou-"))
                (subseq mnemonic 1 (1- len)))
              (subseq mnemonic (1- len)))))
    (intern (string-upcase mnemonic))))




#+development
(defun apply-standard-mnemonics-to-string (downcased-string)
  (declare (eliminate-for-no-macros-gsi))
  (concatenate 'string
               (loop for old = downcased-string then new
                     as new = (apply-standard-mnemonics-1 old)
                     when (equal new old) return new)))

#+development
(defun alt-apply-standard-mnemonics (string-or-symbol)
  (declare (eliminate-for-no-macros-gsi))
  (apply-standard-mnemonics-to-string
    (if (stringp string-or-symbol)
        string-or-symbol
        (string-downcase (symbol-name string-or-symbol)))))

#+development
(defun whip-up-a-mnemonic-string (symbol)
  (declare (eliminate-for-no-macros-gsi))
  (let* ((mnemonic (apply-standard-mnemonics symbol))
         (len (length mnemonic)))
    ;; Apply second rule only if necessary.
    (when (< 6 len)
      (setf mnemonic
            (concatenate 'string
                         (subseq mnemonic 0 1)
                         (remove-if
                           #'(lambda (c) (find c "aeiou-"))
                           (subseq mnemonic 1 (1- len)))
                         (subseq mnemonic (1- len)))))
    mnemonic))

#+development
(defun alt-whip-up-a-mnemonic (symbol)
  (declare (eliminate-for-no-macros-gsi))
  (intern (string-upcase (whip-up-a-mnemonic-string symbol))))



#+development
(defun generate-c-files-in-order (system &optional (output-file-name nil))
  (macrolet ((to-output (filename &body body)
               `(if ,filename
                    (with-open-file (*standard-output* ,filename :direction :output)
                      ,@body)
                    (progn ,@body))))
    (to-output
      output-file-name
      (loop for module-name in (system-modules system) do
        (format t "~A.c~%"
                (whip-up-a-mnemonic-string module-name))))))



;;;; Slot names

#+development
(defvar slotnames-list '())

#+development
(defun car-or-itself (symbol-or-list)
  (if (symbolp symbol-or-list)
      symbol-or-list
      (car symbol-or-list)))

#+development
(defun collect-slotnames (symbol value)
  (push (list* symbol "G2 type name"
               (mapcar #'car-or-itself value))
        slotnames-list))

#+(and lucid development)
(defun make-slotnames ()
  (let ((slotnames-list '())
        (*print-level* 30)
        (*print-length* 1000)
        (lcl:*debug-print-level* 30)
        (lcl:*debug-print-length* 1000))
    (map-over-global-property
      'DEF-STRUCTURE-SLOT-DESCRIPTIONS
      #'collect-slotnames)
    (write slotnames-list :pretty t :circle nil)
    (values)))







;;;; Testing Mnemonic Filenames


;;; Testing Domain

;;; `Collect-all-module-names' will make an attempt at learning the
;;; names of every module known to man.  Load time conditionals in
;;; the declare-system forms make this hard.

#+development
(defun collect-all-module-names ()
  (mapcar #'first all-modules-of-all-systems))




;;; Test-whip-up-a-mnemonic

#+development
(defun test-whip-up-a-mnemonic (quiet?)
  (loop with all-mnemonics = ()
        with limit = 6
        for module in (collect-all-module-names)
        as mnemonic = (whip-up-a-mnemonic module)
        do
    (unless quiet?
      (format t "~&~(~10A ~30A~)" mnemonic module))

    (when (member mnemonic all-mnemonics)
      (warn "~&~(~10A ~A~) <--- Duplicate module mnemonic!" mnemonic module))
    (push mnemonic all-mnemonics)

    (when (< limit (length (symbol-name mnemonic)))
      (warn "~&~(~10A ~A~) <--- Too long module mnemonic!" mnemonic module))))

#+development
(test-whip-up-a-mnemonic t) ;; Check things out at load time.





;;;; Top-level Translation Functions

#+(and :chestnut (not :chestnut-trans)) ;Chestnut3.1
(defun translate-all-modules-in-system (system)
  (let ((utable-pathname
         (make-utable-pathname system)))
    (set-up-chestnut-defaults system)
    (set-up-chestnut-incremental-translations system)
    (truncate-symbols max-chestnut-symbol-length system)
    (map-unused-globals-to-dummy-globals)
    (format t "~&Chestnut Translation starting ...")
    (prepare-or-translate-all-modules system t nil)
    (prepare-or-translate-all-modules system nil t)
    (prepare-user-tables utable-pathname system)
    (setf (chestnut-clear-existing-user-tables-without-prompting) t)
    (chestnut-clear-user-tables)
    (load utable-pathname)
    (chestnut-dump-user-tables)
    (generate-include-file-for-make system)))

#+(and :chestnut-3 (not :chestnut-trans)) ;Chestnut3.1
(defun translate-all-modules-in-system (system &optional prepare-only-p analyze-calls-p)
  (declare (ignorable analyze-calls-p))
  (set-up-chestnut-defaults system)
  ;(when analyze-calls-p (setq user::*collect-call-information-p* t))
  (format t "~%Translator: starting symbols truncation...")
  (truncate-symbols max-chestnut-symbol-length system)
  (format t "~%Chestnut Translation starting ...")
  (prepare-all-modules system)
 (unless prepare-only-p
    (translate-all-modules system)
    (format t "~%Chestnut Header file emitting starting...")
    (chestnut-write-header-files-if-modified system)
    (unless (eq system 'gsi)
      (chestnut-write-main-file
        (make-system-pathname
          system "main" "c" :newest nil 'system-lisp-source-files 'binary)
        (launch-function? system)))
    (when timpl::*enter-function-callback-data*
      (write-names-file
        (make-system-pathname
          system "names" "c" :newest nil 'system-lisp-source-files 'binary)
       (make-system-pathname
          system "names" "h" :newest nil 'system-lisp-source-files 'binary)
        (reverse timpl::*enter-function-callback-data*)))
    (generate-c-files-list system))) ;+1
;    (when analyze-calls-p
;      (write-call-analysis-files system)))
; (terpri))


#+(and :chestnut-3 (not :chestnut-trans)) ;Chestnut3.1
(defun write-names-file (c-pathname h-pathname names)
  (with-open-file (out h-pathname :direction :output :if-exists :supersede)
    (format out "~%#ifndef DISABLE_FN_ARRAY~%")
    (format out "~%typedef void fn_type();~%~%")
    (loop for (name c-name) in names
          do (format out "extern fn_type ~A;~%" c-name))
    (format out "~%#endif~%"))
  (with-open-file (out c-pathname :direction :output :if-exists :supersede)
    (format out "~%#ifndef DISABLE_FN_ARRAY~%")
    (format out "~%#include \"names.h\"~%")
    (format out "~%static int x_fn_file_size_array[] = {~%")
    (loop for i from 0
          for size in (cons 0 (reverse timpl::*enter-function-callback-file-data*))
          do (when (plusp i)
               (format out ",")
               (when (zerop (mod i 10))
                 (format out "~%")))
             (format out "~D" size))
    (format out "};~%")
    (format out "~%static fn_type *x_fn_array[] = {")
    (loop for first = t then nil
          for (name c-name) in names
          do (format out "~A~% ~A"
                     (if first "" ",")
                     c-name))
    (format out "};~%~%")
    (format out "static char *x_fn_name_array[] = {")
    (loop for first = t then nil
          for (name c-name) in names
          do (format out "~A~% ~S"
                     (if first "" ",")
                     (format nil "~A" name)))
    (format out "};~%")
    (format out "~%#endif~%")
    (format out "~
               ~%void INIT_names(size)~
               ~%  int size;~
               ~%{~
               ~%   extern void g2ext_note_fn_table_size();~
               ~%#ifndef DISABLE_FN_ARRAY~
               ~%   g2ext_note_fn_table_size(size,x_fn_array,x_fn_name_array,x_fn_file_size_array);~
               ~%#else~
               ~%   g2ext_note_fn_table_size(0,0,0,0);~
               ~%#endif~
               ~%}~
               ~%~%~%")))



#+(and :chestnut-3 (not :chestnut-trans))
(defparameter call-analysis-subdirectory "logs/calls")

;SS_ERROR

;#+(and :chestnut-3 (not :chestnut-trans))
;(defun write-call-analysis-files (system)
;  (declare (ignore system))
;  (setq user::*default-call-information-package* (find-package "AB"))
;  (let ((system-name (case system
;                       (ab "g2")
;                       (telewindows "tw")
;                       (gsi "gsi")
;                       (t (string-downcase system)))))
;    (user::update-file-table-for-system system-name)
;    (flet ((info-pathname (name)
;            (pathname
;              (format nil "~A/~A/~A-~A.lisp"
;                      source-directory-name call-analysis-subdirectory system-name name))))
;      (user::list-special-variables (info-pathname "special-variables"))
;      (user::report-macroexpand-info (info-pathname "macroexpand-information"))
;      (user::write-call-information (info-pathname "call-information"))
;      (user::write-inverse-call-information (info-pathname "inverse-call-information"))
;      (user::write-uncalled-functions (info-pathname "uncalled-functions"))
;      (user::write-use-information-by-file (info-pathname "use-information-by-file")
;                                           (info-pathname "library-use-information"))))
;  nil)


#+(and :chestnut-3 (not :chestnut-trans))
(defun prepare-all-modules (system)
  (let* ((file-class 'system-lisp-source-files)
         (module-list
          (append '(load bootstrap)
                  (generate-list-of-core-modules system))))
    (dolist (current-module? module-list)
      (when (include-for-compile-p current-module? file-class system)
        (let ((source-pathname?
               (make-system-pathname system current-module? nil :newest)))
          (with-gensym-handlers-for-load-file
            (chestnut-prep-file source-pathname?)))))
    (terpri)))




;;; The function `translate-all-modules' takes a system name and will translate
;;; the modules of that system from Lisp to C.  If the feature :translate-all is
;;; currently in the *features* list, it does translate all.  Otherwise, is uses
;;; the value of modules-compiled to determine which modules to translate.

;;; The translation takes care to not change the file write date of the C or H
;;; files, if the contents of the file have not changed.  To do this, it
;;; moves the old translated files to a temporary name, performs the
;;; translation, and if the new files are no different from the previous files,
;;; it  moves the old ones back.  -jra 8/24/93

#+(and :chestnut-3 (not :chestnut-trans))
(defun translate-all-modules (system)
  (let* ((file-class 'system-lisp-source-files)
         (translate-all-p (member :translate-all *features*))
         (module-list
           (if translate-all-p
               (append '(load bootstrap)
                       (generate-list-of-core-modules system))
               (reverse modules-compiled))))
    (dolist (current-module module-list)
      (when (include-for-compile-p current-module file-class system)
        (let* ((source-pathname
                 (make-system-pathname system current-module nil :newest))
               (mnemonic-name
                 (whip-up-a-mnemonic current-module))
               (temp-name
                 (intern (format nil "~a-TEMP" mnemonic-name)))
               (c-temp-pathname
                 (make-system-pathname
                   system temp-name "c" :newest nil file-class 'binary))
               (c-destination-pathname
                 (make-system-pathname
                   system mnemonic-name "c" :newest nil file-class 'binary))
               (h-temp-pathname
                 (make-system-pathname
                   system temp-name "h" :newest nil file-class 'binary))
               (h-destination-pathname
                 (make-system-pathname
                   system mnemonic-name "h" :newest nil file-class 'binary))
               (old-translation-exists?
                 (and (probe-file c-destination-pathname)
                      (probe-file h-destination-pathname))))
          (declare (ignorable old-translation-exists?
                              c-temp-pathname
                              h-temp-pathname))
          ;; backup old files first
          #+lispworks
          (when old-translation-exists?
            (rename-file c-destination-pathname c-temp-pathname)
            (rename-file h-destination-pathname h-temp-pathname))
	  (with-gensym-handlers-for-compile-file ()
	    (chestnut-translate-file
	     source-pathname
	     c-destination-pathname
	     h-destination-pathname
	     nil))
          #+lispworks
          (when old-translation-exists?
            (cond ((or (file-diff-p c-destination-pathname c-temp-pathname)
                       (file-diff-p h-destination-pathname h-temp-pathname))
                   ;; if there're any differences, old files are useless.
                   (delete-file c-temp-pathname)
                   (delete-file h-temp-pathname))
                  (t
                   ;; or, recover old files
                   (delete-file c-destination-pathname)
                   (delete-file h-destination-pathname)
                   (rename-file c-temp-pathname c-destination-pathname)
                   (rename-file h-temp-pathname h-destination-pathname)))))))
    (terpri)))



;;; The function `file-diff-p' is used to compare two text files.  It will
;;; return true in all cases except where the two given pathnames name existent
;;; files and the contents of these two files are exactly the same.

(defmacro file-diff-read-char (stream)
  #+lucid `(lcl:fast-read-char ,stream nil nil)
  #-lucid `(read-char ,stream nil nil))

(defun-for-macro file-diff-p (pathname1 pathname2)
  (with-open-file (input1 pathname1 :if-does-not-exist nil)
    (unless input1
      (return-from file-diff-p t))
    (with-open-file (input2 pathname2 :if-does-not-exist nil)
      (unless input2
        (return-from file-diff-p t))
      (not (loop for char1 = (file-diff-read-char input1)
                 for char2 = (file-diff-read-char input2)
                 until (and (null char1) (null char2))
                 always (and char1 char2 (char= char1 char2)))))))




;;; The function `generate-c-files-list' is used to make a file in the C
;;; directory which will contain the names of all the C files needed to be
;;; linked together to form this product's image or library.

;;; There are two sets of files to consider.  The first and largest set is the
;;; set of C files produced by translating Lisp source files.  The second set is
;;; make up of the C files always generated by the translator for initializing.

#+(and :chestnut-3 (not :chestnut-trans)) ;Chestnut3.1
(defun generate-c-files-list (system)
  (let ((standard-modules (append
                            '("symtab" "userfuns" "userinit" "usersyms")
                            (when timpl::*enter-function-callback-data*
                              '("names"))))
        (files-on-line 0)
        (files-per-line 6))
    (with-open-file (output
                      (make-system-pathname
                        system
                        (format nil "~(~a~)-files"
                                (or (system-alias system) system))
                        "txt" :newest nil 'system-lisp-source-files 'binary)
                      :direction :output :if-exists :supersede)
      (with-open-file (opt-output
                        (make-system-pathname
                          system
                          (format nil "~(~a~)-files"
                                  (or (system-alias system) system))
                          "opt" :newest nil 'system-lisp-source-files 'binary)
                        :direction :output :if-exists :supersede)
        (loop with first = t
              for standard-module in standard-modules
              do
          (write-line standard-module output)
          (cond (first
                 (setq first nil))
                (t
                 (write-string ", " opt-output)
                 (when (>=f files-on-line files-per-line)
                   (setq files-on-line 0)
                   (write-line "-" opt-output))))
          (write-string standard-module opt-output)
          (write-string ".obj" opt-output)
          (incff files-on-line))
        (loop for lisp-module in
              (append '(load bootstrap) (generate-list-of-core-modules system))
              do
          (when (include-for-compile-p
                  lisp-module 'system-lisp-source-files system)
            (let ((mnemonic (string-downcase
                              (symbol-name (whip-up-a-mnemonic lisp-module)))))
              (write-line mnemonic output)
              (write-string ", " opt-output)
              (when (>=f files-on-line files-per-line)
                (setq files-on-line 0)
                (write-line "-" opt-output))
              (incff files-on-line)
              (write-string mnemonic opt-output)
              (write-string ".obj" opt-output))))))))




#+(and :chestnut (not :chestnut-trans))
(defun prepare-or-translate-all-modules (system prepare? write-out-files?)
  (let* ((file-class 'system-lisp-source-files)
         (module-list
           (if (or prepare?
                   (member :translate-all *features*))
               (reverse
                 (append '(load bootstrap)
                         (generate-list-of-core-modules system)))
               modules-compiled))
         source-pathname?
         c-destination-pathname?
         top-destination-pathname?
         e-destination-pathname?)
    (dolist (module (reverse module-list))
      (let ((current-module? module))
        (when (include-for-compile-p module file-class system)
          (setq source-pathname?
                (make-system-pathname system module nil :newest))
          (cond
            (prepare?
             (setq c-destination-pathname?
                   (make-system-pathname system module "c"
                                         :newest nil file-class 'binary))
             ;; Following form duplicates translator output.
             ;;(format t "~%Preparing file ~A" source-pathname?)
             (chestnut-prep-file source-pathname?))
            (t
             (setq c-destination-pathname?
                   (make-system-pathname system module "c"
                                         :newest nil file-class 'binary))
             (setq e-destination-pathname?
                   (make-pathname :defaults c-destination-pathname?
                                  :type "e"))
             (setq top-destination-pathname?
                   (make-pathname :defaults c-destination-pathname?
                                  :type "top"))
             (format t "~%Translating file ~A to ~A"
                     source-pathname? c-destination-pathname?)

             ;; The following is added as part of a debugging exercise with
             ;; Chestnut.
;             (multiple-value-bind (used avail) (lcl:gc-size)
;               (when (> (+ used avail) 20000000)
;                 (cerror "continue" "Over 20Meg in dynamic hemispheres.")))
             (terpri)
             #-sbcl
             (lisp:room)
;             (user::memory-usage)

             (if write-out-files?
                 (chestnut-translate-file
                   source-pathname? c-destination-pathname?
                   e-destination-pathname? top-destination-pathname?)
                 (chestnut-translate-file source-pathname? nil nil nil)))))))))




#+(and (or :chestnut :chestnut-3) (not :chestnut-trans)) ;Chestnut3.1
(defun prepare-or-translate-module
    (system prepare? write-out-files? source-pathname)
  (let* ((file-class 'system-lisp-source-files)
         c-destination-pathname?
         top-destination-pathname?
         e-destination-pathname?)
    (cond
      (prepare?
       (setq c-destination-pathname?
             (make-system-pathname system source-pathname "c"
                                   :newest nil file-class 'binary))
       (format t "~%Preparing file ~A" source-pathname)
       (chestnut-prep-file source-pathname)
       )
      (t
       (setq c-destination-pathname?
             (make-system-pathname system source-pathname "c"
                                   :newest nil file-class 'binary))
       (setq e-destination-pathname?
             (make-pathname :defaults c-destination-pathname?
                            :type "e"))
       (setq top-destination-pathname?
             (make-pathname :defaults c-destination-pathname?
                            :type "top"))

       (format t "~%Translating file ~A to ~A"
               source-pathname c-destination-pathname?)

       (if write-out-files?
           (progn
             (chestnut-translate-file
               source-pathname c-destination-pathname?
               e-destination-pathname? top-destination-pathname?))
           (chestnut-translate-file source-pathname nil nil nil))))))

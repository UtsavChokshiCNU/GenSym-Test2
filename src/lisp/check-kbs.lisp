;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module CHECK-KBS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Ong, Peng Tsin




;;;; Introduction

;;; This module is assorted small facilities.  It's name is entirely a
;;; historical artifact, though a function of the same name resides in here.
;;; This file is loaded only into G2, hence many debugging functions having
;;; to do with the frame system are here.

;;; This module is compiled with the :overriding-include-test (not no-macros),
;;; which means - amoung other things, this is not directly part of the
;;; distributed product.


;;; `ci' returns the latest strict class instance of class-name.  It remembers
;;; the last class requested.

;;; `ci-list' lists, using the gensym cons pool, all strict class instances of
;;; class-name.

#+development
(defvar ci-last-class-name nil)

#+development
(defun ci (&optional class-name? offset-from-tail?)
  (let ((gensym-list (ci-list class-name? offset-from-tail? 1))) ; => nil or cons
    (prog1 (first gensym-list)
      (reclaim-gensym-list gensym-list))))

#+development
(defun ci-list (&optional class-name? offset-from-tail? max-instances?)
  (let* ((class-name (or class-name? ci-last-class-name))
         (offset-from-tail (or offset-from-tail? 0)))
    (setf ci-last-class-name class-name)
    (when class-name                        ; nil first time in session only
      (loop for instance?
                = (instances-specific-to-this-class-tail-pointer class-name)
                then (class-specific-instances-reverse-pointer instance?)
            as count from 1
            while instance?
            when (> count offset-from-tail)
              collect instance? into result using gensym-cons
              and count t into collection-count
            while (or (null max-instances?)
                      (< collection-count max-instances?))
            finally (return result)))))



;;; `ni' returns the instance named name.

(defun ni (name &optional class?)
  (get-instance-with-name-if-any (or class? 'block) name))



#+development
(defun dcs ()
  (describe-current-state))


;;; The function `lbe' returns a list of the block's edges.

#+development
(defun lbe (&optional (block *))
  (list
    (left-edge-of-block block)
    (top-edge-of-block block)
    (right-edge-of-block block)
    (bottom-edge-of-block block)))



;;; `arglist' - should be #+development, but I want to incur no risk whatsoever
;;; in terms of what I'm changing about Lucid for now.  - jv, 8/23/99

#+allegro
(defmacro arglist (symbol)
  (cond
    ((eval-feature :lucid)
     `(,(intern "ARGLIST" (find-package "LCL"))
        ,symbol))
    ((eval-feature :allegro)
     `(,(intern "ARGLIST" (find-package "EXCL"))
        ,symbol))
    (t
     nil)))



;;; The function `description-of-g2-function-for-ilisp' returns the additional
;;; info describing a function when you type c-sh-A in emacs.

#+development
(defun description-of-g2-function-for-ilisp (symbol)
  ;; Kind of heuristic, but then it's just for c-sh-A.
  (when (fboundp symbol)
    (let* ((arglist (fn-arglist symbol))
           (arg (first arglist)))
      (cond ((eq (symbol-package symbol)
		 #+ansi-cl (find-package "COMMON-LISP")
		 #-ansi-cl (find-package "LISP"))
             " (CommonLisp)")
            ((get symbol 'icp-message-type-code)
             " (ICP)")
            ((not (and (= (length arglist) 1) (symbolp arg) (macro-function symbol)))
             nil)
            ((memq symbol global-property-names)
             " (Global Property)")
            ((memq symbol kb-specific-property-names)
             " (KB Property)")
            ((loop for slotd in (def-structure-slot-descriptions arg)
                   thereis (eq symbol (if (consp slotd) (car slotd) slotd)))
             " (Accessor)")
            ((structure-method-arglist symbol)
             (if (macro-function symbol)
                 " (Structure Method Macro)"
                 " (Structure Method)"))
            ((let* ((class (class-description (car arglist)))
                    (slotd (find symbol (and class (slot-descriptions class))
                                 :key #'(lambda (slotd) (unique-slot-name slotd)))))
               (when slotd
                 (if (eq (slot-name-assignment symbol) 'lookup-slot)
                     " (LookupSlot)"
                     " (Slot)"))))))))


#+(and lucid development)
(when (find-package "ILISP")
  (let ((list (intern "FUNCTION-DESCRIPTIONS" "ILISP")))
    (when (boundp list)
      (push 'description-of-g2-function-for-ilisp (symbol-value list)))))



;;; `get-or-make-documentation-for-editor' is called from
;;; the ILISP implementation of documentation-lisp by virtue
;;; of our redefinition of.

#+development
(defun get-or-make-documentation-for-editor (symbol &optional type)
  (declare (ignore type))
  (with-output-to-string (s)
    ;; Function Bindings
    (when (fboundp symbol)
        (format s
              "~&~S ~(is a ~A: ~)"
              symbol (if (macro-function symbol) "macro" "defun"))
      (let ((*package* (symbol-package symbol)))
        (format s "~&  arglist: ~(~A~)" (fn-arglist symbol))))

    ;; Homes
    (let ((modules (modules-of-symbol symbol))
          (systems (systems-of-symbol symbol)))
      (when modules
        (format s "~&  modules: ~(~S~)" modules))
      (when systems
        (format s ", only in system~p: ~{~a~^, ~}" (length systems) systems)))

    ;; Interesting info from properties.
    (loop for (key value) on (symbol-plist symbol) by #'cddr
          do
      (case key
        (class-description
         (format s "~&  a class: ~S" value))
        (type-description-of-type
         (format s "~&  an ab type: ~S" value))
        (include-test-for-compile
         (format s "~&  this is module name: ~S" value))
        (slot-category
         (format s "~&  this is a slot name: ~S" value))
        (function-to-reclaim-kb-specific-property-value?
         (format s "~&  this is a kb specific property name: ~S" value))
        (generic-method-lambda-list
         (format s "~&  this is a method on frames: ~A" value))
        ))

    (when (memq symbol global-property-names)
      (format s "~&  this is a global property"))

    ))



#+development
(def-development-describer describe-gensym-symbol (symbol)
  (when (symbolp symbol)
    (format t "~&~A" (get-or-make-documentation-for-editor symbol nil))
    (describe symbol)
    symbol))



#+development
(defun print-documentation-for-editor (symbol)
  ;; Interesting info from properties.
  (loop for (key value) on (symbol-plist symbol) by #'cddr
        do
    (case key
      (class-description
       (format t "~& A class: ~S" value))
      (type-description-of-type
       (format t "~& An ab type: ~S" value))
      (include-test-for-compile
       (format t "~& This is module name: ~S" value))
      (slot-category
       (format t "~& This is a slot name: ~S" value))
      (function-to-reclaim-kb-specific-property-value?
       (format t "~& This is a kb specific property name: ~S" value))
      (generic-method-lambda-list
       (format t "~& This is a method on frames: ~A" value)))))


#+(and lucid development)
(when (find-package "ILISP")
  (let ((list (intern "ILISP-FUNCTION-DESCRIBERS" "ILISP")))
    (when (boundp list)
      (push 'print-documentation-for-editor (symbol-value list)))))


#+development
(defun list-magic-arguments
    (&optional
      (mouse-pointer
        (cond
          ((current-named-dynamic-extent-p 'servicing-workstation-event)
           (format t "~&Assuming mouse pointer of event being serviced.")
           (mouse-pointer-of-latest-event current-workstation))
          ((current-named-dynamic-extent-p 'servicing-workstation)
           (format t "~&Assuming lastest mouse pointer of workstation being serviced.")
           (mouse-pointer-of-latest-event current-workstation))
          (t
           (format t "~&Assuming lastest mouse pointer of system window's workstation.")
           (mouse-pointer-of-latest-event
             (workstation-this-is-on
               system-window))))))
  (let (magic-arguments)
    (map-over-global-property
      'magic-argument-fetcher
      #'(lambda (s v)
          (declare (ignore v))
          (push s magic-arguments)))
    (loop
      ;; This binding makes many arguments work, even if not servicing workstation.
      with current-workstation = (workstation-for-mouse-pointer mouse-pointer)
      for magic-argument in (sort magic-arguments #'string<)
          do
      (format t "~&~(~20s~): ~S" magic-argument
              (if (and (memq magic-argument '(event))
                       (not (current-named-dynamic-extent-p
                              'servicing-workstation-event)))
                  :ignored--wrong-dynamic-extent
                  (funcall
                    (get magic-argument 'magic-argument-fetcher)
                    mouse-pointer))))))





;;; `Count-instructions' heuristically determines the number of assembly language
;;; instructions used for the function named function-name.  Note that the result
;;; will vary depending on factors such as the hardware/software platform on
;;; which this is executed and the compiler settings for speed, safety, etc.

#+development
(defun count-instructions (function-name)
  (let ((output-string
          (with-output-to-string (*standard-output*)
            (disassemble function-name))))
    (count #\newline output-string)))



;;; Count-instructions-of-related-functions will do a count-instructions on all
;;; of the functions that were defined in the same file with the function named.
;;; Finally it will provide a total for the entire file.

#+development
(defun count-instructions-of-related-functions (function-in-file)
  (let ((total 0)
        (file-namestring
          (namestring
            (let ((info (get function-in-file :source-file-name)))
              (ab-lisp::etypecase info
                (null (error "Can't find file for ~S" function-in-file))
                (list
                  (second (assq 'defun (get function-in-file :source-file-name))))
                (ab-lisp::pathname
                  info))))))
    (print file-namestring)
    (do-symbols (s (find-package "AB"))
      (flet ((count-em ()
                       (let ((count (count-instructions s)))
                         (incf total count)
                         (format t "~&~6D ~(~S~)" count s))))
        (let ((file-definitions (get s :source-file-name)))
          (cond
            ((null file-definitions)
             )
            ((and (pathnamep file-definitions)
                  (string-equal file-namestring (namestring file-definitions)))
             (count-em))
            ((listp file-definitions)
             (loop
             for file-definition in file-definitions
             do
               (when (and (listp file-definition)
                          (eq 'defun (first file-definition))
                          (string-equal file-namestring (namestring (second file-definition))))
                 (count-em))))))))
    (format t "~&~6D total for file ~A." total file-namestring)))






;;;; All User-Visible Slots




;;; Print-all-user-visible-slots ... prints to *standard-output* if file-name?
;;; is nil; otherwise opens file-name? and prints to it.

#+development
(defun print-all-user-visible-slots
       (&optional (file-name? "ma:>mhd>user-visible-slots.text"))
  (if file-name?
      (with-open-file (*standard-output* file-name? :direction :output)
        (print-all-user-visible-slots-1 'kb-frame))
      (print-all-user-visible-slots-1 'kb-frame)))

#+development
(defun print-all-user-visible-slots-1 (class)
  (print-all-user-visible-slots-2 class)
  (loop for subclass in (inferior-classes class)
        do (print-all-user-visible-slots-1 subclass)))




#+development
(defmacro do-attributes-for-class
          (class
           (slot-name-var alias?-var &optional slot-features-var? type-of-slot-var?)
           &body body)
  (let ((class-var '#:class)
        (class-description-var '#:class-description)
        (slot-descriptions-var '#:slot-descriptions)
        (slot-description-var '#:slot-description)
        (slot-features-var (or slot-features-var? '#:slot-features))
        (type-of-slot-var (or type-of-slot-var? '#:type-of-slot)))
    `(loop with ,class-var = ,class
           with ,class-description-var
             = (class-description ,class-var)
           with ,slot-descriptions-var
             = (slot-descriptions ,class-description-var)
           as ,slot-description-var in ,slot-descriptions-var
           as ,slot-name-var = (unique-slot-name ,slot-description-var)
           as ,alias?-var
              = (get-alias-for-slot-name-if-any ,slot-name-var ,class)
           as ,slot-features-var
              = (slot-features ,slot-description-var)
           as ,type-of-slot-var = (feature-assq 'type ,slot-features-var)
           when (and ,type-of-slot-var
                     (let ((do-not-put-in-attribute-tables-feature?
                               (or
                                 (feature-assq
                                   'previously-put-in-attribute-tables
                                   ,slot-features-var)
                                 (feature-assq
                                   'do-not-put-in-attribute-tables
                                   ,slot-features-var))))
                       (not
                         (if (cdr do-not-put-in-attribute-tables-feature?)
                             (case (cadr do-not-put-in-attribute-tables-feature?)
                               (nupec
                                (nupec-authorized-p))
                               (not-nupec
                                (not (nupec-authorized-p)))
                               ;; (g1 (g2-is-really-g1-p))  ; ML's idea (??)
                               )
                             do-not-put-in-attribute-tables-feature?)))
                     ;; can't decide on this until we have an instance:
;                     (or (not (feature-assq
;                                'do-not-put-in-attribute-tables-if-null
;                                ,slot-features-var))
;                         (get-slot-value ,frame-var ,slot-name-var))
                     )

             do (progn . ,body))))

#+development
(defun print-all-user-visible-slots-2 (class)
  (format t "~2%~a" class)
  (do-attributes-for-class
    class (slot-name alias? slot-features type-of-slot)
    (unless (or (null (category-symbol-given-slot-type type-of-slot))
                (eq slot-name 'class) ; uninteresting
                (not (memq slot-name
                           (slots-local-to-class (class-description class)))))
      ;; The code for determing whether the slot has been inherited has been
      ;; commented out because it is replaced with code checking the slots-
      ;; local-to-class of class.  (ghw 10/13/93)
;      (let ((slot-description-for-this-class
;              (get-slot-description-of-class-description
;                slot-name (class-description class)))
;            (slot-description-for-superior-class?
;              (if (direct-superior-classes class)
;                  (get-slot-description-of-class-description
;                    slot-name (class-description (car (direct-superior-classes class)))))))
;        (if (eq slot-description-for-this-class        ; => inherited
;                slot-description-for-superior-class?)
;            (progn
;              (format t "~%  ~(~a~) " slot-name)
;              (format t "~%    (Inherited from ~a)"
;                      (loop for next-class-up?
;                                = (direct-superior-classes class)
;                                then (direct-superior-classes next-class-up?)
;                            while next-class-up?        ; just for safety
;                            when (not (eq slot-description-for-this-class
;                                          (assq slot-name
;                                                (class-description (car next-class-up?)))))
;                              return (car next-class-up?)))
;              )
;            (progn
      (format t "~%  ~(~a~) " slot-name)
      (if alias? (format t "(AKA ~(~a~))" alias?))
      (if (cadr type-of-slot)
          (format t "  ~a" (cadr type-of-slot)))
      (if (and slot-features
               (or (cdr slot-features)
                   (not (eq (car (car slot-features)) 'type))))
          (loop initially
                  (format t "~%    Features: ")
                for l on slot-features
                unless (eq (car (car l)) 'type)
                  do (format t "~(~a  ~)"
                             (if (consp (car l))
                                 (if (cdr (car l))
                                     (car l)
                                     (car (car l)))
                                 (car l))))))))



#+development
(defun list-classes-whose-instances-are-nameless ()
  (loop for class being each subclass of 'kb-frame
        when (or (null (type-of-slot-if-editable
                         class 'name-or-names-for-frame))
                 (feature-assq
                   'do-not-put-in-attribute-tables
                   (slot-features
                     (get-slot-description-of-class-description
                       'name-or-names-for-frame (class-description class))))
                                  (feature-assq
                   'previously-put-in-attribute-tables
                   (slot-features
                     (get-slot-description-of-class-description
                       'name-or-names-for-frame (class-description class)))))
          collect class))




;; These are the classes whose instances do not have a visible or editable
;; name-or-names-for-frames slot, as of 7/3/91:

;; NOTE: classes button, user-menu-choice, graph, and readout-table were
;; all changed to not be on this list today.  (MHD 7/3/91)

;;    kb-frame
;;    dependent-frame
;;    forward-chaining-link
;;    true-value-update-recipient
;;    backward-chaining-link
;;    g2-cell-array
;;    g2-cell-array-cell
;;    code-body
;;    plot
;;    system-frame
;;    definition
;;    relation
;;    procedure
;;    external-simulation-definition
;;    g2-query-cell
;;    g2-designation-cell
;;    g2-expression-cell
;;    system-table
;;    object-definition
;;    connection-definition
;;    message-definition
;;    printer-setup
;;    debugging-parameters
;;    fonts
;;    timing-parameters
;;    logbook-parameters
;;    message-board-parameters
;;    log-file-parameters
;;    menu-parameters
;;    language-parameters
;;    color-parameters
;;    editor-parameters
;;    journal-and-backup-parameters
;;    inference-engine-parameters
;;    data-server-parameters
;;    simulation-parameters
;;    kb-restrictions
;;    miscellaneous-parameters
;;    function-definition
;;    remote-procedure-declaration
;;    foreign-function-declaration




;;;; Loading Hostinfo

;;; The function `parse-hostinfo-line-into-fields' returns a list of the
;;; colon-delimited strings in line-string.
;;;
;;; The first field begins with the first non-whitespace (space, tab),
;;; non-comment (#) character seen, or with the first colon (:) character seen.
;;; Each subsequent field begins with a colon.  The last field ends with
;;; whitespace, or with a comment, or with a colon. All previous fields end with
;;; a colon.  All whitespace after or before a color is included in a field.
;;; Thus, a reason for starting the first field with a colon, or for ending the
;;; last field with a colon, would be to get whitespace included in the field.
;;;
;;; Note that "empty" fields ("") are allowed, as are all-whitespace fields
;;; (e.g., " ").  They just need to begun and ended with colons.  (And the caller
;;; needs to deal with them.)
;;;
;;; Note that as things now stand, there's no way to have either a : or # appear
;;; within a field, since they'll be interpreted as a field delimiter and a
;;; comment starter, respectively.
;;;
;;; Examples:
;;;
;;; foo
;;; -> ("foo")
;;;
;;; foo:bar:baz:blech
;;; -> ("foo" "bar" "baz" "blech")
;;;
;;;    foo:bar:baz:blech   # same thing
;;; -> ("foo" "bar" "baz" "blech")
;;;
;;; foo:  bar  :  S/N#34562 :baz:blech
;;;
;;; -> ("foo" "  bar  " "  S/N")   ; beware of # -- it starts a comment

(defun parse-hostinfo-line-into-fields (line-string)
  (let ((line-string-1 (string-trim '(#\space #\tab) line-string)))
    (loop with result-so-far = nil
          with i = 0
          do (loop with non-space-seen? = nil
                   for j from i below (length line-string-1)
                   as char = (char line-string-1 j)
                   until (or (char= char #\#)
                             (char= char #\:))
                   when (and (not non-space-seen?)
                             (not (member char '(#\space #\tab))))
                     do (setq non-space-seen? t)
                   finally
                     (setq result-so-far
                           (nconc result-so-far
                                  (if (or non-space-seen? (char= char #\:))
                                      (list (subseq line-string-1 i j)))))
                     (setq i j))
          until (or (>= i (length line-string-1))
                    (char= (char line-string-1 i) #\#))
          do (incff i)
          finally
            (return result-so-far))))


(defun create-custom-hostinfo (namestring machine-id-list dummy-machine-name-stub)
  (with-open-file (output namestring
                   :direction :output)
    (loop for i from 1
          for machine-id in machine-id-list
          do
      (format output "~(~a~)-~3,'0d:~(~a~)~%"
              dummy-machine-name-stub i machine-id))))


;;; `Read-host-info-file-into-list' presumes that pathname is a file containing
;;; the result of the unix command "ypcat hostinfo".

(defun read-host-info-file-into-list (pathname)
  (with-open-file (input-stream pathname)
    (sort-list
      (loop for line? = (read-line input-stream nil nil)
            while line?
            as fields = (parse-colon-delimited-ascii-text-line-into-list-of-ascii-strings line?)
            ;; obsolete! (parse-hostinfo-line-into-fields line?)
            when fields
              collect fields)
      #'string-lessp
      #'car)))




;;;; Site OK Files

;;; This section is HALF of a facility to generate the OK files
;;; for Gensym Corp.  The other - and more secret half - is found
;;; in the module LS, with the critical sources in the lic/integrals.lisp.
;;; Those sources are encrypted.

;;; Remember that this module loads only in development.

;;; The routines that follow contain forward references into the LS code,
;;; and those forward references are crafted to avoid generating warnings.


;;; IMPORTANT NOTE ABOUT STRINGS.

;;; Strings have two representations, Lisp strings (8 bit bytes, elements
;;; are characters) and Wide strings, (symbol vectors with embedded vectors
;;; of 16bit fixnums).

;;; The code in the secret modules only uses Lisp strings.  The following
;;; code uses both, and the code in earlier modules that are part of
;;; G2 use both.

;;; Calls into the secret modules coerce into 8 bits before crossing over.
;;; Calls from the secret modules call routines on this side that expect
;;; 8 bit strings.

;;; Quoted constants, such as symbol names and lists of products etc. are
;;; represented as lisp strings, and coerced into wide strings asap.




;;; Do-site-ok-version is to be wrapped around the saving of the site OK
;;; file.  The version argument should be either 3 or 4 (or 5 or 5.1,
;;; etc.).  It causes the "g2.ok", "tw.ok", etc., to be written for use by
;;; Version 3 G2/TW (and version 4.0 Beta Rev. 0).
;;;
;;; Ok-file-generation-doing-pass-for-version-4-p is true in version 4 or
;;; greater.
;;;
;;; Ok-file-generation-for-version-5.1-or-greater-p is true when what it
;;; says is true.

(defvar ok-file-generation-doing-pass-for-version-4-p nil)

(defvar ok-file-generation-for-version-5.1-or-greater-p nil)

;;; Similarly, `ok-site-file-version' is used to condition what is include
;;; in an ok file. It presently distinguishes v5 from earlier versions in
;;; the choice of authorized-modules made by x34.  -ddm 7/10

(defvar ok-site-file-version nil)
(defvar t2-site-file-version nil)  ; ddm 12/7/98


(defvar site-ok-file-version-extension "")

(defvar host-part-of-ok-pathname-string "")
(defvar directory-part-of-ok-pathname-string "/home/siteok/foundry")
(defvar type-part-of-ok-pathname-string ".ok")
(defvar type-part-of-backup-ok-pathname-string ".ok.bak")


(defmacro do-t2-site-ok-version (version &body body)
  `(let* ((t2-site-file-version ,version)
          (pulse-rate-multiplier t2-site-file-version)
          (pulse-rate-options (choose-pulse-rate-multiplier))
          (site-ok-file-version-extension (format nil "v~d" t2-site-file-version)))
     ,@body))


(defmacro do-site-ok-version ((version sub-version) &body body)
  `(let* ((version ,version)
          (ok-site-file-version version)   ; 'version' is too generic to make special
          (sub-version ,sub-version)
          (chaining-refresh-version version)
          (keytab1 (choose-keytab))        ; bound for integrals
          (ok-file-generation-doing-pass-for-version-4-p (> version 3))
          (ok-file-generation-for-version-5.1-or-greater-p
            ;; This controls the file-format-version. When this is true
            ;; we emit version 2.
            (or (>=f version 6)
                (eq sub-version '5.1-or-greater)))
          (chaining-refresh-list      ; see numbers.lisp: voiceprint/bellyprint
            (case version
              (3 "f3r56twe4")
              (4 "gsa88z0q3")
              (5 "htb99a1r4")
              (6 "htb99a1r4")
              (t (error "illegal version"))))
          (site-ok-file-version-extension (format nil "v~d" version))
          (slots-to-skip-saving-in-ok-files
            (case version
              (3
               (list*
                 'maximum-number-of-concurrent-floating-telewindows-allowed
                 'maximum-number-of-concurrent-floating-tw2-allowed
                 slots-to-skip-saving-in-ok-files))
              (4
               (list*
                 'maximum-number-of-concurrent-floating-tw2-allowed
                 slots-to-skip-saving-in-ok-files))
              (5
               (case sub-version
                 (5.1-or-greater
                  slots-to-skip-saving-in-ok-files)
                 (otherwise
                  (list*
                    'maximum-number-of-concurrent-floating-tw2-allowed
                    slots-to-skip-saving-in-ok-files))))
              (6
               slots-to-skip-saving-in-ok-files))))
     ,@body))




;;; `Authorize-packages' should be executed fom within a g2-window while
;;; a g2.ok is present. It adds authorizations to the ok-names. oks is
;;; a list of ok objects by name. Each must already have a machine-id
;;; present. Packages is a list of the names of packages.

(defun authorize-packages (ok-names packages)
  (loop for ok-name in ok-names
        for ok = (frame-or-frames-with-this-name ok-name)
        when (of-class-p ok 'ok)
          do
            (loop for kb-package in packages doing
              (authorize-package ok kb-package))))



;;; The list `all-gensym-products' doesn't have any official status.  It's just
;;; used to decide which packages to include in the site ok file.  See also
;;; the file lisp/products.lisp

(defparameter all-gensym-products
              '(gensym-gmm gensym-dsp

                gensym-gda                ; used for GDA V. 1; see gensym-gda2 below

                ;; 11/19/92: Gensym Course packages:
                gensym-basic
                gensym-intermediate

                ;; 12/11/92: New Gensym Packages:
                gensym-nol                ; NeurOnLine
                gensym-em                ; Energy Manager


                ;; 12/14/92: New Gensym Package:
                gensym-hd                ; Help Desk

                gensym-gmq                ; G2 Message Queues
                gensym-po                ; Parallel Optimizer

                ;; 8/24/94: New Gensym Package:
                gensym-opa                ; Gensym OPerator's Assistant

                ;; 12/12/94: New Version of Old Package: (gensym-gda)
                gensym-gda2

                ;; 2/21/95
                gensym-rethink

                ;; 5/16/95
                gensym-gspc

                ;; 5/20/95 (but in site OK only as of 7/27/95)
                gensym-bayes-online

                ;; 5/20/95 (but in site OK only as of 7/27/95)
                gensym-space-planner

                ;; 7/27/95
                gensym-vb-bridge

                ;; 4/15/96
                gensym-gas

                ;; 9/10/96
                gensym-gold
                gensym-gda3
                gensym-gda4
                gensym-nol3
                gensym-nol4
                gensym-gspc3

                ;; 6/6/97
                gensym-fe                ; Gensym Fault Expert

                ;; 6/19 (for Ann Bark)
                gensym-oxs           ; Operations eXpert SNMP
                gensym-opac          ; OPeration Action language
                gensym-cdg           ; Causal DiGraph

                ;; 7/28 (for MAK)
                gensym-gqs4          ; G2 Queue System
                gensym-gqs5
                ;;gensym-devtools5     ; G2 Developer Tools
                ;; 'deftools5' has been renamed 'protools5' 12/8
                gensym-protools5

                ;; 3/6/98 for Tim Hill, Kim Wilkins (demos in DC office)
                gensym-opweb    ; OpEx Web Interface
                gensym-dxiov    ; DxI OpenView v2.0
                gensym-ipra     ; IP Reachability Analyzer (IPRA) v1.0
                gensym-ora      ; OpEx Reachability Analyzer (ORA) v1.0

                ;; 3/9/98 for Doug Loyer
                gensym-activexlink

                ;; 10/16/98 for Stephen Flores
                gensym-corbalink-dev-v1
                gensym-corbalink-runtime-v1

                gensym-spt    ; Schematic Programming Tool

                gensym-fermentation-expert
                gensym-message-parsing-engine
                g2player

                gensym-spt    ; Schematic Programming Tool

                ))


(defun authorize-all-machines-for-packages (packages)
  (loop for ok being each class-instance of 'ok
        doing
    (setf (authorized-kb-packages ok) nil)
    (loop for kb-package in packages
          do (authorize-package ok kb-package))))


(defun authorize-all-machines-for-all-gensym-products ()
  (authorize-all-machines-for-packages all-gensym-products))


(defun authorize-package (ok kb-package &optional (start-date 0) (end-date 0))
  (let* ((machine-id (machine-id ok))
         q1 q2 q3 q4 q5 q6 c1 c2 c3
         kb-packages this-authorization?)
    (declare (special ok-authorized-packages))
    (unless (boundp 'ok-authorized-packages)
      (error "A development G2 must be loaded to call authorize-package."))
    (when machine-id
      (multiple-value-setq (q1 q2) (color-match-p (symbol-namew kb-package)))
      (multiple-value-setq (q3 q4) (eval-sequence-2 (symbol-namew kb-package)))
      (let ((machine-id-a (wide-string-to-string machine-id)))
        (multiple-value-setq (q5 q6) (button-down-handler machine-id))
        (reclaim-simple-gensym-string machine-id-a))
      (multiple-value-setq (c1 c2) (procedure-recursive q1 q2 q5 q6 start-date end-date))
      (setq c3 (reverse-list-search q3 q4 q5 q6 c1 c2 start-date end-date))

      (setq kb-packages (authorized-kb-packages ok))
      (setq this-authorization? (assq kb-package kb-packages))

      (cond
        (this-authorization?
         (setf (second this-authorization?) c1)
         (setf (third this-authorization?) c2)
         (setf (fourth this-authorization?) c3)
         (setf (ok-slot-coordinator ok)
               (logiorf (ok-slot-coordinator ok) ok-authorized-packages)))

        (t (setf (authorized-kb-packages ok)
                 (slot-value-cons
                   (nconc
                     (slot-value-list kb-package c1 c2 c3)
                     (if (>f start-date 0) (slot-value-list start-date))
                     (if (>f end-date 0) (slot-value-list end-date)))
                   kb-packages))
           (setf (ok-slot-coordinator ok)
                 (logiorf (ok-slot-coordinator ok) ok-authorized-packages))))

      (let ((machine-id-a (wide-string-to-string machine-id)))
        (analyze-authorized-packages
          (authorized-kb-packages ok)
          machine-id
          ok)
        (reclaim-simple-gensym-string machine-id-a)))))



;;; `Unravel-trapped-errors' visits all the OK objects and fills them
;;; out as the arguments suggest.

;;; `Unravel-trapped-errors' [as of 3/29/93] does not change the OK for this
;;; machine at all.  To change the ok for this machine, call x34 directly.
;;; This function iterates over all of the other OKs in the current KB and
;;; applies x34 to them along with the arguments supplied.

(defun unravel-trapped-errors
    (&optional secure? online? japanese? nupec? korean? license-option?
               gspan? javalink? javalink-professional? activeXlink? chinese?
               number-of-processes?
               (maximum-number-of-concurrent-floating-telewindows-allowed 0)
               (maximum-number-of-concurrent-floating-tw2-allowed 0))
  (when (and
          (not ok-file-generation-doing-pass-for-version-4-p)
          (not (= 0 maximum-number-of-concurrent-floating-telewindows-allowed)))
    (warn "Ignoring maximum-number-of-concurrent-floating-telewindows-allowed = ~d for version 3 OK file"
          maximum-number-of-concurrent-floating-telewindows-allowed)
    (setq maximum-number-of-concurrent-floating-telewindows-allowed 0)
    (setq maximum-number-of-concurrent-floating-tw2-allowed 0))
  (loop for ok being each class-instance of 'ok
        do (x34 ok secure? online? japanese? nupec? korean? license-option?
                gspan? javalink? javalink-professional? activeXlink? chinese?
                number-of-processes?
                maximum-number-of-concurrent-floating-telewindows-allowed
                maximum-number-of-concurrent-floating-tw2-allowed)))

;; Note: the main reason I switched this to not change this machine's OK was
;; that you G2 can sense a security violation and destroy your environment
;; when you go from a secure g2 to a non-secure g2.  This was a huge time
;; waster.  It seems generally wise not to change your own security as a
;; side-effect of updating the site.  (MHD 3/29/93)



;;; `Examine-stack-structure' (obscure name for fillout-g2-ok-objects) is a
;;; driver for unravel-trapped-errors that provides a convenient interface
;;; for making selected individual changes to the ok files. It had been
;;; a macro inside emit-text-based-ok-files but as that capability is being
;;; copied to make other sets of ok files it is now best as its own
;;; routine. The defaults are the values for a gensym developer's license
;;; for 5.1 or later.

#+development
(defun examine-stack-structure
       (&key (secure? nil)
             (online? t)
             (japanese? nil)
             (nupec? nil)
             (korean? nil)
             (license-option? nil) ; i.e. development
             (gspan? nil)
             (javalink? t)
             (javalink-professional? t)
             (activeXlink? t)
             (chinese? nil)
             (number-of-processes? 10)
             (maximum-number-of-concurrent-floating-telewindows-allowed 10)
             (maximum-number-of-concurrent-floating-tw2-allowed 10)) ; See note
  (unravel-trapped-errors
    secure? online? japanese? nupec? korean? license-option?
    gspan? javalink? javalink-professional? activeXlink? chinese?
    number-of-processes?
    maximum-number-of-concurrent-floating-telewindows-allowed
    maximum-number-of-concurrent-floating-tw2-allowed))

;; Note: The choice of ten is based on the observation (RP,VKP 6/29/98)
;; that such a relatively low number was sufficient for everyday operations
;; and we caught a bug the one time it was exceeded.




;;; `Generate-tw-ok' creates a tw.ok, writes it to the file named by
;;; namestring, from a site.ok file.  The tw.ok file will contain
;;; authorization codes for all machines in the site.ok file.  This
;;; function should be run from a breakpoint in a G2 process in which
;;; site.ok has been loaded.

(defun-allowing-unwind generate-tw-ok (namestring authorized-products number-of-processes?)
  (let ((output-stream? nil))
    (unwind-protect
       (progn
         (setq output-stream?
               (g2-stream-open-for-output namestring))
         (cond
           (output-stream?
            (loop with machine-id-a
                  for ok being each strict-class-instance of 'ok
                  as name-or-names = (name-or-names-for-frame ok)
                  as machine-name?
                     = (if (consp name-or-names)
                           (car name-or-names)
                           name-or-names)
                  with fill-in-counter? = 0
                  as fill-in-for-unknown-host-name? = nil
                  do (when (null machine-name?)
                       (incff fill-in-counter?)
                       (setq fill-in-for-unknown-host-name?
                             (intern (format nil "UNKNOWN-HOST-~d" fill-in-counter?)))
                       (cerror (format
                                 nil "Continue, filling in with the name ~s."
                                 fill-in-for-unknown-host-name?)
                               "There's no name for one of the OK objects (~s)" ok))
                     (setf machine-id-a
                           (wide-string-to-string
                             (get-slot-value ok 'machine-id)))
                     (write-authorization-code-to-tw-ok
                       output-stream?
                       (or fill-in-for-unknown-host-name?
                           machine-name?)
                       (take-whitespace-out-of-machine-id
                         machine-id-a)
                       authorized-products
                       number-of-processes?)
                  (reclaim-simple-gensym-string machine-id-a)))
           (t
            (format t "~%~%Can't open ~s!" namestring))))
      (if output-stream?
         (g2-stream-close output-stream?)))))


;;; `Write-authorization-code-to-tw-ok' ... writes machine-name in
;;; all lowercase.

(defun write-authorization-code-to-tw-ok
    (output-stream machine-name machine-id authorized-products
                   number-of-processes?)
  (if machine-id
      (let ((output-text-line
              (twith-output-to-text-string
                (cond
                  ((member 'floating authorized-products)
                   ;; Floating is handled specially as a pseudo product, ignoring
                   ;; any other options.  The intent is to take the authorization
                   ;; from the G2 server.
                   (tformat "~(~a~) ~a      floating" machine-name machine-id))
                  (t
                   (multiple-value-bind
                       (code-1 code-2 code-3 code-4)
                       (enlarge-telewindows-memory
                         machine-id nil nil
                         (compute-product-code authorized-products)
                         number-of-processes?)
                     (let ((name-text-string
                             (tformat-text-string "~(~a~)" machine-name))
                           (id-text-string
                             (tformat-text-string "~a" machine-id))
                           (codes-text-string
                             (tformat-text-string
                               "~d ~d ~d ~d ~d     ~a"
                               code-1 code-2 code-3 code-4
                               (check-small-workspace
                                 machine-id code-1 code-2 code-3 code-4 nil nil
                                 authorized-products
                                 number-of-processes?)
                               (or number-of-processes? ""))))
                       (tformat "~a " name-text-string)
;                       (loop repeat (- 20 (length name-text-string))
;                             do (twrite-character #\space))
                       (tformat "~a " id-text-string)
;                       (loop repeat (- 32 (length id-text-string))
;                             do (twrite-character #\space))
                       (tformat "~a " codes-text-string)
;                       (loop repeat (- (* 9 5) (length codes-text-string))
;                             do (twrite-character #\space))
                       (reclaim-text-string name-text-string)
                       (reclaim-text-string id-text-string)
                       (reclaim-text-string codes-text-string)
                       (loop for product in authorized-products
                             do (tformat
                                  "~(~a~) "
                                  (case product
                                    (restricted-use-option 'restricted-use)
                                    (runtime-option 'runtime)
                                    (embedded-option 'embedded)
                                    (t product))))))))))) ; japanese, korean; etc?
        (g2-stream-write-line output-text-line output-stream)
        (reclaim-text-string output-text-line))
      (cerror "Continue, skipping this machine's OK."
              "No machine id for ~a."
              machine-name)))

;; For japanese, this has to be modified to pass the appropriate args to
;; enlarge-telewindows-memory and check-small-workspace.  Also, the word
;; "japanese" has to be included in the format string.




#+development
(defun-allowing-unwind generate-t2-ok-file ()
  ;; This is a C&S of generate-tw-ok. There appear to be too many essential
  ;; differences to allow them to be collapsed in one abstraction, especially
  ;; since today the ok objects are generated from a list and all will have
  ;; names and a simple format.
  (let ((output-stream? nil)
        (namestring
          (twith-output-to-gensym-string
            (tformat "~a~at2~a.ok"
                     host-part-of-ok-pathname-string
                     directory-part-of-ok-pathname-string
                     site-ok-file-version-extension))))
    (unwind-protect
     (progn
       (setq output-stream? (g2-stream-open-for-output namestring))
       (cond
         (output-stream?
          (loop with narrow-machine-id
                with wide-machine-id
                for ok being each strict-class-instance of 'ok
                as machine-name = (name-or-names-for-frame ok)
                do
            (setq wide-machine-id (get-slot-value ok 'machine-id))
            (setq narrow-machine-id (wide-string-to-string wide-machine-id))
            (let ((output-text-line
                    (twith-output-to-text-string
                      (multiple-value-bind (c1 c2 c3 c4 c5)
                          (compute-tw2-codes-1 wide-machine-id nil nil nil)
                        (tformat "~a" machine-name)
                        (tformat " \"~a\""
                                 (string-upcasew
                                   (take-whitespace-out-of-machine-id
                                     narrow-machine-id)))
                        (tformat "  ~d ~d ~d ~d ~d" c1 c2 c3 c4 c5)
                        (tformat " development")))))
              (g2-stream-write-line output-text-line output-stream?)
              (reclaim-text-string output-text-line)
              (reclaim-simple-gensym-string narrow-machine-id))))
         (t (format t "~%~%Can't open ~s!" namestring))))

      (reclaim-simple-gensym-string namestring)
      (when output-stream?
        (g2-stream-close output-stream?)))))



(defun take-whitespace-out-of-machine-id (machine-id)
  (loop with string-length = (length machine-id)
       as i from 0 below string-length
       while (member (char machine-id i) '(#\space #\tab))
       finally
         (if (not (=f i string-length))
             (return
               (values
                 (twith-output-to-text-string
                   (loop as character = (char machine-id i)
                         do (if (not (member character '(#\space #\tab)))
                                (twrite-char character))
                            (incff i)
                         until (=f i string-length)))
                 i)))))




(defun make-ok-file-namestring (name &optional backup-case? override-version-extension?)
  (format nil "~a~a~(~a~a~)~a"
          host-part-of-ok-pathname-string
          directory-part-of-ok-pathname-string
          name
          (or override-version-extension?
              site-ok-file-version-extension) ; bound by do-site-ok-version
          (if backup-case?
              type-part-of-backup-ok-pathname-string
              type-part-of-ok-pathname-string)))

#+development
(defun save-one-g2-ok-file (name)
  (let ((master-ok-namestring (make-ok-file-namestring name)))
    (when (probe-file master-ok-namestring)
      (rename-file
        master-ok-namestring
        (make-ok-file-namestring name t)))
    (refresh-window system-window)
    (save-ok-kb master-ok-namestring)))

;; TO DO: If save-kb fails, this currently does not have any knowledge of that
;; fact, so it might copy actually garbage files.  This is mitigated by the fact
;; that save-kb writes a temp file out completely and then renames.  But that's
;; not a complete solution.  Fix this!  Note also that a similar problem exists
;; with the function below, save-one-tw-ok-file, which calls generate-tw-ok but
;; may not always have been completely successful.  (MHD 10/1/92)

;; TO DO: Merge this and the function below, save-one-tw-ok-file, into one, or
;; at least abstract the common parts!  (MHD 10/1/92)

;; Consider moving all of this the the module SITE. (MHD 10/1/92)


#+development
(defun save-one-tw-ok-file (name authorized-products number-of-processes?)
  (let* ((master-ok-namestring (make-ok-file-namestring name)))
    (when (probe-file master-ok-namestring)
      (rename-file
        master-ok-namestring
        (make-ok-file-namestring name t)))
    (generate-tw-ok
      master-ok-namestring authorized-products number-of-processes?)))




;;; Check-if-version-is-ok-to-do-all-ok-updates checks to see if we are
;;; running the required version of G2, as given by the parameter
;;; required-g2-version-for-doing-all-ok-updates.  Currently, the required
;;; version is 3.0 Rev. 0.

(defparameter required-g2-version-for-doing-all-ok-updates
  (make-system-version
    3 0
    :quality release-quality
    :revision 0))


(defun system-version-is-3-0-rev-0-p ()
  (and (= (first required-g2-version-for-doing-all-ok-updates)
         (first current-system-version))
       (= (second required-g2-version-for-doing-all-ok-updates)
         (second current-system-version))
       (string-equal
        (alpha-or-beta-of-system-version
          required-g2-version-for-doing-all-ok-updates)
        (alpha-or-beta-of-system-version
          current-system-version))))

#+obsolete
(defun check-if-version-is-ok-to-do-all-ok-updates ()
  (cond
    ((system-version-is-3-0-rev-0-p)
     t)
    (t
     (cerror "Continue anyway, possibly creating compatibility problems."
            "This version, ~s, is not the right version to be updating ok ~
              files.  It's supposed to be version ~s.  It may create incompatible ~
              versions of the OK files."
            (write-system-version-to-string
              required-g2-version-for-doing-all-ok-updates)
            (write-system-version-to-string
              current-system-version))
     nil)))



;;; `do-all-ok-updates' emits one family of g2 & tw OK files for the
;;; version currently established in the dynamic extent.
;;; See: update-gensym-site-ok-file. Note that this version of the
;;; OK file emitter is for KB-based OKs. The version below is for
;;; text-based OKs.

#+development
(defun do-all-ok-updates ()
  (let ((number-of-processes? 10)
        (maximum-number-of-concurrent-floating-telewindows-allowed
          (if (<= 4 chaining-refresh-version)
              10
              0)))

    ;; Setup the defaults, particularly the KB packages
    (unravel-trapped-errors
      nil t nil nil nil nil ; secure? online? japanese? nupec? korean? license-option?
      nil nil nil nil nil   ; gspan? javalink? javalink-professional? activeXlink? chinese?
      number-of-processes?
      maximum-number-of-concurrent-floating-telewindows-allowed
      0 )  ; the maximum number of floating tw2.

    (authorize-all-machines-for-all-gensym-products)  ;; Only done once.

    ;; Emit many OK files:
    ;;   g2{d,ru,rt,e}f{0,1,2,10}v{4,5}.ok
    ;;   g2{d,ru,rt,e}v3.ok
    (loop
      with file-name-template = (if (<= 4 chaining-refresh-version)
                                    "g2~af~d" ;; We have floating TW.
                                    "g2~a"
                                    )
      for maximum-number-of-concurrent-floating-telewindows-allowed
              in (if (<= 4 chaining-refresh-version)
                     '(0 1 10)
                     '(0))
          do
      (loop
        for g2-license-type in '(development restricted-use runtime embedded)
        as name-fragment    in '("d"         "ru"           "rt"    "e")
        do (unravel-trapped-errors
             nil t nil nil nil
             (case g2-license-type
               (development nil)
               (t g2-license-type))
             nil nil nil nil nil
             number-of-processes?
             maximum-number-of-concurrent-floating-telewindows-allowed
             0)
           (save-one-g2-ok-file
             (format
               nil file-name-template name-fragment
               maximum-number-of-concurrent-floating-telewindows-allowed))))

    ;; Emit one Japanese OK file: g2j.ok
    (unravel-trapped-errors
      nil t t nil nil nil
      nil nil nil nil nil
      number-of-processes?
      maximum-number-of-concurrent-floating-telewindows-allowed
      0)
    (save-one-g2-ok-file "g2j")

    ;; Runtime: g2rt
    (unravel-trapped-errors
      nil t nil nil nil 'runtime
      nil nil nil nil nil
      number-of-processes?
      maximum-number-of-concurrent-floating-telewindows-allowed
      0)
    (save-one-g2-ok-file "g2rt")

    ;; Secure: g2s
    (unravel-trapped-errors
      t t nil nil nil nil
      nil nil nil nil nil
      number-of-processes?
      maximum-number-of-concurrent-floating-telewindows-allowed
      0)
    (save-one-g2-ok-file "g2s")

    ;; Back to standard ok file.
    (unravel-trapped-errors)

    ;; Generate TW OK files:
    (when (<= 4 chaining-refresh-version)
      (save-one-tw-ok-file "twf" '(floating) 10))
    (loop
      for number-of-processes in '(1 2 10) doing
      (loop
        for (name products)
            in `(("tw" nil)
                 ("twj" (japanese))
                 ("twk" (korean))
                 ("twjk" (japanese korean))
                 ("twru" (restricted-use-option))
                 ("twd" nil))
        as fname = (format nil "~ap~a" name number-of-processes)
        do (save-one-tw-ok-file fname products number-of-processes)))))

;; Note A: floating isn't really a product but...




;;; `Emit-text-based-v[5,51,6]-ok-files' generates a family of text based OK files
;;; for G2.  It works by filling out the OK objects of an old style G2, and then
;;; writing those into a text formated file. The difference between the two
;;; is in the values for the authorized products: in v5 they are (online gspan),
;;; in v51 they are (online jl jp ax). The v51 values are the default. In v5, the
;;; calls to examine-stack-structure include the needed overrides as well as
;;; the substantive parts that are common to it and v51.

#+development
(defun emit-text-based-v51-ok-files ()

  (examine-stack-structure) ; Make the base OK files with default values

  (authorize-all-machines-for-all-gensym-products)  ;; Only done once.

  (examine-stack-structure :japanese? t)
  (write-current-ok-file (make-ok-file-namestring "g2j" nil "v51"))

  (examine-stack-structure :secure? t)
  (write-current-ok-file (make-ok-file-namestring "g2s" nil "v51"))

  (loop
    for floating-tw in '(0 1 10) doing
    (loop
      ;;         nil, d = development
      for k in '(nil          embedded runtime restricted-use-option)
      as mn in '("d"         "e"      "rt"    "ru"      ) doing

      (loop for floating-tw2 in '(0 1 10)
            do
        (examine-stack-structure
          :license-option? k
          :maximum-number-of-concurrent-floating-telewindows-allowed floating-tw
          :maximum-number-of-concurrent-floating-tw2-allowed floating-tw2)
        (write-current-ok-file
          (make-ok-file-namestring
            (format nil "g2~Af~dtw2~d" mn floating-tw floating-tw2)
            nil
            "v51"))))))

#+development
(defun emit-text-based-v5-ok-files ()
  ;; Make the base OK files with default values, overriding the v5.1 defaults
  ;; as needed.
  (examine-stack-structure
    :gspan? t  :javalink? nil  :javalink-professional? nil  :activeXlink? nil
    :maximum-number-of-concurrent-floating-tw2-allowed 0)

  (authorize-all-machines-for-all-gensym-products)

  (examine-stack-structure
    :japanese? t
    :gspan? t  :javalink? nil  :javalink-professional? nil  :activeXlink? nil
    :maximum-number-of-concurrent-floating-tw2-allowed 0)
  (write-current-ok-file (make-ok-file-namestring "g2j"))

  (examine-stack-structure
    :secure? t
    :gspan? t  :javalink? nil  :javalink-professional? nil  :activeXlink? nil
    :maximum-number-of-concurrent-floating-tw2-allowed 0)
  (write-current-ok-file (make-ok-file-namestring "g2s"))

  (loop
    for floating-tw in '(0 1 10) doing
    (loop
      ;;         nil, d = development
      for k in '(nil          embedded runtime restricted-use-option)
      as mn in '("d"         "e"      "rt"    "ru"      ) doing
      (examine-stack-structure
        :license-option? k
        :maximum-number-of-concurrent-floating-telewindows-allowed floating-tw
        :gspan? t  :javalink? nil  :javalink-professional? nil  :activeXlink? nil
        :maximum-number-of-concurrent-floating-tw2-allowed 0)

      (write-current-ok-file
        (make-ok-file-namestring
          (format nil "g2~Af~d" mn floating-tw))))))



;;; `Emit-text-based-v6-ok-files' is a copy-and-specialize variant of the
;;; 5/5.1 functions above. Like v5.1 it uses default values. It introduces
;;; a nomenclature and suite of alternatives for different combinations of
;;; language-enabled ok files: "g2{c, j, k}.ok

#+development
(defun emit-text-based-v6-ok-files ()

  (examine-stack-structure) ; Make the base OK files with default values

  (authorize-all-machines-for-all-gensym-products)  ;; Only done once.

  (make-v6-suite-of-CJK-ok-files)

  (examine-stack-structure :secure? t)
  (write-current-ok-file (make-ok-file-namestring "g2s" nil "v6"))

  (loop
    for floating-tw in '(0 1 10) doing
    (loop
      ;;         nil, d = development
      for k in '(nil          embedded runtime restricted-use-option)
      as mn in '("d"         "e"      "rt"    "ru"      ) doing

      (loop for floating-tw2 in '(0 1 10)
            do
        (examine-stack-structure
          :license-option? k
          :maximum-number-of-concurrent-floating-telewindows-allowed floating-tw
          :maximum-number-of-concurrent-floating-tw2-allowed floating-tw2)
        (write-current-ok-file
          (make-ok-file-namestring
            (format nil "g2~Af~dtw2~d" mn floating-tw floating-tw2)
            nil
            "v6"))))))

#+development
(defun make-v6-suite-of-CJK-ok-files ()
  (examine-stack-structure :chinese? t)
  (write-current-ok-file (make-ok-file-namestring "g2c" nil "v6"))
  (examine-stack-structure :japanese? t)
  (write-current-ok-file (make-ok-file-namestring "g2j" nil "v6"))
  (examine-stack-structure :korean? t)
  (write-current-ok-file (make-ok-file-namestring "g2k" nil "v6"))
  (examine-stack-structure :chinese? t :japanese? t)
  (write-current-ok-file (make-ok-file-namestring "g2cj" nil "v6"))
  (examine-stack-structure :chinese? t :korean? t)
  (write-current-ok-file (make-ok-file-namestring "g2ck" nil "v6"))
  (examine-stack-structure :japanese? t :korean? t)
  (write-current-ok-file (make-ok-file-namestring "g2jk" nil "v6"))
  (examine-stack-structure :chinese? t :japanese? t :korean? t)
  (write-current-ok-file (make-ok-file-namestring "g2cjk" nil "v6")))





#+development
(defun emit-t2-site-file ()
  ;; It's overkill to have this extra layer, but if we someday want to have
  ;; several variants on what spec a t2 site files has, as we do with tw
  ;; and g2 site files, then we'll need it.   If you examine the calling
  ;; thread for tw, you'll see it has one additional layer, but that one is
  ;; irrelevant today given that we're dealing with text files rather than
  ;; ok kbs.
  (generate-t2-ok-file))


#+development
(defun emit-text-based-tw-ok-files ()
  (save-one-tw-ok-file "twf" '(floating) 10) ;; Note A.
  (loop
    for number-of-processes in '(1 2 10) doing
    (loop
      for (name products) in '(("tw" nil)
                               ("twj" (japanese))
                               ("twk" (korean))
                               ("twjk" (japanese korean))
                               ("twru" (restricted-use-option))
                               ("twd" nil))
      as fname = (format nil "~ap~a" name number-of-processes)
      do (save-one-tw-ok-file fname products number-of-processes))
    (when (>=f 6 ok-site-file-version)
      (loop
        for (name products) in '(("twc" (chinese))
                                 ("twcj" (chinese japanese))
                                 ("twck" (chinese korean))
                                 ("twcjk" (chinese japanese korean)))
        as fname = (format nil "~ap~a" name number-of-processes)
        do (save-one-tw-ok-file fname products number-of-processes)))))

;; Note A: floating is actually the absence of any authorization.
;; it doesn't really have a process limit.




;;; `OK-Match' collects every OK object whose name or names contain the
;;; sequence of characters in each element of name-string-or-strings,
;;; which can be a single symbol or string, or a list thereof.

;;; For example, if there were an ok named OK-FOR-PORTUGAL, then
;;;
;;;   (ok-match 'por)
;;;
;;; would list it.  This is useful for administering the G2.OK file,
;;; as it allows you to see if a machine with a given name has already
;;; been authorized, or if a given name has already been used.

(defun ok-match (name-string-or-strings)
  (if name-string-or-strings
      (loop for ok being each class-instance of 'ok
           as name-or-names = (name-or-names-for-frame ok)
           when (cond
                  ((null name-or-names)
                   nil)
                  ((atom name-or-names)
                   (if (atom name-string-or-strings)
                       (search (string name-string-or-strings)
                               (string name-or-names)
                               :test #'string-equal)
                       (loop for name-string in name-string-or-strings
                             thereis
                               (search (string name-string)
                                       (string name-or-names)
                                       :test #'string-equal))))
                  (t
                   (loop for name in name-or-names
                         thereis
                           (if (atom name-string-or-strings)
                               (search (string name-string-or-strings)
                                       (string name)
                                       :test #'string-equal)
                               (loop for name-string in name-string-or-strings
                                     thereis
                                       (search (string name-string)
                                               (string name)
                                               :test #'string-equal))))))
             collect ok)))


(defun ok-id-match (machine-id-string)
 (loop for ok being each class-instance of 'ok
       as machine-id? = (machine-id ok)
       when (and machine-id?
                 (normalized-string-equal
                   machine-id? machine-id-string))
         collect ok))







(defun make-ok-workspace-from-list (host-info-list)
  (let* ((workspace
           (make-new-top-level-kb-workspace 'kb-workspace nil 'ok)))
    (loop with left-edge
            = (+w (left-edge-of-block workspace)
                  (workspace-margin workspace))
          with top-edge
            = (+w (top-edge-of-block workspace)
                  (workspace-margin workspace)
                  100)                        ; not on top of name box
          for (host-name-string host-id-string) in host-info-list
          as counter from 1
          when (= (mod counter 15) 0)
            do (incf left-edge 200)
               (setq top-edge
                     (+w (top-edge-of-block workspace)
                         (workspace-margin workspace)
                         100))
          do (cond
               ((and (null host-name-string) (null host-id-string))
                (cerror
                  "continue with the rest"
                  "Null entry (~a ~a)"
                  host-name-string host-id-string))
               ((or (null host-name-string)
                    (null host-id-string)
                    (string= host-name-string "")
                    (string= host-id-string ""))
                (format t
                        "~%Warning: Null entry (~s ~s)"
                        host-name-string host-id-string))
               ((bogus-machine-id-string-p host-id-string)
                (format t
                        "~%Warning: Entry (~s ~s) is bogus!"
                        host-name-string host-id-string))
               (t
                (let ((ok (make-entity 'ok)))
                  (add-to-workspace ok workspace left-edge top-edge)
                  (setf (machine-id ok) (copy-text-string host-id-string))
                  (change-slot-value
                    ok
                    'name-or-names-for-frame
                    (intern-text-string        ; normalized here to uppercase
                      (copy-text-string-with-case-conversion
                        host-name-string :all)))
                  (setq top-edge (+w (bottom-edge-of-block ok) 50))))))))

(defvar bogus-machine-ids-list
  '("00FFFFFF4D00" "unknown" "none" "ERROR"))

(defun bogus-machine-id-string-p (machine-id-string)
  (or (< (normalized-string-length (stringw machine-id-string)) 3)        ; Ben's test (Mac Licensing version)
      (member machine-id-string
              bogus-machine-ids-list
              :test 'normalized-string-equal+)
      (search "error" shunned-machine-ids-list)))

(defun normalized-string-equal+ (a b)
  (normalized-string-equal (stringw a) (stringw b)))


#+development
(defun make-ok-kb-from-host-info-file (file-name)
  (let ((host-info-list (read-host-info-file-into-list file-name)))
    (clear-kb)
    (let ((clean-host-info-list
            (loop
              for entry in host-info-list
              as machine-id = (second entry)
              as shun? = (shunned-machine-id-string-p
                           (string-to-wide-string machine-id))
              when shun?
                do (format t "~%Shunned machine id:~S" entry)
              unless shun? collect entry)))
      (make-ok-workspace-from-list clean-host-info-list))))



;;; `Update-gensym-site-ok-file' is the main entry point of the
;;; site ok file generator.  It is called within a running G2,
;;; for example from a break on service-workstations.
;;;
;;; Currently (circa October 1996 and onwards), it is run via a shell
;;; script that is fired up by a deamon that runs nightly and looks for
;;; changes to the hostinfo file. See /home/siteok/ReadMe. The script loads
;;; the ls and g2 systems and then calls this function via a entry
;;; condition on a call to trace validate-mouse-pointers, which is reached
;;; soon after it does a launch-ab.
;;;
;;; A second script is responsible for taking the files that are created
;;; and moving them from where were originally put (currently /home/siteok
;;; /foundry) to various other locations where the default values of our
;;; environment variables expect to see them.
;;;
;;; This makes a large number of files, each containing an OK entry
;;; for every machine in the hostinfo file, by ringing the changes
;;; on a broad set of alternative values for the parameters that
;;; are governed by authorization strictures. There's a non-trivial
;;; amount of diskspace involved, so it's worth re-evaluating this
;;; particular set of choices at some point. (ddm 7/8/98)

;; This function is development only since it stands on other facilities
;; that are development only.

#+development
(defun update-gensym-site-ok-file (&optional hostinfo-pathname?)
  ;; First create the OK KB (as used in G2 V4 and earlier.
  (format t "~%Loading the hostinfo file.")
  (make-ok-kb-from-host-info-file
    (or hostinfo-pathname?
        (format nil "~ahostinfo" directory-part-of-ok-pathname-string)))

  (format t "~%~%Generating OK files for version 6")
  (do-site-ok-version (6 'any)
    (emit-text-based-v6-ok-files))

  (format t "~%~%Generating OK files for version 5 for 5.1 and later")
  (do-site-ok-version (5 '5.1-or-greater)
    (emit-text-based-v51-ok-files))

  (format t "~%~%Generating T2 OK files")
  (do-t2-site-ok-version 1
    (emit-t2-site-file))

  (format t "~%~%Generating OK files for version 5 prior to 5.1.")
  (do-site-ok-version (5 '5.0r3-or-less)
    (emit-text-based-v5-ok-files))

  (format t "~%~%Generating OK files for TW version 6")
  (do-site-ok-version (6 'any)
    (emit-text-based-tw-ok-files))

  (format t "~%~%Generating OK files for TW version 5")
  (do-site-ok-version (5 '5.0r3-or-less)
    (emit-text-based-tw-ok-files))

  (format t "~%~%Generating OK files for version 4.")
  (do-site-ok-version (4 'any)  ;; I.e. {g2,tw}*v4.ok
    (do-all-ok-updates))

  (format t "~%~%Generating OK files for version 3.")
  (do-site-ok-version (3 'any)  ;; I.e. {g2,tw}*v3.ok
    (do-all-ok-updates)))




;;; `Update-developer-site-v5-files' is a variation that makes only
;;; two files: the default settings for developers with or without
;;; an authorization for floating tw2 licenses.

#+development
(defun update-developer-site-v5-files (&optional hostinfo-pathname?)

  (format t "~%Loading the hostinfo file.~%")
  (make-ok-kb-from-host-info-file
    (or hostinfo-pathname?
        (format nil "~ahostinfo" directory-part-of-ok-pathname-string)))

  (authorize-all-machines-for-all-gensym-products)  ;; Only done once.

  (do-site-ok-version (5 '5.1-or-greater)
    (examine-stack-structure)  ; default values

    (format t "~%Generating OK files for G2 versions 5.1 or later~%")
    (write-current-ok-file (make-ok-file-namestring "g2" nil "v51")))

  (do-site-ok-version (5 '5.0r3-or-less)
    (examine-stack-structure ; move things back to the status quo ante
      :gspan? t  :javalink? nil  :javalink-professional? nil  :activeXlink? nil
      :maximum-number-of-concurrent-floating-tw2-allowed 0 )

    (format t "~%Generating OK files for G2 versions 5.0r3 or earlier")
    (write-current-ok-file (make-ok-file-namestring "g2")))

  'done)

;;; N.b. to make a site file for something other than the regular
;;; hostinfo file, e.g. one specific machine, just construct another
;;; file in the same style and supply it as the argument. Also set
;;; the symbol directory-part-of-ok-pathname-string to the location
;;; where you want the new ok file put since it probably is not the
;;; default.
;;;   The syntax is a series of lines, one per machine, where each
;;; line consists of the name of the machine followed by its id with
;;; a colon separating them and no extraneous space.
;;; e.g.
;;;   HQMKRAMER:000861b546c


;;; `Update-QA-site-file-suite' is what it says. The particular set of
;;; files this generates are the ones QA wants. This tends to be updated as
;;; releases go by and to be run, by hand, at the start of a QA period.

#+development
(defun update-QA-site-file-suite (&optional target-directory hostinfo-pathname?)
  (let ((directory-part-of-ok-pathname-string
          (or target-directory "/tmp/")))
    (format t "~%Loading the hostinfo file.~%")
    (make-ok-kb-from-host-info-file
      (or hostinfo-pathname?
          (format nil "~ahostinfo" directory-part-of-ok-pathname-string)))
    (format t "~%Authorizing all machines for all products~%")
    (authorize-all-machines-for-all-gensym-products)  ;; Only done once.

    (do-site-ok-version (5 '5.1-or-greater)
      (emit-QA-test-suite-of-ok-files))))


#+development
(defun emit-QA-test-suite-of-ok-files ()  ; all 5.1 files
  ;; initialize everyone to default settings
  (examine-stack-structure
    :gspan? t  :javalink? nil  :javalink-professional? nil  :activeXlink? nil)

  ;; A pair of TW site files
  (save-one-tw-ok-file "tw1" '() 1)
  (save-one-tw-ok-file "tw1-deployment" '(restricted-use-option) 1)

  ;; One set of Japanese and Korean
  (examine-stack-structure :japanese? t :online? t)
  (write-current-ok-file (make-ok-file-namestring (format nil "g2Jonline")))
  (examine-stack-structure :korean? t :online? t)
  (write-current-ok-file (make-ok-file-namestring (format nil "g2Konline")))

  ;; ring changes through the license types and process counts
  (loop
    for floating-tw-count in '(0 1)
    as floating-t2-count  in '(0 1)
    as processes-count      in '(1 10)   doing

    (loop for online-p in '(t      nil)
          as cn in        '(on     off)  doing

      (loop for k in '(nil          embedded runtime restricted-use)
            as mn in '("d"          "e"      "rt"    "ru"      )   doing

        (examine-stack-structure
          :online? online-p
          :license-option? k
          :number-of-processes? processes-count
          :maximum-number-of-concurrent-floating-telewindows-allowed floating-tw-count
          :maximum-number-of-concurrent-floating-tw2-allowed floating-t2-count)

        (write-current-ok-file
          (make-ok-file-namestring
            (format nil "g2~a-~aTW~aT2~a~a"
                    processes-count floating-tw-count floating-t2-count
                    mn cn)))))))




;;; `Update-t2-site-ok-file' is a standalone version of the calls that are
;;; part of update-gensym-site-ok-file.

#+development
(defun update-t2-site-ok-file (&optional hostinfo-pathname?)
  (format t "~%Loading the hostinfo file.")
  (make-ok-kb-from-host-info-file
    (or hostinfo-pathname?
        (format nil "~ahostinfo" directory-part-of-ok-pathname-string)))
  (format t "~%Starting the site file")
  (do-t2-site-ok-version 1
    (emit-t2-site-file)))


;;; This section is for the Bundling project. ddm 9/8/00 To do: revise the
;;; driver to optionally take it's family-ok-data from a file since this
;;; is a funny place to keep it.

#+development
(defparameter default-family-ok-data
  '((("G2" "Site: G2 Development") nil
     gensym-protools5 gensym-gda4
     gensym-gqs5                        ; GQS was not used for G2 Classic 5.1 (with the G2 5.1 component), but it has been added
                                        ;   because the GDA that goes with G2 Classic 5.2 needs it. (MHD 4/25/01)
     gensym-activexlink
     gensym-corbalink-dev-v1 gensym-corbalink-runtime-v1)
    (("G2" "Site: G2 Deployment") t
     gensym-gda4
     gensym-gqs5                        ; GQS was not used for G2 Classic 5.1 (with the G2 5.1 component), but it has been added
                                        ;   because the GDA that goes with G2 Classic 5.2 needs it. (MHD 4/25/01)
     gensym-activexlink
     gensym-corbalink-dev-v1 gensym-corbalink-runtime-v1)

    (("eSCOR"  "Site: e-SCOR") nil
      gensym-activexlink gensym-e-scor)
    (("eSCOR"  "Site: e-SCOR Deployment") t
      gensym-activexlink gensym-e-scor)

    (("Integrity-Core" "Site: Integrity Core") nil
     gensym-opexpkg1-v3)
    (("Integrity-Core" "Site: Integrity Core Deployment") t
     gensym-opexpkg1-v3)
    (("Integrity-Discovery" "Site: Integity Discovery") nil
     gensym-opexpkg2-v3)
    (("Integrity-Discovery" "Site: Integity Discovery Deployment") t
     gensym-opexpkg2-v3)
    (("Integrity-Premium" "Site: Integity Premium") nil
     gensym-opexpkg3-v3)
    (("Integrity-Premium" "Site: Integity Premium Deployment") t
     gensym-opexpkg3-v3)
    (("Integrity-Reasoner" "Site: Integrity Reasoner") nil
     gensym-opexpkg4-v3)
    (("Integrity-Reasoner" "Site: Integrity Reasoner Deployment") t
     gensym-opexpkg4-v3)

    (("NeurOn-Line-Premium" "Site: NOL Premium") nil
     gensym-protools5 gensym-gda4
     gensym-gqs5                        ; GQS was not used for G2 Classic 5.1 (with the G2 5.1 component), but it has been added
                                        ;   because the GDA that goes with G2 Classic 5.2 needs it. (MHD 4/25/01)
     gensym-activexlink gensym-nol4)
    (("NeurOn-Line-Premium" "Site: NOL Premium Deployment") t
     gensym-protools5 gensym-gda4
     gensym-gqs5                        ; GQS was not used for G2 Classic 5.1 (with the G2 5.1 component), but it has been added
                                        ;   because the GDA that goes with G2 Classic 5.2 needs it. (MHD 4/25/01)
     gensym-activexlink gensym-nol4)
    ))

#+development
(defun generate-bundle-ok-files (&optional target-directory? family-ok-data?)
  (let ((family-data (or family-ok-data? default-family-ok-data))
        (directory-part-of-ok-pathname-string
          (or target-directory?
              ;"/bt/ddm/tmp/bundle-ok-files/"
              "/home/development/installers/release-files/"
              )))
    (loop for bundle-data in family-data do
      (generate-bundle-site-file-suite bundle-data))))


#+development
(defun generate-bundle-site-file-suite (bundle-data)
  (let ((name-and-site-id (first bundle-data))
        (deployment-p (second bundle-data))
        (package-names (cddr bundle-data)))
    (clear-kb)
    (make-ok-workspace-from-list (list name-and-site-id))
    (authorize-all-machines-for-packages package-names)

    (do-site-ok-version (5 '5.1-or-greater)
      (emit-bundle-site-file-suite-of-ok-files (first name-and-site-id)
                                               deployment-p))))

#+development
(defun emit-bundle-site-file-suite-of-ok-files (family-name deployment-p)
  (loop for floating-tw-count
            in (if deployment-p
                   '(4 8 12 16 20 24 28 32)
                   '(1 2 3 4 5 6 7 8 9 10 12 16 20 24 28 32))
        as floating-t2-count = floating-tw-count
        do
    (examine-stack-structure
      :license-option? (if deployment-p 'restricted-use t)
      :number-of-processes? 1
      :javalink-professional? nil
      :activeXlink? nil
      :maximum-number-of-concurrent-floating-telewindows-allowed floating-tw-count
      :maximum-number-of-concurrent-floating-tw2-allowed floating-t2-count)

    (write-current-ok-file
      (make-ok-file-namestring
        (format nil "~a-~a-~a-"  ;; note
                family-name
                (if deployment-p "deployment" "development")
                floating-t2-count)))))

;; Note: make-ok-file-namestring will append "v5.ok" to this string





;;;; Interface to the Code Generator

(defmacro funcall-into-ls (function &rest args)
  `(progn
     (unless (fboundp ,function)
       (error "The system LS must be loaded to use this."))
     (funcall ,function ,@args)))



;;; License-option? can be EMBEDDED, RUNTIME, RESTRICTED-USE, or DEVELOPMENT (or
;;; nil, which is the same as DEVELOPMENT).
;;;
;;; Note that this doesn't, and should not, result in an OK taking effect when
;;; this is the OK for this machine.  (This means you cannot make your G2 secure
;;; or runtime-only by calling this, which is good.  You can get it to take
;;; effect by saving it and loading it, or by reparsing one of the slots.)


(defun x34 (ok &optional secure? online? japanese? nupec? korean? license-option?
               gspan? javalink? javalink-professional? activeXlink? chinese?
               number-of-processes?
               maximum-number-of-concurrent-floating-telewindows-allowed
               maximum-number-of-concurrent-floating-tw2-allowed)
  (declare (special
             ;; Variables in sequences2.lisp
             OK-AUTHORIZED-PRODUCTS
             OK-EXPIRATION-DATE?
             OK-MODIFIED
             OK-NUMBER-OF-PROCESSES-AUTHORIZED
             OK-MAKE-G2-SECURE?
             OK-MAXIMUM-NUMBER-OF-CONCURRENT-FLOATING-TELEWINDOWS-ALLOWED
             OK-MAXIMUM-NUMBER-OF-CONCURRENT-FLOATING-TW2-ALLOWED
             ok-site-file-version))
  (unless (boundp 'OK-AUTHORIZED-PRODUCTS)
    (error "X34 can not be called if a development g2 has not been loaded."))
  (when (machine-id ok)

    (let ((authorized-products
            (nconc
              (copy-list-using-slot-value-conses
                (if online?
                    '(online)
                    '(offline)))
              (copy-list-using-slot-value-conses
                (if chinese? '(chinese)))        ; Placing chinese first because
             (copy-list-using-slot-value-conses  ; the phrase "CJK" is standard
                (if japanese? '(japanese)))      ; in i18n texts.
              (copy-list-using-slot-value-conses
                (if korean? '(korean)))        ; by convention, put korean
                                        ;   after japanese by default when
                                        ;   there's an ordering choice
              (copy-list-using-slot-value-conses
                (if nupec? '(nupec)))
              (copy-list-using-slot-value-conses
                (when (< ok-site-file-version 5)
                  '(gspan)))
              ;; Apparently, gspan was included in all site files prior to
              ;; now (5.1r0). It had been folded in with the online option
              ;; in the clause that checks for Japanese. In version 5, the
              ;; clause below applies, which includes it only if requested.
              (copy-list-using-slot-value-conses
                (unless (< ok-site-file-version 5)
                  (when gspan? '(gspan))))
              (copy-list-using-slot-value-conses
                (when javalink? '(jl)))
              (copy-list-using-slot-value-conses
                (when javalink-professional? '(jp)))
              (copy-list-using-slot-value-conses
                (when activeXlink? '(al)))
              (if (and license-option?
                       (member license-option? '(embedded runtime restricted-use)))
                  (slot-value-list license-option?)))))
      (setf (authorized-products ok) authorized-products)
      (setbits (ok-slot-coordinator ok) ok-authorized-products))

    (setf (expiration-date? ok) nil)
    (clearbits (ok-slot-coordinator ok) ok-expiration-date?)

    (setf (number-of-processes-authorized ok) number-of-processes?)
    (if number-of-processes?
        (setbits (ok-slot-coordinator ok) ok-number-of-processes-authorized)
        (clearbits (ok-slot-coordinator ok) ok-number-of-processes-authorized))

    (setf (make-g2-secure? ok) secure?)
    (if secure?
        (setbits (ok-slot-coordinator ok) ok-make-g2-secure?)
        (clearbits (ok-slot-coordinator ok) ok-make-g2-secure?))

    (setf (maximum-number-of-concurrent-floating-telewindows-allowed ok)
          maximum-number-of-concurrent-floating-telewindows-allowed)
    (if (= maximum-number-of-concurrent-floating-telewindows-allowed 0)
        (clearbits (ok-slot-coordinator ok)
                   ok-maximum-number-of-concurrent-floating-telewindows-allowed)
        (setbits (ok-slot-coordinator ok)
                 ok-maximum-number-of-concurrent-floating-telewindows-allowed))

    (setf (maximum-number-of-concurrent-floating-tw2-allowed ok)
          maximum-number-of-concurrent-floating-tw2-allowed)
    (if (= maximum-number-of-concurrent-floating-tw2-allowed 0)
        (clearbits (ok-slot-coordinator ok)
                   ok-maximum-number-of-concurrent-floating-tw2-allowed)
        (setbits (ok-slot-coordinator ok)
                 ok-maximum-number-of-concurrent-floating-tw2-allowed))

    (multiple-value-bind (cx1 cx2 cx3 cx4 cx5)
        (let ((machine-id-a (wide-string-to-string (machine-id ok))))
          (multiple-value-prog1
              (funcall-into-ls
                'y17
                machine-id-a (authorized-products ok) (expiration-date? ok)
                (number-of-processes-authorized ok)
                (maximum-number-of-concurrent-floating-telewindows-allowed ok)
                (maximum-number-of-concurrent-floating-tw2-allowed ok))
            (reclaim-simple-gensym-string machine-id-a)))
      (setf (code-1 ok) cx1)
      (setf (code-2 ok) cx2)
      (setf (code-3 ok) cx3)
      (setf (code-4 ok) cx4)
      (setf (code-5 ok) cx5))
    (setbits (ok-slot-coordinator ok) ok-modified)))

;; Note that this no longer causes the side-effects, i.e., authorization, to
;; happen when the OK is for this machine.  If you want it for this machine, go
;; parse the one for this machine, or reload the resulting OK KB. (MHD 4/29/94)


(defun compute-product-code-function (x)
  (compute-product-code x))

(defun make-array-from-lisp-strings (x-a y-a)
  (let ((x-w (string-to-wide-string x-a))
        (y-w (string-to-wide-string y-a)))
    (prog1
        (make-array-from-strings x-w y-w)
      (reclaim-wide-string x-w)
      (reclaim-wide-string y-w))))

(defun modulo-string-hash-of-lisp-string (s1-a n)
  (let ((s1-w (string-to-wide-string s1-a)))
    (prog1 (modulo-string-hash s1-w n)
      (reclaim-wide-string s1-w))))

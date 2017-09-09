;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module G2-FINAL

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David and Ben Hyde

#+development
(defun legal-non-copied-slot-value-p (slot-value)
  (or (partial-command-p slot-value)
      (menu-description-p slot-value)
      (workstation-p slot-value)
      (connection-p slot-value)
      (simulation-info-p slot-value)
      (graph-rendering-p slot-value)
      (pseudo-frame-p slot-value)
      (snapshot-of-block-p slot-value)
      (remote-procedure-name-p slot-value)
      (g2ds-server-connection-p slot-value)
      (functionp slot-value)
      (frame-or-deleted-frame-p slot-value)
      (slot-description-p slot-value)        ; in changed-slots-to-represent only
      ))

;;; generate stack-instruction expansions for compilation to C. This needs to
;;; be done late so that calls to expand-lookup-slot-reference will be able
;;; to see all defined classes, which it needs in order to do the right thing.

(defvar ensure-expanded-instruction-macros-has-run-p nil)

(defun ensure-expanded-instruction-macros ()
  (unless ensure-expanded-instruction-macros-has-run-p
    (setq ensure-expanded-instruction-macros-has-run-p t)
    #+compiled-code-saving-is-initially-enabled
    (generate-expanded-instruction-macros t)))

;;; The following loop sets the lookup-slot-optimizable-default properities
;;; to 'no of slots that cannot take advantage of lookup-slot access optimization
;;; because their default values can be changed at runtime.

#-no-macros
(loop for class being each unoptimized-subclass of 'item
      do
  (loop for slot-description in (slot-descriptions (class-description class))
        for slot-name = (pretty-slot-name slot-description)
        do
    (when (and (get-slot-feature-if-any class slot-name 'user-overridable)
               (lookup-slot-from-features-p (slot-features slot-description)))
      (setf (get slot-name 'lookup-slot-optimizable-default) 'no))))

;;; The following function call checks that optimizations for lookups to the
;;; class description of variables have been correctly installed.  Within
;;; FRAMES1 there is a call to a macro declare-optimized-class-description-
;;; lookup.  This macro takes symbols which should name classes, and defines
;;; variables to cache the class descriptions of those variables.  The caching
;;; occurs in the macro expansion of def-class.  However, it is possible for a
;;; symbol to be included in this list which is not actually defined as a class.
;;; The call to the following function checks for that circumstance in
;;; development loads and prints a warning if any of those classes are not
;;; defined.

#+development
(check-class-description-variables)

#+development
(setq strange-cons (cadr (aref (class-description 'block) 4)))

;;;; Assorted Checks and Table Building.

;;; See `validate-*features*' in FEATURES for more infomation.

#+development
(validate-*features*)

;;; Setup Class `Method Tables'.
(initialize-or-update-method-tables-of-class-descriptions 'root)
(setq system-class-method-tables-processed? t)
(setq system-class-method-tables-processed? t)

;;; Check for `Orphaned Methods' i.e. those defined on classes
;;; that were never defined.

#+development
(do-each-class-method-name (method-name)
  (loop for presumabably-a-class-name in (classes-which-define method-name)
        do
    (unless (class-description presumabably-a-class-name)
      (warn
        "A ~S method exists on ~S, but that class does not exist."
        method-name presumabably-a-class-name))))

;;; Set Up Compiler's Agenda of Role Dispatch Functions
;; this better not be a temporary consing context
;; right here while evaluating a top-level form.

(validate-static-evaulate-role-dispatcher)

(check-scheduled-task-names)

#+development
(fill-defun-simple-table)

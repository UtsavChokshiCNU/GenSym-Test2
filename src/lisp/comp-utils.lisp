;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module COMP-UTILS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Jim Allard, Chris Morel








;;;; Forward References



;;; In SETS

(declare-forward-reference reclaim-evaluation-value function)
(declare-forward-reference write-type-specification function)
(declare-forward-reference type-specification-subtype-p function)
(declare-forward-reference type-specifications-could-intersect-p function)

;;; In PROC-COMP

(declare-forward-reference write-procedure-statement function)
(declare-forward-reference register-goto-tag-address function)
(declare-forward-reference generate-new-variable-spot function)
(declare-forward-reference environment-index-ok-in-this-context? function)
(declare-forward-reference mangle-tag-in-context function)
(declare-forward-reference inlining-data-recieved-value-compilations? function)

;; In PLACES

(declare-forward-reference denote-component-of-block function)

;; In FILTERS

(declare-forward-reference block-can-be-dependent-p function)
(declare-forward-reference block-is-unstable-p function)
(declare-forward-reference block-has-stable-heirarchy-p function)
(declare-forward-reference block-is-optimizable-p function)

;; In INSTALL

(declare-forward-reference check-for-undefined-instance-name function)
(declare-forward-reference check-for-valid-method function)
(declare-forward-reference check-for-cached-name-undefined-instance function)
(declare-forward-reference check-for-cached-attribute function)
(declare-forward-reference check-for-undefined-class function)
(declare-forward-reference check-for-undefined-attribute function)
(declare-forward-reference check-for-undefined-attribute-of-class function)
(declare-forward-reference check-for-undefined-class-qualified-method function)
(declare-forward-reference
  check-for-undefined-class-qualified-attribute-of-class function)
(declare-forward-reference
  check-for-undefined-class-qualified-attribute function)
(declare-forward-reference compiled-item-being-analyzed variable)
(declare-forward-reference check-for-valid-procedure-call function)
(declare-forward-reference check-for-valid-function-call function)
(declare-forward-reference check-undefined-instances-of-class function)
(declare-forward-reference check-undefined-instances-of-type function)
(declare-forward-reference delete-as-item-referring-to-name? variable)
(declare-forward-reference add-or-delete-as-item-referring-to-name function)
(declare-forward-reference analyze-compiled-items-for-consistency function)
(declare-forward-reference check-for-valid-stable-compile-time-selected-method
                           function)

;; In PROC-UTILS

(declare-forward-reference procedure-method-name-function function)
(declare-forward-reference procedure-method-class-function function)
(declare-forward-reference get-specific-method function)
(declare-forward-reference get-named-procedure-methods-for-class function)
(declare-forward-reference block-can-be-inlined-p function)
(declare-forward-reference compress-annotation-info-for-saving function)







;;;; Compiler Utilities




;;; This file contains a collection of compiler utilities used by the compilers
;;; that emit byte-coded stack machine instructions.






;;;; New Parse Formats and Compiled Forms




;;; The function `compilations-up-to-date-p' is used in slot putters to identify
;;; if the current KB was saved in a version of G2 whose compilations are not
;;; compatible with the compilations required in the current version of G2.
;;; This function should call a predicate which tests the KB-flags and possibly
;;; characteristics of the given item, if provided.  If no item is given, then
;;; the test should be based solely on the KB-flags, and should return true if
;;; compilations of any item had changed.

;;; Each time the output of the compiler is changed in a non-upwardly compatible
;;; way, such as changing the instruction numbers or fixing a bug in the output
;;; of a compiler, then the predicate tested by this function must be updated,
;;; forcing recompilation of obsolete compiler outputs.

;;; Each time this is updated, please register a comment below briefly
;;; describing the change which required recompilation.  Note that this should
;;; not be done lightly, since knowledge bases which have been text stripped
;;; cannot be recompiled.  All knowledge base toolkit distributors will have to
;;; issue new release of their products each time we update this predicate.

;;; Before today, this predicate always returned false.  Turning on saving of
;;; stack evaluator compiled code and the new managed slot value floats.  -jra
;;; 8/25/91

;;; Updated the kb-flags to force compilations picking up some bug fixes over
;;; the last few weeks.  -jra 9/16/91

;;; Updated the little bugger again after fixing numerous "value of" problems.
;;; -jra 11/19/91

;;; Updated once again after shifting the evaluators down by 30 instructions to
;;; gain more space for the stack-instructions.  Other various fixes to the
;;; compiler were made.  - cpm, 12/13/91

;;; Updated again to propagate fixes to functions, a new format for surrounding
;;; var spot indices, and inner context switching for cells.  -jra 2/5/92

;;; Update again because of fixes to value-of, current-value-of, and
;;; simulated-value-of.  These evaluators were changed from source-nodes to
;;; special-form nodes.  These evaluators need to updated data-seeking or
;;; current-environment flags before the expression is evaluated.  There were
;;; also fixes to there-exists-literal.  In procedures, this statement, to be
;;; compatible with 2.1, allows undeclared local variables.  Also, a fix was
;;; made to readouts, to use push-value-or-none.  - cpm, 2/12/92

;;; Updated because of a fix to the minimum and maximum aggregator.  In the case
;;; where a domain was no item or no values were served, an extra value was
;;; being left on the stack.  - cpm, 2/24/92

;;; Updated because of a fix to nested every expressions around actions in
;;; rules.  - cpm & jra 3/3/92

;;; Updated to force through recompilation fixes for nested function calls,
;;; collection-time-of, expiration-time-of, and relation forward chaining bugs.
;;; -jra 4/6/92

;;; Updated to force through recompile after renaming struct to structure.  -jra
;;; 8/9/96

;;; Updated to force a recompile for methodized-actions -ajs 11/4/96
;;; Updated to force another recompile for methodized-actions.  - cpm, 11/26/96
;;; Updated to force another recompile to remove methodized-actions - ajs, 12/15/96

;;; This is mostly useful in development, when the stack-instruction language
;;; might be rapidly changing.

(defvar always-recompile-on-load nil)

;;; Unfortunately, once you set this to t in a delivery image, there's no
;;; way to set it to T again; if you try to merge in a kb that makes the
;;; system call that sets it back to nil, it tries and fails to recompile it.
;;; So we use this instead, which gets reset after a load.

(defvar recompile-on-next-load nil)

(defun compilations-up-to-date-p (item?)
  (declare (ignore item?))
  (and
    (instruction-argument-counts-not-on-stack-p)
    (not recompile-on-next-load)
    (not always-recompile-on-load)))




;;; The function `cached-parses-up-to-date-p' should be changed to use a new
;;; kb-flags predicate whenever we change the grammar that leads to parses of
;;; procedures.  These are cached on inlineable procedures in the parse-results?
;;; slot, and updating this predicate will cause old parses to be dropped from
;;; there.

;;; Wrote and updated this function when we rewrote inlining to add type
;;; checking for arguments and return values of inlined procedures.  -jallard &
;;; lgibson 10/3/97

(defun cached-parses-up-to-date-p (item?)
  (declare (ignore item?))
  (rewritten-procedure-inlining-p))




;;; The function `rule-compilations-could-be-out-of-date-p' takes no arguments
;;; and returns whether it is possible, though knowledge base kb-flags, that
;;; compilations could have been removed from rules.

;(defun rule-compilations-could-be-out-of-date-p ()
;  (not (compilations-up-to-date-p nil)))






;;; System and Global Variables and Properties




;;; The property `required-domain-types-of-role' takes a role name and returns a
;;; list of types for the domain values that this role requires.  Note that
;;; roles which are class iterations and attribute references should not be
;;; given to this property.

(def-global-property-name required-domain-types-of-role)




;;; The dynamic extent `working-on-lexical-computation-of-frame' provides the
;;; context necessary to generate warnings and error messages when a computation
;;; or compilation fails.

(def-named-dynamic-extent working-on-lexical-computation-of-frame
  (module comp-utils))




;;; The special variable `*current-computation-frame*' holds the kb-frame which 
;;; in
;;; turn held the lexical structure we are currently executing.  This is use in
;;; tracing and errors to generate denotations for the user.  It is not intended
;;; for other purposes.

;;; In some situations current-computation-component-particulars is used to
;;; provide a more refined indication of what part of the frame we are within.
;;; In some situations we don't have any "ovious" frame to refer to, and then
;;; we select some "useful" frame which might give the user a hint.

(defvar-of-named-dynamic-extent *current-computation-frame*
    working-on-lexical-computation-of-frame
  (process-binding nil)
  (global-binding nil))

;; Few of the places that bind this variable actually establish dynamic extent
;; using with-named-dynamic-extent. (ben 1/28/91)

;; For graphs (and other UI frames) it would be nice to be able to record
;; which substructure of the frame held the computation in question.  For example
;; "'the second plot' of graph-xxx-12"  (ben 1/28/91)




;;; The special variable `current-computation-component-particulars' holds a
;;; slot value which further specifies which component of the current
;;; computation frame is currently being executed.  This value is used by
;;; warning-message* or is part of the information given directly to the
;;; denote-component-of-block method.  If there are no component particulars for
;;; the class of the block in *current-computation-frame*, then this variable
;;; should be bound to NIL.

(defvar-of-named-dynamic-extent
  current-computation-component-particulars
  working-on-lexical-computation-of-frame
  (proclaim-special-globally t)
  (global-binding nil))




;;; The system variable `current-computation-instance' is used to hold the
;;; structure representing the currently executing invocation of a rule,
;;; procedure, formula, or whatever that is currently executing.

(def-system-variable current-computation-instance comp-utils nil)




;;; The computation-flag `force-new-request-for-value' can be used to force an
;;; attempt to obtain a new value in get-current-value.  When this is the case,
;;; only a value received in the current clock tick will ever be returned.  This
;;; flag is defined by def-computation-flags in TYPES.

(def-concept force-new-request-for-value)

(def-system-variable *variables-that-did-not-have-values* comp-utils nil)

(defmacro variables-that-did-not-have-values-variable (ignored-instance)
  (declare (ignore ignored-instance))
  '*variables-that-did-not-have-values*)






;;;; Compiler Conses




;;; The cons pool compiler-conses is used by some facilities in the compilers.
;;; Mostly it uses phrase conses.

(defconser compiler)






;;;; Compiler Error Reporting Utilities




;;; The macro `write-compiler-warning' takes a body of forms which write a
;;; warning message about the thing being compiled.  The warning message will be
;;; added to such that it shows the current statement being compiled.

;;; The function `compiler-warning' is similar to write-compiler-warning except
;;; that it takes a tformat control string and up to six optional arguments
;;; which are values for the directives in the format control string.

(defvar compiler-warnings nil)

(defmacro write-compiler-warning (&body forms)
  `(let ((candidate-string
           (twith-output-to-text-string
             (twrite-compiler-message-header)
             ,@forms)))
     (cond ((loop for a-string in compiler-warnings
                  do
              (when (string=w a-string candidate-string)
                (return t)))
            (reclaim-text-string candidate-string)
            nil)
           (t
            (setq compiler-warnings
                  (phrase-cons
                    candidate-string
                    compiler-warnings))
            nil))))

(defun compiler-warning (control-string &optional arg1 arg2 arg3 arg4 arg5 arg6)
  (write-compiler-warning
    (tformat control-string arg1 arg2 arg3 arg4 arg5 arg6)))




;;; The function `compiler-dependence-warning' issues a compiler warning about a
;;; missed chance for an optimization, due to an error between something stable
;;; and something dependent.

(defun compiler-dependence-warning
       (control-string &optional arg1 arg2 arg3 arg4 arg5 arg6)
  (write-compiler-warning
    (tformat control-string arg1 arg2 arg3 arg4 arg5 arg6)
    (twrite-string #w"  You must recompile this item after correcting the problem to achieve the optimization")))

(defconstant compiler-header-statement-length-limit 40)

(defun twrite-compiler-message-header ()
  (when (and current-computation-component-particulars
             (of-class-p *current-computation-frame* 'procedure))
    (twrite-string #w"from ")
    (let ((statement-string
            (twith-output-to-text-string
              (denote-component-of-block nil))))
      (twrite-character #.%\")
      (cond ((<f (text-string-length statement-string)
                 compiler-header-statement-length-limit)
             (twrite-string statement-string))
            (t
             (loop for index from 0 below compiler-header-statement-length-limit
                   do
               (twrite-character (charw statement-string index)))
             (twrite-string #w"...")))
      (twrite-character #.%\")
      (reclaim-text-string statement-string))
    (twrite-string #w": ")))




;;; The macro `write-compiler-error' takes a body of forms which write an error
;;; message.  This macro will cause the error message to be included in the
;;; frame notes for this frame, will abort compilation of the current statement,
;;; and will prevent the form from emitting code.  The compiler will attempt to
;;; compile the remaider of the expressions in the form to possibly produce more
;;; warning and error messages for the user.

(defvar compiler-errors nil)

(defmacro write-compiler-error (&body forms)
  `(let ((candidate-string
           (twith-output-to-text-string
             (twrite-compiler-message-header)
             ,@forms)))
     (cond ((loop for a-string in compiler-errors
                  do
              (when (string=w a-string candidate-string)
                (return t)))
            (reclaim-text-string candidate-string)
            nil)
           (t
            (setq compiler-errors
                  (phrase-cons
                    candidate-string
                    compiler-errors))
            nil))))




;;; The function `compiler-error' takes a tformat control string, and up to six
;;; arguments to the control string.  It is like write-compiler-error, but has
;;; the argument format of tformat instead of establishing a twriting
;;; environment.  This function returns NIL.

(defun compiler-error
       (control-string &optional arg1 arg2 arg3 arg4 arg5 arg6)
  (write-compiler-error
    (tformat control-string arg1 arg2 arg3 arg4 arg5 arg6)))




;;; The function `compiler-bug' is used to report messages about circumstances
;;; which should only happen when there is a bug in the compiler.  This function
;;; takes a string which is a noun naming the region of the compiler which has
;;; experienced a bug, such as "address resolver".  The second argument is a
;;; tformat control string for a sentence which says what went wrong.  The
;;; remaining (up to 6 arguments) are values for printing directives in the
;;; control string.

;;; The message will appear to the user as a compiler error would, in the notes
;;; of thier frame.

(defun compiler-bug
       (section-name control-string &optional arg1 arg2 arg3 arg4 arg5 arg6)
  (write-compiler-error
    (twrite-string #w"An error has just occurred in the compiler ")
    (twrite-string section-name)
    (twrite-string #w".  ")
    (tformat control-string arg1 arg2 arg3 arg4 arg5 arg6)
    (twrite-string #w"  Please report this bug to Gensym software support with ")
    (twrite-string #w"the source code which caused this message.")))




;;; The function `remove-compiler-error-and-warning-frame-notes' deletes the
;;; frame notes for general compiler warnings and error from the frame or
;;; component specified by current computation frame and current computation
;;; component particulars.

(defun remove-compiler-error-and-warning-frame-notes ()
  (let ((block *current-computation-frame*))
    (delete-frame-note-if-any 'compiler-warnings block)
    (delete-frame-note-if-any 'compiler-errors block)
    ;; Note that in 2.1 and previous releases, warnings of this sort were
    ;; included under the type procedure-compiler-errors and
    ;; procedure-compiler-warnings, and these also need to be removed.  -jra
    ;; 7/16/91
    (when (frame-of-class-p block 'procedure)
      (delete-frame-note-if-any 'procedure-compiler-warnings block)
      (delete-frame-note-if-any 'procedure-compiler-errors block))))




;;; The function `add-compiler-error-and-warning-frame-notes' takes the
;;; collected strings from the compiler-errors and compiler-warnings special
;;; variables and establishes those warnings and errors in the frame notes of
;;; the frame or component in the current computation variables.

(defun add-compiler-error-and-warning-frame-notes ()
  (when compiler-warnings
    (add-frame-note
      'compiler-warnings
     *current-computation-frame*
      (nreverse (copy-list-using-slot-value-conses compiler-warnings))
      t nil)
    (setq compiler-warnings nil))
  (when compiler-errors
    (add-frame-note
      'compiler-errors
     *current-computation-frame*
      (nreverse (copy-list-using-slot-value-conses compiler-errors))
      t nil)
    (setq compiler-errors nil)))

(defun compiler-errors? (frame)
  (memq 'compiler-errors (frame-status-and-notes frame)))


;;; The function `clear-compiler-errors' is used to clear all compiler error
;;; currently established.  This is used within compilers which may attempt to
;;; compile something, but have a fallback if the compile fails.  When the
;;; fallback is used, no compiler errors from the failed compile should be
;;; allowed to persist.

(defun clear-compiler-errors ()
  (loop for string in compiler-errors do
    (reclaim-text-string string))
  (setq compiler-errors nil))




;;; The frame note writers for the `compiler-errors frame note' and the
;;; `compiler-warnings frame note' print the warnings and errors generated by
;;; calls to compiler-error and compiler-warning.

;; Consider a linefeed at the beginning of a set of warnings or errors.  -jra &
;; mhd 12/11/91

(def-frame-note-writer compiler-warnings (warning-strings)
  (if (null (cdr warning-strings))
      (tformat "the compiler reported the following warning: ~a"
               (car warning-strings))
      (loop for warning in warning-strings
            for warning-index from 0
            initially
              (tformat "the compiler reported the following warnings: ")
            do
        (unless (=f warning-index 0)
          (twrite-string #w"; "))
        (tformat "(~a) ~a" (+f frame-note-index warning-index) warning)
            finally
              (incff frame-note-index-skip (length (cdr warning-strings))))))

(def-frame-note-writer compiler-errors (error-strings)
  (if (null (cdr error-strings))
      (tformat "the compiler reported the following error: ~a" (car error-strings))
      (loop for error in error-strings
            for error-index from 0
            initially
              (tformat "the compiler reported the following errors: ")
            do
        (unless (=f error-index 0)
          (twrite-string #w"; "))
        (tformat "(~a) ~a" (+f frame-note-index error-index) error)
            finally
              (incff frame-note-index-skip (length (cdr error-strings))))))




;;; The macro `with-compiler-error-reporting' should be wrapped around calls to
;;; compile-expression-to-byte-code-body.  First this macro removes any existing
;;; compiler warnings and errors from the current computation frame and
;;; component.  This macro will then bind variables necessary to allow calls to
;;; compiler-warning, compiler-error, and compiler-bug and execute the body of
;;; forms.  In an unwind-protect after the body has completed execution, this
;;; macro will install the warnings and errors onto the current computation
;;; frame and component particulars, and then return the values of the body.

;;; Note that this macro does not affect whether the frame or component is
;;; marked as bad.  That should is the job of the caller or body of this macro.

(defmacro with-compiler-error-reporting (&body forms)
  `(let ((compiler-errors nil)
         (compiler-warnings nil))
     (remove-compiler-error-and-warning-frame-notes)
     (unwind-protect
         (progn ,@forms)
       (add-compiler-error-and-warning-frame-notes))))






;;;; Compilation Environment




;;; While compiling there are two major classes of information that are kept in
;;; dynamic variables.  They are the code bodies produced by compilation of a
;;; procedure, and the labels defined within code bodies.  The generated set of
;;; code bodies each contain an environment description, instructions, a return
;;; value position, and a maximum received value count.  The labels descriptions
;;; contain the defined labels, the number of the code body they are within, and
;;; a flag saying whether this tag is the target of any JUMP instructions (i.e.
;;; branch instructions which transfer control between code bodies).

;;; For both code bodies and labels there are two lists which are used to keep
;;; track of them during a compilation.  One list is used to show the
;;; hierarchical nesting of lexical label sets and nesting of code bodies as a
;;; compilation proceeds.  The other list is used to keep a master list of the
;;; labels and code bodies that have been generated in total.

;;; The variable `goto-tags-in-compilation' contains a phrase cons list of
;;; tag entries.  Tag entries are structures which are described below.

(defvar goto-tags-in-compilation nil)




;;; The variable `lexically-visible-goto-tags' contains a phrase list of
;;; the procedure tag entries which are currently available for branches.  This
;;; variable is bound and mutated during compilation.  The procedure tag entries
;;; in this list are shared by the goto-tags-in-compilation list, and any
;;; entry listed here must also have already been entered in the
;;; goto-tags-in-compilation list.

(defvar lexically-visible-goto-tags nil)




;;; The variable `compiler-free-references' contains a phrase cons list of the
;;; entries for designations which are not local names to the procedure.  The
;;; elements of this list are themselves lists whose first element is the kind
;;; of free reference, one of either name, class, or class-and-attribute.  The
;;; second is then either the name, the class, or a cons of the class and
;;; attribute.  The rest of the lists are reserved for type information.

;; Better documentation about the free references is found below.

(defvar compiler-free-references nil)




;;; The variable `collecting-free-references' is true in free-reference
;;; collection and false elsewhere.

(defvar collecting-free-references nil)




;;; The variable `code-body-entries-in-compilation' is a phrase cons list of
;;; code body entries for the code bodies generated during the compilation of an
;;; item.  The entries are in the same order as the code bodies will be in the
;;; list of code bodies for the compiled item.  Therefore, the position of an
;;; entry in this list is the code body number for a code body.  Note that only
;;; procedures can have multiple code bodies within a single compiled entity.

(defvar code-body-entries-in-compilation nil)




;;; The variable `lexically-visible-code-bodies' contains a phrase
;;; list of the code body entries which are currently lexically visible during a
;;; compilation. The first entry in this list is the current code body.

(defvar lexically-visible-code-bodies nil)




;;; The structure `goto-tag-entry' is used to represent a procedure tag
;;; during compilation.  This structure will only be instantiated during a
;;; procedure compilation.  The slots are as follows:  Goto-tag-name
;;; contains the name of this tag, either an integer or a symbol.
;;; Goto-tag-code-body-entry contains a pointer to the code body entry
;;; structure from which this tag was generated.  Goto-tag-jump-referenced?
;;; is a flag indicating if this tag is referenced as the target of a jump
;;; instruction from a code body other than the one which contains this tag.
;;; Goto-tag-address contains the address of this tag when emitting code.
;;; Goto-tag-jump-address contains the address for jump instructions to
;;; this tag when emitting code.  This slot will be null when there are no jump
;;; references to this tag.

(def-structure (goto-tag-entry
                 (:constructor make-goto-tag-entry
                  (goto-tag-name goto-tag-code-body-entry)))
  goto-tag-name
  goto-tag-code-body-entry
  (goto-tag-referenced? nil)
  (goto-tag-jump-referenced? nil)
  (goto-tag-address nil)
  (goto-tag-jump-address nil))




;;; The structure `compiler-code-body-entry' is used to represent a code body
;;; during compilation.  This structure will only be instantiated during a
;;; procedure compilation.  Its slots are as follows:
;;; Compiler-code-body-instructions-so-far contains a phrase cons list in reverse
;;;   order of the instructions emitted for this code body.
;;; Compiler-code-body-maximum-received-value-count contains a count of the maximum
;;;   number of values which will be returned to this code body by calls to other procedures.
;;; Compiler-code-body-environment-description contains the environment
;;;   description for this code body.
;;; Compiler-code-body-surrounding-body-number? contains the number of a surrounding
;;;   code body, if there is any.  In some compiler environments, such as procedures
;;; Compiler-code-body-final-instructions contains the list of instructions in forward order after
;;;   optimizations have been performed.
;;; Compiler-code-body-byte-code-stream will hold a pointer to the emitter byte code stream
;;;   for this code body entry when needed in the emitters, as it is in procedures.
;;; Compiler-code-body-local-variable-info contains names and types for local
;;;   variables. Introduced to permit call inlining




(def-structure (compiler-code-body-entry
                 (:constructor make-compiler-code-body-entry
                  (compiler-code-body-environment-description
                    compiler-code-body-surrounding-body-number?)))
  (compiler-code-body-instructions-so-far nil)
  (compiler-code-body-maximum-received-value-count 0)
  compiler-code-body-environment-description
  compiler-code-body-surrounding-body-number?
  (compiler-code-body-entry-points nil)
  (compiler-code-body-frame nil)
  (compiler-code-body-error-handler-spec? nil)
  (compiler-code-body-final-instructions nil)
  (compiler-code-body-byte-code-stream nil)
  (compiler-code-body-argument-descriptions? nil)
  (Compiler-code-body-local-variable-info nil))




;;; The macro `compiler-code-body-entry-number' returns the number of the passed
;;; procedure code body entry.  This number is its position in the list of
;;; code-body-entries-in-compilation.

(defmacro compiler-code-body-entry-number (compiler-code-body-entry)
  `(position ,compiler-code-body-entry code-body-entries-in-compilation))




;;; The macro `with-compiler-goto-tags' binds the variables
;;; goto-tags-in-compilation and lexically-visible-goto-tags in preparation for
;;; compiling.

(defmacro with-compiler-goto-tags (&body forms)
  `(let ((new-goto-tag-counter 0)
         (goto-tags-in-compilation nil)
         (lexically-visible-goto-tags nil))
     (unwind-protect
       (progn ,@forms)
       (loop for tag in goto-tags-in-compilation do
         (reclaim-goto-tag-entry tag)))))


;;; The macro `enter-new-lexical-tag-layer' takes a body of forms.  It
;;; enters a new binding for lexically-visible-goto-tags, and executes the
;;; forms within that binding.  On exit from this binding, all tags newly
;;; declared inside this binding are removed.  Upon entrance to a new lexical
;;; layer, the statements within this layer should be processed to collect all
;;; procedure tags within it.
;; I think this macro is confusingly named.  It's for entering DEEPER (i.e
;; nested) lexical layers. -dkuznick, 7/30/98

(defmacro enter-new-lexical-tag-layer (&body forms)
  `(let ((lexically-visible-goto-tags lexically-visible-goto-tags))
     ,@forms))


;;; The macro `enter-separate-lexical-tag-layer' takes a body of forms.  It
;;; enters a NIL binding for lexically-visible-goto-tags, and executes the
;;; forms within that binding.  On exit from this binding, all tags newly
;;; declared inside this binding are removed.  Upon entrance to a new lexical
;;; layer, the statements within this layer should be processed to collect all
;;; procedure tags within it.

(defmacro enter-separate-lexical-tag-layer (&body forms)
  `(let ((lexically-visible-goto-tags nil))
     ,@forms))


;;; The macro `with-compiler-code-body-entries' binds the variables needed to
;;; generate code bodies in the compiler.

(defmacro with-compiler-code-body-entries (&body forms)
  `(let ((lexically-visible-code-bodies nil)
         (code-body-entries-in-compilation nil))
     (unwind-protect
       (progn ,@forms)
       (loop for code-body-entry in code-body-entries-in-compilation do
         (reclaim-compiler-code-body-entry code-body-entry)))))




;;; The parameter `maximum-code-body-count' determines the maximum number of
;;; code bodies within a single procedure.  This number is limited by the size
;;; of code constants which store indices to them, with the maximum count at
;;; 256.

(defparameter maximum-code-body-count 256)




;;; The macro `enter-new-code-body' takes as its first argument the
;;; environment description for the new code body to be entered, and as the rest
;;; of its arguments a body of forms which will emit instructions for this code
;;; body.  This macro creates the new compiler-code-body-entry, enters it into
;;; the rebound list of lexically-visible-code-bodies and the list of
;;; code-body-entries-in-compilation, binds a new lexical tag environment,
;;; and then executes the forms in its body.

(defmacro enter-new-code-body (environment-description &body forms)
  (let ((surrounding-entry? (gensym))
        (code-body (gensym)))
    `(let* ((,surrounding-entry? (current-compiler-code-body))
            (,code-body (make-compiler-code-body-entry
                          ,environment-description
                          (if ,surrounding-entry?
                              (compiler-code-body-entry-number
                                ,surrounding-entry?)
                              nil)))
            (lexically-visible-code-bodies
              (phrase-cons ,code-body lexically-visible-code-bodies)))
       (setq code-body-entries-in-compilation
             (nconc code-body-entries-in-compilation
                    (phrase-list ,code-body)))
       (check-for-new-code-body-errors)
       ;; If we are inlining, we need to make the receivers understand that
       ;; we're in a deeper code body -dkuznick, 8/6/98
       (if (inlining-context?)
           (adjust-nesting-of-inlining-data-received-value-compilations 1))
       (with-stack-frame-variables-environment
         (enter-new-lexical-tag-layer        ;SEPARATE-lexical.. instead? -dkuznick, 7/30/98
           ,@forms)))))

(defun-void check-for-new-code-body-errors ()
  (when (and (cdr code-body-entries-in-compilation)
             (not (frame-of-class-p *current-computation-frame* 'procedure)))
    (compiler-bug
      "nested code body establishment"
      "Attempting to create multiple code bodies within ~NF, when they ~
       can only exist within procedures."
     *current-computation-frame*))
  (when (>=f (length code-body-entries-in-compilation)
             maximum-code-body-count)
    (compiler-error
      "The maximum number of code bodies within a single procedure, ~a, ~
       has been exceeded.  Code bodies are generated by do in parallel ~
       and on error statements.  You must reduce the number of do in
       parallel and on error statements for this procedure to compile."
      maximum-code-body-count)))



;;; The macro `current-compiler-code-body' returns the procedure code body
;;; entry which is currently receiving emitted instructions.

(defmacro current-compiler-code-body ()
  `(car lexically-visible-code-bodies))




;;; The function `generate-list-of-lexically-visible-code-bodies' takes a
;;; compiler-code-body-entry and returns a phrase-cons list of the code bodies
;;; that lexically surround it.  This list will be equal to the value of the
;;; lexically-visible-code-bodies global variable during the first pass of the
;;; compiler, but this function is used to regenerate that list when entering
;;; the secondary passes of the compiler.  The given code-body will always be
;;; the first element of this list.

(defun-simple generate-list-of-lexically-visible-code-bodies
    (compiler-code-body-entry)
  (loop for code-body = compiler-code-body-entry
                      then (nth surrounding-code-body-number?
                                code-body-entries-in-compilation)
        for surrounding-code-body-number? =
        (compiler-code-body-surrounding-body-number? code-body)
        collect code-body using phrase-cons
        while surrounding-code-body-number?))




;;; The macro `base-code-body' returns the procedure code body entry which is
;;; the base code body (i.e. top level code body) of the currently compiling
;;; procedure.  This macro is intended to be used within procedure statement
;;; compilers.

(defmacro base-code-body ()
  `(car code-body-entries-in-compilation))




;;; The macro `within-base-code-body-p' is a predicate to be used within
;;; procedure statement compilers which returns whether or not emitted code is
;;; currently being sent into the base code body for the procedure.

(defmacro within-base-code-body-p ()
  `(eq (current-compiler-code-body) (base-code-body)))




;;; The macro `emit-instruction' takes &rest arguments of the elements in a
;;; compiler instruction, and adds that instruction to the end of the list of
;;; instructions emitted so far for the currently compiling code body entry.
;;; Compiler instructions differ from pseudo-code instructions only in that
;;; there are TAG instructions and that there are instructions which contain
;;; tags where instruction addresses will be placed.

(defmacro emit-instruction (&rest instruction-contents)
  `(emit-already-consed-instruction (phrase-list ,@instruction-contents)))




;;; The function `emit-already-consed-instruction' takes an instruction already
;;; consed up in phrase-conses, and adds it to the end of the list of
;;; instructions emitted so far for the currently compiling procedure.

(defun emit-already-consed-instruction (instruction)
  (let ((body (current-compiler-code-body)))
    (phrase-push instruction (compiler-code-body-instructions-so-far body))
    nil))



;;; The structure `compiler-instruction-stream' can be used as a target of
;;; emitted instructions when emitting to multiple targets.

(def-structure (pseudo-instruction-stream)
  (pseudo-instructions-in-stream nil))




;;; The function `merge-pseudo-instruction-stream' takes a pseudo instruction
;;; stream, merges its instructions into the instructions in the current code
;;; body, and reclaims the stream.

(defun merge-pseudo-instruction-stream (pseudo-instruction-stream)
  (let ((body (current-compiler-code-body)))
    (setf (compiler-code-body-instructions-so-far body)
          (nconc
            (pseudo-instructions-in-stream pseudo-instruction-stream)
            (compiler-code-body-instructions-so-far body)))
    (reclaim-pseudo-instruction-stream pseudo-instruction-stream)
    nil))




;;; The function `merge-pseudo-instruction-streams' takes two pseudo
;;; instructions streams, concatenates the instructions of the second onto the
;;; first, and reclaims the second.

(defun merge-pseudo-instruction-streams (target-stream consumed-stream)
  (setf (pseudo-instructions-in-stream target-stream)
        (nconc (pseudo-instructions-in-stream consumed-stream)
               (pseudo-instructions-in-stream target-stream)))
  (reclaim-pseudo-instruction-stream consumed-stream)
  nil)




;;; The function `emit-already-consed-instruction-to-stream' takes a
;;; pseudo-instruction-stream and an instruction, and emits the instruction into
;;; the stream.

(defun emit-already-consed-instruction-to-stream (stream instruction)
  (phrase-push instruction (pseudo-instructions-in-stream stream))
  nil)




;;; The macro `emit-instruction-to-stream' takes a pseudo-instruction-stream and
;;; a rest argument of the contents of the instruction.  This macro will combine
;;; the instruction contents into an instruction and emit that instruction into
;;; the stream.

(defmacro emit-instruction-to-stream (stream &rest instruction-contents)
  `(emit-already-consed-instruction-to-stream
     ,stream
     (phrase-list ,@instruction-contents)))




;;; The function `record-new-goto-tag' takes a tag name and records that
;;; tag in the full list of tags and in the list of tags currently lexically
;;; visible.  If this tag has already been declared anywhere in this procedure,
;;; then a compiler error is written.  If a duplicate tag is not currently in
;;; the lexical environment, it is added anyway to avoid further error messages.
;; There used to be a second test to see if the tag was a duplicate in
;; goto-tags-in-compilation which caused a compiler-error. That seemed wrong:
;; Who cares if there are duplicate tags in the compilation?  It should only
;; matter if they're lexically visible! Hence new definition below.
;; -dkuznick, 7/30/98

(defun record-new-goto-tag (tag-name)
  (if (loop for entry in lexically-visible-goto-tags
            thereis (eql (goto-tag-name entry) tag-name))
      (compiler-error
        "The tag ~a is declared more than once in this procedure."
        tag-name)
      ;; Mangle tag names so they don't clash between inlining and surrounding
      ;; contexts -dkuznick, 8/3/98
      (let ((new-entry (make-goto-tag-entry (mangle-tag-in-context tag-name)
                                            (current-compiler-code-body))))
        (setq lexically-visible-goto-tags
              (phrase-cons new-entry lexically-visible-goto-tags))
        (setq goto-tags-in-compilation
              (phrase-cons new-entry goto-tags-in-compilation)))))




;;; The function `jump-depth-for-tag?' should be called on all tags which are
;;; about to be referenced by branch statements.  If the referenced tag is
;;; within the current code body, then this function will return NIL.  If the
;;; referenced tag is within a lexically visible code body, this function will
;;; return the integer which is the number of levels of code which will need to
;;; be exited.  This number is the first argument to the JUMP instruction.  If
;;; the tag is not defined, then this function will return NIL and take care of
;;; issuing a compiler error to that effect.

(defun jump-depth-for-tag? (tag-name)
  (let ((tag-entry?
          (loop for entry in lexically-visible-goto-tags
                do
            (when (eql (goto-tag-name entry) tag-name)
              (return entry)))))
    (cond ((null tag-entry?)
           (write-compiler-error
             (if (loop for entry in goto-tags-in-compilation
                       thereis (eql (goto-tag-name entry) tag-name))
                 (tformat
                   "Illegal branch attempt to tag ~a.  Branches may not be ~
                    performed into the bodies of iteration statements, into IN ~
                    PARALLEL statements, or into the bodies of ON ERROR ~
                    statements."
                   tag-name)
                 (tformat "Illegal branch to the tag ~a, which is not defined."
                          tag-name)))
           nil)
          ((eq (current-compiler-code-body)
               (goto-tag-code-body-entry tag-entry?))
           (setf (goto-tag-referenced? tag-entry?) t)
           nil)
          (t
           (setf (goto-tag-jump-referenced? tag-entry?) t)
           (position (goto-tag-code-body-entry tag-entry?)
                     lexically-visible-code-bodies)))))






;;;; Tag Recorders




;;; Upon entry to a new lexical tag level, the statements of this level should
;;; be traversed, recording new tags.  Tag recorders are therefore defined for
;;; each statement which can produce tags.  These statements include, of course,
;;; the TAG-STATEMENT itself, as well as statements which can hold other
;;; statements, which themselves could generate tags.  The job of a tag
;;; collector is to traverse the statement for which it is defined, calling
;;; record-new-goto-tag on all new tags.  Statements which generate new
;;; lexical levels should not have tag collectors, but the compilers for these
;;; statements should generate new lexical tag layers and then record all tags
;;; within the new layer before going on to perform further compilation.

;;; To be perfectly clear, (there was a bug around this point on 1/31/91) every
;;; statement which contains other statements should either generate a new
;;; lexical level, or it should have a tag recorder defined for it.

;;; The global property `goto-tag-recorder' associates statement name
;;; symbols with the symbols which name a procedure tag recorder function.  See
;;; def-goto-tag-recorder for detials.

(def-global-property-name goto-tag-recorder)




;;; The macro `def-goto-tag-recorder' takes the name of a statement and a
;;; body of forms which implement recording for that statement.  This macro will
;;; cause a function to be defined which will be called with the variable
;;; statement bound to the statment to be traversed.

(defmacro def-goto-tag-recorder (statement &body forms)
  (let ((recorder (intern (format nil "~a-GOTO-TAG-RECORDER" statement))))
    `(defun-void-into-place
         (,recorder (goto-tag-recorder ',statement)) (statement)
       ,@forms)))




;;; The function `record-goto-tags' takes a statement and invokes recorder
;;; functions on that statement such that any defined procedure tags in that
;;; statement are registered via the function record-new-goto-tag.  It uses
;;; tag recorders for statements defined in def-goto-tag-recorder.

(defun-void record-goto-tags (statement)
  (let ((recorder? (goto-tag-recorder (car statement))))
    (when recorder?
      (funcall-simple-compiled-function
        (compiled-function-in-place recorder?) statement))
    nil))




;;; The function `generate-new-goto-tag' takes no arguments and returns a new
;;; tag suitable for GO TOs which is guaranteed new and unique for this
;;; procedure.  The bound variable `new-goto-tag-counter' is initially set to 0
;;; (negative numbers are not valid user goto tags) and decrements every time it
;;; is called.

(defvar new-goto-tag-counter -1)

(defun-simple generate-new-goto-tag ()
  (let ((new-tag (decff new-goto-tag-counter)))
    (record-new-goto-tag new-tag)
    new-tag))






;;;; Free References




;;; The stack compiler generates a description of the global names, classes, and
;;; attributes of classes that are referenced by a compiled entity.  This
;;; information is then used to update frame notes giving notification of
;;; undefined references.  As this facility is improved it will record
;;; dependencies on the existence of other types of data in a knowledge base,
;;; such as the definition of relations, rule categories, and other things I
;;; can't imagine right now.

;;; There are two portions to this facility.  The first is a set of functions
;;; used within the compiler to declare that the thing being compiled has a
;;; dependence on the elements given to the functions.  The second part is a
;;; facility for installing this information into global properties.

;;; The following list documents the types of free references and how they are
;;; handled by the global frame note facilities.  These references are recorded
;;; via calls to record-free-reference during compilation.

;;; NAME
;;;   Free references to names in procedures are registered under the type NAME,
;;;   and the reference given is simply the name symbol.  The function
;;;   check-for-undefined-instance-name is used to register the name globally.
;;;   NOTE: No longer recording new free-references of this type, but still
;;;   handling (analyzing, printing, etc.) existing free-references in KBs.
;;;   Refer to cached-name and stable-name free-references.  UPDATED NOTE: We
;;;   are still using the name reference for item references from pre-4.0 KB's.
;;;   But, the reference is also being used in 4.0 KB's when referring to a
;;;   method-declaration name in the method definition.  This was done instead
;;;   of using a new method reference because it is a reference to the name of
;;;   the method and not the method item.

;;; NAME-OF-CLASS-INSTANCE
;;;   Free references to names where the named object is expected to be an
;;;   instance of a particular class are registered under the type NAME-OF-
;;;   CLASS-INSTANCE.  The reference is a cons where the name symbol is the car
;;;   and the cdr contains a symbol naming the class.  The named item should be
;;;   an instance of the named class.
;;;   NOTE: This free-reference is not used (recorded) when the corresponding
;;;   stable free-reference, stable-name-of-class-instance, is used.

;;; NAME-OF-TYPE
;;;   Free references to names where the named object is expected to be an
;;;   instance of a particular type specification are registered under the type
;;;   NAME-OF-TYPE.  The reference is a cons where the name symbol is the car
;;;   and the cdr contains a type specification (see doc for type specifications
;;;   in SETS).  The named item should satisfy the given type spec.  NOTE: Note
;;;   that there is no corresponding reference to this called
;;;   stable-name-of-type, since that doesn't make sense in our dependency
;;;   tests.

;;; CACHED-NAME
;;;   The compilation of this item has been optimized to depend on the named
;;;   item being cached, for example, in a procedure constant vector.  The
;;;   reference is a cons where the name of the item is the car and the index of
;;;   the cached item is the cdr.  Note that the named item does not need to be
;;;   stable to use this optimization.

;;; STABLE-NAME
;;;   The compilation of this item has been optimized to depend on the
;;;   named item being stable.  The reference is the name symbol.

;;; STABLE-NAME-OF-TYPE
;;;   This reference CANNOT BE USED!  The only stability and name references
;;;   that should be used are stable-name and stable-name-of-class-instance.
;;;   This is because of the stability needs for classes that would be subparts
;;;   of the given type specification.  They would always end up being mentioned
;;;   in the stable-subclass free reference anyway, so this reference would make
;;;   no sense.

;;; STABLE-NAME-OF-CLASS-INSTANCE
;;;   The compilation of this item has been optimized to depend on the named
;;;   item being of a particular stable class .  The reference is a cons where
;;;   the name of the item is the car and a symbol naming the class is the cdr.

;;; CLASS
;;;   References to all classes are included in the type CLASS, and are the
;;;   class name symbol.  The function check-for-undefined-class is used to
;;;   register the reference globally.

;;; ATTRIBUTE-OF-CLASS
;;;   References to attributes of a class are registered under the type
;;;   ATTRIBUTE-OF-CLASS.  The reference is a cons whose car is the attribute
;;;   name symbol, and whose cdr is the class for the attribute reference, or
;;;   NIL if the class cannot be determined from the designation (this should be
;;;   rare or non-existent).  If the cdr of the reference has a class in it,
;;;   then this reference will be registered with check-for-undefined-attribute-
;;;   of-class, otherwise with check-for-undefined-attribute.

;;; CLASS-QUALIFIED-ATTRIBUTE-OF-CLASS
;;;   References to class-qualified attributes of a class are registered under
;;;   the type CLASS-QUALIFIED-ATTRIBUTE-OF-CLASS.  The reference is a list
;;;   whose first element is the attribute name symbol, whose second element is
;;;   the class-qualifier for the attribute, and whose third element is the
;;;   domain class for the attribute reference.
;;;   Note that CACHED-ATTRIBUTE also can record class-qualified attribute
;;;   expressions.

;;; ATTRIBUTE
;;;   References to attributes where the class of the object can only be
;;;   determined to be an item are registered under ATTRIBUTE.  The reference is
;;;   the symbol naming the attribute.

;;; CACHED-ATTRIBUTE
;;;   References to attributes of an item are registered under the type
;;;   CACHED-ATTRIBUTE.  The reference is a list of attribute-name, item-name?
;;;   generic-reference-class-name?, the index to the constant-vector that holds
;;;   the attribute information, a class-specific-attribute-class?, and
;;;   cached-attribute-cons-marker.  Note that the item or generic class name
;;;   can be nil, but not both.  The free reference applies to both named items
;;;   and generic references to items when the class is known.
;;;   A class-specific attribute reference refers to an attribute that is
;;;   defined for an item by the given class or superior class.
;;;   See the cached-attribute-value stack-instruction for more information.

;;; CLASS-QUALIFIED-METHOD
;;;   References to class-qualified methods of a class are registered under
;;;   the type CLASS-QUALIFIED-METHOD. The reference is a list
;;;   whose first element is the method name symbol, whose second element is
;;;   the class-qualifier for the method

;;; PROCEDURE-CALL, REMOTE-PROCEDURE-CALL
;;;   References via either START or CALL to specifically named procedures are
;;;   registered under the type PROCEDURE-CALL or REMOTE-PROCEDURE-CALL.  The
;;;   reference is a list whose first element is the procedure name, whose
;;;   second element is a list of procedure types of the arguments given to the
;;;   procedure.  The third element is a list of the types which are expected
;;;   back from the called procedure.
;;;   NOTE: These free-references are not used (recorded) when the corresponding
;;;   stable free-reference, stable-procedure-call and stable-remote-procedure-
;;;   call, are used.

;;; STABLE-PROCEDURE-CALL, STABLE-REMOTE-PROCEDURE-CALL
;;;   The compilation of this item has been optimized to depend on the existence
;;;   of a procedure and on the types of its arguments and return values.  The
;;;   reference is a list whose first element is the procedure name, whose
;;;   second element is a list of DEFINED procedure argument types.  The third
;;;   element is a list of DEFINED procedure return types.
;;;   NOTE: this differs from the non-stable procedure-call free-reference,
;;;   which stores the actual args and expected return values.

;;; STABLE-COMPILE-TIME-SELECTED-METHOD
;;;   The compilation of this item has been optimized to depend on a stable
;;;   method and on the hierarchy of that method being stable, such that the
;;;   method of the given class and argument specs is used when dispatching on
;;;   instances of the given first argument class.  This free reference is a
;;;   superset of the STABLE-PROCEDURE-CALL free reference with the additional
;;;   compile-time-method-selection requirements.  The format of the reference
;;;   is a list of the class of the selected method, the name of the selected
;;;   method, the class of the first argument to the method, a list of the
;;;   type-specifications of the arguments, and a list of the
;;;   type-specifications of the return types.

;; PROCEDURE-WITH-VALID-ENVIRONMENT
;;   The compilation of this item has been optimized to depend on the existence
;;   of a procedure and on the fact that the procedure does not make any
;;   procedure calls and that the procedure cannot invalidate its environment.
;;   The reference is a symbol, the procedure name.  Note that the procedure
;;   does not need to be stable because it does not make any procedure calls.
;;
;; Not in use.  Using procedure-flags instead and checking them at runtime
;; with procedure-environment-always-valid-p.  - cpm, 8/1/94

;; STABLE-PROCEDURE-WITH-VALID-ENVIRONMENT
;;   The compilation of this item has been optimized to depend on the existence
;;   of a procedure and on the fact that the procedure cannot invalidate its
;;   environment.  The reference is alist where the designation of the
;;   procedure is first, a list of the directly called named procedures are
;;   second, and a list of the indirectly called named procedures are third.
;;   This last list are the procedures called by the directly called
;;   procedures, the procedures called by these procedures, and so on.
;; - Not yet used.  - cpm, 8/1/94

;;; CLASSES-INTERSECT
;;;   References where designations returning an instance of one class which
;;;   then must instances of another class are registered here.  The reference
;;;   is a cons where the car is the symbol naming the class of the destination
;;;   for the instance, and the cdr is the symbol naming the class of the source
;;;   of the instance.  There are two checks that can be made for this
;;;   reference.  If the second class is a subclass of the first, then this
;;;   reference is OK in all situations.  If the first class is a subclass of
;;;   the second, then in some circumstances the instance returned might not
;;;   match the class of the destination.  This could be a level 3 warning for
;;;   the compile, if we had a better way of registering possible problems.  For
;;;   the moment only check that one of the classes is a subclass of the other.
;;;   Also note that this check will have to be rewritten when we have multiple
;;;   inheritance, so that if any subclass of one is a subclass of the other,
;;;   then they do indeed intersect.  -jra 4/1/91

;;; DATUM-TYPE
;;;   References to data types are registered with this reference type.  The
;;;   reference is simply the symbol which names this type.  This currently does
;;;   nothing, but should be improved to check against defined engineering types
;;;   and built in value types.

;;; RULE-CATEGORY
;;;   References to rule categories in INVOKE and FOCUS actions are recorded
;;;   under this type, with the references being the category symbols.  These
;;;   are not currently checked against global definitions.

;;; FUNCTION-CALL
;;;   References to functions are recorded in this type.  (Need to decide if
;;;   this is only user defined functions, or if system functions should be
;;;   placed here as well.  -jra 10/19/89) The reference is a list whose first
;;;   element is the symbol (or designation?) of the function, and the second
;;;   element of the list is the list of argument types.  If the type of an
;;;   argument expression to the function is not known, then NIL will be
;;;   included in that argument position.

;;; RELATION-NAME
;;;   References to named relations are recorded in this type.  The reference is
;;;   the symbol naming the relation used.  There currently is no global use of
;;;   this reference.

;;; PORT-NAME
;;;   References to ports of objects in connected to roles are recorded in this
;;;   type.  The reference is a cons of the port name symbol and the class name
;;;   symbol, if known.  If no class is known, then the cdr of the refernce cons
;;;   is NIL.

;;; SUBCLASS
;;;   References when one item is assigned into a local name with an item type,
;;;   or references where an operation with restricted domain is applied to an
;;;   item typed expression produce free reference dependancies that one class
;;;   be a subclass of another.  The reference is a cons where the superior
;;;   class is the car and the subclass is the cdr.
;;;   NOTE: This free-reference is not used (recorded) when the corresponding
;;;   stable free-reference, stable-subclass is used.

;;; STABLE-SUBCLASS
;;;   The compilation of this item has been optimized to depend on one class
;;;   being a subclass of another.  The reference is a cons where the superior
;;;   class is the car and the subclass is the cdr.

;;; STABLE-NOT-SUBCLASS
;;;   The compilation of this item has been optimized to depend on one class NOT
;;;   being a subclass of another.  The reference is a cons where the superior
;;;   class is the car and the subclass is the cdr.


;; Changes to free-references:

;; In the process of adding some new free-references, I've made the following
;; changes to existing free-references.

;; 1. Free References that are obsolete, but still supported.
;;   The function of some existing free-references will be included in some new
;;   free-references.  These old free-references should no longer be recorded
;;   during compilations.  But, note that to keep existing KBs working, these
;;   old free-references should not be removed and should still be analyzable,
;;   printable, etc.
;;   These old free references include: Name, replaced by cached-name; Attribute
;;   and Attribute-of-class, replaced by cached-attribute.

;; 2. Overlapping free-references
;;   Some free-references are also included in the analysis of other
;;   free-references.  In this case, only one of the free-refences is recorded.

;;   These include: procedure-call included in stable-procedure-call;
;;   remote-procedure-call included in stable-remote-procedure-call; Name and
;;   name-of-class-instance; include in stable-name and
;;   stable-name-of-class-instance, subclass, included in stable-subclass and
;;   stable-not-subclass (no uses of subclass were found);

;;   Note that the non-stable references are not obsolete.  They are still used
;;   to give warnings, even if the compiler is not making assumptions about a
;;   class being stable.

;; 3. New free-references: (NOT YET DONE)
;;    Possibly replace stable-procedure-with-valid-environment with procedure-
;;    with-valid-environment

;; 4. analyze-single-free-reference-for-consistency
;;    Add analysis for procedure-with-valid-environment.

;; 5. [STABLE-]PROCEDURE-WITH-VALID-ENVIRONMENT

;; The valid procedure-environment optimization NEEDS TO BE COMPLETED AND
;; REVIEWED.  Some outstanding issues are:

;; 5.1 Does the free-reference require stability?  The valid-environment
;; optimization is a run-time check and does not require a recompile of the
;; procedure or called procedures.  So, stability is not needed to force
;; recompiles.  But, stability may be needed to handle propogation of the
;; valid-environment procedure flags.

;; 5.2 Format of the free-reference: (<called-procedure-name-p1>
;; <directly-called-procedures-from-p1> <indirectly-called-procedures-from-p1>)
;; I'm not certain if the indirectly called procedures are needed.  This depends
;; on how the analysis of the free-references are handled.

;; 5.3 Free-reference analysis and propagation of procedure flags

;; 5.3.1 Propagate procedure flags up to callers.  I don't think that the flags
;; need to be propated down to called procedures.

;; 5.3.2 Check for cycles and recursion in the call tree.

;; 5.3.3 Alternate methods for maintaining the procedure-flags (i.e.,
;; propagation through the call tree) (note that one of the methods also
;; requires propagating inferior nodes through the call true):

;; 5.3.3.1 Each procedure in the call tree has a free-reference for every
;; procedure in its call tree.  The free-reference contains the name of every
;; procedure called directly or indirectly by this called procedure (cycles or
;; recursive references excluded).  This information is used to re-analyze all
;; of the superior nodes (procedures) in the calling tree when any of the
;; inferior (called) procedures change.

;; This is possible to do through the existing consistency analysis that
;; analyzes all items referring to a given name.  In this case, all superior
;; nodes will be listed as referring to an inferior node, even though they don't
;; reference all of them directly.  (The consistency-analysis may require a
;; change if the analysis is not ordered.  See the notes on disadvantages.)

;; The disadvantages of this method are the following:
;; - the memory cost of each procedure keeping lists of all directly and
;; indirectly called procedures (maybe, there could be a calling tree structure
;; that is share among the procedures?).
;; - the analysis of superior nodes depends on all inferiors.  So, either the
;; analysis must be ordered, with all inferiors done first, propagating the
;; flags upward (and somehow handling recursion and cycles), or it is does not
;; require ordering.  In the second case, the analysis of an inferior node would
;; have to trigger the analysis of superior nodes again, if necessary.  (This
;; requires a change to consistency analysis!)  Eventually, checking for cycles,
;; the analysis will "settle".
;; - if the calling tree of any inferior node changes, then we need to propagate
;; not only the procedure-flags, but the new inferior nodes up to all superior
;; nodes, so they can update their free-references.  This may be weird.  I don't
;; know if there is free-reference analysis that updates the free-reference!

;; 5.3.3.2 Each free-reference only keeps track of the called procedure and its
;; directly called procedures.  It does not keep reference to all the indirectly
;; called procedures.

;; To make this work, consistency analysis would need to be modified.  It can
;; currently analyze the calling procedure when a directly called procedure
;; changes.  But, the analysis does not get propagated further up the call tree.
;; We need to have this analysis trigger additional analysis on the callers of
;; the calling procedure, the callers callers, and so on.

;; This propagation of consistency analysis could be done by noting during an
;; analysis those items also needing to be analyzed.  In this case, these would
;; be the callers of the procedure being analyzed.  Then the additional analysis
;; would be done when the current analysis is completed.  The newly analyzed
;; items would then also note items needing additional analysis.

;;  To keep the analysis from running continually, we would need to test for
;;  cycles among the graph of called procedures.  A procedure call that is part
;;  of cycle, i.e., it was already analzyed to receive propagation of procedure
;;  flags, would only be re-analyzed when the flags of the called procedure
;;  related to valid procedure-environments have changed.

;; Disadvantages:
;; - Significant change to consistency-analysis.  It may be difficult to do or
;; just hack up the design of consistency analysis too much.

;; 5.3.4 When to propagate procedure changes

;; 5.3.4.1 Called procedure changes - propagate current procedure call tree.

;; 5.3.4.2 Procedure flags
;;   procedure-can-invalidate-environment
;;   procedure-contains-wait-state
;;   procedure-contains-indirect-procedure-call
;;   procedure-call-without-validated-environment




;;; The macro `with-compiler-free-reference-collection' is wrapped around the
;;; scope of code which will collect free references within compiles.

(defmacro with-compiler-free-reference-collection (&body forms)
  `(let ((compiler-free-references nil)
         (collecting-free-references t))
     ,@forms))



;;; The `cached-attribute-cons-marker' is used to identify cached-attribute
;;; free-references and constant-vector caches.

(defconstant cached-attribute-cons-marker '|cached-attribute-name|)



;;; The function `analyze-single-free-reference-for-consistency' is used to
;;; assert or retract a free reference during analysis of free reference sets.

;;; Note that stable free-references should not require the stable item to be
;;; OK.  For more information and an example of this, see check-for-valid-
;;; procedure-call, which is called by check-for-valid-stable-procedure-call.

(defun analyze-single-free-reference-for-consistency (parent type reference)
  #-mtg2 (declare (ignore parent))
  (case type
    ((name)
     (if (and (of-class-p compiled-item-being-analyzed 'method)
              (eq (procedure-method-name-function compiled-item-being-analyzed)
                  reference))
         ;; Note that methods are not named and so have a NAME free-reference to
         ;; the corresponding method-declaration.
         (check-for-valid-method reference)
	 (progn
	   (check-for-undefined-instance-name reference)
	   #+mtg2
	   (check-for-foreign-factions parent reference))))
    ((cached-name)
     (check-for-cached-name-undefined-instance
      #+mtg2 parent
      (car-of-cons reference) (cdr-of-cons reference))
     #+mtg2
     (check-for-foreign-factions parent (car-of-cons reference)))
    ((stable-name)
     (check-for-unstable-instance-name reference))
    ((name-of-class-instance)
     (check-undefined-instances-of-class
       (car-of-cons reference)
       (cdr-of-cons reference)))
    ((name-of-type)
     (check-undefined-instances-of-type
       (car-of-cons reference)
       (cdr-of-cons reference)))
    ((stable-name-of-class-instance)
     (check-for-unstable-instance-name-of-class
       (car reference) (cdr reference)))
    ((class)
     (check-for-undefined-class reference))
    (stable-subclass
     (let ((class (car reference))
           (subclass (cdr reference)))
       (check-for-unstable-class-and-subclass class subclass)))
    (stable-hierarchy
     ;; This free reference is obsolete.  After the next forced recompile post
     ;; 5.0 Rev. 1, you may then remove this clause from this function.
     ;; -jallard & lgibson 10/3/97
     nil)
    (inline
     (check-for-invalid-inlining reference))
    (stable-not-subclass
     (let ((class (car reference))
           (non-subclass (cdr reference)))
       (check-for-unstable-class-and-non-subclass class non-subclass)))
    ((attribute)
     (check-for-undefined-attribute reference))
    ((attribute-of-class)
     (if (cdr-of-cons reference)
         (check-for-undefined-attribute-of-class
           (car-of-cons reference) (cdr-of-cons reference))
         (check-for-undefined-attribute (car-of-cons reference))))
    ((class-qualified-attribute-of-class)
     (let ((attribute (first reference))
           (class-qualifier (second reference))
           (domain-class? (third reference)))
       (if domain-class?
           (check-for-undefined-class-qualified-attribute-of-class
             attribute class-qualifier domain-class?)
           (check-for-undefined-class-qualified-attribute
             attribute class-qualifier))))
    ((class-qualified-method)
     (let ((method (first reference))
           (class-qualifier (second reference)))
       (check-for-undefined-class-qualified-method
             method class-qualifier)))
    ((cached-attribute)
     (gensym-dstruct-bind ((attribute-name item-name? class-name?
                                          constant-vector-index
                                          class-specific-attribute-class?)
                          reference)
       (check-for-cached-attribute
         attribute-name item-name? class-name? class-specific-attribute-class?
         constant-vector-index)))
    ((procedure-call remote-procedure-call)
     (gensym-dstruct-bind ((name arg-types return-types) reference)
       (check-for-valid-procedure-call type name arg-types return-types nil nil)))
    ((stable-procedure-call stable-remote-procedure-call)
     (gensym-dstruct-bind ((name arg-types return-types) reference)
       (check-for-valid-stable-procedure-call type name arg-types return-types)))
    ((stable-compile-time-selected-method)
     (gensym-dstruct-bind ((selected-class method-name first-arg-class
                                          arg-types return-types)
                          reference)
       (check-for-valid-stable-compile-time-selected-method
         selected-class method-name first-arg-class arg-types return-types)))
    ((function-call)
     (gensym-dstruct-bind ((name arg-types) reference)
       (check-for-valid-function-call name arg-types)))
    (t
     nil)))

;; Add analysis for procedure-with-valid-environment.  -cpm, 6/17/93.

;; Note that cached-* analysis is not affected by more than one item having the
;; same name.  The reference to the named item should always be to the first,
;; older item.  Note that stable items cannot refer to an item with a duplicate
;; name.  - cpm, 8/1/94



;;; The macro bad-free-reference is used only within the function
;;; record-free-reference to issue a bug note about badly formed free reference
;;; declarations.

(defmacro bad-free-reference (type-of-reference reference)
  `(progn
     (compiler-bug
       "free reference recorder"
       "A reference of type ~a was badly formed: reference = ~a"
       ,type-of-reference ,reference)
     (return-from record-free-reference nil)))




;;; The variable `inhibit-free-reference-recording' is globally bound to
;;; NIL.  By binding it to T around a compilation, free references from
;;; that compilation will no longer be recorded.  This is used when
;;; compiling the known values only case of function defintions to
;;; inhibit warnings about variables not being parameters.

(defvar inhibit-free-reference-recording nil)




;;; The function `record-free-reference' is used to declare a free reference to
;;; some globally available thing during compilations.  It takes the type of
;;; reference, which must be a symbol, and the particular reference, which must
;;; be a value suitable for copying with copy-for-slot-value.  The types
;;; of free references which are available are documented at the top of this
;;; section.

;;; References given will be compared with EQUAL so that duplicate entries are
;;; not kept in the free references list, and some references may be transformed
;;; to one or more other references when an optimization of memory can be made
;;; without sacrificing declarative information.

;;; Types of reference not in the documentation list above can be given to this
;;; function, but they will be discarded.  This is done so that new types of
;;; free references can be easily put into the compiler before there are global
;;; properties with which to manage the frame notes about them.

;;; The entries placed into the compiler-free-references variable are lists
;;; whose car is the type and cdr is the reference.

(defun record-free-reference (type-of-reference reference)
  ;; Transform references according to what we can actually check for
  ;; right now.

  (unless inhibit-free-reference-recording
    (loop for transform-again? = nil do
      (case type-of-reference
        ((name stable-name)
         (unless (and reference (symbolp reference))
           (bad-free-reference type-of-reference reference)))
        ((name-of-class-instance stable-name-of-class-instance)
         (unless (and (consp reference)
                      (symbolp (car-of-cons reference))
                      (symbolp (cdr-of-cons reference)))
           (bad-free-reference type-of-reference reference))
         (when (eq (cdr-of-cons reference) 'item)
           (if (eq type-of-reference 'stable-name-of-class-instance)
               (setq type-of-reference 'stable-name)
               (setq type-of-reference 'name))
           (setq reference (car-of-cons reference))
           (setq transform-again? t)))
        ((name-of-type)
         (unless (and (consp reference)
                      (symbolp (car-of-cons reference))
                      (valid-type-specification-p (cdr-of-cons reference)))
           (bad-free-reference type-of-reference reference))
         (when (class-type-specification-p (cdr-of-cons reference))
           (setq type-of-reference 'name-of-class-instance)
           (setq reference
                 (phrase-cons (car-of-cons reference)
                              (type-specification-class-function
                                (cdr-of-cons reference))))
           (setq transform-again? t)))

        ((cached-name)
         (unless (and (consp reference)
                      ;; cached-name
                      (symbolp (car-of-cons reference))
                      ;; constant vector index
                      (fixnump (cdr-of-cons reference)))
           (bad-free-reference type-of-reference reference)))
        ((class)
         (unless (and reference (symbolp reference))
           (bad-free-reference type-of-reference reference))
         (when (and (system-defined-class-p reference)
                    (subclassp reference 'item))
           (return-from record-free-reference nil)))
        ((attribute-of-class)
         (unless (and (consp reference)
                      (and (car-of-cons reference)
                           (symbolp (car-of-cons reference)))
                      (symbolp (cdr-of-cons reference)))
           (bad-free-reference type-of-reference reference))
         (when (or (null (cdr-of-cons reference))
                   (eq (cdr-of-cons reference) 'item))
           (setq type-of-reference 'attribute)
           (setq reference (car-of-cons reference))
           (setq transform-again? t)))
        ((class-qualified-attribute-of-class)
         (unless (and (listp reference)
                      (and (first reference) (symbolp (first reference)))
                      (and (second reference) (symbolp (second reference)))
                      (and (third reference) (symbolp (third reference))))
           (bad-free-reference type-of-reference reference)))
        ((class-qualified-method)
         (unless (and (listp reference)
                      (and (first reference) (symbolp (first reference)))
                      (and (second reference) (symbolp (second reference))))
           (bad-free-reference type-of-reference reference)))
        ((attribute)
         (unless (and reference (symbolp reference))
           (bad-free-reference type-of-reference reference)))
        ((cached-attribute)
         (unless (and reference
                      (listp reference)
                      (and (first reference) ; attribute name
                           (symbolp (first reference)))
                      (symbolp (second reference)) ;item-name?
                      (symbolp (third reference)) ; class-name?
                      (numberp (fourth reference)) ;constant-vector-index
                                        ;class-specific-attribute-class?
                      (symbolp (fifth reference))
                      (eq (sixth reference) cached-attribute-cons-marker))
           (bad-free-reference type-of-reference reference)))
        ((procedure-call remote-procedure-call stable-procedure-call
                         stable-remote-procedure-call)
         (unless (and (consp reference)
                      ;; Procedure name
                      (symbolp (car-of-cons reference))
                      (consp (cdr-of-cons reference))
                      ;; List of argument types
                      (listp (second reference))
                      (loop for type in (second reference)
                            always (valid-type-specification-p type))
                      (consp (cddr reference))
                      ;; List of return types
                      (listp (third reference))
                      (loop for type in (third reference)
                            always (valid-type-specification-p type)))
           (bad-free-reference type-of-reference reference)))
        ((stable-compile-time-selected-method)
         (unless (and (listp reference)
                      (symbolp (first reference))
                      (symbolp (second reference))
                      (symbolp (third reference))
                      (loop for type in (fourth reference)
                            always (valid-type-specification-p type))
                      (loop for type in (fifth reference)
                            always (valid-type-specification-p type)))
           (bad-free-reference type-of-reference reference)))
;        ((stable-procedure-with-valid-environment)
;         (unless (symbolp reference)
;           (bad-free-reference type-of-reference reference)))
;        ((procedure-with-valid-environment)
;                                        ; Needs to be fixed to handle
;                                        ; second and third references.
;                                        ; - cpm, 7/30/93
;         (unless (symbolp reference)
;           (bad-free-reference type-of-reference reference)))
        ((function-call)
         (unless (and (consp reference)
                      ;; Function name
                      (symbolp (car-of-cons reference))
                      (consp (cdr-of-cons reference))
                      ;; List of argument types
                      (listp (second reference))
                      (loop for type in (second reference)
                            always (valid-type-specification-p type)))
           (bad-free-reference type-of-reference reference)))
        ((stable-subclass stable-not-subclass)
         (unless (and (consp reference)
                      ;; class
                      (symbolp (car-of-cons reference))
                      ;; subclass
                      (symbolp (cdr-of-cons reference)))
           (bad-free-reference type-of-reference reference)))
        ((stable-hierarchy)
         ;; The stable-hierarchy free-reference is obsolete, so always complain
         ;; if someone records a new reference to it. -jallard & lgibson 10/3/97
         (bad-free-reference type-of-reference reference))
        ((inline)
         (unless (and (consp reference)
                      (gensym-dstruct-bind ((class name arg-count md5) reference)
                        (and (symbolp class)
                             (symbolp name)
                             (fixnump arg-count)
                             (wide-string-p md5))))
           (bad-free-reference type-of-reference reference)))
        ;; Since we cannot check for kinds of reference other than those listed
        ;; here, ignore the reference and don't waste memory hanging on to it.
        (otherwise
         (return-from record-free-reference nil)))
          while transform-again?)
    ;; Check if this is a previously existing refernce.
    (loop for entry in compiler-free-references
          do
      (when (and (eq type-of-reference (car-of-cons entry))
                 (equalw reference (cdr-of-cons entry)))
        (return-from record-free-reference nil)))
    ;; Enter the new free reference using phrase-conses.  This list will be copied
    ;; before entry into the procedure frame.
    (phrase-push
      (phrase-cons type-of-reference reference)
      compiler-free-references))
  nil)




;;; The function `install-free-references-in-byte-code-body' takes a
;;; byte-code-body and a list of free references generated during a compile into
;;; the compiler-free-references variable.  This function allocates a
;;; managed-simple-vector to hold the free references and installs it into the
;;; byte code body.

(defun install-free-references-in-byte-code-body
       (byte-code-body free-references)
  (reclaim-if-simple-vector-of-slot-values
    (byte-code-body-free-references byte-code-body))
  (let* ((new-vector? nil)
         (free-references-count (length free-references))
         (requested-length (*f free-references-count 2)))
    (when (>f free-references-count 0)
      (setq new-vector?
            (allocate-managed-simple-vector requested-length))
      (loop for (reference-type . reference-value) in free-references
            with length = (length-of-simple-vector new-vector?)
            for index from 0 by 2
            do
        (setf (svref new-vector? index)
              (copy-for-slot-value reference-type)) ;isn't this always a symbol?
        (setf (svref new-vector? (+f index 1))
              (copy-for-slot-value reference-value))
            finally
              ;; Have to take care of the case when we have an oversized vector.
              ;; For now stick a NIL in to overwrite garbage. -dkuznick, 10/24/02
              (when (<f requested-length length)
                (loop for i from (+f index 2) below length
                      do
                  (setf (svref new-vector? i) nil)))))
    (setf (byte-code-body-free-references byte-code-body) new-vector?)
    nil))


(defun twrite-single-free-reference-for-consistency
       (type reference)
  (case type
    ((name stable-name)
     (tformat "~(~a: ~a~)" type reference))
    ((name-of-class-instance stable-name-of-class-instance)
     (tformat "~(~a: ~a of class ~a~)" type (car reference) (cdr reference)))
    ((name-of-type)
     (tformat "~(~a: ~a of type ~NT~)" type (car reference) (cdr reference)))
    ((cached-name)
     (tformat
       "~(~a: ~a, constant: ~a~)" type (car reference) (cdr reference)))
    ((class)
     (tformat "~(~a: ~a~)" type reference))
    ((attribute-of-class)
     (tformat "~(~a: ~a of ~a~)"
              type (car reference) (or (cdr reference) "item")))
    ((class-qualified-attribute-of-class)
     (tformat "~(~a: ~NQ of ~a~)"
              type (first reference) (second reference)
              (or (third reference) "item")))
    ((attribute)
     (tformat "~(~a: ~a~)" type reference))
    ((cached-attribute)
     (tformat "~(~a: ~a of ~a~)"
              type
              (first reference)
              (or (second reference) (third reference) "item"))
     ;; class-specific attribute
     (when (fifth reference)
       (tformat "~(, from class: ~a~)" (fifth reference)))
     (when (fourth reference)
       (tformat "~(, constant: ~a~)" (fourth reference))))
    ((procedure-call remote-procedure-call stable-procedure-call
                     stable-remote-procedure-call)
     (tformat "~(~a: ~a ~)" type (car reference))
     (write-list-of-type-specifications (second reference))
     (twrite-string #w" = ")
     (write-list-of-type-specifications (third reference)))
    ((stable-compile-time-selected-method)
     (gensym-dstruct-bind ((selected-class method-name first-arg-class
                                          arg-types return-types)
                          reference)
       (tformat "~(~a: call to ~a for first argument ~a selected ~a::~a~)"
                type method-name first-arg-class selected-class method-name)
       (write-list-of-type-specifications arg-types)
       (twrite-string #w" = ")
       (write-list-of-type-specifications return-types)))
;    ((procedure-with-valid-environment)
;     ;; Not currently writing the second and third references, the directly and
;     ;; indirectly called procedures.  These could be two long lists.  - cpm,
;     ;; 6/17/93
;     (tformat "~(~a: ~a ~)" type reference))
;    ((stable-procedure-with-valid-environment)
;     (tformat "~(~a: ~a ~)" type (car reference)))
    ((function-call)
     (tformat "~(~a: ~a ~)" type (car reference))
     (write-list-of-type-specifications (second reference)))
    ((stable-subclass stable-not-subclass)
     (tformat "~(~a: superior class ~a, subclass ~a~)"
              type (car reference) (cdr reference)))
    ((inline)
     (tformat "~(~a: ~a~)" type reference))
    ((stable-hierarchy)
     (tformat "~(~a: ~a~)" type reference))
    (t
     (tformat "~(unused ~a: ~a~)" type reference))))

(defun write-list-of-type-specifications (types)
  (twrite-string #w"(")
  (loop for first-time = t then nil
        for type in types do
    (unless first-time (twrite-string #w", "))
    (write-type-specification type))
  (twrite-string #w")"))



;;; The function `redundant-parameter-free-reference?' checks if the given
;;; parameter reference is unnecessary because of another element found in the
;;; reference-list argument.

;;; Note that a reference is of the form (kind-of-free-reference
;;; . free-reference).  The reference list is a list of these elements.

;;; Currently, this function only checks if one of the "name" free-references
;;; (name-of-type, name-of-class-instance, etc.) overlaps with another.  It
;;; checks if the two "name" free-references refer to the same named item, if
;;; the first reference is of class parameter, and if the second reference is of
;;; class variable-or-parameter.

;;; Note the parameter free-reference can be replaced by the variable-or-
;;; parameter free-reference in the case where "unknown" is allowed.  This is
;;; currently true in user-defined function-definitions, which compiles in
;;; several ways (unknown allowed, unknown not allowed, etc.).

(defun-simple redundant-parameter-free-reference? (ref ref-list)
  (when (consp ref)
    (let ((result? nil)
          (list-of-free-reference-types
            '(name-of-type stable-name-of-type name-of-class-instance
              stable-name-of-class-instance)))
      (gensym-dstruct-bind ((ref-kind . free-ref) ref)
        (let ((ref-name? nil)
              (ref-type? nil))
          (when (and (memq ref-kind list-of-free-reference-types)
                     (listp free-ref)
                     (cdr-of-cons free-ref))
            (setq ref-name? (car-of-cons free-ref))
            (setq ref-type? (cdr-of-cons free-ref)))
          (when (and ref-name?
                     ref-type?
                     (or (and (classp ref-type?)
                              (subclassp ref-type? 'parameter))
                         (and (valid-type-specification-p ref-type?)
                              (type-specification-subtype-p
                                ref-type? '(class parameter)))))
            (loop for test-ref in ref-list
                  for test-ref-name? = nil
                  for test-ref-type? = nil
                  until result?
                  do
              (when (and (consp test-ref)
                         (not (eq test-ref ref)))
                (gensym-dstruct-bind
                    ((test-kind . test-free-ref) test-ref)
                  (when (and (memq test-kind list-of-free-reference-types)
                             (listp test-free-ref)
                             (cdr-of-cons test-free-ref))
                    (setq test-ref-name? (car-of-cons test-free-ref))
                    (setq test-ref-type? (cdr-of-cons test-free-ref))
                    ;; Check if the two free-references refer to the same name
                    ;; and if the second is of the correct type (the type of the
                    ;; first was already checked).  Note that the following does
                    ;; not test if the two free reference classes (or type
                    ;; spec's) "match" (i.e., does not check if ther are equal
                    ;; or if one is a subclass of the other).
                    (when (and test-ref-name?
                               test-ref-type?
                               (eq test-ref-name? ref-name?)
                               (or (eq test-ref-type? 'variable-or-parameter)
                                   (and (classp test-ref-type?)
                                        (subclassp
                                          test-ref-type?
                                          'variable-or-parameter))
                                   (and (valid-type-specification-p
                                          test-ref-type?)
                                        (type-specification-subtype-p
                                          test-ref-type?
                                          '(or (class parameter) (class variable)))
                                        )))
                      (setq result? t)))))))))
      result?)))






;;;; Stack Frame Variables




;;; Some compilers of expressions and the like need access to a local var which
;;; can be used within an atomic context and then is no longer needed.  This is
;;; true for things like AND, OR, and normal form tree compilation.  Stack frame
;;; variables are provided for these situations.

;;; Stack frame variables are managed as follows.  During the compilation of a
;;; segment of code, the function generate-new-stack-frame-var should be called
;;; to create a new var spot designation for a stack frame var.  These var spots
;;; can be placed into stack-node-instructions push-into-surrounding-local-var
;;; and pop-from-surrounding-local-var, which recognize them as different from
;;; local vars and emit the correct instructions.  (This is actually handled in
;;; the emitters for the stack instructions of the same names.)

;;; Near the place in the compiler where with-stack-frame-variables is bound,
;;; care should be taken that some functions are emitted around the instructions
;;; which will reference stack frame vars.  Stack frame vars are placed on the
;;; stack in relation to the stack-frame-base stack pointer.  This variable
;;; defaults to zero, and is incremented and reestablished by call-user-function
;;; and return-from-user-function.  The instruction push-nones must be used to
;;; allocate space on the stack for stack frame variables before entering any
;;; instructions which use them.  On exit from this facility, the instruction
;;; pop-copy-down-the-stack, pop-values, or some other function which gets rid
;;; of those stack locations (like return-from-user-function) must be used to
;;; clear those locations on the stack.  Note that this must be handled such
;;; that the stack frame vars are the first things pushed onto the stack, so
;;; that they can be adjacent to the stack frame base location.

;;; This is handled in rules by having one set of stack frame vars for the
;;; entire rule.  In procedures stack frame vars are typically not used, because
;;; of the excess of branching which makes it difficult to pop stack frame vars
;;; off the stack.  Stack frame vars are only used in compilations where this
;;; has been explicitly allowed by wrapping with-procedure-stack-frame-vars
;;; around calls to compile-expression.  In all other compilations in G2 it is
;;; handled by letting the expression emitter handle allocation itself, since
;;; there is only one expression evaluated at a time in these other kinds of
;;; environments.  -jra 9/5/91

;;; The macro `with-stack-frame-variables-environment' is called within the
;;; macro enter-new-code-body, and is used to bind the variables which makes it
;;; possible to call with-stack-frame-variables.  The environment macro sets up
;;; a newly bound environment within which with-stack-frame-variables can be
;;; called.  Note that the nested provided for by this macro is necessary for
;;; nested code bodies when compiling procedures.  The following macro should be
;;; wrapped around the code whose compilation could allocate stack frame vars
;;; which should be treated as a group at the top of a stack.

(def-system-variable next-stack-frame-var-location comp-utils nil)

(def-system-variable outermost-stack-frame-var-binding? comp-utils nil)

(def-system-variable stack-frame-vars-ok-in-procedure? comp-utils nil)

(defmacro with-stack-frame-variables-environment (&body forms)
  `(let ((outermost-stack-frame-var-binding? nil)
         (next-stack-frame-var-location nil)
         (stack-frame-vars-ok-in-procedure? nil))
     ,@forms))




;;; The macro `with-procedure-stack-frame-variables-environment' is called
;;; within procedure statement compilers to declare local contexts within which
;;; stack frame vars can be used instead of local vars.  This is an optimization
;;; for procedures which attempts to use some stack frame vars to keep the sizes
;;; of procedure environments down.

(defmacro with-procedure-stack-frame-variables-environment (&body forms)
  `(let ((outermost-stack-frame-var-binding? nil)
         (next-stack-frame-var-location nil)
         (stack-frame-vars-ok-in-procedure? t))
     ,@forms))




;;; The macro `with-stack-frame-variables' binds an environment for allocating
;;; stack frame vars.  Note that these environment cannot be nested.  After
;;; executing code which may call generate-new-stack-frame-var, the variable
;;; next-stack-frame-var-location will contain the count of how many stack frame
;;; vars have been allocated.  That many pushes and pops must be executed around
;;; the instructions using the stack frame vars.  All compiler facility users of
;;; this macro must make thier own provisions for pushing and popping, since I
;;; can't think of any way to abstract this at the present time.

;;; I'm going to add a simple kind of nesting, where only when entering this
;;; form and finding a value of NIL will it change the location to a fixnum.
;;; Entrances to this form which find a fixnum in the location must not modify
;;; its value.  -jra 9/5/91

(defmacro with-stack-frame-variables (&body forms)
  (let ((old-value (gensym)))
    `(let* ((,old-value next-stack-frame-var-location)
            (outermost-stack-frame-var-binding? (not ,old-value)))
       (unwind-protect
           (progn
             (unless ,old-value
               (setq next-stack-frame-var-location 0))
             ,@forms)
         (unless ,old-value
           (setq next-stack-frame-var-location ,old-value))))))

(defun generate-new-stack-frame-var-spot (type)
  (cond ((and (not stack-frame-vars-ok-in-procedure?)
              *current-computation-frame*
              (frame-of-class-p *current-computation-frame* 'procedure))
         (generate-new-variable-spot type))
        (t
         (when (>f next-stack-frame-var-location 255)
           (compiler-error
             "~a~a~a~a"
             "Too many stack frame variables have been emitted from this compiled "
             "item.  This item must be simplified to have fewer than 256 stack frame "
             "variables, for example by making smaller expressions or by reducing the "
             "size of a function, to be able to compile."))
         (prog1
           (phrase-list 'stack-frame-var next-stack-frame-var-location type)
           (incff next-stack-frame-var-location)))))




;;; The function `generate-new-stack-arg-var-spot' takes a non-negative integer
;;; and returns a new var-spot referencing that argument location.  Note that
;;; there is a maximum of 256 arguments, and that if this function receives an
;;; index larger than 255 it will issue a compiler-error saying that the maximum
;;; argument count is 256, though it will still return a var spot which can be
;;; used to attempt the remainder of the compile.

(defun generate-new-stack-arg-var-spot (argument-number type-specification)
  (cond ((<f argument-number 0)
         (compiler-bug
           "stack argument registration"
           "The argument number ~a was less than zero, the minimum."
           argument-number)
         (setq argument-number 0))
        ((>=f argument-number 256)
         (compiler-error
           "The maximum number of arguments for a function is 256, attempting ~
            to allocate ~a."
           argument-number)
         (setq argument-number 255)))
  (phrase-list 'stack-arg argument-number type-specification))






;;;; Variable Spots and Local Names




;;; Variable spots are data structures used to represent local variables of
;;; computations.  They are implemented as two elements lists where the first of
;;; the list is one of the symbols var-spot, stack-frame-var, or stack-arg.
;;; Var-spots describe locations within environment vectors.  Stack-frame-vars
;;; represent variables allocated on the stack, offset by an index from the
;;; stack-frame-base.  Stack args are the arguments to functions, which are also
;;; located via offsets from the stack-frame-base.  The term var-spot is
;;; sometimes used to refer to all of these kinds of locations, since they are
;;; the kind of location that has existed the longest.

;;; Stack-frame-vars and stack-args have a fixnum index in the second of their
;;; data structure, which is the index to the particular location they
;;; references.  They also will occasionally have a third, containing the type
;;; specification for values that may be placed within them.

;;; Note that (stack-arg k) denotes the position on the stack, not of the
;;; k'th arg, but the (n-k+2)'th arg. This is done so that all stack-arg
;;; references can be done relative to stack-frame-base, rather than requiring
;;; an additional redirection.
;;; (stack-arg 1) refers to the unknown-p arg, while
;;; (stack-arg 0) refers to the no-item-p arg. -alatto, 10/13/98

;;; Var spots have a more complex indexing scheme, which has changed over time.
;;; The second of a var spot used to be a fixnum or cons tree of fixnums.  If it
;;; was a fixnum, then the spot referenced a particular element of the
;;; environment vector.  If the second of the var-spot was a cons, then the car
;;; of that cons was an index into the environment vector which would contain a
;;; pointer to a surrounding environment vector, and the cdr of that cons would
;;; contain either a fixnum reference into that environment vector, or another
;;; cons.  This data structure was used to refer to locations within environment
;;; vectors of surrounding code body invocations within procedures.

;;; It was always the case the there was only one code body caller of a code
;;; body invocation, though we had originally considered the possibility of
;;; more.  Since this is true, then it is not really necessary to hold a pointer
;;; to the surrounding environment within the local environment vector, since it
;;; can be found within the code body caller of the current code body
;;; invocation.  If this approach is used, then all that is needed to find the
;;; correct surrounding environment vector is a count of the number of nested
;;; callers to traverse.

;;; Var-spot-indices are currently a single fixnum which fits within 16 bits
;;; (i.e. has a range of 0 through 64K-1).  The lower 10 bits (range of 1K) are an
;;; index to an Nth local name of an environment, and the upper 6 bits (range of
;;; 64) are a nesting count.  Fetching the value of a var spot is then iterating
;;; by the nesting count out through the callers of the currently executing code
;;; body, and then fetching the nth element of that environment vector according
;;; to the low order bits index.

;;; The constants `maximum-var-spot-index', `maximum-var-spot-local-index', and
;;; `maximum-var-spot-nesting' reflect the limits of local variable counts and
;;; nesting levels.  They are ste to 64K - 1, 1K -1, and 63 respectively.

(eval-when (:compile-toplevel :load-toplevel :execute)

(defconstant maximum-var-spot-index #.(- (expt 2 16) 1))
(defconstant bits-in-var-spot-index 16)
(defconstant maximum-var-spot-local-index #.(- (expt 2 10) 1))
(defconstant bits-in-var-spot-local-index 10)
(defconstant maximum-var-spot-nesting #.(- (expt 2 6) 1))
(defconstant bits-in-var-spot-nesting 6)

) ; eval-when

;;; The macro `var-spot-index-nesting' takes a var-spot-index and returns the
;;; nesting level of that var-spot.  The macro `var-spot-local-index' takes a
;;; var-spot-index and returns the local index portion.  The macro
;;; `generate-var-spot-index-given-nesting-and-local-index' does what it says.

(defmacro var-spot-index-nesting (var-spot-index)
  `(ashf ,var-spot-index ,(- bits-in-var-spot-local-index)))

(defmacro var-spot-local-index (var-spot-index)
  `(logandf ,var-spot-index ,maximum-var-spot-local-index))

(defmacro generate-var-spot-index-given-nesting-and-local-index
          (nesting local-index)
  `(+f (ashf ,nesting ,bits-in-var-spot-local-index) ,local-index))

(defmacro var-spot-index-of-var-spot (var-spot)
  `(second ,var-spot))




;;; The macro `equal-var-spots' takes two var-spots generated for the same code
;;; body (guaranteeing that index-nesting is comparable) and returns whether or
;;; not the two var-spots refer to the same location.

(defmacro equal-var-spots (var-spot-1 var-spot-2)
  `(=f (var-spot-index-of-var-spot ,var-spot-1)
       (var-spot-index-of-var-spot ,var-spot-2)))




;;; The function `valid-var-spot-p' takes a thing and returns whether or not it
;;; is a valid var-spot.  Note that references to stack-frame-vars and
;;; stack-args are valid var-spots.

(defun valid-var-spot-p (thing)
  (and (consp thing)
       (let ((type-of-var-spot (car-of-cons thing))
             (second-cons? (cdr-of-cons thing)))
         (and (consp second-cons?)
              (let ((car-of-second (car-of-cons second-cons?)))
                (and (fixnump car-of-second)
                     (>=f car-of-second 0)
                     (or (and (eq type-of-var-spot 'var-spot)
                              (<=f car-of-second
                                   maximum-var-spot-index))
                         (and (memq type-of-var-spot
                                    '(stack-frame-var stack-arg))
                              (<=f car-of-second
                                   255)))))
              (or (null (cdr-of-cons second-cons?))
                  (and (consp (cdr-of-cons second-cons?))
                       (valid-type-specification-p (second second-cons?))
                       (null (cdr-of-cons (cdr-of-cons second-cons?)))))))))


(defun valid-var-spot-index-p (thing)
  (and (fixnump thing)
       (<=f 0 thing maximum-var-spot-index)))




;;; The function `var-spot-type' takes a variable spot and a list of code-body-
;;; entries, typcially taken from lexically-visible-code-bodies.  It
;;; returns the type of that variable spot.

(defun var-spot-type (var-spot code-body-entry-stack)
  (case (car var-spot)
    ((stack-frame-var stack-arg)
     (third var-spot))
    ((var-spot)
     (loop for code-body-entry in code-body-entry-stack
           repeat (var-spot-index-nesting (second var-spot))
           finally
             (let* ((environment-description?
                      (when code-body-entry
                        (compiler-code-body-environment-description
                          code-body-entry))))
               (return
                 (getfq (cdr (nth (var-spot-local-index (second var-spot))
                                  environment-description?))
                        :type)))))
    (t
     (compiler-bug
       "type fetcher"
       "Invalid var-spot ~a given to var-spot-type."
       var-spot))))

;;; `inlining-data' is a structure designed to keep inlining from tripping over
;;; itself.

(def-structure (inlining-data-holder)
  (inlining-data-context-stack nil)
  (inlining-data-current-name nil)
  (inlining-data-current-environment-start-point nil)
  (inlining-data-delimiters-of-environments-unavailable-at-top-level nil)
  (inlining-data-recieved-value-compilations nil)
  (inlining-data-environment-context-start-points nil)
  (inlining-data-local-var-context-start-points nil)
  ;; An assoc-list of (<context> . <times-already-inlined>)  This will be used to
  ;; generate tags that don't clash if the same procedure is inlined more than once
  ;; in another procedure.
  (inlining-data-contexts-inlined-already nil)
  ;;these are `defeasible' properties if anything that is inlined
  ;; changes the value from the default value, the new value is retained
  ;; until the end of the compilation
  (inlining-data-optimizable-p-context t)
  (inlining-data-no-next-method-call-required-in-context nil)
  (inlining-data-calling-code-body nil)
  )



(defvar inlining-data (make-inlining-data-holder))


(defun clear-inlining-data ()
  (setf (inlining-data-context-stack inlining-data) nil)
  (setf (inlining-data-current-name inlining-data) nil)
  (setf (inlining-data-delimiters-of-environments-unavailable-at-top-level
          inlining-data) nil)
  (setf (inlining-data-recieved-value-compilations inlining-data) nil)
  (setf (inlining-data-local-var-context-start-points inlining-data) nil)
  (setf (inlining-data-environment-context-start-points inlining-data) nil)
  (setf (inlining-data-contexts-inlined-already inlining-data) nil)
  ;; defeasible
  (setf (inlining-data-optimizable-p-context inlining-data) t)
  (setf (inlining-data-no-next-method-call-required-in-context inlining-data) nil)
  (setf (inlining-data-calling-code-body inlining-data) nil)
  )

;;; `adjust-nesting-of-inlining-data-received-value-compilations' is used to go
;;; in and change the index of var-spots to a different nesting level.  This is
;;; called by ENTER-NEW-CODE-BODY.  This needs to be used because
;;; COMPILE-INLINE-SUBSTITUTION is setting up var-spots for return values from
;;; inlined procedures, yet it can't tell ahead of time if they will be in a
;;; different code body.  So once we enter a new code body, we have to adjust
;;; the return-value-receiving var-spots to take the new code body into
;;; consideration.

(defun adjust-nesting-of-inlining-data-received-value-compilations (amount)
  (loop for var-spot in (inlining-data-recieved-value-compilations?)
        for current-var-spot-index = (var-spot-index-of-var-spot var-spot)
        do
    (setf (var-spot-index-of-var-spot var-spot)
          (generate-var-spot-index-given-nesting-and-local-index
            (+f (var-spot-index-nesting current-var-spot-index)
                amount)
            (var-spot-local-index current-var-spot-index)))))



;;; defeasible accessors

(defun optimizable-in-context? ()
  (and (inlining-data-optimizable-p-context inlining-data)
       (block-is-optimizable-p *current-computation-frame*)))

(defun get-inline-call-number (context-item)
  (let ((context-assoc? (assq context-item
                              (inlining-data-contexts-inlined-already
                                inlining-data))))
    (and context-assoc?
         (cdr-of-cons context-assoc?))))


;;; The function `variable-spot-and-description-for-local-name' takes a symbol
;;; which is possibly a variable spot.  If it is a declared local name, it then
;;; returns two values, a phrase cons var spot for the local name, and the
;;; variable description.  If it is not a declared local name, it returns double
;;; nils.

(defun variable-spot-and-description-for-local-name (possible-local-name)
  (loop for code-body-entry in lexically-visible-code-bodies
        for nesting-index from 0
        for environment = (compiler-code-body-environment-description
                            code-body-entry)
        with ignore-inlining-environment?
        do
    ;; GENSYMCID-1257: After editing some procedures that can be compiled and
    ;; editing some properties, these procedures can no longer be compiled (bug report)
    (setq ignore-inlining-environment?
      (or (null (inlining-data-context-stack inlining-data))
          (neq code-body-entry (car (inlining-data-calling-code-body inlining-data)))))
    (loop for local-index from 0
          for description in environment
          do
      (when (and (eq possible-local-name (car description))
                 (or ignore-inlining-environment?
                     (environment-index-ok-in-this-context? local-index)))
        (return-from variable-spot-and-description-for-local-name
          (values
            (phrase-list
              'var-spot
              (generate-var-spot-index-given-nesting-and-local-index
                nesting-index local-index))
            description))))
        finally (values nil nil)))




;;; The function `generate-new-variable-spot' takes a type and generates a new
;;; entry in the environment description for the local environment description
;;; of the currently compiling computation.  It then returns a phrase cons var
;;; spot reference to the newly created spot.

(defun generate-new-variable-spot
       (type? &optional
        (name? nil)
        (code-body-entry (current-compiler-code-body)))
  (when (and type? (not (valid-type-specification-p type?)))
    (compiler-bug
      "variable spot generator"
      "Invalid type ~a given to generate-new-variable-spot."
      type?))
  (cond ((class-type-specification-p type?)
         (record-free-reference
           'class (type-specification-class-function type?))
         (phrase-list
           'var-spot
           (generate-new-index-in-code-body
             type? name? code-body-entry lexically-visible-code-bodies)
           type?))
        (type?
         (phrase-list
           'var-spot
           (generate-new-index-in-code-body
             type? name? code-body-entry lexically-visible-code-bodies)
           type?))
        (t
         (phrase-list
           'var-spot
           (generate-new-index-in-code-body
             type? name? code-body-entry lexically-visible-code-bodies)))))

(defun generate-new-index-in-code-body
       (type? name? code-body-entry code-body-stack)
  (unless code-body-stack
    (compiler-bug
      "variable index generator"
      "Attempted to generate a new variable in a null code body environment."))
  (loop for code-body-in-stack in code-body-stack
        for nesting-index from 0
        do
    (when (eq code-body-entry code-body-in-stack)
      (let* ((new-description
               (if type?
                   (phrase-list name? :type type?)
                   (phrase-list name?)))
             (old-environment
               (compiler-code-body-environment-description
                 code-body-entry))
             (local-index (length old-environment)))
        (setf (compiler-code-body-environment-description
                code-body-entry)
              (nconc old-environment
                     (phrase-list new-description)))
        (when (>f local-index maximum-var-spot-local-index)
          (compiler-error
            "The maximum number of local variables, ~a, has been ~
             exceeded.  You must reduce the number of local variables, the ~
             complexity of the expressions, or the overall number of ~
             expressions and statements in this item."
            maximum-var-spot-local-index))
        (when (>f nesting-index maximum-var-spot-nesting)
          (compiler-error
            "The maximum number of nestings with a procedure, ~a, has been ~
             exceeded.  You must reduce the depth of do in parallel and on ~
             error nesting within this procedure."
            maximum-var-spot-nesting))
        (return
          (generate-var-spot-index-given-nesting-and-local-index
            nesting-index local-index))))))


;;; `available-var-spot-count' is derived from the
;;; (>f local-index maximum-var-spot-local-index) test which appears in
;;; `generate-new-index-in-code-body'  this function gives other facilites the
;;; information which they need to assure that they are not requesting the
;;; impossible -- the creation of one too many local vars

(defun-simple available-var-spot-count ()
  (-f maximum-var-spot-local-index
     (length (compiler-code-body-environment-description
               (current-compiler-code-body)))))




;;; The macro `generate-block-of-new-variable-spots' takes a rest argument of
;;; types and returns a phrase cons list of var-spots generated to hold the
;;; given types.  The generated variables are allocated contiguously within the
;;; current local variable vector, and so can be copied out of and into using
;;; pop-into-block-of-local-vars and push-from-block-of-local-vars.

(defmacro generate-block-of-new-variable-spots (&rest types)
  `(phrase-list ,@(loop for type in types
                        collect `(generate-new-variable-spot ,type))))






;;;; Missing Local Name Error Handling




;;; The function `procedure-compiler-missing-local-name-error' takes a symbol
;;; which should have named a local name.  The function
;;; `procedure-compiler-duplicate-local-name-error' takes a symbol which names a
;;; local-name or argument that is defined more than once as either an argument or
;;; local-name.  These functions will write a procedure compiler error stating
;;; that this local name was either not defined or defined more than once, if an
;;; error for this name has not already been written.  They keep a list of the
;;; local names already noted in `missing-local-names-already-reported' and
;;; `duplicate-local-names-already-reported', which are bound by the compiler top
;;; level.

(defvar missing-local-names-already-reported nil)
(defvar duplicate-local-names-already-reported nil)

(defun procedure-compiler-missing-local-name-error (local-name)
  (when (not (memq local-name missing-local-names-already-reported))
    (compiler-error "the local name ~a is undefined" local-name)
    (setq missing-local-names-already-reported
          (phrase-cons local-name missing-local-names-already-reported))))

(defun procedure-compiler-duplicate-local-name-error (local-name)
  (when (not (memq local-name duplicate-local-names-already-reported))
    (compiler-error "the local name ~a is defined more than once" local-name)
    (setq duplicate-local-names-already-reported
          (phrase-cons local-name duplicate-local-names-already-reported))))






;;;; Compiler Environment




;;; The macro `with-compiler-environment' binds most of the variables needed for
;;; compiling.  See its components for further details.

(defmacro with-compiler-environment (&body forms)
  `(with-compiler-error-reporting
     (with-compiler-goto-tags
       (with-compiler-code-body-entries
         (with-compiler-stack-nodes
           (with-compiler-free-reference-collection
             ,@forms))))))

(defmacro with-compiler-environment-and-phrase-conses (&body forms)
  `(with-phrase-conses
     (with-compiler-error-reporting
       (with-compiler-goto-tags
         (with-compiler-code-body-entries
           (with-compiler-stack-nodes
             (with-compiler-free-reference-collection
               ,@forms)))))))






;;;; Byte Code Instruction Streams




;;; Byte code instruction streams are used to collect the bytes emitted by
;;; compilers into a single sequence of instructions.  The operations available
;;; for byte code instruction streams are make-byte-code-stream,
;;; byte-code-stream-p, reclaim-byte-code-stream, write-byte-code-to-stream,
;;; byte-code-stream-address, and read-byte-code-stream-vector.

;;; Byte-code-streams also register instructions which need address resolution,
;;; and maintain associations of tag-statments to addresses.  The operations
;;; available for these operations are register-byte-code-tag-resolution-point,
;;; byte-code-stream-addresses-to-resolve, register-tag-at-byte-code-address, and
;;; byte-code-address-of-tag.

;;; Bytes are emitted into the stream as back end code emitting proceeds.  When
;;; emitting is done, then the vector containing the emitted bytes should be
;;; read from the stream.  Note that the returned vector will not be exactly the
;;; length needed to hold the emitted bytes, but will be rounded up to an
;;; appropriate allocation size.  The vector will be zero filled beyond the last
;;; byte.

;;; The parameter maximum-stack-instruction-vector-length gives the maximim size
;;; of a stack instruction vector.  It is set at 16K.  This could be increased
;;; to 64K, as long as we believe we can make vectors that long on all
;;; platforms.

(defparameter maximum-stack-instruction-vector-length #.(expt 2 14))




;;; The structure byte-code-stream implements the data structure for
;;; byte-code-streams.  The address slot holds the index awaiting the next byte.
;;; The bytes slot holds a compiler-cons list of the bytes emitted so far.

;;; The macros `make-byte-code-stream', `reclaim-byte-code-stream',
;;; `byte-code-stream-address', and `byte-code-stream-p' are all automatically
;;; defined as part of the structure.

;;; The macro `byte-code-stream-addresses-to-resolve' returns a list of entries,
;;; where the the car of each entry is the address of an instruction which
;;; requires address resolution, and whose cdr contains a tag or list of tags
;;; which need resolution in that instruction.  This accessor should be called
;;; from the address resolution facility.

(def-structure (byte-code-stream)
  (byte-code-stream-address 0)
  (byte-code-stream-bytes nil :reclaimer reclaim-compiler-tree)
  (byte-code-stream-addresses-to-resolve nil :reclaimer reclaim-compiler-tree)
  (byte-code-stream-constants nil)
  (byte-code-stream-superior-stream? nil)
  (byte-code-stream-base-stream? nil)
  (byte-code-stream-activity-information? nil)
  ;; I took out the reclaimer on the folowing slot because they're phrase
  ;; conses. -dkuznick, 1/13/99
  (byte-code-stream-text-position-information? nil))




;;; The function `make-inferior-byte-code-stream' takes an existing
;;; byte-code-stream as its only argument and returns a new byte code stream
;;; with the given stream as its superior.  Emitting may now occur into the
;;; inferior stream, but the inferior stream must eventually be merged into its
;;; superior stream with merge-byte-code-streams.
(defun-simple make-inferior-byte-code-stream (superior-byte-code-stream)
  (let ((new-stream (make-byte-code-stream)))
    (setf (byte-code-stream-superior-stream? new-stream)
          superior-byte-code-stream)
    new-stream))




;;; The function `make-byte-code-stream-given-base-stream' makes a byte code
;;; stream which for a byte code body which is not the base byte code body of a
;;; computation.  The constant vector for this byte stream will be merged into
;;; the given stream to the base byte code body.

(defun-simple make-byte-code-stream-given-base-stream (base-byte-code-stream)
  (let ((new-stream (make-byte-code-stream)))
    (setf (byte-code-stream-base-stream? new-stream) base-byte-code-stream)
    new-stream))




;;; The function `merge-byte-code-streams' takes a superior byte code stream and
;;; its inferior.  The inferior will be merged into the end of the superior byte
;;; code stream and reclaimed.

(defun-void merge-byte-code-streams (superior inferior)
  (incff (byte-code-stream-address superior)
         (byte-code-stream-address inferior))
  (setf (byte-code-stream-bytes superior)
        (nconc (byte-code-stream-bytes inferior)
               (byte-code-stream-bytes superior)))
  (setf (byte-code-stream-bytes inferior) nil)
  (reclaim-byte-code-stream inferior)
  nil)




;;; The function `write-byte-code-to-stream' takes a byte-code-stream
;;; and a byte code and and a fixnum from 0 through 255 to be written into the
;;; byte stream.

(defun write-byte-code-to-stream (byte-code-stream byte)
  (when (not (and (fixnump byte) (>=f byte 0) (<f byte 256)))
    #+development
    (error "Non-byte ~a given to write-byte-code-stream." byte)
    (compiler-bug
      "byte code emitter" "Non-byte ~a emitted into byte-codes." byte)
    (setq byte 0))
  (let ((current-address (byte-code-stream-address byte-code-stream)))
    ;; If there are already errors, then don't emit anything.
    (cond (compiler-errors
           nil)
          ((>=f current-address maximum-byte-vector-length)
           (compiler-error
             "The byte codes in the instruction vector have exceeded the ~
              maximum, ~a.  There are too many statements and expressions in ~
              this source code."
             maximum-byte-vector-length))
          (t
           (setf (byte-code-stream-bytes byte-code-stream)
                 (compiler-cons
                   byte (byte-code-stream-bytes byte-code-stream)))
           (setf (byte-code-stream-address byte-code-stream)
                 (+f current-address 1))))
    nil))




;;; The function `register-tag-in-byte-code-stream' takes a byte code stream and
;;; a tag.  This function will register the tag in the stream such that future
;;; address resolution will find the current address of this byte code stream.
;;; If there are compiler errors already, don't register the tag.

(defun register-tag-in-byte-code-stream
       (byte-code-stream tag &optional (jump-tag? nil))
  (unless compiler-errors
    (setf (byte-code-stream-bytes byte-code-stream)
          (compiler-cons
            (compiler-cons (if jump-tag? 'jump-tag 'tag) tag)
            (byte-code-stream-bytes byte-code-stream))))
  nil)




;;; The function `register-byte-code-tag-resolution-point' takes a
;;; byte-code-stream, and a tag whose address is to be resolved, or a
;;; compiler-cons list of tags to be resolved.  This function registers the
;;; current address and tags such that during address resolution, the
;;; address-resolution function for the instruction at that address will be
;;; called.  The arguments to the address-resolution function include the tag or
;;; list of tags to this function, so that the instruction need not keep its own
;;; list of tags for that instruction.  When the byte-code-stream is reclaimed,
;;; any conses in the tags list will be reclaimed back into the compiler cons
;;; pool.

;;; Note that this style of registration requires that this function be called
;;; just before the op-code is emitted for the function to be resolved.

(defun register-byte-code-tag-resolution-point (byte-code-stream tags)
  (setf (byte-code-stream-bytes byte-code-stream)
        (compiler-cons
          (compiler-cons 'address-resolution-point tags)
          (byte-code-stream-bytes byte-code-stream)))
  nil)

(defun register-byte-code-tag-resolution-address
       (byte-code-stream tags address)
  (setf (byte-code-stream-addresses-to-resolve byte-code-stream)
        (compiler-cons
          (compiler-cons address (copy-tree-using-compiler-conses tags))
          (byte-code-stream-addresses-to-resolve byte-code-stream)))
  nil)




;;; The function `read-byte-code-stream-vector' takes a byte-code-steam and
;;; returns a byte-vector containing the bytes emitted into the stream.  Note
;;; that the length of the actual vector will be rounded up to some appropriate
;;; allocation size.  The vector will be zero filled beyond the last byte.

;;; Any tags which have been registered into this byte code stream have their
;;; actual addresses registered as the iteration proceeds.  An element of the
;;; byte-code-stream-bytes which is a cons is a registration of a tag in the car
;;; of that cons.  All normal instruction bytes are merely fixnums in the list.

(defun read-byte-code-stream-vector (byte-code-stream)
  (loop with bytes fixnum = (byte-code-stream-address byte-code-stream)
        with vector = (allocate-byte-vector bytes)
        with length fixnum = (byte-vector-length vector)
        with index fixnum = bytes
        for byte-or-tag in (byte-code-stream-bytes byte-code-stream)
        do
    (cond ((consp byte-or-tag)
           (case (car-of-cons byte-or-tag)
             ((tag jump-tag)
              (register-goto-tag-address
                (cdr-of-cons byte-or-tag) index
                (eq (car-of-cons byte-or-tag) 'jump-tag)))
             ((address-resolution-point)
              (register-byte-code-tag-resolution-address
                byte-code-stream (cdr-of-cons byte-or-tag) index))
             (t
              (compiler-bug "byte code stream vector reader"
                            "Unrecognized entry ~a in byte-code-stream-bytes."
                            byte-or-tag))))
          ((fixnump byte-or-tag)
           (decff index)
           (setf (byte-vector-aref vector index) byte-or-tag))
          (t
           (compiler-bug "byte code stream vector reader"
                         "Unrecognized entry ~a in byte-code-stream-bytes."
                         byte-or-tag)))
        finally
          (loop for index-to-zero fixnum from bytes below length
                do
            (setf (byte-vector-aref vector index-to-zero) 0))
          (return vector)))




;;; The function `register-constant-in-byte-code-stream' takes an
;;; evaluation-value and registers it in the byte-code-stream.  This function
;;; will attempt to share locations for equivalent constants.  This function
;;; returns a fixnum which is the index to the registered constant.  If the
;;; registered constant increases the length of the constant vector beyond the
;;; maximum, 1024, then a compiler-error is issued and zero is returned.  The
;;; limit of 1024 is chosen since it is the largest managed simple vector that
;;; we can allocate.

;; Note that this function can sometimes take things which are not evaluation
;; values.  I believe that in all cases the things given are either evaluation
;; values or are cons trees of symbols and fixnums.  If this is true, then this
;; function should be optimized to constant fold for both of these types, given
;; an argument which says which type it is.  -jra 3/15/91

;; Modifed this function not to take internal-constants (i.e.,
;; non-evaluation-values cons trees).  See
;; register-internal-constant-in-byte-code-stream.  cpm, 4/9/91

#+development
(when (> maximum-managed-simple-vector-size (- (expt 2 16) 1))
  (error
    "Maximum-constant-vector-length has grown beyond long code constant size."))

(defparameter maximum-constant-vector-length maximum-managed-simple-vector-size)

(defun-simple register-constant-in-byte-code-stream
              (byte-code-stream evaluation-value)
  #+development
  (assert (evaluation-value-p-function evaluation-value)
          (evaluation-value)
          "~a should have been an evaluation value."
          evaluation-value)
  (cond ((byte-code-stream-superior-stream? byte-code-stream)
         (register-constant-in-byte-code-stream
           (byte-code-stream-superior-stream? byte-code-stream)
           evaluation-value))
        ((byte-code-stream-base-stream? byte-code-stream)
         (register-constant-in-byte-code-stream
           (byte-code-stream-base-stream? byte-code-stream)
           evaluation-value))
        (t
         (let ((old-constants (byte-code-stream-constants byte-code-stream))
               (result-index nil))
           (loop for index from 0
                 for constant in old-constants
                 for constant-fold? = (and (evaluation-value-p-function constant)
                                           (evaluation-values-can-be-constant-folded-p
                                             constant evaluation-value))
                 do
             (when constant-fold?
               (setq result-index index)
               (return nil))
                 finally
                   (setf (byte-code-stream-constants byte-code-stream)
                         (nconc old-constants
                                (slot-value-list
                                  (copy-for-slot-value evaluation-value))))
                   (setq result-index index))
           (when (>=f result-index maximum-constant-vector-length)
             (compiler-error
               "The maximum allowed number of constants, ~a, has been exceeded ~
             while registering ~NE.    You must reduce the size or complexity ~
             of the expressions and statements in this item."
               maximum-constant-vector-length
               evaluation-value))
           (reclaim-evaluation-value evaluation-value)
           result-index))))




;;; The function `register-internal-constant-in-byte-code-stream' takes an
;;; internal-constant and registers it in the byte-code-stream.  The internal
;;; constant is a cons tree of symbols and fixnums, and not an evaluation-value.
;;; This function will attempt to share locations for equivalent constants.
;;; This function returns a fixnum which is the index to the registered
;;; constant.

;; Note that this function can sometimes take things which are not evaluation
;; values.  I believe that in all cases the things given are either evaluation
;; values or are cons trees of symbols and fixnums.  If this is true, then this
;; function should be optimized to constant fold for both of these types, given
;; an argument which says which type it is.  -jra 3/15/91

(defun register-internal-constant-in-byte-code-stream
       (byte-code-stream internal-constant)
  #+development
  (when (and (evaluation-value-p-function internal-constant)
             (not (fixnump internal-constant))
             (not (symbolp internal-constant)))
    (cerror "Continue registering the constant."
            "Attempt to register an evaluation-value as an internal-constant."))
  #+development
  (when (and (consp internal-constant) (eq (car internal-constant) 'var-spot))
    (cerror "Continue" "Var-spot ~a being registered." internal-constant))
  (cond ((byte-code-stream-superior-stream? byte-code-stream)
         (register-internal-constant-in-byte-code-stream
           (byte-code-stream-superior-stream? byte-code-stream)
           internal-constant))
        ((byte-code-stream-base-stream? byte-code-stream)
         (register-internal-constant-in-byte-code-stream
           (byte-code-stream-base-stream? byte-code-stream)
           internal-constant))
        (t
         (let ((old-constants (byte-code-stream-constants byte-code-stream)))
           (loop for index from 0
                 for constant in old-constants
                 for constant-fold? = (constant-fold-internal-constants-p
                                        constant internal-constant)
                 do
             (when constant-fold?
               (return index))
                 finally
                   (setf (byte-code-stream-constants byte-code-stream)
                         (nconc old-constants
                                (slot-value-list
                                  (copy-for-slot-value internal-constant))))
                   (when (>=f index maximum-constant-vector-length)
                     (compiler-error
                       "The maximum allowed number of constants, ~a, has been ~
                     exceeded while registering an internal constant.  You must ~
                     reduce the size or complexity of the expressions and ~
                     statements in this item."
                       maximum-constant-vector-length))
                   (return index))))))




;;; The function `constant-fold-internal-constants-p' takes a value already
;;; stored in a constant vector and a value being registered, and returns
;;; whether the two values are "equivalent" enough to be constant folded.  These
;;; constants are cons trees of symbols and fixnums.

(defun constant-fold-internal-constants-p (constant-1 constant-2)
  (cond ((consp constant-1)
         (and (consp constant-2)
              (constant-fold-internal-constants-p
                (car-of-cons constant-1) (car-of-cons constant-2))
              (constant-fold-internal-constants-p
                (cdr-of-cons constant-1) (cdr-of-cons constant-2))))
        ((symbolp constant-1)
         (eq constant-1 constant-2))
        ((fixnump constant-1)
         (and (fixnump constant-2)
              (=f constant-1 constant-2)))))



;;; The function `make-procedure-byte-code-constants' takes a byte-code-stream
;;; and returns a vector containing all the constants in this stream.  This
;;; function then reclaims the conses which held the constants.

(defun make-procedure-byte-code-constants (byte-code-stream)
  ;; This may be a bit of a hackish place to stick the annotation-lookup
  ;; structure into the constant-vector, but it's convenient and a good safe place
  ;; to do it.  The other hack is that since we don't have a convenient place to
  ;; keep the index into the constant vector, we know it went in last so it's at
  ;; the last position.  -dkuznick, 1/25/99
  (let ((annotation-info? (byte-code-stream-text-position-information?
                            byte-code-stream)))
    (when annotation-info?
      (register-internal-constant-in-byte-code-stream
        byte-code-stream
        (phrase-cons special-annotation-lookup-structure-marker
                     (compress-annotation-info-for-saving (nreverse annotation-info?))))))
  (let* ((constants (byte-code-stream-constants byte-code-stream))
         (count (length constants)))
    (if constants
        (loop with constant-vector = (allocate-managed-simple-vector count)
              for constant in constants
              for index from 0 to (-f count 1)
              do
          (setf (svref constant-vector index) constant)
              finally
                (reclaim-slot-value-list constants)
                (setf (byte-code-stream-constants byte-code-stream) nil)
                (return constant-vector))
        nil)))


;;; `coalesce-lookup-structures' is used to prepare the lookup structure for
;;; "constantization".  The lookup-structure-entry is reversed and consed onto
;;; the existing entries.  This is so that items with multiple code-bodies (and
;;; hence byte-code-bodies) will have the lookup-structure-entry for each
;;; byte-code-body be in the correct poistion.   Note that the byte-code-streams are
;;; visited in outer to inner order, so the base stream is always taken care of first.

(defun coalesce-lookup-structures (lookup-structure-entry?
                                    byte-code-stream
                                    &optional recursive-p)
  (when lookup-structure-entry?
    (let ((base-stream? (byte-code-stream-base-stream? byte-code-stream)))
      ;; Ignore the bogus superior-stream? nonsense.  It's unused. -dkuznick, 2/9/99
      (if base-stream?
          (progn (coalesce-lookup-structures lookup-structure-entry?
                                             base-stream? t)
                 (setf (byte-code-stream-text-position-information?
                         byte-code-stream)
                       nil))
          (setf (byte-code-stream-text-position-information?
                  byte-code-stream)
                ;; Nreverse each entry to make lookup easier.  If this winds up
                ;; being too expensive, we can rewrtite the lookup function,
                ;; get-annotation-for-address-if-any to be smarter,
                (phrase-cons (nreverse lookup-structure-entry?)
                             (and recursive-p
                                  (byte-code-stream-text-position-information?
                                    byte-code-stream))))))))




;;;; Stack Conses




;;; The cons pool stack-cons is made for use in the stack evaluator compiler and
;;; other facilities.

(defconser stack stack-utils)






;;;; Variables for Evaluator Support




;;; The global variable list-of-new-evaluators contains all defined new
;;; evaluators.  It is defined for development only.

;#+development
;(defvar list-of-new-evaluators nil)

;; Not currently used.  -jra 11/23/90




;;; The global property `stack-evaluators' relates a symbol produced as the
;;; parsed operator of an expression with a list of stack evaluator descriptions
;;; for that operation.  There will be more than one evaluator for operations
;;; which type optimized versions of the evaluator.

(def-global-property-name stack-evaluators)

#+unused
(defun stack-evaluators-function (symbol)
  (stack-evaluators symbol))




;;; The constants `maximum-number-of-in-line-evaluators' and
;;; `maximum-number-of-funcalled-evaluators' contain the maximum number of
;;; in-line and out-of-line evaluators.

;;; The constant `base-in-line-evaluator-number' is the lowest in-line evaluator
;;; number.

;;; The global variable `in-line-evaluator-array' contains an array which holds
;;; in-line evaluator descriptions.  The index to this array entry is the
;;; normalized in-line evaluator number, i.e., the in-line number minus the
;;; base-in-line-evaluator-number.

;;; The global variable `funcalled-evaluator-array' contains an array which
;;; holds descriptions of all out-of-line evaluators.

;;; The global variable `funcalled-evaluator-functions' and
;;; `funcalled-evaluator-dispatch-type' contain an array of functions and
;;; function dispatch types respectively.

;;; These variables and constants describe the data structure which will be used
;;; to store declarative information about the evaluators.

(defconstant dispatch-instruction-number 255)
(defconstant maximum-number-of-extended-inline-evaluators 250) ; DO NOT INCREASE!
(defconstant maximum-number-of-in-line-evaluators 106)
(defconstant base-in-line-evaluator-number 150)

;;; The maximum available value is 256
(defconstant maximum-number-of-funcalled-evaluators 200)

(defvar in-line-evaluator-array ;modified by SoftServe
  (make-array-with-nils (+f maximum-number-of-in-line-evaluators
			    maximum-number-of-extended-inline-evaluators)))

(defvar funcalled-evaluator-array
  (make-array-with-nils maximum-number-of-funcalled-evaluators))

(defvar funcalled-evaluator-functions
  (make-array-with-nils maximum-number-of-funcalled-evaluators))

(defvar funcalled-evaluator-dispatch-type
  (make-array-with-nils maximum-number-of-funcalled-evaluators))

(defmacro svref-without-inlining (vector index)
  `(svref ,vector ,index))

(defmacro svref-with-inlining (vector index)
  `(svref ,vector ,index))



;;; The macros `evaluator-name', `instruction-name', `evaluator-environments',
;;; `evaluator- arguments', `evaluator-result-type', `evaluator-printer-
;;; function', `evaluator-function-or-macro-name', `evaluator-in-line-p', and
;;; `evaluator-number' access the elements of an evaluator-description.  SETF
;;; may be used with this accessors to mutate the description slot value.

(defmacro evaluator-name (evaluator-description)
  `(svref ,evaluator-description 0))

(defmacro instruction-name (evaluator-description)
  `(svref ,evaluator-description 1))

(defmacro evaluator-instruction-precedence (evaluator-description)
  `(svref ,evaluator-description 2))

(defmacro evaluator-environments (evaluator-description)
  `(svref ,evaluator-description 3))

(defmacro evaluator-arguments (evaluator-description)
  `(svref ,evaluator-description 4))

(defmacro evaluator-result-type (evaluator-description)
  `(svref ,evaluator-description 5))

(defmacro evaluator-printer-function (evaluator-description)
  `(svref ,evaluator-description 6))

(defmacro evaluator-function-or-macro-name (evaluator-description)
  `(svref ,evaluator-description 7))

(defmacro evaluator-in-line-p (evaluator-description)
  `(svref ,evaluator-description 8))

(defmacro evaluator-number (evaluator-description)
  `(svref ,evaluator-description 9))

(defmacro evaluator-result-in-register-1? (evaluator-description)
  `(svref ,evaluator-description 10))

(defmacro evaluator-pprinter-function (evaluator-description)
  `(svref ,evaluator-description 11))

(defmacro evaluator-expanded-body (evaluator-description)
  `(svref ,evaluator-description 12))

(defmacro evaluator-function-name (evaluator-description)
  `(svref-with-inlining ,evaluator-description 13))

(defmacro evaluator-dispatch-code (evaluator-description)
  `(svref ,evaluator-description 14))


;;; The macro `in-line-evaluator-op-code-p' takes a fixnum op-code and returns
;;; whether or not that op-code is in the range of op-codes used by the in-line
;;; evaluators.

(def-substitution-macro in-line-evaluator-op-code-p (op-code)
  (and (>=f op-code base-in-line-evaluator-number)
       (<f op-code (+f base-in-line-evaluator-number
                       maximum-number-of-in-line-evaluators))))






;;;; Compiler Tree Nodes




;;; The structure `stack-node' is used during stack compilations to hold
;;; information about an expression being compiled.

(def-structure (stack-node
                 (:constructor
                   make-stack-node-1
                   (stack-node-operation
                     stack-node-evaluator-descriptions))
                 (:print-function print-stack-node))
  stack-node-operation
  (stack-node-argument-nodes nil :reclaimer reclaim-stack-list)
  stack-node-evaluator-descriptions
  (stack-node-chosen-evaluator nil)
  (stack-node-required-value-type nil)
  (stack-node-value-type nil)
  (stack-node-type nil)
  (stack-node-tree-type nil)
  (stack-node-stack-frame-vars-needed 0)
  ;;Continuations do not survive the scope of the optimizer
  (stack-node-continuation nil)                ;holds an optimizer structure
  (stack-node-free-reference-type nil))

(def-structure (stack-node-instruction
                 (:constructor
                   make-stack-node-instruction-1
                   (stack-node-operation
                     stack-node-instruction-extra-info))
                 (:include stack-node)
                 (:print-function print-stack-node)
                 (:reclaimer reclaim-stack-node-instruction-1))
  stack-node-instruction-extra-info
  (stack-node-instruction-chosen-instruction nil))



#+development
(defun print-stack-node (stack-node stream depth)
  (printing-random-object (stack-node stream)
    (print-stack-node-1 stack-node stream depth)))

#+development
(defun print-stack-node-1 (stack-node stream depth)
  (format
    stream "(~a"
    (or (and (stack-node-chosen-evaluator stack-node)
             (instruction-name
               (stack-node-chosen-evaluator stack-node)))
        (stack-node-operation stack-node)))
  (when (and (stack-node-instruction-p stack-node)
             (stack-node-instruction-extra-info stack-node))
    (write-char #\space stream)
    (prin1 (stack-node-instruction-extra-info stack-node) stream))
  (let ((args (stack-node-argument-nodes stack-node)))
    (when args
      (if (or (not (fixnump *print-level*))
              (<= depth *print-level*))
          (loop for arg in args do
            (write-char #\space stream)
            (print-stack-node-1 arg stream (1+ depth)))
          (write-string " ...")))
    (write-string ")" stream)))


(defun reclaim-stack-list-of-nodes (stack-list-of-stack-nodes)
  (when stack-list-of-stack-nodes
    (loop for stack-node in stack-list-of-stack-nodes
          do
      (cond ((stack-node-p stack-node)
             (reclaim-stack-node stack-node))
            ((stack-node-instruction-p stack-node)
             (reclaim-stack-node-instruction stack-node))
            (t
             (error "Can't reclaim."))))
    (reclaim-stack-list stack-list-of-stack-nodes))
  nil)


#+unused
(defun stack-node-value-type-function (stack-node)
  (stack-node-value-type stack-node))

(defvar stack-nodes-to-reclaim)

(defmacro make-stack-node
          (stack-node-operation stack-node-evaluator-descriptions)
  (let ((new-node (gensym)))
    `(let ((,new-node (make-stack-node-1
                        ,stack-node-operation
                        ,stack-node-evaluator-descriptions)))
       (setq stack-nodes-to-reclaim
             (stack-cons ,new-node stack-nodes-to-reclaim))
       ,new-node)))

(defmacro make-stack-node-instruction
          (stack-node-operation stack-node-instruction-extra-info
                                &optional chosen-instruction?)
  (let ((new-node (gensym)))
    `(let ((,new-node (make-stack-node-instruction-1
                        ,stack-node-operation
                        ,stack-node-instruction-extra-info)))
       ,@(when chosen-instruction?
           `((setf (stack-node-instruction-chosen-instruction ,new-node)
                   ,chosen-instruction?)))
       (setq stack-nodes-to-reclaim
             (stack-cons ,new-node stack-nodes-to-reclaim))
       ,new-node)))




;;; The macro `with-compiler-stack-nodes' sets up the environment for
;;; automatically reclaimed stack-nodes.  All stack-nodes (and stack node
;;; instructions for that matter) created within the scope of this wrapper will
;;; be reclaimed on exit from the form.

(defmacro with-compiler-stack-nodes (&body forms)
  `(let ((stack-nodes-to-reclaim nil))
     (unwind-protect
         (progn ,@forms)
       (reclaim-stack-list-of-nodes stack-nodes-to-reclaim))))




;;; The function `indirectly-denoted-item-p' takes a stack-node-tree (i.e.  a
;;; compiled expression) that should denote an item.  If the stack-node-tree
;;; denotes an indirectly referenced item, i.e., an item that is not specified
;;; by a name that is known at compile time, then this function returns t.

(defun indirectly-denoted-item-p (stack-node-tree)
  (when (stack-node-instruction-p stack-node-tree)
    (let ((operation (stack-node-operation stack-node-tree)))
      (case operation
        ((name-reference) nil)
        ((push-cached-item) nil)
        ((ensure-type)
         (and (type-specifications-could-intersect-p
                (stack-node-required-value-type stack-node-tree)
                '(class item))
              (indirectly-denoted-item-p
                (car-of-cons (stack-node-argument-nodes stack-node-tree)))))
        (t t)))))






;;;; Stability and Dependence Predicates




;;; Within development of 3.1, we are adding compiler optimizations where items
;;; that are dependent are allowed to compile in reliance on some stable
;;; characteristics of a KB.  (Add lots more... -jra & cpm 1/11/93)

;;; The function `dependent-compilation-p' takes one optional argument, a frame
;;; which defaults to the *current-computation-frame*.  This predicate returns
;;; true if the given frame is allowed to incorporate information about stable
;;; frames within its compilations.

(defun dependent-compilation-p (&optional (frame *current-computation-frame*))
  (if (and collecting-free-references (framep frame))
      (block-can-be-dependent-p frame)
      nil))

;; The above predicate must test the frame argument.  Note that current-
;; computation-frame, the default argument value, can sometimes be NIL.  This
;; could happend, for example, when a frame is being deleted by the user and a
;; free-reference-analysis function, such as check-for-valid-procedure-call, is
;; being called.  - cpm, 8/1/94



;;; The function `stable-class-p' takes a symbol that might name a class, and
;;; returns whether or not the class with that name is stable, and so may be
;;; depended upon by compilations in dependent frames.  This function also takes
;;; an observer-frame, which defaults to *current-computation-frame*.

;;; Note that non-permanent items are not considered stable because they cannot
;;; be depended item.

(defun stable-class-p (class &optional observer-frame?)
  (declare (ignore observer-frame?))
  ;; Check if the class is defined by the system or is declared stable.
  (or (system-defined-class-p class)
      (and (classp class)
           (let ((definition?
                   (get-instance-with-name-if-any 'class-definition class)))
             (and definition?
                  (not (block-is-unstable-p definition?))
                  (permanent-block-p definition?))))))

;; Note that this code does not yet handle hierarchies of classes and stability
;; issues in them.  It only checks that the class is system defined or that
;; the class-definition for the class is stable.  How will we deal with
;; hierarchies?  -jra 2/9/93 I now know!  There is a separate declaration for
;; stable-subclass that handles all depended upon interrelationships between
;; user defined classes.  -jra 12/1/94




;;;




;;; The function `stable-denoted-procedure-p' takes a stack-node-tree (i.e. a
;;; compiled expression) that should denote a procedure and it takes an optional
;;; observer-frame.  If the stack-node-tree denotes a stable procedure from the
;;; perspective of the observer, then this function should return that
;;; procedure.

;;; Note that the argument to this function must be the compiled
;;; stack-node-tree, instead of just the symbol that is to be evaluated to
;;; obtain the procedure being called.  If the symbol is a local name in this
;;; environment, then the local name overrides any global name.  This can most
;;; easily be determined examining the compiled form of the expression.

;; See stack-node-instruction-var-spot-reference-p.  - cpm, 1/15/93

;;; This "perspective of the observer" stuff is a hook for us to possibly allow
;;; procedures to consider themselves stable for recursive calls.  -jra & cpm
;;; 1/12/93

;; Note that for now, this should only return procedures, not
;; remote-procedure-declarations.  -jra 1/12/93

(defun stable-denoted-procedure-p
    (stack-node-tree &optional (observer-frame? *current-computation-frame*))
  (let ((denoted-name? 
         (denoted-name-of-type-p stack-node-tree '(class procedure))))
    (and denoted-name?
         (stable-name-of-class-p denoted-name? 'procedure observer-frame?))))

(defun denoted-name-of-type-p (stack-node-tree type-specification)
  (when (stack-node-instruction-p stack-node-tree)
    (let ((operation (stack-node-operation stack-node-tree)))
      (case operation
        ((name-reference)
         (stack-node-instruction-extra-info stack-node-tree))
        ((push-cached-item)
         (stack-node-instruction-extra-info stack-node-tree))
        ((ensure-type)
         (and (type-specifications-could-intersect-p
                (stack-node-required-value-type stack-node-tree)
                type-specification)
              (denoted-name-of-type-p
                (car-of-cons (stack-node-argument-nodes stack-node-tree))
                type-specification)))
        (t
         nil)))))




;;; The function `stable-name-p' takes a symbol that might name an item, and
;;; returns whether or not the item with that name is stable, and so may be
;;; depended upon by compilations in dependent frames.  This function returns
;;; the frame or NIL.  This function also takes an observer-frame, which
;;; defaults to *current-computation-frame*.

;;; Note that non-permanent items are not considered stable because they cannot
;;; be depended item.

;; Note that references to method-declarations (i.e., method-declaration
;; dispatches) are not stable.  For this to be possible, we would need to add
;; restrictions on definitions of this method and on the related class
;; hieararchy.  - cpm, 2/15/94

(defun stable-name-p
    (name &optional (observer-frame? *current-computation-frame*))
  (stable-name-of-class-p name 'item observer-frame?))

(defun stable-name-of-class-p (name class observer-frame)
  (let* ((frame? (get-instance-with-name-if-any class name))
         (frame-class? (and frame? (class frame?))))
    (when (and frame? frame-class?
               ;; Cannot depend on stable items with duplicate names.
               (let ((name-or-names? (frame-or-frames-with-this-name name)))
                 (or (symbolp name-or-names?)
                     (not (and (consp name-or-names?) (cdr name-or-names?)))))
               ;; Procedure method dispatches cannot currently be stable.

               ;; Why not?  FIND ME, JRA!  -jra 11/21/96
               (not (frame-of-class-p frame? 'method-declaration))
               ;; Check if the frame is stable.  Frames that refer to itself are
               ;; stable, even without a stable declaration.  Non-permanent
               ;; items are not considered stable because they cannot be
               ;; depended item.
               (or (eq frame? observer-frame)
                   (and (not (block-is-unstable-p frame?))
                        (permanent-block-p frame?)))
               ;; The user-defined definitions of stable objects must also be
               ;; stable.
               (or (system-defined-class-p frame-class?)
                   (let ((frame-class-definition?
                           (get-instance-with-name-if-any
                             'class-definition frame-class?)))
                     (when frame-class-definition?
                       (and (not (block-is-unstable-p frame-class-definition?))
                            (permanent-block-p frame-class-definition?))))))
      frame?)))



;;; `inner-block-cant-be-inlined-in-outer-block?' is used to implement the new
;;; restriction that inlining is only valid for blocks in the same
;;; module. It will return a keyword explining why, or NIL meaning that the
;;; inlining is allowable.  Notice that the first reason will always take
;;; precedence over the rest.  -dkuznick, 10/29/98

(defun-simple inner-block-cant-be-inlined-in-outer-block? (inner outer)
  (cond ((not (block-can-be-inlined-p inner))
         :inner-block-not-inlineable)
        ((neq (get-module-block-is-in inner)
              (get-module-block-is-in outer))
         :cross-module-violation)
        (t nil)))





;;;; Stability and Dependent Changes to Items




;;; This section contains functions that test for and handle de-stabilizing
;;; operations on and changes to an item.  For example, a stable item is
;;; de-stabilized if its name is changed.  Also, in this section are functions
;;; that handle changes to the dependent and stable status of an item.  This
;;; status change can occur, for example, when a stable declaration is remove
;;; from an item's configuration.




;;; The following consistency-analysis functions, check-for-unstable-instance-
;;; name and check-for-unstable-class, are used to check if stable-related
;;; free-references are no longer valid.  If it is not valid, the item that's
;;; being analyzed is marked as incomplete and will require recompiling to be
;;; complete.  The stable free-reference can become invalid if:
;;; - the item in the free-reference is no longer stable;
;;; - the item containing the free-reference is no longer dependent;
;;; - the conditions used in the free-reference are no longer correct (for
;;; example the name of a stable item may have changed).

;;; Notes:
;;; 1. The following stable/dependent consistency-analysis functions should
;;; check stability, dependence, and the conditions of the stable
;;; free-reference.
;;; 2. Only the dependent item currently being analyzed can be made incomplete.
;;; This type of analysis is not further propagated to items that depend on the
;;; dependent item being analyzed.
;;; 3. If this analysis did not result from a runtime change, the user is asked
;;; if they would like an INSPECT recompile of incomplete items launched
;;; automatically.  This is a way of recompiling all dependent items that were
;;; made incomplete because of a destabilizing change.  Note that this function
;;; sets a flag that will launch an INSPECT, if within the context that checks
;;; the flag.  This is done so that multiple requests can be combined into one
;;; launching of INSPECT.
;;; 4. Note the case of an expression cell of a freeform-table being analyzed.
;;; If the cell can no longer depend on an item as being stable, then the entire
;;; freeform-table is made incomplete.  Currently, an individual cell cannot be
;;; made incomplete.

;; Note that these functions could cause a security problem, if access to
;; INSPECT is restricted through configurations!!  Currently, the function
;; frame-system-operation-is-allowed-p does not check for INSPECT restrictions.
;; So, we are not able to test for this restriction.  - cpm, mhd, 2/25/94

;; Most consistency-analysis functions are in INSTALL, but these functions
;; should be kept near the stability predicates so they can more easily be kept
;; in synch.  - cpm, 2/24/94

(defvar compiled-item-being-analyzed-started-out-incomplete? nil)

;;; The function `note-invalid-stable-free-reference' is used during consistency
;;; analysis to indicate that a free-reference involving stability is no longer
;;; valid.

(defun note-invalid-stable-free-reference (compiled-item-with-reference name)
  ;; May need to write out the item, if the KB is currently being saved.
  (note-change-to-block compiled-item-with-reference nil)
  (add-to-frame-note-particulars-list-if-necessary
    name 'item-depends-on-modified-stable-item compiled-item-being-analyzed)
  (update-frame-status compiled-item-with-reference 'incomplete nil)
  ;; May launch an INSPECT recompile of incomplete items.
  (unless (and compiled-item-being-analyzed-started-out-incomplete?
               (not compiling-incomplete-items-after-analyze-p))
    (record-item-made-incomplete-if-appropriate compiled-item-with-reference)))

;;; The function `note-invalid-stable-hierarchy' is used during consistency
;;; analysis to indicate that the heirarchy is no longer stable

(defun note-invalid-stable-hierarchy (frame-with-invalid-assumption stability-particulars)
  ;; May need to write out the item, if the KB is currently being saved.
  (note-change-to-block frame-with-invalid-assumption nil)
  (add-to-frame-note-particulars-list-if-necessary
    stability-particulars 'item-depends-on-unstable-heirarchy compiled-item-being-analyzed)
  (update-frame-status frame-with-invalid-assumption 'incomplete nil)
  ;; May launch an INSPECT recompile of incomplete items.
  (unless (and compiled-item-being-analyzed-started-out-incomplete?
               (not compiling-incomplete-items-after-analyze-p))
    (record-item-made-incomplete-if-appropriate frame-with-invalid-assumption)))


;;; The function `note-invalid-inlining' is used during consistency
;;; analysis to indicate that either the item being inlined has changed or is
;;; not in the same module as the caller.  In either case the inlining
;;; is no longer valid

(defun note-invalid-inlining (frame-with-invalid-assumption stability-particulars)
  ;; May need to write out the item, if the KB is currently being saved.
  (note-change-to-block frame-with-invalid-assumption nil)
  (add-to-frame-note-particulars-list-if-necessary
    stability-particulars 'item-depends-on-invalid-inlining compiled-item-being-analyzed)
  (update-frame-status frame-with-invalid-assumption 'incomplete nil)
  ;; May launch an INSPECT recompile of incomplete items.
  (unless compiled-item-being-analyzed-started-out-incomplete?
    (record-item-made-incomplete-if-appropriate frame-with-invalid-assumption)))


;;; The function `note-independent-item-in-stable-free-reference' is used during
;;; consistency analysis to indicate that a free-reference involving stability
;;; is no longer valid.  The dependent item is now independent.

(defun note-independent-item-in-stable-free-reference (compiled-item-with-reference)
  ;; May need to write out the item, if the KB is currently being saved.
  (note-change-to-block compiled-item-with-reference nil)
  (add-frame-note 'item-no-longer-dependent compiled-item-being-analyzed)
  (update-frame-status compiled-item-with-reference 'incomplete nil)
  ;; May launch an INSPECT recompile of incomplete items.
  (unless compiled-item-being-analyzed-started-out-incomplete?
    (record-item-made-incomplete-if-appropriate compiled-item-with-reference)))



;;; The function `check-for-unstable-instance-name' is used to check if the
;;; free-reference to an item is no longer stable.  See above for more comments.

(defun check-for-unstable-instance-name (name)
  (add-or-delete-as-item-referring-to-name name)
  (unless delete-as-item-referring-to-name?
    (cond
      ((not (block-can-be-dependent-p compiled-item-being-analyzed))
       (note-independent-item-in-stable-free-reference
         compiled-item-being-analyzed))
      ((not (stable-name-p name compiled-item-being-analyzed))
       ;; Unstable item, non-existent item, or not compiled-item-being-
       ;; analyzed.  Note that non-stable items can depend on themselves being
       ;; stable.
       (note-invalid-stable-free-reference
         compiled-item-being-analyzed name)))))



;;; The function `check-for-unstable-instance-name-of-class' is used to check if
;;; the free-reference to an item of a given class is no longer valid.

(defun check-for-unstable-instance-name-of-class (name class)
  (add-or-delete-as-item-referring-to-name name)
  (unless delete-as-item-referring-to-name?
    (cond
      ((not (block-can-be-dependent-p compiled-item-being-analyzed))
       (note-independent-item-in-stable-free-reference
         compiled-item-being-analyzed))
      ((not (stable-class-p class compiled-item-being-analyzed))
       ;; The class of a stable item must also be stable.
       (note-invalid-stable-free-reference compiled-item-being-analyzed class))
      ((not (stable-name-of-class-p name class compiled-item-being-analyzed))
       ;; Unstable item, non-existent item, or not compiled-item-being-
       ;; analyzed.  Note that non-stable items can depend on themselves being
       ;; stable.
       (note-invalid-stable-free-reference
         compiled-item-being-analyzed name)))))




;;; The function `check-for-unstable-class-and-not-subclass' is used to check if
;;; the free-reference to a class or it's subclass is no longer stable.  See
;;; above for more comments.

(defun check-for-unstable-class-and-subclass (class subclass)
  (add-or-delete-as-item-referring-to-name class)
  (add-or-delete-as-item-referring-to-name subclass)
  (unless delete-as-item-referring-to-name?
    (cond
      ((not (block-can-be-dependent-p compiled-item-being-analyzed))
       (note-independent-item-in-stable-free-reference
         compiled-item-being-analyzed))
      ((not (stable-class-p class compiled-item-being-analyzed))
       (note-invalid-stable-free-reference compiled-item-being-analyzed class))
      ((not (stable-class-p subclass compiled-item-being-analyzed))
       (note-invalid-stable-free-reference
         compiled-item-being-analyzed subclass))
      ((not (subclassp subclass class))
       ;; Should be a subclass.
       ;; Not certain which class has changed.  So, mention both.
       (note-invalid-stable-free-reference compiled-item-being-analyzed class)
       (note-invalid-stable-free-reference
         compiled-item-being-analyzed subclass)))))



(defun check-for-invalid-inlining (reference)
  (gensym-dstruct-bind ((class? method-or-procedure-name arg-count md5-id)
                       reference)
    (add-or-delete-as-item-referring-to-name method-or-procedure-name)
    (when class?
      (add-or-delete-as-item-referring-to-name class?))
    (unless delete-as-item-referring-to-name?
      (let ((focus-procedure?
              (if class?
                  (let* ((class-description? (class-description class?))
                         (found-method-or-error-text
                           (if class-description?
                               (get-specific-method
                                 method-or-procedure-name class-description?
                                 arg-count nil nil nil)
                               #w"Class is undefined")))
                    (if (text-string-p found-method-or-error-text)
                        nil
                        found-method-or-error-text))
                  (get-instance-with-name-if-any
                    'procedure method-or-procedure-name)))
            (reason-for-inlining-failure? nil))
        (when (or (null focus-procedure?)
                  (let ((focus-md5?
                          (get-slot-value focus-procedure? 'md5-identifier?)))
                    (not (and focus-md5?
                              (string=w md5-id focus-md5?)
                              (let ((inlining-failure-reason?
                                      (inner-block-cant-be-inlined-in-outer-block?
                                        focus-procedure?
                                        compiled-item-being-analyzed)))
                                ;; Yes I know this next form is ugly.  Read it
                                ;; like "the inlining is allowed" -dkuznick, 11/18/98
                                (not
                                  (setq reason-for-inlining-failure?
                                        ;; Allow the loading of old kb's with cross-module violations
                                        ;; if the inlined procedures are really the same -dkuznick, 12/18/98
                                        (if (and (eq inlining-failure-reason?
                                                     :cross-module-violation)
                                                 reading-kb-p)
                                            nil
                                            inlining-failure-reason?))))))))
          (note-invalid-inlining
            compiled-item-being-analyzed
            (slot-value-list class?
                             method-or-procedure-name
                             arg-count
                             reason-for-inlining-failure?)))))))



;;; The function `check-for-unstable-class-and-non-subclass' is used to check if
;;; the free-reference to a class or another non-subclass is no longer stable.
;;; See above for more comments.

(defun check-for-unstable-class-and-non-subclass (class non-subclass)
  (add-or-delete-as-item-referring-to-name class)
  (add-or-delete-as-item-referring-to-name non-subclass)
  (unless delete-as-item-referring-to-name?
    (cond
      ((not (block-can-be-dependent-p compiled-item-being-analyzed))
       (note-independent-item-in-stable-free-reference
         compiled-item-being-analyzed))
      ((not (stable-class-p class compiled-item-being-analyzed))
       (note-invalid-stable-free-reference compiled-item-being-analyzed class))
      ((not (stable-class-p non-subclass compiled-item-being-analyzed))
       (note-invalid-stable-free-reference
         compiled-item-being-analyzed non-subclass))
      ((subclassp non-subclass class)
       ;; Should NOT be a subclass.
       ;; Not certain which class has changed.  So, mention both.
       (note-invalid-stable-free-reference compiled-item-being-analyzed class)
       (note-invalid-stable-free-reference
         compiled-item-being-analyzed non-subclass)))))



;;; The function `check-for-valid-stable-procedure-call' checks that a call to a
;;; stable procedure is still valid.

(defun check-for-valid-stable-procedure-call
    (type-of-call name arg-types return-types)
  (add-or-delete-as-item-referring-to-name name)
  (unless delete-as-item-referring-to-name?
    ;; First, test that the compiled item is dependent and that the named item
    ;; is stable.  (This is similar to check-for-unstable-instance-name.)  Then,
    ;; test if the procedure-call is valid.
    (cond
      ((not (block-can-be-dependent-p compiled-item-being-analyzed))
       (note-independent-item-in-stable-free-reference
         compiled-item-being-analyzed))
      ((not (stable-name-p name compiled-item-being-analyzed))
       ;; Unstable item, non-existent item, or not compiled-item-being-
       ;; analyzed.  Note that non-stable items can depend on themselves being
       ;; stable.
       (note-invalid-stable-free-reference compiled-item-being-analyzed name))
      (t
       (let ((valid-stable-procedure-call?
              (check-for-valid-procedure-call
                type-of-call name arg-types return-types t nil)))
         (unless valid-stable-procedure-call?
           (note-invalid-stable-free-reference
             compiled-item-being-analyzed name)))))))





;;; The function `destabilizing-operation-restricted-for-item-p' tests if one of
;;; the restricted operations would cause inconsistencies for items that are
;;; dependent on the given stable item.

;;; Note that the resticted operations, include some types of edits and
;;; transferring, and vary depending on whether the operation is being done
;;; manual or from an action.  This function does not test the operation.  It
;;; tests only the item.

;;; The complete set of restricted actions (in reference to manual or runtime)
;;; changes is not described here.  Each restricted action or UI operation calls
;;; this predicate when necessary.

(defun destabilizing-operation-restricted-for-item-p (item)
  (and (not (block-is-unstable-p item))
      ;; Test for "permanent" items because the operation is allowed on
      ;; transient and "non-transient-non-permanent" stable items.
       (permanent-block-p item)))

;; Review this predicate.  Perhaps, it should be part of frame-system-
;; operation-is-allowed-p, but that function does not currently allow a
;; stability or dependent argument.  - cpm, 2/24/94

;; Note that unlike stable-name-of-class-p, this function does not test for
;; special cases, such as checking if the item is a method-declaration.
;; Currently, method-declarations cannot be depended upon to be stable.  But, we
;; still want to disallow destabilizing operations on methods because, in future
;; release, we would like to allow dependence on their stability.  Our policy
;; for future releases is too allow restrictions to be relaxed, but not to be
;; made more restrictive.  - cpm, 2/24/94




;;; The function `destabilizing-item-deletion-p' examines the class and workspace
;;; hierarchy of an item that is a candidate for deletion.  When it finds an item
;;; on the hierarchy for which a destabilizing operation is restricted (as deter-
;;; mined by destabilizing-operation-restricted-for-item-p), it returns that item;
;;; otherwise it returns nil.

(defun destabilizing-item-deletion-p (item)
  (cond ((destabilizing-operation-restricted-for-item-p item)
         item)
        ((and (class-definition-p item)
              ;; This loop only checks for stable definitions, and not stable
              ;; class/subclass instances, because the stability of instances
              ;; can only be depended upon when the definitions are also stable.
              (loop with class-name? = (name-of-defined-class item)
                    for subclass being each subclass of class-name?
                    for subclass-definition = (class-definition subclass)
                    thereis
                    (and (destabilizing-operation-restricted-for-item-p
                           subclass-definition)
                         subclass-definition))))
        ((and (entity-p item)
              (subworkspaces item)
              (loop for subworkspace in (subworkspaces item)
                    thereis
                    (loop for subblock being each subblock of subworkspace
                          thereis
                          (and (item-p subblock)
                               (destabilizing-item-deletion-p subblock))))))
        (t nil)))

;; Consider renaming the above function so that it can be used for other
;; operations besides delete.  A possible new name is destabilizing-operation-
;; restricted-for-item-in-hiearchy-p.  - cpm, 2/15/95




;;; `Destabilizing-slot-p' is true if the designated slot could cause
;;; destabilization.

;;; Only those attributes of stable items that are depended upon for stable
;;; optimizations are restricted.  These are the name of items, the class and
;;; superior-classes of a definition, and the text of procedure and remote
;;; procedures.  (There are several exceptions for these slots, when either the
;;; slot, or another related slot, has a value of "none".)

;;; This predicate should be updated as new stable attributes are depended upon
;;; (ie., when there are new stable free-references).

(defun destabilizing-slot-p (frame slot-description)
  (let ((slot-name (pretty-slot-name slot-description)))
    (frame-class-case frame
      (procedure
        (eq slot-name 'procedure-definition))
      (remote-procedure-declaration
        (eq slot-name 'box-translation-and-text))
      (definition
          (cond ((eq slot-name 'name-of-defined-class)
                 ;; If the class name is not "none", an item may be depending on
                 ;; this definition.
                 (not (null (get-slot-value frame 'name-of-defined-class))))
                ((eq slot-name 'direct-superiors-of-defined-class)
                 ;; If both the class name and direct-superiors are not "none",
                 ;; the change could affect dependent items.
                 (not (null
                        (and (get-slot-value frame 'name-of-defined-class)
                             (get-slot-value
                               frame 'direct-superiors-of-defined-class)))))))
      (block
          (and (eq slot-name 'name-or-names-for-frame)
               ;; If the name is not "none", the change could affect a dependent
               ;; item.
               (not (null (get-slot-value frame 'name-or-names-for-frame))))))))



;;; `Restrict-destabilization-p' is true if a destabilization operation on frame
;;; is a restricted operation (in the user-restricted sense) and the designated
;;; slot, if changed, could cause destabilization.

(defun restrict-destabilization-p (frame slot-description)
  (and (destabilizing-slot-p frame slot-description)
       (destabilizing-operation-restricted-for-item-p frame)))



;;; The function `handle-dependent-or-stable-status-change-for-item' is used to
;;; propagate the affects of a change to the dependent or stable status of an
;;; item.  This change could have resulted from a change to configurations
;;; (item, class, kb-workspace, or system-table) or from an operation, such as
;;; transfer, that can affect the configuration of an item.

;;; This function analyzes for consistency this item or other items referring to
;;; this item, as necessary.

;;; Note that this function does not know the cause of the change and so must be
;;; conservative in how it handles it.  For example, it does not know if an
;;; independent or unstable item is newly independent or unstable.  Therefore,
;;; it assumes, in this case, that the status has changed and needs analysis.

;;; Note that when handling an unstable item, all items referring to this item
;;; are analyzed.  Currently, the analysis cannot only be done on the items that
;;; may be dependent on the formerly stable item.  This could be improved.

;;; Note that this function does not propagate the affects of the status change
;;; to subblocks of the given item.  This should be handled by the caller of
;;; this function, if necessary.

(defun-simple handle-dependent-or-stable-status-change-for-item (item)
  (let* ((permanent-p? (permanent-block-p item))
         (name-or-names? (name-or-names-for-frame item))
         (name? (if (consp name-or-names?)
                    (car name-or-names?)
                    name-or-names?)))
    (when (and name? permanent-p?)
      ;; Analyze all items that refer to this item.  This includes items that
      ;; depend on this stable or formerly stable item.  This analysis is needed
      ;; both for the cases when the item is newly stable or newly unstable.
      ;; Note that the analysis is done only if the item is permanent.  Items
      ;; that are both transient and stable are not depended upon.
      (analyze-compiled-items-for-consistency name?))

    ;; Analyze this item.  It may either be newly dependent or independent.
    (check-consistency-analysis item)))

;; The above could be made more efficient by analyzing only those items
;; dependent on the given name, instead of calling analyze-compiled-items-for-
;; consistency.  - cpm, 7/22/94




(defun handle-stable-hierarchy-or-inline-status-change-for-item (item &optional (inline-only? nil))
  (cond ((symbolp item)
         (analyze-compiled-items-for-consistency item))
        ((framep item)
         (let* ((permanent-p? (permanent-block-p item))
                method-name?
                method-class?
                )
           ;;methods need to be analyzed both in reference to the class name
           ;;and the method name
           ;;methods require that all dependencies on either the method or class name
           ;; be analyzed
           (when permanent-p?
             (cond ((of-class-p item 'method)
                    (setq method-name?
                          (procedure-method-name-function item))

                    ;; Analyze all items that refer to this item.
                    (analyze-compiled-items-for-consistency method-name?)
                    (unless inline-only?
                      (setq method-class?
                            (procedure-method-class-function item))
                      (analyze-compiled-items-for-consistency method-class?)))
                   ((of-class-p item 'method-declaration)
                    (setq method-name? (name-or-names-for-frame item))
                    (when (consp method-name?)
                      (setq method-name? (car method-name?)))
                    (analyze-compiled-items-for-consistency method-name?))
                   ((of-class-p item 'function-definition)
                    (when (get-slot-value item 'name-or-names-for-frame)
                      (setq method-name? (get-slot-value item 'name-or-names-for-frame))
                      (when (consp method-name?)
                        (setq method-name? (car method-name?))
                        (analyze-compiled-items-for-consistency method-name?))))
                   (t nil)))

           ;; Analyze this item.  It may either be newly dependent or independent.
           (check-consistency-analysis item)))
        (t
         #+development
         (break "neither a symbol nor a frame"))))



;;;; Special Form Converters




;;; The first part of the stack compiler process converts parsed s-expressions
;;; into trees of stack-node and stack-node-instruction structures.  These
;;; structures are used by the compiler to register type and chosen instruction
;;; information during the compile.  The default format for these parsed
;;; s-expressions is a list whose CAR is a declared in-line or funcalled
;;; evaluator and which takes a fixed number of expressions or designations as
;;; arguments.  Note that a particular operator may take differing numbers of
;;; operators, if seperate in-line and funcalled-evaluators have been declared
;;; for each argument count.

;;; Forms which do not meet the criteria above must be converted from
;;; s-expressions to stack-node trees using a special form converter function.
;;; Special form converter functions are defined using the macro
;;; `def-special-form-converter', defined below.  The first argument to the
;;; macro is the operator name to convert.  The second argument is the argument
;;; list of the function to be defined.  This argument list should take one
;;; argument, which is the expression to be converted.  The macro takes a body
;;; of forms after this as the body of the converter function.

;;; The converter function should convert the given s-expression into a tree of
;;; stack-nodes and stack-node-instructions.  Stack nodes should only be made
;;; for operators which are defined in-line or funcalled evaluators.  Stack node
;;; instructions should be make only for instruction names which have defined
;;; preferred-instruction-choosers and stack-node-instruction-emitters.  The
;;; function convert-expression-to-node-tree should be called on sub-expressions
;;; and designations to convert them.

;;; The global property `stack-special-form-converter' associates operator
;;; symbol names with compiled simple functions implementing converters.

(def-global-property-name stack-special-form-converter)

(defmacro def-special-form-converter (operator arguments &body body)
  (let ((function-name (intern (format nil "~a-STACK-NODE-CONVERTER"
                                       operator))))
    (unless (and (consp arguments) (= (length arguments) 1)
                 (symbolp (car arguments)))
      (warn "Special-form-converter ~a has a bad argument list." operator))
    `(defun-simple-into-place
         (,function-name (stack-special-form-converter ',operator))
         ,arguments
       ,@body)))



;;; The macro `def-default-special-form-converter' is used to define special
;;; form converters that do the default conversion.  A stack-node instruction is
;;; created for the instruction, the arguments are converted into stack-node
;;; trees, and these argument trees are added the argument slot of the
;;; stack-node instruction.

;;; Note that this macro does not evaluate its argument.

(defmacro def-default-special-form-converter (instruction-name)
  `(def-special-form-converter ,instruction-name (expression)
     (let ((instruction-node
             (make-stack-node-instruction ',instruction-name nil)))
       (loop for argument in (cdr expression)
             collect
               (convert-expression-to-stack-node-tree argument)
               into converted-argument-list using stack-cons
             finally
               (setf (stack-node-argument-nodes instruction-node)
                     converted-argument-list))
       instruction-node)))






;;;; Stack Node Preferred Instruction Chooser




;;; The macro `def-preferred-instruction-chooser' takes the name of an
;;; instruction that will be generated in stack node trees and defines the
;;; preferred instruction chooser function for that instruction.  The chooser is
;;; called after a full stack node tree has been built for an expression.  It is
;;; responsible for calling choose-stack-node-instructions-and-types on any
;;; argument nodes it takes, determing its result type and for registering any
;;; free references within that instruction.  There must be a chooser defined
;;; for each instruction emitted into stack node trees.

;;; The macro takes a name of an instruction and a body of forms.  The body will
;;; be executed with the variables stack-node-instruction, required-type, and
;;; extra-info bound to the corresponding values in the stack-node-instruction.
;;; Note that declare ignores must begin the bodies of the chooser if any of
;;; these variables (other than stack-node-instruction) are not used in the
;;; body.

(def-global-property-name preferred-instruction-chooser)

(defmacro def-preferred-instruction-chooser (instruction-name &body forms)
  (let ((function-name (intern (format nil "~a-I-CHOOSER" instruction-name))))
    `(defun-void-into-place
         (,function-name (preferred-instruction-chooser ',instruction-name))
         (stack-node-instruction)
       (let ((required-type
               (stack-node-required-value-type stack-node-instruction))
             (extra-info (stack-node-instruction-extra-info
                           stack-node-instruction)))
         ,@forms))))




;;; The macro `def-stack-node-instruction-emitter' takes the name of a stack
;;; node instruction, and defines an emitter for that instruction.  Note that
;;; the arguments of this instruction will already have been emitted when the
;;; defined emitter function is called for the instruction itself.

;;; The bodies of the emitters will be run with the variables stack-node-
;;; instruction, byte-code-stream, and extra-info bound.  If the extra info
;;; value is not used, then you must declare that it is ignored.  It is assumed
;;; that the byte-code-stream variable will always be referenced.

(def-global-property-name stack-node-instruction-emitter)

(defmacro def-stack-node-instruction-emitter (instruction-name &body forms)
  (let ((function-name (intern (format nil "~a-I-EMIT" instruction-name))))
    `(progn
       (defun-void-into-place
           (,function-name (stack-node-instruction-emitter ',instruction-name))
           (stack-node-instruction byte-code-stream extra-info)
         ,@forms)
       ',instruction-name)))




;;; The macro `def-stack-node-instruction-reclaimer' takes the name of a stack
;;; node instruction, and defines relcaimer for the extra-info of that instruction.

;;; The bodies of the emitters will be run with the variableextra-info bound.

(def-global-property-name stack-node-instruction-reclaimer)

(defmacro def-stack-node-instruction-reclaimer (instruction-name &body forms)
  (let ((function-name (intern (format nil "~a-I-RECLAIM" instruction-name))))
    `(progn
       (defun-void-into-place
           (,function-name (stack-node-instruction-reclaimer ',instruction-name))
           (extra-info)
         ,@forms)
       ',instruction-name)))


;;; The macro `def-stack-node-instruction-copier' takes the name of a stack
;;; node instruction, and defines a copier for  that instruction.

;;; The bodies of the emitters will be run with the variables stack-node-
;;; instruction bound.

(def-global-property-name stack-node-instruction-extra-info-copier)

(defmacro def-stack-node-instruction-extra-info-copier (instruction-name &body forms)
  (let ((function-name (intern (format nil "~a-I-COPY" instruction-name))))
    `(progn
       (defun-simple-into-place
           (,function-name (stack-node-instruction-extra-info-copier ',instruction-name))
           (instruction-original)
         ,@forms)
       ',instruction-name)))






(defun-void reclaim-stack-node-instruction (stack-node-instruction)
  (let ((reclaimer? (stack-node-instruction-reclaimer (stack-node-operation stack-node-instruction))))
    (when reclaimer?
                    (funcall-simple-compiled-function
                reclaimer?
                (stack-node-instruction-extra-info stack-node-instruction))
              (setf (stack-node-instruction-extra-info stack-node-instruction) nil))
    (reclaim-stack-node-instruction-1 stack-node-instruction)))

(defun-simple copy-stack-node-instruction-extra-info (a-stack-node-instruction)
  (let ((copier? (stack-node-instruction-extra-info-copier (stack-node-operation a-stack-node-instruction))))
    (cond (copier?
                    (funcall-simple-compiled-function
                copier? a-stack-node-instruction))
          (t
           (stack-node-instruction-extra-info a-stack-node-instruction)))))


;;;; Expiration Special Form and Expiration Source Nodes




;;; The stack machine compiler transforms expression trees so as to do the least
;;; possible work at run-time for expressions whose value will be unknown, and
;;; to eliminate the run-time checking for unknown values from the majority of
;;; evaluators.  The compilation of expiration normal form trees is described in
;;; documentation in STACK-COMP, but the jist of the definition of normal form
;;; trees is that they only have expiration minimizing nodes within them, which
;;; is the default type of node.  The other two types of nodes are expiration
;;; source nodes, and expiration special form nodes.  Operations which form
;;; special form and source nodes are declared using the two macros defined
;;; below.

;;; The global properties `expiration-special-form-operator' and
;;; `expiration-source-operator' will contain the value true for symbols naming
;;; operations which are expiration special form expiration source nodes.

(def-global-property-name expiration-special-form-operator-p)

(def-global-property-name expiration-source-operator-p)




;;; The macro `def-expiration-special-form-operator' takes a single unquoted
;;; symbol which is the operation of a stack-node-instruction that represents an
;;; expiration special form node.  These operations must be represented as
;;; stack-node-instructions, and their stack-node-instruction-emitters must be
;;; prepared to receive unknown as the values of their arguments.  Note that
;;; expiration source nodes will only return unknown if at least one of thier
;;; arguments could be unknown.

(defmacro def-expiration-special-form (operator)
  `(setf (expiration-special-form-operator-p ',operator) t))




;;; The macro `def-expiration-source-operator' takes a single unquoted symbol as
;;; its argument.  This macro declares that operation to be an expiration source
;;; operator, meaning that this operator may return unknown as a value, though
;;; it cannot accept unknown as an argument.  However, they will not always have
;;; a possible return type of unknown.

(defmacro def-expiration-source-operator (operator)
  `(setf (expiration-source-operator-p ',operator) t))






;;;; Statement and Action Compiler Definition Forms




;;; The global property `procedure-statement-writer' associates writer function
;;; names with the names of procedure statements.

(def-global-property-name procedure-statement-writer)




;;; The global property `procedure-statement-compiler' is used to store compiler
;;; function names for procedure statements.

(def-global-property-name procedure-statement-compiler)




;;; The macro `def-procedure-statement-compiler' takes the name of a parsed
;;; procedure statement and a body of forms as its arguments.  It causes a
;;; compiler function to be defined for that parsed statement name which will be
;;; called with the variable statement bound to the statement to be compiled.

(defmacro def-procedure-statement-compiler
    ((parsed-statement-name statement-printer) &body forms)
  (let ((compiler-function
          (intern (format nil "~a-COMPILER" parsed-statement-name))))
    (multiple-value-bind (declarations-and-documentation rest-of-forms)
        (split-declarations-and-documentation-from-statements forms)
      `(progn
         ,@(when statement-printer
             `((setf (procedure-statement-writer ',parsed-statement-name)
                     #',statement-printer)))
         (defun-simple-into-place
             (,compiler-function
                (procedure-statement-compiler ',parsed-statement-name))
             (statement)
           ,@declarations-and-documentation
           (with-current-annotation-for-sexp statement
             (when generate-source-annotation-info
               (emit-instruction 'annotation
                                 (get-current-annotation-context statement)))
             ,@rest-of-forms)
           nil)
         ',parsed-statement-name))))




;;; The following macros are used to define compilers for actions.  Since these
;;; can be called from both procedures and rules, they need some special
;;; features which go beyond what is available from procedure statement
;;; compilers.

;;; A separate compiler function is defined for each action.  These compilers
;;; are like procedure statement compilers, except that they take two extra
;;; arguments to control their compilation and the instructions they emit.  The
;;; first is unknown-allowed?.  It should control whether the expressions being
;;; evaluated should allow unknown.  The second is leave-on-stack?, and it
;;; controls whether or not the values should be left on the stack by the
;;; emitter when emitting the prolog to an action (see emitters documentation
;;; below).  The compiler needs to know this so that a block of local vars can
;;; be generated by the compiler to hold the cached values.



;;; The global property `action-compiler' is used to store compiler
;;; function names for procedure statements.

(def-global-property-name action-compiler)




;;; The macro `def-action-compiler' takes the name of a parsed action and a body
;;; of forms as its arguments.  It causes a compiler function to be defined for
;;; that action name which will be called with the variable statement bound to
;;; the statement to be compiled, the variable unknown-allowed? bound to a flag
;;; determining if the arguments to the action are allowed to return unknown,
;;; and the variable leave-on-stack? bound to a flag determining if the
;;; arguments to the action should be left on the stack by the action prolog.

(defmacro def-action-compiler
    ((action-name action-printer) &body forms)
  (let ((compiler-function
          (intern (format nil "~a-ACTION-COMPILER" action-name))))
    (multiple-value-bind (declarations-and-documentation rest-of-forms)
        (split-declarations-and-documentation-from-statements forms)
      `(progn
         ,@(when action-printer
             `((setf (procedure-statement-writer ',action-name)
                     #',action-printer)))

         (defun-simple-into-place
             (,compiler-function (action-compiler ',action-name))
             (statement unknown-allowed? leave-on-stack?
                        prolog-stream epilog-stream)
           ,@declarations-and-documentation
           (with-current-annotation-for-sexp statement
             (when generate-source-annotation-info
               (emit-instruction-to-stream
                 prolog-stream
                 'annotation
                 (get-current-annotation-context statement)))
             ,@rest-of-forms))
         ',action-name))))




(def-global-property-name action-method-compiler)



;;;; Pseudo-Instruction Byte Code Emitters




;;; The macro `def-pseudo-instruction-byte-code-emitter' defines a function
;;; which will emit bytes codes to implement a particular pseudo-instruction.
;;; The emitter forms will be executed with the variable instruction bound to
;;; the pseudo-instruction, and the variable byte-code-stream bound to the
;;; current byte-code-stream.  This emitter should be called stack instruction
;;; emitters, and emitters on the layer of write-byte-code-to-stream.

(def-global-property-name pseudo-instruction-byte-code-emitter)

(defmacro def-pseudo-instruction-byte-code-emitter
          (pseudo-instruction-name &body forms)
  (let ((emitter-name
          (intern (format nil "~a-PSEUDO-EMITTER" pseudo-instruction-name))))
    `(progn
       (defun-void-into-place
           (,emitter-name (pseudo-instruction-byte-code-emitter
                            ',pseudo-instruction-name))
           (byte-code-stream instruction)
         ,@forms)
       ',pseudo-instruction-name)))

;;; pseudo-instruction-property lists are a primitive device
;;; for transmitting information between prologs and epilogs
;;; of actions during compilation mostly for the purpose
;;; of making the value-types of the arguments available for
;;; static type dispatching of instructions in the epilog.



(defun create-pseudo-instruction-property-list ()
  (let ((a (allocate-managed-simple-vector 1)))
    (setf (svref a 0) nil)
    a))

(defun reclaim-create-pseudo-instruction-property-list (headed-plist)
  (reclaim-managed-simple-vector headed-plist))

(defmacro pseudo-instruction-property (headed-plist key)
  `(getfq (svref ,headed-plist 0) ,key))

(defun set-pseudo-instruction-property (headed-plist key value)
  (let ((tail? (memq key (svref headed-plist 0))))
    (cond (tail?
           (setf (cadr tail?) value))
          (t
           (setf (svref headed-plist 0)
                 (phrase-cons key
                              (phrase-cons value
                                           (svref headed-plist 0))))))))

(defsetf pseudo-instruction-property set-pseudo-instruction-property)


;;;; Expiration Handling Macros





;;; The macro `min-*' does a min on 2 expirations which are either numbers or
;;; 'never, which is a positive infinity.

(defmacro min-* (e1 e2)
  (if (and (or (symbolp e1) (constantp e1))
           (or (symbolp e2) (constantp e2)))
      `(cond ((eq ,e1 'never) ,e2)
             ((eq ,e2 'never) ,e1)
             (t (minf ,e1 ,e2)))
      `(let ((e1-v ,e1)
             (e2-v ,e2))
         (cond ((eq e1-v 'never) e2-v)
               ((eq e2-v 'never) e1-v)
               (t (mini e1-v e2-v))))))



;;; The macro `minimum-expiration' returns the minimum of two expirations.  Each
;;; expiration could be a fixnum, the symbol never, or nil (i.e., unknown
;;; expiration).

;; Minimum-expiration should be used in place of min-* which should be removed.
;; cpm, 5/20/91

(def-substitution-macro minimum-expiration (e1 e2)
  (cond ((eq e1 'never) e2)
        ((eq e2 'never) e1)
        ((or (null e1) (null e2)) nil)
        (t (minf e1 e2))))






;;;; Current Activity




;;; The system variable `current-computation-activity' is used to store a fixnum
;;; which represents an index into the `registered-activities-array'.  The
;;; referenced element of the array is a Lisp string which names a finely
;;; grained context of what action or statement is currently being executed.
;;; Note that the Lisp string is always encoded in the US-ASCII character set, a
;;; 7-bit character set that's a proper subset of Latin 1.  The value 0
;;; represents some kind of "default" activity for the current-computation-
;;; frame, such as evaluating a rule antecedent, formula for value, etc.  Note
;;; that if the order of the array is changed, then the recompile flag will have
;;; to be bumped up, since indices to this array are held within compiled
;;; byte-code-bodies.

(def-system-variable current-computation-activity comp-utils 0)

(defparameter registered-activities-array
              #("default"

                ;; Procedure statements
                "assign local variable statement"
                "return statement"
                "if-then statement"
                "if-then-else statement"
                "case statement"
                "repeat statement"
                "exit if statement"
                "for statement"
                "for in parallel statement"
                "for in parallel until one completes statement"
                "call statement"
                "system call statement"
                "allow other processing statement"
                "collect data statement"
                "do in parallel statement"
                "do in parallel until one completes statement"
                "wait for interval statement"
                "wait until statement"
                "wait until event statement"
                "on error statement"
                "signal error statement"

                ;; Actions
                "start rpc action"
                "start action"
                "conclude action"
                "conclude has no current value action"
                "conclude has no value action"
                "move action"
                "rotate action"
                "focus action"
                "invoke action"
                "change color action"
                "show action"
                "hide action"
                "activate action"
                "deactivate action"
                "halt action"
                "set action"
                "inform action"
                "conclude relation action"
                "conclude not related action"
                "create action"
                "delete action"
                "transfer action"
                "change action"
                "change text action"
                "change array or list element action"
                "insert action"
                "remove action"
                "nupec synchronize action"
                "create explanation action"
                "update action"
                "create connection action"
                "abort action"
                "shut down G2 action"
                "reset kb action"
                "pause kb action"
                "create by cloning action"
                "make permanent action"
                "make transient action"
                "make subworkspace action"
                "print action"
                "start kb action"
                "resume kb action"

                ;; Rule states
                "begin rule actions"

                ;; Method dispatching
                "call next method statement"
                "call action"
                "call rpc action"
		
                ))




;;; The macro `activity-index' takes a constant string and expands into the
;;; fixnum under which that string is registered.  If none can be found, a
;;; compile time warning is issued and 0 is returned.

(defmacro activity-index (string)
  (loop for index from 0 below (length registered-activities-array)
        do
    (when (string= string (svref registered-activities-array index))
      (return index))
        finally
          (warn "ACTIVITY-INDEX:  The string ~s was not registered." string)
          (return 0)))




;;; The function `activity-given-index' takes a frame, component particulars,
;;; and an activity index.  If the index is 0, the frame and component
;;; particulars are used to determine a default activity.  If the index is
;;; positive, then it is used as in index into the registered-activity-array to
;;; find the referenced activity.  The text string returned must be reclaimed by
;;; the caller of this function.  The function `write-activity-given-index'
;;; takes the same arguments, but twrites its output.

;;; Note that generic-simulation-formulas, simulation-subtables,
;;; generic-formulas, and all kinds of expression cells fall into the default
;;; case at the bottom of this function.

(defun-void write-activity-given-index (frame? component-particulars? activity-index)
  (cond
    ((and (pluspf activity-index)
          (<f activity-index (length-of-simple-vector registered-activities-array)))
     (twrite-string (svref registered-activities-array activity-index)))
    #+development
    ((/=f activity-index 0)
     (cerror
       "Continue"
       "Index ~a not found in registered-activities-array."
       activity-index))
    ((null frame?)
     (twrite-string (svref registered-activities-array 0)))
    (t
     (frame-class-case frame?
       ((rule)
        (twrite-string #w"rule antecedent"))
       ((procedure)
        (twrite-string #w"entering procedure"))
       (t
         (twrite-string #w"executing ")
         (if component-particulars?
             (denote-component-of-block nil component-particulars? frame?)
             (denote-component-of-block t component-particulars? frame?)))))))

(defun-simple activity-given-index (frame? component-particulars? activity-index)
  (twith-output-to-text-string
    (write-activity-given-index frame? component-particulars? activity-index)))


(defun-void add-activity-translation-to-code-stream (byte-code-stream counter-address activity-number)
  (cond ((byte-code-stream-activity-information? byte-code-stream)
         (nconc (byte-code-stream-activity-information? byte-code-stream)
                (slot-value-list (slot-value-list counter-address activity-number))))
        (t
         (setf (byte-code-stream-activity-information? byte-code-stream)
                (slot-value-list (slot-value-list counter-address activity-number))))))

(defun find-activity (byte-code-body program-counter)
  (loop for (index activity) in (byte-code-body-activity-description byte-code-body)
        with current-activity? = nil
        with last-activity?
        do
    (when (> index program-counter)
      (setq current-activity? last-activity?))
    (setq last-activity? activity)
    finally
          (progn
            (unless current-activity?
              (setq current-activity? last-activity?))
            (return (svref registered-activities-array current-activity?)))))

(defun print-activity-list (activity-list)

  (loop for (index activity) in activity-list
        do
    (format t "~% pc: ~a;~a"
            index
            (svref registered-activities-array activity))))

(defun print-activities-in-byte-code-body (byte-code-body)
  (print-activity-list (byte-code-body-activity-description byte-code-body)))

;;; Included program counter in error report. ajs (4/30/96)

(defun-void write-activity-given-pc-and-byte-code-body (byte-code-body pc)
  (twrite-string (find-activity byte-code-body pc))
  (tformat " at program counter ~a " pc))





;;;; Computation Instance Structures




;;; The structure `computation-instance' is an included subpart of the
;;; structures bound into the variable current-computation-instance.  Currently,
;;; code-body-invocation, rule-instance, and formula-invocation include this
;;; structure.  Note that there are times when frames are bound into
;;; current-computation-instance, so it cannot always be assumed that current
;;; computation instance holds structures of this type, but if it is a
;;; structure then it is safe to assume this is part of it.

;;; The main motivation for this inclusion is so that modify-major-stack-eval-
;;; locals need not type dispatch before fetching these slots.

(def-structure (computation-instance)
  #+trace-invocations
  (invocation-mark nil)
  invocation-byte-code-body
  invocation-local-var-vector
  invocation-stack-program-counter
  invocation-constant-vector
  invocation-return-value-position
  invocation-return-value-count
  (invocation-schedule-task nil :reclaimer cancel-task))

;;; A slot-accessor function for forward-referencing

(defun-simple invocation-stack-program-counter-function (ci)
  (invocation-stack-program-counter ci))



;;;; Running Frames




;;; The predicate `runnable-p' takes a block and returns whether or not
;;; computations within it should be able to be executed.  This is determined by
;;; the combination of the active-p flag, the runs-while-inactive-p flag, and
;;; the frame status.

(def-substitution-macro runnable-p (block)
  (and (frame-ok-p block)
       (or (active-p block)
           (and (not inside-breakpoint-p)
                (runs-while-inactive-p block)
                (not (manually-disabled-p block))))))

(defun-simple runnable-p-function (block)
  (runnable-p block))


;;; `reason-not-runnable' takes a block which is known to be not runnable, and
;;; returns something intended to be passed as an argument to a format string,
;;; and not reclaimed.

(defun reason-not-runnable (block)
  (or (frame-status block)
      (cond ((manually-disabled-p block)
             "disabled")
            ((not (active-p block))
             "not active")
            (inside-breakpoint-p
             "inside a breakpoint")
            (t "in an unknown state"))))

;;; The generic-method `note-runs-while-inactive-change' is used to notify
;;; frames of a change in their running-while-inactive status.  This method will
;;; be called after the new value has been installed into the frame.  Each
;;; implementation of this method is responsible for calling
;;; funcall-superior-method.

(def-generic-method note-runs-while-inactive-change (kb-frame)
  )




;;; The generic-method `note-may-refer-to-inactive-items-change' propagates
;;; notifications of a change to the may-refer-to-inactive-items flag.  This
;;; frame flag controls whether or not an item is allowed to reference inactive
;;; items within expressions.  This method performs any class-specific
;;; propagations necessary when the value of this flag changes.  The method
;;; takes a kb-frame after the modification has been made.  Implementations of
;;; this method must call superior methods.

(def-generic-method note-may-refer-to-inactive-items-change (kb-frame)
  )

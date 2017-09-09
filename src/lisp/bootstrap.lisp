;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module BOOTSTRAP

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David, Jim Allard, and Ong, Peng Tsin



;; NOTE: I removed support for DEMO compiles from this module. (MHD 10/12/90)

;; NOTES ON *FEATURES*'s MAIN FLAGS:

;; The following features have to be set correctly in *features*:
;;   :development  (development compiles only; macros present)
;;   :distribution (code that might be shipped)
;;   :no-macros
;;   :non-development-macros  (non-development macro compiles)




;; NOTES:

;; Note: Do not use the LOOP Iteration Macro in this or any other modules
;; preceeding LOOP. (Some Common Lisp's have included a version of this macro,
;; but it should not be used.)

;; Note: A lot of the code here need not be saved as part of the distribution
;; binaries. In particular, code that performs file transfers and lisp source
;; compilation should be abstracted to another module which is not loaded for
;; distribution world saves! -pto 17nov88

;; OR ELSE: just use defun-for-macro, defvar-for-macro, etc. with their defs.
;; (MHD 12/2/88)

;; Note: BOOTSTRAP is intended as an abstract module usable for any "system"
;; (as further defined below). Numerous exceptions have crept as into the
;; software, but the plan is to root them out and to avoid introducing them at
;; every reasonable opportunity!

;; I'm starting to split up bootstrap into Gensym site specific code and code
;; required for distribution.  We start with the site specific code first.
;; -pto 19dec88

;; BOOTSTRAP probably has to be split up into three sections:  the first is
;; Gensym site specific, the second is the code required for distribution, and
;; the third, more Gensym site specific code that is dependent on the second
;; section.  -pto 20dec88







;; TO DO FOR FILE PROPERTIES:  (started 22dec88.  -pto)
;;
;; 1. If :non-lisp-compile is non-nil, deal with it on Unix and Vax.
;;
;; 2. The version numbers of compiled system-lisp-source-files (lisp-binary)
;; should be recorded in the updates file after they have been compiled.  This
;; version number should be used in conjunction with the file write date do
;; decide if the source should be compiled.  See 11.
;;
;; 3. Handle the key :local-file-p.  This means that that particular file is
;; not kept in the master directory, but is created locally by either a lisp or
;; non-lisp compile of a file that is found in the master directory.  Not much
;; here.
;;
;; 4. We should abstract tests for whether to pull-in-file, compile, and/or
;; load a file.  Use the function necessary-to-update-local-file-p as a
;; starting point.
;;
;; 5. Take snapshot of master directory's file version numbers before deciding
;; which files to ftp.
;;
;; 6. Split BOOTSTRAP into 3 files.  Use load-bootstrapping-file.  (Maybe this
;; isn't necessary.  -pto 16jan89)
;;
;; 7. Right now there are dependencies on Lucid-2-for-os4 and Lucid-3 which are
;; used to tell if we are compiling object files on our Sun3 4.0 or our Sun3 3.2
;; machines.  This use of these switches is inappropriate, and should be changed
;; such that there is a switch based on the machines operating system number,
;; rather than on the versions of Lisp that we happen to run on these machines.
;; -jra 3/27/89


;;;; Set appropriate *features* attributes




;;; For Lisp machines, LOAD is distributed as a source file, so we should
;;; ensure that the apropriate features are stuffed into or taken out of
;;; *features*.

#-(and chestnut-3 chestnut-trans)
(progn
  #+no-macros
  (pushnew :no-macros *features*)
  #-no-macros
  (setq *features* (delete :no-macros *features*))

  #+distribution
  (pushnew :distribution *features*)
  #-distribution
  (setq *features* (delete :distribution *features*))

  #+development
  (when (not (member :distribution *features*))
    (pushnew :development *features*))
  #-development
  (setq *features* (delete :development *features*)))






;;; For  VMS machines, at the present, we update the local
;;; sources using the pull-in-all-system-files function.  Here, we set the
;;; *features* attribute :remote-updates so that we can use one switch to
;;; decide if the code to perform the updates is compiled.  The :remote-update
;;; attribute is not meant to be used outside BOOTSTRAP.

#+(and (and (not no-macros) vms) (not chestnut-trans))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :remote-updates *features*)
)

#+(and (not (and (not no-macros) vms)) (not chestnut-trans))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (setq *features* (delete :remote-updates *features*))
)









;;;; First Section Of Site Specific Code

;; Can't do defmacro in the first section of site specific code because it's
;; shadow has not yet been defined.  Defmacro is defined in the distribution
;; part of BOOTSTRAP.  -pto 19dec88

;; Can't use defun in the first section either.  Defun might be shadowed.  -pto 02sep90

;; Can't use ab::funcall in BOOTSTRAP.  Funcall might be shadowed.  -pto 02sep90

;; Can't use ab::symbol-value in BOOTSTRAP.  Funcall might be shadowed.  -pto 02sep90








;;; The variable `allow-development-compile-p' is set to nil when the version
;;; is spunoff for distribution.

(defparameter allow-development-compile-p t)





(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar current-system-being-loaded nil)
)

;;; Shadowed Format

;; jh, 4/6/95.  We shadow format as part of the GSI size reduction project.  In
;; products other than GSI, format behaves as usual, except that it is now a
;; macro.

;; If you want to refer to the Lisp format function, use the macro
;; (lisp-format).  (Be careful that you are only calling format in development
;; or as a one-shot in distribution, since the Lisp format function is known to
;; cons.)

;; MHD, 5/8/96.  We now introduce variable
;; override-eliminate-for-gsi-no-utf-g-p, macro gsi-no-utf-g-eliminable-p, and
;; declaration eliminate-utf-g-for-gsi.  These will be turned on by default in
;; GSI.  Previously, much of this code had used the more simple
;; gsi-eliminable-p.  See modules CHARACTERS, CHARACTERS2, and UNICODE for
;; details of UTF-G and Unicode mapping.  These are an alternative to
;; gsi-eliminable-p/eliminate-for-gsi for code in GSI modules for code involved
;; in UTF-G <-> Unicode mapping.
;;
;; Read the declaration as "eliminable in GSI with no UTF-G (mapping) support",
;; and keep in mind that, for now and indefinitely into the future, UTF-G
;; mapping support is really needed, so this should never be true in GSI or in
;; any other product/system known about at this time.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar override-eliminate-for-gsi-p nil)
(defvar override-eliminate-for-gsi-no-utf-g-p t)

#-no-macros
(ab-lisp::defun gsi-eliminable-p ()
  (and (eq current-system-being-loaded 'gsi)
       (not override-eliminate-for-gsi-p)))

#-no-macros
(ab-lisp::defun gsi-no-utf-g-eliminable-p ()
  (and (eq current-system-being-loaded 'gsi)
       (not override-eliminate-for-gsi-no-utf-g-p)))
)

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(ab-lisp::defmacro format (stream control-string &rest args)
  `(ab-lisp::format ,stream ,control-string ,@args))
)

#-no-macros
(ab-lisp::defmacro lisp-format ()
  `#'ab-lisp::format)

#-no-macros
(ab-lisp::defmacro true-lisp-format (&rest args)
  #-ansi-cl
  `(lisp:format ,@args)
  #+ansi-cl
  `(common-lisp:format ,@args))


;;;; GC Message Printer for Lucid

#-no-macros
(ab-lisp::defmacro print-room-if-available ()
  (cond
    ((and (eq current-system-being-loaded 'gsi)
	  (member :chestnut-3 *features*)
	  (member :chestnut-trans *features*))
     nil)
    (t `(room t))))

#+(and lucid (not chestnut-trans))
(ab-lisp::defun gensym-gc-message (when-done)
  (case when-done
    (:before (format *terminal-io* "~%Before GC "))
    (:after (format *terminal-io* "~%After GC "))
    (:dynamic-expansion (format *terminal-io* "~%Expanding dynamic memory "))
    (:reserved-expansion (format *terminal-io* "~%Expanding reserved memory ")))
  (format *terminal-io* " ...~%")
  (when (not (eq when-done :before))
    (ab-lisp::let* ((*standard-output* *terminal-io*))
      (print-room-if-available))))

;; Note that printing to *terminal-io* as opposed to *standard-output* is
;; important, since this may be called at ANY time and since the latter is
;; not guaranteed to be anything like a console  -- e.g. it could be a KB
;; being written. (MHD)

#-no-macros
(ab-lisp::defmacro body-of-silent-gc (when-done)
  (cond
    ((and (eq current-system-being-loaded 'gsi)
	  (member :chestnut-3 *features*)
	  (member :chestnut-trans *features*))
     nil)
    (t `(progn (write-char #\. *terminal-io*)
	       (when (eql ,when-done :after)
		 (terpri *terminal-io*))
	       (force-output *terminal-io*)))))

#+lucid
(eval-when (compile eval load)
(ab-lisp::defun silent-gc (when-done)
  (body-of-silent-gc when-done))
)


#+(and lucid (not translator) (not development))
(setq sys::*gc-silence* #'silent-gc)

;;;; Distribution Code



;;; The following defintions serve two purposes.  The first is a redefinition
;;; of defmacro such that macro definitions are not included in binaries which
;;; are compiled when the variable :no-macros is in *features*.
;;; Removal of these macros from our binaries reduces our delivery image by
;;; approximately a third.

;;; The second purpose of this code is to gather statistics on the usage of
;;; individual macros.  When bootstrap and the rest of the system is recompiled
;;; in an environment which contains the feature macro-statistics, then
;;; statistics will be gathered on the number of times each macro is used.  To
;;; use these metering tools, push the keyword :macro-statistics onto the
;;; *features* list, touch bootstrap so that it will recompile, load the load
;;; module, call initialize-macro-statistics, then do a full recompile of G2.
;;; After G2 is compiled, call report-macro-statistics in the same environment
;;; as the compile happened within.









;;;; Redefine Shadowed Functions and Special Forms


;;; The special form `ab::if' is used to reimplement the Common Lisp if.  The
;;; rationale is that the implementation on some platforms (e.g.  TIs) takes an
;;; arbitrary number of forms for the else clause.  This breaks conforming
;;; Common Lisp compilers.

;; jh, 1/15/93.  This and subsequent eval-when wrappers of defmacro forms should
;; be superfluous -- consider removing if and when BOOTSTRAP is ever cleaned up.
;; I left them in for now because there might be a undocumented reason for them
;; in the Lisps we currently use.

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(ab-lisp::defmacro if (test then-clause &rest else-clauses)
  (cond
    ((cdr else-clauses)
     (cerror "Wrap progn around the \"else\" args and proceed"
	     "Common Lisp IF takes at most three arguments, extra args: ~a"
	     (cdr else-clauses))
     `(ab-lisp::if ,test
		   ,then-clause
		   (progn ,@else-clauses)))
    (t
       `(ab-lisp::if ,test
		     ,then-clause
		     ,(car else-clauses)))))
)



;;; The function `ab::gensym' is used reimplement gensym for translated files.
;;; This is done to make sure that translated files are not trivially different
;;; from previous translations of the same file, due to gensym indices being
;;; different.  The net effect of this change is to remove all calls to the
;;; ab-lisp::gensym function during translations.

;;; This version of gensym will call ab-lisp::gensym for when not translating files.
;;; When we are translating it will return a unique symbol (made by
;;; make-symbol), but which has only the prefix string as its print name.  This
;;; still provides unique symbols from Gensym, but it does not cause their
;;; translations to produce different C identifiers on different passes through
;;; the translator.  Note that in CLtL II, a string argument to gensym is not
;;; "sticky".  This implementation conforms to CLtL II.

;;; We'd like code emitted by the compiler to C to be the same in development
;;; and delivery, so when macroexpanding expansions, we should use
;;; the delivery-style gensym function.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defvar macroexpanding-for-instruction-expander nil))

(eval-when (:compile-toplevel :load-toplevel :execute)
  (ab-lisp::defun gensym (&optional (x nil x-supplied-p))
    (cond ((member :chestnut-3 *features* :test #'eq) ;Chestnut3.1
	   (if (stringp x)
	       (make-symbol x)
	       (make-symbol "GENSYMED-SYMBOL")))
	  #+development
	  (macroexpanding-for-instruction-expander
	   (if (stringp x)
	       (make-symbol x)
	       (make-symbol "GENSYMED-SYMBOL")))
	  (t
	   (if x-supplied-p
	       (ab-lisp::gensym x)
	       (ab-lisp::gensym))))))

;; rdf & jh, 6/8/93.  Harlequin objects to giving gensym an argument of nil.
;; According to CLtL/2e, it is right to so object.

;;; This hack is is needed to a get all of the ab-lisp::gensym's to use our gensym which
;;; prevent trivial differences from appearing in translated C files. AC 8-12-91.

#+(and (or chestnut chestnut-3) (not translating))
(progn
  #+clozure
  (setq ccl:*warn-if-redefine-kernel* nil)
  (setf (symbol-function 'ab-lisp::gensym) (symbol-function 'ab::gensym))
  (setf (symbol-function #-ANSI-CL 'lisp::gensym #+ANSI-CL 'cl::gensym)
        (symbol-function 'ab::gensym)))

;; The line above is very dubious.  It is a violation of Common Lisp semantics to
;; modify cells of lisp package symbols.  Second, if we really want to replace
;; lisp:gensym with our function at compile time, then we do not have to do it in a
;; way which replaces the function at run-time.  Further, we probably don't need this
;; line at all, since the Chestnut translator uses a make-symbol style facility, not
;; gensym.  Consider removing!  -jra&jh 9/22/92

;; jh, 1/29/93.  I am not convinced that ab-lisp::gensym is not called by the
;; translator, since gensymed_symbols occurs throughout the translated C files.
;; For now, we will simply ensure that this only happens at compile time.




;;; The macro ab::or is used to work around problems in C compilers which are
;;; exposed by the Chestnut translations of OR in certain circumstances.  The
;;; translation of the following Lisp code cannot be compiled in the Interactive
;;; System V compiler on Compaqs.

;;; (defun kill-or-translation (x)
;;;   (or (null x)
;;;       (and (simple-vector-p x) (> (the fixnum (length x)) (the fixnum 0))
;;;            (eq (aref x 0) global-var))))

;;; The workaround is to explicitly execute the sequencing of the OR within a
;;; LET statement that we generate.

;;; Note that we no longer support the Interactive compile, and so can remove
;;; this shadowing of OR.  For the time being, I'll do this by having ab::or
;;; expand into ab-lisp::or, but we should stop shadowing the symbol and remove
;;; all of this code at our next recompile.  -jra 10/1/93

;;; The experiment of unshadowing OR failed.  The Chestnut translator crashed
;;; when compiling the use of OR in create-x11-color-plist-from-color-hierarchy.
;;; Chestnut has been informed.  -jra 10/6/93

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(ab-lisp::defmacro or (&rest arguments)
  `(ab-lisp::or ,@arguments)))

;;; The macro `special-variable-p' is used within our macros which try to deal
;;; with bugs in Chestnut's implementations of special variable binding.  It
;;; takes symbols and returns whether they have been globally declared special.

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(ab-lisp::defmacro special-variable-p (symbol)
  #-(or lucid allegro lispworks)
  (declare (ignore symbol))
  #-(or lucid allegro lispworks)
  nil
  #+lucid
  `(lucid::proclaimed-special-p ,symbol)
  #+allegro
  (if (fboundp 'excl::variable-special-p)
      `(excl::variable-special-p ,symbol nil)
      `(clos::variable-special-p ,symbol nil))
  #+lispworks
  `(walker:variable-special-p ,symbol nil)
  ;; #+sbcl
  ;; `(sb-walker:var-globally-special-p ,symbol) ;; TODO
  ;; Oh because this ISN'T a hack already? -dkuznick, 8/6/99
  ))

;;; The macros `ab::let' and `ab::let*' are used within Chestnut compiles to fix
;;; problems Chestnut has with binding special variables.  Basically, there are
;;; problems in the sequence of bindings, and in having init forms for bindings
;;; further bind special variables.  In fact, any sort of complex rebinding or
;;; even use of special variables within the init forms of LET and LET* confuses
;;; Chestnut to no end.

;;; So, we have shadowed LET, LET*, and all other binding forms which we use to
;;; bind special variables in run-time G2 code, so that the special bindings
;;; actaully happen within a very simply structured LET, and the actual values
;;; computed within seperate LET forms or setqs to the global variable.

;;; The problems occur when at least one special variable is being bound within
;;; the LET and any of the init forms is something other than a constantp form
;;; or a symbol.  When these qualifications are met, we will rewrite the let.
;;; The function `let-bindings-problematic-p' takes the list of bindings for a
;;; let form and tests if they could exhibit problems.

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(ab-lisp::defun let-bindings-problematic-p (bindings)
  (and (member :chestnut-trans *features*)
       (ab-lisp::let ((special-bindings? nil)
		      (non-simple-init-forms? nil))
	 (do* ((binding-cons bindings (cdr binding-cons))
	       (binding (car binding-cons) (car binding-cons)))
	      ((ab-lisp::or (null binding-cons)
			    (and special-bindings? non-simple-init-forms?))
	       (and special-bindings? non-simple-init-forms?))
	   (cond ((symbolp binding)
		  (when (not special-bindings?)
		    (setq special-bindings? (special-variable-p binding))))
		 (t
		  (when (not special-bindings?)
		    (setq special-bindings? (special-variable-p (car binding))))
		  (when (not non-simple-init-forms?)
		    (ab-lisp::let ((init-form (second binding)))
		      (setq non-simple-init-forms?
			    (and (not (symbolp init-form))
				 (not (constantp init-form))))))))))))
)

;;; The macro `ab::let' is rewritten by promoting the evaluation of all
;;; non-constant init forms to a let form, binding all values into gensymed
;;; variables.  The original variables are then bound in a second, nested let
;;; form to the already computed values, or to their constant initial values.

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(ab-lisp::defmacro let (bindings &body declarations-and-forms)
  (if (let-bindings-problematic-p bindings)
      (ab-lisp::let ((generated-bindings nil)
		     (nested-bindings nil))
	(dolist (binding bindings)
	  (if (symbolp binding)
	      (push binding nested-bindings)
	      (ab-lisp::let ((init-form (second binding)))
		(if (constantp init-form)
		    (push binding nested-bindings)
		    (ab-lisp::let ((cached-value (gensym)))
		      (push (list cached-value init-form) generated-bindings)
		      (push (list (car binding) cached-value)
			    nested-bindings))))))
	`(ab-lisp::let ,(nreverse generated-bindings)
	   (ab-lisp::let ,(nreverse nested-bindings)
	     ,@declarations-and-forms)))
      `(ab-lisp::let ,bindings ,@declarations-and-forms)))
)

;;; The macro `ab::let*' is rewritten by binding all special variables to their
;;; previous values in a let form, then emitting a nested let* form which binds
;;; the local (i.e.  lexical) variables to their initial values.  The twist is
;;; that the initialization forms for the local variables will be progn and
;;; prog1 forms which setq the global variables to their initialization form
;;; values in the proper order according to the original let* form.  Note that
;;; in the case where the bindings are all globals, then the initialization
;;; forms will be emitted as setqs within the body of the outer generated let,
;;; and no inner let form will be generated.

;; Note:  This implementation is being done with the hope that we currently have
;; no declarations on bindings of special variables.  If we do, then this
;; implementation will have to be changed to split the declarations into those
;; affecting the global bindings, and those affecting the lexical variables and
;; body.  -jra & jh 10/7/91

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(ab-lisp::defmacro let* (bindings &body declarations-and-forms)
  (if (let-bindings-problematic-p bindings)
      (ab-lisp::let ((deferred-global-inits nil)
		     (global-bindings nil)
		     (lexical-bindings nil))
	(dolist (binding bindings)
	  (ab-lisp::let ((symbol (if (symbolp binding) binding (car binding)))
			 (init-form (if (symbolp binding) nil (second binding))))
	    (cond ((special-variable-p symbol)
		   (push (list symbol symbol) global-bindings)
		   (push `(setq ,symbol ,init-form) deferred-global-inits))
		  (deferred-global-inits
		   (push `(,symbol (progn
				     ,@(nreverse deferred-global-inits)
				     ,init-form))
			 lexical-bindings)
		   (setq deferred-global-inits nil))
		  (t
		   (push binding lexical-bindings)))))
	(when deferred-global-inits
	  (if lexical-bindings
	      ;; Oh help me.
	      (ab-lisp::let ((dummy-var (gensym)))
		(push `(,dummy-var (progn
				     ,@(nreverse deferred-global-inits)
				     nil))
		      lexical-bindings)
		(push `(declare (ignore ,dummy-var))
		      declarations-and-forms))
	      ;; Assumes no declarations on globals only bindings.
	      (setq declarations-and-forms
		    (append (nreverse deferred-global-inits)
			    declarations-and-forms))))
	(if lexical-bindings
	    `(ab-lisp::let ,(nreverse global-bindings)
	       (ab-lisp::let* ,(nreverse lexical-bindings)
		 ,@declarations-and-forms))
	    `(ab-lisp::let ,(nreverse global-bindings)
	       ,@declarations-and-forms)))
      `(ab-lisp::let* ,bindings ,@declarations-and-forms)))
)




;;; The macro `ab::defmacro' ...

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)

#+(and lispworks (not chestnut-3))
(progn
    (cl:defun is-defun-alias? (name)
      (let ((position (cl:search "DEFUN" (cl:symbol-name name))))
	(and position (= position 0))))

    (cl:defun is-defvar-alias? (name)
      (let ((position (cl:search "DEFVAR-" (cl:symbol-name name))))
	(and position (= position 0))))

    (cl:defun is-definition? (name)
      (let ((position (cl:search "DEF-" (cl:symbol-name name))))
	(and position (= position 0)
	     (not (is-method? name)))))

    (cl:defun is-method? (name)
      (or (string= "DEF-CLASS-METHOD" (cl:symbol-name name))
	  (string= "DEF-STRUCTURE-METHOD" (cl:symbol-name name))))

    (cl:defmacro define-dspec-alias (name alias)
      `(progn
	 (dspec:define-form-parser (,name (:alias ,alias)))
	 (dspec:define-dspec-alias ,name (name) `(,',alias ,name))))

    (define-dspec-alias defmacro cl:defmacro)
    (define-dspec-alias defparameter cl:defparameter))

(ab-lisp::defmacro defmacro (name pattern &body body)
  (if (not (member :no-macros *features*))
      (do* ((declarations-and-documentation-strings nil)
	    (rest-of-body body (cdr rest-of-body)))
	   ((ab-lisp::or (not (consp rest-of-body))
			 (not (ab-lisp::or (and (consp (car rest-of-body))
						(eq (caar rest-of-body) 'declare))
					   (stringp (car rest-of-body)))))
	    `(eval-when (:compile-toplevel :load-toplevel :execute)
	       #+(and lispworks (not chestnut-3))
	       ,@(cond ((is-defun-alias? name)
			`((define-dspec-alias ,name cl:defun)))
		       ((is-defvar-alias? name)
			`((define-dspec-alias ,name cl:defvar)))
		       ((is-definition? name)
			`((dspec:define-form-parser
			      (,name (:parser dspec:single-form-with-options-form-parser)))
			  (dspec:define-dspec-class ,name nil
			    ,(format nil "Definition of ~A" name)))))
	       (ab-lisp::defmacro ,name ,pattern
		 ,@(reverse declarations-and-documentation-strings)
		 (record-macro-use ',name)
		 ,@(ab-lisp::or rest-of-body '(nil)))))
	(push (car rest-of-body) declarations-and-documentation-strings))))

)

;; We now have defmacro, but ab::defmacro calls the record-macro-use function
;; which is still not defined.

;;; Define the variable macro-statistics and the function record-macro-use here

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)

(defvar macro-statistics nil)

(ab-lisp::defun record-macro-use (macro-name)
  (if macro-statistics
      (incf (gethash macro-name macro-statistics 0))))
)



;;; The macro `ab::define-modify-macro' expands into a call to the lisp version
;;; of this when we are not making distribution software.  When we are making a
;;; distribution, this turns into a no op.  That eliminates the macro dead code
;;; from our distributions.  This requires that the lisp symbol
;;; define-modify-macro is shadowed by our code in the file LOAD.

;; jh, 2/5/93.  Switching in define-modify-macro for the translation pass of the
;; new Chestnut translator.  It needs to see define-modify-macro forms in the
;; source file at translation time, lest it use the host Lisp's macroexpansdion
;; of a modify macro.  Since the trans:*include-macro-expanders* switch is set
;; to nil in TRANSLATE, this should not result in any dead code in the
;; translated images.  A precedent for this change is that we never switched out
;; defsetf.  Note that a similar problem does not occur with defmacro; i.e., the
;; old method of expanding it to nil during the translation pass still works,
;; presumably because the macro pass leaves the right macroexpanders as the
;; macro-functions of the right symbols.  Evidently the macroexpanders created
;; by define-modify-macro are put in a different place, invisible to the new
;; translator.

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)

(defmacro define-modify-macro
	  (name lambda-list function &rest doc-string-and-declarations)
  (unless (and (member :no-macros *features*)
	       (not (member :chestnut-3 *features*)))
    `(ab-lisp::define-modify-macro
       ,name ,lambda-list ,function ,@doc-string-and-declarations)))

)




;;; The ab::multiple-value-bind macro is used to implement a patch to Chestnut
;;; for binding special variables.

(eval-when (:compile-toplevel :load-toplevel :execute)
#-no-macros
(ab-lisp::defun rename-specials-in-variable-list (original-variable-list)
  (let ((special-rebindings nil)
	(result-variable-list nil))
    (do* ((var-list original-variable-list (cdr var-list))
	  (var (car var-list) (car var-list)))
	 ((null var-list))
      (cond ((special-variable-p var)
	     (let ((special-variable-substitute
		     (make-symbol (format nil "~a-LEXICAL" var))))
	       (push special-variable-substitute result-variable-list)
	       (push (list var special-variable-substitute)
		     special-rebindings)))
	    (t
	     (push var result-variable-list))))
    (values (nreverse result-variable-list)
	    special-rebindings)))
)  ;end of eval-when

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(ab-lisp::defun split-multiple-value-bind-body (body)
  (do* ((collected-declarations nil)
	(rest-of-body body (cdr rest-of-body))
	(this-form (car body) (car rest-of-body)))
       ((ab-lisp::or (not (consp rest-of-body))
		     (not (and (consp this-form)
			       (eq (car this-form) 'declare))))
	(values (nreverse collected-declarations)
		rest-of-body))
    (push this-form collected-declarations)))
) ;end of eval-when

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro multiple-value-bind (variable-list values-form &body body)
  (ab-lisp::multiple-value-bind (new-variable-list
				  let-bindings-of-specials?)
      (rename-specials-in-variable-list variable-list)
    (if (and let-bindings-of-specials?
	     (member :chestnut-trans *features*))
	(ab-lisp::multiple-value-bind (declarations body-after-declarations)
	    (split-multiple-value-bind-body body)
	  `(ab-lisp::multiple-value-bind ,new-variable-list
	       ,values-form
	     ,@declarations
	     (let ,let-bindings-of-specials?
	       ,@body-after-declarations)))
	`(ab-lisp::multiple-value-bind ,variable-list
	     ,values-form
	   ,@body))))
)

;; jh, 10/2/91.  Fixed ab::multiple-value-bind to handle declarations.  Note that
;; if the multiple-value-bind's variable-list holds a special variable which is
;; then declared ignorable, our macroexpansion will result in a "declared but not
;; bound" complaint from the compiler.  This is almost correct behavior, since
;; CLtL/2e mentions (p 230) that "it is desirable for a compiler to issue a
;; warning if [an ignorable] variable ...  is also declared special".  The wording
;; of the warning may be a bit off, however, since we would like an "ignored but
;; special" message instead.



;;;; Shadowing Defun

;;; def-defun-modification
;;;   <modification-name> <defun-components> <modification-args> &body <body>

;;; The macro `def-defun-modification' provides a clean, declarative way to
;;; enhance defun.  It specifies options which the macro
;;; defun-with-modifications (q.v.) uses to "mix and match" the various
;;; enhancements to defun in use at Gensym.

;;; To understand this macro, it is necessary to understand how we "intercept"
;;; the host Lisp definition of the defun special form.  The module LOAD
;;; establishes the AB-LISP package, which uses the LISP package.  In turn, the
;;; AB package, the home package for all our source modules, uses the AB-LISP
;;; package.  Thus, by exporting or declining to export a symbol from AB-LISP,
;;; we can control which Lisp symbols are visible in AB source files.  The
;;; symbol ab-lisp::defun (whose home package is LISP) is one of the symbols we
;;; decline to export.  Instead, we define a macro ab::defun, whose expansion
;;; contains a call to ab-lisp::defun, which provides the core functionality of
;;; the defun special form in the host Lisp.  In our source files, calls to
;;; defun without a package qualifier actually invoke the macroexpander for
;;; ab::defun.  Historically, in order to add functionality to the Lisp defun,
;;; we have directly modified the macro definition of ab::defun.  This practice
;;; has become increasingly cumbersome as vendor-specific enhancements
;;; accumulate and collide.  Now we add a layer of indirection,
;;; defun-with-modifications, a macro that processes individual, meaningful
;;; moidifications specified by def-defun-modification.  For details on
;;; defun-with-modifications, see its documentation below.

;;; A def-defun-modification form specifies additional or modified subforms to
;;; be executed in the vicinity of the core ab-lisp::defun form.  The skeleton
;;; of the ab::defun macroexpansion looks like this:

;;;     (progn
;;;       ...
;;;       forms before the core defun
;;;       ...
;;;       (<defun-marker> <name> <arglist>
;;;         ... doc and declarations ...
;;;         ... defun body ...)
;;;       ...
;;;       forms after the core defun
;;;       ...
;;;     )
;;;

;;; The <body> of def-defun-modification form affects the subforms in this
;;; skeleton.  Inside <body>, each <defun-component> is bound to a variable
;;; representing one of these subforms.  Variable names permissible in
;;; <defun-components> are the following (note that the angle-brackets are part
;;; of the variable name, to add distinction):

;;;   <progn-before-forms>: a list of forms to be executed before the actual
;;;   ab-lisp::defun form.  This list is executed as an implicit progn at
;;;   load time.
;;;
;;;   <defun-marker>: the symbol naming the special form or macro to be used
;;;   in the "defun" place.  This defaults to ab-lisp::defun.
;;;
;;;   <defun-name>: the name of the core ab-lisp::defun form.  The actual
;;;   definition occurs at load time.
;;;
;;;   <argument-list>: the arguments of the core ab-lisp::defun form.
;;;
;;;   <doc-and-decl-forms>: documentations strings and declaration forms to be
;;;   placed in the body of the core ab-lisp::defun form.
;;;
;;;   <body-after-doc-and-decl>: the body of the actual ab-lisp::defun form.
;;;
;;;   <progn-after-forms>: a list of forms to be executed after the actual
;;;   ab-lisp::defun form.  This list is executed as an implicit progn at
;;;   load time.
;;;
;;;   <original-defun-modifications>: a list of the defun modification symbols
;;;   or lists presented to defun-with-modifications, currently (jh, 3/22/95)
;;;   only used by the :intercept-declaration defun modification.

;;; Thus, to modify a subform, <body> should setq the appropriate
;;; <modification-arg>.  For example, to register an enhancement which prints a
;;; message every time a function is called:

;;;  (def-defun-modification :chatty
;;;      (<defun-name> <body-after-doc-and-decl>)
;;;      ()
;;;    (setq <body-after-doc-and-decl>
;;;          `((format t "~%Entering ~s~%" ',<defun-name>)
;;;            ,@<body-after-doc-and-decl>)))

;;; Note that <defun-name> is unchanged by this modification to defun; it is
;;; simply used to format the message.

;;; The <modification-args> subform of def-defun-modification lists extra
;;; arguments that may be passed to <body> via Gensym's intercepting the Common
;;; Lisp declare special form when it occurs in a defun.  See the documentation
;;; for the :intercept-declaration defun modification below for further details.

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar known-defun-component-variables
	'(
	  <progn-before-forms>
	  <defun-marker>
	  <defun-name>
	  <argument-list> 
	  <doc-and-decl-forms>
	  <body-after-doc-and-decl>
	  <progn-after-forms>
	  <listed-defun-replacement-form?>
	  <original-defun-modifications>
	  ))

(defvar defun-modification-alist nil)
)

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro def-defun-modification
          (modification-name defun-components extra-args? &body body)
  (unless (member :no-macros *features*)
    (unless (ab-lisp::subsetp
	      defun-components
	      known-defun-component-variables)
      (error "DEF-DEFUN-MODIFICATION: unknown defun component variable in ~s"
	     defun-components))
    `(eval-when (:compile-toplevel :load-toplevel :execute)
       (let ((defun-modification-entry?
	       (assoc ',modification-name defun-modification-alist))
	     (defun-modification-function
		 #'(lambda (,@known-defun-component-variables
			    ,@(if extra-args?
				 `(&optional ,@extra-args?)
				 nil))
		     ,@body
		     (values ,@known-defun-component-variables))))
	 (if defun-modification-entry?
	     (setf (cdr defun-modification-entry?)
		   defun-modification-function)
	     (push (cons ',modification-name 
			 defun-modification-function)
		   defun-modification-alist)))
       ',modification-name)))
)

;; jh, 1/25/93.  There appears to be a bug, either in the TI implementation of
;; eval-when, or in my understanding of this construct.  Previously, the
;; macroexpander for def-defun-modification created a named defun in an
;; eval-when (compile load eval) situation to serve as the modification
;; function.  This did not work, although the symbol for this function was
;; successfully pushed onto defun-modification-alist at compile time.  So the
;; macroexpander for def-defun-modification now pushes a closure directly onto
;; defun-modification-alist.  Note that this all happens only in the macro pass,
;; and so the runtime image is not saddled with the problematic chore of
;; maintaining or calling closures.




;;; defun-with-modifications <modification-list> <name> <arglist> &body <body>

;;; The macro `defun-with-modifications' is used in combination with
;;; def-defun-modification to augment the Lisp defun.  The first argument of
;;; defun-with-modifications, <modification-list>, is an unevaluated list of
;;; symbols which have been previously registered by def-defun-modification.
;;; The remaining arguments are as in a normal defun.  The modifications are run
;;; in the order that their names appear in <modification-list>.  For example,
;;; the following forms will make a version of defun which arranges to print the
;;; name of the function and then enter a break loop at runtime.

;;;  (def-defun-modification :trace-before
;;;      (<defun-name> <body-after-doc-and-decl>)
;;;      ()
;;;    (setq <body-after-doc-and-decl>
;;;          `((format t "~%Entering ~s~%" ',<defun-name>)
;;;            ,@<body-after-doc-and-decl>)))

;;;  (def-defun-modification :break (<body-after-doc-and-decl>)
;;;    ()
;;;    (setq <body-after-doc-and-decl>
;;;          `((break) ,@<body-after-doc-and-decl>)))

;;;  (defmacro defun-debuggable (name arglist &body body)
;;;    `(defun-with-modifications (:trace-before :break) ,name ,arglist ,@body))

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(ab-lisp::defun split-defun-body (body)
  (do* ((collected-declaration-and-documentation nil)
	(rest-of-body body (cdr rest-of-body))
	(this-form (car body) (car rest-of-body)))
       ((ab-lisp::or (not (consp rest-of-body))
		     (not (ab-lisp::or (and (consp this-form)
					    (eq (car this-form) 'declare))
				       (stringp this-form))))

	;; jh, 3/4/93.  CLtL/2e, p 85: "If doc-string is not followed by a
	;; declaration, it may be present only if at least one form is also
	;; specified, as it is otherwise taken to be a form."
	(let ((last-decl-or-doc-form
		(first collected-declaration-and-documentation)))
	  (multiple-value-bind (doc-and-decl-forms defun-body)
	      (if (and (null rest-of-body)
		       (stringp last-decl-or-doc-form))
		  (values (nreverse
			    (cdr collected-declaration-and-documentation))
			  (list last-decl-or-doc-form))
		  (values (nreverse collected-declaration-and-documentation)
			  rest-of-body))

	    ;; jh, 3/4/93.  CLtL/2e, p 85: "It is an error if more than one
	    ;; doc-string is present."
	    (when (> (count-if #'stringp doc-and-decl-forms) 1)
	      (warn "SPLIT-DEFUN-BODY: more than one doc string in~%~s~%"
		    body))

	    (values doc-and-decl-forms defun-body))))

    (push this-form collected-declaration-and-documentation)))
) ;end of eval-when

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar intercept-declaration-rewrote-defun-p nil)
)

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(ab-lisp::defun apply-defun-modifications
                (progn-before-forms
		  defun-marker
		  defun-name
		  defun-arglist
		  doc-and-decl-forms
		  body-after-doc-and-decl
		  progn-after-forms
		  listed-defun-replacement-form?
		  modification-list)
  (do* ((modifications modification-list (cdr modifications))
	(modification (car modifications) (car modifications)))
       ((or (null modifications) listed-defun-replacement-form?))
    (let* ((modification-has-args-p (consp modification))
	   (modification-entry?
	     (if modification-has-args-p
		 (assoc (car modification) defun-modification-alist)
		 (assoc modification defun-modification-alist)))
	   (supplied-modification-args?
	     (and modification-has-args-p (cdr modification)))
	   (modification-args-to-apply?
	     (and supplied-modification-args?
		  (list supplied-modification-args?))))
      (unless modification-entry?
	(error "DEFUN-WITH-MODIFICATIONS: unknown modification ~s"
	       modification))
      (multiple-value-setq (progn-before-forms
			     defun-marker
			     defun-name
			     defun-arglist
			     doc-and-decl-forms
			     body-after-doc-and-decl
			     progn-after-forms
			     listed-defun-replacement-form?
			     modification-list)
	(apply (cdr modification-entry?)
	       progn-before-forms
	       defun-marker
	       defun-name
	       defun-arglist
	       doc-and-decl-forms
	       body-after-doc-and-decl
	       progn-after-forms
	       listed-defun-replacement-form?
	       modification-list
	       modification-args-to-apply?))))
  (values progn-before-forms
	  defun-marker
	  defun-name
	  defun-arglist
	  doc-and-decl-forms
	  body-after-doc-and-decl
	  progn-after-forms
	  listed-defun-replacement-form?
	  modification-list))
)

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro defun-with-modifications
	  (modification-list
	    defun-name
	    defun-arglist
	    &body doc-and-decl-and-body)
  (let ((progn-before-forms nil)
	(defun-marker 'ab-lisp::defun)
	(progn-after-forms nil)
	(listed-defun-replacement-form? nil))
    (multiple-value-bind (doc-and-decl-forms body-after-doc-and-decl)
	(split-defun-body doc-and-decl-and-body)
      (if (member :intercept-declaration modification-list)
	  (let ((intercept-declaration-rewrote-defun-p nil))
	    (pushnew :notice-defun-name modification-list)
	    (setq modification-list
		  (remove :intercept-declaration modification-list))
	    (multiple-value-setq (progn-before-forms
				   defun-marker
				   defun-name
				   defun-arglist
				   doc-and-decl-forms
				   body-after-doc-and-decl
				   progn-after-forms
				   listed-defun-replacement-form?)
	      (ab-lisp::funcall
		(cdr (assoc :intercept-declaration defun-modification-alist))
		progn-before-forms
		defun-marker
		defun-name
		defun-arglist
		doc-and-decl-forms
		body-after-doc-and-decl
		progn-after-forms
		listed-defun-replacement-form?
		modification-list))
	    (unless intercept-declaration-rewrote-defun-p
	      (multiple-value-setq (progn-before-forms
				     defun-marker
				     defun-name
				     defun-arglist
				     doc-and-decl-forms
				     body-after-doc-and-decl
				     progn-after-forms
				     listed-defun-replacement-form?
				     modification-list)
		(apply-defun-modifications
		  progn-before-forms
		  defun-marker
		  defun-name
		  defun-arglist
		  doc-and-decl-forms
		  body-after-doc-and-decl
		  progn-after-forms
		  listed-defun-replacement-form?
		  modification-list))))
	  (multiple-value-setq (progn-before-forms
				 defun-marker
				 defun-name
				 defun-arglist
				 doc-and-decl-forms
				 body-after-doc-and-decl
				 progn-after-forms
				 listed-defun-replacement-form?
				 modification-list)
	    (apply-defun-modifications
	      progn-before-forms
	      defun-marker
	      defun-name
	      defun-arglist
	      doc-and-decl-forms
	      body-after-doc-and-decl
	      progn-after-forms
	      listed-defun-replacement-form?
	      modification-list)))
      (if listed-defun-replacement-form?
	  (car listed-defun-replacement-form?)
	  `(progn ,@progn-before-forms
		  (,defun-marker ,defun-name ,defun-arglist
		    ,@doc-and-decl-forms
		    ,@body-after-doc-and-decl)
		  ,@progn-after-forms)))))
)

;;; The :notice-defun-name modification to ab::defun ...

;; jh, 9/29/91.  We need most-recent-defun-name to let us zero in on the remaining
;; defuns which should be defun-allowing-unwinds.  We can't bind it as a special
;; because the macroexpander for defun has long since exited by the time the
;; macroexpander for ab::catch does its complaining.

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter most-recent-defun-name nil)
)

(def-defun-modification :notice-defun-name
    (<defun-name>)
    ()
  (setq most-recent-defun-name <defun-name>))




;;; The :rebind-specials modification to ab::defun ...

;; The function rename-specials-in-arglist will detect special variables in a
;; lambda-list given to a defun, so we can work around faulty implementations
;; which don't rebind special variables in lambda-lists.  The strategy is to
;; concoct a new lambda-list with the special variables replaced by gensyms and
;; then bind the specials to the gensyms inside the defun, using let.  In all
;; implementations we know, let binds specials correctly.
;; Rename-specials-in-arglist takes a single argument, an argument list given to
;; defun and returns two values:

;;  1) a lambda-list, possible revised to include gensyms, and

;;  2) a list of pairs of the form (arglist-var gensym), where gensym is the name
;;  in the lambda list and arlist-var is the original special var.  this list will
;;  for a let-binding inside the defun.

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(ab-lisp::defun rename-specials-in-arglist (original-arglist)
  (let ((special-rebindings nil)
	(result-arglist nil))
    (do* ((arglist original-arglist (cdr arglist))
	  (arg (car arglist) (car arglist)))
	 ((null arglist))
      (cond ((eq arg '&aux)
	     (setq result-arglist (append (reverse arglist) result-arglist))
	     (return nil))
	    ((and (member arg '(&optional &rest &key &allow-other-keys))
		  t)				; chestnut idiom (MHD 1/15/92)
						; The Chestnut compiler browbeats
						; you with "Not-predicate MEMBER
						; with constant test-list;
						; Use (AND (MEMBER ...) T)"
						; unless you do this, so I'm giving
						; in.  Note that in later modules, you
						; can use MEMBERP to do the same.
						; (MHD 1/15/92)
	     (push arg result-arglist))
	    ((and (consp arg) (special-variable-p (car arg)))
	     (let ((special-variable-substitute
		     (make-symbol (format nil "~a-ARG-REBOUND" (car arg)))))
	       (push (cons special-variable-substitute
			   (cdr arg))
		     result-arglist)
	       (push (list (car arg)
			   special-variable-substitute)
		     special-rebindings)))
	    ((consp arg)
	     (push arg result-arglist))
	    ((and (symbolp arg)
		  (special-variable-p arg))
	     (let ((special-variable-substitute
		     (make-symbol (format nil "~a-ARG-REBOUND" arg))))
	       (push special-variable-substitute result-arglist)
	       (push (list arg special-variable-substitute)
		     special-rebindings)))
	    (t
	     (push arg result-arglist))))
    (values (nreverse result-arglist)
	    special-rebindings)))
)




;;; The :rebind-specials defun modification is incompatible with running in
;;; safety 3 in Lucid, since the implementation of this reads global variable
;;; values that may not have been initialized.  -jra, Ben, jh 9/21/93

(def-defun-modification :rebind-specials
    (<argument-list> <body-after-doc-and-decl>)
    ()
  (when (and (member :chestnut *features*)
	     (member :chestnut-trans *features*))
    (multiple-value-bind (new-argument-list let-bindings-of-specials?)
	(rename-specials-in-arglist <argument-list>)
      (when let-bindings-of-specials?
	(setq <argument-list> new-argument-list)
	(setq <body-after-doc-and-decl>
	      `((ab-lisp::let ,let-bindings-of-specials?
		  ,@<body-after-doc-and-decl>)))))))



;;; The :protect-stack and :do-not-protect-stack modifications to ab::defun

(def-defun-modification :protect-stack
    (<progn-before-forms> <progn-after-forms>)
    ()
  #+chestnut
  (when (member :chestnut-trans *features*)
    (push `(eval-when (compile)
	     (setq trans:*protect-local-variables* t))
	  <progn-after-forms>))

  #+chestnut-3 
  nil ;Stack protection is the default in Chestnut 3.1
  )

(def-defun-modification :do-not-protect-stack
    (<progn-before-forms> <defun-name> <progn-after-forms>)
    ()
  #+chestnut
  (when (member :chestnut-trans *features*)
    (push `(eval-when (compile)
	     (setq trans:*protect-local-variables* nil))
	  <progn-after-forms>))

  ;; Test the new translator global switch trans:*rtl-includes-gc-p*, which has
  ;; been set to NIL in set-up-chestnut-defaults in bootstrap.  -jra 12/16/93
  #+chestnut-3
  nil
;  (when (member :chestnut-trans *features*)
;    (push `(declaim (tx:nonrelocating ,<defun-name>))
;          <progn-before-forms>))
  
  )



;;; The :unshadow-catch modification to ab::defun is used in
;;; defun-allowing-unwind and defun-for-top-level ...

(def-defun-modification :unshadow-catch
    (<body-after-doc-and-decl>)
    ()
  (setq <body-after-doc-and-decl>
	`((with-catch-unshadowed
	    ,@<body-after-doc-and-decl>))))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro with-catch-unshadowed (&body body)
  `(macrolet
       ((catch (tag &rest forms)
	  `(ab-lisp::catch ,tag ,@forms))
	(unwind-protect (protected-form &rest cleanup-forms)
	  `(ab-lisp::unwind-protect
		,protected-form
	     ,@cleanup-forms)))
     ,@body))
)


#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(ab-lisp::defun get-defun-modifications-from-doc-and-decl-forms
                (doc-and-decl-forms-list)
  (let ((defun-modifications nil)
	(filtered-doc-or-decl-forms nil))
    (do* ((doc-or-decl-forms
	    doc-and-decl-forms-list
	    (cdr doc-or-decl-forms))
	  (doc-or-decl-form
	    (car doc-or-decl-forms)
	    (car doc-or-decl-forms)))
	 ((null doc-or-decl-forms))
      (if (and (consp doc-or-decl-form)
	       (eq (car doc-or-decl-form) 'declare))
	  (let ((filtered-decl-specs? nil))
	    (do* ((decl-specs (cdr doc-or-decl-form) (cdr decl-specs))
		  (decl-spec (car decl-specs) (car decl-specs)))
		 ((null decl-specs)
		  (when filtered-decl-specs?
		    (push (cons 'declare (nreverse filtered-decl-specs?))
			  filtered-doc-or-decl-forms)))
	      (let* ((kind-of-declaration
		       (if (symbolp decl-spec)
			   decl-spec
			   (car decl-spec)))
		     (spec-as-keyword
		       (intern (symbol-name kind-of-declaration) "KEYWORD")))
		(if (assoc spec-as-keyword defun-modification-alist)
		    (pushnew (if (symbolp decl-spec)
				 spec-as-keyword
				 (cons spec-as-keyword (cdr decl-spec)))
			     defun-modifications)
		    (push decl-spec filtered-decl-specs?)))))
	  (push doc-or-decl-form filtered-doc-or-decl-forms)))
    (values (nreverse defun-modifications)
	    (nreverse filtered-doc-or-decl-forms))))
)



;;; The :intercept-declaration modification to ab::defun extends the syntax of
;;; declare forms in the defun body.  Any symbol in a declare form whose name is
;;; the same as a known defun modification will cause that modification to be
;;; run.

;;; If any such symbol is already in the modification list for that variant of
;;; defun, then none of the other modifications are run that normally occur for
;;; that variant.  If no such symbol is already in the modification list for
;;; that variant of defun, then all other modifications are run that normally
;;; occur for that variant, in addition to the modification given by that
;;; symbol.  The intent is that the user can easily either supplant or
;;; supplement the normal defun modifications for that variant.

;;; For example,
;;;
;;;  (defun-allowing-unwind emaciated (x)
;;;    (declare protect-stack)
;;;    (list x x))
;;;
;;; will only run the :protect-stack defun modification.  It will not run
;;; :rebind-specials, nor any other defun modification associated with
;;; defun-allowing-unwind, since the :do-not-protect-stack defun modification is
;;; already specified for the defun-allowing-unwind variant.  In contrast,
;;;
;;;  (defun-allowing-unwind enhanced (x)
;;;    (declare allow-lisp-pathnames)
;;;    (list x x))
;;;
;;; will run all the defun modifications associated with defun-allowing-unwind
;;; (including both :rebind-specials and :protect-stack), and in addition will
;;; run the :allow-lisp-pathnames defun modification that is explicitly
;;; specified in the declaration.

;;; As a special case for easier debugging, the :intercept-declaration
;;; modification will always cause the :notice-defun-name modification to be
;;; run, regardless of the presence or absence of :notice-defun-name in the
;;; defun-with-modifications form or in the declare form inside the defun being
;;; processed.

;; jh, 9/24/93.  The implementation of the :intercept-declaration defun
;; modification involved special-casing defun-with-modifications to run with
;; this modification alone, and only run other modifications if this
;; modification did not rewrite the defun.  We should consider abstracting this
;; special-casing, as well as the hard-wiring of :notice-defun-name.

(def-defun-modification :intercept-declaration
    (<progn-before-forms>
      <defun-name>
      <argument-list>
      <doc-and-decl-forms>
      <body-after-doc-and-decl>
      <progn-after-forms>
      <listed-defun-replacement-form?>
      <original-defun-modifications>)
    ()
  (multiple-value-bind (defun-modifications? real-doc-and-decl-forms)
      (get-defun-modifications-from-doc-and-decl-forms
	<doc-and-decl-forms>)
    (when defun-modifications?
      (setq <original-defun-modifications>
	    (remove :intercept-declaration <original-defun-modifications>))
      (let ((modifications-to-use
	      (if (intersection
		    defun-modifications?
		    <original-defun-modifications>)
		  defun-modifications?
		  (append defun-modifications? <original-defun-modifications>))))
	(multiple-value-setq (<progn-before-forms>
			       <defun-marker>
			       <defun-name>
			       <argument-list>
			       <doc-and-decl-forms>
			       <body-after-doc-and-decl>
			       <progn-after-forms>
			       <listed-defun-replacement-form?>
			       ;; note omission of <original-defun-modifications>
			       )
	  (apply-defun-modifications
	     <progn-before-forms>
	     <defun-marker>
	     <defun-name>
	     <argument-list> 
	     real-doc-and-decl-forms
	     <body-after-doc-and-decl>
	     <progn-after-forms>
	     <listed-defun-replacement-form?>
	     modifications-to-use))
	(setq intercept-declaration-rewrote-defun-p t)))))




;;; The macro `ab::defun' shadows ab-lisp::defun ...

(defmacro defun (defun-name defun-arglist &body doc-and-decl-and-body)
  `(defun-with-modifications (:notice-defun-name
			      :rebind-specials
			      :do-not-protect-stack
			      :intercept-declaration
			      )
     ,defun-name
     ,defun-arglist
     ,@doc-and-decl-and-body))

;; jh, 9/24/93.  Modified defun to use :intercept-declaration (see note above,
;; under its def-defun-modification form).

;; jra & jh, 9/16/92.  Chestnut claims they have fixed the problem with defun in
;; their new 3.1 release.  (Recall the problem was that special variables
;; mentioned in the lambda-list of defun forms did not work properly.) We are
;; therefore commenting out our version and re-introducing the original
;; lisp:defun.  This is a repercussion of our project to abstract the LISP
;; package.  It seems when the TI Lisp compiler encounters "Common Lisp" on the
;; mode line, it complains if either (1) the current package doesn't directly
;; use the LISP package or (2) the current package lacks the symbol lisp:defun.
;; Test (2) is a heuristic to detect if the current package gets LISP package
;; symbols in some indirect way.  In our package abstraction, AB now uses
;; AB-LISP, which in turn uses LISP, and so we fail (1).  Re-introducing
;; lisp:defun allows us to pass test (2).

;; jh, 1/21/93 (much after the fact).  An update to the comment above.  We have
;; backed away from declining to shadow defun in Chestnut.  So the state of
;; affairs as of this date is that we shadow defun in the macro pass in Chestnut
;; and at no other time.

;; jh & ac, 5/29/91.  Changed defun to allow us to protect local variables on a
;; per-function basis in Chestnut.  See note under defun-for-top-level for more
;; details.




;;;; Shadowed Lisp Pathname Functions

;;; The module PATHNAMES contains analogues to most of the Lisp pathname
;;; functions, designed in such a way as to allow us to manage memory use.
;;; Hence, using Lisp pathname functions is almost always wrong, so we shadow
;;; the symbols for these functions in such a way as to emit a warning during
;;; the translate pass if these functions will be used.  The defun variant
;;; `defun-allowing-lisp-pathnames' suppresses these warnings, allowing us to
;;; use Lisp pathname functions in the few cases where they are legitimate.

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar all-shadowed-lisp-pathname-functions nil)
)

(defmacro def-shadowed-pathname-function (ab-name)
  (ab-lisp::let ((lisp-name (intern (symbol-name ab-name) "AB-LISP")))
    (pushnew (list ab-name lisp-name)
	     all-shadowed-lisp-pathname-functions
	     :test #'equal)
    `(defmacro ,ab-name (&rest args)
       (when (member :chestnut-trans *features*)
	 (warn "~a being called in distribution near ~a.~%~
                ~2tThis is a Lisp pathname function, ~
                   not a Gensym pathname function.~%~
                ~2tThe Lisp function will be used, but please review."
	       ',ab-name
	       most-recent-defun-name))
       `(,',lisp-name ,@args))))


(def-shadowed-pathname-function directory)
(def-shadowed-pathname-function directory-namestring)
(def-shadowed-pathname-function enough-namestring)
(def-shadowed-pathname-function file-namestring)
(def-shadowed-pathname-function delete-file)
(def-shadowed-pathname-function host-namestring)
(def-shadowed-pathname-function make-pathname)
(def-shadowed-pathname-function merge-pathnames)
(def-shadowed-pathname-function namestring)
(def-shadowed-pathname-function parse-namestring)
(def-shadowed-pathname-function pathname)
(def-shadowed-pathname-function pathname-device)
(def-shadowed-pathname-function pathname-directory)
(def-shadowed-pathname-function pathname-host)
(def-shadowed-pathname-function pathname-name)
(def-shadowed-pathname-function pathname-type)
(def-shadowed-pathname-function pathname-version)
(def-shadowed-pathname-function pathnamep)
(def-shadowed-pathname-function probe-file)
(def-shadowed-pathname-function rename-file)
(def-shadowed-pathname-function copy-file)
(def-shadowed-pathname-function truename)
(def-shadowed-pathname-function wild-pathname-p)

(def-defun-modification :allow-lisp-pathnames
    (<body-after-doc-and-decl>)
    ()
  (let ((macrolet-specs nil))
    (do* ((functions all-shadowed-lisp-pathname-functions (cdr functions))
	  (entry (car functions) (car functions))
	  (ab-name (first entry) (first entry))
	  (lisp-name (second entry) (second entry)))
	 ((null functions) (setq macrolet-specs (nreverse macrolet-specs)))
      (push (if (and (eq current-system-being-loaded 'gsi)
		     (member :chestnut-trans *features*))
		`(,ab-name (&rest args) `(progn ,@args))
		`(,ab-name (&rest args) `(,',lisp-name ,@args)))
	    macrolet-specs))
    (setq <body-after-doc-and-decl>
	  `((macrolet ,macrolet-specs
	      ,@<body-after-doc-and-decl>)))))

(defmacro defun-allowing-lisp-pathnames
          (defun-name defun-arglist &body doc-and-decl-and-body)
  `(defun-with-modifications (:notice-defun-name
			      :rebind-specials
			      :do-not-protect-stack
			      :intercept-declaration
			      :allow-lisp-pathnames)
     ,defun-name
     ,defun-arglist
     ,@doc-and-decl-and-body))

;; jh, 12/29/94.  :Eliminate-for-gsi highlights the need to allow defun
;; modifications that take arguments.

;;; The :eliminate-for-gsi defun modification allows GSI to remove functions it
;;; will never need without rearranging the entire module in which those
;;; functions appear.

(def-defun-modification :eliminate-for-gsi
    (<listed-defun-replacement-form?>)
    ()
  (when (gsi-eliminable-p)
    (unless (eval-feature :development)
      (setq <listed-defun-replacement-form?> (list nil)))))


;;; The :eliminate-for-gsi-no-utf-g defun modification allows GSI to remove
;;; functions it will never need without rearranging the entire module in which
;;; those functions appear.  Read this declaration as "eliminable in GSI with no
;;; UTF-G (mapping) support", and keep in mind that, for now (5/8/96) and
;;; indefinitely into the future, UTF-G mapping support is really needed, so
;;; this should never be true in GSI or in any other product/system known about
;;; at this time.  Also note that usage of this declaration was initiated with
;;; replacements in relevant code of the eliminate-for-gsi declaration, q.v.

(def-defun-modification :eliminate-for-gsi-no-utf-g
    (<listed-defun-replacement-form?>)
  ()
  (when (gsi-no-utf-g-eliminable-p)
    (unless (eval-feature :development)
      (setq <listed-defun-replacement-form?> (list nil)))))


;;; The :eliminate-for-no-macros-gsi defun modification allows GSI to remove
;;; functions it will never need without rearranging the entire module in which
;;; those functions appear.

(def-defun-modification :eliminate-for-no-macros-gsi
    (<listed-defun-replacement-form?>)
    ()
  (when (gsi-eliminable-p)
    (when (eval-feature :no-macros)
      (setq <listed-defun-replacement-form?> (list nil)))))


(defmacro defvar-excluding-gsi (&rest args)
  (if (and (gsi-eliminable-p)
	   (not (eval-feature :development)))
      nil
      `(defvar ,@args)))

(defmacro defvar-excluding-gsi-no-utf-g (&rest args)
  (if (and (gsi-no-utf-g-eliminable-p)
	   (not (eval-feature :development)))
      nil
      `(defvar ,@args)))

;; At present only the DEFVAR variant is needed (defvar-excluding-gsi-no-utf-g);
;; define others, e.g., the defparameter variant, as needed.  (MHD 5/9/96)


(defmacro defparameter-excluding-gsi (name &rest args)
  (if (and (gsi-eliminable-p)
	   (not (eval-feature :development)))
      `(defparameter ,name nil)
      `(defparameter ,name ,@args)))

(defmacro defparameter-excluding-no-macros-gsi (name &rest args)
  (if (and (gsi-eliminable-p)
	   (not (eval-feature :development))
	   (eval-feature :no-macros))
      `(defparameter ,name nil)
      `(defparameter ,name ,@args)))

(defmacro defvar-excluding-no-macros-gsi (name &rest args)
  (if (and (gsi-eliminable-p)
	   (not (eval-feature :development))
	   (eval-feature :no-macros))
      `(defvar ,name nil)
      `(defvar ,name ,@args)))

(defmacro defconstant-excluding-gsi (&rest args)
  (if (and (gsi-eliminable-p)
	   (not (eval-feature :development)))
      nil
      `(defconstant ,@args)))

;;; The :no-op-for-gsi defun modification allows GSI to stub out functions it
;;; will never need without rearranging the entire module in which those
;;; functions appear.

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(ab-lisp::defun arguments-in-arglist (original-arglist)
  (let ((result-arglist nil))
    (do* ((arglist original-arglist (cdr arglist))
	  (arg (car arglist) (car arglist)))
	 ((null arglist))
      (cond
	((member arg lambda-list-keywords))
	((consp arg) ;&optional or &key with explicit default
	 (let ((first-argform (first arg)))
	   (push (if (consp first-argform)
		     (second first-argform) ;&key with supplied keyword
		     first-argform) ;&key with implicit keyword or &optional
		 result-arglist)))
	(t (push arg result-arglist))))
    (nreverse result-arglist)))
)

(def-defun-modification :no-op-for-gsi
    (<listed-defun-replacement-form?> <defun-name> <argument-list>)
    ()
  (when (gsi-eliminable-p)
    (setq <listed-defun-replacement-form?>
	  (list
	    `(progn
	       (ab-lisp::defun ,<defun-name> ,<argument-list>
		 (declare (ignore
			    ,@(arguments-in-arglist <argument-list>)))))))))


(def-defun-modification :no-op-for-no-macros-gsi
    (<listed-defun-replacement-form?> <defun-name> <argument-list>)
    ()
  (when (gsi-eliminable-p)
    (when (eval-feature :no-macros)
      (setq <listed-defun-replacement-form?>
	    (list
	      `(progn
		 (ab-lisp::defun ,<defun-name> ,<argument-list>
		   (declare (ignore
			      ,@(arguments-in-arglist
				  <argument-list>))))))))))




;;; The :simple defun modification allows a (declare simple) inside a bare defun
;;; to do what the defun-simple macro does.  Note that this macro is not defined
;;; until GLBASICS, so such a declaration should not be used until then.

(def-defun-modification :simple
    (<defun-marker>)
    ()
  (setq <defun-marker> 'defun-simple))




;;; The :void defun modification allows a (declare void) inside a bare defun to
;;; do what the defun-void macro does.  Note that this macro is not defined
;;; until GLBASICS, so such a declaration should not be used until then.

(def-defun-modification :void
    (<defun-marker>)
    ()
  (setq <defun-marker> 'defun-void))




;;; The :eliminate-for-products defun modification is a generalization of the
;;; :eliminate-for-gsi defun modification.


(def-defun-modification :eliminate-for-products
    (<listed-defun-replacement-form?>)
    (products)
  (when (member current-system-being-loaded products)
    (unless (eval-feature :development)
      (setq <listed-defun-replacement-form?> (list nil)))))




;;; The macro `defun-allowing-unwind' ...

;;; The top-level form defun-allowing-unwind behaves like defun, and additionaly
;;; guarantees that any local variables within its scope will obey Common Lisp
;;; semantics under catch and unwind-protect.  Some Lisp-to-C translators
;;; implement these constructs using setjmp, which typically restores register
;;; contents to their original value after a longjmp.  This can cause problems for
;;; local variables inside the defun which have been register-allocated.  If such
;;; a variable is side-effected (as by setq) and a throw occurs, the restored
;;; environment binds the variable to the value it had before the side-effect.
;;; Defun-allowing-unwind should be used in place of defun whenever the body,
;;; after complete macroexpansion, will contain a call to catch or unwind-protect.
;;; Using a normal defun under these circumstances will cause the compiler to
;;; emit a warning at macroexpansion time.

;; jh per jra, bah, and blm, 9/25/91.  Chestnut has a problem in their
;; implementation of catch and unwind-protect.  They use the C setjmp construct,
;; which saves the state of the computation, and restores this state when
;; encountering a longjmp.  The problem arises because "the state of the
;; computation" includes registers.  Thus a side-effect to a register-allocated
;; variable will vanish if a longjmp occurs.  For example, the following code will
;; misbehave, returning OLD instead of NEW, if x is register-allocated.

;;(let ((x 'old))
;;  (catch 'bash
;;    (setq x 'new)
;;    (throw 'bash nil))
;;  x)

;; Our short-term solution is to prevent the C compiler from register-allocating
;; local variables.  Chestnut contains a switch, trans:*protect-local-variables*,
;; which does this as a side-effect.  The intended use of this switch is to ensure
;; that local variables on the stack become part of the root set for garbage
;; collection.  The side effect is that the translator includes a reference to the
;; address of local variables in the C code, thereby preventing the C compiler
;; from register-allocating them.  This is just what we need.  On the Lisp side,
;; owners of all affected functions should use defun-allowing-unwind.

(defmacro defun-allowing-unwind
          (defun-name defun-arglist &body doc-and-decl-and-body)
  `(defun-with-modifications (:notice-defun-name
			       :rebind-specials
			       :protect-stack
			       :unshadow-catch
			       :intercept-declaration)
       ,defun-name
       ,defun-arglist
     ,@doc-and-decl-and-body))

;;; The :allowing-unwind defun modification allows a (declare allowing-unwind)
;;; inside a bare defun to do what the defun-allowing-unwind macro does.

(def-defun-modification :allowing-unwind
    (<defun-marker>)
    ()
  (setq <defun-marker> 'defun-allowing-unwind))




;;; The macro `defun-for-top-level' ...

;;; Within some implementations (ok, Chestnut) the functions which lie above the
;;; top-level run loop in in the stack must be compiled differently than other
;;; functions.  For Chestnut, a function which can cause garbage collections
;;; will occur within the top level function, and every function at or above
;;; this point needs to be compiled with "garbage collection protection".  So
;;; the macro `defun-for-top-level' should be used to define those functions which
;;; will be called at or above the top-level loop.

(defmacro defun-for-top-level
    (defun-name defun-arglist &body doc-and-decl-and-body)
  `(defun-with-modifications (:notice-defun-name
			       :rebind-specials
			       :protect-stack
			       :unshadow-catch
			       :intercept-declaration)
       ,defun-name
       ,defun-arglist
     ,@doc-and-decl-and-body))

;;; The :top-level defun modification allows a (declare top-level) inside a bare
;;; defun to do what the defun-top-level macro does.

(def-defun-modification :top-level
    (<defun-marker>)
    ()
  (setq <defun-marker> 'defun-for-top-level))



;;; The macro ab::catch allows us to shadow catch so the omission of a
;;; defun-allowing-unwind will emit warnings.

;; jh, 9/25/91.  Redefining catch as a macro so we can detect cases in Chestnut
;; where local variables are unprotected through a setjmp.  Note that the symbol
;; catch is shadowed in LOAD so the macro will be properly visible to subsequent
;; code.  (Details on this fix are under the definition of ab::defun in
;; BOOTSTRAP).

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar most-recent-defun-warned-for-catch? nil)
)

(defmacro catch (tag &rest forms)
  (unless (eq most-recent-defun-name
	      most-recent-defun-warned-for-catch?)
    (warn "CATCH used in manner not in keeping with AB's coding conventions~
             ~@[,~%~3tnear definition of ~a~]"
	  most-recent-defun-name)
    (setq most-recent-defun-warned-for-catch? most-recent-defun-name))
  `(ab-lisp::catch ,tag ,@forms))

;;; The macro ab::unwind-protect allows us to shadow unwind-protect so the
;;; omission of a defun-allowing-unwind will emit warnings.

;; jh, 9/25/91.  Redefining unwind-protect as a macro so we can detect cases in
;; Chestnut where local variables are unprotected through a setjmp.  Note that the
;; symbol unwind-protect is shadowed in LOAD so the macro will be properly visible
;; to subsequent code.  (Details on this fix are under the definition of ab::defun
;; in BOOTSTRAP).

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar most-recent-defun-warned-for-unwind-protect? nil)
)

(defmacro unwind-protect (protected-form &rest cleanup-forms)
  (unless (eq most-recent-defun-name
	      most-recent-defun-warned-for-unwind-protect?)
    (warn "UNWIND-PROTECT used in manner not in keeping with AB's coding conventions~
             ~@[,~%~3tnear definition of ~a~]"
	  most-recent-defun-name)
    (setq most-recent-defun-warned-for-unwind-protect?
	  most-recent-defun-name))
  `(ab-lisp::unwind-protect ,protected-form ,@cleanup-forms))





;;; The macro `ab::funcall' expands to a call to gensym-funcall which
;;; ends up calling the Lisp funcall, or expanding into optimized code
;;; on a machine specific basis.

(defmacro funcall (function &rest args)
  ;; Gensym-funcall is in GLBASICS.
  `(gensym-funcall ,function ,@args))




;;; The macro `ab::symbol-function' expands to a call to gensym-symbol-function
;;; which ends up calling the lisp symbol-function.

#+shadow-symbol-function
(eval-when (:compile-toplevel :load-toplevel :execute)

(shadow '(symbol-function))

(pushnew :shadow-symbol-function *features*)

(defmacro symbol-function (symbol)
  ;; gensym-symbol-function is in GLBASICS
  `(gensym-symbol-function ,symbol))

(defsetf symbol-function (symbol) (new-value)
  ;; setf-gensym-symbol-function is in GLBASICS
  `(setf-gensym-symbol-function ,symbol ,new-value))

)






;;; The macro `ab::symbol-value' expands to a call to gensym-symbol-value which ends up
;;; calling the lisp symbol-value.

#+shadow-symbol-value
(eval-when (:compile-toplevel :load-toplevel :execute)

(shadow '(symbol-value))

(pushnew :shadow-symbol-value *features*)

(defmacro symbol-value (symbol)
  ;; gensym-symbol-value is in GLBASICS
  `(gensym-symbol-value ,symbol))

(defsetf symbol-value (symbol) (new-value)
  ;; setf-gensym-symbol-value is in GLBASICS
  `(setf-gensym-symbol-value ,symbol ,new-value))

)


;;;; ANSI Common Lisp Compliance

;; Chestnut3.1

;; jh, 1/22/93.  Introduced new macros to cover "CLtL" Common Lisp facilities
;; that are not present, or present under a different name, in ANSI Common Lisp.
;; Each symbol is redefined in the AB package, either to duplicate the
;; functionality where it can be accessed, or to signal an error at compile time
;; if the functionality is not accessible in the host Lisp.  The symbols are:

;;  symbol               cite                in ANSI?
;;  ------               ----                --------
;;  *break-on-warnings*  CLtL/2e p 669       no
;;  char-bit             CLtL/2e p 386       no
;;  compiler-let         CLtL/2e p 151       no
;;  define-setf-method   ANSI draft p 5-96   yes, define-setf-expander
;;  get-setf-method      ANSI draft p 5-98   yes, get-setf-expansion
;;  int-char             CLtL/2e p 385       yes, code-char
;;  set-char-bit         CLtL/2e p 387       no
;;  special-form-p       ANSI draft p 3-100  yes, special-operator-p
;;  string-char          CLtL/2e p 460       sort of
;;  string-char-p        CLtL/2e p 376       no
;;  declaim                                  yes, not in pre-ANSI

;; The column "in ANSI?" tells whether ANSI supports equivalent functionality.
;; In cases where it doesn't, the macro signals an error at compile time.  The
;; row for string-char needs further explanation.  The string-char type in ANSI
;; is an implementation-specific union of various subtypes of character, so the
;; best we can do is set up a deftype equivalence to the character type.

;; jh, 1/27/93.  Deftype does not work in Chestnut, so we introduce a macro and
;; edit all the callers that would have depended on a deftype.

;; jh, 1/26/93.  As well, the symbol declaim is lacking in non-ANSI
;; implementations, so we define it below.

;; jh, 3/11/93.  The symbol lisp:*break-on-signals* is not translated properly
;; by the the new translator.  It tries to insert
;; lucid-common-lisp:*break-on-signals*.  Backing out until we figure out what
;; is wrong.

;; jh, 3/12/93.  Actually, Lucid has lost *break-on-warnings*, but the
;; translator seems to need this obsolete thing.  Will question Chestnut soon.

;; jh, 6/9/93.  *Break-on-signals* is not a replacement for *break-on-warnings*.
;; Besides, the new Chestnut 3.1 translator implements neither, despite their
;; presence in Common Lisp.  So we will track down all the occurrences of
;; *break-on-warnings* and remove calls to the gensym-break-on-warnings-symbol
;; abstraction there, since the variable is not needed in Chestnut.

(defmacro char-bit (&whole call char name)
  #+chestnut-3
  (declare (ignore char name))
  #+chestnut-3
  (progn 
    (warn "~s~%ANSI Common Lisp does not support CHAR-BIT~
           ~@[,~%~3tused near definition of ~a~] -- will always return nil" 
	  call
	  most-recent-defun-name)
    nil)

  #-chestnut-3
  (declare (ignore call))
  #-chestnut-3
  `(ab-lisp::char-bit ,char ,name)
  )

(defmacro compiler-let (&whole call specs &body body)
  #+(or chestnut-3 ansi-cl)
  (declare (ignore specs body))
  #+(or chestnut-3 ansi-cl)
  (error "~s~%ANSI Common Lisp does not support COMPILER-LET~
          ~@[,~%~3tused near definition of ~a~]"
	 call
	 most-recent-defun-name)

  #-(or chestnut-3 ansi-cl)
  (declare (ignore call))
  #-(or chestnut-3 ansi-cl)
  `(ab-lisp::compiler-let ,specs ,@body)
  )

(defmacro define-setf-method 
	  (access-function lambda-list &body body)
  #+(or chestnut-3 ansi-cl)
  `(ab-lisp::define-setf-expander ,access-function ,lambda-list ,@body)

  #-(or chestnut-3 ansi-cl)
  `(ab-lisp::define-setf-method ,access-function ,lambda-list ,@body)
  )

(defmacro get-setf-method (form)
  #+(or chestnut-3 ansi-cl)
  `(ab-lisp::get-setf-expansion ,form)

  #-(or chestnut-3 ansi-cl)
  `(ab-lisp::get-setf-method ,form)
  )

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro int-char (integer)
  #+(or chestnut-3 ansi-cl)
  `(ab-lisp::code-char ,integer)

  #-(or chestnut-3 ansi-cl)
  `(ab-lisp::int-char ,integer)
  )
)

(defmacro set-char-bit (&whole call char name newvalue)
  #+(or chestnut-3 ansi-cl)
  (declare (ignore char name newvalue))
  #+(or chestnut-3 ansi-cl)
  (progn
    (warn "~s~%ANSI Common Lisp does not support SET-CHAR-BIT~
           ~@[,~%~3tused near definition of ~a~] -- will be a no-op" 
	  call
	  most-recent-defun-name)
    nil)

  #-(or chestnut-3 ansi-cl)
  (declare (ignore call))
  #-(or chestnut-3 ansi-cl)
  `(ab-lisp::set-char-bit ,char ,name ,newvalue)
  )

(defmacro special-form-p (symbol)
  #+chestnut-3
  `(ab-lisp::special-operator-p ,symbol)

  #+(and (not chestnut-3) (not ansi-cl))
  `(ab-lisp::special-form-p ,symbol)

  #+(and (not chestnut-3) ansi-cl)
  `(special-operator-p ,symbol)
  )

;; jra, cpm, & jh, 1/27/93.  Don't use deftype -- it is unreliable.  Call
;; gensym-string-char-type instead.

(defmacro gensym-string-char-type ()
  #+chestnut-3
  `'tx:string-char

  #+(and lucid (not chestnut-3))
  `'ab-lisp::string-char

  #+(and sbcl (not chestnut-3))
  `'cl:character

  #+(and lispworks (not chestnut-3))
  `'cl:base-char

  #+(and allegro (not chestnut-3))
  `'excl::string-char

  #+(and clozure (not chestnut-3))
  `'cl:base-char
  )

(defmacro string-char-p (char)
  #+chestnut-3 
  `(ab-lisp::typep ,char 'tx:string-char)
  
  #+(and lucid (not chestnut-3))
  `(ab-lisp::typep ,char 'ab-lisp::string-char)

  #+(and sbcl (not chestnut-3))
  `(cl:typep ,char 'cl:character)

  #+(and lispworks (not chestnut-3))
  `(cl:typep ,char 'cl:base-char)

  #+(and allegro (not chestnut-3))
  `(excl::string-char-p ,char)

  #+(and clozure (not chestnut-3))
  `(cl:typep ,char 'cl:base-char)
  )

(defmacro declaim (&whole call &rest specs)
  #+(or chestnut-3 ansi-cl)
  (declare (ignore call))
  #+(or chestnut-3 ansi-cl)
  `(ab-lisp::declaim ,@specs)

  #-(or chestnut-3 ansi-cl)
  (declare (ignore specs))
  #-(or chestnut-3 ansi-cl)
  (error "~s~%non-ANSI Common Lisps do not support DECLAIM~
          ~@[,~%~3tused near definition of ~a~]" 
	 call
	 most-recent-defun-name)
  )

;;;; Eval-feature


;;;; String And Symbol Matching Functions



(defmacro uppercase-string (x)
  `(string-upcase (string ,x)))


;;; The function `string-or-symbol-equal' ...

(eval-when (:compile-toplevel :load-toplevel :execute)

(defun string-or-symbol-equal (symbol-or-string-1 symbol-or-string-2)
  (and (or (symbolp symbol-or-string-1) (stringp symbol-or-string-1))
       (or (symbolp symbol-or-string-2) (stringp symbol-or-string-2))
       (string-equal (string symbol-or-string-1)
		     (string symbol-or-string-2))))

)




;;; The macro `string-or-symbol-member' expands to a member test with the
;;; function string-or-symbol-equal as the equality test.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro string-or-symbol-member (symbol-or-string list-of-symbols-or-strings)
  `(member ,symbol-or-string ,list-of-symbols-or-strings
	   :test #'string-or-symbol-equal))
)




;; (jh, 9/27/90)

;;; with-package-specific-symbols
;;;     (package-specs) &rest body
;;;
;;; On occasion we need to mention a package-qualified symbol even though we
;;; aren't sure that the package exists.  This has happened recently in our
;;; translator efforts, where the translator's host Lisp has a package that the
;;; destination Lisp lacks.  For example, suppose a Lucid-specific memory
;;; allocation form contains the symbol lucid::change-memory-management.  Although
;;; this form need not be present in the resulting Chestnut Lisp image, the symbol
;;; is read anyway, since the reader has to read in enough of a form to be able
;;; to ignore it.  This causes an error in Chestnut when the reader reaches the
;;; package qualifier for the unknown "LUCID" package.
;;;
;;; Note that this is only a problem in macros, since any defuns with
;;; platform-specific symbols are not read in the host Lisp and never make it to
;;; the macro phase as long as the conditionalization #-translator is used.
;;;
;;; The solution is to refer to a package-qualified symbol by its printname and
;;; package name and thus bypass the symbol-reader entirely.  The macro
;;; with-package-specific-symbols accomplishes this by interning and substituting
;;; the package-qualified symbol into a macroexpansion only when it finds that the
;;; package exists.  When the package doesn't exist, with-package-specific-symbol
;;; leaves the symbol alone, since the code will never be executed anyway.  This
;;; arrangement gives the reader something to skip over, does the right thing when
;;; we actually intend to use the code, and makes the code more perspicuous than
;;; sprinkling it throughout with (intern "SYMBOL" "PACKAGE") forms.
;;;
;;; The form package-specs is of the format
;;;   (package1 |::| symbol1
;;;    package2 |::| symbol2
;;;    ...)
;;; and is intended to resemble the package-qualified symbols visually.  Note that
;;; the middle item, the symbol whose printname consists of two colons, is
;;; syntactic sugar.
;;;
;;; This macro also has the advantage of documenting in one place the
;;; platform-specific calls we make.

(defmacro with-package-specific-symbols (package-specs &body body)
  (let (platform-specific-symbol-alist)
    (do ((these-package-specs package-specs (cdddr these-package-specs)))
	((null these-package-specs))
      (let ((the-package (first these-package-specs))
	    (symbol (third these-package-specs)))
	(when (find-package the-package)
	  (push
	    (cons symbol
		  (intern (symbol-name symbol) (symbol-name the-package)))
	    platform-specific-symbol-alist))))
    (if (= (length body) 1)
	(setq body (car body))
	(setq body `(progn ,@body)))
    (if platform-specific-symbol-alist
	`(sublis ',platform-specific-symbol-alist
		 ,body)
	body)))



;;; Eval-feature returns nil unless feature is present in the current
;;; environment.  The feature arg may be a string or symbol in any package.
;;; Eval-feature is often useful to use at compile time, especially as an
;;; alternative to the #+feature reader syntax.  It is available in this module
;;; (bootstrap) at compile time.  C.f.  status (MacLisp), *features*
;;; (Common-lisp).
;;;
;;; The feature arg to feature may be anything acceptable as the arg to
;;; sharpsign-plus (#+).  E.g. (eval-feature 'symbolics), (eval-feature '(or
;;; symbolics lucid)), and (featurep '(or (and lispm (not ti) (not lmi) (not
;;; cadr)) 3600)) would all be true on a symbolics 3600 machine.  See the
;;; common lisp documentation of *features* for further information.
;;;

;; Moved here from UTILITIES.  -pto 19dec88

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun eval-feature (feature)
  (if (atom feature)
      (if (eq feature t)
	  feature
	  (string-or-symbol-member feature *features*))
      (case (car feature)
	(and
	 (pop feature)
	 (if feature
	     (do* ((features feature (cdr features))
		   (feature (car features) (car features)))
		  ((null features) t)
	       (if (not (eval-feature feature))
		   (return nil)))
	     t))
	(or
	 (pop feature)
	 (if feature
	     (do* ((features feature (cdr features))
		   (feature (car features) (car features)))
		  ((null features) nil)
	       (if (eval-feature feature)
		   (return t)))
	     nil))
	(not
	 (not (eval-feature (cadr feature)))))))
)



;; At this point, we have all the standard Common Lisp macros.








;;; `Defvar-for-macro' introduces a variable in the style of defvar.  It
;;; arranges to have that variable defined only when we are defining
;;; macros.  It arranges to have that varaible defined and visible to
;;; macros and defuns for macro.

;;; Apparently, on the symbolics, the initial value works only when the
;;; variable is defined in one file and used in a later file.

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)

(defmacro defvar-for-macro (name &body body)
  (unless (member :no-macros *features*)
    `(eval-when (:compile-toplevel :load-toplevel :execute)
      (defvar ,name . ,body))))

)



;;; The macro `defparameter-for-macro' ...

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)

(defmacro defparameter-for-macro (name &body body)
  (unless (member :no-macros *features*)
    `(eval-when (:compile-toplevel :load-toplevel :execute)
      (defparameter ,name . ,body))))

)



;;; The macro `progn-for-macro' ... almost always needs a nested eval-when

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)

(defmacro progn-for-macro (&body body)
  (unless (member :no-macros *features*)
    `(progn
      ,@body)))

)



;;; The macro `defun-for-macro' ...

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)

(defmacro defun-for-macro (name arglist &body body)
  (unless (member :no-macros *features*)
    `(eval-when (:compile-toplevel :load-toplevel :execute)
      (defun-allowing-unwind ,name ,arglist . ,body))))

)

;; jh, 2/28/91.  Added eval-when scope to the def-xxx-for-macro things above.
;; They are not much use at macroexpansion time any other way.

;; jh, 10/6/91.  Changed defun-for-macro to expand to defun-allowing-unwind
;; instead of defun, so we can avoid getting "catch semantics violated" warnings
;; for macro-pass functions, which won't be translated.



;;; The macro `defun-for-non-macro' is used to define functions which do not
;;; need to be available in the macro pass of a distribution compile.  During a
;;; macro pass this will expand to NIL, otherwise it expands into a defun of the
;;; arguments given here.  This is currently being done to reduce the size of a
;;; macro compile pass so that we can compile on the Macintosh.  However, the
;;; use of this facility may be extended in the future such that we have two
;;; truely different environments for macro and distribution compiles, with very
;;; little overlap between them.  For now, this defining form will only be used
;;; for functions which are FUNCALLed, so that we will not be flooded with
;;; warning messages.  The evaluator functions will be the first targets.  When
;;; we want to extend this to more general usage, this should define a function
;;; of the given name which expands into a call to error, which would alert us
;;; to those functions which actually are called at macro pass time.  -jra & ml
;;; 11/3/89

;; CCL is no longer EVER true, so this is no longer EVER defined NOT to emit the
;; defun.  (MHD/AC 5/30/91)

(defmacro defun-for-non-macro (name arguments &body declarations-and-forms)
  `(defun ,name ,arguments ,@declarations-and-forms))







;;; AC 08-12-91: moved these definitions beyond the definitions for 
;;; defvar-for-macro and defun-for-macro.

;;; `Gensym-within-module' returns an uninterned symbol that is both unique
;;; within this module and which is highly likely to have the same print name
;;; from one compile to the next.  That's good since if they did then
;;; the C sources would change even if nothing really changed.

;;; `Gensym-within-module-counter' provides a source of integers for creating
;;; unique names.  While `current-module-for-gensym-within-module' is used to
;;; trigger resetting the counter used by gensym-within-module.

;;; Currently the only known use for this mechinism is to allow you to generate
;;; code where the Chestnut translator must not rename any of your symbols.

(defvar current-module? nil)

(defvar-for-macro current-module-for-gensym-within-module nil)

(defvar-for-macro gensym-within-module-counter 0)

(defun-for-macro gensym-within-module ()
  (unless (eql current-module-for-gensym-within-module
	       current-module?)
    (setf current-module-for-gensym-within-module
	  current-module?)
    (setf gensym-within-module-counter 
	  (if current-module?
	      10000
	      20000)))
  (make-symbol
   (format nil "Z~D" (incf gensym-within-module-counter))))









;;;; Declare-Forward-Reference

;; declare-forward-reference symbol types-of-reference
;; declare-forward-reference symbol types-of-reference module

;;; `Declare-forward-reference' causes the compiler not to worry about forward
;;; references in the current module.
;;;
;;; The syntax is
;;;
;;;    (declare-forward-reference . forward-reference-spec)
;;;
;;; where forward-reference-spec is
;;;
;;;    (symbol {type-of-reference}+ [module])
;;;
;;; Type-of-reference is either VARIABLE or FUNCTION. If forward-reference is
;;; used as a variable in the current module, and variable is among the elements
;;; of types-of-references, then declare-forward-reference will cause the
;;; compiler to consider that symbol to be special.  If forward-reference is
;;; used as a function in the current module, and function is among the
;;; types-of-references then that symbol will be given a dummy functional
;;; binding (if it does not already have one).  None of the arguments are
;;; evaluated, and they should all be symbols.
;;;
;;; Module is a symbol that is neither FUNCTION nor VARIABLE.
;;; Declare-forward-reference makes some checks for inconsistent module
;;; declarations.  It is optional.

;;; `Declare-forward-references' allows a list of forward reference specs.  If
;;; the first form in a declare-forward-references is a list whose car is
;;; :suppress-module-checks-for, and the system being loaded is a member of the
;;; cdr of that list, then module checking will not occur.  This is useful when
;;; you only want to stub out a function that a system never intends to call.
;;; In the future (jh, 10/21/93), this might replace artifacts like TW-PATCHES.

;;; `Declare-forward-references-to-module' lets you gang things together that
;;; are all for one module.  It also defaults type-of-reference to FUNCTION,
;;; exploiting the fact that these make up the vast majority of cases.

(eval-when (:compile-toplevel :load-toplevel :execute)

;; jh, 10/21/93.  The standin functions created by
;; stand-in-for-forwardly-referenced-function all call
;; signal-forward-reference so that we only have a single code constant for the
;; cerror string, rather than as many as there are forward references.

(defun signal-forward-reference (name-of-function?)
  (declare (eliminate-for-no-macros-gsi))
  (if name-of-function?
      (cerror "Ignore this problem and proceed."
	      "The forwardly referenced function ~a is still undefined!"
	      name-of-function?)
      (cerror "Ignore this problem and proceed."
	      "This forwardly referenced function is still undefined!")))

(defun stand-in-for-forwardly-referenced-function
    (&optional arg1 arg2 arg3 arg4 arg5        ; add any number as needed
	       arg6 arg7 arg8 arg9 arg10 arg11 arg12 arg13 arg14
	       arg15 arg16 arg17 arg18 arg19 arg20 arg21 arg22 arg23
	       arg24 arg25 arg26 arg27 arg28 arg29 arg30)
  (declare
    (ignore arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9 arg10 arg11 arg12
	    arg13 arg14 arg15 arg16 arg17 arg18 arg19 arg20 arg21 arg22 arg23
	    arg24 arg25 arg26 arg27 arg28 arg29 arg30)
    (eliminate-for-no-macros-gsi))
  (signal-forward-reference nil))

#-translator
(progn

(defun create-standin-for-forwardly-referenced-function (name-of-function)
  (if (member :development *features*)
      #'(#-lucid lambda
	 #+lucid lcl:named-lambda #+lucid stand-in-for-forwardly-referenced-function
	    (&optional arg1 arg2 arg3 arg4 arg5        ; add any number as needed
		       arg6 arg7 arg8 arg9 arg10 arg11 arg12 arg13 arg14
		       arg15 arg16 arg17 arg18 arg19 arg20 arg21 arg22 arg23
		       arg24 arg25 arg26 arg27 arg28 arg29 arg30)
	  (declare
	    (ignore arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9 arg10 arg11 arg12
		    arg13 arg14 arg15 arg16 arg17 arg18 arg19 arg20 arg21 arg22 arg23
		    arg24 arg25 arg26 arg27 arg28 arg29 arg30))
	  (signal-forward-reference name-of-function))
      (symbol-function 'stand-in-for-forwardly-referenced-function)))

(defun declare-forwardly-referenced-function (forward-reference)
  (when (not (fboundp forward-reference))
    (setf (symbol-function forward-reference)
	  (create-standin-for-forwardly-referenced-function
	    forward-reference))))
)

) ; end of eval-when

(defvar-for-macro allowed-declare-forward-reference-types
  '(variable function))

;;; The macro `declare-forward-reference-simple' is an internal abstraction
;;; designed to ease the task of adding functionality to
;;; declare-forward-references.  Its arguments are the result of parsing the
;;; arguments to a forward declaration spec.  Declare-forward-reference-simple
;;; should not be used outside of this module (currently BOOTSTRAP).

;; jh, 10/21/93.  Modified declare-forward-reference-simple to generate a
;; standin function for forwardly referenced functions that reports the name of
;; the function.  This involves creating closures, but only in development.

(defmacro declare-forward-reference-simple
          (forward-reference
	    variable-reference-p
	    function-reference-p
	    declared-module?)

    (when declared-module?

      (check-for-an-actually-existing-module declared-module?)

      ;; Check that, if the declaration mentions a module, previous declarations
      ;; for the same symbol did not mention a different one.
      (flet ((check-module-consistency (property type-present-p type-name)
	       (when type-present-p
		 (let ((previously-declared-module?
			 (get forward-reference property)))
		   (when previously-declared-module?
		     (unless (eq declared-module?
				 previously-declared-module?)
		       (warn "DECLARE-FORWARD-REFERENCE: ~(~S~) ~S,~%~
                              previously declared to be in module ~S,~%~
                              now declared to be in module ~S"
			     type-name
			     forward-reference
			     previously-declared-module?
			     declared-module?)))))))
	(check-module-consistency
	  'module-defining-forwardly-referenced-variable?
	  variable-reference-p
	  'variable)
	(check-module-consistency
	  'module-defining-forwardly-referenced-function?
	  function-reference-p
	  'function)))

    `(progn

       ;; Handle forwardly-referenced variables if necessary.
       ,@(if (and variable-reference-p
		  (not (eval-feature '(and translator chestnut-trans))))
	     `((eval-when (:compile-toplevel :load-toplevel :execute)
		 (proclaim '(special ,forward-reference))))
	     nil)
       ,@(if (and variable-reference-p declared-module?)
	     `((eval-when (:compile-toplevel)
		 (setf (get ',forward-reference
			    'module-defining-forwardly-referenced-variable?)
		       ',declared-module?)))
	     nil)

       ;; Handle forwardly-referenced functions if necessary.
       ,@(cond
	   ((eval-feature :translator)
	    nil)
	   (t (if function-reference-p
		 `((eval-when (:compile-toplevel :load-toplevel :execute)
		     (declare-forwardly-referenced-function ',forward-reference)))
		 nil)))
       ,@(if (and function-reference-p declared-module?)
	     `((eval-when (:compile-toplevel)
		 (setf (get ',forward-reference
			    'module-defining-forwardly-referenced-function?)
		       ',declared-module?)))
	     nil)))



(defmacro declare-forward-reference
	  (forward-reference &rest types-of-references-and-possibly-module)

  ;; Destructure the arguments.
  (let* ((final-arg (car (last types-of-references-and-possibly-module)))
	 (declared-module?
	   (if (member final-arg allowed-declare-forward-reference-types)
	       nil
	       final-arg))
	 (types-of-references?
	   (if declared-module?
	       (butlast types-of-references-and-possibly-module)
	       types-of-references-and-possibly-module))
	 (variable-reference-p (and (member 'variable types-of-references?) t))
	 (function-reference-p (and (member 'function types-of-references?) t)))

    ;; Check that the declaration contains at least one permissible
    ;; reference-type.
    (unless (and types-of-references?
		 (null (set-difference
			 types-of-references?
			 allowed-declare-forward-reference-types)))
      (warn "DECLARE-FORWARD-REFERENCE: ~
             ~S has a malformed set of reference types."
	    forward-reference))

    `(declare-forward-reference-simple
       ,forward-reference
       ,variable-reference-p
       ,function-reference-p
       ,declared-module?)))

(defmacro declare-forward-references (&rest forward-reference-specs)
  (let* ((possible-suppression-spec (first forward-reference-specs))
	 (suppression-spec-p
	   (and (listp possible-suppression-spec)
		(eq (first possible-suppression-spec)
		    :suppress-module-checks-for)))
	 (systems-to-suppress-module-checking-for?
	   (and suppression-spec-p
		(rest possible-suppression-spec)))
	 (suppress-module-checking-p
	   (or (not (boundp		; usu. in-buffer compile case
		      'current-system-being-loaded))
	       (member current-system-being-loaded
		       systems-to-suppress-module-checking-for?)))
	 (declarations nil))
    (do* ((specs-list
	    (if suppression-spec-p
		(rest forward-reference-specs)
		forward-reference-specs)
	    (cdr specs-list))
	  (spec (car specs-list) (car specs-list)))
	 ((null specs-list) `(progn ,@(nreverse declarations)))
      (if suppress-module-checking-p
	  (push `(declare-forward-reference-simple
		   ,(first spec)
		   ,(and (member 'variable spec) t)
		   ,(and (member 'function spec) t)
		   nil)
		declarations)
	  (push `(declare-forward-reference ,@spec) declarations)))))

(defmacro declare-forward-references-to-module (module &rest references)
  `(declare-forward-references
     . ,(let ((result nil))
	  (dolist (reference references)
	    (push (if (atom reference)
		      `(,reference function ,module)
		      `(,@reference ,module))
		  result))
	  result)))

;; The somewhat byzantine syntax of declare-forward-reference is due in some
;; part to forward compatability problems.  In particular, MODULE has not been
;; required because it was not even possible to specify for the first 7 years
;; ('86-'93) of this macro's life.  The forms
;; declare-forward-references-for-modules and declare-forward-references are
;; newer (10/93), but are quickly gaining popularity.  (MHD 10/15/93)

;; TO DO: (now that we have module information)
;;
;; After loading each module, for each forward reference to that module, check
;; to make sure that the reference has been resolved by loading that module.
;; Complain if unresolved.  For functions, use fdefinedp.  There may not be a
;; portable "specialp" for variables -- just abstract from that and do the best
;; you can for each implementation.  (MHD 10/15/93)

;;   Changed to defvar. -pto 10sep90

;;   WHY?! -- Changed back.  Defvar initial bindings
;;     get made again when compiling in the buffer in
;;     Zmacs.  This could be dangerous.  The above
;;     is perfectly valid and exactly what we want as
;;     far as I can see. (MHD 1/7/91)

;; 'Round and 'round we go.  Chestnut cannot handle double defvars of variables.
;; If you have more than one defvar, it turns into more than one definition of
;; the same variable in the C files, which is an error in C.  Also, since
;; Chestnut does multiple passes over the source code, forward references are
;; never required.  This is why declare-forward-reference should be a no-op for
;; Chestnut, always.  The reason that Peng changed the proclaim special into a
;; defvar is that Chestnut ignores proclaim specials.  Peng must not have
;; realized that this would cause a bug because of double defvars.  -jra 2/1/91


;; Moved here from primitives.  -pto 10mar89


;;; `Find-dead-forward-references' warns of all symbols function bound to the
;;; forward reference stand in function.  It is called in G2-FINAL during the
;;; macro pass to assure (at least) that forward references to development only
;;; functions are guarded by #+development.

#-no-macros
(defun find-dead-forward-references ()
  #+lucid
  (do-symbols (symbol (find-package 'ab))
    (let (symbol-function)
      (when (fboundp symbol)
	(when (and (typep (setf symbol-function (symbol-function symbol))
			  'system:procedure)
		   (eq (system:procedure-name symbol-function)
		       'stand-in-for-forwardly-referenced-function))
	  (unless (eq symbol 'stand-in-for-forwardly-referenced-function)
	    (warn "~S, introduced in a forward reference, was never defined."
		  symbol)))))))

;; This works only in LUCID.  It is designed to be robust in spite of bootstrap
;; loading multiple times, and hence redefining the symbol-function of
;; stand-in-for-forwardly-referenced-function.  See g2-final for call site.
;; - ben 3/9/94







#-no-macros
(defmacro feature-case (&body case-clauses)
  (let* ((cond-body nil)
	 test)
    (dolist (case-clause case-clauses)
      (setq test (car case-clause))
      (cond
	((and (not (symbolp test))
	      (not (and (listp test) (or (eq (car test) 'not)
					 (eq (car test) 'and)
					 (eq (car test) 'or)))))
	 (error "(feature-case ...) can only have symbols or and, or, and not in the case clauses."))
	((eq test t) (push case-clause cond-body))
	(t (push `((eval-feature ',test) ,@(rest case-clause))
		 cond-body))))
    `(cond
       ,@(nreverse cond-body))))






;; jh, 3/28/91.

;;; The macro ifdef-case works like feature-case, with some reduced functionality.
;;; It is used for translator compilations.  The translated C code is always
;;; produced on a single machine and then compiled on many different target
;;; machines, on which the G2 image will actually run.  This is different from the
;;; olden days, where we could count on the compilation machine and the target
;;; machine being identical.  Thus we need access to C compilation features when
;;; we use the translator.

;;; IMPORTANT NOTE: ifdef-case is now (7/16/91) denigrated for runtime use.  It
;;; remains a useful facility for quick patches and experiments, so the code will
;;; stay here for a while.

;;; A clause in ifdef-case takes the form (<matcher> .  <keyforms>).  The
;;; <keyforms> are placed in conditional compilation context in the translated C
;;; source code depending on the specification in <matcher>, which may be either a
;;; symbol or a list.  If <matcher> is a symbol, the <keyforms> will only be
;;; processed by the C compiler if that symbol is defined in the compilation
;;; environment.  If <matcher> is a list, it should be a boolean expression of
;;; symbols to be checked in the C compilation environment.  The only currently
;;; (3/28/91, jh) supported boolean operation is a non-recursive or.

;;; It is important to note that the ifdef-case form is intended to be "evaluated"
;;; at runtime, not compile-time.  Thus, unlike feature-case, macros should expand
;;; to ifdef-case forms rather than use ifdef-case to help them macroexpand to
;;; something else.  This is because the macro wants to insert
;;; conditionally-compiled code in the C translatation, but has no idea what
;;; compilation features are present when the C compiler actually does its work,
;;; since this will probably occur on a different platform.

;;; For now (3/28/91, jh), another important limitation is that all the features
;;; used by a given ifdef-case form are assumed to be disjoint.  This makes things
;;; a lot easier in generating the ifdef wrappers in the translated C code, and
;;; has met our needs so far.

;;; Note that the bare Chestnut construct trun::ifdef does not suit our purposes,
;;; since it does not undertake to return anything useful.  (The documentation
;;; claims it duplicates the functionality of the Lisp when, not the Lisp if.)

;; Discovered an obscure bug when do, let, and list interact on the Lispm:
;;(defun test1 ()
;;  (let ((outer 'result))
;;    (do ((stepper t nil))
;;        ((null stepper))
;;      (let ((inner (list outer)))
;;        (return inner)))))
;;
;;(defun test2 ()
;;  (let ((outer 'result))
;;    (do ((stepper t nil))
;;        ((null stepper))
;;      (let ((inner nil))
;;        (setq inner (list outer))
;;        (return inner)))))
;;
;;(test1)
;;RESULT   ;what happened to the list !?
;;
;;(test2)
;;(RESULT) ;correct!
;;
;; This should not affect the macroexpansion of ifdef-case where it counts, in
;; Lucid on a UNIX machine, but we should document it somewhere.  jh, 3/28/91.

;; jh, 4/1/91.

;; Added def-ifdef-feature to stop complaints during the first (file-loading) pass
;; of the translator.  In this pass, Chestnut trun:ifdef and trun:ifndef expand to
;; when and unless, and these special forms evaluate their test argument.  In the
;; second (translation) pass, trun:ifdef and trun:ifndef cause compile-time
;; switches #ifdef and #ifndef to be placed in the resulting C code, and don't
;; refer to their test argument at all.
;; Thus a form like
;;   (trun:ifdef |unix| (do-unix-things))
;; needs the special variable |unix| bound during the first pass, but it doesn't
;; care about this in second pass, when all it does is emit
;;   #ifdef unix
;;   do_unix_things();
;;   #endif

;; This macro makes the bindings appropriate to the translator environment, in the
;; unlikely event someone should need to debug there.  For example, the form
;;   (def-ifdef-feature unix)
;; expands to
;;   (defvar |unix| t)
;; if the translation is carried out under UNIX, and
;;   (defvar |unix| nil)
;; otherwise.

(defmacro def-ifdef-feature (name)
  (if (and (or (eval-feature :chestnut)
	       (eval-feature :chestnut-3)) ;Chestnut3.1
	   (not (eval-feature :chestnut-trans)))
      (let ((ifdef-defvar-name
	      (intern
		(string-downcase
		  (symbol-name name)))))
	`(defvar ,ifdef-defvar-name
		 ,(and (member (intern (symbol-name name) "KEYWORD")
			       *features*)
		       t)))
      nil))

(def-ifdef-feature unix)
(def-ifdef-feature vms)
(def-ifdef-feature sun)
(def-ifdef-feature decstation)
(def-ifdef-feature aviion)
(def-ifdef-feature rs6000)
(def-ifdef-feature hp)
(def-ifdef-feature i386)
(def-ifdef-feature solaris)
(def-ifdef-feature linux)
(def-ifdef-feature masscomp)
(def-ifdef-feature hppa) ;DO we need this? REVIEW
(def-ifdef-feature dec)




(defmacro ifdef-case (&rest clauses)
  (with-package-specific-symbols (trun |::| ifdef
				  trun |::| ifndef)
    (let ((result-of-ifdef '#:result-of-ifdef))
      `(let ((,result-of-ifdef nil))
	 ,@(let ((result-clauses nil)
		 (non-default-features nil))
	     (dolist (clause clauses result-clauses)
	       (let ((keylist (car clause))
		     (keyforms (cdr clause))
		     (form-to-set-result nil))
		 (setq form-to-set-result ;bug in lispm let! jh, 3/28/91.
		       `(setq ,result-of-ifdef
			      (progn ,@keyforms)))
		 (setq result-clauses
		       (append
			 result-clauses
			 (cond
			   ((and (member keylist '(otherwise t))
				 t)		; chestnut idiom (MHD 1/15/92)
			    (let ((default-clause nil))
			      (dolist (non-default-feature
					non-default-features
					(list default-clause))
				(let ((downcased-non-default-feature
					(intern
					  (string-downcase
					    (symbol-name non-default-feature)))))
				  (if (null default-clause)
				      (setq default-clause
					    `(ifndef ,downcased-non-default-feature
						     ,form-to-set-result))
				      (setq default-clause
					    `(ifndef ,downcased-non-default-feature
						     ,default-clause)))))))
			   ((symbolp keylist)
			    (let ((downcased-keylist
				    (intern
				      (string-downcase
					(symbol-name keylist)))))
			    (push downcased-keylist non-default-features)
			    `((ifdef ,downcased-keylist ,form-to-set-result))))
			   ((not (listp keylist))
			    (error "IFDEF-CASE: expected a list, not ~a"
				   keylist))
			   ((not (eq (first keylist) 'or))
			    (error "IFDEF-CASE: unsupported boolean ~a ~
                                    in complex keylist"
				   (first keylist)))
			   (t (let ((disjunctive-features nil)
				    (disjunctive-clauses nil))
				(dolist (disjunctive-feature (rest keylist))
				  (if (symbolp disjunctive-feature)
				      (push (intern
					      (string-downcase
						(symbol-name disjunctive-feature)))
					    disjunctive-features)
				      (error "IFDEF-CASE: expected a symbol, ~
                                              not ~a"
					     disjunctive-feature)))
				(setq non-default-features
				      (append disjunctive-features
					      non-default-features))
				(dolist (disjunctive-feature
					  disjunctive-features
					  (nreverse disjunctive-clauses))
				  (push
				    `(ifdef ,(string-downcase
					       (symbol-name disjunctive-feature))
					    ,form-to-set-result)
				    disjunctive-clauses))))))))))
	 ,result-of-ifdef))))





;;;; Master Source and Machine Specific Directories




;;; At the present time, there are several places within the code where
;;; explicit references exist to directories for storing source and binary
;;; files while developing at Gensym.  Specifically, the file 123.lisp,
;;; bootstrap.lisp, and site.lisp contain references to the Massachusetts AB
;;; directory.  In an effort to locate this data in a single place, the
;;; following parameters are defined to point to appropriate directory
;;; placements on the differing machines.  Note that these parameters are never
;;; used outside of the Gensym development facilities, but since they are
;;; needed while compiling "non-development" versions of the code, they cannot
;;; be development compiler switched.

;;; The further reason to consolodate the references to directories is that in
;;; order for the updating software to work correctly on release directories,
;;; as well as development directories, we need to be able to redirect requests
;;; for version numbers when asking from the VAX, Sun, HP, etc.  For this
;;; reason, when we spin off, there has to be one spot which gets changed to
;;; redirect the requests for updates.

;;; All machines need to know where the master copies of files are on
;;; Massachusetts (for the moment, the fact that the file server is
;;; Massachusetts will still be hard coded into the files).  Each non-Lisp
;;; machine then also needs to know where to store its binaries for macro and
;;; dst compiles of the software.




;;; The parameter `master-host' is a string representing the name of
;;; the host computer which holds the master sources.

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
  (defparameter master-host (string-downcase  "ma")))

;; The parameter master-host is included today to allow a quick fix of a
;; problem which spinning off Beta3 and while trying to make a tape.  It
;; should be fixed such that the references to master-host below are
;; compiler switched in the same way as this defparameter.  -jra & pto
;; 5/1/90





(eval-when (:compile-toplevel :load-toplevel :execute)
  (setq *load-pathname* (bootstrap-information-default-pathname)))




;;; The parameter `master-lisp-source-file-type' is the string containing the
;;; file type of the lisp source files on the master directory.

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
  (defparameter master-lisp-source-file-type "LISP"))


(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter-for-macro lisp-source-directory-name "lisp")
(defparameter-for-macro lisp-dest-directory-name "lisp")
(defparameter-for-macro standard-lisp-binary-directory-name "dev")
(defparameter-for-macro standard-chestnut-binary-directory-name
  cl-user::*dest-macro-directory-name*)
(defparameter-for-macro standard-distribution-dst-directory-name "dst")
(defparameter-for-macro special-dev-directory-name "dev-special")
(defparameter-for-macro chestnut-dev-directory-name "chestnut-dev")
(defparameter-for-macro chestnut-macro-directory-name "chestnut-macro")
(defparameter-for-macro chestnut-trans-directory-name "chestnut-trans")
)

;;; The system property `local-source-directory' is the directory on the local
;;; machine where the sources for this release of G2 are stored.  This
;;; parameter is used into the pull-in-modules... software, and so is not used
;;; in the Lisp machines.  Note that the host "ma:" has to be in the string
;;; because the TI's can't parse it otherwise.

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
  (defun make-pathname-directories (base-pathname &rest directories)
    (let ((pathname
           (make-pathname :directory (append (pathname-directory base-pathname)
                                             directories)
                          :defaults base-pathname)))
      ;; Note: it's not safe to call this from lisp when doing parallel translations,
      ;; We have to disable it and use ant scripts instead. -- Chun Tian (binghe)
      #+ignore
      (cl:ensure-directories-exist pathname)
      pathname)))

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
  (setf (get 'ab 'local-source-directory)
        (make-pathname-directories source-directory-name lisp-source-directory-name)))

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defun-for-macro default-ab-local-development-binary-directory ()
    (make-pathname-directories dest-directory-name
                               lisp-dest-directory-name
                               (if (eval-feature '(or dev-special shadow-funcall
                                                      shadow-symbol-function shadow-symbol-value
                                                      SymScale mtg2))
                                   special-dev-directory-name
                                 standard-lisp-binary-directory-name))))

;;; The system property `local-development-binary-directory' stores the place
;;; where binaries for development compiles of G2 are to be put.

#+development
(eval-when (:compile-toplevel :load-toplevel :execute)
  (setf (get 'ab 'local-development-binary-directory)
        (default-ab-local-development-binary-directory)))





#+development
(eval-when (:compile-toplevel :load-toplevel :execute)
  (setf (get 'ab 'local-chestnut-development-directory)
        (make-pathname-directories source-directory-name
                                   lisp-source-directory-name
                                   chestnut-dev-directory-name)))

;;; The system property `local-macro-directory' stores the place where binaries
;;; for macro compiles of G2 are to be put.  This and the following parameters
;;; are used by the 123 compiling code.

#-(and chestnut-3 chestnut-trans)
(eval-when (:compile-toplevel :load-toplevel :execute)
  (let ((dest-folder (make-pathname-directories
                       dest-directory-name
                       lisp-dest-directory-name
                       standard-chestnut-binary-directory-name
                       "macro")))
    (setf (get 'ab 'local-macro-directory) dest-folder)
    (setf (get 'gsi 'local-macro-directory) dest-folder)
    (setf (get 'telewindows 'local-macro-directory) dest-folder)))

#-chestnut-3
(eval-when (:compile-toplevel :load-toplevel :execute)
  (setf (get 'ab 'local-chestnut-macro-directory)
        (make-pathname-directories dest-directory-name
                                   lisp-dest-directory-name
                                   chestnut-macro-directory-name)))

;;; The system property `local-dst-directory' stores the directory where
;;; binaries for the distribution compile of G2 are to be stored.

#-(and chestnut-3 chestnut-trans)
(eval-when (:compile-toplevel :load-toplevel :execute)
  (setf (get 'ab 'local-dst-directory)
        (make-pathname-directories dest-directory-name
                                   lisp-dest-directory-name
                                   standard-distribution-dst-directory-name)))

#-(and chestnut-3 chestnut-trans)
(eval-when (:compile-toplevel :load-toplevel :execute)
  (setf (get 'ab 'local-chestnut-dst-directory)
        #+SymScale (make-pathname-directories source-directory-name "SymScale" "c")
        #+mtg2 (make-pathname-directories source-directory-name "mtg2" "c")
        #-(or mtg2 SymScale) (make-pathname-directories source-directory-name "g2" "c"))
  (setf (get 'telewindows 'local-chestnut-dst-directory)
        (make-pathname-directories source-directory-name "tw" "c"))
  (setf (get 'gsi 'local-chestnut-dst-directory)
        #+gsi-web (make-pathname-directories source-directory-name "gw" "c")
        #-gsi-web (make-pathname-directories source-directory-name "gsi" "c")))

#-(and chestnut-3 chestnut-trans)
(eval-when (:compile-toplevel :load-toplevel :execute)
  (setf (get 'ab 'local-chestnut-dst-misc-directory)
        (make-pathname-directories source-directory-name "g2" "c" "misc"))
  (setf (get 'telewindows 'local-chestnut-dst-misc-directory)
        (make-pathname-directories source-directory-name "tw" "c" "misc")))

#-(and chestnut-3 chestnut-trans)
(eval-when (:compile-toplevel :load-toplevel :execute)
  (setf (get 'ab 'local-chestnut-trans-directory)
        (make-pathname-directories dest-directory-name
                                   lisp-dest-directory-name
                                   chestnut-trans-directory-name)))

;;; REVIEW

;;; Definitions for the Check-Memory Function

;;; The check memory facility is defined extremely late in
;;; G2 but used widely.   To ease using it we put up
;;; a forward reference right away to "check-memory."

;;; Most modules will want to forward reference this too.

#+development
(declare-forward-reference check-memory function)

(declare-forward-reference initialize-check-memory function)







;;; The macro `check-memory-for-development' expands to a call to check-memory
;;; if it is compiled in the development environment, and to nil if not.

(defmacro check-memory-for-development (&optional label?)
  (when (eval-feature :development)
    `(let ()
       (declare (special check-memory-enabled-p))
       (when check-memory-enabled-p
	 (check-memory ,label?)))))







;;;; Macro Statistics

;; Has to come before all other defmacros.


(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro initialize-macro-statistics ()
  (if (eval-feature :macro-statistics)
      (setq macro-statistics (make-hash-table :test #'eq :size 1000))
      (setq macro-statistics nil)))
)


(defun-for-macro report-macro-statistics ()
  (cond (macro-statistics
	 (format t "~%Collecting Statistics.  One moment, please.")
	 (let* ((macro-vector
		  (make-array (hash-table-count macro-statistics)))
		(index 0))
	   (maphash #'(lambda (key value)
			(setf (svref macro-vector index) (cons key value))
			(incf index))
		    macro-statistics)
	   (format t "~%Sorting.")
	   (sort macro-vector #'> :key #'cdr)
	   (let ((string "Macro usage during the last compile"))
	     (format t "~2%~a ~v,,,'.a.. Uses"
		     string (- 77 (length string)) ""))
	   (do ((length (length macro-vector))
		(x 0 (+ x 1)))
	       ((>= x length) nil)
	     (let* ((element (svref macro-vector x))
		    (macro (car element))
		    (count (cdr element)))
	       (format
		 t "~%  ~a ~v,,,'.a.. ~4d"
		 macro
		 (max 0 (- 77 (length (string macro)))) ""
		 count)))))
	(t
	 (format
	   t "~%No statistics have been gathered in this environment."))))


(defun-for-macro macro-symbol-name (statistics-entry)
  (symbol-name (car statistics-entry)))

(defun-for-macro report-alphabetical-macro-statistics ()
  (cond (macro-statistics
	 (format t "~%Collecting Statistics.  One moment, please.")
	 (let* ((macro-vector
		  (make-array (hash-table-count macro-statistics)))
		(index 0))
	   (maphash #'(lambda (key value)
			(setf (svref macro-vector index) (cons key value))
			(incf index))
		    macro-statistics)
	   (format t "~%Sorting.")
	   (sort macro-vector #'string-lessp :key #'macro-symbol-name)
	   (let ((string "Macro usage during the last compile"))
	     (format t "~2%~a ~v,,,'.a.. Uses"
		     string (- 77 (length string)) ""))
	   (do ((length (length macro-vector))
		(x 0 (+ x 1)))
	       ((>= x length) nil)
	     (let* ((element (svref macro-vector x))
		    (macro (car element))
		    (count (cdr element)))
	       (format
		 t "~%  ~a ~v,,,'.a.. ~4d"
		 macro
		 (max 0 (- 77 (length (string macro)))) ""
		 count)))))
	(t
	 (format
	   t "~%No statistics have been gathered in this environment."))))











;;;; File IO


;;; The macro `delete-file-if-it-exists' ...

(defmacro delete-file-if-it-exists (string-or-pathname)
  ;; (delete-file-if-it-exists foo)
  `(let ((file? (probe-file ,string-or-pathname)))
     (when file? (delete-file file?))))







;;; The macro `string-or-symbol-remove' ...

(defmacro string-or-symbol-remove (item sequence)
  `(remove ,item ,sequence :test #'string-or-symbol-equal))


(defmacro string-or-symbol-delete (item sequence)
  `(delete ,item ,sequence :test #'string-or-symbol-equal))










;;;; Platform Dependent Abstraction




(defmacro run-unix-program-macro (&rest args)
  (feature-case
    (:lucid
      (feature-case
	((or :ultrix :lcl5.0) ; run-unix-program is obsolete
	  `(,(intern "RUN-PROGRAM" "LUCID") ,@args))
	(t
	  `(,(intern "RUN-UNIX-PROGRAM" "LUCID") ,@args))))
    (:allegro
      `(,(intern "RUN-SHELL-COMMAND" "EXCL") ,@args))
    (t
      nil)))

;; Temporarily fixed by not redirecting stderr AC 16mar90
;;						       
;; GET LUCID TO FIX THEIR PROBLEM WITH ULTRIX!!
;;#+(and lucid-2 vax ultrix)
;;(defun lucid::run-program (&rest args)
;;  (format t "~% lucid::run-program called with ~a  - doesn't work on Vax Ultrix"
;;	  args))




;; Variables for updating files

#+(or remote-updates development)
(defvar-for-macro module-version-plist)

#+(or remote-updates development)
(defvar-for-macro updates-file-pathname)


;;;; File Copying functions



(defun-allowing-lisp-pathnames pathnames-similar-p
    (pathname-1 pathname-2)
  (declare (eliminate-for-no-macros-gsi))
  (and (equal (uppercase-string (directory-namestring pathname-1))
	      (uppercase-string (directory-namestring pathname-2)))
       (equal (uppercase-string (pathname-name pathname-1))
	      (uppercase-string (pathname-name pathname-2)))
       (equal (uppercase-string (pathname-type pathname-1))
	      (uppercase-string (pathname-type pathname-2)))))



(defmacro copy-file-with-open-file (source target)
  (let ((source-stream (gensym))
	(target-stream (gensym)))
  `(with-open-file (,source-stream ,source :direction :input)
     (with-open-file (,target-stream ,target :direction :output)
       (do ((char (read-char ,source-stream nil nil)
		  (read-char ,source-stream nil nil)))
	   ((null char))
	 (write-char char ,target-stream))))))


;;; The function `gensym-copy-file' copies the source file to the target file,
;;; given the pathnames of each.  No copying will be done if the source refers
;;; to the same file as the target (i.e. if the pathname-name, pathname-type,
;;; and pathname-directory are the same).

#-no-macros					;needed if macros present
(defun-for-macro gensym-copy-file (source-pathname-or-string
				    target-pathname-or-string)
  (let ((source (pathname source-pathname-or-string))
	(target (pathname target-pathname-or-string)))
    (when (not (pathnames-similar-p source target))
      #-unix
      (copy-file-with-open-file source target)
      ;; Because Unix does not have version numbers, if the source and
      ;; target are the same physical file (though they might have different
      ;; pathnames), the target will override the source.  Hence, we have
      ;; a backup file to act as the intermediate output file.
      #+unix
      (let ((backup (make-pathname
		      :defaults target
		      :type (format nil "~a~~" (pathname-type target))))
	    (tmp-target (make-pathname
			  :defaults target
			  :type (format nil "#~a" (pathname-type target)))))
	(when (probe-file target)
	  (copy-file-with-open-file target backup))
	(copy-file-with-open-file source tmp-target)
	(rename-file tmp-target target)))))




#-no-macros					;needed if macros present
(defun-for-macro copy-file-with-same-file-type-if-necessary
		 (source-pathname target-pathname)
  (let* ((source (pathname source-pathname))
	 (target (make-pathname :defaults (pathname target-pathname)
				:type (pathname-type source))))
    (gensym-copy-file source target)))








;;;; Compiling for Distribution


(defvar current-directory-of-source-truenames?)
						; Non-nil flags that this
						;   feature is in use.

(defvar current-directory-of-binary-truenames)

(defvar pathname-for-distribution-binaries?)

(defvar use-directory-lists-for-bootstrapping? nil)

(defvar last-bootstrap-mode? nil)







;;; The function `execute-command-line' takes a command-line (a string) and
;;; executes it as if it was typed as an operating system command.  Under
;;; Unix, the command-line is executed in a C shell (csh).

#-(and lispworks win32)
(defun-for-macro execute-command-line 
    (command-line-string)
  #-(and lucid unix)
  (format t "~%Execute-command-line in Unix:  ~s~%" command-line-string)
  #+(and lucid unix)
  (let* ((command-filename			; unique filename (hopefully)
	   (namestring
	     (make-system-pathname
	       current-system-being-loaded "cmdline" "temp" nil)
;	       (make-pathname
;		 :defaults updates-file-pathname
;		 :name "cmdline"
;		 :type "temp")
	     )))
    (unwind-protect
	 (multiple-value-bind
	     (error-info error-p)
	     (lucid::with-error-trapping
		 (with-open-file (output command-filename :direction :output)
		   (format output "~a~%" command-line-string))
	       (progn
		 (run-unix-program-macro "csh"
					 :wait t :arguments command-filename)))
	   (when error-p
	     (format t "~%Error in command: ~a.~%" error-info)))
      (delete-file-if-it-exists command-filename))
    (delete-file-if-it-exists command-filename))
  #+allegro
  (excl:run-shell-command command-line-string))

#+(and lispworks win32)
(defun-for-macro execute-command-line (&rest args) (declare (ignore args)))





;;;; Integer Related Constants

;;; The constant `positive-bits-per-fixnum' stores the integer-length of
;;; most-positive-fixnum.  This is the number of bit flags that may be stored
;;; within a single fixum in G2.

(defconstant-excluding-gsi positive-bits-per-fixnum
    (integer-length most-positive-fixnum))





;;;; Floating Point Numbers




;;; The type gensym-float is defined as the floating point number type inside of
;;; G2.  See the documentation under "Floating Pointer Number Management
;;; Primitives" in module UTILITIES for further details.


#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
  (defun-for-macro gensym-float-type-function ()
    ''double-float)
  (defun-for-macro gensym-long-type-function ()
    ''(signed-byte 64)))

;; Should be (have been) called expand-gensym-float-type-macro, since it does
;; not produce the same thing as gensym-float-type!  Anyway, it's overcomplicated,
;; so simplify when there's a recompile opportunity! (MHD/AC 5/30/91)

(defmacro gensym-float-type ()
  (gensym-float-type-function))

(deftype gensym-float () #.(gensym-float-type-function))

(defmacro gensym-long-type ()
  (gensym-long-type-function))

(deftype gensym-long () #.(gensym-long-type-function))



;; jra & jh.  The constant least-positive-normalized-gensym-float is not used
;; much, currently only in the parameter smallest-order-of-magnitude in
;; UTILITIES1.  Consider removing eventually.  This number can be obtained from
;; DBL_FLT_MIN in /usr/include/float.h on most UNIX platforms, or from the
;; Chestnut include file config.h.

(defconstant least-positive-normalized-gensym-float 2.2250738585072014d-308)






(defconstant most-negative-gensym-float most-negative-double-float)
(defconstant most-positive-gensym-float most-positive-double-float)

;; jh, 3/20/92.  Changed the definitions of the most-xxx-gensym-float constants
;; to use the Lisp most-xxx-double-float constants directly, instead of inlining
;; them with a #.  read-macro.  This was causing problems in float-writing when
;; we translated onto VMS platforms, since the inline number is too large to be
;; represented in native G-float format.








;;; In development, globally set the *read-default-float-format* to whatever
;;; gensym-float-type is, so that compiles in buffer intern constant floating
;;; point numbers correctly.

#+development
(setq *read-default-float-format* (gensym-float-type))

;; This had been commented out.  We really need to stop losing by not having
;; this bound properly for incremental compiles in our editor buffers.
;; So I have uncommented this again.  Whoever commented it out did not provide
;; an explanation.  If there is a reason not to do this I'd like to know
;; about it.  Note that I don't think we should rely on this around our
;; compilations, i.e., we should continue to let-bind it to the right thing,
;; as we've been doing.  But it just makes sense to make it be the right thing
;; in development (on Lispms, presumably), since you otherwise have an unusable
;; environment for compiling in buffer.  The alternatives would be to either
;; always use explicit notation where we write floats (e.g., 2.0d0), or to devise
;; a way to tell (z)emacs to bind this in our buffers, which it has a mechanism
;; to already for binding *package* and *read-base*. (MHD 2/5/93)
;; --- UPDATE: the story is that this has made the Explorers crash in the past
;; due to network software relying on it having its default value.  So I am
;; once again commenting it out.  (MHD 2/5/93)



;;; The following development/lucid functions enable or disable floating point
;;; traps.  `Enable-usual-floating-point-traps' turns on the default set of
;;; traps you get in a standard Lucid image.  `Enable-all-floating-point-traps'
;;; enables the entire set of supported traps.
;;; `Disable-all-floating-point-traps' makes all traps be disabled.  This makes
;;; our environment most like our production environment.  It is essential to
;;; run in this way in order to handle the IEEE exceptional numbers and NaNs
;;; that are expected to turn up as a fact of life.  Therefore, a top-level
;;; form to disable all floating-point traps is also included here.

#+(and lucid development)
(progn
  
(defun enable-usual-floating-point-traps ()
  (setf (user::enabled-floating-point-traps)
	'(user::floating-point-overflow user::floating-point-underflow
	  user::floating-point-invalid-operation user::division-by-zero)))

(defun enable-all-floating-point-traps ()
  (setf (user::enabled-floating-point-traps)
	user::supported-floating-point-conditions))

(defun disable-all-floating-point-traps ()
  (setf (user::enabled-floating-point-traps) nil))

(disable-all-floating-point-traps)

)





;;;; Systems



;;; A `system' is represented as a "normalized symbol".  A `normalized symbol'
;;; is a symbol in the "normal" package, i.e. package AB.  A `name' is a string
;;; or a symbol in any package.

;;; Normalize-name takes a name normalizes it, returning the corresponding
;;; normalized symbol.

;;; Normalize-system-name takes the name or nickname of a system and returns
;;; the corresponding "system", i.e. the normalized symbol representing that
;;; system.  Note that in order for nickname normalization to work, the system
;;; must already have been declared a system by use of declare-system.  If not
;;; using a nickname, this function is just like normalize-name.

;; Modified normalize name to leak less, preparatory to the integration of the new
;; reclaimable gensym-pathnames.  jh, 1/11/91.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar ab-package-1 (find-package "AB"))
)

(defmacro normalize-name (name-symbol-string-or-number)
  (let ((name (gensym)))
    `(let ((,name ,name-symbol-string-or-number))
       (if (and (symbolp ,name)
		(eq (symbol-package ,name) ab-package-1))
	   ,name
	   (let ((internable-string
		   (cond
		     ((symbolp ,name)
		      (symbol-name ,name))
		     ((stringp ,name)
		      ,name)
		     ,@(if (eq current-system-being-loaded 'gsi)
			   `((t "BAD GSI MODULE"))
			   `(((numberp ,name)
			      (format nil "~:@(~a~)" ,name)) ;leaks!
			     (t #+development
				(cerror
				  "Format as a string, intern, and continue"
				  "NORMALIZE-NAME: ~
                                   unexpected type in name ~s" ,name)
				(format nil "~:@(~a~)" ,name)) ;leaks!
			     )))))
	     (values (intern internable-string ab-package-1)))))))

;;; The variable `all-systems' is a list of all the symbols representing
;;; systems declared via declare-system.

(defvar all-systems nil)


(defun system-p (system-name)
  (member system-name all-systems :test #'string-or-symbol-equal))

(defun normalize-system-name (system-name)
  (declare (eliminate-for-no-macros-gsi))
  (if (system-p system-name)
      (normalize-name system-name)
      (or (get (normalize-name system-name) 'real-system-name)
	  (normalize-name system-name))))

(defmacro name-for-pathname (name)
  (case (bootstrap-information-case-of-file-type)
    (downcase `(string-downcase ,name))
    (upcase   `(string-upcase ,name))
    (t        `(string ,name))))




(defmacro file-symbol-for-module-for-symbol-argument
	  (symbol-or-string-for-module)
  `(if (symbolp ,symbol-or-string-for-module)
       ,symbol-or-string-for-module
       (intern (string-upcase ,symbol-or-string-for-module)
	       (find-package 'ab))))


(defmacro file-symbol-for-module (symbol-or-string-for-module)
  (if (symbolp symbol-or-string-for-module)
      `(file-symbol-for-module-for-symbol-argument
	 ,symbol-or-string-for-module)
      (let* ((thing (gensym)))
	`(let* ((,thing ,symbol-or-string-for-module))
	   (file-symbol-for-module-for-symbol-argument ,thing)))))





(defmacro system-alias (system)
  (let ((system-var (gensym)))
    `(let ((,system-var ,system))
       (or (get ,system-var 'system-alias)
	   ,system-var))))

(defsetf system-alias (system) (new-system-alias)
  `(setf (get ,system 'system-alias) ,new-system-alias))

(defmacro systems-to-share-binary-files-with (system)
  `(get ,system 'systems-to-share-binary-files-with))

(defmacro system-lisp-binary-type (system)
  `(get ,system 'system-lisp-binary-type))

(defmacro system-lisp-source-type (system)
  `(get ,system 'system-lisp-source-type))

(defmacro system-kb-type (system)
  `(get ,system 'system-kb-type))

(defmacro system-kl-type (system)
  `(get ,system 'system-kl-type))

(defmacro system-pathname (system)
  `(get ,system 'system-pathname))

(defmacro system-is-windowless-p (system)
  `(get ,system 'system-is-windowless-p))


;;; The macro `system-modules' gives a list of Lisp modules that are relevant to
;;; the given system, on the current platform.

(defmacro system-modules (system)
  `(get ,system 'lisp-modules-to-be-loaded))


;;; The macro `system-creation-date' gives the universal time at which boot-modules-
;;; of-system completed.  This is usually, though not always (e.g., when doing an
;;; updates-only "make"), what one would consider the "system creation date".  In G2
;;; and in Telewindows, this information gets printed out by twrite-system-version
;;; and write-system-version, although it does not get saved in G2 knowledge bases.
;;; Note that this information is stored in a saved executable image by virtue of
;;; the fact that this property of system is saved in the image.

(defmacro system-creation-date (system)
  `(get ,system 'system-creation-date))

;;; The macro `all-lisp-binary-file-symbols' gives a lisp of all Lisp binary
;;; files that are relevant to the given system on all platforms.  This
;;; includes that patch files that are maintained as binary files.

(defmacro all-lisp-binary-file-symbols (system)
  `(get ,system 'system-lisp-source-files))

;;; The function `all-lisp-source-file-symbols' returns the pruned list of all
;;; the Lisp file symbols whose sources are maintained.  This list is a subset
;;; of the list of all Lisp binary files.

(defun-for-macro all-lisp-source-file-symbols (system &optional recompute-p)
  (let* ((all-lisp-source-file-symbols nil))
    (setq all-lisp-source-file-symbols (get system 'all-lisp-source-file-symbols))
    (when (or (null all-lisp-source-file-symbols) recompute-p)
      (setq all-lisp-source-file-symbols nil)
      (dolist (file-symbol (all-lisp-binary-file-symbols system))
	(unless (get-file-property file-symbol 'system-lisp-source-files system
				   :maintained-as-a-binary-file-p)
	  (push file-symbol all-lisp-source-file-symbols)))
      (setq all-lisp-source-file-symbols (nreverse all-lisp-source-file-symbols))
      (setf (get system 'all-lisp-source-file-symbols)
	    all-lisp-source-file-symbols))
    all-lisp-source-file-symbols))


;;; The function `all-lisp-source-files' returns the pruned list of all the Lisp
;;; files whose sources are maintained.  This list is a subset of the list of all
;;; Lisp binary files.

(defun-for-macro all-lisp-source-files (system &optional recompute-p)
  (let* ((all-lisp-source-files nil))
    (setq all-lisp-source-files (get system 'all-lisp-source-files))
    (when (or (null all-lisp-source-files) recompute-p)
      (setq all-lisp-source-files nil)
      (dolist (file-symbol (all-lisp-source-file-symbols system recompute-p))
	(unless (get-file-property file-symbol 'system-lisp-source-files system
				   :maintained-as-a-binary-file-p)
	  (push (pathname (string-for-local-file-namestring
			   file-symbol 'system-lisp-source-files system))
		all-lisp-source-files)))
      (setq all-lisp-source-files (nreverse all-lisp-source-files))
      (setf (get system 'all-lisp-source-files) all-lisp-source-files))
    all-lisp-source-files))

(defmacro system-package-name (system)
  `(get ,system 'system-package-name))

(defmacro system-key-binding-function? (system)	; Set while loading the system 
  `(get ,system 'system-key-binding-function?))	;   by (caller of)
						;   define-system-access

(defmacro system-herald? (system)
  `(get ,system 'system-herald?))

(defmacro launch-function? (system)
  `(get ,system 'launch-function?))

;;; Pathname caching macros:

(defsetf module-pathname-previously-loaded? (module system) (new-value)
  `(set-file-property ,module 'system-lisp-source-files ,system
		      :module-pathname-previously-loaded? ,new-value))

(defmacro module-pathname-previously-loaded? (module system)
  `(get-file-property ,module 'system-lisp-source-files ,system
		      :module-pathname-previously-loaded?))

(defsetf distribution-module-pathname-previously-loaded? (module system) (new-value)
  `(set-file-property ,module 'system-lisp-source-files ,system
		      :distribution-module-pathname-previously-loaded?
		      ,new-value))

(defmacro distribution-module-pathname-previously-loaded? (module system)
  `(get-file-property ,module 'system-lisp-source-files ,system
		      :distribution-module-pathname-previously-loaded?))

(defsetf file-write-date-of-previously-loaded-module? (module system) (new-value)
  `(set-file-property ,module 'system-lisp-source-files ,system
		      :file-write-date-of-previously-loaded-module?
		      ,new-value))

(defmacro file-write-date-of-previously-loaded-module? (module system)
  `(get-file-property ,module 'system-lisp-source-files ,system
		      :file-write-date-of-previously-loaded-module?))


(defsetf distribution-file-write-date-of-previously-loaded-module?
	 (module system) (new-value)
  `(set-file-property ,module 'system-lisp-source-files ,system
		      :distribution-file-write-date-of-previously-loaded-module?
		      ,new-value))

(defmacro distribution-file-write-date-of-previously-loaded-module?
	  (module system)
  `(get-file-property ,module 'system-lisp-source-files ,system
		      :distribution-file-write-date-of-previously-loaded-module?))

;;; `System-version' returns the system version of the system.  If there is none,
;;; it will a system version that is 0.00.

(defmacro system-version (system)
  `(get ,system 'system-version))


(defmacro local-chestnut-development-directory (system)
  `(or (get ,system 'local-chestnut-development-directory)
       (get 'ab 'local-chestnut-development-directory)))


#-chestnut-3
(defmacro local-chestnut-macro-directory (system)
  `(or (get ,system 'local-chestnut-macro-directory)
       (get 'ab 'local-chestnut-macro-directory)))


(defmacro local-chestnut-dst-directory (system)
  `(or (get ,system 'local-chestnut-dst-directory)
       (get 'ab 'local-chestnut-dst-directory)))

(defmacro local-chestnut-dst-misc-directory (system)
  `(or (get ,system 'local-chestnut-dst-misc-directory)
       (get 'ab 'local-chestnut-dst-misc-directory)))

(defmacro local-source-directory (system)
  `(or (get ,system 'local-source-directory)
       (get 'ab 'local-source-directory)))

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)

;;; The constant `lib-objects-directory-name' can be used to change the
;;; directory the system being loaded gets its object library from, one
;;; of "opt" (optimized), "o" (debuggable), or "o-pg" (debuggable and
;;; suitable for the profiler).  By default it is "opt".  A change would
;;; typically require a recompile/reload to have an effect.

(defconstant lib-objects-directory-name "o")

#+ignore ;; DO NOT USE WIN_LIBS ANY MORE -- Chun Tian (binghe), 2011/10/09
(defconstant lib-objects-directory-name "chestnut/win_libs")

(setf (get 'ab 'local-cprim-lib-directory)
      (format nil "~a/ext/~a/" dest-directory-name lib-objects-directory-name))

(setf (get 'ab 'local-fontrip-lib-directory)
      (format nil "~a/fnt/~a/" dest-directory-name lib-objects-directory-name))
;; Added for FONTRIP module. (MHD 6/21/93)

(setf (get 'ab 'local-jpeg-lib-directory)
      (format nil "~a/jpeg/~a/" dest-directory-name lib-objects-directory-name))
;; Added JPEG library. -fmw, 12/28/01

(setf (get 'ab 'local-xml-lib-directory)
      (format nil "~a/xml/~a/" dest-directory-name lib-objects-directory-name))
;; Added XML library. -jv, 11/11/02

(setf (get 'ab 'local-ssl-lib-directory)
      (format nil "~a/openssl/~a/" dest-directory-name lib-objects-directory-name))
;; Added SSL directory. -fmw, 6/22/05

;; The local-shared-object-directory property was longstanding but unused.  It
;; used to be ext; change to lisp now.  I'm also setting the property on all
;; three major systems, just on general principle, even though the macros we use
;; to access it will default to 'ab anyway.  -jv, 12/7/07

(let ((the-local-shared-object-directory
       (format nil #-x86-64 "~a/lisp/~a/" #+x86-64 "~a/lisp/~a/x64/" 
               dest-directory-name lib-objects-directory-name)))
  (setf (get 'telewindows 'local-shared-object-directory) 
	the-local-shared-object-directory
	(get 'ab 'local-shared-object-directory) 
	the-local-shared-object-directory
	(get 'gsi 'local-shared-object-directory) 
	the-local-shared-object-directory))

#+gsi-web
(setf (get 'gsi 'local-weblink-lib-directory)
      (format nil "~a/gw/opt/" dest-directory-name))

) ; no-macros

;; jh & ac, 3/20/92.  Changed the setf of the local-cprim-lib-directory
;; property to consult source-directory-name instead of using a
;; hard-wired "ab", since each spin tree now has a different source
;; directory.



(defmacro local-cprim-lib-directory (system)
  `(or (get ,system 'local-cprim-lib-directory)
       (get 'ab 'local-cprim-lib-directory)))

(defmacro local-fontrip-lib-directory (system)
  `(or (get ,system 'local-fontrip-lib-directory)
       (get 'ab 'local-fontrip-lib-directory)))

;; Added for FONTRIP module. (MHD 6/21/93)

(defmacro local-jpeg-lib-directory (system)
  `(or (get ,system 'local-jpeg-lib-directory)
       (get 'ab 'local-jpeg-lib-directory)))
;; Added jpeg library -fmw, 12/28/01.

(defmacro local-xml-lib-directory (system)
  `(or (get ,system 'local-xml-lib-directory)
       (get 'ab 'local-xml-lib-directory)))
;; Added xml library -jv, 11/11/02

(defmacro local-ssl-lib-directory (system)
  `(or (get ,system 'local-ssl-lib-directory)
       (get 'ab 'local-ssl-lib-directory)))
;; Added ssl -fmw, 6/22/05

(defmacro local-shared-object-directory (system)
  `(or (get ,system 'local-shared-object-directory)
       (get 'ab 'local-shared-object-directory)))

#+gsi-web
(defmacro local-weblink-lib-directory (system)
  `(or (get ,system 'local-weblink-lib-directory)
       (get 'ab 'local-weblink-lib-directory)))

(defmacro local-development-binary-directory-1 (system)
  `(cond
     ((eval-feature :chestnut)
       (local-chestnut-development-directory ,system))
     ((eval-feature :chestnut-3) ;Chestnut3.1
       (local-chestnut-development-directory ,system))
     (t
       (if (eq ,system 'ab)
	   (default-ab-local-development-binary-directory)
	   (or (get ,system 'local-development-binary-directory)
	       (default-ab-local-development-binary-directory))))))

(defmacro local-development-binary-directory (system)
  ;; (local-development-binary-directory (foo))
  (if (symbolp system)
      `(local-development-binary-directory-1 ,system)
      (let* ((system-var (gensym)))
        `(let* ((,system-var ,system))
           (local-development-binary-directory-1 ,system-var)))))

(defmacro local-macro-directory-1 (system)
  ;; This handling for macro directories for Chestnut should die in
  ;; Chestnut-3, so let it fall through to the default.  -jra 9/8/93
  #+chestnut
  `(local-chestnut-macro-directory ,system)
  #-chestnut
  `(or (get ,system 'local-macro-directory)
       (get 'ab 'local-macro-directory)))

(defmacro local-macro-directory (system)
  ;; (local-macro-directory (foo))
  (if (symbolp system)
      `(local-macro-directory-1 ,system)
      (let* ((system-var (gensym)))
	`(let* ((,system-var ,system))
	   (local-macro-directory-1 ,system-var)))))

(defmacro local-dst-directory-1 (system)
  `(cond
     ((eval-feature :chestnut)
       (local-chestnut-dst-directory ,system))
     ((eval-feature :chestnut-3) ;Chestnut3.1
       (local-chestnut-dst-directory ,system))
     (t
       (or (get ,system 'local-dst-directory)
           (get 'ab 'local-dst-directory)))))

(defmacro local-dst-directory (system)
  (if (symbolp system)
      `(local-dst-directory-1 ,system)
      (let* ((system-var (gensym)))
	`(let* ((,system-var ,system))
	   (local-dst-directory-1 ,system-var)))))

(defun system-binary-pathname? (system)
  (declare (eliminate-for-no-macros-gsi))
  ;; overrides system pathname if non-nil
  (let* (pathname?)
    (setq pathname?
	  (feature-case
	    #+development
	    (:development
	      (local-development-binary-directory system))
	    (:non-development-macros
	      (local-macro-directory system))
	    (:no-macros
	      (local-dst-directory system))
	    (t nil)))
    (or pathname?
	(get system 'system-binary-pathname?)
	(get 'ab 'system-binary-pathname?))))

(defparameter null-io (make-broadcast-stream)
  "An output stream used by Boot-System as a `null device' when silent operation is needed.")

;; Should be able to do this with (make-concatenated-stream), but not
;; implemented by TI, at least.



(defvar filename-of-module-being-loaded? nil)

;;; ... If silent-p is non-nil, the special variables *standard-output* and
;;; *error-output* are bound to the value of null-io, a `null stream'.

(defvar current-module-source-filename)
(defvar current-module-lisp-binary-filename)









;;;; File Properties


;;; A `file property' is attached as a property to a module and it serves to
;;; instruct the bootstrap facility what to do with the module.
;;;
;;;	PROPERTY						DEFAULTS
;;;
;;;	:binary-file-p						nil
;;;
;;;	:local-file-p						nil
;;;
;;;	:maintained-as-a-binary-file-p				nil
;;;
;;;	:no-lisp-binary-produced-p				nil
;;;
;;;	:optional-module-p					nil
;;;
;;;	:non-lisp-compile <compile-command-format-string>	nil
;;;
;;;
;;;	:master-directory-namestring <file-pathname-string>	nil
;;;
;;;	:local-directory-namestring <file-pathname-string>	nil
;;;
;;;	:binary-directory-namestring <file-pathname-string>	nil
;;;
;;;
;;;	:master-pathname-name <pathname-name-string>		nil
;;;
;;;	:local-pathname-name <pathname-name-string>		nil
;;;
;;;	:binary-pathname-name <pathname-name-string>		nil
;;;
;;;
;;;	:master-file-type <file-type-string>			nil
;;;
;;;	:local-file-type <file-type-string>			nil
;;;
;;;	:binary-file-type <file-type-string>			nil
;;;
;;;	:default-file-type <file-type-string>			""
;;;
;;;
;;;	:updates-file-type-symbol <file-type-symbol>		nil
;;;
;;;	:lisp-load-function					nil
;;;
;;;	:lisp-compile-function					nil
;;;
;;;	:lisp-update-function					nil
;;;
;;;	:include-test-for-compile <compiler-switch>		nil
;;;
;;;	:include-test-for-load <compiler-switch>		nil
;;;
;;;	:include-test-for-update <compiler-switch>		nil
;;;
;;;	:overriding-include-test <compiler-switch>		t
;;;
;;;     :development-optional-module-p				t
;;;
;;; If :no-lisp-binary-produced-p is true (t), the lisp source file itself will
;;; be loaded.  This may be useful for debugging, or, rarely, for complex kinds
;;; of load/evaluation interactions, e.g., requiring load-time feature
;;; evaluation.  Note also that in this case the source file is loaded from the
;;; source directory, not from one of the binaries directory (e.g., dst, dev,
;;; macro).
;;;
;;; For :non-lisp-compile, the <compile-command-format-string> is used in a
;;; format string as (format nil <compile-command-format-string>
;;; pathname-directory-string pathname-name-string) to generate a string used
;;; to execute in the operating system.
;;;
;;; For include-tests, either :include-test-for-compile or
;;; :include-test-for-load have lower priority then :overriding-include-test.
;;; The function get-default-include-test-for-compile and
;;; get-default-include-test-for-load return the appropriate test form.
;;;
;;; For file-types, the procedure is the same as for include-tests.  Both
;;; :master-file-type and :local-file-type have override :default-file-type.
;;; The accessors are:  get-default-master-file-type and
;;; get-default-local-file-type.
;;;
;;; The default values for :include-test-for-compile and :include-test-for-load
;;; have to be nil, otherwise the :overriding-include-test is never used.
;;;
;;; The binary file specifications (:binary-directory-namestring,
;;; :binary-pathname-name, and :binary-file-type) might be required when
;;; compiling non-Lisp files (i.e., C).
;;;
;;; The lisp load function should take one argument - the input file pathname.
;;; The lisp compile function should take two arguments - the source file
;;; pathname and the output file pathname, in that order.

;;; The parameter `alist-of-file-property-base-defaults' is an association list
;;; of all the possible file properties (the properties of symbols which
;;; represent files) and their base default values.  There are three levels of
;;; file property specification.   The defaults here are overridden by the
;;; defaults for file classes in alist-of-system-file-class-descriptions, which
;;; are in turn overridden by those specified for the individual files in
;;; declare-system.

;;; :development-optional-module-p is only relevant if :optional-module-p is
;;; true.  :development-optional-module-p decides if the optional module is
;;; to be loaded in a development environment by default.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter-excluding-no-macros-gsi alist-of-file-property-base-defaults
	      `((:binary-file-p nil)
		(:local-file-p nil)
		(:no-lisp-binary-produced-p nil)
		(:maintained-as-a-binary-file-p nil)
		(:optional-module-p nil)
		(:non-lisp-compile nil)

		(:master-directory-namestring nil)
		(:local-directory-namestring nil)
		(:binary-directory-namestring nil)

		(:master-pathname-name nil)
		(:local-pathname-name nil)
		(:binary-pathname-name nil)

		(:master-file-type nil)
		(:local-file-type nil)
		(:binary-file-type nil)
		(:default-file-type "")

		(:updates-file-type-symbol nil)

		(:lisp-load-function nil)
		(:lisp-compile-function nil)
		(:lisp-update-function nil)

		;; Nil here means "unspecified".  Nil in declare-system means
		;; do not include.
		(:include-test-for-compile nil)
		(:include-test-for-load nil)
		(:include-test-for-update t)
		(:overriding-include-test nil)
		(:development-optional-module-p t)))
)

;;; The directory namestrings of files should default to (get system
;;; 'master-source-directory) for the master file and (get system
;;; 'local-source-directory) for the local and binary files.  Because these are
;;; system dependent values, we leave it to the accessors to handle the
;;; defaulting.




;;; The macro `all-optional-modules' ... List of all optional modules that
;;; Gensym has.

(defmacro all-optional-modules (system)
  `(get ,system 'all-optional-modules))



;;; The macro `optional-modules' ... List of optional modules present in
;;; the environment.

(defmacro optional-modules (system)
  `(get ,system 'optional-modules))


;;; The macro `module-is-present-p' ...

(defmacro module-is-present-p (module &optional (system ''ab))
  `(member ,module (optional-modules ,system)))








;;; The functions `set-file-property' and `get-file-property' are accessors to
;;; file properties.  The property value is stored in a plist indicated by the
;;; system, and this system-plist is stored in a plist indicated by the
;;; file-class, and the file-class-plist is stored as a property indicated by
;;; property-name in file-symbol.

(defun set-file-property
       (file-symbol file-class system property-name property-value)
  (declare (no-op-for-no-macros-gsi))
  (let ((file-symbol-plist (get file-symbol property-name)))
    (let ((file-class-plist (getf file-symbol-plist file-class)))
      (when (eq property-name :optional-module-p)
	(if property-value
	    (pushnew file-symbol (all-optional-modules system))
	    (setf (all-optional-modules system)
		  (string-or-symbol-delete
		    file-symbol (all-optional-modules system)))))
      (setf (getf file-class-plist system) property-value)
      (setf (getf file-symbol-plist file-class) file-class-plist)
      (setf (get file-symbol property-name) file-symbol-plist))))


(defun get-file-property (file-symbol file-class system property-name)
  (let ((file-symbol-plist (get file-symbol property-name)))
    (let ((file-class-plist (getf file-symbol-plist file-class)))
      (getf file-class-plist system))))










;;;; Get Default File Properties


;;; The macros for getting default file properties.





;;; Get-default-include-test ... Situatation-property-name should be one of
;;;
;;;   :include-test-for-compile,
;;;   :include-test-for-load, or
;;;   :include-test-for-update

(defun get-default-include-test
       (file-symbol file-class system situatation-property-name)
  (or (get-file-property
	file-symbol file-class system :overriding-include-test)
      (get-file-property
	file-symbol file-class system situatation-property-name)))

;; Defun-for-macro?!

;; Only used by callers of the following three macros. (MHD 6/3/91)





;;; The macros `get-default-include-test-for-compile',
;;; `get-default-include-test-for-load', `get-default-master-file-type' get the
;;; appropriate file properties.

(defmacro get-default-include-test-for-compile (file-symbol file-class system)
  `(get-default-include-test
     ,file-symbol ,file-class ,system :include-test-for-compile))

(defmacro get-default-include-test-for-load (file-symbol file-class system)
  `(get-default-include-test
     ,file-symbol ,file-class ,system :include-test-for-load))

(defmacro get-default-include-test-for-update (file-symbol file-class system)
  `(get-default-include-test
     ,file-symbol ,file-class ,system :include-test-for-update))

;;; The function `non-optional-or-included-optional-module-p' ...

(defun non-optional-or-included-optional-module-p
       (file-symbol file-class system)
  (or (not (get-file-property file-symbol file-class system
			      :optional-module-p))
      ;; optional-modules are set in boot-system-in-batch-mode
      (member file-symbol (optional-modules system))))

(defun-for-macro include-for-compile-p (file-symbol file-class system)
  (and (eval-feature
	 (get-default-include-test-for-compile file-symbol file-class system))
       (non-optional-or-included-optional-module-p
	 file-symbol file-class system)))

(defun include-for-load-p (file-symbol file-class system)
  (declare (eliminate-for-no-macros-gsi))
  (and (eval-feature
	 (get-default-include-test-for-load file-symbol file-class system))
       (non-optional-or-included-optional-module-p
	 file-symbol file-class system)))

#+(or remote-updates development)
(defun-for-macro include-for-update-p (file-symbol file-class system)
  (and (eval-feature
	 (get-default-include-test-for-update file-symbol file-class system))
       (non-optional-or-included-optional-module-p
	 file-symbol file-class system)))







;;; The macro `get-default-local-directory-namestring' returns a string
;;; corresponding to the pathname-name of the file of the given file-symbol.
;;; If :local-pathname-name is specified, its value is returned.  Otherwise,
;;; the appropriate string is returned.  The macros
;;; `get-default-binary-directory-namestring' and
;;; `get-default-master-directory-namestring' are the corresponding macros for
;;; local binary files and master files, respectively.  Note that on some Lisp
;;; implementations (eg. the symbolics) a directory-namestring does not end in
;;; a delimiter (">"), while on others (eg. Lucid on the Sun) they do ("/").
;;; In our context, we define our directory-namestrings to end with a
;;; delimiter.
;;;
;;; The macros `get-default-master-pathname-name',
;;; `get-default-local-pathname-name', and `get-default-binary-pathname-name'
;;; get the appropriate pathname-name (which is a string) for the corresponding
;;; files.
;;;
;;; The macros `get-default-master-file-type', `get-default-local-file-type',
;;; and `get-default-binary-file-type' get the appropriate file properties.

(defun get-default-master-directory-namestring
       (file-symbol file-class system)
  (or (get-file-property
	file-symbol file-class system
	:master-directory-namestring)
      (get system 'master-source-directory)
      (get-file-property
	file-symbol file-class 'ab
	:master-directory-namestring)
      (get 'ab 'master-source-directory)))



(defun get-default-local-directory-namestring (file-symbol file-class system)
  (or (get-file-property
	file-symbol file-class system
	:local-directory-namestring)
      (get system 'local-source-directory)
      (get-file-property
	file-symbol file-class 'ab
	:local-directory-namestring)
      (get 'ab 'local-source-directory)))


(defun choose-appropriate-binary-directory (system)
  (declare (eliminate-for-no-macros-gsi))
  (cond
    ((eval-feature :distribution)
     (local-dst-directory system))
    #+development
    (t (local-development-binary-directory system))))





(defun get-default-binary-directory-namestring
       (file-symbol file-class system)
  (declare (eliminate-for-no-macros-gsi))
  (or (get-file-property
	file-symbol file-class system
	:binary-directory-namestring)
      (choose-appropriate-binary-directory system)
      (get-file-property
	file-symbol file-class 'ab
	:binary-directory-namestring)))





(defun get-default-master-pathname-name (file-symbol file-class system)
  (or (get-file-property
	file-symbol file-class system :master-pathname-name)
      (name-for-pathname file-symbol)
      (get-file-property
	file-symbol file-class 'ab :master-pathname-name)))


(defun get-default-local-pathname-name (file-symbol file-class system)
  (or (get-file-property
	file-symbol file-class system
	:local-pathname-name)
      (name-for-pathname file-symbol)
      (get-file-property
	file-symbol file-class 'ab :local-pathname-name)))


(defun get-default-binary-pathname-name (file-symbol file-class system)
  (or (get-file-property
	file-symbol file-class system
	:binary-pathname-name)
      (get-default-local-pathname-name
	file-symbol file-class system)))





(defun get-default-master-file-type (file-symbol file-class system)
  (or (get-file-property
	file-symbol file-class system :master-file-type)
      (get-file-property
	file-symbol file-class system :default-file-type)
      ""))


(defun get-local-file-type (file-symbol file-class system)
  (or (get-file-property
	file-symbol file-class system :local-file-type)
      (get-file-property
	file-symbol file-class system :default-file-type)
      ""))


(defun get-binary-file-type (file-symbol file-class system)
   (or (get-file-property
	 file-symbol file-class system :binary-file-type)
       (get-file-property
	 file-symbol file-class system :default-file-type)
       ""))



(defun get-default-local-file-type (file-symbol file-class system)
  (if (get-file-property file-symbol file-class system
			 :maintained-as-a-binary-file-p)
      (get-binary-file-type file-symbol file-class system)
      (get-local-file-type file-symbol file-class system)))


(defun get-default-binary-file-type (file-symbol file-class system)
  (if (get-file-property file-symbol file-class system
			 :no-lisp-binary-produced-p)
      (get-local-file-type file-symbol file-class system)
      (get-binary-file-type file-symbol file-class system)))







;;; The funtion `string-for-local-file-name-and-type' returns a string
;;; containing the local file name and type of the specified file-symbol.  The
;;; functions `string-for-master-file-name-and-type' and
;;; `string-for-binary-file-name-and-type' do the same for the master file and
;;; local binary file, respectively.

;; Change to macro?
(defun string-for-file-name-and-type (pathname-name pathname-type host-type)
  (declare (eliminate-for-no-macros-gsi))
    (unless pathname-type
      (setq pathname-type ""))
    (unless (eval-feature :unix)
      (setq pathname-name (name-for-pathname pathname-name))
      (setq pathname-type (name-for-pathname pathname-type)))
    (if (and (not (equal host-type 'master))
	     (eval-feature :unix)
	     (or (null pathname-type) (equal pathname-type "")))
	(format nil "~A" pathname-name)
	(format nil "~A.~A" pathname-name pathname-type)))


;; Change to macro?
(defun string-for-master-file-name-and-type
		 (file-symbol file-class system)
  (declare (eliminate-for-no-macros-gsi))
  (string-for-file-name-and-type
    (get-default-master-pathname-name file-symbol file-class system)
    (get-default-master-file-type file-symbol file-class system)
    'master))


;; If string-for-local-file-name-and-type is ever used in places that compile
;; without macros (distribution code), then change it back into a defun, or a
;; macro.  -pto 20jan89

(defun-for-macro string-for-local-file-name-and-type
		 (file-symbol file-class system)
  (string-for-file-name-and-type
    (get-default-local-pathname-name file-symbol file-class system)
    (get-default-local-file-type file-symbol file-class system)
    'local))


;; Change to macro?
(defun string-for-binary-file-name-and-type
		 (file-symbol file-class system)
  (declare (eliminate-for-no-macros-gsi))
  (string-for-file-name-and-type
    (get-default-binary-pathname-name file-symbol file-class system)
    (get-default-binary-file-type file-symbol file-class system)
    'binary))





;;; The macros `string-for-master-file-namestring',
;;; `string-for-local-file-namestring', and `string-for-binary-file-namestring'
;;; return the namestring (without the host or version specification) of the
;;; respective files.

;;; Note that string-for-file-namestring conses strings and is used to present
;;; user menus about file names.  -jra 7/30/89

;; Change to macro
(defun string-for-file-namestring
       (directory-namestring pathname-name pathname-type host-type)
  (declare (eliminate-for-no-macros-gsi))
  (format nil
	  "~A~A"
	  directory-namestring
	  (string-for-file-name-and-type
	    pathname-name pathname-type host-type)))


;; Change to macro
(defun string-for-master-file-namestring
		 (file-symbol file-class system)
  (declare (eliminate-for-no-macros-gsi))
  (string-for-file-namestring
    (get-default-master-directory-namestring file-symbol file-class system)
    (if (eq file-symbol :wild)
	"*"
	(get-default-master-pathname-name file-symbol file-class system))
    (get-default-master-file-type file-symbol file-class system)
    'master))


;; Change to macro
(defun string-for-local-file-namestring (file-symbol file-class system)
  (declare (eliminate-for-no-macros-gsi))
  (string-for-file-namestring
    (get-default-local-directory-namestring file-symbol file-class system)
    (if (eq file-symbol :wild)
	"*"
	(get-default-local-pathname-name file-symbol file-class system))
    (get-default-local-file-type file-symbol file-class system)
    'local))


;; Change to macro
(defun string-for-binary-file-namestring (file-symbol file-class system)
  (declare (eliminate-for-no-macros-gsi))
  (string-for-file-namestring
    (get-default-binary-directory-namestring file-symbol file-class system)
    (if (eq file-symbol :wild)
	"*"
	(get-default-binary-pathname-name file-symbol file-class system))
    (get-default-binary-file-type file-symbol file-class system)
    'binary))










;;; The parameter `alist-of-system-file-class-descriptions' is just that.  A
;;; `system file class description' is a list of the form:
;;;
;;;   (<file-class-name>
;;;      <system-property-name> <alist-of-file-property-defaults>)
;;;
;;; The file-property-defaults here will override those specified in
;;; alist-of-file-property-base-defaults.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defparameter-excluding-no-macros-gsi alist-of-system-file-class-descriptions
		`(
		  (boot-files
		    boot-files
		    ((:updates-file-type-symbol boot-file)))
		  (system-lisp-binary-files
		    system-lisp-binary-files
		    ((:binary-file-p t)
		     (:local-file-p t)
		     (:default-file-type
		       ,(bootstrap-information-lisp-binary-file-type))
		     (:updates-file-type-symbol lisp-binary)
		     (:include-test-for-load t)))

		  (system-lisp-source-files
		    system-lisp-source-files
		    ((:master-file-type ,#.master-lisp-source-file-type)
		     (:default-file-type
		       ,(bootstrap-information-lisp-source-file-type))
		     (:binary-file-type
		       ,(bootstrap-information-lisp-binary-file-type))
		     (:updates-file-type-symbol lisp)
		     (:include-test-for-compile t)
		     (:include-test-for-load t)))

		  (system-c-files
		    system-c-files
		    ((:non-lisp-compile nil)
		     (:binary-file-type "o")
		     (:default-file-type "c")
		     (:updates-file-type-symbol system-c)
		     ;; This introduces spurious diffs in sandbox translates.
		     (:binary-directory-namestring "binary-directory-namestring")))

		  (distribution-c-files
		    distribution-c-files
		    ((:non-lisp-compile nil)
		     (:binary-file-type "o")
		     (:default-file-type "c")
		     (:updates-file-type-symbol c)
		     ;; This introduces spurious diffs in sandbox translates.
		     (:binary-directory-namestring "binary-directory-namestring")))

		  (h-files
		    h-files
		    ((:default-file-type "h")
		     (:updates-file-type-symbol h)))

		  (text-files
		    text-files
		    ((:updates-file-type-symbol text)))

		  (binary-files
		    binary-files
		    ((:binary-file-p t)
		     (:updates-file-type-symbol binary)))

		  (kb-files
		    kb-files
		    ((:default-file-type ,(bootstrap-information-kb-file-type))
		     (:updates-file-type-symbol kb)))

		  (kl-files
		    kl-files
		    ((:default-file-type ,(bootstrap-information-kl-file-type))
		     (:updates-file-type-symbol kl))))))




;; FCD = File-class-description.

(defmacro fcd-file-class-name (file-class-description)
  `(first ,file-class-description))


(defmacro fcd-system-property-name (file-class-description)
  `(second ,file-class-description))


(defmacro fcd-alist-of-file-property-defaults (file-class-description)
  `(third ,file-class-description))










;;;; System Versions



;;; A `system version' is a data-abstracted structure.  At present, a system
;;; version is represented as a list of the form
;;;
;;;    (major-release-number
;;;     minor-release-number
;;;     . system-version-plist).
;;;
;;; The conses that make up this structure should normally never be mutated.

;;; Both a `major release number' and a `minor release number' are a positive
;;; integers.  The minor release number is one hundredth the scale of the
;;; major release number.

;;; `System-version-greater-p' compares two system versions.  It returns true if
;;; either the major release number of system-version-1 is greater than that of
;;; system-version-2 or if the major release numbers are the same and the minor
;;; release number of system-version-1 is greater than the minor release number
;;; of system-version-2. `System-revision-greater-p' is like
;;; system-version-greater-p, but does a finer grain comparison, checking, in
;;; addition, the "release quality" and "revision".

;;; The `system-version' accessor of a system returns the system version for
;;; that system.  BOOTSTRAP expects to find on the system directory of each
;;; system a file that, when loaded, sets the value of the accessor for
;;; the system being loaded to the appropriate value.

;;; A `system version plist' ...


;;; `Make-system-version' ...
;;;
;;; The quality keyword argument should correspond to the value of one of the
;;; symbolic constants `prototype-release-quality', `alpha-release-quality',
;;; `beta-release-quality', or `release-quality'.  It effectively defaults to
;;; prototype-release-quality.
;;;
;;; The revision keyword argument should be a non-negative fixnum.  The first
;;; revision is normally 0, followed by 1, and so on.  It effectively defaults
;;; to 0.
;;;
;;; The machine-model keyword argument should be the value of evaluating
;;; (machine-model) on a one of the supported platforms.  This effectively
;;; defaults to nil
;;;
;;; It is important to fully specify a system version, i.e., by supplying
;;; quality, revision, and machine-model fully for system versions intended to
;;; actually be installed on particular systems.  Especially since they will be
;;; saved in KBs.  When system version are created for comparison with other
;;; system versions, they may want to be only partially specified.
;;;
;;; See the module DELTA for the establishment of the system version for the
;;; various systems in the Gensym product line, which is the critical use of
;;; this function

(eval-when (:compile-toplevel :load-toplevel :execute)
  ;; NB: there's no reason for these values ever to change, but if they do,
  ;; they must be kept in synch with the values in gsi_main.h  - jv, 5/30/02
(defconstant prototype-release-quality 0)
(defconstant alpha-release-quality 1)
(defconstant beta-release-quality 2)
(defconstant release-quality 3)
)

(defmacro make-system-version
    (major-release-number minor-release-number
			  &key quality revision patch machine-model)
  (macrolet ((check-constancy (arg)
	       `(unless (constantp ,arg)
		  (error "MAKE-SYSTEM-VERSION: Non-constant ~s ~s"
			 ',arg
			 ,arg))))
    (check-constancy major-release-number)
    (check-constancy minor-release-number)
    (check-constancy quality)
    (check-constancy revision)
    (let ((evaled-major-release-number (eval major-release-number))
	  (evaled-minor-release-number (eval minor-release-number))
	  (evaled-quality? (eval quality))
	  (evaled-revision? (eval revision))
	  (evaled-patch-level? (eval patch)))
      `(list
	 ,evaled-major-release-number
	 ,evaled-minor-release-number
	 ,@(if (or evaled-quality? evaled-revision?)
	       `('alpha-or-beta
		  ,(format nil "~aRev. ~d"
			   (cond
			     ((or (null evaled-quality?)
				  (= evaled-quality?
				     prototype-release-quality))
			      "Prototype ")
			     ((= evaled-quality? alpha-release-quality)
			      "Alpha ")
			     ((= evaled-quality? beta-release-quality)
			      "Beta ")
			     (t ""))
			   (if (typep evaled-revision? 'fixnum)
			       evaled-revision?
			       0)))
	       nil)
	 ,@(if evaled-patch-level?
	       `('patch-level ,evaled-patch-level?))
	 ,@(cond
	     ((equal machine-model '(machine-model))
	      `('brief-description (machine-model)))
	     ((constantp machine-model)
	      (let ((evaled-machine-model? (eval machine-model)))
		(if evaled-machine-model?
		    `('brief-description
		      ,(format nil "~a" evaled-machine-model?))
		    nil)))
	     (t (cerror "Ignore"
			"MAKE-SYSTEM-VERSION: Non-constant machine-model ~s"
			machine-model)
		nil))))))





;;; `System-version-greater-p' compares version numbers.  The minor version
;;; number is considered in the hundredth.

;;; This is the old definition of `system-version-greater-p' which compares
;;; the major, and then if necessary, the minor parts of the system-versions,
;;; treating the minor part as if it were right padded to make a two digit number.
;;; Thus "11" is less than "2" which is treated as "20."  This has been corrected
;;; as of 23 November 88 in 1.11 system software. Versions of system 1.11
;;; software distributed before this change propagates will attempt to load
;;; Version 1.2 KBs. Beware!!

(defun system-version-greater-p (system-version-1 system-version-2)
  (declare (eliminate-for-no-macros-gsi))
  (let* ((minor-version-1 (second system-version-1))
	 (minor-version-2 (second system-version-2)))
    (or (> (first system-version-1) (first system-version-2))
	(and (= (first system-version-1) (first system-version-2))
	     (> minor-version-1 minor-version-2)))))




(defmacro alpha-or-beta-of-system-version (system-version)
  `(getf (cddr ,system-version) 'alpha-or-beta))


(defmacro patch-level-of-system-version (system-version)
  `(getf (cddr ,system-version) 'patch-level))



;;; The function `system-revision-greater-p' is like system-version-greater-p,
;;; but does a finer grain comparison: it looks beyond the fact that two system
;;; version might be equal in terms of major and minor revision number to look
;;; at whether system-version-1 is greater that system-version-2 in terms of its
;;; "quality" and "revision", terms explained further below.

;;; System-revision-greater-p is intended for use later in the loading process
;;; especially while running.  It can be used while running or not, and can
;;; handle a system version containing either gensym strings or text strings.

(declare-forward-references
  (get-quality-and-revision-of-system-version function))

(defun system-revision-greater-p (system-version-1 system-version-2)
  (declare (eliminate-for-gsi))
  (or (system-version-greater-p system-version-1 system-version-2)
      (and (not (system-version-greater-p system-version-2 system-version-1))
	   (multiple-value-bind (quality-1 revision-1)
	       (get-quality-and-revision-of-system-version system-version-1)
	     (multiple-value-bind (quality-2 revision-2)
		 (get-quality-and-revision-of-system-version system-version-2)
	       (or (> quality-1 quality-2)
		   (and (= quality-1 quality-2)
			(> revision-1 revision-2))))))))


;;; The function `get-quality-and-revision-of-system-version' returns the
;;; `quality' and `revision' of system-version, as first and second values,
;;; respectively.
;;;
;;; Quality is 0 for Prototype, 1 for alpha, 2 for beta, and 3 for released.
;;;
;;; Revision is a small non-negative integer, starting at 0 and going up from
;;; there.
;;;
;;; At present, and since version 3.0, quality and revision attributes of a
;;; system version have been represented by the `revision string' that is the
;;; value of the ALPHA-OR-BETA property of plist stored in the cddr of a system
;;; version list structure.  That will likely change.
;;;
;;; This scheme depends on the following format for a revision string:
;;;
;;;    [PROTOTYPE|ALPHA|BETA|] Rev. <non-negative-integer>
;;;
;;; i.e., an optional symbol, in any letter case, one of the three shown,
;;; followed by any number of spaces, followed by the letters
;;;
;;;    R  E  V  .
;;;
;;; in any letter case, followed by a number such as 0, 1, 2, 3, etc.  Notice
;;; that a "Rev. <n>" entry is required.  Notice that the only indicator of a
;;; "released" quality is the absence of any indicator.
;;;
;;; If, for any reason, the revision string is not present, or is invalid, this
;;; returns 0 for each of the fields that are missing or invalid.
;;;
;;; The parsing of the revision string is performed by
;;; `get-quality-and-revision-of-revision-string'.  Here are some examples
;;; of how it behaves:
;;;
;;;     arg ==> return values
;;;     ---------------------
;;;     "Rev. 3"       ==> 3 3
;;;     "alpha Rev. 3" ==> 1 3
;;;     "beta Rev. 3"  ==> 2 3
;;;     "beta rev. 3"  ==> 2 3
;;;     "BETA    REV. 3" ==> 2 3
;;;     "  prototype    rev. 3" ==> 0 3
;;;     "  exquisite    rev. 1000" ==> 0 1000  (bad quality field)
;;;     "R. 1000" ==> 0 0  (bad revision and quality field)
;;;     "Beta R. 1000" ==> 2 0  (bad revision field)

(declare-forward-references
  (get-quality-and-revision-of-revision-string function)
  (text-string-p function))

(defun get-quality-and-revision-of-system-version (system-version)
  (declare (eliminate-for-gsi))
  (let ((revision-string? (alpha-or-beta-of-system-version system-version)))
    (let ((quality 0)
	  (revision 0))
      (when (or (stringp revision-string?) ; = gensym-string-p
		(text-string-p revision-string?))
	(multiple-value-setq (quality revision)
	  (get-quality-and-revision-of-revision-string revision-string?)))
      (values quality revision))))

(defmacro brief-description-of-system-version (system-version)
  `(getf (cddr ,system-version) 'brief-description))





;;; Creation-date-in-system-version ...

;;; Set-creation-date-in-system-version ...

(defmacro creation-date-in-system-version (system-version)
  `(getf (cddr ,system-version) 'creation-date))

(defmacro set-creation-date-in-system-version (system-version creation-date)
  `(setf (creation-date-in-system-version ,system-version) ,creation-date))




;;; Write-system-version ... Unfortunately, a separate parallel version of this
;;; function must be maintained in module UTILITIES3 which does the same thing
;;; but output functions appropriate for use in a twith-output-to-text-string
;;; context.  (That version is used for the system title block; this version is
;;; used for terminal output while bootstrapping.)

;;; N.b. there is also a routine that returns this information as a structure. See
;;; system-version-information-as-structure in file-sysproc. (ddm 7/21/99)

(defun write-system-version (system-version?)
  (let* ((major-number
	   (or (first system-version?) 0))
	 (minor-number
	   (or (second system-version?) 0))
	 (alpha-or-beta?
	   (alpha-or-beta-of-system-version system-version?))
	 (brief-description?
	   (brief-description-of-system-version system-version?))
	 (patch-level?
	   (patch-level-of-system-version system-version?))
;	 (system-creation-date?
;	   (creation-date-in-system-version system-version?))
	 )
    (format t "Version ~d." major-number)
    (let ((tenths
	    (floor minor-number 10))
	  (hundredths
	    (mod minor-number 10)))
      (declare (type fixnum tenths hundredths))
      (format t "~d" tenths)
      (when (/= (the fixnum hundredths) (the fixnum 0))
	(format t "~d" hundredths)))
    (when alpha-or-beta?
      (if patch-level?
	(format t " ~a~c" alpha-or-beta?
		(code-char (+ patch-level?
			      #.(1- (char-code #\a)))))
	(format t " ~a" alpha-or-beta?)))
     (when brief-description?
       (format t "~a" brief-description?))))


;; Document the "brief-description" property!!

;; Consider having this (or another function) just print the number.

;; Consider having a long and short version of this.

;; Consider printing certain extra information (from the system version plist).

;; Consider having extra arguments to make some of the features mentioned above
;; optionally available.


;;; Write-system-version-to-string ...

(defun write-system-version-to-string (system-version)
  (declare (eliminate-for-no-macros-gsi))
  (with-output-to-string (*standard-output*)
    (write-system-version system-version)))




;;; Set-system-version sets the version of system to system-version.  The
;;; system-version argument is typically created by calling make-system-version,
;;; q.v.

(defun set-system-version (system system-version)
  #+development
  (when (and (system-version system)
	     (or (system-version-greater-p
		   system-version (system-version system))
		 (system-version-greater-p
		   (system-version system) system-version)))
    (cerror "Continue, ignoring this problem at one's own risk."
	    "Cannot load ~a ~a. ~a is now loaded.~%~9TThey ~
               are NOT the same version, and are probably not ~
               compatible."
	    (system-alias system)
	    (with-output-to-string (*standard-output*)
	      (write-system-version system-version))
	    (with-output-to-string (*standard-output*)
	      (write-system-version (system-version system)))))

  (setf (system-version system) system-version))


(defun get-system-major-version (system)
  (first (system-version system)))

(defun get-system-minor-version (system)
  (second (system-version system)))






;;;; Compiling for Distribution


;;; If possible, `open-editor-stream-or-bitsink' opens an editor buffer whose
;;; name is namestring and returns a stream with output to it and a second value
;;; of T; otherwise it returns a "bitsink" stream and a second value of nil.
;;; The caller may, but need not, close the stream when done.  This is useful
;;; for implementing log or dribble files, especially if they are in addition to
;;; a disk file or if they are not essential.  This may cons and should not be
;;; used in the product, but only by development code.

;;; At present, this returns a real editor stream only on TI and Symbolics.  The
;;; function `supports-editor-stream-p' returns whether or not this function
;;; will return anything but a bitsink.

(defun open-editor-stream-or-bitsink (namestring)
  (declare (ignore namestring))
  (values
    (make-broadcast-stream)
    nil))

(defun supports-editor-stream-p ()
  nil)



(defun check-last-bootstrap-mode
       (pathname-for-distribution-binaries?
	pathname-for-non-distribution-binaries?)
  (declare (eliminate-for-no-macros-gsi))
  (when last-bootstrap-mode?
    (when (or (not (equal pathname-for-distribution-binaries?
			  (first last-bootstrap-mode?)))
	      (not (equal pathname-for-non-distribution-binaries?
			  (second last-bootstrap-mode?))))
      (cerror "Proceed in spite of great risk."
	      "Attempt to compile in a different mode than before:
Before:
  Distribution Pathname: ~s
  Macro Pathname: ~s
Now:
  Distribution Pathname: ~s
  Macro Pathname: ~s"
	      (or (first last-bootstrap-mode?) "none")
	      (or (second last-bootstrap-mode?) "none")
	      (or pathname-for-distribution-binaries? "none")
	      (or pathname-for-non-distribution-binaries? "none"))))
  (setq last-bootstrap-mode?
	(list 
	  pathname-for-distribution-binaries?
	  pathname-for-non-distribution-binaries?)))



#-translator
(defun write-time-stamp (&optional universal-time?)
  (multiple-value-bind (second minute hour date month year
			day-of-the-week daylight-savings-time-p
			time-zone)
      (decode-universal-time (or universal-time? (get-universal-time)))
    (declare
      (ignore day-of-the-week daylight-savings-time-p time-zone))
    (format t 
	    ;; e.g. "10 Dec 86  8:05:19"
	    #-chestnut-trans
	    "~2,' d ~a ~2,'0d  ~d:~2,'0d:~2,'0d"
	    #+chestnut-trans
	    "~%[~d ~a ~d ~d:~a~d:~a~d]"
	    date
	    (nth (- month 1)
		 '("Jan" "Feb" "Mar" "Apr" "May" "Jun"
		   "Jul" "Aug" "Sep" "Oct" "Nov" "Dec"))
	    year
	    hour
	    #+chestnut-trans
	    (if (< minute 10) "0" "")
	    minute
	    #+chestnut-trans
	    (if (< second 10) "0" "")
	    second)))

;;; The macro `with-faster-standard-output' somewhat improves the speed of
;;; printing that goes to standard output by enabling output buffering on those
;;; systems that have it.  For example, this helps the interaction between Lucid
;;; and an Emacs displaying the output of that Lucid by limiting the process
;;; switching between the two.  This helps with the "stuck emacs" problem, when
;;; lots of little updates keep making emacs defer updating the screen, instead
;;; of having fewer large updates that emacs can actually catch up with.  By
;;; default in Lucid, every function that writes to *standard-output*
;;; immediately flushes it out to the user.

(defmacro with-faster-standard-output (&body forms)
  #+lucid
  (if (not (eval-feature 'translator))
      `(lcl:with-buffered-terminal-output (*standard-output*)
	 ,@forms)
      `(progn ,@forms))
  #-lucid
  `(progn ,@forms))

;;;; Platform and Operating System Type

;; ac & jh, 7/29/91.  Added g2-operating-system and g2-machine-type as
;; central places to do runtime checks for a specific operating system
;; or for a specific machine type.  All other ways of doing such checks
;; (e.g., eval-feature, checking *features*, etc.) should not be used.

;; jh, 8/17/93.  Added c-get-platform-code to PLATFORMS, which calls out to the
;; operating system to get a unique fixnum that designates the platfrom on which
;; this image is running.  To add a new platform, go to the definition of
;; cc_get_platform_code() in /bt/ab/ext/c/cprim.c and follow the instructions
;; there.  Then, back here in BOOTSTRAP, copy the new #define into the
;; defconstant section below, and add a new clause in the the initform for
;; g2-operating-system and g2-machine-type below.  This mechanism is designed to
;; replace the ad hoc definition of push_runtime_features() in g2main.c.  There
;; is no reason why we can`t initialize g2-operating-system and g2-machine-type
;; the way we do other defvars.

;; The following defconstants are taken from cprim.c, just above the
;; definition of cc_get_platform_code().

(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant i386-code         1)
(defconstant dos-code          2)
(defconstant aviion-code       3)
(defconstant sgi-code          4)
(defconstant sequent-code      5)
(defconstant next-code         6)
(defconstant decstation-code   7)
(defconstant masscomp-code     8)
(defconstant hp9000s300-code   9)
(defconstant hp9000s400-code  10)
(defconstant hp9000s700-code  11)
(defconstant hp9000s800-code  12)
(defconstant rs6000-code      13)
(defconstant sun3-code        14)
(defconstant sun4-code        15)
(defconstant sparcsol-code    16)
(defconstant alphavms-code    17)
(defconstant motorola-code    18)
(defconstant vms-code         19)
(defconstant stratus-code     20)
(defconstant harris-code      21)
(defconstant nec-code         22)
(defconstant alphaosf-code    23)
(defconstant alphant-code     24)
(defconstant intelnt-code     25)
(defconstant ncr-code         26)
(defconstant windows95-code   27)
(defconstant linux-code       28)
(defconstant mac-code         29)
(defconstant hpia-code        30)
(defconstant intelsol-code    31)
)

(declare-forward-reference c-get-platform-code function) ;PLATFORMS

(defvar g2-operating-system
  #+chestnut-trans
  (let ((platform-code (c-get-platform-code)))
    (case platform-code
      (#.i386-code         'unix)
      (#.dos-code          'dos)
      (#.aviion-code       'unix)
      (#.sgi-code          'unix)
      (#.sequent-code      'unix)
      (#.next-code         'unix)
      (#.decstation-code   'unix)
      (#.masscomp-code     'unix)
      (#.hp9000s300-code   'unix)
      (#.hp9000s400-code   'unix)
      (#.hp9000s700-code   'unix)
      (#.hp9000s800-code   'unix)
      (#.rs6000-code       'unix)
      (#.sun3-code         'unix)
      (#.sun4-code         'unix)
      (#.sparcsol-code     'unix)
      (#.intelsol-code     'unix)
      (#.alphavms-code     'vms)
      (#.motorola-code     'unix)
      (#.vms-code          'vms)
      (#.stratus-code      'unix)
      (#.harris-code       'unix)
      (#.nec-code          'unix)
      (#.alphaosf-code     'unix)
      (#.alphant-code      'win32)
      (#.intelnt-code      'win32)
      (#.ncr-code          'unix)
      (#.windows95-code    'win32)
      (#.linux-code        'unix)
      (#.mac-code          'unix)
      (#.hpia-code         'unix)

      ;; jh per jra, 8/26/93.  Made the "otherwise" clause more forgiving for
      ;; new ports.  Instead of an error, we assume that all new ports will be
      ;; to UNIX boxes.
      (otherwise
       (format t "Unknown platform code ~a, assuming UNIX o/s" platform-code)
       'unix)))
  #-chestnut-trans
  (feature-case
    (:solaris 'unix)
    (:sunos-but-not-solaris 'unix)
    (:linux 'unix)
    (:mswindows 'win32)
    (t 'unknown-development-os))
  )

(defvar g2-machine-type
  #+chestnut-trans
  (let ((platform-code (c-get-platform-code)))
    (case platform-code
      (#.i386-code         'i386)
      (#.dos-code          'dos)
      (#.aviion-code       'aviion)
      (#.sgi-code          'sgi)
      (#.sequent-code      'sequent)
      (#.next-code         'next)
      (#.decstation-code   'decstation)
      (#.masscomp-code     'masscomp)
      (#.hp9000s300-code   'hp9000s300)
      (#.hp9000s400-code   'hp9000s400)
      (#.hp9000s700-code   'hp9000s700)
      (#.hp9000s800-code   'hp9000s800)
      (#.rs6000-code       'rs6000)
      (#.sun3-code         'sun3)
      (#.sun4-code         'sparcstation)
      (#.sparcsol-code     'sparcsol)
      (#.intelsol-code     'intelsol)
      (#.alphavms-code     'alphavms)
      (#.motorola-code     'motorola)
      (#.vms-code          'vms)
      (#.stratus-code      'stratus)
      (#.harris-code       'harris)
      (#.nec-code          'nec)
      (#.alphaosf-code     'alphaosf)
      (#.alphant-code      'alphant)
      (#.intelnt-code      'intelnt)
      (#.ncr-code          'ncr)
      (#.windows95-code    'windows95)
      (#.linux-code        'linux)
      (#.mac-code          'mac)
      (#.hpia-code         'hpia64)
      ;; jh per jra, 8/26/93.  Made the "otherwise" clause more forgiving for
      ;; new ports.  Instead of an error, we return a special symbol.
      (otherwise           'experimental-port)))
  #-chestnut-trans
  (feature-case
    (:solaris 'sparcsol)
    (:sunos-but-not-solaris 'sparcstation)
    (:mswindows 'intelnt)
    (t 'unknown-development-machine-type))
  )

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar machine-model-var nil)
(defun machine-model ()
  (if machine-model-var
      machine-model-var
      (setq machine-model-var
	    #+chestnut-trans
	    (case g2-machine-type
	      (aviion " Data General AViiON")
	      (motorola " Motorola 88000")
	      (next " NeXT")
	      (sgi " Silicon Graphics")
	      (sequent " Sequent")
	      (decstation " DECstation")
	      (masscomp " Concurrent 6000s")
	      (hp9000s300 " HP9000/300s")
	      (hp9000s400 " HP9000/400s")
	      (hp9000s700 " PA-RISC HP-UX")
	      ;; jv/mes, 11/17/99 - change HP700 to be more generic for 6.0.
	      ;;   Other HPs should never be used again.
	      ;; jv, 4/6/07.  Well, who can predict the future?  All of a
	      ;;   sudden, we have another HP platform, the Itanium.  Change
	      ;;   the identifier to now say PA-RISC.
	      (hp9000s800 " HP9000/800s")
	      ((i386 compaq) " '386") ;jh, 12/18/92.  Added i386.
	      (rs6000 " IBM POWERstation")
	      (sun3 " Sun 3")
	      (vms " Vax VMS")
	      (alphavms " DEC Alpha AXP/OpenVMS")
	      (sparcsol " Sun 4/SPARCstation Solaris")
	      (intelsol " x86 Solaris")
	      (sun4 " Sun 4/SPARCstation")
	      (harris " Harris Night Hawk")
	      (stratus " Stratus FTX")
	      (nec " NEC EWS4800 Series")
	      (alphaosf " DEC OSF/1 AXP")
	      (alphant  " Alpha NT")
	      (intelnt  " Windows")
	      (dos " MS Windows 3.1")
	      (ncr " NCR 386/486")
	      (windows95 " Windows 95/98")
	      (linux " Linux")
	      (mac " Mac OS X")
	      (hpia64 " Itanium HP-UX")
	      ;; jh per jra & mes, 8/26/93.  Made the "otherwise" clause more
	      ;; articulate for new ports.  The wording may be changed, but
	      ;; should produce a title block that will discourage illicit use
	      ;; of unreleased G2 ports.
	      (otherwise " Experimental Port"))
	    #-chestnut-trans
	    (feature-case
	      (:solaris " Sun 4/SPARCstation Solaris")
	      (:sunos-but-not-solaris " Sun 4/SPARCstation")
	      (:linux " Linux")
	      (:darwin " Mac OS X")
	      (:mswindows " Windows")
	      (t " Unknown Development Platform")))))
)

;; jh, 7/20/93.  Modified the function machine-model to work without the
;; variable g2-machine-type in non-Chestnut environments like Lucid development.
;; The function machine-model is called in SYSTEMS, and at that point the
;; variable g2-machine-type is only defined for images translated by Chestnut
;; (which are linked with main.c, which defines G2_machine_type, the C
;; corresponding global variable).  This problem surfaced because we upped the
;; safety setting for Lucid devlopment compiles, so references to the unbound
;; g2-machine-type signaled an error.





;;; The platform-specific directory contains pre-built object files and
;;; libraries that have been checked into CVS, as opposed to those produced by
;;; the build process, so it's relative to the source directory rather than the
;;; destination directory.  Each platform has its own subdirectory.

(setf (get 'ab 'local-platform-specific-directory)
      #+(or unix mswindows)
      (format nil "~a/specific/~(~a~)/" source-directory-name g2-machine-type)
      #-(or unix mswindows)
      nil)

(defmacro local-platform-specific-directory (system)
  `(or (get ,system 'local-platform-specific-directory)
       (get 'ab 'local-platform-specific-directory)))

;;; The function `make-system-pathname' ... If file-class? is nil, assume that
;;; defaults in file property lists are not to be used.  If type? is nil, and
;;; file-class? is non-nil, the file-property for type is used, using the
;;; specified (or defaulted) option of local-or-binary.

(defun-allowing-lisp-pathnames make-system-pathname
    (system-name
      file-symbol-or-string
      overriding-file-type?
      version? &optional
      (override-pathname? nil)
      (file-class? 'system-lisp-source-files)
      (local-or-binary 'local))
  (declare (eliminate-for-no-macros-gsi))
  (let* ((system (normalize-name system-name))
	 (file-symbol (file-symbol-for-module file-symbol-or-string))
	 (defaults
	     (let* ((namestring
		      (case local-or-binary
			(local (string-for-local-file-namestring
				 file-symbol file-class? system))
			(binary (string-for-binary-file-namestring
				  file-symbol file-class? system)))))
	       (if (and file-class?
			namestring
			(not (equal namestring "")))
		   (pathname namestring)
		   (system-pathname system))))
	 (name
	   (if (eq file-symbol :wild)
	       :wild
	       (if file-class?
		   (case local-or-binary
		     (local (get-default-local-pathname-name
			      file-symbol file-class? system))
		     (binary (get-default-binary-pathname-name
			       file-symbol file-class? system)))
		   (name-for-pathname file-symbol))))
	 (type
	   (if (equal overriding-file-type? :wild)
		       :wild
		       (if (and (null overriding-file-type?) file-class?)
			   (case local-or-binary
			     (local (get-default-local-file-type
				      file-symbol file-class? system))
			     (binary (get-default-binary-file-type
				       file-symbol file-class? system)))
			   (name-for-pathname overriding-file-type?))))
	 (system-pathname
	   (if (and version?
		    (bootstrap-information-version-numbers-available-p))
	       (make-pathname
		 :defaults defaults
		 :name name
		 :type type
		 :version version?)
	       (make-pathname
		 :defaults defaults
		 :name name
		 :type type))))
    (if override-pathname?
	(make-pathname
	  :defaults override-pathname?
	  :name (or (pathname-name system-pathname)
		    (and (not (eq (pathname-name override-pathname?) :wild))
			 (pathname-name override-pathname?)))
	  :type (or (pathname-type system-pathname)
		    (and (not (eq (pathname-type override-pathname?) :wild))
			 (pathname-type override-pathname?)))
	  :directory
	  (or (pathname-directory override-pathname?)
	      (pathname-directory system-pathname))
	  :host (or (pathname-host override-pathname?)	;part of pathname
		    (pathname-host system-pathname))
	  :version (or (if (numberp (pathname-version override-pathname?))
			   (pathname-version override-pathname?))
		       (pathname-version system-pathname)))
	system-pathname)))






;;;The macro `make-system-c-file-object-namestring' ...

(defun make-system-c-file-object-namestring
       (file-symbol-or-string &optional system-name)
  (declare (eliminate-for-no-macros-gsi))
  (string-for-binary-file-namestring
    (file-symbol-for-module file-symbol-or-string)
    'system-c-files
    (or (normalize-name system-name) 'ab)))



;;; The function `make-system-c-file-object-pathname' returns the pathname of
;;; the C object file corresponding to the system-c-file.

(defun-for-macro make-system-c-file-object-pathname
		 (file-symbol-or-string &optional (system-name 'ab))
  (pathname (make-system-c-file-object-namestring
	      file-symbol-or-string system-name)))









;;; Make-module-filename ... Pathname-type can be one of the symbols binary,
;;; source, or kb.  It defaults to binary.

(defun-allowing-lisp-pathnames make-module-filename
    (module
      system
      &optional (pathname-type 'binary)
      (override-pathname? nil))
  (declare (eliminate-for-no-macros-gsi))
  (let ((type (normalize-name pathname-type)))
    (make-system-pathname
      system module
      ;; Abstract ecase below!!!  Use file properties.  -pto 27dec88.   But watch
      ;; out for calls to this function in other modules (eg. SITE).  -pto
      ;; 04jan89.  Many other modules use this function.  Be careful how it is
      ;; abstracted.  -pto 10jan89
      (case (normalize-name pathname-type)
	(binary (system-lisp-binary-type system))
	(source (system-lisp-source-type system))
	(kb (system-kb-type system))
	(kl (system-kl-type system))
	(c 'c)
	(h 'h)
	(t
	 (error "Bad type ~a in make-module-filename" type)))
      :newest
      override-pathname?)))







(defun-for-macro development-compile-cerror ()
  (cerror
    "Continue and do the development compile."
    "You are about to do a development compile on distribution ~
     software.  Please be sure you want to do this."
    ))





;;; The macro `delete-feature' ...

(defmacro delete-feature (feature)
  `(setq *features* (string-or-symbol-delete ,feature *features*)))

(defvar do-not-load-modules-p)

;;; Boot-system ... returns non-nil if it finished without aborting (indicating
;;; success) and nil otherwise.

#-no-macros
(defparameter features-only-relevant-to-non-macro-environments
	      '(:no-macros
		 :translator
		 :chestnut-trans
		 :do-not-load-bootstrap))

(defvar making-distribution-system? #-distribution nil #+distribution t)

#-translator
(defun-allowing-unwind boot-system
		       (system-name		       ;1
			 compile-p		       ;2
			 verbose-p		       ;3
			 recompile-p		       ;4
			 reload-p		       ;5
			 no-process-p		       ;6
			 reload-load-file-p	       ;7
			 silent-p		       ;8
			 pathname-for-distribution-binaries?   ;9
			 from-module?		       ;10
			 to-module?		       ;11
			 pathname-for-non-distribution-binaries?       ;12
			 log-filename?		       ;13
			 no-autolog?		       ;14
			 no-updates-p		       ;15
			 update-only-p		       ;16
			 no-gc-messages?	       ;17
			 update-all-master-files-p     ;18
			 macros-only-p		       ;19
			 no-make-p		       ;20
			 no-delete-p		       ;21
			 command-line?	               ;22
			 launch-only?	               ;23
			 prepare-only-p                ;24
			 analyze-calls-p               ;25
			 &aux (system (normalize-system-name system-name))
		         #+(and lucid (not translator))
		         (old-gc-silence sys::*gc-silence*)
			 (finished-without-aborting? nil))
  #-(and lucid (not translator))
  (declare (ignore no-gc-messages?
		   #-(or allegro lispworks sbcl clozure) no-make-p))
  #+(and lucid (not translator))
  (setq sys::*gc-silence* no-gc-messages?)
  (check-last-bootstrap-mode pathname-for-distribution-binaries?
			     pathname-for-non-distribution-binaries?)

  ;; Get rid of features that can't possibly be in an environment with macros
  #-no-macros
  (when (or compile-p recompile-p)
    (dolist (feature features-only-relevant-to-non-macro-environments)
      (delete-feature feature)))
  #-no-macros
  (when (or compile-p recompile-p)
    (initialize-macro-statistics))
  (catch 'aborted
    (let ((open-output-stream? nil))
      (unwind-protect			; unwind-protect-2
	   (let ((*standard-output* *standard-output*)
		 (*error-output* *error-output*))
	     (if log-filename?
		 (setq open-output-stream?
		       (open
			 (make-pathname
			   :defaults log-filename?
			   :name (or (pathname-name log-filename?) "log")
			   :type (or (pathname-type log-filename?) "text")
			   :version :newest)
			 :direction :output)
		       *standard-output*
		       (make-broadcast-stream
			 *standard-output* open-output-stream?
			 (open-editor-stream-or-bitsink
			   (namestring open-output-stream?)))
		       *error-output* *standard-output*)
		 (if (and compile-p (not no-autolog?)
			  (supports-editor-stream-p))
		     (setq *standard-output*
			   (make-broadcast-stream
			     *standard-output*
			     (open-editor-stream-or-bitsink
			       (format nil "~a Compilation Log" system))))))
	     (let ((source-directory-pathname ; only for Lisp sources
		     (make-system-pathname
		       system :wild (system-lisp-source-type system) :newest))
		   (binary-directory-pathname ; only for Lisp binaries
		     (make-system-pathname
		       system
		       :wild
		       (system-lisp-binary-type system)
		       :newest
		       (or pathname-for-non-distribution-binaries?
			   (if macros-only-p
			       (local-macro-directory system)
			       (system-binary-pathname? system))))))
	       (cond
		 ((not silent-p)
		  (cond
		    ((system-version system) ; just to be safe
		     (format t "~%~:[Loading~;Compiling~] ~a ~a~%"
			     compile-p
			     (system-alias system)
			     (write-system-version-to-string
			       (system-version system)))))
					; (terpri)
		  (write-time-stamp)
		  (terpri)))
	       #-(or no-macros lispworks)
	       (check-for-aborts-while-bootstrapping system compile-p)
	       #-translator
	       (setq current-system-being-loaded system)
	       ;; Bind special variables.
	       (let* ((*package*
			(or (find-package (system-package-name system))
			    *package*))
		      (*read-default-float-format*
			(gensym-float-type))
		      (*standard-output*
			(if silent-p null-io *standard-output*))
		      (*error-output*
			(if silent-p null-io *error-output*))
		      (binary-directory-pathname-to-use
			(if pathname-for-non-distribution-binaries?
			    (make-pathname
			      :defaults pathname-for-non-distribution-binaries?
			      :name :wild
			      :type (system-lisp-binary-type system)

			      :version :newest) ; without this, use of directory
					;   lists for bootstrapping on
					;   SMBX was broken! (MHD/PTO)

			    binary-directory-pathname))
		      ;; These are the default values for these variables.
		      #+(and lucid (not translator))
		      (lcl:*record-source-files* t)
		      #+(and lucid (not translator))
		      (lcl:*redefinition-action* :warn)

		      (use-directory-lists-for-bootstrapping?
			(and (bootstrap-information-use-directory-function-p)
			     (progn
			       #+no-macros
			       t
			       #-no-macros
			       (use-dates-instead-of-versions-p))))
		      (current-directory-of-source-truenames?
			(if (and compile-p
				 use-directory-lists-for-bootstrapping?)
			    (progn
			      (if (not silent-p)
				  (format
				    t "Source directory: ~s~%"
				    (namestring source-directory-pathname)))
			      (new-directory-for-bootstrap
				(make-pathname
				  :defaults source-directory-pathname
				  :version :newest)))))
		      (current-directory-of-binary-truenames
			(if use-directory-lists-for-bootstrapping?
			    (progn
			      #-(or no-macros lispworks)
			      (check-for-aborts-while-bootstrapping
				system compile-p)
			      (if (not silent-p)
				  (format
				    t "Binary directory: ~s~%"
				    (namestring
				      binary-directory-pathname-to-use)))
			      (nconc
				;; This will need fixing if the the assumption
				;;   of only needing the Lisp LOAD source plus
				;;   all the Lisp binaries becomes invalid.
				;; (Getting the entire
				;;   directory should always be safe, but is
				;;   too slow in practice.) (MHD 3/6/89)
				(new-directory-for-bootstrap
				  (make-pathname
				    :defaults binary-directory-pathname-to-use
				    :version :newest))
				(new-directory-for-bootstrap
				  (make-pathname
				    :defaults binary-directory-pathname-to-use
				    :name :wild
				    :type (system-lisp-source-type system)
				    :version :newest))))))
		      (current-system-being-loaded system))
		 (unless launch-only?
		   (do-bootstrapping-preview-if-possible
		       system binary-directory-pathname-to-use compile-p)
		   (if pathname-for-distribution-binaries?
		       (delete-feature :development)
		       (progn
			 #-no-macros
			 (when (and compile-p
				    (not update-only-p)
				    (not macros-only-p)
				    (eval-feature :development)
				    (not allow-development-compile-p))
			   #-no-macros
			   (development-compile-cerror))))

		   #+(and (not no-macros) remote-updates)
		   (setq module-version-plist nil)
		   #+(and (not no-macros) remote-updates)
		   (setq updates-file-pathname
			 (make-system-pathname
			   system 'updates
			   (bootstrap-information-lisp-source-file-type)
			   :newest nil nil 'local))

		   #+(and (not no-macros) remote-updates)
		   (if (and compile-p (or update-only-p (not no-updates-p)))
		       (let ((truename? (probe-file updates-file-pathname)))
			 (if truename?
			     (load truename?)
			     (format t "~%No updates file yet.~%"))
			 (if (not (boundp 'module-version-plist))
			     (setq module-version-plist nil))))
		   (cond
		     (reload-load-file-p
		      #-(or no-macros lispworks)
		      (check-for-aborts-while-bootstrapping system compile-p)
		      (load (make-pathname
			      :defaults (system-pathname system)
			      :name (name-for-pathname "LOAD")
			      :type (system-lisp-source-type system))
			    :verbose (and (not silent-p) verbose-p))))


		   (when (and (not (eval-feature :development))
			      (not (eval-feature :no-macros)))
		     (pushnew :non-development-macros *features*))


		   (let* ((making-distribution-system?
			    (not (not (eval-feature :distribution)))))
		     (boot-all-modules-of-system
		       system
		       compile-p
		       verbose-p
		       recompile-p
		       reload-p
		       silent-p
		       from-module?
		       to-module?
		       binary-directory-pathname-to-use
		       no-updates-p
		       update-only-p
		       update-all-master-files-p
		       no-make-p
		       no-delete-p
		       prepare-only-p
		       analyze-calls-p))

		   (if (and pathname-for-distribution-binaries?
			    (not macros-only-p))
		       (let ((*features* (copy-list *features*))
			     (making-distribution-system? t)
			     (do-not-load-modules-p t)
			     (binary-directory-pathname-to-use
			       (make-pathname
				 :defaults pathname-for-distribution-binaries?
				 :name :wild
				 :type (system-lisp-binary-type system)
				 :version :newest)))
			 ;; This is the only place where we bind *features*.  It is required
			 ;; because :no-macros should not be in *features* if the
			 ;; compile is aborted or when it ends (because it would be a
			 ;; macros environment at that point; do-not-load-modules-p is set,
			 ;; so :no-macro modules are not loaded).

			 (delete-feature :development)

			 #-no-macros
			 (pushnew :do-not-load-bootstrap *features*)
			 ;; The above is to prevent the BOOTSTRAP module compiled
			 ;; for distribution from overriding the
			 ;; development BOOTSTRAP, which is capable of pulling in
			 ;; files from the master directory.  This *features*
			 ;; attribute should only be set here, and no where else;
			 ;; :do-not-load-bootstrap should not be saved out as a
			 ;; *features* attribute in any compilations.  -pto
			 ;; 23jan89

			 (pushnew :no-macros *features*)

			 #+(and (or chestnut chestnut-3) (not no-macros)) ;Chestnut3.1
			 (progn
			   (pushnew :chestnut-trans *features*)
			   (pushnew :translator *features*)
			   #+(and (or chestnut chestnut-3) incremental-trans) ;Chestnut3.1
			   (set-up-chestnut-incremental-translations system))

			 (if use-directory-lists-for-bootstrapping?
			     (setq current-directory-of-binary-truenames
				   (progn
				     #-(or no-macros lispworks)
				     (check-for-aborts-while-bootstrapping
				       system compile-p)
				     (if (not silent-p)
					 (format
					   t "Distribution binary directory: ~s~%"
					   (namestring 
					     binary-directory-pathname-to-use)))
				     (nconc
				       ;; This will need fixing if the the assumption
				       ;;   of only needing the Lisp LOAD source plus
				       ;;   all the Lisp binaries becomes invalid.
				       ;; (Getting the entire
				       ;;   directory should always be safe, but is
				       ;;   too slow in practice.) (MHD 3/6/89)
				       (new-directory-for-bootstrap
					 (make-pathname
					   :defaults binary-directory-pathname-to-use
					   :version :newest))
				       (new-directory-for-bootstrap
					 (make-pathname
					   :defaults binary-directory-pathname-to-use
					   :name :wild
					   :type (system-lisp-source-type system)
					   :version :newest))))))
			 (delete-feature :non-development-macros)

			 (boot-all-modules-of-system
			   system
			   compile-p
			   verbose-p
			   recompile-p
			   reload-p
			   silent-p
			   from-module?
			   to-module?
			   binary-directory-pathname-to-use
			   t
			   nil
			   update-all-master-files-p
			   no-make-p
			   no-delete-p
			   prepare-only-p
			   analyze-calls-p)

			 #-no-macros
			 (dolist
			     (feature
			       features-only-relevant-to-non-macro-environments)
			   (delete-feature feature)))))
					; ok? maybe not reasonable to
					; get things not gotten on
					; 1st pass ever!
		 (when (system-key-binding-function? system)
		   (ab-lisp::funcall
		     (system-key-binding-function? system) system))
		 (when command-line?
		   (if (fboundp 'replace-command-line)
		       (ab-lisp::funcall 'replace-command-line command-line?)
		       (warn
			 "Ignore 'command-line, replace-command-line undefined."
		      )))
		 (unless no-process-p
		   (launch-system system)))))
	(when open-output-stream?
	  (close open-output-stream?)));; end of unwind-protect-2
      (setq finished-without-aborting? t)))

  #+(and lucid (not translator))
  (setq sys::*gc-silence* old-gc-silence)

  finished-without-aborting?)			; return value


;;; The variable `last-update-of-bootstrap-compiled-p' ...

#-no-macros
(defvar last-update-of-bootstrap-compiled-p nil)

#-no-macros
(defvar all-binaries-were-deleted-before-recompile-p nil)

(declare-forward-reference translate-all-modules-in-system function)

;;; The function `boot-all-modules-of-system' ...

#-translator
(defun boot-all-modules-of-system
    (system
     compile-p
     verbose-p
     recompile-p
     reload-p
     silent-p
     from-module?
     to-module?
     pathname-for-binaries?
     no-updates-p
     update-only-p
     update-all-master-files-p
     no-make-p
     no-delete-p; true => doesn't delete all binaries on recompile
     prepare-only-p
     analyze-calls-p)

  #+no-macros
  (declare (ignore no-delete-p))

  #-remote-updates
  (declare (ignore update-all-master-files-p))

  #-(and (or chestnut chestnut-3) (not incremental-trans)) ;Chestnut3.1
  (declare (ignore prepare-only-p analyze-calls-p))

  no-updates-p                                ; maybe not used

  (when (and (not (eval-feature :development))
	     (eval-feature :no-macros))
    (pushnew :distribution *features*))

  ;; Ephemeral Garbage Collection for Lucid 3.0
  #+(and lucid (not (or chestnut chestnut-3))) ;Chestnut3.1
  (lcl::compiler-options :egc (eval-feature :using-egc))

  #-no-macros
  (setq last-update-of-bootstrap-compiled-p nil)

  ;; create needed directory automatically
  (cl:ensure-directories-exist
   (ab-lisp::make-pathname :type nil :name nil
                           :defaults pathname-for-binaries?))

  (let ((file-class 'system-lisp-source-files)
	(reboot-all-modules-p nil)
	(reupdate-all-modules-p nil))

    ;; Delete files if a recompile is asked for:
    ;; (This must not be within the boot-all-modules loop.)
    #-no-macros
    (when (setq all-binaries-were-deleted-before-recompile-p
		(and recompile-p (not no-delete-p)))
      (delete-all-system-binaries-before-recompile
       system file-class pathname-for-binaries?
       from-module?
       to-module?)
      ;;+unix
      ;;(touch-all-system-lisp-files-before-recompile system file-class)
      )

    ;; The boot-all-modules loop:
    (block nil
      (tagbody
       boot-all-modules
	 ;; Updates from the master directory:
	 #+remote-updates
	 (if (and compile-p (or (not no-updates-p) update-only-p))
	     #+no-macros
	     nil
	     #-no-macros
	     (setq reupdate-all-modules-p
		   (pull-in-all-system-files
		    system compile-p verbose-p
		    update-all-master-files-p update-only-p
		    from-module? to-module?)))

	 ;; Make non-Lisp object files:

	 ;; The non-Lisp object files are handled using the Unix "make"
	 ;; facility.  The makefile is MakeG2, and is maintained in
	 ;; the master source directory.  This is not necessarily the
	 ;; best way for providing source control, but it'll do for now.
	 ;; Also, there is no way to maintain non-Lisp object code
	 ;; files on VMS at the moment.  Is it worth the trouble of writing a
	 ;; make-like facility for it?  -pto 20jan89
	 ;;
	 ;; Note that we do not call Unix make when reupdate-all-modules-p
	 ;; is set because if it is set, we expect to be looped back to
	 ;; the top of boot-all-modules and after looping for one or more
	 ;; updates the following "if" statement will eventually be called
	 ;; again with reupdate-all-modules-p set to nil.

	 #-no-macros
	 (if (and (not reupdate-all-modules-p)
		  compile-p
		  (not update-only-p)
		  (not no-make-p))
	     (call-unix-make-for-g2 system))


	 ;; Compile and Load:

	 (when (not update-only-p)
	   (let ((old-making-distribution-system?
		  making-distribution-system?))	; variable defvar'd


	     (unless (eql making-distribution-system?
			  old-making-distribution-system?)
	       ;; in BOOTSTRAP make sure this doesn't get changed!
	       ;; (It took me two days to find this "bug"; it's
	       ;; nasty.(MHD))
	       (error "Variable MAKING-DISTRIBUTION-SYSTEM? was setq'd ~
		    while loading the ~
		    BOOTSTRAP module even though it was a DEFVAR. ~
		    This problem must be fixed in order for ~
		    the Bootstrapping software to work. Things that ~
		    might cause this:  Executing this program ~
		    from a Zmacs buffer or executing this program from ~
		    within a patch file (a file with ~
		    the -*- Patch-File: T -*- attribute). ~
		    Please report this problem to MHD at Gensym.")

	       )
	     (if (not (eval-feature '(and no-macros (not incremental-trans) chestnut-trans)))
		 (let ((started? (null from-module?))
		       (ended? nil))
		   (#-(and best-compile lucid) progn
		    #+(and best-compile lucid) lcl:with-deferred-warnings
		   (dolist (module (all-lisp-binary-file-symbols system))
		     (when ended? (return nil))
		     (when (null started?)
		       (setq started? (eq from-module? module)))
		     (cond
		       ((or compile-p recompile-p started?)
			(when (non-optional-or-included-optional-module-p
				module file-class system)
			  (setq reboot-all-modules-p
				(boot-module
				 module file-class system
				 (if (null started?) nil compile-p)
					;Load even if not started if
					;  compiling
				   verbose-p
				   (if recompile-p started?)
				   ;; Recompile only if started
				   reload-p silent-p pathname-for-binaries?)))))
		     (when to-module?
		       (when started?
			(setq ended? (eq module to-module?))))
		     (when reboot-all-modules-p
		       (format t "~%Reloading~a all modules (if necessary).~%"
			       (if compile-p " and compiling" ""))
		       (setq reboot-all-modules-p nil)
		       ;; reset reupdate-all-modules-p because the loop will
		       ;; reupdate all modules.
		       (setq reupdate-all-modules-p nil)
		       (go boot-all-modules)))))
	       (progn
		   #+(and (or chestnut chestnut-3) (not incremental-trans)) ;Chestnut3.1
		   (translate-all-modules-in-system system prepare-only-p analyze-calls-p)
		   (return nil)))
	     (terpri)))

	 ;; Reupdate if necessary:
         #+remote-updates ;;turns out that reupdate-all-modules-p can
         ;;only be changed in #+remote-updates, so conditionalize that here
	 (when reupdate-all-modules-p
	   (format t "~%Reloading~a all modules.~%"
		   (if compile-p ", and perhaps compiling, " ""))
	   (setq reupdate-all-modules-p nil)
	   (go boot-all-modules))))))

;;; Directory-for-bootstrap is exactly the same as the Common Lisp function
;;; directory.  In certain implementations, Symbolics' in particular, it fixes
;;; the bug that an error may be signalled when files exist matching the
;;; pathname specified on a VMS host over TCP/IP; in this case, nil should be
;;; returned, and this function does so properly.

(defun-allowing-lisp-pathnames directory-for-bootstrap (pathname)
  (directory pathname))

;; At present, this is only used in BOOTSTRAP, but this could conceivably be a
;; problem with directory menu generation in FILES, albeit rarely.  Get
;; symbolics to fix this, and fix FILES!! (MHD 9/25/88)




;;; New-directory-for-bootstrap ... replaces directory-for-bootstrap.  Creates
;;; a directory a-list.

(defun-allowing-lisp-pathnames new-directory-for-bootstrap (pathname)
  (mapcar #'list (directory pathname)))

;; (MHD 3/9/93)



;;; The function `delete-all-system-binaries-before-recompile' deletes all the
;;; binary files associated with the system before starting a recompile of all
;;; files.  The function returns two values:  a boolean saying if the deletion
;;; has been started (given the from and to ranges) and a boolean indicating if
;;; the deletion has ended.

(defun-for-macro delete-all-system-binaries-before-recompile
                 (system file-class
			 pathname-for-binaries? from-module? to-module?)
  (let (pathname
	 pathname?)
    (let* ((started-p (not from-module?))
	   (stopped-p nil))
      (with-faster-standard-output
	(dolist (file-symbol (all-lisp-binary-file-symbols system))
	  (when (string-or-symbol-equal file-symbol from-module?)
	    (setq started-p t))
	  #-(or no-macros lispworks)
	  (check-for-aborts-while-bootstrapping system t)
	  (when (and started-p
		     (not stopped-p)
		     (eval-feature
		       (get-default-include-test-for-compile
			 file-symbol file-class system))
		     (not (get-file-property file-symbol file-class system
					     :no-lisp-binary-produced-p))
		     (not (get-file-property file-symbol file-class system
					     :maintained-as-a-binary-file-p)))
	    (setq pathname
		  (if (or making-distribution-system?
			  pathname-for-binaries?)
		      (make-system-pathname
			system file-symbol nil :newest
			pathname-for-binaries? file-class 'binary)
		      (make-pathname
			:defaults
			(pathname (string-for-binary-file-namestring
				    file-symbol file-class system))
			:version :newest)))
	    (when (setq pathname? (probe-file pathname))
	      (format t "Deleting Binary File ~s.~%" (namestring pathname))
	      (delete-file pathname?)))
	  (when (string-or-symbol-equal file-symbol to-module?)
	    (setq stopped-p t))))
      (values started-p stopped-p))))






;;; The function `launch-system' is the correct top-level interface for
;;; launching a new instance of a product defined through declare-system and
;;; def-system-access.  Note that this function should do nothing but execute
;;; the launch-function? for a system, possibly in its own process.  If there is
;;; no launch-function? for the given system, this function calls error.  It is
;;; also valid to call the launch-function? of a system directly, for example in
;;; the main function of translated C images.  (That is what we do for
;;; translated products.  -jra 8/18/93)

;;; Note that there used to be some initialization operations in this function.
;;; The appropriate place for initializations is the function
;;; launch-system-process, which will always be a subfunction of the
;;; launch-function?  for a system.  Please put all initializations there.  -jra
;;; 8/18/93

(defmacro signal-inability-to-launch-system (system)
  (if (eq current-system-being-loaded 'gsi)
      `(format t "Unable to launch system ~a." ,system)
      `(error "Unable to launch system ~a." ,system)))

(defun-for-top-level launch-system (system)
  (let ((launch-function? (launch-function? system)))
    (cond (launch-function?
	   (ab-lisp::funcall launch-function?))
	  (t (signal-inability-to-launch-system system)))))

;; This used to wrap the funcall inside of lcl:with-scheduling-inhibited
;; when running under Solaris, which prevented the process from being
;; interrupted by a SIGINT (Control-C) signal.  It was used as a workaround,
;; because if you did interrupt a G2 process running in Lucid 4.2,
;; the wrong signal handler for SIGALARMs would be invoked, and Lucid
;; would crash with a segmentation violation.  We have been able to run
;; G2 with scheduling allowed and interrupts working fine by commenting
;; out the call to cc_frequently_typed_chars (an obfuscated name for
;; cc_count_licensed_processes).  I've committed that change to the
;; repository (for 5.0r4), so we no longer need the hack.  - jv, 5/20/98


;;; Check-for-aborts-while-bootstrapping ... Aborts when user types the Abort
;;; key or Control-A.

;; Lucid 2.20 on the Apollo has a problem with doing read-char-no-hangs
;; when taking *standard-input* from a file.  As we need to load the system
;; for distribution in that manner, I've decided to do check-for-aborts
;; only in development code or on Lispms.  -pto 02jun89

#-(or no-macros lispworks)
(defun-allowing-unwind check-for-aborts-while-bootstrapping
		       (system
			 &optional
			 (compile-p nil)
			 (update-p nil)
			 (g2tape-p nil)
			 (other-comments? nil))
  ;; AC 8-28-91.  Added this check to allow us to stop compiles from the
  ;; automated harness.
  (when (not (eval-feature :do-not-check-for-aborts))
    (let ((char? nil))
      (let ((finished-p nil))
	;; Listen for input in case user wants to abort.  If aborted, warn that
	;; this happened.
	(unwind-protect
	    (progn
	      (prog 
		()
	     top-of-loop
		;; Read from *terminal-io*, esp.  since *standard-input* may be
		;; in use for file reading.
		(if (null (setq char? (read-char-no-hang *terminal-io* nil nil)))
		    (return))
		
		;; might not get here, e.g. in the case where the lisp machine
		;; read in an abort character & aborted to top-level; that's OK.
		;; (But the unwind protect should get run.)
		(when (and char?
			   (and (member char?
					'(#.(int-char 1)	;control-A
					  #.(int-char 3)	;control-C
					  #.(int-char 27)	;escape
					  ))
				t))		; chestnut idiom (MHD 1/15/92)
		  #-no-macros
		  (dolist (feature features-only-relevant-to-non-macro-environments)
		    (delete-feature feature))
		  (throw 'aborted nil))
		(go top-of-loop))
	      (setq finished-p t)
	      char?)
	  (if (not finished-p)
	      (if other-comments?
		  (format t "~%~a was aborted.~%" other-comments?)
		  (cond
		    (g2tape-p
		     (format t "~%G2tape was aborted.~%"))
		    (t
		     (format 
		       t "~%~A of ~a was aborted.~%"
		       (cond (update-p "Updating")
			     (compile-p "Compilation")
			     (g2tape-p "G2tape")
			     (t "Loading"))
		       (system-alias system)))))))))))

;; Uses of WARN were changed to use FORMAT T above because doing warn in
;; the protected forms of an unwind protect behaved strangely with *break-
;; on-warnings* was T, at least on TI, 3.2. (MHD 10/20/89)

#-translator
(defun boot-module
       (module file-class system compile-p verbose-p
	recompile-p reload-p silent-p pathname-for-binaries?
	&optional (no-gc-messages? t))
  #-lucid
  (declare (ignore no-gc-messages?))

  (let* ((current-module? module)
	 (current-module-source-filename
	   (make-system-pathname
	     system module
	     (get-default-local-file-type module file-class system)
	     :newest nil file-class 'local))
	 (current-module-lisp-binary-filename
	   (make-system-pathname
	     system module
	     (get-default-binary-file-type module file-class system)
	     :newest pathname-for-binaries? file-class 'binary))
	 (filename-of-module-being-loaded?	; used & advertised in
						;   UTILITIES
	   current-module-source-filename)
	 #+(and lucid (not chestnut-trans) (not translator) (not no-macros))
	 (sys::*gc-silence*
	   (if (or silent-p no-gc-messages?)
	       t
	       (if (or (not (functionp 'gensym-gc-message)) verbose-p)
		   nil
		   #'gensym-gc-message)))
	 (reboot-all-modules-p nil))

    (multiple-value-bind
      (source-truename? binary-truename? loaded-p compiled-p)
	(get-module-file-information
	  module file-class system compile-p pathname-for-binaries?)
      (when (and (or recompile-p (and compile-p (not compiled-p)))
		 #-no-macros
		 (include-for-compile-p module file-class system)
		 source-truename?)

	#-no-macros
	(setq reboot-all-modules-p
	      (and
		#-no-macros
		(compile-or-process-module
		  module file-class system
		  verbose-p silent-p
		  source-truename? pathname-for-binaries?)
		compile-p
		(not compiled-p)))
	;; Will only reboot all modules if this module had to be recompiled (as
	;; opposed to being forced into a compile by the recompile-p flag).
	;; The compiled-p flag indicates if compilation is necessary.

	(if (get-file-property module file-class system
			       :no-lisp-binary-produced-p)
	    (progn
	      (setq binary-truename? t)
	      (setq compiled-p t))
	    (multiple-value-setq
	      (source-truename? binary-truename? loaded-p compiled-p)
	      (get-module-file-information
		module file-class system nil pathname-for-binaries?))))

      #-(or no-macros lispworks)
      (check-for-aborts-while-bootstrapping system compile-p)
      (when (and (or reload-p recompile-p (not loaded-p))
		 (if (boundp 'do-not-load-modules-p)	;don't load dst files!
		     (not do-not-load-modules-p)
		     t)
		 (include-for-load-p module file-class system))
	(if binary-truename?
	    (progn
	      (load-module
		module file-class system verbose-p
		(if (not (eq binary-truename? t))
		    binary-truename?
		    source-truename?)))
	    (when (not
		    (get-file-property module file-class system
				       :optional-module-p))
	      (cerror
		"Ignore the missing module and continue."
		"Cannot load ~a module -- no object file (~s)."
		module
		(namestring
		  (string-for-binary-file-namestring
		    module file-class system)))))))
    reboot-all-modules-p))






;;; The function `get-module-file-information' takes the module, system, a flag
;;; indicating if the information is desired for compilation and a pathname for
;;; binary files, and returns:  source-truename?, binary-truename?, loaded-p,
;;; and compiled-p.


#-translator
(defun get-module-file-information
       (module file-class system for-compilation? pathname-for-binaries?)
  (multiple-value-bind (loaded-p binary-truename?)
      (module-loaded-p module file-class system pathname-for-binaries?)
    (if for-compilation?
	(multiple-value-bind (compiled-p source-truename?)
	    (module-compiled-p module file-class system pathname-for-binaries?)
	  (values source-truename? binary-truename? loaded-p compiled-p))
	(values nil binary-truename? loaded-p nil))))

;;; The special variable `current-lisp-binary-file-pathname' is a pointer to
;;; the file currently being output to during a compile.  It is only bounded
;;; during the compile so that if a bomb out occurs during the compile, an
;;; error trapper could be set up to delete the binary file being produced.

#+(or remote-updates development)
(defvar-for-macro *current-lisp-binary-file-pathname*)






;;; The function `touch' is equivalent to the Unix touch program:  it
;;; changes the creation date of a file to the present.  On operating
;;; systems where version numbers exists, this program will also increment
;;; the version number.  If the file to be touched does not exist, it is
;;; created.

#+(or development (not no-macros))
(defun touch (filename &optional (ignore-if-does-not-exist-p nil))
  (values
    (let* ((pathname? (probe-file filename)))
      (if pathname?
	  (if (bootstrap-information-version-numbers-available-p)
	      (let* ((version
		       (pathname-version pathname?)))
		(when (numberp version)
		  (rename-file pathname?
			       (make-pathname :defaults pathname?
					      :version (+ version 1)))))
	      (let* ((temp-pathname
		       (make-pathname :defaults pathname?
				      :type
				      (format 
					nil "~a~~" (pathname-type pathname?)))))
		(gensym-copy-file pathname? temp-pathname)
		(delete-file pathname?)
		(rename-file temp-pathname pathname?)))
	  (if (not ignore-if-does-not-exist-p)
	      (let* ((stream?
		       (open filename :direction :output
			     #+lucid :error
			     #+lucid nil)))
		(if stream?
		    (progn
		      (close stream?)
		      (probe-file filename))
		    nil)))))))








;; modules-compiled is used to list modules which will need to be translated
;; on the second pass.  modules are pushed on in compile-file-function for
;; each module that is compiled on the first pass.

#-no-macros
(defvar modules-compiled '(bootstrap load))


;;; The function `compile-file-function' is called by the boot-system
;;; facility to compile files if there are no other compile functions
;;; specified for the function.

;; The cc_log calls below were removed in a attempt to find the culprit of the
;; translator crashes.  -jra 12/3/91

;; Put them back in as a compiler switch. Did the same in translate.lisp
;; AC 12/27/91.

(declare-forward-reference set-up-chestnut-incremental-translations function)

(declare-forward-reference translate-module function)

#-no-macros
(defun-for-macro compile-file-function
		 (module source target
			 &optional verbose-p silent-p)
  #-(or allegro lucid) (declare (ignore verbose-p))
  #-lucid (declare (ignore silent-p))
  (pushnew module modules-compiled)
  (if (and (eval-feature :translator)
	   (eval-feature :no-macros))
      (progn
	;; Defined later.
	(translate-module current-system-being-loaded source)
	)
      (progn
	(compile-file-for-bootstrap
	  source
	  :output-file target
	  #+allegro :verbose
	  #+allegro verbose-p
	  #+lucid :messages
	  #+lucid (not (not verbose-p))		       ; s.t. ==> T or NIL
	  #+lucid :warnings
	  #+lucid (not silent-p))))
  )





;;; Print-n-spaces does (princ " ") N times.  This is used as a utility function
;;; for many functions in BOOTSTRAP.

#-translator
(defun print-n-spaces (n)
  (do* ((i 0 (+ i spaces-this-time))
	(spaces-this-time (min 40 (- n i))))
       ((>= i n))
    (write-string
      "                                        "
      *standard-output*
      :end spaces-this-time)))

;;; The function `compile-or-process-module' ...  This function returns nil
;;; no rebooting of the system is required, and a non-nil if the compile
;;; function for the module thinks that a recompilation is required.

#-translator
(defun-for-macro compile-or-process-module
    (module file-class system
	    verbose-p
	    silent-p
	    truename?
	    override-pathname?)
  verbose-p					; not necessarily used
  system					; not used
  #-(or no-macros lispworks)
  (check-for-aborts-while-bootstrapping system t)
  (let* ((source-truename
	   (or truename? (truename current-module-source-filename)))
	 (output-file-truename
	   (make-system-pathname
	     system module nil (pathname-version source-truename)
	     override-pathname? file-class
	     (if (get-file-property module file-class system
				    :no-lisp-binary-produced-p)
		 'local
		 'binary)))
	 (reboot-all-modules-p nil))

    ;; see if this needs integrating w/(eighth bootstrap-information)!!
    ;; (eighth bootstrap-information) =
    ;; (bootstrap-information-use-directory-function-p)

    (let* ((normal-exit? nil)
	   (compile-function?
	     (get-file-property
	       module file-class system :lisp-compile-function))
	   (no-lisp-binary-produced-p
	     (get-file-property module file-class system
				:no-lisp-binary-produced-p))
	   (module-position? nil)		; all this logic cloned in
	   (total-number-of-modules		;    load-module (!)
	     (do* ((system-modules
		     (system-modules system)
		     (cdr system-modules))
		   (i 0))
		  ((null system-modules) i)
	       (incf i)
	       (if (eq module (car system-modules))
		   (setq module-position? i)))))
      (unwind-protect
	   (progn
	     #+(or remote-updates development)
	     (if (or (not no-lisp-binary-produced-p)
		     (not (pathnames-similar-p
			    source-truename output-file-truename)))
		 #+no-macros 
		 nil
		 #-no-macros
		 (setq *current-lisp-binary-file-pathname*
		       output-file-truename))
	     (when (not silent-p)
	       (with-faster-standard-output 
		 (let* ((line
			  (format
			    nil "~a ~a"
			    (if compile-function? "Processing" "Compiling")
			    module))
			(line-length-so-far (length line)))
		   (format t "~%~a" line)
		   (when module-position?
		     (print-n-spaces (- 25 line-length-so-far))
		     (setq line-length-so-far 25)
		     (let ((pathname-version? (pathname-version output-file-truename)))
		       (when (numberp pathname-version?)
			 (format t "#~d" pathname-version?)
			 (incf line-length-so-far
			       (+ 1 (floor (log pathname-version? 10)))))))
		   (cond
		     ((and module-position?
			   (null compile-function?))
		      (print-n-spaces (- 30 line-length-so-far))
		      (format t " [~d/~d]" module-position? total-number-of-modules))
		     ((and compile-function? module-position?)
		      (princ ", ")			; subtract 2 from line-length-so-far
		      (print-n-spaces (- 30 (- line-length-so-far 2)))
		      (format t " [~d/~d]" module-position? total-number-of-modules)
		      (format t " ~%  to ~s" (namestring output-file-truename))
		      (format t "~%  (Processing with ~a)" compile-function?))
		     (compile-function?
		      (format t ",~%  to ~s" (namestring output-file-truename))
		      (format t "~%  (Processing with ~a)" compile-function?))
		     (t
		      (format t " ~%  to ~s" (namestring output-file-truename))))
		   (format t " "))))
	     (if compile-function?
		 (setq reboot-all-modules-p
		       (catch 'reboot-all-modules
			 (progn
			   (ab-lisp::funcall
			     compile-function?
			     source-truename output-file-truename)
			   nil)))
		 (when (not no-lisp-binary-produced-p)
		   #+allegro (terpri)    ; allegro doesn't do "freshline" before writing warnings!
		   #-no-macros
		   (compile-file-function
		     module source-truename output-file-truename
		     verbose-p silent-p)))

	     #+(and (not no-macros) (or remote-updates development))
	     (makunbound '*current-lisp-binary-file-pathname*)
	     (setq normal-exit? t))

	;; Clean up
	(if (not normal-exit?)
	    ;; delete output file if compilation was aborted --
	    ;;   this is esp. useful for TI & Lucid VMS	      
	    (delete-file-if-it-exists output-file-truename))))
    #+lucid
    (sys::clear-undef)
    (if use-directory-lists-for-bootstrapping?
	(add-to-directory-list-for-bootstrapping
	  output-file-truename
	  'current-directory-of-binary-truenames))
    reboot-all-modules-p))





#-translator
(defun load-module (module file-class system
		    verbose-p default-truename?)
  (let* ((load-truename
	   (or default-truename?
	       (truename current-module-lisp-binary-filename)))
	 (load-function?
	   (get-file-property module file-class system :lisp-load-function))
	 (module-position? nil)			; all this logic cloned in
	 (total-number-of-modules		;    compile-module (!)
	   (do* ((system-modules
		   (system-modules system)
		   (cdr system-modules))
		 (i 0))
		((null system-modules) i)
	     (incf i)
	     (if (eq module (car system-modules))
		 (setq module-position? i))))
	 (loading-source-p
	   (get-file-property module file-class system :no-lisp-binary-produced-p))
	 (truenames-directory
	   (if loading-source-p
	       current-directory-of-source-truenames?
	       current-directory-of-binary-truenames)))

    (with-faster-standard-output
      (let ((line (format
		    nil "Loading~a ~a"
		    (if load-function?
			(format nil " with ~a" load-function?)
			(if loading-source-p
			    " (Lisp load) "
			    ""))
		    module)))
	(format t "~&~a" line)		; changed to "freshline" (~&) for allegro
	(cond
	  (module-position?
	   (let ((pathname-version? (pathname-version load-truename)))
	     (cond
	       ((numberp pathname-version?)
		(print-n-spaces (- 25 (length line)))
		(format t "#~d" pathname-version?)
		(print-n-spaces
		  (- 30 (+ 26 (floor (log pathname-version? 10))))))
	       (t
		(print-n-spaces (- 30 (length line))))))
	   (format t " [~d/~d] " module-position? total-number-of-modules)))))

    (with-gensym-handlers-for-load-file
      (if load-function?
	  (ab-lisp::funcall load-function? load-truename)
	  (load load-truename :verbose verbose-p)))

    (cond
      (making-distribution-system?
       (setf (distribution-module-pathname-previously-loaded? module system)
	     load-truename)
       (if (use-dates-instead-of-versions-p)
	   (setf (distribution-file-write-date-of-previously-loaded-module?
		   module system)
		 (if use-directory-lists-for-bootstrapping?
		     (get-file-write-date-from-directory-list
		       load-truename truenames-directory)
		     (file-write-date load-truename)))))
      (t
       (setf (module-pathname-previously-loaded? module system)
	     load-truename)
       (if (use-dates-instead-of-versions-p)
	   (setf (file-write-date-of-previously-loaded-module? module system)
		 (if use-directory-lists-for-bootstrapping?
		     (get-file-write-date-from-directory-list
		       load-truename truenames-directory)
		     (file-write-date load-truename))))))))










;;; Do-bootstrapping-preview-if-possible prints a message to the terminal saying
;;; how many modules there are to load, and how many to compile if compile-p.
;;; However, if use-directory-lists-for-bootstrapping? is false, this does nothing,
;;; since it would be too expensive to compute this information.  This is to be
;;; called out of boot-system after the directory list special variables have
;;; been set up.

;;; This is not defined in the #-translator environment.

#-translator
(defun do-bootstrapping-preview-if-possible
       (system binary-directory-pathname-to-use compile-p)
  (when use-directory-lists-for-bootstrapping?
    (do* ((modules (system-modules system) (cdr modules))
	  (module (car modules) (car modules))
	  (pathname-for-binaries
	    binary-directory-pathname-to-use)
	  (count 0)
	  (count-of-modules-needing-compilation 0)
	  (count-of-modules-needing-loading 0)
	  (file-class 'system-lisp-source-files))
	 ((null modules)
	  (format t "~%[~d/~d module~a to load"
		  count-of-modules-needing-loading
		  count
		  (if (= count-of-modules-needing-loading 1) "" "s"))
	  (format t
		  (if compile-p "; ~d/~d to compile]" "]")
		  count-of-modules-needing-compilation
		  count))
      (incf count)
      (let ((current-module-source-filename
	      (make-system-pathname
		system module
		(get-default-local-file-type
		  module 'system-lisp-source-files system)
		:newest nil file-class 'local)))
	(multiple-value-bind (v1 v2 loaded-p compiled-p)
	    (get-module-file-information
	      module file-class system compile-p pathname-for-binaries)
	  (declare (ignore v1 v2))
	  (cond
	    (compile-p
	     (cond
	       ((not compiled-p)
		(incf count-of-modules-needing-compilation)
		(incf count-of-modules-needing-loading))
	       ((not loaded-p)
		(incf count-of-modules-needing-loading))))
	    ((not loaded-p)
	     (incf count-of-modules-needing-loading))))))))




;;; Find-file-with-same-name-in-directory returns the first truename from
;;; directory, a directory list of truenames, which has a name component that
;;; is string-equal to that of filename.  If filename can't be found in the
;;; directory list, the result of a probe-file of the filename is returned.

#-translator
(defun find-file-with-same-name-in-directory (filename directory-list
					      &optional file-type)
  (or (find-file-with-same-name-in-directory-list
	filename directory-list file-type)
      (if directory-list
	  (let* ((pathname-1 (pathname filename))	; heuristic kludge to decide whether
		 (pathname-2			; to do a probe-file
		   (dolist (entry directory-list)
		     (when (car entry) (return (car entry))))))
	    (when				; Don't do one if the file is in the
						;   directory-list's directory.
	      (not (and (equal (pathname-directory pathname-1)
			       (pathname-directory pathname-2))
			(equal (pathname-host pathname-1)
			       (pathname-host pathname-2))))
	      (probe-file filename)))
	  (probe-file filename))))

#-translator
(defun find-file-with-same-name-in-directory-list (filename directory-list
						   &optional file-type)
  (when (null file-type)
    (setq file-type (pathname-type filename))
    (if (eq file-type :wild) (setq file-type nil)))
  (let ((name (pathname-name filename)))
    (dolist (directory-entry directory-list nil)
      (let ((truename? (first directory-entry)))
	(if (and truename?
		 (string-equal name (pathname-name truename?))
		 (or (null file-type)
		     (string-or-symbol-equal
		       file-type (pathname-type truename?))))
	    (return truename?))))))

;; Consider making a function like this, but more efficient.  The function that
;; BOOTSTRAP needs assume may assume that it will only be called once with a
;; given filename; it therefore could destructively modify the directory list
;; to narrow the search space.  It could also exclude files that were not among
;; the ;; current system's modules.  It could also opportunistically sort the
;; files.  In some implementations the list may already be sorted in some way
;; (or available sorted), and some advantage of that could be taken.

;; One thing to beware of is that Common Lisp does not say whether a directory
;; list is unshared (modifiable) list structure.


(defun get-file-write-date-from-directory-list (goal-truename directory-list)
  (declare (eliminate-for-no-macros-gsi))
  (dolist (directory-entry directory-list nil)
    (let ((truename? (first directory-entry)))
      (if (eq truename? goal-truename)
	  (return
	    (or (getf (cdr directory-entry) :creation-date)
		(file-write-date goal-truename)))))))


;;; Add-to-directory-list-for-bootstrapping sets directory-list-special-variable
;;; so that it contains the directory list of truename at its front.

(defun-allowing-lisp-pathnames add-to-directory-list-for-bootstrapping
       (truename directory-list-special-variable)
  (set directory-list-special-variable
       (nconc (new-directory-for-bootstrap truename)
	      (symbol-value directory-list-special-variable))))



(defun-allowing-lisp-pathnames older-or-same-version-p
    (pathname-1
      pathname-2
      &optional directory-list-1? directory-list-2?)
  (declare (eliminate-for-no-macros-gsi))
  (let (version-1 version-2)
    (if (or (use-dates-instead-of-versions-p)
	    (not (numberp (pathname-version pathname-1)))
	    (not (numberp (pathname-version pathname-2))))
	(progn
	  (setq version-1
		(if directory-list-1?
		    (get-file-write-date-from-directory-list
		      pathname-1 directory-list-1?)
		    (file-write-date pathname-1)))
	  (setq version-2
		(if directory-list-2?
		    (get-file-write-date-from-directory-list
		      pathname-2 directory-list-2?)
		    (file-write-date pathname-2))))
	(progn
	  (setq version-1 (pathname-version pathname-1))
	  (setq version-2 (pathname-version pathname-2))))
    (if (and (numberp version-1) (numberp version-2))
	(<= version-1 version-2)
	(eql version-1 version-2))))




#-translator
(defun module-compiled-p (module file-class system pathname-for-binaries?)
  module system   ; not used
  (let* ((no-lisp-binary-produced-p
	   (get-file-property module file-class system
			      :no-lisp-binary-produced-p))
	 (truename-of-latest-version-source?
	   (if use-directory-lists-for-bootstrapping?
	       (find-file-with-same-name-in-directory
		 current-module-source-filename
		 current-directory-of-source-truenames?
		 (get-default-local-file-type module file-class system))
	       (probe-file
		 current-module-source-filename)))
	 (lisp-destination-filename
	   (make-system-pathname
	     system module nil :NEWEST
	     pathname-for-binaries? file-class
	     (if no-lisp-binary-produced-p
		 'local
		 'binary)))
	 (truename-of-latest-destination-file?
	   (if use-directory-lists-for-bootstrapping?
	       (find-file-with-same-name-in-directory
		 lisp-destination-filename
		 current-directory-of-binary-truenames
		 (if (get-file-property
		       module file-class system :no-lisp-binary-produced-p)
		     (get-default-local-file-type module file-class system)
		     (get-default-binary-file-type module file-class system)))
	       (probe-file lisp-destination-filename))))
    (values
      (and truename-of-latest-version-source?
	   truename-of-latest-destination-file?
	   (older-or-same-version-p
	     truename-of-latest-version-source?
	     truename-of-latest-destination-file?
	     (if use-directory-lists-for-bootstrapping?
		 current-directory-of-source-truenames?)
	     (if use-directory-lists-for-bootstrapping?
		 current-directory-of-binary-truenames)))
      truename-of-latest-version-source?)))

#-translator
(defun module-loaded-p (module file-class system pathname-for-binaries?)
  (let* ((no-lisp-binary-produced-p
	   (get-file-property module file-class system
			      :no-lisp-binary-produced-p))
	 (previously-loaded-pathname?
	   (if making-distribution-system?
	       (or (distribution-module-pathname-previously-loaded? module system)
		   (dolist (sharing-system (systems-to-share-binary-files-with system))
		     (let ((pathname?
			     (distribution-module-pathname-previously-loaded?
			       module sharing-system)))
		       (when pathname? (return pathname?)))))
	       (or (module-pathname-previously-loaded? module system)
		   (dolist (sharing-system (systems-to-share-binary-files-with system))
		     (let ((pathname?
			     (module-pathname-previously-loaded?
			       module sharing-system)))
		       (when pathname? (return pathname?)))))))
	 (lisp-destination-filename
	   #+(and chestnut-trans incremental-trans)
	   (make-system-pathname system module "c" :newest nil file-class 'binary)
	   #-(and chestnut-trans incremental-trans)
	   (make-system-pathname
	     system module nil
	     :NEWEST pathname-for-binaries? file-class
	     (if no-lisp-binary-produced-p
		 'local
		 'binary)))
	 (truename-of-latest-destination-file?
	   (if use-directory-lists-for-bootstrapping?
	       (find-file-with-same-name-in-directory
		 lisp-destination-filename
		 current-directory-of-binary-truenames
		 (if (get-file-property
		       module file-class system :no-lisp-binary-produced-p)
		     (get-default-local-file-type module file-class system)
		     (get-default-binary-file-type module file-class system)))
	       (probe-file lisp-destination-filename))))
    (values
      (and previously-loaded-pathname?
	   truename-of-latest-destination-file?
	   (if (use-dates-instead-of-versions-p)
	       (<=
		 (if use-directory-lists-for-bootstrapping?
		     (get-file-write-date-from-directory-list
		       truename-of-latest-destination-file?
		       current-directory-of-binary-truenames)
		     (file-write-date truename-of-latest-destination-file?))
		 (if making-distribution-system?
		     (or (distribution-file-write-date-of-previously-loaded-module?
			   module system)
			 (dolist (sharing-system (systems-to-share-binary-files-with system))
			   (let ((write-date?
				   (distribution-file-write-date-of-previously-loaded-module?
				     module sharing-system)))
			     (when write-date? (return write-date?))))
			 ;;make type inferencer happy on sbcl:
			 #+sbcl 0.0)
		     (or (file-write-date-of-previously-loaded-module?
			   module system)
			 (dolist (sharing-system (systems-to-share-binary-files-with system))
			   (let ((write-date?
				   (file-write-date-of-previously-loaded-module?
				     module sharing-system)))
			     (when write-date? (return write-date?))))
			 #+sbcl 0.0)))
	       (older-or-same-version-p
		 truename-of-latest-destination-file?
		 previously-loaded-pathname?
		 (if use-directory-lists-for-bootstrapping?
		     current-directory-of-binary-truenames))))
      truename-of-latest-destination-file?)))





;; Module-{loaded,compiled}-p will need some fixing up for systems without
;; versions!

;;;; All System Modules

(defparameter all-modules-of-all-systems nil)

(defmacro canonical-index-of-module (module)
  `(get ,module :standard-module-index))

(defmacro def-all-system-modules (&body list-of-all-modules)
  (if (member :development *features*)
      `(eval-when (:compile-toplevel :load-toplevel :execute)
	  (dolist (old-module-info all-modules-of-all-systems)
	    (setf (canonical-index-of-module (car old-module-info)) nil))
	  (setf all-modules-of-all-systems ',list-of-all-modules)
	  ,@(nreverse
	      (let ((index 1)
		    result)
		(dolist (module-info list-of-all-modules)
		  (push
		    `(setf (canonical-index-of-module ',(car module-info)) ,index)
		    result)
		  (incf index))
		result)))
      nil))





;;;; Declare-system


;;; Declare-system creates a new system.  The system's name is system-name and
;;; its modules consist of the files specified in the list of module names.
;;; The order or the modules is the exact order that they will be compiled and
;;; loaded in.  The order should be such that compiling and then loading each
;;; file in this order "works" regardless of whether the system has ever been
;;; loaded into the lisp environment.

;;; Options is a plist of alternating indicators and values.  Many of these
;;; default in an implementation dependent manner.  Many of these can be set up
;;; to default correctly in the LOAD file.  (See module LOAD.)  This list is
;;; not evaluated.  The options currently supported are:  alias, nicknames,
;;; system-c-files, distribution-c-files, h-files, text-files, binary-files,
;;; kb-files, kl-files, kb-type (*), kl-type (*), lisp-binary-type (*),
;;; lisp-source-type (*), system-pathname (*).  where (*) means that the option
;;; has non-nil default.  -pto 22dec88
;;;
;;;
;;;
;;;    NAMES:
;;;
;;;    alias - the name this system goes by to the General public (good
;;;    means of changing name for users without changing it
;;;    everywhere internally.)
;;;
;;;    nicknames - a list of nicknames for this system
;;;
;;;
;;;
;;;    SYSTEM FILES:  (These files are specified in declare-system's
;;;    options and they exclude Lisp files as lisp files are "real" modules
;;;    while these are just used for updating files that Lisp uses.)
;;;
;;;    system-c-files - a list of C source files used by system
;;;
;;;    distributionc-files - a list of C source files for distribution
;;;
;;;    h-files - a list of include files for C sources
;;;
;;;    text-files - a list of text files (with extentions, if necessary).
;;;    These files can be of any type.
;;;
;;;    binary-files - a list of binary files whose sources are not available.
;;;
;;;    kb-files - a list of KB files to be associated with this system
;;;
;;;    kl-files - a list of knowledge library (KL) files to be associated with
;;;    this system
;;;
;;;    systems-to-share-binary-files-with - a list of systems that may load binary
;;;    files for this system; for example, G2 can share binary files with Telewindows,
;;;    and vice versa.  So, if you've loaded Telewindows, when you load G2, you don't
;;;    have to reload all the files in common between the two systems.
;;;

;;;
;;;
;;;
;;;    FILE TYPES:
;;;
;;;    kb-type - the file type for KBs in this system.
;;;
;;;    kl-type - the file type for knowledge libraries (KLs) in this system.
;;;
;;;    lisp-binary-type - the file type for lisp binaries in this system.  This
;;;    defaults in an implementation-dependent manner
;;;
;;;    lisp-source-type - the file type for sources in this system.
;;;
;;;
;;;
;;;    PATHNAME:
;;;
;;;    system-pathname - the directory on which all files for this system are
;;;    stored

;;; Declare-system generates the following functions whose names are contain
;;; the name name of the system as a root:
;;;
;;;    COMPILE-system-name
;;;    MAKE-system-name or LOAD-system-name
;;;
;;;      MAKE-system-name and LOAD-system-name are exactly the same, at
;;;      present.  The MAKE and COMPILE version differ only in that the COMPILE
;;;      version compiles any modules in the system that it determines are not
;;;      up to date.  Both of these take as their arg any number of symbols
;;;      which turn on or off various optional features.  These include:
;;;
;;;         compile - Compile as well as load.  (MAKE-system-name 'compile) is
;;;         the same  as (COMPILE-system-name)
;;;
;;;         recompile - Compile all modules regardless of whether they appear
;;;         up to date.
;;;
;;;         reload - Reload all modules regardless of whether they appear to
;;;         already have  been loaded.
;;;
;;;         no-process - Do not bring up the system window at the end of
;;;         loading.
;;;
;;;         verbose - Print alot about the status while running.
;;;
;;;         silent - Print absolutely nothing. (Output is actually diverted to
;;;         a null stream in order to enforce this.)

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defun normalize-module-name-or-description
	 (module-name-or-description)
    (if (consp module-name-or-description)
	(progn
	  (setf (car module-name-or-description)
		(normalize-name (car module-name-or-description)))
	  module-name-or-description)
	(normalize-name module-name-or-description))))

(defmacro declare-system ((system-name &rest options)
			  &body list-of-module-names-or-descriptions)
  (when (member current-system-being-loaded
		(getf options 'products-uninterested-in-this-system))
    ;(format t "~&  ignoring system ~s~%" system-name)
    (return-from declare-system nil))
  `(progn
     (if (null (get ',system-name 'system-binary-pathname?))
	 (setf (get ',system-name 'system-binary-pathname?)
	       (progn
		 #-development
		 (bootstrap-information-default-pathname)
		 #+development
		 (if (eval-feature :development)
		     (local-development-binary-directory ',system-name)
		     (bootstrap-information-default-pathname)))))
     ;; In distribution software, we should load G2 from the default
     ;; directory.  -pto 05jun89

     (pushnew ',(normalize-name system-name) all-systems)

     (apply
       #'declare-system-1
       ',(normalize-name system-name)
       ',(mapcar #'normalize-module-name-or-description
		 list-of-module-names-or-descriptions)
       ',options)

     ,@(when (not (eval-feature :translator))
	 (let ((result nil)
	       (service-names '(make compile go))) ; wanted RUN, but
					;   right now, run-ab, run-telewindows
					;   are defined -- what to do?!
					;
					; Note that LOAD was previously a
					;   synonym for MAKE, but the name
					;   never caught on, so I've flushed
					;   it.  (MHD 4/24/94)
	   (dolist (nickname
		     (cons system-name (getf options 'nicknames))
		    result)
	     (push
	       (let ((sub-result nil))
		 `(progn
		    ,@(dolist (service-name
				service-names
			       (nreverse sub-result))
			(let* ((name-in-ab-package
				 (intern
				   (format nil "~A-~A" service-name nickname)
				   (find-package 'ab)))
			       (name-in-user-package
				 (intern
				   (symbol-name name-in-ab-package)
                                   (find-package #+ANSI-CL "CL-USER"
                                                 #-ANSI-CL "USER")))
			       (compile-p (eq service-name 'compile))
			       (run-p (eq service-name 'go)))
			  (push
			    `(defun ,name-in-ab-package (&rest options)
			       (let* ((*package* (find-package 'ab)))
				 (boot-system-in-batch-mode
				   ',system-name
				   ,compile-p
				   ,(if run-p
					'(cons 'launch-only options)
					'options))))
			    sub-result)
			  (push `(setf (symbol-function ',name-in-user-package)
				       (symbol-function ',name-in-ab-package))
				sub-result)))))
	       result))))))


(defun-allowing-lisp-pathnames check-boot-system-options (system options)
  (declare (eliminate-for-no-macros-gsi))
  (do ((entry options (cdr entry)))
      ((null entry))

    (cond
      ((or (and (string-or-symbol-member
		  (car entry)
		  '(compile
		    launch-only
		     recompile
		     incremental
		     reload
		     no-process
		     reload-load

		     for-distribution
		     distribution

		     no-gsi			;automate these?
		     no-gfi
		     no-gspan

		     all-optional-modules
		     no-optional-modules

		     verbose
		     silent
		     #+lucid
		     no-gc-messages

		     macros-only
		     prepare-only
		     analyze-calls
		     #-no-macros
		     no-macros

		     ;;#+(or remote-updates development)
		     no-make

		     #+(or remote-updates development)
		     update-only
		     #+(or remote-updates development)
		     updates-only
		     #+(or remote-updates development)
		     no-updates
		     #+(or remote-updates development)
		     update-all-master-files
		     #+(or remote-updates development)
		     update-only-applicable-files
		     #+(or remote-updates development)
		     ignore-include-test-for-update

		     no-delete

		     no-autolog		; (MHD 7/16/93)

		     logfile))

		t)				; chestnut idiom (MHD 1/15/92)
	   (string-or-symbol-member (car entry) (all-optional-modules system))
	   ))

      ;; Check for a distribution binary directory and for a binary for macros
;;      #+(or remote-updates development)
      ((or (string-or-symbol-equal (car entry) 'destination)
	   (string-or-symbol-equal (car entry) 'distribute)
	   (string-or-symbol-equal (car entry) 'binary-directory)
	   (or (stringp (car entry))
	       (string-or-symbol-equal (car entry) 'command-line)))
       (unless (stringp (car entry))
	 (pop entry))
       (if (not (or (pathnamep (car entry))
		    (stringp (car entry))
		    (and (member
			   (car entry)
			   '(:default-dst-directory
			      :default-macro-directory
			      :default-development-binary-directory))
			 t)))			; chestnut idiom (MHD 1/15/92)
	   (cerror "Continue anyway"
		   "No destination pathname: ~a"
		   (car entry))))

      ((string-or-symbol-member (car entry) '(from to))
       (pop entry)
       (cond
	 ((string-or-symbol-member (car entry) '(after before))
	  (pop entry)
	  (cond
	    ((not
	       (string-or-symbol-member (car entry)
					(all-lisp-binary-file-symbols system)))
	     (cerror
	       "Continue anyway" "Not a system module, AFTER, or ~
  			  BEFORE: ~a"
	       (car entry))
	     (pop entry))))))

      ((string-or-symbol-member (car entry) '(optional-modules))
       ;; Mark D. - Your optional modules option does not work!!!
       ;; -pto 13nov88
       (pop entry)					; Fix checking!!!
       (pop entry))

      (t
       (cerror "Continue anyway" "Unknown Option: ~a" (car entry))))))





;;; The function `translate-binary-directory-or-default' ...

;;#+(or remote-updates development)
(defun-allowing-lisp-pathnames translate-binary-directory-or-default
    (system binary-directory-or-flag)
  (declare (eliminate-for-no-macros-gsi))
  (cond
    ((equal binary-directory-or-flag :default-dst-directory)
     (local-dst-directory system))
    ((equal binary-directory-or-flag :default-macro-directory)
     (local-macro-directory system))

    #+development
    ((equal binary-directory-or-flag :default-development-binary-directory)
     (local-development-binary-directory system))

    ((or (stringp binary-directory-or-flag)
	 (pathnamep binary-directory-or-flag)
	 (null binary-directory-or-flag))
     binary-directory-or-flag)
    (t (error "Illegal 'distribute, 'destination, or 'binary-directory flag ~
               ~a.  The legal flags are:   :default-dst-directory, ~
               :default-macro-directory, and ~
               :default-development-binary-directory."
	      binary-directory-or-flag))))

;;; The function `extract-pathname-for-distribution-binaries' ...

(defun-allowing-lisp-pathnames extract-pathname-for-distribution-binaries
    (system options)
  (declare (eliminate-for-no-macros-gsi))
  (let* ((distribute-list (string-or-symbol-member 'distribute options))
	 (distribute-pathname (cadr distribute-list)))
    (translate-binary-directory-or-default system distribute-pathname)
    (if distribute-list
	(if (or (stringp distribute-pathname) (pathnamep distribute-pathname))
	    distribute-pathname
	    (local-dst-directory system)))))




;;; The function `extract-pathname-for-non-distribution-binaries' ...  Could
;;; return nil.

(defun-allowing-lisp-pathnames extract-pathname-for-non-distribution-binaries
       (system compile-p options)
  (declare (eliminate-for-no-macros-gsi))
  (let* ((destination-list (string-or-symbol-member 'destination options))
	 (binary-directory-list
	   (string-or-symbol-member 'binary-directory options))
	 (destination? (cadr destination-list))
	 (binary-directory? (cadr binary-directory-list)))
    (if (and destination-list
	     binary-directory-list
	     (not (equal destination? binary-directory?)))
	(cerror
	  "Continue, using the binary-destination directory."
	  "Equivalent options 'destination and 'binary-directory-list ~
	   have been specified ~
	   but the values are not the same (~S amd ~S)."
	  destination?
	  binary-directory?))
    (if (and destination? (null binary-directory?))
	(setq binary-directory? destination?))

    ;; From here on down, only binary-directory? is used
    (if binary-directory?
	(setq binary-directory?
	      (translate-binary-directory-or-default
		system binary-directory?)))

    (if (or (stringp binary-directory?) (pathnamep binary-directory?))
	binary-directory?
	(if (string-or-symbol-member 'distribute options)     ;could return nil
	    (if compile-p
		(local-macro-directory system)
		(local-dst-directory system))))))




;;; The function `extract-list-of-optional-modules' is a temporary kludge to
;;; allow control over the inclusion or exclusion of optional modules.  When
;;; the system for productizing optional modules (GSI, GFI, etc.) has been
;;; design, this will go away.  -pto 21dec88

(defun extract-list-of-optional-modules (system user-options)
  (declare (eliminate-for-no-macros-gsi))
  (let ((all-optional-modules (all-optional-modules system))
	(optional-modules nil))

    (if (string-or-symbol-member 'all-optional-modules user-options)
	(if (string-or-symbol-member 'no-optional-modules user-options)
	    (cerror "Continue without all optional modules."
		    "You specified both 'no-optional-modules and ~
			       all-optional-modules.")
	    (dolist (file-symbol all-optional-modules)
	      (pushnew file-symbol optional-modules)))
	;; If not all-optional-modules
	#+development
	(when (eval-feature :development)
	  (dolist (file-symbol all-optional-modules)
	    (if (get-file-property file-symbol 'system-lisp-source-files system
				   :development-optional-module-p)
		(pushnew file-symbol optional-modules)))))

    (dolist (file-symbol all-optional-modules)
      (if (or (eval-feature file-symbol)
	      (string-or-symbol-member file-symbol user-options))
	  (pushnew file-symbol optional-modules))
      (if (string-or-symbol-member
	    (format nil "NO-~a" (symbol-name file-symbol))
	    user-options)
	  (setq optional-modules
		(string-or-symbol-delete file-symbol optional-modules))))

    (if (string-or-symbol-member 'no-optional-modules user-options)
	(setq optional-modules nil))

    (setf (optional-modules system) optional-modules)
    optional-modules))




#+(or remote-updates development)
(defvar ignore-include-test-for-update-p nil)


#-translator
(defun-allowing-unwind boot-system-in-batch-mode
		       (system-name compile-p options)
  (when (string-or-symbol-member 'help options)
    (format t "~%Boot-system-in-batch-mode takes these arguments:")


    (dolist (element
	      '((nil nil "These switches are commonly used.")
		(recompile nil "Discard all binary files, and do full recompile")
		(no-delete nil "Suppress the deleting of all binary files triggered by a recompile.")
		(from <module> "Start from this module.")
		(to   <module> "Finish with this module.")

		(nil nil "These switches are occationally useful.")
		(no-make nil "Suppress invoking the make which builds the C object library.")
		(verbose nil "Be as noisy as you can.")
		(reload nil "Reload the binary files.")
		(silent nil "Be as quiet as possible.")
		(logfile <pathname> "Place the log file at this pathname.")
		(no-gc-messages nil "Suppress the generation of GC messages.")

		(nil nil "These switches are used as part of distribution building")
		(distribution nil "Generate binary files containing only distribution materials.")
		(macros-only nil "Compile, including the macros.")  ; ?? -mhd
		(no-macros nil "Suppress compilation of forms that are for macros.")
		(compile nil "Compile -- same as (compile-<system>)")
		(launch-only nil
		 "Just runs (launches) system -- same as (run-<system>) -- opposite of no-process")
		(no-autolog nil "Do not do autologging -- for user ab's use only.")

		(nil nil "These switches are just aliases.")
		(log <pathname> "See logfile.")
		(for-distribution nil "See distribution." )
		(distribute nil "See distribution.")

		(nil nil "These switches are obsolete.")
		(update-all-master-files "Obsolete: Get the \"master\" files from MA.")
		(updates-only nil "Obsolete: Only update the files from MA.")
		(update-only nil "Obsolete: See updates-only")
		(no-updates nil "Obsolete: Suppress updating the files from MA")
		(no-optional-modules nil "Obsolete: Do not include optional modules.")

		;; The sets the command line, using (replace-command-line
		;; <string>).  That function is defined in OS-SETTINGS, for
		;; development only, so this is not applicable if that doesn't
		;; get defined. (We check using fboundp.)  The setting is
		;; "sticky" in that it remains in effect for the rest of the
		;; (Lisp) session.  For example, subsequent calls launch-ab will
		;; all have the same command line, unless there's an intervening
		;; use of this command-line option, or a direct use of
		;; replace-command-line. Author: MHD. (MHD 3/2/94)
		(command-line <string>
		 "Make this look like the command line (if we know how). Sticky.")))
      (let ((arg-name? (first element))
	    (optional-arg? (second element))
	    (documentation (third element)))
	(cond
	  (arg-name?
	   (format t "~%~(~A ~A~21T~) ~A" arg-name? (if optional-arg?  optional-arg?  "") documentation))
	  (t
	   (format t "~2%~A" documentation)))))
    (return-from boot-system-in-batch-mode 'help-only))

  (let ((safe-keeping nil)
	(system (normalize-name system-name)))
    safe-keeping
    (unwind-protect
	(let ()
	  (let ((compile-p compile-p))
	    ;; this first checks to see if all the options make sense
	    (check-boot-system-options system options)
	    (let* (#+(or remote-updates development)
		   (ignore-include-test-for-update-p
		     (string-or-symbol-member
		       'ignore-include-test-for-update options)))

	      ;; Configure for development or non-developement
	      ;;	    #+(or remote-updates development)
	      (when (or (string-or-symbol-member 'for-distribution options)
			(string-or-symbol-member 'distribution options)
			(string-or-symbol-member 'distribute options)
			(string-or-symbol-member 'macros-only options)
			(string-or-symbol-member 'prepare-only options)
			(string-or-symbol-member 'analyze-calls options)
			#-no-macros
			(string-or-symbol-member 'no-macros options))
		(delete-feature :development))

	      (when (string-or-symbol-member 'macros-only options)
		(pushnew :non-development-macros *features*))

	      #-no-macros
	      (if (and (string-or-symbol-member 'no-macros options)
		       (not (string-or-symbol-member 'macros-only options)))
		  ;; Macros are to be present for Macro compiles,
		  ;; but if this is a no-macros compile, don't do it.
		  (pushnew :no-macros *features*)
		  (delete-feature :no-macros))

	      ;; Compile?
	      (setq compile-p
		    (or compile-p
			(string-or-symbol-member 'compile options)
			(string-or-symbol-member 'recompile options)))

	      ;; :development must be switched in or out by now:
	      (extract-list-of-optional-modules system options)

	      (when (or (eval-feature :chestnut)
			(eval-feature :chestnut-3)) ;Chestnut3.1
		#+development
		(setf (get system 'local-development-binary-directory)
		      (local-chestnut-development-directory system))
		#-chestnut-3
		(setf (get system 'local-macro-directory)
		      (local-chestnut-macro-directory system))
		(setf (get system 'local-dst-directory)
		      (local-chestnut-dst-directory system))
		#-chestnut-3
		(setf (get system 'system-binary-pathname?)
		      (cond
			((eval-feature :development)
			 (get system 'local-chestnut-development-directory))
			((eval-feature :no-macros)
			 (get system 'local-chestnut-dst-directory))
			(t (get system 'local-chestnut-macro-directory)))))

	      (boot-system 
		system					       ;1
		compile-p				       ;2
		(string-or-symbol-member 'verbose options)     ;3
		(string-or-symbol-member 'recompile options)   ;4
		(string-or-symbol-member 'reload options)      ;5
		(cond                                          ;6  -- no-process
		  ((and (boundp 'current-system-name)
			(symbol-value 'current-system-name)) ; recently bound to nil at top level (MHD 4/21/95)
		   (format t
			   "~%;;; Apparently inside a G2 Process, so forcing :no-process~%")
		   t)
		   (t
		    (string-or-symbol-member 'no-process options)))
		(string-or-symbol-member 'reload-load options) ;7
		(string-or-symbol-member 'silent options)      ;8

		;; pathname-for-distribution-binaries?
;;	        #-(or remote-updates development)
;;	        nil
;;	        #+(or remote-updates development)
		(extract-pathname-for-distribution-binaries
		  system options)			       ;9

		;; from-module?
		(let ((from? (string-or-symbol-member 'from options)))
		  (cond
		    (from?
		     (cond
		       ((string-or-symbol-equal (cadr from?) 'after)
			(let ((module-before (normalize-name (caddr from?))))
			  (cadr (member module-before
					(all-lisp-binary-file-symbols system)))))
		       ((string-or-symbol-equal (cadr from?) 'before)
			(do ((l (all-lisp-binary-file-symbols system) (cdr l)))
			    ((null l) nil)
			  (let ((module-after (normalize-name (caddr from?))))
			    (if (eq (cadr l) module-after)
				(return (car l))))))
		       (t (normalize-name (cadr from?)))))))   ;10

		(let ((to? (string-or-symbol-member 'to options)))
		  (cond
		    (to?
		     (cond
		       ((string-or-symbol-equal (cadr to?) 'after)
			(let ((module-before (normalize-name (caddr to?))))
			  (cadr (member module-before
					(all-lisp-binary-file-symbols system)))))
		       ((string-or-symbol-equal (cadr to?) 'before)
			(do ((l (all-lisp-binary-file-symbols system) (cdr l)))
			    ((null l) nil)
			  (let ((module-after (normalize-name (caddr to?))))
			    (if (eq (cadr l) module-after)
				(return (car l))))))
		       (t (normalize-name (cadr to?)))))))     ;11

		;; Pathname-for-non-distribution-binaries?
;	        #-(or remote-updates development)
;	       nil
;	       #+(or remote-updates development)
		(extract-pathname-for-non-distribution-binaries
		  system compile-p options)		       ;12

		(if (or (string-or-symbol-member 'logfile options)
			(string-or-symbol-member 'log options))
		    (or (if (not
			      (symbolp		       ; can be pathmame or string
				(cadr
				  (or (string-or-symbol-member 'logfile options)
				      (string-or-symbol-member 'log options)))))
			    (cadr (or (string-or-symbol-member 'logfile options)
				      (string-or-symbol-member 'log options))))
			(system-pathname system)))     ;13

		(string-or-symbol-member 'no-autolog options)  ;14

		(string-or-symbol-member 'no-updates options)  ;15

		(or (string-or-symbol-member 'update-only options)
		    (string-or-symbol-member 'updates-only options))   ;16

		(string-or-symbol-member 'no-gc-messages options)      ;17

		(and (string-or-symbol-member 'update-all-master-files options)
		     (not
		       (string-or-symbol-member
			 'update-only-applicable-files options)))      ;18

		(string-or-symbol-member 'macros-only options) ;19
		(string-or-symbol-member 'no-make options)     ;20
		(string-or-symbol-member 'no-delete options)   ;21

		(or (dolist (option options)
		      (when (stringp option) ; either the only string or the
			(return option))) ;   command-line keyword-like value
		    (second (string-or-symbol-member 'command-line options))) ;22

		(string-or-symbol-member 'launch-only options)	 ;23
		(string-or-symbol-member 'prepare-only options)  ;24
		(string-or-symbol-member 'analyze-calls options) ;25
		)))))))








;;;; Functions for the Installation of File Properties




;;; The function `install-all-file-properties-from-alist' takes a symbol (which
;;; represents a file) a file-class and an alist of the file property defaults,
;;; and installs all the default file properties on it.  The function
;;; `install-all-file-properties-from-plist' is the same except that it is
;;; given a plist of properties instead.


(defun install-all-file-properties-from-alist
       (file-symbol file-class system file-properties-alist)
  (let (property-name
	property-value)
    (dolist (property-description file-properties-alist)
      (setq property-name (first property-description))
      (setq property-value (second property-description))
      (set-file-property
	file-symbol file-class system property-name property-value))))


(defun install-all-file-properties-from-plist
       (file-symbol file-class system file-properties-plist)
  (let (property-name
	property-value)
    (do ((rest-of-plist file-properties-plist (cddr rest-of-plist)))
	((null rest-of-plist))
      (setq property-name (car rest-of-plist))
      (setq property-value (cadr rest-of-plist))

      ;; A nil test is a (not t).
      (if (and (null property-value)
	       (and (member property-name
			    `(:include-test-for-compile
			       :include-test-for-load
			       :include-test-for-update
			       :overriding-include-test))
		    t))				; chestnut idiom (MHD 1/15/92)
	  (setq property-value '(not t)))

      (set-file-property
	  file-symbol file-class system property-name property-value))))




;; The function `make-an-alist-of-file-property-defaults' makes a
;; file-property-defaults-alist which contains the non-nil defaults resulting
;; from combining the base defaults in the
;; alist-of-system-file-class-descriptions and the overriding defaults in
;; file-class-property-defaults-alist.

(defun make-an-alist-of-file-property-defaults
       (fcd-alist-of-file-property-defaults)
  (let ((file-property-defaults-alist nil)
	property
	base-default
	override
	default)
    (dolist (property-description alist-of-file-property-base-defaults)
      (setq property (first property-description))
      (setq base-default (second property-description))
      (setq override (assoc property fcd-alist-of-file-property-defaults))
      (if override
	  (setq default (second override))
	  (setq default base-default))
      (if default
	  (push (list property default) file-property-defaults-alist)))
    file-property-defaults-alist))



#+development
(defun check-plist-of-file-properties (file-symbol system plist-of-properties)
  (do ((rest-of-plist plist-of-properties (cddr rest-of-plist)))
      ((null rest-of-plist))
    (if (not (assoc (car rest-of-plist) alist-of-file-property-base-defaults))
	(error
	  "Illegal file property specified for ~a in system ~a:  ~a is ~a~%~
	   Legal file properties are:  ~a"
	  file-symbol
	  system
	  (car rest-of-plist)
	  (cadr rest-of-plist)
	  (mapcar #'car alist-of-file-property-base-defaults)))))




;;; The function `install-file-properties-for-file-name-or-description' ...
;;; Returns the file-symbol of the file.

(defun install-file-properties-for-file-name-or-description
       (file-name-or-description
	file-class system file-property-defaults-alist)
  (if (consp file-name-or-description)
      ;; Description
      (let ((file-symbol (car file-name-or-description))
	    (plist-of-properties (cdr file-name-or-description)))
	#+development
	(check-plist-of-file-properties
	  file-symbol system plist-of-properties)

	;; Install defaults first
	(install-all-file-properties-from-alist
	  file-symbol file-class system file-property-defaults-alist)

	;; Then install specific properties
	(install-all-file-properties-from-plist
	  file-symbol file-class system plist-of-properties)
	file-symbol)

      ;; Name
      (progn
	(install-all-file-properties-from-alist
	  file-name-or-description
	  file-class
	  system
	  file-property-defaults-alist)
	file-name-or-description)))



;;; The function `install-file-properties-for-system' takes the file-class, a
;;; list of file names (symbols) or description (lists), and an alist of the
;;; file-class file property defaults; and installs the non-nil module
;;; properties of the file.  (The car of a file description is the filename (a
;;; symbol) and the cdr of the file description is an plist of file properties
;;; that are to override all defaults for that file.)
;;; Install-file-properties-for-system returns a list of symbols corresponding
;;; to the file-symbols of the files.


(defun install-file-properties-for-system
       (file-names-or-descriptions?
	file-class
	system
	fcd-alist-of-file-property-defaults)

  (if file-names-or-descriptions?
      (let* (file-symbol
	     (list-of-file-symbols nil)
	     (file-property-defaults-alist
	       (make-an-alist-of-file-property-defaults 
		 fcd-alist-of-file-property-defaults)))

	(dolist (file-name-or-description file-names-or-descriptions?)
	    (setq file-symbol
		  (install-file-properties-for-file-name-or-description
		    file-name-or-description
		    file-class
		    system
		    file-property-defaults-alist))
	    (if (eval-feature
		  (get-default-include-test-for-load
		    file-symbol file-class system))
		(push file-symbol (system-modules system)))
	    (push file-symbol list-of-file-symbols))

	(nreverse list-of-file-symbols))))




#+(and chestnut-3-2-7 chestnut-trans)
(pushnew nil *features*) ; compatibility feature needed to make declare-system-1 work for GSI.


;;; Declare-system-1 ...

;;; KB-files should be a modules list of the names of KB files.  They are
;;; assumed to be in the same directory as the system.  KB files are text files
;;; with the file type extension KB.
;;;
;;; The options currently supported are:  alias, nicknames, system-c-files,
;;; distribution-c-files, h-files, text-files, binary-files,
;;; system-lisp-binary-files, kb-files, kl-files, kb-type (*), kl-type (*),
;;; lisp-binary-type (*), lisp-source-type (*), system-pathname (*).  where (*)
;;; means that the option has non-nil default.  The option
;;; system-lisp-source-files is equivalent to the system modules declared in
;;; the body of declare-system.
;;;
;;; The entry for the files of modules in
;;; alist-of-system-file-class-descriptions is under 'system-lisp-source-files.

;; a call to `union' was changed to `stable-list-union' since we
;; wanted to preserve order. --mhd and dbakhash (6/2/00)

(defun stable-list-union (list-1 list-2)
  (declare (type list list-1 list-1))
  (let ((result (append list-1 list-2)))
    (remove-duplicates result)))

(defun-allowing-lisp-pathnames declare-system-1
    (system file-names-or-descriptions &rest options)

  ;;; Check in development that all modules are known and in order.
  (when (member :development *features*)
    (let ((previous-module-index? 0))
      (dolist (module-description file-names-or-descriptions)
	(let* ((module (if (symbolp module-description)
			   module-description
			   (first module-description)))
	       (module-index? (canonical-index-of-module module)))
	  (unless module-index?
	    (format t "~&The module ~S unknown, see def-all-system-modules."
		    module))
	  (when (and previous-module-index? module-index?
		     (not (< (the fixnum previous-module-index?)
			     (the fixnum module-index?))))
	    (format t
	      "~&Load order must be consistent across all systems.  ~
                The module ~S appears out of canonical order, ~
                see def-all-system-modules"
	      module))
	  (setf previous-module-index? module-index?)))))

  (let ((alias (or (getf options 'alias) nil))
	(nicknames (or (getf options 'nicknames) nil))
	(system-pathname (or (getf options 'system-pathname)
			     nil))
	(system-package-name (or (getf options 'system-package-name)
				 system))
	(lisp-source-type (or (getf options 'lisp-source-type)
			      (bootstrap-information-lisp-source-file-type)))
	(lisp-binary-type (or (getf options 'lisp-binary-type)
			      (bootstrap-information-lisp-binary-file-type)))
	(kb-type (or (getf options 'kb-type)
		     (bootstrap-information-kb-file-type)))
	(kl-type (or (getf options 'kl-type)
		     (bootstrap-information-kl-file-type)))
	(systems-to-share-binary-files-with?
	  (getf options 'systems-to-share-binary-files-with))
	(system-is-windowless-p
	  (getf options 'system-is-windowless-p)))

    (setq system-pathname
	  (if system-pathname
	      (merge-pathnames			;  different.
		system-pathname
		ab-system-pathname)
	      ab-system-pathname))
    (setf (system-alias system) alias)
    (setf (systems-to-share-binary-files-with system)	; can be nil
	  systems-to-share-binary-files-with?)
    (dolist (nickname nicknames)
      (setf (get (normalize-name nickname) 'real-system-name) system))

    ;; Install properties of files.
    (let (file-class
	   file-class-indicator
	   file-class-module-property-defaults)
      (dolist (file-class-description alist-of-system-file-class-descriptions)
	(setq file-class	  ;eg. kb-files, h-files
	      (fcd-file-class-name file-class-description))
	(setq file-class-indicator
	      (fcd-system-property-name file-class-description))
	(setq file-class-module-property-defaults
	      (fcd-alist-of-file-property-defaults file-class-description))
	(setf (get system file-class-indicator)
	      (install-file-properties-for-system
		(mapcar #'normalize-module-name-or-description
			(getf options file-class))
		file-class
		system
		file-class-module-property-defaults))))

    (setf (system-modules system) nil)

    (let* ((file-class 'system-lisp-source-files)
	   (file-class-description
	     (assoc file-class
		    alist-of-system-file-class-descriptions))
	   (file-class-indicator
	     (fcd-system-property-name file-class-description))
	   (file-class-module-property-defaults
	     (fcd-alist-of-file-property-defaults file-class-description)))
      (setf (get system file-class-indicator)
	    (stable-list-union
	      (get system file-class-indicator)
	      (install-file-properties-for-system
		file-names-or-descriptions	; modules are also files
		file-class
		system
		file-class-module-property-defaults))))

    (setf (system-modules system) (nreverse (system-modules system)))

    ;; Non-nil defaults.
    (setf (system-lisp-source-type system) lisp-source-type)
    (setf (system-lisp-binary-type system) lisp-binary-type)
    (setf (system-kb-type system) kb-type)
    (setf (system-kl-type system) kl-type)
    (setf (system-pathname system) system-pathname)
    (setf (system-package-name system) system-package-name)
    (setf (system-is-windowless-p system) system-is-windowless-p))
  #-no-macros
  (all-lisp-source-files system t))






;;;; Miscellaneous Compile Functions





;;; The function `compile-bootstrap-and-reboot-all-modules'
;;; compiles the bootstrap module and loads it if :do-not-load-bootstrap
;;; is not in *features*.

(defun-for-macro compile-bootstrap-and-reboot-all-modules
		 (source-pathname target-pathname)
  (format t "~%Compiling: BOOTSTRAP (~s) "
	  (namestring source-pathname))
  (force-output)
  #-no-macros
  (compile-file-function nil source-pathname target-pathname nil t)
  #-no-macros
  (when (and (not (eval-feature :do-not-load-bootstrap))
	     (not last-update-of-bootstrap-compiled-p))
    (setq last-update-of-bootstrap-compiled-p t)
    (format
      t "~%~%BOOTSTRAP was compiled.  We will have to restart the compile.~%")
    (throw 'reboot-all-modules t)))







;;; Check-for-an-actually-existing-module ... checks whether declared-module is
;;; actually one of the modules belonging to the system being loaded, or to one
;;; of the systems it shares binary files with.  If it is not, this returns nil
;;; and, unless silently? is true, gives a warning.  Otherwise, this returns
;;; true.
;;;
;;; This is only used for expanding the macro declare-forward-reference-simple.

(defun-for-macro check-for-an-actually-existing-module
    (declared-module &optional silently?)
  ;; Check for an actually existing module name.
  (cond
    ((member
       declared-module
       (get current-system-being-loaded 'system-lisp-source-files))
     t) ; ok
    ((dolist (system (systems-to-share-binary-files-with
		       current-system-being-loaded))
       (when (member
	       declared-module (get system 'system-lisp-source-files))
	 (return t)))
     t) ; ok
    ((not silently?)
     (warn "DECLARE-FORWARD-REFERENCE:  module ~s is not part of system ~a"
	   declared-module
	   current-system-being-loaded)
     nil)
    (t nil)))

;; Note that just checking for modules in the current system being loaded is a
;; loser in the case of loading Telewindows.  This could be made more efficient;
;; it might be noticeably too slow right now, but I'm not sure.  (MHD 10/21/93)






;;;; Miscellaneous Update Functions


;;; The function `update-bootstrap-and-reupdate-all-modules' calls
;;; copy-file-via-ftp to pull in the bootstrap module from the
;;; master directory, and does a throw to 'reupdate-all-modules indicate
;;; that updates have to occur AFTER bootstrap has been compiled
;;; and loaded (in case there are new modules).

(defun-for-macro update-bootstrap-and-reupdate-all-modules
		 (file-symbol file-class system)
  (ab-lisp::funcall 'copy-file-via-ftp file-symbol file-class system)
  #-no-macros
  (setq last-update-of-bootstrap-compiled-p nil)
  (format
    t
    "~%BOOTSTRAP was updated.  We'll have to compile BOOTSTRAP and restart.~%")
  (throw 'reupdate-all-modules t))











;;;; Gensym Site Specific Code



#-chestnut-trans
(defconstant gensym-networking-library "libtcp.a")

#-chestnut-trans
(defconstant gensym-ssl-stub-library "libnogsec.a")

#-chestnut-trans
(defconstant gensym-cprim-library
  #+(and allegro mswindows) "libcprim.dll"
  #+(and allegro (not mswindows)) "libcprim.so"
  #-allegro "libcprim.a")

#+(and lucid (not chestnut-trans))
(defconstant gensym-lucidsrv-library "lucidsrv.o")

#-chestnut-trans
(defconstant gensym-tw-library
  #+mswindows "twlibs.dll"
  #+darwin "twlibs.dylib"
  #-(or mswindows darwin) "twlibs.so")

#-chestnut-trans
(defconstant gensym-g2-library
  #+mswindows "g2libs.dll"
  #+darwin "g2libs.dylib"
  #-(or mswindows darwin) "g2libs.so")

#-chestnut-trans
(defconstant gensym-gsi-library
  #+mswindows "gsilibs.dll"
  #+darwin "gsilibs.dylib"
  #-(or mswindows darwin) "gsilibs.so")

#-chestnut-trans
(defconstant gensym-fnt-library
  #+(and allegro mswindows) "libfnt.dll"
  #+(and allegro (not mswindows)) "libfnt.so"
  #-allegro "libfnt.a")

#-chestnut-trans
(defconstant gensym-jpeg-library	; Added -fmw, 12/28/01
  #+(and allegro mswindows) "libjpeg.dll"
  #+(and allegro (not mswindows)) "libjpeg.so"
  #-allegro "libjpeg.a")

#-chestnut-trans
(defconstant gensym-xml-library		; Added -jv, 11/11/02
  #+(and allegro mswindows) "liblsxml.dll"
  #+(and allegro (not mswindows)) "liblsxml.so"
  #-allegro "liblsxml.a")

#-chestnut-trans
(defconstant gensym-libxml2-library
  #+mswindows "libxml2_a.lib"
  #-mswindows "libxml2.a")

#-chestnut-trans
(defconstant gensym-ssl-library		; Added -fmw, 6/22/05
  #+(and allegro mswindows) "libssl.dll"
  #+(and allegro (not mswindows)) "libssl.so"
  #-allegro "libssl.a")

#-chestnut-trans
(defconstant gensym-crypto-library	; Added -fmw, 6/22/05
  #+(and allegro mswindows) "libcrypto.dll"
  #+(and allegro (not mswindows)) "libcrypto.so"
  #-allegro "libcrypto.a")

#-chestnut-trans
(defconstant gensym-gcc-library		; Added -fmw, 6/23/05
  #+(and allegro mswindows) nil
  #+(and allegro (not mswindows)) nil
  #-allegro "libgcc.a")

#+(and gsi-web (not chestnut-trans))
(defconstant gensym-gw-library		; Added -jv, 8/17/03
  #+(and allegro mswindows) "libgw.dll"
  #+(and allegro (not mswindows)) "libgw.so"
  #-allegro "libgw.a")


;;; `Call-unix-make-for-g2' makes the appropriate library for G2, GSI, or TW, in
;;; both Lucid (.a) and Allegro (.so) development environments.

(defun-for-macro call-unix-make-for-g2 (system)
  (dolist (entry (case system
		   (gsi
		    `((,gensym-networking-library ext ,lib-objects-directory-name)
		      (,gensym-ssl-stub-library ext ,lib-objects-directory-name)
		      #+gsi-web
		      (,gensym-gw-library gw ,lib-objects-directory-name)
		      ))
		   (ab
		    `((,gensym-cprim-library ext ,lib-objects-directory-name)
		      #+lucid
		      (,gensym-lucidsrv-library ext ,lib-objects-directory-name)
		      (,gensym-fnt-library fnt ,lib-objects-directory-name)
		      (,gensym-xml-library xml ,lib-objects-directory-name)
		      (,gensym-jpeg-library jpeg ,lib-objects-directory-name)))
		   (telewindows
		    `((,gensym-cprim-library ext ,lib-objects-directory-name)
		      #+lucid
		      (,gensym-lucidsrv-library ext ,lib-objects-directory-name)
		      (,gensym-fnt-library fnt ,lib-objects-directory-name)
		      (,gensym-jpeg-library jpeg ,lib-objects-directory-name)))))
    (let* ((library (first entry)) (target (second entry)) (type (third entry))
	   (command-line
	    (format nil "~a/util/sbrunmake ~a ~a ~a ~(~a~) ~(~a~) ~a"
		    toolsdir-name
		    source-directory-name dest-directory-name toolsdir-name
		    target type library)))
      (execute-command-line command-line))))






;;;; Vanilla

(defvar-for-macro signal-missing-vanilla-facility-p nil)

(defun-for-macro signal-missing-vanilla-facility-function 
    (definition-name module-name)
  (if signal-missing-vanilla-facility-p
      (cerror "Continue"
	      "~%Missing VANILLA definition, ~a, in module ~a.~%"
	      definition-name
	      module-name)
      (format t
	      "~%Missing VANILLA definition, ~a, in module ~a.~%"
	      definition-name
	      module-name)))

(defmacro signal-missing-vanilla-facility (definition-name module-name)
  (signal-missing-vanilla-facility-function definition-name module-name))





;;;; Translator

(defvar-for-macro signal-missing-translator-facility-p nil)

(defun-for-macro signal-missing-translator-facility-function (definition-name module-name)
  (if signal-missing-translator-facility-p
      (cerror "Continue"
	      "~%Missing translator definition, ~a, in module ~a.~%"
	      definition-name
	      module-name)
      (warn "Missing translator definition, ~a, in module ~a."
	    definition-name
	    module-name)))

(defmacro signal-missing-translator-facility (definition-name module-name)
  (signal-missing-translator-facility-function definition-name module-name))






;;;; Cars, Cdrs, and Simple Vectors



;;; The macro `car-of-cons' is the same as car except that it assumes its
;;; argument to be a (non-nil) cons.  Carc may be more efficient than car, but
;;; it may also crash if the argument is not a cons.

;;; The macro `cdr-of-cons' is the cdr analog of car-of-cons.

(defmacro car-of-cons (cons)
  (if (eval-feature :development)
      (if (or (symbolp cons) (constantp cons))
	  `(if (atom ,cons)
	       (not-a-cons-error ,cons)
	       (car ,cons))
	  (let ((cons-to-check (gensym)))
	    `(let ((,cons-to-check ,cons))
	       (if (atom ,cons-to-check)
		   (not-a-cons-error ,cons-to-check)
		   (car ,cons-to-check)))))
      #+chestnut-3
      (if (eval-feature :chestnut-trans)
	  `(trun:%m-car ,cons)
	  `(car (the cons ,cons)))
      #-chestnut-3
      `(car (the cons ,cons))))

#+development
(defun not-a-cons-error (thing)
  (error
    "A call to car-of-cons or cdr-of-cons received ~a, which was not a cons."
    thing))

(defmacro setf-car-of-cons (cons value)
  `(setf (car ,cons) ,value))

(defsetf car-of-cons setf-car-of-cons)

(defmacro cdr-of-cons (cons)
  (if (eval-feature :development)
      (if (or (symbolp cons) (constantp cons))
	  `(if (atom ,cons)
	       (not-a-cons-error ,cons)
	       (cdr ,cons))
	  (let ((cons-to-check (gensym)))
	    `(let ((,cons-to-check ,cons))
	       (if (atom ,cons-to-check)
		   (not-a-cons-error ,cons-to-check)
		   (cdr ,cons-to-check)))))
      #+chestnut-3
      (if (eval-feature :chestnut-trans)
	  `(trun:%m-cdr ,cons)
	  `(cdr (the cons ,cons)))
      #-chestnut-3
      `(cdr (the cons ,cons))))

(defmacro setf-cdr-of-cons (cons value)
  `(setf (cdr ,cons) ,value))

(defsetf cdr-of-cons setf-cdr-of-cons)




;;; The macro `length-of-simple-vector' takes a simple-vector and returns its
;;; length.  This macro attempts to optimize this call as much as possible.  The
;;; macro `length-of-simple-string' does the same for simple strings.

(defmacro length-of-simple-vector (simple-vector)
  (if (eval-feature :development)
      (if (symbolp simple-vector)
	  `(if (simple-vector-p ,simple-vector)
	       (length (the simple-vector ,simple-vector))
	       (not-a-simple-vector-error ,simple-vector))
	  (let ((sv (gensym)))
	    `(let ((,sv ,simple-vector))
	       (if (simple-vector-p ,simple-vector)
		   (length (the simple-vector ,sv))
		   (not-a-simple-vector-error ,sv)))))
      `(length (the simple-vector ,simple-vector))))

#+development
(defun not-a-simple-vector-error (x)
  (error "In a call to length-of-simple-vector, ~a was not a simple-vector." x))

(defmacro length-of-simple-string (simple-string)
  (if (eval-feature :development)
      (if (symbolp simple-string)
	  `(if (simple-string-p ,simple-string)
	       (length (the simple-string ,simple-string))
	       (not-a-simple-string-error ,simple-string))
	  (let ((ss (gensym)))
	    `(let ((,ss ,simple-string))
	       (if (simple-string-p ,ss)
		   (length (the simple-string ,ss))
		   (not-a-simple-string-error ,ss)))))
      `(length (the simple-string ,simple-string))))

#+development
(defun not-a-simple-string-error (x)
  (error "In a call to length-of-simple-string, ~a was not a simple-string." x))






;;;; Runtime test for executing Chestnut


(defmacro executing-chestnut? ()
  #+(or chestnut chestnut-3) t ;Chestnut3.1
  #-(or chestnut chestnut-3) nil) ;Chestnut3.1








;;;; TS - Tags Setup


;;; Run "/home/development/scripts/make-tags" to set up your files-in-order.dat,
;;; tags table and ID file.  If you call "/home/development/scripts/make-tags with-directory",
;;; it makes a tags table that explicity includes directories for each file.


;;; `generate-files-in-order' - produces a file of all the lisp modules available,
;;; sorted by load order.  - jv 4/16/98

#+development
(defvar files-in-order-filename "files-in-order.dat")

#+development
(defun generate-files-in-order ()
  (with-open-file (*standard-output* files-in-order-filename
				     :direction :output
				     :if-exists :supersede)
    (dolist (module-list all-modules-of-all-systems)
      (format t "~A.lisp~%"
	      (string-downcase (symbol-name (car module-list)))))))



;;;; New suffixes on Solaris

#-translator
(defparameter message-from-jv-about-4b-files
  "Files ending in 4b and 4cb have been deleted from your Solaris sandbox.
;;;    Solaris Lucid will now use the suffixes 4lb for Lucid binaries (found
;;;    in your DSTBOX lisp/dev directory), and 4rb for Chestnut binaries (found
;;;    in your DSTBOX lisp/macro directory.)  There may also be 4b and 4cb
;;;    files in your SRCBOX lisp directory, for bootstrap, systems, and delta.
;;;    They have not been removed in case you intend to use your sandbox for
;;;    multiple platforms.  If you intend this sandbox for use only on Solaris,
;;;    you should 'rm ${SRCBOX}/lisp/*.4b ${SRCBOX}/lisp/*.4cb'.  You should not
;;;    see this warning again for this sandbox.  - jv
")


#-translator
(defun remove-4b-and-4cb-files (remove-top-level-files-p)
  (let ((old-name-files-exist-p nil))
    (with-faster-standard-output
      (when remove-top-level-files-p
	(let* ((lisp-source-directory
		 (make-pathname
		   :defaults
		   (format nil "~a/~a/" source-directory-name
			   lisp-source-directory-name)))
	       (files-in-lisp-source-directory
		 (directory lisp-source-directory)))
	  (dolist (object-file files-in-lisp-source-directory)
	    (when (or (string= "4b" (pathname-type object-file))
		      (string= "4cb" (pathname-type object-file)))
	      (setq old-name-files-exist-p t)
	      (warn "Deleting Binary File ~s." (namestring object-file))
	      (delete-file object-file)))))
      (let* ((lisp-binaries-directory
	       (make-pathname
		 :defaults
		 (format nil "~a/~a/~a/" dest-directory-name
			 lisp-dest-directory-name
			 standard-lisp-binary-directory-name)))
	     (files-in-lisp-dest-directory
	       (directory lisp-binaries-directory)))
	(dolist (object-file files-in-lisp-dest-directory)
	  (when (string= "4b" (pathname-type object-file))
	    (setq old-name-files-exist-p t)
	    (warn "Deleting Binary File ~s." (namestring object-file))
	    (delete-file object-file))))
      (let* ((lisp-translate-directory
	       (make-pathname
		 :defaults
		 (format nil "~a/~a/~a/" dest-directory-name
			 lisp-dest-directory-name
			 standard-chestnut-binary-directory-name)))
	     (files-in-lisp-translate-directory
	       (directory lisp-translate-directory)))
	(dolist (object-file files-in-lisp-translate-directory)
	  (when (string= "4cb" (pathname-type object-file))
	    (setq old-name-files-exist-p t)
	    (warn "Deleting Binary File ~s." (namestring object-file))
	    (delete-file object-file))))
      (when old-name-files-exist-p
	(warn message-from-jv-about-4b-files)))))

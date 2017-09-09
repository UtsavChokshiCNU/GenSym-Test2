(in-package #-(or SBCL MCL clozure Genera) "USER"
	    #+(or SBCL MCL clozure Genera) "CL-USER")

;; yduJ, 11/16/07

;; run bash
;; cd $SRCBOX/chestnut/src/trans
;; export SBCL_HOME=...
;; invoke sbcl
;; load this file itself:
;; (load "sbcl-load-trans.lisp")
;; Save the resulting image:
;; (sb-ext:save-lisp-and-die "trans-sbcl" :executable t :toplevel #'enter-top-level)

#+sbcl
(setq sb-ext:*evaluator-mode* :interpret
      *compile-print* nil)  ;make a little less noise.

(setq *inhibit-final-translator-initialization* t)

;;; Change this to load the translator from somewhere else.
(defvar *translator-directory* *default-pathname-defaults*)

(load (merge-pathnames "load-trans.lisp" *translator-directory*))

;; -- Girnarsoft -- 
;; -- Bug Id: 21585 --
;; -- Bug Description: Gensym-421-IL-RFP-46684-BF-Chestnut Translator does not
;;    support --disable-debugger
;; Defining function process-toplevel-arg to process the top level commandline
;; arguments that are being ignored by SBCL version of Chestnut translator. In
;; the original SBCL, this processing is done by function: toplevel-init
;; defined in file: sbcl-1.0.25/src/code/toplevel.lisp. --disable-debugger
;; option is a toplevel commandline argument and is handled in this function
;; Most of the code for this newly defined funtion: process-toplevel-arg is 
;; taken from toplevel-init. 
(defun process-toplevel-arg ()
 (let ( ;; value of --sysinit option
        (sysinit nil)
        ;; t if --no-sysinit option given
        (no-sysinit nil)
        ;; value of --userinit option
        (userinit nil)
        ;; t if --no-userinit option given
        (no-userinit nil)
        ;; t if --disable-debugger option given
        (disable-debugger nil)
        ;; list of (<kind> . <string>) conses representing --eval and --load
        ;; options. options. --eval options are stored as strings, so that
        ;; they can be passed to READ only after their predecessors have been
        ;; EVALed, so that things work when e.g. REQUIRE in one EVAL form
        ;; creates a package referred to in the next EVAL form. Storing the
        ;; original string also makes for easier debugging.
        (reversed-options nil)
        ;; Has a --noprint option been seen?
        (noprint nil)
        ;; Has a --script option been seen?
        (script nil)
        ;; everything in *POSIX-ARGV* except for argv[0]=programname
        (options (rest *posix-argv*)))

    (declare (type list options))

    ;; Retaining the comments from the original code [toplevel-init]
    ;; FIXME: There are lots of ways for errors to happen around here
    ;; (e.g. bad command line syntax, or READ-ERROR while trying to
    ;; READ an --eval string). Make sure that they're handled
    ;; reasonably.

    ;; Process command line options.
    (loop while options do
         (let ((option (first options)))
           (flet ((pop-option ()
                    (if options
                        (pop options)
                        (sb-impl::startup-error
                         "unexpected end of command line options"))))
             (cond ((string= option "--script")
                    (pop-option)
                    (setf disable-debugger t
                          no-userinit t
                          no-sysinit t
                          script (pop-option))
                    (return))
                   ((string= option "--sysinit")
                    (pop-option)
                    (if sysinit
                        (sb-impl::startup-error "multiple --sysinit options")
                        (setf sysinit (pop-option))))
                   ((string= option "--no-sysinit")
                    (pop-option)
                    (setf no-sysinit t))
                   ((string= option "--userinit")
                    (pop-option)
                    (if userinit
                        (sb-impl::startup-error "multiple --userinit options")
                        (setf userinit (pop-option))))
                   ((string= option "--no-userinit")
                    (pop-option)
                    (setf no-userinit t))
                   ((string= option "--eval")
                    (pop-option)
                    (push (cons :eval (pop-option)) reversed-options))
                   ((string= option "--load")
                    (pop-option)
                    (push (cons :load (pop-option)) reversed-options))
                   ((string= option "--noprint")
                    (pop-option)
                    (setf noprint t))
                   ((string= option "--disable-debugger")
                    (pop-option)
                    (setf disable-debugger t))
                   ((string= option "--end-toplevel-options")
                    (pop-option)
                    (return))
                   (t
                    ;; Anything we don't recognize as a toplevel
                    ;; option must be the start of user-level
                    ;; options.. except that if we encounter
                    ;; "--end-toplevel-options" after we gave up
                    ;; because we didn't recognize an option as a
                    ;; toplevel option, then the option we gave up on
                    ;; must have been an error. (E.g. in
                    ;;  "sbcl --eval '(a)' --eval'(b)' --end-toplevel-options"
                    ;; this test will let us detect that the string
                    ;; "--eval(b)" is an error.)
                    (if (find "--end-toplevel-options" options
                              :test #'string=)
                        (sb-impl::startup-error "bad toplevel option: ~S"
                                       (first options))
                        (return)))))))

    ;; Delete all the options that we processed, so that only
    ;; user-level options are left visible to user code.
    (setf (rest *posix-argv*) options)

    ;; Disable debugger before processing initialization files & co.
    (when disable-debugger
      (sb-ext:disable-debugger))

    ;; Handle initialization files.
    (unless no-sysinit
      (sb-impl::process-init-file sysinit :system))
    (unless no-userinit
      (sb-impl::process-init-file userinit :user))
    (sb-impl::process-eval/load-options (nreverse reversed-options))
    (when script
              (sb-impl::process-script script)
              (bug "PROCESS-SCRIPT returned"))
))

(defun enter-top-level ()
  ;;Initialize translator
  (timpl::final-initialization)
  ;;Handle the toplevel commandline args
  (process-toplevel-arg)
  ;;Run SBCL's regular top-level.
  (sb-impl::repl-fun nil))

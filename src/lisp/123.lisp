;; -*- Mode: Lisp; Package: User; Base: 10; Syntax: Common-Lisp -*-
(in-package #+ANSI-CL "CL-USER" #-ANSI-CL "USER")

;;;; Module 123

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David and Ong, Peng Tsin


;;; Stop from compile this file  -- Chun Tian (binghe), 2009/10/9
(eval-when (:compile-toplevel)
  (error "DO NOT COMPILE THIS FILE (123.lisp) PLEASE!"))

;;; suppress the error like "Redefining function COMMON-LISP:GENSYM visible from package COMMON-LISP."
#+lispworks
(setq lw:*handle-warn-on-redefinition* :warn)

#+ecl
(require :cmp)

;#+sbcl
;(require :sb-sprof)

;; NOTE: I removed support for demo compiles from this module.  Places
;; that used to have support for demo compiles now have text like
;; "reserved for future use" around them.  (MHD 10/12/90)

;; Switches and What They Control
;; ...
;; Switch L - Prompt for command LINE, e.g., "tw d-day.gensym.com  1111"
;; Switch M - no-make
;; Switch P - no-process
;; Switch R - recompile
;; Switch U - multithreaded G2
;; Switch Y - include unit-tests
;; ...
;; Switch I - INCREMENTAL translations
;; Switch Q - Quits Lisp when done
;; [FINISH DOCUMENTING!]

(defvar *dest-macro-directory-name* "g2")

(defun remove-binary-files-from-working-directory (&aux working-directory)
  (setq working-directory
        (make-pathname :name :wild
                       :type :wild
                       :directory (list :relative :up :up "dst" "lisp" *dest-macro-directory-name*)
                       :defaults (or *load-pathname* *default-pathname-defaults*)))
  (format t "Working directory: ~A~%" working-directory)
  (dolist (lispdir-file (directory working-directory))
    (let ((suffix (pathname-type lispdir-file)))
      (when (or (string= "5lb" suffix)
                #+sbcl
                (string= "fasl" suffix)
                #+lispworks
                (string= system:*binary-file-type* suffix)
                #+clozure
                (string= (subseq (namestring ccl:*.fasl-pathname*) 1) suffix)
                (string= "5rb" suffix)
                (string= "4b" suffix)
                (string= "4cb" suffix)
                (string= "sbin" suffix)
                (string= "fsl" suffix))
        (warn "Deleting Binary File ~s." (namestring lispdir-file))
        (delete-file lispdir-file)))))



;; The following are necessary for getting and parsing the
;; command line arguments if present.

(defmacro get-native-command-line-argument (arg-number)
  #+lucid
  `(lucid::%get-command-line-argument ,arg-number)
  #+sbcl
  `(nth ,arg-number sb-ext:*posix-argv*)
  #+lispworks
  `(nth ,arg-number system:*line-arguments-list*)
  #+clozure
  `(nth ,arg-number ccl:*command-line-argument-list*))

(defun convert-option-and-switches-to-list (option-and-switches)
  (let* ((number-of-option-and-switches (length option-and-switches))
         (list-of-option-and-switches nil)
         next-option-or-switch)
    (dotimes (i number-of-option-and-switches)
      (if (= i 0)
          (setq next-option-or-switch
                (digit-char-p (char option-and-switches i)))
          (setq next-option-or-switch
                (intern (string-upcase
                          (char option-and-switches i)))))
      (setq list-of-option-and-switches
            (cons next-option-or-switch list-of-option-and-switches)))
    (reverse list-of-option-and-switches)))

;;; feature: ignore non-option command-line arguments added by CL
;;; implementations or others. -- Chun Tian (binghe), 2010/8/16

(defun option-string-p (options)
  (declare (type string options))
  (and (digit-char-p (char options 0))
       (every #'alpha-char-p (subseq options 1))))

(defun get-command-line-option-and-switches ()
  (labels ((try-next (index)
             (let ((options #+(or lucid sbcl lispworks clozure)
                            (get-native-command-line-argument index)
                            #-(or lucid sbcl lispworks clozure)
                            nil))
               (when (stringp options)
                 (if (option-string-p options)
                     options
                   (try-next (1+ index)))))))
    (try-next 1)))

(defun print-menu ()
  (format t "
  Type an option (number) followed by one or more switches (letters):

      0. Quit
      1. Development Compile             2. Development Load
      3. Distribution Compile            4. Distribution Load
      7. Macro Compile                   8. Macro Load
      9. Get Updates Only

      S. SymScale G2                     E. Enable Code Coverage
      T. TELEWINDOWS (instead of G2)     G. GSI (instead of G2)
      W. G2 WebLink (GW)                 N. Licensing Server (LS)
      U. Multi-threaded G2 (MTG2)        Y. Include Lisp Unit Tests

      D. DUMB (silent) mode              V. VERBOSE compile mode
      R. RECOMPILE all files             P. No PROCESS
      C. CLOCK (time) what gets done     M. Skip MAKE of C (ext) code
      Q. QUIT Lisp when done             L. Prompt for command LINE

      ~:[~;~
      X. Translate all files             Z. Translate using prepare-file only
      A. Analyze translated calls~]

      "
          (member ':translator-is-loaded *features*)))

(declaim (ftype (function (string &optional boolean) t) parse-123-selection))

(defun print-menu-and-input-selection ()
  (do ((need-to-display-menu?
         (loop unless (listen)
                 do (return t)
               unless (member (peek-char nil t nil) '(#\space #\tab #\newline))
                 do (return nil)
               do (read-char))))
      (nil)
    (when need-to-display-menu?
      (print-menu)
      (setq need-to-display-menu? nil))
    (format t "~&~3tOption and switches: ")
    (force-output)
    (finish-output)
    (let* ((line (read-line))
           (option-and-switches-or-illegal-entry-string
             (parse-123-selection line)))
      (unless (equal option-and-switches-or-illegal-entry-string "")
        (if (stringp option-and-switches-or-illegal-entry-string)
            (if (string-equal option-and-switches-or-illegal-entry-string "?")
                (setq need-to-display-menu? t)        ; advertise ? in menu?
                (format t "~&~3T~A~&"
                        option-and-switches-or-illegal-entry-string))
            (return option-and-switches-or-illegal-entry-string))))))

;;; Parse-123-selection returns either string, if it could not be parsed, or
;;; a cons of the form
;;;
;;;    (option? . switches)
;;;
;;; provided that string contains a legal string of options and switches.
;;; Option? is either nil or an integer corresponding to a legal 123 option.
;;; Switches is a list of 0 or more one-letter symbols corresponding to legal
;;; options.

;;; String may have whitespace chars leading, trailing, or interspersed among
;;; the option and switches.

;;; The option may not appear if allow-not-to-have-option? is true and must
;;; appear otherwise. If it does appear, it must precede the switches, if
;;; any, in the string.  At most one option is allowed and it may only appear
;;; once.  Note that option? may be nil in the parse only if allow-not-to-have-
;;; option? is specified true.

;;; Duplicate switches are accepted, but they are removed from the final parse.

(defun parse-123-selection (string &optional allow-not-to-have-option?)
  (let ((string (delete-if #'(lambda (char) (member char '(#\space #\tab)))
                           string)))
    (if (zerop (length string))
        ""
        (let* ((first-char-as-digit (digit-char-p (char string 0)))
               (option-p (and first-char-as-digit
                              (<= first-char-as-digit #+lucid 9 #-lucid 8)
                              (not (member first-char-as-digit
                                           '(5 6)))))) ; reserved for future use
          (if (not (or option-p allow-not-to-have-option?))
              (if first-char-as-digit
                  "Invalid option digit"
                  "Missing option digit")
              (do* ((switches nil)
                    (length (length string))
                    (i (if option-p 1 0) (+ i 1)))
                   ((= i length)
                    (return (cons first-char-as-digit (remove-duplicates switches))))
                (let* ((char (char string i))
                       (char-string (string char)))
                  (unless (member char
                              '(#\t #\g #\s #\w #\n
                                #\r #\p #\c #\x #\m #\a
                                #\i #\e #\y 
                                #\d #\v #\k #\u #\z
                                #\q #\l)
                              :test #'char-equal)
                    (return (format nil "Illegal switch: ~S" char-string)))
                  (setq switches
                        (nconc switches
                               (list
                                 (intern (string-upcase char-string))))))))))))

;; Consider flushing allow-not-to-have-option? eventually, since it is not now
;; used.

;; Load.lisp is in the same folder 123.lisp is.
(defparameter load-module-pathname? 
  (make-pathname :name "load" :type "lisp" :defaults *load-truename*))

#+chestnut-3
(progn
  (defvar filemap-backup-module-pathname?)
  (setq filemap-backup-module-pathname? nil)
  (defvar filemap-module-pathname?)
  (setq filemap-module-pathname? nil)
  (defvar symbolmap-backup-module-pathname?)
  (setq symbolmap-backup-module-pathname? nil)
  (defvar symbolmap-module-pathname?)
  (setq symbolmap-module-pathname? nil)
  (defvar utables-backup-module-pathname?)
  (setq utables-backup-module-pathname? nil)
  (defvar utables-module-pathname?)
  (setq utables-module-pathname? nil))

(defun leave ()
  #-sbcl
  (quit)
  #+sbcl
  #.(let ((exit (find-symbol "EXIT" :sb-ext))
	  (quit (find-symbol "QUIT" :sb-ext)))
      (cond
	(exit `(sb-ext:exit))
	(quit `(sb-ext:quit)))))

(defun g2menu (&optional (command-line-args nil))
  (let* ((parsed-123-option-and-switches
          (if command-line-args
              command-line-args
              (print-menu-and-input-selection)))
         (option (car parsed-123-option-and-switches))
         (switches (cdr parsed-123-option-and-switches))
         (system-to-load 'g2)
         (boot-system-options
          (case option
            ((1 3 5 7)
             (nconc
              (list 'compile)
              (case option
                ((3 5 7)
                 (list
                  'all-optional-modules
                  'destination :default-macro-directory)))
              (case option
                ((3 5)
                 (list 'distribute :default-dst-directory)))
              (case option
                (5 nil))                ; reserved for future use
              (case option
                (7
                 (list 'macros-only)))))
            (4
             (list
              'all-optional-modules
              'destination :default-dst-directory))
            (6 nil)                     ; reserved for future use
            (8
             (list
              'macros-only
              'all-optional-modules
              'destination :default-macro-directory))
            (9 (list 'compile 'updates-only))))
         (no-make-p nil)
         (no-process-p nil))
    (unless (= option 0)                ; 0 => quit
      (dolist (switch switches)
        (case switch
          ;; specify system
          ((t)
           (setq system-to-load 'telewindows)
           (setf *dest-macro-directory-name* "tw")
           (format t "~%  T - Telewindows to be loaded/compiled/updated."))
          (g
           ;; maybe should *remove* :gsi-web from features here?
           (setq system-to-load 'gsi)
           (setf *dest-macro-directory-name* "gsi")
           (format t "~%  G - GSI extension to be loaded/compiled/updated."))
          (w
           (pushnew :gsi-web *features*)
           (setq system-to-load 'gsi)
           (setf *dest-macro-directory-name* "gw")
           (format t "~%  W - WebLink to be loaded/compiled/updated."))
          (n
           (setq system-to-load 'ls)
           (format t "~%  N - ..."))
          (s
           #+(and translator-is-loaded (not translator-supports-thread))
           (error "SymScale is NOT supported by this translator, use multithreading one instead.")
           (pushnew :SymScale *features*)
           (setf *dest-macro-directory-name* "symscale")
           (format t "~%  S - SymScale G2 to be loaded/compiled/updated."))
          (u
           #+(and translator-is-loaded (not translator-supports-thread))
           (error "MTG2 is NOT supported by this translator, use multithreading one instead.")
           (pushnew :mtg2 *features*)
           (setf *dest-macro-directory-name* "mtg2")
           (format t "~%  U - MTG2 to be loaded/compiled/updated."))
	  (y
	   (pushnew :g2-lisp-unit *features*)
           (format t "~%  Y - unit tests to be loaded/compiled/updated."))
          ;; commonly used options
          (r
           (push 'recompile boot-system-options)
           (format t "~%  R - Recompiling all files."))
          (p
           (setq no-process-p t)
           (push 'no-process boot-system-options)
           (format t "~%  P - With no process started after load or compilation."))
          (c
           (format t "~%  C - Will clock (i.e. time) what gets done."))
          (x
           (pushnew :translate-all *features*)
           (format t "~%  X - Translate all lisp files."))
          (m
           (setq no-make-p t)
           (push 'no-make boot-system-options)
           (format t "~%  M - Suppress invoking the make that builds the C object library."))
          (a
           (push 'analyze-calls boot-system-options)
           (format t "~%  A - Write analysis of calls, after translation."))
          (e
           #+clozure
           (setq ccl:*compile-code-coverage* t)
           #+lispworks7
           (hcl:generate-code-coverage :atomic-p t :counters t)
           (format t "~%  E - Enable Code Coverage."))
          ;; probably obsolete, but still used by the eternal recompile
          (i
           (pushnew 'incremental boot-system-options)
           (format t "~%  I - Utables will be loaded with recompile."))

          ;; largely unused and/or undocumented
          (d
           (push 'silent boot-system-options)
           (format t "~%  D - Will be dumb (i.e. silent) as much as possible."))
          (v
           (push 'verbose boot-system-options)
           (format t "~%  V - Will allow all verbose messages."))
          (k
           (push 'kanji boot-system-options)
           (push 'kfep boot-system-options)
           (format t "~%  K - Including KFEP and kanji fonts."))
          (o
           (push 'no-updates boot-system-options)
           (format t "~%  O - No updates from the master directory."))
          (z
           (push 'prepare-only boot-system-options)
           (format t "~%  Z - Only run prepare-file, do not run translate-file."))

          ;; more options handled later
          (q
           (format t "~%  Q - Will quit when done."))
          (l
           (format t "~%  L - Will now prompt for a command line."))))
      (format t "~%~%")
      (remove-binary-files-from-working-directory)

      (if (probe-file load-module-pathname?)
          (progn
            (setq *features* (delete :development *features*))
            (setq *features* (delete :distribution *features*))
            (setq *features* (delete :no-macros *features*))
            (setq *features* (delete :non-development-macros *features*))
            (when (= option 1)
              (pushnew :debug-build *features*))		;for DEBUG build (1rpm)
            (load load-module-pathname?))
          (error "Can't find file load.lisp."))

      #+chestnut
      (progn
        (setq utables-module-pathname?
              (probe-file
               (case system-to-load
                 (g2 #p"g2-utables.lisp")
                 (telewindows #p"tw-utables.lisp"))))
        (setq utables-backup-module-pathname?
              (case system-to-load
                (g2 "g2-utables.bak")
                (telewindows "tw-utables.bak")))
        (setq filemap-module-pathname?
              (probe-file
               (case system-to-load
                 (g2 "g2-files.log")
                 (telewindows "tw-files.log"))))
        (setq filemap-backup-module-pathname?
              (case system-to-load
                (g2 "g2-files.bak")
                (telewindows "tw-files.bak")))
        (setq symbolmap-module-pathname?
              (probe-file
               (case system-to-load
                 (g2 "g2-symbols.log")
                 (telewindows "tw-symbols.log"))))
        (setq symbolmap-backup-module-pathname?
              (case system-to-load
                (g2 "g2-symbols.bak")
                (telewindows "tw-symbols.bak"))))

      #+chestnut-3                      ;Chestnut3.1
      (progn
        (setq utables-module-pathname? nil)
        (setq utables-backup-module-pathname? nil)
        (setq filemap-module-pathname? nil)
        (setq filemap-backup-module-pathname? nil)
        (setq symbolmap-module-pathname? nil)
        (setq symbolmap-backup-module-pathname? nil))

      #+(or chestnut chestnut-3)        ;Chestnut3.1
      (progn
        (when (and (member 'incremental boot-system-options)
                   (not (member 'recompile boot-system-options)))
          (format t "~%~a~%~a~%~a~%"
                  ";;; Ignoring \"I\" (Incremental) option.  Specifiy the \"I\""
                  ";;; option only in combination with the \"R\" option when incremental"
                  ";;; C compiles are desired."))
        (if (or (not (member 'recompile boot-system-options))
                (and (member 'recompile boot-system-options)
                     (member 'incremental boot-system-options)))
            (if utables-module-pathname?
                (load utables-module-pathname?))
            (progn
              (when symbolmap-module-pathname?
                (format t ";;; Recompile: moving symbol map file to ~a.~%"
                        symbolmap-backup-module-pathname?)
                (rename-file symbolmap-module-pathname?
                             symbolmap-backup-module-pathname?))
              (when filemap-module-pathname?
                (format t ";;; Recompile: moving file map file to ~a.~%"
                        filemap-backup-module-pathname?)
                (rename-file filemap-module-pathname?
                             filemap-backup-module-pathname?))
              (when utables-module-pathname?
                (format t ";;; Recompile: moving utables file to ~a.~%"
                        utables-backup-module-pathname?)
                (rename-file utables-module-pathname?
                             utables-backup-module-pathname?)))))


      ;; Set up *features* for distribution if nec. [Do this in BOOTSTRAP?!]
      (if (member option '(3 4 5 6 7 8))
          (pushnew :distribution *features*))

      (when (member 'l switches)
        (format t "~%Enter command line: ")
        (force-output t)
        (let ((command-line (read-line)))
          (format t "Command line: ~s~%" command-line)
          (push command-line boot-system-options)))

      ;; Boot system:
      (let* ((result
              (case system-to-load
                (g2
		 ;(sb-sprof:start-profiling)
                 (if (member 'c switches)
                     (time
                      (let ((start-time (get-universal-time)))
                        (unwind-protect
                             (progn
                               (apply 'make-g2 boot-system-options)
                               (room t)
                               (setq start-time nil))
                          (when start-time
                            (format t "~2%Interrupted after ~D seconds~2%"
                                    (- (get-universal-time) start-time))))))
                     (apply 'make-g2 boot-system-options))
		 ;(sb-sprof:stop-profiling)
		 ;(sb-sprof:report :type :flat)
		 )
                (telewindows
                 (if (member 'c switches)
                     (time (apply 'make-telewindows boot-system-options))
                     (apply 'make-telewindows boot-system-options)))
                (gsi
                 (if (member 'c switches)
                     (time (apply 'make-gsi boot-system-options))
                     (apply 'make-gsi boot-system-options)))
                (ls
                 (if (member 'c switches)
                     (time (apply 'make-ls boot-system-options))
                     (apply 'make-ls boot-system-options))))))

        (when result
          (if (member 'q switches)      ; quit when done
	      (leave)))))))

(defun start-with-command-line-args-or-menu ()
  (let* ((command-line-args (get-command-line-option-and-switches))
         (option-and-switches-list
	  (convert-option-and-switches-to-list command-line-args)))
    (if command-line-args
        (progn
          (pushnew :do-not-check-for-aborts *features*)
          (g2menu option-and-switches-list)
          (format t "~&PROCESS-FINISHED: ~%")
	  (leave))
        (progn
          (g2menu option-and-switches-list)
          (format t "~&PROCESS-FINISHED: ~%")))))

#-under-test
(start-with-command-line-args-or-menu)

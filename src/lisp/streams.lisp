;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-lisp -*-
(in-package "AB")

;;;; Module STREAMS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved

;;; John Hodgkinson

;; 31 Oct 1991




;; This module makes the old STREAMS code more manageable and adds
;; better error reporting.  Spun off from STREAMS #459, 10/31/91.  Note
;; that this module provides the interface to the underlying file I/O
;; machinery that PATHNAMES uses.

;; #+Lisp code removed.  Explicity #-lispm's removed.  Not all #+/-lispm
;; comments removed.  This simplified converstion to Unicode and wide
;; strings. (MHD 2/9/96)



;;;; Overview

;;; `G2-streams' are data structures (or other objects) that are used to maintain
;;; file streams.  The g2-stream-close function reclaims them, and the
;;; g2-stream-open functions (or macros) create them. ...

;;; The following are basic file stream operations.  Unless marked with [macro],
;;; they are all functions.  As well, for every operation named "XXX" there is a
;;; macro version named "XXX-MACRO".

;;;   - predicates -
;;; g2-stream-p (thing)
;;; g2-stream-eof-p (g2-stream)
;;; identical-g2-streams-p (g2-stream-1 g2-stream-2)

;;;   - reclamation -
;;; g2-stream-reclaim (g2-stream)
;;; g2-stream-close (g2-stream)

;;;   - assuring disc I/O -
;;; g2-stream-flush (g2-stream)
;;; g2-stream-sync (g2-stream)

;;;   - creating  -
;;; g2-stream-open-for-input (namestring)
;;; g2-stream-open-for-output (namestring)
;;; g2-stream-open-for-binary-output (namestring)
;;; g2-stream-open-for-appending (namestring create-if-does-not-exist-p)
;;; g2-stream-open-for-random-access-io (filename)
;;; g2-stream-open-for-random-access-binary-io (filename)
;;; g2-stream-open-for-random-access-binary-input (filename)
;;; g2-stream-open-for-binary-appending (filename)
;;; g2-stream-flip-bidirectional-stream (g2-stream)
;;; g2-stream-with-open-stream [macro] (specs &rest body)
;;; g2-stream-probe-file-for-exist (string)
;;; g2-stream-probe-file-for-read (string)
;;; g2-stream-probe-file-for-write (string)

;;;   - reading -
;;; g2-stream-read-char (g2-input-stream)
;;; g2-stream-read-ascii-byte (g2-stream)
;;; g2-stream-read-into-string (input-stream buffer char-count start-index)
;;; g2-stream-read-line (g2-input-stream)
;;; g2-stream-read-into-buffer(buffer-string buffer-length g2-stream)
;;; g2-stream-read-into-byte-vector(byte-vector buffer-length g2-stream)

;;;   - writing -
;;; g2-stream-write-char (character g2-output-stream)
;;; g2-stream-terpri (g2-output-stream)
;;; g2-stream-write-ascii-byte (ascii-byte g2-stream)
;;; g2-stream-write-string (string g2-output-stream)
;;; g2-stream-write-line (string g2-output-stream)
;;; g2-stream-write-from-buffer(buffer-string buffer-length g2-stream)

;;;   - directories -
;;; g2-stream-delete-file (namestring)
;;; g2-stream-rename-file (namestring-of-old-file namestring-of-new-file)
;;; g2-stream-copy-file (namestring-of-old-file namestring-of-new-file)
;;; g2-stream-directory (directory-substring name-substring file-system-symbol)
;;; g2-stream-subdirectories (dirspec filespec)
;;; g2-stream-devices ()
;;; g2-stream-get-default-directory ()
;;; g2-stream-change-default-directory (new-directory-string)


;;;   - file attributes -
;;; g2-stream-file-length (g2-stream)
;;; g2-stream-set-file-position (g2-stream new-position seek-mode)
;;; g2-stream-get-file-position (g2-stream)
;;; g2-stream-get-version (string)
;;; g2-stream-get-device (string)
;;; g2-stream-available-disk-space-in-device (filestring)
;;; g2-stream-file-modification-date (filestring)
;;; g2-stream-file-access-date (filestring)
;;; g2-stream-file-status-change-date (filestring)
;;; g2-stream-logical-name-p (string)
;;; g2-stream-maximum-file-name-length (directory-namestring)


;; To do:

;; We have to think about how to decouple the read call and the return from a read
;; call with the returned values.  For example, the read-line function could be:
;; (spawn-g2-stream-read-line <stream> <function-to-call>) where <stream> is the
;; input stream, and <function-to-call> is the one arguement function which takes
;; the read-string or nil if an error occurs.  Of course on non-multiprocessing
;; systems (i.e.  the Mac), this would be equivalent to: (<function-to-call>
;; (g2-stream-read-line <stream>)).  We should define our stream handling
;; functions (or macros) so they work with a fixed number of parameters.  Also,
;; reclaimable items (strings in particular) will have to be reclaimed in the
;; call-back function.  A prototype exists.  jh, 10/31/91.

;; Also, the functions (or macros) that write in this module do not check for
;; errors.  This should be done when we have better I/O functions (or macros).
;; -pto 18oct88.  Done.  jh, 11/1/91.

;; Consider using block reads to perform read-lines.  It is expensive to call the
;; foreign read character function many times while performing a read-line.  -pto
;; 31oct88.  C does fairly efficient buffering, though we should still look into
;; this in the background.  jh, 11/3/91.


;;;; STREAMS Feature Setup

;; Previously, we had a bundle of platform-specificities to cope with.  Now we
;; only have to differentiate Lisp Machines from everything else.  jh, 10/31/91.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :c-streams *features*)
)




;;;; Forward References

(declare-forward-references (:suppress-module-checks-for gsi)
  (log-file-default-pathname?         variable BOOKS)
  (current-foreign-image-pathname?    variable KB-LOAD1)
  (current-attribute-file-pathname?   variable KB-LOAD1)
  (current-statistics-file-pathname?  variable KB-LOAD1)
  (current-kb-pathname?               variable KB-LOAD1)
  (get-users-editing-module-file      function KB-LOAD1)
  (get-port-number-or-name-lisp-side  function FILE-SYSPROC)
  )

(declare-forward-references
  (g2-identification-for-write-locks  function INT3B)
  (use-unicode-for-filenames?-from-system-table  function GRAMMAR7)
  )


;;;; STREAMS cons pool

(defconser streams)

;; Need the following two functions due to a forward reference to the streams
;; defconser macros with-protected-streams macroexpansion in PLATFORMS.
;; (jh, 7/10/90)

(defun copy-list-using-streams-conses-function (streams-list)
  (copy-list-using-streams-conses streams-list))

(defun reclaim-streams-list-function (streams-list)
  (reclaim-streams-list streams-list))


;;;; Streams structure

;; jh, 4/26/96.  we are moving to Unicode and consequently revisiting our policy
;; around converting strings from the outside world.  One upshot of this is the
;; need to associate more information with the g2-stream data type.
;; Specifically, we would like to know the character encoding of the stream
;; source and sink, as well as the policy for handling conversion problems
;; (signal, elide, what have you).  So it is time for g2-stream-structure.  The
;; slots of this structure have no use as yet; this awaits further design by
;; mhd.

(def-structure (g2-stream-structure
                 (:constructor
                   make-g2-stream-structure-internal
                   (g2-stream-handle)))
  g2-stream-handle ;fixnum, the old "g2-stream" we get from C
  g2-stream-source-encoding
  g2-stream-sink-encoding
  g2-stream-conversion-policy
  )

(defmacro make-g2-stream (g2-stream-handle)
  `(make-g2-stream-structure-internal ,g2-stream-handle))





;;;; Integration with Gensym-pathnames

;;; The variable `maximum-file-name-length?' is a platform specific, maximum
;;; number of characters per file name.  If this value is nil, the maximum has not
;;; been determined or is quite long.

(defun initialize-maximum-file-name-length? ()
  (if (eq g2-operating-system 'dos)
      8
      (case g2-machine-type
        (hp9000s300 14)
        (otherwise nil))))

(defvar maximum-file-name-length? (initialize-maximum-file-name-length?))

;; mhd, cpm, & jh, 5/31/91.  Changed maximum-file-name-length?  from a constant to
;; a system variable because we no longer can determine this at compile time.
;; This is because translation to C occurs on platform which is not necessarily
;; the same as the platform on which the image will run.

;; jh, 9/12/91.  Updated maximum-file-name-length?  and its initializer to reflect
;; the new order.  Specifically, the HPs are the only platform that truncates
;; filenames and dispatching on g2-machine-type is now preferred over
;; feature-case.

;; jh, 10/20/91.  Maximum-file-name-length?  should be renamed
;; maximum-local-filename-length?  to provide for the possibility of remote file
;; access.

;; jv, 7/27/07.  Current file systems still do, in fact, have limits on filename
;; length.  But this variable was never used for large limits.  It was only here
;; because DOS had a limit of 8 and HP300 had a limit of 14.  "nil" never truly
;; meant "no limit", it just meant, as the above comment suggests, "quite long".


;;;; Pseudo File Systems

;;; It can be helpful to change the file parser of G2 without changing the
;;; underlying file system.  The development-only functions
;;; `set-up-pseudo-file-system' and `restore-real-file-system' serve this
;;; purpose.  Many points where filenames make contact with the real file system
;;; have been modified to allow a development-only conversion into something
;;; plausible enough to aid debugging, using the functions
;;; `transform-filestring-from-pseudo-file-system' (for arguments) and
;;; `transform-filestring-to-pseudo-file-system' (for results).  The new
;;; g2-stream-operation pseudo-declaration var-is-file-namestring is the way to
;;; to convert the arguments of a g2-stream function into namestrings that are
;;; meaningful in the native file system.  This pseudo-declaration is
;;; implemented using `intercept-filename-args-in-g2-stream-operation'.  In
;;; contrast to arguments, converting the result of g2-stream functions is
;;; case-by-case, since there are only a handful (as of 8/19/94,
;;; g2-stream-directory, g2-stream-subdirectories, and
;;; g2-stream-get-default-directory).

;; jh, 10/7/94.  Have not yet modified the foreign function machinery to use
;; pseudo file systems as of this date.

;;; Don't set `file-system-for-interception?' yourself; instead, use
;;; set-up-pseudo-file-system and restore-real-file-system as appropriate.

(defvar-for-development file-system-for-interception? nil)

#+development
(defun modify-gensym-pathname-file-system-info (gensym-pathname file-system)
  (setf (gensym-pathname-file-system gensym-pathname) file-system)
  (setf (gensym-pathname-filename-parser gensym-pathname)
        (filename-parser-of-file-system file-system))
  (setf (gensym-pathname-namestring-generator gensym-pathname)
        (namestring-generator-of-file-system file-system)))

#+development
(defun transform-filestring-from-pseudo-file-system (filestring)
  (let ((transformed-pathname
          ;; jh, 11/21/94.  DOS the only file system we use that limits filename
          ;; length, but we don't want to limit a Gensym wildcard expression
          ;; like "{kK}{lL}".  This is not a problem outside development because
          ;; users cannot reach the underlying filesystem with a Gensym wildcard
          ;; expression -- they must go through the file command editor or
          ;; directory-giving system procedures, which impose the user-specified
          ;; wildcard filtering only after obtaining the native pathnames.
          (if (and (wild-regular-expression-string-p filestring)
                   (eq local-file-system 'dos))
              (let ((limit-dos-filename-component-lengths-p nil)
                    (allow-extensionless-dos-filenames-p t)
                    (character-case-mode-for-generalized-dos
                      :all-uppercase))
                (parse-generalized-dos-filename filestring))
              (gensym-pathname filestring))))
    (modify-gensym-pathname-file-system-info
      transformed-pathname
      file-system-for-interception?)
    (let ((transformed-namestring (gensym-namestring transformed-pathname)))
      (reclaim-gensym-pathname transformed-pathname)
      (if (and (convert-file-strings-to-uppercase-p local-file-system)
               (not (convert-file-strings-to-uppercase-p
                      file-system-for-interception?)))
          (nstring-downcasew transformed-namestring)
          transformed-namestring))))

#+development
(defun transform-filestring-to-pseudo-file-system (filestring)
  (let ((transformed-pathname
          (convert-to-gensym-pathname-with-known-parser
            filestring
            (filename-parser-of-file-system file-system-for-interception?)
            (namestring-generator-of-file-system
              file-system-for-interception?))))
    (modify-gensym-pathname-file-system-info
      transformed-pathname
      local-file-system)
    (let ((transformed-namestring (gensym-namestring transformed-pathname)))
      (reclaim-gensym-pathname transformed-pathname)
      transformed-namestring)))

;; In `intercept-filename-args-in-g2-stream-operation', form must return single
;; value, form must not reclaim any filename-arg.

(defun-for-macro intercept-filename-args-in-g2-stream-operation
    (filename-args form)
  (if (eval-feature :development)
      `(prog2
           (when file-system-for-interception?
             ,@(loop for filename-arg in filename-args
                     collect
                     `(setq ,filename-arg
                            (transform-filestring-from-pseudo-file-system
                              ,filename-arg))))
           ,form
         (when file-system-for-interception?
           ,@(loop for filename-arg in filename-args
                   collect
                   `(reclaim-text-string ,filename-arg))))
      form))

#+development
(defun bash-stored-pathname-state ()
  (macrolet ((bash-stored-pathname (stored-pathname-var?)
               `(when (and (boundp ',stored-pathname-var?)
                           ,stored-pathname-var?)
                  (cond
                    ((gensym-pathname-p ,stored-pathname-var?)
                     (modify-gensym-pathname-file-system-info
                       ,stored-pathname-var?
                       local-file-system))
                    ((text-string-p ,stored-pathname-var?)
                     (let ((new-pathname
                             (gensym-pathname ,stored-pathname-var?)))
                       (reclaim-text-string ,stored-pathname-var?)
                       (setq ,stored-pathname-var? new-pathname)))
                    (t (cerror "bash-stored-pathname-state: thing ~s ~
                                is neither a string nor a gensym-pathname"
                               ,stored-pathname-var?))))))
    (bash-stored-pathname process-specific-system-pathname)
    (bash-stored-pathname current-foreign-image-pathname?)
    (bash-stored-pathname current-attribute-file-pathname?)
    (bash-stored-pathname current-statistics-file-pathname?)
    (bash-stored-pathname current-kb-pathname?)
    (bash-stored-pathname log-file-default-pathname?)))

#+development
(defun set-up-pseudo-file-system (file-system-to-emulate)
  (unless (memq file-system-to-emulate all-known-file-systems)
    (error "SET-UP-PSEUDO-FILE-SYSTEM: unknown file system ~a"
           file-system-to-emulate))
  (setq file-system-for-interception? local-file-system)
  (setq local-file-system file-system-to-emulate)
  (setq local-filename-parser
        (filename-parser-of-file-system file-system-to-emulate))
  (setq local-namestring-generator
        (namestring-generator-of-file-system file-system-to-emulate))
  (bash-stored-pathname-state)
  file-system-to-emulate)

#+development
(defun restore-real-file-system ()
  (setq file-system-for-interception? nil)
  (setq local-file-system (initialize-local-file-system))
  (setq local-filename-parser (initialize-local-filename-parser))
  (setq local-namestring-generator
        (initialize-local-namestring-generator))
  (bash-stored-pathname-state)
  local-file-system)






;;; Associating Gensym-pathnames with G2-streams (a.k.a. Truenaming)

(def-system-variable g2-stream-all-open-streams STREAMS nil nil t)

;;; Instead of constant queue, this looks more like a BINARY-TREE, in which
;;; the key is a stream (integer) in slot gensym-pathname-stream?, and the
;;; value is the gensym pathname. In this way, the deletion code could be
;;; further simplified. -- Chun Tian (binghe), Jun 2015.

(def-system-variable all-gensym-pathnames-containing-open-streams
    STREAMS
  #-SymScale nil
  #+SymScale (:funcall make-empty-constant-queue)
  nil t)

(defmacro gensym-maybe-intercepted-pathname (namestring)
  (if (eval-feature :development)
      (avoiding-variable-capture (namestring)
        `(cond
           (file-system-for-interception?
            (let (intercepted-pathname)
              (let* ((local-file-system (initialize-local-file-system))
                     (local-filename-parser (initialize-local-filename-parser))
                     (local-namestring-generator
                       (initialize-local-namestring-generator)))
                (setq intercepted-pathname (gensym-pathname ,namestring)))
              (setf (gensym-pathname-file-system intercepted-pathname)
                    local-file-system)
              (setf (gensym-pathname-filename-parser intercepted-pathname)
                    local-filename-parser)
              (setf (gensym-pathname-namestring-generator intercepted-pathname)
                    local-namestring-generator)
              intercepted-pathname))
           (t (gensym-pathname ,namestring))))
      `(gensym-pathname ,namestring)))

(defun g2-stream-enter-into-stream-tables (namestring new-stream)
  (streams-pushnew new-stream
                   g2-stream-all-open-streams
                   :test #'identical-g2-streams-p)
  (let ((new-pathname? (gensym-maybe-intercepted-pathname namestring)))
    (cond (new-pathname?
           ;; jh, 12/2/91.  Added the following form to get the correct version
           ;; number from streams on Lispms.  Previously, we were probing the file
           ;; by namestring and consequently were off by one (or more, if we were
           ;; in a race condition).
           ;; jh, 12/27/91.  Now we look for a numeric version.  Previously we
           ;; looked for any non-nil thing, even something like :newest, which can
           ;; never be part of a truename.
           (augment-pathname-from-file-system new-pathname? namestring)
           (setf (gensym-pathname-stream? new-pathname?)
                 new-stream)
	   #+SymScale
	   (constant-queue-push-left all-gensym-pathnames-containing-open-streams
				     new-pathname?)
	   #-SymScale
           (streams-push new-pathname?
                         all-gensym-pathnames-containing-open-streams))
          (t #+development
             (cerror "Continue, placing empty pathname in stream tables"
                     "G2 could open stream yet pathname parsing failed.~%~
                      ~2tnamestring: ~a~%stream: ~a~%"
                     namestring
                     new-stream)
             (let ((empty-pathname (gensym-make-pathname :name namestring)))
               (setf (gensym-pathname-stream? empty-pathname) new-stream)
	       #+SymScale
               (constant-queue-push-left all-gensym-pathnames-containing-open-streams
					 empty-pathname)
	       #-SymScale
	       (streams-push empty-pathname
                             all-gensym-pathnames-containing-open-streams)))))
  new-stream)

;; jh, 4/30/91.  Modified g2-stream-enter-into-stream-tables to insert
;; the version number into the gensym-pathname it stores in
;; all-gensym-pathnames-containing-open-streams, if versions matter to
;; the file system involved.  This will allow us to grab the truename of
;; a file from a still-open stream, essential when a file-using facility
;; (warm boot and printing spring to mind) has several file versions
;; open at once.  To get a version-specific pathname, simply call
;; gensym-truename or gensym-pathname with the open stream as argument.
;; Note that process-switching must not occur between when the stream is
;; opened and when g2-stream-enter-into-stream-tables is called.  If it
;; does, some other process could open a stream to the same file and
;; mislead the version-getting function.  Although there is no way to
;; turn off process switching on all platforms, as-atomic-operation
;; wrappers have been placed inside the the relevant g2-stream-open-xxx
;; functions, as a way of documenting the desired behavior.

;; jh, 6/7/91.  Cleaned up the code inside g2-stream-enter-into-stream-tables
;; that decorates a gensym-pathname with information gleaned from the external
;; file system: device name, absolute directory subcomponents, and version
;; number.  All this is handled by augment-pathname-from-file-system, which
;; takes two arguments, a gensym-pathname and a namestring derived from it, and
;; supplies the components.  (The namestring argument is not entirely redundant,
;; since some file components are more easily derived from a namestring than
;; from the existing pathname components.) Augment-pathname-from-file-system is
;; internal to PATHNAMES except for this one appearance.  This is not considered
;; a severe loss of modularity, because eventually STREAMS will be converted to
;; the Common Lisp standard and will share internals with PATHNAMES anyway.




;; We can't use the turnkey delete-streams-element in
;; g2-stream-delete-from-list-of-all-open-streams because it uses an eq test,
;; inappropriate when streams are represented as integers, as they are in
;; c-streams.

(defun g2-stream-delete-from-list-of-open-streams (old-stream)
  (if (identical-g2-streams-p (car g2-stream-all-open-streams) old-stream)
      (streams-pop g2-stream-all-open-streams)
      (loop with cons-containing-stream = nil
            for successive-cdr on g2-stream-all-open-streams
            do (setq cons-containing-stream (cdr successive-cdr))
            do (when (identical-g2-streams-p
                       (car cons-containing-stream)
                       old-stream)
                 (setf (cdr successive-cdr) (cddr successive-cdr))
                 (reclaim-streams-cons cons-containing-stream)
                 (return))
            #+development
            finally
            #+development
            (cerror "Continue, ignoring error."
                    "The stream that was being closed, ~a, was not found ~
                     on g2-stream-all-open-streams."
                    old-stream))))

#+SymScale
(defun delete-from-list-of-active-pathnames (old-stream)
  (unless (constant-queue-empty-p all-gensym-pathnames-containing-open-streams)
    (loop with constant-queue = all-gensym-pathnames-containing-open-streams
	  with head = (constant-queue-head constant-queue)
	  for queue-element = (constant-queue-next head constant-queue)
			    then next-queue-element
	  until (null queue-element)
	  for next-queue-element = (constant-queue-next queue-element constant-queue)
	  for gensym-pathname = (queue-datum queue-element)
	  do
      (when (identical-g2-streams-p (gensym-pathname-stream? gensym-pathname)
				    old-stream)
	(reclaim-gensym-pathname gensym-pathname)
	(constant-queue-delete queue-element constant-queue)
	(return))
          #+development
	  finally
	  #+development
	  (cerror "Continue, ignoring error."
		  "The stream that was being closed, ~a, was not found ~
                   on all-gensym-pathnames-containing-open-streams."
		  old-stream))))

#-SymScale
(defun delete-from-list-of-active-pathnames (old-stream)
  (when all-gensym-pathnames-containing-open-streams
    (if (identical-g2-streams-p
          (gensym-pathname-stream?
            (car all-gensym-pathnames-containing-open-streams))
          old-stream)
        (reclaim-gensym-pathname
          (streams-pop all-gensym-pathnames-containing-open-streams))
        (loop with cons-containing-stream = nil
            for successive-cdr on all-gensym-pathnames-containing-open-streams
            do (setq cons-containing-stream (cdr successive-cdr))
            do (when (identical-g2-streams-p
                       (gensym-pathname-stream? (car cons-containing-stream))
                       old-stream)
                 (setf (cdr successive-cdr) (cddr successive-cdr))
                 (reclaim-gensym-pathname (car cons-containing-stream))
                 (reclaim-path-cons cons-containing-stream)
                 (return))
            #+development
            finally
            #+development
            (cerror "Continue, ignoring error."
                    "The stream that was being closed, ~a, was not found ~
                     on all-gensym-pathnames-containing-open-streams."
                    old-stream)))))

(defun g2-stream-find-active-pathname (stream)
  (loop for pathname being each gensym-pathname of
			   all-gensym-pathnames-containing-open-streams
        thereis
        (and (identical-g2-streams-p
               (gensym-pathname-stream? pathname)
               stream)
             pathname)))


(defun g2-stream-remove-entry-from-stream-tables (old-stream)
  (delete-from-list-of-active-pathnames old-stream)
  (g2-stream-delete-from-list-of-open-streams old-stream))




;;;; Error Reporting

;; The basic idea is that each file operation records a status in a single global
;; variable, `internal-status-of-most-recent-file-operation.' This is modeled
;; after the errno facility in C, and is the "least common denominator" error
;; reporting on all file systems.  Internal-status-of-most-recent-file-operation
;; always contains a fixnum; it is up to the g2-streams machinery to guarantee
;; that this fixnum adequately reflects the status of the file operation that just
;; happened.

;; The variable internal-status-of-most-recent-file-operation should never be used
;; directly outside this module.  Instead, the function
;; most-recent-file-operation-status-as-text will provide a reclaimable text
;; string representing the status in a form suitable for notify-user.

;SS_ERROR
;; error codes that don't come from errno.h
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter file-already-exists-code            17)
(defparameter end-of-file-reached-code             0)
(defparameter file-operation-succeeded-code       -1)
(defparameter file-not-found-code                 -2)
(defparameter file-at-unknown-host-code           -3)
(defparameter file-directory-not-found-code       -4)
(defparameter file-host-not-responding-code       -5)
(defparameter filename-parse-failed-code          -6)
(defparameter file-op-not-supported-code          -7)
(defparameter unknown-error-during-file-op-code   -8)
(defparameter error-creating-disk-query-code     -10)
(defparameter error-spawning-disk-query-code     -11)
(defparameter error-parsing-disk-query-code      -12)
(defparameter directory-spec-too-long-code       -13)
(defparameter failed-to-build-dir-structure-code -14)
(defparameter failed-to-open-dir-structure-code  -15)
(defparameter append-of-non-existent-file-code   -16)
(defparameter bad-regular-expression-code        -17)
(defparameter failed-to-open-device-list-code    -18)

(defparameter unknown-error-during-file-op-message
             "Unspecified error occurred")
) ;end of eval-when for non-errno constants in g2-stream-error-string-table

;; jh, 1/3/92.  Added unknown-error-during-file-op-with-code-message, a format
;; control string which includes the actual unknown error code.  This will be
;; useful on non-UNIX platforms like VMS which have out-of-the-ordinary errno
;; codes.

(defconstant unknown-error-during-file-op-with-code-message
             "Unspecified error (~a) occurred")

;; The non-negative numbers in the following table should remain in synch with the
;; errno.h files on our various platforms, insofar as they themselves remain
;; consistent.

(defvar g2-stream-error-string-table
 '(
   ;; Following eight are internal Gensym codes set in
   ;; g2-stream-ignoring-file-errors
   (#.file-operation-succeeded-code      . "Unknown file access status")
   (#.file-not-found-code                . "File not found")
   (#.file-at-unknown-host-code          . "Unknown host for file")
   (#.file-directory-not-found-code      . "Directory not found for file")
   (#.file-host-not-responding-code      . "File host not responding")
   (#.filename-parse-failed-code         . "Filename parse failed")
   (#.file-op-not-supported-code         . "File operation not supported")
   (#.unknown-error-during-file-op-code  . #.unknown-error-during-file-op-message)

   ;; Following seven codes are internal Gensym codes set by the c-streams
   ;; machinery
   (#.error-creating-disk-query-code     . "Error creating disk query")
   (#.error-spawning-disk-query-code     . "Error spawning disk query")
   (#.error-parsing-disk-query-code      . "Error parsing disk query results")
   (#.directory-spec-too-long-code       . "Directory spec is too long")
   (#.failed-to-build-dir-structure-code . "Failed to build dir structure")
   (#.failed-to-open-dir-structure-code  . "Failed to open dir structure")
   (#.append-of-non-existent-file-code   . "File to append does not exist")
   (#.bad-regular-expression-code        . "Bad regular expression")
   (#.end-of-file-reached-code           . "End of file reached")
   (#.failed-to-open-device-list-code    . "Could not open device list")

   ;; Remaining codes come from errno
   (1     . "No permission to access the file")
   (2     . "No such file or directory")
   (3     . "No such process")
   (4     . "Interrupted system call")
   (5     . "I/O error")
   (6     . "No such device or address")
   (7     . "Argument list too long")
   (8     . "Exec format error")
   (9     . "Bad file number")
   (10    . "No children")
   (11    . "No more processes")
   (12    . "Not enough core")
   (13    . "Permission denied")
   (14    . "Bad address")
   (15    . "Block device required")
   (16    . "Mount device busy")
   (#.file-already-exists-code . "The file already exists")
   (18    . "Cross-device link")
   (19    . "There is no such device")
   (20    . "Not a directory")
   (21    . "You are trying to access a directory")
   (22    . "Invalid argument")
   (23    . "File table overflow")
   (24    . "Too many open files")
   (25    . "Not a typewriter")
   (26    . "Text file busy")
   (27    . "File too large")
   (28    . "No space left on device")
   (29    . "Illegal seek")
   (30    . "Read-only file system")
   (31    . "Too many links")
   (32    . "Broken pipe")
  ))

;; Note that there is no inconsistency in having both
;; g2-stream-foreign-file-op-failure and file-operation-succeeded-code be the same
;; number (-1).  The former represents the result of a foreign call to the C file
;; I/O library while the latter is G2's way of keeping track of the status of its
;; most recent file operation.

(def-system-variable internal-status-of-most-recent-file-operation
  STREAMS #.file-operation-succeeded-code nil t)

;;; `g2-stream-ignoring-file-errors' was a lot more complicated when supporting
;;; lispms -rdf, 3/30/95
(defmacro g2-stream-ignoring-file-errors (&body body)
  `(progn ,@body))


(defmacro most-recent-file-operation-succeeded ()
  `(setq internal-status-of-most-recent-file-operation
         file-operation-succeeded-code))

(defun-simple most-recently-encountered-file-already-exists-error-p ()
  (eql internal-status-of-most-recent-file-operation
       file-already-exists-code))

(defmacro record-file-operation-not-supported ()
  `(setq internal-status-of-most-recent-file-operation
         file-op-not-supported-code))


(def-gensym-c-function c-g2_stream_get_error_number
                       (:fixnum-int "g2ext_g2_stream_get_error_number")
  ())

;; jh, 11/6/91.  Typically, record-status-of-most-recent-file-operation is called
;; whenever the foreign code returns an error status and otherwise
;; most-recent-file-operation-succeeded is called.  This is because the errno
;; mechanism in C doesn't set errno if the operation succeeded.  Changed all
;; g2-stream-operations in this file to reflect this.  (They had been calling
;; record-status-of-most-recent-file-operation in both cases, leading to error
;; reports when there were no errors.

(defmacro record-status-of-most-recent-file-operation (&optional code?)
  (if code?
      `(setq internal-status-of-most-recent-file-operation ,code?)
      `(setq internal-status-of-most-recent-file-operation
             (c-g2_stream_get_error_number))))

(def-system-variable cached-unknown-error-string-with-code? STREAMS nil nil t)


;;; `Most-recent-file-operation-status-as-text' returns a fresh text string
;;; usually originating from the operating system with an error message.
;;;
;;; Note that the caller is responsible for reclaiming the text string result of
;;; calling this function.

(defun most-recent-file-operation-status-as-text ()
  #+development
  (when (eql internal-status-of-most-recent-file-operation
             file-operation-succeeded-code)
    (cerror "Continue"
            "Possible incorrect call to most-recent-file-operation-status-as-text"))
  (let ((error-text?
          (cdr
            (assq internal-status-of-most-recent-file-operation
                  g2-stream-error-string-table))))
    (cond (error-text?
           ;; presumably in the ASCII subset of Unicode, but may need translation!
           (copy-text-string error-text?))
          (t (when cached-unknown-error-string-with-code?
               (reclaim-text-string cached-unknown-error-string-with-code?))
             (setq cached-unknown-error-string-with-code?
                   (tformat-text-string
                     unknown-error-during-file-op-with-code-message
                     internal-status-of-most-recent-file-operation))
             (copy-text-string cached-unknown-error-string-with-code?)))))

(defmacro most-recent-file-operation-succeeded-p ()
  `(=f internal-status-of-most-recent-file-operation
       file-operation-succeeded-code))

;; for backward compatibility

(defmacro g2-stream-error-string () ;don't reclaim the string from this!
  `(or (cdr (assq internal-status-of-most-recent-file-operation
                  g2-stream-error-string-table))
       (progn (when cached-unknown-error-string-with-code?
                (reclaim-text-string cached-unknown-error-string-with-code?))
              (setq cached-unknown-error-string-with-code?
                    (tformat-text-string
                      unknown-error-during-file-op-with-code-message
                      internal-status-of-most-recent-file-operation))
              cached-unknown-error-string-with-code?)))

(defmacro g2-stream-error-flag-set-p ()
  `(/=f internal-status-of-most-recent-file-operation
        file-operation-succeeded-code))

(defmacro g2-stream-get-error-flag ()
  `internal-status-of-most-recent-file-operation)

(defmacro g2-stream-get-error-string-from-flag ;don't reclaim string from this!
          (flag)
  `(or (cdr (assq ,flag g2-stream-error-string-table))
       (progn (when cached-unknown-error-string-with-code?
                (reclaim-text-string cached-unknown-error-string-with-code?))
              (setq cached-unknown-error-string-with-code?
                    (tformat-text-string
                      unknown-error-during-file-op-with-code-message
                      ,flag))
              cached-unknown-error-string-with-code?)))

(defmacro g2-stream-last-error-is-eof-p ()
  `(=f internal-status-of-most-recent-file-operation
       end-of-file-reached-code))



;;;; Defining Platform-independent File Operations

;;; def-g2-stream-operation
;;;    name args record-status-declaration &key c-streams lisp-streams

;;; `Def-g2-stream-operation' is a form for defining platform-independent
;;; operations on g2-streams.  There are two main differences between a
;;; g2-stream-operation and an ordinary function.  First, a g2-stream-operation
;;; behaves differently on Lispms as opposed to non-Lispms.  The code to be
;;; evaluated on each platform is given by the lisp-streams and c-streams
;;; keywords, respectively.  Note that this code is a single form, not an implicit
;;; progn.

;;; The second difference is that a g2-stream-operation may side-effect
;;; internal-status-of-most-recent-file-operation.  This is determined by the
;;; record-status-declaration subform.  If this form is
;;;   (declare (record-status t))
;;; then def-g2-stream-operation guarantees that doing the operation and then
;;; calling most-recent-file-operation-status-as-text immediately afterwards will
;;; yield a reclaimable text-string with a status message relevant to that
;;; operation.  If the form is
;;;   (declare (record-status nil))
;;; then def-g2-stream-operation undertakes not to change the status message.  No
;;; forms other than t or nil are allowed in the record-status declaration.

;;; To fulfil a (record-status t) declaration, the following functions may be
;;; called explicitly:
;;;   record-status-of-most-recent-file-operation (&optional code?)
;;;   most-recent-file-operation-succeeded ()

;;; Using lisp-streams, the declaration could also be fulfilled by code which
;;; wraps g2-stream-ignoring-file-errors around the actual sections which deal
;;; with file operations.  (Since we want to manifest non-file-related errors
;;; differently where possible, wrapping it around the entire form may be
;;; inappropriate.) Inside this wrapper, the handlers for any errors that occur
;;; will side-effect internal-status-of-most-recent-file-operation, which in turn
;;; will cause most-recent-file-operation-status-as-text to return a relevant
;;; status message.

;;; The following pseudo-declaration forms are also supported:
;;;   (ignore-for-lisp-streams <var> ...)
;;;   (ignore-for-c-streams <var> ...)
;;;   (var-is-file-namestring <var> ...)
;;;   (var-is-g2-stream-arg <var> ...)
;;;   (version-for-g2-stream-handle-p t | nil )

;;; The var-is-file-namestring declaration adds development-only code to allow
;;; testing filestrings from different file systems than the native one.  This
;;; is helpful when we debug filename parsing, for example.

;;; The var-is-g2-stream-arg declaration converts the g2-stream argument from a
;;; g2-stream-structure to the internal C handle.  Among other things, this
;;; declaration adds development-only check that the arg in indeed a g2-stream.
;;; This supports thet new implementation of g2-stream as def-structure rather
;;; than fixnum.  This declaration is mandatory rather than exhortative, that
;;; is, undeclared g2-stream arguments to g2-stream operations won't work.

;;; The version-for-g2-stream-handle-p declaration will cause
;;; g2-stream-operation to create a function that accepts a g2-stream argument
;;; that has already been converted to a C handle.  For use only with the
;;; var-is-g2-stream-arg declaration.

(defun-for-macro expander-for-def-g2-stream-operation
                 (name
                   args
                   pseudo-declarations
                   c-streams-body
                   defun-to-use)
  (let* ((record-status-p nil)
         (pseudo-declaration-specifiers (cdr pseudo-declarations))
         (c-streams
           (intercept-filename-args-in-g2-stream-operation
             (cdr (assq 'var-is-file-namestring pseudo-declaration-specifiers))
             c-streams-body))
         (g2-stream-arg?
           (second (assq 'var-is-g2-stream-arg pseudo-declaration-specifiers))))
    (unless (and (eq (first pseudo-declarations) 'declare)
                 (let ((declaration-specifier
                         (assq 'record-status pseudo-declaration-specifiers)))
                   (and (consp declaration-specifier)
                        (= (length declaration-specifier) 2)
                        (memq (setq record-status-p
                                    (second declaration-specifier))
                              '(t nil)))))
      (error "DEF-G2-STREAM-OPERATION: ~a ~
              expected (record-status {t | nil} ), not ~a"
             name
             pseudo-declarations))
    (when record-status-p
      (labels ((walk-form-for-calls (form calls)
                 (cond ((and (symbolp form) (memq form calls))
                        (throw 'found-call t))
                       ((consp form)
                        (or (walk-form-for-calls (car form) calls)
                            (walk-form-for-calls (cdr form) calls)))
                       (t nil))))
        (unless (catch 'found-call
                  (walk-form-for-calls
                    c-streams
                    '(g2-stream-with-open-stream
                       record-status-of-most-recent-file-operation
                       record-file-operation-not-supported
                       most-recent-file-operation-succeeded)))
          (error "DEF-G2-STREAM-OPERATION: ~a ~
                  record-status declared true, but c-streams form ~
                  apparently does not record status"
                 name))))
    (when g2-stream-arg?
      (unless (memq g2-stream-arg? args)
        (error "DEF-G2-STREAM-OPERATION:~%~
                ~A is not an argument to ~A, let alone a g2-stream arg"
               g2-stream-arg?
               name)))
    (let ((substitution-macro-name (intern (format nil "~a-MACRO" name)))
          (internal-macro-name?
            (and (second (assq 'version-for-g2-stream-handle-p
                               pseudo-declaration-specifiers))
                 (intern (format nil "~a-FROM-HANDLE-MACRO" name)))))
      (cond
        ((eval-feature :c-streams)
         (let* ((ignorable-c-stream-args?
                  (cdr (assq 'ignore-for-c-streams
                             pseudo-declaration-specifiers)))
                (referenced-c-stream-args
                  (set-difference args ignorable-c-stream-args?)))
           `(progn
              ,@(if internal-macro-name?
                    `((def-substitution-macro ,internal-macro-name? ,args
                        ,c-streams))
                    nil)
              (def-substitution-macro ,substitution-macro-name
                  ,referenced-c-stream-args
                ,@(if (and g2-stream-arg? (eval-feature :development))
                      `((unless (g2-stream-p ,g2-stream-arg?)
                          (cerror
                            "Assume you know what you're doing"
                            "~A: expected a g2-stream, got ~S"
                            ',name
                            ,g2-stream-arg?)))
                      nil)
                ;; jh, 4/26/96.  Set g2-stream-arg? to actual handle here.
                ,@(if g2-stream-arg?
                      `((setq ,g2-stream-arg?
                              (g2-stream-handle ,g2-stream-arg?)))
                      nil)
                ,c-streams)
              (,defun-to-use ,name ,args
                 ,@(if ignorable-c-stream-args?
                       `((declare (ignore ,@ignorable-c-stream-args?))))
                 (,substitution-macro-name ,@referenced-c-stream-args)))))))))







(defmacro def-g2-stream-operation
          (name args record-status-declaration &key c-streams)
  (expander-for-def-g2-stream-operation
    name
    args
    record-status-declaration
    c-streams
    'defun))


(defmacro def-g2-stream-operation-allowing-unwind
          (name args record-status-declaration &key c-streams)
  (expander-for-def-g2-stream-operation
    name
    args
    record-status-declaration
    c-streams
    'defun-allowing-unwind))




;;;; Predicates

;;; g2-stream-p

;;; `g2-stream-p' (thing)
;;; Returns non-nil if the thing is a g2-stream, nil otherwise.

(def-g2-stream-operation g2-stream-p (thing)
  (declare (record-status nil))

  :c-streams
  (loop for stream? in g2-stream-all-open-streams
        do
    (when (and stream? (identical-g2-streams-p thing stream?))
      (return t))
        finally
          (return nil)))


;;; Returns non-nil if the two arguments, which must be g2-streams, are the
;;; same.

(defun-simple identical-g2-streams-p (g2-stream-1 g2-stream-2)
  (eql g2-stream-1 g2-stream-2))




;;; g2-stream-eof-p

;;; Returns non-nil if g2-stream is at the end-of-file, nil otherwise.

(def-gensym-c-function c-g2_stream_eof_p
                       (:fixnum-int "g2ext_str_eof_p")
  ((:pointer g2-stream)))


(def-g2-stream-operation g2-stream-eof-p (g2-stream)
  (declare (record-status nil)
           (var-is-g2-stream-arg g2-stream)
           (version-for-g2-stream-handle-p t))

  :c-streams
  (if (=f (c-g2_stream_eof_p g2-stream) 0)
      nil
      t))


;;;; Reclamation

;;; g2-stream-reclaim

;;; Reclaims a g2-stream for reuse.  Note that this function (or macro) is not to
;;; be used unless g2-stream-close failed and there is nothing else to do.  The
;;; g2-stream-open functions creates the streams.  This function (macro) will
;;; never cause an error, hence g2-stream-error-string will return the same value.
;;; The value returned is undefined.

(def-g2-stream-operation g2-stream-reclaim (g2-stream-structure)
  ;; Don't declare var-is-g2-stream-arg - we need the structue, not the enclosed
  ;; handle, here.
  (declare (record-status nil)
           (ignore-for-lisp-streams g2-stream-structure))
  :c-streams
  (reclaim-g2-stream-structure g2-stream-structure))

;;; g2-stream-close

;;; The function `g2-stream-close' takes a single argument, a g2-stream.  This
;;; function writes out all buffers to the file associated with the g2-stream
;;; (as if by calling g2-stream-flush) and terminates the association between
;;; the g2-stream and the file.

(def-g2-stream-operation g2-stream-close (g2-stream-structure)
  ;; Don't declare var-is-g2-stream-arg - we need both structure and its
  ;; enclosed handle here.
  (declare (record-status t))
  :c-streams
  (let ((status
          (c-g2_stream_close (g2-stream-handle g2-stream-structure))))
    (g2-stream-remove-entry-from-stream-tables g2-stream-structure)
    (reclaim-g2-stream-structure g2-stream-structure)
    (cond ((=f status g2-stream-foreign-file-op-success)
           (most-recent-file-operation-succeeded)
           t)
          (t (record-status-of-most-recent-file-operation)
             nil)))
  )

;; jh, 11/6/91.  There is an intermittant problem with close on the Explorers.
;; The problem seems to happen the first time a KB is ever saved to a UNIX
;; platform, but it doesn't always happen even then.  Subsequent times do not
;; signal an error.  If we can't narrow down the problem soon, it would be best to
;; revert to what the old STREAMS did, and always assume that close succeeded.
;; jh, 11/7/91.  Reverted.  This is too much trouble to track down on a
;; non-delivery platform.  The delivery platforms don't have this problem.


;;;; Assuring True Disc I/O

;;; g2-stream-flush

;;; Forces output buffers to be emptied so that other processes reading the file
;;; will see their contents.  (This is distinct from g2-stream-sync, which tries
;;; to assure that the contents have actually reached the physical disc.)  T is
;;; returned if no error is encountered.  Otherwise nil is returned, and the
;;; error flag is set accordingly.

(def-gensym-c-function c-g2_stream_flush (:fixnum-int "g2ext_str_flush") ;SS_ERROR: was :void
  ((:pointer g2-stream)))

(def-g2-stream-operation g2-stream-flush (g2-stream)
  (declare (record-status t)
           (var-is-g2-stream-arg g2-stream))

  :c-streams
  (let ((status (c-g2_stream_flush g2-stream)))
    (cond ((=f status g2-stream-foreign-file-op-success)
           (most-recent-file-operation-succeeded)
           t)
          (t (record-status-of-most-recent-file-operation)
             nil))))



;;; g2-stream-sync

;;; Forces output to the disc as much as possible.  T is returned if no error is
;;; encountered.  Otherwise nil is returned, and the error flag is set
;;; accordingly.  Note that this function is distinct from g2-stream-flush.  It
;;; is needed because some operating systems use a technique called "delayed
;;; write", which maximizes throughput by writing file contents to kernel memory
;;; instead of disk under some circumstances.  Thus flushing a buffer to a file
;;; is not the same as placing the contents of that buffer on disc.

(def-gensym-c-function c-g2_stream_sync (:fixnum-int "g2ext_str_sync")
  ((:pointer g2-stream)))

(def-g2-stream-operation g2-stream-sync (g2-stream)
  (declare (record-status t)
           (var-is-g2-stream-arg g2-stream))

  :c-streams
  (let ((status (c-g2_stream_sync g2-stream)))
    (cond ((=f status g2-stream-foreign-file-op-success)
           (most-recent-file-operation-succeeded)
           t)
          (t (record-status-of-most-recent-file-operation)
             nil))))




;;;; Creating G2-streams



;;; `g2-stream-with-8-byte-file', `g2-stream-with-16-byte-file' and
;;; `g2-stream-with-non-character-mode' were a lot mroe complicated when
;;; we used to support lisp machines

(defmacro g2-stream-with-8-byte-file (&body body)
      `(progn ,@body))

(defmacro g2-stream-with-16-byte-file (&body body)
  `(progn ,@body))

(defmacro g2-stream-with-non-character-mode (&body body)
  `(progn ,@body))

(defun use-unicode-for-filenames ()
  (if (and (boundp 'miscellaneous-parameters) miscellaneous-parameters)  
    (use-unicode-for-filenames?-from-system-table)
    nil))


(defmacro def-g2-stream-open-operation
    (name &key c-streams-access raw-access)
  `(def-g2-stream-operation ,name (namestring)
     (declare (record-status t)
              (var-is-file-namestring namestring))

     :c-streams
     (let* ((stream-or-error
	     (if (or ,raw-access (use-unicode-for-filenames))
		 (c-g2_stream_open_wide namestring ,c-streams-access)
	       (c-g2_stream_open namestring ,c-streams-access))))
       (prog1
           (cond
             ((=f stream-or-error g2-stream-foreign-file-op-failure)
              (record-status-of-most-recent-file-operation)
              nil)
             (t (let ((g2-stream-structure (make-g2-stream stream-or-error)))
                  (g2-stream-enter-into-stream-tables
                    namestring
                    g2-stream-structure)
                  (most-recent-file-operation-succeeded)
                  g2-stream-structure)))))))

;; Converted to assume namestring is a text string and that c functions convert
;; as necessary automatically, here and elsewhere in STREAMS. (MHD 2/22/96)

;; jh, 3/16/94.  Added protection against non-simple-strings inside the
;; expansion of a def-g2-stream-open-operation for :c-streams.

;; jh, 4/30/91.  Added as-atomic-operation wrapper inside the
;; g2-stream-open-for-input functions, because we now cache the version number (on
;; file systems where it matters, like VMS).  The worst case process-switching
;; scenario would be that we open a file, another process opens the same file, and
;; we try to cache the wrong version number.  Wrapping as-atomic-operation may be
;; an empty gesture on some platforms, but at least it documents the problem.


;;; g2-stream-open-for-input

;;; Opens a file specified by namestring for input.  Returns a g2-stream if it is
;;; successful, and returns nil and sets the g2-stream-error-flag if it is not
;;; successful.

(def-g2-stream-open-operation g2-stream-open-for-input
  :c-streams-access g2-stream-open-mode-for-input)

(def-g2-stream-open-operation g2-stream-open-for-input-raw
  :c-streams-access g2-stream-open-mode-for-input
  :raw-access t)


;;; g2-stream-open-for-output

;;; Opens a file specified by namestring for output.  If the file exists, a new
;;; version is created.  (If the operating system does not have versions, the old
;;; file will be overwritten by the new file.) Returns a g2-stream if it is
;;; successful, and returns nil and sets the g2-stream-error-flag if it is not
;;; successful.

(def-g2-stream-open-operation g2-stream-open-for-output
  :c-streams-access g2-stream-open-mode-for-output)



(def-g2-stream-open-operation g2-stream-open-for-binary-input
  :c-streams-access g2-stream-open-mode-for-binary-input)

;;; g2-stream-open-for-binary-output

;;; Opens a file specified by namestring for output that can include non-text
;;; characters.  If the file exists, a new version is created.  (If the
;;; operating system does not have versions, the old file will be overwritten by
;;; the new file.) Returns a g2-stream if it it successful, and returns nil and
;;; sets the g2-stream-error-flag if it is not successful.

(def-g2-stream-open-operation g2-stream-open-for-binary-output
  :c-streams-access g2-stream-open-mode-for-binary-output)


;;; g2-stream-open-for-appending

;;; Opens a file for appending.  If create-if-does-not-exist-p is nil, nil will be
;;; returned and g2-stream-error-flag set (indicating that the file is not found)
;;; if namestring doesn't refer to an existing file.  If it does, that file is
;;; opened for appending.  If create-if-does-not-exist?  is non-nil, this function
;;; (or macro) works just like g2-stream-open-for-output.

(defun g2-stream-open (filename mode)
  (if (use-unicode-for-filenames)
    (c-g2_stream_open_wide filename mode)
    (c-g2_stream_open filename mode)))

(def-g2-stream-operation-allowing-unwind g2-stream-open-for-appending
                                         (namestring create-if-does-not-exist?)
  (declare (record-status t)
           (var-is-file-namestring namestring))

  :c-streams
  (progn
    (unless create-if-does-not-exist?
      (unless (g2-stream-probe-file-for-exist namestring)
        (record-status-of-most-recent-file-operation
          append-of-non-existent-file-code)
        (return-from g2-stream-open-for-appending)))
    (let ((stream-or-error (g2-stream-open namestring g2-stream-open-mode-for-appending)))
      (cond ((=f stream-or-error g2-stream-foreign-file-op-failure)
             (record-status-of-most-recent-file-operation)
             nil)
            (t (most-recent-file-operation-succeeded)
               (let ((g2-stream-structure (make-g2-stream stream-or-error)))
                 (g2-stream-enter-into-stream-tables
		  namestring
		  g2-stream-structure)
                 g2-stream-structure))))))


;; jh & pto, 10/8/90.
;; We introduce random access file i/o and bidirectional streams into g2-streams
;; for efficiency in certain applications (notably KFEP).

;; The assumption is that C will return the file position as a positive integer.
;; Harbison and Steele (p316) are careful to allow for more devious
;; implementations than this straightforward one.  If we encounter such
;; implementations, more design will be necessary.

;; NOTE: Before switching directions with a bidirectional stream (reading a
;; character you have just written, for example), the function
;; g2-stream-flip-bidirectional-mode must be called.  This is an artifact of the C
;; implementation mentioned in Harbison and Steele (p313).


;;; g2-stream-open-for-random-access-binary-io (filename)

;;; Returns a bidirectional g2-stream suitable for random access using
;;; characters that may be other than text, or nil if unable to open the stream.
;;; Another way of saying "bidirectional stream" is "stream open for update".
;;; Note that bidirectionality and random-accessibility are independent of one
;;; another.  Some Lisp implementations (notably Lucid/VMS) do not support
;;; random access streams.  In this case, we will have to implement
;;; g2-stream-open-for-random-access-binary-io in C or nothing.  Some other Lisp
;;; implementations (notably the Lisp machines) do not support bidirectional
;;; streams, even though they are a Common Lisp construct (CltL/2e p647).  In
;;; this case, we will have to implement
;;; g2-stream-open-for-random-access-binary-io using platform-specific
;;; operations.

(def-g2-stream-operation g2-stream-open-for-random-access-binary-io
    (namestring)
  (declare (record-status t)
           (ignore-for-lisp-streams namestring)
           (var-is-file-namestring namestring))

  :c-streams
  (let ((stream-or-error
	 (g2-stream-open namestring g2-stream-open-mode-for-binary-update)))
    (cond ((=f stream-or-error g2-stream-foreign-file-op-failure)
           (record-status-of-most-recent-file-operation)
           nil)
          (t (most-recent-file-operation-succeeded)
             (let ((g2-stream-structure (make-g2-stream stream-or-error)))
               (g2-stream-enter-into-stream-tables
                 namestring
                 g2-stream-structure)
               g2-stream-structure)))))


;;; g2-stream-open-for-random-access-io (filename)

;;; Returns a bidirectional g2-stream suitable for random access, or nil if unable
;;; to open the stream.  Another way of saying "bidirectional stream" is "stream
;;; open for update".  Note that bidirectionality and random-accessibility are
;;; independent of one another.  Some Lisp implementations (notably Lucid/VMS) do
;;; not support random access streams.  In this case, we will have to implement
;;; g2-stream-open-for-random-access-io in C or nothing.  Some other Lisp
;;; implementations (notably the Lisp machines) do not support bidirectional
;;; streams, even though they are a Common Lisp construct (CltL/2e p647).  In this
;;; case, we will have to implement g2-stream-open-for-random-access-io using
;;; platform-specific operations.

(def-g2-stream-operation g2-stream-open-for-random-access-io (namestring)
  (declare (record-status t)
           (ignore-for-lisp-streams namestring)
           (var-is-file-namestring namestring))

  :c-streams
  (let ((stream-or-error (g2-stream-open namestring g2-stream-open-mode-for-update)))
    (cond ((=f stream-or-error g2-stream-foreign-file-op-failure)
           (record-status-of-most-recent-file-operation)
           nil)
          (t (most-recent-file-operation-succeeded)
             (let ((g2-stream-structure (make-g2-stream stream-or-error)))
               (g2-stream-enter-into-stream-tables
		namestring
		g2-stream-structure)
               g2-stream-structure)))))



;;; g2-stream-open-for-random-access-binary-input (filename)

;;; Returns an input g2-stream suitable for random-access input to binary files,
;;; or nil if unable to open the stream.

#+lisp-streams
(def-system-variable random-access-stream-alist streams nil nil t)

#+lisp-streams
(defmacro get-random-access-file-element
          (random-access-file-string index)
  `(schar ,random-access-file-string ,index))

(def-g2-stream-operation g2-stream-open-for-random-access-binary-input
                         (namestring)
  (declare (record-status t)
           (var-is-file-namestring namestring))

  :c-streams
  (let ((stream-or-error
	 (g2-stream-open namestring g2-stream-open-mode-for-binary-input)))
    (cond ((=f stream-or-error g2-stream-foreign-file-op-failure)
           (record-status-of-most-recent-file-operation)
           nil)
          (t (most-recent-file-operation-succeeded)
             (let ((g2-stream-structure (make-g2-stream stream-or-error)))
               (g2-stream-enter-into-stream-tables
		namestring
		g2-stream-structure)
               g2-stream-structure)))))

;; MHD, 5/14/96. Note that I have not updated Lisp streams for Unicode and wide
;; characters.  Stuff for Lisp streams has generally either been left as is or
;; removed in certain cases.

;; jh, 10/4/94.  Changed g2-stream-open-for-binary-input to
;; g2-stream-open-for-random-access-binary-input because all its current clients
;; need both abilities.  Nothing changes at the cstreams.c level at this point.

;; jh, 9/28/94.  Changed g2-stream-open-for-random-access-input to
;; g2-stream-open-for-binary-input, because all its clients (currently only in
;; KFEP1) use it to open a stream guaranteed to read binary input, and not a
;; stream guaranteed to permit random access.  Failure to distinguish between
;; these two was preventing the Kanjii Front-End Processor from reading the
;; binary dictionary files on the Alpha NT platform.  During his implementation
;; of bitmapped images, Fred White made the initial discovery that this platform
;; cared about the difference, when none did before.

;; jh, 10/31/91.  Moved the check for stream?  to outside the scope of
;; g2-stream-ignoring-file-errors, so we can set the error flag no matter what
;; happens in gensym-open.

;; Note: consider doing the error-checking here even in non-development!
;;
;; Note: another way to speed up access to random access streams would be to pass
;; around a cons of the array and the pointer AS the stream.  This would involve
;; checking a lot of call sites to make sure they could deal with this.  Also, there
;; is no good reason to leave the original stream open once its contents have been
;; drained.  The closing logic would have to be changed to deal with any change
;; in this area, however.
;;
;; Note: it is assumed, for the random access streams implementation, that two
;; different streams returned by the ab-lisp:open function can always be meaningfully
;; compared using EQ.
;;
;; (MHD 11/27/90)




;;; g2-stream-open-for-binary-appending (filename)

;;; Returns a g2-stream suitable for appending to binary files, or nil if unable
;;; to open the stream.

(def-g2-stream-operation g2-stream-open-for-binary-appending
                         (namestring create-if-does-not-exist?)
  (declare (record-status t)
           (var-is-file-namestring namestring))

  :c-streams
  (progn
    (unless create-if-does-not-exist?
      (unless (g2-stream-probe-file-for-exist namestring)
        (record-status-of-most-recent-file-operation append-of-non-existent-file-code)
        (return-from g2-stream-open-for-binary-appending)))
    (let ((stream-or-error 
	   (g2-stream-open namestring g2-stream-open-mode-for-binary-appending)))
      (cond ((=f stream-or-error g2-stream-foreign-file-op-failure)
             (record-status-of-most-recent-file-operation)
             nil)
            (t (most-recent-file-operation-succeeded)
               (let ((g2-stream-structure (make-g2-stream stream-or-error)))
                 (g2-stream-enter-into-stream-tables
		  namestring
		  g2-stream-structure)
                 g2-stream-structure))))))


;;; g2-stream-flip-bidirectional-mode (g2-stream)

;;; Allows access to a bidirectional stream in a direction different from that
;;; which went before.  The necessity of this is mentioned in Harbison and Steele
;;; (p313).  For efficiency's sake, this function should be called as seldom as
;;; possible.  Calling it every read- or write-char does not seem like a good
;;; idea.  This function returns nil if it fails for any reason, non-nil if it
;;; succeeds.

(def-gensym-c-function c-g2_stream_flip_bidirectional_mode
                       (:fixnum-int "g2ext_str_flip_bidir_mode")
  ((:pointer g2-stream)))

(def-g2-stream-operation g2-stream-flip-bidirectional-mode
                         (g2-stream)
  (declare (record-status t)
           (var-is-g2-stream-arg g2-stream)
           (ignore-for-lisp-streams g2-stream))

  :c-streams
  (let ((result
          (c-g2_stream_flip_bidirectional_mode g2-stream)))

    (cond ((zerop result)
           (most-recent-file-operation-succeeded)
           t)
          (t (record-status-of-most-recent-file-operation)
             nil))))




;;;   (g2-stream-with-open-stream (
;;;                                <g2-stream-variable>
;;;                                :direction { :input | :output | :append }
;;;                                :create-if-does-not-exist <truth-value>
;;;                               )
;;;   . <body> )

;;; Note the differences in syntax between g2-stream-with-open-stream and the
;;; Common Lisp with-open-stream.  In g2-stream-with-open-stream, the user does
;;; not supply the form which will be bound to <g2-stream-variable>, but instead
;;; specifies the pathname to a file which is to be opened.  As with
;;; with-open-stream, the user can specify the type of g2-stream desired with
;;; the :direction keyword, but the :direction argument is unevaluated.  It must
;;; be one of the three keywords :input, :output, or :append, defaulting to
;;; :input.  The :create-if-does-not-exist argument is unevaluated and only
;;; makes sense for the :append direction, and will signal a compile-time error
;;; if used with any other direction.  The :element-type argument is unevaluated
;;; and must be either the symbol string-char or the list (unsigned-byte 8).
;;; The default :element-type is string-char; (unsigned-byte 8) will guarantee
;;; binary file I/O, a.k.a.  8-bit characters.  The <body> forms should call
;;; g2-stream-read and -write functions, after checking that
;;; <g2-stream-variable> is non-nil.

;;; Note that the <body> forms will always be executed, even if
;;; <g2-stream-variable> turns out to be nil.  It is the responsibility of the
;;; <body> to check if <g2-stream-variable> is nil before attempting
;;; g2-stream-read and -write operations.  This conforms with the X3J13
;;; pronouncement on with-open-file forms with nil :if-xxx-exist arguments [CLtL,
;;; 2nd edition, p 649].  Also note that when an error occurs, the global variable
;;; g2-stream-error-flag is set to a non-nil value, an error code To translate
;;; this code into text, call the function g2-stream-error-string with no
;;; arguments.

;;; Finally, a note about reclamation.  As long as the g2 file operations are
;;; implemented as call-outs for external C functions, the stream system will
;;; not cons.  This is true for all lucid.  If we have to revert back to lisp
;;; streams on these platforms, consing will occur, both because the lisp file
;;; system creates throwaway pathnames, and because the error-handling wrappers
;;; cons.  Even if we do revert to the lisp file system, the behavior of the
;;; g2-stream functions and macro will not change: they guarantee never to cause
;;; an error, to return nil if the stream was unaccessible, and to set
;;; g2-stream-error-flag appropriately.

;; Modified g2-stream-with-open-stream to take a gensym-pathname structure to
;; designate a file.  Previously, it was restricted to strings.  jh, 1/11/91.

(defun-for-macro expander-for-g2-stream-with-open-stream
                 (g2-stream-variable?
                   pathname
                   direction
                   create-if-does-not-exist
                   element-type
                   body
                   reckless-p)

  (unless (symbolp g2-stream-variable?)
    (error "g2-stream-with-open-stream requires a symbol for ~
            g2-stream-variable?, not~%~a"
            g2-stream-variable?))

  (unless (symbolp direction)
    (error "g2-stream-with-open-stream requires a symbol for the ~
            direction, not~%~a"
           direction))

  (unless (member direction '(:input :output :append))
    (error "The direction ~a supplied to g2-stream-with-open-stream ~%~
            is not one of :input, :output, or :append"
           direction))

  (unless direction
    (error "No direction supplied to g2-stream-with-open-stream"))

  (when create-if-does-not-exist
    (unless (eq :append direction)
      (error "Create-if-does-not-exist is not an option ~%~
              for g2-stream-with-open-stream in the ~a direction"
             direction)))

  (unless (member element-type '(string-char
                                 string-char-without-os-newline-translations
                                 (unsigned-byte 8))
                  :test #'equal)
    (error "G2-STREAM-WITH-OPEN-STREAMS: unknown element type ~s"
           element-type))

  (avoiding-variable-capture (pathname &aux namestring pathname-used-p)
    (let* ((unsigned-byte-8-p (equal element-type '(unsigned-byte 8)))
           (binary-p (or unsigned-byte-8-p
                         (eq element-type 'string-char-without-os-newline-translations)))
           (stream-opening-form
             (case direction
               (:input (cond (unsigned-byte-8-p
                              `(g2-stream-open-for-random-access-binary-input
                                ,namestring))
                             (binary-p
                              `(g2-stream-open-for-binary-input ,namestring))
                             (t
                              `(g2-stream-open-for-input ,namestring))))
               (:output (if binary-p
                            `(g2-stream-open-for-binary-output ,namestring)
                            `(g2-stream-open-for-output ,namestring)))
               (:append (if binary-p
                            `(g2-stream-open-for-binary-appending
                               ,namestring ,create-if-does-not-exist)
                            `(g2-stream-open-for-appending
                               ,namestring ,create-if-does-not-exist)))
               (otherwise
                (error "Bad direction ~a in g2-stream-with-open-stream"
                       direction)))))
      (if reckless-p
          `(let* ((,pathname-used-p
                     (gensym-pathname-p ,pathname))
                  (,namestring
                     (if (gensym-pathname-p ,pathname)
                         (gensym-namestring ,pathname)
                         ,pathname))
                  (,g2-stream-variable?
                     ;; Stream-opening-form will set g2-stream-error-flag
                     ;; correctly.  jh, 11/15/90.
                     ,stream-opening-form))
             (prog1 (progn ,@body)
               (when ,pathname-used-p
                 (reclaim-text-string ,namestring))
               (when ,g2-stream-variable?
                 (g2-stream-close ,g2-stream-variable?))))
          `(protected-let*
               ((,pathname-used-p
                   (gensym-pathname-p ,pathname))
                (,namestring
                   (if (gensym-pathname-p ,pathname)
                       (gensym-namestring ,pathname)
                       ,pathname)
                   (when ,pathname-used-p
                     (reclaim-text-string ,namestring)))
                (,g2-stream-variable?
                   ;; Stream-opening-form will set g2-stream-error-flag
                   ;; correctly.  jh, 11/15/90.
                   ,stream-opening-form
                   (g2-stream-close ,g2-stream-variable?)))
             ,@body)))))

(defun-for-macro expander-for-g2-stream-with-open-stream-input-raw
                 (g2-stream-variable?
		  pathname
		  body)

  (unless (symbolp g2-stream-variable?)
    (error "g2-stream-with-open-stream requires a symbol for ~
            g2-stream-variable?, not~%~a"
            g2-stream-variable?))

  (avoiding-variable-capture (pathname &aux namestring pathname-used-p)
    (let* ((stream-opening-form
	    `(g2-stream-open-for-input-raw ,namestring)))
      `(protected-let*
	   ((,pathname-used-p
	     (gensym-pathname-p ,pathname))
	    (,namestring
	     (if (gensym-pathname-p ,pathname)
		 (gensym-namestring ,pathname)
	       ,pathname)
	     (when ,pathname-used-p
	       (reclaim-text-string ,namestring)))
	    (,g2-stream-variable?
	     ;; Stream-opening-form will set g2-stream-error-flag
	     ;; correctly.  jh, 11/15/90.
	     ,stream-opening-form
	     (g2-stream-close ,g2-stream-variable?)))
	 ,@body))))

(defmacro g2-stream-with-open-stream
          ((g2-stream-variable pathname
            &key (direction :input)
                 create-if-does-not-exist
                 (element-type 'string-char))
           &body body)

  (expander-for-g2-stream-with-open-stream
    g2-stream-variable
    pathname
    direction
    create-if-does-not-exist
    element-type
    body
    nil))

(defmacro g2-stream-with-reckless-open-stream
          ((g2-stream-variable pathname
            &key (direction :input)
                 create-if-does-not-exist
                 (element-type 'string-char))
           &body body)

  (expander-for-g2-stream-with-open-stream
    g2-stream-variable
    pathname
    direction
    create-if-does-not-exist
    element-type
    body
    t))

;;; Special case for opening files during g2 initialization
(defmacro g2-stream-with-open-stream-raw
          ((g2-stream-variable pathname)
           &body body)
  (expander-for-g2-stream-with-open-stream-input-raw
    g2-stream-variable
    pathname
    body))




;;; g2-stream-probe-file (-for exist, read, write)

;;; Returns non-nil if the file given in string exists and nil if it doesn't.
;;; This is the interface function for the higher-level gensym-probe-file in the
;;; PATHNAMES module.  Gensym-probe-file coerces its argument into a namestring
;;; and does truename conversion on the returned value, duplicating Common Lisp
;;; behavior but with consing control.  (note amended 12/9/90, jh)


;;; there are three different kinds of probing: to just check of the file
;;; exists, to check if we can read it, and to check it we can write to it.
;;; These are abstracted here because they all want to check for various things
;;; like the UNIX ~ expander.  The body can assume all of the variables which
;;; are created such as filename-string-to-use.  Probably this is bad style,
;;; but making it define all of the variables in the macro arguments seems
;;; unnecessarily cumbersome.  -- yduJ 7/00
(defmacro define-g2-probe-file-operation (direction always-succeed &body body)
  (let ((macro-name (intern (format nil "G2-STREAM-PROBE-FILE-FOR-~A" direction))))
    `(def-g2-stream-operation-allowing-unwind ,macro-name (filename-string)
       (declare (record-status t)
                (var-is-file-namestring filename-string))
       :c-streams
       (let ((filename-string-to-use filename-string)
             (need-to-reclaim-filename-string-p nil))
         (when (and (eq local-file-system 'unix)
                    (>f (lengthw filename-string) 0)
                    (char=w (charw filename-string 0) #.%\~))
           (with-pathname-conversion
               ((filename-string pathname-needing-home))
             (if pathname-needing-home
                 (progn
                   (supply-home-to-unix-pathname pathname-needing-home)
                   (setq filename-string-to-use
                         (gensym-namestring pathname-needing-home))
                   (setq need-to-reclaim-filename-string-p t)
                   (reclaim-gensym-pathname pathname-needing-home))
                 (progn
                   (record-status-of-most-recent-file-operation
                     filename-parse-failed-code)
                   (return-from ,macro-name nil)))))
         (let ((found-it-p
                 (progn ,@body)))
           ;; Probe-file always succeeds, even if it returns nil.  This means it
           ;; successfully determined the file was not there.  jh, 1/29/92.
           ;; if it's probe for write, this variable is nil, because of comments
           ;; below about kb-save.  -- yduj, 12/00
           ,@(when always-succeed
               ;;extra set of parentheses so that this gets spliced in when
               ;;always succeed; omits spare nil otherwise
             `((most-recent-file-operation-succeeded)))
           (when need-to-reclaim-filename-string-p
             (reclaim-text-string filename-string-to-use))
           found-it-p)))))

(define-g2-probe-file-operation exist t
  (g2-probe-file-internal filename-string-to-use))

(defun g2-probe-file-internal (filename-string-to-use)
  (if (use-unicode-for-filenames)
    (=f (c-g2_probe_file_wide filename-string-to-use) 0)
    (=f (c-g2_probe_file filename-string-to-use) 0)))

(define-g2-probe-file-operation read t
    (g2-stream-with-reckless-open-stream
      (stream-or-nil filename-string-to-use :direction :input)
      (if stream-or-nil t nil)))


;;; g2-stream-probe-file-for-write

;;; Returns non-nil if the file given in string can be opened for write and nil if
;;; it can't.  Note that, if permissions are correct, a non-existent file can
;;; still be opened for write.  This is the interface function for the
;;; higher-level gensym-probe-file-for write in the PATHNAMES module.

;; jh, 2/22/92.  Changed the distribution version of
;; g2-stream-probe-file-for-write to set the error flag properly if the
;; file is not found.  This is used by save-kb to report the problem to
;; the user.  Note the contrast with the behavior of
;; g2-stream-probe-file, which always succeeds.

;; jh, 12/1/94.  There is a known bug in g2-stream-probe-file-for-write where,
;; under certain file access permissions, it returns true even though the file
;; is not actually writable.  This is because it has to use fopen("w+") to avoid
;; damaging an existing file, and the semantics differ from the fopen("w") that
;; is being probed for.  This bug has not yet been fixed as of this date.

(define-G2-probe-file-operation write nil
    (if (g2-stream-probe-file-for-exist filename-string-to-use)
        (protected-let
            ((stream?
               (prog1
                   (g2-stream-open-for-appending
                     filename-string-to-use
                     nil)
                 (record-status-of-most-recent-file-operation))
               (g2-stream-close stream?)))
          (cond
            (stream?
             (most-recent-file-operation-succeeded)
             t)
            (t nil)))
        (protected-let
            ((stream?
               (prog1
                   (g2-stream-open-for-output filename-string-to-use)
                 (record-status-of-most-recent-file-operation))
               (progn (g2-stream-close stream?)
                      (g2-stream-delete-file filename-string-to-use))))
          (cond
            (stream?
             (most-recent-file-operation-succeeded)
             t)
            (t nil)))))


;;;; Reading from G2-streams

;;; g2-stream-read-char

;;; Returns a character read from the g2-input-stream or nil (with
;;; g2-stream-error-flag set).

(def-gensym-c-function c-g2_stream_read_char
                       (:fixnum-int "g2ext_str_read_char")
  ((:pointer g2-input-stream)))

#+lisp-streams
(def-substitution-macro g2-stream-read-char-using-lstreams
    (g2-input-stream)
  (or (if random-access-stream-alist
          (let ((random-access-entry?
                  (assq g2-input-stream
                        random-access-stream-alist)))
            (if random-access-entry?
                (prog1 (get-random-access-file-element
                         (cadr random-access-entry?)
                         (cddr random-access-entry?))
                  (incff (cddr random-access-entry?)))
                nil))
          nil)
      ;; Note: there are no cases of this now, but some Lisps may not be able to
      ;; read a character unless g2-stream-character-mode? is true.  This was
      ;; true of the TI Lisp machine, which we now no longer support.
      (read-char g2-input-stream nil nil)))


(def-g2-stream-operation g2-stream-read-char (g2-input-stream)
  (declare (var-is-g2-stream-arg g2-input-stream)
           (version-for-g2-stream-handle-p t)
           (record-status t))

  :c-streams
  (let ((ascii (c-g2_stream_read_char g2-input-stream)))
    (declare (type fixnum ascii))
    (cond ((>=f ascii 0)
           (most-recent-file-operation-succeeded)
           (code-char ascii))
          ;; For speed, we don't call to C a second time to get the true errno.
          ;; All errors are "end of file".
          (t (record-status-of-most-recent-file-operation
               end-of-file-reached-code)
             nil))))


;;; g2-stream-read-non-cr-char

;; G2-stream-read-non-cr-char is used by g2-stream-read-line below.  It is used
;; for those files (usually VMS) which separate lines with a #\Return #\Newline
;; sequence.  (A solitary #\Newline is the expected way to separate lines.)
;; Note: Lisp machines simply read the character as usual, without coalescing
;; #\Newline #\Return sequences.

(def-gensym-c-function c-g2_stream_read_non_cr_char
                       (:fixnum-int "g2ext_str_read_non_cr_char")
  ((:pointer g2-input-stream)))



(def-g2-stream-operation g2-stream-read-non-cr-char (g2-input-stream)
  (declare (record-status t)
           (var-is-g2-stream-arg g2-input-stream)
           (version-for-g2-stream-handle-p t))

  :c-streams
  (let ((ascii (c-g2_stream_read_non_cr_char g2-input-stream)))
    (declare (type fixnum ascii))
    (cond ((>=f ascii 0)
           (most-recent-file-operation-succeeded)
           (coerce-to-wide-character ascii))
          ;; For speed, we don't call to C a second time to get the true errno.
          ;; All errors are "end of file".
          (t (record-status-of-most-recent-file-operation
               end-of-file-reached-code)
             nil))))



;;; g2-stream-read-ascii-byte (g2-stream)

;;; Returns an integer representing the next ascii character available from
;;; g2-stream, which should be an input or bidirectional stream.

(def-g2-stream-operation g2-stream-read-ascii-byte
                        (g2-input-stream)
  (declare (record-status t)
           (var-is-g2-stream-arg g2-input-stream))

  :c-streams
  (let ((ascii (c-g2_stream_read_char g2-input-stream)))
    (declare (type fixnum ascii))
    (cond ((>=f ascii 0)
           (most-recent-file-operation-succeeded)
           ascii)
          ;; For speed, we don't call to C a second time to get the true errno.
          ;; All errors are "end of file".
          (t (record-status-of-most-recent-file-operation
               end-of-file-reached-code)
             nil))))



;;; g2-stream-read-into-string

;;; Returns the number of characters read into the buffer.  If the number of
;;; characters read is less than the number requested for, there was a file read
;;; problem (usually an EOF) and g2-stream-error-flag will be set.

;;; This is generally called for the side effect of putting data into string, so
;;; callers must ensure that a simple gensym string is passed in as the string
;;; arg.

(def-gensym-c-function g2-stream-read-into-string-in-c
                       (:fixnum-int "g2ext_g2_stream_read_string")
  ((:pointer g2-input-stream)
   (:string string)
   (:fixnum-int number-of-characters)
   (:fixnum-int start-index)))


(def-substitution-macro g2-stream-read-into-string-with-read-char
                        (g2-input-stream
                          buffer
                          number-of-characters
                          start-index)
  (loop for index from 0 below number-of-characters
        as character?
           = (g2-stream-read-char-from-handle-macro g2-input-stream)
        do (if (characterp character?)
               (setf (char buffer (+f start-index index)) character?)
               (return index))
        finally
          (return index)))



(def-g2-stream-operation g2-stream-read-into-string
                         (g2-input-stream
                           buffer-as-gensym-string
                           number-of-characters
                           start-index)
  (declare (record-status nil) ;each read-char records a status
           (var-is-g2-stream-arg g2-input-stream))
  :c-streams
  (if (array-has-fill-pointer-p buffer-as-gensym-string)
      (g2-stream-read-into-string-with-read-char
        g2-input-stream
        buffer-as-gensym-string
        number-of-characters
        start-index)
      (g2-stream-read-into-string-in-c
        g2-input-stream
        buffer-as-gensym-string
        number-of-characters
        start-index)))

;; It would be losing to have a non-simple string for a buffer.  Consider not
;; supporting this case?! Also, check if error handling is properly done in the
;; non-simple case, if it is to be supported!  (MHD 2/7/96)




;;; g2-stream-read-line

;;; Returns a line read from the g2-input-stream in a text-string or nil (with
;;; g2-stream-error-flag set).  The text-string has to be reclaimed by the caller.

;;; The default function for `g2-stream-read-line' (i.e.  for systems where
;;; non-consing streams have not been implemented) works like read-line and it
;;; produces a text string which has to be reclaimed by the caller.  However, it
;;; only returns one value: a reclaimable text-string (or nil and sets an
;;; error-flag).  The string has to be recycled using reclaim-text-string by
;;; some other function.  We assume here that the newline character is #\newline
;;; or #\newline followed by line #\Linefeed.  #\Linefeeds are ignored when
;;; contiguous to a #\Newline.

;; jh per jra, 11/11/91.  Extracted g2-stream-read-line-internal-loop from inside
;; the twith-output-to-text-string form, which binds global variables and so
;; prevents register optimizations of anything inside it.  Performance inside this
;; loop is, for obvious reasons, highly critical.  Also changed eql to char= and
;; tprinc to twrite-char, arranged to do the work of (>f (lengthw line) 0) inside
;; the loop, and made the returns from the outer block (the function) rather than
;; the inner block (the loop itself).

(defun g2-stream-read-line-internal-loop (g2-input-stream character?)
  (unless character?
    (return-from g2-stream-read-line-internal-loop nil))
  (loop while character?
        until (char=w #.%Newline character?)
        do
    (twrite-char character?)
    (setq character?
          (g2-stream-read-non-cr-char-from-handle-macro
            g2-input-stream))
    finally
      (return-from g2-stream-read-line-internal-loop
        (or character?
            (g2-stream-eof-p-from-handle-macro g2-input-stream)))))


(def-substitution-macro g2-stream-read-line-internal
                        (g2-input-stream)
  (let* ((valid-line-p nil)
         (line
           (twith-output-to-text-string
             (setq valid-line-p
                   (g2-stream-read-line-internal-loop
                     g2-input-stream
                     (g2-stream-read-non-cr-char-from-handle-macro
                       g2-input-stream))))))
    (cond (valid-line-p line)
          (t (reclaim-text-string line)
             nil))))


(def-g2-stream-operation g2-stream-read-line (g2-input-stream)
  (declare (record-status nil) ;each read-char records a status
           (var-is-g2-stream-arg g2-input-stream))
  :c-streams
  (g2-stream-read-line-internal g2-input-stream))




;;; g2-stream-read-into-buffer

;;; The function `g2-stream-read-into-buffer' takes three arguments: a buffer
;;; string, the number of characters to read into that buffer, and a g2-stream.
;;; If successful, this function returns a positive number of characters read.
;;; If an end-of-file is encountered, this function returns 0.  If an error
;;; occurred, this function returns nil.  This function has the side effect of
;;; recording the status of the file operation in a way that can be accessed by
;;; most-recent-file-operation-status-as-text or
;;; most-recent-file-operation-succeeded-p.

(def-g2-stream-operation g2-stream-read-into-buffer
                         (buffer-string buffer-length g2-input-stream)
  (declare (record-status t)
           (var-is-g2-stream-arg g2-input-stream))

  :c-streams
  (let ((number-of-characters-read
          (g2-stream-read-into-string-in-c
            g2-input-stream
            buffer-string
            buffer-length
            0)))
    ;; jh, 6/3/92.  First, note that fread() is the core of
    ;; g2-stream-read-into-string-in-c and that feof() is the core of
    ;; g2-stream-eof-p.  Harbison & Steele, 3rd edition, p 328, do not specify
    ;; how to check for end-of-file when fread() returns a count intermediate
    ;; between 0 and the number of characters requested, although they advise
    ;; using feof() when a count of 0 is returned.
    ;; When the number of characters requested is small and fread() returns an
    ;; intermediate count, feof() returns 1.  When the number of characters is
    ;; large (say the size of read-kb-buffer, to take a random example), feof()
    ;; returns 0 until the next fread() or fgetc().  Jim has pointed out that it
    ;; is not an error condition when fread() returns an intermediate count --
    ;; maybe some writer has blocked before filling the read buffer.
    (cond
      ((>f number-of-characters-read 0)
       (most-recent-file-operation-succeeded)
       number-of-characters-read)
      ((g2-stream-eof-p-from-handle-macro g2-input-stream)
       (record-status-of-most-recent-file-operation
         end-of-file-reached-code)
       0)
      (t (record-status-of-most-recent-file-operation)
         nil))))





;;; G2-stream-read-into-byte-vector
;;;
;;; SPEC/FUTURE CONTRACT:
;;;
;;; Returns the number of characters read into the buffer.  If the number of
;;; characters read is less than the number requested for, there was a file read
;;; problem (usually an EOF) and g2-stream-error-flag will be set.
;;;
;;;
;;; FOR NOW:
;;;
;;; Always returns the number characters asked to be read into the buffer
;;; (number-of-characters).  It is the responsibility of the caller to know that
;;; this will work out, i.e., that enough characters are available.  Results
;;; otherwise are undefined.  All current users of this function can get by with
;;; this limited fulfullment of the contract.
;;;
;;; In addition, this is not yet optimized to its full potential.  That can
;;; easily be done before the final release of 4.0.
;;;
;;; This will almost certainly later be implemented more efficiently, i.e., as a
;;; C foreign function call.  (MHD 1/22/95)

(defun-simple g2-stream-read-into-byte-vector
    (stream byte-vector number-of-characters start-index)
  (declare (type fixnum number-of-characters start-index))
  (let* ((buffer-size 1024)                ; 1024 == one of the bucket sizes
         (string-buffer (obtain-simple-gensym-string buffer-size)))
    (declare (type fixnum buffer-size))
    (loop for characters-read fixnum = 0 then (+f characters-read chars-to-read)
          while (<f characters-read number-of-characters)
          for chars-to-read fixnum
            = (minf buffer-size (-f number-of-characters characters-read))
          do (g2-stream-read-into-string stream string-buffer chars-to-read 0)
             (loop with byte-vector-start-index fixnum
                     = (+f start-index characters-read)
                   for string-index from 0 below chars-to-read
                   do (setf (byte-vector-aref
                              byte-vector
                              (+f byte-vector-start-index string-index))
                            (char-code (schar string-buffer string-index)))))
    (reclaim-simple-gensym-string string-buffer))
  number-of-characters)

;; Added today for 4.0.  Modules using this are limited to, at present, FONTS
;; and KFEP1.  This should be implemented as a single C foreign function call
;; for maximal performance, which is absolutely required for the both of the
;; current applications!  (MHD 1/22/95)



;;; g2-stream-read-into-wide-string-buffer

(def-gensym-c-function g2-stream-read-into-wide-string-in-c
                       (:fixnum-int "g2ext_g2_stream_read_wide_buffer")
  ((:pointer g2-input-stream)
   (:byte-vector-16 wide-string)
   (:fixnum-int number-of-characters)
   (:fixnum-int start-index)))

(def-gensym-c-function g2-stream-read-octets-into-wide-string-in-c
                       (:fixnum-int "g2ext_g2_stream_read_octets_wide")
  ((:pointer g2-input-stream)
   (:byte-vector-16 wide-string)
   (:fixnum-int number-of-characters)
   (:fixnum-int start-index)))

(def-g2-stream-operation g2-stream-read-into-wide-string-buffer
                         (wide-string-buffer buffer-length g2-input-stream)
  (declare (record-status t)
           (var-is-g2-stream-arg g2-input-stream))

  :c-streams
  (let ((number-of-characters-read
          (g2-stream-read-into-wide-string-in-c
            g2-input-stream
            wide-string-buffer
            buffer-length
            0)))
    (cond
      ((>f number-of-characters-read 0)
       (most-recent-file-operation-succeeded)
       number-of-characters-read)
      ((g2-stream-eof-p-from-handle-macro g2-input-stream)
       (record-status-of-most-recent-file-operation
         end-of-file-reached-code)
       0)
      (t (record-status-of-most-recent-file-operation)
         nil))))

(def-g2-stream-operation g2-stream-read-octets-into-wide-string-buffer
                         (wide-string-buffer buffer-length g2-input-stream)
  (declare (record-status t)
           (var-is-g2-stream-arg g2-input-stream))

  :c-streams
  (let ((number-of-characters-read
          (g2-stream-read-octets-into-wide-string-in-c
            g2-input-stream
            wide-string-buffer
            buffer-length
            0)))
    (cond
      ((>f number-of-characters-read 0)
       (most-recent-file-operation-succeeded)
       number-of-characters-read)
      ((g2-stream-eof-p-from-handle-macro g2-input-stream)
       (record-status-of-most-recent-file-operation
         end-of-file-reached-code)
       0)
      (t (record-status-of-most-recent-file-operation)
         nil))))




;;; `read-text-file-into-wide-string' -- I'm not sure if this needed to be
;;; written.  Maybe it already existed (and its duplicate still does).  Maybe
;;; it's a bad idea.  May need to do a bit more error reporting before it's
;;; ready for prime time.

(defconstant read-file-into-string-buffer-size 2048)

(defvar buffer-for-read-file-into-string (make-string read-file-into-string-buffer-size))

(defun read-text-file-into-wide-string (filename)
  (let ((text-stream? (g2-stream-open-for-input filename)))
    (if text-stream?
        (prog1
            (twith-output-to-text-string
              (loop with length = (g2-stream-file-length text-stream?)
                    with keep-going-p = t
                    with accumulated-length = 0
                    with chars-to-read = (minf length read-file-into-string-buffer-size)
                    while keep-going-p
                    for chars-read = (g2-stream-read-into-buffer
                                       buffer-for-read-file-into-string
                                       chars-to-read text-stream?)
                    do
                (cond
                  ((or (not (fixnump chars-read))
                       (<=f chars-read 0))
                   ;; I'm not sure what's up here.  It seems like g2-stream-file-length
                   ;; does not match up with g2-stream-read-into-buffer very well.  The
                   ;; length returned is usually more than the number of characters we
                   ;; are able to read, yet the read seems to be complete.  Needs more
                   ;; investigation later.  -jv, 2/5/07
                   (setq keep-going-p nil))
                  ((>f chars-read (-f maximum-wide-string-length accumulated-length))
                   #+development
                   (cerror "Go on"
                           "Trying to read a text-file too large")
                   ;; write out as much as will fit in buffer
                   (twrite-portion-of-gensym-string-unparsably
                     buffer-for-read-file-into-string
                     0
                     (-f maximum-wide-string-length accumulated-length 2))
                   (setq keep-going-p nil))
                  (t
                   (incff accumulated-length chars-read)
                   (twrite-portion-of-gensym-string-unparsably buffer-for-read-file-into-string 0 chars-read)
                   (setq chars-to-read (minf (-f length accumulated-length)
                                             read-file-into-string-buffer-size))
                   (setq keep-going-p (=f 0 chars-to-read))))))
          (g2-stream-close text-stream?))
        (make-wide-string 0))))




;;;; Writing into G2-streams


;;; g2-stream-write-char

;;; Writes a character to the g2-output-stream and returns the character if it has
;;; been successfully written to the g2-output-stream and nil (with the
;;; g2-stream-error-flag set) if it has not.  The appropriate end of line sequence
;;; is written if a newline is written.

(def-gensym-c-function c-g2_stream_write_char
                       (:fixnum-int "g2ext_str_write_char")
  ((:fixnum-int character-ascii-code)
   (:pointer g2-output-stream)))



(def-g2-stream-operation g2-stream-write-char
                         (character g2-output-stream)
  (declare (record-status t)
           (var-is-g2-stream-arg g2-output-stream)
           (version-for-g2-stream-handle-p t))

  :c-streams
  (let ((result
          (c-g2_stream_write_char
            (if (wide-character-p character)
                ;; only 8-bit character allowed -- brute force applied here:
                (logandf #xff (wide-character-code character))
                (char-code character))
            g2-output-stream)))
    (declare (type fixnum result))
    (cond ((>=f result 0)
           (most-recent-file-operation-succeeded)
           character)
          (t (record-status-of-most-recent-file-operation)
             nil))))



;;; g2-stream-terpri

;;; Prints the appropriate newline character or newline sequence to
;;; g2-output-stream.  Returns t if no error occurs, or nil if an error occurs.
;;; Note that this is different from Lisp's terpri.

(defconstant g2-stream-terminate-string-with-cr 1)
(defconstant g2-stream-do-not-terminate-string-with-cr 0)

(def-g2-stream-operation g2-stream-terpri (g2-output-stream)
  (declare (record-status t)
           (var-is-g2-stream-arg g2-output-stream)
           (version-for-g2-stream-handle-p t))

  :c-streams
  (let ((result (c-g2_stream_write_string
                  ""
                  g2-output-stream
                  g2-stream-terminate-string-with-cr)))
    (declare (type fixnum result))
    (cond ((>=f result 0)
           (most-recent-file-operation-succeeded)
           t)
          (t (record-status-of-most-recent-file-operation)
             nil))))




;;; g2-stream-write-ascii-byte (ascii-byte g2-stream)

;;; Writes a character represented by the integer ascii-byte onto g2-stream, which
;;; should be an output or bidirectional stream.

(def-g2-stream-operation g2-stream-write-ascii-byte
                         (ascii-byte g2-output-stream)
  (declare (record-status t)
           (var-is-g2-stream-arg g2-output-stream))

  :c-streams
  (let ((result (c-g2_stream_write_char ascii-byte g2-output-stream)))
    (declare (type fixnum result))
    (cond ((>=f result 0)
           (most-recent-file-operation-succeeded)
           ascii-byte)
          (t (record-status-of-most-recent-file-operation)
             nil))))



;;; g2-stream-write-string

;;; Writes the string to the g2-output-stream and returns the string if it has
;;; been successfully written to the g2-output-stream and nil if it has not.  The
;;; string is not reclaimed.

;;; Bug/caveat: this stops output upon encountering the character #\Null (code =
;;; 0) within output-string.  C.f., g2-stream-write-from-buffer and
;;; g2-stream-write-from-wide-string-buffer.

(def-g2-stream-operation g2-stream-write-string
                         (string g2-output-stream)
  (declare (record-status nil) ;each write-char records a status
           (var-is-g2-stream-arg g2-output-stream))
  :c-streams
  (let ((result
          (c-g2_stream_write_string
            string
            g2-output-stream
            g2-stream-do-not-terminate-string-with-cr)))
    (declare (type fixnum result))
    (if (>=f result g2-stream-foreign-file-op-success)
        string
        nil)))

;; I consider the issue with fill pointers obsolete, since the C functions
;; already deal with translating non-simple gensym strings into simple gensym
;; strings.  Therefore, code to deal with fill-pointered gensym strings
;; specially (and slowly) has been flushed here.  Needs to be tested well, as
;; usual. (MHD 2/7/96)




;;; G2-stream-tformat

;;; This macro is like tformat, but it writes its output to the first argument,
;;; a g2-stream.   It is indeed based on tformat, and so takes all of the same
;;; format directives.

(defmacro g2-stream-tformat (g2-stream format-string &rest format-args)
  (avoiding-variable-capture (g2-stream &aux result-string)
    `(let ((,result-string (tformat-text-string ,format-string ,@format-args)))
       (g2-stream-write-string ,result-string ,g2-stream)
       (reclaim-text-string ,result-string))))




;;; The function `write-gensym-pathname' takes a gensym-pathname and twrites it
;;; to the current writing context.  Note that it writes using gensym characters,
;;; i.e., converting from ASCII or whatever to the Gensym character set.

(defun write-gensym-pathname (gensym-pathname)
  (let ((namestring (gensym-namestring-as-text-string gensym-pathname)))
    (twrite-string namestring)
    (reclaim-text-string namestring)))




;;; g2-stream-write-line

;;; The same as g2-stream-write-string, except that the appropriate newline
;;; character (or sequence of characters) is printed after the last character of
;;; the string.

;;; Bug/caveat: this stops output upon encountering the character #\Null (code =
;;; 0) within string.  C.f., g2-stream-write-from-buffer and
;;; g2-stream-write-from-wide-string-buffer.

(def-g2-stream-operation g2-stream-write-line
                         (string g2-output-stream)
  (declare (record-status nil) ;each write-char records a status
           (var-is-g2-stream-arg g2-output-stream))
  :c-streams
  (let ((result
          (c-g2_stream_write_string        ; fill-pointered case done away with! (MHD 2/7/96)
            string
            g2-output-stream
            g2-stream-terminate-string-with-cr)))
    (declare (type fixnum result))
    (if (>=f result g2-stream-foreign-file-op-success)
        string
        nil)))

;;; G2-stream-write-from-buffer ... can handle any characters, including null.

(def-gensym-c-function g2-stream-write-from-string-in-c
                       (:fixnum-int "g2ext_g2_stream_write_buffer")
  ((:pointer g2-input-stream)
   (:string string)
   (:fixnum-int number-of-characters)
   (:fixnum-int start-index)))

(def-g2-stream-operation g2-stream-write-from-buffer
                         (buffer buffer-length g2-output-stream)
  (declare (record-status t)
           (var-is-g2-stream-arg g2-output-stream))

  :c-streams
  (let ((number-of-characters-written
          (g2-stream-write-from-string-in-c
            g2-output-stream
            buffer
            buffer-length
            0)))
    (cond
      ((=f number-of-characters-written buffer-length)
       (most-recent-file-operation-succeeded)
       t)
      (t (record-status-of-most-recent-file-operation)
         nil))))


;;; g2-stream-write-from-wide-string-buffer

(def-gensym-c-function g2-stream-write-from-wide-string-in-c
                       (:fixnum-int "g2ext_g2_stream_write_wide_buffer")
  ((:pointer g2-input-stream)
   (:byte-vector-16 wide-string)
   (:fixnum-int number-of-characters)
   (:fixnum-int start-index)))

(def-g2-stream-operation g2-stream-write-from-wide-string-buffer
                         (wide-string-buffer buffer-length g2-output-stream)
  (declare (record-status t)
           (var-is-g2-stream-arg g2-output-stream))

  :c-streams
  (let ((number-of-characters-written
          (g2-stream-write-from-wide-string-in-c
            g2-output-stream
            wide-string-buffer
            buffer-length
            0)))
    (cond
      ((=f number-of-characters-written buffer-length)
       (most-recent-file-operation-succeeded)
       t)
      (t (record-status-of-most-recent-file-operation)
         nil))))





;;;; Writing Text Strings and Wide Characters to G2 Streams



;;; `Write-text-string-to-stream' ... At present, this outputs lines of text in
;;; UTF-G (Gensym-encoded Universal Transformation Format for Unicode), but
;;; translates newline characters into the newline character(s) that
;;; g2-stream-terpri, q.v., likes to emit.  Other characters sets, formats,
;;; and/or encodings may be possible in the future.

(defun write-text-string-to-stream (text-string stream)
  (loop with message-length = (text-string-length text-string)
        for index from 0 below message-length
        for message-char = (charw text-string index)
        do (cond
             ((newline-p message-char)
              (when (null (g2-stream-terpri stream))
                (return-from write-text-string-to-stream nil)))
             (t
              ;; write the char.
              (when (null (write-wide-character-to-stream-in-UTF-G message-char stream))
                (return-from write-text-string-to-stream nil))))
        finally
          (return t)))


;;; `Write-wide-character-to-stream-in-UTF-G' writes wide-character to using
;;; UTF-G.  This will result in at least 1 and most 8 characters being written.

(defun write-wide-character-to-stream-in-UTF-G (wide-character stream)
  (let ((temporary-gensym-string
          ;; later: bind HAN interpretation mode appropriately / heuristically!
          ;; later: translate to other character sets/encodings (e.g., UTF-8)!
          (twith-output-to-gensym-string
            (multiple-value-bind (gensym-character-code extended-code?)
                (map-unicode-to-gensym-character-code
                  (wide-character-code wide-character))
              (multiple-value-bind (character-or-character-code escape-character?)
                  (gensym-character-code-to-pair gensym-character-code)
                (twrite-gensym-character character-or-character-code escape-character?)
                (when extended-code?
                  (multiple-value-bind (extended-character-or-character-code?
                                         extended-escape-character?)
                      (gensym-character-code-to-pair extended-code?)
                    (twrite-gensym-character
                      extended-character-or-character-code?
                      extended-escape-character?))))))))
    (prog1 (g2-stream-write-string temporary-gensym-string stream)
      (reclaim-gensym-string temporary-gensym-string))))


;;; `write-wide-string-into-text-file'

(defun write-wide-string-into-text-file (wide-string filename)
  (let* ((text-stream? (g2-stream-open-for-output filename)))
    (cond
      (text-stream?
       (g2-stream-write-string wide-string text-stream?)
       (g2-stream-close text-stream?))
      (t nil))))





;;;; Directory Access

;;; g2-stream-delete-file <namestring>

;;; Deletes a file.  Returns nil if an error occurred while renaming; returns t
;;; otherwise.

(def-gensym-c-function c-g2_stream_delete_file
                       (:fixnum-int "g2ext_str_delete_file")
  ((:string namestring)))

(def-gensym-c-function c-g2_stream_delete_file_wide
                       (:fixnum-int "g2ext_str_delete_file_s16")
  ((:wide-string namestring)))

(defun g2-delete-file-internal (filename-string-to-use)
  (if (use-unicode-for-filenames)
    (c-g2_stream_delete_file_wide filename-string-to-use)
    (c-g2_stream_delete_file filename-string-to-use)))

(def-g2-stream-operation g2-stream-delete-file (namestring)
  (declare (record-status t)
           (var-is-file-namestring namestring))
  :c-streams
  (let ((status (g2-delete-file-internal namestring)))
    (cond ((=f status g2-stream-foreign-file-op-failure)
           (record-status-of-most-recent-file-operation)
           nil)
          (t (most-recent-file-operation-succeeded)
             t))))

;;; g2-stream-rename-file

;;; Renames a file.  Returns nil if an error occurred while renaming; returns t
;;; otherwise.

(def-gensym-c-function c-g2_stream_rename_file
                       (:fixnum-int "g2ext_str_rename_file")
  ((:string old-namestring)
   (:string new-namestring)))

(def-gensym-c-function c-g2_stream_rename_file_wide
                       (:fixnum-int "g2ext_str_rename_file_s16")
  ((:wide-string old-namestring)
   (:wide-string new-namestring)))

(defun g2-rename-file-internal (old-namestring new-namestring)
  (if (use-unicode-for-filenames)
    (c-g2_stream_rename_file_wide old-namestring new-namestring)
    (c-g2_stream_rename_file old-namestring new-namestring)))

(def-g2-stream-operation g2-stream-rename-file
                         (old-namestring new-namestring)
  (declare (record-status t)
           (var-is-file-namestring old-namestring new-namestring))
  :c-streams
  (let ((status (g2-rename-file-internal old-namestring new-namestring)))
    (cond ((=f status g2-stream-foreign-file-op-failure)
           (record-status-of-most-recent-file-operation)
           nil)
          (t (most-recent-file-operation-succeeded)
             t))))


;;; g2-stream-copy-file

;;; Copies a file.  Returns nil if an error occurred while renaming; returns t
;;; otherwise.

(def-gensym-c-function c-g2_stream_copy_file
                       (:fixnum-int "g2ext_str_copy_file")
  ((:string old-namestring)
   (:string new-namestring)))

(def-gensym-c-function c-g2_stream_copy_file_wide
                       (:fixnum-int "g2ext_str_copy_file_s16")
  ((:wide-string old-namestring)
   (:wide-string new-namestring)))

(defun g2-copy-file-internal (old-namestring new-namestring)
  (if (use-unicode-for-filenames)
    (c-g2_stream_copy_file_wide old-namestring new-namestring)
    (c-g2_stream_copy_file old-namestring new-namestring)))

(def-g2-stream-operation g2-stream-copy-file
                         (old-namestring new-namestring)
  (declare (record-status t)
           (var-is-file-namestring old-namestring new-namestring))

  :c-streams
  (let ((status (g2-copy-file-internal old-namestring new-namestring)))
    (cond ((=f status g2-stream-foreign-file-op-failure)
           (record-status-of-most-recent-file-operation)
           nil)
          (t (most-recent-file-operation-succeeded)
             t))))


;;; g2-stream-directory <dirspec> <filespec>

;;; Returns a list of text strings naming all the files in the directory specified
;;; by directory-substring and name-substring.  The list is composed of
;;; path-conses created by the conser in the PATHNAMES module.  Using the value of
;;; the macro (local-file-system) for file-system-symbol will almost always be
;;; right.  G2-stream-directory is the interface function for the higher-level
;;; function gensym-directory in the PATHNAMES module.  Gensym-directory coerces
;;; its argument into a namestring, duplicating Common Lisp behavior but with
;;; consing control.  G2-stream-directory should not be used elsewhere without a
;;; compelling reason.


(defconstant g2-stream-directory-success 1)

;; G2-stream-directory-buffer-length must be collated with the maximum allowed
;; directory and filename lengths in VMS and UNIX.  This currently (6/4/90)
;; appears to be 255.
;SS_ERROR
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter g2-stream-directory-buffer-length 255)
)

(defvar g2-stream-directory-buffer
        (obtain-text-string #.g2-stream-directory-buffer-length))

;; jh, 9/10/91.  Removed the with-unmoveable-object-creation wrapper from the
;; variable g2-stream-directory-buffer This wrapper is only necessary when we
;; intend to pass a pointer to a C asynchronous process and then resume Lisp
;; processing, thereby creating the risk that the pointer will be relocated by
;; garbage collection.  There is no such risk for g2-stream-directory-buffer,
;; since is is never passed to an asynchronous C process.  Note that an
;; asynchronous file facility may not change this picture.  The current prototype
;; uses a separate C process to perform the file operations, and this process uses
;; no Lisp pointers since it communicates exclusively through ICP.

;; G2-stream-directory-initialized-p is not vulnerable to lisp time-slicing, since
;; G2-streams are not used on such platforms (they have no C call-outs).

(defparameter g2-stream-directory-initialized-p nil)



;;;; Unique Filenames


;;; `size-for-temp-filename' - stdio.h in the gcc-lib we use for Solaris wants a
;;; buffer 25 characters wide for tmpnam.  How profligate.  On Windows, it wants
;;; MAX_PATH, which I found to be 260.  Add on another 10 just to be sure.

(defconstant size-for-temp-filename 270)


;;; `unique-temp-filename' - a single, statically allocated buffer (a "gensym
;;; string", aka a Lisp string, aka a C "char *" with some data around it) which
;;; is used for any call to c-make_unique_filename.  Its value must immediately
;;; be copied out or face being overwritten.

(defvar unique-temp-filename (make-string size-for-temp-filename))


;;; `c-make_unique_filename' - as the local variable name says, identifier is
;;; merely a suggestion.  In fact, on Unix we ignore it.

(def-gensym-c-function c-make_unique_filename
                       (:fixnum-int "g2ext_make_unique_filename")
  ((:string id-suggestion)
   (:fixnum-int buffer-size)
   (:string buffer)))


;;; `make-unique-file-name' - doesn't do much but call c-make_unique_filename,
;;; especially outside of development.  The values (1, -1, -2) should probably
;;; be defconstants here, with matching #define's in C, but it's not worth it
;;; at this time.  Note I don't use a case statement here because someone once
;;; told me that fixnums weren't immediate.  Even though they are (in practice).

(defun make-unique-file-name (identifier)
  (let ((status (c-make_unique_filename
                  identifier size-for-temp-filename
                  unique-temp-filename)))
    (cond
      ((=f 1 status)
       (copy-null-terminated-string-as-text-string unique-temp-filename))
      ((=f -1 status)
       #+development
       (cerror "Go on, returning nil"
               "c-make_unique_filename reports buffer too small; increase size of size-for-temp-filename?")
       nil)
      ((=f -2 status)
       #+development
       (cerror "Go on, returning nil"
               "c-make_unique_filename reports unspecified error generating filename")
       nil)
      (t
       #+development
       (cerror "Go on, returning nil"
               "c-make_unique_filename reports unrecognized return value")
       nil))))




;;;; Regular expression matching for directory contents ...

;; jh, 1/2/92.  Added platform-independent machinery for matching UNIX regular
;; expressions, such as those found in file specifications.  This will make
;; things easier for Porting, since previously every new platform required
;; delving into how regular expression matching was handled by that dialect of
;; UNIX.  It will also counteract the fact that some platforms are sloppy about
;; memory-managing the compiled match pattern.  As well, almost all platforms
;; use malloc and free to create and reclaim this compiled pattern.  Since these
;; functions are not guaranteed to operate in real time, sidestepping them would
;; be a plus.  Note that G2 on VMS (the worst offender when it comes to platform
;; specificity) will also use this regular expression language.

;;; Documentation for G2 users:

;;; The only places regular expressions are available to the G2 user as of
;;; 1/9/95 are in the "load file" edit box and in the system procedures
;;; files-in-directory() and subdirectories-in-directory().  The text typed into
;;; the "load file" edit box and the text argument to these procedures can
;;; contain regular expressions.  The regular expression language used in G2 is
;;; a subset of that found in most UNIX systems, and works on all platforms,
;;; including VMS.  For the purpose of this exposition, a regular expression is
;;; a sequence of ordinary characters and metacharacters.  Metacharacters
;;; include the question mark ?, curly braces {}, the exclamation point !, and
;;; the asterisk *.  They are not interpreted literally, but have special
;;; properties in the match.  This table describes them.

;;;   *       matches zero or more characters
;;;   ?       matches any single character
;;;   {xyz}   matches a single character, either x, y, or z
;;;   {xyz}*  matches zero or more occurrences of either x, y, or z
;;;   !       changes the following character from a metacharacter to an ordinary one
;;;   (xyz)   matches the regular expression xyz [in progress]
;;;   (xyz)*  matches zero or more occurrences of the regular expression xyz [in progress]

;;; The member-of-set metacharacter on typical UNIX systems is the square
;;; bracket [].  The rationale for choosing curly braces instead is to make
;;; things easier on VMS file systems, where the square bracket has another
;;; meaning (it delimits the beginning and end of the directory portion of the
;;; filename).

;;; The single escape character on typical UNIX systems is the backslash \.  The
;;; rationale for choosing the exclamation point instead is to make things
;;; easier on NT and DOS-based file systems, where the backslash has another
;;; meaning (it delimits directory components).

;;; Any charcter that is not a metacharacter is an ordinary character.  An
;;; ordinary character matches an identical one in the string.  Character case
;;; matters when making the match.

;;; Examples:
;;; pattern "greetings" matches string "greetings"
;;; pattern "Greetings" fails to match string "greetings"
;;; pattern "gr*s*" matches string "greetings"
;;; pattern "g*x" fails to match string "greetings"
;;; pattern "greetin?s" matches string "greetings"
;;; pattern "greetin??s" fails to match string "greetings"
;;; pattern "gr{def}etings" matches string "greetings"
;;; pattern "gr{def}tings" fails to match string "greetings"
;;; pattern "gr{def}*tings" matches string "greetings"
;;; pattern "gr{xyz}*eetings" matches string "greetings"
;;; pattern "gr{xyz}*tings" fails to match string "greetings"
;;; pattern "{!{}greet!*ings{!}}" matches string "{greet*ings}"

;; Not included yet:
;;   negation of sets
;;   range in sets
;;   beginning-of-sequence and end-of-sequence
;;   variable binding
;;   subsequences [in progress]

;;; Internal interface to regular expressions:

;;; compile-regular-expression <expression-string>
;;; Converts <expression-string> to a more efficient internal form that may be
;;; reused in successive matches.

;;; reclaim-compiled-regular-expression <compiled-expression>
;;; Reclaims the memory used by <compiled-expression>.

;;; match-regular-expression <compiled-expression> <string-to-match>
;;; Returns non-nil if <string-to-match> matches <compiled-expression>, nil
;;; otherwise.  On delivery platforms, <string-to-match> is a null-terminated C
;;; string.  In development, <string-to-match> is a Lisp string.

;;; wild-regular-expression-string-p <string>
;;; Returns non-nil if <string> is capable of matching more than one other string,
;;; nil otherwise.  Used in wild-pathname-p in PATHNAMES.

(defconser regexp STREAMS)

(def-structure (regular-expression-node
                 (:reclaimer unused-node-reclaimer))
  (next-regular-expression-node nil))

(def-structure (regular-expression-node-for-single-character
                 (:include regular-expression-node)
                 (:constructor
                   make-regular-expression-node-for-single-character
                   (single-character-in-regular-expression))
                 (:reclaimer
                   reclaim-regular-expression-node-for-single-character))
  single-character-in-regular-expression)

(def-structure (regular-expression-node-for-single-wild-character
                 (:include regular-expression-node)
                 (:constructor
                   make-regular-expression-node-for-single-wild-character ())
                 (:reclaimer
                   reclaim-regular-expression-node-for-single-wild-character))
  )

(def-structure (multiply-wild-regular-expression-node
                 (:include regular-expression-node))
  index-of-next-resumed-wild-match-attempt
  index-of-final-resumed-wild-match-attempt)

(def-structure (regular-expression-node-for-wild-characters
                 (:include multiply-wild-regular-expression-node)
                 (:constructor
                   make-regular-expression-node-for-wild-characters ())
                 (:reclaimer
                   reclaim-regular-expression-node-for-wild-characters)))

(def-structure (regular-expression-node-for-set-of-characters
                 (:include multiply-wild-regular-expression-node)
                 (:constructor
                   make-regular-expression-node-for-set-of-characters ())
                 (:reclaimer
                   reclaim-regular-expression-node-for-set-of-characters))
  (set-of-characters-in-regular-expression nil)
  (wild-occurrences-of-characters-in-set-p nil))

(def-structure (regular-expression-node-for-subexpression
                (:include multiply-wild-regular-expression-node)
                (:constructor
                 make-regular-expression-node-for-subexpression
                 (compiled-regular-subexpression))
                (:reclaimer
                 reclaim-regular-expression-node-for-subexpression))
  (compiled-regular-subexpression nil)
  (backtracking-nodes-for-subexpression nil)
  (link-to-next-subexpression-node-for-reclaiming nil)
  (wild-occurrences-of-subexpression-p nil))

(def-system-variable first-subexpression-node-for-reclaiming? STREAMS nil nil t)

(def-substitution-macro push-new-subexpression-node-for-reclaiming (new-node)
  (when first-subexpression-node-for-reclaiming?
    (setf (link-to-next-subexpression-node-for-reclaiming new-node)
          first-subexpression-node-for-reclaiming?))
  (setq first-subexpression-node-for-reclaiming? new-node))

(defun reclaim-regular-expression-node (node)
  (cond
    ((regular-expression-node-for-single-character-p node)
     (reclaim-regular-expression-node-for-single-character node))
    ((regular-expression-node-for-single-wild-character-p node)
     (reclaim-regular-expression-node-for-single-wild-character node))
    ((regular-expression-node-for-wild-characters-p node)
     (reclaim-regular-expression-node-for-wild-characters node))
    ((regular-expression-node-for-set-of-characters-p node)
     (let ((character-set?
             (set-of-characters-in-regular-expression node)))
       (when character-set?
         (reclaim-regexp-list character-set?)))
     (reclaim-regular-expression-node-for-set-of-characters node))
    ((regular-expression-node-for-subexpression-p node)
     (let ((regular-subexpression? (compiled-regular-subexpression node)))
       (when regular-subexpression?
         (reclaim-regular-expression-node regular-subexpression?)))
     (let ((backtracking-nodes? (backtracking-nodes-for-subexpression node)))
       (when backtracking-nodes?
         (reclaim-regexp-list backtracking-nodes?)))
     (setf (link-to-next-subexpression-node-for-reclaiming node) nil))
    #+development
    (t (error "RECLAIM-REGULAR-EXPRESSION-NODE: unknown node type."))))

(defun reclaim-compiled-regular-expression (compiled-expression)
  (loop for this-node? = compiled-expression
                       then (next-regular-expression-node this-node?)
        while this-node?
        do (reclaim-regular-expression-node this-node?)))

(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar single-escape-character-for-gensym-filenames #.%\! )
)

(defun wild-regular-expression-string-p (possibly-wild-string)
  (loop for index from 0 below (lengthw possibly-wild-string)
        for this-char = (charw possibly-wild-string index)
        with escape-mode-p = nil
        do
    (cond ((wide-character-member this-char '(#.%\* #.%\? #.%\{ #.%\}))
           (if escape-mode-p
               (setq escape-mode-p nil)
               (return t)))
          ((char=w single-escape-character-for-gensym-filenames this-char)
           (if escape-mode-p
               (setq escape-mode-p nil)
               (setq escape-mode-p t)))
          (t (setq escape-mode-p nil)))))



(defun compile-regular-expression (expression-string)
  (let ((expression-length (lengthw expression-string)))
    (compile-regular-expression-1 expression-string 0 expression-length)))

(defun compile-regular-expression-1
       (expression-string start-index expression-length)
  (macrolet ((recursive-p () `(>f start-index 0))
             (attach-match (new-node)        ;new-node must not have side effects
               `(progn (when previous-node?
                            (setf (next-regular-expression-node previous-node?)
                               ,new-node))
                 (setq previous-node? ,new-node)))
             (attach-literal-match (this-char)
               `(progn (setq single-character-escape-mode-p nil)
                 (let ((new-node
                        (make-regular-expression-node-for-single-character
                         ,this-char)))
                   (attach-match new-node))))
             (add-to-match-set (this-char)
               `(progn (setq single-character-escape-mode-p nil)
                 (regexp-push
                  ,this-char
                  (set-of-characters-in-regular-expression
                   previous-node?)))))
    (loop for current-index from start-index below expression-length
          for this-char = (charw expression-string current-index)
          with first-node? = nil
          with previous-node? = nil
          with gathering-set-of-characters-p = nil
          with single-character-escape-mode-p = nil
          do
      (wide-character-case this-char
        (#.%\*
         (cond
           (gathering-set-of-characters-p
            (add-to-match-set this-char))
           (single-character-escape-mode-p
            (attach-literal-match this-char))
           ((regular-expression-node-for-wild-characters-p
             previous-node?))
           ((and (regular-expression-node-for-set-of-characters-p
                  previous-node?)
                 (not (wild-occurrences-of-characters-in-set-p
                       previous-node?)))
            (setf (wild-occurrences-of-characters-in-set-p
                   previous-node?)
                  t))
           (t (let ((new-node
                     (make-regular-expression-node-for-wild-characters)))
                (attach-match new-node)))))
        (#.%\?
         (cond
           (gathering-set-of-characters-p
            (add-to-match-set this-char))
           (single-character-escape-mode-p
            (attach-literal-match this-char))
           (t (let ((new-node
                     (make-regular-expression-node-for-single-wild-character)))
                (attach-match new-node)))))
        #+not-yet
        (#.%\(
         (cond
           (gathering-set-of-characters-p
            (add-to-match-set this-char))
           (single-character-escape-mode-p
            (attach-literal-match this-char))
           (t (multiple-value-bind (compiled-subexpression? closing-index?)
                  (compile-regular-expression-1
                   expression-string
                   (1+f current-index)
                   expression-length)
                (if compiled-subexpression?
                    (let ((new-node
                           (make-regular-expression-node-for-subexpression
                            compiled-subexpression?)))
                      (attach-match new-node)
                      (if closing-index?
                          (setq current-index closing-index?)
                          (return (values first-node? nil))))
                    (attach-literal-match this-char))))))
        #+not-yet
        (#.%\)
         (cond
           (gathering-set-of-characters-p
            (add-to-match-set this-char))
           (single-character-escape-mode-p
            (attach-literal-match this-char))
           (t (if (recursive-p)
                  (return (values first-node? current-index))
                  (attach-literal-match this-char)))))
        (#.%\{
         (cond
           (gathering-set-of-characters-p
            (add-to-match-set this-char))
           (single-character-escape-mode-p
            (attach-literal-match this-char))
           (t (let ((new-node
                     (make-regular-expression-node-for-set-of-characters)))
                (attach-match new-node)
                (setq gathering-set-of-characters-p t)))))
        (#.%\}
         (cond
           ((and gathering-set-of-characters-p single-character-escape-mode-p)
            (add-to-match-set this-char))
           (gathering-set-of-characters-p
            (setq gathering-set-of-characters-p nil))
           (t (attach-literal-match this-char))))
        (#.single-escape-character-for-gensym-filenames
         (cond
           ((and gathering-set-of-characters-p single-character-escape-mode-p)
            (add-to-match-set this-char))
           (single-character-escape-mode-p
            (attach-literal-match this-char))
           (t (setq single-character-escape-mode-p t))))
        (otherwise
         (cond
           (gathering-set-of-characters-p
            (add-to-match-set this-char))
           (t (attach-literal-match this-char)))))
      (unless first-node?
        (when previous-node?
          (setq first-node? previous-node?)))
          finally (return (values first-node? nil)))))

(defun regular-expression-node-matches-single-char-p (node char)
  (cond
    ((regular-expression-node-for-single-character-p node)
     (eqlw char (single-character-in-regular-expression node)))
    ((regular-expression-node-for-single-wild-character-p node)
     t)
    ((regular-expression-node-for-wild-characters-p node)
     t)
    ((regular-expression-node-for-set-of-characters-p node)
     (wide-character-member
       char
       (set-of-characters-in-regular-expression node)))
    ((regular-expression-node-for-subexpression-p node)
     (let ((subexpression? (compiled-regular-subexpression node)))
       (and subexpression?
            (regular-expression-node-matches-single-char-p
             subexpression?
             char))))
    #+development
    (t (error "REGULAR-EXPRESSION-NODE-MATCHES-SINGLE-CHAR-P: ~
               unknown node type."))))

(defun compiled-regular-expression-matches-zero-characters-p
       (compiled-expression)
  (loop for possibly-wild-node
            = compiled-expression
            then (next-regular-expression-node
                   possibly-wild-node)
        while possibly-wild-node
        always
          (or (regular-expression-node-for-wild-characters-p
                possibly-wild-node)
              (and (regular-expression-node-for-set-of-characters-p
                     possibly-wild-node)
                   (wild-occurrences-of-characters-in-set-p
                     possibly-wild-node))
              (and (regular-expression-node-for-subexpression-p
                    possibly-wild-node)
                   (wild-occurrences-of-subexpression-p
                    possibly-wild-node)))))

(defun match-regular-expression (compiled-expression string-to-match)
  (when (or (string=w string-to-match #w"")
            (and (>f (lengthw string-to-match) 0)
                 (char=w (charw string-to-match 0) #.%Null)))
    (return-from match-regular-expression
      (compiled-regular-expression-matches-zero-characters-p
       compiled-expression)))
  (let ((final-index-in-string-to-match
         (1-f
          #-chestnut-trans
          (or (position-in-wide-string #.%Null string-to-match)
              (lengthw string-to-match))
          #+chestnut-trans
          (position-in-wide-string #.%Null string-to-match)
          ))
        (first-subexpression-node-for-reclaiming? nil))
    (multiple-value-bind (index-of-first-non-matching-char? backtracking-nodes?)
        (match-regular-expression-given-backtracking-nodes
         compiled-expression
         string-to-match
         final-index-in-string-to-match
         nil)
      (when first-subexpression-node-for-reclaiming?
        (loop for this-subexpression-node?
              = first-subexpression-node-for-reclaiming?
              then (prog1
                       (link-to-next-subexpression-node-for-reclaiming
                        this-subexpression-node?)
                     (setf (link-to-next-subexpression-node-for-reclaiming
                            this-subexpression-node?)
                           nil))
              while this-subexpression-node?
              do
              (let ((backtracking-subnodes?
                     (backtracking-nodes-for-subexpression
                      this-subexpression-node?)))
                (when backtracking-subnodes?
                  (reclaim-regexp-list backtracking-subnodes?)
                  (setf (backtracking-nodes-for-subexpression
                         this-subexpression-node?)
                        nil)))))
      (when backtracking-nodes?
        (reclaim-regexp-list backtracking-nodes?))
      (and index-of-first-non-matching-char? t))))

(defun minimum-number-of-characters-required-for-match
       (compiled-regular-expression)
  (loop for this-node? = compiled-regular-expression
        then (next-regular-expression-node this-node?)
        while this-node?
        sum
        (cond
          ((regular-expression-node-for-single-character-p this-node?)
           1)
          ((regular-expression-node-for-single-wild-character-p this-node?)
           1)
          ((regular-expression-node-for-wild-characters-p this-node?)
           0)
          ((regular-expression-node-for-set-of-characters-p this-node?)
           (if (wild-occurrences-of-characters-in-set-p this-node?)
               0
               1))
          ((regular-expression-node-for-subexpression-p this-node?)
           (if (wild-occurrences-of-subexpression-p this-node?)
               0
               (let ((subexpression?
                      (compiled-regular-subexpression this-node?)))
                 (if subexpression?
                     (minimum-number-of-characters-required-for-match
                      subexpression?)
                     0))))
          (t
           #+development
           (error "MINIMUM-NUMBER-OF-CHARACTERS-REQUIRED-FOR-MATCH: ~
                   unknown regular expression node ~a"
                  this-node?)
           0))))

(defun match-regular-expression-given-backtracking-nodes
    (compiled-expression
     string-to-match
     final-index-in-string-to-match
     resumable-wild-character-match-nodes?)
  (loop with current-index = 0
        for this-char = (charw string-to-match current-index)
        with this-node? = compiled-expression
        with need-to-backtrack-p = nil
        with match-failed-p = nil
        while this-node?
        do
        (cond
          ((regular-expression-node-for-wild-characters-p this-node?)
           (let ((next-node?
                  (next-regular-expression-node this-node?)))
             (if next-node?
                 ;; If there is a subsequent node, find the most distant character
                 ;; that matches it.
                 (loop for backwards-index
                       from final-index-in-string-to-match by -1
                       until
                       (or (>=f current-index backwards-index)
                           (regular-expression-node-matches-single-char-p
                            next-node?
                            (charw string-to-match backwards-index)))
                       finally
                         ;; Establish a backtrack point unless zero characters were
                         ;; absorbed.
                       (when (>f backwards-index current-index)
                         (setf (index-of-next-resumed-wild-match-attempt
                                this-node?)
                               backwards-index)
                         (setf (index-of-final-resumed-wild-match-attempt
                                this-node?)
                               current-index)
                         (regexp-push this-node?
                                      resumable-wild-character-match-nodes?))
                       (setq current-index backwards-index)
                       (setq this-node? next-node?))
                 ;; Else this is the last node in the pattern, so the match has
                 ;; succeeded.
                 (loop-finish))))

          ((regular-expression-node-for-single-wild-character-p this-node?)
           (setq this-node?
                 (next-regular-expression-node this-node?))
           (incf current-index))

          (;; Zero of more occurrences from a set of characters.
           (and (regular-expression-node-for-set-of-characters-p this-node?)
                (wild-occurrences-of-characters-in-set-p this-node?))
           (let* ((characters-in-set
                   (set-of-characters-in-regular-expression this-node?))
                  (final-index-of-member-of-set?
                   (loop for subindex from current-index
                                      to final-index-in-string-to-match
                                      unless (wide-character-member
                                               (charw string-to-match subindex)
                                               characters-in-set)
                                      do (return subindex)
                                      finally (return nil)))
                  (next-node?
                   (next-regular-expression-node this-node?)))
             (cond
               (;; Match ends within the string.
                final-index-of-member-of-set?
                (loop for backwards-index
                      from final-index-of-member-of-set? by -1
                      until
                      (or (=f current-index backwards-index)
                          (and next-node?
                               (regular-expression-node-matches-single-char-p
                                next-node?
                                (charw string-to-match backwards-index))))
                      finally
                        ;; Establish a backtrack point unless zero characters were
                        ;; absorbed.
                      (when (>f backwards-index current-index)
                        (setf (index-of-next-resumed-wild-match-attempt
                               this-node?)
                              backwards-index)
                        (setf (index-of-final-resumed-wild-match-attempt
                               this-node?)
                              current-index)
                        (regexp-push this-node?
                                     resumable-wild-character-match-nodes?))
                      (setq this-node? next-node?)
                      (setq current-index backwards-index)))
               (t;; Match may extend to the end of the string.
                (when next-node?
                  (setf (index-of-next-resumed-wild-match-attempt
                         this-node?)
                        (1+ final-index-in-string-to-match))
                  (setf (index-of-final-resumed-wild-match-attempt
                         this-node?)
                        current-index)
                  (regexp-push this-node?
                               resumable-wild-character-match-nodes?))
                (setq this-node? next-node?)
                (setq current-index (1+ final-index-in-string-to-match))))))

          (;; Exactly one occurrence from a set of characters.
           (regular-expression-node-for-set-of-characters-p this-node?)
           (cond ((wide-character-member
                    this-char
                    (set-of-characters-in-regular-expression this-node?))
                  (setq this-node?
                        (next-regular-expression-node this-node?))
                  (incf current-index))
                 (t (setq need-to-backtrack-p t))))

          ((regular-expression-node-for-single-character-p this-node?)
           (cond ((eqlw this-char
                        (single-character-in-regular-expression this-node?))
                  (setq this-node?
                        (next-regular-expression-node this-node?))
                  (incf current-index))
                 (t (setq need-to-backtrack-p t)))))

        ;; If we are at the end of the string and have some compiled nodes left, we
        ;; need to backtrack unless every remaining node accepts zero characters.
        (when (>f current-index final-index-in-string-to-match)
          (when this-node?
            (unless (compiled-regular-expression-matches-zero-characters-p
                     this-node?)
              (setq need-to-backtrack-p t))))

        (cond
          (;; Some wild node needs to absorb fewer characters and we need to start
           ;; from that point.
           need-to-backtrack-p
           (setq need-to-backtrack-p nil)
           (let ((resumable-node?
                  (car resumable-wild-character-match-nodes?)))
             (cond
               (resumable-node?
                (let ((this-match-index
                       (1-f
                        (index-of-next-resumed-wild-match-attempt
                         resumable-node?)))
                      (final-match-index
                       (index-of-final-resumed-wild-match-attempt
                        resumable-node?)))
                  (if (=f this-match-index final-match-index)
                      (regexp-pop
                       resumable-wild-character-match-nodes?)
                      (setf (index-of-next-resumed-wild-match-attempt
                             resumable-node?)
                            this-match-index))
                  (setq current-index this-match-index)
                  (setq this-node?
                        (next-regular-expression-node resumable-node?))))
               (t;; Nothing to resume, so the match has failed.
                (setq match-failed-p t)
                (loop-finish)))))

          ;; The string and the compiled expression are both exhausted, so we have a
          ;; match.  Note that a compiled expression may be exhausted even if it has
          ;; more nodes remaining, as long as all those nodes accept zero
          ;; characters.
          ((>f current-index final-index-in-string-to-match)
           (loop-finish))

          ;; There are characters remaining in the string, but the compliled
          ;; expression is exhausted, so the match has failed.
          ((null this-node?)
           (setq match-failed-p t)
           (loop-finish)))
        finally
          (return (values (if match-failed-p nil current-index)
                          resumable-wild-character-match-nodes?))))

;; Why all the generic arithmetic above? (MHD 2/9/96)


#+development
(defun print-compiled-regular-expression (compiled-expression)
  (format t "~%")
  (print-compiled-regular-expression-1 compiled-expression)
  (format t "~%"))

#+development
(defun print-compiled-regular-expression-1 (compiled-expression)
  (loop for node = compiled-expression
                 then (next-regular-expression-node node)
        while node
        do
    (cond
      ((regular-expression-node-for-single-character-p node)
       (format t "~a" (single-character-in-regular-expression node)))
      ((regular-expression-node-for-single-wild-character-p node)
       (format t "?"))
      ((regular-expression-node-for-wild-characters-p node)
       (format t "*"))
      ((regular-expression-node-for-set-of-characters-p node)
       (let ((character-set
               (reverse
                (set-of-characters-in-regular-expression node))))
         (format t "{")
         (loop for char in character-set
               do
           (format t "~a" char))
         (format t "}")
         (when (wild-occurrences-of-characters-in-set-p node)
           (format t "*"))))
      ((regular-expression-node-for-subexpression-p node)
       (format t "(")
       (let ((subexpression? (compiled-regular-subexpression node)))
         (when subexpression?
           (print-compiled-regular-expression-1 subexpression?)))
       (format t ")"))
      (t (error "PRINT-COMPILED-REGULAR-EXPRESSION: unknown node type.")))))

#+development
(defun test-regular-expression-matcher (expression-string test-string)
  (let ((compiled-regular-expression
          (compile-regular-expression expression-string)))
    (prog1 (match-regular-expression
             compiled-regular-expression
             test-string)
           (reclaim-compiled-regular-expression compiled-regular-expression))))


#+development
(defparameter validation-suite-for-match-regular-expression
  '(                            ;expression  string
    ((test-regular-expression-matcher "a" "greetings") nil)
    ((test-regular-expression-matcher "a" "") nil)
    ((test-regular-expression-matcher "a" "x") nil)
    ((test-regular-expression-matcher "a" "a") t)
    ((test-regular-expression-matcher "*" "greetings") t)
    ((test-regular-expression-matcher "*" "") t)
    ((test-regular-expression-matcher "*" "x") t)
    ((test-regular-expression-matcher "*" "a") t)
    ((test-regular-expression-matcher "?" "greetings") nil)
    ((test-regular-expression-matcher "?" "") nil)
    ((test-regular-expression-matcher "?" "x") t)
    ((test-regular-expression-matcher "?" "a") t)
    ((test-regular-expression-matcher "greetings{x}*" "greetings") t)
    ((test-regular-expression-matcher "greeting{x}*s" "greetings") t)
    ((test-regular-expression-matcher "{cause}**r.kb" "cause-error.kb") t)
    ((test-regular-expression-matcher "{cause}*r.kb" "cause-error.kb") nil)
    ((test-regular-expression-matcher "*.kb" ".") nil)
    ((test-regular-expression-matcher "*.kb" "..") nil)
    ((test-regular-expression-matcher "*.kb" "...") nil)
    ((test-regular-expression-matcher "{aeiou}*.kb" ".") nil)
    ((test-regular-expression-matcher "{aeiou}*.kb" "..") nil)
    ((test-regular-expression-matcher "{aeiou}*.kb" "...") nil)
    ((test-regular-expression-matcher "{aeiou}a*.kb" ".") nil)
    ((test-regular-expression-matcher "{aeiou}a*.kb" "..") nil)
    ((test-regular-expression-matcher "{aeiou}a*.kb" "...") nil)
    ((test-regular-expression-matcher "ca?se*.kb" "cause-internal-error.kb") t)
    ((test-regular-expression-matcher "?*.kb" "cause-internal-error.kb") t)
    ((test-regular-expression-matcher "greetings" "greetings") t)
    ((test-regular-expression-matcher "greeting"  "greetings") nil)
    ((test-regular-expression-matcher "greetings" "greeting") nil)
    ((test-regular-expression-matcher "g*r*e*e*t*i*n*g*s*" "greetings") t)
    ((test-regular-expression-matcher "g*r*e*e*t*i*n*g*s" "greetings") t)
    ((test-regular-expression-matcher "g*s" "greetings") t)
    ((test-regular-expression-matcher "g*r*e*e*t*i*n*g" "greetings") nil)
    ((test-regular-expression-matcher "greetings*" "greetings") t)
    ((test-regular-expression-matcher "greetings*{xyz}*{abc}*{fgh}*" "greetings") t)
    ((test-regular-expression-matcher "greetings{xyz}*{abc}*{fgh}*" "greetings") t)
    ((test-regular-expression-matcher "greetings*{xyz}*{abc}*{fgh}" "greetings") nil)
    ((test-regular-expression-matcher "greet*" "greetings") t)
    ((test-regular-expression-matcher "*tings" "greetings") t)
    ((test-regular-expression-matcher "g*e*t*" "greetings") t)
    ((test-regular-expression-matcher "g*e*t*?" "greetings") t)
    ((test-regular-expression-matcher "greeting?" "greetings") t)
    ((test-regular-expression-matcher "gre?tings" "greetings") t)
    ((test-regular-expression-matcher "?reetings" "greetings") t)
    ((test-regular-expression-matcher "greeting{pqrs}" "greetings") t)
    ((test-regular-expression-matcher "gre{defg}tings" "greetings") t)
    ((test-regular-expression-matcher "{fghi}reetings" "greetings") t)
    ((test-regular-expression-matcher "greeting{pqrs}*" "greetings") t)
    ((test-regular-expression-matcher "gre{defg}*tings" "greetings") t)
    ((test-regular-expression-matcher "gr{defg}{defg}*tings" "greetings") t)
    ((test-regular-expression-matcher "gr{defg}*{defg}tings" "greetings") t)
    ((test-regular-expression-matcher "{greet}*ings" "greetings") t)
    ((test-regular-expression-matcher "gr{def}{def}tings" "greetings") t)
    ((test-regular-expression-matcher "gr{def}{def}{def}tings" "greetings") nil)
    ((test-regular-expression-matcher "gr{def}{def}*{def}tings" "greetings") t)
    ((test-regular-expression-matcher "gr{def}*{def}{def}*tings" "greetings") t)
    ((test-regular-expression-matcher "gr{def}*{def}*{def}*tings" "greetings") t)
    ((test-regular-expression-matcher "greetin{gs}*" "greetings") t)
    ((test-regular-expression-matcher "greetin{gs}*{gs}*{gs}*" "greetings") t)
    ((test-regular-expression-matcher "greetin{g}*" "greetings") nil)
    ((test-regular-expression-matcher "greetin{g}*s" "greetings") t)
    ((test-regular-expression-matcher "{fghi}reetings" "greetings") t)
    ((test-regular-expression-matcher "{xyz}*{fghi}{xyz}*reetings" "greetings") t)
    ((test-regular-expression-matcher "{{}greetings}" "{greetings}") t)
    ((test-regular-expression-matcher "{!}}greetings!{" "}greetings{") t)
    ((test-regular-expression-matcher "!greetings" "greetings") t)
    ((test-regular-expression-matcher "g!reetings" "greetings") t)
    ((test-regular-expression-matcher "greeting!s" "greetings") t)
    ((test-regular-expression-matcher "!g!r!e!e!t!i!n!g!s" "greetings") t)
    ((test-regular-expression-matcher "g!*r!*e!*e!*t!*i!*n!*g!*s!*" "g*r*e*e*t*i*n*g*s*") t)
    ((test-regular-expression-matcher "g!*r!*e!*e!*t!*i!*n!*g!*s!*" "g*r*e*e*t*i*n*g*s") nil)
    ((test-regular-expression-matcher "greetings!{my friends!}" "greetings{my friends}") t)
    ((test-regular-expression-matcher "greetings!{my friends}" "greetings{my friends}") t)
    ((test-regular-expression-matcher "greetings{my friends}" "greetings{my friends}") nil)
    ((test-regular-expression-matcher "greetings{my friends}" "greetingsy") t)
    ((test-regular-expression-matcher "greetings!?" "greetingsz") nil)
    ((test-regular-expression-matcher "greetings!?" "greetings?") t)
    ((test-regular-expression-matcher "greetings?" "greetings?") t)
    ((test-regular-expression-matcher "greetings?" "greetingsz") t)
    ((test-regular-expression-matcher "greetings!{my friends!}!*" "greetings{my friends}*") t)
    ((test-regular-expression-matcher "greetings!{my friends!}!*" "greetings{my friends}x") nil)
    ((test-regular-expression-matcher "greetings!{my friends!}*" "greetings{my friends}*") t)
    ((test-regular-expression-matcher "greetings!{my friends!}*" "greetings{my friends}x") t)
    ((test-regular-expression-matcher "greetings{my friends}!*" "greetingsy*") t)
    ((test-regular-expression-matcher "greetings{my friends}!*" "greetingsyy") nil)
    ((test-regular-expression-matcher "xxy(" "xxy(") t)     ;will be nil with subexpressions!
    ((test-regular-expression-matcher "xxy(x" "xxy(") nil)
    ((test-regular-expression-matcher "xxy(x" "xxyx") nil)  ;will be t with subexpressions!
    ((test-regular-expression-matcher "xxy()" "xxy()") t)   ;will be nil with subexpressions!
    ((test-regular-expression-matcher "xxy(a)" "xxy(a)") t) ;will be nil with subexpressions!
    ((test-regular-expression-matcher "xxy(a)" "xxya") nil) ;will be t with subexpressions!
    ))

#+development
(defun validate-match-regular-expression (&optional verbose-p)
  (validate-gensym-lisp-facility
    validation-suite-for-match-regular-expression
    verbose-p))

#+development
(defun examine-regular-expression-memory-use ()
  (with-memory-checking
    (validate-match-regular-expression)))




;;; Directory access

(def-gensym-c-function c-g2_stream_initdir
                       (:fixnum-int "g2ext_str_initdir")
  ())


(def-gensym-c-function c-g2_stream_opendir
                       (:fixnum-int "g2ext_str_opendir")
  ((:string dirspec)
   (:string filespec)))


(def-gensym-c-function c-g2_stream_closedir
                       (:fixnum-int "g2ext_str_closedir")
  ())


(def-gensym-c-function c-g2_stream_readdir
                       (:fixnum-int "g2ext_str_readdir")
  ((:string buffer)
   (:fixnum-int include-version-p)
   (:fixnum-int include-unreadable-p)))


(def-gensym-c-function c-g2_stream_read_subdirs
                       (:fixnum-int "g2ext_str_read_subdirs")
  ((:string buffer)
   (:fixnum-int include-version-p)
   (:fixnum-int include-unreadable-p)))


(defun g2-stream-read-subdirs (text-string-buffer include-version-flag include-unreadable-flag)
  (let* ((buffer-length (lengthw text-string-buffer))
         (temporary-simple-gensym-string
           ;; considering having a global for this! (MHD 2/14/96)
           (obtain-simple-gensym-string buffer-length)))
    (prog1 (c-g2_stream_read_subdirs        ; returns error status
             temporary-simple-gensym-string include-version-flag include-unreadable-flag)
      (copy-null-terminated-text-string
        temporary-simple-gensym-string text-string-buffer)
      (reclaim-simple-gensym-string temporary-simple-gensym-string))))

(defun g2-stream-readdir (text-string-buffer include-version-flag include-unreadable-flag)
  (let* ((buffer-length (lengthw text-string-buffer))
         (temporary-simple-gensym-string
           ;; considering having a global for this! (MHD 2/14/96)
           (obtain-simple-gensym-string buffer-length)))
    (prog1 (c-g2_stream_readdir        ; returns error status
             temporary-simple-gensym-string include-version-flag include-unreadable-flag)
      (copy-null-terminated-text-string
        temporary-simple-gensym-string text-string-buffer)
      (reclaim-simple-gensym-string temporary-simple-gensym-string))))

;; Make sure that only copying the part of the buffer preceeding #.%Null is OK!

;; Now that the buffer is a wide string, we must do an extra copy of the buffer
;; that's a gensym (simple Lisp) string into the wide string.  See if that can
;; be avoided, or made as efficient as possible! (MHD 2/14/96)


;; g2-stream-directory always returns a list of text-strings composed of
;; path-conses, even when run using lisp-streams.

(defmacro g2-stream-filtered-directory-using-lstreams
          (dirspec filespec version? file-system subdirectories-only-p)
  `(g2-stream-filtered-directory-using-lstreams-1
     ,dirspec ,filespec ,version? ,file-system ,subdirectories-only-p))

;; Versions not appropriate for truenames include things like ";0" and ".NEWEST"
;; (which denote the newest version) and ";-23" (denoting a previous version
;; relative to the newest version).

(defun version-can-occur-in-truename-p (version?)
  (not
    (and version?
         (let ((length-of-version-string (lengthw version?)))
           (and (>=f length-of-version-string 1)
                (or (and (=f length-of-version-string 2)
                           (char=w (charw version? 1) #.%\0))
                    (loop for index from 1 below length-of-version-string
                          thereis
                            (not (digit-char-pw (charw version? index))))))))))

#+development
(defun g2-stream-maybe-intercepted-directory
    (dirspec filespec version? file-system subdirectories-only-p include-unreadable-files-p)
  (cond
    (file-system-for-interception?
     (let* ((transformed-dirspec
              (transform-filestring-from-pseudo-file-system dirspec))
            (transformed-filespec
              (transform-filestring-from-pseudo-file-system filespec))
            (transformed-version?
              (and version?
                   (transform-filestring-from-pseudo-file-system version?)))
            (directory-list
              (g2-stream-filtered-directory-using-cstreams-1
                transformed-dirspec
                transformed-filespec
                transformed-version?
                file-system-for-interception?
                subdirectories-only-p
                include-unreadable-files-p)))
       (loop for filename in directory-list
             collect
             (transform-filestring-to-pseudo-file-system filename)
               using path-cons
             do (reclaim-text-string filename)
             finally
               (reclaim-path-list directory-list))))
    (t (g2-stream-filtered-directory-using-cstreams-1
         dirspec
         filespec
         version?
         file-system
         subdirectories-only-p
         include-unreadable-files-p))))

(defmacro g2-stream-filtered-directory-using-cstreams
          (dirspec filespec version? file-system subdirectories-only-p include-unreadable-files-p)
  (if (eval-feature :development)
      `(g2-stream-maybe-intercepted-directory
         ,dirspec ,filespec ,version? ,file-system
         ,subdirectories-only-p ,include-unreadable-files-p)
      `(g2-stream-filtered-directory-using-cstreams-1
         ,dirspec ,filespec ,version? ,file-system
         ,subdirectories-only-p ,include-unreadable-files-p)))

;; jh, 8/19/94.  Modified g2-stream-filtered-directory-using-cstreams to
;; transform pseudo-file-systems.  See three-semi comment under "Pseudo File
;; Systems" above for further details.

;;; The compiled-unix-version-match-spec? argument to the substitution macro
;;; `match-regular-expression-for-g2-stream-directory' allows us to filter out
;;; previous versions of UNIX files when appropriate, without a complete parse
;;; of the filestring (this would cross abstraction levels between g2-streams
;;; and gensym-pathnames).  Unlike VMS, the convention for denoting a previous
;;; version (a post-pended tilde) is not present in the operating system per se,
;;; so we have to parse for it.  On the other hand, we do some partial parsing
;;; of VMS versions too, as a version of ";0" cannot be present in a truename
;;; but may be specified in a match pattern, and so must be converted.  This
;;; happens in the body of g2-stream-filtered-directory-using-cstreams-1.

(defvar match-regular-expression-for-g2-stream-directory-hook nil)

(defun match-regular-expression-for-g2-stream-directory
    (compiled-matching-name-spec
      g2-stream-directory-buffer
      compiled-unix-version-match-spec?)
  (and (or (match-regular-expression
             compiled-matching-name-spec
             g2-stream-directory-buffer)
           (and match-regular-expression-for-g2-stream-directory-hook
                (funcall match-regular-expression-for-g2-stream-directory-hook
                         (copy-null-terminated-text-string g2-stream-directory-buffer))))
       (if compiled-unix-version-match-spec?
           (not (match-regular-expression
                  compiled-unix-version-match-spec?
                  g2-stream-directory-buffer))
           t)))

(defun-allowing-unwind g2-stream-filtered-directory-using-cstreams-1
    (dirspec filespec version? file-system subdirectories-only-p include-unreadable-files-p)
  (let ((wild-version-p
          (and version?
               (wild-regular-expression-string-p version?)))
        (version-or-empty-string
          (or version? #w"")))
    (if (or (wild-regular-expression-string-p filespec) wild-version-p)
        (block g2-stream-filtered-directory
          (when (or (>f (lengthw dirspec) g2-stream-directory-buffer-length)
                    (>f (lengthw filespec) g2-stream-directory-buffer-length))
            (record-status-of-most-recent-file-operation
              directory-spec-too-long-code)
            (return-from g2-stream-filtered-directory nil))

          (unless g2-stream-directory-initialized-p
            (cond
              ((=f (c-g2_stream_initdir) g2-stream-directory-success)
               (setq g2-stream-directory-initialized-p t))
              (t (record-status-of-most-recent-file-operation
                   failed-to-build-dir-structure-code)
                 (return-from g2-stream-filtered-directory nil))))

          (protected-let*
              ((complete-name-spec
                 (case file-system
                   (unix
                    (tformat-text-string "*~a"
                      version-or-empty-string))
                   (vms
                    (cond
                      (wild-version-p
                       (copy-constant-wide-string #w"*.*;*"))
                      (version?
                       (tformat-text-string "*.*~a"
                         version?))
                      (t (copy-constant-wide-string #w"*.*;0"))))
                   ;; jh, 1/19/95.  The "*" wildcard is the only way we know to
                   ;; grab both files and subdirectories on DOS-related
                   ;; filesystems.  See note associated with
                   ;; make-wild-name-and-type-pathname in PATHNAMES.
                   ((win32 dos generalized-dos)
                    (copy-constant-wide-string #w"*"))
                   (otherwise
                    (copy-constant-wide-string #w"*.*")))
                 (reclaim-text-string complete-name-spec))
               (invertible-version-p
                 (and version?
                      (version-can-occur-in-truename-p version?)))
               (include-version-flag
                 (if version? 1 0))
               (include-unreadable-flag
                 (if include-unreadable-files-p 1 0))
               (filespec-for-match-pattern
                 (case file-system
                   (unix
                    (tformat-text-string "~a~a"
                      filespec
                      version-or-empty-string))
                   (vms
                    (nstring-upcasew
                      (if (or (null version?)
                              wild-version-p
                              invertible-version-p)
                          (tformat-text-string "~a~a"
                            filespec
                            version-or-empty-string)
                          (tformat-text-string "~a;*"
                            filespec))))
                   ((win32 dos generalized-dos)
                    (copy-text-string filespec))
                   (otherwise
                    (copy-text-string filespec)))
                 (reclaim-text-string filespec-for-match-pattern))
               (compiled-matching-name-spec?
                 (compile-regular-expression
                   filespec-for-match-pattern)
                 (reclaim-compiled-regular-expression
                   compiled-matching-name-spec?))
               (filespec-for-unix-version-match?
                 (and (eq file-system 'unix)
                      (=f (lengthw version-or-empty-string) 0)
                      (tformat-text-string
                        "~a~a"
                        filespec
                        #w"~"))
                 (reclaim-text-string filespec-for-unix-version-match?))
               (compiled-unix-version-match-spec?
                 (and filespec-for-unix-version-match?
                      (compile-regular-expression
                        filespec-for-unix-version-match?))
                 (reclaim-compiled-regular-expression
                   compiled-unix-version-match-spec?)))

            (unless compiled-matching-name-spec?
              (record-status-of-most-recent-file-operation
                bad-regular-expression-code)
              (return-from g2-stream-filtered-directory nil))

            (unless (=f (c-g2_stream_opendir dirspec complete-name-spec)
                        g2-stream-directory-success)
              (record-status-of-most-recent-file-operation
                failed-to-open-dir-structure-code)
              (return-from g2-stream-filtered-directory nil))

            (loop with directory-list = nil
                  until (/=f (if subdirectories-only-p
                                 (g2-stream-read-subdirs
                                   g2-stream-directory-buffer
                                   include-version-flag
                                   include-unreadable-flag)
                                 (g2-stream-readdir
                                   g2-stream-directory-buffer
                                   include-version-flag
                                   include-unreadable-flag))
                             g2-stream-directory-success)
                  when (match-regular-expression-for-g2-stream-directory
                         compiled-matching-name-spec?
                         g2-stream-directory-buffer
                         compiled-unix-version-match-spec?)
                    do
                      (path-push
                        (copy-null-terminated-text-string g2-stream-directory-buffer)
                        directory-list)
                  finally
                    (most-recent-file-operation-succeeded)
                    (c-g2_stream_closedir)
                    (return directory-list))))
        (protected-let
            ((complete-directory-spec
               (tformat-text-string "~a~a~a"
                 dirspec
                 filespec
                 version-or-empty-string)
               (reclaim-text-string complete-directory-spec)))
          (if (and (g2-stream-probe-file-for-read complete-directory-spec)
                   (>f (lengthw filespec) 0))
              (path-list
                (tformat-text-string "~a~a"
                  filespec
                  version-or-empty-string))
              nil)))))


;; jh, 1/7/92.  Note that g2-stream-directory and g2-stream-subdirectories always
;; collect the newest files and ignore previous versions.  This behavior makes
;; things easier for the directory-accessing machinery in execute-file-command,
;; since G2 never has to specify versions other than :newest there.  Note,
;; however, that G2 users can get to the g2-stream directory functions through the
;; system procedures files-in-directory and subdirectories-in-directory, and they
;; might want the ability to specify versions to these procedures.  So we should
;; consider changing g2-stream-directory and g2-stream-subdirectories accordingly.
;; The main problem is that the g2-stream level has no notion of pathname
;; components, and so the regular-expression machinery here can't match a
;; versionless file of a given name with the newest file of the same name.  In
;; distribution, this is only a problem on VMS, since UNIX files with a postpended
;; tilde may still be specified.

;; jh, 1/10/92.  Rewote both g2-stream-filtered-directory-using-lstreams and
;; g2-stream-filtered-directory-using-cstreams to accept version strings and match
;; them appropriately with the underlying file system.  The remaining problem is
;; to let the filename parsers know about permitted wild characters in the version
;; spec (only integers and keywords like :newest were allowed heretofore).

;; jh, 1/10/92.  Filename parsers modified to accept metacharacters in the version
;; when accept-any-version-component-p is non-nil.  See FILE-PARSE for details.
;; This fixes the "remaining problem" in the previous comment.

;; jh, 1/22/92.  Changed g2-stream-filtered-directory-using-cstreams to always
;; include the version in a directory filename if the user provides a non-nil
;; version?  argument.  This involved asking the underlying C directory mechanism
;; to provide the version, then wildcarding the version in the regular-expression
;; used in Lisp to filter the directory mechanism's output.  The purpose of this
;; change is to ensure that the user gets the version number back whenever a
;; version was supplied, even if that version is non-invertible as far as the
;; matching filter is concerned.  (An example of a filename containing a
;; non-invertible version is the VMS filename "xyz.kb;-1", which denotes the
;; previous version of the file "xyz.kb".  True VMS filenames never contain a
;; version of "-1", so our matching machinery would fail without special
;; precautions.)

(def-g2-stream-operation-allowing-unwind g2-stream-directory
    (dirspec filespec version? file-system include-unreadable-files-p)
  (declare (record-status nil)) ;subfunction records status

  :c-streams
  (let ((dirspec-to-use dirspec)
        (need-to-reclaim-dirspec-p nil))
    (when (and (eq local-file-system 'unix)
               (>f (lengthw dirspec) 0)
               (char=w (charw dirspec 0) #.%\~))
      (let ((pathname-needing-home (gensym-pathname dirspec-to-use)))
        (supply-home-to-unix-pathname pathname-needing-home)
        (setq dirspec-to-use
              (gensym-namestring pathname-needing-home))
        (setq need-to-reclaim-dirspec-p t)
        (reclaim-gensym-pathname pathname-needing-home)))
    (prog1
        (g2-stream-filtered-directory-using-cstreams
          dirspec-to-use filespec version? file-system nil include-unreadable-files-p)
      (when need-to-reclaim-dirspec-p
        (reclaim-text-string dirspec-to-use)))))


;;; g2-stream-subdirectories

;;; Returns a path-list of text-strings naming the subdirectories of the given
;;; directory, as well as can be determined.  (This last proviso is due to the
;;; fact that on some file systems it is easy to create ".DIR" files that are not
;;; true directories.)

(def-g2-stream-operation-allowing-unwind g2-stream-subdirectories
    (dirspec filespec version? file-system include-unreadable-files-p)
  (declare (record-status nil)) ;subfunction records status

  :c-streams
  (let ((dirspec-to-use dirspec)
        (need-to-reclaim-dirspec-p nil))
    (when (and (eq local-file-system 'unix)
               (>f (lengthw dirspec) 0)
               (char=w (charw dirspec 0) #.%\~))
      (let ((pathname-needing-home (gensym-pathname dirspec-to-use)))
        (supply-home-to-unix-pathname pathname-needing-home)
        (setq dirspec-to-use (gensym-namestring pathname-needing-home))
        (setq need-to-reclaim-dirspec-p t)
        (reclaim-gensym-pathname pathname-needing-home)))
    (prog1
        (g2-stream-filtered-directory-using-cstreams
          dirspec-to-use filespec version? file-system t include-unreadable-files-p)
      (when need-to-reclaim-dirspec-p
        (reclaim-text-string dirspec-to-use)))))

;;; g2-stream-devices

;;; The constants `foreign-function-success' and `foreign-function-failure' give
;;; the canonical fixnum returned from a foreign function that has,
;;; respectively, succeeded or failed.  You must check the C implementation of
;;; the foreign function to be sure that it adheres to this convention.

(defconstant foreign-function-success 0)
(defconstant foreign-function-failure -1)

(def-gensym-c-function c-g2_stream_open_device_list
    (:fixnum-int "g2ext_str_open_device_list")
  ())
;SS_ERROR
(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter g2-stream-device-buffer-length 256)
)

(defvar g2-stream-device-buffer
        (obtain-simple-gensym-string #.g2-stream-device-buffer-length))

(def-gensym-c-function c-g2_stream_get_next_device
    (:fixnum-int "g2ext_str_get_next_device")
  ((:string buffer)))

;;; Tne function `g2-stream-devices' returns path-list of the names of the
;;; available devices on this machine.  Currently (jh, 10/3/96) this can only
;;; return a non-empty list on Window/NT.

(def-g2-stream-operation-allowing-unwind g2-stream-devices ()
  (declare (record-status t))
  :c-streams
  (let ((device-list nil)
        (open-status (c-g2_stream_open_device_list)))
    (cond
      ((=f open-status foreign-function-failure)
       (record-status-of-most-recent-file-operation
         failed-to-open-device-list-code))
      (t (loop for read-status
                   = (c-g2_stream_get_next_device g2-stream-device-buffer)
               while (=f read-status foreign-function-success)
               do
           (path-push
             (copy-null-terminated-text-string g2-stream-device-buffer)
             device-list)
           (most-recent-file-operation-succeeded))))
        device-list))



;;; g2-stream-directory-p

(def-gensym-c-function c-g2_stream_directory_p
                       (:fixnum-int "g2ext_str_directory_p")
  ((:string namestring)))

(defconstant g2-stream-directory-p-success 1)

(defun-simple pathname-is-root-directory-p (gensym-pathname)
  (with-pathname-components (gensym-pathname)
    (and (equal gensym-pathname-directory '(:absolute))
         (null gensym-pathname-name)
         (null gensym-pathname-type)
         (or (null gensym-pathname-version)
             (eq gensym-pathname-version :unspecific)))))

(def-g2-stream-operation g2-stream-directory-p (namestring)
  (declare (record-status nil)
           (var-is-file-namestring namestring))
  :c-streams
  (macrolet ((syntactic-root-directory-p (platform parser)
               `(and (eq ',platform local-file-system)
                     (let ((directory-pathname? (,parser namestring)))
                       (cond
                         (directory-pathname?
                          (prog1 (pathname-is-root-directory-p
                                   directory-pathname?)
                            (reclaim-gensym-pathname directory-pathname?)))
                         (t nil))))))
    (let* ((result
             (if (or (syntactic-root-directory-p vms   parse-vms-filename)
                     (syntactic-root-directory-p win32 parse-win32-filename)
                     (syntactic-root-directory-p dos   parse-dos-filename))
                 g2-stream-directory-p-success
                 (c-g2_stream_directory_p namestring))))
      (if (=f result g2-stream-directory-p-success)
          t
          nil))))

;; jh, 11/27/94.  Added special case to ensure that g2-stream-directory-p
;; returns true for the root directory "[000000]" on VMS file systems.
;; Apparently the implementation of stat() there does not accept this string.
;; Note that and equal test does not suffice; we have to parse the potential
;; directory string as a gensym-pathname in case it contains a host or device
;; component and nonetheless is the root directory for that host or device.



(def-gensym-c-function c-g2_create_directory
                       (:fixnum-int "g2ext_create_directory")
  ((:string namestring)
   (:fixnum-int create-parents-p)
   (:string mask)))




;;; g2-stream-get-default-directory

;;; Returns the default directory as a text-string, or nil if this cannot be
;;; determined.

(defmacro g2-stream-get-default-directory-using-lstreams ()
  (with-package-specific-symbols (fs |::| default-pathname)
    `(tformat-text-string "~a:~a"
       (file-system-host-as-text-string
         (pathname-host
           (default-pathname)))
       (directory-namestring
         (default-pathname)))))

(def-gensym-c-function c-g2_stream_get_default_dir
                       (:fixnum-int "g2ext_str_get_default_dir")
  ((:string buff)))

(defmacro body-of-g2-stream-get-default-directory ()
  `(let ((result-code
           (c-g2_stream_get_default_dir gensym-environment-variable-buffer)))
     (record-status-of-most-recent-file-operation)
     (let ((text-result?
             (interface-to-foreign-environment-access result-code)))
       (cond (text-result?
              (most-recent-file-operation-succeeded)
              ,(if (eval-feature :development)
                   `(if file-system-for-interception?
                        (prog1
                            (transform-filestring-to-pseudo-file-system
                              text-result?)
                          (reclaim-text-string text-result?))
                        text-result?)
                   `text-result?))
             (t (record-status-of-most-recent-file-operation)
                nil)))))

(def-g2-stream-operation g2-stream-get-default-directory ()
  (declare (record-status nil)) ;done in body-of-g2-stream-get-default-directory

  :c-streams
  (body-of-g2-stream-get-default-directory))



;;; g2-stream-change-default-directory

;;; Returns non-nil if able to change the default directory to that given by
;;; new-directory-string, or nil if unable to comply.

(def-gensym-c-function c-g2_stream_change_default_dir
                       (:fixnum-int "g2ext_str_change_default_dir")
  ((:string new-dir)))


(defmacro g2-stream-change-default-directory-using-lstreams (namestring)
  (with-package-specific-symbols (fs |::| set-default-pathname)
    `(set-default-pathname ,namestring)))

(def-g2-stream-operation g2-stream-change-default-directory (namestring)
  (declare (record-status t)
           (var-is-file-namestring namestring))

  :c-streams
  (let ((status
          (c-g2_stream_change_default_dir namestring)))
    (cond ((=f status g2-stream-foreign-file-op-failure)
           (record-status-of-most-recent-file-operation)
           nil)
          (t (most-recent-file-operation-succeeded)
             t))))


;;;; File Attributes

;;; g2-stream-file-length (g2-stream)

;;; Returns the length of the file connected to the stream in characters, or nil
;;; if it cannot be determined.  If the length of the file is greater than
;;; most-positive-fixnum, results are unpredictable.

(def-gensym-c-function c-g2_stream_file_length
                       (:fixnum-int "g2ext_str_file_length")
  ((:pointer g2-stream)))

(def-g2-stream-operation g2-stream-file-length (g2-stream)
  (declare (record-status t)
           (var-is-g2-stream-arg g2-stream))

  :c-streams
  (let ((file-length-or-error (c-g2_stream_file_length g2-stream)))
    (cond ((< file-length-or-error 0)
           (record-status-of-most-recent-file-operation)
           nil)
          (t (most-recent-file-operation-succeeded)
             file-length-or-error))))

(def-gensym-c-function c-g2_stream_file_non_empty
                       (:fixnum-int "g2ext_str_file_non_empty")
  ((:pointer g2-stream)))

(def-g2-stream-operation g2-stream-file-non-empty (g2-stream)
  (declare (record-status t)
           (var-is-g2-stream-arg g2-stream))

  :c-streams
  (let ((non-empty-or-error (c-g2_stream_file_non_empty g2-stream)))
    (cond ((<f non-empty-or-error 0)
           (record-status-of-most-recent-file-operation)
           nil)
          (t
           (most-recent-file-operation-succeeded)
           (=f non-empty-or-error 1)))))




;;; g2-stream-set-file-position (g2-stream new-position seek-mode)

;;; Sets the file position of the file connected to g2-stream to be new-position
;;; with seek-mode one of the constant-yielding macros
;;;   (g2-stream-seek-from-beginning)
;;;   (g2-stream-seek-from-current-position)
;;;   (g2-stream-seek-from-end)
;;; and new-position an integer.  Returns a non-nil value if successful, nil if
;;; unsuccessful.  If seek-mode is g2-stream-seek-from-end and new-position is
;;; positive, the file will be extended with intervening characters of undefined
;;; value.  If new-position is greater than most-positive-fixnum, results are
;;; unpredictable.  The reason we use constant-yielding macros rather than
;;; simple defconstants is because we don't need the constant symbols around
;;; in our run-time image (per PTO).

(eval-when (:compile-toplevel :load-toplevel :execute)
(defmacro-for-constant g2-stream-seek-from-beginning 0)
(defmacro-for-constant g2-stream-seek-from-current-position 1)
(defmacro-for-constant g2-stream-seek-from-end 2)
)

(def-gensym-c-function c-g2_stream_set_file_position
                       (:fixnum-int "g2ext_str_set_file_position")
  ((:pointer g2-stream)
   (:fixnum-int new-position)
   (:fixnum-int seek-mode)))


(def-g2-stream-operation g2-stream-set-file-position
                         (g2-stream new-position seek-mode)
  (declare (record-status t)
           (var-is-g2-stream-arg g2-stream)
           (ignore-for-lisp-streams seek-mode))

  :c-streams
  (let ((result
          (c-g2_stream_set_file_position g2-stream new-position seek-mode)))
    (cond ((zerop result)
           (most-recent-file-operation-succeeded)
           t)
          (t (record-status-of-most-recent-file-operation)
             nil))))




;;; g2-stream-get-file-position (g2-stream)

;;; Gets the file position of the file connected to g2-stream, or nil if this
;;; cannot be determined.  If the length of the file is greater than
;;; most-positive-fixnum, results are unpredictable.

(def-gensym-c-function c-g2_stream_get_file_position
                       (:fixnum-int "g2ext_str_get_file_position")
  ((:pointer g2-stream)))



(def-g2-stream-operation g2-stream-get-file-position (g2-stream)
  (declare (record-status t)
           (var-is-g2-stream-arg g2-stream))

  :c-streams
  (let ((file-position (c-g2_stream_get_file_position g2-stream)))
    (cond ((< file-position 0)
           (record-status-of-most-recent-file-operation)
           nil)
          (t (most-recent-file-operation-succeeded)
             file-position))))


;;; g2-stream-get-version <namestring>

;;; If the file system supports versions, g2-stream-get-version returns an integer
;;; representing the version of the file named by string.  Otherwise, it returns
;;; nil.  This function helps gensym-probe-file (in the PATHNAMES module) do
;;; truename conversion.

(def-gensym-c-function c-g2_stream_get_version
                       (:fixnum-int "g2ext_str_get_version")
  ((:string namestring)))


(def-g2-stream-operation g2-stream-get-version (namestring)
  (declare (record-status t)
           (var-is-file-namestring namestring))

  :c-streams
  (let ((version?
          (c-g2_stream_get_version namestring)))
    (cond ((=f version? g2-stream-foreign-file-op-failure)
           (record-status-of-most-recent-file-operation)
           nil)
          (t (most-recent-file-operation-succeeded)
             version?))))




;;; g2-stream-get-device <namestring>

;;; If the file system supports device designations, g2-stream-get-device returns
;;; a text-string representing the device of the file named by string.  Supples a
;;; device even if string does not.  This function is currently (6/6/91) used only
;;; to spawn foreign function servers in VMS, where we need the full pathname of
;;; the foreign server to run it.

(def-gensym-c-function c-g2_stream_get_device
                       (:fixnum-int "g2ext_str_get_device")
  ((:string namestring)
   (:string buffer)))


(def-g2-stream-operation g2-stream-get-device (namestring)
  (declare (record-status t)
           (var-is-file-namestring namestring))

  :c-streams
  (let ((status
          (c-g2_stream_get_device
            namestring
            gensym-environment-variable-buffer)))
    (let ((text-result?
            (interface-to-foreign-environment-access status)))
      (cond (text-result?
             (most-recent-file-operation-succeeded)
             text-result?)
            (t (record-status-of-most-recent-file-operation)
               nil)))))



;;; g2-stream-available-disk-space-in-device

;;; Returns the number of blocks (system-dependent) free on the device of the
;;; given filestring, or nil if that cannot be determined.

(def-gensym-c-function c-g2_stream_dir_disk_space
                       (:fixnum-int "g2ext_str_avail_disk_space")
  ((:string dirstring)))

;; Probably due to limitations of the VMS filesystem, get-vms-available-disk-space
;; will only work for a directory that exists.  Some might expect it to find the
;; device for a syntactically well-formed but non-existant directory string, but
;; this seems beyond the capabilities of VMS.  jh, 3/14/91.

;; jh, 11/3/91.  Changed g2_stream_dir_disk_space to return a meaningful error
;; code based on the way we obtain this number (by spawning a subprocess).  Using
;; errno would probably be misleading.

(def-g2-stream-operation g2-stream-available-disk-space-in-device
                         (filestring)
  (declare (record-status t)
           (ignore-for-lisp-streams filestring)
           (var-is-file-namestring filestring))

  :c-streams
  (let ((disk-space-or-error-code
          (c-g2_stream_dir_disk_space filestring)))
    (cond ((>=f disk-space-or-error-code 0)
           (most-recent-file-operation-succeeded)
           disk-space-or-error-code)
          (t (record-status-of-most-recent-file-operation
               disk-space-or-error-code)
             nil))))


;;; g2-stream-file-xxx-date functions

;; G2 uses the unix model of file timestamping.  This comprises three timestamps:
;;   modification:  last time the file was opened or written
;;   access:        last time the file was opened, read, or written
;;   status change: last time the file was opened, written, renamed, or had its
;;                  permissions changed.

;; Note that we have to hope that we never pass non-simple filestrings out to C.
;; I think this should be the case for filestrings of reasonable length, but needs
;; checking with the owner of text-strings.  (Jim?) jh, 3/15/91.

(defconstant file-timestamp-modification-mode 0)
(defconstant file-timestamp-access-mode 1)
(defconstant file-timestamp-status-change-mode 2)

(def-gensym-c-function c-g2_stream_file_timestamp
                       (:double-float "g2ext_str_file_timestamp")
  ((:string     filename)
   (:fixnum-int mode)))


(defconstant number-of-seconds-between-lisp-and-unix-antiquity
             2208988800d0)

(defmacro def-g2-stream-attribute-operation
          (name &key c-streams-attribute)

  `(def-g2-stream-operation ,name (filestring)
     (declare (record-status t)
              (var-is-file-namestring filestring))

     :c-streams
     (with-temporary-gensym-float-creation g2-stream-attribute-operation
       (let ((timestamp-or-status
               (c-g2_stream_file_timestamp filestring ,c-streams-attribute)))
         (cond ((=e timestamp-or-status -1.0)
                (record-status-of-most-recent-file-operation)
                nil)
               (t (most-recent-file-operation-succeeded)
                  (allocate-managed-float timestamp-or-status)))))))


;;; g2-stream-file-modification-date

;;; Returns a managed float indicating the last time the file was opened or
;;; written, in seconds since January 1, 1970 GMT.

(def-g2-stream-attribute-operation g2-stream-file-modification-date
  :c-streams-attribute file-timestamp-modification-mode)



;;; g2-stream-file-access-date

;;; Returns a managed float indicating the last time the file was opened, read, or
;;; written, in seconds since January 1, 1970 GMT.

(def-g2-stream-attribute-operation g2-stream-file-access-date
  :c-streams-attribute file-timestamp-access-mode)




;;; g2-stream-file-status-change-date

;;; Returns a managed float indicating the last time the file was opened, written,
;;; renamed, or had its permissions changed, in seconds since January 1, 1970 GMT.

(def-g2-stream-attribute-operation g2-stream-file-status-change-date
  :c-streams-attribute file-timestamp-status-change-mode)




(defconstant file-access-check-read-mode 0)
(defconstant file-access-check-write-mode 1)
(defconstant file-access-check-execute-mode 2)

(def-gensym-c-function c-g2_stream_file_access_check
                       (:fixnum-int "g2ext_str_file_access_check")
  ((:string     filename)
   (:fixnum-int mode)))

(defmacro def-g2-stream-access-operation
    (name &key c-streams-attribute)

  `(def-g2-stream-operation ,name (filestring)
     (declare (record-status t)
              (var-is-file-namestring filestring))

     :c-streams
     (let ((status
             (c-g2_stream_file_access_check filestring ,c-streams-attribute)))
       (cond ((=f status -1)
              (record-status-of-most-recent-file-operation)
              nil)
             (t (most-recent-file-operation-succeeded)
                (not (=f status 0)))))))

(def-g2-stream-access-operation g2-stream-file-is-readable-p
  :c-streams-attribute file-access-check-read-mode)

(def-g2-stream-access-operation g2-stream-file-is-writable-p
  :c-streams-attribute file-access-check-write-mode)

(def-g2-stream-access-operation g2-stream-file-is-executable-p
  :c-streams-attribute file-access-check-execute-mode)


;;; `verify-executable' - the executable-p test doesn't seem to work on Windows.
;;; Probing that the file exists and is readable may not be a sufficient
;;; substitute.  Could use improvement.  -jv, 2/9/07

(defun verify-executable (filename)
  (and (g2-stream-probe-file-for-read filename)
       (not (g2-stream-directory-p filename))
       (or (neq g2-operating-system 'unix)
           (g2-stream-file-is-executable-p filename))))


(defvar all-write-locks nil)

(def-gensym-c-function c-g2_stream_get_write_lock
                       (:fixnum-int "g2ext_str_get_write_lock")
  ((:string namestring)
   (:string g2-identification)
   (:string buffer)))

(def-gensym-c-function c-g2_stream_release_write_lock
                       (:fixnum-int "g2ext_str_release_write_lock")
  ((:string namestring)
   (:string g2-identification)))

(def-g2-stream-operation g2-stream-get-write-lock
    (namestring g2-identification)
  (declare (record-status t)
           (var-is-file-namestring namestring))

  :c-streams
  (let ((status
          (c-g2_stream_get_write_lock
            namestring
            g2-identification
            gensym-environment-variable-buffer)))
    (let ((text-result?
            (when (=f 0 status)
              (copy-null-terminated-string-as-text-string
                gensym-environment-variable-buffer))))
      (most-recent-file-operation-succeeded)
      text-result?)))

(def-g2-stream-operation g2-stream-release-write-lock
    (namestring g2-identification)
  (declare (record-status t)
           (var-is-file-namestring namestring))

  :c-streams
  (let ((result (c-g2_stream_release_write_lock namestring g2-identification)))
    (cond ((zerop result)
           (most-recent-file-operation-succeeded)
           t)
          (t
           (record-status-of-most-recent-file-operation)
           nil))))

(defun-simple obtain-write-lock-for-kb (filename)
  (let ((error-string?
          (g2-stream-get-write-lock
            filename
            (g2-identification-for-write-locks))))
    (when error-string?
      (prog1 (tformat-text-string "Failed to obtain write lock for ~A: ~A"
                                  filename error-string?)
        (reclaim-text-string error-string?)))))

(defun-void release-write-lock-for-kb (filename)
  (let ((tail (member filename all-write-locks :test #'equal)))
    (when tail
      (let ((recorded-string (car tail)))
        (setq all-write-locks
              (delete-gensym-element recorded-string all-write-locks))
        (g2-stream-release-write-lock
          recorded-string
          (g2-identification-for-write-locks))
        (reclaim-gensym-string recorded-string)))))

(defun-simple try-to-obtain-write-lock-for-kb (filename)
  (let* ((namestring (namestring-as-gensym-string filename))
         (error-string? (obtain-write-lock-for-kb namestring)))
    (unless error-string?
      (gensym-push namestring all-write-locks))
    error-string?))

(defun-void release-all-kb-write-locks ()
  (loop while all-write-locks
        for filename = (first all-write-locks)
        do (release-write-lock-for-kb filename))
  nil)





;;; g2-stream-logical-name-p

;;; G2-stream-logical-name-p returns t if its argument can be translated to a
;;; logical name, nil otherwise.  Currently (jh, 11/4/91) we only need this
;;; function in gensym-merge-pathnames, which should only merge directory contents
;;; if the device is not a logical name.

(def-gensym-c-function c-g2_stream_logical_name_p
                       (:fixnum-int "g2ext_str_logical_name_p")
  ((:string device-component)))

(def-g2-stream-operation g2-stream-logical-name-p (device-component)
  (declare (record-status nil)
           (ignore-for-lisp-streams device-component)
           (var-is-file-namestring device-component))

  :c-streams
  (and (text-string-p device-component)
       (if (=f (c-g2_stream_logical_name_p device-component) 1)
           t
           nil)))




;;; g2-stream-maximum-file-name-length

;;; If there is a limit on the number of characters in a filename for files
;;; residing in the given directory, g2-stream-maximum-file-name-length returns
;;; that limit as a fixnum.  If there is no limit, or if it is unable to
;;; determine a limit, it returns nil.  Currently, this g2-stream operation does
;;; not set any error codes, although eventually it should.  Also note that on
;;; UNIX systems, the limit applies to the sum of the length of the filename
;;; component, the file type component, and the dot that separates them.  This
;;; is because UNIX itself has no intrinsic notion of file type -- this is an
;;; overlay imposed by facilities that want to treat UNIX pathnames like VMS or
;;; Lispm ones.

(def-gensym-c-function c-g2_stream_max_filename
                       (:fixnum-int "g2ext_str_max_filename")
  ((:string directory-namestring)))

(def-g2-stream-operation g2-stream-maximum-file-name-length
                         (directory-namestring)
  (declare (record-status nil)
           (ignore-for-lisp-streams directory-namestring)
           (var-is-file-namestring directory-namestring))



  :c-streams
  (let ((limit-or-flag (c-g2_stream_max_filename directory-namestring)))
    (if (>f limit-or-flag 0)
        limit-or-flag
        nil))
  )

;;;; Search paths for loading files at launch time

;; For security reasons, we check a disabling file before obeying a command-line
;; or environment-variable directive to load an OK or init file.  This is more
;; complicated than with-file-search-path can currently handle.  jh, 1/24/92.

(defun-allowing-unwind get-pathname-for-launch-time-load-from-command-line
                       (command-line-keyword
                         type-of-file-to-load
                         list-of-permitted-pathnames-or-t)
  (let ((namestring-from-command-line?
          (get-command-line-keyword-argument command-line-keyword)))
    (values
      (cond
        (namestring-from-command-line?
         (if (eq list-of-permitted-pathnames-or-t t)
             (or (gensym-probe-file namestring-from-command-line?)
                 (protected-let
                   ((pathname-from-command-line
                      (gensym-pathname namestring-from-command-line?)
                      (reclaim-gensym-pathname pathname-from-command-line)))
                   (if (gensym-pathname-type pathname-from-command-line)
                       nil
                       (protected-let
                         ((pathname-from-command-line-with-default-version
                            (gensym-make-pathname
                              :type type-of-file-to-load
                              :defaults pathname-from-command-line)
                            (reclaim-gensym-pathname
                              pathname-from-command-line-with-default-version)))
                         (gensym-probe-file
                           pathname-from-command-line-with-default-version)))))
             (protected-let
               ((pathname-from-command-line
                  (gensym-merge-pathnames
                    namestring-from-command-line?
                    process-specific-system-pathname)
                  (reclaim-gensym-pathname pathname-from-command-line)))
               (loop for permitted-pathname
                         in list-of-permitted-pathnames-or-t
                     thereis
                       (and (gensym-pathnames-equal-enough-p
                              pathname-from-command-line
                            permitted-pathname)
                            (gensym-probe-file pathname-from-command-line))))))
        (t nil))
      (if namestring-from-command-line?
          (copy-text-string namestring-from-command-line?)
          nil))))


(defun-allowing-unwind get-pathname-for-launch-time-load-from-environment-vars
                       (environment-var-name
                         type-of-file-to-load
                         list-of-permitted-pathnames-or-t)
  (let ((namestring-from-environment-vars?
          (get-gensym-environment-variable environment-var-name)))
    (values
      (cond
        (namestring-from-environment-vars?
         (if (eq list-of-permitted-pathnames-or-t t)
             (or (gensym-probe-file namestring-from-environment-vars?)
                 (protected-let
                   ((pathname-from-environment-vars
                      (gensym-pathname namestring-from-environment-vars?)
                      (reclaim-gensym-pathname
                        pathname-from-environment-vars)))
                   (if (gensym-pathname-type pathname-from-environment-vars)
                       nil
                       (protected-let
                         ((pathname-from-environment-vars-with-default-version
                            (gensym-make-pathname
                              :type type-of-file-to-load
                              :defaults pathname-from-environment-vars)
                            (reclaim-gensym-pathname
                              pathname-from-environment-vars-with-default-version)))
                         (gensym-probe-file
                           pathname-from-environment-vars-with-default-version)))))
             (protected-let
               ((pathname-from-environment-vars
                  (gensym-merge-pathnames
                    namestring-from-environment-vars?
                    process-specific-system-pathname)
                  (reclaim-gensym-pathname pathname-from-environment-vars)))
               (loop for permitted-pathname
                         in list-of-permitted-pathnames-or-t
                     thereis
                       (and (gensym-pathnames-equal-enough-p
                              pathname-from-environment-vars
                              permitted-pathname)
                            (gensym-probe-file pathname-from-environment-vars))))))
        (t nil))
      namestring-from-environment-vars?)))

(defun provide-pathname-for-launch-time-load-asking-os
       (command-line-keyword
        environment-variable-name
        type-of-file-to-load
        default-pathname-for-file-to-load?
        list-of-permitted-pathnames
        provide-desired-namestring-p)
  (let ((pathname-to-provide? nil)
        (explicitly-specified-namestring-1? nil)
        (explicitly-specified-namestring-2? nil)
        (using-default-pathname? nil))
    (multiple-value-setq
        (pathname-to-provide? explicitly-specified-namestring-1?)
      (get-pathname-for-launch-time-load-from-command-line
        command-line-keyword
        type-of-file-to-load
        list-of-permitted-pathnames))
    (unless pathname-to-provide?
      (multiple-value-setq
          (pathname-to-provide? explicitly-specified-namestring-2?)
        (get-pathname-for-launch-time-load-from-environment-vars
          environment-variable-name
          type-of-file-to-load
          list-of-permitted-pathnames))
      (unless pathname-to-provide?
        (setq pathname-to-provide?
              (and default-pathname-for-file-to-load?
                   (gensym-probe-file default-pathname-for-file-to-load?)))
        (when pathname-to-provide?
          (setq using-default-pathname? t))))

    (when pathname-to-provide?
      (unless (sufficient-pathname-for-launch-time-load-p pathname-to-provide?)
        (when default-pathname-for-file-to-load?
          (let ((original-inadequate-pathame-structure pathname-to-provide?))
            (setq pathname-to-provide?
                  (gensym-merge-pathnames pathname-to-provide?
                                          default-pathname-for-file-to-load?))
            (reclaim-gensym-pathname original-inadequate-pathame-structure)))))

    (let ((explicitly-specified-namestring?
            (or explicitly-specified-namestring-2?
                explicitly-specified-namestring-1?))
          (source-of-namestring-specification
            (cond (explicitly-specified-namestring-2? :environment-variable)
                  (using-default-pathname? :directory)
                  (t :command-line))))
      (when (and explicitly-specified-namestring-2?
                 (text-string-p explicitly-specified-namestring-1?))
        (reclaim-text-string explicitly-specified-namestring-1?))
      (cond
        (provide-desired-namestring-p
         (values pathname-to-provide?
                 explicitly-specified-namestring?
                 source-of-namestring-specification))
        (t (when (text-string-p explicitly-specified-namestring?)
             (reclaim-text-string explicitly-specified-namestring?))
           (values pathname-to-provide? nil nil))))))

;; ajs, 5/2/97. Added :directory to distinguish the home directory source from
;; the command line source.


;; return nil if pathname is a directory???  -jv, 11/11/02

(defun-allowing-unwind provide-pathname-for-launch-time-load
                       (default-pathname-for-file-to-load?
                         disabling-file-pathname
                         command-line-keyword
                         environment-variable-name
                         type-of-file-to-load
                         provide-desired-namestring-p)
  (protected-let
      ((namestring-of-disabling-file
         (gensym-namestring disabling-file-pathname)
         (reclaim-text-string namestring-of-disabling-file)))
    (g2-stream-with-open-stream-raw
        (stream-to-disabling-file?
	 namestring-of-disabling-file)
      (cond
        (stream-to-disabling-file?
         (protected-let
             ((list-of-permitted-pathnames
                (loop for line-in-disabling-file?
                          = (g2-stream-read-line stream-to-disabling-file?)
                      then (progn
                             (reclaim-text-string line-in-disabling-file?)
                             (g2-stream-read-line stream-to-disabling-file?))
                      for line-length = nil
                      for start-index? = nil
                      for end-index? = nil
                      for permitted-pathname? = nil
                      while line-in-disabling-file?
                      do
                  (setq line-length (lengthw line-in-disabling-file?))
                  (loop for index from 0 below line-length
                        for this-char = (charw line-in-disabling-file? index)
                        do
                    (if start-index?
                        (when (wide-character-member
                                this-char
                                '(#.%Space #.%Tab))
                          (setq end-index? index)
                          (return))
                        (unless (wide-character-member
                                  this-char
                                  '(#.%Space #.%Tab))
                          (setq start-index? index)))
                        finally
                          (setq end-index? line-length))
                      when
                        (and start-index?
                             (protected-let
                                 ((permitted-namestring
                                    (text-string-substring
                                      line-in-disabling-file?
                                      start-index?
                                      end-index?)
                                    (reclaim-text-string permitted-namestring)))
                               (setq permitted-pathname?
                                     (gensym-pathname permitted-namestring))))
                        collect permitted-pathname? using path-cons)
                (loop for permitted-pathname in list-of-permitted-pathnames
                      do (reclaim-gensym-pathname permitted-pathname)
                         finally (reclaim-path-list list-of-permitted-pathnames))))
           (provide-pathname-for-launch-time-load-asking-os
             command-line-keyword
             environment-variable-name
             type-of-file-to-load
             default-pathname-for-file-to-load?
             list-of-permitted-pathnames
             provide-desired-namestring-p)))
        (t (provide-pathname-for-launch-time-load-asking-os
             command-line-keyword
             environment-variable-name
             type-of-file-to-load
             default-pathname-for-file-to-load?
             t ;all pathnames are permitted
             provide-desired-namestring-p
             ))))))

;; jh, 8/28/92.  Modified provide-pathname-for-launch-time-load to provide a
;; second value if the user explicitly specifies a KB in the command line or as
;; an environment variable and the caller of get-or-use-xxx-pathname requests
;; this value.  In this case, it is the responsibility of the caller to reclaim
;; this value.  The purpose of this fix is to allow G2 to warn the user if it
;; was unable to find a file specified with the -kb command-line directive.



;;; This catches the pathological case of a user giving a pathname in the
;;; command-line or an environment variable that we are supposed to load
;;; but the pathname doesn't include the filename. If other needed components
;;; of the name were worth checking for, they should go here as well. ddm 11/26/96

(defun sufficient-pathname-for-launch-time-load-p (pathname)
  (and (gensym-pathname-directory pathname)
       (gensym-pathname-name pathname)))







;;; The macro `def-suite-for-loading-file-at-launch-time' is designed to abstract
;;; some of the commonalities in loading files at launch time.  Examples of such
;;; files are OK and Init files.  This macro takes the following arguments:

;;; name-of-suite
;;; system
;;; &key base-name-of-file-to-load
;;;      type-of-file-to-load
;;;      command-line-keyword
;;;      environment-variable-name
;;;      base-name-of-disabling-file
;;;      type-of-disabling-file
;;;      module
;;;
;;; Module refers to a Lisp (source code) module, and is used as the module
;;; for which to create the system variables.  With the exception of module,
;;; all of the arguments should be either gensym or wide strings.

;;; Def-suite-for-loading-file-at-launch-time defines three Lisp entities:

;;; (1) a system variable whose name is of the form DEFAULT-xxx-PATHNAME.  This
;;; variable contains the default pathname to load at launch time, if other
;;; user-specified pathnames are not found.

;;; (2) a system variable whose name is of the form
;;; PATHNAME-FOR-DISABLING-xxx-COMMAND-LINE.  This variable is a gensym-pathname
;;; naming a file based in the machines root directory.  If this file is present,
;;; it should contain a list of filenames, one filename per line.  These
;;; filenames, and only these, may be specified in a command-line argument or
;;; environment-variable intended to load a given file at launch time.  If this
;;; file is not present, any file may be specified in the command-line-keyword or
;;; environment-variable.

;;; (3) a function GET-OR-USE-xxx-PATHNAME, which returns a gensym-pathname
;;; suitable for loading, meeting the constraints imposed by (1) and (2).  This
;;; function takes a single optional argument, provide-desired-namestring-p.  If
;;; provide-desired-namestring-p is non-nil, get-or-use-xxx-pathname will return
;;; two additional values describing the provenance of the loading pathname.
;;; The second value is the namestring specified in the command line or as an
;;; environment variable, and the third value is a keyword (one of
;;; :environment-variable or :command-line) describing where in the operating
;;; system environment the pathname was found.  It is the responsibility of the
;;; caller to reclaim this namestring when it is requested using
;;; provide-desired-namestring-p.

;;; For example, the form

;;;(def-suite-for-loading-file-at-launch-time ok g2
;;;  :base-name-of-file-to-load   "g2"
;;;  :type-of-file-to-load        "ok"
;;;  :command-line-keyword        "ok"
;;;  :environment-variable-name   "G2_OK"
;;;  :base-name-of-disabling-file "NOCMD"
;;;  :type-of-disabling-file      "OK")

;;; defines the system variables default-g2-ok-pathname and
;;; pathname-for-disabling-g2-ok-command-line and the function
;;; get-or-use-g2-ok-pathname.  When G2 is launched with the command-line keyword
;;; "-ok" or while the environment variable "G2_OK" is bound, the it will attempt
;;; to load the given file as an OK file.  If the file NOCMD.OK is present in the
;;; root directory, the command-line or environment-variable file will be matched
;;; against any file listed there before G2 will permit the load.  If the user
;;; provides no command-line or environment-variable, G2 will attempt to load
;;; "g2.ok" in the directory from which it launched.

;;; The :module keyword, unevaluated, specifies a module for the system
;;; variables defined by this macro.  It defaults to PATHNAMES.

(defmacro def-suite-for-loading-file-at-launch-time
          (name-of-suite system
           &key (base-name-of-file-to-load (format nil "~(~a~)" system))
                type-of-file-to-load
                command-line-keyword
                environment-variable-name
                base-name-of-disabling-file
                (type-of-disabling-file type-of-file-to-load)
                module)
  ;; Here's new code to coerce to wide strings up front as appropriate:
  (when base-name-of-file-to-load
    (setq base-name-of-file-to-load (stringw base-name-of-file-to-load)))
  (when type-of-file-to-load
    (setq type-of-file-to-load (stringw type-of-file-to-load)))
  (when command-line-keyword
    (setq command-line-keyword (stringw command-line-keyword)))
  (when environment-variable-name
    (setq environment-variable-name (stringw environment-variable-name)))
  (when base-name-of-disabling-file
    (setq base-name-of-disabling-file (stringw base-name-of-disabling-file)))
  (when type-of-disabling-file
    (setq type-of-disabling-file (stringw type-of-disabling-file)))
  ;; On to the rest of the original code:
  (let* ((function-providing-pathname-of-file-to-load
           (intern
             (format nil
               "GET-OR-USE-~a-~a-PATHNAME"
               system
               name-of-suite)))
         (variable-for-default-pathname
           (intern
             (format nil
               "DEFAULT-~a-~a-PATHNAME"
               system
               name-of-suite)))
         (initializer-for-variable-for-default-pathname
           (intern
             (format nil
               "INITIALIZE-~a"
               variable-for-default-pathname)))
         (variable-for-disabling-pathname
           (intern
             (format nil
               "PATHNAME-FOR-DISABLING-~a-~a-COMMAND-LINE"
               system
               name-of-suite)))
         (initializer-for-variable-for-disabling-pathname
           (intern
             (format nil
               "INITIALIZER-FOR-~a"
               variable-for-disabling-pathname))))
    `(progn
       ,@(if base-name-of-file-to-load
             `((defun ,initializer-for-variable-for-default-pathname ()
                 (gensym-make-pathname
                   :name ,base-name-of-file-to-load
                   :type ,type-of-file-to-load
                   :version :newest
                   :defaults process-specific-system-pathname))
               (def-system-variable ,variable-for-default-pathname
                                    ,(or module 'PATHNAMES)
                 (:funcall ,initializer-for-variable-for-default-pathname)))
             `((def-system-variable ,variable-for-default-pathname
                                    ,(or module 'PATHNAMES)
                 nil)))
       (defun ,initializer-for-variable-for-disabling-pathname ()
         (gensym-make-pathname
           :directory '(:absolute)
           :name ,base-name-of-disabling-file
           :type ,type-of-disabling-file
           :version :newest))
       (def-system-variable ,variable-for-disabling-pathname
                            ,(or module 'PATHNAMES)
         (:funcall ,initializer-for-variable-for-disabling-pathname))
       (defun-allowing-unwind ,function-providing-pathname-of-file-to-load
           (&optional provide-desired-namestring-p)
         (provide-pathname-for-launch-time-load
           ,variable-for-default-pathname
           ,variable-for-disabling-pathname
           ,command-line-keyword
           ,environment-variable-name
           ,type-of-file-to-load
           provide-desired-namestring-p)))))

;; jh, 5/29/92.  Modified def-suite-for-loading-file-at-launch-time to accept a
;; :base-name-of-file-to-load argument of nil, meaning there is no default file.
;; This was necessary for the option to load and start a single KB from the
;; command line (as opposed to using an init file).  Made the corresponding
;; changes to provide-pathname-for-launch-time-load.

;; jh, 8/28/92.  Modified def-suite-for-loading-file-at-launch-time to define
;; the get-or-use-xxx-filename function to take an optional argument,
;; provide-desired-namestring-p.  For further details, see the documentation of
;; provide-pathname-for-launch-time-load above.


;; gensym-delete-file
;; convertible-thing => t or nil
;; unlike CL, returns t if succeeded and nil if failed
;; (could fail if stream to file is open, depending on platform)
;; ref: CLtL/2e p653-4

(defun-allowing-unwind gensym-delete-file (convertible-thing)
  (with-protected-pathname-conversion
      ((convertible-thing pathname?))
    (when pathname?
      (protected-let ((namestring
                        (gensym-namestring pathname?)
                        (reclaim-text-string namestring)))
        (g2-stream-delete-file namestring)))))

(defun-allowing-unwind gensym-close-and-delete-file (stream)
  (with-protected-pathname-conversion
      ((stream pathname?))
    (when pathname?
      (protected-let ((namestring
                        (gensym-namestring pathname?)
                        (reclaim-text-string namestring)))
        (g2-stream-close stream)
        (g2-stream-delete-file namestring)))))


;;; gensym-directory
;;;   convertible-thing => path-list-of-gensym-pathnames
;;; Ignores errors.
;;; As usual, caller must reclaim all gensym-pathname structures passed to this
;;; function.
;;; ref: CLtL/2e p663


(defmacro gensym-filtered-directory (convertible-thing subdirectories-only-p include-unreadable-files-p)
  `(with-protected-pathname-conversion
        ((,convertible-thing directory-pathname?))
    (when directory-pathname?
      (protected-let
          ((directory-substring
             (gensym-directory-and-above-namestring
               directory-pathname?
               nil)
             (reclaim-text-string directory-substring))
           (name-and-type-substring
             (gensym-name-and-type-namestring directory-pathname? nil)
             (reclaim-text-string name-and-type-substring))
           (version-substring?
             (if (gensym-pathname-version directory-pathname?)
                 (gensym-version-namestring directory-pathname? nil)
                 nil)
             (reclaim-text-string version-substring?))
           (file-system
             (gensym-pathname-file-system directory-pathname?)))
        (let ((list-of-defaulted-filenames? ;always a path-list of text-strings
                ,(if subdirectories-only-p
                     `(g2-stream-subdirectories directory-substring
                                                name-and-type-substring
                                                version-substring?
                                                file-system
                                                ,include-unreadable-files-p)
                     `(g2-stream-directory directory-substring
                                           name-and-type-substring
                                           version-substring?
                                           file-system
                                           ,include-unreadable-files-p))))
          (if list-of-defaulted-filenames?
              (loop for defaulted-filename in list-of-defaulted-filenames?
                    for merged-pathname? = (gensym-merge-pathnames
                                             defaulted-filename
                                             directory-substring)
                    when merged-pathname?

                      collect (canonicize-host-name-from-file-system
                                merged-pathname?)
                                         using path-cons
                    do (reclaim-text-string defaulted-filename)
                    finally
                      (reclaim-path-list list-of-defaulted-filenames?))
                nil))))))

;; jh, 3/12/92.  Added a null test for the result of merge-pathnames in
;; gensym-filtered-directory.  CLtL/2e is not clear on whether
;; merge-pathnames is allowed to return nil, so gensym-merge-pathnames
;; can return nil when a parse fails.  But when gensym-merge-pathnames
;; returns nil, it affects downstream code which assumes that
;; directory-lists consist solely of gensym-pathnames.

;; jh, 3/30/92.  Discovered that an equality comparison between two
;; gensym-pathnames would not work on the Lispms under certain circumstances.
;; If one pathname was the result of a call to gensym-directory and the other
;; was the result of gensym-probe-file, the comparison would fail because the
;; host names could appear as different aliases even though they referred to the
;; same host (e.g., "ma" vs.  "massachusetts").  The cause was gensym-directory
;; not properly canonicizing host names.  Added a call to the new function
;; canonicize-host-name-from-file-system, which is currently a no-op in
;; distribution.  Note that the fix to this bug has no effect on distribution.
;; The only distribution platform that uses host names is VMS, and the host
;; component of a VMS pathname cannot have an alias per se.  (The device
;; component can have an alias, but these would be different logical names, and
;; should fail the equality comparison.)

(defun-allowing-unwind gensym-directory (convertible-thing &optional (include-unreadable-files-p t))
  (gensym-filtered-directory convertible-thing nil include-unreadable-files-p))

(defun-allowing-unwind gensym-subdirectories (convertible-thing &optional (include-unreadable-files-p t))
  (gensym-filtered-directory convertible-thing t include-unreadable-files-p))




;;; The function `all-subdirectories-in-directory' is a special case of
;;; gensym-subdirectories for convenience.  Given a directory-spec coercible to
;;; a gensym-pathname, it will provide a path-list of all the subdirectories in
;;; a given directory, each represented as a gensym-pathname.

(defun-allowing-unwind all-subdirectories-in-directory (directory-spec)
  (protected-let
   ((directory-pathname?
     (gensym-pathname directory-spec)
     (reclaim-gensym-pathname directory-pathname?))
    (directory-string
     (gensym-device-and-directory-namestring directory-pathname?)
     (reclaim-text-string directory-string)))
   (when directory-pathname?
     (let ((canonical-wild-directory-pathname?
            (make-canonical-wild-directory-pathname-if-possible
             directory-pathname?
             directory-string)))
       (when canonical-wild-directory-pathname?
         (reclaim-gensym-pathname directory-pathname?)
         (setq directory-pathname? canonical-wild-directory-pathname?))))
   (gensym-subdirectories directory-pathname?)))




;; jh, 10/8/91.  Abstracted reclaim-gensym-directory-results for use by the search
;; path mechanism.  It should come in handly elsewhere, though.

(defun reclaim-gensym-directory-results (directory-results?)
  (when directory-results?
    (loop for pathname in directory-results?
          do (reclaim-gensym-pathname pathname)
          finally (reclaim-path-list directory-results?))))




;; Changed/fixed to deal with unix pathnames like
;;
;;    /bt/mhd/lisp/g24.0
;;
;; properly.  It previously would return
;;
;;    /bt/mhd/lisp/g24/
;;
;; Now it gets
;;
;;    /bt/mhd/lisp/g24.0/
;;
;; which is correct.  It is not meant to do anything different for other
;; platforms unless there's a bug in my transformation.  As always, JH, who is
;; on vacation now, should review. (MHD 12/27/94)

(defun filestring-names-real-directory-p (filestring)
  (let* ((dwim-directory-pathname
           (or (gensym-file-as-directory filestring)
               (gensym-pathname filestring)))
         (directory-as-file-namestring
           (gensym-namestring dwim-directory-pathname)))
    (prog1 (g2-stream-directory-p directory-as-file-namestring)
      (reclaim-gensym-pathname dwim-directory-pathname)
      (reclaim-text-string directory-as-file-namestring))))


;; mhd & jh, 1/16/91.

;; Doing (system-pathname 'ab) is a bad way to get the file-loading defaults on
;; multi-process Lisp Machines.  One process could be loading (using a Lisp
;; pathname as the system-pathname property), while another could be running
;; (using a gensym-pathname).  We established the system variable
;; process-specific-system-pathname to resolve this.  The system-pathname property
;; used to be globally set in run-system-process for Lisp Machines and in
;; launch-x-image for other platforms.  Now we leave this property alone.  The
;; necessary changes have been made to the places in FILES and BOOKS which used to
;; use (system-pathname 'ab) to do defaulting.

(defun-allowing-unwind initialize-process-specific-system-pathname
    ()
  (protected-let
      ((default-directory
           (g2-stream-get-default-directory)
           (reclaim-text-string default-directory)))
    (gensym-make-pathname-function
      nil nil nil #w"g2" nil nil
      default-directory)))

(def-system-variable process-specific-system-pathname PATHNAMES
  (:funcall initialize-process-specific-system-pathname))


;;; Supply-absolute-directory-subcomponents will prepend the current working
;;; directory subcomponents to the directory list of pathname, unless that
;;; directory list is explicitly headed by a :relative tag.

;; Note that supply-absolute-directory-subcomponents depends on getting a parsable
;; string from g2-stream-get-default-directory.  In particular, the string it
;; receives on UNIX systems must end in a slash.  Thus a straight call to getcwd
;; is out.  Fixed this in cstreams.c.  jh, 6/6/91.

(defun-allowing-unwind supply-absolute-directory-subcomponents (pathname)
  (let ((relative-directory (gensym-pathname-directory pathname)))
    (unless (eq (car relative-directory) :absolute)
      (protected-let
          ((absolute-directory-string?
             (g2-stream-get-default-directory)
             (reclaim-text-string absolute-directory-string?)))
        (when absolute-directory-string?
          (protected-let*
              ((absolute-directory-pathname
                 (gensym-merge-pathnames
                   absolute-directory-string?
                   pathname)
                 (reclaim-gensym-pathname absolute-directory-pathname))
               (absolute-directory
                 (loop for component in
                           (gensym-pathname-directory
                             absolute-directory-pathname)
                       collect
                       (if (symbolp component)
                           component
                           (copy-text-string component))
                       using path-cons)))
            (when (eq (car relative-directory) :relative)
              (path-pop (gensym-pathname-directory pathname)))
            (setf (gensym-pathname-directory pathname)
                  (nconc absolute-directory
                         (gensym-pathname-directory pathname)))))))))


(defun-allowing-unwind augment-pathname-from-file-system (pathname namestring)

  ;; Add version if applicable.
  (unless (memq (gensym-pathname-file-system pathname)
                '(unix win32 dos generalized-dos))
    (unless (or (integerp (gensym-pathname-version pathname))
                ;; The following clause is for versions with internal wildcards
                ;; (such as "xyz.2*") in contexts where the version gets parsed as
                ;; a string.
                (text-string-p (gensym-pathname-version pathname)))
      (setf (gensym-pathname-version pathname)
            (g2-stream-get-version namestring))))

  ;; Canonicalize directory (remove excess :up and :relative markers).
  ;; Note that coalesce-directory-components reclaims its argument.
  (setf (gensym-pathname-directory pathname)
        (coalesce-directory-components
          (gensym-pathname-directory pathname)))

  ;; As a special case, expand the UNIX cshell metacharacter "~" into the value
  ;; of the environment variable "HOME".  Granted, we probably shouldn't do this
  ;; for every metacharacter (or every UNIX shell) out there.
  (maybe-supply-home-to-possible-unix-pathname pathname)

  ;; Add any missing components to directory.
  ;; jh, 11/18/91.  Don't do this if we are on a file system where the device
  ;; component could be a logical name which might expand into directory
  ;; components (such as VMS).  Note that we must do the check before we fill the
  ;; possibly empty device component in the next form.
  (unless (and (eq (gensym-pathname-file-system pathname) 'vms)
               (gensym-pathname-device pathname))
    (supply-absolute-directory-subcomponents pathname))

  ;; Supply device if applicable.
  ;; jh, 11/19/91.  Note that on VMS this device could be a logical name, but it
  ;; will be compatible with the absolute directory that might be obtained by the
  ;; preceding form.
  (unless (memq (gensym-pathname-file-system pathname)
                '(unix win32 dos generalized-dos))
    (unless (gensym-pathname-device pathname)
      (setf (gensym-pathname-device pathname)
            (g2-stream-get-device namestring))))

  pathname)

;; jh, 1/29/92.  Fixed augment-pathname-from-file-system to call
;; g2-stream-get-version and g2-stream-get-device only when applicable.  Calling
;; these g2-stream functions under UNIX was setting g2-stream-error-flag and
;; making KB saves look like they had failed.  It's beginning to look like this is
;; a g2-stream-operation, since it can influence g2-stream-error-flag in confusing
;; ways.  Consider moving it to STREAMS.


;;; gensym-maximum-file-name-length

;;; If there is a limit on the number of characters in a filename for files
;;; residing in the directory of convertible-thing,
;;; gensym-maximum-file-name-length returns that limit as a fixnum.  If there is
;;; no limit, or if it is unable to determine a limit, it returns nil.

(defun-allowing-unwind gensym-maximum-file-name-length (convertible-thing)
  (with-pathname-conversion ((convertible-thing pathname?))
    (if pathname?
        (protected-let ((directory-namestring
                          (gensym-directory-namestring pathname?)
                          (reclaim-text-string directory-namestring)))
          (if (equal directory-namestring "")
              (case (gensym-pathname-file-system pathname?)
                (unix (g2-stream-maximum-file-name-length "."))
                (vms (g2-stream-maximum-file-name-length "[]"))
                ((dos win32 generalized-dos)
                 (g2-stream-maximum-file-name-length "."))
                (otherwise nil))
              (g2-stream-maximum-file-name-length directory-namestring)))
        nil)))





;;; The function `find-and-open-temp-file' takes a single argument, a
;;; gensym-pathname.  This function creates a unique filename whose name
;;; component is based on the variable root-name-for-temp-file and whose other
;;; components are provided by its argument.  It then tries to open this file
;;; for writing.  If it is successful, it returns the open g2-stream.  If it has
;;; made maximum-number-of-tries-to-create-temp-file attempts and has not
;;; succeeded in creating a writeable g2-stream, find-and-open-temp-file will
;;; return nil.

;; A cursory check confirms that g2-stream-probe-file on the Sparc will indeed
;; return true if there is a stream open to the file but the file has not yet been
;; written to disk.  It is thus reasonable to assume that find-and-open-temp-file
;; will never be able to open two streams to the same temporary file name there.
;; This needs further testing on other delivery platforms, or at least a
;; committment to this behavior in some UNIX and VMS specification.  jh, 1/14/92.

;; jh, 12/1/94.  Fixed find-and-open-temp-file to give up if the candidate temp
;; file could not be opened and the error was anything other than "the file
;; already exists".  This fix works around a known bug in
;; g2-stream-probe-file-for-write, used by open-save-kb-stream-or-reject-save-kb
;; as the gate to calling find-and-open-temp-file.  Now find-and-open-temp-file
;; gives up after the first "permission denied" error rather than making 1000
;; futile attempts to open files in a non-writable directory.

(defvar root-name-for-temp-file "g2temp~a")
(defvar maximum-number-of-tries-to-create-temp-file 1000)

(defun-allowing-unwind find-and-open-temp-file (default-pathname-for-temp-file)
  (declare (eliminate-for-gsi))
  (loop for counter-for-temp-file-truename from -1
        while (<f counter-for-temp-file-truename
                  maximum-number-of-tries-to-create-temp-file)
        do
    (protected-let*
        ((base-namestring-for-temp-file
           (tformat-text-string
             root-name-for-temp-file
             ;; GENSYMCID-1344: use server port number first.
             (if (=f counter-for-temp-file-truename -1)
                 (current-system-case
                   (ab
                    (get-port-number-or-name-lisp-side))
                   (t
                    counter-for-temp-file-truename))
               counter-for-temp-file-truename))
           (reclaim-text-string base-namestring-for-temp-file))
         (pathname-for-temp-file
           (gensym-merge-pathnames
             base-namestring-for-temp-file
             default-pathname-for-temp-file)
           (reclaim-gensym-pathname pathname-for-temp-file))
         (pathname-with-intended-name?
           (gensym-probe-file pathname-for-temp-file)
           (reclaim-gensym-pathname pathname-with-intended-name?)))
      (unless pathname-with-intended-name?
        (protected-let ((temp-namestring
                          (gensym-namestring pathname-for-temp-file)
                          (reclaim-text-string temp-namestring)))
          (let ((stream? (g2-stream-open-for-binary-output temp-namestring)))
            (cond
              (stream? (return stream?))
              (t (unless (most-recently-encountered-file-already-exists-error-p)
                   (loop-finish))))))))))

;; Modified by ML on 1/18/92 to return one value. The second value is dependent
;; on the first if you want it.


;;; yduj, 10/00: gensym-probe-file returns a pathname if it succeeds, and
;;; expects its caller to reclaim this.  However, often one will just use probe
;;; file for its truth value, and it would simplify the code to not have to
;;; reclaim (and, reduce leaks where people weren't reclaiming) to have a second
;;; version for the truth value case.
(defun-allowing-unwind gensym-probe-file-for-truth-value (convertible-thing)
  (with-protected-pathname-conversion
      ((convertible-thing pathname?))
    (if pathname?
        (let ((namestring?
                (funcall (gensym-pathname-namestring-generator pathname?)
                         pathname?)))
          (if namestring?
              (prog1
                  (or (g2-stream-p convertible-thing)
                      (g2-stream-probe-file-for-read namestring?))
                (reclaim-text-string namestring?))
              nil))
        nil)))


(defun gensym-probe-file (convertible-thing)
  (with-pathname-conversion
        ((convertible-thing pathname?))
    (if pathname?
        (let ((namestring?
                (funcall (gensym-pathname-namestring-generator pathname?)
                         pathname?)))
          (cond (namestring?
                 (prog1
                     (cond ((g2-stream-p convertible-thing) pathname?)
                           ((g2-stream-probe-file-for-read namestring?)
                            ;; pathnames from streams are already filled in
                            (augment-pathname-from-file-system
                              pathname?
                              namestring?)
                            pathname?)
                           (t (reclaim-gensym-pathname pathname?)
                              nil))
                   (reclaim-text-string namestring?)))
                (t (reclaim-gensym-pathname pathname?)
                   nil)))
        nil)))

;; jh per bah, 5/17/91.  Fixed gensym-probe-file so it doesn't leak when it is
;; able to parse the namestring but unable to find it on disk.  Previously it was
;; dropping the parsed pathname under these circumstances.  Gensym-truename is
;; safe from an analogous problem, since it reclaims the parsed pathname.  Nor
;; does this problem happen with other gensym-pathname functions, since they
;; return any pathname they are able to create.

;; jh per bah, 5/20/91.  Fixed gensym-probe-file to return a gensym-pathname when
;; it gets a g2-stream as argument, even a g2-stream opened onto a new file name.
;; Note that we only set the version number if the argument to gensym-probe-file
;; is NOT a stream, since this number is already set for streams.  (All
;; g2-stream-open-xxx functions associate a version number with a stream whenever
;; the file system supports it.)

;; jh, 6/6/91.  Enhanced gensym-probe-file to supply the true default device and
;; absolute directory path.

;; jh, 1/19/94.  Rewrote the protected-let form and removed a disjunction in
;; gensym-probe-file in an attempt to work around a corruption problem.


;;; gensym-probe-file-for-write

;;; The function `gensym-probe-file-for-write' takes a single argument, a thing
;;; which can be converted to a gensym-pathname.  This function returns non-nil if
;;; it can determine that the argument names a file that can be written to.
;;; Otherwise, gensym-probe-file-for-write returns nil.  Note that a file may not
;;; exist (i.e., gensym-probe-file will return nil) and yet still be writeable
;;; (i.e., gensym-probe-file-for-write will return non-nil).

;; jh per ml, 1/14/92.  Gensym-probe-file-for-write and its companion function
;; find-and-open-temp-file will help us save KBs without clobbering the old
;; (presumably valid) file until we are sure that the new save has completed
;; successfully.

(defun-allowing-unwind gensym-probe-file-for-write (convertible-thing)
  (with-pathname-conversion
        ((convertible-thing pathname?))
    (if pathname?
        (protected-let ((namestring?
                          (funcall (gensym-pathname-namestring-generator
                                     pathname?)
                                   pathname?)
                          (reclaim-text-string namestring?)))
          (cond ((and namestring?
                      (g2-stream-probe-file-for-write namestring?))
                 ;; Added code for ~-expand, etc. just like the comment
                 ;; at g2-stream-probe-file says should be here.
                 ;; This code is the same as used by gensym-probe-file.
                 ;; - jpg 10/3/00
                 (augment-pathname-from-file-system
                   pathname?
                   namestring?)
                 pathname?)
                (t (reclaim-gensym-pathname pathname?)
                    nil)))
        nil)))


;; gensym-rename-file
;;  old-convertible-thing new-convertible-thing =>
;;    (1) new-pathname or nil
;;    (2) old-truename or nil
;;    (3) new-truename or nil
;; returns (values nil nil nil) if it fails, unlike CL, which signals an error
;; (could fail if stream to file is open, depending on platform)
;; ref: CLtL/2e p653

;; jh, 1/28/92.  Changed gensym-rename-file to return the three values that Common
;; Lisp does if the rename succeeds.  Unlike Common Lisp, if the rename fails an
;; error is not signaled.  Instead, three nil values are returned.

(defun-allowing-unwind gensym-rename-file
                       (old-convertible-thing new-convertible-thing)
  (let ((rename-succeeded-p nil))
    (with-protected-pathname-conversion
        ((old-convertible-thing old-pathname?))
      (if old-pathname?
          (protected-let
              ((old-truename?
                 (gensym-probe-file old-pathname?)
                 (unless rename-succeeded-p
                   (reclaim-gensym-pathname old-truename?))))
            (if old-truename?
                (protected-let
                    ((new-pathname?
                       (gensym-merge-pathnames
                         new-convertible-thing
                         old-pathname?)
                       (unless rename-succeeded-p
                         (reclaim-gensym-pathname new-pathname?))))
                  (if new-pathname?
                      (protected-let
                          ((old-namestring
                             (gensym-namestring old-pathname?)
                             (reclaim-text-string old-namestring))
                           (new-namestring
                             (gensym-namestring new-pathname?)
                             (reclaim-text-string new-namestring)))
                        (setq rename-succeeded-p
                              (g2-stream-rename-file
                                old-namestring
                                new-namestring))
                        (if rename-succeeded-p
                            (values new-pathname?
                                    old-truename?
                                    (gensym-probe-file new-pathname?))
                            (values nil nil nil)))
                      (values nil nil nil)))
                (values nil nil nil)))
          (values nil nil nil)))))




;; jh, 1/28/92.  Added gensym-rename-file-indifferent-to-return-values, which
;; simply returns non-nil if successful instead of three gensym-pathname values
;; which must be reclaimed.

(defun-allowing-unwind gensym-rename-file-indifferent-to-return-values
                       (old-convertible-thing new-convertible-thing)
  (with-protected-pathname-conversion
      ((old-convertible-thing old-pathname?))
    (when old-pathname?
      (protected-let* ((new-pathname?
                         (gensym-merge-pathnames
                           new-convertible-thing
                           old-pathname?)
                         (reclaim-gensym-pathname
                           new-pathname?))
                       (old-namestring
                        (gensym-namestring old-pathname?)
                        (reclaim-text-string old-namestring))
                      (new-namestring
                        (gensym-namestring new-pathname?)
                        (reclaim-text-string new-namestring)))
	;;SoftServe, 02/24/2009. Fixed KB saving facility when backup KB file is present 
   	(when (g2-stream-probe-file-for-exist new-namestring)
       	    (g2-stream-delete-file new-namestring))
        (g2-stream-rename-file old-namestring new-namestring)))))


;;;; OS Pathname Parsing


(defun encode-pathname-os (os)
  (case os
    (unix 1)
    (win32 2)
    (dos 3)
    (vms 4)
    (t 1)))

(defun decode-pathname-os (encoded-os)
  (case encoded-os
    (0 g2-operating-system)                ; Maybe sent by a pre-8.0 G2.
    (1 'unix)
    (2 'win32)
    (3 'dos)
    (4 'vms)
    (t 'unix)))

(defun os-pathname-parser (os)
  (or (filename-parser-of-file-system os)
      'parse-unix-filename))

;;; The function `os-pathname-directory' returns the host/device/directory part
;;; of a pathname from the given OS, as a newly consed text string.  Pathname
;;; must be either a text string or a gensym-pathname.

(defun os-pathname-directory (pathname os)
  (let* ((pathname-gp
           (if (gensym-pathname-p pathname)
               (copy-gensym-pathname pathname)
               (funcall-symbol (os-pathname-parser os) pathname)))
         (defaults-gp                        ; Used just to propagate the OS type.
           (funcall-symbol (os-pathname-parser os) ""))
         (directory-gp
           (gensym-make-pathname
             :host (gensym-pathname-host pathname-gp)
             :device (gensym-pathname-device pathname-gp)
             :directory (gensym-pathname-directory pathname-gp)
             :name nil
             :type nil
             :version nil
             :defaults defaults-gp)))
    (prog1 (gensym-namestring directory-gp)
      (reclaim-gensym-pathname pathname-gp)
      (reclaim-gensym-pathname defaults-gp)
      (reclaim-gensym-pathname directory-gp))))


;;; The function `os-pathname-nondirectory' returns the non-directory part of
;;; the pathname from the given OS, as a newly consed string. If pathname is a
;;; directory (eg, ends in / on unix), returns an empty string. Pathname must be
;;; either a text string or a gensym-pathname.

(defun os-pathname-nondirectory (pathname os)
  (let* ((pathname-gp
           (if (gensym-pathname-p pathname)
               (copy-gensym-pathname pathname)
               (funcall-symbol (os-pathname-parser os) pathname)))
         (defaults-gp                        ; Used just to propagate the OS type.
           (funcall-symbol (os-pathname-parser os) ""))
         (directory-gp
           (gensym-make-pathname
             :host nil
             :device nil
             :directory nil
             :name (gensym-pathname-name pathname-gp)
             :type (gensym-pathname-type pathname-gp)
             :version (gensym-pathname-version pathname-gp)
             :defaults defaults-gp)))
    (prog1 (gensym-namestring directory-gp)
      (reclaim-gensym-pathname pathname-gp)
      (reclaim-gensym-pathname defaults-gp)
      (reclaim-gensym-pathname directory-gp))))


;;;; Verbose List Directory


;;; The function `file-size?' returns the size of given file in 8-bit bytes, or
;;; NIL if the file does not exist or is not readable. Result is unpredictable
;;; if file is larger than most-positive-fixnum. Note that on Windows,
;;; directories are not readable as files.

(defun-allowing-unwind file-size? (gensym-pathname)
  (g2-stream-with-open-stream (stream? gensym-pathname :direction :input
                                       :element-type (unsigned-byte 8))
    (when stream?
      (g2-stream-file-length stream?))))


;;; The function `list-directory' returns a verbose directory listing or an
;;; error string. The listing is a newly consed path-list of (filename modtime
;;; size?), where modtime is a managed-float, and size is a fixnum. Size
;;; is omitted for directories. In case of an error, the listing is a text
;;; string containing the error message.

(defun-allowing-unwind list-directory (directory-string)
  (protected-let*
      ((directory-pathname?
         (let ((accept-any-version-component-p t)) ;for wildcarding versions
           (gensym-pathname directory-string))
         (reclaim-gensym-pathname directory-pathname?))

       (wild-pathname
         (let ((canonical-wild-directory-pathname?
                 (make-canonical-wild-directory-pathname-if-possible
                   directory-pathname?
                   directory-string)))
           (when canonical-wild-directory-pathname?
             (reclaim-gensym-pathname directory-pathname?)
             (setq directory-pathname? canonical-wild-directory-pathname?))
           directory-pathname?))

       (gensym-pathnames (gensym-directory wild-pathname nil)
                         (reclaim-path-list-of-gensym-pathnames gensym-pathnames)))

    ;; If listing failed, return error message. Otherwise, compute the verbose
    ;; directory listing.
    (cond ((g2-stream-error-flag-set-p)
           (most-recent-file-operation-status-as-text))
          (t
           (loop for gensym-pathname in gensym-pathnames
                 as pathname = (gensym-namestring gensym-pathname)
                 as filename? = (when (gensym-pathname-name gensym-pathname) ; Skip . and ..
                                  (protected-let*
                                      ((filestring
                                         (gensym-file-namestring gensym-pathname)
                                         (reclaim-text-string filestring)))
                                    (import-text-string filestring 'g2-directory-pathname)))
                 as modtime? = (g2-stream-file-modification-date pathname)
                 as dir? = (g2-stream-directory-p pathname)
                 as size? = (if dir? 0 (file-size? gensym-pathname))
                 when (and filename? modtime? size?)
                   collect (nconc (path-list filename? modtime?)
                                  (unless dir? (path-list size?)))
                     using path-cons)))))

;; Cf: files-in-directory-lisp-side
;; TODO: links, special files, etc?


;;; The function `reclaim-directory-listing' reclaims the results of
;;; list-directory.

(defun reclaim-directory-listing (listing)
  (cond ((consp listing)
         (loop for entry in listing
               as (name time) = entry
               doing
           (reclaim-text-string name)
           (reclaim-managed-float time)
           (reclaim-path-list entry))
         (reclaim-path-list listing))
        ((text-string-p listing)
         (reclaim-text-string listing))))

(defun-void reclaim-path-list-of-gensym-pathnames (gensym-pathname-list)
  (loop for gp in gensym-pathname-list do (reclaim-gensym-pathname gp))
  (reclaim-path-list gensym-pathname-list))



;;;; Utilities


;;; The function `parent-directory-pathname' returns a newly consed
;;; gensym-pathname for the directory containing the given pathname, or NIL if
;;; already at root. If called iteratively then this function is guarenteed to
;;; eventually return NIL.  The returned pathname is not necessarily canonical;
;;; it has a name part only if the input pathname did.

(defun parent-directory-pathname (pathname)
  (let* ((default-directory (g2-stream-get-default-directory))
         (gensym-pathname (gensym-merge-pathnames pathname default-directory))
         (host (gensym-pathname-host gensym-pathname))
         (device (gensym-pathname-device gensym-pathname))
         (directory (gensym-pathname-directory gensym-pathname))
         (has-name? (or (gensym-pathname-name gensym-pathname)
                        (gensym-pathname-type gensym-pathname)))
         (parent
           (cond ((equal directory '(:absolute))
                  (if has-name?
                      (gensym-make-pathname :host host :device device :directory directory)))
                 ((null directory)                ; Should not happen
                  #+development
                  (cerror "Proceed" "Null directory should not happen: ~s" pathname)
                  nil)
                 (t
                  (let* ((directory* (nreverse (copy-list-using-gensym-conses directory)))
                         (last (gensym-pop directory*))
                         (name* (if has-name? last)))
                    (setq directory* (nreverse directory*))
                    (let ((gp (gensym-make-pathname :host host :device device
                                                    :directory directory*)))
                      (reclaim-gensym-list directory*)
                      (cond (name*
                             (prog1 (gensym-merge-pathnames gp name*)
                               (reclaim-gensym-pathname gp)))
                            (t
                             gp))))))))
    (reclaim-text-string default-directory)
    (reclaim-gensym-pathname gensym-pathname)
    parent))

;;; The function `canonical-directory-pathname' returns a newly consed
;;; gensym-pathname equivalent to the given pathname, such that
;;;  (1) It is an absolute pathname
;;;  (2) It has non-NIL name/type part, or else is the root directory.
;;; This convention for directory pathnames agrees with the pathnames returned
;;; by `all-subdirectories-in-directory'.

(defun canonical-directory-pathname (pathname)
  (let* ((default-directory (g2-stream-get-default-directory))
         (gensym-pathname (gensym-merge-pathnames pathname default-directory))
         (host (gensym-pathname-host gensym-pathname))
         (device (gensym-pathname-device gensym-pathname))
         (directory (gensym-pathname-directory gensym-pathname))
         (has-name? (or (gensym-pathname-name gensym-pathname)
                        (gensym-pathname-type gensym-pathname))))
    (reclaim-text-string default-directory)
    (cond (has-name?
           gensym-pathname)
          ((equal directory '(:absolute))
           gensym-pathname)
          ((null directory)                ; Should not happen
           #+development
           (cerror "Proceed" "Null directory should not happen: ~s." gensym-pathname)
           gensym-pathname)
          (t
           (let* ((directory* (nreverse (copy-list-using-gensym-conses directory)))
                  (name* (gensym-pop directory*)))
             (setq directory* (nreverse directory*))
             (prog1
                 (gensym-make-pathname :host host :device device
                                       :directory directory* :name name*)
               (reclaim-gensym-list directory*)
               (reclaim-gensym-pathname gensym-pathname)))))))

;; As a newly-consed wide string.
(defun default-root-directory ()
  (let* ((default-directory (g2-stream-get-default-directory))
         (default-directory-gp (gensym-pathname default-directory))
         (root-directory-gp (gensym-make-pathname :directory '(:absolute)
                                               :host (gensym-pathname-host default-directory-gp)
                                               :device (gensym-pathname-device default-directory-gp))))
    (prog1 (gensym-namestring root-directory-gp)
      (reclaim-gensym-pathname root-directory-gp)
      (reclaim-gensym-pathname default-directory-gp)
      (reclaim-text-string default-directory))))

;; This is well-defined only because we no longer support VMS.
(defun pathname-separator-as-string ()
  (case g2-operating-system
    ((win32 dos) #w"\\")
    (t #w"/")))

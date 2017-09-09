;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module CHANGE-LOG

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; John Valente and Mark H. David




;;;; KB (module) versions

;; To be documented.  -jv, 1/25/07

;;; `change-logging-kb-version'

(def-list-structure
    (change-logging-kb-version (:consing-function slot-value-cons))
    (change-logging-kb-version-number
      change-logging-kb-version-timestamp
      change-logging-kb-version-uuid))


;;; `make-version-information-entry-for-change-logging'

(defun make-version-information-entry-for-change-logging (version-number)
  (make-change-logging-kb-version
    version-number
    (get-current-frame-edit-timestamp)
    (make-uuid)))


;;; `make-initial-version-information-for-change-logging'

(defun make-initial-version-information-for-change-logging ()
  (slot-value-list
    (make-version-information-entry-for-change-logging 1)))


;;; `enable-kb-change-logging' of saving-parameters

;; The new convention is to avoid ? even in boolean (yes-or-no) slots; previously,
;; it was to be avoided in all slots except yes-or-no.  So here's the alias,
;; accordingly.  (MHD 1/9/96)

(define-slot-alias enable-kb-change-logging enable-kb-change-logging?
  saving-parameters)


;;; `enable-kb-change-logging?' slot-putter

(def-slot-putter enable-kb-change-logging?
    (saving-parameters value initializing?)
  (unless (or initializing? loading-kb-p)
    (cond
      ((and value
            (null
              (kb-version-information-for-change-logging
                saving-parameters)))
       (change-slot-value
         saving-parameters
         'kb-version-information-for-change-logging
         (make-initial-version-information-for-change-logging)
         nil)))
    (propagate-enable-kb-change-logging-to-new-system-table
      value saving-parameters))
  (setf (enable-kb-change-logging? saving-parameters) value))


;;; `kb-version-information-for-change-logging' slot-value-writer

(def-slot-value-writer kb-version-information-for-change-logging (value)
  (if (null value)
      (tformat "none")
      (loop for change-logging-kb-version in value
            as first-time? = t then nil
            unless first-time?
              do (tformat ";~%")
            do (tformat "Version ~d ("
                        (change-logging-kb-version-number change-logging-kb-version))
               (twrite-frame-edit-timestamp
                 (change-logging-kb-version-timestamp change-logging-kb-version))
               (tformat ")"))))


;;; `flush-version-information-for-change-logging-from-table-now'

(defun flush-version-information-for-change-logging-from-table-now (item)
  (when (and (frame-of-class-p item 'saving-parameters)
             (kb-version-information-for-change-logging item))
    (change-slot-value
      item 'kb-version-information-for-change-logging
      (if (enable-kb-change-logging? item)
          (make-initial-version-information-for-change-logging)
          nil))))


;;; `flush-version-information-for-change-logging-from-table' UI command

(define-ui-command (flush-version-information-for-change-logging-from-table
                     :name flush-version-information)
    (slot-name item original-x-in-window original-y-in-window)
  "Flush the change log for this item"
  (when (and package-preparation-mode
             (eq slot-name 'kb-version-information-for-change-logging)
             (and (frame-of-class-p item 'saving-parameters)
                  (kb-version-information-for-change-logging item)))
    (confirm-or-cancel
      (tformat-text-string
        "Flush all version information for this KB?  Once flushed, this information ~
        cannot be recovered.")
      'flush-version-information-for-change-logging-from-table-now
      (slot-value-list item))))


;;; `g2-flush-version-information' system procedure

(defun-for-system-procedure g2-flush-version-information (item)
  (declare (keeps-g2-local-variables-valid t))
  (if (frame-of-class-p item 'saving-parameters)
      (flush-version-information-for-change-logging-from-table-now item)
      (stack-error cached-top-of-stack
                   "~NA must be an instance of saving-parameters."
                   item)))


;;; `g2-delete-version-information-entry' system procedure

(defun-for-system-procedure g2-delete-version-information-entry (sav-params entry-number)
  (cond
    ((not (frame-of-class-p sav-params 'saving-parameters))
     (stack-error cached-top-of-stack
                  "~NA must be an instance of saving-parameters."
                  sav-params))
    ((null (kb-version-information-for-change-logging sav-params))
     (stack-error cached-top-of-stack
                  "~NA does not have any KB version information."
                  sav-params))
    ((<f entry-number 1)
     (stack-error cached-top-of-stack
                  "~NA is an invalid entry-number for KB version information."
                  entry-number))
    ((=f entry-number (caar (kb-version-information-for-change-logging sav-params)))
     (stack-error cached-top-of-stack
                  "~NA is a the current KB version; it cannot be deleted except by flushing the entire attribute."
                  entry-number))
    (t
     (loop for rest on (kb-version-information-for-change-logging sav-params)
           when (>f entry-number (caar rest)) do
               (stack-error cached-top-of-stack
                            "~NA does not exist in the KB version information of ~NA."
                            entry-number sav-params)
           when (=f entry-number (caadr rest)) do
               (with-updates-to-representations
                   (sav-params (get-slot-description-of-class-description
                           'kb-version-information-for-change-logging
                           (class-description 'saving-parameters)))
                 (let ((entry-to-delete (cadr rest)))
                   (setf (cdr rest) (cddr rest))
                   (reclaim-wide-string (change-logging-kb-version-uuid entry-to-delete))
                   (setf (change-logging-kb-version-uuid entry-to-delete) nil)
                   (reclaim-slot-value-list entry-to-delete)))
               (return-from g2-delete-version-information-entry t)))))


;;; `increment-version-for-change-logging-if-appropriate'

(defun increment-version-for-change-logging-if-appropriate
    (saving-parameters-instance)
  (let ((instance saving-parameters-instance))
    (when (kb-version-information-for-change-logging instance)
      (change-slot-value
        saving-parameters-instance
        'kb-version-information-for-change-logging
        (slot-value-cons
          (make-version-information-entry-for-change-logging
            (1+f (change-logging-kb-version-number
                   (first (kb-version-information-for-change-logging instance)))))
          (copy-for-slot-value
            (kb-version-information-for-change-logging instance)))))))

;; See caller in make-or-clear-complete-kb-name, which changes other slots as
;; well.


;;; `get-saving-parameters-for-frame'

(defun get-saving-parameters-for-frame (frame)
  (let ((module?
          (or (if (block-p frame)
                  (get-module-block-is-in frame))
              (get-slot-value
                module-information
                'top-level-kb-module?))))
    (or (if module?
            (get-system-table-of-class-for-module-or-nil
              module? 'saving-parameters))
        saving-parameters)))


;;; `module-uuid-for-frame-if-logging?'

(defun module-uuid-for-frame-if-logging? (frame)
  (let ((saving-parameters-instance
          (get-saving-parameters-for-frame frame)))
    (if (get-slot-value
          saving-parameters-instance
          'enable-kb-change-logging?)
        (change-logging-kb-version-uuid
          (first
            (kb-version-information-for-change-logging
              saving-parameters-instance))))))




;;;; Version Control Parameters



;;; The system table `version-control-parameters'.  Will have slots to specify
;;; how to do external diffing, in the near future.

(def-system-frame version-control-parameters change-log

  (enable-kb-change-logging
    nil lookup-slot system (type yes-or-no))

  (temp-file-1
    nil system lookup-slot
    (type nil)
    do-not-clone do-not-save
    do-not-put-in-attribute-tables)

  (temp-file-2
    nil system lookup-slot
    (type nil)
    do-not-clone do-not-save
    do-not-put-in-attribute-tables)

  (output-filename
    nil system lookup-slot
    (type nil)
    do-not-clone do-not-save
    do-not-put-in-attribute-tables)

  (error-filename
    nil system lookup-slot
    (type nil)
    do-not-clone do-not-save
    do-not-put-in-attribute-tables)

  (command-line
    nil system lookup-slot
    (type nil)
    do-not-clone do-not-save
    do-not-put-in-attribute-tables)

)


;;;  `enable-kb-change-logging' on version-control-parameters slot-putter.
;;; Stays in synch with the very similarly named slot on saving-parameters.

(def-slot-putter enable-kb-change-logging
    (version-control-parameters value initializing?)
  (declare (ignore initializing?))
  (let* ((saving-parameters?
           (get-saving-parameters-for-frame
             version-control-parameters)))
    (when saving-parameters?
        (change-slot-value
          saving-parameters
          'enable-kb-change-logging?
          value)))
  (setf (enable-kb-change-logging version-control-parameters) value))


;;; `propagate-enable-kb-change-logging-to-new-system-table'

(defun-simple propagate-enable-kb-change-logging-to-new-system-table (value sp-system-frame)
  (let* ((vc-parameters?
           (get-system-table-of-class-for-module-or-nil
             (get-module-block-is-in sp-system-frame)
             'version-control-parameters))
         (buddy-slot-description
           (get-slot-description-of-class-description
             'enable-kb-change-logging
             (class-description 'version-control-parameters))))
    (when vc-parameters?
      (with-updates-to-representations
	  (vc-parameters? buddy-slot-description)
	(setf (enable-kb-change-logging vc-parameters?) value)))))



;;;; External Diffs


;;; `default-external-diff' values

(defconstant default-unix-diff-program #w"/usr/bin/diff")
(defconstant default-unix-diff-options #w"-b")

(defconstant default-windows-diff-program #w"C:\\WINDOWS\\system32\\fc.exe")
(defconstant default-windows-diff-options #w"") 


;;; `get-default-diff-program?'

(defun get-default-diff-program? ()
  (copy-text-string
    (if (eq 'unix local-file-system)
        default-unix-diff-program
        default-windows-diff-program)))


;;; `get-default-diff-options?'

(defun get-default-diff-options? ()
  (copy-text-string
    (if (eq 'unix local-file-system)
        default-unix-diff-options
        default-windows-diff-options)))


;;; `external-diff-program?' and `external-diff-options?'.  I think, rather than
;;; being defvars, I want to keep these in the version-control-parameters system
;;; table; and then, instead of setting them via system procedure, they can be
;;; edited directly (and saved out) in the system table.  The biggest issue I
;;; have with doing that is the slot-type.  And once I set the slot-type, it's
;;; a little bit of a problem to change it, because kbs may get saved out with
;;; the old type.  To make things simpler for now, use defvars.  -jv, 2/14/07

(defvar external-diff-program? (get-default-diff-program?))
(defvar external-diff-options? (get-default-diff-options?))


;;; `g2-set-up-external-diff' - while the values are not accessible via system
;;; table, this is the only way to set them.  If we do switch over to a system
;;; table implementation, as I hope we do, we could remove this system procedure
;;; from sys-mod, or rewrite it to modify the system table, or both.  -jv

(defun-for-system-procedure g2-set-up-external-diff (value)
  (let* ((diff-program? (evaluation-structure-slot value 'pathname))
         (diff-options? (evaluation-structure-slot value 'command-line-options)))
    (cond
      ((not (evaluation-text-p diff-program?))
       (stack-error cached-top-of-stack "diff pathname must be text"))
      ((and diff-options? (not (evaluation-text-p diff-options?)))
       (stack-error cached-top-of-stack "diff options must be text"))
      (t
       ;; at this point, we're going to blow away the old values, even if there
       ;; is some problem with the new values
       (when external-diff-program?
         (reclaim-text-string external-diff-program?)
         (setq external-diff-program? nil))
       (when external-diff-options?
         (reclaim-text-string external-diff-options?)
         (setq external-diff-options? nil))
       (let ((requested-diff-program (evaluation-text-value diff-program?)))
         (setq external-diff-program? (copy-text-string requested-diff-program))
         (when diff-options?
           (setq external-diff-options?
                 (copy-text-string (evaluation-text-value diff-options?)))))
       (make-evaluation-truth-value truth)))))


;;; `delete-files-after-external-diff-p' - normally, of course, we'd always want
;;; to delete the temporary files when we're done with them.  But for debugging
;;; purposes, we'll allow that functionality to be disabled.  This can be set or
;;; unset via the hidden system procedure; there's no intention to put this
;;; system procedure into sys-mod.

(defvar delete-files-after-external-diff-p t)

(defun-for-system-procedure g2-delete-files-after-external-diff (value)
  (setq delete-files-after-external-diff-p
        (and (evaluation-truth-value-p value)
             (evaluation-truth-value-is-true-p value))))


;;; `set-version-control-diff-command-line-if-possible'

(defun set-version-control-diff-command-line-if-possible ()
  (setf (command-line version-control-parameters)
        (tformat-text-string
          (case local-file-system
            (unix      "~A ~A ~A ~A > ~A 2> ~A")
            (otherwise "~A ~A ~A ~A > ~A 2> ~A"))
          external-diff-program?
          (or external-diff-options? #w"")
          (temp-file-1 version-control-parameters)
          (temp-file-2 version-control-parameters)
          (output-filename version-control-parameters)
          (error-filename version-control-parameters))))


;;; `set-version-control-diff-filenames'

(defun set-version-control-diff-filenames (need-temp-files-p)
  (when need-temp-files-p
    (setf (temp-file-1 version-control-parameters)
          (make-unique-file-name "fo"))
    (setf (temp-file-2 version-control-parameters)
          (make-unique-file-name "ft")))
  (setf (output-filename version-control-parameters)
        (make-unique-file-name "output"))
  (setf (error-filename version-control-parameters)
        (make-unique-file-name "error"))
  (and (temp-file-1 version-control-parameters)
       (temp-file-2 version-control-parameters)
       (output-filename version-control-parameters)
       (error-filename version-control-parameters)))


;;; `verify-external-diffing'

(defun verify-external-diffing (need-temp-files-p)
  (cond
    ((null external-diff-program?)
     'no-diff-found)
    ((not (verify-executable external-diff-program?))
     'can-not-execute)
    ((not (set-version-control-diff-filenames need-temp-files-p))
     'can-not-make-generate-temp-filenames)
    ((not (set-version-control-diff-command-line-if-possible))
     'can-not-generate-command-line)
    (t
     nil)))


;;; `external-diff-files'

(defun external-diff-files ()
  (let ((pid -1)
        (result? nil))
    (c-set_inherit_stdio_handles 0)
    (with-temporary-gensym-float-creation external-diff-files
      (setq pid (c-spawn_command_line_process
                  (command-line version-control-parameters))))
    (c-set_inherit_stdio_handles 1)
    (reclaim-text-string (command-line version-control-parameters))
    (setf (command-line version-control-parameters) nil)
    (loop while (/=f 0 (c-process_exists pid)) do
      (dmesg "waiting for pid ~s to finish...~%" pid)
      (sleep 1))
    (dmesg "pid ~s finished~%" pid)

    (setq result?
          (allocate-evaluation-structure
            (eval-list 'diff-output
                       (read-text-file-into-wide-string
                         (output-filename version-control-parameters))
                       'diff-error
                       (read-text-file-into-wide-string
                         (error-filename version-control-parameters)))))

    (when delete-files-after-external-diff-p
      (g2-stream-delete-file (output-filename version-control-parameters))
      (g2-stream-delete-file (error-filename version-control-parameters)))

    result?))


;;; `external-diff-text-strings'

(defun external-diff-text-strings (t1 t2)
  (let* ((f1 (temp-file-1 version-control-parameters))
         (f2 (temp-file-2 version-control-parameters))
         (success-p (write-wide-string-into-text-file t1 f1))
         (result? nil))
    (when success-p
      (setq success-p (write-wide-string-into-text-file t2 f2))
      (cond
        (success-p
         (setq result? (external-diff-files))
         (when delete-files-after-external-diff-p
           (g2-stream-delete-file f1)
           (g2-stream-delete-file f2)))
        (t
         (g2-stream-delete-file f1))))
    result?))


;;; `g2-diff-texts'

(defun-for-system-procedure g2-diff-texts (text1 text2)
  (let ((error-symbol? (verify-external-diffing t)))
    (cond
      (error-symbol?
       (stack-error cached-top-of-stack
                    "Unable to execute external diff: ~s" error-symbol?))
      (t
       (external-diff-text-strings
         (evaluation-text-value text1)
         (evaluation-text-value text2))))))



;;; `g2-text-file-contents' - not really related to diffing per se; just takes
;;; the new functionality we created for diffing, reading a text-file wholesale
;;; into a G2 text, and exposes it at the G2 level.  Though, we haven't added
;;; it to sys-mod yet, and might not.

(defun-for-system-procedure g2-text-file-contents (eval-filename)
  (let* ((filename (evaluation-text-value eval-filename))
         (the-text (read-text-file-into-wide-string filename))
         (result (make-evaluation-text the-text)))
    (reclaim-text-string the-text)
    result))




;;;; Change Logging

;; Design notes.... Originally composed, with disclaimer that they were "not
;; necessarily coherent at [that] time", by MHD on 11/17/96.
;;
;; A `frame change log' is a list. Each member of the list is a
;; `change log entry', which is a list of the form
;;
;;    slot-name -- the pretty name of the slot
;;    class-qualifier? -- the class qualifier of the slot name, if necessary
;;    edit-type -- intended to allow us to log transient edits and programmatic
;;      edits (are they the same thing?); for now, is always PERMANENT
;;    timestamp -- when the edit was made
;;    author -- who made the edit; this may become more complicated if we begin
;;      logging transient changes
;;    revision -- an integer which uniquely identifies the entry, given the
;;      frame and the attribute
;;    tags? -- a list of any symbolic tags applied to the entry
;;    type-of-text-stored -- we may want to store only diffs in the future.
;;      We need to know whether the value stored in the text is the full text,
;;      or a diff of some alternate version.  For now, always FULL-TEXT.
;;    slot-value-text -- a "text" Lisp object (list with LOST-SPACES, etc.)
;;      representing what the user would see in the slot in an attribute table
;;    log? -- a user-supplied message documenting the entry
;;    uuid-of-save -- the UUID which identifies the version the module; see
;;      "KB (module) versions" section, above.
;;
;; The functionality can be understood by the user as follows: as you edit
;; definitional items in G2, the previous versions are kept in the item.  You
;; can go back and review a item's previous value for any slot which supports
;; change-logging.  It seems a must that users be able to get at previous
;; "versions" of items, at least insofar as they feel that the new change
;; logging facility keeps information useful for constructing a previous
;; "version", and to see what changes have occured since a certain version.  To
;; provide this, as of 8.3b0, we are introducing the concept of a `revision'.

;; In classic source code control, developers are aware of making a `commit' in
;; a module.  In classic G2 development, there is no exact analog.  One could
;; consider saving the kb to be analogous -- that was part of the original
;; design -- but we're not so sure about that any more.  Instead, every edit
;; will, in fact, be like a commit.  Every edit will get its own revision
;; number.  Actually, given the history, there was little other choice.  It was
;; apparently part of the original design that "when G2 is saved, the entries
;; since the last save are normally eliminated, but for the last."  But that was
;; never implemented.  So now we have lots of kbs with lots of change-log
;; entries, including multiple entries for a single "kb version".  We need to
;; retroactively number these revisions.  What are we supposed to do?  Purge the
;; entries now, well after the fact, and only assign revisions to the last
;; version from each save?  Nope.  Every entry has to get a revision number.
;; And so that's what we'll do going forward, too.

;; Frame-change-log slot is a slot on various items, and is selectively enabled
;; by giving it the type feature (TYPE FRAME-CHANGE-LOG).  The classes that got
;; this enabled in 5.0 were those for which the authors attribute was exposed in
;; 4.0, basically the definitional classes. The writer for frame-change-log
;; writes a count of the changes.  There was Lisp code which implemented a
;; different type of writer, used when a variable called write-frame-change-log-
;; in-long-form? was set.  But there was no documented way to get the "long
;; form", a search through the Lisp code found no obvious way to set it, and an
;; email sent to Engineering yielded no positive responses.  We've decided this
;; was dead code and removed it.

;; Instances of the classes for which this feature is enabled are called "items
;; with changes logged".

;; We might consider a "change" to a slot anything which causes the slot value
;; to be recompiled.  However, not all such changes get logged:

;; If change logging is globally disabled for the module in which the item
;; resides, change-logging is never done.

;; Change-logging is intended to capture user edits.  Programmatic changes do
;; not affect the change-log.  That makes a lot of sense when the programmatic
;; change is transient, as is usually the case.  But even if an item is "made
;; permanent" after a transient change, the change never gets logged.

;; Also, as of 8.3b0, edits which do not change the text of the slot do not get
;; logged.  If you open up the editor on a slot, and hit control+enter, the slot
;; gets recompiled, the authors slot gets updated, and if it's a procedure then
;; active invocations are aborted.  But it will not affect the change log.

;; There were some comments here indicating that when multiple edits were done
;; between kb saves, then perhaps not all such edits would get logged.  However,
;; there's no evidence that was ever the case, and it certainly is not today.

;; There also was talk of a feature which would automatically prune some entries
;; upon a kb save, but, again, this seems to never have been implemented.
;; Instead, as of 8.3b0, we will provide a system procedure to delete any given
;; change-log entry.  There has always been a system procedure to delete *all*
;; the change-log entries for a given item.


(def-concept change-logging)


;;; `change-log-entry-for-slot' -- this is a "list-structure".  It might want
;;; to be a "real" structure, and could be, but first code would need to be
;;; written to write it out upon kb-save, and read it back in upon kb-load.
;;; By using a list, we get save and load for free.  I'd prefer to use a
;;; def-structure, but don't have time to do the serialization, so it will
;;; have to remain a list for now.  -jv, 1/25/07

(def-list-structure
    (change-log-entry-for-slot (:consing-function slot-value-cons))
    (change-log-entry-slot-name
      change-log-entry-class-qualifier?
      change-log-entry-edit-type
      change-log-entry-timestamp
      change-log-entry-author
      change-log-entry-revision
      change-log-entry-tags?
      change-log-entry-type-of-text-stored
      change-log-entry-slot-value-text
      change-log-entry-log?
      change-log-entry-uuid-of-save))





;;; `change-log-information-entry' - the change log slot itself just contains
;;; actual entries.  The slot "change-log-information" has some metadata about
;;; how we're logging: first, whether or not change-logging is enabled on the
;;; item (always T by default), and then an a-list of slot-names with the
;;; revision number at the head of the list.  When we want to add a new entry
;;; to the change log, and need to find out what its revision number should be,
;;; we just look at the change-log-information.  We don't need to look through
;;; the actual change log.

(defun change-log-information-entry (slot-name class-qualifier? revision-number)
  (slot-value-list
    (if class-qualifier?
        (slot-value-cons slot-name class-qualifier?)
        slot-name)
    revision-number))


;;; `build-change-log-information' is used as part of a post-loading function,
;;; because older kbs did not have change-log-information.  It can be used to
;;; construct the change-log for any item, though.

(defun build-change-log-information (frame)
  (loop with revision-list = '()
        for entry in (frame-change-log frame)
        as slot-name = (change-log-entry-slot-name entry)
        as class-qualifier? = (change-log-entry-class-qualifier? entry)
        do
    (unless (loop for (slot-denot nil) in revision-list thereis
                  (or (and (null class-qualifier?)
                           (eq slot-denot slot-name))
                      (and (listp slot-denot)
                           (eq (car slot-denot) slot-name)
                           (eq (cdr slot-denot) class-qualifier?))))
      (slot-value-push
        (change-log-information-entry slot-name class-qualifier?
                                      (change-log-entry-revision entry))
        revision-list))
        finally
          (setf (change-log-information frame) (slot-value-cons t revision-list))))


;;; `ensure-frame-change-log-information' - in theory, we should only need to
;;; build change-log-information in the post-load of old kbs.  But let's be
;;; certain.  Under some circumstances, we could consider it an error that the
;;; change-log-information is nil, but for now, we'll just let things be happy.

(defun ensure-frame-change-log-information (frame)
  (when (null (change-log-information frame))
    (build-change-log-information frame)))


;;; `add-change-log-information-to-83b0-kbs' - *only* runs when a kb of version
;;; 281 is loaded. Anything older than that will have its change-log-information
;;; built by another post-loading function, convert-old-change-logs-to-new-form,
;;; below.  And anything newer, in theory, would have the slots updated and
;;; saved out properly.
;;;
;;; That "in theory" is kind of important.  I'm doing something nonstandard and
;;; probably wrong.  I'm not bumping the kb flags.  So even after kbs get fixed
;;; up, they'll still be saved out as version 281.  Then the next time they're
;;; loaded, this function will run again.  But that'll be ok, the function won't
;;; do anything.  And it just seems a little heavyweight to bump the kb flags
;;; for this.  My assumption is that someone else will do so relatively soon,
;;; and kbs saved after that will not run this code.  -jv, 2/2/07

(def-post-loading-function add-change-log-information-to-83b0-kbs
  (when (=f kb-flags-from-last-kb-read 281)
    (loop for frame being class-instance of 'block
          when (frame-change-log frame) do
              (ensure-frame-change-log-information frame))))


;;; `convert-frame-change-log-to-new-form' - only to be used from the
;;; post-loading function below.  This function assumes that the
;;; change-log-portion is in the "old", kb-flags 280 or earlier version.
;;; -jv, 1/22/07

(defun convert-frame-change-log-to-new-form (frame-change-entries frame)
  (loop with revision-list = '()
        with new-frame-change-log = '()
        with current-module-uuid? = (module-uuid-for-frame-if-logging? frame)
        for uuid-and-entry-list in frame-change-entries
        as module-uuid = (car uuid-and-entry-list)
        as entries = (cdr uuid-and-entry-list)
        do
    (loop for entry in entries
          as slot-name = (first entry)
          as slot-value-text = (second entry)
          as timestamp = (third entry)
          as author = (fourth entry)
          as tag? = (fifth entry)
          as slot-status? = (assq slot-name revision-list)
          as revision = (progn
                          (when (null slot-status?)
                            (setq slot-status? (slot-value-list slot-name
                                                                initial-change-log-revision-number))
                            (slot-value-push slot-status? revision-list))
                          (cadr slot-status?))
          as replacement-entry = (make-change-log-entry-for-slot
                                   slot-name nil 'permanent
                                   timestamp author revision
                                   (if tag? (slot-value-list tag?))
                                   'full-text slot-value-text nil
                                   (copy-for-slot-value module-uuid))
                                   do
      (slot-value-push replacement-entry new-frame-change-log)
      (incff (cadr slot-status?))
      (reclaim-slot-value-list entry))
    (reclaim-slot-value-list entries)
    (reclaim-wide-string module-uuid)
    finally
          ;; now, we update for Suggestion HQ-5410133 "include current-version
          ;; in g2-get-change-log-for-item".  For any slot which we see has been
          ;; logged, we make sure to add the current version to the log, as
          ;; well.  Note that it's possible for a slot to have been logged, and
          ;; to no longer be part of the class; that's why we check the result
          ;; of get-slot-description-of-frame.  -jv, 1/29/07
          (when current-module-uuid?
            (loop for (slot-name slot-revision) in revision-list
                  when (get-slot-description-of-frame slot-name frame nil) do
                      (slot-value-push
                        (make-change-log-entry-for-slot
                          slot-name nil 'permanent
                          (get-current-frame-edit-timestamp)
                          (slot-value-list 'post-load) slot-revision
                          '() 'full-text
                          (make-text-representation-for-slot-value
                            frame slot-name)
                          nil
                          (copy-for-slot-value current-module-uuid?))
                        new-frame-change-log)))
          (setf (change-log-information frame) (slot-value-cons t revision-list))
          (setf (frame-change-log frame) new-frame-change-log)))


;;; `frame-change-log-is-in-old-form-p'

(defmacro frame-change-log-is-in-old-form-p (frame-change-log)
  (avoiding-variable-capture (frame-change-log)
    `(text-string-p (caar ,frame-change-log))))


;;; `convert-old-change-logs-to-new-form' - at first, I forgot how often a
;;; post-loading runs.  It doesn't run only after a "complete" kb-load, i.e.,
;;; after the top-level module has loaded.  It runs after each module loads.
;;; Furthermore, even if that weren't true for an "automated" load, it would
;;; have to be true for a merge-kb.  So, just because the kb we're reading in
;;; is "old", doesn't mean we can assume that every frame in G2 is old.  So
;;; we do have to actually check the status of the frame-change-log before we
;;; try to convert it.  That's what frame-change-log-is-in-old-form-p is for.

(def-post-loading-function convert-old-change-logs-to-new-form
  (unless (>=f kb-flags-from-last-kb-read 281)
    (loop for frame being class-instance of 'block
          as the-change-log? = (frame-change-log frame)
          when (frame-change-log-is-in-old-form-p the-change-log?) do
              (setf (frame-change-log frame) nil)
              (convert-frame-change-log-to-new-form
                (nreverse the-change-log?) frame))
    (loop for system-table-a-list in modules-and-system-tables-a-list do
      (loop with vc-params = nil
            with sv-params = nil
            for system-frame in system-table-a-list
            when (frame-of-class-p system-frame 'version-control-parameters) do
                (setq vc-params system-frame)
            when (frame-of-class-p system-frame 'saving-parameters) do
                (setq sv-params system-frame)
            finally
              (setf (enable-kb-change-logging vc-params)
                    (enable-kb-change-logging? sv-params))))))


;;; the `frame-change-log' slot-value-writer

(def-slot-value-writer frame-change-log (value frame)
  (let ((n (length value)))
    (tformat "~d~a~a"
             n
             (if (=f n 1) #w" entry" #w" entries")
             (if (car (change-log-information frame)) #w"" #w" (disabled)"))))


;;; `get-change-logging-revision-for-slot-on-frame' - we don't store the current
;;; revision number (for a slot) anywhere at the "top level" of the object.  We
;;; have to search through the change-log.  When we find a revision for the
;;; slot, we add 1 to it.

(defun get-change-logging-revision-for-slot-on-frame (frame slot-name class-qualifier?)
  (ensure-frame-change-log-information frame)
  (loop for revision-entry in (cdr (change-log-information frame))
        when (or (and (null class-qualifier?)
                      (eq slot-name (car revision-entry)))
                 (and (listp (car revision-entry))
                      (eq slot-name (caar revision-entry))
                      (eq class-qualifier? (cdar revision-entry))))
          do
            (return-from get-change-logging-revision-for-slot-on-frame
              (incff (cadr revision-entry))))
  (let ((initial-revision initial-change-log-revision-number))
    (slot-value-push
      (change-log-information-entry slot-name class-qualifier? initial-revision)
      (cdr (change-log-information frame)))
    initial-revision))


;;; `Log-kb-change' - adds an entry to the frame change log.  In order to update
;;; the representations (attribute tables), uses change-slot-value, which wants
;;; to reclaim the old value, and therefore wants the new value to be entirely
;;; distinct from the old one.  Rather than making a fresh copy of the entire
;;; frame change log, we hack it by using the old value as the new value, but
;;; putting nil into the slot, so that nothing gets reclaimed when we do the
;;; change-slot-value.  There may be a better way.  -jv, 1/22/07

(defun log-kb-change (frame slot-name qualifier? new-text module-uuid)
  (let* ((new-frame-change-log (frame-change-log frame))
         (new-entry-for-slot
           (make-change-log-entry-for-slot
             slot-name qualifier? 'permanent
             (get-current-frame-edit-timestamp)
             (or (if servicing-workstation?
                     (g2-user-name-for-this-workstation? current-workstation))
                 (get-current-user-name-if-any-case-insensitive)
                 (get-current-user-name))
             (get-change-logging-revision-for-slot-on-frame
               frame slot-name qualifier?)
             '() 'full-text
             new-text
             nil (copy-for-slot-value module-uuid))))
    (setf (frame-change-log frame) nil)
    (slot-value-push new-entry-for-slot new-frame-change-log)
    (change-slot-value frame 'frame-change-log new-frame-change-log)))


;;; `update-change-log-attribute' ... called from EDIT1 and ICON4.  Updates the change
;;; log when appropriate.

(defun update-change-log-attribute (frame slot-description runtime-change-p)
  (ensure-frame-change-log-information frame)
  (let ((uuid-if-logging? (module-uuid-for-frame-if-logging? frame)))
    (cond
      ((null uuid-if-logging?)
       ;; kb-change-logging not enabled in this module; return
       nil)
      ((null (car (change-log-information frame)))
       ;; change-logging specifically disabled on this item
       nil)
      ((not (type-of-slot-if-editable
              (class frame)
              'frame-author-or-authors))
       ;; Authors attribute enablement linked to change log enablement.
       ;; Therefore, no change-logging on this frame; return.
       nil)
      (runtime-change-p
       ;; we consider this case in service of Suggestion HQ-5401481 "possibility
       ;; of having programmatic changes reflected in change-log"; for now, we
       ;; never log runtime changes.  -jv, 1/23/07
       nil)
      (t
       (let* ((pretty-slot-name (pretty-slot-name slot-description))
              (class-qualifier?
                (if (slot-name-needs-qualification-p
                      slot-description (class-description-slot frame))
                    (defining-class slot-description)))
              (most-recent-change-log-entry-text?
                (change-log-entry-slot-value-text
                  (loop for entry in (frame-change-log frame)
                        when (and (eq pretty-slot-name (change-log-entry-slot-name entry))
                                  (eq class-qualifier? (change-log-entry-class-qualifier? entry)))
                          return entry)))
              (newly-installed-text
                (make-text-representation-for-slot-value
                  frame (unique-slot-name slot-description)))
              (log-change-p
                (or (null most-recent-change-log-entry-text?)
                    (not (texts-equal-p most-recent-change-log-entry-text?
                                        newly-installed-text)))))
         (if log-change-p
             (log-kb-change frame pretty-slot-name class-qualifier?
                            newly-installed-text uuid-if-logging?)
             (reclaim-text newly-installed-text)))))))


;; Issues:
;;
;; (a) if text of a text slot that may not have no value is created, do
;;     not show the user "..." as the previous value (e.g., when you
;;     first create a rule)


;;; `make-frame-change-log-table-stub-rows'

(defun make-frame-change-log-table-stub-rows ()
  (slot-value-list
    (slot-value-list
      (make-text-cell
        (convert-text-string-to-text
          (tformat-text-string "Attribute"))
        (parameterized-attribute-description-format))
      (make-text-cell
        (convert-text-string-to-text
          (tformat-text-string "Revision"))
        (parameterized-attribute-value-format))
      (make-text-cell
        (convert-text-string-to-text
          (tformat-text-string "Value"))
        (parameterized-attribute-value-format))
      (make-text-cell
        (convert-text-string-to-text
          (tformat-text-string "Module Version"))
        (parameterized-attribute-value-format))
      (make-text-cell
        (convert-text-string-to-text
          (tformat-text-string "Timestamp"))
        (parameterized-attribute-value-format))
      (make-text-cell
        (convert-text-string-to-text
          (tformat-text-string "Author"))
        (parameterized-attribute-value-format))
      (make-text-cell
        (convert-text-string-to-text
          (tformat-text-string "Tags"))
        (parameterized-attribute-value-format)))))


;;; `make-frame-change-log-table-rows-from-data'

(defun make-frame-change-log-table-rows-from-data (frame row-content-data)
  (loop with saving-parameters-instance? = (get-saving-parameters-for-frame frame)
        for (slot-name class-qualifier? revision text module-uuid? timestamp author tags?) in row-content-data
        as associated-version?
           = (if saving-parameters-instance?
                 (loop for version
                           in (kb-version-information-for-change-logging
                                saving-parameters-instance?)
                       as version-uuid
                          = (change-logging-kb-version-uuid version)
                       when (uuid= module-uuid? version-uuid)
                         return version))
        as version? = (change-logging-kb-version-number associated-version?)
        collect (slot-value-list
                  (make-text-cell  ;; Attribute
                    (make-text-for-cell-identifying-attribute-in-table
                      frame
                      slot-name
                      class-qualifier?
                      nil)
                    (parameterized-attribute-description-format))
                  (make-text-cell  ;; Revision
                    (convert-text-string-to-text
                      (tformat-text-string "~d" revision))
                    (parameterized-attribute-value-format))
                  (make-text-cell  ;; Value
                    (copy-text text)
                    (parameterized-attribute-value-format))
                  (make-text-cell  ;; Module Version
                    (convert-text-string-to-text
                      (tformat-text-string "~a" (or version? "(unknown)")))
                    (parameterized-attribute-value-format))
                  (make-text-cell  ;; Timestamp
                    (convert-text-string-to-text
                      (twith-output-to-text-string
                        (twrite-frame-edit-timestamp timestamp)))
                    (parameterized-attribute-value-format))
                  (make-text-cell  ;; Author
                    (convert-text-string-to-text
                      (tformat-text-string
                        "~(~a~)"
                        (if (evaluation-symbol-p author) author "(unknown)")))
                    (parameterized-attribute-value-format))
                  (make-text-cell  ;; Tags
                    (convert-text-string-to-text
                      (tformat-text-string "~L,&" tags?))
                    (parameterized-attribute-value-format)))
          using slot-value-cons))


;;; `make-frame-change-log-row-content-data'

(defun make-frame-change-log-row-content-data (frame)
  (loop with change-log = (frame-change-log frame)
        for entry in change-log
        collect
        (slot-value-list
          (change-log-entry-slot-name entry)
          (change-log-entry-class-qualifier? entry)
          (change-log-entry-revision entry)
          (change-log-entry-slot-value-text entry)
          (change-log-entry-uuid-of-save entry)
          (change-log-entry-timestamp entry)
          (if (evaluation-symbol-p (change-log-entry-author entry))
              (change-log-entry-author entry))
          (change-log-entry-tags? entry))
          using slot-value-cons))


;;; `make-frame-change-log-table-rows'

(defun make-frame-change-log-table-rows (frame)
  (let ((row-content-data
          (make-frame-change-log-row-content-data frame)))
    (nconc
      (make-frame-change-log-table-stub-rows)
      (make-frame-change-log-table-rows-from-data frame row-content-data))))


;;; `Make-change-log-table' creates an attribute table for frame showing the
;;; change log.

(defun make-change-log-table (frame)
  (let* ((basic-table
          (make-attributes-table
           frame nil
           (parameterized-attribute-table-header-format)
           nil nil
           (if new-g2-classic-ui-p 'none '(class))))
         (additional-rows
           (make-frame-change-log-table-rows frame)))
    ;; spread 1st row across 3 additional columns (w/3 nils):
    (if new-g2-classic-ui-p
        (reclaim-slot-value
         (prog1 (table-rows basic-table)
           (setf (table-rows basic-table) nil)))
      (setf (car (table-rows basic-table))
            (nconc (slot-value-list nil nil nil)
                   (car (table-rows basic-table)))))
    (setf (table-rows basic-table)
          (nconc (table-rows basic-table)
                 additional-rows))
    (reformat-table-in-place basic-table)
    basic-table))




;;;; Change Log Commands


;;; `put-up-change-log-table'

(defun put-up-change-log-table (frame x-in-window y-in-window)
  (let ((table (make-change-log-table frame)))
    (put-table-on-workspace-in-pane table x-in-window y-in-window)
    table))


;;; `view-change-log' UI command

(define-ui-command view-change-log
    (item original-x-in-window original-y-in-window)
  "View the change log for this item"
  (when (and (block-p item)
             (frame-change-log item))
    (put-up-change-log-table
      item original-x-in-window original-y-in-window)))


;;; The ui-command `view-change-log-from-table' is active over the
;;; frame-change-log slot of the table of an item that has change
;;; log entries.

(define-ui-command (view-change-log-from-table :name view-change-log)
    (slot-name item original-x-in-window original-y-in-window)
  "View the change log for this item"
  (when (and (eq slot-name 'frame-change-log)
             (and (block-p item)
                  (frame-change-log item)))
    (put-up-change-log-table
      item original-x-in-window original-y-in-window)))


;;; `flush-change-log-for-item-now'

(defun flush-change-log-for-item-now (item)
  (change-slot-value item 'frame-change-log nil)
  (change-slot-value item 'change-log-information nil))


;;; The ui-command `flush-change-log-from-table' is active over the
;;; frame-change-log slot of the table of an item that has change
;;; log entries.  This should only be available when in package
;;; preparation mode.  (There should be a system procedure that
;;; can do the same at any time.)

(define-ui-command (flush-change-log-from-table :name flush-change-log)
    (slot-name item original-x-in-window original-y-in-window)
  "Flush the change log for this item"
  (when (and (eq slot-name 'frame-change-log)
             package-preparation-mode
             (and (block-p item)
                  (frame-change-log item)))
    (confirm-or-cancel (copy-text-string "Flush the change log for this item?")
                       'flush-change-log-for-item-now
                       (slot-value-list item))))


;;; `g2-flush-change-log-for-item' system procedure

(defun-for-system-procedure g2-flush-change-log-for-item (item)
  (declare (keeps-g2-local-variables-valid t))
  (flush-change-log-for-item-now item))


;;; `flush-change-log-for-entire-kb-now'

(defun flush-change-log-for-entire-kb-now ()
  (loop for class being each subclass of 'block
        do (loop for instance being each strict-class-instance of class
                 do (flush-change-log-for-item-now instance))))

;; TO DO: add long-operation indication that shows that we're busy if this
;; takes a few seconds!


;;; `flush-change-log-for-entire-kb' UI command

(define-ui-command (flush-change-log-for-entire-kb)
    ()
  "Flush the change log for every item in the KB (includes all modules)."
  (when package-preparation-mode
    (confirm-or-cancel (copy-text-string "Flush the change log for the entire KB?")
                       'flush-change-log-for-entire-kb-now)))


;;; `g2-flush-change-log-for-entire-kb' system procedure

(defun-for-system-procedure g2-flush-change-log-for-entire-kb ()
  (declare (keeps-g2-local-variables-valid t))
  (flush-change-log-for-entire-kb-now))




;;;; Programmatic Access to Change Log


;;; `item-has-changes-logged-p' - used by the funcalled-evaluator "with-changes-logged"

(defun-simple item-has-changes-logged-p (item before after author)
  (loop for entry in (frame-change-log item)
        as entry-date = (change-log-entry-timestamp entry)
        as entry-author = (change-log-entry-author entry)
        thereis (and (or (not (evaluation-integer-p before))
                         (<f entry-date before))
                     (or (not (evaluation-integer-p after))
                         (<f after entry-date))
                     (or (not (evaluation-symbol-p author))
                         (eq author entry-author)))))


;;; `change-log-type' type-parameter - defines the structure for programmatic
;;; access to the change-log.  I don't think this actually serves a purpose,
;;; aside from something of internal documentation, for a read only attribute
;;; like change log.  -jv, 1/26/07

(def-type-parameter change-log-type
    (sequence
      (structure ((attribute symbol)
                  (revision integer)
                  (comment text)
                  (tags (sequence))
                  (text-value text)
                  (module-version integer)
                  (timestamp (structure ((year integer)
                                         (month integer)
                                         (date integer)
                                         (hours integer)
                                         (minutes integer))))
                  (author symbol)))))


;;; `get-comment-on-change-log-entry'

(defun get-comment-on-change-log-entry (entry)
  (let ((log? (change-log-entry-log? entry)))
    (if log?
        (copy-evaluation-text log?)
        (make-evaluation-text ""))))


;;; `make-change-log-entry-eval-struct'

(defun make-change-log-entry-eval-struct (entry? item)
  (if (null entry?)
      (allocate-evaluation-structure nil)
      (let* ((saving-parameters? (get-saving-parameters-for-frame item))
             (change-log-entry-author? (change-log-entry-author entry?)))
        (allocate-evaluation-structure
          (eval-list
            'attribute
            (if (change-log-entry-class-qualifier? entry?)
                (intern-unique-slot-name-text-string
                  (make-unique-slot-name-symbol-text-string
                    (change-log-entry-class-qualifier? entry?)
                    (change-log-entry-slot-name entry?)))
                (alias-slot-name-if-necessary (change-log-entry-slot-name entry?) item))
            'revision (change-log-entry-revision entry?)
            'comment (get-comment-on-change-log-entry entry?)
            'tags (allocate-evaluation-sequence
                    (copy-list-using-eval-conses
                      (change-log-entry-tags? entry?)))
            'text-value
            (convert-text-to-text-string
              (change-log-entry-slot-value-text entry?))
            'module-version
            (if saving-parameters?
                (loop for version in (kb-version-information-for-change-logging
                                       saving-parameters?)
                      when (uuid= (change-log-entry-uuid-of-save entry?)
                                  (change-logging-kb-version-uuid version))
                        return (change-logging-kb-version-number version))
                0)
            'timestamp
            (evaluation-structure-for-frame-edit-timestamp
              (change-log-entry-timestamp entry?))
            'author
            (if (evaluation-symbol-p change-log-entry-author?)
                change-log-entry-author?))))))


;;; `frame-change-log-as-sequence-of-structures' returns a sequence of
;;; structures exactly paralleling the output of View Change Log. Cf the
;;; `frame-change-log' slot-value-writer.

(defun frame-change-log-as-sequence-of-structures (frame-change-log item)
  (allocate-evaluation-sequence
    (loop for entry in frame-change-log
          collect
          (make-change-log-entry-eval-struct entry item)
            using eval-cons)))


;;; The `frame-change-log' category evaluator interface.

(define-category-evaluator-interface (frame-change-log :access read)
    (or (sequence) (no-item))
  ((get-form (slot-value frame))
   (frame-change-log-as-sequence-of-structures slot-value frame)))


;;; `make-default-change-logging-identifier'

(defun make-default-change-logging-identifier ()
  (gensym-list 'timestamp (get-current-frame-edit-timestamp)))


;;; `change-log-entry-by-revision?' - looks through the change log, and when
;;; it finds an entry which matches the arguments, jumps out and returns that
;;; entry.  Note, this return value is a "pointer" into the actual slot value.
;;; Callers must not modify or reclaim this value.

(defun change-log-entry-by-revision? (item slot-name revision)
  (loop for entry in (frame-change-log item)
        as entry-slot-name = (alias-slot-name-if-necessary
                               (change-log-entry-slot-name entry) item)
        as entry-revision = (change-log-entry-revision entry)
        when (and (eq entry-slot-name slot-name)
                  (eql entry-revision revision))
          do
            (return-from change-log-entry-by-revision?
              entry)))


;;; `change-log-entry-by-tag?' - just like change-log-entry-by-revision?, but
;;; with tag.  Callers do not own the returned value.

(defun change-log-entry-by-tag? (item slot-name tag)
  (loop for entry in (frame-change-log item)
        as entry-slot-name = (alias-slot-name-if-necessary
                               (change-log-entry-slot-name entry) item)
        as entry-tags? = (change-log-entry-tags? entry)
        when (and (eq entry-slot-name slot-name)
                  (memq tag entry-tags?))
          do
            (return-from change-log-entry-by-tag?
              entry)))


;;; `change-log-entry-by-date?' - like the two above functions, though in this
;;; case, we're not looking for an exact match.  The idea with a timestamp is,
;;; the version "as of" this date: if you went back in time to this date, and
;;; looked at this attribute, what would you see?  It might have been modified
;;; that minute, or it might have been that way for five years; it doesn't
;;; matter.  It's whatever the slot looked like at that time.  If the slot
;;; didn't exist at that time, we return nil.  Otherwise, again, we continue
;;; to own the returned value.  Callers must not munge it.

(defun change-log-entry-by-date? (item slot-name encoded-timestamp)
  (loop for entry in (frame-change-log item)
        as entry-slot-name = (alias-slot-name-if-necessary
                               (change-log-entry-slot-name entry) item)
        as entry-timestamp? = (change-log-entry-timestamp entry)
        when (and (eq slot-name entry-slot-name)
                  (<=f entry-timestamp? encoded-timestamp))
          do
            (return entry)))


;;; `delete-change-log-entry' - deletes an entry from the frame change log.  In
;;; order to update the representations (attribute tables), uses
;;; change-slot-value, which wants to reclaim the old value, and therefore wants
;;; the new value to be entirely distinct from the old one.  Rather than making
;;; a fresh copy of the entire frame change log, we hack it by using the old
;;; value as the new value, but putting nil into the slot, so that nothing gets
;;; reclaimed when we do the change-slot-value.  There may be a better way.
;;; -jv, 1/22/07

(defun delete-change-log-entry (frame entry)
  (let ((new-frame-change-log (frame-change-log frame)))
    (setf (frame-change-log frame) nil)
    (cond
      ((eq entry (car new-frame-change-log))
       (setq new-frame-change-log (cdr new-frame-change-log))
       ;; need to reclaim much more fully!
       (reclaim-slot-value-list entry))
      (t
       (loop for rest on new-frame-change-log
             when (eq entry (cadr rest)) do
                 (setf (cdr rest) (cddr rest)))
       ;; need to reclaim much more fully!
       (reclaim-slot-value-list entry)))
    (change-slot-value frame 'frame-change-log new-frame-change-log)))


;;; `set-comment-on-change-log-entry'

(defun set-comment-on-change-log-entry (entry comment)
  (when (evaluation-text-p (change-log-entry-log? entry))
    (reclaim-evaluation-text (change-log-entry-log? entry)))
  (setf (change-log-entry-log? entry) comment))


;;; `get-change-log-entry'

(defun get-change-log-entry (item slot-name specification)
  (let* ((revision? (cadr (memq 'revision specification)))
         (tag? (cadr (memq 'tag specification)))
         (timestamp? (cadr (memq 'timestamp specification))))
    (cond
      (revision?
       (change-log-entry-by-revision? item slot-name revision?))
      (tag?
       (change-log-entry-by-tag? item slot-name tag?))
      (timestamp?
       (change-log-entry-by-date? item slot-name timestamp?))
      (t
       #+development
       (cerror "Go on, returning no value (nil)"
               "the specification for get-change-log-entry must supply a revision, tag, or date")
       nil))))


;;; `illegal-change-logging-tag-p' - as a first pass, simply disallow NONE.

(defun illegal-change-logging-tag-p (new-tag)
  (memq new-tag '(none)))


;;; `tag-change-log-entry'

(defun tag-change-log-entry (item slot-name identifier new-tag)
  (cond
    ((illegal-change-logging-tag-p new-tag)
     'illegal-tag)
    (t
     (let ((found-entry?
             (get-change-log-entry item slot-name identifier)))
       (cond
         ((null found-entry?)
          'no-such-entry)
         ((memq new-tag (change-log-entry-tags? found-entry?))
          ;; do nothing; should it be an error?  warning?
          found-entry?)
         ((change-log-entry-by-tag? item slot-name new-tag)
          'tag-already-used)
         ((null (change-log-entry-tags? found-entry?))
          (setf (change-log-entry-tags? found-entry?) (slot-value-list new-tag))
          found-entry?)
         (t
          (slot-value-push new-tag (change-log-entry-tags? found-entry?))
          found-entry?))))))


;;; `tag-item-change-log' - tags *each* the logged slots in the item, per the
;;; specification and tag given.  Highly inefficient implementation.  Must be
;;; improved before final release.

(defun tag-item-change-log (item id-as-list new-tag)
  (loop for entry in (cdr (change-log-information item))
        as slot-name = (car entry)
        when (symbolp slot-name) do
            (tag-change-log-entry
              item
              (alias-slot-name-if-necessary slot-name item)
              id-as-list new-tag)))


;;; `tag-all-frames-in-module' - also pretty inefficient.  Is there a way to
;;; iterate over all the frames of a module?  Do I have to iterate over all the
;;; blocks in the kb and do "get-module-block-is-in"?

(defun tag-all-frames-in-module (module-name new-tag id-as-list)
    (loop for item being class-instance of 'block
          when (eq module-name (get-module-block-is-in item)) do
              (tag-item-change-log item id-as-list new-tag)))


;;; `delete-change-log-tag-1'

(defun delete-change-log-tag-1 (found-entry? new-tag)
  (cond
    ((null found-entry?))
    ((null (cdr (change-log-entry-tags? found-entry?)))
     ;; the tag being deleted is the only tag
     (reclaim-slot-value-list (change-log-entry-tags? found-entry?))
     (setf (change-log-entry-tags? found-entry?) nil))
    ((eq new-tag (car (change-log-entry-tags? found-entry?)))
     (let ((cons-to-delete (change-log-entry-tags? found-entry?)))
       (setf (change-log-entry-tags? found-entry?) (cdr (change-log-entry-tags? found-entry?)))
       (reclaim-slot-value-cons cons-to-delete)))
    (t
     (delete-slot-value-element new-tag (change-log-entry-tags? found-entry?))))
  found-entry?)


;;; `delete-change-log-tag'

(defun delete-change-log-tag (item slot-name new-tag error-on-unfound-p)
  (let ((found-entry? (change-log-entry-by-tag? item slot-name new-tag)))
    (if (and error-on-unfound-p (null found-entry?))
        'no-such-entry
        (delete-change-log-tag-1 found-entry? new-tag))))


;;; `revert-change-log-entry'

(defun revert-change-log-entry (item slot-name identifier)
  (let ((found-entry? (get-change-log-entry item slot-name identifier)))
    (when found-entry?
      (change-the-text-of
        item
        (change-log-entry-slot-name found-entry?)
        (convert-text-to-text-string (change-log-entry-slot-value-text found-entry?))))
    found-entry?))


;;; `revert-item-per-change-log' reverts each attribute which is tagged,
;;; according to the id given.

(defun revert-item-per-change-log (item id-as-list)
  (loop with class-description = (class-description (class item))
        for entry in (cdr (change-log-information item))
        as slot-name = (car entry)
        as slot-description? = (and (symbolp slot-name)
                                    (get-slot-description
                                      slot-name
                                      (slot-descriptions class-description)))
        do
    (if slot-description?
        (revert-change-log-entry
          item
          (alias-slot-name-if-necessary slot-name item)
          id-as-list)
        #+development
        (cerror "Ignore it"
                "Cannot revert entry for ~s of ~s; no such slot"
                slot-name item))))


;;; `revert-all-frames-in-module' same issue as tag-all-frames-in-module.  Do we
;;; have to check the module of every block in the kb?

(defun revert-all-frames-in-module (module-name id-as-list)
  (loop for item being class-instance of 'block
        when (eq module-name (get-module-block-is-in item)) do
            (revert-item-per-change-log item id-as-list)))


;;; `set-change-logging-p-on-item'

(defun set-change-logging-p-on-item (frame log-p)
  (let* ((slot-description
           (get-slot-description-of-class-description
             'frame-change-log
             (class-description (class frame)))))
    (with-updates-to-representations
        (frame slot-description)
      (ensure-frame-change-log-information frame)
      (setf (car (change-log-information frame)) log-p))))




;;;; System Procedures


;;; `encode-date-into-edit-timestamp'

(defun encode-date-into-edit-timestamp (seconds minutes hours
                                                date month year)
  (let* ((raw-encoded-ts
           (gensym-encode-unix-time seconds minutes hours
                                    date month year))
         (delta
           (- raw-encoded-ts time-of-frame-edit-base-time))
         (converted-to-minutes
           (/ delta 60)))
    (round converted-to-minutes)))


;;; `edit-timestamp-or-stack-error?'

(defun edit-timestamp-or-stack-error? (timestamp?)
  (when (and timestamp?
             (not (evaluation-structure-p timestamp?)))
    (stack-error
      cached-top-of-stack
      "Timestamp must be structure."))
  (if timestamp?
      (let* ((minutes (evaluation-structure-slot timestamp? 'minutes 0))
             (hours (evaluation-structure-slot timestamp? 'hours 0))
             (date? (evaluation-structure-slot timestamp? 'date))
             (month? (evaluation-structure-slot timestamp? 'month))
             (year? (evaluation-structure-slot timestamp? 'year)))
        (unless (and (fixnump minutes)
                     (<= 0 minutes 59))
          (stack-error
            cached-top-of-stack
            "Minutes must be integer between 0 and 59, inclusive."))
        (unless (and (fixnump hours)
                     (<= 0 hours 23))
          (stack-error
            cached-top-of-stack
            "Hours must be integer between 0 and 23, inclusive."))
        (unless (and (fixnump month?)
                     (<= 1 month? 12))
          (stack-error
            cached-top-of-stack
            "Month must be integer between 1 and 12, inclusive."))
        (unless (and (fixnump year?)
                     (<= 1970 year? 2038))
          (stack-error
            cached-top-of-stack
            "Year must be integer between 1970 and 2038, inclusive."))
        (unless (and (fixnump date?)
                     (valid-date-for-month-p date? month? year?))
          (stack-error
            cached-top-of-stack
            "Date must make sense for given month and year."))
        (encode-date-into-edit-timestamp
          0 ;; seconds
          minutes hours date? month? year?))))


;;; `convert-change-log-identifier-structure-to-list'

(defun convert-change-log-identifier-structure-to-list (identifier allow-empty-p)
  (let* ((revision? (evaluation-structure-slot identifier 'revision))
         (tag? (evaluation-structure-slot identifier 'tag))
         (timestamp? (evaluation-structure-slot identifier 'timestamp)))
    (unless (or allow-empty-p revision? tag? timestamp?)
      (stack-error
        cached-top-of-stack
        "Must supply revision, tag, or timestamp."))
    (when (and revision? tag?)
      (stack-error
        cached-top-of-stack
        "Cannot supply both revision and tag."))
    (when (and revision? timestamp?)
      (stack-error
        cached-top-of-stack
        "Cannot supply both revision and timestamp."))
    ;; Maybe we should allow tag and timestamp together, if we have branches.
    ;; Actually, it's annoying that CVS is missing that feature (the version
    ;; checked in to FOO branch as of <date>).  But in the absence of branches,
    ;; it doesn't make sense. -jv, 1/25/07
    (when (and tag? timestamp?)
      (stack-error
        cached-top-of-stack
        "Cannot supply both tag and timestamp."))
    (when (and revision? (not (evaluation-integer-p revision?)))
      (stack-error
        cached-top-of-stack
        "Revision must be integer."))
    (when (and tag? (not (evaluation-symbol-p tag?)))
      (stack-error
        cached-top-of-stack
        "Tag must be symbol."))
    (cond
      (revision?
       (gensym-list 'revision revision?))
      (tag?
       (gensym-list 'tag tag?))
      (timestamp?
       (let ((evaluated-timestamp? (edit-timestamp-or-stack-error? timestamp?)))
         (if evaluated-timestamp?
             (gensym-list 'timestamp evaluated-timestamp?)
             (stack-error
               cached-top-of-stack
               "Cannot parse timestamp."))))
      (t
       (make-default-change-logging-identifier)))))


;;; `g2-get-change-log-entry'

(defun-for-system-procedure g2-get-change-log-entry (item slot-name id-structure)
  (let* ((specification-as-list
           (convert-change-log-identifier-structure-to-list id-structure t))
         (found-entry?
           (get-change-log-entry item slot-name specification-as-list)))
    (reclaim-gensym-list specification-as-list)
    (make-change-log-entry-eval-struct found-entry? item)))


;;; `g2-diff-change-log-entries'

(defun-for-system-procedure g2-diff-change-log-entries (item slot-name id-struct1 id-struct2)
  (let* ((spec1
           (convert-change-log-identifier-structure-to-list id-struct1 t))
         (spec2
           (convert-change-log-identifier-structure-to-list id-struct2 t))
         (entry1?
           (get-change-log-entry item slot-name spec1))
         (entry2?
           (get-change-log-entry item slot-name spec2))
         (error-symbol? (verify-external-diffing t)))
    (reclaim-gensym-list spec1)
    (reclaim-gensym-list spec2)
    (cond
      (error-symbol?
       (stack-error cached-top-of-stack
                    "Unable to execute external diff: ~s" error-symbol?))
      ((null entry1?)
       (stack-error cached-top-of-stack
                    "No change-log entry found for ~NA." id-struct1))
      ((null entry2?)
       (stack-error cached-top-of-stack
                    "No change-log entry found for ~NA." id-struct2))
      (t
       ;; First we take the "text" and convert it to a text-string; then (in
       ;; external-diff-text-strings), we write the text-string out to a file;
       ;; then we diff them.  It seems, at the very least, we could go directly
       ;; from a "text" to a file, but that functionality doesn't exist.  Maybe
       ;; convert-text-to-text-string could be rewritten in such a way that its
       ;; "output" could be redirected into a file stream rather than into a
       ;; "twith-" buffer; but no time for that now.  -jv, 2/16/07
       (let* ((string1
                (convert-text-to-text-string
                  (change-log-entry-slot-value-text entry1?)))
              (string2
                (convert-text-to-text-string
                  (change-log-entry-slot-value-text entry2?)))
              (result
                (external-diff-text-strings string1 string2)))
         (reclaim-text-string string1)
         (reclaim-text-string string2)
         result)))))



;;; `g2-tag-change-log-entry'

(defun-for-system-procedure g2-tag-change-log-entry (item slot-name identifier new-tag)
  (let* ((specification-as-list
           (convert-change-log-identifier-structure-to-list identifier t))
         (modified-entry-or-error
           (tag-change-log-entry item slot-name specification-as-list new-tag)))
    (reclaim-gensym-list specification-as-list)
    (cond
      ((eq modified-entry-or-error 'illegal-tag)
       (write-stack-error cached-top-of-stack
         (twrite-symbol new-tag t)
         (twrite-string " is an illegal tag for change-logging.")))
      ((eq modified-entry-or-error 'no-such-entry)
       (write-stack-error cached-top-of-stack
         (tformat "No change-log entry found for ~NA." identifier)))
      ((eq modified-entry-or-error 'tag-already-used)
       (write-stack-error cached-top-of-stack
         (tformat "Tag ~s is already in use on ~NF." new-tag item)))
      (t
       (make-change-log-entry-eval-struct modified-entry-or-error item)))))


;;; `g2-delete-change-log-tag'

(defun-for-system-procedure g2-delete-change-log-tag (item slot-name tag-to-delete)
  (let ((modified-entry-or-error
          (delete-change-log-tag item slot-name tag-to-delete t)))
    (cond
      ((eq modified-entry-or-error 'no-such-entry)
       (write-stack-error cached-top-of-stack
         (tformat "No change-log entry found with tag ~NA." tag-to-delete)))
      (t
       (make-change-log-entry-eval-struct modified-entry-or-error item)))))


;;; `g2-delete-change-log-entry' - allows users to permanently remove a given
;;; change log entry while leaving the rest of the log intact.  Users might want
;;; somewhat more far reaching functionality, like "delete all entries from this
;;; revision through this revision", or "delete all entries through this date",
;;; or surely, "delete all entries with this tag, *on all slots*".  But for a
;;; first pass, they have to completely identify a single revision to delete.
;;; Note that after a revision is deleted, the intended behavior is that the
;;; revision numbers do not change, and that revision number is not re-used.
;;; That doesn't work properly if the revision you're deleting is the newest
;;; revision.  -jv, 1/25/07

(defun-for-system-procedure g2-delete-change-log-entry (item slot-name id-structure)
  (let* ((specification-as-list
           (convert-change-log-identifier-structure-to-list id-structure nil))
         (found-entry?
           (get-change-log-entry item slot-name specification-as-list)))
    (reclaim-gensym-list specification-as-list)
    (cond
      ((null found-entry?)
       (make-evaluation-truth-value falsity))
      (t
       (delete-change-log-entry item found-entry?)
       (make-evaluation-truth-value truth)))))


;;; `g2-set-change-log-entry-comment'

(defun-for-system-procedure g2-set-change-log-entry-comment (item slot-name id-structure comment)
  (let* ((specification-as-list
           (convert-change-log-identifier-structure-to-list id-structure nil))
         (found-entry?
           (get-change-log-entry item slot-name specification-as-list)))
    (reclaim-gensym-list specification-as-list)
    (cond
      ((null found-entry?)
       (stack-error cached-top-of-stack
                    "No change-log entry found."))
      (t
       (set-comment-on-change-log-entry found-entry? comment)
       nil))))


;;; `g2-get-change-log-entry-comment'

(defun-for-system-procedure g2-get-change-log-entry-comment (item slot-name id-structure)
  (let* ((specification-as-list
           (convert-change-log-identifier-structure-to-list id-structure nil))
         (found-entry?
           (get-change-log-entry item slot-name specification-as-list)))
    (reclaim-gensym-list specification-as-list)
    (cond
      ((null found-entry?)
       (make-evaluation-text ""))
      (t
       (get-comment-on-change-log-entry found-entry?)))))


;;; `g2-revert-change-log-entry'

(defun-for-system-procedure g2-revert-change-log-entry (item slot-name id-structure)
  (let* ((specification-as-list
           (convert-change-log-identifier-structure-to-list id-structure nil))
         (found-entry? (revert-change-log-entry item slot-name specification-as-list)))
    (reclaim-gensym-list specification-as-list)
    (if (null found-entry?)
        (stack-error cached-top-of-stack
                     "No matching change-log entry found.")
        (make-change-log-entry-eval-struct found-entry? item))))


;;; `g2-tag-module'

(defun-for-system-procedure g2-tag-module (module-name id-structure new-tag)
  (cond
    ((not (module-exists-p module-name))
     (make-evaluation-truth-value falsity))
    (t
     (let ((specification-as-list (convert-change-log-identifier-structure-to-list id-structure t)))
       (tag-all-frames-in-module module-name new-tag specification-as-list)
       (reclaim-gensym-list specification-as-list))
     (make-evaluation-truth-value truth))))


;;; `g2-revert-module'

(defun-for-system-procedure g2-revert-module (module-name id-structure)
  (cond
    ((not (module-exists-p module-name))
     (make-evaluation-truth-value falsity))
    (t
     (let ((specification-as-list (convert-change-log-identifier-structure-to-list id-structure nil)))
       (revert-all-frames-in-module module-name specification-as-list)
       (reclaim-gensym-list specification-as-list))
     (make-evaluation-truth-value truth))))


;;; `g2-disable-change-logging-on-item'

(defun-for-system-procedure g2-disable-change-logging-on-item (frame)
  (set-change-logging-p-on-item frame nil))


;;; `g2-enable-change-logging-on-item'

(defun-for-system-procedure g2-enable-change-logging-on-item (frame)
  (set-change-logging-p-on-item frame t))

  
(defun-for-system-procedure g2-is-gpu-enabled ()
  evaluation-false-value)




;;;; Access via Inspect


(declare-forward-references-to-module queries
  (put-up-verson-control-inspect-workspace function))


;;; `twrite-change-log-entry-as-struct'

(defun twrite-change-log-entry-as-struct (entry item)
  (let ((eval-struct (make-change-log-entry-eval-struct entry item)))
    (prog1
        (tformat "~NA" eval-struct)
      (reclaim-evaluation-structure eval-struct))))


;;; `query-show-logged-changes'

(defun query-show-logged-changes (query run-invisibly-p inspect-command)
  (let* ((item-name (second query))
         (item? (get-instance-with-name-if-any 'block item-name))
         (change-log?
           (and item?
                (frame-change-log-as-sequence-of-structures
                  (frame-change-log item?) item?)))
         (list-of-strings
           (cond
             (run-invisibly-p
              nil)
             ((null item?)
              (gensym-list
                (tformat-text-string "No item named ~s exists." item-name)))
             ((=f 0 (evaluation-sequence-length change-log?))
              (gensym-list
                (tformat-text-string "~s has no change-log." item-name)))
             (t
              (loop for struct being each evaluation-sequence-element of change-log?
                    as string = (tformat-text-string "~NA" struct)
                    collect string using gensym-cons)))))
    (when change-log? (reclaim-evaluation-sequence change-log?))
    (unless run-invisibly-p
      (put-up-verson-control-inspect-workspace list-of-strings inspect-command))))


;;; `query-show-diffs-on-a-workspace'

(defun query-show-diffs-on-a-workspace (query run-invisibly-p inspect-command)
  (let* ((diff-error? (verify-external-diffing t))
         (spec-1 (cadr query))
         (spec-2 (caddr query))
         (slot-name-1 (car (cadar spec-1)))
         (item-name-1 (cadr (cadar spec-1)))
         (item-1? (get-instance-with-name-if-any 'block item-name-1))
         (vc-spec-1 (cadr spec-1))
         (type-of-spec-1 (car vc-spec-1))
         (identifier-1 (cadr vc-spec-1))
         (actual-change-log-entry-1?
           (and item-1?
                (case type-of-spec-1
                  (revision
                   (change-log-entry-by-revision? item-1? slot-name-1 identifier-1))
                  (tag
                   (change-log-entry-by-tag? item-1? slot-name-1 identifier-1))
                  (timestamp
                   (change-log-entry-by-date? item-1? slot-name-1 identifier-1)))))
         (string-1?
           (and actual-change-log-entry-1?
                (convert-text-to-text-string
                  (change-log-entry-slot-value-text actual-change-log-entry-1?))))
         (slot-name-2 (car (cadar spec-2)))
         (item-name-2 (cadr (cadar spec-2)))
         (item-2? (get-instance-with-name-if-any 'block item-name-2))
         (vc-spec-2 (cadr spec-2))
         (type-of-spec-2 (car vc-spec-2))
         (identifier-2 (cadr vc-spec-2))
         (actual-change-log-entry-2?
           (and item-2?
                (case type-of-spec-2
                  (revision
                   (change-log-entry-by-revision? item-2? slot-name-2 identifier-2))
                  (tag
                   (change-log-entry-by-tag? item-2? slot-name-2 identifier-2))
                  (timestamp
                   (change-log-entry-by-date? item-2? slot-name-2 identifier-2)))))
         (string-2?
           (and actual-change-log-entry-2?
                (convert-text-to-text-string
                  (change-log-entry-slot-value-text actual-change-log-entry-2?))))
         (result
           (if (and string-1? string-2? (null diff-error?))
               (external-diff-text-strings string-1? string-2?)
             (allocate-evaluation-structure nil)))

         (output-text?
           (evaluation-structure-slot result 'diff-output))
         (error-text?
           (evaluation-structure-slot result 'diff-error))
         (error-string
           (twith-output-to-text-string
             (cond
               (run-invisibly-p
                nil)
               (diff-error?
                (tformat "Unable to execute external diff: ~s" diff-error?))
               ((null item-1?)
                (tformat "No item named ~s exists." item-name-1))
               ((null actual-change-log-entry-1?)
                (twrite-symbol item-name-1)
                (twrite-string #w" has no change-log entry for ")
                (twrite-symbol slot-name-1)
                (case type-of-spec-1
                  (revision
                   (twrite-string #w" with revision ")
                   (twrite-fixnum identifier-1))
                  (tag
                   (twrite-string #w" with tag ")
                   (twrite-symbol identifier-1))
                  (timestamp
                   (twrite-string #w" as of ")
                   (twrite-frame-edit-timestamp identifier-1))))
               ((null item-2?)
                (tformat "No item named ~s exists." item-name-2))
               ((null actual-change-log-entry-2?)
                (twrite-symbol item-name-2)
                (twrite-string #w" has no change-log entry for ")
                (twrite-symbol slot-name-2)
                (case type-of-spec-2
                  (revision
                   (twrite-string #w" with revision ")
                   (twrite-fixnum identifier-2))
                  (tag
                   (twrite-string #w" with tag ")
                   (twrite-symbol identifier-2))
                  (timestamp
                   (twrite-string #w" as of ")
                   (twrite-frame-edit-timestamp identifier-2))))
               ((evaluation-text-p error-text?)
                (twrite-string
                  (evaluation-text-value error-text?))))))
         (items-to-display
           (if (evaluation-text-p output-text?)
               (if (=f 0 (text-string-length error-string))
                   (gensym-list output-text?)
                   (gensym-list output-text? error-string))
               (gensym-list error-string))))
    (unless run-invisibly-p
      (put-up-verson-control-inspect-workspace
        items-to-display
        inspect-command))))


;;; `query-show-change-log-entry'

(defun query-show-change-log-entry (query run-invisibly-p inspect-command)
  (let* ((slot-name (car (second query)))
         (item-name (cadr (second query)))
         (item? (get-instance-with-name-if-any 'block item-name))
         (vc-spec (third query))
         (type-of-spec (car vc-spec))
         (identifier (cadr vc-spec))
         (actual-change-log-entry?
           (and item?
                (case type-of-spec
                  (revision
                   (change-log-entry-by-revision? item? slot-name identifier))
                  (tag
                   (change-log-entry-by-tag? item? slot-name identifier))
                  (timestamp
                   (change-log-entry-by-date? item? slot-name identifier)))))
         (whipped-up-string
           (twith-output-to-text-string
             (cond
               (run-invisibly-p
                nil)
               ((null item?)
                (tformat "No item named ~s exists." item-name))
               ((null actual-change-log-entry?)
                (twrite-symbol item-name)
                (twrite-string #w" has no change-log entry for ")
                (twrite-symbol slot-name)
                (case type-of-spec
                  (revision
                   (twrite-string #w" with revision ")
                   (twrite-fixnum identifier))
                  (tag
                   (twrite-string #w" with tag ")
                   (twrite-symbol identifier))
                  (timestamp
                   (twrite-string #w" as of ")
                   (twrite-frame-edit-timestamp identifier))))
               (t
                (twrite-change-log-entry-as-struct
                  actual-change-log-entry? item?))))))
    (unless run-invisibly-p
      (put-up-verson-control-inspect-workspace (gensym-list whipped-up-string) inspect-command))))


;;; `query-tag-change-log-entry'

(defun query-tag-change-log-entry (query run-invisibly-p inspect-command)
  (let* ((slot-name (caadr (third (car query))))
         (item-name (cadadr (third (car query))))
         (item? (get-instance-with-name-if-any 'block item-name))
         (vc-spec (or (fifth (car query))
                      (make-default-change-logging-identifier)))
         (new-tag (second (fourth (car query))))
         (modified-entry-or-error
           (if item?
               (tag-change-log-entry item? slot-name vc-spec new-tag)
               'no-such-item))
         (text-for-workspace
           (twith-output-to-text-string
             (cond
               (run-invisibly-p
                nil)
               ((null item?)
                (tformat "No item named ~s exists." item-name))
               ((eq modified-entry-or-error 'illegal-tag)
                (twrite-symbol new-tag t)
                (twrite-string " is an illegal tag for change-logging."))
               ((eq modified-entry-or-error 'no-such-entry)
                (tformat "No change-log entry found for ~NA." vc-spec))
               ((eq modified-entry-or-error 'tag-already-used)
                (tformat "Tag ~s is already in use on ~NF." new-tag item?))
               (t
                (twrite-change-log-entry-as-struct
                  modified-entry-or-error item?))))))
    (unless (fifth (car query))
      (reclaim-gensym-list vc-spec))
    (unless run-invisibly-p
      (put-up-verson-control-inspect-workspace
        (gensym-list text-for-workspace) inspect-command))))


;;; `query-revert-change-log-entry'

(defun query-revert-change-log-entry (query run-invisibly-p inspect-command)
  (let* ((slot-name (car (third (car query))))
         (item-name (cadr (third (car query))))
         (vc-spec (fourth (car query)))
         (item? (get-instance-with-name-if-any 'block item-name))
         (found-entry? (and item? (revert-change-log-entry item? slot-name vc-spec)))
         (text-for-workspace
           (twith-output-to-text-string
             (cond
               (run-invisibly-p
                nil)
               ((null item?)
                (tformat "No item named ~s exists." item-name))
               ((null found-entry?)
                (twrite-string "No matching change-log entry found."))
               (t
                (twrite-change-log-entry-as-struct
                  found-entry? item?))))))
    (unless run-invisibly-p
      (put-up-verson-control-inspect-workspace
        (gensym-list text-for-workspace) inspect-command))))


;;; `query-delete-change-log-entry'

(defun query-delete-change-log-entry (query run-invisibly-p inspect-command)
  (let* ((slot-name (caadar (third (car query))))
         (item-name (car (cdadar (third (car query)))))
         (vc-spec (cadr (third (car query))))
         (item? (get-instance-with-name-if-any 'block item-name))
         (found-entry? (and item? (get-change-log-entry item? slot-name vc-spec)))
         (text-for-workspace
           (twith-output-to-text-string
             (cond
               (run-invisibly-p
                nil)
               ((null item?)
                (tformat "No item named ~s exists." item-name))
               ((null found-entry?)
                (twrite-string "No matching change-log entry found."))
               (t
                (twrite-change-log-entry-as-struct
                  found-entry? item?))))))
    (when found-entry?
      (delete-change-log-entry item? found-entry?))
    (unless run-invisibly-p
      (put-up-verson-control-inspect-workspace
        (gensym-list text-for-workspace) inspect-command))))


;;; `query-tag-all-change-log-entries'

(defun query-tag-all-change-log-entries (query run-invisibly-p inspect-command)
  (let* ((new-tag (second (third (car query))))
         (vc-spec (fifth (car query)))
         (module-name (second (fourth (car query))))
         (module-exists-p (module-exists-p module-name))
         (text-for-workspace
           (twith-output-to-text-string
             (cond
               (run-invisibly-p
                nil)
               ((not module-exists-p)
                (tformat "No module named ~s exists." module-name))
               (t
                (twrite-string "Tagged module."))))))
    (unless (fifth (car query))
      (setq vc-spec (make-default-change-logging-identifier)))
    (tag-all-frames-in-module module-name new-tag vc-spec)
    (unless (fifth (car query))
      (reclaim-gensym-list vc-spec))
    (unless run-invisibly-p
      (put-up-verson-control-inspect-workspace
        (gensym-list text-for-workspace) inspect-command))))


;;; `query-revert-all-change-log-entries'

(defun query-revert-all-change-log-entries (query run-invisibly-p inspect-command)
  (let* ((vc-spec (third (car query)))
         (module-name (second (fourth (car query))))
         (module-exists-p (module-exists-p module-name))
         (text-for-workspace
           (twith-output-to-text-string
             (cond
               (run-invisibly-p
                nil)
               ((not module-exists-p)
                (tformat "No module named ~s exists." module-name))
               (t
                (twrite-string "Reverted module."))))))
    (unless (third (car query))
      (setq vc-spec (make-default-change-logging-identifier)))
    (revert-all-frames-in-module module-name vc-spec)
    (unless (third (car query))
      (reclaim-gensym-list vc-spec))
    (unless run-invisibly-p
      (put-up-verson-control-inspect-workspace
        (gensym-list text-for-workspace) inspect-command))))


;;; `query-enable-change-logging'

(defun query-enable-change-logging (query run-invisibly-p inspect-command)
  (let* ((item-name (third (car query)))
         (item? (get-instance-with-name-if-any 'block item-name))
         (text-for-workspace
           (twith-output-to-text-string
             (cond
               (run-invisibly-p
                nil)
               ((null item?)
                (tformat "No item named ~s exists." item-name))
               (t
                (tformat "Enabled change logging on ~s." item-name))))))
    (when item?
      (set-change-logging-p-on-item item? t))
    (unless run-invisibly-p
      (put-up-verson-control-inspect-workspace
        (gensym-list text-for-workspace) inspect-command))))


;;; `query-disable-change-logging'

(defun query-disable-change-logging (query run-invisibly-p inspect-command)
  (let* ((item-name (third (car query)))
         (item? (get-instance-with-name-if-any 'block item-name))
         (text-for-workspace
           (twith-output-to-text-string
             (cond
               (run-invisibly-p
                nil)
               ((null item?)
                (tformat "No item named ~s exists." item-name))
               (t
                (tformat "Disabled change logging on ~s." item-name))))))
    (when item?
      (set-change-logging-p-on-item item? nil))
    (unless run-invisibly-p
      (put-up-verson-control-inspect-workspace
        (gensym-list text-for-workspace) inspect-command))))


;;; `execute-version-control-query'

(defun execute-version-control-query (query run-invisibly-p inspect-command)
  (case (cadar query)
    (show-logged-changes-on-a-workspace
     (query-show-logged-changes query run-invisibly-p inspect-command))
    (show-change-log-entry-on-a-workspace
     (query-show-change-log-entry query run-invisibly-p inspect-command))
    (show-diffs-on-a-workspace
     (query-show-diffs-on-a-workspace query run-invisibly-p inspect-command))
    (tag-entry
     (query-tag-change-log-entry query run-invisibly-p inspect-command))
    (revert-entry
     (query-revert-change-log-entry query run-invisibly-p inspect-command))
    (delete-entry
     (query-delete-change-log-entry query run-invisibly-p inspect-command))
    (tag-every-attribute
     (query-tag-all-change-log-entries query run-invisibly-p inspect-command))
    (revert-every-attribute
     (query-revert-all-change-log-entries query run-invisibly-p inspect-command))
    (enable-change-logging
     (query-enable-change-logging query run-invisibly-p inspect-command))
    (disable-change-logging
     (query-disable-change-logging query run-invisibly-p inspect-command))
    (t
     #+verbose-change-log-testing
     (warn "unrecognized version-control query: ~s"
           (cadar query)))))


;;; `version-control-query'

(defun version-control-query (inspect-command run-invisibly-p)
  ;; (display-version-control-query inspect-command)
  (execute-version-control-query
    (cdar (box-translation-and-text inspect-command))
    run-invisibly-p inspect-command))


;;; `display-version-control-query'

#+development
(defun display-version-control-query (inspect-command)
  (loop for x in (cdr (box-translation-and-text-function inspect-command))
        when (text-string-p x) do
            (format t "~A " x))
  (format t "~%~s~%" (cdar (box-translation-and-text-function inspect-command))))


;;; `change-log-inspect-test-suite'

#+development
(defvar change-log-inspect-test-suite
  '(
    (#w"show on a workspace the change log entry of the names of modify-dialog-umc-6 as of 1 jan 2007 12:00 a.m."
     (query (version-control show-change-log-entry-on-a-workspace) (names modify-dialog-umc-6) (timestamp 7012860)))
    (#w"show on a workspace the change log entry of the names of modify-dialog-umc-6 with revision 4"
     (query (version-control show-change-log-entry-on-a-workspace) (names modify-dialog-umc-6) (revision 4)))
    (#w"show on a workspace the change log entry of the names of modify-dialog-umc-6 with tag my-tag"
     (query (version-control show-change-log-entry-on-a-workspace) (names modify-dialog-umc-6) (tag my-tag)))
    (#w"show on a workspace the logged changes of modify-dialog-umc-6"
     (query (version-control show-logged-changes-on-a-workspace) modify-dialog-umc-6))
    (#w"version control : delete the change log entry of the names of modify-dialog-umc-6 as of 1 jan 2007 12:00 a.m."
     (query (version-control delete-entry (((the change log entry) (names modify-dialog-umc-6)) (timestamp 7012860)))))
    (#w"version control : delete the change log entry of the names of modify-dialog-umc-6 with revision 3"
     (query (version-control delete-entry (((the change log entry) (names modify-dialog-umc-6)) (revision 3)))))
    (#w"version control : delete the change log entry of the names of modify-dialog-umc-6 with tag jvxyz"
     (query (version-control delete-entry (((the change log entry) (names modify-dialog-umc-6)) (tag jvxyz)))))
    (#w"version control : revert the text of every logged attribute of every item in module edit-versions to the change log entry as of 1 jan 2007 12:00 a.m."
     (query (version-control revert-every-attribute (timestamp 7012860) (revert-module edit-versions))))
    (#w"version control : revert the text of every logged attribute of every item in module edit-versions to the change log entry using tag jvxyz"
     (query (version-control revert-every-attribute (tag jvxyz) (revert-module edit-versions))))
    (#w"version control : revert the text of the names of modify-dialog-umc-6 to the change log entry as of 1 jan 2007 12:00 a.m."
     (query (version-control revert-entry (names modify-dialog-umc-6) (timestamp 7012860))))
    (#w"version control : revert the text of the names of modify-dialog-umc-6 to the change log entry with revision 3 "
     (query (version-control revert-entry (names modify-dialog-umc-6) (revision 3))))
    (#w"version control : revert the text of the names of modify-dialog-umc-6 to the change log entry with tag jvxyz"
     (query (version-control revert-entry (names modify-dialog-umc-6) (tag jvxyz))))
    (#w"version control : tag the change log entry of every logged attribute of every item in module edit-versions as of 1 jan 2007 12:00 a.m. using tag jvxyz"
     (query (version-control tag-every-attribute (tag jvxyz) (tag-module edit-versions) (timestamp 7012860))))
    (#w"version control : tag the change log entry of every logged attribute of every item in module edit-versions using tag jvxyz"
     (query (version-control tag-every-attribute (tag jvxyz) (tag-module edit-versions))))
    (#w"version control : tag the change log entry of the names of modify-dialog-umc-6 as of 1 jan 2007 12:00 a.m. using tag jvxyz"
     (query (version-control tag-entry ((the change log entry) (names modify-dialog-umc-6)) (tag jvxyz) (timestamp 7012860))))
    (#w"version control : tag the change log entry of the names of modify-dialog-umc-6 using tag jvxyz"
     (query (version-control tag-entry ((the change log entry) (names modify-dialog-umc-6)) (tag jvxyz))))
    (#w"version control : tag the change log entry of the names of modify-dialog-umc-6 with revision 3 using tag jvxyz"
     (query (version-control tag-entry ((the change log entry) (names modify-dialog-umc-6)) (tag jvxyz) (revision 3))))
    (#w"show on a workspace the differences between the change log entry of the action of modify-dialog-umc-12 with revision 2 and  the change log entry of the action of modify-dialog-umc-12 with revision 3"
     (query (version-control show-diffs-on-a-workspace)
      (((the change log entry) (action modify-dialog-umc-12)) (revision 2))
      (((the change log entry) (action modify-dialog-umc-12)) (revision 3))))
    (#w"version control : disable change logging on modify-dialog-umc-6"
     (query (version-control disable-change-logging modify-dialog-umc-6)))
    (#w"version control : enable change logging on modify-dialog-umc-6"
     (query (version-control enable-change-logging modify-dialog-umc-6)))))


;;; `test-change-log-inspect-command-parsing'

#+development
(declare-forward-references-to-module attr-export
  (parse-text-string function))

#+development
(defun test-change-log-inspect-command-parsing (inspect-text)
  (let* ((*print-case* :downcase)
         (inspect-command (make-command-frame 'inspect-command inspect-text)))
    (with-phrase-conses
      (multiple-value-bind (parse-result-or-bad-phrase error-string?)
          (parse-text-string inspect-text 'query-command inspect-command)
        (format t "~A~%"
                (or error-string?
                    (copy-tree-using-gensym-conses parse-result-or-bad-phrase)))))
    (values)))


;;; `validate-change-log-inspect-command-parsing'

#+development
(defun validate-change-log-inspect-command-parsing ()
  (let ((inspect-command (make-command-frame 'inspect-command
                                             (caar change-log-inspect-test-suite))))
    (with-phrase-conses
      (loop for (command-string expected-parse-result) in change-log-inspect-test-suite do
        (multiple-value-bind (parse-result-or-bad-phrase error-string?)
            (parse-text-string command-string 'query-command inspect-command)
          (cond
            (error-string?
             (format t "parse error with ~s~%" command-string))
            ((not (equal parse-result-or-bad-phrase expected-parse-result))
             (format t "unexpected-result with ~s~%" command-string))))))))


;;; `validate-executing-change-log-commands'

#+development
(defun validate-executing-change-log-commands ()
  (loop for (nil parse-tree) in change-log-inspect-test-suite do
    (execute-version-control-query (cdr parse-tree) t nil)))

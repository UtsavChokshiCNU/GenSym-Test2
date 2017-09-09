;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module KB-SAVE3

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David and Michael Levin




(declare-forward-references
  ;; To CHANGE-LOG
  (increment-version-for-change-logging-if-appropriate function)

  ;; To ACTIVATE
  (superior-frame function)

  ;; To CONTROLS
  (workstation-for-g2-window?-function function)

  ;; To TRAVERSALS
  (traverse-kb-for-saving function)
  (remove-block-from-module function)

  (return-from-save-to-caller-for-continuation? variable)
  (current-saving-context variable)
  (kb-save-termination-reason? variable)
  (suppress-notification-for-kb-save? variable)
  (terminate-kb-save-stream-error-message? variable)
  (save-kb-state-for-system-procedure-save variable)
  (current-compiled-byte-code-version variable)
  (clear-text-saving-problems-were-encountered-p variable)
  (current-system-rpc-icp-socket? variable)
  (maybe-write-clear-text-diffs function)

  ;; To KB-SAVE4
  (write-clear-text-kb function)

  ;; TO VIEW-G2
  (remove-dialog-info-from-ui-client-interface-dialog-list function))

;;;; Saving Parameters

(def-system-frame saving-parameters kb-save3
  
;  (enable-journalling nil vector-slot system (type yes-or-no))
;  (pathname-format nil vector-slot system (type whole-string?))
;  (number-of-backup-files 2 vector-slot system (type positive-integer))
;  (journalling-status nil lookup-slot system (type journalling-status)
;		      do-not-save not-user-editable)

  
  ;; ;; `Journal-priority', which users know as the attibute `saving-priority',
  ;; ;; controls the priority at which saving happens when the user runs a save
  ;; ;; from the menu (while G2 is running).  (I.e., it doesn't control priority
  ;; ;; when running from the g2-save/g2-save-module/g2-snapshot system
  ;; ;; procedures.)
  ;; ;;
  ;; ;; Prior to G2 4.0 (i.e., in 3.0), this defaulted to 8.  However, we received
  ;; ;; numerous bug reports that indicated gross starvation of the save process
  ;; ;; was occuring and bringing pain to users.  Furthermore, we reasoned that
  ;; ;; this should be at the same priority as things like rules and procedures
  ;; ;; (6), and not as high a priority as display-like things, such as readout
  ;; ;; tables, graphs, etc.  Note that saving as a process doesn't have any
  ;; ;; natural wait states, so it generally starves out anything that's running at
  ;; ;; a priority lower than it.  The current setting makes it hopefully least
  ;; ;; likely to either starve out or be starved out by rules and procedures
  ;; ;; (because it's at their default priority), and that's how we'd like it to
  ;; ;; be.
  ;;
  ;; UPDATE -- Ben and Jim really wanted this to be 8, i.e., background.  So
  ;; be it. (MHD 4/12/94)

  (journal-priority 8 vector-slot system (type priority))

  
  (identifier-of-basis-kb
    nil lookup-slot system
    ; do-not-save  ; See Note (MHD 11/13/96)
    not-user-editable
    (type basis-kb))
  (filename-of-basis-kb
    nil lookup-slot system
    ; do-not-save  ; See Note (MHD 11/13/96)
    not-user-editable
    (type filename-of-basis-kb))

  (kb-file-comment ; the text of the initial ; (comment) lines from the KB
    nil (type free text) lookup-slot system
    ; do-not-save  ; See Note (MHD 11/13/96)
    )

  ;; the folowing slot allows to control kb storing mechanism: when this is "no" you 
  ;; unable store kb when G2 server is running state. When this paramether is "yes" you my try 
  ;; to store your kb chanches. Warning: store kb changes in running state is unsafe and may couse 
  ;; to disrupt kb. Gensym-188

  (enable-kb-online-storing
    nil lookup-slot system (type yes-or-no))

  ;; the following two slots are interdependent: when this is
  ;; "no", the next slot is nil; when "yes", versioning is performed;
  ;; This should really have a dialog associated with changing it, but
  ;; that is deferred for the time being! (MHD 11/17/96)
  (enable-kb-change-logging?
    nil lookup-slot system (type yes-or-no))

  ;; We expose a bit of a "version" concept to users through the read-only slot
  ;; below, which is reset when the above; the contents: a version, which is a
  ;; monotonically increasing integer, a save date, a unique ID (a UUID).  When
  ;; a KB is loaded into memory, the KB's version and its associated save date,
  ;; KB name, and unique ID are the same as they were when the KB was saved.
  ;; (If the KB was never saved with KB change logging enabled, and when KB
  ;; change logging is first enabled, a new version is ginned up, making it
  ;; appear to G2 as though the KB was saved that way.)
  (kb-version-information-for-change-logging
    nil lookup-slot system
    (type kb-version-information-for-change-logging)
    not-user-editable)

  (unsavable-change-protection
    default lookup-slot system (type #-edit-restrictions nil
				     #+edit-restrictions unsavable-change-protection))

  (default-unsavable-change-protection
    (do-not-allow-changes warn)
    lookup-slot system (type #-edit-restrictions nil
			     #+edit-restrictions unsavable-change-protection-specification))

  (save-in-clear-text-by-default
    nil lookup-slot system (type #-clear-text nil #+clear-text yes-or-no))

  (xml-primitive-value-style
    type-is-attribute-of-g2-attribute-and-value-is-contents-of-g2-attribute
    lookup-slot system (type #-clear-text nil #+clear-text xml-primitive-value-style))
  
  (clear-text-history nil        
    (vector-slot) (system) (save)
    (type #-clear-text nil #+clear-text clear-text-history) not-user-editable)

  ;; status attributes
  (current-file-for-module
    nil lookup-slot system (type filename-of-basis-kb) not-user-editable do-not-save)
  (reason-module-is-not-editable
    nil lookup-slot system (type #-edit-restrictions nil
				 #+edit-restrictions status-text-or-none)
    not-user-editable do-not-save no-accessor)
  (module-file-is-read-only
    nil lookup-slot system (type #-edit-restrictions nil
				 #+edit-restrictions readonly-yes-or-no)
    not-user-editable do-not-save)
  (source-code-control-for-module-file
    nil lookup-slot system (type #-use-scc nil #+use-scc source-code-control-name) not-user-editable do-not-save)
  (source-code-control-status-for-module-file
    nil lookup-slot system (type #-use-scc nil #+use-scc status-text-or-none) not-user-editable do-not-save)
  (module-file-is-checked-out-for-writing-by-current-user
    nil lookup-slot system (type #-use-scc nil #+use-scc readonly-yes-or-no) not-user-editable do-not-save)
  (users-currently-having-module-file-checked-out
    nil lookup-slot system (type #-use-scc nil #+use-scc user-name-sequence) not-user-editable do-not-save)
  (version-of-checked-out-module-file
    nil lookup-slot system (type #-use-scc nil #+use-scc status-text-or-none) not-user-editable do-not-save)
  (newest-version-of-module-file
    nil lookup-slot system (type #-use-scc nil #+use-scc status-text-or-none) not-user-editable do-not-save)
  (branch-of-checked-out-module-file
    nil lookup-slot system (type #-use-scc nil #+use-scc status-text-or-none) not-user-editable do-not-save)
  )


;For CVS, each kb in the repository needs a "cvs watch on kb_name"
;  and, for any unmodified files already checked out,
;  a "cvs unedit kb_name" should be done.

;First: are any files in the directory under source code control?
;  CVS: does the file's directory contain "CVS"?
;Second: Is the specified file under source code control?
;        Might as well check if it's binary, and also if its
;        checked-out or locked at the same time.
;  CVS: run "cvs status filename" "cvs editors filename"

(defun run-program-with-string-output (full-command directory initial-timeout? callback?)
  (let* ((unix-command-callback-function callback?)
	 (length 2048)
	 (buffer (obtain-simple-gensym-string length))
	 (number-of-characters
	   (if (eql gensym-environment-variable-success
		    (c-run_program_with_string_output_and_timeout
		      full-command
		      directory
		      buffer
		      (or initial-timeout? most-positive-fixnum)
		      length))
	       (length-of-null-terminated-string buffer)
	       0)))
    (reclaim-text-or-gensym-string full-command)
    (values buffer number-of-characters)))

(defvar current-cvs-command nil)
(defvar cvs-command-initial-timeout (* 2 1000)) ; 2 seconds
(defvar permit-cvs-timeout-dialog-p t)
(defvar cvs-command-timed-out-p nil)

(def-system-variable source-code-control-support-enabled-p kb-save3
  (:funcall get-enable-source-code-control-from-environment-or-command-line))
(defvar source-code-control-is-enabled-by-default nil)

#-use-scc
(defun get-enable-source-code-control-from-environment-or-command-line ()
  (setq source-code-control-support-enabled-p nil))

#+use-scc
(defun get-enable-source-code-control-from-environment-or-command-line ()
  (setq source-code-control-support-enabled-p
	(cond ((or (get-command-line-flag-argument
		     #w"disable-source-code-control" t)
		   (get-gensym-environment-variable
		     #w"G2_DISABLE_SOURCE_CODE_CONTROL"))
	       nil)
	      ((or (get-command-line-flag-argument
		     #w"enable-source-code-control" t)
		   (get-gensym-environment-variable
		     #w"G2_ENABLE_SOURCE_CODE_CONTROL"))
	       t)
	      (t
	       source-code-control-is-enabled-by-default)))
  (when source-code-control-support-enabled-p
    (add-source-code-control-grammar)))

(defvar ms-to-wait-for-cvs nil)

(defun wait-for-cvs (ms-to-wait)
  (setq ms-to-wait-for-cvs ms-to-wait))

(defun disable-cvs-support-and-return-0 ()
  (change-slot-value server-parameters 'source-code-control-support-is-enabled nil)
  (setq cvs-command-timed-out-p t)
  (setq ms-to-wait-for-cvs 0))

(defvar workstations-with-their-stacks-for-timeout-of-source-code-control nil)
(defvar ui-client-interfaces-for-timeout-of-source-code-control nil)

(defun maybe-put-up-scc-timeout-dialog-for-workstation (workstation)
  (unless (assq workstation
		workstations-with-their-stacks-for-timeout-of-source-code-control)
    (gensym-push (gensym-cons workstation
			      (workstation-context-stack workstation))
		 workstations-with-their-stacks-for-timeout-of-source-code-control)
    (for-workstation (workstation)
      (maybe-put-up-scc-timeout-dialog-for-workstation-1))))

(defun maybe-put-up-scc-timeout-dialog-for-workstation-1 ()    
  (enter-dialog
    (tformat-text-string
      "Waiting for the command:~a~%~
         This probably means someone else is currently committing files, ~
         or that the cvs server is unreachable."
      current-cvs-command)
    (copy-constant-wide-string #w"Cancel, and disable source code control") ; OK
    'none
    
    'disable-cvs-support-and-return-0 nil
    nil nil
    
    nil nil nil nil nil nil nil
    t				; strictly modal
    nil))

(defun maybe-put-up-scc-timeout-dialog-for-ui-client-interface (ui-client-interface)
  (unless (assq ui-client-interface ui-client-interfaces-for-timeout-of-source-code-control)
    (gensym-push
      (gensym-cons
	ui-client-interface
	(enter-dialog-for-t2
	  'scc-timeout
	  (eval-list (eval-list 'text (tformat-text-string
					"Waiting for the command:~a~%~
         This probably means someone else is currently committing files, ~
         or that the cvs server is unreachable."
					current-cvs-command)
				'scc-timeout-message)
		     (eval-list 'button (copy-text-string #w"Cancel, and disable source code control")
				'cancel-and-disable-scc))
	  'continuation-for-scc-timeout-dialog-for-ui-client-interface
	  ui-client-interface
	  nil))
      ui-client-interfaces-for-timeout-of-source-code-control)))

(defun continuation-for-scc-timeout-dialog-for-ui-client-interface (dialog-sequence-number client-item)
  (let ((button (leave-dialog-for-t2 dialog-sequence-number)))
    (declare (ignore button))
    (remove-dialog-info-from-ui-client-interface-dialog-list
      dialog-sequence-number
      (ui-client-session-parent-interface client-item))
    (disable-cvs-support-and-return-0)))

(defun leave-scc-timeout-dialog-for-workstation (workstation)
  (let ((a (assq workstation
		 workstations-with-their-stacks-for-timeout-of-source-code-control)))
    (when a
      (setq workstations-with-their-stacks-for-timeout-of-source-code-control
	    (delete-gensym-element
	      a workstations-with-their-stacks-for-timeout-of-source-code-control))
      (let ((stack (cdr a)))
	(reclaim-gensym-cons a)
	(when (loop for current-stack on (workstation-context-stack workstation)
		    thereis (equal stack current-stack))
	  (for-workstation (workstation)
	    (loop while (cdr (workstation-context-stack workstation))
		  until (eq stack (workstation-context-stack workstation))
		  do
	      (abort-current-workstation-context type-of-current-workstation-context))))))))

(defun leave-scc-timeout-dialog-for-ui-client-interface (ui-client-interface)
  (let ((a (assq ui-client-interface ui-client-interfaces-for-timeout-of-source-code-control)))
    (when a
      (setq ui-client-interfaces-for-timeout-of-source-code-control
	    (delete-gensym-element a ui-client-interfaces-for-timeout-of-source-code-control))
      (let ((sequence-number (cdr a)))
	(reclaim-gensym-cons a)
	(leave-dialog-for-t2 sequence-number)))))

(defun leave-all-scc-timeout-dialogs ()
  (loop while workstations-with-their-stacks-for-timeout-of-source-code-control
	do
    (leave-scc-timeout-dialog-for-workstation
      (car (first workstations-with-their-stacks-for-timeout-of-source-code-control))))
  (loop while ui-client-interfaces-for-timeout-of-source-code-control
	do
    (leave-scc-timeout-dialog-for-ui-client-interface
      (car (first ui-client-interfaces-for-timeout-of-source-code-control)))))

;see get-this-window
(defun current-workstation-if-usable-for-dialog (dialog-is-modal-p)
  (let ((workstation? (if servicing-workstation?
			  current-workstation)))
    (when (and workstation?
	       (let ((window (window-for-workstation workstation?)))
		 (or (and (icp-window-p window)
			  (icp-output-port-for-window? window))
		     (and (x11-window-p window)
			  (native-window? window))))
	       (or dialog-is-modal-p
		   (eq type-of-current-workstation-context 'top-level)))
      workstation?)))

(defun get-current-ui-client-interface ()
  (let* ((icp-socket? (or current-system-rpc-icp-socket?
			  current-icp-socket))
	 (interface? (and icp-socket?
			  (enclosing-interface-frame? icp-socket?))))
    (when (and interface?
	       (frame-has-not-been-reprocessed-p
		 interface?
		 (enclosing-interface-frame-serial-number icp-socket?))
	       (frame-of-class-p interface? 'ui-client-interface))
      interface?)))

(defun get-current-workstation-or-ui-client-interface-if-any ()
  (or (current-workstation-if-usable-for-dialog nil)
      (get-current-ui-client-interface)))

(defvar return-to-waiting-for-cvs-p nil)

(defun-allowing-unwind cvs-command-timeout-callback ()
  (unless permit-cvs-timeout-dialog-p
    (setq cvs-command-timed-out-p t)
    (return-from cvs-command-timeout-callback 0))
  (let ((workstation? nil)
	(ui-client-interface? nil))
    (cond ((setq workstation? (current-workstation-if-usable-for-dialog t))
	   (maybe-put-up-scc-timeout-dialog-for-workstation workstation?)
	   (let ((ms-to-wait-for-cvs 100)) ; 100 ms
	     (do-some-workstation-processing workstation?)
	     ms-to-wait-for-cvs))
	  ((setq ui-client-interface? (get-current-ui-client-interface))
	   (maybe-put-up-scc-timeout-dialog-for-ui-client-interface ui-client-interface?)
	   (let ((ms-to-wait-for-cvs 100)) ; 100 ms
	     (do-some-workstation-processing workstation?)
	     ms-to-wait-for-cvs))
	  (t
	   (loop for workstation in workstations-in-service
		 do (maybe-put-up-scc-timeout-dialog-for-workstation workstation))
	   (loop for ui-client-interface being each class-instance of 'ui-client-interface
		 do (maybe-put-up-scc-timeout-dialog-for-ui-client-interface ui-client-interface))
	   (let ((ms-to-wait-for-cvs 100)) ; 100 ms
	     (do-some-workstation-processing nil)
	     ms-to-wait-for-cvs)))))

(defun do-some-workstation-processing (workstation-or-workstation-alist?)
  (declare (ignore workstation-or-workstation-alist?))
  (let ((handle-ui-client-interface-messages-immediately-p t))
    (do-some-icp-processing))
  (propagate-all-workspace-changes-to-image-planes)
  (loop for workstation in workstations-in-service
	do (service-workstation workstation))
  (flush-icp-output-ports))

(defun run-cvs-command-with-string-output (command pathname &optional no-string-p arg1 arg2)
  (when (or (eq g2-operating-system 'vms)
	    (not source-code-control-support-enabled-p))
    (return-from run-cvs-command-with-string-output
      (if no-string-p
	  nil
	  (values nil 0))))
  (let* ((internal-status-of-most-recent-file-operation
	  file-operation-succeeded-code)
	 (pathname-directory-namestring
	  (if pathname
	      (gensym-directory-and-above-namestring pathname)
	      (let ((internal-status-of-most-recent-file-operation
		     file-operation-succeeded-code))
		(g2-stream-get-default-directory))))
	 (pathname-directory-namestring-as-gensym-string
	  (export-text-string pathname-directory-namestring 'namestring-as-gensym-string))
	 (namestring (if (gensym-pathname-p pathname)
			 (gensym-file-namestring pathname)
			 (copy-text-string "")))
	 (current-cvs-command
	  (cond (arg2
		 (tformat-gensym-string "cvs ~a ~a ~a ~a" command arg1 arg2 namestring))
		(arg1
		 (tformat-gensym-string "cvs ~a ~a ~a" command arg1 namestring))
		(t
		 (tformat-gensym-string "cvs ~a ~a" command namestring))))
	 (workstations-with-their-stacks-for-timeout-of-source-code-control nil)
	 (cvs-command-timed-out-p nil))
    (reclaim-text-string namestring)
    (reclaim-text-string pathname-directory-namestring)
    (when send-logbook-messages-to-console-p
      (notify-user-at-console "~a" current-cvs-command))
    (multiple-value-bind (buffer number-of-characters)
	(run-program-with-string-output
	 current-cvs-command
	 pathname-directory-namestring-as-gensym-string
	 cvs-command-initial-timeout
	 #'cvs-command-timeout-callback)
      (reclaim-gensym-string pathname-directory-namestring-as-gensym-string)
      (leave-all-scc-timeout-dialogs)
      (cond (no-string-p
	     (reclaim-simple-gensym-string buffer)
	     (not cvs-command-timed-out-p))
	    (t
	     (values buffer number-of-characters (not cvs-command-timed-out-p)))))))

(defun get-substring-from-buffer
    (buffer number-of-characters start-string end-string result-type require-version-p)
  (let* ((start-pos
	   (search start-string buffer :end2 number-of-characters))
	 (untrimmed-value-start
	   (when start-pos (+f start-pos (length start-string))))
	 (value-start
	   (when untrimmed-value-start
	     (loop for i from untrimmed-value-start
			 below number-of-characters
		   for char = (char buffer i)
		   unless (or (char= char #\space) (char= char #\tab))
		     return i)))
	 (untrimmed-value-end
	   (when value-start
	     (if (characterp end-string)
		 (if (char= end-string #\space)
		     (loop for i from (1+f value-start)
				 below number-of-characters
			   for char = (char buffer i)
			   when (or (char= char #\space) (char= char #\tab)
				    (char= char #\newline))
			     return i)
		     (position end-string buffer
			       :start (1+f value-start)
			       :end number-of-characters))
		 (search end-string buffer
			 :start2 (1+f value-start)
			 :end2 number-of-characters))))
	 (value-end
	   (when untrimmed-value-end
	     (loop for i from (1-f untrimmed-value-end)
			 above value-start
		   for char = (char buffer i)
		   unless (or (char= char #\space) (char= char #\tab)
			      (char= char #\return))
		     return (1+f i)))))
    (when value-end
      (unless (and require-version-p (not (digit-char-p (char buffer value-start))))	
	(case result-type
	  (symbol
	   (intern-gensym-string
	    (gensym-string-substring buffer value-start value-end)))
	  (text-string
	   (twith-output-to-text-string
	     (loop for i from value-start below value-end
		   for char = (char buffer i)
		   do (twrite-char char)))))))))

(defvar local-source-code-control-buffer nil)
(defvar local-source-code-control-number-of-characters nil)
(defvar in-local-source-code-control-scope-p nil)

(defmacro with-source-code-control-for-pathname (pathname &body forms)
  (declare (ignore pathname))
  `(let ((local-source-code-control-buffer nil)
	 (local-source-code-control-number-of-characters nil)
	 (in-local-source-code-control-scope-p t))
     (prog1 (progn ,@forms)
       (when local-source-code-control-buffer
	 (reclaim-simple-gensym-string local-source-code-control-buffer)))))

(defun get-cvs-status (pathname field &optional symbolp)
  (multiple-value-bind (buffer number-of-characters)
      (if (and in-local-source-code-control-scope-p
	       local-source-code-control-buffer)
	  (values local-source-code-control-buffer
		  local-source-code-control-number-of-characters)
	  (run-cvs-command-with-string-output "status" pathname))
    (when (and in-local-source-code-control-scope-p
	       (not local-source-code-control-buffer))
      (setq local-source-code-control-buffer buffer)
      (setq local-source-code-control-number-of-characters number-of-characters))
    (prog1 (when (<f 0 number-of-characters)
	     (if (char= (char buffer 0) #\=)
		 (get-substring-from-buffer
		  buffer number-of-characters
		  (case field
		    (status              "Status:")
		    (checked-out-version "Working revision:")
		    (newest-version      "Repository revision:")
		    (branch              "Sticky Tag:"))
		  (if (eq field 'status) #\newline #\space)
		  (if symbolp 'symbol 'text-string)
		  (or (eq field 'checked-out-version) (eq field 'newest-version)))
		 (let ((substring (twith-output-to-text-string
				    (loop for i from 0 below number-of-characters
					  for char = (char buffer i)
					  do (twrite-char char)))))
		   (notify-user "Error while running \"cvs status ~NP\": " pathname substring)
		   (reclaim-text-string substring)
		   nil)))
      (unless (or in-local-source-code-control-scope-p
		  (null buffer))
	(reclaim-simple-gensym-string buffer)))))

(defun get-cvs-version ()
  (multiple-value-bind (buffer number-of-characters)
      (run-cvs-command-with-string-output "-v" nil)
    (prog1 (when (< 0 number-of-characters)
	     (let* ((version-string-start?
		     (search "1." buffer :end2 number-of-characters))
		    (d1?
		     (when version-string-start?
		       (digit-char-p (char buffer (+f version-string-start? 2)))))
		    (d2?
		     (when version-string-start?
		       (digit-char-p (char buffer (+f version-string-start? 3))))))
	       (when d1?
		 (if d2?
		     (+f (*f d1? 10) d2?)
		     d1?))))
      (reclaim-simple-gensym-string buffer))))

(defun get-cvs-editors (pathname)
  (multiple-value-bind (buffer number-of-characters)
      (run-cvs-command-with-string-output "editors" pathname)
    (prog1 (when (<f 0 number-of-characters)
	     (loop for start-pos = 0 then line-end
		   while start-pos
		   for tab-pos = (position #\tab buffer
					   :start start-pos
					   :end number-of-characters)
		   for name-start = (when tab-pos (1+f tab-pos))
		   for name-end = (when name-start
				    (position #\tab buffer
					      :start name-start
					      :end number-of-characters))
		   for name = (when name-end
				(intern-gensym-string
				  (gensym-string-substring buffer name-start name-end)))
		   for date-start = (when name-end (1+f name-end))
		   for date-end = (when name-end
				    (position #\tab buffer
					      :start date-start
					      :end number-of-characters))
		   for host-start = (when date-end (1+f date-end))
		   for host-end = (when date-end
				    (position #\tab buffer
					      :start host-start
					      :end number-of-characters))
		   for directory-start = (when host-end (1+f host-end))
		   for line-end = (when host-end
				    (position #\newline buffer
					      :start directory-start
					      :end number-of-characters))
		   for directory-end = (when line-end
					 (if (char= (schar buffer (1-f line-end)) #\return)
					     (1-f line-end)
					     line-end))
		   when name
		     collect (gensym-list name
					  (gensym-string-substring
					    buffer (1+f host-end) directory-end))
		       using gensym-cons))
      (when buffer
	(reclaim-simple-gensym-string buffer)))))

(defun reclaim-cvs-editors (editors)
  (loop for editor in editors
	for (user directory) in editor
	do (reclaim-simple-gensym-string directory)
	   (reclaim-gensym-list editor))
  (reclaim-gensym-list editors))

(defun file-is-in-source-code-control-p (pathname)
  (unless (memq (get-cvs-status pathname 'status t) '(nil |Unknown|))
    'cvs))

(defun status-of-currently-checked-out-file (pathname)
  (get-cvs-status pathname 'status))

(defun currently-checked-out-file-is-up-to-date-p (pathname)
  (eq (get-cvs-status pathname 'status t) '|Up-to-date|))

(defun version-of-currently-checked-out-file (pathname)
  (get-cvs-status pathname 'checked-out-version))

(defun newest-version-of-checked-out-file (pathname)
  (get-cvs-status pathname 'newest-version))

(defun branch-of-checked-out-file (pathname)
  (get-cvs-status pathname 'branch))

(defun try-to-get-newest-version-of-file-1 (pathname &optional discard-current-version-if-necessary-p binary-p)
  (case (get-cvs-status pathname 'status t)
    ((|Needs Patch| |Needs Checkout|)
     (if (run-cvs-command-with-string-output "update" pathname t (when binary-p "-kb"))
	 (progn
	   (notify-user "Updated ~NP" pathname)
	   nil)
	 (tformat-text-string "Timed out updating ~NP" pathname)))
    ((|Locally Modified|)
     (when discard-current-version-if-necessary-p
       (gensym-delete-file pathname)
       (notify-user "Deleted ~NP" pathname)
       (try-to-get-newest-version-of-file-1 pathname)))
    ((|Needs Merge|)
     (cond (discard-current-version-if-necessary-p
	    (gensym-delete-file pathname)
	    (notify-user "Deleted ~NP" pathname)
	    (try-to-get-newest-version-of-file-1 pathname))
	   (t
	    (tformat-text-string
	     "Can't update ~NP because it has been edited locally, ~
              and a newer revision has been committed. ~
              Note that it will not be possible to commit ~NP from within G2."
	     pathname pathname))))
    ((|Unknown|)
     ;; The last arg, t, means don't call "cvs add", just do the checking.
     (try-to-put-file-in-source-code-control pathname binary-p "update" t))
    ((nil)
     (when source-code-control-support-enabled-p
       (if (get-cvs-version)
	   (or (try-to-put-file-in-source-code-control pathname binary-p "update" t)
	       (tformat-text-string
		"Can't update ~NP because \"cvs status\" is failing."
		pathname))
	   (tformat-text-string "Can't update ~NP, ~
                                 because cvs is not installed or not in the PATH environment variable"
				pathname))))
    (t
     nil)))

(defun try-to-get-newest-version-of-file (pathname &optional discard-current-version-if-necessary-p binary-p)
  (let ((message? (try-to-get-newest-version-of-file-1
		     pathname discard-current-version-if-necessary-p binary-p)))
    (when message?
      (notify-user-1 message?))))

;when the file's state is |Needs Merge|, what is our error message?

(defun enable-scc-check ()
  (when source-code-control-support-enabled-p
    (let ((version? (get-cvs-version)))
      (cond ((null version?)
	     (notify-user "The source code control features of G2 will not be usable, ~
                           because cvs is not installed or not in the PATH environment variable")
	     t)
	    ((<f version? 10)
	     (notify-user "The source code control features of G2 work best with CVS version 1.10 ~
                           or higher, but version 1.~d was found" version?)
	     nil)))))

(defun non-update-kb-check-1 (pathname top-level-p) 
  (cond (source-code-control-support-enabled-p
	 (when (and top-level-p (null (get-cvs-version)))
	   (return-from non-update-kb-check-1
	     (tformat-text-string
	      "The source code control features of G2 will not be usable, ~
               because cvs is not installed or not in the PATH environment variable")))
	 (let ((error?
		(try-to-put-file-in-source-code-control pathname t "use source code control for" t)))
	   (cond (error?
		  error?)
		 (t
		  (case (get-cvs-status pathname 'status t)
		    ((|Needs Patch| |Needs Checkout|)
		     (tformat-text-string
		      "Note that a newer revision is available for ~NP. ~
                       You might want to load it again using UPDATE BEFORE LOADING"
		      pathname))
		    ((|Needs Merge|)
		     (tformat-text-string
		      "Note that there is now a newer revision for ~NP, ~
                       but it will not be possible to merge it with ~NP"
		      pathname
		      pathname))
		    ((|Up-to-date| |Locally Modified|)
		     (let ((reason? (reason-that-the-current-user-is-not-the-only-editor
				     pathname t)))
		       (when reason?
			 (tformat-text-string
			  "Note that it will not be possible to check out ~NP ~
                           for editing because ~A"
			  pathname reason?)))))))))
	(top-level-p
	 ;;directory in CVS, CVS/Root is remote or exists, but source code control not turned on
	 (let ((error? (try-to-put-file-in-source-code-control pathname t "" t)))
	   (if error? ; maybe this error is why scc is not in use!
	       (progn (reclaim-text-string error?) nil)
	       (progn
		 ;; if we get here, it means that the filesystem says that
		 ;; pathname is in source code control.
		 (tformat-text-string
		  "Note that this file is under source code control. ~
                   If cvs is installed on your machine, you might want ~
                   to turn on source code control support, in the ~
                   server-parameters system table.")))))))

(defun non-update-kb-check (pathname top-level-p) ; called only for the top level module
  (let ((warning? (non-update-kb-check-1 pathname top-level-p)))
    (when warning?
      (notify-user-1 warning?))))

(defparameter status-codes-causing-source-code-control-problems-if-saved-p
  '(; |Locally Modified|
    |Needs Patch| |Needs Checkout| |Needs Merge|))

(defun will-cause-source-code-control-problems-if-saved-p (pathname)
  (not (null (memq (get-cvs-status pathname 'status t)
		   status-codes-causing-source-code-control-problems-if-saved-p))))

;;; will-cause-source-code-control-problems-if-saved-p does not do any CVS operations
(defun-allowing-unwind try-to-put-file-in-source-code-control
    (pathname &optional binary-p operation no-add-p)
  (let ((directory (gensym-pathname-directory pathname)))
    (unless (listp directory) ; I don't think this case ever happens.
      (return-from try-to-put-file-in-source-code-control
	(tformat-text-string
	 "Can't ~A ~NP because its directory is at top level"
	 operation
	 pathname)))
    (let* ((internal-status-of-most-recent-file-operation
	    file-operation-succeeded-code)
	   (cvs-directory
	    (nconc (if directory
		       (copy-list-using-gensym-conses directory)
		       (gensym-list :relative))
		   (gensym-list #w"CVS")))
	   (cvs-root-pathname
	    (gensym-make-pathname :device (gensym-pathname-device pathname)
				  :directory cvs-directory
				  :name #w"Root"))
	   (namestring-for-root (gensym-namestring cvs-root-pathname))
	   (root? (when (g2-stream-file-is-readable-p namestring-for-root)
		    (g2-stream-with-open-stream (input-stream? namestring-for-root)
		      (when input-stream?
			(g2-stream-read-line input-stream?)))))
	   (root-is-local-p
	    (and root?
		 (or (not (position-in-text-string #.%\: root?))
		     (and (<f #.(length ":local:") (lengthw root?))
			  (text-string-equal-given-indices
			   #w":local:" root?
			   0 #.(length ":local:")
			   0 #.(length ":local:"))))))
	   (root-is-local-and-exists-p
	    (and root-is-local-p
		 (g2-stream-file-is-readable-p root?))))
      (reclaim-gensym-list cvs-directory)
      (reclaim-text-string namestring-for-root)
      (cond ((null root?)
	     (prog1 (tformat-text-string
		     "Can't ~A ~NP because its directory is not ~
                      under source code control. ~
                      Use \"cvs checkout\" on its directory first."
		     operation
		     pathname)
	       (reclaim-gensym-pathname cvs-root-pathname)))
	    ((and root-is-local-p (not root-is-local-and-exists-p))
	     (prog1 (tformat-text-string
		     "Can't ~A ~NP because its CVS repository directory, ~A, ~
                      specified by the CVS file ~NP, does not exist."
		     operation
		     pathname
		     root?
		     cvs-root-pathname)
	       (reclaim-text-string root?)
	       (reclaim-gensym-pathname cvs-root-pathname)))
	    (t
	     (reclaim-text-string root?)
	     (reclaim-gensym-pathname cvs-root-pathname)
	     (unless no-add-p
	       (run-cvs-command-with-string-output "add" pathname t
						   (when binary-p "-kb")))
	     nil)))))

(defun try-to-commit-file-1 (pathname message &optional binary-p)
  (when (eq g2-operating-system 'vms)
    (return-from try-to-commit-file-1
      (tformat-text-string
       "Can't commit ~NP because source code control does not run on VMS"
       pathname)))
  (unless source-code-control-support-enabled-p
    (return-from try-to-commit-file-1
      (tformat-text-string
       "Can't commit ~NP because source code control is not enabled"
       pathname)))
  (let ((status (get-cvs-status pathname 'status t)))
    (cond ((null status)
	   (return-from try-to-commit-file-1
	     (let ((version? (get-cvs-version)))
	       (if version?
		   (or (try-to-put-file-in-source-code-control pathname binary-p "commit")
		       (tformat-text-string
			"Can't commit ~NP because \"cvs status\" is failing."
			pathname))
		   (tformat-text-string
		    "Can't commit ~NP because ~
                     cvs is not installed or not in the PATH environment variable"
		    pathname)))))
	  ((eq status '|Unknown|)
	   (let ((error? (try-to-put-file-in-source-code-control pathname binary-p "commit")))
	     (when error?
	       (return-from try-to-commit-file-1 error?))))
	  ((memq status status-codes-causing-source-code-control-problems-if-saved-p)
	   (return-from try-to-commit-file-1
	     (tformat-text-string
	      "Can't commit ~NP because someone else has committed a different version"
	      pathname)))))
  (let* ((temporary-file (write-string-to-temporary-file
			  "g2_commit_log" message))
	 (did-not-time-out-p (run-cvs-command-with-string-output
			      "commit" pathname t "-F" temporary-file)))
    (gensym-delete-file temporary-file)
    (cond (did-not-time-out-p
	   (notify-user "Committed ~NP." pathname)
	   (run-cvs-command-with-string-output "unedit" pathname t)
	   nil)
	  (t
	   (tformat-text-string "Timed out committing ~NP" pathname)))))

(defun try-to-commit-file (pathname message)
  (let ((message? (try-to-commit-file-1 pathname message t)))
    (when message?
      (notify-user-1 message?))))

;if the file is in SCC, it needs to be writable and we need to be the only editor.
;otherwise, it just needs to be writable.

(defun directory-contains-pathname-p (directory pathname)
  (let ((directory-of-pathname
	  (gensym-directory-and-above-namestring pathname)))
    (prog1 (directory-contains-directory-p directory directory-of-pathname)
      (reclaim-text-string directory-of-pathname))))

;if there are no others editing, but we are,
;we should compare pathname's true directory name with
;the editor's true directory pathname.  If they don't match, the current user
;is editing from another directory
(defun get-users-editing-module-file (pathname)
  (loop with editors = (get-cvs-editors pathname)
	with current-user = (get-current-user-name)
	with current-user-in-correct-directory-found-p = nil
	with current-user-but-in-another-directory-found-p = nil
	for (user directory) in editors
	for current-user-editing-from-another-directory-p
	    = (and (eq user current-user)
		   (not (directory-contains-pathname-p directory pathname)))
	for current-user-editing-from-correct-directory-p
	    = (and (eq user current-user)
		   (not current-user-editing-from-another-directory-p))
	when current-user-editing-from-correct-directory-p
	  do (setq current-user-in-correct-directory-found-p t)
	when current-user-editing-from-another-directory-p
	  do (setq current-user-but-in-another-directory-found-p t)
	unless (or current-user-editing-from-correct-directory-p
		   current-user-but-in-another-directory-found-p)
	  collect user into others using slot-value-cons
	finally (reclaim-cvs-editors editors)
		(return (values others
				current-user-editing-from-correct-directory-p
				current-user-but-in-another-directory-found-p))))

(defun reason-that-the-current-user-is-not-the-only-editor (pathname force-check-p)
  (multiple-value-bind (others
			 current-user-editing-from-correct-directory-p
			 current-user-but-in-another-directory-found-p)
      (get-users-editing-module-file pathname)
    (prog1 (cond (others
		  (let ((namestring (gensym-file-namestring pathname)))
		    (prog1 (tformat-text-string "~A is already being edited by ~L,&" namestring others)
		      (reclaim-text-string namestring))))
		 (current-user-but-in-another-directory-found-p
		  (let ((namestring (gensym-file-namestring pathname)))
		    (prog1 (tformat-text-string "~A is already being edited in a different directory" namestring)
		      (reclaim-text-string namestring))))
		 (current-user-editing-from-correct-directory-p
		  nil)
		 (t
		  (unless force-check-p
		    (cond ((ask-user-about-checking-pathname-out-for-editing pathname)
			   (run-cvs-command-with-string-output "edit" pathname t)
			   nil)
			  (t
			   (tformat-text-string "~A does not want to make edits to ~NP"
						(symbol-name-text-string (get-current-user-name))
						pathname))))))
      (reclaim-gensym-list others))))

(defvar result-of-ask-user-about-checking-pathname-out-for-editing nil)
(defvar return-from-ask-user-about-checking-pathname-out-for-editing-p nil)

(defvar workstations-with-their-stacks-for-ask-user-about-checking-pathname-out-for-editing nil)
(defvar ui-client-interfaces-for-ask-user-about-checking-pathname-out-for-editing nil)

(defun ask-user-about-checking-pathname-out-for-editing-for-workstation (workstation question)
  (unless (assq workstation
		workstations-with-their-stacks-for-ask-user-about-checking-pathname-out-for-editing)
    (gensym-push (gensym-cons workstation
			      (workstation-context-stack workstation))
		 workstations-with-their-stacks-for-ask-user-about-checking-pathname-out-for-editing)
    (for-workstation (workstation)
      (ask-user-about-checking-pathname-out-for-editing-for-workstation-1 question))))

(defun ask-user-about-checking-pathname-out-for-editing-for-workstation-1 (question)
  (enter-dialog
    (copy-text-string question)
    (copy-constant-wide-string #w"Yes") (copy-constant-wide-string #w"No")
    'exit-from-ask-user-about-checking-pathname-out-for-editing (slot-value-list t)
    'exit-from-ask-user-about-checking-pathname-out-for-editing (slot-value-list nil)
    (x-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation))
    (y-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation))
    nil nil nil nil nil t))

(defun ask-user-about-checking-pathname-out-for-editing-for-ui-client-interface (ui-client-interface question)
  (unless (assq ui-client-interface
		ui-client-interfaces-for-ask-user-about-checking-pathname-out-for-editing)
    (gensym-push
      (gensym-cons
	ui-client-interface
	(enter-dialog-for-t2
	  'ask-user-about-checking-out-a-file
	  (eval-list (eval-list 'text (copy-text-string question)
				'check-out-for-editing-question)
		     (eval-list 'button (copy-text-string #w"Yes") 'yes)
		     (eval-list 'button (copy-text-string #w"No") 'no))
	  't2-continuation-for-ask-user-about-checking-pathname-out-for-editing
	  ui-client-interface
	  nil))
      ui-client-interfaces-for-ask-user-about-checking-pathname-out-for-editing)))

(defun stop-asking-user-about-checking-pathname-out-for-editing-for-workstation (workstation)
  (let ((a (assq workstation
		 workstations-with-their-stacks-for-ask-user-about-checking-pathname-out-for-editing)))
    (when a
      (setq workstations-with-their-stacks-for-ask-user-about-checking-pathname-out-for-editing
	    (delete-gensym-element
	      a workstations-with-their-stacks-for-ask-user-about-checking-pathname-out-for-editing))
      (let ((stack (cdr a)))
	(reclaim-gensym-cons a)
	(when (loop for current-stack on (workstation-context-stack workstation)
		    thereis (equal stack current-stack))
	  (for-workstation (workstation)
	    (loop while (cdr (workstation-context-stack workstation))
		  until (eq stack (workstation-context-stack workstation))
		  do
	      (abort-current-workstation-context type-of-current-workstation-context))))))))

(defun stop-asking-user-about-checking-pathname-out-for-editing-for-ui-client-interface (ui-client-interface)
  (let ((a (assq ui-client-interface
		 ui-client-interfaces-for-ask-user-about-checking-pathname-out-for-editing)))
    (when a
      (setq ui-client-interfaces-for-ask-user-about-checking-pathname-out-for-editing
	    (delete-gensym-element
	      a ui-client-interfaces-for-ask-user-about-checking-pathname-out-for-editing))
      (let ((sequence-number (cdr a)))
	(reclaim-gensym-cons a)
	(leave-dialog-for-t2 sequence-number)))))

(defun stop-asking-users-about-checking-pathname-out-for-editing ()
  (loop while workstations-with-their-stacks-for-ask-user-about-checking-pathname-out-for-editing
	do
    (stop-asking-user-about-checking-pathname-out-for-editing-for-workstation
      (car (first workstations-with-their-stacks-for-ask-user-about-checking-pathname-out-for-editing))))
  (loop while ui-client-interfaces-for-ask-user-about-checking-pathname-out-for-editing
	do
    (stop-asking-user-about-checking-pathname-out-for-editing-for-ui-client-interface
      (car (first ui-client-interfaces-for-ask-user-about-checking-pathname-out-for-editing)))))

(defun-simple ask-user-about-checking-pathname-out-for-editing (pathname)
  (loop with result-of-ask-user-about-checking-pathname-out-for-editing = nil
	with return-from-ask-user-about-checking-pathname-out-for-editing-p = nil
	with question = (tformat-text-string "Do you want to check out ~NP for editing?" pathname)
	until return-from-ask-user-about-checking-pathname-out-for-editing-p
	do
    (let ((workstation? nil)
	  (ui-client-interface? nil))
      (cond ((setq workstation? (current-workstation-if-usable-for-dialog t))
	     (ask-user-about-checking-pathname-out-for-editing-for-workstation
	       workstation? question))
	    ((setq ui-client-interface? (get-current-ui-client-interface))
	     (ask-user-about-checking-pathname-out-for-editing-for-ui-client-interface
	       ui-client-interface? question))
	    (t
	     (loop for workstation in workstations-in-service
		   do (ask-user-about-checking-pathname-out-for-editing-for-workstation
			workstation question))
	     (loop for ui-client-interface being each class-instance of 'ui-client-interface
		   do (ask-user-about-checking-pathname-out-for-editing-for-ui-client-interface
			ui-client-interface question)))))
    (do-some-workstation-processing
	workstations-with-their-stacks-for-ask-user-about-checking-pathname-out-for-editing)
    (c-uninterruptible-sleep 50)
	finally (reclaim-text-string question)
		(stop-asking-users-about-checking-pathname-out-for-editing)
		(return result-of-ask-user-about-checking-pathname-out-for-editing)))

(defun t2-continuation-for-ask-user-about-checking-pathname-out-for-editing (sequence-number client-item)
  (let ((button (leave-dialog-for-t2 sequence-number)))
    (remove-dialog-info-from-ui-client-interface-dialog-list
      sequence-number
      (ui-client-session-parent-interface client-item))
    (exit-from-ask-user-about-checking-pathname-out-for-editing
      (case button
	(yes t)
	(no nil)))))

(defun exit-from-ask-user-about-checking-pathname-out-for-editing (value)
  (setq result-of-ask-user-about-checking-pathname-out-for-editing value)
  (setq return-from-ask-user-about-checking-pathname-out-for-editing-p t))

(defun do-scc-command-1 (command-symbol default-pathname? &optional log-message-for-commit-after-saving?)
  (let ((operation-name (case command-symbol
			  (scc-update "update")
			  (scc-edit "edit")
			  (scc-unedit "unedit")
			  (scc-revert "revert")
			  (scc-commit "commit"))))
    (when (eq g2-operating-system 'vms)
      (return-from do-scc-command-1
	(tformat-text-string
	 "Can't ~a ~NP because source code control does not run on VMS"
	 operation-name
	 default-pathname?)))
    (let ((scc-type? (and source-code-control-support-enabled-p
			  (file-is-in-source-code-control-p default-pathname?))))
      (unless scc-type?
	(return-from do-scc-command-1
	  (if source-code-control-support-enabled-p
	      (tformat-text-string
	       "Can't perform the source code control operation ~a on ~NP ~
                because it is not under source code control"
	       operation-name
	       default-pathname?)
	      (tformat-text-string
	       "Can't perform the source control operation ~a on ~NP ~
                because source code control is not enabled"
	       operation-name
	       default-pathname?))))
      (case command-symbol
	(scc-update (try-to-get-newest-version-of-file-1 default-pathname? nil))
	(scc-edit   (case scc-type?
		      (cvs
		       (run-cvs-command-with-string-output "edit" default-pathname? t)
		       nil)))
	(scc-unedit (case scc-type?
		      (cvs
		       (run-cvs-command-with-string-output "unedit" default-pathname? t)
		       nil)))
	(scc-revert (try-to-get-newest-version-of-file-1 default-pathname? t))
	(scc-commit (try-to-commit-file-1 default-pathname? log-message-for-commit-after-saving?))))))

(defun do-scc-command (command-symbol default-pathname? &optional log-message-for-commit-after-saving?)
  (let ((error-message? (do-scc-command-1 command-symbol default-pathname?
					  log-message-for-commit-after-saving?)))
    (cond (error-message?
	   (notify-user-1 error-message?)
	   nil)
	  (t
	   (recompute-editability-of-modules)
	   (update-saving-parameters-status-attributes '*)
	   t))))

(defun update-saving-parameters-status-attributes (&optional module?)
  (if (eq module? '*)
      (loop for suite in modules-and-system-tables-a-list
	    as module-information-instance = (first suite)
	    as module-name = (top-level-kb-module? module-information-instance)
	    when module-name
	      do (update-saving-parameters-status-attributes module-name))
      (let ((saving-parameters (get-saving-parameters module?)))
	(when saving-parameters
	  (let* ((internal-status-of-most-recent-file-operation
		   file-operation-succeeded-code)
		 (pathname? (get-true-pathname-of-module-if-any module?))
		 (namestring? (when pathname? (gensym-namestring pathname?))))
	    (with-source-code-control-for-pathname (pathname?)
	      (change-slot-value saving-parameters 'current-file-for-module namestring?)
	      (change-slot-value saving-parameters 'reason-module-is-not-editable
				 (copy-for-slot-value
				   (get-reason-module-is-not-editable module? t)))
	      (change-slot-value saving-parameters 'module-file-is-read-only
				 (not (module-is-writable-p module?)))
	      (change-slot-value saving-parameters 'source-code-control-for-module-file
				 (when namestring?
				   (file-is-in-source-code-control-p pathname?)))
	      (multiple-value-bind (others
				     current-user-editing-from-correct-directory-p
				     current-user-but-in-another-directory-found-p)
		  (when pathname?
		    (get-users-editing-module-file pathname?))
		(when current-user-but-in-another-directory-found-p
		  (slot-value-push (get-current-user-name) others))
		(change-slot-value saving-parameters 'module-file-is-checked-out-for-writing-by-current-user
				   current-user-editing-from-correct-directory-p)
		(change-slot-value saving-parameters 'users-currently-having-module-file-checked-out
				   others))
	      (change-slot-value saving-parameters 'source-code-control-status-for-module-file
				 (when pathname?
				   (status-of-currently-checked-out-file pathname?)))
	      (change-slot-value saving-parameters 'version-of-checked-out-module-file
				 (when pathname?
				   (version-of-currently-checked-out-file pathname?)))
	      (change-slot-value saving-parameters 'newest-version-of-module-file
				 (when pathname?
				   (newest-version-of-checked-out-file pathname?)))
	      (change-slot-value saving-parameters 'branch-of-checked-out-module-file
				 (when pathname?
				   (branch-of-checked-out-file pathname?)))))))))

(defun-for-system-procedure g2-update-saving-parameters-status-attributes ()
  (declare (values)
	   (keeps-g2-local-variables-valid nil))
  (update-saving-parameters-status-attributes '*))


(def-slot-value-writer status-text-or-none (value)
  (twrite (or value #w"none")))

(define-category-evaluator-interface (status-text-or-none
				       :access read)
    (or text (no-item))
  ((get-form (slot-value))
   slot-value))

(def-slot-value-writer source-code-control-name (value)
  (twrite (or value #w"none")))

(define-category-evaluator-interface (source-code-control-name
				       :access read)
    (or symbol (no-item))
  ((get-form (slot-value))
   slot-value))

(def-slot-value-writer user-name-sequence (value)
  (if (consp value)
      (loop for len = (length value)
	    for user in value
	    for firstp = t then nil
	    for i from 1
	    for lastp = (=f i len)
	    do (unless firstp
		 (twrite
		   (cond ((=f len 2) #w" and ")
			 (lastp #w", and ")
			 (t #w", "))))
	       (twrite (stringw user)))
      (twrite #w"none")))

(define-category-evaluator-interface (user-name-sequence
				       :access read)
    (or (sequence) (no-item))
  ((get-form (slot-value))
   slot-value))

(def-slot-value-writer readonly-yes-or-no (yes-or-no)
  (twrite-string (if yes-or-no "yes" "no")))

(define-category-evaluator-interface (readonly-yes-or-no
				       :access read)
    truth-value
  ((get-form (slot-value))
   (make-evaluation-boolean-value slot-value)))


;; Note: the slots identifier-of-basis-kb and filename-of-basis-kb were never
;; saved in a KB, and the new slot kb-file-comment had no history
;; but should work the same.  The old behavior was OK for loading and saving
;; modules in the usual way, but it did not allow these values to persist across
;; ALL- type saves or across snapshot and warmboot.  This causes a
;; disappointment for a user who expects there to be no difference between
;; saving his module hierarchy, and saving an ALL- file, loading it, and then
;; saving the his module hierarchy.  Similar for snapshot/warmboot scenarios.
;; In the do-not-save scenario, the difference would be that source code control
;; comments would be lost (high likelyhood of being noticed by users of that
;; feature) as well as the filename-of-basis-kb information (less often but
;; sometimes used) and the identifier-of-basis-kb information (never used at
;; present).  When a KB's installed system table is loaded, it's OK for this
;; information to be bashed by the new values determined by read-kb, and that's
;; what happens as always before.  However, now when a system table is restored
;; that is just a module's data in a KB, it will retain the original information
;; across saves, i.e., across snapshot and ALL- type saves.  Note that an
;; alternative might be to have a more complicated save policy for slots, e.g.,
;; a save-only-in-snapshot-and-all-type-saves; not now.  (MHD 11/13/96)

;; The commented out slots will not be used until backup is implemented.


(def-substitute-for-old-class journal-and-backup-parameters saving-parameters 210)

(def-absent-slot-putter enable-journalling (saving-parameters-frame value)
  (declare (ignore saving-parameters-frame value)))

(def-absent-slot-putter pathname-format (saving-parameters-frame value)
  (declare (ignore saving-parameters-frame value)))

(def-absent-slot-putter number-of-backup-files (saving-parameters-frame value)
  (declare (ignore saving-parameters-frame value)))

(def-absent-slot-putter journalling-status (saving-parameters-frame value)
  (declare (ignore saving-parameters-frame value)))

(define-slot-alias default-priority-for-runtime-saving journal-priority)



(defun get-saving-parameters (module?)
  (if module?
      (loop for frame in (find-system-table-suite-with-module-assignment module?)
	    when (of-class-p frame 'saving-parameters)
	      return frame)
      saving-parameters))

(def-slot-value-writer clear-text-history (slot-value)
  (cond ((or (not (fixnump slot-value))
	     (=f slot-value 0))
	 (twrite #w"none"))
	(t
	 (when (/=f 0 slot-value)
	   (twrite #w"loaded from clear text")
	   (let ((differences (get-kb-has-been-loaded-from-clear-text-with-differences slot-value)))
	     (when differences
	       (tformat #w", with the following checksum problems: ~(~L,A~)" differences)
	       (reclaim-gensym-list differences)))))))

(defmacro kb-clear-text-history (&optional module)
  `(clear-text-history (get-saving-parameters ,module)))

(defun get-kb-clear-text-history (module currentp)
  (or (let ((frame? (cond (module
			   (get-saving-parameters module))
			  (currentp
			   saving-parameters)
			  (t
			   nil))))
	(when frame?
	  (or (clear-text-history frame?) 0)))
      (loop with bits = 0
	    for suite in modules-and-system-tables-a-list
	    do (loop for frame in suite
		     when (of-class-p frame 'saving-parameters)
		       do (setf bits (logiorf
				       bits
				       (or (clear-text-history frame) 0))))
	    finally (return bits))))

(defmacro set-kb-has-been-loaded-from-clear-text (&optional module)
  `(let ((frame (get-saving-parameters ,module)))
     (setf (clear-text-history frame)
	   (logiorf 1 (or (clear-text-history frame) 0)))))

(defmacro kb-has-been-loaded-from-clear-text (&optional module)
  `(/=f 0 (logandf 1 (get-kb-clear-text-history ,module nil))))

(defun get-kb-has-been-loaded-from-clear-text-with-differences (module?)
  (loop with bits = (if (fixnump module?)
			module?
			(get-kb-clear-text-history module? nil))
	for mask in '(2 4 8 16)
	for name in '(attribute-name uuid value text)
	when (/=f 0 (logandf mask bits))
	  collect name using gensym-cons))

(defmacro set-kb-has-been-loaded-from-clear-text-with-differences (module? differences)
  `(let ((frame (get-saving-parameters ,module?)))
     (when frame
       (loop with bits = (or (clear-text-history frame) 0)
	     for mask in '(1 2 4 8 16)
	     for name in '(t attribute-name uuid value text)
	     when (or (eq name t) (memq name ,differences))
	       do (setq bits (logiorf mask bits))
	     finally (setf (clear-text-history frame) bits)))))

(defun note-modification-of-module-for-clear-text (module1? module2?)
  (setq module1? (cond ((framep module1?)
			(get-module-block-is-in module1?))
		       ((symbolp module1?)
			module1?)
		       (t
			nil)))
  (when module1?
    (setq module2? (cond ((framep module2?)
			  (get-module-block-is-in module2?))
			 ((symbolp module2?)
			  module2?)
			 (t
			  nil)))
    (let* ((debugging-parameters1 (get-saving-parameters module1?))
	   (bits-from-module2
	     (get-kb-clear-text-history module2? nil)))
      (when debugging-parameters1
	(setf (clear-text-history debugging-parameters1)
	      (logiorf (or (clear-text-history debugging-parameters1) 0)
		       bits-from-module2))
	t))))

(def-slot-value-writer xml-primitive-value-style (value)
  (twrite (case value
	    (type-is-sub-element-of-g2-attribute-and-value-is-attribute-of-type
	     "type is sub element of g2 attribute and value is attribute of type")
	    (type-is-sub-element-of-g2-attribute-and-value-is-contents-of-type
	     "type is sub element of g2 attribute and value is contents of type")
	    (type-is-attribute-of-g2-attribute-and-value-is-contents-of-g2-attribute
	     "type is attribute of g2 attribute and value is contents of g2 attribute")
	    (t
	     ""))))

(def-slot-value-compiler xml-primitive-value-style (parse-result)
  parse-result)

(add-grammar-rules
  `((xml-primitive-value-style type-is-sub-element-of-g2-attribute-and-value-is-attribute-of-type)
    (xml-primitive-value-style type-is-sub-element-of-g2-attribute-and-value-is-contents-of-type)
    (xml-primitive-value-style type-is-attribute-of-g2-attribute-and-value-is-contents-of-g2-attribute)

    (type-is-sub-element-of-g2-attribute-and-value-is-attribute-of-type
      ('type 'is 'sub 'element 'of 'g2 'attribute 'and 'value 'is 'attribute 'of 'type)
      type-is-sub-element-of-g2-attribute-and-value-is-attribute-of-type)

    (type-is-sub-element-of-g2-attribute-and-value-is-contents-of-type
      ('type 'is 'sub 'element 'of 'g2 'attribute 'and 'value 'is 'contents 'of 'type)
      type-is-sub-element-of-g2-attribute-and-value-is-contents-of-type)

    (type-is-attribute-of-g2-attribute-and-value-is-contents-of-g2-attribute
      ('type 'is 'attribute 'of 'g2 'attribute 'and 'value 'is 'contents 'of 'g2 'attribute)
      type-is-attribute-of-g2-attribute-and-value-is-contents-of-g2-attribute)
    ))

(define-category-evaluator-interface (xml-primitive-value-style
				       :access read-write)
    (member type-is-sub-element-of-g2-attribute-and-value-is-attribute-of-type
	    type-is-sub-element-of-g2-attribute-and-value-is-contents-of-type
	    type-is-attribute-of-g2-attribute-and-value-is-contents-of-g2-attribute)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))



(add-grammar-rules
  '((unsavable-change-protection-specification
     (unsavable-change-protection-allow-change-specification '\,
      unsavable-change-protection-warning-specification)
     (1 3))
    (unsavable-change-protection-allow-change-specification
     ('allow 'changes) allow-changes)
    (unsavable-change-protection-allow-change-specification
     ('do 'not 'allow 'changes) do-not-allow-changes)
    (unsavable-change-protection-warning-specification
     ('warn 'when 'edit 'attempted) warn)
    (unsavable-change-protection-warning-specification
     ('do 'not 'warn 'when 'edit 'attempted) do-not-warn)))

(add-grammar-rules
  '((unsavable-change-protection
    'default)
    (unsavable-change-protection
     unsavable-change-protection-specification)))

(def-slot-value-writer unsavable-change-protection-specification (value)
  (twrite (if (memq 'allow-changes value)
	      "allow changes"
	      "do not allow changes"))
  (twrite ", ")
  (twrite (if (memq 'warn value)
	      "warn when edit attempted"
	      "do not warn when edit attempted")))

(def-slot-value-writer unsavable-change-protection (value frame)
  (if (consp value)
      (write-unsavable-change-protection-specification-from-slot value frame)
      (twrite "default")))

(def-slot-value-compiler unsavable-change-protection-specification (parse-result)
  parse-result)

(def-slot-value-compiler unsavable-change-protection (parse-result)
  parse-result)

(define-category-evaluator-interface (unsavable-change-protection-specification
				       :access read-write)
    (structure unsavable-change-protection-specification
	       ((allow-changes truth-value)
		(warn truth-value))
	       (and allow-changes warn))
  ((set-form (evaluation-value))
   (with-structure (evaluation-value unsavable-change-protection-specification)
     (phrase-list (if (evaluation-boolean-is-true-p allow-changes)
		      'allow-changes
		      'do-not-allow-changes)
		  (if (evaluation-boolean-is-true-p warn)
		      'warn
		      'do-not-warn))))
  ((get-form (slot-value))
   (with-new-structure (unsavable-change-protection-specification)
     (setf allow-changes (make-evaluation-boolean-value (memq 'allow-changes slot-value)))
     (setf warn (make-evaluation-boolean-value (memq 'do-not-warn slot-value))))))

(define-category-evaluator-interface (unsavable-change-protection
				       :access read-write)
    (or (no-item)
	(named unsavable-change-protection-specification))
  ((set-form (evaluation-value))
   (block safe-category-setter-calling-block
     (if evaluation-value
	 (call-category-setter-safely 'unsavable-change-protection-specification
				      evaluation-value)
	 'default)))
  ((get-form (slot-value))
   (if (eq slot-value 'default)
       nil
       (call-category-getter 'unsavable-change-protection-specification
			     slot-value nil nil))))

(defun-simple get-unsavable-change-protection (module)
  (let ((module-saving-parameters? (get-saving-parameters module)))
    (if (null module-saving-parameters?)
	(default-unsavable-change-protection (get-saving-parameters nil))
	(let ((value (unsavable-change-protection (get-saving-parameters module))))
	  (if (eq value 'default) 
	      (default-unsavable-change-protection (get-saving-parameters nil))
	      value)))))

(defun-simple warn-on-unsavable-change-p (module)
  (not (null (memq 'warn (get-unsavable-change-protection module)))))

(defun-simple allow-unsavable-change-p (module)
  (not (null (memq 'allow-changes (get-unsavable-change-protection module)))))


;(defun enable-journalling-function (journal-parameters-frame)
;  (enable-journalling journal-parameters-frame))

(def-system-variable all-permanently-changed-things-are-marked kb-save3 nil)

(def-slot-value-writer journalling-status (value)
  (declare (ignore value))
  (twrite
    (if all-permanently-changed-things-are-marked
	"ok to write backup or journal"
	"cannot write backup or journal until after a kb is saved")))

(def-slot-value-writer basis-kb (value)
  (twrite (or value "none")))

(define-category-evaluator-interface (basis-kb
				       :access read)
    (or (no-item) text)
  ((get-form (slot-value))
   (if slot-value
       (copy-evaluation-value slot-value)
       'none)))




(def-slot-value-writer filename-of-basis-kb (value)
  (twrite (or value "none")))

(define-category-evaluator-interface (file-name-of-basis-kb
				       :access read)
    (or (no-item) text)
  ((get-form (slot-value))
   (if slot-value
       (copy-evaluation-value slot-value)
       'none)))




;;; `change-all-permanently-changed-things-are-marked' must be used to mutate
;;; this system-variable.  The value is set true for a number of reasons, but
;;; only when journalling is enabled.  However, enabling journalling does not of
;;; itself set it true.  Its value is displayed as journalling-status in
;;; saving-parameters, and this is maintained.

(defun change-all-permanently-changed-things-are-marked (logical-value)
  (let ((modified-value
	  (and logical-value 
	       ; (enable-journalling saving-parameters)
	       )))
    (when (neq modified-value all-permanently-changed-things-are-marked)
      (setq all-permanently-changed-things-are-marked logical-value)
;      (update-representations-of-slot-value saving-parameters
;					    'journalling-status)

      )))




(def-class-method install-system-table (saving-parameters)
;  ;; I fixed this to obey new constraints on system tables, even though
;  ;; this code is currently commented out, by just putting the when around
;  ;; the old code with global side effects.  ML should review! (MHD 10/15/91)
;  (if (enable-journalling saving-parameters)
;      (change-all-permanently-changed-things-are-marked nil))
;  (unless reading-kb-p
;    (setq noting-changes-to-kb-p (enable-journalling saving-parameters)))
  )


(def-class-method deinstall-system-table (saving-parameters))




;(def-slot-putter enable-journalling (saving-parameters value)
;  (setf (enable-journalling saving-parameters) value)
;
;  ;; I fixed this to obey new constraints on system tables, even though
;  ;; this code is currently commented out, by just putting the when around
;  ;; the old code with global side effects.  ML should review! (MHD 10/15/91)
;  (when (system-table-installed-p saving-parameters)
;    (if (null value)
;	(change-all-permanently-changed-things-are-marked nil))
;    (unless reading-kb-p
;      (setq noting-changes-to-kb-p value)))
;
;  value)

;; Consider enabling journalling when it is known that no changes to the kb have
;; been made since a load. Is there a way to know this?

(defun restore-backup-journaling-parameters-to-default-values ()
  (setq noting-changes-to-kb-p nil)
  (setq all-permanently-changed-things-are-marked nil))





;;;; Documentation for Frame Flags

;;; block-permanently-changed is set upon creation of any block by any means
;;; except for reading a kb. It is also set by any change to the savable slots
;;; of the block including those slots savable by special means. It is cleared
;;; only upon writing the entire kb (not a backup or runtime-data-only). It is
;;; maintained only if noting-changes-to-kb-p is true. If this global variable
;;; is nil even momentarily (which it is if the user choice "enable journalling"
;;; is turned off, then it is not considered reliable until either a kb-load or
;;; a complete save has occurred. See
;;; change-all-permanently-changed-things-are-marked, and its callers.

;;; block-has-been-written is cleared for all blocks at the start of any kind of
;;; save, including backup (but not including journalling), and is set during
;;; the process of saving as follows. Note that its semantics are a bit more
;;; than the name implies. (1) For any frame other than a definition: the flag
;;; indicates either that the block has been written, or that it would have been
;;; written except that (1.1) (not (has-slot-values-to-save-p block)). This test
;;; is used for (user defined) attributes and connection frames only, or (1.2)
;;; for a backup, the block has been traversed, but needs not be written because
;;; there are no changes to it. (2): For definitions, the frame is NOT marked
;;; during the definition writing phase of the save, even though the frame is
;;; written. Later, the definition will be traversed as it is encountered in the
;;; ws hierarchy, and it will be marked and its inferiors traversed at this
;;; time.

;;; In any case, set-block-has-been-written is done when the inferiors of a
;;; block are traversed, and therefore this needs not be done again. All the
;;; interesting code for this is in continue-current-kb-save-or-backup, and
;;; note-change-to-block-macro.

;;; block-has-been-referenced is cleared when starting to save. It is set when
;;; the block is referenced (by write-reference-to-frame), and by
;;; continue-current-kb-save-or-backup which are the only callers of
;;; write-frame-for-kb for a block.

;;; block-existed-at-start-of-save is set for every block at the beginning of
;;; any kind of save, and is never cleared. Its purpose is to identify blocks
;;; created since the checkpoint of a save and therefore not part of the save by
;;; its absence.




;;;; Uses of Frame Flags and System State in Combination

;;; Criteria For Writing Out A Block:

;;; (1a) KB-SAVE case: write only permanent blocks.
;;; (1b) KB-SAVE-WITH-RUNTIME-DATA case: write permanent and transient blocks
;;; (1c) RUNTIME-DATA-ONLY case: write permanent and transient blocks, but only the
;;;      changeable aspect of them. (Not completely implemented.)
;;; (1d) BACKUP case: write permanent blocks for which block-permanently-changed-p,
;;;      and all transient blocks.
;;; (2) In all cases, block-existed-at-start-of-save-p and not
;;;     block-referenced-in-current-save-p.

;;; Note the macro collectable-block-p which identifies either permanent blocks
;;; or both permanent and transient blocks acoording to (save-runtime-data?
;;; current-kb-save).


;;; Interrupts While Saving:

;;; Throughout the temporal extent of an interruptible save,
;;; noting-changes-to-kb-p is true even if it otherwise would not be. This
;;; causes the noting changes and noting deletions functions (4 in all) to write
;;; a block if it meets the above criteria.

;;; If all-permanently-changed-things-are-marked, then the block is queued on
;;; items-deleted-since-load-or-save. This is not cleared until a load or save
;;; has occurred. (This condition applies only when backups and journals are
;;; enabled.)


;;; Most of the above documentation holds, more or less, for connection
;;; structures as well as blocks. But they have their own set of frame flags.





;;;; Saving File Progress Display Updating


;;; `Update-file-progress-display-status' updates the status attribute of the
;;; file progress display in current-kb-save per the status arg, and also
;;; updates the line count (amount-written) attribute per the number of KB lines
;;; so far recorded in current-kb-save.

(defun-void update-file-progress-display-status (status)
  (let ((display? (kb-transfer-kb-file-progress-display? current-kb-save)))
    (when display?
      (setf (fixnum-time-of-last-file-progress-display-update display?)
	    (get-fixnum-time))
      (change-slot-value
	display? 'progress-through-file 
	(number-of-kb-lines-so-far current-kb-save))
      (change-slot-value display? 'status-of-file-progress? status)
      (note-update-to-file-progress display?)
      (unless stack-of-slot-value-changes ; See Note A
	(force-process-drawing)))))

;; Note A: Don't force in obscure case where stack-of-slot-value-changes is
;; non-nil, since it can produce turds, as explained under "Note A" under
;; update-text-cell.  This measure is taken for the saving case only (i.e., not
;; for update-file-progress-display, used for loading), since only saving
;; happens while running and potentially in the middle of updating a table,
;; subjecting it to the obscure turding bug. (MHD 7/9/99)



;;;; Kb-save and Backup


;;; `Save-kb' is the single function which accomplishes all kb saving and
;;; backup.  Its behavior is modified by several context files. The first
;;; argument is a gensym-pathname. The second argument is a type of file. This
;;; provides a value for (type-of-kb-save current-saving-context), except if it
;;; is OK-KB-SAVE, which is a special case whose meaning is explained below.

;;; Save-kb is a continuable function when G2 is running, otherwise it executes
;;; without interrupts. If G2 is paused or reset while running and saving, the
;;; save completes without interrupts.  When it executes while running, time
;;; slices are obtained by scheduling immediate tasks with a priority taken from
;;; the `journal-priority' slot of `saving-parameters'.

;;; [OUT OF DATE!  REVISE! -mhd, 9/16/94]
;;;
;;; Start-kb-save-or-backup starts the save, and calls or schedules
;;; start-kb-save-or-backup. At this point, the saving-context is yet to be
;;; located. The point of snapshot has not actually been reached until the
;;; execution of start-kb-save-or-backup.

;;; `Start-kb-save-or-backup' calls or schedules
;;; continue-current-kb-save-or-backup. From here on, an interruptible save is
;;; capable of writing frames out of order on an interrupt basis.

;;; `Continue-current-kb-save-or-backup' either loops until all frames have been
;;; written, or continues itself until this has happened. Finally,
;;; finish-current-kb-save-or-backup is called or scheduled. It closes the file
;;; and calls `terminate-kb-save-or-backup' (without interruption). The latter
;;; cleans up the environment.

;;; If an error has occurred while saving, or if the save is to be terminated
;;; externally, this is accomplished by calling
;;; terminate-kb-save-or-backup-if-error-occurs. This is defined to be a bombout
;;; cleanup function. After terminating by completion or by forcing closure, G2
;;; is left in a state in which another save is possible.


;;; type-of-kb-save? may also be supplied as one of the following symbols:
;;;
;;;    KB-SAVE
;;;    KB-SAVE-WITH-RUNTIME-DATA
;;;    BACKUP
;;;    RUNTIME-DATA-ONLY
;;;    OK-KB-SAVE
;;;    NIL
;;;
;;; Of the above, OK-KB-SAVE and NIL are the only ones that aren't valid values
;;; for type-of-kb-save, the special variable.  NIL means that type-of-kb-save
;;; is KB-SAVE.  OK-KB-SAVE means that type-of-kb-save is KB-SAVE, and that the
;;; file will be saved out in the last supported old KB file format, currently
;;; that of 3.0 Rev. 3.  OK-KB-SAVE is only supported/indended for development.


(defun save-kb
    (pathname-or-module-saving-schedule &optional type-of-kb-save?
					emit-c-code? log-message-for-commit-after-saving?)
  (with-backtrace-for-internal-error 'save-kb-internal
    (let* ((enable-saving-compiled-kbs-p emit-c-code?)
	   (type-of-kb-save (or type-of-kb-save? 'kb-save))
	   (ok-file-saving-mode? (eq type-of-kb-save 'ok-kb-save))
	   (saving-modules-p		; type-of-save assumed appropriate
	     (listp pathname-or-module-saving-schedule)))
      (unless (or (reject-save-kb-if-run-time-only type-of-kb-save)
		  ;(reject-save-kb-if-system-clock-set-back)
		  (reject-save-kb-if-save-or-backup-in-progress)
		  ;; (reject-save-kb-if-for-impossible-backup)
		  (reject-save-kb-if-not-authorized)
		  (reject-save-kb-if-not-savable)
		  (reject-save-kb-if-filename-problems
		    pathname-or-module-saving-schedule)
		  (if saving-modules-p
		      (reject-save-kb-if-saving-modules-without-consistency)))

	(when clear-text-saving-problems-were-encountered-p
	  (reclaim-gensym-list clear-text-saving-problems-were-encountered-p)
	  (setq clear-text-saving-problems-were-encountered-p nil))

	;; Do this before we start noticing changes to blocks!
	(prepare-image-definitions-for-saving)

	;; Do before setting current-saving-context? and especially before
	;; noting-changes-to-kb-p gets set non-nil - fixes HQ-5277336 "Saving
	;; can fail with scheduled table updates"! (MHD 5/13/06)
	(prepare-blocks-and-connections-for-saving saving-modules-p)

	(setq current-saving-context?
	      (make-saving-context
		type-of-kb-save
		pathname-or-module-saving-schedule
		emit-c-code?
		log-message-for-commit-after-saving?))

	(setq noting-changes-to-kb-p t)    
	(setq kb-save-termination-reason? nil)

	(when (neq type-of-kb-save 'backup)
	  (setq basis-kb-frame-serial-number
		(current-frame-serial-number)))
	
	(cond
	  ((eq type-of-kb-save 'backup)
	   (setf (rest-of-deleted-items current-saving-context)
		 items-deleted-since-load-or-save
		 (last-of-deleted-items current-saving-context)
		 items-deleted-since-load-or-save-tail))
	  (t (reclaim-items-deleted-since-load-or-save)))
	(when (let ((number-of-streams-to-open-initially 1)) ; raise this later?!
		(block :initial-stream-opening
		  (with-saving-context (current-saving-context?)
		    (when (=f number-of-streams-to-open-initially 0)
		      (return-from :initial-stream-opening t))
		    (unless (open-kb-save-or-backup-stream) ; may or may not throw
		      (return-from :initial-stream-opening nil))
		    (decff number-of-streams-to-open-initially))
		  t))

	  (with-saving-context (current-saving-context?)
	    (write-initial-sections-of-kb-to-first-checkpoint)
	    (setf (saving-is-started? current-kb-save) t))

	  (setf (need-to-call-terminate-kb-save? current-saving-context?) nil)

	  (cond
	    (return-from-save-to-caller-for-continuation?)
	    (t
	     (continue-current-kb-save-or-backup current-saving-context?))))))))

;; The time slices are obtained by scheduling immeidate tasks with a priority
;; taken from saving-parameters, which is misnamed. Consider changing this. Also
;; consider obtaining the slices from run workstations, and running on an
;; interrupt basis all the time.

;; What happens if clear-kb while saving? If disasterous, install an interface.
;; .... UPDATE: What happens when saving from the menu (the built-in) interface
;; is supposed to work ok.  But if you are saving from a procedure, and the
;; procedure is deleted, it is supposed to abort, and the aborting should abort
;; the save, deleting the KB file(s).  Considering offering a variant of the
;; saving system procedures that will save to completion upon an abort.
;; Note that it has been a bug in 3.0 and 4.0 until now that aborting the
;; save procedure did not do this cleanup, and in fact left users without
;; a way to save again! This is due to be fixed.  (MHD 7/8/94)

;; The various reasons at the beginning of the function for refusing to run need
;; to be included in the procedural interface (i.e., in the system-procedures
;; interface).



;;; `Complete-save-after-running-if-necessary' is called when the system is
;;; paused or reset, with system-is-running bound to nil, and system-has-paused
;;; bound to t if pausing, and nil, if resetting.  Its job is to complete any
;;; save begun while the system was running, which must be done before a pause
;;; or reset state goes into effect.  (This is done mostly because we lack a
;;; scheduler in those modes, I believe.)

(defun complete-save-after-running-if-necessary ()
  ;; This completes save executed from menu while running.
  (execute-task-out-of-order continuation-task-for-current-backup)
  ;; This completes save executed from procedure
  (case save-kb-state-for-system-procedure-save
    (continue (continue-current-kb-save-or-backup current-saving-context?))
    (finish (finish-current-kb-save-or-backup current-saving-context?))))



;;; `Open-save-kb-stream-or-reject-save-kb' attempts to open the output file
;;; designated for the the current save by (kb-transfer-pathname
;;; current-kb-save).

;;; If there is a problem, a message of some sort is generated for the user, and
;;; nil is returned.  This handles setting the kb-save-termination-reason? and
;;; kb-save-stream-error-message global variables, if necessary, i.e., in the
;;; case of a save called from a G2 system procedure.
;;;
;;; If successful, a stream open for output is returned.  In addition, unless
;;; we're saving a non-top-level module, this stores a copy of the output file
;;; pathname into the global variable current-kb-pathname? after reclaiming the
;;; old value, if any, and, in addition, changes the current kb name, using
;;; make-or-clear-kb-complete-kb-name.

(defun-allowing-unwind open-save-kb-stream-or-reject-save-kb (compiled-source-p)
  (protected-let*
      ((pathname (if compiled-source-p
		     (kb-transfer-compiled-pathname current-kb-save)
		     (kb-transfer-pathname current-kb-save)))
       (namestring
	 (gensym-namestring pathname)
	 (reclaim-text-string namestring))
       (namestring-for-user
	 (copy-text-string namestring)
	 (reclaim-text-string namestring-for-user))
       ;; The function, gensym-probe-file-for-write, can return returns a new
       ;; gensym-pathname which should be reclaimed here.  (ghw 2/6/96)
       (probe-pathname?
	 (gensym-probe-file-for-write pathname)
	 (when probe-pathname? (reclaim-gensym-pathname probe-pathname?)))
       (save-kb-stream?
	 (and probe-pathname?
	      (cond
		#+development
		((and compiled-source-p emit-lisp-p)
		 (let ((gensym-string-namestring
			 (export-text-string namestring 'namestring-as-gensym-string)))
		   (prog1 (open gensym-string-namestring :direction :output)
		     (reclaim-gensym-string gensym-string-namestring))))
		(t
		 (find-and-open-temp-file pathname)))))
       (truename-of-save-kb-stream?
	 (cond
	   #+development
	   ((and compiled-source-p emit-lisp-p)
	    t)
	   (save-kb-stream?
	    (gensym-probe-file save-kb-stream?)))
	 (cond
	   #+development
	   ((and compiled-source-p emit-lisp-p))
	   (truename-of-save-kb-stream?
	     (reclaim-gensym-pathname truename-of-save-kb-stream?))))
       (message-string-if-error?
	 (cond
	   ((null save-kb-stream?)
	    (let ((error-text (most-recent-file-operation-status-as-text)))
	      (prog1 (tformat-text-string
		       "G2 could not open the file ~s:  ~a."
		       namestring-for-user
		       error-text)
		(reclaim-text-string error-text))))
	   ((null truename-of-save-kb-stream?)
	    (tformat-text-string
	      "Problem associating stream with file \"~a\"."
	      namestring-for-user)))))
    (cond
      (message-string-if-error?
       (setf (string-from-write-error-during-save? current-kb-save)
	     message-string-if-error?)
       nil)
      (t
       (unless compiled-source-p
	 (when (kb-module-being-saved? current-kb-save)
	   (set-true-pathname-of-module
	     (kb-module-being-saved? current-kb-save)
	     pathname current-kb-pathname?))
	 (unless (and (kb-module-being-saved? current-kb-save)
		      (not (eq (kb-module-being-saved? current-kb-save)
			       (top-level-kb-module? module-information))))
	   (store-current-pathname
	     current-kb-pathname? (copy-gensym-pathname pathname))
	   (add-recent-loaded-kb current-kb-pathname?)))

       save-kb-stream?))))




;;; `Make-saving-context' makes and returns a new saving-context structure.
;;;
;;; Whether to save runtime data is termined by type-of-kb-save.  If it is
;;; either RUNTIME-DATA-ONLY or KB-SAVE-WITH-RUNTIME-DATA, runtime data is
;;; written.  This becomes the value of the type-of-kb-save slot of the
;;; resulting saving-context structure.
;;; 
;;; Pathname-or-module-saving-schedule is either a single gensym pathname, or a
;;; "module loading schedule"; see KB-MERGE for an understanding of what a
;;; module loading schedule is.  None of the argument is reclaimed by this
;;; function, now or later; it must be reclaimed by the caller.
;;;
;;; The pane description is gotten via get-pane-description-for-saving-if-any;
;;; see its definition below.  Note that that function depends on the special
;;; variables g2-window-for-save-via-system-procedure?, and
;;; servicing-workstations?.
	    
(defun make-saving-context
    (type-of-kb-save pathname-or-module-saving-schedule
		     saving-compiled-kbs-p log-message-for-commit-after-saving?)
  (let* ((save-permanent-data?
	   (or (eq type-of-kb-save 'kb-save)
	       (eq type-of-kb-save 'kb-save-with-runtime-data)))
	 (save-runtime-data?
	   (or (eq type-of-kb-save 'runtime-data-only)
	       (eq type-of-kb-save 'kb-save-with-runtime-data)))
	 (serial-number
	   (current-frame-serial-number))
	 (saving-context-kb-file-progress-displays nil)		 
	 (list-of-saves
	   (loop with display-progress?
		   = (and save-permanent-data?
			  (not suppress-notification-for-kb-save?))
		 with existing-table-rows = nil
		 with existing-slots = nil
		 for (module? pathname? read-only?)
		     in (if (atom pathname-or-module-saving-schedule)
			    '((nil nil nil))
			    pathname-or-module-saving-schedule)
		 as pathname = (or pathname? pathname-or-module-saving-schedule)
		 as clear-text-p = (and pathname
					(string-equalw #w"xml" (gensym-pathname-type pathname)))
		 as use-crlf? = (if (and module?
					 (file-is-in-source-code-control-p pathname?))
				    (lookup-kb-specific-property-value-with-default
				      module? 'module-uses-crlf-p 'default)
				    'default)
		 as pathname-copy = (copy-gensym-pathname pathname)
		 as kb-transfer-user-namestring-as-text-string
		    = (gensym-namestring-as-text-string pathname-copy)
		 as kb-save?
		    = (unless read-only?
			(make-kb-save
			  pathname-copy
			  serial-number
			  module?
			  (get-pane-description-for-saving-if-any
			    save-runtime-data? module?)
			  clear-text-p
			  log-message-for-commit-after-saving?
			  (if (eq use-crlf? 'default)
			      (eq g2-operating-system 'win32)
			      use-crlf?)))
		 as file-progress
		    = (make-or-revise-file-progress
			nil nil
			kb-transfer-user-namestring-as-text-string
			'output
			(if read-only? 'read-only 'unopened)
			module?)
		 when read-only?	; always associated with a module for now
		   
		   do (give-read-only-warning-message pathname-copy module?)

		 when (and display-progress? kb-save?)
		   do (setf (kb-transfer-kb-file-progress-display? kb-save?)
			    file-progress)
		 do
	     (gensym-push
	       file-progress
	       saving-context-kb-file-progress-displays)
	     (when display-progress?
	       (multiple-value-setq
		   (existing-table-rows existing-slots)
		 (merge-frame-into-multiframe-table-rows
		   file-progress
		   (select-subset-of-file-progress-attributes-to-show
		     t module? t)
		   existing-table-rows
		   existing-slots)))
		 when kb-save?
		   collect kb-save? into result
		     using journal-cons
		 finally
		   (reclaim-if-text-string log-message-for-commit-after-saving?)
		   (when display-progress?
		     (reclaim-slot-value existing-slots)
		     (let* ((table
			      (finish-making-multiframe-table
				existing-table-rows nil))
			    (workspace
			      (make-workspace 'temporary-workspace nil table 2)))
		       (loop for workstation in workstations-in-service
			     as window = (window-for-workstation workstation)
			     do (put-workspace-on-pane
				  workspace
				  (detail-pane window)
				  'left 'top t
				  ;; Don't have a "standard" title bar, since at least for now we
				  ;; have no support for a close box while it's up. -mhd, 3/29/01
				  :frame-description-reference
				  (lookup-frame-description-reference-of-frame-style
				    'dialog-workspace-frame-style
				    'default-workspace-frame-style)))))
		   (return result))))
    (make-saving-context-internal
      list-of-saves
      type-of-kb-save
      save-permanent-data?
      save-runtime-data?
      saving-context-kb-file-progress-displays
      saving-compiled-kbs-p)))






;;; `Give-read-only-warning-message' is called to warn the user that a file to
;;; be saved is being skipped because it is read-only.  This is not always, at
;;; present, a fatal error.  If module? is non-nil, it should be the name of a
;;; module.

(defun-allowing-unwind give-read-only-warning-message (gensym-pathname module?)
  (protected-let ((name-text-string
		    (gensym-namestring-as-text-string gensym-pathname)
		    (reclaim-text-string name-text-string)))
    (notify-user
      "Warning: Cannot save ~a~a as ~s because it is ~
       read-only.  It is being skipped."
      (if module? "module " "this KB ")
      (or module? "")
      name-text-string)))





;;; The function `get-pane-description-for-saving-if-any' returns either nil or
;;; a pane description appropriate for saving.
;;;
;;; Whether transient workspaces are saved or not depends on the argument
;;; include-transient-kb-workspaces?.
;;;
;;; If module? is non-nil, only image planes for workspaces in that module are
;;; included in the pane description.
;;;
;;; If this is called within a workstation-servicing context, as indicated by
;;; the special variable servicing-workstations?, this saves the the pane layout
;;; for the current workstation's detail pane.  Otherwise, this saves the pane
;;; layout for the window given by the special variable
;;; g2-window-for-save-via-system-procedure?, if it's non-nil.  This window is
;;; bound by the system procedure, based on a parameter provided ultimately by
;;; the user.

(defun get-pane-description-for-saving-if-any
    (include-transient-kb-workspaces? module?)
  (let* ((g2-window?
	   (cond
	     (servicing-workstation?
	      (g2-window-for-this-workstation? current-workstation))
	     (t
	      g2-window-for-save-via-system-procedure?)))
	 (workstation?
	   (if g2-window?
	       (workstation-for-g2-window?-function g2-window?)))
	 (window-for-workstation?
	   (if workstation?
	       (window-for-workstation workstation?)))
	 (detail-pane?
	   (if window-for-workstation?
	       (detail-pane window-for-workstation?))))
    (if detail-pane?
	(modify-pane-description
	  (make-pane-description
	    detail-pane?
	    include-transient-kb-workspaces?
	    nil
	    module?))
	(if (null g2-window?)
	    (modify-pane-description
	      (loop for (workspace? . info) in saved-detail-pane-description
		    when (and (of-class-p workspace? 'kb-workspace)
			      (or include-transient-kb-workspaces?
				  (permanent-block-p workspace?))
			      (or (null module?)
				  (within-module-p workspace? module?)))
		      collect (slot-value-cons workspace?
					       (copy-for-slot-value info))
			using slot-value-cons))))))



;;; The macro `writing-to-kb-save-stream' is a special-purpose macro used when
;;; writing to the current kb withing saving-context, which is evaluated, lexically
;;; within the code block named block-name, which goes unevaluated.
;;;
;;; This can result in a return out of the block named block-name.  Thus, code
;;; that uses this will appear to be written to handle a non-local, even though
;;; the fact that this is a macro makes this appear to the compiler as a local
;;; exit (a return), rather than a non-local exit (a throw), strictly speaking.
;;;
;;; This is to be called insider the with-saving-context macro.
;;;
;;; This executes body, unless interrupted by a non-local exit.
;;;
;;; Regardless of whether there is a non-local exit, if this detects a non-local
;;; exit, or a file-io error, it terminates the save with an error message.
;;;
;;; Block-name should be the current block to return from in the even of an
;;; error in the output process, either a file io (stream) error or a random
;;; abort within body.  It may be any legal Common Lisp block.
;;;
;;; This macro includes an unwind-protect form.  This means that functions
;;; that use it must be defined using defun-allowing-unwind.
;;;
;;; This is a nonstandard macro: only the first of the values returned by
;;; its body forms is returned.
;;;
;;; This has special knowledge of at least some of its callers, via their block
;;; names, but only for purposes of giving more information in the event of an
;;; error.  If you want register a new caller, you will find it easy to do so
;;; by inspecting the code.

;;; Location-symbol gives the save function in which this is taking place.
;;; These map into standard termination reasons.  Here are the standard
;;; "termination reasons", and their locations:
;;;
;;;   error-writing-file-1  --  an error within open-kb-save-or-backup-stream
;;;   error-writing-file-2  --  an error within continue-current-kb-save
;;;   error-writing-file-3  --  an error within finish-current-kb-save
;;;   error-writing-file    --  an error anywhere else
;;;
;;; One of the above should be supplied.  Note that these are returned
;;; potentially to callers of G2 save/snapshot system procedures.  (Or so
;;; I believe. -MHD)

(defmacro writing-to-kb-save-stream
    ((saving-context block-name location-symbol &optional error-token?)
     &body body)
  (avoiding-variable-capture
      (saving-context block-name &aux stream-error-string? protected-form-completed-p)
    `(let* ((,stream-error-string? nil)
	    (,protected-form-completed-p nil))
       (most-recent-file-operation-succeeded)
       (unwind-protect
	    (prog1
		(progn . ,body)
	      (cond
		((string-from-write-error-during-save? current-kb-save)
		 (setq ,stream-error-string?
		       (string-from-write-error-during-save? current-kb-save))
		 (setf (string-from-write-error-during-save? current-kb-save) nil))
		((g2-stream-error-flag-set-p)
		 (setq ,stream-error-string?
		       (most-recent-file-operation-status-as-text))))
	      (setq ,protected-form-completed-p t))
	 (when (or (null ,protected-form-completed-p) ,stream-error-string?)
	   (defer-terminate-kb-save-or-backup 
	       ,saving-context
	       (getf '(open-kb-save-or-backup-stream error-writing-file-1
		       continue-current-kb-save error-writing-file-2
		       finish-current-kb-save error-writing-file-3)
		     ,location-symbol
		     'error-writing-file)
	     ,stream-error-string?)
	   (return-from ,block-name ,error-token?))))))

;; (jh, 6/4/92) After the body, we first see if we cached an error string during
;; some previous write to disk.  This makes sure that we catch disk-full errors
;; on implementations where fputc() only returns an EOF the
;; first time a write is attempted.  See write-char-for-kb for details.
;;
;; (MHD 1/6/93) --- Extended this to users of this macro -- it was originally
;; only on one of the "blocks".





;;; `Funcall-to-write-to-kb-save-stream' funcalls function in a
;;; writing-to-kb-save-stream context.  If the &optional error-token?  argument
;;; is non-nil, it will be returned if an error-occurs during the call.

(defun-allowing-unwind funcall-to-write-to-kb-save-stream
    (function location-symbol &optional error-token?)
  (writing-to-kb-save-stream
    (current-saving-context
      funcall-to-write-to-kb-save-stream ; block name
      location-symbol
      error-token?)
    (funcall function)))  


;;; The top level functions for writing KBs can work either by continuation, or
;;; by call/returning without interrupts. 

;;; `Open-kb-save-or-backup-stream' opens the stream for the current KB save.
;;; It does not write anything.  It may be called after the first things have
;;; been written to buffers; they'll flushed to this stream later.  Note that KB
;;; writing may proceed before this is function is executed.  It simply results
;;; in more buffering to occur prior to actually writing to disk.
;;;
;;; `Write-initial-sections-of-kb-to-first-checkpoint' does various preliminary
;;; tasks up through writing the initial plist.  This call as a function without
;;; any interruption, rather than a continuation, because the checkpoint of the
;;; save is not reached until after start-kb-save-or-backup completes. If
;;; continue-current-kb-save-or-backup were to be called with with
;;; node-to-write-if-interrupting? non-nil during the interum, the environment
;;; would be incorrect, and it would fail in some way.
;;;
;;; Calling rather than continuing introduces a larger delay.  There is no easy
;;; way around this. The time consuming activities necessary to reach a
;;; checkpoint are (i) opening the file (which is done by the caller), (ii)
;;; clearing the old object index, and (iii) marking every item. The last of
;;; these must be done at the checkpoint for it to be valid.  It need not be
;;; last.  In addition, a fourth activity, writing every definition out in the
;;; class-definitions section of the KB, must be done before any frames or
;;; connections are written out of order (i.e., "noting" a change).  These
;;; problems are not easily solved.
;;;
;;; Note that it is not allowed here for anything that results in writing of
;;; frames, including changes to slots and deletion, to occur; it would result
;;; in the frame being written out in the middle of the header.  Such changes
;;; must come before the KB is opened for writing, or wait until after the first
;;; checkpoint is written (i.e., by
;;; write-initial-sections-of-kb-to-first-checkpoint).
;;;
;;; Write-initial-sections-of-kb-to-first-checkpoint temporarily binds
;;; noting-changes-to-kb-p to nil in order to prevent the system table
;;; saving-parameters from being written out during the checkpoint;
;;; saving-parameters has to have its slots changed here, and should be
;;; the only frame that has changes that need noting.

(defun-allowing-unwind open-kb-save-or-backup-stream ()
  (writing-to-kb-save-stream
    (current-saving-context
      open-kb-save-or-backup-stream
      'open-kb-save-or-backup-stream)
    (let ((save-kb-stream? (open-save-kb-stream-or-reject-save-kb nil)))
      (update-file-progress-display-status (if save-kb-stream? 'open 'aborted))
      (cond
	((null save-kb-stream?)
	 nil)
	(t
	 (setf (kb-transfer-stream? current-kb-save) save-kb-stream?)
	 (setf (kb-transfer-stream-open? current-kb-save) t)
	 (cond
	   ((not enable-saving-compiled-kbs-p)
	    t)
	   (t
	    (let ((save-compiled-kb-stream?
		    (open-save-kb-stream-or-reject-save-kb t)))
	      (cond
		((null save-compiled-kb-stream?)
		 ;; reclaim save-kb-stream? in this case
		 nil)
		(t
		 (setf (kb-transfer-compiled-stream? current-kb-save) save-compiled-kb-stream?)
		 (setf (kb-transfer-compiled-stream-open? current-kb-save) t)
		 t))))))))))

(defun-void write-initial-sections-of-compiled-kb-to-first-checkpoint ()
  (cond
    #+development
    (emit-lisp-p
     (let ((out (kb-transfer-compiled-stream? current-kb-save)))
       (format out ";;-*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-~%~%")
       (let ((*print-case* :downcase))
	 (format out "~S~%~%" '(in-package "AB"))
	 (format out "~S~%~%" '(proclaim '(optimize (speed 0) (safety 3)
					   #+lucid (compilation-speed 3)))))))
    (t
     (start-new-compiled-kb-line)
     (write-gensym-string-for-compiled-kb "#include \"bytecode.h\"")
     (start-new-compiled-kb-line)
     (start-new-compiled-kb-line)
     (write-gensym-string-for-compiled-kb "static Object *byte_code_constants;")
     (start-new-compiled-kb-line)
     (write-gensym-string-for-compiled-kb "static Object **byte_code_variables;")
     (start-new-compiled-kb-line)
     (write-gensym-string-for-compiled-kb "static fn_type *byte_code_functions;")
     (start-new-compiled-kb-line)
     (write-gensym-string-for-compiled-kb "static fn_type *byte_code_run_time_functions;")
     (start-new-compiled-kb-line)
     (start-new-compiled-kb-line))))


(defun write-initial-sections-of-kb-to-first-checkpoint ()
  (let ((noting-changes-to-kb-p nil))
    (let ((kb-name (make-kb-name (kb-transfer-pathname current-kb-save))))

      ;; new for KB change logging:   (MHD 11/17/96)      
      (let ((instance?
	      (if (kb-module-being-saved? current-kb-save)
		  (get-system-table-of-class-for-module-or-nil
		    (kb-module-being-saved? current-kb-save)
		    'saving-parameters)
		  saving-parameters)))      
	(when instance?
	  (increment-version-for-change-logging-if-appropriate
	    instance?)))
      
      (make-or-clear-complete-kb-name
	kb-name nil
	(kb-module-being-saved? current-kb-save))
      (reclaim-text-string kb-name))
    (case (format-for-kb-save current-kb-save)
      (normal
       (write-initial-plist complete-kb-name?)
       (setf (kb-transfer-base-reference? current-kb-save) ; enables kb encryption
	     (modf (frame-serial-number-hash (current-frame-serial-number)) base-modulus))
       (when (kb-module-being-saved? current-kb-save)
	 (write-ghost-definitions
	   (kb-module-being-saved? current-kb-save))))
      (clear-text
       nil))
    (when enable-saving-compiled-kbs-p
      (write-initial-sections-of-compiled-kb-to-first-checkpoint))))

;; Note: making (kb-transfer-base-reference? current-kb-save) nil saves "in the
;; clear" -- useful for debugging sometimes. (MHD/JH 6/5/92)



;;; `Not-ready-to-finish-current-kb-save' is to be called within a saving
;;; context.  It returns true if there are either unprocessed deleted items or
;;; unprocessed kb-traversal elements in current-saving-context.  Otherwise,
;;; this returns nil.
;;;
;;; `Not-ready-to-finish-kb-save' does the same, only it takes a saving context
;;; as an argument, and so need not be called within a saving context.

(defmacro not-ready-to-finish-current-kb-save ()
  `(or (rest-of-deleted-items current-saving-context)
       (kb-traversal-state-for-backup current-kb-save)))

(defmacro not-ready-to-finish-kb-save (saving-context)
  `(block :over
     (with-saving-context (,saving-context)
       (when (not-ready-to-finish-current-kb-save)
	 (return-from :over t)))
     nil))



;;; `Write-deletion-for-backup-or-journal' ...

(defmacro write-deletion-for-backup-or-journal (frame-serial-number)
  `(progn
     (write-char-for-kb #\D)
     (write-frame-serial-number-for-kb ,frame-serial-number)))



;;; `Continue-current-kb-save-or-backup' is the main continuable part of writing
;;; a kb.

(defun-simple continue-current-kb-save-or-backup (saving-context)
  (block :timeout
    (with-saving-context (saving-context)
      (when (not-ready-to-finish-current-kb-save)
	(continue-current-kb-save nil))
      (when (null current-saving-context?)	; if terminated
	(return-from continue-current-kb-save-or-backup nil))
      ;; can starve ones at end -- FIX!!
      (when (and system-is-running (time-slice-expired-p))
	(return-from :timeout nil))))
  (cond
    ((not system-is-running)
     (terminate-kb-save-or-backup saving-context nil nil))
    (return-from-save-to-caller-for-continuation?)
    ((need-to-call-terminate-kb-save? saving-context))
    (t
     (if (not-ready-to-finish-kb-save saving-context)
	 (with-current-scheduling (continuation-task-for-current-backup
				    (journal-priority saving-parameters))
	   (continue-current-kb-save-or-backup saving-context))
	 (with-current-scheduling (continuation-task-for-current-backup
				    (journal-priority saving-parameters))
	   (terminate-kb-save-or-backup saving-context nil nil))))))





;;; `Save-only-if-interrupting?' is a variable used in debugging or in
;;; development.  Although it is for development, it is defined in
;;; non-development versions at present.  It is normally nil.  When it is
;;; non-nil, and the system is running, saving will only proceed (beyond
;;; "header" information, and information written out before interrupts are
;;; allowed) in order to save things that are "touched".  In this mode, in fact,
;;; one way to save everything is to delete everything.  That's right.  Doing a
;;; clear-kb while a save is going with this flag set, should cause the entire
;;; KB to be written out to disk as it was before the save began.  (However, the
;;; menu choice clear-kb is typically disabled while running.  A developer can
;;; still call it by hand, however.  A more practical approach is to delete
;;; top-level workspaces.)

(defvar save-only-if-interrupting? nil)


;;; use-minimal-time-slice-for-continue-current-kb-save-p is also used
;;; for debugging.  It is less drastic than save-only-if-interrupting?,
;;; in that it does allow saving to proceed without touching.  It forces
;;; saving to happen in small chunks (see write-kb-per-traversal-state-a-little),
;;; as if the timeslice for saving were very small.

(defvar use-minimal-time-slice-for-continue-current-kb-save-p nil)


;;; `Dont-cerror-for-slot-changes-while-on-window?' is a variable used in
;;; debugging or in development.  Although it is for development, it is defined
;;; in non-development versions at present.  It should never be changed by hand.
;;; It is normally nil.  If a slot is changed while saving while running from
;;; inside an on-window, a cerror will result protesting that this is not
;;; supposed to happen.  If the user (the Lisp developer) proceeds,
;;; dont-cerror-for-slot-changes-while-on-window? is set to true, and the cerror
;;; will no longer occur.

;;; (If the cerror never occurs, for a long time, and nothing else deters us, we
;;; will probably assume that the sources are actually free of this, and we will
;;; then enable the update of the file progess display while saving due to a slot
;;; value change.)

(defvar dont-cerror-for-slot-changes-while-on-window? nil)



;;; `Continue-current-kb-save' ...
;;;
;;; If node-to-write-if-interrupting? is true, this is being called in "interrupt"
;;; mode, that is, from within a change to a node in the KB that necessitates
;;; writing the node out immediately, e.g., a deletion of a block, a change of
;;; a slot in a block, etc.  It is assumed that this may only occur in the case
;;; of a save while running, i.e., a suspendable save.
;;;
;;; When this is true, the writing continues until all definitions have been
;;; written.  Then, the node is pushed into the traversal state.  Then that one
;;; traversal state is gone past, at which point this save may be suspended.

(defvar continue-current-kb-save-failure '(continue-current-kb-save-failure))

(defun-simple continue-current-kb-save (node-to-write-if-interrupting?)
  (with-backtrace-for-internal-error 'continue-current-kb-save
    (when (and system-is-running
	       save-only-if-interrupting?	; for debugging/development only
	       (null node-to-write-if-interrupting?))
      (return-from continue-current-kb-save nil))
    (when (null (kb-transfer-stream? current-kb-save))
      (when (null (open-kb-save-or-backup-stream))
	(return-from continue-current-kb-save nil)))
    (let ((write-ok-p t)
	  (display-to-restore?
	    (when node-to-write-if-interrupting?
	      (block :display
		#+development
		(if (boundp 'current-window)
		    (unless dont-cerror-for-slot-changes-while-on-window?
		      (cerror "go on (this cerror will be disabled; ~
                             it'll be ok, for now)"
			      "Setting slots while on-window is ~
                             a questionable thing to do. (MHD)")
		      (setq dont-cerror-for-slot-changes-while-on-window? t))
		    (return-from :display nil))
		(prog1 (kb-transfer-kb-file-progress-display? current-kb-save)
		  (setf (kb-transfer-kb-file-progress-display? current-kb-save)
			nil)))))
	  (node-to-insert? node-to-write-if-interrupting?)
	  (write-xml-object-items-collected nil))
      (case (format-for-kb-save current-kb-save)
	(clear-text
	 (when (eq (funcall-to-write-to-kb-save-stream
		     #'write-clear-text-kb
		     'continue-current-kb-save
		     continue-current-kb-save-failure)
		   continue-current-kb-save-failure)
	   (setq write-ok-p nil)))
	(normal
	 (loop until (finished-writing-definitions? current-kb-save)
	       for write-result = (funcall-to-write-to-kb-save-stream
				    #'write-kb-per-traversal-state-a-little
				    'continue-current-kb-save
				    continue-current-kb-save-failure)
	       do
	   (when (eq write-result continue-current-kb-save-failure)
	     (setq write-ok-p nil)
	     (loop-finish)))
	 (when write-ok-p
	   (loop while (not-ready-to-finish-current-kb-save)
		 for write-result
		     = (cond
			 ((rest-of-deleted-items current-saving-context)
			  (funcall-to-write-to-kb-save-stream
			    #'write-deletions-for-saving-a-little
			    'continue-current-kb-save
			    continue-current-kb-save-failure))
			 (t (when node-to-insert?
			      (add-node-to-current-kb-save-traversal node-to-insert?)
			      (setq node-to-insert? nil))
			    (funcall-to-write-to-kb-save-stream
			      #'write-kb-per-traversal-state-a-little
			      'continue-current-kb-save
			      continue-current-kb-save-failure)))
		 do (when (eq write-result continue-current-kb-save-failure)
		      (setq write-ok-p nil)
		      (loop-finish))
		 until (and system-is-running
			    (and (null node-to-insert?)
				 (or (null node-to-write-if-interrupting?)
				     (if (connection-p node-to-write-if-interrupting?)
					 (connection-has-been-written-p
					   node-to-write-if-interrupting?)
					 (block-written-in-current-save-p
					   node-to-write-if-interrupting?))))
			    (or use-minimal-time-slice-for-continue-current-kb-save-p
				(time-slice-expired-p)))))))
      (when write-ok-p
	(unless (not-ready-to-finish-current-kb-save)
	  (finish-current-kb-save))
	(when display-to-restore?
	  (setf (kb-transfer-kb-file-progress-display? current-kb-save)
		display-to-restore?))))))



;;; `Write-deletions-for-saving-a-little' writes out a small fixed number (10)
;;; of deleted items, per the value of
;;;
;;;    (rest-of-deleted-items current-saving-context)
;;;
;;; This function manages this slot as well as the last-of-deleted-items slot
;;; in the saving context structure.
;;;
;;; This function is only used in the case of a backup.

(defun-void write-deletions-for-saving-a-little ()
  (loop repeat 10
	while (rest-of-deleted-items current-saving-context)
	do (write-deletion-for-backup-or-journal
	     (first (rest-of-deleted-items current-saving-context)))
	   (setf (rest-of-deleted-items current-saving-context)
		 (if (eq (rest-of-deleted-items current-saving-context)
			 (last-of-deleted-items current-saving-context))
		     nil
		     (cdr (rest-of-deleted-items current-saving-context))))))

;;; `Write-kb-per-traversal-state-a-little' advances traversal of the KB
;;; according to the current traversal state, i.e.,
;;; 
;;;    (kb-traversal-state-for-backup current-kb-save)
;;;
;;; This function manages this slot in the saving context structure.

(defun-void write-kb-per-traversal-state-a-little ()
  (macrolet ((state () `(kb-traversal-state-for-backup current-kb-save))
	     (nodes () `(cdar (state)))
	     (fsn   () `(caar (state))))
    ;; ((fsn . nodes) ...)
    (let ((new-nodes
	    (write-kb-traversal-state-node (fsn)
					   (journal-pop (nodes)))))
      (when (null (nodes))
	(reclaim-frame-serial-number (fsn))
	(reclaim-journal-cons (journal-pop (state))))
      (when new-nodes
	(add-nodes-to-current-kb-save-traversal new-nodes)))))


;; This iteration is top-down, depth-first. It has been demonstrated that a
;; bottom up, depth first traversal writes a KB that is 1.5% smaller because
;; there are fewer references to frames not yet written. (ML)




;;; The function `write-kb-traversal-state-node', called within a saving
;;; context, with the next serial number and node off the traversal state,
;;; writes that node to the current KB.
;;;
;;; If this should lead to a new list of nodes to be pushed into the saving
;;; context, as determined by calling traverse-kb-for-saving on the current
;;; node, that list of nodes is returned, freshly made out of journal conses.
;;; 
;;; This routine notices the transition from the definitions section to the
;;; top-level-workspaces section.  At this transition, it notes that we're
;;; finished writing definitions by setting
;;;
;;;    (finished-writing-definitions? current-kb-save)
;;;
;;; to true.
;;;
;;; Unless this is a backup, the permanently-changed flag of either a connection
;;; or block node is cleared at the time that the written flag is set, which
;;; time is described below.  (But the permanently-changed flag is only relevant
;;; when this is a save with runtime data, i.e., a basis KB being saved.  And
;;; then, it's only important for creating backups based on such a KB.)
;;;
;;; Normally, when node is a block or connection that has not yet been marked as
;;; written, it writes it out and marks it as written.  It also traverses the
;;; subhierarchy (i.e., the inferiors) of the node.
;;;
;;; However, definitions must be "traversed" two times: once for the definitions
;;; section of the KB, and once as blocks within the workspace hierarchy.  This
;;; function knows if it's the second time or not based on whether we're
;;; finished writing definitions.
;;;
;;; When node is a definition, and we're not finished writing definitions, this
;;; writes out the definition unconditionally, does not mark the definition as
;;; has having been written, does mark the definition as having been referenced,
;;; does increment the frame reference balance, and does not traverse the
;;; subhierarchy under the definition, i.e., nil is returned from this function.
;;; Also, if this is a save with runtime data, the subfunctions that write the
;;; definition know not to write that runtime data.  This is done to prevent
;;; references to instances ahead of their definitions.  The runtime data gets
;;; written later, as described next.
;;;
;;; The marking of the definition as referenced, and incrementing of the
;;; reference balance, is done in order to make references work; since we're not
;;; marking definitions as having been written, marking them as referenced at
;;; least keeps G (forward) references from being created.  This is slightly
;;; kludgey in that we have these frames marked as referenced, even though there
;;; aren't any references (G -- forward references) actually written.  That's
;;; life.  See also write-reference-to-frame.
;;;
;;; When node is a definition, and we're finished writing definitions, this
;;; assumes that the definition must have already been written out.  At this
;;; point it does mark the definition as having been written, and it will
;;; traverse the kb hierarchy under the definition.  It does not write out the
;;; definition.  However, if this is a save with runtime data, and the
;;; definition has runtime data, this now writes the definition's runtime data,
;;; as a frame modification.
;;;
;;; If node is a kb-workspace instance, this "normalizes" the workspace prior to
;;; writing it.  See normalize-kb-workspace for details.

(defun-simple write-kb-traversal-state-node (serial-number node)
  (let* ((saving-backup?
	   (eq (type-of-kb-save current-saving-context) 'backup)))
    (cond
      ((symbolp node)
       (when (eq node :top-level-workspaces)
	 (setf (finished-writing-definitions? current-kb-save) t))
       (traverse-kb-for-saving node))
      ((connection-p node)
       (unless (or (connection-has-been-reprocessed-p node serial-number)
		   (connection-has-been-written-p node))
	 (set-connection-has-been-written node)
	 (unless (and saving-backup?
		      (not (connection-permanently-changed-p node)))
	   (write-connection-for-kb node)
	   (unless saving-backup?
	     (clear-connection-permanently-changed node)))
	 (traverse-kb-for-saving node)))
      ((framep node)
       (unless (or (frame-has-been-reprocessed-p node serial-number)
		   (block-written-in-current-save-p node))
	 (let ((class-test
		 (frame-class-case node
		   (class-definition 'class-definition)
		   (kb-workspace 'kb-workspace)))
	       (dont-save-for-this-backup?
		 (and saving-backup?
		      (not (block-permanently-changed-p node)))))
	   (cond
	     ((eq class-test 'class-definition)
	      (cond
		((finished-writing-definitions? current-kb-save)
		 (setf (block-written-in-current-save-p node) t)
		 (unless dont-save-for-this-backup?
		   (cond
		     ;; The way relation instances are saved when
		     ;; snapshotting is mutually exclusive of the
		     ;; method used when doing a normal save.
		     ((save-runtime-data? current-saving-context)
		      (when (relation-instances-not-empty-p
			      (relation-instances node)) ; has runtime data
			(write-runtime-data-frame-modification node)))
		     (t
		      (when (frame-of-class-p node 'definition)
			(write-entangled-slots-of-definition-as-frame-modification node))))
		   (unless saving-backup?
		     (note-saving-frame node)))
		 (traverse-kb-for-saving node))
		(t
		 (unless dont-save-for-this-backup?
		   (unless (block-referenced-in-current-save-p node)
		     (setf (block-referenced-in-current-save-p node) t)
		     (increment-frame-reference-balance
		       node 'write-kb-traversal-state-node))
		   (write-frame-for-kb node t))
		 nil)))
	     (t
	      (setf (block-written-in-current-save-p node) t)
	      (when (eq class-test 'kb-workspace)
		(normalize-kb-workspace node t))
	      (unless dont-save-for-this-backup?
		(write-frame-for-kb node t)
		(unless saving-backup?
		  (note-saving-frame node)))
	      (traverse-kb-for-saving node)))))))))




(defun-void write-compiled-kb-file-specific-initialization-function ()
  (start-new-compiled-kb-line)
  (start-new-compiled-kb-line)
  (write-gensym-string-for-compiled-kb "DLLEXPORT void do_initialize_compiled_kb_")
  (write-fixnum-for-compiled-kb (compiled-kb-emitted-files-count current-kb-save))
  (write-gensym-string-for-compiled-kb "(args)")
  (start-new-compiled-kb-line)
  (write-gensym-string-for-compiled-kb "  void **args;")
  (start-new-compiled-kb-line)
  (write-char-for-compiled-kb #\{)
  (start-new-compiled-kb-line)
  (write-gensym-string-for-compiled-kb "  byte_code_constants = (Object *)(args[0]);")
  (start-new-compiled-kb-line)
  (write-gensym-string-for-compiled-kb "  byte_code_variables = (Object **)(args[1]);")
  (start-new-compiled-kb-line)
  (write-gensym-string-for-compiled-kb "  byte_code_functions = (fn_type *)(args[2]);")
  (start-new-compiled-kb-line)
  (write-gensym-string-for-compiled-kb "  byte_code_run_time_functions = (fn_type *)(args[3]);")
  (start-new-compiled-kb-line)
  (loop for i from (1+f (starting-byte-code-body-count current-kb-save))
	      to (compiled-kb-byte-code-body-count current-kb-save)
	do (write-gensym-string-for-compiled-kb "  add_compiled_function(fn")
	   (write-fixnum-for-compiled-kb i)
	   (write-gensym-string-for-compiled-kb ");")
	   (start-new-compiled-kb-line))
  (write-char-for-compiled-kb #\})
  (start-new-compiled-kb-line)
  (start-new-compiled-kb-line))

(defvar finish-current-kb-save-failure '(finish-current-kb-save-failure))

(defun close-and-rename-current-compiled-kb-stream ()
  (let* ((stream
	   (kb-transfer-compiled-stream? current-kb-save))
	 (temp-file-truename (cond
			       #+development
			       (emit-lisp-p
				(truename stream))
			       (t
				(gensym-truename stream))))
	 termination-description)
    (update-file-progress-display-status 'closing-compiled)
    (unless (prog1 (eq (funcall-to-write-to-kb-save-stream
			 #'close-current-compiled-kb-save-stream
			 'finish-current-kb-save
			 finish-current-kb-save-failure)
		       finish-current-kb-save-failure)
	      (setf (kb-transfer-compiled-stream? current-kb-save) nil))
      (cond
	((g2-stream-error-flag-set-p) ;close failed
	 (gensym-delete-file temp-file-truename)
	 (setq termination-description
	       (most-recent-file-operation-status-as-text)))
	#+development
	(emit-lisp-p nil)
	(t
	 (checkpoint-file-if-necessary
	   (kb-transfer-compiled-pathname current-kb-save))
	 ;; Record the truename here to report to the user.  jh, 1/28/92.
	 (multiple-value-bind (new-pathname? old-truename? new-truename?)
	     (gensym-rename-file
	       temp-file-truename
	       (kb-transfer-compiled-pathname current-kb-save))
	   (when new-pathname?
	     (reclaim-gensym-pathname new-pathname?))
	   (when old-truename?
	     (reclaim-gensym-pathname old-truename?))
	   (when new-truename?
	     (reclaim-gensym-pathname new-truename?))
	   (when (g2-stream-error-flag-set-p) ;rename failed
	     (gensym-delete-file temp-file-truename)
	     (setq termination-description
		   (most-recent-file-operation-status-as-text))))))
      (update-file-progress-display-status 'closed-compiled)
      #+ignore ; don't tell the user about every compiled file
      (notify-user-of-save-termination
	(make-description-text-line-for-kb-save
	  current-saving-context current-kb-save)
	nil nil nil)
      (cond
	#+development
	(emit-lisp-p nil)
	(t
	 (reclaim-gensym-pathname temp-file-truename))))))


(defun-void increment-compiled-kb-file ()
  (write-compiled-kb-file-specific-initialization-function)
  (flush-compiled-kb-write-buffer)
  (setf (length-of-saved-compiled-kb-file-so-far current-kb-save) 0)
  (setf (starting-byte-code-body-count current-kb-save)
	(compiled-kb-byte-code-body-count current-kb-save))
  (incff (compiled-kb-emitted-files-count current-kb-save))
  (close-and-rename-current-compiled-kb-stream)
  (let ((save-compiled-kb-stream?
	  (open-save-kb-stream-or-reject-save-kb t)))
    (when save-compiled-kb-stream?
      (setf (kb-transfer-compiled-stream? current-kb-save)
	    save-compiled-kb-stream?)
      (setf (kb-transfer-compiled-stream-open? current-kb-save) t)
      (set-compiled-kb-file-pathname
	current-kb-save
	(kb-transfer-pathname current-kb-save)
	(compiled-kb-emitted-files-count current-kb-save))
      (write-initial-sections-of-compiled-kb-to-first-checkpoint))))


(defun-void compile-files-into-shared-object (kb-save)
  (let* ((kb-filename
	   (funcall
	     (gensym-pathname-namestring-generator (kb-transfer-pathname kb-save))
	     (kb-transfer-pathname kb-save)))
	 (dll-name
	   (kb-name->shared-object-filename kb-filename)))
    (c-produce_shared_object
      kb-filename
      (compiled-kb-emitted-files-count kb-save)
      (get-object-file-suffix-for-this-os)
      dll-name)
    (reclaim-text-string dll-name)))



(defun-simple finish-current-kb-save-or-backup (saving-context)
  (with-saving-context (saving-context)
    (finish-current-kb-save)
    (when (null current-saving-context?) ; if terminated
      (return-from finish-current-kb-save-or-backup nil)))
  (terminate-kb-save-or-backup saving-context nil nil))


(defun finish-current-kb-save ()
  (funcall-to-write-to-kb-save-stream
    #'finish-current-kb-save-1
    'finish-current-kb-save))


(defun-void write-compiled-kb-bootstrap-function ()
  (write-gensym-string-for-compiled-kb "DLLEXPORT long initialize_compiled_kb(args)")
  (start-new-compiled-kb-line)
  (write-gensym-string-for-compiled-kb "  void **args;")
  (start-new-compiled-kb-line)
  (write-char-for-compiled-kb #\{)
  (start-new-compiled-kb-line)
  (write-gensym-string-for-compiled-kb "  if (!check_version(")
  (write-fixnum-for-compiled-kb current-compiled-byte-code-version)
  (write-gensym-string-for-compiled-kb ")) return 0;")
  (start-new-compiled-kb-line)
  (loop for i from 1 to (compiled-kb-emitted-files-count current-kb-save) do
    (write-gensym-string-for-compiled-kb "  do_initialize_compiled_kb_")
    (write-fixnum-for-compiled-kb i)
    (write-gensym-string-for-compiled-kb "(args);")
    (start-new-compiled-kb-line))
  (write-gensym-string-for-compiled-kb "  return 1;")
  (start-new-compiled-kb-line)
  (write-char-for-compiled-kb #\})
  (start-new-compiled-kb-line)
  (start-new-compiled-kb-line))

;;; For some reason, a call to printf causes the dll to load properly on
;;; the sun4; without this function, dlopen gets an error during mmap.
;;; stupid, but there it is -alatto, 9/25/98

(defun-void write-compiled-kb-dummy-function ()
  (write-gensym-string-for-compiled-kb "void dummy () {")
  (start-new-compiled-kb-line)
  (write-gensym-string-for-compiled-kb "  printf(\"Don't know why, but if this isn't here, dlopen bombs out on the sun4\");")
  (start-new-compiled-kb-line)
  (write-char-for-compiled-kb #\})
  (start-new-compiled-kb-line)
  (start-new-compiled-kb-line))

(defun write-final-plist-for-current-kb-save ()
  (when enable-saving-compiled-kbs-p
    (cond
      #+development
      (emit-lisp-p)
      (t
       (write-compiled-kb-file-specific-initialization-function)
       (write-compiled-kb-bootstrap-function)
       ;;(write-compiled-kb-dummy-function)
       )))
  (write-final-plist
    (kb-transfer-pane-description? current-kb-save)
    (time-of-kb-save-or-backup current-saving-context)))

(defun close-current-kb-save-stream ()
  (g2-stream-close (kb-transfer-stream? current-kb-save)))

(defun-void close-current-compiled-kb-save-stream ()
  (cond
    #+development
    (emit-lisp-p
     (close (kb-transfer-compiled-stream? current-kb-save))
     (let* ((gensym-string (export-text-string
			     (gensym-namestring
			       (kb-transfer-compiled-pathname current-kb-save))
			     'namestring-as-gensym-string))
	    (output-pathname (pathname->shared-file-pathname
			       (kb-transfer-compiled-pathname current-kb-save)))
	    (output-gensym-string (namestring-as-gensym-string output-pathname)))
       (compile-file gensym-string :output-file output-gensym-string)
       (reclaim-gensym-string gensym-string)
       (reclaim-gensym-pathname output-pathname)
       (reclaim-gensym-string output-gensym-string)))
    (t
     (g2-stream-close (kb-transfer-compiled-stream? current-kb-save)))))


(defun close-and-rename-kb-stream (stream compiled-p log-message-for-commit?)
  (when stream
    (let* ((temp-file-truename (cond
				 #+development
				 ((and emit-lisp-p compiled-p)
				  (truename stream))
				 (t
				  (gensym-truename stream))))
	   (termination-reason? nil)
	   termination-description)
      (update-file-progress-display-status (if compiled-p 'closing-compiled 'closing))
      (unless (prog1 (eq (funcall-to-write-to-kb-save-stream
			   (if compiled-p
			       #'close-current-compiled-kb-save-stream
			       #'close-current-kb-save-stream)
			   'finish-current-kb-save
			   finish-current-kb-save-failure)
			 finish-current-kb-save-failure)
		(if compiled-p
		    (setf (kb-transfer-compiled-stream? current-kb-save) nil)
		    (setf (kb-transfer-stream? current-kb-save) nil)))
	(cond
	  (termination-reason?
	   (gensym-delete-file temp-file-truename))
	  ;; jh, 3/13/92.  The following clause is taken if the close failed,
	  ;; which could mean that the file is corrupt.  This happened most
	  ;; recently due to a bug on the Sparcs, which fail to report a
	  ;; "device full" condition in fputc(), but wait until fclose().
	  ;; This was leaving old temp files on disk, since the subsequent
	  ;; rename failed too.  As a last-ditch effort, we try to delete the
	  ;; temp file, but we don't care about any g2-stream error that
	  ;; happens during this cleanup.
	  ((g2-stream-error-flag-set-p) ;close failed
	   (gensym-delete-file temp-file-truename)
	   (setq termination-reason? 'close-failed)
	   (setq termination-description
		 (most-recent-file-operation-status-as-text)))
	  #+development
	  ((and emit-lisp-p compiled-p)
	   nil)
	  (t
	   (checkpoint-file-if-necessary
	     (if compiled-p
		 (kb-transfer-compiled-pathname current-kb-save)
		 (kb-transfer-pathname current-kb-save)))
	   ;; Record the truename here to report to the user.  jh, 1/28/92.
	   (multiple-value-bind (new-pathname? old-truename? new-truename?)
	       (gensym-rename-file
		 temp-file-truename
		 (if compiled-p
		     (kb-transfer-compiled-pathname current-kb-save)
		     (kb-transfer-pathname current-kb-save)))
	     (when (and new-pathname? old-truename? new-truename?)
	       ;; rename succeeded
	       (cond
		 (compiled-p
		  nil)
		 (t
		  (when log-message-for-commit?
		    (try-to-commit-file new-pathname? log-message-for-commit?))
		  (let ((old-namestring-for-user? ; when nil?! (MHD 12/17/93)
			  (kb-transfer-user-namestring current-kb-save)))
		    (when (text-string-p old-namestring-for-user?)
		      (reclaim-text-string old-namestring-for-user?))
		    (setf (kb-transfer-user-namestring current-kb-save)
			  (gensym-namestring-as-text-string new-truename?))))))
	     (when new-pathname?
	       (reclaim-gensym-pathname new-pathname?))
	     (when old-truename?
	       (reclaim-gensym-pathname old-truename?))
	     (when new-truename?
	       (reclaim-gensym-pathname new-truename?))
	     (when (g2-stream-error-flag-set-p) ;rename failed
	       (gensym-delete-file temp-file-truename)
	       (setq termination-reason? 'rename-failed)
	       (setq termination-description
		     (most-recent-file-operation-status-as-text))))))
	(update-file-progress-display-status 'closed)
	(cond
	  (termination-reason?
	   ;; Terminate-kb-save-or-backup takes responsibility for reclaiming
	   ;; file-system-termination-reason?.
	   (terminate-kb-save-or-backup 
	     current-saving-context
	     termination-reason?
	     termination-description))
	  (t (when (and (not compiled-p)
			(null (kb-transfer-compiled-stream? current-kb-save)))
	       (let ((module? (kb-module-being-saved? current-kb-save)))
		 (when module?
		   (setf (module-is-writable-p module?) t)
		   (set-reason-module-is-not-editable
		     module?
		     (if (file-is-in-source-code-control-p
			   (kb-transfer-pathname current-kb-save))
			 'unknown
			 nil))))
	       (notify-user-of-save-termination
		 (make-description-text-line-for-kb-save
		   current-saving-context current-kb-save)
		 nil nil
		 (memq (kb-module-being-saved? current-kb-save)
		       clear-text-saving-problems-were-encountered-p)))))
	(cond
	  #+development
	  ((and emit-lisp-p compiled-p)
	   nil)
	  (t
	   (reclaim-gensym-pathname temp-file-truename)))))))

(defun finish-current-kb-save-1 ()  
  (let ((reason-if-bad? (and (eq (format-for-kb-save current-kb-save) 'normal)
			     (check-frame-reference-balance-for-completed-save))))
    (cond
      (reason-if-bad?			; internal error -- should "never" happen
       (terminate-kb-save-or-backup current-saving-context
				    'failed-to-write-items reason-if-bad?))
      (t
       (unless (or (and (eq (format-for-kb-save current-kb-save) 'normal)
			(eq (funcall-to-write-to-kb-save-stream
			      #'write-final-plist-for-current-kb-save
			      'finish-current-kb-save
			      finish-current-kb-save-failure)
			    finish-current-kb-save-failure))
		   (eq (funcall-to-write-to-kb-save-stream
			 #'flush-kb-write-buffer
			 'finish-current-kb-save
			 finish-current-kb-save-failure)
		       finish-current-kb-save-failure)
		   (eq (funcall-to-write-to-kb-save-stream
			 #'flush-compiled-kb-write-buffer
			 'finish-current-kb-save
			 finish-current-kb-save-failure)
		       finish-current-kb-save-failure))
	 ;; We had no file system failure writing the last part of the KB, and
	 ;; we now think we're done writing to the file, we're ready to close
	 ;; the file cleanly, and ready to demolish all temporary structures.
	 (maybe-write-clear-text-diffs)
	 (setf (kb-transfer-stream-open? current-kb-save) nil)
	 (close-and-rename-kb-stream
	   (kb-transfer-stream? current-kb-save) nil
	   (kb-save-log-message-for-commit-after-saving-p current-kb-save))
	 (setf (kb-transfer-compiled-stream-open? current-kb-save) nil)
	 (close-and-rename-kb-stream
	   (kb-transfer-compiled-stream? current-kb-save) t nil)
	 (let ((module? (kb-module-being-saved? current-kb-save)))
	   (when module?
	     (update-saving-parameters-status-attributes module?))))))))


(defun make-description-text-line-for-kb-save (saving-context kb-save-if-known?)
  (tformat-text-string
    (if kb-save-if-known? "~a \"~a\"" "~a")
    (case (type-of-kb-save saving-context)
      (kb-save
       (if kb-save-if-known?
	   (if (string-equalw
		 (gensym-pathname-type
		   (kb-transfer-pathname kb-save-if-known?))
		 #w"kl")		; last vestige of kb/kl distinction!
	       #w"Saving knowledge library"
	       #w"Saving knowledge base")
	   #w"Saving"))			; improve by eliminating callers
					;   that activate this case!
      (kb-save-with-runtime-data #w"Snapshot of knowledge base")
      (runtime-data-only #w"Saving runtime data only")
      (ok-kb-save #w"Saving of OK knowledge base")
      (t #w"Backup of knowledge base"))
    (if kb-save-if-known?
	(kb-transfer-user-namestring kb-save-if-known?))))




;;; Check-frame-reference-balance-for-completed-save is to be called from
;;; finish-current-kb-save-or-backup to check the frame reference balance for
;;; the current save is 0.
;;;    
;;; If it is not, this represents an internal error, and should "never" happen.
;;; If it were to happen in a production G2, it would print a very long
;;; notification message, and signal an internal error, listing the names, or
;;; temporary names, of "blocks" not written.

(defun check-frame-reference-balance-for-completed-save
    (&aux (balance (frame-reference-balance current-kb-save)))
  (when (/=f 0 balance)
    ;; remember: should not be here -- it's an internal error.
    (loop for block being each class-instance of 'block
	  when (and (block-referenced-in-current-save-p block)
		    (not (block-written-in-current-save-p block))
		    ;; Don't collect junction-block defs in limbo
		    (or (not (frame-of-class-p block 'class-definition))
			(superblock? block)))
	    ;; In 3.0, the "using gensym-cons", and the reclaim below, was
	    ;; missing, causing there to be SI_cons messages.  (MHD
	    ;; 10/6/93)
	    collect block into referenced-blocks using gensym-cons
	  finally
	    (with-user-notification ()
	      (tformat "Warning: THIS KB WAS NOT SAVED CORRECTLY! ~
                        Please notify Gensym Customer Support of this internal ~
                        software problem: this save failed to write ~d items: " balance)
	      ;; GENSYMCID-1214: Error while saving KB
	      ;; print out items that cannot be saved (left items in the tree)
	      (loop for first = t then nil
		    for (block . calling-function) being each binary-tree-entry-cons
		      of (frame-reference-balance-tree current-kb-save)
		    do
		(unless first (tformat ", "))
		(tformat "~NF (class: ~a, calling by: ~a)"
			 block (class block) calling-function))
	      ;; then reference items of above items
	      (tformat "Referenced items: ")
	      (if (null referenced-blocks)
		  (tformat "none")
		  (loop for first = t then nil
			for block in referenced-blocks do
		    (unless first (tformat ", "))
		    (tformat "~NF (~a)" block (class block)))))
	    (reclaim-gensym-list referenced-blocks)
	    (return (twith-output-to-text-string
		      (tformat "failed to write ~d items." balance))))))

;; At an earlier stage we thought to remove this after the development of KB
;; save, but we've found this to be a useful, and inexpensive, safety device,
;; so we plan to leave it in in some form indefinitely. (MHD 1/6/93)



(defun defer-terminate-kb-save-or-backup
       (saving-context termination-reason? stream-error-message?)
  (cond
    ((null system-is-running)
     (terminate-kb-save-or-backup
       saving-context termination-reason? stream-error-message?))
    (return-from-save-to-caller-for-continuation?
     (setq current-saving-context? saving-context
	   kb-save-termination-reason? termination-reason?)
     (update-terminate-kb-save-stream-error-message stream-error-message?))
    (t
     (setf (need-to-call-terminate-kb-save? saving-context) t)
     (with-current-scheduling (continuation-task-for-current-backup 1)
       (terminate-kb-save-or-backup
	 saving-context
	 termination-reason?
	 stream-error-message?)))))




;;; `Terminate-kb-save-or-backup' is always done to end a save.
;;; Termination-reason?  is nil if successful; otherwise, it is a symbolic or
;;; numeric code (i.e., one needing no memory nmanagement).
;;; Stream-error-message?  is nil or a relevent message from the g2 stream.
;;; This happens when the backup has failed.  (If successful, then it happens at
;;; the beginning of the backup two hence.)

;;; Ownership of stream-error-message? is seized by this routine.

(defun-simple terminate-kb-save-or-backup
    (saving-context termination-reason? stream-error-message?)

  (when current-saving-context?

    ;; Only used here for error case; see finish-current-kb-save-1
    (when (or termination-reason? stream-error-message?)
      (notify-user-of-save-termination
	(make-description-text-line-for-kb-save saving-context nil)
	termination-reason? stream-error-message? nil))

    (when clear-text-saving-problems-were-encountered-p
      (notify-user "WARNING: There were problems saving some attributes in clear text ~
                    in the module~A ~(~L,A~).  These problems may prevent the kb ~
                    from being correctly loaded.  Please fix these problems now, ~
                    and save again."
		   (if (cdr clear-text-saving-problems-were-encountered-p) "s" "")
		   clear-text-saving-problems-were-encountered-p)
      (reclaim-gensym-list clear-text-saving-problems-were-encountered-p)
      (setq clear-text-saving-problems-were-encountered-p nil))

    (loop for display in (saving-context-kb-file-progress-displays saving-context)
	  do (note-update-to-file-progress display 'delete)
	     (delete-frame display))

    (with-saving-context (saving-context)
      (let ((kb-object-index-property-name
	      (kb-object-index-property-name current-kb-save)))
	;; Restore symbol-plists on indexed symbols:
	(delete-kb-object-index-property-names
	  kb-object-index-property-name
	  (symbols-with-earlier-kb-object-indices current-kb-save))
	(gensym-push kb-object-index-property-name
		     kb-object-index-property-name-pool))
      
      ;; Close down the display: (A subset of the displays in the context are
      ;; represented by this corresponding kb-save slot -- namely, those saves
      ;; that are read-only have no kb-saves.)
      (let ((display? (kb-transfer-kb-file-progress-display? current-kb-save)))
	(when display?
	  (setf (kb-transfer-kb-file-progress-display? current-kb-save) nil)))

      (let ((file-is-open?
	      (kb-transfer-stream-open? current-kb-save))
	    (stream? (kb-transfer-stream? current-kb-save))
	    (compiled-file-is-open?
	      (kb-transfer-compiled-stream-open? current-kb-save))
	    (compiled-stream? (kb-transfer-compiled-stream? current-kb-save)))
	
	;; We've saved off the last bit of information we need from the saving
	;; context structures.  Reclaim the saving context structures now:
	(reclaim-kb-save current-kb-save)

	;; The last thing we do is a file operation, if needed, that could abort.
	;; We avoid the hassle of an unwind protect by saving that work for the
	;; end.      
	(when (and file-is-open? stream?)
	  ;; In case of the save failing, close the file:
	  (gensym-close-and-delete-file stream?))
	(when (and (or compiled-file-is-open? delete-compiled-kb-source-p)
		   compiled-stream?)
	  (cond
	    #+development
	    (emit-lisp-p
	     (delete-file compiled-stream?))
	    (t
	     (gensym-delete-file compiled-stream?))))))
    
    ;; Get this task out of the scheduler/inference engine/frame system:
    (setq save-kb-state-for-system-procedure-save nil)
    (cancel-task continuation-task-for-current-backup)      
    (setq current-saving-context? nil)      
    (setq noting-changes-to-kb-p nil)	; See NOTE 1 below
    (when (save-permanent-data? saving-context)
      (change-all-permanently-changed-things-are-marked
	(if termination-reason? nil t)))
    (when return-from-save-to-caller-for-continuation?
      (setq kb-save-termination-reason? termination-reason?)
      (setq return-from-save-to-caller-for-continuation? nil))

    (reclaim-saving-context saving-context)))

;; NOTE 1: when journalling is implemented, the value of noting-changes-to-kb-p
;; should be restored according to whether changes are being noted for
;; journalling or backup purposes. For now, this is always set back to NIL.
       
;; NOTE 2: jh&mhd, 6/2/92: If this is a save that succeeded, we have already
;; called flush-kb-write-buffer right after writing the final plist; otherwise,
;; we end up not caring about flushing the write buffer.  That's why we don't
;; call (flush-kb-write-buffer) here.



;;; `Notify-user-of-save-termination' ... save-description-text-line should
;;; be a string naming the type of save and the namestring, such as
;;;
;;;    Saving Knowledge Base "/home/mhd/xyz.kb"
;;;
;;; In the case of a failure, this reports something like
;;;
;;;    Saving Knowledge Base "/home/mhd/xyz.kb" did not
;;;    complete! Problem: Permission Denied
;;;
;;; Generally, save-description-text-line should be created by a call to
;;; make-description-text-line-for-kb-kb-save.
;;;
;;; If stream-error-message? is nil, the save is considered successful.  If not,
;;; stream-error-message? should if at all possible be supplied as a text string
;;; providing a meaningful explaining the message, or giving the Operating
;;; System message in its original form (translated to the Gensym character set,
;;; of course).  If the message string is unavailable, the termination reason,
;;; which should be somewhat descriptive, will be printed instead.
;;;
;;; This also sets terminate-kb-save-stream-error-message? to either nil or the
;;; error message used in the error case (the part after "Problem: " in the
;;; example above).
;;;
;;; The string arguments, save-description-text-line and stream-error-message?,
;;; are reclaimed or incorporated by this function.

(defun notify-user-of-save-termination
    (save-description-text-line termination-reason? stream-error-message?
				clear-text-problems-p)

  (let ((error-text-string?
	  (if termination-reason?
	      (tformat-text-string
		  "~a"
		(or stream-error-message? termination-reason?)))))
    
    
    ;; Tell the user what's happened:
    (cond
      (termination-reason?
       (unless suppress-notification-for-kb-save?
	 (notify-user
	   "WARNING: ~a did not complete. Problem: ~a"
	   save-description-text-line error-text-string?)))
      (t
       (notify-user
	 (if clear-text-problems-p
	     "~a completed successfully, but there were problems saving some attributes"
	     "~a completed successfully")
	 save-description-text-line)))

    ;; Reclaim save-description-text-line and stream-error-message? if appropriate.
    (reclaim-text-string save-description-text-line)
    (update-terminate-kb-save-stream-error-message error-text-string?)))

;; What do other systems do:
;;
;;   Emacs:
;;
;;     I/O error writing xxx.text: I/O error
;;     
;; Comment: I think it's short and to the point, but we
;; want to avoid the term error, because it's negative, and
;; I/O, because it's jargon.  So we say instead: "saving did not
;; complete! Problem:".
;;
;;   MSWord:
;;
;;     Dialog, e.g.,
;;
;;       The destination disk is full. Please insert another diskette.
;;                               [ok/cancel]
;;
;; Comment: would be nice.





;;; `Update-terminate-kb-save-stream-error-message' sets the value of the
;;; special variable terminate-kb-save-stream-error-message? to the argument
;;; stream-error-message?.  If it represents a new (non-EQ) value, and the old
;;; value is a string, it also reclaims the old value.

(defun update-terminate-kb-save-stream-error-message (stream-error-message?)
  (when (and terminate-kb-save-stream-error-message?
	     (not (eq stream-error-message? 
		      terminate-kb-save-stream-error-message?)))
    (reclaim-text-string terminate-kb-save-stream-error-message?))
  (setq terminate-kb-save-stream-error-message? stream-error-message?))




(def-bombout-clean-up-function 'terminate-kb-save-or-backup-if-error-occurs)

(defun terminate-kb-save-or-backup-if-error-occurs ()
  (cond
    (current-saving-context?
     (terminate-kb-save-or-backup
       current-saving-context?
       'error-writing-file
       nil))
    (t
     ;; reset all the random globals from SETS, used for saving
     ;; while running from system procedure:
     (setq return-from-save-to-caller-for-continuation? nil)
     (setq kb-save-termination-reason? nil)
     (setq suppress-notification-for-kb-save? nil)
     (setq terminate-kb-save-stream-error-message? nil)
     (setq save-kb-state-for-system-procedure-save nil))))

(defun cleanup-kb-save-or-backup-if-necessary (x)
  (declare (ignore x))
  (terminate-kb-save-or-backup-if-error-occurs))






;; Notes on dealing with changes while saving:
;; 
;; when noting-changes-to-kb-p
;;       connection has been touched
;;       output-end-object has been touched -no- just for transferts
;;       not transient of output-end-object
;;       not connection-transient-p connection










;;;; Permanent blocks

;;; All blocks must be categorized as being
;;; (1) Transient blocks.
;;; (2) Permanent blocks.
;;; (3) Neither transient nor permanent. 

;;; A block may not be both transient and permanent.

;;; Permanent blocks have the frame-flag permanent-block.
;;; Transient blocks have the frame-flag transient.

;;; A transient block is one that is created by an explict user
;;; CREATE command, blocks inferior to a transient block, and
;;; loose ends opposing transient blocks.

;;; A permanent block is a block which is inferior to a
;;; permanent block, or one of the following: format-frames,
;;; system-frames, class-definitions and top-level kb-workspaces.

;;; A block is inferior to another block in one of the following ways:
;;; (1) As a subblock of a block.
;;; (2) As an input connection to a block.
;;; (3) As a subworkspace of an entity.
;;; (4) As an embedded rule of an action-button or user-menu-choice.
;;; (5) As a simulation frame of a variable.
;;; (6) As a user defined attribute of a block.

;;; There are two exceptions to the above:
;;; (1) The inferior block may be transient and its superior
;;;     permanent. (But not visa-versa.) This happens when a transient
;;;     item is placed on a permanent kb-workspace, or a permanent item is
;;;     given a transient subworkspace, for example.
;;; (2) A block marked do-not-save-in-kb is not treated as a inferior.
;;;     This is done for certain blocks not viewed as part of the user's
;;;     permanent or transient state. It would not be harmful to mark
;;;     any such block (e.g. a menu) with this flag, but it is necessary
;;;     to do so if the block is placed in the KB hierarchy, for example, as
;;;     a subblock of something permanent or transient.

;;; It is important that the permanent-block and transient frame-flags
;;; be maintained. This is done as follows:

;;; (1) The creation of top-level kb-workspace does set-permanent-block.
;;; (2) Whenever a block is made inferior to another block by any
;;;     of the listed methods above,
;;;     (add-as-subordiante-block inferior superior) is called. This
;;;     will copy the appropriate flag. This has been done in add-sbblock,
;;;     make-new-connection-frame-for-connection,
;;;     go-to-maybe-newly-created-subworkspace,
;;;     put-embedded-rule?, put-embedded-rule-in-user-menu-choice?,
;;;     put-simulation-frame?, and put-attribute-value.

;;; Please help to maintain this.


;; Note: In ACTIVATE, the notion of inferior and superior has a slightly
;; different definition. We should consider changing it to make the two
;; consistent. The difference is that connections are defined (in ACTIVATE) to
;; be inferior to the workspace they are drawn on rather than as inferors of the
;; block to which they are an input connection. 




;;;; Noting changes

;;; In order to journal effectively, and to save a KB while running, it is
;;; necessary to intercept the mutation of any kb-savable slot of any permanent
;;; or transient frame.  This must be done without seriously impeding the
;;; performance of G2.

;;; Changes to kb-savable slots of blocks are handled automatically whenever a
;;; setf is done to the slot.  However mutation of the value of a slot other
;;; than by setf, change-slot-value, set-slot-value, and slot-putters will
;;; escape this mechanism.  In particular, changes to inferior structure are
;;; of concern.  A dependent-frame is a inferior structure.  When making
;;; noteworthy changes to dependent frames, it is necessary to note that the
;;; block it is dependent on has changed.  This must be done by calling
;;; (note-change-to-block parent-block slot-name) where slot-name is the slot that the
;;; dependent frame is reachable from.  This call need not be made if (null
;;; noting-changes-to-kb) or if parent-block is nether transient or permanent.
;;; It is not a mistake to call it in any case.

;;; Generally, it is worthwhile to make the (null noting-changes-to-kb) test.
;;; This prevents a function call whenever the user is not interested in the
;;; journal facility (except when a save while running is happening).  Testing
;;; for permanent and transient flags is not being done before the function
;;; call.  I believe that there is little efficiency gain here, and if this test
;;; was built into every setf, it would significantly expand the code.  (We will
;;; test my assumption that most changes to savable slots are to permanent or
;;; transient frames.)




;;; Detailed Documentation on Noting Changes:

;;; add-as-inferior-block is called by all placements into the traversal
;;; hierarchy. See its documentation for details. It does not figure in the
;;; real-time aspects of saving.




;;; note-change-to-connection

;;; Called whenever a connection has a savable modification. Called by various
;;; defsetfs of the connection structure, and change-connection-attribute.




;;; note-change-to-block called from setfs of savable slots and by
;;; delete-connection-in-block, add-connection-in-block, and
;;; replace-connection-in-block. 


;;; How to save consistent at beginning:

;;; Before save, traverse the hierarcy, clear-block-has-been-referenced,
;;; clear-block-has-been-written, set-block-existed-at-start-of-save.

;;; The purpose of block-existed-at-start-of-save is to find out if a block was part of
;;; the traversal hierarchy at the start of the traversal without traversing the
;;; hierarchy. This is the only way to know whether there is a need to save
;;; immediately.

;;; While traversing, requirements for writing are permanent-block, not
;;; block-as-been-written, and block-existed-at-start-of-save.

;;; When a modification occurs, write block before modification, and get its
;;; subordinates before modification.

;;; Connections are treated similarly.

;;; Upon writing, block-has-been-written is set.

;;; If a block is deleted, and it is permanent, has not been written, and
;;; existed at start, then it must be written before deletion.

;;; If a change is reversible, there is no need to take action at this point.


;;; How to note all permanently changed frames:

;;; There are flags block- permanently-changed and
;;; connection-permanently-change.  They are not savable.  There is a global
;;; variable all-permanently-changed-things-are-marked.  If true, it must be the
;;; case that every permanent block that has permanent modifications is so
;;; marked.

;;; All-permanently-changed-things-are-marked becomes true:
;;;    (1) After load (not merge). (Because there are none.) -done-
;;;    (2) After successful save. (Again because there are none.) -done- 
;;;
;;; All-permanently-changed-things-are-marked becomes false:
;;;    (1) If journalling turned off. (Because marking is not occuring.) -done- 
;;;    (2) After merge. (Because there is no single KB that correspnds to what is
;;;       now loaded, except for marked things.) -done-
;;;    (3) After incomplete or failed save. (Because it cleared marks.) -done-

;;; Things are set as permanently changed:
;;;    (1) When established as permanent.
;;;    (2) When permanent and modified.

;;; Things are cleared as permanently changed.
;;;    (1) When written to a save of the whole KB.


;; May 2, 1991 Plan for incremental save (backup)

;; 1. noting-changes-to-kb-p always true when journalling enabled. -done-
;; 2. extra slot with value of All-permanently-changed-things-are-marked -done-
;; 3. When noting changes, mark as changed. -done-
;; 4. Status of all-permanently-changed-things-are-marked as above. -done-
;; 5. When deleting a modified frame, note fsn on a list.

;; 7. A version of save that saves only what has been modified or deleted. -partially-
;; 8. A way to merge it in. (No changes to fsn). It deletes. Needs to have a
;;    fsn map for getting and deleting. Otherwise, when a frame comes in and
;;    exists, the replacements are done to it. (Are there order dependency
;;    problems?) What happens when references are made to non-existent things.
;;    This takes us only through the permanent clip.

;; May 24 notes:

;; The only known bug in the generation of a backup is that new stubs are not
;; being marked as permanently-changed.  This was fixed temporarily, but not in
;; sources.  There is still a problem in loading. It is corrupt.  -fixed- 5/28

;; 1. Does delete-frame work properly for a connection frame?

;; 2. Does change-slot-value reclaim properly?

;; Observed backup merging bugs. 5.28 -all fixed-
;;   1. Result had blank connection. Result of bug 1 above.
;;   2. extra connections floating around
;;   3. connections slot was confused. Is there a mapping problem?
;;   4. connections slot spelled out something with 27 letters 3 times.
;;      This was on a default-junction and may have been the port names.

;; Observed bugs, May 30:
;; Why did save while running not write connections?
;; Need a solution to the pane-description problem.
;;    Write #\P pane desc. after finishing defs.
;;    Note that no kb-workspace may be modified till then. But could it be
;;    deleted. Aparently so. Need better solution.
;; Is finished-writing-definition? set too early?
;; Reinstate the reference count after checking its logic.

;; June 4, 1991
;;   Unable to handle definitions in a backup at all!!!
;;     One solution: Prohibit significant changes to defns.
;;     For example, can we handle changing the class of items??
;;       What are the consequences to non-frame data by changing the
;;       names of existing items. Class emebrship lists. Cached chaining?
;;     If a definition suffers a name change, how do we handle existing items.




;;; Reversible-changes:

;;; A grep on 4/16/91 showed the following calls to note-kb-state-change.
;;; ACTIONS			change-system-attribute
;;; 				now-change-system-attribute needs one!!
;;; BOOKS                       change-text-of-message
;;; BOXES			change-color-of-text-box
;;; CONNECT2			change-color-pattern-of-connection
;;; 				change-color-of-connection
;;; 				rotate-and-reflect-icon
;;; DRAW			change-size-of-workspace-to-minimum
;;; ENTITIES			change-color-of-icon, change-color-of-icon
;;;                             change-color-pattern-of-icon
;;; PANES			change-color-of-workspace
;;; PROC-EVAL			execute-change-system-attribute-instruction
;;; STACK-ACTS			change-system-attribute
;;;                                    (def-funcalled-instruction)
;;; TABLES			change-color-of-text-cell





#+development
(defun permanently-changed-blocks ()
  (loop for block being each class-instance of 'block
	when (block-permanently-changed-p block)
	  collect block))


#+development
(defun find-block-or-connection (fsn)
  (loop for block being each class-instance of 'block
	do
    (when (=f fsn (frame-serial-number block)) (return block))

    (loop for connection being each input-connection of block
	  do
      (when (frame-serial-number-equal fsn (frame-serial-number-for-connection connection))
	(return-from find-block-or-connection connection)))))


#+development
(defun c32r (string)
  (loop with result = 0
	for i below (length string)
	do
    (setq result (+f (*f result 32) (digit-char-p (aref string i) 32)))
	finally (return result)))




;;; To do:

;; 1. Get real time as double float should be put into clocks. -done-
;; 2. The time is repeated at the end. It could be used as a security check. -first done-
;; 3. Unkludge in execute-file-command. MHDF
;; 4. Backup should have different name as save, and shoukld end in bk. -work with MHD-
;; 5. Ask user box "Save [backup] file as..."



;;; June 14, 1991 Notes on traversal and permanent.

;;; The traversal hierarchy must observe the following constraints.
;;; (1) If an item is permanent, its superior if any must be permanent.
;;; (2) If a thing is transient, its superior if any must be transient or
;;; permanent.
;;; (note that a thing which is neither is not properly part of the KB to be
;;; saved at any time.)

;;; Clipping: Saving-transients? is a mode switch which is set during a save.
;;; When it is nil, clipping must eliminate transients. Otherwise clipping must
;;; include transients. It must never include the neither case.

;;; Instances of clipping:
;;;   (1) traverse-kb-for-saving
;;;   (2) note-change-to-block
;;;   (3) note-deletion-of-block (see connection-should-be-written-p)
;;;   (4) slot clipping in write-frame-for-kb
;;;          stack-of-subblocks
;;;          subblocks (write-slot-group-for-block?)
;;;          frame-representations
;;;          to which should be added connections


;; Notes from 6/24/91 on saving runtime data.

;; 1. Format for frame needs fixing because it is F fsn [..!
;;    The problem is that a class is expected after fsn. 

;; 2. Format for connection is worse. C fsn in some cases.

;; 3. Perhaps the class is always needed. In the connection case,
;;    one must look ahead for [. Once reading [, perhaps it must then look for !.

;; 4. Consider what else needs to be present to record runtime data. Not
;;    original-kb-state-plist-written?, but all slots referenced by it so
;;    as to record their current values? Is there an assumption when saving data
;;    only that no permanent changes have occurred? How can we know that? Should
;;    it refuse to work if permanent  changes have occurred? No easy way to know
;;    this because some transient changes appear to be permanent, such as adding
;;    transient subblocks, changing things that revert via
;;    original-kb-state-plist-written?, etc.

;; 6/25/91

;; So:  F fsn {all else} {[ ... } !
;;      C fsn {7 elements} {[ ... !}

;; But need to avoid empty forms such as F fsn ! or F fsn [ !

;; 1. For saving while running, need to note changes when changing the runtime
;; data.

;; Types of runtime data:
;;    Current value and history: put-current-value, conclude having no value?
;;    Same for simulator

;; Relation changes

;; Arrays, lists changes:

;; Only while saving live data is it necessary to note change to frames.



;; 6/26/91
;; Filling an array.

;; (make-or-reformat-cascaded-ring-buffer nil n nil) = cascaded-ring-buffer
;; (setf (variable-or-parameter-stored-histories? variable-or-parameter)
;; (setf (simulation-stored-histories? variable-or-simulation-subtable)

;(store-new-element-in-history-cascaded-ring-buffer
;	    cascaded-ring-buffer
;	    new-element-value
;	    new-element-time)

;; Initialization considerations for simulator. AGH to think about...


;; Put simulation value into (simulation-value and (new-simulation-value
;; of (simulation-runtime-information? var-or-param). Else error.





;; store-managed-number-or-value

;; update-variable put notification for runtime data

;; To put current simulation value...


;; 6/28/91

;; Transient items are not so labeled when they are written because
;; transient-flag is not savable. Need to indicate transient.

;; Some violations of note-change.. icon-attributes-plist

;; It would be useful if reversible changes were marked as reversible.
;; Also, data changes should be marked as reversible.


;; ML to do list of 9/4/91

;; 1. A kb was saved while running. The name-box of a definition did not get
;; saved. -done-

;; 2. Make a good detector of saving that does not write out referenced frames. -done-

;; 3. Merging appears to have multiple images of workspaces. -improvement- MHD must fix.

;; 4. numbers-of-frames-and-connections-written has no purpose. Remove it. -done-

;; 5. Frame-reference-balance and referenced-but-not-read should be removed. -done-

;; 6. Is it possible to decide not to write out a connection frame or an
;; attribute, and then because it is modified, write it out after all.
;; Logically, can we treat and mark such frames as if written? -done-

;; 7. existed-at-start is not being used. Is it possible to create a case where
;; new stuff is added and then gets written out? -not so far-

;; 8. Is there a load problem with cached chainig lists?

;; 9. Neaten up diagnostics.

;; 10. Format-frame duplication. Not easy to demonstarate.

;; 11. But problem with graph-formats.

;; 12. "clear KB problem"

;; 13. Transients not being iterated over correctly in traverse-kb-for-saving.
;; Need to have the full range of items, but not to include
;; procedure-invocations.  -done-

;; 14. What happens if a transient dynamic-relation is referenced as an
;;     attribute-value (?), via a relation instance, within a list, etc. Are any
;;     of these possible?

;; 15. Improve attribute-collector efficiency to not bind global variables all
;; the time.

;; 16. Slot-putter g2-expression-cell-chaining-links. Why is this not a general
;; problem?!!





;; 17. Load >ml>mill. Start. Save while running. Delete factory floor while
;; saving. frame-reference-balance = 2. 

;; Any referenced frame should be (1) rejected by collect-attribute-if-savable
;; for not having slots to save, or (2) be traversed by
;; continue-kb-save-or-backup, or (3) processed by
;; write-block-as-it-is-now. Cases 1 and 2 are disjoint, but case 3 may happen
;; before either of the other two happen. 

;; write-frame-for-kb for blocks is called only from write-block-as-it-is-now,
;; and continue-kb-save-or-backup.

;; The control against either writing twice or writing after a block has been
;; determined not to have slots to save (attributes and connection frames only),
;; is to mark as written immediately before calling write-frame-for-kb, or
;; immediately upon determining that there are no slots to save.

;; The requirement that the first reference if it preceeds the write, or if
;; there is to be no write should be #\G form is: If not referenced, then use
;; #\G. Therefore, a frame is marked as referenced upon writing a #\G reference,
;; and upon writing it, but not upon deciding not to write it. 

;; frame-reference-balance is incremented per #\G, but not if the frame has
;; already been marked as written.  (This is a transition from 00 to 10.) Such a
;; frame has not been written, and has not been determined as not having slots
;; to save.  Upon determining that it has no slots to save, frame-reference
;; balance must be decremented.  (The flags change from 10 to 11 at this time.
;; If the frame has already been written, then this decrementing should not take
;; place.) When a frame that has been referenced is written,
;; frame-reference-balance also decrements.  (This is also a transition from 10
;; to 11.) 

;; Problem was resolved. The key change was to write-reference-to-frame, to have
;; it only increment if block has not been written. (Also changed the guard for
;; the decff in collect-attribute-if-savable. But this was not important.) The
;; following transitions are now defined.

;; Increment when transition from 00 to 10. This is write-reference-to-frame.
;; Decrement when transition from 10 to 11. This is in two places,
;; write-frame-for-kb (which is called only if one has just transitioned from 00
;; to 01 or from 10 to 11. It has a guard on the decff to only decrement if the
;; latter.) and in collect-attribute-if-savable.

;; This is how the bug happened:
;; 00      write-block-as-it-is-now
;; 01        set-block-has-been-written
;;             write-frame-for-kb
;; 11  +1         (write-reference-to-frame self) (Now guarded against.)
;; 11        set-block-has-been-referenced

;; What is the reason for not setting has-been-referenced until after return
;; from write-frame-for-kb? (Happens from write-block-as-it-is-now and
;; continue-kb-save-or-backup.) [Maybe an obsolete comment. -ml, july '93]

;; These notes have important documentation which should be saved.

;; 18. The current method of assigning object index numbers to symbols is
;; somewhar wasteful. There are two assignments in use at any time - one for
;; each saving context. Each one maintains a property on every symbol written to
;; a KB, and also keeps a list (symbols-with-earlier-kb-object-indices
;; current-kb-save) which is part of the context. Total: 6 conses per symbol.
;; Is there a better way? The requirements are that for each of two saving
;; contexts, one must know when the symbol is being written for the first time.
;; This is independent of the index number, which needs not be different for the
;; two contexts. So if properties are being used, either one has to keep a list
;; of symbols with the property for each context, or one has to tour all such
;; symbols. Visiting all symbols is prohibitive, but a single list for both
;; contexts would suffice. I.e., there is only a single list
;; (symbols-with-earlier-kb-object-indices current-kb-save). It lists all
;; symbols with an object-index property. There is only one such property
;; (except for LISPMs) and it is a number with some extra bits to mark whether
;; each context has written the symbol out. The cleanup is no longer than
;; before, you have to traverse the list, and work on the property of each
;; symbol. But you don't reclaim the property or take the symbol off the list
;; for the life of the symbol. If symbols become reclaimable, then a reclaimed
;; symbol must come off the list. But this could be done as an occasional batch
;; operation.

;; Another alternative is not to use sybols, but to use a random access map such
;; as a balanced tree and/or hash table. This is probably slower each time a
;; symbol is written, but might use less storage. 



;;;; Noting changes


;;; The `handle-change-or-deletion-fanout' method is called on subclasses of
;;; block from note-change-or-deletion.  All subclasses of block that refine its
;;; definition must, by convention, funcall their superior's method.  [Change as
;;; of 9/21/94 in pre-beta. (MHD 9/21/94)]
;;;
;;; It is called with the one additional argument
;;; slot-name-or-t-in-change-case?, the same argument documented for
;;; note-change-or-deletion.  This is only called within a saving-context
;;; dynamic extent, i.e., with current-saving-context bound.
;;;
;;; This may need to take special action to ensure that related elements of the
;;; KB get saved out before a change or deletion takes place.
;;;
;;; If it calls note-change-or-deletion recursively, it should normally pass in
;;; the value t, indicating that it's a change, even if the ultimate original
;;; call was for a deletion.
;;;
;;; This method is called as, and so must be coded as, a simple method, i.e.,
;;; having a fixed number of arguments, and not returning more than one useful
;;; value.  The spec for the method does allow for the implementation to meet
;;; these requirements.

(def-generic-method handle-change-or-deletion-fanout
    (block slot-name-or-t-in-change-case?))

;; At present, specific methods are defined for BLOCK, DEFINITION, RELATION, and
;; MODULE-INFORMATION.  The definitions are in the modules for each class's
;; definition, at least when possible: they are here in cases where they cannot
;; be there due to forward reference/load ordering issues.


;;; The `handle-change-or-deletion-fanout method for block' ...

(def-class-method handle-change-or-deletion-fanout
    (block slot-name-or-t-in-change-case?)
  ;; supreme class's method, so no funcall to superior's method
  (when (and (kb-module-being-saved? current-kb-save)
	     (null slot-name-or-t-in-change-case?))
    (remove-block-from-module block)))



;;; The `handle-change-or-deletion-fanout method for workspace' ...

(def-class-method handle-change-or-deletion-fanout
    (workspace slot-name-or-t-in-change-case?)
  (funcall-superior-method workspace slot-name-or-t-in-change-case?)
  (when (and (kb-module-being-saved? current-kb-save)
	     (eq slot-name-or-t-in-change-case? 'module-this-is-part-of?))
    (remove-block-from-module workspace)))



;;; The `handle-change-or-deletion-fanout method for module-information' ...

(def-class-method handle-change-or-deletion-fanout
    (module-information slot-name-or-t-in-change-case?)
  (funcall-superior-method module-information slot-name-or-t-in-change-case?)
  (when (and (eq slot-name-or-t-in-change-case?
		 'top-level-kb-module?)
	     (kb-module-being-saved? current-kb-save))
    ;; If we're saving a module, we need to save out every block in this module.
    ;; Note that this will ultimately reach every connection, too.  
    (loop with module = (kb-module-being-saved? current-kb-save)
	  for block being each class-instance of 'block
	  when (within-module-p block module) ; improve speed of this test!
	    do (note-change-or-deletion block t))))

;; Needs to be here because it references the accessor macro
;; kb-module-being-saved?. (MHD 5/24/94)

;; Perhaps this could be improved with a bit of work.  The within-module-p
;; predicate should either be speeded up, or replaced with some faster test.
;; Perhaps, a special-purpose dynamic extent can be set up to that makes the
;; test faster, e.g., by copying module information down to subworkspaces, to
;; all levels.



;;; The `handle-change-or-deletion-fanout method for relation' ...

(def-class-method handle-change-or-deletion-fanout
    (relation slot-name-or-t-in-change-case?)
  (funcall-superior-method relation slot-name-or-t-in-change-case?)
  (when (save-runtime-data? current-saving-context)
    (note-change-to-all-related-items relation)))

;; Needs to be here because it references the accessor macro save-runtime-data?.
;; (MHD 5/24/94)







(defun-simple note-change-to-runtime-data-for-block-1 (block)
  (when (and current-saving-context?
	     (save-runtime-data? current-saving-context?))
    (note-change-to-block-2 block 'runtime-data)))


(defun-simple save-block-for-change-p (block)
  (and (block-should-be-written-p block)
       (or (save-permanent-data? current-saving-context)
	   (and (eq (type-of-kb-save current-saving-context) 'backup)
		(block-permanently-changed-p block)))))


(defun-simple block-should-be-written-p (block)
  (and (saving-is-started? current-kb-save)
       (block-existed-at-start-of-save-p block)
       (not (block-written-in-current-save-p block))))


(defun-simple save-connection-for-change-p (connection-structure)
  (and (connection-should-be-written-p connection-structure)
       (or (save-permanent-data? current-saving-context)
	   (and (eq (type-of-kb-save current-saving-context) 'backup)
		(connection-permanently-changed-p connection-structure)))))


(defun-simple connection-should-be-written-p (connection-structure)
  (and (saving-is-started? current-kb-save)
       (connection-existed-at-start-of-save-p connection-structure)
       (not (connection-has-been-written-p connection-structure))))


(defun-void note-change-to-block-2 (block slot-name?)
  (note-change-or-deletion block (or slot-name? t))) ; require slot-name!

(defun-void note-deletion-of-block-2 (block)
  (note-change-or-deletion block nil))


(defun-void note-change-to-connection-2 (connection-structure)
  (note-change-or-deletion connection-structure t) ; add slot-name arg!
  (when (not (symbolp (connection-frame-or-class connection-structure)))
    ;; Is this necessary? Sadly, I think so.  Traverse-kb-for-saving
    ;; doesn't treat connection frames a subpart of connections, but
    ;; as a peer -- they're included in the saving list in parallel.
    (note-change-or-deletion
      (connection-frame-or-class connection-structure)
      t)))

(defun-void note-deletion-of-connection-2 (connection-structure)
  (note-change-or-deletion connection-structure nil))



;;; `Note-change-or-deletion' ... Slot-name-or-t-in-change-case? should either
;;; be the name of a slot being changed, T, if some slot is being changed, or
;;; some other "change" is happening besides a deletion of block-or-connection.
;;; Slot-name-or-t-in-change-case? should only be nil in the case where
;;; block-or-connection is being deleted.

(defun-void note-change-or-deletion
    (block-or-connection slot-name-or-t-in-change-case?)
  (when (and current-saving-context?
	     (not (block-that-draw-function-may-modify-p block-or-connection))) 
    (let ((block-case? (framep block-or-connection)))
      (with-saving-context (current-saving-context?)
	(when (and (eq (format-for-kb-save current-kb-save) 'normal)
		   (if block-case?
		       (collectable-block-p block-or-connection)
		       (collectable-connection-p block-or-connection))
		   (or (null (kb-module-being-saved? current-kb-save))
		       (if block-case?
			   (within-module-p
			     block-or-connection
			     (kb-module-being-saved? current-kb-save))
			   (connection-within-module-p
			     block-or-connection
			     (kb-module-being-saved? current-kb-save)))))	  
	  (when (if block-case?
		    (save-block-for-change-p block-or-connection)
		    (save-connection-for-change-p block-or-connection))
	    (continue-current-kb-save block-or-connection))
	  ;; Even if we don't need to save, we still need to handle the fanout,
	  ;; since it varies, potentially, on a slot-by-slot or delete vs. slot
	  ;; basis.
	  (when block-case?
	    (funcall-simple-method-if-any-macro
	      'handle-change-or-deletion-fanout
	      block-or-connection
	      slot-name-or-t-in-change-case?))))
      (cond
	(slot-name-or-t-in-change-case?
	 (if block-case?		; see NOTE
	     (set-block-permanently-changed block-or-connection)
	     (set-connection-permanently-changed block-or-connection)))
	(t				; deletion case	
	 (when (and all-permanently-changed-things-are-marked
		    (if block-case?
			(frame-has-not-been-reprocessed-p
			  block-or-connection
			  basis-kb-frame-serial-number)
			(connection-has-not-been-reprocessed-p
			  block-or-connection
			  basis-kb-frame-serial-number)))
	   (add-deleted-item-to-list block-or-connection block-case?)))))))

;; NOTE: Flaw in logic. What we really want to do if a backup is in progress is
;; get this frame marked for the next backup. This would fail if the block
;; is changed twice during a backup.!! (ML)











;;;; Notes on Testing


;;; A procedure to test incremental save while running:
;;;
;;; (1) Load KB "/gensym/ut/g2-30r3/kbs/kb-tools.kb"
;;;
;;; (2) Start G2
;;;
;;; (3) Break into Lisp, and evaluate
;;;
;;;       (setq save-only-if-interrupting? t)
;;;
;;; (4) Save KB "/home/mhd/tmp/", including all required modules
;;;
;;; (5) Go to Inspect, and enter the command
;;;
;;;    show on a workspace every kb-workspace K such that the
;;;    item superior to K does not exist
;;;
;;; (6) Go to each workspace whose minitable appears, starting
;;;     at the top, and proceeding to the bottom.
;;;
;;;     For each workspace, after going to it, delete it using
;;;     the delete-workspace menu command.
;;;
;;; (7) If the KB doesn't save itself out completely in the course
;;;     of doing the deletion, that's strange.
;;;
;;; (8) If you pause the KB, it should certainly then save without
;;;     a hitch; if not, that's a bug.
;;;
;;; [As of 2/24/94, this is a bug.  You get a bombout after step
;;; (8), with this printed:
;;;
;;; 
;;;    >>Error: This save failed to write 19 blocks.
;;;             referenced-blocks: 
;;;
;;;    CHECK-FRAME-REFERENCE-BALANCE-FOR-COMPLETED-SAVE:
;;;    :C  0: continue
;;;    :A  1: Abort the EXECUTE-MENU-CHOICE event handler
;;;    2: Try loading "/home/mhd/lisp-init" again
;;;    3: Abort to Lisp Top Level
;;;
;;;   -> :b
;;;   CHECK-FRAME-REFERENCE-BALANCE-FOR-COMPLETED-SAVE <- FINISH-CURRENT-KB-SAVE-1
;;;   <- FUNCALL-TO-WRITE-TO-KB-SAVE-STREAM <- FINISH-CURRENT-KB-SAVE
;;;   <- FINISH-CURRENT-KB-SAVE-OR-BACKUP <- CONTINUE-CURRENT-KB-SAVE-OR-BACKUP
;;;   <- EXECUTE-TASK-OUT-OF-ORDER <- COMPLETE-SAVE-AFTER-RUNNING-IF-NECESSARY
;;;   <- SYSTEM-PAUSE <- ...
;;;
;;;   (MHD 2/24/94)]
;;;
;;;   [-- regarding the above bug: what's being said is that the _count_ of
;;;   unwritten blocks is 19, but that there are no blocks that have the
;;;   referenced bit set without the corresponding written bit.  This could be a
;;;   red herring. Something smells fishy.
;;;
;;;   What could cause this?
;;;
;;;        -- deleting things that have the referenced bit set, but not the
;;;        written bit set, without without decrementing the reference balance?
;;;
;;;        ]





;; MK's GDA KB has a block that is the input-end-object of a connection but
;; has NIL as its CONNECTIONS slot value, and nil as SUPERBLOCK? slot value!
;; 
;; This was developed in 3.0.

;; To fix MK's GDA KB:
;;

;#+development
;(defun fix-gda-kb ()
;  (let* ((block
;             (loop for block being each class-instance of 'gdl-data-path-connection-post
;                   when (null (superblock? block))
;                     return block))
;         (connection
;           (loop for c being each class-instance of 'gdl-date-path
;                 when (eq (input-end-object (connection-for-this-connection-frame c))
;                          block)
;                   return c)))


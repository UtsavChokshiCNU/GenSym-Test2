;; Patches to XEmacs 19.12


;; Turn off the annoying minibuffer-electric-slash.
;; It's annoying because you cannot undo its effect.

(define-key read-file-name-map "/" 'self-insert-command)
(define-key read-file-name-must-match-map "/" 'self-insert-command)



;; They removed this function (used by ilisp-out).
(defun window-edges (window)
  (window-pixel-edges window))


;; Changes +2 to +3 -- 19.12's 3d modeline clips off some pixels,
;; or turn off the 3D mode line:
;;       (set-specifier modeline-shadow-thickness 0)

(defun ilisp-needed-window-height-for-19-12 (window)
  (save-window-excursion
    (select-window window)
    (save-excursion
      (set-buffer (window-buffer))
      (+ 3 (save-excursion 
	     (goto-char (point-min))
	     ;; Any upper bound on the height of an emacs window will
	     ;; do here.  How about 1000.
	     (vertical-motion 1000))))))


;; Seems to have changed its default value.
(setq comint-always-scroll t)


;; They renamed these functions.
(defun mouse-track-beginning-of-word (symbolp)
  (default-mouse-track-beginning-of-word symbolp))

(defun mouse-track-end-of-word (symbolp)
  (default-mouse-track-end-of-word symbolp))



;; Somebody had changed (sit-for 0) to (sit-for 1)

(defun kill-ring-save (beg end)
  "Save the region as if killed, but don't kill it.
This command is similar to `copy-region-as-kill', except that it gives
visual feedback indicating the extent of the region being copied."
  (interactive "r")
  (copy-region-as-kill beg end)
  ;; copy before delay, for xclipboard's benefit
  (if (interactive-p)
      (let ((other-end (if (= (point) beg) end beg))
	    (opoint (point))
	    ;; Inhibit quitting so we can make a quit here
	    ;; look like a C-g typed as a command.
	    (inhibit-quit t))
	(if (pos-visible-in-window-p other-end (selected-window))
	    (progn
	      (goto-char other-end)
              (sit-for 0)
              (goto-char opoint)
              ;; If user quit, deactivate the mark
	      ;; as C-g would as a command.
	      (and quit-flag (mark)
                   (zmacs-deactivate-region)))
	  ;; too noisy. -- jwz
;	  (let* ((killed-text (current-kill 0))
;		 (message-len (min (length killed-text) 40)))
;	    (if (= (point) beg)
;		;; Don't say "killed"; that is misleading.
;		(message "Saved text until \"%s\""
;			(substring killed-text (- message-len)))
;	      (message "Saved text from \"%s\""
;		      (substring killed-text 0 message-len))))
	  ))))



;; Remove the annoying ding.
(defun compilation-sentinel (proc msg)
  "Sentinel for compilation buffers."
  (let* ((buffer (process-buffer proc))
	 (window (get-buffer-window buffer)))
    (if (memq (process-status proc) '(signal exit))
	(progn
	  (if (null (buffer-name buffer))
	      ;; buffer killed
	      (set-process-buffer proc nil)
	    (let ((obuf (current-buffer))
		  omax opoint estatus)
	      ;; save-excursion isn't the right thing if
	      ;; process-buffer is current-buffer
	      (unwind-protect
		  (progn
		    ;; Write something in the compilation buffer
		    ;; and hack its mode line.
		    (set-buffer buffer)
		    (let ((buffer-read-only nil))
		      (setq omax (point-max)
			    opoint (point))
		      (goto-char omax)
		      ;; Record where we put the message, so we can ignore it
		      ;; later on.
		      (insert ?\n mode-name " " msg)
		      (forward-char -1)
		      (insert " at " (substring (current-time-string) 0 19))
		      (forward-char 1)
		      (setq modeline-process
			    (concat ":"
				    (symbol-name (process-status proc))
				    (if (zerop (process-exit-status proc))
					" OK"
					(setq estatus
					      (format " [exit-status %d]"
						      (process-exit-status proc))))
				    ))
		      ;; XEmacs - tedium should let you know when it's ended...
;		      (if (and window
;			       (pos-visible-in-window-p (point-max) window))
;			  nil		; assume that the user will see it...
;			(ding t 'ready)
;			(message "Compilation process completed%s."
;				 (or estatus " successfully")
;				 ))
		      ;; Since the buffer and mode line will show that the
		      ;; process is dead, we can delete it now.  Otherwise it
		      ;; will stay around until M-x list-processes.
		      (delete-process proc)
		      ;; Force mode line redisplay soon.
		      (redraw-modeline))
		    (if (and opoint (< opoint omax))
			(goto-char opoint))
		    (if compilation-finish-function
			(funcall compilation-finish-function buffer msg)))
		(set-buffer obuf))))
	  (setq compilation-in-progress (delq proc compilation-in-progress))
	  ))))



;; When toolbar was NIL, this got an error.
(defun Patched-gnus-toolbar-active ()
  (interactive)
  (if (featurep 'toolbar)
      (let ((toolbar (gnus-toolbar-from-orientation gnus-toolbar-orientation)))
	(if (and toolbar
		 (specifier-instance toolbar))
	    t
	  nil))
    nil))

(add-hook 'gnus-group-mode-hook
	  '(lambda ()
	    (fset 'gnus-toolbar-active (function Patched-gnus-toolbar-active))))

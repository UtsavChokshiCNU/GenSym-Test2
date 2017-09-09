;;;; Shell Mode

;;; `bash' is the shell of choice on Linux, and generally seems to work better
;;; there than any csh derivative.  But we're not making this explicit for
;;; "general" goodness.  For some reason, we can't get sbcl to work from csh.
;;; So, on Linux, make the shell be bash.  -jv, 11/20/07

(if linux-p
  (setq explicit-shell-file-name "/bin/bash"))


;;;; Synch Emacs State with Prompt


;;; This facility will override the directory tracking mechanism if your prompt
;;; is like Mr. AB's.  I.e. it will snarf the directory from the prompt.  It
;;; will also highlight the user name in the prompt it it isn't the same as the
;;; login user.

(defvar consider-prompt-in-shell-mode-p t)



;;; `Highlight-prompt-face'  is used to highlight parts of the
;;; prompt that deserve attention.

(copy-face 'default 'highlight-prompt-face)
(set-face-foreground 'highlight-prompt-face "violetred")


;;; `indep-put-text-property' exists just to give us a common function to call
;;; whether we are in Xemacs or FSF emacs.  This works in emacs 20.3.1 on
;;; burlington, as well as all Xemacses, but not in 21.3.1 on brookline or
;;; lenox.  (But it doesn't do any harm there, either.)

(defun indep-put-text-property (start end property value)
  (if xemacs-p
      (put-nonduplicable-text-property
       start end property value)
      (put-text-property
       start end property value)))


;;; `Consider-prompt-in-output' is installed on `comint-output-filter-functions'
;;; when in shell-mode.  It peeks at the prompt and if it is formated in the
;;; style that Mr. AB is into then it will snarf the directory out and use that
;;; rather than the directory tracking mechinisms.

;;; In addition this will highlight the user name in the prompt if it
;;; isn't the current login user.

(defun consider-prompt-in-shell-output (output)
  ;; Search backward from point-max
  (if consider-prompt-in-shell-mode-p
      (save-excursion
        (goto-char (point-max))
        ;; inhibit-field-text-motion only matters in FSF emacs, but it won't
        ;; hurt to bind it in Xemacs
        (let ((inhibit-field-text-motion t))
          (beginning-of-line))
        (cond
          ;; changed pattern to permit it to end with not just '>' (csh/tcsh), but
          ;; also '$' (bash) -jv, 11/16/07
          ((let ((p "\\([^:]*\\):\\([^:]*\\):\\([^:]*\\):\\([^:]*\\):[0-9]*[$>] "))
             (or (looking-at p)
                 (progn (previous-line 1)
                        (looking-at p))))
           ;; We trust the prompt now, so we can disable to alternate mechanism.
           (setq shell-dirtrackp nil)
           ;; Now CD if we actually have changed directories.
           (let (
                 (user
                   (buffer-substring (match-beginning 1) (match-end 1)))
;                 (machine-kind
;                   (buffer-substring (match-beginning 2) (match-end 2)))
;                 (hostname
;                   (buffer-substring (match-beginning 3) (match-end 3)))
                 (directory
                   (concat
                     (buffer-substring (match-beginning 4) (match-end 4))
                     "/")))

             ;; Highlight the user name if different from the login name
             (cond ((not (string-equal (user-login-name) user))
                    (indep-put-text-property
                      (match-beginning 1)
                      (match-end 1) 'face 'highlight-prompt-face)))

             ;; Synch up the directory
             (cond ((not (string-equal default-directory directory))
                    (shell-process-cd directory)))))))))


;;; Add consider-prompt-in-output to the output filter functions for shell-mode.

(add-hook 'shell-mode-hook
          '(lambda ()
             (add-hook 'comint-output-filter-functions
                       'consider-prompt-in-shell-output)))

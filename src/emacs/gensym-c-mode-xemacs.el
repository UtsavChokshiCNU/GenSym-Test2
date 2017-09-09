;; Firther C-mode stuff for XEmacs

(defconst gensym-C-keymap (let ((map (make-sparse-keymap)))
			    (define-key map '(meta button1) 'C-find-tag)
			    (define-key map '(meta button3) 'C-post-menu)
			    map))

(defvar C-identifier nil)

(defconst pop-up-C-menu
  '("C Menu:"
    ["Grep" (C-grep C-identifier) t ""]
    ["Find" (find-tag C-identifier) t ""]
    ["ManPage" (C-manpage C-identifier) t ""]))


(defun C-find-tag (event)
  (interactive "e")
  (save-window-excursion
    (save-excursion
      (mouse-set-point event)
      (setq C-identifier (C-function-at-point))))

  (find-tag C-identifier))


(defun C-post-menu (event)
  (interactive "e")
  (save-window-excursion
    (save-excursion
      (mouse-set-point event)
      (setq C-identifier (C-function-at-point))

      (popup-menu pop-up-C-menu))))


(defun C-delimit-identifer-at-point ()
  (let ((here (point))
	(start nil)
	(end nil))
    (save-excursion
      (if (string-match "[a-zA-Z0-9_]" (format "%s" (preceding-char)))
	  (backward-sexp 1))
      (setq start (point))
      (if (looking-at "[0-9]")		; Not if first char is a digit.
	  nil
	  (forward-sexp 1))
      (setq end (point))

      (if (and (<= start here)
	       (< here end))
	  (cons start end)))))


(defun C-mode-motion-highlight-identifier (event)
  "Highlight C identifier at event"
  (let (pos)
    (ilisp-mouse-highlight-internal	; Allows the doc line.
      event
      (function
	(lambda ()
	  (setq pos (C-delimit-identifer-at-point))
	  (if pos (goto-char (car pos)))))
      (function
	(lambda ()
	  (if pos (goto-char (cdr pos)))))
      "Left: find definition;  Right: menu")

    ;; If the extent is non-empty, give it the keymap.
    (if (and (extentp mode-motion-extent)
	     (extent-buffer mode-motion-extent))
	(set-extent-property mode-motion-extent 'keymap
			     (if (extent-property mode-motion-extent 'highlight)
				 gensym-C-keymap
				 nil)))))


(defun C-highlighter (event)
  (cond ((= 2 (event-modifier-bits event)) ; Meta bit.
	 (C-mode-motion-highlight-identifier event))))

(defun gensym-C-mode-hook ()
  (setq mode-motion-hook 'C-highlighter)
  ;; Set the compile command for files in g2/c
  (cond ((string-match "/bt/[a-zA-Z0-9]*/g2/c/" default-directory)
	 (setq compile-command (format "%s %s"
				       g2comp-script
				       (buffer-name))))))


(add-hook 'c-mode-hook 'gensym-C-mode-hook)

;(add-hook 'c++-mode-hook 'gensym-C-mode-hook)


;; Bugfix.  From cc-mode.el
(defun c-progress-fini (context)
  ;; finished
  (if (and c-progress-info		; ***
	   (or (eq context (aref c-progress-info 3))
	       (eq context t)))
      (progn
	(set-marker (aref c-progress-info 1) nil)
	(setq c-progress-info nil)
	(message "indenting region... done."))))

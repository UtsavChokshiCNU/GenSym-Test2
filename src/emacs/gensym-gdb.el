;;;; GDB

(defun delimit-hex-address-at-point ()
  "Looks like 0x15c8c94"
  (save-excursion
    (skip-chars-backward "0-9a-z")
    (if (looking-at "0x[0-9a-f]*[^a-zA-Z0-9]")
	(cons (match-beginning 0)
	      (1- (match-end 0))))))


(defun hex-address-at-point ()
  (let ((pos (delimit-hex-address-at-point)))
    (if pos
	(buffer-substring (car pos) (cdr pos)))))


(defun mode-motion-highlight-hex-address (event)
  "Highlight gdb hex address at event"
  (let (pos)
    (ilisp-mouse-highlight-internal
      event
      #'(lambda ()
	  (setq pos (delimit-hex-address-at-point))
	  (if pos (goto-char (car pos))))
      #'(lambda ()
	  (if pos (goto-char (cdr pos))))
      "Left: print lisp object;  Middle: describe")))


;; These ought to be just in the extent's keymap.

(defun gdb-print-object (event)
  (interactive "e")
  (let ((hex (save-excursion
	       (mouse-set-point event)
	       (hex-address-at-point))))
    (if (> (length hex) 2)
	(progn
	  (goto-char (point-max))
	  (insert (format "print pm_print(%s)" hex))
	  (comint-send-input))
	(mouse-track event))))


(defun gdb-describe-object (event)
  (interactive "e")
  (let ((hex (save-excursion
	       (mouse-set-point event)
	       (hex-address-at-point))))
    (if (> (length hex) 2)
	(progn
	  (goto-char (point-max))
	  (insert (format "print pm_describe(%s)" hex))
	  (comint-send-input))
	(x-set-point-and-insert-selection event))))
	


;;;; Running the debuggable, translated G2 and Tw


(defun platform-specific-path-for-ab (product)
  (format format-string-for-ab-debuggable
	  machine-type product product))

(defun run-debuggable-image (which)
  "Which should be either g2 or tw"
  (interactive (list (completing-read "Which product: " '(("g2") ("tw")))))
  (let* ((name (downcase (format "%s" which)))
	 (filename (platform-specific-path-for-ab name))
	 (buffer (get-buffer (format "*gdb-%s*" name))))
    (cond ((and buffer (get-buffer-process buffer))
	   (switch-to-buffer buffer))
	  ((file-executable-p filename)
	   (message "Running GDB on %s" filename)
	   (gdb filename))
	  (t
	   (error "File %s is not executable." filename)))))


(defun platform-specific-path-for-et (product)
  (format format-string-for-et-debuggable
	  machine-type product product))


(defun run-eternal-translate-debuggable-image (which)
  "Which should be either g2 or tw"
  (interactive (list (completing-read "Which product: " '(("g2") ("tw")))))
  (let* ((name (downcase (format "%s" which)))
	 (filename (platform-specific-path-for-et name))
	 (buffer (get-buffer (format "*gdb-%s*" name))))
    (cond ((and buffer (get-buffer-process buffer))
	   (switch-to-buffer buffer))
	  ((file-executable-p filename)
	   (message "Running GDB on %s" filename)
	   (gdb filename))
	  (t
	   (error "File %s is not executable." filename)))))



(defvar last-gdb-buffer-name "*gdb*")


(defun switch-to-gdb-buffer ()
  "Switch to last gdb buffer, or create one running G2"
  (interactive)
  (if (get-buffer last-gdb-buffer-name)
      (switch-to-buffer last-gdb-buffer-name)
      (run-debuggable-image "g2")))


(defun gensym-gdb-hook ()
  (cond (xemacs-p
	 (setq last-gdb-buffer-name (buffer-name (current-buffer)))
	 (setq mode-motion-hook 'mode-motion-highlight-hex-address)
	 (define-key gdb-mode-map 'button1 'gdb-print-object)
	 (define-key gdb-mode-map 'button2 'gdb-describe-object)
	 (define-key gdb-mode-map 'kp_enter 'gdb-next)
	 ;; Preserve the top-level binding of c-l, if any.
	 (if (global-key-binding "\C-l")
	     (define-key gdb-mode-map "\C-l" (global-key-binding "\C-l"))))))


(add-hook 'gdb-mode-hook 'gensym-gdb-hook)

(define-key global-map "\C-c\C-j" 'switch-to-gdb-buffer)

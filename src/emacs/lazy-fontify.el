;; Lazy fontification, derived from lazy-lock (by Simon Marshall).

;; (require 'font-lock)


(defconst lazy-lock-minimum-size (* 30 1024)
  "*If non-nil, the minimum size for buffers.
Only buffers at least this size can have demand-driven fontification.
If nil, means size is irrelevant.")

(defconst lazy-lock-continuity-time 0
  "*Time in seconds to delay after a command before fontification.
Window fontification occurs if there is no input within this time.")


(defconst lazy-lock-delay-time 1
  "*Time in seconds to delay after one of `lazy-lock-delay-commands'.")

(defvar lazy-lock-delay-commands
  '(isearch-printing-char isearch-repeat-forward isearch-repeat-backward)
  "A list of commands after which fontification should delay.
Fontification occurs if there is no input after `lazy-lock-delay-time'.")

(defvar lazy-lock-mode nil)		; for modeline

;; This variable records, for each buffer, the window end position.  If this
;; has not changed, the displayed window must be the same as before.  Used to
;; make lazy-lock-fontify-window faster.
(defvar lazy-lock-cache-position -1)


(make-variable-buffer-local 'lazy-lock-cache-position)


(defun lazy-lock-mode (&optional arg)
  "Toggle Lazy Lock mode."
  (interactive "P")
  (set (make-local-variable 'lazy-lock-mode)
       (and (<= (or lazy-lock-minimum-size 0) (buffer-size))
	    (if arg (> (prefix-numeric-value arg) 0) (not lazy-lock-mode))))
  (if (not lazy-lock-mode)
      (let ((modified (buffer-modified-p))
	    (inhibit-read-only t))
	(remove-hook 'post-command-hook 'gensym-lazy-lock-post-command-hook)
;	(remove-text-properties (point-min) (point-max) '(fontified nil))
	(or modified (set-buffer-modified-p nil)))

      (make-local-variable 'post-command-hook)
      (add-hook 'post-command-hook 'gensym-lazy-lock-post-command-hook t)
      (set (make-local-variable 'font-lock-fontified) t)))

(defun turn-on-lazy-lock ()
  "Unconditionally turn on Lazy Lock mode."
  (lazy-lock-mode 1))


(defun gensym-lazy-lock-post-command-hook ()
  (if (sit-for (if (memq this-command lazy-lock-delay-commands)
		   lazy-lock-delay-time
		   lazy-lock-continuity-time))
      (or (eq this-command 'self-insert-command)
	  (lazy-lock-fontify-window))))


(defun refontify-region (start end)
  (font-lock-unfontify-region start end)
  (font-lock-fontify-region start end)
  (font-lock-hack-keywords start end))



(defun refontify-window ()
  (interactive)
  (let ((start (min (point-max) (max (point-min) (window-start))))
	(end (min (point-max) (max (point-min) (window-end)))))
    (font-lock-unfontify-region start end)
    (message "Unfontified")
    (sit-for 2)

    (font-lock-fontify-region start end)
    (message "Fontified")
    (sit-for 2)

    (font-lock-hack-keywords start end)
    (message "keywords")
    (sit-for 2)))
  

(defun lazy-lock-fontify-window ()
  (let ((ws (min (point-max) (max (point-min) (window-start))))
	(we (min (point-max) (max (point-min) (window-end)))))

    ;; Some wierd bug: if you find-file while in the ilisp buffer (only), then
    ;; window-end is equal to the size of the entire new buffer, rather than
    ;; the first windowfull.
;    (if (and (= ws 1)
;	     (> we (* (window-width) (window-height))))
;	(setq we (* (window-width) (window-height))))

    ;; Often times window-start/end are incorrect. Recenter fixes them up.
    (if (> (- we ws) (* (window-width) (window-height)))
	(progn (force-redisplay)
	       (setq ws (min (point-max) (max (point-min) (window-start)))
		     we (min (point-max) (max (point-min) (window-end))))))

    (if (/= we lazy-lock-cache-position)
	(let* ((start ws)
	       (end we)
	       (modified (buffer-modified-p))
	       (inhibit-read-only t))

	  (save-excursion
	    (goto-char start) (beginning-of-line 1) (setq start (point))
	    (goto-char end) (or (bolp) (forward-line 1)) (setq end (point))
	    (formatd start end (window-start) (window-end) (selected-window) (current-buffer) (window-point))
	    (refontify-region start end))

	  (setq lazy-lock-cache-position we)
	  (or modified (set-buffer-modified-p nil))))))


(or (assq 'lazy-lock-mode minor-mode-alist)
    (setq minor-mode-alist (cons '(lazy-lock-mode " Lazy") minor-mode-alist)))


;; Install ourselves:
(defun lazy (arg)
  "Turn on lazy fontification for new buffers.  With any argument, turn it off."
  (interactive "P")
  (cond (arg
	 (remove-hook 'font-lock-mode-hook 'turn-on-lazy-lock)
	 (message "Lazy fontification is off for new buffers."))
	(t
	 (add-hook 'font-lock-mode-hook 'turn-on-lazy-lock))))


(lazy nil)


(provide 'lazy-lock)

;; Lazy fontification, derived from lazy-lock (by Simon Marshall),
;; and hacked for 19.12.

;; I've found that it's faster to refontify the entire window, than
;; to muck around with text properties. -fmw, 6/26/95

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

(defconst lazy-lock-delay-commands
  '(isearch-printing-char isearch-repeat-forward isearch-repeat-backward
    scrollbar-vertical-drag)
  "A list of commands after which fontification should delay.
Fontification occurs if there is no input after `lazy-lock-delay-time'.")

(defconst lazy-lock-ignore-commands
  '(universal-argument digit-argument negative-argument
    isearch-other-control-char isearch-other-meta-char)
  "A list of commands after which fontification should not occur.")



(defvar lazy-lock-mode nil)                ; for modeline


(defvar lazy-lock-cache-start -1)
(defvar lazy-lock-cache-end -1)


(defun lazy-lock-change-hook (add-p)
  (let ((hook (cond (xemacs-p
                     'local-post-command-hook)
                    (t
                     (make-local-variable 'post-command-hook)
                     'post-command-hook))))

    (remove-hook hook 'gensym-lazy-lock-post-command-hook)
    (if add-p
        (add-hook hook 'gensym-lazy-lock-post-command-hook t))))



(defun lazy-lock-mode (&optional arg)
  "Toggle Lazy Lock mode."
  (interactive "P")
  (set (make-local-variable 'lazy-lock-mode)
       (and (<= (or lazy-lock-minimum-size 0) (buffer-size))
            (if arg (> (prefix-numeric-value arg) 0) (not lazy-lock-mode))))

  (cond ((not lazy-lock-mode)
         (let ((modified (buffer-modified-p))
               (inhibit-read-only t))
           (lazy-lock-change-hook nil)
           (or modified (set-buffer-modified-p nil))))

        (t
         (lazy-lock-change-hook t)

         (set (make-local-variable 'lazy-lock-cache-start) 0)
         (set (make-local-variable 'lazy-lock-cache-end) 0)

         ;; This tells font-lock-mode to not fontify the buffer after all.
         (set (make-local-variable 'font-lock-fontified) t))))


(defun turn-on-lazy-lock ()
  "Unconditionally turn on Lazy Lock mode."
  (lazy-lock-mode 1))


(defun gensym-lazy-lock-post-command-hook ()
  (if (and lazy-lock-mode
           (not executing-macro)
           (not (input-pending-p))
           (not (memq this-command lazy-lock-ignore-commands))
           (not (window-minibuffer-p (selected-window)))
           (if (memq this-command lazy-lock-delay-commands)
               (sit-for lazy-lock-delay-time)
               (sit-for lazy-lock-continuity-time t)))

      (or (eq this-command 'self-insert-command)
          (save-excursion
            (condition-case nil (lazy-lock-fontify-window))))))


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


;; based (without permission -- sorry Bill!) on fontifly
(defun lazy-lock-find-bol (&optional point forward)
  (let ((original-point (point)))
    (prog1
        (progn
          (if point (goto-char point))
          (beginning-of-line)
          (if forward (forward-line forward))
          (point))
      (goto-char original-point))))


(defun lazy-lock-fontify-window ()
  ;; ws,we still are not correct -- they vary just after a cursor-forward.
  (let ((ws (lazy-lock-find-bol (point) (- (window-height))))
        (we (lazy-lock-find-bol (point) (window-height))))

    ;; Often times window-start/end are incorrect. Recenter fixes them up.
    (if (or
          ;; Pointless hackery to fix one frequent loophole.
          (memq this-command '(find-tag completer-minibuf-exit))
          (> (- we ws) (* (window-width) (window-height))))
        (progn
          (force-redisplay)
          (setq ws (min (point-max) (max (point-min) (window-start)))
                we (min (point-max) (max (point-min) (window-end))))))

;    (or (equal (buffer-name) "*scratch*")
;        (progn
;          (formatd (buffer-name) this-command (window-height) (- we ws))
;          (formatd ws we lazy-lock-cache-start lazy-lock-cache-end)))

    (if (and (or (/= ws lazy-lock-cache-start) (/= we lazy-lock-cache-end))
             (not (input-pending-p)))

        (let* ((start ws)
               (end we)
               (modified (buffer-modified-p))
               (inhibit-read-only t))

          ;; Give fast feedback for the command, then fontify.
          (sit-for 0)

          (save-excursion
            (goto-char start) (beginning-of-line 1) (setq start (point))
            (goto-char end) (or (bolp) (forward-line 1)) (setq end (point))
            (refontify-region start end))

          (setq lazy-lock-cache-start ws
                lazy-lock-cache-end we)

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

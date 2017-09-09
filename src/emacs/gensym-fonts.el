;;;; Font Lock (xemacs only)


(require 'font-lock)


(defvar g2-public-documentation-face (make-face 'g2-public-documentation-face))
(defvar g2-alert-fact (make-face 'g2-alert-face))


(defvar gensym-lisp-fontify-mode 'default)


;;; Mr. AB likes fast subdued highlighting with a little bit on his comments.

(defconst gensym-lisp-font-lock-keywords
 '(
   ;; (def... <highlight> ...
   ("^(def[-+a-z0-9]+\\s +\\([^ \t\n\)]+\\)" 1 font-lock-function-name-face)

   ;; Mr. AB's Section Headers (;;;;)
   ("\\(^;;;;[ \t].*$\\)" 1 font-lock-keyword-face t)

   ;; Mr. AB's Public Documentation (;;;) -- use roman for these, but
   ;; italics for all other comments.
   ;; (Most publications don't use italics for main text because
   ;; they grow tiresome for text you have to read a lot. (MHD 7/7/93))
   ;;  Note: it doesn't work to give DEFAULT as the face here.
   ;;  Also, there seems to be a bug in font-lock which causes only the first
   ;;  line of the public doc to be in the correct face. Moving the highlit
   ;;  region to after the semicolons seems to work around the bug. (FMW)
   ("^;;;[ \t]\\(.*$\\)" 1 g2-public-documentation-face t)

   ;; These comments stand up and say hello.
;   ("^;;;\\*\\*\\*\\(.*$\\)" 1 g2-alert-face t)

   ;; Mr. AB's `Index Entries'.
   ("`\\([^('][^'\n]*\\)'"  1 font-lock-keyword-face t)
   ; Odd cases:
   ;   (defmacro f () `(gee 'wiz))   -- backquote almost always followed by (
   ;   `Wow' this is `neat'          -- grep likes longest match.

   ))


(defconst gensym-lisp-font-lock-keywords-2
    ;; Highlight control structures
    '(("(\\(cond\\|if\\|when\\|unless\\|[ec]?\\(type\\)?case\\)[ \t\n]" . 1)
      ("(\\(while\\|do\\|let\\*?\\|flet\\|labels\\|prog[nv12*]?\\)[ \t\n]" . 1)
      ("(\\(catch\\|\\throw\\|block\\|return\\|return-from\\)[ \t\n]" . 1)
      ("(\\(loop\\|unwind-protect\\)[ \t\n]" . 1)))



(defun gensym-no-lisp-highlighting ()
  (interactive)
  (setq gensym-lisp-fontify-mode 'none)
  (disable-font-lock))


(defun gensym-default-lisp-highlighting ()
  (interactive)
  (if (eq gensym-lisp-fontify-mode 'none)
      (enable-font-lock))
  (setq gensym-lisp-fontify-mode 'default)
  (setq lisp-font-lock-keywords gensym-lisp-font-lock-keywords)
  (if (memq major-mode '(lisp-mode emacs-lisp-mode))
      (refontify-buffer)))


(defun gensym-more-lisp-highlighting ()
  (interactive)
  (if (eq gensym-lisp-fontify-mode 'none)
      (enable-font-lock))
  (setq gensym-lisp-fontify-mode 'more)
  (setq lisp-font-lock-keywords (append gensym-lisp-font-lock-keywords
                                        gensym-lisp-font-lock-keywords-2))
  (if (memq major-mode '(lisp-mode emacs-lisp-mode))
      (refontify-buffer)))

(defconst gensym-ilisp-font-lock-keywords
    (append
      '(
        ;; Catch Lucid Prompts and highlight the commands.
        ("^[->]*> \\(.*\\)$" 1 font-lock-keyword-face)

        ;; Highlight Warnings.
        ("^\\(;;; Warning: .*\\)$" 1 font-lock-keyword-face t))
      gensym-lisp-font-lock-keywords))


(defconst text-mode-font-lock-keywords
    '(("\\(^\\*+ .*$\\)" 1 font-lock-keyword-face t)))




(defun mr-ab-font-lock-mode-hook ()
  "Sets font-lock-keywords to something appropriate for this ilisp."
  ;; See also: dummy-font-lock-mode-hook in font-lock.el
  (cond ((eq major-mode 'ilisp-mode)
         (setq font-lock-keywords gensym-ilisp-font-lock-keywords))

        ((eq major-mode 'text-mode)
         (setq font-lock-keywords text-mode-font-lock-keywords))

        ((and (eq major-mode 'g2-mode)
              (boundp 'g2-mode-font-lock-keywords))
         ;; if you think it may be unbound, then it might not be defvar'ed either.
         (setq font-lock-keywords (symbol-value 'g2-mode-font-lock-keywords)))))


(add-hook 'font-lock-mode-hook 'mr-ab-font-lock-mode-hook t)


(set-face-foreground 'g2-alert-face "red")


;; Just boldface for function names, and don't underline strings.
(copy-face 'bold 'font-lock-function-name-face)
(set-face-underline-p 'font-lock-string-face nil)



(defun fontify-buffer ()
  "Fontify the current buffer and future typing in the current buffer.
 To toggle font-lock mode, see the function font-lock-mode."
  (interactive)
  (font-lock-mode 1))

(defun unfontify-buffer ()
  "Un-Fontify the current buffer and any future typing in the current buffer.
 To toggle font-lock mode, see the function font-lock-mode."
  (interactive)
  (font-lock-mode nil))

(defun refontify-buffer ()
  (interactive)
  (save-excursion
    (font-lock-set-defaults)
    (cond (lazy-lock-mode
           ;; renamed from lazy-lock-cache-position
           (setq lazy-lock-cache-end -1)
           (lazy-lock-fontify-window))
          (t
           (unfontify-buffer)
           (fontify-buffer)))))


;; Should these loop over all buffers?

(defun enable-font-lock ()
  "Fontify the current buffer and enable font-lock-mode for all new LISP and C buffers."
  (interactive)
  (font-lock-mode 1)
  (setq font-lock-auto-fontify t)
  (add-hook 'dired-mode-hook        'turn-on-font-lock)
  (add-hook 'emacs-lisp-mode-hook 'turn-on-font-lock)
  (add-hook 'c-lisp-mode-hook 'turn-on-font-lock)
  (add-hook 'ilisp-mode-hook 'turn-on-font-lock)
  (add-hook 'lisp-mode-hook 'turn-on-font-lock))

(defun disable-font-lock ()
  "Un-fontify the current buffer, and turn off font locking in any new LISP or C buffers."
  (interactive)
  (font-lock-mode nil)
  (setq font-lock-auto-fontify nil)
  (remove-hook 'dired-mode-hook        'turn-on-font-lock)
  (remove-hook 'emacs-lisp-mode-hook 'turn-on-font-lock)
  (remove-hook 'c-lisp-mode-hook 'turn-on-font-lock)
  (remove-hook 'ilisp-mode-hook 'turn-on-font-lock)
  (remove-hook 'lisp-mode-hook 'turn-on-font-lock))

;; By default, Mr AB likes fontification.
(enable-font-lock)



;; This assumes the use of font-lock-mode
(defun within-comment-p ()
  (let ((extent (extent-at (point))))
    (and extent
         (memq (extent-face extent)
               '(font-lock-comment-face g2-public-documentation-face)))))




;;;; Lazy fontification


;; This seems to work pretty well, so turn it on for everyone.

;; The new one in 19.12 is slower than our hack!  Try scrolling back from the
;; end of a large file, like panes.lisp.

(cond
  (xemacs-p
   (load gensym-lazy-lock-19-12))
  (t
   (load "lazy-fontify")))




;;;; Highlight regexps (Lucid only)


(defvar highlight-regexp-face nil)
(defvar highlight-regexp-pattern "")

;; defined in replace.el.
(defvar minibuffer-regexp-history nil)

(defun highlight-regexp (regexp)
  "Highlight text matching regexp in region, or, in entire buffer.
 Any prefix argument unhighlights."
  (interactive (list (setq highlight-regexp-pattern
                           (read-string "Highlight strings matching regexp: "
                                        highlight-regexp-pattern
                                        'minibuffer-regexp-history))))
  (cond (current-prefix-arg
         (unhighlight-regexp))
        (t
         (cond ((zerop (length regexp))
                (setq regexp highlight-regexp-pattern)))

         (cond ((null highlight-regexp-face)
                (copy-face 'bold 'highlight-regexp-face)
                (setq highlight-regexp-face (find-face 'highlight-regexp-face))
                (set-face-foreground 'highlight-regexp-face "violetred")))

         (setq highlight-regexp-pattern regexp)

         (let ((font-lock-keywords (list (cons regexp
                                               'highlight-regexp-face)))
               (start (if (mark) (min (point) (mark)) (point-min)))
               (end (if (mark) (max (point) (mark)) (point-max))))
           (save-excursion
             (font-lock-hack-keywords start end))))))


(defun unhighlight-regexp ()
  "Unhighlight text which was highlighted by highlight-regexp"
  (interactive)
  (map-extents (function
                 (lambda (extent arg)
                    (if (eq (extent-face extent) 'highlight-regexp-face)
                        (delete-extent extent))))))



;;;; List faces


;; Emacs 19 has this command built-in.  Copy it here for xemacs.

(defvar list-faces-sample-text
  "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "*Text string to display as the sample text for `list-faces-display'.")


(defun list-faces-display ()
  "List all faces, using the same sample text in each.
The sample text is a string that comes from the variable`list-faces-sample-text'.
It is possible to give faces different appearances on different screens.  This
command shows the appearance in the selected screen."
  (interactive)
  (let ((faces (sort (face-list) (function string-lessp)))
        (face nil)
        (screen (selected-frame))
        disp-screen window)
    (with-output-to-temp-buffer "*Faces*"
      (save-excursion
        (set-buffer standard-output)
        (setq truncate-lines t)
        (while faces
          (setq face (car faces))
          (setq faces (cdr faces))
          (insert (format "%35s " (symbol-name face)))
          (let ((beg (point)))
            (insert list-faces-sample-text)
            (insert "\n")
            (set-extent-face (make-extent beg (1- (point))) face)))
        (goto-char (point-min))))
    ;; If the *Faces* buffer appears in a different screen,
    ;; copy all the face definitions from SCREEN,
    ;; so that the display will reflect the selected screen.
    (setq window (get-buffer-window (get-buffer "*Faces*") t))
    (setq disp-screen (if window (window-frame window)
                       (car (frame-list))))
    (or (eq screen disp-screen)
        (let ((faces (face-list)))
          (while faces
            (copy-face (car faces) (car faces) disp-screen)
            (setq faces (cdr faces)))))))

;; Default by Default.
(gensym-default-lisp-highlighting)

;;;; Font Lock (FSF version)

(require 'font-lock)

;;; Mr. AB likes fast subdued highlighting with a little bit on his comments.

(defvar g2-public-documentation-face
  (make-face 'g2-public-documentation-face))
(defvar g2-alert-fact
  (make-face 'g2-alert-face))

(defconst lisp-font-lock-keywords-for-mr-ab
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

(setq lisp-font-lock-keywords lisp-font-lock-keywords-for-mr-ab)



(defconst ilisp-font-lock-keywords-for-mr-ab
    (append
      '(
	;; Catch Lucid Prompts and highlight the commands.
	("^[->]*> \\(.*\\)$" 1 font-lock-keyword-face)

	;; Highlight Warnings.
	("^\\(;;; Warning: .*\\)$" 1 font-lock-keyword-face t))
      lisp-font-lock-keywords-for-mr-ab))


(defconst text-mode-font-lock-keywords
    '(("\\(^\\*+ .*$\\)" 1 font-lock-keyword-face t)))




(defun mr-ab-font-lock-mode-hook ()
  "Sets font-lock-keywords to something appropriate for this ilisp."
  ;; See also: dummy-font-lock-mode-hook in font-lock.el
  (cond ((eq major-mode 'ilisp-mode)	
	 (setq font-lock-keywords
	       ilisp-font-lock-keywords-for-mr-ab))
	((eq major-mode 'text-mode)
	 (setq font-lock-keywords
	       text-mode-font-lock-keywords))))

(add-hook 'font-lock-mode-hook 'mr-ab-font-lock-mode-hook t)


(set-face-foreground 'g2-alert-face "red")

;; Just boldface for function names, and don't underline strings.
(setq font-lock-function-name-face 'bold)
(setq font-lock-string-face 'default)

(defun turn-on-font-lock ()
  (font-lock-mode 1))

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

(defun enable-font-lock ()
  "Fontify the current buffer and enable font-lock-mode for all new LISP and C buffers."
  (interactive)
  (font-lock-mode 1)
  (add-hook 'dired-mode-hook	'turn-on-font-lock)
  (add-hook 'emacs-lisp-mode-hook 'turn-on-font-lock)
  (add-hook 'c-lisp-mode-hook 'turn-on-font-lock)
  (add-hook 'ilisp-mode-hook 'turn-on-font-lock)
  (add-hook 'lisp-mode-hook 'turn-on-font-lock))

(defun disable-font-lock ()
  "Un-fontify the current buffer, and turn off font locking in any new LISP or C buffers."
  (interactive)
  (font-lock-mode nil)
  (remove-hook 'dired-mode-hook	'turn-on-font-lock)
  (remove-hook 'emacs-lisp-mode-hook 'turn-on-font-lock)
  (remove-hook 'c-lisp-mode-hook 'turn-on-font-lock)
  (remove-hook 'ilisp-mode-hook 'turn-on-font-lock)
  (remove-hook 'lisp-mode-hook 'turn-on-font-lock))

;; By default, Mr AB likes fontification.
(enable-font-lock)

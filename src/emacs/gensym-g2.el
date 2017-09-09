;;;; G2 mode

(defvar g2-mode-hook ())
(defvar g2-mode-syntax-table ())
(defvar g2-mode-map ())

(or g2-mode-map
    (progn
      (setq g2-mode-map (make-sparse-keymap))
      (set-keymap-name g2-mode-map 'g2-mode-map)
      (define-key g2-mode-map "\t" 'g2-indent-line)))


(defconst g2-mode-font-lock-keywords
    '(;; Procedure name (probably)
      ("\\(^[-_a-zA-Z0-9]+\\)[ \t]*[\n(]" 1 g2-alert-face t)

      ;; Comments
      ("\\({[^}]*}\\)" 1 font-lock-comment-face t)

      ;; Keywords
      ("\\b\\(begin\\|end\\|case\\|for\\)[ ;\t\n]"
       1 font-lock-keyword-face t)

      ("\\b\\(call next method\\|system call\\|call\\|return\\)\\b"
       1 font-lock-keyword-face t)))


(setq auto-mode-alist (cons '("\\.g2$" . g2-mode)
			    auto-mode-alist))


;; Todo: comment syntax, indentation, compilation.
;; Require keywords to delimit procedures, rules, methods, and functions?
;; Quick arglist
;; meta-dot => etags support
;; grep
;; g2 symbol highlighting
;; Syntax for other procedure attributes (class, priority, tracing, timeout, item config)


(defun g2-comment-indent ()
  (current-column))

(defun g2-indent-line ()
  )


(defun g2-mode ()
  "Major mode for editing G2 procedures"
  (interactive)
  (use-local-map g2-mode-map)

  (kill-all-local-variables)

  (make-local-variable 'comment-start)
  (make-local-variable 'comment-start-skip)
  (make-local-variable 'comment-end)
  (make-local-variable 'comment-column)

  (setq comment-start "{"
	comment-start-skip "{+[ \t]*"
	comment-end "}"
	comment-column 2)

;  (make-local-variable 'comment-indent-function)
;  (setq comment-indent-function 'g2-comment-indent)

  (setq major-mode 'g2-mode)
  (setq mode-name "G2")

;  (set-syntax-table g2-mode-syntax-table)
  (font-lock-mode)
  (run-hooks 'g2-mode-hook))

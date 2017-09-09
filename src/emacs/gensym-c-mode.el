;; C mode enhancements


(defun C-function-at-point ()
  (let (begin)
    (save-excursion
      (if (looking-at "[ \t(]")
	  (skip-chars-backward " \t("))
      (skip-chars-backward "A-Za-z0-9_")
      (setq begin (point))
      (skip-chars-forward "A-Za-z0-9_")
      (buffer-substring begin (point)))))


(defun C-grep (text)
  "Search *.[ch] in the current directory for text. 
Uses the ID database if it exists."
  (interactive
    (let* ((default (C-function-at-point))
	   (prompt "Pattern [%s]: ")
	   (string (read-string (format prompt default))))
      (if (equal string "")
	  (list default)
	  (list string))))
  (cond ((null text))
	((file-exists-p "ID")
	 (compile-internal (format "%s '%s'" gid-executable text)
			   "No more grep hits" "grep"))
	((file-exists-p "../ID")
	 (compile-internal (format "%s -f../ID '%s'" 
				   gid-executable text)
			   "No more grep hits" "grep"))
	(t
	 (message "Note: no ID database found")
	 (grep (concat "grep -n " text " *.[ch]")))))


(defun C-manpage (topic)
  "Dig up the man page for the function before point."
  (interactive (list (C-function-at-point)))
  (if (interactive-p)
      (call-interactively 'manual-entry topic)
      (manual-entry topic)))


(defun C-indent-region-or-defun ()
  (interactive)
  (if (mark)
      (call-interactively 'indent-region)
      (call-interactively 'c-indent-defun)))


;; For the gross new CC-mode in Xemacs, reduce this from 4 to 2.
(setq c-basic-offset 2)


;; The following doesn't work with xemacs 20.4.  I believe all that's required
;; is (require 'c-mode).  However, the machine I was testing with has 
;; mysteriously vanished, so I can't test that theory.  So, I'll just add this
;; comment and leave it at that.  - jv, 11/15/99

(cond (xemacs-21-0-p)
      (xemacs-p
       (define-key c-mode-map '(meta G) 'C-grep) ; Same as lisp-mode grep
       (define-key c-mode-map '(control D) 'C-manpage) ; Same as lisp-mode document-function
       ;;this does not actually appear to be useful.  It's much more useful to fill your comment
       ;;-yduj/mhd, 4/00
       ;;(define-key c-mode-map '(meta q) 'C-indent-region-or-defun)
       (load "gensym-c-mode-xemacs")))



;;;; RMAIL

(require 'rmail)


(defvar ab-mail-subject-color "violetred")
(defvar ab-mail-subject-font nil)


(defun ab-rmail-summary ()
  (interactive)
  (rmail)
  (rmail-summary))

(defun ab-rmail-compose ()
  "Send mail in another window.
While composing the message, use \\[mail-yank-original] to yank the
original message into it."
  (interactive)
  (let ((to nil)
	(subject nil)
	(cc nil))
    (mail-other-window nil to subject nil cc (current-buffer))))

(cond (xemacs-p
       (add-menu-item '("Mail") "Read Mail" 'rmail t)
       (add-menu-item '("Mail") "Send Mail" 'ab-rmail-compose t)
       (add-menu-item '("Mail") "List Mail" 'ab-rmail-summary t)
       (add-menu-item '("Mail") "News" 'gnus t)))


(defun switch-to-other-buffer-but-never-bury-it (arg)
  "Switch to the previous buffer.  With a numeric arg, n, switch to the nth
most recent buffer.  With an arg of 0, do nothing."
  (interactive "p")
  (cond ((eq arg 0))
	(t
	 (switch-to-other-buffer arg))))


;; Used for RMAIL, GNUS and VM modes.

(defun ab-setup-mail-and-news ()
  (cond (xemacs-p
	 (setq mode-motion-hook 'mode-motion-highlight-filename)

	 (if (find-face 'message-highlighted-header-contents)
	     (progn
	       (if ab-mail-subject-color
		   (set-face-foreground 'message-highlighted-header-contents
					ab-mail-subject-color))
	       (if ab-mail-subject-font
		   (set-face-font 'message-highlighted-header-contents
				  ab-mail-subject-font)))))))

;; Add filename operations to rmail mode, on the right button.
;; Big violet subjects
(add-hook 'rmail-mode-hook 'ab-setup-mail-and-news)




(define-key rmail-mode-map "\M-\C-l" 'switch-to-other-buffer-but-never-bury-it)



;;;; GNUS

(require 'gnus)

(setq gnus-nntp-service "nntp")		; How GNUS gets news (another option is NFS).
(setq gnus-nntp-server (or (getenv "NNTPSERVER") ; This should be non-NIL.
			   "gensym1"))
(setq gnus-local-domain "gensym.com")	; The reply address in postings.
(setq gnus-local-organization "Gensym")	; The organization in postings.
(setq gnus-use-generic-from t)		; Use the domain name in From: address.
;(setq gnus-novice-user nil)            ; Should this be set to NIL for everyone? 


;; Don't let GNUS clobber our binding.
(add-hook 'gnus-group-mode-hook
	  '(lambda ()
	    (define-key gnus-group-mode-map "\C-c\C-l" 'lucid)))


(defun scarf-up-gnus-server-name ()
  (let ((buffer (find-file-noselect rn-server-filename)))
    (if buffer
	(save-excursion
	  (set-buffer buffer)
	  (prog1
	      (setq gnus-nntp-server (buffer-substring (point-min) (- (point-max) 1)))
	    (kill-buffer buffer))))))

;; Keep this up-to-date as the NNTP server moves around.
(if (not xemacs-p)
    (add-hook 'gnus-open-server-hook 'scarf-up-gnus-server-name))



;; Add the filename menu to GNUS articles.
(add-hook 'gnus-article-mode-hook 'ab-setup-mail-and-news)

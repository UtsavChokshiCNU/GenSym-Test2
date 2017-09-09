;; Emacs lisp enhancements

(defun elisp-function-arglist (function)
  "The arglist of an emacs-list function."
  ;; In some cases, the info in the doc string would be better than the function slot.
  (let ((def function)
	(doc (if (and (symbolp function) (fboundp function))
		 (documentation function))))
    (while (symbolp def)
      (if (fboundp def)
	  (setq def (symbol-function def))
	  (error "The function \"%s\" is not defined in Emacs-Lisp." def)))
    (cond ((eq 'autoload (car-safe def))
	   nil)
	  ((eq 'lambda (car-safe def))
	   (nth 1 def))
	  ((byte-code-function-p def)
	   (aref def 0))
	  ((not (subrp def))
	   nil)
	  ;; XEmacs doc looks like this.
	  ((string-match "[\n\t ]*\narguments: ?\\((.*)\\)\n?\\'"
			 doc)
	   (car (read-from-string doc (match-beginning 1) (match-end 1))))

	  ;; FSF emacs doc looks different.
	  ((string-match (format "[\n\t ]*\n?\\((%s .*)\\)\n?\\'"
				 function)
			 doc)
	   (cdr (car (read-from-string doc (match-beginning 1) (match-end 1)))))
	  (t
	   nil))))


(defun symbol-called-at-point ()
  (condition-case ()
      (save-excursion
	(save-restriction
	  (narrow-to-region (max (point-min) (- (point) 1000)) (point-max))
	  (backward-up-list 1)
	  (forward-char 1)
	  (let (obj)
	    (setq obj (read (current-buffer)))
	    (and (symbolp obj) obj))))
    (error nil)))

(defun elisp-quick-arglist ()
  "Arglist for emacs lisp"
  (interactive)
  (let* ((fn (symbol-called-at-point))
	 (arglist (elisp-function-arglist fn)))
    (message "%s: %s" fn (or arglist "()"))))


;; I wish this used electric popup buffers.
(defun elisp-describe-function ()
  (interactive)
  (let ((fn (function-called-at-point)))
    (if fn
	(describe-function fn)
	(call-interactively 'describe-function))))

(defun elisp-compile-buffer ()
  (interactive)
  (save-buffer)
  (byte-compile-file (buffer-file-name))
  (load-file (format "%sc" (buffer-file-name))))

(defun byte-compile-and-load-file (&optional filename)
  "Just like byte-compile-file, but it loads it afterwards."
  (interactive "fByte compile and load file: ")
  (setq filename (expand-file-name filename))
  (let ((b (get-file-buffer filename)))
    (if (and b
	     (buffer-modified-p b)
	     (y-or-n-p (format "save buffer %s first? " (buffer-name b))))
	(let ((cb (current-buffer)))
	  (set-buffer b)
	  (save-buffer)
	  (set-buffer cb))))
  (byte-compile-file filename)
  (load-file (concat filename "c")))


;; debugging.
(defvar formatd-stream nil)

(defmacro formatd (&rest args)
  (let ((fmt "")
	(arg nil)
	(list args)
	(newargs ()))
    (while list
      (setq arg (car list)
	    list (cdr list))
      (cond ((stringp arg)
	     (setq fmt (concat fmt arg)))
	    (t
	     (setq fmt (concat fmt (format "%s = %%s" arg)))
	     (setq newargs (cons arg newargs))))
      (if list (setq fmt (concat fmt ", "))))
    (setq fmt (concat fmt "\n"))
    (if (not formatd-stream)
	(setq formatd-stream (get-buffer "*scratch*")))
    (list 'princ (cons 'format (cons fmt (nreverse newargs))) 'formatd-stream)))



;; From js.
(defun find-library (library)
  "Find and edit the source for LIBRARY."
  (interactive (list (completing-read "Find library: "
				      (mapcar '(lambda (s) (cons (symbol-name s) nil))
					      features))))
  (let ((file (locate-file library load-path ".el")))
    (or file
	(error "Library %s not found" library))
    (find-file file)))



;; Make right-bracket self-insert again.
(define-key emacs-lisp-mode-map "]" 'self-insert-command)

(define-key emacs-lisp-mode-map "\C-cc" 'byte-compile-and-load-file)
(define-key emacs-lisp-mode-map "\C-c\C-c" 'byte-compile-file)


(defun ab-emacs-lisp-mode-hook ()
  (if (and xemacs-p (not xemacs-21-0-p))
      ;; This highlights symbols when the meta key is down.
      ;; The mouse-doc line is wrong, though.
      (setq mode-motion-hook 'highlight-for-lisp-mode))
  (make-variable-buffer-local 'page-delimiter)
  (setq page-delimiter "^;;;;"))



(cond (xemacs-p
       (add-hook 'emacs-lisp-mode-hook  'ab-emacs-lisp-mode-hook)
       (add-hook 'emacs-lisp-mode-hook 	'turn-on-font-lock)

       (define-key emacs-lisp-mode-map '(control A) 'elisp-quick-arglist)
       (define-key emacs-lisp-mode-map '(control C) 'compile-defun)
       (define-key emacs-lisp-mode-map '(control D) 'elisp-describe-function)
       (define-key emacs-lisp-mode-map '(control E) 'eval-defun)
       (define-key emacs-lisp-mode-map '(control V) 'describe-variable)
       (define-key emacs-lisp-mode-map '(control meta 59) 'kill-comment)

       (define-key lisp-interaction-mode-map '(control A) 'elisp-quick-arglist)
       (define-key lisp-interaction-mode-map '(control D) 'elisp-describe-function))

      (fsf-emacs-p
       (add-hook 'emacs-lisp-mode-hook  'ab-emacs-lisp-mode-hook)
       (add-hook 'emacs-lisp-mode-hook 	'turn-on-font-lock)

       (define-key emacs-lisp-mode-map (read "[?\\S-\\C-a]") 'elisp-quick-arglist)
       (define-key emacs-lisp-mode-map (read "[?\\S-\\C-c]") 'compile-defun)
       (define-key emacs-lisp-mode-map (read "[?\\S-\\C-d]") 'elisp-describe-function)
       (define-key emacs-lisp-mode-map (read "[?\\S-\\C-e]") 'eval-defun)
       (define-key emacs-lisp-mode-map (read "[?\\S-\\C-v]") 'describe-variable)

       (define-key lisp-interaction-mode-map (read "[?\\S-\\C-a]") 'elisp-quick-arglist)
       (define-key lisp-interaction-mode-map (read "[?\\S-\\C-d]") 'elisp-describe-function)))

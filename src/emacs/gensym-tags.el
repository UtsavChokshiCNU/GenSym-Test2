;;;; Lisp Syntax table

;; Make = be a word constituent.  Loop likes this.
(modify-syntax-entry ?= "_   " lisp-mode-syntax-table)
;; This doesn't work!!



;;;; Patch find-tag to always do an exact match.

(load-library "etags")
(if xemacs-p
    (load-library "symbol-syntax"))

;;; First, need to make ^? act like whitespace.
(modify-syntax-entry 127 " " lisp-mode-syntax-table)
(modify-syntax-entry 127 " " emacs-lisp-mode-syntax-table)


;; **Patch** Fix pattern to pull name out of (define-frob (name ...
;; Still doesn't grok:
;;  (def-keysym "Illegal-Key" 19,291
;;  (def-keysym |Control+@| 27,618

(defconst tags-def-pattern
    "\\(.*[ \t(]+\\)?\\**\\(\\(\\sw\\|\\s_\\)+\\)[ ();,\t]*\C-?")
;;            ^   New stuff.

;; Etags caches some knowledge about syntax tables. Clear the cache.
(setq symbol-syntax-table-alist nil)

(cond (xemacs-21-0-p
       ;; gensym-tags-patches21 was empty.  Uncomment this when it's not.
       ;; (load "gensym-tags-patches21")
       )
      (xemacs-p
       (load "gensym-tags-patches19")))

;;;; Remove trailing : and , from find-tag default.


(defun setup-common-lisp-default-tag-hook ()
  (cond ((memq major-mode '(lisp-mode ilisp-mode))
         (make-variable-buffer-local 'find-tag-default-hook)
         (setq find-tag-default-hook 'common-lisp-default-tag))))

(add-hook 'lisp-mode-hook 'setup-common-lisp-default-tag-hook)
(add-hook 'ilisp-mode-hook 'setup-common-lisp-default-tag-hook)


;; It would be a nice hack to default this to the current debugger function,
;; if we are in ilisp mode and are at the debugger prompt.

(defun common-lisp-default-tag ()
  "Function to return a default tag for Lisp mode."
  (let ((name (unquoted-find-tag-default t)))
    (if name
        (regexp-quote name)
        nil)))


;;;; Find emacs function bound to key.


;; Default the Tags table while visiting any elisp file.
(setq tag-table-alist
      (list (cons "\\.el$" ab-emacs-directory)))


(defun edit-emacs-function-bound-to-key (key)
  "Print the name of the function KEY invokes.  KEY is a string."
  (interactive "kEdit function on key: ")
  (let (defn)
    ;; If the key typed was really a menu selection, grab the form out
    ;; of the event object and intuit the function that would be called,
    ;; and describe that instead.
    (if (and (vectorp key) (= 1 (length key)) (menu-event-p (aref key 0)))
        (let ((event (aref key 0)))
          (setq defn (list (event-function event) (event-object event)))
          (if (eq (car defn) 'eval)
              (setq defn (car (cdr defn))))
          (if (eq (car-safe defn) 'call-interactively)
              (setq defn (car (cdr defn))))
          (if (and (consp defn) (null (cdr defn)))
              (setq defn (car defn))))
      (setq defn (key-binding key)))
    (cond ((or (null defn) (integerp defn))
           (message "%s is undefined" (key-description key)))
          ((eq defn 'keyboard-quit)
           (keyboard-quit))
          (t
           (message "%s runs the command %s" (key-description key) defn)
           (edit-emacs-function defn)))))


(defun edit-emacs-function (function)
  (interactive "aFunction: ")
  ;; Don't let the change be permanent.
  ;; I seem to need this kludgery since the variable is buffer-local,
  ;; and, the current buffer is changing here.
  (let ((old-tags-file-name tags-file-name)
        (old-buffer (current-buffer)))
    (visit-tags-table (format "%sTAGS" ab-emacs-directory))
    (find-tag (if (symbolp function) (symbol-name function) function))
    (save-excursion
      (set-buffer old-buffer)
      (setq tags-file-name old-tags-file-name))))

;; Not used enough to justify a binding.
; (define-key global-map '(control meta \.) 'edit-emacs-function-bound-to-key)

;; This doesn't search any local definitions a user might have.



;;;; Completion

(defun ab-complete-symbol-1 (table predicate)
  (let* ((end (point))
         (beg (save-excursion
                (backward-sexp 1)
                (while (= (char-syntax (following-char)) ?\')
                  (forward-char 1))
                (point)))
         (pattern (buffer-substring beg end))
         (completion (try-completion pattern table predicate)))
    (cond ((eq completion t))
          ((null completion)
           (completer-complete-goto
             "^ \t\n\(\)[]{}'`" completer-words
             table predicate
             nil
             t))
          ((not (string-equal pattern completion))
           (delete-region beg end)
           (insert completion))
          (t
           (message "Making completion list...")
           (let ((list (all-completions pattern table predicate)))
             ;; Want to make the list mosue-sensitive -- need a new buffer mode.
             (with-output-to-temp-buffer "*Completions*"
               (display-completion-list list)))
           (message "Making completion list...%s" "done")))))


(defvar buffer-tag-table-list)


(defun ab-complete-symbol ()
  "Complete symbol before point using the TAGS completion table."
  (interactive)
  (let* ((buffer-tag-table-list (buffer-tag-table-symbol-list))
         (tag-symbol-tables nil))
    (ab-complete-symbol-1 tag-completion-table 'tag-completion-predicate)))

;; Derived from complete-symbol in etags.el



;;;; Network interface


;; This is called via gnudoit from make-tags.

(defun update-tags-completion-table ()
  (interactive)
  (let ((tags-build-completion-table t))
    (message "Updated TAGS buffer %s"
             (get-tag-table-buffer (format "%sTAGS" (user-lisp-sandbox))))))




;;;; Query-replace using Grep (or ID database) results


(defun grep-query-replace (from to &optional delimited)
  "Query-replace-regexp FROM with TO in files from last GREP or m-sh-G,
Search starts from the line point is on in the *grep* buffer.
Third arg DELIMITED (prefix arg) means replace only word-delimited matches. "
  (interactive "sQuery replace: \nsQuery replace %s with: \nP")
  (set-buffer (if (eq major-mode 'compile)
                  (current-buffer)
                  compilation-last-buffer))
  (let* ((buf (current-buffer))
         (win (get-buffer-window buf)))
    (if win (select-window win))
    (while (and
             (progn
               (compile-goto-error)
               (goto-char (point-min))
               (if (save-excursion (re-search-forward from nil t))
                   (perform-replace from to t t delimited)
                   t))
             (condition-case err
                 (progn
                   (if win
                       (pop-to-buffer buf)
                       (set-buffer buf))
                   (compilation-next-file 1))
               (error err))))))

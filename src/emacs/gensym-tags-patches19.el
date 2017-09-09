;; An exact match, except, case does not matter.
(defvar find-tag-use-exact-symbol-match t "If t, enable this patch.")

;;; We had to copy this code to ensure it uses an exact match for both
;;; find-tag and tags-loop-continue.  Also, we modify the binding
;;; of case-fold-search to be T for common lisp.
;;; The changes are marked by ***.

;; *** Redefine ***
(defun find-tag-internal (tagname)
  "Foo"
  (let* ((local-find-tag-hook find-tag-hook)
	 (next (null tagname))
	 (exact (or (consp tagname)	; ***
		    find-tag-use-exact-symbol-match)) ; ***
	 (lisp-like-mode (memq major-mode '(lisp-mode ilisp-mode emacs-lisp-mode))) ; ***
	 (case-fold-tags-search lisp-like-mode)
	 symbol-border tag-target
	 tag-tables tag-table-point file linebeg startpos target buf
	 offset found pat syn-tab)
    (if (consp tagname) (setq tagname (car tagname))) ; ***
    (cond (next
	   (setq tag-tables (cdr (cdr last-tag-data)))
	   (setq tagname (car last-tag-data))
	   (setq tag-table-point (car (cdr last-tag-data))))
	  (t
	   (setq tag-tables (buffer-tag-table-list))
	   (setq tag-table-point 1)))

    ;; If tagname is a list: (TAGNAME), this indicates requiring an exact
    ;; symbol match.  Similarly, \_ in the tagname is used to indicate a
    ;; symbol boundary.
    (cond ((or exact
	       (string-match "\\\\_" tagname))
	   (setq symbol-border t)

	   ;; *** This entire form is changed.
	   (cond ((not exact)
		  (setq tag-target (copy-sequence tagname)))
		 (lisp-like-mode
		  (setq tag-target (concat "\\_" tagname "\\_")))
		 (t
		  (setq tag-target (concat "\\_" tagname "\\_"))))
	   (while (string-match "\\\\_" tag-target)
	     (aset tag-target (1- (match-end 0)) ?b))
	   (setq syn-tab (get-symbol-syntax-table (syntax-table))))
	  (t
	   (setq tag-target tagname)
	   (setq syn-tab (syntax-table))))

    (save-excursion
      (catch 'found
	(while tag-tables

	  (set-buffer (get-tag-table-buffer (car tag-tables)))
	  (bury-buffer (current-buffer))
	  (goto-char (or tag-table-point (point-min)))
	  (setq tag-table-point nil)
	  (let ((osyn (syntax-table))
		(case-fold-search case-fold-tags-search)) ; ***
	    (set-syntax-table syn-tab)

	    ;; Once we've found an occurance of the tag-target, then the final test with looking-at
	    ;; is tricky: we need to distinguish occurances uses of the target from the definition of
	    ;; the target.  It is the definition if the occurance didn't start at the beginning of the
	    ;; line in the TAGS file: eg, "(defmacro def-class^?" matches and "(def-class foo^?" does not.
	    ;; So we simply check that the match-beginning is at a column > 1. Also, a better pattern:
	    ;; Old pattern: "[ )]*\C-?"
	    ;; New pattern: "[ \t();]*\C-?"    (Allow tabs and comments on same line as the defn.)
	    ;; Try m-. on def-substitution-macro, def-class.
	    (unwind-protect
		(while (re-search-forward tag-target nil t)
		  (if (if lisp-like-mode
			  (and (> (save-excursion (goto-char (match-beginning 0)) (current-column)) 1)
			       (looking-at "[ \t();]*\C-?"))
			  (looking-at "[^\n\C-?]*\C-?"))
		      (throw 'found t)))
	      (set-syntax-table osyn)))
	  (setq tag-tables (cdr tag-tables)))

	(error "No %sentries %s %s"
	       (if next "more " "")
	       (if exact "matching" "containing")
	       tagname))

      (search-forward "\C-?")
      (setq file (expand-file-name (file-of-tag)))
      (setq linebeg
	    (buffer-substring (1- (point))
			      (save-excursion (beginning-of-line) (point))))
      (search-forward ",")
      (setq startpos (read (current-buffer)))
      (setq last-tag-data (nconc (list tagname (point)) tag-tables)))
    (setq buf (find-file-noselect file))
    (save-excursion
      (set-buffer buf)
      (save-excursion
	(save-restriction
	  (widen)
	  (setq offset 1000)
	  (setq pat (concat "^" (regexp-quote linebeg)))
	  (or startpos (setq startpos (point-min)))
	  (while (and (not found)
		      (progn
			(goto-char (- startpos offset))
			(not (bobp))))
	    (setq found (re-search-forward pat (+ startpos offset) t))
	    (setq offset (* 3 offset)))
	  (or found
	      (re-search-forward pat nil t)
	      (error "%s not found in %s" pat file))
	  (beginning-of-line)
	  (setq startpos (point)))))
    (cons buf startpos)))





;;;; Patch

;; Change the "Bad TAGS file" error into just a warning.
;; I still don't know why we sometimes got this error.

(defun add-to-tag-completion-table ()
  "Sucks the current buffer (a TAGS table) into the completion-table."
  (message "Adding %s to tags completion table..."
	   buffer-file-name)
  (goto-char (point-min))
  (let ((tag-table-symbol (intern buffer-file-name tag-completion-table))
	(original-syntax-table (syntax-table))
	;; tag-table-symbol is used by intern-tag-symbol
	filename file-type name name2 tag-symbol eol-point
	tag-symbol-tables file-type-syntax-table)
    (unwind-protect
	;; loop over the files mentioned in the TAGS file
	;; for each file, try to find its major-mode,
	;; then process tags appropriately
	(while (looking-at tags-file-pattern)
	  (goto-char (match-end 0))
	  (setq filename (buffer-substring (match-beginning 1) (match-end 1)))
	  (setq filename (file-name-sans-versions filename))
	  ;; clear loop variables
	  (setq file-type nil)
	  (setq file-type-syntax-table nil)
	  (setq name nil name2 nil)
	  (let ((alist auto-mode-alist)
		(case-fold-search (eq system-type 'vax-vms)))
	    ;; loop over pairs of regexps and major-modes
	    (while (and (not file-type) alist)
	      (if (string-match (car (car alist)) filename)
		  (setq file-type (cdr (car alist))))
	      (setq alist (cdr alist))))
	  ;; try to find a syntax table whose name begins with the major-mode
	  (if file-type
	      (setq file-type-syntax-table
		    (intern (concat (symbol-name file-type)
				    "-syntax-table"))))
          (message "%s..." filename)
	  (if (and file-type-syntax-table (boundp file-type-syntax-table))
	      (set-syntax-table (symbol-value file-type-syntax-table))
	    (set-syntax-table (standard-syntax-table)))
	  ;; loop over the individual tag lines
	  (while (not (or (eobp) (eq (following-char) ?\f)))
	    (cond ((and (or (eq file-type 'c-mode)
			    (eq file-type 'c++-mode)
			    (eq file-type 'c++-c-mode))
			(let ((case-fold-search nil))
			  (looking-at "DEFUN[ \t]")))
		   (or (looking-at tags-DEFUN-pattern)
		       (error "DEFUN doesn't fit pattern"))
		   (setq name (buffer-substring (match-beginning 1)
						(match-end 1)))
		   (setq name2 (buffer-substring (match-beginning 2)
						 (match-end 2))))
;;;		  ((looking-at "\\s ")
;;;		   ;; skip probably bogus entry:
;;;		   )
		  ((and (or (eq file-type 'c-mode)
			    (eq file-type 'c++-mode)
			    (eq file-type 'c++-c-mode))
			(looking-at ".*\\["))
		   (or (looking-at tags-array-pattern)
		       (error "array definition doesn't fit pattern"))
		   (setq name (buffer-substring (match-beginning 1)
						(match-end 1))))
		  ((looking-at tags-def-pattern)
		   (setq name (buffer-substring (match-beginning 2)
						(match-end 2)))))
	    ;; add the tags we found to the completion table
	    (if name (intern-tag-symbol name))
	    (if name2 (intern-tag-symbol name2))
	    (forward-line 1)))
      (set-syntax-table original-syntax-table))
    ;; ***
    (or (eobp)
	(message "Warning: Syntax error in the TAGS file")
	(sit-for 0)))

  (message "Adding %s to tags completion table...done"
	   buffer-file-name))


;;;; Turn off the "Tags file has changed" query.


(defvar turn-off-tags-file-has-changed-query t)

;; Don't ask about building completion tables.
;; (setq tags-build-completion-table nil)

;; This takes a while, but it's worth the wait.
(setq tags-build-completion-table 'ask)


;; *** Redefine ***
(defun get-tag-table-buffer (tag-table)
  "Returns a buffer visiting the give TAGS table, reverting if appropriate,
and possibly building a completion-table."
  (or (stringp tag-table)
      (error "Bad tags file name supplied: %s" tag-table))
  ;; add support for removing symbolic links from name

; Avoid the compiler warning on symlink-expand-file-name
;  (if (fboundp 'symlink-expand-file-name)
;      (setq tag-table (funcall 'symlink-expand-file-name tag-table)))

  (let (buf build-completion check-name)
    (setq buf (get-file-buffer tag-table))
    (or buf
	(if (file-readable-p tag-table)
	    (setq buf (find-file-noselect tag-table)
		  check-name t)
	  (error "No such tags file: %s" tag-table)))
    (save-excursion
      (set-buffer buf)
      ;; make the TAGS buffer invisible
      (if (and check-name
	       make-tags-files-invisible
	       (string-match "\\`[^ ]" (buffer-name)))
	  (rename-buffer (generate-new-buffer-name
			  (concat " " (buffer-name)))))
      (or (verify-visited-file-modtime buf)
	  (cond ((or turn-off-tags-file-has-changed-query ; ****
		     (yes-or-no-p
		       (format "Tags file %s has changed, read new contents? "
			       tag-table)))
		 (message "Reading new TAGS file...")
		 (revert-buffer t t)
		 (if (eq tag-table-completion-status t)
		     (setq tag-table-completion-status nil))
		 (setq tag-table-files nil))))
      (or (eq (char-after 1) ?\f)
	  (error "File %s not a valid tags file" tag-table))
      (or (memq tag-table-completion-status '(t disabled))
	  (setq build-completion t))
      (and build-completion
	   (if (cond
		((eq tags-build-completion-table nil)
		 nil)
		((eq tags-build-completion-table t)
		 t)
		((eq tags-build-completion-table 'ask)
		 ;; don't bother asking for small ones
		 (or (< (buffer-size) 20000)
		     (y-or-n-p
		      (format "Build tag completion table for %s? "
			      tag-table))))
		(t (error
		    "tags-build-completion-table is not t, nil, or ask.")))
	       (condition-case foo
		   (progn
		     (add-to-tag-completion-table)
		     (setq tag-table-completion-status t))
		 ;; Allow user to C-g out correctly
		 (quit
		  (setq tag-table-completion-status nil)
		  (setq quit-flag t)
		  (eval t)))
	     (setq tag-table-completion-status 'disabled))))
    buf))

;; *** Redefine ***
(defun visit-tags-table-buffer ()
  "Select the buffer containing the current tag table.
This is a file whose name is in the variable tags-file-name."
  (or tags-file-name
      (call-interactively 'visit-tags-table))
  (set-buffer (or (get-file-buffer tags-file-name)
		  (progn
		    (setq tag-table-files nil)
		    (find-file-noselect tags-file-name))))
  (or (verify-visited-file-modtime (get-file-buffer tags-file-name))
      (cond ((or turn-off-tags-file-has-changed-query                ; ***
		 (yes-or-no-p "Tags file has changed, read new contents? "))
	     (message "Reading new TAGS file...")
	     (revert-buffer t t)
	     (setq tag-table-files nil))))
  (or (eq (char-after 1) ?\^L)
      (error "File %s not a valid tag table" tags-file-name)))



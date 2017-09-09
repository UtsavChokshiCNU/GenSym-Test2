;; gensym-emacs.el

;;; This file contains Mr. AB's personal recomendation for how to configure
;;; XEmacs and FSF Emacs 19.  Mr. AB's .emacs file loads this if it discovers it is
;;; inside of a XEmacs.  This version is for XEmacs 19.13 or greater.

;; This file should be byte compiled, resulting in a .elc version.  Easy way to
;; byte compile this file: do dired on it, and type B next the file name, which
;; invokes the byte compiler on it after confirmation.

;; We have copied the source for some emacs functions in order to
;; customize them.  They are marked with *** Redefine ***.  Some
;; other functions we advice by saving the old definition in a defvar
;; and calling it.  These are marked with *** Advise ***.
;; All will have to be checked for each new version of XEmacs.


(defconst xemacs-21-0-p
  (and xemacs-p
       (or (and (= emacs-major-version 21)
                (>= emacs-minor-version 0))
           (> emacs-major-version 21))))

(defconst solaris-p
  (string-match "-solaris" system-configuration))

(defconst linux-p
  (or (string-match "linux" system-configuration)
      (string-match "darwin" system-configuration)))

(defun lucid-platform-p ()
  solaris-p)

(defun allegro-platform-p ()
  ;; currently have no Allegro licenses
  nil)

(defun mswin-emacs-p ()
  (or
   (string-match "windows" (emacs-version))
   (string-match "nt.\.." (emacs-version))))

(if (mswin-emacs-p)
    (load "windows-files")
    (load "unix-files"))

(cond (fsf-emacs-p
       (load "fsf-compat")))

(cond
  (xemacs-p
   ;; The following line was added to stop XEmacs from using
   ;; /usr/local/lib/XEmacs/lock.  This directory is on gensym2, and waiting
   ;; for file operations on this machine was maddeningly slow.  -jra
   ;; 12/20/95
   (setq lock-directory "/tmp/")
   (setq superlock-path "/tmp/!!!SuperLock!!!") ; need this, too -rh 12/28/95
   ))


;; Turn off unused variable warnings in this file.
(if xemacs-p
    (byte-compiler-options
     (warnings (- unused-vars))))


;;;; Misc Toggles and Settings

(if xemacs-p
    (require 'itimer)                        ; Needed by auto-save-timeout.
    (require 'timer))

(setq completion-ignored-extensions
      (append
        (if (mswin-emacs-p)
            '(".fasl")
            '(".4cb"".5lb" ".5rb" ".fasl"))
        completion-ignored-extensions))


(setq inhibit-startup-message (not xemacs-p))        ; Startup message is boring, except in XEmacs.
(setq scroll-step 6)                        ; helpful scrolling at window edge

(setq make-backup-files t                ; We can afford a single backup file/file
      version-control nil                ;    but we cannot afford multiple versions.
      trim-versions-without-asking t)        ; Don't bug me when you delete old versions.

(setq auto-save-default t                ; Mr. AB does like to be auto-saved from crashes.
      auto-save-interval 0
      auto-save-timeout 120                ; Once every 2 minutes.
      delete-auto-save-files t)                ; Delete autosave files upon save of file


(setq gc-cons-threshold 1000000)        ; Grow bigger before GC-ing (1Mbyte).
                                        ; Not too big, else GCs, though infrequent, will be too lengthy.
(setq minibuffer-max-depth nil)

(put 'narrow-to-page 'disabled nil)
(put 'narrow-to-region 'disabled nil)

(cond ((not xemacs-21-0-p) ; changed to m-:, does not use "disabled" anymore
       (put 'eval-expression 'disabled nil)))  ; let eval work without query.
(setq default-fill-column 80)         ; Mr. AB likes not-too-wide sources.
;; Now called auto-fill-function. Do we need this?
;; (set 'auto-fill-hook nil)             ; but then this gets queried by completion.
(setq require-final-newline 1)        ; Necessary change.log
(setq find-file-compare-truenames  t)        ; Try to never have two buffers on same file.
(setq paragraph-start "^[ \t\n\f]\\|^-*$") ; Make a line of dashes (for change.log)

(setq occur-whole-buffer t)                ; Make M-x Occur search the entire buffer

(setq window-min-height 3)                ; Ilisp typeout windows like to be small.

(defun ab-what-line ()
  "Print the current line number and other useful information."
  (interactive)
  (let* ((char (following-char))
         (pos (point))
         (extent (if xemacs-p (extent-at pos)))
         (total (buffer-size))
         (col (current-column))
         (line (save-restriction
                 (widen)
                 (save-excursion
                   (beginning-of-line)
                   (1+ (count-lines 1 (point)))))))

    (message "Char: %s (0%o),  point=%d/%d,  column %d,  line %d%s"
             (single-key-description char) char pos total col line
             (if extent (format ", face %s" (extent-face extent)) ""))
    (setq zmacs-region-stays t)))


(defun just-one-line ()
  "Kill blank lines around point"
  (interactive)
  (save-excursion
    (let ((start (point))
          (end (point)))
      (if (re-search-backward "[^ \t\n]" nil t)
          (forward-line 1)
          (goto-char (point-min)))
      (beginning-of-line)
      (setq start (point))
      (if (re-search-forward "[^ \t\n]" nil t)
          (beginning-of-line)
          (goto-char (point-max)))
      (setq end (point))
      (if (> end start)
          (kill-region start end)))))


(cond (xemacs-p
       (define-key global-map '(control =) 'ab-what-line)
       (define-key global-map [(control x) (control space)] 'just-one-space)
       (define-key global-map [(control x) space] 'just-one-line))
      (fsf-emacs-p
       (define-key global-map (read "[?\\C-=]") 'ab-what-line)
       (define-key global-map (read "[?\\C-x ?\\C- ]") 'just-one-space)
       (define-key global-map (read "[?\\C-x ?\\ ]") 'just-one-line)))



;; Bugfix for missing function, called from View mode.
(if xemacs-p
    (autoload 'Helper-help "helper"))



;;;; Emacs-lisp enhancements


(load "elisp")

(if xemacs-p
    (load "gensym-tags"))


;; A variation on find-tag which looks only in the current file, and does not
;; require a prebuilt TAGS table.

(autoload 'jump-to-def "jump-def" "Jump to a definition." t)
(define-key global-map "\C-cj" 'jump-to-def)



;; Could be better. Eg, get previous word if between words.
;; Removes trailing : and , from find-tag default.

(defun unquoted-find-tag-default (&optional skip-backwards)
  (save-excursion
    (if skip-backwards
        (skip-chars-backward " \t\n"))
    (if (not (memq (char-syntax (preceding-char)) '(?w ?_)))
        (while (not (looking-at "\\sw\\|\\s_\\|\\'"))
          (forward-char 1)))
    (while (looking-at "\\sw\\|\\s_")
      (forward-char 1))
    (if (re-search-backward "\\sw\\|\\s_" nil t)
        (progn (forward-char 1)
               (let ((name (buffer-substring (point)
                                             (progn (forward-sexp -1)
                                                    (while (looking-at "\\s'")
                                                      (forward-char 1))
                                                    (point)))))
                 ;; Remove trailing : or ,
                 (if (and name (string-match "\\`.*[:,]\\'" name))
                     (setq name (substring name 0 (1- (match-end 0)))))
                 name))

        nil)))



(defvar buffer-tag-table-list)

(defun read-tag-with-completion (prompt &optional default)
  (let ((buffer-tag-table-list (buffer-tag-table-symbol-list)))
    (completing-read
      (if (and default (not (equal default "")))
          (format prompt default)
          prompt)
      tag-completion-table 'tag-completion-predicate nil nil
      'find-tag-history)))





;;;; Utility functions


;; Ben would prefer query-replace to always narrow to the region.
(defun query-replace-in-defun (from-string to-string)
  "Query replace string only within current definition."
  (interactive "sQuery replace in defun: \nsQuery replace %s with: \n")
  (save-excursion
    (save-restriction
      (let ((start (progn (beginning-of-defun) (point)))
            (end (progn (end-of-defun) (point))))
        (beginning-of-defun)
        (narrow-to-region start end)
        (query-replace from-string to-string)))))


(if xemacs-p
    (defvar mark-active))

(defun zmacs-region-present-p ()
  "According to jwz, (mark) is non-NIL iff the region if present."
  (cond (xemacs-p
         (mark))
        (t
          mark-active)))




;;;; ANSI CL manual page.

(defun clman (symbol)
  (interactive (list (read-ansi-common-lisp-symbol (find-tag-default))))
  ;; Want: do the grep ourselves, dvitty, etc.
  (shell-command (format "%s %s &" clman-script symbol)))

(defvar ansi-common-lisp-symbols nil)

(defun read-ansi-common-lisp-symbol (&optional default)
  (if (not ansi-common-lisp-symbols)
      (load "cl-symbols"))
  (let ((string (completing-read (if default
                                     (format "ANSI Common Lisp Symbol [%s]: " default)
                                     "ANSI Common Lisp Symbol: ")
                                 ansi-common-lisp-symbols)))
    (if (string= string "")
        default
        string)))




;;;; The Ispell executable is missing from XEmacs!

(autoload 'spell-word spell-elc-filename "Check spelling of word at or before point." t)
(autoload 'spell-buffer spell-elc-filename "Check spelling of every word in the buffer" t)
(autoload 'spell-region spell-elc-filename "Like spell-buffer but applies only to region"  t)
(define-key global-map "\e$" 'spell-word)




;;;; Turn off only certain queries in find-file-noselect

(defvar no-warn-if-buffer-unmodified nil)

;; *** Redefine ***
(defun later---find-file-noselect (filename &optional nowarn)
  "Read file FILENAME into a buffer and return the buffer.
If a buffer exists visiting FILENAME, return that one, but
verify that the file has not changed since visited or saved.
The buffer is not selected, just returned to the caller."
  (setq filename (abbreviate-file-name (expand-file-name filename)))
  (if (file-directory-p filename)
      (if find-file-run-dired
          (dired-noselect filename)
        (error "%s is a directory." filename))
    (let ((buf (get-file-buffer filename))
          error)
      (if (and buf (not nowarn)
               (or find-file-compare-truenames find-file-use-truenames))
          (save-excursion
            (set-buffer buf)
            (if (not (equal buffer-file-name filename))
                (message "%s and %s are the same file (%s)"
                         filename buffer-file-name
                         buffer-file-truename))))
      (if buf
          (or nowarn
              (verify-visited-file-modtime buf)
              (cond ((not (file-exists-p filename))
                     (error "File %s no longer exists!" filename))
                    ((cond ((buffer-modified-p buf) ; *** Fancier test here.
                            (yes-or-no-p
                              (format "File %s changed on disk.  Discard your edits? "
                                      (file-name-nondirectory filename))))
                           (no-warn-if-buffer-unmodified
                            (message "File %s changed on disk.  Reading the new version..."
                                     (file-name-nondirectory filename))
                            t)
                           (t
                            (yes-or-no-p
                              (format "File %s changed on disk.  Read the new version? "
                                       (file-name-nondirectory filename)))))
                     (save-excursion
                       (set-buffer buf)
                       (revert-buffer t t)))))
        (save-excursion
          (setq buf (create-file-buffer filename))
          (set-buffer buf)
          (erase-buffer)
          (condition-case ()
              (insert-file-contents filename t)
            (file-error
             (setq error t)
             ;; Run find-file-not-found-hooks until one returns non-nil.
             (let ((hooks find-file-not-found-hooks))
               (while (and hooks
                           (not (funcall (car hooks))))
                 (setq hooks (cdr hooks))))))
          ;; Set buffer's default directory to that of the file.
          (setq default-directory (file-name-directory buffer-file-name))
          (after-find-file error (not nowarn))))
      buf)))



;; Don't ask questions about reading new versions of files into
;; UNMODIFED buffers

;; *** Redefine ***
(defun later---compilation-find-file (filename)
  (let ((dirs compilation-search-path)
        (no-warn-if-buffer-unmodified t)
        result)
    (while (and dirs (null result))
      (let ((name (if (car dirs)
                      (concat (car dirs) filename)
                    filename)))
        (setq result
              (and (file-exists-p name)
                   (find-file-noselect name nil))))
      (setq dirs (cdr dirs)))
    result))




;;;; C mode


(load "gensym-c-mode")




;;;; Word selection via mouse


;;; Modify this function to optionally save the selection on the kill ring if
;;; it was a WORD selection (double click).

(defvar save-mouse-word-selection-in-kill-ring t)

;; *** Redefine ***
(defun mouse-track-maybe-own-selection (pair type)
  (let ((start (car pair))
        (end (cdr pair)))
    (or (= start end) (push-mark (if (= (point) start) end start)))
    (cond (zmacs-regions
           (if (= start end)
               nil
             (zmacs-activate-region)
             (setq zmacs-region-stays t)))
          ((eq window-system 'x)
           (if (= start end)
               (x-disown-selection type)
             (x-own-selection (cons (set-marker (make-marker) start)
                                    (set-marker (make-marker) end))
                              type))))
    (if (and (eq window-system 'x)
             (not (= start end)))
        (x-store-cutbuffer (buffer-substring start end)))

    ;; Code added.
    (if (and save-mouse-word-selection-in-kill-ring
             (eq mouse-track-type 'word))
        (let ((this-command nil))        ; *** Do not let it reset this-command.
          (copy-region-as-kill start end)))))



;;;; Emacs command history.


(defun previous-kill-or-history-element (arg)
  (interactive "p")
  (cond ((eq last-command 'yank)
         (call-interactively 'yank-pop arg))
        ;; last-command is t sometimes. I have no idea why.
        ((memq last-command '(t repeat-complex-command repeat-matching-complex-command))
         (setq this-command 'repeat-complex-command)
         (previous-history-element arg))
        (t
         (error "Previous command, %s, must be yank or repeat-complex-command" last-command))))


(define-key global-map "\C-\M-y" 'repeat-complex-command)
(define-key minibuffer-local-map "\M-y" 'previous-kill-or-history-element)

;; Electric-command-history pops up a mouse-sensitive command history.
(define-key global-map "\C-x\C-y" 'electric-command-history)



;;;; News and Mail

;;; Creating new file, 11/11/02.  Code in gensym-news-mail.el used to be inlined
;;; here.  It appears to still work with XEmacs 19.13.  I don't know how well
;;; it works or ever worked with FSF emacs, but it was always included when it
;;; was here, so continue to include it.  It doesn't work with XEmacs 21.

(cond
  ((not xemacs-21-0-p)
   (load "gensym-news-mail")))


;; The default, but just to be sure.
(define-key global-map "\M-\C-l" 'switch-to-other-buffer-but-never-bury-it)



;;;; Make G2 sections behave like pages.


(defun better-page-forward ()
  "Move forward one page, and put top of page at top of window."
  (interactive)
  (end-of-line)
  (call-interactively 'forward-page)
  (beginning-of-line)
  (recenter 0))

(defun better-page-backward ()
  "Move backward one page, and put top of page at top of window."
  (interactive)
  (backward-char)
  (call-interactively 'backward-page)
  (beginning-of-line)
  (recenter 0))

(define-key lisp-mode-map "\C-x[" 'better-page-backward)
(define-key lisp-mode-map "\C-x]" 'better-page-forward)

;; Also, we set page-delimiter to ";;;;", below.


;;;; VM

;; To pick up the mode-motion handler.
(add-hook 'vm-mode-hook 'ab-setup-mail-and-news)




;;;; Font lock

(cond (xemacs-21-0-p
       ) ; gensym-fonts doesn't currently work: no definition for refontify-buffer
      (xemacs-p
       (load "gensym-fonts"))
      ((and fsf-emacs-p window-system)
       (load "gensym-fonts-fsf")))




;;;; Postscript printing

(autoload 'ps-print-buffer-with-faces ps-print-location nil t)

;; Was: (underline font-lock-string-face)
(setq ps-underline-faces nil)

(defun ps-print ()
  "The same as ps-print-buffer-with-faces.  C-U prefix sends to file"
  (interactive)
  (call-interactively 'ps-print-buffer-with-faces))



;;;; List definitions, mouse handling for Occur Mode and Compile mode


(defvar *list-definitions-regexp* "^(def"
  "*Regexp used by list-definitions (\\[list-definitions]) to decide
        what to show (namely, lines that match this). The default should
        be correct for Lisp code.")

(defun list-definitions ()
  "Like its namesake under ZM*CS: puts the list in another buffer,
       where \\<occur-mode-map>\\[occur-mode-goto-occurrence] can be used to get to the
       definitions (see OCCUR for more details). By default,
       uses a regexp that finds Lisp def-forms: with ARG non-nil, uses
       a regexp that also lists CFG language constructs."
  (interactive)
  (save-excursion
    (goto-char (point-min))
    (occur *list-definitions-regexp*)))



;; Have to advise occur-mode since there is no occur-mode-hook

(defvar old-occur-mode-function (symbol-function 'occur-mode))

(defun new-occur-mode ()
  (funcall old-occur-mode-function)
  (setq mode-motion-hook 'mode-motion-highlight-line))

;; *** Advise ***
(fset 'occur-mode 'new-occur-mode)


(defun occur-mode-find-def (event)
  (interactive "@e")
  (mouse-set-point event)
  (occur-mode-goto-occurrence))

(cond (xemacs-p
       (define-key occur-mode-map '(button2) 'occur-mode-find-def)))


;;; Do the same thing for compilation-mode (error messages and grep output).

(require 'compile)

;; Bound to mouse-middle, and hacked to speed up grep-for-lisp-symbol.

(defun faster-compile-mouse-goto-error (event)
  "Visit the source for the error under the mouse.
Use this command in a compilation log buffer."
  (interactive "e")
  (mouse-set-point event)
  (beginning-of-line)
  (faster-compile-goto-error))

(cond (xemacs-p
       (define-key compilation-mode-map '(button2) 'faster-compile-mouse-goto-error)))




;; If point is on a line in the *grep* buffer, find that file and line.
;; This is used to speed up next-error and mouse-middle in this case.

(defun faster-compile-goto-error ()
  (let* ((error-buffer (current-buffer))
         (directory (save-excursion (set-buffer error-buffer) default-directory)))

    (beginning-of-line)
    ;; Is it grep-for-lisp-symbol output?
    (cond ((looking-at "^\\([a-z0-9-]*\\.lisp\\):\\([0-9]*\\):")
           (let* ((file-name (buffer-substring (match-beginning 1) (match-end 1)))
                  (line-number (car (read-from-string (buffer-substring (match-beginning 2) (match-end 2)))))
                  (pathname (format "%s%s" directory file-name))
                  (buffer (find-file-noselect pathname)))
             ;; This is the best I could do with the windows.
             (other-window 1)
             (switch-to-buffer buffer)
             (goto-line line-number)))
          (t
           (compile-goto-error)))))



;;;; Common Lisp indentation

;;; In order to indent backquoted forms properly, we have to copy and change one
;;; line in the brain-dead common-lisp-indent-function.  Marked with ***.
;;; Also, fixed performace bug: very slow indentation at end of buffers.


(defconst ab-default-list-indentation 2 "Number of spaces after the open paren.")

;;; Now redefine `lisp-indent-line' so that a single semicolon in column 0 is not
;;; moved.  (Bens' suggestion).

;; *** Redefine ***
(defun lisp-indent-line (&optional whole-exp)
  "Indent current line as Lisp code.
With argument, indent any additional lines of the same expression
rigidly along with this one."
  (interactive "P")
  (let ((indent (calculate-lisp-indent)) shift-amt beg end
        (pos (- (point-max) (point))))
    (beginning-of-line)
    (setq beg (point))
    (skip-chars-forward " \t")
    (if (looking-at "\\s<\\s<\\s<")
        ;; Don't alter indentation of a ;;; comment line.
        nil
      (if (and (looking-at "\\s<") (not (looking-at "\\s<\\s<")))
          ;; Single-semicolon comment lines should be indented
          ;; as comment lines, not as code.
          (if (zerop (current-column))        ; ***
              nil
              (progn (indent-for-comment) (forward-char -1)))
        (if (listp indent) (setq indent (car indent)))
        (setq shift-amt (- indent (current-column)))
        (if (zerop shift-amt)
            nil
          (delete-region beg (point))
          (indent-to indent)))
      ;; If initial point was within line's indentation,
      ;; position after the indentation.  Else stay at same point in text.
      (if (> (- (point-max) pos) (point))
          (goto-char (- (point-max) pos)))
      ;; If desired, shift remaining lines of expression the same amount.
      (and whole-exp (not (zerop shift-amt))
           (save-excursion
             (goto-char beg)
             (forward-sexp 1)
             (setq end (point))
             (goto-char beg)
             (forward-line 1)
             (setq beg (point))
             (> end beg))
           (indent-code-rigidly beg end shift-amt)))))


(cond ((and xemacs-p (not xemacs-21-0-p)) ; need an alternate version for XEmacs 21
       (load "gensym-indent")
       (load "cl-indent")))


;; *** Redefine ***
(defun common-lisp-indent-function (indent-point state)
  (let ((normal-indent (current-column)))
    ;; Walk up list levels until we see something
    ;;  which does special things with subforms.
    (let ((depth 0)
          ;; Path describes the position of point in terms of
          ;;  list-structure with respect to contining lists.
          ;; `foo' has a path of (0 4 1) in `((a b c (d foo) f) g)'
          (path ())
          ;; set non-nil when somebody works out the indentation to use
          calculated
          (last-point indent-point)
          ;; the position of the open-paren of the innermost containing list
          (containing-form-start (elt state 1))
          ;; the column of the above
          sexp-column)
      ;; Move to start of innermost containing list
      (goto-char containing-form-start)
      (setq sexp-column (current-column))
      ;; Look over successively less-deep containing forms
      (while (and (not calculated)
                  (< depth lisp-indent-maximum-backtracking))
        (let ((containing-sexp (point)))
          (forward-char 1)
          (parse-partial-sexp (point) indent-point 1 t)
          ;; Move to the car of the relevant containing form
          (let (tem function method)
            (if (not (looking-at "\\sw\\|\\s_"))
                ;; This form doesn't seem to start with a symbol
                (setq function nil method nil)
              (setq tem (point))
              (forward-sexp 1)
              (setq function (downcase (buffer-substring tem (point))))
              (goto-char tem)
              (setq tem (intern-soft function)
                    method (get tem 'common-lisp-indent-function))
              (cond ((and (null method)
                          (string-match ":[^:]+" function))
                     ;; The pleblisp package feature
                     (setq function (substring function
                                               (1+ (match-beginning 0)))
                           method (get (intern-soft function)
                                       'common-lisp-indent-function)))
                    ((and (null method))
                     ;; backwards compatibility
                     (setq method (get tem 'lisp-indent-function)))))
            (let ((n 0))
              ;; How far into the containing form is the current form?
              (if (< (point) indent-point)
                  (while (condition-case ()
                             (progn
                               (forward-sexp 1)
                               (if (>= (point) indent-point)
                                   nil
                                 (parse-partial-sexp (point)
                                                     indent-point 1 t)
                                 (setq n (1+ n))
                                 t))
                           (error nil))))
              (setq path (cons n path)))

            ;; backwards compatibility.
            (cond ((null function))
                  ((null method)
                   (if (null (cdr path))
                       ;; (package prefix was stripped off above)
                       (setq method (cond ((string-match "\\`def"
                                                         function)
                                           '(4 (&whole 4 &rest 1) &body))
                                          ((string-match "\\`\\(with\\|do\\)-"
                                                         function)
                                           '(4 &body))))))
                  ;; backwards compatibility.  Bletch.
                  ((eq method 'defun)
                   (setq method '(4 (&whole 4 &rest 1) &body))))

            (cond ((and (memq (char-after (1- containing-sexp)) '(?\')) ; *** Was (?\' ?\`) ***
                        (not (eql (char-after (- containing-sexp 2)) ?\#)))
                   ;; No indentation for "'(...)" elements
                   (setq calculated (1+ sexp-column)))
;; Do not indent , and ,@ forms any differently!  They're probably code, too!  -fmw, 10/6/93
;                  ((or (eql (char-after (1- containing-sexp)) ?\,)
;                       (and (eql (char-after (1- containing-sexp)) ?\@)
;                            (eql (char-after (- containing-sexp 2)) ?\,)))
;                   ;; ",(...)" or ",@(...)"
;                   (setq calculated normal-indent))
                  ((eql (char-after (1- containing-sexp)) ?\#)
                   ;; "#(...)"
                   (setq calculated (1+ sexp-column)))
                  ((null method))
                  ((integerp method)
                   ;; convenient top-level hack.
                   ;;  (also compatible with lisp-indent-function)
                   ;; The number specifies how many `distinguished'
                   ;;  forms there are before the body starts
                   ;; Equivalent to (4 4 ... &body)
                   (setq calculated (cond ((cdr path)
                                           normal-indent)
                                          ((<= (car path) method)
                                           ;; `distinguished' form
                                           (list (+ sexp-column 4)
                                                 containing-form-start))
                                          ((= (car path) (1+ method))
                                           ;; first body form.
                                           (+ sexp-column lisp-body-indent))
                                          (t
                                           ;; other body form
                                           normal-indent))))
                  ((symbolp method)
                   (setq calculated (funcall method
                                             path state indent-point
                                             sexp-column normal-indent)))
                  (t
                   (setq calculated (lisp-indent-259
                                      method path state indent-point
                                      sexp-column normal-indent)))))

          (goto-char containing-sexp)
          (setq last-point containing-sexp)
          ;; Another change: when we are at a top-level form, then the backward-up-list will    ***
          ;; fail, but not until after scanning the entire buffer back to the beginning, which  ***
          ;; is quite slow.  So, act like an error if point is now in column 0.  -fmw, 10/22/93 ***
          (if (not calculated)
              (cond ((zerop (current-column))                                ; ***
                     (setq depth lisp-indent-maximum-backtracking))    ; ***
                    (t
                     (condition-case ()
                         (progn (backward-up-list 1)
                                (setq depth (1+ depth)))
                       (error (setq depth lisp-indent-maximum-backtracking))))))
          ))
      calculated)))


(defun common-lisp-mode ()
  "Common lisp mode is identical to lisp mode."
  (interactive)
  (lisp-mode))





;;;; INDENT REGION and FILL PARAGRAPH


;; This indent region function does exactly the same thing
;; as pressing TAB on each line in the region.

(defun ab-indent-region (start end &optional indenter)
  "Perform indent-line on each line in region."
  (interactive "r")
  (let ((indenter (or indenter indent-line-function)))
    (save-excursion
      (goto-char start)
      (while (and (not (eobp))
                  (< (point) end))
        (if (and (bolp) (not (eolp)))
            (funcall indenter))
        (forward-line 1)))
    (zmacs-deactivate-region)))


(defun ab-indent-sexp ()
  "Indent each line of the sexp starting just after point."
  (interactive)
  (save-restriction
    (if (memq major-mode ilisp-modes)
        (narrow-to-region (save-excursion (lisp-input-start)) (point-max)))
    (let ((start (point))
          (end (save-excursion (forward-sexp 1) (point))))
      (ab-indent-region start end))))


;; Stolen from ilisp.
(defun ab-lisp-in-comment (test)
  "Return T if you are in a comment."
  (beginning-of-line)
  (and (looking-at test)
       (not (= (match-end 0)
               (progn (end-of-line) (point))))))



(defun ab-fill-long-comment ()
  (interactive)
  (let ((comment (concat "[ \t]*" comment-start "+[ \t]*")))
    (back-to-indentation)
    (if (looking-at comment)
        (let ((fill-prefix
                (buffer-substring
                  (progn (beginning-of-line) (point))
                  (match-end 0))))

          (while (and (not (bobp)) (ab-lisp-in-comment comment))
            (forward-line -1))
          (if (not (bobp)) (forward-line 1))
          (let ((begin (point)))
            (while (and (ab-lisp-in-comment comment) (not (eobp)))
              (replace-match fill-prefix)
              (forward-line 1))
            (if (not (eobp))
                (progn (forward-line -1)
                       (end-of-line)
                       (forward-char 1)))
            (fill-region-as-paragraph begin (point)))))))


(defun ab-fill-paragraph ()
  "Fill a long comment, if point is in the midst of one. Else,
 if there is a region, reindent that. Else, reindent the current defun."
  (interactive)
  (cond ((save-excursion
           (beginning-of-line)
           ;; We used to insist that the comment be at toplevel, but now we
           ;; allow internal comments which are on a line by theirself.  This
           ;; means that to indent the defun the cursor must not be on a
           ;; comment line.
           (looking-at (concat "^[ \t]*" comment-start)))

         (if (zmacs-region-present-p)
             (save-restriction
               (narrow-to-region (min (point) (mark)) (max (point) (mark)))
               (ab-fill-long-comment))
           (ab-fill-long-comment)))
        ((zmacs-region-present-p)
         (save-excursion
           (call-interactively 'ab-indent-region)))
        (t
          (save-excursion
            (mark-defun)
            (call-interactively 'ab-indent-region)))))


(define-key lisp-mode-map "\M-q" 'ab-fill-paragraph)
(define-key lisp-mode-map "\C-\M-\\" 'ab-indent-region)

(define-key emacs-lisp-mode-map "\M-q" 'ab-fill-paragraph) ; Was lisp-fill-paragraph
(define-key emacs-lisp-mode-map "\C-\M-\\" 'ab-indent-region)



;;;; Document G2 function.


(defun document-g2-function ()
  "Start off a doc string for the current definition, following the G2 documentation standards."
  (interactive)
  (if (not (looking-at "^\\s("))
      (beginning-of-defun))
  (if (save-excursion (re-search-forward "^\\s(\\([^ ]+\\)[ (]*\\([^ \n\t)]*\\)" nil t))
      (let* ((definer (buffer-substring (match-beginning 1) (match-end 1)))
             (function-name (buffer-substring (match-beginning 2) (match-end 2)))
             (pretty-definer (cond ((equal definer "defun-simple")
                                    "simple function")
                                   ((or (equal definer "defun")
                                        (string-match "\\`defun-" definer))
                                    "function")
                                   ((equal definer "defmacro")
                                    "macro")
                                   ((equal definer "defvar")
                                    "variable")
                                   ((equal definer "defparameter")
                                    "parameter")
                                   ((string-match "\\`define-" definer)
                                    (substring definer (match-end 0)))
                                   ((string-match "\\`def-" definer)
                                    (substring definer (match-end 0)))
                                   (t
                                    definer))))
        (open-line 2)
        (insert (format ";;; The %s `%s' " pretty-definer function-name)))))

;; control-meta-shift-d
(cond (xemacs-p
       (define-key lisp-mode-map '(control meta D) 'document-g2-function))
      (fsf-emacs-p
       (define-key lisp-mode-map (read "[?\\C-\\M-\\S-d]") 'document-g2-function)))



;;;; Mark of the author.


(defvar names-of-months '("Jan" "Feb" "Mar" "Apr" "May" "Jun" "Jul" "Aug" "Sep" "Oct" "Nov" "Dec"))

(defun short-date-string ()
  "Like, 1-Sep-93"
  (let* ((time (current-time-string))
;         (day (substring time 0 3))
         (month (substring time 4 7))
         (date (substring time 8 10))
         (year (substring time 22 24)))
    (if (= (aref date 0) ? ) (setq date (substring date 1)))
    (format "%s-%s-%s" date month year)))

(defun number-of-month (month)
  (let ((list names-of-months)
        (i 1))
    (while (not (equal month (car list)))
      (setq i (+ i 1))
      (setq list (cdr list)))
    i))

(defun numerical-date-string ()
  "Like, 9/1/93"
  (let* ((time (current-time-string))
;         (day (substring time 0 3))
         (month (substring time 4 7))
         (date (substring time 8 10))
         (year (substring time 22 24)))
    (if (= (aref date 0) ? ) (setq date (substring date 1)))
    (format "%s/%s/%s" (number-of-month month) date year)))


(defun insert-mark-of-the-author ()
  "Insert the author's initials and the current date, like this: -fmw, 9/1/93"
  (interactive)
  (insert (format "-%s, %s" (or (getenv "USER") (getenv "USERNAME"))
                  (numerical-date-string))))


(define-key global-map "\C-xc" 'insert-mark-of-the-author)



;;;; Hack


(defun ltrb ()
  "Replicate text, replacing left with top, right, and bottom.
 If there is a region, use that.  Else if the current line is non-blank, use that.
 Otherwise, use the previous line"
  (interactive)
  (save-excursion
    (save-restriction
      (let (start end)
        (cond ((zmacs-region-present-p)
               (setq start (min (point) (mark))
                     end (max (point) (mark))))
              (t
               (beginning-of-line)
               (if (or (eobp) (looking-at "^[ \t]*\n"))
                   (previous-line 1))
               (setq start (point)
                     end  (progn (end-of-line) (forward-char 1) (point)))))

        (let ((string (buffer-substring start end)))
          (ltrb-step string "left" "top")
          (ltrb-step string "left" "right")
          (ltrb-step string "left" "bottom"))))))

(defun ltrb-step (string old new)
  (let (start end)
    (setq start (point))
    (insert string)
    (setq end (point))
    (narrow-to-region start end)
    (goto-char start)
    (replace-string old new)
    (end-of-line)
    (forward-char 1)))





;;;; COMMENT/UNCOMMENT-REGION.


;;; This code is stolen from ilisp, but should work in any language
;;; mode which defines comment-start and comment-end
;; comment-region is now prt of emacs.



;;; A versatile function to bind to c-;

(defun comment-or-uncomment-region (&optional arg)
  "If no region exists, indent for comment on current line. If a region exists,
 then comment it out if no arg, or uncomment it if a single c-u arg."
  (interactive "P")
  (cond ((not (zmacs-region-present-p))
         (call-interactively 'indent-for-comment))
        ((equal (prefix-numeric-value arg) 4) ; Single c-u prefix => uncomment.
         (comment-region (min (point) (mark)) (max (point) (mark)) -1))
        (t
         (call-interactively 'comment-region)))
  ;; This call should not be needed.
  (zmacs-deactivate-region))


(cond (xemacs-p
       (define-key global-map '(control meta 59) 'kill-comment)
       (define-key global-map '(control 59) 'comment-or-uncomment-region))
      (fsf-emacs-p
       (define-key global-map (read "[?\\C-\\M-;]") 'kill-comment)
       (define-key global-map (read "[?\\C-;]") 'comment-or-uncomment-region)))

;; 59 is a semicolon (the keysym "semicolon" does not work.)





;;;; FORWARD-SEXP: go up one level if there is no next sexp.

(defun forward-sexp-or-up-list (&optional arg)
  (interactive "p")
  (cond ((zerop arg))
        ((> arg 0)
         (while (> arg 0)
           (condition-case ()
               (forward-sexp 1)
             (error
              (up-list 1)))
           (setq arg (- arg 1))))
        (t
         (while (< arg 0)
           (condition-case ()
               (backward-sexp 1)
             (error
              (backward-up-list 1)))
           (setq arg (+ arg 1)))))
  (setq zmacs-region-stays t))


(defun backward-sexp-or-up-list (&optional arg)
  (interactive "p")
  (forward-sexp-or-up-list (- arg))
  (setq zmacs-region-stays t))

(define-key emacs-lisp-mode-map "\C-\M-f" 'forward-sexp-or-up-list)
(define-key emacs-lisp-mode-map "\C-\M-b" 'backward-sexp-or-up-list)
(define-key lisp-mode-map "\C-\M-f" 'forward-sexp-or-up-list)
(define-key lisp-mode-map "\C-\M-b" 'backward-sexp-or-up-list)




;;;; Machinations to make emacs more like the Explorer's Zmacs.


;;; Explorer-compatible point pdl.
;;; Most of this is already implemented in etags.el -- we
;;; simply define a function to bind to c-SPACE>

(defun set-pop-mark (&optional arg)
  "Sets or pops a an emacs-wide marker, that is, one which remembers
both the point and the buffer in which the point resided.
With no argumnt: set mark at point and push buffer and point onto pdl.
With c-U: pops the point pdl.
With two C-u's: pops the point pdl and throws it away."
  (interactive "p")
  (cond ((equal arg 1)
         (push-tag-mark)
         (set-mark-command nil))
        ((equal arg 4)
         (pop-tag-mark nil))
        ((equal arg 16)
         (save-excursion
           (pop-tag-mark nil)))))

;; Only the real emacs m-. (find-tag) pushes onto this mark stack.
;; Ilisp's will have to be modified to do the same.
;; Also, other mark setting commands (m-<, m->, etc), push ont
;; a *different* stack!

;;; Bind the cross-buffer mark command to m-space.
(cond (xemacs-p
       (define-key global-map '(meta space) 'set-pop-mark))
      (fsf-emacs-p
       (define-key global-map (read "[?\\M- ]") 'set-pop-mark)))



;;;; GREP lisp sources


;;; Patched popper-show to adjust initial window size.
(defvar popper-default-window-size nil)


(defun user-lisp-sandbox ()
  (let ((sandbox (or (getenv "LISP_DIR")
                     (format "/bt/%s/lisp" (getenv "USER")))))
    (if (and (not (file-exists-p sandbox))
             (get-buffer "*lucid*")
             (get-buffer "*allegro*"))
        (setq sandbox (abbreviate-file-name (save-excursion
                                              (or (set-buffer "*lucid*")
                                                  (get-buffer "*allegro*"))
                                              default-directory))))
    sandbox))


(defun default-grep-pattern (&optional prompt)
  (let* ((default (unquoted-find-tag-default))
         (prompt (or prompt  "Pattern [%s]: "))
         (pattern (if xemacs-p
                      (read-tag-with-completion prompt default)
                      (read-string (format prompt default)))))
    (if (equal pattern "")
        (list default)
        (list pattern))))


;; This is unfinished.
(defun faster-next-error ()
  (interactive)
  (let ((buffer (current-buffer)))
    (set-buffer (compilation-find-buffer))
    (beginning-of-line)
    (if (= (point) (point-min))
        (next-line 1))
    (next-line 1)
    (condition-case ()
        (compile-goto-error)
      (error
        (switch-to-buffer buffer)))))


;;; Search the lisp sources in local sandbox for a symbol or a pattern.

(defconst format-string-for-grep
  (if (mswin-emacs-p)
      "%s \"%s\""
      "%s '%s'"))


(defun ab-grep-lisp-sandbox (pattern)
  "Search the lisp files in your sandbox for a lisp symbol or a grep pattern.
With a positive numeric argument, search for a grep pattern.
With a negative numeric argument, search for a grep pattern but be case sensitive.
with a zero argument, prompt for an additional string which must be present on each line.
You can step through the hits with next-error (\\[next-error])."
  (interactive (default-grep-pattern (if current-prefix-arg "Pattern [%s]: " "Lisp Symbol [%s]: ")))
  (let ((prefix (prefix-numeric-value current-prefix-arg)))
    (cond ((= prefix 1)
           (compile-internal (format format-string-for-grep
                                     grep-for-lisp-symbol
                                     (downcase pattern))
                             "No more grep hits" "grep"))
          ((= prefix 0)
           (let ((filter (read-string "Additional word to filter upon: ")))
             (compile-internal
               (format "%s '%s' | egrep %s"
                       grep-for-lisp-symbol
                       (downcase pattern) filter)
               "No more grep hits" "grep")))
          (t
           (grep (format "%s\"%s\" %s/*.lisp"
                         (if (< prefix 0) "" "-i ")
                         pattern
                         (user-lisp-sandbox)))))))


(cond (xemacs-p
       (define-key global-map '(meta G) 'ab-grep-lisp-sandbox))
      (fsf-emacs-p
       (define-key global-map (read "[?\\M-G]") 'ab-grep-lisp-sandbox)))



;;;; Random mouse commands.

(defun s-expression-at-point ()
  (let (start end)
    (save-excursion
      (cond ((looking-at ")")                ; end of list
             (setq end (point))
             (forward-char 1)
             (backward-sexp 1)
             (setq start (point)))
            ((or (looking-at "(")        ; Start of list.
                 (looking-at "\""))        ; start or end of string? Assume start.
             (setq start (point))
             (forward-sexp 1)
             (setq end (point)))
            ((eolp)                        ; Beyond end of line, take entire line (including cr)
             (beginning-of-line)
             (setq start (point))
             (forward-line 1)
             (setq end (point)))
            ((looking-at "#<")
             (setq start (point))
             (if (re-search-forward "@[0-9]+>" (+ start 80) t)
                 (setq end (match-end 0))
                 (setq end start)))
            ((char-equal (following-char) ?') ; Include single quote if clicked right on it.
             (setq start (point))
             (forward-sexp 1)
             (setq end (point)))
            (t                                ; Symbols, etc.
             (if (not (or (char-equal (preceding-char) ?') ; KLudge. Want, any non-symbol char.
                          (char-equal (char-syntax (preceding-char)) ? )))
                 (backward-sexp 1))
             (if (char-equal (following-char) ?')
                 (forward-char 1))
             (setq start (point))
             (forward-sexp 1)
             (if (or (char-equal (preceding-char) ?:)        ; Drop a trailing colon or comma.
                     (char-equal (preceding-char) ?,))
                 (forward-char -1))
             (setq end (point)))))
    (buffer-substring start end)))


(defun ab-delimit-common-lisp-symbol ()
  "Return a cons of (start . end) for CL symbol around point."
  (let (start end)
    (cond ; ((within-comment-p)
          ;  nil)
          (t
           (mouse-track-beginning-of-word t)
           (if (looking-at "`\\|'")
               (forward-char 1))
           (if (looking-at "#<\\|#+\\|#-")
               (forward-char 2))
           (setq start (point))

           (mouse-track-end-of-word t)
           (if (= (preceding-char) ?.)
               (backward-char 1))
           (if (= (preceding-char) ?')
               (backward-char 1))

           (cond ((memq (preceding-char) '(? ?\t))
                  nil)
                 (t
                  (setq end (point))
                  (cons start end)))))))


(defun common-lisp-symbol-at-event (event)
  (let (spot symbol)
    (save-window-excursion
      (save-excursion
        (mouse-set-point event)
        (setq spot (ab-delimit-common-lisp-symbol))
        (if spot
            (setq symbol (buffer-substring (car spot) (cdr spot))))))
    symbol))

(defun s-expression-at-event (event)
  (let (sexp)
    (save-window-excursion
      (save-excursion
        (mouse-set-point event)
        (setq sexp (s-expression-at-point))))
    sexp))

(defun tag-name-at-event (event)
  (let (tag)
    (save-window-excursion
      (save-excursion
        (mouse-set-point event)
        (setq tag (common-lisp-default-tag))))
    tag))


(defun mouse-insert-sexp-at-point (event)
  "Grab the S-expression under the mouse, and insert it at point."
  (interactive "e")
  (let* ((sexp (s-expression-at-event event))
         (here (point))
         (reindent-p (save-excursion
                       (= here
                          (progn (beginning-of-line)
                                 (skip-chars-forward " \t" here)
                                 (point)))))
         (space-p (save-excursion
                    (forward-char -1)
                    (not (looking-at "[ \t\n()\"\']")))))

    (message "Indent %s  space %s" reindent-p space-p)
    (sit-for 1)

    ;; Insert a space first if no whitespace.
    (if space-p (insert " "))

    (insert sexp)

    ;; Re-Indent line if we are first on it.
    (if (and reindent-p (key-binding 'tab))
        (save-excursion
          (goto-char here)
          (call-interactively (key-binding 'tab))))))


(defun mouse-edit-thing (event)
  "Find-tag or find-file on the thing under the mouse.  Interpreted as a filename if you click
 on the leading double-quote of a string."
  (interactive "@e")
  (let ((thing (if (eq major-mode 'lisp-mode)
                   (common-lisp-symbol-at-event event)
                   (tag-name-at-event event))))
    (cond ((char-equal (aref thing 0) ?\")
           (let ((filename (condition-case ()
                               (car (read-from-string thing))
                             (error nil))))
             (display-image filename)))

          (t
           (message (format "Find tag %s" thing))
           (find-tag (regexp-quote thing))))))


;;; Mark the S-expression under mouse, and leave point nearby.

(defun mouse-mark-sexp (event)
  "Mark the s-expression under mouse."
  (interactive "@e")
  (mouse-set-point event)
  (cond ((looking-at ")")
         (forward-char 1)
         (mark-sexp -1))
        ((looking-at "(")
         (mark-sexp 1))
        (t
         (backward-sexp 1)
         (mark-sexp 1))))

(defun mouse-extend-region (event)
  "Set mark and activate the region."
  (interactive "@e")
  (mouse-set-mark event)
  (zmacs-activate-region))

;; On the explorer, this is bound to the middle button, but in emacs
;; the middle button normally means insert-current-X-selection.
;; So I arbitrarily bind it to control-Left, for now. -fmw

(cond (xemacs-p
       ;; Ought to be bound to double-left, probably.
       (define-key global-map '(control button1) 'mouse-mark-sexp)
       (define-key global-map '(control button2) 'mouse-insert-sexp-at-point)
       (define-key global-map 'button3 'mouse-extend-region)
       (define-key global-map '(meta button1) 'mouse-edit-thing)))


;; Mouse scroll button... for use with PC X servers... with XWin 32 at least,
;; the scroll button is mapped to button 4 for up, button 5 for down.
;; Set appropriate bindings for those buttons.  Note that Emacs running on
;; a PC has a different interpretation of the scroll button; it becomes a
;; "vertical-scroll-bar" keystroke, which is handled correctly, in 20.7.1,
;; at least.
;;
;; I'm not sure eXceed will map the button the same way, and if there are any
;; four or five button mice for Unix boxes, this may cause some unintended
;; results; however, for now, I feel pretty confident this won't break anything
;; and it's pretty cool to have it work with the PC X server.  - jv, 1/31/02

; XEmacs only; seems that using scroll-up works just as well
;(defun scroll-up-this-window ()
;  (interactive)
;  (scrollbar-line-up (selected-window)))
;
;(defun scroll-down-this-window ()
;  (interactive)
;  (scrollbar-line-down (selected-window)))

(defun scroll-up-this-window ()
  (interactive)
  (scroll-up scroll-step))

(defun scroll-down-this-window ()
  (interactive)
  (scroll-down scroll-step))

(cond (xemacs-p
       (define-key global-map 'button4 'scroll-down-this-window)
       (define-key global-map 'button5 'scroll-up-this-window))
      (t
       (define-key global-map '[mouse-4] 'scroll-down-this-window)
       (define-key global-map '[mouse-5] 'scroll-up-this-window)))


;;;; Simple view mode

(defvar simple-view-mode-map nil)

(defun define-simple-view-mode-bindings (map)
  (suppress-keymap map)                        ; Turn off self-inserting chars.
  (define-key map " " 'scroll-up)
  (define-key map "f" 'scroll-up)
  (define-key map "\177" 'scroll-down)
  (define-key map "b" 'scroll-down)
  (if xemacs-p
      (progn
        (define-key map 'backspace 'scroll-down)
        (define-key map 'delete 'scroll-down))))

(if simple-view-mode-map
    ()
  (setq simple-view-mode-map (make-keymap))
  (define-simple-view-mode-bindings simple-view-mode-map))



(defun simple-view-mode ()
  "A simple mode for viewing text. Binds SPACE/DELETE to page forward/backward"
  (interactive)
  (setq mode-name "SimpleView")
  (setq major-mode 'simple-view-mode)
  (use-local-map simple-view-mode-map)
  (if xemacs-p
      (file-mode))                        ; Make filenames sensitive.
  (setq buffer-read-only t))




;;;; Handy functions.


(defun insert-intro-for-er-warnings (product space-before-p)
  (if space-before-p
      (insert "\n\n"))
  (let ((file
          (cond
            ((eq product 'g2) file-for-g2-eternal-recompile)
            ((eq product 'tw) file-for-tw-eternal-recompile)
            ((eq product 'gsi) file-for-gsi-eternal-recompile))))
    (insert (format ";;;; %s  (%s)\n\n" product file))
    (insert-file file)))


(defun warnings-from-external-recompile ()
  "Get G2 warnings from last eternal recompile.
The buffer is in lisp mode so that meta-left click can be used to edit functions."
  (interactive)
  (switch-to-buffer (get-buffer-create "*Eternal Recompile*"))
  (toggle-read-only -1)
  (erase-buffer)
  (insert-intro-for-er-warnings 'g2 nil)
  (end-of-buffer)
  (insert-intro-for-er-warnings 'tw t)
  (end-of-buffer)
  (insert-intro-for-er-warnings 'gsi t)
  (lisp-mode)
  (beginning-of-buffer)
  (toggle-read-only 1))


(defun view-file-simple (filename)
  "View file in readonly mode.  Get the latest version w/o warning."
  (let ((buffer (find-file-noselect filename t)))
    (switch-to-buffer buffer)
    (if (null (verify-visited-file-modtime (current-buffer)))
        (progn
          (toggle-read-only -1)
          (message "Reading new version of %s" filename)
          (revert-buffer t t)
          (toggle-read-only 1)))
    (simple-view-mode)))



(defun file-size (filename)
  (nth 7 (file-attributes filename)))



;;;; Find C source

(load "find-c-source")



;;;; ILISP and customizations

(if ilisp-directory
  ;; Use the new ilisp
  (setq load-path (cons ilisp-directory load-path)))


(cond
  ((and (boundp 'use-lep) use-lep)
   (load "gensym-lep"))
  ((and xemacs-p (not xemacs-21-0-p))
   (load "gensym-ilisp"))

  (fsf-emacs-p
   ;; GNU emacs used for CVS editing, so defer ilisp there.
   (add-hook 'ilisp-site-hook '(lambda () (load "gensym-ilisp")))
   (autoload 'lucid "ilisp" "Inferior Lucid Common LISP." t)
   (define-key global-map "\C-c\C-l" 'lucid)
   (define-key lisp-mode-map "\C-c\C-l" 'lucid)))


;;;; GDB

(load "gensym-gdb")


;;;; Pathname operations

(if xemacs-p
    (load "gensym-files"))


;;;; Gensym menu

(if xemacs-p
    (load "gensym-menu"))


;;;; Weather

(if (boundp 'use-gensym-weather)
    (load "gensym-weather"))


;;;; Comint mode


(require 'comint)


(defun comint-show-output-classic ()
  "Display start of this batch of interpreter output at top of window. Also put cursor there."
  (interactive)
  (goto-char comint-last-input-end)
  (backward-char)
  (beginning-of-line)
  (set-window-start (selected-window) (point))
  (end-of-line))

(add-hook 'comint-mode-hook
          '(lambda ()
            (define-key comint-mode-map "\C-c\C-r" 'comint-show-output-classic)
            ;; Yuck. 19.12 binds c-U to erase line in comint.  Some feature.
            ;; Only shells should do that.
            (if xemacs-p
                (define-key comint-mode-map "\C-u" 'universal-argument))))



;;;; Shell Mode - Synch Emacs State with Prompt


(define-key global-map [(control c)(control k)] 'shell)

(load "gensym-shell")



;;;; Patches for brain dead features


(cond (xemacs-p
       ;; Should not be necessary to load this under XEmacs 21; I would prefer
       ;; that any patches that are actually necessary in both versions actually
       ;; be copied into both files.  But for now, just load the 19.12 patches
       ;; into any version.  -jv, 11/20/07
       (load "gensym-19-12-patches")))

(cond (xemacs-21-0-p
       (load "gensym-21-0-patches")))



;;;; Easy way to get latest changes to this file.


(defun update-emacs ()
  "Load the latest version of Mr. AB's XEmacs utilities, ilisp, etc."
  (interactive)
  (load (concat ab-emacs-directory "gensym-emacs"))
  (define-ilisp-keys)
  (enable-presentations))


(load "ilisp")

;;;; Mr. AB's patches to some ilisp functions.

;;; These patches are relative to the ILISP 5.6


;; Whether to fontify output from the lisp subprocess.  Setting this to T
;; can lock up emacs for voluminous output.
(defvar fontify-ilisp-output nil)


;; *** Redefined (from comint-ipc) to make output fontification optional.
(defun comint-insert (output)
  "Insert process OUTPUT into the current buffer."
  (if output
      (let* ((buffer (current-buffer))
             (process (get-buffer-process buffer))
             (mark (process-mark process))
             (window (selected-window))
             (at-end nil))
        (if (eq (window-buffer window) buffer)
            (setq at-end (= (point) mark))
            (setq window (get-buffer-window buffer)))

        (save-excursion
          (goto-char mark)
            ;; Don't always fontify output. Locks up emacs for voluminous output.
          (let ((font-lock-mode (if fontify-ilisp-output font-lock-mode nil)))
            (insert output))
          (set-marker mark (point)))

        (if window
            (progn
              (if (or at-end comint-always-scroll) (goto-char mark))
              (if (not (pos-visible-in-window-p (point) window))
                  (let ((original (selected-window)))
                    (save-excursion
                      (select-window window)
                      (recenter '(center))
                      (select-window original)))))))))



;; *** Redefined (ilisp-out)
(defun ilisp-display-output-in-echo-area (output)
  "Display output as a message in the echo area."
  ;; First clear any existing typeout so as to not confuse the user.
  (or (eq (selected-window) (ilisp-output-window))
      (ilisp-bury-output))
  ;; Format it else %'s in the output will confuse things.
  (message "%s" output))



;; *** Redefined (ilisp-snd)
(defun ilisp-send (string &optional message status and-go handler)
  "Send STRING to the ILISP buffer, print MESSAGE set STATUS and
return the result if AND-GO is NIL, otherwise switch to ilisp if
and-go is T and show message and results.  If AND-GO is 'dispatch,
then the command will be executed without waiting for results.  If
AND-GO is 'call, then a call will be generated. If this is the first
time an ilisp command has been executed, the lisp will also be
initialized from the files in ilisp-load-inits.  If there is an error,
comint-errorp will be T and it will be handled by HANDLER."
  (ilisp-init t)
  (let ((process (ilisp-process))
        (dispatch (eq and-go 'dispatch)))
    (if message
        (message "%s" (if dispatch
                          (concat "Started " message)
                          message)))
    ;; No completion table
    (setq ilisp-original nil)
    (if (memq and-go '(t call))
        (progn (comint-send process string nil nil status message handler)
               (if (eq and-go 'call)
                   (call-defun-lisp nil)
                   (switch-to-lisp t t))
               nil)
        (let* ((save (ilisp-value 'ilisp-save-command t))
               (result
                 (comint-send
                   process
                   (if save (format save string) string)
                   ;; Interrupt without waiting
                   t (if (not dispatch) 'wait) status message handler)))
          (if save
              (comint-send
                process
                (ilisp-value 'ilisp-restore-command t)
                t nil 'restore "Restore" t t))
          (if (not dispatch)
              (progn
                (while (not (cdr result))
                  ;; In Emacs 19.11, simply (accept-process-output) caused us
                  ;; to sometimes hang here until some X event.  Waiting
                  ;; explicitly for the ilisp process seems to work
                  ;; better. -fmw, 9/21/94
                  ;; In Emacs 19.12+, that bug appears to be fixed, and the
                  ;; workaround causes a different hang. -fmw, 9/7/95
                  (cond (xemacs-p
                         (accept-process-output)
                         (sit-for 0))
                        (t
                         (sit-for 0)
                         (accept-process-output process)
                         (sit-for 0))))
                (comint-remove-whitespace (car result))))))))




;;; Smash lisp-find-file, which recurses infinitely on automounted symlinks.

;; *** Redefined (ilisp-hi) ***
(defun lisp-find-file (file &optional pop no-name)
  "Redefined to simply call find-file."
  (find-file file))


(defun trim-interior-whitespace (string)
  "Collapse all newlines followed by whitespace into just one space."
  (replace-regexp-in-string "\n[ \t]*"
                            " "
                            string))


(defun replace-regexp-in-string (regexp newtext string)
  "Replace all occurances of regexp in string with newtext."
  (let ((result "") (start 0) mb me)
    (while (string-match regexp string start)
      (setq mb (match-beginning 0)
            me (match-end 0)
            result (concat result
                           (substring string start mb)
                           newtext)
            start me))
    (if mb                        ; matched at least once
        (concat result (substring string start))
        string)))




;; Our output display function.

(defun ab-display-output (string)
  ;; New: note which lisp process said this.
  (let ((name ilisp-buffer))
    (if (not (string= ilisp-buffer "*lucid*"))
        (setq string (format "[%s]: %s"
                             (substring name 1 (1- (length name)))
                             string))))

  (cond ((eq this-command 'arglist-lisp)
         ;; Have remove any interior newlines and extra whitespace in the
         ;; string. (ie, undo print-pretty).
         (ilisp-display-output-in-echo-area (trim-interior-whitespace string)))
        ((eq this-command 'describe-function-lisp)
         (ilisp-display-output-in-typeout-window string))
        (t
         (ilisp-display-output-default string))))

(setq ilisp-display-output-function 'ab-display-output)




;;;; Add a describe-variable command, like c-sh-V on the lispm.

(defvar ilisp-describe-variable-command "(ILISP::ilisp-describe-variable \"%s\" \"%s\")")

(defun describe-variable-lisp (sexp)
  "Describe the preceding variable.
With a negative prefix, prompt for the variable."
  (interactive
   (list
    (if (lisp-minus-prefix)
        (ilisp-read "Describe: " (lisp-previous-sexp t))
        (if (memq major-mode ilisp-modes)
            (if (= (point)
                   (process-mark (get-buffer-process (current-buffer))))
                (or (ilisp-value 'ilisp-last-command t)
                    (error "No sexp to describe."))
                (lisp-previous-sexp t))
            (lisp-previous-sexp t)))))
  (let ((result
         (ilisp-send
          (format (ilisp-value 'ilisp-describe-variable-command)
                  (lisp-slashify sexp) (lisp-buffer-package))
          (concat "Describe " sexp)
          'describe)))
    (lisp-display-output result)))




;;;; Add a describe-function command, like c-sh-D or m-sh-D on the lispm.

(defvar ilisp-describe-function-command "(ILISP::ilisp-describe-function \"%s\" \"%s\")")

(defun describe-function-lisp (symbol)
  "Print the current function's arglist and documentation.
With a negative prefix, prompt for the function name."
  (interactive
   (let* ((function (lisp-function-name)))
     (list (if (lisp-minus-prefix)
               (ilisp-read-symbol
                (format "Documentation [%s]: " (lisp-buffer-symbol function))
                function t t)
               function))))
  (let ((result
         (ilisp-send
          (format (ilisp-value 'ilisp-describe-function-command)
                  (lisp-symbol-name symbol)
                  (lisp-symbol-package symbol))
          nil
          'describe)))
    (ilisp-display-output-in-typeout-window result)))

(defun describe-function-lisp-always-prompt (symbol)
  (interactive
   (let ((function (lisp-function-name)))
     (list (ilisp-read-symbol
            (format "Documentation [%s]: " (lisp-buffer-symbol function))
            function t t))))
  (describe-function-lisp symbol))




;;; Find-tag via the source pathnames in recorded in the inferior lisp.

(defun find-tag-via-inferior-lisp (symbol)
  (interactive
    (list
      (let* ((function (lisp-function-name))
             (symbol (lisp-buffer-symbol function)))
        (ilisp-read-symbol
          (format "Edit Definition [%s]: " symbol) function nil t))))
  (let (; (lisp-edit-files nil)
        (tags-file-name nil))
    (edit-definitions-lisp symbol "any")))




;;;; Menu of symbol operations



(defvar ilisp-mouse-symbol nil)

(defconst ilisp-mouse-symbol-menu
  '("Symbol Menu:"
    ["Definition" (find-tag-with-help-from-lisp ilisp-mouse-symbol) t ""]
    ["Definition (C)" (find-c-definition ilisp-mouse-symbol) t ""]
    ["Callers" (ilisp-mouse-edit-caller-1 ilisp-mouse-symbol) t ""]
    ["Grep" (ab-grep-lisp-sandbox ilisp-mouse-symbol) t ""]))


(defun find-tag-with-help-from-lisp (tag)
  (condition-case ()
      (find-tag tag)
    (error
      (message "%s is not in the tags table, trying lisp" tag)
      (sit-for 0)
      (find-tag-via-inferior-lisp (list nil nil tag)))))


(defun ilisp-mouse-post-symbol-menu (event)
  (interactive "e")
  (save-excursion
    (mouse-set-point event)
    (if (setq ilisp-mouse-symbol (common-lisp-symbol-at-event event))
        (popup-menu ilisp-mouse-symbol-menu)
        (beep))))


(defun make-menu-from-choices (title choices handler)
  "Handler gets the choice string."
  (let ((items ()))
    (while choices
      (let ((string (format "%s" (car choices))))
        (setq items (cons (vector string
                                  (list handler string)
                                  t
                                  "")
                          items)))
      (setq choices (cdr choices)))
    (cons title (nreverse items))))



(defun ilisp-mouse-edit-caller (event)
  (interactive "e")
  (let ((symbol (common-lisp-symbol-at-event event)))
    (ilisp-mouse-edit-caller-1 symbol)))


(defun ilisp-who-calls (symbol &optional package)
  "Return a list of callers of symbol from the underlying lisp."
  (let ((string
          (ilisp-send
            (format (ilisp-value 'ilisp-callers-command)
                    (lisp-slashify symbol)
                    (or (lisp-buffer-package) package))
            nil
            'callers)))
    (and string
         (delete t (read (concat "(" (downcase string) ")"))))))


(defun ilisp-mouse-edit-caller-1 (symbol)
  (let ((callers (ilisp-who-calls symbol)))
    (cond ((null callers)
           (error "No callers of %s found." symbol))
          (t
           (popup-menu (make-menu-from-choices "Edit Caller" callers 'find-tag))))))


(defun compile-callers (symbol)
  "Compile all of the callers of the given symbol"
  (interactive (list (read-string "Symbol: " (find-tag-default))))
  (let ((callers (ilisp-who-calls symbol "AB"))
        (fun nil))
    (message "There are %d callers of %s" (length callers) symbol)
    (sit-for 0)
    (while callers
      (setq fun (format "%s" (car callers))
            callers (cdr callers))
      (condition-case ()
          (progn
            (find-tag fun)
            (compile-defun-lisp))
        (error
          (message "Cannot compile %s.  Continuing" fun)
          (sit-for 0))))))



;;;; Matchup argument lists


(defconst ilisp-matchup-arguments-command "(ilisp::ilisp-align-arguments \"%s\")")

(defun matchup-arguments-lisp ()
  "Line up the dummy and actual arguments in the current form"
  (interactive)
  (let (start end error-p)
    (save-excursion
      (backward-up-list 1)
      (setq start (point))
      (condition-case ()
          (forward-sexp 1)
        (error (cond ((eq major-mode 'ilisp)
                      (end-of-buffer))        ; In ilisp mode, makes sense.
                     (t
                      (forward-char 1)        ; In lisp mode, scan to next top-level definition.
                      (if (re-search-forward "^(" nil t)
                          (backward-char 1)
                          (error "Cannot find end of S-expression"))))
               (setq error-p t)))
      (setq end (point)))

    (let* ((string (buffer-substring start end))
           (cmd (format ilisp-matchup-arguments-command
                        (lisp-slashify
                          (if error-p (concat string ")") string))))
           (result (ilisp-send cmd nil 'matchup)))
      (lisp-display-output result))))




;;;; Better macroexpand.

(defun better-macroexpand-lisp (form &optional command insert-p)
  "Macroexpand the form using the given lucid command. Insert into buffer if insert-p."
  (if (string-match "(\\([^ \t\n)]*\\)" form)
      (let ((message (concat "Macroexpand "
                             (substring form
                                        (match-beginning 1)
                                        (match-end 1))))
            (cmd (format
                   (or command (ilisp-value 'ilisp-macroexpand-command))
                   (lisp-slashify form)
                   (lisp-buffer-package)
                   (buffer-file-name)))
            result)
        (setq result (ilisp-send cmd message 'expand))
        (if insert-p
            (save-excursion (forward-sexp) (insert ?\n) (insert result))
            (lisp-display-output result)))
      (error "Not a form: %s" form)))


(defun lisp-macroexpand-form-never-prompt ()
  "Return the next form for macroexpanding. Never prompt."
  (save-excursion
    (skip-chars-forward " \t\n")
    (let* ((begin (point))
           (end (progn (forward-sexp) (point)))
           (form (buffer-substring begin end)))
      (list form))))



(defun macroexpand-n-lisp (form)
  "Macroexpand the next sexp N times, where N is given by the absolute value of the prefix arg.
A negative prefix arg means to insert the result into the current buffer."
  (interactive (lisp-macroexpand-form-never-prompt))
  (let* ((insert-p (lisp-minus-prefix))
         (cmd (format "(ilisp::ilisp-macroexpand-n \"%%s\" \"%%s\" %d)"
                      (prefix-numeric-value current-prefix-arg))))
    (better-macroexpand-lisp form cmd insert-p)))



;;;; Lucid


;;; Site-specific locations for common lisp images.

(defvar current-lucid-program nil)        ; Overriding lucid program.
(defvar current-chestnut-program nil)
(defvar current-cmulisp-program default-cmulisp-program)

(defun lucid-program ()
  (if current-lucid-program
      current-lucid-program
      (cond
        ((string-match "-sunos4.1.4" system-configuration)
         lucid-sun4-executable)
        (t
          (let ((arch (getenv "SPARC_TYPE")))
            (if (equal arch "sparc")
                lucid-solaris-executable
                lucid-ultra-executable))))))

(defun chestnut-program ()
  (if current-chestnut-program
      current-chestnut-program
      (cond
        ((string-match "sparc-sun-solaris" system-configuration)
         (let ((arch (getenv "SPARC_TYPE")))
            (if (equal arch "ultra")
                chestnut-ultra-executable
                (error
                  (format "(%s): Chestnut only runs on Sparc Ultras"
                          "gensym-ilisp")))))
        (t
         (error
           (format "(%s): Cannot run Chestnut on this OS (%s)"
                   "gensym-ilisp" system-configuration))))))


;; Redefine the lucid initialization file. (see also gensym-lucid-hook).
(setq ilisp-lucid-init-file default-ilisp-init-file)

(add-hook 'lucid-hook 'gensym-lucid-hook)

(defun gensym-lucid-hook ()
  (setq lucid-program (lucid-program))

  ;; In Liquid CL 5.0, we need to get sbins appropriate for it.
  (if (string-match "liquid" lucid-program)
      (set-ilisp-value 'ilisp-load-inits
                       (list (cons 'clisp clisp-50-init-file)
                             (cons 'lucid gensym-lucid-50-init-file)))
      ;; On Solaris we we need to have the version
      ;; of these that were compiled for it.(and lucid-program

      (if (string-match "-solaris" system-configuration)
          (set-ilisp-value 'ilisp-load-inits
                           (list (cons 'clisp clisp-42-init-file)
                                 (cons 'lucid gensym-lucid-42-init-file)))))

  ;; The chestnut translator has "sbin" first in the list, while our G2 image
  ;; has it last.  Since we exclusively want "sbin" here (we run only on sparcs),
  ;; hardwire it.
  (setq ilisp-binary-extension "sbin"
        ilisp-binary-command nil)

  ;; Make the *lucid* buffer's default directory be the sandbox.
  (cond ((getenv "LISP_DIR")
         (cd (getenv "LISP_DIR")))
        ((getenv "BT_ROOT")
         (cd (format "%s/lisp" (getenv "BT_ROOT"))))
        ((string-equal (getenv "USER") "mes"))
        (t
         (cd (user-lisp-sandbox)))))



(defdialect chestnut "Chestnut Translator"
  lucid
  (setq chestnut-program (chestnut-program)
        ilisp-binary-extension "sbin"
        ilisp-binary-command nil))


(defdialect tw "TeleWindows"
  lucid)




;;;; Allegro


;;; `allegro-program' is "cl" by default, and that just won't work.  If and
;;; when we buy Allegro CL, we should definitely put it in a better place,
;;; like /home/acl or (my preference) /usr/local/....  However, since right
;;; now all we have is an evaluation copy, I don't want to "install" it
;;; yet.  On the other hand, others may be using it, so I do want to put it
;;; in our "site" files.

(setq allegro-program gensym-acl-location)





;;;; Patches


(defun maybe-edit-current-function (n)
  (interactive "p")
  (cond ((ilisp-mouse-at-prompt-p)
         (let ((fun (ilisp-send "(ilisp::ilisp-current-debugger-function)")))
           (cond (fun
                  (message "Edit Definition %s" fun)
                  (find-tag fun))
                 (t
                  (call-interactively 'find-tag)))))
           (t
            (end-of-line n))))


(defun redefine-some-ilisp-prefix-keys (keymap)
  (ilisp-defkey keymap "d" 'describe-function-lisp)
  (ilisp-defkey keymap "m" 'macroexpand-n-lisp)
  (ilisp-defkey keymap "v" 'describe-variable-lisp)
  (ilisp-defkey keymap "A" 'matchup-arguments-lisp)
  (ilisp-defkey keymap "D" 'clman))



(defun define-ilisp-keys ()
  (interactive)
  (ilisp-bindings)
  (ilisp-lispm-bindings)
  (setq ilisp-output-mode-line nil)        ; Unfortunate cache.

  ;; Nobody wants the close-all bs.
  (define-key lisp-mode-map "]" 'self-insert-command)
  (define-key ilisp-mode-map "]" 'self-insert-command)

  ;; Try to make this binding global
  (define-key ilisp-mode-map "\C-\M-l" 'previous-buffer-lisp)

  ;; Better bindings
  (define-key ilisp-mode-map "\C-\M-f" 'forward-sexp-or-up-list)
  (define-key ilisp-mode-map "\C-\M-b" 'backward-sexp-or-up-list)

  ;; Disable ilisp's attempt at a clever find-file.
  (define-key lisp-mode-map "\C-x\C-f" 'find-file)
  (define-key ilisp-mode-map "\C-x\C-f" 'find-file)

  ;; Don't bother with ilisp's find-tag.
  (defkey-ilisp "\M-." 'find-tag)
  (defkey-ilisp "\M-," 'tags-loop-continue)
  (defkey-ilisp "\M-:" 'find-tag-via-inferior-lisp)

  ;; indent-sexp doesn't see the common lisp indenter!
  (defkey-ilisp "\C-\M-q" 'ab-indent-sexp)
  (define-key lisp-mode-map "\M-q" 'ab-fill-paragraph)

  ;; Workaround for some synch bugs in ilisp.
  (define-key ilisp-mode-map "\C-\M-x" 'repair-ilisp)

  ;; Redefine the prefix versions, too, for vt100's.
  (redefine-some-ilisp-prefix-keys lisp-mode-map)
  (redefine-some-ilisp-prefix-keys ilisp-mode-map)

  ;; Need a version of these bindings for GNU emacs 19.
  (cond (xemacs-p
         (defkey-ilisp '(meta A) 'matchup-arguments-lisp)
         (defkey-ilisp '(meta C) 'clman)
         (defkey-ilisp '(control D) 'describe-function-lisp)
         (defkey-ilisp '(meta D) 'describe-function-lisp-always-prompt)
         (defkey-ilisp '(control M) 'macroexpand-n-lisp)

         (defkey-ilisp '(control V) 'describe-variable-lisp)

         (define-key lisp-mode-map '(control T) 'trace-defun-lisp)
         (define-key lisp-mode-map '(control tab) 'indent-line-ilisp) ; I keep hitting c-TAB by mistake.

         ;; The fast completer (uses etags)
         (define-key ilisp-mode-map '(meta tab) 'ab-complete-symbol)
         (define-key lisp-mode-map '(meta tab) 'ab-complete-symbol)

         ;; The slow completer.
         (define-key ilisp-mode-map '(control tab) 'complete-lisp)

         ;; The pause key pauses G2, so use the same key to resume it.
         (define-key ilisp-mode-map 'pause 'continue-lucid)

         ;; Has to been done after ilisp, in order to rebind m-Q
         (define-key lisp-mode-map '(control meta \\) 'ab-indent-region)

         (defkey-ilisp '(meta button2) 'ilisp-mouse-edit-caller)
         (defkey-ilisp '(meta button3) 'ilisp-mouse-post-symbol-menu))


        (fsf-emacs-p
         (defkey-ilisp (read "[?\\S-\\M-a]") 'matchup-arguments-lisp)
         (defkey-ilisp (read "[?\\S-\\M-c]") 'clman)
         (defkey-ilisp (read "[?\\S-\\C-d]") 'describe-function-lisp)
         (defkey-ilisp (read "[?\\S-\\M-d]") 'describe-function-lisp-always-prompt)
         (defkey-ilisp (read "[?\\S-\\C-v]") 'describe-variable-lisp)
         (defkey-ilisp (read "[?\\S-\\C-t]") 'trace-defun-lisp)
         (defkey-ilisp (read "[?\\S-\\C-m]") 'macroexpand-n-lisp))))


(defun load-ab-indent-table ()
  "Load Indentation for most of G2's macros."
  (interactive)
  (load "ab-indent-table"))


(defvar ab-lisp-mode-initialized nil)

(defun ab-initialize-lisp-mode ()
  ;; For G2, make sections act like pages.
  (make-variable-buffer-local 'page-delimiter)
  (setq page-delimiter "^;;;; ")

  ;; Seems to have changed its default value in 19.12
  ;;rh 11/13/96: commented the setq to comint-always-scroll -
  ;;    The file gensym-19-12-patches.el sets comint-always-scroll to t,
  ;;    but some people want this variable to be nil.
  ;;    Don't reset it here.
  ;;(if xemacs-p
  ;;    (setq comint-always-scroll t))

  ;; Turn on presentations in ilisp buffers.
  (if (and (eq major-mode 'ilisp-mode)
           (fboundp 'enable-presentations))
      (add-hook 'ilisp-init-hook 'enable-presentations))

  (cond (ab-lisp-mode-initialized)
        (t
         (setq ab-lisp-mode-initialized t)

         ;; Fixup Indentation.
         (setq lisp-indent-function 'common-lisp-indent-function)

         ;; Fancy loop indenter
         (require 'loop-indent "loop-indent")

         ;; Indentation for most of G2's macros.
         (load-ab-indent-table)

         (define-ilisp-keys))))



;;;; Global key bindings



(defun careful-lucid ()
  (interactive)
  (careful-lisp-non-interactive 'lucid "*lucid*"))

(defun careful-allegro ()
  (interactive)
  (careful-lisp-non-interactive 'allegro "*allegro*"))

(defun careful-lisp-non-interactive (lisp-name-symbol buffer-name-string)
  (let ((was (get-buffer buffer-name-string)))
    (if (not (eq (current-buffer) was))
        (progn
          (call-interactively lisp-name-symbol)

          (if (not (= (point) (point-max)))
              (end-of-buffer))))))

(defun careful-appropriate-lisp ()
  (interactive)
  (if linux-p
      (careful-allegro)
      (careful-lucid)))




;; Called via gnudoit when G2 breaks.

(defun leap-to-lucid ()
  (interactive)
  (call-interactively 'lucid)
  (delete-other-windows)
  (goto-char (point-max))
  (recenter)
  (sit-for 0)
  (raise-frame (selected-frame)))


(defun continue-lucid ()
  (interactive)
  (if (eq major-mode 'ilisp-mode)
      (progn
        (goto-char (point-max))
        (if (ilisp-mouse-at-prompt-p)
            (progn
              (insert ":c")
              (return-ilisp))
            (beep)))))



;; A key which switches to the lisp listener.
(define-key global-map "\C-c\C-l" 'careful-lucid)
(define-key lisp-mode-map "\C-c\C-l" 'careful-lucid)
(define-key ilisp-mode-map "\C-c\C-l" 'careful-lucid)

;; MHD, 5/14/96: Since c-c c-l is now unreliable -- it
;; is sometimes (!) bound to a function that shows you
;; your command history -- have Lucid be on another Key
;; Binding.  I've found the c-c c-i is works well, so
;; I'm adding it here today.  Leave in the old way
;; for compatibility. -mhd
;; -- update: changed to use careful-appropriate-lisp, so it
;; gets Allegro under Linux. -mhd, 6/14/00

(define-key global-map "\C-c\C-i" 'careful-appropriate-lisp)
(define-key lisp-mode-map "\C-c\C-i" 'careful-appropriate-lisp)
(define-key ilisp-mode-map "\C-c\C-i" 'careful-appropriate-lisp)



;; A key which switches to the telewindows listener.
(define-key global-map "\C-c\C-t" 'tw)
(define-key lisp-mode-map "\C-c\C-t" 'tw)
(define-key ilisp-mode-map "\C-c\C-t" 'tw)



;; A key that switches to the shell.
(define-key lisp-mode-map "\C-c\C-k" 'shell)


(setq lucid-program   (lucid-program)
      cmulisp-program current-cmulisp-program)


(add-hook 'lisp-mode-hook 'ab-initialize-lisp-mode)
(add-hook 'ilisp-mode-hook 'ab-initialize-lisp-mode)



;;;; Find unbalanced parens on Write File


(defun find-unbalanced-parens ()
  "Go to the point in region where LEFT-DELIMITER and RIGHT-DELIMITER
become unbalanced.  Signals an error, with point on the offending delimiter."
  (interactive)
  (lisp-count-pairs (point-min) (point-max)
                    (string-to-char (if (boundp 'left-delimiter) left-delimiter "("))
                    (string-to-char (if (boundp 'right-delimiter) right-delimiter ")"))))



;; The same as ilisp's find-unbalanced-lisp, except for defaulting the delimiter
;; characters.  Makes it safer to use as a write-file-hook.

(defun find-unbalanced-parens-hook ()
  "Go to the point in region where LEFT-DELIMITER and RIGHT-DELIMITER
become unbalanced.  Signals an error, with point on the offending delimiter."
  (interactive)
  (if (memq major-mode '(lisp-mode emacs-lisp-mode))
      (condition-case e
          (progn
            (find-unbalanced-parens)
            nil)
        (error
          (beep)
          (if (y-or-n-p (format "Error: buffer %s has an %s.  Write anyways? "
                                (buffer-name)
                                (downcase (car (cdr e)))))
              nil
              t)))))

(add-hook 'write-file-hooks 'find-unbalanced-parens-hook)

(load "presentations")

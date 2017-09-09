(add-to-list 'load-path ".")

;; copied these from ab-emacs-init because when we batch compile using this file,
;; we don't get those constants defined in advance
(defconst fsf-emacs-p (string-match "GNU Emacs" (emacs-version)))
(defconst xemacs-p (string-match "XEmacs" emacs-version))

(cond
 (fsf-emacs-p
  (byte-compile-file "ab-boot.el")
  (byte-compile-file "ab-emacs-init.el")
  (byte-compile-file "gensym-emacs.el")
  (byte-compile-file "unix-files.el")
  (byte-compile-file "windows-files.el")
  (byte-compile-file "fsf-compat.el")
  (byte-compile-file "elisp.el")
  (byte-compile-file "jump-def.el")
  (byte-compile-file "gensym-c-mode.el")
  (byte-compile-file "gensym-news-mail.el")
  (byte-compile-file "gensym-fonts-fsf.el")
  (byte-compile-file "ps-print.el")
  (byte-compile-file "find-c-source.el")
  (byte-compile-file "gensym-lep.el")
  (byte-compile-file "gensym-gdb.el"))
 (xemacs-p
  (load "ilisp")
  (byte-compile-file "ab-boot.el")
  (byte-compile-file "ab-emacs-init.el")
  (byte-compile-file "gensym-emacs.el")
  (byte-compile-file "unix-files.el")
  (byte-compile-file "elisp.el")
  (byte-compile-file "gensym-tags.el")
  (byte-compile-file "gensym-tags-patches19.el")
  (byte-compile-file "jump-def.el")
  (byte-compile-file "gensym-c-mode.el")
  (byte-compile-file "gensym-c-mode-xemacs.el")
  (byte-compile-file "gensym-news-mail.el")
  (byte-compile-file "gensym-fonts.el")
  (byte-compile-file "gensym-lazy-lock.el")
  (byte-compile-file "lazy-fontify.el")
  (byte-compile-file "ps-print.el")
  (byte-compile-file "gensym-indent.el")
  (byte-compile-file "find-c-source.el")
  (byte-compile-file "gensym-lep.el")
  (byte-compile-file "gensym-ilisp.el")
  (byte-compile-file "presentations.el")
  (byte-compile-file "gensym-gdb.el")
  (byte-compile-file "gensym-files.el")
  (byte-compile-file "gensym-menu.el")
  (byte-compile-file "gensym-shell.el")
  (byte-compile-file "gensym-19-12-patches.el")
  (byte-compile-file "gensym-21-0-patches.el")
  (byte-compile-file "ab-indent-table.el") ;; lucid
  (byte-compile-file "loop-indent.el")
  (byte-compile-file "cl-symbols.el") ;; clman
  (byte-compile-file "gensym-weather.el")
  ;; (byte-compile-file "gensym-g2.el")
  ))

;; windows-files.el, fsf-compat.el, and gensym-fonts-fsf.el are FSF only
;; This file, gensym-make, doesn't get compiled

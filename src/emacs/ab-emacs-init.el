;; -*- Mode: Emacs-Lisp -*-

;; This file serves make sure that the emacs we're running is one we're
;; ready to support, and distinguishes between FSF GNU Emacs, and Xemacs.
;; From there, we go on to gensym-emacs.el, the main elisp file that
;; drives our configuration.

(defconst fsf-emacs-p (string-match "GNU Emacs" (emacs-version)))
(defconst xemacs-p (string-match "XEmacs" emacs-version))

;; This should be set up by ab-boot, aka "~/.emacs".  Sanity check.
(if (not (boundp 'scriptsbox)) (defconst scriptsbox "/home/development/"))
(if (not (boundp 'ab-emacs-directory)) (defconst ab-emacs-directory (concat scriptsbox "emacs/")))
(if (not (member ab-emacs-directory load-path))
    (add-to-list 'load-path ab-emacs-directory))


;; Mr. AB's stuff.
(cond
  ((or
     (and fsf-emacs-p
          (>= emacs-major-version 19))
     (and xemacs-p
          (or (and (= emacs-major-version 19)
                   (>= emacs-minor-version 13))
              (> emacs-major-version 19))))
   (load "gensym-emacs"))
  (t
   (message "Unsupported emacs.  See ab-emacs-init.el (jv).")
   (sit-for 10)))

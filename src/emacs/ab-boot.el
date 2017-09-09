;; -*- Mode: Emacs-Lisp -*-

(defconst scriptsbox "/home/development/")
(defconst ab-emacs-directory (concat scriptsbox "emacs/"))

(add-to-list 'load-path ab-emacs-directory)

(load "ab-emacs-init")

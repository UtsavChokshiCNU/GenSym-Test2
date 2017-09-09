;;; -*- encoding:utf-8 -*-  --- 
;; 
;; Filename: gensym-mode.el
;; Description: Major mode for editing gensym/g2 kb files
;; Author: Jingtao Xu <jingtaozf@gmail.com>
;; Created: 2012.04.27 16:24:24(+0800)
;; Last-Updated: 2013.01.17 17:01:02(+0800)
;;     Update #: 57
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 
;;; Commentary: 
;; To use this file:
;;    1. add path of this file to load-path
;;    2. add following line to .emacs
;;       (autoload 'gensym-mode "gensym-mode.el" "gensym mode." t)
;;       (setq auto-mode-alist (append '(("\\.kb" . gensym-mode)) auto-mode-alist))
;; 

(eval-when-compile (require 'cl))
(provide 'gensym-mode)

(defvar gensym-wordchars "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'-._@")

(defvar gensym-comment-start "{")
(defvar gensym-comment-end "}")
(defvar gensym-comment-line-start "/'"); Plus another slash, of course"
(defvar gensym-string-start "\"")
(defvar gensym-string-end "\"")
(defvar gensym-bracket-start "[")
(defvar gensym-bracket-end "]")
(defvar gensym-escape-char "@")
(defvar gensym-arglist-start "(")
(defvar gensym-class-qualifier-char ":"); Plus another one, of course

;; define several class of keywords
(defvar gensym-keywords
  '("begin" "end" "if" "then" "else" "for" "do"
  "start" "call" "when" "whenever" "and" "or"
  "case" "exit" "signal" "return" "repeat"
  ;/* "go to" "on error" */
  "true" "false")
  "gensym keywords.")

(defvar gensym-types
  '("truth-value" "symbol" "text" "quantity" "value"
    "item-or-value" "sequence" "structure"
    "time-stamp" "long" "integer" "float" "class")
  "gensym types.")


;; create the regex string for each class of keywords
;; see variable lisp-font-lock-keywords-1
(defvar gensym-keywords-regexp (regexp-opt gensym-keywords 'symbols))
(defvar gensym-type-regexp (regexp-opt gensym-types 'symbols))

(defvar gensym-font-lock-keywords
  `(
    (,gensym-type-regexp . font-lock-type-face)
    (,gensym-keywords-regexp . font-lock-keyword-face)
    ))
(defvar gensym-syntax-table nil "Syntax table for `gensym-mode'.")
(setq gensym-syntax-table
      (let ((synTable (make-syntax-table)))

        ;; gensym style comment: "{ }"
        (modify-syntax-entry ?\{ "<" synTable)
        (modify-syntax-entry ?\} ">" synTable)
        ;; c++ style comment: //
        (modify-syntax-entry ?/ ". 124b" synTable)
        (modify-syntax-entry ?* ". 23" synTable)
        (modify-syntax-entry ?\n "> b" synTable)

        ;; @ is a escape in gensym string.
        (modify-syntax-entry ?\@ "\\" synTable)

        ;;declare the underscore character `_',`-' as being a valid part of a word
        (modify-syntax-entry ?_ "w" synTable)
        (modify-syntax-entry ?- "_" synTable)
        synTable))
(define-derived-mode gensym-mode fundamental-mode
  "gensym mode"
  :syntax-table gensym-syntax-table
  "Major mode for editing GENSYM G2 KnowledgeBase language"

  ;; code for syntax highlighting
  (setq font-lock-defaults '((gensym-font-lock-keywords)))
  (set (make-local-variable 'comment-start) gensym-comment-start)
  (set (make-local-variable 'comment-end) gensym-comment-end)
  (set (make-local-variable 'comment-use-global-state) t)
  (set (make-local-variable 'comment-multi-line) t))

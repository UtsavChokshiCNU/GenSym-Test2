
;; Patches to XEmacs 21


;;; `find-tag-default' -- the "built-in" definition, in etags.el, uses a macro
;;; called with-trapping-errors, which does not appear anywhere else in the .el
;;; files that comes with xemacs.  Obviously, this was missed.  We could change
;;; the etags.el file and recompile it, and maybe we should, but then if we
;;; install xemacs on a new machine, it would be broken until we did it again.
;;; I'll try to contact the maintainers of xemacs, such as they are, but for
;;; now, redefine the function here.  Note that the problem was only encountered
;;; in a mode where there was a find-tag-default-hook, which we have for our
;;; Lisp mode.  Tags are not *totally* broken in xemacs 21.

(defun find-tag-default ()
  (or (and (not (memq find-tag-default-hook '(nil find-tag-default)))
           (funcall find-tag-default-hook))
      (symbol-near-point)))



;;;; No, we like .emacs

;; Tell Xemacs 21 that, no, we do not want to migrate our .emacs file to
;; anything or other, thank you very much.  If you don't like Mr. AB's
;; decision here, you can always tell Xemacs by hand to do the migration:
;; M-x migrate-user-init-file

(custom-set-variables '(load-home-init-file t t))

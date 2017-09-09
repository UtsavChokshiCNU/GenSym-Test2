;;;; Mr. AB's patches to LEP.

(cond (xemacs-21-0-p
       (load lep-init-master-liquid50))
      (t
       (load lep-init-master-lucid41)))

(setq l-common-lisp-image-name 
      (if (string-match "-solaris" system-configuration)
	  lucid-ultra-executable
	  lucid-sun4-executable))

(defun get-default-lucid-directory ()
  (cond ((getenv "LISP_DIR")
	 (getenv "LISP_DIR"))
	((getenv "SRCBOX")
	 (format "%s/lisp" (getenv "SRCBOX")))
	((getenv "BT_ROOT")
	 (format "%s/lisp" (getenv "BT_ROOT")))
	(t
	 (user-lisp-sandbox))))

(defun lucid (&optional buffer program)
  "Create an inferior Lucid.  With prefix, prompt for buffer and program."
  (interactive (list nil nil))
  (l-common-lisp
    (or buffer "*Lucid*" )
    (get-default-lucid-directory)
    l-common-lisp-image-name
    nil
    "localhost"))

(defun chestnut (&optional buffer program)
  "Create an inferior Chestnut.  With prefix, prompt for buffer and program."
  (interactive (list nil nil))
  (l-common-lisp
    "*Chestnut*" 
    (get-default-lucid-directory)
    chestnut-ultra-executable
    nil
    "localhost"))

;; This very popular key in ilisp, has an irritating binding
;; in ilisp's absence.  So we clear that away.
(global-unset-key "\C-z")

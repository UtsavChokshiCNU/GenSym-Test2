;;;; Gnu Emacs 19 compatibility functions



(defvar zmacs-regions nil)
(defvar zmacs-region-stays nil)
(defvar find-file-use-truenames nil)
(defvar mouse-track-type nil)
(defvar mode-motion-hook nil)
(defvar lisp-indent-maximum-backtracking 3)


(defun switch-to-other-buffer (arg)
  "Switch to the previous buffer.  With a numeric arg, n, switch to the nth
most recent buffer.  With an arg of 0, buries the current buffer at the
bottom of the buffer stack."
  (interactive "p")
  (if (eq arg 0)
      (bury-buffer (current-buffer)))
  (switch-to-buffer
   (if (<= arg 1) (other-buffer (current-buffer))
     (nth (1+ arg) (buffer-list)))))

(defun zmacs-deactivate-region ()
  )

(defun ksh-mode ()
  "Ksh mode is identical to Sh mode."
  (interactive)
  (sh-mode))

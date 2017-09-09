;;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: USER -*-
(in-package "USER")

;;; After calling compile-and-load-mfg, one would typically invoke
;;; mfg-generate-makefiles-for-build with a list of products for which
;;; makefiles are to be generated.
;;;    e.g., (mfg-generate-makefiles-for-build '(ext fnt rtl))

;;; The following memory management settings are taken from lisp/load.lisp
;;; with the "expand" settings reduced to 100
(defvar lucid-memory-expanded?
  #-lucid t
  #+lucid nil)

#+lucid
(unless lucid-memory-expanded?
  (setq lucid-memory-expanded? t)
  (lcl:change-memory-management
    ;; Kill Lisp if larger than 96 Meg.
    :growth-limit 2000
    ;; Grow 3 Meg at a time (2 hemispheres * 25 seqments * 64Kbytes).
    :growth-rate 25
    ;; Add 16 Meg per hemisphere to Lucid's default allocation.
    :expand 100
    ;; Only expand if there is less than 20% free after a GC, default is 33%
    :reclamation-ratio 0.2
    ;; Grow the reserved area by 25 segments at a time, i.e. 1.2 Meg.
    :reserved-growth-rate 25
    ;; Add 28 Meg reserve to the 7 Meg already reserved.
    :expand-reserved 100)
  ;; Set the ephemeral level sizes to 1 Meg, 1.2 Meg, and 1.2 Meg to
  ;; attempt to get lots of garbage reclaimed here.  This is double the
  ;; default sizes.  -jra 1/6/92
  (lcl:egc-options :level-sizes '(16 20 20)))


(defvar directory-for-mfgen-lisp-binary-files "sbin")

(defvar suffix-for-mfgen-lisp-binary-files "sbin")

(defun compile-and-load-file (basename)
  (let ((object-file (format nil "~A/~A.~A"
			     directory-for-mfgen-lisp-binary-files
			     basename
			     suffix-for-mfgen-lisp-binary-files)))
    (ensure-directories-exist object-file :verbose t)
    (compile-file (format nil "~A.lisp" basename)
		  :output-file object-file)
    (load object-file)))

(defun compile-and-load-mfg ()
  (dolist (mfgen-file '("rdb" "mfg" "mfgmain" "mfgtf"))
    (compile-and-load-file mfgen-file)))


(proclaim '(optimize (speed 3) (safety 0) (compilation-speed 0)))

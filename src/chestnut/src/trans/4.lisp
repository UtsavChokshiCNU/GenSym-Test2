;;; Build translator binary for SymScale

(in-package :cl-user)

(pushnew :translator-supports-thread *features*)

;;; Load portable-threads
(load "../../../lisp/portable-threads")

#+sbcl
(progn
  (load "sbcl-load-trans")
  (sb-ext:save-lisp-and-die (concatenate 'string "trans-mt-sbcl" #+win32 ".exe")
                            :executable t :toplevel #'enter-top-level
                            :save-runtime-options t
                            :compression 5))

#+clozure
(progn
  (load "ccl-load-trans")
  (ccl:save-application (concatenate 'string "trans-mt-ccl" #+windows-target ".exe")
                        :prepend-kernel t :toplevel-function #'enter-top-level))

#+lispworks
(progn
  (load-all-patches)
  (load "lw-load-trans")
  (save-image "trans-mt-lw"
	      :restart-function 'enter-top-level
	      :multiprocessing t
	      :environment nil
	      :console t))

(quit)

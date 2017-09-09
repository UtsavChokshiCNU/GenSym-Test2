(in-package :cl-user)

#+sbcl
(progn
  (load "sbcl-load-trans")
  (sb-ext:save-lisp-and-die (concatenate 'string "trans-sbcl" #+win32 ".exe")
                            :executable t :toplevel #'enter-top-level
                            :save-runtime-options t
                            #+:SB-CORE-COMPRESSION
                            #+:SB-CORE-COMPRESSION
                            :compression 5))

#+clozure
(progn
  (load "ccl-load-trans")
  (ccl:save-application (concatenate 'string "trans-ccl" #+windows-target ".exe")
                        :prepend-kernel t :toplevel-function #'enter-top-level))

#+lispworks
(progn
  (load-all-patches)
  (load "lw-load-trans")
  (save-image "trans-lw"
	      :restart-function 'enter-top-level
	      :multiprocessing t
	      :environment nil
	      :console t))

(quit)

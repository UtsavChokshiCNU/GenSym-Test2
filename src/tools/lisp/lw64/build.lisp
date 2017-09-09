(in-package "CL-USER")

(load-all-patches)

(let* ((name (format nil "LispWorks ~A~@[~A~]"
                     (lisp-implementation-version)
                     (when (sys:featurep :lispworks-64bit) " 64-bit")))
       (exe-name (if (sys:featurep :lispworks-64bit) "lw64" "lw")))
  (save-image (make-pathname :name (format nil "~A-console" exe-name))
              :console t
	      :remarks name
	      :environment nil
	      :multiprocessing t))

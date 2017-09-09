(in-package :cl-user)

(defvar *cfg-file* (merge-pathnames "cfg.lisp" *load-pathname*))
(defvar *kb-to-load* nil)

(when (probe-file *cfg-file*)
  (load *cfg-file*))

(defvar *command-line*
  #+lispworks system:*line-arguments-list*
  #+sbcl sb-ext:*posix-argv*
  #+clozure ccl:*command-line-argument-list*)

(defparameter *module-search-path*
  '("../g2i/kbs/"
    "../g2i/sites/Optegrity/kbs/"
    "../g2i/sites/ReThink/kbs/"
    "../kbs/sources/"
    "../g2db/kbs/src/"
    "../java/products/javalink/kbs/"
    "../g2opc/kbs/"
    "../g2pi/kbs/"))

(nconc *command-line*
       (when *kb-to-load* (list "-kb" *kb-to-load*))
       (list "-module-search-path"
             (format nil "~{~A~^ ~}"
                     (map 'list
                          #'(lambda (x)
                              (make-pathname :name nil :type nil
                                             :defaults 
                                             (merge-pathnames 
                                              x *load-pathname*)))
                          *module-search-path*))))

(load (merge-pathnames "123.lisp" *load-pathname*))

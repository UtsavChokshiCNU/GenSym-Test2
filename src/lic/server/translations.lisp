;;;; G2 Logical Pathname System   -- Chun Tian (binghe), 2010/11/06

(in-package :cl-user)

(defun get-environment-variable-value (name)
  #+lispworks (environment-variable name)
  #+sbcl (sb-ext:posix-getenv name)
  #+clozure (ccl:getenv name))

(defun component-present-p (value)
  (and value (not (eql value :unspecific))))

#-clozure
(defun directory-pathname-p (pathspec)
  (and (not (component-present-p (pathname-name pathspec)))
       (not (component-present-p (pathname-type pathspec)))
       pathspec))

(defun pathname-as-directory (pathspec)
  (let ((pathname (pathname pathspec)))
    (when (wild-pathname-p pathname)
      (error "Can't reliably convert wild pathnames."))
    (cond ((not (directory-pathname-p pathspec))
           (make-pathname :directory (append (or (pathname-directory pathname)
                                                 (list :relative))
                                             (list (file-namestring pathname)))
                          :name nil
                          :type nil
                          :defaults pathname))
          (t pathname))))

(defun simplify-pathname (pathname)
  (truename (pathname (namestring pathname))))

(defun set-logical-pathname-translations 
    (host environment-variable default-path)
  (let* ((defaults
          (pathname-as-directory 
           (or (get-environment-variable-value environment-variable) 
               (simplify-pathname
                (make-pathname :name nil :type nil
                               :directory (append (or (pathname-directory *load-pathname*)
                                                      (list :relative))
                                                  default-path)
                               :defaults *load-pathname*)))))
         (home (make-pathname :name :wild :type :wild
                              :directory (append (pathname-directory defaults)
                                                 '(:wild-inferiors))
                              :host (pathname-host defaults)
                              :defaults defaults
                              :version :newest)))
    (setf (logical-pathname-translations host)
          `(("**;*.*.newest" ,home)
            ("**;*.*" ,home)))))

;; In the case SRCBOX or DSTBOX are not set we assume 123.lisp is being loaded 
;; from lisp folder of the working copy. Thus, defaults are ".." for SRCBOX and 
;; "../../dst" for DSTBOX (Serhiy Yakovyn 2010/10/27)
(eval-when (:load-toplevel :execute) 
  (set-logical-pathname-translations "SRC" "SRCBOX" '(:up :up))
  (set-logical-pathname-translations "DST" "DSTBOX" '(:up :up :up "dst")))

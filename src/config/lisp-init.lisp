;; Mr AB's init file for Lucid Common Lisp

(in-package "USER")

(format t ";;; This image features~{~<~%;;;~:; ~A~>~^,~}.~%" 
	(sort (copy-list *features*) #'string< :key #'symbol-name))

(defun G2 (&optional launch)
  "Compile, load and optionally launch G2."
  (let ((sandbox (format nil "/bt/~a/lisp/" (environment-variable "USER"))))
    (cd sandbox)
    (unless (find-package "AB")
      (load "load"))
    (compile-g2 :no-updates :no-make :no-process)
    (in-package "AB")
    (if launch
	(funcall (intern "LAUNCH-AB" "AB"))
	(format t "Do \"(launch-ab)\" to start a G2.~%"))
    (values)))

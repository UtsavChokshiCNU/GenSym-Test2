
(in-package "USER")

;;; Load the translator
(unless (member :translator-is-loaded *features*)
  (load "load-trans"))

(defparameter *files*
  '("macros" "engine" "rules1" "rules2" "driver"))

(defun translate-application ()
  (trans:translate-files *files*))


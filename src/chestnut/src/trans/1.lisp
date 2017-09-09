;;; Compile translator sources

(in-package :cl-user)

(pushnew :optimize-translator *features*)
#+ignore
(pushnew :translator-supports-clos *features*)

(load "build.lisp")

(quit)

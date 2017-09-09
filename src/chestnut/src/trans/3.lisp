;;; Compile translator sources for SymScale

(in-package :cl-user)

(pushnew :optimize-translator *features*)
(pushnew :translator-supports-thread *features*)

#+ignore
(pushnew :translator-supports-clos *features*)

;;; Compile and load portable-threads
(load (compile-file "../../../lisp/portable-threads.lisp"))

(load "build.lisp")

(quit)

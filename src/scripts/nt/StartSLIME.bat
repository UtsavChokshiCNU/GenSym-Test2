@echo off
setlocal

rem This batch file launches Emacs with a full -module-search-path provided.
rem You may supply all valid G2 commandline arguments.
rem To use it, put something like this into your .emacs:
rem (setq slime-lisp-implementations
rem      `((sbcl ("sbcl"))
rem	   (g2-sbcl
rem	    ,(append
rem	      '("sbcl" "--dynamic-space-size" "2048")
rem	      (when (getenv "G2_ARGS")
rem	       (mapcar
rem	        (lambda (s) (replace-regexp-in-string "\"" "'" s))
rem	        (split-string (getenv "G2_ARGS"))))))
rem	   (ccl64 ("d:/ccl-1.11-windows/ccl/wx86cl64.exe"))))


call %~dp0\StartLW-common.bat

cd C:/G2/src/lisp
rem TODO: fix emacs path
D:\emacs-25.1-2-x86_64-w64-mingw32\bin\runemacs

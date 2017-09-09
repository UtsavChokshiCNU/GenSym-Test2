@echo off

rem Usage: g2adoc.bat <path-to-xml-kb>
rem Will print AsciiDoc to stdout.
rem Requires QuickLisp.
rem Prior to use, copy g2adoc folder from src/tools/lisp to ~/quicklisp/local-projects

if "%~1"=="" (
    echo Usage: g2adoc.bat path-to-xml-kb
    goto :eof
)

if not "%~2"=="" (
    echo Usage: g2adoc.bat path-to-xml-kb
    goto :eof
)

set "fname=%1"
set "fname=%fname:\=/%"

sbcl --noinform --non-interactive --eval "(ql:quickload \"g2adoc\" :silent t)" --eval "(g2adoc:document-kb \"%fname%\")" --quit


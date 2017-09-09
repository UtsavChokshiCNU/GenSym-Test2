:: Run this file and find your executable in BIN folder

@echo off

del ..\..\lisp\*.log
del /s *.fasl

if "" == "%~2" (
  set EXEC=sbcl-x86
  set DIR=win32
  set "OPTION=--dynamic-space-size 940"
) else if "32" == "%~2" (
  set EXEC=sbcl-x86
  set DIR=win32
  set "OPTION=--dynamic-space-size 940"
) else if "64" == "%~2" (
  set EXEC=sbcl-x64
  set DIR=win64
  set "OPTION=--dynamic-space-size 2048"
)

if "" == "%~1" (
  rd /s /q OBIN
  ..\..\..\tools\lisp\sbcl\%EXEC% < 1.lisp
  ..\..\..\tools\lisp\sbcl\%EXEC% %OPTION% < 2.lisp
  copy /Y trans-sbcl.exe ..\..\%DIR%
) else if "mt" == "%~1" (
  rd /s /q OTBIN
  ..\..\..\tools\lisp\sbcl\%EXEC% < 3.lisp
  ..\..\..\tools\lisp\sbcl\%EXEC% %OPTION% < 4.lisp
  copy /Y trans-mt-sbcl.exe ..\..\%DIR%
)

pause

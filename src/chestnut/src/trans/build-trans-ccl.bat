:: Run this file and find your executable in BIN folder

@echo off

del ../../lisp/*.log
del /s *.wx32fsl
del /s *.wx64fsl

if "" == "%~2" (
  set EXEC=wx86cl64
  set DIR=win64
) else if "32" == "%~2" (
  set EXEC=wx86cl
  set DIR=win32
) else if "64" == "%~2" (
  set EXEC=wx86cl64
  set DIR=win64
)

if "" == "%~1" (
  rd /s /q OBIN
  mkdir OBIN
  ..\..\..\tools\lisp\ccl-1.7\%EXEC% -n -l 1.lisp
  ..\..\..\tools\lisp\ccl-1.7\%EXEC% %OPTION% -n -l 2.lisp
  copy /Y trans-ccl.exe ..\..\%DIR%
) else if "mt" == "%~1" (
  rd /s /q OTBIN
  mkdir OTBIN
  ..\..\..\tools\lisp\ccl-1.7\%EXEC% -n -l 3.lisp
  ..\..\..\tools\lisp\ccl-1.7\%EXEC% %OPTION% -n -l 4.lisp
  copy /Y trans-mt-ccl.exe ..\..\%DIR%
)

pause

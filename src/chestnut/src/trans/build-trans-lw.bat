@echo off

set LISPWORKS=..\..\..\tools\lisp\lw64\lw64-console.exe

del /q ..\..\lisp\*.log
if not exist "OBIN" md OBIN
del /q OBIN\*.64ofasl

if "" == "%~1" (
"%LISPWORKS%" -init - -load 1.lisp
"%LISPWORKS%" -build 2.lisp
xcopy trans-lw.exe ..\..\win32\ /R /Y
) else if "mt" == "%~1" (
"%LISPWORKS%" -init - -load 3.lisp
"%LISPWORKS%" -build 4.lisp
xcopy trans-mt-lw.exe ..\..\win32\ /R /Y
)

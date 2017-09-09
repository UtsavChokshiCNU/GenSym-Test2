@echo off

rem Update PATH variable for x64 and x86 systems

set VS2010=%VS100COMNTOOLS%\..\..\VC

rem x64 or x86
call "%VS2010%\vcvarsall.bat" %1

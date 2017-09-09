@echo off
rem A file to help with change setup.rul.
rem Double click on it or in EMACS use the compile command "comprul noPause"
rem It should be in the same directory as setup.rul so you a can edit more than
rem one setup.rul in EMACS and have the correct comprul.bat run.

if "%INSTALLSHIELD_HOME%" == "" goto noinstallshield

setlocal

set path=%INSTALLSHIELD_HOME%\PROGRAM;%INSTALLSHIELD_HOME%\UTILITY\EXEBLDR

set SRC_ROOT=%SRCBOX%\java\products\javalink\builds\intelnt
set RELEASE=%SRCBOX%\staging\javalink\intelnt
set CD_INSTALL=%RELEASE%

if not exist "%CD_INSTALL%" mkdir "%CD_INSTALL%"

cd /d "%SRC_ROOT%\setup"

compile setup.rul

echo on
copy setup.ins        "%CD_INSTALL%"

if "%1" == "" pause

endlocal
goto end

:noinstallshield
@echo "Please setup INSTALLSHEILD_HOME to the root direcrtory of INSTALL SHIELD 3"

:end

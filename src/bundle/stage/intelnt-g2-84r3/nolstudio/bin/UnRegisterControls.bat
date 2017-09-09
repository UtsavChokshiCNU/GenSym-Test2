@echo off
setlocal
set G2_INSTALL_DIR=%ROOTDIR%

if not exist "%G2_INSTALL_DIR%\activexlink\regsvr32.exe" goto defaultreg
set REGSVR32=%G2_INSTALL_DIR%\activexlink\regsvr32.exe
goto gotreg
:defaultreg
set REGSVR32=regsvr32
:gotreg

:axl
if not exist "%G2_INSTALL_DIR%\activexlink" goto twax
cd %G2_INSTALL_DIR%\activexlink\bin
"%REGSVR32%" /u /s G2Com.dll
echo Unregistered G2 ActiveXLink control.

:twax
cd %G2_INSTALL_DIR%\g2
if not exist registerTwControl.bat goto wsv
"%REGSVR32%" /u /s TwControl.ocx
echo Unregistered Telewindows ActiveX Control

:wsv
if not exist registerWSV.bat goto end
"%REGSVR32%" /u /s WorkspaceView.ocx
echo Unregistered Workspace View Control

:end
pause

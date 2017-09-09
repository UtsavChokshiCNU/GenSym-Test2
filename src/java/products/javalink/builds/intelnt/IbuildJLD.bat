if "%INSTALLSHIELD_HOME%" == "" goto noinstallshield

setlocal

set path=%INSTALLSHIELD_HOME%\PROGRAM;%INSTALLSHIELD_HOME%\UTILITY\EXEBLDR

set SRC_ROOT=%SRCBOX%\java\products\javalink\builds\intelnt
rem because build is not rational...
set DSTBOX=%SRCBOX%
set RELEASE=%SRCBOX%\staging\javalink\intelnt
set CD_INSTALL=%RELEASE%

@echo Build components...

if not exist "%CD_INSTALL%" mkdir "%CD_INSTALL%"

cd /d "%SRC_ROOT%\setup"

@echo Compile InstallShield Script...
compile setup.rul

@echo Copy the our setup files to the staging area...
copy setup.ins "%CD_INSTALL%"
copy setup.ini "%CD_INSTALL%"

copy ..\data\rawprop.gen "%CD_INSTALL%"
copy ..\data\*.bmp       "%CD_INSTALL%"

@echo Copy the InstallShield files to the staging area...
copy "%INSTALLSHIELD_HOME%\Program\_inst32i.ex_" "%CD_INSTALL%"
copy "%INSTALLSHIELD_HOME%\Program\_isdel.exe"   "%CD_INSTALL%"
copy "%INSTALLSHIELD_HOME%\Program\_setup.dll"   "%CD_INSTALL%"
copy "%INSTALLSHIELD_HOME%\Program\_setup.lib"   "%CD_INSTALL%"
copy "%INSTALLSHIELD_HOME%\Program\Isdbgn.dll"   "%CD_INSTALL%"
copy "%INSTALLSHIELD_HOME%\Program\setup.exe"    "%CD_INSTALL%"

endlocal
goto end

:noinstallshield
@echo "Please setup INSTALLSHEILD_HOME to the root direcrtory of INSTALL SHIELD 3"

:end

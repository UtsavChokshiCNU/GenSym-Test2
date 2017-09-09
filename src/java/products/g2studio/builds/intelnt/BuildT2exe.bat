setlocal

set path=C:\Program Files\InstallShield\PackageForTheWeb 2

set SRC_ROOT=%SRCBOX%\java\products\sequoia\builds\intelnt
rem because build is not rational...
set DSTBOX=%SRCBOX%
set RELEASE=%DSTBOX%\staging\sequoia
set CD_INSTALL=%RELEASE%\intelnt
set WEB_INSTALL=%RELEASE%

set PFW_FILE=Telewindows2.pfw

@echo Packaging components into a self extracting executable...

if not exist "%WEB_INSTALL%" mkdir "%WEB_INSTALL%"
del /Q "%WEB_INSTALL%\*.exe" 2>nul

@rem The package for the web project is relative so it can be run in any sandbox.
copy "%SRC_ROOT%\%PFW_FILE%" "%WEB_INSTALL%"

cd /d "%WEB_INSTALL%"

@rem -a is automatic, -s silent
pftwwiz .\%PFW_FILE% -a -s

endlocal
goto end

:end

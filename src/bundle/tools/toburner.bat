@echo off
rem Usage: toburner family_name version_tag
rem   E.g., toburner g2 52r0
rem
rem (By default, g2 and 52r0 are used for backward compatibility for now.)
rem
rem This script builds copies the finished Unix and Windows
rem images and setup directories, respectively, to the CD
rem burner directory.

setlocal

set FAMILY=%FAMILY_NAME%-%VERSION_TAG%

echo Setting up environment variables . . .
@echo on
SET DSTBOX=%SRCBOX%\dst\%MACHINE%
SET PATH=%PATH%;%SRCBOX%\UTIL

SET SCRIPTBATFILE=%SRCBOX%\bundle\tools\toburner.bat

set STAGE_DIR=%SRCBOX%\bundle\stage
set INSTALLPROJECT_DIR_NAME=isproj-%FAMILY%
set INSTALLPROJECT_DIR=%STAGE_DIR%\%INSTALLPROJECT_DIR_NAME%
set INSTALLPROJECT=%INSTALLPROJECT_DIR%\gensym.ipr
set MEDIA_DIR=%INSTALLPROJECT_DIR%\Media\Default\Disk Images\Disk1
set TOOLS_DIR=%SRCBOX%\bundle\tools
set C_DIR=%SRCBOX%\bundle\c
set FAMILY_FILE=%SRCBOX%\tools\datafiles\families\%FAMILY_NAME%-%VERSION_TAG%.fam
set FAMILY_DESCRIPTOR_FILE=%STAGE_DIR%\isproj\gensym.ipr

set BURNER_DIR=%BUNDLEBOX%\%FAMILY_NAME%\%VERSION_TAG%
@echo off

echo ****************
echo Script: %SCRIPTBATFILE%
echo Copying IS Setup for %FAMILY%
echo   to CD burner directories under %BURNER_DIR%
echo ****************
set p=intelnt
set d=%BURNER_DIR%\%p%
echo   Media Directory:
dir "%MEDIA_DIR%"
if exist "%d%" echo Burner Directory "%d%" exists, removing ....
if exist "%d%" rmdir /s /q "%d%"
echo Creating directory "%d%" ...
mkdir "%d%"
echo Copying Media Directory to Burner Directory with the following command:
echo   xcopy /E /K "%MEDIA_DIR%" "%d%"
xcopy /E /K "%MEDIA_DIR%\*" "%d%"
dir "%MEDIA_DIR%"

rem Now we go get autorun.inf so we automatically start
copy %SRCBOX%\bundle\tools\autorun.inf %d%\autorun.inf
echo completed successfully

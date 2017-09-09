@echo off
rem Usage: wintounix family_name version_tag
rem   E.g., wintounix g2 52r0
rem
rem (By default, g2 and 52r0 are used for backward compatibility for now.)
rem
rem This script takes the finished Windows setup directory, i.e., after
rem running toburner.bat, and creates a
rem .zip archive of it, copies it to the unix image directory as intelnt.zip.

setlocal

set FAMILY_NAME=g2
set VERSION_TAG=52r0
if not "%1" == "" set FAMILY_NAME=%1
if not "%2" == "" set VERSION_TAG=%2

set FAMILY=%FAMILY_NAME%-%VERSION_TAG%

if "%SRCBOX%" == "" goto error
if "%MACHINE%" == "" goto error
if "%BUNDLEBOX%" == "" goto error

echo Setting up environment variables . . .
@echo on
SET DSTBOX=%SRCBOX%\dst\%MACHINE%
SET PATH=%PATH%;%SRCBOX%\UTIL

SET SCRIPTBATFILE=%SRCBOX%\bundle\tools\wintounix.bat

set STAGE_DIR=%SRCBOX%\bundle\stage
set INSTALLPROJECT_DIR_NAME=isproj-%FAMILY%
set INSTALLPROJECT_DIR=%STAGE_DIR%\%INSTALLPROJECT_DIR_NAME%
set INSTALLPROJECT=%INSTALLPROJECT_DIR%\gensym.ipr
set MEDIA_DIR=%INSTALLPROJECT_DIR%\Media\Default\Disk Images\Disk1
set TOOLS_DIR=%SRCBOX%\bundle\tools
set C_DIR=%SRCBOX%\bundle\c
set FAMILY_FILE=%SRCBOX%\tools\datafiles\families\%FAMILY_NAME%-%VERSION_TAG%.fam
set FAMILY_DESCRIPTOR_FILE=%STAGE_DIR%\isproj\gensym.ipr

set UNIX_HOST=sdev4.gensym.com
set UNIX_DIR=/gensym/bundles
set ZIP_FILE_NAME=intelnt.zip
set TREE_DIR=%STAGE_DIR%\intelnt-%FAMILY_NAME%
set UNIX_IMAGE_DIR=%UNIX_DIR%/%FAMILY_NAME%/%VERSION_TAG%/image

set BURNER_DIR=%BUNDLEBOX%\%FAMILY_NAME%\%VERSION_TAG%
@echo off

echo ****************
echo Script: %SCRIPTBATFILE%
echo ****************
set p=intelnt
set d=%BURNER_DIR%\%p%
echo Making zip archive for directory "%BURNER_DIR%" ....
dir "%BURNER_DIR%\%p%"
set f=%UNIX_IMAGE_DIR%/%p%.zip
set zipfile=%STAGE_DIR%\%p%.zip
echo Copying IS Setup for %FAMILY% to %UNIX_HOST% as "%f%"...
if exist "%zipfile%" del "%zipfile%"
setlocal
cd %BURNER_DIR%\%p%
"%TOOLS_DIR%\zip" -r "%zipfile%" *
endlocal

echo Zip file "%zipfile%" done. Now uploading it to unix directory "%f%"...

rem ftp_file may not have spaces in its name. So just make it locally.
set ftp_file=tmp.ftp

if exist "%ftp_file%" del "%ftp_file%"

echo open %UNIX_HOST% >%ftp_file%
echo ab>>%ftp_file%
echo gensym>>%ftp_file%
echo bin >>%ftp_file%
echo put >>%ftp_file%
echo %zipfile% >>%ftp_file%
echo %f% >>%ftp_file%
echo quit >>"%ftp_file%"

ftp -s:%ftp_file%

echo (Preserving temporary file "%ftp_file%" for now!)
echo (Preserving large temporary file "%zipfile%" for now!)
rem Later, instead do this: (!)
rem   del "%ftp_file%"
rem   del "%zipfile%"

echo done.

goto end

:error 
echo SRCBOX, BUNDLEBOX, or MACHINE not set!  Must set all variables to run this script.

:end

endlocal

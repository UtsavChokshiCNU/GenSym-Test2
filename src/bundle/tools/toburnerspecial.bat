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

set FAMILY_NAME=g2
set VERSION_TAG=52r0
if not "%1" == "" set FAMILY_NAME=%1
if not "%2" == "" set VERSION_TAG=%2

set FAMILY=%FAMILY_NAME%-%VERSION_TAG%

echo Setting up environment variables . . .
@echo on
set BUNDLEBOX=c:\bundle
set SRCBOX=%BUNDLEBOX%\sandbox
SET MACHINE=intelnt
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

set UNIX_HOST=sdev4
set UNIX_DIR=/gensym/spare/bundles
set ZIP_FILE_NAME=intelnt.zip
set TREE_DIR=%STAGE_DIR%\intelnt-%FAMILY_NAME%
set UNIX_IMAGE_DIR=%UNIX_DIR%/%FAMILY_NAME%/%VERSION_TAG%/image

set BURNER_DIR=%BUNDLEBOX%\%FAMILY_NAME%\%VERSION_TAG%
@echo off

echo ****************
echo Script: %SCRIPTBATFILE%
echo Copying IS Setup for %FAMILY%
echo   to CD burner directories under %BURNER_DIR%
echo ****************
set p=linux
set d=%BURNER_DIR%\%p%
set f=%UNIX_IMAGE_DIR%/%p%.iso
if exist "%d%" rmdir /s /q "%d%"
mkdir "%d%"
echo    %TOOLS_DIR%\wget -nv -P "%d%" ftp://ab:gensym@%UNIX_HOST%//%f%
%TOOLS_DIR%\wget -nv -P "%d%" ftp://ab:gensym@%UNIX_HOST%//%f%
echo done.
echo ****************
set p=alphaosf
set d=%BURNER_DIR%\%p%
set f=%UNIX_IMAGE_DIR%/%p%.iso
if exist "%d%" rmdir /s /q "%d%"
mkdir "%d%"
echo    %TOOLS_DIR%\wget -nv -P "%d%" ftp://ab:gensym@%UNIX_HOST%//%f%
%TOOLS_DIR%\wget -nv -P "%d%" ftp://ab:gensym@%UNIX_HOST%//%f%
echo done.
echo done.

endlocal

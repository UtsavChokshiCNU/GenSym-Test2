@echo off

rem This script builds the license key generator.
rem For now, it is intended to run on the G2 group's
rem Windows 2000 system "2000test".

setlocal


set SRCBOX=c:\bundle\sandbox

set MSVC=c:\bundle\msvc
set INCLUDE=%MSVC%\vc98\include
set LIB=%MSVC%\vc98\lib
set PATH=%PATH%;%MSVC%\vc98\bin;%MSVC%\common\msdev98\bin

SET MACHINE=intelnt
SET DSTBOX=%SRCBOX%\dst\%MACHINE%
SET PATH=%PATH%;%SRCBOX%\UTIL

set STAGE_DIR=%SRCBOX%\bundle\stage
set INSTALLPROJECT_DIR=%STAGE_DIR%\isproj
set TOOLS_DIR=%SRCBOX%\bundle\tools
set C_DIR=%SRCBOX%\bundle\c
set JAVA_DIR=%SRCBOX%\bundle\java

set UNIX_HOST=sdev4
set UNIX_DIR=/gensym/bundles
set ZIP_FILE_NAME=license-server.zip

rem note: don't run this as administrator, it doesn't work.

echo cvs up in "%SRCBOX%" ...
cd %SRCBOX%
cvs up

rem echo Unzipping:
rem echo    %TOOLS_DIR%\unzip -q -o "%JAVA_DIR%\%ZIP_FILE_NAME%" -d "%STAGE_DIR%"
rem %TOOLS_DIR%\unzip -q -o "%JAVA_DIR%\%ZIP_FILE_NAME%" -d "%STAGE_DIR%"


cd %SRCBOX%\bundle\java\com\gensym\bundle

echo Java Compiling ....
javac *.java

echo Jar'ing ....
jar cfv "%STAGE_DIR%\keygui.jar" *.class

echo Removing "%STAGE_DIR%\LicenseServer" with:
echo   del /q/s/f "%STAGE_DIR%\LicenseServer" >nul
del /q/s/f "%STAGE_DIR%\LicenseServer" >nul

echo Making directory "%STAGE_DIR%\LicenseServer" ...
mkdir "%STAGE_DIR%\LicenseServer"
mkdir "%STAGE_DIR%\licenseserver\data"
mkdir "%STAGE_DIR%\licenseserver\logs"
copy "%JAVA_DIR%\keygenerator.dll" "%STAGE_DIR%\LicenseServer"
copy "%JAVA_DIR%\startlicenseserver.bat" "%STAGE_DIR%\LicenseServer"
move "%STAGE_DIR%\keygui.jar" "%STAGE_DIR%\LicenseServer"

echo "%STAGE_DIR%\LicenseServer" created with the following contents:
dir "%STAGE_DIR%\LicenseServer"

echo DONE. LicenseServer should be ready to test
echo Make this the working directory:
echo   %STAGE_DIR%\LicenseServer
echo Run this:
echo   startlicenseserver.bat





endlocal



@echo off
echo "Run installer creating - %time%"

pushd ..\..\scripts\nt
call set-boxes
popd

set G2_VER=2015
set STAGE_NAME=intelnt-g2-84r3
set STAGE_DIR=%SRCBOX%\bundle\stage\%STAGE_NAME%
if "%1" == "std" set MACHINE=intelnt
if "%1" == "ent" set MACHINE=win64
set "PATH=%PATH%;C:\Program Files\7-Zip"

if NOT "%1" == "" goto sign_binaries
echo "Mandatory std|ent parameter is missed"
exit 1

:sign_binaries

if "%2" == "" goto create_installer

call sign-code %STAGE_DIR%\g2\g2.exe %2
REM
REM SymScale is not part of the installer (yet)
REM if "%1" == "ent" call sign-code %STAGE_DIR%\g2\SymScale.exe %2
call sign-code %STAGE_DIR%\g2\tw.exe %2
call sign-code %STAGE_DIR%\g2\twng.exe %2
call sign-code %STAGE_DIR%\g2\TwControl.cab %2
call sign-code %STAGE_DIR%\activexlink\bin\G2Com.dll %2
if exist %STAGE_DIR%\activexlink\bin\x64\G2Com.dll call sign-code %STAGE_DIR%\activexlink\bin\x64\G2Com.dll %2
call sign-code %STAGE_DIR%\g2i\data\http_root\TelewindowsAX.cab %2

:create_installer
pushd ..\stage\%STAGE_NAME%
call 7z.exe a -tzip -xr!.svn "%SRCBOX%\bundle\stage\%MACHINE%.zip"
popd

:buildipr

if exist %SRCBOX%\bundle\stage\isproj-g2-%G2_VER% rd /S /Q %SRCBOX%\bundle\stage\isproj-g2-%G2_VER%
call buildipr_x64 %G2_VER% %1

if exist %SRCBOX%\bundle\stage\isproj-g2-%G2_VER%_bak1 rd /S /Q %SRCBOX%\bundle\stage\isproj-g2-%G2_VER%_bak1

rem goto end

pushd ..\stage\isproj-g2-%G2_VER%

if exist Gensym.ipr call "C:\Program Files (x86)\InstallShield\2013 SAB\System\IsCmdBld.exe" -v -p Gensym.ipr -u
call "C:\Program Files (x86)\InstallShield\2013 SAB\System\IsCmdBld.exe" -v -p Gensym.ism
popd

set BUNDLE_FILE=Gensym%G2_VER%.zip
if "%1" == "std" set BUNDLE_FILE=Gensym%G2_VER%-STD.zip
if "%1" == "ent" set BUNDLE_FILE=Gensym%G2_VER%-ENT.zip

pushd ..\stage
if exist %SRCBOX%\bundle\stage\%BUNDLE_FILE% del /F /Q %SRCBOX%\bundle\stage\%BUNDLE_FILE%
call 7z.exe a %BUNDLE_FILE% "%SRCBOX%\bundle\stage\isproj-g2-%G2_VER%\Media\Default\Disk Images\Disk1" -r

if "%1" == "std" set EDITION=STD
if "%1" == "ent" set EDITION=ENT
copy "%SRCBOX%\bundle\stage\isproj-g2-%G2_VER%\Media\Default\Package\Gensym%G2_VER%-%EDITION%.exe" .
..\..\tools\cmdLine\md5sums -u Gensym%G2_VER%-%EDITION%.exe > Gensym%G2_VER%-%EDITION%.exe.md5sum
..\..\tools\cmdLine\md5sums -u Gensym%G2_VER%-%EDITION%.zip > Gensym%G2_VER%-%EDITION%.zip.md5sum

popd

:end

@echo off

rem ***************************************************************************
rem  nsinstall

rem  Copyright (c) 1986 - 2017 Gensym Corporation.
rem  All Rights Reserved.

rem  John Valente

rem This script copies nptwplug.dll from %DSTBOX%\twplug\opt into your Netscape
rem directories, if you have set environment variables to indicate where your
rem Netscape directories are.
rem ***************************************************************************

if "%1" == "" goto noargs
echo WARNING: ignoring arguments

:noargs
if NOT "%DSTBOX%" == "" goto got_dstbox
echo ERROR: The environment variable DSTBOX is not set
goto usage

rem
rem *** We've found the dstbox; install Netscape 6 if available ***
rem
:got_dstbox
if NOT "%NETSCAPE6DIR%" == "" goto trynets6
echo WARNING: NETSCAPE6DIR env var not set
echo   Not attempting to install for Netscape 6
echo .
goto netscape4

rem
rem *** Make sure Netscape 6 directory exists ***
rem
:trynets6
if exist %NETSCAPE6DIR% goto docopy6
echo ERROR: The Netscape 6 directory %NETSCAPE6DIR% does not exist.
echo   Not attempting to install for Netscape 6
echo .
goto netscape4

rem
rem *** Create plugins subdirectory if it doesn't exist ***
rem
:docopy6
echo Installing nptwplug.dll for Netscape 6
if exist %NETSCAPE6DIR%\plugins goto dir6exists
mkdir %NETSCAPE6DIR%\plugins

rem
rem *** Now copy the file ***
rem
:dir6exists
copy %DSTBOX%\twplug\opt\nptwplug.dll %NETSCAPE6DIR%\plugins\nptwplug.dll

:netscape4
rem
rem *** Install Netscape 4 if available ***
rem
if NOT "%NETSCAPE4DIR%" == "" goto trynets4
echo WARNING: NETSCAPE4DIR env var not set
echo   Not attempting to install for Netscape 4
goto end

rem
rem *** Make sure Netscape 4 directory exists ***
rem
:trynets4
if exist %NETSCAPE4DIR% goto docopy4
echo ERROR: The Netscape 4 directory %NETSCAPE4DIR% does not exist.
goto end

rem
rem *** Create plugins subdirectory if it doesn't exist ***
rem
:docopy4
echo Installing nptwplug.dll for Netscape 4
if exist %NETSCAPE4DIR%\plugins goto dir4exists
mkdir %NETSCAPE4DIR%\plugins

rem
rem *** Now copy the file ***
rem
:dir4exists
copy %DSTBOX%\twplug\opt\nptwplug.dll %NETSCAPE4DIR%\plugins\nptwplug.dll
goto end

:usage
echo usage: nsinstall
goto end 

:end
rem  Clean up all variables we've created.

@echo off

rem * This is a bare bones NT version of the sandbox command, which will set all
rem * of the environment variables required to use runmake.

rem * First, make sure that they provide the sandbox name

if not "%1" == "" goto check_root

:error
echo Error: must provide sandbox name
echo e.g. sandbox ab
goto end

set MACHINE=intelnt

rem ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
rem +             Sandbox location -- SB_ROOT.                           +
rem ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
:check_root
if not "%SB_ROOT%" == "" goto check_sandbox
echo Warning: SB_ROOT not set; assuming your sandboxes are in C:\bt
set SB_ROOT=C:\bt


rem ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
rem +     Primary Environment Variables -- SRCBOX, etc.                  +
rem ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
:check_sandbox
set SANDBOX=%SB_ROOT%\%1
if exist %SANDBOX% goto find_srcbox

:find_srcbox

rem ---------------------------------------------------------------------------
rem + Most of the time, SRCBOX is the same as SANDBOX, but allow it to be a   +
rem + subdirectory named "src" as well.  Check for that first.                +
rem ---------------------------------------------------------------------------
set SRCBOX=%SANDBOX%\src
if not exist %SRCBOX% set SRCBOX=%SANDBOX%

rem ---------------------------------------------------------------------------
rem + Mostly we do use platform-specific DSTBOXes, but allow the use of       +
rem + SRCBOX as well.                                                         +
rem ---------------------------------------------------------------------------
set DSTBOX=%SANDBOX%\dst\%MACHINE%
if not exist %DSTBOX% set DSTBOX=%SRCBOX%

rem ---------------------------------------------------------------------------
rem + Allow inherited values of SCRIPTSBOX.  Try various things until         +
rem + something works.                                                        +
rem ---------------------------------------------------------------------------
if exist %SCRIPTSBOX%\scripts\nt goto java_stuff

set SCRIPTSBOX=%SANDBOX%
if exist %SCRIPTSBOX%\scripts\nt goto java_stuff

set SCRIPTSBOX=%SRCBOX%
if exist %SCRIPTSBOX%\scripts\nt goto java_stuff

set SCRIPTSBOX=k:\gensym
if exist %SCRIPTSBOX%\scripts\nt goto java_stuff

echo Warning: unable to find NT scripts directory.  Setting SCRIPTSBOX to
echo  k:\gensym.  You may need to map your K: drive to gensym4\intelnt

rem ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
rem +        Paths -- PATH and CLASSPATH                                 +
rem ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
:java_stuff
set CLASSPATH=%SRCBOX%\java

if not "%JAVA_HOME%" == "" goto use_java_home
echo Warning: JAVA_HOME not set; Java stuff will not be added to your paths.
goto done_java

:use_java_home
set CLASSPATH=%CLASSPATH%;%JAVA_HOME%\jre\lib\jaws.jar
set CLASSPATH=%CLASSPATH%;%JAVA_HOME%\lib\tools.jar
set CLASSPATH=%CLASSPATH%;%JAVA_HOME%\lib\dt.jar
set PATH=%JAVA_HOME%\bin;%PATH%

if not "%SWING_HOME%" == "" goto use_swing_home
echo Warning: SWING_HOME not set; JFC stuff will not be added to your classpath
goto done_java

:use_swing_home
set CLASSPATH=%CLASSPATH%;%SWING_HOME%\windows.jar
set CLASSPATH=%CLASSPATH%;%SWING_HOME%\swing.jar

:done_java
if not "%JVLBIN%" == "" goto finish_path
set JVLBIN=k:\gensym\ut\jvl-12r3\components\bin
echo Warning: JVLBIN not set; using default, %JVLBIN%

:finish_path
rem * Note, these path components are added successively to the FRONT of the
rem * path; therefore, the last one added will end up first in the list,
rem * followed by the next-to-last, and so on.
set PATH=%JVLBIN%;%PATH%
set PATH=%SRCBOX%\util;%PATH%
set PATH=%SCRIPTSBOX%\scripts\nt;%PATH%

rem ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
echo Using SRCBOX %SRCBOX%.  Remember that you need to be on the
echo drive that your sandbox is on for runmake to work.
echo --------------------------------------------------
:end

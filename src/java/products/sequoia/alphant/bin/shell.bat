@echo off

if "%OS%" == "Windows_NT" setlocal

echo "Starting the Telewindows2 Toolkit default shell. Please wait..."

if "%JAVALINK_HOME%" == "" goto error_javalink

if "%SEQUOIA_HOME%" == "" goto error_sequoia

set OLD_CLASSPATH=%CLASSPATH%
set OLD_PATH=%PATH%

set PATH=%JAVALINK_HOME%\bin;%PATH%;%JAVA_HOME%\bin

set CLASSPATH=%JAVA_HOME%\lib\classes.zip;%JAVALINK_HOME%\classes;%JAVALINK_HOME%\classes\core.jar;%JAVALINK_HOME%\classes\classtools.jar;%JAVALINK_HOME%\classes\javalink.jar;%SEQUOIA_HOME%\classes;%SEQUOIA_HOME%\classes\coreui.jar;%SEQUOIA_HOME%\classes\sequoia.jar;%SWING_HOME%\swing.jar;%SWING_HOME%\windows.jar;%CLASSPATH%

java com.gensym.shell.Shell -title "Default Application Shell" %*

set CLASSPATH=%OLD_CLASSPATH%
set PATH=%OLD_PATH%
goto end

:error_javalink
echo "JAVALINK_HOME not set"
goto end

:error_sequoia
echo "SEQUOIA_HOME not set"
goto end

:end

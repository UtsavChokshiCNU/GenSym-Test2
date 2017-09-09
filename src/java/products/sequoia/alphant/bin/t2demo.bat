@echo off

if "%OS%" == "Windows_NT" setlocal

if "%JAVALINK_HOME%" == "" goto error_javalink

if "%SEQUOIA_HOME%" == "" goto error_sequoia

echo "Starting G2, Please wait..."

call "%SEQUOIA_HOME%\bin\start_g2" -kb "%SEQUOIA_HOME%\kbs\mill.kb" -name "Mill" -rgn1lmt 40000000 -width 600 -height 500

echo Starting the Telewindow2 Toolkit default shell, please wait

set OLD_CLASSPATH=%CLASSPATH%
set OLD_PATH=%PATH%

set PATH=%JAVALINK_HOME%\bin;%PATH%;%JAVA_HOME%\bin

set CLASSPATH=%JAVA_HOME%\lib\classes.zip;%JAVALINK_HOME%\classes;%JAVALINK_HOME%\classes\core.jar;%JAVALINK_HOME%\classes\classtools.jar;%JAVALINK_HOME%\classes\javalink.jar;%SEQUOIA_HOME%\classes;%SEQUOIA_HOME%\classes\coreui.jar;%SEQUOIA_HOME%\classes\sequoia.jar;%SWING_HOME%\swing.jar;%SWING_HOME%\windows.jar;%CLASSPATH%

java com.gensym.shell.Shell -title "Telewindows2 Demo (mill)" -geometry 600x500-0-0 -host localhost -port 1111

SET CLASSPATH=%OLD_CLASSPATH%
SET PATH=%OLD_PATH%
goto end

:error_javalink
echo "JAVALINK_HOME not set"
goto end

:error_sequoia
echo "SEQUOIA_HOME not set"
goto end

:end

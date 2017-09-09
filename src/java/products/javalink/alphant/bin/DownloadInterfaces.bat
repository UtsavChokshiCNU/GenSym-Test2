@echo off

if "%OS%" == "Windows_NT" setlocal

echo "Starting G2BeanBuilder Please wait..."

if "%JAVALINK_HOME%" == "" goto error

set OLD_CLASSPATH=%CLASSPATH%
set OLD_PATH=%PATH%

set CLASSPATH=%JAVA_HOME%\lib\classes.zip;%JAVA_HOME%\lib\tools.jar;%JAVALINK_HOME%\classes;%JAVALINK_HOME%\classes\core.jar;%JAVALINK_HOME%\classes\classtools.jar;%JAVALINK_HOME%\classes\javalink.jar;%JAVALINK_HOME%\classes\beanbuilder.jar;%SEQUOIA_HOME%\classes\sequoia.jar;%CLASSPATH%

set PATH=%JAVALINK_HOME%\bin;%PATH%;%JAVA_HOME%\bin

java com.gensym.beanbuilder.G2DownloadInterfaces %*

set CLASSPATH=%OLD_CLASSPATH%
set PATH=%OLD_PATH%

goto end

:error
echo "JAVALINK_HOME not set, exiting"

:end

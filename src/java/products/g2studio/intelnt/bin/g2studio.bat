@echo off

if "%OS%" == "Windows_NT" setlocal

echo "Starting G2Studio. Please wait..."

if "%G2STUDIO_HOME%" == "" goto error_g2studio

set OLD_CLASSPATH=%CLASSPATH%
set OLD_PATH=%PATH%
set OLD_JAVA_HOME=%JAVA_HOME%

set JAVA_HOME=%G2STUDIO_HOME%\bin\jre

set PATH=%G2STUDIO_HOME%\bin;%JAVA_HOME%\bin;%PATH%

set CLASSPATH=%JAVA_HOME%\lib\classes.zip;%G2STUDIO_HOME%\classes;%G2STUDIO_HOME%\classes\core.jar;%G2STUDIO_HOME%\classes\classtools.jar;%G2STUDIO_HOME%\classes\javalink.jar;%G2STUDIO_HOME%\classes;%G2STUDIO_HOME%\classes\coreui.jar;%G2STUDIO_HOME%\classes\sequoia.jar;%G2STUDIO_HOME%\classes\generic-uitools.jar;%G2STUDIO_HOME%\classes\uiutil.jar;%G2STUDIO_HOME%\classes\ntw-uitools.jar;%G2STUDIO_HOME%\classes\sequoia-soon.jar;%G2STUDIO_HOME%\classes\iconeditor.jar;%G2STUDIO_HOME%\classes\g2studio.jar;%SWING_HOME%\swing.jar;%SWING_HOME%\windows.jar;%CLASSPATH%

java -Djava.protocol.handler.pkgs=com.gensym.net -Djava.content.handler.pkgs=com.gensym.net.contents com.gensym.demos.g2studiosample.Shell -title "G2Studio" %*

set CLASSPATH=%OLD_CLASSPATH%
set PATH=%OLD_PATH%
set JAVA_HOME=%OLD_JAVA_HOME%
goto end

:error_g2studio
echo "G2STUDIO_HOME not set"
goto end

:end

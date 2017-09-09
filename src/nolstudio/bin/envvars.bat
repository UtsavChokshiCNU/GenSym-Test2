rem setup environment variables for NOL Studio deployment.

rem If the following command does not contain an expanded G2 install home, then a problem 
rem occurred with the installer, and you should edit it to create the proper value
set NOL_INSTALL_HOME=%ROOTDIR%

if "%NOL_INSTALL_HOME%" == "" goto problem

if "%JAVALINK_HOME%" == "" set JAVALINK_HOME=%NOL_INSTALL_HOME%\javalink

if "%JAVA_HOME%" == "" set JAVA_HOME=%NOL_INSTALL_HOME%\jre

if "%NOLSTUDIO_HOME%" == "" set NOLSTUDIO_HOME=%NOL_INSTALL_HOME%\nolstudio

set PATH=%JAVALINK_HOME%\bin;%PATH%;%JAVA_HOME%\bin;%JAVA_HOME%\bin\client;%NOLSTUDIO_HOME%\bin;

set CLASSPATH=%JAVALINK_HOME%\classes;%JAVALINK_HOME%\classes\core.jar;%JAVALINK_HOME%\classes\classtools.jar;%JAVALINK_HOME%\classes\javalink.jar;%JAVALINK_HOME%\classes\beanbuilder.jar;%JAVALINK_HOME%\NolStudioData.jar;%JAVALINK_HOME%\NolStudioDeploy.jar;%JAVALINK_HOME%\NolStudioMath.jar

if exist "%JAVA_HOME%\lib\tools.jar" set CLASSPATH=%CLASSPATH%;%JAVA_HOME%\lib\tools.jar

goto end

:problem
echo javalink/bin/envvars.bat environment variable setting batch file was not properly set 
echo up by the installer; please edit it to create G2_INSTALL_HOME as appropriate for your 
echo installation.
pause
:end

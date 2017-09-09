rem setup environment variables for Javalink.

rem If the following command does not contain an expanded G2 install home, then a problem 
rem occurred with the installer, and you should edit it to create the proper value
set G2_INSTALL_HOME=%ROOTDIR%

if "%G2_INSTALL_HOME%" == "" goto problem

if "%JAVALINK_HOME%" == "" set JAVALINK_HOME=%G2_INSTALL_HOME%\javalink

if "%JAVA_HOME%" == "" set JAVA_HOME=%G2_INSTALL_HOME%\jre

set PATH=%JAVALINK_HOME%\bin;%PATH%;%JAVA_HOME%\bin

set CLASSPATH=%JAVALINK_HOME%\classes;%JAVALINK_HOME%\classes\core.jar;%JAVALINK_HOME%\classes\classtools.jar;%JAVALINK_HOME%\classes\javalink.jar;%JAVALINK_HOME%\classes\beanbuilder.jar

if exist "%JAVA_HOME%\lib\tools.jar" set CLASSPATH=%CLASSPATH%;%JAVA_HOME%\lib\tools.jar

goto end

:problem
echo javalink/bin/envvars.bat environment variable setting batch file was not properly set 
echo up by the installer; please edit it to create G2_INSTALL_HOME as appropriate for your 
echo installation.
pause
:end

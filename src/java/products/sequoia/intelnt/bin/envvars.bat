rem setup environment variables for Telewindows 2 ToolKit and Javalink.

rem If the following command does not contain an expanded G2 install home, then a problem 
rem occurred with the installer, and you should edit it to create the proper value
set G2_INSTALL_HOME=%ROOTDIR%

if "%G2_INSTALL_HOME%" == "" goto problem

if "%SEQUOIA_HOME%" == "" set SEQUOIA_HOME=%G2_INSTALL_HOME%\tw2

if "%JAVALINK_HOME%" == "" set JAVALINK_HOME=%G2_INSTALL_HOME%\javalink
if "%SEQUOIA_G2%" == "" set SEQUOIA_G2=%G2_INSTALL_HOME%\g2

if "%JAVA_HOME%" == "" set JAVA_HOME=%G2_INSTALL_HOME%\jre

if "%G2V8_OK%" == "" set G2V8_OK=%G2_INSTALL_HOME%\g2\g2.ok

set PATH=%JAVALINK_HOME%\bin;%PATH%;%JAVA_HOME%\bin

set CLASSPATH=%JAVALINK_HOME%\classes;%JAVALINK_HOME%\classes\core.jar;%JAVALINK_HOME%\classes\classtools.jar;%JAVALINK_HOME%\classes\javalink.jar;%JAVALINK_HOME%\classes\beanbuilder.jar;%SEQUOIA_HOME%\classes;%SEQUOIA_HOME%\classes\coreui.jar;%SEQUOIA_HOME%\classes\sequoia.jar;%CLASSPATH%

if exist "%JAVA_HOME%\lib\tools.jar" set CLASSPATH=%CLASSPATH%;%JAVA_HOME%\lib\tools.jar

goto end

:problem
echo tw2/bin/envvars.bat environment variable setting batch file was not properly
echo set up by the installer; please edit it to create G2_INSTALL_HOME as appropriate 
echo for your installation.
pause
:end

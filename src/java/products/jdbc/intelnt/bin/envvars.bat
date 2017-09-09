rem setup environment variables for JDBC bridge.

rem If the following command does not contain an expanded G2 install home, then a problem 
rem occurred with the installer, and you should edit it to create the proper value
set G2_INSTALL_HOME=%ROOTDIR%

if "%G2_INSTALL_HOME%" == "" goto problem

if "%JAVALINK_HOME%" == "" set JAVALINK_HOME=%G2_INSTALL_HOME%\javalink

if "%G2JDBC_HOME%" == "" set G2JDBC_HOME=%G2_INSTALL_HOME%\jdbc

if "%GSI_ROOT%" == "" set GSI_ROOT=%G2JDBC_HOME%

rem Force use the shipping JRE in case the default one is 64-bit.
set JAVA_HOME=%G2_INSTALL_HOME%\jre

set PATH=%JAVALINK_HOME%\bin;%JAVA_HOME%\bin;%PATH%

set CLASSPATH=%JAVALINK_HOME%\classes;%JAVALINK_HOME%\classes\core.jar;%JAVALINK_HOME%\classes\classtools.jar;%JAVALINK_HOME%\classes\javalink.jar;%JAVALINK_HOME%\classes\beanbuilder.jar;%G2JDBC_HOME%\classes\g2jdbc.jar;%G2JDBC_HOME%\classes\log4j-1.2.15.jar;%G2JDBC_HOME%\classes\postgresql-8.3-604.jdbc3.jar

if exist "%JAVA_HOME%\lib\tools.jar" set CLASSPATH=%CLASSPATH%;%JAVA_HOME%\lib\tools.jar

goto end

:problem
echo jdbc/bin/envvars.bat environment variable setting batch file was not properly set 
echo up by the installer; please edit it to create G2_INSTALL_HOME as appropriate for your 
echo installation.
pause
:end

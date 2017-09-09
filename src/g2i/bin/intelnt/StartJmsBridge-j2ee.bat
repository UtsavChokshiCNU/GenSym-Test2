@echo off
setlocal

rem
rem	This batch file launches the JMSlink Bridge
rem	You may supply up to one argument
rem	   - the port number the bridge is listening for G2 connections
rem        - default port number: 22070
rem


set HM=%ROOTDIR%
set JVM=%HM%\jre

set J2E=%J2EE_HOME%
set J2EE_LIB=%J2EE_HOME%\lib\j2ee.jar;%J2E%\lib\locale

set PATH=%HM%\jms\bin;%J2E%\bin;%JVM%\bin;%HM%\javalink\bin;%HM%\tw2\bin;%HM%\gsi;%PATH%
set CLASSPATH=%HM%\jms\classes\G2Jms.jar;%J2EE_LIB%;%HM%\javalink\classes\core.jar;%HM%\javalink\classes\classtools.jar;%HM%\javalink\classes\javalink.jar


if "%1" == "" goto defaultPort

echo Starting G2-JMS Bridge for J2EE V1.3.1 Reference Implementation...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port %*

goto end

:defaultPort
echo Starting G2-JMS Bridge for J2EE V1.3.1 Reference Implementation...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port 22070

:end
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

SET IBM_DIR=%MQ_JAVA_INSTALL_PATH%
set IBM_LIB=%IBM_DIR%\lib\com.ibm.mq.jar;%IBM_DIR%\lib\com.ibm.mqjms.jar;%IBM_DIR%\lib\com.ibm.mqbind.jar;%IBM_DIR%\lib\jms.jar;%IBM_DIR%\lib\jndi.jar;%IBM_DIR%\lib\fscontext.jar;%IBM_DIR%\lib\connector.jar;%IBM_DIR%\lib\jta.jar;%IBM_DIR%\lib\ldap.jar;%IBM_DIR%\lib\providerutil.jar

set PATH=%HM%\jms\bin;%JVM%\bin;%HM%\javalink\bin;%HM%\tw2\bin;%HM%\gsi;;%IBM_DIR%\lib;%IBM_DIR%\bin;%MQ_JAVA_DATA_PATH%\bin;%PATH%
set CLASSPATH=%HM%\jms\classes\G2Jms.jar;%IBM_LIB%;%HM%\javalink\classes\core.jar;%HM%\javalink\classes\classtools.jar;%HM%\javalink\classes\javalink.jar


if "%1" == "" goto defaultPort

echo Starting G2-JMS Bridge for IBM WebSphereMQ Version 5.3.1
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port %*

goto end

:defaultPort
echo Starting G2-JMS Bridge for IBM WebSphereMQ Version 5.3.1
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port 22070

:end
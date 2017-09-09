@echo off
setlocal

echo Please wait...


set HM=%G2I_HOME%
set G2=%G2_HOME%
set JVM=%JAVA_HOME%

SET IBM_DIR=%MQ_JAVA_INSTALL_PATH%
set IBM_LIB=%IBM_DIR%\lib\com.ibm.mq.jar;%IBM_DIR%\lib\com.ibm.mqjms.jar;%IBM_DIR%\lib\com.ibm.mqbind.jar;%IBM_DIR%\lib\jms.jar;%IBM_DIR%\lib\jndi.jar;%IBM_DIR%\lib\fscontext.jar;%IBM_DIR%\lib\connector.jar;%IBM_DIR%\lib\jta.jar;%IBM_DIR%\lib\ldap.jar;%IBM_DIR%\lib\providerutil.jar

set JAVALINK_LIB=%G2%\javalink\classes\javalink.jar;%G2%\javalink\classes\core.jar;%G2%\javalink\classes\classtools.jar

set PATH=%HM%\bin;%JVM%\bin;%G2%\javalink\bin;%IBM_DIR%\lib;%IBM_DIR%\bin;%MQ_JAVA_DATA_PATH%\bin
set CLASSPATH=%HM%\java;%JAVALINK_LIB%;%IBM_LIB%


cd %HM%\java

if "%1" == "" goto defaultPort

echo Starting G2-JMS Bridge for IBM WebSphereMQ Version 5.3.1
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port %1

goto end

:defaultPort
echo Starting G2-JMS Bridge for IBM WebSphereMQ Version 5.3.1
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port 22077

:end
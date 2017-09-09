@echo off
setlocal

echo Please wait...

set HM=%G2I_HOME%
set G2=%G2_HOME%
set JVM=%JAVA_HOME%

set JBOSS_HM=c:\jboss-3.2.3

if "%JBOSS_HOME%" == "" goto defaultJBOSS
set JBOSS_HM=%JBOSS_HOME%
:defaultJBOSS


set JBOSS_HM_CLIENT=%JBOSS_HM%\client

set JBOSS_LIB=%JBOSS_HM_CLIENT%\jbossall-client.jar;%JBOSS_HM_CLIENT%\jbossmq-client.jar;%JBOSS_HM_CLIENT%\jnet.jar;%JBOSS_HM_CLIENT%\jnp-client.jar;%JBOSS_HM_CLIENT%\log4j.jar
set JAVALINK_LIB=%G2%\javalink\classes\javalink.jar;%G2%\javalink\classes\core.jar;%G2%\javalink\classes\classtools.jar

set PATH=%HM%\bin;%JBOSS_HM%\bin;%JVM%\bin;%G2%\javalink\bin
set CLASSPATH=%HM%\java;%JAVALINK_LIB%;%JBOSS_LIB%


cd %HM%\java

if "%1" == "" goto defaultPort

echo Starting G2-JMS Bridge for JBoss V3.0.6 Application Server...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port %1

goto end

:defaultPort
echo Starting G2-JMS Bridge for JBoss V3.0.6 Application Server...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port 22077

:end
@echo off
setlocal

echo Please wait...


set HM=%G2I_HOME%
set G2=%G2_HOME%
set JVM=%JAVA_HOME%

set SONICMQ_HOME=C:\Program Files\SonicSoftware\SonicMQ
set SONICMQ_LIB=%SONICMQ_HOME%\lib

set SONIC_LIB=%SONICMQ_LIB%;%SONICMQ_LIB%\sonic_Client.jar;%SONICMQ_LIB%\broker.jar;%SONICMQ_LIB%\jndi.jar;%SONICMQ_LIB%\mfcontext.jar

set JAVALINK_LIB=%G2%\javalink\classes\javalink.jar;%G2%\javalink\classes\core.jar;%G2%\javalink\classes\classtools.jar

set PATH=%HM%\bin;%JVM%\bin;%G2%\javalink\bin
set CLASSPATH=%HM%\java;%JAVALINK_LIB%;%SONIC_LIB%


cd %HM%\java

if "%1" == "" goto defaultPort

echo Starting G2-JMS Bridge for Sonic MQ Version 5.0.1
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port %1

goto end

:defaultPort
echo Starting G2-JMS Bridge for Sonic MQ V5 Version 5.0.1
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port 22077

:end
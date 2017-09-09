@echo off
setlocal

echo Please wait...


set HM=%G2I_HOME%
set G2=%G2_HOME%
set JVM=%JAVA_HOME%

SET FMQ_DIR=C:\Program Files\Fiorano\FioranoMQ7.0
set FMQ_LIB=%FMQ_DIR%\lib\common.zip;%FMQ_DIR%\lib\fmprtl.zip

set JAVALINK_LIB=%G2%\javalink\classes\javalink.jar;%G2%\javalink\classes\core.jar;%G2%\javalink\classes\classtools.jar

set PATH=%HM%\bin;%JVM%\bin;%G2%\javalink\bin
set CLASSPATH=%HM%\java;%JAVALINK_LIB%;%FMQ_LIB%


cd %HM%\java

if "%1" == "" goto defaultPort

echo Starting G2-JMS Bridge for Fiorano MQ Version 7.0
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port %1

goto end

:defaultPort
echo Starting G2-JMS Bridge for Fiorano MQ Version 7.0
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port 22077

:end
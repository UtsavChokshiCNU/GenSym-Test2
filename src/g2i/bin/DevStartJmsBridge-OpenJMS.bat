@echo off
setlocal

echo Please wait...


set HM=%G2I_HOME%
set G2=%G2_HOME%
set JVM=%JAVA_HOME%

set OPENJMS_HOME=C:\openjms-0.7.6.1
set POLICY_FILE=%OPENJMS_HOME%\config\openjms.policy
set OPENJMS_LIB=%OPENJMS_HOME%\lib\openjms-client-0.7.6.1.jar;%OPENJMS_HOME%\lib\jta-1.0.1.jar

set JAVALINK_LIB=%G2%\javalink\classes\javalink.jar;%G2%\javalink\classes\core.jar;%G2%\javalink\classes\classtools.jar

set PATH=%HM%\bin;%J2EE_HOME%\bin;%JVM%\bin;%G2%\javalink\bin
set CLASSPATH=%OPENJMS_LIB%;%HM%\java;%JAVALINK_LIB%


cd %HM%\java

if "%1" == "" goto defaultPort

echo Starting G2-JMS Bridge for OpenJMS V7.6.1 ...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port %1

goto end

:defaultPort
echo Starting G2-JMS Bridge for OpenJMS V7.6.1 ...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port 22070

:end

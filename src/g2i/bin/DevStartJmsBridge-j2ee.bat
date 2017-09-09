@echo off
setlocal

echo Please wait...


set HM=%G2I_HOME%
set G2=%G2_HOME%
set JVM=%JAVA_HOME%


set J2EE_LIB=%J2EE_HOME%\lib\j2ee.jar;%J2EE_HOME%\lib\locale
set JAVALINK_LIB=%G2%\javalink\classes\javalink.jar;%G2%\javalink\classes\core.jar;%G2%\javalink\classes\classtools.jar

set PATH=%HM%\bin;%J2EE_HOME%\bin;%JVM%\bin;%G2%\javalink\bin
set CLASSPATH=%HM%\java;%JAVALINK_LIB%;%J2EE_LIB%


cd %HM%\java

if "%1" == "" goto defaultPort

echo Starting G2-JMS Bridge for J2EE V1.3.1 Reference Implementation...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port %1

goto end

:defaultPort
echo Starting G2-JMS Bridge for J2EE V1.3.1 Reference Implementation...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port 22077

:end
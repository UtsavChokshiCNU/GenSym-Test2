@echo off
echo Please wait...

if "%1" == "" goto ENTER_AGAIN
if "%2" == "" goto ENTER_AGAIN

set PROJECT_HOME=C:\bt\fwu\g2i\java
set JAVA_HOME=c:\jdk1.3.1_06
set J2EE_HOME=c:\j2sdkee1.3.1
set XML_HOME=c:\xerces-1_4_4
set JAVALINK_HOME=C:\Program Files\Gensym\escor_rethink\javalink

set PATH_ORIG=%PATH%
set PATH=%PROJECT_HOME%\bin;%JAVA_HOME%\bin;%JAVALINK_HOME%\bin

set CLASSPATH_ORIG=%CLASSPATH%
set CLASSPATH=%JAVALINK_HOME%\classes\javalink.jar;%JAVALINK_HOME%\classes;%PROJECT_HOME%\lib;%PROJECT_HOME%;C:\Projects\G2-jms\classes;%XML_HOME%\xerces.jar;C:\jdev903\jdev\lib\jdev-rt.jar;C:\jdev903\soap\lib\soap.jar;C:\jdev903\lib\xmlparserv2.jar;C:\jdev903\jlib\javax-ssl-1_2.jar;C:\jdev903\jlib\jssl-1_2.jar;C:\jdev903\j2ee\home\lib\activation.jar;C:\jdev903\j2ee\home\lib\mail.jar;C:\jdev903\j2ee\home\lib\http_client.jar;%CLASSPATH%;%JAVA_HOME%\lib\;%J2EE_HOME%\lib\j2ee.jar;%J2EE_HOME%\lib\locale;C:\Projects;C:\Projects\G2-Ws\googledemo\googleProj\classes

java -Djms.properties=%J2EE_HOME%\config\jms_client.properties com.gensym.jms.G2Jms %1 %2 %3 %4

set PATH=%PATH_ORIG%
set CLASSPATH=%CLASSPATH_ORIG%

goto END

:ENTER_AGAIN
echo Please provide hostname and port number at command line,
echo   e.g. -port 22044 -g2host localhost -g2port 1111

:END
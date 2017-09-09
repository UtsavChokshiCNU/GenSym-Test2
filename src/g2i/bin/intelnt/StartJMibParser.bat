@echo off
setlocal

set G2_HOME=%ROOTDIR%
set JAVA_HOME=%G2_HOME%\jre
set JAVALINK_HOME=%G2_HOME%\javalink

set PATH=%JAVA_HOME%\bin;%JAVALINK_HOME%\bin;%PATH%
set JAVALINK_CLASSPATH=%JAVALINK_HOME%\classes\core.jar;%JAVALINK_HOME%\classes\javalink.jar;%JAVALINK_HOME%\classes\classtools.jar;%JAVALINK_HOME%\classes
set CLASSPATH=%JAVALINK_CLASSPATH%;.;%G2_HOME%\g2mibparser\classes;%G2_HOME%\g2mibparser\classes\jmibparser.jar;%G2_HOME%\g2mibparser\classes\AdventNetSnmpLLAPI.jar;%G2_HOME%\g2mibparser\classes\AdventNetSnmpHLAPI.jar;%G2_HOME%\g2mibparser\classes\MibBrowser.jar;%CLASSPATH%


echo Starting JMibParser...
java com.gensym.JMibParser.JMibParser -port 22090 -debug 6

@echo off
setlocal

rem	This batch file launches the Java SNMP Bridge

set HM=%ROOTDIR%
set JVM=%HM%\jre

set PATH=%HM%\jsnmp\bin;%JVM%\bin;%HM%\javalink\bin;.;%PATH%

set CLASSPATH=%JVM%\lib\rt.jar;%HM%\jsnmp\classes;%HM%\javalink\classes;%HM%\jsnmp\classes\AdventNetSnmp.jar;%HM%\jsnmp\classes\AdventNetSnmpHLAPI.jar;%HM%\jsnmp\classes\AdventNetSnmpLLAPI.jar;%HM%\jsnmp\classes\AdventNetLogging.jar;%HM%\javalink\classes\classtools.jar;%HM%\javalink\classes\core.jar;%HM%\javalink\classes\javalink.jar;%HM%\jsnmp\classes\G2SNMP.jar

echo Starting Java SNMP Bridge...
java com.gensym.G2SNMP.JsnmpBridge %*



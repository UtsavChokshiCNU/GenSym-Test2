#!/bin/csh
setenv HM %ROOTDIR%

if ( $?JAVA_HOME ) then
  setenv JVM $JAVA_HOME
else
  setenv JVM ${HM}/jre
endif

if ( $?LD_LIBRARY_PATH ) then
  setenv LD_LIBRARY_PATH ${HM}/javalink/bin:${LD_LIBRARY_PATH}
else
  setenv LD_LIBRARY_PATH ${HM}/javalink/bin
endif

setenv CLASSPATH ${HM}/jmail/classes/G2JMail.jar:${HM}/jmail/classes/mail.jar:${HM}/jmail/classes/activation.jar:${HM}/javalink/classes/core.jar:${HM}/javalink/classes/classtools.jar:${HM}/javalink/classes/javalink.jar

setenv PATH $JAVA_HOME/bin\:.\:$PATH

setenv CLASSPATH $JAVA_HOME/lib/tools.jar:$JAVA_HOME/lib/dt.jar:${HM}/jsnmp/classes:${HM}/jsnmp/classes/AdventNetSnmp.jar:${HM}/jsnmp/classes/AdventNetSnmpHLAPI.jar:${HM}/jsnmp/classes/AdventNetSnmpLLAPI.jar:${HM}/javalink/classes/classtools.jar:${HM}/javalink/classes/core.jar:${HM}/javalink/classes/javalink.jar:${HM}/javalink/classes:${HM}/jsnmp/classes/G2SNMP.jar

java com.gensym.G2SNMP.JsnmpBridge $*

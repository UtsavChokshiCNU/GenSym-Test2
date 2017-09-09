#!/bin/csh -f

#
#	This batch file launches the JDBC Bridge
#	You have to supply at least -driver arguments
#         - the JDBC driver name, e.g. org.postgresql.Driver
#	   - the optional port number the bridge is listening for G2 connections
#
#      Add -help parameter to get know the rest G2-JDBC bridge command line options 
#      
#      If you want to another database, you have to add into CLASSPATH the jar with JDBC driver for this database
#

if ($#argv < 1) then
  goto usage
endif


set driver=$1
if (driver == "") then
  goto usage
endif

set port = $2
if ($port == "") then
  set port = 22041 
endif

goto execute

usage:
echo "usage: $0 driver [port]"
echo "   driver - JDBC driver, e.g. org.postgresql.Driver"
echo "   port - G2-JDBC bridge listening port. Default value: 22041"
exit 1

execute:

source `dirname $0`/set-envvars

# add JDBC driver(s) into CLASSPATH
#set CLASSPATH=${CLASSPATH}:${G2JDBC_HOME}/classes/ojdbc6.jar
#set CLASSPATH=${CLASSPATH}:${G2JDBC_HOME}/classes/ojdbc6.jar

java -cp $CLASSPATH -Djava.library.path="$JAVALINK_HOME/bin:$G2JDBC_HOME/bin" core.G2JDBCBridge $*

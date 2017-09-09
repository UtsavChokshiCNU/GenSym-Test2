#!/bin/csh -f

if ( ! $?JAVA_HOME ) then
  echo "JAVA_HOME environment variable must be set."
  exit 1
endif

if ( ! $?SEQUOIA_HOME ) then
    echo "SEQUOIA_HOME environment variable must be set."
    exit 1
endif

if ( ! $?JAVALINK_HOME ) then
    echo "JAVALINK_HOME environment variable must be set."
    exit 1
endif

${SEQUOIA_HOME}/bin/start-g2 -kb $SEQUOIA_HOME/kbs/beans-demo.kb -width 600 -height 500 -tcpport 1288 -tcpipexact -name 'Beans on Workspaces Demo (G2)' &
sleep 5;

if ( $?CLASSPATH ) then
  setenv CLASSPATH ${CLASSPATH}:${JAVALINK_HOME}/classes/javalink.jar:${SEQUOIA_HOME}/classes:${SEQUOIA_HOME}/classes/sequoia.jar:.
else
  setenv CLASSPATH ${JAVALINK_HOME}/classes/javalink.jar:${SEQUOIA_HOME}/classes:${SEQUOIA_HOME}/classes/sequoia.jar:.

endif

if ( $?LD_LIBRARY_PATH ) then
  setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:${SEQUOIA_HOME}/bin
else
  setenv LD_LIBRARY_PATH ${SEQUOIA_HOME}/bin
endif

$JAVA_HOME/bin/java com.gensym.shell.Shell -host localhost -port 1288 -title "Beans on Workspaces Demo (T2)"

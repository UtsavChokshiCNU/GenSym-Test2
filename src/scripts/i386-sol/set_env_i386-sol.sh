#!/bin/sh

# set SRCBOX at first !!!
SRCBOX="/export/home/rishi/TrilogySOL10" # originating sandbox
DSTBOX=$SRCBOX/dst # will be defaulted from SRCBOX, if not provided
MACHINE=i386-sol
machine=i386-sol
HOSTNAME=gensym
SUPPRESSHELP=yes
export SRCBOX DSTBOX HOSTNAME MACHINE SUPPRESSHELP machine

G2_OK=$SRCBOX/g2.ok
G2_HOME=$SRCBOX/g2
G2_PATH=$SRCBOX/dst/g2/o
G2EXEC=$SRCBOX/dst/g2/o/g2
G2i_HOME=$SRCBOX/g2i
G2EXE=$DSTBOX/g2/o/g2    # location of g2 executable, if different
G2_DB=$SRCBOX/g2db       # location of G2 database KBs
G2_OPCLINK=$SRCBOX/g2opc # location of opclink
JAVA_SRCBOX=$SRCBOX/java # java sandbox if different from originating
export G2_HOME G2_PATH G2EXEC G2i_HOME G2_OK G2EXE G2_DB G2_OPCLINK JAVA_SRCBOX

JAVA_HOME=/usr/jdk/j2sdk1.4.2_06 # location of java installation
JAVADOC_CLASSPATH=${JAVADOC_CLASSPATH}:${SRCBOX}/java:${JAVA_HOME}:${JAVA_HOME}/lib/tools.jar
CLASSPATH=${CLASSPATH}:${SRCBOX}/java:${JAVA_HOME}/lib/tools.jar
export JAVA_HOME JAVADOC_CLASSPATH CLASSPATH

PATH=$JAVA_HOME/bin:$PATH:/usr/ccs/bin:/usr/sfw/bin:$SRCBOX/scripts:$SRCBOX/scripts/$MACHINE
export PATH

LD_LIBRARY_PATH=$SRCBOX/specific/intelsol:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH


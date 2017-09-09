#!/bin/bash

. setdirs.sh

export PLATFM=linux64

if [ -z "$JAVA_HOME" ]; then
    export JAVA_HOME=/usr/lib/jvm/java-6-sun
fi

export CLASSPATH=$CLASSPATH:$DSTBOX/javalink/classes/javalink.jar
export CLASSPATH=$CLASSPATH:$DSTBOX/javalink/classes/core.jar
export CLASSPATH=$CLASSPATH:$DSTBOX/javalink/classes/classtools.jar
export CLASSPATH=$CLASSPATH:$DSTBOX/jdbc/g2jdbc.jar
export CLASSPATH=$CLASSPATH:$SRCBOX/g2db/java/G2JDBC/libs/postgresql-8.3-604.jdbc3.jar

$JAVA_HOME/bin/java -Djava.library.path="${DSTBOX}/javalink/bin:${DSTBOX}/jdbc" -cp $CLASSPATH core.G2JDBCBridge -driver org.postgresql.Driver -port 22041s

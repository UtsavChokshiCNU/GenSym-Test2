#!/bin/bash

clear
export SRCBOX=/g2/src
export DSTBOX=/g2/dst
export CLASSPATH=$CLASSPATH:$DSTBOX/javalink/classes/javalink.jar
export CLASSPATH=$CLASSPATH:$DSTBOX/javalink/classes/core.jar
export CLASSPATH=$CLASSPATH:$DSTBOX/javalink/classes/classtools.jar
export CLASSPATH=$CLASSPATH:$DSTBOX/jdbc/g2jdbc.jar
export CLASSPATH=$CLASSPATH:$SRCBOX/g2db/java/G2JDBC/libs/postgresql-8.3-604.jdbc3.jar

java -Djava.library.path=$DSTBOX/javalink/lib -Djava.library.path=$DSTBOX/jdbc -cp $CLASSPATH core.G2JDBCBridge -driver org.postgresql.Driver -port 22041s

cls
echo off

set SRCBOX=C:/g2/src
set DSTBOX=C:/g2/dst
set CLASSPATH=%CLASSPATH%;%DSTBOX%/javalink/classes/javalink.jar
set CLASSPATH=%CLASSPATH%;%DSTBOX%/javalink/classes/core.jar
set CLASSPATH=%CLASSPATH%;%DSTBOX%/javalink/classes/classtools.jar
set CLASSPATH=%CLASSPATH%;%DSTBOX%/jdbc/g2jdbc.jar
set CLASSPATH=%CLASSPATH%;%SRCBOX%/g2db/java/G2JDBC/libs/postgresql-8.3-604.jdbc3.jar

java -Djava.library.path=%DSTBOX%/javalink/lib -Djava.library.path=%DSTBOX%/jdbc -cp %CLASSPATH% core.G2JDBCBridge -driver org.postgresql.Driver -port 22041

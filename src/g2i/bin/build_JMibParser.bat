cls

set CUR_DIR=%~dp0
set SRCBOX=%CUR_DIR%\..\..\

set CLASSPATH=%SRCBOX%\java;%SRCBOX%\g2i\java;%SRCBOX%\g2i\java\classes\AdventNetSnmp.jar;%JAVA_HOME%\lib\tools.jar;%JAVA_HOME%\jre\lib\rt.jar;

cd %SRCBOX%\g2i\java\com\gensym\JMibParser\
del *.class /q /s

cd %SRCBOX%\java
call ..\util\jmake com/gensym/devtools devtools

cd %SRCBOX%\scripts\nt
call jmake %SRCBOX%\g2i\java jmibparser

cd %CUR_DIR%

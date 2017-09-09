echo on

set JAVADOC_CLASSPATH=%JAVAHOME%\lib\classes.zip;%SWING_HOME%\swingall.jar
set TARGET_DIR=%SRCBOX%\javalink\javalink-%MACHINE%-staging
set TARGET_CLASSES=%TARGET_DIR%\Java\classes
set TARGET_BIN=%TARGET_DIR%\bin

:package
java -mx50m com.gensym.devtools.BuildProductRepository javalink %SRCBOX% %TARGET_DIR% %JAVADOC_CLASSPATH%

rem Copy platform specific bin
copy %DSTBOX%\java\lib\JgiInterface.dll %TARGET_BIN%\JgiInterface.dll
if .%MACHINE%. == .intelnt. copy %BDK_HOME%\bridge\classes\beans.ocx %TARGET_CLASSES%\jars\activex

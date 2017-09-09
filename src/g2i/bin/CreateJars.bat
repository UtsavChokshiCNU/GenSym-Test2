echo on
setlocal


set PATH=%JAVAHOME%\bin;%PATH%
set JAVADOC_CLASSPATH=%JAVAHOME%\lib\classes.zip;%SWING_HOME%\swingall.jar
set CLASSPATH=%JAVAHOME%\jre\lib\rt.jar;%JAVAHOME%\jre\lib\jaws.jar;%JAVA_SRCBOX%\java
set SOURCE_DIR=%G2i_HOME%
set TARGET_DIR=%SOURCE_DIR%
set TARGET_CLASSES=%TARGET_DIR%\java\classes
set TARGET_BIN=%TARGET_DIR%\bin

if "%JAVA_SRCBOX%" == "" goto setup_bundle
if not exist "%JAVA_SRCBOX%" goto setup_bundle

goto create_jars

:setup_bundle

set G2=%G2_HOME%
set CLASSPATH=%SOURCE_DIR%\java\classes\devtools.jar;%G2%\javalink\classes\core.jar;%G2%\javalink\classes\classtools.jar;%G2%\javalink\classes\javalink.jar;%G2%\javalink\classes;%G2%\tw2\classes;%CLASSPATH%

:create_jars

if "%1" == "-official" goto compile
echo unofficial build
goto package

:compile
echo *** official build ***
java com.gensym.core.ProductManager -build -product G2Jmail
java com.gensym.core.ProductManager -build -product G2Jms
java com.gensym.core.ProductManager -build -product G2JGope
java com.gensym.core.ProductManager -build -product SocketManager
java com.gensym.core.ProductManager -build -product jmibparser
java com.gensym.core.ProductManager -build -product G2SNMP

cd %G2i_HOME%\java

:package

:jar
java -mx50m com.gensym.devtools.MakeProductJar -productName G2Jmail 	  -sourceDir %SOURCE_DIR%\java -targetFile %TARGET_CLASSES%\G2JMail.jar -javaSource %SOURCE_DIR%\java
java -mx50m com.gensym.devtools.MakeProductJar -productName G2Jms   	  -sourceDir %SOURCE_DIR%\java -targetFile %TARGET_CLASSES%\G2Jms.jar   -javaSource %SOURCE_DIR%\java
java -mx50m com.gensym.devtools.MakeProductJar -productName G2JGope 	  -sourceDir %SOURCE_DIR%\java -targetFile %TARGET_CLASSES%\G2JGope.jar -javaSource %SOURCE_DIR%\java
java -mx50m com.gensym.devtools.MakeProductJar -productName SocketManager -sourceDir %SOURCE_DIR%\java -targetFile %TARGET_CLASSES%\SocketManager.jar -javaSource %SOURCE_DIR%\java
java -mx50m com.gensym.devtools.MakeProductJar -productName jmibparser    -sourceDir %SOURCE_DIR%\java -targetFile %TARGET_CLASSES%\jmibparser.jar -javaSource %SOURCE_DIR%\java
java -mx50m com.gensym.devtools.MakeProductJar -productName G2SNMP        -sourceDir %SOURCE_DIR%\java -targetFile %TARGET_CLASSES%\G2SNMP.jar -javaSource %SOURCE_DIR%\java

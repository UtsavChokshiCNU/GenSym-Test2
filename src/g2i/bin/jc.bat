@echo off

setlocal

set HM=%G2I_HOME%

set PATH="%HM%\bin";%JAVAHOME%\bin;"%JAVA_SRCBOX%\java\products\javalink\intelnt\bin";"%DSTBOX%\javalink\lib";"%DSTBOX%\gsi\tape";%PATH%

set CLASSPATH=%JAVAHOME%\jre\lib\rt.jar;%JAVAHOME%\jre\lib\jaws.jar;%JAVAHOME%\lib\tools.jar;%JAVAHOME%\lib\dt.jar;%HM%\java\classes\devtools.jar;%HM%\java\classes\ntw-uitools.jar;%HM%\java\classes\generic-uitools.jar;%JAVA_SRCBOX%\java;%HM%\java\classes\mail.jar;%HM%\java\classes\activation.jar;%HM%\java\classes\jhall.jar;%HM%\java\classes\j2ee.jar;%HM%\java\classes\AdventNetSnmp.jar;%HM%\java\classes\AdventNetLogging.jar;%HM%\java\classes\MibBrowser.jar;c:\gensym\bt\java

if "%JAVA_SRCBOX%" == "" goto setup_bundle
if not exist "%JAVA_SRCBOX%" goto setup_bundle

goto compile

:setup_bundle

set G2=%G2_HOME%
set CLASSPATH=%G2%\javalink\classes\core.jar;%G2%\javalink\classes\classtools.jar;%G2%\javalink\classes\javalink.jar;%G2%\javalink\classes;%G2%\tw2\classes;C:\JGoEval\JGo.jar;C:\JGoEval\JGoLayout.jar;%CLASSPATH%


:compile


cd %G2i_HOME%
java -mx70m com.gensym.devtools.JavaMake -srcbox %G2i_HOME% -root java -product

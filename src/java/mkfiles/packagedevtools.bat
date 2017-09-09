echo on

set JAVADOC_CLASSPATH=%JAVAHOME%\lib\classes.zip;%SWING_HOME%\swingall.jar
set SOURCE_DIR=%SRCBOX%
set TARGET_DIR=%SOURCE_DIR%\devtools\devtools-intelnt-staging
set TARGET_CLASSES=%TARGET_DIR%\classes
set TARGET_BIN=%TARGET_DIR%\bin

if "%1" == "-official" goto compile
echo unofficial build
goto package

:compile
echo *** official build ***
java com.gensym.core.ProductManager -build -product devtools
cd %SRCBOX%\java

:package
rem ***java -mx50m com.gensym.devtools.BuildProductRepository devtools %SOURCE_DIR% %TARGET_DIR% %JAVADOC_CLASSPATH%

:jar
java -mx50m com.gensym.devtools.MakeProductJar -productName devtools -sourceDir %SOURCE_DIR%\java -targetFile %TARGET_DIR%\devtools.jar -javaSource %SOURCE_DIR%\java


echo on

set JAVADOC_CLASSPATH=%JAVAHOME%\lib\classes.zip;%SWING_HOME%\swingall.jar
set SOURCE_DIR=%SRCBOX%
set TARGET_DIR=%SOURCE_DIR%\javalinkprof\javalinkprof-intelnt-staging
set TARGET_CLASSES=%TARGET_DIR%\classes
set TARGET_BIN=%TARGET_DIR%\bin

if "%1" == "-official" goto compile
echo unofficial build
goto package

:compile
echo *** official build ***
java com.gensym.core.ProductManager -build -product javalinkprof
cd %SRCBOX%\java\com\gensym\jlp
cvs commit version.dat
cd %SRCBOX%\java

:package
call %SRCBOX%\java\products\javalinkprof\kbs\copyProductKbs
java -mx50m -nojit com.gensym.devtools.BuildProductRepository javalinkprof %SOURCE_DIR% %TARGET_DIR% %JAVADOC_CLASSPATH%
java com.gensym.devtools.MakeProductJar -productName antlr -sourceDir %SOURCE_DIR%\java -targetFile %TARGET_CLASSES%\antlr.jar -javaSource  %SOURCE_DIR%\java



rem Copy platform specific bin

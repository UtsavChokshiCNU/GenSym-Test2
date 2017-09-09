echo on

set JAVADOC_CLASSPATH=%JAVAHOME%\lib\classes.zip;

set SOURCE_DIR=%SRCBOX%
set TARGET_DIR=%SOURCE_DIR%\ax2jbeans\ax2jbeans-intelnt-staging
set TARGET_CLASSES=%TARGET_DIR%\classes
set TARGET_BIN=%TARGET_DIR%\bin


java -mx50m com.gensym.devtools.BuildProductRepository ax2jbeans %SOURCE_DIR% %TARGET_DIR% %JAVADOC_CLASSPATH%

rem Copy library
copy %SRCBOX%\java\lib\JavaContainer.dll %TARGET_BIN%\JavaContainer.dll
copy %SRCBOX%\java\jars\axtools.jar %TARGET_CLASSES%\axtools.jar

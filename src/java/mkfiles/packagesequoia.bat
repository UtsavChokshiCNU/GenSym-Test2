@echo off
if "%JAVAPLUGIN_HOME%" == "" set JAVAPLUGIN_HOME=C:\Program Files\Java Plug-in 1.1
if .%MACHINE%. == .alphant. goto START
if not exist "%JAVAPLUGIN_HOME%" goto no_plugin

:START
set JAVADOC_CLASSPATH=%JAVAHOME%\lib\classes.zip;%SWING_HOME%\swingall.jar
set SOURCE_DIR=%SRCBOX%
set TARGET_DIR=%SOURCE_DIR%\sequoia\sequoia-%MACHINE%-staging
if .%MACHINE%. == .alphant. goto ALPHANT

:INTELNT
set TARGET_CLASSES=%TARGET_DIR%\java\classes
set TARGET_BIN=%TARGET_DIR%\java\bin
set ACTIVEX_DIR=%SOURCE_DIR%\java\activex
goto package

:ALPHANT
set TARGET_CLASSES=%TARGET_DIR%\classes
set TARGET_BIN=%TARGET_DIR%\bin
set ACTIVEX_DIR=%TARGET_DIR%\activex
goto package

if "%1" == "-official" goto compile
echo unofficial build
goto package

:compile
echo *** official build ***
java com.gensym.core.ProductManager -build -product sequoia
cd %SRCBOX%\java\com\gensym\ntw
cvs commit version.dat
cd %SRCBOX%\java


:package
java -mx40m com.gensym.devtools.BuildProductRepository sequoia %SOURCE_DIR% %TARGET_DIR% %JAVADOC_CLASSPATH%

echo ....Building sequoia.jar.....
cd %SRCBOX%\java\classes
rm sequoia.jar
cd %SRCBOX%\java
nmake -f mkfiles\intelnt-sequoia-o
copy %SRCBOX%\java\classes\sequoia.jar %TARGET_CLASSES%

copy "%JAVAPLUGIN_HOME%\bin\beans.ocx" %ACTIVEX_DIR%
copy "%JAVAPLUGIN_HOME%\classes\awt.ico" %ACTIVEX_DIR%
nmake -f mkfiles\intelnt-controls-o
nmake -f mkfiles\intelnt-wksp-o
xcopy /i %ACTIVEX_DIR%\* %TARGET_CLASSES%\activex

java com.gensym.devtools.ReplaceVersionStrings %TARGET_CLASSES%\activex
cd %TARGET_CLASSES%\activex
java com.gensym.devtools.RegFileFixer

echo Copying platform specific files to bin
copy %SRCBOX%\java\lib\JavaContainer.dll %TARGET_BIN%\JavaContainer.dll
copy %SRCBOX%\java\c\setup-sequoia-env.exe %TARGET_BIN%
cd %TARGET_DIR%
rm -rf vbshell >nul

goto end

:no_plugin
echo.
echo Can't find Java Plug-in to copy beans.ocx
echo.

:end

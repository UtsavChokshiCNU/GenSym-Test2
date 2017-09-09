@echo off
TITLE NeurOn-Line Studio
REM ------------------------------------------------------
REM This file should only be edited to change the following
REM paths to define PATH, CLASSPATH
REM updated August 16, 2017 by Dmitry Tselishchev
REM ------------------------------------------------------
SET PATH=.;..\..\jre\bin
SET CLASSPATH=.;..\..\jre\lib\rt.jar;..\..\jre\lib\jaws.jar;..\..\jre\lib\i18n.jar;..\..\jre\lib\sunrsasign.jar;..\NolStudioMath.jar;..\NolStudioGUI.jar;..\NolStudioData.jar;..\..\javalink\classes;..\..\javalink\classes\core.jar;..\..\javalink\classes\classtools.jar;..\..\javalink\classes\javalink.jar;..\..\javalink\classes\beanbuilder.jar



REM -- run NOL Studio --
java -Djava.library.path="..\..\javalink\bin" -classpath %CLASSPATH% -Xmx256m com.gensym.nols.main.NeurOnLine
goto result%ERRORLEVEL%
:result1
echo An Error has Occurred!
pause
:result0
REM else nothing has gone wrong, exit and do nothing...

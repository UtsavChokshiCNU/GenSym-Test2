echo on
rem	check args

if "%1" == "" 			goto show_usage
if "%SRCBOX%" == ""           goto show_usage

setlocal
if "%JAVAHOME%" == ""           set JAVAHOME=%JAVA_HOME%
if "%JAVAHOME%" == ""           goto errorNoJava

set NOLSTUDIO_HOME=%SRCBOX%\nolstudio
set JAVALINK_HOME=%SRCBOX%\java

set CLASSPATH=%NOLSTUDIO_HOME%;%JAVAHOME%\jre\lib\rt.jar;%JAVAHOME%\jre\lib\jaws.jar;%JAVALINK_HOME%;%NOLSTUDIO_HOME%\bin\nol.jar
set SOURCE_DIR=%NOLSTUDIO_HOME%
set STAGE_DIR=%SOURCE_DIR%\build-%1
set MATH_STAGE_DIR=%SOURCE_DIR%\build-%1\math
set DATA_STAGE_DIR=%SOURCE_DIR%\build-%1\data
set DEPLOY_STAGE_DIR=%SOURCE_DIR%\build-%1\deploy
set GUI_STAGE_DIR=%SOURCE_DIR%\build-%1\gui
set FINISH_STAGE_DIR=%SOURCE_DIR%\build-%1\build

:checkout the latest files
cd %NOLSTUDIO_HOME%
del /s /F /q %NOLSTUDIO_HOME%\*.class

:compile java files

javac -J-mx120m  -deprecation -g:none -O com\gensym\nols\main\NeurOnLine.java
javac  -deprecation -g:none -O com\gensym\nols\data\function\*.java
javac -deprecation -g:none -O com\gensym\nols\deploy\*.java
javac -deprecation -g:none -O com\gensym\nols\deployutil\ActiveXRegisterManager.java
javac -deprecation -g:none -O com\gensym\nols\data\VersionManager.java
javac -deprecation -g:none -O com\gensym\nols\data\VersionManagerForOnlineProcessor.java
javac -deprecation -g:none -O com\gensym\nols\data\VersionManagerForOnlineOptimizer.java

if not exist "%STAGE_DIR%" 		md "%STAGE_DIR%"
if not exist "%MATH_STAGE_DIR%" 		md "%MATH_STAGE_DIR%"
if not exist "%MATH_STAGE_DIR%\com" 		md "%MATH_STAGE_DIR%\com"
if not exist "%MATH_STAGE_DIR%\com\gensym" 		md "%MATH_STAGE_DIR%\com\gensym"
if not exist "%MATH_STAGE_DIR%\com\gensym\math" 		md "%MATH_STAGE_DIR%\com\gensym\math"

if not exist "%DATA_STAGE_DIR%" 		md "%DATA_STAGE_DIR%"
if not exist "%DATA_STAGE_DIR%\com" 		md "%DATA_STAGE_DIR%\com"
if not exist "%DATA_STAGE_DIR%\com\gensym" 		md "%DATA_STAGE_DIR%\com\gensym"
if not exist "%DATA_STAGE_DIR%\com\gensym\nols" 		md "%DATA_STAGE_DIR%\com\gensym\nols"

if not exist "%DEPLOY_STAGE_DIR%" 		md "%DEPLOY_STAGE_DIR%"
if not exist "%DEPLOY_STAGE_DIR%\com" 		md "%DEPLOY_STAGE_DIR%\com"
if not exist "%DEPLOY_STAGE_DIR%\com\gensym" 		md "%DEPLOY_STAGE_DIR%\com\gensym"
if not exist "%DEPLOY_STAGE_DIR%\com\gensym\nols" 		md "%DEPLOY_STAGE_DIR%\com\gensym\nols"
if not exist "%DEPLOY_STAGE_DIR%\com\gensym\nols\deploy" 		md "%DEPLOY_STAGE_DIR%\com\gensym\nols\deploy"

if not exist "%GUI_STAGE_DIR%" 		md "%GUI_STAGE_DIR%"
if not exist "%GUI_STAGE_DIR%\com" 		md "%GUI_STAGE_DIR%\com"
if not exist "%GUI_STAGE_DIR%\com\gensym" 		md "%GUI_STAGE_DIR%\com\gensym"
if not exist "%GUI_STAGE_DIR%\com\gensym\nols" 		md "%GUI_STAGE_DIR%\com\gensym\nols"
if not exist "%GUI_STAGE_DIR%\com\gensym\nols\main" 		md "%GUI_STAGE_DIR%\com\gensym\nols\main"

if not exist "%FINISH_STAGE_DIR%" 		md "%FINISH_STAGE_DIR%"
if not exist "%FINISH_STAGE_DIR%\doc" 		md "%FINISH_STAGE_DIR%\doc"
if not exist "%FINISH_STAGE_DIR%\bin" 		md "%FINISH_STAGE_DIR%\bin"
if not exist "%FINISH_STAGE_DIR%\projects" 		md "%FINISH_STAGE_DIR%\projects"
if not exist "%FINISH_STAGE_DIR%\projects\examples" 		md "%FINISH_STAGE_DIR%\projects\examples"

del /s /F /q %MATH_STAGE_DIR%\com\gensym\math\*.*
del /s /F /q %DATA_STAGE_DIR%\com\gensym\nols\*.*
del /s /F /q %DEPLOY_STAGE_DIR%\com\gensym\nols\deploy\*.*
del /s /F /q %GUI_STAGE_DIR%\com\gensym\nols\main\*.*



:create_jars
rem copy everything from the development area

xcopy %NOLSTUDIO_HOME%\com\gensym\math %MATH_STAGE_DIR%\com\gensym\math /E
copy %NOLSTUDIO_HOME%\com\gensym\DEBUG.class %MATH_STAGE_DIR%\com\gensym\

copy %NOLSTUDIO_HOME%\com\gensym\nols\main\NeurOnLine.class %GUI_STAGE_DIR%\com\gensym\nols\main\NeurOnLine.class 

xcopy %NOLSTUDIO_HOME%\com\gensym\nols %DATA_STAGE_DIR%\com\gensym\nols /E

del /q %DATA_STAGE_DIR%\com\gensym\nols\deploy\OnlineProcessorAPIG2.class
del /q %DATA_STAGE_DIR%\com\gensym\nols\deploy\OnlineProcessorAPI.class
del /q %DATA_STAGE_DIR%\com\gensym\nols\deploy\OnlineOptimizerAPIG2.class
del /q %DATA_STAGE_DIR%\com\gensym\nols\deploy\OnlineOptimizerAPI.class
del /q %DATA_STAGE_DIR%\com\gensym\nols\main\NeurOnLine.class


xcopy %NOLSTUDIO_HOME%\com\gensym\nols\deploy %DEPLOY_STAGE_DIR%\com\gensym\nols\deploy /E

rem delete the source code 
del /s /F /q %STAGE_DIR%\*.java
del /s /F /q %STAGE_DIR%\cvs*

cd %DATA_STAGE_DIR%
jar cf NolStudioData.jar com
cd %GUI_STAGE_DIR%
jar cf NolStudioGUI.jar com
cd %MATH_STAGE_DIR%
jar cf NolStudioMath.jar com
cd %DEPLOY_STAGE_DIR%
jar cf NolStudioDeploy.jar com


cd %STAGE_DIR%
copy .\math\*.jar %FINISH_STAGE_DIR%\
copy .\data\*.jar %FINISH_STAGE_DIR%\
copy .\gui\*.jar %FINISH_STAGE_DIR%\
copy .\deploy\*.jar %FINISH_STAGE_DIR%\
copy %NOLSTUDIO_HOME%\demolicense.txt %FINISH_STAGE_DIR%\
copy %NOLSTUDIO_HOME%\nolstudio.bat %FINISH_STAGE_DIR%\
copy %NOLSTUDIO_HOME%\nolonline.bat %FINISH_STAGE_DIR%\
copy %NOLSTUDIO_HOME%\onlinenolstudio.bat %FINISH_STAGE_DIR%\
copy %NOLSTUDIO_HOME%\RegisterControls.bat %FINISH_STAGE_DIR%\
copy %NOLSTUDIO_HOME%\UnRegisterControls.bat %FINISH_STAGE_DIR%\
copy %NOLSTUDIO_HOME%\NolMainFrame.properties %FINISH_STAGE_DIR%\
copy %NOLSTUDIO_HOME%\NolStringResources.properties %FINISH_STAGE_DIR%\
copy %NOLSTUDIO_HOME%\known-bugs.txt %FINISH_STAGE_DIR%\
copy %NOLSTUDIO_HOME%\nolstudio %FINISH_STAGE_DIR%\nolstudio
copy %NOLSTUDIO_HOME%\nolonline %FINISH_STAGE_DIR%\nolonline
copy %NOLSTUDIO_HOME%\readme-nol-bundle.html %FINISH_STAGE_DIR%\readme-nol-bundle.html
copy %NOLSTUDIO_HOME%\readme-nol-bundle.txt %FINISH_STAGE_DIR%\readme-nol-bundle.txt
copy %NOLSTUDIO_HOME%\readme.html %FINISH_STAGE_DIR%\readme.html
copy %NOLSTUDIO_HOME%\readme.txt %FINISH_STAGE_DIR%\readme.txt
copy %NOLSTUDIO_HOME%\bin\NolOnline.dll %FINISH_STAGE_DIR%\bin\
copy %NOLSTUDIO_HOME%\bin\jnol.dll %FINISH_STAGE_DIR%\bin\

xcopy %NOLSTUDIO_HOME%\projects %FINISH_STAGE_DIR%\projects /E/Y
xcopy %NOLSTUDIO_HOME%\doc %FINISH_STAGE_DIR%\doc  /E/Y

cd %NOLSTUDIO_HOME%
del /s /F /q %NOLSTUDIO_HOME%\*.class

goto end

:errorNoJava
@echo.
@echo Cannot find either JAVA_HOME or JAVAHOME environment variable.
@echo.
goto end

:show_usage
@echo.
@echo.
@echo Usage: CreateBuild "version-tag" 
@echo.
@echo	version-tag:	specifies the version to build
@echo			you only specify the version number,
@echo			i.e. 10b0, 20r0, etc
@echo.
@echo 	Examples:	createbuild 10r0  
@echo. 			createbuild 10r0  u:
@echo.

:end

REM echo off

if "%1" == "" goto error
if "%2" == "" goto notargetdir

set SOURCE_DIR=%SRCBOX%\java
set JAVASRC_HOME=%JAVA_HOME%\src
set SWINGSRC_HOME=%SWING_HOME%\src

cd %2
del /Q *.*
cd %SOURCE_DIR%\mkfiles

java -nojit -mx400m com.gensym.core.GenerateDocs %1 %2 %SOURCE_DIR% %JAVASRC_HOME% %SWINGSRC_HOME%
echo ***FINISHED***
goto end

:error
echo please specify a product name
goto end

:notargetdir
echo please specify a target dir

:end



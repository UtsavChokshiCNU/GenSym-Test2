echo off

if "%1" == "" goto error
if "%2" == "" goto nosourcedir

set SOURCE_DIR=%SRCBOX%\java
cd %SOURCE_DIR%\mkfiles

java  -mx400m com.gensym.core.LinkJavaDocs %1 %SOURCE_DIR% %2
echo ***FINISHED***
goto end

:error
echo please specify a product name
goto end

:nosourcedir
echo please specify a source dir - where the javadoc files reside

:end

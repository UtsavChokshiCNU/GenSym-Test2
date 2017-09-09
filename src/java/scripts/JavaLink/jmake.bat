@echo off

if exist %SRCBOX%\java\com\gensym\devtools\JavaMake.class goto begin

@echo on
echo Compiling JavaMake
javac %SRCBOX%\java\com\gensym\devtools\JavaMake.java


@echo off
if not exist %SRCBOX%\java\com\gensym\devtools\JavaMake.class goto error

:begin
set DIRECTORY=%1
set PRODUCT=%2
set CLEAN=%2

if NOT "%CLEAN%" == "-clean" goto compile

java -mx70m com.gensym.devtools.JavaMake -srcbox %SRCBOX% -root %DIRECTORY% -clean -product %PRODUCT% %*
goto end


:compile
java  -mx70m com.gensym.devtools.JavaMake -srcbox %SRCBOX% -root %DIRECTORY% -product %PRODUCT% %*
goto end


:error
echo Could not compile com/gensym/devtools/JavaMake


:end
@echo on

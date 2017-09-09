:ReplaceVersionStrings.bat
:AUTHOR: SJW
:CREATED: 4/27/99 

:DESCRIPTION:   

:CHECK FLAGS
if .%1. == .. goto USAGE
if .%1. == .demos. set PACKAGE=%SRCBOX%\java\com\gensym\demos
if .%1. == .beaneditor. set PACKAGE=%SRCBOX%\java\com\gensym\beaneditor
if .%1. == .shell. set PACKAGE=%SRCBOX%\java\com\gensym\shell
if .%1. == .doc. set PACKAGE=%SRCBOX%\doc


:CHECK IF CLASS FILE EXISTS
if not exist %SRCBOX%\java\com\gensym\devtools\ReplaceVersionStrings.class goto CHECK_SOURCE
goto RUN

:CHECK_SOURCE
if not exist  %SRCBOX%\java\com\gensym\devtools\ReplaceVersionStrings.java goto ERROR

:COMPILE
call javac  %SRCBOX%\java\com\gensym\devtools\ReplaceVersionStrings.java
call javac  %SRCBOX%\java\com\gensym\util\symbol\*.java
call javac  %SRCBOX%\java\com\gensym\util\*.java

:RUN
call java com.gensym.devtools.ReplaceVersionStrings %PACKAGE%
goto END

:USAGE
echo Usage: ReplaceVersionStrings.bat <PACKAGE_NAME>
echo <PACKAGE_NAME> options are demos, beaneditor, shell, docs
goto END

:ERROR
echo ERROR: ReplaceVersionStrings.java not found.  Please check your sandbox.

:END

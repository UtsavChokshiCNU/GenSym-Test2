:CommitVersionFiles.bat
:AUTHOR: SJW
:CREATED: 4/26/99 

:DESCRIPTION:   

:CHECK FLAGS
if .%1. == .. goto USAGE
if .%1. == .core. set DIR=core
if .%1. == .javalink. set DIR=jgi
if .%1. == .sequoia. set DIR=ntw

cd %SRCBOX%\java\com\gensym\%DIR%
cvs commit -F version.dat version.dat

:USAGE
echo Usage: CommitVersionFiles.bat <PRODUCT_NAME>
echo <PRODUCT_NAME> options are core, javalink, sequoia
goto END

:ERROR 

:END

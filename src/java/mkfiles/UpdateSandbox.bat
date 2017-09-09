:UpdateSandbox.bat
:AUTHOR: SJW
:CREATED: 4/26/99 

:DESCRIPTION:   

:REMOVE JAVA DIR
rd /S/Q %SRCBOX%\doc 

:UPDATE SANDBOX
cd %SRCBOX%
call cvs co ext rtl gsi util gen specific fnt
call cvs co java

mkdir %SRCBOX%\doc
mkdir %SRCBOX%\java\lib
mkdir %SRCBOX%\ext\o
mkdir %SRCBOX%\rtl\o
mkdir %SRCBOX%\gsi\o


:USAGE
echo Usage: UpdateSandbox.bat
goto END

:ERROR 

:END

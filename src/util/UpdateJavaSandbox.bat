:UpdateSandbox.bat
:AUTHOR: SJW
:CREATED: 4/26/99 

:DESCRIPTION:   

:UPDATE SANDBOX
cd %SRCBOX%
cvs co -P ext rtl gsi util gen specific fnt
cvs co -P -rJLTW2_10R2_BG1_BRANCH java

mkdir %SRCBOX%\doc
mkdir %SRCBOX%\java\lib
mkdir %SRCBOX%\ext\o
mkdir %SRCBOX%\rtl\o
mkdir %SRCBOX%\gsi\o
mkdir %SRCBOX%\java\o

:USAGE
echo Usage: UpdateSandbox.bat
goto END

:ERROR 

:END

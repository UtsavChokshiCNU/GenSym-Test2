cls

rem Builds G2 Server, instrumented for the line coverage.

set SCRIPTSBOX=%SRCBOX%
set MACHINE=Intelnt
set DISPLAY=X

call vcvars32
call setenv

cd %SRCBOX%\scripts\nt
call runmake ext o all

cd %SRCBOX%\scripts\nt
call runmake rtl o all

cd %SRCBOX%\scripts\nt
call runmake fnt o all

cd %SRCBOX%\scripts\nt
call runmake jpeg o all

cd %SRCBOX%\scripts\nt
call runmake scintilla o all

cd %SRCBOX%\scripts\nt
call runmake xml o all

cd %SRCBOX%\scripts\nt
call runmake g2 o coverage




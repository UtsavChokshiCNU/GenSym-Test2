cls

rem Builds TWNG, instrumented for the line coverage.

set SCRIPTSBOX=%SRCBOX%
set MACHINE=Intelnt
set DISPLAY=X

call vcvars32
call setenv

cd %SRCBOX%\scripts\nt
call runmake rtl o all

cd %SRCBOX%\scripts\nt
call runmake fnt o all

cd %SRCBOX%\scripts\nt
call runmake jpeg o all

cd %SRCBOX%\scripts\nt
call runmake scintilla o all

cd %SRCBOX%\scripts\nt
call runmake xtp o

cd %SRCBOX%\scripts\nt
call runmake widgets o

cd %SRCBOX%\scripts\nt
call runmake twng o clean coverage

cd %SRCBOX%\scripts\nt
call runmake twng o install
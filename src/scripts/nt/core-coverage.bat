
cls

set SCRIPTSBOX=%SRCBOX%
set MACHINE=Intelnt
set DISPLAY=X

call vcvars32
call setenv
call iclvars
call setenv

cd %SRCBOX%\scripts\nt
call runmake ext opt-intc coverage

cd %SRCBOX%\scripts\nt
call runmake rtl opt-intc coverage

cd %SRCBOX%\scripts\nt
call runmake fnt opt-intc coverage

cd %SRCBOX%\scripts\nt
call runmake scintilla opt-intc coverage

cd %SRCBOX%\scripts\nt
call runmake xml opt-intc coverage

cd %SRCBOX%\scripts\nt
call runmake jpeg opt-intc coverage

cd %SRCBOX%\scripts\nt 

set SCRIPTSBOX=%SRCBOX%
set MACHINE=Intelnt
set DISPLAY=X

cd %SRCBOX%\scripts\nt

call vcvars32
call setenv

cd %SRCBOX%\scripts\nt

call iclvars
call setenv

IF "%1" == "" GOTO ERROR
GOTO %1
GOTO ERROR

:vc
cd %SRCBOX%\scripts\nt
call runmake gw opt all
GOTO EOF

:intc
cd %SRCBOX%\scripts\nt
call runmake gw opt-intc all
GOTO EOF


:ERROR 
echo Please set compiler as parameter: 
echo "vc" for Visual C++
echo "intc" for Intel C++

:EOF
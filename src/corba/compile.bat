set SCRIPTSBOX=%SRCBOX%
set MACHINE=Intelnt
set DISPLAY=X
set GSIDIR=%DSTBOX%\gsi\test

cd %SRCBOX%\scripts\nt

call vcvars32
call setenv

cd %SRCBOX%\corba

msdev cpp\corba.dsw /MAKE "Corba - Win32 Release"

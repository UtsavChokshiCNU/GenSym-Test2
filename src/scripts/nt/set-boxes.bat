rem This batch file must be run from /scrips/nt directory

if not defined SRCBOX set "SRCBOX=%~dp0..\.."
if not defined DSTBOX set "DSTBOX=%SRCBOX%\..\dst"
if not defined G2V83_OK set G2V83_OK="%SRCBOX%\license\g2sitev2015.ok"
if not defined G2_PATH set "G2_PATH=%DSTBOX%\g2\opt"
if not defined TWNG_PATH set "TWNG_PATH=%DSTBOX%\twng\opt"
if not defined CRTHOME set CRTHOME=C:\CRT

set path=%SRCBOX%\scripts\nt;%SRCBOX%\promote\bin;%SRCBOX%\tests\performance;%PATH%
set path=%path%;C:\cabsdk\BIN;

set SCRIPTSBOX=%SRCBOX%
set MACHINE=Intelnt
set DISPLAY=X

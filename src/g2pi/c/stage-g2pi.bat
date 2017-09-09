rem This script stages the G2 PI Bridge for promotion.

setlocal

echo y | rmdir /s %SANDBOX%\stage\g2pi

mkdir %SANDBOX%\stage\g2pi
mkdir %SANDBOX%\stage\g2pi\kbs
mkdir %SANDBOX%\stage\g2pi\bin

rem Copy the kbs
copy %SRCBOX%\g2pi\kbs\g2-pi.kb %SANDBOX%\stage\g2pi\kbs

rem Copy the executables.  One we built, and one we fetch from cvs
copy %DSTBOX%\g2pi\opt\g2pi.exe %SANDBOX%\stage\g2pi\bin
copy %SRCBOX%\g2pi\bas\g2picfg.exe %SANDBOX%\stage\g2pi\bin

rem Make empty pisrvrs.dat file.  
copy NUL: %SANDBOX%\stage\g2pi\bin\pisrvrs.dat

rem Copy the startup batch file
copy %SRCBOX%\g2pi\c\run-g2-pi.bat %SANDBOX%\stage\g2pi\bin

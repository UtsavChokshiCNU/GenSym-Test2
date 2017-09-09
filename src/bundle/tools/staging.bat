rem This file is to stage built files
rem ===============================================
rem Set up STAGE
rem ===============================================

set STAGE=C:\G2\SRC\bundle\stage

set SRC=C:\G2\SRC

copy /y %SRC%\vstudio2008\g2\Win32\Release\g2.exe %STAGE%\intelnt-g2-84r3\g2\

copy /-y %SRC%\vstudio2008\twng\Release_MFC\twng.exe %STAGE%\intelnt-g2-84r3\g2\
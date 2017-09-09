@echo off
setlocal
set HM=%ROOTDIR%
set PATH=%HM%\gsi;%PATH%
"%HM%\g2i\G2Agent\intelnt\bin\G2Agent.exe" %*

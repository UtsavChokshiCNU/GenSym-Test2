@echo off
setlocal
set HM=%ROOTDIR%
set PATH=%HM%\gsi;%RTI_HOME%\bin;%PATH%
"%HM%\hla\bin\G2-hla.exe" %*

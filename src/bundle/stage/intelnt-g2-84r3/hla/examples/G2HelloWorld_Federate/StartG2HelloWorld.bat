@echo off
setlocal
set HM=%ROOTDIR%
set PATH=%HM%\gsi;%RTI_HOME%\bin;%HM%\hla\resources;%PATH%
"%HM%\hla\examples\G2HelloWorld_Federate\G2HelloWorld.exe" %*

@echo off
setlocal
set HM=%ROOTDIR%
set PATH=%HM%\gsi;%RTI_HOME%\bin;%HM%\hla\resources;%PATH%
"%HM%\hla\examples\G2Demo_Federate\G2Demo.exe" %*

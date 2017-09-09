@echo off
setlocal
set GSI_ROOT=%ROOTDIR%\mssql
"%GSI_ROOT%\bin\x64\g2-sqlsvr" %*

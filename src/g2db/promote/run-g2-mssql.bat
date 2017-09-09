@echo off
setlocal
set GSI_ROOT=%ROOTDIR%\mssql
"%GSI_ROOT%\bin\g2-sqlsvr" %*

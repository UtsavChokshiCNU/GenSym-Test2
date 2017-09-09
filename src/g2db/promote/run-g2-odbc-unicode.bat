@echo off
setlocal
set GSI_ROOT=%ROOTDIR%\odbc_unicode
"%GSI_ROOT%\bin\g2-odbc" %*

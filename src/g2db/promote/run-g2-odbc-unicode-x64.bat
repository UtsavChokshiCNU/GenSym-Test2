@echo off
setlocal
set GSI_ROOT=%ROOTDIR%\odbc_unicode
"%GSI_ROOT%\bin\x64\g2-odbc" %*

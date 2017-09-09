@echo off
setlocal
set GSI_ROOT=%ROOTDIR%\opcclient
start /b "G2-OPC Client Bridge" "%GSI_ROOT%\x64\g2opc" %*

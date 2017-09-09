@echo off
setlocal

set "G2_PATH=C:\G2\dst\g2\opt-mt"
set "G2THREADS=%NUMBER_OF_PROCESSORS%"
call %~dp0\StartServer.bat %*

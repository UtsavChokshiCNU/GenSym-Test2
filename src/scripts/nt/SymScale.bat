@echo off
setlocal

set "G2_PATH=C:\G2\dst\g2\opt"
set "G2EXE=SymScale"

rem set "G2_ARGS=-threads 2"
rem set "G2_ARGS=-legacy"

call %~dp0\StartServer.bat %*

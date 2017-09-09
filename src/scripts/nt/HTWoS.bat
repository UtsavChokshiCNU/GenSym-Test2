@echo off
setlocal

set "G2_PATH=C:\G2\dst\g2\opt"
set "G2EXE=SymScale"

mkdir C:\G2\dst\g2\opt\logs

rem set "G2_ARGS=-threads 4"
rem set "G2_ARGS=-legacy"

call %~dp0\StartServer.bat -kb ..\..\tests\performance\htwos\htwos.kb

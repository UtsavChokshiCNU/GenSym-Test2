@echo off
setlocal

call %~dp0\StartLW-common.bat
set "G2THREADS=%NUMBER_OF_PROCESSORS%"
cd C:/G2/src/vstudio/mtg2
start mtg2.sln

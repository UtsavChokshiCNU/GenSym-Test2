@echo off

REM Starts 32 bit, non-unicode ODBC bridge. 
REM Use 32 bit ODBC admin (c:\Windows\SysWOW64\odbcad32.exe) to set DSNs

setlocal
call %~p0\set-boxes.bat
set GSI_ROOT=%SRCBOX%\license\ODBC

REM ========= DEBUG VERSION ===============================
REM set log=c:\g2\logs\StartODBC.log
REM echo === ENVIRONMENT =========== >> %log%
REM set >> %log%
REM echo ====== COMMAND TO RUN ========== >> %log%
REM echo "%DSTBOX%\odbc\g2-odbc.exe %* >> %log% 2>&1" >> %log% 
REM %DSTBOX%\odbc\g2-odbc.exe %* >> %log% 2>&1

reg Query "HKLM\Hardware\Description\System\CentralProcessor\0" | find /i "x86" > NUL && set OS=32BIT || set OS=64BIT

if exist %DSTBOX%\odbc\x64\g2-odbc.exe if %OS%==64BIT (
   REM ============= 64-BIT VERSION
   %DSTBOX%\odbc\x64\g2-odbc.exe %* 
) else (
   REM ============= 32-BIT VERSION
   %DSTBOX%\odbc\g2-odbc.exe %* 
)
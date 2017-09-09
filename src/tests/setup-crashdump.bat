@echo off
set MINI_DUMP=1
set ROOT=HKLM\SOFTWARE\Microsoft\Windows\Windows Error Reporting\LocalDumps
set DUMP_FOLDER=d:\g2\src\tests\crashdump

if exist "%DUMP_FOLDER%" rmdir /S /Q "%DUMP_FOLDER%"
mkdir "%DUMP_FOLDER%"

reg add "%root%" /f
reg add "%root%" /f /reg:64

reg add "%root%\g2.exe" /f
reg add "%root%\g2.exe" /f /reg:64
reg add "%root%\g2.exe" /f /v DumpFolder /d  "%DUMP_FOLDER%"
reg add "%root%\g2.exe" /f /v DumpFolder /d  "%DUMP_FOLDER%" /reg:64
reg add "%root%\g2.exe" /f /v DumpCount /d  1024 /t REG_DWORD
reg add "%root%\g2.exe" /f /v DumpCount /d  1024 /t REG_DWORD /reg:64
reg add "%root%\g2.exe" /f /v DumpType /d  %MINI_DUMP% /t REG_DWORD
reg add "%root%\g2.exe" /f /v DumpType /d  %MINI_DUMP% /t REG_DWORD /reg:64

reg add "%root%\twng.exe" /f
reg add "%root%\twng.exe" /f /reg:64
reg add "%root%\twng.exe" /f /v DumpFolder /d  "%DUMP_FOLDER%"
reg add "%root%\twng.exe" /f /v DumpFolder /d  "%DUMP_FOLDER%" /reg:64
reg add "%root%\twng.exe" /f /v DumpCount /d  1024 /t REG_DWORD
reg add "%root%\twng.exe" /f /v DumpCount /d  1024 /t REG_DWORD /reg:64
reg add "%root%\twng.exe" /f /v DumpType /d  %MINI_DUMP% /t REG_DWORD
reg add "%root%\twng.exe" /f /v DumpType /d  %MINI_DUMP% /t REG_DWORD /reg:64
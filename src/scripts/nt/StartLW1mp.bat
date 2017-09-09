@echo off
setlocal

rem This batch file launches G2 with a full -module-search-path provided.
rem You may supply all valid G2 commandline arguments.

rem To set a timeout for G2 execution, supply environment variables:
rem `key_part_of_command_line_to_kill_after_timeout' - it is a part of commandline such that 
rem the process to be killed is uniquely identified by this part (e.g. kb name)
rem `approximate_lw1mp_timeout_in_seconds' - timeout before process is killed 
rem (with some default, see below)
rem If timeout is set, this batch file does not return until G2 process is terminated
rem note that extra 10 seconds is left for every process to start.


call %~dp0set-boxes.bat

rem Force using ENT license:
set G2V83_OK="C:\G2\src\license\g2sitev2015-ent.ok"

set "TITLE_='G2 Server (development mode)'"

call :searchPath "kbs" "g2\kbs\utils"
call :searchPath "kbs" "g2\kbs\samples"
call :searchPath "kbs\sources" ""
call :searchPath "kbs\tools" ""
rem call :searchPath "..\dst\g2i\staging" "g2i\kbs"
call :searchPath "g2i\kbs" "g2i\examples"
call :searchPath "g2i\kbs" "jmail\kbs"
call :searchPath "g2i\kbs" "jms\kbs"
call :searchPath "g2i\sites\Integrity\kbs" "integrity\kbs"
call :searchPath "g2i\sites\Optegrity\kbs" "optegrity\kbs"
call :searchPath "g2i\sites\e-SCOR\kbs" "escor\kbs"
call :searchPath "g2i\sites\ReThink\kbs" "rethink\kbs"
call :searchPath "g2i\sites\Nol\kbs" "nol\kbs"
call :searchPath "g2i\sites\HLA\kbs" "hla\kbs"
call :searchPath "g2i\sites\DevSite\kbs" ""
call :searchPath "gdanol\common\kbs" ""
call :searchPath "gdanol\gda\kbs" "gda\kbs"
call :searchPath "gdanol\nol\kbs" "nol\kbs"
call :searchPath "java\products\javalink\kbs" "javalink\kbs"
call :searchPath "g2db\kbs\src" "oracle\kbs"
call :searchPath "g2pi\kbs" "pi\kbs"
call :searchPath "g2opc\kbs" "opcclient\kbs"
call :searchPath "gw\kbs" "gw\kbs"
call :searchPath "tests" ""

if "%G2RGN1LMT%" == "" set G2RGN1LMT=40000000
if "%G2RGN2LMT%" == "" set G2RGN2LMT=3500000
if "%G2EXE%" == "" set G2EXE=g2

SET "G2_ARGS=%G2_ARGS% %* -resourcefile '%SRCBOX%\g2i\kbs\resources-*.txt' -configfile '%SRCBOX%\g2i\kbs\config.txt' -fonts '%SRCBOX%\promote\fonts' -g2passwdexe '%G2_PATH%\g2passwd.exe'"
SET "G2_ARGS=%G2_ARGS% -ok %G2V83_OK%"
rem Reserved for CRT debug
rem SET "G2_ARGS=%G2_ARGS% -ok %G2V83_OK% -init-string %CRTHOME%\config\crt.ini -kb %CRTHOME%\kbs\v-crt-dep.kb"

if "" neq "%MI_COVERAGE_REPORT_FILE%" ( SET "G2_ARGS=-measure-coverage %MI_COVERAGE_REPORT_FILE% %G2_ARGS%" )

cd /d C:/G2/src/lisp

REM this G2_IN_LISP_EXECUTABLE is used elsewhere. If you change this variable, 
REM grep it in *.bat and *.xml
set G2_IN_LISP_EXECUTABLE=lispworks-6-0-0-x64-windows.exe
start "LW" "C:\Program Files\LispWorks\%G2_IN_LISP_EXECUTABLE%" -load c:\G2\src\tests\load-g2-lw-for-regression-tests.lisp %G2_ARGS%

REM Timeout guard
if "%key_part_of_command_line_to_kill_after_timeout%" == "" goto :end_of_file
if "%approximate_lw1mp_timeout_in_seconds%" == "" set approximate_lw1mp_timeout_in_seconds=360

REM Give the process a time to start. 
REM Using ping is a "canonical way" to sleep in batch file on Windows
REM Next command will sleep for approximately n-1 or n seconds, depending on if 127.0.0.1 is reachable or not
ping 127.0.0.1 -n 11 -w 10 >nul

REM Enable timeout guard
call %~dp0KillProcessByKeyAfterTimeout %KEY_PART_OF_COMMAND_LINE_TO_KILL_AFTER_TIMEOUT% %G2_IN_LISP_EXECUTABLE% %approximate_lw1mp_timeout_in_seconds%

goto :end_of_file

:searchPath
  SET "KBS_PATH=%~1"
  if defined INSTALL_DIR ( SET "KBS_PATH=%~2" )
  
  if exist "%SRCBOX%\%KBS_PATH%" set "G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%SRCBOX%\%KBS_PATH%'"
exit /b

:end_of_file

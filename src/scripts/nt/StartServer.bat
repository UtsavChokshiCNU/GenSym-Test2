@echo off
setlocal

rem
rem This batch file launches G2 with a full -module-search-path provided.
rem You may supply all valid G2 commandline arguments.

call %~dp0\set-boxes.bat

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

SET "G2_ARGS=%G2_ARGS% %* -icon %TITLE_% -name %TITLE_% -resourcefile '%SRCBOX%\g2i\kbs\resources-*.txt' -configfile '%SRCBOX%\g2i\kbs\config.txt' -fonts '%SRCBOX%\promote\fonts' -g2passwdexe '%G2_PATH%\g2passwd.exe'"
SET "G2_ARGS=%G2_ARGS% -ok %G2V83_OK%"
rem Reserved for CRT debug
rem SET "G2_ARGS=%G2_ARGS% -ok %G2V83_OK% -init-string %CRTHOME%\config\crt.ini -kb %CRTHOME%\kbs\v-crt-dep.kb"

if "" neq "%MI_COVERAGE_REPORT_FILE%" ( SET "G2_ARGS=-measure-coverage %MI_COVERAGE_REPORT_FILE% %G2_ARGS%" )
SET START_CALL=start "%TITLE_%"

%START_CALL% "%G2_PATH%\%G2EXE%" %G2_ARGS%
goto end

:searchPath
  SET "KBS_PATH=%~1"
  if defined INSTALL_DIR ( SET "KBS_PATH=%~2" )
  
  if exist "%SRCBOX%\%KBS_PATH%" set "G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%SRCBOX%\%KBS_PATH%'"
exit /b

:end

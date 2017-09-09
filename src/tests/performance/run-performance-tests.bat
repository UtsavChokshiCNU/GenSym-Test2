@echo off
setlocal ENABLEEXTENSIONS
prompt $t$g 

if "" == "%~1" ( 
  call %~n0 UC1 UC3 UC2 UC4a UC5 UC6 UC8 UC9 UC10 UC11a UC11b UC13 UC14 UC16 UC17
  call taskkill /IM typeperf.exe /F
  exit /b
)

set "N=3"
set "UC1=run-load-long-kb-measurement"
set "UC2= 1112 %N% ALL-G2-x64-abort-2 3 merge-kb-time"
set "UC3= 1113 %N% ALL-G2-x64-abort-2 2 recompile-kb-time"
set "UC4a= 1114 %N% aero-simulation-time 2 aero-simulation-time"
set "UC4b= 1115 1 ap-prm-test-2-measurement 2 ap-prm-test-2-measurement 1 true twng"
set "UC5= 1116 %N% specific-fault-model-measurement 2 fault-model-report"
set "UC6= 1117 %N% tree-nodes-100-obj 12 tree-view-report 1 true twng"
set "UC7= 1118 1 htwos\htwos 2 washington-river-report"
set "UC8= 1119 %N% gensym-mean-shift-outliers\continental-statistical-functions-benchmark-test 2 continental-statistical-benchmark-report"
set "UC9= 1120 %N% ss-function-benchmark-tests 2 smart-signal-report"
set "UC10= 1121 %N% nokia-faster-1 4 nokia-faster-1"
set "UC11a= 2222 %N% uc11\uc11rpc 1 uc11rpc 1000000"
set "UC11b= 2222 %N% uc11\uc11caching 1 uc11caching 100000"
set "UC13= 1124 %N% uc13 1 uc13"
set "UC14= 1125 %N% uc14 1 uc14 130"
set "UC15= 1126 %N% uc15\htwos 1 uc15"
set "UC15a= 1126 %N% uc15a\htwos 1 uc15a"
set "UC16= 1127 %N% dalkia-2 1 uc16 100"
set "UC17= 1128 %N% uc17 1 uc17 1000000"

if defined INSTALL_DIR ( call :useInstaller )

:_again
call :_run %~1
shift /1
if "" neq "%~1" ( goto :_again ) else ( call taskkill /IM typeperf.exe /F )

endlocal
exit /b

:_run
  title Launching [%~1]
  if "UC1" == "%~1" ( 
    call %%%~1%% %N% 1111
  ) else (
    if "UC2" == "%~1" ( set "G2_MERGE_KB_NAME=%~dp0..\lz-htwos.kb" )
    if "UC3" == "%~1" ( set "G2_RECOMPILE_KB_NAME=ALL-G2-x64-abort-2.kb" )
    if "UC11a" == "%~1" ( set "UC_SETUP=uc11setup.bat" )
    if "UC11b" == "%~1" ( set "UC_SETUP=uc11setup.bat" )
    call run-measurement%%%~1%%
  )
  if defined UC_SETUP set UC_SETUP=
  if defined G2_MERGE_KB_NAME set G2_MERGE_KB_NAME=
  if defined G2_RECOMPILE_KB_NAME set G2_RECOMPILE_KB_NAME=

exit /b

:useInstaller
	SET "G2_AUTO_TEST=%SRCBOX%\tests\performance\results"
	SET "SRCBOX=%INSTALL_DIR%"
	SET "G2_PATH=%SRCBOX%\g2"
	SET "G2V83_OK=%G2_PATH%\g2.ok"
	SET "G2_OK=%G2_PATH%\g2.ok"
	SET "REPORT_DIR=%G2_AUTO_TEST%"
exit /b

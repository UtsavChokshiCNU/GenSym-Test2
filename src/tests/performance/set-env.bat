set "PATH=..\..\scripts\nt;%PATH%"

call set-boxes

if not defined G2_AUTO_TEST ( set "G2_AUTO_TEST=%SRCBOX%\tests\performance\results" )
if not defined REPORT_DIR ( set "REPORT_DIR=%G2_AUTO_TEST%" )
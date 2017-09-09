set G2V83_OK=C:\G2\license\g2sitev83.ok
set G2_AUTO_TEST=C:\G2\src\tests\performance\results
set G2_MODULE_SEARCH_PATH= 'C:\G2\src\kbs\sources' 'C:\G2\src\kbs\' 'C:\G2\src\g2i\kbs' 'C:\G2\src\g2i\sites\Integrity\kbs' 'C:\G2\src\java\products\javalink\kbs' 'C:\G2\src\g2db\kbs' 'C:\G2\src\g2i\sites\Optegrity\kbs' 'C:\G2\src\g2i\sites\e-scor\kbs' 'C:\G2\src\g2pi\kbs' 'C:\G2\src\g2i\sites\ReThink\kbs' 'C:\G2\src\g2i\sites\Nol\kbs' 'C:\G2\src\g2i\sites\HLA\kbs' 'C:\G2\src\g2opc\kbs' 'C:\G2\src\gdanol\gda\kbs' 'C:\G2\src\gdanol\common\kbs' 'C:\G2\src\gdanol\nol\kbs' 'C:\G2\src\tests'
set G2_OK=C:\G2\lisence\g2sitev83.ok
set "REPORT_DIR=%G2_AUTO_TEST%"

set SRCBOX=C:\G2\src\
set DSTBOX=C:\G2\dst\

set SCRIPTSBOX=%SRCBOX%
set MACHINE=Intelnt
set DISPLAY=X
set USE_VS2008=YES

REM In visual studio, set the following debugging options for G2.exe
REM -kb C:\G2\src\tests\performance\aero-simulation-time.kb -start -log .\results\log_g2.log -ok C:\G2\src\scripts\nt\..\..\..\license\g2sitev83.ok   -icon "G2 Server (development mode)" -name "G2 Server (development mode)" -resourcefile 'C:\G2\src\scripts\nt\..\..\g2i\kbs\resources-*.txt' -configfile 'C:\G2\src\scripts\nt\..\..\g2i\kbs\config.txt' -ok C:\G2\src\scripts\nt\..\..\..\license\g2sitev83.ok
REM Working directory: C:\G2\src\tests\performance\
call "C:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\IDE\devenv.exe"                                                                                                                                                                                                                                                                                                                                      

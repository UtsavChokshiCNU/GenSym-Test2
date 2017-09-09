@REM E.g.: srG2.bat -kb C:\G2\src\tests\performance\aero-simulation-time.kb -start
@REM  -kb C:\G2\src\kbs\profiler.kb 
start c:\G2\dst\G2\opt\G2.exe -log C:\G2\src\tests\performance\vsProfile\logs\g2_log.txt -icon "G2 Server (development mode)" -name "G2 Server (development mode)" -resourcefile 'C:\G2\src\g2i\kbs\resources-*.txt' -configfile 'C:\G2\src\g2i\kbs\config.txt' -ok C:\G2\license\g2sitev83.ok %*
@REM start c:\G2\dst\TWNG\opt\twng.exe localhost 1111 -log C:\G2\src\tests\performance\vsProfile\logs\twng_1111_log.txt